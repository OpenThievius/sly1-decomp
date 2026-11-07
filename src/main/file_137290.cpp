// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "c8b.h"
#include "v24a0.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"

// The file's .data: the two words func_00139C38 registers with func_00139B70 (4-aligned, so
// the .data starts right after file_130F48's; 0x26131C is padding before class 0x3B's).
s32 D_00261314 = 0;
s32 D_00261318 = 0;

typedef u64 Quad_136040 __attribute__((mode(TI)));

f32 func_001EAFE0(f32 x, f32 y);

struct __attribute__((aligned(16))) Vec_135E30 { s32 a, b, c, d; };

struct __attribute__((aligned(16))) Vec_135E48 { s32 a, b, c, d; };

void func_001A1F40(Vec_135E48* v, s32 mode);

BufferedStream* func_00137290(BufferedStream* self, s32 a1, s32 a2, s32 a3)
{
    s32 align = (a2 + 0x3F) & -0x40;
    self->mode = -1;
    self->flags = a3;
    self->nextPtr = 0;
    self->ptr = 0;
    self->nextCount = 0;
    self->remaining = 0;
    self->f30 = 0;
    self->f28 = 0;
    self->f2C = 0;
    self->end = align;
    self->start = a1 - (align - a2);
    return self;
}

// Newly matched US functions from the small-function wave.
extern void func_00136FE8(s32, s32);
extern void func_001373D0(void*);
extern void func_0018D778(void*);
extern void func_00137A60(void*, s32, void*);

