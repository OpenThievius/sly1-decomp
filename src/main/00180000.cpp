// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "screen_element.h"
#include "switched_collider.h"
#include "c6e.h"
#include "cone_volume.h"
#include "world.h"
#include "masked_collider.h"
#include "object_link.h"
#include "message_body.h"
#include "shapes.h"
#include "game_progress.h"
#include "globals.h"
#include "script_value.h"

void func_001C2320(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* func_001C1E48(ScriptValue* self, s32 n, s32* keys, s32* vals);

int func_001EAC68(f32 a, f32 b, f32 eps);

void func_00183F40(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d)
{
    if (func_001EAC68(a, c, 1e-4f)) {
        *(s32*)out1 = 0;
        *out0 = b;
    } else {
        f32 t = (d - b) / (c - a);
        *out1 = t;
        *out0 = b - t * a;
    }
}

void func_001830D8(void* self);

void func_00192C58(void* self);
void func_00181DA8(C1A* self, s32 n);

void func_00182D00(BaseObject* self)
{
    self->desc->m06(self);
    self->desc->m0E(self, 1, self);
}

void func_00182E88(BaseObject* self)
{
    self->desc->m07(self);
    self->desc->m0E(self, 2, self);
}

struct Node_1831E8 { void* f0; s32 f4; u8 pad0[8]; void* f10; };
void* func_001DBBD8(void);

void func_001831E8(void* a0, void** head, void* item, s32 count)
{
    Node_1831E8* n = (Node_1831E8*)TakeCallRecord();
    n->f0 = item;
    n->f4 = count;
    n->f10 = *head;
    *head = n;
}

s32 func_00183458(BaseObject* a)
{
    if (a->alias) return a->alias->id;
    return a->id;
}

void func_00152600(void* a, void* b);
void func_001841B0(void* a);

void func_00183DC0(ConeVolume* self)
{
    RemoveFromList((u8*)self->world + 0x1BE8, self);
    func_001841B0(self);
}

s32 func_001EAC68(f32 a, f32 b, f32 c);

void func_00183FE0(f32* out, s32* flag, f32 x, f32 y, f32 z, f32 w)
{
    const f32 eps = 0.0001f;
    if (func_001EAC68(x, z, eps) || __builtin_fabsf(x) < eps || __builtin_fabsf(z) < eps) {
        *flag = 0;
        *out = y;
        return;
    }
    f32 t = (x * z) * (w - y) / (x - z);
    *(f32*)flag = t;
    *out = y - t / x;
}

void func_00128018(void* a0, s32 zero, void* table, void* out);
void func_001BC260(f32 t, void* obj, void* a, void* b);
f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);
void func_001C5D58(void* obj);
void func_00175170(void* obj, s32 a, s32 b);

extern f32 D_00264180[];

struct Vec_181B20 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct Obj_181B20 {
    void** vtbl;
    u8 pad0[0x638 - 4];
    f32 x638;
};

void func_001BC4D8(void* self, void* sub);

void func_0013CE40(void* self);
void func_00124DF8(void* self, s32 a, void* table);
s32 func_001B6290(void* a0, void* self, s32 b, s32 c);
s32 func_00121160(s32 a);
void* func_0018D500(s32 size);

void func_00182C18(BaseObject* self)
{
    self->desc->m01(self);
    self->desc->m02(self);
}

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00182C58(BaseObject* self)
{
    TriggerScriptEvent(self, 0, 0, 0);
}

void func_00182F78(BaseObject* self, BaseObject* parent)
{
    self->desc->m03(self);
    self->parent = parent;
    self->desc->m02(self);
}

s32 func_00182FC8(void* p);

void func_00183028(void* a0, s32* out)
{
    *out = IsObjectAttached(a0);
}

void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);

typedef void (*VFn_183058)(void* self, void* arg);
struct Obj_183058 { void* vtbl; };

