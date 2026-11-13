// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 60/64, checked 2026-11-12
// w32-sizeA (2026-11-11): not retried (60+ forms already in docs/toolchain/gcse.md); the first differing block is the compare's (retail beq with move a1,v1 in its slot, ours bnel), as above.
// NEAR (2026-11-08, night-gamec): retail's beq with the store's address copied (move a1,v1 in its delay slot) where this has bnel and one address register; the reload after the store is the same
// In the context of its file, src/main/disc_access.cpp: its declarations before the function, bodies cut.
// Mechanism (2026-11-10, docs/TOOLCHAIN.md, GCSE, "A %hi copied into a second register"):
//       retail's move a1,v1 is PRE's late insertion of the %hi at the end of the compare's block,
//       which cse2 turns into a copy; it happens only when the store's arm begins with a label at
//       cse time (a jump into the arm that cse folds away), so its %hi is still its own pseudo.
//       A plain if puts the arm in the compare's cse block. `|| <real second test>` and
//       `while (g_discStatus != status) g_discStatus = status;` reproduce the copy (the loop the
//       whole shape, registers v1/a0 swapped and a nop); no plausible single-test form found
//       (about 30 forms ruled out, listed there).
// Wave 16 (2026-11-10): about 25 more forms ruled out (docs/toolchain/gcse.md, "Also ruled out"):
//       condition spellings, goto, switch, ?:/&&/|| statements, do-while(0), the return's forms;
//       every loop form gives the copy but adds an aligned loop label's nop (68 bytes).
// w37-f2 (2026-11-12): the width is 32 bits (s8/s16 add sll+sra and are 64 bytes by coincidence; u8/u16 an andi;
//       long a dsll32/dsra32). From -da dumps of three forms: retail needs the join's %hi merged with the
//       compare's in cse1 (the skip around the arm does that) and the store's block cut off from the
//       compare's in cse1 AND cse2. A run-once loop before the store cuts only cse1 (cse2 ignores a loop end
//       in its forward scan and rewrites the store to the first register; the note also aligns the join);
//       the two-test form cuts the join instead, so store and join both go through PRE's copy. Ruled out
//       too: the equal case returning first with a run-once loop after its return, and that inside a
//       do/while(0) left by break. docs/toolchain/gcse.md, "A %hi copied into a second register".
// w40-fb (2026-11-12): the volatile signature is absent (retail's equal path skips the second lw and uses the test's load; a volatile read is never reused) and `volatile s32 g_discStatus` compiles to this near miss's code unchanged. docs/toolchain/gcse.md, same section.
#include "common.h"
#include "asm_func.h"
#include "key_id.h"

// The sector check's state, the word before this file's .data: GCC aligns the read errors
// (24 bytes) to 8, so a .data that started at 0x2613EC would put them at 0x261400.
extern s32 g_discSectorCheckState;

// The file's .data, in retail's order: the drive's state, the last result of a read request
// and the read errors.
s32 g_discStatus = -1;
s32 g_lastDiscReadResult = 0;
s32 g_discReadErrors[6] = { 0, 0, 0, 0, 0, 0 };

// In another stretch of .rodata (global_tables.cpp defines them): the read mode, the checked sector
// and its CRC-32.
extern const u32 D_00247AA0;
extern const u32 D_00247AA4;
extern const u32 D_00247AA8[2];
extern u8 D_002701B8[];
extern u8 g_discCheckSectorBuffer[];
extern u32 g_crc32Table[];
extern u8 g_pauseMenuElement[];

s32 StartDiscRead(s32 a0, s32 a1, void* a2, void* a3);
s32 SyncDiscRead(s32 mode);
s32 GetDiscReadError(void);
void UppercaseString(s8* p);
s32 GetStringLength(const s8* s);
void* AppendString(s8* dst, const char* src);
s32 FormatToString(void* dst, const char* fmt, ...);
s32 CheckDiscChanged(s32 a0, s32* out);
u32 SendDiscSCommand22(s32 arg);
s32 ReadDiscSectors(void*, void*, void*, void*);
s32 SyncDiscNCommand(s32);
s32 GetDiscError(void);
s32 RefreshDiscStatus(void);
s32 TestDiscReadDone(s32 value);
void SetPauseMenuLayerPage(void* self, s32 a, s32 b);

void ResetDiscSectorCheck(void);

// The second word of a key (GetKeyedDataSize, func_0018C1E8, hands it one).
s32 GetKeyIdSecond(KeyId* key);

s32 NormalizeDiscPath(s8* path);

s32 GetDiscStatus(void);

s32 RefreshDiscStatus(void)
{
    s32 status = GetDiscStatus();
    if (g_discStatus != status) {
        g_discStatus = status;
    }
    return g_discStatus == 0x14;
}
