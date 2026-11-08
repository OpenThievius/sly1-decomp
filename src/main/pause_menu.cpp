// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "screen_element.h"
#include "packet_writer.h"
#include "font.h"
#include "shapes.h"
#include "load_progress.h"
#include "text_reader.h"
#include "layout_137228.h"
#include "game_progress.h"
#include "pad_record.h"
#include "memory_card.h"
#include "background_job.h"
#include "screen_fade.h"

void SendDisplayResetPacket(LoadProgress*);
void DrawLoadProgressBar(LoadProgress*);

s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);

s32 IsFontLoaded(s32 k);
Font* GetFontById(s32 k);

// The DISPLAY register pair at D_00262490 (0x18 and 0x40), read as func_00193EE8 reads them.
struct DisplayRegRead {
    u8 pad[0x18];
    union {
        struct {
            u32 x : 12;
        } a;
        s64 q18;
    };
};

extern f32 D_0026A700;
extern f32 D_0026A704;
extern f32 D_0026A708;
extern f32 D_0026A70C;

void StopStreamVoice(void);

s32 GetEntryName(s32 v);
s32 FormatToString(char* dst, const char* fmt, ...);

// The packet DrawLoadProgressBar builds on its stack: its memory, then the writer.
struct BarPacket { u8 bytes[0x400]; PacketWriter f; };

void* InitGifPacket(PacketWriter* f);
void UsePacketBufferMemory(PacketWriter* f, s32 n, BarPacket* b);
void BeginDmaTag(PacketWriter* f);
f32 TruncateFloat(f32 x);
void WriteColoredSpritePacket(s32 a, s32 b, s32 c, s32 d, PacketWriter* e, f32 x, f32 y, f32 z, f32 w);
void EndGifPacket(PacketWriter* f);
void AddDmaEndTag(PacketWriter* f);
void CloseDmaTag(PacketWriter* f);
void DetachPacketBuffer(PacketWriter* f, s32 a, s32 b);
void SendPacketToBothBuffers(BarPacket* b);

void ShowScreenElement(void* self);

void HideScreenElement(void* self);

void BuildPauseMenuPage(void* self, s32 v);


extern void* g_currentWorld;

void SetPauseMenuLayerPage(void* self, s32 a, s32 b);
void StartScreenFade(void* obj, void* rec, s32 n);
void* FindFirstObjectByIdGathered(void* a, s32 b, s32 c, s32 d);
void SetPairControllerState(void* p, s32 mode);
void BeginLevelExit(void* a, s32 b);

void BuildPauseMenuPage(T217D_6D0* self);
void SetPauseMenuPage(void* self, s32 v);
void SetScreenElementMode(void* self, s32 flag);

extern u8 g_elementStack[];

void ChangePauseMenuPage(void* self, s32 a, s32 b);
void SetPauseMenuPage(void* self, s32 v);
void PopStackElement(void* q);
void PushStackElement(void* a, void* b);

extern u8 D_00247AB0[];

void StartScreenFade(void* dst, void* args, s32 count);


extern u8 g_unitZVector[];

// The two DISPLAY registers at D_00262490 (the screen's position: 12 bits of x, 11 of y).
// The register at +0x18 is described with 32-bit bit-fields, the one at +0x40 with 64-bit ones;
// the mixed types are what give retail's copy of the masked value.
struct DisplayReg64 { u64 lo : 12; u64 mid : 11; u64 rest : 41; };
struct DisplayReg32 { u32 lo : 12; u32 mid : 11; u32 rest : 9; u32 hi; } __attribute__((aligned(8)));
struct DisplayRegs {
    u8 pad0[0x18];
    DisplayReg32 f18;
    u8 pad20[0x20];
    DisplayReg64 f40;
};
extern DisplayRegs D_00262490;
extern s32 D_00275BF0;
extern f32 D_0026A708;
extern f32 D_0026A70C;
void SetPauseMenuLayerPage(T217D_6D0* self, s32 a, s32 b);
s32 ConvertFloatToU32(f32 x);


extern u8 g_elementStack[];
extern u8 D_00247AD0[];
extern CardSlot D_002542D8[];

void CancelPauseMenuPage(T217D_6D0* self);
void SetPauseMenuLayerPage(T217D_6D0* self, s32 a, s32 b);
void ExitLevelFromPauseMenu(T217D_6D0* self, s32 a, s32 b);
void PushStackElement(u8* a, void* b);
void BeginLevelExit(s32 a, s32 b);
void StartObjectFade(u8* a, s32 b, s32 c);
void SetMemoryCardDisplayMode(MemoryCard* a, s32 b);
void StartBackgroundJob(BackgroundJob* a, void* fn, MemoryCard* self);
s32 SaveGameToMemoryCardSlot(MemoryCard* self);
s32 RunMemoryCardFormatJob(MemoryCard* self);
s32 CreateMemoryCardSaveFiles(MemoryCard* self);
s32 WriteSelectedMemoryCardSlot(MemoryCard* self);
s32 ApplyMemoryCardImage(MemoryCard* self);
void ResumeAtSavedLevel(void);
void BuildPauseMenuPage(T217D_6D0* self);
void* GetActiveSwitchedCollider(void);
s32 IsObjectOfKind(void* node, s32 kind);
void GetStateWalkerCurrentKey(void* ptr, s32* out);
void RecordPathFollowerProgress(void* p);
void TeleportStateWalker(void* h, s32 arg);
void SetStateWalkerTarget(s32 a, s32 b);
s32 ComputeCompletionMask(void);
void FadeOutAndQueueMovie(s32 n);
void StartPauseMenuExitFade(void);
void TogglePadPatternSetting(GameProgress* g);
void SilenceVolumeChannel3(s32 flag);
s32 ApplySoundOptionFlag(s32 flag);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

// The glyph mark FindSubstring finds in a page title: the glyph is its third byte.
struct GlyphMark {
    u8 pad0[2];
    u8 f2;
};

extern f32 g_elapsedTime;
extern CardSlot* D_0026998C;
extern s32 D_00264A4C;
extern f32 D_0026A22C;
// The speeds the screen-position page moves the screen at (x is D_0026A22C).
struct ScreenAdjustRate { f32 f0; f32 f4; };
extern ScreenAdjustRate D_0026A230;
extern f32 D_0026A700;
extern f32 D_0026A704;

s32 ComputeCompletionPercent(GameProgress* g);
s32 CheckStreamVoicePending(void);
s32 PollIopCommands(void);
s32 HasStreamVoice(void);
s32 GetPadVerticalStep(PadRecord* p);
s32 GetPadHorizontalStep(PadRecord* p);
void ClearPadPressedBits(PadRecord* p, s32 mask);
f32 GetPadButtonAnalog(PadRecord* p, s32 idx);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void SetPauseMenuLayerPage(T217D_6D0* self, s32 a, s32 b);
void ActivatePauseMenuSelection(T217D_6D0* self);
void CancelPauseMenuPage(T217D_6D0* self);
void StartPauseMenuExitFade(void);
s32 IsBackgroundJobRunning(BackgroundJob* p);
void StartBackgroundJob(BackgroundJob* p, void* fn, void* arg);
GlyphMark* FindSubstring(void* a, const char* name);
s32 GetCyclingGlyph(void);
s32 ConvertFloatToU32(f32 x);

