// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x16AA18 to 0x16C470: the current object's choices, the selection caption and the grid
// selector (three pick-one screens, each with its input, opening and drawing), and the box styles
// its static initialiser builds. Its name is ours, after that role.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "state_walker.h"
#include "listed_collision_part.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "current_placed_object.h"
#include "part_holder_object.h"
#include "list_iter.h"
#include "screen_element.h"
#include "packet_writer.h"
#include "font.h"
#include "game_progress.h"
#include "attachment.h"
#include "pad_record.h"
#include "globals.h"
#include "strip_mesh.h"
#include "bump_allocator.h"
#include "texture_header.h"
#include "shapes.h"
#include "object_finder.h"
#include "layout_137228.h"

// Types other files define, named by the parameters of their functions declared here.
struct MemoryCard;
struct ObjectLink;

extern f32 g_gameTime[];
extern f32 g_elapsedTime;
extern s32 g_previousLevelIndex;
extern u8 g_memoryCard[];
extern s32 g_currentPlacedObject;
extern u8 g_elementStack[];
// An entry of the choice tables D_00262718 and D_00262788 (three words).
struct ChoiceEntry { s32 a; s32 b; s32 c; };
struct ChoiceTable { ChoiceEntry e[9]; s32 end; };
extern ChoiceTable g_partHolderLinks;
// The element stack (D_00275BC0) as func_0016AED8 sets its state word.
struct ElementStackState { u8 pad0[0x30]; s32 f30; };
extern ChoiceEntry g_currentPlacedObjectLinks[18];
// The entry LookupEntryById gives for a choice's level: StartObjectFade fades it when its
// two words differ.
struct ChoiceLevelEntry {
    s32 f0;
    s32 f4;
    u8 pad[0x14];
    s32 f1C;
};
// The state-walker keys of each choice (D_00262860): the one walked to, the one targeted.
struct ChoiceKeys { s32 walkerKey; s32 targetKey; };
extern ChoiceKeys D_00262860[6];
// A sound request of a choice (D_00262890 by choice, D_00262950), 0x20 bytes.
struct ChoiceSound { u32 w[8]; };
extern ChoiceSound D_00262890[6];
extern ChoiceSound D_00262950;
extern f32 g_gameClock[];
extern f32 D_00262970;
extern s32 D_0026FCF4;
struct BoxStyle;
extern BoxStyle D_00262988;
extern s32 D_00272420;
struct CaptionLayout;
struct CaptionLayout {
    union {
        u8 b[32];
        struct {
            f32 x, y;
            f32 w, h;
            u32 color;
#ifdef VERSION_EU
            s32 pal14;  // PAL has one word more before the alignments (func_0016BEA0)
#endif
            s32 hAlign;
            s32 vAlign;
        };
    };
    void Pos(f32 x, f32 y) { ((Layout_137228*)this)->Pos(x, y); }
    void Size(f32 x, f32 y) { ((Layout_137228*)this)->Size(x, y); }
    void Color(s32* c) { ((Layout_137228*)this)->Color(c); }
    void FlagA(s32 f) { ((Layout_137228*)this)->SetF14(f); }
    void FlagB(s32 f) { ((Layout_137228*)this)->SetF18(f); }
};
struct CaptionDrawer {
    static void Draw(Font** h, CaptionLayout* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};
extern BoxStyle D_002629A8;

void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
u32 GetEntryFlags(s32 idx);
u32* GetLevelEntryByKey(s32 idx);
void CallFlaggedParts(PartHolderObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 9, (ObjectLink*)&g_partHolderLinks);

    if ((u32)(self->id - 0x515) < 5) {
        s32 t = self->id - 0x514;
        s32 s4 = t << 8;

        for (s32 i = 0; i < 9; i++) {
            if (self->parts[i] == 0) {
                continue;
            }
            s32 flag;
            if (i == 8) {
                flag = g_saveData->levels[t].f448 & 0x20;
            } else {
                s32 idx = s4 | i;
                u32 r = GetEntryFlags(idx);
                u32* p = GetLevelEntryByKey(idx);
                if ((r & 2) != 0) {
                    flag = *p & 2;
                } else {
                    flag = *p & 1;
                }
            }
            if (flag != 0) {
                PartObject* obj = self->parts[i];
                obj->vtbl[6](obj);
            }
        }
    }
}

StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
s32 ComputeCompletionMask();
void SetCurrentObjectChoice(CurrentPlacedObject* self, s32 a, s32 b);
void TeleportStateWalker(StateWalker* self, s32 key);
void PushStackElement(ElementStack* self, ScreenElement* node);
void SetupCurrentObjectChoices(CurrentPlacedObject* self)
{
    if (self->walkers[0].graph) self->walkers[0].walker = CreateStateWalker((StateGraph*)self->walkers[0].graph, 0, -1, 0);
    if (self->walkers[1].graph) self->walkers[1].walker = CreateStateWalker((StateGraph*)self->walkers[1].graph, 0, -1, 0);
    if (self->walkers[2].graph) self->walkers[2].walker = CreateStateWalker((StateGraph*)self->walkers[2].graph, 0, -1, 0);
    if (self->walkers[3].graph) self->walkers[3].walker = CreateStateWalker((StateGraph*)self->walkers[3].graph, 0, -1, 1);
    self->lastChoice = 5;
    for (;;) {
        s32 c = self->lastChoice;
        if (c < 3) break;
        if (g_saveData->levels[c - 2].f448 & 0x20) break;
        s32 d = c - 1;
        if (g_saveData->levels[d].f448 & 1) break;
        self->lastChoice = d;
    }
    for (s32 i = 1; i <= self->lastChoice; i++) {
        StateTrigger* o = self->levelObjects[i - 1];
        if (o && (g_saveData->levels[i].f448 & 1)) o->desc->m02(o);
    }
    self->pendingSequence = 0;
    for (s32 i = 0; i < 4; i++) {
        ChoiceSequence* c = self->sequences[i];
        if (c && *c->flagp == 0) {
            s32 v = 0;
            switch (i) {
            case 0: v = 1; break;
            case 1: v = ComputeCompletionMask() >> 1; goto mask;
            case 2: v = ComputeCompletionMask() >> 2; goto mask;
            case 3: v = ComputeCompletionMask() >> 3;
            mask: v &= 1; break;
            default: break;
            }
            if (v) {
                self->pendingSequence = c;
                break;
            }
        }
    }
    s32 idx;
    if (self->pendingSequence) {
        idx = 0;
    } else {
        s32 a = g_previousLevelIndex;
        if (a != -1 && (g_saveData->levels[a].f448 & 1)) {
            idx = a;
        } else {
            s32 c = self->lastChoice;
            if ((g_saveData->levels[c - 1].f448 & 1) == 0) {
                idx = c - 2;
            } else if ((g_saveData->levels[c].f448 & 1) == 0) {
                idx = c - 1;
            } else {
                idx = c;
            }
        }
    }
    SetCurrentObjectChoice(self, idx, 0);
    if (self->walkers[2].walker || self->walkers[3].walker) {
        idx = self->lastChoice;
        if (idx != 5) {
            self->walkerChoice = idx;
        } else {
            GameProgress* t = g_saveData;
            if (t->levels[4].f448 & 0x20) self->walkerChoice = 0;
            else if (t->levels[5].f448 & 1) self->walkerChoice = 0;
            else self->walkerChoice = idx;
        }
        if (self->walkers[2].walker) TeleportStateWalker(self->walkers[2].walker, D_00262860[self->walkerChoice].walkerKey);
        if (self->walkers[3].walker) TeleportStateWalker(self->walkers[3].walker, D_00262860[self->walkerChoice].walkerKey);
    }
    PushStackElement((ElementStack*)g_elementStack, &D_0026FA90);
}

