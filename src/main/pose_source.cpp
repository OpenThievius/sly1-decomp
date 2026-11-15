// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x11E560 to 0x1233C0: the stream reader func_0011E680 (its three jump tables open the file's
// .rodata at 0x249870), the keyed curves (method tables D_00219668 to D_00219728) and the
// attachments that give a placed object its position and orientation (method tables D_00219560
// to D_00219600 and D_002197C0), with the object methods func_00122550 and func_001225D0 that
// read them. The state trigger code at 0x1233C0 starts the next file.
#include "common.h"
#include "asm_func.h"
#include "property_descriptor.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "masked_collider.h"
#include "animation.h"
#include "attachment.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "game_clock.h"
#include "functions/base_object.h"
#include "functions/blend_animation.h"
#include "functions/collider.h"
#include "functions/curve_segment.h"
#include "functions/effect_spawner.h"
#include "functions/matrix.h"
#include "functions/object_host_functions.h"
#include "functions/object_properties.h"
#include "functions/placed_object.h"
#include "functions/pooled_object.h"
#include "functions/pose_source.h"
#include "functions/state_walker.h"
#include "functions/value_pools.h"
#include "functions/warp_menu.h"
#include "functions/world.h"

#include "anim_curve.h"

#include "world.h"

#include "entry_pool.h"

#include "buffered_stream.h"

#include "script_value.h"

#include "ramp_profile.h"

void* AllocateBackMemory(s32 size);



extern u8 g_objectPropertyDescriptors[];


s32 ReadBufferedS16(BufferedStream* self);

// The owner's slot 44 (PlacedObjectDescriptor::m28) is told what was asked.
typedef void (*VectorCurveToldFn)(PlacedObject* self, f32* a, f32* b);




u16 ReadBufferedU16(BufferedStream* self);

s32 ReadBufferedS16(BufferedStream* self);

f32 ReadBufferedFloat(BufferedStream* r);

s32 ReadBufferedS8(BufferedStream* self);

void* AllocateFrontMemory(s32 size);

s32 ReadBufferedU8(BufferedStream* self);

void ReadBufferedVector3(BufferedStream* src, void* dst);


// What FindCurveSegment (func_0011EE70) gives back: the segment's length and the time into it,
// and the segment's first key.
struct CurveSegment { f32 diff; f32 delta; u8* ptr; };



// The owner's slot 45 (PlacedObjectDescriptor::m29) is told what was asked.
typedef void (*AxisRotationToldFn)(PlacedObject* self, void* a, void* b);

// The angles and their rates EvaluateAxisCurves gives an axis rotation curve (func_0011FF08).
struct AngleSample { s32 a[4]; s32 b[4]; };





struct AxisCurveClosure {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    s32 count;
    f32* values;
    f32 first;
};




extern void PushBackMemoryMark(void);

extern void PopBackMemoryMark(void);

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f18` and the `move $a0`); the argument setup is scheduled differently.

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f12` and the `move $a0`); the argument setup is scheduled differently.





// A class's property list (g_classPropertyLists) seen from its first descriptor pointer: the
// descriptor, then the word before the next one.
struct PropertyListSlot { void* node; s32 pad; };

extern u8 g_classPropertyLists[];

void* InitBufferedStream(BufferedStream* self, s32 a, u8* b, s32 c);

void OpenBufferedMemoryStream(BufferedStream* self, s32 a1, u8* a2);


void DestroyBufferedStream(BufferedStream* self, s32 flags);

// EXACT: reuse parameter a1 directly instead of a local copy

extern u8 g_classDescriptorTable[];

void* AllocateZeroedFrontMemory(s32 n);





// EXACT: dtor of the temp called before e = rp; array dtor written as while (buf != e) { e--; dtor(e,0); }


typedef void (*PropertyMethodFn)(void);

union PropertyValues { ScriptValue buf[32]; f32 f[8]; s32 i[2]; };

s32 ReadBufferedS16(BufferedStream* r);

s32 ReadBufferedU8(BufferedStream* r);

s32 ReadBufferedS32(BufferedStream* r);

s32 ReadBufferedU32(BufferedStream* r);

f32 ReadBufferedFloat(BufferedStream* r);


void CopyMemory(void* dst, void* src, u32 size);

void SortElements(void* base, u32 n, u32 size, s32 (*compare)(const void* x, const void* y));


// The angles and their rates EvaluateVectorKeyCurve gives a keyed rotation curve (func_00120130).
struct KeyedAngleSample { u8 bytes[0x20]; };
typedef void (*KeyedRotationToldFn)(PlacedObject* self, void* output, void* state);


extern "C" void* FillMemory(void* p, s32 value, s32 size);





extern World* g_currentWorld;

void CopyMemory(void* dst, void* src, u32 size);

// Gives the owner the position and the orientation this attachment gives (slots 29, 30, 32, 33).
struct PoseLocals {
    Vec4 pos;
    Vec4 vec;
    Mat3 rot;
};

// The owner's slot 44 (PlacedObjectDescriptor::m28) and 45 (m29) are told what was asked.
typedef void (*PositionToldFn)(PlacedObject* self, Vec4* a, Vec4* b);

typedef void (*OrientationToldFn)(PlacedObject* self, Mat3* b, Vec4* q);

typedef void (*OwnerToldFn)(PlacedObject* self);



extern f32 g_gameTime[];


struct KeyedCurveClosure {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    f32 first;
};

f32 g_valueRampProfile[4] = { 3.0f, 1.0f, 0.1f, 0.0f };
extern f32 g_frameStep;
extern f32 g_frameDt;




// The position curves' tables, defined at the end of this file.
extern const PositionCurveVt g_positionCurveKind0Methods;
extern const PositionCurveVt g_positionCurveKind1Methods;
extern const PositionCurveVt g_positionCurveKind2Methods;

extern u8 g_zeroVector[];

extern u8 g_identityMatrix[];


extern const RotationCurveVt g_rotationCurveKind0Methods;
extern const RotationCurveVt g_rotationCurveKind1Methods;
extern const RotationCurveVt g_rotationCurveKind2Methods;

extern const ScaleCurveVt g_scaleCurveKind0Methods;
extern const ScaleCurveVt g_scaleCurveKind1Methods;
void* AllocateZeroedFrontMemory(s32 n);

extern u8 g_ownerPoseSourceMethods[];

typedef void (*PositionOutToldFn)(PlacedObject* self, Vec4* out);


// The dispatch tables func_00121160 gives each kind of curve: three functions, or one and a
// shared one, each table followed by a zero word.
extern const WeightCurveVt g_weightCurveKind0Methods;
extern const WeightCurveVt g_weightCurveKind1Methods;
extern const WeightCurveVt g_weightCurveKind2Methods;
extern const WeightCurveVt g_weightCurveKind3Methods;
extern const WeightCurveVt g_weightCurveKind4Methods;
void* AllocateZeroedFrontMemory(s32 n);

typedef void (*FrameOutToldFn)(PlacedObject* self, Mat3* out1, Vec4* out2);

// Fills the object property table with the built-in entries.
void InitObjectBuiltinTable(void)
{
    FillObjectPropertyTable();
}

// Creates an object of the class with this index in the class table: a zeroed record of the class's
// size, with its descriptor, id, parent, world and script scope set; it is added to the world's
// hash list by id and to the list of its class, and the class's method 0 runs. For class 0x6C the
// object is its own world.
BaseObject* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4)
{
    s32 off = index << 2;
    // address arithmetic over a variable index
    BaseObjectDescriptor* owner = *(BaseObjectDescriptor**)((u8*)g_classDescriptorTable + off);
    BaseObject* r = (BaseObject*)AllocateZeroedFrontMemory(owner->size);
    r->desc = owner;
    r->id = a3;
    if (index == 0x6C) {
        a1 = r;
        InitWorldHashLists((u8*)r);
    }
    r->parent = a2;
    r->world = (World*)a1;
    r->scriptScope = GetScriptEntryScope(a4, (World*)a1);
    AppendToList((ObjectList*)(GetHashedSlot((u8*)r->world, r->id)), r);
    // address arithmetic over a variable index
    u8* base = (u8*)r->world->objectsById;
    void** slot = (void**)(base + off);
    r->nextById = (BaseObject*)*slot;
    *slot = r;
    r->desc->m00(r);
    return r;
}