struct ClampFloat {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

enum PadSelectBits {
    PAD_SELECT_NONE = 0
};

extern u8 g_elementStack[];
extern u8* D_0027051C;

void PauseStagedBankVoice(void);
void ResumeStagedBankVoice(void);
void SetElementStackState(void* self, s32 mode);
void ChangePauseMenuPage(T217D_6D0* self, s32 a, s32 b);
s32 SetPadSelectFlags(PadSelectBits bits);
void ClearPadSelectFlags(PadSelectBits n);
void ResetPadStepRepeat(PadRecord* p);

// func_0015DB28 builds a text buffer and returns it (a constructor's `this`).

void FillMemory(void* p, s32 zero, s32 size);

// The style of the menu's box (D_0026A210, the element's frame): the font that draws it and
// its colour; the static initialiser builds it.
struct MenuBoxStyle {
    Font* font;
    u8 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    union {
        u32 f18;
        Rgba4 color;
    };
    MenuBoxStyle(s32 size)
    {
        FillMemory(this, 0, 0x1C);
        f4 = 0x2D;
        f8 = size;
        f14 = f10 = 0.6f;
        f18 = 0xFF7D4B00;
    }
};
// A page of the pause menu (g_pauseMenuPages): its title, the scales of the title and the items,
// whether the items stand in a column, and the items (indices of choice labels).
struct MenuPage { char* title; f32 titleScale; f32 itemScale; s32 vertical; s32 count; s32* items; };
extern MenuPage g_pauseMenuPages[33];

extern f32 g_gameClock[];
extern s32 D_00275BEC;
extern f32 D_00262CEC;
extern u8 g_fadeRampProfile[];
extern u8 g_gsPacketWriter[];

f32 Sine(f32 x);
void SetTextLayoutPosition(Layout_137228* out, f32 x, f32 y);
void SetTextLayoutSize(Layout_137228* out, f32 x, f32 y);
void SetTextLayoutColor(Layout_137228* out, Quad4* value);
void SetTextLayoutHorizontalAlign(Layout_137228* out, s32 flag);
void SetTextLayoutVerticalAlign(Layout_137228* out, s32 flag);
f32 ApproachValueWithRamp(void* p, s32 zero, f32 a, f32 b, f32 c);
void PushFontScale(Font* font, f32 a, f32 b);
TextReader* InitTextReader(TextReader* out, void* str, Font* font);
void DrawAlignedText(TextReader* buf, Layout_137228* out, s32 zero, void* data);
f32 MeasureTextHeight(TextReader* buf, f32 w);
void PopFontScale(Font* font);
f32 SumTextWidth(TextReader* buf);
char* GetMenuChoiceLabel(s32 index);
void DrawLineSegment(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, Rgba4* c, s32 k);

struct SetupLayout { static void Do(Layout_137228* out, f32 x, f32 y, f32 w, f32 h, s32 color, s32 flag)
{
    SetTextLayoutPosition(out, x, y);
    SetTextLayoutSize(out, w, h);
    Quad4 tmp;
    tmp.w[0] = color;
    SetTextLayoutColor(out, &tmp);
    SetTextLayoutHorizontalAlign(out, flag);
    SetTextLayoutVerticalAlign(out, 0);
} };

struct DrawBoxWithFont { static void Do(MenuBoxStyle* o, Layout_137228* out, void* d)
{
    Font* hk = o->font;
    if (hk != 0) {
        hk->vt->drawBox((Font*)((u8*)hk + hk->vt->adj9), o, out, d);
    }
} };

struct LerpChannel { static s32 Do(s32 a, s32 b, f32 t)
{
    if (a == b) {
        return b;
    }
    if (a < b) {
        return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
    }
    return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
} };

struct LerpColor { static void Do(Rgba4* out, Rgba4 a, Rgba4 b, f32 t)
{
    Rgba4 r;
    r.r = LerpChannel::Do(a.r, b.r, t);
    r.g = LerpChannel::Do(a.g, b.g, t);
    r.b = LerpChannel::Do(a.b, b.b, t);
    r.a = LerpChannel::Do(a.a, b.a, t);
    *out = r;
} };

void FillMemory(void* p, s32 zero, s32 size);

// The file's .data, in retail's order from 0x269CD8, and the strings of its menus, which open
// its .rodata. The style (func_00196330, the static initialiser, builds it) and the buffers the
// menus' labels are written into at run time are zeros until then.
// A choice's labels, one per state (g_menuChoiceStates).
struct ChoiceLabels { s32 count; char** labels; };

extern s32 g_pauseMenuItems[];
extern s32 g_optionsMenuItems[];
extern char D_0026A480[];
extern char D_0026A4C0[];
extern char D_0026A500[];
extern char D_0026A540[];
extern char D_0026A580[];
extern char D_0026A5C0[];
extern char D_0026A600[];
extern char D_0026A640[];
extern char D_0026A680[];
extern char D_0026A6C0[];

s32 D_00269CD8[8] = { 3, 18, 19, 20, 4, 5, 21, 9 };
s32 g_yesNoItems[2] = { 0, 1 };
s32 D_00269D00[2] = { 2, 0 };
s32 D_00269D08[4] = { 10, 11, 12, 17 };
s32 D_00269D18[10] = { 6, 7, 8, 15, 16, 13, 14, 23, 17, 0 };
s32 D_00269D40[4] = { 24, 25, 26, 17 };
MenuPage g_pauseMenuPages[33] = {
    { "Paused", 1.0f, 1.0f, 1, 8, g_pauseMenuItems },
    { "Game Over. Try again?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "Really Quit?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "There is no Memory Card (PS2) inserted in\nMemory Card Slot 1\n\nSly Cooper requires 49 KB of free space\n\nPlease insert a Memory Card (PS2) containing sufficient space or you will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) in Memory Card Slot 1 is unformatted\n\nIf you do not format it then you will not be able to save your progress\n\nDo you want to format?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "\nFormatting the Memory Card (PS2) in Memory Card Slot 1\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "An error occurred while formatting the Memory Card (PS2) in Memory Card Slot 1\n\nYou will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "No Sly Cooper Save File on the Memory Card (PS2) inserted in Memory Card Slot 1\n\nSly Cooper requires 49 KB of free space\n\nIf you do not create a Sly Cooper Save File then you will not be able to save your progress\n\nDo you want to create a Sly Cooper Save File?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "\nCreating the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "An error occurred while creating the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nYour progress is not being saved\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) inserted in Memory Card Slot 1 does not have enough free space to create a Sly Cooper Save File\n\nSly Cooper requires 49 KB of free space\n\nPlease insert a Memory Card (PS2) containing sufficient space or you will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "Save Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "\nSaving...\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "Game Saved", 1.0f, 1.0f, 1, 1, D_00269D00 },
    { "Do you want to overwrite this game?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "An error occurred while writing to the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nYour progress is not being saved\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "New Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "Load Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "Do you want to erase this game?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "\nErasing...\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "When the following icon appears,\nyour progress is being saved\n\n^15&2a&.^.\n\nWhile this icon is on screen, please\ndo not turn off your system or remove\nthe Memory Card (PS2)\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) in Memory Card Slot 1 was removed\n\nAuto-save has been disabled\n\nUse the save game option to manually save your game and re-enable auto-save\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The disc was removed\n\nPlease insert the Sly Cooper disc to continue playing", 0.8f, 1.0f, 1, 0, 0 },
    { "Options", 1.0f, 1.0f, 1, 9, g_optionsMenuItems },
    { "&2T&. : Cancel\n&2+&. : Move\n&2X&. : Accept", 0.8f, 1.0f, 1, 0, 0 },
    { "Try again?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "Try again?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "CONGRATULATIONS!\n\nYou have beaten the\nMaster Thief Sprint!\n\nReturn to this level at any time\nto hear the Bonus Commentary!", 0.8f, 1.0f, 0, 1, D_00269D00 },
    { "TIME EXPIRED\n\nWould you like to retry\nthe Master Thief Sprint?\n\n", 0.8f, 1.0f, 0, 2, g_yesNoItems },
    { "CONGRATULATIONS!\n\nYou beat your best\nMaster Thief Sprint time!\n\nTry Again?", 0.8f, 1.0f, 0, 2, g_yesNoItems },
    { "You didn't beat your best\nMaster Thief Sprint time\n\nTry again?", 0.8f, 1.0f, 0, 2, g_yesNoItems },
    { "Controls", 1.0f, 0.8f, 1, 4, D_00269D40 },
    { "\nPlease insert a Memory Card (PS2) in Memory Card Slot 1 that contains a Sly Cooper Save File\n", 1.0f, 1.0f, 1, 1, D_00269D00 },
};
char* g_menuChoiceLabels[28] = {
    "Yes",
    "No",
    "Continue",
    "Return to Game",
    "View Map",
    "Options...",
    "New Game...",
    "Load Game...",
    "Save Game...",
    D_0026A540,
    D_0026A480,
    D_0026A4C0,
    D_0026A500,
    D_0026A580,
    "Center Screen...",
    D_0026A5C0,
    D_0026A600,
    "Back",
    "Restart Race",
    "Restart Sprint",
    "Restart Level",
    "Exit Level",
    "Exit to Hideout",
    "Controls...",
    D_0026A640,
    D_0026A680,
    D_0026A6C0,
    0,
};
char* D_0026A0D8 = "New Game";
char* D_0026A0DC = "Empty";
char* D_0026A0E0[2] = { "Quit Game", "Save and Quit" };
char* D_0026A0E8[2] = { "Vibrations: On", "Vibrations: Off" };
char* D_0026A0F0[2] = { "Music: On", "Music: Off" };
char* D_0026A0F8[2] = { "Speakers: Stereo", "Speakers: Mono" };
char* D_0026A100[2] = { "Binoc-u-com: &2(&. Up = Look Down", "Binoc-u-com: &2(&. Up = Look Up" };
char* D_0026A108[2] = { "Turrets: &2(&. Up = Aim Down", "Turrets: &2(&. Up = Aim Up" };
char* D_0026A110[2] = { "Jet Pack: &2(&. Up = Fly Down", "Jet Pack: &2(&. Up = Fly Up" };
u32 D_0026A118[8] = { 0x2815A489, 0x4A3840F1, 0xDB146408, 0x9260417F, 0x4CCB23D6, 0x281349F9, 0xDB146685, 0x4A39BF71 };
ChoiceLabels D_0026A138[27] = {
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 2, D_0026A0E0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 2, D_0026A0E8 },
    { 0, 0 },
    { 2, D_0026A0F0 },
    { 2, D_0026A0F8 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 2, D_0026A100 },
    { 2, D_0026A108 },
    { 2, D_0026A110 },
};
MenuBoxStyle D_0026A210(15);
f32 D_0026A22C = 5.0f;
ScreenAdjustRate D_0026A230 = { 2.0f, 0.0f };
s32 g_pauseMenuItems[8] = { 0 };
s32 g_optionsMenuItems[138] = { 0 };
char D_0026A480[64] = { 0 };
char D_0026A4C0[64] = { 0 };
char D_0026A500[64] = { 0 };
char D_0026A540[64] = { 0 };
char D_0026A580[64] = { 0 };
char D_0026A5C0[64] = { 0 };
char D_0026A600[64] = { 0 };
char D_0026A640[64] = { 0 };
char D_0026A680[64] = { 0 };
char D_0026A6C0[64] = { 0 };
f32 D_0026A700 = 0;
f32 D_0026A704 = 0;
f32 D_0026A708 = 0;
f32 D_0026A70C = 0;

