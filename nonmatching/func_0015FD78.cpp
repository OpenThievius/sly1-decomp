// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 520/476, checked 2026-11-07
// NEAR: the loops and the VU0 part are right; the constants 1 and 2 of the mode test are kept in s6 and s7 over the whole outer loop (frame 144), where retail loads them into a2 and a3 inside it (frame 112).
#include "common.h"
#include "id_lookup_object.h"
#include "placed_object.h"
#include "world.h"
#include "animation.h"
#include "sound_record.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "list_iter.h"
#include "packet_writer.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "keyed_entry.h"
#include "identity_key.h"
#include "strip_mesh.h"
#include "vertex_batch.h"
#include "shapes.h"

// Stands in for the static objects of the file: the check names its compiler-made functions.
struct NmInit {
    NmInit();
};
NmInit::NmInit() {}
NmInit g_nmInit;


void UpdateGroupsNearCamera(void* self);
void RemoveFromList(List01* list, PlacedObject* node);
typedef void (*Fn_Table)();
typedef void (*AttachmentHandlerFn)(void* self);
typedef void (*AnimatorStepFn)(void* self, f32 f);

#include "camera.h"
struct VisitClass { u8 pad0[8]; s32 flags; u8 pad1[0x54]; void (*visit)(void* self, void* arg); };
struct VisitNode { VisitClass* cls; u8 pad0[0x18]; VisitNode* next; u8 pad1[0x14]; VisitNode* child; };
extern Camera* g_camera;
void VisitObjectTree(VisitNode* self, void* arg);
void AppendToList(void* list, void* node);
void RemoveFromList(void* list, void* node);

void UpdateGroupsNearCamera(World* self)
{
    for (PlacedObject* g = (PlacedObject*)self->list54.head; g != 0; g = (PlacedObject*)g->link48.next) {
        if (g->f54 != g) {
            continue;
        }
        PlacedObject* first = (PlacedObject*)g->list60.head;
        PlacedObject* m = first;
        s32 active;
        if (m != 0) {
            Camera* cam = g_camera;
            for (; m != 0; m = (PlacedObject*)m->link58.next) {
                s32 mode = (s32)(m->flags >> 40) & 3;
                if (mode == 1) {
                    break;
                }
                if (mode == 2) {
                    m = 0;
                    break;
                }
                if ((m->f88 & cam->f21C) == cam->f21C) {
                    f32 r = m->f80 + m->f2A8;
                    u128 diff = Vu0::Sub(Vu0::Q(m->v140), Vu0::Q(cam->f40));
                    f32 d = Vu0::ToFloat(Vu0::Dot(diff, diff));
                    if (!(r * r < d)) {
                        break;
                    }
                }
            }
        }
        active = m != 0;
        m = first;
        if (m == 0) {
            continue;
        }
        u64 bit = (u64)active << 37;
        u64 mask = ~((u64)1 << 37);
        while (m != 0) {
            if (active != ((m->flags >> 37) & 1)) {
                if (active != 0) {
                    VisitObjectTree((VisitNode*)m, 0);
                    AppendToList(&self->list60, m);
                    if (m->desc->flags & 2) {
                        AppendToList(&self->list6C, m);
                    }
                } else {
                    VisitObjectTree((VisitNode*)m, (void*)1);
                    RemoveFromList(&self->list60, m);
                    if (m->desc->flags & 2) {
                        RemoveFromList(&self->list6C, m);
                    }
                }
                m->flags = (m->flags & mask) | bit;
            }
            m = (PlacedObject*)m->link58.next;
        }
    }
}
