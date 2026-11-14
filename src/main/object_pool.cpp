// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1A7FE8 to 0x1AA268, built whole (config/us/files.tsv): the object pool
// (class 0x8C, from its init method func_001A7FE8), the agent of class 0x0D, and the set-up,
// update and drawing of the 37 screen elements (func_001A9C68 ... func_001AA1F0), whose objects
// it defines. Its .rodata is the FLT_MAX literal of func_001A7FE8 (0x24CBC4); its .data
// (0x26C3E0 to 0x274398) is the per-element placement table D_0026C3E0, then the 37 screen
// objects, uninitialised (zero, filled at run time by func_001A9C68), which GCC puts at the end
// of the file's .data in definition order. Its name is ours, after its first and largest family,
// the object pool.
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
#include "object_finder.h"
#include "functions/agent.h"
#include "functions/arc_element.h"
#include "functions/collider.h"
#include "functions/commentary_best_time.h"
#include "functions/game_progress.h"
#include "functions/item_column.h"
#include "functions/matrix.h"
#include "functions/memory_card.h"
#include "functions/mode_walker.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/screen_element.h"
#include "functions/selection_menus.h"
#include "functions/text_format.h"
#include "functions/text_panel.h"
#include "functions/warp_menu.h"
struct BaseObject;
struct Vec02;

struct BaseObject;

struct BaseObject;
struct Mat02;

struct BaseObject;
struct Mat02;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct MemoryCard;

// The font object's calls.
Font* GetFontById(s32 k);
void PushFontScale(Font* font, f32 x, f32 y);
f32 MeasureFontString(Font* self, const char* s);
struct Font;
struct StringLayout;
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);
void PopFontScale(Font* font);
void* InitTextReader(TextReader* self, char* text, Font* font);
struct Layout_137228;
struct PacketWriter;
struct TextReader;
struct Vec4U;
void DrawAlignedText(TextReader* self, Layout_137228* p, Vec4U* clip, PacketWriter* s);

void UnregisterObject(BaseObject* self);
void ClearObjectPoolChoice(ObjectPool* p);


void GetObjectWorldRotation(void* a, f32* out);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);




extern f32 g_gameTime;
extern f32 g_frameDt;


extern s32 g_defaultFont;

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);



void SetWorldActiveFollower(World* self, void* v);


s32 IsPadSelectFlagHeld(World* self);


typedef void* (*VFn_1A9960)(void* self);




extern u8 g_memoryCard[];



extern T217D_2E0 g_gaugeBarElement;




extern ElementPlaceTable g_elementPlaces;
extern u8 g_elapsedTime[];


void* AllocateZeroedFrontMemory(s32 n);


void StartObject(BaseObject* self);


extern "C" void* FillMemory(void* p, s32 value, s32 size);


extern "C" void* FillMemory(void* p, s32 value, s32 size);


void ClearObjectPoolChoice(ObjectPool* p);



ObjectPoolEntry* FindObjectPoolEntry(ObjectPool* table, s32 key);







// Where func_001A94C0 takes a position and a matrix from: an object's world frame (f0 or f4), a
// placed object's m110 and v140 (f8), or its own copy of both.
struct FrameSource {
    void* positionObject;
    void* frameObject;
    PlacedObject* placedObject;
    u8 pad0[4];
    Vec02 pos;
    Vec02 rot[3];
};

void GetObjectWorldRotation(BaseObject* self, Mat02* out);


extern u8 g_elapsedTime[];

void CopyObjectData(BaseObject* self, BaseObject* src);
void* GetObjectPoolShare(void* self);
u8* CopyToFrontMemory(s32 size, void* src);









extern void* const g_screenElements[];
extern u8 g_padRouting[];
extern u8 g_padRecord[];
extern u8 g_blankPadRecord[];
extern u8 g_screenFade[];

struct ScreenFade;


extern void* const g_screenElements[];


// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();