LoadProgress* InitLoadProgress(LoadProgress* self, U32P* s1, U32P* s2, U32P* s3, U32P* s4);
void BeginLoadProgress(LoadProgress* p);
void UpdateLoadProgress(LoadProgress* self, s32 value);
void EndLoadProgress(LoadProgress* p);
void DrawLoadProgressBar(LoadProgress* o);
void FormatGameSummary(GameProgress* self, char* dst);
s32 FindObject42CStateWalker(void);
void InitPauseMenu(T217D_6D0* self);
void ChangePauseMenuPage(T217D_6D0* self, s32 a, s32 b);
void SetPauseMenuOpen(T217D_6D0* self, s32 mode);
void ExitLevelFromPauseMenu(void* a0, s32 a1, s32 a2);
void StartPauseMenuExitFade(void);
void UpdatePauseMenu(T217D_6D0* self);
void SetPauseMenuLayerPage(T217D_6D0* self, s32 idx, s32 value);
void SetPauseMenuMode(T217D_6D0* self, s32 v);
void ShowPauseMenu(T217D_6D0* self);
void HidePauseMenu(T217D_6D0* self);
void DrawPauseMenu(T217D_6D0* self);
void SetPauseMenuPage(T217D_6D0* self, s32 v);
void ActivatePauseMenuSelection(T217D_6D0* self);
void CancelPauseMenuPage(T217D_6D0* self);

LoadProgress* InitLoadProgress(LoadProgress* self, U32P* s1, U32P* s2, U32P* s3, U32P* s4)
{
    self->f14 = *s1;
    self->f18 = *s2;
    self->f1C = *s3;
    self->f20 = *s4;
    self->active = 0;
    self->stalls = 0;
    self->current = 0;
    self->total = 0;
    self->scale = 0;
    return self;
}

void BeginLoadProgress(LoadProgress* p) { p->active=0; p->stalls=0; p->current=0; p->total=0; p->scale=0; }

void UpdateLoadProgress(LoadProgress* self, s32 value)
{
	if (self->active != 0) {
		if (self->total == 0) { self->scale = value << 1; self->total = value; SendDisplayResetPacket(self); }
		else if (self->current == value) self->stalls++;
		else self->stalls = 0;
		self->current = value;
		DrawLoadProgressBar(self);
	}
}

void EndLoadProgress(LoadProgress* p) { p->active=0; p->stalls=0; p->current=0; p->total=0; p->scale=0; }

