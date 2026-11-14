// SPDX-License-Identifier: AGPL-3.0-or-later
// An object of the kernel library from 0x1F7BE8 to 0x1F84D8, built whole (config/us/files.tsv):
// a client of the command channel to the IOP. func_001F7BE8 sets it up once (the flag
// D_00277134, cleared again by func_001F7D88): the record D_00627800 with its three pools of
// 0x40-byte packets in .bss (D_00626000, D_00626800, D_00627000, used through their uncached
// addresses) and the handlers of the commands 0x80000008 to 0x8000000C. func_001F7DB0 takes a
// free packet of the first pool and func_001F7E58 frees it; func_001F7E78 takes the next packet of
// the reply ring; func_001F7EA8, func_001F7F60, func_001F8010 and func_001F8200 are the command
// handlers; func_001F80C0 and func_001F8290 open a client and send its request; func_001F8480
// checks that a client's packet is still its own. The leftover func_001F84C0 ends the object.
#include "common.h"
#include "remote_call_client.h"
#include "semaphore_params.h"
#include "asm_func.h"


// A packet of the command channel: the channel's header, then the request. This is a request of
// this side, taken from the pool of TakeRequestPacket: its self word is its own address, and a
// pointer (CallRemoteService's code needs that store in a class of its own:
// docs/toolchain/alias-classes.md, "A store that conflicts with two classes").
struct RemoteCallPacket {
    u32 head[4];
    u32 flags;
    RemoteCallPacket* self;
    s32 id;
    u32 client;
    u32 cmd;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
};

// A packet the IOP sent, and the reply to one: the same layout, with the sender's self and
// client words, which are the IOP's and plain words here (AnswerIopCall's and
// AnswerServiceLookup's code needs them in the int class).
struct IopCallPacket {
    u32 head[4];
    u32 flags;
    u32 self;
    s32 id;
    u32 client;
    u32 cmd;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
};

// An IOP-side list the command 0x80000009 searches: groups of entries, each entry keyed by its
// first word.
struct ServiceRecord {
    u32 key;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    u8 f18[0x20];
    ServiceRecord* next;
};

struct ServiceGroup {
    s32 f0;
    s32 f4;
    ServiceRecord* entries;
    s32 fC;
    s32 f10;
    ServiceGroup* next;
};

// The client's state: the next packet id, the pool of request packets, the reply ring and the
// service groups of the IOP.
struct RemoteCallState {
    s32 nextId;
    RemoteCallPacket* packets;
    s32 packetCount;
    s32 fC;
    s32 f10;
    IopCallPacket* replies;
    s32 replyCount;
    RemoteCallPacket* thirdPool;
    s32 thirdPoolCount;
    s32 replyCursor;
    ServiceGroup* serviceGroups;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
};

s32 g_remoteCallsReady = 0;

static u8 D_00626000[0x800];
static u8 D_00626800[0x800];
static u8 D_00627000[0x800];
static RemoteCallState g_remoteCallState;

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
void ShutDownCommandChannel(void);
extern "C" s32 NewSemaphore(SemaphoreParams* params);
extern "C" s32 FreeSemaphore(s32 sema);
extern "C" void PostSemaphoreFromInterrupt(s32 sema);
extern "C" s32 AwaitSemaphore(s32 sema);
s32 SendCommand(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count);
s32 SendCommandFromInterrupt(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count);
s32 QueueThreadRequest(s32 tid);
extern "C" void WriteBackDataCacheRange(void* data, s32 size);

void InitCommandChannel(void);
s32 GetChannelWord(s32 index);
struct CommandPacket;
struct CommandChannel;
typedef void (*CommandHandler)(CommandPacket* packet, CommandChannel* channel);
extern "C" void SetCommandHandler(s32 cmd, CommandHandler handler, void* arg);
s32 ReadIopRegister(u32 reg);
u32 WriteIopRegister(u32 reg, u32 value);
void HandleRemoteCallReply(RemoteCallPacket* reply);
void AnswerServiceLookup(IopCallPacket* src, RemoteCallState* pools);
void QueueServerRequest(struct ServerRequestPacket* self);
void AnswerIopCall(IopCallPacket* src, RemoteCallState* pools);

