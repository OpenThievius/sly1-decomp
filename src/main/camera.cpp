// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "shapes.h"
#include "collider.h"
#include "world.h"
#include "camera.h"
#include "pad_record.h"
#include "asm_func.h"
extern void SetCameraFogNear(void*);
extern void SetCameraFogFar(void*);
extern void SetCameraFogStrength(void*);
extern void SetCameraFogColor(void*);
extern void SetCameraPlacement(void*, s32, void*);
#include "list_iter.h"


void SetCameraNearDistance(void* arg);



void SetCameraDistanceScale(void* arg);



// Built at startup: the compiler's initialiser and constructor for this file are func_001460B8
// and func_001460E0 (config/us/generated.tsv).
struct PackedRgba
{
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
    PackedRgba(u32 v) { rgba = v; }
};

void UpdateCameraProjection(void* self);








struct Target_00143148 {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
};

void ComputePolarOffset(void* self, f32 x, f32 y, f32 z);



void FitReciprocalThroughPoints(f32* a, f32* b, f32 x, f32 y, f32 z, f32 w);




void SnapCameraZoom(void* self);




void SetCameraFarDistance(void* self);








void PlaceCameraLookingAt(void* self, void* a, void* b);
void SetCameraControllerValue(CameraController* p, s32 zero);
void PushCameraController(void* self, s32 a1, void* a2, s32 a3, s32 a4);







void CopyMemory(void* dst, void* src, u32 size);






typedef int s32;
typedef unsigned char u8;
typedef float f32;


void UpdateCameraProjection(void* self);



typedef int s32;
typedef unsigned char u8;
typedef float f32;


void UpdateCameraProjection(void* self);



void UpdateCameraProjection(void* self);



void UpdateCameraProjection(void* self);













void SetCameraPlacement(void* self, void* a, void* b);




struct __attribute__((packed)) Value_00143A08 { u32 value; };


// EXACT: float constants and .data floats as locals, 1.0f stores in source order 1C0,1C4,1C8

// What func_00143648 copies whole: the four settings at 0x1D0 (from D_002618B8), the fog
// colour at 0x204 and the three rows of the identity frame at 0x80.
struct __attribute__((packed)) ParamBlock16 {
    u64 a;
    u64 b;
};

struct __attribute__((packed)) FogColorWord {
    s32 a;
};

struct __attribute__((aligned(16))) FrameRow {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

void InitObject(BaseObject* self);
void UpdateCameraProjection(Camera* self);
void SetCameraControllerOwner(CameraController* self, Camera* owner);
void InitTargetCameraController(TargetCameraController* self, Camera* owner);
void InitFrameCameraController(FrameCameraController* self, Camera* owner);
void ResetCamera(Camera* self, s32 a1);

extern u8 g_identityMatrix[];
// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_00217398[];
extern const Fn_Table D_002173B0[];
extern const Fn_Table D_002173C8[];
extern const Fn_Table D_002173E0[];
extern const Fn_Table D_002173F8[];



extern s32 g_padRouting;

f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, void* p, void* q);
void ResetCameraTargetTracking(Camera* c, void* n, void* x);
void UpdateCameraTargetTracking(Camera* c, void* n, f32 dt, void* x);
void SnapCameraZoom(Camera* c, f32 v);
void UpdateCameraProjection(Camera* c);


typedef void (*VFn_143E40)(void* self, f32 dt, void* a);





f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);




















extern f32 g_gameTime;




void PushStackValue(TargetCameraController* self, s32 value);


s32 PopStackValue(TargetCameraController* self);


s32 PeekStackValue(TargetCameraController* self);


void func_00144008(void* self);
void LookupValueTreeLeaf(void* a, void* b, void* c);

extern World* g_currentWorld;






extern u8 g_vifPacketWriter[];

void BeginDmaTag(void* f);
void WriteVifBaseOffset(void* s, s32 a, s32 b);
void CopyWordsToWriter(void* s, s32 a, s32 b, void* c, s32 d);
void CloseDmaTag(void* self);





void UpdateCameraMatrices(Camera* self);



// NEAR: only a0/a1 saved regs swapped (s0/s1) and the four loads use the other base; stores/frame match


