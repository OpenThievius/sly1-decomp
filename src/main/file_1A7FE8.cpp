// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1A7FE8 to 0x1AA268, built whole (config/us/files.tsv): the object pool
// (class 0x8C, from its init method func_001A7FE8), the agent of class 0x0D, and the set-up,
// update and drawing of the 37 screen elements (func_001A9C68 ... func_001AA1F0), whose objects
// it defines. Its .rodata is the FLT_MAX literal of func_001A7FE8 (0x24CBC4); its .data
// (0x26C3E0 to 0x274398) is the per-element placement table D_0026C3E0, then the 37 screen
// objects, uninitialised (zero, filled at run time by func_001A9C68), which GCC puts at the end
// of the file's .data in definition order. Named after its first address until what it was is
// known.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "world.h"
#include "object_pool.h"
#include "screen_element.h"
#include "font.h"
#include "shapes.h"
#include "game_clock.h"
#include "game_progress.h"
#include "text_reader.h"
#include "globals.h"
#include "asm_func.h"
#include "vu0.h"

// The font object's calls.
Font* GetFontById(s32 k);
void PushFontScale(Font* font, f32 x, f32 y);
f32 MeasureFontString(Font* font, void* text);
void DrawFontString(Font* font, void* text, void* out, s32 zero, void* d);
void PopFontScale(Font* font);
void* InitTextReader(void* out, void* text, Font* font);
void DrawAlignedText(void* buf, void* out, s32 zero, void* d);

void UnregisterObject(void* self);
void ClearObjectPoolChoice(void* self);


void GetObjectWorldRotation(void* a, f32* out);
void TransformRotationBetweenFrames(int a, int b, void* c, f32* d);
f32 ArctangentOfRatio(f32 x, f32 y);


void UpdateAgent(void* self);
void StopAnimationPlayer(void* obj);


extern f32 g_gameTime;
extern f32 g_frameDt;

void StepTimer(T217D_510* self, f32 value);

extern s32 g_defaultFont;

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);


void SetTextLayoutPosition(void* out, f32 x, f32 y);
void SetTextLayoutSize(void* out, f32 x, f32 y);
void SetTextLayoutColor(void* out, s32* value);
void SetTextLayoutHorizontalAlign(void* out, s32 flag);
void SetTextLayoutVerticalAlign(void* out, s32 flag);

void StartAgent(GaugeBarAgent* self);
void SetWorldActiveFollower(void* sub, GaugeBarAgent* self);


s32 IsPadSelectFlagHeld(void* sub);


typedef void* (*VFn_1A9960)(void* self);
void UpdateAgentGoal(GaugeBarAgent* self);
void func_001C8418(GaugeBarAgent* self, void* p);


void UpdateAgentState(GaugeBarAgent* self);
void FaceAgentTowardGoalPoint(GaugeBarAgent* self);


extern u8 g_memoryCard[];

void EnterAgentState(GaugeBarAgent* self);
void MarkLevelDone(s32 n);
void StartMemoryCardSave(u8* p);


extern T217D_2E0 g_gaugeBarElement;

s32 AreMenusAndFadeClear(void);



extern ElementPlaceTable g_elementPlaces;
extern u8 g_elapsedTime[];


void* AllocateZeroedFrontMemory(u32 n);


void StartObject(void* self);
void* FindFirstObjectByIdMode4(void* obj, s32 id, void* owner);
s32 IsObjectOfKind(void* node, s32 kind);


s32 FillMemory(void* p, s32 value, s32 size);


s32 FillMemory(void* p, s32 value, s32 size);


void ClearObjectPoolChoice(void* self);



ObjectPoolEntry* FindObjectPoolEntry(ObjectPool* table, s32 key);







// Where func_001A94C0 takes a position and a matrix from: an object's world frame (f0 or f4), a
// placed object's m110 and v140 (f8), or its own copy of both.
struct FrameSource {
    void* f0;
    void* f4;
    PlacedObject* f8;
    u8 pad0[4];
    Vec02 pos;
    Vec02 rot[3];
};

void ConvertPositionToWorld(void* self, void* arg);
s32 GetObjectWorldPosition(void* self, void* arg);
void GetObjectWorldRotation(void* self, void* arg);
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void TransformRotationBetweenFrames(void* a0, void* a1, void* a2, void* a3);


extern u8 g_elapsedTime[];

void CopyObjectData(ObjectPool* self, void* o);
void* GetObjectPoolShare(void* self);
void SetListLinkOffset(void* self, s32 value);
void AppendToList(void* list, void* item);
u8* CopyToFrontMemory(s32 size, void* src);




void SetTextLayoutPosition(void* out, f32 x, f32 y);
void SetTextLayoutSize(void* out, f32 x, f32 y);
void SetTextLayoutColor(void* out, s32* value);
void SetTextLayoutHorizontalAlign(void* out, s32 flag);
void SetTextLayoutVerticalAlign(void* out, s32 flag);




void SetTextLayoutPosition(void* out, f32 x, f32 y);
void SetTextLayoutSize(void* out, f32 x, f32 y);
void SetTextLayoutColor(void* out, void* p);
void SetTextLayoutHorizontalAlign(void* out, s32 v);
void SetTextLayoutVerticalAlign(void* out, s32 v);

extern void* const g_screenElements[];
extern u8 g_padRouting[];
extern u8 g_padRecord[];
extern u8 g_blankPadRecord[];
extern u8 g_screenFade[];

void UpdateScreenFade(void* a, void* b);


extern void* const g_screenElements[];


// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
// The screen elements' methods, in src/main/screen_element.cpp.
void SetupScreenElementText(ScreenElement* self);
void UpdateScreenElementSlide(ScreenElement* self);
void InitCounterCaption(T217D_E30* self);
void DrawCounterCaption(T217D_E30* self);
f32 GetCaptionHoldTime(void);
void InitTimerElement(T217D_510* self);
void UpdateTimerElement(T217D_510* self);
void DrawTimerElement(T217D_510* self);
f32 GetPairCaptionHoldTime(void);
f32 GetGaugeAmountCaptionHoldTime(void);
f32 GetGaugeColliderCaptionHoldTime(void);

