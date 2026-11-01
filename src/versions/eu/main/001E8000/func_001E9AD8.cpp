// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two gate fields of each global are at 0x560 and 0x56C (US 0x250, 0x25C).
struct Gate_1E9AD8_eu { u8 pad0[0x560]; s32 f560; u8 pad1[8]; s32 f56C; };

extern s32 D_00275F84;
extern u8 D_0026FF68[];
extern u8 D_0026F808[];

s32 func_001E9AD8(void)
{
    if (D_00275F84 != 0) goto fail;
    if (((Gate_1E9AD8_eu*)D_0026FF68)->f56C != 0) goto fail;
    if (((Gate_1E9AD8_eu*)D_0026FF68)->f560 != 0) goto fail;
    if (((Gate_1E9AD8_eu*)D_0026F808)->f56C != 0) goto fail;
    if (((Gate_1E9AD8_eu*)D_0026F808)->f560 == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}
