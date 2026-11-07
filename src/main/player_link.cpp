// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "globals.h"
#include "switched_collider.h"

// The file's .data, in retail's order: the constants of its assembly.
float D_00274D40 = -0.25f;
float D_00274D44 = -2.5f;
float D_00274D48 = -1.0f;
float D_00274D4C = 0.25f;
float D_00274D50[4] = {5.0f, 0.0f, 0.0f, 0.0f};
float D_00274D60[4] = {0.5f, -0.00999999978f, 0.0f, 0.0f};
float D_00274D70[4] = {1000.0f, 0.0f, 0.25f, 5000.0f};
float D_00274D80 = 75.0f;
float D_00274D84 = 230.0f;
float D_00274D88[3] = {15.0f, 0.0f, 0.100000001f};
float D_00274D94 = 1.39999998f;
float D_00274D98 = 1.39999998f;
float D_00274D9C = 0.25f;
float D_00274DA0 = 0.100000001f;
float D_00274DA4 = 0.400000006f;
float D_00274DA8 = 80.0f;
float D_00274DAC = 120.0f;
float D_00274DB0[4] = {1.0f, 0.0f, 0.100000001f, 0.0f};
float D_00274DC0[3] = {4.0f, 0.0f, 0.100000001f};
float D_00274DCC = 1.70000005f;
float D_00274DD0 = 3.0f;
float D_00274DD4 = 3.5f;
float D_00274DD8[2] = {-1.70000005f, 0.0f};
float D_00274DE0[3] = {3000.0f, 1000.0f, 0.150000006f};
float D_00274DF0[3] = {30.0f, 10.0f, 0.150000006f};

void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);

struct ThreeBlendRecord { s32 f0; u8 pad0[0xC - 0x4]; s32 fC; u8 pad1[0x18 - 0x10]; f32 f18; };

void CreateThreeEntryBlend(void* a0, ThreeBlendRecord* a1, void** a2)
{
    void* tmp;
    a1->f0 = 0;
    a1->fC = 0;
    a1->f18 = 1.0f;
    BuildCombinedBlendAnimation(a0, 12, 3, a1, 0, 0, 0, &tmp);
    SetBlendItemWeights(tmp, 12, 3, a1);
    if (a2 != 0) {
        *a2 = tmp;
    }
}

INCLUDE_ASM(func_001CC490);

INCLUDE_ASM(func_001CC818);

// The product a b of two rotations: b's rows each rotated by a.
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
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
    *out = r;
}

extern f32 g_frameDt[];
void AddColliderForce(void* target, void* slot);
s32 GetObjectWorldPosition(void* self, Vec02* out);
void BuildShortestArcRotation(const Vec02* from, Vec02* to, Mat02* out);
void BuildAxisAngleMatrix(const Vec02* axis, f32 angle, Mat02* out);
void TurnColliderTowardRotation(void* self, Mat02* rot, void* data, f32 scale);

void TurnPlayerTowardLinkedObject(Player* self)
{
    Vec02 pos;
    Vec02 d;
    Mat02 a;
    Mat02 b;
    Mat02 r;
    AddColliderForce(self, (u8*)self + 0x22B0);
    GetObjectWorldPosition((void*)self->f2204, &pos);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(*(Vec02*)((u8*)self + 0x140)));
    BuildShortestArcRotation(&g_unitZVector, &d, &a);
    BuildAxisAngleMatrix(&g_unitZVector, self->f638, &b);
    MulRotation(&r, a, b);
    TurnColliderTowardRotation(self, &r, D_00274D88, g_frameDt[0]);
}

struct LinkTargetHolder { s32 pad0; void* target; };
void AddColliderForce(void* target, void* slot);
void AddColliderTorque(void* target, void* slot);

void SyncPlayerTarget(Player* self)
{
    AddColliderForce(((LinkTargetHolder*)self->f22AC)->target, (u8*)self + 0x22D0);
    AddColliderTorque(((LinkTargetHolder*)self->f22AC)->target, (u8*)self + 0x22E0);
}

INCLUDE_ASM(func_001CD0C8);

void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);

struct LinkedFrame { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; BaseObject* item; };
typedef void (*LinkItemFn)(BaseObject* self, Vec02* a, f32 t, s32 b, Vec02* c, s32 d, s32 e, void* f);

// Lets go of a linked object that has got too far: the first beyond 50 units, the second, after
// asking its item, beyond 50 units squared.
void ReleaseFarPlayerLinks(Player* self)
{
    Vec02 pos;
    Vec02 q;
    u8* p = (u8*)self;
    LinkedFrame* a = *(LinkedFrame**)(p + 0x2210);
    if (a != 0) {
        TransformPointBetweenFrames(a->frame, 0, (u8*)a + 0x40, &pos);
        if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*(Vec02*)(*(u8**)(p + 0x23D4) + 0x140)), Vu0::Q(pos)))) > 50.0f) {
            *(s32*)(p + 0x2210) = 0;
            self->f4B8 = 0;
        }
    } else {
        if (*(LinkedFrame**)(p + 0x2214) != 0) {
            TransformPointBetweenFrames(0, (*(LinkedFrame**)(p + 0x2214))->frame, *(u8**)(p + 0x23D4) + 0x140, &pos);
            LinkItemFn fn = (LinkItemFn)((void**)(*(LinkedFrame**)(p + 0x2214))->item->desc)[12];
            if (fn != 0) {
                fn((*(LinkedFrame**)(p + 0x2214))->item, &pos, *(f32*)(p + 0x2218), 0, &q, 0, 0, p + 0x2218);
            }
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(q), Vu0::Q(q))) > 2500.0f) {
                *(s32*)(p + 0x2214) = 0;
            }
        }
    }
}

