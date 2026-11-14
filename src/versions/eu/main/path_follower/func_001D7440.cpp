// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// StartPathFollower, PAL's definition: starts the placed object, its links, heading, state walker,
// engine sounds and partner as US does (config/names/main/path_follower.tsv), at PAL's addresses.
struct Blk_eu_1D7440 {
    u8 pad0[0x574];
    void* p574;
    u8 pad578[0x58C - 0x578];
    s32 f58C;
};
struct __attribute__((packed)) BlkP_eu_1D7440 { u8 pad[0x58C]; s32 v; };

void StartPathFollower(PathFollower* self)
{
    BaseObject* buf[16];
    s32 id0;
    s32 id1;
    s32 id2;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x14, D_002752A0);
    self->targetHeading = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    if (self->walkerGraph != 0) {
        StateWalker* v = CreateStateWalker((StateGraph*)self->walkerGraph, self, -1, 0);
        self->fB48 = v;
        SetStateWalkerTarget(v, self->kind == 1 ? 0x484 : 0x384);
    }
    switch (g_currentWorld->soundBank) {
    case 3:
        id0 = self->enabled ? 0x1D2 : 0x1AD;
        id1 = 0x1BB;
        id2 = 0x1AF;
        goto spawn;
    case 5:
        id0 = self->enabled ? 0x2A6 : 0x280;
        id1 = 0x27F;
        id2 = 0x27D;
        goto spawn;
    case 6:
        id0 = self->enabled ? 0x2DE : 0x2DC;
        id1 = 0x2DB;
        id2 = 0x2DD;
    spawn:
        StartSoundEffect(id0, (PlayingSound**)self->engineSoundB, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id1, (PlayingSound**)self->engineSoundA, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id2, (PlayingSound**)self->slideSound, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        {
            f32 r = RandomFloatInRange(-0.1f, 0.1f);
            self->slidePitchOffset = self->engineBPitchOffset = self->engineAPitchOffset = self->fB98 = r;
        }
        break;
    default:
        break;
    }
    {
        void* c = FindFirstObjectById(g_currentWorld, 0x104, 7, self);
        if (c != 0) {
            self->f594 = 200.0f;
            self->partner = c;
            self->f598 = c;
        }
    }
    if (self->kind == 1) {
        s32 n = GatherObjectsByMode((self->world), 0x105, 0x426, 0, 0x10, buf);
        for (s32 i = 0; i < n; i++) {
            buf[i]->desc->m17(buf[i], self);
        }
        ((BlkP_eu_1D7440*)&D_00272430)->v = 0;
        ((BlkP_eu_1D7440*)&D_002726B0)->v = 0;
        ((Blk_eu_1D7440*)&D_00272430)->p574 = &((Blk_eu_1D7440*)&D_00272430)->f58C;
        ((Blk_eu_1D7440*)&D_002726B0)->p574 = &((Blk_eu_1D7440*)&D_002726B0)->f58C;
    }
    for (s32 k = 0; k < 4; k++) {
        Slot19* s = &self->f6B0[k];
        s->placedPos = s->obj->pos;
    }
    ResetPathFollower(self);
}