void DrawLoadProgressBar(LoadProgress* o)
{
    BarPacket buf;
    s32 n1;
    s32 n2;
    BarColor c;

    n1 = (s32)((f32)o->total * 620.0f / (f32)o->scale);
    n2 = (s32)((f32)n1 * (f32)(o->total - o->current) / (f32)o->total);
    InitGifPacket(&buf.f);
    UsePacketBufferMemory(&buf.f, 0x40, &buf);
    BeginDmaTag(&buf.f);
    {
        u8 r = o->barColor.r;
        u8 g = o->barColor.g;
        u8 b = o->barColor.b;
        f32 y = TruncateFloat(412.909088f) * 1.1f;
        f32 z = (f32)(n2 + 10);
        WriteColoredSpritePacket(r, g, b, 255, &buf.f, 10.0f, y, z, TruncateFloat(412.909088f) * 1.1f + 6.6000004f);
    }
    if (o->stalls <= 0) {
        c = o->color0;
    } else if (o->stalls == 1) {
        c = o->color1;
    } else {
        c = o->color2;
    }
    {
        u8 r = c.r;
        u8 g = c.g;
        u8 b = c.b;
        f32 x = (f32)(n2 + 10);
        f32 y = TruncateFloat(412.909088f) * 1.1f;
        f32 z = (f32)(n1 + 10);
        WriteColoredSpritePacket(r, g, b, 255, &buf.f, x, y, z, TruncateFloat(412.909088f) * 1.1f + 6.6000004f);
    }
    EndGifPacket(&buf.f);
    AddDmaEndTag(&buf.f);
    CloseDmaTag(&buf.f);
    DetachPacketBuffer(&buf.f, 0, 0);
    SendPacketToBothBuffers(&buf);
}

char* GetMenuChoiceLabel(s32 index)
{
    return g_menuChoiceLabels[index];
}

void FormatGameSummary(GameProgress* self, char* dst)
{
    s32 a = ComputeCompletionPercent(self);
    s32 b = GetEntryName((self->f19D8 << 8) | self->f19DC);
    s32 v = (s32)(self->fC * (1.0f / 60.0f));
    s32 t = v > 0 ? v : 1;
    FormatToString(dst, "%d%% - %s - %d:%02d", a, b, t / 60, t % 60);
}

s32 FindObject42CStateWalker(void)
{
    s32 r = FindFirstObjectById(g_currentWorld, 5, 0x42C, 0);
    s32 v;
    if (r == 0) {
        v = 0;
    } else {
        v = *(s32*)(r + 0x48);
    }
    return v;
}

extern s32 D_0026FA68;
extern s32 D_0026EC58;
extern s32 D_00269984;
void CopyString(char* dst, const char* src);
s32 IsPadPatternEnabled(GameProgress* g);
void OpenKeyRecord(void* rec);
void SetScreenElementSize(void* self, f32 w, f32 h);
void MeasureText(TextReader* buf, f32 w, f32* outW, f32* outH);

// Builds the page on view: the items of the main and options pages as the game's state allows,
// the labels that depend on the state, the row first highlighted, and the box's size.
void BuildPauseMenuPage(T217D_6D0* self)
{
    s32 page = self->page;
    MenuPage* row = &g_pauseMenuPages[page];
    switch (page) {
    case 0:
        row->count = 0;
        for (u32 i = 0; i < 8; i++) {
            s32 item = D_00269CD8[i];
            s32 show = 1;
            switch (item) {
            case 4:
                if (D_0026FA68 == 0) {
                    show = 0;
                }
                break;
            case 5:             // shown always: retail's table sends it to case 20's `show = 1`
                show = 1;
                break;
            case 18: {
                s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
                if (key != 0x204 && key != 0x407) {
                    show = 0;
                    break;
                }
                show = 0;
                s32 walker = FindObject42CStateWalker();
                if (walker != 0) {
                    s32 code;
                    GetStateWalkerCurrentKey((void*)walker, &code);
                    if (code < 0x431) {
                        show = code >= 0x42F;
                    }
                }
                break;
            }
            case 19:
                show = D_0026EC58 == 2;
                break;
            case 20: {
                s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
                show = 0;
                if (key == 0x304 || key == 0x307 || key == 0x502) {
                    show = 1;
                }
                break;
            }
            case 21:
                if (g_saveData->f19D8 == 0) {
                    show = 0;
                } else if (g_saveData->f19D8 == 5 || g_saveData->f19DC == 1 ||
                           (g_saveData->f19DC == 0 && (*(s32*)(g_currentLevelRecord->bits74 + 4) & 1) == 0)) {
                    item = 0x16;
                }
                break;
            }
            if (show != 0) {
                row->items[row->count++] = item;
            }
        }
        break;
    case 0x17:
        row->count = 0;
        for (u32 i = 0; i < 9; i++) {
            s32 item = D_00269D18[i];
            s32 show = 1;
            switch (item) {
            case 6:
                show = ((ElementStack*)g_elementStack)->resumeState == 1;
                break;
            case 7:             // shown always: retail's compare tree tests it
                break;
            case 8:
                show = ((ElementStack*)g_elementStack)->resumeState != 1;
                break;
            }
            if (show != 0) {
                row->items[row->count++] = item;
            }
        }
        break;
    }
    for (s32 i = 0; i < 27; i++) {
        char* dst = g_menuChoiceLabels[i];
        ChoiceLabels* cl = &D_0026A138[i];
        switch (i) {
        case 9:
            if (D_00269984 != 0) {
                CopyString(dst, cl->labels[1]);
            } else {
                CopyString(dst, cl->labels[0]);
            }
            break;
        case 13: {
            char** l = cl->labels;
            CopyString(dst, *(IsPadPatternEnabled(g_saveData) ? l : l + 1));
            break;
        }
        case 15:
        {
            char** l = cl->labels;
            CopyString(dst, *((g_saveData->f19EC & 0x80) ? l + 1 : l));
            break;
        }
        case 16:
        {
            char** l = cl->labels;
            CopyString(dst, *((g_saveData->f19EC & 0x40) ? l + 1 : l));
            break;
        }
        case 24:
        {
            char** l = cl->labels;
            CopyString(dst, *((g_saveData->f19EC & 0x200) ? l + 1 : l));
            break;
        }
        case 25:
        {
            char** l = cl->labels;
            CopyString(dst, *((g_saveData->f19EC & 0x400) ? l + 1 : l));
            break;
        }
        case 26:
        {
            char** l = cl->labels;
            CopyString(dst, *((g_saveData->f19EC & 0x800) ? l + 1 : l));
            break;
        }
        case 10:
        case 11:
        case 12: {
            s32 k = i - 10;
            CardSlot* slot = &g_memoryCard.slots[k];
            if (slot->f0C != 0.0f) {
                FormatGameSummary(&slot->data, dst);
            } else {
                if (page < 0x12) {
                    if (page >= 0x10) {
                        FormatToString(dst, D_0026A0D8);
                        break;
                    }
                }
                FormatToString(dst, D_0026A0DC);
            }
            break;
        }
        }
    }
    switch (page) {
    case 16:
        // The first empty slot. The slots read as a CardSlot pointer: as an array the base folds
        // with the field's offset, where retail keeps the base in a register.
        for (self->cursor = 0; self->cursor < 3 && ((CardSlot*)g_memoryCard.slots)[self->cursor].f0C != 0.0f;
             self->cursor++) {
        }
        break;
    case 11:
    case 17:
        if (g_memoryCard.f4F44 != 0) {
            self->cursor = (CardSlot*)g_memoryCard.f4F44 - g_memoryCard.slots;
            break;
        }
        self->cursor = 0;
        break;
    case 20:
        if (HasStreamVoice() == 0) {
            OpenKeyRecord(D_0026A118);
            self->sound = HasStreamVoice();
        }
        break;
    case 2:
    case 4:
    case 7:
    case 14:
    case 18:
        self->cursor = 1;
        break;
    default:
        self->cursor = 0;
        break;
    }
    f32 width = 0.0f;
    f32 items = width;
    f32 height = width;
    TextReader tr;
    if (row->title != 0) {
        PushFontScale(self->font, row->titleScale, row->titleScale);
        InitTextReader(&tr, row->title, self->font);
        f32 tw, th;
        MeasureText(&tr, 500.0f, &tw, &th);
        PopFontScale(self->font);
        height = th;
        width = tw >? width;
    }
    PushFontScale(self->font, row->itemScale, row->itemScale);
    if (row->vertical != 0) {
        height += (f32)self->font->height * self->font->sy * (f32)row->count;
    } else {
        height += (f32)self->font->height * self->font->sy;
    }
    for (s32 i = 0; i < row->count && row->items[i] != -1; i++) {
        ChoiceLabels* cl = &D_0026A138[row->items[i]];
        f32 w = 0.0f;
        if (cl->count != 0) {
            for (s32 j = 0; j < cl->count; j++) {
                InitTextReader(&tr, cl->labels[j], self->font);
                w = SumTextWidth(&tr) >? w;
            }
        } else {
            InitTextReader(&tr, GetMenuChoiceLabel(row->items[i]), self->font);
            w = SumTextWidth(&tr);
        }
        if (row->vertical != 0) {
            items = items >? w;
        } else {
            if (i != 0) {
                items += (f32)self->font->advance * self->font->sx * 2.0f;
            }
            items += w;
        }
    }
    PopFontScale(self->font);
    width = items >? width;
    SetScreenElementSize(self, width + 10.0f, height);
}

