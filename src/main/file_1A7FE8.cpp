// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1A7FE8 to 0x1AA268, built whole (config/us/files.tsv): the object pool
// (class 0x8C, from its init method func_001A7FE8), the agent of class 0x0D, and the set-up,
// update and drawing of the 37 screen elements (func_001A9C68 ... func_001AA1F0), whose objects
// it defines. Its .rodata is the FLT_MAX literal of func_001A7FE8 (0x24CBC4); its .data
// (0x26C3E0 to 0x274398) is the per-element placement table D_0026C3E0, then the 37 screen
// objects, uninitialised (zero, filled at run time by func_001A9C68), which GCC puts at the end
// of the file's .data in definition order. Named after its first address until what it was is
// known.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "world.h"
#include "object_pool.h"
#include "screen_element.h"
#include "font.h"
#include "shapes.h"
#include "game_clock.h"
#include "game_progress.h"
#include "text_reader.h"
#include "globals.h"
#include "asm_func.h"

// The font object's calls.
Font* func_0015C1C0(s32 k);
void func_0015C8B8(Font* font, f32 x, f32 y);
f32 func_0015C418(Font* font, void* text);
void func_0015C638(Font* font, void* text, void* out, s32 zero, void* d);
void func_0015C900(Font* font);
void* func_0015DB28(void* out, void* text, Font* font);
void func_0015E318(void* buf, void* out, s32 zero, void* d);

void func_00182ED0(void* self);
void func_001A93C8(void* self);


void func_001F3C08(void* a, f32* out);
void func_00128150(int a, int b, void* c, f32* d);
f32 func_00205778(f32 x, f32 y);


void func_001C7CB8(void* self);
void func_0012E760(void* obj);


extern f32 D_0026185C;
extern f32 D_00261860;

void func_001AB980(T217D_510* self, f32 value);

extern s32 D_0026227C;

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);


void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);

void func_001C72A0(GaugeBarAgent* self);
void func_001DDC38(void* sub, GaugeBarAgent* self);


s32 func_001DDA80(void* sub);


typedef void* (*VFn_1A9960)(void* self);
void func_001C8C08(GaugeBarAgent* self);
void func_001C8418(GaugeBarAgent* self, void* p);


void func_001C8E28(GaugeBarAgent* self);
void func_001C8BC0(GaugeBarAgent* self);


extern u8 D_00264A40[];

void func_001C91C8(GaugeBarAgent* self);
void func_001603E8(s32 n);
void func_0018C7F8(u8* p);


extern T217D_2E0 D_0026E248;

s32 func_001E9970(void);



extern ElementPlaceTable D_0026C3E0;
extern u8 D_00261868[];


void* func_0018D5C0(u32 n);


void func_00182C58(void* self);
void* func_0015A448(void* obj, s32 id, void* owner);
s32 func_001300E8(void* node, s32 kind);


s32 func_001F5C0C(void* p, s32 value, s32 size);


s32 func_001F5C0C(void* p, s32 value, s32 size);


void func_001A93C8(void* self);



ObjectPoolEntry* func_001A8718(ObjectPool* table, s32 key);







// Where func_001A94C0 takes a position and a matrix from: an object's world frame (f0 or f4), a
// placed object's m110 and v140 (f8), or its own copy of both.
struct FrameSource {
    void* f0;
    void* f4;
    PlacedObject* f8;
    u8 pad0[4];
    Vec02 pos;
    Vec02 rot[3];
};

void func_001920B0(void* self, void* arg);
s32 func_001F3BD8(void* self, void* arg);
void func_001F3C08(void* self, void* arg);
void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);


extern u8 D_00261868[];

void func_001830D8(ObjectPool* self, void* o);
void* func_001A8110(void* self);
void func_00152438(void* self, s32 value);
void func_00152470(void* list, void* item);
u8* func_0018D568(s32 size, void* src);




void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);




void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, void* p);
void func_00137260(void* out, s32 v);
void func_00137268(void* out, s32 v);

extern void* const D_002486B0[];
extern u8 D_00262C68[];
extern u8 D_00262C70[];
extern u8 D_00262D38[];
extern u8 D_00275F80[];

void func_001EFD10(void* a, void* b);


extern void* const D_002486B0[];


// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
// The screen elements' methods, in src/main/screen_element.cpp.
void func_001AA268(ScreenElement* self);
void func_001AA298(ScreenElement* self);
void func_001AAF88(T217D_E30* self);
void func_001AB198(T217D_E30* self);
f32 func_001AB5D8(void);
void func_001AB600(T217D_510* self);
void func_001AB660(T217D_510* self);
void func_001AB710(T217D_510* self);
f32 func_001ABE40(void);
f32 func_001ABE50(void);
f32 func_001ABE60(void);

extern const Fn_Table D_00217E30[];
extern const Fn_Table D_00217E80[];
extern const Fn_Table D_00217ED0[];
extern const Fn_Table D_00217F20[];
extern const Fn_Table D_00217F70[];
extern const Fn_Table D_00217FC0[];
extern const Fn_Table D_00218010[];
extern const Fn_Table D_00218060[];
extern const Fn_Table D_002180B0[];
extern const Fn_Table D_00218100[];
extern const Fn_Table D_00218150[];
extern const Fn_Table D_002181A0[];
extern const Fn_Table D_002181F0[];
extern const Fn_Table D_00218240[];
extern const Fn_Table D_00218290[];
extern const Fn_Table D_002182E0[];
extern const Fn_Table D_00218330[];
extern const Fn_Table D_00218380[];
extern const Fn_Table D_002183D0[];
extern const Fn_Table D_00218420[];
extern const Fn_Table D_00218470[];
extern const Fn_Table D_002184C0[];
extern const Fn_Table D_00218510[];
extern const Fn_Table D_00218560[];
extern const Fn_Table D_002185B0[];
extern const Fn_Table D_00218600[];
extern const Fn_Table D_002186D0[];
extern const Fn_Table D_00218720[];
extern const Fn_Table D_0021A3F0[];
extern const Fn_Table D_0021A440[];
extern const Fn_Table D_00220BF0[];
extern const Fn_Table D_002210F0[];
extern const Fn_Table D_002212E0[];
extern const Fn_Table D_00221330[];
extern const Fn_Table D_00221380[];
extern u8 D_00275F80[];

void func_001EFCE8(void* p);


extern s8 D_00262250[];
extern u8 D_0024E879[];
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void* func_001E2138(void* dst, void* src);


void* func_0018D500(s32 size);
PlacedObject* func_0015A418(void* a, s32 b, s32 c, ObjectPool* d);
void func_00152438(void* p, s32 a);
s32 func_001527D8(void* p);
PlacedObject* func_00183058(PlacedObject* a, World* b, BaseObject* c);





void func_001A8AF8(ObjectPool* self);





extern void* const D_002486B0[];


extern void* const D_002486B0[];


extern void* const D_002486B0[];

extern ElementPlaceTable D_0026C3E0;



// allocator puts the count in $s1 and the pointer in $s0; retail is the other way round.

extern u8 D_00275F80[];
void func_001EFEE0(u8* a);
void func_001AE820(u8* a);




void* func_0018D5C0(u32 n);


s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...);
extern s32 D_002751D4;

// EXACT: dst built as i*4 + (u32)items

void func_001A89E8(ObjectPool* self);
s32 func_001A88A0(ObjectPool* self, s32 item);
void func_001F5B08(s32* dst, s32* src, s32 size);



s32 func_001A88A0(ObjectPool* self, s32 item);




void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...);

f32 func_001EAF28(f32 x);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001AA1F0();
void func_001AA790();
void func_001AA898();
void func_001AA8A0();
void func_001AA8A8();
void func_001AA8C8();
void func_001AA8F0();
void func_001AA958();
void func_001AAF58();
void func_001AAAC8();
void func_001AA4F0();
void func_001AA998();
void func_001AB058();
void func_001ABE70();
void func_001AC0E8();
void func_001AC888();
void func_001AC910();
void func_001AC990();
s32 func_001AC9E0();
void func_001ACA30();
void func_001ACA68();
void func_001ACAA8();
void func_001ACDA0();
void func_001ACE38();
void func_001AD320();
void func_001AD378();
void func_001AD3B0();
void func_001AD3F0();
void func_001AD6A8();
void func_001AD718();
void func_001AD7B0();
void func_001ADC60();
void func_001ADD28();
void func_001ADF28();
void func_001AE130();
void func_001AE178();
void func_001AE220();
void func_001AD940();
void func_001AD970();
void func_001ADB00();
void func_001AE510();
void func_001AE5E0();
void func_001AE758();
void func_001AE7F8();
void func_00193E58();
void func_001940E8();
void func_001943E8();
void func_00194E60();
void func_00194F00();
void func_00194F38();
void func_00194F80();
void func_0014ABD0();
void func_0014AC48();
void func_0014AD00();
void func_0014AD70();
void func_0014ADE0();
void func_001E5E70();
void func_001E6188();
void func_001E73B8();
void func_001E76E0();
void func_001E77C0();
void func_001E7C60();
void func_001E8840();
void func_001310F0();
void func_00131198();
void func_00135550();
void func_00136040();
void func_00136238();
void func_001363D0();
void func_00136408();
f32 func_001365F0();
f32 func_00136648();
void func_001366A0();
void func_00136EF8();
s32 func_00136FA8();
void func_001821B0();
void func_001F1960();
void func_001F1A08();
void func_001F1C90();
void func_001F20A8();
void func_0016B4A0();
void func_0016B560();
void func_0016B580();
void func_0016B7A8();
void func_0016B860();
void func_0016BA40();
void func_0016BBA8();
void func_0016BDD0();
void func_0016BEA0();
void func_001DFEB8();
void func_001E00B0();
void func_001E0678();