extern const Fn_Table D_00217E30[];
extern const Fn_Table D_00217E80[];
extern const Fn_Table D_00217ED0[];
extern const Fn_Table D_00217F20[];
extern const Fn_Table D_00217F70[];
extern const Fn_Table g_gaugeAmountCaptionMethods[];
extern const Fn_Table D_00218010[];
extern const Fn_Table D_00218060[];
extern const Fn_Table D_002180B0[];
extern const Fn_Table D_00218100[];
extern const Fn_Table D_00218150[];
extern const Fn_Table D_002181A0[];
extern const Fn_Table D_002181F0[];
extern const Fn_Table D_00218240[];
extern const Fn_Table D_00218290[];
extern const Fn_Table g_gaugeBarElementMethods[];
extern const Fn_Table D_00218330[];
extern const Fn_Table g_pointerTextCaptionMethods[];
extern const Fn_Table g_copiedTextCaptionMethods[];
extern const Fn_Table g_hintGlyphElementMethods[];
extern const Fn_Table g_titleElementMethods[];
extern const Fn_Table g_promptElementMethods[];
extern const Fn_Table g_timerElementMethods[];
extern const Fn_Table g_letterboxElementMethods[];
extern const Fn_Table g_letterGlyphElementMethods[];
extern const Fn_Table g_cyclingGlyphElementMethods[];
extern const Fn_Table g_pauseMenuElementMethods[];
extern const Fn_Table g_stackedCaptionGroupMethods[];
extern const Fn_Table g_arcElementMethods[];
extern const Fn_Table g_typedTextCaptionBoxMethods[];
extern const Fn_Table g_spinningSpriteElementMethods[];
extern const Fn_Table g_mapScreenListMethods[];
extern const Fn_Table g_selectionCaptionMethods[];
extern const Fn_Table g_gridSelectorMethods[];
extern const Fn_Table g_timerCaptionMethods[];
extern u8 g_screenFade[];



extern s8 g_fontEscapeKeys[];
extern u8 g_charClassFlags[];


void* AllocateFrontMemory(s32 size);
PlacedObject* CreateObjectCopy(BaseObject* self, World* world, BaseObject* parent);





void ChooseObjectPoolItem(ObjectPool* self);





extern void* const g_screenElements[];


extern void* const g_screenElements[];


extern void* const g_screenElements[];

extern ElementPlaceTable g_elementPlaces;



// allocator puts the count in $s1 and the pointer in $s0; retail is the other way round.

extern u8 g_screenFade[];




void* AllocateZeroedFrontMemory(s32 n);


extern s32 D_002751D4;

// EXACT: dst built as i*4 + (u32)items

void AdvanceObjectPoolEntry(ObjectPool* self);
struct PoolCandidate;
s32 IsObjectPoolItemFree(ObjectPool* self, PoolCandidate* key);
void* MoveMemory(s32* dst, s32* src, s32 size);



s32 IsObjectPoolItemFree(ObjectPool* self, PoolCandidate* key);




struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);


// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void InitScreenElement();
void InitPauseMenu();
void SetPauseMenuOpen();
void UpdatePauseMenu();
void SetPauseMenuMode();
void ShowPauseMenu();
void HidePauseMenu();
void DrawPauseMenu();
struct T217D_3F0;
void InitWarpMenu();
void HandleWarpMenuInput();
void SetWarpMenuOpen();
void DrawWarpMenu();


void MeasureText(TextReader*, f32, f32*, f32*);

extern f32 g_frameDt;

f32 SumTextWidth(TextReader* loc);


// An object func_001A88A0 may add to a pool: a class 0x3B with 0x678 clear or a class 0x20
// with 0x680 set is refused.
struct PoolCandidate { u8 pad0[0x678]; s32 f678; u8 pad1[4]; s32 f680; };

