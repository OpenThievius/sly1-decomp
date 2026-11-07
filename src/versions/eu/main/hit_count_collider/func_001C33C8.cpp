// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two global pointer slots are at 0x574 and 0x578 (US 0x264, 0x268), and the float at 0x57C (US 0x26C).
void func_001C33C8(HitCountCollider* self)
{
    StartPlacedObject(self);
    self->f68C = self->radius3CC;
    ResolveObjectLinks(self, 0xC, D_002749B0);
    self->f668 = CreateStateWalker(self->f664, self, -1, 0);
    self->f644 = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    PlacedObject* v = (PlacedObject*)self->f660;
    self->f648 = func_00205778(v->rot.r[0].y, v->rot.r[0].x);
    *(Pk8_1C33C8*)&self->f630 = *(Pk8_1C33C8*)((u8*)self->f62C + 0x2DC);
    u8* g1 = (u8*)&D_0026DD48;
    ((Pp_1C33C8*)(g1 + 0x574))->p = (u8*)self + 0x690;
    u8* g2 = (u8*)&D_0026DFC8;
    ((Pp_1C33C8*)(g2 + 0x574))->p = (u8*)self + 0x694;
    *(void**)(g1 + 0x578) = D_00274A40;
    *(f32*)(g2 + 0x57C) = 4.0f;
    SetWorldActiveFollower(self->world, self);
    s32 c = self->f71C;
    self->f720[c] = self;
    self->f71C = c + 1;
    func_001C3FC8(self, 1);
}
