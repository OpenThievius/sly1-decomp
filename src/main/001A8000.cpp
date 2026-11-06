// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "world.h"
#include "object_pool.h"
#include "screen_element.h"
#include "v24a2.h"
#include "shapes.h"
#include "game_clock.h"
#include "game_progress.h"
#include "text_reader.h"
#include "globals.h"

// The font object's calls.
V24A2* func_0015C1C0(s32 k);
void func_0015C8B8(V24A2* font, f32 x, f32 y);
f32 func_0015C418(V24A2* font, void* text);
void func_0015C638(V24A2* font, void* text, void* out, s32 zero, void* d);
void func_0015C900(V24A2* font);
void* func_0015DB28(void* out, void* text, V24A2* font);
void func_0015E318(void* buf, void* out, s32 zero, void* d);

void func_00182ED0(void* self);
void func_001A93C8(void* self);

void func_001A80E0(ObjectPool* self)
{
    UnregisterObject(self);
    ClearObjectPoolChoice(self);
}

void func_001F3C08(void* a, f32* out);
void func_00128150(int a, int b, void* c, f32* d);
f32 func_00205778(f32 x, f32 y);

void func_001A97C8(u8* self, f32* out, int x)
{
    f32 v[12];
    if (*(void**)(self + 0x10) != 0) {
        GetObjectWorldRotation(*(void**)(self + 0x10), v);
        func_00128150(0, x, v, v);
        *out = func_00205778(v[1], v[0]);
    } else if (*(u8**)(self + 0x14) != 0) {
        func_00128150(0, x, *(u8**)(self + 0x14) + 0x110, v);
        *out = func_00205778(v[1], v[0]);
    } else {
        *out = *(f32*)(self + 0x8);
    }
}

void func_001C7CB8(void* self);
void func_0012E760(void* obj);

void func_001A9A40(C0D* self)
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

void func_001AA788(ScreenElement* self, f32 v)
{
    self->scale = v;
}

void func_001AA8B8(ScreenElement* self, f32 v)
{
    self->holdTime = v;
}

extern f32 D_0026185C;
extern f32 D_00261860;

void func_001AB980(T217D_510* self, f32 value);

void func_001AB660(T217D_510* self)
{
    UpdateScreenElementSlide(self);
    if (self->mode == 0) {
        return;
    }
    if (self->state == 0) {
        s32 close = (1.0f <= g_gameTime - self->stateSince);
        if ((u32)(self->mode - 1) < 2) {
            if (self->f290 != 0 || close) {
                self->vt->m15(self);
            }
        }
    } else {
        StepTimer(self, g_frameDt);
    }
}

void func_001ABE20(T217D_510* self, s32 state)
{
    if (self->state != state) {
        self->state = state;
        self->stateSince = g_gameTime;
    }
}

extern s32 D_0026227C;

void func_001AA268(ScreenElement* self)
{
    s32 value = g_defaultFont;
    u32 flags = 0xFF808080;
    self->font = (V24A2*)value;
    self->scale = 1.0f;
    self->color = flags;
    self->text[0] = 0;
}

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);


void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);

void func_001AA790(ScreenElement* self)
{
    u8 out[32];
    s32 tmp;
    void* handle;
    f32 x;

    if (self->text[0] != 0) {
        f32 p = self->w;
        f32 q = self->h;
        s32 held = self->color;
        func_00137228(out, self->x, self->y);
        func_00137238(out, p, q);
        tmp = held;
        func_00137248(out, &tmp);
        func_00137260(out, 0);
        func_00137268(out, 0);

        handle = self->frame;
        if (handle != 0) {
            void* obj = *(void**)handle;
            if (obj != 0) {
                void* vt = *(void**)((u8*)obj + 76);
                VirtualCall_1AA790 fn = *(VirtualCall_1AA790*)((u8*)vt + 76);
                s16 adj = *(s16*)((u8*)vt + 72);
                fn((u8*)obj + adj, handle, out, &g_gsPacketWriter);
            }
        }
        x = self->scale;
        PushFontScale(self->font, x, x);
        DrawFontString(self->font, &self->text[0], out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

f32 func_001AA898(ScreenElement* self)
{
    return self->inTime;
}

f32 func_001AA8A0(ScreenElement* self)
{
    return self->holdTime;
}

f32 func_001AA8A8(ScreenElement* self)
{
    return self->outTime;
}

void func_001C72A0(C0D* self);
void func_001DDC38(void* sub, C0D* self);

void func_001A98F8(C0D* self)
{
    StartAgent(self);
    func_001DDC38(self->world, self);
}

s32 func_001DDA80(void* sub);

s32 func_001A9928(C0D* self)
{
    if (func_001DDA80(self->world) != 0)
        return 0;
    return self->fC24;
}

typedef void* (*VFn_1A9960)(void* self);
void func_001C8C08(C0D* self);
void func_001C8418(C0D* self, void* p);

void func_001A9960(C0D* self)
{
    UpdateAgentGoal(self);
    if (self->f724 == 0x10) {
        void* r = ((VFn_1A9960*)self->desc)[102](self);
        if (r != 0)
            func_001C8418(self, (u8*)r + 0x140);
    }
}

void func_001C8E28(C0D* self);
void func_001C8BC0(C0D* self);

void func_001A99B8(C0D* self)
{
    UpdateAgentState(self);
    if (self->f724 == 0x10)
        func_001C8BC0(self);
}

void func_001AB958(T217D_510* self)
{
    self->f290 = 1;
    SetTimerState(self, 0);
}

f32 func_001ABE40(void)
{
    return 0.0f;
}

f32 func_001ABE50(void)
{
    return 0.0f;
}

f32 func_001ABE60(void)
{
    return 0.0f;
}

extern u8 D_00264A40[];

void func_001C91C8(C0D* self);
void func_001603E8(s32 n);
void func_0018C7F8(u8* p);

void func_001A99F8(C0D* self)
{
    EnterAgentState(self);
    if (self->f724 == 0xB) {
        MarkLevelDone(4);
        StartMemoryCardSave(g_memoryCard);
    }
}

extern T217D_2E0 D_0026E248;

s32 func_001E9970(void);

void func_001A9A98(void)
{
    if (AreMenusAndFadeClear()) {
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    } else {
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
    }
}

void func_001A9C58(C0D* self, s32 a, s32 b, s32 c)
{
    self->fC14 = a;
    self->fC18 = b;
    self->fC1C = c;
}

struct Tab_26C3E0 { T217D_Place e[37]; s32 end; };
extern Tab_26C3E0 D_0026C3E0;
extern u8 D_00261868[];

void func_001AA1F0(ScreenElement* self, s32 index)
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

void* func_0018D5C0(u32 n);

void* func_001A8110(ObjectPool* self)
{
    if (self->sub == 0) {
        Sub8C* p = (Sub8C*)AllocateZeroedFrontMemory(0x20);
        self->sub = p;
        *(ObjectPool**)p = self;
    }
    return self->sub;
}

void func_001AA8B0(ScreenElement* self, f32 v)
{
    self->inTime = v;
}

void func_001AA8C0(ScreenElement* self, f32 v)
{
    self->outTime = v;
}

void func_00182C58(void* self);
void* func_0015A448(void* obj, s32 id, void* owner);
s32 func_001300E8(void* node, s32 kind);

void func_001A8590(ObjectPool* self)
{
    StartObject(self);
    if (self->f168 != 0) {
        return;
    }
    self->f168 = 1;
    if (self->id4C != -1) {
        void* p = func_0015A448(self->world, self->id4C, self);
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
        void* p = func_0015A448(self->world, self->id50, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 2) != 0) {
                self->fE0 = p;
            } else if (IsObjectOfKind(p, 0x75) != 0) {
                self->fE4 = p;
            }
        }
    }
    if (self->id54 != -1) {
        void* p = func_0015A448(self->world, self->id54, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 0x73) != 0) {
                self->f160 = p;
            } else if (IsObjectOfKind(p, 2) != 0) {
                self->f164 = p;
            }
        }
    }
    if (self->id58 != -1) {
        self->f5C = func_0015A448(self->world, self->id58, self);
    }
}

