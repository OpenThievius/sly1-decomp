// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c6e.h"
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

typedef void (*VFn_1B0F70)(void* self, s32 arg);

void func_001B1BF0(RangeRecord* o);

void func_001B1DA8(RangeRecord* o, f32 v)
{
    o->f08 = v;
    if (o->f04 < 0.0f) {
        o->f04 = v;
    }
    func_001B1BF0(o);
}

struct Obj_1B2118 {
    u8 pad_0[0x410];
    u32 f410;
    u8 pad_414[0x538 - 0x414];
    u64 f538;
};

s32 func_001B2118(void* unused, Obj_1B2118* o)
{
    s32 r = 0;
    if ((o->f538 & (1UL << 43)) == 0) {
        r = o->f410 != 0;
    }
    return r;
}


extern u32 D_00275718;
void func_00137A60(void* a, s32 b, void* c);

void func_001B2B50(void* a0, V24A2_ImgB* a1)
{
    ReadBufferedStreamBytes(a0, 12, a1);
    a1->f8 = D_00275718 + a1->f8;
    a1->fC = (u32)((a1->f4 << 2) + 15) >> 4;
}

struct Bits_1B29E0 {
    u64 bits;
};

u64 func_001B2988(TextureTable* obj, s32 p1, s32 p2);
void func_00161708(void* ctx, s32 kind, u64 value);
void func_001F5C0C(void* p, s32 v, s32 n);

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

extern s32 D_00274508;
extern s32 D_00274514;

u16 func_00137BE0(void* self);
void* func_0018D5C0(s32 bytes);

void func_001B2BA8(void* self)
{
    s32 i;
    s32 count = ReadBufferedU16(self);
    g_imageRecordCountB = count;
    g_imageRecordsB = (V24A2_ImgB*)AllocateZeroedFrontMemory(count * 0x18);
    D_00274514 = 0;
    for (i = 0; i < g_imageRecordCountB; i++) {
        func_001B2B50(self, &g_imageRecordsB[i]);
        if (g_imageRecordsB[i].f0 & 0x10000000) {
            D_00274514++;
        }
    }
    {
        s32 done = D_00274514;
        s32 left = g_imageRecordCountB - done;
        if (done < left) {
            D_00274514 = left;
        }
    }
}

void func_00137A60(void* self, s32 size, void* obj);

void func_001B2CA8(void* self, V24A2_ImgA* obj)
{
    ReadBufferedStreamBytes(self, 0x14, obj);
    s32 base = D_00275718;
    u32 bytes = obj->bytes;
    s32 off = obj->f10;
    obj->f14 = (bytes + 0xF) >> 4;
    obj->f10 = base + off;

}

extern s32 D_00274500;
extern s32 D_00274510;

u16 func_00137BE0(void* self);
void* func_0018D5C0(s32 bytes);

void func_001B2CF8(void* self)
{
    s32 i;
    s32 count = ReadBufferedU16(self);
    g_imageRecordCountA = count;
    g_imageRecordsA = (V24A2_ImgA*)AllocateZeroedFrontMemory(count * 0x20);
    D_00274510 = 0;
    for (i = 0; i < g_imageRecordCountA; i++) {
        func_001B2CA8(self, &g_imageRecordsA[i]);
        if (g_imageRecordsA[i].f4 & 0x10000000) {
            D_00274510++;
        }
    }
    {
        s32 done = D_00274510;
        s32 left = g_imageRecordCountA - done;
        if (done < left) {
            D_00274510 = left;
        }
    }
}

extern s32 D_00274518;

void func_00168D68(void* dst, s32 size, s32 align);
void func_001692B0(s32 a, void* b);

void func_001B3450(void)
{
    s32 scratch[4];
    InitBumpAllocator(scratch, 0x1E00, 0x4000);
    SendMaskedImagesToGif(0x10000000, scratch);
    D_00274518 = 0;
}

void func_00124A48(void* self);

typedef void (*VFn_1B11A0)(void* self, s32 arg);

typedef void (*VFn_1B15D0)(void* self, s32 arg);

extern f32 D_0026185C;

typedef void (*VFn_1B1608)(void* self, s32 arg);

extern s32 D_002626D0;
extern u8 D_0027DC20[];

