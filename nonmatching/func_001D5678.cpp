// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 2346/2348 (99.9%), checked 2026-11-11
// NEAR (2026-11-10, w15): DrawAngleSortedRing (func_001D5678): the points around the anchors
// projected into camera space, the lowest first, their angles about it and the sort, the hull (a
// Graham scan against the z axis), the bounds' centre, the points where the hull crosses the
// centre's x, the angles about the centre, the gaps filled every D_0027506C radians, then the
// strip drawn once per texture with two rows of the three. Retail's size (587 instructions) and
// frame (0x3A00). Earlier rounds: one index variable for the loops after the anchors, down at the
// top of the gap loop, lo and hi at function scope, the colour copied as an Rgba4, one
// `RingEntry* e;` reused by every loop (loop.c reduces each `e = &entries[i]` into a register of
// its own and copies it in, retail's `addu v0,v0,sp; move s1,v0 ... addiu v0,s1,-32`), the gap
// loop's first point read through e after the angles loop (`e[n]`: retail's `addu a1,s2,s1`).
// What got there (w15, 1755 to 2272 bytes; 567 of 587 instructions agree by register):
// - The weighted sums of the anchors and of the crossings name their operands as Vec locals,
//   each weight before the vector it scales: the slot stores come first and each vector load
//   waits for the store before it, as retail's do.
// - `entries[n++]` (crossings) and `e = &entries[n++]` (gaps): the giv is taken after the
//   increment, retail's base -32 and its -32(s1)/-16(s1) offsets.
// - One `s32 next;` for the hull and the draw loop (C style), and one `s32 r;` for the rows' copy
//   and the draw: the copy's reversed counter is then a pseudo that crosses calls (sched1 lifts
//   its `li s4,2` into the sort call's delay slot, as retail), and next lives in s8.
// - The draw reads the rows through `(rows + r)->`: pointer arithmetic inside a memory reference
//   keeps the frame constant outside the sum ((fp + r*16) + 14512), so GCSE sees no fp+14512 there
//   and PRE does not tie it to the copy loop's; loop.c then forms rows+14512 in the i loop's
//   preheader and spills it (14644), as retail. `rows[r].x` and `&rows[r]` both compute fp+14512
//   on its own, which PRE makes redundant with the copy loop's.
// - The lift passed inline to the sum as Vec::ScalarAtValue, whose slot is now the cast's copy
//   without Q: Q's reference left the slot address in a pseudo that CSE handed to &c (the same
//   freed slot, 14560), which loop.c then moved out of the row loop into s7.
// - The prev vector read before prevAngle, from and to declared and then assigned (their spill
//   slots in retail's order), the row weight named before the sum.
// - `*(Vu0::Vec*)&x = F(...)` for the stores and the named weight bring GCSE's table to 323
//   buckets, where the four PRE'd addresses come out in retail's spill-slot order (sp+32, sp+8288,
//   params+112, sp+14512: bucket = (13258 + regno + offset) mod T; 323 is the nearest T above 305
//   that orders them so).
// w17 (2272 to 2346 bytes; 587 of 587 instructions agree by register, two registers differ):
// - The gap loop counts with i, the outer loop's own variable (C style: the outer loop keeps
//   `down` because the inner loop reuses i). k was a pseudo of its own that global-alloc ranked
//   after the entry pointer (1.448 against 1.826), so the pointer took s0; i is s0 already.
// - The angles loop after the anchors has its own `s32 j` (as the anchor loops do): with i
//   from there on, i's life is 390 insns and its priority (1.277) falls below the gap pointer's,
//   which takes s0 from it; with j, i's life starts at the hull and it is placed first.
// - Length's float through ToFloatMoved: the compiler's own qmfc2 instead of the asm's lowers
//   the asm chain's priority in sched2 (38 against the uv[1] store's 37 with ToFloat), so the
//   store issues before the dot's asm, and the argument moves for UnprojectCameraPoint fall
//   after the camera's load, as retail's.
// Still differs: n - 1 for the first sort is s2 where retail has s3. It is GCSE's temporary
// (inserted at the end of the swap's block, after the loop's entry test and params+112, which
// is retail's order); global-alloc places it 64th of 80, both s2 and s3 already used and free
// over its life, and no lower-priority conflicting allocno has a hard-register preference (no
// local-alloc pseudo sits in a saved register), so the first free in the allocation order, s2,
// wins. A user variable for the count (`s32 last = n - 1;` before the loop, reused by the later
// `last = n - 1`) gives s3, but its set then has an earlier LUID than the entry test and sched1
// issues it two slots early; the same variable assigned after the loop is PRE'd into a new
// temporary whose copy dies (s2 again). `entries + 1`, a `Vec02* row = rows + r` (spill slots
// move) and a function-scope j (109 lines) were tried. Also tried (w17, second round): `n--;`
// before the sort and `n++;` after (8 bytes longer), `RingEntry* first = &entries[1];` passed
// (no change), `s32 count = n - 1;` before the angles loop (s2, and issued early), and the sorts
// through an inline `SortEntries(base, count)` (GCSE's table changes size and the four PRE'd
// addresses take other spill slots: 557 lines).
// w19 (tools/globalalloc.py and tools/sched1.py on the dumps; both replays agree with them):
// the GCSE temporary (928, 2 refs over 28 insns, priority 714, 64th of 80) has no preference,
// copy preference or regs_someone_prefers bit, and no allocno of the function prefers s2 or s3
// at all (no local-alloc pseudo sits in a saved register). Raising or lowering its priority
// (--set refs/length) gives s0 or s2, never s3. s2 is in regs_used_so_far long before it (the
// offsets pointer, 11351, takes it 23rd). So retail's s3 needs a conflict with a pseudo global-
// alloc had put in s2, live across the swap block and the angles loop; retail reads no s2 value
// there (the offsets pointer is dead after the anchor loops; s2 is next set by the crossings'
// `sll s2,s5,0x5`), so it would be invisible: a pseudo reload later moved to the stack, such as
// one of the four PRE'd addresses (spilled in both builds, slots 14628-14640). Not found. The
// user variable (`last = n - 1;` set before the angles loop and reused later) still gives s3 by
// its later life's conflicts; its set then precedes the loop's entry test in LUID and sched1
// breaks the priority-2 tie by LUID (slt and the set swap: one pair). Also tried: `entries + 1`.
// w22 (2026-11-11): re-scored, unchanged (the two s2/s3 lines). The PRE-numbering lever that
// matched func_001B55C0 (reaching registers numbered in hash-bucket order break global-alloc's
// priority ties) does not reach it: the n - 1 temporary is not in a tie, both s2 and s3 are free
// over its life, so only a conflict with a pseudo in s2 gives retail's s3 (w19).
// In the context of its file, src/main/player_request.cpp (FLT_MAX is retail's D_0024DC88).
#include "common.h"
#include "shapes.h"
#include "placed_object.h"
#include "vertex_batch.h"
#include "packet_writer.h"
#include "game_clock.h"
#include "vu0.h"

