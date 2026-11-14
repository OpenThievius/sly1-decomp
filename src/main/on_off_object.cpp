// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1E2420 to 0x1E5378 (its .rodata from 0x24E5F0, its .data from 0x275970): the
// on-off object and its camera controller, the mesh tables and face tree test, and the world load
// request with its static initialiser (func_001E5358, retail's constructor list). Its .data
// provably starts at 0x275970: the word before it, g_movieDecodeThread (D_00275964), ends at
// 0x275968, where D_00275970 (a float, aligned to 4) would follow in one file; retail has 8 bytes
// of zeros and puts it on 16, the linker's padding before a new file's .data. Its start in the
// code is a choice, any function start from 0x1E1DB8 to 0x1E2420 (text_format.cpp says why); the
// cut is at 0x1E2420, the first on-off object function. It holds several families; its name is
// ours, after the largest, the on-off object and its camera controller.
#include "common.h"
#include "asm_func.h"
#include "on_off_object.h"
#include "collider.h"
#include "world.h"
#include "camera_controller.h"
#include "camera.h"
#include "globals.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "load_progress.h"
#include "output_buffer.h"
#include "game_progress.h"
#include "flag_table.h"
#include "semaphore_params.h"
#include "thread_params.h"
#include "memory_card.h"
#include "screen_element.h"
#include "vu0.h"
#include "fpu.h"
#include "pad_record.h"
#include "ramp_profile.h"
#include "value_range.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/flagged_object.h"
#include "functions/game_clock.h"
#include "functions/game_progress.h"
#include "functions/matrix.h"
#include "functions/memory_card.h"
#include "functions/on_off_object.h"
#include "functions/oscillator.h"
#include "functions/pad_input.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/selection_menus.h"
#include "functions/sound_system.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world_contacts.h"
struct Mat02;
struct Vec02;





extern "C" void* FillMemory(void* p, s32 value, s32 size);




extern f32 g_gameTime;








void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);








extern f32 D_00275980[16];






void RemoveQueuedCalls(World* self, u32 mask, void* code, void* arg, s32 k2, s32 k3);









void ReadBufferedRotation3(BufferedStream* self, void* out);
void ReadBufferedVector3(BufferedStream* src, void* dst);
s32 ReadBufferedS8(BufferedStream* self);
void* CreatePathCurve(s32 idx);
void ReadPropertyRecords(void* a, void* b);




// What an on-off camera controller points to: while f438 is set, its f43C is the camera's f1C8.
struct CameraFovSource { u8 pad[0x438]; f32 zoomOverride; f32 savedZoom; };



extern "C" void* FillMemory(void* p, s32 value, s32 size);



extern f32 D_00275980[];
extern f32 D_00275A10[4];
extern f32 D_00275A20[2];






// A point as func_00128018 writes it and func_001E4DC0 tests it.
struct FacePoint {
    s32 v[4];
};


s32 IsPointInsideFaceTree(TreeNode03* self, FacePoint* value);




extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

extern f32 g_gameClock[];


struct SpanCandidate { u8 pad[0x20]; f32 value; };



extern "C" void* FillMemory(void* p, s32 value, s32 size);

// The eight scrambled words that locate a level's data on the disc: the key of the sector
// range is w[0] ^ w[5] and w[1] ^ w[7]; two blocks are the same level when w[2] ^ w[6] agree.
struct WorldKeyBlock { u32 w[8]; };

// The world load QueueWorldLoad (func_001E4E80) asks for and RunPendingWorldLoad
// (func_001E4EA8) carries out. Built at startup: its constructor is func_001E4E38; the
// compiler's initialiser and constructor for this file are func_001E5328 and func_001E5358
// (config/us/generated.tsv).
struct WorldLoadRequest {
    s32 state;              // 0x00: 1 while a load is queued
    WorldKeyBlock* key;     // 0x04: the level to load, or 0 to stay
    s32 f8;                 // 0x08: the ids FindOrActivateSwitchedCollider starts from
    s32 fC;                 // 0x0C
    s32 flags;              // 0x10: handed to SetCurrentLevelEntry; 0x10 shows D_0026C6C8
    WorldKeyBlock current;  // 0x14: the level loaded last
    WorldLoadRequest();
};














extern FlagTable g_flagTable;




struct SameWorldKey {
    static s32 Of(WorldKeyBlock* a, WorldKeyBlock* b)
    {
        if (a == b) return 1;
        if (b == 0) return 0;
        return ((a->w[2] ^ a->w[6]) ^ (b->w[2] ^ b->w[6])) == 0;
    }
};
struct OwnedStream : BufferedStream {
    void SetOwner(void* o) { owner = o; }
};

extern u8 g_packetBufferMemory[];
extern u8 g_scatterController[];
extern u8 D_002623D8[];

extern f32 g_frameStep;

void ClearKeyId(KeyId* q);
LoadProgress* InitLoadProgress(LoadProgress* q, U32P* a, U32P* b, U32P* c, U32P* d);
void* InitBufferedStream(BufferedStream* q, s32 a, u8* b, s32 c);
void BeginLoadProgress(LoadProgress* p);
s32 OpenBufferedSectorStreamRange(BufferedStream* q, KeyId* k);
void DestroyBufferedStream(BufferedStream* q, s32 n);
void ResetWorldSubsystems(World* q);
void ReadBufferedBlockHeader(s32 a, BufferedStream* q);
struct GameClock;
struct KeyedEntry;
World* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void CloseBufferedStream(BufferedStream* q);
void EndLoadProgress(LoadProgress* p);
struct Counter;
f32 D_00275970 = 0.5f;
f32 g_onOffCameraRetryDelay = 2.0f;
s32 D_00275978 = 0;
f32 D_00275980[16] = { -450.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 1.0f, 0, 0, 125.0f, 1.0f, 0, 0 };
f32 D_002759C0[20] = { -3.4028235e38f, 3.4028235e38f, -3.4028235e38f, 3.4028235e38f, -3.4028235e38f, 3.4028235e38f, 0, -0.1f,
                        1.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 0, 0 };
