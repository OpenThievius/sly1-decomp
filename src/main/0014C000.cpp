// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "world.h"
#include "screen_element.h"
#include "object_link.h"
#include "g261ef0.h"
#include "shapes.h"

void func_0014C838(GaugeManager* self, s32 value)
{
    s32 i = self->slotCount;
    self->slotCount = i + 1;
    self->slots[i].obj = (void*)value;
}

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

typedef void (*Fn_14DD28)(void* self);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);

s32 func_0014DA38(void* self, f32* a, f32* b);

void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

void func_00130C20(void* p0, void* p1, void* p2, void* p3, f32 x, f32 y);

void func_001B7A98(Collider* self);
s32 func_001526D0(void* a, void* b);
void func_00152600(void* a, void* b);
s32 func_001300E8(void* a, s32 b);

ObjectLink D_00261CC8[1] = { { 2, 0x2BC, 0x574 } };
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 idx, void* table);

extern u8* D_00262E10;

extern GaugeManager* D_0027C00C;

void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0014C5E8(GaugeManager* self);

void func_0014C668(void* unused, s32 mode)
{
    if (mode == 1) {
        s32 t[2];
        func_001B6568(D_0027C00C->device, &t[0]);
        func_001B6598(D_0027C00C->device, &t[1]);
        if (t[0] != 0x3FE && t[1] != 0x3FE) {
            SetStateWalkerTarget(D_0027C00C->device, 0x3FF);
            ApplyGaugeRatioToEffect(D_0027C00C);
        }
    }
}

extern f32 D_00261858[];

void func_00124FC0(void* self);
void func_0014C858(void* self);
void func_0014CBA8(void* self);
void* func_001925F0(void);

typedef void (*VFn_14C6E0)(void* self);
struct Obj_14C6E0 { VFn_14C6E0* vtbl; };

void func_0014C6E0(GaugeManager* self)
{
    s32 tag;
    UpdatePlacedObject(self);
    func_001B6598(self->device, &tag);
    if (tag == 0x3FD) {
        if (self->f45C < g_gameClock[1]) {
            func_0014C858(self);
        }
        if (self->f460 < g_gameClock[1]) {
            ActivateRandomGaugeSlot(self);
        }
        void* p = GetActiveSwitchedCollider();
        Obj_14C6E0* o = (Obj_14C6E0*)p;
        o->vtbl[81](p);
    }
}


void* func_001E9970(void* zero);

void func_0014C788(GaugeManager* self)
{
    s32 tag;
    func_001B6598(self->device, &tag);
    void* p = 0;
    if (tag == 0x3FD) {
        p = AreMenusAndFadeClear(p);
    }
    if (p) {
        g_gaugeAmountCaption.vt->m14(&g_gaugeAmountCaption);
        g_timerElement.vt->m14(&g_timerElement);
    } else {
        g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
        g_timerElement.vt->m15(&g_timerElement);
    }
}

void* func_0014C820(GaugeManager* self)
{
    return (u8*)self + (self->setIndex * 0xB0 + 0x480);
}

extern f32 D_0026185C[];

f32 func_001EAAE0(f32 a, f32 b);

struct Mgr_14CD70 {
    u8 pad_00[0x43C];
    f32 f43C;
    f32 f440;
    u8 pad_444[0x450 - 0x444];
    s32 f450;
    u8 pad_454[0x458 - 0x454];
    s32 f458;
    f32 f45C;
};

void func_0014CD70(Mgr_14CD70* self)
{
    if (self->f458 == self->f450) {
        self->f45C = g_gameTime[0] + RandomFloatInRange(self->f43C, self->f440);
    }
    self->f458 = self->f458 - 1;
}

void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);
s32 func_001300E8(void* obj, s32 kind);

s32 func_001B8A08(void* self, void* obj);

typedef void (*VFn2_0014FC38)(void* self, s32 arg);

void func_001B6628(void* h, s32 arg);
void func_001B6598(void* h, s32* out);
void func_001B6438(void* h);
void func_0013D278(void* self);

