// SPDX-License-Identifier: AGPL-3.0-or-later
// The buffered stream reader, 0x137290 to 0x1385A0 (no .rodata, .data or .bss of its own): the
// stream's set-up, refills from sectors or a file, its LZ-style unpacking and the typed readers
// (bytes, words, floats, vectors, matrices, meshes, face trees, strings, blocks). Its start is
// text_panel.cpp's proved end; its end is not proved by retail, only by the change of role to
// the world's contact pairs (world_contacts.cpp): no function on either side reads .rodata or
// .data of its own, so the cut could lie from 0x138550 to 0x1385A0. The name is ours, after its
// role.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "aim_blend_grid.h"
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
#include "common.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "object_finder.h"

// Types other files define, named by the parameters of their functions declared here.
struct LoadProgress;


f32 WrapModulo(f32 x, f32 y);

BufferedStream* InitBufferedStream(BufferedStream* self, s32 a1, u8* a2, s32 a3)
{
    sptr align = ((sptr)a2 + 0x3F) & -0x40;
    self->mode = -1;
    self->flags = a3;
    self->nextPtr = 0;
    self->ptr = 0;
    self->nextCount = 0;
    self->remaining = 0;
    self->progress = 0;
    self->unpackFlags = 0;
    self->unpackCarry = 0;
    self->end = align;
    self->start = a1 - (align - (sptr)a2);
    return self;
}

// Newly matched US functions from the small-function wave.
extern void ConstructTextPanelStatics(s32, s32);
extern void CloseBufferedStream(BufferedStream* self);
extern void FreeObjectMemory(void*);
extern void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

void DestroyBufferedStream(BufferedStream* self, s32 flags)
{
    CloseBufferedStream(self);
    if (flags & 1) FreeObjectMemory(self);
}

s32 OpenBufferedSectorStream(BufferedStream* r, s32 a1, s32 a2)
{
    r->mode = 1;
    r->sector = a1;
    r->totalSize = a2;
    r->bytesToRead = a2;
    r->bytesLeft = a2;
    r->nextPtr = r->end;
    r->f38 = 0;
    r->f44 = 0;
    r->discOpen = 0;
    s32 count = r->start / 0x100000;
    s32 m = 2;
    if (m < count) m = count;
    r->f50 = 0;
    r->f54 = 0;
    r->chunkCount = m;
    r->lastChunk = m - 1;
    return 1;
}

void OpenBufferedMemoryStream(BufferedStream* self, s32 size, u8* data) { self->remaining = size; self->cur = data; self->mode = 2; }

#include "common.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
struct TextPointObject;

struct Effect;


void ResetScreenElement(void* self);
void SetStepSequenceState(StepSequence* self, s32 next);



s32 OpenBufferedSectorStream(BufferedStream* r, s32 a1, s32 a2);

s32 OpenBufferedSectorStreamRange(BufferedStream* a, KeyId* pair)
{
    return OpenBufferedSectorStream(a, pair->first, pair->second);
}

extern f32 g_gameClock[];

extern "C" s32 GetStringLength(const char* s);
void* CopyString(void* dst, const char* src);
void PushFontScale(s32 a, f32 x, f32 y);
struct TextReader;
void* InitTextReader(TextReader* self, char* text, Font* font);
s32 WrapTextLines(TextReader* self, f32 limit);
void PopFontScale(s32 v);
void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

s32 ReadFile(s32 fd, void* buf, s32 size);

s32 CloseFile(s32 p);
extern "C" s32 StopDiscRead();
s32 CloseDiscStream(void);

void CloseBufferedStream(BufferedStream* self)
{
    s32 next = -1;
    switch (self->mode) {
    case 0:
        if (self->fileHandle >= 0) {
            CloseFile(self->fileHandle);
        }
        break;
    case 1:
        if (self->discOpen != 0) {
            if ((self->flags & 2) != 0) {
                StopDiscRead();
            } else {
                CloseDiscStream();
            }
        }
        break;
    default:
        break;
    }
    self->mode = next;
    self->nextPtr = 0;
    self->ptr = 0;
    self->nextCount = 0;
    self->remaining = 0;
    self->unpackFlags = 0;
    self->unpackCarry = 0;
}

