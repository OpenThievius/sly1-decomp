// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "child_group_object.h"
#include "attachment.h"
#include "shapes.h"
#include "object_link.h"
#include "stream_reader.h"
#include "stream_reader_window.h"
#include "key_id.h"
#include "identity_key.h"
#include "pad_record.h"
#include "game_progress.h"
#include "globals.h"

// The movie player: its object (D_00269A00), the stream its data comes through, and the two
// sinks a transfer goes to (a ring buffer, and the IPU's DMA channel).

// Where a transfer's data goes: two virtual methods, which retail's vtables list in this order.
class TransferSink {
public:
    virtual s32 Put(s32 size, u8* buf) = 0;
    virtual s32 Idle() = 0;
};

// A ring buffer in the IOP's memory, read through the SIF.
class IopRingSink : public TransferSink {
public:
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 Put(s32 size, u8* buf);
    s32 Idle();
};

// The IPU's input DMA channel.
class IpuDmaSink : public TransferSink {
public:
    s32 Put(s32 size, u8* buf);
    s32 Idle();
};

// The stream the movie's data comes through (func_0018E940 opens it).
struct MovieStream {
    s32 f00;
    s32 f04;
#ifdef VERSION_EU
    u8 pad08[0x28];     // a word longer in PAL: its StartMovieStream has sub-objects at 0x30 and 0x50
#else
    u8 pad08[0x24];
#endif
    u8 sub2C[0x20];
    u8 sub4C[0x20];
    IopRingSink sub6C;
    s32 f8C;
    s32 f90;
};

struct MoviePlayer {
    s32 mode;
    void* f04;
    void* f08;
    void* f0C;
    u8 decoder[0x48];
    void* f58;
    void* f5C;
    u8 queue60[0x20];
    MovieStream stream;
    void* f114;
    void* f118;
    u8 pad11C[0x14];
    s32 f130;
    volatile s32 f134;   // 0x134: the decode thread's step (0, 1, 2); FinishMovie waits for 0
    u32 crc;
    u8* cur;
    s32 remain;
    u8 pad144[4];  // to the label after it, g_movieChecksumFailed
};

ObjectLink D_002699B0[1] = { { 2, 0x317, 0x6B0 } };
f32 D_002699BC = 0.5f;
const char* D_002699C0[16] = {
    "The Secret Police File",
    "The Tokyo Police File",
    "The Making Of Sly Cooper",
    "Commercials & Outtakes",
    "Tide of Terror",
    "Raleigh Hung out to Dry",
    "Sunset Snake Eyes",
    "Muggshot Busted",
    "Vicious Voodoo",
    "Mz Ruby Vexed",
    "Fire in the Sky",
    "The Panda King on Ice",
    "The Cold Heart of Hate",
    "Ten Seconds",
    "The Thievius Raccoonus",
    "Credits"
};
MoviePlayer D_00269A00;
s32 D_00269B48;
s32 D_00269B4C;

extern u8 D_00261858[];




void func_00124DF8(void* self, s32 mode, void* data);

struct Span_18E7C0 {
    s32 a;
    s32 b;
    void* c;
    s32 d;
};

void func_001F6C20(s32 a);
void* func_001F6CA0(Span_18E7C0* span, s32 n);
s32 func_001F6C90(void* obj);


s32 func_001833F0(void* key, void* item);
s32 func_001300E8(void* key, void* item);
s32 func_001B8A08(void* self, void* key);



struct Obj_18EA48 { s32 flag; u8 pad0[0x2C - 4]; };

void func_0011E460(void);
void func_0013C9B0(void* state);

struct Obj_18F148 { u8 pad0[4]; s32 f04; s32 f08; };

void func_001B7B78(void* self);
void func_0012E760(void* obj);

extern u8 D_002CBB40[];

