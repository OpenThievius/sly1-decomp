// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x18F988 to 0x193210: one file between two exact edges (it could be several).
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "box_collider.h"
#include "object_link.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "point_graph_object.h"
#include "world.h"
#include "step_sequence.h"
#include "screen_element.h"
#include "globals.h"
#include "pad_record.h"
#include "effect.h"
#include "vu0.h"
#include "object_message.h"
void InitCollider(void* self);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void InitAgent(void* self);
void StartAgent(void* self);
void ResolveObjectLinks(void* self, s32 n, void* table);
s32 ResolveAgentClip(void* self, s32 id);
void RemoveItemKeeperMember(void* a, void* b);
void EnterAgentState(void* self, s32 a, s32 b);
s32 IsObjectAttached();
s32 FindSwitchedColliderIndex(SwitchedCollider* value);
s32 FindSwitchedColliderIndex(void* value);
void ActivateSwitchedColliderIndex(s32 index);
void* MoveMemory(void* dst, void* src, s32 size);
void RegisterCollider(void* self);
void AddToSwitchedColliderList(void* self);
void UnregisterCollider(void* self);
void RemoveFromSwitchedColliderList(void* self);
void AddToSwitchedColliderList(SwitchedCollider* self);
void RemoveFromSwitchedColliderList(SwitchedCollider* self);
void* GetActiveSwitchedCollider();
// The two interaction flags GetSwitchedColliderInteractFlags gives.
struct InteractFlags {
    s32 a;
    s32 b;
};
s32 IsObjectInPool(void* p, s32 v);
s32 AcceptAgentRequest(void* self, s32* arg);
void StartObject(void* self);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void TransformPointBetweenFrames(void* a0, s32 a1, void* a2, void* a3);
// The object a seeking agent of kind 0x10 keeps at 0xC2C: a method table, and at 0x618 what
// func_001A8820 tests a request's argument against.
typedef void (*ChildFn)(void* self);
struct SeekPartner {
    ChildFn* vtbl;
    u8 pad04[0x618 - 0x04];
    void* p618;
};
void LeaveAgentState(void* self);
extern s32 g_buttonCodeFlags;
s32 IsPadSelectFlagHeld(void* p);
s32 IsAgentRequestBlocked(void* self, s32 a);
void* CreateEffect(s32 kind, s32 zero);
void AddEffectListener(void* node, void* owner);
f32 GetAnimationMarkerTime(void* obj, s32 id);
// Descriptor slot 72 as func_00192880 calls it, with the collider switched from or to.
typedef void (*ActivationHook)(void* self, s32 mode, void* other);
extern u8 g_elementStack[];
void PushStackElement(void* a, void* b);
extern s32 g_padRouting;
extern u8* D_0026F800;
// A record whose 16-bit flags sit at 0xAA.


s32 IsTopCameraController(void* p);
void SkipRemainingSteps(StepSequence* ctx, PadRecord* rec);
void SetStepSequenceState(void* p, s32 n);
void ClearPadPressedBits(PadRecord* rec, s32 n);
s32 IsObjectAttached(void* p);
s32 IsObjectOfKind(void* a, s32 b);
void ReparentObject(void* self, s32 value);
void ReadBufferedString(void* other, void* sub);
void InitCollider(void* self);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value);
extern void ChangeAgentState(SeekingAgent* self, s32 mode, s32 value);
// Notification 0x13: its source and an id.
struct SourceNotice { s32 f_0; u8 pad4[4]; s32 f_8; };
extern void HandleAgentNotification(SeekingAgent* self, s32 code, SourceNotice* req);
extern void SpendReserveUnit(void);
void CopyCollider(SwitchedCollider* self);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 mode);
void PushCameraController(void* mgr, s32 a1, void* a2, SwitchedCollider* self, s32 a4);
void RemoveCameraControllers(void* mgr, s32 a1, s32 a2, s32 a3, SwitchedCollider* self, s32 a5);
void* GetActiveSwitchedCollider(void);
void ActivateSwitchedCollider(void* value);
// The point graph FindPointGraphPath and SnapPointToPointGraph take, at 0x34 of its owner.
struct GraphQueryOwner { u8 head[0x34]; PointGraph graph; };
s32 FindPointGraphPath(PointGraph* graph, Vec02* start, Vec02* goal, s32 maxOut, Vec02* out);
s32 FindPointGraphTriangleWithin(GraphFace* faces, Vec02* p);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist);
void SnapPointToPointGraph(PointGraph* self, Vec02* p, Vec02* out);
f32 RandomFloatInRange(f32 lo, f32 hi);
void ReadBufferedVector3(void* a, void* b);
void ReadPropertyRecords(void* a, void* b);
void TransformPointBetweenFrames(void* a, s32 b, void* c, s32 d);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
extern u8 D_0026A210[];
void SetupScreenElementText(void* self);
s32 IsFontLoaded(s32 k);
void* GetFontById(s32 k);
s32 CollectSegmentSpansInPlaneTree(void* p);
void SyncDataCache(s32 a);
void CopyObjectData(void* self);
void SetListLinkOffset(void* self, s32 value);
void ClearList(void* p);
void RegisterObject(void* self);
void AppendToList(void* table, void* self);
void UnregisterObject(void* self);
void RemoveFromList(void* table, void* self);
extern s32 g_menuChoiceLabels[];
s32 IsPadSelectFlagHeld(void* p);
void CaptureColliderPose(void);
// func_001EA4B8 takes its float arguments first: the caller then sets $f14 before $a0.
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, Quad16* p, s32 zero);
// An object event, and notification 0x17 that passes its id on.
struct AgentEvent { s32 id; };
struct EventNotice {
    SeekingAgent* self;
    s32 id;
};
s32 HasSpareCount(void* a, void* b);
s32 HandleAgentObjectEvent(void* a, void* b);
extern s32 g_buttonCodeFlags;
extern u8* g_saveData;
// The parameters SpawnEffectsAt is given (word 0x28 set by the caller).
struct EffectSpawnParams { s32 f0, f4, f8, fC; f32 f10, f14; s32 f18, f1C; f32 f20, f24; s32 f28, f2C, f30, f34, f38, f3C; };
void RotateMatrixUpright(void* sub, s32 zero, void* out);
s32 CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, s32 d, f32 fa, f32 fb);
void SpawnEffectsAt(void* a, void* b, s32 c, void* d, void* e, s32 f, s32 g);
void LoadObjectProperties(BaseObject* o, Stream8A* in);
s32 ReadBufferedU16(void* stream);
void* AllocateZeroedFrontMemory(s32 n);
void ReadBufferedVector3(Stream8A* in, void* p);
s32 ReadBufferedU8(Stream8A* in);
void* AllocateFrontMemory(s32 n);
f32 ReadBufferedFloat(Stream8A* in);
s32 ReadBufferedS16(Stream8A* in);
void MeasurePointGraphEdges(PointGraph* m);
void* GetActiveSwitchedCollider(void);
void InitObject(BaseObject* self);
// kind==0x10 loop test at the top (retail tests it with the first slot peeled) and
// keeps one more register (frame 64 bytes as retail, but a different loop shape).

void HandlePlacedObjectNotification(SwitchedCollider* self, s32 kind, void* msg);
void StopSoundRecord(void* self, s32 n);
extern f32 D_0026A700;
extern f32 D_0026A704;
extern f32 D_0026A708;
extern f32 D_0026A70C;
void StopStreamVoice(void);
// NEAR: the frame, calls and branch shape match; the saved registers are swapped (retail keeps the input base in $s2 and the moving "last" pointer in $s3, ours the other way round), which changes 18 lines.

void PushBackMemoryMark(void);
s32* AllocateBackMemory(s32 bytes);
void CopyMemory(void* dst, void* src, s32 bytes);
void PopBackMemoryMark(void);
s32 IsPointPathShortcutBlocked(void* self, s32 a, s32 b);
s32 GetEntryName(s32 v);
void UpdateAgentGoal(SeekingAgent* self);
void SetAgentGoalPoint(SeekingAgent* self, void* p);
s32 IsObjectAttached(void* p);
s32 GetObjectWorldPosition(void* self, s32* arg);
// Up to d spans between two points of the graph (0xE0 bytes for d = 2: two ColliderSpans).
s32 CollectSegmentSpansInPlaneTree(void* a, s32 b, s32 c, s32 d, ColliderSpan* e);
typedef void (*SlotFn)(void* self);
extern u8* g_saveData;
void UpdateCollider(SwitchedCollider* self);
void EmitSwitchedColliderTrailPoints(SwitchedCollider* self);
struct ClampInt {
    static s32 Of(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) return lo;
        if (hi < v) return hi;
        return v;
    }
};
f32 TruncateFloat(f32 x);