extern "C" void InitRemoteCalls(s32 mode)
{
    DisableInterrupts();
    if (g_remoteCallsReady != 0) {
        EnableInterrupts();
        return;
    }
    g_remoteCallsReady = 1;
    EnableInterrupts();
    InitCommandChannel();
    DisableInterrupts();
    RemoteCallState* s = &g_remoteCallState;
    s->packets = (RemoteCallPacket*)((u32)D_00626000 | 0x20000000);
    s->packetCount = 0x20;
    s->fC = 0;
    s->f10 = 0;
    s->replies = (IopCallPacket*)((u32)D_00626800 | 0x20000000);
    s->replyCount = 0x20;
    s->thirdPool = (RemoteCallPacket*)((u32)D_00627000 | 0x20000000);
    s->thirdPoolCount = 0x20;
    s->replyCursor = 0;
    // The id counter is set after the pools: Sony's compiler then stores it after the pool
    // sizes (docs/TOOLCHAIN.md, "A run of stores in two alias classes").
    s->nextId = 1;
    SetCommandHandler(0x80000008, (CommandHandler)HandleRemoteCallReply, s);
    SetCommandHandler(0x80000009, (CommandHandler)AnswerServiceLookup, s);
    SetCommandHandler(0x8000000A, (CommandHandler)QueueServerRequest, s);
    SetCommandHandler(0x8000000C, (CommandHandler)AnswerIopCall, s);
    EnableInterrupts();
    if (ReadIopRegister(0x80000002) != 0) {
        return;
    }
    RemoteCallPacket* p = (RemoteCallPacket*)D_00626000 + 1;
    p->head[3] = 1;
    SendCommand(0x80000002, p, 0x10, 0, 0, 0);
    while (GetChannelWord(0) == 0) {
    }
    WriteIopRegister(0x80000002, 1);
}

void ShutDownRemoteCalls(void)
{
    ShutDownCommandChannel();
    g_remoteCallsReady = 0;
}

RemoteCallPacket* TakeRequestPacket(RemoteCallState* self)
{
    DisableInterrupts();
    s32 count = self->packetCount;
    s32 index = 0;
    RemoteCallPacket* item = self->packets;
    if (count > 0) {
        do {
            if ((item->flags & 1) == 0) {
                item->flags = (index << 16) | 5;
                s32 id;
                self->nextId++;
                if (self->nextId == 1) {
                    id = self->nextId++;
                } else {
                    id = self->nextId;
                }
                item->self = item;
                item->id = id;
                EnableInterrupts();
                return item;
            }
            index++;
            item++;
        } while (index < count);
    }
    EnableInterrupts();
    return 0;
}

void FreeRequestPacket(RemoteCallPacket* packet)
{
    packet->id = 0;
    packet->flags &= ~1u;
}

IopCallPacket* NextReplyPacket(RemoteCallState* r)
{
    s32 index = r->replyCursor % r->replyCount;
    s32 off = index << 6;
    r->replyCursor = index + 1;
    return (IopCallPacket*)((u8*)r->replies + off);
}

void HandleRemoteCallReply(RemoteCallPacket* reply)
{
    RemoteCallClient* s0;
    u32 cmd = reply->cmd;
    if (cmd == 0x8000000A) goto call_path;
    if (cmd > 0x8000000A) {
        s0 = (RemoteCallClient*)reply->client;
        goto after;
    }
    if (cmd == 0x80000009) goto set_fields;
    s0 = (RemoteCallClient*)reply->client;
    goto after;
call_path:
    s0 = (RemoteCallClient*)reply->client;
    if (s0->callback != 0) {
        ((RemoteCallEndFn)s0->callback)((void*)s0->callbackArg);
        s0 = (RemoteCallClient*)reply->client;
    }
    goto after;
set_fields:
    s0 = (RemoteCallClient*)reply->client;
    s0->server = reply->f24;
    s0->f14 = reply->f28;
    s0->f18 = reply->f2C;
after:
    s32 sema = s0->sema;
    if (sema >= 0) PostSemaphoreFromInterrupt(sema);
    FreeRequestPacket(s0->packet.ptr);
    s0->packet.ptr = 0;
}

void AnswerIopCall(IopCallPacket* src, RemoteCallState* pools)
{
    IopCallPacket* m = NextReplyPacket(pools);
    u32 a = src->self;
    u32 b = src->client;
    m->self = a;
    m->client = b;
    m->cmd = 0x8000000C;
    SendCommandFromInterrupt(0x80000008, m, 0x40, (void*)src->cmd, src->f24, src->f28);
}

ServiceRecord* FindRemoteService(u32 key, RemoteCallState* pools)
{
    ServiceGroup* group = pools->serviceGroups;
    while (group) {
        ServiceRecord* entry = group->entries;
        while (entry) {
            if (entry->key == key) return entry;
            entry = entry->next;
        }
        group = group->next;
    }
    return 0;
}

void AnswerServiceLookup(IopCallPacket* src, RemoteCallState* pools)
{
    IopCallPacket* m = NextReplyPacket(pools);
    u32 a = src->self;
    u32 b = src->client;
    m->self = a;
    m->client = b;
    m->cmd = 0x80000009;
    ServiceRecord* n = FindRemoteService(src->cmd, pools);
    if (n == 0) {
        m->f24 = 0;
        m->f28 = 0;
        m->f2C = 0;
    } else {
        m->f24 = (s32)n;
        m->f28 = n->f8;
        m->f2C = n->f14;
    }
    SendCommandFromInterrupt(0x80000008, m, 0x40, 0, 0, 0);
}

