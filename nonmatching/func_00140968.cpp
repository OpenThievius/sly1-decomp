// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 60/64, checked 2026-11-11
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
u32 SendDiscSValueCommand(s32 arg);
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