void func_0011D6A8(u32 a0);
void func_0011D6D8(u32 a0);
void func_0011E010(void);
s32 func_0011CE30(void);
void func_0011E110(s32 a0);
s32 func_0011E1F8(s32 flag);
s32 func_0011D4B8(s32 arg);
void func_0011D480(s32 a0, s32 a1);
s32 func_0011E428(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001C08B0(void* p, s32 a, s32 b);
void func_0013C988(void* state, s32 size, void* buf);

struct Obj_18EAA0 {
    s32 f00;
    u8 pad04[0x88];
    s32 f8C;
    s32 f90;
};

void func_0011E498(void);
void func_001C0950(void* p);

s32 func_0013CC00(void* queue, s32 size, void* data);

struct Args_18EC80 { u8 pad0[8]; u8* f8; s32 fC; };

struct Blk_18EB98 { u8 b[0x24]; };

struct Self_18EB98 {
    s32 state;
    u8 pad4[0x4C - 4];
    Blk_18EB98 f4C;
    s32 f70;
    s32 f74;
    u8 pad78[8];
    s32 f80;
};

s32 func_0013CAD8(void* queue, s32 n, void* sink);
void func_0011E4C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

struct Stream_18EAF8 {
    s32 mode;
    u8 pad0[0x2C - 4];
    u8 sub2C[0x10];
    s32 v3C;
    u8 pad1[0x4C - 0x40];
    u8 sub4C[0x10];
    s32 v5C;
};

struct Local_18EF78 { u8 bytes[0x30]; };

void* func_001611B8(void* b);
void func_001529C8(void* b, s32 a1, void* self);
void func_00152B38(void* b);
void func_001613C0(void* b, s32 a1, s32 a2, u64 a3);
void func_00161708(void* b, s32 a1, u64 a2);
void func_001614C8(void* b, s32 a1, s32 a2);
void func_001615F0(void* b, s32 a1, s32 a2, s32 a3, s32 a4);
void func_00161200(void* b);
void func_00152D30(void* b);
void func_001529E0(void* b, s32 a1, s32 a2);
void func_00161958(void* f, s32 a);
void func_00152B80(void* f, s32 a, s32 b);

struct Frame_18DB20 {
    Vec02 q00;
    Vec02 q10;
    Vec02 q20;
    Mat02 tbl30;
    Vec02 q60;
    u8 pad70[0xA0 - 0x70];
    Mat4A blkA0;
    u8 padE0[0xF0 - 0xE0];
    Mat4A blkF0;
};





void func_00125B70(void* obj, void* c, void* out);
void func_00188B08(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);
void func_00125C90(void* obj, void* s, void* out);

extern s32 D_00261F1C;

s32 func_001F6B60(s32 a);
void func_001686E8(s32 a, s32 b);
void func_001684E8(void);
void func_001683E8(void);

struct Obj_18F610 {
    u8 pad0[0x138];
    u32 crc;
    u8* cur;
    s32 remain;
};

extern u8 D_005A2E60[];

struct Obj_18F7D0 {
    s32 f00;
    u8 pad04[0x08];
    s32 f0C;
    u8 pad10[0x124];
    s32 f134;
};

extern s32 D_002626CC;

void func_0020B0C0(void* self);
s32 func_0020B048(void* self);
void func_001B3450(void);



extern const u32 D_002484B0[128];

struct Obj_18ECA8 { u8 pad0[0x60]; u8 sub[0x14]; s32 f74; };

void* func_001F5C0C(void* dst, s32 value, s32 size);
void func_0013CC48(void* queue, s32 n);

void func_0018D410(KeyId* p);
struct Same_18F198 {
    static s32 Of(IdentityKey* a, const IdentityKey* b)
    {
        if (a == b) return 1;
        if (!a) return 0;
        if (!b) return 0;
        return ((a->words[2] ^ a->words[6]) ^ (b->words[2] ^ b->words[6])) == 0;
    }
};
struct Fill_18F198 {
    static s32 Of(KeyId* p, IdentityKey* key)
    {
        ClearKeyId(p);
        s32 ok;
        if (!key) {
            ok = 0;
        } else {
            u32 t = key->words[1] ^ key->words[7];
            p->k1 = t;
            p->k0 = key->words[0] ^ key->words[5];
            ok = t != 0;
        }
        return ok;
    }
};
struct Self_18F198 {
    u32 mode;
    u8 pad[0xC];
    u8 list[1];
};

extern u8 D_002C3B00[];
extern u8 D_00275F80[];
extern s32 D_002613EC;

void func_00191E70(s32 v);
void* func_0012FCF0(StreamReader* o, u8* d);
s32 func_0012FD78(StreamReader* o, KeyId* k);
void func_0016EC20(PadRecord* d, s32 n);
void func_00143030(u8* t);
void func_0016E238(PadRecord* d);
s32 func_001F00F0(u8* a, PadRecord* b, s32 c);
void func_001409E0();
s32 func_0020B0B0(u8* l);
void func_0012FDE8(StreamReader* o);
void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00191EB0(s32 v);
void func_0012FD30(StreamReader* o, s32 f);

extern u8 D_002C2B00[];
extern u8 D_002832F0[];
extern s32 D_00275964;

struct Init_18E5E8 { s32 f00; void (*f04)(void); s32 f08; s32 f0C; s32 f10; s32 f14; u8 pad[0x18]; };
struct Mgr_18E5E8 { s32 f00; };

s32 func_001E2268(Init_18E5E8* a, void* b);
s32 func_001F6A10(Init_18E5E8* p);
void func_001F6A20(Mgr_18E5E8* m, s32 b);

s32 func_0011E4F8(void* self);

struct Frame_18EDA8 { u8 buf[0x30]; };

void func_00189350(void* a, void* b);
void func_001BC088(Collider* self, f32 x, void* b);

struct Object_18F890 { u8 pad00[0x0C]; StreamReaderWindow* buffer; u8 pad10[4]; };
struct Empty_18F890 {
    static bool Of(StreamReaderWindow* b) { return b->readyLength == b->usedLength; }
};
void func_00130070(StreamReaderWindow*);
s32 func_0020A518(void*, s32, s32);
void func_001300D8(StreamReaderWindow*, s32);

struct Obj_18F6E8 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1[0x5C - 0x1C];
    s32 f5C;
    u8 pad2[0x114 - 0x60];
    void* f114;
    void* f118;
    u8 pad3[0x130 - 0x11C];
    s32 f130;
    volatile s32 f134;  // state another thread changes: FinishMovie busy-waits on it
};

