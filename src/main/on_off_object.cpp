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




void* FillMemory(void* p, s32 value, s32 size);




void RemoveCameraControllers(u32 a0, int a1, int a2, void* a3, int a4, void* a5);
void PushCameraController(u32 a0, int a1, void* a2, int a3, void* a4);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
extern f32 g_gameTime;




void UpdateOnOffObjectState(void* self, s32 a, s32 b);




void UpdatePlacedObject(void* self);
void UpdateOnOffObjectState(void* self, s32 a, s32 b);
void* AppendQueuedCall(void* owner, void* fn, void* arg, s32 a3, s32 a4);



void DrawPlacedObject(void);





extern f32 D_00275980[16];






void UnregisterPlacedObject(void* self);
void SetOnOffObjectState(void* self, s32 state);
void RemoveQueuedCalls(void* a, s32 b, s32 c, void* d, s32 e, s32 f);



void StartPlacedObject(void* self);



void SetPlacedObjectFrozen(void* self, void* p);
void SetOnOffObjectState(void* selfv, s32 state);



void ReadBufferedRotation3(void* a, void* b);
void ReadBufferedVector3(void* a, void* b);
void ReadMeshTables(void* a, void* b, void* c, void* d, void* e);
s32 ReadBufferedS8(void* a);
void* CreatePathCurve(s32 idx);
void ReadPropertyRecords(void* a, void* b);




// What an on-off camera controller points to: while f438 is set, its f43C is the camera's f1C8.
struct CameraFovSource { u8 pad[0x438]; f32 f438; f32 f43C; };



void* FillMemory(void* p, s32 value, s32 size);



extern f32 D_00275980[];
extern f32 D_00275A10[4];
extern f32 D_00275A20[2];

void InitPlacedObject(void* self);





// A point as func_00128018 writes it and func_001E4DC0 tests it.
struct FacePoint {
    s32 v[4];
};


void* GetActiveSwitchedCollider(void);
void TransformPointBetweenFrames(void* a0, OnOffObject* a1, void* a2, FacePoint* a3);
s32 IsPointInsideFaceTree(TreeNode03* self, FacePoint* value);
void SetOnOffObjectState(OnOffObject* self, s32 state);




void* FillMemory(void* p, s32 value, s32 size);
void* FillMemory(void* p, s32 value, s32 size);

extern f32 g_gameClock[];


struct SpanCandidate { u8 pad[0x20]; f32 value; };



void* FillMemory(void* p, s32 value, s32 size);

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

void SetIopVolumeChannel8(f32 x);
void StartScreenFadeFromFlagTable(FlagTable* r);
void QueueWorldLoad(WorldLoadRequest* self, WorldKeyBlock* key, s32 a, s32 b, s32 flags);



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

extern u8 D_002C3B00[];
extern u8 g_scatterController[];
extern u8 D_002623D8[];

extern f32 g_frameStep;

void SetScreenOwner(s32 a);
void ClearKeyId(KeyId* q);
LoadProgress* InitLoadProgress(LoadProgress* q, U32P* a, U32P* b, U32P* c, U32P* d);
void* InitBufferedStream(BufferedStream* q, s32 a, u8* b, s32 c);
void BeginLoadProgress(void* q);
s32 OpenBufferedSectorStreamRange(BufferedStream* q, KeyId* k);
void DestroyBufferedStream(BufferedStream* q, s32 n);
void ResetWorldSubsystems(World* q);
void ReadBufferedBlockHeader(s32 a, BufferedStream* q);
void SetGameClockTime(u8* q, f32 v);
s32 SetPadSelectFlags(s32 n);
void SetCurrentLevelEntry(WorldKeyBlock* q, s32 n);
World* CreateTypedRecord(s32 a, s32 b, s32 c, s32 d, s32 e);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void CloseBufferedStream(BufferedStream* q);
void EndLoadProgress(void* q);
void StartMemoryCardSave(MemoryCard* q);
void ResetCamera(s32 q, s32 f);
void UpdateSoundEmitters(void);
s32 FindOrActivateSwitchedCollider(World* q, s32 a, s32 b);
void NotifyScatterControllerLoaded(u8* q);
void ResetCounter(u8* q);
void RestoreSelectionCaptionCamera(T217D_12E0* q);
void UpdateWorldContacts(World* q, s32 n);
void UpdateCamera(s32 q, s32 n, f32 v);
void SetGameClockScale(f32 x);
void ResetVolumeChannelFactors(void);
void ClearScreenOwner(s32 a);
INCLUDE_DATA(D_00275970);
INCLUDE_DATA(D_00275974);
s32 D_00275978 = 0;
f32 D_00275980[16] = { -450.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 1.0f, 0, 0, 125.0f, 1.0f, 0, 0 };
f32 D_002759C0[20] = { -3.4028235e38f, 3.4028235e38f, -3.4028235e38f, 3.4028235e38f, -3.4028235e38f, 3.4028235e38f, 0, -0.1f,
                        1.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 0, 0 };
