// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x146100 to 0x149398 (its .rodata from 0x249E50, its .data from 0x2619A0):
// class 0x39's methods (0x146100 to 0x146340), then class 0x55 and the classes 0x56 to 0x5B
// derived from it, with their helpers. Its name is ours, after the state notifiers it
// holds most of.
#include "common.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "asm_func.h"
#include "state_notifier.h"
#include "world.h"
#include "scaled_offset_object.h"
#include "game_progress.h"
#include "object_link.h"
#include "switched_collider.h"
#include "camera.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "flag_table.h"
#include "deferred_request.h"
#include "shapes.h"
#include "list_iter.h"

void SetClass75ObjectField90(void* a, s32 b);
void LoadPlacedObject(void* a, void* b);
void ResolveObjectLinks(void* a, s32 b, void* c);
void CopyPlacedObject(void* a, void* b);
extern u8 g_flagTable[];
void StartPlacedObject(void* a);
void* FindFirstObjectByIdGathered(void* a, s32 b, s32 c, void* d);
s32 TestFlagTableBit(void* a, s32 b);

extern s32 D_00270458;
extern f32 g_frameDt;
void LoadCollider(Collider* self, void* p);
f32 ReadBufferedFloat(void* p);
void StartPlacedObject(void* self);
void ApplyScaledOffset(ScaledOffsetObject* self);
void ClearRootObjectStateBits(World* a, void* self, s32 n);
void ClearRootTries(void* self);
void InitCollider(Collider* self);
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* sub, s32* out);
void* AppendQueuedCall(void* owner, void* fn, void* ctx, s32 a3, s32 a4);
void CompleteTimeRangeNotifier(void* self);

// What a notifier tells the world's object (World::f1D60, its slot 27) or its listener (slot 31)
// when it fires: the state and itself.
struct StateMessage {
    s32 state;              // 0x00
    void* sender;           // 0x04
};

// The frame of a notifier's message handler (func_00147EF8, func_00148770, func_00148E40): the
// message it sends, and the code func_001B6598 gives it at 0x50.
struct NotifyFrame {
    StateMessage note;      // 0x00
    u8 pad08[0x50 - 0x08];
    s32 code;               // 0x50
    u8 pad54[0x60 - 0x54];
};

// The 0x50-byte message a notifier sends its listener's slot 31 (func_00148298, func_00148888,
// func_00148FF0): the new state and the sender.
struct ListenerMessage {
    s32 state;              // 0x00
    void* sender;           // 0x04
    u8 pad08[0x50 - 0x08];
};

s32 IsObjectOfKind(void* node, s32 kind);
extern u8 g_flagTable[];
void InitPlacedObject(StateNotifier* self);
void AppendToList(List01* list, StateNotifier* item);
s32 TakeFlagTableIndex(FlagTable* p);

struct __attribute__((packed)) PSys_1481A0 {
    u8 pad0[0x26C];
    f32 f26C;
};

void PlaceSpareSoundNotifier(World* self);
void AddReserveUnit(void);
s32 GetSpareCountLimit(void);


extern s32 D_0026EC58;
s32 IsObjectOfKind(void* node, s32 kind);
SwitchedCollider* GetActiveSwitchedCollider(void);


extern s32 D_00275C34;
extern u8 g_scatterController[];
extern u8 g_memoryCard[];
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void ResetScatterLevels(void* p);
void StartMemoryCardSave(void* p);
extern void* g_deadlineNotifier;
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void* AppendQueuedCall(void* target, void* fn, void* ctx, s32 a, s32 b);

extern f32 g_gameTime;
void AppendToList(void* table, void* self);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void SetBestTimeState(T217D_1380* self, s32 n);

void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void* AppendQueuedCall(void* target, void* fn, void* ctx, s32 a, s32 b);
void CompleteCountdownNotifier(void* self);

extern s32 D_00270458;
extern f32 g_frameDt;

extern void* D_00261B60[28];
extern u8 g_flagTable[];
f32 RandomFloatInRange(f32 a, f32 b);
Effect* CreateEffect(s32 kind, EffectOwner* sys);
void SetFlagTableBit(void* table, s32 v);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void AddReserveUnitNow(void* self);

void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern u8 D_0026EC60[];

extern u8 g_camera[];
extern u8 g_identityMatrix[];

extern u8 g_identityMatrix[];
extern u8 D_00248D30[];
extern f32 D_00261B40;
void PushBackMemoryMark(void);
StateNotifier** AllocateBackMemory(s32 size);
s32 GatherObjectsOfKind(World* self, s32 a1, s32 n, StateNotifier** arr);
f32 RandomFloatInRange(f32 a, f32 b);
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
void QueryValueListMask(World* a, f32 f, void* b, void* c); // stays void: retail returns a value, but declared so func_00148AC0 differs in registers
void PopBackMemoryMark(void);


struct __attribute__((aligned(16))) Quad_148038 {
    s32 a, b, c, d;
};

struct Ctx_148038;
extern f32 D_00261AB0[4];
extern u8 g_identityMatrix[];
extern u8 D_00248D30[];
extern Quad_148038 D_00261AC0;
s32 GatherObjectsOfKind(World* self, s32 a1, s32 a2, void** out);
s32 GetSpareCountLimit(void);
void UnprojectCameraPoint(Ctx_148038* a, void* b, void* c);
s32 QueryValueListMask(Ctx_148038* self, f32 x, void* vec, void* out);

extern void* D_00261AD0[28];
Effect* CreateEffect(s32 kind, EffectOwner* sys);
void CountPickupTowardHundred(void* self);
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

ObjectLink g_stateNotifierLinks[5] = {

    { 0, 0x25F, 0x2E4 },
    { 2, 0x25B, 0x324 },
    { 2, 0x25C, 0x328 },
    { 2, 0x25E, 0x380 },
    { 2, 0x25D, 0x384 },
};
f32 D_002619DC = -5.0f;
f32 D_002619E0 = 0.25f;
f32 D_002619E4 = 1.0f;
f32 D_002619E8 = 0.25f;
f32 D_002619EC = 5.0f;
f32 D_002619F0[4] = { 0.0f, 0.0f, -2250.0f, 0.0f };
f32 D_00261A00[4] = { 0.0f, 75.0f, 85.0f, 0.0f };
f32 D_00261A10[4] = { 10.0f, 0.0f, 0.25f, 0.0f };
f32 D_00261A20[12] = { 20.0f, 5.0f, 0.150000006f, 120.0f, 800.0f, 50.0f, 0.25f, 4500.0f, 800.0f, 50.0f, 0.25f, 4500.0f };
f32 D_00261A50 = 300.0f;
INCLUDE_DATA(D_00261A54);
f32 D_00261A60[4] = { 1.0f, 1.0f, 0.0f, 0.0f };
f32 D_00261A70[4] = { -250.0f, 0.0f, 600.0f, 0.0f };
f32 D_00261A80[4] = { 1.0f, -0.300000012f, 0.0f, 0.0f };
f32 D_00261A90[4] = { 0.699999988f, -0.400000006f, 0.0f, 0.0f };
f32 D_00261AA0[4] = { 0.0f, 800.0f, 1200.0f, 0.0f };
f32 D_00261AB0[4] = { -0.6f, 0.85f, 300.0f, 0.0f };
Quad_148038 D_00261AC0 = { 0x40A00000, (s32)0xC3FA0000, 0, 0 };
void* D_00261AD0[28] = {
    (void*)0xBF59999A, (void*)0x3F4CCCCD, (void*)0x42C80000, 0,
    (void*)0xBF800000, (void*)0xBF800000, 0, 0,
    (void*)0xBF800000, (void*)0x40000000, 0, 0,
    (void*)0x3F800000, (void*)0x40400000, 0, 0,
    0, 0, (void*)0x3F800000, 0,
    (void*)0x3F800000, (void*)0xBF4CCCCD, 0, 0,
    (void*)CountPickupTowardHundred, 0, 0, 0
};
f32 D_00261B40 = 0.05f;
f32 D_00261B48[2] = { 75.0f, 1e+02f };
f32 D_00261B50[4] = { 1e+03f, 1.3e+03f, 0.0f, 0.0f };
void* D_00261B60[28] = {
    (void*)0xBD4CCCCD, (void*)0x3F4CCCCD, (void*)0x42C80000, 0,
    (void*)0xBF800000, (void*)0xBF800000, 0, 0,
    (void*)0xBF800000, (void*)0x40000000, 0, 0,
    (void*)0x3F800000, (void*)0x40400000, 0, 0,
    0, 0, (void*)0x3F800000, 0,
    (void*)0x3F800000, (void*)0xBF4CCCCD, 0, 0,
    (void*)(void (*)(void))AddReserveUnitNow, 0, 0, 0
};
f32 D_00261BD0[4] = { 0.0f, 0.0f, 200.0f, 0.0f };
f32 D_00261BE0 = 0.75f;
INCLUDE_DATA(D_00261BE4);