extern const Fn_Table D_00217E30[];
extern const Fn_Table D_00217E80[];
extern const Fn_Table D_00217ED0[];
extern const Fn_Table D_00217F20[];
extern const Fn_Table D_00217F70[];
extern const Fn_Table D_00217FC0[];
extern const Fn_Table D_00218010[];
extern const Fn_Table D_00218060[];
extern const Fn_Table D_002180B0[];
extern const Fn_Table D_00218100[];
extern const Fn_Table D_00218150[];
extern const Fn_Table D_002181A0[];
extern const Fn_Table D_002181F0[];
extern const Fn_Table D_00218240[];
extern const Fn_Table D_00218290[];
extern const Fn_Table D_002182E0[];
extern const Fn_Table D_00218330[];
extern const Fn_Table D_00218380[];
extern const Fn_Table D_002183D0[];
extern const Fn_Table D_00218420[];
extern const Fn_Table D_00218470[];
extern const Fn_Table D_002184C0[];
extern const Fn_Table D_00218510[];
extern const Fn_Table D_00218560[];
extern const Fn_Table D_002185B0[];
extern const Fn_Table D_00218600[];
extern const Fn_Table D_002186D0[];
extern const Fn_Table D_00218720[];
extern const Fn_Table D_0021A3F0[];
extern const Fn_Table D_0021A440[];
extern const Fn_Table D_00220BF0[];
extern const Fn_Table D_002210F0[];
extern const Fn_Table D_002212E0[];
extern const Fn_Table D_00221330[];
extern const Fn_Table D_00221380[];
extern u8 g_screenFade[];

void ResetScreenFade(void* p);


extern s8 g_fontEscapeKeys[];
extern u8 g_charClassFlags[];
s32 FormatToString(char* dst, const char* fmt, ...);
void* CopyString(void* dst, void* src);


void* AllocateFrontMemory(s32 size);
PlacedObject* FindFirstObjectById(void* a, s32 b, s32 c, ObjectPool* d);
void SetListLinkOffset(void* p, s32 a);
s32 CountListItems(void* p);
PlacedObject* CreateObjectCopy(PlacedObject* a, World* b, BaseObject* c);





void ChooseObjectPoolItem(ObjectPool* self);





extern void* const g_screenElements[];


extern void* const g_screenElements[];


extern void* const g_screenElements[];

extern ElementPlaceTable g_elementPlaces;



// allocator puts the count in $s1 and the pointer in $s0; retail is the other way round.

extern u8 g_screenFade[];
void DrawScreenFade(u8* a);
void DrawCyclingGlyphElement(u8* a);




void* AllocateZeroedFrontMemory(u32 n);


s32 FormatToStringBounded(char* dst, s32 cap, const char* fmt, ...);
extern s32 D_002751D4;

// EXACT: dst built as i*4 + (u32)items

void AdvanceObjectPoolEntry(ObjectPool* self);
s32 IsObjectPoolItemFree(ObjectPool* self, s32 item);
void* MoveMemory(s32* dst, s32* src, s32 size);



s32 IsObjectPoolItemFree(ObjectPool* self, s32 item);