s32 IsObjectAttached(BaseObject* self);

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
T217D_E30 g_reserveCountCaption;
T217D_E30 g_collectedItemCaption;
T217D_E30 D_0026CBC8;
T217D_E30 D_0026CE48;
T217D_E30 g_pairControllerCountCaption;
T217D_E30 g_gaugeAmountCaption;
T217D_E30 g_pathFollowerFirstCountCaption;
T217D_E30 D_0026D848;
T217D_E30 g_pathFollowerSecondCountCaption;
T217D_E30 g_hitCountCaptionA;
T217D_E30 g_hitCountCaptionB;
T217D_2E0 g_gaugeBarElement;
T217D_E30 g_gaugeColliderCaption;
T217D_510 g_timerElement;
T217D_1380 g_timerCaption;
T217D_330 g_buttonHintElement;
T217D_380 g_pointerTextCaption;
T217D_3D0 g_copiedTextCaption;
T217D_420 g_hintGlyphElement;
T217D_0F0 g_mapScreenList;
T217D_12E0 g_selectionCaption;
T217D_1330 g_gridSelector;
T217D_6D0 g_pauseMenuElement;
T217D_440 g_typedTextCaptionBox;
T217D_BF0 g_spinningSpriteElement;
T217D_3F0 D_002708E0;
T217D_3F0 D_00271558;
T217D_560 g_letterboxElement;
T217D_E30 g_firstTallyCaption;
T217D_E30 g_secondTallyCaption;
T217D_470 g_titleElement;
T217D_4C0 g_promptElement;
T217D_720 g_stackedCaptionGroup;
T217D_5B0 D_002739F0;
T217D_5B0 D_00273C50;
T217D_600 g_cyclingGlyphElement;
T217D_E30 g_completionPercentCaption;




void InitObject(BaseObject* self);