void func_001B1CF8(RangeRecord* self, s32 code);
s32 func_001B1D38(RangeRecord* self);
void func_001B1D70(RangeRecord* self, f32 v);
void func_001B1DA8(RangeRecord* self, f32 v);
void func_001F5C0C(void* p, s32 v, s32 n);

struct Hdr_1B1B38 {
    u8 pad0[0xC];
    s32 f0C;
};

void func_001B1B38(RangeRecord* self)
{
    if (self->link == 0) {
        func_001B1CF8(self, 0x2C);
    }
    if (func_001B1D38(self) == 0) {
        func_001B1D70(self, 100.0f);
        func_001B1DA8(self, 400.0f);
    }
    if ((((Hdr_1B1B38*)self->link)->f0C & 0x10000000) == 0) {
        s32 idx = g_meshQueueCount;
        if (idx < 0x4000) {
            u8* p = D_0027DC20 + idx * 16;
            self->f2D0 = p;
            g_meshQueueCount = idx + 1;
            func_001F5C0C(p, 0, 16);
        }
    }
}

void func_001B1BF0(RangeRecord* self)
{
    self->fC0 = 0;
}

void* func_001B4688(s32 key);
void func_001B1CF8(RangeRecord* self, s32 key)
{
    void* found = FindAnimRecord(key != -1 ? key : 0x2C);
    self->link = found;
    if (found)
        func_001B1BF0(self);
}

s32 func_001B1D38(RangeRecord* p)
{
    s32 r = 0;
    if (0.0f <= p->f04 && 0.0f <= p->f08)
        r = 1;
    return r;
}

void func_001B1D70(RangeRecord* p, f32 v)
{
    p->f04 = v;
    if (p->f08 < 0.0f)
        p->f08 = v;
    func_001B1BF0(p);
}

typedef void (*VFn_1B00E8)(void* self, s32 arg);

void func_001AECB0(void* self);

struct Entry_1B2988 { u8 pad[0x18]; u64 tail; };
struct Cell_1B2988 { u8 pad[0x10]; u64 value; };
u64 func_001B2988(TextureTable* t, s32 i, s32 j)
{
    Entry_1B2988* e = ((Entry_1B2988**)t->entries)[i];
    s32 stride = 1;
    if (*t->singleCell == 0) stride = 3;
    Cell_1B2988* c = ((Cell_1B2988**)t->cells)[i * stride + j];
    u64 r = e->tail;
    if (c != 0) r |= c->value;
    return r;
}

typedef void (*VFn_1B0160)(void* self, s32 arg);

void func_001B1BF8(RangeRecord* o);

void func_001B1FB0(RangeRecord* o, f32 v)
{
    o->f40 = v;
    func_001B1BF8(o);
    func_001B1BF0(o);
}

void func_001B1FE0(RangeRecord* o, f32 v)
{
    o->f44 = v;
    func_001B1BF8(o);
    func_001B1BF0(o);
}

typedef void (*VFn_1B0EA8)(void* self, s32 arg);

s32 func_00137B90(void* src);
T2176* func_0014D9A8(s32 kind);
void func_0011EC40(void* self, void* obj);

void func_001B2840(C6E* self, void* obj)
{
    T2176* p = CreatePathCurve(ReadBufferedU8(obj));
    self->curve = p;
    void (*fn)(T2176* self, void* stream) = p->vt->m00;
    if (fn != 0) {
        fn(p, obj);
    }
    ReadPropertyRecords(self, obj);
}

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

typedef void (*VFn_1B04D0)(void* self, s32 v);

typedef void (*VFn_1B0EE0)(void* self, s32 arg);

extern f32 D_0026185C;

struct Sub_1B2640 {
    u8 pad0[0xC];
    s32 f0C;
};

struct Obj_1B2640 {
    Sub_1B2640* f0;
    u8 pad4[0xBC];
    s32 fC0;
    u8 padC4[0xC];
};


void func_001B2358(void* o);