void func_001372E0(void* self, s32 flags)
{
    CloseBufferedStream(self);
    if (flags & 1) func_0018D778(self);
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

void func_00137398(BufferedStream* self, s32 a1, s32 a2) { self->remaining = a1; self->ptr = a2; self->mode = 2; }

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"

void func_001AA8C8(void* self);
void func_00150790(void* obj, s32 mode);

struct Child_136EF8 { u8 pad0[0x2D0]; s32 kind; };

void func_00150790(Child_136EF8* obj, s32 mode);

s32 func_00137328(void* a, void* b, s32 c);

void func_001373B0(void* a, KeyId* pair)
{
    OpenBufferedSectorStream(a, pair->p0, pair->second);
}

extern f32 D_00261858[];

s32 func_001E2100(const char* s);
void* func_001E2138(void* dst, const char* src);
void func_0015C8B8(s32 a, f32 x, f32 y);
void* func_0015DB28(void* buf, void* p, s32 v);
s32 func_0015E068(void* buf, f32 x);
void func_0015C900(s32 v);
void func_0015DB80(void* buf);
s32 func_0015DBE0(void* buf);

s32 func_001F8DB8(s32 p, s32 a, s32 b);

s32 func_001F8C38(s32 p);
s32 func_00203E28(void);
s32 func_0011E2A0(void);

void func_001373D0(BufferedStream* self)
{
    s32 next = -1;
    switch (self->mode) {
    case 0:
        if (self->f34 >= 0) {
            func_001F8C38(self->f34);
        }
        break;
    case 1:
        if (self->f3C != 0) {
            if ((self->flags & 2) != 0) {
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
    self->nextPtr = 0;
    self->ptr = 0;
    self->nextCount = 0;
    self->remaining = 0;
    self->f28 = 0;
    self->f2C = 0;
}

s32 func_00182FC8(void* obj);

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

void func_00160D30(u32* out);
f32 func_00205210(f32 x);
f32 func_001EA4B8(f32 a, f32 b, f32 c, f32* p, s32 zero);

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
                else busy = SyncDiscRead(1);
                if (busy == 0) {
                    s32 err;
                    if (self->flags & 2) err = func_00203D90();
                    else err = GetDiscReadError();
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

struct State_001365A8 { u8 pad[0x300]; f32 value;
    void set(f32 x, f32 lo, f32 hi) {
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        value = x;
    }
};

struct Max_137820 { static s32 Of(s32 a, s32 b) { return a < b ? b : a; } };
void func_001377C0(void* self);
void func_00137490(void* self);
void func_00193288(void* self, s32 value);
void func_00137820(BufferedStream* self)
{
    switch (self->mode) {
    case 0: RefillBufferedStreamFromFile(self); break;
    case 1: RefillBufferedStreamFromSectors(self); break;
    }
    s32 value = self->f14 - self->nextCount;
    value = Max_137820::Of(0, value);
    self->f14 = value;
    if (self->f30) UpdateLoadProgress((void*)self->f30, value);
}

struct Item_135550;
struct List_135550 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_135550 { List_135550* list; u8* link; s32 offset; Iter_135550* saved; };
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

void func_0012F6B0(Item_135550* item, f32 x);

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


void func_001BEA50(void);
void func_001BEA28(void);
s32 func_00160D10(void);
void func_00135E78(Obj_136238* self, s32 state, s32 flag);
s32 func_0015A4F0(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void func_00192190(void* p);

struct Min_136238 { static s32 Of(s32 a, s32 b) { if (b - 1 < a) return b; return a; } };

void func_00137820(BufferedStream* d);
void func_001F5A58(void* dst, void* src, s32 n);

void func_001378A0(BufferedStream* d)
{
    u8* base = (u8*)0x70000000;
    s32 pos = 0;
    s32 n = d->nextCount;
    u8* p = d->next;
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
                RefillBufferedStream(d);
                if (d->nextCount <= 0) break;
                p = d->next;
                n = d->nextCount - 1;
            }
            flags = *p++ + 0xFF00;
        }
        if (--n < 0) {
            RefillBufferedStream(d);
            if (d->nextCount <= 0) break;
            p = d->next;
            n = d->nextCount - 1;
        }
        s32 b = *p++;
        if (flags & 1) {
            base[pos++] = b;
        } else {
            if (--n < 0) {
                RefillBufferedStream(d);
                p = d->next;
                n = d->nextCount - 1;
            }
            u32 v = b + (*p++ << 8);
            s32 cnt = ((s32)v >> 13) + 2;
            s32 src = v & 0x1FFF;
            for (; cnt >= 0; cnt--) {
                base[pos++] = base[src++ & 0x1FFF];
            }
        }
    }
    d->cur = base;
    if (more == 0) {
        d->remaining = 0x2000;
        d->f2C = pos - 0x2000;
    } else {
        d->remaining = pos;
        d->f2C = 0;
    }
    d->next = p;
    d->nextCount = n;
    d->f28 = flags;
}

typedef void (*VFn_1356C0)(void* self);

extern f32 D_0026185C;

void func_001BFCD8(s32 a, s32 b, s32 c, s32 d, f32 g, f32 h, f32 i, f32 j, f32 k, s32 e, s32 f);

extern u8 func_00135E20[];
extern u8 func_00135E40[];

s32 func_00160D10(void);

// NEAR: control flow and the calls match; the compiler picks s0 for self and s1 for n (retail: s1, s0),
// and keeps the loaded count in $a2 where retail uses $v1.
struct Dst_137A60;

void func_001378A0(BufferedStream* self);
void func_00137820(BufferedStream* self);
void func_0018D800(Dst_137A60* dst, void* src, s32 count);

void func_00137A60(BufferedStream* self, s32 remaining, Dst_137A60* dst)
{
    if (self->remaining < 0) {
        return;
    }
    if (remaining <= 0) {
        return;
    }
    do {
        s32 cnt = self->remaining;
        if (cnt == 0) {
            if (self->flags & 4) {
                UnpackBufferedStream(self);
            } else {
                RefillBufferedStream(self);
                s32 nc = self->nextCount;
                s32 np = self->nextPtr;
                self->remaining = nc;
                self->ptr = np;
                self->nextPtr = np + nc;
                self->nextCount = 0;
            }
            cnt = self->remaining;
            if (cnt == 0) {
                self->remaining = -1;
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
            CopyMemory(dst, (void*)self->ptr, n);
            dst = (Dst_137A60*)((u8*)dst + n);
        }
        remaining -= n;
        self->ptr += n;
        self->remaining -= n;
    } while (remaining > 0);
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

s32 func_00137B90(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 1) {
        u8* p = self->cur;
        s32 value = p[0];
        self->cur = p + 1;
        self->remaining = count - 1;
        return value;
    }
    u8 value;
    ReadBufferedStreamBytes(self, 1, &value);
    return value;
}

s32 func_00137BE0(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 2) {
        u8* p = self->cur;
        s32 value = p[0] | (p[1] << 8);
        self->cur = p + 2;
        self->remaining = count - 2;
        return value;
    }
    u16 value;
    ReadBufferedStreamBytes(self, 2, &value);
    return value;
}

u32 func_00137C40(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 4) {
        u8* p = self->cur;
        u32 value = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        self->cur = p + 4;
        self->remaining = count - 4;
        return value;
    }
    u32 value;
    ReadBufferedStreamBytes(self, 4, &value);
    return value;
}

LINKER_REMNANT(func_00137CB8);

s32 func_00137CC0(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 1) {
        u8* p = self->cur;
        s32 value = (s8)p[0];
        self->cur = p + 1;
        self->remaining = count - 1;
        return value;
    }
    s8 value;
    ReadBufferedStreamBytes(self, 1, &value);
    return value;
}

struct SlotEntry_135E78 { void* handle; s32 extra; };

void func_0019EBE8(void* handle);
void func_001A1DF0(void* handle, s32 mode);
void func_001F5C0C(void* block, s32 value, s32 size);

void func_00137A60(void* self, s32 count, void* out);

s32 func_00137D10(BufferedStream* self)
{
    if (self->remaining >= 2) {
        u8* p = self->cur;
        u8 lo = p[0];
        s32 hi = p[1];
        self->cur = p + 2;
        self->remaining -= 2;
        return lo | ((s16)(hi << 8));
    }
    s16 tmp;
    ReadBufferedStreamBytes(self, 2, &tmp);
    return tmp;
}

s32 func_00137D78(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 4) {
        u8* p = self->cur;
        s32 value = p[0] + (p[1] << 8) + (p[2] << 16) + ((s8)p[3] << 24);
        self->cur = p + 4;
        self->remaining = count - 4;
        return value;
    }
    s32 value;
    ReadBufferedStreamBytes(self, 4, &value);
    return value;
}

LINKER_REMNANT(func_00137DF0);

void func_00137A60(void* self, s32 size, void* dst);

f32 func_00137DF8(BufferedStream* r)
{
    s32 left = r->remaining;
    if (left >= 4) {
        u8* p = r->cur;
        u32 v = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        r->cur = p + 4;
        r->remaining = left - 4;
        return *(f32*)&v;
    }
    f32 tmp;
    ReadBufferedStreamBytes(r, 4, &tmp);
    return tmp;
}

void func_00137A60(void* self, s32 size, void* dst);

void func_00137E70(void* src, void* dst)
{
    ReadBufferedStreamBytes(src, 12, dst);
}

void func_00137E90(void* self, void* out) { ReadBufferedStreamBytes(self, 0x10, out); }

void func_00137EB0(void* self, u8* buffer)
{
    ReadBufferedStreamBytes(self, 0xC, buffer);
    ReadBufferedStreamBytes(self, 0xC, buffer + 0x10);
    ReadBufferedStreamBytes(self, 0xC, buffer + 0x20);
}

extern f32 D_0026185C;

void* func_0015DB28(void* out, void* p, s32 handle);
s32 func_0015DF58(void* self);

void func_00137A60(void* self, s32 size, void* obj);

