# For whoever ports the game

This repository is a matching decompilation: its C++ exists to rebuild retail's bytes with the
period compiler (docs/TOOLCHAIN.md), so it keeps only code that does. A portable implementation
of anything below belongs in a port, not here. This page says where the PS2-specific parts are;
it does not say how to port.

## The vector seam: include/vu0.h

Every vector operation of the game's code goes through the helpers of include/vu0.h
(`Vu0::Vec`, `Vu0::Add`, `Vu0::Dot`, `Vu0::Rotate`, `Vu0::Transform`, ...) and a few of
include/fpu.h (`Fpu::Sqrt`). They exist so that retail's VU0 macro-mode instructions come out
of plain C++; their bodies are one `__asm__` statement of VU0 instructions each.

- Each helper's comment ends in a "Computes:" line: the result per lane (x, y, z, w), which lanes
  are not defined, which lane a broadcast form uses, the accumulator expression, and the
  behaviour of `vdiv` and `vsqrt` at zero and negative inputs. The header's top comment
  lists the VU0 float conventions (no infinity or NaN, rounding toward zero, denormals as zero).
- A port replaces the header: the same names and signatures with portable bodies. Callers pass
  vectors as `u128`/`Vu0::Vec` values and as 16-aligned 16-byte objects in memory, so the
  replacement also decides what a vector value is (four floats, a SIMD register).
- Not everything in it is arithmetic. The `ToFloat*`, `ToBits`, `FromFloat*`, `Scalar*`,
  `Splat`, `FromFloats`, `Transpose` and `StoreX` helpers are moves between GPRs, FPU and VU0
  registers or MMI shuffles; several of them (`Scalar`, `ScalarInGpr`, `ScalarAt*`) exist only
  to place a stack store or a load as retail did, and are plain float-to-vector conversions in
  meaning.
- Two interfaces are not arithmetic at all: `Vu0::ParticleFilter` (the microprogram at 0x10)
  and `Vu0::NextLightGroup` with `LoadVf`, `CallMs`, `MoveToVi` and `ReadViWait` (the light
  test microprograms at 0x60 and 0x168). Each is used by one function
  (`FilterParticleVerticesVu0`, `CollectLightsForSphere`); a port reimplements the
  microprograms' work in those two functions.
- The few other single-function exceptions of AGENTS.md ("Matching rules") are
  `Vu0::ScalarInGprAt`, `ScalarMovedReg` and `ScalarMoved` (conversions of a float to a vector),
  `SetTlbWired` and `CurrentThreadIdFromInterrupt` (include/system.h, system calls of the kernel
  library), and `func_001FAA00`'s register variable; none changes what its function computes.

## The other PS2-specific parts