void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void SetElementStackState(ElementStack* self, s32 state);
void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d); // stays void: retail returns a value, but declared so func_0016AED8 differs in registers
void BecomeCurrentObject(CurrentPlacedObject* self)
{
    StartPlacedObject(self);
    self->flags = (self->flags & ~(3ULL << 40)) | (1ULL << 40);
    g_currentPlacedObject = (s32)self;
    ((ElementStackState*)g_elementStack)->f30 = 2;
    SetElementStackState((ElementStack*)g_elementStack, 2);
    ResolveObjectLinks(self, 0x12, (ObjectLink*)g_currentPlacedObjectLinks);
    self->choice = -1;
    AppendQueuedCall(self->world, (void*)SetupCurrentObjectChoices, self, 0, 0);
}

void SetElementTextFromIndexedCounts(ScreenElement* self, s32 idx);
void ShowCurrentObjectCaptions(CurrentPlacedObject* self)
{
    s32 s1 = 0;
    StateWalker* p = self->walkers[0].walker;

    if (p->currentEntry != p->index) {
        D_0026F138.vt->m08(&D_0026F138, "");
    } else if (self->choice == 0) {
        D_0026F138.vt->m08(&D_0026F138, "Bentley");
    } else {
        s32 flags = g_saveData->levels[self->choice].f448;
        if (flags & 1) {
            SetElementTextFromIndexedCounts(&D_0026F138, self->choice);
        } else if (self->choice == self->walkerChoice) {
            D_0026F138.vt->m08(&D_0026F138, "Murray");
        } else {
            s1 = 1;
            D_0026F138.vt->m08(&D_0026F138, "");
        }
    }

    SetScreenElementHoldTime(&D_0026F138, 0.0f);
    D_0026F138.announce = 0;
    D_0026F138.vt->m14(&D_0026F138);

    if (s1 != 0) {
        D_0026FA90.vt->m08(&D_0026FA90, "Press &2X&. to Start Mission!");
        D_0026FA90.vt->m14(&D_0026FA90);
    } else {
        D_0026FA90.vt->m15(&D_0026FA90);
    }
}

s32 GetPadHorizontalStep(PadRecord* self);
void SetCurrentObjectChoice(CurrentPlacedObject* self, s32 a, s32 b);
void MoveCurrentObjectChoice(CurrentPlacedObject* self, PadRecord* a1)
{
    s32 n = self->choice;
    s32 r = GetPadHorizontalStep((PadRecord*)a1);
    f32 f = (f32)r;
    s32 v = self->lastChoice;
    s32 k = (v == 5);

    if (f < 0.0f) {
        if (n <= 0) {
            n = k ? v : n;
        } else {
            n--;
        }
    } else if (0.0f < f) {
        if (n >= v) {
            n = k ? 0 : n;
        } else {
            n++;
        }
    }
    SetCurrentObjectChoice(self, n, 0);
}

void* LookupEntryById(s32 key);
void MarkProgressStageFlag(s32 idx);
struct IdentityKey;
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb); // stays void: retail returns a value, but declared so func_0016B190 differs in registers
s32 HasAnimationEventKind19(Animation* a0);
void StartObjectFade(IdentityKey* obj, s32 value, s32 count);
void PopStackElement(ElementStack* g);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void SetCurrentObjectChoice(CurrentPlacedObject* self, s32 a, s32 b);
void ConfirmCurrentObjectChoice(CurrentPlacedObject* self)
{
    s32 callB = 1;
    s32 idx = self->choice;
    if (idx != 0) {
        if ((g_saveData->levels[idx].f448 & 1) == 0) {
        if (idx != self->walkerChoice) {
            s32 s2 = 1;
            void* elt;
            u8* table = (u8*)self->choiceAnimations;
            MarkProgressStageFlag(idx);
            elt = *(void**)(table + (self->choice << 2));
            if (elt != 0) {
                CreateAnimationPlayerWithoutPresetTargets((Animation*)elt, self, 0, 0, 0.0f, 1.0f);
                elt = *(void**)(table + (self->choice << 2));
                if (elt != 0 && HasAnimationEventKind19((Animation*)elt) != 0) {
                    goto tail;
                }
            }
            {
                ChoiceLevelEntry* a = (ChoiceLevelEntry*)LookupEntryById(self->choice << 8);
                s32 flag = 0;
                if (a != 0) {
                    flag = (a->f4 != a->f1C);
                }
                if (flag) {
                    StartObjectFade((IdentityKey*)a, -1, 1);
                } else {
                    s2 = 0;
                }
            }
        tail:
            if (s2) {
                PopStackElement((ElementStack*)g_elementStack);
            }
        } else {
            void* h = self->walkers[3].walker;
            callB = 0;
            if (h != 0) {
                { SetStateWalkerTarget((StateWalker*)h, D_00262860[idx].targetKey); }
            }
        }
        }
    }
    if (callB) {
        SetCurrentObjectChoice(self, self->choice, 1);
    }
}