void StartSoundEffect(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 FormatToStringBounded(char* dst, s32 cap, const char* fmt, ...);

f32 TruncateFloat(f32 x);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void InitScreenElement();
void DrawScreenElementText();
void GetScreenElementSlideInTime();
void GetScreenElementHoldTime();
void GetScreenElementSlideOutTime();
void ResetScreenElement();
void ShowScreenElement();
void HideScreenElement();
void SetScreenElementClock();
void AreScreenElementsTogether();
void SetScreenElementText();
void SetScreenElementMode();
void UpdateCounterCaption();
void InitGauge();
void DrawGauge();
void InitPointerTextCaption();
void SetElementTextAfterSlideOut();
void SetElementModeApplyingPendingText();
s32 AreElementsTogetherOrPending();
void ShowElementUnlessTextPending();
void HideElementOrDropPendingText();
void DrawSlidingGlyphElement();
void InitCopiedTextCaption();
void SetElementTextCopiedAfterSlideOut();
void SetElementModeApplyingCopiedText();
void ShowElementUnlessCopiedTextPending();
void HideElementOrDropCopiedText();
void DrawMessageElement();
void InitHintGlyphElement();
void UpdateHintGlyphElement();
void DrawHintGlyphElement();
void InitTitleElement();
void DrawTitleElement();
void InitPromptElement();
void SetElementModeRebuildingText();
void UpdatePromptElement();
void DrawPromptElement();
void InitLetterboxElement();
void SetElementModeFollowingFade();
void DrawLetterboxElement();
void InitLetterGlyphElement();
void DrawLetterGlyphElement();
void InitCyclingGlyphElement();
void SetElementModeClearingFlag();
void InitPauseMenu();
void SetPauseMenuOpen();
void UpdatePauseMenu();
void SetPauseMenuMode();
void ShowPauseMenu();
void HidePauseMenu();
void DrawPauseMenu();
void InitItemColumn();
void SetupItemColumn();
void UpdateItemColumn();
void UpdateItemColumnSlide();
void DrawItemColumn();
void InitArcPoints();
void CreateArcSprite();
void DrawArc();
void SetArcMode();
void UpdateArc();
void QueueArcDraw();
void ResetArc();
void InitTextPanel();
void SetupTextPanel();
void SetTextPanelMode();
void UpdatePanelStick();
void SetTextPanelOpen();
void ResetTextPanel();
void SetTextPanelText();
f32 GetTextPanelSlideInTime();
f32 GetTextPanelSlideOutTime();
void DrawTextPanel();
void ChooseTextPanelState();
s32 EndTextPanelState();
void DrawSpinningSpriteElement();
void InitWarpMenu();
void HandleWarpMenuInput();
void SetWarpMenuOpen();
void DrawWarpMenu();
void InitSelectionCaption();
void UpdateSelectionCaption();
void HandleSelectionCaptionInput();
void SetSelectionCaptionOpen();
void DrawSelectionCaption();
void InitGridSelector();
void HandleGridSelectorInput();
void SetGridSelectorOpen();
void DrawGridSelector();
void InitCommentaryPromptElement();
void UpdateBestTimeState();
void DrawFramedText();


s32 GetStringLength(const char*);
void* CopyString(char*, const char*);
void MeasureText(TextReader*, f32, f32*, f32*);

extern f32 g_frameDt;

void FormatCounterCaption(T217D_E30* self);
f32 SumTextWidth(TextReader* loc);


// An object func_001A88A0 may add to a pool: a class 0x3B with 0x678 clear or a class 0x20
// with 0x680 set is refused.
struct PoolCandidate { u8 pad0[0x678]; s32 f678; u8 pad1[4]; s32 f680; };

s32 IsObjectAttached(PoolCandidate* p);
s32 IsObjectOfKind(PoolCandidate* p, s32 kind);

// The list walk (list_iter.h): push a frame, step through the elements, pop it.
struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

struct ListWalkNext {
    static u8* Of(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct ListWalkEnd {
    static void Of(ListFrame* it)
    {
        g_activeListFrames = it->prev;
    }
};


// Data defined by this file.
ElementPlaceTable g_elementPlaces = {
    {
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 20.0f, 2, -1, -1 },
        { -18.0f, 20.0f, 1, -1, -1 },
        { -18.0f, 20.0f, 1, 4, 2 },
        { 18.0f, 20.0f, 0, -1, -1 },
        { -18.0f, 20.0f, 1, 5, 2 },
        { -18.0f, 20.0f, 1, -1, -1 },
        { 18.0f, 20.0f, 2, 6, 2 },
        { 0.0f, 20.0f, 2, 3, 2 },
        { -18.0f, 20.0f, 2, 5, 2 },
        { -18.0f, 20.0f, 2, 5, 2 },
        { 18.0f, 20.0f, 2, 6, 2 },
        { 18.0f, 20.0f, 0, -1, -1 },
        { 18.0f, 20.0f, 0, -1, -1 },
        { 18.0f, -20.0f, 0, -1, -1 },
        { 18.0f, -20.0f, 0, 16, 3 },
        { 18.0f, -20.0f, -1, -1, -1 },
        { -18.0f, -20.0f, 1, -1, -1 },
        { -18.0f, -20.0f, 1, 19, 3 },
        { 18.0f, -20.0f, 0, 18, 3 },
        { 18.0f, -20.0f, -1, -1, -1 },
        { 0.0f, -40.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 1.0f, -20.0f, 0, -1, -1 },
        { -1.0f, -20.0f, 1, -1, -1 },
        { -18.0f, 20.0f, 2, -1, -1 },
        { 18.0f, 20.0f, 2, -1, -1 },
        { 18.0f, 20.0f, 2, -1, -1 },
        { -18.0f, -20.0f, 3, -1, -1 },
        { 18.0f, 20.0f, -1, -1, -1 },
        { 18.0f, -20.0f, 2, -1, -1 },
        { 18.0f, -20.0f, 2, -1, -1 },
        { 18.0f, -20.0f, 3, -1, -1 },
        { 0.0f, -20.0f, 3, -1, -1 },
    },
    0,
};

// The 37 screen objects, in address order (D_002486B0 lists them in another order). They have
// no initialiser: func_001A9C68 installs their tables at run time.
T217D_E30 D_0026C6C8;
T217D_E30 D_0026C948;
T217D_E30 D_0026CBC8;
T217D_E30 D_0026CE48;
T217D_E30 D_0026D0C8;
T217D_E30 g_gaugeAmountCaption;
T217D_E30 D_0026D5C8;
T217D_E30 D_0026D848;
T217D_E30 D_0026DAC8;
T217D_E30 D_0026DD48;
T217D_E30 D_0026DFC8;
T217D_2E0 g_gaugeBarElement;
T217D_E30 D_0026E4E0;
T217D_510 g_timerElement;
T217D_1380 g_timerCaption;
T217D_330 g_buttonHintElement;
T217D_380 D_0026EED0;
T217D_3D0 D_0026F138;
T217D_420 D_0026F5A0;
T217D_0F0 g_mapScreenList;
T217D_12E0 D_0026FA90;
T217D_1330 D_0026FD00;
T217D_6D0 g_pauseMenuElement;
T217D_440 g_typedTextCaptionBox;
T217D_BF0 D_00270650;
T217D_3F0 D_002708E0;
T217D_3F0 D_00271558;
T217D_560 D_002721D0;
T217D_E30 D_00272430;
T217D_E30 D_002726B0;
T217D_470 D_00272930;
T217D_4C0 D_00272B98;
T217D_720 g_stackedCaptionGroup;
T217D_5B0 D_002739F0;
T217D_5B0 D_00273C50;
T217D_600 D_00273EB0;
T217D_E30 D_00274118;




void InitObject(ObjectPool* self);

void* AppendQueuedCall(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void SpawnObjectPoolCopies(ObjectPool* self);



void InitObjectPool(ObjectPool* self)
{
    InitObject(self);
    u8* s1 = (u8*)self + 0x60;
    self->id4C = -1;
    self->id50 = -1;
    self->id54 = -1;
    self->id58 = -1;
    (void)FillMemory(s1, 0, 0x80);
    const Quad16* src = (const Quad16*)&g_identityMatrix;
    *(Quad16*)(s1 + 0x20) = src[0];
    *(Quad16*)(s1 + 0x30) = src[1];
    *(Quad16*)(s1 + 0x40) = src[2];
    (void)FillMemory(((u8*)self + 0xE0), 0, 0x70);
    V8C* p = &self->v110;
    p->a = 0;
    p->b = 1.0f;
    p->c = 0;
    self->f120 = 0;
    self->f124 = 20000.0f;
    (void)FillMemory(((u8*)self + 0x150), 0, 0x18);
    f32 d = 3.4028235e+38f;
    self->fD8 = 5.0f;
    self->f168 = 0;
    self->f144 = d;
    AppendQueuedCall(self->world, (void*)SpawnObjectPoolCopies, self, 0, 0);
}

void UnregisterObjectPool(ObjectPool* self)
{
    UnregisterObject(self);
    ClearObjectPoolChoice(self);
}

void* GetObjectPoolShare(ObjectPool* self)
{
    if (self->sub == 0) {
        Sub8C* p = (Sub8C*)AllocateZeroedFrontMemory(0x20);
        self->sub = p;
        *(ObjectPool**)p = self;
    }
    return self->sub;
}

void AddObjectPoolEntry(ObjectPool* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->items == 0) {
        self->items = (ObjectPoolEntry*)AllocateZeroedFrontMemory(0x50);
    }
    ObjectPoolEntry* e = &self->items[self->count++];
    e->id = a1;
    e->count = a2;
    e->flags = ((((e->flags & -2) | (a3 & 1)) & -3) | ((a4 & 1) << 1));
}

void SpawnObjectPoolCopies(ObjectPool* self)
{
    s32 i;
    if (self->sub != 0) {
        if (self->sub->f4 != 0) {
            self->sub->qC = (Quad16*)AllocateFrontMemory(self->count << 5);
        }
    }
    for (i = 0; i < self->count; i++) {
        ObjectPoolEntry* e = &self->items[i];
        PlacedObject* obj = FindFirstObjectById(self->world, 4, e->id, self);
        s32 n;
        s32 cnt;
        if (obj == 0) {
            e->count = 0;
            continue;
        }
        if (self->sub != 0 && self->sub->f4 != 0) {
            s32 x = self->sub->f8;
            if (x == 1) goto c1;
            if (x < 2) {
                if (x == 0) goto c0;
            } else if (x == 2) {
                n = 0;
                cnt = 0;
            }
            goto done;
        c0:
            self->sub->f8 = 1;
            SetListLinkOffset((u8*)self->sub + 0x14, 0x18);
        c1: {
                s32 r = CountListItems((u8*)self->sub + 0x14);
                s32 lim = r + 1;
                s32 m = e->count;
                s32 q = lim;
                if (q < m) q = m;
                n = q;
                cnt = n - r - 1;
            }
        } else {
            n = e->count;
            cnt = n - 1;
        }
    done:
        if (n != 0) e->objects = (void**)AllocateFrontMemory(n << 2);
        e->objects[e->total++] = obj;
        if (cnt > 0) {
            s32 k = cnt;
            do {
                PlacedObject* o2 = CreateObjectCopy(obj, obj->world, obj->parent);
                e->objects[e->total++] = o2;
                if (o2->desc->m0F != 0) o2->desc->m0F(o2);
                o2->desc->m10(o2);
                o2->desc->m15(o2, 0);
                o2->desc->m03(o2);
            } while (--k);
        }
        if (obj->desc->m0F != 0) obj->desc->m0F(obj);
        obj->desc->m10(obj);
        obj->desc->m15(obj, 0);
        obj->desc->m03(obj);
        if (self->sub != 0 && self->sub->f4 != 0) {
            Quad16* d = self->sub->qC + (i << 1);
            d[0] = *(Quad16*)&obj->v190;
            d[1] = *(Quad16*)&obj->v1D0;
        }
    }
}

void CopyObjectPool(ObjectPool* self, ObjectPool* other)
{
    CopyObjectData(self, other);
    if (self->sub != 0 && self->sub->f4 != 0) {
        if (other->sub->f8 != 0) {
            self->sub = 0;
        } else {
            other->sub->f8 = 1;
            SetListLinkOffset((u8*)other->sub + 0x14, 0x18);
            self->sub = 0;
        }
        GetObjectPoolShare(self);
        self->sub->f4 = 1;
        self->sub->f8 = 2;
        self->sub->f14 = other;
        AppendToList((u8*)other->sub + 0x14, self->sub);
    } else {
        self->items = (ObjectPoolEntry*)CopyToFrontMemory(other->count * 0x14, other->items);
    }
}

void StartObjectPool(ObjectPool* self)
{
    StartObject(self);
    if (self->f168 != 0) {
        return;
    }
    self->f168 = 1;
    if (self->id4C != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id4C, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 0x7E) != 0) {
                self->f60 = p;
            } else if (IsObjectOfKind(p, 0x73) != 0) {
                self->f64 = p;
            } else if (IsObjectOfKind(p, 2) != 0) {
                self->f68 = p;
            }
        }
    }
    if (self->id50 != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id50, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 2) != 0) {
                self->fE0 = p;
            } else if (IsObjectOfKind(p, 0x75) != 0) {
                self->fE4 = p;
            }
        }
    }
    if (self->id54 != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id54, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 0x73) != 0) {
                self->f160 = p;
            } else if (IsObjectOfKind(p, 2) != 0) {
                self->f164 = p;
            }
        }
    }
    if (self->id58 != -1) {
        self->f5C = FindFirstObjectByIdMode4(self->world, self->id58, self);
    }
}