f32 D_00275A10[4] = { 0, 0.5f, 0, 0 };
f32 D_00275A20[2] = { 0, 3.4028235e38f };
f32 D_00275A28 = 2.5f;
f32 D_00275A2C = 2.5f;
f32 D_00275A30[4] = { 15.0f, 0.0f, 0.0f, 0.0f };
f32 D_00275A40[4] = { 1.0f, -2.0f, -2.0f, 0.0f };
f32 D_00275A50[2] = { 1.0f, 2.0f };
f32 D_00275A58[6] = { 0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f };
f32 D_00275A70[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
RampProfile D_00275A80 = { 4.0f, 0.0f, 0.25f, 0.0f };
RampProfile D_00275A90 = { 2.5f, 0.0f, 0.35f, 15.0f };
Vec02 D_00275AA0[5] = { { 0, 0, 0, 0 }, { 0, -50.0f, 0, 0 }, { 0, 50.0f, 0, 0 }, { 0, 0, 75.0f, 0 }, { 0, 0, -50.0f, 0 } };

void* GetOnOffObjectBlock(void* self) { return self ? (u8*)self + 0x2F0 : (void*)D_00275980; }

struct CameraPlacement { Vec02 q[5]; };
void PlaceOnOffCameraFrame(OnOffObject* object, Vec02* eye, Vec02* x, Vec02* dir);
void PlaceOnOffCameraOrbit(f32 angle, f32 offset, OnOffObject* self, f32* x, f32* poly, f32* range, s32 mode, Vec02* out);
// The orbit's polynomial block: three rows of four floats, cleared before the blend fills them.
struct OrbitPoly {
    f32 f[12];
    void Clear() { FillMemory(this, 0, (s32)sizeof(*this)); }
};

void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object)
{
    f32 t = *(f32*)((u8*)block + 0x60);
    Vu0::Q(*out) = Vu0::MulXSum(Vu0::Q(eye->q[1]), Vu0::Scalar(1.0f - t), Vu0::Q(eye->q[4]), Vu0::Scalar(t));
    if (object != 0) {
        Vec02 x;
        OrbitPoly poly;
        Vec02 dir;
        poly.Clear();
        poly.f[1] = *(f32*)((u8*)block + 0x70);
        poly.f[5] = *(f32*)((u8*)block + 0x74);
        poly.f[9] = *(f32*)((u8*)block + 0x78);
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
    self->f428 = 2.0f;
    self->f42C = 1.0f;
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
    self->f420 = 2.0f;
    self->f424 = 1.0f;
    self->f430 = -1;
    self->quad450 = *(Quad63*)D_00275A10;
    {
        u8* src = (u8*)D_00275A20;
        self->pack460 = *(Pack63*)src;
    }
    self->f398 = -1;
}

void UnregisterOnOffObject(OnOffObject* self)
{
    UnregisterPlacedObject(self);
    SetOnOffObjectState(self, 0);
    RemoveQueuedCalls(self->world, 2, 0, self, -1, 0);
}

void LoadOnOffObject(OnOffObject* self, void* a1)
{
    ReadBufferedRotation3(a1, &self->rot);
    ReadBufferedVector3(a1, &self->pos);
    const Desc01* vt = self->desc;
    if (vt->m12 != 0) {
        vt->m12(self);
    }
    ReadMeshTables(a1, (u8*)self + 0x2D4, (u8*)self + 0x2D8, (u8*)self + 0x2DC, (u8*)self + 0x2E0);
    s32 idx = ReadBufferedS8(a1);
    if (idx != -1) {
        Arr63* o = (Arr63*)CreatePathCurve(idx);
        self->obj = o;
        void** curveTable = *(void***)o;
        if (curveTable[0] != 0) {
            ((void (*)(void*, void*))curveTable[0])(o, a1);
        }
        Arr63* p = self->obj;
        self->f3F0 = p->data[p->count - 1];
    } else {
        ReadBufferedRotation3(a1, (u8*)self + 0x3B0);
        ReadBufferedVector3(a1, (u8*)self + 0x3E0);
        *(s32*)&self->f3F0 = 0;
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
    if (self->f394 == state) return;
    if (state != 0) {
        if (state != 1) {
            self->f394 = state;
            goto tail;
        }
        u32 base = (u32)g_camera;
        PushCameraController(base, self->f388 + 2, (void*)(base + 0x520), (s32)self->f2D0, self);
        TriggerScriptEvent(self, 2, 0, 0);
    } else {
        u32 base = (u32)g_camera;
        RemoveCameraControllers(base, 8, -1, 0, 0, self);
        TriggerScriptEvent(self, 3, 0, 0);
    }
    self->f394 = state;
tail:
    self->f39C = g_gameTime;
}

void SetOnOffObjectForcedState(void* selfv, s32 value)
{
    OnOffObject* self = (OnOffObject*)selfv;
    if (value == self->f398) return;
    self->f398 = value;
    UpdateOnOffObjectState(self, 0, 0);
}

void UpdateOnOffObjectState(OnOffObject* self) {
    FacePoint loc;
    void* p = GetActiveSwitchedCollider();
    if (p == 0) {
        return;
    }
    if (p != self->f2D0) {
        SetOnOffObjectState(self, 0);
        self->f2D0 = p;
    }
    s32 st;
    if (self->f398 == -1) {
        TransformPointBetweenFrames(0, self, (u8*)p + 0x140, &loc);
        s32 r = IsPointInsideFaceTree((TreeNode03*)self->f2E0, &loc);
        st = (0u < (u32)r);
    } else {
        st = self->f398;
    }
    if (self->f384 == 0 && p == (u8*)g_player && ((Player*)p)->f2220 == 2 &&
        g_camera->f224 == 0) {
        if (self->f398 == -1) {
            return;
        }
    }
    SetOnOffObjectState(self, st);
}

void UpdateOnOffObject(OnOffObject* self)
{
    UpdatePlacedObject(self);
    if (self->f398 != 0) {
        AppendQueuedCall(self->world, (void*)(void (*)(OnOffObject*))UpdateOnOffObjectState, self, 0, 0);
    }
}

void DrawOnOffObject(void)
{
    DrawPlacedObject();
}

void SetOnOffObjectFrozen(OnOffObject* self, void* p)
{
    SetPlacedObjectFrozen(self, p);
    if (p != 0) {
        SetOnOffObjectState(self, 0);
    }
}

void SetOnOffObjectBlockValue(OnOffObject* self, f32 value) { *(f32*)(self->block2F0.d + 0x74) = value; *(f32*)(self->block2F0.d + 0x78) = 1.0f; *(f32*)(self->block2F0.d + 0x70) = value; }

typedef void (*OnOffShapeFn)(f32 angle, Arr63* obj, Vec02* out, Vec02* dir);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void BuildBasisFromXAndZHint(Vec02* dir, const Vec02* hint, Mat02* out);

void PlaceOnOffCameraFrame(OnOffObject* self, Vec02* eye, Vec02* out, Vec02* dir)
{
    Vec02 a;
    Vec02 b;
    Mat02 m;
    TransformPointBetweenFrames(0, self, eye, (FacePoint*)&a);
    if (self->obj != 0) {
        OnOffShapeFn fn = *(OnOffShapeFn*)(*(u8**)self->obj + 8);
        if (fn != 0) {
            fn(self->angle3A0, self->obj, &b, dir);
        }
        BuildBasisFromXAndZHint(dir, &g_unitZVector, &m);
        Vu0::Q(*out) = Vu0::RotateTransposed(m, Vu0::Sub(Vu0::Q(a), Vu0::Q(b)));
    } else if (self->f38C != 0) {
        Vec02 p;
        ComputePolarOffset(&p, self->angle3A0 / self->f410, self->f410, 0.0f);
        Vu0::Q(b) = Vu0::Add(Vu0::Q(self->v400), Vu0::Q(p));
        u128 side = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(p));
        Vu0::Q(*dir) = Vu0::DivX(side, Vu0::Length(side));
        BuildBasisFromXAndZHint(dir, &g_unitZVector, &m);
        Vu0::Q(*out) = Vu0::RotateTransposed(m, Vu0::Sub(Vu0::Q(a), Vu0::Q(b)));
    } else {
        *dir = g_unitXVector;
        Vu0::Q(*out) = Vu0::RotateTransposed(*(Mat02*)((u8*)self + 0x3B0), Vu0::Sub(Vu0::Q(a), Vu0::Q(*(Vec02*)((u8*)self + 0x3E0))));
    }
}

f32 FloatRemainder(f32 x, f32 y);
void TransformPointBetweenFrames(OnOffObject* from, void* to, void* in, FacePoint* out);

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
        ComputePolarOffset(&v, v.x, v.y, v.z);
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
        f32 period = self->f410 * 6.2831855f;
        f32 a;
        if (mode != 1) {
            a = angle - offset;
        } else {
            a = angle + offset;
        }
        f32 wrapped = FloatRemainder(a, period);
        ComputePolarOffset(&t, wrapped / self->f410, self->f410, 0.0f);
        u128 side = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(t));
        Vu0::Q(t) = Vu0::Add(Vu0::Q(t), Vu0::Q(self->v400));
        Vu0::Q(dir) = Vu0::DivX(side, Vu0::Length(side));
        BuildBasisFromXAndZHint(&dir, &g_unitZVector, &m);
        Vu0::Q(r) = Vu0::Rotate(m, Vu0::Q(v));
    } else {
        v.x += offset;
        t = *(Vec02*)((u8*)self + 0x3E0);
        Vu0::Q(r) = Vu0::Rotate(*(Mat02*)((u8*)self + 0x3B0), Vu0::Q(v));
    }
    Vu0::Q(t) = Vu0::Add(Vu0::Q(t), Vu0::Q(r));
    TransformPointBetweenFrames(self, 0, &t, (FacePoint*)out);
}

