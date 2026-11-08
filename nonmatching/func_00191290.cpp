// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 724/732, checked 2026-11-07
// NEAR: (2026-11-08, night-size3) the size is retail's now: the start node's fields are written as
// node1's own (retail's sw 48(sp), 52(sp) and its links reloaded from 52(sp)), and the corner's
// count is read once (corner->links[corner->count++] = l). Still differs, registers only: retail
// keeps a copy of &node1 in t3 for the search, walks the first loop's links with a1 and its
// counter in a3 (here a3 and t1) and the second's counter in t0 (here a1), and forms the path's
// count with a copy of maxOut and movz (move s0,s7; movz s0,v1), where every form of the minimum
// here (if, ternary both ways, an inline function) gives movn into the count's register. Earlier:
// about 30 compiles (pointers or indices for the walks, the node as a pointer variable, the
// minimum written both ways).
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
    node1.pos = a;
    node1.count = 3;
    node1.links = (PathLink**)AllocateBackMemory(12);
    PathNode** tp = tri0;
    PathLink* l = links1;
    for (s32 i = 0; i < 3; i++) {
        l->a = n1;
        PathNode* c = *tp;
        l->b = c;
        u128 d = Vu0::Sub(Vu0::Q(n1->pos), Vu0::Q(c->pos));
        *(u32*)&l->length = Vu0::ToBits(Vu0::Sqrt(Vu0::DotXY(d, d)));
        node1.links[i] = l;
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
        corner->links[corner->count++] = l;
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
