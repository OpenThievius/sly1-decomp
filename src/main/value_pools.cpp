// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "entry_pool.h"
#include "script_value.h"

// The pools that follow value.cpp: the entry pool, the keyed values and the five payload pools,
// 0x11C128-0x11CBB8. Its .data, the payload pools' slot counts, starts where value.cpp's ends
// (0x25C2F0) and ends where the IOP command file's starts (0x25C340).

s32 D_0025C2F0 = 256;
s32 D_0025C2F4 = 256;
s32 D_0025C2F8 = 64;
s32 D_0025C2FC = 64;
s32 D_0025C300[16] = { 32 };

void func_001F5C0C(void* dst, s32 value, u32 size);
void* func_0018D5C0(s32 size);

void* func_0018D500(s32 bytes);
void* func_0011C288(EntryPool* p, s32 index);

void func_0011C128(EntryPool* p, s32 count, s32 size)
{
    p->stride = count + 8;
    p->count = size;
    p->mem = (u8*)AllocateFrontMemory((count + 8) * size);
    void* node = GetPoolEntry(p, 0);
    p->freeList = node;
    s32 i = 1;
    if (i < size) {
        void* prev;
        do {
            prev = node;
            node = GetPoolEntry(p, i);
            i++;
            *(void**)prev = node;
        } while (i < size);
    }
    *(void**)node = 0;
    p->live = 0;
    p->high = 0;
}

void func_0011C1D0(void* p)
{
}

// The header of every entry of an entry pool, 8 bytes before the entry's payload: the link of the
// free or live list, and the state word the collector marks (MarkPoolEntryUsed) and the sweep tests
// (ReleaseDeadPoolEntries).
struct PoolEntryHeader {
    PoolEntryHeader* next;  // 0x00: the next entry of the free or live list
    s32 state;              // 0x04: 1 once marked, 0 when cleared (ClearPoolLiveStates)
};

extern u8 D_00259F38[];
void func_0011AB58(void* p);
void* func_0011C3B8(void* base);

void* func_0011C1D8(EntryPool* self)
{
    if (self->freeList == 0) {
        CollectScriptPools(g_markStacks);
    }
    PoolEntryHeader* n = (PoolEntryHeader*)self->freeList;
    if (n != 0) {
        self->freeList = n->next;
        n->next = (PoolEntryHeader*)self->liveHead;
        self->liveHead = n;
        return GetPoolEntryPayload(n);
    }
    return 0;
}

// Newly matched US functions from the small-function wave.
extern void* func_0011C1D8(void*);



void* func_0011C240(void* self)
{
    void* result = PopPoolFreeEntry(self);
    func_001F5C0C(result, 0, *(s32*)self - 8);
    return result;
}


void* func_0011C288(EntryPool* self, s32 index)
{
    return self->mem + index * self->stride;
}

void func_0011C2A0(EntryPool* self)
{
    self->liveMark = self->liveHead;
}

void func_0011C2B0(EntryPool* self)
{
    PoolEntryHeader* node = (PoolEntryHeader*)self->liveHead;
    if (node == 0) return;
    do {
        node->state = 0;
        node = node->next;
    } while (node != 0);
}

typedef void (*Cb_11C2E8)(void* p);

void func_0011C2E8(EntryPool* self)
{
    PoolEntryHeader* prev = (PoolEntryHeader*)&self->liveHead;
    PoolEntryHeader* cur = (PoolEntryHeader*)self->liveHead;
    if (cur != 0 && cur != self->liveMark) {
        prev = cur;
        for (;;) {
            cur = cur->next;
            if (cur == 0 || cur == self->liveMark) {
                break;
            }
            prev = cur;
        }
    }
    PoolEntryHeader* s2 = prev;
    cur = s2->next;
    while (cur != 0) {
        if (cur->state != 0) {
            prev = cur;
        } else {
            prev->next = cur->next;
            cur->next = (PoolEntryHeader*)self->freeList;
            self->freeList = cur;
            if (self->removeCallback != 0) {
                ((Cb_11C2E8)self->removeCallback)(GetPoolEntryPayload(cur));
            }
        }
        cur = prev->next;
    }
    self->liveMark = s2->next;
}