void* func_00183058(BaseObject* self, void* a1, s32 a2)
{
    Obj_183058* r = (Obj_183058*)CreateTypedRecord(self->desc->id, a1, a2, self->id, -1);
    ((VFn_183058*)r->vtbl)[12](r, self);
    return r;
}

void func_001243E0(void* self);
void func_00183DC0(void* self);

void func_00183E70(ConeVolume* self)
{
    UnregisterPlacedObject(self);
    RemoveConeVolumeFromWorldList(self);
}

s32 func_001EB050(void* target, f32 scale);
void func_00182DD8(void* self);

void func_00182E40(void* self, void* target)
{
    if (IsInsideRange(target, g_currentEntry->dt)) {
        AddObjectKeyToOwner(self);
    }
}

void func_00182ED0(BaseObject* self)
{
    (void)self;
}

s32 func_00182FC8(void* self);

void func_00182ED8(BaseObject* self)
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

s32 func_00182F40(BaseObject* node, BaseObject* target)
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

struct __attribute__((packed)) Pack_183B20 { u64 v; };

void* func_0011C858(void);

void func_00183B20(BaseObject* a0, s32 a1, void* a2)
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


void func_00183BB8(BaseObject* a0, s32 a1, s32 n)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueInt(&a, n);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}


void* func_0011C508(void);

void func_00183C38(BaseObject* a0, s32 a1, void* a2)
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

void func_00125138(void* self);
void func_001841D0(void* self);
void func_00184B58(void* self);

void func_00183D88(ConeVolume* self)
{
    ComputePlacedObjectWorldFrame(self);
    func_001841D0(self);
    func_00184B58(self);
}

void func_001830B0(BaseObject* self, BaseObject* src)
{
    self->desc->m09(self, src);
}

extern u8 D_00259F38[];

void func_0011A708(u8* a, void* b);
void func_0018D800(void* dst, void* src, s32 size);
u8* func_00159F20(World* world, s32 n);
void func_00152600(u8* p, void* self);
void func_00152470(u8* p, void* self);
void* func_0011A630(void);
void func_0011A800(u8* a);
void func_0011A5B0(void* a, void* b);
void func_0011A6C0(u8* a, void* b);

void func_001830D8(BaseObject* self, BaseObject* src)
{
    if (src->f04 != 0) {
        R11B008List* p = NewKeyedList();
        CopyKeyedList((R11B008List*)src->f04, p);
        self->f04 = p;
        AddMarkRootList(D_00259F38, p);
    }
    const Desc01* d = src->desc;
    World* s0 = self->world;
    CopyMemory((u8*)self + sizeof(BaseObject), (u8*)src + sizeof(BaseObject), d->size - sizeof(BaseObject));
    u8* t = GetHashedSlot(s0, self->id);
    RemoveFromList(t, self);
    t = GetHashedSlot(s0, src->id);
    AppendToList(t, self);
    self->id = src->id;
    if (src->f2C != 0) {
        u8* s1 = D_00259F38;
        MarkPoolLiveEnds(s1);
        void* p = NewScriptScope();
        CopyScriptScope(src->f2C, p);
        self->f2C = p;
        AddUniqueMarkRoot(s1, p);
    }
    self->alias = src->alias;
}

void func_00152470(void* sub, void* self);

void func_00183DF8(ConeVolume* self)
{
    void (*fn)(BaseObject*);

    AppendToList((u8*)self->world + 0x1BE8, self);
    fn = self->desc->m12;
    if (fn != 0) fn(self);
}

void func_001240F8(void* self);
void func_00183DF8(ConeVolume* self);

void func_00183E40(ConeVolume* self)
{
    RegisterPlacedObject(self);
    AddConeVolumeToWorldList(self);
}

void func_00182D48(void* self);
void func_00152470(u8* table, void* self);

void func_00182D48(BaseObject* self)
{
    (void)self;
}

s32 func_001526D0(List01* list, BaseObject* item);
s32 func_00182FC8(BaseObject* self);
void func_00152600(List01* list, BaseObject* item);

void func_00182D50(BaseObject* self)
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

s32 func_001833F0(BaseObject* self, s32 id)
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

