// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "c3b.h"

// The movie player: its object (D_00269A00), the stream its data comes through, and the two
// sinks a transfer goes to (a ring buffer, and the IPU's DMA channel).

// Where a transfer's data goes: two virtual methods, which retail's vtables list in this order.
class Sink_18E6C0 {
public:
    virtual s32 Put(s32 size, u8* buf) = 0;
    virtual s32 Idle() = 0;
};

// A ring buffer in the IOP's memory, read through the SIF.
class Ring_18E6C0 : public Sink_18E6C0 {
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
class Dma_18E8C8 : public Sink_18E6C0 {
public:
    s32 Put(s32 size, u8* buf);
    s32 Idle();
};

// The stream the movie's data comes through (func_0018E940 opens it).
struct Obj_18E940 {
    s32 f00;
    s32 f04;
    u8 pad08[0x24];
    u8 sub2C[0x20];
    u8 sub4C[0x20];
    Ring_18E6C0 sub6C;
    s32 f8C;
    s32 f90;
};

struct Movie_269A00 {
    s32 mode;
    void* f04;
    void* f08;
    void* f0C;
    u8 decoder[0x48];
    void* f58;
    void* f5C;
    u8 queue60[0x20];
    Obj_18E940 stream;
    void* f114;
    void* f118;
    u8 pad11C[0x14];
    s32 f130;
    s32 f134;
    u32 crc;
    u8* cur;
    s32 remain;
    u8 pad144[4];  // to the label after it, D_00269B48
};

struct Ent_2699B0 { s32 a; s32 b; s32 c; };

Ent_2699B0 D_002699B0 = { 2, 0x317, 0x6B0 };
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
Movie_269A00 D_00269A00;
s32 D_00269B48;
s32 D_00269B4C;

extern u8 D_00261858[];
extern u8* D_002623C0;




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

extern u8* D_00275710;
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

struct __attribute__((aligned(16))) Quad_18DB20 { s32 a, b, c, d; };
struct __attribute__((aligned(16))) Tbl3_18DB20 { Quad_18DB20 q[3]; };
struct __attribute__((aligned(16))) Blk4_18DB20 { Quad_18DB20 q[4]; };

struct Frame_18DB20 {
    Quad_18DB20 q00;
    Quad_18DB20 q10;
    Quad_18DB20 q20;
    Tbl3_18DB20 tbl30;
    Quad_18DB20 q60;
    u8 pad70[0xA0 - 0x70];
    Blk4_18DB20 blkA0;
    u8 padE0[0xF0 - 0xE0];
    Blk4_18DB20 blkF0;
};

typedef void (*VFn_18DB20)(void* self, f32 f, void* a, void* b);
struct Obj_18DB20 { VFn_18DB20* vtbl; };


extern u8 D_00248D30[];
extern u8 D_002483D0[];

void func_00125B70(void* obj, void* c, void* out);
void func_00188B08(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);
void func_00125C90(void* obj, void* s, void* out);

extern s32 D_00261F1C;

void func_001F6B60(s32 a);
void func_001686E8(s32 a, s32 b);
void func_001684E8(void);
void func_001683E8(void);

struct Task_18E558 {
    u8 pad0[0x114];
    s32 f114;
    s32 f118;
    u8 pad1[0x14];
    s32 f130;
    volatile s32 f134;
};

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


struct Ent_18E410 {
    u8 pad0[8];
    s32 k0;
    u8 pad1[0xC];
    s32 k1;
    u8 pad2[4];
};

extern const u32 D_002484B0[128];

struct Dev_18E4F0 { u8 pad0[0x19F4]; s32 w19F4; };

struct Obj_18ECA8 { u8 pad0[0x60]; u8 sub[0x14]; s32 f74; };

void* func_001F5C0C(void* dst, s32 value, s32 size);
void func_0013CC48(void* queue, s32 n);

struct Key_18F198 {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
    u32 w4;
    u32 w5;
    u32 w6;
    u32 w7;
    s32 Same(Key_18F198* b)
    {
        Key_18F198* a = this;
        if (a == b) return 1;
        if (!a) return 0;
        if (!b) return 0;
        return ((a->w2 ^ a->w6) ^ (b->w2 ^ b->w6)) == 0;
    }
};
struct Dev_18F198 {
    u8 pad[0xAA];
    u16 bits;
};
struct Tbl_18F198 {
    u8 pad[0x19F8];
    u32 mask;
};
struct Loc_18F198 {
    u8 body[0x30];
};
struct Pair_18F198;
void func_0018D410(Pair_18F198* p);
struct Pair_18F198 {
    u32 k[2];
    s32 Set(Key_18F198* key)
    {
        func_0018D410(this);
        s32 ok;
        if (!key) {
            ok = 0;
        } else {
            u32 t = key->w1 ^ key->w7;
            k[1] = t;
            k[0] = key->w0 ^ key->w5;
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

extern const Key_18F198 D_00248490;
extern u8 D_002C3B00[];
extern Dev_18F198 D_00262C70;
extern u8 D_00275F80[];
extern s32 D_002613EC;

void func_00191E70(s32 v);
void func_0012FCF0(Loc_18F198* o, u8* d);
s32 func_0012FD78(Loc_18F198* o, Pair_18F198* k);
void func_0016EC20(Dev_18F198* d, s32 n);
void func_00143030(u8* t);
void func_0016E238(Dev_18F198* d);
s32 func_001F00F0(u8* a, Dev_18F198* b, s32 c);
void func_001409E0();
s32 func_0020B0B0(u8* l);
void func_0012FDE8(Loc_18F198* o);
void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00191EB0(s32 v);
void func_0012FD30(Loc_18F198* o, s32 f);

extern u8 D_002C2B00[];
extern u8 D_002832F0[];
extern s32 D_00275964;

struct Glob_18E5E8 { u8 pad0[0xC]; s32 f0C; u8 pad1[0x120]; s32 f130; };
struct Init_18E5E8 { s32 f00; void (*f04)(void); s32 f08; s32 f0C; s32 f10; s32 f14; u8 pad[0x18]; };
struct Mgr_18E5E8 { s32 f00; };

s32 func_001E2268(Init_18E5E8* a, void* b);
s32 func_001F6A10(Init_18E5E8* p);
void func_001F6A20(Mgr_18E5E8* m, s32 b);

s32 func_0011E4F8(void* self);

struct Frame_18EDA8 { u8 buf[0x30]; };

void func_00189350(void* a, void* b);
s32 func_001BC088(C03* self, f32 x, void* b);

struct Buffer_18F890 { u8 pad00[0x18]; s32 head; s32 base; s32 tail; };
struct Object_18F890 { u8 pad00[0x0C]; Buffer_18F890* buffer; u8 pad10[4]; };
struct Empty_18F890 {
    static bool Of(Buffer_18F890* b) { return b->head == b->tail; }
};
void func_00130070(Buffer_18F890*);
s32 func_0020A518(void*, s32, s32);
void func_001300D8(Buffer_18F890*, s32);

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
    volatile s32 f134;  // state another thread changes: func_0018F7D0 busy-waits on it
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
void func_0020AE40(void* self, void* a, s32 b);
void func_0020A538(void* self, s32 a, s32 b, void* fn, void* arg);
void func_0020B168(void* self, s32 a, void* fn, void* arg);

s32 func_0018E410(Ent_18E410* key);
u8* func_0018E480(s32 index);
void func_0018E4C0(s32 idx);
void func_0018E4F0(s32 idx, u32 n);
void func_0018E558(void);
void func_0018E5E8(void);
void func_0018E678(Ring_18E6C0* self, s32 a1, s32 a2);
void func_0018E6A0(Ring_18E6C0* c);
s32 func_0018E7C0(Ring_18E6C0* p, s32 size, u8* buf);
void func_0018E838(Ring_18E6C0* self);
s32 func_0018E940(Obj_18E940* self);
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
void func_0018F198(Self_18F198* self, Key_18F198* key);
void func_0018F448(Obj_18F448* self, void* v);
void func_0018F610(Obj_18F610* self);
void func_0018F6E8(Obj_18F6E8* self);
void func_0018F7D0(Obj_18F7D0* self);
s32 func_0018F890(Object_18F890* self, s32 wait);

void func_0018D8E0(C3C* self)
{
    func_0013B4C0(self);
    self->ready = 1;
}

void func_0018D910(C3C* self)
{
    u64 mask = (u64)(s64)-0x301;
    u64 set = 0x8000;
    func_0013B598(self);
    func_00124DF8(self, 1, &D_002699B0);
    mask <<= 16;
    mask |= 0xFFFF;
    mask <<= 16;
    mask |= 0xFFFF;
    set <<= 25;
    self->flags = (self->flags & mask) | set;
}

void func_0018D978(C3C* self)
{
    func_001B7B78(self);
    void* p = self->f6B4;
    if (p != 0) {
        func_0012E760(p);
        self->f6B4 = 0;
    }
}

void func_0018D9B8(C3C* self, void* b, f32 x)
{
    if (self->ready != 0) {
        func_00189350(&self->v150, &self->rot);
    }
    s32 s1 = (s32)self->f1EC;
    s32 s0 = (s32)self->f1F0;
    self->f1EC = 0;
    self->f1F0 = 0;
    func_001BC088(self, x, b);
    self->f1EC = (T2195*)s1;
    self->f1F0 = (T2195*)s0;
}

ASM_FUNC(func_0018DA40);

void func_0018DB20(C3C* self, void* in1, void* in2)
{
    Frame_18DB20 f;

    if ((self->flags & 0x100000000ULL) == 0) {
        if (self->f1EC == 0 && self->f1F0 == 0) {
            func_00125C90(self, in1, in2);
        } else {
            if (self->f1EC != 0) {
                ((Obj_18DB20*)self->f1EC)->vtbl[4](self->f1EC, 0.0f, &f, &f.q10);
            } else {
                f.q00 = *(Quad_18DB20*)D_00248D30;
            }
            if (self->f1F0 != 0) {
                ((Obj_18DB20*)self->f1F0)->vtbl[5](self->f1F0, 0.0f, &f.tbl30, &f.q20);
            } else {
                f.tbl30 = *(Tbl3_18DB20*)D_002483D0;
            }
            func_00125B70(self, in2, &f.blkA0);
            func_00188B08(&f, &f.tbl30, &f.q60);
            func_00188668(&f.blkF0, &f.blkA0, &f.q60);
            f.blkA0 = f.blkF0;
            func_00125C90(self, in1, &f.blkA0);
        }
    }
}

s32 func_0018DC88(C3C* self, void* key)
{
    if (key == self->f6E4) {
        return 1;
    }
    for (s32 i = 0; i < self->count6BC; i++) {
        if (func_001833F0(key, self->items6C0[i]) != 0) {
            return 1;
        }
    }
    for (s32 j = 0; j < self->count6D0; j++) {
        if (func_001300E8(key, self->items6D4[j]) != 0) {
            return 1;
        }
    }
    return func_001B8A08(self, key);
}

void func_0018DD50(C3C* self, void* item)
{
    u32 n = self->count6BC;
    if (n < 4) {
        self->items6C0[n] = item;
        self->count6BC = n + 1;
    }
}

void func_0018DD78(C3C* self, s32 value)
{
    s32 n = self->count6D0;
    if ((u32)n < 4) {
        self->items6D4[n] = (void*)value;
        self->count6D0 = n + 1;
    }
}

void func_0018DDA0(C3C* self)
{
    func_0018D8E0(self);
    self->gravity = *(Vec02*)D_00248D30;
}

ASM_FUNC(func_0018DDD8);

ASM_FUNC(func_0018DE70);

ASM_FUNC(func_0018DEE8);

ASM_FUNC(func_0018E040);

s32 func_0018E410(Ent_18E410* key)
{
    Ent_18E410* p = (Ent_18E410*)(u8*)D_002484B0;
    s32 i = 0;
    s32 m;

    do {
        if (p == key) {
            m = 1;
        } else if (p == 0 || key == 0) {
            m = 0;
        } else {
            m = ((p->k0 ^ p->k1) ^ (key->k0 ^ key->k1)) == 0;
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
        return (u8*)D_002699C0[index];
    }
    if (index == -1) {
        return (u8*)"Nil";
    }
    return (u8*)"(unknown)";
}

void func_0018E4C0(s32 idx)
{
    func_0018F0E8(&D_00269A00, (u8*)D_002484B0 + (idx << 5));
}

void func_0018E4F0(s32 idx, u32 n)
{
    Dev_18E4F0* dev;
    s32 m;

    func_0018E4C0(idx);
    D_00269A00.f08 = (void*)((u8*)D_002484B0 + (n << 5));
    if (n >= 16) { m = 0; } else { m = 1 << n; }
    dev = (Dev_18E4F0*)D_002623C0;
    dev->w19F4 |= m;
}

void func_0018E558(void)
{
    Task_18E558* t = (Task_18E558*)&D_00269A00;

    for (;;) {
        t->f134 = 0;
        func_001F6B60(t->f130);
        t->f134 = 1;
        func_001686E8(D_00261F1C, t->f114);
        t->f134 = 2;
        func_001684E8();
        func_001686E8(D_00261F1C, t->f118);
        func_001683E8();
        func_001686E8(D_00261F1C, t->f118);
        func_001683E8();
    }
}

void func_0018E5E8(void)
{
    Init_18E5E8 l;
    s32 v;

    ((Glob_18E5E8*)&D_00269A00)->f130 = func_001E2268((Init_18E5E8*)0, (void*)1);
    ((Glob_18E5E8*)&D_00269A00)->f0C = 0;
    (void)func_001F5C0C(&l, 0, sizeof(l));
    l.f04 = func_0018E558;
    l.f08 = (s32)D_002C2B00;
    l.f10 = (s32)D_002832F0;
    l.f0C = 0x1000;
    l.f14 = 2;
    v = func_001F6A10(&l);
    D_00275964 = v;
    func_001F6A20((Mgr_18E5E8*)v, 0);
}

void func_0018E678(Ring_18E6C0* self, s32 a1, s32 a2)
{
    self->f04 = a2;
    self->f08 = a1;
    func_0018E6A0(self);
}

void func_0018E6A0(Ring_18E6C0* c)
{
    c->f14 = c->f08;
    c->f18 = 0;
    c->f10 = 0;
    c->f0C = 0;
    c->f1C = 0;
}

s32 Ring_18E6C0::Put(s32 count, u8* dst)
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
        r = func_0018E7C0(this, left < avail ? left : avail, dst + total);
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

s32 func_0018E7C0(Ring_18E6C0* p, s32 size, u8* buf)
{
    Span_18E7C0 span;
    void* obj;

    span.a = (s32)buf;
    span.b = p->f04 + p->f0C;
    span.c = (void*)size;
    span.d = 0;
    func_001F6C20(0);
    obj = func_001F6CA0(&span, 1);
    while (func_001F6C90(obj) >= 0) {
    }
    return size;
}

void func_0018E838(Ring_18E6C0* self) { s32 raw = func_0011E4F8(self); s32 x = (raw & 0xFFFFFF) - self->f04; x = x - self->f0C; x = x - 0x400; x = x + self->f08; self->f14 = x; self->f14 = x % self->f08; s32 d = self->f08 - self->f14; self->f18 = d; s32 y = self->f0C - d; y += self->f08; self->f10 = y; self->f10 = y % self->f08; }

s32 Ring_18E6C0::Idle()
{
    return 0;
}

s32 Dma_18E8C8::Put(s32 size, u8* buf)
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

s32 Dma_18E8C8::Idle()
{
    return 1;
}

// Declared to return a value it never sets: func_0018F448, its caller, is retail's only with a
// callee that returns one.
s32 func_0018E940(Obj_18E940* self)
{
    s32 r;
    func_0011D6A8(0xFFFFFFFF);
    func_001C08B0(D_00275710, 0, 0);
    func_0011E010();
    while (func_0011CE30() != 0) {
    }
    func_0011E110(1);
    func_0011E1F8(0);
    self->f8C = func_0011D4B8(2);
    self->f90 = func_0011D4B8(8);
    func_0011D480(2, 0x400);
    func_0011D480(8, 0x200);
    r = func_0011E428(0x6000, 0x400, 0, 2, 2);
    if (r < 0) {
        self->f00 = 0;
    } else {
        self->f00 = 1;
        func_0013C988(self->sub2C, 0x28, &self->f04);
        func_0013C988(self->sub4C, 0xC000, D_002CBB40);
        func_0018E678(&self->sub6C, 0x6000, r);
    }
}

void func_0018EA48(Obj_18EA48* self)
{
    if (self->flag != 0) {
        func_0011E460();
        self->flag = 1;
        func_0013C9B0((u8*)self + 0x2C);
        func_0013C9B0((u8*)self + 0x4C);
        func_0018E6A0((Ring_18E6C0*)((u8*)self + 0x6C));
    }
}

void func_0018EAA0(Obj_18EAA0* self)
{
    self->f00 = 0;
    func_0011E498();
    func_0011D480(2, self->f8C);
    func_0011D480(8, self->f90);
    func_001C0950(D_00275710);
    func_0011D6D8(0xFFFFFFFF);
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
        n = func_0013CC00(self->sub2C, left, right);
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
    func_0013CC00(self->sub4C, left, right);
one:
    return 1;
}

void func_0018EB98(Self_18EB98* self)
{
    switch (self->state) {
    case 2:
        func_0013CAD8(&self->f4C, self->f80, (u8*)&self->f4C + 0x20);
        if (self->f80 != 0) {
            break;
        }
        func_0011E4C0(self->f70, self->f74, self->f70, 0, 0);
        self->state = 3;
        break;
    case 3: {
        void* s0 = (u8*)&self->f4C + 0x20;
        func_0018E838((Ring_18E6C0*)s0);
        func_0013CAD8(&self->f4C, self->f80, s0);
        break;
    }
    }
}

s32 func_0018EC40(void* a0, void* a1, void* a2)
{
    if (*(u32*)((u8*)a2 + 0x70) >= *(u32*)((u8*)a1 + 0xC)) {
        func_0013CC00((u8*)a2 + 0x60, *(u32*)((u8*)a1 + 0xC), *(void**)((u8*)a1 + 0x8));
        return 1;
    }
    return 0;
}

void func_0018EC80(void* a0, Args_18EC80* a1, void* a2)
{
    func_0018EAF8((Stream_18EAF8*)((u8*)a2 + 0x80), a1->fC, a1->f8);
}

s32 func_0018ECA8(void* u0, void* u1, Obj_18ECA8* self)
{
    s32 total = 0x40;
    while (self->f74 < 0x1000) {
        if (func_0018F890((Object_18F890*)self, 1) == 0) {
            u8 zero[0x40];
            func_001F5C0C(zero, 0, 0x40);
            s32 k = self->f74;
            func_0013CC00(&self->sub, total - (k % 32), zero);
            break;
        }
    }
    {
        Dma_18E8C8 dma;
        func_0013CC48(&self->sub, 0);
        func_0013CAD8(&self->sub, 0, &dma);
    }
    return 1;
}

s32 func_0018ED78(void* a0, s32 a1, void* a2)
{
    func_0018F890((Object_18F890*)a2, 0);
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

    func_001611B8(&f);
    func_001529C8(&f, 0x1C28, p);
    func_00152B38(&f);
    func_001613C0(&f, 0, 1, 0xE);
    func_00161708(&f, 0x50, (u64)0xA1E0 << 36);
    func_00161708(&f, 0x52, ((u64)0x10 << 32) | 0x10);
    for (y = 0; y < ny; y++) {
        for (x = 0; x < nx; x++) {
            func_001613C0(&f, 0, 1, 0xE);
            func_00161708(&f, 0x51, ((u64)(y << 4) << 32) | ((u64)(x << 4) << 48));
            func_00161708(&f, 0x53, 0);
            func_00161958(&f, 0x40);
            func_00152B80(&f, 0x40, addr & 0xFFFFFFF);
            addr += 0x400;
        }
    }
    func_001613C0(&f, 0, 1, 0xE);
    func_00161708(&f, 0x3F, 0);
    func_00161708(&f, 0x61, 0);
    func_00161200(&f);
    func_00152D30(&f);
    func_001529E0(&f, 0, 0);
}

void func_0018EF78(void* self, s32 a1, s32 a2)
{
    Local_18EF78 buf;
    func_001611B8(&buf);
    func_001529C8(&buf, 0x12, self);
    func_00152B38(&buf);
    func_001613C0(&buf, 6, 1, 0xE);
    func_00161708(&buf, 6, 0x0AA8029E00ULL);
    func_00161708(&buf, 0x14, 0x61);
    func_00161708(&buf, 8, 5);
    func_00161708(&buf, 0x42, 0x44);
    func_00161708(&buf, 0x47, 0x31001);
    func_001613C0(&buf, 0x116, 5, 0xE4343);
    func_001614C8(&buf, 8, 8);
    func_001615F0(&buf, 0x6C00, 0x7900, 0, 0);
    func_001614C8(&buf, (a1 << 4) | 8, (a2 << 4) | 8);
    func_001615F0(&buf, 0x9400, 0x8700, 0, 0);
    func_00161708(&buf, 0x61, 0);
    func_00161200(&buf);
    func_00152D30(&buf);
    func_001529E0(&buf, 0, 0);
}

void func_0018F0E8(void* self, void* p)
{
    s32 m;
    s32 v;

    if (*(void**)((u8*)self + 4) != 0) {
        return;
    }
    *(void**)((u8*)self + 4) = p;
    v = func_0018E410((Ent_18E410*)p);
    if ((u32)v >= 16) {
        m = 0;
    } else {
        m = 1 << v;
    }
    *(u32*)((u8*)D_002623C0 + 0x19F4) |= m;
}

void func_0018F148(Obj_18F148* self)
{
    s32 pending = self->f08;
    s32 first = self->f04;
    self->f04 = 0;
    self->f08 = 0;
    func_0018F198((Self_18F198*)self, (Key_18F198*)first);
    if (pending != 0) {
        func_0018F198((Self_18F198*)self, (Key_18F198*)pending);
    }
}

void func_0018F198(Self_18F198* self, Key_18F198* key)
{
    Loc_18F198 loc;
    Pair_18F198 pr;
    func_00191E70(4);
    self->mode = func_0018E410((Ent_18E410*)key);
    func_0012FCF0(&loc, D_002C3B00);
    if (pr.Set(key) && func_0012FD78(&loc, &pr)) {
        func_0018F448((Obj_18F448*)self, &loc);
        while (!func_0020B0B0(self->list)) {
            func_00143030(((u8*)D_00261858));
            func_0016E238(&D_00262C70);
            s32 flag = 0;
            if (key->Same((Key_18F198*)&D_00248490)) flag = D_00269B4C != 0;
            u32 m;
            if (self->mode >= 16) m = 0;
            else m = 1u << self->mode;
            if ((*(Tbl_18F198**)&D_002623C0)->mask & m) flag = 1;
            if (flag) {
                if (func_001F00F0(D_00275F80, &D_00262C70, 2)) break;
                if (D_00262C70.bits & 0x91F) {
                    func_0016EC20(&D_00262C70, 0x91F);
                    break;
                }
            }
            func_001409E0();
            if (D_002613EC != 3) break;
            func_0018F6E8((Obj_18F6E8*)self);
        }
        if (key->Same((Key_18F198*)&D_00248490)) D_00269B4C = 1;
        func_0018F7D0((Obj_18F7D0*)self);
        func_0012FDE8(&loc);
    } else {
        func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    func_00191EB0(4);
    func_0012FD30(&loc, 2);
}

void func_0018F448(Obj_18F448* self, void* v)
{
    s32 i;

    self->fC = v;
    self->f58 = D_002D7B40;
    self->f5C = D_0045AAC0;
    func_0013C988((u8*)self + 0x60, 0x30000, (void*)((s32)D_0042AAC0 | 0x20000000));
    func_0018E940((Obj_18E940*)((u8*)self + 0x80));
    func_0020ADA0();
    func_0020AE40((u8*)self + 0x10, self->f58, 0x152F68);
    func_0020A538((u8*)self + 0x10, 0, 0, (void*)func_0018EC40, self);
    func_0020A538((u8*)self + 0x10, 2, 0, (void*)func_0018EC80, self);
    func_0020B168((u8*)self + 0x10, 1, (void*)func_0018ECA8, self);
    func_0020B168((u8*)self + 0x10, 4, (void*)func_0018ED78, self);
    func_0020B168((u8*)self + 0x10, 0, (void*)func_0018EDA0, self);
    while (func_0018F890((Object_18F890*)self, 1) != 0) {
    }
    self->f114 = D_00586AC0;
    self->f118 = D_005A2D40;
    D_002626CC = 0;
    D_00269A00.cur = (u8*)0x100010;
    D_00269A00.remain = (s32)D_00148D68;
    D_00269A00.crc = 0xFFFFFFFF;
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
            D_00269B48 = 1;
        }
    }
}

void func_0018F6E8(Obj_18F6E8* self)
{
    void* s1;
    if (self->f134 == 1) {
        do {
            (void)func_0018F890((Object_18F890*)self, 0);
        } while (self->f134 == 1);
    }
    if (func_0020B058((u8*)self + 0x10, self->f5C, 0x4B0) < 0) {
        return;
    }
    if (self->f18 == 0) {
        func_0018EDA8(self->f114, self->f5C, self->f10, self->f14);
        func_0018EF78(self->f118, self->f10, self->f14);
        func_001F6C20(0);
    }
    s1 = (u8*)self + 0x80;
    if (self->f134 != 0) {
        do {
            (void)func_0018F890((Object_18F890*)self, 0);
            func_0018F610((Obj_18F610*)self);
        } while (self->f134 != 0);
    }
    func_001F6B40(self->f130);
    func_0018EB98((Self_18EB98*)s1);
}

void func_0018F7D0(Obj_18F7D0* self)
{
    u8* base = (u8*)self;
    s32 mask;

    self->f0C = 0;
    func_0018EA48((Obj_18EA48*)(base + 0x80));
    func_0018EAA0((Obj_18EAA0*)(base + 0x80));
    func_0020B0C0(base + 0x10);
    (void)func_0020B048(base + 0x10);
    if (self->f134 != 0) {
        do {
        } while (*(volatile s32*)&self->f134 != 0);
    }
    D_002626CC = 3;
    func_001B3450();
    if ((u32)self->f00 >= 16) {
        mask = 0;
    } else {
        mask = 1 << self->f00;
    }
    *(s32*)((u8*)D_002623C0 + 0x19F8) |= mask;
}

s32 func_0018F890(Object_18F890* self, s32 wait)
{
    while (Empty_18F890::Of(self->buffer)) {
        func_00130070(self->buffer);
        if (Empty_18F890::Of(self->buffer) && !wait) return 0;
    }
    func_001F6C20(0);
    Buffer_18F890* buffer = self->buffer;
    s32 count = buffer->head - buffer->tail;
    s32 result = func_0020A518(self->pad10, buffer->base + buffer->tail, count);
    func_001300D8(self->buffer, result);
    return result;
}

LINKER_REMNANT(func_0018F938);