void func_00137F08(void* self, u8* p)
{
    u8* a = p + 0x10;
    u8* b = p + 0x20;
    u8* c = p + 0x30;

    ReadBufferedStreamBytes(self, 12, p);
    ReadBufferedStreamBytes(self, 12, a);
    ReadBufferedStreamBytes(self, 12, b);
    ReadBufferedStreamBytes(self, 12, c);
    *(s32*)(p + 0xC) = 0;
    *(s32*)(a + 0xC) = 0;
    *(s32*)(b + 0xC) = 0;
    *(f32*)(c + 0xC) = 1.0f;
}

ASM_FUNC(func_00137FB0);

struct In_138278 { u8 pad0[0x10]; s32 base; };

s32 func_00137BE0(void* self);
void* func_0018D5C0(s32 size);

void func_00138278(void* self, In_138278* in, Tree03* out)
{
    s32 x = ReadBufferedU16(self);
    out->count = x;
    s32 y = ReadBufferedU16(self);
    out->count2 = y;
    out->nodes = (TreeNode03*)AllocateZeroedFrontMemory(12 * out->count);
    for (s32 i = 0; i < out->count; i++) {
        TreeNode03* e = out->nodes + i;
        s32 v = ReadBufferedU16(self);
        e->face = (void*)(in->base + (v << 5));
        s32 w = ReadBufferedU16(self);
        if ((w & 0xFFFF) != 0xFFFF) {
            e->back = out->nodes + w;
        }
        s32 z = ReadBufferedU16(self);
        if ((z & 0xFFFF) != 0xFFFF) {
            e->front = out->nodes + z;
        }
    }
}

void func_001BA130(void* self, void* other);

struct Item_138398 {
    u8 pad0[0x10];
    f32 f10;
    s32 f14;
    s32 f18;
    u8 pad1[0x20 - 0x1C];
};

s32 func_00137BE0(void* src);
void* func_0018D5C0(s32 bytes);
void func_00137E70(void* src, void* item);
f32 func_00137DF8(void* src);
s32 func_00137C40(void* src);

void func_00138398(void* src, s32* count, Item_138398** out)
{
    s32 n = ReadBufferedU16(src);
    *count = n;
    *out = (Item_138398*)AllocateZeroedFrontMemory(n << 5);

    for (s32 i = 0; i < *count; i++) {
        Item_138398* item = &(*out)[i];
        ReadBufferedVector3(src, item);
        item->f10 = ReadBufferedFloat(src);

        s32 v = ReadBufferedU32(src);
        if ((v & 0x80000000) != 0) {
            item->f14 = v;
        } else {
            item->f14 = (s32)((*out) + v);
        }
        v = ReadBufferedU32(src);
        if ((v & 0x80000000) != 0) {
            item->f18 = v;
        } else {
            item->f18 = (s32)((*out) + v);
        }
    }
}

void* func_0018D500(s32 size);
void func_001384A0(void* self, u8** out)
{
    s32 size = ReadBufferedU16(self);
    u8* buffer = (u8*)AllocateFrontMemory(size + 1);
    ReadBufferedStreamBytes(self, size, buffer);
    buffer[size] = 0;
    *out = buffer;
}

LINKER_REMNANT(func_00138510);

extern f32 D_0026185C;


void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);


s32 func_00137BE0(void* src);
void func_00137A60(void* self, s32 size, void* obj);

void func_00138518(void* self)
{
    s32 n = ReadBufferedU16(self);
    ReadBufferedStreamBytes(self, n, 0);
}

struct Range_138550 {
    s32 w[8];
};

void func_00137A60(void* self, s32 size, void* obj);
u32 func_0018D568(s32 size, void* src);

void func_00138550(void* self, u32* out)
{
    Range_138550 r;
    ReadBufferedStreamBytes(self, 0x20, &r);
    if (r.w[1] != r.w[7]) {
        *out = CopyToFrontMemory(0x20, &r);
    } else {
        *out = 0;
    }
}

void func_001B7968(Collider* self);


struct Link_1385A0 { s32 f0; s32 f4; Link_1385A0* f8; Collider* fC; };

Link_1385A0* func_00138738(World* w, s32 a, s32 b);
Link_1385A0* func_00138788(World* w, s32 a, s32 b);
void func_001861E8(World* w, s32 a);
void func_00129DF8(Collider* e);
void func_001B5F28(u8* w, Link_1385A0* l);

void func_001385A0(World* w, s32 a, s32 b, u8 set, u8 clr) {
    Link_1385A0* n1;
    Link_1385A0* n2;
    s32 ia = (a - (s32)w->tables) >> 4;
    s32 ib = (b - (s32)w->tables) >> 4;
    u8* p = (u8*)w->buf1ADC + (ia << 8) + ib;
    u8* q = (u8*)w->buf1ADC + (ib << 8) + ia;
    u8 v = (set | *p) & ~clr;
    *q = v;
    *p = v;
    if ((v & 0xF) == 0xF || (v & 0x40)) {
        if (v & 0x80) return;
        u8 v2 = v | 0x80;
        *p = v2;
        *q = v2;
        n1 = PushContactRow(w, a, b);
        n2 = PushContactRow(w, b, a);
        n1->f8 = n2;
        n2->f8 = n1;
    } else if (v & 0x80) {
        u8 v2 = v & 0x7F;
        *p = v2;
        *q = v2;
        n1 = UnlinkContactRow(w, a, b);
        n2 = UnlinkContactRow(w, b, a);
        if (n1->f0) {
            u64 m = (u64)0x8000 << 40;
            FreePooledContactChain(w, n1->f0);
            if (!(n1->fC->flags538 & m)) func_00129DF8(n1->fC);
            if (!(n2->fC->flags538 & m)) func_00129DF8(n2->fC);
        }
        PushFreeSlot((u8*)w + 0x1AF0, n1);
        PushFreeSlot((u8*)w + 0x1AF0, n2);
    }
}

struct Node_138738 { s32 a0; Node_138738* next; void* a8; s32 value; };
struct List_138738 { Node_138738* head; };
struct Src_138738 { u8 pad0[4]; s32 value4; };

