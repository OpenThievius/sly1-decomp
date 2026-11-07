// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "path_curve_object.h"
#include "cursor_animator.h"
#include "world.h"
#include "v24a0.h"
#include "v24a2.h"
#include "list_iter.h"
#include "shapes.h"
#include "globals.h"
#include "range_record.h"
#include "texture_table.h"
#include "bump_allocator.h"
#define TEST_1B3510(ate, atst, aref, afail, date, datm, zte, ztst) \
    ((u64)(ate) | ((u64)(atst) << 1) | ((u64)(aref) << 4) | ((u64)(afail) << 12) | ((u64)(date) << 14) | \
     ((u64)(datm) << 15) | ((u64)(zte) << 16) | ((u64)(ztst) << 17))
#define ALPHA_1B3510(a, b, c, d, fix) \
    ((u64)(a) | ((u64)(b) << 2) | ((u64)(c) << 4) | ((u64)(d) << 6) | ((u64)(fix) << 32))
#include "script_value.h"
#include "switched_collider.h"
#include "collider.h"
#include "state_graph.h"
#include "c54.h"
#include "attachment.h"
#include "state_walker.h"
#include "asm_func.h"

extern u32 D_00275718;
void func_00137A60(void* a, s32 b, void* c);
struct Bits_1B29E0 {
    u64 bits;
};
u64 func_001B2988(TextureTable* obj, s32 p1, s32 p2);
void func_00161708(void* ctx, s32 kind, u64 value);
void func_001F5C0C(void* p, s32 v, s32 n);
extern s32 D_00274508;
extern s32 D_00274514;
u16 func_00137BE0(void* self);
void* func_0018D5C0(s32 bytes);
void func_00137A60(void* self, s32 size, void* obj);
extern s32 D_00274500;
extern s32 D_00274510;
extern s32 D_00274518;
void func_00168D68(void* dst, s32 size, s32 align);
void func_001692B0(s32 a, void* b);
extern f32 D_0026185C;
struct Entry_1B2988 { u8 pad[0x18]; u64 tail; };
struct Cell_1B2988 { u8 pad[0x10]; u64 value; };
u32* func_0018D500(s32 bytes);
struct Obj_1B3488;
extern s32 D_002626CC;
void func_001B47C0(void);
void func_00168D78(Obj_1B3488* p);
void func_001692B0(Obj_1B3488* self, u8* arg);
void func_001B3510(Obj_1B3488* self);
void func_00169718(void);
void func_0013B430(Obj_1B3488* mask);
// EXACT (us)

struct Ent_1B3040 {
    s32 type;
    s32 data;
};
extern s32 D_002744F8;
extern AnimRecord* D_002744FC;
extern s32 D_0027453C;
extern CursorAnimator** D_00274540;
extern s32 D_00274520[];
extern s32 D_00274538;
void func_001B2BA8(void* self);
void func_001B2CF8(void* self);
void func_00137A60(void* self, s32 key, AnimRecord* out);
CursorAnimator* func_001B4A10(void* self);
void func_001B2F00(void* self, TextureTable* e);
void func_001B2DF8(void* self);
void func_00168D68(BumpAllocator* p, s32 a, s32 b);
s32 func_001690C0(s32 mask, BumpAllocator* arg, s32 f);
void func_001B3510(s32 mask);
void func_0015E5F0(void);
void func_001A9F78(void);
s32 func_00169780(s32 mask);
s32 func_001693A8(s32 mask);
struct Ent_1B3510 {
    s32 type;
    Quad4* data;
};
struct Glob_1B3510 {
    u8 pad0[0x204];
    u32 f204;
};
void* func_001611B8(V24A0* b);
void func_001529C8(V24A0* b, s32 n, Quad4* q);
void func_001612F8(V24A0* b, s32 a, s32 c, s32 d, s32 e, s32 f);
void func_001613C0(V24A0* b, s32 a, s32 c, u64 d);
void func_00161708(V24A0* b, s32 reg, u64 v);
void func_001B29E0(TextureTable* e, s32 j, s32 pass, s32 kind, V24A0* b);
void func_00152D70(V24A0* b);
void func_001528C8(V24A0* b);
void func_00161278(V24A0* b, s32 n);
void func_00161520(V24A0* b, f32 x, f32 y, f32 z);
void func_00161458(V24A0* b, u32 c);
struct Ctx_1B2DF8;
extern u8 D_0024A220[];
void* func_001FD8A8(s32 size);
struct Ent_1B2DF8 {
    u8 pad00[0x4C];
    void* p4c;
    u8 pad50[0x30];
    s32 v80;
    u8 pad84[0x04];