// The five quadwords func_00143418 gives for a camera and its target: the placement.
void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object);

// The camera parameters of an on/off object, the 0x90 bytes at 0x2F0 (Block63) that
// GetOnOffObjectBlock returns: only the floats this function reads are named.
struct OnOffCameraParams {
    f32 f00;
    u8 pad04[0x2C];
    f32 f30;
    u8 pad34[0x24];
    f32 f58;
    f32 f5C;
    u8 pad60[0x4];
    f32 f64;
    f32 f68;
    u8 pad6C[0x14];
    f32 f80;
    f32 f84;
    u8 pad88[0x8];
};
struct OnOffCameraView {
    u8 pad00[0x0C];
    f32 f0C;
    f32 f10;
    f32 f14;
    s32 f18;
    f32 f1C;
    s32 f20;
    s32 active24;
    s32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    Vec02 v50;
    f32 f60;
};
struct OnOffEventObject { u8 pad[0x434]; s32 f434; f32 f438; f32 f43C; };
typedef void (*OnOffPoseFn)(Arr63* obj, Vec02* out, s32 a, s32 b, s32 c, s32 d, f32* angle);
void ConvertOffsetToCylindrical(void* camera, Vec02* point, f32* a, f32* b, f32* c);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void RequestCameraSnap(Camera* camera, s32 mode);
void SetCameraAimOffsetFromScreenPoint(Camera* camera, Vec02* point, f32 a, f32 b);
void* GetOnOffObjectBlock(void* self);
void ComputeOnOffCameraHeading(OnOffCameraController* self, CameraPlacement* eye);
void GetCameraTargetPlacement(Camera* camera, s32 target, CameraPlacement* out, f32 t);

