// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 434/460 (94.3%), checked 2026-11-07
// NEAR: all but two things retail has: MulAddX2's result takes c's register here, a's in retail (the header lists c first; a first gives a's register but swaps a and b's, vf2 and vf3), and the loop of the faces: retail's face pointer is a1 loaded before the triangle base (the load is in blez's delay slot, copied to a2), here the other way round. Needs the lead: MulAddX2's operand order.
#include "common.h"
#include "collider.h"
#include "fpu.h"
#include "vu0.h"

struct MeshMotion {
    Vec02* velocity;
    Vec02* accel;
    struct Tri { s32 i[3]; } *tris;
};

struct MeshFace {
    Vec02 normal;
    f32 dist;
    u8 pad14[0xA];
    u16 ref;
};

void func_001BBEB8(Collider* self, f32 dt)
{
    Vec02 a, b;
    Vec02* pts = (Vec02*)self->mesh.verts;
    Vec02* vel = ((MeshMotion*)self->hook)->velocity;
    Vec02* acc = ((MeshMotion*)self->hook)->accel;
    f32 big = 0.0f;
    for (s32 i = 0; i < self->mesh.vertCount; i++) {
        u128 p = Vu0::Q(pts[i]);
        u128 s = Vu0::Scalar(dt);
        u128 v = Vu0::Q(vel[i]);
        u128 t = Vu0::Scalar(dt * (dt * 0.5f));
        u128 c = Vu0::Q(acc[i]);
        Vu0::Q(pts[i]) = Vu0::MulAddX2(p, v, s, c, t);
        Vu0::Q(vel[i]) = Vu0::MulAddX(Vu0::Q(vel[i]), Vu0::Q(acc[i]), Vu0::Scalar(dt));
        f32 len = Vu0::ToFloat(Vu0::Dot(Vu0::Q(pts[i]), Vu0::Q(pts[i])));
        if (big < len) {
            big = len;
        }
    }
    self->radius3CC = Fpu::Sqrt(big);
    MeshFace* face = (MeshFace*)self->mesh.faces;
    MeshMotion::Tri* tri = ((MeshMotion*)self->hook)->tris;
    for (s32 i = 0; i < self->mesh.faceCount; i++) {
        Vu0::Q(a) = Vu0::Sub(Vu0::Q(pts[tri[i].i[1]]), Vu0::Q(pts[tri[i].i[0]]));
        Vu0::Q(b) = Vu0::Sub(Vu0::Q(pts[tri[i].i[2]]), Vu0::Q(pts[tri[i].i[0]]));
        u128 n = Vu0::Cross(Vu0::Q(a), Vu0::Q(b));
        Vu0::Q(face->normal) = n;
        n = Vu0::DivX(Vu0::Q(face->normal), Vu0::Sqrt(Vu0::Dot(Vu0::Q(face->normal), Vu0::Q(face->normal))));
        Vu0::Q(face->normal) = n;
        *(u32*)&face->dist = Vu0::ToBits(Vu0::Dot(Vu0::Q(face->normal), Vu0::Q(pts[face->ref])));
        face++;
    }
}