void* func_0011C3B8(u8* base)
{
    return base + 8;
}

PoolEntryHeader* func_0011C3C0(u8* base)
{
    return (PoolEntryHeader*)(base - 8);
}

PoolEntryHeader* func_0011C3C0(void);

s32 func_0011C3C8(void)
{
    return GetPoolEntryHeader()->state == 0;
}

void func_0011C3F0(u8* base)
{
    GetPoolEntryHeader(base)->state = 1;
}

extern s32 D_0025C268;
extern s32 D_0025C288;
extern s32 D_0025C2A8;
extern s32 D_0025C2C8;
extern s32 D_0025C2E8;
R11B008Key* func_0011C498(void);
void func_0011C418(R11B008Key* a, R11B008Key* b, s32 c);

void func_0011C418(R11B008Key* a, R11B008Key* b, s32 c)
{
    b->key = a->key;
    CloneScriptValue(&a->value, &b->value, c);
    if (a->next != 0) {
        R11B008Key* n = NewKeyedValue();
        CopyKeyedValueChain(a->next, n, c);
        b->next = n;
    }
}

void* func_0011C240(void* pool);
void func_001F5C0C(void* dst, s32 value, u32 size);

R11B008Key* func_0011C498(void)
{
    R11B008Key* n = (R11B008Key*)TakePoolEntry(&g_keyedValuePool);
    func_001F5C0C(n, 0, 16);
    InitScriptValue(&n->value);
    n->value.tag = -1;
    return n;
}

void func_0011C4E8(R11B008Key* a)
{
    DestroyScriptValue(&a->value, 2);
}

extern s32 D_0062C558;
void* func_001B5EA0(void* pool);
void* func_001B5EE0(void* pool);
void func_0011AB58(void* arg);

