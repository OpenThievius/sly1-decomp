// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x182C18 to 0x184D78: the methods of class 0x01, the root of every object class
// (include/base_object.h), with its callbacks, properties and script events, then the cone
// volume and its fitting helpers. Its name is ours, after the class.
#include "common.h"
#include "screen_element.h"
#include "switched_collider.h"
#include "path_curve_object.h"
#include "cone_volume.h"
#include "world.h"
#include "queued_call.h"
#include "debug_assert.h"
#include "masked_collider.h"
#include "object_link.h"
#include "message_body.h"
#include "shapes.h"
#include "script_builtin.h"
#include "game_progress.h"
#include "globals.h"
#include "script_value.h"
#include "fpu.h"
#include "collider.h"
#include "vu0.h"
#include "packet_writer.h"
#include "asm_func.h"
struct Mat02;


void SetExtraObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value); // stays void: retail returns a ScriptValue by value through the hidden pointer, a call with no value register, which a pointer return changes in func_00183A90 and func_00183C38

ScriptValue* BuildScriptListFromPairs(ScriptValue* self, s32 n, s32* keys, s32* vals);

int AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);

void CopyObjectData(void* self, void* src);


void* TakeCallRecord(World* self);

void RemoveFromList(List01* list, void* item);

void NoteConeVolumeLightingChange(ConeVolume* self);

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);

void* AllocateFrontMemory(s32 size);

void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);

s32 IsObjectAttached(BaseObject* self);

void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);



void UnregisterPlacedObject(PlacedObject* self);

void RemoveConeVolumeFromWorldList(void* self);

struct ValueRange;
s32 IsInsideRange(ValueRange* span, f32 x);

void AddObjectKeyToOwner(BaseObject* self);

s32 IsObjectAttached(BaseObject* self);

struct __attribute__((packed)) Pack_183B20 { u64 v; };

void* AcquirePairPayload(void);

void* AcquireVectorAPayload(void);

void ComputePlacedObjectWorldFrame(PlacedObject* self);

void RefreshConeVolumeShape(ConeVolume* self);

void UpdateConeVolumeBounds(ConeVolume* self);

extern u8 g_markStacks[];

struct MarkStacks;
void AddMarkRootList(MarkStacks* self, R11B008List* list);

void CopyMemory(void* dst, void* src, u32 size);

u8* GetHashedSlot(u8* base, s32 n);

void RemoveFromList(List01* list, void* item);

void AppendToList(List01* self, void* item);

ScriptScope* NewScriptScope(void);

void MarkPoolLiveEnds(MarkStacks* stacks);

void CopyScriptScope(ScriptScope* src, ScriptScope* dst);

struct MarkEntry;
void AddUniqueMarkRoot(MarkStacks* self, MarkEntry* value);

void AppendToList(List01* self, void* item);

void RegisterPlacedObject(PlacedObject* self);

void AddConeVolumeToWorldList(ConeVolume* self);

void RegisterObject(void* self);

void AppendToList(List01* self, void* item);

s32 IsInList(List01* self, void* item);

s32 IsObjectAttached(BaseObject* self);

void RemoveFromList(List01* list, void* item);

void UnregisterObject(void* self);

void RemoveFromList(List01* list, void* item);


struct T219CHook;
struct World;
void ReleaseCallRecords(World* self, T219CHook* node);

s32 GetAliasId(BaseObject* self);

void AppendToList(List01* self, void* item);

s32 IsInList(List01* self, void* item);

// The callback list's helpers (func_001831E8 adds, func_00183238 removes), as the slots call them.
void AddCallbackNode(World* world, Callback01** head, void* fn, void* ctx);

void RemoveCallbackNode(World* world, Callback01** head, void* fn, void* ctx);

void* AcquireVectorBPayload(void);

void ReadPropertyRecords(void* a, void* b);

// The script function func_001834A0 calls (the value of a script variable): the scope it was
// made in, its parameters, its body.
struct ScriptParam { s32 a; s32 name; ScriptParam* next; };

struct ScriptParams { s32 pad0; s32 selfName; ScriptParam* head; };

struct ScriptMethod { ScriptScope* scope; ScriptParams* params; s32 pad8; s32 padC; void* body; };

void MarkPoolLiveEnds(MarkStacks* stacks);

s32 LookupScriptVariable(ScriptScope* scope, s32 key, s32 flag, ScriptValue* out);

void SetScriptScopeParent(ScriptScope* scope, ScriptScope* parent);

void* DefineScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value);

