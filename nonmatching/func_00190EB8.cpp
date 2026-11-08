// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 616/624, checked 2026-11-07
// NEAR: 14 instructions differ. The branch for `other == goal` is laid out differently (retail:
//       bne past a `b` with `move v0, zero` in its delay slot, ours cross-jumps it to the shared
//       `move v0, zero` and branches with beq), the start node's stores and node->parent are
//       ordered differently, and one store after the tail call. About 30 compiles (the test as an
//       inline function with early returns, a ternary, a flag variable, the node creation inside
//       the if).
#include "common.h"
#include "point_graph_object.h"
#include "placed_object.h"
#include "vu0.h"

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
s32* AllocateBackMemory(s32 bytes);
s32* AllocateZeroedBackMemory(s32 bytes);
s32 GetPointGraphItemIndex(PointGraph* p, s32 x);

struct SearchLink {
    GraphPoint* a;
    GraphPoint* b;
    f32 length;
};

struct SearchNode {
    GraphPoint* point;
    f32 score;
    f32 cost;
    SearchNode* parent;
    s32 depth;
    SearchNode* next;
};

static inline s32 Test(s32* slot)
{
    if (*slot != 0) return 1;
    *slot = 1;
    return 0;
}

static inline s32 WasSearched(PointGraph* graph, s32* seen, GraphPoint* p, GraphPoint* goal)
{
    return (p == goal) ? 0 : Test(&seen[GetPointGraphItemIndex(graph, (s32)p)]);
}

void func_00190EB8(PointGraph* graph, GraphPoint* from, GraphPoint* goal, s32 unused, s32* outCount, GraphPoint** outPath)
{
    SearchNode start;
    SearchNode* open;
    PushBackMemoryMark();
    s32* seen = AllocateZeroedBackMemory(graph->pointCount << 2);
    SearchNode* cur = &start;
    open = 0;
    outPath[0] = from;
    start.point = from;
    start.cost = 0.0f;
    start.parent = 0;
    start.depth = 1;
    u128 d = Vu0::Sub(Vu0::Q(*(Vec02*)from), Vu0::Q(*(Vec02*)goal));
    start.score = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
    if (from != goal) {
        do {
            GraphPoint* here = cur->point;
            for (s32 i = 0; i < here->linkCount; i++) {
                SearchLink* link = (SearchLink*)here->links[i];
                GraphPoint* other = link->a;
                if (other == here) other = link->b;
                if (WasSearched(graph, seen, other, goal)) continue;
                SearchNode* node = (SearchNode*)AllocateBackMemory(sizeof(SearchNode));
                node->point = other;
                f32 cost = cur->cost + link->length;
                node->cost = cost;
                node->parent = cur;
                u128 e = Vu0::Sub(Vu0::Q(*(Vec02*)here), Vu0::Q(*(Vec02*)goal));
                node->score = cost + Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(e, e)));
                node->depth = cur->depth + 1;
                SearchNode** pp = &open;
                SearchNode* c = open;
                while (c != 0 && !(node->score < c->score)) {
                    pp = &c->next;
                    c = c->next;
                }
                node->next = c;
                *pp = node;
            }
            cur = open;
            if (cur == 0) break;
            open = cur->next;
        } while (cur->point != goal);
    }
    if (cur != 0) {
        *outCount = cur->depth;
        while (cur != 0) {
            outPath[cur->depth - 1] = cur->point;
            cur = cur->parent;
        }
    } else {
        *outCount = 0;
    }
    PopBackMemoryMark();
}
