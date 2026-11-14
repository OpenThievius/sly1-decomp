// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL lays Obj_11A338 out 0x310 bytes later from 0x208 on, no longer sets the current
// entry here, takes the name from entry offset 8, and fetches the message with func_eu_001DDAB0(0xAA).
void SetupScreenElementText(void* self);
void SetScreenElementScale(void* self, f32 v);
void SetScreenElementHoldTime(void* self, f32 v);
void SetBestTimeState(T217D_1380* self, s32 n);
struct Ent_11A338_eu { u32 pad0; f32 f4; void* w8; };
struct Obj_11A338_eu;
struct VTab_11A338_eu { u8 pad[0x20]; void (*f20)(Obj_11A338_eu*, const char*); u8 pad2[0x38 - 0x24]; void (*f38)(Obj_11A338_eu*); };
struct Obj_11A338_eu { VTab_11A338_eu* vt; u8 pad0[0x518 - 4]; s32 color; u8 pad1[4]; void** slot; u8 pad2[0x57C - 0x524]; s32 f26c; s32 f270; };
const char* GetTextTableEntry(s32 id);

void InitCommentaryPromptElement(Obj_11A338_eu* self)
{
    Ent_11A338_eu* e;

    SetupScreenElementText(self);
    e = (Ent_11A338_eu*)FindLevelEntry((g_saveData->levelIndex << 8) | g_saveData->entryIndex);
    if (e) {
        if (e->f4 != 0.0f) {
            g_currentWorld->timerDuration = e->f4;
        }
        if (g_currentWorld->creditsText == 0 || !GetStringLength((const char*)g_currentWorld->creditsText)) {
            g_currentWorld->creditsText = e->w8;
        }
    }
    if (IsFontLoaded(2)) {
        self->slot = (void**)&g_commentaryFrameStyle;
        *self->slot = GetFontById(2);
    }
    SetScreenElementScale(self, 0.6f);
    *(s32*)((u8*)self + 0x518) = (s32)0xDF7F7F7Fu;
    if (CheckEntryThreeBitRequirement(g_currentWorld, (g_saveData->levelIndex << 8) | g_saveData->entryIndex)) {
        SetBestTimeState((T217D_1380*)self, 1);
    } else {
        SetBestTimeState((T217D_1380*)self, 0);
    }
    if (g_currentEntry->bits & 8) {
        if (((CommentaryRecord*)g_currentWorld->commentaryRecord)->differs()) {
            self->vt->f20(self, GetTextTableEntry(0xAA));
            SetScreenElementHoldTime(self, 5.0f);
            self->vt->f38(self);
            self->f26c = 1;
        } else {
            self->f26c = 0;
        }
    } else {
        self->f26c = 0;
    }
    self->f270 = 0;
}
