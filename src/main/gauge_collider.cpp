// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1963D8 to 0x198980: the object group's methods, the gauge collider, its agent and the
// gauge-counted object's start. Its name is ours, after the gauge collider and its agent, which
// hold most of its code.
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
#include "vu0.h"
#include "object_finder.h"

// Types other files define, named by the parameters of their functions declared here.
struct NodeQuery;
extern f32 g_gameTime[];
#include "list_iter.h"
#include "object_group.h"
#include "world.h"
#include "gauge_counted_object.h"
#include "object_link.h"
#include "attachment.h"
#include "shapes.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_element.h"
#include "sound_state_object.h"
#include "pad_record.h"
#include "mul_rotation.h"
#include "value_range.h"
#include "attached_set.h"
struct BufferedStream;
struct BaseObject;
struct Vec02;

struct BaseObject;
struct GraphQueryOwner;
struct PointGraphObject;
struct Vec02;

struct Effect;
struct PlacedObject;

struct Collider;

struct Mat02;
struct Vec02;




void InitPlacedObject(PlacedObject* self);
void AppendToList(List01* self, void* item);



void StartPlacedObject(PlacedObject* self);




void LoadCollider(Collider* self, BufferedStream* in);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);




s32 IsObjectOfKind(BaseObject* list, s32 key);



void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
s32 AreMenusAndFadeClear(void);


void SetSoundStateObjectState(SoundStateObject* self, s32 idx);
void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);








void HandleSwitchedColliderActivation(SwitchedCollider* self, void* activator);



extern u8 g_scatterController[];
struct ScatterController;
void RaiseScatterLevels(ScatterController* self, f32 amount);



void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void ApplyGaugeColliderRatioToEffect(GaugeCollider* self);



extern u8 D_0026E744[];


void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetWorldActiveFollower(World* self, void* v);
void StartTimer(T217D_510* self, f32 x);
void SetTimerLimit(T217D_510* self, f32 limit, T217D_510_Fn onEnd);
void StartTimerCounting(T217D_510* self);
void StopTimer(T217D_510* self);
void EndGaugeColliderTimer(s32 unused, s32 flag);




extern f32 g_gameClock[];
extern s32 CountListItems(List01* list);
extern s32 RandomIntInRange(s32 a, s32 b);
extern void RemoveFromList(List01* list, void* item);
extern void AppendToList(List01* self, void* item);
extern void ChangeAgentState(Agent* self, s32 state, void* context);
extern void SetSoundStateObjectState(SoundStateObject* self, s32 idx);







void InitSwitchedCollider(SwitchedCollider* self);
void SetListLinkOffset(List01* p, s32 value);




extern u8 D_0021A790[];

struct StateGraph;
void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
void* CreatePoseSource(World* root, PlacedObject* value, const T2195_Vt* table);
void InsertAttachment(PlacedObject* self, Attachment* src);
void* AllocateFrontMemory(s32 size);
void AppendToList(List01* self, void* item);
void AddStateWalkerListener(StateWalker* self, PlacedObject** p);




struct BufferedStream;
void SetListLinkOffset(List01* self, s32 offset);
void ReadBufferedRotation3(BufferedStream* self, void* out);
void ReadBufferedVector3(BufferedStream* src, void* dst);
s32 ReadBufferedU8(BufferedStream* self);
s32 ReadBufferedS16(BufferedStream* self);
PlacedObject* PopSpawnedClone(World* self, s32 index);
PlacedObject* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void PushCloneBatch(World* self, void* src, s32 n);
GroupCell* AllocateZeroedFrontMemory(s32 n);
void AppendToList(List01* self, void* item);
struct ScriptScope;
void* GetScriptEntryScope(s32 index, World* self);
void AddScriptScopeParent(ScriptScope* scope, ScriptScope* parent);
s32 ReadBufferedU32(BufferedStream* self);
s32 ReadBufferedS8(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
void ReadPropertyRecords(void* self, void* obj);
void ReadSlotObjects(World* self, void* a1, void* a2);
s32 IsListEmpty(List01* list);

// The id that names no object.
struct NoId {
    static s32 None() { return -1; }
};




void CopyPlacedObject(PlacedObject* self, PlacedObject* src);
void ClearList(List01* p);
void AppendToList(List01* self, void* item);



void CopyCollider(Collider* self, Collider* other);
void InitObjectSet(void*);
void ApplyColliderPendingImpulse(Collider* self, s32 moved);
void RegisterObject(void*);
void AppendToList(List01* self, void* item);
void UnregisterObject(void*);
void RemoveFromList(List01* list, void* item);
void StartObject(void*);
void RegisterCollider(Collider* self);
void UnregisterCollider(Collider* self);
void InitObject(void*);
void WriteCameraMatricesPacket(Camera* self);
void AddDmaRefTagIfChanged(void* list, s32 value, s32 end);
void UploadProjectionConstants(void);
void UploadGroupConstants(void);
void UploadCameraOncePerFrame(void);
void RemoveEffect(Effect* self);
void AddCallbackNode(void*, void*, s32, void*);
void AddCallbackNode(void*, void*, void*, void*);
void RemoveCallbackNode(void*, void*, void*, void*);
void EndEffectWithImpact(Effect* self, s32 flag);





void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);



void StartAgent(Agent* self);




void* GetActiveSwitchedCollider(void);
void ReleaseObjectNode(u8* self, GaugeColliderAgent* ctx);
void LeaveAgentState(Agent* self, s32 mode);




void EnterAgentState(Agent* self, s32 evt, Animation* arg);
void FaceAgentAlongPath(Agent* self);



// Notifications 10 and 11: a value and the agent they are for.
struct AgentValueNotice {
    s32 a;
    s32 b;
};

struct AgentNotification;
struct Agent;
void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg);




s32 GetAgentRosterState(Agent* self);
s32 ChooseAgentState(Agent* self);






struct ObjectGatherer;
s32 IsObjectOfKind(BaseObject* list, s32 key);
s32 IsObjectAttached(BaseObject* self);
s32 TestPointAgainstObjectShape(ObjectGatherer* self, void* value);
// The query FindNodeForQuery takes, in the 0x40-byte local retail keeps.
struct NodeQueryFrame {
    void* f00;
    void* f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    u8 pad14[0x40 - 0x14];
};
s32 FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);
void UpdateAgent(Agent* self, f32 dt);

