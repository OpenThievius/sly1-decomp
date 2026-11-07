// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
extern f32 D_0026185C[];
#include "list_iter.h"
#include "object_group.h"
#include "world.h"
#include "gauge_counted_object.h"
#include "object_link.h"
#include "attachment.h"
#include "shapes.h"
#include "globals.h"
#include "screen_element.h"

// A four-float vector, aligned as the VU0 reads it.
struct __attribute__((aligned(16))) Vec4_1963D8 { f32 x, y, z, w; };


void func_00123ED0(ObjectGroup* self);
void func_00152470(u8* dst, ObjectGroup* src);



void func_00124A48(ObjectGroup* self);




void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* table);



struct Obj_196E48 { u8 pad0[0x50]; s32 f50; u8 pad1[0x538 - 0x54]; u64 bits538; };

s32 func_001300E8(void* self, s32 kind);



void func_001B6598(void* obj, s32* out);
void* func_001E9970(s32 arg);


void func_001A76A0(void* node, s32 flag);
void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);





struct Pair_00197A68 { u8 pad[0x94]; f32 f94; f32 f98; };



void func_001922E8(void* a, void* b);



extern u8 D_00261EF0[];
void func_00151E20(void* self, f32 amount);



void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_001973D8(C18* self);



extern u8 D_0026E744[];


void func_00192230(void* self, s32 kind, void* rec);
void func_001B6598(void* dev, s32* out);
void func_001DDC38(void* sub, void* self);
void func_001AB890(void* obj, f32 x);
void func_001AB928(void* obj, f32 x, void* fn);
void func_001AB938(void* obj);
void func_001AB958(void* obj);
void func_00197458(s32 unused, s32 flag);



struct Node_197848 {
    u8 pad[0x568];
    Node_197848* next;
};

extern f32 D_00261858[];
extern C0F* func_00182FC8(C0F*);
extern s32 func_001527D8(void* list);
extern s32 func_001EAA70(s32 a, s32 b);
extern void func_00152600(void* a, void* b);
extern void func_00152470(void* a, void* b);
extern void func_001C8F20(void* node, s32 kind, s32 flag);
extern void func_001A76A0(void* node, s32 flag);







void func_001921A8(C18* self);
void func_00152438(List01* p, s32 value);



struct Item_001969F8 { u8 pad[0x24]; void* p24; };

struct Any_001969F8;

extern u8 D_0021A790[];

void func_00124A48(C18* self);
void func_00124DF8(C18* self, s32 n, void* table);
f32 func_00205778(f32 a, f32 b);
void* func_001B6290(Any_001969F8* a, void* b, s32 c, s32 d);
void* func_00121228(World* root, void* value, const T2195_Vt* table);
void func_001299E0(Any_001969F8* a, void* b);
s32 func_0015A4F0(Any_001969F8* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void* func_0018D500(s32 size);
void func_00152470(Any_001969F8* list, void* item);
void func_001B6DF8(Any_001969F8* a, void* b);



struct Cell_196410 { PlacedObject* node; s32 link; };

void func_00152438(u8* a, s32 v);
void func_00137EB0(LoadStream* r, void* out);
void func_00137E70(LoadStream* r, void* out);
s32 func_00137B90(LoadStream* r);
s32 func_00137D10(LoadStream* r);
PlacedObject* func_001DC208(void* host, s32 a);
PlacedObject* func_0011E580(s32 slot, void* host, s32 z, s32 key, s32 flag);
void func_001DC150(void* host, PlacedObject* n, s32 v);
Cell_196410* func_0018D5C0(s32 n);
void func_00152470(u8* list, Cell_196410* c);
PlacedObject* func_0015A418(void* host, s32 kind, s32 id, PlacedObject* c);
void* func_001C1390(s32 id, void* host);
void func_0011A338(void* a, void* b);
s32 func_00137C40(LoadStream* r);
s32 func_00137CC0(LoadStream* r);
f32 func_00137DF8(LoadStream* r);
void func_0011EC40(PlacedObject* n, LoadStream* r);
void func_0011ECB8(void* host, ObjectGroup* self, LoadStream* r);
s32 func_00152720(List01* list);

// The id that names no object.
struct Id_196410 {
    static s32 None() { return -1; }
};




struct Cell_196810 { void* node; s32 link; };
struct Elem_196810 { s32 f0; u8 pad4[4]; Elem_196810* next; };
struct Item_196810 { u8 pad0[0x1C]; Item_196810* next; u8 pad20[0x10]; void* f30; };
void func_00127048(ObjectGroup* self, ObjectGroup* src);
void func_00152440(GroupList* p);
void func_00152470(GroupList* list, Cell_196810* c);



void func_001BA130(void*);
void func_00198980(void*);
void func_001B7F78(void);
void func_00182D48(void*);
void func_00152470(void*, void*);
void func_00182ED0(void*);
void func_00152600(void*, void*);
void func_00182C58(void*);
void* func_0015A418(void*, s32, s32, void*);
void func_001B7A98(void*);
void func_001B7B78(void*);
void func_00182C18(void*);
void func_00144848(void*);
void func_0015EAE0(void*, void*, void*);
void func_0019D860(void);
void func_0019D968(void);
void func_0019D930(void);
void func_0019EBE8(void*);
void func_001831E8(void*, void*, s32, void*);
void func_001831E8(void*, void*, void*, void*);
void func_00183238(void*, void*, void*, void*);
void func_0019F9D0(void*, u32);





void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_0015A838(void* a, s32 b, s32 c, void* d);



void func_001C72A0(void* self);




void* func_001925F0(void);
void func_00197A08(void* h, void* self);
void func_001C9008(void* self, void* arg);




void func_001C91C8(void* self);
void func_001C8920(void* self);



struct Req_1986E8 {
    s32 a;
    s32 b;
};

void func_001C9DE0(void* self, s32 code, void* req);




s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);






