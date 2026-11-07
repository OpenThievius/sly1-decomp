// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x11E560 to 0x1233C0: the stream reader func_0011E680 (its three jump tables open the file's
// .rodata at 0x249870), the keyed curves (method tables D_00219668 to D_00219728) and the
// attachments that give a placed object its position and orientation (method tables D_00219560
// to D_00219600 and D_002197C0), with the object methods func_00122550 and func_001225D0 that
// read them. The state trigger code at 0x1233C0 starts the next file.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "masked_collider.h"
#include "animation.h"
#include "attachment.h"

#include "anim_curve.h"

#include "world.h"

#include "entry_pool.h"

#include "buffered_stream.h"

#include "script_value.h"

void* func_0018D658(s32 size);

void func_0011F850(WeightCurve** axis, s32* outCount, f32** outTimes);

void func_00109488(void);

extern u8 D_002505D8[];

void func_0011E680(void* self, void* slot, void* obj);

s32 func_00137D10(void* p);

// The owner's slot 44 (Desc02::m28) is told what was asked.
typedef void (*Hook_11FC20)(PlacedObject* self, s32 a, s32 b);

void func_0011F6B0(WeightCurve** a, PlacedObject* b, s32 c, Vec02* d, s32 e, s32 f, f32 g, f32 h);

void func_0011F9F8(s32 a, s32 b, s32 c, s32 d, s32 e, f32 g, f32 h);

void func_0011FB98(s32 count, VectorKey* src, s32* outCount, f32** outArr);

s32 func_00137BE0(void* src);

s32 func_00137D10(void* src);

f32 func_00137DF8(void* src);

s32 func_00137CC0(void* src);

void* func_0018D500(s32 size);

s32 func_00137B90(void* src);

void func_00137E70(void* src, void* dst);

WeightCurve* func_00121160(s32 index);

struct Scratch_11F9F8 { f32 diff; f32 delta; u8* ptr; };

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);

void func_00130540(u8* a, u8* b, u8* c, u8* d, f32 f12, f32 f13, f32 f14, s32 a4, s32 a5, s32 a6);

// The owner's slot 45 (Desc02::m29) is told what was asked.
typedef void (*Method_11FF08)(PlacedObject* self, void* a, void* b);

struct Scratch_11FF08 { s32 a[4]; s32 b[4]; };

void func_0011F6B0(WeightCurve** a, PlacedObject* b, s32 c, Vec02* d, void* e, void* f);

void func_00188A20(void* a, void* b);

void func_001EDE38(void* a, void* b, void* c);

extern void* func_0011F6B0(void*, u32, u32, void*, u32, u32);

struct Locals_11FFD8 {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    s32 count;
    f32* values;
    f32 first;
};

extern void func_0011F798(WeightCurve**, Vec02*, Stream83*);

extern void func_00189150(void*, void*, void*);

extern void func_00188D28(void*, void*, void*);

extern void func_0018D608(void);

extern void func_0018D6F0(void);

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f18` and the `move $a0`); the argument setup is scheduled differently.

void func_001303F0(f32 delta, f32 diff, f32 scale, f32 p4, f32 p14, f32 p1C, f32 p24, f32* outF, f32* outI, s32 zero);

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f12` and the `move $a0`); the argument setup is scheduled differently.

void func_00130168(f32 delta, f32 diff, f32 scale, f32 p4, f32 p18, f32 p1C, f32 p24, f32 p2C, f32 p30, f32* outF, f32* outI, s32 zero);

typedef void (*Slot_11ECB8)(void* self, void* arg);

struct Obj_11ECB8 {
    Slot_11ECB8* vtbl;
};

void* func_0011E580(s32 slot, void* self, void* a1, s32 key, s32 flag);

s32 func_0011ECA0(s32 value);

void func_00182ED8(void* obj);

struct Pair_11EDA8 { void* node; s32 pad; };

struct Node_11EDA8 { u8 pad0[4]; s32 flags; u8 body[4]; };

extern u8 D_00244950[];

void* func_00137290(BufferedStream* self, s32 a, s32 b, s32 c);

void func_00137398(BufferedStream* self, s32 a1, u8* a2);

void func_0011E680(BaseObject* self, Node_11EDA8* slot, BufferedStream* obj);

void func_001372E0(BufferedStream* self, s32 flags);

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

void func_0018D800(f32* dst, f32* src, s32 n);

void func_001F5CD0(f32* base, s32 n, s32 size, void* cmp);

extern u8 func_001EB128[];

struct Buffer_00120130 { u8 bytes[0x20]; };
typedef void (*Finish_00120130)(PlacedObject* self, void* output, void* state);
extern void func_0011F9F8(s32, VectorKey*, s32, void*, void*);
extern void func_00188A20(void*, void*);
extern void func_001EDE38(void*, void*, void*);

extern void func_0011F9F8(s32, VectorKey*);
extern void func_0011FB98(s32, VectorKey*, s32*, f32**);

struct Result_001202F0 { f32 x; f32 y; f32 z; };
struct Output_001202F0 { f32 x; u8 pad4[0x10]; f32 y; u8 pad18[0x10]; f32 z; };
extern void func_0011F6B0(WeightCurve**, PlacedObject*, void*, Vec02*, void*, s32, f32, f32);
extern void func_001F5C0C(void*, s32, s32);

void func_0011F798(WeightCurve** a, Vec02* b, Stream83* c);

