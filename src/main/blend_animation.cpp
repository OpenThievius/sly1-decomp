// SPDX-License-Identifier: AGPL-3.0-or-later
// The combined blend animations, 0x138FF0 to 0x139B70 (no .rodata, .data or .bss of its own):
// LoopOverMinCountNoOp, BuildCombinedBlendAnimation and the duration, weight and range helpers
// it uses, and SetBlendEntryRecordFlag. The edges are not proved by retail, only by the change
// of role: the world's contact pairs end before it (world_contacts.cpp) and the alpha state
// packets and world-listed objects begin after it (world_listed_object.cpp); none of these
// functions reads .rodata or .data of either side, so the cut before could lie from 0x138F28 to
// 0x139038 and the one after from 0x139B38 to 0x139B70. The name is ours, after its role.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "aim_blend_grid.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"
#include "anim_curve.h"
#include "attachment.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "vu0.h"
#include "placed_object.h"
#include "collider.h"
#include "common.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "list_iter.h"


f32 WrapModulo(f32 x, f32 y);
void CopyMemory(void* dst, void* src, u32 size);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 bytes);

void* AllocateFrontMemory(s32 size);


void LoopOverMinCountNoOp(s32 a, s32 b, s32 c, s32 d)
{
    s32 i;
    for (i = 0; i < (a < c ? a : c); i++) {
    }
}

struct BlendCurveView { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; };
struct BlendTrack {
    s32 key; BlendCurveView* a; BlendCurveView* b; s32 fC; BlendCurveView* c; s32 n; BlendCurveView** d;
};
struct BlendSourceAnim {
    u8 pad0[0x38]; s32 count; BlendTrack* grps; u8 pad40[4]; s32 f44;
    u8 pad48[0x54 - 0x48]; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64; s32 f68;
    u8 pad6C[0x78 - 0x6C]; s32 f78; f32 f7C;
};
struct BlendItem { s32 f0; BlendSourceAnim* src; };
struct BlendAnimation;
typedef void (*BlendAnimationFn)(BlendAnimation*);
struct BlendAnimation {
    BlendAnimationFn* vtbl; u8 pad4[0x34]; s32 count; BlendTrack* grps; u8 pad40[4]; s32 f44;
    u8 pad48[0x54 - 0x48]; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64; s32 f68;
    u8 pad6C[0x78 - 0x6C]; s32 f78; f32 f7C;
    u8 pad80[0xB0 - 0x80]; s32 stride; s32 nitems; void* data; s32 nkeys; BlendSequence* keys;
};

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
BlendAnimation* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);
BlendTrack* AllocateZeroedBackMemory(s32 size);
u8* CopyToFrontMemory(s32 size, void* src);
BlendCurveView* CreatePositionCurve(s32 kind);
BlendCurveView* CreateRotationCurve(s32 kind);
BlendCurveView* CreateWeightCurve(u32 kind);
void LoopOverMinCountNoOp(s32 a, s32 b, s32 c, s32 d);

