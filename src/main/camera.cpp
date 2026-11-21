// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_functions.h"
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
#include "list_iter.h"
#include "game_clock.h"
#include "mul_rotation.h"
#include "value_range.h"
#include "mesh_hit_sample.h"
#include "functions/active_set_solver.h"
#include "functions/base_object.h"
#include "functions/camera_controller.h"
#include "functions/collider_contact.h"
#include "functions/collider_span.h"
#include "functions/pooled_object.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/zone_collider.h"








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

void UpdateCameraProjection(Camera* self);








struct Target_00143148 {
    u8 pad0[0x30];
    f32 heading;
    f32 distance;
};








void SnapCameraZoom(void* self, f32 x);




void SetCameraFarDistance(Camera* self, f32 value);








void PlaceCameraLookingAt(Camera* self, const Vec4* target, const Vec4* focus);
void PushCameraController(Camera* self, s32 key, CameraController* ctl, void* target, void* arg);







void CopyMemory(void* dst, void* src, u32 size);






typedef int s32;
typedef unsigned char u8;
typedef float f32;


void UpdateCameraProjection(Camera* self);



typedef int s32;
typedef unsigned char u8;
typedef float f32;


void UpdateCameraProjection(Camera* self);



void UpdateCameraProjection(Camera* self);



void UpdateCameraProjection(Camera* self);













void SetCameraPlacement(Camera* self, Quad16* a, Quad16* b);




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

void UpdateCameraProjection(Camera* self);
void ResetCamera(Camera* self, s32 a1);

extern u8 g_identityMatrix[];
// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table g_cameraControllerMethods[];
extern const Fn_Table g_targetCameraControllerMethods[];
extern const Fn_Table g_frameCameraControllerMethods[];
extern const Fn_Table g_valueCameraControllerMethods[];
extern const Fn_Table g_onOffCameraControllerMethods[];



extern s32 g_padRouting;

struct Tracking_001433E0;
void ResetCameraTargetTracking(Tracking_001433E0* self, void* a1, Target_00143148* a2);
struct Spring_00143208;
struct Record_00143208;
void UpdateCameraTargetTracking(Spring_00143208* self, void* target, f32 dt, Record_00143208* rec);
void SnapCameraZoom(void* self, f32 x);
void UpdateCameraProjection(Camera* c);


typedef void (*VFn_143E40)(void* self, f32 dt, void* a);





extern "C" f32 ArctangentOfRatio(f32 y, f32 x);




















extern f32 g_gameTime;










void BuildCameraGroundFrame(void* self);
void LookupValueTreeLeaf(void* a, void* b, void* c);

extern World* g_currentWorld;






extern u8 g_vifPacketWriter[];

struct PacketWriter;





void UpdateCameraMatrices(Camera* self);



// NEAR: only a0/a1 saved regs swapped (s0/s1) and the four loads use the other base; stores/frame match


void InitIdentityMatrix(Mat4* self);
s32 InvertMatrix4x4(void* a0, void* a1);
Mat4A MultiplyMatrices(const Mat4A& a, const Mat4A& b);




void UpdateOrbitCameraPlacement(Camera* self, s32 flags, const Vec4* target, const Vec4* focus, s32 e, f32 gain, f32 damp,
                   f32 unused, f32 yawOffset, f32 pitchOffset, f32 dt);





void ApplyLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* out, f32 x, f32 y, f32 z);
void ComputeLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* out, f32* x, f32* y, f32* z);
void BuildBasisFromX(Vec4* x, Mat3* out);








extern f32 g_gameTime;

void InitCameraModule(void);
void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3);
void ComputeCameraFogTerms(Camera* self, f32* out, f32 p);
void SnapCurrentCameraZoom(void* unused0, f32 zoom);
void SetCurrentCameraNearDistance(void* unused0, f32 distance);
void SetCurrentCameraFarDistance(void* unused0, f32 distance);
void SetCurrentCameraFogNear(void* unused0, f32 distance);
void SetCurrentCameraFogFar(void* unused0, f32 distance);
void SetCurrentCameraFogStrength(void* unused0, f32 strength);
void SetCurrentCameraFogColor(void* unused0, void* color);
void SetCurrentCameraDistanceScale(void* unused0, f32 scale);
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
void RemoveCameraObject(Camera* list, void* item);
s32 IsCameraObstacle(void* unused, Collider* e);
void UpdateCamera(Camera* self, s32 flag, f32 dt);
void UpdateCameraLocation(Camera* self);
void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out);
void WriteCameraMatricesPacket(Camera* self);
void SetCameraPlacement(Camera* self, Quad16* a, Quad16* b);
void PlaceCameraLookingAt(Camera* self, const Vec4* target, const Vec4* focus);
void SetCameraLookAnchor(Camera* self, Quad16* arg);
void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);
void RemoveCameraControllers(Camera* self, s32 flags, s32 k0, CameraController* k1, void* k2, void* k3);
void RequestCameraSnap(Camera* self, f32* src);
void QueueCameraSnap(Camera* self);
void RequestPlainCameraSnap(void* p);
s32 FindFirstFreeSpan(s32 count, Collider** objs, void* a2, void* a3, f32 thresh, f32* lo, f32* hi);
s32 HasColliderSecondTree(void* unused, Collider* other);
void PushCameraStackValue(Camera* self, s32 value);
s32 PopCameraStackValue(Camera* self);
s32 PeekCameraStackValue(Camera* self);
void SetCameraControllerSettings(Camera* obj, s32 value, f32 first, f32 second);
void RecordCameraTimestamp(Camera* obj);

// The file's .data, in retail's order; the labels only its assembly reads are included.
f32 g_cameraResetPosition[4] = { 0.0f, -2000.0f, 500.0f, 0.0f };
f32 g_cameraResetTarget[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 g_cameraDefaultFogNear = 5e+02f;
f32 g_cameraDefaultFogFar = 2e+04f;
f32 g_cameraDefaultFogStrength = 0.5f;
PackedRgba g_cameraDefaultFogColor(0x80303030);
f32 g_cameraDefaultRamp[4] = { 0.5f, 0.0f, 0.1f, 10.0f };
f32 g_cameraSwingDuration = 0.5f;
f32 g_cameraSwingRate = 50.0f;
f32 g_cameraSwingFalloffCurve[4] = { 1.0f, -2.0f, 1.0f, 0.0f };
s32 g_cameraSwingOffset[4] = {0};
f32 g_cameraSwingTurn[4] = { 0.05f, 0.0f, 0.0f, 0.0f };
s32 g_cameraSwingCornerShift[4] = {0};
s32 g_cameraSwingTiltShift[4] = {0};
f32 g_cameraAimSpringStiffness = 15.0f;
f32 g_cameraAimSpringDamping = -8.0f;
f32 g_freePointRingSamples[9] = { 1.0f, 5.0f, 10.0f, 12.0f, 15.0f, 12.0f, 10.0f, 5.0f, 1.0f };
f32 g_cameraProbeRadius = 250.0f;
f32 g_cameraProbeLimitMargin[2] = { 1500.0f, 0.0f };
RampProfile g_cameraClearanceRamp = { 2500.0f, 0.0f, 0.25f, 0.0f };
Vec4 g_cameraProbeBoxMin = { -250.0f, -250.0f, -250.0f, 0.0f };
Vec4 g_cameraProbeBoxMax = { 250.0f, 250.0f, 250.0f, 0.0f };
Camera* g_camera = 0;

// Empty: the camera module needs no set-up of its own.
void InitCameraModule(void)
{
}

// Gives in a3 the offset that puts the camera behind the target: its distance away, opposite its
// heading (heading plus pi).
void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3)
{
    ComputePolarOffset((Vec3*)a3, a2->heading + 3.1415927f, a2->distance, 0.0f);
}