void* EvalScriptBody(ScriptValue* ret, R11B008Node* list, ScriptScope* scope);

extern const s32 D_00244EC0[];
extern s32 D_00244DFC[];

s32 SuppressScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);

void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

void RunScriptEventHandler(BaseObject* self, s32 key, R11B008Node* list);

void UpdateConeVolumeTangents(ConeVolume* self);

void InitPlacedObject(PlacedObject* self);

s32 IsObjectAttached(BaseObject* self);

void RemoveConeVolumeFromWorldList(ConeVolume*);

void CopyPlacedObject(PlacedObject* self, PlacedObject* src);

extern "C" f32 Cosine(f32 x);

struct LinePoints { f32 x; f32 y; };

void FitLineThroughPoints(f32 a, f32 b, f32 c, f32 d, f32* out0, f32* out1);

extern s32 g_frameCount;

extern s32 g_lightingChangeFrame;

void UpdateConeVolumeTangents(void* self);

struct Quad_001B4580;
void ConvertRgb255ToHsv255(Quad_001B4580* src, f32* dst);

void SetConeVolumeColor(ConeVolume* self, Quad16* src);


extern "C" f32 Tangent(f32 x);

struct ClampHelper {
    static f32 Of(f32 v, f32 lo, f32 hi)
    {
        if (v < lo)
            return lo;
        if (hi < v)
            return hi;
        return v;
    }
};

extern "C" f32 Cosine(f32 x);


void InitObject(BaseObject* self)
{
    self->desc->m01(self);
    self->desc->m02(self);
}

void StartObject(BaseObject* self)
{
    TriggerScriptEvent(self, 0, 0, 0);
}

void AddObjectToParentList(BaseObject* self)
{
    List01* sub;
    if (self->parent == 0) {
        sub = &self->world->list48;
    } else {
        sub = &((PlacedObject*)self->parent)->children;
    }
    if (IsInList(sub, self) != 0) {
        return;
    }
    AppendToList(sub, self);
    if (IsObjectAttached(self) != 0) {
        self->desc->m04(self);
    }
}

void AttachObject(BaseObject* self)
{
    self->desc->m06(self);
    self->desc->m0E(self, 1, self);
}

void RegisterObject(BaseObject* self)
{
    (void)self;
}

void RemoveObjectFromParentList(BaseObject* self)
{
    List01* sub;
    if (self->parent == 0) {
        sub = &self->world->list48;
    } else {
        sub = &((PlacedObject*)self->parent)->children;
    }
    if (IsInList(sub, self) != 0) {
        if (IsObjectAttached(self) != 0) {
            RemoveFromList(sub, self);
            self->desc->m05(self);
            return;
        }
        RemoveFromList(sub, self);
    }
}

void AddObjectKeyToOwner(BaseObject* self)
{
    PlacedObject* target;
    if (self->desc->flags & 1) {
        target = (PlacedObject*)self;
    } else {
        target = (PlacedObject*)self->parent;
    }
    if (target != 0) {
        Key02* n = (Key02*)AllocateFrontMemory(8);
        n->key = self->id;
        n->next = target->keys;
        target->keys = n;
    }
}

void AddObjectKeyIfLevelInRange(BaseObject* self, void* target)
{
    if (IsInsideRange((ValueRange*)target, g_currentEntry->dt)) {
        AddObjectKeyToOwner(self);
    }
}

void DetachObject(BaseObject* self)
{
    self->desc->m07(self);
    self->desc->m0E(self, 2, self);
}

void UnregisterObject(BaseObject* self)
{
    (void)self;
}

void ResolveAndStartObject(BaseObject* self)
{
    if (IsObjectAttached(self)) {
        void (*f)(BaseObject*) = self->desc->m0F;
        if (f) {
            f(self);
        }
        self->desc->m10(self);
        self->desc->m03(self);
    }
}

s32 IsObjectDescendantOf(BaseObject* node, BaseObject* target)
{
    if (node == 0) {
        return 0;
    }
    while (node != 0) {
        if (node == target) {
            return 1;
        }
        node = node->parent;
    }
    return target == 0;
}

void ReparentObject(BaseObject* self, BaseObject* parent)
{
    self->desc->m03(self);
    self->parent = parent;
    self->desc->m02(self);
}

s32 IsObjectAttached(BaseObject* self)
{
    BaseObject* node = self;
    while (node != 0) {
        BaseObject* next = node->parent;
        void* sub;
        if (next != 0) {
            sub = &((PlacedObject*)next)->children;
        } else {
            sub = node->world;
            sub = (u8*)sub + 0x48;
        }
        if (IsInList((List01*)sub, node) == 0) {
            return 0;
        }
        node = next;
    }
    return 1;
}