// Reads one property value from the stream by the descriptor and applies it to obj: with flag 0x400
// as a script call (arguments read into script values and passed to the setter), with 0x80 by
// storing it at the descriptor's offset, otherwise through a setter method. The types are byte,
// int, float, vectors of two to four floats, a rotation given as three floats and a 16-bit id.
void ApplyPropertyRecord(void* obj, PropertyDescriptor* d, BufferedStream* r)
{
    PropertyValues sc;
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
        n = d->argCount;
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
        d->setter(rp, obj, n, sc.buf);
        DestroyScriptValue(rp, 2);
        e = rp;
        while (sc.buf != e) {
            e--;
            DestroyScriptValue(e, 0);
        }
    } else if (flags & 0x80) {
        u8* dst;
        if (flags & 0x1000) {
            // address arithmetic over a variable index
            dst = (u8*)d->target(obj, 1) + d->offset;
        } else {
            // address arithmetic over a variable index
            dst = (u8*)obj + d->offset;
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
            BuildRotationFromVector((Vec4*)t, (Mat3*)dst);
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
        PropertyMethodFn fn;
        if (flags & 0x100) {
            fn = (PropertyMethodFn)(d->offset);
            if (flags & 0x1000) {
                tgt = d->target(obj, 1);
            } else {
                tgt = obj;
            }
        } else {
            fn = *(PropertyMethodFn*)(*(s32*)obj + d->offset);
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
            BuildRotationFromVector((Vec4*)t, (Mat3*)o);
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

// Reads property records from the stream and applies each to self until a negative index ends it.
void ReadPropertyRecords(void* self, void* obj)
{
    s32 r;
    while ((r = ReadBufferedS16((BufferedStream*)obj)) >= 0) {
        ApplyPropertyRecord(self, (PropertyDescriptor*)(g_objectPropertyDescriptors + (r << 5)), (BufferedStream*)obj);
    }
}

// Maps a key code 12 to 42 onto the slot 0 to 30, and anything else to -1.
s32 MapKeyToSlotIndex(s32 value)
{
    s32 r = value - 12;
    return ((u32)30 < (u32)r) ? -1 : r;
}

// Reads a count and then, for each, a class index, an id and a script id from the stream, creates
// the object with CreateTypedRecord, lets it read its own data, and, when the id maps to one of the
// world's slots, stores it there and starts it.
void ReadSlotObjects(World* self, void* a1, void* a2)
{
    s32 n = ReadBufferedS16((BufferedStream*)a2);
    if (n > 0) {
        s32 i = n;
        do {
            s32 slot = ReadBufferedS16((BufferedStream*)a2);
            s32 key = ReadBufferedS16((BufferedStream*)a2);
            s32 flag = ReadBufferedS16((BufferedStream*)a2);
            BaseObject* obj = CreateTypedRecord(slot, self, (BaseObject*)a1, key, flag);
            obj->desc->m0A(obj, a2);
            s32 r = MapKeyToSlotIndex(key);
            if (r >= 0) {
                self->slot1CE8[r] = (BaseObject*)obj;

                ResolveAndStartObject(obj);
            }
        } while (--i != 0);
    }
}

// Applies the default value of each property of the object's class that is flagged 0x800, by
// parsing the property's stored value as a buffered memory stream.
void ApplyObjectClassDefaults(BaseObject* self)
{
    BufferedStream buf;
    s32 off = self->desc->id << 3;
    s32 n = *(s32*)(g_classPropertyLists + off);
    u8* list = *(u8**)(g_classPropertyLists + off + 4);
    if (n > 0) {
        PropertyListSlot* p = (PropertyListSlot*)(list + 4);
        s32 i = n;
        do {
            PropertyDescriptor* node = (PropertyDescriptor*)p->node;
            if (node->flags & 0x800) {
                InitBufferedStream(&buf, 0, 0, 0);
                OpenBufferedMemoryStream(&buf, 4, node->value);
                ApplyPropertyRecord(self, node, &buf);
                DestroyBufferedStream(&buf, 2);
            }
            p++;
        } while (--i != 0);
    }
}

// Binary-searches the key array (records of stride bytes, time first) for the segment holding key.
// Gives the segment start in *outPtr, the time into it in *outDiff and its length in *outDelta
// (either may be null). With flags bit 0 set, a key exactly on a boundary uses the previous
// segment.
void FindCurveSegment(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr)
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

// Does nothing: the empty position curve's evaluation.
void EvaluateNoPositionCurve(void)
{
}

// The empty position curve has no keys: stores 0 as the count.
void GetNoPositionCurveTimes(PositionCurve* unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0) {
        *b = 0;
    }
}

// Does nothing: the empty rotation curve's evaluation.
void EvaluateNoRotationCurve(void)
{
}

// Does nothing: the empty rotation curve's raw getter.
void GetNoRotationCurve(void)
{
}

// The empty rotation curve has no keys: stores 0 as the count.
void GetNoRotationCurveTimes(RotationCurve* self, s32* first, s32* second)
{
    *first = 0;
    if (second != 0) {
        *second = 0;
    }
}

// Does nothing: the empty scale curve's evaluation.
void EvaluateNoScaleCurve()
{
}

// The empty scale curve has no keys: stores 0 as the count.
void GetNoScaleCurveTimes(ScaleCurve* a0, s32* a1, s32* a2)
{
    *a1 = 0;
    if (a2 != 0) {
        *a2 = 0;
    }
}

// Does nothing: the empty weight curve's evaluation.
void EvaluateNoWeightCurve()
{
}

// The empty weight curve has no keys: stores 0 as the count.
void GetNoWeightCurveTimes(WeightCurve* unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0)
        *b = 0;
}

// Reads the keys of a Hermite weight curve from the stream: count, then per key the time (in 1/60
// s, stored in seconds), the value, two bytes and two slope values.
void ReadTangentWeightCurve(TangentWeightCurve* self, Stream83* src)
{
    self->count = ReadBufferedU16((BufferedStream*)src);
    self->keys = (TangentWeightKey*)AllocateFrontMemory(0x18 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        TangentWeightKey* e = self->keys + i;
        e->time = (f32)ReadBufferedS16((BufferedStream*)src) * 0.016666668f;
        e->value = ReadBufferedFloat((BufferedStream*)src);
        e->c = ReadBufferedS8((BufferedStream*)src);
        e->kind = ReadBufferedS8((BufferedStream*)src);
        e->d = ReadBufferedFloat((BufferedStream*)src);
        e->f = ReadBufferedFloat((BufferedStream*)src);
    }
}

// Evaluates a weight curve of Hermite keys at key: a segment whose first key has kind 5 holds its
// value, any other is a Hermite segment between the two keys. Value to *outF, slope to *outI.
void EvaluateTangentWeightCurve(TangentWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
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

// Gives the key count, and with outValues non-null a back-memory array of the keys' times.
void GetTangentWeightCurveTimes(TangentWeightCurve* src, s32* outCount, f32** outValues)
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

// Reads the keys of a Bezier weight curve from the stream: count, then per key the time (stored in
// 1/60 s, converted to seconds), the value, two bytes, a slope and the two control points as
// offsets from the value (before and after).
void ReadControlPointWeightCurve(ControlPointWeightCurve* self, Stream83* src)
{
    self->count = ReadBufferedU16((BufferedStream*)src);
    self->keys = (ControlPointWeightKey*)AllocateFrontMemory(0x20 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        ControlPointWeightKey* e = self->keys + i;
        e->time = (f32)ReadBufferedS16((BufferedStream*)src) * 0.016666668f;
        e->value = ReadBufferedFloat((BufferedStream*)src);
        e->c = ReadBufferedS8((BufferedStream*)src);
        e->kind = ReadBufferedS8((BufferedStream*)src);
        e->d = ReadBufferedFloat((BufferedStream*)src);
        f32 t = ReadBufferedFloat((BufferedStream*)src);
        e->e = e->value - t;
        e->g = ReadBufferedFloat((BufferedStream*)src);
        f32 u = ReadBufferedFloat((BufferedStream*)src);
        e->h = e->value + u;
    }
}

// Evaluates a weight curve of Bezier keys at key: a segment whose first key has kind 5 holds its
// value, any other is solved as a Bezier segment between the two keys. Value to *outF, slope to
// *outI.
void EvaluateControlPointWeightCurve(ControlPointWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
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

// Gives the key count, and with outArr non-null a back-memory array of the keys' times.
void GetControlPointWeightCurveTimes(ControlPointWeightCurve* self, s32* outCount, f32** outArr)
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

// Evaluates a piecewise linear weight curve at key: the value to outF and the slope (the difference
// to the next key's value times scale over the segment's length) to outI; either may be null. A
// segment of almost no length gives its first key's value and slope 0.
void EvaluateLinearWeightCurve(LinearWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
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

// Reads a count and that many (time, value) keys from the stream; times are stored in 1/60 s ticks
// and converted to seconds.
void ReadLinearWeightCurve(LinearWeightCurve* self, Stream83* src)
{
    self->count = ReadBufferedU16((BufferedStream*)src);
    self->keys = (LinearWeightKey*)AllocateFrontMemory(self->count << 3);
    for (s32 i = 0; i < self->count; i++) {
        LinearWeightKey* e = self->keys + i;
        e->time = (f32)ReadBufferedS16((BufferedStream*)src) * 0.016666668f;
        e->value = ReadBufferedFloat((BufferedStream*)src);
    }
}

// Gives the key count, and with out non-null a back-memory array of the keys' times.
void GetLinearWeightCurveTimes(LinearWeightCurve* self, s32* count, f32** out)
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

// Evaluates the three axis curves at key: the values start from base (and the slopes from 0), and
// each axis that has a curve overwrites its own component; outputs may be null.
void EvaluateAxisCurves(WeightCurve** axis, PlacedObject* other, s32 flags, Vec4* base, f32* outValues, f32* outSlopes, f32 key, f32 scale)
{
    if (outValues)
        *(Vec4*)outValues = *base;
    if (outSlopes)
        Vu0::Q(*(Vec4*)outSlopes) = Vu0::Zero();
    for (s32 i = 0; i < 3; i++) {
        WeightCurve* curve = axis[i];
        if (curve)
            curve->vt->eval(curve, other, key, scale, flags, outValues ? outValues + i : 0, outSlopes ? outSlopes + i : 0);
    }
}

// Reads a vector and a 3-bit mask, then for each set bit one weight curve (kind byte, then the
// curve's own read) into out[0..2], one per axis.
void ReadAxisCurves(WeightCurve** out, Vec4* dst, Stream83* src)
{
    s32 mask = ReadBufferedU8((BufferedStream*)src);
    WeightCurve** slot = out;
    ReadBufferedVector3((BufferedStream*)src, dst);
    s32 i = 2;
    do {
        s32 bit = mask & 1;
        mask >>= 1;
        if (bit) {
            WeightCurve* o = CreateWeightCurve(ReadBufferedU8((BufferedStream*)src));
            void (*fn)(WeightCurve*, Stream83*) = o->vt->read;
            if (fn)
                fn(o, src);
            *slot = o;
        }
        slot++;
        i--;
    } while (i >= 0);
}

// Collects the key times of up to three curves (one per axis) into one sorted array without
// duplicates, allocated from back memory, and gives its length in outCount (0 and a null array if
// there are none).
void GatherAxisCurveTimes(WeightCurve** objs, s32* outCount, f32** outArr)
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
    SortElements(arr, total, 4, (s32 (*)(const void*, const void*))CompareFloats);
    f32* r = w;
    for (total = last - 1; total >= 0; total--) {
        if (*r != w[-1]) { *w = *r; w++; }
        r++;
    }
    *outCount = w - arr;
    if (outArr) *outArr = arr;
}

// Evaluates a curve of 0x40-byte vector keys at key: finds the segment and runs the Hermite vector
// evaluation between its two keys, giving values and slopes.
void EvaluateVectorKeyCurve(s32 count, VectorKey* keys, s32 flags, f32* values, f32* slopes, f32 key, f32 scale)
{
    CurveSegment s;
    FindCurveSegment(key, flags, 0x40, count, (u8*)keys, &s.diff, &s.delta, &s.ptr);
    u8* p = s.ptr;
    EvaluateHermiteVectorSegment(s.delta, (const Vec4*)(p + 0x10), (const Vec4*)(p + 0x30), (const Vec4*)(p + 0x50), (const Vec4*)(p + 0x60), s.diff, scale, (Vec4*)values, (Vec4*)slopes, 0);
}

// Reads a list of vector keys from the stream: a count, then per key the time (in 1/60 s, stored in
// seconds) and three vectors. Gives the count and the allocated array.
void ReadVectorKeys(s32* outCount, VectorKey** outItems, Stream83* src)
{
    s32 count = ReadBufferedU16((BufferedStream*)src);
    VectorKey* items = (VectorKey*)AllocateFrontMemory(count << 6);
    if (count > 0) {
        u8* p2 = (u8*)&items->v2;
        u8* p1 = (u8*)&items->v1;
        u8* p0 = (u8*)&items->v0;
        VectorKey* it = items;
        s32 left = count;
        do {
            left--;
            it->time = (f32)ReadBufferedS16((BufferedStream*)src) * 0.016666668f;
            ReadBufferedVector3((BufferedStream*)src, p0);
            p0 += 0x40;
            ReadBufferedVector3((BufferedStream*)src, p1);
            p1 += 0x40;
            ReadBufferedVector3((BufferedStream*)src, p2);
            p2 += 0x40;
            it++;
        } while (left != 0);
    }
    *outCount = count;
    *outItems = items;
}

// Gives the key count, and with outArr non-null a back-memory array of the keys' times.
void GetVectorKeyTimes(s32 count, VectorKey* src, s32* outCount, f32** outArr)
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

// Evaluates the three per-axis curves, then tells the owner through its slot-28 method if it has
// one.
void EvaluateAxisPositionCurve(AxisPositionCurve* self, PlacedObject* other, s32 c, f32* e, f32* f, f32 p12, f32 p13)
{
    EvaluateAxisCurves(self->axis, other, c, &self->base, e, f, p12, p13);
    if (other && other->desc02()->m28)
        ((VectorCurveToldFn)other->desc02()->m28)(other, e, f);
}

// Reads the three axis curves of a position curve from the stream and works out whether it is
// closed: the curve is marked closed when its first and last key positions are less than 1 unit
// apart (or it has no keys).
void ReadAxisPositionCurve(AxisPositionCurve* self, Stream83* arg)
{
    Vec4 v[2];
    s32 count;
    f32* values;
    s32 result;

    ReadAxisCurves(self->axis, &self->base, arg);
    PushBackMemoryMark();
    self->vt->times(self, &count, &values);
    if (count != 0) {
        self->vt->eval(self, 0, values[0], 1.0f, 0, &v[0], 0);
        self->vt->eval(self, 0, values[count - 1], 1.0f, 0, &v[1], 0);
        result = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(v[0]), Vu0::Q(v[1])))) < 1.0f;
    } else {
        result = 1;
    }
    self->closed = result;
    PopBackMemoryMark();
}

