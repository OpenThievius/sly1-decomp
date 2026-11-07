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
#include "font.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "object_pool.h"
#include "owner_message.h"

s32 IsObjectOfKind(void* node, s32 kind);
extern s32 D_00275BEC;
extern f32 g_timeScale;




void EnterAgentState(NumberedAgent* self);


void SetAnimationPlayerSpeed(void* handle, f32 scale);
// An agent of the world's list at +0x1CCC (linked at +0xC10), seen as its table of slots:
// slot 0x50 takes an owner message (func_0014BDC8, func_0014BEF8).
typedef void (*AgentMessageFn)(void* self, void* arg);

struct ListedAgentView {
    AgentMessageFn* vtbl;
    u8 pad0[0xC10 - 4];
    ListedAgentView* next;
};

// The 32-byte block func_0014BDC8 builds its owner message in (InitOwnerMessage fills the
// first 16 bytes; the frame has room for 32).
struct Scratch_0014BDC8 {
    s32 words[8];
};

s32 ChooseAgentState(ContactAgent* self);


s32 IsContactBetweenParts(void* a, void* b);
void InitOwnerMessage(void* out, s32 mode, ContactAgent* owner);
void ChangeAgentState(void* node, s32 kind, s32 flag);
s32 IsPadSelectFlagHeld(void* p);


s32 HandleAgentObjectEvent(ContactAgent* self, ListedAgentView** slot);
void InitOwnerMessage(void* out, s32 mode, ContactAgent* owner);
void SetCameraControllerOwner(CameraController* self, Camera* owner);


void VectorToAngles(void* a, void* b, void* c);
s32 GetCameraControllerTargetPoint(void* out, TargetCameraController* self);
void SetCameraLookAnchor(void* eng, void* tmp);
void SetCameraNearDistance(void* eng, f32 x);
extern void* g_deadlineNotifier;
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void RegisterAgent(void* self);
void AppendToList(void* table, void* self);

// What SetSinCosPair fills: the two results of ComputeSinCos and a word it clears.
struct SinCosPair { f32 a; f32 b; s32 value; };

void ComputeSinCos(void* a, void* b, f32 value);
void UnregisterAgent(void*);
void RemoveFromList(void*, void*);
void CopyAgent(void*, void*);
void InitAgent(void*);
void StartAgent(void*);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* dev, s32* out);


s32 GetCameraControllerTargetPoint(void* out, TargetCameraController* self);
void GetTargetCameraControllerEyePoint(void* out, void* self);
void StopSoundRecord(void* self, s32 n);
void PlaceCameraLookingAt(void* self, void* a, void* b);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);
void SnapCameraZoom(void* self, f32 x);
void SetCameraNearDistance(void* self, f32 x);


void EnterAgentState(void* self);
void CountDownGaugeContacts(void* mgr, void* self);
void SetAnimationPlayerSpeed(void* sub, f32 x);
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void PauseIopVoice(s32 a);

// What StartCameraSounds keeps of each sound it starts: the IOP voice at +0x18 it pauses.
struct CameraSound {
    u8 pad000[0x18];
    s32 voice;
};

// The object StartCameraSounds fills (g_camera): two sounds and a flag it sets.
struct CameraSoundOwner {
    u8 pad000[0x44];
    s32 f44;
    CameraSound* f48;
    s32 f4C;
};

s32 HandleAgentObjectEvent(NumberedAgent* self);
extern u8 g_camera[];
void ConvertPositionToWorld(void* n, void* out);
extern u8 g_identityMatrix[];
extern u8 g_identityMatrix[];
extern u8 D_00248D30[];
f32 RandomFloatInRange(f32 a, f32 b);
extern u8 g_identityMatrix[];
extern u8 D_00248D30[];
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern T217D_Vt D_00218330;
void RemoveFromList(void* a, void* b);
s32 IsObjectOfKind(void* a, s32 b);
void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 idx, void* table);


void GetStateWalkerTargetKey(void* dev, s32* out);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void SetStateWalkerTarget(void* dev, s32 value);
void ApplyGaugeRatioToEffect(GaugeManager* self);
extern f32 g_gameClock[];
void UpdatePlacedObject(void* self);
void RunGaugeTimedEvent(void* self);
void ActivateRandomGaugeSlot(void* self);
void* GetActiveSwitchedCollider(void);
// The active collider seen as its table of slots: slot 81 (func_0014C6E0, func_0014CDC8).
typedef void (*ColliderSlotFn)(void* self);