// One step of a damped spring pulling pos toward target: the velocity gains (target - pos) * k
// + vel * damp over dt, and pos moves by the velocity over dt. With f224 set, pos is placed at
// target at rest.
void SpringCameraVector(Camera* self, Vec4* pos, Vec4* vel, Vec4* target, f32 k, f32 damp, f32 dt)
{
    if (self->snapping != 0) {
        *pos = *target;
        Vu0::Q(*vel) = Vu0::Zero();
        return;
    }
    Vec4 d;
    Vec4 acc;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*target), Vu0::Q(*pos));
    Vu0::Q(acc) = Vu0::MulXSum(Vu0::Q(d), Vu0::Scalar(k), Vu0::Q(*vel), Vu0::Scalar(damp));
    Vu0::Q(*vel) = Vu0::MulAddX(Vu0::Q(*vel), Vu0::Q(acc), Vu0::Scalar(dt));
    Vu0::Q(*pos) = Vu0::MulAddX(Vu0::Q(*pos), Vu0::Q(*vel), Vu0::Scalar(dt));
}

// The camera func_00143208 springs towards the target's offset: the spring's two vectors
// (+0x250/+0x260 and +0x270/+0x280) and the record func_00143148 reads.
struct Spring_00143208 {
    u8 pad0[0x250];
    Vec4 v250;             // 0x250
    Vec4 v260;             // 0x260
    Vec4 v270;             // 0x270
    Vec4 v280;             // 0x280
};

struct Record_00143208 {
    u8 pad0[0x10];
    Vec4 v10;              // 0x10
    u8 pad20[0x40 - 0x20];
    Vec4 v40;              // 0x40
};

extern Player* g_player;
extern const Vec4 g_zeroVector;
void SpringCameraVector(Camera* self, Vec4* pos, Vec4* vel, Vec4* target, f32 k, f32 damp, f32 dt);
void ComputeOffsetBehindTarget(void* a0, void* a1, Target_00143148* a2, void* a3);

// Moves the camera's tracking offset (v250, with velocity v260) and look offset (v270 and v280)
// toward the offset behind the target by springs; for the player the springs depend on its camera
// state (0 normal, 1 slower, 2 position only). Writes the tracked position, the record's base plus
// the offset, into the record.
void UpdateCameraTargetTracking(Spring_00143208* self, void* target, f32 dt, Record_00143208* rec)
{
    Vec4 offset;

    ComputeOffsetBehindTarget(self, target, (Target_00143148*)rec, &offset);
    if (target == g_player) {
        switch (g_player->cameraSpringMode) {
        case 0:
            SpringCameraVector((Camera*)self, &self->v250, &self->v260, &offset, 5.0f, -3.5f, dt);
            SpringCameraVector((Camera*)self, &self->v270, &self->v280, (Vec4*)&g_zeroVector, 5.0f, -3.5f, dt);
            break;
        case 1:
            SpringCameraVector((Camera*)self, &self->v250, &self->v260, &offset, 1.0f, -10.0f, dt);
            SpringCameraVector((Camera*)self, &self->v270, &self->v280, &self->v270, 0.0f, -10.0f, dt);
            break;
        case 2:
            SpringCameraVector((Camera*)self, &self->v250, &self->v260, &offset, 5.0f, -3.5f, dt);
            break;
        }
    } else {
        SpringCameraVector((Camera*)self, &self->v250, &self->v260, &offset, 5.0f, -3.5f, dt);
        SpringCameraVector((Camera*)self, &self->v270, &self->v280, (Vec4*)&g_zeroVector, 5.0f, -3.5f, dt);
    }
    Vu0::Q(rec->v40) = Vu0::Add(Vu0::Q(rec->v10), Vu0::Q(self->v250));
}

// What func_001433E0 resets: the offset ComputeOffsetBehindTarget gives (+0x250) and three
// vectors after it.
struct Tracking_001433E0 {
    u8 pad0[0x250];
    Quad16 offset;          // 0x250
    Quad16 v260;            // 0x260
    Quad16 v270;            // 0x270
    Quad16 v280;            // 0x280
};

// Starts the target camera over: the offset behind the target is recomputed and the three tracking
// vectors at 0x260, 0x270 and 0x280 are zeroed.
void ResetCameraTargetTracking(Tracking_001433E0* self, void* a1, Target_00143148* a2)
{
    ComputeOffsetBehindTarget(self, a1, a2, &self->offset);
    Vu0::Q(self->v260) = Vu0::Zero();
    Vu0::Q(self->v270) = Vu0::Zero();
    Vu0::Q(self->v280) = Vu0::Zero();
}

// The 0x50-byte record of the target in action (Camera +0x2F0): the target's slot 73 fills it.
struct TargetRecord_00143418 {
    u8 pad0[0x10];
    Vec4 v10;              // 0x10
    u8 pad20[0x40 - 0x20];
    Vec4 v40;              // 0x40
};

// Slot 73 (0x124) of the target's method table: CaptureColliderPose and its overrides take the
// record and the frame's time step.
typedef void (*VFn_143418)(void* self, TargetRecord_00143418* out, f32 dt);

// dt is the caller's $f12 (func_001E2E68 passes 0.0f), passed on to the target's slot 73 as
// the other callers of that slot do; the time step's register is never mentioned because it
// is still in $f12 at the call.
void GetCameraTargetPlacement(Camera* self, void* o, TargetRecord_00143418* out, f32 dt)
{
    Vec4 offset;
    if (o == self->currentTarget) {
        *out = *(TargetRecord_00143418*)&self->f2F0;
    } else {
        ((VFn_143418)(*(void***)o)[0x124 / 4])(o, out, dt);
        ComputeOffsetBehindTarget(self, o, (Target_00143148*)out, &offset);
        Vu0::Q(out->v40) = Vu0::Add(Vu0::Q(out->v10), Vu0::Q(offset));
    }
}

// Computes the four fog terms into out for a fog strength factor p, fitting a reciprocal through
// the near and far fog distances; the values are biased for the GS's float-to-integer trick
// (8388608.0 and 36864.0).
void ComputeCameraFogTerms(Camera* self, f32* out, f32 p)
{
    f32 one = 1.0f;
    f32 scale = 4080.0f;
    f32 a = self->fogStrength * p;
    f32 b = self->fogFar;
    f32 c = self->fogNear;
    FitReciprocalThroughPoints(out, out + 1, one, scale, b / c, (one - a) * scale);
    out[0] = out[0] + 8388608.0f;
    out[2] = self->fogNear;
    out[3] = out[0] + 36864.0f;
}