s32 IsObjectAttached(void* obj);

struct NumberedItem;
void GetNumberedItemFlag(NumberedItem* self, s32* out);

s32 ReduceBufferedStreamBytesLeft(BufferedStream* self, s32 n)
{
    return self->bytesLeft -= n;
}

void GetCurrentLevelBit(u32* out);
struct RampProfile;
extern "C" f32 Cosine(f32 x);
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);

struct SectorStreamState {
    s32 flags;      // 0x00
    s32 mode;
    u8* base;       // 0x08
    s32 total;      // 0x0C
    u8 pad10[0x10];
    u8* pos;        // 0x20
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

extern "C" s32 GetDiscReadPosition();
extern "C" s32 SyncDiscNCommand(s32 mode);
s32 SyncDiscRead(s32 a);
extern "C" s32 GetDiscError();
s32 GetDiscReadError(void);
void StartLowLevelDiscReadUntilAccepted(s32 sector, s32 count, void* buffer);
void StartDiscReadUntilAccepted(s32 sector, s32 count, void* buffer);

struct SectorReadIssue {
    static void Read(SectorStreamState* self, s32 sector, s32 len, void* dst)
    {
        if (self->flags & 2) StartLowLevelDiscReadUntilAccepted(sector, len, dst);
        else StartDiscReadUntilAccepted(sector, len, dst);
    }
};

void RefillBufferedStreamFromSectors(SectorStreamState* self)
{
    self->pos += self->rem;
    self->rem = 0;
    s32 chunk = (self->total / self->count) & -0x800;
    if (self->cur > 0) {
        s32 n = self->readIdx + 1;
        if (self->pos == self->base + n * chunk) {
            n = n % self->count;
            self->cur--;
            self->readIdx = n;
            self->pos = n * chunk + self->base;
        }
    }
    do {
        if (self->size > 0) {
            s32 got;
            if (self->flags & 2) got = GetDiscReadPosition();
            else got = 0;
            got = MinOf::Of(got + self->start, self->size);
            if (self->done < got) {
                self->done = got;
            } else {
                s32 busy;
                if (self->flags & 2) busy = SyncDiscNCommand(1);
                else busy = SyncDiscRead(1);
                if (busy == 0) {
                    s32 err;
                    if (self->flags & 2) err = GetDiscError();
                    else err = GetDiscReadError();
                    if (err == 0) {
                        s32 size = self->size;
                        self->done = size;
                        self->sector += size / 0x800;
                        self->left -= size;
                        self->size = 0;
                        self->start = 0;
                    } else {
                        s32 done = self->done;
                        u8* dst = self->base + self->writeIdx * chunk + done;
                        s32 len = ((self->size - done + 0x7FF) & -0x800) / 0x800;
                        self->start = done;
                        s32 sector = self->sector + done / 0x800;
                        SectorReadIssue::Read(self, sector, len, dst);
                    }
                }
            }
        }
        s32 cur = self->cur;
        if (cur < self->count && self->size == 0 && self->left > 0) {
            s32 size = MinOf::Of(self->left, chunk);
            self->done = 0;
            self->size = size;
            s32 n = (self->writeIdx + 1) % self->count;
            self->cur = cur + 1;
            s32 len = ((size + 0x7FF) & -0x800) / 0x800;
            u8* dst = self->base + n * chunk;
            s32 sector = self->sector;
            self->writeIdx = n;
            SectorReadIssue::Read(self, sector, len, dst);
        }
        if (self->cur == 0) {
            self->rem = 0;
        } else {
            s32 singleBuffer = 1; // only the buffer being read is queued: it may still be loading
            s32 lim = chunk;
            if (self->cur == singleBuffer) lim = self->done;
            s32 avail = lim - (self->pos - (self->base + self->readIdx * chunk));
            self->rem = MinOf::Of(avail, 0x8000);
        }
    } while (self->rem == 0 && self->left > 0);
}

extern s32 ReadFile(s32 fd, void* buf, s32 size);
struct FileStreamState { u8 pad0[8]; void* buffer; s32 fC; u8 pad10[4]; s32 fileLeft; u8 pad18[8]; void* fillPtr; s32 fillCount; u8 pad28[0xC]; s32 fileHandle; };
void RefillBufferedStreamFromFile(FileStreamState* self)
{
    s32 size = self->fC;
    s32 limit = self->fileLeft;
    self->fillPtr = self->buffer;
    size = (size > 0x8000) ? MinOf::Of(0x8000, limit) : MinOf::Of(size, limit);
    self->fillCount = ReadFile(self->fileHandle, self->fillPtr, size);
}

struct MaxOf { static s32 Of(s32 a, s32 b) { return a < b ? b : a; } };
void RefillBufferedStreamFromFile(FileStreamState* self);
void RefillBufferedStreamFromSectors(SectorStreamState* self);
void UpdateLoadProgress(LoadProgress* self, s32 value);
void RefillBufferedStream(BufferedStream* self)
{
    switch (self->mode) {
    case 0: RefillBufferedStreamFromFile((FileStreamState*)self); break;
    case 1: RefillBufferedStreamFromSectors((SectorStreamState*)self); break;
    }
    s32 value = self->bytesToRead - self->nextCount;
    value = MaxOf::Of(0, value);
    self->bytesToRead = value;
    if (self->progress) UpdateLoadProgress((LoadProgress*)self->progress, value);
}


void ResetTextPointToHalf(TextPointObject* self);


void RefillBufferedStream(BufferedStream* d);
extern "C" void* CopyBytes(void* dst, void* src, s32 n);

void UnpackBufferedStream(BufferedStream* d)
{
    u8* base = (u8*)0x70000000;
    s32 pos = 0;
    s32 n = d->nextCount;
    u8* p = d->next;
    s32 flags = d->unpackFlags;
    s32 more;
    s32 carry = d->unpackCarry;
    if (carry > 0) {
        CopyBytes((void*)0x70000000, (void*)0x70002000, carry);
        pos = d->unpackCarry;
    }
    while ((more = pos < 0x2000) != 0) {
        flags >>= 1;
        if (!(flags & 0x100)) {
            if (--n < 0) {
                RefillBufferedStream(d);
                if (d->nextCount <= 0) break;
                p = d->next;
                n = d->nextCount - 1;
            }
            flags = *p++ + 0xFF00;
        }
        if (--n < 0) {
            RefillBufferedStream(d);
            if (d->nextCount <= 0) break;
            p = d->next;
            n = d->nextCount - 1;
        }
        s32 b = *p++;
        if (flags & 1) {
            base[pos++] = b;
        } else {
            if (--n < 0) {
                RefillBufferedStream(d);
                p = d->next;
                n = d->nextCount - 1;
            }
            u32 v = b + (*p++ << 8);
            s32 cnt = ((s32)v >> 13) + 2;
            s32 src = v & 0x1FFF;
            for (; cnt >= 0; cnt--) {
                base[pos++] = base[src++ & 0x1FFF];
            }
        }
    }
    d->cur = base;
    if (more == 0) {
        d->remaining = 0x2000;
        d->unpackCarry = pos - 0x2000;
    } else {
        d->remaining = pos;
        d->unpackCarry = 0;
    }
    d->next = p;
    d->nextCount = n;
    d->unpackFlags = flags;
}


extern f32 g_gameTime;

struct BaseObject;
struct PlayingSound;
struct Vec02;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

extern u8 func_00135E20[];
extern u8 func_00135E40[];

s32 MaskWorldBitsBySave(void);

// NEAR: control flow and the calls match; the compiler picks s0 for self and s1 for n (retail: s1, s0),
// and keeps the loaded count in $a2 where retail uses $v1.
void UnpackBufferedStream(BufferedStream* self);
void RefillBufferedStream(BufferedStream* self);
void CopyMemory(void* dst, void* src, u32 size);

void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out)
{
    u8* dst = (u8*)out;
    if (self->remaining < 0) {
        return;
    }
    if (remaining <= 0) {
        return;
    }
    do {
        s32 cnt = self->remaining;
        if (cnt == 0) {
            if (self->flags & 4) {
                UnpackBufferedStream(self);
            } else {
                RefillBufferedStream(self);
                s32 nc = self->nextCount;
                sptr np = self->nextPtr;
                self->remaining = nc;
                self->ptr = np;
                self->nextPtr = np + nc;
                self->nextCount = 0;
            }
            cnt = self->remaining;
            if (cnt == 0) {
                self->remaining = -1;
                return;
            }
        }
        s32 n;
        if (remaining < cnt) {
            n = remaining;
        } else {
            n = cnt;
        }
        if (dst != 0) {
            CopyMemory(dst, (void*)self->ptr, n);
            dst += n;
        }
        remaining -= n;
        self->ptr += n;
        self->remaining -= n;
    } while (remaining > 0);
}

