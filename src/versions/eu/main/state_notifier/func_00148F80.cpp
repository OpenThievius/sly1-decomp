// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f26C, f274 and f278 are at 0x57C, 0x584 and 0x588 (US 0x26C, 0x274, 0x278).
typedef void (*VFn_148F80)(void* self);
struct Obj_148F80_eu {
    VFn_148F80* vtbl;
    u8 pad004[0x57C - 0x004];
    f32 f26C;
    s32 f270;
    s32 f274;
    s32 f278;
};

void AddReserveUnitNow(void* self)
{
    Obj_148F80_eu* obj = (Obj_148F80_eu*)&g_reserveCountCaption;
    obj->vtbl[14](obj);
    GameProgress* g = g_saveData;
    if (g->reserveCount < 0x63) {
        g->reserveCount = g->reserveCount + 1;
        obj->f26C = 250.0f;
        obj->f274 = 0;
        obj->f278 = 0;
    } else {
        g->reserveCount = 0x63;
    }
}