void TransformPointBetweenFrames(void* a0, OnOffObject* a1, void* a2, FacePoint* a3);
extern f32 g_gameClock[];
void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object);

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
    s32 target = *(s32*)((u8*)cam + 0x3DC);
    void* block = GetOnOffObjectBlock(object);
    GetCameraTargetPlacement(cam, target, &place, 0.0f);
    BlendOnOffCameraPoint(block, &place, &blended, 0);
    if (object != 0) {
        if (object->obj != 0) {
            TransformPointBetweenFrames(0, object, &blended, (FacePoint*)&here);
            OnOffPoseFn fn = *(OnOffPoseFn*)(*(u8**)object->obj + 0x28);
            if (fn != 0) {
                fn(object->obj, &here, 0, 0, 0, 0, &object->angle3A0);
            }
        } else if (object->f38C != 0) {
            ComputeOnOffCameraHeading(self, &place);
        }
        BlendOnOffCameraPoint(block, &place, &blended, object);
    }
    Vu0::Q(sum) = Vu0::Add(Vu0::Q(blended), Vu0::Q(*(Vec02*)((u8*)g_camera + 0x270)));
    ConvertOffsetToCylindrical((u8*)cam + 0x40, &sum, &view->f0C, &view->f10, &view->f14);
    f32 reach = Fpu::Sqrt(view->f10 * view->f10 + view->f14 * view->f14);
    f32 scale = (reach - *(f32*)((u8*)cam + 0x1E4)) / reach;
    f32 lateral = view->f10 * scale;
    f32 radial = view->f14 * scale;
    view->f14 = radial;
    view->f10 = lateral;
    ComputePolarOffset(&polar, view->f0C, lateral, radial);
    Vu0::Q(view->v50) = Vu0::Add(Vu0::Q(sum), Vu0::Q(polar));
    view->f20 = 0;
    if (object != 0 && ((OnOffEventObject*)object)->f434 != 0) {
        RequestCameraSnap(cam, 0);
    }
    view->f60 = g_gameClock[1];
    view->f40 = g_gameClock[1];
    view->f30 = g_gameClock[1] - 10.0f;
    view->f28 = 0;
    if (object != 0) {
        f32 fov = ((OnOffEventObject*)object)->f438;
        if (fov != 0.0f) {
            ((OnOffEventObject*)object)->f43C = g_camera->f1C8;
            g_camera->f1C8 = fov;
        }
    }
    SetCameraAimOffsetFromScreenPoint(cam, &sum, *(f32*)((u8*)block + 0x58), *(f32*)((u8*)block + 0x5C));
}

void DeactivateOnOffCameraController(OnOffCameraController* self)
{
    CameraFovSource* s = (CameraFovSource*)self->ptr;
    if (s != 0) {
        if (s->f438 != 0.0f) {
            Camera* g = g_camera;
            g->f1C8 = s->f43C;
        }
    }
    self->ptr = 0;
}

void NoteOnOffCameraControllerPushed(OnOffCameraController* self, s32 arg)
{
}

void NoteOnOffCameraControllerRemoved(OnOffCameraController* self, s32 arg) {}

f32 ArctangentOfRatio(f32 y, f32 x);

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
    TransformPointBetweenFrames(0, object, &blended, (FacePoint*)&here);
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
        object->angle3A0 = angle * object->f410;
    }
}

