// SPDX-License-Identifier: AGPL-3.0-or-later
// An original assembly function inside a whole file (config/us/files.tsv). Written for this
// project. The function was not made from C (docs/ASM_CLASSIFICATION.md), but the original file
// held it between its C functions, so the whole file's object holds it at its place:
// `INCLUDE_ASM(func_X);` at file scope, in retail's order. tools/compile.py writes the included
// file from the disassembly (tools/asm_func.py). This is not inline assembly in a function.
// A function of the file's range that is not matched yet is included the same way until its C
// matches; it counts as unmatched (tools/build.py, tools/progress.py).
#ifndef ASM_FUNC_H
#define ASM_FUNC_H

#define INCLUDE_ASM(NAME)                                                                   \
    __asm__(".section .text\n\t.set noat\n\t.set noreorder\n\t.include \"build/us/asm_func/" #NAME \
            ".s\"\n\t.set reorder\n\t.set at")

// The read-only data at a label that only original assembly uses (a jump table into an assembly
// function, a constant it loads), included in the whole file's .rodata in retail's order.
// The same for a .data label that only original assembly (or a function not matched yet) uses.
#define INCLUDE_DATA(LABEL)                                                                  \
    __asm__(".section .data\n\t.include \"build/us/asm_func/" #LABEL ".s\"\n\t.section .text")

#define INCLUDE_RODATA(LABEL)                                                                \
    __asm__(".section .rodata\n\t.include \"build/us/asm_func/" #LABEL ".s\"\n\t.section .text")

#endif
