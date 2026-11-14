// SPDX-License-Identifier: AGPL-3.0-or-later
// The active-set solver, 0x1533A8 to 0x1549C8 (its .rodata from 0x24A100, its .data from
// 0x261F30 to 0x261F70; no .bss of its own): DrawPlacedObjectParts, then InitActiveSetSolver to
// SolveActiveSetSystem, the bounded linear solve the contact code runs for its impulses. Its
// .rodata provably starts a file: the display-list writer's base vtable D_0024A0E0, which
// pooled_object.cpp's PacketWriter (its one virtual func_00152E18) brings, lies just before
// PivotActiveSet's jump table at 0x24A100, and GCC 2.95 writes a file's vtables after all of its
// functions' literals and jump tables (a test unit built whole puts its vtable after the jump
// table of a function defined after the class's methods), so that vtable ends the previous
// file's .rodata. Its .data provably starts a file too: D_00261F30, the matrix
// DrawPlacedObjectParts hands MultiplyMatrices, which reads it with lqc2, is 16-aligned (Mat4A),
// and pooled_object.cpp's .data starts at 0x261CC8, 8 mod 16, so the matrix cannot lie inside
// it; the 8 zero bytes before it are the linker's padding. Its start in the code is a choice: any
// function start from 0x152E20 (after the vtable's method) to 0x1533A8 links to the same bytes,
// since the functions between read no .rodata or .data of either file, and DrawPlacedObjectParts,
// the matrix's one reader, belongs with it. The cut is at DrawPlacedObjectParts, the latest
// start the data allows (its caller QueuePlacedObjectDraw stays in pooled_object.cpp); the
// solver's own functions begin at InitActiveSetSolver. The name is ours, after its role.
#include "common.h"
#include "gauge_manager.h"
#include "asm_func.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "world.h"
#include "screen_element.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "list_iter.h"
#include "texture_render_object.h"
#include "step_sequence.h"
#include "animation.h"
#include "attachment.h"
#include "camera.h"
#include "flagged_object.h"
#include "packet_writer.h"
#include "globals.h"
#include "game_progress.h"
#include "threshold_range.h"
#include "pad_record.h"
#include "active_set_solver.h"
#include "buffered_stream.h"
#include "texture_header.h"
#include "range_record.h"
#include "effect_spawner.h"
#include "effect_owner.h"
#include "effect.h"
#include "deferred_request.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "owner_message.h"
#include "switched_collider.h"
#include "vu0.h"
#include "fpu.h"
#include "functions/active_set_solver.h"
#include "functions/collider.h"
#include "functions/heap.h"
#include "functions/placed_object_model.h"
#include "functions/pooled_object.h"
#include "functions/symmetric_solve.h"
#include "functions/warp_menu.h"

extern "C" void* FillMemory(void* p, s32 value, s32 size);

// What DrawPlacedObjectParts hands the part drawer (DrawModelPart) for each part: the object's
// transform, the object, its record at +0x22C, the part, and the view matrix.
// The range record of a placed object (TextureRenderObject::drawRange): the clip-space matrix
// of its draw range at 0x70.
struct DrawRangeRecord {
    u8 pad00[0x70];
    u8 m70[0x40];
};

struct PartDrawFrame {
    void* fn;
    u8 pad0[4];
    s32 kind;
    u8 pad1[0x10 - 0x0C];
    DrawTransform copy;
    u8 pad2[0x70 - 0x60];
    TextureRenderObject* object;
    void* record;
    void* part;
    u8 pad3[0x80 - 0x7C];
    Quad16 q80[4];
    Quad16 qC0[4];
};


extern "C" void* FillMemory(void* p, s32 value, s32 size);
void* MultiplyMatrices(Quad16* out, void* b, void* in);
struct PartDrawRequest;

