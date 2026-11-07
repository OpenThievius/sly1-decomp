// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 683/736 (92.8%), checked 2026-11-07
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "vu0.h"
extern float D_00274E04;
void TransformPointBetweenFrames(void* frame, void* player, void* in, void* out);
// NEAR (2026-11-08, wave 3 retry): RotateUntied is not the lever here: retail's rotation result
// takes the vector's register (vf2, Rotate's tie) and the row at +0x10 is vf1, as the Rotate
// form gives; with RotateUntied the result takes the first row's register and the rest is the
// same. What differs is the schedule: retail compares the first dot product with -2.0 (c.lt.s
// f4,f1) before it loads the matrix rows, here the compare comes after the rotation.
struct TargetMover {
    struct Vt {
        u8 pad0[8];
        void (*place)(TargetMover* self, f32 angle, void* out, s32 flag);   // 0x08
        u8 pad0C[0x2C - 0x0C];
        void (*track)(TargetMover* self, f32 angle, void* pos, s32 zero, void* dir, void* up, f32* angleOut, f32* limitOut);   // 0x2C
    };
    const Vt* vt;           // 0x00
    u8 pad04[4];
    s32 wraps;              // 0x08
    s32 count;              // 0x0C
    u8 pad10[4];
    const f32* low;         // 0x14: the angles the mover's pieces start at
};
struct TargetFrameRecord {
    u8 pad0[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    TargetMover* mover;     // 0x34
    u8 pad38[0x40 - 0x38];
    s32 active;             // 0x40
};
struct ContactPlayerView {
    u8 pad0[0x23B8];
    void* anchor;           // 0x23B8
    TargetFrameRecord* record;  // 0x23BC
    f32 angle;              // 0x23C0
    f32 limit;              // 0x23C4
};

void ConvertPositionToWorld(void* obj, void* out);
void TransformDirectionBetweenFrames(void* frame, s32 a, void* in, void* out);
void AddPlayerObjectContacts(void* self, s32 code, void* a, void* b, void* c, void* d);

void func_001D0F20(Player* self)
{
    Vec02 pos;
    Vec02 local;
    Vec02 dir0;
    Vec02 world;
    Vec02 dir;
    Vec02 k;
    ContactPlayerView* p = (ContactPlayerView*)self;
    s32 code;
    switch (self->f239C) {
    case 5:
        ConvertPositionToWorld(p->anchor, &pos);
        AddPlayerObjectContacts(self, 0x23, p->anchor, &pos, 0, (void*)self->f6D4);
        break;
    case 4: {
        TargetFrameRecord* rec = p->record;
        void* frame = rec->frame;
        TargetMover* m = rec->mover;
        TransformPointBetweenFrames(0, frame, (void*)self->f6D4, &pos);
        if (m->vt->track != 0) {
            m->vt->track(m, p->angle, &pos, 0, &local, &dir0, &p->angle, &p->limit);
        }
        TransformPointBetweenFrames(frame, 0, &local, &world);
        TransformDirectionBetweenFrames(frame, 0, &dir0, &dir);
        code = 0x22;
        if (p->record->active == 0 && m->wraps == 0) {
            f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v150), Vu0::Q(dir)));
            f32 nlimit = -2.0f;
            f32 side = -Vu0::ToFloat(Vu0::Dot(Vu0::Rotate(self->rot, Vu0::Q(self->v640)), Vu0::Q(dir)));
            if (along < nlimit || side < 2.0f) {
                f32 lim = m->low[0] + D_00274E04;
                if (p->limit < lim) {
                    if (m->vt->place != 0) {
                        m->vt->place(m, lim, &local, 0);
                    }
                    TransformPointBetweenFrames(frame, 0, &local, &world);
                    code = 0x2A;
                    goto call;
                }
            }
            if (2.0f < along || -2.0f < side) {
                f32 lim = m->low[m->count - 1] - D_00274E04;
                if (lim < p->limit) {
                    if (m->vt->place != 0) {
                        m->vt->place(m, lim, &local, 0);
                    }
                    TransformPointBetweenFrames(frame, 0, &local, &world);
                    Vu0::Q(k) = Vu0::FromFloat(-1.0f);
                    Vu0::Q(dir) = Vu0::MulX(Vu0::Q(dir), Vu0::Q(k));
                    code = 0x2A;
                    goto call;
                }
            }
        }
    call:
        AddPlayerObjectContacts(self, code, p->record, &world, &dir, (void*)self->f6D4);
        break;
    }
    }
}
