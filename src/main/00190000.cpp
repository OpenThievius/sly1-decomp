// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "c6e.h"
#include "point_object.h"
#include "point_graph_object.h"
#include "world.h"
#include "step_sequence.h"
#include "screen_element.h"
#include "globals.h"
#include "pad_record.h"

void func_00192498(SwitchedCollider* self, s32* out)
{
    *out = ((s32 (*)(SwitchedCollider*, s32*))self->desc05()->m4D)(self, out);
}

s32 D_00269BCC = -1;
extern void* D_00269C98[16];

void* func_001925F0()
{
    s32 i = g_activeSwitchedCollider;
    if (i < 0) return 0;
    return g_switchedColliders[i];
}

extern s32 D_00269C90;
s32 func_00182FC8();
s32 func_00192688(SwitchedCollider* value);

void func_001926D0(SwitchedCollider* self)
{
    if (self->f550 == 0) return;
    if (self->parent != 0) return;
    if (!IsObjectAttached()) return;
    if (FindSwitchedColliderIndex(self) >= 0) return;
    s32 n = g_switchedColliderCount;
    if ((u32)n < 16) {
        g_switchedColliders[n] = self;
        g_switchedColliderCount = n + 1;
    } else if (self->id == 5 && g_player == 0) {
        g_switchedColliders[0] = self;
    }
}

s32 func_00192688(void* value);
void func_00192880(s32 index);
void func_001F5B08(void* dst, void* src, s32 size);

void func_00192780(void* value)
{
    s32 idx = FindSwitchedColliderIndex(value);
    if (idx < 0) return;
    if (idx == g_activeSwitchedCollider) ActivateSwitchedColliderIndex(-1);
    s32 n = g_switchedColliderCount;
    func_001F5B08(&g_switchedColliders[idx], &g_switchedColliders[idx + 1], (n - idx) * 4 - 4);
    if (idx < g_activeSwitchedCollider) g_activeSwitchedCollider = g_activeSwitchedCollider - 1;
    g_switchedColliderCount = g_switchedColliderCount - 1;
}

void func_001B7A98(void* self);
void func_001926D0(void* self);

void func_00192820(SwitchedCollider* self)
{
    RegisterCollider(self);
    AddToSwitchedColliderList(self);
}

void func_001B7B78(void* self);
void func_00192780(void* self);

void func_00192850(SwitchedCollider* self)
{
    UnregisterCollider(self);
    RemoveFromSwitchedColliderList(self);
}

void func_001926D0(SwitchedCollider* self);
void func_00192780(SwitchedCollider* self);

void func_00192990(SwitchedCollider* self, s32 value)
{
    if (self->f550 == value) return;
    self->f550 = value;
    if (value) AddToSwitchedColliderList(self);
    else RemoveFromSwitchedColliderList(self);
}

void func_001929D0(void* value)
{
    ActivateSwitchedColliderIndex(FindSwitchedColliderIndex(value));
}

extern u8 D_00604700[];
void* func_001925F0();

void* func_001929F8()
{
    void* r = GetActiveSwitchedCollider();
    if (r) return (u8*)r + 0x580;
    return D_00604700;
}

struct Pair_192A28 {
    s32 a;
    s32 b;
};

void func_00192A28(s32, s32, Pair_192A28* out)
{
    out->b = 1;
    out->a = 1;
}

struct Mid_190450 { u8 pad0[0x618]; void* p618; };

s32 func_001A8820(void* p, s32 v);
s32 func_001C9990(void* self, s32* arg);

s32 func_00190450(C0E* self, s32* arg)
{
    if (self->desc05()->m4B(self, arg[0])) {
        return 0;
    }
    self->fC34 = 0;
    self->fC30 = arg[0];
    if (arg[0] == 0 && arg[1] != 0) {
        if (func_001A8820(((Mid_190450*)self->fC2C)->p618, arg[1])) {
            self->fC34 = 1;
        }
    }
    return AcceptAgentRequest(self, arg);
}

void func_001906E8(C0E* self, s32 value)
{
    self->fC28 = (void*)value;
}

