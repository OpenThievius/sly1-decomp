// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1963D8 to 0x198980: the object group's methods, the gauge collider, its agent and the
// gauge-counted object's start. Its name is ours, after the gauge collider and its agent, which
// hold most of its code.
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
#include "vu0.h"
#include "object_finder.h"
#include "functions/agent.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/collider_span.h"
#include "functions/effect.h"
#include "functions/effect_spawner.h"
#include "functions/flagged_object.h"
#include "functions/group_marker.h"
#include "functions/matrix.h"
#include "functions/object_gatherer.h"
#include "functions/object_properties.h"
#include "functions/oscillator.h"
#include "functions/pair_controller.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/render_frame.h"
#include "functions/screen_element.h"
#include "functions/script_machine.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/turning_collider.h"
#include "functions/warp_menu.h"

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




void AppendToList(List01* self, void* item);
















void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);











extern u8 g_scatterController[];
struct ScatterController;
void RaiseScatterLevels(ScatterController* self, f32 amount);



void ApplyGaugeColliderRatioToEffect(GaugeCollider* self);



extern u8 D_0026E744[];


void SetWorldActiveFollower(World* self, void* v);
void EndGaugeColliderTimer(s32 unused, s32 flag);




extern f32 g_gameClock[];
extern s32 CountListItems(List01* list);
extern void RemoveFromList(List01* list, void* item);
extern void AppendToList(List01* self, void* item);







void SetListLinkOffset(List01* p, s32 value);




extern u8 g_aimSwitchPoseSourceMethods[];

struct StateGraph;
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void* CreatePoseSource(World* root, PlacedObject* value, const T2195_Vt* table);
void* AllocateFrontMemory(s32 size);
void AppendToList(List01* self, void* item);




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




void ClearList(List01* p);
void AppendToList(List01* self, void* item);



void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);












void ReleaseObjectNode(GaugeCollider* self, GaugeColliderAgent* ctx);







// Notifications 10 and 11: a value and the agent they are for.
struct AgentValueNotice {
    s32 a;
    s32 b;
};

struct AgentNotification;
struct Agent;










struct ObjectGatherer;
// The query FindNodeForQuery takes, in the 0x40-byte local retail keeps.
struct NodeQueryFrame {
    void* f00;
    void* hold;
    s32 f08;
    s32 out;
    s32 kind;
    u8 pad14[0x40 - 0x14];
};
s32 FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);

// The file's .data, in retail's order.
f32 g_gaugeNoticeTopSpeed = 2200.0f;
f32 g_gaugeNoticePushStrength = 4000.0f;
f32 g_gaugeGroundTopSpeed = 2000.0f;
f32 g_gaugeGroundPushStrength = 4000.0f;
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
f32 g_gaugeNearestRange = 250.0f;
f32 g_gaugePickDelay = 0.25f;
f32 g_gaugePlaceCooldown = 0.5f;
f32 g_gaugeBounce = 0.2f;
f32 g_gaugeFriction = 0.1f;
f32 D_0026A844 = 1.3f;
Vec02 D_0026A850 = { 0.0f, 3.0f, 0.0f, 0.0f };
Vec02 D_0026A860 = { 0.0f, 0.75f, 0.0f, 0.0f };
Vec02 D_0026A870 = { 5000.0f, 0.0f, 0.0f, 0.0f };
Vec02 D_0026A880 = { 3.0f, -2.0f, -1.0f, 0.0f };
Vec02 g_agentGoalMinDistance = { 500.0f, 0.0f, 0.0f, 0.0f };
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
void ReleaseObjectNode(GaugeCollider* self, GaugeColliderAgent* ctx);
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

// Initialises the placed object and appends it to the world's list at 0x1C3C.
void InitObjectGroup(ObjectGroup* self)
{
    InitPlacedObject(self);
    AppendToList(&self->world->list1C3C, self);
}

