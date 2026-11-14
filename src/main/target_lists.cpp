// SPDX-License-Identifier: AGPL-3.0-or-later
// The target lists, 0x169C58 to 0x16AA18 (its .rodata from 0x24A794, its .data from 0x2626E8):
// the three object lists SetObjectListLinkOffsets sets up and their classes, the target curve
// (0x6F), the target point (0x7F) and the listed collision part (0x3A), then the pooled
// children's hold helpers and FindRingPointTowardCollider. Its end is selection_menus.cpp's proved
// start; its start is not proved by retail, only by the change of role from the texture upload
// (texture_upload.cpp): the lists are this file's .data and only its functions read them, so
// the cut could lie from 0x169B18 to 0x169C58. The name is ours, after its role.
#include "common.h"
#include "asm_func.h"
#include "system.h"
#include "listed_collision_part.h"
#include "pooled_object.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "list_iter.h"
#include "attachment.h"
#include "globals.h"
#include "strip_mesh.h"
#include "bump_allocator.h"
#include "texture_header.h"
#include "shapes.h"
#include "vu0.h"
#include "object_finder.h"
#include "functions/agent.h"
#include "functions/anim_record.h"
#include "functions/base_object.h"
#include "functions/collider.h"
#include "functions/cone_agent.h"
#include "functions/display.h"
#include "functions/group_marker.h"
#include "functions/heap.h"
#include "functions/matrix.h"
#include "functions/point_graph.h"
#include "functions/switched_collider.h"
#include "functions/system_calls.h"
#include "functions/target_lists.h"
#include "functions/text_format.h"
#include "functions/texture_upload.h"
struct BufferedStream;
struct BaseObject;
struct Vec02;

struct BaseObject;

struct FrameTarget;
struct ImageRecord;
#include "gs_display.h"
struct PaletteRecord;

struct Mat02;
struct Vec02;

#include "texture_upload_packet.h"



#include "gathered_event_object.h"

void GatherAnimationEventObjects(Animation* self, BaseObject* ctx, s32* outCount, BaseObject*** outArr);
void* CreateRecord2505C0(void);
struct StateResetObject;
struct StateResetGroup;
void AppendToSmallList(StateResetGroup* self, StateResetObject* value);


void RemoveFromList(List01* list, void* item);




extern "C" void ResetGs(s16 mode, s16 x, s16 y, s16 flag);
struct GsOffset;
extern "C" void SetFieldDrawOffset(GsOffset* self, s16 a1, s16 a2, s16 a3);
extern "C" void SyncDataCache(s32 a0);
extern "C" s32 SwapDoubleBuffer(void* self, s32 flag);

#include "dma_chain_block.h"

extern u8 g_screenClearPacketC[];
void* InitPacketBuffer(PacketWriter* self);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void AddDmaRefTag(DmaChainBlock* a, s32 n, void* table);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

struct TexturePacketValue : PacketWriter { s32 value; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;
extern s32 g_gifChannel;

void* InitGifPacket(PacketWriter* f);
void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count);
void BeginDmaTag(PacketWriter* f);
void BeginGifTag(PacketWriter* f, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* f, s32 a, u64 b);
void EndGifPacket(PacketWriter* f);
void AddDmaEndTag(PacketWriter* f);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

extern FrameTarget g_meshQueueEntries[];

void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);


struct TargetedObject {
    u8 pad_00[0x398];
    s32 f398;
};



void SetScaledRotationSpring(PlacedObject* self, f32 scale);
void SetScaledSpinSpring(PlacedObject* self, f32 scale);
void SetScaledPositionRamp(PlacedObject* self, f32 scale);
void SetScaledRotationRamp(void* self, f32 k);


void BeginGifTag(void* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* p, s32 a, u64 b);
void AddGifImageTag(void* p, s32 x);

// The GS register TEX0 an image or palette record keeps (ImageRecord at 0x18, PaletteRecord
// at 0x10), as func_00168E78 and func_00168FB0 fill it: the base, width and format, the size
// as powers of two, then the palette's base, format and load mode.