u32 func_001907E0(u32 x)
{
    return (x & 1) ? 0 : x;
}

s32 D_00269BA4 = 0;

void func_00191EB0(void)
{
    D_00269BA4 = 0;
}

void func_00182C58(void* self);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_00191FD8(C70* self)
{
    StartObject(self);
    if (self->id64 != -1) {
        self->found68 = FindFirstObjectById(self->world, 4, self->id64, self);
    }
}

s32 func_00128018(void* a0, s32 a1, void* a2, void* a3);

s32 func_00192128(PointObject* self, void* other)
{
    void* p = &self->pos;
    return func_00128018(other, 0, p, p);
}

struct Child_001900A0;
typedef void (*ChildFn)(void* self);

struct Child_001900A0 {
    ChildFn* vtbl;
};

void func_001C9008(void* self);

void func_001900A0(C0E* self)
{
    LeaveAgentState(self);
    s32 kind = self->f724;
    if (kind != 8) {
        if (kind == 0x10) {
            Child_001900A0* child = ((Child_001900A0*)self->fC2C);
            if (child != 0) {
                child->vtbl[0x54](child);
            }
        }
    } else {
        if (self->f600 == 1) {
            self->desc05()->m4F(self, 0);
        }
    }
}

extern s32 D_00262C64;

s32 func_001DDA80(void* p);
s32 func_001C9A48(void* self, s32 a);

s32 func_001903F0(C0E* self, s32 a1)
{
    if (g_buttonCodeFlags & 1) {
        return 1;
    }
    if (func_001DDA80(self->world) == 0) {
        return IsAgentRequestBlocked(self, a1);
    }
    return 1;
}

s32 func_00192490(void)
{
    return 0;
}

typedef void (*Init_001924C8)(void* self, void* table, s32 zero, f32 scale);

// A node made by func_0019EA78: a hook table, a float at 0x1C and a quad at 0xC0.
struct Node_001924C8 {
    Init_001924C8* vtbl;
    u8 pad0[0x1C - 4];
    f32 f1C;
    s32 f20;
    u8 pad1[0xC0 - 0x24];
    Vec02 q0C0;
    u8 pad2[0x134 - 0xD0];
    void* p134;
};

void* func_0019EA78(s32 kind, s32 zero);
void func_0019F8E8(void* node, void* owner);
f32 func_0012CCC0(void* obj, s32 id);

void func_001924C8(SwitchedCollider* self, s32 mode, PlacedObject* other)
{
    switch (mode) {
    case 0:
        if (self->f5F0 == 0)
            return;
        {
            Node_001924C8* n = (Node_001924C8*)CreateEffect(0x1A, 0);
            self->f5AC[0] = n;
            self->f5D0 = 1;
            if (n != 0) {
                Init_001924C8 init = n->vtbl[0];
                init(n, (u8*)other + 0x140, 0, 1.0f);
                func_0019F8E8(n, self);
                f32 r = func_0012CCC0(self->f5F0, 0x13F);
                n->f1C = r;
                n->f20 = self->f59C;
                n->q0C0 = other->world->gravity;
                n->p134 = other;
            }
        }
        self->desc05()->m4F(self, 1);
        break;
    case 1:
        self->desc05()->m4F(self, 2);
        break;
    }
}

typedef void (*Hook_00192880)(void* self, s32 mode, void* other);

// An entry with a hook table at 0 and a 64-bit flag word at 0x538.
struct Entry_00269C98 { Hook_00192880* vtbl; u8 pad[0x538 - 4]; u64 flags; };

