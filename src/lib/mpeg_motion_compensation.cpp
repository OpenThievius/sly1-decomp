// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's hand-written motion compensation, the whole object, 0x20D138-0x20DEE8
// (config/us/files.tsv): sixteen routines in the EE's 128-bit multimedia instructions that fetch
// and average a prediction block, whole or half pixel, for each kind of motion (retail's two
// tables at D_0027B000 and D_0027B020 point to them, func_0020CAF8 calls through them), and the
// two that add the prediction to the decoded residual and saturate the result (func_0020DE28,
// func_0020DE88, with their constant at D_0020DED0 in .text). All of it is original assembly
// (config/us/original_asm.tsv).
#include "asm_func.h"

ASM_FUNC(func_0020D138);

ASM_FUNC(func_0020D1B0);

ASM_FUNC(func_0020D248);

ASM_FUNC(func_0020D300);

ASM_FUNC(func_0020D3D0);

ASM_FUNC(func_0020D480);

ASM_FUNC(func_0020D538);

ASM_FUNC(func_0020D630);

ASM_FUNC(func_0020D730);

ASM_FUNC(func_0020D7D0);

ASM_FUNC(func_0020D880);

ASM_FUNC(func_0020D960);

ASM_FUNC(func_0020DA48);

ASM_FUNC(func_0020DB20);

ASM_FUNC(func_0020DBF0);

ASM_FUNC(func_0020DD10);

ASM_FUNC(func_0020DE28);

ASM_FUNC(func_0020DE88);