// Gives the key times of the three per-axis position curves.
void GetAxisPositionCurveTimes(AxisPositionCurve* self, s32* outCount, f32** outTimes)
{
    GatherAxisCurveTimes(self->axis, outCount, outTimes);
}

// Evaluates the key curve, then tells the owner through its slot-28 method if it has one.
void EvaluateVectorKeyPositionCurve(VectorKeyPositionCurve* self, PlacedObject* other, s32 a2, f32* a3, f32* a4, f32 p12, f32 p13)
{
    EvaluateVectorKeyCurve(self->count, self->keys, a2, a3, a4, p12, p13);
    if (other && other->desc02()->m28)
        ((VectorCurveToldFn)other->desc02()->m28)(other, a3, a4);
}

// Reads the position keys from the stream and sets closed when the last key is within 1 unit of the
// first (a single key counts as closed).
void ReadVectorKeyPositionCurve(VectorKeyPositionCurve* self, Stream83* arg)
{
    ReadVectorKeys(&self->count, &self->keys, arg);
    if (self->count < 2) {
        self->closed = 1;
    } else {
        u128 d = Vu0::Sub(Vu0::Q(self->keys->v0), Vu0::Q(self->keys[self->count - 1].v0));
        self->closed = (Vu0::ToFloat(Vu0::Dot(d, d)) < 1.0f) ? 1 : 0;
    }
}

// Gives the position curve's key count and times.
void GetVectorKeyPositionCurveTimes(VectorKeyPositionCurve* self, s32* outCount, f32** outArr)
{
    GetVectorKeyTimes(self->count, self->keys, outCount, outArr);
}

// Evaluates the three per-axis curves into Euler angles, builds the rotation matrix (and the
// rotation's derivative) from them, then tells the owner through its slot-29 method.
void EvaluateAxisRotationCurve(AxisRotationCurve* self, PlacedObject* other, s32 c, void* p3, void* p4, f32 key, f32 scale)
{
    AngleSample tmp;
    EvaluateAxisCurves(self->axis, other, c, &self->base, p3 ? (f32*)&tmp : 0, p4 ? (f32*)tmp.b : 0, key, scale);
    if (p3)
        BuildEulerRotationMatrix((f32*)&tmp, (f32*)p3);
    if (p4)
        RotateVectorByTwoAngles((Vec3*)&tmp, (Vec3*)tmp.b, (Vec3*)p4);
    if (other)
        ((AxisRotationToldFn)other->desc02()->m29)(other, p3, p4);
}

// Evaluates the three per-axis curves at key (the method shares its body with the axis position
// evaluation, without the angles and notification).
void* GetAxisRotationCurve(AxisRotationCurve* self, PlacedObject* other, s32 flags, f32* values, f32* slopes, f32 key, f32 scale)
{
    EvaluateAxisCurves(self->axis, other, flags, &self->base, values, slopes, key, scale);
}