void func_00192880(s32 index)
{
    if (index == g_activeSwitchedCollider)
        return;
    if (g_activeSwitchedCollider >= 0) {
        u64 mask = (u64)(s64)-8193;
        mask = (mask << 16) | 0xFFFF;
        mask = (mask << 16) | 0xFFFF;
        Entry_00269C98** slot = (Entry_00269C98**)&g_switchedColliders[g_activeSwitchedCollider];
        (*slot)->flags &= mask;
        Hook_00192880* vt = (*slot)->vtbl;
        Entry_00269C98* next = index >= 0 ? (Entry_00269C98*)g_switchedColliders[index] : 0;
        vt[0x130 / 4]((*slot), 0, next);
    }
    s32 old = g_activeSwitchedCollider;
    g_activeSwitchedCollider = index;
    if (index >= 0) {
        Entry_00269C98** slot = (Entry_00269C98**)&g_switchedColliders[index];
        (*slot)->flags |= 1ULL << 45;
        Hook_00192880* vt = (*slot)->vtbl;
        Entry_00269C98* prev = old >= 0 ? (Entry_00269C98*)g_switchedColliders[old] : 0;
        vt[0x130 / 4]((*slot), 1, prev);
    }
}

extern u8 D_00275BC0[];

void func_001E9498(void* a, void* b);

void func_00192A38(SwitchedCollider* self, u32 value)
{
    T217D_440* block = &g_typedTextCaptionBox;
    ((T217D_Word*)&block->child)->v = value;
    PushStackElement(g_elementStack, &g_typedTextCaptionBox);
}

extern s32 D_00262C68;
extern u8* D_0026F800;

// A record whose 16-bit flags sit at 0xAA.


s32 func_001493A0(void* p);
void func_001516C0(StepSequence* ctx, PadRecord* rec);
void func_00150790(void* p, s32 n);
void func_0016EC20(PadRecord* rec, s32 n);

void func_00192A70(void* self, PadRecord* rec)
{
    if (IsTopCameraController(&g_camera->ctl454) != 0)
        return;
    PadRecord* a1 = (D_00262C68 & 4) ? &g_padRecord : &g_blankPadRecord;
    StepSequence* ctx = D_0027051C;
    if (ctx != 0 && ctx->state2D4 == 3 && ctx->f32C == 0 && (a1->flags & 0xC) != 0
        && *(s32*)ctx->target304 != 0) {
        SkipRemainingSteps(ctx, a1);
    } else if ((rec->flags & 0xC) != 0 && D_0026F800 != 0) {
        SetStepSequenceState(D_0026F800, 1);
    }
    ClearPadPressedBits(rec, 0xC);
}

s32 func_00190658(void)
{
    return 0;
}

struct Item_190660 { u8 pad0[0x724]; s32 kind; };

s32 func_00182FC8(void* p);
s32 func_001300E8(void* a, s32 b);

s32 func_00190660(C0E* self, Item_190660* item)
{
    if (item != 0 && IsObjectAttached(item) != 0) {
        if (IsObjectOfKind(item, 8) == 0 || item->kind != 0xB) {
            s32 n = self->fC10;
            if ((u32)n < 4) {
                self->fC14[n] = item;
                self->fC10 = n + 1;
                return 1;
            }
        }
    }
    return 0;
}

void func_00182F78(void* self, s32 value);

void func_001920E0(PointObject* self, s32 value)
{
    void* sub = &self->pos;
    func_00128018(self->parent, value, sub, sub);
    ReparentObject(self, value);
}

void func_001384A0(void* other, void* sub);

void func_00192150(TextPointObject* self, void* other)
{
    LoadPointObject(self, other);
    ReadBufferedString(other, &self->text);
}

struct Obj_00192190 { u8 pad0[0x54]; f32 f54; f32 f58; };

void func_00192190(Obj_00192190* self)
{
    self->f54 = 0.5f;
    self->f58 = 0.5f;
}

void func_001B7968(void* self);
void func_00192990(SwitchedCollider* self, s32 value);

void func_001921A8(SwitchedCollider* self)
{
    InitCollider(self);
    self->f598 = self;
    self->f580 = 1;
    SetSwitchedColliderEnabled(self, 1);
}

void func_001906F0(C0E* self, s32 value)
{
    self->fC24 = (void*)value;
}

extern void func_001C8F20(C0E* self, s32 mode, s32 value);

void func_001906F8(C0E* self, s32 flag, PlacedObject* extra)
{
    func_001924C8(self, flag, extra);
    if (flag == 0) {
        ChangeAgentState(self, 8, (s32)self->f5F0);
    }
}

