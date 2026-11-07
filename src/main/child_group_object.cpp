// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "child_group_object.h"
#include "object_message.h"

// The file's .data, in retail's order: class 0x3B's set-up values, then the constants of its
// assembly functions.
Quad3B D_00261320 = { 0x42480000, 0x459C4000, 0, 0 };
Quad3B D_00261330 = { 0x43FA0000, 0x3FE66666, 0, 0 };
Quad3B D_00261340 = { 0x3F000000, 0x3E4CCCCD, 0, 0 };
Pair3B D_00261350 = { 0x44160000, 0x44AF0000 };
Pair3B D_00261358 = { 0x41A00000, 0x42480000 };
f32 D_00261360 = 600.0f;
INCLUDE_DATA(D_00261364);
f32 D_00261370[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 D_00261380[4] = { 2.0f, -1.5f, 0.0f, 0.0f };

void func_001B7968(Collider* self);

void func_0013B4C0(ChildGroupObject* self)
{
    InitCollider(self);
    self->f554 = 3.4028235e+38f;
    self->f55C = 200.0f;
    self->f560 = 200.0f;
    self->f550 = 0;
    self->f56C = *(Pair3B*)&D_00261320;
    self->f568 = 800.0f;
    self->f574 = 5000.0f;
    self->f5D0 = *(Quad3B*)&D_00261330;
    self->f5E0 = *(Pair3B*)&D_00261350;
    self->f5F0 = *(Quad3B*)&D_00261340;
    self->f600 = *(Pair3B*)&D_00261358;
    self->f674 = 1;
    self->f678 = 1;
    self->f67C = 0;
}

void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);

void func_0013B598(ChildGroupObject* self)
{
    LoadCollider(self);
    FindOrBuildMemberGroup(&self->member5BC, self);
}

void func_001BA130(void* self, void* other);
u32 func_0018D568(s32 size, void* src);

void func_0013B5C8(ChildGroupObject* self, ChildGroupObject* other)
{
    CopyCollider(self, other);
    if (other->slot) self->slot = (void*)CopyToFrontMemory(0x24, other->slot);
}

struct List_13B610 { s32 head; s32 pad; s32 off; };
struct Frame_13B610;
struct Frame_13B610 {
    void* base; void* cur; s32 off; Frame_13B610* prev;
    Frame_13B610(List_13B610* l) {
        cur = l;
        base = l;
        Frame_13B610* p = (Frame_13B610*)g_activeListFrames;
        off = l->off;
        g_activeListFrames = (ListFrame*)this;
        prev = p;
    }
    ~Frame_13B610() { g_activeListFrames = (ListFrame*)prev; }
};

void func_00124A48(void* self);
s32 func_001300E8(void* node, s32 kind);
void func_00182ED8(s32 a);
void* func_0018D500(s32 size);

void func_0013B610(ChildGroupObject* self)
{
    StartPlacedObject(self);
    Frame_13B610 f((List_13B610*)&self->children);
    void* n;
    void* t = *(void**)f.base;
    f.cur = (u8*)t + f.off;
    n = t;
    if (n != 0) {
        do {
            if (IsObjectOfKind(n, 0x27)) {
                s32 c = self->count;
                if ((u32)c < 16) {
                    self->arr[c] = (s32)n;
                    self->count = c + 1;
                    ResolveAndStartObject((s32)n);
                }
            }
            void* c = f.cur; s32 o = f.off; void* a = *(void**)c;
            f.cur = (u8*)a + o; n = a;
        } while (n != 0);
    }
    if (self->active != 0) {
        self->entries = (Entry3B*)AllocateFrontMemory(0xC0);
    }
}

void func_00127378(ChildGroupObject* self, s32 kind, ObjectMessage* msg);
void func_0013BE00(ChildGroupObject* p, f32 delta);

void func_0013B708(ChildGroupObject* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0xA) {
        if ((ChildGroupObject*)msg->target == self) {
            if (((ChildGroupObject*)msg->target)->f550 == 0) {
                StartChildGroupDelay((ChildGroupObject*)msg->target, 0.0f);
            }
        }
    }
}

ASM_FUNC(func_0013B778);

ASM_FUNC(func_0013B828);

s32 func_00185D20(void*, s32, void*, void*, s32, s32, s32, void*, f32);

void func_0013B9D8(ChildGroupObject* self, s32 key, s32 a2, s32 a3, s32 a4, void* arg5)
{
    s32 i;
    if (self->active) {
        for (i = 0; i < self->entryCount; i++) {
            if (self->entries[i].key == key) break;
        }
        if (i < self->entryCount) {
            Entry3B* e = &self->entries[i];
            func_00185D20(self, key, e, &e->data, 9, 0, 0, arg5, e->value);
        }
    }
}

ASM_FUNC(func_0013BA70);

ASM_FUNC(func_0013BBA0);

ASM_FUNC(func_0013BC80);

extern f32 D_0026185C;

void func_0013BE00(ChildGroupObject* self, f32 delta)
{
    self->f554 = g_gameTime + delta;
}

ASM_FUNC(func_0013BE18);

// The FLT_MAX func_0013BF68 loads, the last of the file's .rodata.
extern const f32 D_00249D78 = 3.4028235e+38f;

ASM_FUNC(func_0013BF68);

void func_001BE4D8(void* p);

s32 func_0013C950(ChildGroupObject* self)
{
    if (self->slot == 0) {
        InitSoundParams(&self->slot);
    }
    return (s32)self->slot;
}