// Reads the three axis curves of a rotation curve from the stream and works out whether it is
// closed: the rotations at its first and last key are compared and the curve is marked closed when
// they differ by less than 0.01 in angle (or it has no keys).
void ReadAxisRotationCurve(AxisRotationCurve* self, Stream83* arg)
{
    AxisCurveClosure loc;
    s32 result;

    ReadAxisCurves(self->axis, &self->base, arg);
    PushBackMemoryMark();
    self->vt->times(self, &loc.count, &loc.values);
    if (loc.count > 0) {
        self->vt->eval(self, 0, 0, loc.a, 0, loc.values[0], 1.0f);
        self->vt->eval(self, 0, 0, loc.b, 0, loc.values[loc.count - 1], 1.0f);
        MultiplyMatrices3x3((Mat3*)loc.a, (Mat3*)loc.b, (Mat3*)loc.c);
        MatrixToAxisAngle((Mat3*)loc.c, &loc.first, (Vec4*)loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    } else {
        result = 1;
    }
    self->closed = result;
    PopBackMemoryMark();
}

// Gives the key times of the three per-axis rotation curves.
void GetAxisRotationCurveKeyTimes(AxisRotationCurve* self, s32* outCount, f32** outTimes)
{
    GatherAxisCurveTimes(self->axis, outCount, outTimes);
}

// Evaluates the keyed curve into Euler angles, builds the rotation matrix (and the derivative) from
// them, then tells the parent through its slot-29 method.
void EvaluateKeyedRotationCurve(KeyedRotationCurve* self, PlacedObject* parent, s32 mode,
                   void* output, void* state, f32 key, f32 scale)
{
    KeyedAngleSample buffer;
    EvaluateVectorKeyCurve(self->count, self->keys, mode,
                  output ? (f32*)&buffer.bytes[0] : 0,
                  state ? (f32*)&buffer.bytes[0x10] : 0, key, scale);
    if (output) {
        BuildEulerRotationMatrix((f32*)&buffer.bytes[0], (f32*)output);
    }
    if (state) {
        RotateVectorByTwoAngles((Vec3*)&buffer.bytes[0], (Vec3*)&buffer.bytes[0x10], (Vec3*)state);
    }
    if (parent) {
        ((KeyedRotationToldFn)parent->desc02()->m29)(parent, output, state);
    }
}

// Evaluates the keyed rotation curve's raw vector keys at key, giving values and slopes.
void GetKeyedRotationCurve(KeyedRotationCurve* self, PlacedObject* other, s32 flags, f32* values, f32* slopes, f32 key, f32 scale)
{
	EvaluateVectorKeyCurve(self->count, self->keys, flags, values, slopes, key, scale);
}

// Reads the rotation keys from the stream and sets closed when the curve loops: the rotation from
// the first key to the last is under 0.01 in angle (a single key counts as closed).
void ReadKeyedRotationCurve(KeyedRotationCurve* self, Stream83* arg)
{
    KeyedCurveClosure loc;
    s32 result;

    ReadVectorKeys(&self->count, &self->keys, arg);
    if (self->count < 2) {
        result = 1;
    } else {
        BuildEulerRotationMatrix((f32*)&self->keys[0].v0, (f32*)loc.a);
        BuildEulerRotationMatrix((f32*)&self->keys[self->count - 1].v0, (f32*)loc.b);
        MultiplyMatrices3x3((Mat3*)loc.a, (Mat3*)loc.b, (Mat3*)loc.c);
        MatrixToAxisAngle((Mat3*)loc.c, &loc.first, (Vec4*)loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    }
    self->closed = result;
}

// Gives the key count and times of the keyed rotation curve.
void GetKeyedRotationCurveKeyTimes(KeyedRotationCurve* self, s32* outCount, f32** outTimes)
{
	GetVectorKeyTimes(self->count, self->keys, outCount, outTimes);
}

// Evaluates the three per-axis curves into a diagonal scale matrix (the rest zeroed).
void EvaluateAxisScaleCurve(AxisScaleCurve* self, PlacedObject* second, s32 third,
                   Mat3U* output, f32 factor)
{
    Vec3 result;
    EvaluateAxisCurves(self->axis, second, third, &self->base,
                  output ? (f32*)&result : 0, 0, factor, 1.0f);
    if (output) {
        FillMemory(output, 0, 0x30);
        output->m[0][0] = result.x;
        output->m[1][1] = result.y;
        output->m[2][2] = result.z;
    }
}

// Reads the three per-axis scale curves from the stream.
void ReadAxisScaleCurve(AxisScaleCurve* self, Stream83* p)
{
    ReadAxisCurves(self->axis, &self->base, p);
}

// Gives the key times of the three per-axis scale curves.
void GetAxisScaleCurveKeyTimes(AxisScaleCurve* self, s32* outCount, f32** outTimes)
{
	GatherAxisCurveTimes(self->axis, outCount, outTimes);
}

// Evaluates the keyed curve into a diagonal scale matrix (the rest zeroed).
void EvaluateKeyedScaleCurve(KeyedScaleCurve* self, PlacedObject* unused, s32 mode,
                   Mat3U* output, f32 factor)
{
    Vec3 result;
    EvaluateVectorKeyCurve(self->count, self->keys, mode,
                  output ? &result.x : 0, 0, factor, 1.0f);
    if (output) {
        FillMemory(output, 0, 0x30);
        output->m[0][0] = result.x;
        output->m[1][1] = result.y;
        output->m[2][2] = result.z;
    }
}

// Reads the scale keys from the stream.
void ReadKeyedScaleCurve(KeyedScaleCurve* self, Stream83* stream)
{
	ReadVectorKeys(&self->count, &self->keys, stream);
}

// Gives the key count and times of the keyed scale curve.
void GetKeyedScaleCurveKeyTimes(KeyedScaleCurve* self, s32* outCount, f32** outTimes)
{
	GetVectorKeyTimes(self->count, self->keys, outCount, outTimes);
}

// Evaluates a weighted blend of position curves at time dt (through the cyclic ranges of its
// sequence if it has one): out0 gets the weighted sum of the positions and out1 of the velocities
// (a missing target counts as the object's own value), either may be null; then the owner's method
// 0x28 sees them.
void EvaluateBlendedPositionCurve(PositionCurveKind2* o, PlacedObject* cam, s32 c, Vec4* out0, Vec4* out1, f32 dt, f32 scale)
{
    Vec4 x0;
    Vec4 x1;
    Vec4 k;
    f32 x2;
    Vec4* p1;
    if (out0)
        Vu0::Q(*out0) = Vu0::Zero();
    if (out1)
        Vu0::Q(*out1) = Vu0::Zero();
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
        Vec4* p0 = out0 ? &x0 : 0;
        f32 wt = e->weight;
        if (wt == 0.0f)
            continue;
        PositionCurve* tg = o->targets[i];
        if (!tg) {
            if (out0) {
                u128 w = Vu0::FromFloat(wt);
                u128 acc = Vu0::Q(*out0);
                Vu0::Q(k) = w;
                Vu0::Q(*out0) = Vu0::MulAddX(acc, Vu0::Q(cam ? cam->v190 : *(Vec4*)g_zeroVector), w);
            }
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                // address arithmetic over a variable index
                BlendTimeScale* q = (BlendTimeScale*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, a, b * scale, c, p0, out1 ? &x1 : 0);
            if (out0) {
                u128 w = Vu0::FromFloatAt(e->weight);
                Vu0::Q(k) = w;
                Vu0::Q(*out0) = Vu0::MulAddX(Vu0::Q(*out0), Vu0::Q(x0), w);
            }
            if (out1) {
                u128 w = Vu0::FromFloatAt(e->weight);
                Vu0::Q(k) = w;
                Vu0::Q(*out1) = Vu0::MulAddX(Vu0::Q(*out1), Vu0::Q(x1), w);
            }
        }
    }
    if (cam && cam->desc02()->m28)
        cam->desc02()->m28(cam, out0, out1);
}

// The product a b of two rotations into out: b's rows each rotated by a, the rows of both read
// once (mul_rotation.h has the forms that read b's rows one by one).
static inline void MulRotationRowsOnce(Mat3* out, const Mat3& a, const Mat3& b)
{
    Mat3 r;
    Vec4 x;
    Vec4 y;
    Vec4 z;
    const u128* p = (const u128*)&a;
    const u128* q = (const u128*)&b;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    u128 b0 = q[0], b1 = q[1], b2 = q[2];
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, b0);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, b1);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, b2);
    r.r[2] = z;
    *out = r;
}


// Evaluates a weighted blend of rotation curves at time dt (through its sequence's cyclic ranges if
// any): a rotation matrix to out0 and an angular velocity to out1 (either may be null). Targets of
// weight 0 are skipped, a missing target uses the object's own value; rotations are averaged as
// angles or, with multiplyRotations, composed by weighted axis-angle.
void EvaluateBlendedRotationCurve(RotationCurveKind2* o, PlacedObject* cam, s32 c, Mat3* out0, Vec4* out1, f32 dt, f32 scale)
{
    Vec4 x0;
    Vec4 acc0;
    Vec4 x1;
    Vec4 acc1;
    f32 x2;
    if (out0)
        Vu0::Q(acc0) = Vu0::Zero();
    if (out1)
        Vu0::Q(acc1) = Vu0::Zero();
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
    f32 w = 0.0f;
    for (s32 i = 0; i < cfg->count; i++) {
        BlendEntry* e = (BlendEntry*)(cfg->base + i * cfg->stride);
        if (e->weight == 0.0f)
            continue;
        RotationCurve* tg = o->targets[i];
        if (!tg) {
            if (!out0)
                continue;
            Vu0::Set(x0, Vu0::Q(cam ? cam->v1D0 : *(Vec4*)g_zeroVector));
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                // address arithmetic over a variable index
                BlendTimeScale* q = (BlendTimeScale*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->get(tg, cam, c, out0 ? &x0 : 0, out1 ? &x1 : 0, a, b * scale);
            if (out1)
                Vu0::Q(acc1) = Vu0::MulAddX(Vu0::Q(acc1), Vu0::Q(x1), Vu0::ScalarAt(e->weight));
        }
        if (!out0)
            continue;
        if (o->multiplyRotations) {
            if (w == 0.0f) {
                BuildEulerRotationMatrix((f32*)&x0, (f32*)out0);
            } else {
                Vec4 axis;
                Mat3 rotA;
                Mat3 prod;
                f32 angle;
                BuildEulerRotationMatrix((f32*)&x0, (f32*)&rotA);
                MultiplyMatrices3x3(&rotA, out0, &prod);
                MatrixToAxisAngle(&prod, &angle, &axis);
                BuildAxisAngleMatrix(&axis, &prod, angle * w / (w + e->weight));
                MulRotationRowsOnce(out0, prod, rotA);
            }
            w += e->weight;
        } else {
            Vu0::Q(acc0) = Vu0::MulAddX(Vu0::Q(acc0), Vu0::Q(x0), Vu0::ScalarAt(e->weight));
        }
    }
    if (out0 && !o->multiplyRotations)
        BuildEulerRotationMatrix((f32*)&acc0, (f32*)out0);
    if (out1)
        RotateVectorByTwoAngles((Vec3*)&acc0, (Vec3*)&acc1, (Vec3*)out1);
    if (cam)
        ((KeyedRotationToldFn)cam->desc02()->m29)(cam, out0, out1);
}

// Evaluates a weighted blend of angle curves at time dt: out0 gets the blended angle (each term
// added along the shortest way round, using the object's own link angle for a missing target) and
// out1 the weighted sum of the slopes; either may be null.
void EvaluateAngleBlendCurve(AngleBlendWeightCurve* o, PlacedObject* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
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
                f32 r = WrapAngle(((Rec2195_224*)cam->linkRecord)->angle - v0);
                v0 += r * e->weight / (w + e->weight);
            }
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                // address arithmetic over a variable index
                BlendTimeScale* q = (BlendTimeScale*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, a, b * scale, c, p0, p1);
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

// Evaluates a weighted blend of scalar curves at time dt: out0 gets the weighted sum of the values
// (a missing target uses the object's own value at the curve's index) and out1 the weighted sum of
// the slopes; either may be null.
void EvaluateValueBlendCurve(ValueBlendWeightCurve* o, PlacedObject* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
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
                sum0 += e->weight * cam->defaultValues[o->index];
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                // address arithmetic over a variable index
                BlendTimeScale* q = (BlendTimeScale*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, a, b * scale, c, p0, p1);
            sum0 += e->weight * x0;
            sum1 += e->weight * x1;
        }
    }
    if (out0)
        *out0 = sum0;
    if (out1)
        *out1 = sum1;
}

