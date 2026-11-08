// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 340/360 (94.4%), checked 2026-11-08
#include "common.h"
#include "switched_collider.h"
#include "screen_element.h"
#include "vu0.h"
// NEAR (2026-11-08, worker night-mmi): all but mode 2's registers: retail keeps the aim's
// address in v1 and the vector in a2 (the base allocated before the vector), and stores the
// helper's slot after loading the element's table into a3; here the base takes a2, the vector
// v1, and the slot is stored first. Writing the aim before the rates gives retail's base (the
// aim's address, the rates at -0x10); through a pointer to the element the base is the element.

extern f32 g_gameClock[];
extern const Vec02 D_00248D30;
void SetFollowObjects(void* a, s32 b, s32 c);
s32 ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);

void SetModeColliderMode(ModeCollider* self, s32 mode)
{
    s32 old = self->f610;
    if (mode == old) return;
    switch (old) {
    case 3:
    case 4:
        self->f6D8 = g_gameClock[1];
        break;
    }
    void* anim = 0;
    switch (mode) {
    case 2: {
        Vu0::Q(D_00270650.aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
        *(Vec02*)&D_00270650.rateX = D_00248D30;
        D_00270650.vt->m16(&D_00270650, 2);
        anim = self->f6C0;
        break;
    }
    case 1:
        anim = self->f6C4;
        break;
    case 3:
        anim = self->f6C8;
        self->f6D8 = 3.4028235e+38f;
        break;
    case 4:
        anim = self->f6CC;
        self->f6D8 = 3.4028235e+38f;
        SetFollowObjects(self->f6E8, (s32)self, (s32)self);
        break;
    }
    self->f610 = mode;
    self->f614 = g_gameClock[1];
    ReplaceAnimationPlayer(anim, self, 1, &self->f618, 0.0f, 1.0f);
}
