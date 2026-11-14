// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x15F678 to 0x162890 (its .rodata from 0x24A2D0, its .data from 0x2623C0): the
// level names, the game progress pointers and the code around them, the GIF packet writer with
// its GCC vtable D_0024A6F8, and the vertex batch. Its .rodata ends with that vtable at 0x24A710:
// GCC 2.95 writes a file's vtables after all of its functions' literals and jump tables, so the
// FLT_MAX after it starts the next file (placed_object_model.cpp, which says why its start in
// the code is a choice). One file between two edges otherwise; it could be several. Its name is
// ours, after its largest family, the game progress (the level entries, the completion and the
// saved counts); the object groups, the GIF packet writer and the vertex batch share it.
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
#include "object_finder.h"
struct NodeAttachment;
struct NodeOwner;
struct Oscillator;


// Types other files define, named by the parameters of their functions declared here.
struct AnimationPlayer;
struct T217D_6D0;


void RegroupQueuedObjects(World* self);
void UpdateGroupsNearCamera(World* self);


void DissolveObjectLinkList(World* self, PlacedObject* owner);

struct VisitClass { u8 pad0[8]; s32 flags; u8 pad1[0x54]; void (*visit)(void* self, void* arg); };
struct VisitNode { VisitClass* cls; u8 pad0[0x18]; VisitNode* next; u8 pad1[0x14]; VisitNode* child; };



void SpliceListToEnd(List01* dst, List01* src);
void TransformByMatrixWithW(const Quad16* m, const Vec02* v, f32 w, Vec02* out);
void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);
void FreeTouchNodes(World* owner, Touch03* node);


s32 IsObjectAttached(BaseObject* self);
void MergeObjectLinkLists(World* ctx, PlacedObject* self, PlacedObject* other);


void MergeObjectGroupMembers(World* self, FoundList* group);

struct CountedArray
{
    s32 count;
};

void RemoveValueFromArray(CountedArray* list, void** arr, void* value);

void* MoveMemory(void* dst, void* src, s32 bytes);


void MergeObjectGroupMembers(World* self, FoundList* group);

extern u8 D_00248D30[];

struct PlayingSound;
void StopSoundRecord(PlayingSound* self, s32 n);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

void StartObject(BaseObject* self);
void* AllocateFrontMemory(s32 size);
void RegisterObjectGroup(World* self, FoundList* group);


struct LinkListWalk {
    List01* list;
    u8* link;
    s32 offset;
    LinkListWalk* prev;
};


void RemoveFromList(List01* list, void* item);
void QueueObjectForRegroup(World* owner, PlacedObject* obj);

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



struct RefCounted
{
    u8 pad[4];
    s32 refs;
};




struct EntryFlags { u8 pad0[0x28]; s32 flags; };


s32 ComputeCompletionMask(void);

extern s32 g_previousLevelIndex;
extern u8 g_flagTable[];

void ResetReserveCounts(void);
struct FlagTable;
void RestoreFlagTableSnapshot(FlagTable* p);
void ResetFlagTable(FlagTable* r);
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

extern "C" void* FillMemory(void* p, s32 value, s32 size);

struct Counter
{
    u8 pad[4];
    s32 count;
};


extern World* g_currentWorld;

void FreeObjectMemory(void* self);

void FlushVertexBatch(VertexBatch* batch);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void InvertRigidTransform(void* a, void* b, Quad16* out);

struct ColoredVertexBatch {
    u8 pad0[0xF8];
    u8* mode;
};

void FlushVertexBatch(VertexBatch* batch);
void SetVertexColor(VertexBatch* batch, void* src);



extern u8 g_scatterController[];
extern U32P D_00269984;
extern s32 g_buttonCodeFlags;
extern s32 g_previousLevelIndex;

void ResetGameProgress(void* self);
void ClearTwoWords(void* self);
void ClearScatterController(void* self);
void ResetReserveCounts(void);






struct ClearedRecord { u8 pad0[4]; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; };

void BeginGifTag(void* self, s32 a, s32 b, u64 c);



void ResetGameSessionAndFade();

typedef void* (*MemoryFillFn)(void*,s32,s32);



struct KeyedPointSet { u8 pad0[4]; s32 count; u8* base; };
struct KeyedEdge { s16 k0; s16 k1; u8 pad[4]; KeyedEdge* next; };
struct EdgeHolder { u8 pad0[0x14]; KeyedEdge* head; };
struct ContactHit { EdgeHolder* holder; u8 pad[8]; };

void PushBackMemoryMark(void);
u8* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);
struct PlaneTreeNode;
struct PlaneTreeOutput;
s32 QueryPlaneTreePoint(PlaneTreeNode* node, Vec02* p, f32 eps, PlaneTreeOutput* out);

extern u8 g_flushBatchProgram[];
extern u8 D_000018F8[];

