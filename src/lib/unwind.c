/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The toolchain runtime's unwinder, which throw (src/lib/throw.c) asks for the state of each frame
 * it unwinds. C, built by cc1 (config/cflags.tsv), as the runtime was compiled (docs/TOOLCHAIN.md).
 * Written for this project from retail's code; func_001FF658, which finds a code address's frame
 * record, is a near miss in nonmatching/. */
#include "common.h"

/* A frame description record: its length, the distance back to its common record, its range. */
typedef struct FrameDesc {
    u32 length;
    s32 commonDelta;
    void* start;
    u32 range;
} FrameDesc;

/* What the common record says: its augmentation string, the handler data, the return column. */
typedef struct CommonInfo {
    char* augmentation;
    void* handlerData;
    s32 codeAlign;
    s32 dataAlign;
    u16 returnColumn;
    u16 pad12;
    s32 pad14[3];
} CommonInfo;

/* A frame's unwind state as the caller gets it, 0x2F0 bytes. */
typedef struct UnwindState {
    s32 cfa;
    void* handlerData;
    s64 body[0x290 / 8];
    s16 pad298;
    s16 returnColumn;
    s32 pad29C;
    s64 tail[0x50 / 8];
} UnwindState;

/* The interpreter's state: the caller's, and the saved one. */
typedef struct UnwindWork {
    UnwindState s;
    void* saved;
    s32 pad2F4;
} UnwindWork;

FrameDesc* func_001FF658(void* pc);
u8* func_001FF740(FrameDesc* f, CommonInfo* info);
u8* func_001FF848(u8* insn, UnwindWork* work, CommonInfo* info, void** pc);
u8* func_001FF048(u8* input, u32* output);
void* func_001F5C0C(void* dst, s32 c, u32 n);

UnwindState* func_001FFC80(void* target, UnwindState* out)
{
    FrameDesc* f;
    u8* insn;
    u8* end;
    void* pc;
    CommonInfo info;
    UnwindWork work;

    f = func_001FF658(target);
    if (f == 0)
        return 0;
    insn = func_001FF740(f, &info);
    if (insn == 0)
        return 0;

    func_001F5C0C(&work, 0, sizeof(work));
    work.s.returnColumn = info.returnColumn;
    work.s.handlerData = info.handlerData;

    {
        FrameDesc* common = (FrameDesc*)((char*)&f->commonDelta - f->commonDelta);
        end = (u8*)common + common->length + 4;
    }
    while (insn < end)
        insn = func_001FF848(insn, &work, &info, 0);

    insn = (u8*)(f + 1);
    if (info.augmentation[0] == 'z') {
        u32 skip;
        insn = func_001FF048(insn, &skip);
        insn += skip;
    }

    end = (u8*)f + f->length + 4;
    pc = f->start;
    while (insn < end && pc <= target)
        insn = func_001FF848(insn, &work, &info, &pc);

    *out = work.s;
    return out;
}
