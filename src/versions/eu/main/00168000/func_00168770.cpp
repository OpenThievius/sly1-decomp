// SPDX-License-Identifier: AGPL-3.0-or-later
// Clears the screen with a colour: a GS packet of sprite-block fills; PAL uses other VRAM bases.
void func_00168770(Self_168770* self, u8* color, s32 flag)
{
    Packet_168770 f;
    s32 x;

    func_001611B8(&f);
    func_001529C8(&f, 0x2C, self);
    func_001613C0(&f, (s8)color[3] >= 0 ? 0x46 : 6, 1, 0xE);
    func_00161708(&f, 1, (u64)color[0] | ((u64)color[1] << 8) | ((u64)color[2] << 16) | ((u64)color[3] << 24));
    func_00161708(&f, 0x47, flag != 0 ? 0x32001 : 0x32000);
    for (x = 0; x < 0x280; x += 0x20) {
        func_00161708(&f, 5, (u64)((0x6C0 + x) << 4) | ((u64)(0x780 << 4) << 16));
        func_00161708(&f, 5, (u64)((0x6E0 + x) << 4) | ((u64)(0x880 << 4) << 16));
    }
    func_00161708(&f, 0x47, 0x70000);
    func_00161200(&f);
}