s32 IsObjectAttached(BaseObject* obj);
void SetContactPairFlags(World* world, Contacts03* a, Contacts03* b, s32 set, s32 clr);

// Walks up the parents to the first object whose class has flag bit 2.
void SetFlaggedLinkContactMask(Collider* self, BaseObject* node, s32 flag)
{
    BaseObject* n = node;
    while (n != 0) {
        if ((n->desc->flags & 2) != 0) {
            break;
        }
        n = n->parent;
    }
    if (n != 0) {
        if (IsObjectAttached(n) != 0) {
            SetContactPairFlags(self->world, self->contacts,
                                ((Collider*)((PlacedObject*)n)->root)->contacts,
                                flag != 0 ? 0x40 : 0, flag != 0 ? 0 : 0x40);
        }
    }
    self->f4B8 = 0;
}

INCLUDE_ASM(func_001CD870);

struct HeadingVector {
    f32 x;
    f32 y;
};

void TransformDirectionBetweenFrames(void* a, s32 b, void* c, HeadingVector* d);
f32 ArctangentOfRatio(f32 a, f32 b);

void GetLinkedObjectHeading(u8* a0, f32* a1)
{
    HeadingVector v;
    void* owner = *(void**)(a0 + 0x2204);
    TransformDirectionBetweenFrames(*(void**)((u8*)owner + 0x18), 0, (u8*)owner + 0x50, &v);
    *a1 = ArctangentOfRatio(v.y, v.x);
}

INCLUDE_ASM(func_001CDB70);

typedef u64 Quad128 __attribute__((mode(TI)));
Quad128 ApproachPointWithRamp(Quad128 cur, Quad128 target, const f32* params, s32 flag, f32 dt);
void ApproachRotationWithRamp(Mat02* cur, const Mat02* target, const f32* params, Mat02* out, s32 flag, f32 dt);
void ComputePlayerLinkPose(Player* self, Vec02* pos, Mat02* rotA, Mat02* rotB);
void ApplyPoseSource(void* obj, s32 flag);
extern f32 g_gameClock[];

struct LinkPoseTarget {
    u8 pad00[0x20];
    Vec02 pos;              // 0x20
    u8 pad30[0x40 - 0x30];
    Mat02 rot;              // 0x40
};

struct LinkPoseView {
    u8 pad00[0x22F0];
    Vec02 offset;           // 0x22F0
    Mat02 rotA;             // 0x2300
    Mat02 rotB;             // 0x2330
};

static inline void MulRotationInto(LinkPoseTarget* obj, const Mat02& a, const Mat02& b)
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
    obj->rot = r;
}

void UpdatePlayerLinkPose(Player* self)
{
    Vec02 pos;
    Mat02 a;
    Mat02 b;
    LinkPoseView* v = (LinkPoseView*)self;
    ComputePlayerLinkPose(self, &pos, &a, &b);
    *(Quad128*)&v->offset = ApproachPointWithRamp(*(Quad128*)&v->offset, *(const Quad128*)&D_00248D30, D_00274DE0, 0, g_gameClock[2]);
    ApproachRotationWithRamp(&v->rotA, &D_002483D0, D_00274DF0, &v->rotA, 0, g_gameClock[2]);
    ApproachRotationWithRamp(&v->rotB, &D_002483D0, D_00274DF0, &v->rotB, 0, g_gameClock[2]);
    Vu0::Q((*(LinkPoseTarget**)((u8*)self + 0x251C))->pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(v->offset));
    MulRotationInto(*(LinkPoseTarget**)((u8*)self + 0x251C), v->rotA, a);
    MulRotationInto(*(LinkPoseTarget**)((u8*)self + 0x2520), v->rotB, b);
    ApplyPoseSource(*(void**)((u8*)self + 0x251C), 1);
    ApplyPoseSource(*(void**)((u8*)self + 0x2520), 1);
}

void GetPlacedObjectRotationAt(Player* self, f32 t, void* out, void* extra);
void GetTurningColliderPose(Player* self, f32 t, void* out, void* extra);

void GetPlayerPose(Player* self, f32 t, void* out, void* extra)
{
    if (self->f2220 == 3) {
        GetPlacedObjectRotationAt(self, t, out, extra);
    } else {
        GetTurningColliderPose(self, t, out, extra);
    }
}