void InitPauseMenu(T217D_6D0* self)
{
    SetupScreenElementText(self);
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&D_0026A210;
        *self->frame = GetFontById(2);
    }
    self->page = -1;
    self->stage = -1;
    for (u32 i = 0; i < 3; i++) {
        self->want[i] = -1;
    }
    self->fade = 1.0f;
}

void ChangePauseMenuPage(T217D_6D0* self, s32 a, s32 b)
{
    if (a == b) {
        return;
    }
    if (self->sound != 0) {
        StopStreamVoice();
        self->sound = 0;
    }
    if (a == 11) {
        goto call;
    }
    if (a > 10) {
        if (a < 18) {
            if (a > 15) {
            call:
                g_buttonHintElement.vt->m15(&g_buttonHintElement);
            }
        }
    }
    switch (b) {
    case 11:
    case 16:
    case 17: {
        T217D_330* o = &g_buttonHintElement;
        SetScreenElementHoldTime(o, 0.0f);
        SetScreenElementScale(o, 0.6f);
        break;
    }
    case 24: {
        D_0026A700 = D_0026A708 = (f32)(u32)((DisplayRegRead*)&D_00262490)->a.x;
        D_0026A704 = D_0026A70C = (f32)((u32)(((DisplayRegRead*)&D_00262490)->q18 >> 12) & 0x7FF);
        break;
    }
    case -1:
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
        D_00274118.vt->m15(&D_00274118);
        break;
    }
}

void SetPauseMenuOpen(T217D_6D0* self, s32 mode) {
    if (self->open == mode) return;
    if (mode != 0) {
        s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
        if (key == 0x308) {
            PauseStagedBankVoice();
            SetElementStackState(g_elementStack, 5);
        } else if (D_0027051C != 0) {
            SetElementStackState(g_elementStack, 5);
        } else {
            u8* base = g_elementStack;
            if (((s32*)base)[1] == 3) {
                SetElementStackState(base, 4);
            } else {
                SetElementStackState(base, 5);
            }
        }
        ChangePauseMenuPage(self, -1, self->page);
        self->vt->m14(self);
        SetPadSelectFlags((PadSelectBits)1);
        ResetPadStepRepeat(&g_padRecord);
    } else {
        s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
        if (key == 0x308) {
            ResumeStagedBankVoice();
            SetElementStackState(g_elementStack, 3);
        } else if (D_0027051C != 0) {
            SetElementStackState(g_elementStack, 3);
        } else if (self->page != 0) {
            SetElementStackState(g_elementStack, 3);
        } else {
            SetElementStackState(g_elementStack, 6);
        }
        ChangePauseMenuPage(self, self->page, -1);
        self->vt->m15(self);
        ClearPadSelectFlags((PadSelectBits)1);
    }
    self->open = mode;
}

void ExitLevelFromPauseMenu(void* a0, s32 a1, s32 a2)
{
    SetPauseMenuLayerPage(a0, 0, -1);
    GameProgress* g = g_saveData;
    s32 key = (g->f19D8 << 8) | g->f19DC;
    if (key == 0x106) {
        if (a1 != 0) {
            FadeRequest r;
            r.kind = 1;
            r.key = &D_00275B04;
            r.f08 = -1;
            r.f0C = -1;
            r.flags = 0;
            StartScreenFade(&g_screenFade, &r, a2);
        } else {
            void* p = FindFirstObjectByIdGathered(g_currentWorld, 5, 0x5F, 0);
            SetPairControllerState(p, 6);
        }
        return;
    }
    if (a1 != 0) {
        FadeRequest r;
        r.kind = 1;
        r.key = &D_00275B04;
        r.f08 = -1;
        r.f0C = -1;
        r.flags = 0x10;
        StartScreenFade(&g_screenFade, &r, a2);
    } else {
        BeginLevelExit(0, a2);
    }
}

void StartPauseMenuExitFade(void)
{
    FadeRequest args;
    args.kind = 1;
    args.text = D_00247AB0;
    args.f08 = -1;
    args.f0C = -1;
    args.flags = 4;
    StartScreenFade(&g_screenFade, &args, 0);
}

