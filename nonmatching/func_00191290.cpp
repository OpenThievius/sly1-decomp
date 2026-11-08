// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 724/732, checked 2026-11-07
// NEAR: 732 bytes, the frame, the calls and every VU0 sequence are retail's. The registers of the
//       two three-step loops are not: retail holds the first temporary node's address in $s0 and
//       walks the link records with $a1 and a counter in $a3 (the second loop counts $t0 down),
//       ours uses $a3 for the records and $t1 for the counter, and loads the vertex count straight
//       into the register of the result (retail: movz of a copy). About 30 compiles (pointers or
//       indices for the walks, the node as a pointer variable, the minimum written both ways).
#include "common.h"
#include "point_graph_object.h"
#include "placed_object.h"
#include "vu0.h"

struct PlaneNode;
s32 func_00190810(PlaneNode* node, Vec02* p);
s32 func_001908C0(PlaneNode* node, Vec02* p);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
s32* AllocateBackMemory(s32 bytes);
void SimplifyPointPath(void* a0, s32* a1, s32* a2);

struct PathNode;

struct PathLink {
    PathNode* a;
    PathNode* b;
    f32 length;
};

struct PathNode {
    Vec02 pos;
    s32 count;
    PathLink** links;
    u8 pad18[8];
};

void SnapPointToPointGraph(PointGraph* graph, Vec02* in, Vec02* out);
void SearchPointGraph(PointGraph* graph, PathNode* from, PathNode* goal, s32 limit, s32* outCount, PathNode** outPath);

s32 func_00191290(PointGraph* graph, Vec02* start, Vec02* goal, s32 maxOut, Vec02* out)
{
    Vec02 a;
    Vec02 b;
    PathNode* faces = (PathNode*)graph->faces;
    PathNode** tri0 = (PathNode**)func_00190810((PlaneNode*)faces, start);
    if (tri0 != 0) {
        a = *start;
    } else {
        SnapPointToPointGraph(graph, start, &a);
        tri0 = (PathNode**)func_001908C0((PlaneNode*)faces, &a);
    }
    PathNode** tri1 = (PathNode**)func_00190810((PlaneNode*)faces, goal);
    if (tri1 != 0) {
        b = *goal;
    } else {
        SnapPointToPointGraph(graph, goal, &b);
        tri1 = (PathNode**)func_001908C0((PlaneNode*)faces, &b);
    }
    if (tri0 == tri1) {
        out[0] = a;
        out[1] = b;
        return 2;
    }
    PushBackMemoryMark();
    PathNode** path = (PathNode**)AllocateBackMemory(0x200);
    PathNode node1;
    PathLink links1[3];
    PathNode node2;
    PathLink links2[3];
    s32 count;
    PathNode* n1 = &node1;
    n1->pos = a;
    n1->count = 3;
    n1->links = (PathLink**)AllocateBackMemory(12);
    PathNode** tp = tri0;
    PathLink* l = links1;
    for (s32 i = 0; i < 3; i++) {
        l->a = n1;
        PathNode* c = *tp;
        l->b = c;
        u128 d = Vu0::Sub(Vu0::Q(n1->pos), Vu0::Q(c->pos));
        *(u32*)&l->length = Vu0::ToBits(Vu0::Sqrt(Vu0::DotXY(d, d)));
        n1->links[i] = l;
        tp++;
        l++;
    }
    node2.pos = b;
    node2.count = 0;
    node2.links = 0;
    tp = tri1;
    l = links2;
    for (s32 i = 0; i < 3; i++) {
        PathNode* corner = *tp;
        l->a = corner;
        l->b = &node2;
        u128 d = Vu0::Sub(Vu0::Q(corner->pos), Vu0::Q(node2.pos));
        *(u32*)&l->length = Vu0::ToBits(Vu0::Sqrt(Vu0::DotXY(d, d)));
        corner->links[corner->count] = l;
        corner->count++;
        tp++;
        l++;
    }
    SearchPointGraph(graph, n1, &node2, 0x80, &count, path);
    if (count >= 3) {
        SimplifyPointPath(graph->faces, &count, (s32*)path);
    }
    s32 n = maxOut < count ? maxOut : count;
    for (s32 i = 0; i < n; i++) {
        out[i] = path[i]->pos;
    }
    for (s32 i = 0; i < 3; i++) {
        tri1[i]->count--;
    }
    PopBackMemoryMark();
    return n;
}
