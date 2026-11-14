// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the format string as unsigned bytes (lbu where US has lb)
s32 ParseSignedDecimal(u8* s, s32* out);

s32 ParseFormatSpec(u8* at, FormatSpec* spec, s32** va)
{
    s32 state = 0;
    u8* p = at;
    s32 next;

    FillMemory(spec, 0, 0x34);
    if (*at != 0) {
        for (;;) {
            s32 adv = 0;
            next = state;
            switch (state) {
            case 0: {
                u8 c = *p;
                if (c != 0x25) {
                    next = 6;
                } else {
                    u8 d = p[1];
                    next = 1;
                    if (d == c) {
                        spec->conv = d;
                        next = 6;
                        adv = 2;
                    } else {
                        adv = 1;
                    }
                }
                break;
            }
            case 1:
                switch (*p - 0x20) {
                case 13:
                    spec->left = 1;
                    adv = 1;
                    break;
                case 11:
                    spec->plus = 1;
                    adv = 1;
                    break;
                case 0:
                    spec->space = 1;
                    adv = 1;
                    break;
                case 3:
                    spec->alt = 1;
                    adv = 1;
                    break;
                case 16:
                    spec->zero = 1;
                    adv = 1;
                    break;
                default:
                    next = 2;
                    break;
                }
                break;
            case 2:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    spec->width = w;
                    if (w < 0) {
                        w = (w < 0) ? -w : w;
                        spec->left = 1;
                        spec->width = w;
                    }
                    adv = 1;
                } else {
                    adv = ParseSignedDecimal(p, &spec->width);
                }
                if (p[adv] == 0x2E) {
                    next = 3;
                    adv++;
                } else {
                    next = 4;
                }
                break;
            case 3:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    adv = 1;
                    w = (w < 0) ? -w : w;
                    spec->prec = w;
                } else {
                    adv = ParseSignedDecimal(p, &spec->prec);
                }
                spec->noprec = spec->prec == 0;
                next = 4;
                break;
            case 4: {
                switch (*p - 0x4C) {
                case 28:
                    spec->length = 1;
                    adv = 1;
                    break;
                case 32:
                    adv = 1;
                    if (p[1] != 0x6C) {
                        spec->length = 2;
                        break;
                    }
                    // fall through
                case 0:
                case 37:
                    spec->length = 2;
                    adv++;
                    break;
                case 1:
                case 10:
                case 33:
                case 42: {
                    s32 a = 3;
                    s32 r = 1;
                    s32 d;
                    s32 l;
                    if (g_charClassFlags[*p] & 1) {
                        a = 4;
                    }
                    spec->vectorCount = a;
                    d = *p;
                    l = (g_charClassFlags[d] & 1) ? d + 0x20 : d;
                    if (l ^ 0x76) {
                        r = a;
                    }
                    spec->matrixRows = r;
                    adv = 1;
                    break;
                }
                default:
                    break;
                }
                next = 5;
                break;
            }
            case 5:
                if (*p != 0x25) {
                    s32 e = *p;
                    s32 f;
                    s32 l;
                    spec->upper = g_charClassFlags[e] & 1;
                    f = *p;
                    l = (g_charClassFlags[f] & 1) ? f + 0x20 : f;
                    spec->conv = l;
                }
                adv = 1;
                next = 6;
                break;
            default:
                return p - at;
            }
            p += adv;
            state = next;
            if (*p == 0 || next == 6) {
                break;
            }
        }
    }
    return p - at;
}