void func_001B6568(void* h, s32* out);
void func_001B64D8(void* h, s32 code);

void func_0014D280(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_0014D280(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_00188700(void* a, void* b, void* c, f32 w);
void func_001DD3E0(void* a, void* b, void* c, s32 d, s32 e);

void func_00130B48(void* a, void* b, void* c, void* d, f32 x, f32 y, f32 z, s32 n, void* buf);
f32 func_0014D0A8(s32 n, void* buf, void* other);

typedef f32 (*Fn_14E6A8)(void* self);
typedef void (*Fn2_14E6A8)(void* self, f32 t, s32 a1, void* a2);

void func_001B7968(Collider* self);

void func_00188700(void* a, void* b, void* c, f32 w);

void func_0014D3A8(void* a0, void* a1, s32 count, void* a3, void* a4, void* a5, s32* outIdx, f32* outT);

void func_0013DDB8(void* self);

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);
void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

typedef void (*Fn_14E3D0)(void* self);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);
void func_0014E500(void* self);

void func_00182D50(void*);
void func_00152470(void*,void*);

void func_001BA130(Collider* self, Collider* other);

void func_001BAC30(Collider* self);
void func_00159478(void** out, void* self);

void func_00127378(void* self, s32 kind, void* msg);

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6568(void* dev, s32* out);
void func_001B6438(void* h);

s32 func_0014D1A0(f32 x, s32 n, f32* arr, void* p2, f32* lo, f32* hi);


struct Src_14F920 { void** vtbl; u8 pad0[0x14 - 4]; void* p14; BaseObject* f18; u8 pad1[0x190 - 0x1C]; Quad16 q190[4];
 };
typedef void (*VFn_14F920)(void* self);
typedef void (*VFn_14F920Arg)(void* self, s32 x);

ObjectLink D_00261CE0[3] = { { 4, 0x2B4, 0x734 }, { 4, 0x2B5, 0x738 }, { 0, 0x2B6, 0x73C } };

void func_0013CE40(void* self);
void func_00124DF8(void* self, s32 n, void* table);
Src_14F920* func_0015A480(void* a, s32 kind, void* arg);
void* func_00183058(void* item, void* x, void* self);
void func_0014F900(C23* self);
void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void* func_001B6290(void* a, void* b, s32 c, s32 d);

struct Step_14C138 {
    u8 pad0[0xC];
    f32 dt;
};

struct Node_14C138 {
    u8 pad[0x14];
    void* f14;
};

extern Step_14C138* D_002623C8;
extern f32 D_00275C60[];
ObjectLink D_00261CA0[3] = { { 5, 0x3F8, 0x420 }, { 5, 0x3F9, 0x424 }, { 1, 0x3FA, 0x428 } };

void func_00124A48(GaugeManager* self);
void func_00124DF8(GaugeManager* self, s32 n, void* table);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6598(void* a, void* b);
void func_001B6DF8(void* a, void* b);
void func_0014C2F0(GaugeManager* self);

void func_0014C138(GaugeManager* self)
{
    s32 i = 0;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, g_gaugeManagerLinks);
    self->device = CreateStateWalker(self->f428, 0, 0x3FB, 0);
    func_001B6598(self->device, self->buf430);
    func_001B6DF8(self->device, self);
    for (; i < self->slotCount; i++) {
        GaugeSlot* s = &self->slots[i];
        Node_14C138* n = (Node_14C138*)func_0015A448(self->world, s->obj, self);
        s->obj = n;
        s->f8 = func_0015A480(n->f14, 0x3F7, n);
        s->f4 = func_0015A480(n->f14, 0x3F6, n);
    }
    f32* p = self->poly;
    f32 g = g_currentEntry->dt;
    f32 v = self->poly[0] + g * (p[1] + g * p[2]);
    f32 lo = g_unitRange[0];
    f32 hi = g_unitRange[1];
    f32 t;
    if (v < lo) {
        t = lo;
    } else if (hi < v) {
        t = hi;
    } else {
        t = v;
    }
    f32 u = 1.0f - t;
    f32* pa = (f32*)&self->params0;
    f32* pb = (f32*)&self->params1;
    f32* po = self->o5E0;
    for (u32 k = 0; k < 44; k++) {
        *po++ = u * *pa++ + t * *pb++;
    }
    self->f44C = (s32)self->o5E0[0];
    ComputeGaugeOutputs(self);
}