| What | Where |
| --- | --- |
| VU microprograms (VU0 and VU1 microcode) | `.vutext` (0x211E10, 0x5550 bytes in the US executable, docs/VERSIONS.md), counted as original assembly; not decompiled, no C of them exists |
| Hand-written assembly functions and linker leftovers | `config/us/original_asm.tsv` (`config/eu/original_asm.tsv` for PAL's own), marked `ASM_FUNC` and `LINKER_REMNANT` in the sources (include/asm_func.h, docs/ASM_CLASSIFICATION.md); a port reimplements each from its role in the name tables |
| Graphics: GS and VIF packet building, DMA chains | game code writes the packets with the packet writer (`g_vifPacketWriter`, include/globals.h; `AddDmaEndTag`, `SubmitPacketBuffer` in src/main) and the DMA helpers of src/lib (`dma.c`, `graph.c`); the packets' contents are the PS2's GIF, VIF and DMA formats |
| Sony libraries (kernel calls, IOP clients, memory card, pad, CD, IPU and MPEG, the C and C++ runtime) | `src/lib/` (`system_calls.cpp`, `iop_*`, `memory_card_client.cpp`, `cdvd.c`, `pad.c`, `ipu_*`, `mpeg_*`, `exception.cpp`, `unwind.c`...), built with Sony's compiler; the IOP side's modules are on the disc and are not here |
| The math library | `src/libm/`, the toolchain's own C library functions; a port uses its platform's |
| Hardware registers and scratchpad | `volatile` accesses at fixed addresses (`*(volatile u32*)0x10002010`), DMA channel blocks, the scratchpad transfers (`StartToSprChain`, `StartFromSprChain`) |
| Inline-assembly helpers other than vu0.h | include/system.h (system and MMI instructions), include/mul_wide.h (`MUL_WIDE`, the runtime's multiply with hi and lo), include/fpu.h |
| A stand-in statement | `func_0020BB18` (AllocatePictureBuffers, src/lib/mpeg_decoder.cpp): a test that is never true, there only because retail's code needs the instruction it leaves; it is not the original's statement (AGENTS.md) |

## Data and types a port meets

- **32-bit pointers.** The PS2's pointers are 32 bits, and the structures keep retail's layouts,
  so their `sizeof` checks (`check_X` typedefs) assume 4-byte pointers. Where the code keeps an
  address in an integer, because a pointer type would change retail's code, the integer is
  `sptr` or `uptr` (include/common.h): retail's `s32` and `u32` here, `intptr_t` and `uintptr_t`
  in a port on 64-bit pointers, which changes only those two lines. They hold the property
  descriptors' getters and setters (include/property_descriptor.h), the list walks' frames
  (`WordListFrame`, include/list_iter.h), the stream readers' buffer addresses
  (include/stream_reader.h, include/buffered_stream.h), the spawners' arrays (`SpawnSetup`), the
  value tree's children (`PlaneNode`, src/main/warp_menu.cpp), and the address arithmetic that
  aligns a buffer or indexes an array of pointers (`i * sizeof(void*) + (uptr)arr`). A pointer
  stored at an address the code does not trust to be aligned is `PtrP` (include/shapes.h).
  What still carries an address in 32 bits:
  - **script values.** The script machine's integer (`ScriptValue::i`, tag 0x14) holds object
    and sound-level handles (PushSoundLevelBuiltin, ReadPropertyValue's property references):
    a port makes the value's word pointer-sized or hands scripts a handle table;
  - **the hardware's words**: DMA tags and channel addresses (`g_vif0Channel` and the other
    channels in src/main/pooled_object.cpp, `dma.c`), the uncached `0x20000000` segment, the
    IOP request words and the VU microcode addresses, all of which a port replaces with its own
    graphics, sound and file layers;
  - the free-function declarations PR #148 left (its description lists them), which a normal
    linker reports.
- **128-bit values** are `u128` (`unsigned int` with `mode(TI)`, include/vu0.h): four 32-bit
  lanes in one register, with the 16-byte alignment `lqc2`, `sqc2`, `lq` and `sq` need. The
  structures that hold vectors are 16-aligned; a port keeps the alignment if it uses SIMD loads.
- **Names** are macros from `config/names/` (docs/NAMING.md); the readable name and the address
  name are the same symbol.
- **Floats** follow the EE's and VU0's rules (rounding toward zero, no infinity or NaN,
  denormals as zero): see the top of include/vu0.h and `Fpu::Sqrt`. Where the game's behaviour
  depends on them (saturating divisions, the square root of a negative), the "Computes:" lines
  say so. These float rules come from public descriptions of the hardware and are not proved by
  the decompilation, which checks bytes, not arithmetic: test them before relying on them.

## Sound

The game's sound runs on the IOP, in Sony's sound driver, which is not part of the
executable and is not decompiled. The game's side is: it loads a bank by its start sector,
starts a sound by bank handle and record number with a volume and pitch word, and adjusts and
stops the voice the driver returns (docs/DISC.md, "Sound banks", lists the calls and the
banks' layout). A port does as OpenRAC's port does: it answers those calls with its own sound
engine, which reads the banks and decodes their SPU ADPCM samples itself, and it must answer
every call the game waits on: src/main/iop_commands.cpp loops until a call is no longer
pending or its reply word is no longer -1, and hangs on a call no one answers.

## A warning for anyone editing include/vu0.h
Adding or removing lines in include/vu0.h can change the compiled code of a function that
includes it: inserting three comment lines near the top made func_001D7778 (StepPathFollower)
differ, and the same lines folded into existing ones did not (2026-11-13). The cause is not
yet traced (line positions reach some pass through the inline helpers' expansion). Rebuild with
tools/build.py after any edit to the header, comments included.

## Where to read more

docs/toolchain/vu0-helpers.md (why each helper is built as it is), docs/toolchain/mmi-system-helpers.md,
docs/ASM_CLASSIFICATION.md, docs/VERSIONS.md (the sections of each version), and the class and
table maps in `config/us/` (AGENTS.md's table).
