// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 123/156 (78.8%), checked 2026-11-08
// permute.py --auto (2026-11-08, night-orders): 2 runs of 2/7 lines (5042 orders): best 23 bytes differ (33 as it stands), none EXACT.
#include "common.h"
#include "attached_set.h"
#include "oscillator.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-a): grows the box (+0x420, +0x430) and both radii by the
// oscillator's largest swing. The order of the last part differs: retail loads both corners,
// adds both radii, then vsub, vadd, stores the corners (min first) and the radii (0x3D4 first);
// here vsub and vadd follow their loads. All 24 orders of the four statements tried (9 to 17
// instructions off). The registers here are vf2 for the swing and vf3 for the Dot's 1.0, the
// other way round from retail: a Dot taking one vector (vmul.xyz %0, %2, %2 with a single "j"
// input) gives retail's (swing vf3, 1.0 vf2) and leaves 9 instructions of order; the header has
// no such helper because no matched function needs it.

void UpdateColliderBounds(Collider* self);
void ComputeOscillatorMaxDisplacement(Oscillator* osc, Vec02* out);

struct SwingRecord {
    u8 pad00[0x0C];
    Oscillator* osc;        // 0x0C
};

void UpdateAttachedSetBounds(AttachedSet* self)
{
    UpdateColliderBounds(self);
    SwingRecord* r = (SwingRecord*)self->f278;
    if (r != 0 && r->osc != 0) {
        Vec02 d;
        ComputeOscillatorMaxDisplacement(r->osc, &d);
        u128 v = Vu0::Q(d);
        f32 len = Vu0::ToFloat(Vu0::Length(v));
        Vu0::Q(self->boundsMin) = Vu0::Sub(Vu0::Q(self->boundsMin), v);
        Vu0::Q(self->boundsMax) = Vu0::Add(Vu0::Q(self->boundsMax), v);
        self->radius3D0 += len;
        self->radius3D4 += len;
    }
}