void BuildProjectionMatrix(Mat4* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
extern "C" f32 Tangent(f32 x);

// Recomputes the camera's projection from its zoom (the field of view): the tangent of half of it
// and of its horizontal extent by the aspect, the distance scale (at least 1), the projection
// matrix for the 640x224 screen with the near and far distances, and the fog terms, then the camera
// matrices.
void UpdateCameraProjection(Camera* self)
{
    f32 one = 1.0f;
    f32 t = Tangent(self->zoom * 0.5f);
    f32 inv = one / self->zoom;
    f32 w = self->aspectScale;
    self->projectionScaleY = t;
    self->projectionScaleX = t * w;
    f32 d = w * w + one;
    self->rangeScale = (one >? self->distanceScale * inv);
    f32 q = t * Fpu::Sqrt(d);
    self->nearClearance = q * self->nearDistance + one;
    BuildProjectionMatrix(&self->projection, 640.0f / (t * w * 4096.0f), 224.0f / (t * 4096.0f), 0.0f, 0.0f, self->nearDistance, self->farDistance);
    ComputeCameraFogTerms(self, self->fogTerms, one);
    UpdateCameraMatrices(self);
}

// Initialises the camera object: the scale and ramp defaults, the near-clip and fog defaults (a
// field of view ratio of about 1.3, near 100, far 20000), the identity orientation, the projection,
// and the five controllers it owns (the base one, the target, frame, value and on/off controllers)
// with their method tables and owner; ends with ResetCamera.
void InitCamera(Camera* self)
{
    InitObject(self);
    f32 one = 1.0f;
    self->distanceScale = one;
    self->zoom = one;
    self->zoomGoal = one;
    *(struct ParamBlock16*)&self->zoomProfile = *(struct ParamBlock16*)g_cameraDefaultRamp;
    f32 k = 1.29870129f;
    f32 x = g_cameraDefaultFogNear;
    f32 y = g_cameraDefaultFogFar;
    f32 z = g_cameraDefaultFogStrength;
    f32 h = 100.0f;
    f32 t = 20000.0f;
    self->aspectScale = k;
    self->nearDistance = h;
    self->farDistance = t;
    self->fogNear = x;
    self->fogFar = y;
    self->fogStrength = z;
    *(struct FogColorWord*)&self->fogColor = *(struct FogColorWord*)&g_cameraDefaultFogColor;
    *(struct FrameRow*)&self->rot80.r[0] = *(struct FrameRow*)g_identityMatrix;
    *(struct FrameRow*)&self->rot80.r[1] = *(struct FrameRow*)(g_identityMatrix + 0x10);
    *(struct FrameRow*)&self->rot80.r[2] = *(struct FrameRow*)(g_identityMatrix + 0x20);
    UpdateCameraProjection(self);
    self->ctl454.vt = (const CameraControllerVt*)g_cameraControllerMethods;
    SetCameraControllerOwner(&self->ctl454, self);
    self->ctl460.vt = (const CameraControllerVt*)g_targetCameraControllerMethods;
    InitTargetCameraController(&self->ctl460, self);
    self->ctl4C0.vt = (const CameraControllerVt*)g_frameCameraControllerMethods;
    InitFrameCameraController(&self->ctl4C0, self);
    self->ctl510.vt = (const CameraControllerVt*)g_valueCameraControllerMethods;
    SetCameraControllerOwner(&self->ctl510, self);
    self->ctl520.vt = (const CameraControllerVt*)g_onOffCameraControllerMethods;
    SetCameraControllerOwner(&self->ctl520, self);
    ResetCamera(self, 1);
}

// SnapCameraZoom on the current camera.
void SnapCurrentCameraZoom(void* unused0, f32 zoom)
{
    SnapCameraZoom(g_camera, zoom);
}

// SetCameraNearDistance on the current camera.
void SetCurrentCameraNearDistance(void* unused0, f32 distance)
{
    SetCameraNearDistance(g_camera, distance);
}

// SetCameraFarDistance on the current camera.
void SetCurrentCameraFarDistance(void* unused0, f32 distance)
{
    SetCameraFarDistance(g_camera, distance);
}

// SetCameraFogNear on the current camera.
void SetCurrentCameraFogNear(void* unused0, f32 distance) { SetCameraFogNear(g_camera, distance); }

// SetCameraFogFar on the current camera.
void SetCurrentCameraFogFar(void* unused0, f32 distance) { SetCameraFogFar(g_camera, distance); }

// SetCameraFogStrength on the current camera.
void SetCurrentCameraFogStrength(void* unused0, f32 strength) { SetCameraFogStrength(g_camera, strength); }

// SetCameraFogColor on the current camera.
void SetCurrentCameraFogColor(void* unused0, void* color) { SetCameraFogColor(g_camera, color); }

// SetCameraDistanceScale on the current camera.
void SetCurrentCameraDistanceScale(void* unused0, f32 scale)
{
    SetCameraDistanceScale(g_camera, scale);
}

// Sets only the camera's position (see SetCameraPlacement).
void SetCameraPosition(void* self, void* value)
{
    SetCameraPlacement((Camera*)self, (Quad16*)value, 0);
}

// Sets only the camera's orientation (see SetCameraPlacement).
void SetCameraOrientation(void* arg, void* arg2) { SetCameraPlacement((Camera*)arg, 0, (Quad16*)arg2); }

// Sets the zoom and its goal to x, so there is no easing, and updates the projection.
void SnapCameraZoom(void* self, f32 x)
{
    Camera* c = (Camera*)self;
    c->zoom = x;
    c->zoomGoal = x;
    c->i1CC = 0;
    UpdateCameraProjection((Camera*)self);
}

// Sets the near plane distance and updates the projection.
void SetCameraNearDistance(void* self, f32 x)
{
    Camera* c = (Camera*)self;
    c->nearDistance = x;
    UpdateCameraProjection((Camera*)self);
}

// Sets the far plane distance and updates the projection.
void SetCameraFarDistance(Camera* self, f32 value)
{
    self->farDistance = value;
    UpdateCameraProjection(self);
}

// Sets the distance where the fog starts and updates the projection.
void SetCameraFogNear(Camera* self, f32 value)
{
    self->fogNear = value;
    UpdateCameraProjection(self);
}

// Sets the distance where the fog is full and updates the projection.
void SetCameraFogFar(Camera* self, f32 value)
{
    self->fogFar = value;
    UpdateCameraProjection(self);
}

// Sets the fog's strength and updates the projection.
void SetCameraFogStrength(void* ptr, f32 value)
{
    Camera* self = (Camera*)ptr;
    self->fogStrength = value;
    UpdateCameraProjection(self);
}

// Sets the camera's fog colour and updates the projection.
void SetCameraFogColor(void* self, void* value)
{
    *(Value_00143A08*)&((Camera*)self)->fogColor = *(Value_00143A08*)value;
    UpdateCameraProjection((Camera*)self);
}

// Sets the distance scale and updates the projection of the current camera.
void SetCameraDistanceScale(Camera* self, f32 value)
{
    self->distanceScale = value;
    UpdateCameraProjection(g_camera);
}

// Resets the camera: with flag set, puts it at its reset position looking at the reset target;
// empties the controller stack, pushes the base controller, requests a snap and restores the
// default value mask (0x0FFFFFFF) and swing start time (-10).
void ResetCamera(Camera* self, s32 flag)
{
    if (flag != 0) {
        PlaceCameraLookingAt(self, (const Vec4*)g_cameraResetPosition, (const Vec4*)g_cameraResetTarget);
    }
    self->stackCount = 0;
    SetCameraControllerValue(&self->ctl454, 0);
    PushCameraController(self, 0, &self->ctl454, 0, 0);
    RequestCameraSnap(self, 0);
    self->areaMask = 0x0FFFFFFF;
    self->swingStartTime = -10.0f;
}

// Empties the camera's object list.
void ClearCameraObjectList(Camera* obj)
{
    obj->objectCount = 0;
}

// Appends an object to the camera's list (8 at most).
void AddCameraObject(Camera* list, void* item)
{
    u32 n = list->objectCount;
    if (n < 8) {
        list->objects[n] = item;
        list->objectCount = n + 1;
    }
}

// Takes item out of the camera's object list (closing the gap) when it is there.
void RemoveCameraObject(Camera* list, void* item)
{
    for (s32 i = 0; i < list->objectCount; i++) {
        if (item == list->objects[i]) {
            CopyMemory(&list->objects[i], &list->objects[i + 1], (list->objectCount - i - 1) * 4);
            list->objectCount--;
            return;
        }
    }
}

// Collider filter for the camera: a collider is an obstacle when its flag field matches 0x8000 at
// bit 20 of the flags or it has node groups.
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

// A part's state as func_00143BE0 writes it (0x28 bytes, PlacedObject::partStates): the time
// until which the part is faded.
struct PartFade {
    u8 pad00[0x14];
    f32 until;              // 0x14
    u8 pad18[0x28 - 0x18];
};

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

// Marks the parts of colliders that lie between the camera and the camera's objects (those with
// flag bit 37) as faded for the next 0.1 s: it gathers the colliders in the box of those points
// that IsCameraObstacle accepts and, for each span a segment from the camera to an object crosses,
// sets the fade-until time of the span's part group.
void FadeCameraObstructingParts(Camera* self)
{
    Vec4 lo;
    Vec4 hi;
    ColliderSpan spans[0x20];
    s32 n;
    Collider** list;
    PushBackMemoryMark();
    lo = hi = *(Vec4*)self->position;
    for (s32 i = 0; i < self->objectCount; i++) {
        PlacedObject* obj = (PlacedObject*)self->objects[i];
        if (obj->flags & (1ULL << 37)) {
            Vu0::Q(lo) = Vu0::Min(Vu0::Q(lo), Vu0::Q(obj->v140));
            Vu0::Q(hi) = Vu0::Max(Vu0::Q(hi), Vu0::Q(obj->v140));
        }
    }
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, IsCameraObstacle, 0, &n, &list);
    for (s32 j = 0; j < n; j++) {
        Collider* c = list[j];
        for (s32 k = 0; k < self->objectCount; k++) {
            PlacedObject* obj = (PlacedObject*)self->objects[k];
            if (!(obj->flags & (1ULL << 37))) {
                continue;
            }
            s32 m = CollectTreeNodeSpans(c->tree.nodes, (Vec4*)self->position, &obj->v140, c->nodeGroups, 0x20, spans);
            ColliderSpan* end = &spans[m];
            for (ColliderSpan* sp = spans; sp < end; sp++) {
                if (sp->group < 0) {
                    continue;
                }
                for (s32 q = sp->group; q < c->groupCount; q++) {
                    CollisionRefPair* e = &c->groups[q];
                    if (e->a >= 0 && q != sp->group) {
                        break;
                    }
                    ((PartFade*)c->partStates)[e->b].until = g_gameClock.elapsed + 0.1f;
                }
            }
        }
    }
    PopBackMemoryMark();
}

