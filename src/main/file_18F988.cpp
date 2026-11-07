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
void MoveMemory(void* dst, void* src, s32 size);
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
s32 TransformPointBetweenFrames(void* a0, s32 a1, void* a2, void* a3);
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
// The point-graph query FindPointGraphPath and SnapPointToPointGraph take, at 0x34 of its owner.
struct GraphQuery { u8 data[4]; };
struct GraphQueryOwner { u8 head[0x34]; GraphQuery part; };
void FindPointGraphPath(GraphQuery* part);
void SnapPointToPointGraph(GraphQuery* part);
void ReadBufferedVector3(void* a, void* b);
void ReadPropertyRecords(void* a, void* b);
s32 TransformPointBetweenFrames(void* a, s32 b, void* c, s32 d);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
extern u8 D_0026A210[];
void SetupScreenElementText(void* self);
s32 IsFontLoaded(s32 k);
void* GetFontById(s32 k);
struct Obj_191AA8 {
    u8 pad0[0x54];
    void* p54;
};
s32 func_001909F0(void* p);
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
s32 ReadBufferedU16(Stream8A* in);
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
void func_001C8418(SeekingAgent* self, void* p);
s32 IsObjectAttached(void* p);
s32 GetObjectWorldPosition(void* self, s32* arg);
// Up to d spans between two points of the graph (0xE0 bytes for d = 2: two ColliderSpans).
s32 func_001909F0(void* a, s32 b, s32 c, s32 d, ColliderSpan* e);
typedef void (*SlotFn)(void* self);
extern u8* g_saveData;
void UpdateCollider(SwitchedCollider* self);
void func_00192DD0(SwitchedCollider* self);
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

ASM_FUNC(func_0018F9D8);
INCLUDE_RODATA(D_0024B5E0);
INCLUDE_RODATA(jtbl_0024B5F0);

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
                    func_001C8418(self, (u8*)n + 0x140);
                    break;
                }
            }
        }
        break;
    case 4:
        if (self->f750 == 0) {
            if (self->fC24 != 0) {
                GetObjectWorldPosition(self->fC24, tmp);
                func_001C8418(self, tmp);
            } else {
                func_001C8418(self, &self->v140);
            }
        } else {
            UpdateAgentGoal(self);
        }
        break;
    case 12:
    case 13:
        if (self->fC28 != 0) {
            GetObjectWorldPosition(self->fC28, tmp);
            func_001C8418(self, tmp);
        }
        break;
    default:
        UpdateAgentGoal(self);
        break;
    }
}

ASM_FUNC(func_00190258);
INCLUDE_RODATA(jtbl_0024B610);

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

ASM_FUNC(func_00190810);

ASM_FUNC(func_001908C0);

s32 ClassifyAgainstUnitRange(f32 value)
{
    if (value > 1.0f) return 0;
    if (value < -1.0f) return 1;
    return 2;
}

ASM_FUNC(func_001909F0);

s32 IsPointPathShortcutBlocked(void* a, s32 b, s32 c)
{
    ColliderSpan out[2];
    switch (func_001909F0(a, b, c, 2, out)) {
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

ASM_FUNC(func_00190EB8);

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

ASM_FUNC(func_00191290);

ASM_FUNC(func_00191570);
INCLUDE_RODATA(D_0024B64C);

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

void FindOwnerGraphPath(GraphQueryOwner* self)
{
    FindPointGraphPath(&self->part);
}

void SnapPointToOwnerGraph(GraphQueryOwner* self)
{
    SnapPointToPointGraph(&self->part);
}

void TestOwnerGraphSpan(Obj_191AA8* self)
{
    func_001909F0(self->p54);
}

ASM_FUNC(func_00191AC8);

ASM_FUNC(func_00191C78);

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
    return TransformPointBetweenFrames(other, 0, p, p);
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
        func_00192DD0(self);
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

ASM_FUNC(func_00192DD0);

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