// The file's .data, in retail's order.
f32 D_0026A710 = 2200.0f;
f32 D_0026A714 = 4000.0f;
f32 D_0026A718 = 2000.0f;
f32 D_0026A71C = 4000.0f;
s32 g_gaugeAgentCountLimit = 5;
ObjectLink g_gaugeColliderLoadLinks[1] = { { 0, 0x3D9, 0x610 } };
ObjectLink g_gaugeColliderStartLinks[13] = {
    { 0x24, 0x3DD, 0x640 },
    { 0x20, 0x3DE, 0x648 },
    { 0x0, 0x3E7, 0x64C },
    { 0x0, 0x3E8, 0x650 },
    { 0x0, 0x3E9, 0x654 },
    { 0x0, 0x3EA, 0x658 },
    { 0x0, 0x3EC, 0x670 },
    { 0x4, 0x3ED, 0x65C },
    { 0x0, 0x3EE, 0x668 },
    { 0x0, 0x3F0, 0x66C },
    { 0x4, 0x3EF, 0x660 },
    { 0x24, 0x3EB, 0x678 },
    { 0x1, 0x3F1, 0x6B4 },
};
f32 D_0026A7D8[6] = { 7.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f };
Vec02 D_0026A7F0 = { 3.0f, -2.0f, -1.0f, 0.0f };
Vec02 D_0026A800 = { 0.25f, 0.0f, 0.0f, 0.0f };
Vec02 D_0026A810 = { 1.2f, -1.2f, 0.0f, 0.0f };
f32 D_0026A820 = 60.0f;
f32 D_0026A824 = -30.0f;
f32 D_0026A828 = 0.25f;
f32 D_0026A82C = 0.7f;
f32 D_0026A830 = 250.0f;
f32 D_0026A834 = 0.25f;
f32 D_0026A838 = 0.5f;
f32 D_0026A83C = 0.2f;
f32 D_0026A840 = 0.1f;
f32 D_0026A844 = 1.3f;
Vec02 D_0026A850 = { 0.0f, 3.0f, 0.0f, 0.0f };
Vec02 D_0026A860 = { 0.0f, 0.75f, 0.0f, 0.0f };
Vec02 D_0026A870 = { 5000.0f, 0.0f, 0.0f, 0.0f };
Vec02 D_0026A880 = { 3.0f, -2.0f, -1.0f, 0.0f };
Vec02 D_0026A890 = { 500.0f, 0.0f, 0.0f, 0.0f };
Vec02 D_0026A8A0 = { 1.8f, -0.00024999998f, 0.0f, 0.0f };
Vec02 D_0026A8B0 = { 1.1f, 1.6f, 0.0f, 0.0f };
Vec02 D_0026A8C0 = { 1.4f, -0.005f, 0.0f, 0.0f };
f32 D_0026A8D0[2] = { 0.9f, 1.2f };
f32 D_0026A8D8 = 2000.0f;
f32 D_0026A8DC = 1100.0f;
ObjectLink g_gaugeCountedObjectLinks[3] = { { 0x0, 0x3E4, 0x558 }, { 0x0, 0x3E5, 0x554 }, { 0x20, 0x3E6, 0x55C } };
// The object func_00196938 registers itself as; filled at run time.
GaugeCollider* g_gaugeCollider = 0;

void InitObjectGroup(ObjectGroup* self);
void LoadObjectGroup(ObjectGroup* self, LoadStream* rd);
void CopyObjectGroup(ObjectGroup* self, ObjectGroup* src);
void StartObjectGroup(ObjectGroup* self);
void InitGaugeCollider(GaugeCollider* self);
void LoadGaugeCollider(GaugeCollider* self, BufferedStream* stream);
void StartGaugeCollider(GaugeCollider* self);
s32 AcceptColliderOfOtherRoot(void* root, Collider* self);
void ApplyGaugeColliderRatioToEffect(GaugeCollider* self);
void EndGaugeColliderTimer(s32 unused, s32 flag);
void HandleGaugeColliderActivation(GaugeCollider* a, void* b);
void UpdateGaugeColliderVisibility(GaugeCollider* self);
void PlaceObjectAtRandomNode(GaugeCollider* self);
void ReleaseObjectNode(u8* self, GaugeColliderAgent* ctx);
void ComputeGaugeColliderContactValue(GaugeCollider* ctx, Contact03* out);
void HandleGaugeColliderNotification(GaugeCollider* self, s32 kind, void* rec);
void StartGaugeColliderAgent(GaugeColliderAgent* self);
s32 ChooseGaugeColliderAgentState(GaugeColliderAgent* self);
void LeaveGaugeColliderAgentState(GaugeColliderAgent* self, s32 arg);
void EnterGaugeColliderAgentState(GaugeColliderAgent* self, s32 evt, Animation* arg);
void HandleGaugeColliderAgentNotification(GaugeColliderAgent* self, s32 code, AgentValueNotice* req);
void UpdateGaugeColliderAgent(GaugeColliderAgent* s1, f32 f);
u32 IsGaugeColliderAgentTargetInRange(void);
void StartGaugeCountedObject(GaugeCountedObject* self);

void InitObjectGroup(ObjectGroup* self)
{
    InitPlacedObject(self);
    AppendToList(&self->world->list1C3C, self);
}