// Per-frame camera update: turns a queued snap into the snapping state, runs the top controller of
// the stack (updating its target tracking once per target and calling its method 4 with the target
// record, the pad or a blank one, and dt; again if the top changes), then moves the zoom toward its
// goal or snaps it. A set flag ends the snap.
void UpdateCamera(Camera* self, s32 flag, f32 dt)
{
    if (self->snapQueued != 0) {
        self->snapQueued = 0;
        self->snapping = 1;
        self->hasSnapValue = 0;
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
                    x = (u8*)&self->f2F0;
                    if (o != last) {
                        ((VFn_143E40)(*(void***)o)[0x124 / 4])(o, dt, x);
                        if (prev != 0 || o != self->currentTarget) {
                            ResetCameraTargetTracking((Tracking_001433E0*)self, o, (Target_00143148*)x);
                        }
                        UpdateCameraTargetTracking((Spring_00143208*)self, o, dt, (Record_00143208*)x);
                        self->currentTarget = o;
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
    if (self->snapping != 0) {
        SnapCameraZoom(self, self->zoomGoal);
    } else if (self->zoom != self->zoomGoal) {
        self->zoom = ApproachValueClampingVelocity(self->zoom, self->zoomSpeed, self->zoomGoal, dt, &self->zoomProfile, &self->zoomSpeed);
        UpdateCameraProjection(self);
    }
    if (flag != 0) {
        self->hasSnapValue = 0;
        self->snapping = 0;
    }
}

ASM_FUNC(func_00144008);

// The camera's frame as func_00144128 reads it: rows at 0x80, a position at 0x40, two scales.
struct Frame_00144128 {
    u8 pad0[0x40];
    Vec4 pos;              // 0x40
    u8 pad50[0x80 - 0x50];
    Mat3 rot;              // 0x80
    u8 padB0[0x1F0 - 0xB0];
    f32 scaleY;             // 0x1F0
    f32 scaleZ;             // 0x1F4
};

// The inverse of ProjectPointToCamera: from a[0], a[1] and depth a[2] makes the world point.
void UnprojectCameraPoint(Camera* camera, f32* a, Vec4* out)
{
    Frame_00144128* self = (Frame_00144128*)camera;
    Vec4 v;
    v.x = a[2];
    v.y = -a[0];
    v.z = a[1];
    if (1e-4f < a[2]) {
        v.y = -a[0] * a[2];
        v.z = a[1] * a[2];
    }
    v.y = v.y * self->scaleY;
    v.z = v.z * self->scaleZ;
    Vu0::Q(*out) = Vu0::Add(Vu0::Rotate(self->rot, Vu0::Q(v)), Vu0::Q(self->pos));
}

// Projects a world point into the camera's frame: out[2] is the depth along the camera's x axis,
// out[0] and out[1] the sideways and up offsets scaled by the camera's y and z scale and, for a
// point in front of the camera (depth above 1e-4), divided by the depth.
void ProjectPointToCamera(Camera* camera, Vec4* in, f32* out)
{
    Frame_00144128* self = (Frame_00144128*)camera;
    Vec4 v;
    Vu0::Q(v) = Vu0::RotateTransposed(self->rot, Vu0::Sub(Vu0::Q(*in), Vu0::Q(self->pos)));
    out[2] = v.x;
    out[1] = v.z;
    out[0] = -v.y;
    out[0] /= self->scaleY;
    out[1] /= self->scaleZ;
    if (1e-4f < v.x) {
        out[0] /= v.x;
        out[1] /= v.x;
    }
}

// Rebuilds the camera's ground frame and, when the world has a value tree, looks up the leaf at the
// camera's position and keeps its value (when non-zero) in f21C.
void UpdateCameraLocation(Camera* self)
{
    Quad16 in;
    s32 out;
    World* g;

    BuildCameraGroundFrame(self);
    g = g_currentWorld;
    if (g != 0) {
        in = *(Quad16*)self->position;
        LookupValueTreeLeaf((void*)g->valueListObject, &in, &out);
        if (out != 0) {
            self->areaMask = out;
        }
    }
}

// Builds the view matrix from the camera position b and the rows of its orientation a (as a matrix
// whose columns are the negated second and third rows, and the first row), inverts it and
// multiplies it with the projection matrix c, storing the four rows of the result in out.
void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out)
{
    Mat4 m;
    Mat4 v;
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
    Mat4A r = MultiplyMatrices(*(Mat4A*)c, *(Mat4A*)&v);
    out[0] = ((Quad16*)&r)[0];
    out[1] = ((Quad16*)&r)[1];
    out[2] = ((Quad16*)&r)[2];
    out[3] = ((Quad16*)&r)[3];
}

// v made unit length: DivX by its Length.
static inline u128 Unit(u128 v)
{
    return Vu0::DivX(v, Vu0::Length(v));
}

// Builds the normals of the four side planes of a view frustum from the orientation matrix m (its
// rows being the view axes) and the half-extents x and y (as tangents): two for the sides of the
// horizontal range and two for the vertical one, each the cross product of a view axis with the
// unit edge direction.
void BuildFrustumSideNormals(Mat3* m, Vec4* out, f32 x, f32 y)
{
    f32 nx = -x;
    f32 ny = -y;
    Vu0::Q(out[0]) = Vu0::Cross(Vu0::Q(m->r[2]), Unit(Vu0::MulAddX(Vu0::Q(m->r[0]), Vu0::Q(m->r[1]), Vu0::Scalar(x))));
    Vu0::Q(out[1]) = Vu0::Cross(Unit(Vu0::MulAddX(Vu0::Q(m->r[0]), Vu0::Q(m->r[1]), Vu0::Scalar(nx))), Vu0::Q(m->r[2]));
    Vu0::Q(out[2]) = Vu0::Cross(Unit(Vu0::MulAddX(Vu0::Q(m->r[0]), Vu0::Q(m->r[2]), Vu0::Scalar(y))), Vu0::Q(m->r[1]));
    Vu0::Q(out[3]) = Vu0::Cross(Vu0::Q(m->r[1]), Unit(Vu0::MulAddX(Vu0::Q(m->r[0]), Vu0::Q(m->r[2]), Vu0::Scalar(ny))));
}

extern const f32 g_unitScale[4];
extern "C" f32 Sine(f32 x);
void BuildRotationFromVector(Vec4* v, Mat3* mat);

// For D_002618C8 seconds after self->f218 the view swings by a sine of the time since then,
// scaled by a curve of that time. The weight is written at each use: each
// Vu0::Scalar(swing) stores its slot again, and the repeat (dir's before the call, tilt's
// after the product) is what holds the first store ahead of the other stores and leaves no
// code (docs/toolchain/sched1.md, "A weight written again in the next statement"). corner
// comes after the product, so the product's rows are read before corner's store.
void UpdateCameraMatrices(Camera* self)
{
    Vec4 pos;
    Vec4 dir;
    Mat3 rotation;
    f32 f6 = g_gameTime - self->swingStartTime;
    if (g_cameraSwingDuration < f6) {
        BuildViewProjectionMatrix((f32*)self->position, (f32*)self->rotation, &self->projection, (Quad16*)&self->viewProjection);
    } else {
        f32 t = f6 / g_cameraSwingDuration;
        f32 amount = g_unitRange.Limit(g_cameraSwingFalloffCurve[0] + t * (g_cameraSwingFalloffCurve[1] + t * g_cameraSwingFalloffCurve[2]));
        f32 swing = Sine(f6 * g_cameraSwingRate) * amount;
        u128 turn = Vu0::Rotate(*(Mat3*)self->rotation, Vu0::Q(*(Vec4*)g_cameraSwingOffset));
        Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(*(Vec4*)self->position), turn, Vu0::Scalar(swing));
        Vu0::Q(dir) = Vu0::MulX(Vu0::Q(*(Vec4*)g_cameraSwingTurn), Vu0::Scalar(swing));
        BuildRotationFromVector(&dir, (Mat3*)&rotation);
        MulRotationRowsX(&rotation, *(Mat3*)self->rotation, rotation);
        Vec4 corner;
        Vec4 tilt;
        Mat4 proj;
        Vu0::Q(corner) = Vu0::MulAddX(Vu0::Q(*(Vec4*)g_unitScale), Vu0::Q(*(Vec4*)g_cameraSwingCornerShift), Vu0::Scalar(swing));
        Vu0::Q(tilt) = Vu0::MulX(Vu0::Q(*(Vec4*)g_cameraSwingTiltShift), Vu0::Scalar(swing));
        BuildProjectionMatrix(&proj, corner.x * 640.0f / (self->projectionScaleX * 4096.0f), corner.y * 224.0f / (self->projectionScaleY * 4096.0f), tilt.x, tilt.y, self->nearDistance, self->farDistance);
        BuildViewProjectionMatrix((f32*)&pos, (f32*)&rotation, &proj, (Quad16*)&self->viewProjection);
    }
    InvertMatrix4x4((u8*)&self->viewProjection, (u8*)&self->inverseViewProjection);
    BuildFrustumSideNormals((Mat3*)self->rotation, self->frustum, self->projectionScaleX, self->projectionScaleY);
    {
        f32* e = (f32*)&self->frustum[3];
        f32* d = self->planes[0];
        f32* c = (f32*)&self->frustum[2];
        f32* b = (f32*)&self->frustum[1];
        f32* a = (f32*)&self->frustum[0];
        s32 n = 2;
        do {
            d[0] = *a++;
            d[1] = *b++;
            d[2] = *c++;
            d[3] = *e++;
            d += 4;
        } while (--n >= 0);
    }
}