s32 func_001E2100(const char*);
void* func_001E2138(char*, const char*);
void func_0015E290(TextReader*, f32, f32*, f32*);

extern f32 D_00261860;

void func_001AB2B8(T217D_E30* self);
f32 func_0015DFF8(TextReader* loc);


// An object func_001A88A0 may add to a pool: a class 0x3B with 0x678 clear or a class 0x20
// with 0x680 set is refused.
struct PoolCandidate { u8 pad0[0x678]; s32 f678; u8 pad1[4]; s32 f680; };

s32 func_00182FC8(PoolCandidate* p);
s32 func_001300E8(PoolCandidate* p, s32 kind);

// The list walk (list_iter.h): push a frame, step through the elements, pop it.
struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

struct ListWalkNext {
    static u8* Of(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct ListWalkEnd {
    static void Of(ListFrame* it)
    {
        g_activeListFrames = it->prev;
    }
};


// Data defined by this file.
ElementPlaceTable D_0026C3E0 = {
    {
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 20.0f, 2, -1, -1 },
        { -18.0f, 20.0f, 1, -1, -1 },
        { -18.0f, 20.0f, 1, 4, 2 },
        { 18.0f, 20.0f, 0, -1, -1 },
        { -18.0f, 20.0f, 1, 5, 2 },
        { -18.0f, 20.0f, 1, -1, -1 },
        { 18.0f, 20.0f, 2, 6, 2 },
        { 0.0f, 20.0f, 2, 3, 2 },
        { -18.0f, 20.0f, 2, 5, 2 },
        { -18.0f, 20.0f, 2, 5, 2 },
        { 18.0f, 20.0f, 2, 6, 2 },
        { 18.0f, 20.0f, 0, -1, -1 },
        { 18.0f, 20.0f, 0, -1, -1 },
        { 18.0f, -20.0f, 0, -1, -1 },
        { 18.0f, -20.0f, 0, 16, 3 },
        { 18.0f, -20.0f, -1, -1, -1 },
        { -18.0f, -20.0f, 1, -1, -1 },
        { -18.0f, -20.0f, 1, 19, 3 },
        { 18.0f, -20.0f, 0, 18, 3 },
        { 18.0f, -20.0f, -1, -1, -1 },
        { 0.0f, -40.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 0.0f, 0.0f, -1, -1, -1 },
        { 1.0f, -20.0f, 0, -1, -1 },
        { -1.0f, -20.0f, 1, -1, -1 },
        { -18.0f, 20.0f, 2, -1, -1 },
        { 18.0f, 20.0f, 2, -1, -1 },
        { 18.0f, 20.0f, 2, -1, -1 },
        { -18.0f, -20.0f, 3, -1, -1 },
        { 18.0f, 20.0f, -1, -1, -1 },
        { 18.0f, -20.0f, 2, -1, -1 },
        { 18.0f, -20.0f, 2, -1, -1 },
        { 18.0f, -20.0f, 3, -1, -1 },
        { 0.0f, -20.0f, 3, -1, -1 },
    },
    0,
};

// The 37 screen objects, in address order (D_002486B0 lists them in another order). They have
// no initialiser: func_001A9C68 installs their tables at run time.
T217D_E30 D_0026C6C8;
T217D_E30 D_0026C948;
T217D_E30 D_0026CBC8;
T217D_E30 D_0026CE48;
T217D_E30 D_0026D0C8;
T217D_E30 D_0026D348;
T217D_E30 D_0026D5C8;
T217D_E30 D_0026D848;
T217D_E30 D_0026DAC8;
T217D_E30 D_0026DD48;
T217D_E30 D_0026DFC8;
T217D_2E0 D_0026E248;
T217D_E30 D_0026E4E0;
T217D_510 D_0026E760;
T217D_1380 D_0026E9F8;
T217D_330 D_0026EC70;
T217D_380 D_0026EED0;
T217D_3D0 D_0026F138;
T217D_420 D_0026F5A0;
T217D_0F0 D_0026F808;
T217D_12E0 D_0026FA90;
T217D_1330 D_0026FD00;
T217D_6D0 D_0026FF68;
T217D_440 D_002701F8;
T217D_BF0 D_00270650;
T217D_3F0 D_002708E0;
T217D_3F0 D_00271558;
T217D_560 D_002721D0;
T217D_E30 D_00272430;
T217D_E30 D_002726B0;
T217D_470 D_00272930;
T217D_4C0 D_00272B98;
T217D_720 D_00272E08;
T217D_5B0 D_002739F0;
T217D_5B0 D_00273C50;
T217D_600 D_00273EB0;
T217D_E30 D_00274118;




void func_00182C18(ObjectPool* self);

void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_001A8208(ObjectPool* self);



void func_001A7FE8(ObjectPool* self)
{
    InitObject(self);
    u8* s1 = (u8*)self + 0x60;
    self->id4C = -1;
    self->id50 = -1;
    self->id54 = -1;
    self->id58 = -1;
    (void)FillMemory(s1, 0, 0x80);
    const Quad16* src = (const Quad16*)&g_identityMatrix;
    *(Quad16*)(s1 + 0x20) = src[0];
    *(Quad16*)(s1 + 0x30) = src[1];
    *(Quad16*)(s1 + 0x40) = src[2];
    (void)FillMemory(((u8*)self + 0xE0), 0, 0x70);
    V8C* p = &self->v110;
    p->a = 0;
    p->b = 1.0f;
    p->c = 0;
    self->f120 = 0;
    self->f124 = 20000.0f;
    (void)FillMemory(((u8*)self + 0x150), 0, 0x18);
    f32 d = 3.4028235e+38f;
    self->fD8 = 5.0f;
    self->f168 = 0;
    self->f144 = d;
    AppendQueuedCall(self->world, (void*)SpawnObjectPoolCopies, self, 0, 0);
}

void func_001A80E0(ObjectPool* self)
{
    UnregisterObject(self);
    ClearObjectPoolChoice(self);
}

void* func_001A8110(ObjectPool* self)
{
    if (self->sub == 0) {
        Sub8C* p = (Sub8C*)AllocateZeroedFrontMemory(0x20);
        self->sub = p;
        *(ObjectPool**)p = self;
    }
    return self->sub;
}

void func_001A8150(ObjectPool* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->items == 0) {
        self->items = (ObjectPoolEntry*)AllocateZeroedFrontMemory(0x50);
    }
    ObjectPoolEntry* e = &self->items[self->count++];
    e->id = a1;
    e->count = a2;
    e->flags = ((((e->flags & -2) | (a3 & 1)) & -3) | ((a4 & 1) << 1));
}