void LoadObjectGroup(ObjectGroup* self, LoadStream* rd)
{
    PlacedObject* arr[64];
    ListFrame fr;
    PlacedObject* t;
    PlacedObject* c;
    s32 n;
    s32 i;
    s32 j;
    s32 cnt;
    s32 id;
    PlacedObject* x;
    PlacedObject* h;

    SetListLinkOffset((List01*)&self->cells, 8);
    ReadBufferedRotation3((BufferedStream*)rd, &self->rot);
    ReadBufferedVector3((BufferedStream*)rd, &self->pos);
    n = ReadBufferedU8((BufferedStream*)rd);
    if (self->desc->m12 != 0)
    {
        self->desc->m12(self);
    }
    for (i = 0; i < n; i++)
    {
        GroupCell* cell;
        id = ReadBufferedS16((BufferedStream*)rd);
        if (id == NoId::None())
        {
            c = PopSpawnedClone(self->world, ReadBufferedS16((BufferedStream*)rd));
        }
        else
        {
            s32 a = ReadBufferedS16((BufferedStream*)rd);
            c = CreateTypedRecord(id, self->world, 0, a, ReadBufferedS16((BufferedStream*)rd));
            c->desc->m0A(c, rd);
            PushCloneBatch(self->world, c, ReadBufferedS16((BufferedStream*)rd));
        }
        cell = AllocateZeroedFrontMemory(16);
        cell->node = c;
        cell->id = self->id;
        c->alias = (Alias01*)cell;
        AppendToList((List01*)&self->cells, cell);
        arr[i] = c;
    }
    cnt = ReadBufferedU8((BufferedStream*)rd);
    for (j = 0; j < cnt; j++)
    {
        f32 big = 1.0e10f;
        t = 0;
        id = ReadBufferedS16((BufferedStream*)rd);
        for (i = 0; i < n; i++)
        {
            c = arr[i];
            if (c->id == id)
            {
                t = c;
            }
            else if (c->desc->flags & 1)
            {
                t = (PlacedObject*)FindFirstObjectById(self->world, 0x101, id, c);
            }
            if (t != 0)
            {
                break;
            }
        }
        s32 res = ReadBufferedS16((BufferedStream*)rd);
        if (res != NoId::None())
        {
            void* r = GetScriptEntryScope(res, self->world);
            if (t->f2C != 0)
            {
                AddScriptScopeParent((ScriptScope*)r, (ScriptScope*)t->f2C);
            }
            t->f2C = r;
        }
        s32 w = ReadBufferedU32((BufferedStream*)rd);
        if (t->desc->flags & 1)
        {
            t->f88 = w;
        }
        s32 m = ReadBufferedS8((BufferedStream*)rd);
        if (m == 2)
        {
            t->bits28 = m;
            t->f80 = ReadBufferedFloat((BufferedStream*)rd);
            if (t->f80 == 3.4028235e+38f)
            {
                t->f80 = big;
            }
        }
        ReadPropertyRecords(t, rd);
    }
    for (i = 0; i < n; i++)
    {
        c = arr[i];
        if (c->desc->m16 != 0)
        {
            c->desc->m16(c, self);
        }
        c->desc->m15(c, self->parent);
    }
    if (n == 1)
    {
        List01* list = &self->children;
        ReadSlotObjects(self->world, self, rd);
        if (IsListEmpty(list) == 0)
        {
            fr.list = list;
            fr.prev = g_activeListFrames;
            fr.offset = list->offset;
            g_activeListFrames = &fr;
            c = arr[0];
            h = *(PlacedObject**)list;
            fr.link = (u8*)h + fr.offset;
            x = h;
            while (x != 0)
            {
                x->desc->m15(x, c);
                PlacedObject* nx = *(PlacedObject**)fr.link;
                fr.link = (u8*)nx + fr.offset;
                x = nx;
            }
            g_activeListFrames = fr.prev;
        }
    }
    self->desc->m03(self);
    self->desc->m02(self);
}

void CopyObjectGroup(ObjectGroup* self, ObjectGroup* src)
{
    Pair53 saved = self->kept;
    CopyPlacedObject(self, src);
    self->kept = saved;
    GroupList list = self->cells;
    ClearList((List01*)&self->cells);
    ListFrame frame;
    GroupCell* e = (GroupCell*)list.first;
    while (e != 0) {
        PlacedObject* it = (PlacedObject*)((PlacedObject*)self->parent)->children.head;
        for (; it != 0; it = (PlacedObject*)it->next) {
            if (it->alias == (Alias01*)e) break;
        }
        GroupCell* cell = (GroupCell*)AllocateZeroedFrontMemory(16);
        cell->id = self->id;
        if (it != 0) {
            cell->node = it;
            it->alias = (Alias01*)cell;
        } else {
            cell->node = e->node;
        }
        AppendToList((List01*)&self->cells, cell);
        e = e->next;
    }
}

void StartObjectGroup(ObjectGroup* self)
{
    StartPlacedObject(self);
    self->desc->m03(self);
}

void InitGaugeCollider(GaugeCollider* self)
{
    InitSwitchedCollider(self);
    self->f61C = -10.0f;
    (*(Quad16*)&self->v630) = *(Quad16*)&g_unitZVector;
    self->f688 = 120.0f;
    self->f624 = D_0026A71C;
    self->f628 = D_0026A718;
    SetListLinkOffset(&self->f6A8, 0x568);
    SetListLinkOffset(&self->f69C, 0x568);
    g_gaugeCollider = self;
}

void LoadGaugeCollider(GaugeCollider* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, g_gaugeColliderLoadLinks);
}

void StartGaugeCollider(GaugeCollider* self)
{
    s32 arr[32];
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0xD, g_gaugeColliderStartLinks);
    self->f618 = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    self->f614 = (StateWalker*)CreateStateWalker((StateGraph*)self->f610, self, -1, 1);

    self->f664 = CreatePoseSource(self->world, (PlacedObject*)self->f65C, (const T2195_Vt*)D_0021A790);
    ((Attachment*)self->f664)->mode1 = 2;
    InsertAttachment((PlacedObject*)self->f65C, (Attachment*)self->f664);
    ((T2195_790*)self->f664)->hasTarget = 1;
    ((T2195_790*)self->f664)->target = self->f660;
    *(Quad16*)((u8*)self->f664 + 0x30) = *(Quad16*)&D_00248D30;
    s32 n1 = GatherObjectsById(self->world, 0x305, 0xF, 0, 0, 0);
    self->f690 = n1;
    void* buf = AllocateFrontMemory(n1 * 4);
    self->f694 = buf;
    self->f690 = GatherObjectsById(self->world, 0x105, 0xF, 0, self->f690, buf);
    s32 cnt = GatherObjectsById(self->world, 5, 0x44, 0, 0x20, arr);
    for (s32 i = 0; i < cnt; i++) {
        AppendToList(&self->f69C, (void*)arr[i]);
    }
    self->f6B8 = CreateStateWalker((StateGraph*)self->f6B4, 0, -1, 0);
    AddStateWalkerListener((StateWalker*)self->f6B8, (PlacedObject**)self);
}

void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
void BuildShortestArcRotation(const Vec02* from, const Vec02* to, Mat02* out);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);
f32 WrapAngle(f32 a);
void StepCollider(Collider* self, f32 t);
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain);
void AddColliderForce(void* self, Vec02* force);
extern const Vec02 g_unitZVector;


