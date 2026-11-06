// SPDX-License-Identifier: AGPL-3.0-or-later
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "v24a2.h"

s32 func_00160D98(void);

s32 func_001300E8(void* node, s32 kind);

extern s32 D_00275BEC;
extern f32 D_00261850;

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

struct Pending_0014BD38 { u8 pad0[0x10]; s32 f10; };
struct Ctx_0014BD38 { u8 pad0[0x448]; f32 scale; };
extern Ctx_0014BD38* D_0027C00C;
void func_001C91C8(C11* self);
void func_0014CDC8(Ctx_0014BD38* ctx, C11* self);
void func_0012F6B0(void* handle, f32 scale);

void func_0014BD38(C11* self)
{
    EnterAgentState(self);
    switch (self->f724) {
    case 0xB:
        AddToGaugeAmount(D_0027C00C, self);
        if (((Pending_0014BD38*)self->fC28) != 0) { ((Pending_0014BD38*)self->fC28)->f10 = 0; self->fC28 = 0; }
        break;
    case 0xC:
        if (((Pending_0014BD38*)self->fC28) != 0) { ((Pending_0014BD38*)self->fC28)->f10 = 0; self->fC28 = 0; }
        SetAnimationPlayerSpeed(self->f7E0, D_0027C00C->scale);
        break;
    }
}

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
Node_0014BDC8* func_001925F0(void);
s32 func_001B9FB0(void* a, void* b);
void func_001D7098(void* out, s32 mode, C12* owner);
void func_001C8F20(void* node, s32 kind, s32 flag);

s32 func_0014BDC8(C12* self)
{
    s32 result = ChooseAgentState(self);
    if (result == 0xB) return result;
    Node_0014BDC8* n = GetActiveSwitchedCollider();
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

s32 func_001DDA80(void* p);

s32 func_0014BEA8(C12* self)
{
    if (func_001DDA80(self->world) != 0) return 0;
    if (self->f724 == 0xB || self->f724 == 0x10) return 0;
    return 1;
}

typedef void (*VFn_0014BEF8)(void* self, void* arg);

struct Node_0014BEF8 {
    VFn_0014BEF8* vtbl;
};

struct Scratch_0014BEF8 {
    s32 words[4];
};

s32 func_001C96D8(C12* self, Node_0014BEF8** slot);
void func_001D7098(void* out, s32 mode, C12* owner);

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

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00149398(T2173* self, Camera* owner);

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

struct Tmp_1496C0 {
    s32 w[4];
};

f32 D_00261BF0;

void func_00189230(void* a, void* b, void* c);
s32 func_001493C8(void* out, T2173_3B0* self);
void func_00144B70(void* eng, void* tmp);
void func_00143968(void* eng, f32 x);

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

extern void* D_0026EC68;

void func_00149398(T2173* self, Camera* owner)
{
    self->owner = owner;
}

s32 func_001493A0(T2173* self)
{
    return self->owner->stack[0].ctl == self;
}

void func_0014AD70(T217D_720* self)
{
    UpdateScreenElementSlide(self);
    for (s32 i = 0; i < self->count; i++) {
        T217D_330* s = &self->items[i];
        s->vt->m02(s);
    }
}

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);
void* func_001DBCC8(void* target, void* fn, void* ctx, s32 a, s32 b);

void func_001493B8(T2173* self, s32 value)
{
    self->value = value;
}

void func_001493C0(T2173* self, u8* eye, u8* tail, f32 dt)
{
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

void func_001C74E8(void* self);
void func_00152470(void* table, void* self);

void func_0014B550(C10* self)
{
    RegisterAgent(self);
    AppendToList(&self->world->list1CCC, self);
}

void func_0014AA90(T2173_3E0* obj, s32 value) { obj->value = value; }

void func_0014AA98(T2173_3E0* obj) { obj->value = 0; }

void func_0014A8D0(T2173_3C8* self)
{
    Camera* parent = self->owner;
    func_00144B70(parent, (u8*)parent->stack[0].target + 0x370);
}

struct State_0014B678 { f32 a; f32 b; s32 value; };
void func_001EAD88(void* a, void* b, f32 value);
void func_0014B678(State_0014B678* self, f32 value)
{
    ComputeSinCos(&self->b, self, value);
    self->value = 0;
}

void func_001C7520(void*);
void func_00152600(void*, void*);
void func_0014B588(C10* self) { UnregisterAgent(self); RemoveFromList(&self->world->list1CCC, self); }

void func_001C7188(void*, void*);
void func_0014B5C0(C10* self, void* other) { Pack10 save=self->fC10; CopyAgent(self,other); self->fC10=save; }

void func_001C6F48(void*);
static s32 D_0027C008;  // a running count, reset by func_0014B608
void func_0014B608(C11* self) { InitAgent(self); self->fC24=1; D_0027C008=0; }

void func_001C72A0(void*);
void func_0014B640(C11* self) { StartAgent(self); self->fC2C=D_0027C008++; }

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);
void* func_001DBCC8(void* target, void* fn, void* ctx, s32 a, s32 b);

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

