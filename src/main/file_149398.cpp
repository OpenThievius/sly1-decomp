// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x149398 to 0x14D0A8 (its .rodata from 0x249EA0, its .data from 0x261BF0, its
// .bss from 0x27C008): the camera's controllers (0x149398 to 0x14ABD0, the method tables
// D_00217398 to D_002173E0), a screen element's methods and the helpers after them (0x14ABD0 to
// 0x14B550), classes 0x10 to 0x12 and class 0x68, the gauge manager (0x14B550 to 0x14D0A8).
// One file between two exact edges: it could be several. Classes 0x11, 0x12 and 0x68 share it,
// since all three read the static D_0027C00C. Its name is ours, after its first address.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "v24a2.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "g261ef0.h"
#include "shapes.h"

s32 func_001300E8(void* node, s32 kind);
extern s32 D_00275BEC;
extern f32 D_00261850;

struct Pending_0014BD38 { u8 pad0[0x10]; s32 f10; };



void func_001C91C8(C11* self);


void func_0012F6B0(void* handle, f32 scale);
typedef void (*VFn_0014BDC8)(void* self, void* arg);

struct Node_0014BDC8 {
    VFn_0014BDC8* vtbl;
    u8 pad0[0xC10 - 4];
    Node_0014BDC8* next;
};

struct Scratch_0014BDC8 {
    s32 words[8];
};

s32 func_001C8010(C12* self);


s32 func_001B9FB0(void* a, void* b);
void func_001D7098(void* out, s32 mode, C12* owner);
void func_001C8F20(void* node, s32 kind, s32 flag);
s32 func_001DDA80(void* p);
typedef void (*VFn_0014BEF8)(void* self, void* arg);

struct Node_0014BEF8 {
    VFn_0014BEF8* vtbl;
};

struct Scratch_0014BEF8 {
    s32 words[4];
};

s32 func_001C96D8(C12* self, Node_0014BEF8** slot);
void func_001D7098(void* out, s32 mode, C12* owner);
void func_00149398(T2173* self, Camera* owner);

struct Tmp_1496C0 {
    s32 w[4];
};

void func_00189230(void* a, void* b, void* c);
s32 func_001493C8(void* out, T2173_3B0* self);
void func_00144B70(void* eng, void* tmp);
void func_00143968(void* eng, f32 x);
extern void* D_0026EC68;
void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);
void func_001C74E8(void* self);
void func_00152470(void* table, void* self);

struct State_0014B678 { f32 a; f32 b; s32 value; };

void func_001EAD88(void* a, void* b, f32 value);
void func_001C7520(void*);
void func_00152600(void*, void*);
void func_001C7188(void*, void*);
void func_001C6F48(void*);
void func_001C72A0(void*);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);

struct Quad_14A7B8 {
    s32 w[4];
};

s32 func_001493C8(void* out, T2173_3B0* self);
void func_00149458(void* out, void* self);
void func_001BF788(void* self, s32 n);
void func_00144938(void* self, void* a, void* b);
s32 func_001EAC68(f32 a, f32 b, f32 c);
void func_00143940(void* self, f32 x);
void func_00143968(void* self, f32 x);

struct Slot_14BF88 {
    u8 pad0[0x10];
    s32 v10;
};

void func_001C91C8(void* self);
void func_0014CD70(void* mgr, void* self);
void func_0012F6B0(void* sub, f32 x);
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_0011D640(s32 a);

struct Sub_149508 {
    u8 pad000[0x18];
    s32 f18;
};

struct Obj_149508 {
    u8 pad000[0x44];
    s32 f44;
    Sub_149508* f48;
    s32 f4C;
};

s32 func_001C96D8(C11* self);
extern u8 D_00261990[];
void func_001920B0(void* n, void* out);
extern u8 D_002483D0[];
extern u8 D_002483D0[];
extern u8 D_00248D30[];
f32 func_001EAAE0(f32 a, f32 b);
extern u8 D_002483D0[];
extern u8 D_00248D30[];
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern T217D_Vt D_00218330;
void func_00152600(void* a, void* b);
s32 func_001300E8(void* a, s32 b);
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 idx, void* table);