void StepGaugeCollider(GaugeCollider* self, f32 dt)
{
    Mat02 b;
    Mat02 a;

    StepCollider(self, dt);
    BuildAxisAngleMatrix(&g_unitZVector, &b, self->f618);
    BuildShortestArcRotation(&g_unitZVector, &self->v630, &a);
    {
        u128 a0 = Vu0::Q(a.r[0]);
        u128 a1 = Vu0::Q(a.r[1]);
        u128 a2 = Vu0::Q(a.r[2]);
        Vec02 x;
        Vec02 y;
        Vec02 z;
        Mat02 r;
        u128 p0 = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
        Vu0::Set(r.r[0], p0);
        Vu0::Set(x, p0);
        u128 p1 = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
        Vu0::Set(r.r[1], p1);
        Vu0::Set(y, p1);
        u128 p2 = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
        Vu0::Set(r.r[2], p2);
        Vu0::Set(z, p2);
        b = r;
    }
    TurnColliderTowardRotation(self, dt, &b, D_0026A7D8);
    Mat02 u;
    Mat02 v;
    Mat02 c;
    RotateMatrixUpright(&self->rot, &u, &v);
    BuildAxisAngleMatrix(&g_unitZVector, &c, self->f618);
    c = MultiplyByTransposedMatrix3x3(u, c);
    Vec02 force;
    f32 turn = __builtin_fabsf(WrapAngle(ArctangentOfRatio(v.r[0].y, v.r[0].x) - self->f618));
    f32 k1 = g_unitRange.Limit(D_0026A7F0.x + turn * (D_0026A7F0.y + turn * D_0026A7F0.z));
    f32 phase = (g_gameTime[0] - self->f61C) / D_0026A800.x;
    f32 k2 = g_unitRange.Limit(D_0026A810.x + phase * (D_0026A810.y + phase * D_0026A810.z));
    Vu0::Q(force) = Vu0::MulX(Vu0::Q(c.r[0]), Vu0::Scalar(k1 * k2 * self->f620));
    AddColliderForce(self, &force);
    Vec02 drag;
    drag = self->v150;
    drag.z = 0.0f;
    Vu0::Q(force) = Vu0::MulX(Vu0::Q(drag), Vu0::Scalar(-self->f624 / (self->f628 * self->f628) * k2 * Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(drag)))));
    AddColliderForce(self, &force);
}

s32 AcceptColliderOfOtherRoot(void* root, Collider* self)
{
    if (self->flags538 & 0x80000000000ULL) {
        if (IsObjectOfKind(self, 0x1F) == 0) return 0;
    }
    return self->root != root;
}

extern float g_gameTime[];
extern f32 D_0026A710;
extern f32 D_0026A714;
extern f32 D_0026A718;
extern f32 D_0026A71C;
extern f32 D_0026A820;
extern f32 D_0026A824;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
s32 IsObjectOfKind(BaseObject* list, s32 key);

void UpdateSwitchedCollider(SwitchedCollider* self, f32 dt);
void* FindColliderFloorContact(void* self, s32 key, s32* out);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
struct Oscillator;
void ComputeOscillatorDisplacement(Oscillator* self, f32 time, Vec02* in, Vec02* deltas, Vec02* outA, Vec02* outDeltas, Vec02* outB);
void ClearRootTries(PlacedObject* self);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
Collider* FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);
s32 AcceptColliderOfOtherRoot(void* root, Collider* self);
extern const Vec02 g_unitZVector;
extern const Vec02 g_unitXVector;

struct GaugeSpanOwner { u8 pad00[0x278]; u8* f278; };

void UpdateGaugeCollider(GaugeCollider* self, f32 dt)
{
    Vec02 sum;
    Vec02 pos;
    Vec02 lo;
    Vec02 hi;
    ColliderSpan span;
    Vec02 dir;
    s32 n;
    Collider** list;
    u32 i;

    UpdateSwitchedCollider(self, dt);
    if (FindColliderFloorContact(self, 0, 0) != 0) {
        self->f61C = g_gameTime[0];
        self->f628 = D_0026A718;
        self->f624 = D_0026A71C;
    } else if (self->f644 != 0) {
        self->f61C = g_gameTime[0];
        self->f628 = D_0026A710;
        self->f624 = D_0026A714;
    }
    sum = *(Vec02*)&D_00248D30;
    s32* np;
    Collider*** lp;
    Vec02* pp;
    pp = &pos;
    np = &n;
    lp = &list;
    for (i = 0; i < 4; i++) {
        ConvertPositionToWorld((BaseObject*)self->f64C[i], pp);
        hi = pos;
        lo = pos;
        hi.z = hi.z + D_0026A820;
        lo.z = lo.z + D_0026A824;
        PushBackMemoryMark();
        GatherCollidersInBox(self->world, 0, &hi, &lo, AcceptColliderOfOtherRoot, self, np, lp);
        Collider* hit = FindNearestSpanObject(1, &hi, &lo, n, list, &span);
        if (hit != 0) {
            *(Quad16*)&dir = span.q[2];
            if (IsObjectOfKind(hit, 0x1F) != 0 && ((GaugeSpanOwner*)hit)->f278 != 0) {
                Vec02 pair[2];
                Vec02 in = dir;
                BuildPerpendicularPair(&in, pair, &g_unitXVector, &g_unitZVector);
                ComputeOscillatorDisplacement((Oscillator*)(*(void**)(((GaugeSpanOwner*)hit)->f278 + 0xC)), 50.0f, (Vec02*)&span, pair, 0, pair, 0);
                Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(pair[0]), Vu0::Q(pair[1])), Vu0::Q(g_unitZVector)));
            }
            if (!(dir.z < 0.7f)) {
                goto keep;
            }
        }
        dir = self->v630;
    keep:
        Vu0::Q(sum) = Vu0::MulAddX(Vu0::Q(sum), Vu0::Q(dir), Vu0::Scalar(0.25f));
        PopBackMemoryMark();
    }
    Vu0::Q(self->v630) = Vu0::DivX(Vu0::Q(sum), Vu0::Length(Vu0::Q(sum)));
    ClearRootTries(self);
}

