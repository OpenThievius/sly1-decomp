// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1C1190 to 0x1C29E8 (its .rodata from 0x24D3C0, its .data from 0x2748F0): the
// script entries and object properties (their jump tables are its .rodata), and the scratchpad
// transfers with the static initialiser that builds them (func_001C27B0, its _GLOBAL_$I$
// func_001C29C8 in retail's constructor list). It ends at an exact edge. Its start is NOT proved
// by retail: the cut at 0x1C1190 follows the change of role, inside the range retail's .rodata
// allows (sound_system.cpp says why: from 0x1C10D8 to 0x1C15D8), and its two families could be
// two files. Its name is ours, after the script entries and object properties, which hold most of
// its code.
#include "common.h"
#include "sound_record.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
#include "buffered_stream.h"
#include "object_event.h"
#include "key_record.h"
#include "key_id.h"
#include "base_object.h"
#include "fpu.h"
#include "asm_func.h"
#include "point_object.h"
#include "id_linked_object.h"
#include "game_progress.h"
#include "shapes.h"
#include "property_descriptor.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "attached_set.h"
#include "active_set_solver.h"
#include "sound_level.h"
#define VA_ARG_WORD(ap, T) (*(T*)((ap += 8) - 8))

void* FillMemory(void* p, s32 value, s32 size);
void* AllocateFrontMemory(s32 size);
s32 ScriptListContainsValue(s32 value, void* out);
s32 AppendPropertyToScriptList(s32 value, void* out);
s32 ReadBufferedU32(BufferedStream* in);
void* FillMemory(void* p, s32 value, s32 size);
void* FillMemory(void* p, s32 value, s32 size);
void* FillMemory(void* p, s32 value, s32 size);
typedef signed int s32;
typedef unsigned char u8;
void EnsureKeyedList(void* p);
// An entry of World::f1EF4: an expression read from the level and the scope it was evaluated in
// (0 until func_001C13E8 evaluates it).
struct WorldScriptEntry { R11B008Node* expr; s32 scope; };
extern u8 g_markStacks[];
void AddUniqueMarkRoot(void* a, void* b);
// A property's getter (PropertyDescriptor::getter with flags 4, or the method at that offset of
// the object's table): fills `out` with the value of `obj`.
typedef void (*PropertyGetter)(void* obj, void* out);
// A property's setter (PropertyDescriptor::putter with flags 0x20, or the method at that offset
// of the object's table): stores `value` into `obj`.
typedef void (*PropertySetter)(void* obj, s32 value);
ScriptValue* WritePropertyValue(ScriptValue* out, void* base, PropertyDescriptor* d, ScriptValue* val);
// A DMA tag of a chain (two doublewords; func_001C2430 writes the first).
struct DmaTag { u64 lo; u64 hi; };
// The tags of the two transfers' chains (8 each, read uncached).
extern DmaTag D_00605440[8];
extern DmaTag D_006054C0[8];

// One of the two scratchpad transfer buffers (D_002748F0; D_00274990 picks the current one):
// func_001C2430 sends up to 8 blocks into the scratchpad by a DMA chain, func_001C25B0 sends
// them back to memory.
struct SprTransfer {
    DmaTag* tags;           // 0x00: the chain's tags
    s32 base;               // 0x04: the scratchpad address of the first block's tag
    u32 addrs[8];           // 0x08: each block's address, after its 16-byte tag
    s32 sizes[8];           // 0x28: each block's size, rounded up to 16
    s32 count;              // 0x48: the number of blocks
    s32 state;              // 0x4C: 1 sent in, 3 sending back (StartFromSprChain), 0 done
};

void* FillMemory(void* p, s32 value, s32 size);

