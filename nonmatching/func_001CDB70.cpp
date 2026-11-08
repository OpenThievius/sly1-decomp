// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 532/548 (97.1%), checked 2026-11-08
// NEAR: registers match; the schedule differs: retail loads the player link source (lw v0,0x2204) and forms the address of the position (move v1,sp) first after the call, ours does it after the Dot.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "globals.h"
#include "switched_collider.h"
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
struct LinkTargetHolder { s32 pad0; void* target; };
void AddColliderForce(void* target, void* slot);
void AddColliderTorque(void* target, void* slot);
void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);
struct LinkedFrame { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; BaseObject* item; };
typedef void (*LinkItemFn)(BaseObject* self, Vec02* a, f32 t, s32 b, Vec02* c, s32 d, s32 e, void* f);
s32 IsObjectAttached(BaseObject* obj);
void SetContactPairFlags(World* world, Contacts03* a, Contacts03* b, s32 set, s32 clr);
struct HeadingVector {
    f32 x;
    f32 y;
};
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, HeadingVector* d);
f32 ArctangentOfRatio(f32 a, f32 b);

struct LinkSource {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 point;            // 0x40
    u8 pad50[0xB0 - 0x50];
    f32 reach;              // 0xB0
};

struct LinkRecord {
    u8 pad00[0x80];
    PlacedObject* object;   // 0x80
};

void BuildShortestArcRotation(const Vec02* from, Vec02* to, Mat02* out);

extern const Vec02 g_unitXVector;
extern const Vec02 D_00248D30;

void ComputePlayerLinkPose(Player* self, Vec02* pos, Mat02* rotA, Mat02* rotB)
{
    Vec02 a;
    Vec02 b;
    Vec02 gap;
    Mat02 arc;
    Mat02 axis;
    Vec02 k;
    LinkSource* source = (LinkSource*)self->f2204;
    PlacedObject* held = ((LinkRecord*)((PlacedObject*)self->f61C)->f224)->object;
    TransformPointBetweenFrames(source->frame, self, &source->point, &a);
    TransformPointBetweenFrames(0, self, &held->v140, &b);
    Vu0::Q(gap) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
    BuildShortestArcRotation(&g_unitXVector, &gap, &arc);
    u128 here = Vu0::Q(a);
    u128 reach = Vu0::FromFloatAt(((LinkSource*)self->f2204)->reach);
    Vu0::Q(k) = reach;
    Vu0::Q(a) = Vu0::MulAddX(here, Vu0::NormalizeOr(Vu0::Q(gap), Vu0::Q(D_00248D30)), reach);
    BuildAxisAngleMatrix(&g_unitXVector, D_00274DD4, &axis);
    MulRotation(rotA, arc, axis);
    BuildAxisAngleMatrix(&g_unitXVector, D_00274DD8[0], rotB);
    u128 turned = Vu0::Rotate(*rotB, Vu0::Q(((PlacedObject*)self->f23D4)->pos));
    u128 sum = Vu0::Add(Vu0::Q((*(PlacedObject**)((u8*)self + 0x23D0))->pos), turned);
    u128 moved = Vu0::Rotate(*rotA, sum);
    PlacedObject* base = (PlacedObject*)self->f61C;
    u128 total = Vu0::Add(Vu0::Q(base->pos), moved);
    Vu0::Q(k) = total;
    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(base->pos), Vu0::Sub(Vu0::Q(a), total));
}
