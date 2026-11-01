// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two slots written in D_0026D348 on code 0x3F3 are at 0x574 and 0x578 (not 0x264 and 0x268).
void func_00197F10(Obj_197F10* self, s32 kind, void* rec)
{
    s32 code;
    func_00192230(self, kind, rec);
    switch (kind) {
    case 0xB:
        self->f644 = 0;
        return;
    case 0xA:
        self->f644 = *(s32*)rec;
        return;
    case 0x14:
        if (rec != self->f6B8) {
            return;
        }
        func_001B6598(rec, &code);
        if (code == 0x3F3) {
            u8* tbl;
            *(void**)D_0026E744 = (u8*)self + 0x67C;
            tbl = (u8*)&D_0026D348;
            *(void**)(tbl + 0x574) = (u8*)self + 0x680;
            *(void**)(tbl + 0x578) = (u8*)self + 0x684;
            func_001DDC38(self->f14, self);
            func_001AB890(&D_0026E760, self->f688);
            func_001AB928(&D_0026E760, 0.0f, (void*)func_00197458);
            func_001AB938(&D_0026E760);
        } else {
            if (code < 0x3F3) {
                return;
            }
            if (code < 0x3F6) {
                func_001AB958(&D_0026E760);
                ((Vt_197F10*)&D_0026D348)->vtbl[15](&D_0026D348);
                ((Vt_197F10*)&D_0026E4E0)->vtbl[15](&D_0026E4E0);
                ((Vt_197F10*)&D_0026E760)->vtbl[15](&D_0026E760);
                func_001DDC38(self->f14, 0);
            }
        }
        return;
    }
}
