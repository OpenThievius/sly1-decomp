// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x18F988 to 0x1921A8 (its .rodata from 0x24B5E0, its .data from 0x269B50): the
// box collider (class 0x49), the seeking agent (class 0x0E), the point graph and its searches, the
// screen owner, the target vectors (class 0x70) and the point objects. It starts at an exact edge
// (movie_player.cpp's end) and could itself be several files. Its end in the code is a choice:
// switched_collider.cpp's .data provably starts at 0x269BC0 (that file says why), and this file's
// last global, g_targetVectors (D_00269BA8, read by UnregisterTargetVector at 0x191FA0), ends
// before it, so any function start from 0x191FD8 to 0x192380 (CaptureSwitchedColliderPose, the
// first reader of 0x269BC0) can begin the next file. The cut is at 0x1921A8, where the switched
// collider's functions begin. Its name is ours, after its largest family, the point graph and its
// searches.
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
#include "object_finder.h"
#include "agent_request.h"
#include "functions/base_object.h"
#include "functions/buffered_stream.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/game_progress.h"
#include "functions/group_marker.h"
#include "functions/matrix.h"
#include "functions/object_pool.h"
#include "functions/object_properties.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/placed_object_model.h"
#include "functions/pooled_object.h"
#include "functions/pose_source.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
struct ColliderSpan;
struct PlaneNode;
struct Vec02;
struct BaseObject;
struct Mat02;
struct Mat4A;
struct DeferredRequest;
struct ItemKeeper;
struct AgentRequest;
struct Agent;

void InitAgent(Agent* self);
void StartAgent(Agent* self);
s32 ResolveAgentClip(Agent* self, s32 id);
void RemoveItemKeeperMember(ItemKeeper* self, Agent* value);
void EnterAgentState(Agent* self, s32 evt, Animation* arg);
struct ObjectPool;
s32 AcceptAgentRequest(Agent* self, AgentRequest* req);
// The object a seeking agent of kind 0x10 keeps at 0xC2C: a method table, and at 0x618 what
// func_001A8820 tests a request's argument against.
typedef void (*ChildFn)(void* self);
struct SeekPartner {
    ChildFn* vtbl;
    u8 pad04[0x618 - 0x04];
    void* p618;
};
void LeaveAgentState(Agent* self, s32 mode);
extern s32 g_buttonCodeFlags;
struct BufferedStream;
s32 IsAgentRequestBlocked(Agent* self, s32 unused1);
extern void ChangeAgentState(Agent* self, s32 state, void* context);
// Notification 0x13: its source and an id.
struct SourceNotice { s32 f_0; u8 pad4[4]; s32 f_8; };
struct AgentNotification;
extern void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg);
// The point graph FindPointGraphPath and SnapPointToPointGraph take, at 0x34 of its owner.
s32 FindPointGraphPath(PointGraph* graph, Vec02* start, Vec02* goal, s32 maxOut, Vec02* out);
s32 FindPointGraphTriangleWithin(PlaneNode* node, Vec02* p);
void SnapPointToPointGraph(PointGraph* self, Vec02* p, Vec02* out);
extern "C" void* CopyBytes(void* dst, void* src, s32 n);
extern "C" void SyncDataCache(s32 a);
// func_001EA4B8 takes its float arguments first: the caller then sets $f14 before $a0.
struct RampProfile;
// An object event, and notification 0x17 that passes its id on.
struct AgentEvent { s32 id; };
struct EventNotice {
    SeekingAgent* self;
    s32 id;
};
struct BufferedStream;
struct AgentHit;
s32 HandleAgentObjectEvent(Agent* self, AgentHit* ev);
extern s32 g_buttonCodeFlags;
void* AllocateZeroedFrontMemory(s32 n);
void* AllocateFrontMemory(s32 n);
void MeasurePointGraphEdges(PointGraph* m);
// NEAR: the frame, calls and branch shape match; the saved registers are swapped (retail keeps the input base in $s2 and the moving "last" pointer in $s3, ours the other way round), which changes 18 lines.

void PushBackMemoryMark(void);
s32* AllocateBackMemory(s32 bytes);
void CopyMemory(void* dst, void* src, u32 size);
void PopBackMemoryMark(void);
s32 IsPointPathShortcutBlocked(void* self, s32 a, s32 b);
void UpdateAgentGoal(Agent* self, s32 flag);
void SetAgentGoalPoint(Agent* self, Vec02* p);
// Up to d spans between two points of the graph (0xE0 bytes for d = 2: two ColliderSpans).
s32 CollectSegmentSpansInPlaneTree(PlaneNode* root, Vec02* a, Vec02* b, s32 max, ColliderSpan* spans);


