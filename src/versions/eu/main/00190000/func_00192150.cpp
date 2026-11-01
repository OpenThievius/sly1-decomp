// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: calls func_eu_001387C8 where US calls func_001384A0
void func_eu_001387C8(void* other, void* sub);
void func_00192150(void* self, void* other)
{
    func_00192068(self, other);
    func_eu_001387C8(other, (u8*)self + 0x50);
}