extern f32 D_0026185C[];

struct Arg_14CDC8 {
    u8 pad_00[0xC24];
    s32 fC24;
};

typedef s32 (*VFnI_14CDC8)(void* self);
struct Obj_14CDC8 { VFnI_14CDC8* vtbl; };

f32 func_001EAAE0(f32 a, f32 b);
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void* func_001925F0(void);
void func_001B64D8(void* dev, s32 value);
s32 func_0015A4F0(void* obj, s32 a1, s32 a2, s32 a3, s32 a4, s32* out);
void func_001C8F20(s32 value, s32 a1, s32 a2);
void func_001AB958(void* obj);
void func_0014C2F0(GaugeManager* self);

void func_0014CDC8(GaugeManager* self, Arg_14CDC8* arg)
{
    s32 hi = self->maxAmount;
    s32 v = self->amount + arg->fC24;
    if (v < 0) {
        v = 0;
    } else {
        if (hi < v) {
            v = hi;
        }
    }
    self->amount = v;
    if (!(v < self->maxAmount)) {
        s32 arr[32];
        s32 t1;
        s32 t2;
        func_001B6598(self->device, &t1);
        func_001B6568(self->device, &t2);
        void* p = GetActiveSwitchedCollider();
        Obj_14CDC8* o = (Obj_14CDC8*)p;
        s32 r = o->vtbl[81](p);
        if (t1 != 0x3FF && t2 != 0x3FF && r != 2) {
            SetStateWalkerTarget(self->device, 0x3FE);
            s32 n = GatherObjectsById(self->world, 5, 0x12, 0, 0x20, arr);
            if (n > 0) {
                s32 cnt = n;
                s32* q = arr;
                do {
                    ChangeAgentState(*q, 0xB, 0);
                    q++;
                } while (--cnt != 0);
            }
        }
        StopTimer(&g_timerElement);
    }
    ComputeGaugeOutputs(self);
    if (self->f454 == self->f44C) {
        self->f460 = g_gameTime[0] + RandomFloatInRange(*(f32*)(self->buf430 + 4), *(f32*)(self->buf430 + 8));
    }
    self->f454 = self->f454 - 1;
}