// Allocates a position curve of the given kind (0 to 2) and sets its method table; null otherwise.
PositionCurve* CreatePositionCurve(s32 kind)
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

// Allocates a rotation curve of the given kind (0 to 2) and sets its method table; null otherwise.
RotationCurve* CreateRotationCurve(s32 kind) {
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

// Allocates a scale curve of the given kind (0 or 1) and sets its method table; null otherwise.
ScaleCurve* CreateScaleCurve(s32 kind)
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

// Allocates a weight curve of the given kind (0 to 4) and sets its method table; null for any other
// kind. The kinds differ in size, so each has its own key layout.
WeightCurve* CreateWeightCurve(u32 kind)
{
    WeightCurve* o;
    switch (kind) {
    case 0:
        o = (WeightCurve*)AllocateZeroedFrontMemory(0x10);
        o->vt = &g_weightCurveKind0Methods;
        break;
    case 1:
        o = (WeightCurve*)AllocateZeroedFrontMemory(0x10);
        o->vt = &g_weightCurveKind1Methods;
        break;
    case 3:
        o = (WeightCurve*)AllocateZeroedFrontMemory(0x14);
        o->vt = &g_weightCurveKind3Methods;
        break;
    case 4:
        o = (WeightCurve*)AllocateZeroedFrontMemory(0x18);
        o->vt = &g_weightCurveKind4Methods;
        break;
    case 2:
        o = (WeightCurve*)AllocateZeroedFrontMemory(0x10);
        o->vt = &g_weightCurveKind2Methods;
        break;
    default:
        o = 0;
    }
    if (o)
        o->kind = kind;
    return o;
}

// Takes a zeroed slot from the world's pose source pool, sets its method table and initialises it
// for the owner.
Attachment* CreatePoseSource(World* root, PlacedObject* value, const T2195_Vt* table)
{
	Attachment* node = (Attachment*)PopZeroedFreeSlot(&root->pool1B20);
	node->vt = table;
	table->init(node, value);
	return node;
}

// Creates an owner-type pose source on the given world and owner and copies this one into it.
Attachment* ClonePoseSource(Attachment* self, World* a, PlacedObject* b)
{
    Attachment* node = CreatePoseSource(a, b, (const T2195_Vt*)g_ownerPoseSourceMethods);
    node->vt->copy(node, self);
    return node;
}

// Copies a pose source's whole record over this one, keeping this one's list links and owner.
void CopyPoseSource(Attachment* self, Attachment* src)
{
    Link2195 tmp = self->link;
    PlacedObject* saved = self->owner;
    CopyMemory(self, src, g_currentWorld->pool1B20.size);
    self->link = tmp;
    self->owner = saved;
}

// Sets the owner and puts all four mode bytes at -1 (unset).
void InitPoseSource(Attachment* self, PlacedObject* value)
{
	s8 m = -1;
	self->owner = value;
	self->mode2 = m;
	self->mode3 = -1;
	self->mode1 = m;
	self->mode0 = m;
}

// Removes the pose source from its owner's list and lets the owner's method 0x2B update; if it was
// the position (or orientation) attachment and the flags say so (1 and 2), the owner's velocity (or
// spin) is set to the constrained current one for a collider, or to zero for another object. The
// slot goes back to the world's pool.
void ReleasePoseSource(Attachment* self, s32 flags)
{
    PlacedObject* m = self->owner;
    s32 local[4];
    RemoveFromList(&m->list1E0, self);
    Attachment* a = m->positionAttachment;
    Attachment* b = m->orientationAttachment;
    m->desc02()->m2B(m);
    if (self == a && m->positionAttachment == 0 && (flags & 1) != 0) {
        if ((m->desc->flags & 2) != 0) {
            ConstrainColliderVector(m, (u8*)&((Collider*)m)->v440, (u8*)&m->v150, local, 0);
            m->desc02()->m20(m, (Vec4*)local);
        } else {
            SetPlacedObjectVelocity(m, (Vec4*)g_zeroVector);
        }
    }
    if (self == b && m->orientationAttachment == 0 && (flags & 2) != 0) {
        if ((m->desc->flags & 2) != 0) {
            ConstrainColliderVector(m, (u8*)&((Collider*)m)->v460, (u8*)&m->v160, local, 0);
            m->desc02()->m21(m, (Vec4*)local);
        } else {
            SetPlacedObjectSpin(m, (Vec4*)g_zeroVector);
        }
    }
    PushFreeSlot(&m->world->pool1B20, self);
}

// Gives the owner's position and a zero vector, then tells the owner through its slot-28 method if
// it has one.
void GetOwnerPosition(Attachment* self, Vec4* out1, Vec4* out2)
{
    *out1 = self->owner->v190;
    *out2 = *(Vec4*)g_zeroVector;
    if (self->owner->desc02()->m28 != 0) {
        ((PositionOutToldFn)self->owner->desc02()->m28)(self->owner, out1);
    }
}

// Gives the owner's orientation and a zero vector, then tells the owner through its slot-29 method.
void GetOwnerRotation(Attachment* self, Mat3* out1, Vec4* out2)
{
    *out1 = self->owner->m1A0;
    *out2 = *(Vec4*)g_zeroVector;
    ((FrameOutToldFn)self->owner->desc02()->m29)(self->owner, out1, out2);
}

// Gives the owner's link record value and a slope of 0.
void GetOwnerValue(Attachment* self, f32* value, f32* slope)
{
	Rec2195_224* rec = (Rec2195_224*)self->owner->linkRecord;
	*value = rec->initialAngle;
	*slope = 0.0f;
}

// Copies the 3-row identity matrix into out.
void GetIdentityMatrix(Attachment* unused, Mat3* out)
{
    Mat3* src = (Mat3*)g_identityMatrix;
    out->r[0] = src->r[0];
    out->r[1] = src->r[1];
    out->r[2] = src->r[2];
}

// Gives entry index of the owner's animation value array.
f32 GetOwnerIndexedValue(Attachment* self, s32 index)
{
	return self->owner->defaultValues[index];
}

// Picks the source's two modes from the owner: its own 0x2C9 and 0x2CA bytes unless they are -1,
// else 2 for a non-collider (or collider mode 3) and 3 otherwise.
void ChoosePoseSourceModes(Attachment* obj)
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

// Sets the owner's position and velocity (when this is its position attachment) and its rotation
// and spin (when it is its orientation attachment) from the pose source at once, if flag is set or
// the mode is 2.
void ApplyPoseSource(Attachment* self, s32 flag)
{
    PoseLocals loc;
    PlacedObject* s2 = self->owner;

    if (self == s2->positionAttachment) {
        if (flag != 0 || self->mode0 == 2) {
            self->vt->getPos(self, 0.0f, &loc.pos, &loc.vec);
            s2->desc02()->m1D(s2, &loc.pos);
            s2->desc02()->m20(s2, &loc.vec);
        }
    }
    if (self == s2->orientationAttachment) {
        if (flag != 0 || self->mode1 == 2) {
            self->vt->getRot(self, 0.0f, &loc.rot, &loc.pos);

            s2->desc02()->m1E(s2, &loc.rot);
            s2->desc02()->m21(s2, &loc.pos);
        }
    }
}

// Computes in out the acceleration that pulls the owner's position toward the target position a and
// its velocity toward b: a spring term along the offset (quadratic coefficients from p20C, as
// k2*len + k1 + k0/len) and a damping term on the velocity difference (coefficients of p210,
// limited by 1 over the frame time).
void ComputePositionSpringAcceleration(PlacedObject* self, f32 dt, Vec4* a, Vec4* b, Vec4* out)
{
    Vec4 force = *(Vec4*)g_zeroVector;
    Vec4 d;
    f32* k = (f32*)self->p20C;
    f32* k2;
    if (k != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(self->pos));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (1e-4f < len) {
            f32 s = k[2] * len + k[1] + k[0] / len;
            Vu0::Q(force) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(s));
        }
    }
    k2 = (f32*)self->p210;
    if (k2 != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(self->v150));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (1e-4f < len) {
            f32 s = k2[2] * len + k2[1] + k2[0] / len;
            f32 limit = 1.0f / dt;
            if (limit < s) {
                s = limit;
            }
            Vu0::Q(force) = Vu0::MulAddX(Vu0::Q(force), Vu0::Q(d), Vu0::Scalar(s));
        }
    }
    *out = force;
}

f32 SplitVectorAlongAxis(Vec4* v, Vec4* axis, Vec4* along, Vec4* rest);
// The ramp with its floats first (the value, the target, the step), as retail sets $f12 to
// $f14 before the profile and the rate's address.
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
extern f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
extern const Vec4 g_unitXVector;

