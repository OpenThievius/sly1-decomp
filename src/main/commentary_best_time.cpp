// SPDX-License-Identifier: AGPL-3.0-or-later
// The bonus commentary and the Master Thief Sprint's best time, as the level's screen element
// shows them. Its .rodata opens with the names the commentary table (D_00248748, read only by
// func_001DFE80 here) points to; its .data is the style its static initialiser builds and the
// buffer the best time is written into.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "world.h"
#include "screen_element.h"
#include "font.h"
#include "globals.h"
#include "game_progress.h"
#include "level_entry.h"
#include "pad_record.h"
#include "memory_card.h"
#include "layout_137228.h"
#include "functions/game_progress.h"
#include "functions/memory_card.h"
#include "functions/pad_input.h"
#include "functions/screen_element.h"
#include "functions/sound_system.h"
#include "functions/state_notifier.h"
#include "functions/text_format.h"
#include "functions/warp_menu.h"
#include "functions/world.h"

extern const char g_levelCredits0100[24] = "Nate Fox\nHokyo Lim";
extern const char g_levelCredits0102[32] = "Rob McDaniel\nSuzanne Kaufmann";
extern const char g_levelCredits0103[80] = "Rob McDaniel\nDev Madan\nAugie Pagan\nKarin Yamagiwa\nHokyo Lim\nSuzanne Kaufmann";
extern const char g_levelCredits0104[40] = "Bruce Oberg\nRob McDaniel\nHokyo Lim";
extern const char g_levelCredits0105[32] = "Rob McDaniel\nChris Heidorn";
extern const char g_levelCredits0106[32] = "Brian Fleming\nChris Bentzel";
extern const char g_levelCredits0107[40] = "Brian Fleming\nDJ Stiner\nRob McDaniel";
extern const char g_levelCredits0200[40] = "Brian Fleming\nNate Fox\nTravis Kotzesbue";
extern const char g_levelCredits0202[32] = "Bruce Oberg\nNate Fox\nMatt Olsen";
extern const char g_levelCredits0204[40] = "Chris Zimmerman\nMatt Olsen\nBruce Oberg";
extern const char g_levelCredits0205[24] = "Nate Fox\nChris Bentzel";
extern const char g_levelCredits0207[32] = "Rob McDaniel\nBrian Fleming";
extern const char g_levelCredits0300[40] = "Nate Fox\nMatt Olsen\nAndrew Woods";
extern const char g_levelCredits0302[40] = "Nate Fox\nBrian Fleming\nReid Johnson";
extern const char g_levelCredits0303[48] = "Suzanne Kaufmann\nKelle DeForrest\nRob McDaniel";
extern const char g_levelCredits0304[32] = "Chris Bentzel\nKelle DeForrest";
extern const char g_levelCredits0305[64] = "Rob McDaniel\nSuzanne Kaufmann\nAndrew Woods\nKarin Yamagiwa";
extern const char g_levelCredits0306[40] = "Nate Fox\nMatthew Morgaine\nChris Heidorn";
extern const char g_levelCredits0307[40] = "Bruce Oberg\nGary Burd\nChris Bentzel";
extern const char g_levelCredits0400[24] = "Nate Fox\nMatt Olsen";
extern const char g_levelCredits0402[32] = "Rob McDaniel\nDarrell Plank";
extern const char g_levelCredits0403[24] = "Nate Fox\nAndrew Woods";
extern const char g_levelCredits0404[40] = "Chris Bentzel\nIan Stout\nKelle DeForrest";
extern const char g_levelCredits0405[32] = "Chris Bentzel\nRob McDaniel";
extern const char g_levelCredits0406[40] = "Rob McDaniel\nAugie Pagan\nAndrew Woods";
extern const char g_levelCredits0407[40] = "Matthew Morgaine\nChris Zimmerman";
extern const char g_levelCredits0502[32] = "Nate Fox\nChris Zimmerman";
extern const char g_levelCredits0503[32] = "Nate Fox\nMatthew Morgaine";
extern const char g_levelCredits0504[48] = "Matthew Morgaine\nMatt Olsen\nChris Bentzel";
extern const char g_levelCredits0505[32] = "Suzanne Kaufmann\nChris Bentzel";
extern const char g_levelCredits0506[40] = "Rob McDaniel\nDev Madan\nTravis Kotzesbue";

extern "C" void* FillMemory(void* p, s32 value, s32 size);

// The text style the best time draws with: the static initialiser (func_001E0848) zeroes it,
// then sets its kind, two sizes given as integers, 0.3 twice and its colour.
struct BestTimeTextStyle {
    u8 pad0[4];
    u8 kind;
    u8 pad5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    s32 color;
    BestTimeTextStyle(s32 a, s32 b)
    {
        FillMemory(this, 0, 0x1C);
        kind = 0x2D;
        f8 = a;
        fC = b;
        f14 = f10 = 0.3f;
        color = (s32)0xFF7D4B00;
    }
};
BestTimeTextStyle g_commentaryFrameStyle(2, 1);