void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);
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
    self->idsResolved = 0;
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
        if (self->sub->lentOut != 0) {
            self->sub->qC = (Quad16*)AllocateFrontMemory(self->count << 5);
        }
    }
    for (i = 0; i < self->count; i++) {
        ObjectPoolEntry* e = &self->items[i];
        PlacedObject* obj = (PlacedObject*)FindFirstObjectById(self->world, 4, e->id, self);
        s32 n;
        s32 cnt;
        if (obj == 0) {
            e->count = 0;
            continue;
        }
        if (self->sub != 0 && self->sub->lentOut != 0) {
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
            SetListLinkOffset((List01*)((u8*)self->sub + 0x14), 0x18);
        c1: {
                s32 r = CountListItems((List01*)((u8*)self->sub + 0x14));
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
        if (self->sub != 0 && self->sub->lentOut != 0) {
            Quad16* d = self->sub->qC + (i << 1);
            d[0] = *(Quad16*)&obj->v190;
            d[1] = *(Quad16*)&obj->v1D0;
        }
    }
}

void CopyObjectPool(ObjectPool* self, ObjectPool* other)
{
    CopyObjectData(self, other);
    if (self->sub != 0 && self->sub->lentOut != 0) {
        if (other->sub->f8 != 0) {
            self->sub = 0;
        } else {
            other->sub->f8 = 1;
            SetListLinkOffset((List01*)((u8*)other->sub + 0x14), 0x18);
            self->sub = 0;
        }
        GetObjectPoolShare(self);
        self->sub->lentOut = 1;
        self->sub->f8 = 2;
        self->sub->lentTo = other;
        AppendToList((List01*)((u8*)other->sub + 0x14), self->sub);
    } else {
        self->items = (ObjectPoolEntry*)CopyToFrontMemory(other->count * 0x14, other->items);
    }
}

void StartObjectPool(ObjectPool* self)
{
    StartObject(self);
    if (self->idsResolved != 0) {
        return;
    }
    self->idsResolved = 1;
    if (self->id4C != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id4C, self);
        if (p != 0) {
            if (IsObjectOfKind((BaseObject*)p, 0x7E) != 0) {
                self->f60 = p;
            } else if (IsObjectOfKind((BaseObject*)p, 0x73) != 0) {
                self->f64 = p;
            } else if (IsObjectOfKind((BaseObject*)p, 2) != 0) {
                self->f68 = p;
            }
        }
    }
    if (self->id50 != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id50, self);
        if (p != 0) {
            if (IsObjectOfKind((BaseObject*)p, 2) != 0) {
                self->fE0 = p;
            } else if (IsObjectOfKind((BaseObject*)p, 0x75) != 0) {
                self->fE4 = p;
            }
        }
    }
    if (self->id54 != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id54, self);
        if (p != 0) {
            if (IsObjectOfKind((BaseObject*)p, 0x73) != 0) {
                self->f160 = p;
            } else if (IsObjectOfKind((BaseObject*)p, 2) != 0) {
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

    if (group != 0 && group->lentOut != 0) {
        List01* list;
        ObjectPool* skip;
        ListFrame it;
        u8* obj;

        switch (group->f8) {
        case 1:
            list = (List01*)&group->lentTo;
            skip = 0;
            break;
        case 2: {
            ObjectPool* e = (ObjectPool*)group->lentTo;
            skip = self;
            if (e->chosenItem == (s32)key) {
                return 0;
            }
            list = (List01*)&e->sub->lentTo;
            break;
        }
        }
        ListWalkBegin::Of(&it, list);
        for (obj = ListWalkNext::Of(&it); obj != 0; obj = ListWalkNext::Of(&it)) {
            ObjectPool* e = *(ObjectPool**)obj;
            if (e != skip && e->chosenItem == (s32)key) {
                ListWalkEnd::Of(&it);
                return 0;
            }
        }
        ListWalkEnd::Of(&it);
    }
    if (IsObjectAttached((BaseObject*)key) != 0) {
        return 0;
    }
    if (IsObjectOfKind((BaseObject*)key, 0x3B) != 0 && key->f678 == 0) {
        return 0;
    }
    if (IsObjectOfKind((BaseObject*)key, 0x20) != 0 && key->f680 != 0) {
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
    pos = (self->lastItemIndex + 1) % self->count;
    if (!(i < self->count)) {
        return;
    }
    do {
        ObjectPoolEntry* rec = &self->items[pos];
        if ((rec->flags & 2) != 0) {
            for (k = 0; k < rec->count; k++) {
                if (IsObjectPoolItemFree(self, (PoolCandidate*)rec->objects[k]) != 0) {
                    goto found;
                }
            }
        }
        pos = (pos + 1) % self->count;
        i++;
    } while (i < self->count);
found:
    if (i < self->count) {
        self->lastItemIndex = pos;
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
        ObjectPoolEntry* rec = &self->items[self->lastItemIndex];

        if (rec->flags & 2) {
            s32 i = 0;
            if (rec->count > 0) {
                do {
                    if (IsObjectPoolItemFree(self, (PoolCandidate*)rec->objects[i]) != 0) {
                        s4 = (s32)rec->objects[i];
                        if (self->sub != 0 && self->sub->lentOut != 0) {
                            s5 = self->sub->fC + (self->lastItemIndex << 5);
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
    self->chosenItem = s4;
    if (self->sub != 0 && self->sub->lentOut != 0) {
        self->sub->f10 = s5;
    }
}

s32 HasObjectPoolChoice(ObjectPool* self)
{
    if (self->chosenItem != 0) {
        return 1;
    }
    ChooseObjectPoolItem(self);
    return self->chosenItem != 0;
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
    f32 expiryTime;                 // 0x554: the game time at which the released object expires
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

struct FrameFollower;
void GetPlacementRecordTransform(FrameSource* self, Vec02* a1, Vec02* a2, void* a3);
void ComputeFrameFollowerPoint(FrameFollower* self, Vec02* target, Vec02* out, void* to);
void GetPlacementRecordAngle(u8* self, f32* out, void* x);
void GetPlacementRecordPitch(u8* self, f32* out, void* x);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void ForwardBallisticLaunchVelocity(f32 angle, Vec02* from, Vec02* to, Vec02* out, u8* rec);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
s32 ComputeBallisticLaunchVelocity(f32 angle, Vec02* from, Vec02* to, Vec02* out, u8* rec);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);

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

s32 LaunchChosenPoolObject(ObjectPool* pool, s32 aim)
{
    PoolView_1A8C90* self = (PoolView_1A8C90*)pool;
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
    GetPlacementRecordTransform((FrameSource*)((u8*)self + 0x60), &pos, rot.r, self->frame);
    ComputeFrameFollowerPoint((FrameFollower*)((u8*)self + 0xE0), &pos, &to, self->frame);
    Vu0::Q(dir) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
    u128 len = NormalizeVectorOr(dir, g_unitXVector);
    f32 reach = self->range.Clamp(self->poly.Eval(Vu0::ToFloatMoved(len)));
    Vu0::Q(to) = Vu0::Add(Vu0::Q(pos), Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(reach)));
    if (self->parent != 0 && self->parent->root != 0 && ((*self->parent->root)->flags & 2) && IsObjectOfKind((BaseObject*)obj, 0x3C)) {
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
    SetColliderAnchors((Collider*)obj, 0, 0, 0, 0);
    obj->desc->m84(obj, &pos);
    obj->desc->m88(obj, &rot);
    if (self->sub != 0 && self->sub->lentOut != 0) {
        Vec02* q = (Vec02*)self->sub->f10;
        obj->v190 = q[0];
        obj->v1D0 = q[1];
    }
    if (self->mover != 0) {
        Vec02 vel;
        Vec02 spin;
        ComputeObjectMotionInFrame((PlacedObject*)self->mover, 0, &((PlacedObject*)self->mover)->v140, &vel, &spin, 0, 0);
        obj->desc->m90(obj, &vel);
        obj->desc->m94(obj, &spin);
    } else {
        Vec02* vel = vel;
        if (aim != 0) {
            ReleaseHeading_1A8C90* h = &self->heading;
            if (IsObjectOfKind((BaseObject*)obj, 0x3E) || IsObjectOfKind((BaseObject*)obj, 0x3D)) {
                Vec02 delta;
                Vec02 scale;
                Mat02 m;
                f32 yaw;
                f32 pitch;
                Vu0::Q(delta) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
                if (h->flags & 2) {
                    GetPlacementRecordAngle((u8*)h, &yaw, self->frame);
                } else {
                    yaw = ArctangentOfRatio(delta.y, delta.x);
                }
                if (h->flags & 1) {
                    GetPlacementRecordPitch((u8*)h, &pitch, self->frame);
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
                    GetPlacementRecordAngle((u8*)h, &yaw, self->frame);
                    a = WrapAngle(a);
                    AreFloatsNearlyEqual(a, WrapAngle(yaw), 0.0001f);
                }
                if (self->heading.flags & 1) {
                    f32 t;
                    GetPlacementRecordPitch((u8*)h, &t, self->frame);
                    ForwardBallisticLaunchVelocity(t, &pos, &to, &self->velocity, (u8*)obj);
                } else if (self->heading.flags & 4) {
                    ComputeLaunchVelocityToPoint(h->speed, &pos, &to, &self->velocity, (u8*)obj);
                } else {
                    ComputeBallisticLaunchVelocity(0.5f, &pos, &to, &self->velocity, (u8*)obj);
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
    if (0.0f < self->life && IsObjectOfKind((BaseObject*)obj, 0x3B)) {
        obj->expiryTime = g_gameTime + self->life;
    }
    if (IsObjectOfKind((BaseObject*)obj, 0x3C)) {
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
    if (IsObjectOfKind((BaseObject*)obj, 8)) {
        ChangeAgentState((Agent*)obj, 0x10, 0);
        if (IsObjectOfKind((BaseObject*)obj, 0xA)) {
            obj->fC3C = 1;
        }
    }
    Released_1A8C90** held = &obj;
    TriggerScriptEvent((BaseObject*)self, 0xD, 1, &held);
    ClearObjectPoolChoice((ObjectPool*)self);
    return 1;
}

void ClearObjectPoolChoice(ObjectPool* p) { p->chosenItem = 0; if (p->sub != 0 && p->sub->lentOut != 0) p->sub->f10 = 0; }

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
    if (self->positionObject != 0) {
        ConvertPositionToWorld((BaseObject*)self->positionObject, a1);
        a2[0] = self->rot[0];
        a2[1] = self->rot[1];
        a2[2] = self->rot[2];
    } else if (self->frameObject != 0) {
        GetObjectWorldPosition((BaseObject*)self->frameObject, a1);
        GetObjectWorldRotation((BaseObject*)self->frameObject, (Mat02*)a2);
    } else {
        if (self->placedObject != 0) {
            a1[0] = self->placedObject->v140;
            PlacedObject* in = self->placedObject;
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
        TransformPointBetweenFrames(0, (PlacedObject*)a3, a1, a1);
        TransformRotationBetweenFrames(0, (PlacedObject*)a3, (Mat02*)a2, (Mat02*)a2);
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

// Left in this order: retail's call here evaluates the time before the pointers.
void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);

void ComputeFrameFollowerPoint(FrameFollower* self, Vec02* target, Vec02* out, void* to)
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
        TransformPointBetweenFrames((PlacedObject*)frame, (PlacedObject*)to, local, out);
        return;
    case 1:
    case 2: {
        TransformPointBetweenFrames((PlacedObject*)frame, 0, local, &here);
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
        ComputeObjectFrameAtTime((PlacedObject*)frame, 0, t, &here, &rot, 0, 0);
        Vu0::Q(*out) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(*local)), Vu0::Q(here));
        if (to != 0) {
            ComputeObjectFrameAtTime((PlacedObject*)to, 0, t, &pos2, &rot2, 0, 0);
            Vu0::Q(*out) = Vu0::RotateTransposed(rot2, Vu0::Sub(Vu0::Q(*out), Vu0::Q(pos2)));
        }
        break;
    }
    }
}

void GetPlacementRecordAngle(u8* self, f32* out, void* x)
{
    f32 v[12];
    if (*(void**)(self + 0x10) != 0) {
        GetObjectWorldRotation(*(void**)(self + 0x10), v);
        TransformRotationBetweenFrames(0, (PlacedObject*)x, (Mat02*)v, (Mat02*)v);
        *out = ArctangentOfRatio(v[1], v[0]);
    } else if (*(u8**)(self + 0x14) != 0) {
        TransformRotationBetweenFrames(0, (PlacedObject*)x, (Mat02*)(*(u8**)(self + 0x14) + 0x110), (Mat02*)v);
        *out = ArctangentOfRatio(v[1], v[0]);
    } else {
        *out = *(f32*)(self + 0x8);
    }
}

void GetPlacementRecordPitch(u8* self, f32* out, void* x)
{
    f32 v[12] __attribute__((aligned(16)));
    if (*(void**)(self + 0x10) != 0) {
        GetObjectWorldRotation(*(void**)(self + 0x10), v);
        TransformRotationBetweenFrames(0, (PlacedObject*)x, (Mat02*)v, (Mat02*)v);
        u128 r = Vu0::Q(*(u128*)v);
        *out = ArctangentOfRatio(v[2], Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(r, r))));
    } else {
        *out = *(f32*)(self + 0x4);
    }
}

void StartWorld4Boss(World4Boss* self)
{
    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
}

s32 IsWorld4BossFree(World4Boss* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0)
        return 0;
    return self->fC24;
}

void UpdateWorld4BossGoal(World4Boss* self, s32 flag)
{
    UpdateAgentGoal(self, flag);
    if (self->state == 0x10) {
        void* r = ((VFn_1A9960*)self->desc)[102](self);
        if (r != 0)
            SetAgentGoalPoint(self, &((PlacedObject*)r)->v140);
    }
}

void UpdateWorld4BossState(World4Boss* self)
{
    UpdateAgentState(self);
    if (self->state == 0x10)
        FaceAgentTowardGoalPoint(self);
}

void EnterWorld4BossState(World4Boss* self, s32 evt, Animation* arg)
{
    EnterAgentState(self, evt, arg);
    if (self->state == 0xB) {
        MarkLevelDone(4);
        StartMemoryCardSave((MemoryCard*)g_memoryCard);
    }
}

void UpdateWorld4Boss(World4Boss* self, f32 dt)
{
    u8* s = (u8*)self;
    UpdateAgent(self, dt);
    void* p = *(void**)(s + 0xC20);
    if (p != 0) {
        if (*(f32*)((u8*)p + 0x18) == 0.0f) {
            StopAnimationPlayer((AnimationPlayer*)p);
            *(void**)(s + 0xC20) = 0;
        }
    }
}

void UpdateWorld4BossVisibility(void)
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
struct AgentHit;
struct Agent;
extern Player* g_player;
extern const Vec02 g_unitXVector;


s32 HandleWorld4BossObjectEvent(World4Boss* self, ObjectEvent* ev)
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
        Animation* which;
        if ((ev->extraFlags & 2) != 0) {
            if (g_player == 0 || g_player->aimMode == 4 || g_player->aimMode == 6)
                which = self->fC14;
            else
                which = self->fC18;
        } else if ((ev->extraFlags & 4) != 0) {
            which = self->fC1C;
        } else {
            which = self->fC14;
        }
        ReplaceAnimationPlayer(which, self, 1, (AnimationPlayer**)((u8*)self + 0xC20), 0.0f, 1.0f);
        ev->eventFlags &= ~0x20;
    }
    return HandleAgentObjectEvent(self, (AgentHit*)ev);
}

void SetWorld4BossValues(World4Boss* self, Animation* a, Animation* b, Animation* c)
{
    self->fC14 = a;
    self->fC18 = b;
    self->fC1C = c;
}

void InstallScreenElements()
{
    g_reserveCountCaption.vt = (const T217D_Vt*)D_00217E30;
    g_collectedItemCaption.vt = (const T217D_Vt*)D_00217E80;
    D_0026CBC8.vt = (const T217D_Vt*)D_00217ED0;
    D_0026CE48.vt = (const T217D_Vt*)D_00217F20;
    g_pairControllerCountCaption.vt = (const T217D_Vt*)D_00217F70;
    g_gaugeAmountCaption.vt = (const T217D_Vt*)g_gaugeAmountCaptionMethods;
    g_pathFollowerFirstCountCaption.vt = (const T217D_Vt*)D_002180B0;
    D_0026D848.vt = (const T217D_Vt*)D_00218010;
    g_pathFollowerSecondCountCaption.vt = (const T217D_Vt*)D_00218060;
    g_hitCountCaptionA.vt = (const T217D_Vt*)D_00218100;
    g_hitCountCaptionB.vt = (const T217D_Vt*)D_00218150;
    g_gaugeBarElement.vt = (const T217D_Vt*)g_gaugeBarElementMethods;
    g_gaugeColliderCaption.vt = (const T217D_Vt*)D_002181A0;
    g_timerElement.vt = (const T217D_Vt*)g_timerElementMethods;
    g_timerCaption.vt = (const T217D_Vt*)g_timerCaptionMethods;
    g_buttonHintElement.vt = (const T217D_Vt*)D_00218330;
    g_pointerTextCaption.vt = (const T217D_Vt*)g_pointerTextCaptionMethods;
    g_copiedTextCaption.vt = (const T217D_Vt*)g_copiedTextCaptionMethods;
    g_hintGlyphElement.vt = (const T217D_Vt*)g_hintGlyphElementMethods;
    g_mapScreenList.vt = (const T217D_Vt*)g_mapScreenListMethods;
    g_selectionCaption.vt = (const T217D_Vt*)g_selectionCaptionMethods;
    g_gridSelector.vt = (const T217D_Vt*)g_gridSelectorMethods;
    g_pauseMenuElement.vt = (const T217D_Vt*)g_pauseMenuElementMethods;
    g_typedTextCaptionBox.vt = (const T217D_Vt*)g_typedTextCaptionBoxMethods;
    g_spinningSpriteElement.vt = (const T217D_Vt*)g_spinningSpriteElementMethods;
    D_002708E0.vt = (const T217D_Vt*)g_arcElementMethods;
    D_00271558.vt = (const T217D_Vt*)g_arcElementMethods;
    g_firstTallyCaption.vt = (const T217D_Vt*)D_00218240;
    g_secondTallyCaption.vt = (const T217D_Vt*)D_00218290;
    g_titleElement.vt = (const T217D_Vt*)g_titleElementMethods;
    g_promptElement.vt = (const T217D_Vt*)g_promptElementMethods;
    g_letterboxElement.vt = (const T217D_Vt*)g_letterboxElementMethods;
    g_stackedCaptionGroup.vt = (const T217D_Vt*)g_stackedCaptionGroupMethods;
    D_002739F0.vt = (const T217D_Vt*)g_letterGlyphElementMethods;
    D_00273C50.vt = (const T217D_Vt*)g_letterGlyphElementMethods;
    g_cyclingGlyphElement.vt = (const T217D_Vt*)g_cyclingGlyphElementMethods;
    g_completionPercentCaption.vt = (const T217D_Vt*)D_002181F0;
    for (s32 i = 0x24; i >= 0; i--) {
        ((ScreenElement**)g_screenElements)[i]->vt->m00(((ScreenElement**)g_screenElements)[i], i);
    }
    ResetScreenFade((ScreenFade*)g_screenFade);
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
    UpdateScreenFade((ScreenFade*)g, (PadRecord*)b);
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
    DrawScreenFade((ScreenFade*)g_screenFade);
    DrawCyclingGlyphElement((T217D_600*)&g_cyclingGlyphElement);
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