f32 D_00275A10[4] = { 0, 0.5f, 0, 0 };
f32 D_00275A20[2] = { 0, 3.4028235e38f };
f32 g_onOffCameraTurnLimit = 2.5f;
f32 g_onOffCameraAimGain = 2.5f;
f32 g_onOffCameraStepRate[4] = { 15.0f, 0.0f, 0.0f, 0.0f };
f32 g_onOffCameraTurnTiltCoefficients[4] = { 1.0f, -2.0f, -2.0f, 0.0f };
f32 g_onOffCameraTurnTiltLimits[2] = { 1.0f, 2.0f };
f32 D_00275A58[6] = { 0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f };
f32 g_onOffCameraTurnBlendCoefficients[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
RampProfile g_onOffCameraFadeRamp = { 4.0f, 0.0f, 0.25f, 0.0f };
RampProfile g_onOffCameraAngleRamp = { 2.5f, 0.0f, 0.35f, 15.0f };
Vec02 g_onOffCameraProbeOffsets[5] = { { 0, 0, 0, 0 }, { 0, -50.0f, 0, 0 }, { 0, 50.0f, 0, 0 }, { 0, 0, 75.0f, 0 }, { 0, 0, -50.0f, 0 } };

void* GetOnOffObjectBlock(void* self) { return self ? (u8*)self + 0x2F0 : (void*)D_00275980; }

struct CameraPlacement { Vec02 q[5]; };
// The orbit's polynomial block: three rows of four floats, cleared before the blend fills them.
struct OrbitPoly {
    f32 f[12];
    void Clear() { FillMemory(this, 0, (s32)sizeof(*this)); }
};

void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object)
{
    Block63* b = (Block63*)block;
    f32 t = b->f60;
    Vu0::Q(*out) = Vu0::MulXSum(Vu0::Q(eye->q[1]), Vu0::Scalar(1.0f - t), Vu0::Q(eye->q[4]), Vu0::Scalar(t));
    if (object != 0) {
        Vec02 x;
        OrbitPoly poly;
        Vec02 dir;
        poly.Clear();
        poly.f[1] = b->f70;
        poly.f[5] = b->f74;
        poly.f[9] = b->f78;
        s32 saved = object->f380;
        object->f380 = 0;
        PlaceOnOffCameraFrame(object, out, &x, &dir);
        PlaceOnOffCameraOrbit(object->angle3A0, 0.0f, object, (f32*)&x, poly.f, D_002759C0, 1, out);
        object->f380 = saved;
    }
}

void InitOnOffObject(OnOffObject* self)
{
    InitPlacedObject(self);
    self->block2F0 = *(Block63*)D_00275980;
    self->limitRampTime = 2.0f;
    self->limitSpeed = 1.0f;
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
    self->holdRampTime = 2.0f;
    self->holdSpeed = 1.0f;
    self->f430 = -1;
    self->quad450 = *(Quad63*)D_00275A10;
    {
        u8* src = (u8*)D_00275A20;
        self->pack460 = *(Pack63*)src;
    }
    self->forcedState = -1;
}

void UnregisterOnOffObject(OnOffObject* self)
{
    UnregisterPlacedObject(self);
    SetOnOffObjectState(self, 0);
    RemoveQueuedCalls(self->world, 2, 0, self, -1, 0);
}

void LoadOnOffObject(OnOffObject* self, void* a1)
{
    ReadBufferedRotation3((BufferedStream*)a1, &self->rot);
    ReadBufferedVector3((BufferedStream*)a1, &self->pos);
    const Desc01* vt = self->desc;
    if (vt->m12 != 0) {
        vt->m12(self);
    }
    ReadMeshTables(a1, &self->f2D4, self->f2D8, &self->f2DC, &self->faceTree);
    s32 idx = ReadBufferedS8((BufferedStream*)a1);
    if (idx != -1) {
        Arr63* o = (Arr63*)CreatePathCurve(idx);
        self->obj = o;
        void** curveTable = *(void***)o;
        if (curveTable[0] != 0) {
            ((void (*)(void*, void*))curveTable[0])(o, a1);
        }
        Arr63* p = self->obj;
        self->lastCurveValue = p->data[p->count - 1];
    } else {
        ReadBufferedRotation3((BufferedStream*)a1, &self->rot3B0);
        ReadBufferedVector3((BufferedStream*)a1, &self->v3E0);
        *(s32*)&self->lastCurveValue = 0;
    }
    self->i414 = (self->obj != 0) ? 7 : 5;
    ReadPropertyRecords(self, a1);
}

void StartOnOffObject(OnOffObject* self)
{
    StartPlacedObject(self);
}

void SetOnOffObjectState(void* selfv, s32 state)
{
    OnOffObject* self = (OnOffObject*)selfv;
    if (self->onOffState == state) return;
    if (state != 0) {
        if (state != 1) {
            self->onOffState = state;
            goto tail;
        }
        Camera* base = g_camera;
        PushCameraController(base, self->f388 + 2, &base->ctl520, self->switchedCollider, self);
        TriggerScriptEvent(self, 2, 0, 0);
    } else {
        Camera* base = g_camera;
        RemoveCameraControllers(base, 8, -1, 0, 0, self);
        TriggerScriptEvent(self, 3, 0, 0);
    }
    self->onOffState = state;
tail:
    self->stateChangeTime = g_gameTime;
}

void SetOnOffObjectForcedState(void* selfv, s32 value)
{
    OnOffObject* self = (OnOffObject*)selfv;
    if (value == self->forcedState) return;
    self->forcedState = value;
    UpdateOnOffObjectState(self, 0, 0);
}

void UpdateOnOffObjectState(OnOffObject* self, s32 unused1, s32 unused2) {
    FacePoint loc;
    void* p = GetActiveSwitchedCollider();
    if (p == 0) {
        return;
    }
    if (p != self->switchedCollider) {
        SetOnOffObjectState(self, 0);
        self->switchedCollider = p;
    }
    s32 st;
    if (self->forcedState == -1) {
        TransformPointBetweenFrames(0, self, (Vec02*)((u8*)p + 0x140), (Vec02*)&loc);
        s32 r = IsPointInsideFaceTree((TreeNode03*)self->faceTree, &loc);
        st = (0u < (u32)r);
    } else {
        st = self->forcedState;
    }
    if (self->f384 == 0 && p == (u8*)g_player && ((Player*)p)->state == 2 &&
        g_camera->snapping == 0) {
        if (self->forcedState == -1) {
            return;
        }
    }
    SetOnOffObjectState(self, st);
}

void UpdateOnOffObject(OnOffObject* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    if (self->forcedState != 0) {
        AppendQueuedCall(self->world, (void*)(void (*)(OnOffObject*, s32, s32))UpdateOnOffObjectState, self, 0, 0);
    }
}

void DrawOnOffObject(OnOffObject* self, void* arg1, void* arg2)
{
    DrawPlacedObject(self, arg1, arg2);
}

void SetOnOffObjectFrozen(OnOffObject* self, s32 p)
{
    SetPlacedObjectFrozen(self, p);
    if (p != 0) {
        SetOnOffObjectState(self, 0);
    }
}

void SetOnOffObjectBlockValue(OnOffObject* self, f32 value) { self->block2F0.f74 = value; self->block2F0.f78 = 1.0f; self->block2F0.f70 = value; }

typedef void (*OnOffShapeFn)(f32 angle, Arr63* obj, Vec02* out, Vec02* dir);

