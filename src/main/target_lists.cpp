// SPDX-License-Identifier: AGPL-3.0-or-later
// The target lists, 0x169C58 to 0x16AA18 (its .rodata from 0x24A794, its .data from 0x2626E8):
// the three object lists SetObjectListLinkOffsets sets up and their classes, the target curve
// (0x6F), the target point (0x7F) and the listed collision part (0x3A), then the pooled
// children's hold helpers and FindRingPointTowardCollider. Its end is file_16AA18.cpp's proved
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

void DrawAgent(void);

struct GatheredEventObject { u8 pad0[0x328]; s32 f328; };
struct GatheredObjects { s32 count; GatheredEventObject** items; };

void StartAgent(void* self);
void* FindFirstObjectByIdMode4(void* a, s32 b, void* c);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherAnimationEventObjects(void* a, void* b, s32* c, void** d);
void* CreateRecord2505C0(void);
void AppendToSmallList(void* a, void* b);

void InitAgent(void* self);
void InitConeAgent(ConeAgent* self);

void UnregisterCollider(void* self);
void RemoveFromList(void* data, void* self);

void CopyCollider(void* self);

s32 TestCollidersMayContact(Collider* a, Collider* b);

void* FindFirstObjectByIdMode4(void* obj, s32 id, s32 flags);

void SendDisplayResetPacket(void);
void SignalDisplaySync(void);
void ResetGs(s32 a0, s32 a1, s32 a2, s32 a3);
void SetFieldDrawOffset(void* p, s32 a1, s32 a2, s32 a3);
void SyncDataCache(s32 a0);
s32 SwapDoubleBuffer(void* p, s32 a1);

struct DmaChainBlock { u8 bytes[0x20]; };

extern u8 D_002BE1A0[];
void* InitPacketBuffer(DmaChainBlock* a);
void UsePacketBufferMemory(DmaChainBlock* a, s32 n, DmaChainBlock* b);
void AddDmaRefTag(DmaChainBlock* a, s32 n, void* table);
void AddDmaEndTag(DmaChainBlock* a);
void DetachPacketBuffer(DmaChainBlock* a, s32 x, s32 y);
void SendPacketToBothBuffers(DmaChainBlock* b);

