// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1588/1604 (99.0%), checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "camera.h"
#include "game_clock.h"
#include "globals.h"
// NEAR (night-low1, 2026-11-08): same size now, four words off. The normalisation written out on
// one variable (u128 v = Rotate(...); v = fallback or DivX(v, len); Set(n, v)) with the fallback
// read first into its own value gives retail's lq v0 and qmtc2 into the rotated vector's vf4 in
// the fallback's delay slot; rec.kind stored before rec.block.f44 puts the f44 store in bc1t's
// slot. Still differs: the cubic's first coefficient load (lwc1 c[3]) comes before abs.s of the
// view term and c[0]'s load before the first mul.s (retail: abs.s first, c[0] after the
// mul). Tried: fabs in the call, a pointer to the cubic, Eval as statements or with c[0] in a
// local, permute.py on the fallback's line: no change.
// Before (2026-11-08, night-large4): the part loop of slot 0x26's draw, the two view tests, the fade
// calls, the facing cubic, the state's ease and the request's copies are retail's code (registers
// included: the transform's address hoisted into s6, rows 1 and 2 through it from an in-block
// pointer, the state through a chained assignment). Left: NormalizeOr's fallback. Retail loads
// D_00248D30 with lq into v0 and moves it to the result's register (vf4, the rotated vector's) with
// qmtc2 in the fallback's branch delay slot; here it is loaded with lqc2 straight into the result
// (vf3), which drops retail's `b` and shifts every later word by one. Same with u128 or Vec forms,
// a named rotation, the test written out with ToFloat, or Q() for the store. Also retail stores
// rec.kind before rec.block.f44 (the f44 store in bc1t's delay slot).
struct ScaledTransform {
    Quad16 q[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4c;
};
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
extern void* FillMemory(void*, s32, s32);
extern f32 ApproachValueWithRamp(void*, s32, f32, f32, f32);
extern u8 g_unitRange[];
extern f32 g_fadeRampProfile[4];

// A part of a placed object's model (drawParts, 0x70 bytes each): what func_00126270 reads of it.
struct FadeCubic {
    f32 c[4];
    f32 Eval(f32 t) const { return c[0] + t * (c[1] + t * (c[2] + t * c[3])); }
};
struct ModelPartFade {
    Vec02 axis;             // 0x00: the part's facing, turned by the object's transform
    FadeCubic cubic;        // 0x10: its weight by how squarely the camera sees it
};
struct ModelPartHook;
struct ModelPartHookVt {
    u8 pad00[0x10];
    void (*m04)(ModelPartHook* self, PlacedObject* obj, void* req); // 0x10
};
struct ModelPartHook {
    const ModelPartHookVt* vt;
};
struct ModelPart {
    Vec02 pos;              // 0x00: the part's point in the object
    f32 radius;             // 0x10
    s32 kind;               // 0x14
    u8 pad18[0x1C - 0x18];
    f32 nearFade;           // 0x1C
    f32 farFade;            // 0x20
    f32 dist;               // 0x24: FLT_MAX for the distance to the camera
    u8 pad28[0x30 - 0x28];
    ModelPartFade* fade;    // 0x30
    void* f34;              // 0x34
    ModelPartHook* hook;    // 0x38
    u8 pad3C[0x60 - 0x3C];
    s32 f60;                // 0x60
    u8 pad64[0x68 - 0x64];
    void* f68;              // 0x68: a matrix the transform is multiplied by
    u8 pad6C[0x70 - 0x6C];
};
// A part's state (partStates, 0x28 bytes each).
struct ModelPartState {
    u32 mask;               // 0x00: the camera's f21C bits it is drawn under
    u8 pad04[0x10 - 0x04];
    f32 fade;               // 0x10: eased to 1, or 0.5 until `until`
    f32 until;              // 0x14
    u8 pad18[0x28 - 0x18];
};
// The 0x80-byte request func_00126270 queues for each part it draws (DrawModelPart).
struct __attribute__((aligned(16))) ModelPartRequest {
    void* fn;               // 0x00
    f32 dist;               // 0x04
    s32 kind;               // 0x08
    u8 pad0C[0x10 - 0x0C];
    ScaledTransform block;  // 0x10
    Vec02 pos;              // 0x60
    PlacedObject* obj;      // 0x70
    void* sub;              // 0x74
    ModelPart* part;        // 0x78
    ModelPartState* state;  // 0x7C
};

void TransformByMatrixWithW(void* m, void* v, void* out, f32 w);
s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
f32 ClampToRange(void* span, f32 x);
void MultiplyMatrices(Mat4A* out, void* a, void* b);
void QueueDeferredRequest(void* r);
void ApplyPoseSourceIndexedValue(void* src, s32 i);
void DrawModelPart(void* r);
void func_00126DE8(PlacedObject* self, Camera* cam, void* p, Vec02* pos, ScaledTransform* m);
#include "game_clock.h"
extern Camera* g_camera;

void func_00126270(PlacedObject* self, Camera* cam, Quad16* src)
{
    ModelPartRequest rec;
    ModelPartState* state = 0;
    s32 drawn = 0;
    FillMemory(&rec, 0, 0x80);
    BuildPlacedObjectTransform(self, src, &rec.block);
    rec.fn = (void*)DrawModelPart;
    rec.obj = self;
    rec.sub = self->sub22C;
    f32 alpha = rec.block.f40;
    f32 glow = rec.block.f44;
    for (s32 i = 0; i < self->drawPartCount; i++) {
        ModelPart* part = &((ModelPart*)self->drawParts)[i];
        rec.part = part;
        if (self->partStates != 0) {
            state = rec.state = &((ModelPartState*)self->partStates)[i];
            if (self->bits26 == 1 && (state->mask & cam->f21C) != (u32)cam->f21C) {
                continue;
            }
        }
        if (self->flags & 0x200000000ULL) {
            rec.pos = part->pos;
        } else {
            TransformByMatrixWithW(&rec.block, part, &rec.pos, 1.0f);
        }
        u128 d = Vu0::Sub(Vu0::Q(rec.pos), Vu0::Q(cam->f40));
        if (self->bits28 == 1) {
            Vec02 r;
            f32 fade;
            f32 radius = part->radius;
            u128 ones = Vu0::Ones();
            Vu0::Q(r) = Vu0::FromFloat(radius);
            if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Q(r)) ^ 0xF0) != 0) {
                continue;
            }
            if (ComputeCameraDistanceFade(cam, d, &fade, radius, part->nearFade) == 0) {
                continue;
            }
            rec.block.f40 = alpha * fade;
            if (part->f60 != 0) {
                if (part->farFade < part->nearFade) {
                    if (ComputeCameraDistanceFade(cam, d, &fade, part->radius, part->farFade) == 0) {
                        rec.block.f44 = 0.0f;
                    } else {
                        rec.block.f44 = glow * fade;
                    }
                }
            }
        } else {
            if (src == 0) {
                Vec02 r;
                u128 ones = Vu0::Ones();
                Vu0::Q(r) = Vu0::FromFloatAt(part->radius);
                if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Q(r)) ^ 0xF0) != 0) {
                    continue;
                }
            }
            rec.block.f40 = alpha;
            rec.block.f44 = glow;
        }
        if (part->fade != 0) {
            Vec02 n;
            ScaledTransform* m = &rec.block;
            u128 fb = Vu0::Q(D_00248D30);
            u128 v = Vu0::Rotate(*m, Vu0::Q(part->fade->axis));
            u128 len = Vu0::Length(v);
            if (Vu0::ToFloatMoved(len) < 0.0001f) {
                v = fb;
            } else {
                v = Vu0::DivX(v, len);
            }
            Vu0::Set(n, v);
            f32 t = __builtin_fabsf(Vu0::ToFloat(Vu0::Dot(Vu0::Q(n), Vu0::Q(g_camera->f80))));
            rec.block.f40 = rec.block.f40 * ClampToRange(g_unitRange, part->fade->cubic.Eval(t));
        }
        if (state != 0) {
            f32 goal = 1.0f;
            if (g_gameClock.elapsed < state->until) {
                goal = 0.5f;
            }
            if (goal != state->fade) {
                state->fade = ApproachValueWithRamp(g_fadeRampProfile, 0, state->fade, goal, g_gameClock.dt);
            }
            rec.block.f40 = rec.block.f40 * state->fade;
        }
        if (rec.block.f40 <= 0.0f) {
            continue;
        }
        drawn = 1;
        if (part->dist != 3.402823466e+38f) {
            rec.dist = part->dist;
        } else {
            rec.dist = Vu0::ToFloat(Vu0::Dot(d, d));
        }
        rec.kind = part->kind;
        rec.block.f44 = rec.block.f44 * rec.block.f40;
        s32 kind = rec.kind;
        if (rec.block.f40 != 1.0f) {
            switch (kind) {
            case 3:
            case 4:
            case 7:
            case 8:
                rec.kind = 0xD;
                break;
            case 5:
            case 9:
                rec.kind = 0xE;
                break;
            }
        }
        ModelPartHook* hook = part->hook;
        if (hook != 0 && hook->vt->m04 != 0) {
            hook->vt->m04(hook, self, &rec);
        }
        if (part->f68 != 0 || part->f34 != 0) {
            Mat4A saved = *(Mat4A*)&rec.block;
            if (part->f68 != 0) {
                Mat4A t;
                MultiplyMatrices(&t, &rec.block, part->f68);
                *(Mat4A*)&rec.block = t;
            }
            if (part->f34 != 0) {
                func_00126DE8(self, cam, part->f34, &rec.pos, &rec.block);
            }
            QueueDeferredRequest(&rec);
            *(Mat4A*)&rec.block = saved;
        } else {
            QueueDeferredRequest(&rec);
        }
    }
    if (drawn != 0) {
        self->desc02()->m27(self, src);
        if (self->f1F8 != 0) {
            for (s32 j = 0; j < self->f26C; j++) {
                if (self->f1F8[j] != 0) {
                    ApplyPoseSourceIndexedValue(self->f1F8[j], j);
                } else {
                    self->f270[j] = (*(f32**)((u8*)self + 0x274))[j];
                }
            }
        }
    }
}
