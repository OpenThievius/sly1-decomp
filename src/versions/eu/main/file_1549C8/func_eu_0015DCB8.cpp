// SPDX-License-Identifier: AGPL-3.0-or-later
// Constructor: sets the kind, two ids and four default colours, then runs the base init and returns the object.
struct Obj_eu_15DCB8 {
    s32 kind;
    s32 a1;
    u8 pad8[8];
    s32 a2;
    u8 pad14[0x50];
    void* table;
    u8 pad68[0x3C];
    u32 c0;
    u32 c1;
    u32 c2;
    u32 c3;
    s32 a3;
};

extern u8 D_eu_0024CA50[];
void func_eu_0015DDA0(Obj_eu_15DCB8* self);

Obj_eu_15DCB8* func_eu_0015DCB8(Obj_eu_15DCB8* self, s32 a1, s32 a2, s32 a3)
{
    self->table = D_eu_0024CA50;
    self->kind = 1;
    self->a1 = a1;
    self->a2 = a2;
    self->c3 = 0xFF808080;
    self->c2 = 0xFF808080;
    self->c1 = 0xFF808080;
    self->c0 = 0xFF808080;
    self->a3 = a3;
    func_eu_0015DDA0(self);
    return self;
}