s32 func_0020B058(void* a, s32 b, s32 c);
void func_001F6B40(s32 a);

struct Obj_18F448 {
    u8 pad0[0xC];
    void* fC;
    u8 pad1[0x48];
    void* f58;
    void* f5C;
    u8 pad2[0xB4];
    void* f114;
    void* f118;
};

extern u8 D_002D7B40[];
extern u8 D_0045AAC0[];
extern u8 D_0042AAC0[];
extern u8 D_00586AC0[];
extern u8 D_005A2D40[];
extern u8 D_00148D68[];

void func_0020ADA0(void);
s32 func_0020AE40(void* self, void* a, s32 b);
s32 func_0020A538(void* self, s32 a, s32 b, void* fn, void* arg);
s32 func_0020B168(void* self, s32 a, void* fn, void* arg);

s32 func_0018E410(IdentityKey* key);
u8* func_0018E480(s32 index);
void func_0018E4C0(s32 idx);
void func_0018E4F0(s32 idx, u32 n);
void func_0018E558(void);
void func_0018E5E8(void);
void func_0018E678(IopRingSink* self, s32 a1, s32 a2);
void func_0018E6A0(IopRingSink* c);
s32 func_0018E7C0(IopRingSink* p, s32 size, u8* buf);
void func_0018E838(IopRingSink* self);
s32 func_0018E940(MovieStream* self);
void func_0018EA48(Obj_18EA48* self);
void func_0018EAA0(Obj_18EAA0* self);
s32 func_0018EAF8(Stream_18EAF8* self, s32 left, u8* right);
void func_0018EB98(Self_18EB98* self);
s32 func_0018EC40(void* a0, void* a1, void* a2);
void func_0018EC80(void* a0, Args_18EC80* a1, void* a2);
s32 func_0018ECA8(void* u0, void* u1, Obj_18ECA8* self);
s32 func_0018ED78(void* a0, s32 a1, void* a2);
s32 func_0018EDA0(void);
void func_0018EDA8(void* p, s32 addr, s32 w, s32 h);
void func_0018EF78(void* self, s32 a1, s32 a2);
void func_0018F0E8(void* self, void* p);
void func_0018F148(Obj_18F148* self);
void func_0018F198(Self_18F198* self, IdentityKey* key);
void func_0018F448(Obj_18F448* self, void* v);
void func_0018F610(Obj_18F610* self);
void func_0018F6E8(Obj_18F6E8* self);
void func_0018F7D0(Obj_18F7D0* self);
s32 func_0018F890(Object_18F890* self, s32 wait);

void func_0018D8E0(ContactListObject* self)
{
    InitChildGroupObject(self);
    self->ready = 1;
}

void func_0018D910(ContactListObject* self)
{
    u64 mask = (u64)(s64)-0x301;
    u64 set = 0x8000;
    LoadChildGroupObject(self);
    ResolveObjectLinks(self, 1, g_contactListObjectLinks);
    mask <<= 16;
    mask |= 0xFFFF;
    mask <<= 16;
    mask |= 0xFFFF;
    set <<= 25;
    self->flags = (self->flags & mask) | set;
}

void func_0018D978(ContactListObject* self)
{
    UnregisterCollider(self);
    void* p = self->f6B4;
    if (p != 0) {
        StopAnimationPlayer(p);
        self->f6B4 = 0;
    }
}

