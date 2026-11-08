// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 760/804, checked 2026-11-08
// NEAR: right frame (0x150), calls, arguments, list walk and the VU0 tail (MulXSum of the bounds with one half Scalar, Distance to hi); registers and block order of the head follow retail's. Differs: ours hoists mfc1 of dt, the three bases (D_002748F0 + 8, the stride 0x840, 0x50) out of the loop where retail keeps them in s5/s7/s8 and recomputes the dt move inside it (loop.c: the loop is too small; Vec values were not enough to make it bigger), and the u128 argument's dead store lands at 0x90 (retail's 0x80, sharing the slot with `center`). The scalar for func_0013A498's second argument is the float's bits moved by mfc1 (por a1,zero,v1; sq v1,0x80): `Vu0::Q(sv) = (u128)*(s32*)&dt` gives the por but not its store in place. The literal FLT_MAX bounds are retail's rodata (D_00249D64, D_00249D68 defined in C by the file today would be removed when this lands). Needs WorldListedObject::f618 (0x618, the mode word) in include/world_listed_object.h; written here with an offset.
// In the context of its file, src/main/file_137290.cpp.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "owned_record.h"
#include "world_listed_object.h"
#include "vu0.h"
#include "placed_object.h"

void DetachOwnedRecord(OwnedRecord* o);

void TurnMatrixBySpin(void* spin, Mat02* out);
void WaitDmaChannel(s32 channel, s32 a, s32 b);
void StartToSprChain(s32 n0, void* p1, s32 n2, void* p3, s32 n4, void* p5, s32 a6, s32 a7);
void StartFromSprChain(void* p0, void* p1, void* p2, s32 a3);
s32 func_0013A498(Mat02* m, u128 s, void* a2, void* a3, void* a4, s32 n, s32 mode, Vec02* lo, Vec02* hi);
extern s32 g_toSprChannel;
extern s32 D_00274990;
struct SprBuffer {
    u8 pad00[8];
    void* f08;
    void* f0C;
    void* f10;
    u8 pad14[0x4C - 0x14];
    s32 f4C;
};
extern SprBuffer D_002748F0[];

void func_0013A618(WorldListedObject* self, f32 dt)
{
    Vec02 lo = {};
    Vec02 hi = {};
    Vec02 mat[4];
    WordListFrame fr;
    Vec02 center;
    lo.x = lo.y = lo.z = 3.4028234663852886e+38f;
    hi.x = hi.y = hi.z = -3.4028234663852886e+38f;
    s32 e = (s32)&self->members.head;
    fr.list = e;
    fr.link = e;
    TurnMatrixBySpin((u8*)self + 0x330, (Mat02*)mat);
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.offset = link;
    *(s32*)&g_activeListFrames = (s32)&fr;
    OwnedRecord* node = *(OwnedRecord**)fr.link;
    fr.link = (s32)node + fr.offset;
    StartToSprChain(node->count * 16, node->points[node->bank], node->count * 16, (u8*)node->points[node->bank] + 0x2C0, node->count * 16, (u8*)node->points[node->bank] + 0x580, 0, 0);
    while (node != 0) {
        WaitDmaChannel(g_toSprChannel, 0, 0);
        s32 flip = 1 - D_00274990;
        D_00274990 = flip;
        SprBuffer* buf = &D_002748F0[flip];
        buf->f4C = 2;
        OwnedRecord* next = *(OwnedRecord**)fr.link;
        fr.link = (s32)next + fr.offset;
        if (next != 0) {
            StartToSprChain(next->count * 16, next->points[next->bank], next->count * 16, (u8*)next->points[next->bank] + 0x2C0, next->count * 16, (u8*)next->points[next->bank] + 0x580, 0, 0);
        }
        Vec02 sv;
        Vu0::Q(sv) = (u128)*(s32*)&dt;
        s32 used = func_0013A498((Mat02*)mat, Vu0::Q(sv), buf->f08, buf->f0C, buf->f10, node->count, *(s32*)((u8*)self + 0x618), &lo, &hi);
        s32 nb = (node->bank + 1) & 1;
        StartFromSprChain(node->points[nb], (u8*)node->points[nb] + 0x2C0, (u8*)node->points[nb] + 0x580, 0);
        node->count -= used;
        self->f620 -= used;
        if (node->count > 0) {
            node->bank = nb;
        } else {
            DetachOwnedRecord(node);
        }
        node = next;
    }
    if (self->f620 <= 0) {
        self->desc->m07(self);
    } else {
        Vu0::Q(center) = Vu0::MulXSum(Vu0::Q(lo), Vu0::Scalar(0.5f), Vu0::Q(hi), Vu0::Scalar(0.5f));
        self->desc02()->m1D(self, &center);
        self->f2A4 = self->f2A8 = Vu0::Distance(center, hi);
    }
    *(s32*)&g_activeListFrames = fr.prev;
}