struct Result_001203A8 {
    f32 first;
    f32 second;
    f32 third;
};
struct Output_001203A8 {
    f32 first;
    u8 pad4[0x10];
    f32 second;
    u8 pad18[0x10];
    f32 third;
};
extern void func_0011F9F8(s32, VectorKey*, void*, f32*, s32, f32, f32);

extern void func_0011FA88(s32*, VectorKey**, Stream83*);

extern void* func_001B5EE0(void*);

extern World* D_00275710;

void func_0018D800(Attachment* self, Attachment* src, s32 size);

// Gives the owner the position and the orientation this attachment gives (slots 29, 30, 32, 33).
struct Locals_121648 {
    Vec02 pos;
    Vec02 vec;
    Mat02 rot;
};

// The owner's slot 44 (Desc02::m28) and 45 (m29) are told what was asked.
typedef void (*Told_1227B0)(PlacedObject* self, Vec02* a, Vec02* b);

typedef void (*Told_1227F0)(PlacedObject* self, Mat02* b, Vec02* q);

typedef void (*Told_122920)(PlacedObject* self);

void func_00121338(Attachment* self, PlacedObject* a1);

void func_00152600(void* list, void* item);
void func_00121358(Attachment* self, s32 flags);

extern f32 D_0026185C[];
void func_001214B8(Attachment* self, Vec02* a1, Vec02* a2);
s32 func_0012E9E0(AnimationPlayer* t, f32* a, f32* b);

void func_00121508(Attachment* self, Mat02* a, Vec02* b);

struct Locals_001201F0 {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    f32 first;
};

f32 D_00260E60[4] = { 3.0f, 1.0f, 0.1f, 0.0f };
extern f32 D_0026186C;
extern f32 D_00261860;
extern f32 func_001EA4B8(void*, s32, f32, f32, f32);

void func_00121568(Attachment* self, f32* value, f32* slope);

extern void func_00121568(Attachment* self, f32* a1, f32* a2);

extern void func_00121580(Attachment* self, Mat02* a1);

// The position curves' tables, defined at the end of this file.
extern const PositionCurveVt D_002196B8;
extern const PositionCurveVt D_002196C8;
extern const PositionCurveVt D_002196D8;

extern u8 D_00248D30[];
void func_00152600(void* a, void* b);
void func_001BA500(void* a, void* b, void* c, void* d, s32 e);
void func_001274F8(void* a, void* b);
void func_00127590(void* a, void* b);
void func_001B5F28(void* a, void* b);

extern u8 D_002483D0[];

s32 func_00139970(f32 x, f32 period, s32 count, BlendTimeScale* p, f32* out);
f32 func_001EA408(f32 a);

extern const RotationCurveVt D_002196E8;
extern const RotationCurveVt D_002196F8;
extern const RotationCurveVt D_00219708;

extern const ScaleCurveVt D_00219718;
extern const ScaleCurveVt D_00219728;
void* func_0018D5C0(u32 n);

extern u8 D_00219560[];

typedef void (*Told_1214B8)(PlacedObject* self, Vec02* out);

void func_00121338(Attachment* self);

// The dispatch tables func_00121160 gives each kind of curve: three functions, or one and a
// shared one, each table followed by a zero word.
void func_0011F0C8();
void func_0011EFC8();
void func_0011F180();
void func_0011F320();
void func_0011F210();
void func_0011F3E8();
void func_0011F478();
void func_0011F568();
void func_0011F620();
void func_0011EFB0();
extern const WeightCurveVt D_00219668;
extern const WeightCurveVt D_00219678;
extern const WeightCurveVt D_00219688;
extern const WeightCurveVt D_00219698;
extern const WeightCurveVt D_002196A8;
void* func_0018D5C0(WeightCurve* n);

typedef void (*Told_121508)(PlacedObject* self, Mat02* out1, Vec02* out2);

void func_0011E560(void)
{
    func_00109488();
}

Rec_11E580* func_0011E580(s32 index, void* a1, s32 a2, s32 a3, s32 a4)
{
    s32 off = index << 2;
    Owner_11E580* owner = *(Owner_11E580**)((u8*)D_00247448 + off);
    Rec_11E580* r = (Rec_11E580*)AllocateZeroedFrontMemory(owner->f0C);
    r->f00 = owner;
    r->f08 = a3;
    if (index == 0x6C) {
        a1 = r;
        InitWorldHashLists(r);
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
            BuildRotationFromVector(t, (f32*)dst);
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
            BuildRotationFromVector(t, o);
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

                ResolveAndStartObject(obj);
            }
        } while (--i != 0);
    }
}

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

void func_0011EF40(void)
{
}

void func_0011EF48(PositionCurve* unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0) {
        *b = 0;
    }
}

void func_0011EF60(void)
{
}

void func_0011EF68(void)
{
}

void func_0011EF70(RotationCurve* self, s32* first, s32* second)
{
    *first = 0;
    if (second != 0) {
        *second = 0;
    }
}

void func_0011EF88()
{
}

void func_0011EF90(ScaleCurve* a0, s32* a1, s32* a2)
{
    *a1 = 0;
    if (a2 != 0) {
        *a2 = 0;
    }
}

void func_0011EFA8()
{
}

void func_0011EFB0(WeightCurve* unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0)
        *b = 0;
}

