// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

#include "t2196.h"

#include "world.h"

#include "entry_pool.h"

#include "buffered_stream.h"

#include "script_value.h"

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr)
{
    s32 hi = n;
    s32 lo = 1;

    if (n != 1)
    {
        do
        {
            s32 mid = (hi + lo) / 2;
            f32 v = *(f32*)(base + stride * mid);
            if (key < v)
            {
                hi = mid;
            }
            else
            {
                lo = mid + 1;
            }
        } while (lo != hi);
    }

    if (lo >= n)
    {
        lo = n - 1;
    }
    s32 exact = flags & 1;
    lo = lo - 1;
    u8* p = base + stride * lo;

    if (exact)
    {
        if (*(f32*)p == key)
        {
            p = p - stride;
            if (p < base)
            {
                p = p + (n - 1) * stride;
                key = *(f32*)(p + stride);
            }
        }
    }

    if (outDiff != 0)
    {
        *outDiff = key - *(f32*)p;
    }
    if (outDelta != 0)
    {
        *outDelta = *(f32*)(p + stride) - *(f32*)p;
    }
    *outPtr = p;
}

void func_0011EF88()
{
}

void* func_0018D658(s32 size);

void func_0011F180(T2196_668* src, s32* outCount, f32** outValues)
{
    *outCount = src->count;
    if (outValues != 0)
    {
        *outValues = (f32*)AllocateBackMemory(*outCount << 2);
        for (s32 i = 0; i < *outCount; i++)
        {
            (*outValues)[i] = src->keys[i].time;
        }
    }
}

void* func_0018D658(s32 size);

void func_0011F620(T2196_688* self, s32* count, f32** out)
{
    s32 n = self->count;
    *count = n;
    if (out != 0) {
        *out = (f32*)AllocateBackMemory(n * 4);
        for (s32 i = 0; i < *count; i++) {
            (*out)[i] = self->keys[i].time;
        }
    }
}

void func_0011F850(T2196_Weight** axis, s32* outCount, f32** outTimes);

void func_0011FDB8(T2196_6B8* self, s32* outCount, f32** outTimes)
{
    GatherAxisCurveTimes(self->axis, outCount, outTimes);
}

void func_00109488(void);

void func_0011E560(void)
{
    func_00109488();
}

extern u8 D_002505D8[];

void func_0011E680(void* self, void* slot, void* obj);

s32 func_00137D10(void* p);

void func_0011EC40(void* self, void* obj)
{
    s32 r;
    while ((r = ReadBufferedS16(obj)) >= 0) {
        ApplyPropertyRecord(self, D_002505D8 + (r << 5), obj);
    }
}

s32 func_0011ECA0(s32 value)
{
    s32 r = value - 12;
    return ((u32)30 < (u32)r) ? -1 : r;
}

void func_0011EF40(void)
{
}

void func_0011EF48(T2196_Pos* unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0) {
        *b = 0;
    }
}

void func_0011EF60(void)
{
}

void* func_0018D658(s32 size);

void func_0011FB98(s32 count, Key2196_Vec* src, s32* outCount, f32** outArr)
{
    *outCount = count;
    if (outArr) {
        *outArr = (f32*)AllocateBackMemory(count * 4);
        s32 i = 0;
        if (*outCount > 0) {
            Key2196_Vec* p = src;
            do {
                (*outArr)[i] = p->time;
                p++;
                i++;
            } while (i < *outCount);
        }
    }
}

// The owner's slot 44 (Desc02::m28) is told what was asked.
typedef void (*Hook_11FC20)(PlacedObject* self, s32 a, s32 b);

void func_0011F6B0(T2196_Weight** a, PlacedObject* b, s32 c, Vec02* d, s32 e, s32 f, f32 g, f32 h);

void func_0011FC20(T2196_6B8* self, PlacedObject* other, s32 c, s32 e, s32 f, f32 p12, f32 p13)
{
    func_0011F6B0(self->axis, other, c, &self->base, e, f, p12, p13);
    if (other && other->desc02()->m28)
        ((Hook_11FC20)other->desc02()->m28)(other, e, f);
}