void func_001F5C0C(void* p, s32 value, s32 size);

void func_001A9438(ObjectPool* self)
{
    func_001F5C0C((u8*)self + 0xE0, 0, 0x70);
    V8C* t = &self->v110;
    t->a = 0;
    t->b = 1.0f;
    t->c = 0;
    self->f124 = 20000.0f;
    self->f120 = 0;
}

void func_001F5C0C(void* p, s32 value, s32 size);

void func_001A9498(u8* self)
{
    func_001F5C0C(self + 0x150, 0, 0x18);
}

f32 func_001AB5D8(void)
{
    return g_gameClock.running != 0 ? 2.5f : 0.0f;
}

void func_001A93C8(void* self);

void func_001A86F8(ObjectPool* self, s32 flag)
{
    if (flag) {
        ClearObjectPoolChoice(self);
    }
}

struct Entry_1A8718 { s32 key; s32 pad[3]; s32 flags; };

Entry_1A8718* func_001A8718(ObjectPool* table, s32 key);

void func_001A8778(ObjectPool* table, s32 key)
{
    Entry_1A8718* e = FindObjectPoolEntry(table, key);
    if (e) {
        e->flags |= 2;
    }
}

void func_001AA8C8(ScreenElement* self)
{
    self->vt->m16(self, 0);
}

void func_001AB920(T217D_510* self, f32 value)
{
    self->rate = value;
}

struct Row_1A8820 { s32 unk0; s32 itemCount; void** items; u8 pad[8]; };
s32 func_001A8820(ObjectPool* list, BaseObject* query) { for(s32 i=0;i<list->count;i++){ Row_1A8820* row=(Row_1A8820*)((u8*)list->items+i*0x14); if(row->itemCount<=0) continue; void** items=row->items; if(*(s32*)((u8*)items[0]+8) != query->id) continue; for(s32 j=0;j<row->itemCount;j++) if(query==items[j]) return 1; } return 0; }

void func_001A93C8(ObjectPool* p) { p->f48 = 0; if (p->sub != 0 && p->sub->f4 != 0) p->sub->f10 = 0; }

struct Entry_1A87E0 { s32 pad0; s32 f4; s32 pad1; s32 fC; };

Entry_1A87E0* func_001A8718(void* table, s32 key);

void func_001A87E0(void* table, s32 key, s32 value)
{
    Entry_1A87E0* e = FindObjectPoolEntry(table, key);
    if (e != 0) {
        if (value >= e->fC) {
            value = e->fC;
        }
        e->f4 = value;
    }
}

struct __attribute__((aligned(16))) Quad_1A94C0 { s32 a, b, c, d; };
struct Inner_1A94C0 {
    u8 pad0[0x110];
    Quad_1A94C0 q110;
    Quad_1A94C0 q120;
    Quad_1A94C0 q130;
    Quad_1A94C0 q140;
};
struct Obj_1A94C0 {
    void* f0;
    void* f4;
    Inner_1A94C0* f8;
    u8 pad0[4];
    Quad_1A94C0 q10;
    Quad_1A94C0 q20;
    Quad_1A94C0 q30;
    Quad_1A94C0 q40;
};

void func_001920B0(void* self, void* arg);
s32 func_001F3BD8(void* self, void* arg);
void func_001F3C08(void* self, void* arg);
void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);

void func_001A94C0(Obj_1A94C0* self, Quad_1A94C0* a1, Quad_1A94C0* a2, void* a3)
{
    if (self->f0 != 0) {
        func_001920B0(self->f0, a1);
        a2[0] = self->q20;
        a2[1] = self->q30;
        a2[2] = self->q40;
    } else if (self->f4 != 0) {
        GetObjectWorldPosition(self->f4, a1);
        GetObjectWorldRotation(self->f4, a2);
    } else {
        if (self->f8 != 0) {
            a1[0] = self->f8->q140;
            Inner_1A94C0* in = self->f8;
            a2[0] = in->q110;
            a2[1] = in->q120;
            a2[2] = in->q130;
        } else {
            a1[0] = self->q10;
            a2[0] = self->q20;
            a2[1] = self->q30;
            a2[2] = self->q40;
        }
    }
    if (a3 != 0) {
        func_00128018(0, a3, a1, a1);
        func_00128150(0, a3, a2, a2);
    }
}

void func_001AB938(T217D_510* self)
{
    SetTimerState(self, 2);
}

extern u8 D_00261868[];

void func_001AAF58(ScreenElement* self, f32* p)
{
    if (self->clock != p) {
        if (p == 0) {
            p = (f32*)g_elapsedTime;
        }
        self->since = *p;
    }
    self->clock = p;
}

void func_001AB928(T217D_510* self, T217D_510_Fn onEnd, f32 limit)
{
    self->limit = limit;
    self->onEnd = onEnd;
}