extern s32 D_0026FA64;
extern f32 D_00261920;
extern f32 D_00261924;
extern s32 D_00275978;
extern f32 D_00275A28;
extern f32 D_00275A2C;
extern f32 D_00275A30[4];
extern f32 D_00275A40[4];
extern f32 D_00275A50[2];
extern f32 D_00275A58[6];
extern f32 D_00275A70[4];
extern RampProfile D_00275A80;
extern RampProfile D_00275A90;
extern ValueRange g_unitRange;
f32 WrapAngle(f32 a);
f32 ClampToMagnitude(f32 a, f32 b);
f32 ClampToRange(ValueRange* range, f32 v);
f32 ApproachValueWithRamp(f32 value, f32 target, f32 dt, RampProfile* profile, f32* speed);
f32 ApproachAngleWithRamp(f32 angle, f32 target, f32 dt, RampProfile* profile, f32* speed);
f32 ApproachAngleClampingVelocity(f32 angle, f32 speed, f32 target, f32 dt, RampProfile* profile, f32* out);
void SpringCameraVector(Camera* cam, Vec02* pos, Vec02* vel, Vec02* goal, f32 a, f32 b, f32 dt);
void StartSoundEffect(s32 id, s32 a, s32 b, s32 c, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, s32 d, s32 e);
void ClearPadPressedBits(PadRecord* self, s32 mask);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
void FindFreeOnOffCameraAngle(OnOffCameraController* self, Vec02* center, Vec02* in, Vec02* out);
void FindFreeOnOffCameraScreenSpan(OnOffCameraController* self, Vec02* center);
void PushCameraOutOfGeometry(Camera* cam, Vec02* from, Vec02* in, Vec02* out);
void AimCameraAtPointWithSpring(Camera* cam, Vec02* center, Vec02* pos, f32 a, f32 b);
void FadeCameraObstructingParts(Camera* cam);

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
        SpringCameraVector(g_camera, (Vec02*)((u8*)g_camera + 0x270), (Vec02*)((u8*)g_camera + 0x280), &goal, 8.0f, -6.0f, dt);
    }
    Vu0::Q(sum) = Vu0::Add(Vu0::Q(blended), Vu0::Q(*(Vec02*)((u8*)g_camera + 0x270)));
    view->f44 = ApproachValueWithRamp(view->f44, (*(s32*)&eye->q[0] & 1) ? 0.0f : block->f64, dt, &D_00275A80, 0);
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
                frame.x += ClampToMagnitude(WrapAngle(view->f34 - frame.x), *(f32*)&object->f390);
            }
            view->f34 = frame.x;
        }
        if (flags & 1) {
            PlaceOnOffCameraOrbit(object->angle3A0, *(f32*)&object->block2F0, object, &frame.x,
                                  (f32*)((u8*)object + 0x300), (f32*)((u8*)object + 0x330), 1, &orbit1);
            ConvertOffsetToCylindrical(&orbit1, &sum, &angle1, &dist1, &height1);
        }
        if (object->i414 & 2) {
            PlaceOnOffCameraOrbit(object->angle3A0, *(f32*)&object->block2F0, object, &frame.x,
                                  (f32*)((u8*)object + 0x300), (f32*)((u8*)object + 0x330), 2, &orbit2);
            ConvertOffsetToCylindrical(&orbit2, &sum, &angle2, &dist2, &height2);
        }
    }
    if (view->active24 != 0) {
        view->f20 = 4;
    }
    if (cam->f224 != 0) {
        if (cam->f228 != 0) {
            view->f20 = 4;
            view->f0C = cam->f22C;
        } else if (!(flags & 3)) {
            view->f20 = 4;
            view->f0C = eye->q[3].x;
        } else if (!(flags & 2)) {
            view->f20 = 1;
        } else if (flags & 1) {
            f32 a = WrapAngle(angle1 - eye->q[3].x);
            f32 b = WrapAngle(angle2 - eye->q[3].x);
            if (__builtin_fabsf(a) < __builtin_fabsf(b)) {
                view->f20 = 1;
            } else {
                view->f20 = 2;
            }
        } else {
            view->f20 = 2;
        }
        view->f40 = g_gameClock[1];
        view->f30 = g_gameClock[1] - 10.0f;
    }
    if ((view->f20 & flags) == 0 && 0 < view->f20 && view->f20 < 3) {
        view->f20 = 4;
    }
    Vec02 offset;
    if (object != 0 && *(PlacedObject**)((u8*)object + 0x444) != 0) {
        Vec02 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q((*(PlacedObject**)((u8*)object + 0x444))->v140), Vu0::Q(eye->q[1]));
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
    f32 angle = view->f0C;
    if (pad->flags & 0x400) {
        if (flags & 4) {
            ClearPadPressedBits(pad, 0x400);
            StartSoundEffect(3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            view->f18 = 1;
            view->f1C = WrapAngle(eye->q[3].x);
            view->f30 = g_gameClock[1];
            view->f28 = 1;
            goto done;
        }
    } else if (flags & 4) {
        if (0.0f < pad->f7C || view->f2C != 0.0f || view->f18 != 0) {
            if (view->f20 != 4) {
                StartSoundEffect(3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            if (0.0f < pad->f7C) {
                view->f18 = 0;
            }
            if (view->f18 != 0) {
                angle = ApproachAngleClampingVelocity(view->f0C, view->f2C, view->f1C, step, &D_00275A90, &view->f2C);
                if (angle == view->f1C) {
                    view->f18 = 0;
                }
            } else {
                f32 x = pad->f74;
                f32 lim = D_00275A30[0] * step;
                f32 v = view->f2C;
                f32 lo = v - lim;
                f32 hi = v + lim;
                f32 want = x * __builtin_fabsf(x) * D_00275A2C;
                f32 nv = (want < lo) ? lo : ((hi < want) ? hi : want);
                view->f2C = nv;
                angle = WrapAngle(view->f0C + nv * step);
            }
            view->f20 = 4;
            view->f30 = g_gameClock[1];
            view->f28 = 1;
            goto done;
        }
    }
    if (view->f20 == 4) {
        Vec02 stick;
        Vu0::Vec n;
        n.q = Vu0::FromFloats(pad->f40, pad->f44, 0.0f);
        *(Vu0::Vec*)&stick = n;
        *(Vu0::Vec*)&stick = Vu0::NormalizeOr(Vu0::Vec::Of(stick), Vu0::Vec::Of(g_unitXVector));
        Vec02 toCam;
        Vu0::Q(toCam) = Vu0::Sub(Vu0::Q(sum), Vu0::Q(cam->f40));
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
        f32 turn = ClampToMagnitude(Vu0::ToFloat(Vu0::Dot(Vu0::Q(offset), Vu0::Q(axis))) / dist, D_00275A28) * view->f44;
        f32 y = stick.y;
        turn *= ((ValueRange*)D_00275A50)->Clamp(D_00275A40[0] + y * (D_00275A40[1] + y * D_00275A40[2]));
        f32 t = g_gameClock[1] - view->f30;
        turn *= g_unitRange.Limit(D_00275A70[0] + t * (D_00275A70[1] + t * D_00275A70[2]));
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
        } else if (target == g_player && object == target->f2678) {
            weight = 3.0f;
            goal = angle1;
        } else if (view->f20 == 1) {
            weight = 1.0f;
            goal = angle1;
        } else if (view->f20 == 2) {
            weight = 1.0f;
            goal = angle2;
        } else {
            Vec02 fwd;
            Mat02 basis;
            if (target == g_player && target->f2220 == 13) {
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
            if (g_player->f2220 == 6 && g_player->f239C == 0) {
                f32 one = 1.0f;
                speed = one <? Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(offset), Vu0::Q(offset)))) * 0.005f;
            } else {
                f32 one = 1.0f;
                speed = one <? Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(offset), Vu0::Q(offset)))) * 0.0016666667f;
            }
        } else {
            speed = 0.0f;
        }
        speed *= block->f68;
        if (limit != 0) {
            f32 t1 = g_gameClock[1] - (view->f40 + 0.75f);
            f32 t2 = g_gameClock[1] - (view->f30 + 10.0f);
            f32 ramp = object->f428;
            f32 s = 0.0f;
            if (0.0f < ramp) {
                s = ClampToRange(&g_unitRange, t1 / ramp);
                s *= ClampToRange(&g_unitRange, t2 / object->f428);
            } else if (0.0f < t1 && 0.0f < t2) {
                s = 1.0f;
            }
            s *= object->f42C;
            if (speed * weight < s) {
                weight = 1.0f;
                speed = s;
            }
        }
        if (hold != 0 && view->f28 == 0) {
            f32 s;
            if (0.0f < object->f420) {
                s = ClampToRange(&g_unitRange, (g_gameClock[1] - object->f39C) / object->f420);
            } else {
                s = 1.0f;
            }
            f32 hs = s * object->f424;
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
                (WrapAngle(view->f0C - view->f38) * WrapAngle(angle - angle1) <= 0.0f ||
                 __builtin_fabsf(WrapAngle(angle - angle1)) < 0.0001f) &&
                __builtin_fabsf(WrapAngle(angle - angle1)) < 1.5707964f) {
                view->f20 = 1;
                view->f28 = 1;
            } else if ((flags & 2) &&
                       (WrapAngle(view->f0C - view->f3C) * WrapAngle(angle - angle2) <= 0.0f ||
                        __builtin_fabsf(WrapAngle(angle - angle2)) < 0.0001f) &&
                       __builtin_fabsf(WrapAngle(angle - angle2)) < 1.5707964f) {
                view->f20 = 2;
                view->f28 = 1;
            }
        }
    }