void GetObjectAttached(BaseObject* a0, s32* out)
{
    *out = IsObjectAttached(a0);
}

LINKER_REMNANT(func_00183050);

void* CreateObjectCopy(BaseObject* self, World* world, BaseObject* parent)
{
    BaseObject* r = (BaseObject*)CreateTypedRecord(self->desc->id, world, parent, self->id, -1);
    r->desc->m08(r, self);
    return r;
}

void CloneObject(BaseObject* self, BaseObject* src)
{
    self->desc->m09(self, src);
}

void CopyObjectData(BaseObject* self, BaseObject* src)
{
    if (src->keyedList != 0) {
        R11B008List* p = NewKeyedList();
        CopyKeyedList((R11B008List*)src->keyedList, p);
        self->keyedList = p;
        AddMarkRootList((MarkStacks*)g_markStacks, p);
    }
    const Desc01* d = src->desc;
    World* s0 = self->world;
    CopyMemory((u8*)self + sizeof(BaseObject), (u8*)src + sizeof(BaseObject), d->size - sizeof(BaseObject));
    u8* t = GetHashedSlot((u8*)s0, self->id);
    RemoveFromList((List01*)t, self);
    t = GetHashedSlot((u8*)s0, src->id);
    AppendToList((List01*)t, self);
    self->id = src->id;
    if (src->scriptScope != 0) {
        u8* s1 = g_markStacks;
        MarkPoolLiveEnds((MarkStacks*)s1);
        ScriptScope* p = NewScriptScope();
        CopyScriptScope((ScriptScope*)src->scriptScope, p);
        self->scriptScope = p;
        AddUniqueMarkRoot((MarkStacks*)s1, (MarkEntry*)p);
    }
    self->alias = src->alias;
}

void AddCallbackNode(World* world, Callback01** head, void* fn, void* ctx)
{
    Callback01* n = (Callback01*)TakeCallRecord(world);
    n->fn = (void (*)(void*, s32, void*))fn;
    n->ctx = ctx;
    n->next = *head;
    *head = n;
}

void RemoveCallbackNode(World* mgr, Callback01** link, void* fn, void* ctx)
{
    Callback01* node;
    goto test;
advance:
    link = &(*link)->next;
test:
    node = *link;
    if (node == 0) {
        return;
    }
    if ((void*)node->fn != fn || node->ctx != ctx) {
        goto advance;
    }
    *link = node->next;
    node->next = 0;
    ReleaseCallRecords(mgr, (T219CHook*)node);
}

void AddObjectCallback(BaseObject* self, void* fn, void* ctx)
{
    AddCallbackNode(self->world, &self->callbacks, fn, ctx);
}

void RemoveObjectCallback(BaseObject* self, void* fn, void* ctx)
{
    RemoveCallbackNode(self->world, &self->callbacks, fn, ctx);
}

void AddObjectListener(BaseObject* self, BaseObject* src)
{
    AddCallbackNode(self->world, &self->callbacks, (void*)src->desc->m0D, src);
}

void RemoveObjectListener(BaseObject* self, BaseObject* src)
{
    RemoveCallbackNode(self->world, &self->callbacks, (void*)src->desc->m0D, src);
}

void SendObjectNotification(BaseObject* self, s32 kind, void* arg)
{
    if (self->desc->m0D != 0) {
        self->desc->m0D(self, kind, arg);
    }
    Callback01* n = self->callbacks;
    while (n) { void* c = n->ctx; void (*f)(void*, s32, void*) = n->fn; n = n->next; f(c, kind, arg); }
}

void LoadObjectProperties(BaseObject* self, void* stream)
{
    ReadPropertyRecords(self, stream);
}

s32 MatchesObjectId(BaseObject* self, s32 id)
{
    Alias01* link;

    if (id == -1) {
        return 0;
    }
    if (self->id == id) {
        goto found;
    }
    link = self->alias;
    if (link == 0) {
        goto missing;
    }
    if (link->id != id) {
        goto missing;
    }
found:
    return 1;
missing:
    return 0;
}

s32 GetAliasId(BaseObject* self)
{
    Alias01* link = self->alias;
    if (link != 0) {
        return link->id;
    }
    return -1;
}

s32 GetEffectiveObjectId(BaseObject* a)
{
    if (a->alias) return a->alias->id;
    return a->id;
}

