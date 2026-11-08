// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1620/1716 (94.4%), checked 2026-11-08
// NEAR (2026-11-08, night-large5): func_00186BA8 (the contacts between two colliders' edge hits,
// 1716 bytes): same size and frame; the hit grouping, the face search per edge group, the paths
// between groups (FindGraphPath, FindSegmentClosestParams, two blends) and the edge-against-face
// contacts follow retail. Left: the spill slots of the keys and groups addresses swap (0x752C and
// 0x7530); in the path loop retail loads params[1] early (its 1 - t1 in f0, t1 in f1) and runs
// both weight pairs before the first MulXSum, where ours computes them pair by pair; the two dots
// against e->r2/r3 take v1/a1 in retail (ours a1/v0) and the last contact's dot v0 (ours v1).
#include "common.h"
#include "vu0.h"
#include "collider.h"

struct MeshFace {
    Vec02 normal;           // 0x00
    f32 dist;               // 0x10
    u8 pad14[0x1C - 0x14];
    u16 flags;              // 0x1C
    u8 pad1E[2];
};

struct MeshEdge {
    union {
        struct {
            s16 x;          // 0x00
            s16 y;          // 0x02
        };
        s16 v[2];           // 0x00
    };
    s16 face[2];            // 0x04
    u8 pad08[0x10 - 8];
};

struct MeshHit {
    Vec02 r0;               // 0x00
    Vec02 r1;               // 0x10
    Vec02 r2;               // 0x20
    Vec02 r3;               // 0x30
    f32 f40;                // 0x40
    f32 f44;                // 0x44
    u8 pad48[0x50 - 0x48];
    union {
        s32 i50;            // 0x50
        void* p50;
        MeshFace* face50;
    };
    union {
        s32 i54;            // 0x54
        MeshFace* face54;
    };
    MeshEdge* edge;         // 0x58
    s32 slot5C;             // 0x5C
    MeshHit* next;          // 0x60
};

struct PooledContact {
    u8 pad0[0x9C];
    s32 kind;               // 0x9C
    void* a;                // 0xA0
    void* b;                // 0xA4
    u8 padA8[0xD0 - 0xA8];
    PooledContact* next;    // 0xD0
};

s32 CollectEdgeContacts(s32 unused, Collider* self, u8* ctx, s32 cap, MeshHit* out);
s32 func_00186568(Collider* a, Collider* b, void* c, void* d, s32 cap, MeshHit* out);
void GroupEdgesByKey(s32 count, MeshHit* base, s32* outCount, s32* keys, MeshHit** groups, MeshHit** head);
s32 FindGraphPath(MeshFace* base, s32 key, s32 target, MeshHit* head, MeshHit** out);
void FindSegmentClosestParams(Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* t, f32* depth, Vec02* normal);
s32 CreatePooledContact(f32 f, Collider* a0, Collider* a1, void* a2, void* a3, s32 a4, void* a5, void* a6, PooledContact** a7);

extern const f32 D_0024B258;

static inline f32 FaceDotMoved(const Vec02& p, const MeshFace* f)
{
    return Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(p), Vu0::Vec::Of(f->normal)));
}

static inline f32 FaceDot(const Vec02& p, const MeshFace* f)
{
    return Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(p), Vu0::Vec::Of(f->normal)));
}

