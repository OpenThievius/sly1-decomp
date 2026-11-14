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
struct BufferedStream;
struct BaseObject;
struct Vec02;

struct BaseObject;

struct FrameTarget;
struct ImageRecord;
struct PacketWriter;
struct PaletteRecord;

struct Mat02;
struct Vec02;

struct PacketWriter;



struct GatheredEventObject { u8 pad0[0x328]; s32 f328; };
struct GatheredObjects { s32 count; GatheredEventObject** items; };

void StartAgent(Agent* self);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherAnimationEventObjects(Animation* self, BaseObject* ctx, s32* outCount, BaseObject*** outArr);
void* CreateRecord2505C0(void);
struct StateResetObject;
struct StateResetGroup;
void AppendToSmallList(StateResetGroup* self, StateResetObject* value);

void InitAgent(Agent* self);
void InitConeAgent(ConeAgent* self);

void UnregisterCollider(Collider* self);
void RemoveFromList(List01* list, void* item);

void CopyCollider(Collider* self, Collider* other);

s32 TestCollidersMayContact(Collider* a, Collider* b);


void SendDisplayResetPacket(void);
void SignalDisplaySync(void);
extern "C" void ResetGs(s16 mode, s16 x, s16 y, s16 flag);
struct GsOffset;
extern "C" void SetFieldDrawOffset(GsOffset* self, s16 a1, s16 a2, s16 a3);
extern "C" void SyncDataCache(s32 a0);
extern "C" s32 SwapDoubleBuffer(void* self, s32 flag);

struct DmaChainBlock { u8 bytes[0x20]; };

extern u8 g_screenClearPacketC[];
void* InitPacketBuffer(PacketWriter* self);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void AddDmaRefTag(DmaChainBlock* a, s32 n, void* table);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void SendPacketToBothBuffers(DmaChainBlock* b);

struct TexturePacket : PacketWriter { s32 value; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;
extern s32 g_gifChannel;

void* InitGifPacket(PacketWriter* f);
void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count);
void BeginDmaTag(PacketWriter* f);
s32 PlaceMaskedImages(s32 mask, BumpAllocator* b, PacketWriter* c);
void BeginGifTag(PacketWriter* f, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* f, s32 a, u64 b);
void EndGifPacket(PacketWriter* f);
void AddDmaEndTag(PacketWriter* f);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void SendGsPacketAndWait(s32 channel, void* b);

extern FrameTarget g_meshQueueEntries[];

void RegisterObject(BaseObject* self);
void AppendToList(List01* self, void* item);
void UnregisterObject(BaseObject* self);
void RemoveFromList(List01* list, void* item);


struct TargetedObject {
    u8 pad_00[0x398];
    s32 f398;
};


void CopyObjectData(BaseObject* self, BaseObject* src);

void InitCollider(Collider* self);
void SetScaledRotationSpring(PlacedObject* self, f32 scale);
void SetScaledSpinSpring(PlacedObject* self, f32 scale);
void SetScaledPositionRamp(PlacedObject* self, f32 scale);
void SetScaledRotationRamp(void* self, f32 k);

void RegisterCollider(Collider* self);

void BeginGifTag(void* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* p, s32 a, u64 b);
void AddGifImageTag(void* p, s32 x);

// The GS register TEX0 an image or palette record keeps (ImageRecord at 0x18, PaletteRecord
// at 0x10), as func_00168E78 and func_00168FB0 fill it: the base, width and format, the size
// as powers of two, then the palette's base, format and load mode.
struct GsTex0 {
    u64 tbp : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
};

u32 CeilLog2(u32 n);

void BeginImageTransfer(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void SetListLinkOffset(List01* self, s32 offset);

void ClearList(List01* p);


void SubmitMeshQueueEntry(FrameTarget* self);
void* AllocateZeroedFrontMemory(u32 n);


extern u8 g_screenClearPacketA[];
extern u8 g_screenClearPacketC[];
extern u8 g_screenClearPacketB[];

struct GsDBuff;
extern "C" void SetUpDoubleBuffer(GsDBuff* self, s16 a1, s16 w, s16 h, s16 a4, s16 a5, s16 flag);
void FillScreenColor(u8* buffer, Rgba4* color, s32 flag);
s32 CreateLockSemaphore(s32 initCount, s32 maxCount);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);
s32 EnableInterruptCause(s32 a0);
void InitMeshQueue(void);
void ResetDisplayBuffers(void);
s32 HandleVblankStart(s32 cause);
s32 HandleGsFinish(s32 cause);

extern s32 g_gifChannel;

extern "C" s32 SendDrawEnvironment(void* self);
struct DmaChannel;
extern "C" void StartDmaChain(DmaChannel* ch, void* tadr);
extern "C" s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout);

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other);