done:
    f32 placeAngle, placeDist, placeHeight;
    f32 roll;
    f32 pitch;
    switch (view->f20) {
    case 1:
        placeAngle = angle1;
        placeDist = dist1;
        placeHeight = height1;
        roll = block->f58;
        pitch = block->f5C;
        break;
    case 2:
        placeAngle = angle2;
        placeDist = dist2;
        placeHeight = height2;
        roll = -block->f58;
        pitch = block->f5C;
        break;
    case 4:
        placeAngle = angle;
        if (!(flags & 3)) {
            placeDist = __builtin_fabsf(block->f00);
            placeHeight = block->f30;
            roll = block->f58;
            pitch = block->f5C;
        } else {
            f32 w;
            if (!(flags & 2)) {
                w = 1.0f;
            } else if ((flags & 1) == 0) {
                w = 0.0f;
            } else {
                if (angle1 > view->f0C && angle2 > view->f0C) {
                    if (angle2 < angle1) {
                        angle1 -= 6.2831855f;
                    } else {
                        angle2 -= 6.2831855f;
                    }
                } else if (angle1 < view->f0C && angle2 < view->f0C) {
                    if (angle1 < angle2) {
                        angle1 += 6.2831855f;
                    } else {
                        angle2 += 6.2831855f;
                    }
                }
                w = (view->f0C - angle2) / (angle1 - angle2);
                w = w * w * (3.0f - (w + w));
            }
            f32 iw = 1.0f - w;
            f32 r = block->f58;
            placeDist = w * dist1 + iw * dist2;
            placeHeight = w * height1 + iw * height2;
            roll = w * r + iw * -r;
            pitch = block->f5C;
        }
        break;
    }
    if (cam->f224 == 0) {
        view->f48 = (block->f84 * D_00261924 * dt + 1.0f) * view->f48 + (placeDist - view->f10) * block->f80 * D_00261920 * dt;
        placeDist = view->f10 + view->f48 * dt;
        view->f4C = (block->f84 * D_00261924 * dt + 1.0f) * view->f4C + (placeHeight - view->f14) * block->f80 * D_00261920 * dt;
        placeHeight = view->f14 + view->f4C * dt;
    } else {
        view->f48 = view->f4C = 0.0f;
    }
    Vec02 polar;
    ComputePolarOffset(&polar, placeAngle, placeDist, placeHeight);
    Vec02 pos;
    Vu0::Set(pos, Vu0::Add(Vu0::Q(sum), Vu0::Q(polar)));
    if (object == 0 || *(s32*)((u8*)object + 0x440) == 0) {
        if (cam->f224 != 0) {
            if (cam->f228 == 0) {
                FindFreeOnOffCameraAngle(self, &sum, &pos, &pos);
            }
        } else if (D_00275978 == 0) {
            PushCameraOutOfGeometry(cam, &view->v50, &pos, &pos);
        }
    }
    ConvertOffsetToCylindrical(&pos, &sum, &placeAngle, &placeDist, &placeHeight);
    view->v50 = pos;
    ComputePolarOffset(&polar, placeAngle, placeDist, placeHeight);
    u128 len = Vu0::Length(Vu0::Q(polar));
    f32 l = Vu0::ToFloatMoved(len);
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(sum), Vu0::MulX(Vu0::Q(polar), Vu0::Scalar((l + cam->f1E4) / l)));
    AimCameraAtPointWithSpring(cam, &sum, &pos, roll, pitch);
    view->f0C = placeAngle;
    view->f10 = placeDist;
    view->f14 = placeHeight;
    view->f38 = angle1;
    view->f3C = angle2;
    FadeCameraObstructingParts(cam);
    view->active24 = 0;
    FindFreeOnOffCameraScreenSpan(self, &sum);
}