// Moves the owner's position toward what the pose source gives (position A and velocity B), once
// per frame, by mode: 2 and 7 copy it; 1 integrates a spring acceleration; 3, 6 and 9 move toward
// it with a speed limited by a ramp (6 must also arrive by an end time) and drop to mode 7 once
// there; 4 follows a Hermite segment that ends exactly at the end time.
void ApplyPoseSourcePosition(TrackFollowAttachment* self)
{
    PlacedObject* owner = self->owner;
    f32 dt;
    f32 now;
    Vec4 A;
    Vec4 B;
    if (owner->frameStepClock != 0) {
        dt = g_gameClock.step;
    } else {
        dt = g_gameClock.dt;
    }
    if (owner->frameStepClock != 0) {
        now = g_gameClock.elapsed;
    } else {
        now = g_gameClock.time;
    }
    self->vt->getPos(self, 0.0f, &A, &B);
    switch (self->mode0) {
    case 2:
    case 7:
        owner->pos = A;
        owner->v150 = B;
        break;
    case 1: {
        Vec4 C;
        ComputePositionSpringAcceleration(owner, dt, &A, &B, &C);
        Vu0::Q(C) = Vu0::Add(Vu0::Q(C), Vu0::Q(owner->v170));
        Vu0::Q(owner->pos) = Vu0::MulAddX2WeightFirst(Vu0::Vec::Of(owner->pos), Vu0::Vec::Scalar(dt), Vu0::Vec::Of(owner->v150), Vu0::Vec::Scalar(dt * (dt * 0.5f)), Vu0::Vec::Of(C)).q;
        Vu0::Q(owner->v150) = Vu0::MulAddX(Vu0::Vec::Of(owner->v150), Vu0::Vec::Of(C), Vu0::Vec::Scalar(dt)).q;
        break;
    }
    case 3:
    case 6:
    case 9: {
        Vec4 d;
        Vec4 dir;
        Vec4 rest;
        RampProfile prof;
        f32 speed;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(A), Vu0::Q(owner->pos));
        Vu0::Q(dir) = Vu0::Q(d);
        Vu0::Vec fallback = Vu0::Vec::Of(g_unitXVector);
        Vu0::Vec len = Vu0::Length(Vu0::Vec::Of(d));
        f32 dist = Vu0::ToFloat(len.q);
        Vu0::Vec n;
        if (dist < 0.0001f) {
            n = fallback;
        } else {
            n = Vu0::DivX(Vu0::Vec::Of(d), len);
        }
        Vu0::Q(dir) = n.q;
        f32 r = SplitVectorAlongAxis(&B, &dir, 0, &rest);
        prof.maxSpeed = ((RampProfile*)owner->p21C)->maxSpeed + r;
        prof.endSpeed = ((RampProfile*)owner->p21C)->endSpeed + r;
        prof.rampTime = ((RampProfile*)owner->p21C)->rampTime;
        f32 reach = ApproachValueWithRamp(0.0f, dist, dt, &prof, &speed);
        if (self->mode0 == 6) {
            f32 end = self->endTime;
            f32 lim;
            if (now < end) {
                lim = dist * dt / (end - now + dt);
            } else {
                lim = dist;
            }
            if (reach < lim) {
                reach = lim;
                speed = reach / dt;
            }
        }
        if (dist <= reach) {
            owner->pos = A;
            owner->v150 = B;
            if (self->mode0 != 9) {
                self->mode0 = 7;
            }
        } else {
            Vu0::Q(owner->pos) = Vu0::MulAddX(Vu0::Vec::Of(owner->pos), Vu0::Vec::Of(dir), Vu0::Vec::Scalar(reach)).q;
            Vu0::Q(owner->v150) = Vu0::MulAddX(Vu0::Vec::Of(rest), Vu0::Vec::Of(dir), Vu0::Vec::ScalarAt(speed)).q;
        }
        break;
    }
    case 4: {
        f32 end = self->endTime;
        f32 left = end - now;
        if (left < dt) {
            Vec4 k;
            Vu0::Q(k) = Vu0::FromFloat(now + dt - end);
            Vu0::Q(owner->pos) = Vu0::MulAddX(Vu0::Q(A), Vu0::Q(B), Vu0::Q(k));
            owner->v150 = B;
        } else {
            Vec4 p;
            Vec4 v;
            EvaluateHermiteVectorSegment(left, &owner->pos, &owner->v150, &A, &B, dt, 1.0f, &p, &v, 0);
            owner->pos = p;
            owner->v150 = v;
        }
        break;
    }
    }
}

// Computes in out the angular acceleration that pulls the owner's rotation toward the target
// rotation and spin: a spring term along the axis of the remaining rotation (a quadratic in the
// angle with the coefficients of p214) and a damping term toward the target's spin (coefficients of
// p218, limited by 1 over the frame time).
void ComputeRotationSpringAcceleration(PlacedObject* self, f32 dt, Mat3* rot, Vec4* spin, Vec4* out)
{
    Vec4 force = *(Vec4*)g_zeroVector;
    if (self->p214 != 0) {
        Mat3 m;
        Vec4 axis;
        f32 angle;
        MultiplyMatrices3x3(&self->rot, rot, &m);
        MatrixToAxisAngle(&m, &angle, &axis);
        if (1e-4f < angle) {
            f32* k = (f32*)self->p214;
            f32 s = k[2] * angle * angle + k[1] * angle + k[0];
            Vu0::Q(force) = Vu0::MulX(Vu0::Q(axis), Vu0::Scalar(s));
        }
    }
    if (self->p218 != 0) {
        Vec4 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*spin), Vu0::Q(self->v160));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (1e-4f < len) {
            f32* k = (f32*)self->p218;
            f32 s = k[2] * len + k[1] + k[0] / len;
            f32 limit = 1.0f / dt;
            if (limit < s) {
                s = limit;
            }
            Vu0::Q(force) = Vu0::MulAddX(Vu0::Q(force), Vu0::Q(d), Vu0::Scalar(s));
        }
    }
    *out = force;
}

void OrthonormalizeMatrix(Mat3* m);
void BlendRotationsWithSpin(f32 dur, f32 t, f32 e, Mat3* a, const Vec4* wa, Mat3* b, const Vec4* wb, Mat3* out, Vec4* outW,
                            s32 unused6);

// Moves the owner's rotation toward the pose source's orientation A and spin B (and a link angle
// value) once per frame, by mode: 2 and 7 copy; 1 integrates a spring acceleration; 3, 6 and 9 turn
// at a speed limited by a ramp (6 must arrive by an end time) and drop to 7 when there; 4 is a
// timed blend ending exactly at the end time.
void ApplyPoseSourceRotation(Attachment* self)
{
    PlacedObject* owner = self->owner;
    f32 dt;
    f32 now;
    Mat3 A;
    Vec4 B;
    f32 value;
    f32 slope;
    s32 hasValue;
    if (owner->frameStepClock != 0) {
        dt = g_gameClock.step;
    } else {
        dt = g_gameClock.dt;
    }
    if (owner->frameStepClock != 0) {
        now = g_gameClock.elapsed;
    } else {
        now = g_gameClock.time;
    }
    self->vt->getRot(self, 0.0f, &A, &B);
    if (owner->linkRecord != 0 && (owner->linkRecord->flags & 0x20)) {
        self->vt->getValue(self, &value, &slope);
        hasValue = 1;
    } else {
        hasValue = 0;
    }
    switch (self->mode1) {
    case 2:
    case 7:
        owner->rot = A;
        owner->v160 = B;
        if (hasValue) {
            owner->linkRecord->angle = value;
            owner->linkRecord->angleSlope = slope;
        }
        break;
    case 1: {
        Vec4 C;
        Vec4 w;
        Mat3 m;
        ComputeRotationSpringAcceleration(owner, dt, &A, &B, &C);
        Vu0::Q(C) = Vu0::Add(Vu0::Q(C), Vu0::Q(owner->v180));
        Vu0::Vec s;
        s.q = Vu0::ScalarInGpr(dt);
        Vu0::Q(w) = Vu0::MulXSum(Vu0::Vec::Of(owner->v160), s, Vu0::Vec::Of(C), Vu0::Vec::Scalar(dt * (dt * 0.5f))).q;
        BuildRotationFromVector((Vec4*)&w, (Mat3*)&m);
        MulRotationIntoRotX(owner, m, owner->rot);
        OrthonormalizeMatrix(&owner->rot);
        Vu0::Q(owner->v160) = Vu0::MulAddX(Vu0::Vec::Of(owner->v160), Vu0::Vec::Of(C), Vu0::Vec::ScalarInGpr(dt)).q;
        if (hasValue) {
            owner->linkRecord->angle = ApproachValueWithRamp(owner->linkRecord->angle, value, dt, (RampProfile*)owner->p220, &owner->linkRecord->angleSlope);
        }
        break;
    }
    case 3:
    case 6:
    case 9: {
        Mat3 m;
        Vec4 axis;
        Vec4 rest;
        Vec4 prof;
        f32 angle;
        f32 rate;
        s32 settle = 0;
        MultiplyMatrices3x3(&owner->rot, &A, &m);
        MatrixToAxisAngle(&m, &angle, &axis);
        f32 r = SplitVectorAlongAxis(&B, &axis, 0, &rest);
        prof.x = ((f32*)owner->p220)[0] + r;
        prof.y = ((f32*)owner->p220)[1] + r;
        prof.z = ((f32*)owner->p220)[2];
        f32 reach = ApproachValueWithRamp(0.0f, angle, dt, (RampProfile*)&prof, &rate);
        if (self->mode1 == 6) {
            f32 end = ((TrackFollowAttachment*)self)->endTime;
            f32 lim;
            if (now < end) {
                lim = angle * dt / (end - now + dt);
            } else {
                lim = angle;
            }
            if (reach < lim) {
                reach = lim;
                rate = reach / dt;
            }
        }
        if (angle <= reach) {
            owner->rot = A;
            owner->v160 = B;
            settle = self->mode1 != 9;
        } else {
            BuildAxisAngleMatrix(&axis, &m, reach);
            MulRotationIntoRotX(owner, m, owner->rot);
            OrthonormalizeMatrix(&owner->rot);
            Vu0::Q(owner->v160) = Vu0::MulAddX(Vu0::Q(rest), Vu0::Q(axis), Vu0::ScalarAt(rate));
        }
        if (hasValue) {
            owner->linkRecord->angle = ApproachValueWithRamp(owner->linkRecord->angle, value, dt, (RampProfile*)owner->p220, &owner->linkRecord->angleSlope);
            if (owner->linkRecord->angle != value) {
                settle = 0;
            }
        }
        if (settle) {
            self->mode1 = 7;
        }
        break;
    }
    case 4: {
        f32 left = ((TrackFollowAttachment*)self)->endTime - now;
        if (left <= dt) {
            s32 still = 0;
            if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(B))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(B))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(B))) < 0.0001f) {
                still = 1;
            }
            if (still) {
                owner->rot = A;
                owner->v160 = *(Vec4*)g_zeroVector;
            } else {
                Vec4 w;
                Mat3 m;
                Vu0::Q(w) = Vu0::MulX(Vu0::Q(B), Vu0::Scalar(now + dt - ((TrackFollowAttachment*)self)->endTime));
                BuildRotationFromVector((Vec4*)&w, (Mat3*)&m);
                MulRotationIntoRotMatFirst(owner, m, A);
                owner->v160 = B;
            }
            if (hasValue) {
                owner->linkRecord->angle = value;
                owner->linkRecord->angleSlope = 0.0f;
            }
        } else {
            Mat3 m;
            Vec4 s;
            BlendRotationsWithSpin(left, dt, 1.0f, &owner->rot, &owner->v160, &A, &B, &m, &s, 0);
            owner->rot = m;
            owner->v160 = s;
            if (hasValue) {
                EvaluateHermiteSegment(left, dt, 1.0f, owner->linkRecord->angle, owner->linkRecord->angleSlope, value, slope, &owner->linkRecord->angle, &owner->linkRecord->angleSlope, 0);
            }
        }
        break;
    }
    }
}