void UpdatePauseMenu(T217D_6D0* self)
{
    GameProgress* g = g_saveData;
    MenuPage* row = &g_pauseMenuPages[self->page];
    s32 on;
    s32 n;
    PadRecord* pad;

    on = 0;
    switch ((g->f19D8 << 8) | g->f19DC) {
    case 0x106:
    case 0x204:
    case 0x304:
    case 0x307:
    case 0x407:
    case 0x502:
    case 0x504:
        break;
    default:
        on = self->page == 0;
        break;
    }
    if (on) {
        D_0026C6C8.vt->m14(&D_0026C6C8);
        D_0026C948.vt->m14(&D_0026C948);
        D_0026CBC8.vt->m14(&D_0026CBC8);
        D_0026CE48.vt->m14(&D_0026CE48);
    } else {
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
    }
    switch (self->page) {
    case 0:
    case 11:
    case 17:
        D_00274118.own = ComputeCompletionPercent(g_saveData);
        D_00274118.target = &D_00274118.own;
        D_00274118.vt->m14(&D_00274118);
        break;
    default:
        D_00274118.vt->m15(&D_00274118);
        break;
    }
    if (self->sound != 0) {
        if (CheckStreamVoicePending() != 0) {
            PollIopCommands();
        }
        self->sound = HasStreamVoice();
    }
    s32 ready = 1;
    if (self->queued != 0 || self->mode != 2 || !(0.1f < g_elapsedTime - self->since)) {
        ready = 0;
    }
    pad = &g_padRecord;
    if (row->count == 0) {
        n = 0;
    } else if (row->vertical != 0) {
        n = GetPadVerticalStep(pad);
    } else {
        n = GetPadHorizontalStep(pad);
    }
    if (n > 0) {
        self->cursor = (self->cursor + 1) % row->count;
        StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (n < 0) {
        self->cursor = (self->cursor + row->count - 1) % row->count;
        StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (!ready) {
        return;
    }
    if (pad->flags & 0x810) {
        ClearPadPressedBits(&g_padRecord, 0x810);
        CancelPauseMenuPage(self);
        return;
    }
    if (pad->flags & 0x80) {
        ClearPadPressedBits(&g_padRecord, 0x80);
        if (self->page == 11 || self->page == 16) {
            CardSlot* e = &D_002542D8[row->items[self->cursor]];
            if (e->f0C != 0.0f) {
                D_0026998C = e;
                SetPauseMenuLayerPage(self, 1, 0x12);
            }
        }
        return;
    }
    if (pad->flags & 0x40) {
        ClearPadPressedBits(&g_padRecord, 0x40);
        ActivatePauseMenuSelection(self);
        return;
    }
    switch (self->page) {
    case 24: {
        f32 a = GetPadButtonAnalog(pad, 0);
        f32 dx = a - GetPadButtonAnalog(pad, 1);
        f32 b = GetPadButtonAnalog(pad, 3);
        f32 dy = b - GetPadButtonAnalog(pad, 2);
        f32 v;
        if (dx == 0.0f && dy == 0.0f) {
            return;
        }
        D_0026A700 = ClampFloat::Of(D_0026A700 + dx * D_0026A22C, 424.0f, 848.0f);
        v = ClampFloat::Of(D_0026A704 + dy * D_0026A230.f0, 10.0f, 90.0f);
        D_0026A704 = v;
        {
            DisplayRegs* gs = &D_00262490;
            s32 h = ConvertFloatToU32(D_0026A700);
            DisplayReg64 ra = gs->f40;
            DisplayReg32 rb = gs->f18;
            ra.lo = h;
            rb.lo = h;
            gs->f40 = ra;
            gs->f18 = rb;
            s32 w = ConvertFloatToU32(v);
            ra.mid = w & ~1;
            rb.mid = w & 0x7FE;
            gs->f40 = ra;
            gs->f18 = rb;
        }
        break;
    }
    case 11:
    case 16:
    case 17:
        if (g_memoryCard.displayMode != 1) {
            CancelPauseMenuPage(self);
            return;
        } else {
            s32 id = row->items[self->cursor];
            if ((u32)(id - 10) < 3) {
                CardSlot* e = &D_002542D8[id];
                if (self->page == 16) {
                    if (e->f0C != 0.0f) {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2S&. : Erase Game");
                    } else {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : New Game");
                    }
                } else if (self->page == 17) {
                    if (e->f0C != 0.0f) {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : Load Game");
                    } else {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : New Game");
                    }
                } else {
                    if (e->f0C != 0.0f) {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : Overwrite Game\n&2S&. : Erase Game");
                    } else {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : Save Game");
                    }
                }
                g_buttonHintElement.vt->m14(&g_buttonHintElement);
            } else {
                g_buttonHintElement.vt->m15(&g_buttonHintElement);
            }
        }
        break;
    case 18:
        if (g_memoryCard.displayMode != 1) {
            CancelPauseMenuPage(self);
        }
        break;
    case 20: {
        GlyphMark* it;
        if (g_memoryCard.displayMode != 1) {
            CancelPauseMenuPage(self);
        }
        it = FindSubstring(row->title, "&2");
        if (it != 0) {
            it->f2 = GetCyclingGlyph();
        }
        break;
    }
    case 3:
    case 4:
    case 7:
    case 10:
    case 32:
        if (D_00264A4C == 5) {
            SetPauseMenuLayerPage(&g_pauseMenuElement, 1, -1);
        }
        break;
    case 5: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                StartBackgroundJob(p, (void*)(void (*)(MemoryCard*))CreateMemoryCardSaveFiles, ((u8*)&g_memoryCard));
                SetPauseMenuLayerPage(self, 1, 8);
            } else {
                SetPauseMenuLayerPage(self, 1, 6);
            }
        }
        break;
    }
    case 8: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
            } else {
                SetPauseMenuLayerPage(self, 1, 9);
            }
        }
        break;
    }
    case 12: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
                if (self->stage == 2) {
                    StartPauseMenuExitFade();
                }
            } else {
                SetPauseMenuLayerPage(self, 0, 0x17);
                SetPauseMenuLayerPage(self, 1, 0xF);
            }
        }
        break;
    }
    case 19: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            D_0026998C = 0;
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
            } else {
                SetPauseMenuLayerPage(self, 0, 0x17);
                SetPauseMenuLayerPage(self, 1, 0xF);
            }
        }
        break;
    }
    }
}

void SetPauseMenuLayerPage(T217D_6D0* self, s32 idx, s32 value)
{
    s32 s1;
    s32 s2;
    u32 i;
    s32* p;

    s2 = value;
    self->want[idx] = s2;
    p = self->want;
    for (i = 0; i < 3; i++) {
        if (*p != -1) {
            s2 = *p;
        }
        p++;
    }
    if (self->queued != 0) {
        s1 = self->queuedPage;
    } else {
        s1 = self->page;
    }
    ChangePauseMenuPage(self, s1, s2);
    if (s1 != s2) {
        if (self->mode == 0) {
            SetPauseMenuPage(self, s2);
        } else if (self->mode >= 0) {
          if (self->mode < 4) {
            if (s2 == -1) {
                self->queued = 0;
                self->queuedPage = s2;
            } else {
                self->queuedPage = s2;
                self->queued = 1;
                self->vt->m16(self, 3);
            }
          }
        }
    }
    if (s2 == -1) {
        if (self->open != 0) {
            PopStackElement(g_elementStack);
        }
    } else {
        if (self->open == 0) {
            PushStackElement(g_elementStack, self);
        }
    }
}

void SetPauseMenuMode(T217D_6D0* self, s32 v)
{
    s32 flag = v;

    if (self->mode == v) return;
    if (self->mode == 0 && self->page == 0) {
        BuildPauseMenuPage(self);
    }
    if (v == 0) {
        if (self->queued != 0) {
            SetPauseMenuPage(self, self->queuedPage);
            flag = 1;
            self->queued = 0;
            self->queuedPage = -1;
        } else {
            if (self->page == 0) {
                BuildPauseMenuPage(self);
            }
        }
    }
    SetScreenElementMode(self, flag);
}

void ShowPauseMenu(T217D_6D0* self)
{
    if (self->mode == 3 && self->queued != 0) return;
    ShowScreenElement(self);
}

void HidePauseMenu(T217D_6D0* self)
{
    if (self->mode == 3 && self->queued != 0) {
        self->queued = 0;
        self->queuedPage = -1;
        return;
    }
    HideScreenElement(self);
}

