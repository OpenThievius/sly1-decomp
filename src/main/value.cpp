// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "entry_pool.h"
#include "script_value.h"
#include "buffered_stream.h"
#include "shapes.h"

// The five pools values are taken from (func_0011C240): func_0011BF70 sets them up, func_0011C040
// empties them all. Built at startup: the compiler's initialiser, constructor and destructor for this
// file are func_0011C0A8, func_0011C0E8 and func_0011C108 (config/us/generated.tsv).
EntryPool g_valueNodePool;
EntryPool g_scopePool;
EntryPool g_keyedValuePool;
EntryPool g_payloadPool;
EntryPool g_propertyRefPool;

// The payloads of tags 0x19 and 0x1A as func_0011B258 copies them (ldl/ldr for the first two
// words: the pool does not align them).
struct PairPayload { U64P xy; };
struct TriplePayload { U64P xy; s32 z; };

void FreeObjectMemory(void* p);
void* AllocateZeroedFrontMemory(s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 CompareMemory(void* a, void* b, s32 n);
void* TakePoolEntry(EntryPool* pool);
void InitEntryPool(EntryPool* pool, s32 size, s32 count);
void ShutDownEntryPool(EntryPool* pool);
R11B008Key* NewKeyedValue(void);
void CopyKeyedValueChain(R11B008Key* src, R11B008Key* dst, s32 zero);
void DestroyKeyedValue(R11B008Key* a);
void InitPayloadPools(void);
void ShutDownPayloadPools(void);
extern u8 g_markStacks[];
struct MarkStacks;
void ResetMarkRoots(MarkStacks* self);
void ShutDownMarkRoots(MarkStacks* stacks);
void ReleaseScriptScope(void);

// The pooled payloads (value_pools.cpp): each tag's allocator, reference and release.
void* AcquireVectorAPayload(void);
void* AcquireMatrixPayload(void);
void* AcquireVectorBPayload(void);
void* AcquirePairPayload(void);
void* AcquireTriplePayload(void);
s32 AddRefVectorAPayload(void* p);
s32 AddRefMatrixPayload(void* p);
s32 AddRefVectorBPayload(void* p);
s32 AddRefPairPayload(void* p);
s32 AddRefTriplePayload(void* p);
void ReleaseVectorAPayload(void* p);
void ReleaseMatrixPayload(void* p);
void ReleaseVectorBPayload(void* p);
void ReleasePairPayload(void* p);
void ReleaseTriplePayload(void* p);

// The stream reader (buffered_stream.cpp).
s32 ReadBufferedU8(BufferedStream* r);
u16 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedS32(BufferedStream* r);
f32 ReadBufferedFloat(BufferedStream* r);
s32 ReadBufferedU32(BufferedStream* r);

extern u32 g_scriptStreamExtras;

void* TakeZeroedPoolEntry(void)
{
    void* p = TakePoolEntry(&g_propertyRefPool);
    FillMemory(p, 0, 12);
    return p;
}

void CopyScriptValueChain(R11B008Node* src, R11B008Node* dst, s32 first)
{
    CloneScriptValue(src, dst, first);
    if (src->next != 0) {
        R11B008Node* copy = NewScriptValueNode();
        CopyScriptValueChain(src->next, copy, first);
        dst->next = copy;
    }
}

R11B008Node* NewScriptValueNode(void)
{
    R11B008Node* node = (R11B008Node*)TakePoolEntry(&g_valueNodePool);
    FillMemory(node, 0, 12);
    InitScriptValue(node);
    node->tag = -1;
    return node;
}

void DestroyScriptValueNode(R11B008Node* self)
{
    DestroyScriptValue(self, 2);
}

void CopyScriptValueRecord(R11AFC8* src, R11AFC8* dst, s32 first)
{
    if (first == 0) {
        first = src->w0;
    }
    dst->w0 = first;
    dst->w4 = src->w4;
    dst->w8 = src->w8;
    dst->wC = src->wC;
    dst->w10 = src->w10;
}

R11AFC8* NewScriptValueRecord(void)
{
    R11AFC8* p = (R11AFC8*)TakePoolEntry(&g_payloadPool);
    FillMemory(p, 0, 0x14);
    return p;
}

ScriptValue* InitScriptValue(ScriptValue* self)
{
    self->tag = -1;
    return self;
}

ScriptValue* CopyConstructScriptValue(ScriptValue* self, const ScriptValue* src)
{
    AddRefScriptValuePayload(src);
    self->tag = src->tag;
    self->i = src->i;
    return self;
}

void DestroyScriptValue(ScriptValue* self, s32 flags)
{
    ReleaseScriptValuePayload(self);
    if (flags & 1) {
        FreeObjectMemory(self);
    }
}

ScriptValue* AssignScriptValue(ScriptValue* self, const ScriptValue* src)
{
    AddRefScriptValuePayload(src);
    ReleaseScriptValuePayload(self);
    self->tag = src->tag;
    self->i = src->i;
    return self;
}

s32 AreScriptValuesEqual(const ScriptValue* a, const ScriptValue* b)
{
    if (a->tag != b->tag)
        return 0;
    switch (a->tag) {
    case 0x15:
        return a->f == b->f;
    case 0x1B: {
        s32 r = 0;
        if (a->p == 0) {
            if (b->p == 0)
                goto yes;
            goto out;
        }
        if (b->p != 0) {
        yes:
            r = 1;
        }
    out:
        return r;
    }
    case 0x17:
        return CompareMemory(a->p, b->p, 0x40) == 0;
    case 0x19: {
        f32* pa = a->v;
        f32* pb = b->v;
        s32 r = 0;
        if (pa[0] == pb[0] && pa[1] == pb[1])
            r = 1;
        return r;
    }
    case 0x16:
    case 0x18:
    case 0x1A: {
        f32* pa = a->v;
        f32* pb = b->v;
        s32 r = 0;
        if (pa[0] == pb[0] && pa[1] == pb[1] && pa[2] == pb[2])
            r = 1;
        return r;
    }
    case 0x14:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
        return a->i == b->i;
    }
    return 1;
}

void CloneScriptValue(const ScriptValue* src, ScriptValue* dst, s32 first)
{
    dst->tag = src->tag;
    switch (src->tag) {
    case 0x1E: {
        R11B008Node* n = NewScriptValueNode();
        CopyScriptValueChain(src->node, n, first);
        dst->node = n;
        break;
    }
    case 0x16: {
        Quad16* p = (Quad16*)AcquireVectorAPayload();
        *p = *(Quad16*)src->p;
        (void)AddRefVectorAPayload(p);
        dst->p = p;
        break;
    }
    case 0x17: {
        Mat4A* p = (Mat4A*)AcquireMatrixPayload();
        *p = *(Mat4A*)src->p;
        (void)AddRefMatrixPayload(p);
        dst->p = p;
        break;
    }
    case 0x18: {
        Quad16* p = (Quad16*)AcquireVectorBPayload();
        *p = *(Quad16*)src->p;
        (void)AddRefVectorBPayload(p);
        dst->p = p;
        break;
    }
    case 0x19: {
        PairPayload* p = (PairPayload*)AcquirePairPayload();
        *p = *(PairPayload*)src->p;
        (void)AddRefPairPayload(p);
        dst->p = p;
        break;
    }
    case 0x1A: {
        TriplePayload* p = (TriplePayload*)AcquireTriplePayload();
        *p = *(TriplePayload*)src->p;
        (void)AddRefTriplePayload(p);
        dst->p = p;
        break;
    }
    case 0x1F: {
        R11AFC8* r = NewScriptValueRecord();
        CopyScriptValueRecord(src->rec, r, first);
        dst->rec = r;
        break;
    }
    default:
        dst->p = src->p;
        break;
    }
}

void ReleaseScriptValuePayload(ScriptValue* self)
{
    switch (self->tag) {
    case 0x16: ReleaseVectorAPayload(self->p); break;
    case 0x17: ReleaseMatrixPayload(self->p); break;
    case 0x18: ReleaseVectorBPayload(self->p); break;
    case 0x19: ReleasePairPayload(self->p); break;
    case 0x1A: ReleaseTriplePayload(self->p); break;
    }
}

void AddRefScriptValuePayload(const ScriptValue* self)
{
    switch (self->tag) {
    case 0x16: AddRefVectorAPayload(self->p); break;
    case 0x17: AddRefMatrixPayload(self->p); break;
    case 0x18: AddRefVectorBPayload(self->p); break;
    case 0x19: AddRefPairPayload(self->p); break;
    case 0x1A: AddRefTriplePayload(self->p); break;
    }
}

void SetScriptValueTag(ScriptValue* self, s32 tag)
{
    ReleaseScriptValuePayload(self);
    self->tag = tag;
}

void SetScriptValueInt(ScriptValue* self, s32 value)
{
    ReleaseScriptValuePayload(self);
    self->i = value;
    self->tag = 0x14;
}

void SetScriptValueFloat(ScriptValue* self, f32 value)
{
    ReleaseScriptValuePayload(self);
    self->f = value;
    self->tag = 0x15;
}

void SetScriptValueBool(ScriptValue* self, s32 flag)
{
    ReleaseScriptValuePayload(self);
    if (flag != 0)
        self->i = 1;
    else
        self->i = 0;
    self->tag = 0x1B;
}

void SetScriptValuePointer(ScriptValue* self, void* p)
{
    ReleaseScriptValuePayload(self);
    self->p = p;
    self->tag = 0x1C;
}

void SetScriptValueIntB(ScriptValue* self, s32 value)
{
    ReleaseScriptValuePayload(self);
    self->i = value;
    self->tag = 0x1D;
}

void SetScriptValueChain(ScriptValue* self, R11B008Node* node)
{
    ReleaseScriptValuePayload(self);
    self->node = node;
    self->tag = 0x1E;
}

void SetScriptValueRecord(ScriptValue* self, R11AFC8* rec)
{
    ReleaseScriptValuePayload(self);
    self->rec = rec;
    self->tag = 0x1F;
}

void SetScriptValueVectorA(ScriptValue* self, f32* v)
{
    AddRefVectorAPayload(v);
    ReleaseScriptValuePayload(self);
    self->v = v;
    self->tag = 0x16;
}

void SetScriptValueMatrix(ScriptValue* self, f32* v)
{
    (void)AddRefMatrixPayload(v);
    ReleaseScriptValuePayload(self);
    self->v = v;
    self->tag = 23;
}

void SetScriptValueVectorB(ScriptValue* self, f32* v)
{
    (void)AddRefVectorBPayload(v);
    ReleaseScriptValuePayload(self);
    self->v = v;
    self->tag = 24;
}

void SetScriptValuePair(ScriptValue* self, f32* v)
{
    (void)AddRefPairPayload(v);
    ReleaseScriptValuePayload(self);
    self->v = v;
    self->tag = 25;
}

void SetScriptValueTriple(ScriptValue* self, f32* v)
{
    (void)AddRefTriplePayload(v);
    ReleaseScriptValuePayload(self);
    self->v = v;
    self->tag = 26;
}

void SetScriptValuePointerB(ScriptValue* self, void* p)
{
    ReleaseScriptValuePayload(self);
    self->p = p;
    self->tag = 0x20;
}

void SetScriptValueIntC(ScriptValue* self, s32 value)
{
    ReleaseScriptValuePayload(self);
    self->tag = 0x21;
    self->i = value;
}

ScriptValue* ConvertScriptValueToInt(ScriptValue* out, const ScriptValue* in)
{
    if (in->tag == 0x14) {
        CopyConstructScriptValue(out, in);
    } else {
        ScriptValue tmp;
        InitScriptValue(&tmp);
        SetScriptValueInt(&tmp, (s32)in->f);
        CopyConstructScriptValue(out, &tmp);
        DestroyScriptValue(&tmp, 2);
    }
    return out;
}

ScriptValue* ConvertScriptValueToFloat(ScriptValue* out, const ScriptValue* in)
{
    if (in->tag == 0x15) {
        CopyConstructScriptValue(out, in);
    } else {
        ScriptValue tmp;
        InitScriptValue(&tmp);
        SetScriptValueFloat(&tmp, (f32)in->i);
        CopyConstructScriptValue(out, &tmp);
        DestroyScriptValue(&tmp, 2);
    }
    return out;
}

R11B008Node* ReadScriptValueChain(BufferedStream* rd)
{
    s32 tag = ReadBufferedU8(rd);
    if (tag == 0xFF) {
        return 0;
    }
    s32 flag = tag & 0x80;
    R11B008Node* n = NewScriptValueNode();
    n->tag = tag & 0x7F;
    if (g_scriptStreamExtras) {
        ReadBufferedU16(rd);
        ReadBufferedU16(rd);
        ReadBufferedU16(rd);
        ReadBufferedU16(rd);
        ReadBufferedU16(rd);
    }
    switch (n->tag) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20:
        SetScriptValueInt(n, ReadBufferedS32(rd));
        break;
    case 21:
        SetScriptValueFloat(n, ReadBufferedFloat(rd));
        break;
    case 27:
        SetScriptValueBool(n, ReadBufferedU32(rd));
        break;
    case 32:
        SetScriptValuePointerB(n, (void*)ReadBufferedU32(rd));
        break;
    case 28:
        SetScriptValuePointer(n, (void*)ReadBufferedU32(rd));
        break;
    case 29:
        SetScriptValueIntB(n, ReadBufferedU32(rd));
        break;
    case 22:
    {
        s32 i = 2;
        f32* buf = (f32*)AcquireVectorAPayload();
        f32* p = buf;
        do {
            *p++ = ReadBufferedFloat(rd);
        } while (--i >= 0);
        n->tag = -1;
        SetScriptValueVectorA(n, buf);
    }
        break;
    case 23:
    {
        s32 i = 15;
        f32* buf = (f32*)AcquireMatrixPayload();
        f32* p = buf;
        do {
            *p++ = ReadBufferedFloat(rd);
        } while (--i >= 0);
        n->tag = -1;
        SetScriptValueMatrix(n, buf);
    }
        break;
    case 24:
    {
        s32 i = 2;
        f32* buf = (f32*)AcquireVectorBPayload();
        f32* p = buf;
        do {
            *p++ = ReadBufferedFloat(rd);
        } while (--i >= 0);
        n->tag = -1;
        SetScriptValueVectorB(n, buf);
    }
        break;
    case 25:
    {
        f32* p = (f32*)AcquirePairPayload();
        p[0] = ReadBufferedFloat(rd);
        p[1] = ReadBufferedFloat(rd);
        n->tag = -1;
        SetScriptValuePair(n, p);
    }
        break;
    case 26:
    {
        f32* p = (f32*)AcquireTriplePayload();
        p[0] = ReadBufferedFloat(rd);
        p[1] = ReadBufferedFloat(rd);
        p[2] = ReadBufferedFloat(rd);
        n->tag = -1;
        SetScriptValueTriple(n, p);
    }
        break;
    case 30:
        SetScriptValueChain(n, ReadScriptValueChain(rd));
        break;
    }
    if (flag) {
        n->next = ReadScriptValueChain(rd);
    } else {
        n->next = 0;
    }
    return n;
}

