// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 332/680 (48.8%), checked 2026-11-13
// w47-h (2026-11-13), 15 compiles and the dumps of the 36 library files this cc1 builds: the three forms left uncompiled are compiled and out (callee return types void or s32: 102; one variable for rows and height: 64 lines but s6/s7 swapped, not closer; for rows and size: 79, the same; the height set in each arm: 136), and so are the test as nested ifs, gotos or a flag local. Measured: this compiler's insns that print nothing are a trap_if anti-dependent on another trap (func_00202140's match; no division by a variable here), flow's `(use (const_int 0))` after a call that ends a block (tied behind the call), and `blockage` before the epilogue's stack adjustment; no dead set reaches sched2 in any library file, so the dead re-read reading is out; and no block of those files has one insn alone in cycle 1 with a free ALU insn waiting, so retail's first cycle is not a rank of one block. gcse is edge-based: with the last plane's address partly available PRE computes it on both edges into the body (test and both slots exact), and so does the address set in each arm by hand (35 lines), but each leaves one pseudo set on the edges (in s5 in the PRE probe; by hand spilled beside its set, slot 48); retail's `sw v0,68(sp)` sits in the body after the picture stores, so v0 crosses a code-free boundary and the stored pseudo is the last made (docs/toolchain/sched1.md, "A block whose first cycle holds one insn", third pass). No source form found.
// w46-d (2026-11-13), 5 compiles (do-while over the body and over its first half, two dead if/else probes): nothing closer, 102 lines. Measured: loop.c calls a do-while(0) "phony" and moves nothing out of it, so a loop note here is only a barrier; this cc1's jump turns an if/else of two loads into a conditional move, so the emptied if/else of alias-classes.md leaves no block boundary (the probe's blocks are the base's). Read from retail's cycles, not compiled: retail's first cycle is one ALU insn and no store, and every later store is one cycle late while the ALU insns keep their order, so either nothing else was ready (a barrier or a block's end after the address) or an insn that leaves no code held the memory unit in cycle 1. The second fits a re-read of pic->width at the head of the body: the picture's stores wait for it (priority above 65), it takes the memory unit, and reorg.c's fill_slots_from_thread drops an insn that redundant_insn finds before the branch (`lw v1,0(a1)` is there on both paths) and copies the next one, the address, into both slots. flow2 would delete the load if nothing read it, so something read v1 up to sched2 and went in jump2 or reorg. The last slot (68) for the address fits a pseudo made after the others: the argument's own, set by a copy from a register that holds the address only at the head. Not compiled against either reading.
// w44-fa (2026-11-12), no compile: read against the three untested forms. A callee's return type and a count set in each arm act after the first cycle of the body (the calls come later; rows is already set in each arm), and one variable for unrelated values would have to be the height's temporary (`lw v0,4(a1)`) reused for the last plane's address: retail has no spill store after that load, which a spilled pseudo set there would have (the beq reads it), so they are not one pseudo. Nothing tried in C.
// w37-f3 (2026-11-12): two more candidates for the insn that shares the body's first cycle, both ruled out. A CLOBBER of the picture's size (the file as C, `pic->dim = (struct Dim){ w, h };`: cc1's store_constructor emits `(clobber (mem:BLK pic))` before the two stores) reaches sched1 only: reload deletes every CLOBBER insn, sched2 sees the same block and the score is the same 102 lines (the plain file as C is 102 too, so the front end is not the difference). `do { } while (0)` around the whole body makes the height store the barrier (128 lines). Read from retail's cycles: its body schedules exactly as ours would with the address in a block of its own ahead of it (sw s6 + li, sw s7 + mult, sw v0,68(sp) + addiu s1), so what is missing is still an insn or a block boundary that only sched2 sees (docs/toolchain/sched1.md, "A block whose first cycle holds one insn").
// NEAR: in its file, src/lib/mpeg_decoder.cpp (Sony's 2.9-ee-991111). The structure, the
//       calls and the tail call match; the rows kept in a local give retail's use of the value
//       for the height and its reload of the width, and the defaults' stores are now retail's.
//       Left (re-scored 2026-11-10): retail's sched2 issues the last plane's address
//       (`addiu v0,s8,1320`, a spilled pseudo) alone in the body's first cycle; ours pairs it
//       with the height store, which wins the tie on dependents and comes first. reorg then
//       puts the store in an annulled bnel slot, where retail copies the address into both the
//       bne and the beq slots, and the body runs one insn off from there (docs/TOOLCHAIN.md,
//       "A block whose first cycle holds one insn"). Only a scheduling barrier at that address
//       reproduces it: a loop note before it (`for (p8 = &st->planes[8].addr; 0; ) { }` at the
//       top of the body, not plausible) gives the test and both delay slots exactly. Tried: the
//       stores and the size in every order, the planes' addresses in locals, the size as
//       w * h * 0x180 (other multiply order), (w * 0x180) * h, the body inside the inverted
//       test, unsigned fields, w and h in the other order, rows stored in both arms, the size
//       before the test, an inline helper (not inlined), do-while(0) around or before the body,
//       -fno-strict-aliasing, -O3, -fno-gcse, the Linux -01 build. Second pass (2026-11-10): no
//       barrier fits exactly (a loop note is a barrier only after the block's first insn,
//       and the barrier is the insn after it), no invisible insn reaches sched2 (no-op moves,
//       flow's nops, reorg's redundant re-read), and -funroll-loops, the planes through a
//       local pointer and the test or the body as an inline are worse
//       (docs/toolchain/sched1.md, "A block whose first cycle holds one insn"). Written for
//       this project from retail's code.
// permute.py --auto (2026-11-08, night-orders): 4 runs of 6/4/7/7 lines (10824 orders): best 180 bytes differ (348 as it stands), none EXACT.
#include "common.h"