struct Req_190770 { s32 f_0; u8 pad4[4]; s32 f_8; };

extern void func_001C9DE0(C0E* self, s32 code, Req_190770* req);
extern void func_00160DA0(void);

void func_00190770(C0E* self, s32 code, Req_190770* req)
{
    HandleAgentNotification(self, code, req);
    if (code == 0x13) {
        if (req->f_0 == (s32)self->f7E0) {
            if (req->f_8 == 0x53A) {
                func_00160DA0();
            }
        }
    }
}

void func_001BA130(SwitchedCollider* self);
void func_00192990(SwitchedCollider* self, s32 mode);

void func_001921E8(SwitchedCollider* self)
{
    CopyCollider(self);
    if (self->f550 != 0) {
        return;
    }
    self->f550 = 1;
    SetSwitchedColliderEnabled(self, 0);
}

void func_00145088(void* mgr, s32 a1, void* a2, SwitchedCollider* self, s32 a4);
void func_001451F0(void* mgr, s32 a1, s32 a2, s32 a3, SwitchedCollider* self, s32 a5);

void func_001922E8(SwitchedCollider* self, s32 mode)
{
    if (mode != 0) {
        self->v560 = self->v140;
        PushCameraController(g_camera, 1, &g_camera->ctl520, self, 0);
        return;
    }
    for (s32 i = 1; i < 7; i++) {
        RemoveCameraControllers(g_camera, 5, i, 0, self, 0);
    }
}

s32 func_00192410(void)
{
    return 1;
}

s32 func_001907F0(s32 value)
{
    if (value & 1) return value & -2;
    return 0;
}

s32 func_001909B0(f32 value)
{
    if (value > 1.0f) return 0;
    if (value < -1.0f) return 1;
    return 2;
}

void* func_001925F0(void);
void func_001929D0(void* value);

void func_00192418(void* self)
{
    if (self != GetActiveSwitchedCollider()) ActivateSwitchedCollider(self);
}

s32 func_00192488(SwitchedCollider* self)
{
    return 0;
}

struct Part_191A68 { u8 data[4]; };
struct Owner_191A68 { u8 head[0x34]; Part_191A68 part; };

void func_00191290(Part_191A68* part);

void func_00191A68(Owner_191A68* self)
{
    func_00191290(&self->part);
}

struct Part_191A88 { u8 data[4]; };
struct Owner_191A88 { u8 head[0x34]; Part_191A88 part; };

void func_00191570(Part_191A88* part);

void func_00191A88(Owner_191A88* self)
{
    func_00191570(&self->part);
}

void func_00137E70(void* a, void* b);
void func_0011EC40(void* a, void* b);

void func_00192068(PointObject* self, void* other)
{
    ReadBufferedVector3(other, &self->pos);
    ReadPropertyRecords(self, other);
}

s32 func_00128018(void* a, s32 b, void* c, s32 d);

void func_001920B0(BaseObject* self, s32 arg)
{
    func_00128018((void*)self->parent, 0, (u8*)self + 0x40, arg);
}


s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

extern u8 D_0026A210[];

void func_001AA268(void* self);
s32 func_0015C188(s32 k);
void* func_0015C1C0(s32 k);

struct Obj_191AA8 {
    u8 pad0[0x54];
    void* p54;
};

s32 func_001909F0(void* p);

void func_00191AA8(Obj_191AA8* self)
{
    func_001909F0(self->p54);
}

extern s32 D_00269BA4;

void func_001F6C20(s32 a);

void func_00191E70(s32 value)
{
    if (D_00269BA4 != value) {
        func_001F6C20(0);
        D_00269BA4 = value;
    }
}

void* func_001930B0(SwitchedCollider* p)
{
    return p;
}

s32 func_001930B8(s32 a, s32 b);

s32 func_001931F0(void)
{
    return func_001930B8(1, 0xFFFF);
}

struct S_190EA8 { u8 pad[4]; s32 value; };
s32 func_00190EA8(S_190EA8* p, s32 x) { return (x - p->value) >> 5; }

