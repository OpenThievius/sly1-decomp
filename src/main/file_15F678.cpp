// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "id_lookup_object.h"
#include "placed_object.h"
#include "world.h"
#include "animation.h"
#include "sound_record.h"
#include "asm_func.h"
#include "list_iter.h"
#include "packet_writer.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "keyed_entry.h"
#include "identity_key.h"
#include "strip_mesh.h"
#include "vertex_batch.h"
#include "shapes.h"


void func_0015FA58(void* self);
void func_0015FD78(void* self);


void func_0015F930(void* list, void* base, void* item);
void func_0015F710(void* self, void* value);

struct VisitClass { u8 pad0[8]; s32 flags; u8 pad1[0x54]; void (*visit)(void* self, void* arg); };
struct VisitNode { VisitClass* cls; u8 pad0[0x18]; VisitNode* next; u8 pad1[0x14]; VisitNode* child; };



void func_00152730(void* dst, void* src);


s32 func_00182FC8(void* p);
void func_0015F6C0(void* ctx, void* a, void* b);


void func_0015F7D8(void* self, FoundList* group);

struct CountedArray
{
    s32 count;
};

void* func_001F5B08(void* dst, void* src, s32 bytes);


void func_0015F7D8(void* self, void* item);

extern u8 D_00248D30[];

void func_001BF788(void* self, s32 n);
void func_001BFCD8(void* a0, void* a1, void* a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, s32 a5);

void func_00182C58(BaseObject* self);
void* func_0018D500(s32 size);
s32 func_0015A480(World* world, s32 item, void* c);
void func_0015F8B0(World* world, FoundList* sub);


struct LinkListWalk {
    List01* list;
    u8* link;
    s32 offset;
    LinkListWalk* prev;
};


void func_00152600(List01* list, PlacedObject* node);
void func_0015F678(void* self, PlacedObject* node);

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

void* func_00160110();

s32* func_00160810();

struct RefCounted
{
    u8 pad[4];
    s32 refs;
};


void func_001612E8(void* self, s32 a1, s32 a2);


struct EntryFlags { u8 pad0[0x28]; s32 f28; };

EntryFlags* func_00160110(void* a0);

s32 func_001602A0(void);

extern s32 D_002623CC;
extern u8 D_00261420[];

s32 func_001601A0(s32 a0);
void func_001608E0(void);
void func_00140F48(u8* p);
void func_00140D90(u8* p);
void func_00160880(void);


void* func_0018D500(s32 size);

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

void* func_001F5C0C(void* p, s32 value, s32 size);

struct Counter
{
    u8 pad[4];
    s32 count;
};


extern World* D_00275710;

void func_0018D778(void);

void func_00162508(void* self);
void func_00188B08(void* a, void* b, void* c);
void func_00188B48(void* a, void* b, void* c);

struct ColoredVertexBatch {
    u8 pad0[0xF8];
    s32 f0F8;
};

void func_00162508(void* self);
void func_001626A8(void* self, u32* value);

KeyedEntry* func_001600A0(void);


extern u8 D_00261EF0[];
extern U32P D_00269984;
extern s32 D_00262C64;
extern s32 D_002623CC;

void func_001605E8(void* self);
void func_00160CC8(void* self);
void func_00151A68(void* self);
void func_001608E0(void);

void func_001612E8(void* self, s32 a1, s32 a2);


void func_001612E8(void* self, s32 a1, s32 a2);


void func_001612E8(void* self, s32 a1, s32 a2);

struct ClearedRecord { u8 pad0[4]; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; };

void func_001613C0(void* self, s32 a, s32 b, s32 c);



void func_00160918();

typedef void* (*MemoryFillFn)(void*,s32,s32);

void func_001612E8(void* self, s32 a1, s32 a2);

void func_001612E8(void* self, s32 a1, s32 a2);

struct KeyedPointSet { u8 pad0[4]; s32 count; u8* base; };
struct KeyedEdge { s16 k0; s16 k1; u8 pad[4]; KeyedEdge* next; };
struct EdgeHolder { u8 pad0[0x14]; KeyedEdge* head; };
struct ContactHit { EdgeHolder* holder; u8 pad[8]; };