// Writes a DMA packet that loads the camera's two matrices (at 0x100 and 0x140) into VU memory with
// base offset 0.
void WriteCameraMatricesPacket(Camera* self)
{
    BeginDmaTag((PacketWriter*)g_vifPacketWriter);
    WriteVifBaseOffset((PacketWriter*)g_vifPacketWriter, 0, 0);
    CopyWordsToWriter((PacketWriter*)g_vifPacketWriter, 0xC, 4, (u32*)&self->viewProjection, 4);
    CopyWordsToWriter((PacketWriter*)g_vifPacketWriter, 0xC, 4, (u32*)&self->inverseViewProjection, 8);
    CloseDmaTag((PacketWriter*)g_vifPacketWriter);
}

// Sets the camera's position and/or its three orientation vectors (either may be 0 to keep it),
// updates its matrices and clears the look-frame offsets.
void SetCameraPlacement(Camera* self, Quad16* a, Quad16* b)
{
    if (a != 0) {
        *(Quad16*)self->position = *a;
    }
    if (b != 0) {
        *(Quad16*)self->rotation = b[0];
        *(Quad16*)self->rotationRow1 = b[1];
        *(Quad16*)self->rotationRow2 = b[2];
    }
    UpdateCameraMatrices(self);
    f32 zero = 0.0f;
    self->tiltRate = zero;
    self->yawRate = zero;
    self->pitchRate = zero;
    self->headingRate = zero;
    self->distanceRate = zero;
}