// Reads the indexed value val from the pose source and writes it into the owner's value array: mode
// 2 stores it directly, mode 3 eases the stored value toward it with the value ramp profile.
void ApplyPoseSourceIndexedValue(Attachment* self, s32 val)
{
    f32 ret = self->vt->getIndexed(self, val);
    switch (self->mode3) {
    case 2:
        self->owner->currentValues[val] = ret;
        break;
    case 3: {
        f32 cur = self->owner->currentValues[val];
        f32 limit = self->owner->frameStepClock ? g_frameStep : g_frameDt;
        self->owner->currentValues[val] = ApproachValueWithRamp(cur, ret, limit, (RampProfile*)g_valueRampProfile, 0);
        break;
    }
    }
}

// Gives the object's position and velocity t seconds ahead: its own if t is 0, the position
// attachment's if it has one, else the plain linear extrapolation pos + velocity * t.
void GetPlacedObjectPositionAt(PlacedObject* self, f32 t, Vec4* pos, Vec4* vec)
{
    Vec4 k;
    Attachment* source = self->positionAttachment;
    if (t == 0.0f) {
        *pos = self->pos;
        *vec = self->v150;
    } else if (source) {
        source->vt->getPos(source, t, pos, vec);
    } else {
        u128 d = Vu0::Q(self->v150);
        Vu0::Q(k) = Vu0::FromFloat(t);
        Vu0::Q(*vec) = d;
        Vu0::Q(*pos) = Vu0::Add(Vu0::Q(self->pos), Vu0::MulX(d, Vu0::Q(k)));
    }
}

// Gives the placed object's rotation and spin at t seconds from now: now if t is zero, from its
// orientation attachment if it has one, otherwise by turning the current rotation by its spin times
// t.
void GetPlacedObjectRotationAt(PlacedObject* self, f32 t, Mat3* rot, Vec4* vec)
{
    Vec4 d;
    Mat3 m;
    Vec4 k;
    Attachment* source = self->orientationAttachment;
    if (t == 0.0f) {
        *rot = self->rot;
        *vec = self->v160;
    } else if (source) {
        source->vt->getRot(source, t, rot, vec);
    } else {
        u128 w = Vu0::Q(self->v160);
        Vu0::Q(k) = Vu0::FromFloat(t);
        Vu0::Q(*vec) = w;
        Vu0::Q(d) = Vu0::MulX(w, Vu0::Q(k));
        BuildRotationFromVector((Vec4*)&d, (Mat3*)&m);
        MulRotationRowsIndexed(rot, m, self->rot);
    }
}

// Turns a mode0 or mode1 of 7 into 3.
void SettlePoseSourceModes(Attachment* self)
{
    if (self->mode0 == 7) {
        self->mode0 = 3;
    }
    if (self->mode1 == 7) {
        self->mode1 = 3;
    }
}

// Sets the pose source up as a copy of the owner's current position, orientation and animation
// values, with an identity matrix beside it.
void InitSnapshotPoseSource(OwnerSnapshotAttachment* self, PlacedObject* src)
{
    InitPoseSource(self, src);
    self->pos = src->v190;
    self->rot.r[0] = src->m1A0.r[0];
    self->rot.r[1] = src->m1A0.r[1];
    self->rot.r[2] = src->m1A0.r[2];
    Rec2195_224* p = (Rec2195_224*)src->linkRecord;
    if (p != 0) {
        if (p->flags & 0x20) {
            self->f80 = p->initialAngle;
        }
    }
    Vec4* table = (Vec4*)g_identityMatrix;
    self->m90.r[0] = table[0];
    self->m90.r[1] = table[1];
    self->m90.r[2] = table[2];
    self->countC0 = src->valueCount;
    self->valuesC4 = src->defaultValues;
}

// Gives the snapshot position and vector, then tells the owner through its slot-28 method if set.
void GetSnapshotPosition(OwnerSnapshotAttachment* src, Vec4* d0, Vec4* d1)
{
    *d0 = src->pos;
    *d1 = src->vec;
    PlacedObject* obj = src->owner;
    PositionToldFn fn = obj->desc02()->m28;
    if (fn != 0) {
        fn(obj, d0, d1);
    }
}

// Gives the snapshot orientation and vector, then tells the owner through its slot-29 method.
void GetSnapshotRotation(OwnerSnapshotAttachment* src, Mat3* d0, Vec4* d1)
{
    d0->r[0] = src->rot.r[0];
    d0->r[1] = src->rot.r[1];
    d0->r[2] = src->rot.r[2];
    *d1 = src->v70;
    PlacedObject* obj = src->owner;
    OrientationToldFn fn = (OrientationToldFn)obj->desc02()->m29;
    fn(obj, d0, d1);
}

// Gives the two values saved in the snapshot.
void GetSnapshotValue(OwnerSnapshotAttachment* self, f32* first, f32* second)
{
	*first = self->f80;
	*second = self->f84;
}

// Copies the snapshot's second matrix (the identity set at init) into output.
void GetSnapshotMatrix(OwnerSnapshotAttachment* self, Mat3* output)
{
	output->r[0] = self->m90.r[0];
	output->r[1] = self->m90.r[1];
	output->r[2] = self->m90.r[2];
}

// Gives entry i of the snapshot's value array.
f32 GetSnapshotIndexedValue(OwnerSnapshotAttachment* self, s32 i)
{
    return self->valuesC4[i];
}

// Sets the pose source up to point at the owner's own position, orientation and animation values
// (and its link record's value when flagged 0x20) instead of copying them.
void InitLinkedPoseSource(OwnerPointerAttachment* self, PlacedObject* src)
{
    InitPoseSource(self, src);
    self->pos = &src->v190;
    self->rot = &src->m1A0;
    self->count = &src->valueCount;
    self->vec = (Vec4*)g_zeroVector;
    self->vec2 = (Vec4*)g_zeroVector;
    self->values = src->defaultValues;
    Rec2195_224* o = (Rec2195_224*)src->linkRecord;
    if (o != 0) {
        if (o->flags & 0x20) {
            self->p30 = (f32*)g_zeroVector;
            self->p2C = &o->initialAngle;
        }
    }
    self->ident = (Mat3*)g_identityMatrix;
}

// Gives the linked position and vector, then calls the owner's slot-28 method if it has one.
void GetLinkedPosition(OwnerPointerAttachment* self, Vec4* first, Vec4* second)
{
	*first = *self->pos;
	*second = *self->vec;
	OwnerToldFn callback = (OwnerToldFn)self->owner->desc02()->m28;
	if (callback)
		callback(self->owner);
}

// Gives the linked orientation and vector, then tells the owner through its slot-29 method.
void GetLinkedRotation(OwnerPointerAttachment* self, Mat3* d1, Vec4* d2)
{
    Mat3* s = self->rot;
    d1->r[0] = s->r[0];
    d1->r[1] = s->r[1];
    d1->r[2] = s->r[2];
    *d2 = *self->vec2;
    self->owner->desc02()->m29(self->owner, d1, d2);

}