void BuildCombinedBlendAnimation(Collider* ctx, s32 stride, s32 count, u8* items, s32 nkeys, s32* keyA, s32* keyB, BlendAnimation** out)
{
    s32 i;
    BlendItem* item;
    BlendTrack* buf;
    for (i = 0; ; i++) {
        if (i >= count) {
            *out = 0;
            return;
        }
        item = (BlendItem*)(items + i * stride);
        if (item->src != 0) break;
    }
    BlendSourceAnim* src = item->src;
    PushBackMemoryMark();
    BlendAnimation* anim = CreateTypedRecord(0x84, ctx->world, ctx, -1, -1);
    anim->vtbl[7](anim);
    anim->nitems = count;
    anim->stride = stride;
    anim->data = AllocateFrontMemory(count * stride);
    anim->nkeys = nkeys;
    anim->keys = (BlendSequence*)AllocateFrontMemory(nkeys * 12);
    for (s32 k = 0; k < nkeys; k++) {
        BlendSequence* key = &anim->keys[k];
        key->stride = keyA[k];
        key->count = keyB[k];
        key->pairs = (BlendTimeScale*)AllocateFrontMemory(key->count << 3);
    }
    s32 total = 0;
    for (i = 0; i < count; i++) {
        item = (BlendItem*)(items + i * stride);
        if (item->src != 0) total += item->src->count;
    }
    buf = AllocateZeroedBackMemory(total * 0x1C);
    s32 used = 0;
    for (i = 0; i < count; i++) {
        item = (BlendItem*)(items + i * stride);
        if (item->src == 0) continue;
        for (s32 j = 0; j < item->src->count; j++) {
            BlendTrack* g = &item->src->grps[j];
            if (g->a == 0 && g->b == 0 && g->c == 0 && g->d == 0) continue;
            BlendTrack* e;
            for (s32 m = 0; m < used; m++) {
                e = &buf[m];
                if (g->key == e->key) goto have;
            }
            e = &buf[used++];
            e->key = g->key;
        have:
            if (g->a != 0) {
                if (e->a == 0) {
                    BlendCurveView* t = CreatePositionCurve(2);
                    t->fC = (s32)anim;
                    t->f10 = (s32)anim->keys;
                    t->f14 = (s32)AllocateZeroedFrontMemory(count << 2);
                    t->f8 = 1;
                    e->a = t;
                }
                if (g->a->f8 == 0) e->a->f8 = 0;
                ((BlendCurveView**)e->a->f14)[i] = g->a;
            }
            if (g->b != 0) {
                if (e->b == 0) {
                    BlendCurveView* t = CreateRotationCurve(2);
                    t->fC = (s32)anim;
                    t->f10 = (s32)anim->keys;
                    t->f14 = (s32)AllocateZeroedFrontMemory(count << 2);
                    t->f8 = 1;
                    e->b = t;
                }
                if (g->b->f8 == 0) e->b->f8 = 0;
                ((BlendCurveView**)e->b->f14)[i] = g->b;
            }
            if (g->c != 0) {
                if (e->c == 0) {
                    BlendCurveView* t = CreateWeightCurve(3);
                    t->f8 = (s32)anim;
                    t->fC = (s32)anim->keys;
                    t->f10 = (s32)AllocateZeroedFrontMemory(count << 2);
                    e->c = t;
                }
                ((BlendCurveView**)e->c->f10)[i] = g->c;
            }
            if (g->d != 0) {
                if (e->d == 0) {
                    e->n = g->n;
                    e->d = (BlendCurveView**)AllocateZeroedFrontMemory(g->n << 2);
                }
                for (s32 q = 0; q < g->n; q++) {
                    BlendCurveView* v = g->d[q];
                    if (v != 0) {
                        BlendCurveView* t = e->d[q];
                        if (t == 0) {
                            BlendCurveView* nt = CreateWeightCurve(4);
                            nt->f8 = (s32)anim;
                            nt->fC = (s32)anim->keys;
                            nt->f10 = (s32)AllocateZeroedFrontMemory(count << 2);
                            nt->f14 = q;
                            e->d[q] = nt;
                            t = nt;
                        }
                        ((BlendCurveView**)t->f10)[i] = v;
                    }
                }
            }
        }
    }
    anim->count = used;
    anim->grps = (BlendTrack*)CopyToFrontMemory(used * 0x1C, buf);
    anim->f44 = src->f44;
    anim->f78 = src->f78;
    anim->f7C = src->f7C;
    anim->f54 = src->f54;
    anim->f58 = src->f58;
    anim->f64 = src->f64;
    anim->f68 = src->f68;
    if (nkeys == 0) {
        anim->f5C = src->f5C;
        anim->f60 = src->f60;
        LoopOverMinCountNoOp(anim->f5C, anim->f60, src->f5C, src->f60);
    }
    *out = anim;
    PopBackMemoryMark();
}

f32 GetAnimationMarkerTime(Animation* self, s32 key);

void ComputeWrappedDeltas(s32 stride, s32 count, u8* base, s32 off, s32 count2, s32* vals)
{
    s32 i;
    for (i = 0; i < count; i++) {
        BlendEntry* e = (BlendEntry*)(base + i * stride);
        if (e->sub == 0) {
            continue;
        }
        BlendTimeScale* s1 = (BlendTimeScale*)((u8*)e + off);
        BlendTimeScale* s5 = s1;
        s32 n;
        s32 bytes = count2 * 8;
        if (count2 > 0) {
            s32* v = vals;
            n = count2;
            do {
                n--;
                s1->a = GetAnimationMarkerTime((Animation*)e->sub, *v);
                v++;
                s1++;
            } while (n != 0);
        }
        s1 = s5;
        BlendTimeScale* prev = (BlendTimeScale*)((u8*)s1 + (bytes - 8));
        if (count2 > 0) {
            n = count2;
            do {
                f32 d = s1->a - prev->a;
                prev->b = d;
                if (d < 0.0f) {
                    prev->b = d + e->sub->length;
                }
                prev = s1;
                n--;
                s1++;
            } while (n != 0);
        }
    }
}