void InitScaledOffsetObject(ScaledOffsetObject* self)
{
    InitCollider(self);
    self->scale = 100.0f;
}

void LoadScaledOffsetObject(ScaledOffsetObject* self, void* p)
{
    LoadCollider(self, p);
    self->factorX = ReadBufferedFloat(p);
    self->factorY = ReadBufferedFloat(p);
}

void StartScaledOffsetObject(ScaledOffsetObject* self)
{
    StartPlacedObject(self);
    ApplyScaledOffset(self);
}

void ResolveScaledOffsetContact(ScaledOffsetObject* self, Contact03* c, s32 end)
{
    Vec02 push;
    Vu0::Q(push) = Vu0::Cross(Vu0::Q(self->m110.r[1]), Vu0::Q(c->v80));
    f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(push)));
    if (!(len < 0.0001f)) {
        Vec02 w;
        Vec02* v = &c->end[end].v30;
        u128 cur = Vu0::Q(*v);
        Vu0::Q(w) = Vu0::FromFloat(-(self->scale / len));
        Vu0::Q(push) = Vu0::MulX(Vu0::Q(push), Vu0::Q(w));
        Vu0::Q(*v) = Vu0::Sub(cur, Vu0::Q(push));
    }
}

void SetOffsetScale(ScaledOffsetObject* self, f32 v)
{
    if (v != self->scale) {
        self->scale = v;
        ClearRootObjectStateBits(self->world, self, 7);
        ApplyScaledOffset(self);
        ClearRootTries(self);
    }
}

void ApplyScaledOffset(ScaledOffsetObject* self)
{
    for (s32 i = 0; i < self->elemCount; i++) {
        if (self->elems[i]->kind == 6) {
            Elem02* e = self->elems[i];
            e->x = -(self->scale * self->factorX);
            e->y = -(self->scale * self->factorY);
            break;
        }
    }
}

void InitStateNotifier(StateNotifier* self)
{
    self->initialMode = 0;
    self->f388 = 30.0f;
    self->state = self->f2DC = -1;
    InitPlacedObject(self);
    AppendToList(&self->world->list1C54, self);
    s32 v = TakeFlagTableIndex((FlagTable*)g_flagTable);
    self->f37C = v;
    self->tint[2] = 0x10;
    self->tint[1] = 0x10;
    self->tint[0] = 0x10;
    self->tint[3] = 0x10;
    self->armed = 1;
}

void LoadStateNotifier(StateNotifier* self, void* arg)
{
    SetClass75ObjectField90(self, 1);
    LoadPlacedObject(self, arg);
    ResolveObjectLinks(self, 5, g_stateNotifierLinks);
}

void CopyStateNotifier(StateNotifier* self, void* arg)
{
    s32 keep = self->f37C;
    u64 tmp;
    __builtin_memcpy(&tmp, self->tail374, 8);
    CopyPlacedObject(self, arg);
    __builtin_memcpy(self->tail374, &tmp, 8);
    self->f37C = keep;
}

void StartStateNotifier(StateNotifier* self)
{
    StartPlacedObject(self);
    void* r = FindFirstObjectByIdGathered(self->world, 1, 0x75, self);
    self->f2EC = r;
    if (r != 0) {
        ((void (*)(void*))((void**)*(void***)r)[7])(r);
    }
    GameProgress* g = g_saveData;
    if (((g->f19D8 << 8) | g->f19DC) != 0x308) {
        if (TestFlagTableBit(g_flagTable, self->f37C)) {
            self->initialMode = 2;
        }
    }
    self->desc02()->m2F(self, self->initialMode);
}

extern f32 g_gameTime;
extern u8 g_camera[];
extern u8 D_00248D30[];
extern f32 D_002619DC;
extern f32 D_002619E0;
extern f32 D_002619E8;
extern f32 D_00261A00[4];
extern f32 D_00261A10[4];
extern f32 D_00261A20[12];
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
extern u8 g_unitXVector[];
extern const Vec02 g_unitZVector;
void* GetActiveSwitchedColliderData(void);
void BuildBasisFromX(Vec02* v, Mat02* out);
void BuildAxisAngleMatrix(f32* axis, Mat4* mat, f32 angle);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* axis, f32* angle);
extern Player* g_player;
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);
f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, f32* params, f32* out);
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);
f32 ApproachAngleWithRamp(f32 a, f32 b, f32 c, f32* params, s32 z);
void ComputeObjectFrameAtTime(void* obj, s32 b, Vec02* pos, Mat02* rot, f32 t, s32 e, s32 f);
void BuildBasisFromXAndZHint(Vec02* x, const Vec02* z, Mat02* out);

// What the active switched collider gives the notifier (GetActiveSwitchedColliderData): the
// object it is placed by, the one it times its frame on and the one whose heading it takes.
struct NotifierLead {
    s32 f00;
    PlacedObject* f04;
    u8 pad08[0x0C - 0x08];
    PlacedObject* f0C;
    u8 pad10[0x18 - 0x10];
    PlacedObject* f18;
};

// The sources an object's animation gives (slot 0 of each): an offset or a frame, and a spin.
struct NotifierSource;
struct NotifierSourceVt { void (*get)(NotifierSource* self, StateNotifier* owner, s32 z, void* a, Vec02* b, f32 t, f32 u); };
struct NotifierSource { NotifierSourceVt* vt; };
struct NotifierSources { u8 pad0[4]; NotifierSource* pos; NotifierSource* rot; };
struct NotifierAnimDesc { u8 pad0[0x9C]; NotifierSources* sources; };
struct NotifierAnim { u8 pad0[8]; NotifierAnimDesc* desc; u8 pad0C[0x14 - 0x0C]; f32 f14; f32 f18; };
struct NotifierHost { u8 pad0[0x24]; NotifierAnim* anim; };

static inline s32 IsNearlyEqual(f32 a, f32 b)
{
    return AreFloatsNearlyEqual(a, b, 0.0001f);
}

