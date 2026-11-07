// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 256/284, checked 2026-11-07
// NEAR: the same except that the compiler turns the test of bit 31 of a child (next & 0x80000000) into a sign test (bgez), where retail keeps and with a register holding 0x80000000 (lui s3,0x8000). Written as next < 0, next & (1 << 31), (u32) & 0x80000000 and with != 0, all the same. Its callers must pass the float radius in f12.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "fpu.h"
#include "world.h"
#include "warp_page.h"
#include "screen_element.h"
#include "globals.h"
#include "shapes.h"
#include "object_link.h"
#include "owner_message.h"
#include "game_clock.h"
#include "pad_record.h"
#include "memory_card.h"
#include "timeline.h"
#include "value_list_object.h"
#include "c62.h"
#include "attached_set.h"
#include "packet_writer.h"
#include "screen_fade.h"
#include "transform_object.h"
#include "oscillator.h"
#include "camera.h"
#include "game_progress.h"
#include "item_keeper.h"
#include "attachment.h"
#include "animation.h"
#include "ramp_profile.h"
#include "asm_func.h"
#include "vu0.h"

// Stands in for the static objects of the file: the check names its compiler-made functions.
struct NmInit {
    NmInit();
};
NmInit::NmInit() {}
NmInit g_nmInit;



typedef u64 Bits128 __attribute__((mode(TI)));
s32 ExpandMaskThroughTable(ValueListObject* self, s32 bits);

struct PlaneNode {
    Vec02 normal;           // 0x00
    f32 dist;               // 0x10
    s32 front;              // 0x14: a node, or a leaf mask with bit 31 set
    s32 back;               // 0x18
};

s32 QueryValueTreeMask(ValueListObject* self, s32 node, Bits128 point, s32* out, f32 radius)
{
    if (node < 0) {
        *out = ExpandMaskThroughTable(self, node);
    } else {
        for (;;) {
            PlaneNode* n = (PlaneNode*)node;
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(point), Vu0::Q(n->normal))) - n->dist;
            s32 next;
            if (d < -radius) {
                next = n->front;
            } else {
                next = n->back;
                if (!(radius < d)) {
                    if ((u32)next & 0x80000000) {
                        *out |= ExpandMaskThroughTable(self, next);
                    } else {
                        QueryValueTreeMask(self, next, point, out, radius);
                    }
                    next = n->front;
                }
            }
            if ((u32)next & 0x80000000) {
                *out |= ExpandMaskThroughTable(self, next);
                break;
            }
            node = next;
        }
    }
}

