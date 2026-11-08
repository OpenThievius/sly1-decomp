// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1060/1072, checked 2026-11-08
// BYTES 0/0, checked 2026-11-07
// NEAR (2026-11-07, worker night-large1): the trigger zone's start: the walk of its children
// (quads for state 0, rotations for state 1) and the axes of each state, retail's code to the end
// of the walk and through state 0. The switch's compare tree is retail's with an empty case 2
// (cases 0, 1 alone test 0 first). In state 1 retail forms the last rotation's address and copies
// it (move a0, a1) before the row's address, and stores the 100.0 weight twice (once more after
// the first MulAddX); here CSE drops the second store whatever the order of the three products
// (four orders tried), and the registers of the rest follow.
#include "common.h"
#include "flag_table.h"
#include "asm_func.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "object_message.h"
#include "world.h"
#include "object_event.h"
#include "vu0.h"

void AddTriggerZoneQuad(TriggerZone* self, void* a1, Quad28* q);

struct ScopedListFrame {
    void* list;
    void* cursor;
    s32 next_off;
    ScopedListFrame* prev;
    ScopedListFrame(List01* l)
    {
        list = l;
        cursor = l;
        ScopedListFrame* p = (ScopedListFrame*)g_activeListFrames;
        next_off = l->offset;
        g_activeListFrames = (ListFrame*)this;
        prev = p;
    }
    ~ScopedListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

void StartPlacedObject(TriggerZone* self);
void StartZoneRecord(Zone28* self);
void SetTriggerZoneMode(TriggerZone* self, s32 v);
s32 IsObjectOfKind(void* node, s32 kind);
void TransformPointBetweenFrames(void* to, void* from, void* in, void* out);
void TransformRotationBetweenFrames(void* to, void* from, void* in, void* out);
void TransformDirectionBetweenFrames(void* to, void* from, void* in, void* out);
void AddTriggerZoneRotation(TriggerZone* self, void* a1, Mat02* m);
void ConstrainColliderVector(void* self, Vec02* limit, Vec02* in, Vec02* out, s32 a);
void CopyMemory(void* dst, void* src, s32 n);
extern const Vec02 g_unitXVector;
extern const Vec02 g_unitYVector;
extern const Vec02 g_unitZVector;

void func_0013F290(TriggerZone* self)
{
    ScopedListFrame frame(&self->children);
    Vec02 v;
    StartPlacedObject(self);
    StartZoneRecord(&self->zone);
    SetTriggerZoneMode(self, 0);
    s32 state = self->state;
    void* head = *(void**)frame.cursor;
    frame.cursor = (void*)((s32)head + frame.next_off);
    PlacedObject* node = (PlacedObject*)head;
    if (node != 0) {
        do {
            if (state == 0 && IsObjectOfKind(node, 0x7E)) {
                TransformPointBetweenFrames(self, self->parent, (u8*)node + 0x40, &v);
                AddTriggerZoneQuad(self, node, (Quad28*)&v);
            } else if (state == 1 && IsObjectOfKind(node, 0x73) && !IsObjectOfKind(node, 0x75)) {
                Mat02 m;
                TransformRotationBetweenFrames(self, self->parent, (u8*)node + 0x50, &m);
                AddTriggerZoneRotation(self, node, &m);
                node->desc->m03(node);
            }
            if (IsObjectOfKind(node, 0x76)) {
                self->id880 = (s32)node;
            }
            void* next = *(void**)frame.cursor;
            frame.cursor = (void*)((s32)next + frame.next_off);
            node = (PlacedObject*)next;
        } while (node != 0);
    }
    switch (state) {
    case 0: {
        s32 i;
        for (i = 0; i < self->f7B4; i++) {
            Vu0::Q(v) = Vu0::Sub(Vu0::Q(self->quads[i]), Vu0::Q(self->pos));
            ConstrainColliderVector(self, &self->v440, &v, &v, 0);
            Vu0::Q(self->quads[i]) = Vu0::Add(Vu0::Q(self->pos), Vu0::Q(v));
        }
        u128 d = Vu0::Sub(Vu0::Q(self->quads[self->f7B4 - 1]), Vu0::Q(self->quads[0]));
        Vu0::Q(self->v860) = d;
        Vu0::Q(self->v860) = Vu0::DivX(d, Vu0::Length(d));
        Vu0::Q(self->v870) = Vu0::MulX(Vu0::Q(self->v860), Vu0::Scalar(-1.0f));
        break;
    }
    case 1: {
        Mat02 rows;
        Vec02 a;
        Vec02 b;
        Vec02 dir;
        s32 k = self->count7E0 - 1;
        TransformDirectionBetweenFrames(self->parent, self, &self->v460, &dir);
        Vec02* side;
        Vec02* last;
        const Vec02* up;
        if (0.9f < dir.x) {
            rows.r[0] = ((Mat02*)self->entries)->r[2];
            side = &((Mat02*)self->entries)->r[1];
            up = &g_unitYVector;
            last = &((Mat02*)((u8*)self + k * 0x30 + 0x7F0))->r[1];
            rows.r[1] = ((Mat02*)((u8*)self + k * 0x30 + 0x7F0))->r[2];
        } else if (0.9f < dir.y) {
            rows.r[0] = ((Mat02*)self->entries)->r[0];
            side = &((Mat02*)self->entries)->r[2];
            up = &g_unitZVector;
            last = &((Mat02*)((u8*)self + k * 0x30 + 0x7F0))->r[2];
            rows.r[1] = ((Mat02*)((u8*)self + k * 0x30 + 0x7F0))->r[0];
        } else {
            rows.r[0] = ((Mat02*)self->entries)->r[1];
            side = &((Mat02*)self->entries)->r[0];
            up = &g_unitXVector;
            last = &((Mat02*)((u8*)self + k * 0x30 + 0x7F0))->r[0];
            rows.r[1] = ((Mat02*)((u8*)self + k * 0x30 + 0x7F0))->r[1];
        }
        if (self->parent != 0) {
            rows.r[2] = self->pos;
        } else {
            rows.r[2] = self->v140;
        }
        CopyMemory(&self->v860, &rows, 0x20);
        u128 s = Vu0::Scalar(100.0f);
        Vu0::Q(self->v850) = Vu0::MulX(Vu0::Q(*up), s);
        Vu0::Q(a) = Vu0::MulAddX(Vu0::Q(rows.r[2]), Vu0::Q(*side), s);
        Vu0::Q(b) = Vu0::MulAddX(Vu0::Q(rows.r[2]), Vu0::Q(*last), Vu0::Scalar(100.0f));
        Vu0::Q(v) = Vu0::Sub(Vu0::Q(b), Vu0::Q(a));
        if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v870), Vu0::Q(v)))) {
            Vu0::Q(self->v870) = Vu0::MulX(Vu0::Q(self->v870), Vu0::Scalar(-1.0f));
        } else {
            Vu0::Q(self->v860) = Vu0::MulX(Vu0::Q(self->v860), Vu0::Scalar(-1.0f));
        }
        break;
    }
    case 2:
        break;
    }
}
