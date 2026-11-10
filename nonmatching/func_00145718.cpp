// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 229/248 (92.3%), checked 2026-11-10
// NEAR (2026-11-10, w12-145088): 248 bytes, retail's size, and retail's registers: the position copied as Vu0::Q(self->pos) = Vu0::Q(*a2) (a u128 load into v0, which frees a0 for D_00261920's %hi and leaves retail's move a0,s0 in the call's delay slot). Still differs: the order of the three float argument loads (retail: $f13 before the sq, then $f12, $f14; ours: all three after the sq, $f13, $f14, $f12). The u128 store has no alias class, so every global float load waits for it; a store with a class (the Vec02 assignment, a Vec member) lets all three pass it and local-alloc then gives the copy a2 and the %hi t0, as before. Locals for the floats before or after the copy, Vec::Of, and a Vec member store were tried. Before: right instructions; differs in the order the arguments of the first call are set up (which hi() lands in which register, and where the copy of *a2 sits). Tried arguments through locals in three orders, the pointer last, the floats first, decomp-permuter --auto of tools/permute.py.
#include "common.h"
#include "shapes.h"
#include "camera.h"
#include "placed_object.h"
#include "vu0.h"

// The file's static initialiser and its constructor (config/us/generated.tsv) need this global.
struct PackedRgba
{
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
    PackedRgba(u32 v) { rgba = v; }
};
PackedRgba D_002618B0(0x80303030);

struct Target_00143148 {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
};
void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3);
f32 D_00261920 = 15.0f;
f32 D_00261924 = -8.0f;

// The camera func_00145718 moves: its position (+0x40), the orientation matrix (+0x80), the
// spring's two vectors (+0x230, +0x240) and the factors of a turn per pixel (+0x1F0, +0x1F4).
struct Orbit_00145718 {
    u8 pad0[0x40];
    Vec02 pos;              // 0x40
    u8 pad50[0x80 - 0x50];
    Mat02 rot;              // 0x80
    u8 padB0[0x1F0 - 0xB0];
    f32 scaleYaw;           // 0x1F0
    f32 scalePitch;         // 0x1F4
    u8 pad1F8[0x230 - 0x1F8];
    Vec02 v230;             // 0x230
    Vec02 v240;             // 0x240
};

void func_00144540(Camera* self);
extern f32 g_frameDt;
extern const Vec02 D_00248D30;
void SpringCameraVector(Orbit_00145718* self, Vec02* a, Vec02* b, const Vec02* target, f32 x, f32 y, f32 dt);
void ConvertOffsetToSpherical(Vec02* offset, Vec02* origin, f32* yaw, f32* pitch, f32* dist);
f32 Arctangent(f32 x);
void BuildYawPitchMatrix(Mat02* out, f32 yaw, f32 pitch);

void func_00145718(Orbit_00145718* self, Vec02* a1, Vec02* a2, f32 turnYaw, f32 turnPitch)
{
    Vec02 tmp;
    f32 yaw;
    f32 pitch;
    f32 dist;

    Vu0::Q(self->pos) = Vu0::Q(*a2);
    SpringCameraVector(self, &self->v230, &self->v240, &D_00248D30, D_00261920, D_00261924, g_frameDt);
    Vu0::Q(tmp) = Vu0::Add(Vu0::Q(*a1), Vu0::Q(self->v230));
    ConvertOffsetToSpherical(&tmp, a2, &yaw, &pitch, &dist);
    yaw = yaw + Arctangent(turnYaw * self->scaleYaw);
    pitch = pitch - Arctangent(turnPitch * self->scalePitch);
    BuildYawPitchMatrix(&self->rot, yaw, pitch);
    func_00144540((Camera*)self);
}

