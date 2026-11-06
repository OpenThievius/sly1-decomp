// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's object has its fields at 0x528, 0x560 and 0x578, and the y is 126.30508 where US has 125.4.
void func_001AA998(void* self, s32 flag);
void func_001AAB20(void* self, f32 x, f32 y);
void func_001E7518(void* self, s32 mode);
struct Ptr_1E76E0_eu {
    s32 f0;
    union {
        s32 i4;
        f32 f4;
    };
};

struct Obj_1E76E0_eu {
    u8 pad0[0x528];
    Ptr_1E76E0_eu* f528;
    u8 pad1[0x560 - 0x52C];
    s32 f560;
    u8 pad2[0x578 - 0x564];
    s32 f578;
};

void func_001E76E0(Obj_1E76E0_eu* self, s32 value)
{
    s32 old = self->f560;
    SetScreenElementMode(self, value);
    if (old == value) return;
    if (old != 0) goto done;
    if (D_00270458 == 4) {
        self->f528->i4 = 0;
        SetScreenElementSize(self, 640.0f, 360.0f);
    } else {
        self->f528->f4 = -20.0f;
        SetScreenElementSize(self, 160.0f, 126.305086f);
    }
done:
    if (value != 2) return;
    if (D_00270458 == 4) return;
    self->f578 = -1;
    SetArcPhase(self, 3);
}
