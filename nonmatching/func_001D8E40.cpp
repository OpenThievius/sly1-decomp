// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1074/1196 (89.8%), checked 2026-11-08
// NEAR (2026-11-08, worker night-large2): the lap timer, the four wheels' two emitters, the
// random tilt and the product (MulRotation), the spawn record and the leftover counts are
// retail's; 49 lines differ. Retail hoists %hi(D_00275510) into fp and forms &m (sp+0x80) at
// each call, ours hoists &m into s8 (loop.c's choice: our loop has 232 insns at the loop pass);
// retail stores the wheel offset's FromFloats from its GPR (sq to 0x60 and to the slot) and
// reads it back with lqc2, ours moves it to VU0 first and stores it with sqc2; and the
// velocity's Rotate takes vf2 where ours takes vf1. Found: the tilt's switch on (s32)i, whose
// i < 2 test retail's later `front` reuses, and the velocity call's fourth argument &basis.
// In the context of its file, src/main/file_1D62E0.cpp (which includes mul_rotation.h for it).
#include "common.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "switched_collider.h"
#include "value_range.h"
#include "world.h"
#include "globals.h"

struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

extern f32 g_gameTime;
extern float D_002751D8;
extern float D_00275240[4];
extern f32 D_00275500[2];
extern f32 D_00275508[2];
extern f32 D_00275510[2];
extern World* g_currentWorld;
f32 RandomFloatInRange(f32 a, f32 b);
void BuildAxisAngleMatrix(const Vec02* t, void* out, f32 x);
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void FillMemory(void* p, s32 value, u32 size);
// The record a wheel's emitter (PathEmitter's slot at 0x7C) takes: flags, the spawn data and
// how many to spawn.
struct WheelEmit {
    s32 flags;              // 0x00: 0xC0
    u8 pad04[0x3C - 0x04];
    void* spawn;            // 0x3C: the WheelSpawn
    s32 count;              // 0x40
    u8 pad44[0x50 - 0x44];
};

// Where and how a wheel's particles start: a point, a basis and a velocity.
struct WheelSpawn {
    Vec02 pos;              // 0x00
    Mat02 basis;            // 0x10
    Vec02 vel;              // 0x40
    u8 pad50[0x60 - 0x50];
};

typedef void (*EmitFn)(PathEmitter* self, WheelEmit* rec);
void func_00127E60(void* obj, s32 a1, void* a2, void* a3, void* a4, s32 a5);
void BuildBasisFromX(Vec02* v, Mat02* out);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
extern ValueRange g_unitRange;

void func_001D8E40(PathFollower* self)
{
    typedef Vu0::Vec Vec;
    if (self->fB14 != 0) {
        f32 t = (g_gameTime - self->f854) / D_002751D8;
        *(f32*)((u8*)self->fB14 + 0x334) = g_unitRange.Clamp(((QuadraticCurve*)D_00275240)->Eval(t));
        BaseObject* o = self->fB14;
        if (*(f32*)((u8*)o + 0x334) == 0.0f) {
            ((void (*)(BaseObject*))o->desc->m03)(o);
        }
    }
    f32 one = 1.0f;
    f32 zero = 0.0f;
    WheelSpawn spawn;
    for (u32 i = 0; i < 4; i++) {
        Slot19* s = &self->f6B0[i];
        if (one <= s->f58) {
            if (500.0f < self->f698) {
                Vec02 off;
                Vec02 dir;
                Mat02 m;
                Mat02 n;
                f32* range = (g_currentWorld->f1D70 == 3) ? D_00275508 : D_00275500;
                BuildAxisAngleMatrix(&g_unitYVector, &m, RandomFloatInRange(range[0], range[1]));
                f32 b = RandomFloatInRange(D_00275510[0], D_00275510[1]);
                switch ((s32)i) {
                case 0:
                    b = b + self->f69C;
                    break;
                case 1:
                    b = self->f69C - b;
                    break;
                case 2:
                    break;
                case 3:
                    b = -b;
                    break;
                }
                s32 front = (s32)i < 2;
                BuildAxisAngleMatrix(&g_unitZVector, &n, b);
                MulRotation(&m, n, m);
                TransformPointBetweenFrames(0, self, &s->v20, &spawn.pos);
                f32 len = front ? self->f610 : self->f614;
                Vu0::Q(off) = Vu0::FromFloats(zero, zero, len);
                Vu0::Q(spawn.pos) = Vu0::Sub(Vu0::Add(Vec::Of(spawn.pos), Vec::Of(off)),
                                             Vu0::Rotate(m, Vec::Of(off))).q;
                TransformDirectionBetweenFrames(0, self, &s->v30, &dir);
                BuildBasisFromX(&dir, &spawn.basis);
                Vu0::Q(spawn.vel) = Vu0::FromFloats(-self->f698, zero, zero);
                Vu0::Q(spawn.vel) = Vu0::Rotate(m, Vec::Of(spawn.vel)).q;
                WheelEmit rec;
                rec.flags = 0xC0;
                rec.count = (s32)s->f58;
                rec.spawn = &spawn;
                PathEmitter* e = (self->fAFC != 0) ? self->fAFC->f20 : self->fB18;
                if (e != 0) {
                    if (e->f18 == 0) {
                        func_00127E60(self, 0, &spawn.pos, &spawn.basis, &spawn.vel, 0);
                    }
                    ((EmitFn)e->vt[0x7C / 4])(e, &rec);
                }
            }
            s->f58 = s->f58 - (f32)(s32)s->f58;
        }
        if (one <= s->f5C) {
            Vec02 dir;
            WheelEmit rec;
            FillMemory(&spawn, 0, 0x60);
            TransformPointBetweenFrames(0, self, &s->v20, &spawn.pos);
            TransformDirectionBetweenFrames(0, self, &s->v30, &dir);
            BuildBasisFromX(&dir, &spawn.basis);
            rec.flags = 0xC0;
            rec.count = (s32)s->f5C;
            rec.spawn = &spawn;
            PathEmitter* e = (self->fAFC != 0) ? self->fAFC->f24 : self->fB1C;
            if (e != 0) {
                ((EmitFn)e->vt[0x7C / 4])(e, &rec);
            }
            s->f5C = s->f5C - (f32)rec.count;
        }
    }
}
