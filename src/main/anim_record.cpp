// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "path_curve_object.h"
#include "cursor_animator.h"
#include "world.h"
#include "packet_writer.h"
#include "font.h"
#include "list_iter.h"
#include "shapes.h"
#include "globals.h"
#include "range_record.h"
#include "vu0.h"
#include "texture_table.h"
#include "bump_allocator.h"
#include "buffered_stream.h"
#define TEST_1B3510(ate, atst, aref, afail, date, datm, zte, ztst) \
    ((u64)(ate) | ((u64)(atst) << 1) | ((u64)(aref) << 4) | ((u64)(afail) << 12) | ((u64)(date) << 14) | \
     ((u64)(datm) << 15) | ((u64)(zte) << 16) | ((u64)(ztst) << 17))
#define ALPHA_1B3510(a, b, c, d, fix) \
    ((u64)(a) | ((u64)(b) << 2) | ((u64)(c) << 4) | ((u64)(d) << 6) | ((u64)(fix) << 32))
#include "script_value.h"
#include "switched_collider.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "attachment.h"
#include "state_walker.h"
#include "asm_func.h"

extern u32 D_00275718;
void ReadBufferedStreamBytes(void* a, s32 b, void* c);
// A GIF register word, built from a zeroed doubleword.
struct GifWord {
    u64 bits;
};
u64 GetTextureRegisterBits(TextureTable* obj, s32 p1, s32 p2);
void AddGifRegisterWrite(void* ctx, s32 kind, u64 value);
void FillMemory(void* p, s32 v, s32 n);
extern s32 g_imageRecordCountB;
extern s32 g_imageSlotsB;
u16 ReadBufferedU16(void* self);
void* AllocateZeroedFrontMemory(s32 bytes);
void ReadBufferedStreamBytes(void* self, s32 size, void* obj);
extern s32 g_imageRecordCountA;
extern s32 g_imageSlotsA;
extern s32 g_activeImageMask;
void InitBumpAllocator(void* dst, s32 size, s32 align);
void SendMaskedImagesToGif(s32 a, void* b);
extern f32 g_gameTime;
u32* AllocateFrontMemory(s32 bytes);
extern s32 D_002626CC;
void FlushCursors(void);
void ResetBumpAllocator(BumpAllocator* p);
void FlushMeshQueue(void);
void UpdateMatchingListedObjects(s32 mask);
// EXACT (us)

extern s32 g_animRecordCount;
extern AnimRecord* g_animRecords;
extern s32 g_cursorAnimatorCount;
extern CursorAnimator** g_cursorAnimators;
extern s32 g_maskImageUploads[];
extern s32 g_maskedImagesPacket;
void LoadImageRecordsB(void* self);
void LoadImageRecordsA(void* self);
void ReadBufferedStreamBytes(void* self, s32 key, AnimRecord* out);
CursorAnimator* ReadAnimator(void* self);
void ReadTextureTable(void* self, TextureTable* e);
void LoadFonts(void* self);
void InitBumpAllocator(BumpAllocator* p, s32 a, s32 b);
s32 PlaceMaskedImages(s32 mask, BumpAllocator* arg, s32 f);
void BuildAnimRecordGifPackets(s32 mask);
void UploadAllFontImages(void);
void InitScreenElements(void);
s32 UploadImagesByMask(s32 mask);
s32 BuildMaskedImagesPacket(s32 mask);
void* InitGifPacket(PacketWriter* b);
void UsePacketBufferMemory(PacketWriter* b, s32 n, Quad4* q);
void ReserveGifPackedData(PacketWriter* b, s32 a, s32 c, s32 d, s32 e, s32 f);
void BeginGifTag(PacketWriter* b, s32 a, s32 c, u64 d);
void AddGifRegisterWrite(PacketWriter* b, s32 reg, u64 v);
void SendTextureRegisters(TextureTable* e, s32 j, s32 pass, s32 kind, PacketWriter* b);
void CloseDmaTag(PacketWriter* b);
void ClearPacketBuffer(PacketWriter* b);
void CloseGifTag(PacketWriter* b, s32 n);
void AddGifStEntry(PacketWriter* b, f32 x, f32 y, f32 z);
void AddGifRgbaEntry(PacketWriter* b, u32 c);
extern u8 g_fontMethods[];
void* AllocateOrThrow(s32 size);
// A font of the level's table (g_fontRecords), built with the font's table in place.
struct LoadedFont : Font {
    LoadedFont() { vt = (const FontVt*)g_fontMethods; }
    void* operator new[](__SIZE_TYPE__ size) { return AllocateOrThrow(size); }
};
extern s32 g_fontCount;
extern LoadedFont* g_fontRecords;
extern s32 g_defaultFont;
s32 ReadBufferedU16(BufferedStream* src);
void LoadFont(LoadedFont* e, BufferedStream* self);
s32 GetFontById(s32 n);
void SetCursorFrame(s32 a, s32 frame);
void LoadAnimatorBase(CursorAnimator* self, const AnimatorParams* src);
void BindAnimatorRecord(CursorAnimator* self);
void SetCursorFrame(AnimCursor* cur, s32 idx);
void SetCursorCoords(AnimCursor* cur, f32 x, f32 y);
AnimRecord* FindAnimRecord(s32 key);
extern AnimCursor* g_lastPendingCursor;
extern AnimCursor* g_pendingCursors;
f32 RandomFloatInRange(f32 a, f32 b);
struct FacingXY { f32 x; f32 y; };
struct PartFacingSource { u8 pad0[0x34]; s32 i34; };
struct DrawnPart {
    void* vt; u8 pad0[0xC]; FacingXY vec; u8 pad1[0x60]; PartFacingSource* p78;
};
extern u8 DrawModelPart[];
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapModulo(f32 a, f32 b);
f32 FloatRemainder(f32 a, f32 b);
void SubmitMeshQueueEntry(void* p);
s32 ClaimAnimatorStep(CursorAnimator* p);
s32 GetAnimatorSize(s32 type);
void* AllocateZeroedFrontMemory(s32 size);
void* GetAnimatorMethods(s32 type);
void ReadBufferedStreamBytes(void* owner, s32 key, void* out);
void FillMemory(void* p, int zero, s32 count);
struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };
void ConvertHsvToRgb(Quad_001B4580* p);
f32 WrapAngle(f32 a);
void ComputeSinCos(f32 angle, f32* a, f32* b);
f32 WrapModulo(f32 x, f32 y);
// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table g_frameRunAnimatorMethods[];
extern const Fn_Table g_framePingPongAnimatorMethods[];
extern const Fn_Table g_randomJumpAnimatorMethods[];
extern const Fn_Table g_angleFrameAnimatorMethods[];
extern u8 g_crossfadeAnimatorMethods[];
extern const Fn_Table g_scrollAnimatorMethods[];
extern const Fn_Table g_circleAnimatorMethods[];
extern const Fn_Table g_triangleAnimatorMethods[];
struct RandomRangeLow { s32 v; };
s32 RandomIntInRange(RandomRangeLow lo, s32 hi);

