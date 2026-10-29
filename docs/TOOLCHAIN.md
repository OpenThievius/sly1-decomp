# The toolchain

The compiler, assembler and linker are proprietary. They are never committed,
and nothing in the repository is copied from them: you supply them, and the
tools find them outside the tree.

## What built the game

The working assumption is **Sony's GNU EE GCC 2.9-ee-991111b**, compiling the
game as **C++** with `cc1plus`. What points there:

| Evidence | What it shows |
|---|---|
| Retail has a `.gcc_except_table` section | the code is C++, built by GCC |
| ELF flags `0x20924001` (noreorder, eabi64, 5900, mips3) | GNU EE toolchain for the R5900 |
| `.vutext` and `.DVP.overlay..*` sections | VU code assembled by the GNU EE tree's `dvp-as` |
| The disc's release date (August 2002) | 2.9-ee-991111b was Sony's EE GCC of that time |
| The May 2002 prototype's debug information names the same assembler release | a hint only: it is not the build we match |

None of this is proof. The proof is retail functions compiling to retail's
bytes (below).

## Getting the compiler

Its Windows build is in the public mirror of Sony's SDK 2.4 tools. Clone it
outside the repository:

```sh
git clone https://github.com/AngheloAlf/sce_ps2_sdk_24 ~/toolchains/sn-prodg-24
export SLY1_TOOLCHAIN=~/toolchains/sn-prodg-24/local/sce/ee/gcc
```

`$SLY1_TOOLCHAIN/lib/gcc-lib/ee/2.9-ee-991111/cc1plus.exe` reports
`GNU C++ version 2.9-ee-991111b/r4 (ee)`. A `toolchain` link in the repository
root works instead of the variable; git ignores it, and
`tests/check_repository.py` rejects any link or toolchain file that gets
staged. OpenThievius's `tools/openthievius.py setup` makes the link for you.

The Windows tools run on macOS and Linux through
[wibo](https://github.com/decompals/wibo), or Wine. Put `wibo` on `PATH` or set
`SLY1_RUNNER`:

```sh
python3 tools/toolchain.py
# toolchain: .../local/sce/ee/gcc
# cc1plus:   .../lib/gcc-lib/ee/2.9-ee-991111/cc1plus.exe
# runner:    .../wibo
# version:   GNU C++ version 2.9-ee-991111b/r4 (ee) compiled by CC.
# ok: the compiler runs and is 2.9-ee-991111b
```

Checked on 2026-10-28 on macOS (Apple silicon) with wibo 1.2.0's macOS build.

## Still to qualify

1. **The compiler build.** Write C++ for a set of small retail functions,
   compile it with `cc1plus.exe` and compare instruction by instruction. If
   the Windows r4 build does not match, the next candidate is the same
   release rebuilt from GNU's public EE GCC source, with any changes written
   and measured by this project.
2. **The flags.** `-O2 -G0` is the starting guess (`tools/toolchain.py`,
   `DEFAULT_FLAGS`). Retail has no `.sdata` and only 0x2C bytes of `.sbss`,
   which suggests `-G0` for the game code, but that is unproven. Flags are set
   per source file, never per function.
3. **The assembler and linker.** `ee-as` and `ee-ld` of the same tree, or a
   free binutils that gives the same bytes.
4. **The libraries.** Sony's libraries were linked from prebuilt archives.
   Their code in the retail executable is decompiled like the rest: never from
   SDK source, headers or samples.

Record every result here: the function, the compiler, the flags, and whether
it matched.