f32 D_00269B50[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
ObjectLink D_00269B60[2] = { { 0x20, 0x167, 0x59C }, { 0x20, 0x168, 0x5A0 } };
f32 D_00269B78[11] = { 0.0f, 0.5f, -0.5f, 1.0f, -1.0f, 1.5f, -1.5f, 2.0f, -2.0f, 2.5f, -2.5f };
s32 g_screenOwner = 0;
List_269BA8 g_targetVectors = { 0 };

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
    void* cameraFacing;     // 0x34: given to func_00126DE8 for the matrix
    void* hook;             // 0x38: an object whose slot 4 adjusts the request
    u8 pad3C[0x60 - 0x3C];
    s32 flag60;             // 0x60: fades in as well
    u8 pad64[0x68 - 0x64];
    void* matrix;           // 0x68: a matrix the transform is multiplied by
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

// One of the two scratchpad transfer buffers (object_properties.cpp): the blocks StartToSprChain sent.
struct SprTransfer {
    void* tags;             // 0x00
    s32 base;               // 0x04
    u32 addrs[8];           // 0x08: each block's scratchpad address
    s32 sizes[8];           // 0x28
    s32 count;              // 0x48
    s32 state;              // 0x4C: 2 while its parts are drawn
};

extern s32 g_sprTransferIndex;
extern SprTransfer g_sprTransfers[2];

// Block n of the current scratchpad transfer.
struct SprBlock {
    static u32 Of(s32 n)
    {
        return g_sprTransfers[g_sprTransferIndex].addrs[n];
    }
};

struct Frame_166690;
struct DmaChannel;
extern "C" s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout);
s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
Mat4A MultiplyMatrices(const Mat4A& a, const Mat4A& b);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern void* g_toSprChannel;
extern f32 g_gameClock[];
extern const Mat4A g_identityMatrix4;

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
        WaitDmaChannel((DmaChannel*)g_toSprChannel, 0, 0);
        s32 next = i + n;
        g_sprTransferIndex = 1 - g_sprTransferIndex;
        g_sprTransfers[g_sprTransferIndex].state = 2;
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
            u128 d = Vu0::Sub(Vu0::Q(part->at), Vu0::Q(cam->position));
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
                f32 a = ApproachValueWithRamp((RampProfile*)D_00269B50, 0, st->alpha, target, g_gameClock[2]);
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
            if (part->hook != 0) {
                void (*adjust)(void*, PlacedObject*, PartRequest*) = (*(void (***)(void*, PlacedObject*, PartRequest*))part->hook)[4];
                if (adjust != 0) {
                    adjust(part->hook, self, &rec);
                }
            }
            if (part->matrix != 0) {
                rec.m = MultiplyMatrices(rec.m, *(Mat4A*)part->matrix);
            }
            if (part->cameraFacing != 0) {
                BuildCameraFacingMatrix(self, cam, part->cameraFacing, (f32*)&rec.at, &rec.m);
            }
            QueueDeferredRequest((DeferredRequest*)&rec);
            if (part->matrix != 0 || part->cameraFacing != 0) {
                rec.m = g_identityMatrix4;
            }
        }
        i = next;
        n = m;
    }
}

void InitSeekingAgent(SeekingAgent* self)
{
    InitAgent(self);
    self->fadesOut = 0;
    self->fBD0 = 0;
}

void StartSeekingAgent(SeekingAgent* self)
{
    StartAgent(self);
    ResolveObjectLinks(self, 2, D_00269B60);
    self->f5F0 = (void*)ResolveAgentClip(self, 0xEF);
    self->removeClip = ResolveAgentClip(self, 0x16C);
    self->hurtClip = ResolveAgentClip(self, 0x16D);
    self->removeClipAlt = ResolveAgentClip(self, 0x16A);
    self->hurtClipAlt = ResolveAgentClip(self, 0x16B);
}

void EnterSeekingAgentState(SeekingAgent* self, s32 a1, s32 a2)
{
    s32 a2v = a2;
    switch (self->state) {
    case 4:
        self->stateTarget = 0;
        self->objectCount = 0;
        break;
    case 0x10:
        if (self->requestKind == 4) {
            a2v = self->hurtClipAlt;
        } else {
            a2v = self->hurtClip;
        }
        break;
    case 0xB:
        if (self->requestKind == 4) {
            a2v = self->removeClipAlt;
        } else {
            a2v = self->removeClip;
        }
        if (self->roster != 0) {
            RemoveItemKeeperMember((ItemKeeper*)self->roster, self);
        }
        break;
    }
    EnterAgentState(self, a1, (Animation*)a2v);
    s32 kind = self->state;
    if (kind == 0xB || kind == 0x10) {
        self->contactsDisabled = 0;
    }
}

