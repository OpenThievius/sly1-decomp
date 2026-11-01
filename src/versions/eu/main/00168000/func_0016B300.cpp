// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: picks a sound through func_eu_001DE018 (by id) where US takes a slot address from a table.
// D_eu_00275374 is US D_0026FCF4, at an address the tools do not pair.

struct Gl_eu_16B300 { u8 pad[0x578]; f32 f578; };
extern s32 D_eu_00263BC0[];
extern s32 D_eu_00275374;
Slot_16B300* func_eu_001DE018(s32 id);

void func_0016B300(Self_16B300* self, s32 a, s32 b)
{
    if (a == self->f2D0 && b == self->f2D4) return;
    if (a != self->f300 && a > 0) {
        Slot_16B300* slot = 0;
        u8* ent = (u8*)D_002623C0 + a * 0x44C;
        if (*(s32*)(ent + 0x458) & 1) {
            if (!(((Glob_16B300*)D_002623C0)->f19EC & 2)) {
                slot = func_eu_001DE018(5);
                ((Glob_16B300*)D_002623C0)->f19EC |= 2;
            }
        } else {
            Gl_eu_16B300* gp = (Gl_eu_16B300*)D_0026FA90;
            if (D_00262970 <= D_00261858.f4 - gp->f578) {
                slot = func_eu_001DE018(D_eu_00263BC0[a]);
                gp->f578 = D_00261858.f4;
            }
        }
        if (slot) {
            func_001BE728(slot);
            D_eu_00275374 = func_001BE980();
        }
    }
    void* h = self->f2E0;
    if (h) {
        if (self->f2D0 == -1) {
            if (a != 0) {
                func_001B6628(h, D_00262860[a].b);
                func_001B64D8(self->f2E0, D_00262860[a].a);
            }
        } else {
            func_001B64D8(h, *(s32*)((u8*)D_00262860 + (a * 8 + b * 4)));
        }
    }
    self->f2D0 = a;
    self->f2D4 = b;
    self->f2D8 = D_00261858.f4;
}
