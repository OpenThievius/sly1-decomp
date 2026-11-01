// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 144/176, checked 2026-11-01
// Near match: the volatile status polling and timeout helper are modeled, but
// GCC removes retail's saved-register frame and emits a shorter polling shape.
// Artificial register pins and barriers are prohibited by the workflow.
#include "common.h"

void func_0020B1E0(s32 value);
s32 func_0020F198(void* self)
{
    volatile s64* status = (volatile s64*)0x10002000;
    volatile u32* flags = (volatile u32*)0x10002010;
    s64 value = *status;
    if (value < 0) {
        if ((*flags & 0x4000) == 0) {
            s32 count = 0;
            while (1) {
                if (count >= 0x1389) {
                    func_0020B1E0(*(s32*)((u8*)self + 0x858));
                    count = 0;
                }
                count++;
                value = *status;
                if (value >= 0) break;
                if ((*flags & 0x4000) != 0) break;
            }
        }
    }
    return (s32)value;
}
