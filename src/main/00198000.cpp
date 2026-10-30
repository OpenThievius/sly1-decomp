// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Actor_198980 { u8 pad0[0x554]; s32 flag554; };

void func_001B7968(void* self);

void func_00198980(Actor_198980* self)
{
    func_001B7968(self);
    self->flag554 = 1;
}

struct Actor_198A88 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x55C - 0x18];
    s32 n55C;
    void* arr560[4];
    s32 n570;
    void* arr574[1];
};

void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);

void func_00198A88(Actor_198A88* self)
{
    s32 i;

    func_001249A8(self);
    for (i = 0; i < self->n55C; i++) {
        void* r = func_0015A448(self->f14, self->arr560[i], self);
        if (r != 0) {
            self->arr574[self->n570++] = r;
        }
    }
}

typedef s32 (*VFn_198B28)(void* self);
struct Actor_198B28 {
    VFn_198B28* vtbl;
    u8 pad0[0x558 - 4];
    s32 flag558;
    u8 pad1[0x570 - 0x55C];
    s32 n570;
    void* arr574[1];
};

void func_00124A48(void* self);
s32 func_0012C9A8(void* node);
void func_00182ED8(void* node);

void func_00198B28(Actor_198B28* self)
{
    s32 i;

    func_00124A48(self);
    for (i = 0; i < self->n570; i++) {
        void* node = self->arr574[i];
        if (func_0012C9A8(node)) {
            self->flag558 = 1;
        }
        func_00182ED8(node);
    }
    if (self->vtbl[76](self) == 0) {
        self->vtbl[7](self);
    }
}

typedef void (*VFn_198DA8)(void* self);

struct Actor_198DA8 {
    VFn_198DA8* vtbl;
    u8 pad_04[0x570 - 4];
    s32 count_570;
    void* items_574[1];
};

void func_0012C8F8(void* item, s32 a, f32 x, s32 b, f32 y, s32 c);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00198DA8(Actor_198DA8* self)
{
    VFn_198DA8 fn = self->vtbl[7];
    fn(self);
    s32 i = self->count_570;
    i--;
    for (; i >= 0; i--) {
        (void)func_0012C8F8(self->items_574[i], 0, 0.0f, 1, 1.0f, 0);
    }
    self->vtbl[78](self);
    (void)func_001837E0(self, 2, 0, 0);
}

typedef void (*VFn_198E58)(void* self, void* msg);

struct Msg_198E58 {
    s32 kind;
    void* owner;
    u8 pad_08[0x50 - 8];
};

struct Target_198E58 {
    VFn_198E58* vtbl;
};

struct Actor_198E58 {
    u8 pad_00[0x584];
    Target_198E58* target_584;
};

void func_00198E58(Actor_198E58* self)
{
    Target_198E58* t = self->target_584;
    if (t != 0) {
        Msg_198E58 msg;
        msg.kind = 1;
        msg.owner = self;
        t->vtbl[31](t, &msg);
    }
}

struct Actor_198E98 {
    u8 pad_00[0x554];
    s32 slot_554;
};

s32 func_00182FC8(void* self);

s32 func_00198E98(Actor_198E98* self)
{
    if (func_00182FC8(self)) {
        return (self->slot_554 != 0) ? 1 : 2;
    }
    return 0;
}

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

u32 func_00198858(void) { return 0; }

struct Queue_00198ED8 {
    u8 pad[0x55C];
    s32 count;
    void* items[1];
};

void func_00198ED8(Queue_00198ED8* queue, void* item)
{
    queue->items[queue->count++] = item;
}

typedef void (*VFn_198EF8)(void* self, void* other);

struct Msg_198EF8 {
    u8 pad_00[8];
    s32 key_08;
};

struct Ctx_198EF8 {
    VFn_198EF8* vtbl;
    u8 pad_04[0x2230 - 4];
    Msg_198EF8* watched_2230;
};

struct Actor_198EF8 {
    u8 pad_00[0x570];
    s32 count_570;
    s32 ids_574[5];
    s32 marks_588[4];
    s32 done_598;
};

extern Ctx_198EF8* D_00262E10;

void func_00127378(Actor_198EF8* self, s32 msg, Msg_198EF8* m);

void func_00198EF8(Actor_198EF8* self, s32 msg, Msg_198EF8* m)
{
    (void)func_00127378(self, msg, m);
    if (msg == 5) {
        for (s32 i = 0; i < self->count_570; i++) {
            if (m->key_08 == self->ids_574[i]) {
                self->marks_588[i] = 1;
            }
        }
        Ctx_198EF8* g = D_00262E10;
        if (g != 0) {
            if (m == g->watched_2230) {
                g->vtbl[28](g, self);
                self->done_598 = 1;
            }
        }
    }
}

s32 func_001300E8(void* obj, s32 kind);

s32 func_00198FB0(void* unused, void* obj)
{
    if (func_001300E8(obj, 8) != 0 || func_001300E8(obj, 0x3B) != 0) {
        return 1;
    }
    return 0;
}

void* func_001929F8();
s32 func_00182F40(void* e, void* b);

struct Rec_199000 {
    u8 pad0[0x18];
    void* f18;
};

struct Elem_199000 {
    u8 pad0[0x4];
    void* f4;
    u8 pad1[0x40 - 0x8];
};

struct Owner_199000 {
u8 pad0[0x59C];
    s32 f59C;
};