void* func_001925F0(C0F* self, f32 f);
s32 func_001300E8(void* key, s32 kind);
s32 func_00182FC8(void* p);
s32 func_00141170(void* self, void* value);
struct Tmp_198760 {
    void* f00;
    void* f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    u8 pad14[0x40 - 0x14];
};
s32 func_00177838(Tmp_198760* f, s32 a, s32 b);
void func_001C7CB8(C0F* self, f32 f);

// The file's .data, in retail's order.
f32 D_0026A710 = 2200.0f;
f32 D_0026A714 = 4000.0f;
f32 D_0026A718 = 2000.0f;
f32 D_0026A71C = 4000.0f;
s32 D_0026A720 = 5;
ObjectLink D_0026A728[1] = { { 0, 0x3D9, 0x610 } };
ObjectLink D_0026A738[13] = {
    { 0x24, 0x3DD, 0x640 },
    { 0x20, 0x3DE, 0x648 },
    { 0x0, 0x3E7, 0x64C },
    { 0x0, 0x3E8, 0x650 },
    { 0x0, 0x3E9, 0x654 },
    { 0x0, 0x3EA, 0x658 },
    { 0x0, 0x3EC, 0x670 },
    { 0x4, 0x3ED, 0x65C },
    { 0x0, 0x3EE, 0x668 },
    { 0x0, 0x3F0, 0x66C },
    { 0x4, 0x3EF, 0x660 },
    { 0x24, 0x3EB, 0x678 },
    { 0x1, 0x3F1, 0x6B4 },
};
f32 D_0026A7D8[6] = { 7.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A7F0 = { 3.0f, -2.0f, -1.0f, 0.0f };
Vec4_1963D8 D_0026A800 = { 0.25f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A810 = { 1.2f, -1.2f, 0.0f, 0.0f };
f32 D_0026A820 = 60.0f;
f32 D_0026A824 = -30.0f;
f32 D_0026A828 = 0.25f;
f32 D_0026A82C = 0.7f;
f32 D_0026A830 = 250.0f;
f32 D_0026A834 = 0.25f;
f32 D_0026A838 = 0.5f;
f32 D_0026A83C = 0.2f;
f32 D_0026A840 = 0.1f;
f32 D_0026A844 = 1.3f;
Vec4_1963D8 D_0026A850 = { 0.0f, 3.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A860 = { 0.0f, 0.75f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A870 = { 5000.0f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A880 = { 3.0f, -2.0f, -1.0f, 0.0f };
Vec4_1963D8 D_0026A890 = { 500.0f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A8A0 = { 1.8f, -0.00024999998f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A8B0 = { 1.1f, 1.6f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A8C0 = { 1.4f, -0.005f, 0.0f, 0.0f };
f32 D_0026A8D0[2] = { 0.9f, 1.2f };
f32 D_0026A8D8 = 2000.0f;
f32 D_0026A8DC = 1100.0f;
ObjectLink D_0026A8E0[3] = { { 0x0, 0x3E4, 0x558 }, { 0x0, 0x3E5, 0x554 }, { 0x20, 0x3E6, 0x55C } };
// The object func_00196938 registers itself as; filled at run time.
C18* D_0026A904 = 0;

void func_001963D8(ObjectGroup* self);
void func_00196410(ObjectGroup* self, LoadStream* rd);
void func_00196810(ObjectGroup* self, ObjectGroup* src);
void func_00196900(ObjectGroup* self);
void func_00196938(C18* self);
void func_001969C0(C18* self);
void func_001969F8(C18* self);
s32 func_00196E48(s32 a0, Obj_196E48* self);
void func_001973D8(C18* self);
void func_00197458(s32 unused, s32 flag);
void func_001974D8(C18* a, void* b);
void func_00197788(C18* self);
void func_00197848(C18* self);
void func_00197A08(u8* self, C0F* ctx);
void func_00197A68(C18* ctx, Pair_00197A68* out);
void func_00197F10(C18* self, s32 kind, void* rec);
void func_00198090(C0F* self);
s32 func_001982A0(C0F* self);
void func_001984B8(C0F* self, void* arg);
void func_00198530(C0F* self);
void func_001986E8(C0F* self, s32 code, Req_1986E8* req);
void func_00198760(C0F* s1, f32 f);
u32 func_00198858(void);
void func_00198920(GaugeCountedObject* self);

void func_001963D8(ObjectGroup* self)
{
    InitPlacedObject(self);
    AppendToList(&self->world->list1C3C, self);
}

void func_00196410(ObjectGroup* self, LoadStream* rd)
{
    PlacedObject* arr[64];
    ListFrame fr;
    PlacedObject* t;
    PlacedObject* c;
    s32 n;
    s32 i;
    s32 j;
    s32 cnt;
    s32 id;
    PlacedObject* x;
    PlacedObject* h;

    SetListLinkOffset((u8*)&self->cells, 8);
    ReadBufferedRotation3(rd, &self->rot);
    ReadBufferedVector3(rd, &self->pos);
    n = ReadBufferedU8(rd);
    if (self->desc->m12 != 0)
    {
        self->desc->m12(self);
    }
    for (i = 0; i < n; i++)
    {
        Cell_196410* cell;
        id = ReadBufferedS16(rd);
        if (id == Id_196410::None())
        {
            c = PopSpawnedClone(self->world, ReadBufferedS16(rd));
        }
        else
        {
            s32 a = ReadBufferedS16(rd);
            c = CreateTypedRecord(id, self->world, 0, a, ReadBufferedS16(rd));
            c->desc->m0A(c, rd);
            PushCloneBatch(self->world, c, ReadBufferedS16(rd));
        }
        cell = AllocateZeroedFrontMemory(16);
        cell->node = c;
        cell->link = self->id;
        c->alias = (Alias01*)cell;
        AppendToList((u8*)&self->cells, cell);
        arr[i] = c;
    }
    cnt = ReadBufferedU8(rd);
    for (j = 0; j < cnt; j++)
    {
        f32 big = 1.0e10f;
        t = 0;
        id = ReadBufferedS16(rd);
        for (i = 0; i < n; i++)
        {
            c = arr[i];
            if (c->id == id)
            {
                t = c;
            }
            else if (c->desc->flags & 1)
            {
                t = FindFirstObjectById(self->world, 0x101, id, c);
            }
            if (t != 0)
            {
                break;
            }
        }
        s32 res = ReadBufferedS16(rd);
        if (res != Id_196410::None())
        {
            void* r = GetScriptEntryScope(res, self->world);
            if (t->f2C != 0)
            {
                AddScriptScopeParent(r, t->f2C);
            }
            t->f2C = r;
        }
        s32 w = ReadBufferedU32(rd);
        if (t->desc->flags & 1)
        {
            t->f88 = w;
        }
        s32 m = ReadBufferedS8(rd);
        if (m == 2)
        {
            t->bits28 = m;
            t->f80 = ReadBufferedFloat(rd);
            if (t->f80 == 3.4028235e+38f)
            {
                t->f80 = big;
            }
        }
        ReadPropertyRecords(t, rd);
    }
    for (i = 0; i < n; i++)
    {
        c = arr[i];
        if (c->desc->m16 != 0)
        {
            c->desc->m16(c, self);
        }
        c->desc->m15(c, self->parent);
    }
    if (n == 1)
    {
        List01* list = &self->children;
        ReadSlotObjects(self->world, self, rd);
        if (IsListEmpty(list) == 0)
        {
            fr.list = list;
            fr.prev = g_activeListFrames;
            fr.offset = list->offset;
            g_activeListFrames = &fr;
            c = arr[0];
            h = *(PlacedObject**)list;
            fr.link = (u8*)h + fr.offset;
            x = h;
            while (x != 0)
            {
                x->desc->m15(x, c);
                PlacedObject* nx = *(PlacedObject**)fr.link;
                fr.link = (u8*)nx + fr.offset;
                x = nx;
            }
            g_activeListFrames = fr.prev;
        }
    }
    self->desc->m03(self);
    self->desc->m02(self);
}

void func_00196810(ObjectGroup* self, ObjectGroup* src)
{
    Pair53 saved = self->kept;
    CopyPlacedObject(self, src);
    self->kept = saved;
    GroupList list = self->cells;
    ClearList(&self->cells);
    ListFrame frame;
    Elem_196810* e = (Elem_196810*)list.first;
    while (e != 0) {
        Item_196810* it = (Item_196810*)((PlacedObject*)self->parent)->children.head;
        for (; it != 0; it = it->next) {
            if (it->f30 == e) break;
        }
        Cell_196810* cell = (Cell_196810*)AllocateZeroedFrontMemory(16);
        cell->link = self->id;
        if (it != 0) {
            cell->node = it;
            it->f30 = cell;
        } else {
            cell->node = (void*)e->f0;
        }
        AppendToList(&self->cells, cell);
        e = e->next;
    }
}

void func_00196900(ObjectGroup* self)
{
    StartPlacedObject(self);
    self->desc->m03(self);
}

void func_00196938(C18* self)
{
    InitSwitchedCollider(self);
    self->f61C = -10.0f;
    (*(Quad16*)&self->v630) = *(Quad16*)&g_unitZVector;
    self->f688 = 120.0f;
    self->f624 = D_0026A71C;
    self->f628 = D_0026A718;
    SetListLinkOffset(&self->f6A8, 0x568);
    SetListLinkOffset(&self->f69C, 0x568);
    g_gaugeCollider = self;
}

void func_001969C0(C18* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_gaugeColliderLoadLinks);
}

void func_001969F8(C18* self)
{
    s32 arr[32];
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0xD, g_gaugeColliderStartLinks);
    self->f618 = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    self->f614 = (StateWalker*)CreateStateWalker((Any_001969F8*)self->f610, self, -1, 1);

    self->f664 = CreatePoseSource(self->world, self->f65C, (const T2195_Vt*)D_0021A790);
    ((Attachment*)self->f664)->mode1 = 2;
    InsertAttachment((Any_001969F8*)self->f65C, self->f664);
    ((s32*)self->f664)[7] = 1;
    ((Item_001969F8*)self->f664)->p24 = self->f660;
    *(Quad16*)((u8*)self->f664 + 0x30) = *(Quad16*)&D_00248D30;
    s32 n1 = GatherObjectsById((Any_001969F8*)self->world, 0x305, 0xF, 0, 0, 0);
    self->f690 = n1;
    void* buf = AllocateFrontMemory(n1 * 4);
    self->f694 = buf;
    self->f690 = GatherObjectsById((Any_001969F8*)self->world, 0x105, 0xF, 0, self->f690, buf);
    s32 cnt = GatherObjectsById((Any_001969F8*)self->world, 5, 0x44, 0, 0x20, arr);
    for (s32 i = 0; i < cnt; i++) {
        AppendToList((Any_001969F8*)&self->f69C, (void*)arr[i]);
    }
    self->f6B8 = CreateStateWalker((Any_001969F8*)self->f6B4, 0, -1, 0);
    func_001B6DF8((Any_001969F8*)self->f6B8, self);
}

ASM_FUNC(func_00196B78);

s32 func_00196E48(s32 a0, Obj_196E48* self)
{
    if (self->bits538 & 0x80000000000ULL) {
        if (IsObjectOfKind(self, 0x1F) == 0) return 0;
    }
    return self->f50 != a0;
}

ASM_FUNC(func_00196EB0);

ASM_FUNC(func_001971B8);

void func_001973D8(C18* self)
{
    f32 one = 1.0f;
    f32 t = (f32)self->f680 / (f32)self->f684;
    f32 c;
    if (t < 0.0f) {
        c = 0.0f;
    } else if (one < t) {
        c = one;
    } else {
        c = t;
    }
    RaiseScatterLevels(g_scatterController, 1.0f - c * 0.8f);
}

void func_00197458(s32 unused, s32 flag)
{
    s32 out[4];
    if (flag == 1) {
        if (g_gaugeCollider->f6B8 != 0) {
            GetStateWalkerTargetKey(g_gaugeCollider->f6B8, &out[0]);
            GetStateWalkerCurrentKey(g_gaugeCollider->f6B8, &out[1]);
            if (out[0] != 0x3F4 && out[1] != 0x3F4) {
                SetStateWalkerTarget(g_gaugeCollider->f6B8, 0x3F5);
                ApplyGaugeColliderRatioToEffect(g_gaugeCollider);
            }
        }
    }
}

void func_001974D8(C18* a, void* b)
{
    HandleSwitchedColliderActivation(a, b);
}

ASM_FUNC(func_001974F8);

void func_00197788(C18* self)
{
    s32 v;
    GetStateWalkerCurrentKey(self->f6B8, &v);
    void* p = 0;
    if (v == 0x3F3) p = AreMenusAndFadeClear(0);
    if (p != 0) {
        g_gaugeAmountCaption.vt->m14(&g_gaugeAmountCaption);
        D_0026E4E0.vt->m14(&D_0026E4E0);
        g_timerElement.vt->m14(&g_timerElement);
        return;
    }
    g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
    D_0026E4E0.vt->m15(&D_0026E4E0);
    g_timerElement.vt->m15(&g_timerElement);
}

void func_00197848(C18* self)
{
    ListFrame frame;
    if (g_gameClock[1] < self->f698) return;
    s32 i = 0;
    for (; i < self->f690; i++) {
        if (IsObjectAttached(((C0F**)self->f694)[i]) == 0) break;
    }
    if (i >= self->f690) {
        self->f698 = 3.4028235e+38f;
        return;
    }
    C0F* o = ((C0F**)self->f694)[i];
    s32 n = RandomIntInRange(0, CountListItems(&self->f69C) - 1);
    Node_197848* nd = (Node_197848*)self->f69C.head;
    if (n > 0) {
        do {
            nd = nd->next;
        } while (--n);
    }
    if (nd == 0) return;
    RemoveFromList(&self->f69C, nd);
    AppendToList(&self->f6A8, nd);
    o->desc->m02(o);
    o->desc02()->m1D(o, (Vec02*)((u8*)nd + 0x140));
    o->desc02()->m1E(o, (Mat02*)((u8*)nd + 0x110));
    o->desc02()->m20(o, (Vec02*)&D_00248D30);
    o->desc02()->m21(o, (Vec02*)&D_00248D30);
    ChangeAgentState(o, 0x10, 0);
    o->fC14 = nd;
    SetSoundStateObjectState(nd, 1);
    self->f698 = g_gameClock[1] + D_0026A838;
}


void func_00197A08(u8* self, C0F* ctx)
{
    void* p = ctx->fC14;
    SetSoundStateObjectState(p, 0);
    RemoveFromList(self + 0x6A8, p);
    AppendToList(self + 0x69C, p);
    ctx->fC14 = 0;
}

void func_00197A68(C18* ctx, Pair_00197A68* out)
{
    (void)ctx;
    out->f98 = D_0026A83C;
    out->f94 = D_0026A840;
}

ASM_FUNC(func_00197A88);

void func_00197F10(C18* self, s32 kind, void* rec)
{
    s32 code;
    HandleSwitchedColliderNotification(self, kind, rec);
    switch (kind) {
    case 0xB:
        self->f644 = 0;
        return;
    case 0xA:
        self->f644 = *(s32*)rec;
        return;
    case 0x14:
        if (rec != self->f6B8) {
            return;
        }
        GetStateWalkerCurrentKey(rec, &code);
        if (code == 0x3F3) {
            *(void**)D_0026E744 = (u8*)self + 0x67C;
            g_gaugeAmountCaption.target = &self->f680;
            g_gaugeAmountCaption.limit = &self->f684;
            SetWorldActiveFollower(self->world, self);
            StartTimer(&g_timerElement, self->f688);
            SetTimerLimit(&g_timerElement, 0.0f, (void*)EndGaugeColliderTimer);
            StartTimerCounting(&g_timerElement);
        } else {
            if (code < 0x3F3) {
                return;
            }
            if (code < 0x3F6) {
                StopTimer(&g_timerElement);
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                D_0026E4E0.vt->m15(&D_0026E4E0);
                g_timerElement.vt->m15(&g_timerElement);
                SetWorldActiveFollower(self->world, 0);
            }
        }
        return;
    }
}

void func_00198090(C0F* self)
{
    StartAgent(self);
}

ASM_FUNC(func_001980B0);

s32 func_001982A0(C0F* self)
{
    s32 r;

    switch (self->f724) {
    case 2:
        if (func_001C96B8(self) == 0) {
            r = 4;
            break;
        }
        r = ChooseAgentState(self);
        break;
    case 0x10:
        r = 0x10;
        if (self->fC10 != 0) {
            r = 0;
        }
        break;
    default:
        r = ChooseAgentState(self);
        break;
    }
    return r;
}

ASM_FUNC(func_00198318);

void func_001984B8(C0F* self, void* arg)
{
    if (self->f724 == 0x10) {
        void* h = GetActiveSwitchedCollider();
        ReleaseObjectNode(h, self);
        Vec02 ctx = self->v150;
        ctx.z = 0;
        self->desc02()->m20(self, &ctx);
    }
    LeaveAgentState(self, arg);
}

void func_00198530(C0F* self)
{
    EnterAgentState(self);
    if (self->f724 == 0x10) {
        func_001C8920(self);
    }
}

ASM_FUNC(func_00198570);

void func_001986E8(C0F* self, s32 code, Req_1986E8* req)
{
    HandleAgentNotification(self, code, req);
    if (code != 10) {
        if (code == 11) {
            if (req->b == (s32)self) {
                self->fC10 = 0;
            }
        }
    } else {
        if (req->b == (s32)self) {
            self->fC10 = req->a;
        }
    }
}

void func_00198760(C0F* s1, f32 f)
{
    C18* s0 = (C18*)GetActiveSwitchedCollider(s1, f);

    if (IsObjectOfKind(s0, 0x18) != 0) {
        if (s0->f640 != 0) {
            if (IsObjectAttached(s0->f640) != 0) {
                if (func_00141170(s0->f640, (u8*)s1 + 0x140) != 0) {
                    Tmp_198760 t;
                    t.f00 = s1;
                    t.f10 = 2;
                    t.f04 = s1;
                    if (FindNodeForQuery(&t, 0, 0) != 0) {
                        s32 n = s0->f67C + 1;
                        if (!(n < g_gaugeAgentCountLimit)) {
                            n = g_gaugeAgentCountLimit;
                        }
                        s0->f67C = n;
                        if (s0->f698 == 3.4028235e+38f) {
                            s0->f698 = g_gameTime[0] + D_0026A838;
                        }
                    }
                }
            }
        }
    }
    UpdateAgent(s1, f);
}

u32 func_00198858(void) { return 0; }

ASM_FUNC(func_00198860);

void func_00198920(GaugeCountedObject* self)
{
    ResolveObjectLinks(self, 3, g_gaugeCountedObjectLinks);
    StartPlacedObject(self);
    C18* p = (C18*)FindFirstObjectByIdGathered(self->world, 5, 0x18, 0);
    if (p != 0) {
        p->f684 = p->f684 + 1;
    }
}