void func_0018D9B8(ContactListObject* self, void* b, f32 x)
{
    if (self->ready != 0) {
        BuildBasisFromX(&self->v150, &self->rot);
    }
    s32 s1 = (s32)self->f1EC;
    s32 s0 = (s32)self->f1F0;
    self->f1EC = 0;
    self->f1F0 = 0;
    func_001BC088(self, x, b);
    self->f1EC = (Attachment*)s1;
    self->f1F0 = (Attachment*)s0;
}

ASM_FUNC(func_0018DA40);

void func_0018DB20(ContactListObject* self, void* in1, void* in2)
{
    Frame_18DB20 f;

    if ((self->flags & 0x100000000ULL) == 0) {
        if (self->f1EC == 0 && self->f1F0 == 0) {
            func_00125C90(self, in1, in2);
        } else {
            if (self->f1EC != 0) {
                self->f1EC->vt->getPos(self->f1EC, 0.0f, &f.q00, &f.q10);
            } else {
                f.q00 = D_00248D30;
            }
            if (self->f1F0 != 0) {
                self->f1F0->vt->getRot(self->f1F0, 0.0f, &f.tbl30, &f.q20);

            } else {
                f.tbl30 = g_identityMatrix;
            }
            BuildPlacedObjectTransform(self, in2, &f.blkA0);
            BuildMatrixFromRotationAndTranslation(&f, &f.tbl30, &f.q60);
            MultiplyMatrices(&f.blkF0, &f.blkA0, &f.q60);
            f.blkA0 = f.blkF0;
            func_00125C90(self, in1, &f.blkA0);
        }
    }
}

s32 func_0018DC88(ContactListObject* self, void* key)
{
    if (key == self->f6E4) {
        return 1;
    }
    for (s32 i = 0; i < self->count6BC; i++) {
        if (MatchesObjectId(key, self->items6C0[i]) != 0) {
            return 1;
        }
    }
    for (s32 j = 0; j < self->count6D0; j++) {
        if (IsObjectOfKind(key, self->items6D4[j]) != 0) {
            return 1;
        }
    }
    return TestCollidersMayContact(self, key);
}

void func_0018DD50(ContactListObject* self, void* item)
{
    u32 n = self->count6BC;
    if (n < 4) {
        self->items6C0[n] = item;
        self->count6BC = n + 1;
    }
}

void func_0018DD78(ContactListObject* self, s32 value)
{
    s32 n = self->count6D0;
    if ((u32)n < 4) {
        self->items6D4[n] = (void*)value;
        self->count6D0 = n + 1;
    }
}

void func_0018DDA0(ContactListObject* self)
{
    InitContactListObject(self);
    self->gravity = D_00248D30;
}

ASM_FUNC(func_0018DDD8);

ASM_FUNC(func_0018DE70);

ASM_FUNC(func_0018DEE8);

ASM_FUNC(func_0018E040);

s32 func_0018E410(IdentityKey* key)
{
    IdentityKey* p = (IdentityKey*)(u8*)g_movieKeys;
    s32 i = 0;
    s32 m;

    do {
        if (p == key) {
            m = 1;
        } else if (p == 0 || key == 0) {
            m = 0;
        } else {
            m = ((p->signedWords[2] ^ p->signedWords[6]) ^ (key->signedWords[2] ^ key->signedWords[6])) == 0;
        }
        if (!m) {
            i++;
            p++;
        } else {
            return i;
        }
    } while (i < 16);
    return -1;
}

u8* func_0018E480(s32 index)
{
    if ((u32)index < 16) {
        return (u8*)g_movieTitles[index];
    }
    if (index == -1) {
        return (u8*)"Nil";
    }
    return (u8*)"(unknown)";
}

void func_0018E4C0(s32 idx)
{
    QueueMovie(&g_moviePlayer, (u8*)g_movieKeys + (idx << 5));
}

void func_0018E4F0(s32 idx, u32 n)
{
    GameProgress* dev;
    s32 m;

    QueueMovieByIndex(idx);
    g_moviePlayer.f08 = (void*)((u8*)g_movieKeys + (n << 5));
    if (n >= 16) { m = 0; } else { m = 1 << n; }
    dev = g_saveData;
    dev->u19F4 |= m;
}

void func_0018E558(void)
{
    MoviePlayer* t = &g_moviePlayer;

    for (;;) {
        t->f134 = 0;
        AwaitSemaphore(t->f130);
        t->f134 = 1;
        SendGsPacketAndWait(g_gifChannel, (s32)t->f114);
        t->f134 = 2;
        ApplyPendingDisplayFlip();
        SendGsPacketAndWait(g_gifChannel, (s32)t->f118);
        FlipDisplayFrame();
        SendGsPacketAndWait(g_gifChannel, (s32)t->f118);
        FlipDisplayFrame();
    }
}

