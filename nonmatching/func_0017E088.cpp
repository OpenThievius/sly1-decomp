// SPDX-License-Identifier: AGPL-3.0-or-later
// BROKEN, checked 2026-11-07
// NEAR: wave 4 e3. 828 bytes, same size; about 40 of 207 words differ, all in the edge-group case (kind 2): its running sum is
//       in vf2/vf3 where retail has vf3/vf4 and the final normalisation loads the sum twice (vf4 for the length, vf2 in the
//       delay slot of the test), where ours loads it once and, with the DivX hoisted above the test, uses bc1fl. Kinds 1 and 3
//       and the tail call are retail's. The locals share one 0x100 buffer (the entries of kind 1, kind 2's tmp and span).
//       ~14 compiles (NormalizeOr, hand-expanded normalisation in three forms, buffer or separate locals, case order).
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"

struct EdgeNode : MeshEdge {
    EdgeNode* next8;
    EdgeNode* nextC;
};
struct EdgeGroup {
    u8 pad00[8];
    f32 f8;
    u8 padC[8];
    EdgeNode* list14;
    EdgeNode* list18;
};
s32 CollectEntriesForKey(Mesh03* mesh, Tree03* tree, s32 index, s32 max, MeshEdge** out);
s32 CollectTreeNodeSpans(TreeNode03* nodes, Vec02* a, Vec02* b, s32 c, s32 d, ColliderSpan* out);
s32 TestProbeSegmentsAgainstColliders(Collider* self, void* ctx, Quad16* src);
extern const Vec02 D_00248D30;
s32 func_0017E088(Collider* self, Collider* part, Vec02* point, s32 kind, void* arg, Vec02* out)
{
    u8 buf[0x100] __attribute__((aligned(16)));
    Vec02 gap;
    Vec02 sum;
    switch (kind) {
    case 1: {
        Mesh03* mesh = &part->meshCopy;
        u128 acc = Vu0::Q(D_00248D30);
        s32 found = 0;
        s32 n = CollectEntriesForKey(mesh, &part->tree, (Vec02*)arg - (Vec02*)mesh->verts, 0x40, (MeshEdge**)buf);
        for (s32 i = 0; i < n; i++) {
            if (func_0017DCE0(self, part, ((MeshEdge**)buf)[i], &gap) != 0) {
                found = 1;
                acc = Vu0::Add(acc, Vu0::Q(gap));
            }
        }
        if (found == 0) {
            return 0;
        }
        Vu0::Q(*out) = Vu0::NormalizeOr(acc, Vu0::Q(g_unitXVector));
        break;
    }
    case 3:
        if (func_0017DCE0(self, part, (MeshEdge*)arg, out) == 0) {
            return 0;
        }
        break;
    case 2: {
        EdgeGroup* g = (EdgeGroup*)arg;
        if (g->f8 < 0.7f) {
            return 0;
        }
        sum = D_00248D30;
        s32 found = 0;
        Vec02* verts;
        for (EdgeNode* e = g->list14; e != 0; e = e->next8) {
            if (func_0017DCE0(self, part, e, (Vec02*)buf) != 0) {
                verts = (Vec02*)part->meshCopy.verts;
                if (CollectTreeNodeSpans(self->tree.nodes, verts + e->vertA, verts + e->vertB, 0, 2, (ColliderSpan*)(buf + 0x10)) > 0) {
                    found = 1;
                    Vu0::Q(sum) = Vu0::Add(Vu0::Q(sum), Vu0::Q(*(Vec02*)buf));
                }
            }
        }
        for (EdgeNode* e = g->list18; e != 0; e = e->nextC) {
            if (func_0017DCE0(self, part, e, (Vec02*)buf) != 0) {
                verts = (Vec02*)part->meshCopy.verts;
                if (CollectTreeNodeSpans(self->tree.nodes, verts + e->vertA, verts + e->vertB, 0, 2, (ColliderSpan*)(buf + 0x10)) > 0) {
                    found = 1;
                    Vu0::Q(sum) = Vu0::Add(Vu0::Q(sum), Vu0::Q(*(Vec02*)buf));
                }
            }
        }
        if (found == 0) {
            return 0;
        }
        u128 fb = Vu0::Q(g_unitXVector);
        u128 len = Vu0::Length(Vu0::Q(sum));
        u128 r;
        if (Vu0::ToFloat(len) < 0.0001f) {
            r = fb;
        } else {
            r = Vu0::DivX(Vu0::Q(sum), len);
        }
        Vu0::Q(*out) = r;
        break;
    }
    default:
        break;
    }
    return TestProbeSegmentsAgainstColliders(self, point, (Quad16*)out);
}
