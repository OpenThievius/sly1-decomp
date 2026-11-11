// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "id_lookup_object.h"
#include "placed_object.h"
#include "world.h"
#include "animation.h"
#include "sound_record.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "list_iter.h"
#include "packet_writer.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "keyed_entry.h"
#include "identity_key.h"
#include "strip_mesh.h"
#include "vertex_batch.h"
#include "shapes.h"
#include "word_copy.h"
#include "camera.h"


void RegroupQueuedObjects(void* self);
void UpdateGroupsNearCamera(World* self);


void RemoveValueFromArray(void* list, void* base, void* item);
void DissolveObjectLinkList(void* self, void* value);

struct VisitClass { u8 pad0[8]; s32 flags; u8 pad1[0x54]; void (*visit)(void* self, void* arg); };
struct VisitNode { VisitClass* cls; u8 pad0[0x18]; VisitNode* next; u8 pad1[0x14]; VisitNode* child; };



void SpliceListToEnd(void* dst, void* src);
void TransformByMatrixWithW(void* m, f32 w, const void* src, void* out);
void SetColliderAnchors(Collider* self, s32 a, s32 b, s32 c, s32 d);
void FreeTouchNodes(void* owner, Touch03* node);


s32 IsObjectAttached(void* p);
void MergeObjectLinkLists(void* ctx, void* a, void* b);


void MergeObjectGroupMembers(void* self, FoundList* group);

struct CountedArray
{
    s32 count;
};

void* MoveMemory(void* dst, void* src, s32 bytes);


void MergeObjectGroupMembers(void* self, void* item);

extern u8 D_00248D30[];

void StopSoundRecord(void* self, s32 n);
void StartSoundEffect(void* a0, void* a1, void* a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, s32 a5);

void StartObject(BaseObject* self);
void* AllocateFrontMemory(s32 size);
s32 FindFirstObjectByIdMode1(World* world, s32 item, void* c);
void RegisterObjectGroup(World* world, FoundList* sub);


struct LinkListWalk {
    List01* list;
    u8* link;
    s32 offset;
    LinkListWalk* prev;
};


void RemoveFromList(List01* list, PlacedObject* node);
void QueueObjectForRegroup(void* self, PlacedObject* node);

struct BeginLinkListWalk {
    static void Of(LinkListWalk* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (LinkListWalk*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)it;
    }
};

