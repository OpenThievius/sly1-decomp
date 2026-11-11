// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 334/376 (88.8%), checked 2026-11-11
// Tried night-close8: n->key in a named local for both tests, for the tag test only, the tag test as an else-if: no closer (59, 34, 34 differing words).
// Near match: the same instructions and block layout as retail; only registers differ.
// Retail reloads n->key for the tag test through a copy ($v1), which GCC CSE does not do here
// because CSE follows the key-test branch into the tag test. An empty do { } while (0) after the
// key-match return stops that and matches EXACT, but it is an artificial barrier (AGENTS.md),
// so it is not kept here. Not linked.
// Wave 9 (docs/TOOLCHAIN.md, CSE, "A reload after an if whose body returns"): the copy is GCSE's;
// CSE's follow-jumps reaches the tag test because the label after the returning key-match body
// has one use and a barrier before it. Retail needs a used label or a NOTE_INSN_LOOP_END there.
// Ruled out (34 or more words): else-if, the three conditions repeated per test, the range tests
// as switch (key) with and without default, the body as an inline returning the comparison, and
// a search loop that breaks on the tag with the unlink after it (67).
// Wave 15 (docs/toolchain/cse.md, same section): -fno-cse-follow-jumps alone gives retail's
// registers. A second use of the tag label that the first CSE folds does not help (CSE goes on past
// the label); one that only GCSE's constant propagation removes is EXACT: `s32 flag = 1;` before the
// walk and `if (flag && n->key == key)`. A flag that is always 1 is not plausible, so it is not kept.
// Also ruled out: continue with prev = n in the increment, do/while with goto next, the owner test
// repeated around each key test (65), `n->key == key || n->key == tag` with the key body inside (62).
// w22 (2026-11-11): re-scored; no new lever beyond the notes above (the tag label needs a second use that survives the first
// CSE; no plain form of the key-match body or the loop gives one).
#include "common.h"
// NEAR (p58b): 34 lines, all register numbering; retail's `move v1,v0` copy of n->key for the tag test needs CSE to stop following the key-test branch. func_00183668_assert.cpp puts a compiled-out ASSERT macro (do {} while (0)) before the tag test: every register then matches, but GCC aligns one label (.p2align 3) and inserts one nop, so the branches after it are 4 bytes off. Only the do {} while (0) after `return 1` (dead code) is EXACT.

struct Self_183668;
struct Node_183668;
struct Inner_183668 { s32 pad0; s32 f4; };
struct Ctx_183668 {
    u8 pad0[0x1EC8];
    Node_183668* head;
    Node_183668* tail;
    void Clear() { tail = 0; head = 0; }
};
struct Node_183668 {
    void (*fn)(Self_183668* self, s32 key, Node_183668* list);
    Self_183668* owner;
    s32 key;
    Inner_183668* data;
    Node_183668* next;
};
struct Self_183668 {
    u8 pad0[0x14];
    Ctx_183668* ctx;
    u8 pad18[0x284];
    f32 f29C;
};

void RunScriptEventHandler(Self_183668* self, s32 key, Node_183668* list);
void ReleaseCallRecords(Ctx_183668* ctx, Node_183668* n);

s32 SuppressScriptEvent(Self_183668* self, s32 key, void* unused, s32** p)
{
    s32 tag = -1;
    switch (key) {
    case 1: {
        f32 f = self->f29C;
        if (f <= 0.0f) return 0;
        f32 g = f - *(f32*)p[0];
        s32 r = 1;
        self->f29C = g;
        if (!(0.0f < g)) r = 0;
        return r;
    }
    case 4:
        tag = 5;
        break;
    case 5:
        tag = 4;
        break;
    case 6:
    case 7:
        break;
    case 0:
    case 29:
    default:
        return 0;
    }
    Node_183668* prev = 0;
    for (Node_183668* n = self->ctx->head; n != 0; n = n->next) {
        if (n->fn == RunScriptEventHandler && n->owner == self) {
            if (n->key == key) {
                if (key >= 8) return 1;
                if (key >= 6) { s32* q = p[0]; return n->data->f4 == *q; }
                return 1;
            }
            if (n->key == tag) {
                if (prev != 0) {
                    prev->next = n->next;
                    if (n->next == 0) self->ctx->tail = prev;
                } else if (n->next != 0) {
                    self->ctx->head = n->next;
                } else {
                    Ctx_183668* c = self->ctx;
                    c->tail = 0;
                    c->head = 0;
                }
                n->next = 0;
                ReleaseCallRecords(self->ctx, n);
                return 1;
            }
        }
        prev = n;
    }
    return 0;
}