void ComputeBlendedDuration(s32 stride, s32 count, void* items, s32 offset, s32 nKeys, BlendTimeScale* pairs, void* out)
{
    BlendTimeScale* keys = pairs;
    f32* duration = (f32*)out;
    f32 total = 0.0f;
    s32 j;
    s32 k;
    BlendEntry* item;

    if (nKeys == 0) {
        if (duration == 0) {
            return;
        }
        for (j = 0; j < count; j++) {
            item = (BlendEntry*)((u8*)items + j * stride);
            if (item->weight != 0.0f) {
                total += item->sub->length * item->weight;
            }
        }
        *duration = total;
        return;
    }
    for (k = 0; k < nKeys; k++) {
        keys[k].b = 0.0f;
        for (j = 0; j < count; j++) {
            item = (BlendEntry*)((u8*)items + j * stride);
            if (item->sub != 0) {
                keys[k].b += ((BlendTimeScale*)((u8*)item + offset))[k].b * item->weight;
            }
        }
        total += keys[k].b;
    }
    f32 sum;
    f32 ref;
    s32 first = 1;
    for (j = 0; j < count; j++) {
        item = (BlendEntry*)((u8*)items + j * stride);
        if (item->weight != 0.0f) {
            BlendTimeScale* key = (BlendTimeScale*)((u8*)item + offset);
            if (first) {
                first = 0;
                sum = key->a / item->sub->length;
                ref = sum;
            } else {
                f32 d = key->a / item->sub->length - ref;
                if (d <= -0.5f) {
                    d += 1.0f;
                } else if (0.5f < d) {
                    d -= 1.0f;
                }
                sum += d * item->weight;
            }
        }
    }
    keys[0].a = WrapModulo(sum, 1.0f) * total;
    for (k = 1; k < nKeys; k++) {
        f32 s = keys[k - 1].a + keys[k - 1].b;
        keys[k].a = s;
        if (total <= s) {
            keys[k].a = s - total;
        }
    }
    if (duration != 0) {
        *duration = total;
    }
}

s32 FindCyclicRangeIndex(f32 x, f32 period, s32 count, BlendTimeScale* p, f32* out)
{
    s32 i;
    for (i = 0; i < count; p++, i++) {
        if (p->b != 0.0f) {
            f32 d = x - p->a;
            if (d < 0.0f) {
                d += period;
            }
            if (d < p->b + 0.0001f) {
                if (out != 0) {
                    *out = d;
                }
                break;
            }
        }
    }
    return i;
}

LINKER_REMNANT(func_001399F0);

#include "list_iter.h"


void CopyMemory(void* dst, void* src, u32 size);
void ComputeBlendedDuration(s32 stride, s32 count, void* items, s32 offset, s32 nKeys, BlendTimeScale* pairs, void* out);
void SettleListedPoseSources(AnimationPlayer* self);

void SetBlendItemWeights(BlendAnimationView* self, s32 a1, s32 a2, void* a3)
{
    AnimationPlayer* node = (AnimationPlayer*)self->f6C;
    s32 i;
    s32 count;
    BlendSequence* ent;
    ListFrame frame;

    if (node != 0) {
        do {
            node->time = node->time / self->f34;
            node = node->animNext;
        } while (node != 0);
    }
    CopyMemory(self->fB8, a3, a2 * a1);
    count = self->fBC;
    if (count == 0) {
        ComputeBlendedDuration(a1, a2, a3, 0, 0, 0, &self->f34);
    } else {
        for (i = 0; i < count; i++) {
            ent = (BlendSequence*)((u8*)self->pC0 + i * 12);
            ComputeBlendedDuration(a1, a2, a3, ent->stride, ent->count, ent->pairs, &self->f34);
        }
    }
    node = (AnimationPlayer*)self->f6C;
    if (node != 0) {
        do {
            node->time = node->time * self->f34;
            SettleListedPoseSources(node);
            node = node->animNext;
        } while (node != 0);
    }
}


void* FindEntryByObjectId(BlendAnimationView* self, void* key);

void SetBlendEntryRecordFlag(BlendAnimationView* blend, void* key)
{
    BlendSourceEntry* o = (BlendSourceEntry*)FindEntryByObjectId(blend, key);
    if (o) {
        if (o->sub) {
            o->sub->flag = 1;
        }
    }
}