struct GaugeNodeRec {
    u8 pad00[0x18];
    s32 f18;                // 0x18
    u8 pad1C[0x40 - 0x1C];
    Quad16 q40;             // 0x40
};

struct GaugeHeld {
    u8 pad00[0x550];
    s32 f550;               // 0x550
    GaugeNodeRec* f554;     // 0x554
    BaseObject* f558;       // 0x558
    s32 f55C;               // 0x55C
};

void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist);
void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);

GaugeHeld* FindHeldObjectAhead(GaugeCollider* self)
{
    GaugeHeld* list[0x40];
    Mat02 rot;
    Vec02 ahead;
    Vec02 here;
    Vec02 start;
    Vec02 diff;
    GaugeHeld* best = 0;
    BuildAxisAngleMatrix(&g_unitZVector, &rot, self->f618);
    Vu0::Q(ahead) = Vu0::MulAddX(Vu0::Vec::Of(self->pos), Vu0::Vec::Of(self->v150), Vu0::Vec::ScalarAt(D_0026A828)).q;
    ConvertPositionToWorld((BaseObject*)self->f670, &here);
    Vu0::Q(start) = Vu0::Add(Vu0::Rotate(rot, Vu0::Vec::Of(((GaugeNodeRec*)self->f670)->q40)), Vu0::Vec::Of(ahead)).q;
    Vu0::Q(diff) = Vu0::Sub(Vu0::Vec::Of(start), Vu0::Vec::Of(here)).q;
    f32 nearest = D_0026A830;
    s32 n = GatherObjectsById(self->world, 5, 0x48, 0, 0x40, list);
    for (s32 i = 0; i < n; i++) {
        Vec02 framePos;
        Mat02 frameRot;
        Vec02 world;
        Vec02 end;
        Vec02 d;
        f32 t;
        f32 dist;
        GaugeHeld* o = list[i];
        if (o->f550 != 0) {
            continue;
        }
        ComputeObjectFrameAtTime((PlacedObject*)o->f554->f18, 0, &framePos, &frameRot, 0, 0, D_0026A828);
        ConvertPositionToWorld((BaseObject*)o->f554, &world);
        Vu0::Q(world) = Vu0::Add(Vu0::Vec::Of(world), Vu0::Vec::Of(diff)).q;
        Vu0::Q(end) = Vu0::Add(Vu0::Rotate(frameRot, Vu0::Vec::Of(o->f554->q40)), Vu0::Vec::Of(framePos)).q;
        MeasurePointToSegment(&start, &world, &end, &dist, &t);
        if (t < nearest) {
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(world), Vu0::Q(self->v140));
            if (__builtin_fabsf(WrapAngle(ArctangentOfRatio(d.y, d.x) - self->f618)) > D_0026A82C) {
                continue;
            }
            nearest = t;
            best = o;
        }
    }
    return best;
}

void ApplyGaugeColliderRatioToEffect(GaugeCollider* self)
{
    f32 one = 1.0f;
    f32 t = (f32)self->f680 / (f32)self->f684;
    f32 c;
    if (t < 0.0f) {
        c = 0.0f;
    } else if (one < t) {
        c = one;
    } else {
        c = t;
    }
    RaiseScatterLevels((ScatterController*)g_scatterController, 1.0f - c * 0.8f);
}

void EndGaugeColliderTimer(s32 unused, s32 flag)
{
    s32 out[4];
    if (flag == 1) {
        if (g_gaugeCollider->f6B8 != 0) {
            GetStateWalkerTargetKey((StateWalker*)g_gaugeCollider->f6B8, &out[0]);
            GetStateWalkerCurrentKey((StateWalker*)g_gaugeCollider->f6B8, &out[1]);
            if (out[0] != 0x3F4 && out[1] != 0x3F4) {
                SetStateWalkerTarget((StateWalker*)g_gaugeCollider->f6B8, 0x3F5);
                ApplyGaugeColliderRatioToEffect(g_gaugeCollider);
            }
        }
    }
}

void HandleGaugeColliderActivation(GaugeCollider* a, void* b)
{
    HandleSwitchedColliderActivation(a, b);
}

struct GaugeCarrierRec {
    u8 pad00[0x18C];
    void* f18C;             // 0x18C
};

struct GaugeCarrier : BaseObject {
    u8 pad34[0x2D0 - 0x34];
    GaugeCarrierRec* rec;   // 0x2D0
};

void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
GaugeHeld* FindHeldObjectAhead(GaugeCollider* self);
extern f32 g_gameTime[];
extern f32 D_0026A834;

void ControlGaugeCollider(GaugeCollider* self, PadRecord* pad, f32 dt)
{
    s32 cur;
    s32 tgt;
    s32 cur2;
    s32 tgt2;
    s32 cur3;
    Vec02 pos;
    Vec02 delta;

    if (0.0f < pad->f48) {
        ComputeCameraRelativeStickHeading(g_camera, pad, 0, &self->f618);
    }
    self->f620 = pad->f48 * self->f624;
    if (pad->flags & 0xC0) {
        GetStateWalkerCurrentKey(self->f614, &cur);
        GetStateWalkerTargetKey(self->f614, &tgt);
        if (cur == 0x3DB && tgt == cur) {
            if (self->f67C > 0) {
                self->f674 = 0;
                ((GaugeCarrier*)self->f668)->rec->f18C = self->f678;
                SetStateWalkerTarget(self->f614, 0x3DC);
                self->f67C--;
                self->f68C = g_gameTime[0];
            }
        }
    }
    GaugeHeld* held = (GaugeHeld*)self->f674;
    if (held != 0 && self->f68C + D_0026A834 < g_gameTime[0]) {
        held->f550 = 1;
        BaseObject* o = ((GaugeHeld*)self->f674)->f558;
        o->desc->m02(o);
        BaseObject* c = (BaseObject*)self->f668;
        c->desc->m03(c);
        self->f680++;
        if (self->f680 >= self->f684) {
            if (self->f6B8 == 0) {
                self->f674 = 0;
                goto settled;
            }
            GetStateWalkerCurrentKey((StateWalker*)self->f6B8, &cur2);
            GetStateWalkerTargetKey((StateWalker*)self->f6B8, &tgt2);
            if (cur2 != 0x3F5 && tgt2 != 0x3F5) {
                SetStateWalkerTarget((StateWalker*)self->f6B8, 0x3F4);
            }
            StopTimer(&g_timerElement);
        }
        self->f674 = 0;
    }
settled:
    if (IsObjectAttached((BaseObject*)self->f668) != 0) {
        if (self->f674 == 0) {
            self->f674 = FindHeldObjectAhead(self);
            if (self->f674 != 0) {
                GaugeHeld* h = (GaugeHeld*)self->f674;
                ConvertPositionToWorld((BaseObject*)h->f554, &pos);
                Vu0::Q(delta) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
                self->f618 = ArctangentOfRatio(delta.y, delta.x);
                ((T2195_790*)self->f664)->target = (void*)((GaugeHeld*)self->f674)->f554->f18;
                ((T2195_790*)self->f664)->point = *(Vec02*)&((GaugeHeld*)self->f674)->f554->q40;
                ((GaugeCarrier*)self->f668)->rec->f18C = (void*)((GaugeHeld*)self->f674)->f55C;
            }
        }
    } else {
        ((T2195_790*)self->f664)->target = self->f660;
        *(Quad16*)&((T2195_790*)self->f664)->point = *(Quad16*)&D_00248D30;
    }
    GetStateWalkerCurrentKey((StateWalker*)self->f6B8, &cur3);
    if (cur3 == 0x3F3) {
        PlaceObjectAtRandomNode(self);
    }
}