void func_0018E5E8(void)
{
    Init_18E5E8 l;
    s32 v;

    g_moviePlayer.f130 = CreateLockSemaphore((Init_18E5E8*)0, (void*)1);
    g_moviePlayer.f0C = 0;
    (void)FillMemory(&l, 0, sizeof(l));
    l.f04 = RunMovieDecodeThread;
    l.f08 = (s32)g_movieDecodeThreadStack;
    l.f10 = (s32)D_002832F0;
    l.f0C = 0x1000;
    l.f14 = 2;
    v = MakeThread(&l);
    g_movieDecodeThread = v;
    RunThread((Mgr_18E5E8*)v, 0);
}

void func_0018E678(IopRingSink* self, s32 a1, s32 a2)
{
    self->f04 = a2;
    self->f08 = a1;
    ResetIopRingSink(self);
}

void func_0018E6A0(IopRingSink* c)
{
    c->f14 = c->f08;
    c->f18 = 0;
    c->f10 = 0;
    c->f0C = 0;
    c->f1C = 0;
}

s32 IopRingSink::Put(s32 count, u8* dst)
{
    s32 n = count;
    s32 total = 0;
    s32 left = n;
    s32 r;

    if (left <= 0 || f14 < left) {
        left = f14;
    }
    left &= -0x400;
    while (left != 0) {
        s32 avail = f08 - f0C;
        r = WriteIopRingBlock(this, left < avail ? left : avail, dst + total);
        if (r == 0) {
            break;
        }
        total += r;
        left -= r;
        f0C += r;
        f0C = f0C % f08;
        f18 += r;
        f14 -= r;
        f1C += r;
        if (n <= 0) {
            break;
        }
    }
    return total;
}

s32 func_0018E7C0(IopRingSink* p, s32 size, u8* buf)
{
    Span_18E7C0 span;
    void* obj;

    span.a = (s32)buf;
    span.b = p->f04 + p->f0C;
    span.c = (void*)size;
    span.d = 0;
    SyncDataCache(0);
    obj = StartIopDma(&span, 1);
    while (GetIopDmaStatus(obj) >= 0) {
    }
    return size;
}

void func_0018E838(IopRingSink* self) { s32 raw = GetIopRingPosition(self); s32 x = (raw & 0xFFFFFF) - self->f04; x = x - self->f0C; x = x - 0x400; x = x + self->f08; self->f14 = x; self->f14 = x % self->f08; s32 d = self->f08 - self->f14; self->f18 = d; s32 y = self->f0C - d; y += self->f08; self->f10 = y; self->f10 = y % self->f08; }

s32 IopRingSink::Idle()
{
    return 0;
}

s32 IpuDmaSink::Put(s32 size, u8* buf)
{
    s32 n = size & 0xFFFFFFF0;
    if (n > 0x1000) n = 0x1000;
    u32 old = *(volatile u32*)0x1000F590;
    *(volatile u32*)0x1000F590 = 0x10000;
    *(volatile u32*)0x1000B420 = (u32)n >> 4;
    u32 addr = (u32)buf & 0x0FFFFFFF;
    *(volatile u32*)0x1000B410 = addr;
    *(volatile u32*)0x1000B400 = 0x101;
    *(volatile u32*)0x1000F590 = old;
    return n;
}

s32 IpuDmaSink::Idle()
{
    return 1;
}

// Declared to return a value it never sets: func_0018F448, its caller, is retail's only with a
// callee that returns one.
s32 func_0018E940(MovieStream* self)
{
    s32 r;
    SuspendIopVoices(0xFFFFFFFF);
    PushIopChannel2Setting(g_currentWorld, 0, 0);
    StopAllIopSounds();
    while (PollIopCommands() != 0) {
    }
    func_0011E110(1);
    SyncDiscRead(0);
    self->f8C = GetIopVolumeChannel(2);
    self->f90 = GetIopVolumeChannel(8);
    SetIopVolumeChannel(2, 0x400);
    SetIopVolumeChannel(8, 0x200);
    r = OpenIopRing(0x6000, 0x400, 0, 2, 2);
    if (r < 0) {
        self->f00 = 0;
    } else {
        self->f00 = 1;
        InitRingBuffer(self->sub2C, 0x28, &self->f04);
        InitRingBuffer(self->sub4C, 0xC000, D_002CBB40);
        InitIopRingSink(&self->sub6C, 0x6000, r);
    }
}