void func_001A8208(ObjectPool* self)
{
    s32 i;
    if (self->sub != 0) {
        if (self->sub->f4 != 0) {
            self->sub->qC = (Quad16*)AllocateFrontMemory(self->count << 5);
        }
    }
    for (i = 0; i < self->count; i++) {
        ObjectPoolEntry* e = &self->items[i];
        PlacedObject* obj = FindFirstObjectById(self->world, 4, e->id, self);
        s32 n;
        s32 cnt;
        if (obj == 0) {
            e->count = 0;
            continue;
        }
        if (self->sub != 0 && self->sub->f4 != 0) {
            s32 x = self->sub->f8;
            if (x == 1) goto c1;
            if (x < 2) {
                if (x == 0) goto c0;
            } else if (x == 2) {
                n = 0;
                cnt = 0;
            }
            goto done;
        c0:
            self->sub->f8 = 1;
            SetListLinkOffset((u8*)self->sub + 0x14, 0x18);
        c1: {
                s32 r = CountListItems((u8*)self->sub + 0x14);
                s32 lim = r + 1;
                s32 m = e->count;
                s32 q = lim;
                if (q < m) q = m;
                n = q;
                cnt = n - r - 1;
            }
        } else {
            n = e->count;
            cnt = n - 1;
        }
    done:
        if (n != 0) e->objects = (void**)AllocateFrontMemory(n << 2);
        e->objects[e->total++] = obj;
        if (cnt > 0) {
            s32 k = cnt;
            do {
                PlacedObject* o2 = CreateObjectCopy(obj, obj->world, obj->parent);
                e->objects[e->total++] = o2;
                if (o2->desc->m0F != 0) o2->desc->m0F(o2);
                o2->desc->m10(o2);
                o2->desc->m15(o2, 0);
                o2->desc->m03(o2);
            } while (--k);
        }
        if (obj->desc->m0F != 0) obj->desc->m0F(obj);
        obj->desc->m10(obj);
        obj->desc->m15(obj, 0);
        obj->desc->m03(obj);
        if (self->sub != 0 && self->sub->f4 != 0) {
            Quad16* d = self->sub->qC + (i << 1);
            d[0] = *(Quad16*)&obj->v190;
            d[1] = *(Quad16*)&obj->v1D0;
        }
    }
}

