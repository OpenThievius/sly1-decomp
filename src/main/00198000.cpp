// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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


void func_00199C58(void)
{
    func_001B7F78();
}

extern u8* D_002623C0;
void func_00199FF0(u32 value)
{
    *(u32*)(D_002623C0 + 0x19F0) = value;
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

extern void* D_00275710;
struct Obj_0019F8E8 { u8 pad[0x44]; s32 value; };

void func_0019F8E8(void* obj, void* arg)
{
    Obj_0019F8E8* value = *(Obj_0019F8E8**)arg;
    func_001831E8(D_00275710, (u8*)obj + 0x118, value->value, arg);
}

extern void* D_00275710;

void func_0019F918(void* obj, void* a1, void* a2)
{
    func_001831E8(D_00275710, (u8*)obj + 0x118, a1, a2);
}

extern void* D_00275710;

void func_0019F950(void* obj, void* a1, void* a2)
{
    func_00183238(D_00275710, (u8*)obj + 0x118, a1, a2);
}


void func_0019FCE8(void* value, u32 enabled)
{
    func_0019F9D0(value, enabled < 1);
}