void func_0018EA48(Obj_18EA48* self)
{
    if (self->flag != 0) {
        ResetIopRing();
        self->flag = 1;
        ResetRingBuffer((u8*)self + 0x2C);
        ResetRingBuffer((u8*)self + 0x4C);
        ResetIopRingSink((IopRingSink*)((u8*)self + 0x6C));
    }
}

void func_0018EAA0(Obj_18EAA0* self)
{
    self->f00 = 0;
    StopIopMovieStream();
    SetIopVolumeChannel(2, self->f8C);
    SetIopVolumeChannel(8, self->f90);
    PopIopChannel2Setting(g_currentWorld);
    ResumeIopVoices(0xFFFFFFFF);
}

s32 func_0018EAF8(Stream_18EAF8* self, s32 left, u8* right)
{
    s32 n;

    if (self->mode == 0) {
        goto zero;
    }
    left -= 4;
    right += 4;
    if (self->mode == 1) {
        n = FillRingBufferFromMemory(self->sub2C, left, right);
        left -= n;
        right += n;
        if (self->v3C > 0) {
            goto one;
        }
        self->mode = 2;
    }
    if (self->v5C >= left) {
        goto call;
    }
zero:
    return 0;
call:
    FillRingBufferFromMemory(self->sub4C, left, right);
one:
    return 1;
}

void func_0018EB98(Self_18EB98* self)
{
    switch (self->state) {
    case 2:
        DrainRingBuffer(&self->f4C, self->f80, (u8*)&self->f4C + 0x20);
        if (self->f80 != 0) {
            break;
        }
        UpdateIopMovieStream(self->f70, self->f74, self->f70, 0, 0);
        self->state = 3;
        break;
    case 3: {
        void* s0 = (u8*)&self->f4C + 0x20;
        UpdateIopRingSink((IopRingSink*)s0);
        DrainRingBuffer(&self->f4C, self->f80, s0);
        break;
    }
    }
}

s32 func_0018EC40(void* a0, void* a1, void* a2)
{
    if (*(u32*)((u8*)a2 + 0x70) >= *(u32*)((u8*)a1 + 0xC)) {
        FillRingBufferFromMemory((u8*)a2 + 0x60, *(u32*)((u8*)a1 + 0xC), *(void**)((u8*)a1 + 0x8));
        return 1;
    }
    return 0;
}

void func_0018EC80(void* a0, Args_18EC80* a1, void* a2)
{
    FeedMovieStream((Stream_18EAF8*)((u8*)a2 + 0x80), a1->fC, a1->f8);
}

s32 func_0018ECA8(void* u0, void* u1, Obj_18ECA8* self)
{
    s32 total = 0x40;
    while (self->f74 < 0x1000) {
        if (FeedMovieDecoder((Object_18F890*)self, 1) == 0) {
            u8 zero[0x40];
            FillMemory(zero, 0, 0x40);
            s32 k = self->f74;
            FillRingBufferFromMemory(&self->sub, total - (k % 32), zero);
            break;
        }
    }
    {
        IpuDmaSink dma;
        ConsumeSpan(&self->sub, 0);
        DrainRingBuffer(&self->sub, 0, &dma);
    }
    return 1;
}

s32 func_0018ED78(void* a0, s32 a1, void* a2)
{
    FeedMovieDecoder((Object_18F890*)a2, 0);
    return 1;
}

s32 func_0018EDA0(void)
{
    return 1;
}

void func_0018EDA8(void* p, s32 addr, s32 w, s32 h)
{
    s32 ny = w / 16;
    s32 nx = h / 16;
    s32 x;
    s32 y;
    Frame_18EDA8 f;

    InitGifPacket(&f);
    UsePacketBufferMemory(&f, 0x1C28, p);
    BeginDmaTag(&f);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x50, (u64)0xA1E0 << 36);
    AddGifRegisterWrite(&f, 0x52, ((u64)0x10 << 32) | 0x10);
    for (y = 0; y < ny; y++) {
        for (x = 0; x < nx; x++) {
            BeginGifTag(&f, 0, 1, 0xE);
            AddGifRegisterWrite(&f, 0x51, ((u64)(y << 4) << 32) | ((u64)(x << 4) << 48));
            AddGifRegisterWrite(&f, 0x53, 0);
            AddGifImageTag(&f, 0x40);
            AddDmaRefTag(&f, 0x40, addr & 0xFFFFFFF);
            addr += 0x400;
        }
    }
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x3F, 0);
    AddGifRegisterWrite(&f, 0x61, 0);
    EndGifPacket(&f);
    AddDmaEndTag(&f);
    DetachPacketBuffer(&f, 0, 0);
}