// A walk of a list with its frame pushed on g_activeListFrames for as long as it lives.
struct NotifierListFrame {
    void* list;
    void* cursor;
    s32 next_off;
    NotifierListFrame* prev;
    NotifierListFrame(List01* l)
    {
        list = l;
        cursor = l;
        next_off = l->offset;
        prev = (NotifierListFrame*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~NotifierListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

// An object's placement set to the product a b of two rotations (MulRotation's rows): the
// object's own pointer is the one the rows are stored through.
static inline void SetRotationProduct(PlacedObject* o, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    o->rot = r;
}

// The same with a's rows loaded once as values and each row's two stores chained, as
// MulRotationRowsX (include/mul_rotation.h).
static inline void SetRotationProductRows(PlacedObject* o, const Mat02& a, const Mat02& b)
{
    const u128* q = (const u128*)&a;
    u128 a0 = q[0];
    u128 a1 = q[1];
    u128 a2 = q[2];
    const u128* p = (const u128*)&b;
    u128 b0 = p[0];
    u128 b1 = p[1];
    u128 b2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, b0);
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, b1);
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, b2);
    o->rot = r;
}

void MoveStateNotifier(StateNotifier* self, f32 dt, s32 quiet)
{
    switch (self->state) {
    case 4: {
        Vec02 v;
        Vec02 w;
        Mat02 m;
        Mat02 n;
        Mat02 p;
        NotifierLead* lead = (NotifierLead*)GetActiveSwitchedColliderData();
        v = *(Vec02*)D_00261A00;
        PlacedObject* o = lead->f18;
        f32 a = WrapAngle(ArctangentOfRatio(o->m110.r[0].y, o->m110.r[0].x)) + 15.707964f;
        v.x = a;
        f32 d = a - self->v2F0.x;
        if (__builtin_fabsf(d + 6.2831855f) < __builtin_fabsf(d)) {
            v.x = a + 6.2831855f;
        }
        f32* vel = &self->v300.x;
        f32* cur = &self->v2F0.x;
        for (s32 i = 0; i < 3; i++) {
            cur[i] = ApproachValueClampingVelocity(cur[i], vel[i], (&v.x)[i], dt, &D_00261A20[i * 4], &vel[i]);
        }
        u128 g = Vu0::Q(v);
        u128 c = Vu0::Q(self->v2F0);
        s32 same = IsNearlyEqual(Vu0::ToFloatMoved(g), Vu0::ToFloatMoved(c))
            && IsNearlyEqual(Vu0::ToFloatY(g), Vu0::ToFloatY(c))
            && IsNearlyEqual(Vu0::ToFloatZ(g), Vu0::ToFloatZ(c));
        if (same) {
            self->f370 = 1;
        }
        ComputePolarOffset(&w, self->v2F0.x, self->v2F0.y, self->v2F0.z);
        *(Vu0::Vec*)&self->pos = Vu0::Add(Vu0::Vec::Of(lead->f04->v140), Vu0::Vec::Of(w));
        self->v150 = *(Vec02*)&D_00248D30;
        Vu0::Q(w) = Vu0::Sub(Vu0::Q(lead->f04->v140), Vu0::Q(self->pos));
        w.z *= D_002619E0;
        BuildBasisFromX(&w, &m);
        BuildAxisAngleMatrix((f32*)g_unitXVector, (Mat4*)&n, -2.5f);
        MulRotation(&m, m, n);
        f32 t = ApproachAngleWithRamp(self->f35C, 0.0f, dt, D_00261A10, 0);
        self->f35C = t;
        BuildAxisAngleMatrix(&self->v360.x, (Mat4*)&p, t);
        SetRotationProduct(self, p, m);
        break;
    }
    case 5: {
        Vec02 v;
        Vec02 w;
        Mat02 m;
        Mat02 n;
        Mat02* rot = &self->rot;
        NotifierLead* lead = (NotifierLead*)GetActiveSwitchedColliderData();
        f32 t = self->stateSince + D_002619E8 - g_gameTime;
        ComputeObjectFrameAtTime(lead->f0C, 0, &v, &m, t, 0, 0);
        MultiplyMatrices3x3(rot, &m, &n);
        f32 angle;
        MatrixToAxisAngle(&n, &angle, &w.x);
        f32 k = dt / (t >? dt);
        BuildAxisAngleMatrix(&w.x, (Mat4*)&n, angle * k);
        SetRotationProductRows(self, n, *rot);
        Vu0::Q(self->pos) = Vu0::MulXSum(Vu0::Q(v), Vu0::Scalar(k), Vu0::Q(self->pos), Vu0::Scalar(1.0f - k));
        break;
    }
    case 7: {
        Vec02 v;
        f32 t = g_player->f2424 - g_gameTime;
        t = t >? 0.0f;
        f32 k = dt / (t + dt);
        ComputeObjectFrameAtTime(g_player->f23D4, 0, &v, 0, t, 0, 0);
        Vu0::Q(self->pos) = Vu0::MulXSum(Vu0::Q(v), Vu0::Scalar(k), Vu0::Q(self->pos), Vu0::Scalar(1.0f - k));
        break;
    }
    default: {
        f32 drag;
        if (self->state == 0 || self->state == 6) {
            drag = D_002619DC * dt + 1.0f;
        } else {
            drag = 1.0f;
        }
        Vu0::Q(self->v300) = Vu0::MulXSum(Vu0::Q(self->v300), Vu0::Scalar(drag), Vu0::Q(self->v310), Vu0::Scalar(dt));
        Vu0::Q(self->v2F0) = Vu0::MulAddX(Vu0::Q(self->v2F0), Vu0::Q(self->v300), Vu0::Scalar(dt));
        Vu0::Q(self->pos) = Vu0::Q(self->v2F0);
        Vu0::Q(self->v150) = Vu0::Q(self->v300);
        break;
    }
    }
    NotifierHost* h = (NotifierHost*)self->f2E8;
    if (h != 0 && h->anim != 0 && h->anim->desc->sources != 0) {
        Vec02 v;
        Vec02 off;
        Vec02 spin;
        Vec02 turn;
        Mat02 face;
        Mat02 r;
        Vu0::Q(v) = Vu0::Sub(Vu0::Q((*(Camera**)g_camera)->f40), Vu0::Q(self->pos));
        v.z = 0.0f;
        BuildBasisFromXAndZHint(&v, (Vec02*)&g_unitZVector, &face);
        NotifierAnim* an = ((NotifierHost*)self->f2E8)->anim;
        NotifierSource* src = an->desc->sources->pos;
        if (src != 0) {
            src->vt->get(src, self, 0, &off, &spin, an->f14, an->f18);
            Vu0::Q(self->pos) = Vu0::Add(Vu0::Q(self->pos), Vu0::Rotate(face, Vu0::Q(off)));
            Vu0::Q(self->v150) = Vu0::Add(Vu0::Q(self->v150), Vu0::Rotate(face, Vu0::Q(spin)));
        }
        an = ((NotifierHost*)self->f2E8)->anim;
        src = an->desc->sources->rot;
        if (src != 0) {
            src->vt->get(src, self, 0, &r, &turn, an->f14, an->f18);
            SetRotationProduct(self, face, r);
            Vu0::Q(self->v160) = Vu0::Rotate(face, Vu0::Q(turn));
        }
    }
    NotifierListFrame frame(&self->children);
    PlacedObject* head = *(PlacedObject**)frame.list;
    frame.cursor = (u8*)head + frame.next_off;
    PlacedObject* c = head;
    if (c != 0) {
        do {
            if (c->desc->flags & 1) {
                ((void (*)(PlacedObject*, f32, s32))c->desc->m1B)(c, dt, 1);
            }
            PlacedObject* next = *(PlacedObject**)frame.cursor;
            frame.cursor = (u8*)next + frame.next_off;
            c = next;
        } while (c != 0);
    }
    if (quiet == 0) {
        void (*fn)(BaseObject*) = self->desc->m12;
        if (fn != 0) {
            fn(self);
        }
    }
}

