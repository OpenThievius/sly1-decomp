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

void* FillMemory(void* p, s32 value, s32 size);
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

void ShutDownEntryPool(void* p)
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
void CollectScriptPools(void* p);
void* GetPoolEntryPayload(void* base);

void* PopPoolFreeEntry(EntryPool* self)
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
extern void* PopPoolFreeEntry(void*);



void* TakePoolEntry(void* self)
{
    void* result = PopPoolFreeEntry(self);
    FillMemory(result, 0, *(s32*)self - 8);
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

void* GetPoolEntryPayload(u8* base)
{
    return base + 8;
}

PoolEntryHeader* GetPoolEntryHeader(u8* base)
{
    return (PoolEntryHeader*)(base - 8);
}

PoolEntryHeader* GetPoolEntryHeader(void);

s32 IsPoolEntryUnmarked(void)
{
    return GetPoolEntryHeader()->state == 0;
}

void MarkPoolEntryUsed(u8* base)
{
    GetPoolEntryHeader(base)->state = 1;
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

void* TakePoolEntry(void* pool);
void* FillMemory(void* p, s32 value, s32 size);

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
void* PopFreeSlot(void* pool);
void* PopZeroedFreeSlot(void* pool);
void CollectScriptPools(void* arg);

void* AcquireVectorAPayload(void)
{
    void* p = PopFreeSlot(&g_vectorAPayloadPool);
    if (p != 0) {
        FillMemory(p, 0, g_vectorAPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        p = PopZeroedFreeSlot(&g_vectorAPayloadPool);
    }
    return p;
}

extern u32 D_0062C55C;
extern u8* g_payloadRefCounts[];

s32 AddRefVectorAPayload(u32 addr)
{
    u8* p = g_payloadRefCounts[0] + ((addr - D_0062C55C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void PushFreeSlot(void* list, void* item);

void ReleaseVectorAPayload(u32 addr)
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

void ShutDownEntryPool(void* p);
void ShutDownPayloadPools(void);
extern u8 g_matrixPayloadPool[];
void* FillMemory(void* p, s32 value, s32 size);

void* AcquireMatrixPayload(void)
{
    void* s0 = PopFreeSlot(g_matrixPayloadPool);
    if (s0 != 0) {
        FillMemory(s0, 0, *(u32*)g_matrixPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        s0 = PopZeroedFreeSlot(g_matrixPayloadPool);
    }
    return s0;
}

extern u32 D_0062C56C;

s32 AddRefMatrixPayload(u32 addr)
{
    u8* p = g_payloadRefCounts[1] + ((addr - D_0062C56C) >> 6);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void ReleaseMatrixPayload(s32 a)
{
    u8* base = g_matrixPayloadPool;
    s32 idx = (s32)((u32)(a - *(s32*)(base + 4)) >> 6);
    u8* p = (u8*)(*(s32*)((u8*)g_payloadRefCounts + 4) + idx);
    *p = *p - 1;
    if (*p == 0) {
        PushFreeSlot(base, (void*)a);
    }
}

void FreeMatrixPayload(void* item)
{
    PushFreeSlot(g_matrixPayloadPool, item);
}

extern u8 g_vectorBPayloadPool[];

void* AcquireVectorBPayload(void)
{
    void* s0 = PopFreeSlot(g_vectorBPayloadPool);
    if (s0 != 0) {
        FillMemory(s0, 0, *(u32*)g_vectorBPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        s0 = PopZeroedFreeSlot(g_vectorBPayloadPool);
    }
    return s0;
}

extern u32 D_0062C57C;

s32 AddRefVectorBPayload(u32 addr)
{
    u8* p = g_payloadRefCounts[2] + ((addr - D_0062C57C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void ReleaseVectorBPayload(u32 addr)
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

extern u8 g_pairPayloadPool[];

void* AcquirePairPayload(void)
{
    void* s0 = PopFreeSlot(g_pairPayloadPool);
    if (s0 != 0) {
        FillMemory(s0, 0, *(u32*)g_pairPayloadPool);
    } else {
        CollectScriptPools(g_markStacks);
        s0 = PopZeroedFreeSlot(g_pairPayloadPool);
    }
    return s0;
}

extern u32 D_0062C58C;

s32 AddRefPairPayload(u32 addr)
{
    u8* p = g_payloadRefCounts[3] + ((addr - D_0062C58C) >> 3);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

void ReleasePairPayload(u32 addr)
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

extern s32 g_triplePayloadPool[];
struct TriplePayloadSlot;
TriplePayloadSlot* PopFreeSlot(s32* pool);
void* FillMemory(void* p, s32 value, s32 size);
void CollectScriptPools(u8* p);
TriplePayloadSlot* PopZeroedFreeSlot(s32* pool);

TriplePayloadSlot* AcquireTriplePayload(void)
{
    TriplePayloadSlot* p = PopFreeSlot(g_triplePayloadPool);
    if (p) {
        FillMemory(p, 0, g_triplePayloadPool[0]);
    } else {
        CollectScriptPools(g_markStacks);
        p = PopZeroedFreeSlot(g_triplePayloadPool);
    }
    return p;
}

extern s32 D_0062C59C;
extern u8* g_triplePayloadRefCounts;

s32 AddRefTriplePayload(u32 offset)
{
    u32 n = 12;
    u8* p = g_triplePayloadRefCounts + (offset - D_0062C59C) / n;
    s32 v = *p + 1;
    *p = v;
    return v;
}

// A slot pool's head: the slot size, then the first slot's address (func_0011CA20 indexes by it).
struct SlotPool {
    s32 slotSize;           // 0x00
    u32 origin;             // 0x04
};

void PushFreeSlot(SlotPool* t, u8* item);

void ReleaseTriplePayload(u8* p)
{
    SlotPool* t = (SlotPool*)((u8*)&g_triplePayloadPool);
    u32 index = ((u32)p - t->origin) / 12;
    u8* cell = g_triplePayloadRefCounts + index;
    *cell = (u8)(*cell - 1);
    if (*cell != 0) {
        return;
    }
    PushFreeSlot(t, p);
}

extern u8* D_0027B304;
extern u8* D_0027B308;
extern u8* D_0027B30C;
void InitSlotPool(SlotPool* p, s32 size, s32 val);

struct PayloadPoolInit {
    static void Load(void* buf, s32 size, s32* id, u8** out)
    {
        InitSlotPool((SlotPool*)buf, size, *id);
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