void ApplyFieldDisplayOffset(void);
s32 WaitGsPaths(s32 a0, s32 a1);

struct TextureUploadPacket : PacketWriter { u8 span[0x10]; s32 out; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other);
s32 PlaceMaskedImages(s32 mask, BumpAllocator* b, PacketWriter* c);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
void BuildAnimRecordGifPackets(void* self);

struct FadePacket : PacketWriter { s32 value; u8 pad[0x3F0]; };

extern s32 g_gifChannel;

void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void WriteColoredSpritePacket(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, PacketWriter* p);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void SendGsPacketAndWait(s32 channel, void* b);
void FlipDisplayFrame(void);

extern s32 g_imageRecordCountA;
extern s32 g_imageRecordCountB;
s32 AllocateBump(s32* self,s32 size);
void BuildPaletteTexRegister(PaletteRecord* self, u32 a1);
void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx);
void AddDmaRefTag(void* self, s32 lo, s32 hi);
void BuildImageTexRegister(ImageRecord* self, u32 a1);
void StartImageUpload(ImageRecord* d, u32 dbp, void* ctx);


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

void InitObject(BaseObject* self);

// What FindTargetCurveLengthNearCollider asks the curve (slot 10): a point and a direction in
// the curve's parent's frame, and the arc length it answers.
struct CurveProbe {
    Quad16 a;
    Quad16 b;
    s32 c;
    u8 pad[0xC];
    f32 x;
};

void* GetActiveSwitchedCollider(void);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void PlaceOnTargetCurve(TargetCurve* self, Vec02* out, f32* angleOut, f32 t);

struct HoldMatrices {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    u8 e[0x10];
};

extern f32 g_gameTime[];

void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);


// The start of what a queue entry copies: two GIF tags whose words func_001694A0 marks (bit
// 15) when the entry has a flag.
struct QueuedGifTags {
    s32 f0;
    u8 pad0[0xC];
    s32 f10;
};

void CopyMemory(QueuedGifTags* dst, void* src, s32 count);

extern "C" s32 GetGsInterruptMask(s32 mask);
extern "C" s32 SwapGsInterruptMask(s32 mask);
extern "C" void SyncDataCache(s32 a);
extern "C" s32 AwaitSemaphore(s32 a);

void LoadCollider(Collider* self, BufferedStream* stream);
void* AllocateZeroedFrontMemory(s32 bytes);

void StepCollider(Collider* self, f32 t);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
void SteerColliderTowardRotation(Collider* self, Mat02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
extern f32 g_gameTime[];

struct TransferBase { s32 v; };

void BeginImageTransfer(TransferBase dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);

struct GsPmode { u32 en1 : 1; u32 rest : 31; u32 hi : 32; };
struct GsDispFb { u32 fbp : 9; u32 fbw : 6; u32 psm : 5; u32 pad0 : 12; u32 dbx : 11; u32 dby : 11; u32 pad1 : 10; };
struct GsDisplay { u32 dx : 12; u32 dy : 11; u32 magh : 4; u32 magv : 2; u32 pad0 : 3; u32 dw : 12; u32 dh : 11; u32 pad1 : 9; };
struct DisplayRegs { GsPmode pmode; u64 pad; GsDispFb dispfb; GsDisplay display; u64 pad2; };
struct GsPrivRegs {
    GsPmode pmode; u8 pad0[0x70 - 8];
    GsDispFb dispfb2; u8 pad1[8];
    GsDisplay display2; u8 pad2[0x1000 - 0x88];
    u32 csr;
};

extern s32 g_imageRecordCountB;
extern s32 g_imageRecordCountA;
extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other);
void* InitPacketWriter(PacketWriter* f);
void WriteVifFlush(PacketWriter* f);
void RewindPacketBuffer(PacketWriter* f);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
s32 AllocateBump(s32* self,s32 size);
void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx);
void StartImageUpload(ImageRecord* d, u32 dbp, void* ctx);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag);
void WriteVifDirectRef(PacketWriter* f, s32 a, s32 b, s32 c);
void CloseDmaTag(PacketWriter* f);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
void BuildAnimRecordGifPackets(u32 mask);

// The file's .data, in retail's order (0x2626E8 to 0x262714): the three object lists.
List01 g_targetCurveList = { 0 };
List01 g_targetPointList = { 0 };
List01 g_partList = { 0 };

void SetObjectListLinkOffsets()
{
    SetListLinkOffset(&g_targetCurveList, 0x38);
    SetListLinkOffset(&g_targetPointList, 0x50);
    SetListLinkOffset(&g_partList, 0x558);
}

void ClearObjectLists()
{
    ClearList(&g_targetCurveList);
    ClearList(&g_targetPointList);
    ClearList(&g_partList);
}