void func_00199000(Owner_199000* self, Elem_199000* elems, s32 idx)
{
    Rec_199000* r = (Rec_199000*)func_001929F8();
    if (r->f18 == 0) return;
    {
        s32 one = 1;
        Elem_199000* e = (Elem_199000*)((u8*)elems + ((one - idx) << 6));
        if (func_00182F40(e->f4, r->f18) != 0) {
            self->f59C = one;
        }
    }
}

struct Obj_001990A8 { u8 pad[0x5A0]; s32 value; };

void func_001990A8(Obj_001990A8* obj)
{
    s32 value = obj->value;
    func_001BA130(obj);
    obj->value = value;
}

struct Flags_00199380 {
    u8 pad[0x2D0];
    u32 flags;
};

void func_00199380(Flags_00199380* flags, u32 bit)
{
    flags->flags = 1 << (bit + 1);
}

struct Queue_00199398 {
    u8 pad[0x2DC];
    u32 count;
    void* items[1];
};

void func_00199398(Queue_00199398* queue, void* item)
{
    u32 count = queue->count;
    if (count < 8) {
        queue->items[count] = item;
        queue->count = count + 1;
    }
}

struct Manager_001993F0 { u8 pad[0x2300]; s32 count; };
struct Obj_001993F0 { u8 pad[0x14]; Manager_001993F0* manager; u8 pad2[0x5A0 - 0x18]; s32 index; };

void func_001993F0(Obj_001993F0* obj)
{
    func_00198980(obj);
    obj->index = obj->manager->count++;
}

struct Obj_001994C8 { u8 pad[0x5A0]; s32 value; };

void func_001994C8(Obj_001994C8* obj)
{
    s32 value = obj->value;
    func_001BA130(obj);
    obj->value = value;
}

struct Bits_199C10 { u8 pad[0x5A0]; s32 index; };

extern u8* D_002623C8;

void func_00199C10(Bits_199C10* self, s32* out)
{
    s32 n = self->index;
    s32 byte = n / 8;
    s32 bit = n & 7;
    u8 b = (D_002623C8 + byte)[0x68];
    s32 mask = 1;
    mask <<= bit;
    *out = (b & mask) != 0;
}

void func_00199C58(void)
{
    func_001B7F78();
}

extern u8* D_002623C0;
void func_00199FF0(u32 value)
{
    *(u32*)(D_002623C0 + 0x19F0) = value;
}

struct Rec_19A088 { s32 flags; u8 rest[0x74]; };
struct Sys_19A088 { u8 pad0[0x19D8]; s32 cur19D8; };


void func_0019A088(s32 index)
{
    if (index == -1) index = ((Sys_19A088*)D_002623C0)->cur19D8;
    u8* base = (u8*)D_002623C0 + (index * 0x44C + 0x10);
    Rec_19A088* p = (Rec_19A088*)base;
    Rec_19A088* end = (Rec_19A088*)(base + 0x438);
    do {
        p->flags |= 1;
        p++;
    } while ((s32)p < (s32)end);
    *(s32*)(base + 0x448) |= 0x1F;
}

struct Obj_19A0F0 { u8 pad0[0x30]; s32 f30; };
extern Obj_19A0F0 D_00275BC0;
void func_0019A088(s32 index);
void func_001E5278(s32 mode);

void func_0019A0F0()
{
    for (s32 i = 0; i < 6; i++) func_0019A088(i);
    if (D_00275BC0.f30 == 2) func_001E5278(0);
}

struct Obj_19A148 { u8 pad0[0x644]; s32 f644; u8 pad1[0x4]; s32 f64C; };
void func_001921A8(Obj_19A148* self);

void func_0019A148(Obj_19A148* self)
{
    func_001921A8(self);
    self->f64C = -1;
    self->f644 = -1;
}

struct Obj_19A178 { s32 f0; s32 f4; s32 f8; };
extern s32 D_00275710;
s32 func_0015A418(s32 a, s32 b, s32 c, s32 d);
void func_00182ED8(s32 a);
s32 func_001B6290(s32 a, s32 b, s32 c, s32 d);

void func_0019A178(Obj_19A178* self, s32 x)
{
    self->f4 = func_0015A418(D_00275710, 0x101, 0x37A, self->f0);
    func_00182ED8(self->f4);
    self->f8 = func_001B6290(self->f4, self->f0, x, 0);
}

struct __attribute__((aligned(16))) Quad_19A520 { s32 a, b, c, d; };
struct Blk_19A520 { Quad_19A520 q[8]; };

struct Src_19A520 {
    u8 pad0[0x580];
    Blk_19A520 blk580;
    u8 pad1[4];
    s32 f604;
};

struct Glob_19A520 {
    u8 pad0[0x19EC];
    s32 f19EC;
};

struct Actor_19A520 {
    u8 pad0[0x580];
    Blk_19A520 blk580;
    u8 pad1[4];
    s32 f604;
    u8 pad2[0x614 - 0x608];
    void* f614;
    u8 pad3[0x648 - 0x618];
    void* f648;
    u8 pad4[0x7D8 - 0x64C];
    s32 n7D8;
    void* arr7DC[1];
};

void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0016EC88(void* p);
s32 func_001602A0(void);
void func_00160578(s32 value);
void* func_0015A448(void* a, s32 code, void* c);

extern u8 D_00262C70[];