void* func_0011C508(void)
{
    void* p = PopFreeSlot(&g_vectorAPayloadPool);
    if (p != 0) {
        func_001F5C0C(p, 0, g_vectorAPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        p = PopZeroedFreeSlot(&g_vectorAPayloadPool);
    }
    return p;
}

extern u32 D_0062C55C;
extern u8* D_0027B300[];

s32 func_0011C580(u32 addr)
{
    u8* p = g_payloadRefCounts[0] + ((addr - D_0062C55C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void func_001B5F28(void* list, void* item);

void func_0011C5B0(u32 addr)
{
    u8* pool = (u8*)&g_vectorAPayloadPool;
    u8* p = g_payloadRefCounts[0] + ((addr - *(u32*)(pool + 4)) >> 4);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        PushFreeSlot(pool, (void*)addr);
    }
}

LINKER_REMNANT(func_0011C610);

void func_0011C1D0(void* p);
void func_0011CBB0(void);
extern u8 D_0062C568[];
void func_001F5C0C(void* p, s32 zero, u32 count);

void* func_0011C618(void)
{
    void* s0 = PopFreeSlot(g_matrixPayloadPool);
    if (s0 != 0) {
        func_001F5C0C(s0, 0, *(u32*)g_matrixPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        s0 = PopZeroedFreeSlot(g_matrixPayloadPool);
    }
    return s0;
}

extern u32 D_0062C56C;

s32 func_0011C690(u32 addr)
{
    u8* p = g_payloadRefCounts[1] + ((addr - D_0062C56C) >> 6);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void func_0011C6C0(s32 a)
{
    u8* base = g_matrixPayloadPool;
    s32 idx = (s32)((u32)(a - *(s32*)(base + 4)) >> 6);
    u8* p = (u8*)(*(s32*)((u8*)g_payloadRefCounts + 4) + idx);
    *p = *p - 1;
    if (*p == 0) {
        PushFreeSlot(base, (void*)a);
    }
}

void func_0011C720(void* item)
{
    PushFreeSlot(g_matrixPayloadPool, item);
}

extern u8 D_0062C578[];

void* func_0011C748(void)
{
    void* s0 = PopFreeSlot(g_vectorBPayloadPool);
    if (s0 != 0) {
        func_001F5C0C(s0, 0, *(u32*)g_vectorBPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        s0 = PopZeroedFreeSlot(g_vectorBPayloadPool);
    }
    return s0;
}

extern u32 D_0062C57C;

s32 func_0011C7C0(u32 addr)
{
    u8* p = g_payloadRefCounts[2] + ((addr - D_0062C57C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void func_0011C7F0(u32 addr)
{
    u8* pool = g_vectorBPayloadPool;
    u8* p = g_payloadRefCounts[2] + ((addr - *(u32*)(pool + 4)) >> 4);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        PushFreeSlot(pool, (void*)addr);
    }
}

LINKER_REMNANT(func_0011C850);

extern u8 D_0062C588[];

void* func_0011C858(void)
{
    void* s0 = PopFreeSlot(g_pairPayloadPool);
    if (s0 != 0) {
        func_001F5C0C(s0, 0, *(u32*)g_pairPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        s0 = PopZeroedFreeSlot(g_pairPayloadPool);
    }
    return s0;
}

extern u32 D_0062C58C;

s32 func_0011C8D0(u32 addr)
{
    u8* p = g_payloadRefCounts[3] + ((addr - D_0062C58C) >> 3);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void func_0011C900(u32 addr)
{
    u8* pool = g_pairPayloadPool;
    u8* p = g_payloadRefCounts[3] + ((addr - *(u32*)(pool + 4)) >> 3);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        PushFreeSlot(pool, (void*)addr);
    }
}

LINKER_REMNANT(func_0011C960);

extern s32 D_0062C598[];
struct Pool_11C968;
Pool_11C968* func_001B5EA0(s32* pool);
void func_001F5C0C(Pool_11C968* p, s32 zero, s32 size);
void func_0011AB58(u8* p);
Pool_11C968* func_001B5EE0(s32* pool);

Pool_11C968* func_0011C968(void)
{
    Pool_11C968* p = PopFreeSlot(g_triplePayloadPool);
    if (p) {
        func_001F5C0C(p, 0, g_triplePayloadPool[0]);
    } else {
        CollectScriptPools(g_markStacks);
        p = PopZeroedFreeSlot(g_triplePayloadPool);
    }
    return p;
}

extern s32 D_0062C59C;
extern u8* D_0027B310;

s32 func_0011C9E0(u32 offset)
{
    u32 n = 12;
    u8* p = g_triplePayloadRefCounts + (offset - D_0062C59C) / n;
    s32 v = *p + 1;
    *p = v;
    return v;
}

struct Table_0011CA20 {
    s32 pad_00;
    u32 origin;
};

void func_001B5F28(Table_0011CA20* t, u8* item);

void func_0011CA20(u8* p)
{
    Table_0011CA20* t = (Table_0011CA20*)((u8*)&g_triplePayloadPool);
    u32 index = ((u32)p - t->origin) / 12;
    u8* cell = g_triplePayloadRefCounts + index;
    *cell = (u8)(*cell - 1);
    if (*cell != 0) {
        return;
    }
    PushFreeSlot(t, p);
}

struct Dst_11CA90 { u8 pad[4]; };
extern u8* D_0027B304;
extern u8* D_0027B308;
extern u8* D_0027B30C;
void func_001B5DD0(Dst_11CA90* p, s32 size, s32 val);

struct Init_11CA90 {
    static void Load(void* buf, s32 size, s32* id, u8** out)
    {
        func_001B5DD0((Dst_11CA90*)buf, size, *id);
        *out = (u8*)func_0018D5C0(*id);
    }
};

void func_0011CA90(void)
{
    Init_11CA90::Load(((u8*)&g_vectorAPayloadPool), 0x10, &g_vectorAPayloadCapacity, &g_payloadRefCounts[0]);
    Init_11CA90::Load(g_matrixPayloadPool, 0x40, &g_matrixPayloadCapacity, &D_0027B304);
    Init_11CA90::Load(g_vectorBPayloadPool, 0x10, &g_vectorBPayloadCapacity, &D_0027B308);
    Init_11CA90::Load(g_pairPayloadPool, 0x08, &g_pairPayloadCapacity, &D_0027B30C);
    Init_11CA90::Load(((u8*)&g_triplePayloadPool), 0x0C, g_triplePayloadCapacity, &g_triplePayloadRefCounts);
}

void func_0011CBB0(void)
{
}