// Places the camera at target looking at focus, through the orbit camera placement.
void PlaceCameraLookingAt(Camera* self, const Vec4* target, const Vec4* focus)
{
    UpdateOrbitCameraPlacement(self, 0, target, focus, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

// Gives the coordinates of the point in, in a frame that looks from a to b: z is the distance along
// the look direction and x and y the sideways and up offsets divided by the look distance (at least
// 100). All three are 0 when a and b are almost the same point.
void ComputeLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* in, f32* x, f32* y, f32* z)
{
    Mat3 m;
    Vec4 d;
    Vec4 v;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    BuildBasisFromX(&d, &m);
    f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
    if (len < 1e-4f) {
        *z = *x = *y = 0.0f;
    } else {
        Vu0::Q(v) = Vu0::RotateTransposed(m, Vu0::Q(*in));
        if (len < 100.0f) {
            len = 100.0f;
        }
        *z = v.x;
        *x = v.y / len;
        *y = v.z / len;
    }
}

// Turns look-frame coordinates (x, y, z) into a point: the frame has its x axis from a to b and a
// basis built from it; the point is (z, len*x, len*y) in that frame, with len the distance a to b,
// rotated into world space into *out. The inverse of ComputeLookFrameCoordinates.
void ApplyLookFrameCoordinates(Quad16* a, Quad16* b, Quad16* out, f32 x, f32 y, f32 z)
{
    Mat3 m;
    Vec4 d;
    Vec4 v;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    BuildBasisFromX(&d, &m);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    Vu0::Q(v) = Vu0::FromFloats(z, len * x, len * y);
    Vu0::Q(*out) = Vu0::RotateUntied(m, Vu0::Q(v));
}

// Moves the camera's look anchor to arg without moving the view: the look-frame coordinates
// (f2B0-f2B8) are recomputed against the new anchor.
void SetCameraLookAnchor(Camera* self, Quad16* arg)
{
    Quad16 tmp;
    ApplyLookFrameCoordinates((Quad16*)self->lookFocus, (Quad16*)self->position, &tmp, self->headingRate, self->pitchRate, self->distanceRate);
    ComputeLookFrameCoordinates(arg, (Quad16*)self->position, &tmp, &self->headingRate, &self->pitchRate, &self->distanceRate);
    *(Quad16*)self->lookFocus = *arg;
}

void ConvertOffsetToSpherical(const Vec4* a, const Vec4* b, f32* heading, f32* pitch, f32* dist);
void VectorToAngles(Vec3* v, f32* a1, f32* a2);
void BuildYawPitchMatrix(f32 yaw, f32 pitch, Mat3* out);

// Places the camera on an orbit around focus, looking at target, from the spherical coordinates of
// the offset plus yaw and pitch offsets scaled by the zoom. Unless snapping, the five current
// values move toward their goals as damped springs (gain, damp, dt), going the short way round,
// then the position, rotation rows and matrices are written and focus is kept.
void UpdateOrbitCameraPlacement(Camera* self, s32 flags, const Vec4* target, const Vec4* focus, s32 e, f32 gain, f32 damp,
                   f32 unused, f32 yawOffset, f32 pitchOffset, f32 dt)
{
    Vec4 dir;
    Vec4 pos;
    Mat3 m;
    f32 heading;
    f32 pitch;
    f32 dist;
    f32 curHeading;
    f32 curPitch;
    f32 curDist;
    f32 curYaw;
    f32 curTilt;
    f32 h;
    f32 p;
    f32 r;
    f32 y;
    f32 t;
    if (self->snapping != 0) {
        flags &= ~1;
    }
    ConvertOffsetToSpherical(target, focus, &heading, &pitch, &dist);
    f32 yaw = heading + 3.14159274f + yawOffset * self->zoom * self->aspectScale * 0.5f;
    f32 tilt = -pitch - pitchOffset * self->zoom * 0.5f;
    ConvertOffsetToSpherical((Vec4*)self->position, (Vec4*)self->lookFocus, &curHeading, &curPitch, &curDist);
    VectorToAngles((Vec3*)self->rotation, &curYaw, &curTilt);
    if ((flags & 1) == 0) {
        y = yaw;
        t = tilt;
        h = heading;
        p = pitch;
        r = dist;
    } else {
        f32 dh = WrapAngle(heading - curHeading);
        f32 dp = pitch - curPitch;
        f32 dd = dist - curDist;
        f32 dy = WrapAngle(yaw - curYaw);
        f32 dt2 = tilt - curTilt;
        if (2.0f < __builtin_fabsf(dh) && 2.0f < __builtin_fabsf(dy) && dh * dy < 0.0f) {
            if (__builtin_fabsf(dy) < __builtin_fabsf(dh)) {
                if (dy < 0.0f) {
                    dy += 6.28318548f;
                } else {
                    dy -= 6.28318548f;
                }
            } else {
                if (dh < 0.0f) {
                    dh += 6.28318548f;
                } else {
                    dh -= 6.28318548f;
                }
            }
        }
        f32 s = 1.0f;
        f32 x = __builtin_fabsf(dh) * 0.666666687f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dp) * 1.33333337f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dd) * 0.00200000009f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dy) * 0.666666687f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dt2) * 1.33333337f;
        if (s < x) {
            s = x;
        }
        dh /= s;
        dp /= s;
        dd /= s;
        dy /= s;
        dt2 /= s;
        self->headingRate += (dh * gain + self->headingRate * damp) * dt;
        self->pitchRate += (dp * gain + self->pitchRate * damp) * dt;
        self->distanceRate += (dd * gain + self->distanceRate * damp) * dt;
        self->yawRate += (dy * gain + self->yawRate * damp) * dt;
        self->tiltRate += (dt2 * gain + self->tiltRate * damp) * dt;
        h = curHeading + self->headingRate * dt;
        p = curPitch + self->pitchRate * dt;
        r = curDist + self->distanceRate * dt;
        y = curYaw + self->yawRate * dt;
        t = curTilt + self->tiltRate * dt;
    }
    ComputeDirectionFromAngles((Vec3*)&dir, h, p, r);
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(*focus), Vu0::Q(dir));
    BuildYawPitchMatrix(y, t, &m);
    *(Vec4*)self->position = pos;
    *(Vec4*)self->rotation = m.r[0];
    *(Vec4*)self->rotationRow1 = m.r[1];
    *(Vec4*)self->rotationRow2 = m.r[2];
    UpdateCameraMatrices(self);
    *(Vec4*)self->lookFocus = *focus;
}