// The file's .data: the view matrix DrawPlacedObjectParts multiplies the object's transform by.
Mat4A g_unitSquareToClipMatrix = { { { 2.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { -1.0f, -1.0f, 0.0f, 1.0f } } };

// Deferred draw callback of a placed object with a model: sends the object's first DMA packet,
// builds the transform of the view (clip matrix times the object's draw range matrix), draws each
// of its 0x70-byte parts (DrawModelPart) and sends the second packet.
void DrawPlacedObjectParts(DeferredRequest* self)
{
    PartDrawFrame f;
    s32 i;
    u8* base = (u8*)&g_vifPacketWriter;
    TextureRenderObject* s1 = (TextureRenderObject*)self->arg;
    AddDmaRefTag((PacketWriter*)base, s1->firstPacket, s1->firstPacketSize);
    FillMemory(&f, 0, 0x80);
    f.kind = 3;
    f.fn = (void*)DrawModelPart;
    f.copy = self->block;
    f.object = s1;
    f.record = s1->sub22C;
    i = 0;
    MultiplyMatrices(f.qC0, &g_unitSquareToClipMatrix, &((DrawRangeRecord*)s1->drawRange)->m70);
    f.q80[0] = f.qC0[0];
    f.q80[1] = f.qC0[1];
    f.q80[2] = f.qC0[2];
    f.q80[3] = f.qC0[3];
    BeginDmaTag((PacketWriter*)&g_vifPacketWriter);
    WriteVifBaseOffset((PacketWriter*)&g_vifPacketWriter, 0, 0);
    CopyWordsToWriter(&g_vifPacketWriter, 0xC, 4, (u32*)f.q80, 4);
    CloseDmaTag((PacketWriter*)&g_vifPacketWriter);
    if (s1->drawPartCount > 0) {
        s32 off = 0;
        do {
            i++;
            // address arithmetic over a variable index
            f.part = (u8*)s1->drawParts + off;
            DrawModelPart((PartDrawRequest*)&f);
            off += 0x70;
        } while (i < s1->drawPartCount);
    }
    AddDmaRefTag((PacketWriter*)&g_vifPacketWriter, s1->secondPacket, s1->secondPacketSize);
}

// A ListFrame (list_iter.h) as func_00153EC0 builds it, word by word.
struct ListFrameWords {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};


// Sets up the solver for count constraints: clears the record, allocates (from back memory) room
// for twice as many items of 0x60 bytes, the item lists linked at +0x4C, and the square matrices
// and vectors the pivoting uses.
void InitActiveSetSolver(ActiveSetSolver* self, s32 count)
{
	(void)FillMemory(self, 0, 0x50);
	s32 n = count << 1;
	self->slots = n;
	s32 size = 0x60 * n;
	self->items = AllocateBackMemory(size);
	(void)FillMemory(self->items, 0, size);
	SetListLinkOffset(&self->active, 0x4C);
	SetListLinkOffset(&self->atLow, 0x4C);
	SetListLinkOffset(&self->atHigh, 0x4C);
	SetListLinkOffset(&self->pending, 0x4C);
	s32 sq = (n * n) << 2;
	self->matrix = (f32*)AllocateBackMemory(sq);
	self->factor = (f32*)AllocateBackMemory(sq);
	self->rhs = (f32*)AllocateBackMemory(count << 3);
	self->solution = (f32*)AllocateBackMemory(count << 3);
}

// Empties the solver's lists, clears every item and puts all items back in the pending list.
void ResetActiveSetSolver(ActiveSetSolver* self)
{
    s32 i;
    self->activeCount = 0;
    ClearList(&self->active);
    ClearList(&self->atLow);
    ClearList(&self->atHigh);
    ClearList(&self->pending);
    for (i = 0; i < self->count; i++) {
        ActiveSetItem* e = (ActiveSetItem*)(self->items + i * 0x60);
        e->x = e->val = 0.0f;
        (void)FillMemory(&e->next, 0, 8);
        AppendToList(&self->pending, e);
    }
}

// Adds an item to the solver: fills its column in every existing item's row with the dot product of
// their axes and puts it in the pending list.
void AddActiveSetItem(ActiveSetSolver* self, ActiveSetItem* item)
{
    for (s32 i = 0; i < self->count; i++) {
        ActiveSetItem* e = (ActiveSetItem*)(self->items + i * 0x60);
        f32* row = e->row;
        if (row != 0) {
            Vu0::Vec d = Vu0::Dot(Vu0::Vec::Of(item->axis), Vu0::Vec::Of(e->axes[((BodyContact*)item->owner)->axesIndex]));
            Vu0::StoreX(((u32*)row)[self->count], d.q);
        }
    }
    AppendToList(&self->pending, item);
    self->count++;
}

typedef void (*EndRowsFn)(Collider* body, s32 a1, void* contact, s32 end, ActiveSetItem* item, f32* rows);
typedef void (*EndFillFn)(Collider* body, s32 a1, s32 size, s32 extra, f32* rows);
void ComputeColliderPointVelocity(Collider* body, Vec4* point, void* motion, Vec4* out);

// Fills in what the solver needs of a constraint item the first time it is used: for each body of
// its contact the rows of that body's response to a unit impulse (the bodies' slots 58 and 59),
// then the axes (relative point velocity of the bodies at each other constraint's contact) and
// its own row of dot products against every item's axis.
void BuildContactItemRows(ActiveSetSolver* self, s32 a1, ActiveSetItem* n, s32 a3, s32 a4, s32 a5, s32 a6)
{
    BodyContact* contact = (BodyContact*)n->owner;
    for (s32 i = 0; i < 2; i++) {
        Collider* body = contact->end[i].body;
        if (body != 0 && body->solverIndex >= 0) {
            s32 idx = body->solverIndex << 2;
            s32* size = (s32*)(idx + a5);
            f32* r = (f32*)AllocateZeroedBackMemory(*size << 5);
            n->rows[i] = r;
            ((EndRowsFn*)body->desc)[58](body, a1, contact, i, n, r);
            ((EndFillFn*)body->desc)[59](body, a1, *size, *(s32*)(idx + a6), r);
        }
    }
    Vec4* axes = (Vec4*)AllocateBackMemory(a3 << 4);
    n->axes = (u8(*)[16])axes;
    Vec4 out[2];
    for (s32 i = 0; i < a3; i++, axes++) {
        ContactEnd03* e = *(ContactEnd03**)(i * 4 + a4);
        for (s32 j = 0; j < 2; j++) {
            Collider* body = e[j].body;
            if (body == 0 || body->solverIndex < 0) {
                Vu0::Q(out[j]) = Vu0::Zero();
            } else if (body == contact->end[0].body) {
                Collider* part = e[j].part;
                // address arithmetic over a variable index
                ComputeColliderPointVelocity(part, &e[j].point, (f32*)((u8*)n->rows[0] + (part->index << 5)), &out[j]);
            } else if (body == contact->end[1].body) {
                Collider* part = e[j].part;
                // address arithmetic over a variable index
                ComputeColliderPointVelocity(part, &e[j].point, (f32*)((u8*)n->rows[1] + (part->index << 5)), &out[j]);
            } else {
                Vu0::Q(out[j]) = Vu0::Zero();
            }
        }
        Vu0::Q(*axes) = Vu0::Sub(Vu0::Vec::Of(out[0]), Vu0::Vec::Of(out[1])).q;
    }
    f32* row = (f32*)AllocateBackMemory(self->slots << 2);
    n->row = row;
    for (s32 i = 0; i < self->count; i++) {
        ActiveSetItem* it = (ActiveSetItem*)(self->items + i * 0x60);
        *(u32*)row++ = Vu0::ToBits(Vu0::Dot(Vu0::Vec::Of(it->axis), Vu0::Vec::Of(((Vec4*)n->axes)[((BodyContact*)it->owner)->axesIndex])).q);
    }
}

// Brings item x (if any) onto the active list, then up to 10 times solves the active items'
// system and steps along the solution by the longest step (at most 1) before an item hits a
// bound: an active item that does moves to the at-low or at-high list, one at a bound whose
// residual turns the wrong way becomes active. Stops on a full step or when x is dropped.
void PivotActiveSet(ActiveSetSolver* self, ActiveSetItem* x)
{
    s32 iter;
    ActiveSetItem* p;
    ActiveSetItem* q;
    f32* w;
    s32 i;
    if (x) {
        RemoveFromList(&self->pending, x);
        AppendToList(&self->active, x);
        self->activeCount++;
    }
    iter = 0;
    do {
        {
            f32* out = self->matrix;
            for (p = (ActiveSetItem*)self->active.head; p; p = p->next) {
                for (q = (ActiveSetItem*)self->active.head; q; q = q->next) {
                    *out = p->row[q - (ActiveSetItem*)self->items];
                    out++;
                }
            }
        }
        FactorSymmetricMatrix(self->activeCount, self->matrix, self->factor);
        {
            f32* out = self->rhs;
            for (p = (ActiveSetItem*)self->active.head; p; p = p->next) {
                *out = -p->val;
                out++;
            }
        }
        SolveFactoredSystem(self->activeCount, self->factor, self->rhs, self->solution);
        for (i = 0; i < self->count; i++) {
            f32 sum = 0.0f;
            w = self->solution;
            for (p = (ActiveSetItem*)self->active.head; p; p = p->next) {
                sum += *w * p->row[i];
                w++;
            }
            ((ActiveSetItem*)self->items)[i].rate = sum;
        }

        ActiveSetItem* best = 0;
        f32 bestT = 1.0f;
        s32 code = 0;
        w = self->solution;
        for (p = (ActiveSetItem*)self->active.head; p; p = p->next) {
            f32 f = *w;
            w++;
            if (p->kind != 2) {
                if (0.0001f < f) {
                    if (p->bounded != 0) {
                        f32 t = (p->limit - p->x) / f;
                        if (t < bestT) {
                            bestT = t;
                            best = p;
                            code = 4;
                        }
                    }
                } else if (f < -0.0001f) {
                    f32 t = -p->x / f;
                    if (t < bestT) {
                        bestT = t;
                        best = p;
                        code = 2;
                    }
                }
            }
        }
        for (ActiveSetItem* n = (ActiveSetItem*)self->atLow.head; n; n = n->next) {
            f32 f = n->rate;
            if (!(-0.0001f < f)) {
                f32 t = -n->val / f;
                if (t < bestT) {
                    bestT = t;
                    best = n;
                    code = 1;
                }
            }
        }
        for (ActiveSetItem* n = (ActiveSetItem*)self->atHigh.head; n; n = n->next) {
            f32 f = n->rate;
            if (!(f < 0.0001f)) {
                f32 t = -n->val / f;
                if (t < bestT) {
                    bestT = t;
                    best = n;
                    code = 3;
                }
            }
        }
        for (i = 0; i < self->count; i++) {
            ActiveSetItem* r = (ActiveSetItem*)self->items + i;
            r->val += bestT * r->rate;
        }
        {
            w = self->solution;
            for (p = (ActiveSetItem*)self->active.head; p; p = p->next) {
                p->x += bestT * *w;
                w++;
            }
        }
        switch (code) {
        case 0:
            return;
        case 2:
            self->activeCount--;
            RemoveFromList(&self->active, best);
            AppendToList(&self->atLow, best);
            if (best == x) return;
            break;
        case 1:
            self->activeCount++;
            RemoveFromList(&self->atLow, best);
            AppendToList(&self->active, best);
            break;
        case 4:
            self->activeCount--;
            RemoveFromList(&self->active, best);
            AppendToList(&self->atHigh, best);
            if (best == x) return;
            break;
        case 3:
            self->activeCount++;
            RemoveFromList(&self->atHigh, best);
            AppendToList(&self->active, best);
            break;
        }
        iter++;
    } while (iter < 10);
}

// Solves the constraint items for non-negative (or bounded) values: first activates all the
// equality items (kind 2) and solves, then repeatedly picks the pending item whose residual is
// most negative (below -0.01) and pivots it in, until none is left.
void RunActiveSetSolver(ActiveSetSolver* self, s32 a1, s32 a3, s32 a4, s32 a5, s32 a6)
{
    ListFrameWords fr;
    ListFrame frame;
    s32 e = (s32)&self->pending;
    fr.cursor = e;
    fr.list = e;
    s32 old = (s32)g_activeListFrames;
    s32 link = ((ObjectList*)e)->offset;
    g_activeListFrames = (ListFrame*)&fr;
    fr.prev = old;
    s32 h = *(s32*)e;
    fr.link = link;
    fr.cursor = h + link;
    ActiveSetItem* node = (ActiveSetItem*)h;
    while (node != 0) {
        if (node->kind == 2) {
            if (node->row == 0) {
                BuildContactItemRows(self, a1, node, a3, a4, a5, a6);
            }
            RemoveFromList(&self->pending, node);
            AppendToList(&self->active, node);
            self->activeCount++;
        }
        ActiveSetItem* nx = *(ActiveSetItem**)fr.cursor;
        s32 lk = fr.link;
        fr.cursor = (s32)nx + lk;
        node = nx;
    }
    PivotActiveSet(self, (ActiveSetItem*)0);
    g_activeListFrames = (ListFrame*)fr.prev;
    for (;;) {
        f32 best = -0.01f;
        ActiveSetItem* sel = 0;
        for (ActiveSetItem* p = (ActiveSetItem*)self->pending.head; p != 0; p = p->next) {
            if (p->val < best) {
                best = p->val;
                sel = p;
            }
        }
        if (!sel) break;
        if (sel->row == 0) {
            BuildContactItemRows(self, a1, sel, a3, a4, a5, a6);
        }
        PivotActiveSet(self, (ActiveSetItem*)sel);
    }
}

typedef void (*HandlerFn)(void* handler, s32 flags, ActiveSetItem* item, s32 end, f32 dt);

// Runs the solver, then adds friction: for the contact with the largest sliding speed along its
// surface (above a small threshold) it adds a bounded friction item (limit = the normal force
// times the friction) paired with the normal item, lets the handlers see it, and solves again;
// repeats until no contact slides.
void AddFrictionItemsAndSolve(ActiveSetSolver* self, s32 a1, s32 n, BodyContact** contacts, s32 a4, s32 a5, f32 dt)
{
    u128 zero = Vu0::Zero();
    Vec4 best;
    for (;;) {
        RunActiveSetSolver(self, a1, n, (s32)contacts, a4, a5);
        s32 bestIndex = -1;
        Vu0::Q(best) = zero;
        f32 top = 0.01f;
        BodyContact* bestContact = 0;
        for (s32 i = 0; i < n; i++) {
            ActiveSetItem* item = (ActiveSetItem*)(self->items + i * 0x60);
            if (item->twin != 0) {
                continue;
            }
            if (item->x < 0.0001f) {
                continue;
            }
            if (item->kind == 2) {
                continue;
            }
            BodyContact* c = contacts[i];
            if (c->friction < 0.0001f) {
                continue;
            }
            Vec4 acc;
            Vu0::Q(acc) = Vu0::Q(c->relativeVelocity);
            for (s32 k = 0; k < self->count; k++) {
                ActiveSetItem* other = (ActiveSetItem*)(self->items + k * 0x60);
                if (other->x != 0.0f) {
                    Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(((Vec4*)other->axes)[i]), Vu0::Scalar(other->x));
                }
            }
            u128 v = Vu0::Q(acc);
            u128 normal = Vu0::Q(c->normal);
            u128 tangent = Vu0::Sub(v, Vu0::MulX(normal, Vu0::Dot(v, normal)));
            u128 len2 = Vu0::Dot(tangent, tangent);
            Vu0::Q(acc) = tangent;
            f32 len = Vu0::ToFloat(len2);
            if (top < len) {
                Vu0::Q(best) = tangent;
                top = len;
                bestIndex = i;
                bestContact = c;
            }
        }
        if (bestContact == 0) {
            return;
        }
        ActiveSetItem* it = (ActiveSetItem*)(self->items + self->count * 0x60);
        ActiveSetItem* twin = (ActiveSetItem*)(self->items + bestIndex * 0x60);
        it->twin = twin;
        twin->twin = it;
        f32 mag = -Fpu::Sqrt(top);
        it->owner = bestContact;
        ContactEnd03* end = bestContact->end;
        it->val = mag;
        Vu0::Q(it->axis) = Vu0::MulX(Vu0::Q(best), Vu0::Scalar(1.0f / mag));
        it->kind = 1;
        it->bounded = 1;
        it->limit = it->twin->x * bestContact->friction;
        for (s32 j = 0; j < 2; j++) {
            Collider* h = FindHandlerForSlot(end[j].part, 0x108);
            if (h != 0) {
                HandlerFn fn = (HandlerFn)h->desc03()->m3E;
                if (fn != 0) {
                    fn(h, a1 | 0x10, it, j, dt);
                }
            }
        }
        AddActiveSetItem(self, it);
    }
}


