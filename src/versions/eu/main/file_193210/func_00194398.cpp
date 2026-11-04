// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the text is element D_eu_00263710 (32 bytes each) of the table at D_00247AB0
extern s32 D_eu_00263710;
void func_00194398(void)
{
    Args_194398 args;
    args.kind = 1;
    args.text = D_00247AB0 + D_eu_00263710 * 32;
    args.x = -1;
    args.y = -1;
    args.z = 4;
    func_001EFFA0(D_00275F80, &args, 0);
}
