// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 751/804 (93.4%), checked 2026-11-10
// NEAR: retail's size (804 bytes), 30 differing lines when built in src/main/file_137290.cpp (and
//       standalone). New this round:
//       the bank pointer `p` is one variable reused by the three transfers (C style), so it is a
//       global pseudo that global-alloc puts in a1 (two of its three copies go to a1), which gives
//       retail's `addu a1; move a0,a1` before StartFromSprChain; the bounds are constant
//       initialisers ({K, K, K, 0}: clear, then z, x, y as retail stores them). Left, two
//       mechanisms: (1) sched1 issues both literal %hi's in the first cycle (equal priority 26,
//       every bound store feeds the aliasing load of the list's link offset), so the second %hi
//       takes v1 where retail reuses v0 after the first lwc1; the frame push's registers follow
//       (retail e in v1, &fr in a3, the %hi of g_activeListFrames in a2). (2) loop.c does not
//       move the loop's life-1 invariants (the %hi of g_toSprChannel; likely the 1 of `1 - D_00274990`):
//       80 * 1 * 1 < 95 insns (87 in pass 2); retail's `lui a3` in the loop and the bnez slot and
//       probably its `li v0,1` with the result in the loaded register, are reload's rematerialisations
//       of moved invariants that got no register (s0-s8 are all taken). A `void* const& ch =
//       g_toSprChannel;` at the loop top gives the hoist (life 2), but changes the preheader and
//       is not plausible code. Lands with: the FLT_MAX bounds as literals, which removes the C
//       definitions of D_00249D64 and D_00249D68 from src/main/file_137290.cpp (they are this
//       function's literal pool, the file's .rodata +0 and +4).
// In the context of its file, src/main/file_137290.cpp.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "owned_record.h"
#include "world_listed_object.h"
#include "vu0.h"
#include "placed_object.h"

void DetachOwnedRecord(OwnedRecord* o);

// One of the two scratchpad transfer buffers (file_1B7968.cpp): the blocks StartToSprChain sent.
struct SprTransfer {
    void* tags;             // 0x00
    s32 base;               // 0x04
    u32 addrs[8];           // 0x08: each block's scratchpad address
    s32 sizes[8];           // 0x28
    s32 count;              // 0x48
    s32 state;              // 0x4C: 2 while its blocks are worked on
};

extern s32 D_00274990;
extern SprTransfer D_002748F0[2];
extern void* g_toSprChannel;

// Block n of the current scratchpad transfer.
struct SprBlock {
    static u32 Of(s32 n)
    {
        return D_002748F0[D_00274990].addrs[n];
    }
};

void TurnMatrixBySpin(void* spin, Vec02* out);
s32 WaitDmaChannel(void* dma, s32 b, s32 c);
void StartToSprChain(s32 size, ...);
void StartFromSprChain(void* first, ...);
s32 func_0013A498(Vec02* m, u128 s, u32 a, u32 b, u32 c, s32 n, s32 mode, Vec02* lo, Vec02* hi);

void func_0013A618(WorldListedObject* self, f32 dt)
{
    Vec02 lo = {3.4028235e+38f, 3.4028235e+38f, 3.4028235e+38f, 0.0f};
    Vec02 hi = {-3.4028235e+38f, -3.4028235e+38f, -3.4028235e+38f, 0.0f};
    Vec02 mat[4];
    WordListFrame fr;
    s32 e = (s32)&self->members.head;
    fr.list = e;
    fr.link = e;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.offset = link;
    *(s32*)&g_activeListFrames = (s32)&fr;
    TurnMatrixBySpin((u8*)self + 0x330, mat);
    s32 head = *(s32*)fr.link;
    fr.link = head + fr.offset;
    OwnedRecord* node = (OwnedRecord*)head;
    Vec02* p = node->points[node->bank];
    StartToSprChain(node->count * 16, p, node->count * 16, p + 0x2C, node->count * 16, p + 0x58, 0, 0);
    while (node != 0) {
        WaitDmaChannel(g_toSprChannel, 0, 0);
        D_00274990 = 1 - D_00274990;
        D_002748F0[D_00274990].state = 2;
        OwnedRecord* next = *(OwnedRecord**)fr.link;
        fr.link = (s32)next + fr.offset;
        if (next != 0) {
            p = next->points[next->bank];
            StartToSprChain(next->count * 16, p, next->count * 16, p + 0x2C, next->count * 16, p + 0x58, 0, 0);
        }
        u128 w = Vu0::ScalarInGpr(dt);
        s32 used = func_0013A498(mat, w, SprBlock::Of(0), SprBlock::Of(1), SprBlock::Of(2), node->count, self->f618, &lo, &hi);
        s32 nb = (node->bank + 1) & 1;
        p = node->points[nb];
        StartFromSprChain(p, p + 0x2C, p + 0x58, 0);
        node->count -= used;
        self->f620 -= used;
        if (node->count <= 0) {
            DetachOwnedRecord(node);
        } else {
            node->bank = nb;
        }
        node = next;
    }
    if (self->f620 <= 0) {
        self->desc->m03(self);
    } else {
        Vec02 center;
        Vu0::Q(center) = Vu0::MulXSum(Vu0::Q(lo), Vu0::Scalar(0.5f), Vu0::Q(hi), Vu0::Scalar(0.5f));
        self->desc02()->m1D(self, &center);
        self->f2A4 = self->f2A8 = Vu0::Distance(center, hi);
    }
    *(s32*)&g_activeListFrames = fr.prev;
}