struct BestTimeTextBuffer { char c[0x40]; };
BestTimeTextBuffer g_bestTimeText = {};

void* FindLevelEntry(s32 key)
{
    const LevelEntry* p = g_levelEntries;
    const LevelEntry* end = g_levelEntries + 33;
    do {
        if (key != p->levelId) {
            p++;
        } else {
            return (void*)p;
        }
    } while (p < end);
    return 0;
}

// The record a level entry keeps at +8 (World::commentaryRecord points to it; func_001E00B0 streams it):
// its two words at +4 and +0x1C differ while there is commentary to play.
struct CommentaryRecord { u8 pad0[4]; s32 a; u8 pad1[0x1C - 8]; s32 b; s32 differs() { if (this == 0) return 0; return a != b; } };


void* FindLevelEntry(s32 k);
s32 IsFontLoaded(s32 k);
Font* GetFontById(s32 k);
void SetBestTimeState(T217D_1380* self, s32 n);

void InitCommentaryPromptElement(T217D_1380* self)
{
    const LevelEntry* e;

    SetupScreenElementText(self);
    e = (const LevelEntry*)FindLevelEntry((g_saveData->levelIndex << 8) | g_saveData->entryIndex);
    if (e) {
        if (e->timerDuration != 0.0f) {
            g_currentWorld->timerDuration = e->timerDuration;
        }
        if (!(((CommentaryRecord*)g_currentWorld->commentaryRecord)->differs())) {
            g_currentWorld->commentaryRecord = (CommentaryRecord*)e->record;
        }
        if (g_currentWorld->creditsText == 0 || !GetStringLength((const char*)g_currentWorld->creditsText)) {
            g_currentWorld->creditsText = (void*)e->credits;
        }
    }
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&g_commentaryFrameStyle;
        *self->frame = GetFontById(2);
    }
    SetScreenElementScale(self, 0.6f);
    *(s32*)((u8*)self + 0x208) = (s32)0xDF7F7F7Fu;
    if (CheckEntryThreeBitRequirement(g_currentWorld, (g_saveData->levelIndex << 8) | g_saveData->entryIndex)) {
        SetBestTimeState(self, 1);
    } else {
        SetBestTimeState(self, 0);
    }
    if (g_currentEntry->bits & 8) {
        if (((CommentaryRecord*)g_currentWorld->commentaryRecord)->differs()) {
            self->vt->m08(self, "Press &2L&. for Bonus Commentary");
            SetScreenElementHoldTime(self, 5.0f);
            self->vt->m14(self);
            self->pressed = 1;
        } else {
            self->pressed = 0;
        }
    } else {
        self->pressed = 0;
    }
    self->f270 = 0;
}

void SetBestTimeState(T217D_1380* self, s32 n);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

extern f32 g_gameTime;
extern s32 D_002701C4;
extern s32 g_timerRateExponent;

struct KeyRecord;
void SetBestTimeState(T217D_1380* self, s32 n);
extern "C" f32 Power(f32 x, f32 y);

void UpdateBestTimeState(T217D_1380* self)
{
    UpdateScreenElementSlide(self);
    switch (self->state) {
    case 0:
    case 1:
    {
        if (self->pressed != 0) {
        if (g_padRecord.flags & 4) {
            ClearPadPressedBits(&g_padRecord, 4);
            StartLockedStreamVoice((KeyRecord*)g_currentWorld->commentaryRecord);
            if (g_currentWorld->creditsText != 0) {
                SetScreenElementHoldTime(self, 15.0f);
                self->vt->m08(self, (const char*)g_currentWorld->creditsText);
            } else {
                self->vt->m15(self);
            }
            self->pressed = 0;
        } else if (g_gameTime >= 5.0f) {
            self->vt->m15(self);
            self->pressed = 0;
        }
        }
    break;
    }
    case 2:
    {
        T217D_510* o = &g_timerElement;
        s32 r;
        if (o->state == 0) {
            SetBestTimeState(self, 3);
            return;
        }
        SetTimerRate(o, -Power(2.0f, (f32)g_timerRateExponent));
        r = AreMenusAndFadeClear();
        if (r) o->vt->m14(o); else o->vt->m15(o);
        if (g_currentEntry->flags & 8) {
            s32 b = 0;
            if (r && D_002701C4 == 0 && g_currentEntry->f08 < g_timerElement.time) b = 1;
            if (b) g_timerCaption.vt->m14(&g_timerCaption); else g_timerCaption.vt->m15(&g_timerCaption);
        }
    }
    break;
    }
}

extern s32 g_timerRateExponent;

struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
extern "C" f32 Power(f32 x, f32 y);
void SetPauseMenuLayerPage(T217D_6D0* y, s32 a, s32 b);