s32 IsEligibleNotifierTarget(void* unused, Collider* self)
{
    u64 bit = 0x8000;
    bit <<= 28;
    if (self->flags538 & bit) {
        return 0;
    }
    if (IsObjectOfKind(self->root, 5) != 0 || IsObjectOfKind(self->root, 0x27) != 0 ||
        IsObjectOfKind(self->root, 0x3B) != 0 || IsObjectOfKind(self->root, 0x40) != 0 ||
        IsObjectOfKind(self->root, 0x2E) != 0) {
        return 0;
    }
    return 1;
}

// A hit CollectMeshHits gives (0x30 bytes): the surface's normal at 0x10, the depth at 0x20.
struct NotifierMeshHit {
    u8 pad0[0x10];
    Vec02 normal;           // 0x10
    f32 depth;              // 0x20
    u8 pad24[0x30 - 0x24];
};

extern const f32 D_00248D40[4];
extern u8 g_unitXVector[];
s32 CollectMeshHits(f32 f0, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6);
extern const Vec02 g_unitZVector;
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*),
                          StateNotifier* self, s32* n, Collider*** list);
f32 SplitVectorAlongAxis(Vec02* v, const Vec02* axis, Vec02* along, Vec02* across);

void BounceStateNotifierOffSurfaces(StateNotifier* self)
{
    typedef Vu0::Vec Vec;
    PushBackMemoryMark();
    f32 best = 0.0f;
    Vec02 lo;
    Vec02 hi;
    Vu0::Q(lo) = Vu0::MulAddX(Vec::Of(self->v140), Vec::Of(D_00248D40), Vec::Scalar(-self->f34C)).q;
    Vu0::Q(hi) = Vu0::MulAddX(Vec::Of(self->v140), Vec::Of(D_00248D40), Vec::Scalar(self->f34C)).q;
    Vec02 dir;
    Vec02 bestN;
    NotifierMeshHit hits[8];
    s32 count;
    Collider** list;
    GatherCollidersInBox(self->world, 0, &lo, &hi, IsEligibleNotifierTarget, self, &count, &list);
    for (s32 i = 0; i < count; i++) {
        Collider* c = list[i];
        if (c->flags538 & 0x10000000000ULL) {
            f32 dist = Vu0::Distance(c->v140, self->v140) - c->radius3CC - self->f34C;
            if (dist < best) {
                Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vec::Of(self->v2F0), Vec::Of(c->v140)),
                                               Vec::Of(*(Vec02*)g_unitXVector)).q);
                if (Vu0::ToFloat(Vu0::Dot(Vec::Of(self->v300), Vec::Of(dir))) < 0.0f) {
                    best = dist;
                    bestN = dir;
                }
            }
        } else if (c->tree.nodes != 0) {
            s32 n = CollectMeshHits(self->f34C, &self->v140, (void*)c->tree.count, c->tree.nodes, 0,
                                    &c->meshCopy, 8, hits);
            for (s32 j = 0; j < n; j++) {
                NotifierMeshHit* h = &hits[j];
                f32 depth = h->depth;
                if (depth < best && Vu0::ToFloat(Vu0::Dot(Vec::Of(self->v300), Vec::Of(h->normal))) < 0.0f) {
                    bestN = h->normal;
                    best = depth;
                }
            }
        }
    }
    f32 zero = 0.0f;
    if (best < zero) {
        Vec02 along;
        Vec02 across;
        Vec02 motion;
        if (0.7f < bestN.z && self->state == 3) {
            SplitVectorAlongAxis(&self->v300, &g_unitZVector, &along, &across);
            Vu0::Q(motion) = Vu0::MulXSum(Vec::Of(along), Vec::Scalar(-self->f354), Vec::Of(across),
                                          Vec::ScalarAt(self->f358)).q;
            if (self->f33C == 0) {
                s32 low = Vu0::ToFloat(Vu0::Dot(Vec::Of(motion), Vec::Of(bestN))) < self->f348;
                if (low) {
                    across.z = zero >? across.z;
                    Vu0::Q(motion) = Vu0::MulAddX(Vec::Of(across), Vec::Of(g_unitZVector), Vec::Scalar(self->f348)).q;
                    self->f33C = 1;
                }
            }
        } else {
            SplitVectorAlongAxis(&self->v300, &bestN, &along, &across);
            Vu0::Q(motion) = Vu0::MulXSum(Vec::Of(along), Vec::Scalar(-self->f354), Vec::Of(across),
                                          Vec::ScalarAt(self->f358)).q;
        }
        Vu0::Q(self->v2F0) = Vu0::MulAddX(Vec::Of(self->v2F0), Vec::Of(bestN), Vec::Scalar(-best)).q;
        self->v300 = motion;
    }
    PopBackMemoryMark();
}

struct ActiveNotifierData {
    s32 f00;
    u8 pad04[0x14 - 0x04];
    f32 f14;
    PlacedObject* f18;
};

void* GetActiveSwitchedColliderData(void);
s32 MaskWorldBitsBySave(void);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, s32 a, s32 b, s32 c);
s32 CollectMeshHits(f32 f0, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6);

void TriggerStateNotifierNearPlayer(StateNotifier* self)
{
    Vec02 hit[3];
    Vec02 p0;
    Vec02 p1;
    if (self->armed != 0) {
        ActiveNotifierData* d = (ActiveNotifierData*)GetActiveSwitchedColliderData();
        if (d->f00 != 0 && d->f18 != 0) {
            Vec02* pos = &self->v140;
            f32 r = D_00261A50;
            u128 diff = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(d->f18->v140));
            f32 sq = Vu0::ToFloatMoved(Vu0::Dot(diff, diff));
            if (!(r * r < sq)) {
                f32 reach = d->f14;
                if (sq < reach * reach) {
                    self->desc02()->m2F(self, 1);
                    return;
                }
                if ((MaskWorldBitsBySave() & 0x20) != 0 && IsObjectOfKind(self, 0x58) != 0) {
                    ComputeObjectMotionInFrame(d->f18, 0, &d->f18->v140, &p0, 0, 0, 0);
                    ComputeObjectMotionInFrame(self, 0, pos, &p1, 0, 0, 0);
                    u128 dd = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(d->f18->v140));
                    u128 fb = *(const u128*)&D_00248D30;
                    u128 rel = Vu0::Sub(Vu0::Q(p1), Vu0::Q(p0));
                    u128 dir = Vu0::NormalizeOrMoved(dd, fb);
                    if (-50.0f < Vu0::ToFloat(Vu0::Dot(rel, dir))) {
                        self->desc02()->m2F(self, 1);
                        return;
                    }
                }
                PlacedObject* o = d->f18;
                if ((o->desc->flags & 2) != 0 && *(void**)((u8*)o + 0x3F8) != 0) {
                    if (CollectMeshHits(self->f350, pos, *(void**)((u8*)o + 0x3F0), *(void**)((u8*)o + 0x3F8), 0, (u8*)o + 0x3A4, 1, hit) != 0) {
                        self->desc02()->m2F(self, 1);
                    }
                }
            }
        }
    }
}

s32 HandleStateNotifierContact(StateNotifier* self, ContactObject* b)
{
    if (self->armed != 0) {
        if (b->fC & 0x10) {
            self->desc02()->m2F(self, 1);
        }
    }
    return 1;
}


extern f32 D_00261A54;
extern f32 g_gameClock[];
extern Player* g_player;
void UpdatePlacedObject(StateNotifier* self, f32 dt);
void TransformDirectionBetweenFrames(void* to, void* from, void* in, void* out);
void BounceStateNotifierOffSurfaces(StateNotifier* self);
void TriggerStateNotifierNearPlayer(StateNotifier* self);
void CompleteSoundNotifiers(World* self);
void* GetActiveSwitchedColliderData(void);
extern World* g_currentWorld;

