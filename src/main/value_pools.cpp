// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "entry_pool.h"
#include "script_value.h"

// The pools that follow value.cpp: the entry pool, the keyed values and the five payload pools,
// 0x11C128-0x11CBB8. Its .data, the payload pools' slot counts, starts where value.cpp's ends
// (0x25C2F0) and ends where the IOP command file's starts (0x25C340).

s32 g_vectorAPayloadCapacity = 256;
s32 g_matrixPayloadCapacity = 256;
s32 g_vectorBPayloadCapacity = 64;
s32 g_pairPayloadCapacity = 64;
s32 g_triplePayloadCapacity[16] = { 32 };

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void* AllocateZeroedFrontMemory(s32 size);

void* AllocateFrontMemory(s32 bytes);
void* GetPoolEntry(EntryPool* p, s32 index);

void InitEntryPool(EntryPool* p, s32 count, s32 size)
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

void ShutDownEntryPool(EntryPool* p)
{
}

// The header of every entry of an entry pool, 8 bytes before the entry's payload: the link of the
// free or live list, and the state word the collector marks (MarkPoolEntryUsed) and the sweep tests
// (ReleaseDeadPoolEntries).
struct PoolEntryHeader {
    PoolEntryHeader* next;  // 0x00: the next entry of the free or live list
    s32 state;              // 0x04: 1 once marked, 0 when cleared (ClearPoolLiveStates)
};

extern u8 g_markStacks[];
struct MarkStacks;
void CollectScriptPools(MarkStacks* w);
void* GetPoolEntryPayload(PoolEntryHeader* entry);