void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other);
s32 ConstructSwitchedColliderDefaults(s32 a, s32 b);

f32 D_00269B50[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
ObjectLink D_00269B60[2] = { { 0x20, 0x167, 0x59C }, { 0x20, 0x168, 0x5A0 } };
f32 D_00269B78[11] = { 0.0f, 0.5f, -0.5f, 1.0f, -1.0f, 1.5f, -1.5f, 2.0f, -2.0f, 2.5f, -2.5f };
s32 g_screenOwner = 0;
List_269BA8 g_targetVectors = { 0 };
f32 D_00269BC0[3] = { 1000.0f, 10.0f, 1.0f };
s32 g_activeSwitchedCollider = -1;
EffectSpawnParams D_00269BD0 = { 0x18, -1, 0, 0, 1.0f, 2.0f, 0, 0, 1.0f, 2.0f, 0, 0, 0, 1, 0, 0 };
// Built by the static initialiser (func_001930B8, still assembly below): each as a whole block,
// D_00604700 zero but its last vector, D_00269C10 with its own values. Until that C matches they
// are defined without their initialisers, which leaves them where retail has them: the static in
// .bss, the global with the uninitialised ones at the end of .data.
static Blk05 D_00604700;
Blk05 D_00269C10;
s32 g_switchedColliderCount;
void* g_switchedColliders[16];

void InitBoxCollider(BoxCollider* self)
{
    InitCollider(self);
    self->flags538 |= (u64)0x8000 << 28;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

// A part of a placed object's model (0x70 bytes, drawParts): its centre, radius, group and the
// distances its fade works by.
struct ModelPart {
    Vec02 at;               // 0x00
    f32 radius;             // 0x10
    s32 group;              // 0x14
    u8 pad18[4];
    f32 farFade;            // 0x1C: the distance it fades out by (ComputeCameraDistanceFade)
    f32 nearFade;           // 0x20: and in by, when below farFade (flag60)
    f32 depth;              // 0x24: its sort depth, FLT_MAX for the eye's distance
    u8 pad28[0x34 - 0x28];
    void* f34;              // 0x34: given to func_00126DE8 for the matrix
    void* f38;              // 0x38: an object whose slot 4 adjusts the request
    u8 pad3C[0x60 - 0x3C];
    s32 flag60;             // 0x60: fades in as well
    u8 pad64[0x68 - 0x64];
    void* f68;              // 0x68: a matrix the transform is multiplied by
    u8 pad6C[4];
};

// A part's state (0x28 bytes, partStates): which views see it and its eased alpha.
struct ModelPartState {
    u32 views;              // 0x00: the camera's view bits it is drawn in
    u8 pad04[0x10 - 0x04];
    f32 alpha;              // 0x10: eased toward 1.0, or 0.5 while far
    f32 dist;               // 0x14
    u8 pad18[0x28 - 0x18];
};

// The request queued for a part: the part drawer, the depth and group, the transform and the
// fades, the part's centre, the object and the part.
struct __attribute__((aligned(16))) PartRequest {
    void* callback;         // 0x00: DrawModelPart
    f32 depth;              // 0x04
    s32 group;              // 0x08: the part's, 0xD or 0xE while it fades
    u8 pad0C[4];
    Mat4A m;                // 0x10
    f32 fade;               // 0x50
    f32 fade2;              // 0x54
    u8 pad58[8];
    Vec02 at;               // 0x60
    PlacedObject* owner;    // 0x70
    void* state;            // 0x74: the owner's record at +0x22C
    ModelPart* part;        // 0x78
    ModelPartState* partState;  // 0x7C
};

// One of the two scratchpad transfer buffers (file_1B7968.cpp): the blocks StartToSprChain sent.
struct SprTransfer {
    void* tags;             // 0x00
    s32 base;               // 0x04
    u32 addrs[8];           // 0x08: each block's scratchpad address
    s32 sizes[8];           // 0x28
    s32 count;              // 0x48
    s32 state;              // 0x4C: 2 while its parts are drawn
};

extern s32 D_00274990;
extern SprTransfer D_002748F0[2];

// Block n of the current scratchpad transfer.
struct SprBlock {
    static u32 Of(s32 n)
    {
        return D_002748F0[D_00274990].addrs[n];
    }
};

void DrawModelPart(PartRequest* r);
void BuildMatrixFromRotationAndTranslation(Vec02* pos, Mat02* rot, Mat4A* out);
void StartToSprChain(s32 size, ...);
s32 WaitDmaChannel(void* dma, s32 b, s32 c);
s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
void MultiplyMatrices(Mat4A* out, Mat4A* b, void* in); // stays void: retail returns a value, but declared so func_0018F9D8 differs in registers
void BuildCameraFacingMatrix(void* unused0, Camera* cam, void* unused2, Vec02* pos, Mat4A* m);
void QueueDeferredRequest(PartRequest* r);
void* FillMemory(void* p, s32 value, s32 size);
extern void* g_toSprChannel;
extern f32 g_gameClock[];
extern const Mat4A D_00248400;

void QueueModelPartDraws(PlacedObject* self, Camera* cam)
{
    PartRequest rec;
    s32 i = 0;
    s32 n;
    u32 views = cam->f21C;
    FillMemory(&rec, 0, 0x80);
    n = 0x34;
    rec.callback = (void*)DrawModelPart;
    rec.state = self->sub22C;
    rec.owner = self;
    BuildMatrixFromRotationAndTranslation(&self->v140, &self->m110, &rec.m);
    if (self->drawPartCount <= 0x33) {
        n = self->drawPartCount;
    }
    StartToSprChain(n * 0x70, self->drawParts, n * 0x28, self->partStates, 0, 0);
    while (i < self->drawPartCount) {
        WaitDmaChannel(g_toSprChannel, 0, 0);
        s32 next = i + n;
        D_00274990 = 1 - D_00274990;
        D_002748F0[D_00274990].state = 2;
        s32 rest = self->drawPartCount - next;
        s32 m = 0x34;
        if (rest <= 0x33) {
            m = rest;
        }
        StartToSprChain(m * 0x70, (u8*)self->drawParts + next * 0x70, m * 0x28, (u8*)self->partStates + next * 0x28, 0, 0);
        ModelPart* parts = (ModelPart*)SprBlock::Of(0);
        ModelPartState* states = (ModelPartState*)SprBlock::Of(1);
        for (s32 j = 0; j < n; j++) {
            ModelPartState* st = &states[j];
            if ((st->views & views) != views) {
                continue;
            }
            ModelPart* part = &parts[j];
            u128 ones = Vu0::Ones();
            u128 d = Vu0::Sub(Vu0::Q(part->at), Vu0::Q(cam->f40));
            f32 radius = part->radius;
            u32 signs = Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Scalar(radius)) ^ 0xF0;
            if (signs != 0) {
                continue;
            }
            if (!ComputeCameraDistanceFade(cam, d, &rec.fade, radius, part->farFade)) {
                continue;
            }
            if (part->flag60 != 0) {
                if (part->nearFade < part->farFade) {
                    if (!ComputeCameraDistanceFade(cam, d, &rec.fade2, part->radius, part->nearFade)) {
                        rec.fade2 = 0.0f;
                    }
                } else {
                    rec.fade2 = 1.0f;
                }
            }
            f32 target = 1.0f;
            if (g_gameClock[4] < st->dist) {
                target = 0.5f;
            }
            if (target != st->alpha) {
                ModelPartState* home = (ModelPartState*)((u8*)self->partStates + (j + i) * 0x28);
                f32 a = ApproachValueWithRamp(st->alpha, target, g_gameClock[2], (Quad16*)D_00269B50, 0);
                st->alpha = a;
                home->alpha = a;
            }
            rec.fade *= st->alpha;
            if (rec.fade <= 0.0f) {
                continue;
            }
            rec.part = (ModelPart*)((u8*)self->drawParts + (j + i) * 0x70);
            rec.partState = (ModelPartState*)((u8*)self->partStates + (j + i) * 0x28);
            rec.at = part->at;
            if (part->depth != 3.4028235e+38f) {
                rec.depth = part->depth;
            } else {
                rec.depth = Vu0::ToFloat(Vu0::Dot(d, d));
            }
            rec.group = part->group;
            rec.fade2 *= rec.fade;
            if (rec.fade < 1.0f) {
                switch (rec.group) {
                case 3:
                case 4:
                case 7:
                case 8:
                    rec.group = 0xD;
                    break;
                case 5:
                case 9:
                    rec.group = 0xE;
                    break;
                }
            }
            if (part->f38 != 0) {
                void (*adjust)(void*, PlacedObject*, PartRequest*) = (*(void (***)(void*, PlacedObject*, PartRequest*))part->f38)[4];
                if (adjust != 0) {
                    adjust(part->f38, self, &rec);
                }
            }
            if (part->f68 != 0) {
                Mat4A t;
                MultiplyMatrices(&t, &rec.m, part->f68);
                rec.m = t;
            }
            if (part->f34 != 0) {
                BuildCameraFacingMatrix(self, cam, part->f34, &rec.at, &rec.m);
            }
            QueueDeferredRequest(&rec);
            if (part->f68 != 0 || part->f34 != 0) {
                rec.m = D_00248400;
            }
        }
        i = next;
        n = m;
    }
}

void InitSeekingAgent(SeekingAgent* self)
{
    InitAgent(self);
    self->fBD4 = 0;
    self->fBD0 = 0;
}

void StartSeekingAgent(SeekingAgent* self)
{
    StartAgent(self);
    ResolveObjectLinks(self, 2, D_00269B60);
    self->f5F0 = (void*)ResolveAgentClip(self, 0xEF);
    self->fC38 = ResolveAgentClip(self, 0x16C);
    self->fC3C = ResolveAgentClip(self, 0x16D);
    self->fC40 = ResolveAgentClip(self, 0x16A);
    self->fC44 = ResolveAgentClip(self, 0x16B);
}

void EnterSeekingAgentState(SeekingAgent* self, s32 a1, s32 a2)
{
    s32 a2v = a2;
    switch (self->f724) {
    case 4:
        self->fC28 = 0;
        self->fC10 = 0;
        break;
    case 0x10:
        if (self->fC30 == 4) {
            a2v = self->fC44;
        } else {
            a2v = self->fC3C;
        }
        break;
    case 0xB:
        if (self->fC30 == 4) {
            a2v = self->fC40;
        } else {
            a2v = self->fC38;
        }
        if (self->f720 != 0) {
            RemoveItemKeeperMember(self->f720, self);
        }
        break;
    }
    EnterAgentState(self, a1, a2v);
    s32 kind = self->f724;
    if (kind == 0xB || kind == 0x10) {
        self->fC04 = 0;
    }
}

void LeaveSeekingAgentState(SeekingAgent* self)
{
    LeaveAgentState(self);
    s32 kind = self->f724;
    if (kind != 8) {
        if (kind == 0x10) {
            SeekPartner* child = ((SeekPartner*)self->fC2C);
            if (child != 0) {
                child->vtbl[0x54](child);
            }
        }
    } else {
        if (self->f600 == 1) {
            self->desc05()->m4F(self, 0);
        }
    }
}

void UpdateSeekingAgentGoal(SeekingAgent* self, s32 flag)
{
    s32 tmp[4];

    switch (self->f724) {
    case 7:
        if (flag != 0) {
            s32 i;
            void** slot;
            for (i = 0, slot = self->fC14; i < self->fC10; slot++, i++) {
                void* n = *slot;
                if (IsObjectAttached(n) != 0) {
                    SetAgentGoalPoint(self, (u8*)n + 0x140);
                    break;
                }
            }
        }
        break;
    case 4:
        if (self->f750 == 0) {
            if (self->fC24 != 0) {
                GetObjectWorldPosition(self->fC24, tmp);
                SetAgentGoalPoint(self, tmp);
            } else {
                SetAgentGoalPoint(self, &self->v140);
            }
        } else {
            UpdateAgentGoal(self);
        }
        break;
    case 12:
    case 13:
        if (self->fC28 != 0) {
            GetObjectWorldPosition(self->fC28, tmp);
            SetAgentGoalPoint(self, tmp);
        }
        break;
    default:
        UpdateAgentGoal(self);
        break;
    }
}

void FaceAgentTowardGoalPoint(SeekingAgent* self);
void UpdateAgentState(SeekingAgent* self);
void SetAgentFacingAngles(SeekingAgent* self, f32 a, f32 b);
f32 WrapAngle(f32 x);
f32 ArctangentOfRatio(f32 y, f32 x);
s32 GetObjectWorldRotation(void* self, Vec02* out);

void UpdateSeekingAgentState(SeekingAgent* self)
{
    Vec02 tmp;
    Vec02 second;
    Vec02 third;
    f32 a;

    switch (self->f724) {
    case 7:
        FaceAgentTowardGoalPoint(self);
        break;
    case 2:
        if (self->f754 != 0) {
            UpdateAgentState(self);
            break;
        }
        if (self->fC24 != 0) {
            GetObjectWorldRotation(self->fC24, &tmp);
            a = ArctangentOfRatio(tmp.y, tmp.x);
            SetAgentFacingAngles(self, a, 0.0f);
        } else {
            SwitchedCollider* other = (SwitchedCollider*)GetActiveSwitchedCollider();
            if (other == 0 || other == self) {
                break;
            }
            Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(other->v140), Vu0::Q(self->v140));
            a = ArctangentOfRatio(tmp.y, tmp.x);
            SetAgentFacingAngles(self, a, 0.0f);
        }
        break;
    case 13:
        if (self->fC28 == 0) {
            break;
        }
        GetObjectWorldRotation(self->fC28, &tmp);
        a = ArctangentOfRatio(tmp.y, tmp.x);
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    case 8:
        if (*(void**)((u8*)self->f7E0 + 8) != self->f5F0) {
            break;
        }
        Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)g_camera + 0x40)), Vu0::Q(self->v140));
        a = ArctangentOfRatio(tmp.y, tmp.x);
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    case 11:
    case 16:
        if (self->fC34 == 0) {
            break;
        }
        Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)((u8*)self->fC2C + 0x140)));
        a = ArctangentOfRatio(tmp.y, tmp.x);
        if (self->f724 == 0x10) {
            a = WrapAngle(a + 4.0f);
        } else {
            a = WrapAngle(a + 4.7f);
        }
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    default:
        UpdateAgentState(self);
        break;
    }
}