extern s32 g_padSelectFlags;
extern f32 D_00275970;
extern f32 D_00275974;
extern f32 g_gameClock[];
extern f32 g_gameTime;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void ProjectPointToCamera(Camera* cam, Vec02* in, Vec02* out);
void UnprojectCameraPoint(Camera* cam, Vec02* in, Vec02* out);
void QueueCameraSnap(Camera* cam);
s32 HasColliderSecondTree(void* unused, Collider* other);
void GatherCollidersInBox(void* world, void* self, Vec02* a, Vec02* b, void* filter, s32 d, s32* count, Collider*** list);
s32 FindFirstFreeSpan(s32 count, Collider** objs, void* a2, void* a3, f32 thresh, f32* lo, f32* hi);
void FindFreeOnOffCameraScreenSpan(CameraController* self)
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
        *(f32*)((u8*)self + 0x60) = g_gameTime;
        return;
    }
    if (self->ptr != 0 && *(s32*)((u8*)self->ptr + 0x440) != 0) {
        return;
    }
    if (D_00275978 != 0) {
        return;
    }
    if (g_gameClock[1] - *(f32*)((u8*)self + 0x60) < D_00275970) {
        return;
    }
    lo = hi = *(Vec02*)cam->f40;
    *(Vu0::Vec*)&basis.r[2] = Vu0::Vec::Of(g_unitZVector);
    Vu0::Vec side = Vu0::NormalizeOr(Vu0::Cross(Vu0::Vec::Of(g_unitZVector), Vu0::Sub(Vu0::Vec::Of(target->v140), Vu0::Vec::Of(cam->f40))), Vu0::Vec::Of(g_unitXVector));
    *(Vu0::Vec*)&basis.r[1] = side;
    *(Vu0::Vec*)&basis.r[0] = Vu0::Cross(Vu0::Vec::Of(basis.r[2]), side);
    for (i = 0; (u32)i < 5; i++) {
        Vu0::Vec p = Vu0::Add(Vu0::Vec::Of(target->v140), Vu0::Rotate(basis, Vu0::Vec::Of(D_00275AA0[i])));
        *(Vu0::Vec*)&lo = Vu0::Min(Vu0::Vec::Of(lo), p);
        *(Vu0::Vec*)&hi = Vu0::Max(Vu0::Vec::Of(lo), p);
        *(Vu0::Vec*)&pts[i] = p;
    }
    PushBackMemoryMark();
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, (void*)HasColliderSecondTree, 0, &count, &list);
    for (i = 0; (u32)i < 5; i++) {
        ProjectPointToCamera(cam, &pts[i], &tmp);
        tmp.z = cam->f1E4;
        UnprojectCameraPoint(cam, &tmp, &tmp);
        if (FindFirstFreeSpan(count, list, &pts[i], &tmp, 0.0f, 0, &spanEnd) != 0 && 1.0f <= spanEnd) {
            *(f32*)((u8*)self + 0x60) = g_gameClock[1];
            break;
        }
    }
    PopBackMemoryMark();
    if (D_00275974 < g_gameClock[1] - *(f32*)((u8*)self + 0x60)) {
        QueueCameraSnap(cam);
    }
}