void AlignBufferedStreamPosition(BufferedStream* self, s32 n)
{
    sptr head = self->ptr;
    sptr t = head - 1;
    t = t + n;
    sptr aligned = t & -n;
    s32 delta = aligned - head;
    self->ptr = aligned;
    self->remaining -= delta;
}

s32 ReadBufferedU8(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 1) {
        u8* p = self->cur;
        s32 value = p[0];
        self->cur = p + 1;
        self->remaining = count - 1;
        return value;
    }
    u8 value;
    ReadBufferedStreamBytes(self, 1, &value);
    return value;
}

u16 ReadBufferedU16(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 2) {
        u8* p = self->cur;
        s32 value = p[0] | (p[1] << 8);
        self->cur = p + 2;
        self->remaining = count - 2;
        return value;
    }
    u16 value;
    ReadBufferedStreamBytes(self, 2, &value);
    return value;
}

u32 ReadBufferedU32(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 4) {
        u8* p = self->cur;
        u32 value = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        self->cur = p + 4;
        self->remaining = count - 4;
        return value;
    }
    u32 value;
    ReadBufferedStreamBytes(self, 4, &value);
    return value;
}

LINKER_REMNANT(func_00137CB8);

s32 ReadBufferedS8(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 1) {
        u8* p = self->cur;
        s32 value = (s8)p[0];
        self->cur = p + 1;
        self->remaining = count - 1;
        return value;
    }
    s8 value;
    ReadBufferedStreamBytes(self, 1, &value);
    return value;
}