// Transfer i's record, cleared, with its tags read uncached (0x20000000) and its first tag's
// scratchpad address: the static initialiser (func_001C27B0) builds the two in a temporary and
// copies each into D_002748F0.
static inline SprTransfer MakeSprTransfer(s32 i)
{
    SprTransfer t;
    FillMemory(&t, 0, 0x50);
    t.tags = (DmaTag*)((u32)(i != 0 ? D_006054C0 : D_00605440) | 0x20000000);
    t.base = 0x70000000 + i * 0x2000;
    return t;
}
// The registers of the scratchpad DMA channels (g_fromSprChannel, g_toSprChannel) the code sets.
struct SprDmaChannel {
    s32 chcr;               // 0x00: its control register (bit 6 cleared or set)
    u8 pad4[0x7C];
    s32 sadr;               // 0x80: the scratchpad address
};
extern SprDmaChannel* g_fromSprChannel;
s32 WaitDmaChannel(SprDmaChannel* d, s32 b, s32 c);
void StartDmaChainToMemory(SprDmaChannel* d);
// A script list being built (func_001C1530 hands one to a getter; func_001C1A28 appends a value
// of `type` to it).
struct ScriptListBuilder { s32 type; R11B008Node* head; R11B008Node* tail; };
void* FillMemory(void* p, s32 value, s32 size);
void ReadPropertyValue(ScriptValue* t, s32 value, PropertyDescriptor* d);
extern PropertyList g_classPropertyLists[];
// (if/else with the small path first moved $s0/$s1)
ScriptValue *ReadPropertyValue(ScriptValue* self, void* a, s32 r);
s32 ReadBufferedU32(void* src);
void* AllocateFrontMemory(u32 size);
void SkipBufferedBlock(void* self);
s32 NewScriptScope(void);
void AddUniqueMarkRoot(u8* a, s32 b);
void* DefineScriptVariable(ScriptValue* out, s32 a, s32 b, ScriptValue* body);
extern u32 D_00275714;
// NEAR: the entry pointer is loaded into v0 where retail uses v1 (register choice only); five lines differ.

void EvalScriptExpression(ScriptValue* t, R11B008Node* node, s32 b); // stays void: retail returns a value, but declared so func_001C13E8 differs in registers
// A type and a list of script values: func_001C1AD8 tells whether a value is among them.
struct ScriptValueFilter { u32 type; R11B008Node* list; };
// The payloads of script values of kind 10 and 11 (two and three words), copied word by word.
struct ScriptPair { s32 w[2]; };
struct ScriptTriple { s32 w[3]; };
extern void* AcquireVectorAPayload(void);
extern void* AcquireMatrixPayload(void);
extern void* CopyRotationMatrix(void* d, void* s);
extern void ResetMatrixHomogeneous(void* d);
extern void* AcquireVectorBPayload(void);
extern void* AcquirePairPayload(void);
extern void* AcquireTriplePayload(void);
extern SprDmaChannel* g_toSprChannel;
s32 WaitDmaChannel(void* p, s32 a, s32 b);
void StartDmaChain(SprDmaChannel* c, u32 addr);
void LoadScriptEntryTable(World* self, BufferedStream* arg);
void* GetScriptEntryScope(s32 index, World* self);
ScriptValue* EvalScriptEntry(ScriptValue* self, s32 index, World* ctx);
PropertyDescriptor* FindPropertyDescriptor(BaseObject* self, s32 key);
ScriptValue* BuildScriptListFromCallback(ScriptValue* self, void* ctx, s32 v, PropertyGetter cb);
ScriptValue* ReadPropertyValue(ScriptValue* out, void* base, PropertyDescriptor* d);
s32 AppendPropertyToScriptList(ScriptListBuilder* self, s32 value);
s32 ScriptListContainsValue(ScriptValueFilter* filter, s32* val);
ScriptValue* StoreScriptArguments(ScriptValue* out, s32 n, ScriptValue* args, const u32* kinds, void** dsts);
ScriptValue* BuildScriptListFromPairs(ScriptValue* self, s32 n, s32* keys, s32* vals);
ScriptValue* GetObjectProperty(ScriptValue* self, BaseObject* p, s32 n);
ScriptValue* UpdateObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* AddObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* SetExtraObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* StoreScriptArgumentsVa(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...);
void StartToSprChain(s32 size, ...);
void StartFromSprChain(s32 first, ...);
SprTransfer D_002748F0[2] = { MakeSprTransfer(0), MakeSprTransfer(1) };
s32 D_00274990 = 0;
void* FillMemory(void* p, s32 value, s32 size);

