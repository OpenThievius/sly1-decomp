// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "contact_tracker.h"
#include "lookup_object.h"
#include "object_sub_group.h"
#include "switched_collider.h"
#include "animation.h"
#include "screen_fade.h"

struct Obj_1F7E58 { u8 pad[0x10]; u32 flags; u8 pad2[4]; s32 field_18; };
void func_001F7E58(Obj_1F7E58* self) { self->field_18 = 0; self->flags &= ~1u; }

struct Obj_1F7FC0 { u8 pad[0x28]; struct Node* root; };
struct Node { u8 pad0[8]; Node* child; u8 pad1[0x2C]; Node* next; };
void* func_001F7FC0(u32 key, Obj_1F7FC0* obj) { Node* node = obj->root; while (node) { Node* child = node->child; while (child) { if (*(u32*)child == key) return child; child = child->next; } node = *(Node**)((u8*)node + 0x14); } return 0; }

extern u8 D_0027696C[];
void func_001F66F8(void* value) { void* p = *(void**)g_randomState; *(void**)((u8*)p + 0x58) = value; }