void* func_001B5EC0(void* pool);

Node_138738* func_00138738(World* self, List_138738* list, Src_138738* src)
{
    Node_138738* n = (Node_138738*)func_001B5EC0((u8*)self + 0x1AF0);
    n->a0 = 0;
    n->value = src->value4;
    n->next = list->head;
    list->head = n;
    return n;
}

ContactRow03* func_00138788(void* unused, ContactRow03** head, Contacts03* key)
{
    ContactRow03* node = *head;
    Collider* wanted = key->owner;
    while (node) {
        if (node->other == wanted) {
            *head = node->next;
            break;
        }
        head = &node->next;
        node = node->next;
    }
    return node;
}

void* func_001387C0(Collider* self, Collider* other)
{
    ContactRow03* cur = self->root03()->contacts->head;
    PlacedObject* key = other->root;
    if (cur != 0) {
        do {
            if (cur->other != key) {
                cur = cur->next;
            } else {
                return cur;
            }
        } while (cur != 0);
    }
    return 0;
}

void* func_001387C0(void* self, void* other);

s32 func_001387F8(void* self, void* other)
{
    s32* p = (s32*)FindContactRow(self, other);
    s32 r = 0;
    if (p != 0) {
        r = *p;
    }
    return r;
}

struct Slot_138828 {
    s32 flag;
    void* owner;
    void* link;
};

void func_001389C8(void* self);

void func_00138828(World* self, void* arg)
{
    World* t = self;
    s32 stride = 24;
    s32 one = 1;
    u8* a3 = (u8*)arg + 0x430;
    u8* a2 = (u8*)arg + 0x420;
    s32 off = 0;
    s32 n = 2;
    do {
        n--;
        Slot_138828* e = (Slot_138828*)((u8*)t->buf1AD8 + off + t->count38 * stride);
        off += 0x1800;
        e->link = a2;
        e->flag = 0;
        e->owner = arg;
        a2 += 4;
        e++;
        e->link = a3;
        e->owner = arg;
        e->flag = one;
        a3 += 4;
    } while (n >= 0);
    func_001389C8(self);
}

INCLUDE_ASM(func_001388A0);

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "c8b.h"
#include "v24a0.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"

void func_001389C8(World* a0)
{
    a0->f1AEC = 0;
}

INCLUDE_ASM(func_001389D0);

void func_00138BE0(void* a0, Collider* owner, u32 mask)
{
    Collider* n = owner->root03();
    if (n) {
        n->f4B8 &= ~mask;
    }
}

struct Obj_138C00;
struct Child_138C00;

struct Vtbl_138C00
{
    u8 pad0[0x10C];
    void (*f10C)(Child_138C00* c);
    void (*f110)(Child_138C00* c);
};

struct Child_138C00
{
    Vtbl_138C00* vt;
    u8 pad[0x2E4 - 4];
    Child_138C00* next;
};

struct Pair_138C00
{
    Contact03* prev;
    Contact03* it;
};

struct Slot_138C00
{
    Contact03* f0;
};

struct Node_138C00
{
    Contact03* f0;
    Node_138C00* f4;
    Slot_138C00* f8;
    Obj_138C00* fC;
};

struct List_138C00
{
    Node_138C00* head;
};

struct Obj_138C00
{
    u8 pad0[0x2C8];
    u64 bits2C8;
    u8 pad1[0x2D8 - 0x2D0];
    Child_138C00* children;
    u8 pad2[0x414 - 0x2DC];
    Obj_138C00* next;
    u8 pad3[0x480 - 0x418];
    List_138C00* list;
    u8 pad4[0x4B8 - 0x484];
    s32 kind;
    u8 pad5[0x538 - 0x4BC];
    u64 bits538;
};

void func_001389D0(World* w);
void func_001861E8(World* w, Contact03* item);
Contact03* func_00188270(World* w, Obj_138C00** pair, s32 arg);
void func_001860A8(World* w, s32 one, Contact03** item);
void func_00129DF8(Obj_138C00* o);

void func_00138C00(World* w, s32 arg)
{
    Obj_138C00* pair[2];
    Obj_138C00* o;
    Child_138C00* ch;
    func_001389D0(w);
    for (o = (Obj_138C00*)w->list6C.head; o; o = o->next)
    {
        pair[0] = o;
        if (o->kind == 7)
        {
            continue;
        }
        if (o->bits538 & (0x8000ull << 27))
        {
            continue;
        }
        o->bits538 |= 0x8000ull << 46;
        Node_138C00* node = pair[0]->list->head;
        for (; node; node = node->f4)
        {
            s32 dead = 7;
            u64 linked = 0x8000ull << 22;
            u64 visited = 0x8000ull << 27;
            u64 marked = 0x8000ull << 46;
            pair[1] = node->fC;
            if (pair[1] < pair[0] && pair[1]->kind != dead && (pair[1]->bits2C8 & linked))
            {
                continue;
            }
            if (pair[1]->bits538 & visited)
            {
                continue;
            }
            pair[1]->bits538 |= marked;
            if (((pair[0]->kind ^ 1) & 1) || ((pair[1]->kind ^ 1) & 1))
            {
                Contact03* old = node->f0;
                if (old)
                {
                    FreePooledContactChain(w, old);
                }
                Contact03* nw = func_00188270(w, pair, arg);
                node->f0 = nw;
                node->f8->f0 = nw;
                if ((old == 0) != (node->f0 == 0))
                {
                    if (!(pair[0]->bits538 & (0x8000ull << 40)))
                    {
                        func_00129DF8(pair[0]);
                    }
                    if (!(pair[1]->bits538 & (0x8000ull << 40)))
                    {
                        func_00129DF8(pair[1]);
                    }
                }
            }
            else
            {
                Pair_138C00 p;
                for (p.it = node->f0; p.it; p.it = p.it->next)
                {
                    func_001860A8(w, 1, &p.it);
                }
            }
        }
    }
    for (o = (Obj_138C00*)w->list6C.head; o; o = o->next)
    {
        if (o->kind & 4)
        {
            continue;
        }
        for (ch = o->children; ch; ch = ch->next)
        {
            if (ch->vt->f110)
            {
                ch->vt->f110(ch);
            }
        }
        o->bits538 |= 0x8000ull << 46;
    }
    for (o = (Obj_138C00*)w->list6C.head; o; o = o->next)
    {
        if (o->bits538 & (0x8000ull << 46))
        {
            for (ch = o->children; ch; ch = ch->next)
            {
                if (ch->vt->f10C)
                {
                    ch->vt->f10C(ch);
                }
            }
            o->bits538 &= ~(0x8000ull << 46);
        }
        o->kind = 7;
    }
}