    Ent_1B2DF8() { p4c = g_fontMethods; }
    void* operator new[](__SIZE_TYPE__ size) { return func_001FD8A8(size); }
};
extern s32 D_00262260;
extern Ent_1B2DF8* D_00262264;
extern s32 D_0026227C;
s32 func_00137BE0(Ctx_1B2DF8* src);
void func_0015D8A8(Ent_1B2DF8* e, Ctx_1B2DF8* self);
s32 func_0015C1C0(s32 n);
void func_001B46E0(s32 a, s32 frame);
void func_001B4AA0(CursorAnimator* self, const AnimatorParams* src);
void func_001B4AD0(CursorAnimator* self);
void func_001B46E0(AnimCursor* cur, s32 idx);
void func_001B4750(AnimCursor* cur, f32 x, f32 y);
AnimRecord* func_001B4688(s32 key);
extern AnimCursor* D_00274544;
extern AnimCursor* D_0027451C;
f32 func_001EAAE0(f32 a, f32 b);
struct Vec2_1B5160 { f32 x; f32 y; };
struct Inner_1B5160 { u8 pad0[0x34]; s32 i34; };
struct Other_1B5160 {
    void* vt; u8 pad0[0xC]; Vec2_1B5160 vec; u8 pad1[0x60]; Inner_1B5160* p78;
};
extern u8 func_00166690[];
f32 func_00205778(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);
f32 func_002058A0(f32 a, f32 b);
void func_001694A0(void* p);
s32 func_001B4B08(CursorAnimator* p);
s32 func_001B4920(s32 type);
void* func_0018D5C0(s32 size);
void* func_001B4980(s32 type);
void func_00137A60(void* owner, s32 key, void* out);
void func_001F5C0C(void* p, int zero, s32 count);
struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };
void func_001B4330(Quad_001B4580* p);
f32 func_001EA408(f32 a);
void func_001EAD88(f32 angle, f32* a, f32* b);
f32 func_001EAFE0(f32 x, f32 y);
// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0021E358[];
extern const Fn_Table D_0021E378[];
extern const Fn_Table D_0021E398[];
extern const Fn_Table D_0021E3B8[];
extern u8 D_0021E438[];
extern const Fn_Table D_0021E3D8[];
extern const Fn_Table D_0021E3F8[];
extern const Fn_Table D_0021E418[];
struct Lo_1B4FC0 { s32 v; };
s32 func_001EAA70(Lo_1B4FC0 lo, s32 hi);

// The file's .data, in retail's order.
s32 D_002744F8 = 0;
AnimRecord* D_002744FC = 0;
s32 D_00274500 = 0;
V24A2_ImgA* D_00274504 = 0;
s32 D_00274508 = 0;
V24A2_ImgB* D_0027450C = 0;
s32 D_00274510 = 0;
s32 D_00274514 = 0;
s32 D_00274518 = 0;
AnimCursor* D_0027451C = 0;
s32 D_00274520[6] = {0};
s32 D_00274538 = 0;
s32 D_0027453C = 0;
CursorAnimator** D_00274540 = 0;
AnimCursor* D_00274544 = 0;

u64 func_001B2988(TextureTable* t, s32 i, s32 j)
{
    Entry_1B2988* e = ((Entry_1B2988**)t->entries)[i];
    s32 stride = 1;
    if (t->record->kind == 0) stride = 3;
    Cell_1B2988* c = ((Cell_1B2988**)t->cells)[i * stride + j];
    u64 r = e->tail;
    if (c != 0) r |= c->value;
    return r;
}