void func_0011EFC8(TangentWeightCurve* self, Stream83* src)
{
    self->count = ReadBufferedU16(src);
    self->keys = (TangentWeightKey*)AllocateFrontMemory(0x18 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        TangentWeightKey* e = self->keys + i;
        e->time = (f32)ReadBufferedS16(src) * 0.016666668f;
        e->value = ReadBufferedFloat(src);
        e->c = ReadBufferedS8(src);
        e->kind = ReadBufferedS8(src);
        e->d = ReadBufferedFloat(src);
        e->f = ReadBufferedFloat(src);
    }
}

void func_0011F0C8(TangentWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    FindCurveSegment(key, flags, 0x18, self->count, (u8*)self->keys, &diff, &delta, &p);
    if (((TangentWeightKey*)p)->kind == 5) {
        if (outF != 0) {
            *outF = ((TangentWeightKey*)p)->value;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    EvaluateHermiteSegment(delta, diff, scale, ((TangentWeightKey*)p)->value, ((TangentWeightKey*)p)->f, ((TangentWeightKey*)p + 1)->value, ((TangentWeightKey*)p + 1)->d, outF, outI, 0);
}

void func_0011F180(TangentWeightCurve* src, s32* outCount, f32** outValues)
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

void func_0011F210(ControlPointWeightCurve* self, Stream83* src)
{
    self->count = ReadBufferedU16(src);
    self->keys = (ControlPointWeightKey*)AllocateFrontMemory(0x20 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        ControlPointWeightKey* e = self->keys + i;
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

void func_0011F320(ControlPointWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    FindCurveSegment(key, flags, 0x20, self->count, (u8*)self->keys, &diff, &delta, &p);
    if (((ControlPointWeightKey*)p)->kind == 5) {
        if (outF != 0) {
            *outF = ((ControlPointWeightKey*)p)->value;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    SolveBezierSegment(delta, diff, scale, ((ControlPointWeightKey*)p)->value, ((ControlPointWeightKey*)p)->g, ((ControlPointWeightKey*)p)->h, ((ControlPointWeightKey*)p + 1)->value, ((ControlPointWeightKey*)p + 1)->d, ((ControlPointWeightKey*)p + 1)->e, outF, outI, 0);
}

void func_0011F3E8(ControlPointWeightCurve* self, s32* outCount, f32** outArr)
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

void func_0011F478(LinearWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    FindCurveSegment(key, flags, 8, self->count, (u8*)self->keys, &diff, &delta, &p);
    if (delta < 0.0001f) {
        if (outF != 0) {
            *outF = ((LinearWeightKey*)p)->value;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    if (outF != 0) {
        f32 t = diff / delta;
        *outF = (1.0f - t) * ((LinearWeightKey*)p)->value + t * ((LinearWeightKey*)p + 1)->value;
    }
    if (outI != 0) {
        *outI = scale * (((LinearWeightKey*)p + 1)->value - ((LinearWeightKey*)p)->value) / delta;
    }
}

void func_0011F568(LinearWeightCurve* self, Stream83* src)
{
    self->count = ReadBufferedU16(src);
    self->keys = (LinearWeightKey*)AllocateFrontMemory(self->count << 3);
    for (s32 i = 0; i < self->count; i++) {
        LinearWeightKey* e = self->keys + i;
        e->time = (f32)ReadBufferedS16(src) * 0.016666668f;
        e->value = ReadBufferedFloat(src);
    }
}

void func_0011F620(LinearWeightCurve* self, s32* count, f32** out)
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

ASM_FUNC(func_0011F6B0);

void func_0011F798(WeightCurve** out, Vec02* dst, Stream83* src)
{
    s32 mask = ReadBufferedU8(src);
    WeightCurve** slot = out;
    ReadBufferedVector3(src, dst);
    s32 i = 2;
    do {
        s32 bit = mask & 1;
        mask >>= 1;
        if (bit) {
            WeightCurve* o = CreateWeightCurve(ReadBufferedU8(src));
            void (*fn)(WeightCurve*, Stream83*) = o->vt->read;
            if (fn)
                fn(o, src);
            *slot = o;
        }
        slot++;
        i--;
    } while (i >= 0);
}

void func_0011F850(WeightCurve** objs, s32* outCount, f32** outArr)
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
    SortElements(arr, total, 4, CompareFloats);
    f32* r = w;
    for (total = last - 1; total >= 0; total--) {
        if (*r != w[-1]) { *w = *r; w++; }
        r++;
    }
    *outCount = w - arr;
    if (outArr) *outArr = arr;
}

void func_0011F9F8(s32 count, s32 base, s32 flags, s32 d, s32 e, f32 key, f32 scale)
{
    Scratch_11F9F8 s;
    FindCurveSegment(key, flags, 0x40, count, (u8*)base, &s.diff, &s.delta, &s.ptr);
    u8* p = s.ptr;
    func_00130540(p + 0x10, p + 0x30, p + 0x50, p + 0x60, s.delta, s.diff, scale, d, e, 0);
}

void func_0011FA88(s32* outCount, VectorKey** outItems, Stream83* src)
{
    s32 count = ReadBufferedU16(src);
    VectorKey* items = (VectorKey*)AllocateFrontMemory(count << 6);
    if (count > 0) {
        u8* p2 = (u8*)&items->v2;
        u8* p1 = (u8*)&items->v1;
        u8* p0 = (u8*)&items->v0;
        VectorKey* it = items;
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

void func_0011FB98(s32 count, VectorKey* src, s32* outCount, f32** outArr)
{
    *outCount = count;
    if (outArr) {
        *outArr = (f32*)AllocateBackMemory(count * 4);
        s32 i = 0;
        if (*outCount > 0) {
            VectorKey* p = src;
            do {
                (*outArr)[i] = p->time;
                p++;
                i++;
            } while (i < *outCount);
        }
    }
}

void func_0011FC20(AxisPositionCurve* self, PlacedObject* other, s32 c, s32 e, s32 f, f32 p12, f32 p13)
{
    EvaluateAxisCurves(self->axis, other, c, &self->base, e, f, p12, p13);
    if (other && other->desc02()->m28)
        ((Hook_11FC20)other->desc02()->m28)(other, e, f);
}

ASM_FUNC(func_0011FC90);

void func_0011FDB8(AxisPositionCurve* self, s32* outCount, f32** outTimes)
{
    GatherAxisCurveTimes(self->axis, outCount, outTimes);
}

void func_0011FDD8(VectorKeyPositionCurve* self, PlacedObject* other, s32 a2, s32 a3, s32 a4, f32 p12, f32 p13)
{
    EvaluateVectorKeyCurve(self->count, (s32)self->keys, a2, a3, a4, p12, p13);
    if (other && other->desc02()->m28)
        ((Hook_11FC20)other->desc02()->m28)(other, a3, a4);
}

ASM_FUNC(func_0011FE40);

void func_0011FED8(VectorKeyPositionCurve* self, s32* outCount, f32** outArr)
{
    GetVectorKeyTimes(self->count, self->keys, outCount, outArr);
}

void func_0011FF08(AxisRotationCurve* self, PlacedObject* other, s32 c, void* p3, void* p4)
{
    Scratch_11FF08 tmp;
    EvaluateAxisCurves(self->axis, other, c, &self->base, p3 ? (void*)&tmp : 0, p4 ? (void*)tmp.b : 0);
    if (p3)
        BuildEulerRotationMatrix(&tmp, p3);
    if (p4)
        RotateVectorByTwoAngles(&tmp, tmp.b, p4);
    if (other)
        ((Method_11FF08)other->desc02()->m29)(other, p3, p4);
}

void* func_0011FFA8(AxisRotationCurve* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    return EvaluateAxisCurves(self->axis, a1, a2, &self->base, a3, a4);
}

void func_0011FFD8(AxisRotationCurve* self, Stream83* arg)
{
    Locals_11FFD8 loc;
    s32 result;

    ReadAxisCurves(self->axis, &self->base, arg);
    PushBackMemoryMark();
    self->vt->times(self, &loc.count, &loc.values);
    if (loc.count > 0) {
        self->vt->eval(self, 0, 0, loc.a, 0, loc.values[0], 1.0f);
        self->vt->eval(self, 0, 0, loc.b, 0, loc.values[loc.count - 1], 1.0f);
        MultiplyMatrices3x3(loc.a, loc.b, loc.c);
        MatrixToAxisAngle(loc.c, &loc.first, loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    } else {
        result = 1;
    }
    self->closed = result;
    PopBackMemoryMark();
}

void func_00120110(AxisRotationCurve* self, s32* outCount, f32** outTimes)
{
    GatherAxisCurveTimes(self->axis, outCount, outTimes);
}

void func_00120130(KeyedRotationCurve* self, PlacedObject* parent, s32 mode,
                   void* output, void* state)
{
    Buffer_00120130 buffer;
    EvaluateVectorKeyCurve(self->count, self->keys, mode,
                  output ? &buffer.bytes[0] : 0,
                  state ? &buffer.bytes[0x10] : 0);
    if (output) {
        BuildEulerRotationMatrix(&buffer.bytes[0], output);
    }
    if (state) {
        RotateVectorByTwoAngles(&buffer.bytes[0], &buffer.bytes[0x10], state);
    }
    if (parent) {
        ((Finish_00120130)parent->desc02()->m29)(parent, output, state);
    }
}

void func_001201D0(KeyedRotationCurve* self)
{
	EvaluateVectorKeyCurve(self->count, self->keys);
}

void func_001201F0(KeyedRotationCurve* self, Stream83* arg)
{
    Locals_001201F0 loc;
    s32 result;

    ReadVectorKeys(&self->count, &self->keys, arg);
    if (self->count < 2) {
        result = 1;
    } else {
        BuildEulerRotationMatrix((u8*)self->keys + 0x10, loc.a);
        u8* tail = (u8*)((self->count << 6) + (s32)self->keys) - 0x30;
        BuildEulerRotationMatrix(tail, loc.b);
        MultiplyMatrices3x3(loc.a, loc.b, loc.c);
        MatrixToAxisAngle(loc.c, &loc.first, loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    }
    self->closed = result;
}

void func_001202C0(KeyedRotationCurve* self, s32* outCount, f32** outTimes)
{
	GetVectorKeyTimes(self->count, self->keys, outCount, outTimes);
}

void func_001202F0(AxisScaleCurve* self, PlacedObject* second, void* third,
                   Output_001202F0* output, f32 factor)
{
    Result_001202F0 result;
    EvaluateAxisCurves(self->axis, second, third, &self->base,
                  output ? &result : 0, 0, factor, 1.0f);
    if (output) {
        FillMemory(output, 0, 0x30);
        output->x = result.x;
        output->y = result.y;
        output->z = result.z;
    }
}

void func_00120360(AxisScaleCurve* self, Stream83* p)
{
    ReadAxisCurves(self->axis, &self->base, p);
}

void func_00120388(AxisScaleCurve* self, s32* outCount, f32** outTimes)
{
	GatherAxisCurveTimes(self->axis, outCount, outTimes);
}

void func_001203A8(KeyedScaleCurve* self, PlacedObject* unused, void* mode,
                   Output_001203A8* output, f32 factor)
{
    Result_001203A8 result;
    EvaluateVectorKeyCurve(self->count, self->keys, mode,
                  output ? &result.first : 0, 0, factor, 1.0f);
    if (output) {
        FillMemory(output, 0, 0x30);
        output->first = result.first;
        output->second = result.second;
        output->third = result.third;
    }
}

void func_00120418(KeyedScaleCurve* self, Stream83* stream)
{
	ReadVectorKeys(&self->count, &self->keys, stream);
}

void func_00120440(KeyedScaleCurve* self, s32* outCount, f32** outTimes)
{
	GetVectorKeyTimes(self->count, self->keys, outCount, outTimes);
}

ASM_FUNC(func_00120470);

ASM_FUNC(func_00120700);

void func_00120AA8(AngleBlendWeightCurve* o, PlacedObject* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
{
    f32 sum1 = 0.0f;
    f32 v0 = sum1;
    f32 x0;
    f32 x1;
    f32 x2;
    f32* p0;
    f32* p1;
    if (out0) {
        p0 = &x0;
    } else {
        x0 = sum1;
        p0 = 0;
    }
    if (out1) {
        p1 = &x1;
    } else {
        x1 = 0.0f;
        p1 = 0;
    }
    BlendSequence* seq = o->seq;
    BlendConfig* cfg = o->cfg;
    f32 w = 0.0f;
    f32 t;
    s32 idx;
    if (!seq) {
        t = dt / cfg->length;
    } else {
        idx = FindCyclicRangeIndex(dt, cfg->length, seq->count, seq->pairs, &x2);
        t = x2 / seq->pairs[idx].b;
    }
    for (s32 i = 0; i < cfg->count; i++) {
        BlendEntry* e = (BlendEntry*)(cfg->base + i * cfg->stride);
        if (e->weight == 0.0f)
            continue;
        WeightCurve* tg = o->targets[i];
        if (!tg) {
            if (cam) {
                f32 r = WrapAngle(((Rec2195_224*)cam->f224)->f90 - v0);
                v0 += r * e->weight / (w + e->weight);
            }
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                BlendTimeScale* q = (BlendTimeScale*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, c, p0, p1, a, b * scale);
            if (w == 0.0f) {
                v0 = x0;
            } else {
                f32 r = WrapAngle(WrapAngle(x0) - v0);
                v0 += r * e->weight / (w + e->weight);
            }
            sum1 += e->weight * x1;
        }
        w += e->weight;
        v0 = WrapAngle(v0);
    }
    if (out0)
        *out0 = v0;
    if (out1)
        *out1 = sum1;
}

void func_00120D58(ValueBlendWeightCurve* o, PlacedObject* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
{
    f32 sum1 = 0.0f;
    f32 sum0 = sum1;
    f32 x0;
    f32 x1;
    f32 x2;
    f32* p0;
    f32* p1;
    if (out0) {
        p0 = &x0;
    } else {
        x0 = sum1;
        p0 = 0;
    }
    if (out1) {
        p1 = &x1;
    } else {
        x1 = 0.0f;
        p1 = 0;
    }
    BlendSequence* seq = o->seq;
    BlendConfig* cfg = o->cfg;
    f32 t;
    s32 idx;
    if (!seq) {
        t = dt / cfg->length;
    } else {
        idx = FindCyclicRangeIndex(dt, cfg->length, seq->count, seq->pairs, &x2);
        t = x2 / seq->pairs[idx].b;
    }
    for (s32 i = 0; i < cfg->count; i++) {
        BlendEntry* e = (BlendEntry*)(cfg->base + i * cfg->stride);
        f32 zero = 0.0f;
        if (e->weight == zero)
            continue;
        WeightCurve* tg = o->targets[i];
        if (!tg) {
            if (cam)
                sum0 += e->weight * (*(f32**)((u8*)cam + 0x274))[o->index];
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                BlendTimeScale* q = (BlendTimeScale*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, c, p0, p1, a, b * scale);
            sum0 += e->weight * x0;
            sum1 += e->weight * x1;
        }
    }
    if (out0)
        *out0 = sum0;
    if (out1)
        *out1 = sum1;
}

PositionCurve* func_00120FB0(s32 kind)
{
    PositionCurve* p;
    switch (kind) {
    case 0:
        p = (PositionCurve*)AllocateZeroedFrontMemory(0x30);
        p->vt = &g_positionCurveKind0Methods;
        break;
    case 1:
        p = (PositionCurve*)AllocateZeroedFrontMemory(0x14);
        p->vt = &g_positionCurveKind1Methods;
        break;
    case 2:
        p = (PositionCurve*)AllocateZeroedFrontMemory(0x18);
        p->vt = &g_positionCurveKind2Methods;
        break;
    default:
        p = 0;
        break;
    }
    if (p != 0) {
        p->kind = kind;
    }
    return p;
}

RotationCurve* func_00121050(s32 kind) {
    RotationCurve* p;
    switch (kind) {
    case 0:
        p = (RotationCurve*)AllocateZeroedFrontMemory(0x30);
        p->vt = &g_rotationCurveKind0Methods;
        break;
    case 1:
        p = (RotationCurve*)AllocateZeroedFrontMemory(0x14);
        p->vt = &g_rotationCurveKind1Methods;
        break;
    case 2:
        p = (RotationCurve*)AllocateZeroedFrontMemory(0x1C);
        p->vt = &g_rotationCurveKind2Methods;
        break;
    default:
        p = 0;
        break;
    }
    if (p) {
        p->kind = kind;
    }
    return p;
}

ScaleCurve* func_001210F0(s32 kind)
{
    ScaleCurve* p;
    switch (kind) {
    case 0:
        p = (ScaleCurve*)AllocateZeroedFrontMemory(0x30);
        p->vt = &g_scaleCurveKind0Methods;
        break;
    case 1:
        p = (ScaleCurve*)AllocateZeroedFrontMemory(0x10);
        p->vt = &g_scaleCurveKind1Methods;
        break;
    default:
        p = 0;
        break;
    }
    if (p != 0) {
        p->kind = kind;
    }
    return p;
}

WeightCurve* func_00121160(u32 kind)
{
    WeightCurve* o;
    switch (kind) {
    case 0:
        o = (WeightCurve*)AllocateZeroedFrontMemory((WeightCurve*)0x10);
        o->vt = &g_weightCurveKind0Methods;
        break;
    case 1:
        o = (WeightCurve*)AllocateZeroedFrontMemory((WeightCurve*)0x10);
        o->vt = &g_weightCurveKind1Methods;
        break;
    case 3:
        o = (WeightCurve*)AllocateZeroedFrontMemory((WeightCurve*)0x14);
        o->vt = &g_weightCurveKind3Methods;
        break;
    case 4:
        o = (WeightCurve*)AllocateZeroedFrontMemory((WeightCurve*)0x18);
        o->vt = &g_weightCurveKind4Methods;
        break;
    case 2:
        o = (WeightCurve*)AllocateZeroedFrontMemory((WeightCurve*)0x10);
        o->vt = &g_weightCurveKind2Methods;
        break;
    default:
        o = 0;
    }
    if (o)
        o->kind = kind;
    return o;
}

Attachment* func_00121228(World* root, PlacedObject* value, const T2195_Vt* table)
{
	Attachment* node = (Attachment*)PopZeroedFreeSlot(&root->pool1B20);
	node->vt = table;
	table->init(node, value);
	return node;
}

Attachment* func_00121280(Attachment* self, World* a, PlacedObject* b)
{
    Attachment* node = CreatePoseSource(a, b, (const T2195_Vt*)D_00219560);
    node->vt->copy(node, self);
    return node;
}

void func_001212D8(Attachment* self, Attachment* src)
{
    Link2195 tmp = self->link;
    PlacedObject* saved = self->owner;
    CopyMemory(self, src, g_currentWorld->pool1B20.size);
    self->link = tmp;
    self->owner = saved;
}

void func_00121338(Attachment* self, PlacedObject* value)
{
	s8 m = -1;
	self->owner = value;
	self->mode2 = m;
	self->mode3 = -1;
	self->mode1 = m;
	self->mode0 = m;
}

void func_00121358(Attachment* self, s32 flags)
{
    PlacedObject* m = self->owner;
    s32 local[4];
    RemoveFromList(&m->list1E0, self);
    Attachment* a = m->f1EC;
    Attachment* b = m->f1F0;
    m->desc02()->m2B(m);
    if (self == a && m->f1EC == 0 && (flags & 1) != 0) {
        if ((m->desc->flags & 2) != 0) {
            func_001BA500(m, (u8*)m + 0x440, (u8*)m + 0x150, local, 0);
            m->desc02()->m20(m, (Vec02*)local);
        } else {
            SetPlacedObjectVelocity(m, D_00248D30);
        }
    }
    if (self == b && m->f1F0 == 0 && (flags & 2) != 0) {
        if ((m->desc->flags & 2) != 0) {
            func_001BA500(m, (u8*)m + 0x460, (u8*)m + 0x160, local, 0);
            m->desc02()->m21(m, (Vec02*)local);
        } else {
            SetPlacedObjectSpin(m, D_00248D30);
        }
    }
    PushFreeSlot(&m->world->pool1B20, self);
}

void func_001214B8(Attachment* self, Vec02* out1, Vec02* out2)
{
    *out1 = self->owner->v190;
    *out2 = *(Vec02*)D_00248D30;
    if (self->owner->desc02()->m28 != 0) {
        ((Told_1214B8)self->owner->desc02()->m28)(self->owner, out1);
    }
}

void func_00121508(Attachment* self, Mat02* out1, Vec02* out2)
{
    *out1 = self->owner->m1A0;
    *out2 = *(Vec02*)D_00248D30;
    ((Told_121508)self->owner->desc02()->m29)(self->owner, out1, out2);
}

void func_00121568(Attachment* self, f32* value, f32* slope)
{
	Rec2195_224* rec = (Rec2195_224*)self->owner->f224;
	*value = rec->f8C;
	*slope = 0.0f;
}

void func_00121580(Attachment* unused, Mat02* out)
{
    Mat02* src = (Mat02*)g_identityMatrix;
    out->r[0] = src->r[0];
    out->r[1] = src->r[1];
    out->r[2] = src->r[2];
}

f32 func_001215A8(Attachment* self, s32 index)
{
	return (*(f32**)((u8*)self->owner + 0x274))[index];
}

void func_001215C0(Attachment* obj)
{
    PlacedObject* node = obj->owner;
    Collider* a2 = (node->desc->flags & 2) ? (Collider*)node : 0;
    s8 b2C9 = node->b2C9;
    if (b2C9 != -1) {
        obj->mode0 = b2C9;
    } else {
        if (a2 == 0 || a2->mode450 == 3) {
            obj->mode0 = 2;
        } else {
            obj->mode0 = 3;
        }
    }
    s8 b2CA = node->b2CA;
    if (b2CA != -1) {
        obj->mode1 = b2CA;
        return;
    }
    if (a2 == 0 || a2->mode470 == 3) {
        obj->mode1 = 2;
    } else {
        obj->mode1 = 3;
    }
}

void func_00121648(Attachment* self, s32 flag)
{
    Locals_121648 loc;
    PlacedObject* s2 = self->owner;

    if (self == s2->f1EC) {
        if (flag != 0 || self->mode0 == 2) {
            self->vt->getPos(self, 0.0f, &loc.pos, &loc.vec);
            s2->desc02()->m1D(s2, &loc.pos);
            s2->desc02()->m20(s2, &loc.vec);
        }
    }
    if (self == s2->f1F0) {
        if (flag != 0 || self->mode1 == 2) {
            self->vt->getRot(self, 0.0f, &loc.rot, &loc.pos);

            s2->desc02()->m1E(s2, &loc.rot);
            s2->desc02()->m21(s2, &loc.pos);
        }
    }
}

ASM_FUNC(func_00121760);

INCLUDE_RODATA(jtbl_00249990);

ASM_FUNC(func_001218C0);

ASM_FUNC(func_00121C48);

INCLUDE_RODATA(jtbl_002499C0);

ASM_FUNC(func_00121DE0);

void func_00122488(Attachment* self, s32 val)
{
    f32 ret = self->vt->getIndexed(self, val);
    switch (self->mode3) {
    case 2:
        self->owner->f270[val] = ret;
        break;
    case 3: {
        f32 cur = self->owner->f270[val];
        f32 limit = self->owner->f294 ? g_frameStep : g_frameDt;
        self->owner->f270[val] = ApproachValueWithRamp(g_valueRampProfile, 0, cur, ret, limit);
        break;
    }
    }
}

ASM_FUNC(func_00122550);

ASM_FUNC(func_001225D0);

void func_001226D8(Attachment* self)
{
    if (self->mode0 == 7) {
        self->mode0 = 3;
    }
    if (self->mode1 == 7) {
        self->mode1 = 3;
    }
}

void func_00122708(T2195_588* self, PlacedObject* src)
{
    InitPoseSource(self, src);
    self->pos = src->v190;
    self->rot.r[0] = src->m1A0.r[0];
    self->rot.r[1] = src->m1A0.r[1];
    self->rot.r[2] = src->m1A0.r[2];
    Rec2195_224* p = (Rec2195_224*)src->f224;
    if (p != 0) {
        if (p->fB0 & 0x20) {
            self->f80 = p->f8C;
        }
    }
    Vec02* table = (Vec02*)g_identityMatrix;
    self->m90.r[0] = table[0];
    self->m90.r[1] = table[1];
    self->m90.r[2] = table[2];
    self->countC0 = src->f26C;
    self->valuesC4 = *(f32**)((u8*)src + 0x274);
}

void func_001227B0(T2195_588* src, Vec02* d0, Vec02* d1)
{
    *d0 = src->pos;
    *d1 = src->vec;
    PlacedObject* obj = src->owner;
    Told_1227B0 fn = obj->desc02()->m28;
    if (fn != 0) {
        fn(obj, d0, d1);
    }
}

void func_001227F0(T2195_588* src, Mat02* d0, Vec02* d1)
{
    d0->r[0] = src->rot.r[0];
    d0->r[1] = src->rot.r[1];
    d0->r[2] = src->rot.r[2];
    *d1 = src->v70;
    PlacedObject* obj = src->owner;
    Told_1227F0 fn = (Told_1227F0)obj->desc02()->m29;
    fn(obj, d0, d1);
}

void func_00122840(T2195_588* self, f32* first, f32* second)
{
	*first = self->f80;
	*second = self->f84;
}

void func_00122858(T2195_588* self, Mat02* output)
{
	output->r[0] = self->m90.r[0];
	output->r[1] = self->m90.r[1];
	output->r[2] = self->m90.r[2];
}

f32 func_00122878(T2195_588* self, s32 i)
{
    return self->valuesC4[i];
}

void func_00122890(T2195_5B0* self, PlacedObject* src)
{
    InitPoseSource(self, src);
    self->pos = &src->v190;
    self->rot = &src->m1A0;
    self->count = &src->f26C;
    self->vec = (Vec02*)D_00248D30;
    self->vec2 = (Vec02*)D_00248D30;
    self->values = *(f32**)((u8*)src + 0x274);
    Rec2195_224* o = (Rec2195_224*)src->f224;
    if (o != 0) {
        if (o->fB0 & 0x20) {
            self->p30 = (f32*)D_00248D30;
            self->p2C = &o->f8C;
        }
    }
    self->ident = (Mat02*)g_identityMatrix;
}

void func_00122920(T2195_5B0* self, Vec02* first, Vec02* second)
{
	*first = *self->pos;
	*second = *self->vec;
	Told_122920 callback = (Told_122920)self->owner->desc02()->m28;
	if (callback)
		callback(self->owner);
}

void func_00122968(T2195_5B0* self, Mat02* d1, Vec02* d2)
{
    Mat02* s = self->rot;
    d1->r[0] = s->r[0];
    d1->r[1] = s->r[1];
    d1->r[2] = s->r[2];
    *d2 = *self->vec2;
    self->owner->desc02()->m29(self->owner, d1, d2);

}

void func_001229C0(T2195_5B0* self, f32* a, f32* b)
{
    *a = *self->p2C;
    *b = *self->p30;
}

void func_001229E0(T2195_5B0* self, Mat02* dst)
{
    Mat02* s = self->ident;
    dst->r[0] = s->r[0];
    dst->r[1] = s->r[1];
    dst->r[2] = s->r[2];
}

f32 func_00122A00(T2195_5B0* self, s32 i)
{
    return self->values[i];
}

void func_00122A18(T2195_5D8* self)
{
    InitPoseSource(self);
    Vec02* src = (Vec02*)g_identityMatrix;
    Vec02* d1 = self->m40.r;
    Vec02* d2 = self->m90.r;
    self->m40.r[0] = src[0];
    d1[1] = src[1];
    d1[2] = src[2];
    self->m90.r[0] = src[0];
    d2[1] = src[1];
    d2[2] = src[2];
}

ASM_FUNC(func_00122A80);

ASM_FUNC(func_00122B30);

void func_00122C48(Attachment* self, f32* a1, f32* a2)
{
    Attachment* p = self;
    while ((p = p->link.next) != 0) {
        s8 f = p->mode1;
        if (f == 0) { p = 0; break; }
        if (f != -1) break;
    }
    if (p != 0) {
        p->vt->getValue(p, a1, a2);
    } else {
        GetOwnerValue(self, a1, a2);
    }
}

ASM_FUNC(func_00122CB0);

f32 func_00122D90(void)
{
    return 0.0f;
}

void func_00122DA0(T2195_600* self, PlacedObject* a1)
{
    InitPoseSource(self, a1);
    self->f1C = 1.0f;
    self->f20 = 0.25f;
}

ASM_FUNC(func_00122DE0);

void func_00122F28(T2195_7C0* self, s32 a1)
{
    AnimationPlayer* o = self->player;
    RemoveFromList(&o->list44, self);
    if (o->driven == self) {
        o->driven = 0;
    }
    ReleasePoseSource(self, a1);
}

void func_00122F88(T2195_7C0* self, Attachment* a1)
{
    AnimationPlayer* saved = self->player;
    Pair2195 tmp = self->w20;
    CopyPoseSource(self, a1);
    self->w20 = tmp;
    self->player = saved;
}

void func_00122FE0(T2195_7C0* self, Vec02* a1, Vec02* a2, f32 f)
{
    AnimationPlayer* track = self->player;
    Track83* e = &track->anim->tracks[self->index];
    if (e->pos != 0) {
        f32 tmp[2];
        if (f != 0.0f) {
            f32 c14 = track->time;
            f32 c18 = track->speed;
            tmp[1] = c18;
            tmp[0] = c14 + f * c18;
            ApplyAnimationLoopMode(track, &tmp[0], &tmp[1]);
        } else {
            tmp[0] = track->time;
        }
        if (self->mode0 == 4) {
            f32 d = self->f18 - g_gameTime[0] - track->f10;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->speed;
            }
        }
        e->pos->vt->eval(e->pos, self->owner, 0, a1, a2, tmp[0], track->speed);
        return;
    }
    GetOwnerPosition(self, a1, a2);
}

void func_00123120(T2195_7C0* self, Mat02* a1, Vec02* a2, f32 f)
{
    PlacedObject* p4 = self->owner;
    AnimationPlayer* track = self->player;
    Track83* e = &track->anim->tracks[self->index];
    if (e->rot != 0) {
        f32 tmp[2];
        if (f != 0.0f) {
            f32 c14 = track->time;
            f32 c18 = track->speed;
            tmp[1] = c18;
            tmp[0] = c14 + f * c18;
            ApplyAnimationLoopMode(track, &tmp[0], &tmp[1]);
        } else {
            tmp[0] = track->time;
        }
        if (self->mode1 == 4) {
            f32 d = self->f18 - g_gameTime[0] - track->f10;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->speed;
            }
        }
        e->rot->vt->eval(e->rot, p4, 0, a1, a2, tmp[0], track->speed);
        return;
    }
    GetOwnerRotation(self, a1, a2);
}

void func_00123270(T2195_7C0* self, f32* a1, f32* a2)
{
    f32* saved = a1;
    PlacedObject* f4 = self->owner;
    AnimationPlayer* player = self->player;
    Track83* e = &player->anim->tracks[self->index];
    WeightCurve* target = e->weight;
    if (target) {
        target->vt->eval(target, f4, 0, saved, a2, player->time, player->speed);
    } else {
        GetOwnerValue(self, saved, a2);
    }
}

void func_001232E8(T2195_7C0* self, Mat02* a1)
{
    Mat02* saved = a1;
    PlacedObject* f4 = self->owner;
    AnimationPlayer* player = self->player;
    Track83* e = &player->anim->tracks[self->index];
    ScaleCurve* target = e->scale;
    if (target) {
        target->vt->eval(target, f4, 0, saved, player->time);
    } else {
        GetIdentityMatrix(self, saved);
    }
}

f32 func_00123358(T2195_7C0* self, s32 index)
{
    AnimationPlayer* track = self->player;
    Track83* row = &track->anim->tracks[self->index];
    WeightCurve** values = row->morph;
    WeightCurve* object = values[index];
    f32 result;
    object->vt->eval(object, self->owner, 0, &result, 0, track->time, track->speed);
    return result;
}