struct NextInLinkList {
    static PlacedObject* Of(LinkListWalk* it)
    {
        PlacedObject* obj = *(PlacedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

void* FindEntryById();

s32* GetLevelEntryByKey();

struct RefCounted
{
    u8 pad[4];
    s32 refs;
};


void CountGifEntry(void* self, s32 a1, s32 a2);


struct EntryFlags { u8 pad0[0x28]; s32 f28; };

EntryFlags* FindEntryById(void* a0);

s32 ComputeCompletionMask(void);

extern s32 g_previousLevelIndex;
extern u8 g_flagTable[];

s32 GetEntryIdByKey(s32 a0);
void ResetReserveCounts(void);
void RestoreFlagTableSnapshot(u8* p);
void ResetFlagTable(u8* p);
void ResetGameSession(void);


void* AllocateFrontMemory(s32 size);

struct RefItem { u8 pad[0x38]; void* ref; u8 rest[0x70 - 0x3C]; };

struct RefOwner
{
    u8 pad0[0xC];
    s32 count;
    RefItem* items;
    u8 pad1[0x50 - 0x14];
    s32 capacity;
    void** refs;
};

void* FillMemory(void* p, s32 value, s32 size);

struct Counter
{
    u8 pad[4];
    s32 count;
};


extern World* g_currentWorld;

void FreeObjectMemory(void);

void FlushVertexBatch(void* self);
void BuildMatrixFromRotationAndTranslation(void* a, void* b, void* c);
void InvertRigidTransform(void* a, void* b, void* c);

struct ColoredVertexBatch {
    u8 pad0[0xF8];
    s32 f0F8;
};

void FlushVertexBatch(void* self);
void SetVertexColor(void* self, u32* value);

KeyedEntry* FindKeyEntry(void);


extern u8 g_scatterController[];
extern U32P D_00269984;
extern s32 g_buttonCodeFlags;
extern s32 g_previousLevelIndex;

void ResetGameProgress(void* self);
void ClearTwoWords(void* self);
void ClearScatterController(void* self);
void ResetReserveCounts(void);

void CountGifEntry(void* self, s32 a1, s32 a2);


void CountGifEntry(void* self, s32 a1, s32 a2);


void CountGifEntry(void* self, s32 a1, s32 a2);

struct ClearedRecord { u8 pad0[4]; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; };

void BeginGifTag(void* self, s32 a, s32 b, s32 c);



void ResetGameSessionAndFade();

typedef void* (*MemoryFillFn)(void*,s32,s32);

void CountGifEntry(void* self, s32 a1, s32 a2);

void CountGifEntry(void* self, s32 a1, s32 a2);

struct KeyedPointSet { u8 pad0[4]; s32 count; u8* base; };
struct KeyedEdge { s16 k0; s16 k1; u8 pad[4]; KeyedEdge* next; };
struct EdgeHolder { u8 pad0[0x14]; KeyedEdge* head; };
struct ContactHit { EdgeHolder* holder; u8 pad[8]; };

void PushBackMemoryMark(void);
u8* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);
s32 QueryPlaneTreePoint(u8* a0, u8* a1, s32* a2, f32 scale);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void WriteVifMscal(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void WriteVifMscal(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void WriteVifMscal(void* obj, void* data);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void WriteVifMscal(void* obj, void* text);

void ApplyPadPatternSetting(void* self);

// the key keeps the file's comparison (IdentityKey has no method of its own: the forms differ per file)
struct SessionKey : IdentityKey {
    s32 Same(SessionKey* o)
    {
        if (this == o) {
            return 1;
        }
        if (this == 0) {
            return 0;
        }
        if (o == 0) {
            return 0;
        }
        return ((signedWords[2] ^ signedWords[6]) ^ (o->signedWords[2] ^ o->signedWords[6])) == 0;
    }
};

struct PlayerListWalk;

struct AnimationPlayerList {
    void* head;
    s32 pad4;
    s32 next_off;
};

struct PlayerListWalk {
    void* list;
    void* cursor;
    s32 next_off;
    PlayerListWalk* prev;
    PlayerListWalk(AnimationPlayerList* l)
    {
        list = l;
        cursor = l;
        next_off = l->next_off;
        prev = (PlayerListWalk*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~PlayerListWalk() { g_activeListFrames = (ListFrame*)prev; }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + next_off;
        return n;
    }
};

struct ElementStackState { u8 pad0[0x30]; s32 f30; };
extern ElementStackState g_elementStack;
extern SessionKey D_00247AB0;
extern s32 D_00275F84;

SessionKey* LookupEntryById(s32 key);
void ClearTwoWords(void* p);
void StartObjectFade(void* a, s32 b, s32 c);
void SilenceVolumeChannel3(s32 flag);
void ApplySoundOptionFlag(s32 flag);
Animation* FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void StopAnimationPlayer(void* obj);
void SetElementStackState(void* obj, s32 mode);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void WriteVifMscal(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void WriteVifMscal(void* s, s32 n);

void ResetFlagTable(void* p);

extern u8 g_flagTable[];


extern u8 g_scatterController[];
extern u8 g_flagTable[];
extern u8 g_pauseMenuElement[];

void PopActiveSequenceElement(void* x);
void StopLockedStreamVoice(void);
void StartScreenFade(void* dst, FadeRequest* args, s32 count);
void StartScreenFadeFromFlagTable(void* r);
void SetPauseMenuLayerPage(void* self, s32 a, s32 b);
void RaiseScatterLevels(void* self, f32 amount);


u32* GetLevelEntryByKey(void* key);


extern u8 D_00247AD0[];

void StartObjectFade(void* obj, s32 m, s32 n);
void QueueMovieWithSuccessor(s32 slot, u32 n);


void ResetGameSession(void);
void StartObjectFade(void* obj, s32 value, s32 count);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table g_gifPacketMethods[];
s32 InitPacketBuffer(PacketWriter* a);

void ApplyCompletionFlags(s32 mode);

// EXACT: self->block store ahead of self->f20 store.

struct MorphTargetHeader
{
    u16* p;
    s32 count;
};
// Built at startup: the compiler's initialiser and constructor for this file are func_00167D20
// and func_00167D48 (config/us/generated.tsv).
struct ColorWord
{
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
    ColorWord(u32 v) { rgba = v; }
};

// The file's .data, in retail's order. It begins with the game progress pointers
// (game_progress.h), which this file's functions read and file_1549C8's do not.
GameProgress* g_saveData = &D_0027C220;
G27C230* g_currentLevelRecord = D_0027C230;
G27C230* g_currentEntry = D_0027C230;
s32 g_previousLevelIndex = -1;
char D_002623D0[8] = "<none>";
u8 D_002623D8[4] = { 0 };
s32 D_002623DC = 0;
ColorWord D_002623E0(0x80101010);
s32 D_002623E4 = 1;
s32 D_002623E8[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 D_00262400[6] = { -1, 0, 4, 8, 12, 0 };
s32 D_00262418[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 D_00262430[6] = { -1, 0, 4, 8, 12, 0 };
s32 D_00262448[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 D_00262460[5] = { -1, 0, 4, 8, 12 };
s32 D_00262474 = 0x28;
extern u8 D_00001298[];
extern u8 D_00001368[];
extern u8 D_00000ED8[];

void ReserveVifUnpack(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* FillMemory(void* p, s32 value, s32 size);
void AllocateTempPacketBuffer(PacketWriter* f, s32 size);
void BeginGifTag(PacketWriter* f, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(PacketWriter* f, s32 a, u64 b);
void CloseGifTag(PacketWriter* f, s32 n);
void CopyWordsToWriter(PacketWriter* s, s32 a, s32 b, void* data, s32 flags);
void RewindPacketBuffer(PacketWriter* f);
void AddGifXyzfEntry(PacketWriter* f, s32 a1, s32 a2, s32 a3, s32 a4);
void WriteVifStrow(PacketWriter* s, u32* src);
void WriteVifStmask(PacketWriter* s, s32 value);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void WriteMorphTargetMscal(s32 mode, PacketWriter* obj);

struct QuadClear
{
    static void Clear(u32* q)
    {
        FillMemory(q, 0, 0x10);
    }
};

struct PercentClamp {
    static s32 Of(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) return lo;
        if (v > hi) return hi;
        return v;
    }
};

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.

struct FlushedVertexBatch { u8 pad0[0xF8]; u8* f0F8; u8 pad1[0x28]; s32 f124; };

extern PacketWriter g_vifPacketWriter;
extern u8 D_000018C0[];

void FlipVifBaseOffset(void);
s32 WriteVifUnpackHeader(PacketWriter* s, s32 a, s32 b, s32 c);
void ResetVertexBatch(FlushedVertexBatch* self);
void BuildUnlitVertexPacket(FlushedVertexBatch* self);
void BuildLitVertexPacket(FlushedVertexBatch* self);

struct __attribute__((packed)) BatchVertexWords {
    u64 q0;
    u64 q8;
    u64 q10;
    u64 q18;
    s32 f20;
    s32 value;
    BatchVertexWords() {}
};

struct AppendVertexBatch {
    u8 pad0[0xF8];
    u8* pF8;
    BatchVertexWords cur;
    s32 count;
    BatchVertexWords recs[1];
};

void CopyMemory(BatchVertexWords* dst, const void* src, s32 size);
void FlushVertexBatch(AppendVertexBatch* self);
void SetVertexBatchMode(AppendVertexBatch* self, u8* value);

struct DrawMesh;
// A point and a fourth word, as the vertex packets write them.
struct VifPoint { Vec3 v; f32 w; };
struct UnlitVertex { Vec3 v; u8 pad[0xC]; u8 rgba[4]; f32 f1C; f32 f20; s32 f24; };
struct UnlitVertexBatch {
    u8 pad[0x80];
    f32 f80;
    u8 pad2[0xF8 - 0x84];
    DrawMesh* fF8;
    u8 pad3[0x124 - 0xFC];
    s32 f124;
    UnlitVertex e[1];
};
struct UnlitUnpackHeader { u16 f0; u16 f2; u8 pad[4]; u16 f8[4]; u16 f10; u8 pad3[6]; };
struct CopiedGifTags { u32 w[8]; };

void* FillMemory(void* p, s32 value, s32 size);
extern u8 D_00001A50[];
extern u8 D_000002F8[];
void CopyMemory(CopiedGifTags* dst, u8* src, s32 n);

// A run of bytes, for the fill and copy calls.
struct ByteSpan { u8 b[1]; };
struct LitUnpackHeader { u16 f0; u16 f2; u8 pad4[4]; u16 f8[3]; u16 fE; u16 f10; u8 pad12[6]; };
struct LitVertex
{
    Vec3 pos;
    f32 nx, ny, nz;
    u8 col[4];
    f32 u, v;
    s32 flag;
};
// The mesh the two vertex-packet builders draw (the layout of StripMesh): its colour, its
// frames of packet data and the cursor whose frame picks one.
struct MeshFrameCursor { u8 pad[0x18]; s32 n; };
struct MeshFrameData { s32 n; u8* data; };
struct DrawMesh
{
    u8 pad0[4];
    u8 col[4];
    u8 pad8[0x10];
    s32 count;
    MeshFrameData* ents;
    u8 pad20[4];
    MeshFrameCursor* sub;
};
struct BatchTexture { u8 pad[0x418]; s32 n; u8 pad41C[4]; u8 data[1]; };
struct LitVertexBatch
{
    u8 pad0[0x80];
    f32 base;
    u8 pad84[0x30];
    s32 texCount;
    BatchTexture* tex[16];
    DrawMesh* mesh;
    u8 padFC[0x28];
    s32 n;
    LitVertex verts[1];
};

extern u8 D_00000288[];
extern u8 D_00001210[];
extern u8 D_00001AB0[];
extern u8 D_00000010[];

void ReserveVifUnpack(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* FillMemory(void* p, s32 value, s32 size);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifMscalf(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void CloseDmaTag(PacketWriter* s);
void AddDmaRefTag(PacketWriter* s, s32 n, void* data);
void BeginDmaTag(PacketWriter* s);
void CopyMemory(ByteSpan* dst, void* src, s32 count);

struct MeshUv {
    f32 u;
    f32 v;
};
// A vertex's indices into the position, normal and uv arrays, and its flags.
struct VertexRefs {
    u8 pos;
    u8 nrm;
    u8 uv;
    u8 flags;
};
// A weight's two index lists: the positions it moves, then the normals.
struct WeightIndices {
    u16* pos;
    u16* nrm;
};
struct MeshBuildState {
    u8 pad00[0x40];
    s32 f40;
};
struct StripMeshInfo {
    u8 pad00[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
};
struct CursorHook;
typedef AnimCursor* (*CursorHookFn)(CursorHook* self, StripMesh* mesh);
struct CursorHook {
    CursorHookFn* vt;
};
struct StripMeshOwner {
    u8 pad00[0x18];
    s32 f18;
    u8 pad1C[0x28 - 0x1C];
    s32 f28;
    u8 pad2C[0x38 - 0x2C];
    CursorHook* f38;
    u8 pad3C[0x40 - 0x3C];
    f32 f40;
    u8 pad44[0x54 - 0x44];
    StripMeshInfo* f54;
};
struct StripExtra {
    s32 f0;
    s32 a4[4];
    s32 a14[4];
    s32 a24[4];
};
struct StripUnpack {
    u16 off[4];
    u16 strip[4];
    u16 f10;
    u16 f12;
    u16 pad14[2];
};
struct StripHeader {
    u8 pad00[0x14];
    u32 f14;
    u8 pad18[0x1C - 0x18];
    StripUnpack* p;
    StripExtra* extra;
    s32 count;
};

extern u8 D_000002F8[];
extern u8 D_00001A50[];
extern u8 D_000036D0[];
extern u8 D_00001A80[];
extern u8 D_000027C0[];
extern u8 D_00002008[];
extern u8 D_000023B8[];
extern u8 D_00003A80[];
extern u8 D_00003A90[];

void BeginDmaTag(PacketWriter* pkt);
void CloseDmaTag(PacketWriter* pkt);
void AddDmaReturnTag(PacketWriter* pkt);
void ReserveVifUnpack(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* FillMemory(void* p, s32 value, s32 size);
void WriteVifStcycl(PacketWriter* s, s32 a, s32 b);
void WriteVifStrow(PacketWriter* s, u32* src);
void WriteVifStmask(PacketWriter* s, s32 value);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifMscalf(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void CopyWordsToWriter(PacketWriter* s, s32 a, s32 b, void* data, s32 flags);
void WriteVifUnpack(PacketWriter* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* AllocateZeroedFrontMemory(s32 bytes);
void WriteStripMeshMscal(s32 mode, PacketWriter* pkt);
void QueueNodeLink(s32 a, s32 b, AnimCursor* node);
void QueueMeshStrip(StripMesh* mesh, FrameSource* strip, s32 a, s32 b, s32 n, AnimCursor* node);

void WriteVifBaseOffset(void* obj, s32 size, s32 flags);

void ApplyLinkConstraint(void*);

typedef void (*AttachmentHandlerFn)(void* self);
struct AttachmentHandler { AttachmentHandlerFn* vtbl; };
struct AttachmentEntry { u8 pad0[0x38]; AttachmentHandler* f38; u8 pad1[0x70 - 0x3C]; };
struct AttachmentNode { u8 pad0[4]; void* f4; s32 f8; u8 pad1[0x80 - 0xC]; AttachmentNode* next80; };
struct AttachmentBlock { u8 pad0[0xC]; s32 count0C; AttachmentEntry* f10; u8* f14; u8 pad1[0x4C - 0x18]; AttachmentNode* f4C; };

void BuildAttachmentDmaChain(void* self, void* entry, void* sub, void* ctx);
void AttachNodeToOwner(void* owner, void* unused, void* ctx);

// Four quadwords: a matrix as the attachment code copies it.
struct QuadMatrix { Quad16 q[4]; };
struct TargetObject { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct AttachmentTarget { TargetObject* p0; u8 pad0[0xC]; QuadMatrix m; u8 tail[0x90 - 0x50]; };
struct AttachmentTargets { s32 count; AttachmentTarget* elems; s32* keys; };
struct TargetFrames { Quad16 a; u8 pad0[0x30]; Quad16 b; u8 pad1[0x30]; QuadMatrix m; };

void* FindFirstObjectByIdMode4(void* a, s32 b, void* c);
void BuildMatrixFromRotationAndTranslation(void* a, void* b, void* out);
void InvertRigidTransform(void* a, void* b, void* out);
void MultiplyMatrices(void* out, void* b, void* in);

struct AnimatorStep;
typedef void (*AnimatorStepFn)(void* self, f32 f);

struct AnimatorStep {
    AnimatorStepFn* vtbl;
    u8 pad4[0x8];
    void* f0C;
    u8 pad10[0x70];
    AnimatorStep* next80;
};

struct AnimatorOwner {
    u8 pad0[0x4C];
    AnimatorStep* head4C;
};


s32 ClaimAnimatorStep(void* p);
void EvaluateOscillator(void* p);

extern u8 D_00000010[];
extern u8 D_000000F0[];

struct PartPacketContext { u8 pad0[0x28]; s32 f28; };
struct PartRange { u16 lo; u16 hi; };
struct PartPacketSource { u8 pad0[0x18]; u8* f18; PartRange* f1C; };
struct PartPackets { void* f0; void* f4; void* f8; void* fC; void* f10; void* f14; };

void* InitPacketWriter(void* p);
void AllocateQuadwordBuffer(void* buf, u32 count, u32 kind);
void WriteVifStcycl(void* b, u32 x, u32 y);
void ReserveVifUnpack(void* s, u32 tag, s32 size, s32 a3, void* a4, void* a5);
void WriteVifMscal(void* s, void* n);
void DetachPacketBuffer(void* self, void* a, void* b);

struct AttachmentLink { s32 tag; AttachmentLink* p4; u8 pad8[0x48]; void* p50; void* p54; u8 pad58[0x28]; AttachmentLink* next; u8 pad84[0xC]; };
struct AttachmentPartInfo { u8 pad[0x10]; u32 flags; };
struct AttachmentPart { u8 pad[0x38]; AttachmentPartInfo* a; u8 pad3C[0x18]; void* b; };
struct AttachmentCopy { s32 n0; void* p4; u8 pad8[4]; s32 count; AttachmentPart* recs; void* p14; u8 pad18[0x28]; s32 n40; void* p44; u8 pad48[4]; AttachmentLink* head; s32 f50; };

void CopyMemory(AttachmentCopy* dst, void* src, s32 n);
void* AllocateZeroedFrontMemory(s32 n);
void* CopyToFrontMemory(s32 size, void* src);
void CopyAttachmentPart(AttachmentCopy* o, void* a, void* b);
void CollectNonNullRefs(AttachmentCopy* o);

// Index written (i << 4) * 9: a plain &items[i] gives a mult that loop.c does not strength-reduce (no s4 offset giv).
struct FramedObject;
typedef void (*FramedObjectFn)(FramedObject* self);
struct FramedObjectVt { u8 pad[0xC0]; FramedObjectFn f; };
struct FrameLinkConstraint { u8 pad0[0x60]; QuadMatrix m60; u8 pad[4]; s32 a4; u8 pad2[8]; u32 flags; };
struct FramedObject { FramedObjectVt* vt; u8 pad0[0x10C]; u8 sub110[0x30]; u8 sub140[0x40]; u8 pad180[0xA4]; FrameLinkConstraint* link; };
struct FramedAttachment { FramedObject* obj; u8 pad[0xC]; Quad16 q10[4]; QuadMatrix m50;  };
struct FramedAttachmentList { s32 count; FramedAttachment* items; };
struct ParentFrame { u8 pad[0x30]; };

void InvertRigidTransform(void* a, void* b, void* out);
void BuildMatrixFromRotationAndTranslation(void* a, void* b, void* out);
QuadMatrix MultiplyMatrices(QuadMatrix a, void* q);

// The lit strip builder's packets: 0x24-byte slots, written two apart.
struct PacketSlot {
    u8 pad[0x24];
};
struct QuadLanes {
    f32 x[4];
    f32 y[4];
    f32 z[4];
    f32 w[4];
};

extern u8 D_00000288[];
extern u8 D_00001AB0[];
extern u8 D_00002008[];
extern u8 D_00002088[];
extern u8 D_000023B8[];
extern u8 D_000023D8[];
extern u8 D_000023F0[];
extern u8 D_000027C0[];
extern u8 D_00003A80[];
extern u8 D_00003AA0[];

void BeginDmaTag(PacketSlot* pkt);
void CloseDmaTag(PacketSlot* pkt);
void AddDmaReturnTag(PacketSlot* pkt);
void ReserveVifUnpack(PacketSlot* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* FillMemory(void* p, s32 value, s32 size);
void WriteVifStcycl(PacketSlot* s, s32 a, s32 b);
void WriteVifStrow(PacketSlot* s, u32* src);
void WriteVifStmask(PacketSlot* s, s32 value);
void WriteVifMscal(PacketSlot* s, void* data);
void WriteVifFlushE(PacketSlot* s);
void CopyWordsToWriter(PacketSlot* s, s32 a, s32 b, void* data, s32 flags);
void WriteVifUnpack(PacketSlot* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* AllocateZeroedFrontMemory(s32 bytes);
void WriteStripMeshMscal(s32 mode, PacketSlot* pkt);
void QueueNodeLink(s32 a, s32 b, AnimCursor* node);
void QueueMeshStrip(StripMesh* mesh, FrameSource* strip, s32 a, s32 b, s32 n, AnimCursor* node);

void QueueObjectForRegroup(World* owner, u8* obj);
void MergeObjectLinkLists(void* ctx, PlacedObject* self, PlacedObject* other);
void DissolveObjectLinkList(void* self, PlacedObject* owner);
void MergeObjectGroupMembers(void* self, FoundList* group);
void RegisterObjectGroup(void* self, FoundList* group);
void RemoveValueFromArray(CountedArray* list, s32* arr, s32 value);
void UnregisterObjectGroup(void* self, FoundList* s);
void RegroupQueuedObjects(World* self);
void VisitObjectTree(VisitNode* self, void* arg);
s32 GetPlacedObjectFrozen(PlacedObject* self, s32* out);
void SetPlacedObjectFrozen(PlacedObject* self, s32 flag);
void UpdateWorldObjectLists(void* self);
void AddLookupId(IdLookupObject* obj, s32 value);
void RunResetGameSession();
KeyedEntry* FindKeyEntry(KeyedEntry* key);
void* FindEntryById(s32 key);
void* GetEntryName();
s32 LookupEntryById(void);
s32 GetEntryIdByKey(void);
s32 GetEntryFlags(void* a0);
void CountCategoryFlags(s32 key, s32* a1, s32* a2, s32* a3);
s32 ComputeCompletionMask(void);
void MarkProgressStageFlag(s32 n);
void MarkLevelDone(s32 n);
void ApplyCompletionFlags(s32 mode);
void FadeOutAndQueueMovie(s32 kind);
void ResetGameProgress(GameProgress* self);
s32 ChecksumGameProgress(GameProgress* s);
void SetCurrentLevelEntry(s32 a0, s32 flags);
void AddElapsedTime(f32 dx);
void* GetLevelEntryByKey(s32 key);
s32 GetLevelEntryWord();
void ResetGameSession(void);
void ResetReserveCounts(void);
void ResetGameSessionAndFade(void);
void ResumeAtSavedLevel(void);
s32 ComputeCompletionPercent(u8* p);
void SetSpareCount(s32 value);
s32 HasSpareCount();
void* GetIndexedTargetSlot(u8* self,s32 index);
void ClearTwoWords(void* p);
void ResetCounter(Counter* c);
s32 IncrementCounter(Counter* c);
void ReleaseCounterRef(RefCounted* self);
s32 MaskWorldBitsBySave();
void GetCurrentLevelBit(u32* out);
s32 GetSpareCountLimit(void);
void SpendReserveUnit(void);
void ClearRecordBody(ClearedRecord* self);
s32 CollectEntriesForKey(KeyedPointSet* dst, KeyedPointSet* src, s32 key, s32 maxOut, KeyedEdge** out);
PacketWriter* InitGifPacket(PacketWriter* self);
void EndGifPacket(PacketWriter* self);
void CloseGifTag(PacketWriter* f, s32 n);
s32 CountGifEntry(PacketWriter* obj);
void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, s32* out);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, s32 a3);
void AddGifRgbaEntry(PacketWriter* self, u32 value);
void AddGifUvEntry(PacketWriter* self,s32 a,s32 b);
void AddGifStEntry(PacketWriter* self,f32 a,f32 b,f32 c);
void AddGifXyzEntry(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void AddGifXyzfNoDrawEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void BeginGifRegListTag(PacketWriter* self, u32 a1, u64 a2);
void AddGifRegListFloat(PacketWriter* self, s32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* self, s32 a1, s32 a2);
void AddGifXyzfRegListEntry(PacketWriter* self, s32 a1, s32 a2, u32 a3, u32 a4);
void DestroyVertexBatch(void* self, s32 flag);
void SetVertexBatchTransform(u8* self, void* a1, void* a2);
void ResetVertexBatch(u8* self);
void SetVertexBatchMode(ColoredVertexBatch* self, s32 value);
void BuildUnlitVertexPacket(UnlitVertexBatch* self);
void BuildLitVertexPacket(LitVertexBatch* self);
void FlushVertexBatch(FlushedVertexBatch* self);
void SetVertexPosition(VertexBatch* body, Vec3* v);
void SetVertexColor(u8* dst, u8* src);
void SetVertexTexCoord(VertexBatch* dst, U64P* src);
void AddVertex(AppendVertexBatch* self, s32 value);
void CollectNonNullRefs(RefOwner* owner);
void WriteStripMeshMscal(s32 mode, void* obj);
void WriteMorphTargetMscal(s32 mode, void* obj);
void BuildMorphTargetPacket(MeshBuildState* self, s32 mode, MorphTargetHeader* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, void* data, PacketWriter* pkt);
void BuildStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 mode, StripHeader* hdr, StripMesh* mesh,
                   Vec3* vecs, s32 unused6, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, s32 unused13, f32* weights, PacketWriter* pkt,
                   s32** outs);
void BuildLitStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 unused2, s32 mode, StripHeader* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, PacketSlot* pkt, s32** outs);
void BuildPartVifPackets(PartPacketContext* a, PartPacketSource* b, PartPackets* c);
void StartAttachments(AttachmentBlock* self, PlacedObject* ctx);
void BindAttachmentTargets(AttachmentTargets* self, PlacedObject* ctx);
void CopyAttachmentBlock(AttachmentCopy* self, s32 arg, void* src);
void UpdateAttachments(AnimatorOwner* self, PlacedObject* sub, f32 f);
void UpdateLinkConstraint(PlacedObject* self);
void UpdateAttachmentFrames(PlacedObject* self, ParentFrame* par);
void FlipVifBaseOffset(void);

// The 46 names of the keyed entries (keyed_entry.h; D_00247AF0, which this file's functions
// walk), which begin the file's .rodata, before its functions' own literals.
extern const char D_0024A2D0[8] = "Splash";
extern const char D_0024A2D8[16] = "Paris, France";
extern const char D_0024A2E8[16] = "The Hideout";
extern const char D_0024A2F8[24] = "A Stealthy Approach";
extern const char D_0024A310[24] = "Prowling the Grounds";
extern const char D_0024A328[24] = "High Class Heist";
extern const char D_0024A340[24] = "Into the Machine";
extern const char D_0024A358[24] = "A Cunning Disguise";
extern const char D_0024A370[24] = "The Fire Down Below";
extern const char D_0024A388[24] = "Treasure in the Depths";
extern const char D_0024A3A0[24] = "The Gunboat Graveyard";
extern const char D_0024A3B8[24] = "The Eye of the Storm";
extern const char D_0024A3D0[16] = "A Rocky Start";
extern const char D_0024A3E0[16] = "Muggshot's Turf";
extern const char D_0024A3F0[16] = "Boneyard Casino";
extern const char D_0024A400[24] = "Murray's Big Gamble";
extern const char D_0024A418[24] = "At the Dog Track";
extern const char D_0024A430[16] = "Two to Tango";
extern const char D_0024A440[24] = "Straight to the Top";
extern const char D_0024A458[24] = "Back Alley Heist";
extern const char D_0024A470[16] = "Last Call";
extern const char D_0024A480[24] = "The Dread Swamp Path";
extern const char D_0024A498[24] = "The Swamp's Dark Center";
extern const char D_0024A4B0[24] = "The Lair of the Beast";
extern const char D_0024A4C8[24] = "A Grave Undertaking";
extern const char D_0024A4E0[16] = "Piranha Lake";
extern const char D_0024A4F0[24] = "Descent into Danger";
extern const char D_0024A508[24] = "A Ghastly Voyage";
extern const char D_0024A520[24] = "Down Home Cooking";
extern const char D_0024A538[16] = "A Deadly Dance";
extern const char D_0024A548[24] = "A Perilous Ascent";
extern const char D_0024A560[24] = "Inside the Stronghold";
extern const char D_0024A578[24] = "Flaming Temple of Flame";
extern const char D_0024A590[16] = "The Unseen Foe";
extern const char D_0024A5A0[24] = "The King of the Hill";
extern const char D_0024A5B8[24] = "Rapid Fire Assault";
extern const char D_0024A5D0[24] = "Duel by the Dragon";
extern const char D_0024A5E8[24] = "A Desperate Race";
extern const char D_0024A600[16] = "Flame Fu!";
extern const char D_0024A610[24] = "A Hazardous Path";
extern const char D_0024A628[16] = "Burning Rubber";
extern const char D_0024A638[16] = "A Daring Rescue";
extern const char D_0024A648[24] = "Bentley Comes Through";
extern const char D_0024A660[24] = "A Temporary Truce";
extern const char D_0024A678[16] = "Sinking Peril";
extern const char D_0024A688[24] = "A Strange Reunion";

void QueueObjectForRegroup(World* owner, u8* obj)
{
    u64 flags = *(u64*)(obj + 0x2C8);
    u64 bit = (u64)0x8000 << 24;
    if (!(flags & bit))
    {
        *(u64*)(obj + 0x2C8) = flags | bit;
        s32 n = owner->regroupCount;
        owner->regroupObjects[n] = (PlacedObject*)obj;
        owner->regroupCount = n + 1;
    }
}

void MergeObjectLinkLists(void* ctx, PlacedObject* self, PlacedObject* other)
{
    ListFrame frame;
    if (self != other) {
        PlacedObject* e = (PlacedObject*)other->list60.head;
        if (e != 0) {
            e->f54 = self;
            for (e = (PlacedObject*)e->link58.next; e != 0; e = (PlacedObject*)e->link58.next) {
                e->f54 = self;
            }
        }
        SpliceListToEnd(&self->list60.head, &other->list60.head);
    }
}

void DissolveObjectLinkList(void* self, PlacedObject* owner)
{
    LinkListWalk it;
    PlacedObject* node;
    BeginLinkListWalk::Of(&it, &owner->list60);
    while ((node = NextInLinkList::Of(&it)) != 0) {
        if (node != owner) {
            RemoveFromList(&owner->list60, node);
            node->f54 = node;
            node->list60.tail = node;
            node->list60.head = node;
        }
        QueueObjectForRegroup(self, node);
    }
    g_activeListFrames = (ListFrame*)it.prev;
}

void MergeObjectGroupMembers(void* self, FoundList* group)
{
    s32 i = 0;
    while (i < group->count) {
        if (IsObjectAttached(group->objects[i]) != 0) {
            break;
        }
        i++;
    }
    s32 first = i;
    for (; i < group->count; i++) {
        if (IsObjectAttached(group->objects[i]) != 0) {
            MergeObjectLinkLists(self, group->objects[first]->f54, group->objects[i]->f54);
        }
    }
}

void RegisterObjectGroup(void* self, FoundList* group)
{
    if (group->count >= 2) {
        for (s32 i = 0; i < group->count; i++) {
            PlacedObject* item = group->objects[i];
            u32 n = item->count6C;
            if (n < 4) {
                item->items70[n] = (PlacedObject*)group;
                item->count6C = n + 1;
            }
        }
        MergeObjectGroupMembers(self, group);
    }
}

void RemoveValueFromArray(CountedArray* list, s32* arr, s32 value)
{
    s32 i = list->count;
    s32* p = (s32*)(((s32)i << 2) + (s32)arr);
    i--;
    for (;;)
    {
        if (i < 0)
        {
            return;
        }
        p--;
        if (*p == value)
        {
            break;
        }
        i--;
    }
    (void)MoveMemory(arr, arr + 1, (list->count - i) * 4 - 4);
    list->count--;
}

void UnregisterObjectGroup(void* self, FoundList* s)
{
    s32 i;
    PlacedObject* obj;
    if (s->count >= 2) {
        for (i = 0; i < s->count; i++) {
            obj = s->objects[i];
            RemoveValueFromArray(&obj->count6C, obj->items70, s);
        }
        for (i = 0; i < s->count; i++) {
            obj = s->objects[i];
            if (obj->f54 != 0) {
                DissolveObjectLinkList(self, obj->f54);
                break;
            }
        }
    }
}

void RegroupQueuedObjects(World* self)
{
    s32 i = self->regroupCount;
    i--;
    if (i >= 0) {
        u64 mask = ((u64)~0x80 << 32) | 0xFFFFFFFF;
        do {
            PlacedObject* obj = self->regroupObjects[i];
            obj->flags &= mask;
            if (obj->f54 == obj) {
                s32 j = obj->count6C;
                j--;
                for (; j >= 0; j--) {
                    MergeObjectGroupMembers(self, obj->items70[j]);
                }
            }
            i--;
        } while (i >= 0);
    }
    self->regroupCount = 0;
}

void VisitObjectTree(VisitNode* self, void* arg)
{
    ListFrame frame;
    if (self->cls->visit != 0)
        self->cls->visit(self, arg);
    VisitNode* node = self->child;
    if (node != 0)
    {
        do
        {
            if (node->cls->flags & 1)
                VisitObjectTree(node, arg);
            node = node->next;
        } while (node != 0);
    }
}

s32 GetPlacedObjectFrozen(PlacedObject* self, s32* out)
{
    s32 bit = (s32)(self->flags >> 38) & 1;
    *out = bit;
    return bit;
}

void SetPlacedObjectFrozen(PlacedObject* self, s32 flag)
{
    if (flag != 0) {
        self->vA0 = self->v150;
        self->vB0 = self->v160;
        self->f29C = 0;
        if (self->f2AC != 0) {
            StopSoundRecord((void*)self->f2AC->p1C, 0);
        }
        self->desc02()->m20(self, (Vec02*)D_00248D30);
        self->desc02()->m21(self, (Vec02*)D_00248D30);
        self->flags |= (u64)1 << 38;
    } else {
        self->flags &= ~((u64)1 << 38);
        self->desc02()->m20(self, &self->vA0);
        self->desc02()->m21(self, &self->vB0);
        SoundRecord* c = self->f2AC;
        if (c != 0) {
            StartSoundEffect(c->p00, &c->p1C, (void*)self, 0, c->f04, c->f08, c->f0C, c->f10, c->f20, &c->b14, 0);
        }
    }
}

void SetColliderFrozen(Collider* self, s32 flag)
{
    if (flag != 0) {
        self->save90 = self->mode450;
        self->save94 = self->mode470;
        SetColliderAnchors(self, 3, 0, 3, 0);
        u128 zero = Vu0::Zero();
        Vu0::Q(*(Vec02*)((u8*)self + 0x170)) = zero;
        Vu0::Q(*(Vec02*)((u8*)self + 0x180)) = zero;
        FreeTouchNodes(self->world, self->touching);
        self->touching = 0;
        SetPlacedObjectFrozen(self, 1);
    } else {
        SetPlacedObjectFrozen(self, 0);
        SetColliderAnchors(self, self->save90, 0, self->save94, 0);
    }
}

extern u8* g_camera;
void AppendToList(void* list, void* node);
void RemoveFromList(void* list, void* node);

// Marks each group active (bit 37 of its members' flags) when a member's mode bits force it or the
// camera sees a member within its radius, and moves the members into or out of the world's lists.
void UpdateGroupsNearCamera(World* self)
{
    for (PlacedObject* g = (PlacedObject*)self->list54.head; g != 0; g = (PlacedObject*)g->link48.next) {
        if (g->f54 != g) {
            continue;
        }
        PlacedObject* m = (PlacedObject*)g->list60.head;
        PlacedObject* first = m;
        s32 active;
        for (; m != 0; m = (PlacedObject*)m->link58.next) {
            Camera* cam = (Camera*)g_camera;
            s32 mode = (s32)(m->flags >> 40) & 3;
            if (mode == 1) {
                goto done;
            }
            if (mode == 2) {
                m = 0;
                goto done;
            }
            if ((m->f88 & cam->f21C) == cam->f21C) {
                f32 r = m->f80 + m->f2A8;
                u128 diff = Vu0::Sub(Vu0::Q(m->v140), Vu0::Q(cam->f40));
                f32 d = Vu0::ToFloatMoved(Vu0::Dot(diff, diff));
                if (!(r * r < d)) {
                    goto done;
                }
            }
        }
    done:
        active = m != 0;
        m = first;
        if (m == 0) {
            continue;
        }
        u64 bit = (u64)active << 37;
        u64 mask = ~((u64)1 << 37);
        while (m != 0) {
            if (active != ((s32)(m->flags >> 37) & 1)) {
                if (active != 0) {
                    VisitObjectTree((VisitNode*)m, 0);
                    AppendToList(&self->list60, m);
                    if (m->desc->flags & 2) {
                        AppendToList(&self->list6C, m);
                    }
                } else {
                    VisitObjectTree((VisitNode*)m, (void*)1);
                    RemoveFromList(&self->list60, m);
                    if (m->desc->flags & 2) {
                        RemoveFromList(&self->list6C, m);
                    }
                }
                m->flags = (m->flags & mask) | bit;
            }
            m = (PlacedObject*)m->link58.next;
        }
    }
}

void UpdateWorldObjectLists(void* self)
{
    RegroupQueuedObjects(self);
    UpdateGroupsNearCamera((World*)self);
}

void ResolveLookupIds(IdLookupObject* self)
{
    StartObject(self);
    World* cur = self->world;
    FoundList* sub = &self->found;
    sub->items = (s32*)AllocateFrontMemory(self->idCount * 4);
    for (s32 i = 0; i < self->idCount; i++) {
        s32 r = FindFirstObjectByIdMode1(cur, self->ids[i], self->parent);
        if (r != 0) { s32 n = sub->count; sub->items[n] = r; sub->count = n + 1; }
    }
    RegisterObjectGroup(cur, &self->found);
}

void AddLookupId(IdLookupObject* obj, s32 value) { obj->ids[obj->idCount++] = value; }

void RunResetGameSession() { ResetGameSessionAndFade(); }

LINKER_REMNANT(func_00160090);

KeyedEntry* FindKeyEntry(KeyedEntry* key)
{
    KeyedEntry* p = (KeyedEntry*)g_keyedEntries;
    KeyedEntry* end = (KeyedEntry*)((u8*)g_keyedEntries + 0x7E8);
    s32 m;

    do {
        if (key == p) {
            m = 1;
        } else if (key == 0 || p == 0) {
            m = 0;
        } else {
            m = ((key->key.signedWords[2] ^ key->key.signedWords[6]) ^ (p->key.signedWords[2] ^ p->key.signedWords[6])) == 0;
        }
        if (!m) {
            p = (KeyedEntry*)((u8*)p + 0x2C);
        } else {
            return p;
        }
    } while (p < end);
    return 0;
}

void* FindEntryById(s32 key)
{
    u8* p = (u8*)g_keyedEntries;
    u8* end = (u8*)g_keyedEntries + 0x7E8;
    for (;;) {
        if (key != *(s32*)(p + 0x20)) {
            p += 0x2C;
            if ((u32)p < (u32)end) {
                continue;
            }
            return 0;
        }
        return p;
    }
}

void* GetEntryName()
{
    void* p = FindEntryById();
    if (p == 0)
    {
        return D_002623D0;
    }
    return *(void**)((u8*)p + 0x24);
}

LINKER_REMNANT(func_00160178);

s32 LookupEntryById(void)
{
    return (s32)FindEntryById();
}

s32 GetEntryIdByKey(void)
{
    s32 v;
    KeyedEntry* r = FindKeyEntry();
    v = -1;
    if (r != 0) v = r->id;
    return v;
}

LINKER_REMNANT(func_001601D0);

s32 GetEntryFlags(void* a0)
{
    EntryFlags* e = FindEntryById(a0);
    s32 r = 0;
    if (e != 0) {
        r = e->f28;
    }
    return r;
}

void CountCategoryFlags(s32 key, s32* a1, s32* a2, s32* a3)
{
    KeyedEntry* p;
    KeyedEntry* end;

    *a3 = 0;
    *a2 = 0;
    p = (KeyedEntry*)g_keyedEntries;
    *a1 = 0;
    end = (KeyedEntry*)((u8*)g_keyedEntries + 0x7E8);
    do {
        if ((p->id >> 8) == key) {
            if (p->i28 & 2) {
                (*a1)++;
            }
            if (p->i28 & 4) {
                (*a2)++;
            }
            if (p->i28 & 8) {
                (*a3)++;
            }
        }
        p++;
    } while (p < end);
}

s32 ComputeCompletionMask(void) {
    u32 mask = 0xE;
    u8* p = (u8*)g_keyedEntries;
    u8* end = (u8*)g_keyedEntries + 0x7E8;
    do {
        u32* r = GetLevelEntryByKey((void*)*(void**)(p + 0x20));
        mask &= ~*(u32*)(p + 0x28) | *r;
        p += 0x2C;
    } while (p < end);
    s32 clear = -3;
    s32 n = 4;
    u8* q = (u8*)&g_saveData->levels[1].f448;
    do {
        u32 flag = *(u32*)q & 0x20;
        mask = (flag == 0) ? (mask & (u32)clear) : mask;
        q += 0x44C;
        n--;
    } while (n >= 0);
    return mask;
}

void MarkProgressStageFlag(s32 n)
{
    switch (n) {
    case 1: g_saveData->f19F4 |= 0x10; break;
    case 2: g_saveData->f19F4 |= 0x40; break;
    case 3: g_saveData->f19F4 |= 0x100; break;
    case 4: g_saveData->f19F4 |= 0x400; break;
    case 5: g_saveData->f19F4 |= 0x1000; break;
    }
}

void MarkLevelDone(s32 n)
{
    g_saveData->levels[n].f448 |= 0x20;
    switch (n) {
    case 1:
        g_saveData->f19F4 |= 0x20;
        break;
    case 2:
        g_saveData->f19F4 |= 0x80;
        break;
    case 3:
        g_saveData->f19F4 |= 0x200;
        g_saveData->f19F0 |= 0x10000;
        break;
    case 4:
        g_saveData->f19F4 |= 0x800;
        break;
    case 5:
        ApplyCompletionFlags(2);
        break;
    }
}

void ApplyCompletionFlags(s32 mode)
{
    switch (mode) {
    case 2:
        g_saveData->f19F4 |= 0xA002;
        g_saveData->f19F8 |= 2;
        break;
    case 4:
        if ((ComputeCompletionMask() & 4) != 0) {
            g_saveData->f19F4 |= 0xC000;
        }
        break;
    case 8:
        if ((ComputeCompletionMask() & 8) != 0) {
            g_saveData->f19F4 |= 0xC;
            g_saveData->f19F8 |= 0xC;
        }
        break;
    }
}

void FadeOutAndQueueMovie(s32 kind)
{
    s32 s0 = -1;

    if (kind != 4) { if (kind < 5) { if (kind == 2) { s0 = 0xD; } } } else { s0 = 0xE; }
    StartObjectFade((void*)D_00247AD0, -1, 1);
    if (s0 != -1) {
        QueueMovieWithSuccessor(s0, 0xF);
    }
}

void ResetGameProgress(GameProgress* self)
{
    FillMemory(self, 0, 0x1A00);
    self->type = 0x12;
    self->f19D8 = 0;
    self->f19F0 = 0;
    self->size = 0x1A00;
    self->f19DC = 3;
    self->f19E0 = 5;
    self->f19FC = -1;
    ApplyPadPatternSetting(self);
}

s32 ChecksumGameProgress(GameProgress* s)
{
    u8* p = (u8*)&s->fC;
    s32 sum = 0;
    for (s32 i = 0; i < (u8*)(s + 1) - (u8*)&s->fC; i++) {
        sum += *p++;
    }
    return sum;
}

void SetCurrentLevelEntry(s32 a0, s32 flags)
{
    s32 r = GetEntryIdByKey(a0);
    s32 hi = (r != -1) ? (r >> 8) : 0;
    s32 lo = (r != -1) ? (r & 0xFF) : 0;
    G27C230* base = &g_saveData->levels[hi];
    GameProgress* g = g_saveData;
    s32 gate = g->f19E0;
    g_currentLevelRecord = base;
    g_currentEntry = (G27C230*)((u8*)base + lo * 0x78);
    if (gate < 0 || (flags & 2) != 0) {
        ResetReserveCounts();
    } else if ((flags & 1) != 0) {
        RestoreFlagTableSnapshot(g_flagTable);
    } else if ((flags & 4) != 0) {
        ResetGameSession();
    } else {
        ResetFlagTable(g_flagTable);
    }
    g = g_saveData;
    g_previousLevelIndex = g->f19D8;
    g->f19D8 = hi;
    g->f19DC = lo;
    g_currentLevelRecord->f448 |= 1;
    g_currentEntry->flags |= 1;
}

void AddElapsedTime(f32 dx)
{
    g_saveData->fC += dx;
    g_currentLevelRecord->f444 += dx;
    g_currentEntry->f04 += dx;
}

void* GetLevelEntryByKey(s32 key)
{
    return key == -1 ? 0 : (u8*)&g_saveData->levels[key >> 8] + (key & 0xFF) * 0x78;
}

s32 GetLevelEntryWord()
{
    s32* p = GetLevelEntryByKey();
    s32 value = 0;
    if (p)
    {
        value = *p;
    }
    return value;
}

void ResetGameSession(void)
{
    ResetGameProgress(g_saveData);
    D_00269984.v = 0;
    ClearTwoWords(D_002623D8);
    ClearScatterController(g_scatterController);
    g_buttonCodeFlags = 0;
    g_previousLevelIndex = -1;
    ResetReserveCounts();
}

void ResetReserveCounts(void)
{
    GameProgress* g = g_saveData;
    g->f19E0 = 5;
    g->f19E4 = 0;
    ResetFlagTable((void*)g_flagTable);
}

void ResetGameSessionAndFade(void)
{
    ResetGameSession();
    StartObjectFade((void*)&D_00247AB0, -1, 0);
}

void ResumeAtSavedLevel(void)
{
    SessionKey* k = LookupEntryById((g_saveData->f19D8 << 8) | g_saveData->f19DC);
    if (k == 0) {
        k = &D_00247AB0;
    }
    ClearTwoWords(D_002623D8);
    if (g_elementStack.f30 != 1 || g_saveData->fC != 0.0f || !k->Same((SessionKey*)&D_00275B04)) {
        StartObjectFade(k, -1, 1);
    } else if (g_elementStack.f30 == 1) {
        if (D_00275F84 == 0) {
            SilenceVolumeChannel3(g_saveData->f19EC & 0x80);
            ApplySoundOptionFlag(g_saveData->f19EC & 0x40);
            Animation* r = FindFirstObjectById(g_currentWorld, 0x105, 0x494, 0);
            if (r != 0) {
                PlayerListWalk frame((AnimationPlayerList*)r->props6C);
                void* head = *(void**)r->props6C;
                frame.cursor = (u8*)head + frame.next_off;
                void* node = head;
                if (node != 0) {
                    do {
                        StopAnimationPlayer(node);
                        node = frame.Next();
                    } while (node != 0);
                }
            }
            g_elementStack.f30 = -1;
            SetElementStackState(&g_elementStack, 3);
        }
    }
}

s32 ComputeCompletionPercent(u8* p)
{
    s32 total = 0;
    s32 done = 0;
    u32 i;
    s32 k;
    for (i = 0; i < 0x2E; i++) {
        u8* e = (u8*)g_keyedEntries + i * 0x2C;
        u32 v = *(u32*)(e + 0x20);
        s32 idx = (s32)v >> 8;
        if (idx != 0) {
            u32 flags = *(u32*)(e + 0x28);
            u32* w = (u32*)(p + (idx * 0x44C + 0x10) + (v & 0xFF) * 0x78);
            u32 bit;
            total++;
            done += *w & 1;
            for (bit = 2; bit & 0xE; bit <<= 1) {
                if (flags & bit) {
                    total++;
                    if (*w & bit) done++;
                }
            }
        }
    }
    for (k = 0; k < 5; k++) {
        total++;
        if (*(u32*)(p + 0x8A4 + k * 0x44C) & 0x20) done++;
    }
    if (done == 0) return 0;
    if (done == total) return 100;
    return PercentClamp::Of(done * 100 / total, 1, 99);
}

void SetSpareCount(s32 value)
{
    g_saveData->f19E4 = value;
}

s32 HasSpareCount()
{
    s32 result=0;
    if (g_saveData->f19E4>0 || (g_buttonCodeFlags&2)) result=1;
    return result;
}

LINKER_REMNANT(func_00160C90);

void* GetIndexedTargetSlot(u8* self,s32 index)
{
    if ((u32)(index-0x33B)>=12) return 0;
    else return self+(index*4-0xCD8);
}

void ClearTwoWords(void* p)
{
    FillMemory(p, 0, 8);
}

void ResetCounter(Counter* c)
{
    c->count = 0;
}

s32 IncrementCounter(Counter* c)
{
    return ++c->count;
}

void ReleaseCounterRef(RefCounted* self)
{
    self->refs--;
}

s32 MaskWorldBitsBySave()
{
    return g_saveData->f19F0 & g_currentWorld->f235C;
}

void GetCurrentLevelBit(u32* out)
{
    s32 m;
    switch (g_saveData->f19D8) {
    case 4: m = 0x10000000; break;
    case 1: m = 0x20000000; break;
    case 2: m = 0x40000000; break;
    case 3: m = 0x80000000; break;
    case 0:
    case 5: m = 0; break;
    }
    if (out) *out = m;
}

s32 GetSpareCountLimit(void)
{
    return 2;
}

void SpendReserveUnit(void)
{
    GameProgress* o = g_saveData;
    u8* x = (u8*)g_currentWorld;
    s32 t = o->f19E0 - 1;
    o->f19E0 = t;
    PopActiveSequenceElement((void*)x);
    StopLockedStreamVoice();
    GameProgress* p = g_saveData;
    s32 m = p->f19DC;
    if (m == 1) {
        FadeRequest args;
        args.kind = m;
        args.text = (u8*)&D_00275B04;
        u8* base = args.text - 0x14;
        args.f08 = *(s32*)(base + 0x8);
        args.f0C = *(s32*)(base + 0xC);
        args.flags = 0x10;
        StartScreenFade((void*)&g_screenFade, &args, 1);
    } else if (p->f19E0 >= 0) {
        StartScreenFadeFromFlagTable((void*)g_flagTable);
    } else {
        SetPauseMenuLayerPage((void*)g_pauseMenuElement, 0, 1);
    }
    RaiseScatterLevels((void*)g_scatterController, 1.0f);
}

void ClearRecordBody(ClearedRecord* self)
{
    self->f4 = 0;
    self->f8 = 0;
    self->fC = 0;
    self->f10 = 0;
    self->f14 = 0;
    self->f18 = 0;
}

void CopyMeshTransformed(Mesh03* src, s32 matrix, Mesh03* dst)
{
    dst->vertCount = src->vertCount;
    dst->verts = CopyToFrontMemory(src->vertCount << 4, src->verts);
    dst->faceCount = src->faceCount;
    dst->faces = CopyToFrontMemory(src->faceCount << 5, src->faces);
    dst->points = CopyToFrontMemory(src->faceCount << 4, src->points);
    dst->words = CopyToFrontMemory(src->faceCount << 2, src->words);
    dst->edgeCount = src->edgeCount;
    dst->edges = src->edges;
    if (matrix != 0) {
        for (s32 i = 0; i < dst->vertCount; i++) {
            Vec02* v = &((Vec02*)dst->verts)[i];
            TransformByMatrixWithW((void*)matrix, 1.0f, v, v);
        }
        for (s32 i = 0; i < dst->faceCount; i++) {
            u8* face = (u8*)dst->faces + (i << 5);
            TransformByMatrixWithW((void*)matrix, 0.0f, face, face);
            Vec02* vert = (Vec02*)((*(u16*)(face + 0x1E) << 4) + (s32)dst->verts);
            *(u32*)(face + 0x10) = Vu0::ToBits(Vu0::Dot(Vu0::Q(*(Vec02*)face), Vu0::Q(*vert)));
            Vec02* p = &((Vec02*)dst->points)[i];
            TransformByMatrixWithW((void*)matrix, 1.0f, p, p);
        }
    }
}

s32 CollectEntriesForKey(KeyedPointSet* dst, KeyedPointSet* src, s32 key, s32 maxOut, KeyedEdge** out)
{
    s32 buf[4];

    PushBackMemoryMark();
    u8* k = AllocateBackMemory(src->count * 12);
    buf[0] = (s32)k;
    if (QueryPlaneTreePoint(src->base, dst->base + key * 16, buf, 1.0f) != 2) {
        PopBackMemoryMark();
        return 0;
    }
    s32 i = 0;
    s32 n = (((s32)buf[0] - (s32)k) * (s32)0xAAAAAAAB) >> 2;
    s32 j = 0;
    if (n > 0) {
        for (; i < n; i++) {
            ContactHit* e = (ContactHit*)(k + i * 12);
            KeyedEdge* p = e->holder->head;
            if (p == 0) {
                continue;
            }
            KeyedEdge** o = (KeyedEdge**)(j * 4 + (s32)out);
            while (p != 0) {
                if (key == p->k0 || key == p->k1) {
                    s32 m;
                    for (m = 0; m < j; m++) {
                        if (p == out[m]) {
                            break;
                        }
                    }
                    if (m >= j && j < maxOut) {
                        *o = p;
                        o++;
                        j++;
                    }
                }
                p = p->next;
            }
        }
    }
    PopBackMemoryMark();
    return j;
}

extern const Fn_Table g_gifPacketMethods[6] = { 0, 0, 0, (Fn_Table)(void (*)(PacketWriter* f, s32 n))CloseGifTag, 0, 0 };

PacketWriter* InitGifPacket(PacketWriter* self)
{
    (void)InitPacketBuffer(self);
    self->f14 = 1;
    self->vt = (const PacketWriterVt*)g_gifPacketMethods;
    self->f1C = 0;
    self->f20 = 0;
    self->f24 = 0;
    return self;
}

void EndGifPacket(PacketWriter* self)
{
    if (self->f1C != 0) {
        const PacketWriterVt* s = self->vt;
        s->close((PacketWriter*)((u8*)self + s->adj1), 1);
    } else {
        BeginGifTag(self, 0, 1, 0xE);
        const PacketWriterVt* s = self->vt;
        s->close((PacketWriter*)((u8*)self + s->adj1), 1);
    }
}

void CloseGifTag(PacketWriter* f, s32 n)
{
    if (f->f1C == 0)
        return;
    u32 q = f->f24 / f->f20;
    u32 a2 = f->curU;
    if (a2 & 0xF) {
        f->curU = a2 + 8;
        *(u64*)a2 = 0;
    }
    u32* p = f->f1C;
    u32 w;
    if (n) {
        w = *p;
        w |= 0x8000;
    } else {
        w = *p;
    }
    w |= q;
    *p = w;
    f->f1C = 0;
}

s32 CountGifEntry(PacketWriter* obj) { return ++obj->f24; }

void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, s32* out)
{
    PacketWriter* w = self;
    const PacketWriterVt* sub = w->vt;
    sub->close((PacketWriter*)((u8*)self + sub->adj1), 0);

    u8* p = w->cur;
    u64 tag = (prim << 47) | (1ULL << 46) | (u64)nloop | ((u64)nreg << 60);
    w->cur = p + 16;
    *(u64*)(p + 8) = data;
    *(u64*)p = tag;
    if (out != 0) {
        *out = (s32)w->cur;
    }
    w->cur = w->cur + nloop * nreg * 16;
}

void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, s32 a3)
{
    const PacketWriterVt* d = self->vt;
    d->close((PacketWriter*)((u8*)self + d->adj1), 0);
    u8* blk = self->cur;
    s64 lo = ((s64)a2 << 60) | ((s64)1 << 46);
    s64 hdr = ((s64)a1 << 47) | lo;
    self->cur = blk + 0x10;
    *(s64*)blk = hdr;
    *(s64*)(blk + 8) = (s64)a3;
    self->block = blk;
    self->f20 = a2;
    self->f24 = 0;
}

void AddGifRgbaEntry(PacketWriter* self, u32 value)
{
    CountGifEntry(self, 1, 1);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = value & 0xFF;
    p[1] = (value & 0xFF00) >> 8;
    p[2] = (value >> 16) & 0xFF;
    p[3] = value >> 24;
}

void AddGifUvEntry(PacketWriter* self,s32 a,s32 b)
{
    CountGifEntry(self,1,3);
    s32* p=(s32*)self->cur;
    self->cur+=16;
    p[0]=a;
    p[1]=b;
}

void AddGifStEntry(PacketWriter* self,f32 a,f32 b,f32 c)
{
    CountGifEntry(self,1,2);
    f32* p=(f32*)self->cur;
    self->cur+=16;
    p[0]=a;
    p[1]=b;
    p[2]=c;
}

void AddGifXyzEntry(PacketWriter* self, s32 a1, s32 a2, u64 a3)
{
    CountGifEntry(self, 1, 5);
    u8* p = self->cur;
    self->cur = p + 0x10;
    *(s32*)(p + 0x0) = a1;
    *(s32*)(p + 0x4) = a2;
    *(u64*)(p + 0x8) = a3;
}

void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 1, 4);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = a1;
    p[1] = a2;
    p[2] = a3;
    p[3] = (a4 & 0xFF) << 4;
}

void AddGifXyzfNoDrawEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 1, 4);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = a1;
    p[1] = a2;
    p[2] = (a3 & 0xFFFFFF) << 4;
    p[3] = ((a4 & 0xFF) << 4) | 0x8000;
}

void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2)
{
    CountGifEntry(self, 1, 14);
    u64* p = self->cur64;
    self->cur64 = p + 2;
    p[0] = a2;
    p[1] = a1;
}

LINKER_REMNANT(func_00161760);

void BeginGifRegListTag(PacketWriter* self, u32 a1, u64 a2)
{
    const PacketWriterVt* sub = self->vt;
    sub->close((PacketWriter*)((u8*)self + sub->adj1), 0);
    u64* p = self->cur64;
    self->cur64 = p + 2;
    p[1] = a2;
    p[0] = ((u64)a1 << 60) | ((u64)0x8000 << 43);
    self->f20 = a1;
    self->last = p;
    self->f24 = 0;
}

void AddGifRegListFloat(PacketWriter* self, s32 tag, f32 value)
{
    CountGifEntry(self, 0, 1);
    s32 bits = *(s32*)&value;
    u64 hi = (u64)(s64)bits << 32;
    u64 lo = (u64)(u32)tag;
    u64* p = (u64*)self->cur;
    self->cur = (u8*)(p + 1);
    *p = lo | hi;
}

LINKER_REMNANT(func_00161858);

void AddGifUvRegListEntry(PacketWriter* self, s32 a1, s32 a2)
{
    CountGifEntry(self, 0, 3);
    u64 v = (u64)a1 | (u64)(a2 << 16);
    u64* p = self->cur64;
    self->cur64 = p + 1;
    *p = v;
}

void AddGifXyzfRegListEntry(PacketWriter* self, s32 a1, s32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 0, 4);
    u64 lo = (u64)a1 | (u64)(a2 << 16);
    u64 mid = a3 & 0xFFFFFF;
    u64* p = self->cur64;
    self->cur64 = p + 1;
    *p = (lo | (mid << 32)) | ((u64)a4 << 56);
}

LINKER_REMNANT(func_00161950);

void AddGifImageTag(PacketWriter* self, s32 count)
{
    self->Close(0);
    u64* p = self->cur64;
    self->cur64 = p + 2;
    p[0] = (u64)count | ((u64)2 << 58);
    p[1] = 0;
}

struct CameraBlock16 { u8 b[16]; };

u8* InitVertexBatch(u8* self)
{
    s32 i;
    for (i = 0x93; i != -1; i--) {
    }
    FillMemory(self + 0xFC, 0, 0x28);
    FillMemory(self, 0, 0xB0);
    u8* camera = g_camera;
    *(s32*)(self + 0x98) = 1;
    *(f32*)(self + 0x90) = 1.0f;
    *(CameraBlock16*)(self + 0x80) = *(CameraBlock16*)(camera + 0x208);
    *(s32*)(self + 0xB0) = 0;
    *(s32*)(self + 0xB4) = 0;
    *(s32*)(self + 0x94) = -1;
    *(f32*)(self + 0xAC) = 1.0f;
    ResetVertexBatch(self);
    return self;
}

void DestroyVertexBatch(void* self, s32 flag)
{
    (void)self;
    if (flag & 1) {
        FreeObjectMemory();
    }
}

void SetVertexBatchTransform(u8* self, void* a1, void* a2)
{
    FlushVertexBatch(self);
    BuildMatrixFromRotationAndTranslation(a1, a2, self);
    InvertRigidTransform(a1, a2, self + 0x40);
}

// The lights a batch is lit by: CollectLightsForSphere (main_loop.cpp) takes the world, the
// sphere's centre in a1 and its radius in $f12, which this function passes on untouched (the
// caller, trail_ribbon.cpp's builder, sets both), then a mask, a maximum and the three outputs.
s32 CollectLightsForSphere(void* world, void* center, f32 radius, s32 mask, s32 max,
                           s32* first, s32* count, s32* mode);
struct LightedVertexBatch {
    u8 pad0[0x94];
    s32 f94;
    u8 pad98[4];
    s32 f9C;
    u8 padA0[0xB0 - 0xA0];
    s32 fB0;
    s32 fB4;
    s32 fB8;
    u8 padBC[0xF8 - 0xBC];
    u8* fF8;
};

void SelectVertexBatchLights(LightedVertexBatch* self, void* center, f32 radius)
{
    if (*self->fF8 != 0) {
        self->fB4 = 0;
        self->f94 = -1;
        self->fB0 = 0;
    } else {
        self->f9C = CollectLightsForSphere(g_currentWorld, center, radius, 1, 0x10, &self->fB0,
                                           &self->fB4, &self->fB8);
        self->f94 = 4;
    }
}

void ResetVertexBatch(u8* self)
{
    *(s32*)(self+0xF8)=0;
    *(s32*)(self+0x124)=0;
    ((MemoryFillFn)FillMemory)(self+0x128,0,0x1720);
}

void SetVertexBatchMode(ColoredVertexBatch* self, s32 value)
{
    u32 local;
    FlushVertexBatch(self);
    self->f0F8 = value;
    local = 0xFFFFFFFF;
    SetVertexColor(self, &local);
}

void BuildUnlitVertexPacket(UnlitVertexBatch* self)
{
    UnlitUnpackHeader* hd;
    f32* out1;
    VifPoint* out2;
    u8* out3;
    s32 count;
    CopiedGifTags* dst;
    s32 base;
    s32 i;
    s32 k;
    UnlitVertex* c;

    base = 0x24;
    ReserveVifUnpack(&g_vifPacketWriter, 0xD, 3, 0xB, 0, &hd);
    FillMemory(hd, 0, 0x18);
    hd->f10 = 3;
    hd->f0 = base;
    base = self->f124 * 3 + 0x24;
    hd->f2 = base;
    WriteVifStcycl(&g_vifPacketWriter, 1, 3);
    ReserveVifUnpack(&g_vifPacketWriter, 8, self->f124, hd->f0, 0, &out1);
    ReserveVifUnpack(&g_vifPacketWriter, 0xC, self->f124, hd->f0 + 2, 0, &out2);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->f124; i++) {
        c = &self->e[i];
        out1[0] = c->f1C;
        out1[1] = c->f20;
        out1[2] = 1.0f;
        out2->v = c->v;
        out2->w = c->f24 != 0 ? self->f80 + 32768.0f : self->f80;
        out1 += 3;
        out2++;
    }
    WriteVifMscal(&g_vifPacketWriter, D_00001A50);
    WriteVifStcycl(&g_vifPacketWriter, 1, 3);
    ReserveVifUnpack(&g_vifPacketWriter, 0xE, self->f124, hd->f0 + 1, 0, &out3);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->f124; i++) {
        s32 j;
        c = &self->e[i];
        for (j = 0; j < 4; j++) {
            out3[j] = (self->fF8->col[j] * c->rgba[j] + 0x100) / 0x1FE;
        }
        out3 += 4;
    }
    for (k = 0; k < self->fF8->count; k++) {
        MeshFrameData* pair = &self->fF8->ents[k];
        s32 frame;
        ReserveVifUnpack(&g_vifPacketWriter, 0xC, pair->n, base, &count, &dst);
        frame = 0;
        if (self->fF8->sub != 0) {
            frame = self->fF8->sub->n;
        }
        CopyMemory(dst, pair->data + ((frame * pair->n) << 4), count);
        dst->w[0] |= 0x8000 | self->f124;
        dst->w[4] |= 0x8000;
        hd->f8[k] = base;
        base += pair->n;
    }
    WriteVifMscalf(&g_vifPacketWriter, D_000002F8);
}

void BuildLitVertexPacket(LitVertexBatch* self)
{
    LitUnpackHeader* hdr;
    VifPoint* p4;
    Mat4* p8;
    u8* pC;
    Vec3* p10;
    s32 size;
    u32* dst;
    s32 off = 0x24;
    s32 j;
    s32 i;
    LitVertex* v;

    ReserveVifUnpack(&g_vifPacketWriter, 0xD, 3, 0xB, 0, &hdr);
    FillMemory((ByteSpan*)hdr, 0, 0x18);
    hdr->f10 = 4;
    hdr->f0 = off;
    off += self->n * 4;
    hdr->f2 = off;
    off += (((self->n + 3) & ~3) - self->n) * 4;
    hdr->fE = off;
    off += self->n;
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    ReserveVifUnpack(&g_vifPacketWriter, 0xC, self->n, hdr->f0 + 3, 0, &p4);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->n; i++)
    {
        v = &self->verts[i];
        p4->v = v->pos;
        if (v->flag != 0)
            p4->w = self->base + 32768.0f;
        else
            p4->w = self->base + 28672.0f;
        p4++;
    }
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    ReserveVifUnpack(&g_vifPacketWriter, 0xC, (self->n + 3) & ~3, hdr->f0, 0, &p8);
    ReserveVifUnpack(&g_vifPacketWriter, 0xE, self->n, hdr->f0 + 1, 0, &pC);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    WriteVifMscal(&g_vifPacketWriter, D_00000288);
    for (i = 0; i < self->n; i += 4)
    {
        for (j = 0; j < 4; j++)
        {
            if (i + j < self->n)
            {
                p8->m[0][j] = self->verts[i + j].nx;
                p8->m[1][j] = self->verts[i + j].ny;
                p8->m[2][j] = self->verts[i + j].nz;
            }
            else
            {
                p8->m[0][j] = p8->m[1][j] = p8->m[2][j] = 0.0f;
            }
        }
        FillMemory((ByteSpan*)p8->m[3], 0, 0x10);
        p8++;
    }
    for (i = 0; i < self->n; i++)
    {
        v = &self->verts[i];
        for (s32 m = 0; m < 4; m++)
            pC[m] = (self->mesh->col[m] * v->col[m] + 0x100) / 0x1FE;
        pC += 4;
    }
    CloseDmaTag(&g_vifPacketWriter);
    for (s32 t = 0; t < self->texCount; t++)
        AddDmaRefTag(&g_vifPacketWriter, self->tex[t]->n, self->tex[t]->data);
    BeginDmaTag(&g_vifPacketWriter);
    WriteVifMscal(&g_vifPacketWriter, D_00001210);
    WriteVifFlushE(&g_vifPacketWriter);
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    ReserveVifUnpack(&g_vifPacketWriter, 8, self->n, hdr->f0, 0, &p10);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    WriteVifMscal(&g_vifPacketWriter, D_00001AB0);
    for (i = 0; i < self->n; i++)
    {
        v = &self->verts[i];
        p10->x = v->u;
        p10->y = v->v;
        p10->z = 1.0f;
        p10++;
    }
    s32 k = 0;
    for (s32 t = 0; t < self->mesh->count; t++)
    {
        MeshFrameData* e = &self->mesh->ents[t];
        ReserveVifUnpack(&g_vifPacketWriter, 0xC, e->n, off, &size, &dst);
        MeshFrameCursor* sub = self->mesh->sub;
        s32 m = sub ? sub->n : 0;
        CopyMemory((ByteSpan*)dst, e->data + m * e->n * 16, size);
        dst[0] |= 0x8000 | self->n;
        dst[4] |= 0x8000;
        hdr->f8[k] = off;
        k++;
        off += e->n;
    }
    WriteVifMscalf(&g_vifPacketWriter, D_00000010);
}

void FlushVertexBatch(FlushedVertexBatch* self)
{
    if (self->f0F8 == 0) {
        return;
    }
    if (self->f124 < 3) {
        ResetVertexBatch(self);
        return;
    }
    {
        FlipVifBaseOffset();
        PacketWriter* s = &g_vifPacketWriter;
        s32 size = WriteVifUnpackHeader(s, 12, 11, 0);
        WordCopy::Words((s32*)s->cur, (s32*)self, size >> 2);
        s->cur += size;
        WriteVifMscal(&g_vifPacketWriter, D_000018C0);
        switch (*self->f0F8) {
        case 1:
        case 6:
        case 7:
        case 8:
            BuildUnlitVertexPacket(self);
            break;
        case 0:
            BuildLitVertexPacket(self);
            break;
        }
    }
    ResetVertexBatch(self);
}

void SetVertexPosition(VertexBatch* body, Vec3* v)
{
    body->x = v->x;
    body->y = v->y;
    body->z = v->z;
}

LINKER_REMNANT(func_001626A0);

void SetVertexColor(u8* dst, u8* src)
{
    *(U32P*)(dst + 0x114) = *(U32P*)src;
}

void SetVertexTexCoord(VertexBatch* dst, U64P* src)
{
    dst->texCoord.v = src->v;
}

void AddVertex(AppendVertexBatch* self, s32 value)
{
    s32 n;
    s64 max;

    self->cur.value = value;
    n = self->count;
    max = (*self->pF8 == 0) ? 0x50 : 0x94;
    self->recs[n] = self->cur;
    n++;
    self->count = n;
    if (n == max) {
        BatchVertexWords tmp[2];
        u8* p = self->pF8;
        CopyMemory(tmp, &self->recs[self->count - 2], sizeof(tmp));
        FlushVertexBatch(self);
        SetVertexBatchMode(self, p);
        CopyMemory(self->recs, tmp, sizeof(tmp));
        self->count = 2;
    }
}

void CollectNonNullRefs(RefOwner* owner)
{
    owner->refs = (void**)AllocateFrontMemory(owner->capacity << 2);
    s32 n = 0;
    for (s32 i = 0; i < owner->count; i++) {
        void* ref = owner->items[i].ref;
        if (ref != 0)
            owner->refs[n++] = ref;
    }
}

// A packet buffer this reader fills (0x24 bytes: the three are 0x24 apart).
struct ModelPacket {
    u8* end;
    u8* begin;
    s32* f08;
    u8* cur;
    u8 pad10[0x24 - 0x10];
};

// A placed object's model, read from the level stream (func_00162890).
struct ModelLink;
struct ModelPart;
struct ModelStrip;
struct ModelRecord;

// The 0x90-byte record a part with flag 0x100 links to its model.
struct ModelLink {
    s32 owner;              // 0x00
    ModelPart* part;        // 0x04
    s32 id;                 // 0x08
    u8 pad0C[4];
    s32 f10;                // 0x10
    s32 f14;                // 0x14
    s32 f18;                // 0x18
    u8 pad1C[4];
    s32 bone;               // 0x20
    f32 f24;                // 0x24
    f32 f28;                // 0x28
    f32 f2C;                // 0x2C
    f32 f30;                // 0x30
    u8 pad34[0xC];
    u8 matrix[0x40];        // 0x40
    ModelLink* next;        // 0x80
    u8 pad84[0xC];
};

struct ModelAnimator;
struct ModelAnimatorVt {
    void* slots[6];
    void (*bind)(ModelAnimator* self, s32** outs, ModelRecord* model, ModelPart* part, ModelStrip* strip);
};
struct ModelAnimator { ModelAnimatorVt* vt; };

// One strip of a part's mesh.
struct ModelStrip {
    Vec3 pos;               // 0x00
    u8 pad0C[4];
    f32 f10;                // 0x10
    s32 f14;                // 0x14
    StripMesh* mesh;        // 0x18
    StripUnpack* unpack;    // 0x1C
    StripExtra* extra;      // 0x20
    s32 nkeys;              // 0x24
    s32 keys[4];            // 0x28
    s32 qwc[3];             // 0x38
    u32 addr[3];            // 0x44
};

// One morph target of a part.
struct ModelMorph {
    u16* p;                 // 0x00
    s32 nkeys;              // 0x04
    s32 keys[4];            // 0x08
    s32 qwc;                // 0x18
    u32 addr;               // 0x1C
};

struct __attribute__((aligned(16))) ModelPart {
    Vec3 pos;               // 0x00
    u8 pad0C[4];
    f32 f10;                // 0x10
    s32 f14;                // 0x14
    u8 pad18[4];
    f32 far;                // 0x1C
    f32 near;               // 0x20
    f32 f24;                // 0x24
    s32 f28;                // 0x28
    s32 f2C;                // 0x2C
    f32* vecs;              // 0x30
    s32 f34;                // 0x34
    ModelAnimator* animator;    // 0x38
    f32 f3C;                // 0x3C
    f32 fog[4];             // 0x40
    f32 f50;                // 0x50
    ModelLink* link;        // 0x54
    s32 nstrips;            // 0x58
    ModelStrip* strips;     // 0x5C
    s32 nmorphs;            // 0x60
    ModelMorph* morphs;     // 0x64
    void* matrix;           // 0x68
    u8 pad6C[4];
};

// A strip's packets (BuildPartVifPackets fills the first six words).
struct StripPackets {
    void* f0;
    void* f4;
    void* f8;
    void* fC;
    void* f10;
    void* f14;
    u8 pad18[0x18];
};

struct ModelPose {
    u32 f0;                 // 0x00
    StripPackets* packets;  // 0x04
    u8 pad08[8];
    f32 f10;                // 0x10
    u8 pad14[0x14];
};

struct ModelRecord {
    s32 nids;               // 0x00
    void* links;            // 0x04
    s32* ids;               // 0x08
    s32 count;              // 0x0C
    ModelPart* parts;       // 0x10
    ModelPose* poses;       // 0x14
    u8 pad18[0x28];
    s32 nweights;           // 0x40
    void* weights;          // 0x44
    void* weightsCopy;      // 0x48
    ModelLink* head;        // 0x4C
    s32 nanimators;         // 0x50
};

PacketWriter *InitPacketWriter(ModelPacket* p);

// A packet buffer of the model reader, set up where it is declared.
struct StripPacket : ModelPacket {
    StripPacket() { InitPacketWriter(this); }
};

struct StripOutputs {
    s32* p[3];
    StripOutputs() { FillMemory(this, 0, sizeof(*this)); }
};

// A pointer into a packet buffer moved with its copy.
// Its arguments are in RemapMeshQueueValues's order (size, start, to).
struct MovedPointer {
    static void Fix(s32* p, u32 size, u32 start, u32 to)
    {
        if (p) {
            u32& v = *(u32*)p;
            if (v >= start && v < start + size)
                v += to - start;
        }
    }
};

s32 ReadBufferedU8(void* stream);
s32 ReadBufferedU16(void* stream);
s32 ReadBufferedS16(void* stream);
s32 ReadBufferedS8(void* stream);
u32 ReadBufferedU32(void* stream);
f32 ReadBufferedFloat(void* stream);
void ReadBufferedStreamBytes(void* stream, s32 size, void* dst);
void ReadBufferedMatrix4(void* stream, void* dst);
void ReadBufferedVector3(void* stream, void* dst);
void ReadBufferedVector4(void* stream, void* dst);
void AlignBufferedStreamPosition(void* stream, s32 n);
ModelAnimator* ReadAnimator(void* stream);
void ComputeCameraFogTerms(u8* camera, f32* out, f32 p);
void CopyAttachmentPart(ModelRecord* self, ModelPart* part, ModelPose* pose);
void CollectNonNullRefs(ModelRecord* self);
void AllocateTempPacketBuffer(ModelPacket* p, s32 size);
void DetachPacketBufferCopy(ModelPacket* p, s32* qwc, u32* start, u32* addr, s32 flags);
void RemapMeshQueueValues(s32 idx, u32 lo, u32 take, u32 give);
void BuildStripMeshPacket(ModelRecord* self, ModelPart* obj, s32 mode, ModelStrip* hdr, StripMesh* mesh,
                   Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, Vec3* vnrms, f32* weights, ModelPacket* pkt,
                   s32** outs);
void BuildLitStripMeshPacket(ModelRecord* self, ModelPart* obj, s32 unused2, s32 mode, ModelStrip* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, ModelPacket* pkt, s32** outs);
void BuildMorphTargetPacket(ModelRecord* self, s32 mode, ModelMorph* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, f32* data, ModelPacket* pkt);
void BuildPartVifPackets(ModelPart* a, ModelStrip* b, StripPackets* c);
extern s32 g_meshQueueCount;
extern u8* g_animRecords;

void ReadPlacedObjectModel(ModelRecord* self, void* stream, s32 owner)
{
    s32 i;
    s32 a;
    s32 b;

    self->nanimators = 0;
    a = ReadBufferedU8(stream);
    b = ReadBufferedU8(stream);
    self->nids = ReadBufferedU8(stream);
    self->links = AllocateZeroedFrontMemory(self->nids * 0x90);
    self->ids = (s32*)AllocateZeroedFrontMemory(self->nids * 4);
    for (s32 n = 0; n < self->nids; n++) {
        self->ids[n] = ReadBufferedS16(stream);
    }
    self->nweights = ReadBufferedU8(stream);
    self->weights = AllocateZeroedFrontMemory(self->nweights * 4);
    ReadBufferedStreamBytes(stream, self->nweights * 4, self->weights);
    self->weightsCopy = CopyToFrontMemory(self->nweights * 4, self->weights);
    self->count = ReadBufferedU16(stream);
    self->parts = (ModelPart*)AllocateZeroedFrontMemory(self->count * 0x70);
    self->poses = (ModelPose*)AllocateZeroedFrontMemory(self->count * 0x28);
    for (i = 0; i < self->count; i++) {
        ModelPart* part = &self->parts[i];
        ModelPose* pose = &self->poses[i];
        s32 j;
        s32 k;
        s32 flags = ReadBufferedU16(stream);
        if (flags & 1) {
            s32 idx = ReadBufferedS16(stream);
            *part = self->parts[idx];
            *pose = self->poses[idx];
            part->matrix = AllocateFrontMemory(0x40);
            ReadBufferedMatrix4(stream, part->matrix);
        } else {
            part->far = 1.0e10f;
            part->near = 2000.0f;
            part->f24 = 3.402823466e+38f;
            part->f3C = 1.0f;
            part->f50 = 1.0f;
            part->f28 = a;
            pose->f10 = 1.0f;
        }
        s32 copied = flags & 1;
        s32 hasWord = flags & 2;
        s32 hasF50 = flags & 0x200;
        s32 hasScale = flags & 4;
        s32 hasF3C = flags & 8;
        s32 hasFar = flags & 0x10;
        s32 hasNear = flags & 0x20;
        s32 hasAnimator = flags & 0x40;
        s32 hasVecs = flags & 0x80;
        s32 hasLink = flags & 0x100;
        if (hasWord) {
            pose->f0 = ReadBufferedU32(stream);
        }
        if (hasF50) {
            part->f50 = ReadBufferedFloat(stream);
        }
        if (hasScale) {
            f32 v = ReadBufferedFloat(stream);
            if (v == 3.402823466e+38f) {
                part->f24 = 3.402823466e+38f;
            } else {
                part->f24 = v * __builtin_fabsf(v);
            }
        }
        if (hasF3C) {
            part->f3C = ReadBufferedFloat(stream);
        }
        if (hasFar) {
            part->far = ReadBufferedFloat(stream);
            if (part->far == 3.402823466e+38f) {
                part->far = 1.0e10f;
            }
        }
        if (hasNear) {
            part->near = ReadBufferedFloat(stream);
            if (part->near == 3.402823466e+38f) {
                part->near = 2000.0f;
            }
        }
        part->near = part->far <? part->near;
        if (hasAnimator) {
            part->animator = ReadAnimator(stream);
            self->nanimators++;
        }
        if (hasVecs) {
            part->vecs = (f32*)AllocateFrontMemory(0x20);
            ReadBufferedVector3(stream, part->vecs);
            ReadBufferedVector4(stream, part->vecs + 4);
        } else {
            part->vecs = 0;
        }
        if (hasLink) {
            ModelLink* link = (ModelLink*)AllocateZeroedFrontMemory(0x90);
            link->owner = owner;
            link->part = part;
            link->id = ReadBufferedS16(stream);
            link->bone = ReadBufferedS8(stream);
            if (link->bone != -1) {
                link->f24 = ReadBufferedFloat(stream);
                link->f28 = ReadBufferedFloat(stream);
                link->f2C = ReadBufferedFloat(stream);
                link->f30 = ReadBufferedFloat(stream);
                ReadBufferedMatrix4(stream, link->matrix);
            }
            link->f10 = ReadBufferedU8(stream);
            link->f14 = ReadBufferedU8(stream);
            link->f18 = ReadBufferedU8(stream);
            part->link = link;
            link->next = self->head;
            self->head = link;
        } else {
            part->link = 0;
        }
        ReadBufferedVector3(stream, part);
        part->f10 = ReadBufferedFloat(stream);
        ReadBufferedS16(stream);
        part->f34 = ReadBufferedU8(stream);
        part->f14 = ReadBufferedU8(stream);
        part->f2C = ReadBufferedU8(stream);
        ComputeCameraFogTerms(g_camera, part->fog, part->f3C);
        if (copied) {
            CopyAttachmentPart(self, part, pose);
        } else {
            k = 0;
            part->nstrips = ReadBufferedU16(stream);
            part->strips = (ModelStrip*)AllocateZeroedFrontMemory(part->nstrips * 0x50);
            pose->packets = (StripPackets*)AllocateZeroedFrontMemory(part->nstrips * 0x30);
            for (j = 0; j < part->nstrips; j++) {
                ModelStrip* strip = &part->strips[j];
                StripPackets* pp = &pose->packets[j];
                s32 nvecs;
                s32 nnrms;
                s32 ntints;
                s32 nuvs;
                Vec3* vecs;
                Vec3* nrms;
                u8 (*tints)[4];
                MeshUv* uvs;
                s32 nrefs;
                VertexRefs* refs;
                WeightIndices* ents;
                Vec3* verts;
                Vec3* vnrms;
                StripMesh* mesh;
                f32* weights;
                PushBackMemoryMark();
                ReadBufferedVector3(stream, strip);
                strip->f10 = ReadBufferedFloat(stream);
                nvecs = ReadBufferedU8(stream);
                nnrms = ReadBufferedU8(stream);
                ntints = ReadBufferedU8(stream);
                nuvs = ReadBufferedU8(stream);
                nrefs = ReadBufferedU8(stream);
                AlignBufferedStreamPosition(stream, 4);
                vecs = (Vec3*)AllocateBackMemory(nvecs * 12);
                ReadBufferedStreamBytes(stream, nvecs * 12, vecs);
                nrms = (Vec3*)AllocateBackMemory(nnrms * 12);
                ReadBufferedStreamBytes(stream, nnrms * 12, nrms);
                tints = (u8 (*)[4])AllocateBackMemory(ntints * 4);
                ReadBufferedStreamBytes(stream, ntints * 4, tints);
                uvs = (MeshUv*)AllocateBackMemory(nuvs * 8);
                ReadBufferedStreamBytes(stream, nuvs * 8, uvs);
                refs = (VertexRefs*)AllocateBackMemory(nrefs * 4);
                ReadBufferedStreamBytes(stream, nrefs * 4, refs);
                mesh = (StripMesh*)(g_animRecords + ReadBufferedU16(stream) * 0x28);
                strip->mesh = mesh;
                strip->f14 = ReadBufferedU8(stream);
                strip->nkeys = ReadBufferedU8(stream);
                for (s32 n = 0; n < strip->nkeys; n++) {
                    strip->keys[n] = ReadBufferedU8(stream);
                }
                s32 size = strip->nkeys * nvecs * 4;
                weights = (f32*)AllocateBackMemory(size);
                ReadBufferedStreamBytes(stream, size, weights);
                if (self->nweights != 0) {
                    s32 w;
                    s32 nverts = ReadBufferedU16(stream);
                    verts = (Vec3*)AllocateBackMemory(nverts * 12);
                    ReadBufferedStreamBytes(stream, nverts * 12, verts);
                    s32 nvnrms = ReadBufferedU16(stream);
                    vnrms = (Vec3*)AllocateBackMemory(nvnrms * 12);
                    ReadBufferedStreamBytes(stream, nvnrms * 12, vnrms);
                    ents = (WeightIndices*)AllocateBackMemory(self->nweights * 8);
                    for (w = 0; w < self->nweights; w++) {
                        ents[w].pos = (u16*)AllocateBackMemory(nrefs * 2);
                        ReadBufferedStreamBytes(stream, nrefs * 2, ents[w].pos);
                        ents[w].nrm = (u16*)AllocateBackMemory(nrefs * 2);
                        ReadBufferedStreamBytes(stream, nrefs * 2, ents[w].nrm);
                    }
                }
                StripPacket pw[3];
                s32 queued = g_meshQueueCount;
                for (s32 n = 0; n < 3; n++) {
                    AllocateTempPacketBuffer(&pw[n], 0x400);
                }
                StripOutputs outs;
                ModelAnimator* anim = part->animator;
                if (anim != 0 && anim->vt->bind != 0) {
                    anim->vt->bind(anim, outs.p, self, part, strip);
                }
                switch (mesh->kind) {
                case 1:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    BuildStripMeshPacket(self, part, k++, strip, mesh, vecs, nrms, tints, uvs, nrefs, refs,
                                         ents, verts, vnrms, weights, pw, outs.p);
                    break;
                case 0:
                    BuildLitStripMeshPacket(self, part, b, k++, strip, mesh, vecs, nrms, tints, uvs, nrefs,
                                            refs, ents, verts, vnrms, weights, pw, outs.p);
                    break;
                }
                u32 starts[3];
                for (s32 n = 0; n < 3; n++) {
                    if (pw[n].cur != pw[n].begin) {
                        DetachPacketBufferCopy(&pw[n], &strip->qwc[n], &starts[n], &strip->addr[n], 0x13);
                        RemapMeshQueueValues(queued, strip->qwc[n] * 16, starts[n], strip->addr[n]);
                        MovedPointer::Fix(outs.p[1], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                        MovedPointer::Fix(outs.p[2], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                        if (strip->extra != 0) {
                            StripExtra* e = strip->extra;
                            MovedPointer::Fix(&e->f0, strip->qwc[n] * 16, starts[n], strip->addr[n]);
                            for (s32 m = 0; m < part->link->f10; m++) {
                                MovedPointer::Fix(&e->a4[m], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                                MovedPointer::Fix(&e->a14[m], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                                MovedPointer::Fix(&e->a24[m], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                            }
                        }
                    }
                }
                strip->unpack = (StripUnpack*)((u8*)strip->unpack + (strip->addr[0] - starts[0]));
                BuildPartVifPackets(part, strip, pp);
                PopBackMemoryMark();
            }
            part->nmorphs = ReadBufferedU16(stream);
            part->morphs = (ModelMorph*)AllocateZeroedFrontMemory(part->nmorphs * 32);
            for (s32 t = 0; t < part->nmorphs; t++) {
                ModelMorph* m = &part->morphs[t];
                s32 n;
                s32 nvecs;
                Vec3* vecs;
                s32 nextra;
                void* extra;
                f32* weights;
                WeightIndices* ents;
                Vec3* verts;
                PushBackMemoryMark();
                nvecs = ReadBufferedU8(stream);
                vecs = (Vec3*)AllocateBackMemory(nvecs * 12);
                ReadBufferedStreamBytes(stream, nvecs * 12, vecs);
                nextra = ReadBufferedU8(stream);
                extra = AllocateBackMemory(nextra * 4);
                ReadBufferedStreamBytes(stream, nextra * 4, extra);
                m->nkeys = ReadBufferedU8(stream);
                for (n = 0; n < m->nkeys; n++) {
                    m->keys[n] = ReadBufferedU8(stream);
                }
                s32 size = m->nkeys * nvecs * 4;
                weights = (f32*)AllocateBackMemory(size);
                ReadBufferedStreamBytes(stream, size, weights);
                if (self->nweights != 0) {
                    s32 w;
                    s32 nverts = ReadBufferedU16(stream);
                    verts = (Vec3*)AllocateBackMemory(nverts * 12);
                    ReadBufferedStreamBytes(stream, nverts * 12, verts);
                    ents = (WeightIndices*)AllocateBackMemory(self->nweights * 8);
                    for (w = 0; w < self->nweights; w++) {
                        ents[w].pos = (u16*)AllocateBackMemory(nvecs * 2);
                        ReadBufferedStreamBytes(stream, nvecs * 2, ents[w].pos);
                        ents[w].nrm = 0;
                    }
                }
                ModelPacket pw;
                InitPacketWriter(&pw);
                s32 queued = g_meshQueueCount;
                AllocateTempPacketBuffer(&pw, self->nweights * 128 + 0x400);
                BuildMorphTargetPacket(self, k++, m, nvecs, vecs, nextra, extra, ents, verts, weights, &pw);
                u32 start;
                DetachPacketBufferCopy(&pw, &m->qwc, &start, &m->addr, 0x13);
                RemapMeshQueueValues(queued, m->qwc * 16, start, m->addr);
                m->p = (u16*)((u8*)m->p + (m->addr - start));
                PopBackMemoryMark();
            }
        }
    }
    CollectNonNullRefs(self);
}

void WriteStripMeshMscal(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        WriteVifMscal(obj, D_000018C0);
        break;
    case 1:
        WriteVifMscal(obj, D_000018F8);
        break;
    }
}

void WriteMorphTargetMscal(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        WriteVifMscal(obj, D_00000FA0);
        break;
    case 1:
        WriteVifMscal(obj, D_00000FD8);
        break;
    }
}

void BuildMorphTargetPacket(MeshBuildState* self, s32 mode, MorphTargetHeader* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, void* data, PacketWriter* pkt)
{
    PacketWriter f;
    u32 buf[4];
    s32 i;
    Vec3* out;
    s32 off = 0x2B;

    ReserveVifUnpack(pkt, 0xD, 2, 0x16, 0, hdr);
    FillMemory(hdr->p, 0, 0x10);
    InitGifPacket(&f);
    AllocateTempPacketBuffer(&f, 8);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x42, 0x44);
    AddGifRegisterWrite(&f, 1, (u64)D_002623E0.r | ((u64)D_002623E0.g << 8) | ((u64)D_002623E0.b << 16)
                             | ((u64)D_002623E0.a << 24) | (1ULL << 32));
    CloseGifTag(&f, 1);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin, 0x18);
    RewindPacketBuffer(&f);
    BeginGifTag(&f, 0xC1, 3, 0x44E);
    AddGifRegisterWrite(&f, 0x47, 0x70000);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    CloseGifTag(&f, 0);
    BeginGifTag(&f, 1, 3, 0x44E);
    AddGifRegisterWrite(&f, 0x47, 0x72001);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    CloseGifTag(&f, 1);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin, 0x1B);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin + 0x40, 0x1F);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin, 0x23);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin + 0x40, 0x27);

    hdr->p[0] = off;
    off += n;
    hdr->p[1] = off;
    CopyWordsToWriter(pkt, 8, n, vecs, hdr->p[0]);
    if (hdr->count > 0)
    {
        hdr->p[4] = off;
        off += hdr->count * 4;
        hdr->p[5] = off;
        QuadClear::Clear(buf);
        off += n;
        WriteVifStrow(pkt, buf);
        WriteVifStmask(pkt, D_002623E8[hdr->count]);
        CopyWordsToWriter(pkt, D_00262400[hdr->count], n, data, hdr->p[5]);
        WriteVifStmask(pkt, 0);
    }
    s32 end = off + extra;
    if (self->f40 != 0)
    {
        hdr->p[5] = off;
        hdr->p[6] = self->f40 + off;
        for (i = 0; i < self->f40; i++)
        {
            CopyWordsToWriter(pkt, 0, 1, &i, 0x1D);
            ReserveVifUnpack(pkt, 8, n, hdr->p[6], 0, &out);
            u16* idx = ents[i].pos;
            for (s32 k = 0; k < n; k++)
            {
                Vec3* v = &verts[idx[k]];
                out[k].x = v->x - vecs[k].x;
                out[k].y = v->y - vecs[k].y;
                out[k].z = v->z - vecs[k].z;
            }
            WriteVifMscal(pkt, D_00001298);
            WriteVifFlushE(pkt);
        }
    }
    hdr->p[2] = off;
    hdr->p[3] = end;
    CopyWordsToWriter(pkt, 0xE, extra, extraData, hdr->p[2]);
    WriteMorphTargetMscal(mode, pkt);
    WriteVifMscal(pkt, D_00001368);
    WriteVifMscal(pkt, D_00000ED8);
}

void BuildStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 mode, StripHeader* hdr, StripMesh* mesh,
                   Vec3* vecs, s32 unused6, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, s32 unused13, f32* weights, PacketWriter* pkt,
                   s32** outs)
{
    u32 buf[4];
    f32* uvOut;
    f32* posOut;
    s32 a;
    s32 b;
    f32* wOut;
    s32 k;
    Vec3* dOut;
    u8* cOut;
    s32 c;
    s32 d;
    s32 off;
    s32 hasUv;
    s32 tinted;
    void* tail;
    void* head;
    AnimCursor* node;
    s32 i;
    VertexRefs* r;

    if (obj->f54 != 0) {
        BeginDmaTag(pkt);
    }
    ReserveVifUnpack(pkt, 0xD, 3, 0xB, 0, &hdr->p);
    off = 0x24;
    FillMemory(hdr->p, 0, 0x18);
    hdr->p->f10 = 3;
    hdr->p->off[0] = off;
    off = n * 3 + 0x24;
    hdr->p->off[1] = off;
    switch (mesh->kind) {
    case 1:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        head = D_000002F8;
        tail = D_00001A50;
        tinted = 1;
        hasUv = 1;
        break;
    case 4:
        head = D_000036D0;
        tail = D_00001A80;
        hasUv = mesh->mode & 2;
        tinted = hasUv;
        break;
    case 9:
        head = D_000002F8;
        tail = D_00001A50;
        hasUv = 0;
        tinted = 1;
        break;
    }
    cOut = 0;
    uvOut = 0;
    WriteVifStcycl(pkt, 1, 3);
    if (hasUv) {
        ReserveVifUnpack(pkt, 8, n, hdr->p->off[0], 0, &uvOut);
    }
    ReserveVifUnpack(pkt, 0xC, n, hdr->p->off[0] + 2, 0, &posOut);
    WriteVifStcycl(pkt, 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    if (obj->f54 != 0) {
        StripExtra* e = (StripExtra*)AllocateZeroedFrontMemory(0x34);
        hdr->extra = e;
        e->f0 = (s32)posOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        if (hasUv) {
            if (r->uv == 0xFF) {
                uvOut[0] = uvOut[1] = 0.0f;
            } else {
                uvOut[0] = uvs[r->uv].u;
                uvOut[1] = uvs[r->uv].v;
            }
            uvOut[2] = 1.0f;
            uvOut += 3;
        }
        *(Vec3*)posOut = vecs[recs[i].pos];
        if (recs[i].flags >> 7) {
            posOut[3] = obj->f40 + 32768.0f;
        } else {
            posOut[3] = obj->f40 + 28672.0f;
        }
        posOut += 4;
    }
    node = 0;
    if (obj->f38 != 0) {
        node = obj->f38->vt[5](obj->f38, mesh);
    }
    if (node == 0 && mesh->hook != 0) {
        node = ((CursorHook*)mesh->hook)->vt[5]((CursorHook*)mesh->hook, mesh);
    }
    WriteStripMeshMscal(mode, pkt);
    if (node != 0 && (node->flags & 2)) {
        ReserveVifUnpack(pkt, 4, 1, 0x16, &a, &b);
        QueueNodeLink(b, a, node);
        WriteVifMscal(pkt, D_000027C0);
    }
    if (hdr->count > 0) {
        hdr->p->off[2] = off;
        off += hdr->count * 4;
        hdr->p->off[3] = off;
        off += n;
        FillMemory(buf, 0, 0x10);
        WriteVifStrow(pkt, buf);
        WriteVifStmask(pkt, D_00262418[hdr->count]);
        ReserveVifUnpack(pkt, D_00262430[hdr->count], n, hdr->p->off[3], 0, &wOut);
        WriteVifStmask(pkt, 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        WriteVifMscal(pkt, D_00002008);
    }
    if (self->f40 != 0) {
        hdr->p->off[3] = off;
        off += self->f40;
        hdr->p->strip[3] = off;
        for (k = 0; k < self->f40; k++) {
            if (k > 0) {
                WriteVifFlushE(pkt);
            }
            CopyWordsToWriter(pkt, 0, 1, &k, 0x16);
            ReserveVifUnpack(pkt, 8, n, hdr->p->strip[3], 0, &dOut);
            u16* idx = ents[k].pos;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            WriteVifMscal(pkt, D_000023B8);
        }
    }
    if (hdr->extra != 0) {
        StripExtra* e = hdr->extra;
        for (s32 i = 0; i < obj->f54->f10; i++) {
            ReserveVifUnpack(pkt, 0xC, n, off, 0, &e->a24[i]);
            if (obj->f54->f18 != 0) {
                WriteVifUnpack(pkt, 0xC, 4, 0, 0x16, &e->a14[i]);
                WriteVifMscal(pkt, D_00003A80);
                WriteVifFlushE(pkt);
            }
            if (obj->f54->f14 != 0) {
                WriteVifUnpack(pkt, 0xC, 4, 0, 0x16, &e->a4[i]);
                WriteVifMscal(pkt, D_00003A90);
                WriteVifFlushE(pkt);
            }
        }
        hdr->p->off[3] = off;
        off += n;
    }
    WriteVifMscal(pkt, tail);
    if (tinted) {
        WriteVifStcycl(pkt, 1, 3);
        ReserveVifUnpack(pkt, 0xE, n, hdr->p->off[0] + 1, 0, &cOut);
        WriteVifStcycl(pkt, 1, 1);
        for (i = 0; i < n; i++) {
            s32 j;
            r = &recs[i];
            if ((r->flags & 0x7F) == 0x7F) {
                for (j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] + 1) >> 1;
                }
            } else {
                for (j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] * tints[r->flags & 0x7F][j] + 0x100) / 0x1FE;
                }
            }
            cOut += 4;
        }
    }
    for (s32 i = 0; i < mesh->nstrips; i++) {
        FrameSource* s = &mesh->strips[i];
        ReserveVifUnpack(pkt, 0xC, s->stride, off, &c, &d);
        QueueMeshStrip(mesh, s, d, c, n, node);
        hdr->p->strip[i] = off;
        off += s->stride;
    }
    WriteVifMscalf(pkt, head);
    if (obj->f54 != 0) {
        CloseDmaTag(pkt);
        AddDmaReturnTag(pkt);
    }
}

void BuildLitStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 unused2, s32 mode, StripHeader* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, PacketSlot* pkt, s32** outs)
{
    u32 buf[4];
    f32* posOut;
    f32* wOut;
    s32 k;
    Vec3* dOut;
    QuadLanes* quads;
    f32* nOut;
    u8* cOut;
    Vec3* nDelta;
    f32* uvOut;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 off;
    AnimCursor* node;
    s32 i;
    VertexRefs* r;

    if (obj->f54 != 0) {
        BeginDmaTag(&pkt[2]);
    }
    obj->f18 = 1;
    ReserveVifUnpack(&pkt[0], 0xD, 3, 0xB, 0, &hdr->p);
    off = 0x24;
    FillMemory(hdr->p, 0, 0x18);
    hdr->p->f10 = 4;
    hdr->p->f12 = hdr->f14 * 0x7FA6 / 0xFF;
    hdr->p->off[0] = off;
    off = n * 4 + 0x24;
    hdr->p->off[1] = off;
    if (hdr->count != 0 || self->f40 != 0) {
        obj->f28 = 1;
    }
    if (obj->f28 != 0) {
        off += (((n + 3) & ~3) - n) * 4;
    }
    hdr->p->strip[3] = off;
    off += n;
    WriteVifStcycl(&pkt[0], 1, 4);
    ReserveVifUnpack(&pkt[0], 0xC, n, hdr->p->off[0] + 3, 0, &posOut);
    WriteVifStcycl(&pkt[0], 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (obj->f54 != 0) {
        StripExtra* e = (StripExtra*)AllocateZeroedFrontMemory(0x34);
        hdr->extra = e;
        e->f0 = (s32)posOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        *(Vec3*)posOut = vecs[r->pos];
        if (r->flags >> 7) {
            posOut[3] = obj->f40 + 32768.0f;
        } else {
            posOut[3] = obj->f40 + 28672.0f;
        }
        posOut += 4;
    }
    WriteStripMeshMscal(mode, &pkt[0]);
    if (hdr->count > 0) {
        hdr->p->off[2] = off;
        off += hdr->count * 4;
        hdr->p->off[3] = off;
        off += n;
        FillMemory(buf, 0, 0x10);
        WriteVifStrow(&pkt[0], buf);
        WriteVifStmask(&pkt[0], D_00262448[hdr->count]);
        ReserveVifUnpack(&pkt[0], D_00262460[hdr->count], n, hdr->p->off[3], 0, &wOut);
        WriteVifStmask(&pkt[0], 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        WriteVifMscal(&pkt[0], D_00002008);
    }
    if (self->f40 != 0) {
        hdr->p->off[3] = off;
        off += self->f40;
        for (k = 0; k < self->f40; k++) {
            CopyWordsToWriter(&pkt[0], 0, 1, &k, 0x16);
            ReserveVifUnpack(&pkt[0], 8, n, hdr->p->strip[3], 0, &dOut);
            u16* idx = ents[k].pos;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            WriteVifMscal(&pkt[0], D_000023B8);
            WriteVifFlushE(&pkt[0]);
        }
    }
    WriteVifStcycl(&pkt[1], 1, 4);
    if (obj->f28 != 0 && hdr->count == 0 && self->f40 == 0) {
        ReserveVifUnpack(&pkt[1], 0xC, (n + 3) & ~3, hdr->p->off[0], 0, &quads);
        nOut = 0;
    } else {
        ReserveVifUnpack(&pkt[1], 0xC, n, hdr->p->off[0], 0, &nOut);
        quads = 0;
    }
    ReserveVifUnpack(&pkt[1], 0xE, n, hdr->p->off[0] + 1, 0, &cOut);
    WriteVifStcycl(&pkt[1], 1, 1);
    if (hdr->count > 0) {
        WriteVifMscal(&pkt[1], D_00002088);
    }
    if (self->f40 > 0) {
        for (s32 m = 0; m < self->f40; m++) {
            if (m > 0) {
                WriteVifFlushE(&pkt[1]);
            }
            ReserveVifUnpack(&pkt[1], 8, n, hdr->p->strip[3], 0, &nDelta);
            u16* idx = ents[m].nrm;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3* v = &vnrms[idx[i]];
                nDelta[i].x = v->x - nrms[r->nrm].x;
                nDelta[i].y = v->y - nrms[r->nrm].y;
                nDelta[i].z = v->z - nrms[r->nrm].z;
            }
            WriteVifMscal(&pkt[1], D_000023D8);
        }
        WriteVifMscal(&pkt[1], D_000023F0);
    }
    WriteVifMscal(&pkt[1], D_00000288);
    for (i = 0; i < n; i++) {
        s32 j;
        r = &recs[i];
        if ((r->flags & 0x7F) == 0x7F) {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] + 1) >> 1;
            }
        } else {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] * tints[r->flags & 0x7F][j] + 0x100) / 0x1FE;
            }
        }
        if (nOut != 0) {
            if (r->nrm == 0xFF) {
                nOut[0] = nOut[1] = nOut[2] = 0.0f;
            } else {
                *(Vec3*)nOut = nrms[r->nrm];
            }
            nOut[3] = (cOut[0] + cOut[1] + cOut[2]) * 0.33333334f;
            nOut += 4;
        }
        cOut += 4;
    }
    if (quads != 0) {
        for (i = 0; i < n; i += 4) {
            for (s32 j = 0; j < 4; j++) {
                if (i + j < n) {
                    quads->x[j] = nrms[recs[i + j].nrm].x;
                    quads->y[j] = nrms[recs[i + j].nrm].y;
                    quads->z[j] = nrms[recs[i + j].nrm].z;
                } else {
                    quads->x[j] = quads->y[j] = quads->z[j] = 0.0f;
                }
            }
            FillMemory(quads->w, 0, 0x10);
            quads++;
        }
    }
    WriteVifStcycl(&pkt[2], 1, 4);
    ReserveVifUnpack(&pkt[2], 8, n, hdr->p->off[0], 0, &uvOut);
    WriteVifStcycl(&pkt[2], 1, 1);
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        if (r->uv == 0xFF) {
            uvOut[0] = uvOut[1] = 0.0f;
        } else {
            uvOut[0] = uvs[r->uv].u;
            uvOut[1] = uvs[r->uv].v;
        }
        uvOut[2] = 1.0f;
        uvOut += 3;
    }
    node = 0;
    if (obj->f38 != 0) {
        node = obj->f38->vt[5](obj->f38, mesh);
    }
    if (node == 0 && mesh->hook != 0) {
        node = ((CursorHook*)mesh->hook)->vt[5]((CursorHook*)mesh->hook, mesh);
    }
    if (node != 0 && (node->flags & 2)) {
        ReserveVifUnpack(&pkt[2], 4, 1, 0x16, &a, &b);
        QueueNodeLink(b, a, node);
        WriteVifMscal(&pkt[2], D_000027C0);
    }
    if (hdr->extra != 0) {
        StripExtra* e = hdr->extra;
        for (s32 i = 0; i < obj->f54->f10; i++) {
            ReserveVifUnpack(&pkt[2], 0xC, n, off, 0, &e->a24[i]);
            if (obj->f54->f18 != 0) {
                WriteVifUnpack(&pkt[2], 0xC, 4, 0, 0x16, &e->a14[i]);
                WriteVifMscal(&pkt[2], D_00003A80);
                WriteVifFlushE(&pkt[2]);
            }
            if (obj->f54->f14 != 0) {
                WriteVifUnpack(&pkt[2], 0xC, 4, 0, 0x16, &e->a4[i]);
                WriteVifMscal(&pkt[2], D_00003AA0);
                WriteVifFlushE(&pkt[2]);
            }
        }
        hdr->p->off[3] = off;
        off += n;
    }
    WriteVifMscal(&pkt[2], D_00001AB0);
    s32 slot = 0;
    for (s32 i = 0; i < mesh->nstrips; i++) {
        FrameSource* s = &mesh->strips[i];
        ReserveVifUnpack(&pkt[2], 0xC, s->stride, off, &c, &d);
        QueueMeshStrip(mesh, s, d, c, n, node);
        hdr->p->strip[slot++] = off;
        off += s->stride;
    }
    if (obj->f54 != 0) {
        CloseDmaTag(&pkt[2]);
        AddDmaReturnTag(&pkt[2]);
    }
}