void SetListLinkOffset(List01* self, s32 offset);

void ClearList(List01* p);




extern u8 g_screenClearPacketA[];
extern u8 g_screenClearPacketC[];
extern u8 g_screenClearPacketB[];

struct GsDBuff;
extern "C" void SetUpDoubleBuffer(GsDBuff* self, s16 a1, s16 w, s16 h, s16 a4, s16 a5, s16 flag);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);

extern s32 g_gifChannel;

extern "C" s32 SendDrawEnvironment(void* self);
struct DmaChannel;
extern "C" void StartDmaChain(DmaChannel* ch, void* tadr);
extern "C" s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout);


s32 WaitGsPaths(s32 a0, s32 a1);



extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);



extern s32 g_gifChannel;

void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

extern s32 g_imageRecordCountA;
extern s32 g_imageRecordCountB;
void AddDmaRefTag(void* self, s32 lo, s32 hi);


void* IsObjectOfKind(BaseObject* list, s32 key);

struct ChildListWalk {
    List01* iter;
    void* cursor;
    s32 link;
    void* prev;

    ChildListWalk(List01* i)
    {
        cursor = i;
        iter = i;
        link = i->offset;
        prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ChildListWalk() { g_activeListFrames = (ListFrame*)prev; }
    void* First()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
};


// What FindTargetCurveLengthNearCollider asks the curve (slot 10): a point and a direction in
// the curve's parent's frame, and the arc length it answers.
struct CurveProbe {
    Quad16 a;
    Quad16 b;
    s32 c;
    u8 pad[0xC];
    f32 x;
};

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

struct HoldMatrices {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    u8 e[0x10];
};

extern f32 g_gameTime[];



// The start of what a queue entry copies: two GIF tags whose words func_001694A0 marks (bit
// 15) when the entry has a flag.



extern "C" s32 GetGsInterruptMask(s32 mask);
extern "C" s32 SwapGsInterruptMask(s32 mask);
extern "C" void SyncDataCache(s32 a);
extern "C" s32 AwaitSemaphore(s32 a);


extern f32 g_gameTime[];




void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);






extern s32 g_imageRecordCountB;
extern s32 g_imageRecordCountA;
extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void* InitPacketWriter(PacketWriter* f);
void WriteVifFlush(PacketWriter* f);
void RewindPacketBuffer(PacketWriter* f);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag);
void WriteVifDirectRef(PacketWriter* f, s32 a, s32 b, s32 c);
void CloseDmaTag(PacketWriter* f);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);

// The file's .data, in retail's order (0x2626E8 to 0x262714): the three object lists.
List01 g_targetCurveList = { 0 };
List01 g_targetPointList = { 0 };
List01 g_partList = { 0 };

// Sets the link offset of the three lists (target curves 0x38, target points 0x50, parts
// 0x558).
void SetObjectListLinkOffsets()
{
    SetListLinkOffset(&g_targetCurveList, 0x38);
    SetListLinkOffset(&g_targetPointList, 0x50);
    SetListLinkOffset(&g_partList, 0x558);
}

// Empties the three lists (target curves, target points, parts).
void ClearObjectLists()
{
    ClearList(&g_targetCurveList);
    ClearList(&g_targetPointList);
    ClearList(&g_partList);
}

// Initialiser of the target curve (class 0x6F): no target id (-1), f4C = 1, f50 = 3 and the
// largest float as its range.
void InitTargetCurve(TargetCurve* self)
{
    InitObject(self);
    self->targetId = -1;
    self->f4C = 1;
    self->f50 = 3;
    self->maxHeightAbove = 3.4028235e+38f;
}

// Registers a target curve as an object and adds it to the list of target curves.
void RegisterTargetCurve(TargetCurve* self)
{
    RegisterObject(self);
    AppendToList(&g_targetCurveList, self);
}

// Undoes RegisterTargetCurve.
void UnregisterTargetCurve(TargetCurve* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetCurveList, self);
}

