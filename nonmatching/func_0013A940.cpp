// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 944/964, checked 2026-11-07
// NEAR (first translation, the control flow and every call are retail's; the code is not yet): the
//       frame is 0x150 against retail's 0x140, retail clears both bounds with 128-bit stores before
//       setting their x, y, z, the per-chunk base addresses and the pointer walks come out
//       differently, and the list frame is filled in another order. About 10 compiles.
#include "common.h"
#include "list_iter.h"
#include "placed_object.h"
#include "vu0.h"

extern f32 g_gameClock[];
extern const f32 D_00249D6C;
extern const f32 D_00249D70;
struct ParticleArrays03 { Vec02 pos[0x2C]; Vec02 vel[0x2C]; Vec02 rec[0x2C]; };

struct ParticleChunk03 {
    ParticleArrays03 blk[2];    // 0x000, 0x840
    s32 flip;                   // 0x1080
    s32 count;                  // 0x1084
    Vec02* extra;               // 0x1088: 32-byte entries
    s32 f108C;
    ParticleChunk03* next;      // 0x1090
};

void func_0013A618(void* set, f32 dt);
f32 WrapAngle(f32 a);
void EvaluateHermiteVectorSegment(void* a, void* b, void* c, void* d, f32 f12, f32 f13, f32 f14, void* a4, void* a5, s32 a6);
void DetachOwnedRecord(void* a);
#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))

void func_0013A940(void* set, f32 dt)
{
    Vec02 lo;
    Vec02 hi;
    Vec02 center;
    ListFrame frame;
    if (AT(s32, set, 0x320) == 0) {
        func_0013A618(set, dt);
        return;
    }
    lo.x = lo.y = lo.z = D_00249D6C;
    lo.w = 0.0f;
    hi.x = hi.y = hi.z = D_00249D70;
    hi.w = 0.0f;
    frame.list = (u8*)set + 0x624;
    frame.link = (u8*)frame.list;
    frame.offset = AT(s32, frame.list, 8);
    frame.prev = g_activeListFrames;
    g_activeListFrames = &frame;
    ParticleChunk03* chunk = AT(ParticleChunk03*, set, 0x624);
    frame.link = (u8*)chunk + frame.offset;
    while (chunk != 0) {
        s32 flip = (chunk->flip + 1) & 1;
        ParticleArrays03* cur = &chunk->blk[chunk->flip];
        ParticleArrays03* nxt = &chunk->blk[flip];
        s32 cnt = chunk->count;
        s32 removed = 0;
        s32 out = 0;
        for (s32 j = 0; j < cnt; j++) {
            f32 end = cur->vel[j].w;
            if (end <= g_gameClock[1]) {
                removed++;
                continue;
            }
            if (AT(s32, set, 0x320) == 1) {
                nxt->vel[out] = cur->vel[j];
                Vu0::Q(nxt->pos[out]) = Vu0::MulAddX(Vu0::Q(cur->pos[j]), Vu0::Q(cur->vel[j]), Vu0::Scalar(dt));
            } else if (AT(s32, set, 0x320) == 2) {
                Vec02* ex = chunk->extra;
                EvaluateHermiteVectorSegment(&cur->pos[j], &cur->vel[j], &ex[j * 2], &ex[j * 2 + 1], end - g_gameClock[1], (end - g_gameClock[1]) <? dt, 1.0f, &nxt->pos[out], &nxt->vel[out], 0);
                if (out != j) {
                    ex[out * 2] = ex[j * 2];
                    ex[out * 2 + 1] = ex[j * 2 + 1];
                }
            }
            nxt->pos[out].w = cur->pos[j].w;
            nxt->vel[out].w = cur->vel[j].w;
            nxt->rec[out] = cur->rec[j];
            if (AT(s32, set, 0x618) == 2) {
                nxt->rec[out].w = WrapAngle(cur->rec[j].w + cur->rec[j].z * dt);
            }
            Vu0::Q(lo) = Vu0::Min(Vu0::Q(lo), Vu0::Q(nxt->pos[out]));
            Vu0::Q(hi) = Vu0::Max(Vu0::Q(hi), Vu0::Q(nxt->pos[out]));
            out++;
        }
        chunk->count = cnt - removed;
        AT(s32, set, 0x620) = AT(s32, set, 0x620) - removed;
        if (chunk->count <= 0) {
            DetachOwnedRecord(chunk);
        } else {
            chunk->flip = flip;
        }
        chunk = *(ParticleChunk03**)frame.link;
        frame.link = (u8*)chunk + frame.offset;
    }
    if (AT(s32, set, 0x620) <= 0) {
        (*(void (**)(void*))(AT(u8*, set, 0) + 0x1C))(set);
    } else {
        Vu0::Q(center) = Vu0::MulXSum(Vu0::Q(lo), Vu0::Scalar(0.5f), Vu0::Q(hi), Vu0::Scalar(0.5f));
        (*(void (**)(void*, Vec02*))(AT(u8*, set, 0) + 0x84))(set, &center);
        f32 r = Vu0::ToFloat(Vu0::Sqrt(Vu0::Dot(Vu0::Sub(Vu0::Q(center), Vu0::Q(lo)), Vu0::Sub(Vu0::Q(center), Vu0::Q(lo)))));
        AT(f32, set, 0x2A4) = r;
        AT(f32, set, 0x2A8) = r;
    }
    g_activeListFrames = frame.prev;
}