void func_0018D608(void);
u8* func_0018D658(s32 size);
void func_0018D6F0(void);
s32 func_0013E430(u8* a0, u8* a1, s32* a2, f32 scale);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* obj, void* data);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* obj, void* text);

void func_001A7E90(void* self);

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
extern ElementStackState D_00275BC0;
extern SessionKey D_00247AB0;
extern s32 D_00275F84;

SessionKey* func_00160180(s32 key);
void func_00160CC8(void* p);
void func_001F0428(void* a, s32 b, s32 c);
void func_001C0760(s32 flag);
void func_001C0790(s32 flag);
Animation* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_0012E760(void* obj);
void func_001E96F8(void* obj, s32 mode);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* s, s32 n);

void func_00140D90(void* p);

extern u8 D_00261420[];


extern u8 D_00261EF0[];
extern u8 D_00261420[];
extern u8 D_0026FF68[];

void func_001DDAD0(void* x);
void func_001BE708(void);
void func_001EFFA0(void* dst, FadeRequest* args, s32 count);
void func_00140ED0(void* r);
void func_00194D30(void* self, s32 a, s32 b);
void func_00151E20(void* self, f32 amount);


u32* func_00160810(void* key);


extern u8 D_00247AD0[];

void func_001F0428(void* obj, s32 m, s32 n);
void func_0018E4F0(s32 slot, u32 n);


void func_00160880(void);
void func_001F0428(void* obj, s32 value, s32 count);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0024A6F8[];
s32 func_00152888(PacketWriter* a);

void func_001604B8(s32 mode);

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

// The file's .data, in retail's order.
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