void LeaveSeekingAgentState(SeekingAgent* self, s32 mode)
{
    LeaveAgentState(self, mode);
    s32 kind = self->state;
    if (kind != 8) {
        if (kind == 0x10) {
            SeekPartner* child = ((SeekPartner*)self->partner);
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

    switch (self->state) {
    case 7:
        if (flag != 0) {
            s32 i;
            void** slot;
            for (i = 0, slot = self->objects; i < self->objectCount; slot++, i++) {
                void* n = *slot;
                if (IsObjectAttached((BaseObject*)n) != 0) {
                    SetAgentGoalPoint(self, (Vec02*)((u8*)n + 0x140));
                    break;
                }
            }
        }
        break;
    case 4:
        if (self->mainClip == 0) {
            if (self->walkTarget != 0) {
                GetObjectWorldPosition((BaseObject*)self->walkTarget, (Vec02*)tmp);
                SetAgentGoalPoint(self, (Vec02*)tmp);
            } else {
                SetAgentGoalPoint(self, &self->v140);
            }
        } else {
            UpdateAgentGoal(self, flag);
        }
        break;
    case 12:
    case 13:
        if (self->stateTarget != 0) {
            GetObjectWorldPosition((BaseObject*)self->stateTarget, (Vec02*)tmp);
            SetAgentGoalPoint(self, (Vec02*)tmp);
        }
        break;
    default:
        UpdateAgentGoal(self, flag);
        break;
    }
}

void FaceAgentTowardGoalPoint(Agent* self);
void UpdateAgentState(Agent* self);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

void UpdateSeekingAgentState(SeekingAgent* self)
{
    Vec02 tmp;
    Vec02 second;
    Vec02 third;
    f32 a;

    switch (self->state) {
    case 7:
        FaceAgentTowardGoalPoint(self);
        break;
    case 2:
        if (self->mainPlayer != 0) {
            UpdateAgentState(self);
            break;
        }
        if (self->walkTarget != 0) {
            GetObjectWorldRotation((BaseObject*)self->walkTarget, (Mat02*)&tmp);
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
        if (self->stateTarget == 0) {
            break;
        }
        GetObjectWorldRotation((BaseObject*)self->stateTarget, (Mat02*)&tmp);
        a = ArctangentOfRatio(tmp.y, tmp.x);
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    case 8:
        if (*(void**)((u8*)self->statePlayer + 8) != self->f5F0) {
            break;
        }
        Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)g_camera + 0x40)), Vu0::Q(self->v140));
        a = ArctangentOfRatio(tmp.y, tmp.x);
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    case 11:
    case 16:
        if (self->requestInPool == 0) {
            break;
        }
        Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)((u8*)self->partner + 0x140)));
        a = ArctangentOfRatio(tmp.y, tmp.x);
        if (self->state == 0x10) {
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

s32 AcceptSeekingAgentRequest(SeekingAgent* self, AgentRequest* arg)
{
    if (self->desc05()->m4B(self, arg->kind00)) {
        return 0;
    }
    self->requestInPool = 0;
    self->requestKind = arg->kind00;
    if (arg->kind00 == 0 && arg->ref04 != 0) {
        if (IsObjectInPool((ObjectPool*)((SeekPartner*)self->partner)->p618, arg->ref04)) {
            self->requestInPool = 1;
        }
    }
    return AcceptAgentRequest(self, arg);
}

s32 HandleSeekingAgentObjectEvent(SeekingAgent* self, AgentEvent* msg)
{
    EventNotice args;
    if (HasSpareCount() != 0 && self->requestInPool == 0) {
        self->hitsLeft = 1;
    } else {
        self->hitsLeft = 0;
    }
    if (HandleAgentObjectEvent(self, (AgentHit*)msg) == 0) {
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
    if (self->stateTarget != 0) {
        for (i = 0; i < self->objectCount; i++) {
            Agent* n = (Agent*)self->objects[i];
            if (IsObjectOfKind(n, 8) != 0) {
                s32 k = n->state;
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
        if (i < self->objectCount) {
            return 1;
        }
        self->stateTarget = 0;
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
        if (IsObjectOfKind(item, 8) == 0 || item->state != 0xB) {
            s32 n = self->objectCount;
            if ((u32)n < 4) {
                self->objects[n] = item;
                self->objectCount = n + 1;
                return 1;
            }
        }
    }
    return 0;
}

void SetSeekingAgentStateTarget(SeekingAgent* self, s32 value)
{
    self->stateTarget = (void*)value;
}

void SetSeekingAgentTarget(SeekingAgent* self, s32 value)
{
    self->walkTarget = (void*)value;
}

void StartSeekingAgentEffect(SeekingAgent* self, s32 flag, PlacedObject* extra)
{
    StartSwitchedColliderEffect(self, flag, extra);
    if (flag == 0) {
        ChangeAgentState(self, 8, self->f5F0);
    }
}

// was NEAR: GCC folds the final return 1/return 0 into sltiu/xori; retail keeps li v0,16 + bne and a separate move v0,zero tail

s32 GetSeekingAgentStateKind(SeekingAgent* self)
{
    switch (self->state) {
    case 0x10: return 1;
    case 0xB: return 2;
    }
    return 0;
}

void HandleSeekingAgentNotification(SeekingAgent* self, s32 code, SourceNotice* req)
{
    HandleAgentNotification(self, code, (AgentNotification*)req);
    if (code == 0x13) {
        if (req->f_0 == (s32)self->statePlayer) {
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
    switch (CollectSegmentSpansInPlaneTree((PlaneNode*)a, (Vec02*)b, (Vec02*)c, 2, out)) {
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
    if (FindPointGraphTriangleWithin((PlaneNode*)self->faces, p) != 0) {
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
    o->graph.pointCount = ReadBufferedU16((BufferedStream*)in);
    m->points = (GraphPoint*)AllocateZeroedFrontMemory(o->graph.pointCount << 5);
    m->nA = ReadBufferedU16((BufferedStream*)in);
    m->linkCount = ReadBufferedU16((BufferedStream*)in) + m->nA;
    m->links = (u8*)AllocateZeroedFrontMemory(m->linkCount * 12);
    m->triCount = ReadBufferedU16((BufferedStream*)in);
    m->tris = (u8*)AllocateZeroedFrontMemory(m->triCount * 12);
    if (o->graph.pointCount > 0) {
        do {
            GraphPoint* v = (GraphPoint*)((u8*)m->points + (i << 5));
            s32 k = i + 1;
            j = 0;
            ReadBufferedVector3((BufferedStream*)in, v);
            v->linkCount = ReadBufferedU8((BufferedStream*)in);
            v->links = (GraphLink**)AllocateFrontMemory((v->linkCount + 1) << 2);
            if (v->linkCount > 0) {
                do {
                    v->links[j] = (GraphLink*)(m->links + ReadBufferedU16((BufferedStream*)in) * 12);
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
                *p = (GraphPoint*)((u8*)m->points + (ReadBufferedU16((BufferedStream*)in) << 5));
                p++;
            } while (j >= 0);
        }
        for (e = 0; e < m->triCount; e++) {
            GraphPoint** p = (GraphPoint**)(m->tris + e * 12);
            j = 2;
            do {
                j--;
                *p = (GraphPoint*)((u8*)m->points + (ReadBufferedU16((BufferedStream*)in) << 5));
                p++;
            } while (j >= 0);
        }
    }
    m->faceCount = ReadBufferedU16((BufferedStream*)in);
    m->faces = (GraphFace*)AllocateZeroedFrontMemory(m->faceCount << 5);
    for (s32 e = 0; e < m->faceCount; e++) {
        s32 a;
        GraphFace* f = (GraphFace*)((u8*)m->faces + (e << 5));
        ReadBufferedVector3((BufferedStream*)in, f);
        f->f10 = ReadBufferedFloat((BufferedStream*)in);
        a = ReadBufferedS16((BufferedStream*)in);
        if (a == -1) {
            f->neighbourA = 0;
        } else if (a >= 0) {
            f->neighbourA = (u8*)m->faces + (a << 5);
        } else {
            a += 2;
            a = -a;
            f->neighbourA = (void*)((u32)(m->tris + a * 12) | 1);
        }
        a = ReadBufferedS16((BufferedStream*)in);
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

s32 FindOwnerGraphPath(PointGraphObject* self, Vec02* start, Vec02* goal, s32 maxOut, Vec02* out)
{
    return FindPointGraphPath(&self->graph, start, goal, maxOut, out);
}

void SnapPointToOwnerGraph(PointGraphObject* self, Vec02* p, Vec02* out)
{
    SnapPointToPointGraph(&self->graph, p, out);
}

s32 TestOwnerGraphSpan(PointGraphObject* self, Vec02* from, Vec02* to, s32 max, ColliderSpan* out)
{
    return CollectSegmentSpansInPlaneTree((PlaneNode*)self->graph.faces, from, to, max, out);
}

// A matrix copied whole: the call's arguments are its parameters, substituted as constants.
static inline void CopyMatrix(Mat02* d, const Mat02* s) { CopyBytes(d, (void*)s, 0x30); }

// A step fitted to the graph: the step turned about Z by each of eleven angles in turn (none,
// then half a radian more to either side each time) and scaled, the span from the position to
// its end tested against the graph, and the furthest point reached kept (a whole step ends the
// search). The step becomes the way to that point, divided by the scale.
// The scale is made a vector where the turned matrix is scaled, after the matrix's call, and
// again for the division after the loop (Vu0::ScalarMovedReg and Vu0::ScalarMoved, this
// function's own under AGENTS.md's named exception). loop.c leaves the first in the loop: an
// asm with a float operand may trap, and a call has been passed. gcse puts the second at the
// end of the loop's first block, where cse2 makes it a copy of the first: the load before the
// branch on the test's result (docs/toolchain/loops.md, "An asm kept in its loop"). Retail
// stores a copy of the scale beside the scaled matrix (0xF0), which nothing reads.
void FitStepToPointGraph(PointGraphObject* self, f32 scale, Vec02* pos, Vec02* step)
{
    Mat02 turn;
    Vec02 end;
    Vec02 reached;
    ColliderSpan span;
    f32 best = -1.0f;
    for (u32 i = 0; i < 11; i++) {
        Mat02 scaled;
        Vec02 weight;
        Mat02 rows;
        BuildAxisAngleMatrix(&g_unitZVector, &turn, D_00269B78[i]);
        Vu0::Vec k;
        k.q = Vu0::ScalarMovedReg(scale);
        *(Vu0::Vec*)&rows.r[0] = Vu0::MulX(Vu0::Vec::Of(turn.r[0]), k);
        *(Vu0::Vec*)&rows.r[1] = Vu0::MulX(Vu0::Vec::Of(turn.r[1]), k);
        *(Vu0::Vec*)&rows.r[2] = Vu0::MulX(Vu0::Vec::Of(turn.r[2]), k);
        u128 from = Vu0::Q(*pos);
        *(Vu0::Vec*)&weight = k;
        CopyMatrix(&scaled, &rows);
        Vu0::Q(end) = Vu0::Add(from, Vu0::Rotate(scaled, Vu0::Q(*step)));
        if (TestOwnerGraphSpan(self, pos, &end, 1, &span) != 0 && best < span.time[1]) {
            best = span.time[1];
            Vu0::Q(reached) = Vu0::Q(span.q[1]);
            if (1.0f <= best) break;
        }
    }
    Vu0::Q(*step) = Vu0::DivX(Vu0::Sub(Vu0::Q(reached), Vu0::Q(*pos)), Vu0::ScalarMoved(scale));
}

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

void ClearScreenOwner(s32 owner)
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

void CopyTargetVector(TargetVector* self, TargetVector* src)
{
    PathCurveKeptBits tmp;
    tmp = self->keep;
    CopyObjectData(self, src);
    self->keep = tmp;
}

void LoadPointObject(PointObject* self, void* other)
{
    ReadBufferedVector3((BufferedStream*)other, &self->pos);
    ReadPropertyRecords(self, other);
}

void ConvertPositionToWorld(BaseObject* self, Vec02* out)
{
    TransformPointBetweenFrames((PlacedObject*)self->parent, 0, (Vec02*)((u8*)self + 0x40), out);
}

void ReparentPointObject(PointObject* self, BaseObject* value)
{
    void* sub = &self->pos;
    TransformPointBetweenFrames((PlacedObject*)self->parent, (PlacedObject*)value, (Vec02*)sub, (Vec02*)sub);
    ReparentObject(self, value);
}

s32 ConvertPointObjectPosition(PointObject* self, void* other)
{
    void* p = &self->pos;
    TransformPointBetweenFrames((PlacedObject*)other, 0, (Vec02*)p, (Vec02*)p);
}

void LoadTextPointObject(TextPointObject* self, void* other)
{
    LoadPointObject(self, other);
    ReadBufferedString((BufferedStream*)other, &self->text);
}

void ResetTextPointToHalf(TextPointObject* self)
{
    self->f54 = 0.5f;
    self->f58 = 0.5f;
}