void func_001B29E0(TextureTable* obj, s32 p1, s32 p2, s32 flag, void* ctx)
{
    Bits_1B29E0 a;
    Bits_1B29E0 b;
    Bits_1B29E0 c;
    Bits_1B29E0 d;
    Bits_1B29E0 e;
    s32 sel = flag ^ 5;
    u64 one = 1;

    func_001F5C0C(&a, 0, 8);
    func_001F5C0C(&b, 0, 8);
    func_001F5C0C(&c, 0, 8);
    func_001F5C0C(&d, 0, 8);
    func_001F5C0C(&e, 0, 8);

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

void func_001B2B50(void* a0, V24A2_ImgB* a1)
{
    ReadBufferedStreamBytes(a0, 12, a1);
    a1->f8 = D_00275718 + a1->f8;
    a1->fC = (u32)((a1->f4 << 2) + 15) >> 4;
}

void func_001B2BA8(void* self)
{
    s32 i;
    s32 count = ReadBufferedU16(self);
    g_imageRecordCountB = count;
    g_imageRecordsB = (V24A2_ImgB*)AllocateZeroedFrontMemory(count * 0x18);
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

void func_001B2CA8(void* self, V24A2_ImgA* obj)
{
    ReadBufferedStreamBytes(self, 0x14, obj);
    s32 base = D_00275718;
    u32 bytes = obj->bytes;
    s32 off = obj->f10;
    obj->f14 = (bytes + 0xF) >> 4;
    obj->f10 = base + off;

}

void func_001B2CF8(void* self)
{
    s32 i;
    s32 count = ReadBufferedU16(self);
    g_imageRecordCountA = count;
    g_imageRecordsA = (V24A2_ImgA*)AllocateZeroedFrontMemory(count * 0x20);
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

void func_001B2DF8(Ctx_1B2DF8* self)
{
    g_fontCount = ReadBufferedU16(self);
    g_fontRecords = new Ent_1B2DF8[g_fontCount];
    for (s32 i = 0; i < g_fontCount; i++) {
        LoadFont(&g_fontRecords[i], self);
        g_fontRecords[i].v80 = 1 << i;
    }
    g_defaultFont = GetFontById(0);
}

void func_001B2F00(void* self, TextureTable* o)
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

void func_001B3040(void* self)
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
        rec->ents = AllocateZeroedFrontMemory(rec->entCount * 8);
        Ent_1B3040* arr = (Ent_1B3040*)rec->ents;
        Ent_1B3040* e;
        switch (rec->kind) {
        case 1:
        case 6:
        case 7:
        case 8:
        case 10:
            arr[0].type = 8;
            arr[0].data = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            break;
        case 4: {
            s32 n = (rec->flags & 2) ? 3 : 0;
            n += 5;
            e = arr + 1;
            arr[0].type = n;
            arr[0].data = (s32)AllocateZeroedFrontMemory((rec->count * arr[0].type) << 4);
            e->type = 5;
            e->data = (s32)AllocateZeroedFrontMemory((rec->count * e->type) << 4);
            e = arr + 2;
            e->type = 7;
            e->data = (s32)AllocateZeroedFrontMemory((rec->count * e->type) << 4);
            e = arr + 3;
            e->type = 4;
            e->data = (s32)AllocateZeroedFrontMemory(rec->count << 6);
            break;
        }
        case 2:
        case 3:
            arr[0].type = 6;
            arr[0].data = (s32)AllocateZeroedFrontMemory((rec->count * arr[0].type) << 4);
            break;
        case 0:
            e = arr + 1;
            arr[0].type = 8;
            arr[0].data = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            e->type = 8;
            e->data = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            e = arr + 2;
            e->type = 8;
            e->data = (s32)AllocateZeroedFrontMemory(rec->count << 7);
            break;
        case 5:
            arr[0].type = 7;
            arr[0].data = (s32)AllocateZeroedFrontMemory((rec->count * arr[0].type) << 4);
            break;
        case 9:
            arr[0].type = 4;
            arr[0].data = (s32)AllocateZeroedFrontMemory(0x40);
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

void func_001B3450(void)
{
    s32 scratch[4];
    InitBumpAllocator(scratch, 0x1E00, 0x4000);
    SendMaskedImagesToGif(0x10000000, scratch);
    g_activeImageMask = 0;
}

void func_001B3488(Obj_1B3488* self)
{
    FlushCursors();
    if ((s32)self != g_activeImageMask) {
        ResetBumpAllocator((Obj_1B3488*)&g_bumpAllocator);
        SendMaskedImagesToGif(self, (u8*)&g_bumpAllocator);
        BuildAnimRecordGifPackets(self);
        FlushMeshQueue();
        UpdateMatchingListedObjects(self);
        D_002626CC = 2;
        g_activeImageMask = (s32)self;
    }
}

void func_001B3510(s32 mask)
{
    V24A0 buf;
    u8 col[4];
    s32 i;
    s32 j;
    AnimRecord* rec;
    Ent_1B3510* ents;
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
            ents = (Ent_1B3510*)rec->ents;
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
                AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
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
                    AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
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
                AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
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
                AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
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

INCLUDE_RODATA(jtbl_0024D200);
ASM_FUNC(func_001B4330);

void func_001B4580(Quad_001B4580* src, f32* dst)
{
    Quad_001B4580 tmp = *src;
    tmp.v[1] = tmp.v[1] * 0.003921569f;
    tmp.v[2] = tmp.v[2] * 0.003921569f;
    ConvertHsvToRgb(&tmp);
    dst[0] = dst[0] * 255.0f;
    dst[1] = dst[1] * 255.0f;
    dst[2] = dst[2] * 255.0f;
}

ASM_FUNC(func_001B4600);

LINKER_REMNANT(func_001B4670);

AnimRecord* func_001B4688(s32 key)
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

void func_001B46E0(AnimCursor* a0, s32 a1)
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

void func_001B4750(AnimCursor* a0, f32 a, f32 b)
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

void func_001B47C0(void)
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

void func_001B4878(f32 t)
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

s32 func_001B4920(s32 k)
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

void* func_001B4980(s32 n)
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

CursorAnimator* func_001B4A10(void* a0)
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

void func_001B4AA0(CursorAnimator* self, const AnimatorParams* src)
{
    s32 old = self->cursor.flags;
    self->recordKey = src->recordKey;
    self->cursor.flags = old | 1;
    if (src->flag != 0) {
        self->cursor.flags = old | 5;
    }
}

void func_001B4AD0(CursorAnimator* self)
{
    if (self->cursor.record == 0) {
        self->cursor.record = FindAnimRecord(self->recordKey);
    }
}

s32 func_001B4B08(CursorAnimator* a0)
{
    if (a0->stamp != g_gameTime) {
        a0->stamp = g_gameTime;
        return 1;
    }
    return 0;
}

f32 func_001B4B38(void)
{
    return 0.0f;
}

AnimCursor* func_001B4B48(CursorAnimator* self, const AnimRecord* key)
{
    if (key->key == self->recordKey) {
        return &self->cursor;
    }
    return 0;
}

void func_001B4B68(FrameRunAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

void func_001B4BC8(FrameRunAnimator* p)
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

void func_001B4C30(FrameRunAnimator* p, f32 dt)
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

f32 func_001B4D18(FrameRunAnimator* p)
{
    return (p->pos / p->rate) / ((f32)p->cursor.record->count / p->rate + p->wait0);
}

void func_001B4D48(FramePingPongAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

void func_001B4DA8(FramePingPongAnimator* p)
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

void func_001B4E18(FramePingPongAnimator* p, f32 dt)
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

f32 func_001B4F18(FramePingPongAnimator* p)
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

void func_001B4F80(RandomJumpAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->waitMin = s->f4;
    p->waitMax = s->f8;
}

void func_001B4FC0(RandomJumpAnimator* self, f32 x)
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
    Lo_1B4FC0 lo;
    lo.v = 1;
    s32 v = RandomIntInRange(lo, count - 1);
    s32 rem = (self->cursor.frame + v) % self->cursor.record->count;
    SetCursorFrame(&self->cursor, rem);
    self->wait = RandomFloatInRange(self->waitMin, self->waitMax);
}

void func_001B5060(AngleFrameAnimator* self, AnimatorParams* key)
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

void func_001B5108(AngleFrameAnimator* p)
{
    BindAnimatorRecord(p);
    if (p->cursor.record != 0) {
        s32 n = p->cursor.record->count;
        if (n >= 2) {
            p->step = p->sector / (f32)n;
        }
    }
}

void func_001B5160(AngleFrameAnimator* p, void* unused, Other_1B5160* q)
{
    if (p->cursor.record == 0) {
        return;
    }
    if (p->cursor.record->count < 2) {
        return;
    }
    if (*(void**)q != (void*)func_00166690) {
        return;
    }
    Vec2_1B5160* vv;
    if (q->p78->i34 != 0) {
        vv = &q->vec;
    } else {
        vv = (Vec2_1B5160*)g_camera->g80;
    }
    f32 t = func_00205778(vv->y, vv->x);
    f32 r = WrapModulo(p->phase - t, p->sector);
    s32 k = (s32)(r / p->step);
    SetCursorFrame(&p->cursor, k);
}

void func_001B5200(ScrollAnimator* p, AnimatorParams* s)
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

void func_001B5278(ScrollAnimator* p, f32 t)
{
    if (p->cursor.record != 0) {
        f32 r1 = func_002058A0(p->cursor.u + p->velU * p->mulU * t, p->wrapU);
        f32 r2 = func_002058A0(p->cursor.v + p->velV * p->mulV * t, p->wrapV);
        SetCursorCoords(&p->cursor, r1, r2);
    }
}

f32 func_001B5308(ScrollAnimator* p) { f32 result=0.0f; if (p->velU != 0.0f) result=(p->cursor.u/p->wrapU)*0.5f; else result=0.5f; if (p->velV != 0.0f) result += (p->cursor.v/p->wrapV)*0.5f; else result += 0.5f; return result; }

void func_001B5388(ScrollAnimator* p, f32 a, f32 b)
{
    p->mulU = a;
    p->mulV = b;
}

void func_001B5398(CircleAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->omega = s->f4; p->radius = s->f8; p->centerU = s->fC; p->centerV = s->f10; p->cursor.flags = (p->cursor.flags & ~1) | 2;
}

void func_001B5400(CircleAnimator* self)
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

f32 func_001B5488(CircleAnimator* p)
{
    f32 a = WrapModulo(g_gameTime * p->omega, 6.2831855f);
    return a * 0.15915494f;
}

void func_001B54D0(TriangleAnimator* self, AnimatorParams* src)
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

void func_001B5568(TriangleAnimator* self, void** out) { out[0] = &self->out44; out[1] = &self->out4C; out[2] = &self->out48; }