void GetObjectAliasId(BaseObject* self, s32* out)
{
    *out = GetAliasId(self);
}

void RunScriptEventHandler(BaseObject* self, s32 key, R11B008Node* list)
{
    ScriptValue q0;
    ScriptValue q1;
    ScriptValue q2;
    ScriptValue q3;
    InitScriptValue(&q0);
    InitScriptValue(&q1);
    InitScriptValue(&q2);
    MarkPoolLiveEnds((MarkStacks*)g_markStacks);
    if (LookupScriptVariable((ScriptScope*)self->scriptScope, key, 1, &q0) == 0) {
        DestroyScriptValue(&q2, 2);
        DestroyScriptValue(&q1, 2);
        DestroyScriptValue(&q0, 2);
        return;
    }
    ScriptMethod* rec = (ScriptMethod*)q0.p;
    ScriptScope* slot = NewScriptScope();
    SetScriptScopeParent(slot, rec->scope);
    SetScriptValuePointerB(&q1, self);
    DefineScriptVariable(&q3, slot, rec->params->selfName, &q1);
    AssignScriptValue(&q2, &q3);
    DestroyScriptValue(&q3, 2);
    if (list != 0) {
        R11B008Node* it = list;
        ScriptParam* l = rec->params->head;
        do {
            DefineScriptVariable(&q3, slot, l->name, it);
            AssignScriptValue(&q2, &q3);
            DestroyScriptValue(&q3, 2);
            it = it->next;
            l = l->next;
        } while (it != 0);
    }
    EvalScriptBody(&q3, (R11B008Node*)rec->body, slot);
    AssignScriptValue(&q2, &q3);
    DestroyScriptValue(&q3, 2);
    DestroyScriptValue(&q2, 2);
    DestroyScriptValue(&q1, 2);
    DestroyScriptValue(&q0, 2);
}

// The record a queued script handler carries at +0x0C: the value its event was raised with.
struct ScriptEventArg { s32 pad0; s32 value; };

// Whether TriggerScriptEvent should drop an event: a timer still running (1), a handler for the
// same event already queued (6 and 7 only with the same value), or, for 4 and 5, the opposite
// event's queued handler, which is taken out of the world's list and released.
s32 SuppressScriptEvent(BaseObject* self, s32 key, s32 flag, void* out)
{
    s32** p = (s32**)out;
    s32 tag = -1;
    switch (key) {
    case 1: {
        f32 f = *(f32*)((u8*)self + 0x29C);
        if (f <= 0.0f) return 0;
        f32 g = f - *(f32*)p[0];
        s32 r = 1;
        *(f32*)((u8*)self + 0x29C) = g;
        if (!(0.0f < g)) r = 0;
        return r;
    }
    case 4:
        tag = 5;
        break;
    case 5:
        tag = 4;
        break;
    case 6:
    case 7:
        break;
    case 0:
    case 29:
    default:
        return 0;
    }
    QueuedCall* prev = 0;
    for (QueuedCall* n = self->world->queuedCallHead; n != 0; n = n->next) {
        if ((void*)n->fn == (void*)RunScriptEventHandler && (BaseObject*)n->arg == self) {
            if (n->k2 == key) {
                if (key >= 8) return 1;
                else if (key >= 6) { s32* q = p[0]; return ((ScriptEventArg*)n->p0C)->value == *q; }
                else return 1;
                // Not reached. Retail's code keeps the loop notes of the compiled-out macro
                // (docs/toolchain/cse.md, "A reload after an if whose body returns").
                ASSERT(0);
            }
            if (n->k2 == tag) {
                if (prev != 0) {
                    prev->next = n->next;
                    if (n->next == 0) self->world->queuedCallTail = prev;
                } else if (n->next != 0) {
                    self->world->queuedCallHead = n->next;
                } else {
                    World* c = self->world;
                    c->queuedCallTail = 0;
                    c->queuedCallHead = 0;
                }
                n->next = 0;
                ReleaseCallRecords(self->world, (T219CHook*)n);
                return 1;
            }
        }
        prev = n;
    }
    return 0;
}