s32 IsSeekingAgentRequestBlocked(SeekingAgent* self, s32 a1)
{
    if (g_buttonCodeFlags & 1) {
        return 1;
    }
    if (IsPadSelectFlagHeld(self->world) == 0) {
        return IsAgentRequestBlocked(self, a1);
    }
    return 1;
}

s32 AcceptSeekingAgentRequest(SeekingAgent* self, s32* arg)
{
    if (self->desc05()->m4B(self, arg[0])) {
        return 0;
    }
    self->fC34 = 0;
    self->fC30 = arg[0];
    if (arg[0] == 0 && arg[1] != 0) {
        if (IsObjectInPool(((SeekPartner*)self->fC2C)->p618, arg[1])) {
            self->fC34 = 1;
        }
    }
    return AcceptAgentRequest(self, arg);
}

s32 HandleSeekingAgentObjectEvent(SeekingAgent* self, AgentEvent* msg)
{
    EventNotice args;
    if (HasSpareCount(self, msg) != 0 && self->fC34 == 0) {
        self->fA68 = 1;
    } else {
        self->fA68 = 0;
    }
    if (HandleAgentObjectEvent(self, msg) == 0) {
        return 0;
    }
    args.self = self;
    args.id = msg->id;
    self->desc->m0E(self, 0x17, &args);
    return 1;
}