void func_001A84C8(ObjectPool* self, ObjectPool* other)
{
    CopyObjectData(self, other);
    if (self->sub != 0 && self->sub->f4 != 0) {
        if (other->sub->f8 != 0) {
            self->sub = 0;
        } else {
            other->sub->f8 = 1;
            SetListLinkOffset((u8*)other->sub + 0x14, 0x18);
            self->sub = 0;
        }
        GetObjectPoolShare(self);
        self->sub->f4 = 1;
        self->sub->f8 = 2;
        self->sub->f14 = other;
        AppendToList((u8*)other->sub + 0x14, self->sub);
    } else {
        self->items = (ObjectPoolEntry*)CopyToFrontMemory(other->count * 0x14, other->items);
    }
}

void func_001A8590(ObjectPool* self)
{
    StartObject(self);
    if (self->f168 != 0) {
        return;
    }
    self->f168 = 1;
    if (self->id4C != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id4C, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 0x7E) != 0) {
                self->f60 = p;
            } else if (IsObjectOfKind(p, 0x73) != 0) {
                self->f64 = p;
            } else if (IsObjectOfKind(p, 2) != 0) {
                self->f68 = p;
            }
        }
    }
    if (self->id50 != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id50, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 2) != 0) {
                self->fE0 = p;
            } else if (IsObjectOfKind(p, 0x75) != 0) {
                self->fE4 = p;
            }
        }
    }
    if (self->id54 != -1) {
        void* p = FindFirstObjectByIdMode4(self->world, self->id54, self);
        if (p != 0) {
            if (IsObjectOfKind(p, 0x73) != 0) {
                self->f160 = p;
            } else if (IsObjectOfKind(p, 2) != 0) {
                self->f164 = p;
            }
        }
    }
    if (self->id58 != -1) {
        self->f5C = FindFirstObjectByIdMode4(self->world, self->id58, self);
    }
}

void func_001A86F8(ObjectPool* self, s32 flag)
{
    if (flag) {
        ClearObjectPoolChoice(self);
    }
}

ObjectPoolEntry* func_001A8718(ObjectPool* self, s32 key)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (self->items[i].id == key) break;
    }
    if (i < self->count) return &self->items[i];
    return 0;
}

void func_001A8778(ObjectPool* table, s32 key)
{
    ObjectPoolEntry* e = FindObjectPoolEntry(table, key);
    if (e) {
        e->flags |= 2;
    }
}

void func_001A87A8(ObjectPool* table, s32 key)
{
    ObjectPoolEntry* e = FindObjectPoolEntry(table, key);
    if (e != 0) {
        e->flags &= ~2;
    }
}

void func_001A87E0(ObjectPool* table, s32 key, s32 value)
{
    ObjectPoolEntry* e = FindObjectPoolEntry(table, key);
    if (e != 0) {
        if (value >= e->total) {
            value = e->total;
        }
        e->count = value;
    }
}

s32 func_001A8820(ObjectPool* list, BaseObject* query) { for(s32 i=0;i<list->count;i++){ ObjectPoolEntry* row=&list->items[i]; if(row->count<=0) continue; void** items=row->objects; if(*(s32*)((u8*)items[0]+8) != query->id) continue; for(s32 j=0;j<row->count;j++) if(query==items[j]) return 1; } return 0; }

