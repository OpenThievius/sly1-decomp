// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the format character as an unsigned byte (lbu where US has lb)
struct Fmt_1E1028_eu {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8 pad20[0xC];
    u8 mode;
    u8 pad2D[3];
    s32 f30;
};
s32 func_001E0E18(Fmt_1E1028_eu* self, Val_1E1028* v);
s32 func_001E0EF8(u8 c);

void func_001E1028(Fmt_1E1028_eu* self, Sink_1E1028* sink, u64 value)
{
    char buf[0x50];
    char pfx[0x10];
    char padc[0x10];
    Val_1E1028 val;
    s32 total;
    s32 lead;
    s32 trail;
    s32 zeros;
    s32 plen;
    s32 ndig;
    s32 n;

    val.v = value;
    if (self->f14 != 0 || self->f1C != 0) {
        self->f10 = 0;
    }
    if (self->f14 != 0 && val.v == 0) {
        plen = 0;
        zeros = 0;
        ndig = 0;
    } else {
        s32 neg = func_001E0E18(self, &val);
        zeros = self->f1C;
        pfx[0] = 0;
        switch ((u8)self->mode) {
        case 'd':
        case 'i':
            if (neg) {
                *(u16*)pfx = D_0024E3D0;
            } else if (self->f4) {
                *(u16*)pfx = D_0024E3D8;
            } else if (self->f8) {
                *(u16*)pfx = D_0024E3E0;
            }
            zeros -= func_001E2100(pfx);
            break;
        case 'b':
            if (self->fC) {
                *(u16*)pfx = *(u16*)D_0024E3E8;
                pfx[2] = D_0024E3E8[2];
            }
            break;
        case 'o':
            if (self->fC) {
                *(u16*)pfx = D_0024E3F0;
            }
            break;
        case 'x':
            if (self->fC) {
                *(u16*)pfx = *(u16*)D_0024E3F8;
                pfx[2] = D_0024E3F8[2];
            }
            break;
        }
        plen = func_001E2100(pfx);
        ndig = func_001E0F58(buf, 0x40, val.v, func_001E0EF8(self->mode));
        zeros -= ndig;
        zeros = zeros >= 0 ? zeros : 0;
    }
    buf[ndig] = 0;
    if (self->f30) {
        func_001E2218(pfx);
        func_001E2218(buf);
    }
    total = plen + zeros + ndig;
    lead = 0;
    trail = 0;
    if (total < self->f18) {
        s32 rem = self->f18 - total;
        if (self->f0) {
            trail = rem;
        } else if (self->f10 == 0) {
            lead = rem;
        } else if (ndig != 0) {
            zeros += rem;
        } else {
            lead = rem;
        }
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (func_001D7190(sink, padc, 1) != 1) {
            break;
        }
    }
    func_001D7190(sink, pfx, plen);
    padc[0] = '0';
    n = zeros;
    while (n-- > 0) {
        if (func_001D7190(sink, padc, 1) != 1) {
            break;
        }
    }
    func_001D7190(sink, buf, ndig);
    padc[0] = ' ';
    n = trail;
    while (n-- > 0) {
        if (func_001D7190(sink, padc, 1) != 1) {
            break;
        }
    }
}
