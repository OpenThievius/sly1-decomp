// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001451F0(u32, int, int, void*, int, void*);
void func_00125C90();
struct Obj_1F4308 { u8 pad[0x98]; s32 state; f32 value; };
void func_001F4308(Obj_1F4308* self, f32 value) { self->value = value; self->state = 1; }
void func_001F51C8() { func_00125C90(); }
void* func_001F5208(void* self) { return (u8*)self + 0x550; }
struct Obj_1F5210 { u8 pad[0x5E4]; s32 value; };
void func_001F5210(Obj_1F5210* self) { self->value = 0; }
struct Obj_1F7E58 { u8 pad[0x10]; u32 flags; u8 pad2[4]; s32 field_18; };
void func_001F7E58(Obj_1F7E58* self) { self->field_18 = 0; self->flags &= ~1u; }
void func_00123ED0(void*);
struct Obj_1F4E18 { u8 pad[0x2D0]; s32 value; };
void func_001F4E18(Obj_1F4E18* self) { func_00123ED0(self); self->value = -1; }
void func_001F57E0(void*);
int func_001F51E8(void* self) { func_001F57E0((u8*)self + 0x550); return 1; }
struct Obj_1F7FC0 { u8 pad[0x28]; struct Node* root; };
struct Node { u8 pad0[8]; Node* child; u8 pad1[0x2C]; Node* next; };
void* func_001F7FC0(u32 key, Obj_1F7FC0* obj) { Node* node = obj->root; while (node) { Node* child = node->child; while (child) { if (*(u32*)child == key) return child; child = child->next; } node = *(Node**)((u8*)node + 0x14); } return 0; }
struct Obj_1F5840 { u8 pad[0x10]; s32 count; void* entries[8]; };
void func_001F5840(Obj_1F5840* self, void* entry) { u32 n = self->count; if (n < 32) { self->entries[n] = entry; self->count = n + 1; } }
extern u8 D_0027696C[];
void func_001F66F8(void* value) { void* p = *(void**)D_0027696C; *(void**)((u8*)p + 0x58) = value; }
void func_001F5590(void* a, void* b) { *(void**)a = b; *(u32*)((u8*)a + 4) = 0; *(f32*)((u8*)a + 8) = 150.0f; }
extern u8 D_00261990[];
void func_00145088(u32, int, void*, int, void*);
void func_001F4F20(void* self) { if (*(s32*)((u8*)self + 0x310)) { func_001451F0(*(u32*)D_00261990, 0xB, 7, (u8*)*(u32*)D_00261990 + 0x510, 0, self); *(s32*)((u8*)self + 0x310) = 0; } }
struct Obj_1F51A0 { u8 pad[0x550]; void* field; };
void* func_001BA130(void*);
void func_001F51A0(Obj_1F51A0* self) { func_001BA130(self); self->field = self; }
void func_0013EC00(void*, int, void*, void*, void*, void*, void*);
void func_001F42D0(void* self, void* a1, void* a2, void* a3, void* a4) { func_0013EC00((u8*)self + 0xB8, 4, (u8*)self + 0xB4, a1, a2, a3, a4); }
extern u32 D_00277134;
void func_00124A48(void*);
void func_001F55A8(void*);
void func_001F4FD8(void* self) { func_00124A48(self); func_001F55A8((u8*)self + 0x550); }
void func_001FA468();
void func_001F4ED0(void* self) { if (!*(s32*)((u8*)self + 0x310)) { func_00145088(*(u32*)D_00261990, 7, (u8*)*(u32*)D_00261990 + 0x510, 0, self); *(s32*)((u8*)self + 0x310) = 1; } }

s32 func_001F3C38(void* a, void* b);
s32 func_001F4008(void* x);
s32 func_001925F0(void);
s32 func_00192620(void);
s32 func_001929D0(void* v);

s32 func_001F4318(void* unused, void* a, void* b)
{
    s32 r = func_001F3C38(a, b);
    if (r != 0) {
        r = func_001F4008((void*)r);
        goto done;
    }
    r = func_001925F0();
    if (r == 0) {
        r = func_00192620();
        if (r != 0) {
            r = func_001929D0((void*)r);
        }
    }
done:
    return r;
}