void ClearObjectPoolChoiceIfFlag(ObjectPool* self, s32 flag)
{
    if (flag) {
        ClearObjectPoolChoice(self);
    }
}

ObjectPoolEntry* FindObjectPoolEntry(ObjectPool* self, s32 key)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (self->items[i].id == key) break;
    }
    if (i < self->count) return &self->items[i];
    return 0;
}

void EnableObjectPoolEntry(ObjectPool* table, s32 key)
{
    ObjectPoolEntry* e = FindObjectPoolEntry(table, key);
    if (e) {
        e->flags |= 2;
    }
}

void DisableObjectPoolEntry(ObjectPool* table, s32 key)
{
    ObjectPoolEntry* e = FindObjectPoolEntry(table, key);
    if (e != 0) {
        e->flags &= ~2;
    }
}

void SetObjectPoolEntryCount(ObjectPool* table, s32 key, s32 value)
{
    ObjectPoolEntry* e = FindObjectPoolEntry(table, key);
    if (e != 0) {
        if (value >= e->total) {
            value = e->total;
        }
        e->count = value;
    }
}

s32 IsObjectInPool(ObjectPool* list, BaseObject* query) { for(s32 i=0;i<list->count;i++){ ObjectPoolEntry* row=&list->items[i]; if(row->count<=0) continue; void** items=row->objects; if(*(s32*)((u8*)items[0]+8) != query->id) continue; for(s32 j=0;j<row->count;j++) if(query==items[j]) return 1; } return 0; }

s32 IsObjectPoolItemFree(ObjectPool* self, PoolCandidate* key)
{
    Sub8C* group = self->sub;

    if (group != 0 && group->f4 != 0) {
        List01* list;
        ObjectPool* skip;
        ListFrame it;
        u8* obj;

        switch (group->f8) {
        case 1:
            list = (List01*)&group->f14;
            skip = 0;
            break;
        case 2: {
            ObjectPool* e = (ObjectPool*)group->f14;
            skip = self;
            if (e->f48 == (s32)key) {
                return 0;
            }
            list = (List01*)&e->sub->f14;
            break;
        }
        }
        ListWalkBegin::Of(&it, list);
        for (obj = ListWalkNext::Of(&it); obj != 0; obj = ListWalkNext::Of(&it)) {
            ObjectPool* e = *(ObjectPool**)obj;
            if (e != skip && e->f48 == (s32)key) {
                ListWalkEnd::Of(&it);
                return 0;
            }
        }
        ListWalkEnd::Of(&it);
    }
    if (IsObjectAttached(key) != 0) {
        return 0;
    }
    if (IsObjectOfKind(key, 0x3B) != 0 && key->f678 == 0) {
        return 0;
    }
    if (IsObjectOfKind(key, 0x20) != 0 && key->f680 != 0) {
        return 0;
    }
    return 1;
}

void AdvanceObjectPoolEntry(ObjectPool* self)
{
    s32 i;
    s32 pos;
    s32 k;

    if (self->count == 0) {
        return;
    }
    i = 1;
    pos = (self->f44 + 1) % self->count;
    if (!(i < self->count)) {
        return;
    }
    do {
        ObjectPoolEntry* rec = &self->items[pos];
        if ((rec->flags & 2) != 0) {
            for (k = 0; k < rec->count; k++) {
                if (IsObjectPoolItemFree(self, (s32)rec->objects[k]) != 0) {
                    goto found;
                }
            }
        }
        pos = (pos + 1) % self->count;
        i++;
    } while (i < self->count);
found:
    if (i < self->count) {
        self->f44 = pos;
    }
}

