// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL lays Obj_11A338 out 0x310 bytes later from 0x208 on, no longer sets the current
// entry here, takes the name from entry offset 8, and fetches the message with func_eu_001DDAB0(0xAA).
struct Ent_11A338_eu { u32 pad0; f32 f4; void* w8; };
struct Obj_11A338_eu;
struct VTab_11A338_eu { u8 pad[0x20]; void (*f20)(Obj_11A338_eu*, const char*); u8 pad2[0x38 - 0x24]; void (*f38)(Obj_11A338_eu*); };
struct Obj_11A338_eu { VTab_11A338_eu* vt; u8 pad0[0x518 - 4]; s32 color; u8 pad1[4]; void** slot; u8 pad2[0x57C - 0x524]; s32 f26c; s32 f270; };
const char* func_eu_001DDAB0(s32 id);

void func_001DFEB8(Obj_11A338_eu* self)
{
    Ent_11A338_eu* e;

    func_001AA268(self);
    e = (Ent_11A338_eu*)func_001DFE80((((Cam_11A338*)D_002623C0)->hi << 8) | ((Cam_11A338*)D_002623C0)->lo);
    if (e) {
        if (e->f4 != 0.0f) {
            ((Glob_11A338*)D_00275710)->f = e->f4;
        }
        if (((Glob_11A338*)D_00275710)->nm == 0 || !func_001E2100(((Glob_11A338*)D_00275710)->nm)) {
            ((Glob_11A338*)D_00275710)->nm = e->w8;
        }
    }
    if (func_0015C188(2)) {
        self->slot = (void**)D_002758E0;
        *self->slot = func_0015C1C0(2);
    }
    func_001AA788(self, 0.6f);
    *(s32*)((u8*)self + 0x518) = (s32)0xDF7F7F7Fu;
    if (func_001DD7A0((Glob_11A338*)D_00275710, (((Cam_11A338*)D_002623C0)->hi << 8) | ((Cam_11A338*)D_002623C0)->lo)) {
        func_001E02C8(self, 1);
    } else {
        func_001E02C8(self, 0);
    }
    if (((Flags_11A338*)D_002623C8)->flags & 8) {
        if (((Glob_11A338*)D_00275710)->cur->differs()) {
            self->vt->f20(self, func_eu_001DDAB0(0xAA));
            func_001AA8B8(self, 5.0f);
            self->vt->f38(self);
            self->f26c = 1;
        } else {
            self->f26c = 0;
        }
    } else {
        self->f26c = 0;
    }
    self->f270 = 0;
}