void func_001B2640(Obj_1B2640* o)
{
    if (o->f0 != 0) {
        Camera* c = g_camera;
        s32 bits = o->f0->f0C;
        s32 need = c->f21C;
        s32 a2 = 0;
        if ((bits & 0x10000000) != 0) {
            goto set;
        }
        if ((need & bits) != need) {
            goto skip;
        }
    set:
        a2 = 1;
    skip:
        if (a2 != 0) {
            if (o->fC0 == 0) {
                func_001B2358(o);
                if (o->fC0 == 0) {
                    goto done;
                }
            }
            V24A0* g = &g_vifPacketWriter;
            u64 hi = (u64)(u32)((u8*)o + 0xD0) << 32;
            u64 v = (u64)(s64)(o->fC0 | 0x40000000) | hi;
            *(u64*)g->cur = v;
            g->cur = g->cur + 0x10;
        }
    }
done:
    ;
}

void func_001B2068(RangeRecord* self, Quad16* src)
{
    *(Quad16*)((u8*)self + 0x30) = *src;
    func_001B1BF0(self);
}

struct Node_1B2790;
struct Node_1B2790 { u8 pad[0xB8]; Node_1B2790* next; };

s32 func_001B26F8(Node_1B2790* node, void* a1, f32 f);

void func_001B2790(World* self, void* a1, s32 max, s32* outCount, Node_1B2790** out, f32 f)
{
    ListFrame frame;
    s32 count = 0;
    Node_1B2790* node;
    for (node = (Node_1B2790*)self->list1C00.head; node != 0; node = node->next) {
        if (func_001B26F8(node, a1, f) == 0) {
            continue;
        }
        if (count < max) {
            *out = node;
            out++;
            count++;
        } else {
            break;
        }
    }
    *outCount = count;
}

typedef void (*VFn_1B0120)(void* self, s32 arg);

struct Obj_1B2090 {
    u8 kind_0;
    u8 pad_1[0xB];
    u32 flags_C;
};

s32 func_001B2090(Obj_1B2090** self, u32 bits)
{
    s32 r = 0;
    if (*self != 0) {
        u32 flags = (*self)->flags_C;
        Camera* g = g_camera;
        u32 mask = g->f21C;
        s32 ok = 0;
        if ((flags & 0x10000000) != 0 || (mask & flags) == mask) {
            ok = 1;
        }
        if (ok != 0) {
            if (((bits & 1) != 0 && (*self)->kind_0 == 2) || ((bits & 2) != 0 && (*self)->kind_0 == 3)) {
                r = 1;
            }
        }
    }
    return r;
}

struct Obj_1B2F00 {
    u8 pad0[4];
    u8 countA;
    u8 countB;
    u8 pad6[6];
    u32* ptrC;
    u32* ptr10;
};

void func_00137A60(void* self, s32 size, void* obj);
u32* func_0018D500(s32 bytes);

void func_001B2F00(void* self, Obj_1B2F00* o)
{
    ReadBufferedStreamBytes(self, 6, o);
    if (o->countA != 0) {
        o->ptrC = AllocateFrontMemory(o->countA * 4);
        for (s32 i = 0; i < o->countA; i++) {
            u16 idx = ReadBufferedU16(self);
            o->ptrC[i] = (u32)g_imageRecordsA + (idx << 5);
        }
    }
    if (o->countB != 0) {
        o->ptr10 = AllocateFrontMemory(o->countB * 4);
        for (s32 i = 0; i < o->countB; i++) {
            u16 idx = ReadBufferedU16(self);
            if (idx == 0xFFFF) {
                o->ptr10[i] = 0;
            } else {
                o->ptr10[i] = (u32)g_imageRecordsB + idx * 0x18;
            }
        }
    }
}

s32 func_001925F0(void);
s32 func_001AEE50(void* self, void* other);

// Matched by a switch on f558 (cases 1 and 5).

typedef void (*VFn_1B1698)(void* self, s32 arg);

f32 func_002054F0(RangeRecord* o, f32 s);

void func_001B2010(RangeRecord* o, f32 s) {
    f32 t = func_002054F0(o, s * 0.00872664712f);
    o->f04 = t * o->f40;
    o->f08 = t * o->f44;
    func_001B1BF0(o);
}

struct Obj_1B3488;

extern s32 D_00274518;
extern s32 D_002626CC;

void func_001B47C0(void);
void func_00168D78(Obj_1B3488* p);
void func_001692B0(Obj_1B3488* self, u8* arg);
void func_001B3510(Obj_1B3488* self);
void func_00169718(void);
void func_0013B430(Obj_1B3488* mask);