void RemoveEffect(Effect* self);
void SetEffectPhase(Effect* self, s32 mode);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

s32 ReadBufferedS16(BufferedStream* self)
{
    if (self->remaining >= 2) {
        u8* p = self->cur;
        u8 lo = p[0];
        s32 hi = p[1];
        self->cur = p + 2;
        self->remaining -= 2;
        return lo | ((s16)(hi << 8));
    }
    s16 tmp;
    ReadBufferedStreamBytes(self, 2, &tmp);
    return tmp;
}

s32 ReadBufferedS32(BufferedStream* self)
{
    s32 count = self->remaining;
    if (count >= 4) {
        u8* p = self->cur;
        s32 value = p[0] + (p[1] << 8) + (p[2] << 16) + ((s8)p[3] << 24);
        self->cur = p + 4;
        self->remaining = count - 4;
        return value;
    }
    s32 value;
    ReadBufferedStreamBytes(self, 4, &value);
    return value;
}

LINKER_REMNANT(func_00137DF0);

void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

f32 ReadBufferedFloat(BufferedStream* r)
{
    s32 left = r->remaining;
    if (left >= 4) {
        u8* p = r->cur;
        u32 v = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        r->cur = p + 4;
        r->remaining = left - 4;
        return *(f32*)&v;
    }
    f32 tmp;
    ReadBufferedStreamBytes(r, 4, &tmp);
    return tmp;
}

void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