void func_0019A520(Actor_19A520* self, s32 flag)
{
    s32 r;
    s32 flags;
    void* a;
    s32 n;

    func_001B6568(self->f614, &r);
    if (r == -1) {
        func_001B6598(self->f614, &r);
    }
    if (flag != 0) {
        if (r != 0x38F) {
            func_001B64D8(self->f614, 0x385);
        }
        func_0016EC88(D_00262C70);
        flags = ((Glob_19A520*)D_002623C0)->f19EC;
        if ((flags & 8) == 0) {
            a = func_0015A448((void*)D_00275710, 0x39A, self);
        } else {
            if ((flags & 0x10) != 0) {
                goto tail;
            }
            a = func_0015A448((void*)D_00275710, 0x39B, self);
        }
        if (a != 0) {
            n = self->n7D8;
            self->arr7DC[n] = a;
            self->n7D8 = n + 1;
        }
tail:
        a = self->f648;
        if (a != 0) {
            n = self->n7D8;
            self->arr7DC[n] = a;
            self->n7D8 = n + 1;
        }
        if (D_00262E10 != 0) {
            self->blk580 = ((Src_19A520*)D_00262E10)->blk580;
            self->f604 = ((Src_19A520*)D_00262E10)->f604;
        }
    } else {
        if (r != 0x38F) {
            func_001B64D8(self->f614, 0x384);
        }
        self->n7D8 = 0;
        if ((func_001602A0() & 4) != 0) {
            func_00160578(4);
        }
    }
}

struct Record_0019AD30 { u32 count; void* items[1]; };
struct List_0019AD30 { u8 pad[0x658]; Record_0019AD30 records[1]; };
void func_0019AD30(List_0019AD30* list, u32 index, void* item)
{
    Record_0019AD30* record = (Record_0019AD30*)((u8*)list + 0x658 + index * 0x2C);
    u32 count = record->count;
    if (count < 4) {
        record->items[count] = item;
        record->count = count + 1;
    }
}

struct Obj_0019AF38 { u8 pad[0x14]; u8* owner; };


void func_0019AF38(Obj_0019AF38* obj)
{
    func_00182D48(obj);
    func_00152470(obj->owner + 0x1C90, obj);
}

struct Obj_0019AF70 { u8 pad[0x14]; u8* owner; };


void func_0019AF70(Obj_0019AF70* obj)
{
    func_00182ED0(obj);
    func_00152600(obj->owner + 0x1C90, obj);
}

struct Obj_0019AFA8 { u8 pad[0x14]; void* owner; u8 pad2[0x3C]; s32 status; s32 result; };


void func_0019AFA8(Obj_0019AFA8* obj)
{
    func_00182C58(obj);
    if (obj->status != -1)
        obj->result = (s32)func_0015A418(obj->owner, 4, obj->status, obj);
}

struct __attribute__((packed)) Field8_19AFF0 { s64 bits; };
struct Obj_19AFF0 {
    u8 pad0[0x38];
    Field8_19AFF0 f38;
};

void func_001830D8(void* self);

void func_0019AFF0(Obj_19AFF0* self)
{
    Field8_19AFF0 tmp;

    tmp = self->f38;
    func_001830D8(self);
    self->f38 = tmp;
}

struct Obj_0019B1E0 { u8 pad[0x14]; u8* owner; };


void func_0019B1E0(Obj_0019B1E0* obj)
{
    func_001B7A98(obj);
    func_00152470(obj->owner + 0x1C60, obj);
}

struct Obj_0019B218 { u8 pad[0x14]; u8* owner; };


void func_0019B218(Obj_0019B218* obj)
{
    func_001B7B78(obj);
    func_00152600(obj->owner + 0x1C60, obj);
}

struct Obj_0019C3D0 { u8 pad[0x14]; u8* owner; };


void func_0019C3D0(Obj_0019C3D0* obj)
{
    func_00182D48(obj);
    func_00152470(obj->owner + 0x1C6C, obj);
}

struct Obj_0019C408 { u8 pad[0x14]; u8* owner; };


void func_0019C408(Obj_0019C408* obj)
{
    func_00182ED0(obj);
    func_00152600(obj->owner + 0x1C6C, obj);
}

struct Obj_0019C440 { u8 pad[0x34]; s32 first, second; };

void func_0019C440(Obj_0019C440* obj)
{
    func_00182C18(obj);
    obj->second = -1;
    obj->first = -1;
}

struct Vec_0019CE28 { u8 pad[0x54]; f32 x, y, z; };
void func_0019CE28(Vec_0019CE28* value, f32 x, f32 y, f32 z)
{
    value->x = x;
    value->y = y;
    value->z = z;
}

struct Val_0019D468 { u8 pad[4]; f32 value; };
int func_0019D468(Val_0019D468** a, Val_0019D468** b)
{
    Val_0019D468* left = *a;
    Val_0019D468* right = *b;
    if (right->value < left->value) return -1;
    if (left->value < right->value) return 1;
    return ((s32)left - (s32)right) >> 7;
}

extern u32 D_00604788;
extern u32 D_00261990;

void func_0019D930(void)
{
    if (!D_00604788) {
        D_00604788 = 1;
        func_00144848((void*)D_00261990);
    }
}

extern u8 D_002622A8[];
extern u8 D_00212160[];
extern u8 D_00215C50[];

void func_0019DA30(void)
{
    func_0015EAE0(D_002622A8, D_00212160, D_00215C50);
}

extern u8 D_002622A8[];
extern u8 D_00212160[];
extern u8 D_00215C50[];
extern u32 D_00604788;