// Loads a group of placed objects: rotation, position, then entries, each a clone from the world's
// spawned list or a new typed record that reads itself, given a cell on the group's list. It then
// reads per-object overrides (script scope, visibility mask, fade distance, properties), attaches
// the objects to the group (and a one-entry group's children to it).
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
            if (t->scriptScope != 0)
            {
                AddScriptScopeParent((ScriptScope*)r, (ScriptScope*)t->scriptScope);
            }
            t->scriptScope = r;
        }
        s32 w = ReadBufferedU32((BufferedStream*)rd);
        if (t->desc->flags & 1)
        {
            t->visibilityMask = w;
        }
        s32 m = ReadBufferedS8((BufferedStream*)rd);
        if (m == 2)
        {
            t->bits28 = m;
            t->fadeDistanceFar = ReadBufferedFloat((BufferedStream*)rd);
            if (t->fadeDistanceFar == 3.4028235e+38f)
            {
                t->fadeDistanceFar = big;
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

// Copies a group from src: the placed object copy, then the cell list is rebuilt, each cell
// pointing to the matching child of the parent (found by its alias) or, if there is none, to the
// old cell's node.
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

// Starts the placed object and then calls the class's method 3 on it.
void StartObjectGroup(ObjectGroup* self)
{
    StartPlacedObject(self);
    self->desc->m03(self);
}

// Initialises the switched collider and sets the gauge's defaults (last ground time -10 s, the up
// vector as its ground normal, a 120 s time limit, push strength and top speed) and the links of
// its node lists; it also becomes the global gauge collider.
void InitGaugeCollider(GaugeCollider* self)
{
    InitSwitchedCollider(self);
    self->lastGroundTime = -10.0f;
    (*(Quad16*)&self->groundNormal) = *(Quad16*)&g_unitZVector;
    self->timeLimit = 120.0f;
    self->pushStrength = g_gaugeGroundPushStrength;
    self->topSpeed = g_gaugeGroundTopSpeed;
    SetListLinkOffset(&self->usedNodes, 0x568);
    SetListLinkOffset(&self->freeNodes, 0x568);
    g_gaugeCollider = self;
}

// Loads the collider from the stream and resolves its load links.
void LoadGaugeCollider(GaugeCollider* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, g_gaugeColliderLoadLinks);
}

// Starts the gauge collider: resolves its links, takes the heading from its rotation, creates the
// carry walker and a pose source for the pose object (with the rest target), gathers its agents
// (ids 0x305 and 0x105 of kind 0xF) and up to 32 nodes (id 5 of kind 0x44) onto its free list, and
// creates the phase walker with itself as its listener.
void StartGaugeCollider(GaugeCollider* self)
{
    s32 arr[32];
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0xD, g_gaugeColliderStartLinks);
    self->heading = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    self->carryWalker = (StateWalker*)CreateStateWalker((StateGraph*)self->carryGraph, self, -1, 1);

    self->poseSource = CreatePoseSource(self->world, (PlacedObject*)self->poseObject, (const T2195_Vt*)g_aimSwitchPoseSourceMethods);
    ((Attachment*)self->poseSource)->mode1 = 2;
    InsertAttachment((PlacedObject*)self->poseObject, (Attachment*)self->poseSource);
    ((T2195_790*)self->poseSource)->hasTarget = 1;
    ((T2195_790*)self->poseSource)->target = self->restTarget;
    *(Quad16*)&((T2195_790*)self->poseSource)->point = *(Quad16*)&g_zeroVector;
    s32 n1 = GatherObjectsById(self->world, 0x305, 0xF, 0, 0, 0);
    self->agentCount = n1;
    void* buf = AllocateFrontMemory(n1 * 4);
    self->agents = buf;
    self->agentCount = GatherObjectsById(self->world, 0x105, 0xF, 0, self->agentCount, buf);
    s32 cnt = GatherObjectsById(self->world, 5, 0x44, 0, 0x20, arr);
    for (s32 i = 0; i < cnt; i++) {
        AppendToList(&self->freeNodes, (void*)arr[i]);
    }
    self->phaseWalker = CreateStateWalker((StateGraph*)self->phaseGraph, 0, -1, 0);
    AddStateWalkerListener((StateWalker*)self->phaseWalker, (PlacedObject**)self);
}

Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);
void AddColliderForce(void* self, Vec02* force);
extern const Vec02 g_unitZVector;