void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out)
{
    ScriptValue r;
    ScriptValue tmp;
    s32 a4;

    InitScriptValue(&r);
    if (self->scriptScope == 0 || LookupScriptVariable((ScriptScope*)self->scriptScope, idx, 1, &r) == 0) {
        DestroyScriptValue(&r, 2);
        goto done;
    }
    MarkPoolLiveEnds((MarkStacks*)g_markStacks);
    if (SuppressScriptEvent(self, idx, flag, out) == 0) {
        if (flag != 0) {
            BuildScriptListFromPairs(&tmp, flag, (s32*)D_00244DFC + D_00244EC0[idx], (s32*)out);
            AssignScriptValue(&r, &tmp);
            DestroyScriptValue(&tmp, 2);
            a4 = (s32)r.p;
        } else {
            a4 = 0;
        }
        AppendQueuedCall(self->world, (void*)(void (*)(void*, s32, void*))RunScriptEventHandler, self, idx, a4);
    }
    DestroyScriptValue(&r, 2);
done:
    ;
}

void SetExtraObjectPropertyBool(BaseObject* a0, s32 a1, s32 a2)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueBool(&a, a2);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void SetExtraObjectPropertyInt(BaseObject* a0, s32 a1, s32 n)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueInt(&a, n);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void SetExtraObjectPropertyFloat(BaseObject* a0, s32 a1, f32 x)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueFloat(&a, x);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void SetExtraObjectPropertyVectorB(BaseObject* a0, s32 a1, void* a2)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    f32* p = (f32*)AcquireVectorBPayload();
    *(Quad16*)p = *(Quad16*)a2;
    SetScriptValueVectorB(&a, p);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void SetExtraObjectPropertyPair(BaseObject* a0, s32 a1, void* a2)
{
    ScriptValue a;
    ScriptValue b;
    void* p;
    InitScriptValue(&a);
    p = AcquirePairPayload();
    *(Pack_183B20*)p = *(Pack_183B20*)a2;
    SetScriptValuePair(&a, (f32*)p);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void SetExtraObjectPropertyWord(BaseObject* a0, s32 a1, s32 n)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueInt(&a, n);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void SetExtraObjectPropertyVectorA(BaseObject* a0, s32 a1, void* a2)
{
    ScriptValue a;
    ScriptValue b;
    f32* p;
    InitScriptValue(&a);
    p = (f32*)AcquireVectorAPayload();
    *(Quad16*)p = *(Quad16*)a2;
    SetScriptValueVectorA(&a, p);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void InitConeVolume(ConeVolume* self)
{
    self->flags = (self->flags & ~(0x3ULL << 40)) | ((u64)0x8000 << 25);
    self->mode = 0;
    self->q320 = *(const Quad16*)&g_unitZVector;
    self->q340 = *(const Quad16*)&g_unitYVector;
    self->rangeMin = 200.0f;
    self->rangeMax = 2000.0f;
    self->secondAngle = 240.0f;
    self->firstAngle = 180.0f;
    self->thirdAngle = 180.0f;
    self->outerAngle = 60.0f;
    UpdateConeVolumeTangents(self);
    InitPlacedObject(self);
}

void RefreshConeVolume(ConeVolume* self)
{
    ComputePlacedObjectWorldFrame(self);
    RefreshConeVolumeShape(self);
    UpdateConeVolumeBounds(self);
}

void RemoveConeVolumeFromWorldList(ConeVolume* self)
{
    RemoveFromList((List01*)((u8*)self->world + 0x1BE8), self);
    NoteConeVolumeLightingChange(self);
}

void AddConeVolumeToWorldList(ConeVolume* self)
{
    void (*fn)(BaseObject*);

    AppendToList((List01*)((u8*)self->world + 0x1BE8), self);
    fn = self->desc->m12;
    if (fn != 0) fn(self);
}

void RegisterConeVolume(ConeVolume* self)
{
    RegisterPlacedObject(self);
    AddConeVolumeToWorldList(self);
}

void UnregisterConeVolume(ConeVolume* self)
{
    UnregisterPlacedObject(self);
    RemoveConeVolumeFromWorldList(self);
}

void CopyConeVolume(ConeVolume* self, ConeVolume* other)
{
    s32 changed = 0;
    if (IsObjectAttached(self)) {
        changed = self->value != other->value;
    }
    if (changed) {
        RemoveConeVolumeFromWorldList(self);
    }
    ConeVolumeSaved keep = self->saved;
    CopyPlacedObject(self, other);
    self->saved = keep;
    if (changed) {
        AddConeVolumeToWorldList(self);
    }
}

void FitLineThroughPoints(f32 a, f32 b, f32 c, f32 d, f32* out0, f32* out1)
{
    if (AreFloatsNearlyEqual(a, c, 1e-4f)) {
        *(s32*)out1 = 0;
        *out0 = b;
    } else {
        f32 t = (d - b) / (c - a);
        *out1 = t;
        *out0 = b - t * a;
    }
}

void FitReciprocalThroughPoints(f32* out, f32* scale, f32 x, f32 y, f32 z, f32 w)
{
    const f32 eps = 0.0001f;
    if (AreFloatsNearlyEqual(x, z, eps) || __builtin_fabsf(x) < eps || __builtin_fabsf(z) < eps) {
        *scale = 0.0f;
        *out = y;
        return;
    }
    f32 t = (x * z) * (w - y) / (x - z);
    *scale = t;
    *out = y - t / x;
}

void FitUnitRampBetweenPair(LinePoints* self, f32* out0, f32* out1)
{
    FitLineThroughPoints(self->x, 1.0f, self->y, 0.0f, out0, out1);
}

void FitLineThroughAngleSamples(f32 a, f32 b, f32 c, f32 d, f32* out0, f32* out1)
{
    f32 x = Cosine(a * 0.0087266471f);
    x = x + x * x * x;
    f32 y = Cosine(c * 0.0087266471f);
    y = y + y * y * y;
    FitLineThroughPoints(x, b * 0.003921569f, y, d * 0.003921569f, out0, out1);
}

void NoteConeVolumeLightingChange(ConeVolume* self)
{
    if (self->value == 0) {
        g_lightingChangeFrame = g_frameCount;
    }
}

void *InitPacketWriter(PacketWriter* p);
void UsePacketBufferMemory(PacketWriter* p, s32 n, void* q);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
void WriteVifMscal(PacketWriter* p, void* code);
void WriteVifFlushE(PacketWriter* p);
void DetachPacketBuffer(PacketWriter* p, u32* outCount, u8** outBegin);
void ConvertHsv255ToRgb255(Quad_001B4580* src, f32* dst);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void BuildBasisFromXAndZHint(const Vec02* x, const Vec02* hint, Mat02* out);
void BuildFrustumSideNormals(Mat02* m, Vec02* out, f32 x, f32 y);
void BuildProjectionMatrix(Mat4* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out);
extern u8 D_00000BF0[];
extern u8 D_00000D30[];
extern u8 D_00000EF0[];

void RefreshConeVolumeShape(ConeVolume* self)
{
    PacketWriter w;
    InitPacketWriter(&w);
    NoteConeVolumeLightingChange(self);
    if (0.0001f < self->firstAngle && 0.0001f < self->hsv.z) {
        self->shape = 2;
    } else if (0.0001f < self->secondAngle && 0.0001f < self->secondLevel) {
        self->shape = 1;
    } else {
        self->shape = 0;
    }
    UsePacketBufferMemory(&w, 0x20, self->packet);
    Vec02 c;
    if (0.0001f < self->hsv.z) {
        ConvertHsv255ToRgb255((Quad_001B4580*)&self->hsv, (f32*)&c);
        Vu0::Q(c) = Vu0::MulX(Vu0::Q(c), Vu0::Scalar(1.0f / self->hsv.z));
    } else {
        Vu0::Q(c) = Vu0::Zero();
    }
    CopyWordsToWriter(&w, 0xC, 1, (u32*)&c, 0x16);
    f32 fit[2][4];
    FitLineThroughAngleSamples(self->firstAngle, 0.0f, 0.0f, self->hsv.z, &fit[1][2], &fit[0][2]);
    FitLineThroughAngleSamples(self->secondAngle, 0.0f, 0.0f, self->secondLevel, &fit[1][1], &fit[0][1]);
    FitLineThroughAngleSamples(360.0f - self->thirdAngle, 0.0f, 360.0f, self->thirdLevel, &fit[1][0], &fit[0][0]);
    CopyWordsToWriter(&w, 0xC, 2, (u32*)fit, 0x17);
    switch (self->mode) {
    case 0: {
        Vec02 d;
        TransformDirectionBetweenFrames(self, 0, (Vec02*)&self->q320, &d);
        CopyWordsToWriter(&w, 8, 1, (u32*)&d, 0x19);
        WriteVifMscal(&w, D_00000BF0);
        break;
    }
    case 1: {
        f32 r[4];
        FitReciprocalThroughPoints(&r[0], &r[1], self->rangeMin, 1.0f, self->rangeMax, 0.0f);
        CopyWordsToWriter(&w, 4, 1, (u32*)r, 0x19);
        CopyWordsToWriter(&w, 8, 1, (u32*)&self->v140, 0x1A);
        WriteVifMscal(&w, D_00000D30);
        break;
    }
    case 2:
    case 3: {
        Vec02 d;
        Vec02 up;
        TransformDirectionBetweenFrames(self, 0, (Vec02*)&self->q320, &d);
        Vu0::Q(d) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(-1.0f));
        TransformDirectionBetweenFrames(self, 0, (Vec02*)&self->q340, &up);
        BuildBasisFromXAndZHint(&d, &up, &self->basis);
        BuildFrustumSideNormals(&self->basis, self->planes, self->tangentX, self->tangentY);
        Vec02& far = self->planes[4];
        Vec02& near = self->planes[5];
        for (s32 i = 0; i < 4; i++) {
            self->planes[i].w = -Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(self->v140), Vu0::Vec::Of(self->planes[i])));
        }
        Vu0::Q(self->planes[4]) = Vu0::Q(self->basis.r[0]);
        far.w = -self->rangeMax - Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(self->v140), Vu0::Vec::Of(self->planes[4])));
        f32 proj[4][4];
        f32 view[4][4];
        f32 ramp[2][4];
        f32 one = 1.0f;
        f32 zero = 0.0f;
        u128 neg = Vu0::ScalarInGpr(-1.0f);
        Vu0::Q(self->planes[5]) = Vu0::MulX(Vu0::Q(self->basis.r[0]), neg);
        near.w = 50.0f - Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(self->v140), Vu0::Vec::Of(self->planes[5])));
        BuildProjectionMatrix((Mat4*)proj, one / self->tangentX, one / self->tangentY, zero, zero, 50.0f, self->rangeMax);
        BuildViewProjectionMatrix((f32*)&self->v140, (f32*)&self->basis, proj, (Quad16*)view);
        Vu0::Q(d) = Vu0::MulX(Vu0::Q(d), Vu0::ScalarInGpr(-1.0f));
        if (self->mode == 2) {
            FitUnitRampBetweenPair((LinePoints*)&self->innerRatioX, &ramp[0][0], &ramp[1][0]);
            FitUnitRampBetweenPair((LinePoints*)&self->innerRatioY, &ramp[0][1], &ramp[1][1]);
            ramp[0][2] = one;
            ramp[1][2] = zero;
        } else {
            ramp[0][0] = one;
            ramp[1][0] = zero;
            ramp[0][1] = one;
            ramp[1][1] = zero;
            FitUnitRampBetweenPair((LinePoints*)&self->innerRatioRoot, &ramp[0][2], &ramp[1][2]);
        }
        FitUnitRampBetweenPair((LinePoints*)&self->rangeMin, &ramp[0][3], &ramp[1][3]);
        CopyWordsToWriter(&w, 0xC, 2, (u32*)ramp, 0x19);
        CopyWordsToWriter(&w, 8, 1, (u32*)&d, 0x1B);
        CopyWordsToWriter(&w, 0xC, 4, (u32*)view, 0x1C);
        WriteVifMscal(&w, D_00000EF0);
        break;
    }
    }
    WriteVifFlushE(&w);
    DetachPacketBuffer(&w, &self->packetSize, 0);
}

