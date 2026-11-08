// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 768/772 (99.5%), checked 2026-11-08
// NEAR: wave 4 e3. 772 bytes, same size; four words differ: the restore of the history entry moved to the front
//       loads its two quadwords into v0, v1 (retail v1, v0) and so stores them with the registers swapped. The switch, the
//       frame, the jump table and the history search are retail's. ~12 compiles (struct copy, two quadword copies in either
//       order, Vu0::Q copies).
// Night-close2 (2026-11-08): the restore as two u128 copies, in either order or loaded before MoveMemory, gives the same swap (or callee-saved registers); func_001A2E68 has the same pattern.
// Still differs (2026-11-08, night-close6): tmp declared in the restore block (copy-initialised or assigned), with case 0's two vectors as locals of their own: the same swap.
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "font.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "background_job.h"
#include "vu0.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "vu0.h"

struct TargetMemo {
    void* key;
    f32 f4;
    f32 f8;
    u8 padC[4];
    Vec02 pos;
};
extern const Vec02 D_00248D30;
extern f32 g_gameClock[];
void ConvertPositionToWorld(void* obj, Vec02* out);
f32 ArctangentOfRatio(f32 y, f32 x);
void MoveMemory(void* dst, void* src, s32 size);
void FillMemory(void* dst, s32 value, s32 size);
#define History(p) ((TargetMemo*)((u8*)(p) + 0x2770))
void func_001790B8(Player* self)
{
    Vec02 pos = D_00248D30;
    TargetMemo tmp;
    u8* key = 0;
    f32 w = 0.0f;
    switch (self->f2220) {
    case 3: {
        u8* o = (u8*)self->f2204;
        if (*(s32*)(o + 0xB8) != 0) {
            return;
        }
        key = o;
        break;
    }
    case 6:
        switch (self->f239C) {
        case 4: {
            u8* o = (u8*)self->f23BC;
            if (*(s32*)(o + 0x50) != 0) {
                return;
            }
            key = o;
            w = *(f32*)((u8*)self + 0x23C4);
            break;
        }
        case 5: {
            u8* o = *(u8**)((u8*)self + 0x23B8);
            if (*(s32*)(o + 0x5C) != 0) {
                return;
            }
            key = o;
            break;
        }
        case 0: {
            u8* o = (u8*)self->f23A0;
            if (o != 0) {
                if (*(s32*)(o + 0x5C) != 0) {
                    return;
                }
                key = o;
                w = self->f23A4;
            } else {
                o = (u8*)self->f23A8;
                if (*(s32*)(o + 0x74) != 0) {
                    return;
                }
                key = o;
                ConvertPositionToWorld(o, (Vec02*)&tmp);
                Vu0::Q(tmp.pos) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)&tmp));
                w = ArctangentOfRatio(tmp.pos.y, tmp.pos.x) * *(f32*)((u8*)self->f23A8 + 0x5C);
            }
            break;
        }
        case 7:
            return;
        default:
            goto probe;
        }
        break;
    case 2:
    case 4:
    case 8:
    case 11:
        return;
    case 0:
    case 1:
    case 5:
    case 9:
    case 10:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    probe:
        if (self->f690 == 0) {
            return;
        }
        if (self->f6C0 == 0) {
            pos = self->v6A0;
        } else {
            if ((((Collider*)self->f6C0)->flags538 & (1ull << 52)) != 0) {
                return;
            }
            pos = self->v6A0;
        }
        break;
    case 7: {
        u8* o = (u8*)self->f2208;
        if (*(s32*)(o + 0x60) != 0) {
            return;
        }
        w = self->f2410;
        key = o;
        break;
    }
    default:
        break;
    }
        s32 i;
    for (i = 1; i < self->f2768; i++) {
        TargetMemo* e = &History(self)[i];
        s32 match = 0;
        if (key == e->key) {
            if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(pos), Vu0::Q(e->pos)))) < 50.0f) {
                if (__builtin_fabsf(w - e->f4) < 50.0f) {
                    match = 1;
                }
            }
        }
        if (match) {
            if (i != 1) {
                tmp = *e;
                MoveMemory(&History(self)[2], &History(self)[1], (i - 1) * 0x20);
                History(self)[1] = tmp;
            }
            break;
        }
    }
    if (i >= self->f2768) {
        if ((u32)self->f2768 < 0x20) {
            self->f2768++;
        }
        MoveMemory(&History(self)[1], &History(self)[0], self->f2768 * 0x20 - 0x20);
        FillMemory(&History(self)[0], 0, 0x20);
    }
    History(self)[0].key = key;
    History(self)[0].pos = pos;
    History(self)[0].f4 = w;
    History(self)[0].f8 = g_gameClock[1];
}