// Physics step of the gauge collider: turns it toward the heading rotation tilted to the ground
// normal, then adds a driving force along its forward axis (scaled by the push, by how far it has
// to turn, and by the time since it last touched the ground) and a drag force against its
// horizontal velocity that grows with speed.
void StepGaugeCollider(GaugeCollider* self, f32 dt)
{
    Mat02 b;
    Mat02 a;

    StepCollider(self, dt);
    BuildAxisAngleMatrix(&g_unitZVector, &b, self->heading);
    BuildShortestArcRotation(&g_unitZVector, &self->groundNormal, &a);
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
    BuildAxisAngleMatrix(&g_unitZVector, &c, self->heading);
    c = MultiplyByTransposedMatrix3x3(u, c);
    Vec02 force;
    f32 turn = __builtin_fabsf(WrapAngle(ArctangentOfRatio(v.r[0].y, v.r[0].x) - self->heading));
    f32 k1 = g_unitRange.Limit(D_0026A7F0.x + turn * (D_0026A7F0.y + turn * D_0026A7F0.z));
    f32 phase = (g_gameTime[0] - self->lastGroundTime) / D_0026A800.x;
    f32 k2 = g_unitRange.Limit(D_0026A810.x + phase * (D_0026A810.y + phase * D_0026A810.z));
    Vu0::Q(force) = Vu0::MulX(Vu0::Q(c.r[0]), Vu0::Scalar(k1 * k2 * self->push));
    AddColliderForce(self, &force);
    Vec02 drag;
    drag = self->v150;
    drag.z = 0.0f;
    Vu0::Q(force) = Vu0::MulX(Vu0::Q(drag), Vu0::Scalar(-self->pushStrength / (self->topSpeed * self->topSpeed) * k2 * Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(drag)))));
    AddColliderForce(self, &force);
}

// Whether the collider counts: with flag 0x80000000000 set it must be of kind 0x1F, and in any
// case it must not share the given root.
s32 AcceptColliderOfOtherRoot(void* root, Collider* self)
{
    if (self->flags538 & 0x80000000000ULL) {
        if (IsObjectOfKind(self, 0x1F) == 0) return 0;
    }
    return self->root != root;
}

extern float g_gameTime[];
extern f32 g_gaugeNoticeTopSpeed;
extern f32 g_gaugeNoticePushStrength;
extern f32 g_gaugeGroundTopSpeed;
extern f32 g_gaugeGroundPushStrength;
extern f32 D_0026A820;
extern f32 D_0026A824;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
struct Oscillator;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
s32 AcceptColliderOfOtherRoot(void* root, Collider* self);
extern const Vec02 g_unitZVector;
extern const Vec02 g_unitXVector;

// The record PlacedObject::oscillatorBlock points at (a swinging part's oscillator): its oscillator at 0xC.
struct OscillatorBlock { u8 pad00[0x0C]; Oscillator* oscillator; };

// Per-frame update of the gauge collider: after the base update it sets top speed and push strength
// by whether it is on the floor (or a notice value is set), and averages the surface normals under
// its four probe points into groundNormal (the old one where a hit is steeper than 0.7 in z).
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
        self->lastGroundTime = g_gameTime[0];
        self->topSpeed = g_gaugeGroundTopSpeed;
        self->pushStrength = g_gaugeGroundPushStrength;
    } else if (self->noticeValue != 0) {
        self->lastGroundTime = g_gameTime[0];
        self->topSpeed = g_gaugeNoticeTopSpeed;
        self->pushStrength = g_gaugeNoticePushStrength;
    }
    sum = *(Vec02*)&g_zeroVector;
    s32* np;
    Collider*** lp;
    Vec02* pp;
    pp = &pos;
    np = &n;
    lp = &list;
    for (i = 0; i < 4; i++) {
        ConvertPositionToWorld((BaseObject*)self->groundProbes[i], pp);
        hi = pos;
        lo = pos;
        hi.z = hi.z + D_0026A820;
        lo.z = lo.z + D_0026A824;
        PushBackMemoryMark();
        GatherCollidersInBox(self->world, 0, &hi, &lo, AcceptColliderOfOtherRoot, self, np, lp);
        Collider* hit = FindNearestSpanObject(1, &hi, &lo, n, list, &span);
        if (hit != 0) {
            *(Quad16*)&dir = span.q[2];
            if (IsObjectOfKind(hit, 0x1F) != 0 && ((PlacedObject*)hit)->oscillatorBlock != 0) {
                Vec02 pair[2];
                Vec02 in = dir;
                BuildPerpendicularPair(&in, pair, &g_unitXVector, &g_unitZVector);
                ComputeOscillatorDisplacement(((OscillatorBlock*)((PlacedObject*)hit)->oscillatorBlock)->oscillator, 50.0f, (Vec02*)&span, pair, 0, pair, 0);
                Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(pair[0]), Vu0::Q(pair[1])), Vu0::Q(g_unitZVector)));
            }
            if (!(dir.z < 0.7f)) {
                goto keep;
            }
        }
        dir = self->groundNormal;
    keep:
        Vu0::Q(sum) = Vu0::MulAddX(Vu0::Q(sum), Vu0::Q(dir), Vu0::Scalar(0.25f));
        PopBackMemoryMark();
    }
    Vu0::Q(self->groundNormal) = Vu0::DivX(Vu0::Q(sum), Vu0::Length(Vu0::Q(sum)));
    ClearRootTries(self);
}