// A part's share of the solved impulses: a linear and an angular one.
struct PartImpulse {
    Vec4 lin;              // 0x00
    Vec4 ang;              // 0x10
};

// acc += v, with v cut to length `limit` when it is longer (limitSq is limit squared).
static inline void AddLimited(Vec4* acc, Vec4* v, f32 limitSq, f32 limit)
{
    f32 lengthSq = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(*v), Vu0::Vec::Of(*v)));
    if (limitSq < lengthSq) {
        Vu0::Vec a = Vu0::Vec::Of(*acc);
        Vu0::Vec s = Vu0::Vec::Scalar(limit / Fpu::Sqrt(lengthSq));
        Vu0::Q(*acc) = Vu0::MulAddX(a, Vu0::Vec::Of(*v), s).q;
    } else {
        Vu0::Q(*acc) = Vu0::Add(Vu0::Vec::Of(*acc), Vu0::Vec::Of(*v)).q;
    }
}

// The solver's impulses handed out: each solved item adds its rows, weighted by its x, to the
// parts of the bodies at its contact's two ends (n groups of parts, counts[j] in group j); each
// part then takes its own impulse, relative to its parent's motion at its position and in the
// parent's frame when it has one, constrained and cut to maxLin and maxAng.
void ApplySolvedImpulsesToParts(ActiveSetSolver* self, s32 n, s32* counts, Collider*** lists, f32 maxLin, f32 maxAng)
{
    PartImpulse** bufs;
    f32 maxLinSq;
    f32 maxAngSq;
    s32 j;

    PushBackMemoryMark();
    bufs = (PartImpulse**)AllocateBackMemory(n * 4);
    for (j = 0; j < n; j++) {
        bufs[j] = (PartImpulse*)AllocateZeroedBackMemory(counts[j] << 5);
    }
    maxLinSq = maxLin * maxLin;
    maxAngSq = maxAng * maxAng;
    for (s32 i = 0; i < self->count; i++) {
        ActiveSetItem* it = (ActiveSetItem*)(self->items + i * 0x60);
        s32 k;
        if (it->x == 0.0f) {
            continue;
        }
        for (k = 0; k < 2; k++) {
            Collider* body = ((BodyContact*)it->owner)->end[k].body;
            s32 m;
            if (body == 0) {
                continue;
            }
            s32 g = body->solverIndex;
            if (g < 0) {
                continue;
            }
            Vec4* row = (Vec4*)it->rows[k];
            PartImpulse* buf = bufs[g];
            for (m = 0; m < counts[g]; m++) {
                u128 lin = Vu0::Q(buf[m].lin);
                Vu0::Q(buf[m].lin) = Vu0::MulAddX(lin, Vu0::Q(row[2 * m]), Vu0::ScalarAt(it->x));
                u128 ang = Vu0::Q(buf[m].ang);
                Vu0::Q(buf[m].ang) = Vu0::MulAddX(ang, Vu0::Q(row[2 * m + 1]), Vu0::ScalarAt(it->x));
            }
        }
    }
    for (j = 0; j < n; j++) {
        s32 count = counts[j];
        PartImpulse* buf = bufs[j];
        Collider** list = lists[j];
        for (s32 i = 0; i < count; i++) {
            Collider* body = list[i];
            PartImpulse* own = &buf[body->index];
            Collider* parent = (Collider*)body->parent;
            if (parent != 0) {
                PartImpulse* up = &buf[parent->index];
                Vec4 lin;
                Vec4 ang;
                Vec4 linLocal;
                Vec4 angLocal;
                ComputeColliderPointVelocity(parent, &body->v140, up, &lin);
                Vu0::Q(lin) = Vu0::Sub(Vu0::Vec::Of(own->lin), Vu0::Vec::Of(lin)).q;
                Vu0::Q(ang) = Vu0::Sub(Vu0::Vec::Of(own->ang), Vu0::Vec::Of(up->ang)).q;
                Vu0::Q(linLocal) = Vu0::RotateTransposed(parent->m110, Vu0::Vec::Of(lin)).q;
                Vu0::Q(angLocal) = Vu0::RotateTransposed(parent->m110, Vu0::Vec::Of(ang)).q;
                ConstrainColliderVector(body, &body->v440, &linLocal, &linLocal, 0);
                ConstrainColliderVector(body, &body->v460, &angLocal, &angLocal, 0);
                AddLimited(&body->v490, &linLocal, maxLinSq, maxLin);
                AddLimited(&body->spin4A0, &angLocal, maxAngSq, maxAng);
            } else {
                AddLimited(&body->v490, &own->lin, maxLinSq, maxLin);
                AddLimited(&body->spin4A0, &own->ang, maxAngSq, maxAng);
            }
        }
    }
    PopBackMemoryMark();
}

// Solves a count by count linear system (data is the matrix, values the right-hand side) with the
// active-set solver, for callers that are not contacts; the solution is written to out.
void SolveActiveSetSystem(s32 count, u8* data, f32* values, f32* out)
{
    ActiveSetSolver loc;
    s32 i;

    PushBackMemoryMark();
    InitActiveSetSolver(&loc, count);
    for (i = 0; i < count; i++) {
        ActiveSetItem* item = (ActiveSetItem*)(loc.items + i * 0x60);
        item->row = (f32*)AllocateBackMemory(count * 4);
        CopyMemory(item->row, data + i * count * 4, count * 4);
        item->val = values[i];
        AppendToList(&loc.pending, item);
    }
    loc.count = count;
    RunActiveSetSolver(&loc, 0, 0, 0, 0, 0);
    for (i = 0; i < count; i++)
        out[i] = *(f32*)(loc.items + i * 0x60 + 0x34);
    PopBackMemoryMark();
}