void func_001830D8(void* self);

void func_00192020(C70* self)
{
    Keep6E tmp;
    tmp = self->keep;
    CopyObjectData(self);
    self->keep = tmp;
}


void func_00152438(void* self, s32 value);

void func_00191EC0()
{
    func_00152438(&g_targetVectors, 0x38);
}

void func_00152440(void* p);

void func_00191EE8(void)
{
    ClearList(&g_targetVectors);
}

void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_00191F68(C70* self)
{
    RegisterObject(self);
    AppendToList(&g_targetVectors, self);
}

void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_00191FA0(C70* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetVectors, self);
}

extern s32 D_0026A068[];

// was NEAR: GCC folds the final return 1/return 0 into sltiu/xori; retail keeps li v0,16 + bne and a separate move v0,zero tail

s32 func_00190740(C0E* self)
{
    switch (self->f724) {
    case 0x10: return 1;
    case 0xB: return 2;
    }
    return 0;
}

s32 func_001DDA80(void* p);

s32 func_00192450(SwitchedCollider* self)
{
    if ((g_buttonCodeFlags & 1) || func_001DDA80(self->world)) return 1;
    return 0;
}

struct __attribute__((aligned(16))) Quad_192380 { s32 w[4]; };

extern f32 D_00269BC0[3];
void func_001B9F30(void);
// func_001EA4B8 takes its float arguments first: the caller then sets $f14 before $a0.
f32 func_001EA4B8(f32 a, f32 b, f32 c, Quad_192380* p, s32 zero);

void func_00192380(SwitchedCollider* self, u8* out, f32 a)
{
    CaptureColliderPose();
    if (self->f554 != 0) {
        *(Quad_192380*)(out + 0x10) = *(Quad_192380*)((u8*)self + 0x560);
        return;
    }
    Camera* base = g_camera;
    if (base->f224 == 0) {
        *(f32*)(out + 0x18) = ApproachValueWithRamp(self->v560.z, self->v140.z, a, (Quad_192380*)D_00269BC0, 0);
    }
    *(Quad_192380*)((u8*)self + 0x560) = *(Quad_192380*)(out + 0x10);
}

extern s32 D_00269C90;

s32 func_00192688(s32 key)
{
    s32 i;
    for (i = 0; i < g_switchedColliderCount; i++) {
        if (key == (s32)g_switchedColliders[i]) {
            return i;
        }
    }
    return -1;
}

struct Msg_1904E0 { s32 id; };

struct Args_1904E0 {
    C0E* self;
    s32 id;
};

s32 func_00160C58(void* a, void* b);
s32 func_001C96D8(void* a, void* b);

s32 func_001904E0(C0E* self, Msg_1904E0* msg)
{
    Args_1904E0 args;
    if (func_00160C58(self, msg) != 0 && self->fC34 == 0) {
        self->fA68 = 1;
    } else {
        self->fA68 = 0;
    }
    if (HandleAgentObjectEvent(self, msg) == 0) {
        return 0;
    }
    args.self = self;
    args.id = msg->id;
    self->desc->m0E(self, 0x17, &args);
    return 1;
}

extern s32 D_00262C64;
extern u8* D_002623C0;
struct Entry_269BD0 { s32 f0, f4, f8, fC; f32 f10, f14; s32 f18, f1C; f32 f20, f24; s32 f28, f2C, f30, f34, f38, f3C; };
extern Entry_269BD0 D_00269BD0;
extern u8 D_00269C10[];

struct Scratch_192C58 { u8 bytes[0x30]; };

void func_00189378(void* sub, s32 zero, void* out);
s32 func_0012C7B0(void* a, void* b, s32 c, s32 d, f32 fa, f32 fb);
void func_00157EF8(void* a, void* b, s32 c, void* d, void* e, s32 f, s32 g);

