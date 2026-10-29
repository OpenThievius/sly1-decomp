// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: branch scheduling differs from retail around the nullable output.
#include "common.h"
void func_0011EF90(void* unused, s32* first, s32* second)
{
    if (second == 0) {
        *first = 0;
    } else {
        *first = 0;
        *second = 0;
    }
}