void BuildPartVifPackets(PartPacketContext* a, PartPacketSource* b, PartPackets* c)
{
    u8 buf[0x30];
    s32 s0;

    if (*b->f18 != 0) return;
    if (a->f28 != 0) return;
    InitPacketWriter(buf);
    s0 = (b->f1C->hi - b->f1C->lo) / 4;
    AllocateQuadwordBuffer(buf, (u32)((s0 + 7) / 4), 0x1A);
    WriteVifStcycl(buf, 1, 4);
    ReserveVifUnpack(buf, 0xE, s0, b->f1C->lo + 1, 0, &c->f8);
    WriteVifStcycl(buf, 1, 1);
    WriteVifMscal(buf, D_00000010);
    DetachPacketBuffer(buf, &c->f0, &c->f4);
    AllocateQuadwordBuffer(buf, (u32)((s0 + 4) / 2), 0x1A);
    WriteVifStcycl(buf, 1, 4);
    ReserveVifUnpack(buf, 0xE, s0, b->f1C->lo + 2, 0, &c->f14);
    WriteVifStcycl(buf, 1, 1);
    ReserveVifUnpack(buf, 0xE, s0, b->f1C->hi, 0, 0);
    WriteVifMscal(buf, D_000000F0);
    DetachPacketBuffer(buf, &c->fC, &c->f10);
}