void ChooseObjectPoolItem(ObjectPool* self)
{
    s32 s5 = 0;
    s32 s4 = 0;
    if (self->count != 0) {
        if (self->f40 == 0) {
            AdvanceObjectPoolEntry(self);
        }
        ObjectPoolEntry* rec = &self->items[self->f44];

        if (rec->flags & 2) {
            s32 i = 0;
            if (rec->count > 0) {
                do {
                    if (IsObjectPoolItemFree(self, (s32)rec->objects[i]) != 0) {
                        s4 = (s32)rec->objects[i];
                        if (self->sub != 0 && self->sub->f4 != 0) {
                            s5 = self->sub->fC + (self->f44 << 5);
                        }
                        if (rec->flags & 1) {
                        } else {
                            rec->count = rec->count - 1;
                            s32* p = (s32*)((u8*)0 + i * 4 + (u32)rec->objects);
                            MoveMemory(p, p + 1, (rec->count - i) * 4);
                        }
                        break;
                    }
                    i++;
                } while (i < rec->count);
            }
        }
    }
    self->f48 = s4;
    if (self->sub != 0 && self->sub->f4 != 0) {
        self->sub->f10 = s5;
    }
}

s32 HasObjectPoolChoice(ObjectPool* self)
{
    if (self->f48 != 0) {
        return 1;
    }
    ChooseObjectPoolItem(self);
    return self->f48 != 0;
}

#include "placed_object.h"
#include "object_event.h"
#include "object_message.h"
#include "hit_target.h"
#include "value_range.h"
extern const Vec02 g_unitXVector;
struct Released_1A8C90;
typedef void (*ReleasedFn_1A8C90)(Released_1A8C90* self, void* a, void* b);
struct ReleasedDesc_1A8C90 {
    u8 pad00[8];
    u32 flags;                      // 0x08
    u8 pad0C[0x18 - 0x0C];
    void (*m18)(Released_1A8C90* self);                 // 0x18: into the parent's list
    u8 pad1C[0x84 - 0x1C];
    void (*m84)(Released_1A8C90* self, Vec02* pos);     // 0x84: the position
    void (*m88)(Released_1A8C90* self, void* rot);      // 0x88: the orientation
    void (*m8C)(Released_1A8C90* self, Vec02* v);
    void (*m90)(Released_1A8C90* self, Vec02* vel);     // 0x90: the velocity
    void (*m94)(Released_1A8C90* self, Vec02* spin);    // 0x94: the spin
    u8 pad98[0x130 - 0x98];
    void (*m130)(Released_1A8C90* self, void* frame, void* at);  // 0x130
};
struct ReleasedTrack_1A8C90 { u8 pad00[0x60]; void* frame; u8 pad64[0xB0 - 0x64]; u32 flags; };
struct Released_1A8C90 {
    ReleasedDesc_1A8C90* desc;
    u8 pad004[0x190 - 0x004];
    Vec02 v190;                     // 0x190
    u8 pad1A0[0x1D0 - 0x1A0];
    Vec02 v1D0;                     // 0x1D0
    u8 pad1E0[0x224 - 0x1E0];
    ReleasedTrack_1A8C90* track;    // 0x224
    u8 pad228[0x554 - 0x228];
    f32 f554;                       // 0x554
    u8 pad558[0x690 - 0x558];
    f32 speed;                      // 0x690
    u8 pad694[0x6E4 - 0x694];
    void* f6E4;                     // 0x6E4
    u8 pad6E8[0xC3C - 0x6E8];
    s32 fC3C;                       // 0xC3C
};
struct ReleaseHeading_1A8C90 { u32 flags; u8 pad04[0xC - 4]; f32 speed; };
struct PoolOwner_1A8C90 { u8 pad00[8]; u32 flags; };
struct PoolParent_1A8C90 { u8 pad00[0x50]; PoolOwner_1A8C90** root; };
struct PoolView_1A8C90 {
    u8 pad000[0x18];
    PoolParent_1A8C90* parent;      // 0x18
    u8 pad01C[0x3C - 0x1C];
    Sub8C* sub;                     // 0x3C
    u8 pad040[0x48 - 0x40];
    Released_1A8C90* chosen;        // 0x48
    u8 pad04C[0x5C - 0x4C];
    void* frame;                    // 0x5C
    u8 pad060[0x68 - 0x60];
    void* mover;                    // 0x68
    u8 pad06C[0xB0 - 0x6C];
    Vec02 velocity;                 // 0xB0
    Vec02 spin;                     // 0xC0
    ValueRange spinRange;           // 0xD0
    f32 life;                       // 0xD8
    u8 padDC[0xE0 - 0xDC];
    void* targetFrame;              // 0xE0
    PlacedObject* target;           // 0xE4
    u8 padE8[0xF0 - 0xE8];
    Vec02 at;                       // 0xF0
    s32 aimMode;                    // 0x100
    u8 pad104[0x110 - 0x104];
    TimePolynomial poly;            // 0x110
    u8 pad11C[0x120 - 0x11C];
    ValueRange range;               // 0x120
    u8 pad128[0x150 - 0x128];
    ReleaseHeading_1A8C90 heading;  // 0x150
};

void GetPlacementRecordTransform(void* self, Vec02* a1, void* a2, void* a3);
void func_001A95D0(void* self, Vec02* target, Vec02* out, void* to);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, Vec02* spin, s32 b, s32 c);
void GetPlacementRecordAngle(void* self, f32* out, void* x);
void func_001A9868(void* self, f32* out, void* x);
void BuildYawPitchMatrix(f32 yaw, f32 pitch, Mat02* out);
f32 WrapAngle(f32 a);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);
void ForwardBallisticLaunchVelocity(f32 t, Vec02* from, Vec02* to, Vec02* out, void* obj);
void func_001EE090(f32 t, Vec02* from, Vec02* to, Vec02* out, void* obj);
void ComputeBallisticLaunchVelocity(f32 t, Vec02* from, Vec02* to, Vec02* out, void* obj);
f32 RandomFloatInRange(f32 a, f32 b);
void ChangeAgentState(void* node, s32 kind, s32 flag);
void TriggerScriptEvent(void* self, s32 a, s32 b, void* c);

// v made a unit vector, or the fallback when shorter than 1e-4; its length.
static inline u128 NormalizeVectorOr(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Q(v) = Vu0::DivX(Vu0::Q(v), len);
    }
    return len;
}