// The file's .data, in retail's order.
s32 g_animRecordCount = 0;
AnimRecord* g_animRecords = 0;
s32 g_imageRecordCountA = 0;
ImageRecord* g_imageRecordsA = 0;
s32 g_imageRecordCountB = 0;
PaletteRecord* g_imageRecordsB = 0;
s32 g_imageSlotsA = 0;
s32 g_imageSlotsB = 0;
s32 g_activeImageMask = 0;
AnimCursor* g_pendingCursors = 0;
s32 g_maskImageUploads[6] = {0};
s32 g_maskedImagesPacket = 0;
s32 g_cursorAnimatorCount = 0;
CursorAnimator** g_cursorAnimators = 0;
AnimCursor* g_lastPendingCursor = 0;

u64 GetTextureRegisterBits(TextureTable* t, s32 i, s32 j)
{
    ImageRecord* e = ((ImageRecord**)t->entries)[i];
    s32 stride = 1;
    if (t->record->kind == 0) stride = 3;
    PaletteRecord* c = ((PaletteRecord**)t->cells)[i * stride + j];
    u64 r = e->f18;
    if (c != 0) r |= c->f10;
    return r;
}

void SendTextureRegisters(TextureTable* obj, s32 p1, s32 p2, s32 flag, void* ctx)
{
    GifWord a;
    GifWord b;
    GifWord c;
    GifWord d;
    GifWord e;
    s32 sel = flag ^ 5;
    u64 one = 1;

    FillMemory(&a, 0, 8);
    FillMemory(&b, 0, 8);
    FillMemory(&c, 0, 8);
    FillMemory(&d, 0, 8);
    FillMemory(&e, 0, 8);

    a.bits = GetTextureRegisterBits(obj, p1, p2);
    s32 kindA = 7;
    if (sel != 0) {
        kindA = 6;
    }
    AddGifRegisterWrite(ctx, kindA, a.bits);

    b.bits = ((b.bits | one | 0x20) & ~0x1C0ULL) | 0x40;
    s32 kindB = 0x15;
    if (sel != 0) {
        kindB = 0x14;
    }
    AddGifRegisterWrite(ctx, kindB, b.bits);

    if (obj->flags & 1) {
        e.bits = (e.bits & ~3ULL) | one;
    }
    if (obj->flags & 2) {
        e.bits = (e.bits & ~0xCULL) | 4;
    }
    s32 kindC = 9;
    if (sel != 0) {
        kindC = 8;
    }
    AddGifRegisterWrite(ctx, kindC, e.bits);
}

void ReadImageRecordB(void* a0, PaletteRecord* a1)
{
    ReadBufferedStreamBytes(a0, 12, a1);
    a1->f8 = D_00275718 + a1->f8;
    a1->fC = (u32)((a1->f4 << 2) + 15) >> 4;
}