void func_001EE5C8(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_00152980(PacketWriter* f, s32 size);
void func_001613C0(PacketWriter* f, s32 a, s32 b, s32 c);
void func_00161708(PacketWriter* f, s32 a, u64 b);
void func_00161278(PacketWriter* f, s32 n);
void func_001EE668(PacketWriter* s, s32 a, s32 b, void* data, s32 flags);
void func_001528E0(PacketWriter* f);
void func_001615F0(PacketWriter* f, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001EE4C0(PacketWriter* s, u32* src);
void func_001EE528(PacketWriter* s, s32 value);
void func_001EE3F0(PacketWriter* s, void* data);
void func_001EE480(PacketWriter* s);
void func_00163990(s32 mode, PacketWriter* obj);

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

extern PacketWriter D_002622A8;
extern u8 D_000018C0[];

void func_00166658(void);
s32 func_001EE560(PacketWriter* s, s32 a, s32 b, s32 c);
void func_00161B80(FlushedVertexBatch* self);
void func_00161C00(FlushedVertexBatch* self);
void func_00161F70(FlushedVertexBatch* self);

struct WordCopy {
    static void Words(s32* dst, s32* src, s32 n)
    {
        s32 rem = n & 3;
        s32 bulk = n - rem;
        s32 i;
        for (i = 0; i < rem; i++) {
            *dst++ = *src++;
        }
        for (i = 0; i < bulk; i += 4) {
            s32 a = src[0];
            s32 b = src[1];
            s32 c = src[2];
            s32 d = src[3];
            dst[0] = a;
            dst[1] = b;
            dst[2] = c;
            dst[3] = d;
            src += 4;
            dst += 4;
        }
    }
};

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

void func_0018D800(BatchVertexWords* dst, const void* src, s32 size);
void func_00162508(AppendVertexBatch* self);
void func_00161BB0(AppendVertexBatch* self, u8* value);

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

void func_001F5C0C(UnlitUnpackHeader* p, s32 v, s32 n);
extern u8 D_00001A50[];
extern u8 D_000002F8[];
void func_0018D800(CopiedGifTags* dst, u8* src, s32 n);

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

void func_001EE5C8(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
ByteSpan* func_001F5C0C(ByteSpan* p, s32 value, s32 size);
void func_001EE3F0(PacketWriter* s, void* data);
void func_001EE420(PacketWriter* s, void* data);
void func_001EE480(PacketWriter* s);
void func_00152D70(PacketWriter* s);
void func_00152B80(PacketWriter* s, s32 n, void* data);
void func_00152B38(PacketWriter* s);
void func_0018D800(ByteSpan* dst, void* src, s32 count);

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

void func_00152B38(PacketWriter* pkt);
void func_00152D70(PacketWriter* pkt);
void func_00152CA0(PacketWriter* pkt);
void func_001EE5C8(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_001EE498(PacketWriter* s, s32 a, s32 b);
void func_001EE4C0(PacketWriter* s, u32* src);
void func_001EE528(PacketWriter* s, s32 value);
void func_001EE3F0(PacketWriter* s, void* data);
void func_001EE420(PacketWriter* s, void* data);
void func_001EE480(PacketWriter* s);
void func_001EE668(PacketWriter* s, s32 a, s32 b, void* data, s32 flags);
void func_001EE718(PacketWriter* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* func_0018D5C0(s32 bytes);
void func_00163938(s32 mode, PacketWriter* pkt);
void func_00169608(s32 a, s32 b, AnimCursor* node);
void func_001694F8(StripMesh* mesh, FrameSource* strip, s32 a, s32 b, s32 n, AnimCursor* node);

void func_001EE3B8(void* obj, s32 size, s32 flags);

void func_0016C528(void*);

typedef void (*AttachmentHandlerFn)(void* self);
struct AttachmentHandler { AttachmentHandlerFn* vtbl; };
struct AttachmentEntry { u8 pad0[0x38]; AttachmentHandler* f38; u8 pad1[0x70 - 0x3C]; };
struct AttachmentNode { u8 pad0[4]; void* f4; s32 f8; u8 pad1[0x80 - 0xC]; AttachmentNode* next80; };
struct AttachmentBlock { u8 pad0[0xC]; s32 count0C; AttachmentEntry* f10; u8* f14; u8 pad1[0x4C - 0x18]; AttachmentNode* f4C; };

void func_001662A8(void* self, void* entry, void* sub, void* ctx);
void func_001F2798(void* owner, void* unused, void* ctx);

// Four quadwords: a matrix as the attachment code copies it.
struct QuadMatrix { Quad16 q[4]; };
struct TargetObject { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct AttachmentTarget { TargetObject* p0; u8 pad0[0xC]; QuadMatrix m; u8 tail[0x90 - 0x50]; };
struct AttachmentTargets { s32 count; AttachmentTarget* elems; s32* keys; };
struct TargetFrames { Quad16 a; u8 pad0[0x30]; Quad16 b; u8 pad1[0x30]; QuadMatrix m; };

void* func_0015A448(void* a, s32 b, void* c);
void func_00188B08(void* a, void* b, void* out);
void func_00188B48(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);

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


s32 func_001B4B08(void* p);
void func_001F3408(void* p);

extern u8 D_00000010[];
extern u8 D_000000F0[];

struct PartPacketContext { u8 pad0[0x28]; s32 f28; };
struct PartRange { u16 lo; u16 hi; };
struct PartPacketSource { u8 pad0[0x18]; u8* f18; PartRange* f1C; };
struct PartPackets { void* f0; void* f4; void* f8; void* fC; void* f10; void* f14; };

void* func_001EE318(void* p);
void func_00152938(void* buf, u32 count, u32 kind);
void func_001EE498(void* b, u32 x, u32 y);
void func_001EE5C8(void* s, u32 tag, s32 size, s32 a3, void* a4, void* a5);
void func_001EE3F0(void* s, void* n);
void func_001529E0(void* self, void* a, void* b);

struct AttachmentLink { s32 tag; AttachmentLink* p4; u8 pad8[0x48]; void* p50; void* p54; u8 pad58[0x28]; AttachmentLink* next; u8 pad84[0xC]; };
struct AttachmentPartInfo { u8 pad[0x10]; u32 flags; };
struct AttachmentPart { u8 pad[0x38]; AttachmentPartInfo* a; u8 pad3C[0x18]; void* b; };
struct AttachmentCopy { s32 n0; void* p4; u8 pad8[4]; s32 count; AttachmentPart* recs; void* p14; u8 pad18[0x28]; s32 n40; void* p44; u8 pad48[4]; AttachmentLink* head; s32 f50; };

void func_0018D800(AttachmentCopy* dst, void* src, s32 n);
void* func_0018D5C0(s32 n);
void* func_0018D568(s32 size, void* src);
void func_00165AE8(AttachmentCopy* o, void* a, void* b);
void func_00162810(AttachmentCopy* o);

// Index written (i << 4) * 9: a plain &items[i] gives a mult that loop.c does not strength-reduce (no s4 offset giv).
struct FramedObject;
typedef void (*FramedObjectFn)(FramedObject* self);
struct FramedObjectVt { u8 pad[0xC0]; FramedObjectFn f; };
struct FrameLinkConstraint { u8 pad0[0x60]; QuadMatrix m60; u8 pad[4]; s32 a4; u8 pad2[8]; u32 flags; };
struct FramedObject { FramedObjectVt* vt; u8 pad0[0x10C]; u8 sub110[0x30]; u8 sub140[0x40]; u8 pad180[0xA4]; FrameLinkConstraint* link; };
struct FramedAttachment { FramedObject* obj; u8 pad[0xC]; Quad16 q10[4]; QuadMatrix m50;  };
struct FramedAttachmentList { s32 count; FramedAttachment* items; };
struct ParentFrame { u8 pad[0x30]; };

void func_00188B48(void* a, void* b, void* out);
void func_00188B08(void* a, void* b, void* out);
QuadMatrix func_00188668(QuadMatrix a, void* q);

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

void func_00152B38(PacketSlot* pkt);
void func_00152D70(PacketSlot* pkt);
void func_00152CA0(PacketSlot* pkt);
void func_001EE5C8(PacketSlot* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_001EE498(PacketSlot* s, s32 a, s32 b);
void func_001EE4C0(PacketSlot* s, u32* src);
void func_001EE528(PacketSlot* s, s32 value);
void func_001EE3F0(PacketSlot* s, void* data);
void func_001EE480(PacketSlot* s);
void func_001EE668(PacketSlot* s, s32 a, s32 b, void* data, s32 flags);
void func_001EE718(PacketSlot* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* func_0018D5C0(s32 bytes);
void func_00163938(s32 mode, PacketSlot* pkt);
void func_00169608(s32 a, s32 b, AnimCursor* node);
void func_001694F8(StripMesh* mesh, FrameSource* strip, s32 a, s32 b, s32 n, AnimCursor* node);

void func_0015F678(World* owner, u8* obj);
void func_0015F6C0(void* ctx, PlacedObject* self, PlacedObject* other);
void func_0015F710(void* self, PlacedObject* owner);
void func_0015F7D8(void* self, FoundList* group);
void func_0015F8B0(void* self, FoundList* group);
void func_0015F930(CountedArray* list, s32* arr, s32 value);
void func_0015F9A0(void* self, FoundList* s);
void func_0015FA58(World* self);
void func_0015FB28(VisitNode* self, void* arg);
s32 func_0015FBA0(PlacedObject* self, s32* out);
void func_0015FBB8(PlacedObject* self, s32 flag);
void func_0015FF58(void* self);
void func_00160050(IdLookupObject* obj, s32 value);
void func_00160070();
KeyedEntry* func_001600A0(KeyedEntry* key);
void* func_00160110(s32 key);
void* func_00160148();
s32 func_00160180(void);
s32 func_001601A0(void);
s32 func_001601D8(void* a0);
void func_00160208(s32 key, s32* a1, s32* a2, s32* a3);
s32 func_001602A0(void);
void func_00160340(s32 n);
void func_001603E8(s32 n);
void func_001604B8(s32 mode);
void func_00160578(s32 kind);
void func_001605E8(GameProgress* self);
s32 func_00160650(GameProgress* s);
void func_00160690(s32 a0, s32 flags);
void func_001607D0(f32 dx);
void* func_00160810(s32 key);
s32 func_00160850();
void func_00160880(void);
void func_001608E0(void);
void func_00160918(void);
void func_00160948(void);
s32 func_00160B28(u8* p);
void func_00160C48(s32 value);
s32 func_00160C58();
void* func_00160CA0(u8* self,s32 index);
void func_00160CC8(void* p);
void func_00160CE8(Counter* c);
s32 func_00160CF0(Counter* c);
void func_00160D00(RefCounted* self);
s32 func_00160D10();
void func_00160D30(u32* out);
s32 func_00160D98(void);
void func_00160DA0(void);
void func_00160E80(ClearedRecord* self);
s32 func_00161028(KeyedPointSet* dst, KeyedPointSet* src, s32 key, s32 maxOut, KeyedEdge** out);
PacketWriter* func_001611B8(PacketWriter* self);
void func_00161200(PacketWriter* self);
void func_00161278(PacketWriter* f, s32 n);
s32 func_001612E8(PacketWriter* obj);
void func_001612F8(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, s32* out);
void func_001613C0(PacketWriter* self, s32 a1, s32 a2, s32 a3);
void func_00161458(PacketWriter* self, u32 value);
void func_001614C8(PacketWriter* self,s32 a,s32 b);
void func_00161520(PacketWriter* self,f32 a,f32 b,f32 c);
void func_00161588(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void func_001615F0(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void func_00161670(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void func_00161708(PacketWriter* self, u64 a1, u64 a2);
void func_00161768(PacketWriter* self, u32 a1, u64 a2);
void func_001617E8(PacketWriter* self, s32 tag, f32 value);
void func_00161860(PacketWriter* self, s32 a1, s32 a2);
void func_001618C0(PacketWriter* self, s32 a1, s32 a2, u32 a3, u32 a4);
void func_00161A88(void* self, s32 flag);
void func_00161AB0(u8* self, void* a1, void* a2);
void func_00161B80(u8* self);
void func_00161BB0(ColoredVertexBatch* self, s32 value);
void func_00161C00(UnlitVertexBatch* self);
void func_00161F70(LitVertexBatch* self);
void func_00162508(FlushedVertexBatch* self);
void func_00162680(VertexBatch* body, Vec3* v);
void func_001626A8(u8* dst, u8* src);
void func_001626C0(VertexBatch* dst, U64P* src);
void func_001626D8(AppendVertexBatch* self, s32 value);
void func_00162810(RefOwner* owner);
void func_00163938(s32 mode, void* obj);
void func_00163990(s32 mode, void* obj);
void func_001639E8(MeshBuildState* self, s32 mode, MorphTargetHeader* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, void* data, PacketWriter* pkt);
void func_00163ED8(MeshBuildState* self, StripMeshOwner* obj, s32 mode, StripHeader* hdr, StripMesh* mesh,
                   Vec3* vecs, s32 unused6, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, s32 unused13, f32* weights, PacketWriter* pkt,
                   s32** outs);
void func_00164868(MeshBuildState* self, StripMeshOwner* obj, s32 unused2, s32 mode, StripHeader* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, PacketSlot* pkt, s32** outs);
void func_00165588(PartPacketContext* a, PartPacketSource* b, PartPackets* c);
void func_00165728(AttachmentBlock* self, PlacedObject* ctx);
void func_00165828(AttachmentTargets* self, PlacedObject* ctx);
void func_00165920(AttachmentCopy* self, s32 arg, void* src);
void func_00165FE0(AnimatorOwner* self, PlacedObject* sub, f32 f);
void func_001660A0(PlacedObject* self);
void func_001660E8(PlacedObject* self, ParentFrame* par);
void func_00166658(void);

void func_0015F678(World* owner, u8* obj)
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

void func_0015F6C0(void* ctx, PlacedObject* self, PlacedObject* other)
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

void func_0015F710(void* self, PlacedObject* owner)
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

void func_0015F7D8(void* self, FoundList* group)
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

void func_0015F8B0(void* self, FoundList* group)
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

void func_0015F930(CountedArray* list, s32* arr, s32 value)
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

void func_0015F9A0(void* self, FoundList* s)
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

void func_0015FA58(World* self)
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

void func_0015FB28(VisitNode* self, void* arg)
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

s32 func_0015FBA0(PlacedObject* self, s32* out)
{
    s32 bit = (s32)(self->flags >> 38) & 1;
    *out = bit;
    return bit;
}

void func_0015FBB8(PlacedObject* self, s32 flag)
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

ASM_FUNC(func_0015FCD8);

ASM_FUNC(func_0015FD78);

void func_0015FF58(void* self)
{
    RegroupQueuedObjects(self);
    UpdateGroupsNearCamera(self);
}

void func_0015FF88(IdLookupObject* self)
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

void func_00160050(IdLookupObject* obj, s32 value) { obj->ids[obj->idCount++] = value; }

void func_00160070() { ResetGameSessionAndFade(); }

LINKER_REMNANT(func_00160090);

KeyedEntry* func_001600A0(KeyedEntry* key)
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

void* func_00160110(s32 key)
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

void* func_00160148()
{
    void* p = FindEntryById();
    if (p == 0)
    {
        return D_002623D0;
    }
    return *(void**)((u8*)p + 0x24);
}

LINKER_REMNANT(func_00160178);

s32 func_00160180(void)
{
    return (s32)FindEntryById();
}

s32 func_001601A0(void)
{
    s32 v;
    KeyedEntry* r = FindKeyEntry();
    v = -1;
    if (r != 0) v = r->id;
    return v;
}

LINKER_REMNANT(func_001601D0);

s32 func_001601D8(void* a0)
{
    EntryFlags* e = FindEntryById(a0);
    s32 r = 0;
    if (e != 0) {
        r = e->f28;
    }
    return r;
}

void func_00160208(s32 key, s32* a1, s32* a2, s32* a3)
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

s32 func_001602A0(void) {
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

void func_00160340(s32 n)
{
    switch (n) {
    case 1: g_saveData->f19F4 |= 0x10; break;
    case 2: g_saveData->f19F4 |= 0x40; break;
    case 3: g_saveData->f19F4 |= 0x100; break;
    case 4: g_saveData->f19F4 |= 0x400; break;
    case 5: g_saveData->f19F4 |= 0x1000; break;
    }
}

void func_001603E8(s32 n)
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

void func_001604B8(s32 mode)
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

void func_00160578(s32 kind)
{
    s32 s0 = -1;

    if (kind != 4) { if (kind < 5) { if (kind == 2) { s0 = 0xD; } } } else { s0 = 0xE; }
    StartObjectFade((void*)D_00247AD0, -1, 1);
    if (s0 != -1) {
        QueueMovieWithSuccessor(s0, 0xF);
    }
}

void func_001605E8(GameProgress* self)
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

s32 func_00160650(GameProgress* s)
{
    u8* p = (u8*)&s->fC;
    s32 sum = 0;
    for (s32 i = 0; i < (u8*)(s + 1) - (u8*)&s->fC; i++) {
        sum += *p++;
    }
    return sum;
}

void func_00160690(s32 a0, s32 flags)
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

void func_001607D0(f32 dx)
{
    g_saveData->fC += dx;
    g_currentLevelRecord->f444 += dx;
    g_currentEntry->f04 += dx;
}

void* func_00160810(s32 key)
{
    return key == -1 ? 0 : (u8*)&g_saveData->levels[key >> 8] + (key & 0xFF) * 0x78;
}

s32 func_00160850()
{
    s32* p = GetLevelEntryByKey();
    s32 value = 0;
    if (p)
    {
        value = *p;
    }
    return value;
}

void func_00160880(void)
{
    ResetGameProgress(g_saveData);
    D_00269984.v = 0;
    ClearTwoWords(D_002623D8);
    ClearScatterController(g_scatterController);
    g_buttonCodeFlags = 0;
    g_previousLevelIndex = -1;
    ResetReserveCounts();
}

void func_001608E0(void)
{
    GameProgress* g = g_saveData;
    g->f19E0 = 5;
    g->f19E4 = 0;
    ResetFlagTable((void*)g_flagTable);
}

void func_00160918(void)
{
    ResetGameSession();
    StartObjectFade((void*)&D_00247AB0, -1, 0);
}

void func_00160948(void)
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
            func_001C0790(g_saveData->f19EC & 0x40);
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

s32 func_00160B28(u8* p)
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

void func_00160C48(s32 value)
{
    g_saveData->f19E4 = value;
}

s32 func_00160C58()
{
    s32 result=0;
    if (g_saveData->f19E4>0 || (g_buttonCodeFlags&2)) result=1;
    return result;
}

LINKER_REMNANT(func_00160C90);

void* func_00160CA0(u8* self,s32 index)
{
    if ((u32)(index-0x33B)>=12) return 0;
    else return self+(index*4-0xCD8);
}

void func_00160CC8(void* p)
{
    FillMemory(p, 0, 8);
}

void func_00160CE8(Counter* c)
{
    c->count = 0;
}

s32 func_00160CF0(Counter* c)
{
    return ++c->count;
}

void func_00160D00(RefCounted* self)
{
    self->refs--;
}

s32 func_00160D10()
{
    return g_saveData->f19F0 & g_currentWorld->f235C;
}

void func_00160D30(u32* out)
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

s32 func_00160D98(void)
{
    return 2;
}

void func_00160DA0(void)
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

void func_00160E80(ClearedRecord* self)
{
    self->f4 = 0;
    self->f8 = 0;
    self->fC = 0;
    self->f10 = 0;
    self->f14 = 0;
    self->f18 = 0;
}

ASM_FUNC(func_00160EA0);

s32 func_00161028(KeyedPointSet* dst, KeyedPointSet* src, s32 key, s32 maxOut, KeyedEdge** out)
{
    s32 buf[4];

    PushBackMemoryMark();
    u8* k = AllocateBackMemory(src->count * 12);
    buf[0] = (s32)k;
    if (func_0013E430(src->base, dst->base + key * 16, buf, 1.0f) != 2) {
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

extern const Fn_Table D_0024A6F8[6] = { 0, 0, 0, (Fn_Table)(void (*)(PacketWriter* f, s32 n))func_00161278, 0, 0 };

PacketWriter* func_001611B8(PacketWriter* self)
{
    (void)InitPacketBuffer(self);
    self->f14 = 1;
    self->vt = (const PacketWriterVt*)g_gifPacketMethods;
    self->f1C = 0;
    self->f20 = 0;
    self->f24 = 0;
    return self;
}

void func_00161200(PacketWriter* self)
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

void func_00161278(PacketWriter* f, s32 n)
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

s32 func_001612E8(PacketWriter* obj) { return ++obj->f24; }

void func_001612F8(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, s32* out)
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

void func_001613C0(PacketWriter* self, s32 a1, s32 a2, s32 a3)
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

void func_00161458(PacketWriter* self, u32 value)
{
    CountGifEntry(self, 1, 1);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = value & 0xFF;
    p[1] = (value & 0xFF00) >> 8;
    p[2] = (value >> 16) & 0xFF;
    p[3] = value >> 24;
}

void func_001614C8(PacketWriter* self,s32 a,s32 b)
{
    CountGifEntry(self,1,3);
    s32* p=(s32*)self->cur;
    self->cur+=16;
    p[0]=a;
    p[1]=b;
}

void func_00161520(PacketWriter* self,f32 a,f32 b,f32 c)
{
    CountGifEntry(self,1,2);
    f32* p=(f32*)self->cur;
    self->cur+=16;
    p[0]=a;
    p[1]=b;
    p[2]=c;
}

void func_00161588(PacketWriter* self, s32 a1, s32 a2, u64 a3)
{
    CountGifEntry(self, 1, 5);
    u8* p = self->cur;
    self->cur = p + 0x10;
    *(s32*)(p + 0x0) = a1;
    *(s32*)(p + 0x4) = a2;
    *(u64*)(p + 0x8) = a3;
}

void func_001615F0(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 1, 4);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = a1;
    p[1] = a2;
    p[2] = a3;
    p[3] = (a4 & 0xFF) << 4;
}

void func_00161670(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 1, 4);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = a1;
    p[1] = a2;
    p[2] = (a3 & 0xFFFFFF) << 4;
    p[3] = ((a4 & 0xFF) << 4) | 0x8000;
}

void func_00161708(PacketWriter* self, u64 a1, u64 a2)
{
    CountGifEntry(self, 1, 14);
    u64* p = self->cur64;
    self->cur64 = p + 2;
    p[0] = a2;
    p[1] = a1;
}

LINKER_REMNANT(func_00161760);

void func_00161768(PacketWriter* self, u32 a1, u64 a2)
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

void func_001617E8(PacketWriter* self, s32 tag, f32 value)
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

void func_00161860(PacketWriter* self, s32 a1, s32 a2)
{
    CountGifEntry(self, 0, 3);
    u64 v = (u64)a1 | (u64)(a2 << 16);
    u64* p = self->cur64;
    self->cur64 = p + 1;
    *p = v;
}

void func_001618C0(PacketWriter* self, s32 a1, s32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 0, 4);
    u64 lo = (u64)a1 | (u64)(a2 << 16);
    u64 mid = a3 & 0xFFFFFF;
    u64* p = self->cur64;
    self->cur64 = p + 1;
    *p = (lo | (mid << 32)) | ((u64)a4 << 56);
}

LINKER_REMNANT(func_00161950);

void func_00161958(PacketWriter* self, s32 count)
{
    self->Close(0);
    u64* p = self->cur64;
    self->cur64 = p + 2;
    p[0] = (u64)count | ((u64)2 << 58);
    p[1] = 0;
}

struct CameraBlock16 { u8 b[16]; };
extern u8* D_00261990;

u8* func_001619C0(u8* self)
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

void func_00161A88(void* self, s32 flag)
{
    (void)self;
    if (flag & 1) {
        FreeObjectMemory();
    }
}

void func_00161AB0(u8* self, void* a1, void* a2)
{
    FlushVertexBatch(self);
    BuildMatrixFromRotationAndTranslation(a1, a2, self);
    InvertRigidTransform(a1, a2, self + 0x40);
}

INCLUDE_ASM(func_00161B10);

void func_00161B80(u8* self)
{
    *(s32*)(self+0xF8)=0;
    *(s32*)(self+0x124)=0;
    ((MemoryFillFn)FillMemory)(self+0x128,0,0x1720);
}

void func_00161BB0(ColoredVertexBatch* self, s32 value)
{
    u32 local;
    FlushVertexBatch(self);
    self->f0F8 = value;
    local = 0xFFFFFFFF;
    SetVertexColor(self, &local);
}

void func_00161C00(UnlitVertexBatch* self)
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

void func_00161F70(LitVertexBatch* self)
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

void func_00162508(FlushedVertexBatch* self)
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

void func_00162680(VertexBatch* body, Vec3* v)
{
    body->x = v->x;
    body->y = v->y;
    body->z = v->z;
}

LINKER_REMNANT(func_001626A0);

void func_001626A8(u8* dst, u8* src)
{
    *(U32P*)(dst + 0x114) = *(U32P*)src;
}

void func_001626C0(VertexBatch* dst, U64P* src)
{
    dst->texCoord.v = src->v;
}

void func_001626D8(AppendVertexBatch* self, s32 value)
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

void func_00162810(RefOwner* owner)
{
    owner->refs = (void**)AllocateFrontMemory(owner->capacity << 2);
    s32 n = 0;
    for (s32 i = 0; i < owner->count; i++) {
        void* ref = owner->items[i].ref;
        if (ref != 0)
            owner->refs[n++] = ref;
    }
}

INCLUDE_RODATA(D_0024A710);
ASM_FUNC(func_00162890);

void func_00163938(s32 mode, void* obj)
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

void func_00163990(s32 mode, void* obj)
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

void func_001639E8(MeshBuildState* self, s32 mode, MorphTargetHeader* hdr, s32 n, Vec3* vecs, s32 extra,
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

void func_00163ED8(MeshBuildState* self, StripMeshOwner* obj, s32 mode, StripHeader* hdr, StripMesh* mesh,
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

void func_00164868(MeshBuildState* self, StripMeshOwner* obj, s32 unused2, s32 mode, StripHeader* hdr,
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

void func_00165588(PartPacketContext* a, PartPacketSource* b, PartPackets* c)
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

void func_00165728(AttachmentBlock* self, PlacedObject* ctx)
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

void func_00165828(AttachmentTargets* self, PlacedObject* ctx)
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

void func_00165920(AttachmentCopy* self, s32 arg, void* src)
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

INCLUDE_ASM(func_00165AE8);

void func_00165FE0(AnimatorOwner* self, PlacedObject* sub, f32 f)
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

void func_001660A0(PlacedObject* self)
{
    u8* p=(u8*)self->f224;
    if (p && (*(s32*)(p+0xB0)&16) && *(s32*)(p+0x64)) ApplyLinkConstraint(*(void**)(p+0x60));
}

void func_001660E8(PlacedObject* self, ParentFrame* par)
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

INCLUDE_ASM(func_001662A8);

void func_00166658(void)
{
    s32 v = 0x23C - D_00262474;
    D_00262474 = v;
    WriteVifBaseOffset(&g_vifPacketWriter, v, 0);
}

INCLUDE_RODATA(jtbl_0024A750);
INCLUDE_RODATA(jtbl_0024A780);
INCLUDE_ASM(func_00166690);

