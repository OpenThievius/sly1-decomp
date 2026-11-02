// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 446/448 (99.6%), checked 2026-11-02
#include "common.h"
// NEAR: 2 instructions differ: the two `move $t0/$t1, zero` that clear count and n before the loop come out in the other order (retail clears count, $t0, first). Declaring count first swaps the registers as well; every order of the six initialisers (tools/permute.py), declaring them at the top, chained assignments, for/do-while forms and u32 count leave it. The andi in the A-Z/0-9 tests needed the char re-read through *in rather than a u8 local.

void func_001E2218(s8* p);
s32 func_001E2100(const s8* s);
void* func_001E2180(s8* dst, const char* src);

s32 func_001407A8(s8* path)
{
    func_001E2218(path);
    s32 len = func_001E2100(path);
    if (len != 0) {
        s8 last = path[len - 1];
        if (last != '\\' && last != '/') {
            func_001E2180(path, ";1");
            len = func_001E2100(path);
        }
    }
    s8* end = path + len;
    s8* out = path;
    s8* in = path;
    s32 n = 0;
    s32 count = 0;
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
                if ((u8)(*in - 'A') < 26 || (u8)(*in - '0') < 10) {
                    *out = *in;
                } else {
                    *out = '_';
                }
                out++;
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