// After loading: finds the object the curve targets by id (under its parent), keeps it and
// clears its f398.
void PostLoadTargetCurve(TargetCurve* self)
{
    if (self->targetId != -1) {
        TargetedObject* r = (TargetedObject*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

// Copy of a target curve: copies the object data but keeps its own list bits.
void CopyTargetCurve(TargetCurve* self, TargetCurve* src)
{
    PathCurveKeptBits saved = self->keep;
    CopyObjectData(self, src);
    self->keep = saved;
}

f32 WrapAngle(f32 a);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

// Gives the place on a target curve at length t where the player is held: the curve's point (in the
// world) offset sideways, 20 units to one side for mode 0 and 70 for mode 1, and the heading angle
// to face along the curve (turned half a turn for mode 1).
void PlaceOnTargetCurve(TargetCurve* self, Vec02* out, f32* angleOut, f32 t)
{
    Vec02 pos;
    Vec02 tangent;
    PathCurve* o = self->curve;
    if (o->vt->m02 != 0) {
        ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, t, &pos, &tangent);
    }
    TransformPointBetweenFrames((PlacedObject*)self->parent, 0, &pos, &pos);
    TransformDirectionBetweenFrames((PlacedObject*)self->parent, 0, &tangent, &tangent);
    f32 radius;
    switch (self->mode40) {
    case 0:
        radius = 20.0f;
        break;
    case 1:
        radius = 70.0f;
        break;
    default:
        radius = 0.0f;
        break;
    }
    if (out) {
        u128 base = Vu0::Q(pos);
        u128 k = Vu0::Scalar(radius);
        Vu0::Q(*out) = Vu0::MulAddX(base, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(tangent), Vu0::Q(g_unitZVector)), Vu0::Q(g_zeroVector)), k);
    }
    if (angleOut) {
        *angleOut = ArctangentOfRatio(-tangent.x, tangent.y);
        if (self->mode40 == 1) {
            *angleOut = WrapAngle(*angleOut + 3.14159274f);
        }
    }
}

// Finds the length along a target curve nearest the active switched collider (the player), kept 30
// units from the ends of an open curve, and puts the place and angle at that length
// (PlaceOnTargetCurve) in a2 and a3. The length is stored in *out.
void FindTargetCurveLengthNearCollider(TargetCurve* self, f32* out, void* a2, void* a3)
{
    CurveProbe f;
    PlacedObject* node = (PlacedObject*)GetActiveSwitchedCollider();
    PathCurve* o = self->curve;
    f.c = 1;
    TransformPointBetweenFrames(0, (PlacedObject*)self->parent, &node->v140, (Vec02*)&f.a);
    TransformDirectionBetweenFrames(0, (PlacedObject*)self->parent, (Vec02*)&g_unitZVector, (Vec02*)&f.b);
    if (o->vt->m10 != 0) {
        o->vt->m10(o, &f.a, &f.b, 0, 0, 0, &f.x);
    }
    if (o->wrap == 0) {
        f32 k = 30.0f;
        f32 t = self->curve->vt->m08(self->curve) - k;
        f32 r = f.x;
        if (r < k) {
            r = k;
        } else if (t < r) {
            r = t;
        }
        f.x = r;
    }
    PlaceOnTargetCurve(self, (Vec02*)a2, (f32*)a3, f.x);
    *out = f.x;
}

// Initialiser of the target point (class 0x7F): no target id (-1), f68 = 1 and the largest float
// as its range.
void InitTargetPoint(TargetPoint* self)
{
    InitObject(self);
    f32 k = 3.4028235e+38f;
    self->targetId = -1;
    self->f68 = 1;
    self->f70 = k;
}

// Registers a target point as an object and adds it to the list of target points.
void RegisterTargetPoint(TargetPoint* self)
{
    RegisterObject(self);
    AppendToList(&g_targetPointList, self);
}

// Undoes RegisterTargetPoint.
void UnregisterTargetPoint(TargetPoint* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetPointList, self);
}