void func_001385A0(World* a0, s32 a1, Contacts03* a2, s32 a3, s32 a4);

void func_00138F28(World* self, Collider* obj)
{
    obj->f4B8 = 0;
    Contacts03* n = self->usedTables;
    while (n != 0) {
        if (n->owner != obj) {
            s32 s2 = 0;
            if (obj->desc03()->m38(obj, n->owner) || n->owner->desc03()->m38(n->owner, obj)) {
                s2 = 1;
            }
            SetContactPairFlags(self, (s32)obj->contacts, n, s2 == 0 ? 8 : 0, s2 ? 8 : 0);
        }
        n = n->next;
    }
}

void func_00138FF0(s32 a, s32 b, s32 c, s32 d)
{
    s32 i;
    for (i = 0; i < (a < c ? a : c); i++) {
    }
}

struct Track_139038 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; };
struct Grp_139038 {
    s32 key; Track_139038* a; Track_139038* b; s32 fC; Track_139038* c; s32 n; Track_139038** d;
};
struct Src_139038 {
    u8 pad0[0x38]; s32 count; Grp_139038* grps; u8 pad40[4]; s32 f44;
    u8 pad48[0x54 - 0x48]; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64; s32 f68;
    u8 pad6C[0x78 - 0x6C]; s32 f78; f32 f7C;
};
struct Item_139038 { s32 f0; Src_139038* src; };
struct Key_139038 { s32 f0; s32 f4; void* f8; };
struct Anim_139038;
typedef void (*VFn_139038)(Anim_139038*);
struct Anim_139038 {
    VFn_139038* vtbl; u8 pad4[0x34]; s32 count; Grp_139038* grps; u8 pad40[4]; s32 f44;
    u8 pad48[0x54 - 0x48]; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64; s32 f68;
    u8 pad6C[0x78 - 0x6C]; s32 f78; f32 f7C;
    u8 pad80[0xB0 - 0x80]; s32 stride; s32 nitems; void* data; s32 nkeys; Key_139038* keys;
};

void func_0018D608(void);
void func_0018D6F0(void);
Anim_139038* func_0011E580(s32 kind, s32 a, Collider* ctx, s32 b, s32 c);
void* func_0018D500(s32 size);
void* func_0018D5C0(s32 size);
Grp_139038* func_0018D6A8(s32 size);
Grp_139038* func_0018D568(s32 size, Grp_139038* src);
Track_139038* func_00120FB0(s32 kind);
Track_139038* func_00121050(s32 kind);
Track_139038* func_00121160(s32 kind);
void func_00138FF0(s32 a, s32 b, s32 c, s32 d);

void func_00139038(Collider* ctx, s32 stride, s32 count, u8* items, s32 nkeys, s32* keyA, s32* keyB, Anim_139038** out)
{
    s32 i;
    Item_139038* item;
    Grp_139038* buf;
    for (i = 0; ; i++) {
        if (i >= count) {
            *out = 0;
            return;
        }
        item = (Item_139038*)(items + i * stride);
        if (item->src != 0) break;
    }
    Src_139038* src = item->src;
    PushBackMemoryMark();
    Anim_139038* anim = CreateTypedRecord(0x84, (s32)ctx->world, ctx, -1, -1);
    anim->vtbl[7](anim);
    anim->nitems = count;
    anim->stride = stride;
    anim->data = AllocateFrontMemory(count * stride);
    anim->nkeys = nkeys;
    anim->keys = (Key_139038*)AllocateFrontMemory(nkeys * 12);
    for (s32 k = 0; k < nkeys; k++) {
        Key_139038* key = &anim->keys[k];
        key->f0 = keyA[k];
        key->f4 = keyB[k];
        key->f8 = AllocateFrontMemory(key->f4 << 3);
    }
    s32 total = 0;
    for (i = 0; i < count; i++) {
        item = (Item_139038*)(items + i * stride);
        if (item->src != 0) total += item->src->count;
    }
    buf = AllocateZeroedBackMemory(total * 0x1C);
    s32 used = 0;
    for (i = 0; i < count; i++) {
        item = (Item_139038*)(items + i * stride);
        if (item->src == 0) continue;
        for (s32 j = 0; j < item->src->count; j++) {
            Grp_139038* g = &item->src->grps[j];
            if (g->a == 0 && g->b == 0 && g->c == 0 && g->d == 0) continue;
            Grp_139038* e;
            for (s32 m = 0; m < used; m++) {
                e = &buf[m];
                if (g->key == e->key) goto have;
            }
            e = &buf[used++];
            e->key = g->key;
        have:
            if (g->a != 0) {
                if (e->a == 0) {
                    Track_139038* t = CreatePositionCurve(2);
                    t->fC = (s32)anim;
                    t->f10 = (s32)anim->keys;
                    t->f14 = (s32)AllocateZeroedFrontMemory(count << 2);
                    t->f8 = 1;
                    e->a = t;
                }
                if (g->a->f8 == 0) e->a->f8 = 0;
                ((Track_139038**)e->a->f14)[i] = g->a;
            }
            if (g->b != 0) {
                if (e->b == 0) {
                    Track_139038* t = CreateRotationCurve(2);
                    t->fC = (s32)anim;
                    t->f10 = (s32)anim->keys;
                    t->f14 = (s32)AllocateZeroedFrontMemory(count << 2);
                    t->f8 = 1;
                    e->b = t;
                }
                if (g->b->f8 == 0) e->b->f8 = 0;
                ((Track_139038**)e->b->f14)[i] = g->b;
            }
            if (g->c != 0) {
                if (e->c == 0) {
                    Track_139038* t = CreateWeightCurve(3);
                    t->f8 = (s32)anim;
                    t->fC = (s32)anim->keys;
                    t->f10 = (s32)AllocateZeroedFrontMemory(count << 2);
                    e->c = t;
                }
                ((Track_139038**)e->c->f10)[i] = g->c;
            }
            if (g->d != 0) {
                if (e->d == 0) {
                    e->n = g->n;
                    e->d = (Track_139038**)AllocateZeroedFrontMemory(g->n << 2);
                }
                for (s32 q = 0; q < g->n; q++) {
                    Track_139038* v = g->d[q];
                    if (v != 0) {
                        Track_139038* t = e->d[q];
                        if (t == 0) {
                            Track_139038* nt = CreateWeightCurve(4);
                            nt->f8 = (s32)anim;
                            nt->fC = (s32)anim->keys;
                            nt->f10 = (s32)AllocateZeroedFrontMemory(count << 2);
                            nt->f14 = q;
                            e->d[q] = nt;
                            t = nt;
                        }
                        ((Track_139038**)t->f10)[i] = v;
                    }
                }
            }
        }
    }
    anim->count = used;
    anim->grps = CopyToFrontMemory(used * 0x1C, buf);
    anim->f44 = src->f44;
    anim->f78 = src->f78;
    anim->f7C = src->f7C;
    anim->f54 = src->f54;
    anim->f58 = src->f58;
    anim->f64 = src->f64;
    anim->f68 = src->f68;
    if (nkeys == 0) {
        anim->f5C = src->f5C;
        anim->f60 = src->f60;
        func_00138FF0(anim->f5C, anim->f60, src->f5C, src->f60);
    }
    *out = anim;
    PopBackMemoryMark();
}