struct Pool_0020B278 {
    u32 f00;
    u32 f04;
    u32 f08;
};
struct Owner_0020B278;
struct Item_20B9D0;
s32 RewindMpegRingToMark(s32* item);
s32 AllocateFromMpegRing(Owner_0020B278* owner, Pool_0020B278* pool, u32 offset, u32 align);
s32 SetPictureDimensions(Item_20B9D0* item, s32 x, s32 y);

// A picture plane: its address, its size in pixels and in macroblocks.
struct Plane_20BB18 {
    u32 addr;
    s32 width;
    s32 height;
    s32 mbWidth;
    s32 mbHeight;
    u8 pad14[0x68 - 0x14];
};

struct State_20BB18 {
    u8 pad0[0xFC];
    u32 fFC;
    u32 f100;
    u32 f104;
    Pool_0020B278 pool;
    u32 f114;
    u8 pad118[0x124 - 0x118];
    s32 f124;
    s32 f128;
    s32 f12C;
    s32 f130;
    u8 pad134[0x13C - 0x134];
    s32 f13C;
    s32 f140;
    s32 f144;
    u8 pad148[0x174 - 0x148];
    s32 f174;
    u8 pad178[4];
    s32 f17C;
    u8 pad180[8];
    s32 f188;
    u8 pad18C[0x1E8 - 0x18C];
    Plane_20BB18 planes[9];
    u8 pad590[0x848 - 0x590];
    s32 f848;
};

struct Picture_20BB18 {
    s32 width;
    s32 height;
    u8 pad8[0x38];
    State_20BB18* state;
};

void SetUpPictureBufferAddresses(u32* a0, u32* a1, u32* a2, u32* a3, u32* a4, u32* a5, u32* a6, u32* a7, u32* p9, u32 p10, u32 p11, u32 p12, s32 p13, s32 p14);

void AllocatePictureBuffers(Picture_20BB18* pic)
{
    State_20BB18* st = pic->state;
    s32 w;
    s32 h;
    u32 size;
    s32 rows;

    if (st->f848 == 0) {
        st->f174 = 3;
        st->f13C = 1;
        st->f140 = 1;
        st->f188 = 1;
        st->f17C = 1;
        st->f144 = 5;
    }
    st->f12C = (st->f124 + 15) >> 4;
    if (st->f848 != 0 && st->f13C == 0)
        rows = ((st->f128 + 31) >> 5) << 1;
    else
        rows = (st->f128 + 15) >> 4;
    st->f130 = rows;
    h = rows << 4;
    w = st->f12C << 4;
    if (w == pic->width && h == pic->height)
        return;
    pic->width = w;
    pic->height = h;
    size = (u32)(w * 0x180 * h) >> 8;
    RewindMpegRingToMark((s32*)&st->pool);
    st->fFC = AllocateFromMpegRing((Owner_0020B278*)st, &st->pool, size, 0x40);
    st->f100 = AllocateFromMpegRing((Owner_0020B278*)st, &st->pool, size, 0x40);
    st->f104 = AllocateFromMpegRing((Owner_0020B278*)st, &st->pool, size, 0x40);
    SetUpPictureBufferAddresses(&st->planes[0].addr, &st->planes[1].addr, &st->planes[2].addr, &st->planes[3].addr,
                  &st->planes[4].addr, &st->planes[5].addr, &st->planes[6].addr, &st->planes[7].addr,
                  &st->planes[8].addr, st->fFC, st->f100, st->f104, w, h);
    SetPictureDimensions((Item_20B9D0*)&st->planes[0], w, h);
    SetPictureDimensions((Item_20B9D0*)&st->planes[1], w, h);
    SetPictureDimensions((Item_20B9D0*)&st->planes[2], w, h);
    SetPictureDimensions((Item_20B9D0*)&st->planes[3], w, h >> 1);
    SetPictureDimensions((Item_20B9D0*)&st->planes[4], w, h >> 1);
    SetPictureDimensions((Item_20B9D0*)&st->planes[5], w, h >> 1);
    SetPictureDimensions((Item_20B9D0*)&st->planes[6], w, h >> 1);
    SetPictureDimensions((Item_20B9D0*)&st->planes[7], w, h >> 1);
    SetPictureDimensions((Item_20B9D0*)&st->planes[8], w, h >> 1);
}