void func_00186BA8(Collider* self, Collider* other, void* a2, void* a3, u8* ctx, PooledContact** list)
{
    s32 counts[2];
    MeshHit hits[2][0x80];
    s32 groupCounts[2];
    s32 keys[2][64];
    MeshHit* groups[2][64];
    MeshHit* heads[2];
    Collider* objs[2];
    MeshHit* path[32];
    f32 params[2];
    Vec02 normal;
    Vec02 pts[2];
    Vec02* seg[4];
    f32 depth;
    s32 i;
    s32 j;
    MeshHit* e;

    counts[0] = CollectEdgeContacts((s32)other, self, ctx, 0x80, hits[0]);
    counts[1] = func_00186568(self, other, a2, a3, 0x80, hits[1]);
    if (counts[0] == 0 && counts[1] == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        GroupEdgesByKey(counts[i], hits[i], &groupCounts[i], keys[i], groups[i], &heads[i]);
    }
    objs[0] = self;
    objs[1] = other;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < groupCounts[i]; j++) {
            MeshHit* g = groups[i][j];
            s32 key = keys[i][j];
            Vec02* verts = (Vec02*)objs[0]->meshCopy.verts;
            Vec02* kp = &verts[key];
            f32 best = D_0024B258;
            MeshFace* bestFace = 0;
            f32 bestDot;
            MeshHit* h;
            MeshHit* c;
            for (c = g; c != 0; c = c->next) {
                MeshFace* f = c->face54;
                if (f->flags & 8) {
                    continue;
                }
                f->flags |= 8;
                f32 d = FaceDot(*kp, f);
                f32 m = d;
                for (h = g; h != 0; h = h->next) {
                    if (h->face54 == f) {
                        continue;
                    }
                    f32 d2 = FaceDot(verts[h->edge->v[1 - h->slot5C]], f);
                    if (d2 < m) {
                        m = d2;
                    }
                }
                m -= f->dist;
                if (best < m) {
                    bestFace = f;
                    best = m;
                    bestDot = d;
                }
            }
            for (c = g; c != 0; c = c->next) {
                c->face54->flags &= ~8;
            }
            CreatePooledContact(bestDot - bestFace->dist, objs[0], objs[1], kp, bestFace, 1,
                                &((Vec02*)objs[0]->meshCopy.verts)[key], bestFace, list);
            for (h = g; h != 0; h = h->next) {
                if (h->face54 == bestFace) {
                    continue;
                }
                f32 d = FaceDot(h->r1, bestFace);
                if (d < bestDot) {
                    CreatePooledContact(d - bestFace->dist, objs[0], objs[1], &h->r1, bestFace, 2, h->edge,
                                        bestFace, list);
                }
            }
        }
        Collider* t = objs[0];
        objs[0] = objs[1];
        objs[1] = t;
    }
    for (e = heads[0]; e != 0; e = e->next) {
        if (e->face50 == 0) {
            continue;
        }
        if (e->face54 == 0) {
            continue;
        }
        MeshFace* faces = (MeshFace*)other->meshCopy.faces;
        s32 n = FindGraphPath(faces, e->face50 - faces, e->face54 - faces, heads[1], path);
        if (n > 0) {
            for (s32 k = 0; k < n; k++) {
                MeshHit* h = path[k];
                Vec02* va = (Vec02*)self->meshCopy.verts;
                Vec02* vb = (Vec02*)other->meshCopy.verts;
                seg[0] = &va[e->edge->v[0]];
                seg[1] = &va[e->edge->v[1]];
                seg[2] = &vb[h->edge->v[0]];
                seg[3] = &vb[h->edge->v[1]];
                FindSegmentClosestParams(seg[0], seg[1], seg[2], seg[3], params, &depth, &normal);
                Vu0::Set(pts[0], Vu0::MulXSum(Vu0::Vec::Of(*seg[0]), Vu0::Vec::Scalar(1.0f - params[0]),
                                              Vu0::Vec::Of(*seg[1]), Vu0::Vec::Scalar(params[0])).q);
                Vu0::Set(pts[1], Vu0::MulXSum(Vu0::Vec::Of(*seg[2]), Vu0::Vec::Scalar(1.0f - params[1]),
                                              Vu0::Vec::Of(*seg[3]), Vu0::Vec::Scalar(params[1])).q);
                CreatePooledContact(-depth, self, other, pts, &normal, 3, e->edge, h->edge, list);
            }
        } else {
            MeshEdge* edge = e->edge;
            for (s32 k = 0; k < counts[1]; k++) {
                MeshHit* h = &hits[1][k];
                MeshFace* faces = (MeshFace*)self->meshCopy.faces;
                if (h->face50 == &faces[edge->face[0]] || h->face50 == &faces[edge->face[1]] ||
                    h->face54 == &faces[edge->face[0]] || h->face54 == &faces[edge->face[1]]) {
                    goto next;
                }
            }
            Vu0::Vec pos = Vu0::Vec::Of(self->v140);
            f32 d0 = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(pos, Vu0::Vec::Of(e->r0)), Vu0::Vec::Of(e->r2)));
            f32 d1 = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(pos, Vu0::Vec::Of(e->r1)), Vu0::Vec::Of(e->r3)));
            MeshFace* face;
            s32 end = e->slot5C;
            if (d1 < d0) {
                face = e->face50;
                end = 1 - end;
            } else {
                face = e->face54;
            }
            Vec02* p = &((Vec02*)self->meshCopy.verts)[edge->v[end]];
            PooledContact* c;
            for (c = *list; c != 0; c = c->next) {
                if (c->kind == 1 && c->a == p && c->b == face) {
                    break;
                }
            }
            if (c != 0) {
                continue;
            }
            CreatePooledContact(FaceDotMoved(*p, face) - face->dist, self, other, p, face, 1, p, face, list);
        }
    next:;
    }
}
