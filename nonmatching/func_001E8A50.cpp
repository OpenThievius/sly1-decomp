// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 0/0, checked 2026-11-08
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
#include "vu0.h"
#include "asm_func.h"
#include "vu0.h"
// NEAR (2026-11-08, worker vu0w4-e1): the switch, its three tables of cases, the vector sequence and
// the calls are retail's, in retail's order (cases 1, 16, 11, 10 and 14). Differing: the
// registers of the loop counter and the chosen state (retail: counter s0, state s2, self s1), the
// delay slots around the first call and the length test (retail: bc1t with li 8 in the slot and li 5
// after, here bc1tl), and the store in case 16 that retail shares for the modes 0x2D9 to 0x2DB
// through v0 (a shared tail; written with a `goto` it moved self to s2).
extern float g_gameTime[];
extern u8 g_flagTable[];
void* FindObjectHandle(s32 a, s32 b);
typedef void* (*TargetObjectFn)(void* self);
void DecrementGaugeCount(void* p);
void StartMemoryCardSave(void* p);
void EnterAgentState(TempoAgent* self, s32 a, s32 b);
s32 FindNearestAgentKey(void* self, void* p);
void SetStateWalkerTarget(void* walker, s32 key);
void MarkLevelDone(s32 n);

s32 TestFlagTableBit(u8* table, s32 v);
void SetFlagTableBit(u8* table, s32 v);
void RaiseScatterLevelForObject(void* controller, s32 v);
extern u8 g_scatterController[];

void func_001E8A50(KeyedConeAgent* self, s32 a, s32 b)
{
    u32 i;
    s32 key;
    s32 slot;

    switch (self->f724) {
    case 1:
        if (self->fC54 != 0) {
            SetStateWalkerTarget(self->fC54, self->fC58);
            void* near = ((TargetObjectFn*)self->desc)[102](self);
            key = 0;
            if (near != 0) {
                key = FindNearestAgentKey(self, (u8*)near + 0x140);
            }
            i = 0;
            do {
                PlacedObject* root = self->fC64[i];
                s32 pick;
                switch (self->fC58) {
                case 0x2D7:
                case 0x2D8:
                case 0x2DA:
                    pick = 0x2DE;
                    break;
                case 0x2D9:
                case 0x2DB:
                case 0x2DC:
                case 0x2DD:
                    pick = 0x2DF;
                    if ((s32)root == key) {
                        pick = 0x2DE;
                    }
                    break;
                }
                void* h = FindObjectHandle((s32)root, -1);
                if (h != 0) {
                    SetStateWalkerTarget(h, pick);
                }
                i++;
            } while (i < 6);
        }
        if (self->fC58 == 0x2DA) {
            self->fC5C = 5;
        } else {
            u128 d = Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(self->v190));
            s32 v = 5;
            if (Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d))) < 300.0f) {
                v = 8;
            }
            self->fC5C = v;
        }
        self->fC7C = 0;
        break;
    case 16:
        switch (self->fC58) {
        case 0x2D8:
            self->fC58 = 0x2D9;
            slot = 0;
            break;
        case 0x2D9:
            self->fC58 = 0x2DA;
            slot = 1;
            break;
        case 0x2DA:
            self->fC58 = 0x2DA;
            slot = 2;
            break;
        case 0x2DB:
            self->fC58 = 0x2DC;
            slot = 3;
            break;
        }
        if (TestFlagTableBit(g_flagTable, (s32)self->fC80[slot]) == 0) {
            RaiseScatterLevelForObject(g_scatterController, 0);
        }
        SetFlagTableBit(g_flagTable, (s32)self->fC80[slot]);
        self->fC90 = 3 - slot;
        DecrementGaugeCount(&g_gaugeBarElement);
        break;
    case 11:
        if (self->fC54 != 0) {
            SetStateWalkerTarget(self->fC54, 0x2DD);
        }
        for (i = 0; i < 6; i++) {
            void* h = FindObjectHandle((s32)self->fC64[i], -1);
            if (h != 0) {
                SetStateWalkerTarget(h, 0x2DE);
            }
        }
        self->fC90 = 0;
        DecrementGaugeCount(&g_gaugeBarElement);
        MarkLevelDone(1);
        StartMemoryCardSave(&g_memoryCard);
        break;
    case 10:
    case 14:
        self->fC5C = 0;
        break;
    }
    EnterAgentState((TempoAgent*)self, a, b);
}