// Gives in *out the world heading the stick points to when the camera's view is taken into account:
// the stick's angle (stick 0 or 1 by mode; 0 for other modes) plus the camera's own heading,
// wrapped.
void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out)
{
    f32 t;
    f32 x;
    f32 y;
    switch (mode) {
    case 0:
        y = p->stickY;
        x = p->stickX;
        goto call;
    case 1:
        y = p->secondStickY;
        x = p->secondStickX;
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


// Moves the entries from the given one on up by one, to open a slot for a new entry.
// Its parameter copies give retail its (i * 16 + self) base shared by both pointers
// (as RemoveFromSmallList's helper in warp_menu.cpp).
struct MoveEntriesUp {
    static void Of(CameraControllerEntry* dst, CameraControllerEntry* src, s32 n)
    {
        MoveMemory(dst, src, n);
    }
};

// Inserts a controller into the stack, which is kept in descending key order, after the
// entries whose key is at least its own. It calls the new controller's slot 2; when the
// new one becomes the first, the displaced one's slot 1 and then its own slot 0.
void PushCameraController(Camera* self, s32 key, CameraController* ctl, void* target, void* arg)
{
    s32 i;
    for (i = 0; i < self->stackCount; i++) {
        if ((self->stack + i)->key < key) {
            break;
        }
    }
    MoveEntriesUp::Of(&self->stack[i + 1], &self->stack[i], (self->stackCount - i) * sizeof(CameraControllerEntry));
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
        self->controllerSwitchTime = g_gameTime;
        CameraControllerFn fn0 = ctl->vt->m00;
        if (fn0 != 0) {
            fn0(ctl, arg);
        }
    }
}

// Removes the entries of the camera's controller stack that match all of the selected fields (flags
// 1 key, 2 controller, 4 target, 8 argument), calling each one's method 3 and keeping the others in
// order. If the top entry was removed, it calls that controller's method 1 and, if any entry is
// left, records the switch time and calls the new top's method 0.
void RemoveCameraControllers(Camera* self, s32 flags, s32 k0, CameraController* k1, void* k2, void* k3)
{
    void* s5 = 0;
    CameraController* s4 = 0;
    s32 i = 0;
    CameraControllerEntry* w = self->stack;
    CameraControllerEntry* r = w;
    for (; i < self->stackCount; i++, r++) {
        if ((!(flags & 1) || k0 == r->key) && (!(flags & 2) || k1 == r->ctl) &&
            (!(flags & 4) || k2 == r->target) && (!(flags & 8) || k3 == r->arg)) {
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
            self->controllerSwitchTime = g_gameTime;
            CameraController* o = self->stack[0].ctl;
            CameraControllerFn fn2 = o->vt->m00;
            if (fn2 != 0) {
                fn2(o, self->stack[0].arg);
            }
        }
    }
}

ASM_FUNC(func_001453B0);

// Gives the offset a (minus b, when b is given) as an angle about the z axis (wrapped), the
// horizontal distance and the height; any of the three outputs may be 0 to skip it.
void ConvertOffsetToCylindrical(const Vec4* a, const Vec4* b, f32* angle, f32* dist, f32* height)
{
    Vec4 d;
    if (b != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(*b));
    } else {
        d = *a;
    }
    if (angle != 0) {
        *angle = WrapAngle(ArctangentOfRatio(d.y, d.x));
    }
    if (dist != 0) {
        u128 v = Vu0::Q(d);
        *(u32*)dist = Vu0::ToBits(Vu0::Sqrt(Vu0::DotXY(v, v)));
    }
    if (height != 0) {
        *height = d.z;
    }
}

// Turns the offset a - b (or a alone if b is null) into spherical coordinates: heading (the angle
// in the xy plane), pitch (the elevation) and distance; each output may be null.
void ConvertOffsetToSpherical(const Vec4* a, const Vec4* b, f32* heading, f32* pitch, f32* dist)
{
    Vec4 d;
    if (b != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(*b));
    } else {
        d = *a;
    }
    if (heading != 0) {
        *heading = WrapAngle(ArctangentOfRatio(d.y, d.x));
    }
    if (pitch != 0) {
        u128 v = Vu0::Q(d);
        *pitch = WrapAngle(ArctangentOfRatio(d.z, Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(v, v)))));
    }
    if (dist != 0) {
        *(u32*)dist = Vu0::ToBits(Vu0::Length(Vu0::Q(d)));
    }
}

// Asks the camera to jump to its goal at the next update instead of easing; with src, also keeps
// its value as the snap value.
void RequestCameraSnap(Camera* self, f32* src)
{
    self->snapping = 1;
    if (src != 0) {
        self->hasSnapValue = 1;
        self->snapValue = *src;
    }
}

// Sets the flag that queues a snap for later (snapQueued).
void QueueCameraSnap(Camera* self)
{
    self->snapQueued = 1;
}

// RequestCameraSnap without a value.
void RequestPlainCameraSnap(void* p)
{
    RequestCameraSnap((Camera*)p, 0);
}

extern const Vec4 g_zeroVector;

// The view ray through the screen point (x, y): from the camera 100 units along the direction
// (1, -x f1F0, y f1F4) in its frame, the point of it nearest p; v230 is that point less p.
void SetCameraAimOffsetFromScreenPoint(Camera* self, Vec4* p, f32 x, f32 y)
{
    Vec4 dir;
    Vec4 far;
    f32 t;
    f32 dist;
    self->v240 = g_zeroVector;
    dir.x = 1.0f;
    dir.y = -x * self->projectionScaleX;
    dir.z = y * self->projectionScaleY;
    Vu0::Q(far) = Vu0::MulAddX(Vu0::Q(self->position), Vu0::Rotate(self->rotation, Vu0::Q(dir)), Vu0::Scalar(100.0f));
    MeasurePointToLine(p, (Vec4*)self->position, &far, &t, &dist);
    Vu0::Q(far) = Vu0::MulXSum(Vu0::Q(self->position), Vu0::Scalar(1.0f - t), Vu0::Q(far), Vu0::Scalar(t));
    Vu0::Q(self->v230) = Vu0::Sub(Vu0::Q(far), Vu0::Q(*p));
}

extern "C" f32 Arctangent(f32 x);

