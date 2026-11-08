// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: now the size of retail's (804 bytes), with its loop shape: the bases (D_002748F0 + 8,
// 0x840, 0x50) hoisted as retail has them, the dt weight passed through Vu0::ScalarInGpr (mfc1,
// the sq to 0x80, shared with `center` declared in the else block), the transfer's blocks read
// through the inline SprBlock::Of(n) (the offset added before the base, as func_0018F9D8), the
// list head read into a word before it becomes the node (retail's lw v1 / move s1,v1), and the
// count test written <= 0 first (bgtzl). Left: register choices and order around the frame push
// (retail: e in v1, &fr in a3, the lui in a2), the literals' lui pair and the lo/hi stores'
// order, the bank*0x840 product's registers in both StartToSprChain calls, and the weight's
// mfc1 into v1 then por a1 (ours mfc1 straight into a1). Tried: ListFrame with BeginListWalk's
// order (worse), the weight in a local before the call, the helper returning r, pointer forms
// of the block arguments. Lands with: the FLT_MAX bounds as literals, which removes the C
// definitions of D_00249D64 and D_00249D68 from src/main/file_137290.cpp.
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
    Vec02 lo = {};
    Vec02 hi = {};
    Vec02 mat[4];
    WordListFrame fr;
    lo.y = lo.x = lo.z = 3.4028235e+38f;
    hi.y = hi.x = hi.z = -3.4028235e+38f;
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
    StartToSprChain(node->count * 16, node->points[node->bank], node->count * 16, &node->points[node->bank][0x2C], node->count * 16, &node->points[node->bank][0x58], 0, 0);
    while (node != 0) {
        WaitDmaChannel(g_toSprChannel, 0, 0);
        D_00274990 = 1 - D_00274990;
        D_002748F0[D_00274990].state = 2;
        OwnedRecord* next = *(OwnedRecord**)fr.link;
        fr.link = (s32)next + fr.offset;
        if (next != 0) {
            StartToSprChain(next->count * 16, next->points[next->bank], next->count * 16, &next->points[next->bank][0x2C], next->count * 16, &next->points[next->bank][0x58], 0, 0);
        }
        u128 w = Vu0::ScalarInGpr(dt);
        s32 used = func_0013A498(mat, w, SprBlock::Of(0), SprBlock::Of(1), SprBlock::Of(2), node->count, self->f618, &lo, &hi);
        s32 nb = (node->bank + 1) & 1;
        Vec02* p = node->points[nb];
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