s32 func_00183438(BaseObject* self)
{
    Alias01* link = self->alias;
    if (link != 0) {
        return link->id;
    }
    return -1;
}

void func_00182ED0(void* self);
void func_00152600(u8* table, void* self);

void func_001D73A8(void* self);

void* func_0018D500(s32 size);

void func_00182DD8(PlacedObject* self)
{
    PlacedObject* target;
    if (self->desc->flags & 1) {
        target = self;
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

struct Node_183238 {
    s32 key1;
    s32 key2;
    u8 pad8[8];
    Node_183238* next;
};

void func_001DBC18(void* a, void* b);

void func_00183238(void* mgr, Node_183238** link, s32 key1, s32 key2)
{
    Node_183238* node;
    goto test;
advance:
    link = &(*link)->next;
test:
    node = *link;
    if (node == 0) {
        return;
    }
    if (node->key1 != key1 || node->key2 != key2) {
        goto advance;
    }
    *link = node->next;
    node->next = 0;
    ReleaseCallRecords(mgr, node);
}

s32 func_00183438(void* self);

void func_00183478(void* self, s32* out)
{
    *out = GetAliasId(self);
}


void func_00183910(BaseObject* a0, s32 a1, s32 a2)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueBool(&a, a2);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}

void func_001DAE48(void);

struct __attribute__((aligned(16))) Quad_181A58 { s32 q[4]; };
struct Inner_181A58 { u8 pad000[0x140]; Quad_181A58 q140; };

struct Sub_181D28 { u8 pad0[0x24]; s32 f24; };

void func_001DAF08(void* self, s32 code, MessageBody* rec);

void func_0013DDB8(void* self);

void func_00152470(List01* list, BaseObject* item);

void func_00182C80(BaseObject* self)
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

s32 func_001526D0(void* sub, BaseObject* self);

s32 func_00182FC8(BaseObject* self)
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
        if (IsInList(sub, node) == 0) {
            return 0;
        }
        node = next;
    }
    return 1;
}

// The callback list's helpers (func_001831E8 adds, func_00183238 removes), as the slots call them.
void func_001831E8(World* world, Callback01** head, void* fn, s32 ctx);
void func_00183238(World* world, Callback01** head, s32 fn, s32 ctx);
void func_001831E8(World* world, Callback01** head, void (*fn)(BaseObject*, s32, void*), BaseObject* ctx);
void func_00183238(World* world, Callback01** head, void (*fn)(BaseObject*, s32, void*), BaseObject* ctx);

void func_00183290(BaseObject* self, void* fn, s32 ctx)
{
    AddCallbackNode(self->world, &self->callbacks, fn, ctx);
}

void func_001832C0(BaseObject* self, s32 fn, s32 ctx)
{
    RemoveCallbackNode(self->world, &self->callbacks, fn, ctx);
}

void func_001832F0(BaseObject* self, BaseObject* src)
{
    AddCallbackNode(self->world, &self->callbacks, src->desc->m0D, src);
}


void func_00183990(BaseObject* a0, s32 a1, s32 n)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueInt(&a, n);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}


void func_00183A10(BaseObject* a0, s32 a1, f32 x)
{
    ScriptValue a;
    ScriptValue b;
    InitScriptValue(&a);
    SetScriptValueFloat(&a, x);
    SetExtraObjectProperty(&b, a0, a1, &a);
    DestroyScriptValue(&b, 2);
    DestroyScriptValue(&a, 2);
}


void* func_0011C748(void);

void func_00183A90(BaseObject* a0, s32 a1, void* a2)
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

void func_00183320(BaseObject* self, BaseObject* src)
{
    RemoveCallbackNode(self->world, &self->callbacks, src->desc->m0D, src);
}

void func_0011EC40(void* a, void* b);

void func_001833D0(BaseObject* self, void* stream)
{
    ReadPropertyRecords(self, stream);
}

