// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: Obj_16B7A8 fields f25C, f260 and f264 are at 0x56C, 0x570 and 0x574 (US 0x25C, 0x260, 0x264).
typedef void (*VFn_16B7A8)(void* self);
struct Obj_16B7A8_eu { VFn_16B7A8* vtbl; u8 pad0[0x56C - 4]; s32 f56C; void* f570; s32 f574; };

void SetSelectionCaptionOpen(Obj_16B7A8_eu* self, s32 v)
{
    s32 flag = (v != 0);
    if (flag != (self->f56C == 0)) {
        return;
    }
    if (v != 0) {
        SetCurrentObjectChoice((CurrentPlacedObject*)self->f570, ((CurrentPlacedObject*)self->f570)->choice, 0);
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
    } else {
        if (self->f574 != 0) {
            StopStreamVoice();
            self->f574 = 0;
        }
        ClearPadSelectFlags(1);
        self->vtbl[15](self);
        g_copiedTextCaption.vt->m15(&g_copiedTextCaption);
    }
    self->f56C = v;
}