void LoadScriptEntryTable(World* self, BufferedStream* arg) {
    ScriptValue q0;
    ScriptValue q1;
    ScriptValue q2;
    s32 i = 0;
    InitScriptValue(&q0);
    self->f1EF0 = ReadBufferedU32(arg);
    self->f1EF4 = AllocateFrontMemory(self->f1EF0 << 3);
    s32 n1 = ReadBufferedU32(arg);
    s32 n2 = ReadBufferedU32(arg);
    for (i = 0; i < self->f1EF0; i++) {
        {
            WorldScriptEntry* e = (WorldScriptEntry*)self->f1EF4 + i;
            e->expr = ReadScriptValueChain(arg);
            e->scope = 0;
            if (D_00275714) {
                SkipBufferedBlock(arg);
                SkipBufferedBlock(arg);
                SkipBufferedBlock(arg);
            }
        }
    }
    if (D_00275714) {
        if (n1 > 0) { s32 k = n1; do SkipBufferedBlock(arg); while (--k); }
        if (n2 > 0) { s32 k = n2; do SkipBufferedBlock(arg); while (--k); }
    }
    s32 r = NewScriptScope();
    i = 0;
    self->f2C = (void*)r;
    AddUniqueMarkRoot(g_markStacks, r);
    self->f1EF8 = n1;
    SetScriptValueTag(&q0, 0);
    DefineScriptVariable(&q1, (s32)self->f2C, self->f1EF8, &q0);
    DestroyScriptValue(&q1, 2);
    if (self->f1EF0 > 0) {
        do {
            InitScriptValue(&q1);
            EvalScriptEntry(&q2, i, self);
            i++;
            AssignScriptValue(&q1, &q2);
            DestroyScriptValue(&q2, 2);
            DestroyScriptValue(&q1, 2);
        } while (i < self->f1EF0);
    }
    DestroyScriptValue(&q0, 2);
}

void* GetScriptEntryScope(s32 index, World* self)
{
    if (index == -1) {
        return 0;
    } else {
        WorldScriptEntry* e = (WorldScriptEntry*)((index << 3) + (u32)self->f1EF4);
        void* p = (void*)e->scope;
        if (p != 0) AddUniqueMarkRoot(g_markStacks, p);
        return p;
    }
}