void PlaceOnOffCameraFrame(OnOffObject* self, Vec02* eye, Vec02* out, Vec02* dir)
{
    Vec02 a;
    Vec02 b;
    Mat02 m;
    TransformPointBetweenFrames(0, self, eye, &a);
    if (self->obj != 0) {
        OnOffShapeFn fn = *(OnOffShapeFn*)(*(u8**)self->obj + 8);
        if (fn != 0) {
            fn(self->angle3A0, self->obj, &b, dir);
        }
        BuildBasisFromXAndZHint(dir, &g_unitZVector, &m);
        Vu0::Q(*out) = Vu0::RotateTransposed(m, Vu0::Sub(Vu0::Q(a), Vu0::Q(b)));
    } else if (self->f38C != 0) {
        Vec02 p;
        ComputePolarOffset((Vec3*)&p, self->angle3A0 / self->orbitRadius, self->orbitRadius, 0.0f);
        Vu0::Q(b) = Vu0::Add(Vu0::Q(self->v400), Vu0::Q(p));
        u128 side = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(p));
        Vu0::Q(*dir) = Vu0::DivX(side, Vu0::Length(side));
        BuildBasisFromXAndZHint(dir, &g_unitZVector, &m);
        Vu0::Q(*out) = Vu0::RotateTransposed(m, Vu0::Sub(Vu0::Q(a), Vu0::Q(b)));
    } else {
        *dir = g_unitXVector;
        Vu0::Q(*out) = Vu0::RotateTransposed(*(Mat02*)(&self->rot3B0), Vu0::Sub(Vu0::Q(a), Vu0::Q(*(Vec02*)(&self->v3E0))));
    }
}

extern "C" f32 FloatRemainder(f32 x, f32 y);

void PlaceOnOffCameraOrbit(f32 angle, f32 offset, OnOffObject* self, f32* x, f32* poly, f32* range, s32 mode, Vec02* out)
{
    Vec02 v;
    Vec02 dir;
    Vec02 t;
    Mat02 m;
    Vec02 r;
    s32 i = 2;
    f32* o = &v.x;
    do {
        f32 p = poly[0] + x[0] * (poly[1] + x[0] * poly[2]);
        f32 lo = range[0];
        f32 hi = range[1];
        if (p < lo) {
            p = lo;
        } else if (hi < p) {
            p = hi;
        }
        *o++ = p;
        x++;
        range += 2;
        poly += 4;
    } while (--i >= 0);
    if (mode == 2) {
        v.x = -v.x;
    }
    if (self->f380 != 0) {
        ComputePolarOffset((Vec3*)&v, v.x, v.y, v.z);
    }
    if (self->obj != 0) {
        f32 a;
        if (mode != 1) {
            a = angle - offset;
        } else {
            a = angle + offset;
        }
        OnOffShapeFn fn = *(OnOffShapeFn*)(*(u8**)self->obj + 8);
        if (fn != 0) {
            fn(a, self->obj, &t, &dir);
        }
        BuildBasisFromXAndZHint(&dir, &g_unitZVector, &m);
        Vu0::Q(r) = Vu0::Rotate(m, Vu0::Q(v));
    } else if (self->f38C != 0) {
        f32 period = self->orbitRadius * 6.2831855f;
        f32 a;
        if (mode != 1) {
            a = angle - offset;
        } else {
            a = angle + offset;
        }
        f32 wrapped = FloatRemainder(a, period);
        ComputePolarOffset((Vec3*)&t, wrapped / self->orbitRadius, self->orbitRadius, 0.0f);
        u128 side = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(t));
        Vu0::Q(t) = Vu0::Add(Vu0::Q(t), Vu0::Q(self->v400));
        Vu0::Q(dir) = Vu0::DivX(side, Vu0::Length(side));
        BuildBasisFromXAndZHint(&dir, &g_unitZVector, &m);
        Vu0::Q(r) = Vu0::Rotate(m, Vu0::Q(v));
    } else {
        v.x += offset;
        t = *(Vec02*)(&self->v3E0);
        Vu0::Q(r) = Vu0::Rotate(*(Mat02*)(&self->rot3B0), Vu0::Q(v));
    }
    Vu0::Q(t) = Vu0::Add(Vu0::Q(t), Vu0::Q(r));
    TransformPointBetweenFrames(self, 0, &t, out);
}


// The camera parameters of an on/off object, the 0x90 bytes at 0x2F0 (Block63) that
// GetOnOffObjectBlock returns: only the floats this function reads are named.
struct OnOffCameraParams {
    f32 distance;
    u8 pad04[0x2C];
    f32 height;
    u8 pad34[0x24];
    f32 screenOffsetX;
    f32 screenOffsetY;
    u8 pad60[0x4];
    f32 turnRate;
    f32 followSpeed;
    u8 pad6C[0x14];
    f32 springStiffness;
    f32 springDamping;
    u8 pad88[0x8];
};
struct OnOffCameraView {
    u8 pad00[0x0C];
    f32 angle;
    f32 distance;
    f32 height;
    s32 turningToGoal;
    f32 goalAngle;
    s32 mode;
    s32 active24;
    s32 userTurned;
    f32 angleVelocity;
    f32 lastTurnTime;
    f32 frameAngle;
    f32 lastAngle1;
    f32 lastAngle2;
    f32 f40;
    f32 turnScale;
    f32 distanceVelocity;
    f32 heightVelocity;
    Vec02 v50;
    f32 f60;
};
struct OnOffEventObject { u8 pad[0x434]; s32 snapsCamera; f32 zoomOverride; f32 savedZoom; };
typedef void (*OnOffPoseFn)(Arr63* obj, Vec02* out, s32 a, s32 b, s32 c, s32 d, f32* angle);
struct TargetRecord_00143418;
struct Camera;

extern f32 g_gameClock[];

