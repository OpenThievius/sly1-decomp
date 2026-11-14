// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two global pointer slots are at 0x574 and 0x578 (US 0x264, 0x268), and the float at 0x57C (US 0x26C).
void StartHitCountCollider(HitCountCollider* self)
{
    StartPlacedObject(self);
    self->baseRadius = self->radius3CC;
    ResolveObjectLinks(self, 0xC, (ObjectLink*)D_002749B0);
    self->walker = CreateStateWalker((StateGraph*)self->walkerGraph, self, -1, 0);
    self->heading = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    PlacedObject* v = (PlacedObject*)self->aimObject;
    self->aimHeading = ArctangentOfRatio(v->rot.r[0].y, v->rot.r[0].x);
    *(UnalignedFloatPair*)&self->f630 = *(UnalignedFloatPair*)((u8*)self->f62C + 0x2DC);
    u8* g1 = (u8*)&D_0026DD48;
    ((UnalignedPointer*)(g1 + 0x574))->p = (u8*)self + 0x690;
    u8* g2 = (u8*)&D_0026DFC8;
    ((UnalignedPointer*)(g2 + 0x574))->p = (u8*)self + 0x694;
    *(void**)(g1 + 0x578) = D_00274A40;
    *(f32*)(g2 + 0x57C) = 4.0f;
    SetWorldActiveFollower(self->world, self);
    s32 c = self->itemCount;
    self->items[c] = self;
    self->itemCount = c + 1;
    SetHitCountColliderState(self, 1);
}