// NEAR: only the order of `addiu v0,s5,lo(D_00261858)` vs `sw s4,0x2D4(s3)` differs (2 instrs swapped)

struct KeyRecord;
void OpenKeyRecord(KeyRecord* self);
s32 HasStreamVoice(void);
void TeleportStateWalker(StateWalker* self, s32 key);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void SetCurrentObjectChoice(CurrentPlacedObject* self, s32 a, s32 b)
{
    if (a == self->choice && b == self->keyIndex) return;
    if (a != self->walkerChoice && a > 0) {
        ChoiceSound* slot = 0;
        if (g_saveData->levels[a].f448 & 1) {
            s32 fl = g_saveData->optionFlags;
            if (!(fl & 2)) {
                g_saveData->optionFlags = fl | 2;
                slot = (ChoiceSound*)&D_00262950;
            }
        } else {
            f32 t = g_gameClock[1];
            if (D_00262970 <= t - D_0026FA90.lastAt) {
                D_0026FA90.lastAt = t;
                slot = (ChoiceSound*)((u8*)D_00262890 + (a << 5));
            }
        }
        if (slot) {
            OpenKeyRecord((KeyRecord*)slot);
            D_0026FCF4 = HasStreamVoice();
        }
    }
    void* h = self->walkers[0].walker;
    if (h) {
        if (self->choice == -1) {
            if (a != 0) {
                TeleportStateWalker((StateWalker*)h, D_00262860[a].targetKey);
                SetStateWalkerTarget(self->walkers[0].walker, D_00262860[a].walkerKey);
            }
        } else {
            SetStateWalkerTarget((StateWalker*)h, *(s32*)((u8*)D_00262860 + (a * 8 + b * 4)));
        }
    }
    self->choice = a;
    self->keyIndex = b;
    self->choiceTime = g_gameClock[1];
}

s32 IsFontLoaded(s32 index);
Font* GetFontById(s32 index);
void InitSelectionCaption(T217D_12E0* self)
{
    SetupScreenElementText(self);
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&D_00262988;
        *self->frame = GetFontById(2);
    }
    SetScreenElementHoldTime(self, 0.0f);
    self->node = 0;
    *(u32*)self->rgba.c = 0xDF7F7F7F;
    self->sound = 0;
    self->lastAt = -D_00262970;
}

void PushObjectCameraController(void* p);
void RestoreSelectionCaptionCamera(T217D_12E0* self)
{
    if (self->open != 0) {
        void* p = FindFirstObjectByIdMode4(g_currentWorld, 0x4FD, 0);
        if (p != 0) {
            PushObjectCameraController(p);
        }
    }
}

void UpdateSelectionCaption(T217D_12E0* self)
{
    UpdateScreenElementSlide(self);
}