void DrawPauseMenu(T217D_6D0* self)
{
    f32 cx;
    f32 cy;
    f32 h;
    f32 w;
    f32 pulse;
    f32 fade;
    s32 alpha;
    MenuPage* menu;
    f32 lineH;
    f32 base;
    f32 x;
    s32 i;

    if (self->mode == 0) {
        return;
    }
    {
        f32 ww = self->w;
        f32 hh = self->h;
        f32 s = self->blend;
        f32 x0 = self->shownX + ww * 0.5f; 
        f32 y0 = self->shownY + hh * 0.5f; 
        w = ww * s; 
        cx = self->shownX * s + x0 * (1.0f - s); 
        cy = self->shownY * s + y0 * (1.0f - s); 
        h = hh * s; 
    }
    pulse = Sine(g_gameClock[4] * 10.0f) * 0.5f + 0.5f;
    menu = &g_pauseMenuPages[self->page];
    fade = 1.0f;
    if (self->page == 0 && D_00275BEC == 2) {
        fade = 1.0f - D_00262CEC;
    }
    self->fade = ApproachValueWithRamp(g_fadeRampProfile, 0, self->fade, fade, g_gameClock[5]);
    alpha = (u8)(s32)(self->fade * 255.0f);
    if (((MenuBoxStyle*)self->frame) != 0) {
        Layout_137228 out;
        s32 backColor = 0xFF808080;
        SetTextLayoutPosition(&out, cx, cy);
        SetTextLayoutSize(&out, w, h);
        {
            Quad4 tmp;
            tmp.w[0] = backColor;
            SetTextLayoutColor(&out, &tmp);
        }
        SetTextLayoutHorizontalAlign(&out, 0);
        SetTextLayoutVerticalAlign(&out, 0);
        Rgba4 saved = ((MenuBoxStyle*)self->frame)->color;
        {
            Rgba4 t = saved;
            t.a = alpha;
            ((MenuBoxStyle*)self->frame)->color = t;
        }
        if (menu->count == 0) {
            MenuBoxStyle* cur = ((MenuBoxStyle*)self->frame);
            Rgba4 gray;
            gray.r = 0x6F; 
            gray.g = 0x6F; 
            gray.b = 0x6F; 
            gray.a = alpha; 
            Rgba4 res;
            LerpColor::Do(&res, cur->color, gray, pulse * pulse);
            cur->color = res;
        }
        DrawBoxWithFont::Do(((MenuBoxStyle*)self->frame), &out, g_gsPacketWriter);
        ((MenuBoxStyle*)self->frame)->color = saved;
    }
    if (menu->title != 0) {
        TextReader buf;
        Layout_137228 out;
        Rgba4 c;
        f32 sc = menu->titleScale * self->blend;
        PushFontScale(self->font, sc, sc);
        InitTextReader(&buf, menu->title, self->font);
        c.r = 0x7F;
        c.g = 0x7F;
        c.b = 0x7F;
        c.a = alpha;
        SetupLayout::Do(&out, cx, cy, w, h, *(s32*)&c, 1);
        DrawAlignedText(&buf, &out, 0, g_gsPacketWriter);
        cy += MeasureTextHeight(&buf, 500.0f);
        PopFontScale(self->font);
    }
    base = cy + -1.0f;
    {
        f32 sc = menu->itemScale * self->blend;
        PushFontScale(self->font, sc, sc);
    }
    lineH = (f32)self->font->height * self->font->sy;
    if (menu->vertical == 0) {
        f32 total = 0.0f;
        for (s32 k = 0; k < menu->count; k++) {
            TextReader buf;
            if (k != 0) {
                total += (f32)self->font->advance * self->font->sx + (f32)self->font->advance * self->font->sx;
            }
            void* str = GetMenuChoiceLabel(menu->items[k]);
            InitTextReader(&buf, str, self->font);
            total += SumTextWidth(&buf);
        }
        x = cx + (w - total) * 0.5f;
    }
    for (i = 0; i < menu->count; i++) {
        Rgba4 col;
        f32 grow;
        f32 width;
        void* str;
        f32 th;
        if (i == self->cursor) {
            Rgba4 c;
            c.r = 0x6F;
            c.g = 0x6F;
            c.b = (s32)(pulse * 64.0f) + 0x2F;
            c.a = alpha;
            col = c;
            grow = (1.0f - pulse) * 0.1f + 1.0f;
        } else {
            Rgba4 c;
            c.r = 0x5F;
            c.g = 0x5F;
            c.b = 0x5F;
            c.a = alpha;
            col = c;
            grow = 1.0f;
        }
        TextReader buf;
        str = GetMenuChoiceLabel(menu->items[i]);
        InitTextReader(&buf, str, self->font);
        width = SumTextWidth(&buf);
        if (menu->vertical != 0) {
            x = cx + (w - width) * 0.5f;
        }
        {
            f32 sc = menu->itemScale * self->blend * grow;
            PushFontScale(self->font, sc, sc);
        }
        InitTextReader(&buf, str, self->font);
        f32 width2 = SumTextWidth(&buf);
        th = (f32)self->font->height * self->font->sy;
        Layout_137228 out;
        SetupLayout::Do(&out, x + (width - width2) * 0.5f, cy + (lineH - th) * 0.5f, w, th, *(s32*)&col, 0);
        DrawAlignedText(&buf, &out, 0, g_gsPacketWriter);
        PopFontScale(self->font);
        if (menu->vertical != 0) {
            cy += (f32)self->font->height * self->font->sy;
        } else {
            x += width + ((f32)self->font->advance * self->font->sx + (f32)self->font->advance * self->font->sx);
        }
    }
    PopFontScale(self->font);
    if (menu->title != 0 && menu->count != 0) {
        Rgba4 c = D_0026A210.color;
        c.a = alpha;
        s32 y = (s32)((base * 0.45454547f + 1936.0f) * 16.0f);
        DrawLineSegment((s32)((cx + 1728.0f) * 16.0f), y, 0, (s32)((cx + w + 1728.0f) * 16.0f), y, 0, &c, 0);
    }
}

void SetPauseMenuPage(T217D_6D0* self, s32 v)
{
    if (self->page != v) {
        self->page = v;
        if (v != -1) BuildPauseMenuPage(self, v);
    }
}