void ActivateOnOffCameraController(OnOffCameraController* self, OnOffObject* object)
{
    OnOffCameraView* view = (OnOffCameraView*)self;
    CameraPlacement place;
    Vec02 blended;
    Vec02 here;
    Vec02 sum;
    Vec02 polar;
    Camera* cam = self->owner;
    self->active24 = 1;
    self->ptr = object;
    void* target = cam->stack[0].target;
    void* block = GetOnOffObjectBlock(object);
    GetCameraTargetPlacement(cam, target, (TargetRecord_00143418*)&place, 0.0f);
    BlendOnOffCameraPoint(block, &place, &blended, 0);
    if (object != 0) {
        if (object->obj != 0) {
            TransformPointBetweenFrames(0, object, &blended, &here);
            OnOffPoseFn fn = *(OnOffPoseFn*)(*(u8**)object->obj + 0x28);
            if (fn != 0) {
                fn(object->obj, &here, 0, 0, 0, 0, &object->angle3A0);
            }
        } else if (object->f38C != 0) {
            ComputeOnOffCameraHeading(self, &place);
        }
        BlendOnOffCameraPoint(block, &place, &blended, object);
    }
    Vu0::Q(sum) = Vu0::Add(Vu0::Q(blended), Vu0::Q(g_camera->v270));
    ConvertOffsetToCylindrical((const Vec02*)cam->position, &sum, &view->angle, &view->distance, &view->height);
    f32 reach = Fpu::Sqrt(view->distance * view->distance + view->height * view->height);
    f32 scale = (reach - cam->nearDistance) / reach;
    f32 lateral = view->distance * scale;
    f32 radial = view->height * scale;
    view->height = radial;
    view->distance = lateral;
    ComputePolarOffset((Vec3*)&polar, view->angle, lateral, radial);
    Vu0::Q(view->v50) = Vu0::Add(Vu0::Q(sum), Vu0::Q(polar));
    view->mode = 0;
    if (object != 0 && ((OnOffEventObject*)object)->snapsCamera != 0) {
        RequestCameraSnap(cam, 0);
    }
    view->f60 = g_gameClock[1];
    view->f40 = g_gameClock[1];
    view->lastTurnTime = g_gameClock[1] - 10.0f;
    view->userTurned = 0;
    if (object != 0) {
        f32 fov = ((OnOffEventObject*)object)->zoomOverride;
        if (fov != 0.0f) {
            ((OnOffEventObject*)object)->savedZoom = g_camera->zoomGoal;
            g_camera->zoomGoal = fov;
        }
    }
    SetCameraAimOffsetFromScreenPoint(cam, &sum, ((Block63*)block)->f58, ((Block63*)block)->f5C);
}

void DeactivateOnOffCameraController(OnOffCameraController* self)
{
    CameraFovSource* s = (CameraFovSource*)self->ptr;
    if (s != 0) {
        if (s->zoomOverride != 0.0f) {
            Camera* g = g_camera;
            g->zoomGoal = s->savedZoom;
        }
    }
    self->ptr = 0;
}

void NoteOnOffCameraControllerPushed(OnOffCameraController* self, s32 arg)
{
}

void NoteOnOffCameraControllerRemoved(OnOffCameraController* self, s32 arg) {}

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

void ComputeOnOffCameraHeading(OnOffCameraController* self, CameraPlacement* eye)
{
    Vec02 blended;
    Vec02 here;
    Vec02 delta;
    OnOffObject* object = (OnOffObject*)self->ptr;
    if (!object)
        return;
    if (!object->obj && !object->f38C)
        return;
    BlendOnOffCameraPoint(GetOnOffObjectBlock(object), eye, &blended, 0);
    TransformPointBetweenFrames(0, object, &blended, &here);
    if (object->obj) {
        typedef void (*Fn)(f32, Arr63*, Vec02*, s32, s32, s32, s32, f32*);
        Fn fn = *(Fn*)(*(u8**)object->obj + 0x30);
        if (!fn)
            return;
        fn(object->angle3A0, object->obj, &here, 0, 0, 0, 0, &object->angle3A0);
    } else {
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(here), Vu0::Q(object->v400));
        f32 angle = ArctangentOfRatio(delta.y, delta.x);
        if (angle < 0.0f)
            angle += 6.2831855f;
        object->angle3A0 = angle * object->orbitRadius;
    }
}

extern s32 D_0026FA64;
extern f32 g_cameraAimSpringStiffness;
extern f32 g_cameraAimSpringDamping;
extern s32 D_00275978;
extern f32 g_onOffCameraTurnLimit;
extern f32 g_onOffCameraAimGain;
extern f32 g_onOffCameraStepRate[4];
extern f32 g_onOffCameraTurnTiltCoefficients[4];
extern f32 g_onOffCameraTurnTiltLimits[2];
extern f32 D_00275A58[6];
extern f32 g_onOffCameraTurnBlendCoefficients[4];
extern RampProfile g_onOffCameraFadeRamp;
extern RampProfile g_onOffCameraAngleRamp;
extern ValueRange g_unitRange;
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