void* PopPoolFreeEntry(EntryPool* self)
{
    if (self->freeList == 0) {
        CollectScriptPools((MarkStacks*)g_markStacks);
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

void* TakePoolEntry(EntryPool* self)
{
    void* result = PopPoolFreeEntry(self);
    FillMemory(result, 0, self->stride - 8);
    return result;
}


void* GetPoolEntry(EntryPool* self, s32 index)
{
    return self->mem + index * self->stride;
}

void MarkPoolLiveEnd(EntryPool* self)
{
    self->liveMark = self->liveHead;
}

void ClearPoolLiveStates(EntryPool* self)
{
    PoolEntryHeader* node = (PoolEntryHeader*)self->liveHead;
    if (node == 0) return;
    do {
        node->state = 0;
        node = node->next;
    } while (node != 0);
}

typedef void (*Cb_11C2E8)(void* p);

void ReleaseDeadPoolEntries(EntryPool* self)
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

void* GetPoolEntryPayload(PoolEntryHeader* entry)
{
    return (u8*)entry + 8;
}

PoolEntryHeader* GetPoolEntryHeader(u8* base)
{
    return (PoolEntryHeader*)(base - 8);
}

s32 IsPoolEntryUnmarked(void* payload)
{
    return GetPoolEntryHeader((u8*)payload)->state == 0;
}

void MarkPoolEntryUsed(void* payload)
{
    GetPoolEntryHeader((u8*)payload)->state = 1;
}

extern s32 D_0025C268;
extern s32 D_0025C288;
extern s32 D_0025C2A8;
extern s32 D_0025C2C8;
extern s32 D_0025C2E8;
R11B008Key* NewKeyedValue(void);
void CopyKeyedValueChain(R11B008Key* a, R11B008Key* b, s32 c);

void CopyKeyedValueChain(R11B008Key* a, R11B008Key* b, s32 c)
{
    b->key = a->key;
    CloneScriptValue(&a->value, &b->value, c);
    if (a->next != 0) {
        R11B008Key* n = NewKeyedValue();
        CopyKeyedValueChain(a->next, n, c);
        b->next = n;
    }
}

void* TakePoolEntry(EntryPool* pool);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

R11B008Key* NewKeyedValue(void)
{
    R11B008Key* n = (R11B008Key*)TakePoolEntry(&g_keyedValuePool);
    FillMemory(n, 0, 16);
    InitScriptValue(&n->value);
    n->value.tag = -1;
    return n;
}

void DestroyKeyedValue(R11B008Key* a)
{
    DestroyScriptValue(&a->value, 2);
}

extern s32 g_vectorAPayloadPool;
struct Pool6C;
void* PopFreeSlot(Pool6C* pool);
void* PopZeroedFreeSlot(Pool6C* pool);
void CollectScriptPools(MarkStacks* w);

void* AcquireVectorAPayload(void)
{
    void* p = PopFreeSlot((Pool6C*)&g_vectorAPayloadPool);
    if (p != 0) {
        FillMemory(p, 0, g_vectorAPayloadPool);
    } else {
        CollectScriptPools((MarkStacks*)g_markStacks);
        p = PopZeroedFreeSlot((Pool6C*)&g_vectorAPayloadPool);
    }
    return p;
}

extern u8* D_0062C55C;
extern u8* g_payloadRefCounts[];

s32 AddRefVectorAPayload(void* payload)
{
    u8* p = g_payloadRefCounts[0] + ((u32)((u8*)payload - D_0062C55C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void PushFreeSlot(Pool6C* list, void* item);

void ReleaseVectorAPayload(void* payload)
{
    u8* pool = (u8*)&g_vectorAPayloadPool;
    u8* p = g_payloadRefCounts[0] + ((u32)((u8*)payload - *(u8**)(pool + 4)) >> 4);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        PushFreeSlot((Pool6C*)pool, payload);
    }
}

LINKER_REMNANT(func_0011C610);

void ShutDownEntryPool(EntryPool* p);
void ShutDownPayloadPools(void);
extern u8 g_matrixPayloadPool[];
extern "C" void* FillMemory(void* p, s32 value, s32 size);

void* AcquireMatrixPayload(void)
{
    void* s0 = PopFreeSlot((Pool6C*)g_matrixPayloadPool);
    if (s0 != 0) {
        FillMemory(s0, 0, *(u32*)g_matrixPayloadPool);
    } else {
        CollectScriptPools((MarkStacks*)g_markStacks);
        s0 = PopZeroedFreeSlot((Pool6C*)g_matrixPayloadPool);
    }
    return s0;
}

extern u8* D_0062C56C;

s32 AddRefMatrixPayload(void* payload)
{
    u8* p = g_payloadRefCounts[1] + ((u32)((u8*)payload - D_0062C56C) >> 6);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void ReleaseMatrixPayload(void* payload)
{
    u8* base = g_matrixPayloadPool;
    s32 idx = (s32)((u32)((u8*)payload - *(u8**)(base + 4)) >> 6);
    u8* p = (u8*)(*(s32*)((u8*)g_payloadRefCounts + 4) + idx);
    *p = *p - 1;
    if (*p == 0) {
        PushFreeSlot((Pool6C*)base, payload);
    }
}

void FreeMatrixPayload(void* item)
{
    PushFreeSlot((Pool6C*)g_matrixPayloadPool, item);
}

extern u8 g_vectorBPayloadPool[];

void* AcquireVectorBPayload(void)
{
    void* s0 = PopFreeSlot((Pool6C*)g_vectorBPayloadPool);
    if (s0 != 0) {
        FillMemory(s0, 0, *(u32*)g_vectorBPayloadPool);
    } else {
        CollectScriptPools((MarkStacks*)g_markStacks);
        s0 = PopZeroedFreeSlot((Pool6C*)g_vectorBPayloadPool);
    }
    return s0;
}

extern u8* D_0062C57C;

s32 AddRefVectorBPayload(void* payload)
{
    u8* p = g_payloadRefCounts[2] + ((u32)((u8*)payload - D_0062C57C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void ReleaseVectorBPayload(void* payload)
{
    u8* pool = g_vectorBPayloadPool;
    u8* p = g_payloadRefCounts[2] + ((u32)((u8*)payload - *(u8**)(pool + 4)) >> 4);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        PushFreeSlot((Pool6C*)pool, payload);
    }
}

LINKER_REMNANT(func_0011C850);

extern u8 g_pairPayloadPool[];

void* AcquirePairPayload(void)
{
    void* s0 = PopFreeSlot((Pool6C*)g_pairPayloadPool);
    if (s0 != 0) {
        FillMemory(s0, 0, *(u32*)g_pairPayloadPool);
    } else {
        CollectScriptPools((MarkStacks*)g_markStacks);
        s0 = PopZeroedFreeSlot((Pool6C*)g_pairPayloadPool);
    }
    return s0;
}

extern u8* D_0062C58C;

s32 AddRefPairPayload(void* payload)
{
    u8* p = g_payloadRefCounts[3] + ((u32)((u8*)payload - D_0062C58C) >> 3);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void ReleasePairPayload(void* payload)
{
    u8* pool = g_pairPayloadPool;
    u8* p = g_payloadRefCounts[3] + ((u32)((u8*)payload - *(u8**)(pool + 4)) >> 3);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        PushFreeSlot((Pool6C*)pool, payload);
    }
}

LINKER_REMNANT(func_0011C960);

extern s32 g_triplePayloadPool[];
struct TriplePayloadSlot;
void* PopFreeSlot(Pool6C* pool);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void CollectScriptPools(MarkStacks* w);
void* PopZeroedFreeSlot(Pool6C* pool);

TriplePayloadSlot* AcquireTriplePayload(void)
{
    TriplePayloadSlot* p = (TriplePayloadSlot*)PopFreeSlot((Pool6C*)g_triplePayloadPool);
    if (p) {
        FillMemory(p, 0, g_triplePayloadPool[0]);
    } else {
        CollectScriptPools((MarkStacks*)g_markStacks);
        p = (TriplePayloadSlot*)PopZeroedFreeSlot((Pool6C*)g_triplePayloadPool);
    }
    return p;
}

extern u8* D_0062C59C;
extern u8* g_triplePayloadRefCounts;

s32 AddRefTriplePayload(void* payload)
{
    u32 n = 12;
    u8* p = g_triplePayloadRefCounts + (u32)((u8*)payload - D_0062C59C) / n;
    s32 v = *p + 1;
    *p = v;
    return v;
}

// A slot pool's head: the slot size, then the first slot's address (func_0011CA20 indexes by it).
struct SlotPool {
    s32 slotSize;           // 0x00
    u8* origin;             // 0x04
};

void PushFreeSlot(Pool6C* list, void* item);

void ReleaseTriplePayload(void* payload)
{
    SlotPool* t = (SlotPool*)((u8*)&g_triplePayloadPool);
    u32 index = (u32)((u8*)payload - t->origin) / 12;
    u8* cell = g_triplePayloadRefCounts + index;
    *cell = (u8)(*cell - 1);
    if (*cell != 0) {
        return;
    }
    PushFreeSlot((Pool6C*)t, payload);
}

extern u8* D_0027B304;
extern u8* D_0027B308;
extern u8* D_0027B30C;
void InitSlotPool(Pool6C* s, s32 size, s32 count);

struct PayloadPoolInit {
    static void Load(void* buf, s32 size, s32* id, u8** out)
    {
        InitSlotPool((Pool6C*)buf, size, *id);
        *out = (u8*)AllocateZeroedFrontMemory(*id);
    }
};

void InitPayloadPools(void)
{
    PayloadPoolInit::Load(((u8*)&g_vectorAPayloadPool), 0x10, &g_vectorAPayloadCapacity, &g_payloadRefCounts[0]);
    PayloadPoolInit::Load(g_matrixPayloadPool, 0x40, &g_matrixPayloadCapacity, &D_0027B304);
    PayloadPoolInit::Load(g_vectorBPayloadPool, 0x10, &g_vectorBPayloadCapacity, &D_0027B308);
    PayloadPoolInit::Load(g_pairPayloadPool, 0x08, &g_pairPayloadCapacity, &D_0027B30C);
    PayloadPoolInit::Load(((u8*)&g_triplePayloadPool), 0x0C, g_triplePayloadCapacity, &g_triplePayloadRefCounts);
}

void ShutDownPayloadPools(void)
{
}
