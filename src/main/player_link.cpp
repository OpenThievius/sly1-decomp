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
float D_00274DD8 = -1.70000005f;
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

// A row of the link's system: the response of the two objects to a unit impulse along one axis,
// in direction (a) and in rotation (b).
struct LinkRow {
    Vec02 a;
    Vec02 b;
};

// The right-hand side of the link's system, read as components by index.
struct __attribute__((aligned(16))) LinkVector {
    f32 v[4];
};

void ConstrainVectorByParentAnchor(void* self, void* anchor, Vec02* in, Vec02* out, s32 mode);
void ApplyColliderInverseInertia(void* self, Vec02* in, Vec02* out);
void ComputeColliderPointVelocity(void* self, void* data, LinkRow* row, Vec02* out);
void FactorSymmetricMatrix(s32 n, f32* a, f32* l);
void SolveFactoredSystem(s32 n, f32* a, f32* b, f32* c);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);

void SolvePlayerLinkSystem(PlacedObject* a, PlacedObject* b, Vec02* point, const LinkVector* target, LinkRow* out)
{
    PlacedObject* objs[2];
    Vec02 pts[2];
    Vec02 axis;
    Vec02 cross;
    Vec02 scaled;
    Vec02 torque;
    LinkRow rows[2][3];
    Vec02 vel[2];
    Vec02 diff[3];
    f32 m[3][3];
    f32 factor[3][3];
    f32 rhs[3];
    f32 sol[3];
    s32 i;
    s32 j;
    s32 flipped = 1;    // the object whose impulse is turned the other way

    objs[0] = a;
    objs[1] = b;
    pts[0] = a->v140;
    pts[1] = *point;
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 2; i++) {
            PlacedObject* o = objs[i];
            axis = g_identityMatrix.r[j];
            if (i == flipped) {
                Vu0::Q(axis) = Vu0::MulX(Vu0::Vec::Of(axis), Vu0::Vec::Scalar(-1.0f)).q;
            }
            Vu0::Vec p = Vu0::Vec::Of(pts[i]);
            Vu0::Vec c = Vu0::Vec::Of(o->v140);
            Vu0::Vec arm = Vu0::Sub(p, c);
            Vu0::Set(cross, Vu0::Cross(arm, Vu0::Vec::Of(axis)).q);
            Vu0::Vec mass = Vu0::Vec::ScalarAtValue(*(f32*)((u8*)o + 0x368));
            Vu0::Set(scaled, Vu0::DivX(Vu0::Vec::Of(axis), mass).q);
            ConstrainVectorByParentAnchor(o, (u8*)o + 0x440, &scaled, &rows[i][j].a, 0);
            ApplyColliderInverseInertia(o, &cross, &torque);
            ConstrainVectorByParentAnchor(o, (u8*)o + 0x460, &torque, &rows[i][j].b, 0);
            ComputeColliderPointVelocity(o, point, &rows[i][j], &vel[i]);
        }
        Vu0::Vec v0 = Vu0::Vec::Of(vel[0]);
        Vu0::Vec v1 = Vu0::Vec::Of(vel[1]);
        Vu0::Q(diff[j]) = Vu0::Sub(v0, v1).q;
    }
    for (j = 0; j < 3; j++) {
        f32* row = m[j];
        for (s32 k = 0; k < 3; k++) {
            Vu0::Vec e = Vu0::Vec::Of(g_identityMatrix.r[k]);
            Vu0::Vec d = Vu0::Vec::Of(diff[j]);
            Vu0::StoreX(row[k], Vu0::Dot(e, d).q);
        }
        rhs[j] = target->v[j];
    }
    FactorSymmetricMatrix(3, &m[0][0], &factor[0][0]);
    SolveFactoredSystem(3, &factor[0][0], rhs, sol);
    for (i = 0; i < 2; i++) {
        Vu0::Vec s0 = Vu0::Vec::ScalarAtValue(sol[0]);
        Vu0::Vec a0 = Vu0::Vec::Of(rows[i][0].a);
        Vu0::Vec s1 = Vu0::Vec::ScalarAtValue(sol[1]);
        Vu0::Vec a1 = Vu0::Vec::Of(rows[i][1].a);
        Vu0::Vec s2 = Vu0::Vec::ScalarAtValue(sol[2]);
        Vu0::Vec a2 = Vu0::Vec::Of(rows[i][2].a);
        Vu0::Q(out[i].a) = Vu0::MulXSum3(a0, s0, a1, s1, a2, s2).q;
        Vu0::Vec t0 = Vu0::Vec::ScalarAtValue(sol[0]);
        Vu0::Vec b0 = Vu0::Vec::Of(rows[i][0].b);
        Vu0::Vec t1 = Vu0::Vec::ScalarAtValue(sol[1]);
        Vu0::Vec b1 = Vu0::Vec::Of(rows[i][1].b);
        Vu0::Vec t2 = Vu0::Vec::ScalarAtValue(sol[2]);
        Vu0::Vec b2 = Vu0::Vec::Of(rows[i][2].b);
        Vu0::Q(out[i].b) = Vu0::MulXSum3(b0, t0, b1, t1, b2, t2).q;
        TransformDirectionBetweenFrames(0, *(void**)((u8*)objs[i] + 0x18), &out[i].a, &out[i].a);
        TransformDirectionBetweenFrames(0, *(void**)((u8*)objs[i] + 0x18), &out[i].b, &out[i].b);
    }
}

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