void func_001830D8(ObjectPool* self, void* o);
void* func_001A8110(void* self);
void func_00152438(void* self, s32 value);
void func_00152470(void* list, void* item);
u8* func_0018D568(s32 size, void* src);

void func_001A84C8(ObjectPool* self, ObjectPool* other)
{
    CopyObjectData(self, other);
    if (self->sub != 0 && self->sub->f4 != 0) {
        if (other->sub->f8 != 0) {
            self->sub = 0;
        } else {
            other->sub->f8 = 1;
            func_00152438((u8*)other->sub + 0x14, 0x18);
            self->sub = 0;
        }
        GetObjectPoolShare(self);
        self->sub->f4 = 1;
        self->sub->f8 = 2;
        self->sub->f14 = other;
        AppendToList((u8*)other->sub + 0x14, self->sub);
    } else {
        self->items = CopyToFrontMemory(other->count * 0x14, other->items);
    }
}

// NEAR: frame and body match; the two local slots are swapped (retail: tmp at sp+0x30, buffer at sp+0x40; ours: buffer at sp+0x30, tmp at sp+0xE0), so the frame is 0x120 not 0x130


void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);

void func_001AB198(T217D_E30* self)
{
    u8 out[0x20];
    T217D_Word packed;
    s32 held;
    s32 tmp[4];
    u8 buf[0xB0];
    f32 scale;
    f32 px;
    f32 py;
    T217D_6D0* g;

    if (self->text[0] == 0) {
        return;
    }
    g = &g_pauseMenuElement;
    scale = 1.0f;
    if (g->mode != 0) {
        scale = g->fade;
    }
    packed = self->colorWord;
    ((u8*)&packed)[3] = (u8)(s32)(scale * 255.0f);
    held = packed.v;
    px = self->w;
    py = self->h;
    func_00137228(out, self->x, self->y);
    func_00137238(out, px, py);
    tmp[0] = held;
    func_00137248(out, &tmp[0]);
    func_00137260(out, 0);
    func_00137268(out, 0);
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(buf, &self->text[0], self->font);
    DrawAlignedText(buf, out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

void func_001AA8F0(ScreenElement* self)
{
    s32 s = self->mode;
    if (s == 2) {
        goto store;
    }
    if (s < 3) {
        if (s == 0) {
            goto call;
        }
        return;
    }
    if (s != 3) {
        return;
    }
call:
    self->vt->m16(self, 1);
    return;
store:
    self->since = *self->clock;
}


struct Local_001AB710 { f32 x; f32 y; u8 pad0[0x8]; T217D_Word w10; u8 pad1[0xC]; s32 tag; u8 pad2[0xC]; T217D_Word w30; };
struct VDesc_001AB710 { u8 pad0[0x48]; s16 off48; u8 pad1[2]; void (*fn4C)(void* self, void* obj, void* out, void* d); };
struct SubObj_001AB710 { u8 pad0[0x4C]; VDesc_001AB710* desc4C; };

void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, void* p);
void func_00137260(void* out, s32 v);
void func_00137268(void* out, s32 v);

void func_001AB710(T217D_510* self)
{
    Local_001AB710 L;
    if (self->text[0] != 0) {
        f32 f234 = self->w;
        f32 f238 = self->h;
        s32 s0v = self->color;
        func_00137228(&L, self->x, self->y);
        func_00137238(&L, f234, f238);
        L.tag = s0v;
        func_00137248(&L, &L.tag);
        func_00137260(&L, 0);
        func_00137268(&L, 0);
        void* obj = self->frame;
        if (obj != 0) {
            SubObj_001AB710* sub = *(SubObj_001AB710**)obj;
            if (sub != 0) {
                VDesc_001AB710* d = sub->desc4C;
                d->fn4C((u8*)sub + d->off48, obj, &L, &g_gsPacketWriter);
            }
        }
        f32 v = self->scale;
        u8* dp = (u8*)&g_gsPacketWriter;
        PushFontScale(self->font, v, v);
        ((u8*)&L.tag)[0] = 0x54;
        ((u8*)&L.tag)[1] = 0;
        DrawFontString(self->font, &L.tag, &L, 0, dp);
        f32 r = MeasureFontString(self->font, &L.tag);
        f32 a = self->x + r;
        L.y = self->y;
        L.x = a;
        if (self->warned != 0) {
            L.w30 = self->warnColor;
            L.w10 = L.w30;
        }
        DrawFontString(self->font, (u8*)self + 9, &L, 0, dp);
        PopFontScale(self->font);
    }
}

extern void* const D_002486B0[];
extern u8 D_00262C68[];
extern u8 D_00262C70[];
extern u8 D_00262D38[];
extern u8 D_00275F80[];

void func_001EFD10(void* a, void* b);

void func_001A9FD0(void)
{
    ScreenElement** slots = (ScreenElement**)g_screenElements;
    for (s32 i = 36; i >= 0; i--) {
        ScreenElement* o = slots[i];
        o->vt->m02(o);
    }
    u8* g = g_screenFade;
    void* b;
    if (*(s32*)D_00262C68 & 4) {
        b = g_padRecord;
    } else {
        b = g_blankPadRecord;
    }
    UpdateScreenFade(g, b);
}

extern void* const D_002486B0[];

void func_001AA0C0(void)
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

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
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
extern u8 D_00275F80[];

void func_001EFCE8(void* p);

void func_001A9C68()
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
    D_0026EC70.vt = (const T217D_Vt*)D_00218330;
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

extern s8 D_00262250[];
extern u8 D_0024E879[];
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void* func_001E2138(void* dst, void* src);

void func_001AA5A0(ScreenElement* self)
{
    char buf[0x200];
    char* s = self->text;
    char* d = buf;
    if (*s != 0) {
        do {
            if (self->font->Has(*s) == 0) {
                if (GetFontById(3)->Has(*s) != 0) {
                    d += FormatToString(d, "&%c%c&.", g_fontEscapeKeys[3], *s);
                    goto next;
                }
                if (GetFontById(4)->Has(*s) != 0) {
                    d += FormatToString(d, "&%c%c&.", g_fontEscapeKeys[4], *s);
                    goto next;
                }
            }
            if (*s == 0x2F) {
                if (g_charClassFlags[s[1]] & 4) {
                    d += FormatToString(d, "^05~b2a83d/");
                    s++;
                    while (*s != 0 && (g_charClassFlags[*s] & 4)) {
                        *d = *s;
                        s++;
                        d++;
                    }
                    d += FormatToString(d, "~.^.");
                    s--;
                } else {
                    *d = *(u8*)s;
                    d++;
                }
            } else {
                *d = *(u8*)s;
                d++;
            }
        next:
            s++;
        } while (*s != 0);
    }
    *d = 0;
    CopyString(self->text, buf);
}

struct Hdr_1A8208 { u8 pad0[4]; s32 f4; s32 f8; Quad16* fC; };
struct Ent_1A8208 { s32 f0; s32 f4; void** f8; s32 fC; s32 f10; };
struct Self_1A8208 {
    u8 pad0[0x14]; void* f14; u8 pad18[0x1C];
    s32 f34; Ent_1A8208* f38; Hdr_1A8208* f3C;
};

void* func_0018D500(s32 size);
PlacedObject* func_0015A418(void* a, s32 b, s32 c, Self_1A8208* d);
void func_00152438(void* p, s32 a);
s32 func_001527D8(void* p);
PlacedObject* func_00183058(PlacedObject* a, World* b, BaseObject* c);

void func_001A8208(Self_1A8208* self)
{
    s32 i;
    if (self->f3C != 0) {
        if (self->f3C->f4 != 0) {
            self->f3C->fC = (Quad16*)AllocateFrontMemory(self->f34 << 5);
        }
    }
    for (i = 0; i < self->f34; i++) {
        Ent_1A8208* e = &self->f38[i];
        PlacedObject* obj = FindFirstObjectById(self->f14, 4, e->f0, self);
        s32 n;
        s32 cnt;
        if (obj == 0) {
            e->f4 = 0;
            continue;
        }
        if (self->f3C != 0 && self->f3C->f4 != 0) {
            s32 x = self->f3C->f8;
            if (x == 1) goto c1;
            if (x < 2) {
                if (x == 0) goto c0;
            } else if (x == 2) {
                n = 0;
                cnt = 0;
            }
            goto done;
        c0:
            self->f3C->f8 = 1;
            func_00152438((u8*)self->f3C + 0x14, 0x18);
        c1: {
                s32 r = CountListItems((u8*)self->f3C + 0x14);
                s32 lim = r + 1;
                s32 m = e->f4;
                s32 q = lim;
                if (q < m) q = m;
                n = q;
                cnt = n - r - 1;
            }
        } else {
            n = e->f4;
            cnt = n - 1;
        }
    done:
        if (n != 0) e->f8 = (void**)AllocateFrontMemory(n << 2);
        e->f8[e->fC++] = obj;
        if (cnt > 0) {
            s32 k = cnt;
            do {
                PlacedObject* o2 = CreateObjectCopy(obj, obj->world, obj->parent);
                e->f8[e->fC++] = o2;
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
        if (self->f3C != 0 && self->f3C->f4 != 0) {
            Quad16* d = self->f3C->fC + (i << 1);
            d[0] = *(Quad16*)&obj->v190;
            d[1] = *(Quad16*)&obj->v1D0;
        }
    }
}

s32 func_001AAAC8(ScreenElement* a, ScreenElement* b)
{
    s32 r = 0;
    s32 am = a->mode;
    if ((u32)(am - 1) < 2) { if ((u32)(b->mode - 1) < 2) goto yes; }
    if (am == 3) { if (b->mode == 3) goto yes; }
    if (b->mode == 3) { if (am == 2) goto yes; }
    goto done;
yes:
    r = 1;
done:
    return r;
}

struct Tab_1A87A8;
struct Ent_1A87A8 { s32 pad[4]; s32 flags; };

Ent_1A87A8* func_001A8718(Tab_1A87A8* table, s32 key);

void func_001A87A8(Tab_1A87A8* table, s32 key)
{
    Ent_1A87A8* e = FindObjectPoolEntry(table, key);
    if (e != 0) {
        e->flags &= ~2;
    }
}

void func_001A8AF8(ObjectPool* self);

s32 func_001A8C50(ObjectPool* self)
{
    if (self->f48 != 0) {
        return 1;
    }
    ChooseObjectPoolItem(self);
    return self->f48 != 0;
}

void func_001AA958(ScreenElement* self)
{
    s32 m = self->mode;
    if (m < 3) {
        if (m > 0) {
            self->vt->m16(self, 3);
        }
    }
}

void func_001AAB20(ScreenElement *self, f32 x, f32 y) {
    if (0.0f <= x) {
        self->w = x;
    }
    if (0.0f <= y) {
        self->h = y;
    }
    PlaceScreenElement(self);
}

struct Obj_1A93E8;
void func_001F5C0C(Obj_1A93E8* p, s32 zero, s32 size);

void func_001A93E8(u8* self)
{
    u8* p = self + 0x60;
    func_001F5C0C((Obj_1A93E8*)p, 0, 0x80);
    *(Mat02*)(p + 0x20) = g_identityMatrix;
}

extern void* const D_002486B0[];

void func_001A9F78(void)
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

extern void* const D_002486B0[];

void func_001AA060(void)
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

extern void* const D_002486B0[];
void func_001AA110(void)
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

extern Tab_26C3E0 D_0026C3E0;

void func_001AAEC0(ScreenElement* changed)
{
    T217D_Place* e = (T217D_Place*)&g_elementPlaces;
    s32 i;

    for (i = 0; i < 0x25; i++, e++) {
        s32 v = e->anchor;
        if (v != -1) {
            if (((ScreenElement**)g_screenElements)[v] == changed) {
                PlaceScreenElement(((ScreenElement**)g_screenElements)[i]);
            }
        }
    }
}

extern const f32 D_0024CD48 = 3.4028235e+38f;

void func_001AB600(T217D_510* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    self->lastTenth = self->lastSecond = -1;
    self->warnAt = D_0024CD48;
    self->f290 = 1;
    SetTimerState(self, 0);
}

extern const f32 D_0024CD4C = 3.4028235e+38f;

void func_001AB890(T217D_510* self, f32 x)
{
    self->onWarn = 0;
    self->warned = 0;
    self->limit = 0;
    self->onEnd = 0;
    self->f290 = 0;
    self->color = 0xFF808080;
    self->rate = -1.0f;
    self->lastSecond = -1;
    self->lastTenth = -1;
    self->warnAt = D_0024CD4C;
    self->time = x;
    SetTimerState(self, 1);
    StepTimer(self, 0.0f);
    self->vt->m14(self);
}

// NEAR: (fixed: indexed loop gave EXACT)
// allocator puts the count in $s1 and the pointer in $s0; retail is the other way round.

extern u8 D_00275F80[];
void func_001EFEE0(u8* a);
void func_001AE820(u8* a);

void func_001AA178(void)
{
    s32 i;
    for (i = 0; i < 0x25; i++) {
        ScreenElement* p = ((ScreenElement**)g_screenElements)[i];
        if (p->mode != 0) {
            p->vt->m09(p);
        }
    }
    DrawScreenFade(g_screenFade);
    func_001AE820((u8*)&D_00273EB0);
}

f32 D_002743A0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };

void func_001AA298(ScreenElement* self) {
    f32 t = *self->clock;
    s32 s = self->mode;
    switch (s) {
    case 2: {
        f32 d = self->vt->m12(self);
        if (d != 0.0f) {
            if (d <= t - self->since) s = 3;
        }
        break; }
    case 1: {
        f32 d = self->vt->m11(self);
        f32 zero = 0.0f;
        f32 x;
        if (d != zero) {
            f32 one = 1.0f;
            x = (t - self->since + self->offset) / d;
            if (x < zero) x = zero;
            else if (one < x) x = one;
            self->blend = x;
        }
        if (self->blend >= 1.0f) s = 2;
        break; }
    case 3: {
        f32 d = self->vt->m13(self);
        f32 zero = 0.0f;
        f32 x;
        if (d != zero) {
            f32 one = 1.0f;
            x = (t - self->since + self->offset) / d;
            f32 y = x < zero ? zero : (one < x ? one : x);
            self->blend = 1.0f - y;
        }
        if (self->blend <= 0.0f) s = 0;
        break; }
    }
    if (s == self->mode) {
        f32 p = self->blend;
        f32 k = D_002743A0[0] + p * (D_002743A0[1] + p * D_002743A0[2]);
        self->x = self->hiddenX + k * (self->shownX - self->hiddenX);
        self->y = self->hiddenY + k * (self->shownY - self->hiddenY);
        PlaceAnchoredScreenElements(self);
    }
    self->vt->m16(self, s);
}

struct Entry_1A8150 { s32 f0; s32 f4; u8 pad[8]; s32 f10; };

void* func_0018D5C0(u32 n);

void func_001A8150(ObjectPool* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->items == 0) {
        self->items = AllocateZeroedFrontMemory(0x50);
    }
    Entry_1A8150* e = &((Entry_1A8150*)self->items)[self->count++];
    e->f0 = a1;
    e->f4 = a2;
    e->f10 = ((((e->f10 & -2) | (a3 & 1)) & -3) | ((a4 & 1) << 1));
}

void func_001AAF88(T217D_E30* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    self->shown = -1;
    self->rate = 6000.0f;
    switch (self->index) {
    case 3:
        self->target = &g_saveData->f19E0;
        break;
    case 4:
        self->target = &g_currentEntry->count64;
        self->limit = &g_currentWorld->count2300;
        break;
    case 5:
        self->target = &g_currentLevelRecord->f438;
        break;
    case 6:
        self->target = &g_saveData->f19E8;
        break;
    case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 28: case 29:
    case 36:
        self->target = &self->shown;
        break;
    }
}

s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...);
extern const char D_0024CC78[];
extern const char D_0024CC80[];
extern const char D_0024CC88[];
extern const char D_0024CC90[];
extern const char D_0024CC98[];
extern const char D_0024CCA8[];
extern const char D_0024CCB0[];
extern const char D_0024CCB8[];
extern s32 D_002751D4;