ScriptValue* AddKeyedValue(ScriptValue* out, R11B008List* list, s32 key, const ScriptValue* value)
{
    ScriptValue tmp;
    InitScriptValue(&tmp);
    R11B008Key* node = NewKeyedValue();
    node->key = key;
    (void)AssignScriptValue(&node->value, value);
    node->next = list->head;
    list->head = node;
    SetScriptValueTag(&tmp, 0x22);
    CopyConstructScriptValue(out, &tmp);
    DestroyScriptValue(&tmp, 2);
    return out;
}

ScriptValue* UpdateKeyedValue(ScriptValue* out, R11B008List* list, s32 key, const ScriptValue* value)
{
    ScriptValue tmp;
    R11B008Key* node = list->head;
    while (node != 0) {
        if (node->key == key) {
            InitScriptValue(&tmp);
            (void)AssignScriptValue(&node->value, value);
            SetScriptValueTag(&tmp, 0x22);
            CopyConstructScriptValue(out, &tmp);
            DestroyScriptValue(&tmp, 2);
            goto done;
        }
        node = node->next;
    }
    InitScriptValue(&tmp);
    SetScriptValueTag(&tmp, 0x22);
    CopyConstructScriptValue(out, &tmp);
    DestroyScriptValue(&tmp, 2);
done:
    return out;
}