void UpdateOnOffCameraController(OnOffCameraController* self, CameraPlacement* eye, PadRecord* pad, f32 dt)
{
    OnOffCameraView* view = (OnOffCameraView*)self;
    f32 step;
    if (D_0026FA64 != 0) {
        step = g_gameClock[2];
    } else {
        step = g_gameClock[5];
    }
    Camera* cam = self->owner;
    OnOffObject* object = (OnOffObject*)self->ptr;
    Player* target = (Player*)cam->stack[0].target;
    s32 flags;
    s32 hold;
    s32 limit;
    if (object != 0) {
        flags = object->i414;
        hold = object->f418;
        limit = object->f41C;
    } else {
        limit = 0;
        flags = 4;
        hold = 0;
    }
    ComputeOnOffCameraHeading(self, eye);
    OnOffCameraParams* block = (OnOffCameraParams*)GetOnOffObjectBlock(object);
    Vec02 blended;
    Vec02 sum;
    BlendOnOffCameraPoint(block, eye, &blended, object);
    if (target == g_player && target->f268C == 2) {
        Vec02 goal;
        Vu0::Q(goal) = Vu0::Sub(Vu0::Q(target->v2690), Vu0::Q(blended));
        SpringCameraVector(g_camera, &g_camera->v270, &g_camera->v280, &goal, 8.0f, -6.0f, dt);
    }
    Vu0::Q(sum) = Vu0::Add(Vu0::Q(blended), Vu0::Q(g_camera->v270));
    view->turnScale = ApproachValueWithRamp(view->turnScale, (*(s32*)&eye->q[0] & 1) ? 0.0f : block->turnRate, dt, &g_onOffCameraFadeRamp, 0);
    view->f40 = eye->q[3].z >? view->f40;
    Vec02 frame;
    Vec02 dir;
    Vec02 orbit1;
    Vec02 orbit2;
    f32 angle1, dist1, height1;
    f32 angle2, dist2, height2;
    if (object != 0 && (flags & 3)) {
        PlaceOnOffCameraFrame(object, &blended, &frame, &dir);
        if (object->f380 != 0) {
            ConvertOffsetToCylindrical(&frame, (Vec02*)&D_00248D30, &frame.x, &frame.y, &frame.z);
            if (view->active24 == 0) {
                frame.x += ClampToMagnitude(WrapAngle(view->frameAngle - frame.x), *(f32*)&object->f390);
            }
            view->frameAngle = frame.x;
        }
        if (flags & 1) {
            PlaceOnOffCameraOrbit(object->angle3A0, *(f32*)&object->block2F0, object, &frame.x,
                                  object->block2F0.f10, object->block2F0.f40, 1, &orbit1);
            ConvertOffsetToCylindrical(&orbit1, &sum, &angle1, &dist1, &height1);
        }
        if (object->i414 & 2) {
            PlaceOnOffCameraOrbit(object->angle3A0, *(f32*)&object->block2F0, object, &frame.x,
                                  object->block2F0.f10, object->block2F0.f40, 2, &orbit2);
            ConvertOffsetToCylindrical(&orbit2, &sum, &angle2, &dist2, &height2);
        }
    }
    if (view->active24 != 0) {
        view->mode = 4;
    }
    if (cam->snapping != 0) {
        if (cam->hasSnapValue != 0) {
            view->mode = 4;
            view->angle = cam->snapValue;
        } else if (!(flags & 3)) {
            view->mode = 4;
            view->angle = eye->q[3].x;
        } else if (!(flags & 2)) {
            view->mode = 1;
        } else if (flags & 1) {
            f32 a = WrapAngle(angle1 - eye->q[3].x);
            f32 b = WrapAngle(angle2 - eye->q[3].x);
            if (__builtin_fabsf(a) < __builtin_fabsf(b)) {
                view->mode = 1;
            } else {
                view->mode = 2;
            }
        } else {
            view->mode = 2;
        }
        view->f40 = g_gameClock[1];
        view->lastTurnTime = g_gameClock[1] - 10.0f;
    }
    if ((view->mode & flags) == 0 && 0 < view->mode && view->mode < 3) {
        view->mode = 4;
    }
    Vec02 offset;
    if (object != 0 && object->f444 != 0) {
        Vec02 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q((object->f444)->v140), Vu0::Q(eye->q[1]));
        d.z = 0.0f;
        const u128& zero = Vu0::Q(D_00248D30);
        Vu0::Vec v = Vu0::Vec::Of(d);
        Vu0::Vec l = Vu0::Length(v);
        if (Vu0::ToFloat(l) < 0.0001f) {
            Vu0::Set(d, zero);
        } else {
            Vu0::Set(d, Vu0::DivX(v, l).q);
        }
        f32 x = Vu0::ToFloatMoved(l);
        f32* poly = (f32*)&object->quad450;
        f32 p = poly[0] + x * (poly[1] + x * poly[2]);
        f32 s = ((ValueRange*)&object->pack460)->Clamp(p);
        Vu0::Set(offset, Vu0::MulX(Vu0::Vec::Of(d).q, Vu0::Scalar(s)));
    } else {
        offset = eye->q[2];
    }
    f32 angle = view->angle;
    if (pad->flags & 0x400) {
        if (flags & 4) {
            ClearPadPressedBits(pad, 0x400);
            StartSoundEffect(3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            view->turningToGoal = 1;
            view->goalAngle = WrapAngle(eye->q[3].x);
            view->lastTurnTime = g_gameClock[1];
            view->userTurned = 1;
            goto done;
        }
    } else if (flags & 4) {
        if (0.0f < pad->secondStickMagnitude || view->angleVelocity != 0.0f || view->turningToGoal != 0) {
            if (view->mode != 4) {
                StartSoundEffect(3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            if (0.0f < pad->secondStickMagnitude) {
                view->turningToGoal = 0;
            }
            if (view->turningToGoal != 0) {
                angle = ApproachAngleClampingVelocity(view->angle, view->angleVelocity, view->goalAngle, step, &g_onOffCameraAngleRamp, &view->angleVelocity);
                if (angle == view->goalAngle) {
                    view->turningToGoal = 0;
                }
            } else {
                f32 x = pad->secondStickX;
                f32 lim = g_onOffCameraStepRate[0] * step;
                f32 v = view->angleVelocity;
                f32 lo = v - lim;
                f32 hi = v + lim;
                f32 want = x * __builtin_fabsf(x) * g_onOffCameraAimGain;
                f32 nv = (want < lo) ? lo : ((hi < want) ? hi : want);
                view->angleVelocity = nv;
                angle = WrapAngle(view->angle + nv * step);
            }
            view->mode = 4;
            view->lastTurnTime = g_gameClock[1];
            view->userTurned = 1;
            goto done;
        }
    }
    if (view->mode == 4) {
        Vec02 stick;
        Vu0::Vec n;
        n.q = Vu0::FromFloats(pad->stickX, pad->stickY, 0.0f);
        *(Vu0::Vec*)&stick = n;
        *(Vu0::Vec*)&stick = Vu0::NormalizeOr(Vu0::Vec::Of(stick), Vu0::Vec::Of(g_unitXVector));
        Vec02 toCam;
        Vu0::Q(toCam) = Vu0::Sub(Vu0::Q(sum), Vu0::Q(cam->position));
        toCam.z = 0.0f;
        const u128& unitX = Vu0::Q(g_unitXVector);
        Vu0::Vec v = Vu0::Vec::Of(toCam);
        Vu0::Vec l = Vu0::Length(v);
        if (Vu0::ToFloat(l) < 0.0001f) {
            Vu0::Set(toCam, unitX);
        } else {
            Vu0::Set(toCam, Vu0::DivX(v, l).q);
        }
        f32 dist = Vu0::ToFloat(l);
        s32 sel;
        if (object == 0 || (sel = object->f430) == -1) {
            sel = *(s32*)&eye->q[3].w;
        }
        Vec02 axis;
        switch (sel) {
        case 0:
            Vu0::Q(axis) = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(toCam));
            break;
        case 1:
            axis = toCam;
            break;
        }
        f32 turn = ClampToMagnitude(Vu0::ToFloat(Vu0::Dot(Vu0::Q(offset), Vu0::Q(axis))) / dist, g_onOffCameraTurnLimit) * view->turnScale;
        f32 y = stick.y;
        turn *= ((ValueRange*)g_onOffCameraTurnTiltLimits)->Clamp(g_onOffCameraTurnTiltCoefficients[0] + y * (g_onOffCameraTurnTiltCoefficients[1] + y * g_onOffCameraTurnTiltCoefficients[2]));
        f32 t = g_gameClock[1] - view->lastTurnTime;
        turn *= g_unitRange.Limit(g_onOffCameraTurnBlendCoefficients[0] + t * (g_onOffCameraTurnBlendCoefficients[1] + t * g_onOffCameraTurnBlendCoefficients[2]));
        f32 next = WrapAngle(angle + turn * dt);
        if (!(flags & 3)) {
            angle = next;
            goto done;
        }
        f32 weight;
        f32 goal;
        if (object->obj == 0 && object->f38C == 0) {
            weight = 1.0f;
            goal = angle1;
        } else if (target == g_player && object == target->ownOnOffObject) {
            weight = 3.0f;
            goal = angle1;
        } else if (view->mode == 1) {
            weight = 1.0f;
            goal = angle1;
        } else if (view->mode == 2) {
            weight = 1.0f;
            goal = angle2;
        } else {
            Vec02 fwd;
            Mat02 basis;
            if (target == g_player && target->state == 13) {
                fwd = target->v150;
            } else {
                fwd = target->m110.r[0];
            }
            fwd.z = 0.0f;
            Vu0::Set(fwd, Vu0::NormalizeOr(Vu0::Vec::Of(fwd).q, Vu0::Q(g_unitXVector)));
            TransformDirectionBetweenFrames(object, 0, &dir, &dir);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(fwd).q, Vu0::Vec::Of(dir).q));
            weight = d * d * (3.0f - __builtin_fabsf(d));
            if (!(flags & 2)) {
                goal = angle1;
            } else if (0.0f < d) {
                goal = angle1;
            } else {
                goal = angle2;
            }
        }
        f32 speed;
        if (g_player != 0) {
            if (g_player->state == 6 && g_player->targetMode == 0) {
                f32 one = 1.0f;
                speed = one <? Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(offset), Vu0::Q(offset)))) * 0.005f;
            } else {
                f32 one = 1.0f;
                speed = one <? Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(offset), Vu0::Q(offset)))) * 0.0016666667f;
            }
        } else {
            speed = 0.0f;
        }
        speed *= block->followSpeed;
        if (limit != 0) {
            f32 t1 = g_gameClock[1] - (view->f40 + 0.75f);
            f32 t2 = g_gameClock[1] - (view->lastTurnTime + 10.0f);
            f32 ramp = object->limitRampTime;
            f32 s = 0.0f;
            if (0.0f < ramp) {
                s = ClampToRange(&g_unitRange, t1 / ramp);
                s *= ClampToRange(&g_unitRange, t2 / object->limitRampTime);
            } else if (0.0f < t1 && 0.0f < t2) {
                s = 1.0f;
            }
            s *= object->limitSpeed;
            if (speed * weight < s) {
                weight = 1.0f;
                speed = s;
            }
        }
        if (hold != 0 && view->userTurned == 0) {
            f32 s;
            if (0.0f < object->holdRampTime) {
                s = ClampToRange(&g_unitRange, (g_gameClock[1] - object->stateChangeTime) / object->holdRampTime);
            } else {
                s = 1.0f;
            }
            f32 hs = s * object->holdSpeed;
            if (speed * weight < hs) {
                weight = 1.0f;
                speed = hs;
            }
        }
        RampProfile prof;
        prof.maxSpeed = D_00275A58[0] * speed;
        prof.endSpeed = D_00275A58[1] * speed;
        prof.rampTime = D_00275A58[2];
        f32 a = ApproachAngleWithRamp(angle, WrapAngle(angle + WrapAngle(goal - angle)), dt, &prof, 0);
        f32 da = __builtin_fabsf(WrapAngle(goal - a));
        if (__builtin_fabsf(WrapAngle(goal - next)) < da) {
            a = next;
        }
        f32 e1 = WrapAngle(next - angle);
        f32 e2 = WrapAngle(a - angle);
        angle = WrapAngle(angle + (1.0f - weight) * e1 + weight * e2);
        if (view->active24 == 0) {
            if ((flags & 1) &&
                (WrapAngle(view->angle - view->lastAngle1) * WrapAngle(angle - angle1) <= 0.0f ||
                 __builtin_fabsf(WrapAngle(angle - angle1)) < 0.0001f) &&
                __builtin_fabsf(WrapAngle(angle - angle1)) < 1.5707964f) {
                view->mode = 1;
                view->userTurned = 1;
            } else if ((flags & 2) &&
                       (WrapAngle(view->angle - view->lastAngle2) * WrapAngle(angle - angle2) <= 0.0f ||
                        __builtin_fabsf(WrapAngle(angle - angle2)) < 0.0001f) &&
                       __builtin_fabsf(WrapAngle(angle - angle2)) < 1.5707964f) {
                view->mode = 2;
                view->userTurned = 1;
            }
        }
    }