void UpdateGaugeColliderVisibility(GaugeCollider* self)
{
    s32 v;
    GetStateWalkerCurrentKey((StateWalker*)self->f6B8, &v);
    s32 p = 0;
    if (v == 0x3F3) p = AreMenusAndFadeClear();
    if (p != 0) {
        g_gaugeAmountCaption.vt->m14(&g_gaugeAmountCaption);
        D_0026E4E0.vt->m14(&D_0026E4E0);
        g_timerElement.vt->m14(&g_timerElement);
        return;
    }
    g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
    D_0026E4E0.vt->m15(&D_0026E4E0);
    g_timerElement.vt->m15(&g_timerElement);
}

void PlaceObjectAtRandomNode(GaugeCollider* self)
{
    ListFrame frame;
    if (g_gameClock[1] < self->f698) return;
    s32 i = 0;
    for (; i < self->f690; i++) {
        if (IsObjectAttached(((GaugeColliderAgent**)self->f694)[i]) == 0) break;
    }
    if (i >= self->f690) {
        self->f698 = 3.4028235e+38f;
        return;
    }
    GaugeColliderAgent* o = ((GaugeColliderAgent**)self->f694)[i];
    s32 n = RandomIntInRange(0, CountListItems(&self->f69C) - 1);
    SoundStateObject* nd = (SoundStateObject*)self->f69C.head;
    if (n > 0) {
        do {
            nd = nd->listNext;
        } while (--n);
    }
    if (nd == 0) return;
    RemoveFromList(&self->f69C, nd);
    AppendToList(&self->f6A8, nd);
    o->desc->m02(o);
    o->desc02()->m1D(o, (Vec02*)((u8*)nd + 0x140));
    o->desc02()->m1E(o, (Mat02*)((u8*)nd + 0x110));
    o->desc02()->m20(o, (Vec02*)&D_00248D30);
    o->desc02()->m21(o, (Vec02*)&D_00248D30);
    ChangeAgentState(o, 0x10, 0);
    o->fC14 = nd;
    SetSoundStateObjectState(nd, 1);
    self->f698 = g_gameClock[1] + D_0026A838;
}


void ReleaseObjectNode(u8* self, GaugeColliderAgent* ctx)
{
    void* p = ctx->fC14;
    SetSoundStateObjectState((SoundStateObject*)p, 0);
    RemoveFromList((List01*)(self + 0x6A8), p);
    AppendToList((List01*)(self + 0x69C), p);
    ctx->fC14 = 0;
}

void ComputeGaugeColliderContactValue(GaugeCollider* ctx, Contact03* out)
{
    (void)ctx;
    out->f98 = D_0026A83C;
    out->f94 = D_0026A840;
}

f32 MeasureAttachedSetContactDepth(AttachedSet* self, TurningCollider* o, Vec02* nOut, Vec02* hitOut);
void GetAttachedSetPointMotion(AttachedSet* self, void* in, Quad16* outA, Quad16* outB);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
void ComputeOscillatorDisplacement(Oscillator* self, f32 time, Vec02* in, Vec02* deltas, Vec02* outA, Vec02* outDeltas, Vec02* outB);
void ConstrainColliderVector(void* a, void* b, void* c, void* d, s32 e);
f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
void SteerColliderTowardPosition(Collider* self, Vec02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
void SteerColliderTowardRotation(Collider* self, Mat02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
void SpawnSurfaceContactEffects(BaseObject* self, u8* cfg, Quad16* p, f32 chance, Quad16* at, f32 minScale, f32 size);
struct PlayingSound;
void StopSoundRecord(PlayingSound* self, s32 n);

void ApplyGaugeColliderAttachedSetContact(GaugeCollider* self, AttachedSet* set, f32 dt)
{
    Vec02 at;
    Vec02 atVel;
    Vec02 v;
    Vec02 w;
    Vec02 point;
    Vec02 normal;
    Vec02 gains;
    f32 depth = MeasureAttachedSetContactDepth(set, (TurningCollider*)self, &point, &normal);
    if (set->f278 != 0) {
        Vec02 pair[2];
        Vec02 n;
        n = normal;
        BuildPerpendicularPair(&n, pair, &g_unitXVector, &g_unitZVector);
        ComputeOscillatorDisplacement((Oscillator*)(*(void**)(set->f278 + 0xC)), 50.0f, &point, pair, 0, pair, 0);
        Vu0::Set(normal, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(pair[0]), Vu0::Q(pair[1])), Vu0::Q(g_unitZVector)));
    }
    f32 push = self->f360 * set->f360;
    f32 hold = self->f364 * set->f364;
    if (push != 0.0f) {
        Vu0::Q(v) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Scalar(-push * depth));
        ConstrainColliderVector(self, &self->v440, &v, &v, 0);
        AddColliderForce(self, &v);
    }
    if (hold != 0.0f) {
        Vec02 along;
        Vec02 rest;
        Vec02 aim;
        Vec02 aim2;
        Vec02 spinAlong;
        Vec02 spinRest;
        Vec02 aim3;
        Vec02 aim4;
        s32 i;
        GetAttachedSetPointMotion(set, &self->v140, (Quad16*)&at, (Quad16*)&atVel);
        Vu0::Q(v) = Vu0::Sub(Vu0::Q(at), Vu0::Q(self->v150));
        SplitVectorAlongAxis(&v, &normal, &along, &rest);
        f32 k = D_0026A844 + depth;
        for (i = 0; i < 3; i++) {
            (&gains.x)[i] = (&D_0026A850.x)[i] * k * hold;
        }
        Vu0::Q(aim) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(along));
        SteerColliderTowardPosition(self, 0, 0, &aim, &gains.x, dt);
        for (i = 0; i < 3; i++) {
            (&gains.x)[i] = (&D_0026A850.x)[i] * depth * hold;
        }
        Vu0::Q(aim2) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(rest));
        SteerColliderTowardPosition(self, 0, 0, &aim2, &gains.x, dt);
        Vu0::Q(w) = Vu0::Sub(Vu0::Q(D_00248D30), Vu0::Q(self->v160));
        SplitVectorAlongAxis(&w, &normal, &spinAlong, &spinRest);
        for (i = 0; i < 3; i++) {
            (&gains.x)[i] = (&D_0026A860.x)[i] * depth * hold;
        }
        Vu0::Q(aim3) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(spinAlong));
        SteerColliderTowardRotation(self, 0, 0, &aim3, &gains.x, dt);
        for (i = 0; i < 3; i++) {
            (&gains.x)[i] = (&D_0026A860.x)[i] * hold;
        }
        Vu0::Q(aim4) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(spinRest));
        SteerColliderTowardRotation(self, 0, 0, &aim4, &gains.x, dt);
    }
    if (0.0f < depth && depth < 1.0f && 0.9f < normal.z) {
        SpawnSurfaceContactEffects(self, (u8*)set, (Quad16*)&at, dt, (Quad16*)&point, 0.1f,
                      ((self->boundsMax.x - self->boundsMin.x) + (self->boundsMax.y - self->boundsMin.y)) * 0.25f);
    } else {
        StopSoundRecord((PlayingSound*)self->f574, 0);
    }
}

