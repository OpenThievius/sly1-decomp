# The toolchain

The compiler, assembler and linker are proprietary. They are never committed,
and nothing in the repository is copied from them: you supply them, and the
tools find them outside the tree.

## What built the game

**SN Systems' GCC 2.95.3 for the PlayStation 2, compiling C++**, with
`-O2 -G0 -fno-exceptions`, assembled by the EE GNU assembler of the same era.
Measured on 2026-10-28 against seven retail functions of `SCUS_971.98` (a push
onto a list, an add-if-absent loop, a pop, two calls passing a data address, a
float update, and a function with saved registers and a local object): every
one is EXACT with this compiler, on US and on PAL.

| Compiler (folder under `lib/gcc-lib/ee/`) | Banner | The seven functions |
|---|---|---|
| `2.95.3` (sce_ps2_sdk_24) | GCC 2.95.3 SN BUILD 1.14 | 7 EXACT: **the one config/cflags.tsv names** |
| `2.96-ee-001003-1` (sce_ps2_sdk_24) | GCC 2.95.3 SN BUILD v1.07 | 7 EXACT |
| `2.95.2` (sce_ps2_sdk_24) | GCC 2.95.2 SN BUILD v2.74 | 7 EXACT |
| `2.9-ee-991111` (sce_ps2_sdk_24) | GNU 2.9-ee-991111b/r4 (Sony's) | 2 EXACT: it makes tail calls (`j` in place of `jal`) and saves registers in 8 bytes, where retail saves 16 (`sq`) |

The three SN builds agree on everything measured so far; SN BUILD 1.14 is the
working choice because it is the one other 2002 games of the period were built
with. A function that tells the SN builds apart is worth recording here.

What else was measured:

- **The assembler matters.** cc1plus leaves macros and hazards to the
  assembler. Compiled C goes through `ee/bin/as.exe`, the assembler the
  compiler driver runs, with the options the driver gives it (`-G0 -O2`):
  - `move` becomes `daddu`, as in retail; a modern GNU as writes `or`;
  - no `nop` after `mtc1` before the register is used (`li.s`, `cvt.s.w`), as
    in retail. `bin/ee-as.exe`, the same release (`2.9-ee-991111b`) in
    another build, puts one there: measured on `func_00158108` and
    `func_001A7290`, EXACT with `ee/bin/as.exe` only.

  Then GNU objcopy rewrites the object's symbol table in the order modern ld
  wants, without touching code.
- **`-fno-exceptions`.** Without it every file gets C++ exception frame records
  in `.data`; retail has only four such records, all in library code.
- **`-ffunction-sections`** is added to every file so that the build can put
  each function at its retail address (tools/c_layout.py). It changes no code.
- **The preprocessor** is the toolchain's `cpp.exe`, given the macros the
  compiler driver defines (tools/compile.py).

## Getting the compiler

Its Windows build is in the public mirror of Sony's SDK 2.4 tools. Clone it
outside the repository:

```sh
git clone https://github.com/AngheloAlf/sce_ps2_sdk_24 ~/toolchains/sn-prodg-24
ln -s ~/toolchains/sn-prodg-24/local/sce/ee/gcc toolchain     # or export SLY1_TOOLCHAIN=...
```

OpenThievius's `tools/openthievius.py setup` makes the `toolchain` link for you.
If you have an OpenRAC checkout, its `toolchains/sn-prodg-24` is the same mirror.

The Windows tools run on macOS and Linux through
[wibo](https://github.com/decompals/wibo) (or Wine): a `wibo` link in the
repository root, `SLY1_RUNNER`, or `wibo` on `PATH`. Both links are gitignored,
and `tests/check_repository.py` rejects them if they are ever staged.

```sh
python3 tools/toolchain.py      # finds the tools and compiles a test unit
```

The disassembly is assembled and linked by GNU binutils for mips
(`mips-linux-gnu-as`, `-ld`, `-objcopy`, `-objdump`; `brew install
mips-linux-gnu-binutils`, or your distribution's `binutils-mips-linux-gnu`),
with `-march=r5900 -mabi=eabi`. splat writes n32 register names for it.

## Still to qualify

1. **SN build.** A function that compiles differently under the three SN
   builds would settle which one retail used.
2. **Per-file flags.** `-O2 -G0 -fno-exceptions` is every file's default so
   far (config/cflags.tsv); a file that needs other options gets its own row,
   never a function.
3. **The libraries.** Sony's libraries and the compiler's runtime were linked
   from prebuilt archives and need other compilers or options. Their code is
   decompiled from retail like the rest: never from SDK source, headers or
   samples. Measured on 2026-10-29: the double-precision float support at
   0x1FB618–0x1FD6E0 makes tail calls and saves registers in 8 bytes, and
   five of its functions (`func_001FBDF8`, `func_001FCD20`, `func_001FCD78`,
   `func_001FD308`, `func_001FD548`) are EXACT with Sony's `2.9-ee-991111`,
   none with the SN builds. Those files need their own compiler row in
   config/cflags.tsv (and, being C, the release's `cc1`); tools/compile.py
   does not support a compiler per file yet, so they are not landed.

Record every result here: the function, the compiler, the flags, and whether
it matched.
