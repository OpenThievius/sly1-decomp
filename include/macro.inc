# SPDX-License-Identifier: AGPL-3.0-or-later
#
# The label macros of the disassembly (asm/<version>/), for GNU as. Every listing splat writes
# starts with `.include "macro.inc"`, and tools/build.py assembles it with include/ on the
# path. splat's own copy (generate_asm_macros_files) is off in config/splat/: these are the
# project's, written for the forms our listings use and nothing else. The toolchain's 1999
# assembler does not read them; tools/asm_func.py writes them out for the functions a whole file
# includes.

.ifndef SLY1_MACRO_INC
.set SLY1_MACRO_INC, 1

# glabel NAME: a function starts. A global function symbol, opened for the debugging directives.
.macro glabel name, binding=global
    .\binding "\name"
    .type "\name", @function
"\name":
    .ent "\name"
.endm

# endlabel NAME: a function ends; its size runs from its label to here.
.macro endlabel name
    .size "\name", . - "\name"
    .end "\name"
.endm

# alabel NAME: a second entry point inside a function.
.macro alabel name, binding=global
    .\binding "\name"
    .type "\name", @function
"\name":
    .aent "\name"
.endm

# jlabel NAME: a jump-table target inside a function.
.macro jlabel name, binding=global
    .\binding "\name"
"\name":
.endm

# dlabel NAME: a datum starts. A global object symbol.
.macro dlabel name, binding=global
    .\binding "\name"
    .type "\name", @object
"\name":
.endm

# enddlabel NAME: a datum ends; its size runs from its label to here.
.macro enddlabel name
    .size "\name", . - "\name"
.endm

# nonmatching NAME[, SIZE]: splat marks each symbol that is not yet C. The build takes every
# symbol without C from the disassembly anyway (tools/build.py), so the marker emits nothing.
.macro nonmatching name, size=1
.endm

.endif
