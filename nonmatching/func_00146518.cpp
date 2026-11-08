// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 2036/2040 (99.8%), checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "state_notifier.h"
#include "switched_collider.h"
#include "camera.h"
#include "shapes.h"
#include "list_iter.h"
// NEAR (2026-11-08, night-large7): two instructions differ, the size and frame retail's: in
// state 5 retail loads rows 1 and 2 of the matrix through the pointer (lqc2 32(s2), 16(s2)) where
// CSE here folds them into 0xF0(s3) and 0xE0(s3) (row 0 is 0xD0(s3) in both). Found on the way:
// the object's matrix set through the object's pointer (SetRotationProduct: the rows stored at
// 0xD0(s3)); state 5's product with b's rows loaded as values in the order 0, 2, 1; a Vec value
// stored as a struct (*(Vu0::Vec*)&self->pos) lets the float global's load pass the store; the
// loop over the three angles indexing two pointers (cur[i], vel[i]) gives retail's givs; the
// default state stores the motion into v300 and v2F0 and copies them; the list walk reads its
// head through the frame. Needs StateNotifier::v310, f35C, v360, f370.

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
extern u8 g_unitZVector[];
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
    u128 b0 = Vu0::Q(b.r[0]);
    u128 b2 = Vu0::Q(b.r[2]);
    u128 b1 = Vu0::Q(b.r[1]);
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, b0);
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, b1);
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, b2);
    o->rot = r;
}

void func_00146518(StateNotifier* self, f32 dt, s32 quiet)
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
        BuildBasisFromXAndZHint(&v, (Vec02*)g_unitZVector, &face);
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
