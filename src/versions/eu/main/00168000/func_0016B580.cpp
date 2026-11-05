// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f250, p260 and f264 sit 784 (0x310) bytes further on than in US; from f2D0 on nothing moves.
struct Obj_16B580_eu {
    u8 pad0[0x2D0];
    s32 f2D0;
    s32 f2D4;
    f32 f2D8;
    u8 pad2DC[4];
    Sub_16B580* f2E0;
    u8 pad2E4[0x308 - 0x2E4];
    void* f308;
    u8 pad30C[0x33C - 0x30C];
    void* f33C;
    u8 pad340[0x250 + 0x310 - 0x340];
    s32 f250;
    u8 pad254[0xC];
    Obj_16B580_eu* p260;
    s32 f264;
};

void func_0016AF80(Obj_16B580_eu* o);
void func_0016B190(Obj_16B580_eu* o);
void func_0016B0F8(Obj_16B580_eu* o, G262C70* a);

void func_0016B580(Obj_16B580_eu* self, G262C70* arg)
{
    if (self->p260 == 0) {
        return;
    }
    if (self->p260->f2E0 == 0) {
        return;
    }
    if (self->f264 != 0) {
        if (func_001BE810() != 0) {
            func_0011CE30();
        }
        self->f264 = func_001BE980();
    }
    if (D_00272420 != 0) {
        return;
    }
    if (D_0027051C != 0) {
        return;
    }
    self = self->p260;
    Sub_16B580* p = self->f2E0;
    if (self->f308 != 0) {
        if (self->f308 == self->f33C) {
            func_0018C7F8(D_00264A40);
        }
        func_001518B8(self->f308);
        self->f308 = 0;
    }
    func_0016AF80(self);
    f32 delay = 0.3f;
    if (self->f2D4 == 1 && (p->f28 == p->f30 || delay <= D_0026185C[0] - self->f2D8)) {
        s32 idx = self->f2D0;
        if (idx == 0) {
            Obj_16B580_eu* g = (Obj_16B580_eu*)&D_0026FD00;
            if (g->f250 != 0) {
                return;
            }
            func_001E9498(D_00275BC0, &D_0026FD00);
            return;
        }
        Obj_16B580_eu* g = (Obj_16B580_eu*)&D_0026F808;
        if (g->f250 != 0) {
            return;
        }
        g->p260 = *(Obj_16B580_eu**)((u8*)&D_0026F808 + idx * 4 + 0x264 + 0x310);
        func_001E9498(D_00275BC0, &D_0026F808);
        return;
    }
    if (p->f28 != p->f30) {
        return;
    }
    if ((arg->flags & 0x800) || (arg->f14 == 1 && 5.0f <= D_0026185C[0])) {
        func_0016EC20(arg, 0x800);
        func_00194D30(&D_0026FF68, 0, 0x17);
        return;
    }
    if ((arg->flags & 0x140) != 0) {
        func_0016EC20(arg, 0x140);
        func_0016B190(self);
        return;
    }
    func_0016B0F8(self, arg);
}
