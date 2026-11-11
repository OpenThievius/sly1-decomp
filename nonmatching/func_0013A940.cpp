// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 952/964, checked 2026-11-11
// NEAR: built in src/main/file_137290.cpp it is 952 bytes of retail's 964, with retail's frame
//       (0x140), block layout and calls. Since the first translation: the mode tests are a switch
//       (retail's beq 1 / beql 2 / b compare tree, the mode-1 case placed after it), the bounds
//       are constant initialisers ({K, K, K, 0}: two sq clears, then z, x, y) and the frame push
//       is func_0013A618's (WordListFrame, the head read straight from self->members).
//       Left: (1) loop.c combines the inner loop's address givs differently. Retail keeps
//       &cur->pos[j], &cur->vel[j], &nxt->pos[out], &nxt->vel[out] (the call arguments) as their
//       own reduced registers (fp, s6, s7, s5) and bases every memory reference on the rec
//       arrays' givs (s1 = cur + 0x580, s0 = nxt + 0x580, negative offsets); ours lets the
//       multi-use &cur[j] DEST_REG giv absorb the memory givs (tie at total benefit 116, broken
//       by giv order), so one callee-saved register is left over and the bivs (removed, j, out)
//       land in it instead of retail's a7/t0/t1 saved around both calls (caller-save sq/lq):
//       the 12-byte gap is that. (2) The mode-2 case: retail reads node->extraRecord twice (in
//       the beql slot and again after the call, keeping only j * 32 in s2), which writing the
//       extra record as an array of 32-byte pairs {Vec02, Vec02} indexed from node->extraRecord
//       at each use gives (tried: right code there, but the freed register then holds j and the
//       caller-saves go, 912 bytes). (3) The prologue has func_0013A618's sched1 tie: both
//       literal %hi's issue in the first cycle, so the second takes v1 (retail reuses v0).
//       About 12 compiles this round.
// W23 (2026-11-11): re-scored, unchanged (952/964); its walls are loop.c's giv combination, which the
//       replay tools do not model, and func_0013A618's prologue tie. Not retried.
// In the context of its file, src/main/file_137290.cpp.
#include "common.h"
#include "list_iter.h"
#include "owned_record.h"
#include "world_listed_object.h"
#include "placed_object.h"
#include "vu0.h"

extern f32 g_gameClock[];

void DetachOwnedRecord(OwnedRecord* o);
void StepListedObjectParticles(WorldListedObject* self, f32 dt);
s32 EvaluateHermiteVectorSegment(Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32 t, f32 span, f32 scale, Vec02* pos, Vec02* vel, s32 flags);
f32 WrapAngle(f32 a);

void MoveWorldListedObject(WorldListedObject* self, f32 dt)
{
    if (self->mode == 0) {
        StepListedObjectParticles(self, dt);
        return;
    }
    Vec02 lo = {3.4028235e+38f, 3.4028235e+38f, 3.4028235e+38f, 0.0f};
    Vec02 hi = {-3.4028235e+38f, -3.4028235e+38f, -3.4028235e+38f, 0.0f};
    WordListFrame fr;
    s32 e = (s32)&self->members.head;
    fr.list = e;
    fr.link = e;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.offset = link;
    *(s32*)&g_activeListFrames = (s32)&fr;
    s32 head = *(s32*)fr.link;
    fr.link = head + fr.offset;
    OwnedRecord* node = (OwnedRecord*)head;
    while (node != 0) {
        Vec02* cur = node->points[node->bank];
        s32 out = 0;
        s32 removed = 0;
        s32 nb = (node->bank + 1) & 1;
        Vec02* nxt = node->points[nb];
        for (s32 j = 0; j < node->count; j++) {
            f32 end = cur[0x2C + j].w;
            if (end <= g_gameClock[1]) {
                removed++;
                continue;
            }
            switch (self->mode) {
            case 1: {
                u128 v = Vu0::Q(cur[0x2C + j]);
                Vu0::Q(nxt[0x2C + out]) = v;
                Vu0::Q(nxt[out]) = Vu0::MulAddX(Vu0::Q(cur[j]), v, Vu0::Scalar(dt));
                break;
            }
            case 2: {
                Vec02* ex = (Vec02*)node->extraRecord;
                f32 left = end - g_gameClock[1];
                EvaluateHermiteVectorSegment(&cur[j], &cur[0x2C + j], &ex[j * 2], &ex[j * 2 + 1], left, left <? dt, 1.0f, &nxt[out], &nxt[0x2C + out], 0);
                if (out != j) {
                    ex[out * 2] = ex[j * 2];
                    ex[out * 2 + 1] = ex[j * 2 + 1];
                }
                break;
            }
            }
            nxt[out].w = cur[j].w;
            nxt[0x2C + out].w = cur[0x2C + j].w;
            nxt[0x58 + out] = cur[0x58 + j];
            if (self->f618 == 2) {
                nxt[0x58 + out].w = WrapAngle(cur[0x58 + j].w + cur[0x58 + j].z * dt);
            }
            Vu0::Q(lo) = Vu0::Min(Vu0::Q(lo), Vu0::Q(nxt[out]));
            Vu0::Q(hi) = Vu0::Max(Vu0::Q(hi), Vu0::Q(nxt[out]));
            out++;
        }
        node->count -= removed;
        self->f620 -= removed;
        if (node->count <= 0) {
            DetachOwnedRecord(node);
        } else {
            node->bank = nb;
        }
        node = *(OwnedRecord**)fr.link;
        fr.link = (s32)node + fr.offset;
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