struct AnimRecord;
// A point the ring goes around: an object's position (+0x140) and how far its offsets reach.
struct RingAnchor {
    s32 f0;                 // 0x00
    f32 scale;              // 0x04
    PlacedObject* obj;      // 0x08
};
// A row of the ring's strip: the radius terms, the texture's v, the lift and the colour.
struct RingRow {
    Vec02 shape;            // 0x00: x over the depth, plus y and z times the length
    f32 v;                  // 0x10
    f32 lift;               // 0x14: along +z
    Rgba4 color;            // 0x18
    u8 pad1C[4];
};
// The parameter block of a ring (the DrawPlayerMarkerRing functions' static records).
struct RingParams {
    s32 mode;               // 0x00: 1, u from the angle's distance to pi/2; otherwise from the angle
    f32 uScale;             // 0x04
    f32 rate;               // 0x08: u's scroll per second
    u8 pad0C[4];
    RingRow rows[3];        // 0x10
    AnimRecord* textures[2]; // 0x70: one strip drawn for each that is set
};
// A point of the ring in camera space and its angle about the centre.
struct __attribute__((aligned(16))) RingEntry {
    Vec02 pos;              // 0x00
    f32 angle;              // 0x10
    u8 pad14[0x20 - 0x14];
};
struct Point2 { f32 x; f32 y; };