void ReadBufferedVector3(BufferedStream* src, void* dst)
{
    ReadBufferedStreamBytes(src, 12, dst);
}

void ReadBufferedVector4(BufferedStream* self, void* out) { ReadBufferedStreamBytes(self, 0x10, out); }

void ReadBufferedRotation3(BufferedStream* self, void* out)
{
    u8* buffer = (u8*)out;
    ReadBufferedStreamBytes(self, 0xC, buffer);
    ReadBufferedStreamBytes(self, 0xC, buffer + 0x10);
    ReadBufferedStreamBytes(self, 0xC, buffer + 0x20);
}

extern f32 g_gameTime;

struct Font;
struct TextReader;
void* InitTextReader(TextReader* self, char* text, Font* font);
s32 CountTextChars(void* self);

void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

void ReadBufferedMatrix4(BufferedStream* self, void* out)
{
    u8* p = (u8*)out;
    u8* a = p + 0x10;
    u8* b = p + 0x20;
    u8* c = p + 0x30;

    ReadBufferedStreamBytes(self, 12, p);
    ReadBufferedStreamBytes(self, 12, a);
    ReadBufferedStreamBytes(self, 12, b);
    ReadBufferedStreamBytes(self, 12, c);
    *(s32*)(p + 0xC) = 0;
    *(s32*)(a + 0xC) = 0;
    *(s32*)(b + 0xC) = 0;
    *(f32*)(c + 0xC) = 1.0f;
}