void InitIdentityMatrix(void* self);
void* InvertMatrix4x4(void* a0, void* a1);
void MultiplyMatrices(void* out, void* b, void* in);




void func_00144BE8(Camera* a, s32 b, void* c, s32 d, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);





void ApplyLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* out, f32 x, f32 y, f32 z);
void ComputeLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* out, f32* x, f32* y, f32* z);




s32 CollectTreeNodeSpans(TreeNode03* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 MergeOverlappingSpans(s32 n, void* recs);




extern f32 g_gameTime;

void InitCameraModule(void);
void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3);
void ComputeCameraFogTerms(Camera* self, f32* out, f32 p);
void SnapCurrentCameraZoom(void);
void SetCurrentCameraNearDistance(void);
void SetCurrentCameraFarDistance(void);
void SetCurrentCameraFogNear(void);
void SetCurrentCameraFogFar(void);
void SetCurrentCameraFogStrength(void);
void SetCurrentCameraFogColor(void);
void SetCurrentCameraDistanceScale(void);
void SetCameraPosition(void* self, void* value);
void SetCameraOrientation(void* arg, void* arg2);
void SnapCameraZoom(void* self, f32 x);
void SetCameraNearDistance(void* self, f32 x);
void SetCameraFarDistance(Camera* self, f32 value);
void SetCameraFogNear(Camera* self, f32 value);
void SetCameraFogFar(Camera* self, f32 value);
void SetCameraFogStrength(void* ptr, f32 value);
void SetCameraFogColor(void* self, void* value);
void SetCameraDistanceScale(Camera* self, f32 value);
void ResetCamera(Camera* self, s32 flag);
void ClearCameraObjectList(Camera* obj);
void AddCameraObject(Camera* list, void* item);
void RemoveCameraObject(Camera* list, s32 value);
s32 IsCameraObstacle(void* unused, Collider* e);
void UpdateCamera(Camera* self, s32 flag, f32 dt);
void UpdateCameraLocation(Camera* self);
void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out);
void WriteCameraMatricesPacket(u8* self);
void SetCameraPlacement(Camera* self, Quad16* a, Quad16* b);
void PlaceCameraLookingAt(Camera* self, void* p, s32 q);
void SetCameraLookAnchor(Camera* self, Quad16* arg);
void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);
void RemoveCameraControllers(Camera* self, s32 flags, s32 k0, CameraController* k1, s32 k2, s32 k3);
void RequestCameraSnap(Camera* self, f32* src);
void QueueCameraSnap(Camera* self);
void RequestPlainCameraSnap(void* p);
s32 FindFirstFreeSpan(s32 count, Collider** objs, f32 thresh, void* a2, void* a3, f32* lo, f32* hi);
s32 HasColliderSecondTree(void* unused, Collider* other);
void PushCameraStackValue(Camera* self, s32 value);
s32 PopCameraStackValue(Camera* self);
s32 PeekCameraStackValue(Camera* self);
void SetCameraControllerSettings(Camera* obj, s32 value, f32 first, f32 second);
void RecordCameraTimestamp(Camera* obj);

// The file's .data, in retail's order; the labels only its assembly reads are included.
f32 D_00261880[4] = { 0.0f, -2000.0f, 500.0f, 0.0f };
f32 D_00261890[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_002618A0 = 5e+02f;
f32 D_002618A4 = 2e+04f;
f32 D_002618A8 = 0.5f;
PackedRgba D_002618B0(0x80303030);
f32 D_002618B8[4] = { 0.5f, 0.0f, 0.1f, 10.0f };
INCLUDE_DATA(D_002618C8);
INCLUDE_DATA(D_002618CC);
INCLUDE_DATA(D_002618D0);
INCLUDE_DATA(D_002618E0);
INCLUDE_DATA(D_002618F0);
INCLUDE_DATA(D_00261900);
INCLUDE_DATA(D_00261910);
INCLUDE_DATA(D_00261920);
INCLUDE_DATA(D_00261924);
INCLUDE_DATA(D_00261928);
INCLUDE_DATA(D_0026194C);
INCLUDE_DATA(D_00261950);
INCLUDE_DATA(D_00261958);
INCLUDE_DATA(D_00261970);
INCLUDE_DATA(D_00261980);
void* g_camera = 0;

void InitCameraModule(void)
{
}

void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3)
{
    ComputePolarOffset(a3, a2->f30 + 3.1415927f, a2->f34, 0.0f);
}

