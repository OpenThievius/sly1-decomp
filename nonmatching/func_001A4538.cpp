// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 101/124 (81.5%), checked 2026-11-07
#include "common.h"
#include "placed_object.h"
#include "vu0.h"
s32 HasAnimationDrivenAttachment(void* ctx);
// NEAR (2026-11-07, worker inline-vu0): GPRs, frame and sequences are retail's. Retail loads the
// entry's point (lqc2 vf3) before the vmulx and keeps the walker's point in vf4 (scratch vf5);
// here the entry is loaded after the store of d, so the VU0 registers shift by one.

// What func_001A4538 moves: a walker's point (+0x630), and a contact record's normal (+0x80)
// with its entries of 0x40 bytes, each with a point at +0x30.
struct Walker_001A4538 {
    u8 pad0[0x630];
    Vec02 point;            // 0x630
};

struct ContactEntry_001A4538 {
    u8 pad0[0x30];
    Vec02 point;            // 0x30
};

union Contact_001A4538 {
    ContactEntry_001A4538 entries[1];   // 0x00
    struct {
        u8 pad0[0x80];
        Vec02 normal;       // 0x80
    };
};

void ResolveWalkerColliderContact(Walker_001A4538* self, Contact_001A4538* c, s32 i)
{
    if (HasAnimationDrivenAttachment(self) == 0) {
        Vec02* p = &c->entries[i].point;
        Vec02 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->point),
                             Vu0::MulX(Vu0::Q(c->normal), Vu0::Dot(Vu0::Q(self->point), Vu0::Q(c->normal))));
        Vu0::Q(*p) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(d));
    }
}