void UpdateStateNotifier(StateNotifier* self, f32 dt)
{
    s32 below = 1;
    Vec02 d;
    UpdatePlacedObject(self, dt);
    TransformDirectionBetweenFrames(self, 0, D_00261A60, &d);
    if (!(Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(*(Vec02*)(*(Camera**)g_camera)->f90))) < 0.0f)) {
        below = 0;
    }
    if (below != self->f32C) {
        if (RandomFloatInRange(0.0f, 1.0f) < self->f320 && D_00261A54 < g_gameClock[1] - self->f330) {
            PlacedObject* at;
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(*(Vec02*)(*(Camera**)g_camera)->f80))) < 0.0f) {
                at = self->f324;
            } else {
                at = self->f328;
            }
            if (at != 0) {
                Effect* e = CreateEffect(0x19, 0);
                if (e != 0) {
                    f32 one = 1.0f;
                    self->f330 = g_gameClock[1];
                    ((void (*)(Effect*, void*, s32, f32))e->vt->m00)(e, (u8*)at + 0x40, 0, one);
                    e->p120 = self;
                    e->life = 1.5f / (one >? __builtin_fabsf(self->v160.z));
                }
            }
        }
        self->f32C = below;
    }
    if (self->state == 7 && self->f384 != 0) {
        self->f38C = self->f38C + dt * self->f388;
        if (1.0f <= self->f38C) {
            ListenerMessage msg;
            *(s32*)(msg.pad08 + 0x38) = (s32)self->f38C;
            msg.state = 0x81;
            msg.sender = self;
            self->f384->vtbl[31](self->f384, &msg);
            self->f38C = self->f38C - (f32)(s32)self->f38C;
        }
    }
    switch (self->state) {
    case 0:
        if (10000.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v300), Vu0::Q(self->v300)))) {
            BounceStateNotifierOffSurfaces(self);
        }
        TriggerStateNotifierNearPlayer(self);
        break;
    case 3:
        if (D_002619EC < g_gameClock[1] - self->stateSince) {
            self->desc02()->m2F(self, 2);
            break;
        }
        if (self->f33C != 0 && self->v300.z < 25.0f) {
            self->f33C = 0;
            self->desc02()->m2F(self, 0);
            break;
        }
        BounceStateNotifierOffSurfaces(self);
        if (!(1.0f < g_gameClock[1] - self->stateSince)) {
            break;
        }
        ((BaseObject*)self->f2EC)->desc->m02((BaseObject*)self->f2EC);
    case 6:
        TriggerStateNotifierNearPlayer(self);
        break;
    case 4:
        if (*(s32*)GetActiveSwitchedColliderData() == 0) {
            self->desc02()->m2F(self, 3);
        } else if (*(s32*)((u8*)self + 0x370) != 0) {
            self->desc02()->m2F(self, 5);
        }
        break;
    case 5: {
        s32* active = (s32*)GetActiveSwitchedColliderData();
        if (*active != 0) {
            GameProgress* g = g_saveData;
            if (g->f19E4 < GetSpareCountLimit()) {
                goto spare;
            }
        }
        {
            PlacedObject* o = (PlacedObject*)active[6];
            Vec02 v;
            Vu0::Q(v) = Vu0::Add(Vu0::Vec::Of(o->v150), Vu0::Rotate(o->rot, Vu0::Vec::Of(D_00261A70))).q;
            self->desc02()->m20(self, &v);
            self->desc02()->m2F(self, 3);
        }
        break;
    spare:
        if (D_002619E8 < g_gameTime - self->stateSince) {
            g_saveData->f19E4++;
            self->desc02()->m2F(self, 2);
            CompleteSoundNotifiers(g_currentWorld);
        }
        break;
    }
    case 7:
        if (g_player->f2424 <= g_gameTime) {
            self->desc02()->m2F(self, 1);
        }
        break;
    }
    ClearRootTries(self);
}

// States 4 and 5 scale the drawn object by a curve of the time in the state: each arm evaluates
// it and splats it itself, so cross-jumping leaves only the arms' own loads in them.
void BuildScaledTransformMatrix(const void* pos, const void* rot, void* scale, void* out);
void BuildPlacedObjectTransform(PlacedObject* self, void* src, void* dst);
Mat4A MultiplyMatrices(const void* a, const void* b);
void ApplyPlacedObjectTransform(PlacedObject* self, void* a, void* m);

void ApplyStateNotifierScale(StateNotifier* self, void* a, void* m)
{
    if (self->flags & (1ULL << 32)) return;
    s32 state = self->state;
    switch (state) {
    case 4:
    case 5: {
        DrawTransform t;
        Quad16 scale;
        Mat4A s;
        f32 k;
        if (state == 4) {
            f32 v = (g_gameTime - self->stateSince) / D_002619E4;
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 x;
            if (v < lo) x = lo;
            else if (hi < v) x = hi;
            else x = v;
            f32* c = D_00261A80;
            k = c[0];
            k += x * (c[1] + x * c[2]);
            Vu0::Q(scale) = Vu0::Splat(k);
            } else {
            f32 v = (g_gameTime - self->stateSince) / D_002619E8;
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 x;
            if (v < lo) x = lo;
            else if (hi < v) x = hi;
            else x = v;
            f32* c = D_00261A90;
            k = c[0];
            k += x * (c[1] + x * c[2]);
            Vu0::Q(scale) = Vu0::Splat(k);
            }
        BuildScaledTransformMatrix(D_00248D30, g_identityMatrix, &scale, &s);
        BuildPlacedObjectTransform(self, m, &t);
        *(Mat4A*)&t = MultiplyMatrices(&t, &s);
        m = &t;
        break;
    }
    }
    ApplyPlacedObjectTransform(self, a, m);
}