ASM_FUNC(func_00143180);

ASM_FUNC(func_00143208);

ASM_FUNC(func_001433E0);

ASM_FUNC(func_00143418);

void ComputeCameraFogTerms(Camera* self, f32* out, f32 p)
{
    f32 one = 1.0f;
    f32 scale = 4080.0f;
    f32 a = self->f200 * p;
    f32 b = self->f1FC;
    f32 c = self->f1F8;
    FitReciprocalThroughPoints(out, out + 1, one, scale, b / c, (one - a) * scale);
    out[0] = out[0] + 8388608.0f;
    out[2] = self->f1F8;
    out[3] = out[0] + 36864.0f;
}

ASM_FUNC(func_00143560);

void InitCamera(Camera* self)
{
    u8* s = (u8*)self;

    InitObject(self);
    f32 one = 1.0f;
    *(f32*)(s + 0x1C0) = one;
    *(f32*)(s + 0x1C4) = one;
    *(f32*)(s + 0x1C8) = one;
    *(struct ParamBlock16*)(s + 0x1D0) = *(struct ParamBlock16*)D_002618B8;
    f32 k = 1.29870129f;
    f32 x = D_002618A0;
    f32 y = D_002618A4;
    f32 z = D_002618A8;
    f32 h = 100.0f;
    f32 t = 20000.0f;
    *(f32*)(s + 0x1E0) = k;
    *(f32*)(s + 0x1E4) = h;
    *(f32*)(s + 0x1E8) = t;
    *(f32*)(s + 0x1F8) = x;
    *(f32*)(s + 0x1FC) = y;
    *(f32*)(s + 0x200) = z;
    *(struct FogColorWord*)(s + 0x204) = *(struct FogColorWord*)&D_002618B0;
    *(struct FrameRow*)(s + 0x80) = *(struct FrameRow*)g_identityMatrix;
    *(struct FrameRow*)(s + 0x90) = *(struct FrameRow*)(g_identityMatrix + 0x10);
    *(struct FrameRow*)(s + 0xA0) = *(struct FrameRow*)(g_identityMatrix + 0x20);
    UpdateCameraProjection(self);
    self->ctl454.vt = (const CameraControllerVt*)D_00217398;
    SetCameraControllerOwner(&self->ctl454, self);
    self->ctl460.vt = (const CameraControllerVt*)D_002173B0;
    InitTargetCameraController(&self->ctl460, self);
    self->ctl4C0.vt = (const CameraControllerVt*)D_002173C8;
    InitFrameCameraController(&self->ctl4C0, self);
    self->ctl510.vt = (const CameraControllerVt*)D_002173E0;
    SetCameraControllerOwner(&self->ctl510, self);
    self->ctl520.vt = (const CameraControllerVt*)D_002173F8;
    SetCameraControllerOwner(&self->ctl520, self);
    ResetCamera(self, 1);
}

void SnapCurrentCameraZoom(void)
{
    SnapCameraZoom(g_camera);
}

void SetCurrentCameraNearDistance(void)
{
    SetCameraNearDistance(g_camera);
}

void SetCurrentCameraFarDistance(void)
{
    SetCameraFarDistance(g_camera);
}

void SetCurrentCameraFogNear(void) { SetCameraFogNear(g_camera); }

void SetCurrentCameraFogFar(void) { SetCameraFogFar(g_camera); }

void SetCurrentCameraFogStrength(void) { SetCameraFogStrength(g_camera); }

void SetCurrentCameraFogColor(void) { SetCameraFogColor(g_camera); }

void SetCurrentCameraDistanceScale(void)
{
    SetCameraDistanceScale(g_camera);
}

void SetCameraPosition(void* self, void* value)
{
    SetCameraPlacement(self, value, 0);
}

void SetCameraOrientation(void* arg, void* arg2) { SetCameraPlacement(arg, 0, arg2); }

