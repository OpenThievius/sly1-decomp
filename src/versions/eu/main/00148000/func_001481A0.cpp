// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f26C, fn274 and p278 are at 0x57C, 0x584 and 0x588 (US 0x26C, 0x274, 0x278).
struct Sys_1481A0_eu {
    u8 pad0[0x57C];
    f32 f26C;
    u8 pad1[0x4];
    void (*fn274)(void);
    void* p278;
};

struct __attribute__((packed)) PSys_1481A0_eu {
    u8 pad0[0x57C];
    f32 f26C;
};

void func_001481A0(void* self)
{
    Self_1481A0* s = (Self_1481A0*)self;
    Glob_1481A0* g = D_002623C0;
    s32 c = g->f19E8 + 1;
    s32 r;
    g->f19E8 = c;
    if (c >= 100) {
        r = func_00160D98();
        if (g->f19E4 < r) {
            D_002623C0->f19E8 = 0;
            ((PSys_1481A0_eu*)D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0_eu*)D_0026CE48)->fn274 = func_00148038;
            ((Sys_1481A0_eu*)D_0026CE48)->p278 = s->p14;
            return;
        }
        if (D_002623C0->f19E0 < 99) {
            D_002623C0->f19E8 = 0;
            ((Sys_1481A0_eu*)D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0_eu*)D_0026CE48)->p278 = 0;
            ((Sys_1481A0_eu*)D_0026CE48)->fn274 = func_00148178;
            {
                VObj_1481A0* obj = (VObj_1481A0*)D_0026C6C8;
                obj->vtbl[14](obj);
            }
        } else {
            D_002623C0->f19E8 = 99;
        }
    }
}