void func_00192C58(SwitchedCollider* self)
{
    s32 flags = g_buttonCodeFlags & 2;
    if (flags == 0) {
        u8* g = g_saveData;
        s32 n = *(s32*)(g + 0x19E4) - 1;
        *(s32*)(g + 0x19E4) = flags < n ? n : 0;
    }

    PlacedObject* s1 = self->f604;
    if (s1 != 0) {
        Scratch_192C58 tmp;
        s1->desc->m02(s1);
        s1->desc->m15(s1, 0);
        func_00189378(((u8*)self->f584) + 0x110, 0, &tmp);
        s1->desc02()->m1D(s1, (Vec02*)(((u8*)self->f584) + 0x140));
        s1->desc02()->m1E(s1, (Mat02*)&tmp);
        s1->desc02()->m20(s1, (Vec02*)&D_00248D30);
        s1->desc02()->m21(s1, (Vec02*)&D_00248D30);
        void* r = (void*)FindFirstObjectById(self->world, 1, 0x18C, s1);
        if (r != 0) {
            CreateAnimationPlayerWithoutPresetTargets(r, s1, 0, 0, 0.0f, 1.0f);
        }
    } else {
        s32 v = (s32)self->f588[1];
        if (v != 0) {
            u8* g = (u8*)&D_00269BD0;
            *(s32*)(g + 0x28) = v;
            SpawnEffectsAt(((u8*)self->f584) + 0x140, (void*)&g_unitZVector, 1, g, D_00269C10, 0, 0);
        }
    }
}

void func_001833D0(BaseObject* o, Stream8A* in);
s32 func_00137BE0(Stream8A* in);
void* func_0018D5C0(s32 n);
void func_00137E70(Stream8A* in, void* p);
s32 func_00137B90(Stream8A* in);
void* func_0018D500(s32 n);
f32 func_00137DF8(Stream8A* in);
s32 func_00137D10(Stream8A* in);
void func_001919F8(PointGraph* m);

void func_001916D0(PointGraphObject* o, Stream8A* in)
{
    PointGraph* m = &o->graph;
    s32 i;
    s32 j;
    LoadObjectProperties(o, in);
    i = 0;
    o->graph.pointCount = ReadBufferedU16(in);
    m->points = (GraphPoint*)AllocateZeroedFrontMemory(o->graph.pointCount << 5);
    m->nA = ReadBufferedU16(in);
    m->linkCount = ReadBufferedU16(in) + m->nA;
    m->links = (u8*)AllocateZeroedFrontMemory(m->linkCount * 12);
    m->triCount = ReadBufferedU16(in);
    m->tris = (u8*)AllocateZeroedFrontMemory(m->triCount * 12);
    if (o->graph.pointCount > 0) {
        do {
            GraphPoint* v = (GraphPoint*)((u8*)m->points + (i << 5));
            s32 k = i + 1;
            j = 0;
            ReadBufferedVector3(in, v);
            v->linkCount = ReadBufferedU8(in);
            v->links = (GraphLink**)AllocateFrontMemory((v->linkCount + 1) << 2);
            if (v->linkCount > 0) {
                do {
                    v->links[j] = (GraphLink*)(m->links + ReadBufferedU16(in) * 12);
                    j++;
                } while (j < v->linkCount);
            }
            i = k;
        } while (i < m->pointCount);
    }
    {
        s32 e;
        for (e = 0; e < m->linkCount; e++) {
            GraphPoint** p = (GraphPoint**)(m->links + e * 12);
            j = 1;
            do {
                j--;
                *p = (GraphPoint*)((u8*)m->points + (ReadBufferedU16(in) << 5));
                p++;
            } while (j >= 0);
        }
        for (e = 0; e < m->triCount; e++) {
            GraphPoint** p = (GraphPoint**)(m->tris + e * 12);
            j = 2;
            do {
                j--;
                *p = (GraphPoint*)((u8*)m->points + (ReadBufferedU16(in) << 5));
                p++;
            } while (j >= 0);
        }
    }
    m->faceCount = ReadBufferedU16(in);
    m->faces = (GraphFace*)AllocateZeroedFrontMemory(m->faceCount << 5);
    for (s32 e = 0; e < m->faceCount; e++) {
        s32 a;
        GraphFace* f = (GraphFace*)((u8*)m->faces + (e << 5));
        ReadBufferedVector3(in, f);
        f->f10 = ReadBufferedFloat(in);
        a = ReadBufferedS16(in);
        if (a == -1) {
            f->neighbourA = 0;
        } else if (a >= 0) {
            f->neighbourA = (u8*)m->faces + (a << 5);
        } else {
            a += 2;
            a = -a;
            f->neighbourA = (void*)((u32)(m->tris + a * 12) | 1);
        }
        a = ReadBufferedS16(in);
        if (a == -1) {
            f->neighbourB = 0;
        } else if (a >= 0) {
            f->neighbourB = (u8*)m->faces + (a << 5);
        } else {
            a += 2;
            a = -a;
            f->neighbourB = (void*)((u32)(m->tris + a * 12) | 1);
        }
    }
    func_001919F8(m);
}

