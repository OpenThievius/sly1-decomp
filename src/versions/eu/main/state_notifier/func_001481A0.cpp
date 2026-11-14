// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f26C, fn274 and p278 are at 0x57C, 0x584 and 0x588 (US 0x26C, 0x274, 0x278).
typedef void (*VFn_1481A0)(void* self);
struct VObj_1481A0 {
    VFn_1481A0* vtbl;
};
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

void CountPickupTowardHundred(void* self)
{
    Effect* s = (Effect*)self;
    GameProgress* g = g_saveData;
    s32 c = g->pickupCount + 1;
    s32 r;
    g->pickupCount = c;
    if (c >= 100) {
        r = GetSpareCountLimit();
        if (g->spareCount < r) {
            g_saveData->pickupCount = 0;
            ((PSys_1481A0_eu*)&D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0_eu*)&D_0026CE48)->fn274 = (void (*)(void))PlaceSpareSoundNotifier;
            ((Sys_1481A0_eu*)&D_0026CE48)->p278 = s->prev;
            return;
        }
        if (g_saveData->reserveCount < 99) {
            g_saveData->pickupCount = 0;
            ((Sys_1481A0_eu*)&D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0_eu*)&D_0026CE48)->p278 = 0;
            ((Sys_1481A0_eu*)&D_0026CE48)->fn274 = AddReserveUnit;
            {
                VObj_1481A0* obj = (VObj_1481A0*)&D_0026C6C8;
                obj->vtbl[14](obj);
            }
        } else {
            g_saveData->pickupCount = 99;
        }
    }
}
