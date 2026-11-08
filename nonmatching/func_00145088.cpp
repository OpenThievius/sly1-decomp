// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 344/356, checked 2026-11-08
// NEAR (2026-11-08, night-gamec): the move: retail computes i*16 + self once and copies it for the source (move a1,a0), and copies the count from v1 to a0 before the scan; the rest is register choice
// In the context of its file, src/main/camera.cpp: its declarations before the function, bodies cut.
#include "common.h"
#include "shapes.h"
#include "collider.h"
#include "world.h"
#include "camera.h"
#include "pad_record.h"
#include "fpu.h"
#include "asm_func.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "placed_object.h"
#include "switched_collider.h"
extern void SetCameraFogNear(void*);
extern void SetCameraFogFar(void*);
extern void SetCameraFogStrength(void*);
extern void SetCameraFogColor(void*);
extern void SetCameraPlacement(void*, s32, void*);
#include "list_iter.h"
#include "game_clock.h"

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
void BuildBasisFromX(void* self, void* value);

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
f32 D_00261928[9] = { 1.0f, 5.0f, 10.0f, 12.0f, 15.0f, 12.0f, 10.0f, 5.0f, 1.0f };
f32 D_0026194C = 250.0f;
RampProfile D_00261958 = { 2500.0f, 0.0f, 0.25f, 0.0f };
void* g_camera = 0;

void InitCameraModule(void);

void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3);

// One step of a damped spring pulling pos toward target: the velocity gains (target - pos) * k
// + vel * damp over dt, and pos moves by the velocity over dt. With f224 set, pos is placed at
// target at rest.
void SpringCameraVector(Camera* self, Vec02* pos, Vec02* vel, Vec02* target, f32 k, f32 damp, f32 dt);

// The camera func_00143208 springs towards the target's offset: the spring's two vectors
// (+0x250/+0x260 and +0x270/+0x280) and the record func_00143148 reads.
struct Spring_00143208 {
    u8 pad0[0x250];
    Vec02 v250;             // 0x250
    Vec02 v260;             // 0x260
    Vec02 v270;             // 0x270
    Vec02 v280;             // 0x280
};

struct Record_00143208 {
    u8 pad0[0x10];
    Vec02 v10;              // 0x10
    u8 pad20[0x40 - 0x20];
    Vec02 v40;              // 0x40
};

extern Player* g_player;
extern const Vec02 D_00248D30;
void SpringCameraVector(Spring_00143208* self, Vec02* a, Vec02* b, const Vec02* target, f32 x, f32 y, f32 dt);
void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3);

void func_00143208(Spring_00143208* self, void* target, Record_00143208* rec, f32 dt);

// What func_001433E0 resets: the offset ComputeOffsetBehindTarget gives (+0x250) and three
// vectors after it.
struct Tracking_001433E0 {
    u8 pad0[0x250];
    Quad16 offset;          // 0x250
    Quad16 v260;            // 0x260
    Quad16 v270;            // 0x270
    Quad16 v280;            // 0x280
};

void ResetCameraTargetTracking(Tracking_001433E0* self, void* a1, Target_00143148* a2);

void ComputeCameraFogTerms(Camera* self, f32* out, f32 p);

void func_00189F58(void* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
f32 func_002054F0(f32 x);

void func_00143560(Camera* self);

void InitCamera(Camera* self);

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

// A part's state as func_00143BE0 writes it (0x28 bytes, PlacedObject::partStates): the time
// until which the part is faded.
struct PartFade {
    u8 pad00[0x14];
    f32 until;              // 0x14
    u8 pad18[0x28 - 0x18];
};

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*), s32 p4, s32* n, Collider*** list);

void func_00143BE0(Camera* self);

void UpdateCamera(Camera* self, s32 flag, f32 dt);

// The camera's frame as func_00144128 reads it: rows at 0x80, a position at 0x40, two scales.
struct Frame_00144128 {
    u8 pad0[0x40];
    Vec02 pos;              // 0x40
    u8 pad50[0x80 - 0x50];
    Mat02 rot;              // 0x80
    u8 padB0[0x1F0 - 0xB0];
    f32 scaleY;             // 0x1F0
    f32 scaleZ;             // 0x1F4
};

void func_00144128(Frame_00144128* self, f32* a, Vec02* out);

void func_001441C0(Frame_00144128* self, Vec02* in, f32* out);

void UpdateCameraLocation(Camera* self);

void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out);

// v made unit length: DivX by its Length.
static inline u128 Unit(u128 v);

void func_001443C8(Mat02* m, Vec02* out, f32 x, f32 y);

void WriteCameraMatricesPacket(u8* self);

void SetCameraPlacement(Camera* self, Quad16* a, Quad16* b);

void PlaceCameraLookingAt(Camera* self, void* p, s32 q);

void ComputeLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* in, f32* x, f32* y, f32* z);

void ApplyLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* out, f32 x, f32 y, f32 z);

void SetCameraLookAnchor(Camera* self, Quad16* arg);

void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);

void MoveMemory(void* dst, void* src, s32 bytes);

void PushCameraController(Camera* self, s32 key, CameraController* ctl, void* target, s32 arg)
{
    s32 i;
    for (i = 0; i < self->stackCount; i++) {
        if (self->stack[i].key < key) {
            break;
        }
    }
    s32 o = i * 0x10;
    MoveMemory((u8*)(o + (s32)self) + 0x3E4, (u8*)(o + (s32)self) + 0x3D4, (self->stackCount - i) * 0x10);
    self->stack[i].key = key;
    self->stack[i].ctl = ctl;
    self->stack[i].target = target;
    self->stack[i].arg = arg;
    self->stackCount++;
    CameraControllerFn fn = ctl->vt->m02;
    if (fn != 0) {
        fn(ctl, arg);
    }
    if (i == 0) {
        if (self->stackCount >= 2) {
            CameraController* o = self->stack[1].ctl;
            CameraControllerFn fn1 = o->vt->m01;
            if (fn1 != 0) {
                fn1(o, self->stack[1].arg);
            }
        }
        self->f364 = g_gameTime;
        CameraControllerFn fn0 = ctl->vt->m00;
        if (fn0 != 0) {
            fn0(ctl, arg);
        }
    }
}