void LoadImageRecordsB(void* self)
{
    s32 i;
    s32 count = ReadBufferedU16(self);
    g_imageRecordCountB = count;
    g_imageRecordsB = (PaletteRecord*)AllocateZeroedFrontMemory(count * 0x18);
    g_imageSlotsB = 0;
    for (i = 0; i < g_imageRecordCountB; i++) {
        ReadImageRecordB(self, &g_imageRecordsB[i]);
        if (g_imageRecordsB[i].f0 & 0x10000000) {
            g_imageSlotsB++;
        }
    }
    {
        s32 done = g_imageSlotsB;
        s32 left = g_imageRecordCountB - done;
        if (done < left) {
            g_imageSlotsB = left;
        }
    }
}

void ReadImageRecordA(void* self, ImageRecord* obj)
{
    ReadBufferedStreamBytes(self, 0x14, obj);
    s32 base = D_00275718;
    u32 bytes = obj->bytes;
    s32 off = obj->f10;
    obj->f14 = (bytes + 0xF) >> 4;
    obj->f10 = base + off;

}

void LoadImageRecordsA(void* self)
{
    s32 i;
    s32 count = ReadBufferedU16(self);
    g_imageRecordCountA = count;
    g_imageRecordsA = (ImageRecord*)AllocateZeroedFrontMemory(count * 0x20);
    g_imageSlotsA = 0;
    for (i = 0; i < g_imageRecordCountA; i++) {
        ReadImageRecordA(self, &g_imageRecordsA[i]);
        if (g_imageRecordsA[i].f4 & 0x10000000) {
            g_imageSlotsA++;
        }
    }
    {
        s32 done = g_imageSlotsA;
        s32 left = g_imageRecordCountA - done;
        if (done < left) {
            g_imageSlotsA = left;
        }
    }
}

void LoadFonts(BufferedStream* self)
{
    g_fontCount = ReadBufferedU16(self);
    g_fontRecords = new LoadedFont[g_fontCount];
    for (s32 i = 0; i < g_fontCount; i++) {
        LoadFont(&g_fontRecords[i], self);
        g_fontRecords[i].mask = 1 << i;
    }
    g_defaultFont = GetFontById(0);
}

void ReadTextureTable(void* self, TextureTable* o)
{
    ReadBufferedStreamBytes(self, 6, o);
    if (o->entryCount != 0) {
        o->entries = (void**)AllocateFrontMemory(o->entryCount * 4);
        for (s32 i = 0; i < o->entryCount; i++) {
            u16 idx = ReadBufferedU16(self);
            o->entries[i] = (void*)((u32)g_imageRecordsA + (idx << 5));
        }
    }
    if (o->cellCount != 0) {
        o->cells = (void**)AllocateFrontMemory(o->cellCount * 4);
        for (s32 i = 0; i < o->cellCount; i++) {
            u16 idx = ReadBufferedU16(self);
            if (idx == 0xFFFF) {
                o->cells[i] = 0;
            } else {
                o->cells[i] = (void*)((u32)g_imageRecordsB + idx * 0x18);
            }
        }
    }
}

void LoadScreenResources(void* self)
{
    s32 i;
    s32 j;
    AnimRecord* rec;
    CursorAnimator** out;
    BumpAllocator f;

    LoadImageRecordsB(self);
    LoadImageRecordsA(self);
    g_animRecordCount = ReadBufferedU16(self);
    g_animRecords = (AnimRecord*)AllocateZeroedFrontMemory(g_animRecordCount * 0x28);
    g_cursorAnimatorCount = ReadBufferedU16(self);
    g_cursorAnimators = (CursorAnimator**)AllocateZeroedFrontMemory(g_cursorAnimatorCount * 4);
    out = g_cursorAnimators;
    for (i = 0; i < g_animRecordCount; i++) {
        rec = &g_animRecords[i];
        ReadBufferedStreamBytes(self, 0x14, rec);
        rec->owner = ReadAnimator(self);
        if (rec->owner) {
            rec->owner->cursor.record = rec;
            *out++ = rec->owner;
        }
        rec->elems = (TextureTable*)AllocateZeroedFrontMemory(rec->nelem * 0x14);
        for (j = 0; j < rec->nelem; j++) {
            TextureTable* e = (TextureTable*)((u8*)rec->elems + j * 0x14);
            ReadTextureTable(self, e);
            e->record = rec;
        }
        rec->count = rec->elems->entryCount;
        switch (rec->kind) {
        case 0:
            rec->entCount = 3;
            break;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            rec->entCount = 1;
            break;
        case 4:
            rec->entCount = 4;
            break;
        }
        rec->ents = (AnimRecordEntry*)AllocateZeroedFrontMemory(rec->entCount * 8);
        AnimRecordEntry* arr = rec->ents;
        AnimRecordEntry* e;
        switch (rec->kind) {
        case 1:
        case 6:
        case 7:
        case 8:
        case 10:
            arr[0].type = 8;
            arr[0].addr = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            break;
        case 4: {
            s32 n = (rec->flags & 2) ? 3 : 0;
            n += 5;
            e = arr + 1;
            arr[0].type = n;
            arr[0].addr = (s32)AllocateZeroedFrontMemory((rec->count * arr[0].type) << 4);
            e->type = 5;
            e->addr = (s32)AllocateZeroedFrontMemory((rec->count * e->type) << 4);
            e = arr + 2;
            e->type = 7;
            e->addr = (s32)AllocateZeroedFrontMemory((rec->count * e->type) << 4);
            e = arr + 3;
            e->type = 4;
            e->addr = (s32)AllocateZeroedFrontMemory(rec->count << 6);
            break;
        }
        case 2:
        case 3:
            arr[0].type = 6;
            arr[0].addr = (s32)AllocateZeroedFrontMemory((rec->count * arr[0].type) << 4);
            break;
        case 0:
            e = arr + 1;
            arr[0].type = 8;
            arr[0].addr = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            e->type = 8;
            e->addr = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            e = arr + 2;
            e->type = 8;
            e->addr = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            break;
        case 5:
            arr[0].type = 7;
            arr[0].addr = (s32)AllocateZeroedFrontMemory((rec->count * arr[0].type) << 4);
            break;
        case 9:
            arr[0].type = 4;
            arr[0].addr = (s32)AllocateZeroedFrontMemory(0x40);
            break;
        }
    }
    LoadFonts(self);
    for (s32 k = 0; k < g_cursorAnimatorCount; k++) {
        g_cursorAnimators[k]->methods->bind(g_cursorAnimators[k]);
    }
    InitBumpAllocator(&f, 0x1E00, 0x4000);
    PlaceMaskedImages(0x10000000, &f, 0);
    BuildAnimRecordGifPackets(0x10000000);
    InitBumpAllocator(&g_bumpAllocator, f.next, 0x4000);
    UploadAllFontImages();
    InitScreenElements();
    for (s32 m = 0; m < 6; m++) {
        g_maskImageUploads[m] = UploadImagesByMask((1 << m) | 0x40000000);
    }
    g_maskedImagesPacket = BuildMaskedImagesPacket(0x20000000);
}

