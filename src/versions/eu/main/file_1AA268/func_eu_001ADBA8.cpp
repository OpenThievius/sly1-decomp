// SPDX-License-Identifier: AGPL-3.0-or-later
// Dispatches on the state at +0x560 (0 to 3): calls func_eu_001AB2B0 for state 0; otherwise sets the flag at +0x570 and calls func_eu_001E3100 or func_eu_001E3050, then the virtual slot 16 of self with 3.
typedef void (*VFnS_eu_001ADBA8)(void* self, s32 a);

struct Obj_eu_001ADBA8 {
    VFnS_eu_001ADBA8* vtbl;
    u8 pad004[4];
    u8 sub008[0x558];
    s32 state;
    u8 pad564[0xC];
    s32 flag;
    u8 pad574[0];
    u16 value;
};

void func_eu_001AB2B0(void* self, s32 a1);
s32 func_eu_001E3100(void* p, s32 a1);
void* func_eu_001E3050(void* p, s32 a1);

void func_eu_001ADBA8(Obj_eu_001ADBA8* self, s32 a1)
{
    if (self->state == 0) {
        func_eu_001AB2B0(self, a1);
        return;
    }
    if (self->state < 0) {
        return;
    }
    if (self->state >= 4) {
        return;
    }
    if (self->flag == 0) {
        if (func_eu_001E3100(self->sub008, a1) == 0) {
            return;
        }
    }
    self->flag = 1;
    if (a1 != 0) {
        func_eu_001E3050((u8*)self + 0x574, a1);
    } else {
        self->value = 0;
    }
    self->vtbl[16](self, 3);
}