s32 FindKeyedValue(R11B008List* list, s32 key, ScriptValue* out)
{
    R11B008Key* n = list->head;
    while (n != 0) {
        if (n->key == key) {
            if (out != 0) {
                AssignScriptValue(out, &n->value);
            }
            return 1;
        }
        n = n->next;
    }
    return 0;
}

void CopyKeyedList(R11B008List* self, R11B008List* out)
{
    R11B008Key* copy = NewKeyedValue();
    CopyKeyedValueChain(self->head, copy, 0);
    out->head = copy;
}

R11B008List* NewKeyedList(void)
{
    R11B008List* p = (R11B008List*)AllocateZeroedFrontMemory(4);
    FillMemory(p, 0, 4);
    return p;
}

void InitScriptValuePools(void)
{
    ResetMarkRoots((MarkStacks*)g_markStacks);
    InitEntryPool(&g_valueNodePool, 0xC, 0x2000);
    g_valueNodePool.removeCallback = (void*)DestroyScriptValueNode;
    InitEntryPool(&g_scopePool, 0x1C, 0x190);
    g_scopePool.removeCallback = (void*)ReleaseScriptScope;
    InitEntryPool(&g_keyedValuePool, 0x10, 0x800);
    g_keyedValuePool.removeCallback = (void*)DestroyKeyedValue;
    InitEntryPool(&g_payloadPool, 0x14, 0x800);
    InitPayloadPools();
    InitEntryPool(&g_propertyRefPool, 0xC, 0x80);
}

void ShutDownScriptValuePools(void)
{
    ShutDownEntryPool(&g_valueNodePool);
    ShutDownEntryPool(&g_scopePool);
    ShutDownEntryPool(&g_keyedValuePool);
    ShutDownEntryPool(&g_payloadPool);
    ShutDownPayloadPools();
    ShutDownEntryPool(&g_propertyRefPool);
    ShutDownMarkRoots((MarkStacks*)g_markStacks);
}
