// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 154/172 (89.5%), checked 2026-11-07
// NEAR: same code and branches as retail; self and out swap saved registers (retail keeps out in $s1 and the camera in $s2). About 12 variants of the copy and the call (pointer locals, order of the branches) tried.
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

// The 0x50-byte record of the target in action (Camera +0x2F0): the target's slot 73 fills it.
struct TargetRecord_00143418 {
    u8 pad0[0x10];
    Vec02 v10;              // 0x10
    u8 pad20[0x40 - 0x20];
    Vec02 v40;              // 0x40
};

typedef void (*VFn_143418)(void* self, TargetRecord_00143418* out);



void func_00143418(Camera* self, void* o, TargetRecord_00143418* out)
{
    Vec02 offset;
    if (o == self->f2E0) {
        *out = *(TargetRecord_00143418*)((u8*)self + 0x2F0);
    } else {
        ((VFn_143418)(*(void***)o)[0x124 / 4])(o, out);
        ComputeOffsetBehindTarget(self, o, (Target_00143148*)out, &offset);
        Vu0::Q(out->v40) = Vu0::Add(Vu0::Q(out->v10), Vu0::Q(offset));
    }
}
