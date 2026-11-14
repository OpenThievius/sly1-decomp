// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the fields of self are at 0x56C, 0x570, 0x58C and 0x590 (US 0x25C, 0x260, 0x27C, 0x280).
typedef void (*VFn_1F1C90)(void* self);
struct Obj_1F1C90_eu {
    VFn_1F1C90* vtbl;
    u8 pad0[0x56C - 4];
    s32 f56C;
    WarpPage* f570;
    u8 pad1[0x58C - 0x574];
    f32 f58C;
    f32 f590;
};

void HideScreenElements(void* self);
s32 GetCurrentWarpEntry(void);
s32 IsWarpEntryAvailable(WarpPage* self, s32 kind, s32* outA, s32* outB);
void SetWarpCursor(WarpPage* self, s32 a1, s32 a2);
void BeginWarpPageClose(void* self);
void SetScreenElementSlideInTime(void* self, f32 v);
void SetScreenElementSlideOutTime(void* self, f32 v);
void PauseStagedBankVoice(void);
void ResumeStagedBankVoice(void);
s32 SetPadSelectFlags(s32 bits);
void ClearPadSelectFlags(u32 mask);
void ResetPadStepRepeat(PadRecord* p);
void SetElementStackState(void* obj, s32 mode);

void SetWarpMenuOpen(Obj_1F1C90_eu* self, s32 a1)
{
    if ((a1 != 0) != (self->f56C == 0)) return;
    if (a1 != 0) {
        HideScreenElements(self);
        s32 r = GetCurrentWarpEntry();
        if (r == 10) {
            r = (IsWarpEntryAvailable(self->f570, 1, 0, 0) != 0);
        }
        SetWarpCursor(self->f570, r, 2);
        self->f590 = 1.0f;
        self->f58C = 1.0f;
        Animation* an = self->f570->openAnimation;
        if (an != 0) {
            SetScreenElementSlideInTime(self, an->length);
        }
        GameProgress* g = g_saveData;
        if (((g->levelIndex << 8) | g->entryIndex) == 0x308) {
            PauseStagedBankVoice();
        }
        self->vtbl[14](self);
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
        SetElementStackState((ElementStack*)g_elementStack, 7);
    } else {
        self->vtbl[15](self);
        if (self->f570->f560 == 0) {
            BeginWarpPageClose(self->f570);
            Animation* an = self->f570->closeAnimation;
            if (an != 0) {
                SetScreenElementSlideOutTime(self, an->length);
            }
            ClearPadSelectFlags(1);
            SetElementStackState((ElementStack*)g_elementStack, 3);
            GameProgress* g = g_saveData;
            if (((g->levelIndex << 8) | g->entryIndex) == 0x308) {
                ResumeStagedBankVoice();
            }
        }
    }
    self->f56C = a1;
}