void* func_001925F0(void);

void* func_00192620(void)
{
    void* r = GetActiveSwitchedCollider();
    if (r == 0) {
        Player* q = g_player;
        if (q != 0) {
            s32 t = q->f550;
            if (t != 0) r = q;
        }
    }
    if (r == 0 && g_switchedColliderCount != 0) {
        r = g_switchedColliders[0];
    }
    return r;
}

extern f32 D_0024B650;
void func_00182C18(BaseObject* self);

void func_00191F08(C70* self)
{
    InitObject(self);
    self->q40 = *(Quad70*)&g_unitXVector;
    self->f54 = 9;
    self->f50 = 8;
    self->f58 = -1;
    self->f5C = D_0024B650;
    self->id64 = -1;
}

// kind==0x10 loop test at the top (retail tests it with the first slot peeled) and
// keeps one more register (frame 64 bytes as retail, but a different loop shape).

struct Sub_192230;

void func_00127378(SwitchedCollider* self, s32 kind, void* msg);
void func_001BF788(Sub_192230* self, s32 n);

void func_00192230(SwitchedCollider* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    switch (kind) {
    case 0xB:
        StopSoundRecord(((Sub_192230*)self->f574), 0);
        break;
    case 0x10: {
        s32 i;
        for (i = 0; i < self->f5D0; i++) {
            if (self->f5AC[i] == msg) {
                self->f5AC[i] = 0;
                break;
            }
        }
        break;
    }
    }
}

extern f32 D_0026A700;
extern f32 D_0026A704;
extern f32 D_0026A708;
extern f32 D_0026A70C;

void func_001BE998(void);

// NEAR: the frame, calls and branch shape match; the saved registers are swapped (retail keeps the input base in $s2 and the moving "last" pointer in $s3, ours the other way round), which changes 18 lines.

void func_0018D608(void);
s32* func_0018D658(s32 bytes);
void func_0018D800(void* dst, void* src, s32 bytes);
void func_0018D6F0(void);
s32 func_00190E30(void* self, s32 a, s32 b);

void func_00191128(void* a0, s32* a1, s32* a2)
{
    s32 count;
    s32* out;
    s32* end;
    s32* last;
    s32* base;
    s32* q;
    s32* p;
    s32 n;
    s32 val;

    last = a2;
    base = a2;
    p = base + 1;
    q = base + 2;
    PushBackMemoryMark();
    n = *a1;
    out = AllocateBackMemory(n << 2);
    end = base + n;
    out[0] = base[0];
    count = 1;
    if (q < end) {
        do {
            if (func_00190E30(a0, *last, *q) != 0) {
                val = *p;
                last = p;
                p = q;
                q++;
                out[count] = val;
                count++;
            } else {
                p = q;
                q++;
            }
        } while (q < end);
    }
    out[count] = base[n - 1];
    count++;
    if (count < n) {
        if (count >= 3) {
            SimplifyPointPath(a0, &count, out);
        }
    }
    CopyMemory(base, out, count * 4);
    *a1 = count;
    PopBackMemoryMark();
}

s32 func_00160148(s32 v);

void func_001C8C08(C0E* self);
void func_001C8418(C0E* self, void* p);
s32 func_00182FC8(void* p);
s32 func_001F3BD8(void* self, s32* arg);

