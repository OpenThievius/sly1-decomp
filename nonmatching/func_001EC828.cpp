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
// NEAR (2026-11-08, worker vu0w4-e1): the structure, the frame (240 bytes), the registers of self
// (s2) and the message kind (s3, reused for the pointer to the timeline's record) are retail's, and
// so are the vector sequences. Differing: the order of two float loads in the time expression
// (retail loads fC88 before fC64), `move a0,s3` of the timeline's record after the add, the order of
// the two stores of the beat length (0x6F0 first in retail; the scheduler puts 0x690 first here), and the loop
// that finds the entry (retail holds the count in a2 and a copy in a1). The jump table is the
// C's own (retail's is jtbl_0024E740 with the same entries).
extern float g_gameTime[];
extern s32 D_00275DB8;
extern s32 D_00275DBC;
void GetStateWalkerCurrentKey(void* sub, s32* out);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, Vec02* e, Vec02* f, f32 t);
void RemoveTempoAgentEntry(TempoAgent* self, AnimationPlayer* key);
struct FramePoint_001EBD10 {
    u8 pad0[0x18];
    void* object;           // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 point;            // 0x40
};

struct TempoNoticeRec {
    void* object;           // 0x00
    u8 pad04[4];
    s32 id;                 // 0x08
};

struct TempoLineSub {
    u8 pad00[0x78];
    f32 f78;                // 0x78
};

struct TempoLine {
    u8 pad00[0x48];
    u8* rec;                // 0x48
    u8 pad4C[0x60 - 0x4C];
    TempoLineSub sub;       // 0x60
    u8 padDC[0xF0 - 0xDC];
    Vec02 vF0;              // 0xF0
};

void ChooseObjectPoolItem(void* timeline);
void GetPlacementRecordTransform(void* sub, Vec02* a, Mat02* b, s32 c);
void func_001A8C90(void* timeline, s32 a);
void RemoveTempoAgentEntry(TempoAgent* self, AnimationPlayer* key);
void HandleAgentNotification(TempoAgent* self, s32 kind, void* rec);
void SetCachedVoiceParam(s32 a, s32 b);
s32 GetCachedVoiceParam(s32 a);

void func_001EC828(TempoAgent* self, s32 kind, TempoNoticeRec* rec)
{
    Vec02 a;
    Mat02 b;
    Mat02 rot;
    Vec02 p;
    s32 key;
    s32 voice;

    switch (kind) {
    case 0x13:
        if (rec->object == self->f7E0 && rec->id == 0x1A5) {
            TempoLine* line = ((TempoLine**)self->fC24)[self->fC40];
            ChooseObjectPoolItem(line);
            TempoLineSub* sub = &line->sub;
            f32 t = self->fC64 + self->fC44 - g_gameTime[0] + ((f32*)self->fC3C)[0x684 / 4] * (self->fC88 * 0.5f);
            u8* r = line->rec;
            FramePoint_001EBD10* fp = (FramePoint_001EBD10*)((BeatPressCollider*)self->fC3C)->f618[self->fC40];
            GetPlacementRecordTransform(sub, &a, &b, 0);
            ComputeObjectFrameAtTime(fp->object, 0, &p, &rot, 0, 0, t);
            Vu0::Q(line->vF0) = Vu0::Add(Vu0::Q(p), Vu0::Rotate(rot, Vu0::Q(fp->point)));
            f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(line->vF0)))) / t;
            *(f32*)(r + 0x690) = d;
            *(f32*)(r + 0x6F0) = d;
            sub->f78 = t * 1.25f;
            func_001A8C90(line, 1);
            return;
        }
        break;
    case 6: {
        s32 i = 0;
        s32 n = self->fC68;
        if (n > 0) {
            TempoPlayerEntry* p = self->fC6C;
            while ((void*)p->player != (void*)rec) {
                i++;
                if (i >= n) {
                    goto done;
                }
                p++;
            }
            if (i < n) {
                RemoveTempoAgentEntry(self, (AnimationPlayer*)rec);
            }
        }
        break;
    }
    case 0x14:
        if ((void*)rec == self->fC54) {
            GetStateWalkerCurrentKey(rec, &key);
            switch (key) {
            case 0x4EC: voice = 0; break;
            case 0x4ED: voice = 1; break;
            case 0x4EE: voice = 2; break;
            case 0x4EF: voice = 3; break;
            case 0x4F0: voice = 4; break;
            case 0x4F1:
            case 0x4F2: voice = 5; break;
            case 0x4F3: voice = 6; break;
            case 0x4F4:
            case 0x4F5: voice = 7; break;
            case 0x4F6: voice = 8; break;
            case 0x4F7: voice = 9; break;
            case 0x4F8: voice = 10; break;
            }
            if (voice != GetCachedVoiceParam(0)) {
                D_00275DB8 = 1;
                D_00275DBC = voice;
                SetCachedVoiceParam(0, voice);
            }
        }
        break;
    }
done:
    HandleAgentNotification(self, kind, rec);
}