struct TexturePacket : PacketWriter { s32 value; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;
extern s32 g_gifChannel;

void* InitGifPacket(PacketWriter* f);
void AllocateTempPacketBuffer(PacketWriter* f, s32 size);
void BeginDmaTag(PacketWriter* f);
s32 PlaceMaskedImages(void* self, void* arg, TexturePacket* f);
void BeginGifTag(PacketWriter* f, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(PacketWriter* f, s32 a, u64 b);
void EndGifPacket(PacketWriter* f);
void AddDmaEndTag(PacketWriter* f);
void DetachPacketBuffer(PacketWriter* f, s32 a, s32* out);
void SendGsPacketAndWait(s32 a, s32 b);

extern FrameTarget D_0027DC20[];

void RegisterObject(void* self);
void AppendToList(void* table, void* self);

void UnregisterObject(void* self);
void RemoveFromList(void* table, void* self);

struct TargetedObject {
    u8 pad_00[0x398];
    s32 f398;
};

void* FindFirstObjectByIdMode4(void* a, s32 b, s32 c);

void CopyObjectData(void* self);

void InitCollider(void* self);
void SetScaledRotationSpring(void* self, f32 k);
void SetScaledSpinSpring(void* self, f32 k);
void SetScaledPositionRamp(void* self, f32 k);
void SetScaledRotationRamp(void* self, f32 k);

void RegisterCollider(void* self);

void BeginGifTag(void* p, s32 a, s32 b, s32 c);
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

void SetListLinkOffset(void* self, s32 value);

void ClearList(void* self);


void SubmitMeshQueueEntry(void* p);
void* AllocateZeroedFrontMemory(u32 n);


extern u8 D_002BDC20[];
extern u8 D_002BE1A0[];
extern u8 D_002BDEE0[];

void SetUpDoubleBuffer(void* p, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void FillScreenColor(void* ctx, Rgba4* v, s32 flag);
s32 CreateLockSemaphore(void* a, void* b);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);
s32 EnableInterruptCause(s32 a0);
void InitMeshQueue(void);
void ResetDisplayBuffers(void);
s32 HandleVblankStart(s32 cause);
s32 HandleGsFinish(s32 cause);

extern s32 g_gifChannel;

s32 SendDrawEnvironment(void* p);
void StartDmaChain(s32 a, void* b);
s32 WaitDmaChannel(s32 a, s32 b, s32 c);

void InitBumpAllocator(BumpAllocator*,s32,s32);

void ApplyFieldDisplayOffset(void);
s32 WaitGsPaths(s32 a0, s32 a1);

struct TextureUploadPacket : PacketWriter { u8 span[0x10]; s32 out; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void InitBumpAllocator(void* p, s32 a, s32 b);
s32 PlaceMaskedImages(void* self, void* arg, TextureUploadPacket* f);
void DetachPacketBufferCopy(PacketWriter* f, s32 a1, s32 a2, s32* out, s32 a4);
void BuildAnimRecordGifPackets(void* self);

struct FadePacket : PacketWriter { s32 value; u8 pad[0x3F0]; };

extern s32 g_gifChannel;

void UsePacketBufferMemory(PacketWriter* f, s32 n, s32* p);
void WriteColoredSpritePacket(f32 x, f32 y, f32 z, f32 w, s32 a, s32 b, s32 c, s32 d, FadePacket* e);
void DetachPacketBuffer(PacketWriter* f, s32 a, s32 b);
void SendGsPacketAndWait(s32 a, s32* b);
void FlipDisplayFrame(void);

extern s32 g_imageRecordCountA;
extern s32 g_imageRecordCountB;
s32 AllocateBump(void* self, s32 size);
void BuildPaletteTexRegister(PaletteRecord* e, s32 v);
void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx);
void AddDmaRefTag(void* self, s32 lo, s32 hi);
void BuildImageTexRegister(ImageRecord* e, s32 v);
void StartImageUpload(ImageRecord* e, s32 v, void* ctx);


void* IsObjectOfKind(void* node, s32 flags);

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

void InitObject(void* self);

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
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, void* d);
void PlaceOnTargetCurve(void* a0, void* a1, void* a2, f32 f);

struct HoldMatrices {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    u8 e[0x10];
};

extern f32 g_gameTime[];

void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void TriggerScriptEvent(void* obj, s32 kind, s32 a, s32 b);
void RotateMatrixUpright(void* sub, void* a, void* out);
void MatrixToAxisAngle(void* a, void* b, void* c);
void MultiplyMatrices3x3(void* a, void* b, s32 c);


// The start of what a queue entry copies: two GIF tags whose words func_001694A0 marks (bit
// 15) when the entry has a flag.
struct QueuedGifTags {
    s32 f0;
    u8 pad0[0xC];
    s32 f10;
};

void CopyMemory(QueuedGifTags* dst, void* src, s32 count);

s32 GetGsInterruptMask(void);
s32 SwapGsInterruptMask(s32 a);
void SyncDataCache(s32 a);
s32 AwaitSemaphore(s32 a);

void LoadCollider(Collider* self);
void* AllocateZeroedFrontMemory(s32 bytes);

void StepCollider(Collider* self, f32 t);
void RotateMatrixUpright(Mat02* sub, s32 zero, Mat3U* out);
void SteerColliderTowardRotation(Collider* self, Mat3U* out, s32 a, void* table, s32 b, f32 t);
extern f32 g_gameTime[];

struct TransferBase { s32 v; };

void BeginImageTransfer(TransferBase dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void UsePacketBufferMemory(PacketWriter* f, s32 n, PacketWriter* p);

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

void InitBumpAllocator(BumpAllocator* p, s32 a, s32 b);
void* InitPacketWriter(PacketWriter* f);
void WriteVifFlush(PacketWriter* f);
void RewindPacketBuffer(PacketWriter* f);
void UsePacketBufferMemory(PacketWriter* f, s32 n, u8* buf);
s32 AllocateBump(BumpAllocator* p, s32 size);
void StartPaletteUpload(PaletteRecord* e, s32 v, PacketWriter* f);
void StartImageUpload(ImageRecord* e, s32 v, PacketWriter* f);
void DetachPacketBuffer(PacketWriter* f, s32* o0, s32* o1);
void WriteVifDirect(PacketWriter* f, s32 a, s32 b, s32 c);
void WriteVifDirectRef(PacketWriter* f, s32 a, s32 b, s32 c);
void CloseDmaTag(PacketWriter* f);
void DetachPacketBufferCopy(PacketWriter* f, s32 a, s32 b, s32* out, s32 c);
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

void CopyTargetCurve(TargetCurve* self)
{
    PathCurveKeptBits saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

f32 WrapAngle(f32 a);
f32 ArctangentOfRatio(f32 y, f32 x);

void PlaceOnTargetCurve(TargetCurve* self, Vec02* out, f32* angleOut, f32 t)
{
    Vec02 pos;
    Vec02 tangent;
    PathCurve* o = self->curve;
    if (o->vt->m02 != 0) {
        ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, t, &pos, &tangent);
    }
    TransformPointBetweenFrames(self->parent, 0, &pos, &pos);
    TransformDirectionBetweenFrames(self->parent, 0, &tangent, &tangent);
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
    TransformPointBetweenFrames(0, (s32)self->parent, node + 0x140, &f.a);
    TransformDirectionBetweenFrames(0, (s32)self->parent, (void*)&g_unitZVector, &f.b);
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
    PlaceOnTargetCurve(self, a2, a3, f.x);
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

void CopyTargetPoint(TargetPoint* self)
{
    KeptBits saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void ComputePolarOffset(Vec02* out, f32 x, f32 y, f32 z);
f32 WrapAngle(f32 a);
f32 ArctangentOfRatio(f32 y, f32 x);

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
        ComputePolarOffset(&offset, angle, radius, 0.0f);
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

void LoadListedCollisionPart(ListedCollisionPart* self)
{
    Rec2195_224* b;
    Quad16* dst;
    Quad16* src;

    LoadCollider(self);
    if (self->f224 == 0) {
        self->f224 = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);

    }
    b = self->f224;
    b->fB0 |= 1;
    dst = (Quad16*)self->f224;
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

void CopyKeepingListLink(ListedCollisionPart* self)
{
    Link02 tmp = self->listLink;
    CopyCollider(self);
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
    if (self->f550 != 0) {
        return;
    }
    RotateMatrixUpright((Mat02*)((u8*)self + 0xD0), 0, &buf);
    SteerColliderTowardRotation(self, &buf, (s32)self->p214, (void*)&D_00248D30, (s32)self->p218, t);
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
        RotateMatrixUpright((u8*)g_player + 0x110, 0, f.a);
        RotateMatrixUpright((u8*)self + 0x110, f.c, f.b);
        MatrixToAxisAngle(f.c, f.e, f.d);
        MultiplyMatrices3x3(f.a, f.b, (s32)self->f224);
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
        if (IsObjectOfKind(node, 70)) {
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
        if (IsObjectOfKind(node, 0x46)) {
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
f32 ArctangentOfRatio(f32 y, f32 x);

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
