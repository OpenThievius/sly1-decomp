// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: crc, cur and remain sit at 0x14C, 0x150 and 0x154 (not 0x138, 0x13C and 0x140).
struct Obj_18F610_eu {
    u8 pad0[0x14C];
    u32 crc;
    u8* cur;
    s32 remain;
};

void func_0018F610(Obj_18F610_eu* self)
{
    if (self->remain > 0) {
        s32 n = self->remain - 4;
        u32* tab = (u32*)D_005A2E60;
        u8* p = self->cur;
        u8* nxt = p + 4;
        u32 c0 = self->crc;
        u32 c1, c2, c3;

        c1 = tab[(c0 ^ p[0]) & 0xff] ^ (c0 >> 8);
        self->crc = c1;
        c2 = tab[(c1 ^ p[1]) & 0xff] ^ (c1 >> 8);
        self->crc = c2;
        self->remain = n;
        c3 = tab[(c2 ^ p[2]) & 0xff] ^ (c2 >> 8);
        self->crc = c3;
        u32 t = tab[(c3 ^ p[3]) & 0xff];
        self->cur = nxt;
        u32 c = t ^ (c3 >> 8);
        self->crc = c;
        if (n == 0 && c != 0) {
            *(s32*)D_00269B48 = 1;
        }
    }
}