struct Obj_139600 { u8 pad0[0x34]; f32 f34; };
struct Elem_139600 { s32 w0; Obj_139600* p4; };
struct Pair_139600 { f32 a; f32 b; };

f32 func_0012CCC0(Obj_139600* a, s32 b);

void func_00139600(s32 stride, s32 count, u8* base, s32 off, s32 count2, s32* vals)
{
    s32 i;
    for (i = 0; i < count; i++) {
        Elem_139600* e = (Elem_139600*)(base + i * stride);
        if (e->p4 == 0) {
            continue;
        }
        Pair_139600* s1 = (Pair_139600*)((u8*)e + off);
        Pair_139600* s5 = s1;
        s32 n;
        s32 bytes = count2 * 8;
        if (count2 > 0) {
            s32* v = vals;
            n = count2;
            do {
                n--;
                s1->a = func_0012CCC0(e->p4, *v);
                v++;
                s1++;
            } while (n != 0);
        }
        s1 = s5;
        Pair_139600* prev = (Pair_139600*)((u8*)s1 + (bytes - 8));
        if (count2 > 0) {
            n = count2;
            do {
                f32 d = s1->a - prev->a;
                prev->b = d;
                if (d < 0.0f) {
                    prev->b = d + e->p4->f34;
                }
                prev = s1;
                n--;
                s1++;
            } while (n != 0);
        }
    }
}

INCLUDE_ASM(func_00139740);

struct Pair_139970 { f32 a; f32 b; };

s32 func_00139970(s32 count, Pair_139970* p, f32 x, f32 period, f32* out)
{
    s32 i;
    for (i = 0; i < count; p++, i++) {
        if (p->b != 0.0f) {
            f32 d = x - p->a;
            if (d < 0.0f) {
                d += period;
            }
            if (d < p->b + 0.0001f) {
                if (out != 0) {
                    *out = d;
                }
                break;
            }
        }
    }
    return i;
}

LINKER_REMNANT(func_001399F0);

#include "list_iter.h"

struct Node_1399F8 { u8 pad0[0x14]; f32 f14; u8 pad18[0x3C - 0x18]; Node_1399F8* f3C; };
struct Ent_1399F8 { s32 a; s32 b; s32 c; };

void func_0018D800(void* a, void* b, s32 n);
void func_00139740(s32 a0, s32 a1, void* a2, s32 a3, s32 a4, s32 a5, void* a6);
void func_0012F1D8(void* node);

void func_001399F8(Gr8B* self, s32 a1, s32 a2, void* a3)
{
    Node_1399F8* node = (Node_1399F8*)self->f6C;
    s32 i;
    s32 count;
    Ent_1399F8* ent;
    ListFrame frame;

    if (node != 0) {
        do {
            node->f14 = node->f14 / self->f34;
            node = node->f3C;
        } while (node != 0);
    }
    CopyMemory(self->fB8, a3, a2 * a1);
    count = self->fBC;
    if (count == 0) {
        func_00139740(a1, a2, a3, 0, 0, 0, &self->f34);
    } else {
        for (i = 0; i < count; i++) {
            ent = (Ent_1399F8*)((u8*)self->pC0 + i * 12);
            func_00139740(a1, a2, a3, ent->a, ent->b, ent->c, &self->f34);
        }
    }
    node = (Node_1399F8*)self->f6C;
    if (node != 0) {
        do {
            node->f14 = node->f14 * self->f34;
            SettleListedPoseSources(node);
            node = node->f3C;
        } while (node != 0);
    }
}

struct Sub_139B38 { u8 pad[0x18]; s32 flag; };
struct Owner_139B38 { u8 pad[8]; Sub_139B38* sub; };