void SendResidentImages(void)
{
    s32 scratch[4];
    InitBumpAllocator(scratch, 0x1E00, 0x4000);
    SendMaskedImagesToGif(0x10000000, scratch);
    g_activeImageMask = 0;
}

void SwitchActiveImageMask(s32 self)
{
    FlushCursors();
    if (self != g_activeImageMask) {
        ResetBumpAllocator(&g_bumpAllocator);
        SendMaskedImagesToGif(self, (u8*)&g_bumpAllocator);
        BuildAnimRecordGifPackets(self);
        FlushMeshQueue();
        UpdateMatchingListedObjects(self);
        D_002626CC = 2;
        g_activeImageMask = self;
    }
}

void BuildAnimRecordGifPackets(s32 mask)
{
    PacketWriter buf;
    u8 col[4];
    s32 i;
    s32 j;
    AnimRecord* rec;
    AnimRecordEntry* ents;
    u64 test;
    u64 sel;

    if (mask == 0) {
        return;
    }
    for (i = 0; i < g_animRecordCount; i++) {
        rec = &g_animRecords[i];
        if ((rec->maskC & mask) != (u32)mask) {
            continue;
        }
        for (j = 0; j < rec->count; j++) {
            ents = rec->ents;
            switch (rec->kind) {
            case 1:
            case 6:
            case 7:
            case 8:
            case 10:
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x7C, 0, 3, 0x412, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                if (rec->kind == 10) {
                    AddGifRegisterWrite(&buf, 0x47, 0x53001);
                    AddGifRegisterWrite(&buf, 0x42, 0x11);
                } else if (rec->flags & 8) {
                    AddGifRegisterWrite(&buf, 0x47, 0x7001B);
                    AddGifRegisterWrite(&buf, 0x42, 0);
                } else if (rec->flags & 0x20) {
                    test = (rec->flags & 4) ? 0x13001 : 0x11001;
                    test |= (rec->kind != 1) ? 0x20000 : 0x60000;
                    AddGifRegisterWrite(&buf, 0x47, test);
                    AddGifRegisterWrite(&buf, 0x42, 0);
                } else if (rec->flags & 0x10) {
                    test = TEST_1B3510(1, (rec->kind == 1) ? 5 : 0, 0x7E, (rec->flags & 4) ? 3 : 1, 0, 0, 1, (rec->kind == 1) ? 3 : 1);
                    AddGifRegisterWrite(&buf, 0x47, test);
                    sel = (rec->flags & 1) ? 2 : 0;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(1, sel, 0, 0, 0));
                } else {
                    test = TEST_1B3510(1, (rec->kind == 1) ? 5 : 0, 0x7E, (rec->flags & 4) ? 3 : 1, 0, 0, 1, (rec->kind == 1) ? 3 : 1);
                    AddGifRegisterWrite(&buf, 0x47, test);
                    sel = (rec->flags & 1) ? 2 : 1;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                }
                AddGifRegisterWrite(&buf, 0x3D, g_camera->fogColor);
                SendTextureRegisters(rec->elems, j, 0, rec->kind, &buf);
                CloseDmaTag(&buf);
                break;
            case 4:
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                if (rec->flags & 2) {
                    ReserveGifPackedData(&buf, 0x7C, 0, 3, 0x412, 0);
                    BeginGifTag(&buf, 0, 1, 0xE);
                    AddGifRegisterWrite(&buf, 0x47, 0x71001);
                    sel = (rec->flags & 1) ? 2 : 1;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                    AddGifRegisterWrite(&buf, 0x3D, g_camera->fogColor);
                    SendTextureRegisters(rec->elems, j, 0, rec->kind, &buf);
                } else {
                    ReserveGifPackedData(&buf, 0x4C, 0, 3, 0x4FF, 0);
                    BeginGifTag(&buf, 0, 1, 0xE);
                    AddGifRegisterWrite(&buf, 0x47, 0x71001);
                    AddGifRegisterWrite(&buf, 0x42, 0x6A);
                    AddGifRegisterWrite(&buf, 1, 0x100000020);
                }
                ents++;
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ents++;
                ReserveGifPackedData(&buf, 0x4C, 0, 3, 0x4FF, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x47, 0x71001);
                AddGifRegisterWrite(&buf, 0x42, 0x6A);
                AddGifRegisterWrite(&buf, 1, 0x180002000);
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ents++;
                ReserveGifPackedData(&buf, 0x6C, 0, 3, 0x4FF, 0);
                BeginGifTag(&buf, 0, 5, 0x12EEE);
                AddGifRegisterWrite(&buf, 0x47, 0x75001);
                sel = (rec->flags & 1) ? 2 : 1;
                AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                AddGifRegisterWrite(&buf, 0x3D, g_camera->fogColor);
                AddGifStEntry(&buf, 0.0f, 0.0f, 1.0f);
                col[0] = (rec->color[0] + 1) >> 1;
                col[1] = (rec->color[1] + 1) >> 1;
                col[2] = (rec->color[2] + 1) >> 1;
                col[3] = (rec->color[3] + 1) >> 1;
                AddGifRgbaEntry(&buf, *(u32*)col);
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                if (rec->flags & 2) {
                    ReserveGifPackedData(&buf, 0x7D, 0, 3, 0x412, 0);
                } else {
                    ReserveGifPackedData(&buf, 0x4D, 0, 3, 0x4FF, 0);
                }
                ReserveGifPackedData(&buf, 0x6D, 0, 3, 0x4FF, 0);
                if (rec->flags & 2) {
                    ReserveGifPackedData(&buf, 0x5D, 0, 1, 4, 0);
                } else {
                    ReserveGifPackedData(&buf, 0x4D, 0, 1, 4, 0);
                }
                ReserveGifPackedData(&buf, 0x4D, 0, 1, 4, 0);
                CloseDmaTag(&buf);
                break;
            case 2:
            case 3:
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x47, 0x5F001);
                if (rec->kind == 2) {
                    AddGifRegisterWrite(&buf, 0x42, 0x44);
                } else {
                    AddGifRegisterWrite(&buf, 0x42, 0x49);
                }
                SendTextureRegisters(rec->elems, j, 0, rec->kind, &buf);
                CloseGifTag(&buf, 1);
                break;
            case 0: {
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x7C, 0, 4, 0x4F12, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                if (rec->flags & 8) {
                    AddGifRegisterWrite(&buf, 0x47, 0x70000);
                    AddGifRegisterWrite(&buf, 0x42, 0);
                } else {
                    AddGifRegisterWrite(&buf, 0x47, (rec->flags & 4) ? 0x737EB : 0x717EB);
                    sel = (rec->flags & 1) ? 2 : 1;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                }
                ents++;
                AddGifRegisterWrite(&buf, 0x3D, g_camera->fogColor);
                SendTextureRegisters(rec->elems, j, 0, rec->kind, &buf);
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x7C, 0, 4, 0x41F2, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x47, 0x53001);
                if (rec->flags & 8) {
                    AddGifRegisterWrite(&buf, 0x42, 0x8000000068);
                } else {
                    AddGifRegisterWrite(&buf, 0x42, 0x48);
                }
                ents++;
                AddGifRegisterWrite(&buf, 0x3D, 0);
                SendTextureRegisters(rec->elems, j, 1, rec->kind, &buf);
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x7C, 0, 4, 0x4F12, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x47, 0x53001);
                if (rec->flags & 8) {
                    AddGifRegisterWrite(&buf, 0x42, 0x8000000068);
                } else {
                    AddGifRegisterWrite(&buf, 0x42, 0x48);
                }
                AddGifRegisterWrite(&buf, 0x3D, 0);
                AnimRecord* found = (AnimRecord*)FindAnimRecord(rec->linkKey);
                if (found) {
                    SendTextureRegisters(found->elems, j, 0, rec->kind, &buf);
                } else {
                    SendTextureRegisters(rec->elems, j, 2, rec->kind, &buf);
                }
                CloseDmaTag(&buf);
                break;
            }
            case 5:
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x24C, 0, 3, 0x412, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x48, 0x31001);
                AddGifRegisterWrite(&buf, 0x43, 0x44);
                SendTextureRegisters(rec->elems, j, 0, rec->kind, &buf);
                CloseDmaTag(&buf);
                break;
            case 9:
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x4C, 0, 3, 0x41F, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x47, 0x51001);
                AddGifRegisterWrite(&buf, 0x42, 0x6A);
                CloseDmaTag(&buf);
                break;
            }
        }
    }
}