struct ColliderSlots { ColliderSlotFn* vtbl; };

void* AreMenusAndFadeClear(void* zero);
extern f32 g_gameTime[];
f32 RandomFloatInRange(f32 a, f32 b);


void* FindFirstObjectByIdMode4(void* a, void* b, void* c);
s32 IsObjectOfKind(void* obj, s32 kind);
void GetStateWalkerCurrentKey(void* h, s32* out);
void GetStateWalkerTargetKey(void* h, s32* out);
void SetStateWalkerTarget(void* h, s32 code);
void AppendToList(void*,void*);
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerTargetKey(void* dev, s32* out);


void ResolveObjectLinks(void* self, s32 n, void* table);
BaseObject* FindFirstObjectByIdMode1(void* a, s32 kind, void* arg);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);



extern f32 g_unitRange[];
void StartPlacedObject(GaugeManager* self);
void ResolveObjectLinks(GaugeManager* self, s32 n, void* table);
void* CreateStateWalker(void* a, s32 b, s32 c, s32 d);
void GetStateWalkerCurrentKey(void* a, void* b);
void AddStateWalkerListener(void* a, void* b);
void ComputeGaugeOutputs(GaugeManager* self);
extern f32 g_gameTime[];


void AddToGaugeAmount(GaugeManager* self, NumberedAgent* arg);
typedef s32 (*ColliderQueryFn)(void* self);

struct ColliderQuerySlots { ColliderQueryFn* vtbl; };

f32 RandomFloatInRange(f32 a, f32 b);
void GetStateWalkerTargetKey(void* dev, s32* out);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void* GetActiveSwitchedCollider(void);
void SetStateWalkerTarget(void* dev, s32 value);
s32 GatherObjectsById(void* obj, s32 a1, s32 a2, s32 a3, s32 a4, s32* out);
void ChangeAgentState(s32 value, s32 a1, s32 a2);
void StopTimer(void* obj);
void ComputeGaugeOutputs(GaugeManager* self);
extern f32 g_gameTime[];
void RaiseScatterLevels(void* self, f32 amount);
extern u8 D_00248D30[];
extern u8 D_00248D30[];
void GetStateWalkerCurrentKey(void* p, s32* out);
void GetStateWalkerTargetKey(void* p, s32* out);

extern u8 D_00248D30[];
void ChooseObjectPoolItem(ObjectPool* p);
s32 RandomIntInRange(s32 a, s32 b);
s32 func_001A8C90(ObjectPool* h, s32 v);
s32 GetObjectWorldPosition(void* p, f32* out);
s32 GetObjectWorldRotation(void* p, f32* out);
s32 CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, void* out, f32 fa, f32 fb);
void AddAnimationPlayerRecordCallback(void* a, GaugeManager* self);
f32 RandomFloatInRange(f32 a, f32 b);


void InitPlacedObject(GaugeManager* self);
typedef void (*TimerDoneFn)(void* self);
void HandlePlacedObjectNotification(GaugeManager* self, s32 kind, void* key);
void GetStateWalkerCurrentKey(void* key, s32* out);
void SetWorldActiveFollower(void* sub, GaugeManager* self);
void StartTimer(T217D_510* self, f32 v);
void SetTimerLimit(T217D_510* self, f32 v, TimerDoneFn cb);
void StartTimerCounting(T217D_510* self);
void FinishGaugeOnTimeout(void* self);

// The coefficients of a quadratic in the gauge fraction (GaugeCurve::Eval).
struct Quadratic {
    f32 a;
    f32 b;
    f32 c;
};

// The helpers func_0014C2F0 maps the gauge fraction with: a quadratic, a clamp, a blend.
struct GaugeCurve {
    static f32 Eval(Quadratic* q, f32 t) { return q->a + t * (q->b + t * q->c); }
    static f32 Limit(f32 g, f32 lo, f32 hi)
    {
        if (g < lo) return lo;
        if (hi < g) return hi;
        return g;
    }
    static f32 Lerp(f32 s, f32 a, f32 b) { return (1.0f - s) * a + s * b; }
};