void InitTargetCurve(TargetCurve* self)
{
    InitObject(self);
    self->targetId = -1;
    self->f4C = 1;
    self->f50 = 3;
    self->f58 = 3.4028235e+38f;
}

void RegisterTargetCurve(TargetCurve* self)
{
    RegisterObject(self);
    AppendToList(&g_targetCurveList, self);
}

void UnregisterTargetCurve(TargetCurve* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetCurveList, self);
}

void PostLoadTargetCurve(TargetCurve* self)
{
    if (self->targetId != -1) {
        TargetedObject* r = (TargetedObject*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

void CopyTargetCurve(TargetCurve* self, TargetCurve* src)
{
    PathCurveKeptBits saved = self->keep;
    CopyObjectData(self, src);
    self->keep = saved;
}

f32 WrapAngle(f32 a);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

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
        Vu0::Q(*out) = Vu0::MulAddX(base, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(tangent), Vu0::Q(g_unitZVector)), Vu0::Q(D_00248D30)), k);
    }
    if (angleOut) {
        *angleOut = ArctangentOfRatio(-tangent.x, tangent.y);
        if (self->mode40 == 1) {
            *angleOut = WrapAngle(*angleOut + 3.14159274f);
        }
    }
}

void FindTargetCurveLengthNearCollider(TargetCurve* self, f32* out, void* a2, void* a3)
{
    CurveProbe f;
    u8* node = (u8*)GetActiveSwitchedCollider();
    PathCurve* o = self->curve;
    f.c = 1;
    TransformPointBetweenFrames(0, (PlacedObject*)self->parent, (Vec02*)(node + 0x140), (Vec02*)&f.a);
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

void InitTargetPoint(TargetPoint* self)
{
    InitObject(self);
    f32 k = 3.4028235e+38f;
    self->targetId = -1;
    self->f68 = 1;
    self->f70 = k;
}

void RegisterTargetPoint(TargetPoint* self)
{
    RegisterObject(self);
    AppendToList(&g_targetPointList, self);
}

void UnregisterTargetPoint(TargetPoint* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetPointList, self);
}

void PostLoadTargetPoint(TargetPoint* self)
{
    if (self->targetId != -1) {
        TargetedObject* r = (TargetedObject*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

void CopyTargetPoint(TargetPoint* self, TargetPoint* src)
{
    KeptBits saved = self->keep;
    CopyObjectData(self, src);
    self->keep = saved;
}

void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);
f32 WrapAngle(f32 a);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

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

void PlaceTargetPointNearCollider(TargetPoint* self, Vec02* out, f32* angleOut)
{
    Vec02 here;
    Vec02 d;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    ConvertPositionToWorld(self, &here);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(active->v140), Vu0::Q(here));
    PlaceOnTargetPoint(self, out, angleOut, ArctangentOfRatio(d.y, d.x) * self->radius5C);
}

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

void AddToPartList(ListedCollisionPart* self)
{
    RegisterCollider(self);
    AppendToList(&g_partList, self);
}

void RemoveFromPartList(ListedCollisionPart* self)
{
    UnregisterCollider(self);
    RemoveFromList(&g_partList, self);
}

void CopyKeepingListLink(ListedCollisionPart* self, ListedCollisionPart* src)
{
    Link02 tmp = self->listLink;
    CopyCollider(self, src);
    self->listLink = tmp;
}

s32 TestListedCollisionPartMayContact(Collider* a0, Collider* a1)
{
    if ((void*)a1 == g_player && (void*)a0 == ((Player*)a1)->heldObject) {
        return 1;
    }
    return TestCollidersMayContact(a0, a1);
}

void StepListedCollisionPart(ListedCollisionPart* self, f32 t)
{
    Mat3U buf;

    StepCollider(self, t);
    if (self->skipSteering != 0) {
        return;
    }
    RotateMatrixUpright(&self->rot, 0, (Mat02*)&buf);
    SteerColliderTowardRotation(self, (Mat02*)&buf, (f32*)self->p214, (Vec02*)&D_00248D30, (f32*)self->p218, t);
}

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
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
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

void* GetActiveSwitchedCollider(void);
f32 WrapAngle(f32 a);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

void FindRingPointTowardCollider(PlacedObject* self, Vec02* out, f32* angleOut)
{
    Vec02 d;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    u128 p = Vu0::Q(self->v140);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(active->v140), p);
    d.z = 0.0f;
    if (out) {
        u128 k = Vu0::Scalar(*(f32*)((u8*)self + 0x560) + 70.0f);
        Vu0::Q(*out) = Vu0::MulAddX(p, Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)), k);
    }
    if (angleOut) {
        *angleOut = WrapAngle(ArctangentOfRatio(d.y, d.x) + 3.14159274f);
    }
}