f32 GetSpanCandidateValue(void* a0, void* a1, void* a2, SpanCandidate* a3)
{
    return a3->value;
}

void FindNearestFreePointAround(s32 count, Collider** objs, Vec02* origin, Vec02* out, f32 r);
void ComputeConstrainedPushOut(void* ctx, s32 count, Collider** objs, void* fn, f32 r, f32 limit, void* a4, Vec02* origin, Vec02* out);
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
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, (void*)HasColliderSecondTree, 0, &count, &list);
    FindNearestFreePointAround(count, list, &target->v140, &pos, 500.0f);
    FindFirstFreeSpan(count, list, &pos, q, 0.0f, &spanLo, &spanHi);
    if (spanHi < 1.0f) {
        Vec02 dir;
        Vec02 cand;
        Vec02 mixed;
        *(s32*)((u8*)self + 0x20) = 4;
        ConvertOffsetToCylindrical(q, p, &m0, &m1, &m2);
        f32 bestScore = 3.40282347e+38f;
        f32 angle = 0.0f;
        f32 next;
        do {
            ComputePolarOffset(&dir, m0 + angle, m1, m2);
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
    ComputeConstrainedPushOut(cam, count, list, (void*)GetSpanCandidateValue, ((f32*)cam)[0x1EC / 4], ((f32*)cam)[0x1EC / 4], &best, &best, out);
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

s32 ReadBufferedU16(BufferedStream* s);
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
            InitBufferedStream(&sub, 0x340C00, D_002C3B00, 6);
            sub.SetOwner(&o30);
            if (sub.owner != 0) BeginLoadProgress(sub.owner);
            if (OpenBufferedSectorStreamRange(&sub, &key) == 0) {
                DestroyBufferedStream(&sub, 2);
                goto end;
            }
            ResetWorldSubsystems(g_currentWorld);
            g_currentWorld = 0;
            ReadBufferedBlockHeader(ne, &sub);
            SetGameClockTime(((u8*)&g_gameClock), 0.0f);
            SetPadSelectFlags(0x80);
            self->current = blob;
            SetCurrentLevelEntry(s2, self->flags);
            g_currentWorld = CreateTypedRecord(0x6C, 0, 0, 3, -1);
            SetVolumeChannelFactor(0xA, 0, 0.0f);
            g_currentWorld->desc->m0A(g_currentWorld, &sub);
            CloseBufferedStream(&sub);
            if (sub.owner != 0) EndLoadProgress(sub.owner);
            if (g_saveData->f19EC & 0x100) {
                GameProgress* c = g_memoryCard.image;
                if (c != 0 && (c->f19D8 != g_saveData->f19D8 || c->f19DC != g_saveData->f19DC))
                    StartMemoryCardSave(&g_memoryCard);
            }
            DestroyBufferedStream(&sub, 2);
        }
    }
    ResetCamera((*(s32*)&g_camera), 1);
    UpdateSoundEmitters();
    SetVolumeChannelFactor(0xA, 0, 1.0f);
    FindOrActivateSwitchedCollider(g_currentWorld, self->f8, self->fC);
    NotifyScatterControllerLoaded(g_scatterController);
    ResetCounter(D_002623D8);
    RestoreSelectionCaptionCamera(&D_0026FA90);
    UpdateWorldContacts(g_currentWorld, 0);
    UpdateCamera((*(s32*)&g_camera), 0, g_frameStep);
    if (self->flags & 0x10) D_0026C6C8.vt->m14(&D_0026C6C8);
    SetGameClockScale(1.0f);
end:
    ResetVolumeChannelFactors();
    SetVolumeChannelFactor(1, 1, g_currentWorld->f1D7C);
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