// The object the element shows (a view of it: its mode at +0x2D0, its animation clock at +0x2D8).
s32 CheckStreamVoicePending(void);
s32 PollIopCommands(void);
s32 HasStreamVoice(void);
void StartMemoryCardSave(MemoryCard* self);
void ChooseStepSequenceState(StepSequence* self);
void ShowCurrentObjectCaptions(CurrentPlacedObject* o);
void PushStackElement(ElementStack* self, ScreenElement* node);
void ClearPadPressedBits(PadRecord* self, u32 mask);
void SetPauseMenuLayerPage(T217D_6D0* a, s32 b, s32 c);
void ConfirmCurrentObjectChoice(CurrentPlacedObject* o);
void MoveCurrentObjectChoice(CurrentPlacedObject* self, PadRecord* a1);
void HandleSelectionCaptionInput(T217D_12E0* self, PadRecord* arg)
{
    if (self->node == 0) {
        return;
    }
    if (((CurrentPlacedObject*)self->node)->walkers[0].walker == 0) {
        return;
    }
    if (self->sound != 0) {
        if (CheckStreamVoicePending() != 0) {
            PollIopCommands();
        }
        self->sound = HasStreamVoice();
    }
    if (D_00272420 != 0) {
        return;
    }
    if (D_0027051C != 0) {
        return;
    }
    CurrentPlacedObject* o = (CurrentPlacedObject*)self->node;
    StateWalker* p = o->walkers[0].walker;
    if (o->pendingSequence != 0) {
        if (o->pendingSequence == o->sequences[0]) {
            StartMemoryCardSave((MemoryCard*)g_memoryCard);
        }
        ChooseStepSequenceState((StepSequence*)o->pendingSequence);
        o->pendingSequence = 0;
    }
    ShowCurrentObjectCaptions(o);
    f32 delay = 0.3f;
    if (o->keyIndex == 1 && (p->currentEntry == p->index || delay <= g_gameTime[0] - o->choiceTime)) {
        s32 idx = o->choice;
        if (idx == 0) {
            if (D_0026FD00.mode != 0) {
                return;
            }
            PushStackElement((ElementStack*)g_elementStack, &D_0026FD00);
            return;
        }
        if (g_mapScreenList.mode != 0) {
            return;
        }
        g_mapScreenList.current = g_mapScreenList.nodes[idx];
        PushStackElement((ElementStack*)g_elementStack, &g_mapScreenList);
        return;
    }
    if (p->currentEntry != p->index) {
        return;
    }
    if ((arg->flags & 0x800) || (arg->connectionMode == 1 && 5.0f <= g_gameTime[0])) {
        ClearPadPressedBits(arg, 0x800);
        SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0x17);
        return;
    }
    if ((arg->flags & 0x140) != 0) {
        ClearPadPressedBits(arg, 0x140);
        ConfirmCurrentObjectChoice(o);
        return;
    }
    MoveCurrentObjectChoice(o, arg);
}

void SetCurrentObjectChoice(CurrentPlacedObject* self, s32 a, s32 b);
s32 SetPadSelectFlags(s32 bits);
void ResetPadStepRepeat(PadRecord* p);
void StopStreamVoice(void);
void ClearPadSelectFlags(u32 mask);
void SetSelectionCaptionOpen(T217D_12E0* self, s32 v)
{
    s32 flag = (v != 0);
    if (flag != (self->open == 0)) {
        return;
    }
    if (v != 0) {
        SetCurrentObjectChoice((CurrentPlacedObject*)self->node, ((CurrentPlacedObject*)self->node)->choice, 0);
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
    } else {
        if (self->sound != 0) {
            StopStreamVoice();
            self->sound = 0;
        }
        ClearPadSelectFlags(1);
        self->vt->m15(self);
        D_0026F138.vt->m15(&D_0026F138);
    }
    self->open = v;
}