// Gives the two linked values, read through the pointers at 0x2C and 0x30.
void GetLinkedValue(OwnerPointerAttachment* self, f32* a, f32* b)
{
    *a = *self->p2C;
    *b = *self->p30;
}

// Copies the linked identity matrix into dst.
void GetLinkedMatrix(OwnerPointerAttachment* self, Mat3* dst)
{
    Mat3* s = self->ident;
    dst->r[0] = s->r[0];
    dst->r[1] = s->r[1];
    dst->r[2] = s->r[2];
}

// Gives entry i of the linked value array.
f32 GetLinkedIndexedValue(OwnerPointerAttachment* self, s32 i)
{
    return self->values[i];
}

// Sets the pose source up with two identity matrices.
void InitIdentityPoseSource(IdentityMatrixAttachment* self, PlacedObject* owner)
{
    InitPoseSource(self, owner);
    Vec4* src = (Vec4*)g_identityMatrix;
    Vec4* d1 = self->m40.r;
    Vec4* d2 = self->m90.r;
    self->m40.r[0] = src[0];
    d1[1] = src[1];
    d1[2] = src[2];
    self->m90.r[0] = src[0];
    d2[1] = src[1];
    d2[2] = src[2];
}

// Gives the position at time t from the next pose source in the chain whose mode0 is not 0 or -1
// (the owner's position if there is none), then adds this source's own offset vectors.
void GetIdentityPosePosition(OwnerSnapshotAttachment* self, f32 t, Vec4* pos, Vec4* vec)
{
    Attachment* p = self;
    while ((p = p->link.next) != 0) {
        s8 f = p->mode0;
        if (f == 0) { p = 0; break; }
        if (f != -1) break;
    }
    if (p != 0) {
        p->vt->getPos(p, t, pos, vec);
    } else {
        GetOwnerPosition(self, pos, vec);
    }
    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(*pos), Vu0::Q(self->pos));
    Vu0::Q(*vec) = Vu0::Add(Vu0::Q(*vec), Vu0::Q(self->vec));
}

// Gives the rotation and spin of a pose source that stands on another one: the next attachment of
// the chain with a defined orientation (or the owner's own) is asked, the rotation is composed with
// this source's rotation, and the spin is rotated by it and offset by v70.
void GetIdentityPoseRotation(OwnerSnapshotAttachment* self, f32 t, Mat3* rot, Vec4* vec)
{
    Attachment* p = self;
    while ((p = p->link.next) != 0) {
        s8 f = p->mode1;
        if (f == 0) { p = 0; break; }
        if (f != -1) break;
    }
    if (p != 0) {
        p->vt->getRot(p, t, rot, vec);
    } else {
        GetOwnerRotation(self, rot, vec);
    }
    MulRotationSetRows(rot, self->rot, *rot);
    Vu0::Q(*vec) = Vu0::Add(Vu0::RotateMembers(self->rot, Vu0::Q(*vec)), Vu0::Q(self->v70));
}

// Gives the value from the next pose source in the chain whose mode1 is not 0 or -1 (the owner's
// own value if there is none).
void GetNextPoseSourceValue(Attachment* self, f32* a1, f32* a2)
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

// Gives the matrix of a pose source that stands on another one: the next attachment of the chain
// with a defined matrix (or the identity) is asked and the result is composed with this source's
// own matrix.
void GetIdentityPoseMatrix(OwnerSnapshotAttachment* self, Mat3* out)
{
    Mat3 m;
    Attachment* p = self;
    while ((p = p->link.next) != 0) {
        s8 f = p->mode2;
        if (f == 0) { p = 0; break; }
        if (f != -1) break;
    }
    if (p != 0) {
        p->vt->getMatrix(p, &m);
    } else {
        GetIdentityMatrix(0, &m);
    }
    MulRotationRowsOnce(out, self->m90, m);
}

// The identity pose has no values: always 0.
f32 GetIdentityPoseIndexedValue(void)
{
    return 0.0f;
}

// Initialises the pose source with two constants, 1.0 and 0.25, in its aim fields.
void InitAimPoseSource(TiltValueAttachment* self, PlacedObject* a1)
{
    InitPoseSource(self, a1);
    self->tiltScale = 1.0f;
    self->sampleTime = 0.25f;
}


// Gives a rotation that points the owner along its velocity with up taken against gravity (the
// collider's or the world's), tilted toward the change in velocity of the position source over f20
// seconds, scaled by f1C; the angular velocity is zero.
void GetAimPoseRotation(TiltValueAttachment* self, Mat3* out, Vec4* vec)
{
    Vec4 dir;
    Vec4 vel;
    Vec4* pd = &dir;
    PlacedObject* owner = self->owner;
    Attachment* source = owner->positionAttachment;
    Vu0::Vec g;
    if ((owner->desc->flags & 2) != 0) {
        g = Vu0::MulX(Vu0::Vec::Of(((Collider*)owner)->gravity), Vu0::Vec::Scalar(-1.0f));
    } else {
        g = Vu0::MulX(Vu0::Vec::Of(owner->world->gravity), Vu0::Vec::Scalar(-1.0f));
    }
    Vu0::Q(*pd) = g.q;
    if (source != 0 && self->sampleTime != 0.0f && self->tiltScale != 0.0f) {
        source->vt->getPos(source, self->sampleTime, 0, &vel);
        u128 w1 = Vu0::ScalarAt(self->tiltScale);
        Vu0::Q(dir) = Vu0::MulAddX(Vu0::Q(dir), Vu0::DivX(Vu0::Sub(Vu0::Q(vel), Vu0::Q(owner->v150)), Vu0::ScalarAt(self->sampleTime)), w1);
    }
    BuildBasisFromXAndZHint(&owner->v150, &dir, out);
    *vec = *(Vec4*)g_zeroVector;
}

// Removes the track's pose source from its player's list, clears the player's driven pointer if it
// was this one, and releases it.
void ReleaseTrackPoseSource(TrackFollowAttachment* self, s32 a1)
{
    AnimationPlayer* o = self->player;
    RemoveFromList(&o->list44, self);
    if (o->driven == self) {
        o->driven = 0;
    }
    ReleasePoseSource(self, a1);
}

// Copies a pose source over this track source, keeping its player and its pair at 0x20.
void CopyTrackPoseSource(TrackFollowAttachment* self, Attachment* a1)
{
    AnimationPlayer* saved = self->player;
    Pair2195 tmp = self->w20;
    CopyPoseSource(self, a1);
    self->w20 = tmp;
    self->player = saved;
}

// Gives the position and velocity of the pose source's animation track at the player's time (moved
// ahead by f seconds, with the loop mode applied, and further ahead while in mode 4 until its end
// time); if the track has no position curve it gives the owner's own.
void GetTrackPosition(TrackFollowAttachment* self, Vec4* a1, Vec4* a2, f32 f)
{
    AnimationPlayer* track = self->player;
    AnimationTrack* e = &track->anim->tracks[self->index];
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
            f32 d = self->endTime - g_gameTime[0] - track->delay;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->speed;
            }
        }
        e->pos->vt->eval(e->pos, self->owner, tmp[0], track->speed, 0, a1, a2);
        return;
    }
    GetOwnerPosition(self, a1, a2);
}

// Gives the rotation and angular velocity of the pose source's animation track at the player's time
// (moved ahead by f seconds, with the loop mode applied, and further ahead while in mode 4 until
// its end time); if the track has no rotation curve it gives the owner's own.
void GetTrackRotation(TrackFollowAttachment* self, Mat3* a1, Vec4* a2, f32 f)
{
    PlacedObject* p4 = self->owner;
    AnimationPlayer* track = self->player;
    AnimationTrack* e = &track->anim->tracks[self->index];
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
            f32 d = self->endTime - g_gameTime[0] - track->delay;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->speed;
            }
        }
        e->rot->vt->eval(e->rot, p4, 0, a1, a2, tmp[0], track->speed);
        return;
    }
    GetOwnerRotation(self, a1, a2);
}

// Gives the value of the animation track's weight curve at the player's time, or the owner's own
// value when the track has no weight curve.
void GetTrackValue(TrackFollowAttachment* self, f32* a1, f32* a2)
{
    f32* saved = a1;
    PlacedObject* f4 = self->owner;
    AnimationPlayer* player = self->player;
    AnimationTrack* e = &player->anim->tracks[self->index];
    WeightCurve* target = e->weight;
    if (target) {
        target->vt->eval(target, f4, player->time, player->speed, 0, saved, a2);
    } else {
        GetOwnerValue(self, saved, a2);
    }
}

// Gives the scale matrix of the animation track's scale curve at the player's time, or the identity
// when the track has none.
void GetTrackScaleMatrix(TrackFollowAttachment* self, Mat3* a1)
{
    Mat3* saved = a1;
    PlacedObject* f4 = self->owner;
    AnimationPlayer* player = self->player;
    AnimationTrack* e = &player->anim->tracks[self->index];
    ScaleCurve* target = e->scale;
    if (target) {
        target->vt->eval(target, f4, 0, saved, player->time);
    } else {
        GetIdentityMatrix(self, saved);
    }
}

// Gives the track's indexed curve at index, evaluated at the player's time.
f32 GetTrackIndexedValue(TrackFollowAttachment* self, s32 index)
{
    AnimationPlayer* track = self->player;
    AnimationTrack* row = &track->anim->tracks[self->index];
    WeightCurve** values = row->morph;
    WeightCurve* object = values[index];
    f32 result;
    object->vt->eval(object, self->owner, track->time, track->speed, 0, &result, 0);
    return result;
}