void func_0018EF78(void* self, s32 a1, s32 a2)
{
    Local_18EF78 buf;
    InitGifPacket(&buf);
    UsePacketBufferMemory(&buf, 0x12, self);
    BeginDmaTag(&buf);
    BeginGifTag(&buf, 6, 1, 0xE);
    AddGifRegisterWrite(&buf, 6, 0x0AA8029E00ULL);
    AddGifRegisterWrite(&buf, 0x14, 0x61);
    AddGifRegisterWrite(&buf, 8, 5);
    AddGifRegisterWrite(&buf, 0x42, 0x44);
    AddGifRegisterWrite(&buf, 0x47, 0x31001);
    BeginGifTag(&buf, 0x116, 5, 0xE4343);
    AddGifUvEntry(&buf, 8, 8);
    AddGifXyzfEntry(&buf, 0x6C00, 0x7900, 0, 0);
    AddGifUvEntry(&buf, (a1 << 4) | 8, (a2 << 4) | 8);
    AddGifXyzfEntry(&buf, 0x9400, 0x8700, 0, 0);
    AddGifRegisterWrite(&buf, 0x61, 0);
    EndGifPacket(&buf);
    AddDmaEndTag(&buf);
    DetachPacketBuffer(&buf, 0, 0);
}

void func_0018F0E8(void* self, void* p)
{
    s32 m;
    s32 v;

    if (*(void**)((u8*)self + 4) != 0) {
        return;
    }
    *(void**)((u8*)self + 4) = p;
    v = FindKeyIndex((IdentityKey*)p);
    if ((u32)v >= 16) {
        m = 0;
    } else {
        m = 1 << v;
    }
    g_saveData->u19F4 |= m;
}

void func_0018F148(Obj_18F148* self)
{
    s32 pending = self->f08;
    s32 first = self->f04;
    self->f04 = 0;
    self->f08 = 0;
    PlayMovie((Self_18F198*)self, (IdentityKey*)first);
    if (pending != 0) {
        PlayMovie((Self_18F198*)self, (IdentityKey*)pending);
    }
}

