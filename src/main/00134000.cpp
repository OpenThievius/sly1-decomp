// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"

struct Node_1363D0 { u8 pad0[0x324]; void* child; };

void func_001AA8C8(void* self);
s32 func_00150790(void* obj, s32 mode);



struct Child_136EF8 { u8 pad0[0x2D0]; s32 kind; };
struct Owner_136EF8 { u8 pad0[0x324]; Child_136EF8* child; };

void func_001356C0(Owner_136EF8* self, s32 mode);
void func_00150790(Child_136EF8* obj, s32 mode);



struct Obj_137268 { u8 pad[0x18]; void* field18; };



struct Pair_1373B0 { void* first; s32 second; };

void func_00137328(void* a, void* b, s32 c);

void func_001373B0(void* a, Pair_1373B0* pair)
{
    func_00137328(a, pair->first, pair->second);
}

struct Ring_137B60 { u8 pad0[0x18]; s32 head; s32 size; };

void func_00137B60(Ring_137B60* self, s32 n)
{
    s32 head = self->head;
    s32 t = head - 1;
    t = t + n;
    s32 aligned = t & -n;
    s32 delta = aligned - head;
    self->head = aligned;
    self->size -= delta;
}

struct Entry_1357F0 {
    void* obj;
    f32 key;
};

s32 func_00182FC8(void* obj);



struct Entry_135858 {
    void* obj;
    f32 key;
};

void func_00199C10(void* obj, s32* out);



struct Chan_1373D0 {
    s32 a00;
    s32 mode;
    s32 a08;
    s32 a0C;
    s32 a10;
    s32 a14;
    s32 a18;
    s32 a1C;
    s32 a20;
    s32 a24;
    s32 a28;
    s32 a2C;
    void* a30;
    void* a34;
    s32 a38;
    s32 a3C;
    s32 a40;
};

s32 func_00137480(Chan_1373D0* self, s32 n)
{
    return self->a40 -= n;
}

struct SlotEntry_135E78 { void* handle; s32 extra; };

struct SlotBank_135E78 {
    u8 pad0[0x328];
    s32 state;
    u8 pad1[0x4];
    u8 blockA[0x10];
    u8 blockB[0x10];
    s32 countA;
    s32 count;
    u8 pad2[0x4];
    SlotEntry_135E78 entries[1];
};

void func_0019EBE8(void* handle);
void func_001A1DF0(void* handle, s32 mode);
void func_001F5C0C(void* block, s32 value, s32 size);



struct Owner_136FA8 { u8 pad0[0x324]; void* child; };

s32 func_001356C0(Owner_136FA8* self, s32 mode);



struct Pair_137228 { f32 x; f32 y; };



struct Reader_137D10 { u8 pad0[0x18]; u8* cur_18; s32 remaining_1C; };

void func_00137A60(void* self, s32 count, void* out);

s32 func_00137D10(Reader_137D10* self)
{
    if (self->remaining_1C >= 2) {
        u8* p = self->cur_18;
        u8 lo = p[0];
        s32 hi = p[1];
        self->cur_18 = p + 2;
        self->remaining_1C -= 2;
        return lo | ((s16)(hi << 8));
    }
    s16 tmp;
    func_00137A60(self, 2, &tmp);
    return tmp;
}

struct Vec2_137238 { u8 pad0[0x8]; f32 x; f32 y; };



struct __attribute__((packed)) Unaligned_137248 { u32 value; };



struct Reader_137DF8 {
    u8 pad0[0x18];
    u8* cursor_18;
    s32 left_1C;
};

void func_00137A60(void* self, s32 size, void* dst);

f32 func_00137DF8(Reader_137DF8* r)
{
    s32 left = r->left_1C;
    if (left >= 4) {
        u8* p = r->cursor_18;
        u32 v = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        r->cursor_18 = p + 4;
        r->left_1C = left - 4;
        return *(f32*)&v;
    }
    f32 tmp;
    func_00137A60(r, 4, &tmp);
    return tmp;
}

void func_00137A60(void* self, s32 size, void* dst);

void func_00137E70(void* src, void* dst)
{
    func_00137A60(src, 12, dst);
}