s32 HasAttachedSeekingTarget(SeekingAgent* self)
{
    s32 i;
    if (self->fC28 != 0) {
        for (i = 0; i < self->fC10; i++) {
            Agent* n = (Agent*)self->fC14[i];
            if (IsObjectOfKind(n, 8) != 0) {
                s32 k = n->f724;
                if (k == 0xB) {
                    continue;
                }
                if (IsObjectOfKind(n, 9) == 0 && k == 0xA) {
                    continue;
                }
            }
            if (IsObjectAttached(n) != 0) {
                break;
            }
        }
        if (i < self->fC10) {
            return 1;
        }
        self->fC28 = 0;
    }
    return 0;
}

s32 IsSeekingAgentTargetInRange(void)
{
    return 0;
}

s32 AddSeekingAgentObject(SeekingAgent* self, Agent* item)
{
    if (item != 0 && IsObjectAttached(item) != 0) {
        if (IsObjectOfKind(item, 8) == 0 || item->f724 != 0xB) {
            s32 n = self->fC10;
            if ((u32)n < 4) {
                self->fC14[n] = item;
                self->fC10 = n + 1;
                return 1;
            }
        }
    }
    return 0;
}

void SetSeekingAgentStateTarget(SeekingAgent* self, s32 value)
{
    self->fC28 = (void*)value;
}

void SetSeekingAgentTarget(SeekingAgent* self, s32 value)
{
    self->fC24 = (void*)value;
}

void StartSeekingAgentEffect(SeekingAgent* self, s32 flag, PlacedObject* extra)
{
    StartSwitchedColliderEffect(self, flag, extra);
    if (flag == 0) {
        ChangeAgentState(self, 8, (s32)self->f5F0);
    }
}

// was NEAR: GCC folds the final return 1/return 0 into sltiu/xori; retail keeps li v0,16 + bne and a separate move v0,zero tail

s32 GetSeekingAgentStateKind(SeekingAgent* self)
{
    switch (self->f724) {
    case 0x10: return 1;
    case 0xB: return 2;
    }
    return 0;
}

void HandleSeekingAgentNotification(SeekingAgent* self, s32 code, SourceNotice* req)
{
    HandleAgentNotification(self, code, req);
    if (code == 0x13) {
        if (req->f_0 == (s32)self->f7E0) {
            if (req->f_8 == 0x53A) {
                SpendReserveUnit();
            }
        }
    }
}

u32 GetNeighbourFace(u32 x)
{
    return (x & 1) ? 0 : x;
}

s32 GetNeighbourTriangle(s32 value)
{
    if (value & 1) return value & -2;
    return 0;
}

// A node of the binary tree over the point graph's triangles: a plane (normal and offset) and
// the two sides. A side with its low bit set is a triangle (GetNeighbourTriangle), otherwise
// another node.
struct PlaneNode {
    Vec02 normal;           // 0x00
    f32 offset;             // 0x10
    s32 below;              // 0x14
    s32 above;              // 0x18
};

s32 FindPointGraphTriangle(PlaneNode* node, Vec02* p)
{
    while (node != 0) {
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(*p), Vu0::Q(node->normal))) - node->offset;
        if (d > 1e-4f) {
            s32 t = GetNeighbourTriangle(node->above);
            if (t != 0) {
                return t;
            }
            node = (PlaneNode*)node->above;
        } else {
            s32 t = GetNeighbourTriangle(node->below);
            if (t != 0) {
                return t;
            }
            node = (PlaneNode*)node->below;
        }
    }
    return 0;
}

s32 FindPointGraphTriangleWithin(PlaneNode* node, Vec02* p)
{
    while (node != 0) {
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(*p), Vu0::Q(node->normal))) - node->offset;
        if (!(d < -1.0f)) {
            s32 t;
            if (d > 1.0f) {
                t = GetNeighbourTriangle(node->above);
                if (t != 0) {
                    return t;
                }
                node = (PlaneNode*)node->above;
                continue;
            }
            t = GetNeighbourTriangle(node->above);
            if (t != 0) {
                return t;
            }
            t = FindPointGraphTriangleWithin((PlaneNode*)node->above, p);
            if (t != 0) {
                return t;
            }
        }
        {
            s32 t = GetNeighbourTriangle(node->below);
            if (t != 0) {
                return t;
            }
            node = (PlaneNode*)node->below;
        }
    }
    return 0;
}

s32 ClassifyAgainstUnitRange(f32 value)
{
    if (value > 1.0f) return 0;
    if (value < -1.0f) return 1;
    return 2;
}

// An entry of the tree walk of func_001909F0: a node still to test (0 once a side ends), the
// node whose triangle the part reached (0 when it left the tree) and where along the segment the
// part starts. A part that reached a triangle becomes a span.
struct SegmentWalkEntry {
    PlaneNode* node;
    s32 leaf;
    f32 t;
};

// The point at t along the segment from a to b.
struct SegmentPoint {
    static u128 At(const Vec02& a, const Vec02& b, f32 t)
    {
        return Vu0::MulXSum(Vu0::Q(a), Vu0::Scalar(1.0f - t), Vu0::Q(b), Vu0::Scalar(t));
    }
};

s32 CollectSegmentSpansInPlaneTree(PlaneNode* root, Vec02* a, Vec02* b, s32 max, ColliderSpan* spans)
{
    SegmentWalkEntry cur;
    SegmentWalkEntry stack[32];
    SegmentWalkEntry* top;
    ColliderSpan* span;
    ColliderSpan* last;

    span = spans;
    last = 0;
    top = stack;
    cur.node = root;
    cur.leaf = 0;
    cur.t = 0.0f;
    top->node = 0;
    top->leaf = 0;
    top->t = 1.0f;
    for (;;) {
        while (cur.node == 0) {
            if (cur.leaf != 0) {
                if (last != 0 && cur.t == last->time[1]) {
                    Vu0::Q(last->q[1]) = SegmentPoint::At(*a, *b, top->t);
                    last->time[1] = top->t;
                } else {
                    if (span - spans >= max) {
                        return max;
                    }
                    last = span++;
                    last->f48 = 3;
                    Vu0::Q(last->q[0]) = SegmentPoint::At(*a, *b, cur.t);
                    Vu0::Q(last->q[1]) = SegmentPoint::At(*a, *b, top->t);
                    last->time[0] = cur.t;
                    last->time[1] = top->t;
                }
            }
            if (top <= stack) {
                return span - spans;
            }
            cur = *top;
            top--;
        }
        f32 d0 = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(*a), Vu0::Q(cur.node->normal))) - cur.node->offset;
        f32 d1 = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(*b), Vu0::Q(cur.node->normal))) - cur.node->offset;
        s32 c0 = ClassifyAgainstUnitRange(d0);
        s32 c1 = ClassifyAgainstUnitRange(d1);
        if ((c0 == 1 && c1 != 0) || (c1 == 1 && c0 != 0)) {
            cur.leaf = (s32)cur.node;
            cur.node = (PlaneNode*)GetNeighbourFace(cur.node->below);
        } else if ((c0 == 0 && c1 != 1) || (c1 == 0 && c0 != 1)) {
            if (GetNeighbourTriangle(cur.node->above) != 0) {
                cur.leaf = (s32)cur.node;
                cur.node = 0;
            } else {
                cur.node = (PlaneNode*)cur.node->above;
                cur.leaf = 0;
            }
        } else if (c0 == 2 && c1 == 2) {
            cur.leaf = (s32)cur.node;
            cur.node = (PlaneNode*)GetNeighbourFace(cur.node->below);
        } else {
            f32 cut = d0 / (d0 - d1);
            f32 e0 = d1 * cur.t + (1.0f - cur.t) * d0;
            f32 e1 = d1 * top->t + (1.0f - top->t) * d0;
            if (cur.t < cut && cut < top->t) {
                top++;
                top->t = cut;
                if (e0 <= 0.0f) {
                    if (GetNeighbourTriangle(cur.node->above) != 0) {
                        top->leaf = (s32)cur.node;
                        top->node = 0;
                    } else {
                        top->node = (PlaneNode*)cur.node->above;
                        top->leaf = 0;
                    }
                } else {
                    top->leaf = (s32)cur.node;
                    top->node = (PlaneNode*)GetNeighbourFace(cur.node->below);
                }
            }
            if (e0 < 0.0f || (e0 == 0.0f && e1 <= 0.0f)) {
                cur.leaf = (s32)cur.node;
                cur.node = (PlaneNode*)GetNeighbourFace(cur.node->below);
            } else {
                if (GetNeighbourTriangle(cur.node->above) != 0) {
                    cur.leaf = (s32)cur.node;
                    cur.node = 0;
                } else {
                    cur.node = (PlaneNode*)cur.node->above;
                    cur.leaf = 0;
                }
            }
        }
    }
}

