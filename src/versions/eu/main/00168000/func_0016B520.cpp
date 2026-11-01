// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: Obj_16B520.field25C is at 0x56C (US 0x25C).
struct Obj_16B520_eu { u8 pad0[0x56C]; s32 field56C; };

void func_0016B520(Obj_16B520_eu* self)
{
    if (self->field56C != 0) {
        void* p = func_0015A448(D_00275710, 0x4FD, 0);
        if (p != 0) {
            func_001F4ED0(p);
        }
    }
}