void func_0011F9F8(s32 a, s32 b, s32 c, s32 d, s32 e, f32 g, f32 h);

void func_0011FDD8(T2196_6C8* self, PlacedObject* other, s32 a2, s32 a3, s32 a4, f32 p12, f32 p13)
{
    EvaluateVectorKeyCurve(self->count, (s32)self->keys, a2, a3, a4, p12, p13);
    if (other && other->desc02()->m28)
        ((Hook_11FC20)other->desc02()->m28)(other, a3, a4);
}

void func_0011FB98(s32 count, Key2196_Vec* src, s32* outCount, f32** outArr);

void func_0011FED8(T2196_6C8* self, s32* outCount, f32** outArr)
{
    GetVectorKeyTimes(self->count, self->keys, outCount, outArr);
}

void func_0011EFB0(T2196_Weight* unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0)
        *b = 0;
}

s32 func_00137BE0(void* src);

s32 func_00137D10(void* src);

f32 func_00137DF8(void* src);

s32 func_00137CC0(void* src);

void* func_0018D500(s32 size);

void func_0011EFC8(T2196_668* self, Stream83* src)
{
    self->count = ReadBufferedU16(src);
    self->keys = (Key2196_668*)AllocateFrontMemory(0x18 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        Key2196_668* e = self->keys + i;
        e->time = (f32)ReadBufferedS16(src) * 0.016666668f;
        e->value = ReadBufferedFloat(src);
        e->c = ReadBufferedS8(src);
        e->kind = ReadBufferedS8(src);
        e->d = ReadBufferedFloat(src);
        e->f = ReadBufferedFloat(src);
    }
}

s32 func_00137BE0(void* src);

s32 func_00137D10(void* src);

f32 func_00137DF8(void* src);

s32 func_00137CC0(void* src);

void* func_0018D500(s32 size);

void func_0011F210(T2196_678* self, Stream83* src)
{
    self->count = ReadBufferedU16(src);
    self->keys = (Key2196_678*)AllocateFrontMemory(0x20 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        Key2196_678* e = self->keys + i;
        e->time = (f32)ReadBufferedS16(src) * 0.016666668f;
        e->value = ReadBufferedFloat(src);
        e->c = ReadBufferedS8(src);
        e->kind = ReadBufferedS8(src);
        e->d = ReadBufferedFloat(src);
        f32 t = ReadBufferedFloat(src);
        e->e = e->value - t;
        e->g = ReadBufferedFloat(src);
        f32 u = ReadBufferedFloat(src);
        e->h = e->value + u;
    }
}

void* func_0018D658(s32 size);

void func_0011F3E8(T2196_678* self, s32* outCount, f32** outArr)
{
    s32 n = self->count;
    *outCount = n;
    if (outArr) {
        s32 i;
        *outArr = (f32*)AllocateBackMemory(n * 4);
        i = 0;
        if (*outCount > 0) {
            do {
                (*outArr)[i] = self->keys[i].time;
                i++;
            } while (i < *outCount);
        }
    }
}

s32 func_00137B90(void* src);

void func_00137E70(void* src, void* dst);

T2196_Weight* func_00121160(s32 index);

void func_0011F798(T2196_Weight** out, Vec02* dst, Stream83* src)
{
    s32 mask = ReadBufferedU8(src);
    T2196_Weight** slot = out;
    ReadBufferedVector3(src, dst);
    s32 i = 2;
    do {
        s32 bit = mask & 1;
        mask >>= 1;
        if (bit) {
            T2196_Weight* o = CreateWeightCurve(ReadBufferedU8(src));
            void (*fn)(T2196_Weight*, Stream83*) = o->vt->read;
            if (fn)
                fn(o, src);
            *slot = o;
        }
        slot++;
        i--;
    } while (i >= 0);
}

struct Scratch_11F9F8 { f32 diff; f32 delta; u8* ptr; };

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);

void func_00130540(u8* a, u8* b, u8* c, u8* d, f32 f12, f32 f13, f32 f14, s32 a4, s32 a5, s32 a6);