#define CAMERA_AT(T, p, off) (*(T*)((u8*)(p) + (off)))
extern f32 g_gameTime;
extern u8 g_unitXVector[];
void* GetActiveSwitchedColliderData(void);
void ConvertOffsetToCylindrical(const Vec02* a, const Vec02* b, f32* angle, f32* dist, f32* height);
void BuildBasisFromX(Vec02* v, Mat02* out);
void BuildAxisAngleMatrix(f32* axis, Mat4* mat, f32 angle);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* axis, f32* angle);
void* CreateStateWalker(void* a, void* owner, s32 id, s32 z);
void DestroyStateWalker(void* h);
void SetStateWalkerTarget(void* h, s32 id);
void AdvanceStateWalkerTime(void* h, f32 t);
// The camera's state setter: keeps the eye and target offsets when the old state is one of -1, 2,
// 4 and 5, sets the vectors of the new state, tells the object at 0x2EC (add to or remove from
// its parent's list) and starts or stops the state walker of the state's event (0x260 to 0x263,
// or the one saved at 0x2DC in state 0).
void SetStateNotifierState(Camera* self, s32 state)
{
    s32 event = -1;
    if (CAMERA_AT(s32, self, 0x2D0) == state) {
        return;
    }
    void* active = GetActiveSwitchedColliderData();
    if (state != 0 && state != 6) {
        self->desc->m15(self, 0);
    }
    switch (CAMERA_AT(s32, self, 0x2D0)) {
    case -1:
    case 2:
    case 4:
    case 5:
        CAMERA_AT(Vec02, self, 0x2F0) = *(Vec02*)((u8*)self + 0x100);
        CAMERA_AT(Vec02, self, 0x300) = *(Vec02*)((u8*)self + 0x150);
        break;
    default:
        break;
    }
    if ((u32)state < 8) {
        switch (state) {
        case 0: {
            s32 saved = CAMERA_AT(s32, self, 0x2DC);
            CAMERA_AT(Vec02, self, 0x310) = *(Vec02*)D_00248D30;
            event = 0x261;
            if (saved != -1) {
                event = saved;
            }
            break;
        }
        case 7:
            event = 0x262;
            CAMERA_AT(Vec02, self, 0x310) = *(Vec02*)D_00248D30;
            break;
        case 3:
            event = 0x260;
            CAMERA_AT(Vec02, self, 0x310) = *(Vec02*)D_002619F0;
            break;
        case 2:
            if (CAMERA_AT(s32, self, 0x334) == 0) {
                CAMERA_AT(s32, self, 0x338) = 1;
            }
            self->desc->m03(self);
            break;
        case 4: {
            Vec02 dir;
            Mat02 m10;
            Mat02 m40;
            ConvertOffsetToCylindrical((Vec02*)((u8*)self + 0x140), (Vec02*)((u8*)CAMERA_AT(u8*, active, 4) + 0x140), (f32*)((u8*)self + 0x2F0), (f32*)((u8*)self + 0x2F4), (f32*)((u8*)self + 0x2F8));
            CAMERA_AT(Vec02, self, 0x300) = *(Vec02*)D_00261AA0;
            CAMERA_AT(Vec02, self, 0x310) = *(Vec02*)D_00248D30;
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)CAMERA_AT(u8*, active, 4) + 0x140)), Vu0::Q(*(Vec02*)((u8*)self + 0x140)));
            dir.z = dir.z * D_002619E0;
            BuildBasisFromX(&dir, &m10);
            BuildAxisAngleMatrix((f32*)g_unitXVector, (Mat4*)&m40, -2.5f);
            MulRotationRowsX(&m10, m10, m40);
            MultiplyMatrices3x3(&m10, (Mat02*)((u8*)self + 0x110), &m40);
            MatrixToAxisAngle(&m40, (f32*)((u8*)self + 0x35C), (f32*)((u8*)self + 0x360));
            CAMERA_AT(s32, self, 0x370) = 0;
            break;
        }
        case 5:
            Vu0::Q(CAMERA_AT(Vec02, self, 0x2F0)) = Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)self + 0x140)), Vu0::Q(*(Vec02*)((u8*)CAMERA_AT(u8*, active, 4) + 0x140)));
            CAMERA_AT(Vec02, self, 0x300) = CAMERA_AT(Vec02, self, 0x310) = *(Vec02*)D_00248D30;
            break;
        case 6:
            event = 0x263;
            CAMERA_AT(Vec02, self, 0x310) = *(Vec02*)D_00248D30;
            break;
        default:
            break;
        }
    }
    if (state == 0 || state == 6) {
        BaseObject* obj = CAMERA_AT(BaseObject*, self, 0x2EC);
        if (obj != 0) {
            obj->desc->m02(obj);
        } else {
            obj->desc->m03(0);
        }
    } else {
        BaseObject* obj = CAMERA_AT(BaseObject*, self, 0x2EC);
        if (obj != 0) {
            obj->desc->m03(obj);
        }
    }
    CAMERA_AT(s32, self, 0x2D0) = state;
    CAMERA_AT(f32, self, 0x2D4) = g_gameTime;
    if (event != -1) {
        void* h = CAMERA_AT(void*, self, 0x2E8);
        if (h == 0) {
            void* made = CreateStateWalker(CAMERA_AT(void*, self, 0x2E4), self, event, 0);
            CAMERA_AT(void*, self, 0x2E8) = made;
            if (0.0f < CAMERA_AT(f32, self, 0x2E0)) {
                AdvanceStateWalkerTime(made, CAMERA_AT(f32, self, 0x2E0));
            }
        } else {
            SetStateWalkerTarget(h, event);
        }
    } else {
        void* h = CAMERA_AT(void*, self, 0x2E8);
        if (h != 0) {
            DestroyStateWalker(h);
            CAMERA_AT(void*, self, 0x2E8) = 0;
        }
    }
}


void InitTimeRangeNotifier(TimeRangeNotifier* self)
{
    InitStateNotifier(self);
    f32 k = 50.0f;
    self->f34C = 45.0f;
    self->f344 = 250.0f;
    self->f348 = self->f350 = k;
    self->f358 = 0.6f;
    self->f354 = 0.75f;
    self->f320 = 0.25f;
    self->timeMin = 8.0f;
    self->timeMax = 10.0f;
}

void CompleteTimeRangeNotifier(TimeRangeNotifier* self)
{
    self->desc02()->m2F(self, 2);
}

void HandleTimeRangeNotifierNotification(TimeRangeNotifier* self, s32 kind, void* target)
{
    NotifyFrame fr;
    HandlePlacedObjectNotification(self, kind, target);
    if (kind != 0x14) return;
    if (target != self->f2E8) return;
    GetStateWalkerCurrentKey(target, &fr.code);
    if (fr.code != 0x263) return;
    BaseObject* obj = self->world->f1D60;
    if (obj != 0) {
        fr.note.state = 1;
        fr.note.sender = self;
        obj->desc->m1B(obj, &fr.note);
    }
    AppendQueuedCall(self->world, (void*)(void (*)(void*))CompleteTimeRangeNotifier, self, 0, 0);
}

void UpdateTimeRangeNotifier(TimeRangeNotifier* self)
{
    UpdateStateNotifier(self);
    if (self->state != 0) return;
    if (self->f338 == 0) return;
    if (D_00270458 != 2) {
        self->timeLeft = self->timeLeft - g_frameDt;
    }
    if (self->timeLeft <= 0.0f) {
        self->desc02()->m2F(self, 6);
    }
}

void PlaceSpareSoundNotifier(World* self)
{
    SoundNotifier* obj;
    s32 buf[4];
    GameProgress* g;
    s32 n;
    s32 c;

    if (GatherObjectsOfKind(self, 0x56, 1, (void**)&obj) == 0) {
        g = g_saveData;
        n = GetSpareCountLimit();
        c = g->f19E4 + 1;
        c = (c < n) ? c : n;
        g_saveData->f19E4 = c;
    } else {
        obj->desc->m02(obj);
        obj->desc->m15(obj, 0);
        UnprojectCameraPoint(*(Ctx_148038**)g_camera, (void*)D_00261AB0, buf);
        obj->desc02()->m1D(obj, (Vec02*)buf);
        obj->desc02()->m1E(obj, (Mat02*)g_identityMatrix);
        obj->desc02()->m20(obj, (Vec02*)D_00248D30);
        obj->desc02()->m21(obj, (Vec02*)D_00248D30);
        obj->desc02()->m2F(obj, 4);
        *(Quad_148038*)((u8*)obj + 0x300) = D_00261AC0;
        QueryValueListMask((Ctx_148038*)self->f1EC4, obj->f2A8, (u8*)obj + 0x140, (u8*)obj + 0x88);
    }
}

void AddReserveUnit(void)
{
    GameProgress* g = g_saveData;
    s32 r = 99;
    if (g->f19E0 + 1 <= 98) r = g->f19E0 + 1;
    g->f19E0 = r;
}

void CountPickupTowardHundred(void* self)
{
    Effect* s = (Effect*)self;
    GameProgress* g = g_saveData;
    s32 c = g->f19E8 + 1;
    s32 r;
    g->f19E8 = c;
    if (c >= 100) {
        r = GetSpareCountLimit();
        if (g->f19E4 < r) {
            g_saveData->f19E8 = 0;
            ((PSys_1481A0*)&D_0026CE48)->f26C = 250.0f;
            D_0026CE48.onDone = (void (*)(void*))PlaceSpareSoundNotifier;
            D_0026CE48.doneArg = s->prev;
            return;
        }
        if (g_saveData->f19E0 < 99) {
            g_saveData->f19E8 = 0;
            D_0026CE48.rate = 250.0f;
            D_0026CE48.doneArg = 0;
            D_0026CE48.onDone = (void (*)(void*))AddReserveUnit;
            {
                D_0026C6C8.vt->m14(&D_0026C6C8);
            }
        } else {
            g_saveData->f19E8 = 99;
        }
    }
}