void StartAttachments(AttachmentBlock* self, PlacedObject* ctx)
{
    for (s32 i = 0; i < self->count0C; i++)
    {
        AttachmentEntry* e = self->f10 + i;
        AttachmentHandler* o = e->f38;
        if (o != 0)
        {
            o->vtbl[1](o);
        }
        BuildAttachmentDmaChain(self, e, self->f14 + i * 0x28, ctx);
    }
    AttachmentNode* n = self->f4C;
    if (n != 0)
    {
        do
        {
            void* v = FindFirstObjectById(ctx->world, 0x104, n->f8, ctx);
            if (v != 0)
            {
                AttachNodeToOwner(v, ctx, n->f4);
            }
            n = n->next80;
        } while (n != 0);
    }
}

void BindAttachmentTargets(AttachmentTargets* self, PlacedObject* ctx)
{
    TargetFrames f;
    s32 i;

    for (i = 0; i < self->count; i++) {
        AttachmentTarget* e = &self->elems[i];
        TargetObject* r = (TargetObject*)FindFirstObjectByIdMode4(ctx->world, self->keys[i], ctx);
        e->p0 = r;
        if (r != 0) {
            BuildMatrixFromRotationAndTranslation(&ctx->v140, &ctx->m110, &f.a);
            InvertRigidTransform(&e->p0->sub140, &e->p0->sub110, &f.b);
            MultiplyMatrices(&f.m, &f.b, &f.a);
            e->m = f.m;
        }
    }
}