void HandleGaugeColliderNotification(GaugeCollider* self, s32 kind, void* rec)
{
    s32 code;
    HandleSwitchedColliderNotification(self, kind, rec);
    switch (kind) {
    case 0xB:
        self->f644 = 0;
        return;
    case 0xA:
        self->f644 = *(s32*)rec;
        return;
    case 0x14:
        if (rec != self->f6B8) {
            return;
        }
        GetStateWalkerCurrentKey((StateWalker*)rec, &code);
        if (code == 0x3F3) {
            *(void**)D_0026E744 = (u8*)self + 0x67C;
            g_gaugeAmountCaption.target = &self->f680;
            g_gaugeAmountCaption.limit = &self->f684;
            SetWorldActiveFollower(self->world, self);
            StartTimer(&g_timerElement, self->f688);
            SetTimerLimit(&g_timerElement, 0.0f, (T217D_510_Fn)EndGaugeColliderTimer);
            StartTimerCounting(&g_timerElement);
        } else {
            if (code < 0x3F3) {
                return;
            }
            if (code < 0x3F6) {
                StopTimer(&g_timerElement);
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                D_0026E4E0.vt->m15(&D_0026E4E0);
                g_timerElement.vt->m15(&g_timerElement);
                SetWorldActiveFollower(self->world, 0);
            }
        }
        return;
    }
}

void StartGaugeColliderAgent(GaugeColliderAgent* self)
{
    StartAgent(self);
}

void ApplyTurningColliderDrive(TurningCollider* self);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void StepAgent(Agent* self, f32 dt);

void StepGaugeColliderAgent(GaugeColliderAgent* self, f32 dt)
{
    if (self->fC10 != 0 && *(f32*)&self->fBA4 <= g_gameTime[0]) {
        Vec02 accel;
        Vec02 moved;
        ApplyTurningColliderDrive(self);
        Vu0::Q(moved) = Vu0::RotateMembers(self->m110, Vu0::MulX(Vu0::Q(self->v640), Vu0::Scalar(-1.0f)));
        Vu0::Q(accel) = Vu0::DivX(Vu0::Sub(Vu0::Q(moved), Vu0::Q(self->v150)), Vu0::Scalar(dt));
        f32 turn = WrapAngle(self->f638 - ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x));
        f32 a = __builtin_fabsf(turn);
        f32 t = g_unitRange.Limit(D_0026A880.x + a * (D_0026A880.y + a * D_0026A880.z));
        ClampVectorLength(&accel, &accel, D_0026A870.x * t);
        AddColliderForce(self, &accel);
        if (self->parent == 0 && (self->flags538 & 0x8000000000000ULL) == 0) {
            Vec02 local;
            ConstrainColliderVector(self, &self->v440, &self->gravity, &local, 0);
            AddColliderForce(self, &local);
        }
        for (Attach03* n = self->attached; n != 0; n = n->next) {
            n->owner->desc03()->m33(n->owner, n, dt);
        }
    } else {
        StepAgent(self, dt);
    }
}

s32 ChooseGaugeColliderAgentState(GaugeColliderAgent* self)
{
    s32 r;

    switch (self->f724) {
    case 2:
        if (GetAgentRosterState(self) == 0) {
            r = 4;
            break;
        }
        r = ChooseAgentState(self);
        break;
    case 0x10:
        r = 0x10;
        if (self->fC10 != 0) {
            r = 0;
        }
        break;
    default:
        r = ChooseAgentState(self);
        break;
    }
    return r;
}

void UpdateAgentGoal(Agent* self, s32 flag);
void SetAgentGoalPoint(Agent* self, Vec02* p);
void PickRandomPointOnPointGraph(PointGraphObject* self, Vec02* out);
void FitStepToPointGraph(PointGraphObject* self, f32 scale, Vec02* pos, Vec02* step);
void SnapPointToOwnerGraph(PointGraphObject* self, Vec02* p, Vec02* out);