void func_001B3488(Obj_1B3488* self)
{
    FlushCursors();
    if ((s32)self != D_00274518) {
        ResetBumpAllocator((Obj_1B3488*)&g_bumpAllocator);
        SendMaskedImagesToGif(self, (u8*)&g_bumpAllocator);
        BuildAnimRecordGifPackets(self);
        FlushMeshQueue();
        UpdateMatchingListedObjects(self);
        D_002626CC = 2;
        D_00274518 = (s32)self;
    }
}

extern u8 D_00248400[];

void func_00188B08(void* a, void* b, Mat4A* dst);
void func_00182F78(BaseObject* self, void* other);

void func_001B28A8(C6E* self, BaseObject* other)
{
    Mat4A a;
    Mat4A b;
    T2176* h;
    if (self->parent) {
        BuildMatrixFromRotationAndTranslation((u8*)self->parent + 0x140, (u8*)self->parent + 0x110, &a);
    } else {
        a = *(Mat4A*)D_00248400;
    }
    if (other) {
        BuildMatrixFromRotationAndTranslation((u8*)other + 0x140, (u8*)other + 0x110, &b);
    } else {
        b = *(Mat4A*)D_00248400;
    }
    h = self->curve;
    if (h->vt->m04) {
        h->vt->m04(h, &a, &b);
    }
    ReparentObject(self, other);
}

extern s32 D_002744D0;
void func_001BF788(s32 a, s32 n);
void func_00155F90(s32 p);

struct Tgt_1B1710;
void func_001BF788(Tgt_1B1710* t, s32 n);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

extern f32 D_0026185C;

extern f32 D_0026185C;

// NEAR: float regs: case 0 wants t=$f4 zero=$f2 m=$f3; ours t=$f3 zero=$f4 m=$f2 (8 lines differ); delay-slot load of m fixed via local m

extern f32 D_0026185C;

// EXACT (us)

struct Ent_1B3040 {
    s32 type;
    s32 data;
};
struct Elem_1B3040 {
    u8 pad0[4];
    u8 f4;
    u8 pad5[3];
    AnimRecord* f8;
    u8 pad0C[8];
};
extern s32 D_002744F8;
extern AnimRecord* D_002744FC;
extern s32 D_0027453C;
extern CursorAnimator** D_00274540;
extern s32 D_00274520[];
extern s32 D_00274538;

void func_001B2BA8(void* self);
void func_001B2CF8(void* self);
void* func_0018D5C0(s32 bytes);
void func_00137A60(void* self, s32 key, AnimRecord* out);
CursorAnimator* func_001B4A10(void* self);
void func_001B2F00(void* self, Elem_1B3040* e);
void func_001B2DF8(void* self);
void func_00168D68(BumpAllocator* p, s32 a, s32 b);
s32 func_001690C0(s32 mask, BumpAllocator* arg, s32 f);
void func_001B3510(s32 mask);
void func_0015E5F0(void);
void func_001A9F78(void);
s32 func_00169780(s32 mask);
s32 func_001693A8(s32 mask);

void func_001B3040(void* self)
{
    s32 i;
    s32 j;
    AnimRecord* rec;
    CursorAnimator** out;
    BumpAllocator f;

    func_001B2BA8(self);
    func_001B2CF8(self);
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
        rec->elems = AllocateZeroedFrontMemory(rec->nelem * 0x14);
        for (j = 0; j < rec->nelem; j++) {
            Elem_1B3040* e = (Elem_1B3040*)((u8*)rec->elems + j * 0x14);
            func_001B2F00(self, e);
            e->f8 = rec;
        }
        rec->count = ((Elem_1B3040*)rec->elems)->f4;
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
        D_00274520[m] = UploadImagesByMask((1 << m) | 0x40000000);
    }
    D_00274538 = BuildMaskedImagesPacket(0x20000000);
}

struct Ent_1B3510 {
    s32 type;
    Quad4* data;
};
struct Elem_1B3510;
struct Rec_1B3510 {
    u8 kind;
    u8 f1;
    u8 pad2[6];
    u8 col[4];
    u32 mask;
    s16 f10;
    u8 pad12[2];
    Elem_1B3510* f14;
    s32 f18;
    Ent_1B3510* f1C;
    s32 f20;
    void* f24;
};
struct Glob_1B3510 {
    u8 pad0[0x204];
    u32 f204;
};