void CopyAttachmentBlock(AttachmentCopy* self, s32 arg, void* src)
{
    s32 i = 0;
    AttachmentLink** link;
    CopyMemory(self, src, 0x58);
    self->f50 = 0;
    self->p4 = AllocateZeroedFrontMemory(self->n0 * 0x90);
    self->p44 = CopyToFrontMemory(self->n40 << 2, self->p44);
    self->p14 = CopyToFrontMemory(self->count * 0x28, self->p14);
    AttachmentPart* old = self->recs;
    for (; i < self->count; i++) {
        AttachmentPart* r = (AttachmentPart*)((u8*)self->recs + i * 0x70);
        if ((r->a && (r->a->flags & 4)) || r->b) {
            self->recs = (AttachmentPart*)CopyToFrontMemory(self->count * 0x70, self->recs);
            break;
        }
    }
    link = &self->head;
    AttachmentLink* s = self->head;
    if (s) {
        do {
            AttachmentLink* n = (AttachmentLink*)CopyToFrontMemory(0x90, s);
            n->tag = arg;
            AttachmentLink** pf = &n->p4;
            u32 sz = self->count * 0x70;
            u32 nb = (u32)self->recs;
            if (pf) {
                u32 v = (u32)n->p4;
                if (!(v < (u32)old) && v < (u32)old + sz)
                    n->p4 = (AttachmentLink*)(v + (nb - (u32)old));
            }
            ((AttachmentPart*)n->p4)->b = n;
            *link = n;
            link = &n->next;
            s = n->next;
        } while (s);
    }
    *link = 0;
    i = 0;
    if (self->count > 0) {
        s32 b = 0, a = 0;
        do {
            i++;
            CopyAttachmentPart(self, (u8*)self->recs + a, (u8*)self->p14 + b);
            a += 0x70;
            b += 0x28;
        } while (i < self->count);
    }
    CollectNonNullRefs(self);
}

