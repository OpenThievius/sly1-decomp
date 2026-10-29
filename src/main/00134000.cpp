// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Node_1363D0 { u8 pad0[0x324]; void* child; };

void func_001AA8C8(void* self);
void func_00150790(void* obj, s32 mode);

void func_001363D0(Node_1363D0* self)
{
    func_001AA8C8(self);
    if (self->child != 0) {
        func_00150790(self->child, 2);
    }
}

struct Child_136EF8 { u8 pad0[0x2D0]; s32 kind; };
struct Owner_136EF8 { u8 pad0[0x324]; Child_136EF8* child; };

void func_001356C0(Owner_136EF8* self, s32 mode);
void func_00150790(Child_136EF8* obj, s32 mode);

void func_00136EF8(Owner_136EF8* self)
{
    if (self->child != 0) {
        switch (self->child->kind) {
        case 0:
            func_001356C0(self, 2);
            break;
        case 1:
            func_001356C0(self, 3);
            break;
        case 2:
            func_001356C0(self, 4);
            break;
        }
        func_00150790(self->child, 3);
    } else {
        func_001356C0(self, 1);
    }
}

struct Obj_137268 { u8 pad[0x18]; void* field18; };

void func_00137268(Obj_137268* self, void* value)
{
    self->field18 = value;
}

struct Pair_1373B0 { void* first; s32 second; };

void func_00137328(void* a, void* b, s32 c);

void func_001373B0(void* a, Pair_1373B0* pair)
{
    func_00137328(a, pair->first, pair->second);
}

struct Ring_137B60 { u8 pad0[0x18]; s32 head; s32 size; };

void func_00137B60(Ring_137B60* self, s32 n)
{
    s32 head = self->head;
    s32 t = head - 1;
    t = t + n;
    s32 aligned = t & -n;
    s32 delta = aligned - head;
    self->head = aligned;
    self->size -= delta;
}
