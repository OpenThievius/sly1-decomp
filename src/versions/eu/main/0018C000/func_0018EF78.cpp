// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two func_001615F0 calls pass 0x7800 and 0x8800 where US passes 0x7900 and 0x8700.
void func_0018EF78(void* self, s32 a1, s32 a2)
{
    Local_18EF78 buf;
    func_001611B8(&buf);
    func_001529C8(&buf, 0x12, self);
    func_00152B38(&buf);
    func_001613C0(&buf, 6, 1, 0xE);
    func_00161708(&buf, 6, 0x0AA8029E00ULL);
    func_00161708(&buf, 0x14, 0x61);
    func_00161708(&buf, 8, 5);
    func_00161708(&buf, 0x42, 0x44);
    func_00161708(&buf, 0x47, 0x31001);
    func_001613C0(&buf, 0x116, 5, 0xE4343);
    func_001614C8(&buf, 8, 8);
    func_001615F0(&buf, 0x6C00, 0x7800, 0, 0);
    func_001614C8(&buf, (a1 << 4) | 8, (a2 << 4) | 8);
    func_001615F0(&buf, 0x9400, 0x8800, 0, 0);
    func_00161708(&buf, 0x61, 0);
    func_00161200(&buf);
    func_00152D30(&buf);
    func_001529E0(&buf, 0, 0);
}