void SnapCameraZoom(void* self, f32 x)
{
    Camera* c = (Camera*)self;
    c->f1C4 = x;
    c->f1C8 = x;
    c->i1CC = 0;
    UpdateCameraProjection(self);
}

void SetCameraNearDistance(void* self, f32 x)
{
    Camera* c = (Camera*)self;
    c->f1E4 = x;
    UpdateCameraProjection(self);
}

void SetCameraFarDistance(Camera* self, f32 value)
{
    self->f1E8 = value;
    UpdateCameraProjection(self);
}

void SetCameraFogNear(Camera* self, f32 value)
{
    self->f1F8 = value;
    UpdateCameraProjection(self);
}

void SetCameraFogFar(Camera* self, f32 value)
{
    self->f1FC = value;
    UpdateCameraProjection(self);
}

void SetCameraFogStrength(void* ptr, f32 value)
{
    Camera* self = (Camera*)ptr;
    self->f200 = value;
    UpdateCameraProjection(self);
}

void SetCameraFogColor(void* self, void* value)
{
    *(Value_00143A08*)((u8*)self + 0x204) = *(Value_00143A08*)value;
    UpdateCameraProjection(self);
}

void SetCameraDistanceScale(Camera* self, f32 value)
{
    self->f1C0 = value;
    UpdateCameraProjection(g_camera);
}

void ResetCamera(Camera* self, s32 flag)
{
    if (flag != 0) {
        PlaceCameraLookingAt(self, D_00261880, D_00261890);
    }
    self->stackCount = 0;
    SetCameraControllerValue(&self->ctl454, 0);
    PushCameraController(self, 0, &self->ctl454, 0, 0);
    RequestCameraSnap(self, 0);
    self->f21C = 0x0FFFFFFF;
    self->f218 = -10.0f;
}

void ClearCameraObjectList(Camera* obj)
{
    obj->f340 = 0;
}

void AddCameraObject(Camera* list, void* item)
{
    u32 n = list->f340;
    if (n < 8) {
        list->f344[n] = item;
        list->f340 = n + 1;
    }
}

void RemoveCameraObject(Camera* list, s32 value)
{
    for (s32 i = 0; i < list->f340; i++) {
        if (value == ((s32*)list->f344)[i]) {
            CopyMemory(&((s32*)list->f344)[i], &((s32*)list->f344)[i + 1], (list->f340 - i - 1) * 4);
            list->f340--;
            return;
        }
    }
}

s32 IsCameraObstacle(void* unused, Collider* e)
{
    s64 field = 0xF000;
    s64 want = 0x8000;
    s32 r = 0;
    field <<= 20;
    want <<= 17;
    if ((e->flags538 & field) == want) {
        goto set;
    }
    if (e->nodeGroups == 0) {
        goto done;
    }
set:
    r = 1;
done:
    return r;
}

ASM_FUNC(func_00143BE0);

void UpdateCamera(Camera* self, s32 flag, f32 dt)
{
    if (self->f220 != 0) {
        self->f220 = 0;
        self->f224 = 1;
        self->f228 = 0;
    }
    if (self->stackCount > 0) {
        CameraController* n = self->stack[0].ctl;
        CameraController* prev = 0;
        void* last = 0;
        if (n != 0) {
            do {
                void* o = self->stack[0].target;
                u8* x;
                if (o != 0) {
                    x = (u8*)self + 0x2F0;
                    if (o != last) {
                        ((VFn_143E40)(*(void***)o)[0x124 / 4])(o, dt, x);
                        if (prev != 0 || o != self->f2E0) {
                            ResetCameraTargetTracking(self, o, x);
                        }
                        UpdateCameraTargetTracking(self, o, dt, x);
                        self->f2E0 = o;
                        last = o;
                    }
                } else {
                    x = 0;
                }
                const CameraControllerVt* vt = n->vt;
                if (vt->m04 != 0) {
                    PadRecord* t = (g_padRouting & 1) ? &g_padRecord : &g_blankPadRecord;
                    vt->m04(n, x, (u8*)t, dt);
                }
                prev = n;
                if (self->stackCount <= 0) break;
                n = self->stack[0].ctl;
            } while (n != prev);
        }
    }
    if (self->f224 != 0) {
        SnapCameraZoom(self, self->f1C8);
    } else if (self->f1C4 != self->f1C8) {
        self->f1C4 = ApproachValueClampingVelocity(self->f1C4, self->f1CC, self->f1C8, dt, &self->f1D0, &self->f1CC);
        UpdateCameraProjection(self);
    }
    if (flag != 0) {
        self->f228 = 0;
        self->f224 = 0;
    }
}

