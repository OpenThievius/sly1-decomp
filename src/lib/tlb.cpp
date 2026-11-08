// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library's TLB set-up, its own object from 0x1FA9B0 to 0x1FAC00, built whole
// (config/us/files.tsv): a file-local copy of the system call stub 0x56 (func_001FA9B0, which
// only func_001FAA00 calls; the public one is func_001F6BD0), the entry func_001FA9C0, which
// sets the TLB up through func_001FAA00 when func_001F6D20 reports 0x2000000 and calls
// func_001F6D30 otherwise, and func_001FAA00 itself, which reports the entry counts and writes
// the three tables of entries D_00277FE0 points to (C with a register variable and the TLB's
// system sequence: docs/ASM_CLASSIFICATION.md, "Two kernel-library functions examined"). Its .rodata (the four messages) and .data (the three
// tables and the record pointing to them) are this object's.
#include "common.h"
#include "asm_func.h"
#include "system.h"

ASM_FUNC(func_001FA9B0);

s32 QueryMemorySize(void);
s32 func_001F6D30(void);
s32 func_001FAA00(void);

s32 SetUpTlbForMemory(void)
{
    if (QueryMemorySize() == 0x2000000) {
        return func_001FAA00();
    }
    return func_001F6D30();
}

// One TLB entry as the kernel's call takes it: the page mask, the virtual page (EntryHi) and
// the two physical pages (EntryLo0, EntryLo1).
struct TlbEntry {
    u32 mask;
    u32 hi;
    u32 lo0;
    u32 lo1;
};

// The set-up's record: how many entries each of the three tables holds (the message reports
// them as the kernel, default and extended ranges), the wired count written back, and the
// tables.
struct TlbSetup {
    s32 kernelCount;
    s32 defaultCount;
    s32 extendedCount;
    s32 wiredCount;
    TlbEntry* kernel;
    TlbEntry* defaults;
    TlbEntry* extended;
    void* f1C;
};

extern TlbSetup D_00277FE0;
extern const char D_0024EC30[], D_0024EC68[], D_0024EC80[], D_0024EC98[];
s32 PrintToOutputHook(const char* fmt, ...);
void TerminateProgram(s32 code);
void func_001FA9B0(s32 index, u32 mask, u32 hi, u32 lo0, u32 lo1);

// Reports the three ranges, writes the kernel and default entries and wires them, then the
// extended ones, and maps every entry left with an empty page from 0xE0000000. The counter is
// a register variable in $t9 (retail keeps it there across the calls, which only such a
// declaration gives); its return is the entry count.
s32 func_001FAA00(void)
{
    register s32 i __asm__("$25");
    TlbEntry* e;
    s32 n;
    s32 j;
    PrintToOutputHook(D_0024EC30, D_00277FE0.kernelCount - 1, D_00277FE0.kernelCount,
                      D_00277FE0.kernelCount + D_00277FE0.defaultCount - 1,
                      D_00277FE0.kernelCount + D_00277FE0.defaultCount,
                      D_00277FE0.kernelCount + D_00277FE0.defaultCount + D_00277FE0.extendedCount - 1);
    SetTlbWired(0);
    i = 0;
    n = D_00277FE0.kernelCount;
    if (n > 0x30) {
        PrintToOutputHook(D_0024EC68);
        TerminateProgram(1);
    }
    for (e = D_00277FE0.kernel; i < n; i++, e++) {
        func_001FA9B0(i, e->mask, e->hi, e->lo0, e->lo1);
    }
    n = i + D_00277FE0.defaultCount;
    if (n > 0x30) {
        PrintToOutputHook(D_0024EC80);
        TerminateProgram(1);
    }
    for (e = D_00277FE0.defaults; i < n; i++, e++) {
        func_001FA9B0(i, e->mask, e->hi, e->lo0, e->lo1);
    }
    D_00277FE0.wiredCount = i;
    SetTlbWired(i);
    if (D_00277FE0.extendedCount > 0) {
        n = i + D_00277FE0.extendedCount;
        if (n > 0x30) {
            PrintToOutputHook(D_0024EC98);
            TerminateProgram(1);
        }
        for (e = D_00277FE0.extended; i < n; i++, e++) {
            func_001FA9B0(i, e->mask, e->hi, e->lo0, e->lo1);
        }
    }
    for (j = i; j < 0x30; j++) {
        func_001FA9B0(j, 0, 0xE0000000 + (j << 13), 0, 0);
    }
    return i;
}

extern const char D_0024EC30[56] = "# TLB spad=0 kernel=1:%d default=%d:%d extended=%d:%d\n";
extern const char D_0024EC68[24] = "# TLB over flow (1)";
extern const char D_0024EC80[24] = "# TLB over flow (2)";
extern const char D_0024EC98[24] = "# TLB over flow (3)";

INCLUDE_DATA(D_00277D70);
INCLUDE_DATA(D_00277E40);
INCLUDE_DATA(D_00277F60);

extern u8 D_00277D70[], D_00277E40[], D_00277F60[], D_0027B184[];
TlbSetup D_00277FE0 = { 0xD, 0x12, 8, 0, (TlbEntry*)D_00277D70, (TlbEntry*)D_00277E40, (TlbEntry*)D_00277F60, D_0027B184 };
