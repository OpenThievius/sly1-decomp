// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 531/568 (93.5%), checked 2026-11-08
// NIGHT-LOW2 (2026-11-08): case 9 before case 8 in the source gives retail's block order (9, then 8's switch). Still differs: the entry in s3 and the result in s2 (retail s2 and s3), and the shared tail of kinds 4, 6 and 7 (bc1fl; move s2, zero here, bc1t to the return with v0 = s3 and b with s3 = 0 in retail).
// NEAR: wave 4 e3. Same size, every instruction but the registers and one tail matches: ours keeps the entry in s3 and the result in s2 (retail
//       s2 and s3), and the shared tail of kinds 4, 6 and 7 is `bc1fl; move s2, zero` where retail's is `bc1t C644 (v0 = s3); b C640 (s3 = 0)`.
//       ~10 compiles (the result declared first, initialised, the entry as the parameter, break / if-else / assigned-comparison forms).
#include "common.h"
#include "switched_collider.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "globals.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "point_object.h"
#include "collider.h"
#include "placed_object.h"
#include "path_curve_object.h"
#include "on_off_object.h"
#include "asm_func.h"
#include "vu0.h"

extern f32 D_00263E38;
extern f32 D_00263E3C;
void GetNodeAnchorAndHeading(EntryQueue* self, BaseObject* n, Vec02* out, f32* outf);

extern f32 D_0026185C;
void* FindFirstObjectById(void* host, s32 kind, s32 id, s32 mode);
void StopAnimationPlayer(void* p);
void SetPlayerState(Player* p, s32 state, s32 arg);

s32 CheckQueueEntryDone(EntryQueue* self, QueueEntry* e)
{
    s32 done = 1;
    Player* pl = (Player*)self->f3C;
    void* obj = FindFirstObjectById(pl->world, 0x104, e->id, self->f4C);
    switch (e->kind) {
    case 4:
        done = 1;
        if (e->valueF < D_0026185C - self->f44) {
            break;
        }
        done = 0;
        break;
    case 5:
        done = pl->f2220 != 2;
        break;
    case 6: {
        if (obj == 0) {
            done = 1;
            break;
        }
        Vec02 pos;
        GetNodeAnchorAndHeading(self, (BaseObject*)obj, &pos, 0);
        u128 gap = Vu0::Sub(Vu0::Q(pl->v140), Vu0::Q(pos));
        done = 1;
        if (Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(gap, gap))) < D_00263E38) {
            break;
        }
        done = 0;
        break;
    }
    case 7:
        done = 1;
        if (__builtin_fabsf(pl->f2410 - self->f64) < D_00263E3C) {
            break;
        }
        done = 0;
        break;
    case 9: {
        void* p = self->f50;
        done = 0;
        if (p == 0 || ((f32*)p)[6] == 0.0f) {
            done = 1;
        }
        if (done && p != 0) {
            StopAnimationPlayer(p);
            self->f50 = 0;
        }
        break;
    }
    case 8:
        switch (e->value) {
        case 2:
            done = pl->f223C == -1;
            break;
        case 4:
            done = pl->f2220 != 2;
            break;
        case 8:
            done = pl->f2220 != 10;
            break;
        default:
            done = 1;
            break;
        }
        break;
    case 12:
        if (pl->f2220 == 2 && (u32)(pl->f2228 - 12) < 2) {
            done = 0;
            break;
        }
        done = 1;
        if (pl->f2220 == 6 && (u32)pl->f239C < 2) {
            SetPlayerState(pl, 0, -1);
        }
        break;
    default:
        done = 1;
        break;
    }
    return done;
}

void StartNextQueueEntry(EntryQueue* self);
