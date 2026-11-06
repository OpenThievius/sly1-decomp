// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the path's characters are read as unsigned bytes.
s32 func_001407A8(s8* path)
{
    u8* p = (u8*)path;
    UppercaseString(path);
    s32 len = GetStringLength(path);
    if (len != 0) {
        u8 last = p[len - 1];
        if (last != '\\' && last != '/') {
            AppendString(path, ";1");
            len = GetStringLength(path);
        }
    }
    u8* end = p + len;
    u8* out = p;
    u8* in = p;
    s32 count = 0;
    s32 n = 0;
    s32 max = 8;
    while (in < end) {
        switch (*in) {
        case '/':
        case '\\':
            if (n != 0) {
                *out++ = 0;
                n = 0;
                max = 8;
                count++;
            }
            break;
        case '.':
            if (n != 0 && max == 8) {
                *out++ = *in;
                n = 0;
                max = 3;
            }
            break;
        case ';':
            if (n != 0 && in == end - 2 && in[1] == '1') {
                *out++ = *in++;
                *out++ = *in;
                n += 2;
                break;
            }
        default:
            if (n < max) {
                if ((*in >= 'A' && *in <= 'Z') || (*in >= '0' && *in <= '9')) {
                    *out++ = *in;
                } else {
                    *out++ = '_';
                }
                n++;
            }
            break;
        }
        in++;
    }
    if (n != 0) {
        *out = 0;
        count++;
    }
    return count;
}