struct GaugeNodeRec {
    u8 pad00[0x18];
    s32 target;             // 0x18
    u8 pad1C[0x40 - 0x1C];
    Quad16 q40;             // 0x40
};

struct GaugeHeld {
    u8 pad00[0x550];
    s32 taken;              // 0x550
    GaugeNodeRec* anchor;   // 0x554
    BaseObject* object;     // 0x558
    s32 f55C;               // 0x55C
};


// Gives the not yet taken object (of the ones found by id 0x48) that the collider is moving toward:
// it tests each object's anchor segment against a point ahead of the collider, takes the one with
// the smallest parameter below a limit whose direction is within a limit angle of the heading, or 0
// if there is none.
GaugeHeld* FindHeldObjectAhead(GaugeCollider* self)
{
    GaugeHeld* list[0x40];
    Mat02 rot;
    Vec02 ahead;
    Vec02 here;
    Vec02 start;
    Vec02 diff;
    GaugeHeld* best = 0;
    BuildAxisAngleMatrix(&g_unitZVector, &rot, self->heading);
    Vu0::Q(ahead) = Vu0::MulAddX(Vu0::Vec::Of(self->pos), Vu0::Vec::Of(self->v150), Vu0::Vec::ScalarAt(D_0026A828)).q;
    ConvertPositionToWorld((BaseObject*)self->carryNode, &here);
    Vu0::Q(start) = Vu0::Add(Vu0::Rotate(rot, Vu0::Vec::Of(((GaugeNodeRec*)self->carryNode)->q40)), Vu0::Vec::Of(ahead)).q;
    Vu0::Q(diff) = Vu0::Sub(Vu0::Vec::Of(start), Vu0::Vec::Of(here)).q;
    f32 nearest = g_gaugeNearestRange;
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
        if (o->taken != 0) {
            continue;
        }
        ComputeObjectFrameAtTime((PlacedObject*)o->anchor->target, 0, &framePos, &frameRot, 0, 0, D_0026A828);
        ConvertPositionToWorld((BaseObject*)o->anchor, &world);
        Vu0::Q(world) = Vu0::Add(Vu0::Vec::Of(world), Vu0::Vec::Of(diff)).q;
        Vu0::Q(end) = Vu0::Add(Vu0::Rotate(frameRot, Vu0::Vec::Of(o->anchor->q40)), Vu0::Vec::Of(framePos)).q;
        MeasurePointToSegment(&start, &world, &end, &dist, &t);
        if (t < nearest) {
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(world), Vu0::Q(self->v140));
            if (__builtin_fabsf(WrapAngle(ArctangentOfRatio(d.y, d.x) - self->heading)) > D_0026A82C) {
                continue;
            }
            nearest = t;
            best = o;
        }
    }
    return best;
}