void func_0014A7B8(T2173_3B0* self)
{
    Quad_14A7B8 a;
    Quad_14A7B8 b;
    Camera* n;

    GetCameraControllerTargetPoint(&a, self);
    func_00149458(&b, self);
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

struct Slot_14BF88 {
    u8 pad0[0x10];
    s32 v10;
};

void func_001C91C8(void* self);
void func_0014CD70(void* mgr, void* self);
void func_0012F6B0(void* sub, f32 x);

void func_0014BF88(C12* self)
{
    EnterAgentState(self);
    switch (self->f724) {
    case 0xB:
        func_0014CD70((void*)D_0027C00C, self);
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

f32 func_001EAAE0(f32 a, f32 b);
Effect* func_0019EA78(s32 kind, EffectOwner* sys);
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
void func_00149508(Obj_149508* self)
{
    StartSoundEffect(0x71, &self->f48, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    if (self->f48 != 0) {
        func_0011D640(self->f48->f18);
    }
    StartSoundEffect(0x70, &self->f4C, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    self->f44 = 1;
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

s32 func_001C96D8(C11* self);

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

struct __attribute__((aligned(16))) Quad_1493C8 { s32 a, b, c, d; };

extern u8 D_00261990[];
f32 D_00261BF8 = 7e+01f;
void func_001920B0(void* n, void* out);

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

void func_0014AD00(T217D_720* self, f32* clock)
{
    SetScreenElementClock(self, clock);
    T217D_330* e = self->items;
    for (u32 i = 0; i < 4; i++) {
        e->vt->m17(e, clock);
        e++;
    }
}

extern u8 D_002483D0[];
void func_0014A888(T2173_3C8* self, Camera* a1)
{
    SetCameraControllerOwner(self, a1);
    Blk2173* dst = &self->frame20;
    *dst = *(Blk2173*)g_identityMatrix;
}

struct Obj_148AC0;
struct Vt_148AC0 {
    u8 pad00[0x18];
    void (*f18)(Obj_148AC0* self);
    u8 pad1C[0x64 - 0x1C];
    void (*f64)(Obj_148AC0* self, s32 a);
    u8 pad68[0x84 - 0x68];
    void (*f84)(Obj_148AC0* self, s32 a);
    void (*f88)(Obj_148AC0* self, void* a);
    u8 pad8C[4];
    void (*f90)(Obj_148AC0* self, void* a);
    void (*f94)(Obj_148AC0* self, void* a);
    u8 pad98[0xCC - 0x98];
    void (*fCC)(Obj_148AC0* self, s32 a);
};
struct Obj_148AC0 {
    Vt_148AC0* vt;
    u8 pad04[0x88 - 0x04];
    u8 f88[0x2A8 - 0x88];
    f32 f2A8;
    u8 pad2AC[0x2E0 - 0x2AC];
    f32 f2E0;
    u8 pad2E4[0x33C - 0x2E4];
    s32 f33C;
};
extern u8 D_002483D0[];
extern u8 D_00248D30[];

s32 func_00148938(World* self, s32 a1, s32 n, Obj_148AC0** arr);
f32 func_001EAAE0(f32 a, f32 b);
void func_001EEB60(World* a, f32 f, void* b, void* c);

// NEAR: every instruction matches except the setup of the last call: retail loads obj into $a1 and derives $a2 from it, we load it into $a2 and derive $a1

struct __attribute__((aligned(16))) Quad_148038 {
    s32 a, b, c, d;
};

struct Ctx_148038;

extern u8 D_002483D0[];
extern u8 D_00248D30[];

s32 func_00148938(World* self, s32 a1, s32 a2, void** out);
s32 func_00160D98(void);
s32 func_001EEB60(Ctx_148038* self, f32 x, void* vec, void* out);

// EXACT: callee declared with a4,a5 after the float parameters

Effect* func_0019EA78(s32 kind, EffectOwner* sys);
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

extern T217D_Vt D_00218330;

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

void* D_0026EC68;