done:
    f32 placeAngle, placeDist, placeHeight;
    f32 roll;
    f32 pitch;
    switch (view->mode) {
    case 1:
        placeAngle = angle1;
        placeDist = dist1;
        placeHeight = height1;
        roll = block->screenOffsetX;
        pitch = block->screenOffsetY;
        break;
    case 2:
        placeAngle = angle2;
        placeDist = dist2;
        placeHeight = height2;
        roll = -block->screenOffsetX;
        pitch = block->screenOffsetY;
        break;
    case 4:
        placeAngle = angle;
        if (!(flags & 3)) {
            placeDist = __builtin_fabsf(block->distance);
            placeHeight = block->height;
            roll = block->screenOffsetX;
            pitch = block->screenOffsetY;
        } else {
            f32 w;
            if (!(flags & 2)) {
                w = 1.0f;
            } else if ((flags & 1) == 0) {
                w = 0.0f;
            } else {
                if (angle1 > view->angle && angle2 > view->angle) {
                    if (angle2 < angle1) {
                        angle1 -= 6.2831855f;
                    } else {
                        angle2 -= 6.2831855f;
                    }
                } else if (angle1 < view->angle && angle2 < view->angle) {
                    if (angle1 < angle2) {
                        angle1 += 6.2831855f;
                    } else {
                        angle2 += 6.2831855f;
                    }
                }
                w = (view->angle - angle2) / (angle1 - angle2);
                w = w * w * (3.0f - (w + w));
            }
            f32 iw = 1.0f - w;
            f32 r = block->screenOffsetX;
            placeDist = w * dist1 + iw * dist2;
            placeHeight = w * height1 + iw * height2;
            roll = w * r + iw * -r;
            pitch = block->screenOffsetY;
        }
        break;
    }
    if (cam->snapping == 0) {
        view->distanceVelocity = (block->springDamping * g_cameraAimSpringDamping * dt + 1.0f) * view->distanceVelocity + (placeDist - view->distance) * block->springStiffness * g_cameraAimSpringStiffness * dt;
        placeDist = view->distance + view->distanceVelocity * dt;
        view->heightVelocity = (block->springDamping * g_cameraAimSpringDamping * dt + 1.0f) * view->heightVelocity + (placeHeight - view->height) * block->springStiffness * g_cameraAimSpringStiffness * dt;
        placeHeight = view->height + view->heightVelocity * dt;
    } else {
        view->distanceVelocity = view->heightVelocity = 0.0f;
    }
    Vec02 polar;
    ComputePolarOffset((Vec3*)&polar, placeAngle, placeDist, placeHeight);
    Vec02 pos;
    Vu0::Set(pos, Vu0::Add(Vu0::Q(sum), Vu0::Q(polar)));
    if (object == 0 || object->f440 == 0) {
        if (cam->snapping != 0) {
            if (cam->hasSnapValue == 0) {
                FindFreeOnOffCameraAngle(self, &sum, &pos, &pos);
            }
        } else if (D_00275978 == 0) {
            PushCameraOutOfGeometry(cam, (Quad16*)&view->v50, (Quad16*)&pos, &pos);
        }
    }
    ConvertOffsetToCylindrical(&pos, &sum, &placeAngle, &placeDist, &placeHeight);
    view->v50 = pos;
    ComputePolarOffset((Vec3*)&polar, placeAngle, placeDist, placeHeight);
    u128 len = Vu0::Length(Vu0::Q(polar));
    f32 l = Vu0::ToFloatMoved(len);
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(sum), Vu0::MulX(Vu0::Q(polar), Vu0::Scalar((l + cam->nearDistance) / l)));
    AimCameraAtPointWithSpring(cam, &sum, &pos, roll, pitch);
    view->angle = placeAngle;
    view->distance = placeDist;
    view->height = placeHeight;
    view->lastAngle1 = angle1;
    view->lastAngle2 = angle2;
    FadeCameraObstructingParts(cam);
    view->active24 = 0;
    FindFreeOnOffCameraScreenSpan(self, &sum);
}