#define TEST_1B3510(ate, atst, aref, afail, date, datm, zte, ztst) \
    ((u64)(ate) | ((u64)(atst) << 1) | ((u64)(aref) << 4) | ((u64)(afail) << 12) | ((u64)(date) << 14) | \
     ((u64)(datm) << 15) | ((u64)(zte) << 16) | ((u64)(ztst) << 17))
#define ALPHA_1B3510(a, b, c, d, fix) \
    ((u64)(a) | ((u64)(b) << 2) | ((u64)(c) << 4) | ((u64)(d) << 6) | ((u64)(fix) << 32))

extern s32 D_002744F8;

void* func_001611B8(V24A0* b);
void func_001529C8(V24A0* b, s32 n, Quad4* q);
void func_001612F8(V24A0* b, s32 a, s32 c, s32 d, s32 e, s32 f);
void func_001613C0(V24A0* b, s32 a, s32 c, u64 d);
void func_00161708(V24A0* b, s32 reg, u64 v);
void func_001B29E0(Elem_1B3510* e, s32 j, s32 pass, s32 kind, V24A0* b);
void func_00152D70(V24A0* b);
void func_001528C8(V24A0* b);
void func_00161278(V24A0* b, s32 n);
void func_00161520(V24A0* b, f32 x, f32 y, f32 z);
void func_00161458(V24A0* b, u32 c);
void* func_001B4688(s32 key);