void GetLinkedObjectHeading(Player* self, f32* out);
f32 WrapAngle(f32 a);
void ComputeCameraRelativeStickHeading(Camera* self, void* pad, s32 mode, f32* out);
f32 ArctangentOfRatio(f32 y, f32 x);
void SetPlayerState(Player* self, s32 a, s32 b);
void PlacePlayerOnLinkedObject(Player* self);
void ClearRootTries(void* self);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, f32* p, s32 zero);
f32 ClampToMagnitude(f32 a, f32 b);
extern f32 g_gameTime;
extern f32 g_gameClock[];

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

struct LinkBlend_1CD0C8 { u8 pad0[0x34]; f32 f34; };
struct LinkRoot_1CD0C8 { s32 pad0; void* root; };
struct LinkMessage_1CD0C8 { u8 pad0[0x14]; f32 f14; f32 f18; };

void ControlPlayerOnLinkedObject(Player* self, void* pad)
{
    Vec02 pos;
    Vec02 dir;
    Vec02 local;
    Mat02 m;
    f32 stick;
    s32 toward = 0;
    s32 away = 0;
    GetLinkedObjectHeading(self, &self->f638);
    if (self->f22A8 != 0) {
        self->f638 = WrapAngle(self->f638 + 3.14159274f);
    }
    ComputeCameraRelativeStickHeading(g_camera, pad, 0, &stick);
    f32 diff = WrapAngle(stick - self->f638);
    if (0.3f < self->f634) {
        f32 ad = __builtin_fabsf(diff);
        if (ad < 1.04719758f) {
            toward = 1;
            self->f22A0 = g_gameTime;
        } else if (2.09439516f < ad) {
            away = 1;
            self->f22A0 = g_gameTime;
        }
    } else {
        self->f22A4 = -1;
    }
    GetObjectWorldPosition((void*)self->f2204, &pos);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140)), Vu0::Q(g_unitZVector)));
    BuildAxisAngleMatrix(&g_unitZVector, self->f638, &m);
    Vu0::Q(local) = Vu0::RotateTransposed(m, Vu0::Q(dir));
    f32 angle = WrapAngle(ArctangentOfRatio(local.z, local.x) - 1.57079637f);
    s32 state = self->f2228;
    switch (state) {
    case 0x32:
        if (away) {
            state = 0x34;
        } else if (toward) {
            if (D_00274D94 < g_gameTime - self->f222C) {
                self->f22A4 = state;
                state = 0x33;
            }
        } else if (D_00274D9C < g_gameTime - self->f22A0) {
            state = 0x33;
        }
        break;
    case 0x34:
        if (toward) {
            state = 0x32;
        } else if (away) {
            if (D_00274D98 < g_gameTime - self->f222C) {
                self->f22A4 = state;
                state = 0x33;
            }
        } else if (D_00274D9C < g_gameTime - self->f22A0) {
            state = 0x33;
        }
        break;
    case 0x33:
        if (toward && self->f22A4 != 0x32) {
            self->f22A4 = -1;
            state = 0x32;
        } else if (away && self->f22A4 != 0x34) {
            self->f22A4 = -1;
            state = 0x34;
        } else if (__builtin_fabsf(angle) < D_00274DA0) {
            s32 slow = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150))) < D_00274DA8;
            if (slow) {
                state = 0x35;
            }
        }
        break;
    case 0x35:
        if (toward && self->f22A4 != 0x32) {
            self->f22A4 = -1;
            state = 0x32;
        } else if (away && self->f22A4 != 0x34) {
            self->f22A4 = -1;
            state = 0x34;
        } else if (__builtin_fabsf(angle) > D_00274DA4) {
            s32 fast = D_00274DAC < Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150)));
            if (fast) {
                state = 0x33;
            }
        }
        break;
    }
    SetPlayerState(self, 3, state);
    PlacePlayerOnLinkedObject(self);
    if (self->f22AC != 0) {
        ClearRootTries(((LinkRoot_1CD0C8*)self->f22AC)->root);
    }
    f32 w0;
    f32 w1;
    if (self->f2228 == 0x35) {
        return;
    }
    switch (self->f2228) {
    case 0x32:
        w0 = w1 = 1.0f;
        break;
    case 0x34:
        w0 = 1.0f;
        w1 = 0.0f;
        break;
    case 0x33:
        w0 = 0.0f;
        w1 = (0.5f < self->f2388) ? 1.0f : 0.0f;
        break;
    }
    self->f238C = ApproachValueWithRamp(self->f238C, w0, g_gameClock[2], D_00274DB0, 0);
    f32 b = ApproachValueWithRamp(self->f2388, w1, g_gameClock[2], D_00274DC0, 0);
    self->f2388 = b;
    f32 a = self->f238C;
    self->f2360 = a * b;
    self->f236C = a * (1.0f - b);
    self->f2378 = 1.0f - a;
    SetBlendItemWeights(self->f2384, 0xC, 3, &self->f2360);
    f32 c = ClampBetween(angle / D_00274DCC, -1.0f, 1.0f);
    ((LinkMessage_1CD0C8*)self->watched2230)->f18 = ClampToMagnitude((((LinkBlend_1CD0C8*)self->f2384)->f34 * (c + 1.0f) * 0.5f - ((LinkMessage_1CD0C8*)self->watched2230)->f14) / g_gameClock[2], D_00274DD0);
}

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