// NEAR: all calls and branches match; only the vtable load for the last call differs (retail loads the vtable into $v1 and the slot into $v0, ours the other way round)
typedef s32 (*VFnQ_181BC8)(void* self, s32 a);
typedef void (*VFnP_181BC8)(void* self, void* a);
typedef s32 (*VFnR_181BC8)(void* self, void* a);
typedef void (*VFnV_181BC8)(void* self);
typedef void (*VFnPPP_181BC8)(void* self, s32 a, void* b);
typedef void (*Fn_181BC8)(void);

s32 func_00160C58();
void func_00181DA8(C1A* self, s32 n);
void func_00192990(void* self, s32 value);
void func_00175170(void* self, s32 a, s32 b);
void func_001929D0(void* value);
void func_001D7098(void* out, s32 mode, void* owner);
void func_00181B20(void);

extern f32 D_0026185C;

struct Vt_181BC8 { void** vt; };
struct Loc_181BC8 { void* self; s32 val; s32 pad8; Fn_181BC8 fn; };

typedef s32 (*Fn_181448)(C1A*, void*, void*);
struct Vt_181448 { u8 pad0[0x12C]; Fn_181448 f12C; };
struct Slot_181448 { Collider* p; u8 pad[0x3C]; };
struct Node_181448 {
    C1A* owner;
    Slot_181448 s[2];
    u8 pad[0xD0 - 0x84];
    Node_181448* next;
};

extern f32 D_00261858[];
extern f32 D_00264154[];
extern f32 D_00275C60[];

void func_001D9C98(C1A* self, f32 dt);
void func_001D7098(void* out, s32 mode, Collider* c);
void func_001861E8(void* a, void* head);
void func_00129E10(void* o, f32 v);
void func_00129FB0(void* o, f32 v);

struct Link_1834A0 { s32 a; void* b; Link_1834A0* next; };
struct Mid_1834A0 { s32 pad0; void* kind; Link_1834A0* head; };
struct Rec_1834A0 { s32 key; Mid_1834A0* mid; s32 pad8; s32 padC; void* f10; };
struct Slot_1834A0 { s32 flag; s32 value; };
struct Item_1834A0 { s32 pad0; s32 pad4; Item_1834A0* next; };

void func_0011A800(void* d);
s32 func_0011A498(void* a, s32 b, s32 c, ScriptValue* d);
void func_0011A328(Slot_1834A0* slot, s32 value);
void* func_0011A358(ScriptValue* out, Slot_1834A0* owner, void* kind, void* body);
void* func_00119A58(ScriptValue* out, void* list, Slot_1834A0* c);
extern u8 D_00259F38[];

void func_001834A0(BaseObject* self, s32 key, Item_1834A0* list)
{
    ScriptValue q0;
    ScriptValue q1;
    ScriptValue q2;
    ScriptValue q3;
    InitScriptValue(&q0);
    InitScriptValue(&q1);
    InitScriptValue(&q2);
    MarkPoolLiveEnds(D_00259F38);
    if (LookupScriptVariable(self->f2C, key, 1, &q0) == 0) {
        DestroyScriptValue(&q2, 2);
        DestroyScriptValue(&q1, 2);
        DestroyScriptValue(&q0, 2);
        return;
    }
    Rec_1834A0* rec = (Rec_1834A0*)q0.p;
    Slot_1834A0* slot = (Slot_1834A0*)NewScriptScope();
    SetScriptScopeParent(slot, rec->key);
    SetScriptValuePointerB(&q1, self);
    DefineScriptVariable(&q3, slot, rec->mid->kind, &q1);
    AssignScriptValue(&q2, &q3);
    DestroyScriptValue(&q3, 2);
    if (list != 0) {
        Item_1834A0* it = list;
        Link_1834A0* l = rec->mid->head;
        do {
            DefineScriptVariable(&q3, slot, l->b, it);
            AssignScriptValue(&q2, &q3);
            DestroyScriptValue(&q3, 2);
            it = it->next;
            l = l->next;
        } while (it != 0);
    }
    EvalScriptBody(&q3, rec->f10, slot);
    AssignScriptValue(&q2, &q3);
    DestroyScriptValue(&q3, 2);
    DestroyScriptValue(&q2, 2);
    DestroyScriptValue(&q1, 2);
    DestroyScriptValue(&q0, 2);
}