void func_001B3510(s32 mask)
{
    V24A0 buf;
    u8 col[4];
    s32 i;
    s32 j;
    Rec_1B3510* rec;
    Ent_1B3510* ents;
    u64 test;
    u64 sel;

    if (mask == 0) {
        return;
    }
    for (i = 0; i < g_animRecordCount; i++) {
        rec = &((Rec_1B3510*)g_animRecords)[i];
        if ((rec->mask & mask) != (u32)mask) {
            continue;
        }
        for (j = 0; j < rec->f20; j++) {
            ents = rec->f1C;
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
                } else if (rec->f1 & 8) {
                    AddGifRegisterWrite(&buf, 0x47, 0x7001B);
                    AddGifRegisterWrite(&buf, 0x42, 0);
                } else if (rec->f1 & 0x20) {
                    test = (rec->f1 & 4) ? 0x13001 : 0x11001;
                    test |= (rec->kind != 1) ? 0x20000 : 0x60000;
                    AddGifRegisterWrite(&buf, 0x47, test);
                    AddGifRegisterWrite(&buf, 0x42, 0);
                } else if (rec->f1 & 0x10) {
                    test = TEST_1B3510(1, (rec->kind == 1) ? 5 : 0, 0x7E, (rec->f1 & 4) ? 3 : 1, 0, 0, 1, (rec->kind == 1) ? 3 : 1);
                    AddGifRegisterWrite(&buf, 0x47, test);
                    sel = (rec->f1 & 1) ? 2 : 0;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(1, sel, 0, 0, 0));
                } else {
                    test = TEST_1B3510(1, (rec->kind == 1) ? 5 : 0, 0x7E, (rec->f1 & 4) ? 3 : 1, 0, 0, 1, (rec->kind == 1) ? 3 : 1);
                    AddGifRegisterWrite(&buf, 0x47, test);
                    sel = (rec->f1 & 1) ? 2 : 1;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                }
                AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
                SendTextureRegisters(rec->f14, j, 0, rec->kind, &buf);
                CloseDmaTag(&buf);
                break;
            case 4:
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                if (rec->f1 & 2) {
                    ReserveGifPackedData(&buf, 0x7C, 0, 3, 0x412, 0);
                    BeginGifTag(&buf, 0, 1, 0xE);
                    AddGifRegisterWrite(&buf, 0x47, 0x71001);
                    sel = (rec->f1 & 1) ? 2 : 1;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                    AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
                    SendTextureRegisters(rec->f14, j, 0, rec->kind, &buf);
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
                sel = (rec->f1 & 1) ? 2 : 1;
                AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
                AddGifStEntry(&buf, 0.0f, 0.0f, 1.0f);
                col[0] = (rec->col[0] + 1) >> 1;
                col[1] = (rec->col[1] + 1) >> 1;
                col[2] = (rec->col[2] + 1) >> 1;
                col[3] = (rec->col[3] + 1) >> 1;
                AddGifRgbaEntry(&buf, *(u32*)col);
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                if (rec->f1 & 2) {
                    ReserveGifPackedData(&buf, 0x7D, 0, 3, 0x412, 0);
                } else {
                    ReserveGifPackedData(&buf, 0x4D, 0, 3, 0x4FF, 0);
                }
                ReserveGifPackedData(&buf, 0x6D, 0, 3, 0x4FF, 0);
                if (rec->f1 & 2) {
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
                SendTextureRegisters(rec->f14, j, 0, rec->kind, &buf);
                CloseGifTag(&buf, 1);
                break;
            case 0: {
                InitGifPacket(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x7C, 0, 4, 0x4F12, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                if (rec->f1 & 8) {
                    AddGifRegisterWrite(&buf, 0x47, 0x70000);
                    AddGifRegisterWrite(&buf, 0x42, 0);
                } else {
                    AddGifRegisterWrite(&buf, 0x47, (rec->f1 & 4) ? 0x737EB : 0x717EB);
                    sel = (rec->f1 & 1) ? 2 : 1;
                    AddGifRegisterWrite(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                }
                ents++;
                AddGifRegisterWrite(&buf, 0x3D, ((Glob_1B3510*)g_camera)->f204);
                SendTextureRegisters(rec->f14, j, 0, rec->kind, &buf);
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x7C, 0, 4, 0x41F2, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x47, 0x53001);
                if (rec->f1 & 8) {
                    AddGifRegisterWrite(&buf, 0x42, 0x8000000068);
                } else {
                    AddGifRegisterWrite(&buf, 0x42, 0x48);
                }
                ents++;
                AddGifRegisterWrite(&buf, 0x3D, 0);
                SendTextureRegisters(rec->f14, j, 1, rec->kind, &buf);
                CloseDmaTag(&buf);
                ClearPacketBuffer(&buf);
                UsePacketBufferMemory(&buf, ents->type, ents->data + j * ents->type);
                ReserveGifPackedData(&buf, 0x7C, 0, 4, 0x4F12, 0);
                BeginGifTag(&buf, 0, 1, 0xE);
                AddGifRegisterWrite(&buf, 0x47, 0x53001);
                if (rec->f1 & 8) {
                    AddGifRegisterWrite(&buf, 0x42, 0x8000000068);
                } else {
                    AddGifRegisterWrite(&buf, 0x42, 0x48);
                }
                AddGifRegisterWrite(&buf, 0x3D, 0);
                AnimRecord* found = (AnimRecord*)FindAnimRecord(rec->f10);
                if (found) {
                    SendTextureRegisters((Elem_1B3510*)found->elems, j, 0, rec->kind, &buf);
                } else {
                    SendTextureRegisters(rec->f14, j, 2, rec->kind, &buf);
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
                SendTextureRegisters(rec->f14, j, 0, rec->kind, &buf);
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

struct Ctx_1B2DF8;

extern u8 D_0024A220[];
void* func_001FD8A8(s32 size);

struct Ent_1B2DF8 {
    u8 pad00[0x4C];
    void* p4c;
    u8 pad50[0x30];
    s32 v80;
    u8 pad84[0x04];

    Ent_1B2DF8() { p4c = D_0024A220; }
    void* operator new[](__SIZE_TYPE__ size) { return func_001FD8A8(size); }
};

extern s32 D_00262260;
extern Ent_1B2DF8* D_00262264;
extern s32 D_0026227C;

s32 func_00137BE0(Ctx_1B2DF8* src);
void func_0015D8A8(Ent_1B2DF8* e, Ctx_1B2DF8* self);
s32 func_0015C1C0(s32 n);

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

extern f32 D_0026185C;
void func_001B46E0(s32 a, s32 frame);

struct Snd_1B1070;
enum Kind_1B1070 { KIND_1B1070_1B = 0x1B };

void func_001BF788(Snd_1B1070* p, s32 n);
void func_001BFCD8(Kind_1B1070 a0, Snd_1B1070** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