void func_0019DAD8(void)
{
    func_0019D860();
    func_0019D968();
    func_0015EAE0(D_002622A8, D_00212160, D_00215C50);
    D_00604788 = 0;
}

extern u8 D_002622A8[];
extern u8 D_00212160[];
extern u8 D_00215C50[];




void func_0019DB20(void)
{
    func_0019D860();
    func_0019D930();
    func_0019D968();
    func_0015EAE0(D_002622A8, D_00212160, D_00215C50);
}

extern u8 D_002622A8[];
extern u8 D_00215C60[];
extern u8 D_00217348[];




void func_0019DB68(void)
{
    func_0019D860();
    func_0019D930();
    func_0019D968();
    func_0015EAE0(D_002622A8, D_00215C60, D_00217348);
}

struct A_0019E158 { u8 pad[0x554]; f32 value; };
struct B_0019E158 { u8 pad[0x1E8]; f32 value; };
void func_0019E158(A_0019E158* a, B_0019E158* b)
{
    a->value = b->value;
}

void func_0019E418(void) {}

struct Counter_0019EC20 { u8 pad[8]; s32 value; };
void func_0019EC20(Counter_0019EC20* counter)
{
    counter->value++;
}

void func_0019ECE0(void* value, void* enabled)
{
    if (enabled) func_0019EBE8(value);
}


struct Obj_0019F8E8 { u8 pad[0x44]; s32 value; };

void func_0019F8E8(void* obj, void* arg)
{
    Obj_0019F8E8* value = *(Obj_0019F8E8**)arg;
    func_001831E8((void*)D_00275710, (u8*)obj + 0x118, value->value, arg);
}



void func_0019F918(void* obj, void* a1, void* a2)
{
    func_001831E8((void*)D_00275710, (u8*)obj + 0x118, a1, a2);
}



void func_0019F950(void* obj, void* a1, void* a2)
{
    func_00183238((void*)D_00275710, (u8*)obj + 0x118, a1, a2);
}

void func_0019FCE8(void* value, u32 enabled)
{
    func_0019F9D0(value, enabled < 1);
}

extern u8 D_0026A8E0[];

struct Obj_198920 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x684 - 0x18];
    s32 f684;
};

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_0015A838(void* a, s32 b, s32 c, void* d);

void func_00198920(Obj_198920* self)
{
    func_00124DF8(self, 3, D_0026A8E0);
    func_00124A48(self);
    Obj_198920* p = (Obj_198920*)func_0015A838(self->f14, 5, 0x18, 0);
    if (p != 0) {
        p->f684 = p->f684 + 1;
    }
}

extern u8 D_00261420[];

struct Obj_199070 {
    u8 pad0[0x5A0];
    void* f5A0;
};

void func_00198980(void* self);
void* func_00140FF8(void* p);

void func_00199070(Obj_199070* self)
{
    func_00198980(self);
    self->f5A0 = func_00140FF8(D_00261420);
}

struct Owner_199428 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x5AC - 0x18];
    s32 n5AC;
    void* arr5B0;
};