s32 func_001DDA80(void* p);

typedef void (*VFn_180F98)(void* self);

struct Vt_180F98 {
    VFn_180F98* vtbl;
};

struct Packed_180F98 { f32 v; } __attribute__((packed));

void func_001D7440(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_00129D00(void* a, s32 b, void* c);
void func_00128018(void* a, void* b, void* c, void* d);
void func_00181DA8(C1A* self, s32 n);
s32 func_001B4688(s32 key);

void func_00183350(BaseObject* self, s32 kind, void* arg)
{
    if (self->desc->m0D != 0) {
        self->desc->m0D(self, kind, arg);
    }
    Callback01* n = self->callbacks;
    while (n) { void* c = n->ctx; void (*f)(void*, s32, void*) = n->fn; n = n->next; f(c, kind, arg); }
}

extern u8 D_00259F38[];
extern const s32 D_00244EC0[32] = { 0, 1, 3, 4, 5, 6, 7, 9, 11, 12, 14, 17, 19, 20, 22, 26, 29, 31, 33, 34, 36, 38, 39, 40, 41, 43, 44, 45, 47, 48, 50, 0 };
extern s32 D_00244DFC[];
void func_0011A800(u8* a);
s32 func_0011A498(void* a, s32 b, s32 c, ScriptValue* d);
s32 func_00183668(BaseObject* self, s32 idx, s32 flag, void* out);
void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_001834A0(BaseObject* self, s32 key, Item_1834A0* list);

void func_001837E0(BaseObject* self, s32 idx, s32 flag, s32* out)
{
    ScriptValue r;
    ScriptValue tmp;
    s32 a4;

    InitScriptValue(&r);
    if (self->f2C == 0 || LookupScriptVariable(self->f2C, idx, 1, &r) == 0) {
        DestroyScriptValue(&r, 2);
        goto done;
    }
    MarkPoolLiveEnds(D_00259F38);
    if (func_00183668(self, idx, flag, out) == 0) {
        if (flag != 0) {
            BuildScriptListFromPairs(&tmp, flag, (s32*)D_00244DFC + D_00244EC0[idx], out);
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


void func_00184A70(ConeVolume* self);
void func_00123ED0(ConeVolume* self);

void func_00183CC8(ConeVolume* self)
{
    self->flags = (self->flags & ~(0x3ULL << 40)) | ((u64)0x8000 << 25);
    self->mode = 0;
    self->q320 = *(const Quad16*)&g_unitZVector;
    self->q340 = *(const Quad16*)&g_unitYVector;
    self->rangeMin = 200.0f;
    self->rangeMax = 2000.0f;
    self->f2fc = 240.0f;
    self->f2f8 = 180.0f;
    self->f300 = 180.0f;
    self->outerAngle = 60.0f;
    UpdateConeVolumeTangents(self);
    InitPlacedObject(self);
}

// EXACT: switch (mode) for the call dispatch; flag tail as mode==0, mode<0, mode>=4, mode>=2 chain

extern f32 D_00261858[];
void func_001B64D8(void* p, s32 n);
void func_001B6628(void* p, s32 n);

s32 func_00182FC8(ConeVolume*);
void func_00183DC0(ConeVolume*);
void func_00127048(ConeVolume*, ConeVolume*);

void func_00183EA0(ConeVolume* self, ConeVolume* other)
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

struct Clamp_181818
{
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo)
        {
            return lo;
        }
        if (hi < x)
        {
            return hi;
        }
        return x;
    }
};

extern f32 D_00261858[];
extern f32 D_00275C60[];
extern Rgba4 D_002623E0[];

f32 func_00205210(f32 x);
void func_00126A48(C1A* o, u32 c);
void func_00125C90(C1A* o, void* a, void* b);

