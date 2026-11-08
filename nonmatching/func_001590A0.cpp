// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 964/984, checked 2026-11-07
// NEAR: the frame (0x320), the calls, the switch and the VU0 sequences are retail's, 56 of 203
//       instructions differ. Retail reloads the message's flags word after each store into the
//       record (`lw v0, 0(s2)` before every test; the stores do not let the compiler keep it),
//       ours keeps it in a register; the 0x80 count branch, the minimum with `movz` against our
//       `movn`, and the register numbers of the frame pointers follow. About 25 compiles
//       (the record and the message as structs or byte views, the helpers' quadwords).
#include "common.h"
#include "effect_owner.h"
#include "effect.h"
#include "shapes.h"
#include "placed_object.h"
#include "vu0.h"

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))
f32 RandomFloatInRange(f32 a, f32 b);
void* FillMemory(void* p, s32 v, u32 n);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

struct __attribute__((aligned(16))) RecCopy { u8 b[0x200]; };
struct __attribute__((aligned(16))) FrameCopy { u8 b[0x60]; };
typedef int Quadword128 __attribute__((mode(TI)));
void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);
f32 ClampToRange(void* range, f32 x);
void ComputeChainedWorldFrame(void* a, void* frame, void* out);
void SpawnEffectsFromRecord(s32 count, void* rec, void* chain);
extern f32 D_00262178[2];
extern const Vec02 D_00248D30;

struct SpawnMessage {
    s32 flags;
    s32 f4;
    u8 pad8[0x8];
    Quad16 q10;
    Quad16 q20;
    f32 f30;
    f32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
};
void func_001590A0(void* self, SpawnMessage* m)
{
    RecCopy rec;
    FrameCopy frame;
    Vec02 v;
    Vec02 tmp0;
    Vec02 tmp1;
    rec = *AT(RecCopy*, self, 0x90);
    s32 flags = m->flags;
    s32 count;
    if (flags & 0x80) {
        count = m->f40;
    } else {
        count = (s32)RandomFloatInRange(AT(f32, self, 0xA4), AT(f32, self, 0xA8));
    }
    if (m->flags & 1) AT(s32, &rec, 0x7C) = m->f4;
    if (m->flags & 2) AT(Quad16, &rec, 0x60) = m->q10;
    if (m->flags & 4) {
        AT(s32, &rec, 0x10) = 0;
        AT(Quad16, &rec, 0x20) = m->q20;
    } else if (flags & 0x40) {
        AT(s32, &rec, 0x78) = m->f3C;
        AT(s32, &rec, 0x7C) = AT(s32, self, 0x18);
    } else {
        FillMemory(&frame, 0, 0x60);
        ComputeChainedWorldFrame(self, &frame, (u8*)&frame + 0x10);
        AT(void*, &rec, 0x78) = &frame;
        if (!(m->flags & 1)) AT(s32, &rec, 0x7C) = AT(s32, self, 0x18);
    }
    if (m->flags & 8) {
        if (AT(s32, &rec, 0x120) == 0) {
            f32 s = m->f30;
            if (s == 0.0f) s = m->f34 * 0.01f;
            if (s < 1.0f) count = (s32)((f32)count * s);
            else count = (s32)((f32)count / s);
            s32 cap = (s32)AT(f32, self, 0xA8) / 2;
            if (cap < count) count = cap;
            f32 r = ClampToRange(D_00262178, s);
            AT(f32, &rec, 0xA0) = AT(f32, &rec, 0xA0) * r;
            AT(f32, &rec, 0xA4) = AT(f32, &rec, 0xA4) * r;
            s = 0.5f >? s;
            StoreFloatAsQuadword(&tmp0, s);
            Quadword128 q0 = *(Quadword128*)&tmp0;
            CopyQuadword(&tmp1, (u8*)&rec + 0x140);
            StoreQuadword((u8*)&rec + 0x140, ScaleQuadword(q0, *(Quadword128*)&tmp1));
        }
    }
    if (AT(s32, &rec, 0x120) == 1) {
        if (m->flags & 0x10) {
            AT(f32, &rec, 0x1D4) = m->f30;
            AT(f32, &rec, 0x1D0) = m->f30;
        }
        if (m->flags & 0x20) AT(s32, &rec, 0x1E0) = m->f38;
    }
    void* chain[3];
    void* cp = 0;
    if (AT(s32, self, 0xBC) != 0) {
        chain[0] = (u8*)self + 0xC4;
        chain[1] = (u8*)self + 0xC0;
        chain[2] = self;
        cp = chain;
    }
    SpawnEffectsFromRecord(count, &rec, cp);
    if (AT(s32, self, 0xA0) != 0) {
        switch (AT(s32, &rec, 0x10)) {
        case 0:
            v = AT(Vec02, &rec, 0x20);
            break;
        case 1:
            Vu0::Q(v) = Vu0::MulXSum(Vu0::Q(AT(Vec02, &rec, 0x20)), Vu0::Scalar(0.5f), Vu0::Q(AT(Vec02, &rec, 0x30)), Vu0::Scalar(0.5f));
            break;
        case 2:
            v = *AT(Vec02*, AT(u8*, &rec, 0x20), 0x18);
            break;
        case 3:
            v = D_00248D30;
            break;
        case 4:
            v = AT(Vec02, &rec, 0x40);
            break;
        }
        if (AT(u8*, &rec, 0x78) != 0) {
            u8* fr = AT(u8*, &rec, 0x78);
            Vu0::Q(v) = Vu0::Add(Vu0::Rotate(AT(Mat02, fr, 0x10), Vu0::Q(v)), Vu0::Q(AT(Vec02, fr, 0)));
        }
        TransformPointBetweenFrames(AT(void*, &rec, 0x7C), 0, &v, &v);
        u8* snd = AT(u8*, self, 0xA0);
        StartSoundEffect(AT(s32, snd, 0), 0, 0, (s32)&v, AT(f32, snd, 4), AT(f32, snd, 8), AT(f32, snd, 0xC), AT(f32, snd, 0x10), 0.0f, 0, 0);
    }
}