ASM_FUNC(func_00144008);

ASM_FUNC(func_00144128);

ASM_FUNC(func_001441C0);

void UpdateCameraLocation(Camera* self)
{
    Quad16 in;
    s32 out;
    World* g;

    func_00144008(self);
    g = g_currentWorld;
    if (g != 0) {
        in = *(Quad16*)self->f40;
        LookupValueTreeLeaf((void*)g->f1EC4, &in, &out);
        if (out != 0) {
            self->f21C = out;
        }
    }
}

void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out)
{
    Mat4 m;
    Mat4 v;
    Quad16 r[4];
    f32* d0;
    f32* d1;
    f32* d2;
    f32* d3;
    InitIdentityMatrix(&m);
    f32* pb = b;
    f32* pa = a;
    d3 = m.m[3];
    d2 = m.m[2];
    d1 = m.m[1];
    d0 = m.m[0];
    s32 n = 2;
    do {
        n--;
        f32 w = *pb;
        f32 x = -pa[4];
        f32 y = -pa[8];
        f32 z = pa[0];
        *d0++ = x;
        *d1++ = y;
        *d2++ = z;
        *d3++ = w;
        pb++;
        pa++;
    } while (n >= 0);
    InvertMatrix4x4(&m, &v);
    MultiplyMatrices(r, c, &v);
    out[0] = r[0];
    out[1] = r[1];
    out[2] = r[2];
    out[3] = r[3];
}

ASM_FUNC(func_001443C8);

ASM_FUNC(func_00144540);

void WriteCameraMatricesPacket(u8* self)
{
    BeginDmaTag(g_vifPacketWriter);
    WriteVifBaseOffset(g_vifPacketWriter, 0, 0);
    CopyWordsToWriter(g_vifPacketWriter, 0xC, 4, self + 0x100, 4);
    CopyWordsToWriter(g_vifPacketWriter, 0xC, 4, self + 0x140, 8);
    CloseDmaTag(g_vifPacketWriter);
}

void SetCameraPlacement(Camera* self, Quad16* a, Quad16* b)
{
    if (a != 0) {
        *(Quad16*)self->f40 = *a;
    }
    if (b != 0) {
        *(Quad16*)self->f80 = b[0];
        *(Quad16*)self->f90 = b[1];
        *(Quad16*)self->fA0 = b[2];
    }
    UpdateCameraMatrices(self);
    f32 zero = 0.0f;
    self->f2C0 = zero;
    self->f2BC = zero;
    self->f2B4 = zero;
    self->f2B0 = zero;
    self->f2B8 = zero;
}