// The agent's next goal by state: 800 on from the active collider, away on the ground (12
// and 13); a random point of its graph at least D_0026A890 away (4); its own place on the
// graph (16); the agent's own choice otherwise. States 4 and 16 only when asked.
void UpdateGaugeColliderAgentGoal(GaugeColliderAgent* self, s32 pick)
{
    Vec02 d;
    Vec02 t;
    Vec02 k;
    switch (self->f724) {
    case 12:
    case 13: {
        SwitchedCollider* c = (SwitchedCollider*)GetActiveSwitchedCollider();
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(c->v140));
        d.z = 0.0f;
        Vu0::Q(k) = Vu0::FromFloat(800.0f);
        u128 v = Vu0::Q(d);
        Vu0::Q(d) = Vu0::MulX(Vu0::DivX(v, Vu0::Length(v)), Vu0::Q(k));
        FitStepToPointGraph(self->f928, 1.0f, &self->v140, &d);
        Vu0::Q(t) = Vu0::Add(Vu0::Q(self->v140), Vu0::Q(d));
        SetAgentGoalPoint(self, &t);
        break;
    }
    case 4:
        if (pick == 0) {
            break;
        }
        s32 far;
        do {
            PickRandomPointOnPointGraph(self->f928, &d);
            u128 e = Vu0::Sub(Vu0::Q(d), Vu0::Q(self->v140));
            far = D_0026A890.x < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(e, e)));
        } while (far == 0);
        SetAgentGoalPoint(self, &d);
        break;
    case 16:
        if (pick == 0) {
            break;
        }
        SnapPointToOwnerGraph(self->f928, &self->v140, &d);
        SetAgentGoalPoint(self, &d);
        break;
    default:
        UpdateAgentGoal(self, pick);
        break;
    }
}

void LeaveGaugeColliderAgentState(GaugeColliderAgent* self, s32 arg)
{
    if (self->f724 == 0x10) {
        void* h = GetActiveSwitchedCollider();
        ReleaseObjectNode((u8*)h, self);
        Vec02 ctx = self->v150;
        ctx.z = 0;
        self->desc02()->m20(self, &ctx);
    }
    LeaveAgentState(self, arg);
}

void EnterGaugeColliderAgentState(GaugeColliderAgent* self, s32 evt, Animation* arg)
{
    EnterAgentState(self, evt, arg);
    if (self->f724 == 0x10) {
        FaceAgentAlongPath(self);
    }
}

void UpdateAgentState(Agent* self);
void SetAnimationPlayerSpeed(AnimationPlayer* p, f32 speed);
extern G27C230* g_currentEntry;

// In state 12, the animation runs at a speed that grows with the distance on the ground from
// the active collider (a quadratic, clamped), both blended by the entry's dt.
void UpdateGaugeColliderAgentState(GaugeColliderAgent* self)
{
    f32 q[3];
    f32 r[2];
    UpdateAgentState(self);
    if (self->f724 != 12) {
        return;
    }
    for (s32 i = 0; i < 3; i++) {
        q[i] = g_currentEntry->dt * ((f32*)&D_0026A8C0)[i] + (1.0f - g_currentEntry->dt) * ((f32*)&D_0026A8A0)[i];
    }
    for (s32 i = 0; i < 2; i++) {
        r[i] = g_currentEntry->dt * D_0026A8D0[i] + (1.0f - g_currentEntry->dt) * ((f32*)&D_0026A8B0)[i];
    }
    u128 p = Vu0::Q(self->v140);
    SwitchedCollider* c = (SwitchedCollider*)GetActiveSwitchedCollider();
    u128 d = Vu0::Sub(p, Vu0::Q(c->v140));
    f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
    f32 v = q[0] + dist * (q[1] + dist * q[2]);
    f32 lo = r[0];
    f32 hi = r[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    SetAnimationPlayerSpeed(self->f7E0, v);
}

void HandleGaugeColliderAgentNotification(GaugeColliderAgent* self, s32 code, AgentValueNotice* req)
{
    HandleAgentNotification(self, code, (AgentNotification*)req);
    if (code != 10) {
        if (code == 11) {
            if (req->b == (s32)self) {
                self->fC10 = 0;
            }
        }
    } else {
        if (req->b == (s32)self) {
            self->fC10 = req->a;
        }
    }
}

void UpdateGaugeColliderAgent(GaugeColliderAgent* s1, f32 f)
{
    GaugeCollider* s0 = (GaugeCollider*)GetActiveSwitchedCollider();

    if (IsObjectOfKind(s0, 0x18) != 0) {
        if (s0->f640 != 0) {
            if (IsObjectAttached((BaseObject*)s0->f640) != 0) {
                if (TestPointAgainstObjectShape((ObjectGatherer*)s0->f640, (u8*)s1 + 0x140) != 0) {
                    NodeQueryFrame t;
                    t.f00 = s1;
                    t.f10 = 2;
                    t.f04 = s1;
                    if (FindNodeForQuery((NodeQuery*)&t, 0, 0) != 0) {
                        s32 n = s0->f67C + 1;
                        if (!(n < g_gaugeAgentCountLimit)) {
                            n = g_gaugeAgentCountLimit;
                        }
                        s0->f67C = n;
                        if (s0->f698 == 3.4028235e+38f) {
                            s0->f698 = g_gameTime[0] + D_0026A838;
                        }
                    }
                }
            }
        }
    }
    UpdateAgent(s1, f);
}

u32 IsGaugeColliderAgentTargetInRange(void) { return 0; }

s32 IsGaugeColliderAgentNear(GaugeColliderAgent* self)
{
    SwitchedCollider* c = (SwitchedCollider*)GetActiveSwitchedCollider();
    if (c == 0 || IsObjectOfKind(c, 0x18) == 0) {
        return 0;
    }
    u128 d = Vu0::Sub(Vu0::Q(c->v140), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
    if (self->fC18 != 0) {
        if (D_0026A8D8 < dist) {
            self->fC18 = 0;
        }
    } else if (dist < D_0026A8DC) {
        self->fC18 = 1;
    }
    return self->fC18;
}

void StartGaugeCountedObject(GaugeCountedObject* self)
{
    ResolveObjectLinks(self, 3, g_gaugeCountedObjectLinks);
    StartPlacedObject(self);
    GaugeCollider* p = (GaugeCollider*)FindFirstObjectByIdGathered(self->world, 5, 0x18, 0);
    if (p != 0) {
        p->f684 = p->f684 + 1;
    }
}
