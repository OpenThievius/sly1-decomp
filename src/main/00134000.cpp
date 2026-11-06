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

void func_00137398(BufferedStream* self, s32 a1, s32 a2) { self->remaining = a1; self->ptr = a2; self->mode = 2; }

void func_00137E90(void* self, void* out) { ReadBufferedStreamBytes(self, 0x10, out); }

void func_00137EB0(void* self, u8* buffer)
{
    ReadBufferedStreamBytes(self, 0xC, buffer);
    ReadBufferedStreamBytes(self, 0xC, buffer + 0x10);
    ReadBufferedStreamBytes(self, 0xC, buffer + 0x20);
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

extern f32 D_0026185C;

void func_001BFCD8(s32 a, s32 b, s32 c, s32 d, f32 g, f32 h, f32 i, f32 j, f32 k, s32 e, s32 f);

extern u8 D_00275710[];
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

extern u8 D_00275710[];

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