void ActivatePauseMenuSelection(T217D_6D0* self)
{
    s32 sel = g_pauseMenuPages[self->page].items ? g_pauseMenuPages[self->page].items[self->cursor] : -1;
    if (sel == 0x11) {
        CancelPauseMenuPage(self);
        return;
    }
    switch (self->page) {
    case 0:
        switch (sel) {
        case 3:
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        case 4: {
            T217D_0F0* s = &g_mapScreenList;
            if (s->current != 0) {
                SetPauseMenuLayerPage(self, 0, -1);
                PushStackElement(g_elementStack, s);
                return;
            }
            StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            return;
        }
        case 18: {
            s32 v;
            void* s2 = (void*)FindObject42CStateWalker();
            void* s0 = GetActiveSwitchedCollider();
            if (s2 != 0 && s0 != 0 && IsObjectOfKind(s0, 0x19) != 0) {
                GetStateWalkerCurrentKey(s2, &v);
                if (v < 0x431) {
                    if (v >= 0x42F) {
                        RecordPathFollowerProgress(s0);
                        TeleportStateWalker(s2, 0x42E);
                    }
                }
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        case 19:
        case 20:
            ExitLevelFromPauseMenu(self, 1, 1);
            return;
        case 21:
            SetPauseMenuLayerPage(self, 0, -1);
            BeginLevelExit(1, 2);
            return;
        case 22:
            SetPauseMenuLayerPage(self, 0, -1);
            StartObjectFade(D_00247AD0, -1, 2);
            return;
        case 9:
            SetPauseMenuLayerPage(self, 0, 2);
            return;
        case 5:
            SetPauseMenuLayerPage(self, 0, 0x17);
            return;
        case 23:
            SetPauseMenuLayerPage(self, 0, 0x1F);
            return;
        }
        return;
    case 23:
        switch (sel) {
        case 6:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0x10);
            return;
        case 7:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0x11);
            return;
        case 8:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0xB);
            return;
        case 13:
            TogglePadPatternSetting(g_saveData);
            {
                s32 keep;
                keep = self->cursor;
                BuildPauseMenuPage(self);
                self->cursor = keep;
            }
            return;
        case 15: {
            GameProgress* g = g_saveData;
            g->u19EC ^= 0x80;
            SilenceVolumeChannel3(g->u19EC & 0x80);
            {
                s32 keep;
                keep = self->cursor;
                BuildPauseMenuPage(self);
                self->cursor = keep;
            }
            return;
        }
        case 16: {
            GameProgress* g = g_saveData;
            g->u19EC ^= 0x40;
            ApplySoundOptionFlag(g->u19EC & 0x40);
            {
                s32 keep;
                keep = self->cursor;
                BuildPauseMenuPage(self);
                self->cursor = keep;
            }
            return;
        }
        case 14:
            SetPauseMenuLayerPage(self, 0, 0x18);
            return;
        case 23:
            SetPauseMenuLayerPage(self, 0, 0x1F);
            return;
        }
        return;
    case 27:
        if ((ComputeCompletionMask() & 8) != 0) {
            FadeOutAndQueueMovie(8);
            return;
        }
        ExitLevelFromPauseMenu(self, 0, 2);
        return;
    case 1:
    case 26:
    case 28:
    case 29:
    case 30:
        ExitLevelFromPauseMenu(self, (u32)sel < 1, 1);
        return;
    case 25: {
        s32 a = self->f280;
        self->f280 = 0;
        SetStateWalkerTarget(a, sel == 0 ? 0x434 : 0x435);
        SetPauseMenuLayerPage(self, 0, -1);
        return;
    }
    case 2:
        if (sel == 0) {
            MemoryCard* b = &g_memoryCard;
            if (b->f4F44 != 0) {
                self->stage = 2;
                if ((g_saveData->u19EC & 0x100) == 0) {
                    SetPauseMenuLayerPage(self, 1, 0x14);
                } else {
                    SetPauseMenuLayerPage(self, 1, 0xC);
                    StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, b);
                }
            } else {
                StartPauseMenuExitFade();
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        SetPauseMenuLayerPage(self, 0, -1);
        return;
    case 31:
        switch (sel) {
        case 0x18: {
            g_saveData->u19EC ^= 0x200;
            s32 keep = self->cursor;
            BuildPauseMenuPage(self);
            self->cursor = keep;
            return;
        }
        case 0x19: {
            g_saveData->u19EC ^= 0x400;
            s32 keep = self->cursor;
            BuildPauseMenuPage(self);
            self->cursor = keep;
            return;
        }
        case 0x1A: {
            g_saveData->u19EC ^= 0x800;
            s32 keep = self->cursor;
            BuildPauseMenuPage(self);
            self->cursor = keep;
            return;
        }
        }
        return;
    case 14:
        if (sel == 0) {
            goto c6030;
        }
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 4:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)RunMemoryCardFormatJob, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 5);
            return;
        }
        goto c5EC0;
    case 7:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)CreateMemoryCardSaveFiles, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 8);
            return;
        }
        goto c5EC0;
    case 3:
    case 6:
    case 9:
    case 10:
    case 21:
    case 32:
    c5EC0: {
        s32 v;
        SetPauseMenuLayerPage(self, 1, -1);
        SetMemoryCardDisplayMode(&g_memoryCard, 2);
        v = self->want[0];
        if (v == 0xB) {
            goto c5F08;
        }
        if (v < 0xB) {
            return;
        }
        if (v >= 0x12) {
            return;
        }
        if (v < 0x10) {
            return;
        }
    }
    case 24:
    c5F08:
        SetPauseMenuLayerPage(self, 0, 0x17);
        return;
    case 16: {
        CardSlot* e = &D_002542D8[sel];
        if (e->f0C == 0.0f) {
            SetPauseMenuLayerPage(self, 0, -1);
            g_memoryCard.f4F44 = e;
            ApplyMemoryCardImage(&g_memoryCard);
            ResumeAtSavedLevel();
            return;
        }
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    case 17:
        SetPauseMenuLayerPage(self, 0, -1);
        g_memoryCard.f4F44 = &D_002542D8[sel];
        ApplyMemoryCardImage(&g_memoryCard);
        ResumeAtSavedLevel();
        return;
    case 11: {
        CardSlot* e;
        u32 p;
        p = sel * sizeof(CardSlot);
        p += (u32)D_002542D8;
        e = (CardSlot*)p;
        g_memoryCard.f4F4C = e;
        if (e->f0C == 0.0f) {
        c6030:
            MemoryCard* b;
            b = &g_memoryCard;
            b->f4F44 = b->f4F4C;
            self->stage = 0xB;
            if ((g_saveData->u19EC & 0x100) == 0) {
                SetPauseMenuLayerPage(self, 1, 0x14);
            } else {
                SetPauseMenuLayerPage(self, 1, 0xC);
                StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, b);
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        SetPauseMenuLayerPage(self, 1, 0xE);
        return;
    }
    case 18:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)WriteSelectedMemoryCardSlot, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 0x13);
            return;
        }
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 13:
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 20: {
        g_saveData->u19EC |= 0x100;
        s32 v = self->stage;
        switch (v) {
        case 2:
        case 0xB:
            SetPauseMenuLayerPage(self, 1, 0xC);
            break;
        case -1:
            SetPauseMenuLayerPage(self, 1, -1);
            D_00273EB0.vt->m14(&D_00273EB0);
            break;
        }
        StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, &g_memoryCard);
        return;
    }
    }
}

void CancelPauseMenuPage(T217D_6D0* self)
{
    switch (self->page) {
    case 0:
        SetPauseMenuLayerPage(self, 0, -1);
        break;
    case 23:
        if ((u32)(D_00275BF0 - 1) < 2) {
            SetPauseMenuLayerPage(self, 0, -1);
            break;
        }
        SetPauseMenuLayerPage(self, 0, 0);
        break;
    case 24: {
        DisplayRegs* g = &D_00262490;
        s32 v = ConvertFloatToU32(D_0026A708);
        DisplayReg64 a = g->f40;
        DisplayReg32 b = g->f18;
        a.lo = v;
        b.lo = v;
        g->f40 = a;
        g->f18 = b;
        s32 w = ConvertFloatToU32(D_0026A70C);
        a.mid = w;
        b.mid = w;
        g->f40 = a;
        g->f18 = b;
        SetPauseMenuLayerPage(self, 0, 0x17);
        break;
    }
    case 2:
        SetPauseMenuLayerPage(self, 0, 0);
        break;
    case 13:
        SetPauseMenuLayerPage(self, 1, -1);
        break;
    case 11:
    case 16:
    case 17:
    case 31:
        SetPauseMenuLayerPage(self, 0, 0x17);
        break;
    case 14:
    case 18:
        SetPauseMenuLayerPage(self, 1, -1);
        break;
    }
}

// The style above is built by the static initialiser GCC writes here (func_00196330), and its
// _GLOBAL_$I$ (func_001963B8) follows the 16 bytes the linker left of two layout setters this
// file wrote out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001963A8);
