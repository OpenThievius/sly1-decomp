<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# The MMI and system helpers

The 37 `inline` functions whose special instructions are MMI or system ones, not VU0
(2026-11-08, build/swarm/lead/night/mmi.tsv), were matched as the VU0 ones were: plain C around
shared helpers.

- **The game's MMI needs no header of its own.** Its 19 functions use pextlw, pcpyld, pextuw
  and prot3w only in the GPR forms include/vu0.h already has: FromFloats (mfc1 x3, pextlw,
  pcpyld) for a vector built of three floats, Splat (pextlw twice) for one float in all four
  fields, and ToFloatMoved, ToFloatY (prot3w), ToFloatZ (pextuw with $zero) for a vector's lanes
  in a GPR. No include/mmi.h: none of pmaxw, pminw, por, qfsrv, mfsa, plzcw or a multu read
  through hi is in game code's C. Matched with them: SetWorldGravityZ, BuildUniformScaleAboutPoint,
  ResetFlagTable, HandleWorld5ModeColliderActivation, ResetTintBlendColliderOrientation,
  HandleModeWalkerActivation, func_00125BF0, SetRandomEffectSpin, InitIdLinkedObject,
  LaunchContactListObject, SetRangeRecordPosition and SetRangeRecordDirection, InitPlayer,
  MatrixToAxisAngle.
- **include/system.h** holds the system instructions, as static inline functions (C and C++
  include it: the libraries have .c files), each one volatile asm, as AGENTS.md allows hardware
  access to be: retail never schedules anything across them.

  | Helper | Sequence | Form | Users |
  | --- | --- | --- | --- |
  | `Sync()` | `sync` | no operands | DisableInterruptCause, EnableInterruptCause, DisableDmaInterrupt, EnableDmaInterrupt (after the system call), DefineDrawEnvironment (at the end), func_00210C38 (before starting the DMA) |
  | `SyncAndEnableInterrupts()` | `sync; ei` | no operands | the ends of the interrupt handlers WakeDiscWaiter, WakeCardWaiter, func_001F89F8, HandleGsFinish, HandleVblankStart, func_0015E6A8 (and the near misses HandleCommandInterrupt, func_00210F18) |
  | `ReadCop0Status()` | `mfc0 r, $12` | `"=r"` u32 | the four interrupt wrappers of system_calls.cpp, RefreshPadFrames |
  | `ReadCop0Count()` | `mfc0 r, $9` | `"=r"` u64 | ResetGameClockTick |

- **The status bit in its own register.** Retail's `mfc0 s0, $12; and s0, s0, v0` is a variable
  given the register and then masked in place: `u32 enabled = ReadCop0Status(); enabled &=
  0x10000;`; the mask written in the initialiser gives `mfc0 v1` and `and s0, v1, v0`.
- **Count is a doubleword.** Retail stores `mfc0`'s result with `sd` at once; mfc0
  sign-extends, so the helper's result is u64 (a u32 assigned to the u64 global adds the
  zero-extension).
- **Sibling calls.** The libraries' compiler (2.9-ee-991111, above) turns a call at the end into
  `j` after the epilogue: RefreshPadFrames and func_00210C38 end with `j EnableInterrupts`,
  plain C.
- **A constant set again before each call is an inline function's.** Retail sets the 1e-4
  tolerance of AreFloatsNearlyEqual (lui, ori, mtc1 $f14) again before each of a vector's three
  tests; the constant written at each call is shared by CSE in a saved FPR. An inline function
  that passes it (range_record.cpp's IsNearlyEqual) gives retail's code: each inlined body is a
  block of its own to CSE.
- **Tails merged by cross-jumping.** Code that two arms share after the registers are allocated
  is merged by jump.c's cross-jumping, leaving in each arm only what differs: MatrixToAxisAngle's
  sign fix of the largest axis z is written in both arms of the x test (retail negates x from the
  register both arms hold), and func_001478F0 (near miss) evaluates its curve in each arm, which
  leaves the arms' own `c[0]` loads in them, as retail's.
- **Data a DMA fills is volatile.** The command channel's receive buffer (HandleCommandInterrupt,
  near miss) is read with `lbu` then `andi 0xff`: a volatile byte, whose zero-extension combine
  leaves.
- **Statement order is store order.** In InitPlayer, InitIdLinkedObject and ResetFlagTable the
  stores of constants come out in the C's order (tools/permute.py found InitPlayer's last seven);
  DefineDrawEnvironment writes each register's address before its value, as retail stores them.
- **The assembler and a macro in a delay slot.** A store to a constant address whose low half is
  negative (`sw $3,0x1000b000`, a macro of lui and sw) that the assembler moves into a `jal`'s
  delay slot came out with the lui's carry lost (`lui at, 0x1000`, where retail has 0x1001; the
  same store outside a delay slot was right). The build corrects it: tools/volatile_slots.py, which
  already writes the `lui $at` / `jal` / `sw` of a volatile store into the call's slot, writes a
  constant address's high half itself, with the carry (`lui $1,4097`, `sw $3,-20480($1)`), instead
  of `%hi`/`%lo` of the bare constant, which this assembler takes without the carry. A symbol
  keeps `%hi`/`%lo`. Only the stores that tool moves into a slot are affected (func_00210F18, now
  matched).
- **Left as they are.** func_001F71D0 is the only function with an inline `syscall` (`li $3,
  -0x2F; syscall`, its result moved from $v0), so it has no helper (a sequence one function
  alone has). func_001FAA00 keeps its loop counter in $t9 across calls, which the compiler never
  does with a caller-saved register: it was written with a register variable or by hand, and is
  not C to match as it stands; its `mtc0 $6` and `sync.p` (the TLB's wired count) occur nowhere
  else.