// The orbit step: the camera moves to the focus a2, the spring at v230/v240 eases toward rest,
// and the heading and pitch of a1 plus the spring's offset, seen from a2, turn by the
// arctangents of the screen turn scaled by f1F0 and f1F4; the frame is rebuilt from them.
void AimCameraAtPointWithSpring(Camera* self, Vec4* a1, Vec4* a2, f32 turnYaw, f32 turnPitch)
{
    Vec4 tmp;
    f32 yaw;
    f32 pitch;
    f32 dist;

    *(Vec4*)self->position = *a2;
    SpringCameraVector(self, &self->v230, &self->v240, (Vec4*)&g_zeroVector, g_cameraAimSpringStiffness, g_cameraAimSpringDamping, g_gameClock.dt);
    Vu0::Q(tmp) = Vu0::Add(Vu0::Q(*a1), Vu0::Q(self->v230));
    ConvertOffsetToSpherical(&tmp, a2, &yaw, &pitch, &dist);
    yaw = yaw + Arctangent(turnYaw * self->projectionScaleX);
    pitch = pitch - Arctangent(turnPitch * self->projectionScaleY);
    BuildYawPitchMatrix(yaw, pitch, (Mat3*)self->rotation);
    UpdateCameraMatrices(self);
}
// Finds along the segment a2 to a3 the first stretch of at least thresh (as a fraction of the
// segment) that no collider's tree crosses: the spans of all the colliders (at most 64) are merged
// and the gaps between them, and from the start and to the end, are tested in order. Gives 1 and
// the fractions lo and hi of that stretch, or 0.
s32 FindFirstFreeSpan(s32 count, Collider** objs, void* a2, void* a3, f32 thresh, f32* lo, f32* hi)
{
    ColliderSpan recs[64];
    s32 total = 0;
    s32 i;
    s32 k;
    s32 j;
    f32 f2;
    f32 f1;
    for (i = 0; i < count; i++) {
        total += CollectTreeNodeSpans(objs[i]->tree2.nodes, (Vec4*)a2, (Vec4*)a3, 0, 0x40 - total, &recs[total]);
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


// Searches a sphere of radius r around origin for the nearest point the camera can take: samples
// directions on nine latitude rings (counts in g_freePointRingSamples), tests the line from origin
// to each with FindFirstFreeSpan and keeps the one with the smallest free fraction (plus a step);
// origin if none.
void FindNearestFreePointAround(s32 count, Collider** objs, Vec4* origin, Vec4* out, f32 r)
{
    Vec4 dir;
    Vec4 cand;
    Vec4 best;
    f32 lo;
    f32 hi;
    f32 step = 5.0f / r;
    f32 nearest = 3.4028234663852886e+38f;
    best = *origin;
    for (s32 i = 0; i < 9; i++) {
        f32 n = g_freePointRingSamples[i];
        f32 pitch = (f32)(i - 4) * 0.39269909f;
        for (s32 j = 0; (f32)j < n; j++) {
            ComputeDirectionFromAngles((Vec3*)&dir, (f32)j * 3.14159274f / n, pitch, r);
            Vu0::Q(cand) = Vu0::Add(Vu0::Q(*origin), Vu0::Q(dir));
            if (FindFirstFreeSpan(count, objs, origin, &cand, step + step, &lo, &hi) != 0) {
                if (0.0f < lo) {
                    lo = lo + step;
                }
                if (lo < nearest) {
                    nearest = lo;
                    Vu0::Q(best) = Vu0::MulXSum(Vu0::Q(*origin), Vu0::Scalar(1.0f - nearest), Vu0::Q(cand), Vu0::Scalar(nearest));
                }
            }
        }
    }
    *out = best;
}


typedef f32 (*MeshHitWeigh)(void* ctx, void* a, void* b, MeshHitSample* hit);
struct FaceRef;
struct CollisionMesh;
struct MeshHitEntry;
void* AllocateBackMemory(s32 size);

// Gives in out where origin must move to be clear of the meshes of the given colliders within r of
// a4: up to 64 hit points are gathered, the weights that fn asks for are solved with the active-set
// solver, and their weighted sum (limited to limit in length) is added to origin; origin itself if
// nothing is hit.
void ComputeConstrainedPushOut(void* ctx, s32 count, Collider** objs, MeshHitWeigh fn, f32 r, f32 limit, void* a4, Vec4* origin, Vec4* out)
{
    MeshHitSample hits[64];
    Vec4 sum;
    s32 total = 0;
    s32 i;
    s32 j;
    f32* p;
    for (s32 k = 0; k < count; k++) {
        Collider* c = objs[k];
        if (c->tree2.nodes != 0) {
            total += CollectMeshHits((Vec4*)a4, r, c->tree2.count2, (FaceRef*)c->tree2.nodes, 0, &c->mesh2Copy, 0x40 - total, (MeshHitEntry*)&hits[total]);
        }
    }
    if (total == 0) {
        *out = *origin;
        return;
    }
    PushBackMemoryMark();
    f32* dots = (f32*)AllocateBackMemory(total * total * 4);
    f32* rhs = (f32*)AllocateBackMemory(total * 4);
    f32* weights = (f32*)AllocateBackMemory(total * 4);
    p = dots;
    for (i = 0; i < total; i++) {
        for (j = 0; j < total; j++) {
            Vu0::StoreX(*p, Vu0::Dot(Vu0::Q(hits[i].normal), Vu0::Q(hits[j].normal)));
            p++;
        }
    }
    p = rhs;
    for (i = 0; i < total; i++) {
        *p++ = fn(ctx, a4, origin, &hits[i]);
    }
    SolveActiveSetSystem(total, (u8*)dots, rhs, weights);
    sum = g_zeroVector;
    p = weights;
    for (i = 0; i < total; i++) {
        Vu0::Q(sum) = Vu0::MulAddX(Vu0::Q(sum), Vu0::Q(hits[i].normal), Vu0::Scalar(*p++));
    }
    ClampVectorLength(&sum, &sum, limit);
    PopBackMemoryMark();
    Vu0::Q(*out) = Vu0::Add(Vu0::Q(*origin), Vu0::Q(sum));
}

// Collider filter: true when the collider has a second tree.
s32 HasColliderSecondTree(void* unused, Collider* other)
{
    return other->tree2.nodes != 0;
}

// The vectors func_00145DE8 reads: a direction at +0x10 and a distance at +0x20.
struct Heading_00145DE8 {
    u8 pad0[0x10];
    Quad16 dir;             // 0x10
    f32 dist;               // 0x20
};

extern f32 g_frameStep;

// How far the camera's probe along direction h->dir is clear of a hit at v: the dot of v with the
// direction minus the clearance, which follows a ramp toward the camera's probe distance less the
// probe radius.
f32 ComputeCameraHitClearance(Camera* self, void* unused, Quad16* v, Heading_00145DE8* h)
{
    f32 out;
    ApproachValueWithRamp(h->dist, self->nearClearance - g_cameraProbeRadius, g_frameStep, &g_cameraClearanceRamp, &out);
    return Vu0::ToFloat(Vu0::Dot(Vu0::Q(*v), Vu0::Q(h->dir))) - out;
}

// The camera's sweep probe: the step's direction from origin to dest, the colliders in a box
// of 250 around the origin, and the weighed hit, scaled by the step, from the origin into out.
void PushCameraOutOfGeometry(Camera* self, Quad16* origin, Quad16* dest, Vec4* out)
{
    Vec4 dir;
    Vec4 hit;
    Vec4 lo;
    Vec4 hi;
    s32 n;
    Collider** list;
    GameClock* clock = &g_gameClock;
    Vu0::Set(dir, Vu0::DivX(Vu0::Sub(Vu0::Q(*dest), Vu0::Q(*origin)), Vu0::ScalarAt(clock->step)));
    Vu0::Set(lo, Vu0::Add(Vu0::Q(*origin), Vu0::Q(g_cameraProbeBoxMin)));
    Vu0::Set(hi, Vu0::Add(Vu0::Q(*origin), Vu0::Q(g_cameraProbeBoxMax)));
    PushBackMemoryMark();
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, HasColliderSecondTree, 0, &n, &list);
    ComputeConstrainedPushOut(self, n, list, (MeshHitWeigh)ComputeCameraHitClearance, g_cameraProbeRadius, Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(dir))) + g_cameraProbeLimitMargin[0], origin, &dir, &hit);
    Vu0::Q(*out) = Vu0::MulAddX(Vu0::Q(*origin), Vu0::Q(hit), Vu0::ScalarAt(clock->step));
    PopBackMemoryMark();
}

// Pushes a value on the target controller's value stack.
void PushCameraStackValue(Camera* self, s32 value)
{
    PushStackValue(&self->ctl460, value);
}

// Pops the target controller's value stack.
s32 PopCameraStackValue(Camera* self)
{
    return PopStackValue(&self->ctl460);
}

// Reads the top of the target controller's value stack without popping.
s32 PeekCameraStackValue(Camera* self)
{
    return PeekStackValue(&self->ctl460);
}

// Sets the target controller's three settings: the value at 0x50, the one at 0x54 and the size
// override.
void SetCameraControllerSettings(Camera* obj, s32 value, f32 first, f32 second) { obj->ctl460.f50 = value; obj->ctl460.distanceFactor = first; obj->ctl460.sizeOverride = second; }

// Stores the current game time as the camera's swing start time.
void RecordCameraTimestamp(Camera* obj) { obj->swingStartTime = g_gameTime; }

s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);

// True when the sphere (centre p, given radius) is inside all of the camera's side planes and its
// distance fade (ComputeCameraDistanceFade) is non-zero.
s32 IsSphereInCameraView(Camera* self, Vec4* p, f32 radius, f32 x)
{
    Vec4 r;
    f32 fade;
    s32 in = 0;
    u128 d = Vu0::Sub(Vu0::Q(*p), Vu0::Q(self->position));
    u128 ones = Vu0::Ones();
    Vu0::Q(r) = Vu0::FromFloat(radius);
    if ((Vu0::PlaneSigns(Vu0::Q(self->planes[0]), Vu0::Q(self->planes[1]), Vu0::Q(self->planes[2]), d, ones, Vu0::Q(r)) ^ 0xF0) == 0) {
        in = ComputeCameraDistanceFade(self, d, &fade, radius, x) != 0;
    }
    return in;
}