extern s32 g_padSelectFlags;
extern f32 D_00275970;
extern f32 g_onOffCameraRetryDelay;
extern f32 g_gameClock[];
extern f32 g_gameTime;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
void FindFreeOnOffCameraScreenSpan(CameraController* self, Vec02* center)
{
    Vec02 lo;
    Vec02 hi;
    Vec02 tmp;
    Vec02 pts[5];
    Mat02 basis;
    s32 count;
    Collider** list;
    f32 spanEnd;
    s32 i;
    Camera* cam = (Camera*)self->owner;
    Collider* target = (Collider*)cam->stack[0].target;
    if (g_padSelectFlags & 2) {
        ((OnOffCameraController*)self)->lastMoveTime = g_gameTime;
        return;
    }
    if (self->ptr != 0 && ((OnOffObject*)self->ptr)->f440 != 0) {
        return;
    }
    if (D_00275978 != 0) {
        return;
    }
    if (g_gameClock[1] - ((OnOffCameraController*)self)->lastMoveTime < D_00275970) {
        return;
    }
    lo = hi = *(Vec02*)cam->position;
    *(Vu0::Vec*)&basis.r[2] = Vu0::Vec::Of(g_unitZVector);
    Vu0::Vec side = Vu0::NormalizeOr(Vu0::Cross(Vu0::Vec::Of(g_unitZVector), Vu0::Sub(Vu0::Vec::Of(target->v140), Vu0::Vec::Of(cam->position))), Vu0::Vec::Of(g_unitXVector));
    *(Vu0::Vec*)&basis.r[1] = side;
    *(Vu0::Vec*)&basis.r[0] = Vu0::Cross(Vu0::Vec::Of(basis.r[2]), side);
    for (i = 0; (u32)i < 5; i++) {
        Vu0::Vec p = Vu0::Add(Vu0::Vec::Of(target->v140), Vu0::Rotate(basis, Vu0::Vec::Of(g_onOffCameraProbeOffsets[i])));
        *(Vu0::Vec*)&lo = Vu0::Min(Vu0::Vec::Of(lo), p);
        *(Vu0::Vec*)&hi = Vu0::Max(Vu0::Vec::Of(lo), p);
        *(Vu0::Vec*)&pts[i] = p;
    }
    PushBackMemoryMark();
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, (s32 (*)(void*, Collider*))HasColliderSecondTree, 0, &count, &list);
    for (i = 0; (u32)i < 5; i++) {
        ProjectPointToCamera(cam, &pts[i], (f32*)&tmp);
        tmp.z = cam->nearDistance;
        UnprojectCameraPoint(cam, (f32*)&tmp, &tmp);
        if (FindFirstFreeSpan(count, list, &pts[i], &tmp, 0.0f, 0, &spanEnd) != 0 && 1.0f <= spanEnd) {
            ((OnOffCameraController*)self)->lastMoveTime = g_gameClock[1];
            break;
        }
    }
    PopBackMemoryMark();
    if (g_onOffCameraRetryDelay < g_gameClock[1] - ((OnOffCameraController*)self)->lastMoveTime) {
        QueueCameraSnap(cam);
    }
}

f32 GetSpanCandidateValue(void* a0, void* a1, void* a2, SpanCandidate* a3)
{
    return a3->value;
}

struct MeshHit;
typedef f32 (*MeshHitWeigh)(void* ctx, void* a, void* b, MeshHit* hit);
void ComputeConstrainedPushOut(void* ctx, s32 count, Collider** objs, MeshHitWeigh fn, f32 r, f32 limit, void* a4, Vec02* origin, Vec02* out);
void FindFreeOnOffCameraAngle(CameraController* self, Vec02* p, Vec02* q, Vec02* out)
{
    Vec02 lo;
    Vec02 hi;
    Vec02 pos;
    Vec02 best;
    s32 count;
    Collider** list;
    f32 spanLo;
    f32 spanHi;
    f32 m0;
    f32 m1;
    f32 m2;
    Camera* cam = (Camera*)self->owner;
    Collider* target = (Collider*)cam->stack[0].target;
    PushBackMemoryMark();
    Vu0::Q(lo) = Vu0::Min(Vu0::Q(*p), Vu0::Min(Vu0::Q(*q), Vu0::Q(target->v140)));
    Vu0::Q(hi) = Vu0::Max(Vu0::Q(*p), Vu0::Max(Vu0::Q(*q), Vu0::Q(target->v140)));
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, (s32 (*)(void*, Collider*))HasColliderSecondTree, 0, &count, &list);
    FindNearestFreePointAround(count, list, &target->v140, &pos, 500.0f);
    FindFirstFreeSpan(count, list, &pos, q, 0.0f, &spanLo, &spanHi);
    if (spanHi < 1.0f) {
        Vec02 dir;
        Vec02 cand;
        Vec02 mixed;
        ((OnOffCameraController*)self)->f20 = 4;
        ConvertOffsetToCylindrical(q, p, &m0, &m1, &m2);
        f32 bestScore = 3.40282347e+38f;
        f32 angle = 0.0f;
        f32 next;
        do {
            ComputePolarOffset((Vec3*)&dir, m0 + angle, m1, m2);
            Vu0::Q(cand) = Vu0::Add(Vu0::Q(*p), Vu0::Q(dir));
            FindFirstFreeSpan(count, list, &pos, &cand, 0.0f, &spanLo, &spanHi);
            f32 score = (1.25f - spanHi) * (__builtin_fabsf(angle) + 0.47123894f);
            if (score < bestScore) {
                bestScore = score;
                Vu0::Q(mixed) = Vu0::MulXSum(Vu0::Q(pos), Vu0::Scalar(1.0f - spanHi), Vu0::Q(cand), Vu0::Scalar(spanHi));
            }
            next = -angle;
            if (angle <= 0.0f) {
                next = next + 0.28559935f;
            }
            angle = next;
            if (bestScore < (__builtin_fabsf(next) + 0.47123894f) * 0.25f) {
                break;
            }
        } while (next < 3.1415927f);
        best = mixed;
    } else {
        Vu0::Q(best) = Vu0::MulXSum(Vu0::Q(pos), Vu0::Scalar(1.0f - spanHi), Vu0::Q(*q), Vu0::Scalar(spanHi));
    }
    ComputeConstrainedPushOut(cam, count, list, (MeshHitWeigh)GetSpanCandidateValue, ((f32*)cam)[0x1EC / 4], ((f32*)cam)[0x1EC / 4], &best, &best, out);
    FindFirstFreeSpan(count, list, &best, out, 0.0f, &spanLo, &spanHi);
    if (spanHi != 1.0f) {
        f32 w = (spanLo + spanHi) * 0.5f;
        Vu0::Q(*out) = Vu0::MulXSum(Vu0::Q(best), Vu0::Scalar(1.0f - w), Vu0::Q(*out), Vu0::Scalar(w));
    }
    PopBackMemoryMark();
}

