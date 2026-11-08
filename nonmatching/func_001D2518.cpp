// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 648/680 (95.3%), checked 2026-11-08
// Tried night-close8, 12 compiles: the else arm's row as the link it already holds (row = (ContactRow03*)link: retail's move s4,s7), the normalised direction stored with Vu0::Set (from the frame, not through s1), and the three dots read with ToFloatMoved: 37 differing words down to 13, the callee-saved registers now retail's. Row initialised before the if: far worse; the last dot of Vec values: no change.
// NEAR: the prologue's order (retail saves s0 and ra and moves a0 before s8 and s7), the else arm's move s4,s7 before the addiu of sp+0x10 in retail, and the last dot's VU0 registers (retail loads delta into vf2 and dir into vf1, ours the other way).
// Before, night-moved (2026-11-08): NormalizeOrMoved loads the unit-Z fallback with lq before the length mtc1 as retail does; left: the callee-saved register assignment (s1/s2, s7/s8, s4) and the dot operands vf1/vf2 order.
// Before (2026-11-08, vu0w3-e1): same size and frame; 7 instructions of 170 differ in order and the rest in registers: retail keeps the frame addresses in s1 (sp+0x20), s2 (sp+0x10), s3, s5 and the link in s7 with &f23E0 in s8 (here s1/s2 and s7/s8 swapped), and loads the unit-Z fallback with lq before the length's mtc1 where here it is in the delay slot of the compare.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "game_clock.h"
#include "globals.h"
#include "vu0.h"
#include "placed_object.h"
#include "path_curve.h"
#include "collider.h"

float D_00274F00 = 35.0f;
float D_00274F04 = 100.0f;
float D_00274F08 = 0.5f;
INCLUDE_DATA(D_00274F0C);
float D_00274F14 = 50.0f;
float D_00274F18 = 1.0f;
float D_00274F1C = 0.400000006f;
float D_00274F20[2] = {10.0f, 0.0f};
float D_00274F28[4] = {1500.0f, 0.0f, 0.5f, 0.0f};

struct TwoEntryBlendEntry {
    u8 pad0[4];
    void* p4;
    u8 pad8[4];
    f32 fC;
};

void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);
void func_0012CD78(f32 f12, f32 f13, void* a0, void* a1, void* a2, s32 a3, void* a4, s32 a5, void* a6, s32 a7);


struct PinnedPath {
    u8 pad00[0x18];
    PlacedObject* f18;
    u8 pad1C[0x34 - 0x1C];
    PathCurve* f34;
};

typedef void (*PathSampleFn)(PathCurve* self, f32 len, Vec02* pos, Vec02* dir);

void TransformPointBetweenFrames(void* from, void* to, void* in, void* out);
void TransformDirectionBetweenFrames(void* from, void* to, void* in, void* out);
void BuildPerpendicularPair(Vec02* dir, Vec02* a, const Vec02* b, const Vec02* c);
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void func_001D2518(Player* self)
{
    Vec02 pos;
    Vec02 dir;
    Vec02 local;
    Vec02 delta;
    Vec02 perp[2];
    PinnedPath* path = (PinnedPath*)self->f2208;
    Contact03** link = &self->contacts4B4;
    ContactRow03* row;
    if (path->f18 != 0 && (path->f18->desc->flags & 2) != 0) {
        ContactRow03* r = self->contacts->head;
        Collider* key = *(Collider**)((u8*)path->f18 + 0x50);
        while (r != 0 && r->other != key) {
            r = r->next;
        }
        row = r;
        link = row->link;
    } else {
        row = (ContactRow03*)link;
    }
    PathSampleFn sample = (PathSampleFn)((PinnedPath*)self->f2208)->f34->vt->m02;
    if (sample) {
        sample(((PinnedPath*)self->f2208)->f34, self->f2410, &pos, &dir);
    }
    TransformPointBetweenFrames(((PinnedPath*)self->f2208)->f18, 0, &pos, &pos);
    TransformDirectionBetweenFrames(((PinnedPath*)self->f2208)->f18, 0, &dir, &dir);
    Vu0::Set(dir, Vu0::NormalizeOrMoved(Vu0::Q(dir), *(const u128*)&g_unitZVector));
    BuildPerpendicularPair(&dir, perp, &g_unitXVector, &g_unitZVector);
    TransformPointBetweenFrames(self, 0, &self->f23E0, &local);
    Vu0::Q(delta) = Vu0::Sub(Vu0::Add(Vu0::Q(local), Vu0::Q(*(Vec02*)((u8*)self + 0x2400))), Vu0::Q(pos));
    CreatePooledContact(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(delta), Vu0::Q(perp[0]))), self, path->f18, &local, &perp[0], 0xB, 0, 0, row);
    CreatePooledContact(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(delta), Vu0::Q(perp[1]))), self, path->f18, &local, &perp[1], 0xB, 0, 0, row);
    CreatePooledContact(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(delta), Vu0::Q(dir))), self, path->f18, &local, &dir, 0xB, 0, 0, row);
    *link = (Contact03*)row->head;
}