s32 IsPointPathShortcutBlocked(void* a, s32 b, s32 c)
{
    ColliderSpan out[2];
    switch (CollectSegmentSpansInPlaneTree(a, b, c, 2, out)) {
    case 0:
        return 1;
    case 1:
        if (out[0].time[0] == 0.0f && out[0].time[1] == 1.0f) {
            return 0;
        }
        return 1;
    case 2:
        return 1;
    }
    return 1;
}

s32 GetPointGraphItemIndex(PointGraph* p, s32 x) { return (x - (s32)p->points) >> 5; }

s32* AllocateZeroedBackMemory(s32 bytes);

struct SearchLink {
    GraphPoint* a;
    GraphPoint* b;
    f32 length;
};

struct SearchNode {
    GraphPoint* point;
    f32 score;
    f32 cost;
    SearchNode* parent;
    s32 depth;
    SearchNode* next;
};

// Whether a point's seen flag was set, setting it.
static inline s32 Test(s32* slot)
{
    if (*slot == 0) {
        *slot = 1;
        return 0;
    }
    return 1;
}

static inline s32 WasSearched(PointGraph* graph, s32* seen, GraphPoint* p, GraphPoint* goal)
{
    if (p == goal) return 0;
    return Test(&seen[GetPointGraphItemIndex(graph, (s32)p)]);
}

// The shortest path through the point graph from one point to another (A*: the open list kept
// sorted by cost plus straight distance), written back to front into outPath.
void SearchPointGraph(PointGraph* graph, GraphPoint* from, GraphPoint* goal, s32 unused, s32* outCount, GraphPoint** outPath)
{
    SearchNode start;
    SearchNode* open;
    PushBackMemoryMark();
    s32* seen = AllocateZeroedBackMemory(graph->pointCount << 2);
    open = 0;
    SearchNode* cur = &start;
    outPath[0] = from;
    start.point = from;
    start.cost = 0.0f;
    start.parent = 0;
    start.depth = 1;
    u128 d = Vu0::Sub(Vu0::Q(*(Vec02*)from), Vu0::Q(*(Vec02*)goal));
    start.score = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
    if (from != goal) {
        do {
            GraphPoint* here = cur->point;
            for (s32 i = 0; i < here->linkCount; i++) {
                SearchLink* link = (SearchLink*)here->links[i];
                GraphPoint* other = link->a;
                if (other == here) other = link->b;
                if (WasSearched(graph, seen, other, goal)) continue;
                SearchNode* node = (SearchNode*)AllocateBackMemory(sizeof(SearchNode));
                node->point = other;
                f32 cost = cur->cost + link->length;
                node->cost = cost;
                u128 e = Vu0::Sub(Vu0::Q(*(Vec02*)here), Vu0::Q(*(Vec02*)goal));
                node->parent = cur;
                node->score = cost + Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(e, e)));
                node->depth = cur->depth + 1;
                SearchNode** pp = &open;
                SearchNode* c = open;
                while (c != 0 && !(node->score < c->score)) {
                    pp = &c->next;
                    c = c->next;
                }
                node->next = c;
                *pp = node;
            }
            cur = open;
            if (cur == 0) break;
            open = cur->next;
        } while (cur->point != goal);
    }
    if (cur != 0) {
        *outCount = cur->depth;
        while (cur != 0) {
            outPath[cur->depth - 1] = cur->point;
            cur = cur->parent;
        }
    } else {
        *outCount = 0;
    }
    PopBackMemoryMark();
}

void SimplifyPointPath(void* a0, s32* a1, s32* a2)
{
    s32 count;
    s32* out;
    s32* end;
    s32* last;
    s32* base;
    s32* q;
    s32* p;
    s32 n;
    s32 val;

    last = a2;
    base = a2;
    p = base + 1;
    q = base + 2;
    PushBackMemoryMark();
    n = *a1;
    out = AllocateBackMemory(n << 2);
    end = base + n;
    out[0] = base[0];
    count = 1;
    if (q < end) {
        do {
            if (IsPointPathShortcutBlocked(a0, *last, *q) != 0) {
                val = *p;
                last = p;
                p = q;
                q++;
                out[count] = val;
                count++;
            } else {
                p = q;
                q++;
            }
        } while (q < end);
    }
    out[count] = base[n - 1];
    count++;
    if (count < n) {
        if (count >= 3) {
            SimplifyPointPath(a0, &count, out);
        }
    }
    CopyMemory(base, out, count * 4);
    *a1 = count;
    PopBackMemoryMark();
}

// The temporary start and goal points FindPointGraphPath links into the graph: a GraphPoint's
// layout, with its position.
struct PathNode;

struct PathLink {
    PathNode* a;
    PathNode* b;
    f32 length;
};

struct PathNode {
    Vec02 pos;
    s32 count;
    PathLink** links;
    u8 pad18[8];
};

static inline s32 MinOfCounts(s32 a, s32 b)
{
    return a < b ? a : b;
}

// A path from start to goal over the point graph, at most maxOut points written to out; its
// count is returned. Each end is placed in its triangle (snapped onto the graph when outside
// it); a shared triangle is the straight path. Otherwise the start becomes a temporary point
// linked to its triangle's corners, the goal one its triangle's corners link to (their counts
// raised for the search and lowered after), and the search's path is simplified.
s32 FindPointGraphPath(PointGraph* graph, Vec02* start, Vec02* goal, s32 maxOut, Vec02* out)
{
    Vec02 a;
    Vec02 b;
    PathNode* faces = (PathNode*)graph->faces;
    PathNode** tri0 = (PathNode**)FindPointGraphTriangle((PlaneNode*)faces, start);
    if (tri0 != 0) {
        a = *start;
    } else {
        SnapPointToPointGraph(graph, start, &a);
        tri0 = (PathNode**)FindPointGraphTriangleWithin((PlaneNode*)faces, &a);
    }
    PathNode** tri1 = (PathNode**)FindPointGraphTriangle((PlaneNode*)faces, goal);
    if (tri1 != 0) {
        b = *goal;
    } else {
        SnapPointToPointGraph(graph, goal, &b);
        tri1 = (PathNode**)FindPointGraphTriangleWithin((PlaneNode*)faces, &b);
    }
    if (tri0 == tri1) {
        out[0] = a;
        out[1] = b;
        return 2;
    }
    PushBackMemoryMark();
    PathNode** path = (PathNode**)AllocateBackMemory(0x200);
    PathNode node1;
    PathLink links1[3];
    PathNode node2;
    PathLink links2[3];
    s32 count;
    PathNode* n1 = &node1;
    node1.pos = a;
    node1.count = 3;
    node1.links = (PathLink**)AllocateBackMemory(12);
    for (s32 i = 0; i < 3; i++) {
        PathLink* l = &links1[i];
        l->a = n1;
        PathNode* c = tri0[i];
        l->b = c;
        u128 d = Vu0::Sub(Vu0::Q(n1->pos), Vu0::Q(c->pos));
        Vu0::StoreX(l->length, Vu0::Sqrt(Vu0::DotXY(d, d)));
        node1.links[i] = l;
    }
    node2.pos = b;
    node2.count = 0;
    node2.links = 0;
    // One counter for both walks of the goal's corners (retail's t0 in each).
    s32 k;
    for (k = 0; k < 3; k++) {
        PathLink* l = &links2[k];
        PathNode* corner = tri1[k];
        l->a = corner;
        l->b = &node2;
        u128 d = Vu0::Sub(Vu0::Q(corner->pos), Vu0::Q(node2.pos));
        Vu0::StoreX(l->length, Vu0::Sqrt(Vu0::DotXY(d, d)));
        corner->links[corner->count++] = l;
    }
    SearchPointGraph(graph, (GraphPoint*)&node1, (GraphPoint*)&node2, 0x80, &count, (GraphPoint**)path);
    if (count >= 3) {
        SimplifyPointPath(graph->faces, &count, (s32*)path);
    }
    s32 n = MinOfCounts(maxOut, count);
    for (s32 i = 0; i < n; i++) {
        out[i] = path[i]->pos;
    }
    for (k = 0; k < 3; k++) {
        tri1[k]->count--;
    }
    PopBackMemoryMark();
    return n;
}

