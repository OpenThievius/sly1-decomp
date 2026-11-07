// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 424/420, checked 2026-11-07
#include "common.h"
#include "shapes.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "item_keeper.h"
#include "flag_table.h"
#include "node_query.h"
#include "c62.h"
#include "animation.h"
#include "attachment.h"
#include "c8b.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-c): all but the difference vector. Retail stores it from a copy
// (vsub into vf2, vmove.xyzw vf3, vf2, sqc2 vf3) and dots the copy in case 0 and the original in
// case 1, never reloading it; here it is stored from vf2 and reloaded from the stack in both
// cases (4 bytes longer). Tried: a u128 for the dots with the Vec02 stored apart (no reloads,
// no vmove: vf2 in both), Vu0::Set for the store, a cast read for the dots.

// What func_001CB3D0 reads of the player's f23A0 and f23A8: a word that, set, ends the test.
struct Blocker_23A0 {
    u8 pad00[0x54];
    s32 f54;                // 0x54
};
struct Blocker_23A8 {
    u8 pad00[0x6C];
    s32 f6C;                // 0x6C
};

s32 MaskWorldBitsBySave(void);
s32 IsObjectOfKind(void* obj, s32 kind);

s32 func_001CB3D0(Agent* self)
{
    Player* t = (Player*)self->desc08()->m62(self);
    if (IsObjectOfKind(t, 7) == 0) {
        return 0;
    }
    if (t->f2220 != 6) {
        return 0;
    }
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(t->v140), Vu0::Q(self->v140));
    switch (t->f239C) {
    case 3:
        if (MaskWorldBitsBySave() & 0x12000) {
            return 1;
        }
        break;
    case 0:
        if (t->f23A0 != 0 && ((Blocker_23A0*)t->f23A0)->f54 != 0) {
            return 0;
        }
        if (t->f23A8 != 0 && ((Blocker_23A8*)t->f23A8)->f6C != 0) {
            return 0;
        }
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(t->m110.r[0]))) > 0.0f) {
            return 1;
        }
        break;
    case 1:
        if (t->f23A0 != 0 && ((Blocker_23A0*)t->f23A0)->f54 != 0) {
            return 0;
        }
        if (t->f23A8 != 0 && ((Blocker_23A8*)t->f23A8)->f6C != 0) {
            return 0;
        }
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(t->m110.r[0]))) < 0.0f) {
            return 1;
        }
        break;
    case 2:
        if (t->f2228 == 0x10) {
            return 1;
        }
        break;
    }
    return 0;
}