void* func_0012CCE8(void);

void func_00139B38(void)
{
    Owner_139B38* o = (Owner_139B38*)FindEntryByObjectId();
    if (o) {
        if (o->sub) {
            o->sub->flag = 1;
        }
    }
}

void* func_001611B8(V24A0* f);
void func_001528F0(V24A0* f, s32 n);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_001612F8(V24A0* f, s32 a, s32 b, s32 c, u64 d, s32 e);
void func_00152D70(V24A0* f);
void func_001529E0(V24A0* f, s32 a, void* b);

void func_00139B70(s32 idx, void* arg)
{
    V24A0 f;

    InitGifPacket(&f);
    AllocatePacketBuffer(&f, 4);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x47, 0x7180B);
    AddGifRegisterWrite(&f, 0x42, ((u64)(s64)idx << 2) | 0x40);
    ReserveGifPackedData(&f, 0x54, 0, 0xA, 0x424242412EULL, 0);
    CloseDmaTag(&f);
    DetachPacketBuffer(&f, 0, arg);
}


void func_00139B70(s32 idx, void* arg);

void func_00139C38(void)
{
    func_00139B70(1, &D_00261314);
    func_00139B70(2, &D_00261318);
}

struct Obj_139C70 { u8 pad0[0x14]; u8* ctx; u8 pad1[0x320 - 0x18]; s32 mode; };

void* func_001B5EA0(void* p);
void func_001B5F28(void* p, void* q);
void func_001F5C0C(void* p, s32 v, s32 n);
void func_00152470(void* list, void* item);

OwnedRecord* func_00139C70(Obj_139C70* o)
{
    OwnedRecord* s = (OwnedRecord*)PopFreeSlot(o->ctx + 0x1B40);
    if (!s) {
        return 0;
    }
    func_001F5C0C(s, 0, 0x10C0);
    if (o->mode != 2) {
        s->owner = o;
    } else {
        void* r = PopFreeSlot(o->ctx + 0x1B4C);
        s->extraRecord = r;
        if (r) {
            func_001F5C0C(r, 0, 0x580);
            s->owner = o;
        } else {
            PushFreeSlot(o->ctx + 0x1B40, s);
            return 0;
        }
    }
    AppendToList((u8*)o + 0x624, s);
    return s;
}

struct Sub_139D28 { u8 pad[0x108C]; struct Obj_139D28* owner; };
struct Obj_139D28 { u8 pad[0x1]; };


void func_00152600(void* list, void* item);
void func_00152470(void* list, void* item);

void func_00139D28(Sub_139D28* o)
{
    RemoveFromList((u8*)o->owner + 0x624, o);
    AppendToList(&D_002622F0, o);
}

typedef void (*VFn_139D68)(void* self);

struct Obj_139D68 {
    VFn_139D68* vtbl;
    u8 pad04[0x80 - 4];
    f32 f80;
    u8 pad84[0x2C8 - 0x84];
    u64 bits2C8;
    s32 w2D0;
    u8 pad2D4[0x620 - 0x2D4];
    s32 w620;
};

struct Outer_139D68 {
    u8 pad0[0x1CC0];
    Obj_139D68* obj1CC0;
};

Obj_139D68* func_00139D68(Outer_139D68* self)
{
    Obj_139D68* s0 = self->obj1CC0;
    if (s0 != 0) {
        u64 b = ((s0->bits2C8 & 0xFFFFFFFFF3FFFFFFull) | 0x08000000ull) & 0xFFFFFFFFCFFFFFFFull | 0x20000000ull;
        s0->w2D0 = 0;
        s0->f80 = 1e10f;
        s0->bits2C8 = b;
        s0->w620 = 0;
        s0->vtbl[6](s0);
    }
    return s0;
}

void func_00127378(ChildGroupObject* self, s32 kind, ObjectMessage* msg);
void func_0013BE00(ChildGroupObject* p, f32 delta);


void func_00152470(void* list, void* item);
void func_00152438(void* self, s32 value);
void func_00123ED0(void* self);

void func_00139DE8(WorldListedObject* self)
{
    AppendToList(&self->world->list1CC0, self);
    InitPlacedObject(self);
    SetListLinkOffset(&self->members, 0x1090);
    u64 b = self->flags;
    b &= 0xFFFFFFFFCFFFFFFFull;
    b |= 0x20000000ull;
    b &= 0xFFFFFCFFFFFFFFFFull;
    self->f80 = 1e10f;
    b |= 0x10000000000ull;
    self->flags = b;
}

void func_00152600(void* sub, void* self);
void func_00152470(void* sub, void* self);
void func_001240F8(void* self);

void func_00139E80(WorldListedObject* self)
{
    RemoveFromList(&self->world->list1CC0, self);
    AppendToList(&self->world->list1CB4, self);
    RegisterPlacedObject(self);
}

void func_00139D28(void* a);
void func_00152600(u8* a, void* b);
void func_00152470(u8* a, void* b);
void func_001243E0(void* self);

struct Frame_139EC8 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_00139EC8(WorldListedObject* self)
{
    WorldListedObject* obj = self;
    Frame_139EC8 fr;
    s32 e = (s32)&obj->members.head;
    fr.list = e;
    fr.cursor = e;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.link = link;
    *(s32*)&g_activeListFrames = (s32)&fr;
    s32 head = obj->members.head;
    fr.cursor = head + fr.link;
    s32 node = head;
    while (node != 0) {
        DetachOwnedRecord((void*)node);
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        node = nx;
    }
    RemoveFromList(&obj->world->list1CB4, self);
    AppendToList(&D_002622E0, self);

    UnregisterPlacedObject(self);
    *(s32*)&g_activeListFrames = fr.prev;
}

struct Obj_139F80 { u8 pad0[0x380]; s32 f380; u8 pad1[0x20C]; s32 f590; u8 f594[4]; };