void SetEffectNotifierState(TimeRangeNotifier* self, s32 mode)
{
    TimeRangeNotifier* s = self;
    if (s->state != mode) {
        switch (mode) {
        case 0:
            if (s->f338 != 0) {
                s->timeLeft = RandomFloatInRange(s->timeMin, s->timeMax);
            }
            break;
        case 1:
                Effect* n = CreateEffect(0x10, 0);
                if (n != 0) {
                    n->params = (const T219C_Params*)D_00261AD0;
                    n->p134 = self;
                    n->vt->m00(n, &s->v140, 1.0f, 0);
                    n->p20 = self;
                    n->rot50[0] = s->m110.r[0];
                    n->rot50[1] = s->m110.r[1];
                    n->rot50[2] = s->m110.r[2];
                } else {
                    CountPickupTowardHundred(self);
                }
                D_0026CE48.vt->m14(&D_0026CE48);
                f32 z = 0.0f;
                StartSoundEffect(0x78, 0, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
                if (s->listener != 0) {
                    ListenerMessage msg;
                    msg.state = 1;
                    msg.sender = self;
                    s->listener->vtbl[31](s->listener, &msg);
                }
                mode = 2;
            break;
        }
        SetStateNotifierState(self, mode);
    }
}

void InitSoundNotifier(SoundNotifier* self)
{
    SoundNotifier* o = self;
    InitStateNotifier(o);
    f32 k60 = 60.0f;
    f32 k300 = 300.0f;
    f32 k075 = 0.75f;
    f32 k05 = 0.5f;
    f32 k035 = 0.35f;
    o->f320 = k035;
    o->f344 = k300;
    o->f358 = k075;
    o->f354 = k05;
    o->f34C = k60;
    o->i348 = 0;
    o->f350 = k60;
}

void SetSoundNotifierState(SoundNotifier* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 1) {
        StartSoundEffect(0x74, 0, (s32)self, 0, 0, 0, 1500.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        mode = 4;
        TriggerScriptEvent(self, 2, 0, 0);
    }
    SetStateNotifierState(self, mode);
}

void InitSaveNotifier(SaveNotifier* self)
{
    SaveNotifier* o = self;
    InitStateNotifier(o);
    f32 k35 = 35.0f;
    f32 k06 = 0.6f;
    f32 k500 = 500.0f;
    f32 k250 = 250.0f;
    f32 k075 = 0.75f;
    G27C230* fl = g_currentEntry;
    o->f350 = o->f34C = k35;
    o->f344 = k500;
    o->f348 = k250;
    o->f354 = o->f358 = k06;
    o->f320 = k075;
    if (fl->flags & 2) {
        o->initialMode = 2;
    }
}

void SetSaveNotifierState(SaveNotifier* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 1) {
        G27C230* fl = g_currentEntry;
        s32 bits = fl->flags;
        if ((bits & 2) == 0) {
            G27C230* cx = g_currentLevelRecord;
            fl->flags = bits | 2;
            s32 g = D_00275C34; s32 old = cx->f438; cx->f438 = old + 1; if (g != 0) cx->f438 = old;
        }
        D_0026CBC8.vt->m14(&D_0026CBC8);
        SwitchedCollider* r = GetActiveSwitchedCollider();
        if (r != 0) {
            r->desc05()->m4E(r, 0, self);
        }
        TriggerScriptEvent(self, 2, 0, 0);
        mode = 2;
        ResetScatterLevels(g_scatterController);
        StartMemoryCardSave(g_memoryCard);
    }
    SetStateNotifierState(self, mode);
}

void InitDeadlineNotifier(DeadlineNotifier* self)
{
    InitStateNotifier(self);
    self->f34C = 60.0f;
    self->f350 = 60.0f;
    self->f344 = 500.0f;
    self->f358 = 0.6f;
    self->f348 = 250.0f;
    self->f354 = 0.6f;
    self->f320 = 0.75f;
    if (*(s32*)D_0026EC60 == 0) {
        self->initialMode = 2;
    }
}

void StartDeadlineNotifier(DeadlineNotifier* self)
{
    StartStateNotifier(self);
    g_deadlineNotifier = self;
}

void CompleteDeadlineNotifier(DeadlineNotifier* self)
{
    self->desc02()->m2F(self, 2);
}

void HandleDeadlineNotifierNotification(DeadlineNotifier* self, s32 kind, void* msg)
{
    NotifyFrame fr;
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind != 0x14) return;
    if (msg != self->f2E8) return;
    GetStateWalkerCurrentKey(msg, &fr.code);
    if (fr.code != 0x263) return;
    BaseObject* dev = self->world->f1D60;
    if (dev != 0) {
        fr.note.state = 1;
        fr.note.sender = self;
        dev->desc->m1B(dev, &fr.note);
    }
    AppendQueuedCall(self->world, (void*)CompleteDeadlineNotifier, self, 0, 0);
}

void UpdateNotifierWorldDeadline(DeadlineNotifier* self)
{
    UpdateStateNotifier(self);
    if (self->state != 0) return;
    if (self->world->f2308 <= g_gameTime) self->desc02()->m2F(self, 6);
}

void SetDeadlineNotifierState(DeadlineNotifier* self, s32 mode)
{
    ListenerMessage msg;
    if (self->state == mode) return;
    if (mode == 1) {
        SetBestTimeState(&g_timerCaption, 2);
        StateListener* dev = self->listener;
        if (dev != 0) {
            msg.state = mode;
            msg.sender = self;
            dev->vtbl[31](dev, &msg);
        }
        mode = 2;
    }
    SetStateNotifierState(self, mode);
}

s32 CompareFloatsDescending(const f32* first, const f32* second)
{
    s32 result = -1;
    if (*first < *second) result = 1;
    return result;
}

// A candidate func_00148938 sorts: its squared distance from the point of view, and the object.
struct Candidate_00148938 {
    union {
        f32 dist;
        u32 bits;
    };
    StateNotifier* obj;
};

s32 CountListItems(List01* list);
void SortElements(void* base, s32 count, s32 size, void* cmp);

s32 GatherObjectsOfKind(World* self, s32 kind, s32 max, StateNotifier** out)
{
    Vec02 origin;
    Candidate_00148938* recs;
    s32 n;
    if (max == 0) {
        return 0;
    }
    PushBackMemoryMark();
    SwitchedCollider* viewer = GetActiveSwitchedCollider();
    Vec02* src;
    if (viewer != 0) {
        src = &viewer->v140;
    } else {
        src = (Vec02*)(*(u8**)g_camera + 0x40);
    }
    origin = *src;
    n = 0;
    recs = (Candidate_00148938*)AllocateBackMemory(CountListItems(&self->list1C54) * 8);
    for (StateNotifier* p = (StateNotifier*)self->list1C54.head; p != 0; p = p->next374) {
        if (p->f338 != 0 && ((Desc01*)p->desc)->id == kind) {
            Candidate_00148938* r = &recs[n++];
            r->obj = p;
            if (p->state == 2) {
                r->dist = 3.4028234663852886e+38f;
            } else {
                u128 d = Vu0::Sub(Vu0::Q(origin), Vu0::Q(p->v140));
                r->bits = Vu0::ToBits(Vu0::Dot(d, d));
            }
        }
    }
    SortElements(recs, n, 8, (void*)CompareFloatsDescending);
    if (n < max) {
        max = n;
    }
    for (s32 i = 0; i < max; i++) {
        out[i] = recs[i].obj;
    }
    PopBackMemoryMark();
    return max;
}