extern "C" f32 Sine(f32 x);
void PushFontScale(Font* font, f32 a, f32 b);
struct TextReader;
void* InitTextReader(TextReader* self, char* text, Font* font);
struct Layout_137228;
struct Layout_137228;
struct TextReader;
void DrawAlignedText(TextReader* self, Layout_137228* p, Vec4U* clip, PacketWriter* s);
void PopFontScale(Font* font);
void DrawSelectionCaption(T217D_12E0* self)
{
    T217D_Word tmp;
    CaptionLayout out;
    T217D_Word slot;
    u8 loc[0xB0];

    if (self->node != 0 && self->text[0] != 0) {
        tmp = self->colorWord;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
        f32 p = self->w;
        f32 q = self->h;
        s32 held = tmp.v;
        out.Pos(self->x, self->y);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(1);
        out.FlagB(1);

        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            CaptionDrawer::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        f32 r = Sine(g_elapsedTime * 10.0f);
        f32 t = r * 0.5f + 0.5f;
        f32 k = (1.0f - t) * 0.9f + t;
        f32 v = self->scale * k;
        PushFontScale(self->font, v, v);
        InitTextReader((TextReader*)loc, &self->text[0], self->font);
        DrawAlignedText((TextReader*)loc, (Layout_137228*)&out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

s32 IsFontLoaded(s32 k);
void PushFontScale(Font* font, f32 x, f32 y);
void PopFontScale(Font* font);
void InitGridSelector(T217D_1330* self)
{
    SetupScreenElementText(self);
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&D_002629A8;
        *self->frame = GetFontById(2);
    }
    Font* a1 = self->font;
    f32 f20 = 60.0f;
    f32 f21 = 90.0f;
    const FontVt* vt = a1->vt;
    Font* n = vt->clone((Font*)((u8*)a1 + vt->adj1), 1.0f, 1.0f);
    self->font = n;
    self->color = 0xDF7F7F7F;
    f20 = (f32)n->height * n->sy + f20;
    Font* s0 = GetFontById(4);
    PushFontScale(s0, 1.3f, 1.3f);
    const FontVt* v = s0->vt;
    f32 r = v->width((Font*)((u8*)s0 + v->adj3), 0x5F);
    f21 = r * 4.0f + f21;
    f20 = f20 + (f32)s0->height * s0->sy * 4.0f;
    PopFontScale(s0);
    SetScreenElementSize(self, f21, f20);
}

u32 TestGridEntryBit(u32 bit)
{
    u32 mask;
    if (bit >= 16) {
        mask = 0;
    } else {
        mask = 1 << bit;
    }
    return g_saveData->u19F4 & mask;
}

void ClearPadPressedBits(PadRecord* self, u32 mask);
void QueueMovieByIndex(s32 index);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
s32 GetPadHorizontalStep(PadRecord* p);
s32 GetPadVerticalStep(PadRecord* p);
void HandleGridSelectorInput(T217D_1330* ctx, PadRecord* o)
{
    s32 s1;
    s32 r2;

    if ((o->flags & 0x9B0) != 0 || (o->connectionMode == 1 && 5.0f <= g_gameTime[0])) {
        ClearPadPressedBits(o, 0x9B0);
        PopStackElement((ElementStack*)g_elementStack);
        return;
    }
    if ((o->flags & 0x40) != 0) {
        ClearPadPressedBits(o, 0x40);
        if (TestGridEntryBit(ctx->cursor) != 0) {
            QueueMovieByIndex(ctx->cursor);
            return;
        }
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s1 = GetPadHorizontalStep(o);
    r2 = GetPadVerticalStep(o);
    if (s1 == 0 && r2 == 0) {
        return;
    }
    o->nextStepTimeX = g_gameClock[4] + o->stepDelayX;
    o->nextStepTimeY = g_gameClock[4] + o->stepDelayY;

    {
        s32 n = ctx->cursor;
        s32 q = n / 4;
        s32 r = n % 4;
        if (s1 < 0 && r == 0)
            r2 = -1;
        if (s1 > 0 && r == 3)
            r2 = 1;
        s32 dy = r2 + 4;
        s32 dx = s1 + 4;
        q = (q + dy) % 4;
        r = (r + dx) % 4;
        ctx->cursor = q * 4 + r;
    }
    StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

s32 SetPadSelectFlags(s32 n);
void ClearPadSelectFlags(u32 mask);
void ResetPadStepRepeat(PadRecord* p);
void SetGridSelectorOpen(T217D_1330* self, s32 flag)
{
    if ((flag != 0) != (self->open == 0)) {
        return;
    }
    if (flag != 0) {
        s32 bit = 15;
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
        self->vt->m14(self);
        s32 mask = TestGridEntryBit(15);
        GameProgress* g = g_saveData;
        for (; bit > 0; bit--) {
            if (g->u19F4 & mask) {
                break;
            }
            mask >>= 1;
        }
        self->cursor = bit;
    } else {
        ClearPadSelectFlags(1);
        self->vt->m15(self);
    }
    self->open = flag;
}

void PushFontScale(Font* font, f32 x, f32 y);
// One scale for both axes: the argument goes straight into $f12 and $f13 (an inline's unmodified
// parameter is its constant), so no pseudo of the push's 1.3 is left for the loop's 1.3 to copy.
inline void PushUniformFontScale(Font* font, f32 s) { PushFontScale(font, s, s); }
struct Font;
struct PacketWriter;
struct StringLayout;
struct Vec4U;
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);
const char* GetMovieTitle(s32 index);
void DrawLineSegment(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, void* color, s32 flag);
void DrawGridSelector(T217D_1330* self)
{
    T217D_Word tmp;
    CaptionLayout out;

    tmp = self->colorWord;
    ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
    f32 p = self->w;
    f32 q = self->h;
    s32 held = tmp.v;
    out.Pos(self->x, self->y);
    out.Size(p, q);
    {
        // The colour word's slot, reused below for the frame's own colour; its address is named
        // (retail computes it into a register in this block, which gcse then reuses for the
        // string and the line's colour at the same offset).
        T217D_Word slot;
        slot.v = held;
        s32* color = &slot.v;
        out.Color(color);
        out.FlagA(1);
        out.FlagB(0);
        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            CaptionDrawer::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
    }
    const char* title = "???";
    if (TestGridEntryBit(self->cursor) != 0)
        title = GetMovieTitle(self->cursor);
    CaptionLayout* o = &out;
    f32 half = 0.5f;
    DrawFontString(self->font, title, (StringLayout*)o, 0, &g_gsPacketWriter);
    f32 left = 18.0f;
    f32 gap = 12.0f;
    Font* f = GetFontById(4);
    PushUniformFontScale(f, 1.3f);
    f32 cellW = f->Width('_');
    f32 cellH = (f32)f->height * f->sy;
    f32 y0 = self->y + (f32)self->font->height * self->font->sy + gap + cellH * half;
    f32 x0 = self->x + left + cellW * half;
    f32 dx = f->Width('_') + left;
    f32 dy = (f32)f->height * f->sy + gap;
    out.w = 0;
    out.h = 0;
    o->hAlign = 1;
    o->vAlign = 1;
    for (s32 i = 0; i < 4; i++) {
        f32 y = y0 + (f32)i * dy;
        for (s32 j = 0; j < 4; j++) {
            f32 x = x0 + (f32)j * dx;
            s32 n = i * 4 + j;
            char s[2] = { TestGridEntryBit(n) != 0 ? 'a' + n : '_', 0 };
            out.x = x;
            out.y = y;
            f32 k = 1.0f;
            if (n == self->cursor)
                k = (k - (Sine(g_gameClock[4] * 10.0f) * 0.5f + 0.5f)) * 0.1f + k;
            f32 v = self->blend * (k * 1.3f);
            PushFontScale(f, v, v);
            DrawFontString(f, s, (StringLayout*)&out, 0, &g_gsPacketWriter);
            PopFontScale(f);
        }
    }
    PopFontScale(f);
    s32 y = (s32)(((self->y + (f32)self->font->height * self->font->sy + -1.0f) * 0.45454547f + 1936.0f) * 16.0f);
    T217D_Word slot = *(T217D_Word*)((u8*)&D_002629A8 + 0x18);
    DrawLineSegment((s32)((self->x + 1728.0f) * 16.0f), y, 0, (s32)((self->x + self->w + 1728.0f) * 16.0f), y, 0,
                    &slot, 0);
}

// The file's .data, in retail's order from 0x262718. The two styles are built by the static
// initialiser GCC writes for them (func_0016C360); their bytes are zero until then.
// The rodata from 0x24A7A0 is func_0016AF80's strings ("" to the mission prompt) and
// func_0016BEA0's "???", all literals.
extern "C" void* FillMemory(void* p, s32 value, s32 size);

struct BoxStyle {
    void* font;
    u8 f4;
    f32 paddingX;
    f32 paddingY;
    f32 scaleX;
    f32 scaleY;
    u32 color;
    BoxStyle(f32 w, f32 h)
    {
        FillMemory(this, 0, 0x1C);
        f4 = 0x2D;
        paddingX = w;
        paddingY = h;
        scaleX = 0.3f;
        scaleY = 0.3f;
        color = 0xFF7D4B00;
    }
};

ChoiceTable g_partHolderLinks = {
    { { 2, 0x51A, 0x2D0 }, { 2, 0x51B, 0x2D4 }, { 2, 0x51C, 0x2D8 }, { 2, 0x51D, 0x2DC },
      { 2, 0x51E, 0x2E0 }, { 2, 0x51F, 0x2E4 }, { 2, 0x520, 0x2E8 }, { 2, 0x521, 0x2EC },
      { 2, 0x522, 0x2F0 } },
    0
};
ChoiceEntry g_currentPlacedObjectLinks[18] = {
    { 0, 0x4F9, 0x2DC }, { 0, 0x4FA, 0x2E4 }, { 0, 0x4FB, 0x2EC }, { 1, 0x4FC, 0x2F4 },
    { 0, 0x50B, 0x328 }, { 0, 0x50C, 0x32C }, { 0, 0x50D, 0x330 }, { 0, 0x50E, 0x334 },
    { 0, 0x50F, 0x338 }, { 1, 0x510, 0x310 }, { 1, 0x511, 0x314 }, { 1, 0x512, 0x318 },
    { 1, 0x513, 0x31C }, { 1, 0x514, 0x320 }, { 7, 0x33B, 0x33C }, { 7, 0x33C, 0x340 },
    { 7, 0x33D, 0x344 }, { 7, 0x33E, 0x348 }
};
ChoiceKeys D_00262860[6] = {
    { 0x4FF, 0x505 }, { 0x500, 0x506 }, { 0x501, 0x507 }, { 0x502, 0x508 }, { 0x503, 0x509 },
    { 0x504, 0x50A }
};
ChoiceSound D_00262890[6] = {
    { { 0, 0, 0, 0, 0, 0, 0, 0 } },
    { { 0x635DE216, 0x4EC49A4B, 0xE334472E, 0xCEF69512, 0x21FD26D6, 0x635CED13, 0xE33445A7, 0x4EC400FB } },
    { { 0x3FB4CB9D, 0xE4C59CDC, 0xB54DAA16, 0x74DAA291, 0x4E0ADF39, 0x3FB04A25, 0xB54DA89D, 0xE4C5FF1C } },
    { { 0x51EAF76B, 0xB417FD43, 0x999B48BC, 0xA609B70E, 0x7503D2C5, 0x51EAB865, 0x999B4A34, 0xB41790D3 } },
    { { 0xA46F3D2E, 0x368721CE, 0xF314B84E, 0x702E7249, 0x5011BB12, 0xA47BDDCC, 0xF314BAC4, 0x3687A2FE } },
    { { 0x4BEF3327, 0x61E51B24, 0x2E2955B0, 0xFEF61D5D, 0x4AC1B015, 0x4BE71C67, 0x2E29573C, 0x61E5EF04 } }
};
ChoiceSound D_00262950 = { { 0xAD5AA16C, 0xC4D11624, 0x183E0989, 0x9870DBBF, 0xC74A50B2, 0xAD59F526, 0x183E0BF2, 0xC4D06934 } };
// Six words of floats; the code reads only the first (func_0016B300, func_0016B4A0).
f32 D_00262970 = 20.0f;
f32 D_00262974 = 0.5f;
f32 D_00262978 = 2.0f;
f32 D_0026297C = 0.0f;
f32 D_00262980 = 0.1f;
f32 D_00262984 = 0.0f;
BoxStyle D_00262988(2.0f, 1.0f);
f32 D_002629A4 = 0.5f;
BoxStyle D_002629A8(2.0f, 1.0f);  // D_002629C0, which func_0016BEA0 reads, is its colour f18

// The static initialiser above (func_0016C360) is followed in retail by 12 bytes the linker left
// of a setter this file wrote out, then the file's _GLOBAL_$I$ (func_0016C450).
LINKER_REMNANT_AFTER_INIT(func_0016C440);
