// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 216/220, checked 2026-11-07
// NEAR: addressing: retail loads the object's first row with 0x50(v0), then forms v0+0x50 once and loads the other two rows at 0x10(v0) and 0x20(v0); here every row is addressed from the unmodified v0 (0x60, 0x70) and the epilogue branch differs by one word. Same MulRotation as placed_object.cpp (RotateUntied rows from the frame matrix at sp, the product into the out matrix, w copied to the second out).
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "globals.h"
#include "vu0.h"

struct FramePoint_001EBD10 {
    u8 pad0[0x18];
    void* object;           // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 point;            // 0x40
    Mat02 m50;              // 0x50
};
void GetPlacedObjectRotationAt(void* self, f32 t, Mat02* rot, Vec02* spin);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, Vec02* e, Vec02* f, f32 t);

static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}
void func_001EBDD0(BeatPressCollider* self, f32 t, Mat02* rot, Vec02* spin)
{
    if (self->f67C == 0) {
        GetPlacedObjectRotationAt(self, t, rot, spin);
        return;
    }
    Mat02 m;
    Vec02 w;
    ComputeObjectFrameAtTime(((FramePoint_001EBD10*)self->f67C)->object, 0, 0, &m, 0, &w, t);
    FramePoint_001EBD10* f = (FramePoint_001EBD10*)self->f67C;
    MulRotation(rot, m, *(Mat02*)((u8*)self->f67C + 0x50));
    *spin = w;
}