void func_0011F9F8(s32 count, s32 base, s32 flags, s32 d, s32 e, f32 key, f32 scale)
{
    Scratch_11F9F8 s;
    FindCurveSegment(key, flags, 0x40, count, (u8*)base, &s.diff, &s.delta, &s.ptr);
    u8* p = s.ptr;
    func_00130540(p + 0x10, p + 0x30, p + 0x50, p + 0x60, s.delta, s.diff, scale, d, e, 0);
}

void func_0011EF68(void)
{
}

void func_0011EF70(T2196_Rot* self, s32* first, s32* second)
{
    *first = 0;
    if (second != 0) {
        *second = 0;
    }
}

s32 func_00137BE0(void* src);

s32 func_00137D10(void* src);

void func_00137E70(void* src, void* dst);

void* func_0018D500(s32 size);

void func_0011FA88(s32* outCount, Key2196_Vec** outItems, Stream83* src)
{
    s32 count = ReadBufferedU16(src);
    Key2196_Vec* items = (Key2196_Vec*)AllocateFrontMemory(count << 6);
    if (count > 0) {
        u8* p2 = (u8*)&items->v2;
        u8* p1 = (u8*)&items->v1;
        u8* p0 = (u8*)&items->v0;
        Key2196_Vec* it = items;
        s32 left = count;
        do {
            left--;
            it->time = (f32)ReadBufferedS16(src) * 0.016666668f;
            ReadBufferedVector3(src, p0);
            p0 += 0x40;
            ReadBufferedVector3(src, p1);
            p1 += 0x40;
            ReadBufferedVector3(src, p2);
            p2 += 0x40;
            it++;
        } while (left != 0);
    }
    *outCount = count;
    *outItems = items;
}

// The owner's slot 45 (Desc02::m29) is told what was asked.
typedef void (*Method_11FF08)(PlacedObject* self, void* a, void* b);

struct Scratch_11FF08 { s32 a[4]; s32 b[4]; };

void func_0011F6B0(T2196_Weight** a, PlacedObject* b, s32 c, Vec02* d, void* e, void* f);

void func_00188A20(void* a, void* b);

void func_001EDE38(void* a, void* b, void* c);

void func_0011FF08(T2196_6E8* self, PlacedObject* other, s32 c, void* p3, void* p4)
{
    Scratch_11FF08 tmp;
    func_0011F6B0(self->axis, other, c, &self->base, p3 ? (void*)&tmp : 0, p4 ? (void*)tmp.b : 0);
    if (p3)
        BuildEulerRotationMatrix(&tmp, p3);
    if (p4)
        RotateVectorByTwoAngles(&tmp, tmp.b, p4);
    if (other)
        ((Method_11FF08)other->desc02()->m29)(other, p3, p4);
}

void func_0011EFA8()
{
}

extern void* func_0011F6B0(void*, u32, u32, void*, u32, u32);

void* func_0011FFA8(T2196_6E8* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    return func_0011F6B0(self->axis, a1, a2, &self->base, a3, a4);
}

void func_0011EF90(T2196_Scale* a0, s32* a1, s32* a2)
{
    *a1 = 0;
    if (a2 != 0) {
        *a2 = 0;
    }
}

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);