// A point of a mesh's tables: a float and a vector (32 bytes).
struct MeshPoint {
    f32 f;
    u8 pad04[0xC];
    Vec02 v;
};

// A link of a mesh's tables: the point it starts at and two other links, or none.
struct MeshLink {
    MeshPoint* point;
    MeshLink* next[2];
};

u16 ReadBufferedU16(BufferedStream* s);
s32 ReadBufferedS16(BufferedStream* s);
f32 ReadBufferedFloat(BufferedStream* s);
void* AllocateFrontMemory(s32 size);

// Sets a link's other link from its index in the table, -1 for none.
static inline void SetLink(MeshLink* link, s32 which, MeshLink* links, s32 k)
{
    if (k == -1) {
        link->next[which] = 0;
    } else {
        link->next[which] = &links[k];
    }
}

void ReadMeshTables(void* stream, void* nOut, void* pointsOut, void* mOut, void* linksOut)
{
    BufferedStream* s = (BufferedStream*)stream;
    s32 n = ReadBufferedU16(s);
    MeshPoint* points = (MeshPoint*)AllocateFrontMemory(n * sizeof(MeshPoint));
    for (s32 i = 0; i < n; i++) {
        points[i].f = ReadBufferedFloat(s);
        ReadBufferedVector3(s, &points[i].v);
    }
    s32 m = ReadBufferedU16(s);
    MeshLink* links = (MeshLink*)AllocateFrontMemory(m * sizeof(MeshLink));
    for (s32 i = 0; i < m; i++) {
        MeshLink* link = &links[i];
        link->point = &points[ReadBufferedU16(s)];
        SetLink(link, 0, links, ReadBufferedS16(s));
        SetLink(link, 1, links, ReadBufferedS16(s));
    }
    *(s32*)nOut = n;
    *(MeshPoint**)pointsOut = points;
    *(s32*)mOut = m;
    *(MeshLink**)linksOut = links;
}

ASM_FUNC(func_001E4DC0);

WorldLoadRequest::WorldLoadRequest()
{
    key = 0;
    flags = 0;
    fC = f8 = -1;
    FillMemory(&current, 0, 0x20);
}

WorldLoadRequest g_worldLoadRequest;

void QueueWorldLoad(WorldLoadRequest* self, WorldKeyBlock* key, s32 a2, s32 a3, s32 flags)
{
    if (self->state == 0) {
        self->state = 1;
        self->key = key;
        self->f8 = a2;
        self->fC = a3;
        self->flags = flags;
    }
}

void RunPendingWorldLoad(WorldLoadRequest* self)
{
    KeyId key;
    WorldKeyBlock blob;
    LoadProgress o30;
    U32P w60, w70, w80, w90;
    OwnedStream sub;
    SetScreenOwner(2);
    if (self->key != 0) {
        ClearKeyId(&key);
        blob = *self->key;
        self->key = 0;
        key.second = blob.w[1] ^ blob.w[7];
        key.first = blob.w[0] ^ blob.w[5];
        if (key.second == 0) goto end;
        {
            WorldKeyBlock* s2 = &self->current;
            s32 ne = !SameWorldKey::Of(&blob, s2);
            w60.v = 0x3F00;
            w70.v = 0x3F3F3F;
            w80.v = 0x3F3F;
            w90.v = 0x3F;
            InitLoadProgress(&o30, &w60, &w70, &w80, &w90);
            InitBufferedStream(&sub, 0x340C00, g_packetBufferMemory, 6);
            sub.SetOwner(&o30);
            if (sub.owner != 0) BeginLoadProgress((LoadProgress*)sub.owner);
            if (OpenBufferedSectorStreamRange(&sub, &key) == 0) {
                DestroyBufferedStream(&sub, 2);
                goto end;
            }
            ResetWorldSubsystems(g_currentWorld);
            g_currentWorld = 0;
            ReadBufferedBlockHeader(ne, &sub);
            SetGameClockTime((GameClock*)&g_gameClock, 0.0f);
            SetPadSelectFlags(0x80);
            self->current = blob;
            SetCurrentLevelEntry((KeyedEntry*)s2, self->flags);
            g_currentWorld = CreateTypedRecord(0x6C, 0, 0, 3, -1);
            SetVolumeChannelFactor(0xA, 0, 0.0f);
            g_currentWorld->desc->m0A(g_currentWorld, &sub);
            CloseBufferedStream(&sub);
            if (sub.owner != 0) EndLoadProgress((LoadProgress*)sub.owner);
            if (g_saveData->optionFlags & 0x100) {
                GameProgress* c = g_memoryCard.image;
                if (c != 0 && (c->levelIndex != g_saveData->levelIndex || c->entryIndex != g_saveData->entryIndex))
                    StartMemoryCardSave(&g_memoryCard);
            }
            DestroyBufferedStream(&sub, 2);
        }
    }
    ResetCamera(g_camera, 1);
    UpdateSoundEmitters();
    SetVolumeChannelFactor(0xA, 0, 1.0f);
    FindOrActivateSwitchedCollider(g_currentWorld, self->f8, self->fC);
    NotifyScatterControllerLoaded(g_scatterController);
    ResetCounter((Counter*)D_002623D8);
    RestoreSelectionCaptionCamera(&g_selectionCaption);
    UpdateWorldContacts(g_currentWorld, 0);
    UpdateCamera(g_camera, 0, g_frameStep);
    if (self->flags & 0x10) g_reserveCountCaption.vt->m14(&g_reserveCountCaption);
    SetGameClockScale(1.0f);
end:
    ResetVolumeChannelFactors();
    SetVolumeChannelFactor(1, 1, g_currentWorld->volumeChannel1Factor);
    ClearScreenOwner(2);
    self->state = 0;
}

void RequestWorldLoadByMode(s32 mode)
{
    s32 n;
    SetIopVolumeChannel8(0.0f);
    switch (mode) {
    case 0:
        n = 0;
        break;
    case 1:
        StartScreenFadeFromFlagTable(&g_flagTable);
        return;
    case 2:
        n = 2;
        break;
    case 3:
        n = 4;
        break;
    }
    QueueWorldLoad(&g_worldLoadRequest, &g_worldLoadRequest.current, -1, -1, n);
}