void func_001989B0(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void* func_0018D500(s32 size);
void func_00182ED8(s32 a);
extern u8 D_0026A948[];

void func_00199428(Owner_199428* self)
{
    func_001989B0(self);
    s32 i = 0x318;
    func_00124DF8(self, 1, D_0026A948);
    self->arr5B0 = func_0018D500(0x80);
    while (i < 0x338) {
        s32 r = (s32)func_0015A418(self->f14, 1, i, self);
        if (r == 0) {
            break;
        }
        s32 count = self->n5AC;
        i++;
        ((s32*)self->arr5B0)[count] = r;
        self->n5AC = count + 1;
        func_00182ED8(r);
    }
}

struct Vec4_19BE08 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Src_19BE08 { u8 pad[0x20]; Vec4_19BE08 q20; Vec4_19BE08 q30; };
struct Local_19BE08 { s32 mode; u8 pad[0xC]; Vec4_19BE08 qa; Vec4_19BE08 qb; u8 pad2[0x20]; };
typedef void (*VFn_19BE08)(void* self, void* arg);
struct Obj_19BE08 { VFn_19BE08* vtbl; };

void func_0019C1C0(void* self, s32 mode);

s32 func_0019BE08(u8* self, Src_19BE08* src)
{
    Local_19BE08 loc;
    if (*(s32*)(self + 0x550) != 3) {
        func_0019C1C0(self, 3);
        Obj_19BE08* obj = *(Obj_19BE08**)(self + 0x5F8);
        if (obj != 0) {
            loc.mode = 6;
            loc.qb = src->q20;
            loc.qa = src->q30;
            obj->vtbl[31](obj, &loc);
        }
    }
    return 1;
}

struct Actor_1990E0 {
    u8 pad_00[0x5A0];
    s32 slot_5A0;
};

extern u8 D_00261420[];
s32 func_00198E98(void* self);
s32 func_00141008(void* table, s32 index);

s32 func_001990E0(Actor_1990E0* self)
{
    s32 r = func_00198E98(self);
    if (r == 1) {
        r = func_00141008(D_00261420, self->slot_5A0) ? 0 : r;
    }
    return r;
}

struct Actor_199138 {
    u8 pad_00[0x5A0];
    s32 slot_5A0;
};

extern u8 D_00261420[];
void func_00141040(void* table, s32 index);
void func_00198DA8(void* self);

void func_00199138(Actor_199138* self)
{
    func_00141040(D_00261420, self->slot_5A0);
    func_00198DA8(self);
}

typedef void (*VFn_199AF0)(void* self);
struct Obj_199AF0 { VFn_199AF0* vtbl; };

void func_00199AF0(void* p)
{
    Obj_199AF0* o = (Obj_199AF0*)p;
    o->vtbl[77](o);
}

void func_001C72A0(void* self);

void func_00198090(void* self)
{
    func_001C72A0(self);
}

struct __attribute__((aligned(16))) Quad_1984B8 { s32 a, b, c, d; };
typedef void (*VFn_1984B8)(void* self, void* ctx);
struct Actor_1984B8 { VFn_1984B8* vtbl; u8 pad0[0x150 - 4]; Quad_1984B8 q150; u8 pad1[0x724 - 0x160]; s32 kind; };

void* func_001925F0(void);
void func_00197A08(void* h, void* self);
void func_001C9008(void* self, void* arg);

void func_001984B8(void* self, void* arg)
{
    Actor_1984B8* actor = (Actor_1984B8*)self;
    if (actor->kind == 0x10) {
        void* h = func_001925F0();
        func_00197A08(h, self);
        Quad_1984B8 ctx = actor->q150;
        ctx.c = 0;
        actor->vtbl[36](self, &ctx);
    }
    func_001C9008(self, arg);
}

struct Actor_198530 { u8 pad0[0x724]; s32 kind; };

void func_001C91C8(void* self);
void func_001C8920(void* self);

void func_00198530(void* self)
{
    Actor_198530* actor = (Actor_198530*)self;
    func_001C91C8(self);
    if (actor->kind == 0x10) {
        func_001C8920(self);
    }
}

struct Req_1986E8 {
    s32 a;
    s32 b;
};

struct Self_1986E8 {
    u8 pad[0xC10];
    s32 slot;
};

void func_001C9DE0(void* self, s32 code, void* req);

void func_001986E8(Self_1986E8* self, s32 code, Req_1986E8* req)
{
    func_001C9DE0(self, code, req);
    if (code != 10) {
        if (code == 11) {
            if (req->b == (s32)self) {
                self->slot = 0;
            }
        }
    } else {
        if (req->b == (s32)self) {
            self->slot = req->a;
        }
    }
}

struct Ev_199C78 { u8 pad[0xC]; s32 flags; };
typedef void (*VFnA_199C78)(void* self, s32 a);
typedef void (*VFnB_199C78)(void* self);
struct Obj_199C78 { void** vtbl; };

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_001BC320(void* self, Ev_199C78* ev);

s32 func_00199C78(void* a0, Ev_199C78* a1)
{
    Obj_199C78* self = (Obj_199C78*)a0;
    if (a1->flags & 0x8) {
        ((VFnA_199C78)self->vtbl[25])(self, 0);
        func_001B9AE0(self, 0, 0, 3, 0);
    }
    func_001BC320(self, a1);
    if (a1->flags & 0x10) {
        ((VFnB_199C78)self->vtbl[77])(self);
    }
    return 1;
}

struct __attribute__((packed)) Q_19B250 { s64 v; };
struct Obj_19B250 { u8 pad[0x600]; Q_19B250 q; };

void func_001BA130(void* self);

void func_0019B250(void* a0)
{
    Obj_19B250* self = (Obj_19B250*)a0;
    Q_19B250 tmp;
    tmp = self->q;
    func_001BA130(self);
    self->q = tmp;
}

extern u8 D_0026A918[];

void func_001289C0(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_00199170(void* self)
{
    func_001289C0(self);
    func_00124DF8(self, 1, D_0026A918);
}

extern u8 D_0026A928[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_001991A8(void* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, D_0026A928);
}

extern u8 D_0026A938[];

void func_001289C0(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_001991E0(void* self)
{
    func_001289C0(self);
    func_00124DF8(self, 1, D_0026A938);
}

typedef void (*VFn_199F38)(void* self);

struct Obj_199F38 {
    VFn_199F38* vtbl;
};

struct Holder_199F38 {
    u8 pad0[0x18];
    Obj_199F38* sub;
};

extern u8 D_0026C948[];

s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_00199B18(void* obj);
s32 func_001300E8(void* node, s32 kind);

void func_00199F38(void)
{
    void* arr[0x100];
    s32 i = func_0015A4F0((void*)D_00275710, 0x105, 0x2E, 0, 0x100, arr) - 1;
    if (i >= 0) {
        void** p = (void**)(i * 4 + (s32)arr);
        do {
            func_00199B18(*p);
            if (((Holder_199F38*)*p)->sub != 0) {
                if (func_001300E8(((Holder_199F38*)*p)->sub, 0x20) != 0) {
                    Obj_199F38* s = ((Holder_199F38*)*p)->sub;
                    s->vtbl[7](s);
                }
            }
            i--;
            p--;
        } while (i >= 0);
    }
    VFn_199F38* vt = *(VFn_199F38**)D_0026C948;
    vt[14](D_0026C948);
}

struct Ctx_19A000 {
    u8 pad0[0x19F0];
    s32 f19F0;
};

extern u8* D_002623C0;
s32 func_001602A0(void);

s32 func_0019A000(s32 bits)
{
    s64 mask = 0xF000;
    mask <<= 16;
    mask |= 0xFFFF;
    if ((((Ctx_19A000*)D_002623C0)->f19F0 & mask) == mask) {
        return 0;
    }
    if (func_001602A0() & 2) {
        return 0;
    }
    Ctx_19A000* c = (Ctx_19A000*)D_002623C0;
    s64 v = c->f19F0 | bits;
    s32 r = 1;
    if ((v & mask) ^ mask) {
        r = 0;
    }
    return r;
}

struct Self_19B038 {
    u8 pad0[0x55C];
    f32 f55C;
    u8 pad1[0x608 - 0x560];
    f32 f608;
    f32 f60C;
    u8 pad2[0x664 - 0x610];
    s32 f664;
};

extern f32 D_0026185C[];
void func_001B7968(void* self);
f32 func_001EAB48(f32 a, f32 b, f32 c);

void func_0019B038(Self_19B038* self)
{
    func_001B7968(self);
    self->f60C = 1.0f;
    self->f608 = 0.5f;
    self->f55C = func_001EAB48(*(f32*)D_0026185C + 3.0f, 1.0f, 2.5f);
    self->f664 = -1;
}

struct Obj_19B0A0 {
    u8 pad0[0x14];
    u8* f14;
    u8 pad1[0x564 - 0x18];
    s32 f564;
    void* f568[16];
    s32 f5A8;
    void* f5AC[19];
};

extern u8 D_0026AB90[];

void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void* func_0015A480(void* self, s32 kind, void* arg);
void func_00182ED8(void* node);

void func_0019B0A0(Obj_19B0A0* self)
{
    s32 k = 0x269;
    func_001BAC30(self);
    func_00159478((u8*)self + 0x5F8, self);
    func_00124DF8(self, 1, D_0026AB90);
    for (; k < 0x288; k++) {
        void* node = func_0015A480(self->f14, k, self);
        if (node != 0) {
            func_00182ED8(node);
            if (k < 0x279) {
                self->f568[self->f564++] = node;
            } else {
                self->f5AC[self->f5A8++] = node;
            }
        }
    }
}

extern u8 D_0026ABA0[];

struct __attribute__((aligned(16))) Quad_19B188 { s32 a, b, c, d; };
struct Obj_19B188 { u8 pad0[0x140]; Quad_19B188 q140; u8 pad1[0x400]; s32 f550; u8 pad2[0xFC]; Quad_19B188 q650; };

void func_0019C1C0(void* self, s32 mode);
void func_00124DF8(void* self, s32 n, void* table);
void func_00124A48(void* self);

void func_0019B188(void* self)
{
    Obj_19B188* o = (Obj_19B188*)self;
    func_00124DF8(self, 1, D_0026ABA0);
    func_00124A48(self);
    o->f550 = -1;
    func_0019C1C0(self, 1);
    o->q650 = o->q140;
}

struct Obj_19A1E0;
struct VObj_19A1E0 { s32 (**vtbl)(VObj_19A1E0*, Obj_19A1E0*); };
struct Ent_19A1E0 {
    s32 count;
    s32 keys[4];
    s32 n;
    VObj_19A1E0* list[4];
    s32 pick;
};
struct Sub_19A1E0 { u8 pad[0x1CE4]; Obj_19A1E0* f1CE4; };
struct Obj_19A1E0 {
    u8 pad0[0x14];
    Sub_19A1E0* f14;
    u8 pad1[0x5F8];
    s32 f610;
    s32 f614;
    u8 pad2[4];
    u8 f61C[0x28];
    s32 f644;
    s32 f648;
    s32 f64C;
    VObj_19A1E0* f650;
    u8 pad3[4];
    Ent_19A1E0 ents[6];
    u8 pad4[0x760 - 0x658 - 6 * 0x2C];
    s32 f760;
    s32 f764;
};
struct Sys_19A1E0 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; u8 pad1[0x10]; u32 f19F0; };
struct Pad_19A1E0 { u32 flags; u8 pad[0x74]; };
struct Flags_19A1E0 { u32 flags; };

extern u8 D_0026AA50[];
extern Pad_19A1E0* D_002623C4;
extern s32 D_0026A9E0[];

void func_00124A48(Obj_19A1E0* o);
void func_00124DF8(Obj_19A1E0* o, s32 n, u8* t);
void func_0019A178(void* p, s32 x);
s32 func_001B6290(s32 a, Obj_19A1E0* b, s32 c, s32 d);
void func_001B64D8(s32 a, s32 b);
VObj_19A1E0* func_0015A448(Sub_19A1E0* a, s32 b, Obj_19A1E0* c);
s32 func_001EAA70(s32 a, s32 b);
void func_00160D30(s32* p);

void func_0019A1E0(Obj_19A1E0* o)
{
    u32 i;
    func_00124A48(o);
    func_00124DF8(o, 0x1A, D_0026AA50);
    for (i = 0; i < 3; i++)
        func_0019A178(o->f61C + i * 12, 0x390);
    s32 h = func_001B6290(o->f610, o, 0x384, 1);
    o->f764 = -1;
    o->f614 = h;
    if (((Flags_19A1E0*)D_002623C8)->flags & 4) {
        func_001B64D8(h, 0x38F);
        return;
    }
    o->f14->f1CE4 = o;
    for (s32 e = 0; e < 6; e++) {
        Ent_19A1E0* en = &o->ents[e];
        for (s32 k = 0; k < en->count; k++) {
            VObj_19A1E0* r = func_0015A448(o->f14, en->keys[k], o);
            if (r) {
                en->list[en->n++] = r;
            }
        }
        if (en->n > 0)
            en->pick = func_001EAA70(0, en->n - 1);
    }
    o->f648 = (s32)func_0015A448(o->f14, o->f644, o);
    o->f650 = func_0015A448(o->f14, o->f64C, o);
    if (o->f650)
        o->f650->vtbl[0x6C / 4](o->f650, o);
    if (((((Sys_19A1E0*)D_002623C0)->f19D8 << 8) | ((Sys_19A1E0*)D_002623C0)->f19DC) == 3) {
        o->f760 = 1;
    } else {
        func_00160D30(&o->f760);
        if (o->f760 & 0xF000FFFFl) {
            s32 cnt = 0;
            Pad_19A1E0* p = D_002623C4;
            Pad_19A1E0* end = p + 9;
            do {
                if (p->flags & 4)
                    cnt++;
                p++;
            } while (p < end);
            if (cnt != 2)
                o->f760 = 0;
            if (o->f760 & 0xF000FFFFl) {
                o->f764 = 0;
                goto lookup;
            }
        }
        o->f760 = 2;
        if (((Sys_19A1E0*)D_002623C0)->f19F0 & 2) {
            do {
                o->f760 = o->f760 << 1;
            } while ((o->f760 & 0xF000FFFFl) && (((Sys_19A1E0*)D_002623C0)->f19F0 & o->f760));
        }
        o->f760 &= (s32)0xF000FFFF;
    }
    if ((o->f760 & 0xF000FFFFl) == 0)
        return;
    o->f764 = 0;
lookup:
    if (D_0026A9E0[0] != (s32)o->f760) {
        do {
            o->f764++;
            if (o->f764 >= 0x1C) {
                o->f764 = -1;
                return;
            }
        } while (D_0026A9E0[o->f764] != (s32)o->f760);
    }
    if (o->f764 >= 0x1C)
        o->f764 = -1;
}

struct Actor_1982A0 { u8 pad0[0x724]; s32 kind; u8 pad1[0xC10 - 0x728]; s32 fC10; };

s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);

s32 func_001982A0(void* self)
{
    Actor_1982A0* actor = (Actor_1982A0*)self;
    s32 r;

    switch (actor->kind) {
    case 2:
        if (func_001C96B8(self) == 0) {
            r = 4;
            break;
        }
        r = func_001C8010(self);
        break;
    case 0x10:
        r = 0x10;
        if (actor->fC10 != 0) {
            r = 0;
        }
        break;
    default:
        r = func_001C8010(self);
        break;
    }
    return r;
}

struct Actor_199218 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x2D0 - 0x18];
    s32 n2D0;
    void* f2D4;
    void* f2D8;
    s32 n2DC;
    s32 arr2E0[8];
    s32 n300;
    void* arr304[8];
};