INCLUDE_ASM(func_001B40C8);

LINKER_REMNANT(func_001B4180);

ASM_FUNC(func_001B4188);

f32 RoundDown(f32 x);

// A value clamped to [lo, hi], as an inline function of its own: each clamp of ConvertHsvToRgb
// sets its 0 and 1 again.
static inline f32 ClampTo(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void ConvertHsvToRgb(Quad_001B4580* hsv, Quad_001B4580* rgb)
{
    f32 h;
    if (0.0f <= hsv->v[0]) {
        h = ClampTo(hsv->v[0], 0.0f, 360.0f);
    } else {
        h = -1.0f;
    }
    f32 s = ClampTo(hsv->v[1], 0.0f, 1.0f);
    f32 v = ClampTo(hsv->v[2], 0.0f, 1.0f);
    if (s == 0.0f) {
        Vu0::Q(*rgb) = Vu0::FromFloats(v, v, v);
        return;
    }
    if (h == 360.0f) h = 0.0f;
    h *= 0.016666668f;
    s32 i = (s32)RoundDown(h);
    f32 f = h - (f32)i;
    f32 p = v * (1.0f - s);
    f32 q = v * (1.0f - s * f);
    f32 t = v * (1.0f - s * (1.0f - f));
    switch (i) {
    case 0:
    case 6:
        Vu0::Q(*rgb) = Vu0::FromFloats(v, t, p);
        break;
    case 1:
        Vu0::Q(*rgb) = Vu0::FromFloats(q, v, p);
        break;
    case 2:
        Vu0::Q(*rgb) = Vu0::FromFloats(p, v, t);
        break;
    case 3:
        Vu0::Q(*rgb) = Vu0::FromFloats(p, q, v);
        break;
    case 4:
        Vu0::Q(*rgb) = Vu0::FromFloats(t, p, v);
        break;
    case 5:
        Vu0::Q(*rgb) = Vu0::FromFloats(v, p, q);
        break;
    }
}

void ConvertHsv255ToRgb255(Quad_001B4580* src, f32* dst)
{
    Quad_001B4580 tmp = *src;
    tmp.v[1] = tmp.v[1] * 0.003921569f;
    tmp.v[2] = tmp.v[2] * 0.003921569f;
    ConvertHsvToRgb(&tmp);
    dst[0] = dst[0] * 255.0f;
    dst[1] = dst[1] * 255.0f;
    dst[2] = dst[2] * 255.0f;
}

void ConvertRgbToHsv(Quad_001B4580* p, f32* dst);

void ConvertRgb255ToHsv255(Quad_001B4580* src, f32* dst)
{
    Quad_001B4580 tmp;
    Quad_001B4580 k;
    Vu0::Q(k) = Vu0::FromFloat(0.003921569f);
    Vu0::Q(tmp) = Vu0::MulX(Vu0::Q(*src), Vu0::Q(k));
    ConvertRgbToHsv(&tmp, dst);
    dst[1] = dst[1] * 255.0f;
    dst[2] = dst[2] * 255.0f;
}

LINKER_REMNANT(func_001B4670);

AnimRecord* FindAnimRecord(s32 key)
{
    if (key == -1) {
        return 0;
    }
    s32 i = 0;
    if (i < g_animRecordCount) {
        AnimRecord* p = g_animRecords;
        do {
            if (p->key == key) {
                return p;
            }
            i++;
            p++;
        } while (i < g_animRecordCount);
    }
    return 0;
}

void SetCursorFrame(AnimCursor* a0, s32 a1)
{
    if (a0->record != 0) {
        s32 hi = a0->record->count - 1;
        if (a1 < 0) {
            a1 = 0;
        } else {
            a1 = (hi < a1) ? hi : a1;
        }
        if (a0->frame != a1) {
            AnimCursor* n = a0->next;
            a0->frame = a1;
            if (n == 0) {
                if (a0 != g_lastPendingCursor) {
                    if (g_lastPendingCursor == 0) {
                        g_lastPendingCursor = a0;
                    }
                    a0->next = g_pendingCursors;
                    g_pendingCursors = a0;
                }
            }
        }
    }
}

void SetCursorCoords(AnimCursor* a0, f32 a, f32 b)
{
    if (a0->record == 0) return;
    if (a0->u == a && a0->v == b) return;
    a0->u = a;
    AnimCursor* v = a0->next;
    a0->v = b;
    if (v != 0) return;
    if (a0 == g_lastPendingCursor) return;
    if (g_lastPendingCursor == 0) g_lastPendingCursor = a0;
    a0->next = g_pendingCursors;
    g_pendingCursors = a0;
}

void FlushCursors(void)
{
    AnimCursor* n = g_pendingCursors;
    while (n != 0) {
        for (FrameLink* e = n->links; e != 0; e = e->next) {
            if (n->flags & 1) {
                e->dst->value = e->src->base + ((n->frame * e->src->stride) << 4);
            }
            SubmitMeshQueueEntry(e->dst);
        }
        AnimCursor* nx = n->next;
        n->next = 0;
        n = nx;
    }
    g_pendingCursors = 0;
    g_lastPendingCursor = 0;
}

void StepAnimators(f32 t)
{
    for (s32 i = 0; i < g_cursorAnimatorCount; i++) {
        CursorAnimator* o = g_cursorAnimators[i];
        if (ClaimAnimatorStep(o) != 0) {
            void (*fn)(CursorAnimator*, f32) = o->methods->step;
            if (fn != 0) {
                fn(o, t);
            }
        }
    }
}

s32 GetAnimatorSize(s32 k)
{
    switch (k) {
    case 1:
    case 2:
        return 0x4C;
    case 3:
    case 4:
        return 0x38;
    case 5:
        return 0x78;
    case 6:
        return 0x44;
    case 7:
        return 0x3C;
    case 8:
        return 0x50;
    }
    return 0;
}

void* GetAnimatorMethods(s32 n)
{
    switch (n) {
    case 1: return ((u8*)g_frameRunAnimatorMethods);
    case 2: return ((u8*)g_framePingPongAnimatorMethods);
    case 3: return ((u8*)g_randomJumpAnimatorMethods);
    case 4: return ((u8*)g_angleFrameAnimatorMethods);
    case 5: return g_crossfadeAnimatorMethods;
    case 6: return ((u8*)g_scrollAnimatorMethods);
    case 7: return ((u8*)g_circleAnimatorMethods);
    case 8: return ((u8*)g_triangleAnimatorMethods);
    }
    return 0;
}

CursorAnimator* ReadAnimator(void* a0)
{
    s32 type = ReadBufferedU16(a0);
    CursorAnimator* result = 0;
    if (type != 0) {
        CursorAnimator* o = (CursorAnimator*)AllocateZeroedFrontMemory(GetAnimatorSize(type));
        void* vt = GetAnimatorMethods(type);
        o->type = type;
        o->methods = (const CursorAnimatorMethods*)vt;
        u32 buf[8];
        ReadBufferedStreamBytes(a0, 0x1C, buf);
        o->methods->load(o, (AnimatorParams*)buf);
        result = o;
    }
    return result;
}

void LoadAnimatorBase(CursorAnimator* self, const AnimatorParams* src)
{
    s32 old = self->cursor.flags;
    self->recordKey = src->recordKey;
    self->cursor.flags = old | 1;
    if (src->flag != 0) {
        self->cursor.flags = old | 5;
    }
}

void BindAnimatorRecord(CursorAnimator* self)
{
    if (self->cursor.record == 0) {
        self->cursor.record = FindAnimRecord(self->recordKey);
    }
}

s32 ClaimAnimatorStep(CursorAnimator* a0)
{
    if (a0->stamp != g_gameTime) {
        a0->stamp = g_gameTime;
        return 1;
    }
    return 0;
}

f32 GetAnimatorZeroProgress(void)
{
    return 0.0f;
}

AnimCursor* FindAnimatorCursor(CursorAnimator* self, const AnimRecord* key)
{
    if (key->key == self->recordKey) {
        return &self->cursor;
    }
    return 0;
}

void LoadFrameRunAnimator(FrameRunAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

void BindFrameRunAnimator(FrameRunAnimator* p)
{
    BindAnimatorRecord(p);
    if (p->cursor.record != 0) {
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)p->cursor.record->count / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
}

void StepFrameRunAnimator(FrameRunAnimator* p, f32 dt)
{
    if (p->cursor.record == 0) {
        return;
    }
    if (p->cursor.record->count < 2) {
        return;
    }
    if (p->wait > 0.0f) {
        p->wait = p->wait - dt;
        return;
    }
    p->pos = p->pos + p->rate * dt;
    if ((f32)p->cursor.record->count <= p->pos) {
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)p->cursor.record->count / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
    f32 t = WrapModulo(p->pos, (f32)p->cursor.record->count);
    p->pos = t;
    SetCursorFrame(&p->cursor, (s32)t);
}

f32 GetFrameRunProgress(FrameRunAnimator* p)
{
    return (p->pos / p->rate) / ((f32)p->cursor.record->count / p->rate + p->wait0);
}

void LoadFramePingPongAnimator(FramePingPongAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

void BindFramePingPongAnimator(FramePingPongAnimator* p)
{
    BindAnimatorRecord(p);
    if (p->cursor.record != 0) {
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)(p->cursor.record->count * 2) / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
}

void StepFramePingPongAnimator(FramePingPongAnimator* p, f32 dt)
{
    AnimRecord* d = p->cursor.record;
    if (d == 0) return;
    if (d->count < 2) return;
    if (0.0f < p->wait) {
        p->wait = p->wait - dt;
        return;
    }
    f32 prod = p->rate * dt;
    f32 sum = p->pos + prod;
    p->pos = sum;
    if ((f32)d->count <= sum) {
        p->pos = sum - prod;
        p->rate = -p->rate;
    }
    if (p->pos < 0.0f) {
        p->pos = 0.0f;
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)(p->cursor.record->count * 2) / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
    SetCursorFrame(&p->cursor, (s32)p->pos);
}

f32 GetFramePingPongProgress(FramePingPongAnimator* p)
{
    f32 x = p->rate;
    f32 a;
    if (x < 0.0f) {
        x = -x;
        a = (f32)(p->cursor.record->count << 1) - p->pos;
    } else {
        a = p->pos;
    }
    return (a / x) / ((f32)(p->cursor.record->count << 1) / x + p->wait0);
}

void LoadRandomJumpAnimator(RandomJumpAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->waitMin = s->f4;
    p->waitMax = s->f8;
}

void StepRandomJumpAnimator(RandomJumpAnimator* self, f32 x)
{
    AnimRecord* p = self->cursor.record;
    if (p == 0)
        return;
    s32 count = p->count;
    if (count < 2)
        return;
    if (0.0f < self->wait) {
        self->wait = self->wait - x;
        return;
    }
    RandomRangeLow lo;
    lo.v = 1;
    s32 v = RandomIntInRange(lo, count - 1);
    s32 rem = (self->cursor.frame + v) % self->cursor.record->count;
    SetCursorFrame(&self->cursor, rem);
    self->wait = RandomFloatInRange(self->waitMin, self->waitMax);
}

void LoadAngleFrameAnimator(AngleFrameAnimator* self, AnimatorParams* key)
{
    LoadAnimatorBase(self, key);
    self->phase = key->f4;
    f32 d = (f32)(u32)key->i8;
    f32 q = 6.2831855f / d;
    self->sector = q;
    if (self->phase == 3.4028234663852886e+38f) {
        self->phase = RandomFloatInRange(0.0f, q);
    }
}

void BindAngleFrameAnimator(AngleFrameAnimator* p)
{
    BindAnimatorRecord(p);
    if (p->cursor.record != 0) {
        s32 n = p->cursor.record->count;
        if (n >= 2) {
            p->step = p->sector / (f32)n;
        }
    }
}

void FollowObjectAngle(AngleFrameAnimator* p, void* unused, DrawnPart* q)
{
    if (p->cursor.record == 0) {
        return;
    }
    if (p->cursor.record->count < 2) {
        return;
    }
    if (*(void**)q != (void*)DrawModelPart) {
        return;
    }
    FacingXY* vv;
    if (q->p78->i34 != 0) {
        vv = &q->vec;
    } else {
        vv = (FacingXY*)g_camera->g80;
    }
    f32 t = ArctangentOfRatio(vv->y, vv->x);
    f32 r = WrapModulo(p->phase - t, p->sector);
    s32 k = (s32)(r / p->step);
    SetCursorFrame(&p->cursor, k);
}

void LoadScrollAnimator(ScrollAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->velU = s->f4;
    p->velV = s->f8;
    p->wrapU = s->fC;
    p->wrapV = s->f10;
    p->mulV = 1.0f;
    p->mulU = 1.0f;
    p->cursor.flags = (p->cursor.flags & ~1) | 2;
}

void StepScrollAnimator(ScrollAnimator* p, f32 t)
{
    if (p->cursor.record != 0) {
        f32 r1 = FloatRemainder(p->cursor.u + p->velU * p->mulU * t, p->wrapU);
        f32 r2 = FloatRemainder(p->cursor.v + p->velV * p->mulV * t, p->wrapV);
        SetCursorCoords(&p->cursor, r1, r2);
    }
}

f32 GetScrollProgress(ScrollAnimator* p) { f32 result=0.0f; if (p->velU != 0.0f) result=(p->cursor.u/p->wrapU)*0.5f; else result=0.5f; if (p->velV != 0.0f) result += (p->cursor.v/p->wrapV)*0.5f; else result += 0.5f; return result; }

void SetScrollScale(ScrollAnimator* p, f32 a, f32 b)
{
    p->mulU = a;
    p->mulV = b;
}

void LoadCircleAnimator(CircleAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->omega = s->f4; p->radius = s->f8; p->centerU = s->fC; p->centerV = s->f10; p->cursor.flags = (p->cursor.flags & ~1) | 2;
}

void StepCircleAnimator(CircleAnimator* self)
{
    if (self->cursor.record != 0) {
        f32 t[2];
        f32 ang = WrapAngle(g_gameTime * self->omega);
        ComputeSinCos(ang, &t[0], &t[1]);
        t[0] = t[0] * self->radius + self->centerU;
        t[1] = t[1] * self->radius + self->centerV;
        SetCursorCoords(&self->cursor, t[0], t[1]);
    }
}

f32 GetCircleProgress(CircleAnimator* p)
{
    f32 a = WrapModulo(g_gameTime * p->omega, 6.2831855f);
    return a * 0.15915494f;
}

void LoadTriangleAnimator(TriangleAnimator* self, AnimatorParams* src)
{
    LoadAnimatorBase(self, src);
    s32 fl = self->cursor.flags;
    self->u0 = src->f4;
    self->v0 = src->f8;
    self->du1 = src->fC - src->f4;
    self->du2 = src->f10 - src->f4;
    self->dv1 = src->f14 - src->f8;
    f32 d = src->f18 - src->f8;
    self->cursor.flags = (fl & -2) | 2;
    self->dv2 = d;
}

void GetTriangleOutputs(TriangleAnimator* self, void** out) { out[0] = &self->out44; out[1] = &self->out4C; out[2] = &self->out48; }