// GaugeManager::o5E0, the blend of the two parameter sets, as func_0014C2F0 reads it: pairs of
// limits and the quadratics that pick between them.
struct BlendedGaugeParams {
    f32 f00;
    f32 f04;
    u8 pad08[8];
    Quadratic q10;
    u8 pad1C[4];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    Quadratic q30;
    u8 pad3C[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    u8 pad54[0xC];
    Quadratic q60;
    u8 pad6C[4];
    f32 f70;
    f32 f74;
    u8 pad78[8];
    Quadratic q80;
    u8 pad8C[4];
    f32 f90;
    f32 f94;
    u8 pad98[8];
    Quadratic qA0;
};

extern f32 g_unitRange[];
extern f32 g_gameClock[];

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
ObjectLink g_gaugeManagerLinks[3] = { { 5, 0x3F8, 0x420 }, { 5, 0x3F9, 0x424 }, { 1, 0x3FA, 0x428 } };

void SetCameraControllerOwner(CameraController* self, Camera* owner)
{
    self->owner = owner;
}

s32 IsTopCameraController(CameraController* self)
{
    return self->owner->stack[0].ctl == self;
}

void SetCameraControllerValue(CameraController* self, s32 value)
{
    self->value = value;
}

void UpdateIdleCameraController(CameraController* self, u8* eye, u8* tail, f32 dt)
{
}


Quad16 GetCameraControllerTargetPoint(TargetCameraController* self)
{
    Quad16 r;
    if (self->f5C != 0) {
        ConvertPositionToWorld(self->f5C, &r);
    } else {
        if (GetActiveSwitchedCollider() != 0) {
            r = *(Quad16*)((u8*)GetActiveSwitchedCollider() + 0x140);
            *(f32*)&r.w[2] = *(f32*)&r.w[2] + D_00261BF8;
        } else {
            r = *(Quad16*)(*(u8**)g_camera + 0x40);
        }
    }
    return r;
}

ASM_FUNC(func_00149458);

void StartCameraSounds(CameraSoundOwner* self)
{
    StartSoundEffect(0x71, &self->f48, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    if (self->f48 != 0) {
        PauseIopVoice(self->f48->voice);
    }
    StartSoundEffect(0x70, &self->f4C, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    self->f44 = 1;
}

void PushStackValue(TargetCameraController* s, s32 value)
{
    s32 n = s->count;
    if ((u32)n < 4) {
        s->items[n] = value;
        s->count = n + 1;
    }
}

s32 PopStackValue(TargetCameraController* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    n = n - 1;
    s->count = n;
    return s->items[n];
}

s32 PeekStackValue(TargetCameraController* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    return s->items[n - 1];
}

void InitTargetCameraController(TargetCameraController* self, Camera* owner)
{
    SetCameraControllerOwner(self, owner);
    self->count = 0;
    self->f20 = 10.0f;
    PushStackValue(self, 0);
    self->f54 = 0.5f;
    self->f58 = -1.0f;
    self->f50 = 0;
}

void ActivateTargetCameraController(TargetCameraController* self)
{
    Quad4 tmp;
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
    SetCameraLookAnchor(eng, &tmp);
    self->f2C = eng->f1E4;
    SetCameraNearDistance(eng, 49.0f);
}

INCLUDE_RODATA(D_00249EA0);
INCLUDE_RODATA(jtbl_00249EB0);
INCLUDE_RODATA(jtbl_00249ED0);

ASM_FUNC(func_00149760);

void DeactivateTargetCameraController(TargetCameraController* self)
{
    Quad4 a;
    Quad4 b;
    Camera* n;

    GetCameraControllerTargetPoint(&a, self);
    GetTargetCameraControllerEyePoint(&b, self);
    n = (Camera*)self->owner;
    StopSoundRecord(self->p48, 0);
    StopSoundRecord(self->p4C, 500);
    PlaceCameraLookingAt(n, &b, &a);
    if (AreFloatsNearlyEqual(n->f1C4, self->f28, 1e-4f) == 0) {
        SnapCameraZoom(n, self->f28);
    }
    self->f5C = 0;
    if (n->f1E4 == 49.0f) {
        SetCameraNearDistance(n, self->f2C);
    }
}

void InitFrameCameraController(FrameCameraController* self, Camera* a1)
{
    SetCameraControllerOwner(self, a1);
    CameraFrameBlock* dst = &self->frame20;
    *dst = *(CameraFrameBlock*)g_identityMatrix;
}

void ActivateFrameCameraController(FrameCameraController* self)
{
    Camera* parent = self->owner;
    SetCameraLookAnchor(parent, (u8*)parent->stack[0].target + 0x370);
}

ASM_FUNC(func_0014A8F8);

void ActivateValueCameraController(ValueCameraController* obj, s32 value) { obj->value = value; }

void DeactivateValueCameraController(ValueCameraController* obj) { obj->value = 0; }

ASM_FUNC(func_0014AAA0);

void InitItemColumn(T217D_720* self)
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

void SetupItemColumn(T217D_720* self)
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

void UpdateItemColumn(T217D_720* self, f32* clock)
{
    SetScreenElementClock(self, clock);
    T217D_330* e = self->items;
    for (u32 i = 0; i < 4; i++) {
        e->vt->m17(e, clock);
        e++;
    }
}

void UpdateItemColumnSlide(T217D_720* self)
{
    UpdateScreenElementSlide(self);
    for (s32 i = 0; i < self->count; i++) {
        T217D_330* s = &self->items[i];
        s->vt->m02(s);
    }
}

void DrawItemColumn(T217D_720* self)
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

void ResizeItemColumn(T217D_720* self, s32 n, f32 x, f32 y)
{
    self->place->dx = x;
    self->place->dy = y;
    self->count = n;
    Font* q = self->font;
    SetScreenElementSize(self, self->w, (f32)q->height * q->sy * (f32)n);
    self->vt->m16(self, 2);
}

void ClearItemColumn(T217D_720* self)
{
    self->vt->m16(self, 0);
}

ASM_FUNC(func_0014AF38);

void FactorSymmetricMatrix(s32 n, f32* a, f32* l)
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

void SolveFactoredSystem(s32 n, f32* m, f32* b, f32* x)
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

void RegisterWorldListedAgent(WorldListedAgent* self)
{
    RegisterAgent(self);
    AppendToList(&self->world->list1CCC, self);
}

void UnregisterWorldListedAgent(WorldListedAgent* self) { UnregisterAgent(self); RemoveFromList(&self->world->list1CCC, self); }

void CopyWorldListedAgent(WorldListedAgent* self, void* other) { Pack10 save=self->fC10; CopyAgent(self,other); self->fC10=save; }

void InitNumberedAgent(NumberedAgent* self) { InitAgent(self); self->fC24=1; D_0027C008=0; }

void StartNumberedAgent(NumberedAgent* self) { StartAgent(self); self->fC2C=D_0027C008++; }

void SetSinCosPair(SinCosPair* self, f32 value)
{
    ComputeSinCos(&self->b, self, value);
    self->value = 0;
}

INCLUDE_RODATA(D_00249EF0);

ASM_FUNC(func_0014B6A8);

ASM_FUNC(func_0014BB08);

s32 HandleNumberedAgentObjectEvent(NumberedAgent* self)
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

void EnterNumberedAgentState(NumberedAgent* self)
{
    EnterAgentState(self);
    switch (self->f724) {
    case 0xB:
        AddToGaugeAmount(D_0027C00C, self);
        if (((GaugeSlot*)self->fC28) != 0) { ((GaugeSlot*)self->fC28)->taken = 0; self->fC28 = 0; }
        break;
    case 0xC:
        if (((GaugeSlot*)self->fC28) != 0) { ((GaugeSlot*)self->fC28)->taken = 0; self->fC28 = 0; }
        SetAnimationPlayerSpeed(self->f7E0, D_0027C00C->speed448);
        break;
    }
}

s32 ChooseAgentStateByContact(ContactAgent* self)
{
    s32 result = ChooseAgentState(self);
    if (result == 0xB) return result;
    ListedAgentView* n = (ListedAgentView*)GetActiveSwitchedCollider();
    if (n != 0 && IsContactBetweenParts(self, n) != 0) {
        Scratch_0014BDC8 buf;
        InitOwnerMessage(&buf, 0, self);
        result = 0xB;
        n->vtbl[0x50](n, &buf);
    }
    for (ListedAgentView* x = (ListedAgentView*)self->world->list1CCC.head; x != 0; x = x->next) {
        if ((void*)x != (void*)self && IsObjectOfKind(x, 0x12) != 0 && IsContactBetweenParts(self, x) != 0) {
            ChangeAgentState(x, 0xB, 0);
        }
    }
    return result;
}

s32 IsContactAgentFree(ContactAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0) return 0;
    if (self->f724 == 0xB || self->f724 == 0x10) return 0;
    return 1;
}

s32 HandleContactAgentObjectEvent(ContactAgent* self, ListedAgentView** slot)
{
    if (self->f724 == 0x10 || self->f724 == 0xB) return 1;
    if (HandleAgentObjectEvent(self, slot) == 0) return 0;
    ListedAgentView* found = (ListedAgentView*)GetActiveSwitchedCollider();
    ListedAgentView* n = *slot;
    if (n == found) {
        OwnerMessage buf;
        InitOwnerMessage(&buf, 0, self);
        n->vtbl[0x50](n, &buf);
    }
    return 1;
}

void EnterContactAgentState(ContactAgent* self)
{
    EnterAgentState(self);
    switch (self->f724) {
    case 0xB:
        CountDownGaugeContacts((void*)D_0027C00C, self);
        if (((GaugeSlot*)self->fC20) != 0) {
            ((GaugeSlot*)self->fC20)->taken = 0;
            self->fC20 = 0;
        }
        break;
    case 0xC:
        if (((GaugeSlot*)self->fC20) != 0) {
            ((GaugeSlot*)self->fC20)->taken = 0;
            self->fC20 = 0;
        }
        SetAnimationPlayerSpeed(self->f7E0, self->fC24);
        break;
    }
}

extern const GaugeParams g_defaultGaugeParams = {
    { 0x41000000, 0x40C00000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A, 0x3F19999A, 0x3F4CCCCD, 0x3FA66666, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A },
    { 3.5f, 5.0f }, { 2.0f, 2.5f },
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F59999A, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F4CCCCD, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000 }
};

void InitGaugeManager(GaugeManager* self)
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

void BlendParamSets(GaugeManager* self)
{
    s32 i = 0;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, g_gaugeManagerLinks);
    self->device = CreateStateWalker(self->f428, 0, 0x3FB, 0);
    GetStateWalkerCurrentKey(self->device, self->buf430);
    AddStateWalkerListener(self->device, self);
    for (; i < self->slotCount; i++) {
        GaugeSlot* s = &self->slots[i];
        BaseObject* n = (BaseObject*)FindFirstObjectByIdMode4(self->world, s->obj, self);
        s->obj = n;
        s->f8 = FindFirstObjectByIdMode1(n->world, 0x3F7, n);
        s->f4 = FindFirstObjectByIdMode1(n->world, 0x3F6, n);
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

void ComputeGaugeOutputs(GaugeManager* o)
{
    f32 t = GaugeCurve::Limit((f32)o->amount / (f32)o->maxAmount, 0.0f, 1.0f);
    BlendedGaugeParams* p = (BlendedGaugeParams*)o->o5E0;
    f32 s;

    s = GaugeCurve::Limit(GaugeCurve::Eval(&p->q30, t), g_unitRange[0], g_unitRange[1]);
    *(f32*)(o->buf430 + 4) = GaugeCurve::Lerp(s, p->f20, p->f28);
    *(f32*)(o->buf430 + 8) = GaugeCurve::Lerp(s, p->f24, p->f2C);

    s = GaugeCurve::Limit(GaugeCurve::Eval(&p->q60, t), g_unitRange[0], g_unitRange[1]);
    *(f32*)(o->buf430 + 0xC) = GaugeCurve::Lerp(s, p->f44, p->f4C);
    *(f32*)(o->buf430 + 0x10) = GaugeCurve::Lerp(s, p->f48, p->f50);

    *(f32*)(o->buf430 + 0x14) = GaugeCurve::Lerp(GaugeCurve::Limit(GaugeCurve::Eval(&p->q80, t), g_unitRange[0], g_unitRange[1]), p->f70, p->f74);

    *(f32*)(o->buf430 + 0x18) = GaugeCurve::Lerp(GaugeCurve::Limit(GaugeCurve::Eval(&p->qA0, t), g_unitRange[0], g_unitRange[1]), p->f90, p->f94);

    o->f44C = (s32)GaugeCurve::Lerp(GaugeCurve::Limit(GaugeCurve::Eval(&p->q10, t), g_unitRange[0], g_unitRange[1]), p->f00, p->f04);

    if (p->f40 < t && o->f464 == 0) {
        o->f464 = 1;
        o->f45C = g_gameClock[1];
    }
}

void ApplyGaugeRatioToEffect(GaugeManager* self)
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

void FinishGaugeOnTimeout(void* unused, s32 mode)
{
    if (mode == 1) {
        s32 t[2];
        GetStateWalkerTargetKey(D_0027C00C->device, &t[0]);
        GetStateWalkerCurrentKey(D_0027C00C->device, &t[1]);
        if (t[0] != 0x3FE && t[1] != 0x3FE) {
            SetStateWalkerTarget(D_0027C00C->device, 0x3FF);
            ApplyGaugeRatioToEffect(D_0027C00C);
        }
    }
}

void UpdateGaugeManager(GaugeManager* self)
{
    s32 tag;
    UpdatePlacedObject(self);
    GetStateWalkerCurrentKey(self->device, &tag);
    if (tag == 0x3FD) {
        if (self->f45C < g_gameClock[1]) {
            RunGaugeTimedEvent(self);
        }
        if (self->f460 < g_gameClock[1]) {
            ActivateRandomGaugeSlot(self);
        }
        void* p = GetActiveSwitchedCollider();
        ColliderSlots* o = (ColliderSlots*)p;
        o->vtbl[81](p);
    }
}

void ShowGaugeManagerDisplays(GaugeManager* self)
{
    s32 tag;
    GetStateWalkerCurrentKey(self->device, &tag);
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

void* GetGaugeParams(GaugeManager* self)
{
    return (u8*)self + (self->setIndex * 0xB0 + 0x480);
}

void AppendGaugeSlot(GaugeManager* self, s32 value)
{
    s32 i = self->slotCount;
    self->slotCount = i + 1;
    self->slots[i].obj = (void*)value;
}

INCLUDE_RODATA(D_00249FB4);

ASM_FUNC(func_0014C858);

void ActivateRandomGaugeSlot(GaugeManager* self)
{
    GaugeSlot* list[16];
    f32 v0[4];
    f32 v1[12];
    if (self->f454 >= self->f44C) {
        self->f460 = 3.4028235e+38f;
        return;
    }
    ChooseObjectPoolItem((ObjectPool*)self->f424);
    if (!((ObjectPool*)self->f424)->f48) return;
    s32 n = 0;
    for (s32 i = 0; i < self->slotCount; i++) {
        GaugeSlot* s = &self->slots[i];
        if (!s->taken && !s->key) list[n++] = s;
    }
    if (n <= 0) return;
    s32 idx = RandomIntInRange(0, n - 1);
    ObjectPool* h = (ObjectPool*)self->f424;
    NumberedAgent* c = (NumberedAgent*)h->f48;
    GaugeSlot* s = list[idx];
    (void)func_001A8C90(h, 0);
    GetObjectWorldPosition(s->f4, v0);
    GetObjectWorldRotation(s->f4, v1);
    c->desc02()->m1D(c, (Vec02*)v0);
    c->desc02()->m1E(c, (Mat02*)v1);
    c->desc02()->m20(c, (Vec02*)D_00248D30);
    c->desc02()->m21(c, (Vec02*)D_00248D30);
    CreateAnimationPlayerWithoutPresetTargets(s->f8, s->obj, 0, &s->key, 0.0f, 1.0f);
    AddAnimationPlayerRecordCallback(s->key, self);
    self->f454 = self->f454 + 1;
    f32 r = RandomFloatInRange(*(f32*)(self->buf430 + 4), *(f32*)(self->buf430 + 8));
    self->f460 = (*(f32*)&g_gameTime) + r;
    c->fC28 = s;
    s->taken = 1;
}

void CountDownGaugeContacts(GaugeManager* self)
{
    if (self->f458 == self->f450) {
        self->f45C = g_gameTime[0] + RandomFloatInRange(self->f43C, self->f440);
    }
    self->f458 = self->f458 - 1;
}

void AddToGaugeAmount(GaugeManager* self, NumberedAgent* arg)
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
        GetStateWalkerCurrentKey(self->device, &t1);
        GetStateWalkerTargetKey(self->device, &t2);
        void* p = GetActiveSwitchedCollider();
        ColliderQuerySlots* o = (ColliderQuerySlots*)p;
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

void HandleGaugeManagerNotification(GaugeManager* self, s32 kind, void* key)
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
            GetStateWalkerCurrentKey(key, &out);
            if (out == 0x3FD) {
                g_gaugeAmountCaption.target = &self->amount;
                g_gaugeAmountCaption.limit = &self->maxAmount;
                SetWorldActiveFollower(self->world, self);
                StartTimer(&g_timerElement, self->f2D8);
                SetTimerLimit(&g_timerElement, 0.0f, FinishGaugeOnTimeout);
                StartTimerCounting(&g_timerElement);
            }
            if (self->tag430 == 0x3FD) {
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                g_timerElement.vt->m15(&g_timerElement);
                SetWorldActiveFollower(self->world, 0);
            }
            self->tag430 = out;
        }
        break;
    }
}