// p, when it is outside every face, moved to the nearest point of the nearest link (each link
// taken at p's height); otherwise p itself. The weighted sum's operands are formed weight, end,
// weight, end, the order retail's stores and loads keep (docs/TOOLCHAIN.md, "A weighted sum's
// operands in insn order").
void SnapPointToPointGraph(PointGraph* self, Vec02* p, Vec02* out)
{
    if (FindPointGraphTriangleWithin(self->faces, p) != 0) {
        *out = *p;
        return;
    }
    f32 best = 3.4028235e38f;
    f32 bestT = -1.0f;
    GraphPoint** nearest = 0;
    for (s32 i = 0; i < self->nA; i++) {
        GraphPoint** link = (GraphPoint**)(self->links + i * 12);
        Vec02 a = *(Vec02*)link[0];
        Vec02 b = *(Vec02*)link[1];
        f32 t;
        f32 d;
        a.z = p->z;
        b.z = p->z;
        MeasurePointToSegment(p, &a, &b, &t, &d);
        if (d < best) {
            bestT = t;
            nearest = link;
            best = d;
        }
    }
    Vec02* b = (Vec02*)nearest[1];
    Vec02* a = (Vec02*)nearest[0];
    Vu0::Vec s = Vu0::Vec::Scalar(1.0f - bestT);
    Vu0::Vec pa = Vu0::Vec::Of(*a);
    Vu0::Vec t = Vu0::Vec::Scalar(bestT);
    Vu0::Vec pb = Vu0::Vec::Of(*b);
    Vu0::Q(*out) = Vu0::MulXSum(pa, s, pb, t).q;
}

void LoadPointGraph(PointGraphObject* o, Stream8A* in)
{
    PointGraph* m = &o->graph;
    s32 i;
    s32 j;
    LoadObjectProperties(o, in);
    i = 0;
    o->graph.pointCount = ReadBufferedU16(in);
    m->points = (GraphPoint*)AllocateZeroedFrontMemory(o->graph.pointCount << 5);
    m->nA = ReadBufferedU16(in);
    m->linkCount = ReadBufferedU16(in) + m->nA;
    m->links = (u8*)AllocateZeroedFrontMemory(m->linkCount * 12);
    m->triCount = ReadBufferedU16(in);
    m->tris = (u8*)AllocateZeroedFrontMemory(m->triCount * 12);
    if (o->graph.pointCount > 0) {
        do {
            GraphPoint* v = (GraphPoint*)((u8*)m->points + (i << 5));
            s32 k = i + 1;
            j = 0;
            ReadBufferedVector3(in, v);
            v->linkCount = ReadBufferedU8(in);
            v->links = (GraphLink**)AllocateFrontMemory((v->linkCount + 1) << 2);
            if (v->linkCount > 0) {
                do {
                    v->links[j] = (GraphLink*)(m->links + ReadBufferedU16(in) * 12);
                    j++;
                } while (j < v->linkCount);
            }
            i = k;
        } while (i < m->pointCount);
    }
    {
        s32 e;
        for (e = 0; e < m->linkCount; e++) {
            GraphPoint** p = (GraphPoint**)(m->links + e * 12);
            j = 1;
            do {
                j--;
                *p = (GraphPoint*)((u8*)m->points + (ReadBufferedU16(in) << 5));
                p++;
            } while (j >= 0);
        }
        for (e = 0; e < m->triCount; e++) {
            GraphPoint** p = (GraphPoint**)(m->tris + e * 12);
            j = 2;
            do {
                j--;
                *p = (GraphPoint*)((u8*)m->points + (ReadBufferedU16(in) << 5));
                p++;
            } while (j >= 0);
        }
    }
    m->faceCount = ReadBufferedU16(in);
    m->faces = (GraphFace*)AllocateZeroedFrontMemory(m->faceCount << 5);
    for (s32 e = 0; e < m->faceCount; e++) {
        s32 a;
        GraphFace* f = (GraphFace*)((u8*)m->faces + (e << 5));
        ReadBufferedVector3(in, f);
        f->f10 = ReadBufferedFloat(in);
        a = ReadBufferedS16(in);
        if (a == -1) {
            f->neighbourA = 0;
        } else if (a >= 0) {
            f->neighbourA = (u8*)m->faces + (a << 5);
        } else {
            a += 2;
            a = -a;
            f->neighbourA = (void*)((u32)(m->tris + a * 12) | 1);
        }
        a = ReadBufferedS16(in);
        if (a == -1) {
            f->neighbourB = 0;
        } else if (a >= 0) {
            f->neighbourB = (u8*)m->faces + (a << 5);
        } else {
            a += 2;
            a = -a;
            f->neighbourB = (void*)((u32)(m->tris + a * 12) | 1);
        }
    }
    MeasurePointGraphEdges(m);
}

ASM_FUNC(func_001919F8);

s32 FindOwnerGraphPath(GraphQueryOwner* self, Vec02* start, Vec02* goal, s32 maxOut, Vec02* out)
{
    return FindPointGraphPath(&self->graph, start, goal, maxOut, out);
}

void SnapPointToOwnerGraph(GraphQueryOwner* self, Vec02* p, Vec02* out)
{
    SnapPointToPointGraph(&self->graph, p, out);
}

void TestOwnerGraphSpan(GraphQueryOwner* self)
{
    CollectSegmentSpansInPlaneTree(self->graph.faces);
}

INCLUDE_ASM(func_00191AC8);

// A random point on the graph's triangles: one picked by its area, then a point inside it.
void PickRandomPointOnPointGraph(PointGraphObject* self, Vec02* out)
{
    Vec02 e1;
    Vec02 e2;
    GraphTri* t;
    f32 total = 0.0f;
    s32 i;
    for (i = 0; i < self->graph.triCount; i++) {
        t = (GraphTri*)(self->graph.tris + i * 12);
        Vu0::Q(e1) = Vu0::Sub(Vu0::Vec::Of(*t->corner[1]), Vu0::Vec::Of(*t->corner[0])).q;
        Vu0::Q(e2) = Vu0::Sub(Vu0::Vec::Of(*t->corner[2]), Vu0::Vec::Of(*t->corner[0])).q;
        total += e1.x * e2.y - e1.y * e2.x;
    }
    f32 r = RandomFloatInRange(0.0f, total);
    for (i = 0; i < self->graph.triCount; i++) {
        t = (GraphTri*)(self->graph.tris + i * 12);
        Vu0::Q(e1) = Vu0::Sub(Vu0::Vec::Of(*t->corner[1]), Vu0::Vec::Of(*t->corner[0])).q;
        Vu0::Q(e2) = Vu0::Sub(Vu0::Vec::Of(*t->corner[2]), Vu0::Vec::Of(*t->corner[0])).q;
        r -= e1.x * e2.y - e1.y * e2.x;
        if (r < 0.0f) {
            break;
        }
    }
    f32 u = RandomFloatInRange(0.0f, 1.0f);
    f32 v = RandomFloatInRange(0.0f, 1.0f);
    if (1.0f < u + v) {
        u = 1.0f - u;
        v = 1.0f - v;
    }
    Vu0::Vec su = Vu0::Vec::Scalar(u);
    Vu0::Vec a = Vu0::Vec::Of(*t->corner[0]);
    Vu0::Vec sv = Vu0::Vec::Scalar(v);
    Vu0::Vec b = Vu0::Vec::Of(*t->corner[1]);
    Vu0::Vec sw = Vu0::Vec::Scalar(1.0f - u - v);
    Vu0::Vec c = Vu0::Vec::Of(*t->corner[2]);
    Vu0::Q(*out) = Vu0::MulXSum3(a, su, b, sv, c, sw).q;
}

void SetScreenOwner(s32 value)
{
    if (g_screenOwner != value) {
        SyncDataCache(0);
        g_screenOwner = value;
    }
}