void PlaceCameraLookingAt(Camera* self, void* p, s32 q)
{
    func_00144BE8(self, 0, p, q, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

ASM_FUNC(func_00144978);

ASM_FUNC(func_00144AA0);

void SetCameraLookAnchor(Camera* self, Quad16* arg)
{
    Quad16 tmp;
    ApplyLookFrameCoordinates((Quad16*)self->f2D0, (Quad16*)self->f40, &tmp, self->f2B0, self->f2B4, self->f2B8);
    ComputeLookFrameCoordinates(arg, (Quad16*)self->f40, &tmp, &self->f2B0, &self->f2B4, &self->f2B8);
    *(Quad16*)self->f2D0 = *arg;
}

ASM_FUNC(func_00144BE8);

void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out)
{
    f32 t;
    f32 x;
    f32 y;
    switch (mode) {
    case 0:
        y = p->f44;
        x = p->f40;
        goto call;
    case 1:
        y = p->f78;
        x = p->f74;
        goto call;
    default:
        goto zero;
    }
call:
    t = ArctangentOfRatio(-x, y);
    goto store;
zero:
    t = 0.0f;
store:
    *out = WrapAngle(t + ArctangentOfRatio(self->g80[1], self->g80[0]));

}

LINKER_REMNANT(func_00145080);

INCLUDE_ASM(func_00145088);

void RemoveCameraControllers(Camera* self, s32 flags, s32 k0, CameraController* k1, s32 k2, s32 k3)
{
    s32 s5 = 0;
    CameraController* s4 = 0;
    s32 i = 0;
    CameraControllerEntry* w = self->stack;
    CameraControllerEntry* r = w;
    for (; i < self->stackCount; i++, r++) {
        if ((!(flags & 1) || k0 == r->key) && (!(flags & 2) || k1 == r->ctl) &&
            (!(flags & 4) || k2 == (s32)r->target) && (!(flags & 8) || k3 == r->arg)) {
            if (i == 0) {
                s5 = r->arg;
                s4 = r->ctl;
            }
            CameraController* o = r->ctl;
            CameraControllerFn fn = o->vt->m03;
            if (fn != 0) {
                fn(o, r->arg);
            }
        } else {
            *w = *r;
            w++;
        }
    }
    self->stackCount = w - self->stack;
    if (s4 != 0) {
        CameraControllerFn fn = s4->vt->m01;
        if (fn != 0) {
            fn(s4, s5);
        }
        if (self->stackCount > 0) {
            self->f364 = g_gameTime;
            CameraController* o = self->stack[0].ctl;
            CameraControllerFn fn2 = o->vt->m00;
            if (fn2 != 0) {
                fn2(o, self->stack[0].arg);
            }
        }
    }
}

ASM_FUNC(func_001453B0);

ASM_FUNC(func_00145438);

ASM_FUNC(func_001454E0);

void RequestCameraSnap(Camera* self, f32* src)
{
    self->f224 = 1;
    if (src != 0) {
        self->f228 = 1;
        self->f22C = *src;
    }
}

void QueueCameraSnap(Camera* self)
{
    self->f220 = 1;
}

void RequestPlainCameraSnap(void* p)
{
    RequestCameraSnap((Camera*)p, 0);
}

ASM_FUNC(func_00145610);

ASM_FUNC(func_00145718);

s32 FindFirstFreeSpan(s32 count, Collider** objs, f32 thresh, void* a2, void* a3, f32* lo, f32* hi)
{
    ColliderSpan recs[64];
    s32 total = 0;
    s32 i;
    s32 k;
    s32 j;
    f32 f2;
    f32 f1;
    for (i = 0; i < count; i++) {
        total += CollectTreeNodeSpans(objs[i]->tree2.nodes, a2, a3, 0, 0x40 - total, &recs[total]);
    }
    total = MergeOverlappingSpans(total, recs);
    j = 0;
    for (k = 0;; k++) {
        if (total < k) return 0;
        f2 = 0.0f;
        if (k > 0) f2 = recs[j - 1].time[1];
        if (k < total) f1 = recs[j].time[0];
        else f1 = 1.0f;
        j++;
        if (thresh < f1 - f2) break;
    }
    if (lo != 0) *lo = f2;
    if (hi != 0) *hi = f1;
    return 1;
}

// The file's one .rodata word, the largest float, which the original assembly func_00145950
// loads.
extern const f32 D_00249E4C = 3.4028235e+38f;
ASM_FUNC(func_00145950);

ASM_FUNC(func_00145B68);

s32 HasColliderSecondTree(void* unused, Collider* other)
{
    return other->tree2.nodes != 0;
}

ASM_FUNC(func_00145DE8);

ASM_FUNC(func_00145E68);

void PushCameraStackValue(Camera* self, s32 value)
{
    PushStackValue(&self->ctl460, value);
}

s32 PopCameraStackValue(Camera* self)
{
    return PopStackValue(&self->ctl460);
}

s32 PeekCameraStackValue(Camera* self)
{
    return PeekStackValue(&self->ctl460);
}

void SetCameraControllerSettings(Camera* obj, s32 value, f32 first, f32 second) { obj->ctl460.f50 = value; obj->ctl460.f54 = first; obj->ctl460.f58 = second; }

void RecordCameraTimestamp(Camera* obj) { obj->f218 = g_gameTime; }

ASM_FUNC(func_00146038);


