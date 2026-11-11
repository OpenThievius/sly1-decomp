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
s32 SetUpTlbSyscall(void);
s32 SetUpTlbEntries(void);

s32 SetUpTlbForMemory(void)
{
    if (QueryMemorySize() == 0x2000000) {
        return SetUpTlbEntries();
    }
    return SetUpTlbSyscall();
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
void PrintToOutputHook(const char* fmt, ...);
void TerminateProgram(s32 code);
void WriteTlbEntryForSetUp(s32 index, u32 mask, u32 hi, u32 lo0, u32 lo1);

// Reports the three ranges, writes the kernel and default entries and wires them, then the
// extended ones, and maps every entry left with an empty page from 0xE0000000. The counter is
// a register variable in $t9 (retail keeps it there across the calls, which only such a
// declaration gives); its return is the entry count.
s32 SetUpTlbEntries(void)
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
        WriteTlbEntryForSetUp(i, e->mask, e->hi, e->lo0, e->lo1);
    }
    n = i + D_00277FE0.defaultCount;
    if (n > 0x30) {
        PrintToOutputHook(D_0024EC80);
        TerminateProgram(1);
    }
    for (e = D_00277FE0.defaults; i < n; i++, e++) {
        WriteTlbEntryForSetUp(i, e->mask, e->hi, e->lo0, e->lo1);
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
            WriteTlbEntryForSetUp(i, e->mask, e->hi, e->lo0, e->lo1);
        }
    }
    for (j = i; j < 0x30; j++) {
        WriteTlbEntryForSetUp(j, 0, 0xE0000000 + (j << 13), 0, 0);
    }
    return i;
}

extern const char D_0024EC30[56] = "# TLB spad=0 kernel=1:%d default=%d:%d extended=%d:%d\n";
extern const char D_0024EC68[24] = "# TLB over flow (1)";
extern const char D_0024EC80[24] = "# TLB over flow (2)";
extern const char D_0024EC98[24] = "# TLB over flow (3)";

TlbEntry D_00277D70[13] = {
    { 0x0, 0x70000000, 0x80000007, 0x7 },
    { 0x6000, 0xFFFF8000, 0x1E1F, 0x1F1F },
    { 0x0, 0x10000000, 0x400017, 0x400053 },
    { 0x0, 0x10002000, 0x400097, 0x4000D7 },
    { 0x0, 0x10004000, 0x400117, 0x400157 },
    { 0x0, 0x10006000, 0x400197, 0x4001D7 },
    { 0x0, 0x10008000, 0x400217, 0x400257 },
    { 0x0, 0x1000A000, 0x400297, 0x4002D7 },
    { 0x0, 0x1000C000, 0x400313, 0x400357 },
    { 0x0, 0x1000E000, 0x400397, 0x4003D7 },
    { 0x1E000, 0x11000000, 0x440017, 0x440415 },
    { 0x1E000, 0x12000000, 0x480017, 0x480415 },
    { 0x1FFE000, 0x1E000000, 0x780017, 0x7C0017 }
};
TlbEntry D_00277E40[18] = {
    { 0x7E000, 0x80000, 0x201F, 0x301F },
    { 0x7E000, 0x100000, 0x401F, 0x501F },
    { 0x7E000, 0x180000, 0x601F, 0x701F },
    { 0x1FE000, 0x200000, 0x801F, 0xC01F },
    { 0x1FE000, 0x400000, 0x1001F, 0x1401F },
    { 0x1FE000, 0x600000, 0x1801F, 0x1C01F },
    { 0x7FE000, 0x800000, 0x2001F, 0x3001F },
    { 0x7FE000, 0x1000000, 0x4001F, 0x5001F },
    { 0x7FE000, 0x1800000, 0x6001F, 0x7001F },
    { 0x7E000, 0x20080000, 0x2017, 0x3017 },
    { 0x7E000, 0x20100000, 0x4017, 0x5017 },
    { 0x7E000, 0x20180000, 0x6017, 0x7017 },
    { 0x1FE000, 0x20200000, 0x8017, 0xC017 },
    { 0x1FE000, 0x20400000, 0x10017, 0x14017 },
    { 0x1FE000, 0x20600000, 0x18017, 0x1C017 },
    { 0x7FE000, 0x20800000, 0x20017, 0x30017 },
    { 0x7FE000, 0x21000000, 0x40017, 0x50017 },
    { 0x7FE000, 0x21800000, 0x60017, 0x70017 }
};
TlbEntry D_00277F60[8] = {
    { 0x7E000, 0x30100000, 0x403F, 0x503F },
    { 0x7E000, 0x30180000, 0x603F, 0x703F },
    { 0x1FE000, 0x30200000, 0x803F, 0xC03F },
    { 0x1FE000, 0x30400000, 0x1003F, 0x1403F },
    { 0x1FE000, 0x30600000, 0x1803F, 0x1C03F },
    { 0x7FE000, 0x30800000, 0x2003F, 0x3003F },
    { 0x7FE000, 0x31000000, 0x4003F, 0x5003F },
    { 0x7FE000, 0x31800000, 0x6003F, 0x7003F }
};

extern u8 D_0027B184[];
TlbSetup D_00277FE0 = { 0xD, 0x12, 8, 0, D_00277D70, D_00277E40, D_00277F60, D_0027B184 };
