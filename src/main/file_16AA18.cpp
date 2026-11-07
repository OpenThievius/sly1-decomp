// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
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

extern f32 D_0026185C[];
extern f32 D_00261868;
extern s32 D_002623CC;
extern u8 D_00264A40[];
extern s32 D_0026FCF0;
extern u8 D_00275BC0[];
typedef void (*VFn_16A5F0)(void* self, void* a);
struct Ent_262718 { s32 a; s32 b; s32 c; };
struct Tab_262718 { Ent_262718 e[9]; s32 end; };
extern Tab_262718 D_00262718;
struct Cand_16AB38 {
    u8 pad[0x304];
    s32* flagp;
};
struct Pair_16AB38 {
    StateTrigger* src;
    StateTrigger* dst;
};
struct Self_16AB38 {
    u8 pad0[0x2DC];
    Pair_16AB38 p[4];
    s32 cur;
    s32 sel;
    u8 pad1[4];
    Cand_16AB38* chosen;
    u8 pad2[4];
    StateTrigger* objs[5];
    u8 pad3[0x18];
    Cand_16AB38* cands[4];
};
struct SelEnt_16AB38 {
    s32 id;
    s32 pad;
};
struct Obj_16AED8Glob { u8 pad0[0x30]; s32 f30; };
struct Ent_262788 { s32 a; s32 b; s32 c; };
extern Ent_262788 D_00262788[18];
struct Pair_16AF80 {
    u8 pad0[0x28];
    s32 f28;
    u8 pad1[4];
    s32 f30;
};
struct Ctx_16AF80 {
    u8 pad0[0x2D0];
    s32 f2D0;
    u8 pad1[0xC];
    Pair_16AF80* f2E0;
    u8 pad2[0x1C];
    s32 f300;
};
struct Obj_16B0F8 { u8 pad0[0x2D0]; s32 f2D0; u8 pad1[0x28]; s32 f2FC; };
struct Obj_16B190 {
    u8 pad0[0x2D0];
    s32 f2D0;
    u8 pad1[0x24];
    void* f2F8;
    u8 pad2[4];
    s32 f300;
    u8 pad3[0x20];
    void* table[1];
};
struct Rec_16B190 {
    s32 f0;
    s32 f4;
    u8 pad[0x14];
    s32 f1C;
};
struct Tab_16B300 { s32 a; s32 b; };
extern Tab_16B300 D_00262860[6];
struct Slot_16B300 { u8 pad[0x20]; };
struct Slot_262890 { u32 w[8]; };
extern Slot_262890 D_00262890[6];
extern Slot_262890 D_00262950;
struct Self_16B300 {
    u8 pad0[0x2D0]; s32 f2D0; s32 f2D4; f32 f2D8; u8 pad1[4]; void* f2E0;
    u8 pad2[0x300 - 0x2E4]; s32 f300;
};
extern f32 D_00261858[];
extern f32 D_00262970;
extern s32 D_0026FCF4;
struct Style_16C360;
extern Style_16C360 D_00262988;
struct Sub_16B580 { u8 pad0[0x28]; s32 f28; s32 f2C; s32 f30; };
struct Obj_16B580 {
    u8 pad0[0x2D0];
    s32 f2D0;
    s32 f2D4;
    f32 f2D8;
    u8 pad2DC[4];
    Sub_16B580* f2E0;
    u8 pad2E4[0x308 - 0x2E4];
    void* f308;
    u8 pad30C[0x33C - 0x30C];
    void* f33C;
};
extern s32 D_00272420;
struct Node_16B7A8 {
    u8 pad0[0x2D0];
    s32 f2D0;
};
struct Out_16B860;
void func_00137228(Out_16B860* out, f32 x, f32 y);
void func_00137238(Out_16B860* out, f32 x, f32 y);
void func_00137248(Out_16B860* out, s32* value);
void func_00137260(Out_16B860* out, s32 flag);
void func_00137268(Out_16B860* out, s32 flag);
struct Out_16B860 {
    u8 b[32];
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};
struct Hd_16B860 {
    static void Draw(Font** h, Out_16B860* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};
extern Style_16C360 D_002629A8;
struct Tag_16BBA8;
struct Bits_16BBA8;
struct Group_16BBA8;

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
u32 func_001601D8(s32 idx);
u32* func_00160810(s32 idx);
void func_0016AA18(PartHolderObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 9, &g_partHolderLinks);

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

StateTrigger* func_001B6290(StateTrigger* o, s32 a, s32 b, s32 c);
s32 func_001602A0();
void func_0016B300(Self_16AB38* self, s32 idx, s32 z);
void func_001B6628(StateTrigger* o, s32 id);
void func_001E9498(u8* a, u8* b);
void func_0016AB38(Self_16AB38* self)
{
    if (self->p[0].src) self->p[0].dst = CreateStateWalker(self->p[0].src, 0, -1, 0);
    if (self->p[1].src) self->p[1].dst = CreateStateWalker(self->p[1].src, 0, -1, 0);
    if (self->p[2].src) self->p[2].dst = CreateStateWalker(self->p[2].src, 0, -1, 0);
    if (self->p[3].src) self->p[3].dst = CreateStateWalker(self->p[3].src, 0, -1, 1);
    self->cur = 5;
    for (;;) {
        s32 c = self->cur;
        if (c < 3) break;
        if (g_saveData->levels[c - 2].f448 & 0x20) break;
        s32 d = c - 1;
        if (g_saveData->levels[d].f448 & 1) break;
        self->cur = d;
    }
    for (s32 i = 1; i <= self->cur; i++) {
        StateTrigger* o = self->objs[i - 1];
        if (o && (g_saveData->levels[i].f448 & 1)) o->desc->m02(o);
    }
    self->chosen = 0;
    for (s32 i = 0; i < 4; i++) {
        Cand_16AB38* c = self->cands[i];
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
                self->chosen = c;
                break;
            }
        }
    }
    s32 idx;
    if (self->chosen) {
        idx = 0;
    } else {
        s32 a = g_previousLevelIndex;
        if (a != -1 && (g_saveData->levels[a].f448 & 1)) {
            idx = a;
        } else {
            s32 c = self->cur;
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
    if (self->p[2].dst || self->p[3].dst) {
        idx = self->cur;
        if (idx != 5) {
            self->sel = idx;
        } else {
            GameProgress* t = g_saveData;
            if (t->levels[4].f448 & 0x20) self->sel = 0;
            else if (t->levels[5].f448 & 1) self->sel = 0;
            else self->sel = idx;
        }
        if (self->p[2].dst) TeleportStateWalker(self->p[2].dst, ((SelEnt_16AB38*)&D_00262860)[self->sel].id);
        if (self->p[3].dst) TeleportStateWalker(self->p[3].dst, ((SelEnt_16AB38*)&D_00262860)[self->sel].id);
    }
    PushStackElement(g_elementStack, (u8*)&D_0026FA90);
}

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001E96F8(void* obj, s32 mode);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_0016AED8(CurrentPlacedObject* self)
{
    StartPlacedObject(self);
    self->flags = (self->flags & ~(3ULL << 40)) | (1ULL << 40);
    g_currentPlacedObject = (s32)self;
    ((Obj_16AED8Glob*)g_elementStack)->f30 = 2;
    SetElementStackState(g_elementStack, 2);
    ResolveObjectLinks(self, 0x12, g_currentPlacedObjectLinks);
    self->f2D0 = -1;
    AppendQueuedCall(self->world, (void*)SetupCurrentObjectChoices, self, 0, 0);
}

void func_001AD1E8(T217D_3D0* self);
void func_0016AF80(Ctx_16AF80* self)
{
    s32 s1 = 0;
    Pair_16AF80* p = self->f2E0;

    if (p->f28 != p->f30) {
        D_0026F138.vt->m08(&D_0026F138, "");
    } else if (self->f2D0 == 0) {
        D_0026F138.vt->m08(&D_0026F138, "Bentley");
    } else {
        s32 flags = g_saveData->levels[self->f2D0].f448;
        if (flags & 1) {
            SetElementTextFromIndexedCounts(&D_0026F138);
        } else if (self->f2D0 == self->f300) {
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

s32 func_0016EC98(void* p);
void func_0016B300(Obj_16B0F8* self, s32 idx, s32 zero);
void func_0016B0F8(Obj_16B0F8* self, void* a1)
{
    s32 n = self->f2D0;
    s32 r = GetPadHorizontalStep(a1);
    f32 f = (f32)r;
    s32 v = self->f2FC;
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

void* func_00160180(s32 key);
void func_00160340(s32 idx);
void func_0012C7B0(void* a, void* b, s32 c, s32 d, f32 fa, f32 fb);
s32 func_0012C9A8(void* a);
void func_001F0428(void* a, s32 b, s32 c);
void func_001E9570(void* p);
void func_001B64D8(void* a, s32 b);
void func_0016B300(void* self, s32 idx, s32 flag);
void func_0016B190(Obj_16B190* self)
{
    s32 callB = 1;
    s32 idx = self->f2D0;
    if (idx != 0) {
        if ((g_saveData->levels[idx].f448 & 1) == 0) {
        if (idx != self->f300) {
            s32 s2 = 1;
            void* elt;
            u8* table = (u8*)self + 0x324;
            MarkProgressStageFlag(idx);
            elt = *(void**)(table + (self->f2D0 << 2));
            if (elt != 0) {
                CreateAnimationPlayerWithoutPresetTargets(elt, self, 0, 0, 0.0f, 1.0f);
                elt = *(void**)(table + (self->f2D0 << 2));
                if (elt != 0 && func_0012C9A8(elt) != 0) {
                    goto tail;
                }
            }
            {
                Rec_16B190* a = (Rec_16B190*)LookupEntryById(self->f2D0 << 8);
                s32 flag = 0;
                if (a != 0) {
                    flag = (a->f4 != a->f1C);
                }
                if (flag) {
                    StartObjectFade(a, -1, 1);
                } else {
                    s2 = 0;
                }
            }
        tail:
            if (s2) {
                PopStackElement(g_elementStack);
            }
        } else {
            void* h = self->f2F8;
            callB = 0;
            if (h != 0) {
                { SetStateWalkerTarget(h, D_00262860[idx].b); }
            }
        }
        }
    }
    if (callB) {
        SetCurrentObjectChoice(self, self->f2D0, 1);
    }
}

// NEAR: only the order of `addiu v0,s5,lo(D_00261858)` vs `sw s4,0x2D4(s3)` differs (2 instrs swapped)

void func_001BE728(Slot_16B300* s);
s32 func_001BE980(void);
void func_001B6628(void* h, s32 arg);
void func_001B64D8(void* h, s32 arg);
void func_0016B300(Self_16B300* self, s32 a, s32 b)
{
    if (a == self->f2D0 && b == self->f2D4) return;
    if (a != self->f300 && a > 0) {
        Slot_16B300* slot = 0;
        if (g_saveData->levels[a].f448 & 1) {
            s32 fl = g_saveData->f19EC;
            if (!(fl & 2)) {
                g_saveData->f19EC = fl | 2;
                slot = (Slot_16B300*)&D_00262950;
            }
        } else {
            f32 t = g_gameClock[1];
            if (D_00262970 <= t - D_0026FA90.lastAt) {
                D_0026FA90.lastAt = t;
                slot = (Slot_16B300*)((u8*)D_00262890 + (a << 5));
            }
        }
        if (slot) {
            OpenKeyRecord(slot);
            D_0026FCF4 = HasStreamVoice();
        }
    }
    void* h = self->f2E0;
    if (h) {
        if (self->f2D0 == -1) {
            if (a != 0) {
                TeleportStateWalker(h, D_00262860[a].b);
                SetStateWalkerTarget(self->f2E0, D_00262860[a].a);
            }
        } else {
            SetStateWalkerTarget(h, *(s32*)((u8*)D_00262860 + (a * 8 + b * 4)));
        }
    }
    self->f2D0 = a;
    self->f2D4 = b;
    self->f2D8 = g_gameClock[1];
}

s32 func_0015C188(s32 index);
Font* func_0015C1C0(s32 index);
void func_0016B4A0(T217D_12E0* self)
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

void* func_0015A448(void* obj, s32 id, s32 flags);
void func_001F4ED0(void* p);
void func_0016B520(T217D_12E0* self)
{
    if (self->open != 0) {
        void* p = FindFirstObjectByIdMode4(g_currentWorld, 0x4FD, 0);
        if (p != 0) {
            PushObjectCameraController(p);
        }
    }
}

void func_0016B560(T217D_12E0* self)
{
    UpdateScreenElementSlide(self);
}

// The object the element shows (a view of it: its mode at +0x2D0, its animation clock at +0x2D8).
s32 func_001BE810(void);
s32 func_0011CE30(void);
s32 func_001BE980(void);
void func_0018C7F8(u8* p);
void func_001518B8(void* p);
void func_0016AF80(Obj_16B580* o);
void func_001E9498(u8* a, void* b);
void func_0016EC20(PadRecord* a, s32 mask);
void func_00194D30(T217D_6D0* a, s32 b, s32 c);
void func_0016B190(Obj_16B580* o);
void func_0016B0F8(Obj_16B580* o, PadRecord* a);
void func_0016B580(T217D_12E0* self, PadRecord* arg)
{
    if (self->node == 0) {
        return;
    }
    if (((Obj_16B580*)self->node)->f2E0 == 0) {
        return;
    }
    if (self->sound != 0) {
        if (func_001BE810() != 0) {
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
    Obj_16B580* o = (Obj_16B580*)self->node;
    Sub_16B580* p = o->f2E0;
    if (o->f308 != 0) {
        if (o->f308 == o->f33C) {
            StartMemoryCardSave(g_memoryCard);
        }
        ChooseStepSequenceState(o->f308);
        o->f308 = 0;
    }
    ShowCurrentObjectCaptions(o);
    f32 delay = 0.3f;
    if (o->f2D4 == 1 && (p->f28 == p->f30 || delay <= g_gameTime[0] - o->f2D8)) {
        s32 idx = o->f2D0;
        if (idx == 0) {
            if (D_0026FD00.mode != 0) {
                return;
            }
            PushStackElement(g_elementStack, &D_0026FD00);
            return;
        }
        if (g_mapScreenList.mode != 0) {
            return;
        }
        g_mapScreenList.current = g_mapScreenList.nodes[idx];
        PushStackElement(g_elementStack, &g_mapScreenList);
        return;
    }
    if (p->f28 != p->f30) {
        return;
    }
    if ((arg->flags & 0x800) || (arg->f14 == 1 && 5.0f <= g_gameTime[0])) {
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

void func_0016B300(void* self, s32 idx, s32 flag);
s32 func_0016E0F0(s32 bits);
void func_0016EC88(void* p);
void func_001BE998(void);
void func_0016E118(s32 n);
void func_0016B7A8(T217D_12E0* self, s32 v)
{
    s32 flag = (v != 0);
    if (flag != (self->open == 0)) {
        return;
    }
    if (v != 0) {
        SetCurrentObjectChoice(self->node, ((Node_16B7A8*)self->node)->f2D0, 0);
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

f32 func_00205400(f32 x);
void func_0015C8B8(Font* font, f32 a, f32 b);
void* func_0015DB28(void* out, void* p, Font* font);
void func_0015E318(void* a, void* b, s32 c, void* d);
void func_0015C900(Font* font);
void func_0016B860(T217D_12E0* self)
{
    T217D_Word tmp;
    Out_16B860 out;
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
            Hd_16B860::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        f32 r = Sine(g_elapsedTime * 10.0f);
        f32 t = r * 0.5f + 0.5f;
        f32 k = (1.0f - t) * 0.9f + t;
        f32 v = self->scale * k;
        PushFontScale(self->font, v, v);
        InitTextReader(loc, &self->text[0], self->font);
        DrawAlignedText(loc, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

s32 func_0015C188(s32 k);
void func_0015C8B8(Font* font, f32 x, f32 y);
void func_0015C900(Font* font);
void func_0016BA40(T217D_1330* self)
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

u32 func_0016BB78(u32 bit)
{
    u32 mask;
    if (bit >= 16) {
        mask = 0;
    } else {
        mask = 1 << bit;
    }
    return g_saveData->u19F4 & mask;
}

void func_0016EC20(PadRecord* self, s32 mask);
void func_001E9570(Group_16BBA8* g);
u32 func_0016BB78(Bits_16BBA8* bit);
void func_0018E4C0(Bits_16BBA8* bit);
void func_001BFCD8(Tag_16BBA8* a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 r2, s32 a5);
s32 func_0016EC98(PadRecord* p);
s32 func_0016EED0(PadRecord* p);
void func_0016BBA8(T217D_1330* ctx, PadRecord* o)
{
    s32 s1;
    s32 r2;

    if ((o->flags & 0x9B0) != 0 || (o->f14 == 1 && 5.0f <= g_gameTime[0])) {
        ClearPadPressedBits(o, 0x9B0);
        PopStackElement((Group_16BBA8*)g_elementStack);
        return;
    }
    if ((o->flags & 0x40) != 0) {
        ClearPadPressedBits(o, 0x40);
        if (TestGridEntryBit((Bits_16BBA8*)ctx->cursor) != 0) {
            QueueMovieByIndex((Bits_16BBA8*)ctx->cursor);
            return;
        }
        StartSoundEffect((Tag_16BBA8*)0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s1 = GetPadHorizontalStep(o);
    r2 = GetPadVerticalStep(o);
    if (s1 == 0 && r2 == 0) {
        return;
    }
    o->f30 = g_gameClock[4] + o->f34;
    o->f38 = g_gameClock[4] + o->f3C;

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
    StartSoundEffect((Tag_16BBA8*)0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

s32 func_0016E0F0(s32 n);
void func_0016E118(s32 n);
void func_0016EC88(void* p);
s32 func_0016BB78(s32 n);
void func_0016BDD0(T217D_1330* self, s32 flag)
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

INCLUDE_RODATA(D_0024A7D8);
INCLUDE_ASM(func_0016BEA0);

// The file's .data, in retail's order from 0x262718. The two styles are built by the static
// initialiser GCC writes for them (func_0016C360); their bytes are zero until then.
// The rodata from 0x24A7A0 is func_0016AF80's strings ("" to the mission prompt) and
// func_0016BEA0's "???", all literals.
void func_001F5C0C(void* p, s32 zero, s32 size);

struct Style_16C360 {
    void* f0;
    u8 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 f18;
    Style_16C360(f32 w, f32 h)
    {
        FillMemory(this, 0, 0x1C);
        f4 = 0x2D;
        f8 = w;
        fC = h;
        f10 = 0.3f;
        f14 = 0.3f;
        f18 = 0xFF7D4B00;
    }
};

Tab_262718 D_00262718 = {
    { { 2, 0x51A, 0x2D0 }, { 2, 0x51B, 0x2D4 }, { 2, 0x51C, 0x2D8 }, { 2, 0x51D, 0x2DC },
      { 2, 0x51E, 0x2E0 }, { 2, 0x51F, 0x2E4 }, { 2, 0x520, 0x2E8 }, { 2, 0x521, 0x2EC },
      { 2, 0x522, 0x2F0 } },
    0
};
Ent_262788 D_00262788[18] = {
    { 0, 0x4F9, 0x2DC }, { 0, 0x4FA, 0x2E4 }, { 0, 0x4FB, 0x2EC }, { 1, 0x4FC, 0x2F4 },
    { 0, 0x50B, 0x328 }, { 0, 0x50C, 0x32C }, { 0, 0x50D, 0x330 }, { 0, 0x50E, 0x334 },
    { 0, 0x50F, 0x338 }, { 1, 0x510, 0x310 }, { 1, 0x511, 0x314 }, { 1, 0x512, 0x318 },
    { 1, 0x513, 0x31C }, { 1, 0x514, 0x320 }, { 7, 0x33B, 0x33C }, { 7, 0x33C, 0x340 },
    { 7, 0x33D, 0x344 }, { 7, 0x33E, 0x348 }
};
Tab_16B300 D_00262860[6] = {
    { 0x4FF, 0x505 }, { 0x500, 0x506 }, { 0x501, 0x507 }, { 0x502, 0x508 }, { 0x503, 0x509 },
    { 0x504, 0x50A }
};
Slot_262890 D_00262890[6] = {
    { { 0, 0, 0, 0, 0, 0, 0, 0 } },
    { { 0x635DE216, 0x4EC49A4B, 0xE334472E, 0xCEF69512, 0x21FD26D6, 0x635CED13, 0xE33445A7, 0x4EC400FB } },
    { { 0x3FB4CB9D, 0xE4C59CDC, 0xB54DAA16, 0x74DAA291, 0x4E0ADF39, 0x3FB04A25, 0xB54DA89D, 0xE4C5FF1C } },
    { { 0x51EAF76B, 0xB417FD43, 0x999B48BC, 0xA609B70E, 0x7503D2C5, 0x51EAB865, 0x999B4A34, 0xB41790D3 } },
    { { 0xA46F3D2E, 0x368721CE, 0xF314B84E, 0x702E7249, 0x5011BB12, 0xA47BDDCC, 0xF314BAC4, 0x3687A2FE } },
    { { 0x4BEF3327, 0x61E51B24, 0x2E2955B0, 0xFEF61D5D, 0x4AC1B015, 0x4BE71C67, 0x2E29573C, 0x61E5EF04 } }
};
Slot_262890 D_00262950 = { { 0xAD5AA16C, 0xC4D11624, 0x183E0989, 0x9870DBBF, 0xC74A50B2, 0xAD59F526, 0x183E0BF2, 0xC4D06934 } };
// Six words of floats; the code reads only the first (func_0016B300, func_0016B4A0).
f32 D_00262970 = 20.0f;
f32 D_00262974 = 0.5f;
f32 D_00262978 = 2.0f;
f32 D_0026297C = 0.0f;
f32 D_00262980 = 0.1f;
f32 D_00262984 = 0.0f;
Style_16C360 D_00262988(2.0f, 1.0f);
f32 D_002629A4 = 0.5f;
Style_16C360 D_002629A8(2.0f, 1.0f);  // D_002629C0, which func_0016BEA0 reads, is its colour f18

// The static initialiser above (func_0016C360) is followed in retail by 12 bytes the linker left
// of a setter this file wrote out, then the file's _GLOBAL_$I$ (func_0016C450).
LINKER_REMNANT_AFTER_INIT(func_0016C440);
