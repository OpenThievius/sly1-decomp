// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_002701F8.f324 is at 0x5B0 (US 0x324).
struct Global_177F98_eu { u8 pad0[0x5B0]; void* f5B0; };

void func_00177F98(Obj_177F98* self, Node_177F98* node)
{
    if ((u32)(node->kind - 1) < 2) {
        ((Global_177F98_eu*)&D_002701F8)->f5B0 = node;
        func_001E9498(D_00275BC0, &D_002701F8);
        return;
    }
    if (self->state != 0xC) {
        s32 f = self->flags;
        self->f225C = 0x21;
        self->f2BD0 = node;
        self->f2258 = 0xC;
        self->flags = f | 1;
    }
}