// Newly matched US functions from the small-function wave.
struct Obj_1365A0 { u8 pad[0x2FC]; s32 f2FC; };
struct Obj_137260 { u8 pad[0x14]; s32 f14; };
extern void func_00136FE8(s32, s32);
extern void func_001373D0(void*);
extern void func_0018D778(void*);
struct Obj_137398 { u8 pad0[4]; s32 state; u8 pad8[0x10]; s32 f18; s32 f1C; };
extern void func_00137A60(void*, s32, void*);







void func_001372E0(void* self, s32 flags)
{
    func_001373D0(self);
    if (flags & 1) func_0018D778(self);
}

void func_00137398(Obj_137398* self, s32 a1, s32 a2) { self->f1C = a1; self->f18 = a2; self->state = 2; }

void func_00137E90(void* self, void* out) { func_00137A60(self, 0x10, out); }

void func_00137EB0(void* self, u8* buffer)
{
    func_00137A60(self, 0xC, buffer);
    func_00137A60(self, 0xC, buffer + 0x10);
    func_00137A60(self, 0xC, buffer + 0x20);
}

struct State_001365A8 { u8 pad[0x300]; f32 value;
    void set(f32 x, f32 lo, f32 hi) {
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        value = x;
    }
};


struct State_00136EC8 { u8 pad[0x304]; f32 x; f32 y; };


struct State_00137820 { s32 w[13]; s32 maximum(s32 a, s32 b) { return a < b ? b : a; } };
void func_001377C0(void* self);
void func_00137490(void* self);
void func_00193288(void* self, s32 value);
void func_00137820(State_00137820* self)
{
    switch (self->w[1]) {
    case 0: func_001377C0(self); break;
    case 1: func_00137490(self); break;
    }
    s32 value = self->w[5] - self->w[9];
    value = self->maximum(0, value);
    self->w[5] = value;
    if (self->w[12]) func_00193288((void*)self->w[12], value);
}

s32 func_00137B90(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 1) {
        u8* p = self->cur_18;
        s32 value = p[0];
        self->cur_18 = p + 1;
        self->remaining_1C = count - 1;
        return value;
    }
    u8 value;
    func_00137A60(self, 1, &value);
    return value;
}

s32 func_00137BE0(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 2) {
        u8* p = self->cur_18;
        s32 value = p[0] | (p[1] << 8);
        self->cur_18 = p + 2;
        self->remaining_1C = count - 2;
        return value;
    }
    u16 value;
    func_00137A60(self, 2, &value);
    return value;
}

u32 func_00137C40(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 4) {
        u8* p = self->cur_18;
        u32 value = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        self->cur_18 = p + 4;
        self->remaining_1C = count - 4;
        return value;
    }
    u32 value;
    func_00137A60(self, 4, &value);
    return value;
}

s32 func_00137CC0(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 1) {
        u8* p = self->cur_18;
        s32 value = (s8)p[0];
        self->cur_18 = p + 1;
        self->remaining_1C = count - 1;
        return value;
    }
    s8 value;
    func_00137A60(self, 1, &value);
    return value;
}

s32 func_00137D78(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 4) {
        u8* p = self->cur_18;
        s32 value = p[0] + (p[1] << 8) + (p[2] << 16) + ((s8)p[3] << 24);
        self->cur_18 = p + 4;
        self->remaining_1C = count - 4;
        return value;
    }
    s32 value;
    func_00137A60(self, 4, &value);
    return value;
}

struct Obj_136530 {
    u8 pad0[4];
    s32 handle;
    s8 flag;
    u8 pad1[0x268 - 9];
    f32 f268;
    u8 pad2[0x2F0 - 0x26C];
    f32 scale;
};

extern f32 D_0026185C;

void func_0015DB28(void* out, void* p, s32 handle);
s32 func_0015DF58(void* self);



void func_00137A60(void* self, s32 size, void* obj);

void func_00137F08(void* self, u8* p)
{
    u8* a = p + 0x10;
    u8* b = p + 0x20;
    u8* c = p + 0x30;

    func_00137A60(self, 12, p);
    func_00137A60(self, 12, a);
    func_00137A60(self, 12, b);
    func_00137A60(self, 12, c);
    *(s32*)(p + 0xC) = 0;
    *(s32*)(a + 0xC) = 0;
    *(s32*)(b + 0xC) = 0;
    *(f32*)(c + 0xC) = 1.0f;
}

extern f32 D_00261858[];

struct Scratch_00136408 {
    u8 bytes[0xB0];
};