struct Elem_199218 {
    u8 pad0[0x2D0];
    void* f2D0;
    void* f2D4;
};

struct Gl_199218 {
    u8 pad0[0x448];
    s32 n448;
};


void func_00124A48(void* self);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001B64D8(void* p, s32 n);

void func_00199218(Actor_199218* self)
{
    func_00124A48(self);
    self->n300 = func_0015A4F0(self->f14, 1, 0x5C, self, 8, self->arr304);
    s32 i;
    Elem_199218* e;
    for (i = 0; i < self->n2DC; i++) {
        e = (Elem_199218*)func_0015A418(self->f14, 4, self->arr2E0[i], self);
        if (e != 0) {
            u32 k = self->n300;
            if (k < 8) {
                self->arr304[k] = (void*)e;
                self->n300 = k + 1;
            }
        }
    }
    s32 s4 = (((Gl_199218*)D_002623C4)->n448 & self->n2D0) ? 0x22F : 0x22E;
    for (i = 0; i < self->n300; i++) {
        e = (Elem_199218*)self->arr304[i];
        e->f2D4 = func_001B6290(e->f2D0, e, -1, 0);
        func_001B64D8(e->f2D4, s4);
    }
    self->f2D8 = func_001B6290(self->f2D4, self, -1, 0);
    func_001B64D8(self->f2D8, s4);
}