void ClearScreenOwner(void)
{
    g_screenOwner = 0;
}

void SetTargetVectorListLinkOffset()
{
    SetListLinkOffset(&g_targetVectors.list, 0x38);
}

void ClearTargetVectorList(void)
{
    ClearList(&g_targetVectors.list);
}

void InitTargetVector(TargetVector* self)
{
    InitObject(self);
    self->q40 = *(TargetVectorQuad*)&g_unitXVector;
    self->f54 = 9;
    self->f50 = 8;
    self->f58 = -1;
    self->f5C = 3.40282347e+38f;
    self->targetId = -1;
}

void RegisterTargetVector(TargetVector* self)
{
    RegisterObject(self);
    AppendToList(&g_targetVectors.list, self);
}

void UnregisterTargetVector(TargetVector* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetVectors.list, self);
}

void StartTargetVector(TargetVector* self)
{
    StartObject(self);
    if (self->targetId != -1) {
        self->target = FindFirstObjectById(self->world, 4, self->targetId, self);
    }
}

void CopyTargetVector(TargetVector* self)
{
    PathCurveKeptBits tmp;
    tmp = self->keep;
    CopyObjectData(self);
    self->keep = tmp;
}

void LoadPointObject(PointObject* self, void* other)
{
    ReadBufferedVector3(other, &self->pos);
    ReadPropertyRecords(self, other);
}

void ConvertPositionToWorld(BaseObject* self, s32 arg)
{
    TransformPointBetweenFrames((void*)self->parent, 0, (u8*)self + 0x40, arg);
}

void ReparentPointObject(PointObject* self, s32 value)
{
    void* sub = &self->pos;
    TransformPointBetweenFrames(self->parent, value, sub, sub);
    ReparentObject(self, value);
}

s32 ConvertPointObjectPosition(PointObject* self, void* other)
{
    void* p = &self->pos;
    TransformPointBetweenFrames(other, 0, p, p);
}

void LoadTextPointObject(TextPointObject* self, void* other)
{
    LoadPointObject(self, other);
    ReadBufferedString(other, &self->text);
}

void ResetTextPointToHalf(TextPointObject* self)
{
    self->f54 = 0.5f;
    self->f58 = 0.5f;
}

void InitSwitchedCollider(SwitchedCollider* self)
{
    InitCollider(self);
    self->f598 = self;
    self->f580 = 1;
    SetSwitchedColliderEnabled(self, 1);
}

void CopySwitchedCollider(SwitchedCollider* self)
{
    CopyCollider(self);
    if (self->f550 != 0) {
        return;
    }
    self->f550 = 1;
    SetSwitchedColliderEnabled(self, 0);
}

void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    switch (kind) {
    case 0xB:
        StopSoundRecord(self->f574, 0);
        break;
    case 0x10: {
        s32 i;
        for (i = 0; i < self->f5D0; i++) {
            if (self->f5AC[i] == msg) {
                self->f5AC[i] = 0;
                break;
            }
        }
        break;
    }
    }
}

void HandleSwitchedColliderActivation(SwitchedCollider* self, s32 mode)
{
    if (mode != 0) {
        self->v560 = self->v140;
        PushCameraController(g_camera, 1, &g_camera->ctl520, self, 0);
        return;
    }
    for (s32 i = 1; i < 7; i++) {
        RemoveCameraControllers(g_camera, 5, i, 0, self, 0);
    }
}

void CaptureSwitchedColliderPose(SwitchedCollider* self, u8* out, f32 a)
{
    CaptureColliderPose();
    if (self->f554 != 0) {
        *(Quad16*)(out + 0x10) = *(Quad16*)((u8*)self + 0x560);
        return;
    }
    Camera* base = g_camera;
    if (base->f224 == 0) {
        *(f32*)(out + 0x18) = ApproachValueWithRamp(self->v560.z, self->v140.z, a, (Quad16*)D_00269BC0, 0);
    }
    *(Quad16*)((u8*)self + 0x560) = *(Quad16*)(out + 0x10);
}

s32 IsSwitchedColliderCameraFree(void)
{
    return 1;
}

void ActivateSwitchedColliderUnlessActive(void* self)
{
    if (self != GetActiveSwitchedCollider()) ActivateSwitchedCollider(self);
}

s32 IsSwitchedColliderRequestBlocked(SwitchedCollider* self)
{
    if ((g_buttonCodeFlags & 1) || IsPadSelectFlagHeld(self->world)) return 1;
    return 0;
}

s32 AcceptSwitchedColliderRequest(SwitchedCollider* self)
{
    return 0;
}

s32 HasSwitchedColliderAcceptedRequest(void)
{
    return 0;
}

void StoreSwitchedColliderAccepted(SwitchedCollider* self, s32* out)
{
    *out = ((s32 (*)(SwitchedCollider*, s32*))self->desc05()->m4D)(self, out);
}

void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other)
{
    switch (mode) {
    case 0:
        if (self->f5F0 == 0)
            return;
        {
            Effect* n = (Effect*)CreateEffect(0x1A, 0);
            self->f5AC[0] = n;
            self->f5D0 = 1;
            if (n != 0) {
                void (*init)(Effect* self, void* pos, f32 scale, s32 flags) = n->vt->m00;
                init(n, (u8*)other + 0x140, 1.0f, 0);
                AddEffectListener(n, self);
                f32 r = GetAnimationMarkerTime(self->f5F0, 0x13F);
                n->life = r;
                n->i20 = self->f59C;
                n->vC0 = other->world->gravity;
                n->p134 = other;
            }
        }
        self->desc05()->m4F(self, 1);
        break;
    case 1:
        self->desc05()->m4F(self, 2);
        break;
    }
}

ASM_FUNC(func_001925C0);

void* GetActiveSwitchedCollider()
{
    s32 i = g_activeSwitchedCollider;
    if (i < 0) return 0;
    return g_switchedColliders[i];
}

void* GetCurrentSwitchedCollider(void)
{
    void* r = GetActiveSwitchedCollider();
    if (r == 0) {
        Player* q = g_player;
        if (q != 0) {
            s32 t = q->f550;
            if (t != 0) r = q;
        }
    }
    if (r == 0 && g_switchedColliderCount != 0) {
        r = g_switchedColliders[0];
    }
    return r;
}

s32 FindSwitchedColliderIndex(s32 key)
{
    s32 i;
    for (i = 0; i < g_switchedColliderCount; i++) {
        if (key == (s32)g_switchedColliders[i]) {
            return i;
        }
    }
    return -1;
}

void AddToSwitchedColliderList(SwitchedCollider* self)
{
    if (self->f550 == 0) return;
    if (self->parent != 0) return;
    if (!IsObjectAttached()) return;
    if (FindSwitchedColliderIndex(self) >= 0) return;
    s32 n = g_switchedColliderCount;
    if ((u32)n < 16) {
        g_switchedColliders[n] = self;
        g_switchedColliderCount = n + 1;
    } else if (self->id == 5 && g_player == 0) {
        g_switchedColliders[0] = self;
    }
}

void RemoveFromSwitchedColliderList(void* value)
{
    s32 idx = FindSwitchedColliderIndex(value);
    if (idx < 0) return;
    if (idx == g_activeSwitchedCollider) ActivateSwitchedColliderIndex(-1);
    s32 n = g_switchedColliderCount;
    MoveMemory(&g_switchedColliders[idx], &g_switchedColliders[idx + 1], (n - idx) * 4 - 4);
    if (idx < g_activeSwitchedCollider) g_activeSwitchedCollider = g_activeSwitchedCollider - 1;
    g_switchedColliderCount = g_switchedColliderCount - 1;
}

void RegisterSwitchedCollider(SwitchedCollider* self)
{
    RegisterCollider(self);
    AddToSwitchedColliderList(self);
}

void UnregisterSwitchedCollider(SwitchedCollider* self)
{
    UnregisterCollider(self);
    RemoveFromSwitchedColliderList(self);
}

