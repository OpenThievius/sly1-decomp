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
#include "v24a2.h"
#include "globals.h"
#include "game_progress.h"
#include "level_entry.h"

extern const char D_0024DCB0[24] = "Nate Fox\nHokyo Lim";
extern const char D_0024DCC8[32] = "Rob McDaniel\nSuzanne Kaufmann";
extern const char D_0024DCE8[80] = "Rob McDaniel\nDev Madan\nAugie Pagan\nKarin Yamagiwa\nHokyo Lim\nSuzanne Kaufmann";
extern const char D_0024DD38[40] = "Bruce Oberg\nRob McDaniel\nHokyo Lim";
extern const char D_0024DD60[32] = "Rob McDaniel\nChris Heidorn";
extern const char D_0024DD80[32] = "Brian Fleming\nChris Bentzel";
extern const char D_0024DDA0[40] = "Brian Fleming\nDJ Stiner\nRob McDaniel";
extern const char D_0024DDC8[40] = "Brian Fleming\nNate Fox\nTravis Kotzesbue";
extern const char D_0024DDF0[32] = "Bruce Oberg\nNate Fox\nMatt Olsen";
extern const char D_0024DE10[40] = "Chris Zimmerman\nMatt Olsen\nBruce Oberg";
extern const char D_0024DE38[24] = "Nate Fox\nChris Bentzel";
extern const char D_0024DE50[32] = "Rob McDaniel\nBrian Fleming";
extern const char D_0024DE70[40] = "Nate Fox\nMatt Olsen\nAndrew Woods";
extern const char D_0024DE98[40] = "Nate Fox\nBrian Fleming\nReid Johnson";
extern const char D_0024DEC0[48] = "Suzanne Kaufmann\nKelle DeForrest\nRob McDaniel";
extern const char D_0024DEF0[32] = "Chris Bentzel\nKelle DeForrest";
extern const char D_0024DF10[64] = "Rob McDaniel\nSuzanne Kaufmann\nAndrew Woods\nKarin Yamagiwa";
extern const char D_0024DF50[40] = "Nate Fox\nMatthew Morgaine\nChris Heidorn";
extern const char D_0024DF78[40] = "Bruce Oberg\nGary Burd\nChris Bentzel";
extern const char D_0024DFA0[24] = "Nate Fox\nMatt Olsen";
extern const char D_0024DFB8[32] = "Rob McDaniel\nDarrell Plank";
extern const char D_0024DFD8[24] = "Nate Fox\nAndrew Woods";
extern const char D_0024DFF0[40] = "Chris Bentzel\nIan Stout\nKelle DeForrest";
extern const char D_0024E018[32] = "Chris Bentzel\nRob McDaniel";
extern const char D_0024E038[40] = "Rob McDaniel\nAugie Pagan\nAndrew Woods";
extern const char D_0024E060[40] = "Matthew Morgaine\nChris Zimmerman";
extern const char D_0024E088[32] = "Nate Fox\nChris Zimmerman";
extern const char D_0024E0A8[32] = "Nate Fox\nMatthew Morgaine";
extern const char D_0024E0C8[48] = "Matthew Morgaine\nMatt Olsen\nChris Bentzel";
extern const char D_0024E0F8[32] = "Suzanne Kaufmann\nChris Bentzel";
extern const char D_0024E118[40] = "Rob McDaniel\nDev Madan\nTravis Kotzesbue";

void func_001F5C0C(void* p, s32 zero, s32 size);

// The text style the best time draws with: the static initialiser (func_001E0848) zeroes it,
// then sets its kind, two sizes given as integers, 0.3 twice and its colour.
struct Style_1E0848 {
    u8 pad0[4];
    u8 kind;
    u8 pad5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    s32 f18;
    Style_1E0848(s32 a, s32 b)
    {
        func_001F5C0C(this, 0, 0x1C);
        kind = 0x2D;
        f8 = a;
        fC = b;
        f14 = f10 = 0.3f;
        f18 = (s32)0xFF7D4B00;
    }
};
Style_1E0848 D_002758E0(2, 1);

struct Buf_1E02C8 { char c[0x40]; };
Buf_1E02C8 D_00275900 = {};

void* func_001DFE80(s32 key)
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

struct Ent_11A338 { u32 pad0; f32 f4; u8 pad1[0x1C - 8]; s32 w1c; u8 pad2[0x28 - 0x20]; void* w28; };
struct Cur_11A338 { u8 pad0[4]; s32 a; u8 pad1[0x1C - 8]; s32 b; s32 differs() { if (this == 0) return 0; return a != b; } };


void* func_001DFE80(s32 k);
s32 func_001E2100(void* p);
s32 func_0015C188(s32 k);
V24A2* func_0015C1C0(s32 k);
s32 func_001DD7A0(World* g, s32 k);
void func_001E02C8(T217D_1380* self, s32 n);