// What CopyAttachmentPart copies: a part's 0x50-byte entries (the mesh, a record of pointers
// into its three buffers, the buffers' sizes and the buffers) and the 0x28-byte record built
// for the part.
struct PartPointers {
    void* f00;              // 0x00
    void* a[4];             // 0x04
    void* b[4];             // 0x14
    void* c[4];             // 0x24
};
struct PartEntry {
    u8 pad00[0x18];
    StripMesh* mesh;        // 0x18
    u8 pad1C[0x20 - 0x1C];
    PartPointers* pointers; // 0x20
    u8 pad24[0x38 - 0x24];
    s32 sizes[3];           // 0x38: quadwords
    void* buffers[3];       // 0x44
    u8 pad50[0x50 - 0x50];
};
struct CopiedPart {
    u8 pad00[0x38];
    CursorAnimator* animator;   // 0x38
    u8 pad3C[0x54 - 0x3C];
    void* f54;              // 0x54
    s32 count;              // 0x58
    PartEntry* entries;     // 0x5C
};
struct PartRecord {
    u8 pad00[0x04];
    u8* packets;            // 0x04: 0x30 bytes an entry
};
extern FrameTarget D_0027DC20[];
s32 GetAnimatorSize(s32 type);

// Moves a pointer that points into the block at `from` (`size` bytes) to the same place in the
// block at `to`.
static inline void MovePointerInto(void** p, u8* from, s32 size, u8* to)
{
    if (p != 0 && !((u8*)*p < from) && (u8*)*p < from + size) {
        *p = (u8*)*p + (to - from);
    }
}