extern s32 D_002744FC;
s32 func_001B4688(void* x);
void func_0013A008(Obj_139F80* self);

void func_00139F80(Obj_139F80* self, void* x)
{
    s32 r = FindAnimRecord(x);
    self->f380 = r;
    if (r == 0) {
        self->f380 = g_animRecords;
    }
    if (self->f590 == 0) {
        self->f590 = 1;
        s32 i = 0;
        u8* dst = self->f594;
        do {
            u8* src = (u8*)self->f380 + i;
            dst[i] = (u8)((src[4] + 1) >> 1);
            i++;
        } while (i < 4);
    }
    func_0013A008(self);
}

s32 func_00185D20(void*, s32, void*, void*, s32, s32, s32, void*, f32);


struct __attribute__((aligned(16))) Entry_13A008 {
    u64 value;
    s32 tag;
    s32 pad;
};

struct StateB_13A008 {
    u8 pad0[0x4];
    u8 bits4;
};

struct StateA_13A008 {
    u8 pad0[0x14];
    StateB_13A008* p14;
};

struct Ctx_13A008 {
    u8 pad0[0x380];
    StateA_13A008* p380;
    s32 a384;
    u8 pad388[0x8];
    Entry_13A008 entries[1];
};

u64 func_001B2988(void* t, s32 i, s32 j);

void func_0013A008(Ctx_13A008* self)
{
    StateB_13A008* blk = self->p380->p14;
    s32 a = 1;
    s32 s4 = 0;
    s32 t = blk->bits4 >> 1;
    s32 b;
    s32 i;
    Entry_13A008* e;

    while (t != 0) {
        t >>= 1;
        a <<= 1;
    }
    a = a << (a < blk->bits4);
    while (a >= 0x20) {
        a >>= 1;
    }
    b = blk->bits4;
    if (b < a) {
        s4 = a - blk->bits4;
    }
    self->a384 = a;
    e = self->entries;
    for (i = 0; i < b; i++) {
        e->value = GetTextureRegisterBits(blk, i, 0);
        e->tag = 6;
        if (i < s4) {
            e[1] = *e;
            e++;
        }
        e++;
    }
}

ASM_FUNC(func_0013A128);

void func_00124FC0(void* self);
void func_00129DF8(void* self);

void func_0013A3A0(WorldListedObject* self)
{
    UpdatePlacedObject(self);
    func_00129DF8(self);
    FlagRecord* sub = self->flagRecord;
    Camera* g = g_camera;
    s32 hit = 0;
    u32 flags = sub->flags;
    u32 mask = g->f21C;

    if ((flags & 0x10000000) != 0 || (mask & flags) == mask)
        hit = 1;
    if (hit == 0)
        self->desc->m03(self);
}

void func_001832F0(WorldListedObject* self, BaseObject* src);
s32 func_001300E8(BaseObject* src, s32 kind);
s32 func_00152720(void* sub);

void func_0013A418(WorldListedObject* self, BaseObject* src)
{
    AddObjectListener(self, src);
    if (IsObjectOfKind(src, 0x50) != 0) {
        EffectSpawner* from = (EffectSpawner*)src;
        self->source = from;
        self->f80 = from->f80;
        if (IsListEmpty(from->list314) == 0) {
            self->flags &= 0xFFFFFFFFF3FFFFFFULL;
            self->flags &= 0xFFFFFFFFCFFFFFFFULL;
        }
    }
}

ASM_FUNC(func_0013A498);

// The bounds the assembly func_0013A618 and func_0013A940 start from: the file's .rodata.
extern const f32 D_00249D64 = 3.4028235e+38f;
extern const f32 D_00249D68 = -3.4028235e+38f;
extern const f32 D_00249D6C = 3.4028235e+38f;
extern const f32 D_00249D70 = -3.4028235e+38f;

ASM_FUNC(func_0013A618);

ASM_FUNC(func_0013A940);

struct ParamBlock_13AD08 { void (*fn)(void* self); s32 zero; s32 count; u8 pad0[0x50 - 0x0C]; f32 radius; u8 pad1[0x60 - 0x54]; void* owner; u8 pad2[0x80 - 0x64]; };
struct Src_13AD08 { u8 pad[0x40]; f32 scale; };

void* func_001F5C0C(void* dst, s32 value, u32 size);
void func_0019D410(void* block);
void func_0013AD80(void* self);

void func_0013AD08(WorldListedObject* owner, s32 unused, Src_13AD08* src)
{
    ParamBlock_13AD08 blk;
    func_001F5C0C(&blk, 0, (u32)0x80);
    blk.count = 0xF;
    blk.fn = func_0013AD80;
    blk.zero = 0;
    if (src != 0) {
        blk.radius = src->scale;
    } else {
        blk.radius = 1.0f;
    }
    blk.owner = owner;
    QueueDeferredRequest(&blk);
}

ASM_FUNC(func_0013AD80);

// NEAR: frame and loop shape right; retail tests the call condition as a 0/1 value (li a0,1 / beqzl) and orders registers differently

struct Sub_13B430 { u8 pad0[0xC]; s32 next_0C; };
struct Node_13B430 { u8 pad0[0x380]; Sub_13B430* sub_380; u8 pad1[0x630 - 0x384]; Node_13B430* next_630; };


void func_0013A008(Node_13B430* node);

void func_0013B430(s32 mask)
{
    Node_13B430* node;
    s32 v;
    s32 go;
    ListFrame frame;

    if (mask != 0) {
        node = (Node_13B430*)g_currentWorld->list1CB4.head;

        if (node != 0) {
            do {
                v = node->sub_380->next_0C;
                go = 0;
                if ((v & 0x10000000) != 0 || (mask & v) == mask) {
                    go = 1;
                }
                if (go) {
                    func_0013A008(node);
                }
                node = node->next_630;
            } while (node != 0);
        }
    }
}