s32 func_001A8C90(PoolView_1A8C90* self, s32 aim)
{
    Vec02 pos;
    Vec02 to;
    Vec02 dir;
    Mat02 rot;
    Released_1A8C90* obj = self->chosen;
    if (obj == 0) {
        ChooseObjectPoolItem((ObjectPool*)self);
        if (self->chosen == 0) {
            return 0;
        }
        obj = self->chosen;
    }
    GetPlacementRecordTransform((u8*)self + 0x60, &pos, &rot, self->frame);
    func_001A95D0((u8*)self + 0xE0, &pos, &to, self->frame);
    Vu0::Q(dir) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
    u128 len = NormalizeVectorOr(dir, g_unitXVector);
    f32 reach = self->range.Clamp(self->poly.Eval(Vu0::ToFloatMoved(len)));
    Vu0::Q(to) = Vu0::Add(Vu0::Q(pos), Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(reach)));
    if (self->parent != 0 && self->parent->root != 0 && ((*self->parent->root)->flags & 2) && IsObjectOfKind(obj, 0x3C)) {
        obj->f6E4 = self->parent->root;
    }
    if (self->frame != 0) {
        if (obj->track == 0) {
            obj->track = (ReleasedTrack_1A8C90*)AllocateZeroedFrontMemory(0xC0);
        }
        obj->track->flags |= 0xC;
        obj->track->frame = self->frame;
    }
    obj->desc->m18(obj);
    SetColliderAnchors(obj, 0, 0, 0, 0);
    obj->desc->m84(obj, &pos);
    obj->desc->m88(obj, &rot);
    if (self->sub != 0 && self->sub->f4 != 0) {
        Vec02* q = (Vec02*)self->sub->f10;
        obj->v190 = q[0];
        obj->v1D0 = q[1];
    }
    if (self->mover != 0) {
        Vec02 vel;
        Vec02 spin;
        ComputeObjectMotionInFrame(self->mover, 0, (u8*)self->mover + 0x140, &vel, &spin, 0, 0);
        obj->desc->m90(obj, &vel);
        obj->desc->m94(obj, &spin);
    } else {
        Vec02* vel = vel;
        if (aim != 0) {
            ReleaseHeading_1A8C90* h = &self->heading;
            if (IsObjectOfKind(obj, 0x3E) || IsObjectOfKind(obj, 0x3D)) {
                Vec02 delta;
                Vec02 scale;
                Mat02 m;
                f32 yaw;
                f32 pitch;
                Vu0::Q(delta) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
                if (h->flags & 2) {
                    GetPlacementRecordAngle(h, &yaw, self->frame);
                } else {
                    yaw = ArctangentOfRatio(delta.y, delta.x);
                }
                if (h->flags & 1) {
                    func_001A9868(h, &pitch, self->frame);
                } else {
                    pitch = ArctangentOfRatio(delta.z, Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(delta), Vu0::Q(delta)))));
                }
                f32 speed;
                if (h->flags & 4) {
                    speed = h->speed;
                } else {
                    speed = obj->speed;
                }
                BuildYawPitchMatrix(yaw, pitch, &m);
                Vu0::Q(scale) = Vu0::FromFloat(speed);
                Vu0::Q(self->velocity) = Vu0::MulX(Vu0::Q(m.r[0]), Vu0::Q(scale));
            } else {
                Vec02 delta;
                Vu0::Q(delta) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
                if (h->flags & 2) {
                    f32 yaw;
                    f32 a = ArctangentOfRatio(delta.y, delta.x);
                    GetPlacementRecordAngle(h, &yaw, self->frame);
                    a = WrapAngle(a);
                    AreFloatsNearlyEqual(a, WrapAngle(yaw), 0.0001f);
                }
                if (self->heading.flags & 1) {
                    f32 t;
                    func_001A9868(h, &t, self->frame);
                    ForwardBallisticLaunchVelocity(t, &pos, &to, &self->velocity, obj);
                } else if (self->heading.flags & 4) {
                    func_001EE090(h->speed, &pos, &to, &self->velocity, obj);
                } else {
                    ComputeBallisticLaunchVelocity(0.5f, &pos, &to, &self->velocity, obj);
                }
            }
        }
        obj->desc->m90(obj, &self->velocity);
        if (0.0f < self->spinRange.hi) {
            Vec02 spin;
            f32 m = self->spinRange.Random();
            spin.x = RandomFloatInRange(-1.0f, 1.0f);
            spin.y = RandomFloatInRange(-1.0f, 1.0f);
            spin.z = RandomFloatInRange(-1.0f, 1.0f);
            Vu0::Set(spin, Vu0::MulX(Vu0::NormalizeOr(Vu0::Q(spin), Vu0::Q(g_unitXVector)), Vu0::Scalar(m)));
            obj->desc->m94(obj, &spin);
        } else {
            obj->desc->m94(obj, &self->spin);
        }
    }
    if (0.0f < self->life && IsObjectOfKind(obj, 0x3B)) {
        obj->f554 = g_gameTime + self->life;
    }
    if (IsObjectOfKind(obj, 0x3C)) {
        switch (self->aimMode) {
        case 0:
        case 1:
        default:
            obj->desc->m130(obj, 0, &to);
            break;
        case 2: {
            void* frame = self->targetFrame;
            void* at;
            if (frame != 0 || self->target == 0) {
                at = &self->at;
            } else {
                frame = self->target->parent;
                at = &self->target->link40;
            }
            obj->desc->m130(obj, frame, at);
            break;
        }
        }
    }
    if (IsObjectOfKind(obj, 8)) {
        ChangeAgentState(obj, 0x10, 0);
        if (IsObjectOfKind(obj, 0xA)) {
            obj->fC3C = 1;
        }
    }
    Released_1A8C90** held = &obj;
    TriggerScriptEvent(self, 0xD, 1, &held);
    ClearObjectPoolChoice(self);
    return 1;
}

void ClearObjectPoolChoice(ObjectPool* p) { p->f48 = 0; if (p->sub != 0 && p->sub->f4 != 0) p->sub->f10 = 0; }

void ResetPlacementRecord(u8* self)
{
    u8* p = self + 0x60;
    FillMemory(p, 0, 0x80);
    *(Mat02*)(p + 0x20) = g_identityMatrix;
}

void ResetObjectPoolReleaseRecord(ObjectPool* self)
{
    FillMemory((u8*)self + 0xE0, 0, 0x70);
    V8C* t = &self->v110;
    t->a = 0;
    t->b = 1.0f;
    t->c = 0;
    self->f124 = 20000.0f;
    self->f120 = 0;
}

void ClearObjectPoolHeadingRecord(u8* self)
{
    FillMemory(self + 0x150, 0, 0x18);
}