// Retail reads part->animator again after the count's store, so the count is its own statement;
// the detached list is walked through a variable of its own (`lw v0; move s0,v0`: the load can't
// pass the store of 0 into the loop's variable); and the strip search reads e->mesh at each use:
// PRE then loads it once in the loop's entry, after NOTE_INSN_LOOP_BEG, and loop.c calls the loop
// phony and moves nothing out of it (retail reloads the count, the strips and the frame each time).
void CopyAttachmentPart(AttachmentCopy* owner, void* partp, void* recp)
{
    CopiedPart* part = (CopiedPart*)partp;
    PartRecord* rec = (PartRecord*)recp;
    rec->packets = (u8*)CopyToFrontMemory(part->count * 0x30, rec->packets);
    if (part->animator != 0) {
        owner->f50++;
    }
    s32 animated = part->animator != 0 && (part->animator->cursor.flags & 4) != 0;
    s32 linked = part->f54 != 0;
    s32 first;
    if (animated || linked) {
        first = g_meshQueueCount;
        part->entries = (PartEntry*)CopyToFrontMemory(part->count * 0x50, part->entries);
        if (part->animator != 0) {
            part->animator = (CursorAnimator*)CopyToFrontMemory(GetAnimatorSize(part->animator->type), part->animator);
            AnimCursor* cursor = &part->animator->cursor;
            FrameLink* links = cursor->links;
            cursor->links = 0;
            for (FrameLink* link = links; link != 0; link = link->next) {
                FrameTarget* t = link->dst;
                if (link->src != 0) {
                    QueueMeshStrip((StripMesh*)cursor->record, link->src, t->dstAddr, t->count, t->flag, cursor);
                } else {
                    QueueNodeLink(t->dstAddr, t->count, cursor);
                }
            }
        }
    }
    for (s32 i = 0; i < part->count; i++) {
        PartEntry* e = &part->entries[i];
        u8* packets = rec->packets + i * 0x30;
        if (animated || linked) {
            for (s32 j = 0; j < 3; j++) {
                u8* old = (u8*)e->buffers[j];
                if (old != 0) {
                    s32 size = e->sizes[j] << 4;
                    u8* end = old + size;
                    e->buffers[j] = CopyToFrontMemory(size, old);
                    for (s32 k = 0; k < first; k++) {
                        FrameTarget* t = &D_0027DC20[k];
                        if (!((u8*)t->dstAddr < old) && (u8*)t->dstAddr < end) {
                            s32 again = 0;
                            for (s32 m = first; m < g_meshQueueCount; m++) {
                                FrameTarget* q = &D_0027DC20[m];
                                if (q->dstAddr == t->dstAddr) {
                                    again = 1;
                                    break;
                                }
                            }
                            if (again == 0) {
                                FrameSource* strip = 0;
                                for (s32 n = 0; n < e->mesh->nstrips; n++) {
                                    FrameSource* s = &e->mesh->strips[n];
                                    u32 limit = (u32)s->base + ((*(s32*)((u8*)e->mesh + 0x20) * s->stride) << 4);
                                    if (!((u32)t->value < (u32)s->base) && (u32)t->value < limit) {
                                        strip = s;
                                        break;
                                    }
                                }
                                QueueMeshStrip(e->mesh, strip, t->dstAddr, t->count, t->flag, 0);
                            }
                        }
                    }
                    RemapMeshQueueValues(first, size, (u32)old, (u32)e->buffers[j]);
                    if (linked) {
                        e->pointers = (PartPointers*)CopyToFrontMemory(0x34, e->pointers);
                        MovePointerInto(&e->pointers->f00, old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                        for (s32 k = 0; k < 4; k++) {
                            MovePointerInto(&e->pointers->a[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                            MovePointerInto(&e->pointers->b[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                            MovePointerInto(&e->pointers->c[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                        }
                    }
                }
            }
        }
        BuildPartVifPackets((PartPacketContext*)part, (PartPacketSource*)e, (PartPackets*)packets);
    }
}

void UpdateAttachments(AnimatorOwner* self, PlacedObject* sub, f32 f)
{
    AnimatorStep* e;
    s32 i;

    for (i = 0; i < sub->elemCount; i++) {
        e = ((AnimatorStep**)sub->elems)[i];
        if (ClaimAnimatorStep(e) != 0) {
            AnimatorStepFn fn = e->vtbl[2];
            if (fn != 0) {
                fn(e, f);
            }
        }
    }
    for (e = self->head4C; e != 0; e = e->next80) {
        EvaluateOscillator(e->f0C);
    }
}

void UpdateLinkConstraint(PlacedObject* self)
{
    u8* p=(u8*)self->f224;
    if (p && (*(s32*)(p+0xB0)&16) && *(s32*)(p+0x64)) ApplyLinkConstraint(*(void**)(p+0x60));
}

void UpdateAttachmentFrames(PlacedObject* self, ParentFrame* par)
{
    QuadMatrix a;
    QuadMatrix b;
    QuadMatrix c;
    QuadMatrix e;
    s32 i;
    FramedAttachmentList* l = (FramedAttachmentList*)self->sub22C;

    if (l->count > 0) {
        InvertRigidTransform(&self->v140, &self->m110, &a);
        if (par != 0) {
            InvertRigidTransform((u8*)par + 0x30, par, &b);
        } else {
            b = a;
        }
        for (i = 0; i < l->count; i++) {
            FramedAttachment* el = (FramedAttachment*)((u8*)l->items + (i << 4) * 9);
            if (el->obj != 0) {
                el->obj->vt->f(el->obj);
                FrameLinkConstraint* t = el->obj->link;
                if (t != 0 && (t->flags & 0x80) && t->a4 != 0) {
                    c = t->m60;
                    e = MultiplyMatrices(b, &c);
                } else {
                    BuildMatrixFromRotationAndTranslation(el->obj->sub140, el->obj->sub110, &c);
                    e = MultiplyMatrices(a, &c);
                }
                el->m50 = MultiplyMatrices(e, &el->q10);
            }
        }
    }
}

struct Buf_1662A8 { u8 pad[0x30]; };
struct Q_1662A8 { u64 a; u64 b; };
struct Cmd_1662A8 {
    u8 pad0[0x18]; u8* f18; u8 pad1C[0x24 - 0x1C]; s32 f24; u8 pad28[0x38 - 0x28];
    s32 f38; u8 pad3C[4]; s32 f40; s32 f44; u8 pad48[4]; s32 f4C;
};
struct Row_1662A8 { s32 f0, f4, f8, fC, f10; u8 pad14[0x30 - 0x14]; };
struct Spr_1662A8 { u8 pad0[4]; s32 f4; u8 pad8[0x18 - 8]; s32 f18, f1C; };
struct Cfg_1662A8 {
    u8 pad0[0x28]; s32 f28; u8 pad2C[0x54 - 0x2C]; s32 f54; s32 f58; Cmd_1662A8* f5C; s32 f60; Spr_1662A8* f64;
};
struct Out_1662A8 { u8 pad0[4]; Row_1662A8* f4; u8 pad8[0x18 - 8]; s32 f18[2]; s32 f20[2]; };
struct Self_1662A8 { u8 pad[0x40]; s32 f40; };

Buf_1662A8* InitPacketWriter(Buf_1662A8* b);
void AllocateTempPacketBuffer(Buf_1662A8* b, s32 n);
void BeginDmaTag(Buf_1662A8* b);
void WriteVifBaseOffset(Buf_1662A8* b, s32 n, s32 f);
void CloseDmaTag(Buf_1662A8* b);
void AddDmaRefTag(Buf_1662A8* b, s32 x, s32 y);
void AddDmaCallTag(Buf_1662A8* b, s32 x);
void CopyWordsToWriter(Buf_1662A8* b, s32 a, s32 c, Q_1662A8* q, s32 d);
void AddDmaReturnTag(Buf_1662A8* b);
void DetachPacketBufferCopy(Buf_1662A8* b, s32* a1, s32 a2, s32* a3, s32 a4);

void BuildAttachmentDmaChain(void* selfArg, void* cfgArg, void* outArg, void* ctx)
{
    Self_1662A8* self = (Self_1662A8*)selfArg;
    Cfg_1662A8* cfg = (Cfg_1662A8*)cfgArg;
    Out_1662A8* out = (Out_1662A8*)outArg;
    Buf_1662A8 buf;
    Q_1662A8 q;
    s32 pass;
    s32 i, k;
    s32 n;
    s32 sz;

    InitPacketWriter(&buf);
    if (cfg->f28) return;
    if (!out) return;
    if (self->f40) return;
    for (i = 0; i < cfg->f58; i++) {
        if (cfg->f5C[i].f24) return;
    }
    for (k = 0; k < cfg->f60; k++) {
        if (cfg->f64[k].f4) return;
    }
    for (pass = 0; pass < 2; pass++) {
        s32 total = 0x23C;
        sz = 0x214;
        PushBackMemoryMark();
        AllocateTempPacketBuffer(&buf, 0x1000);
        n = 0;
        if (pass == 0) sz = 0x28;
        s32 co, ro;
        i = 0;
        if (i < cfg->f58) {
        ro = 0; co = 0;
        do {
            Cmd_1662A8* c;
            Row_1662A8* r;
            s32 prev;
            c = (Cmd_1662A8*)((u8*)cfg->f5C + co);
            r = (Row_1662A8*)((u8*)out->f4 + ro);
            sz = total - sz;
            if (n++ > 0) {
                BeginDmaTag(&buf);
                WriteVifBaseOffset(&buf, sz, 0);
                CloseDmaTag(&buf);
            }
            switch (*c->f18) {
            case 0:
                AddDmaRefTag(&buf, c->f38, c->f44);
                if (cfg->f54) {
                    AddDmaCallTag(&buf, c->f4C);
                } else {
                    AddDmaRefTag(&buf, c->f40, c->f4C);
                }
                AddDmaRefTag(&buf, r->f0, r->f4);
                AddDmaRefTag(&buf, r->fC, r->f10);
                break;
            case 1:
            case 4: case 5: case 6: case 7: case 8: case 9: case 10:
                if (cfg->f54) {
                    AddDmaCallTag(&buf, c->f44);
                } else {
                    AddDmaRefTag(&buf, c->f38, c->f44);
                }
                break;
            }
            i++; ro += sizeof(Row_1662A8); co += sizeof(Cmd_1662A8);
        } while (i < cfg->f58);
        }
        for (k = 0; k < cfg->f60; k++) {
            Spr_1662A8* s = &cfg->f64[k];
            sz = total - sz;
            BeginDmaTag(&buf);
            if (n++ > 0) WriteVifBaseOffset(&buf, sz, 0);
            q.b = 1;
            q.a = (u64)D_002623E0.r | ((u64)D_002623E0.g << 8) | ((u64)D_002623E0.b << 16) | ((u64)D_002623E0.a << 24) | ((u64)1 << 32);
            CopyWordsToWriter(&buf, 0xC, 1, &q, 0x1A);
            CloseDmaTag(&buf);
            AddDmaRefTag(&buf, s->f18, s->f1C);
        }
        AddDmaReturnTag(&buf);
        DetachPacketBufferCopy(&buf, &out->f18[pass], 0, &out->f20[pass], 0x19);
        PopBackMemoryMark();
        if (n < 2) {
            out->f18[1] = out->f18[0];
            out->f20[1] = out->f20[0];
            return;
        }
    }
}

void FlipVifBaseOffset(void)
{
    s32 v = 0x23C - D_00262474;
    D_00262474 = v;
    WriteVifBaseOffset(&g_vifPacketWriter, v, 0);
}

// The part drawer func_001533A8 runs for each 0x70-byte part of a placed object: it writes the
// part's header block, its bone matrices and weights and the DMA references of its meshes.
struct Bone_166690 { u8 pad0[0x50]; Mat4 m; };
struct Skin_166690 {
    u8 pad0[4];
    Bone_166690* bones;     // 0x04
    u8 pad8[0x38 - 0x8];
    u32 flags;              // 0x38
    u8 r, g, b, a;          // 0x3C
    s32 count;              // 0x40
    s32* words;             // 0x44
};
struct Slots_166690 { u16 f0; u16 f2; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; };
struct Mesh_166690 {
    Quad16 pos;             // 0x00
    f32 f10;                // 0x10
    u8 pad14[4];
    u8* kind;               // 0x18
    Slots_166690* slots;    // 0x1C
    u8 pad20[4];
    s32 nbones;             // 0x24
    s32 bones[4];           // 0x28
    s32 f38;                // 0x38
    s32 f3C;                // 0x3C
    s32 f40;                // 0x40
    s32 f44;                // 0x44
    s32 f48;                // 0x48
    s32 f4C;                // 0x4C
};
struct Strip_166690 {
    Slots_166690* slots;    // 0x00
    s32 nbones;             // 0x04
    s32 bones[4];           // 0x08
    s32 f18;                // 0x18
    s32 f1C;                // 0x1C
};
struct Light_166690 { u8 pad0[0x27C]; void* f27C; };
struct Part_166690 {
    u8 pad0[0x10];
    f32 f10;                // 0x10
    u8 pad14[4];
    s32 f18;                // 0x18
    u8 pad1C[0x28 - 0x1C];
    s32 f28;                // 0x28
    u32 flags;              // 0x2C
    u8 pad30[0x40 - 0x30];
    QuadP f40;              // 0x40
    f32 f50;                // 0x50
    s32 f54;                // 0x54
    s32 nmeshes;            // 0x58
    Mesh_166690* meshes;    // 0x5C
    s32 nstrips;            // 0x60
    Strip_166690* strips;   // 0x64
    u8 pad68[4];
    Light_166690* light;    // 0x6C
};
struct Cache_166690 {
    s32 f00;                // 0x00
    s32 f04;                // 0x04
    u8 pad08[4];
    s32 f0C;                // 0x0C
    s32 f10;                // 0x10
    u8 pad14[4];
    f32 f18;                // 0x18
    s32 count;              // 0x1C
    void* nodes[4];         // 0x20
};
struct CacheSet_166690 {
    u8 pad0[4];
    Cache_166690* items;    // 0x04
    s32 f8;                 // 0x08
    s32 fC;                 // 0x0C
    u8 pad10[0x18 - 0x10];
    s32 f18;                // 0x18
    u8 pad1C[0x20 - 0x1C];
    s32 refs[2];            // 0x20
};
struct Class_166690 { u8 pad0[8]; u32 flags; };
struct Owner_166690 { Class_166690* cls; u8 pad4[0x410 - 4]; s32 f410; };
struct Frame_166690 {
    u8 pad0[0x10];
    Mat4A m;                // 0x10
    f32 f50;                // 0x50
    f32 f54;                // 0x54
    u8 pad58[8];
    Quad16 f60;             // 0x60
    Owner_166690* owner;    // 0x70
    Skin_166690* skin;      // 0x74
    Part_166690* part;      // 0x78
    CacheSet_166690* cache; // 0x7C
};
struct Batch_166690 {
    Mat4A m;                // 0x00
    Mat4A m40;              // 0x40
    QuadP f80;              // 0x80
    f32 f90;                // 0x90
    s32 mode;               // 0x94
    s32 f98;                // 0x98
    s32 f9C;                // 0x9C
    union {
        Quad16 fA0;         // 0xA0
        struct { f32 pad[3]; f32 fAC; } w;
    };
};
struct Qw_166690 { u64 lo; u64 hi; };
struct World_166690 { u8 pad0[0x234C]; f32 f234C; };
extern s32 g_lightingChangeFrame;
extern s32 g_lightCount;
extern s32 g_frameCount;
extern Quad4* g_buildFrameData;
extern f32 g_gameClock[];
extern f32 g_gameTime;
void CollectRangeRecordsInReach(World* world, void* pos, s32 max, s32* count, void** out, f32 r);
s32 RangeRecordMatchesKinds(void* node, u32 bits);
s32 RangeRecordReachesSphere(void* node, void* v, f32 f);
void QueueRangeRecordPacket(void* node);
struct Vif_166690 {
    static u32* Open(PacketWriter* w)
    {
        u32* tag = (u32*)w->cur;
        *(u64*)w->cur = 0x10000000;
        w->cur += 16;
        return tag;
    }
    static void Cnt1(PacketWriter* w)
    {
        *(u64*)w->cur = 0x10000001;
        w->cur += 16;
    }
    static void Word(PacketWriter* w, u32 v)
    {
        *(u32*)w->cur = v;
        w->cur += 4;
    }
    static void Copy(PacketWriter* w, void* src, s32 size)
    {
        WordCopy::Words(w->cur, src, size >> 2);
        w->cur += size;
    }
    static void Pad(PacketWriter* w)
    {
        while (w->curU & 0xF) {
            *(u32*)w->cur = 0;
            w->cur += 4;
        }
    }
    static void Close(PacketWriter* w, u32* tag)
    {
        *tag |= ((w->cur - (u8*)tag) >> 4) - 1;
    }
    static void Refs(PacketWriter* w, s32 qwc, s32 addr)
    {
        *(u64*)w->cur = (s64)(qwc | 0x40000000) | ((s64)addr << 32);
        w->cur += 16;
    }
    static void Call(PacketWriter* w, s32 addr)
    {
        *(u64*)w->cur = ((s64)addr << 32) | 0x50000000;
        w->cur += 16;
    }
    static void Mscal(PacketWriter* w, u8* addr)
    {
        Word(w, ((u32)addr >> 3) | 0x14000000);
    }
    static void Mscalf(PacketWriter* w, u8* addr)
    {
        Word(w, ((u32)addr >> 3) | 0x15000000);
    }
    // A V4-32 unpack of num quadwords to addr (flags 0xC000): the command word is formed at its
    // store from the literal, so loop.c leaves the constant in the strip loop as retail does
    // (passed in as a parameter it lives from the inline's entry and is hoisted).
    static void UnpackV4(PacketWriter* w, void* src, s32 num, u32 addr)
    {
        *(u32*)w->cur = (num << 16) | addr | 0x6C00C000;
        w->cur += 4;
        Copy(w, src, num << 4);
    }
    // An unpack of size bytes with its command word and address: the source first, so its
    // address is expanded before the command (the bone loops' preheaders, in retail's order).
    static void UnpackAt(PacketWriter* w, void* src, s32 size, u32 cmd, u32 addr)
    {
        Word(w, cmd | addr);
        Copy(w, src, size);
    }
};
static inline u8 Alpha_166690(u8 a)
{
    if (a <= 0x40) {
        return a;
    }
    if ((s8)a >= 0) {
        return 0x40;
    }
    return 0x80;
}
static inline u64 Rgbaq_166690(u8 a, u8 r, u8 g, u8 b)
{
    return (u64)r | ((u64)g << 8) | ((u64)b << 16) | ((u64)a << 24) | (1ULL << 32);
}
void DrawModelPart(Frame_166690* self)
{
    Batch_166690 b;
    void* lights[128];
    void* nodes[16];
    Qw_166690 q;
    s32 n300;
    s32 n304;
    s32 n308;
    Part_166690* part = self->part;
    Owner_166690* owner = self->owner;
    CacheSet_166690* cache = self->cache;
    Skin_166690* skin = self->skin;
    s32 useCache;
    s32 count;
    s32 i;
    s32 t;
    u32* tag;
    Mesh_166690* e;
    Cache_166690* c;
    f32 r;

    b.m = self->m;
    InvertRigidTransform(&self->m.m[3], &self->m, &b.m40);
    b.f80 = part->f40;
    n300 = 0;
    n304 = 0;
    if (part->f18 != 0) {
        if (part->light != 0) {
            n304 = 1;
            n300 = 1;
            lights[0] = part->light->f27C;
            b.fA0 = self->f60;
            b.mode = 4;
            b.f9C = 2;
        } else if (part->f28 != 0) {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 1, 0x80, &n300, &n304, (s32*)lights);
            b.fA0 = self->f60;
            b.mode = 4;
        } else if (cache == 0) {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 3, 0x80, &n300, &n304, (s32*)lights);
            b.mode = 2;
        } else if (cache->f8 >= g_lightingChangeFrame) {
            if (g_lightCount != 0) {
                b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 2, 0x80, 0, &n304, (s32*)lights);
            }
            if (n304 != 0) {
                b.mode = 1;
                if (b.f9C < cache->fC) {
                    b.f9C = cache->fC;
                }
            } else {
                b.mode = 0;
                b.f9C = cache->fC;
            }
        } else {
            b.f9C = CollectLightsForSphere(g_currentWorld, &self->f60, part->f10, 7, 0x80, &n300, &n304, (s32*)lights);
            if (n300 == 0 && n304 > 0) {
                b.mode = 2;
            } else {
                b.mode = 3;
                cache->f8 = g_frameCount;
            }
            cache->fC = b.f9C;
        }
    } else {
        b.mode = -1;
        b.f9C = 2;
    }

    useCache = cache != 0 && (owner->cls->flags & 2) && owner->f410 != 0;
    n308 = 0;
    if (!useCache && (part->flags & 3)) {
        CollectRangeRecordsInReach(g_currentWorld, &self->f60, 0x10, &n308, nodes, part->f10);
    }
    b.f90 = self->f50;
    b.f98 = 1;
    if (part->flags & 4) {
        b.w.fAC = 1.0f;
    } else {
        b.w.fAC = ((World_166690*)g_currentWorld)->f234C;
    }
    count = 0;

    if (cache != 0 && cache->f18 != 0 && (b.mode == -1 || b.mode == 0)
        && (useCache || n308 == 0) && !(skin->flags & 3)) {
        if (useCache) {
            for (i = 0; i < part->nmeshes; i++) {
                Cache_166690* t = &cache->items[i];
                if (t->count != 0 && t->f18 == g_gameClock[1]) {
                    goto slow;
                }
            }
        }
        {
            s32 half = D_00262474 != 0x28;
            D_00262474 = 0x23C - D_00262474;
            tag = Vif_166690::Open(&g_vifPacketWriter);
            Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
            Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
            Vif_166690::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
            Vif_166690::Pad(&g_vifPacketWriter);
            Vif_166690::Close(&g_vifPacketWriter, tag);
            Vif_166690::Call(&g_vifPacketWriter, cache->refs[half]);
            if ((part->nmeshes + part->nstrips) & 1) {
                return;
            }
            D_00262474 = 0x23C - D_00262474;
            return;
        }
    }
slow:
    for (i = 0; i < part->nmeshes; i++) {
        s32 k;
        s32 j;
        s32 n;
        e = &part->meshes[i];
        if (cache != 0) {
            c = &cache->items[i];
        } else {
            c = 0;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = Vif_166690::Open(&g_vifPacketWriter);
        count++;
        Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            Vif_166690::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
        }
        if (e->nbones > 0) {
            u32 addr = e->slots->f4;
            for (k = 0; k < e->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, &skin->bones[e->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, e->slots->f6);
        }
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);

        switch (*e->kind) {
        case 0:
            Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            switch (b.mode) {
            case 0:
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Refs(&g_vifPacketWriter, c->f00, c->f04);
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                break;
            case 1:
                Vif_166690::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 2:
            case 4:
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n304; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x10000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            case 3: {
                Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                for (k = 0; k < n300; k++) {
                    u8* l = (u8*)lights[k];
                    Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                Vif_166690::Word(&g_vifPacketWriter, 0x90000000);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                {
                    s32 base = D_00262474;
                    u32* p = (u32*)g_buildFrameData++;
                    p[0] = ((base + e->slots->f0) << 4) + 0x1100C000;
                    p[1] = ((base + e->slots->f2) << 4) + 0x1100C000;
                    p[2] = ((base + e->slots->fE) << 4) + 0x1100C000;
                    p[3] = (u32)c;
                }
                if (k < n304) {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f3C, e->f48);
                    for (k = 0; k < n304; k++) {
                        u8* l = (u8*)lights[k];
                        Vif_166690::Refs(&g_vifPacketWriter, *(s32*)(l + 0x418), (s32)(l + 0x420));
                    }
                    Vif_166690::Cnt1(&g_vifPacketWriter);
                    Vif_166690::Mscal(&g_vifPacketWriter, D_00001210);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                    Vif_166690::Word(&g_vifPacketWriter, 0);
                }
                if (part->f54) {
                    Vif_166690::Call(&g_vifPacketWriter, e->f4C);
                } else {
                    Vif_166690::Refs(&g_vifPacketWriter, e->f40, e->f4C);
                }
                Vif_166690::Cnt1(&g_vifPacketWriter);
                Vif_166690::Mscalf(&g_vifPacketWriter, D_00000010);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                Vif_166690::Word(&g_vifPacketWriter, 0);
                break;
            }
            }
            break;
        case 1:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            break;
        case 4:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            continue;
        case 5:
            if (part->f54) {
                Vif_166690::Call(&g_vifPacketWriter, e->f44);
            } else {
                Vif_166690::Refs(&g_vifPacketWriter, e->f38, e->f44);
            }
            continue;
        default:
            continue;
        }

        if (useCache) {
            if (c->f18 == g_gameTime) {
                n308 = c->count;
            } else {
                n308 = 0;
            }
        }
        if (n308 != 0) {
            TransformByMatrixWithW(&b, 1.0f, e, &q);
            r = e->f10 * part->f50;
        }
        for (j = 0; j < n308; j++) {
            void* node;
            if (useCache) {
                node = c->nodes[j];
            } else {
                node = nodes[j];
                if (RangeRecordMatchesKinds(node, part->flags) == 0) {
                    continue;
                }
            }
            if (RangeRecordReachesSphere(node, &q, r) != 0) {
                QueueRangeRecordPacket(node);
            }
        }
    }

    if (skin != 0 && (skin->flags & 1)) {
        return;
    }
    if (self->f54 <= 0.0f) {
        return;
    }
    for (t = 0; t < part->nstrips; t++) {
        Strip_166690* s = &part->strips[t];
        s32 n;
        if (skin != 0 && (skin->flags & 2)) {
            u8 a = Alpha_166690((s32)(skin->a * self->f54));
            q.hi = 1;
            q.lo = Rgbaq_166690(a, skin->r, skin->g, skin->b);
        } else {
            q.lo = Rgbaq_166690(Alpha_166690((s32)(D_002623E0.a * self->f54)), D_002623E0.r, D_002623E0.g, D_002623E0.b);
            q.hi = 1;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = Vif_166690::Open(&g_vifPacketWriter);
        count++;
        Vif_166690::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        Vif_166690::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            Vif_166690::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
        }
        if (s->nbones > 0) {
            u32 addr = s->slots->f8;
            s32 k;
            for (k = 0; k < s->nbones; k++) {
                Vif_166690::UnpackAt(&g_vifPacketWriter, &skin->bones[s->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            Vif_166690::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, s->slots->fA);
        }
        Vif_166690::UnpackV4(&g_vifPacketWriter, &q, 1, 0x1A);
        Vif_166690::Pad(&g_vifPacketWriter);
        Vif_166690::Close(&g_vifPacketWriter, tag);
        Vif_166690::Refs(&g_vifPacketWriter, s->f18, s->f1C);
    }
}

