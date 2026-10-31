// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the same instructions and block layout as retail; only registers differ.
// Retail reloads n->key for the tag test through a copy ($v1), which GCC CSE does not do here
// because CSE follows the key-test branch into the tag test. An empty do { } while (0) after the
// key-match return stops that and matches EXACT, but it is an artificial barrier (AGENTS.md),
// so it is not kept here. Not linked.
#include "common.h"

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

void func_001834A0(Self_183668* self, s32 key, Node_183668* list);
void func_001DBC18(Ctx_183668* ctx, Node_183668* n);

s32 func_00183668(Self_183668* self, s32 key, void* unused, s32** p)
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
        if (n->fn == func_001834A0 && n->owner == self) {
            if (n->key == key) {
                if (key >= 8) return 1;
                if (key >= 6) return *p[0] == n->data->f4;
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
                func_001DBC18(self->ctx, n);
                return 1;
            }
        }
        prev = n;
    }
    return 0;
}