void func_001DFEB8(T217D_1380* self)
{
    Ent_11A338* e;

    SetupScreenElementText(self);
    e = (Ent_11A338*)FindLevelEntry((g_saveData->f19D8 << 8) | g_saveData->f19DC);
    if (e) {
        if (e->f4 != 0.0f) {
            g_currentWorld->f230C = e->f4;
        }
        if (!(((Cur_11A338*)g_currentWorld->f2310)->differs())) {
            g_currentWorld->f2310 = (Cur_11A338*)((u8*)e + 8);
        }
        if (g_currentWorld->f2314 == 0 || !GetStringLength(g_currentWorld->f2314)) {
            g_currentWorld->f2314 = e->w28;
        }
    }
    if (IsFontLoaded(2)) {
        self->frame = (V24A2**)&D_002758E0;
        *self->frame = GetFontById(2);
    }
    SetScreenElementScale(self, 0.6f);
    *(s32*)((u8*)self + 0x208) = (s32)0xDF7F7F7Fu;
    if (CheckEntryThreeBitRequirement(g_currentWorld, (g_saveData->f19D8 << 8) | g_saveData->f19DC)) {
        SetBestTimeState(self, 1);
    } else {
        SetBestTimeState(self, 0);
    }
    if (g_currentEntry->bits & 8) {
        if (((Cur_11A338*)g_currentWorld->f2310)->differs()) {
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

void func_001E02C8(void* self, s32 n);

void func_001F5C0C(void* p, s32 zero, s32 size);

struct Glob_1E00B0 { u8 pad[0x230C]; f32 f230C; s32 f2310; void* f2314; };
struct Pool_1E00B0 { u8 pad[0xAA]; u16 fAA; };
extern Pool_1E00B0 D_00262C70;
extern f32 D_0026185C;
extern s32 D_002701C4;
extern s32 D_002623DC;

void func_0016EC20(Pool_1E00B0* q, s32 n);
void func_001BE5F8(s32 q);
void func_001E02C8(T217D_1380* q, s32 n);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(T217D_510* q, f32 v);
s32 func_001E9970(void);

void func_001E00B0(T217D_1380* self)
{
    UpdateScreenElementSlide(self);
    switch (self->state) {
    case 0:
    case 1:
    {
        if (self->pressed != 0) {
        if (g_padRecord.fAA & 4) {
            ClearPadPressedBits(&g_padRecord, 4);
            StartLockedStreamVoice((s32)g_currentWorld->f2310);
            if (g_currentWorld->f2314 != 0) {
                SetScreenElementHoldTime(self, 15.0f);
                self->vt->m08(self, (const char*)g_currentWorld->f2314);
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
        SetTimerRate(o, -func_00205C78(2.0f, (f32)D_002623DC));
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

struct X_1E02C8 { u8 pad[4]; };

extern s32 D_002623DC;
extern X_1E02C8 D_00264A40;

void func_001AB958(T217D_510* o);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00160C48(s32 v);
void func_001DDAD0(World* g);
void func_001AB890(T217D_510* o, f32 v);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(T217D_510* o, f32 v);
void func_001AB928(T217D_510* o, f32 v, void* fn);
void func_001AB938(T217D_510* o);
s32 func_001E1FD0(Buf_1E02C8* dst, const char* fmt, ...);
void func_0018C7F8(X_1E02C8* x);
s32 func_001602A0(void);
void func_001604B8(s32 m);
void func_00194D30(T217D_6D0* y, s32 a, s32 b);
void func_00148CE0(World* g);

void func_001E02C8(T217D_1380* self, s32 n)
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
        func_001DDAD0(g_currentWorld);
        StartTimer(&g_timerElement, g_currentWorld->f230C + 0.99f);
        SetTimerRate(&g_timerElement, -func_00205C78(2.0f, (f32)D_002623DC));
        SetTimerLimit(&g_timerElement, zero, 0);
        StartTimerCounting(&g_timerElement);
        G27C230* cam = g_currentEntry;
        if (cam->flags & 8) {
            f32 t = cam->f08;
            if (t < one) {
                FormatToString(&D_00275900, "Best time: &10.%d", (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 minutes = s / 60;
                s32 seconds = s % 60;
                FormatToString(&D_00275900, "Best time: &1%d:%02d", minutes, seconds);
            }
            SetScreenElementHoldTime(self, zero);
            self->vt->m08(self, D_00275900.c);
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

struct Out_1E0678;
void func_00137228(Out_1E0678* out, f32 x, f32 y);
void func_00137238(Out_1E0678* out, f32 x, f32 y);
void func_00137248(Out_1E0678* out, s32* value);
void func_00137260(Out_1E0678* out, s32 flag);
void func_00137268(Out_1E0678* out, s32 flag);
struct Out_1E0678 {
    u8 b[32];
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};
struct Hd_1E0678 {
    static void Draw(V24A2** h, Out_1E0678* out, void* tbl)
    {
        if (*h != 0) {
            const V24A2_Vt* vt = (*h)->vt;
            vt->drawBox((V24A2*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};

extern f32 D_0027240C;
void func_0015C8B8(V24A2* font, f32 a, f32 b);
void* func_0015DB28(void* out, void* p, V24A2* font);
void func_0015E318(void* a, void* b, s32 c, void* d);
void func_0015C900(V24A2* font);

void func_001E0678(T217D_1380* self)
{
    T217D_Word tmp;
    Out_1E0678 out;
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
            Hd_1E0678::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        InitTextReader(loc, &self->text[0], self->font);
        DrawAlignedText(loc, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

LINKER_REMNANT(func_001E0820);

void func_001E0828(void* self)
{
    SetBestTimeState(self, 3);
}

// The style above is built by the static initialiser GCC writes here (func_001E0848), and its
// _GLOBAL_$I$ (func_001E08D8) follows the 12 bytes the linker left of a function this file wrote
// out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001E08C8);