extern void* g_camera;
extern u8 D_00248D30[];
extern u8 g_identityMatrix[];
extern Vec02 g_unitZVector;
extern PacketWriter g_vifPacketWriter;
extern f32 D_0027506C;
void ProjectPointToCamera(void* cam, Vec02* in, void* out);
void UnprojectCameraPoint(void* cam, Vec02* in, Vec02* out);
f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
f32 WrapModulo(f32 a, f32 m);
void SortElements(void* base, s32 n, s32 size, s32 (*cmp)(RingEntry*, RingEntry*));
s32 CompareSortedTargets(RingEntry* a, RingEntry* b);
void* InitVertexBatch(VertexBatch* b);
void BeginDmaTag(PacketWriter* g);
void SetVertexBatchTransform(VertexBatch* b, u8* a, u8* c);
void SetVertexBatchMode(VertexBatch* b, AnimRecord* r);
void SetVertexTexCoord(VertexBatch* b, f32* uv);
void SetVertexColor(VertexBatch* b, Rgba4* c);
void SetVertexPosition(VertexBatch* b, Vec02* v);
void AddVertex(VertexBatch* b, s32 z);
void FlushVertexBatch(VertexBatch* b);
void CloseDmaTag(PacketWriter* g);
void DestroyVertexBatch(VertexBatch* b, s32 f);