void WriteVifMscal(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void WriteVifMscal(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void WriteVifMscal(void* obj, void* data);

extern u8 g_flushBatchProgram[];
extern u8 D_000018F8[];

void WriteVifMscal(void* obj, void* text);

void ApplyPadPatternSetting(GameProgress* ctx);

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
extern SessionKey g_sessionFadeKey;
extern s32 g_resumeSoundSetupDone;

void ClearTwoWords(void* p);
void StartObjectFade(IdentityKey* obj, s32 value, s32 count);
void SilenceVolumeChannel3(s32 flag);
void ApplySoundOptionFlag(s32 flag);
struct ElementStack;
void StopAnimationPlayer(AnimationPlayer* self);
void SetElementStackState(ElementStack* self, s32 state);

extern u8 g_flushBatchProgram[];
extern u8 D_000018F8[];

void WriteVifMscal(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void WriteVifMscal(void* s, s32 n);

void ResetFlagTable(FlagTable* r);

extern u8 g_flagTable[];


extern u8 g_scatterController[];
extern u8 g_flagTable[];
extern u8 g_pauseMenuElement[];

void PopActiveSequenceElement(World* world);
void StopLockedStreamVoice(void);
struct ScatterController;
void StartScreenFade(ScreenFade* dst, FadeRequest* args, s32 count);
void StartScreenFadeFromFlagTable(FlagTable* r);
void SetPauseMenuLayerPage(T217D_6D0* self, s32 idx, s32 value);
void RaiseScatterLevels(ScatterController* self, f32 amount);




extern u8 g_objectFadeIn[];

void StartObjectFade(IdentityKey* obj, s32 value, s32 count);
void QueueMovieWithSuccessor(s32 slot, u32 n);


void ResetGameSession(void);
void StartObjectFade(IdentityKey* obj, s32 value, s32 count);

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
// (game_progress.h), which this file's functions read and render_frame.cpp's do not.
GameProgress* g_saveData = &g_saveDataBlock;
G27C230* g_currentLevelRecord = D_0027C230;
G27C230* g_currentEntry = D_0027C230;
s32 g_previousLevelIndex = -1;
char g_missingEntryName[8] = "<none>";
u8 D_002623D8[4] = { 0 };
s32 g_timerRateExponent = 0;
extern u8 D_00001298[];
extern u8 D_00001368[];
extern u8 D_00000ED8[];

void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count);
void BeginGifTag(PacketWriter* f, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* f, s32 a, u64 b);
void CloseGifTag(PacketWriter* f, s32 n);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
void RewindPacketBuffer(PacketWriter* f);
void AddGifXyzfEntry(PacketWriter* f, s32 a1, s32 a2, s32 a3, s32 a4);
void WriteVifStrow(PacketWriter* s, u32* src);
void WriteVifStmask(PacketWriter* s, s32 value);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void WriteMorphTargetMscal(s32 mode, void* obj);

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

struct FlushedVertexBatch { u8 pad0[0xF8]; u8* mode; u8 pad1[0x28]; s32 vertexCount; };

extern PacketWriter g_vifPacketWriter;
extern u8 g_flushBatchProgram[];

void FlipVifBaseOffset(void);
s32 WriteVifUnpackHeader(PacketWriter* s, s32 a, s32 b, s32 c);
void ResetVertexBatch(VertexBatch* batch);
void BuildUnlitVertexPacket(VertexBatch* batch);
void BuildLitVertexPacket(VertexBatch* batch);

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

void CopyMemory(void* dst, void* src, u32 size);
void FlushVertexBatch(VertexBatch* batch);
void SetVertexBatchMode(VertexBatch* batch, u8* value);

struct DrawMesh;
// A point and a fourth word, as the vertex packets write them.
struct VifPoint { Vec3 v; f32 w; };
struct UnlitVertex { Vec3 v; u8 pad[0xC]; u8 rgba[4]; f32 texU; f32 texV; s32 flag; };
struct UnlitVertexBatch {
    u8 pad[0x80];
    f32 base;
    u8 pad2[0xF8 - 0x84];
    DrawMesh* mesh;
    u8 pad3[0x124 - 0xFC];
    s32 vertexCount;
    UnlitVertex e[1];
};
struct UnlitUnpackHeader { u16 arrayOffset; u16 frameDataOffset; u8 pad[4]; u16 frameOffsets[4]; u16 arrayCount; u8 pad3[6]; };
struct CopiedGifTags { u32 w[8]; };

extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern u8 g_unlitBatchProgram[];
extern u8 g_unlitBatchFinishProgram[];
void CopyMemory(void* dst, void* src, u32 size);

// A run of bytes, for the fill and copy calls.
struct ByteSpan { u8 b[1]; };
struct LitUnpackHeader { u16 arrayOffset; u16 f2; u8 pad4[4]; u16 frameOffsets[3]; u16 fE; u16 arrayCount; u8 pad12[6]; };
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

extern u8 g_litBatchProgram[];
extern u8 g_litBatchSecondProgram[];
extern u8 g_litBatchThirdProgram[];
extern u8 g_litBatchFinishProgram[];

void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifMscalf(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void CloseDmaTag(PacketWriter* s);
void AddDmaRefTag(PacketWriter* s, s32 n, void* data);
void BeginDmaTag(PacketWriter* s);
void CopyMemory(void* dst, void* src, u32 size);

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

extern u8 g_unlitBatchFinishProgram[];
extern u8 g_unlitBatchProgram[];
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
void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void WriteVifStcycl(PacketWriter* b, u32 x, u32 y);
void WriteVifStrow(PacketWriter* s, u32* src);
void WriteVifStmask(PacketWriter* s, s32 value);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifMscalf(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
void WriteVifUnpack(PacketWriter* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* AllocateZeroedFrontMemory(s32 bytes);
void WriteStripMeshMscal(s32 mode, void* obj);
void QueueNodeLink(s32 a, s32 b, AnimCursor* node);
void QueueMeshStrip(StripMesh* mesh, FrameSource* strip, s32 a, s32 b, s32 n, AnimCursor* node);

void WriteVifBaseOffset(PacketWriter* s, u32 a, u32 b);

void ApplyLinkConstraint(PlacedObject* self);

typedef void (*AttachmentHandlerFn)(void* self);
struct AttachmentHandler { AttachmentHandlerFn* vtbl; };
struct AttachmentEntry { u8 pad0[0x38]; AttachmentHandler* f38; u8 pad1[0x70 - 0x3C]; };
struct AttachmentNode { u8 pad0[4]; void* f4; s32 f8; u8 pad1[0x80 - 0xC]; AttachmentNode* next80; };
struct AttachmentBlock { u8 pad0[0xC]; s32 count0C; AttachmentEntry* f10; u8* f14; u8 pad1[0x4C - 0x18]; AttachmentNode* f4C; };

void BuildAttachmentDmaChain(void* self, void* entry, void* sub, void* ctx);
void AttachNodeToOwner(NodeOwner* self, void* unused, NodeAttachment* ctx);

// Four quadwords: a matrix as the attachment code copies it.
struct QuadMatrix { Quad16 q[4]; };
struct TargetObject { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct AttachmentTarget { TargetObject* p0; u8 pad0[0xC]; QuadMatrix m; u8 tail[0x90 - 0x50]; };
struct AttachmentTargets { s32 count; AttachmentTarget* elems; s32* keys; };
struct TargetFrames { Quad16 a; u8 pad0[0x30]; Quad16 b; u8 pad1[0x30]; QuadMatrix m; };

void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void InvertRigidTransform(void* a, void* b, Quad16* out);

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
void EvaluateOscillator(Oscillator* self);

extern u8 g_litBatchFinishProgram[];
extern u8 D_000000F0[];

struct PartPacketContext { u8 pad0[0x28]; s32 f28; };
struct PartRange { u16 lo; u16 hi; };
struct PartPacketSource { u8 pad0[0x18]; u8* f18; PartRange* f1C; };
struct PartPackets { void* f0; void* f4; void* f8; void* fC; void* f10; void* f14; };

void* InitPacketWriter(PacketWriter* self);
void AllocateQuadwordBuffer(PacketWriter* buffer, u32 count, u32 kind);
void WriteVifStcycl(PacketWriter* b, u32 x, u32 y);
void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
void WriteVifMscal(void* s, void* n);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

struct AttachmentLink { s32 tag; AttachmentLink* p4; u8 pad8[0x48]; void* p50; void* p54; u8 pad58[0x28]; AttachmentLink* next; u8 pad84[0xC]; };
struct AttachmentPartInfo { u8 pad[0x10]; u32 flags; };
struct AttachmentPart { u8 pad[0x38]; AttachmentPartInfo* a; u8 pad3C[0x18]; void* b; };
struct AttachmentCopy { s32 n0; void* p4; u8 pad8[4]; s32 count; AttachmentPart* recs; void* p14; u8 pad18[0x28]; s32 n40; void* p44; u8 pad48[4]; AttachmentLink* head; s32 f50; };

void CopyMemory(void* dst, void* src, u32 size);
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

void InvertRigidTransform(void* a, void* b, Quad16* out);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
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

extern u8 g_litBatchProgram[];
extern u8 g_litBatchThirdProgram[];
extern u8 D_00002008[];
extern u8 D_00002088[];
extern u8 D_000023B8[];
extern u8 D_000023D8[];
extern u8 D_000023F0[];
extern u8 D_000027C0[];
extern u8 D_00003A80[];
extern u8 D_00003AA0[];

void BeginDmaTag(PacketWriter* self);
void CloseDmaTag(PacketWriter* self);
void AddDmaReturnTag(PacketWriter* self);
void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void WriteVifStcycl(PacketWriter* b, u32 x, u32 y);
void WriteVifStrow(PacketWriter* b, u32* src);
void WriteVifStmask(PacketWriter* self, s32 value);
void WriteVifMscal(PacketSlot* s, void* data);
void WriteVifFlushE(PacketWriter* b);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
void WriteVifUnpack(PacketSlot* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* AllocateZeroedFrontMemory(s32 bytes);
void WriteStripMeshMscal(s32 mode, void* obj);
void QueueNodeLink(s32 a, s32 b, AnimCursor* node);
void QueueMeshStrip(StripMesh* mesh, FrameSource* strip, s32 a, s32 b, s32 n, AnimCursor* node);

void QueueObjectForRegroup(World* owner, PlacedObject* obj);
void MergeObjectLinkLists(World* ctx, PlacedObject* self, PlacedObject* other);
void DissolveObjectLinkList(World* self, PlacedObject* owner);
void MergeObjectGroupMembers(World* self, FoundList* group);
void RegisterObjectGroup(World* self, FoundList* group);
void RemoveValueFromArray(CountedArray* list, void** arr, void* value);
void UnregisterObjectGroup(World* self, FoundList* s);
void RegroupQueuedObjects(World* self);
void VisitObjectTree(VisitNode* self, void* arg);
s32 GetPlacedObjectFrozen(PlacedObject* self, s32* out);
void SetPlacedObjectFrozen(PlacedObject* self, s32 flag);
void UpdateWorldObjectLists(World* self);
void AddLookupId(IdLookupObject* obj, s32 value);
void RunResetGameSession();
KeyedEntry* FindKeyEntry(KeyedEntry* key);
void* FindEntryById(s32 key);
void* GetEntryName(s32 id);
void* LookupEntryById(s32 id);
s32 GetEntryIdByKey(KeyedEntry* key);
s32 GetEntryFlags(s32 id);
void CountCategoryFlags(s32 key, s32* a1, s32* a2, s32* a3);
s32 ComputeCompletionMask(void);
void MarkProgressStageFlag(s32 n);
void MarkLevelDone(s32 n);
void ApplyCompletionFlags(s32 mode);
void FadeOutAndQueueMovie(s32 kind);
void ResetGameProgress(GameProgress* self);
s32 ChecksumGameProgress(GameProgress* s);
void SetCurrentLevelEntry(KeyedEntry* key, s32 flags);
void AddElapsedTime(f32 dx);
void* GetLevelEntryByKey(s32 key);
s32 GetLevelEntryWord(s32 key);
void ResetGameSession(void);
void ResetReserveCounts(void);
void ResetGameSessionAndFade(void);
void ResumeAtSavedLevel(void);
s32 ComputeCompletionPercent(GameProgress* progress);
void SetSpareCount(s32 value);
s32 HasSpareCount();
void* GetIndexedTargetSlot(void* self, s32 index);
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
void CountGifEntry(PacketWriter* obj, s32 unused1, s32 unused2);
void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, u8** out);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
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
void DestroyVertexBatch(VertexBatch* self, s32 flag);
void SetVertexBatchTransform(VertexBatch* batch, void* a1, void* a2);
void ResetVertexBatch(VertexBatch* batch);
void SetVertexBatchMode(VertexBatch* batch, u8* value);
void BuildUnlitVertexPacket(VertexBatch* batch);
void BuildLitVertexPacket(VertexBatch* batch);
void FlushVertexBatch(VertexBatch* batch);
void SetVertexPosition(VertexBatch* body, Vec3* v);
void SetVertexColor(VertexBatch* batch, void* src);
void SetVertexTexCoord(VertexBatch* dst, U64P* src);
void AddVertex(VertexBatch* batch, s32 value);
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
extern const char g_entryNameSplash[8] = "Splash";
extern const char g_entryNameParisFrance[16] = "Paris, France";
extern const char g_entryNameTheHideout[16] = "The Hideout";
extern const char g_entryNameAStealthyApproach[24] = "A Stealthy Approach";
extern const char g_entryNameProwlingTheGrounds[24] = "Prowling the Grounds";
extern const char g_entryNameHighClassHeist[24] = "High Class Heist";
extern const char g_entryNameIntoTheMachine[24] = "Into the Machine";
extern const char g_entryNameACunningDisguise[24] = "A Cunning Disguise";
extern const char g_entryNameTheFireDownBelow[24] = "The Fire Down Below";
extern const char g_entryNameTreasureInTheDepths[24] = "Treasure in the Depths";
extern const char g_entryNameTheGunboatGraveyard[24] = "The Gunboat Graveyard";
extern const char g_entryNameTheEyeOfTheStorm[24] = "The Eye of the Storm";
extern const char g_entryNameARockyStart[16] = "A Rocky Start";
extern const char g_entryNameMuggshotsTurf[16] = "Muggshot's Turf";
extern const char g_entryNameBoneyardCasino[16] = "Boneyard Casino";
extern const char g_entryNameMurraysBigGamble[24] = "Murray's Big Gamble";
extern const char g_entryNameAtTheDogTrack[24] = "At the Dog Track";
extern const char g_entryNameTwoToTango[16] = "Two to Tango";
extern const char g_entryNameStraightToTheTop[24] = "Straight to the Top";
extern const char g_entryNameBackAlleyHeist[24] = "Back Alley Heist";
extern const char g_entryNameLastCall[16] = "Last Call";
extern const char g_entryNameTheDreadSwampPath[24] = "The Dread Swamp Path";
extern const char g_entryNameTheSwampsDarkCenter[24] = "The Swamp's Dark Center";
extern const char g_entryNameTheLairOfTheBeast[24] = "The Lair of the Beast";
extern const char g_entryNameAGraveUndertaking[24] = "A Grave Undertaking";
extern const char g_entryNamePiranhaLake[16] = "Piranha Lake";
extern const char g_entryNameDescentIntoDanger[24] = "Descent into Danger";
extern const char g_entryNameAGhastlyVoyage[24] = "A Ghastly Voyage";
extern const char g_entryNameDownHomeCooking[24] = "Down Home Cooking";
extern const char g_entryNameADeadlyDance[16] = "A Deadly Dance";
extern const char g_entryNameAPerilousAscent[24] = "A Perilous Ascent";
extern const char g_entryNameInsideTheStronghold[24] = "Inside the Stronghold";
extern const char g_entryNameFlamingTempleOfFlame[24] = "Flaming Temple of Flame";
extern const char g_entryNameTheUnseenFoe[16] = "The Unseen Foe";
extern const char g_entryNameTheKingOfTheHill[24] = "The King of the Hill";
extern const char g_entryNameRapidFireAssault[24] = "Rapid Fire Assault";
extern const char g_entryNameDuelByTheDragon[24] = "Duel by the Dragon";
extern const char g_entryNameADesperateRace[24] = "A Desperate Race";
extern const char g_entryNameFlameFu[16] = "Flame Fu!";
extern const char g_entryNameAHazardousPath[24] = "A Hazardous Path";
extern const char g_entryNameBurningRubber[16] = "Burning Rubber";
extern const char g_entryNameADaringRescue[16] = "A Daring Rescue";
extern const char g_entryNameBentleyComesThrough[24] = "Bentley Comes Through";
extern const char g_entryNameATemporaryTruce[24] = "A Temporary Truce";
extern const char g_entryNameSinkingPeril[16] = "Sinking Peril";
extern const char g_entryNameAStrangeReunion[24] = "A Strange Reunion";

void QueueObjectForRegroup(World* owner, PlacedObject* obj)
{
    u64 flags = obj->flags;
    u64 bit = (u64)0x8000 << 24;
    if (!(flags & bit))
    {
        obj->flags = flags | bit;
        s32 n = owner->regroupCount;
        owner->regroupObjects[n] = obj;
        owner->regroupCount = n + 1;
    }
}

void MergeObjectLinkLists(World* ctx, PlacedObject* self, PlacedObject* other)
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
        SpliceListToEnd((List01*)&self->list60.head, (List01*)&other->list60.head);
    }
}

void DissolveObjectLinkList(World* self, PlacedObject* owner)
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

void MergeObjectGroupMembers(World* self, FoundList* group)
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

void RegisterObjectGroup(World* self, FoundList* group)
{
    if (group->count >= 2) {
        for (s32 i = 0; i < group->count; i++) {
            PlacedObject* item = group->objects[i];
            u32 n = item->count6C;
            if (n < 4) {
                item->items70[n] = group;
                item->count6C = n + 1;
            }
        }
        MergeObjectGroupMembers(self, group);
    }
}

void RemoveValueFromArray(CountedArray* list, void** arr, void* value)
{
    s32 i = list->count;
    void** p = (void**)(i * sizeof(void*) + (uptr)arr);
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
    (void)MoveMemory(arr, arr + 1, (list->count - i) * sizeof(void*) - sizeof(void*));
    list->count--;
}

void UnregisterObjectGroup(World* self, FoundList* s)
{
    s32 i;
    PlacedObject* obj;
    if (s->count >= 2) {
        for (i = 0; i < s->count; i++) {
            obj = s->objects[i];
            RemoveValueFromArray((CountedArray*)&obj->count6C, (void**)obj->items70, s);
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
        if (self->soundRecord != 0) {
            StopSoundRecord((PlayingSound*)self->soundRecord->sound, 0);
        }
        self->desc02()->m20(self, (Vec02*)D_00248D30);
        self->desc02()->m21(self, (Vec02*)D_00248D30);
        self->flags |= (u64)1 << 38;
    } else {
        self->flags &= ~((u64)1 << 38);
        self->desc02()->m20(self, &self->vA0);
        self->desc02()->m21(self, &self->vB0);
        SoundRecord* c = self->soundRecord;
        if (c != 0) {
            StartSoundEffect(c->soundId, (PlayingSound**)&c->sound, (BaseObject*)self, 0, c->outerRange, c->innerRange, c->baseVolume, c->pitch, c->startParam, (f32*)&c->b14, 0);
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
void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);

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
            if ((m->visibilityMask & cam->f21C) == cam->f21C) {
                f32 r = m->fadeDistanceFar + m->boundRadius;
                u128 diff = Vu0::Sub(Vu0::Q(m->v140), Vu0::Q(cam->position));
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
                    AppendToList((List01*)&self->list60, m);
                    if (m->desc->flags & 2) {
                        AppendToList((List01*)&self->list6C, m);
                    }
                } else {
                    VisitObjectTree((VisitNode*)m, (void*)1);
                    RemoveFromList((List01*)&self->list60, m);
                    if (m->desc->flags & 2) {
                        RemoveFromList((List01*)&self->list6C, m);
                    }
                }
                m->flags = (m->flags & mask) | bit;
            }
            m = (PlacedObject*)m->link58.next;
        }
    }
}

void UpdateWorldObjectLists(World* self)
{
    RegroupQueuedObjects(self);
    UpdateGroupsNearCamera(self);
}

void ResolveLookupIds(IdLookupObject* self)
{
    StartObject(self);
    World* cur = self->world;
    FoundList* sub = &self->found;
    sub->items = (BaseObject**)AllocateFrontMemory(self->idCount * 4);
    for (s32 i = 0; i < self->idCount; i++) {
        BaseObject* r = FindFirstObjectByIdMode1(cur, self->ids[i], self->parent);
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

void* GetEntryName(s32 id)
{
    void* p = FindEntryById(id);
    if (p == 0)
    {
        return g_missingEntryName;
    }
    return *(void**)((u8*)p + 0x24);
}

LINKER_REMNANT(func_00160178);

void* LookupEntryById(s32 id)
{
    return FindEntryById(id);
}

s32 GetEntryIdByKey(KeyedEntry* key)
{
    s32 v;
    KeyedEntry* r = FindKeyEntry(key);
    v = -1;
    if (r != 0) v = r->id;
    return v;
}

LINKER_REMNANT(func_001601D0);

s32 GetEntryFlags(s32 id)
{
    EntryFlags* e = (EntryFlags*)FindEntryById(id);
    s32 r = 0;
    if (e != 0) {
        r = e->flags;
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
        u32* r = (u32*)GetLevelEntryByKey(*(s32*)(p + 0x20));
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
        g_saveData->movieBits |= 2;
        break;
    case 4:
        if ((ComputeCompletionMask() & 4) != 0) {
            g_saveData->f19F4 |= 0xC000;
        }
        break;
    case 8:
        if ((ComputeCompletionMask() & 8) != 0) {
            g_saveData->f19F4 |= 0xC;
            g_saveData->movieBits |= 0xC;
        }
        break;
    }
}

void FadeOutAndQueueMovie(s32 kind)
{
    s32 s0 = -1;

    if (kind != 4) { if (kind < 5) { if (kind == 2) { s0 = 0xD; } } } else { s0 = 0xE; }
    StartObjectFade((IdentityKey*)g_objectFadeIn, -1, 1);
    if (s0 != -1) {
        QueueMovieWithSuccessor(s0, 0xF);
    }
}

void ResetGameProgress(GameProgress* self)
{
    FillMemory(self, 0, 0x1A00);
    self->type = 0x12;
    self->levelIndex = 0;
    self->f19F0 = 0;
    self->size = 0x1A00;
    self->entryIndex = 3;
    self->reserveCount = 5;
    self->lastHintMode = -1;
    ApplyPadPatternSetting(self);
}

s32 ChecksumGameProgress(GameProgress* s)
{
    u8* p = (u8*)&s->totalTime;
    s32 sum = 0;
    for (s32 i = 0; i < (u8*)(s + 1) - (u8*)&s->totalTime; i++) {
        sum += *p++;
    }
    return sum;
}

void SetCurrentLevelEntry(KeyedEntry* key, s32 flags)
{
    s32 r = GetEntryIdByKey(key);
    s32 hi = (r != -1) ? (r >> 8) : 0;
    s32 lo = (r != -1) ? (r & 0xFF) : 0;
    G27C230* base = &g_saveData->levels[hi];
    GameProgress* g = g_saveData;
    s32 gate = g->reserveCount;
    g_currentLevelRecord = base;
    g_currentEntry = (G27C230*)((u8*)base + lo * 0x78);
    if (gate < 0 || (flags & 2) != 0) {
        ResetReserveCounts();
    } else if ((flags & 1) != 0) {
        RestoreFlagTableSnapshot((FlagTable*)g_flagTable);
    } else if ((flags & 4) != 0) {
        ResetGameSession();
    } else {
        ResetFlagTable((FlagTable*)g_flagTable);
    }
    g = g_saveData;
    g_previousLevelIndex = g->levelIndex;
    g->levelIndex = hi;
    g->entryIndex = lo;
    g_currentLevelRecord->f448 |= 1;
    g_currentEntry->flags |= 1;
}

void AddElapsedTime(f32 dx)
{
    g_saveData->totalTime += dx;
    g_currentLevelRecord->levelElapsedTime += dx;
    g_currentEntry->elapsedTime += dx;
}

void* GetLevelEntryByKey(s32 key)
{
    return key == -1 ? 0 : (u8*)&g_saveData->levels[key >> 8] + (key & 0xFF) * 0x78;
}

s32 GetLevelEntryWord(s32 key)
{
    s32* p = (s32*)GetLevelEntryByKey(key);
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
    g->reserveCount = 5;
    g->spareCount = 0;
    ResetFlagTable((FlagTable*)g_flagTable);
}

void ResetGameSessionAndFade(void)
{
    ResetGameSession();
    StartObjectFade(&g_sessionFadeKey, -1, 0);
}

void ResumeAtSavedLevel(void)
{
    SessionKey* k = (SessionKey*)LookupEntryById((g_saveData->levelIndex << 8) | g_saveData->entryIndex);
    if (k == 0) {
        k = &g_sessionFadeKey;
    }
    ClearTwoWords(D_002623D8);
    if (g_elementStack.f30 != 1 || g_saveData->totalTime != 0.0f || !k->Same((SessionKey*)&D_00275B04)) {
        StartObjectFade(k, -1, 1);
    } else if (g_elementStack.f30 == 1) {
        if (g_resumeSoundSetupDone == 0) {
            SilenceVolumeChannel3(g_saveData->optionFlags & 0x80);
            ApplySoundOptionFlag(g_saveData->optionFlags & 0x40);
            Animation* r = (Animation*)FindFirstObjectById(g_currentWorld, 0x105, 0x494, 0);
            if (r != 0) {
                PlayerListWalk frame((AnimationPlayerList*)r->props6C);
                void* head = *(void**)r->props6C;
                frame.cursor = (u8*)head + frame.next_off;
                void* node = head;
                if (node != 0) {
                    do {
                        StopAnimationPlayer((AnimationPlayer*)node);
                        node = frame.Next();
                    } while (node != 0);
                }
            }
            g_elementStack.f30 = -1;
            SetElementStackState((ElementStack*)&g_elementStack, 3);
        }
    }
}

s32 ComputeCompletionPercent(GameProgress* progress)
{
    u8* p = (u8*)progress;
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
    g_saveData->spareCount = value;
}

s32 HasSpareCount()
{
    s32 result=0;
    if (g_saveData->spareCount>0 || (g_buttonCodeFlags&2)) result=1;
    return result;
}

LINKER_REMNANT(func_00160C90);

void* GetIndexedTargetSlot(void* self,s32 index)
{
    if ((u32)(index-0x33B)>=12) return 0;
    else return (u8*)self+(index*4-0xCD8);
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
    return g_saveData->f19F0 & g_currentWorld->flagBits;
}

void GetCurrentLevelBit(u32* out)
{
    s32 m;
    switch (g_saveData->levelIndex) {
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
    s32 t = o->reserveCount - 1;
    o->reserveCount = t;
    PopActiveSequenceElement((World*)x);
    StopLockedStreamVoice();
    GameProgress* p = g_saveData;
    s32 m = p->entryIndex;
    if (m == 1) {
        FadeRequest args;
        args.kind = m;
        args.text = (u8*)&D_00275B04;
        u8* base = args.text - 0x14;
        args.f08 = *(s32*)(base + 0x8);
        args.f0C = *(s32*)(base + 0xC);
        args.flags = 0x10;
        StartScreenFade(&g_screenFade, &args, 1);
    } else if (p->reserveCount >= 0) {
        StartScreenFadeFromFlagTable((FlagTable*)g_flagTable);
    } else {
        SetPauseMenuLayerPage((T217D_6D0*)g_pauseMenuElement, 0, 1);
    }
    RaiseScatterLevels((ScatterController*)g_scatterController, 1.0f);
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
            TransformByMatrixWithW((const Quad16*)matrix, v, 1.0f, v);
        }
        for (s32 i = 0; i < dst->faceCount; i++) {
            u8* face = (u8*)dst->faces + (i << 5);
            TransformByMatrixWithW((const Quad16*)matrix, (const Vec02*)face, 0.0f, (Vec02*)face);
            Vec02* vert = (Vec02*)((*(u16*)(face + 0x1E) << 4) + (uptr)dst->verts);
            *(u32*)(face + 0x10) = Vu0::ToBits(Vu0::Dot(Vu0::Q(*(Vec02*)face), Vu0::Q(*vert)));
            Vec02* p = &((Vec02*)dst->points)[i];
            TransformByMatrixWithW((const Quad16*)matrix, p, 1.0f, p);
        }
    }
}

s32 CollectEntriesForKey(KeyedPointSet* dst, KeyedPointSet* src, s32 key, s32 maxOut, KeyedEdge** out)
{
    sptr buf[4];

    PushBackMemoryMark();
    u8* k = AllocateBackMemory(src->count * 12);
    buf[0] = (sptr)k;
    if (QueryPlaneTreePoint((PlaneTreeNode*)src->base, (Vec02*)(dst->base + key * 16), 1.0f, (PlaneTreeOutput*)buf) != 2) {
        PopBackMemoryMark();
        return 0;
    }
    s32 i = 0;
    s32 n = ((s32)(buf[0] - (sptr)k) * (s32)0xAAAAAAAB) >> 2;
    s32 j = 0;
    if (n > 0) {
        for (; i < n; i++) {
            ContactHit* e = (ContactHit*)(k + i * 12);
            KeyedEdge* p = e->holder->head;
            if (p == 0) {
                continue;
            }
            KeyedEdge** o = (KeyedEdge**)(j * sizeof(KeyedEdge*) + (uptr)out);
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
    self->openTag = 0;
    self->registerCount = 0;
    self->entryCount = 0;
    return self;
}

void EndGifPacket(PacketWriter* self)
{
    if (self->openTag != 0) {
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
    if (f->openTag == 0)
        return;
    u32 q = f->entryCount / f->registerCount;
    u32 a2 = f->curU;
    if (a2 & 0xF) {
        f->curU = a2 + 8;
        *(u64*)a2 = 0;
    }
    u32* p = f->openTag;
    u32 w;
    if (n) {
        w = *p;
        w |= 0x8000;
    } else {
        w = *p;
    }
    w |= q;
    *p = w;
    f->openTag = 0;
}

void CountGifEntry(PacketWriter* obj, s32 unused1, s32 unused2) { ++obj->entryCount; }

void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, u8** out)
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
        *out = w->cur;
    }
    w->cur = w->cur + nloop * nreg * 16;
}

void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3)
{
    const PacketWriterVt* d = self->vt;
    d->close((PacketWriter*)((u8*)self + d->adj1), 0);
    u8* blk = self->cur;
    s64 lo = ((s64)a2 << 60) | ((s64)1 << 46);
    s64 hdr = ((s64)a1 << 47) | lo;
    self->cur = blk + 0x10;
    *(s64*)blk = hdr;
    *(u64*)(blk + 8) = a3;
    self->block = blk;
    self->registerCount = a2;
    self->entryCount = 0;
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
    self->registerCount = a1;
    self->last = p;
    self->entryCount = 0;
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

u8* InitVertexBatch(VertexBatch* batch)
{
    u8* self = (u8*)batch;
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
    ResetVertexBatch(batch);
    return self;
}

void DestroyVertexBatch(VertexBatch* self, s32 flag)
{
    if (flag & 1) {
        FreeObjectMemory(self);
    }
}

void SetVertexBatchTransform(VertexBatch* batch, void* a1, void* a2)
{
    u8* self = (u8*)batch;
    FlushVertexBatch(batch);
    BuildMatrixFromRotationAndTranslation((const Vec02*)a1, (const Mat02*)a2, (Mat4A*)self);
    InvertRigidTransform(a1, a2, (Quad16*)(self + 0x40));
}

// The lights a batch is lit by: CollectLightsForSphere (main_loop.cpp) takes the world, the
// sphere's centre in a1 and its radius in $f12, which this function passes on untouched (the
// caller, trail_ribbon.cpp's builder, sets both), then a mask, a maximum and the three outputs.
struct LightObject;
s32 CollectLightsForSphere(World* world, const Vec02* centre, f32 radius, u32 skipMask, s32 maxLights, s32* flagged, s32* outCount,
                  LightObject** out);
struct LightedVertexBatch {
    u8 pad0[0x94];
    s32 f94;
    u8 pad98[4];
    s32 strongestLight;
    u8 padA0[0xB0 - 0xA0];
    s32 flaggedLightCount;
    s32 lightCount;
    LightObject* lights[16]; // 0xB8: the lights CollectLightsForSphere gives
    u8* mode;
};

void SelectVertexBatchLights(VertexBatch* batch, void* center, f32 radius)
{
    LightedVertexBatch* self = (LightedVertexBatch*)batch;
    if (*self->mode != 0) {
        self->lightCount = 0;
        self->f94 = -1;
        self->flaggedLightCount = 0;
    } else {
        self->strongestLight = CollectLightsForSphere(g_currentWorld, (const Vec02*)center, radius, 1, 0x10, &self->flaggedLightCount,
                                           &self->lightCount, self->lights);
        self->f94 = 4;
    }
}

void ResetVertexBatch(VertexBatch* batch)
{
    u8* self = (u8*)batch;
    *(s32*)(self+0xF8)=0;
    *(s32*)(self+0x124)=0;
    ((MemoryFillFn)FillMemory)(self+0x128,0,0x1720);
}

void SetVertexBatchMode(VertexBatch* batch, u8* value)
{
    ColoredVertexBatch* self = (ColoredVertexBatch*)batch;
    u32 local;
    FlushVertexBatch(batch);
    self->mode = value;
    local = 0xFFFFFFFF;
    SetVertexColor(batch, &local);
}

void BuildUnlitVertexPacket(VertexBatch* batch)
{
    UnlitVertexBatch* self = (UnlitVertexBatch*)batch;
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
    ReserveVifUnpack(&g_vifPacketWriter, 0xD, 3, 0xB, 0, (u8**)&hd);
    FillMemory(hd, 0, 0x18);
    hd->arrayCount = 3;
    hd->arrayOffset = base;
    base = self->vertexCount * 3 + 0x24;
    hd->frameDataOffset = base;
    WriteVifStcycl(&g_vifPacketWriter, 1, 3);
    ReserveVifUnpack(&g_vifPacketWriter, 8, self->vertexCount, hd->arrayOffset, 0, (u8**)&out1);
    ReserveVifUnpack(&g_vifPacketWriter, 0xC, self->vertexCount, hd->arrayOffset + 2, 0, (u8**)&out2);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->vertexCount; i++) {
        c = &self->e[i];
        out1[0] = c->texU;
        out1[1] = c->texV;
        out1[2] = 1.0f;
        out2->v = c->v;
        out2->w = c->flag != 0 ? self->base + 32768.0f : self->base;
        out1 += 3;
        out2++;
    }
    WriteVifMscal(&g_vifPacketWriter, g_unlitBatchProgram);
    WriteVifStcycl(&g_vifPacketWriter, 1, 3);
    ReserveVifUnpack(&g_vifPacketWriter, 0xE, self->vertexCount, hd->arrayOffset + 1, 0, &out3);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->vertexCount; i++) {
        s32 j;
        c = &self->e[i];
        for (j = 0; j < 4; j++) {
            out3[j] = (self->mesh->col[j] * c->rgba[j] + 0x100) / 0x1FE;
        }
        out3 += 4;
    }
    for (k = 0; k < self->mesh->count; k++) {
        MeshFrameData* pair = &self->mesh->ents[k];
        s32 frame;
        ReserveVifUnpack(&g_vifPacketWriter, 0xC, pair->n, base, &count, (u8**)&dst);
        frame = 0;
        if (self->mesh->sub != 0) {
            frame = self->mesh->sub->n;
        }
        CopyMemory(dst, pair->data + ((frame * pair->n) << 4), count);
        dst->w[0] |= 0x8000 | self->vertexCount;
        dst->w[4] |= 0x8000;
        hd->frameOffsets[k] = base;
        base += pair->n;
    }
    WriteVifMscalf(&g_vifPacketWriter, g_unlitBatchFinishProgram);
}

void BuildLitVertexPacket(VertexBatch* batch)
{
    LitVertexBatch* self = (LitVertexBatch*)batch;
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

    ReserveVifUnpack(&g_vifPacketWriter, 0xD, 3, 0xB, 0, (u8**)&hdr);
    FillMemory((ByteSpan*)hdr, 0, 0x18);
    hdr->arrayCount = 4;
    hdr->arrayOffset = off;
    off += self->n * 4;
    hdr->f2 = off;
    off += (((self->n + 3) & ~3) - self->n) * 4;
    hdr->fE = off;
    off += self->n;
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    ReserveVifUnpack(&g_vifPacketWriter, 0xC, self->n, hdr->arrayOffset + 3, 0, (u8**)&p4);
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
    ReserveVifUnpack(&g_vifPacketWriter, 0xC, (self->n + 3) & ~3, hdr->arrayOffset, 0, (u8**)&p8);
    ReserveVifUnpack(&g_vifPacketWriter, 0xE, self->n, hdr->arrayOffset + 1, 0, &pC);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    WriteVifMscal(&g_vifPacketWriter, g_litBatchProgram);
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
    WriteVifMscal(&g_vifPacketWriter, g_litBatchSecondProgram);
    WriteVifFlushE(&g_vifPacketWriter);
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    ReserveVifUnpack(&g_vifPacketWriter, 8, self->n, hdr->arrayOffset, 0, (u8**)&p10);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    WriteVifMscal(&g_vifPacketWriter, g_litBatchThirdProgram);
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
        ReserveVifUnpack(&g_vifPacketWriter, 0xC, e->n, off, &size, (u8**)&dst);
        MeshFrameCursor* sub = self->mesh->sub;
        s32 m = sub ? sub->n : 0;
        CopyMemory((ByteSpan*)dst, e->data + m * e->n * 16, size);
        dst[0] |= 0x8000 | self->n;
        dst[4] |= 0x8000;
        hdr->frameOffsets[k] = off;
        k++;
        off += e->n;
    }
    WriteVifMscalf(&g_vifPacketWriter, g_litBatchFinishProgram);
}

void FlushVertexBatch(VertexBatch* batch)
{
    FlushedVertexBatch* self = (FlushedVertexBatch*)batch;
    if (self->mode == 0) {
        return;
    }
    if (self->vertexCount < 3) {
        ResetVertexBatch(batch);
        return;
    }
    {
        FlipVifBaseOffset();
        PacketWriter* s = &g_vifPacketWriter;
        s32 size = WriteVifUnpackHeader(s, 12, 11, 0);
        WordCopy::Words((s32*)s->cur, (s32*)self, size >> 2);
        s->cur += size;
        WriteVifMscal(&g_vifPacketWriter, g_flushBatchProgram);
        switch (*self->mode) {
        case 1:
        case 6:
        case 7:
        case 8:
            BuildUnlitVertexPacket(batch);
            break;
        case 0:
            BuildLitVertexPacket(batch);
            break;
        }
    }
    ResetVertexBatch(batch);
}

void SetVertexPosition(VertexBatch* body, Vec3* v)
{
    body->x = v->x;
    body->y = v->y;
    body->z = v->z;
}

LINKER_REMNANT(func_001626A0);

void SetVertexColor(VertexBatch* batch, void* src)
{
    u8* dst = (u8*)batch;
    *(U32P*)(dst + 0x114) = *(U32P*)src;
}

void SetVertexTexCoord(VertexBatch* dst, U64P* src)
{
    dst->texCoord.v = src->v;
}

void AddVertex(VertexBatch* batch, s32 value)
{
    AppendVertexBatch* self = (AppendVertexBatch*)batch;
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
        FlushVertexBatch(batch);
        SetVertexBatchMode(batch, p);
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