struct Entry_00136408 {
    u8 pad0[4];
    s32 f04;
    u8 name08[0x258];
    s32 f260;
    u8 pad264[4];
    f32 f268;
    s32 f26C;
    s32 list270[16];
};

s32 func_001E2100(const char* s);
void func_001E2138(void* dst, const char* src);
void func_0015C8B8(s32 a, f32 x, f32 y);
void func_0015DB28(void* buf, void* p, s32 v);
void func_0015E068(void* buf, f32 x);
void func_0015C900(s32 v);
void func_0015DB80(void* buf);
s32 func_0015DBE0(void* buf);



struct Chan_001373D0 {
    s32 a00;
    s32 mode;
    s32 a08;
    s32 a0C;
    s32 a10;
    s32 a14;
    s32 a18;
    s32 a1C;
    s32 a20;
    s32 a24;
    s32 a28;
    s32 a2C;
    s32 a30;
    s32 a34;
    s32 a38;
    s32 a3C;
    s32 a40;
};

s32 func_001F8DB8(s32 p, s32 a, s32 b);

void func_001F8C38(s32 p);
void func_00203E28(void);
void func_0011E2A0(void);

void func_001373D0(Chan_001373D0* self)
{
    s32 next = -1;
    switch (self->mode) {
    case 0:
        if (self->a34 >= 0) {
            func_001F8C38(self->a34);
        }
        break;
    case 1:
        if (self->a3C != 0) {
            if ((self->a00 & 2) != 0) {
                func_00203E28();
            } else {
                func_0011E2A0();
            }
        }
        break;
    default:
        break;
    }
    self->mode = next;
    self->a20 = 0;
    self->a18 = 0;
    self->a24 = 0;
    self->a1C = 0;
    self->a28 = 0;
    self->a2C = 0;
}

struct Ring_00137328 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    u8 pad24[0x14];
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
};

s32 func_00137328(Ring_00137328* r, s32 a1, s32 a2)
{
    r->f04 = 1;
    r->f48 = a1;
    r->f10 = a2;
    r->f14 = a2;
    r->f40 = a2;
    r->f20 = r->f08;
    r->f38 = 0;
    r->f44 = 0;
    r->f3C = 0;
    s32 count = r->f0C / 0x100000;
    s32 m = 2;
    if (m < count) m = count;
    r->f50 = 0;
    r->f54 = 0;
    r->f4C = m;
    r->f58 = m - 1;
    return 1;
}

typedef void (*VFn_1356C0)(void* self);

struct __attribute__((packed)) Tail_1356C0 { u8 pad0[0x464]; s32 v; };
struct Global_1356C0 {
    VFn_1356C0* vtbl;
    u8 pad0[0x464 - 4];
};

struct Obj_1356C0 { u8 pad0[0x260]; s32 state; f32 timer; };

extern Global_1356C0 D_0026F138;
extern f32 D_0026185C;

void func_00131140(Obj_1356C0* self);
void func_001BFCD8(s32 a, s32 b, s32 c, s32 d, f32 g, f32 h, f32 i, f32 j, f32 k, s32 e, s32 f);



extern u8 D_00275710[];
extern u8 func_00135E20[];
extern u8 func_00135E40[];

struct Self_135F48 {
    u8 pad000[0x328];
    s32 f328;
};

struct Ctx_135F48 {
    u8 pad000[0x1D44];
    s32 f1D44;
    u8 pad1D48[0x0C];
    s32 f1D54;
};

struct Flag_135F48 { s32 v; };

void func_00160D30(Flag_135F48* p);
s32 func_00160D10(void);
void func_00135E78(Self_135F48* self, s32 state, s32 flag);
void func_001358D0(Self_135F48* self, s32 a1, void* a2, void* a3, s32 a4, s32 a5, f32 f);



// NEAR: control flow and the calls match; the compiler picks s0 for self and s1 for n (retail: s1, s0),
// and keeps the loaded count in $a2 where retail uses $v1.
struct Stream_137A60 {
    s32 flags;      // 0x00
    u8 pad04[0x14];
    s32 ptr;        // 0x18
    s32 count;      // 0x1C
    s32 nextPtr;    // 0x20
    s32 nextCount;  // 0x24
};

struct Dst_137A60;

void func_001378A0(Stream_137A60* self);
void func_00137820(Stream_137A60* self);
void func_0018D800(Dst_137A60* dst, void* src, s32 count);