s32 func_001A88A0(ObjectPool* self, PoolCandidate* key)
{
    Sub8C* group = self->sub;

    if (group != 0 && group->f4 != 0) {
        List01* list;
        ObjectPool* skip;
        ListFrame it;
        u8* obj;

        switch (group->f8) {
        case 1:
            list = (List01*)&group->f14;
            skip = 0;
            break;
        case 2: {
            ObjectPool* e = (ObjectPool*)group->f14;
            skip = self;
            if (e->f48 == (s32)key) {
                return 0;
            }
            list = (List01*)&e->sub->f14;
            break;
        }
        }
        ListWalkBegin::Of(&it, list);
        for (obj = ListWalkNext::Of(&it); obj != 0; obj = ListWalkNext::Of(&it)) {
            ObjectPool* e = *(ObjectPool**)obj;
            if (e != skip && e->f48 == (s32)key) {
                ListWalkEnd::Of(&it);
                return 0;
            }
        }
        ListWalkEnd::Of(&it);
    }
    if (IsObjectAttached(key) != 0) {
        return 0;
    }
    if (IsObjectOfKind(key, 0x3B) != 0 && key->f678 == 0) {
        return 0;
    }
    if (IsObjectOfKind(key, 0x20) != 0 && key->f680 != 0) {
        return 0;
    }
    return 1;
}

void func_001A89E8(ObjectPool* self)
{
    s32 i;
    s32 pos;
    s32 k;

    if (self->count == 0) {
        return;
    }
    i = 1;
    pos = (self->f44 + 1) % self->count;
    if (!(i < self->count)) {
        return;
    }
    do {
        ObjectPoolEntry* rec = &self->items[pos];
        if ((rec->flags & 2) != 0) {
            for (k = 0; k < rec->count; k++) {
                if (IsObjectPoolItemFree(self, (s32)rec->objects[k]) != 0) {
                    goto found;
                }
            }
        }
        pos = (pos + 1) % self->count;
        i++;
    } while (i < self->count);
found:
    if (i < self->count) {
        self->f44 = pos;
    }
}

void func_001A8AF8(ObjectPool* self)
{
    s32 s5 = 0;
    s32 s4 = 0;
    if (self->count != 0) {
        if (self->f40 == 0) {
            AdvanceObjectPoolEntry(self);
        }
        ObjectPoolEntry* rec = &self->items[self->f44];

        if (rec->flags & 2) {
            s32 i = 0;
            if (rec->count > 0) {
                do {
                    if (IsObjectPoolItemFree(self, (s32)rec->objects[i]) != 0) {
                        s4 = (s32)rec->objects[i];
                        if (self->sub != 0 && self->sub->f4 != 0) {
                            s5 = self->sub->fC + (self->f44 << 5);
                        }
                        if (rec->flags & 1) {
                        } else {
                            rec->count = rec->count - 1;
                            s32* p = (s32*)((u8*)0 + i * 4 + (u32)rec->objects);
                            MoveMemory(p, p + 1, (rec->count - i) * 4);
                        }
                        break;
                    }
                    i++;
                } while (i < rec->count);
            }
        }
    }
    self->f48 = s4;
    if (self->sub != 0 && self->sub->f4 != 0) {
        self->sub->f10 = s5;
    }
}

s32 func_001A8C50(ObjectPool* self)
{
    if (self->f48 != 0) {
        return 1;
    }
    ChooseObjectPoolItem(self);
    return self->f48 != 0;
}

ASM_FUNC(func_001A8C90);

void func_001A93C8(ObjectPool* p) { p->f48 = 0; if (p->sub != 0 && p->sub->f4 != 0) p->sub->f10 = 0; }

void func_001A93E8(u8* self)
{
    u8* p = self + 0x60;
    FillMemory(p, 0, 0x80);
    *(Mat02*)(p + 0x20) = g_identityMatrix;
}

void func_001A9438(ObjectPool* self)
{
    FillMemory((u8*)self + 0xE0, 0, 0x70);
    V8C* t = &self->v110;
    t->a = 0;
    t->b = 1.0f;
    t->c = 0;
    self->f124 = 20000.0f;
    self->f120 = 0;
}

void func_001A9498(u8* self)
{
    FillMemory(self + 0x150, 0, 0x18);
}

