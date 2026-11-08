// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 502/524 (95.8%), checked 2026-11-08
// NEAR (2026-11-08, night-gamec): eight instructions at the outer loop's top: retail loads the list base before the count and multiplies into a0 with 0x1800 in v0; register choice only
// In the context of its file, src/main/file_137290.cpp: its declarations before the function, bodies cut.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "c8b.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"
#include "anim_curve.h"
#include "attachment.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "vu0.h"
#include "placed_object.h"
#include "collider.h"

// The file's .data: the two words func_00139C38 registers with func_00139B70 (4-aligned, so
// the .data starts right after text_panel.cpp's; 0x26131C is padding before class 0x3B's).
// Tried (order-class pass): list base as local before the count, product operand order, count as a local before the base, count*2-1 written three ways, the axis loop as a while/for-scope variant: still the same 8 words.
s32 g_alphaStatePacket1 = 0;
s32 g_alphaStatePacket2 = 0;

f32 WrapModulo(f32 x, f32 y);

BufferedStream* InitBufferedStream(BufferedStream* self, s32 a1, s32 a2, s32 a3);

// Newly matched US functions from the small-function wave.
extern void ConstructTextPanelStatics(s32, s32);
extern void CloseBufferedStream(void*);
extern void FreeObjectMemory(void*);
extern void ReadBufferedStreamBytes(void*, s32, void*);

void DestroyBufferedStream(void* self, s32 flags);

s32 OpenBufferedSectorStream(BufferedStream* r, s32 a1, s32 a2);

void OpenBufferedMemoryStream(BufferedStream* self, s32 a1, s32 a2);

#include "common.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"

void ResetScreenElement(void* self);
void SetStepSequenceState(void* obj, s32 mode);

s32 OpenBufferedSectorStream(void* a, void* b, s32 c);

void OpenBufferedSectorStreamRange(void* a, KeyId* pair);

extern f32 g_gameClock[];

s32 GetStringLength(const char* s);
void* CopyString(void* dst, const char* src);
void PushFontScale(s32 a, f32 x, f32 y);
void* InitTextReader(void* buf, void* p, s32 v);
s32 WrapTextLines(void* buf, f32 x);
void PopFontScale(s32 v);
void RewindTextReader(void* buf);
s32 ReadTextChar(void* buf);

s32 ReadFile(s32 p, s32 a, s32 b);

s32 CloseFile(s32 p);
s32 StopDiscRead(void);
s32 CloseDiscStream(void);

void CloseBufferedStream(BufferedStream* self);

s32 IsObjectAttached(void* obj);

void GetNumberedItemFlag(void* obj, s32* out);

s32 ReduceBufferedStreamBytesLeft(BufferedStream* self, s32 n);

void GetCurrentLevelBit(u32* out);
f32 Cosine(f32 x);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, f32* p, s32 zero);

struct SectorStreamState {
    s32 flags;      // 0x00
    s32 f04;
    s32 base;       // 0x08
    s32 total;      // 0x0C
    u8 pad10[0x10];
    s32 pos;        // 0x20
    s32 rem;        // 0x24
    u8 pad28[0x10];
    s32 done;       // 0x38
    s32 size;       // 0x3C
    s32 left;       // 0x40
    s32 start;      // 0x44
    s32 sector;     // 0x48
    s32 count;      // 0x4C
    s32 cur;        // 0x50
    s32 readIdx;    // 0x54
    s32 writeIdx;   // 0x58
};

struct MinOf {
    static s32 Of(s32 a, s32 b) { return a < b ? a : b; }
};

s32 GetDiscReadPosition(void);
s32 SyncDiscNCommand(s32 a);
s32 SyncDiscRead(s32 a);
s32 GetDiscError(void);
s32 GetDiscReadError(void);
void StartLowLevelDiscReadUntilAccepted(s32 a, s32 b, s32 c);
void StartDiscReadUntilAccepted(s32 a, s32 b, s32 c);

struct SectorReadIssue {
    static void Read(SectorStreamState* self, s32 sector, s32 len, s32 dst)
    {
        if (self->flags & 2) StartLowLevelDiscReadUntilAccepted(sector, len, dst);
        else StartDiscReadUntilAccepted(sector, len, dst);
    }
};