void func_001AB2B8(T217D_E30* self)
{
    switch (self->index) {
    case 3:
        FormatToStringBounded(self->text, 0x200, D_0024CC78, 0x4C, self->shown);
        break;
    case 4:
        if (*self->limit != 0) {
            FormatToStringBounded(self->text, 0x200, D_0024CC80, self->shown, *self->limit,
                          self->shown < *self->limit ? 0x3F : 0x21);
        } else {
            self->text[0] = 0;
        }
        break;
    case 5:
        if ((u32)(g_saveData->f19D8 - 1) < 4) {
            FormatToStringBounded(self->text, 0x200, D_0024CC88, self->shown, 0x4B);
        } else {
            self->text[0] = 0;
        }
        break;
    case 6:
        if (g_currentWorld->f2354 != 0) {
            FormatToStringBounded(self->text, 0x200, D_0024CC78, 0x43, self->shown);
        } else {
            self->text[0] = 0;
        }
        break;
    case 7:
        FormatToStringBounded(self->text, 0x200, D_0024CC80, self->shown, *self->limit, 0x56);
        break;
    case 8:
        FormatToStringBounded(self->text, 0x200, D_0024CC80, self->shown, *self->limit, 0x4E);
        break;
    case 9:
        FormatToStringBounded(self->text, 0x200, D_0024CC90, 0x46, self->shown, *self->limit);
        break;
    case 10:
        FormatToStringBounded(self->text, 0x200, D_0024CC78, 0x4E, self->shown);
        break;
    case 11:
        FormatToStringBounded(self->text, 0x200, D_0024CC80, self->shown, *self->limit, 0x56);
        break;
    case 28:
        FormatToStringBounded(self->text, 0x200, D_0024CC80, self->shown, D_002751D4, 0x56);
        break;
    case 29:
        FormatToStringBounded(self->text, 0x200, D_0024CC90, 0x4E, self->shown, D_002751D4);
        break;
    case 12:
        FormatToStringBounded(self->text, 0x200, D_0024CC80, self->shown, *self->limit, 0x64);
        break;
    case 13:
        FormatToStringBounded(self->text, 0x200, D_0024CC98, 's',
                      self->shown >= 1 ? 'b' : 'm', self->shown >= 2 ? 'b' : 'm',
                      self->shown >= 3 ? 'b' : 'm', self->shown >= 4 ? 'b' : 'm',
                      self->shown >= 5 ? 'b' : 'm');
        break;
    case 14:
        FormatToStringBounded(self->text, 0x200, D_0024CCA8);
        break;
    case 15:
        FormatToStringBounded(self->text, 0x200, D_0024CCB0, 0x46, self->shown);
        break;
    case 36:
        FormatToStringBounded(self->text, 0x200, D_0024CCB8, self->shown);
        break;
    }
    SubstituteScreenElementGlyphs(self);
}