void func_00190128(C0E* self, s32 flag)
{
    s32 tmp[4];

    switch (self->f724) {
    case 7:
        if (flag != 0) {
            s32 i;
            void** slot;
            for (i = 0, slot = self->fC14; i < self->fC10; slot++, i++) {
                void* n = *slot;
                if (IsObjectAttached(n) != 0) {
                    func_001C8418(self, (u8*)n + 0x140);
                    break;
                }
            }
        }
        break;
    case 4:
        if (self->f750 == 0) {
            if (self->fC24 != 0) {
                GetObjectWorldPosition(self->fC24, tmp);
                func_001C8418(self, tmp);
            } else {
                func_001C8418(self, &self->v140);
            }
        } else {
            UpdateAgentGoal(self);
        }
        break;
    case 12:
    case 13:
        if (self->fC28 != 0) {
            GetObjectWorldPosition(self->fC28, tmp);
            func_001C8418(self, tmp);
        }
        break;
    default:
        UpdateAgentGoal(self);
        break;
    }
}

struct Elem_190570 {
    u8 pad0[0x724];
    s32 kind;
};

s32 func_001300E8(Elem_190570* node, s32 kind);
s32 func_00182FC8(Elem_190570* p);

s32 func_00190570(C0E* self)
{
    s32 i;
    if (self->fC28 != 0) {
        for (i = 0; i < self->fC10; i++) {
            Elem_190570* n = (Elem_190570*)self->fC14[i];
            if (IsObjectOfKind(n, 8) != 0) {
                s32 k = n->kind;
                if (k == 0xB) {
                    continue;
                }
                if (IsObjectOfKind(n, 9) == 0 && k == 0xA) {
                    continue;
                }
            }
            if (IsObjectAttached(n) != 0) {
                break;
            }
        }
        if (i < self->fC10) {
            return 1;
        }
        self->fC28 = 0;
    }
    return 0;
}

struct Out_190E30 {
    u8 pad0[0x40];
    f32 f40;
    f32 f44;
    u8 pad1[0x98];
};

s32 func_001909F0(void* a, s32 b, s32 c, s32 d, Out_190E30* e);

s32 func_00190E30(void* a, s32 b, s32 c)
{
    Out_190E30 out;
    switch (func_001909F0(a, b, c, 2, &out)) {
    case 0:
        return 1;
    case 1:
        if (out.f40 == 0.0f && out.f44 == 1.0f) {
            return 0;
        }
        return 1;
    case 2:
        return 1;
    }
    return 1;
}

struct Ent_192B58;
typedef void (*VFn_192B58)(void* self);

extern u8* D_002623C0;

void func_001B93F8(SwitchedCollider* self);
void func_00192DD0(SwitchedCollider* self);

struct Clamp_192B58 {
    static s32 Of(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) return lo;
        if (hi < v) return hi;
        return v;
    }
};

void func_00192B58(SwitchedCollider* self)
{
    UpdateCollider(self);

    u8* ctx = g_saveData;
    s32 cnt = *(s32*)(ctx + 0x19E4);
    s32 lim = Clamp_192B58::Of(cnt, 0, 2);

    for (s32 i = 0; i < 3; i++) {
        void* e = self->f588[i];
        if ((self->flags & ((u64)1 << 32)) == 0 && i == lim) {
            if (e != 0) {
                (*(VFn_192B58**)e)[6](e);
            }
        } else {
            if (e != 0) {
                (*(VFn_192B58**)e)[7](e);
            }
        }
    }

    if (self->f600 == 1 || self->f600 == 3) {
        func_00192DD0(self);
    }
}

f32 func_001EAF28(f32 x);

f32 D_00269BC0[3] = { 1000.0f, 10.0f, 1.0f };
Entry_269BD0 D_00269BD0 = { 0x18, -1, 0, 0, 1.0f, 2.0f, 0, 0, 1.0f, 2.0f, 0, 0, 0, 1, 0, 0 };
void* D_00269C98[16] = { 0 };