void BuildBasisFromXAndZHint(Vec02* x, const Vec02* z, Mat02* out);
s32 CreatePooledContact(f32 f, void* self, void* other, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

// Adds the contacts of the player with the object node for the axes of flags (bits 1 2 4: always,
// bits 8 0x10 0x20: when the offset along that axis is under 0.0001), in the frame of axis.
void AddPlayerObjectContacts(Player* self, s32 flags, BaseObject* node, Vec02* origin, Vec02* axis, Vec02* offset)
{
    Vec02 d;
    Mat02 m;
    if (IsObjectAttached(node) == 0) {
        SetPlayerState(self, 2, 2);
        return;
    }
    s32 each = flags & 2;
    s32 first = flags & 1;
    s32 third = flags & 4;
    BaseObject* n = node;
    while (n != 0 && (n->desc->flags & 2) == 0) {
        n = n->parent;
    }
    Contact03** last;
    Contact03** head;
    if (n != 0) {
        ContactRow03* row = self->contacts->head;
        void* want = ((PlacedObject*)n)->root;
        while (row != 0 && (void*)row->other != want) {
            row = row->next;
        }
        head = (Contact03**)row;
        last = row->link;
    } else {
        last = &self->contacts4B4;
        head = last;
    }
    if (axis != 0) {
        BuildBasisFromXAndZHint(axis, &g_unitZVector, &m);
    } else {
        m = g_identityMatrix;
    }
    Vu0::Q(d) = Vu0::Sub(Vu0::Add(Vu0::Q(*offset), Vu0::Q(*(Vec02*)((u8*)self + 0x2400))), Vu0::Q(*origin));
    Vu0::Q(d) = Vu0::RotateTransposed(m, Vu0::Q(d));
    if (first != 0 || ((flags & 8) != 0 && d.x < 0.0001f)) {
        CreatePooledContact(d.x, self, n, offset, &m.r[0], first != 0 ? 11 : 10, 0, 0, head);
    }
    if (each != 0 || ((flags & 0x10) != 0 && d.y < 0.0001f)) {
        CreatePooledContact(d.y, self, n, offset, &m.r[1], each != 0 ? 11 : 10, 0, 0, head);
    }
    if (third != 0 || ((flags & 0x20) != 0 && d.z < 0.0001f)) {
        CreatePooledContact(d.z, self, n, offset, &m.r[2], third != 0 ? 11 : 10, third != 0 ? 0 : *(s32*)((u8*)self + 0x6D4), 0, head);
    }
    *last = *head;
}

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
    BuildAxisAngleMatrix(&g_unitXVector, D_00274DD8, rotB);
    u128 turned = Vu0::Rotate(*rotB, Vu0::Q(((PlacedObject*)self->f23D4)->pos));
    u128 sum = Vu0::Add(Vu0::Q((*(PlacedObject**)((u8*)self + 0x23D0))->pos), turned);
    u128 moved = Vu0::Rotate(*rotA, sum);
    PlacedObject* base = (PlacedObject*)self->f61C;
    u128 total = Vu0::Add(Vu0::Q(base->pos), moved);
    Vu0::Q(k) = total;
    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(base->pos), Vu0::Sub(Vu0::Q(a), total));
}

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
    ApproachRotationWithRamp(&v->rotA, &g_identityMatrix, D_00274DF0, &v->rotA, 0, g_gameClock[2]);
    ApproachRotationWithRamp(&v->rotB, &g_identityMatrix, D_00274DF0, &v->rotB, 0, g_gameClock[2]);
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