ScriptValue* EvalScriptEntry(ScriptValue* self, s32 index, World* ctx)
{
    s32 off = index << 3;
    ScriptValue q;
    WorldScriptEntry* e;
    InitScriptValue(&q);
    e = (WorldScriptEntry*)(off + (s32)ctx->f1EF4);
    if (e->expr != 0 && e->scope == 0) {
        ScriptValue t;
        ((WorldScriptEntry*)(off + (s32)ctx->f1EF4))->scope = NewScriptScope();
        EvalScriptExpression(&t, ((WorldScriptEntry*)(off + (s32)ctx->f1EF4))->expr, ((WorldScriptEntry*)(off + (s32)ctx->f1EF4))->scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

PropertyDescriptor* FindPropertyDescriptor(BaseObject* self, s32 key)
{
    PropertyList* entry = &g_classPropertyLists[self->desc->id];
    s32 lo = 0;
    s32 hi = entry->count - 1;
    const PropertyEntry* items = entry->entries;

    while (lo <= hi) {
        s32 mid = (lo + hi) >> 1;
        s32 k = items[mid].id;
        if (k == key) {
            return items[mid].prop;
        }
        if (key < k) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

ScriptValue* BuildScriptListFromCallback(ScriptValue* self, void* ctx, s32 v, PropertyGetter cb)
{
    ScriptValue q;
    ScriptListBuilder r;
    InitScriptValue(&q);
    r.type = v;
    r.head = 0;
    r.tail = 0;
    cb(ctx, &r);
    if (r.head != 0) {
        SetScriptValueChain(&q, r.head);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

ScriptValue* ReadPropertyValue(ScriptValue* out, void* base, PropertyDescriptor* d)
{
    ScriptValue q;
    ScriptValue q2;
    s32 t20, t28, t2c, t30;
    f32 t24;
    char* p;
    PropertyGetter fn;
    InitScriptValue(&q);
    if (d->flags & 1) {
        s32* r = (s32*)TakeZeroedPoolEntry();
        r[0] = (s32)base;
        r[1] = d->f10;
        r[2] = d->argCount;
        SetScriptValueIntC(&q, (s32)r);
    } else if (d->flags & 2) {
        if (d->flags & 0x1000) {
            p = (char*)d->target(base, 0) + d->getter;
        } else {
            p = (char*)base + d->getter;
        }
        switch (d->type) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            SetScriptValueInt(&q, *(s32*)p);
            break;
        case 1:
            SetScriptValueFloat(&q, *(f32*)p);
            break;
        case 0:
            SetScriptValueBool(&q, *(s32*)p);
            break;
        case 2: {
            Quad16* r = (Quad16*)AcquireVectorAPayload();
            *r = *(Quad16*)p;
            SetScriptValueVectorA(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = AcquireMatrixPayload();
            CopyRotationMatrix(r, p);
            SetScriptValueMatrix(&q, (f32*)r);
            break;
        }
        case 9: {
            Quad16* r = (Quad16*)AcquireVectorBPayload();
            *r = *(Quad16*)p;
            SetScriptValueVectorB(&q, (f32*)r);
            break;
        }
        case 10: {
            ScriptPair* r = (ScriptPair*)AcquirePairPayload();
            *r = *(ScriptPair*)p;
            SetScriptValuePair(&q, (f32*)r);
            break;
        }
        case 11: {
            ScriptTriple* r = (ScriptTriple*)AcquireTriplePayload();
            *r = *(ScriptTriple*)p;
            SetScriptValueTriple(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->type & 0x1000) {
                SetScriptValueInt(&q, *(s32*)p);
            } else if (d->type & 0x2000) {
                SetScriptValuePointerB(&q, (void*)*(s32*)p);
            }
            break;
        }
    } else {
        if (d->flags & 0x1000) {
            p = (char*)d->target(base, 0);
        } else {
            p = (char*)base;
        }
        if (d->flags & 4) {
            fn = (PropertyGetter)d->getter;
        } else {
            fn = *(PropertyGetter*)(*(char**)base + d->getter);
        }
        switch (d->type) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            fn(p, &t20);
            SetScriptValueInt(&q, t20);
            break;
        case 1:
            fn(p, &t24);
            SetScriptValueFloat(&q, t24);
            break;
        case 0:
            fn(p, &t28);
            SetScriptValueBool(&q, t28);
            break;
        case 2: {
            void* r = AcquireVectorAPayload();
            fn(p, r);
            SetScriptValueVectorA(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = AcquireMatrixPayload();
            fn(p, r);
            ResetMatrixHomogeneous(r);
            SetScriptValueMatrix(&q, (f32*)r);
            break;
        }
        case 9: {
            void* r = AcquireVectorBPayload();
            fn(p, r);
            SetScriptValueVectorB(&q, (f32*)r);
            break;
        }
        case 10: {
            void* r = AcquirePairPayload();
            fn(p, r);
            SetScriptValuePair(&q, (f32*)r);
            break;
        }
        case 11: {
            void* r = AcquireTriplePayload();
            fn(p, r);
            SetScriptValueTriple(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->type < 0) {
                BuildScriptListFromCallback(&q2, base, d->type & 0x7fffffff, fn);
                AssignScriptValue(&q, &q2);
                DestroyScriptValue(&q2, 2);
            } else if (d->type & 0x1000) {
                fn(p, &t2c);
                SetScriptValueInt(&q, t2c);
            } else if (d->type & 0x2000) {
                fn(p, &t30);
                SetScriptValuePointerB(&q, (void*)t30);
            }
            break;
        }
    }
    CopyConstructScriptValue(out, &q);
    DestroyScriptValue(&q, 2);
    return out;
}

s32 AppendPropertyToScriptList(ScriptListBuilder* self, s32 value)
{
    PropertyDescriptor d;
    ScriptValue t;
    FillMemory(&d, 0, 0x20);
    d.flags = 2;
    d.type = self->type;
    d.getter = 0;
    R11B008Node* n = NewScriptValueNode();
    ReadPropertyValue(&t, value, &d);
    AssignScriptValue(n, &t);
    DestroyScriptValue(&t, 2);
    if (self->head != 0) {
        self->tail->next = n;
    } else {
        self->head = n;
    }
    self->tail = n;
    return 1;
}

s32 ScriptListContainsValue(ScriptValueFilter* filter, s32* val) {
    ScriptValue q;
    R11B008Node* l;
    InitScriptValue(&q);
    l = filter->list;
    if (l) {
        switch (filter->type) {
        case 1:
            SetScriptValueFloat(&q, *(f32*)val);
            break;
        case 0:
            SetScriptValueBool(&q, *val);
            break;
        case 2: case 4: case 9: case 10: case 11: case 13:
            break;
        default:
            if (filter->type & 0x1000) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
                SetScriptValueInt(&q, *val);
            } else if (filter->type & 0x2000) {
                SetScriptValuePointerB(&q, (void*)*val);
            }
            break;
        }
        while (l) {
            if (AreScriptValuesEqual(l, &q)) {
                DestroyScriptValue(&q, 2);
                return 1;
            }
            l = l->next;
        }
    }
    DestroyScriptValue(&q, 2);
    return 0;
}

ScriptValue* StoreScriptArguments(ScriptValue* out, s32 n, ScriptValue* args, const u32* kinds, void** dsts)
{
    ScriptValue q;
    ScriptValue a;
    ScriptValue b;
    ScriptValue c;
    s32 i;
    InitScriptValue(&q);
    for (i = 0; i < n; i++) {
        AssignScriptValue(&q, args + i);
        u32 t = kinds[i];
        void* d = dsts[i];
        switch (t) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
        case 20:
            if (q.tag == 0x14) {
                goto store;
            }
            InitScriptValue(&a);
            ConvertScriptValueToInt(&b, &q);
            AssignScriptValue(&a, &b);
            DestroyScriptValue(&b, 2);
            *(s32*)d = a.i;
            DestroyScriptValue(&a, 2);
            break;
        case 1:
            if (q.tag == 0x15) {
                *(f32*)d = q.f;
            } else {
                InitScriptValue(&a);
                ConvertScriptValueToFloat(&c, &q);
                AssignScriptValue(&a, &c);
                DestroyScriptValue(&c, 2);
                *(f32*)d = a.f;
                DestroyScriptValue(&a, 2);
            }
            break;
        case 4:
            *(Mat02*)d = *(Mat02*)q.p;
            break;
        case 2:
        case 9:
            *(Quad16*)d = *(Quad16*)q.p;
            break;
        case 10:
            *(ScriptPair*)d = *(ScriptPair*)q.p;
            break;
        case 11:
            *(ScriptTriple*)d = *(ScriptTriple*)q.p;
            break;
        default:
            if (t & 0x1000) {
                goto store;
            }
            if (t & 0x2000) {
                goto store;
            }
            break;
        case 0:
        store:
            *(s32*)d = q.i;
            break;
        case 13:
            break;
        }
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(out, &q);
    DestroyScriptValue(&q, 2);
    return out;
}

ScriptValue* BuildScriptListFromPairs(ScriptValue* self, s32 n, s32* keys, s32* vals)
{
    ScriptValue q;
    ScriptListBuilder list;
    InitScriptValue(&q);
    list.head = 0;
    list.tail = 0;
    for (s32 i = 0; i < n; i++) {
        list.type = keys[i];
        AppendPropertyToScriptList(&list, vals[i]);
    }
    if (list.head) {
        SetScriptValueChain(&q, list.head);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

ScriptValue* WritePropertyValue(ScriptValue* out, void* base, PropertyDescriptor* d, ScriptValue* val)
{
    ScriptValue q;
    ScriptValue q2;
    ScriptValue q3;
    ScriptValue q4;
    void* dst[1];
    PropertySetter fn;
    void* p;
    InitScriptValue(&q);
    q.tag = 0x22;
    if (d->flags & 0x10) {
        if (d->flags & 0x1000) {
            dst[0] = (char*)d->target(base, 1) + d->putter;
        } else {
            dst[0] = (char*)base + d->putter;
        }
        StoreScriptArguments(&q2, 1, val, (const u32*)d, dst);
        AssignScriptValue(&q, &q2);
        DestroyScriptValue(&q2, 2);
    } else {
        p = (d->flags & 0x1000) ? d->target(base, 1) : base;
        fn = (d->flags & 0x20) ? (PropertySetter)d->putter
                               : *(PropertySetter*)(*(char**)base + d->putter);
        switch (d->type) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17: {
            s32 v;
            if (val->tag == 0x14) {
                v = val->i;
            } else {
                InitScriptValue(&q2);
                ConvertScriptValueToInt(&q3, val);
                AssignScriptValue(&q2, &q3);
                DestroyScriptValue(&q3, 2);
                v = q2.i;
                DestroyScriptValue(&q2, 2);
            }
            fn(p, v);
            break;
        }
        case 1: {
            f32 f;
            if (val->tag == 0x15) {
                f = val->f;
            } else {
                InitScriptValue(&q2);
                ConvertScriptValueToFloat(&q4, val);
                AssignScriptValue(&q2, &q4);
                DestroyScriptValue(&q4, 2);
                f = q2.f;
                DestroyScriptValue(&q2, 2);
            }
            ((void (*)(void*, f32))fn)(p, f);
            break;
        }
        case 0:
            fn(p, val->i);
            break;
        case 2:
            fn(p, val->i);
            break;
        case 4:
            fn(p, val->i);
            break;
        case 9:
            fn(p, val->i);
            break;
        case 10:
            fn(p, val->i);
            break;
        case 11:
            fn(p, val->i);
            break;
        case 13:
            break;
        default:
            if (d->type & 0x1000) {
                fn(p, val->i);
            } else if (d->type & 0x2000) {
                fn(p, val->i);
            }
            break;
        }
    }
    CopyConstructScriptValue(out, &q);
    DestroyScriptValue(&q, 2);
    return out;
}

ScriptValue* GetObjectProperty(ScriptValue* self, BaseObject* p, s32 n)
{
    if (n < 0x495) {
        s32 r = (s32)FindPropertyDescriptor(p, n);
        ReadPropertyValue(self, p, r);
    } else {
        ScriptValue q;
        InitScriptValue(&q);
        FindKeyedValue((R11B008List*)p->f04, n, &q);
        CopyConstructScriptValue(self, &q);
        DestroyScriptValue(&q, 2);
    }
    return self;
}

ScriptValue* UpdateObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value)
{
    if (key < 0x495) {
        PropertyDescriptor* d = FindPropertyDescriptor(p, key);
        WritePropertyValue(self, p, d, value);
    } else {
        UpdateKeyedValue(self, (R11B008List*)p->f04, key, value);
    }
    return self;
}

ScriptValue* AddObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value)
{
    EnsureKeyedList(p);
    AddKeyedValue(self, (R11B008List*)p->f04, key, value);
    return self;
}

ScriptValue* SetExtraObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value)
{
    EnsureKeyedList(p);
    if (FindKeyedValue((R11B008List*)p->f04, key, 0)) UpdateKeyedValue(self, (R11B008List*)p->f04, key, value);
    else AddKeyedValue(self, (R11B008List*)p->f04, key, value);
    return self;
}

ScriptValue* StoreScriptArgumentsVa(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...)
{
    void* arr[32];
    void* ap = (char*)__builtin_next_arg(kinds) - 32;
    if (count > 0) {
        void** d = arr;
        s32 i = count;
        do {
            ap = (char*)ap + 8;
            *d = *(void**)((char*)ap - 8);
            d++;
            i--;
        } while (i != 0);
    }
    StoreScriptArguments(ret, count, args, (const u32*)kinds, arr);
    return ret;
}

void StartToSprChain(s32 size, ...)
{
    char* ap;
    SprTransfer* e = &D_002748F0[1 - D_00274990];
    s32 n = 0;
    ap = (char*)__builtin_next_arg(size) - (8 - __builtin_args_info(0)) * 8;
    u32 addr = e->base;
    if (e->state == 3) {
        WaitDmaChannel((*(void**)&g_fromSprChannel), 0, 0);
    }
    e->state = 1;
    s32 data = VA_ARG_WORD(ap, s32);
    if (size != 0) {
        do {
            s32 nsize = VA_ARG_WORD(ap, s32);
            size = (size + 15) & ~15;
            addr += 16;
            e->sizes[n] = size;
            e->addrs[n] = addr;
            addr += size;
            s32 ndata = VA_ARG_WORD(ap, s32);
            if (data != 0) {
                e->tags[n].lo = (u64)(size >> 4) | ((u64)(ndata != 0 ? 3 : 0) << 28) | ((u64)data << 32);
            }
            data = ndata;
            size = nsize;
            n++;
        } while (size != 0);
    }
    e->count = n;
    SprDmaChannel* c = g_toSprChannel;
    c->chcr |= 0x40;
    c->sadr = (e->base & 0x0FFFFFFF) | 0x80000000;
    StartDmaChain(c, (u32)e->tags & 0x0FFFFFFF);
}

void StartFromSprChain(s32 first, ...) {
    s32 buf[8];
    SprTransfer* r = &D_002748F0[D_00274990];
    s32 n = 0;
    s32 x = first;
    r->state = 3;
    WaitDmaChannel(g_fromSprChannel, 0, 0);
    void* ap = (char*)__builtin_next_arg(first) - 56;
    while (x) {
        buf[n] = x;
        ap = (char*)ap + 8;
        x = *(s32*)((char*)ap - 8);
        n++;
    }
    s32 i = 0;
    n = r->count - n;
    while (n < r->count - 1) {
        *(u64*)(r->addrs[n] - 0x10) = ((r->sizes[n] >> 4) | 0x10000000) | ((u64)buf[i] << 32);
        n++;
        i++;
    }
    SprDmaChannel* d = g_fromSprChannel;
    *(u64*)(r->addrs[n] - 0x10) = ((r->sizes[n] >> 4) | 0x70000000) | ((u64)buf[i] << 32);
    d->chcr &= ~0x40;
    d->sadr = (r->base & 0xFFFFFFF) + 0x80000000;
    StartDmaChainToMemory(d);
    r = &D_002748F0[1 - D_00274990];
    if (r->state == 3) r->state = 0;
}

LINKER_REMNANT(func_001C27A8);