void func_001A94C0(FrameSource* self, Vec02* a1, Vec02* a2, void* a3)
{
    if (self->f0 != 0) {
        ConvertPositionToWorld(self->f0, a1);
        a2[0] = self->rot[0];
        a2[1] = self->rot[1];
        a2[2] = self->rot[2];
    } else if (self->f4 != 0) {
        GetObjectWorldPosition(self->f4, a1);
        GetObjectWorldRotation(self->f4, a2);
    } else {
        if (self->f8 != 0) {
            a1[0] = self->f8->v140;
            PlacedObject* in = self->f8;
            a2[0] = in->m110.r[0];
            a2[1] = in->m110.r[1];
            a2[2] = in->m110.r[2];
        } else {
            a1[0] = self->pos;
            a2[0] = self->rot[0];
            a2[1] = self->rot[1];
            a2[2] = self->rot[2];
        }
    }
    if (a3 != 0) {
        TransformPointBetweenFrames(0, a3, a1, a1);
        TransformRotationBetweenFrames(0, a3, a2, a2);
    }
}

ASM_FUNC(func_001A95D0);

void func_001A97C8(u8* self, f32* out, int x)
{
    f32 v[12];
    if (*(void**)(self + 0x10) != 0) {
        GetObjectWorldRotation(*(void**)(self + 0x10), v);
        TransformRotationBetweenFrames(0, x, v, v);
        *out = ArctangentOfRatio(v[1], v[0]);
    } else if (*(u8**)(self + 0x14) != 0) {
        TransformRotationBetweenFrames(0, x, *(u8**)(self + 0x14) + 0x110, v);
        *out = ArctangentOfRatio(v[1], v[0]);
    } else {
        *out = *(f32*)(self + 0x8);
    }
}

ASM_FUNC(func_001A9868);

void func_001A98F8(GaugeBarAgent* self)
{
    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
}

s32 func_001A9928(GaugeBarAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0)
        return 0;
    return self->fC24;
}

void func_001A9960(GaugeBarAgent* self)
{
    UpdateAgentGoal(self);
    if (self->f724 == 0x10) {
        void* r = ((VFn_1A9960*)self->desc)[102](self);
        if (r != 0)
            func_001C8418(self, (u8*)r + 0x140);
    }
}

void func_001A99B8(GaugeBarAgent* self)
{
    UpdateAgentState(self);
    if (self->f724 == 0x10)
        FaceAgentTowardGoalPoint(self);
}

void func_001A99F8(GaugeBarAgent* self)
{
    EnterAgentState(self);
    if (self->f724 == 0xB) {
        MarkLevelDone(4);
        StartMemoryCardSave(g_memoryCard);
    }
}

void func_001A9A40(GaugeBarAgent* self)
{
    u8* s = (u8*)self;
    UpdateAgent(self);
    void* p = *(void**)(s + 0xC20);
    if (p != 0) {
        if (*(f32*)((u8*)p + 0x18) == 0.0f) {
            StopAnimationPlayer(p);
            *(void**)(s + 0xC20) = 0;
        }
    }
}

void func_001A9A98(void)
{
    if (AreMenusAndFadeClear()) {
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    } else {
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
    }
}

ASM_FUNC(func_001A9AE8);

void func_001A9C58(GaugeBarAgent* self, s32 a, s32 b, s32 c)
{
    self->fC14 = a;
    self->fC18 = b;
    self->fC1C = c;
}

