// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 2124/2132, checked 2026-11-08
// NEAR (2026-11-08, night-large3): SolveColliderGroupContacts (func_001BCD00), 89.5% of the
// words: the flag scans, the solver set-up, the depth, rest and bounce passes and the write-back
// follow retail (the second scan as a guarded do-while, the item kind as a switch). Left: loop
// counters' registers (retail keeps the scans' counter in s0 and the parts loop's in s1; ours a2
// and s1, a separate counter for the scans changes nothing) and the order of the first
// AllocateBackMemory's size against the flag saves.
#include "common.h"
#include "sound_record.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
#include "buffered_stream.h"
#include "object_event.h"
#include "key_record.h"
#include "key_id.h"
#include "base_object.h"
#include "fpu.h"
#include "asm_func.h"
#include "point_object.h"
#include "id_linked_object.h"
#include "game_progress.h"
#include "shapes.h"
#include "property_descriptor.h"
#include "vu0.h"
#include "active_set_solver.h"

Collider* FindHandlerForSlot(Collider* node, s32 offset);
struct SolveContact_1BCD00 {
    ContactEnd03 end[2];            // 0x00
    Vec02 normal;                   // 0x80
    f32 depth;                      // 0x90
    u8 pad94[0x98 - 0x94];
    f32 bounce;                     // 0x98
    s32 kind;                       // 0x9C
    f32 limit;                      // 0xA0
    u8 padA4[0xB0 - 0xA4];
    Vec02 relVel;                   // 0xB0
    f32 push;                       // 0xC0
    f32 impulse;                    // 0xC4
    f32 speed;                      // 0xC8
    s32 index;                      // 0xCC
};
struct SolveHandler_1BCD00;
struct SolveHandlerDesc_1BCD00 { u8 pad00[0x108]; void (*m108)(SolveHandler_1BCD00* self, s32 kind, ActiveSetItem* it, s32 end, f32 dt); };
struct SolveHandler_1BCD00 { SolveHandlerDesc_1BCD00* desc; };
typedef void (*SolvePartFn_1BCD00)(Collider* self, void* a, void* b);

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void* FillMemory(void* p, s32 zero, s32 size);
void InitActiveSetSolver(ActiveSetSolver* loc, s32 count);
void AddActiveSetItem(ActiveSetSolver* loc, ActiveSetItem* item);
void RunActiveSetSolver(ActiveSetSolver* loc, s32 a1, s32 n, SolveContact_1BCD00** contacts, s32* counts, void** lists);
void func_00154370(f32 a, f32 b, ActiveSetSolver* loc, s32 n, s32* counts, void** lists);
void ResetActiveSetSolver(ActiveSetSolver* self);
void func_00185F48(World* world, s32 n, SolveContact_1BCD00** list);
void NotifyContactEnds(World* world, s32 n, SolveContact_1BCD00** list);
void func_00154088(f32 dt, ActiveSetSolver* loc, s32 flags, s32 n, SolveContact_1BCD00** contacts, s32* counts, void** lists);
f32 RandomFloatInRange(f32 a, f32 b);

