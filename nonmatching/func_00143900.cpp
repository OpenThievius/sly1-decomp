// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: passing the literal zero emits an extra argument setup instruction.
#include "common.h"
extern void func_001448C8(void*, s32, void*);
void func_00143900(void* arg) { func_001448C8(arg, 0, 0); }