u16 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedU8(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
void ReadBufferedVector3(BufferedStream* src, void* dst);
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

s32 ReadBufferedU8(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);

void ReadMeshFromStream(BufferedStream* in, Mesh03* mesh)
{
    s32 i = 0;
    mesh->radius = ReadBufferedFloat(in);
    s32 n = ReadBufferedU16(in);
    mesh->vertCount = n;
    mesh->verts = AllocateFrontMemory(n << 4);
    while (i < mesh->vertCount) {
        ReadBufferedVector3(in, (u8*)mesh->verts + (i << 4));
        i++;
    }
    s32 face = 0;
    s32 fc = ReadBufferedU16(in);
    mesh->faceCount = fc;
    mesh->faces = AllocateZeroedFrontMemory(fc << 5);
    mesh->points = AllocateFrontMemory(mesh->faceCount << 4);
    mesh->words = AllocateFrontMemory(mesh->faceCount << 2);
    s32 ec = ReadBufferedU16(in);
    mesh->edgeCount = ec;
    void* edges = AllocateZeroedFrontMemory(ec << 4);
    mesh->edges = edges;
    MeshEdge03* nextEdge = (MeshEdge03*)edges;
    while (face < mesh->faceCount) {
        MeshFace03* f = (MeshFace03*)((u8*)mesh->faces + (face << 5));
        s32 k = 0;
        s32 idx[3];
        idx[0] = ReadBufferedU16(in);
        idx[1] = ReadBufferedU16(in);
        idx[2] = ReadBufferedU16(in);
        Vec02 e1;
        Vec02 e2;
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(((Vec02*)mesh->verts)[idx[1]]), Vu0::Q(((Vec02*)mesh->verts)[idx[0]]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(((Vec02*)mesh->verts)[idx[2]]), Vu0::Q(((Vec02*)mesh->verts)[idx[0]]));
        u128 nrm = Vu0::Cross(Vu0::Q(e1), Vu0::Q(e2));
        u128 unit = Vu0::DivX(nrm, Vu0::Length(nrm));
        Vu0::Q(f->normal) = unit;
        f->vert = idx[0];
        Vu0::StoreX(f->offset, Vu0::Dot(unit, Vu0::Q(((Vec02*)mesh->verts)[f->vert])));
        ((f32*)mesh->words)[face] = ReadBufferedFloat(in);
        ReadBufferedVector3(in, (u8*)mesh->points + (face << 4));
        s32 cnt = ReadBufferedU8(in);
        while (k < cnt) {
            MeshEdge03* e = nextEdge;
            nextEdge = e + 1;
            e->a = ReadBufferedU16(in);
            e->b = ReadBufferedU16(in);
            e->face = face;
            e->other = ReadBufferedU16(in);
            if (k == 0) {
                f->first = e;
            } else {
                e[-1].next = e;
            }
            MeshFace03* g = (MeshFace03*)((u8*)mesh->faces + (e->other << 5));
            k++;
            e->link = g->edges;
            g->edges = e;
        }
        face++;
    }
}


u16 ReadBufferedU16(BufferedStream* self);
void* AllocateZeroedFrontMemory(s32 size);

void ReadFaceTree(BufferedStream* self, Mesh03* in, Tree03* out)
{
    s32 x = ReadBufferedU16(self);
    out->count = x;
    s32 y = ReadBufferedU16(self);
    out->count2 = y;
    out->nodes = (TreeNode03*)AllocateZeroedFrontMemory(12 * out->count);
    for (s32 i = 0; i < out->count; i++) {
        TreeNode03* e = out->nodes + i;
        s32 v = ReadBufferedU16(self);
        e->face = (u8*)in->faces + (v << 5);
        s32 w = ReadBufferedU16(self);
        if ((w & 0xFFFF) != 0xFFFF) {
            e->back = out->nodes + w;
        }
        s32 z = ReadBufferedU16(self);
        if ((z & 0xFFFF) != 0xFFFF) {
            e->front = out->nodes + z;
        }
    }
}

void CopyCollider(Collider* self, Collider* other);

struct LinkedItem {
    u8 pad0[0x10];
    f32 f10;
    s32 linkA;
    s32 linkB;
    u8 pad1[0x20 - 0x1C];
};

u16 ReadBufferedU16(BufferedStream* self);
void* AllocateZeroedFrontMemory(s32 bytes);
void ReadBufferedVector3(BufferedStream* src, void* dst);
f32 ReadBufferedFloat(BufferedStream* r);
u32 ReadBufferedU32(BufferedStream* self);

void ReadLinkedItemArray(BufferedStream* src, s32* count, LinkedItem** out)
{
    s32 n = ReadBufferedU16(src);
    *count = n;
    *out = (LinkedItem*)AllocateZeroedFrontMemory(n << 5);

    for (s32 i = 0; i < *count; i++) {
        LinkedItem* item = &(*out)[i];
        ReadBufferedVector3(src, item);
        item->f10 = ReadBufferedFloat(src);

        s32 v = ReadBufferedU32(src);
        if ((v & 0x80000000) != 0) {
            item->linkA = v;
        } else {
            item->linkA = (s32)((*out) + v);
        }
        v = ReadBufferedU32(src);
        if ((v & 0x80000000) != 0) {
            item->linkB = v;
        } else {
            item->linkB = (s32)((*out) + v);
        }
    }
}

void* AllocateFrontMemory(s32 size);
void ReadBufferedString(BufferedStream* self, u8** out)
{
    s32 size = ReadBufferedU16(self);
    u8* buffer = (u8*)AllocateFrontMemory(size + 1);
    ReadBufferedStreamBytes(self, size, buffer);
    buffer[size] = 0;
    *out = buffer;
}

LINKER_REMNANT(func_00138510);

extern f32 g_gameTime;


void LoadCollider(Collider* self, BufferedStream* in);
void FindOrBuildMemberGroup(void** out, void* self);


u16 ReadBufferedU16(BufferedStream* self);
void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

void SkipBufferedBlock(BufferedStream* self)
{
    s32 n = ReadBufferedU16(self);
    ReadBufferedStreamBytes(self, n, 0);
}

struct OptionalBlock {
    s32 w[8];
};

void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);
u32 CopyToFrontMemory(s32 size, void* src);

void ReadOptionalBufferedBlock(BufferedStream* self, u32* out)
{
    OptionalBlock r;
    ReadBufferedStreamBytes(self, 0x20, &r);
    if (r.w[1] != r.w[7]) {
        *out = CopyToFrontMemory(0x20, &r);
    } else {
        *out = 0;
    }
}