void func_00137A60(Stream_137A60* self, s32 remaining, Dst_137A60* dst)
{
    if (self->count < 0) {
        return;
    }
    if (remaining <= 0) {
        return;
    }
    do {
        s32 cnt = self->count;
        if (cnt == 0) {
            if (self->flags & 4) {
                func_001378A0(self);
            } else {
                func_00137820(self);
                s32 nc = self->nextCount;
                s32 np = self->nextPtr;
                self->count = nc;
                self->ptr = np;
                self->nextPtr = np + nc;
                self->nextCount = 0;
            }
            cnt = self->count;
            if (cnt == 0) {
                self->count = -1;
                return;
            }
        }
        s32 n;
        if (remaining < cnt) {
            n = remaining;
        } else {
            n = cnt;
        }
        if (dst != 0) {
            func_0018D800(dst, (void*)self->ptr, n);
            dst = (Dst_137A60*)((u8*)dst + n);
        }
        remaining -= n;
        self->ptr += n;
        self->count -= n;
    } while (remaining > 0);
}

struct Obj_1365F0 { u8 pad0[0x260]; s32 state; };

f32 func_001AA898(Obj_1365F0* self);



struct S_136648 { u8 pad[0x260]; s32 mode; };
extern f32 func_001AA8A8(S_136648* s);



struct Tri_136040 { u64 a __attribute__((packed)); u32 b; };
typedef u64 Quad_136040 __attribute__((mode(TI)));
struct __attribute__((aligned(16))) Vec_136040 { f32 x, y, z, w; };
struct Pad_136040 {
    u8 pad_00[0x40];
    f32 f40;
    f32 f44;
    f32 f48;
    u8 pad_4C[0x74 - 0x4C];
    f32 f74;
    u8 pad_78[4];
    f32 f7C;
};
struct Self_136040 {
    u8 pad_000[0x260];
    s32 f260;
    u8 pad_264[0x304 - 0x264];
    f32 f304;
    f32 f308;
    u8 pad_30C[8];
    f32 f314;
};
struct Glob_136040 {
    u8 pad[0x19EC];
    u32 flags;
};

extern const Tri_136040 D_00249D00;
extern const Tri_136040 D_00249D10;
extern Glob_136040* D_002623C0;

Quad_136040 func_001EA818(Quad_136040 a, Quad_136040 b, Tri_136040* c, s32 d, f32 f12);
f32 func_001EAFE0(f32 x, f32 y);
void func_00135F48(Self_136040* self, Pad_136040* p);



struct __attribute__((aligned(16))) Vec_135E30 { s32 a, b, c, d; };
struct Obj_135E30 { char pad[0x140]; Vec_135E30 v; };



struct __attribute__((aligned(16))) Vec_135E48 { s32 a, b, c, d; };
struct Obj_135E48 { char pad[0x140]; Vec_135E48 v; };

void func_001A1F40(Vec_135E48* v, s32 mode);



struct Obj_137290 { s32 f0; s32 f4; s32 f8; s32 fC; u8 pad10[8]; s32 f18; s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30; };
Obj_137290* func_00137290(Obj_137290* self, s32 a1, s32 a2, s32 a3)
{
    s32 align = (a2 + 0x3F) & -0x40;
    self->f4 = -1;
    self->f0 = a3;
    self->f20 = 0;
    self->f18 = 0;
    self->f24 = 0;
    self->f1C = 0;
    self->f30 = 0;
    self->f28 = 0;
    self->f2C = 0;
    self->f8 = align;
    self->fC = a1 - (align - a2);
    return self;
}

extern s32 func_001F8DB8(void*, s32, s32);
struct Obj_1377C0 { u8 pad0[8]; s32 f8; s32 fC; u8 pad10[4]; s32 f14; u8 pad18[8]; s32 f20; s32 f24; u8 pad28[0xC]; void* f34; };
struct Min_1377C0 { static s32 Of(s32 a, s32 b) { return a < b ? a : b; } };
void func_001377C0(Obj_1377C0* self)
{
    s32 size = self->fC;
    s32 limit = self->f14;
    self->f20 = self->f8;
    size = (size > 0x8000) ? Min_1377C0::Of(0x8000, limit) : Min_1377C0::Of(size, limit);
    self->f24 = func_001F8DB8(self->f34, self->f20, size);
}