void GetPlacementRecordTransform(FrameSource* self, Vec02* a1, Vec02* a2, void* a3)
{
    if (self->f0 != 0) {
        ConvertPositionToWorld(self->f0, a1);
        a2[0] = self->rot[0];
        a2[1] = self->rot[1];
        a2[2] = self->rot[2];
    } else if (self->f4 != 0) {
        GetObjectWorldPosition(self->f4, a1);
        GetObjectWorldRotation(self->f4, a2);
    } else {
        if (self->f8 != 0) {
            a1[0] = self->f8->v140;
            PlacedObject* in = self->f8;
            a2[0] = in->m110.r[0];
            a2[1] = in->m110.r[1];
            a2[2] = in->m110.r[2];
        } else {
            a1[0] = self->pos;
            a2[0] = self->rot[0];
            a2[1] = self->rot[1];
            a2[2] = self->rot[2];
        }
    }
    if (a3 != 0) {
        TransformPointBetweenFrames(0, a3, a1, a1);
        TransformRotationBetweenFrames(0, a3, a2, a2);
    }
}

#include "placed_object.h"

// A point that follows an object's frame, or a frame of its own: the spring that eases the follow
// is a quadratic of the distance (func_001A95D0).
struct FrameFollower {
    PlacedObject* frameObject;      // 0x00
    u8* anchor;                     // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 pos;                      // 0x10
    s32 mode;                       // 0x20
    u8 pad24[0x50 - 0x24];
    f32 poly[3];                    // 0x50
    u8 pad5C[0x60 - 0x5C];
    f32 lo;                         // 0x60
    f32 hi;                         // 0x64
};

s32 ComputeObjectFrameAtTime(void* object, s32 b, f32 t, Vec02* pos, Mat02* rot, s32 e, s32 f);

void func_001A95D0(FrameFollower* self, Vec02* target, Vec02* out, void* to)
{
    Vec02 here;
    Mat02 rot;
    Vec02 pos2;
    Mat02 rot2;
    void* frame;
    Vec02* local;
    if (self->frameObject != 0 || self->anchor == 0) {
        frame = self->frameObject;
        local = &self->pos;
    } else {
        frame = *(void**)(self->anchor + 0x18);
        local = (Vec02*)(self->anchor + 0x40);
    }
    switch (self->mode) {
    case 0:
        TransformPointBetweenFrames(frame, to, local, out);
        return;
    case 1:
    case 2: {
        TransformPointBetweenFrames(frame, 0, local, &here);
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(here), Vu0::Q(*target))));
        f32* p = self->poly;
        f32 v = self->poly[0] + len * (p[1] + len * p[2]);
        f32 lo = self->lo;
        f32 hi = self->hi;
        f32 t;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = hi;
        } else {
            t = v;
        }
        ComputeObjectFrameAtTime(frame, 0, t, &here, &rot, 0, 0);
        Vu0::Q(*out) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(*local)), Vu0::Q(here));
        if (to != 0) {
            ComputeObjectFrameAtTime(to, 0, t, &pos2, &rot2, 0, 0);
            Vu0::Q(*out) = Vu0::RotateTransposed(rot2, Vu0::Sub(Vu0::Q(*out), Vu0::Q(pos2)));
        }
        break;
    }
    }
}

void GetPlacementRecordAngle(u8* self, f32* out, int x)
{
    f32 v[12];
    if (*(void**)(self + 0x10) != 0) {
        GetObjectWorldRotation(*(void**)(self + 0x10), v);
        TransformRotationBetweenFrames(0, x, v, v);
        *out = ArctangentOfRatio(v[1], v[0]);
    } else if (*(u8**)(self + 0x14) != 0) {
        TransformRotationBetweenFrames(0, x, *(u8**)(self + 0x14) + 0x110, v);
        *out = ArctangentOfRatio(v[1], v[0]);
    } else {
        *out = *(f32*)(self + 0x8);
    }
}

void func_001A9868(u8* self, f32* out, int x)
{
    f32 v[12] __attribute__((aligned(16)));
    if (*(void**)(self + 0x10) != 0) {
        GetObjectWorldRotation(*(void**)(self + 0x10), v);
        TransformRotationBetweenFrames(0, x, v, v);
        u128 r = Vu0::Q(*(u128*)v);
        *out = ArctangentOfRatio(v[2], Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(r, r))));
    } else {
        *out = *(f32*)(self + 0x4);
    }
}

void StartGaugeBarAgent(GaugeBarAgent* self)
{
    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
}

s32 IsGaugeBarAgentFree(GaugeBarAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0)
        return 0;
    return self->fC24;
}

void UpdateGaugeBarAgentGoal(GaugeBarAgent* self)
{
    UpdateAgentGoal(self);
    if (self->f724 == 0x10) {
        void* r = ((VFn_1A9960*)self->desc)[102](self);
        if (r != 0)
            func_001C8418(self, (u8*)r + 0x140);
    }
}

void UpdateGaugeBarAgentState(GaugeBarAgent* self)
{
    UpdateAgentState(self);
    if (self->f724 == 0x10)
        FaceAgentTowardGoalPoint(self);
}

void EnterGaugeBarAgentState(GaugeBarAgent* self)
{
    EnterAgentState(self);
    if (self->f724 == 0xB) {
        MarkLevelDone(4);
        StartMemoryCardSave(g_memoryCard);
    }
}

void UpdateGaugeBarAgent(GaugeBarAgent* self)
{
    u8* s = (u8*)self;
    UpdateAgent(self);
    void* p = *(void**)(s + 0xC20);
    if (p != 0) {
        if (*(f32*)((u8*)p + 0x18) == 0.0f) {
            StopAnimationPlayer(p);
            *(void**)(s + 0xC20) = 0;
        }
    }
}

void UpdateGaugeBarAgentVisibility(void)
{
    if (AreMenusAndFadeClear()) {
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    } else {
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
    }
}

#include "object_event.h"
#include "object_message.h"

typedef void (*VFn_1A9AE8)(void* self, SlotMessage* msg);
void DecrementGaugeCount(void* element);
void ReplaceAnimationPlayer(s32 a, void* b, s32 c, void* d, f32 e, f32 f);
s32 HandleAgentObjectEvent(GaugeBarAgent* self, ObjectEvent* ev);
extern Player* g_player;
extern const Vec02 g_unitXVector;

