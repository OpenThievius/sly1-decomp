// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: writes up to count bytes of buf into the IOP's ring, block by block; for kind 0x10 it first rearranges the columns and marks the slot of each block in the data.
struct Obj_eu_18EF40 {
    u8 pad0[4];
    s32 kind;
    u8 pad8[4];
    s32 cols;
    u8 pad10[4];
    s32 f14;
    s32 f18;
    s32 f1C;
    u8 pad20[4];
    s32 f24;
    s32 f28;
    s32 f2C;
};

void GroupRingBlockColumns(Obj_eu_18EF40* self, s32 len, u8* dst);
s32 WriteIopRingBlockByKind(Obj_eu_18EF40* self, s32 size, u8* buf);

s32 PutIopRingSinkByKind(Obj_eu_18EF40* self, s32 count, u8* buf)
{
    s32 n = count;
    s32 total = 0;
    s32 left = n;
    s32 r;

    if (left <= 0 || self->f24 < left) {
        left = self->f24;
    }
    if (self->kind == 0x10) {
        left &= -(self->cols << 10);
        GroupRingBlockColumns(self, left, buf);
    } else {
        left &= -0x400;
    }
    while (left != 0) {
        s32 chunk;
        s32 avail = self->f18 - self->f1C;
        if (left < avail) {
            chunk = left;
        } else {
            chunk = avail;
        }
        u8* dst = buf + total;
        if (self->kind == 0x10) {
            s32 slot = self->f2C / 1024 / self->cols % 4;
            chunk = 0x400;
            if (slot == 0) {
                dst[1] = 6;
                dst[0x11] = 2;
            } else if (slot == 3) {
                dst[0x3F1] = slot;
            }
        }
        r = WriteIopRingBlockByKind(self, chunk, dst);
        if (r == 0) {
            break;
        }
        total += r;
        left -= r;
        self->f1C += r;
        self->f1C = self->f1C % self->f18;
        self->f28 += r;
        self->f24 -= r;
        self->f2C += r;
        if (n <= 0) {
            break;
        }
    }
    return total;
}
