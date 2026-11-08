// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 620/632 (98.1%), checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "world_listed_object.h"
// NEAR (2026-11-08, worker night-mmi): five instructions: the colour's address is
// addu a0, t0, v0 here and addu a0, v0, t0 in retail (the base and the index swapped, in every
// form of the address tried); the second RemapQuadraticParameter call sets $f13 before a0, where
// retail sets a0 first; and the last test of mode loads it into v0 where retail uses v1.

void AssignAnimRecord(WorldListedObject* self, void* x);
void FillMemory(void* block, s32 value, s32 size);

// The part of the record from +0x120 that func_0013A128 reads through one pointer.
struct LookSourceTail {
    u8 pad00[0x10];
    s32 still;          // 0x130
    void* anim;         // 0x134: the anim record's key (AssignAnimRecord)
    u8 pad18[0x20 - 0x18];
    u8 curve140[0x10];  // 0x140
    Quad16 q150;        // 0x150
    u8 curve160[0x10];  // 0x160
    s32 f170;           // 0x170
    f32 f174;           // 0x174
    u8 pad58[0x5C - 0x58];
    s32 colorCount;     // 0x17C
    u8* colors;         // 0x180: colorCount colours of four bytes
    s32 f184;           // 0x184
    u8 pad68[0x70 - 0x68];
    s32 f190;           // 0x190
    f32 f194;           // 0x194
};

// The record func_0013A128 copies a world-listed object's look from (an effect spawner's
// +0x2D0), as far as it reads it.
struct LookSource {
    u8 pad00[0xB0];
    Vec02 vB0;              // 0xB0: a drift; the source is still when it and fC0, fC4 are 0
    f32 fC0;                // 0xC0
    f32 fC4;                // 0xC4
    u8 padC8[0xF4 - 0xC8];
    f32 fF4;                // 0xF4: a time the curves and the rate are taken over
    u8 padF8[0x110 - 0xF8];
    u8 curve110[0x10];      // 0x110
    LookSourceTail tail;    // 0x120
};

void RemapQuadraticParameter(f32 scale, f32 offset, void* in, void* out);
void func_001583E8(void* out, LookSource* src);

void func_0013A128(WorldListedObject* self, LookSource* src)
{
    LookSourceTail* t = &src->tail;
    self->f618 = src->tail.f190;
    self->f61C = src->tail.f194;
    self->colorCount = src->tail.colorCount;
    for (s32 i = 0; i < self->colorCount; i++) {
        s32 k = self->colorCount - i - 1;
        u8* colors = self->color[0];
        u8* out = &colors[k * 4];
        for (s32 j = 0; j < 4; j++) {
            *out++ = ((src->tail.colors + i * 4)[j] + 1) >> 1;
        }
    }
    self->f614 = src->tail.f184;
    AssignAnimRecord(self, t->anim);
    FillMemory(&self->q300, 0, 0x10);
    s32 n = self->regCount;
    if (n >= 2) {
        if (t->f174 != 0.0f) {
            self->f304 = (f32)n / t->f174;
        } else if (t->f170 != 0) {
            self->f304 = (f32)n / src->fF4;
        } else {
            self->q300 = t->q150;
        }
    }
    RemapQuadraticParameter(1.0f / src->fF4, 0.0f, src->curve110, self->curve2F0);
    RemapQuadraticParameter(1.0f / src->fF4, 0.0f, src->tail.curve140, self->curve2E0);
    RemapQuadraticParameter(1.0f / src->fF4, 0.0f, src->tail.curve160, self->curve310);
    s32 st = src->tail.still;
    self->mode = st;
    s32 still = 0;
    if (st == 0) {
        s32 slow = 0;
        if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(src->vB0))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(src->vB0))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(src->vB0))) < 0.0001f) {
            slow = 1;
        }
        if (slow && src->fC0 == 0.0f && src->fC4 == 0.0f) {
            still = 1;
        }
    }
    if (still) {
        self->mode = 1;
    }
    FillMemory(self->block330, 0, 0x50);
    if (self->mode == 0) {
        func_001583E8(self->block330, src);
    }
}