void RefillBufferedStreamFromSectors(SectorStreamState* self);

extern s32 ReadFile(void*, s32, s32);
struct FileStreamState { u8 pad0[8]; s32 f8; s32 fC; u8 pad10[4]; s32 f14; u8 pad18[8]; s32 f20; s32 f24; u8 pad28[0xC]; void* f34; };
void RefillBufferedStreamFromFile(FileStreamState* self);

struct MaxOf { static s32 Of(s32 a, s32 b) { return a < b ? b : a; } };
void RefillBufferedStreamFromFile(void* self);
void RefillBufferedStreamFromSectors(void* self);
void UpdateLoadProgress(void* self, s32 value);
void RefillBufferedStream(BufferedStream* self);

s32 GatherObjectsById(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void ResetTextPointToHalf(void* p);

void RefillBufferedStream(BufferedStream* d);
void CopyBytes(void* dst, void* src, s32 n);

void UnpackBufferedStream(BufferedStream* d);

extern f32 g_gameTime;

void StartSoundEffect(s32 a, s32 b, s32 c, s32 d, f32 g, f32 h, f32 i, f32 j, f32 k, s32 e, s32 f);

extern u8 func_00135E20[];
extern u8 func_00135E40[];

s32 MaskWorldBitsBySave(void);

// NEAR: control flow and the calls match; the compiler picks s0 for self and s1 for n (retail: s1, s0),
// and keeps the loaded count in $a2 where retail uses $v1.
void UnpackBufferedStream(BufferedStream* self);
void RefillBufferedStream(BufferedStream* self);
void CopyMemory(void* dst, void* src, s32 count);

void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, u8* dst);

void AlignBufferedStreamPosition(BufferedStream* self, s32 n);

s32 ReadBufferedU8(BufferedStream* self);

s32 ReadBufferedU16(BufferedStream* self);

u32 ReadBufferedU32(BufferedStream* self);

s32 ReadBufferedS8(BufferedStream* self);

void RemoveEffect(void* handle);
void SetEffectPhase(void* handle, s32 mode);
void FillMemory(void* block, s32 value, s32 size);

void ReadBufferedStreamBytes(void* self, s32 count, void* out);

s32 ReadBufferedS16(BufferedStream* self);

s32 ReadBufferedS32(BufferedStream* self);

void ReadBufferedStreamBytes(void* self, s32 size, void* dst);

f32 ReadBufferedFloat(BufferedStream* r);

void ReadBufferedStreamBytes(void* self, s32 size, void* dst);

void ReadBufferedVector3(void* src, void* dst);

void ReadBufferedVector4(void* self, void* out);

void ReadBufferedRotation3(void* self, u8* buffer);

extern f32 g_gameTime;

void* InitTextReader(void* out, void* p, s32 handle);
s32 CountTextChars(void* self);

void ReadBufferedStreamBytes(void* self, s32 size, void* obj);

void ReadBufferedMatrix4(void* self, u8* p);

s32 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedU8(void* self);
f32 ReadBufferedFloat(void* self);
void ReadBufferedVector3(void* src, void* dst);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);

struct MeshEdge03 {
    u16 a;
    u16 b;
    s16 face;
    s16 other;
    MeshEdge03* next;
    MeshEdge03* link;
};

struct MeshFace03 {
    Vec02 normal;
    u32 offset;
    MeshEdge03* first;
    MeshEdge03* edges;
    u16 pad1C;
    u16 vert;
};

s32 ReadBufferedU8(void* self);
f32 ReadBufferedFloat(void* self);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);

void func_00137FB0(BufferedStream* in, Mesh03* mesh);

s32 ReadBufferedU16(void* self);
void* AllocateZeroedFrontMemory(s32 size);

void ReadFaceTree(void* self, Mesh03* in, Tree03* out);

void CopyCollider(void* self, void* other);

struct LinkedItem {
    u8 pad0[0x10];
    f32 f10;
    s32 f14;
    s32 f18;
    u8 pad1[0x20 - 0x1C];
};

