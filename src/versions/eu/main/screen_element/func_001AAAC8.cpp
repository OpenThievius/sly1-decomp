// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: mode sits 784 (0x310) bytes further on than in US.
struct Obj_1AAAC8_eu { u8 pad[0x250 + 0x310]; s32 mode; };

s32 func_001AAAC8(Obj_1AAAC8_eu* a, Obj_1AAAC8_eu* b)
{
    s32 r = 0;
    s32 am = a->mode;
    if ((u32)(am - 1) < 2) { if ((u32)(b->mode - 1) < 2) goto yes; }
    if (am == 3) { if (b->mode == 3) goto yes; }
    if (b->mode == 3) { if (am == 2) goto yes; }
    goto done;
yes:
    r = 1;
done:
    return r;
}