void func_0018F198(Self_18F198* self, IdentityKey* key)
{
    StreamReader loc;
    KeyId pr;
    SetScreenOwner(4);
    self->mode = FindKeyIndex(key);
    InitStreamReader(&loc, D_002C3B00);
    if (Fill_18F198::Of(&pr, key) && OpenSectorStreamRange(&loc, &pr)) {
        InitMoviePlayback((Obj_18F448*)self, &loc);
        while (!GetMpegDecoderStatus(self->list)) {
            AdvanceGameClockElapsed(((u8*)g_gameClock));
            UpdatePadConnection(&g_padRecord);
            s32 flag = 0;
            if (Same_18F198::Of(key, &D_00248490)) flag = g_keyedMovieWatched != 0;
            u32 m;
            if (self->mode >= 16) m = 0;
            else m = 1u << self->mode;
            if (g_saveData->f19F8 & m) flag = 1;
            if (flag) {
                if (RestoreFadeRequest(g_screenFade, &g_padRecord, 2)) break;
                if (g_padRecord.flags & 0x91F) {
                    ClearPadPressedBits(&g_padRecord, 0x91F);
                    break;
                }
            }
            StepDiscSectorCheck();
            if (g_discSectorCheckState != 3) break;
            StepMovieFrame((Obj_18F6E8*)self);
        }
        if (Same_18F198::Of(key, &D_00248490)) g_keyedMovieWatched = 1;
        FinishMovie((Obj_18F7D0*)self);
        CloseStreamReader(&loc);
    } else {
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    ClearScreenOwner(4);
    DestroyStreamReader(&loc, 2);
}

void func_0018F448(Obj_18F448* self, void* v)
{
    s32 i;

    self->fC = v;
    self->f58 = D_002D7B40;
    self->f5C = D_0045AAC0;
    InitRingBuffer((u8*)self + 0x60, 0x30000, (void*)((s32)D_0042AAC0 | 0x20000000));
    StartMovieStream((MovieStream*)((u8*)self + 0x80));
    InitMpegLibrary();
    CreateMpegDecoder((u8*)self + 0x10, self->f58, 0x152F68);
    SetStreamCallback((u8*)self + 0x10, 0, 0, (void*)AcceptMovieDataIntoRing, self);
    SetStreamCallback((u8*)self + 0x10, 2, 0, (void*)PassMovieDataToStream, self);
    SetMpegCallback((u8*)self + 0x10, 1, (void*)FlushMovieToIpu, self);
    SetMpegCallback((u8*)self + 0x10, 4, (void*)FeedMovieDecoderWithoutWaiting, self);
    SetMpegCallback((u8*)self + 0x10, 0, (void*)AcceptMovieDecoderEvent, self);
    while (FeedMovieDecoder((Object_18F890*)self, 1) != 0) {
    }
    self->f114 = D_00586AC0;
    self->f118 = D_005A2D40;
    D_002626CC = 0;
    g_moviePlayer.cur = (u8*)0x100010;
    g_moviePlayer.remain = (s32)D_00148D68;
    g_moviePlayer.crc = 0xFFFFFFFF;
    u8* tb = D_005A2E60;
    i = 0;
    s32 j;
    do {
        u32 c = i;
        s32 k;
        s32 off = c * 4;
        j = c + 1;
        for (k = 7; k >= 0; k--) {
            if (c & 1) c = (c >> 1) ^ 0xEDB88320; else c = c >> 1;
        }
        *(u32*)(tb + off) = c;
        i = j;
    } while (j < 256);
}

void func_0018F610(Obj_18F610* self)
{
    if (self->remain > 0) {
        s32 n = self->remain - 4;
        u32* tab = (u32*)D_005A2E60;
        u8* p = self->cur;
        u8* nxt = p + 4;
        u32 c0 = self->crc;
        u32 c1, c2, c3;

        c1 = tab[(c0 ^ p[0]) & 0xff] ^ (c0 >> 8);
        self->crc = c1;
        c2 = tab[(c1 ^ p[1]) & 0xff] ^ (c1 >> 8);
        self->crc = c2;
        self->remain = n;
        c3 = tab[(c2 ^ p[2]) & 0xff] ^ (c2 >> 8);
        self->crc = c3;
        u32 t = tab[(c3 ^ p[3]) & 0xff];
        self->cur = nxt;
        u32 c = t ^ (c3 >> 8);
        self->crc = c;
        if (n == 0 && c != 0) {
            g_movieChecksumFailed = 1;
        }
    }
}

void func_0018F6E8(Obj_18F6E8* self)
{
    void* s1;
    if (self->f134 == 1) {
        do {
            (void)FeedMovieDecoder((Object_18F890*)self, 0);
        } while (self->f134 == 1);
    }
    if (DecodeMpegPicture((u8*)self + 0x10, self->f5C, 0x4B0) < 0) {
        return;
    }
    if (self->f18 == 0) {
        UploadMovieFrame(self->f114, self->f5C, self->f10, self->f14);
        DrawMovieFrame(self->f118, self->f10, self->f14);
        SyncDataCache(0);
    }
    s1 = (u8*)self + 0x80;
    if (self->f134 != 0) {
        do {
            (void)FeedMovieDecoder((Object_18F890*)self, 0);
            AdvanceCodeChecksum((Obj_18F610*)self);
        } while (self->f134 != 0);
    }
    PostSemaphore(self->f130);
    UpdateMovieStream((Self_18EB98*)s1);
}

void func_0018F7D0(Obj_18F7D0* self)
{
    u8* base = (u8*)self;
    s32 mask;

    self->f0C = 0;
    ResetMovieStream((Obj_18EA48*)(base + 0x80));
    StopMovieStream((Obj_18EAA0*)(base + 0x80));
    ResetMpegDecoder(base + 0x10);
    (void)DeleteMpegDecoder(base + 0x10);
    if (self->f134 != 0) {
        do {
        } while (*(volatile s32*)&self->f134 != 0);
    }
    D_002626CC = 3;
    SendResidentImages();
    if ((u32)self->f00 >= 16) {
        mask = 0;
    } else {
        mask = 1 << self->f00;
    }
    g_saveData->f19F8 |= mask;
}

s32 func_0018F890(Object_18F890* self, s32 wait)
{
    while (Empty_18F890::Of(self->buffer)) {
        PumpStreamReader(self->buffer);
        if (Empty_18F890::Of(self->buffer) && !wait) return 0;
    }
    SyncDataCache(0);
    StreamReaderWindow* buffer = self->buffer;
    s32 count = buffer->readyLength - buffer->usedLength;
    s32 result = DemultiplexBuffer(self->pad10, buffer->readyStart + buffer->usedLength, count);
    ConsumeStreamBytes(self->buffer, result);
    return result;
}

LINKER_REMNANT(func_0018F938);