void SetConeVolumeMode(ConeVolume* self, s32 flag)
{
    self->mode = flag;
    if (flag == 0) {
        self->flags = (self->flags & ~(u64)0x30000000000) | ((u64)0x8000 << 25);
    } else {
        self->flags = self->flags & ~(u64)0x30000000000;
    }
    RefreshConeVolumeShape(self);
    UpdateConeVolumeBounds(self);
}

void SetConeVolumeColor(ConeVolume* self, Quad16* src)
{
    *(Quad16*)self->color = *src;
    RefreshConeVolumeShape(self);
}

void SetConeVolumeSecondLevel(ConeVolume* self, f32 v)
{
    self->secondLevel = v;
    RefreshConeVolumeShape(self);
}

void SetConeVolumeThirdLevel(ConeVolume* self, f32 v)
{
    self->thirdLevel = v;
    RefreshConeVolumeShape(self);
}

void SetConeVolumeFirstAngle(ConeVolume* self, f32 v)
{
    self->firstAngle = v;
    RefreshConeVolumeShape(self);
}

void SetConeVolumeSecondAngle(ConeVolume* self, f32 v)
{
    self->secondAngle = v;
    RefreshConeVolumeShape(self);
}

void SetConeVolumeThirdAngle(ConeVolume* self, f32 v)
{
    self->thirdAngle = v;
    RefreshConeVolumeShape(self);
}