extern "C" s32 BindRemoteService(RemoteCallClient* self, u32 cmd, s32 mode)
{
    SemaphoreParams params;
    RemoteCallPacket* packet;
    s32 sema;

    self->f10 = 0;
    self->server = 0;
    packet = TakeRequestPacket(&g_remoteCallState);
    if (packet == 0) return -1;
    // The id is read before the client's packet word is written: that word is a union member,
    // whose store holds every later load (docs/toolchain/alias-classes.md, "A store that
    // conflicts with two classes").
    s32 id = packet->id;
    self->packet.ptr = packet;
    self->id = id;
    packet->cmd = cmd;
    packet->self = packet;
    packet->client = (u32)self;
    if ((mode & 1) == 0) {
        params.initCount = 0;
        params.maxCount = 1;
        sema = NewSemaphore(&params);
        self->sema = sema;
        if (sema < 0) {
            FreeRequestPacket(packet);
            return -3;
        }
        if (SendCommand(0x80000009, packet, 0x40, 0, 0, 0) == 0) {
            FreeRequestPacket(packet);
            FreeSemaphore(self->sema);
            return -2;
        }
        AwaitSemaphore(self->sema);
        FreeSemaphore(self->sema);
        return 0;
    }
    self->sema = -1;
    if (SendCommand(0x80000009, packet, 0x40, 0, 0, 0) != 0) {
        return 0;
    }
    FreeRequestPacket(packet);
    return -2;
}

// A queued request of the server (func_001F8200): the packet's words, and at 0x40 the list it is
// queued on (its first and last entries at 0x0C and 0x10, the thread to wake at 0x00).
struct ServerRequestEntry {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 next;
    ServerRequestEntry* list;
};

// The request packet func_001F8200 handles: RemoteCallPacket's layout, with the entry it was
// assigned at 0x34.
struct ServerRequestPacket {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    ServerRequestEntry* f34;
};



void QueueServerRequest(ServerRequestPacket* self)
{
    ServerRequestEntry* n = self->f34;
    ServerRequestEntry* list = n->list;
    if (list->f0C == 0) {
        list->f0C = (s32)n;
    } else {
        ((ServerRequestEntry*)list->f10)->next = (s32)n;
    }
    list->f10 = (s32)n;
    s32 a = self->f14;
    s32 b = self->f1C;
    n->f20 = a;
    n->f1C = b;
    n->f24 = self->f20;
    n->f0C = self->f24;
    n->f28 = self->f28;
    n->f2C = self->f2C;
    n->f30 = self->f30;
    n->f34 = self->f10;
    if (list->f00 < 0) {
        return;
    }
    if (list->f04 != 0) {
        return;
    }
    QueueThreadRequest(list->f00);
}

extern "C" s32 CallRemoteService(RemoteCallClient* self, s32 cmd, s32 mode, void* send, s32 sendSize, void* recv, s32 recvSize,
                      RemoteCallEndFn callback, void* callbackArg)
{
    SemaphoreParams params;
    RemoteCallPacket* packet;
    s32 sema;

    packet = TakeRequestPacket(&g_remoteCallState);
    if (packet == 0) return -1;
    // As in BindRemoteService, the id is read before the client's packet word is written.
    s32 id = packet->id;
    self->packet.ptr = packet;
    self->id = id;
    self->callback = (u32)callback;
    self->callbackArg = (s32)callbackArg;
    packet->cmd = cmd;
    packet->f24 = sendSize;
    packet->f28 = (s32)recv;
    packet->f2C = recvSize;
    packet->self = packet;
    packet->f34 = self->server;
    packet->client = (u32)self;
    if ((mode & 2) == 0) {
        if (send == recv) {
            WriteBackDataCacheRange(send, sendSize < recvSize ? recvSize : sendSize);
        } else {
            if (sendSize > 0) WriteBackDataCacheRange(send, sendSize);
            if (recvSize > 0) WriteBackDataCacheRange(recv, recvSize);
        }
    }
    if (mode & 1) {
        if (callback == 0) {
            packet->f30 = 0;
        } else {
            packet->f30 = 1;
        }
        self->sema = -1;
        if (SendCommand(0x8000000A, packet, 0x40, send, self->f14, sendSize) != 0) {
            return 0;
        }
        FreeRequestPacket(packet);
        return -2;
    }
    params.initCount = 0;
    params.maxCount = 1;
    sema = NewSemaphore(&params);
    self->sema = sema;
    if (sema < 0) {
        FreeRequestPacket(packet);
        return -3;
    }
    packet->f30 = 1;
    if (SendCommand(0x8000000A, packet, 0x40, send, self->f14, sendSize) == 0) {
        FreeSemaphore(self->sema);
        FreeRequestPacket(packet);
        return -2;
    }
    AwaitSemaphore(self->sema);
    FreeSemaphore(self->sema);
    return 0;
}

extern "C" s32 IsRemoteCallPending(RemoteCallClient* self)
{
    RemoteCallPacket* p = self->packet.ptr;
    if (p != 0 && self->id == p->id) {
        u32 f = p->flags & 1;
        if (f != 0) goto yes;
    }
    return 0;
yes:
    return 1;
}

LINKER_REMNANT(func_001F84C0);