s32 ReadBufferedU16(void* src);
void* AllocateZeroedFrontMemory(s32 bytes);
void ReadBufferedVector3(void* src, void* item);
f32 ReadBufferedFloat(void* src);
s32 ReadBufferedU32(void* src);

void ReadLinkedItemArray(void* src, s32* count, LinkedItem** out);

void* AllocateFrontMemory(s32 size);
void ReadBufferedString(void* self, u8** out);

extern f32 g_gameTime;

void LoadCollider(void* self);
void FindOrBuildMemberGroup(void* sub, void* self);

s32 ReadBufferedU16(void* src);
void ReadBufferedStreamBytes(void* self, s32 size, void* obj);

void SkipBufferedBlock(void* self);

struct OptionalBlock {
    s32 w[8];
};

void ReadBufferedStreamBytes(void* self, s32 size, void* obj);
u32 CopyToFrontMemory(s32 size, void* src);

void ReadOptionalBufferedBlock(void* self, u32* out);

void InitCollider(Collider* self);

struct ContactPairLink { s32 f0; s32 f4; ContactPairLink* f8; Collider* fC; };

ContactPairLink* PushContactRow(World* w, s32 a, s32 b);
ContactPairLink* UnlinkContactRow(World* w, s32 a, s32 b);
void FreePooledContactChain(World* w, s32 a);
void ClearRootTries(Collider* e);
void PushFreeSlot(u8* w, ContactPairLink* l);

void SetContactPairFlags(World* w, s32 a, s32 b, u8 set, u8 clr);

struct ContactRowNode { s32 a0; ContactRowNode* next; void* a8; s32 value; };
struct ContactRowList { ContactRowNode* head; };
struct ContactRowSource { u8 pad0[4]; s32 value4; };

void* TakePoolSlot(void* pool);

ContactRowNode* PushContactRow(World* self, ContactRowList* list, ContactRowSource* src);

ContactRow03* UnlinkContactRow(void* unused, ContactRow03** head, Contacts03* key);

void* FindContactRow(Collider* self, Collider* other);

void* FindContactRow(void* self, void* other);

s32 GetContactRowHead(void* self, void* other);

struct SweepAxisSlot {
    s32 flag;
    void* owner;
    void* link;
};

void MarkSweepAxesUnsorted(void* self);

void AddColliderToSweepAxes(World* self, void* arg);

#include "common.h"
#include "list_iter.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "c8b.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"

void MarkSweepAxesUnsorted(World* a0);

void MoveMemory(void* dst, void* src, s32 bytes);

// An entry of one of the three sweep axes (0x200 of them each in buf1AD8): a body's start (0)
// or end (1) on the axis and the bound it reads.
struct SweepEntry {
    s32 end;                // 0x00
    Collider* body;         // 0x04
    f32* bound;             // 0x08
};

void SortSweepAxes(World* self)
{
    if (self->count38 == 0 || self->f1AEC != 0) {
        return;
    }
    s32 axis = 0;
    u8 bit = 1;
    for (; axis < 3; axis++) {
        SweepEntry* p = (SweepEntry*)((u8*)self->buf1AD8 + axis * 0x1800);
        SweepEntry* list = p;
        f32 top = *p->bound;
        p++;
        for (s32 k = self->count38 * 2 - 1; k > 0; p++, k--) {
            f32 v = *p->bound;
            if (top <= v) {
                top = v;
            } else {
                SweepEntry* q = p - 1;
                while (q >= list) {
                    if (*q->bound <= v) {
                        break;
                    }
                    if (p->end != q->end) {
                        if (p->end == 0) {
                            SetContactPairFlags(self, (s32)p->body->contacts, (s32)q->body->contacts, bit, 0);
                        } else {
                            SetContactPairFlags(self, (s32)p->body->contacts, (s32)q->body->contacts, 0, bit);
                        }
                    }
                    q--;
                }
                q++;
                SweepEntry tmp = *p;
                MoveMemory(q + 1, q, (p - q) * sizeof(SweepEntry));
                *q = tmp;
            }
        }
        bit <<= 1;
    }
    self->f1AEC = 1;
}