void SetBestTimeState(T217D_1380* self, s32 n)
{
    if (self->state == n) {
        return;
    }
    switch (self->state) {
    case 1:
        if (self->pressed != 0) {
            self->vt->m15(self);
            self->pressed = 0;
        }
        break;
    case 2:
        StopTimer(&g_timerElement);
        g_timerElement.vt->m15(&g_timerElement);
        self->vt->m15(self);
        break;
    }
    switch (n) {
    case 2: {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        StartSoundEffect(0x6D, 0, 0, 0, 3000.0f, 300.0f, one, zero, zero, 0, 0);
        SetSpareCount(0);
        PopActiveSequenceElement(g_currentWorld);
        StartTimer(&g_timerElement, g_currentWorld->timerDuration + 0.99f);
        SetTimerRate(&g_timerElement, -Power(2.0f, (f32)g_timerRateExponent));
        SetTimerLimit(&g_timerElement, zero, 0);
        StartTimerCounting(&g_timerElement);
        G27C230* cam = g_currentEntry;
        if (cam->flags & 8) {
            f32 t = cam->f08;
            if (t < one) {
                FormatToString((char*)&g_bestTimeText, "Best time: &10.%d", (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 minutes = s / 60;
                s32 seconds = s % 60;
                FormatToString((char*)&g_bestTimeText, "Best time: &1%d:%02d", minutes, seconds);
            }
            SetScreenElementHoldTime(self, zero);
            self->vt->m08(self, g_bestTimeText.c);
        } else {
            SetScreenElementHoldTime(self, 5.0f);
            self->vt->m08(self, "Beginning Master Thief Sprint!");
        }
        self->vt->m14(self);
        break;
    }
    case 3: {
        T217D_510* o = &g_timerElement;
        s32 id;
        f32 t = o->time;
        if (0.0f < t) {
            G27C230* cam = g_currentEntry;
            if (cam->flags & 8) {
                if (cam->f08 < t) {
                    cam->f08 = t;
                    id = 0x1D;
                    StartMemoryCardSave(&g_memoryCard);
                } else {
                    id = 0x1E;
                }
            } else {
                id = 0x1B;
                cam->flags |= 8;
                cam->f08 = o->time;
                g_currentLevelRecord->f440 = g_currentLevelRecord->f440 + 1;
                if (ComputeCompletionMask() & 8) {
                    ApplyCompletionFlags(8);
                    StartMemoryCardSave(&g_memoryCard);
                }
            }
        } else {
            id = 0x1C;
            if (g_currentEntry->flags & 8) {
                id = 0x1E;
            }
        }
        SetPauseMenuLayerPage(&g_pauseMenuElement, 0, id);
        break;
    }
    }
    self->state = n;
    self->stateSince = *self->clock;
    if (n == 2) {
        CompleteSoundNotifiers(g_currentWorld);
    }
    self->active = (self->state != 0);
}

struct TextLayout;
struct TextLayout {
    u8 b[32];
    void Pos(f32 x, f32 y) { ((Layout_137228*)this)->Pos(x, y); }
    void Size(f32 x, f32 y) { ((Layout_137228*)this)->Size(x, y); }
    void Color(s32* c) { ((Layout_137228*)this)->Color(c); }
    void FlagA(s32 f) { ((Layout_137228*)this)->SetF14(f); }
    void FlagB(s32 f) { ((Layout_137228*)this)->SetF18(f); }
};
struct FrameFont {
    static void Draw(Font** h, TextLayout* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};

struct Font;
extern f32 D_0027240C;
void PushFontScale(Font* font, f32 a, f32 b);
struct TextReader;
struct Layout_137228;
void* InitTextReader(TextReader* self, char* text, Font* font);
struct Layout_137228;
struct PacketWriter;
struct TextReader;
struct Vec4U;
void DrawAlignedText(TextReader* self, Layout_137228* p, Vec4U* clip, PacketWriter* s);
void PopFontScale(Font* font);

void DrawFramedText(T217D_1380* self)
{
    T217D_Word tmp;
    TextLayout out;
    T217D_Word slot;
    u8 loc[0xB0];

    if (self->text[0] != 0) {
        PushFontScale(self->font, self->scale, self->scale);
        tmp = self->colorWord;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
        f32 p = self->w;
        f32 q = self->h;
        s32 held = tmp.v;
        out.Pos(self->shownX, self->shownY - D_0027240C * 66.40000915527344f);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(0);
        out.FlagB(0);

        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            FrameFont::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        InitTextReader((TextReader*)loc, &self->text[0], self->font);
        DrawAlignedText((TextReader*)loc, (Layout_137228*)&out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

LINKER_REMNANT(func_001E0820);

void FinishBestTimeRun(void* self)
{
    SetBestTimeState((T217D_1380*)self, 3);
}

// The style above is built by the static initialiser GCC writes here (func_001E0848), and its
// _GLOBAL_$I$ (func_001E08D8) follows the 12 bytes the linker left of a function this file wrote
// out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001E08C8);
