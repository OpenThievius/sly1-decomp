// SPDX-License-Identifier: AGPL-3.0-or-later
// The last object of .text, 0x211DE0-0x211E0C, built whole (config/us/files.tsv): the pair of
// functions that register the program's exception frame information with the runtime
// (func_001FFBE0, in src/lib/unwind.c) at startup and take it back at exit. Retail's constructor
// list (D_0027B130) ends with func_00211DE0 and its destructor list (D_0027B180) with
// func_00211DF8. D_0027B198 is the linker's list of the objects with frame information; this
// file's only data is the runtime's bookkeeping record for it, the 0x18 bytes of .bss at
// D_0062C540. Written for this project from retail's code.
#include "common.h"

extern u8 D_0027B198[];

// The runtime's record of the registered frame information.
static u8 D_0062C540[0x18];

void func_001FFBE0(u8* begin, u8* object);
void func_001FFC08(u8* begin);

void func_00211DE0(void)
{
    RegisterFrameInfo(D_0027B198, D_0062C540);
}

void func_00211DF8(void)
{
    DeregisterFrameInfo(D_0027B198);
}