// NEAR: global kept in $a1 not $t0 and the mask shift scheduled early; call and loop sequence match

typedef void (*VFn_199B18)(void* self);

struct Actor_199B18 {
    VFn_199B18* vtbl;
    u8 pad0[0x570 - 4];
    s32 n570;
    void* arr574[1];
    u8 pad1[0x5A0 - 0x578];
    s32 n5A0;
};

struct Mgr_199B18 {
    u8 pad0[0x64];
    s32 n64;
    u8 bits[1];
};


void* func_0012C8F8(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00199B18(Actor_199B18* self)
{
    self->vtbl[7](self);
    s32 n = self->n5A0;
    Mgr_199B18* m = (Mgr_199B18*)D_002623C8;
    s32 idx = n / 8;
    u8 cur = m->bits[idx];
    s32 mask = 1 << (n & 7);
    if (!(cur & mask)) {
        m->bits[idx] = cur | mask;
        m->n64 = m->n64 + 1;
    }
    s32 i = self->n570;
    i--;
    while (i >= 0) {
        func_0012C8F8(self->arr574[i], 0, 1, 0, 0.0f, 1.0f);
        i--;
    }
    func_001837E0(self, 2, 0, 0);
}

struct Arg_001993C0;
s32 func_001781E0(Arg_001993C0* a, s32 v);

void func_001993C0(s32 a0) {
    if ((s32)D_00262E10 != 0) {
        (void)func_001781E0((Arg_001993C0*)D_00262E10, a0);
    }
}

struct Self_19AF00 { u8 pad0[0x4C]; f32 f4C; u8 pad1[0x54 - 0x50]; s32 s54; };

extern f32 D_0024C8C4;
void func_00182C18(Self_19AF00* self);

void func_0019AF00(Self_19AF00* self)
{
    func_00182C18(self);
    self->s54 = -1;
    self->f4C = D_0024C8C4;
}

struct Obj_199500;
typedef void (*VFn_199500)(Obj_199500* self);
struct Vt_199500 { u8 pad[0x1C]; VFn_199500 f1C; };
struct Obj_199500 {
    Vt_199500* vtbl;
    u8 pad04[0x5A0 - 4];
    s32 idx;
    f32 f5A4;
    f32 f5A8;
    u8 pad5AC[8];
    f32 f5B4;
    f32 f5B8;
};
struct Step_199500 { u8 pad[0x64]; s32 count; u8 bits[1]; };

void func_00198B28(Obj_199500* self);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_001EAA70(s32 a, s32 b);
extern f32 D_0026A958[];
extern f32 D_0026A960[];
extern s32 D_00275C34;

void func_00199500(Obj_199500* self)
{
    func_00198B28(self);
    self->f5B8 = func_001EAAE0(-3.1415927f, 3.1415927f);
    self->f5B4 = func_001EAAE0(D_0026A958[0], D_0026A958[1]);
    if (func_001EAA70(0, 1)) {
        self->f5B4 = -self->f5B4;
    }
    s32 one = 1;
    self->f5A8 = self->f5A8 * func_001EAAE0(D_0026A960[0], D_0026A960[1]);
    self->f5A4 = func_001EAAE0(0.0f, self->f5A8 + self->f5A8);
    if (((Step_199500*)D_002623C8)->bits[self->idx / 8] & (one << (self->idx & 7))) {
        self->vtbl->f1C(self);
    }
    if (D_00275C34) {
        if (func_001EAA70(0, 100) < 20) {
            Step_199500* st = (Step_199500*)D_002623C8;
            u8* b = st->bits;
            u8* p = b + self->idx / 8;
            s32 m = one << (self->idx & 7);
            if (*p & m) {
                *p = *p & ~m;
                st->count--;
            }
            self->vtbl->f1C(self);
        }
    }
}

struct Obj_19AD68;
struct VT_19AD68 {
    u8 pad[0x70];
    void (*f70)(Obj_19AD68* o, void* arg);
    u8 pad2[0];
};
struct Obj_19AD68 { VT_19AD68* vt; };
struct VT2_19AD68 { u8 pad[0x18]; void (*f18)(void* o); };
struct Obj2_19AD68 { VT2_19AD68* vt; };

struct Self_19AD68 {
    u8 pad0[0x14];
    u8* f14;
    u8 pad1[0x614 - 0x18];
    void* f614;
    u8 pad2[0x650 - 0x618];
    Obj_19AD68* f650;
    u8 pad3[0x760 - 0x654];
    s32 f760;
    s32 f764;
    Obj2_19AD68* f768[1];
    u8 pad4[0x7D8 - 0x76C];
    s32 f7D8;
    Obj2_19AD68* f7DC[1];
};

void func_001B64D8(Self_19AD68* p, s32 n);
void func_001E9570(Self_19AD68* q);
s32 func_001602A0(void);
void func_001604B8(s32 mode);
void func_0018C7F8(Self_19AD68* p);
Obj2_19AD68* func_0015A418(u8* host, s32 a1, s32 a2, Self_19AD68* ctx);

extern s32 D_00270454;
extern u8 D_00264A40[];
struct G_19AD68 { u8 pad[0x19EC]; s32 f19EC; s32 f19F0; };
struct H_19AD68 { u8 pad[0x43C]; s32 f43C; };

void func_0019AD68(Self_19AD68* self)
{
    func_001B64D8((Self_19AD68*)self->f614, 0x38E);
    if (self->f650 != 0) {
        self->f650->vt->f70(self->f650, self);
        self->f650 = 0;
        self->f7D8 = 0;
    } else {
        self->f7D8 = 0;
    }
    if (D_00270454 != 0) {
        func_001E9570((Self_19AD68*)&D_00275BC0);
    }
    if ((self->f760 & 0xF000FFFFl) != 0) {
        s32 id;
        Obj2_19AD68* o;
        H_19AD68* h = (H_19AD68*)D_002623C4;
        G_19AD68* g = (G_19AD68*)D_002623C0;
        u32* c = (u32*)D_002623C8;
        h->f43C += 1;
        g->f19F0 |= self->f760;
        *(s32*)(self->f14 + 0x1CE4) = 0;
        *c |= 4;
        {
            s32 v = g->f19EC;
            if ((v & 8) == 0) {
                g->f19EC = v | 8;
            } else if ((v & 0x10) == 0) {
                g->f19EC = v | 0x10;
            }
        }
        if ((func_001602A0() & 4) != 0) {
            func_001604B8(4);
        }
        id = 0x37E;
        if (self->f760 != 1) {
            id = 0x37F;
            func_0018C7F8((Self_19AD68*)D_00264A40);
        }
        o = func_0015A418(self->f14, 0x101, id, self);
        if (o != 0) {
            o->vt->f18(o);
        }
        if (self->f764 >= 0) {
            Obj2_19AD68* e = self->f768[self->f764];
            if (e != 0) {
                self->f7DC[self->f7D8++] = e;
            }
        }
    }
}