void func_001A9C68()
{
    D_0026C6C8.vt = (const T217D_Vt*)D_00217E30;
    D_0026C948.vt = (const T217D_Vt*)D_00217E80;
    D_0026CBC8.vt = (const T217D_Vt*)D_00217ED0;
    D_0026CE48.vt = (const T217D_Vt*)D_00217F20;
    D_0026D0C8.vt = (const T217D_Vt*)D_00217F70;
    g_gaugeAmountCaption.vt = (const T217D_Vt*)D_00217FC0;
    D_0026D5C8.vt = (const T217D_Vt*)D_002180B0;
    D_0026D848.vt = (const T217D_Vt*)D_00218010;
    D_0026DAC8.vt = (const T217D_Vt*)D_00218060;
    D_0026DD48.vt = (const T217D_Vt*)D_00218100;
    D_0026DFC8.vt = (const T217D_Vt*)D_00218150;
    g_gaugeBarElement.vt = (const T217D_Vt*)D_002182E0;
    D_0026E4E0.vt = (const T217D_Vt*)D_002181A0;
    g_timerElement.vt = (const T217D_Vt*)D_00218510;
    g_timerCaption.vt = (const T217D_Vt*)D_00221380;
    g_buttonHintElement.vt = (const T217D_Vt*)D_00218330;
    D_0026EED0.vt = (const T217D_Vt*)D_00218380;
    D_0026F138.vt = (const T217D_Vt*)D_002183D0;
    D_0026F5A0.vt = (const T217D_Vt*)D_00218420;
    g_mapScreenList.vt = (const T217D_Vt*)D_002210F0;
    D_0026FA90.vt = (const T217D_Vt*)D_002212E0;
    D_0026FD00.vt = (const T217D_Vt*)D_00221330;
    g_pauseMenuElement.vt = (const T217D_Vt*)D_002186D0;
    g_typedTextCaptionBox.vt = (const T217D_Vt*)D_0021A440;
    D_00270650.vt = (const T217D_Vt*)D_00220BF0;
    D_002708E0.vt = (const T217D_Vt*)D_0021A3F0;
    D_00271558.vt = (const T217D_Vt*)D_0021A3F0;
    D_00272430.vt = (const T217D_Vt*)D_00218240;
    D_002726B0.vt = (const T217D_Vt*)D_00218290;
    D_00272930.vt = (const T217D_Vt*)D_00218470;
    D_00272B98.vt = (const T217D_Vt*)D_002184C0;
    D_002721D0.vt = (const T217D_Vt*)D_00218560;
    g_stackedCaptionGroup.vt = (const T217D_Vt*)D_00218720;
    D_002739F0.vt = (const T217D_Vt*)D_002185B0;
    D_00273C50.vt = (const T217D_Vt*)D_002185B0;
    D_00273EB0.vt = (const T217D_Vt*)D_00218600;
    D_00274118.vt = (const T217D_Vt*)D_002181F0;
    for (s32 i = 0x24; i >= 0; i--) {
        ((ScreenElement**)g_screenElements)[i]->vt->m00(((ScreenElement**)g_screenElements)[i], i);
    }
    ResetScreenFade(g_screenFade);
}

void func_001A9F78(void)
{
    ScreenElement** base = (ScreenElement**)g_screenElements;
    ScreenElement** p = base + 36;
    s32 i = 0x24;
    do {
        i--;
        (*p)->vt->m01(*p);
        p--;
    } while (i >= 0);
}

void func_001A9FD0(void)
{
    ScreenElement** slots = (ScreenElement**)g_screenElements;
    for (s32 i = 36; i >= 0; i--) {
        ScreenElement* o = slots[i];
        o->vt->m02(o);
    }
    u8* g = g_screenFade;
    void* b;
    if (*(s32*)g_padRouting & 4) {
        b = g_padRecord;
    } else {
        b = g_blankPadRecord;
    }
    UpdateScreenFade(g, b);
}

void func_001AA060(void)
{
    ScreenElement** base = (ScreenElement**)g_screenElements;
    ScreenElement** p = base + 36;
    s32 i = 0x24;
    do {
        ScreenElement* o = *p;
        p--;
        o->vt->m16(o, 0);
        i--;
    } while (i >= 0);
}

void func_001AA0C0(void)
{
    ScreenElement** p = (ScreenElement**)g_screenElements;
    s32 n = 0x24;
    do {
        n--;
        ScreenElement* o = *p;
        o->vt->m05(o);
        p++;
    } while (n >= 0);
}

void func_001AA110(void)
{
    s32 n = 0x24;
    ScreenElement** p = (ScreenElement**)g_screenElements;
    do {
        ScreenElement* o = *p;
        p++;
        n--;
        if (o->mode != 0) {
            void (*fn)(ScreenElement*) = o->vt->m10;
            if (fn != 0) {
                fn(o);
            }
        }
    } while (n >= 0);
}

void func_001AA178(void)
{
    s32 i;
    for (i = 0; i < 0x25; i++) {
        ScreenElement* p = ((ScreenElement**)g_screenElements)[i];
        if (p->mode != 0) {
            p->vt->m09(p);
        }
    }
    DrawScreenFade(g_screenFade);
    DrawCyclingGlyphElement((u8*)&D_00273EB0);
}

void func_001AA1F0(ScreenElement* self, s32 index)
{
    self->place = (T217D_Place*)((u8*)&g_elementPlaces + index * 20);
    self->outTime = 0.25f;
    self->inTime = 0.25f;
    self->clock = (f32*)g_elapsedTime;
    self->index = index;
    SetScreenElementSize(self, self->w, self->h);
    self->x = self->hiddenX;
    self->y = self->hiddenY;
}