// EXACT: dst built as i*4 + (u32)items

struct Rec_1A8AF8 { s32 f0; s32 count; s32* items; s32 f0C; s32 flags; };
void func_001A89E8(ObjectPool* self);
s32 func_001A88A0(ObjectPool* self, s32 item);
void func_001F5B08(s32* dst, s32* src, s32 size);

void func_001A8AF8(ObjectPool* self)
{
    s32 s5 = 0;
    s32 s4 = 0;
    if (self->count != 0) {
        if (self->f40 == 0) {
            AdvanceObjectPoolEntry(self);
        }
        Rec_1A8AF8* rec = &((Rec_1A8AF8*)self->items)[self->f44];

        if (rec->flags & 2) {
            s32 i = 0;
            if (rec->count > 0) {
                do {
                    if (IsObjectPoolItemFree(self, rec->items[i]) != 0) {
                        s4 = rec->items[i];
                        if (self->sub != 0 && self->sub->f4 != 0) {
                            s5 = self->sub->fC + (self->f44 << 5);
                        }
                        if (rec->flags & 1) {
                        } else {
                            rec->count = rec->count - 1;
                            s32* p = (s32*)((u8*)0 + i * 4 + (u32)rec->items);
                            func_001F5B08(p, p + 1, (rec->count - i) * 4);
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

struct Rec_001A89E8 {
    s32 f00;
    s32 f04;
    s32* f08;
    s32 f0C;
    s32 f10;
};

s32 func_001A88A0(ObjectPool* self, s32 item);

void func_001A89E8(ObjectPool* self)
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
        Rec_001A89E8* rec = &((Rec_001A89E8*)self->items)[pos];
        if ((rec->f10 & 2) != 0) {
            for (k = 0; k < rec->f04; k++) {
                if (IsObjectPoolItemFree(self, rec->f08[k]) != 0) {
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


extern const f32 D_0024CD6C = 3.4028235e+38f;
extern const char D_0024CD50[];
extern const char D_0024CD60[];
extern char D_0024CD68[];

void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...);

void func_001AB980(T217D_510* self, f32 dt)
{
    f32 t = __builtin_fabsf(self->time);
    s32 sec = (s32)t;
    s32 hund = (s32)(t * 10.0f);
    s32 tenth = (s32)((t - (f32)sec) * 10.0f);

    if (self->state == 2)
    {
        f32 rate = self->rate;
        if (rate != 0.0f)
        {
            if (rate < 0.0f && 0.0f <= self->time && self->time < 10.0f)
            {
                if (tenth != self->lastTenth)
                {
                    if (tenth == 9)
                        StartSoundEffect(0x7E, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                    else if (tenth == 4)
                        StartSoundEffect(0x7F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                }
            }
            else if (sec != self->lastSecond)
            {
                StartSoundEffect((sec & 1) ? 0x72 : 0x73, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
    }
    self->lastTenth = tenth;
    self->lastSecond = sec;

    if (g_gameClock.running != 0 && self->state == 2 && (*(s32*)D_00262C68 & 2))
    {
        s32 warn = 0;
        s32 end = 0;
        f32 rate = self->rate;
        self->time = self->time + dt * rate;
        if (rate < 0.0f)
        {
            if (self->warnAt != D_0024CD6C && self->time <= self->warnAt)
                warn = 1;
            if (self->time <= self->limit)
                end = 1;
        }
        else if (rate > 0.0f)
        {
            if (self->warnAt != D_0024CD6C && self->warnAt <= self->time)
                warn = 1;
            if (self->time >= self->limit)
                end = 1;
        }
        if (warn && self->warned == 0)
        {
            self->warned = 1;
            if (self->onWarn != 0)
                self->onWarn(self, 0);
        }
        if (end)
        {
            self->time = self->limit;
            StartSoundEffect(1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            SetTimerState(self, 0);
            if (self->onEnd != 0)
                self->onEnd(self, 1);
        }
        t = __builtin_fabsf(self->time);
    }

    s32 show = 0;
    s32 tenths = 0;
    s32 hi;
    s32 lo;
    s32 sep;
    s32 h;
    if (t < 10.0f && (h = (s32)(t * 10.0f)) != hund)
    {
        hi = h / 10;
        lo = h % 10;
        sep = '.';
        tenths = 1;
        show = 1;
    }
    else
    {
        s32 s = (s32)t;
        if (s != sec || (self->state == 1 && g_gameClock.time - self->stateSince <= g_gameClock.dt))
        {
            hi = s / 60;
            lo = s % 60;
            sep = ':';
            show = 1;
        }
    }
    if (show)
    {
        FormatToStringBounded(self->text, 0x200, D_0024CD50, 0x54, hi, sep, (lo < 10 && !tenths) ? D_0024CD60 : D_0024CD68, lo);
        PushFontScale(self->font, self->scale, self->scale);
        f32 w = MeasureFontString(self->font, self->text);
        V24A2* f = self->font;
        SetScreenElementSize(self, w, (f32)f->height * f->sy);
        PopFontScale(self->font);
    }
}

f32 func_001EAF28(f32 x);

void func_001AAB60(ScreenElement* self) {
    T217D_Place* r = self->place;
    f32 x0 = 0.0f;
    f32 x1 = 640.0f;
    f32 y1 = 492.80002f;
    f32 y0 = x0;

    if (r->anchor != -1) {
        ScreenElement** objs = (ScreenElement**)g_screenElements;
        T217D_Place* recs = (T217D_Place*)&g_elementPlaces;
        do {
            ScreenElement* o = objs[r->anchor];
            if (o->vt->m18(o, self)) {
                switch (r->relation) {
                case 0:
                    if (o->w != 0.0f) x0 = o->x + o->w;
                    break;
                case 1:
                    if (o->w != 0.0f) x1 = o->x;
                    break;
                case 2:
                    if (o->h != 0.0f) y0 = o->y + o->h;
                    break;
                case 3:
                    if (o->h != 0.0f) y1 = o->y;
                    break;
                }
                break;
            }
            r = &recs[r->anchor];
        } while (r->anchor != -1);
    }
    f32 a = self->place->dx;
    if (a == 0.0f) {
        self->shownX = (x1 - x0 - self->w) * 0.5f;
    } else if (0.0f < a) {
        self->shownX = x0 + a;
    } else {
        self->shownX = x1 + a - self->w;
    }
    f32 b = self->place->dy;
    if (b == 0.0f) {
        self->shownY = (y1 - y0 - self->h) * 0.5f;
    } else if (0.0f < b) {
        self->shownY = y0 + b;
    } else {
        self->shownY = y1 + b - self->h;
    }
    f32 t = TruncateFloat(self->shownY * 0.9090909f) * 1.1f;
    self->hiddenX = self->shownX;
    self->shownY = t;
    self->hiddenY = t;
    switch (self->place->from) {
    case 0: self->hiddenX = -self->w; break;
    case 1: self->hiddenX = 640.0f; break;
    case 2: self->hiddenY = -self->h; break;
    case 3: self->hiddenY = 492.80002f; break;
    }
    s32 m = self->mode;
    if (m != 0) {
        if (m == 2) {
            self->x = self->shownX;
            self->y = self->shownY;
        }
    } else {
        self->x = self->hiddenX;
        self->y = self->hiddenY;
    }
    PlaceAnchoredScreenElements(self);
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001AA1F0();
void func_001AA790();
void func_001AA898();
void func_001AA8A0();
void func_001AA8A8();
void func_001AA8C8();
void func_001AA8F0();
void func_001AA958();
void func_001AAF58();
void func_001AAAC8();
void func_001AA4F0();
void func_001AA998();
void func_001AB058();
void func_001ABE70();
void func_001AC0E8();
void func_001AC888();
void func_001AC910();
void func_001AC990();
s32 func_001AC9E0();
void func_001ACA30();
void func_001ACA68();
void func_001ACAA8();
void func_001ACDA0();
void func_001ACE38();
void func_001AD320();
void func_001AD378();
void func_001AD3B0();
void func_001AD3F0();
void func_001AD6A8();
void func_001AD718();
void func_001AD7B0();
void func_001ADC60();
void func_001ADD28();
void func_001ADF28();
void func_001AE130();
void func_001AE178();
void func_001AE220();
void func_001AD940();
void func_001AD970();
void func_001ADB00();
void func_001AE510();
void func_001AE5E0();
void func_001AE758();
void func_001AE7F8();
void func_00193E58();
void func_001940E8();
void func_001943E8();
void func_00194E60();
void func_00194F00();
void func_00194F38();
void func_00194F80();
void func_0014ABD0();
void func_0014AC48();
void func_0014AD00();
void func_0014AD70();
void func_0014ADE0();
void func_001E5E70();
void func_001E6188();
void func_001E73B8();
void func_001E76E0();
void func_001E77C0();
void func_001E7C60();
void func_001E8840();
void func_001310F0();
void func_00131198();
void func_00135550();
void func_00136040();
void func_00136238();
void func_001363D0();
void func_00136408();
f32 func_001365F0();
f32 func_00136648();
void func_001366A0();
void func_00136EF8();
s32 func_00136FA8();
void func_001821B0();
void func_001F1960();
void func_001F1A08();
void func_001F1C90();
void func_001F20A8();
void func_0016B4A0();
void func_0016B560();
void func_0016B580();
void func_0016B7A8();
void func_0016B860();
void func_0016BA40();
void func_0016BBA8();
void func_0016BDD0();
void func_0016BEA0();
void func_001DFEB8();
void func_001E00B0();
void func_001E0678();
extern const Fn_Table D_00217E30[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217E80[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217ED0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217F20[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217F70[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001ABE40, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217FC0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001ABE50, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218010[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218060[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002180B0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218100[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218150[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002181A0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001ABE60, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002181F0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218240[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218290[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002182E0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ABE70, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AC0E8, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218380[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AC888, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AC910, (Fn_Table)func_001ACAA8, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001ACA30, (Fn_Table)func_001ACA68, (Fn_Table)func_001AC990, (Fn_Table)func_001AAF58, (Fn_Table)func_001AC9E0, 0 };
extern const Fn_Table D_002183D0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ACDA0, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001ACE38, (Fn_Table)func_001AD3F0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AD378, (Fn_Table)func_001AD3B0, (Fn_Table)func_001AD320, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218420[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AD6A8, (Fn_Table)func_001AD718, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AD7B0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218470[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ADC60, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001ADD28, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002184C0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ADF28, (Fn_Table)func_001AE178, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AE220, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AE130, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218510[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AB600, (Fn_Table)func_001AB660, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB710, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218560[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AD940, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001ADB00, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AD970, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002185B0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AE510, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AE5E0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218600[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AE758, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AA790, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AE7F8, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002186D0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_00193E58, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_001940E8, (Fn_Table)func_001943E8, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_00194F80, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_00194F00, (Fn_Table)func_00194F38, (Fn_Table)func_00194E60, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218720[20] = { (Fn_Table)func_0014ABD0, (Fn_Table)func_0014AC48, (Fn_Table)func_0014AD70, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_0014ADE0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_0014AD00, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_0021A3F0[20] = { (Fn_Table)func_001E5E70, (Fn_Table)func_001E6188, (Fn_Table)func_001E77C0, 0, 0, (Fn_Table)func_001E8840, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001E73B8, (Fn_Table)func_001E7C60, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001E76E0, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_0021A440[20] = { (Fn_Table)func_001310F0, (Fn_Table)func_00131198, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_00136238, (Fn_Table)func_00136040, (Fn_Table)func_001363D0, (Fn_Table)func_00136EF8, (Fn_Table)func_00136FA8, (Fn_Table)func_00136408, (Fn_Table)func_001366A0, 0, (Fn_Table)func_001365F0, (Fn_Table)func_001AA8A0, (Fn_Table)func_00136648, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_00135550, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00220BF0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)(void (*)(ScreenElement* self))func_001AA268, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001821B0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002210F0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001F1960, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_001F1C90, (Fn_Table)func_001F1A08, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001F20A8, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002212E0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_0016B4A0, (Fn_Table)func_0016B560, (Fn_Table)func_0016B7A8, (Fn_Table)func_0016B580, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_0016B860, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00221330[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_0016BA40, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_0016BDD0, (Fn_Table)func_0016BBA8, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_0016BEA0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00221380[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001DFEB8, (Fn_Table)func_001E00B0, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001E0678, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };

Entry_1A8718* func_001A8718(ObjectPool* self, s32 key)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (((Entry_1A8718*)self->items)[i].key == key) break;
    }
    if (i < self->count) return &((Entry_1A8718*)self->items)[i];
    return 0;
}

s32 func_001E2100(const char*);
void* func_001E2138(char*, const char*);
void func_0015E290(TextReader*, f32, f32*, f32*);
void func_001AA4F0(ScreenElement* self, const char* arg)
{
    if (arg && GetStringLength(arg)) {
        CopyString(self->text, arg);
    } else {
        self->text[0] = 0;
    }
    PushFontScale(self->font, self->scale, self->scale);
    TextReader m;
    InitTextReader(&m, self->text, self->font);
    f32 x, y;
    MeasureText(&m, 0.0f, &x, &y);
    SetScreenElementSize(self, x, y);
    PopFontScale(self->font);

}

extern f32 D_00261860;

void func_001AB2B8(T217D_E30* self);
f32 func_0015DFF8(TextReader* loc);

void func_001AB058(T217D_E30* self)
{
    TextReader loc;
    f32 frac;
    s32 n;
    s32 first;
    s32* p;

    UpdateScreenElementSlide(self);
    p = self->target;
    if (self->shown == *p) {
        return;
    }
    if (self->shown >= 0) {
        frac = g_frameDt * self->rate + self->fraction;
        n = (s32)frac;
        self->fraction = frac - (f32)n;
        first = *self->target;
        if (first < self->shown) {
            s32 lo = self->shown - n;
            self->shown = first < lo ? lo : first;
        } else {
            s32 hi = self->shown + n;
            self->shown = hi < first ? hi : first;
        }
    } else {
        self->shown = *p;
    }
    if (self->shown == *self->target && self->onDone != 0) {
        self->onDone(self->doneArg);
        self->onDone = 0;
        self->doneArg = 0;
    }
    FormatCounterCaption(self);
    if (self->text[0] != 0) {
        PushFontScale(self->font, self->scale, self->scale);
        InitTextReader(&loc, &self->text[0], self->font);
        f32 x = SumTextWidth(&loc);
        f32 y = (f32)self->font->height * self->font->sy;
        SetScreenElementSize(self, x, y);
        PopFontScale(self->font);
    } else {
        SetScreenElementSize(self, 0.0f, 0.0f);
    }
}


struct Key_1A88A0 { u8 pad0[0x678]; s32 f678; u8 pad1[4]; s32 f680; };
struct List_1A88A0 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_1A88A0 { List_1A88A0* list; u8* link; s32 offset; Iter_1A88A0* prev; };

s32 func_00182FC8(Key_1A88A0* p);
s32 func_001300E8(Key_1A88A0* p, s32 kind);

struct Begin_1A88A0 {
    static void Of(Iter_1A88A0* it, List_1A88A0* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (Iter_1A88A0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_1A88A0 {
    static u8* Of(Iter_1A88A0* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct End_1A88A0 {
    static void Of(Iter_1A88A0* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};

s32 func_001A88A0(ObjectPool* self, Key_1A88A0* key)
{
    Sub8C* group = self->sub;

    if (group != 0 && group->f4 != 0) {
        List_1A88A0* list;
        ObjectPool* skip;
        Iter_1A88A0 it;
        u8* obj;

        switch (group->f8) {
        case 1:
            list = (List_1A88A0*)&group->f14;
            skip = 0;
            break;
        case 2: {
            ObjectPool* e = (ObjectPool*)group->f14;
            skip = self;
            if (e->f48 == (s32)key) {
                return 0;
            }
            list = (List_1A88A0*)&e->sub->f14;
            break;
        }
        }
        Begin_1A88A0::Of(&it, list);
        for (obj = Next_1A88A0::Of(&it); obj != 0; obj = Next_1A88A0::Of(&it)) {
            ObjectPool* e = *(ObjectPool**)obj;
            if (e != skip && e->f48 == (s32)key) {
                End_1A88A0::Of(&it);
                return 0;
            }
        }
        End_1A88A0::Of(&it);
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

void func_001AA998(ScreenElement* self, s32 mode)
{
    if (self->mode == mode) {
        return;
    }
    s32 notify = 0;
    switch (mode) {
    case 1:
    case 3:
        if (mode == 1) {
            self->offset = self->blend * self->vt->m11(self);
        } else {
            self->offset = (1.0f - self->blend) * self->vt->m13(self);
        }
        if (self->mode == 0 || self->mode == 2) {
            notify = 1;
        }
        break;
    case 2:
        notify = 1;
        self->x = self->shownX;
        self->y = self->shownY;
        self->blend = 1.0f;
        self->offset = 0.0f;
        break;
    case 0:
        notify = 1;
        self->x = self->hiddenX;
        self->y = self->hiddenY;
        self->blend = 0.0f;
        self->offset = 0.0f;
        break;
    }
    self->mode = mode;
    self->since = *self->clock;
    if (notify) {
        PlaceScreenElement(self);
    }
}

// Data defined by this file.
extern void* const D_002486B0[38] = {
    (void*)&D_002721D0,
    (void*)&D_002701F8,
    (void*)&D_00270650,
    (void*)&D_0026C6C8,
    (void*)&D_0026C948,
    (void*)&D_0026CBC8,
    (void*)&D_0026CE48,
    (void*)&D_0026D0C8,
    (void*)&D_0026D348,
    (void*)&D_0026D5C8,
    (void*)&D_0026D848,
    (void*)&D_0026DAC8,
    (void*)&D_0026DD48,
    (void*)&D_0026DFC8,
    (void*)&D_0026E248,
    (void*)&D_0026E4E0,
    (void*)&D_0026E760,
    (void*)&D_0026E9F8,
    (void*)&D_0026EC70,
    (void*)&D_0026EED0,
    (void*)&D_0026F138,
    (void*)&D_0026F5A0,
    (void*)&D_0026F808,
    (void*)&D_0026FA90,
    (void*)&D_0026FD00,
    (void*)&D_0026FF68,
    (void*)&D_002708E0,
    (void*)&D_00271558,
    (void*)&D_00272430,
    (void*)&D_002726B0,
    (void*)&D_00272930,
    (void*)&D_00272B98,
    (void*)&D_00272E08,
    (void*)&D_002739F0,
    (void*)&D_00273C50,
    (void*)&D_00273EB0,
    (void*)&D_00274118,
    0,
};
Tab_26C3E0 D_0026C3E0 = {
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
extern const char D_0024CC78[8] = "%c%d";
extern const char D_0024CC80[8] = "%d/%d%c";
extern const char D_0024CC88[8] = "%d%c";
extern const char D_0024CC90[8] = "%c%d/%d";
extern const char D_0024CC98[16] = "%c%c%c%c%c%c";
extern const char D_0024CCA8[8] = "rstuv";
extern const char D_0024CCB0[8] = "%c%d/5";
extern const char D_0024CCB8[8] = "%d%%";
extern const char D_0024CD50[16] = "%c%d%c%s%d";
extern const char D_0024CD60[8] = "0";
