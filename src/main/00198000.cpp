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