// Takes the delivered count over the delivery limit, clamped to 0..1, and lowers the scatter
// controller's levels to 1 minus 0.8 of it.
void ApplyGaugeColliderRatioToEffect(GaugeCollider* self)
{
    f32 one = 1.0f;
    f32 t = (f32)self->deliveredCount / (f32)self->deliveryLimit;
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

// Timer end callback: when flag is 1 and the phase walker is neither at nor heading to key 0x3F4,
// sets its target to 0x3F5 and applies the delivered ratio to the effect.
void EndGaugeColliderTimer(s32 unused, s32 flag)
{
    s32 out[4];
    if (flag == 1) {
        if (g_gaugeCollider->phaseWalker != 0) {
            GetStateWalkerTargetKey((StateWalker*)g_gaugeCollider->phaseWalker, &out[0]);
            GetStateWalkerCurrentKey((StateWalker*)g_gaugeCollider->phaseWalker, &out[1]);
            if (out[0] != 0x3F4 && out[1] != 0x3F4) {
                SetStateWalkerTarget((StateWalker*)g_gaugeCollider->phaseWalker, 0x3F5);
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

GaugeHeld* FindHeldObjectAhead(GaugeCollider* self);
extern f32 g_gameTime[];
extern f32 g_gaugePickDelay;

// Pad control: the stick sets the heading (camera-relative) and the push. A button press (0xC0) at
// the carry walker's rest key with agents waiting drops the held object and starts a delivery;
// after its delay the object is taken, counted, and at the delivery limit the phase walker moves on
// and the timer stops. While the carrier is attached it picks up a held object ahead.
void ControlGaugeCollider(GaugeCollider* self, PadRecord* pad, f32 dt)
{
    s32 cur;
    s32 tgt;
    s32 cur2;
    s32 tgt2;
    s32 cur3;
    Vec02 pos;
    Vec02 delta;

    if (0.0f < pad->stickMagnitude) {
        ComputeCameraRelativeStickHeading(g_camera, pad, 0, &self->heading);
    }
    self->push = pad->stickMagnitude * self->pushStrength;
    if (pad->flags & 0xC0) {
        GetStateWalkerCurrentKey(self->carryWalker, &cur);
        GetStateWalkerTargetKey(self->carryWalker, &tgt);
        if (cur == 0x3DB && tgt == cur) {
            if (self->waitingCount > 0) {
                self->held = 0;
                ((GaugeCarrier*)self->carrier)->rec->f18C = self->f678;
                SetStateWalkerTarget(self->carryWalker, 0x3DC);
                self->waitingCount--;
                self->pickTime = g_gameTime[0];
            }
        }
    }
    GaugeHeld* held = (GaugeHeld*)self->held;
    if (held != 0 && self->pickTime + g_gaugePickDelay < g_gameTime[0]) {
        held->taken = 1;
        BaseObject* o = ((GaugeHeld*)self->held)->object;
        o->desc->m02(o);
        BaseObject* c = (BaseObject*)self->carrier;
        c->desc->m03(c);
        self->deliveredCount++;
        if (self->deliveredCount >= self->deliveryLimit) {
            if (self->phaseWalker == 0) {
                self->held = 0;
                goto settled;
            }
            GetStateWalkerCurrentKey((StateWalker*)self->phaseWalker, &cur2);
            GetStateWalkerTargetKey((StateWalker*)self->phaseWalker, &tgt2);
            if (cur2 != 0x3F5 && tgt2 != 0x3F5) {
                SetStateWalkerTarget((StateWalker*)self->phaseWalker, 0x3F4);
            }
            StopTimer(&g_timerElement);
        }
        self->held = 0;
    }
settled:
    if (IsObjectAttached((BaseObject*)self->carrier) != 0) {
        if (self->held == 0) {
            self->held = FindHeldObjectAhead(self);
            if (self->held != 0) {
                GaugeHeld* h = (GaugeHeld*)self->held;
                ConvertPositionToWorld((BaseObject*)h->anchor, &pos);
                Vu0::Q(delta) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
                self->heading = ArctangentOfRatio(delta.y, delta.x);
                ((T2195_790*)self->poseSource)->target = (void*)((GaugeHeld*)self->held)->anchor->target;
                ((T2195_790*)self->poseSource)->point = *(Vec02*)&((GaugeHeld*)self->held)->anchor->q40;
                ((GaugeCarrier*)self->carrier)->rec->f18C = (void*)((GaugeHeld*)self->held)->f55C;
            }
        }
    } else {
        ((T2195_790*)self->poseSource)->target = self->restTarget;
        *(Quad16*)&((T2195_790*)self->poseSource)->point = *(Quad16*)&g_zeroVector;
    }
    GetStateWalkerCurrentKey((StateWalker*)self->phaseWalker, &cur3);
    if (cur3 == 0x3F3) {
        PlaceObjectAtRandomNode(self);
    }
}

// Looks at the phase walker's current key: when it is 0x3F3 and the menus and fade are clear,
// calls method 14 of the amount caption, the collider caption and the timer element (probably
// showing them), otherwise method 15 of the same three (probably hiding them).
void UpdateGaugeColliderVisibility(GaugeCollider* self)
{
    s32 v;
    GetStateWalkerCurrentKey((StateWalker*)self->phaseWalker, &v);
    s32 p = 0;
    if (v == 0x3F3) p = AreMenusAndFadeClear();
    if (p != 0) {
        g_gaugeAmountCaption.vt->m14(&g_gaugeAmountCaption);
        g_gaugeColliderCaption.vt->m14(&g_gaugeColliderCaption);
        g_timerElement.vt->m14(&g_timerElement);
        return;
    }
    g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
    g_gaugeColliderCaption.vt->m15(&g_gaugeColliderCaption);
    g_timerElement.vt->m15(&g_timerElement);
}

// Once the next place time has come, takes the first unattached agent and places it at a random
// free node (moved to the used list): position and orientation from the node, velocities cleared,
// agent state 0x10, node state 1, and schedules the next time. With no free agent the time becomes
// the largest float, so it stops trying.
void PlaceObjectAtRandomNode(GaugeCollider* self)
{
    ListFrame frame;
    if (g_gameClock[1] < self->nextPlaceTime) return;
    s32 i = 0;
    for (; i < self->agentCount; i++) {
        if (IsObjectAttached(((GaugeColliderAgent**)self->agents)[i]) == 0) break;
    }
    if (i >= self->agentCount) {
        self->nextPlaceTime = 3.4028235e+38f;
        return;
    }
    GaugeColliderAgent* o = ((GaugeColliderAgent**)self->agents)[i];
    s32 n = RandomIntInRange(0, CountListItems(&self->freeNodes) - 1);
    SoundStateObject* nd = (SoundStateObject*)self->freeNodes.head;
    if (n > 0) {
        do {
            nd = nd->listNext;
        } while (--n);
    }
    if (nd == 0) return;
    RemoveFromList(&self->freeNodes, nd);
    AppendToList(&self->usedNodes, nd);
    o->desc->m02(o);
    o->desc02()->m1D(o, &nd->v140);
    o->desc02()->m1E(o, &nd->m110);
    o->desc02()->m20(o, (Vec02*)&g_zeroVector);
    o->desc02()->m21(o, (Vec02*)&g_zeroVector);
    ChangeAgentState(o, 0x10, 0);
    o->node = nd;
    SetSoundStateObjectState(nd, 1);
    self->nextPlaceTime = g_gameClock[1] + g_gaugePlaceCooldown;
}


// Gives the agent's node back: sets its sound state object state to 0, moves it from the used
// list (0x6A8) to the other list (0x69C) and clears the agent's node.
void ReleaseObjectNode(GaugeCollider* self, GaugeColliderAgent* ctx)
{
    void* p = ctx->node;
    SetSoundStateObjectState((SoundStateObject*)p, 0);
    RemoveFromList(&self->usedNodes, p);
    AppendToList(&self->freeNodes, p);
    ctx->node = 0;
}

// Fills the contact's bounce and friction with fixed values; the collider itself is not read.
void ComputeGaugeColliderContactValue(GaugeCollider* ctx, Contact03* out)
{
    (void)ctx;
    out->bounce = g_gaugeBounce;
    out->friction = g_gaugeFriction;
}

void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
struct PlayingSound;

// Applies the contact of the collider with the attached set it rests on, from the depth
// MeasureAttachedSetContactDepth gives (and a normal perturbed by the set's oscillator): pushes out
// against gravity by the depth and steers position and rotation toward the set's motion. A shallow
// flat contact spawns effects, otherwise the sound stops.
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
    if (set->oscillatorBlock != 0) {
        Vec02 pair[2];
        Vec02 n;
        n = normal;
        BuildPerpendicularPair(&n, pair, &g_unitXVector, &g_unitZVector);
        ComputeOscillatorDisplacement(((OscillatorBlock*)set->oscillatorBlock)->oscillator, 50.0f, &point, pair, 0, pair, 0);
        Vu0::Set(normal, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(pair[0]), Vu0::Q(pair[1])), Vu0::Q(g_unitZVector)));
    }
    f32 push = self->pushFactor * set->pushFactor;
    f32 hold = self->dragFactor * set->dragFactor;
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
        Vu0::Q(w) = Vu0::Sub(Vu0::Q(g_zeroVector), Vu0::Q(self->v160));
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
        StopSoundRecord((PlayingSound*)self->playingSound, 0);
    }
}

// Handles notifications after the base handler: 0xB clears the notice value, 0xA sets it, and 0x14
// from the phase walker reacts to its key. At 0x3F3 the game starts (caption targets, the world's
// active follower and the timer with its limit, calling EndGaugeColliderTimer); keys 0x3F4 and
// 0x3F5 stop the timer, hide the captions and the timer and release the active follower.
void HandleGaugeColliderNotification(GaugeCollider* self, s32 kind, void* rec)
{
    s32 code;
    HandleSwitchedColliderNotification(self, kind, rec);
    switch (kind) {
    case 0xB:
        self->noticeValue = 0;
        return;
    case 0xA:
        self->noticeValue = *(s32*)rec;
        return;
    case 0x14:
        if (rec != self->phaseWalker) {
            return;
        }
        GetStateWalkerCurrentKey((StateWalker*)rec, &code);
        if (code == 0x3F3) {
            *(void**)D_0026E744 = &self->waitingCount;
            g_gaugeAmountCaption.target = &self->deliveredCount;
            g_gaugeAmountCaption.limit = &self->deliveryLimit;
            SetWorldActiveFollower(self->world, self);
            StartTimer(&g_timerElement, self->timeLimit);
            SetTimerLimit(&g_timerElement, 0.0f, (T217D_510_Fn)EndGaugeColliderTimer);
            StartTimerCounting(&g_timerElement);
        } else {
            if (code < 0x3F3) {
                return;
            }
            if (code < 0x3F6) {
                StopTimer(&g_timerElement);
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                g_gaugeColliderCaption.vt->m15(&g_gaugeColliderCaption);
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


// Physics step of an agent of the gauge collider: when it has a notice value and its arrival time
// has passed, it applies the turning collider's drive, an acceleration toward the heading velocity
// (limited by a curve of the turn angle), gravity if it has no parent and the flag is clear, and
// the force steps of the attached objects; otherwise it steps as a plain agent.
void StepGaugeColliderAgent(GaugeColliderAgent* self, f32 dt)
{
    if (self->noticeValue != 0 && *(f32*)&self->arrivalTime <= g_gameTime[0]) {
        Vec02 accel;
        Vec02 moved;
        ApplyTurningColliderDrive(self);
        Vu0::Q(moved) = Vu0::RotateMembers(self->m110, Vu0::MulX(Vu0::Q(self->headingVelocity), Vu0::Scalar(-1.0f)));
        Vu0::Q(accel) = Vu0::DivX(Vu0::Sub(Vu0::Q(moved), Vu0::Q(self->v150)), Vu0::Scalar(dt));
        f32 turn = WrapAngle(self->heading - ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x));
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

// The agent's next state: from state 2 it goes to 4 when the roster state is 0; state 0x10 is
// kept until a notice value is set, then it becomes 0; other cases take the ordinary agent
// choice.
s32 ChooseGaugeColliderAgentState(GaugeColliderAgent* self)
{
    s32 r;

    switch (self->state) {
    case 2:
        if (GetAgentRosterState(self) == 0) {
            r = 4;
            break;
        }
        r = ChooseAgentState(self);
        break;
    case 0x10:
        r = 0x10;
        if (self->noticeValue != 0) {
            r = 0;
        }
        break;
    default:
        r = ChooseAgentState(self);
        break;
    }
    return r;
}


// The agent's next goal by state: 800 on from the active collider, away on the ground (12
// and 13); a random point of its graph at least D_0026A890 away (4); its own place on the
// graph (16); the agent's own choice otherwise. States 4 and 16 only when asked.
void UpdateGaugeColliderAgentGoal(GaugeColliderAgent* self, s32 pick)
{
    Vec02 d;
    Vec02 t;
    Vec02 k;
    switch (self->state) {
    case 12:
    case 13: {
        SwitchedCollider* c = (SwitchedCollider*)GetActiveSwitchedCollider();
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(c->v140));
        d.z = 0.0f;
        Vu0::Q(k) = Vu0::FromFloat(800.0f);
        u128 v = Vu0::Q(d);
        Vu0::Q(d) = Vu0::MulX(Vu0::DivX(v, Vu0::Length(v)), Vu0::Q(k));
        FitStepToPointGraph(self->pathGraph, 1.0f, &self->v140, &d);
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
            PickRandomPointOnPointGraph(self->pathGraph, &d);
            u128 e = Vu0::Sub(Vu0::Q(d), Vu0::Q(self->v140));
            far = g_agentGoalMinDistance.x < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(e, e)));
        } while (far == 0);
        SetAgentGoalPoint(self, &d);
        break;
    case 16:
        if (pick == 0) {
            break;
        }
        SnapPointToOwnerGraph(self->pathGraph, &self->v140, &d);
        SetAgentGoalPoint(self, &d);
        break;
    default:
        UpdateAgentGoal(self, pick);
        break;
    }
}

// Leaving state 0x10 releases the agent's node on the active collider and gives the agent its own
// velocity with z cleared; then the ordinary agent leave.
void LeaveGaugeColliderAgentState(GaugeColliderAgent* self, s32 arg)
{
    if (self->state == 0x10) {
        void* h = GetActiveSwitchedCollider();
        ReleaseObjectNode((GaugeCollider*)h, self);
        Vec02 ctx = self->v150;
        ctx.z = 0;
        self->desc02()->m20(self, &ctx);
    }
    LeaveAgentState(self, arg);
}

// The ordinary agent enter, and then in state 0x10 turns the agent along its path.
void EnterGaugeColliderAgentState(GaugeColliderAgent* self, s32 evt, Animation* arg)
{
    EnterAgentState(self, evt, arg);
    if (self->state == 0x10) {
        FaceAgentAlongPath(self);
    }
}

extern G27C230* g_currentEntry;

// In state 12, the animation runs at a speed that grows with the distance on the ground from
// the active collider (a quadratic, clamped), both blended by the entry's dt.
void UpdateGaugeColliderAgentState(GaugeColliderAgent* self)
{
    f32 q[3];
    f32 r[2];
    UpdateAgentState(self);
    if (self->state != 12) {
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
    SetAnimationPlayerSpeed(self->statePlayer, v);
}

// Handles the agent notification and tracks a notice value: kind 10 aimed at this agent stores
// the message's value, kind 11 aimed at it clears it.
void HandleGaugeColliderAgentNotification(GaugeColliderAgent* self, s32 code, AgentValueNotice* req)
{
    HandleAgentNotification(self, code, (AgentNotification*)req);
    if (code != 10) {
        if (code == 11) {
            if (req->b == (s32)self) {
                self->noticeValue = 0;
            }
        }
    } else {
        if (req->b == (s32)self) {
            self->noticeValue = req->a;
        }
    }
}

// Per-frame update of an agent: when the active collider is a gauge collider with a drop zone
// attached and the agent is inside that zone and a node query finds it, it counts one more waiting
// agent for that collider (limited by a maximum) and, if no placement is scheduled, schedules one.
// Then does the base agent's update.
void UpdateGaugeColliderAgent(GaugeColliderAgent* s1, f32 f)
{
    GaugeCollider* s0 = (GaugeCollider*)GetActiveSwitchedCollider();

    if (IsObjectOfKind(s0, 0x18) != 0) {
        if (s0->dropZone != 0) {
            if (IsObjectAttached((BaseObject*)s0->dropZone) != 0) {
                if (TestPointAgainstObjectShape((ObjectGatherer*)s0->dropZone, &s1->v140) != 0) {
                    NodeQueryFrame t;
                    t.f00 = s1;
                    t.kind = 2;
                    t.hold = s1;
                    if (FindNodeForQuery((NodeQuery*)&t, 0, 0) != 0) {
                        s32 n = s0->waitingCount + 1;
                        if (!(n < g_gaugeAgentCountLimit)) {
                            n = g_gaugeAgentCountLimit;
                        }
                        s0->waitingCount = n;
                        if (s0->nextPlaceTime == 3.4028235e+38f) {
                            s0->nextPlaceTime = g_gameTime[0] + g_gaugePlaceCooldown;
                        }
                    }
                }
            }
        }
    }
    UpdateAgent(s1, f);
}

// Always 0: this agent never counts its target as in range.
u32 IsGaugeColliderAgentTargetInRange(void) { return 0; }

// Whether the active collider, if it is of kind 0x18, is near the agent in the XY plane; the
// answer has hysteresis, switching to near under one distance and back only past a larger one.
s32 IsGaugeColliderAgentNear(GaugeColliderAgent* self)
{
    SwitchedCollider* c = (SwitchedCollider*)GetActiveSwitchedCollider();
    if (c == 0 || IsObjectOfKind(c, 0x18) == 0) {
        return 0;
    }
    u128 d = Vu0::Sub(Vu0::Q(c->v140), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
    if (self->nearCollider != 0) {
        if (D_0026A8D8 < dist) {
            self->nearCollider = 0;
        }
    } else if (dist < D_0026A8DC) {
        self->nearCollider = 1;
    }
    return self->nearCollider;
}

// Resolves its links and starts the placed object, then adds one to the delivery limit of the
// gauge collider found in the world (so the limit counts these objects).
void StartGaugeCountedObject(GaugeCountedObject* self)
{
    ResolveObjectLinks(self, 3, g_gaugeCountedObjectLinks);
    StartPlacedObject(self);
    GaugeCollider* p = (GaugeCollider*)FindFirstObjectByIdGathered(self->world, 5, 0x18, 0);
    if (p != 0) {
        p->deliveryLimit = p->deliveryLimit + 1;
    }
}
