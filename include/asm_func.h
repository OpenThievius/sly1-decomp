// SPDX-License-Identifier: AGPL-3.0-or-later
// An original assembly function inside a whole file (config/us/files.tsv). Written for this
// project. The function was not made from C (docs/ASM_CLASSIFICATION.md), but the original file
// held it between its C functions, so the whole file's object holds it at its place:
// `INCLUDE_ASM(func_X);` at file scope, in retail's order. tools/compile.py writes the included
// file from the disassembly (tools/asm_func.py). This is not inline assembly in a function.
#ifndef ASM_FUNC_H
#define ASM_FUNC_H

#define INCLUDE_ASM(NAME)                                                                   \
    __asm__(".section .text\n\t.set noat\n\t.set noreorder\n\t.include \"build/us/asm_func/" #NAME \
            ".s\"\n\t.set reorder\n\t.set at")

#endif