s32 func_001A9AE8(GaugeBarAgent* self, ObjectEvent* ev)
{
    if (self->fC14 != 0 && (ev->eventFlags & 0x20) != 0) {
        self->fC10 = self->fC10 + 1;
        DecrementGaugeCount(&g_gaugeBarElement);
        if (*(void**)((u8*)self + 0xB00) != 0) {
            SlotMessage msg;
            msg.kind = 6;
            msg.vb = ev->pos;
            Vu0::Set(msg.va, Vu0::NormalizeOrMoved(Vu0::Q(ev->v30), Vu0::Q(g_unitXVector)));
            void* o = *(void**)((u8*)self + 0xB00);
            ((VFn_1A9AE8*)(*(void***)o))[0x7C / 4](o, &msg);
        }
        s32 which;
        if ((ev->extraFlags & 2) != 0) {
            if (g_player == 0 || g_player->f223C == 4 || g_player->f223C == 6)
                which = self->fC14;
            else
                which = self->fC18;
        } else if ((ev->extraFlags & 4) != 0) {
            which = self->fC1C;
        } else {
            which = self->fC14;
        }
        ReplaceAnimationPlayer(which, self, 1, (u8*)self + 0xC20, 0.0f, 1.0f);
        ev->eventFlags &= ~0x20;
    }
    return HandleAgentObjectEvent(self, ev);
}

void SetGaugeBarAgentValues(GaugeBarAgent* self, s32 a, s32 b, s32 c)
{
    self->fC14 = a;
    self->fC18 = b;
    self->fC1C = c;
}

void InstallScreenElements()
{
    D_0026C6C8.vt = (const T217D_Vt*)D_00217E30;
    D_0026C948.vt = (const T217D_Vt*)D_00217E80;
    D_0026CBC8.vt = (const T217D_Vt*)D_00217ED0;
    D_0026CE48.vt = (const T217D_Vt*)D_00217F20;
    D_0026D0C8.vt = (const T217D_Vt*)D_00217F70;
    g_gaugeAmountCaption.vt = (const T217D_Vt*)D_00217FC0;
    D_0026D5C8.vt = (const T217D_Vt*)D_002180B0;
    D_0026D848.vt = (const T217D_Vt*)D_00218010;
    D_0026DAC8.vt = (const T217D_Vt*)D_00218060;
    D_0026DD48.vt = (const T217D_Vt*)D_00218100;
    D_0026DFC8.vt = (const T217D_Vt*)D_00218150;
    g_gaugeBarElement.vt = (const T217D_Vt*)D_002182E0;
    D_0026E4E0.vt = (const T217D_Vt*)D_002181A0;
    g_timerElement.vt = (const T217D_Vt*)D_00218510;
    g_timerCaption.vt = (const T217D_Vt*)D_00221380;
    g_buttonHintElement.vt = (const T217D_Vt*)D_00218330;
    D_0026EED0.vt = (const T217D_Vt*)D_00218380;
    D_0026F138.vt = (const T217D_Vt*)D_002183D0;
    D_0026F5A0.vt = (const T217D_Vt*)D_00218420;
    g_mapScreenList.vt = (const T217D_Vt*)D_002210F0;
    D_0026FA90.vt = (const T217D_Vt*)D_002212E0;
    D_0026FD00.vt = (const T217D_Vt*)D_00221330;
    g_pauseMenuElement.vt = (const T217D_Vt*)D_002186D0;
    g_typedTextCaptionBox.vt = (const T217D_Vt*)D_0021A440;
    D_00270650.vt = (const T217D_Vt*)D_00220BF0;
    D_002708E0.vt = (const T217D_Vt*)D_0021A3F0;
    D_00271558.vt = (const T217D_Vt*)D_0021A3F0;
    D_00272430.vt = (const T217D_Vt*)D_00218240;
    D_002726B0.vt = (const T217D_Vt*)D_00218290;
    D_00272930.vt = (const T217D_Vt*)D_00218470;
    D_00272B98.vt = (const T217D_Vt*)D_002184C0;
    D_002721D0.vt = (const T217D_Vt*)D_00218560;
    g_stackedCaptionGroup.vt = (const T217D_Vt*)D_00218720;
    D_002739F0.vt = (const T217D_Vt*)D_002185B0;
    D_00273C50.vt = (const T217D_Vt*)D_002185B0;
    D_00273EB0.vt = (const T217D_Vt*)D_00218600;
    D_00274118.vt = (const T217D_Vt*)D_002181F0;
    for (s32 i = 0x24; i >= 0; i--) {
        ((ScreenElement**)g_screenElements)[i]->vt->m00(((ScreenElement**)g_screenElements)[i], i);
    }
    ResetScreenFade(g_screenFade);
}

void InitScreenElements(void)
{
    ScreenElement** base = (ScreenElement**)g_screenElements;
    ScreenElement** p = base + 36;
    s32 i = 0x24;
    do {
        i--;
        (*p)->vt->m01(*p);
        p--;
    } while (i >= 0);
}

void UpdateScreenElements(void)
{
    ScreenElement** slots = (ScreenElement**)g_screenElements;
    for (s32 i = 36; i >= 0; i--) {
        ScreenElement* o = slots[i];
        o->vt->m02(o);
    }
    u8* g = g_screenFade;
    void* b;
    if (*(s32*)g_padRouting & 4) {
        b = g_padRecord;
    } else {
        b = g_blankPadRecord;
    }
    UpdateScreenFade(g, b);
}

void HideScreenElements(void)
{
    ScreenElement** base = (ScreenElement**)g_screenElements;
    ScreenElement** p = base + 36;
    s32 i = 0x24;
    do {
        ScreenElement* o = *p;
        p--;
        o->vt->m16(o, 0);
        i--;
    } while (i >= 0);
}

void ResetScreenElements(void)
{
    ScreenElement** p = (ScreenElement**)g_screenElements;
    s32 n = 0x24;
    do {
        n--;
        ScreenElement* o = *p;
        o->vt->m05(o);
        p++;
    } while (n >= 0);
}

void QueueEachScreenElementDraw(void)
{
    s32 n = 0x24;
    ScreenElement** p = (ScreenElement**)g_screenElements;
    do {
        ScreenElement* o = *p;
        p++;
        n--;
        if (o->mode != 0) {
            void (*fn)(ScreenElement*) = o->vt->m10;
            if (fn != 0) {
                fn(o);
            }
        }
    } while (n >= 0);
}

void DrawScreenElements(void)
{
    s32 i;
    for (i = 0; i < 0x25; i++) {
        ScreenElement* p = ((ScreenElement**)g_screenElements)[i];
        if (p->mode != 0) {
            p->vt->m09(p);
        }
    }
    DrawScreenFade(g_screenFade);
    DrawCyclingGlyphElement((u8*)&D_00273EB0);
}

void InitScreenElement(ScreenElement* self, s32 index)
{
    self->place = (T217D_Place*)((u8*)&g_elementPlaces + index * 20);
    self->outTime = 0.25f;
    self->inTime = 0.25f;
    self->clock = (f32*)g_elapsedTime;
    self->index = index;
    SetScreenElementSize(self, self->w, self->h);
    self->x = self->hiddenX;
    self->y = self->hiddenY;
}