// After loading: finds the object the point targets by id (under its parent), keeps it and
// clears its f398.
void PostLoadTargetPoint(TargetPoint* self)
{
    if (self->targetId != -1) {
        TargetedObject* r = (TargetedObject*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

// Copy of a target point: copies the object data but keeps its own list bits.
void CopyTargetPoint(TargetPoint* self, TargetPoint* src)
{
    KeptBits saved = self->keep;
    CopyObjectData(self, src);
    self->keep = saved;
}

void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);
f32 WrapAngle(f32 a);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

// Gives the place on a target point's ring at distance t along it (an angle of t over the ring's
// radius): the point's position plus the offset at that angle, the radius grown by 20 for mode 0
// and 70 for mode 1, and the angle to face (turned half a turn for mode 1).
void PlaceOnTargetPoint(TargetPoint* self, Vec02* out, f32* angleOut, f32 t)
{
    Vec02 offset;
    f32 angle = t / self->radius5C;
    if (out) {
        f32 radius = self->radius5C;
        switch (self->mode58) {
        case 0:
            radius += 20.0f;
            break;
        case 1:
            radius += 70.0f;
            break;
        }
        ComputePolarOffset((Vec3*)&offset, angle, radius, 0.0f);
        ConvertPositionToWorld(self, out);
        Vu0::Q(*out) = Vu0::Add(Vu0::Q(*out), Vu0::Q(offset));
    }
    if (angleOut) {
        *angleOut = angle;
        if (self->mode58 == 1)
            *angleOut = WrapAngle(angle + 3.14159274f);
    }
}

// Places a point on the target point's circle (radius at +0x5C), at the angle from the target
// point toward the active switched collider.
void PlaceTargetPointNearCollider(TargetPoint* self, Vec02* out, f32* angleOut)
{
    Vec02 here;
    Vec02 d;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    ConvertPositionToWorld(self, &here);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(active->v140), Vu0::Q(here));
    PlaceOnTargetPoint(self, out, angleOut, ArctangentOfRatio(d.y, d.x) * self->radius5C);
}

// Initialiser of class 0x3A: a collider with springs and ramps set to scale 3 (2 for the
// rotation ramp) and f568 = 300.
void InitListedCollisionPart(ListedCollisionPart* self)
{
    f32 k = 3.0f;
    InitCollider(self);
    SetScaledRotationSpring(self, k);
    SetScaledSpinSpring(self, k);
    SetScaledPositionRamp(self, k);
    SetScaledRotationRamp(self, 2.0f);
    self->f568 = 300.0f;
}

// Loads a listed collision part: its collider data, then marks its link record (allocating it
// when missing) and sets its first three rows to the identity.
void LoadListedCollisionPart(ListedCollisionPart* self, BufferedStream* stream)
{
    Rec2195_224* b;
    Quad16* dst;
    Quad16* src;

    LoadCollider(self, stream);
    if (self->linkRecord == 0) {
        self->linkRecord = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);

    }
    b = self->linkRecord;
    b->flags |= 1;
    dst = (Quad16*)self->linkRecord;
    src = (Quad16*)&g_identityMatrix;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

// Registers a collision part as a collider and adds it to the list of parts.
void AddToPartList(ListedCollisionPart* self)
{
    RegisterCollider(self);
    AppendToList(&g_partList, self);
}

// Undoes AddToPartList.
void RemoveFromPartList(ListedCollisionPart* self)
{
    UnregisterCollider(self);
    RemoveFromList(&g_partList, self);
}

// Copy of a listed collision part that keeps its own list link, so it stays on its own list.
void CopyKeepingListLink(ListedCollisionPart* self, ListedCollisionPart* src)
{
    Link02 tmp = self->listLink;
    CopyCollider(self, src);
    self->listLink = tmp;
}

// Contact filter of a listed collision part: always allowed against the player that is holding
// it, otherwise the common test.
s32 TestListedCollisionPartMayContact(Collider* a0, Collider* a1)
{
    if ((void*)a1 == g_player && (void*)a0 == ((Player*)a1)->heldObject) {
        return 1;
    }
    return TestCollidersMayContact(a0, a1);
}

// Per-frame step of a listed collision part: the collider's, then, unless steering is skipped,
// steers it toward its own rotation made upright.
void StepListedCollisionPart(ListedCollisionPart* self, f32 t)
{
    Mat3U buf;

    StepCollider(self, t);
    if (self->skipSteering != 0) {
        return;
    }
    RotateMatrixUpright(&self->rot, 0, (Mat02*)&buf);
    SteerColliderTowardRotation(self, (Mat02*)&buf, (f32*)self->p214, (Vec02*)&g_zeroVector, (f32*)self->p218, t);
}

// Changes the state of a pooled object that the player can pick up: leaving state 1 (held) lets go
// of the player, clears the anchors and raises script event 3; entering state 1 takes the player as
// its holder, zeroes its velocities, anchors it and stores the rotation of the player's upright
// frame relative to its own, raising script event 2. The state time is stamped.
void SetPooledObjectPlayerHold(PooledObject* self, s32 v)
{
    HoldMatrices f;

    if (self->state == v) {
        return;
    }
    if (self->state == 1) {
        self->desc->m15(self, 0);
        SetColliderAnchors(self, 0, 0, 0, 0);
        TriggerScriptEvent(self, 3, 0, 0);
    }
    if (v == 1) {
        self->desc->m15(self, (BaseObject*)g_player);
        self->desc02()->m20(self, (Vec02*)&g_zeroVector);
        self->desc02()->m21(self, (Vec02*)&g_zeroVector);
        SetColliderAnchors(self, 3, 0, 3, 0);
        RotateMatrixUpright(&g_player->m110, 0, (Mat02*)f.a);
        RotateMatrixUpright(&self->m110, (Mat02*)f.c, (Mat02*)f.b);
        MatrixToAxisAngle((Mat02*)f.c, (f32*)f.e, (Vec02*)f.d);
        MultiplyMatrices3x3((Mat02*)f.a, (Mat02*)f.b, (Mat02*)self->linkRecord);
        TriggerScriptEvent(self, 2, 0, 0);
    }
    self->state = v;
    self->stateTime = g_gameTime[0];
}

// The number of the object's children of class 70 (a pooled object) whose state is 3 or 4, that
// is those it is holding at the moment.
s32 CountHeldPooledChildren(PlacedObject* self)
{
    ChildListWalk w(&self->children);
    s32 count = 0;
    void* node = w.First();
    while (node != 0) {
        if (IsObjectOfKind((BaseObject*)node, 70)) {
            s32 x = ((PooledObject*)node)->state;
            if (1 < (u32)(x - 3)) {
            } else {
                count++;
            }
        }
        node = w.Next();
    }
    return count;
}

// Finds the child of kind 0x46 in state 4 whose state time is the earliest (the one that has been
// in that state longest); null when there is none.
void* FindEarliestPooledChild(PlacedObject* self)
{
    ChildListWalk w(&self->children);
    void* best = 0;
    f32 bestF = 3.4028235e+38f;
    void* node = w.First();
    while (node != 0) {
        if (IsObjectOfKind((BaseObject*)node, 0x46)) {
            PooledObject* n = (PooledObject*)node;
            if (n->state == 4 && n->stateTime < bestF) {
                best = node;
                bestF = n->stateTime;
            }
        }
        node = w.Next();
    }
    return best;
}

f32 WrapAngle(f32 a);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

// Gives the point on a ring around an object (the radius at +0x560 plus 70) in the direction of the
// active switched collider, in the horizontal plane, and the heading angle of that direction turned
// half a turn.
void FindRingPointTowardCollider(PlacedObject* self, Vec02* out, f32* angleOut)
{
    Vec02 d;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    u128 p = Vu0::Q(self->v140);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(active->v140), p);
    d.z = 0.0f;
    if (out) {
        // the held object's class is not known: its ring radius is at 0x560
        u128 k = Vu0::Scalar(*(f32*)((u8*)self + 0x560) + 70.0f);
        Vu0::Q(*out) = Vu0::MulAddX(p, Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)), k);
    }
    if (angleOut) {
        *angleOut = WrapAngle(ArctangentOfRatio(d.y, d.x) + 3.14159274f);
    }
}