void SolveColliderGroupContacts(f32 dt, World* world, s32 nParts, Collider** parts, s32 n, SolveContact_1BCD00** contacts, s32 flags)
{
    ActiveSetSolver loc;
    s32 i;
    if (flags & 1) {
        if (n == 0) {
            return;
        }
    } else {
        if (flags & 4) {
            s32 i;
            for (i = 0; i < n; i++) {
                SolveContact_1BCD00* c = contacts[i];
                if (c->kind == 11) {
                    if (0.1f < __builtin_fabsf(c->depth)) {
                        break;
                    }
                } else if (c->depth < -2.0f) {
                    break;
                }
            }
            if (!(i < n)) {
                flags &= ~4;
            }
        }
        if (flags & 2) {
            i = 0;
            if (0 < n) {
                do {
                    SolveContact_1BCD00* c = contacts[i];
                    if (c->kind == 11) {
                        if (5.0f < __builtin_fabsf(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal))))) {
                            break;
                        }
                    } else if (Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal))) < -5.0f) {
                        break;
                    }
                    i++;
                } while (i < n);
            }
            if (!(i < n)) {
                flags &= ~2;
            }
        }
        if (flags == 0) {
            return;
        }
    }
    PushBackMemoryMark();
    void** lists = (void**)AllocateBackMemory(nParts * 4);
    s32 rest = flags & 1;
    s32* counts = (s32*)AllocateBackMemory(nParts * 4);
    s32 depthPass = flags & 4;
    FillMemory(counts, 0, nParts * 4);
    for (s32 k = 0; k < nParts; k++) {
        Collider* part = parts[k];
        part->f4BC = k;
        lists[k] = AllocateBackMemory(0xC0);
        ((SolvePartFn_1BCD00*)part->desc)[57](part, &counts[k], lists[k]);
    }
    for (i = 0; i < n; i++) {
        contacts[i]->index = i;
    }
    InitActiveSetSolver(&loc, n);
    for (i = 0; i < n; i++) {
        ActiveSetItem* it = (ActiveSetItem*)(loc.items + i * 0x60);
        SolveContact_1BCD00* c = contacts[i];
        it->owner = c;
        *(Vec02*)it->axis = c->normal;
        switch (c->kind) {
        case 11:
            it->kind = 2;
            break;
        case 12:
            it->kind = 0;
            it->bounded = 1;
            it->limit = c->limit;
            break;
        default:
            it->kind = 0;
            break;
        }
        AddActiveSetItem(&loc, it);
    }
    if (depthPass) {
        for (i = 0; i < n; i++) {
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + i * 0x60);
            SolveContact_1BCD00* c = contacts[i];
            if (it->kind == 2) {
                it->val = c->depth;
            } else {
                it->val = c->depth + 1.0f;
            }
            for (s32 e = 0; e < 2; e++) {
                SolveHandler_1BCD00* h = (SolveHandler_1BCD00*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 0xC, it, e, dt);
                }
            }
        }
        RunActiveSetSolver(&loc, 4, n, contacts, counts, lists);
        func_00154370(100.0f, 1.0f, &loc, nParts, counts, lists);
        for (i = 0; i < nParts; i++) {
            ((SolvePartFn_1BCD00*)parts[i]->desc)[51](parts[i], 0, 0);
        }
        if (flags == 4) {
            goto done;
        }
        ResetActiveSetSolver(&loc);
    }
    if (rest) {
        func_00185F48(world, n, contacts);
        NotifyContactEnds(world, n, contacts);
        for (i = 0; i < n; i++) {
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + i * 0x60);
            SolveContact_1BCD00* c = contacts[i];
            *(u32*)&it->val = Vu0::ToBits(Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal)));
            for (s32 e = 0; e < 2; e++) {
                SolveHandler_1BCD00* h = (SolveHandler_1BCD00*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 9, it, e, dt);
                }
            }
        }
    } else {
        for (i = rest; i < n; i++) {
            SolveContact_1BCD00* c = contacts[i];
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + i * 0x60);
            *(u32*)&c->speed = Vu0::ToBits(Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal)));
            f32 r = RandomFloatInRange(0.9f, 1.1f);
            it->val = c->speed * (c->bounce * r + 1.0f);
            for (s32 e = 0; e < 2; e++) {
                SolveHandler_1BCD00* h = (SolveHandler_1BCD00*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 10, it, e, dt);
                }
            }
        }
    }
    func_00154088(dt, &loc, flags & ~4, n, contacts, counts, lists);
    if (rest) {
        func_00154370(5000.0f, 50.0f, &loc, nParts, counts, lists);
    } else {
        func_00154370(5000.0f, 50.0f, &loc, nParts, counts, lists);
    }
done:
    for (i = 0; i < nParts; i++) {
        Collider* part = parts[i];
        part->f4BC = -1;
        if (rest) {
            ((SolvePartFn_1BCD00*)part->desc)[53](part, 0, 0);
        } else if (flags & 2) {
            ((SolvePartFn_1BCD00*)part->desc)[52](part, 0, 0);
        }
        for (s32 j = 0; j < counts[i]; j++) {
            ((Collider**)lists[i])[j]->index = -1;
        }
    }
    if (rest) {
        for (i = 0; i < n; i++) {
            contacts[i]->push = ((ActiveSetItem*)(loc.items + i * 0x60))->x;
        }
    } else if (flags & 2) {
        for (i = 0; i < n; i++) {
            contacts[i]->impulse = ((ActiveSetItem*)(loc.items + i * 0x60))->x;
        }
    }
    PopBackMemoryMark();
}