s32 ScatterObjectsAroundCircle(World* self, s32 a1, s32 a2, s32 n, StateNotifier** arr)
{
    StateNotifier** p;
    s32 i;
    s32 count;
    f32 ang;
    f32 step;
    PushBackMemoryMark();
    if (arr == 0) {
        arr = AllocateBackMemory(n * 4);
    }
    count = GatherObjectsOfKind(self, a1, n, arr);
    i = 0;
    step = 6.2831855f / (f32)n;
    ang = RandomFloatInRange(0.0f, 6.2831855f);
    {
        for (; i < count;) {
            StateNotifier* o = arr[i];
            u8* q = (u8*)o + 0x300;
            f32 a;
            f32 b;
            o->desc->m02(o);
            o->desc->m15(o, 0);
            o->desc02()->m1D(o, (Vec02*)a2);
            o->desc02()->m1E(o, (Mat02*)g_identityMatrix);
            o->desc02()->m20(o, (Vec02*)D_00248D30);
            o->desc02()->m21(o, (Vec02*)D_00248D30);
            o->f2E0 = (f32)i * D_00261B40;
            o->f33C = 0;
            i++;
            o->desc02()->m2F(o, 3);
            a = RandomFloatInRange(D_00261B48[0], D_00261B48[1]);
            b = RandomFloatInRange(D_00261B50[0], D_00261B50[1]);
            ComputePolarOffset(q, ang, a, b);
            ang += step;
            QueryValueListMask((World*)self->f1EC4, o->f2A8, (u8*)o + 0x140, (u8*)o + 0x88);
        }
    }
    PopBackMemoryMark();
    return count;
}

void CompleteSoundNotifiers(World* self)
{
    GameProgress* g = g_saveData;
    if (((g->f19D8 << 8) | g->f19DC) == 0x308) return;
    s32 r = GetSpareCountLimit();
    if (g->f19E4 < r) {
        if (D_0026EC58 < 2) return;
    }
    StateNotifier* p = (StateNotifier*)self->list1C54.head;
    if (p == 0) return;
    do {
        if (IsObjectOfKind(p, 0x56) != 0) {
            p->desc02()->m2F(p, 2);
        }
        p = p->next374;
    } while (p != 0);
}

void InitCountdownNotifier(CountdownNotifier* self)
{
    InitStateNotifier(self);
    f32 k = 50.0f;
    self->f34C = 45.0f;
    self->f344 = 250.0f;
    self->f348 = self->f350 = k;
    self->f358 = 0.05f;
    self->f354 = 0.5f;
    self->timeMin = 4.0f;
    self->i320 = 0;
    self->timeMax = 6.0f;
}

void CompleteCountdownNotifier(CountdownNotifier* self)
{
    self->desc02()->m2F(self, 2);
}

void HandleCountdownNotifierNotification(CountdownNotifier* self, s32 kind, void* msg)
{
    NotifyFrame fr;
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind != 0x14) return;
    if (msg != self->f2E8) return;
    GetStateWalkerCurrentKey(msg, &fr.code);
    if (fr.code != 0x263) return;
    BaseObject* dev = self->world->f1D60;
    if (dev != 0) {
        fr.note.state = 1;
        fr.note.sender = self;
        dev->desc->m1B(dev, &fr.note);
    }
    AppendQueuedCall(self->world, (void*)(void (*)(void*))CompleteCountdownNotifier, self, 0, 0);
}

void CountDownNotifierTimer(CountdownNotifier* self)
{
    UpdateStateNotifier(self);
    if (self->state != 0) return;
    if (self->f338 == 0) return;
    if (D_00270458 != 2) {
        self->timeLeft = self->timeLeft - g_frameDt;
    }
    if (self->timeLeft <= 0.0f) {
        self->desc02()->m2F(self, 6);
    }
}

void AddReserveUnitNow(void)
{
    T217D_E30* obj = &D_0026C6C8;
    obj->vt->m14(obj);
    GameProgress* g = g_saveData;
    if (g->f19E0 < 0x63) {
        g->f19E0 = g->f19E0 + 1;
        obj->rate = 250.0f;
        obj->onDone = 0;
        obj->doneArg = 0;
    } else {
        g->f19E0 = 0x63;
    }
}

void SetCountdownNotifierState(CountdownNotifier* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 0) goto zero_case;
    if (mode == 1) goto one_case;
    goto call_tail;

zero_case:
    if (self->f338 != 0) {
        self->timeLeft = RandomFloatInRange(self->timeMin, self->timeMax);
    }
    goto call_tail;

one_case:
    {
        Effect* c = CreateEffect(0x10, 0);
        if (c != 0) {
            c->p134 = self;
            c->params = (const T219C_Params*)D_00261B60;
            c->vt->m00(c, &self->v140, 1.0f, 0);
            c->p20 = self;
            c->rot50[0] = self->m110.r[0];
            c->rot50[1] = self->m110.r[1];
            c->rot50[2] = self->m110.r[2];
        } else {
            AddReserveUnitNow(self);
        }
        D_0026C6C8.vt->m14(&D_0026C6C8);
        SetFlagTableBit(g_flagTable, self->f37C);
        StartSoundEffect(0x69, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        if (self->listener != 0) {
            ListenerMessage fr;
            fr.state = 1;
            fr.sender = self;
            self->listener->vtbl[31](self->listener, &fr);
        }
        mode = 2;
    }

call_tail:
    SetStateNotifierState(self, mode);
}

void InitArmedStateNotifier(ArmedStateNotifier* self)
{
    InitStateNotifier(self);
    self->armed = 0;
}

extern f32 D_00261BE4;
s32 GatherObjectsById(void* world, s32 a, s32 b, s32 c, s32 d, PlacedObject** out);

// Pushes the objects of kind 0x19 near the notifier (within 500, their meshes hit from 200 above
// it) away by 0.75 of their velocity, the push never downward, counting the hits of the active
// switched collider up to 99, and tells the listener.
void UpdateArmedNotifier(ArmedStateNotifier* self)
{
    typedef Vu0::Vec Vec;
    Vec02 probe;
    PlacedObject* found[6];
    u8 hit[0x30];
    Vec02 push;
    s32 n;

    UpdateStateNotifier(self);
    Vu0::Q(probe) = Vu0::Add(Vec::Of(self->v140), Vec::Of(D_00261BD0)).q;
    n = GatherObjectsById(self->world, 5, 0x19, 0, 6, found);
    for (s32 i = 0; i < n; i++) {
        f32 zero = 0.0f;
        PlacedObject* o = found[i];
        Vec d = Vu0::Sub(Vec::Of(o->v140), Vec::Of(probe));
        if (250000.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
            continue;
        }
        if (CollectMeshHits(100.0f, &probe, *(void**)((u8*)o + 0x3F4), *(void**)((u8*)o + 0x3F8), 0,
                            (u8*)o + 0x3A4, 1, hit) <= 0) {
            continue;
        }
        if ((void*)o == (void*)GetActiveSwitchedCollider()) {
            s32 c = *(s32*)((u8*)o + 0x858) + 1;
            s32 v = 99;
            if (c < 99) v = c;
            *(s32*)((u8*)o + 0x858) = v;
        }
        Vec k = Vec::ScalarAtValue(D_00261BE0);
        Vu0::Q(push) = Vu0::MulX(Vec::Of(o->v150), k).q;
        push.z = zero >? push.z;
        self->desc02()->m20(self, &push);
        if (self->listener != 0) {
            ListenerMessage msg;
            msg.state = 1;
            msg.sender = self;
            self->listener->vtbl[31](self->listener, &msg);
        }
        StartSoundEffect(0x2C, 0, 0, (s32)&self->v140, 7500.0f, 2500.0f, 2.0f, D_00261BE4, 0.0f, 0, 0);
        self->desc02()->m2F(self, 2);
    }
}

