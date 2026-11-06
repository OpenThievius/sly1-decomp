// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: in D_0026F808 the pointer slot is at 0x570 and the table at 0x574 (US 0x260, 0x264).
struct Tbl_1F0660_eu { u8 pad0[0x574]; void* f574[1]; };

void func_001F0660(C67* o) {
    StartPlacedObject(o);
    o->flags = (o->flags & ~(3UL << 40)) | (1UL << 40);
    if (g_saveData->f19D8) {
        u8* t = (u8*)&g_mapScreenList;
        ((Ptr_1F0660*)(t + 0x570))->p = o;
    }
    switch (o->id) {
    case 0x1C7: o->slot = 1; break;
    case 0x1C8: o->slot = 2; break;
    case 0x1C9: o->slot = 3; break;
    case 0x1C6: o->slot = 4; break;
    case 0x1CA: o->slot = 5; break;
    default: o->slot = g_saveData->f19D8; break;
    }
    ((Tbl_1F0660_eu*)&g_mapScreenList)->f574[o->slot] = o;
}
