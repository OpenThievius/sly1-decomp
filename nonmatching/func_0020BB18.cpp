// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 332/680 (48.8%), checked 2026-11-11
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