void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0014C5E8(GaugeManager* self);
extern f32 D_00261858[];
void func_00124FC0(void* self);
void func_0014C858(void* self);
void func_0014CBA8(void* self);
void* func_001925F0(void);
typedef void (*VFn_14C6E0)(void* self);

struct Obj_14C6E0 { VFn_14C6E0* vtbl; };

void* func_001E9970(void* zero);
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

void* func_0015A448(void* a, void* b, void* c);
s32 func_001300E8(void* obj, s32 kind);
void func_001B6598(void* h, s32* out);
void func_001B6568(void* h, s32* out);
void func_001B64D8(void* h, s32 code);
void func_00152470(void*,void*);
void func_00127378(void* self, s32 kind, void* msg);
void func_00127378(void* self, s32 kind, void* msg);
void func_001B6568(void* dev, s32* out);

struct Src_14F920 { void** vtbl; u8 pad0[0x14 - 4]; void* p14; BaseObject* f18; u8 pad1[0x190 - 0x1C]; Quad16 q190[4];
 };

void func_00124DF8(void* self, s32 n, void* table);
Src_14F920* func_0015A480(void* a, s32 kind, void* arg);
void* func_001B6290(void* a, void* b, s32 c, s32 d);

struct Node_14C138 {
    u8 pad[0x14];
    void* f14;
};


extern f32 D_00275C60[];
void func_00124A48(GaugeManager* self);
void func_00124DF8(GaugeManager* self, s32 n, void* table);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6598(void* a, void* b);
void func_001B6DF8(void* a, void* b);
void func_0014C2F0(GaugeManager* self);
extern f32 D_0026185C[];

struct Arg_14CDC8 {
    u8 pad_00[0xC24];
    s32 fC24;
};

void func_0014CDC8(GaugeManager* self, Arg_14CDC8* arg);
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
extern f32 D_0026185C[];
void func_00151E20(void* self, f32 amount);
extern u8 D_00248D30[];
extern u8 D_00248D30[];
void func_001B6598(void* p, s32* out);
void func_001B6568(void* p, s32* out);

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

extern u8 D_00248D30[];
void func_001A8AF8(Holder_14CBA8* p);
s32 func_001EAA70(s32 a, s32 b);
s32 func_001A8C90(Holder_14CBA8* h, s32 v);
s32 func_001F3BD8(void* p, f32* out);
s32 func_001F3C08(void* p, f32* out);
s32 func_0012C7B0(void* a, void* b, s32 c, void* out, f32 fa, f32 fb);
void func_0012F810(void* a, GaugeManager* self);
f32 func_001EAAE0(f32 a, f32 b);


void func_00123ED0(GaugeManager* self);
typedef void (*Cb_14CF30)(void* self);
void func_00127378(GaugeManager* self, s32 kind, void* key);
void func_001B6598(void* key, s32* out);
void func_001DDC38(void* sub, GaugeManager* self);
void func_001AB890(T217D_510* self, f32 v);
void func_001AB928(T217D_510* self, f32 v, Cb_14CF30 cb);
void func_001AB938(T217D_510* self);
void func_0014C668(void* self);

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

// The file's statics (.bss from 0x27C008).
static s32 D_0027C008;  // a running count, reset by func_0014B608
static GaugeManager* D_0027C00C;  // the gauge manager, set by its set-up (func_0014C018)