void func_001D5678(Vec02* at, s32 nOffsets, Point2* offsets, s32 nAnchors, RingAnchor* anchors, RingParams* params)
{
    RingEntry entries[256];
    Vec02 pt;
    Vec02 center;
    f32 lowest = 3.4028235e+38f;
    RingEntry* low = 0;
    s32 n = 0;
    s32 i;
    s32 next;
    RingEntry* e;
    ProjectPointToCamera(g_camera, at, &center);
    for (s32 j = 0; j < nAnchors; j++) {
        RingAnchor* anchor = &anchors[j];
        for (s32 k = 0; k < nOffsets; k++) {
            Point2* off = &offsets[k];
            f32 s = anchor->scale;
            u8* cam = (u8*)g_camera;
            Vu0::Vec base = Vu0::Vec::Of(anchor->obj->v140);
            Vu0::Vec sx = Vu0::Vec::Scalar(off->x * s);
            Vu0::Vec ax = Vu0::Vec::Of(*(Vec02*)(cam + 0x90));
            Vu0::Vec sy = Vu0::Vec::Scalar(off->y * s);
            Vu0::Vec ay = Vu0::Vec::Of(*(Vec02*)(cam + 0xA0));
            *(Vu0::Vec*)&pt = Vu0::MulAddX2(base, ax, sx, ay, sy);
            e = &entries[n];
            ProjectPointToCamera(g_camera, &pt, e);
            n++;
            e->pos.z = center.z;
            if (e->pos.y < lowest) {
                lowest = e->pos.y;
                low = e;
            }
        }
    }
    {
        RingEntry t = *low;
        *low = entries[0];
        entries[0] = t;
    }
    for (s32 j = 1; j < n; j++) {
        Vec02 d;
        e = &entries[j];
        *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(entries[0].pos));
        e->angle = ArctangentOfRatio(d.y, d.x);
    }
    SortElements(&entries[1], n - 1, 0x20, CompareSortedTargets);
    RingEntry* top = entries;
    for (i = 0; i < n;) {
        next = i + 1;
        e = &entries[i];
        while (top >= &entries[2]) {
            Vu0::Vec c = Vu0::Cross(Vu0::Sub(Vu0::Vec::Of(top[-1].pos), Vu0::Vec::Of(top[-2].pos)), Vu0::Vec::Of(g_unitZVector));
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(top[-2].pos)), c)) < 0.0f) {
                break;
            }
            top--;
        }
        *top = *e;
        top++;
        i = next;
    }
    n = top - entries;
    entries[n] = entries[0];
    Vec02 lo;
    Vec02 hi;
    lo = hi = center;
    for (i = n - 1; i >= 0; i--) {
        e = &entries[i];
        *(Vu0::Vec*)&lo = Vu0::Min(Vu0::Vec::Of(lo), Vu0::Vec::Of(e->pos));
        *(Vu0::Vec*)&hi = Vu0::Max(Vu0::Vec::Of(hi), Vu0::Vec::Of(e->pos));
    }
    Vu0::Vec half = Vu0::Vec::Scalar(0.5f);
    *(Vu0::Vec*)&center = Vu0::MulXSum(Vu0::Vec::Of(lo), half, Vu0::Vec::Of(hi), half);
    for (i = n - 1; i >= 0; i--) {
        e = &entries[i];
        f32 x0 = e[0].pos.x;
        f32 x1 = e[1].pos.x;
        if ((x0 - center.x) * (x1 - center.x) < 0.0f) {
            f32 t = (center.x - x0) / (x1 - x0);
            Vu0::Vec s0 = Vu0::Vec::Scalar(1.0f - t);
            Vu0::Vec p0 = Vu0::Vec::Of(e[0].pos);
            Vu0::Vec s1 = Vu0::Vec::Scalar(t);
            Vu0::Vec p1 = Vu0::Vec::Of(e[1].pos);
            *(Vu0::Vec*)&entries[n++].pos = Vu0::MulXSum(p0, s0, p1, s1);
        }
    }
    s32 last = n - 1;
    for (i = last; i >= 0; i--) {
        Vec02 d;
        e = &entries[i];
        *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center));
        e->angle = WrapAngle(ArctangentOfRatio(d.y, d.x));
    }
    SortElements(entries, n, 0x20, CompareSortedTargets);
    entries[n] = entries[0];
    {
        Vu0::Vec prev = Vu0::Vec::Of(e[n].pos);
        f32 prevAngle = e[n].angle;
        for (i = last; i >= 0;) {
            s32 down = i - 1;
            Vu0::Vec from;
            Vu0::Vec to;
            from = prev;
            to = Vu0::Vec::Of(entries[i].pos);
            prev = to;
            f32 a = prevAngle;
            prevAngle = entries[i].angle;
            s32 steps = (s32)(__builtin_fabsf(WrapAngle(a - prevAngle)) / D_0027506C);
            if (steps > 0) {
                for (i = 0; i < steps;) {
                    i++;
                    f32 t = (f32)i / (f32)(steps + 1);
                    Vec02 d;
                    e = &entries[n++];
                    *(Vu0::Vec*)&e->pos = Vu0::MulXSum(to, Vu0::Vec::Scalar(1.0f - t), from, Vu0::Vec::Scalar(t));
                    *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center));
                    e->angle = ArctangentOfRatio(d.y, d.x);
                }
            }
            i = down;
        }
    }
    SortElements(entries, n, 0x20, CompareSortedTargets);
    entries[n] = entries[0];
    VertexBatch batch;
    InitVertexBatch(&batch);
    BeginDmaTag(&g_vifPacketWriter);
    SetVertexBatchTransform(&batch, D_00248D30, g_identityMatrix);
    Vec02 rows[3];
    s32 r;
    for (r = 0; r < 3; r++) {
        rows[r] = params->rows[r].shape;
        rows[r].x = rows[r].x / center.z;
        rows[r].z = rows[r].z * center.z;
    }
    for (s32 s = 0; s < 2; s++) {
        AnimRecord* tex = params->textures[s];
        if (tex == 0) {
            continue;
        }
        f32 prev = -3.1415927f;
        SetVertexBatchMode(&batch, tex);
        f32 u0 = WrapModulo(g_gameClock.time * params->rate, 1.0f);
        for (i = 0; i <= n;) {
            Vec02 d;
            f32 uv[2];
            next = i + 1;
            e = &entries[i];
            *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center));
            f32 a = e->angle;
            while (a < prev) {
                a += 6.2831855f;
            }
            prev = a;
            switch (params->mode) {
            case 0:
            default:
                uv[0] = u0 + params->uScale * a * 0.15915494f;
                break;
            case 1:
                uv[0] = u0 + params->uScale * __builtin_fabsf(WrapAngle(a - 1.5707964f)) * 0.15915494f;
                break;
            }
            for (r = s; r <= s + 1; r++) {
                uv[1] = params->rows[r].v;
                f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(d)));
                Vu0::Vec w = Vu0::Vec::Scalar(((rows + r)->x + len * ((rows + r)->y + len * (rows + r)->z)) / len);
                *(Vu0::Vec*)&pt = Vu0::MulAddX2(Vu0::Vec::Of(center), Vu0::Vec::Of(d), w, Vu0::Vec::Of(g_unitZVector), Vu0::Vec::ScalarAtValue(params->rows[r].lift));
                UnprojectCameraPoint(g_camera, &pt, &pt);
                SetVertexTexCoord(&batch, uv);
                Rgba4 c = params->rows[r].color;
                SetVertexColor(&batch, &c);
                SetVertexPosition(&batch, &pt);
                AddVertex(&batch, 0);
            }
            i = next;
        }
        FlushVertexBatch(&batch);
    }
    CloseDmaTag(&g_vifPacketWriter);
    DestroyVertexBatch(&batch, 2);
}
