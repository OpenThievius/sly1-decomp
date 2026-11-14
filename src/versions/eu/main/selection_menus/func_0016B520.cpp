// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL: Obj_16B520.field25C is at 0x56C (US 0x25C).
struct Obj_16B520_eu { u8 pad0[0x56C]; s32 field56C; };

void RestoreSelectionCaptionCamera(Obj_16B520_eu* self)
{
    if (self->field56C != 0) {
        void* p = FindFirstObjectByIdMode4(g_currentWorld, 0x4FD, 0);
        if (p != 0) {
            PushObjectCameraController(p);
        }
    }
}

