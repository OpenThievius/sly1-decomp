// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: toggles a screen's mode (offsets 0x56C/0x570 in PAL).
struct Obj_1940E8_eu {
    void** vtbl;
    u8 pad_004[0x56C - 4];
    s32 f56C;
    s32 f570;
};
typedef void (*VFn_1940E8_eu)(Obj_1940E8_eu* self);
void func_001E96F8(Obj_1940E8_eu* self, s32 mode);
void func_00193EE8(Obj_1940E8_eu* self, s32 a, s32 b);

void func_001940E8(Obj_1940E8_eu* self, s32 mode) {
    if (self->f56C == mode) return;
    if (mode != 0) {
        s32 key = (*(u32*)((*(u8**)&D_002623C0) + 0x19D8) << 8) | *(u32*)((*(u8**)&D_002623C0) + 0x19DC);
        if (key == 0x308) {
            func_001BED48();
            func_001E96F8((Obj_1940E8_eu*)D_00275BC0, 5);
        } else if (D_0027051C != 0) {
            func_001E96F8((Obj_1940E8_eu*)D_00275BC0, 5);
        } else {
            u8* base = D_00275BC0;
            if (((s32*)base)[1] == 3) {
                func_001E96F8((Obj_1940E8_eu*)base, 4);
            } else {
                func_001E96F8((Obj_1940E8_eu*)base, 5);
            }
        }
        func_00193EE8(self, -1, self->f570);
        ((VFn_1940E8_eu)self->vtbl[14])(self);
        func_0016E0F0((Bits_1940E8)1);
        func_0016EC88((Pool_1940E8*)((u8*)&D_00262C70));
    } else {
        s32 key = (*(u32*)((*(u8**)&D_002623C0) + 0x19D8) << 8) | *(u32*)((*(u8**)&D_002623C0) + 0x19DC);
        if (key == 0x308) {
            func_001BED70();
            func_001E96F8((Obj_1940E8_eu*)D_00275BC0, 3);
        } else if (D_0027051C != 0) {
            func_001E96F8((Obj_1940E8_eu*)D_00275BC0, 3);
        } else if (self->f570 != 0) {
            func_001E96F8((Obj_1940E8_eu*)D_00275BC0, 3);
        } else {
            func_001E96F8((Obj_1940E8_eu*)D_00275BC0, 6);
        }
        func_00193EE8(self, self->f570, -1);
        ((VFn_1940E8_eu)self->vtbl[15])(self);
        func_0016E118((Bits_1940E8)1);
    }
    self->f56C = mode;
}