void SetConeVolumeDirection(ConeVolume* self, Quad16* dir)
{
    self->q310 = *dir;
    u128 v = Vu0::Q(*dir);
    f32 len = Vu0::ToFloat(Vu0::Length(v));
    if (0.0001f < len) {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(-1.0f / len);
        Vu0::Q(self->q320) = Vu0::MulX(v, Vu0::Q(k));
    } else {
        self->q320 = *(const Quad16*)&g_unitZVector;
    }
    RefreshConeVolumeShape(self);
    UpdateConeVolumeBounds(self);
}

void SetConeVolumeValue(ConeVolume* self, s32 v)
{
    if (v != self->value) {
        self->value = v;
        RefreshConeVolumeShape(self);
    }
}

void SetConeVolumeRange(ConeVolume* self, U64P* src)
{
    *(U64P*)&self->rangeMin = *src;
    RefreshConeVolumeShape(self);
    UpdateConeVolumeBounds(self);
}

void SetConeVolumeOuterAngle(ConeVolume* self, f32 v)
{
    self->outerAngle = v;
    UpdateConeVolumeTangents(self);
    RefreshConeVolumeShape(self);
    UpdateConeVolumeBounds(self);
}

void SetConeVolumeInnerAngle(ConeVolume* self, f32 v)
{
    self->innerAngle = v;
    UpdateConeVolumeTangents(self);
    RefreshConeVolumeShape(self);
}

