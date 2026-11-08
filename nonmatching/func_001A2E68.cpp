// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 408/412 (99.0%), checked 2026-11-08
// NEAR (2026-11-08, vu0w3-e1): exact but for the two quadword copies of the node query: retail loads *where into $v1 and the effect's qA0 into $v0 (here the reverse, stores in the same order); all 120 orders of the five field assignments (tools/permute.py) leave this 4-byte difference, the best being this one.
// Night-close2 (2026-11-08): `u128 w = Vu0::Q(*where); Vu0::Q(q.dir) = Vu0::Q(self->qA0); Vu0::Q(q.pos) = w;` gives retail's registers but swaps the two sq (still 4 bytes; tools/permute.py over the five stores finds nothing better); NormalizeOr and the Vec02 temporaries do not apply.
#include "common.h"
#include "node_query.h"
#include "vu0.h"
#include "effect.h"

void RemoveEffect(Effect* node);
f32 RandomFloatInRange(f32 a, f32 b);
void FillMemory(void* p, s32 v, s32 n);
s32 FindNodeForQuery(void* p, s32 a, s32 b);
void BuildBasisFromX(void* a, void* b);

s32 HandleStreakedEffectImpact(Effect* self, void* hold, Vec02* where, Vec02* dir)
{
    if (self->i124 != 0) {
        NodeQuery q;
        FillMemory(&q, 0, 0x40);
        q.pos = *where;
        q.dir = *(Vec02*)&self->qA0;
        q.hold = hold;
        q.p00 = self->owner;
        q.kind = 0x10;
        if (FindNodeForQuery(&q, 0, 0) != 0) {
            goto remove;
        }
    }
    if (self->i120 != 0) {
        Mat02 basis;
        Vec02 v;
        *(Vec02*)&self->q80 = *where;
        BuildBasisFromX(dir, &basis);
        Vu0::Q(v) = Vu0::RotateTransposed(basis, Vu0::Q(self->qA0));
        v.x *= RandomFloatInRange(-0.95f, -0.85f);
        v.y += RandomFloatInRange(-400.0f, 400.0f);
        v.z += RandomFloatInRange(-400.0f, 400.0f);
        Vu0::Q(self->qA0) = Vu0::Rotate(basis, Vu0::Q(v));
        return 1;
    }
remove:
    RemoveEffect(self);
    return 1;
}
