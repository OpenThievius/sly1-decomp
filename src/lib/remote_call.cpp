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


// A packet of the command channel: the channel's header, then the request.
struct RemoteCallPacket {
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
struct Entry_1F7FC0 {
    u32 key;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    u8 f18[0x20];
    Entry_1F7FC0* next;
};

struct Group_1F7FC0 {
    s32 f0;
    s32 f4;
    Entry_1F7FC0* entries;
    s32 fC;
    s32 f10;
    Group_1F7FC0* next;
};

// The client's state: the next packet id, the pool of request packets, the reply ring.
struct Pools_1F7BE8 {
    s32 next_id;
    RemoteCallPacket* packets;
    s32 packet_count;
    s32 fC;
    s32 f10;
    RemoteCallPacket* replies;
    s32 reply_count;
    RemoteCallPacket* f1C;
    s32 f20;
    s32 cursor;
    Group_1F7FC0* groups;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
};

s32 D_00277134 = 0;

static u8 D_00626000[0x800];
static u8 D_00626800[0x800];
static u8 D_00627000[0x800];
static Pools_1F7BE8 D_00627800;

s32 func_001F9D60(void);
void func_001F9DA8(void);
void func_001FA468(void);
s32 func_001F6B20(SemaphoreParams* params);
void func_001F6B30(s32 sema);
void func_001F6B50(s32 sema);
s32 func_001F6B60(s32 sema);
s32 func_001FA630(u32 cmd, void* data, s32 size, s32 a3, s32 a4, s32 a5);
s32 func_001FA670(u32 cmd, void* data, s32 size, s32 a3, s32 a4, s32 a5);
void func_001F71D0(void* thread);

INCLUDE_ASM(func_001F7BE8);

void func_001F7D88(void)
{
    ShutDownCommandChannel();
    g_remoteCallsReady = 0;
}

RemoteCallPacket* func_001F7DB0(Pools_1F7BE8* self)
{
    DisableInterrupts();
    s32 count = self->packet_count;
    s32 index = 0;
    RemoteCallPacket* item = self->packets;
    if (count > 0) {
        do {
            if ((item->flags & 1) == 0) {
                item->flags = (index << 16) | 5;
                s32 id;
                self->next_id++;
                if (self->next_id == 1) {
                    id = self->next_id++;
                } else {
                    id = self->next_id;
                }
                item->self = (u32)item;
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

void func_001F7E58(RemoteCallPacket* packet)
{
    packet->id = 0;
    packet->flags &= ~1u;
}

RemoteCallPacket* func_001F7E78(Pools_1F7BE8* r)
{
    s32 index = r->cursor % r->reply_count;
    s32 off = index << 6;
    r->cursor = index + 1;
    return (RemoteCallPacket*)((u8*)r->replies + off);
}

void func_001F7EA8(RemoteCallPacket* reply)
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
        s0->callback(s0->callbackArg);
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
    FreeRequestPacket(s0->packet);
    s0->packet = 0;
}

void func_001F7F60(RemoteCallPacket* src, Pools_1F7BE8* pools)
{
    RemoteCallPacket* m = NextReplyPacket(pools);
    u32 a = src->self;
    u32 b = src->client;
    m->self = a;
    m->client = b;
    m->cmd = 0x8000000C;
    SendCommandFromInterrupt(0x80000008, m, 0x40, src->cmd, src->f24, src->f28);
}

Entry_1F7FC0* func_001F7FC0(u32 key, Pools_1F7BE8* pools)
{
    Group_1F7FC0* group = pools->groups;
    while (group) {
        Entry_1F7FC0* entry = group->entries;
        while (entry) {
            if (entry->key == key) return entry;
            entry = entry->next;
        }
        group = group->next;
    }
    return 0;
}

void func_001F8010(RemoteCallPacket* src, Pools_1F7BE8* pools)
{
    RemoteCallPacket* m = NextReplyPacket(pools);
    u32 a = src->self;
    u32 b = src->client;
    m->self = a;
    m->client = b;
    m->cmd = 0x80000009;
    Entry_1F7FC0* n = FindRemoteService(src->cmd, pools);
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

s32 func_001F80C0(RemoteCallClient* self, u32 cmd, s32 mode)
{
    SemaphoreParams params;
    RemoteCallPacket* packet;
    s32 sema;

    self->f10 = 0;
    self->server = 0;
    packet = TakeRequestPacket(&g_remoteCallState);
    if (packet == 0) return -1;
    self->packet = packet;
    self->id = packet->id;
    packet->cmd = cmd;
    packet->self = (u32)packet;
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

struct Node_001F8200 {
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
    s32 f3C;
    Node_001F8200* f40;
};

struct Ctx_001F8200 {
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
    Node_001F8200* f34;
};



void func_001F8200(Ctx_001F8200* self)
{
    Node_001F8200* n = self->f34;
    Node_001F8200* list = n->f40;
    if (list->f0C == 0) {
        list->f0C = (s32)n;
    } else {
        ((Node_001F8200*)list->f10)->f3C = (s32)n;
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
    QueueThreadRequest((void*)list->f00);
}

INCLUDE_ASM(func_001F8290);

s32 func_001F8480(RemoteCallClient* self)
{
    RemoteCallPacket* p = self->packet;
    if (p != 0 && self->id == p->id) {
        u32 f = p->flags & 1;
        if (f != 0) goto yes;
    }
    return 0;
yes:
    return 1;
}

LINKER_REMNANT(func_001F84C0);