void SetConeVolumeVector340(ConeVolume* self, Quad16* src)

{
    self->q340 = *src;
    RefreshConeVolumeShape(self);
    UpdateConeVolumeBounds(self);
}

void UpdateConeVolumeTangents(ConeVolume* self)
{
    f32 a = ClampHelper::Of(self->outerAngle, 0.0f, 175.0f);
    f32 b = ClampHelper::Of(self->innerAngle, 0.0f, a);
    f32 r = Tangent(a * 0.00872664712f);
    self->tangentY = r;
    self->tangentX = r;
    f32 q = Tangent(b * 0.00872664712f);
    self->innerRatioX = q / self->tangentX;
    self->innerRatioY = q / self->tangentY;
    self->f36C = self->f364 = 1.0f;
    self->innerRatioRoot = Fpu::Sqrt(self->innerRatioX);
    self->f35C = 1.0f;
}

struct ValueListObject;
struct Bits128;
void QueryValueListMask(ValueListObject* self, f32 radius, Bits128* vec, s32* out);

void UpdateConeVolumeBounds(ConeVolume* self)
{
    if (self->value == 0) {
        return;
    }
    switch (self->mode) {
    case 0:
        self->mask = 0x0FFFFFFF;
        break;
    case 1:
        QueryValueListMask((ValueListObject*)self->world->valueListObject, self->rangeMax, (Bits128*)&self->v140, &self->mask);
        break;
    case 2:
    case 3: {
        Vec02 apex;
        Vec02 rim;
        Vec02 v;
        Vec02 center;
        Vu0::Q(apex) = Vu0::FromFloats(0.0f, 0.0f, self->rangeMax * 0.5f);
        f32 t = Tangent(self->outerAngle * 0.00872664712f);
        Vu0::Q(rim) = Vu0::FromFloats(t * self->rangeMax, 0.0f, self->rangeMax);
        Vu0::Q(v) = Vu0::Sub(Vu0::Q(rim), Vu0::Q(apex));
        f32 r = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(v)));
        Vu0::Q(v) = Vu0::MulX(Vu0::Q(self->axis), Vu0::Scalar(self->rangeMax * 0.5f));
        Vu0::Q(center) = Vu0::Add(Vu0::Q(self->v140), Vu0::Q(v));
        QueryValueListMask((ValueListObject*)self->world->valueListObject, r, (Bits128*)&center, &self->mask);
        break;
    }
    }
}

void SetConeVolumeOuterLevels(ConeVolume* self, f32 v)
{
    SetConeVolumeSecondLevel(self, v);
    SetConeVolumeThirdLevel(self, v);
}

void GetConeVolumeSecondLevel(ConeVolume* self, f32* out)
{
    *out = self->secondLevel;
}

void SetConeVolumeColorRgb(ConeVolume* self, void* a1)
{
    Quad16 q;
    ConvertRgb255ToHsv255((Quad_001B4580*)a1, (f32*)&q);
    SetConeVolumeColor(self, &q);
}

void GetConeVolumeColorRgb(u8* self, f32* out)
{
    ConvertHsv255ToRgb255((Quad_001B4580*)(self + 736), out);
}
