// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1755/2348 (74.7%), checked 2026-11-10
// NEAR (2026-11-10, w14): DrawAngleSortedRing (func_001D5678): the points around the anchors
// projected into camera space, the lowest first, their angles about it and the sort, the hull (a
// Graham scan against the z axis), the bounds' centre, the points where the hull crosses the
// centre's x, the angles about the centre, the gaps filled every D_0027506C radians, then the
// strip drawn once per texture with two rows of the three. Retail's size (587 instructions) and
// frame (0x3A00). What got there (earlier rounds): one index variable for the loops after the
// anchors, next and down at the top of the hull and gap loops, lo and hi at function scope, the
// rows read through params by index, the colour copied as an Rgba4.
// What got there (w14, 581 to 587, 483 to 523 of 587 instructions agreeing by register):
// - The lift is Vec::ScalarAtValue(params->rows[r].lift) (lw straight into qmtc2's GPR). With
//   the reference ScalarAt, params (17 refs over 438 insns: 4*17/438 = 0.155) outranks nOffsets
//   (5 refs over 68: 2*5/68 = 0.147) in global-alloc and takes s8; ScalarAtValue lengthens
//   params' life and nOffsets gets s8 again, as in retail, params spilled at 14588(sp).
// - One `RingEntry* e;` at function scope, reused by every loop (C style). Each loop's
//   `e = &entries[i]` is a user variable's giv that is not replaceable (its register is set
//   before, or read after, the loop), so loop.c reduces it into a register of its own and copies
//   it into e at the loop top: retail's `addu v0,v0,sp; move s1,v0 ... addiu v0,s1,-32`. In the
//   anchors' loop, `e = &entries[n]` passed to the call is not worth reducing (a user variable
//   not replaceable pays copy_cost: benefit 6 - 4 - 4 < 0), so retail recomputes it each time
//   (sll; addu s1,sp,v0) while e's uses after n++ reduce to s0 from sp-32.
// - The gap loop's first point is read through e after the loop over the angles about the
//   centre (`e[n]`, e then &entries[0]): retail's `addu a1,s2,s1`. No other form found gives it;
//   it is the one part of this attempt that is not plausibly the original's as written.
// Still differs: the anchors' inner loop's schedule (the weights' loads); the gap loop's inner
// insert (`e = &entries[n]; ... n++;` gives a copy, `e = &entries[n++];` retail's -32 offsets but
// two instructions short, as the next point: retail adds them in the draw); the rows' copy
// counter (a2 for retail's s4) and the draw loop: retail recomputes &rows (sp+14512) in the
// i loop's preheader and spills it (14644), where PRE hoists ours to the entry with the copy
// loop's (expression 130 redundant in bb 38), and keeps next = i + 1 in s8 (`move s0,s8`) where
// ours spills it (s+1 takes s8).
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
    RingEntry* e;
    ProjectPointToCamera(g_camera, at, &center);
    for (s32 j = 0; j < nAnchors; j++) {
        RingAnchor* anchor = &anchors[j];
        for (s32 k = 0; k < nOffsets; k++) {
            Point2* off = &offsets[k];
            f32 s = anchor->scale;
            u8* cam = (u8*)g_camera;
            Vu0::Q(pt) = Vu0::MulAddX2(Vu0::Vec::Of(anchor->obj->v140), Vu0::Vec::Of(*(Vec02*)(cam + 0x90)), Vu0::Vec::Scalar(off->x * s),
                                       Vu0::Vec::Of(*(Vec02*)(cam + 0xA0)), Vu0::Vec::Scalar(off->y * s)).q;
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
    for (i = 1; i < n; i++) {
        Vec02 d;
        e = &entries[i];
        Vu0::Q(d) = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(entries[0].pos)).q;
        e->angle = ArctangentOfRatio(d.y, d.x);
    }
    SortElements(&entries[1], n - 1, 0x20, CompareSortedTargets);
    RingEntry* top = entries;
    for (i = 0; i < n;) {
        s32 next = i + 1;
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
        Vu0::Q(lo) = Vu0::Min(Vu0::Vec::Of(lo), Vu0::Vec::Of(e->pos)).q;
        Vu0::Q(hi) = Vu0::Max(Vu0::Vec::Of(hi), Vu0::Vec::Of(e->pos)).q;
    }
    Vu0::Vec half = Vu0::Vec::Scalar(0.5f);
    Vu0::Q(center) = Vu0::MulXSum(Vu0::Vec::Of(lo), half, Vu0::Vec::Of(hi), half).q;
    for (i = n - 1; i >= 0; i--) {
        e = &entries[i];
        f32 x0 = e[0].pos.x;
        f32 x1 = e[1].pos.x;
        if ((x0 - center.x) * (x1 - center.x) < 0.0f) {
            f32 t = (center.x - x0) / (x1 - x0);
            Vu0::Q(entries[n].pos) = Vu0::MulXSum(Vu0::Vec::Of(e[0].pos), Vu0::Vec::Scalar(1.0f - t), Vu0::Vec::Of(e[1].pos), Vu0::Vec::Scalar(t)).q;
            n++;
        }
    }
    s32 last = n - 1;
    for (i = last; i >= 0; i--) {
        Vec02 d;
        e = &entries[i];
        Vu0::Q(d) = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center)).q;
        e->angle = WrapAngle(ArctangentOfRatio(d.y, d.x));
    }
    SortElements(entries, n, 0x20, CompareSortedTargets);
    entries[n] = entries[0];
    {
        f32 prevAngle = e[n].angle;
        Vu0::Vec prev = Vu0::Vec::Of(e[n].pos);
        for (i = last; i >= 0;) {
            s32 down = i - 1;
            Vu0::Vec from = prev;
            Vu0::Vec to = Vu0::Vec::Of(entries[i].pos);
            prev = to;
            f32 a = prevAngle;
            prevAngle = entries[i].angle;
            s32 steps = (s32)(__builtin_fabsf(WrapAngle(a - prevAngle)) / D_0027506C);
            if (steps > 0) {
                for (s32 k = 0; k < steps;) {
                    k++;
                    f32 t = (f32)k / (f32)(steps + 1);
                    Vec02 d;
                    e = &entries[n];
                    Vu0::Q(e->pos) = Vu0::MulXSum(to, Vu0::Vec::Scalar(1.0f - t), from, Vu0::Vec::Scalar(t)).q;
                    Vu0::Q(d) = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center)).q;
                    e->angle = ArctangentOfRatio(d.y, d.x);
                    n++;
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
    for (s32 k = 0; k < 3; k++) {
        rows[k] = params->rows[k].shape;
        rows[k].x = rows[k].x / center.z;
        rows[k].z = rows[k].z * center.z;
    }
    for (s32 s = 0; s < 2; s++) {
        AnimRecord* tex = params->textures[s];
        if (tex == 0) {
            continue;
        }
        f32 prev = -3.1415927f;
        SetVertexBatchMode(&batch, tex);
        f32 u0 = WrapModulo(g_gameClock.time * params->rate, 1.0f);
        for (i = 0; i <= n; i++) {
            Vec02 d;
            f32 uv[2];
            e = &entries[i];
            Vu0::Q(d) = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center)).q;
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
            for (s32 r = s; r <= s + 1; r++) {
                uv[1] = params->rows[r].v;
                f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Vec::Of(d)));
                Vu0::Vec lift = Vu0::Vec::ScalarAtValue(params->rows[r].lift);
                Vu0::Q(pt) = Vu0::MulAddX2(Vu0::Vec::Of(center), Vu0::Vec::Of(d), Vu0::Vec::Scalar((rows[r].x + len * (rows[r].y + len * rows[r].z)) / len), Vu0::Vec::Of(g_unitZVector), lift).q;
                UnprojectCameraPoint(g_camera, &pt, &pt);
                SetVertexTexCoord(&batch, uv);
                Rgba4 c = params->rows[r].color;
                SetVertexColor(&batch, &c);
                SetVertexPosition(&batch, &pt);
                AddVertex(&batch, 0);
            }
        }
        FlushVertexBatch(&batch);
    }
    CloseDmaTag(&g_vifPacketWriter);
    DestroyVertexBatch(&batch, 2);
}