void ActivateSwitchedColliderIndex(s32 index)
{
    if (index == g_activeSwitchedCollider)
        return;
    if (g_activeSwitchedCollider >= 0) {
        u64 mask = (u64)(s64)-8193;
        mask = (mask << 16) | 0xFFFF;
        mask = (mask << 16) | 0xFFFF;
        SwitchedCollider** slot = (SwitchedCollider**)&g_switchedColliders[g_activeSwitchedCollider];
        (*slot)->flags538 &= mask;
        ActivationHook* vt = (ActivationHook*)(*slot)->desc;
        SwitchedCollider* next = index >= 0 ? (SwitchedCollider*)g_switchedColliders[index] : 0;
        vt[0x130 / 4]((*slot), 0, next);
    }
    s32 old = g_activeSwitchedCollider;
    g_activeSwitchedCollider = index;
    if (index >= 0) {
        SwitchedCollider** slot = (SwitchedCollider**)&g_switchedColliders[index];
        (*slot)->flags538 |= 1ULL << 45;
        ActivationHook* vt = (ActivationHook*)(*slot)->desc;
        SwitchedCollider* prev = old >= 0 ? (SwitchedCollider*)g_switchedColliders[old] : 0;
        vt[0x130 / 4]((*slot), 1, prev);
    }
}

LINKER_REMNANT(func_00192988);

void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value)
{
    if (self->f550 == value) return;
    self->f550 = value;
    if (value) AddToSwitchedColliderList(self);
    else RemoveFromSwitchedColliderList(self);
}

void ActivateSwitchedCollider(void* value)
{
    ActivateSwitchedColliderIndex(FindSwitchedColliderIndex(value));
}

void* GetActiveSwitchedColliderData()
{
    void* r = GetActiveSwitchedCollider();
    if (r) return (u8*)r + 0x580;
    return &D_00604700;
}

void GetSwitchedColliderInteractFlags(s32, s32, InteractFlags* out)
{
    out->b = 1;
    out->a = 1;
}

void ShowTypedTextCaptionBox(SwitchedCollider* self, u32 value)
{
    T217D_440* block = &g_typedTextCaptionBox;
    ((T217D_Word*)&block->child)->v = value;
    PushStackElement(g_elementStack, &g_typedTextCaptionBox);
}

void HandleStepSequenceSkipButtons(void* self, PadRecord* rec)
{
    if (IsTopCameraController(&g_camera->ctl454) != 0)
        return;
    PadRecord* a1 = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
    StepSequence* ctx = D_0027051C;
    if (ctx != 0 && ctx->state2D4 == 3 && ctx->f32C == 0 && (a1->flags & 0xC) != 0
        && *(s32*)ctx->target304 != 0) {
        SkipRemainingSteps(ctx, a1);
    } else if ((rec->flags & 0xC) != 0 && D_0026F800 != 0) {
        SetStepSequenceState(D_0026F800, 1);
    }
    ClearPadPressedBits(rec, 0xC);
}

void UpdateSwitchedCollider(SwitchedCollider* self)
{
    UpdateCollider(self);

    u8* ctx = g_saveData;
    s32 cnt = *(s32*)(ctx + 0x19E4);
    s32 lim = ClampInt::Of(cnt, 0, 2);

    for (s32 i = 0; i < 3; i++) {
        void* e = self->f588[i];
        if ((self->flags & ((u64)1 << 32)) == 0 && i == lim) {
            if (e != 0) {
                (*(SlotFn**)e)[6](e);
            }
        } else {
            if (e != 0) {
                (*(SlotFn**)e)[7](e);
            }
        }
    }

    if (self->f600 == 1 || self->f600 == 3) {
        EmitSwitchedColliderTrailPoints(self);
    }
}

void FinishSwitchedCollider(SwitchedCollider* self)
{
    s32 flags = g_buttonCodeFlags & 2;
    if (flags == 0) {
        u8* g = g_saveData;
        s32 n = *(s32*)(g + 0x19E4) - 1;
        *(s32*)(g + 0x19E4) = flags < n ? n : 0;
    }

    PlacedObject* s1 = self->f604;
    if (s1 != 0) {
        Mat02 tmp;
        s1->desc->m02(s1);
        s1->desc->m15(s1, 0);
        RotateMatrixUpright(((u8*)self->f584) + 0x110, 0, &tmp);
        s1->desc02()->m1D(s1, (Vec02*)(((u8*)self->f584) + 0x140));
        s1->desc02()->m1E(s1, &tmp);
        s1->desc02()->m20(s1, (Vec02*)&D_00248D30);
        s1->desc02()->m21(s1, (Vec02*)&D_00248D30);
        void* r = (void*)FindFirstObjectById(self->world, 1, 0x18C, s1);
        if (r != 0) {
            CreateAnimationPlayerWithoutPresetTargets(r, s1, 0, 0, 0.0f, 1.0f);
        }
    } else {
        s32 v = (s32)self->f588[1];
        if (v != 0) {
            u8* g = (u8*)&D_00269BD0;
            *(s32*)(g + 0x28) = v;
            SpawnEffectsAt(((u8*)self->f584) + 0x140, (void*)&g_unitZVector, 1, g, &D_00269C10, 0, 0);
        }
    }
}

// A trail node of a switched collider's list at 0x5AC: when it was laid and the segment it spans.
struct TrailNode {
    u8 pad00[0x18];
    f32 time;               // 0x18
    u8 pad1C[0x80 - 0x1C];
    Vec02 v80;              // 0x80
    Vec02 v90;              // 0x90
};

// Sends the sink a message for each point along the segments to the attached node (or along
// the trail), one every 5 units. The segment loop's size decides what loop.c moves out: with
// the vectors as Vu0::Vec values and the walk a `for` from step to 1.0, pass 1 sees 82 insns and
// moves only the guard's 1.0 (jump.c's copy, life 2), pass 2 sees 79 and moves 0.0001; 5.0
// stays, as retail's (docs/TOOLCHAIN.md, "Loops").
void EmitSwitchedColliderTrailPoints(SwitchedCollider* self)
{
    Vec02 from[9];
    Vec02 to[9];
    SlotMessage msg;
    Vec02 a;
    Vec02 b;
    BaseObject* sink = *(BaseObject**)((u8*)self->world + 0x1D5C);
    s32 count;
    if (sink != 0) {
        PlacedObject* target = 0;
        void** nodes = (void**)((u8*)self + 0x59C);
        for (u32 k = 0; k < 4; k++) {
            if (nodes[k] != 0 && IsObjectAttached(nodes[k]) != 0) {
                target = (PlacedObject*)nodes[k];
                break;
            }
        }
        if (target != 0) {
            count = 1;
            s32 still = 0;
            if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f) {
                still = 1;
            }
            if (still) {
                from[0] = target->v140;
            } else {
                from[0] = (*(Vec02*)((u8*)self + 0x5E0));
            }
            to[0] = target->v140;
        } else {
            count = 0;
            for (s32 k = 0; k < self->f5D0; k++) {
                TrailNode* n = (TrailNode*)self->f5AC[k];
                if (n != 0 && g_gameClock[1] >= n->time) {
                    from[count] = n->v90;
                    to[count] = n->v80;
                    count++;
                }
            }
        }
        msg.kind = 4;
        for (s32 i = 0; i < count; i++) {
            a = from[i];
            b = to[i];
            f32 len = Vu0::Distance(a, b);
            f32 step;
            if (len < 0.0001f) {
                step = 1.0f;
            } else {
                step = 5.0f / len;
            }
            for (f32 t = step; t < 1.0f; t += step) {
                *(Vu0::Vec*)&msg.vb = Vu0::MulXSum(Vu0::Vec::Of(a), Vu0::Vec::Scalar(1.0f - t), Vu0::Vec::Of(b), Vu0::Vec::Scalar(t));
                sink->desc->m1B(sink, &msg);
            }
            *(Vu0::Vec*)&msg.vb = Vu0::Vec::Of(b);
            sink->desc->m1B(sink, &msg);
            (*(Vec02*)((u8*)self + 0x5E0)) = b;
        }
    }
}

void* GetSwitchedColliderTarget(SwitchedCollider* p)
{
    return p;
}

// The static initialiser, which builds D_00604700 and D_00269C10 (nonmatching/func_001930B8.cpp).
INCLUDE_ASM(func_001930B8);

s32 ConstructSwitchedColliderDefaultsAtStartup(void)
{
    return ConstructSwitchedColliderDefaults(1, 0xFFFF);
}