f32 D_00261BF0 = 0.0f;
f32 D_00261BF4 = 0.300000012f;
f32 D_00261BF8 = 7e+01f;
f32 D_00261BFC = -1.0f;
f32 D_00261C00[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
f32 D_00261C10[4] = { -150.0f, 0.0f, 0.0f, 0.0f };
f32 D_00261C20[4] = { -25.0f, 0.0f, 0.0f, 0.0f };
f32 D_00261C30[4] = { 2.0f, 0.0f, -1.0f, 0.0f };
f32 D_00261C40[4] = { 0.200000003f, 0.0f, 0.5f, 1.0f };
f32 D_00261C50[4] = { 0.25f, 0.0f, 0.75f, 2.25f };
f32 D_00261C60[4] = { 10.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00261C70[4] = { 1.0f, 0.400000006f, 1.5f, 0.0f };
f32 D_00261C80[3] = { 5.0f, 0.0f, 0.5f };
f32 D_00261C8C = 24.0f;
s32 D_00261C90 = 4;
f32 D_00261C94 = 900.0f;
f32 D_00261C98 = 1200.0f;
ObjectLink D_00261CA0[3] = { { 5, 0x3F8, 0x420 }, { 5, 0x3F9, 0x424 }, { 1, 0x3FA, 0x428 } };

void func_00149398(T2173* self, Camera* owner)
{
    self->owner = owner;
}

s32 func_001493A0(T2173* self)
{
    return self->owner->stack[0].ctl == self;
}

void func_001493B8(T2173* self, s32 value)
{
    self->value = value;
}

void func_001493C0(T2173* self, u8* eye, u8* tail, f32 dt)
{
}

struct __attribute__((aligned(16))) Quad_1493C8 { s32 a, b, c, d; };

Quad_1493C8 func_001493C8(T2173_3B0* self)
{
    Quad_1493C8 r;
    if (self->f5C != 0) {
        func_001920B0(self->f5C, &r);
    } else {
        if (GetActiveSwitchedCollider() != 0) {
            r = *(Quad_1493C8*)((u8*)GetActiveSwitchedCollider() + 0x140);
            *(f32*)&r.c = *(f32*)&r.c + D_00261BF8;
        } else {
            r = *(Quad_1493C8*)(*(u8**)g_camera + 0x40);
        }
    }
    return r;
}

ASM_FUNC(func_00149458);

void func_00149508(Obj_149508* self)
{
    StartSoundEffect(0x71, &self->f48, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    if (self->f48 != 0) {
        func_0011D640(self->f48->f18);
    }
    StartSoundEffect(0x70, &self->f4C, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    self->f44 = 1;
}

void func_001495E8(T2173_3B0* s, s32 value)
{
    s32 n = s->count;
    if ((u32)n < 4) {
        s->items[n] = value;
        s->count = n + 1;
    }
}

s32 func_00149610(T2173_3B0* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    n = n - 1;
    s->count = n;
    return s->items[n];
}

s32 func_00149638(T2173_3B0* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    return s->items[n - 1];
}

void func_00149660(T2173_3B0* self, Camera* owner)
{
    SetCameraControllerOwner(self, owner);
    self->count = 0;
    self->f20 = 10.0f;
    PushStackValue(self, 0);
    self->f54 = 0.5f;
    self->f58 = -1.0f;
    self->f50 = 0;
}

void func_001496C0(T2173_3B0* self)
{
    Tmp_1496C0 tmp;
    Camera* eng = (Camera*)self->owner;
    VectorToAngles((u8*)eng + 0x80, (u8*)self + 8, (u8*)self + 0x10);
    f32 d = self->f20;
    self->f10 = D_00261BF0;
    self->f0C = 0;
    self->f14 = 0;
    self->f18 = 0;
    self->f1C = 0;
    f32 a = eng->f1C8;
    self->f28 = a;
    self->f24 = a / d;
    GetCameraControllerTargetPoint(&tmp, self);
    func_00144B70(eng, &tmp);
    self->f2C = eng->f1E4;
    SetCameraNearDistance(eng, 49.0f);
}

INCLUDE_RODATA(D_00249EA0);
INCLUDE_RODATA(jtbl_00249EB0);
INCLUDE_RODATA(jtbl_00249ED0);

ASM_FUNC(func_00149760);

void func_0014A7B8(T2173_3B0* self)
{
    Quad_14A7B8 a;
    Quad_14A7B8 b;
    Camera* n;

    GetCameraControllerTargetPoint(&a, self);
    GetTargetCameraControllerEyePoint(&b, self);
    n = (Camera*)self->owner;
    StopSoundRecord(self->p48, 0);
    StopSoundRecord(self->p4C, 500);
    func_00144938(n, &b, &a);
    if (func_001EAC68(n->f1C4, self->f28, 1e-4f) == 0) {
        SnapCameraZoom(n, self->f28);
    }
    self->f5C = 0;
    if (n->f1E4 == 49.0f) {
        SetCameraNearDistance(n, self->f2C);
    }
}

void func_0014A888(T2173_3C8* self, Camera* a1)
{
    SetCameraControllerOwner(self, a1);
    Blk2173* dst = &self->frame20;
    *dst = *(Blk2173*)g_identityMatrix;
}

void func_0014A8D0(T2173_3C8* self)
{
    Camera* parent = self->owner;
    func_00144B70(parent, (u8*)parent->stack[0].target + 0x370);
}

ASM_FUNC(func_0014A8F8);

void func_0014AA90(T2173_3E0* obj, s32 value) { obj->value = value; }

void func_0014AA98(T2173_3E0* obj) { obj->value = 0; }

ASM_FUNC(func_0014AAA0);

void func_0014ABD0(T217D_720* self)
{
    u32 n;

    InitScreenElement(self, 0x20);
    T217D_330* e = self->items;
    for (n = 0; n < 4; n++) {
        e->vt = &D_00218330;
        D_00218330.m00(e, 0x12);
        e++;
    }
}

void func_0014AC48(T217D_720* self)
{
    T217D_330* e;
    u32 i;

    e = (T217D_330*)self;
    SetupScreenElementText(e);
    e = self->items;
    for (i = 0; i < 4; i++) {
        e->vt->m01(e);
        e->frame = 0;
        e->font->sx = 0.8f;
        e->font->sy = 0.8f;
        SetScreenElementSlideInTime(e, 1.0f);
        SetScreenElementSlideOutTime(e, 1.0f);
        SetScreenElementHoldTime(e, 0.0f);
        e++;
    }
}

void func_0014AD00(T217D_720* self, f32* clock)
{
    SetScreenElementClock(self, clock);
    T217D_330* e = self->items;
    for (u32 i = 0; i < 4; i++) {
        e->vt->m17(e, clock);
        e++;
    }
}

void func_0014AD70(T217D_720* self)
{
    UpdateScreenElementSlide(self);
    for (s32 i = 0; i < self->count; i++) {
        T217D_330* s = &self->items[i];
        s->vt->m02(s);
    }
}

void func_0014ADE0(T217D_720* self)
{
    if (D_00275BEC == 1) {
        f32 acc = self->y;
        s32 i;
        for (i = 0; i < self->count; i++) {
            T217D_330* e = &self->items[i];
            f32 saved = e->blend;
            f32 base = self->x;
            f32 scaled = saved * g_timeScale;
            e->y = acc;
            e->x = base;
            e->blend = scaled;
            e->vt->m09(e);
            e->blend = saved;
            acc += e->h;
        }
    }
}

void func_0014AEA0(T217D_720* self, s32 n, f32 x, f32 y)
{
    self->place->dx = x;
    self->place->dy = y;
    self->count = n;
    V24A2* q = self->font;
    SetScreenElementSize(self, self->w, (f32)q->height * q->sy * (f32)n);
    self->vt->m16(self, 2);
}

void func_0014AF10(T217D_720* self)
{
    self->vt->m16(self, 0);
}

ASM_FUNC(func_0014AF38);

void func_0014B0C0(s32 n, f32* a, f32* l)
{
    s32 i;
    s32 j;
    s32 k;
    f32 sum;

    if (n == 0)
    {
        return;
    }
    for (i = 0; i < n; i++)
    {
        l[i] = a[i];
    }
    if (__builtin_fabsf(l[0]) < 1e-8f)
    {
        for (j = 0; j < n; j++)
        {
            l[j * n] = 0.0f;
        }
    }
    else
    {
        for (j = 1; j < n; j++)
        {
            l[j * n] = a[j * n] / l[0];
        }
    }
    for (j = 1; j < n - 1; j++)
    {
        for (i = j; i < n; i++)
        {
            sum = 0.0f;
            for (k = 0; k < j; k++)
            {
                sum += l[i + k * n] * l[j * n + k];
            }
            l[j * n + i] = a[j * n + i] - sum;
        }
        if (__builtin_fabsf(l[j * n + j]) < 1e-8f)
        {
            for (k = j; k < n; k++)
            {
                l[k * n + j] = 0.0f;
            }
        }
        else
        {
            for (k = j + 1; k < n; k++)
            {
                sum = 0.0f;
                for (i = 0; i < j; i++)
                {
                    sum += l[j + i * n] * l[k * n + i];
                }
                l[k * n + j] = (a[k * n + j] - sum) / l[j * n + j];
            }
        }
    }
    sum = 0.0f;
    for (k = 0; k < n - 1; k++)
    {
        sum += l[(n - 1) + k * n] * l[(n - 1) * n + k];
    }
    l[(n - 1) * n + (n - 1)] = a[(n - 1) * n + (n - 1)] - sum;
    if (__builtin_fabsf(l[(n - 1) * n + (n - 1)]) < 1e-8f)
    {
        l[(n - 1) * n + (n - 1)] = 0.0f;
    }
}

void func_0014B3E0(s32 n, f32* m, f32* b, f32* x)
{
    s32 i;
    s32 k;
    f32 sum;

    for (i = 0; i < n; i++) {
        if (m[i * n + i] == 0.0f) {
            x[i] = 0.0f;
        } else {
            sum = 0.0f;
            for (k = 0; k < i; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] = (b[i] - sum) / m[i * n + i];
        }
    }

    for (i = n - 2; i >= 0; i--) {
        if (m[i * n + i] != 0.0f) {
            sum = 0.0f;
            for (k = i + 1; k < n; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] -= sum;
        }
    }
}

void func_0014B550(C10* self)
{
    RegisterAgent(self);
    AppendToList(&self->world->list1CCC, self);
}

void func_0014B588(C10* self) { UnregisterAgent(self); RemoveFromList(&self->world->list1CCC, self); }

void func_0014B5C0(C10* self, void* other) { Pack10 save=self->fC10; CopyAgent(self,other); self->fC10=save; }

void func_0014B608(C11* self) { InitAgent(self); self->fC24=1; D_0027C008=0; }

void func_0014B640(C11* self) { StartAgent(self); self->fC2C=D_0027C008++; }

void func_0014B678(State_0014B678* self, f32 value)
{
    ComputeSinCos(&self->b, self, value);
    self->value = 0;
}

INCLUDE_RODATA(D_00249EF0);

ASM_FUNC(func_0014B6A8);

ASM_FUNC(func_0014BB08);

s32 func_0014BCE8(C11* self)
{
    if (self->f724 == 0x10) {
        return 1;
    }
    if (self->f724 == 0xB) {
        return 1;
    }
    if (HandleAgentObjectEvent(self) == 0) {
        return 0;
    }
    self->fC20 = 0;
    return 1;
}

void func_0014BD38(C11* self)
{
    EnterAgentState(self);
    switch (self->f724) {
    case 0xB:
        AddToGaugeAmount(D_0027C00C, (Arg_14CDC8*)self);
        if (((Pending_0014BD38*)self->fC28) != 0) { ((Pending_0014BD38*)self->fC28)->f10 = 0; self->fC28 = 0; }
        break;
    case 0xC:
        if (((Pending_0014BD38*)self->fC28) != 0) { ((Pending_0014BD38*)self->fC28)->f10 = 0; self->fC28 = 0; }
        SetAnimationPlayerSpeed(self->f7E0, D_0027C00C->speed448);
        break;
    }
}

s32 func_0014BDC8(C12* self)
{
    s32 result = ChooseAgentState(self);
    if (result == 0xB) return result;
    Node_0014BDC8* n = (Node_0014BDC8*)GetActiveSwitchedCollider();
    if (n != 0 && IsContactBetweenParts(self, n) != 0) {
        Scratch_0014BDC8 buf;
        InitOwnerMessage(&buf, 0, self);
        result = 0xB;
        n->vtbl[0x50](n, &buf);
    }
    for (Node_0014BDC8* x = (Node_0014BDC8*)self->world->list1CCC.head; x != 0; x = x->next) {
        if ((void*)x != (void*)self && IsObjectOfKind(x, 0x12) != 0 && IsContactBetweenParts(self, x) != 0) {
            ChangeAgentState(x, 0xB, 0);
        }
    }
    return result;
}

s32 func_0014BEA8(C12* self)
{
    if (func_001DDA80(self->world) != 0) return 0;
    if (self->f724 == 0xB || self->f724 == 0x10) return 0;
    return 1;
}

s32 func_0014BEF8(C12* self, Node_0014BEF8** slot)
{
    if (self->f724 == 0x10 || self->f724 == 0xB) return 1;
    if (HandleAgentObjectEvent(self, slot) == 0) return 0;
    Node_0014BEF8* found = (Node_0014BEF8*)GetActiveSwitchedCollider();
    Node_0014BEF8* n = *slot;
    if (n == found) {
        Scratch_0014BEF8 buf;
        InitOwnerMessage(&buf, 0, self);
        n->vtbl[0x50](n, &buf);
    }
    return 1;
}

void func_0014BF88(C12* self)
{
    EnterAgentState(self);
    switch (self->f724) {
    case 0xB:
        CountDownGaugeContacts((void*)D_0027C00C, self);
        if (((Slot_14BF88*)self->fC20) != 0) {
            ((Slot_14BF88*)self->fC20)->v10 = 0;
            self->fC20 = 0;
        }
        break;
    case 0xC:
        if (((Slot_14BF88*)self->fC20) != 0) {
            ((Slot_14BF88*)self->fC20)->v10 = 0;
            self->fC20 = 0;
        }
        SetAnimationPlayerSpeed(self->f7E0, self->fC24);
        break;
    }
}

extern const GaugeParams D_00249F00 = {
    { 0x41000000, 0x40C00000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A, 0x3F19999A, 0x3F4CCCCD, 0x3FA66666, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A },
    { 3.5f, 5.0f }, { 2.0f, 2.5f },
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F59999A, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F4CCCCD, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000 }
};

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
    self->f45C = 3.4028235e+38f;
    self->f450 = 2;
    self->f464 = 0;
    D_0027C00C = self;
}

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
    RaiseScatterLevels(&g_scatterController, 1.0f - c * 0.8f);
}

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

void func_0014C6E0(GaugeManager* self)
{
    s32 tag;
    UpdatePlacedObject(self);
    func_001B6598(self->device, &tag);
    if (tag == 0x3FD) {
        if (self->f45C < g_gameClock[1]) {
            RunGaugeTimedEvent(self);
        }
        if (self->f460 < g_gameClock[1]) {
            ActivateRandomGaugeSlot(self);
        }
        void* p = GetActiveSwitchedCollider();
        Obj_14C6E0* o = (Obj_14C6E0*)p;
        o->vtbl[81](p);
    }
}

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

void func_0014C838(GaugeManager* self, s32 value)
{
    s32 i = self->slotCount;
    self->slotCount = i + 1;
    self->slots[i].obj = (void*)value;
}

INCLUDE_RODATA(D_00249FB4);

ASM_FUNC(func_0014C858);

void func_0014CBA8(GaugeManager* self)
{
    Slot_14CBA8* list[16];
    f32 v0[4];
    f32 v1[12];
    if (self->f454 >= self->f44C) {
        self->f460 = 3.4028235e+38f;
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

void func_0014CD70(Mgr_14CD70* self)
{
    if (self->f458 == self->f450) {
        self->f45C = g_gameTime[0] + RandomFloatInRange(self->f43C, self->f440);
    }
    self->f458 = self->f458 - 1;
}

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
                SetTimerLimit(&g_timerElement, 0.0f, FinishGaugeOnTimeout);
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