typedef f32 (*Slot6_14ED98)(void* self);
typedef void (*Slot11_14ED98)(void* self, s32 p1, f32 x, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

struct Sub_14F110;

extern f32 D_0026185C[];

s32 func_00126D60(Sub_14F110* sub, f32 value);

void func_00151E20(void* self, f32 amount);

void func_0014C5E8(GaugeManager* self)
{
    f32 one = 1.0f;
    f32 ratio = (f32)self->amount / (f32)self->maxAmount;
    f32 c;
    if (ratio < 0.0f) {
        c = 0.0f;
    } else if (one < ratio) {
        c = 1.0f;
    } else {
        c = ratio;
    }
    func_00151E20(&D_00261EF0, 1.0f - c * 0.8f);
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_002176D0[];
extern const Fn_Table D_00217708[];

void* func_0018D5C0(u32 n);

// NEAR: the calls and branches match; the store of 1 into the inner object comes before the
// float load of D_0026185C in retail, ours schedules the float load first (5 instructions).
extern u8 D_00248D30[];

s32 func_0014FEC0(C23* self);
PooledObject* func_00150338(C23* self);
s32 func_00182FC8(PooledObject* p);
void func_001853F0(Held23* a, PooledObject* b, u8* c);

// NEAR: the tail stores differ in order and register: retail does sw f6C8, then lui v1 / li v0,1 / lwc1 v1, we do lui v0 before the sw and use v0 for the address.

extern u8 D_00248D30[];

s32 func_00152720(void* p);
void func_00150298(C23* self);
void func_001B9AE0(Collider* o, s32 a, s32 b, s32 c, s32 d);

// NEAR: the search index is kept in a0 where retail uses a2, and hi is saved in s3 before the call in retail; the loop shape is otherwise the same.

struct Tab_14D1A0;

f32 func_0014D138(Tab_14D1A0* count, f32* table, void* wrap, f32 x);

void func_001B93F8(Collider* self);
void func_0014F270(PooledObject* self, f32 f);

void func_0013D068(C23* self);
void func_001B6598(void* p, s32* out);
void func_001B6568(void* p, s32* out);
void func_0014FDA8(C23* self, s32* state);
void func_00150008(C23* self);
void func_0014FCE8(C23* self, s32 state);

struct Slot_14CBA8 {
    void* p0;
    void* obj;
    void* p8;
    void* pc;
    s32 flag;
};
struct Ctl_14CBA8;
struct VT_14CBA8 {
    u8 pad[0x84];
    void (*f84)(Ctl_14CBA8* self, f32* v);
    void (*f88)(Ctl_14CBA8* self, f32* v);
    void (*f8c)(Ctl_14CBA8* self, f32* v);
    void (*f90)(Ctl_14CBA8* self, u8* v);
    void (*f94)(Ctl_14CBA8* self, u8* v);
};
struct Ctl_14CBA8 {
    VT_14CBA8* vt;
    u8 pad[0xC24];
    Slot_14CBA8* cur;
};
struct Holder_14CBA8 {
    u8 pad0[0x48];
    Ctl_14CBA8* ctl;
};
extern const f32 D_00249FB8 = 3.4028235e+38f;
extern u8 D_00248D30[];

void func_001A8AF8(Holder_14CBA8* p);
s32 func_001EAA70(s32 a, s32 b);
s32 func_001A8C90(Holder_14CBA8* h, s32 v);
s32 func_001F3BD8(void* p, f32* out);
s32 func_001F3C08(void* p, f32* out);
s32 func_0012C7B0(void* a, void* b, s32 c, void* out, f32 fa, f32 fb);
void func_0012F810(void* a, GaugeManager* self);
f32 func_001EAAE0(f32 a, f32 b);

void func_0014CBA8(GaugeManager* self)
{
    Slot_14CBA8* list[16];
    f32 v0[4];
    f32 v1[12];
    if (self->f454 >= self->f44C) {
        self->f460 = D_00249FB8;
        return;
    }
    ChooseObjectPoolItem((Holder_14CBA8*)self->f424);
    if (!((Holder_14CBA8*)self->f424)->ctl) return;
    s32 n = 0;
    for (s32 i = 0; i < self->slotCount; i++) {
        Slot_14CBA8* s = (Slot_14CBA8*)&self->slots[i];
        if (!s->flag && !s->pc) list[n++] = s;
    }
    if (n <= 0) return;
    s32 idx = RandomIntInRange(0, n - 1);
    Holder_14CBA8* h = (Holder_14CBA8*)self->f424;
    Ctl_14CBA8* c = h->ctl;
    Slot_14CBA8* s = list[idx];
    (void)func_001A8C90(h, 0);
    GetObjectWorldPosition(s->obj, v0);
    GetObjectWorldRotation(s->obj, v1);
    c->vt->f84(c, v0);
    c->vt->f88(c, v1);
    c->vt->f90(c, D_00248D30);
    c->vt->f94(c, D_00248D30);
    CreateAnimationPlayerWithoutPresetTargets(s->p8, s->p0, 0, &s->pc, 0.0f, 1.0f);
    func_0012F810(s->pc, self);
    self->f454 = self->f454 + 1;
    f32 r = RandomFloatInRange(*(f32*)(self->buf430 + 4), *(f32*)(self->buf430 + 8));
    self->f460 = (*(f32*)&g_gameTime) + r;
    c->cur = s;
    s->flag = 1;
}

struct Obj_14DBD0 { void** vt; s32 f4; s32 f8; s32 fC; f32* f10; };

void func_0014DB70(void);
struct Step_14DBD0;

struct Obj_14EC70 { void** vt; s32 f4; s32 f8; s32 fC; f32* f10; };

void func_0014DA98(void);
struct Step_14EC70;

extern const GaugeParams D_00249F00;
extern const f32 D_00249FB0 = 3.4028235e+38f;

void func_00123ED0(GaugeManager* self);

void func_0014C018(GaugeManager* self)
{
    InitPlacedObject(self);
    self->maxAmount = 50;
    self->f2D8 = 90.0f;
    GaugeParams params = g_defaultGaugeParams;
    self->params0 = params;
    self->params1 = params;
    self->params1.p44.Set(12.0f, 12.0f);
    self->params1.p4C.Set(12.0f, 12.0f);
    self->timer.Init();
    self->f45C = D_00249FB0;
    self->f450 = 2;
    self->f464 = 0;
    D_0027C00C = self;
}

struct __attribute__((aligned(16))) Vec_14DB78 { f32 v[4]; };
struct Src_14DB78;
struct VT_14DB78 {
    void* slot0;
    void (*f4)(Src_14DB78* self, Vec_14DB78* out, s32 flag);
};
struct Src_14DB78 { VT_14DB78* vt; };

void func_00186320(Vec_14DB78* p, Vec_14DB78* a, Vec_14DB78* b, f32* o1, f32* o2);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
// Defined in src/main/file_14D0A8.cpp.
f32 func_0014DB40();
f32 func_0014DB58();
void func_0014DD28();
void func_0014DE08();
void func_0014DE40();
void func_0014DE78();
void func_0014DF68();
f32 func_0014DF98();
f32 func_0014E000();
f32 func_0014E068();
void func_0014E090();
void func_0014E170();
void func_0014E2A0();
void func_0014E3D0();
void func_0014E5B8();
void func_0014E6A8();
void func_0014E710();
void func_0014E828();
f32 func_0014E910();
f32 func_0014E990();
void func_0014EA48();
void func_0014EB10();
void func_0014EC70();
void func_0014ED98();
extern const Fn_Table D_002176D0[14] = { (Fn_Table)func_0014DD28, (Fn_Table)func_0014DE08, (Fn_Table)func_0014DE40, (Fn_Table)func_0014DE78, (Fn_Table)func_0014DF68, (Fn_Table)func_0014DF98, (Fn_Table)func_0014E000, (Fn_Table)func_0014DB40, (Fn_Table)func_0014DB58, (Fn_Table)func_0014E068, (Fn_Table)func_0014E090, (Fn_Table)func_0014E170, (Fn_Table)func_0014E2A0, 0 };
extern const Fn_Table D_00217708[14] = { (Fn_Table)func_0014E3D0, (Fn_Table)func_0014E5B8, (Fn_Table)func_0014E6A8, (Fn_Table)func_0014E710, (Fn_Table)func_0014E828, (Fn_Table)func_0014E910, (Fn_Table)func_0014E990, (Fn_Table)func_0014DB40, (Fn_Table)func_0014DB58, (Fn_Table)func_0014EA48, (Fn_Table)func_0014EB10, (Fn_Table)func_0014EC70, (Fn_Table)func_0014ED98, 0 };

typedef void (*Cb_14CF30)(void* self);

void func_00127378(GaugeManager* self, s32 kind, void* key);
void func_001B6598(void* key, s32* out);
void func_001DDC38(void* sub, GaugeManager* self);
void func_001AB890(T217D_510* self, f32 v);
void func_001AB928(T217D_510* self, f32 v, Cb_14CF30 cb);
void func_001AB938(T217D_510* self);
void func_0014C668(void* self);

void func_0014CF30(GaugeManager* self, s32 kind, void* key)
{
    HandlePlacedObjectNotification(self, kind, key);
    switch (kind) {
    case 6: {
        s32 i;
        for (i = 0; i < self->slotCount; i++) {
            if (self->slots[i].key == key) {
                break;
            }
        }
        if (i < self->slotCount) {
            self->slots[i].key = 0;
        }
        break;
    }
    case 0x14:
        if (key == self->device) {
            s32 out;
            func_001B6598(key, &out);
            if (out == 0x3FD) {
                g_gaugeAmountCaption.target = &self->amount;
                g_gaugeAmountCaption.limit = &self->maxAmount;
                func_001DDC38(self->world, self);
                StartTimer(&g_timerElement, self->f2D8);
                SetTimerLimit(&g_timerElement, 0.0f, func_0014C668);
                StartTimerCounting(&g_timerElement);
            }
            if (self->tag430 == 0x3FD) {
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                g_timerElement.vt->m15(&g_timerElement);
                func_001DDC38(self->world, 0);
            }
            self->tag430 = out;
        }
        break;
    }
}

struct Clq_14C2F0 {
    f32 a;
    f32 b;
    f32 c;
};

struct Util_14C2F0 {
    static f32 Eval(Clq_14C2F0* q, f32 t) { return q->a + t * (q->b + t * q->c); }
    static f32 Limit(f32 g, f32 lo, f32 hi)
    {
        if (g < lo) return lo;
        if (hi < g) return hi;
        return g;
    }
    static f32 Lerp(f32 s, f32 a, f32 b) { return (1.0f - s) * a + s * b; }
};

struct Params_14C2F0 {
    f32 f00;
    f32 f04;
    u8 pad08[8];
    Clq_14C2F0 q10;
    u8 pad1C[4];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    Clq_14C2F0 q30;
    u8 pad3C[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    u8 pad54[0xC];
    Clq_14C2F0 q60;
    u8 pad6C[4];
    f32 f70;
    f32 f74;
    u8 pad78[8];
    Clq_14C2F0 q80;
    u8 pad8C[4];
    f32 f90;
    f32 f94;
    u8 pad98[8];
    Clq_14C2F0 qA0;
};

extern f32 D_00275C60[];
extern f32 D_00261858[];

void func_0014C2F0(GaugeManager* o)
{
    f32 t = Util_14C2F0::Limit((f32)o->amount / (f32)o->maxAmount, 0.0f, 1.0f);
    Params_14C2F0* p = (Params_14C2F0*)o->o5E0;
    f32 s;

    s = Util_14C2F0::Limit(Util_14C2F0::Eval(&p->q30, t), g_unitRange[0], g_unitRange[1]);
    *(f32*)(o->buf430 + 4) = Util_14C2F0::Lerp(s, p->f20, p->f28);
    *(f32*)(o->buf430 + 8) = Util_14C2F0::Lerp(s, p->f24, p->f2C);

    s = Util_14C2F0::Limit(Util_14C2F0::Eval(&p->q60, t), g_unitRange[0], g_unitRange[1]);
    *(f32*)(o->buf430 + 0xC) = Util_14C2F0::Lerp(s, p->f44, p->f4C);
    *(f32*)(o->buf430 + 0x10) = Util_14C2F0::Lerp(s, p->f48, p->f50);

    *(f32*)(o->buf430 + 0x14) = Util_14C2F0::Lerp(Util_14C2F0::Limit(Util_14C2F0::Eval(&p->q80, t), g_unitRange[0], g_unitRange[1]), p->f70, p->f74);

    *(f32*)(o->buf430 + 0x18) = Util_14C2F0::Lerp(Util_14C2F0::Limit(Util_14C2F0::Eval(&p->qA0, t), g_unitRange[0], g_unitRange[1]), p->f90, p->f94);

    o->f44C = (s32)Util_14C2F0::Lerp(Util_14C2F0::Limit(Util_14C2F0::Eval(&p->q10, t), g_unitRange[0], g_unitRange[1]), p->f00, p->f04);

    if (p->f40 < t && o->f464 == 0) {
        o->f464 = 1;
        o->f45C = g_gameClock[1];
    }
}

extern const GaugeParams D_00249F00 = {
    { 0x41000000, 0x40C00000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A, 0x3F19999A, 0x3F4CCCCD, 0x3FA66666, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A },
    { 3.5f, 5.0f }, { 2.0f, 2.5f },
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F59999A, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F4CCCCD, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000 }
};