struct Item_135550;
struct List_135550 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_135550 { List_135550* list; u8* link; s32 offset; Iter_135550* saved; };
struct Group_135550 { u8 pad0[0x6C]; List_135550 list; };
struct Obj_135550 { u8 pad0[0x250]; s32 f250; };
struct Host_135550;


struct Next_135550 {
    static Item_135550* Of(Iter_135550* it)
    {
        Item_135550* obj = *(Item_135550**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_135550 {
    static void Of(Iter_135550* it, List_135550* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_135550*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

Group_135550* func_0015A418(Host_135550* host, s32 a1, s32 a2, void* ctx);
void func_0012F6B0(Item_135550* item, f32 x);
void func_001AA998(Obj_135550* self, s32 value);



struct Obj_136238;
struct VT_136238 { u8 pad0[0x40]; void (*f40)(Obj_136238*, s32); };
struct Obj_136238 {
    VT_136238* vt;
    u8 pad4[0x25C - 4];
    s32 f25C;
    u8 pad260[0x320 - 0x260];
    s32 f320;
    struct Sub_136238* f324;
    s32 f328;
    s32 f32C;
};
struct Sub_136238 { u8 pad0[0x2D4]; s32 f2D4; };
struct In_136238 { s32 a; };

s32 D_00261120[2] = { -268435456, -268435456 };
extern u8 D_00275710[];

void func_001BEA50(void);
void func_001BEA28(void);
void func_00160D30(In_136238* p);
s32 func_00160D10(void);
void func_00135E78(Obj_136238* self, s32 state, s32 flag);
s32 func_0015A4F0(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void func_00192190(void* p);

struct Min_136238 { static s32 Of(s32 a, s32 b) { if (b - 1 < a) return b; return a; } };



struct Dec_1378A0 {
    u8 pad0[0x18];
    u8* f18;
    s32 f1C;
    u8* f20;
    s32 f24;
    s32 f28;
    s32 f2C;
};

void func_00137820(Dec_1378A0* d);
void func_001F5A58(void* dst, void* src, s32 n);

void func_001378A0(Dec_1378A0* d)
{
    u8* base = (u8*)0x70000000;
    s32 pos = 0;
    s32 n = d->f24;
    u8* p = d->f20;
    s32 flags = d->f28;
    s32 more;
    s32 carry = d->f2C;
    if (carry > 0) {
        func_001F5A58((void*)0x70000000, (void*)0x70002000, carry);
        pos = d->f2C;
    }
    while ((more = pos < 0x2000) != 0) {
        flags >>= 1;
        if (!(flags & 0x100)) {
            if (--n < 0) {
                func_00137820(d);
                if (d->f24 <= 0) break;
                p = d->f20;
                n = d->f24 - 1;
            }
            flags = *p++ + 0xFF00;
        }
        if (--n < 0) {
            func_00137820(d);
            if (d->f24 <= 0) break;
            p = d->f20;
            n = d->f24 - 1;
        }
        s32 b = *p++;
        if (flags & 1) {
            base[pos++] = b;
        } else {
            if (--n < 0) {
                func_00137820(d);
                p = d->f20;
                n = d->f24 - 1;
            }
            u32 v = b + (*p++ << 8);
            s32 cnt = ((s32)v >> 13) + 2;
            s32 src = v & 0x1FFF;
            for (; cnt >= 0; cnt--) {
                base[pos++] = base[src++ & 0x1FFF];
            }
        }
    }
    d->f18 = base;
    if (more == 0) {
        d->f1C = 0x2000;
        d->f2C = pos - 0x2000;
    } else {
        d->f1C = pos;
        d->f2C = 0;
    }
    d->f20 = p;
    d->f24 = n;
    d->f28 = flags;
}

struct Obj_135228
{
    u8 pad0[0x260];
    s32 f260;
    u8 pad1[0x330 - 0x264];
    s32 f330[4];
    f32 f340[4];
};

struct Q_135228
{
    u8 pad[4];
};

f32 D_00261260[2] = { 8.0f, 0.0f };
f32 D_002611E0[4][4] = {
    { -5.0f, -15.0f, -35.0f, -15.0f },
    { 5.0f, 15.0f, 35.0f, 15.0f },
    { 0.0f, 10.0f, 0.0f, -10.0f },
    { 0.0f, -10.0f, 0.0f, 10.0f },
};
f32 D_00261220[4][4] = {
    { 0.0f, -11.0f, 0.0f, 11.0f },
    { 0.0f, 11.0f, 0.0f, -11.0f },
    { -4.4f, -15.4f, -35.2f, -15.4f },
    { 4.4f, 15.4f, 35.2f, 15.4f },
};

void func_00160D30(u32* out);
void func_00134B48(Obj_135228* self, Q_135228* q);
f32 func_00205210(f32 x);
f32 func_001EA4B8(f32 a, f32 b, f32 c, f32* p, s32 zero);
void func_001613C0(Q_135228* q, s32 a, s32 b, u64 c);
void func_00161458(Q_135228* q, u32 v);
void func_001615F0(Q_135228* q, s32 a, s32 b, s32 c, s32 d);



struct Strm_137490 {
    s32 flags;      // 0x00
    s32 f04;
    s32 base;       // 0x08
    s32 total;      // 0x0C
    u8 pad10[0x10];
    s32 pos;        // 0x20
    s32 rem;        // 0x24
    u8 pad28[0x10];
    s32 done;       // 0x38
    s32 size;       // 0x3C
    s32 left;       // 0x40
    s32 start;      // 0x44
    s32 sector;     // 0x48
    s32 count;      // 0x4C
    s32 cur;        // 0x50
    s32 readIdx;    // 0x54
    s32 writeIdx;   // 0x58
};

struct Min_137490 {
    static s32 Of(s32 a, s32 b) { return a < b ? a : b; }
};

s32 func_00203AE8(void);
s32 func_002032C8(s32 a);
s32 func_0011E1F8(s32 a);
s32 func_00203D90(void);
s32 func_0011E2E8(void);
void func_00140CC8(s32 a, s32 b, s32 c);
void func_00140C28(s32 a, s32 b, s32 c);

struct Io_137490 {
    static void Read(Strm_137490* self, s32 sector, s32 len, s32 dst)
    {
        if (self->flags & 2) func_00140CC8(sector, len, dst);
        else func_00140C28(sector, len, dst);
    }
};

void func_00137490(Strm_137490* self)
{
    self->pos += self->rem;
    self->rem = 0;
    s32 chunk = (self->total / self->count) & -0x800;
    if (self->cur > 0) {
        s32 n = self->readIdx + 1;
        if (self->pos == self->base + n * chunk) {
            n = n % self->count;
            self->cur--;
            self->readIdx = n;
            self->pos = n * chunk + self->base;
        }
    }
    do {
        if (self->size > 0) {
            s32 got;
            if (self->flags & 2) got = func_00203AE8();
            else got = 0;
            got = Min_137490::Of(got + self->start, self->size);
            if (self->done < got) {
                self->done = got;
            } else {
                s32 busy;
                if (self->flags & 2) busy = func_002032C8(1);
                else busy = func_0011E1F8(1);
                if (busy == 0) {
                    s32 err;
                    if (self->flags & 2) err = func_00203D90();
                    else err = func_0011E2E8();
                    if (err == 0) {
                        s32 size = self->size;
                        self->done = size;
                        self->sector += size / 0x800;
                        self->left -= size;
                        self->size = 0;
                        self->start = 0;
                    } else {
                        s32 done = self->done;
                        s32 dst = self->base + self->writeIdx * chunk + done;
                        s32 len = ((self->size - done + 0x7FF) & -0x800) / 0x800;
                        self->start = done;
                        s32 sector = self->sector + done / 0x800;
                        Io_137490::Read(self, sector, len, dst);
                    }
                }
            }
        }
        s32 cur = self->cur;
        if (cur < self->count && self->size == 0 && self->left > 0) {
            s32 size = Min_137490::Of(self->left, chunk);
            self->done = 0;
            self->size = size;
            s32 n = (self->writeIdx + 1) % self->count;
            self->cur = cur + 1;
            s32 len = ((size + 0x7FF) & -0x800) / 0x800;
            s32 dst = self->base + n * chunk;
            s32 sector = self->sector;
            self->writeIdx = n;
            Io_137490::Read(self, sector, len, dst);
        }
        if (self->cur == 0) {
            self->rem = 0;
        } else {
            s32 singleBuffer = 1; // only the buffer being read is queued: it may still be loading
            s32 lim = chunk;
            if (self->cur == singleBuffer) lim = self->done;
            s32 avail = lim - (self->pos - (self->base + self->readIdx * chunk));
            self->rem = Min_137490::Of(avail, 0x8000);
        }
    } while (self->rem == 0 && self->left > 0);
}