void func_0011F478(T2196_688* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    FindCurveSegment(key, flags, 8, self->count, (u8*)self->keys, &diff, &delta, &p);
    if (delta < 0.0001f) {
        if (outF != 0) {
            *outF = ((Key2196_688*)p)->value;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    if (outF != 0) {
        f32 t = diff / delta;
        *outF = (1.0f - t) * ((Key2196_688*)p)->value + t * ((Key2196_688*)p + 1)->value;
    }
    if (outI != 0) {
        *outI = scale * (((Key2196_688*)p + 1)->value - ((Key2196_688*)p)->value) / delta;
    }
}

s32 func_00137BE0(void* src);

s32 func_00137D10(void* src);

f32 func_00137DF8(void* src);

void* func_0018D500(s32 size);

void func_0011F568(T2196_688* self, Stream83* src)
{
    self->count = ReadBufferedU16(src);
    self->keys = (Key2196_688*)AllocateFrontMemory(self->count << 3);
    for (s32 i = 0; i < self->count; i++) {
        Key2196_688* e = self->keys + i;
        e->time = (f32)ReadBufferedS16(src) * 0.016666668f;
        e->value = ReadBufferedFloat(src);
    }
}

struct Locals_11FFD8 {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    s32 count;
    f32* values;
    f32 first;
};

extern void func_0011F798(T2196_Weight**, Vec02*, Stream83*);

extern void func_00189150(void*, void*, void*);

extern void func_00188D28(void*, void*, void*);

extern void func_0018D608(void);

extern void func_0018D6F0(void);

void func_0011FFD8(T2196_6E8* self, Stream83* arg)
{
    Locals_11FFD8 loc;
    s32 result;

    ReadAxisCurves(self->axis, &self->base, arg);
    PushBackMemoryMark();
    self->vt->times(self, &loc.count, &loc.values);
    if (loc.count > 0) {
        self->vt->eval(self, 0, 0, loc.a, 0, loc.values[0], 1.0f);
        self->vt->eval(self, 0, 0, loc.b, 0, loc.values[loc.count - 1], 1.0f);
        func_00189150(loc.a, loc.b, loc.c);
        func_00188D28(loc.c, &loc.first, loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    } else {
        result = 1;
    }
    self->closed = result;
    PopBackMemoryMark();
}

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f18` and the `move $a0`); the argument setup is scheduled differently.

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);

void func_001303F0(f32 delta, f32 diff, f32 scale, f32 p4, f32 p14, f32 p1C, f32 p24, f32* outF, f32* outI, s32 zero);

void func_0011F0C8(T2196_668* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    FindCurveSegment(key, flags, 0x18, self->count, (u8*)self->keys, &diff, &delta, &p);
    if (((Key2196_668*)p)->kind == 5) {
        if (outF != 0) {
            *outF = ((Key2196_668*)p)->value;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    EvaluateHermiteSegment(delta, diff, scale, ((Key2196_668*)p)->value, ((Key2196_668*)p)->f, ((Key2196_668*)p + 1)->value, ((Key2196_668*)p + 1)->d, outF, outI, 0);
}

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f12` and the `move $a0`); the argument setup is scheduled differently.

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);

void func_00130168(f32 delta, f32 diff, f32 scale, f32 p4, f32 p18, f32 p1C, f32 p24, f32 p2C, f32 p30, f32* outF, f32* outI, s32 zero);

void func_0011F320(T2196_678* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    FindCurveSegment(key, flags, 0x20, self->count, (u8*)self->keys, &diff, &delta, &p);
    if (((Key2196_678*)p)->kind == 5) {
        if (outF != 0) {
            *outF = ((Key2196_678*)p)->value;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    SolveBezierSegment(delta, diff, scale, ((Key2196_678*)p)->value, ((Key2196_678*)p)->g, ((Key2196_678*)p)->h, ((Key2196_678*)p + 1)->value, ((Key2196_678*)p + 1)->d, ((Key2196_678*)p + 1)->e, outF, outI, 0);
}

typedef void (*Slot_11ECB8)(void* self, void* arg);

struct Obj_11ECB8 {
    Slot_11ECB8* vtbl;
};

s32 func_00137D10(void* p);

void* func_0011E580(s32 slot, void* self, void* a1, s32 key, s32 flag);

s32 func_0011ECA0(s32 value);

void func_00182ED8(void* obj);

void func_0011ECB8(World* self, void* a1, void* a2)
{
    s32 n = ReadBufferedS16(a2);
    if (n > 0) {
        s32 i = n;
        do {
            s32 slot = ReadBufferedS16(a2);
            s32 key = ReadBufferedS16(a2);
            s32 flag = ReadBufferedS16(a2);
            Obj_11ECB8* obj = (Obj_11ECB8*)CreateTypedRecord(slot, self, a1, key, flag);
            obj->vtbl[14](obj, a2);
            s32 r = MapKeyToSlotIndex(key);
            if (r >= 0) {
                self->slot1CE8[r] = (BaseObject*)obj;

                func_00182ED8(obj);
            }
        } while (--i != 0);
    }
}

struct Pair_11EDA8 { void* node; s32 pad; };

struct Node_11EDA8 { u8 pad0[4]; s32 flags; u8 body[4]; };

extern u8 D_00244950[];

void* func_00137290(BufferedStream* self, s32 a, s32 b, s32 c);

void func_00137398(BufferedStream* self, s32 a1, u8* a2);

void func_0011E680(BaseObject* self, Node_11EDA8* slot, BufferedStream* obj);

void func_001372E0(BufferedStream* self, s32 flags);

void func_0011EDA8(BaseObject* self)
{
    BufferedStream buf;
    s32 off = self->desc->id << 3;
    s32 n = *(s32*)(g_classPropertyLists + off);
    u8* list = *(u8**)(g_classPropertyLists + off + 4);
    if (n > 0) {
        Pair_11EDA8* p = (Pair_11EDA8*)(list + 4);
        s32 i = n;
        do {
            Node_11EDA8* node = (Node_11EDA8*)p->node;
            if (node->flags & 0x800) {
                InitBufferedStream(&buf, 0, 0, 0);
                OpenBufferedMemoryStream(&buf, 4, node->body);
                ApplyPropertyRecord(self, node, &buf);
                DestroyBufferedStream(&buf, 2);
            }
            p++;
        } while (--i != 0);
    }
}

// EXACT: reuse parameter a1 directly instead of a local copy

extern u8 D_00247448[];

struct Owner_11E580 {
    u8 pad00[0x0C];
    s32 f0C;
    void (*f10)(void*);
};

struct Rec_11E580 {
    Owner_11E580* f00;
    s32 f04;
    s32 f08;
    u8 pad0C[8];
    void* f14;
    s32 f18;
    u8 pad1C[8];
    void* f24;
    u8 pad28[4];
    void* f2C;
};

struct Arg_11E580 { s32 v; };

void* func_0018D5C0(s32 bytes);

void func_001DB480(void* self);

void* func_001C1390(Arg_11E580* id, void* ctx);

void* func_00159F20(void* base, s32 n);

void func_00152470(void* list, void* item);

Rec_11E580* func_0011E580(s32 index, void* a1, s32 a2, s32 a3, s32 a4)
{
    s32 off = index << 2;
    Owner_11E580* owner = *(Owner_11E580**)((u8*)D_00247448 + off);
    Rec_11E580* r = (Rec_11E580*)AllocateZeroedFrontMemory(owner->f0C);
    r->f00 = owner;
    r->f08 = a3;
    if (index == 0x6C) {
        a1 = r;
        func_001DB480(r);
    }
    r->f18 = a2;
    r->f14 = a1;
    Arg_11E580* id = (Arg_11E580*)a4;
    r->f2C = GetScriptEntryScope(id, a1);
    AppendToList(GetHashedSlot(r->f14, r->f08), r);
    u8* base = (u8*)r->f14 + 0x1884;
    void** slot = (void**)(base + off);
    r->f24 = *slot;
    *slot = r;
    r->f00->f10(r);
    return r;
}

// EXACT: dtor of the temp called before e = rp; array dtor written as while (buf != e) { e--; dtor(e,0); }

struct Dsc_11E680 {
    s32 type;
    u32 flags;
    u8 pad8[4];
    void (*fC)(ScriptValue* ret, void* obj, s32 n, ScriptValue* args);
    u8 pad10[4];
    s32 count;
    s32 off;
    void* (*f1C)(void* obj, s32 one);
};

void* func_0011C508(void);
void* func_0011C748(void);
void* func_0011C858(void);

typedef void (*Fn_11E680)(void);

union Sc_11E680 { ScriptValue buf[32]; f32 f[8]; s32 i[2]; };

s32 func_00137D10(BufferedStream* r);

s32 func_00137B90(BufferedStream* r);

s32 func_00137D78(BufferedStream* r);

s32 func_00137C40(BufferedStream* r);

f32 func_00137DF8(BufferedStream* r);

void func_00188978(f32* in, f32* out);

void func_0011E680(void* obj, Dsc_11E680* d, BufferedStream* r)
{
    Sc_11E680 sc;
    ScriptValue ret;
    u32 flags = d->flags;
    if (flags & 0x400) {
        ScriptValue* p = sc.buf;
        ScriptValue* rp;
        s32 i;
        s32 n;
        s32 k;
        ScriptValue* e;
        i = 31;
        rp = &ret;
        for (; i != -1; i--) {
            InitScriptValue(p);
            p++;
        }
        n = d->count;
        for (k = 0; k < n; k++) {
            u32 t = ReadBufferedS16(r);
            switch (t) {
            case 0:
                { s32 v = ReadBufferedU8(r); SetScriptValueBool(&sc.buf[k], v); }
                break;
            case 5:
                { s32 v = ReadBufferedS32(r); SetScriptValueInt(&sc.buf[k], v); }
                break;
            case 1:
                { f32 v = ReadBufferedFloat(r); SetScriptValueFloat(&sc.buf[k], v); }
                break;
            case 6:
            case 7:
            case 14:
            case 15:
            case 16:
            case 17:
            case 20:
            {
                s32 v = ReadBufferedS16(r);
                SetScriptValueInt(&sc.buf[k], v);
                break;
            }
            case 9: {
                f32* v = (f32*)AcquireVectorBPayload();
                v[0] = ReadBufferedFloat(r);
                v[1] = ReadBufferedFloat(r);
                v[2] = ReadBufferedFloat(r);
                SetScriptValueVectorB(&sc.buf[k], v);
                break;
            }
            case 10: {
                f32* v = (f32*)AcquirePairPayload();
                v[0] = ReadBufferedFloat(r);
                v[1] = ReadBufferedFloat(r);
                SetScriptValuePair(&sc.buf[k], v);
                break;
            }
            case 2: {
                f32* v = (f32*)AcquireVectorAPayload();
                v[0] = ReadBufferedFloat(r);
                v[1] = ReadBufferedFloat(r);
                v[2] = ReadBufferedFloat(r);
                SetScriptValueVectorA(&sc.buf[k], v);
                break;
            }
            default:
                if (((t & 0x7FFFFFFF) >> 12) == 1) {
                    s32 v = ReadBufferedS16(r);
                    SetScriptValueInt(&sc.buf[k], v);
                }
                break;
            }
        }
        d->fC(rp, obj, n, sc.buf);
        DestroyScriptValue(rp, 2);
        e = rp;
        while (sc.buf != e) {
            e--;
            DestroyScriptValue(e, 0);
        }
    } else if (flags & 0x80) {
        u8* dst;
        if (flags & 0x1000) {
            dst = (u8*)d->f1C(obj, 1) + d->off;
        } else {
            dst = (u8*)obj + d->off;
        }
        switch (d->type) {
        case 0:
            *dst = ReadBufferedU8(r);
            break;
        case 5:
            *(s32*)dst = ReadBufferedS32(r);
            break;
        case 1:
            *(f32*)dst = ReadBufferedFloat(r);
            break;
        case 10:
            ((f32*)dst)[0] = ReadBufferedFloat(r);
            ((f32*)dst)[1] = ReadBufferedFloat(r);
            break;
        case 2:
        case 9:
        case 11:
            ((f32*)dst)[0] = ReadBufferedFloat(r);
            ((f32*)dst)[1] = ReadBufferedFloat(r);
            ((f32*)dst)[2] = ReadBufferedFloat(r);
            break;
        case 3:
        case 12:
            ((f32*)dst)[0] = ReadBufferedFloat(r);
            ((f32*)dst)[1] = ReadBufferedFloat(r);
            ((f32*)dst)[2] = ReadBufferedFloat(r);
            ((f32*)dst)[3] = ReadBufferedFloat(r);
            break;
        case 13:
            *(s32*)dst = ReadBufferedU32(r);
            break;
        case 4: {
            f32* t = sc.f;
            t[0] = ReadBufferedFloat(r);
            t[1] = ReadBufferedFloat(r);
            t[2] = ReadBufferedFloat(r);
            func_00188978(t, (f32*)dst);
            break;
        }
        case 6:
        case 7:
        case 8:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        default:
            *(s32*)dst = ReadBufferedS16(r);
            break;
        }
    } else {
        void* tgt;
        Fn_11E680 fn;
        if (flags & 0x100) {
            fn = (Fn_11E680)(d->off);
            if (flags & 0x1000) {
                tgt = d->f1C(obj, 1);
            } else {
                tgt = obj;
            }
        } else {
            fn = *(Fn_11E680*)(*(s32*)obj + d->off);
            tgt = obj;
        }
        switch (d->type) {
        case 0:
            ((void (*)(void*, s32))fn)(tgt, ReadBufferedU8(r));
            break;
        case 5:
            ((void (*)(void*, s32))fn)(tgt, ReadBufferedS32(r));
            break;
        case 1:
            ((void (*)(void*, f32))fn)(tgt, ReadBufferedFloat(r));
            break;
        case 10: {
            f32* t = sc.f;
            t[0] = ReadBufferedFloat(r);
            t[1] = ReadBufferedFloat(r);
            ((void (*)(void*, f32*))fn)(tgt, t);
            break;
        }
        case 2:
        case 9:
        case 11: {
            f32* t = sc.f;
            t[0] = ReadBufferedFloat(r);
            t[1] = ReadBufferedFloat(r);
            t[2] = ReadBufferedFloat(r);
            ((void (*)(void*, f32*))fn)(tgt, t);
            break;
        }
        case 3:
        case 12: {
            f32* t = sc.f;
            t[0] = ReadBufferedFloat(r);
            t[1] = ReadBufferedFloat(r);
            t[2] = ReadBufferedFloat(r);
            t[3] = ReadBufferedFloat(r);
            ((void (*)(void*, f32*))fn)(tgt, t);
            break;
        }
        case 13: {
            s32* t = sc.i;
            t[0] = ReadBufferedU32(r);
            ((void (*)(void*, s32*))fn)(tgt, t);
            break;
        }
        case 4: {
            f32* t = sc.f;
            f32* o;
            t[0] = ReadBufferedFloat(r);
            t[1] = ReadBufferedFloat(r);
            t[2] = ReadBufferedFloat(r);
            o = sc.f + 4;
            func_00188978(t, o);
            ((void (*)(void*, f32*))fn)(tgt, o);
            break;
        }
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 17:
            ((void (*)(void*, s32))fn)(tgt, ReadBufferedS16(r));
            break;
        default:
            ((void (*)(void*, s32))fn)(tgt, ReadBufferedS16(r));
            break;
        }
    }
}

void func_0018D800(f32* dst, f32* src, s32 n);

void func_001F5CD0(f32* base, s32 n, s32 size, void* cmp);

extern u8 func_001EB128[];

void func_0011F850(T2196_Weight** objs, s32* outCount, f32** outArr)
{
    s32 counts[3];
    f32* ptrs[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        if (objs[i]) {
            objs[i]->vt->times(objs[i], &counts[i], &ptrs[i]);
        } else {
            counts[i] = 0;
            ptrs[i] = 0;
        }
    }
    s32 total = counts[0] + counts[1] + counts[2];
    if (total == 0) {
        *outCount = 0;
        if (outArr) *outArr = 0;
        return;
    }
    s32 last = total - 1;
    f32* arr = (f32*)AllocateBackMemory(total * 4);
    f32* w = arr;
    for (i = 0; i < 3; i++) {
        CopyMemory(w, ptrs[i], counts[i] * 4);
        w += counts[i];
    }
    w = arr + 1;
    func_001F5CD0(arr, total, 4, CompareFloats);
    f32* r = w;
    for (total = last - 1; total >= 0; total--) {
        if (*r != w[-1]) { *w = *r; w++; }
        r++;
    }
    *outCount = w - arr;
    if (outArr) *outArr = arr;
}
