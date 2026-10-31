// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_0024F230[];

struct Node_2000F0 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

void func_002000F0(struct Node_2000F0 *self, s32 a1, s32 a2, s32 a3) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = D_0024F230;
        self->field2 = a2;
        self->field3 = a3;
    }
}

extern u8 D_0024F248[];

struct Node_200118 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

void func_00200118(struct Node_200118 *self, s32 a1, s32 a2) {
    if (self != 0) {
        self->field2 = a2;
        self->field0 = a1;
        self->vtbl = D_0024F248;
    }
}

extern u8 D_0024F260[];

void func_00200138(void* self, void* value)
{
    if (self != 0) {
        *(void**)self = value;
        *(void**)((u8*)self + 4) = D_0024F260;
    }
}

extern u8 D_0024F230[];

struct Node_2003F8 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

struct Node_2003F8 *func_002003F8(struct Node_2003F8 *self, s32 a1, s32 a2, s32 a3) {
    self->field0 = a1;
    self->vtbl = D_0024F230;
    self->field2 = a2;
    self->field3 = a3;
    return self;
}

extern u8 D_0024F248[];

void* func_00200488(void* self, void* a, void* b)
{
    *(void**)self = a;
    *(void**)((u8*)self + 4) = D_0024F248;
    *(void**)((u8*)self + 8) = b;
    return self;
}

extern u8 D_0024F260[];

void* func_00200518(void* self, void* value)
{
    *(void**)self = value;
    *(void**)((u8*)self + 4) = D_0024F260;
    return self;
}

extern u8 D_0024F278[];

void* func_002005D0(void* self)
{
    *(void**)self = D_0024F278;
    return self;
}

extern u8 D_0024F290[];

void* func_00200668(void* self)
{
    *(void**)self = D_0024F290;
    return self;
}

extern u8 D_0024F2A8[];

void* func_002006F8(void* self, void* value)
{
    *(void**)self = value;
    *(void**)((u8*)self + 4) = D_0024F2A8;
    return self;
}

extern u8 D_0024F428[];

struct Node_200C90 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

void func_00200C90(struct Node_200C90 *self, s32 a1, s32 a2) {
    if (self != 0) {
        self->field2 = a2;
        self->field0 = a1;
        self->vtbl = D_0024F428;
    }
}

extern u8 D_0024F3F8[];

struct Node_200CD8 {
    s32 field0;
    void *vtbl;
};

void func_00200CD8(struct Node_200CD8 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = D_0024F3F8;
    }
}

extern u8 D_0024F3E8[];

struct Node_200CF8 {
    s32 field0;
    void *vtbl;
};

void func_00200CF8(struct Node_200CF8 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = D_0024F3E8;
    }
}

extern u8 D_0024F3D8[];

struct Node_200D18 {
    s32 field0;
    void *vtbl;
};

void func_00200D18(struct Node_200D18 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = D_0024F3D8;
    }
}

extern u8 D_0024F3C8[];

struct Node_200D38 {
    s32 field0;
    void *vtbl;
};

void func_00200D38(struct Node_200D38 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = D_0024F3C8;
    }
}

extern u8 D_0024F418[];

struct Node_200CB0 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

void func_00200CB0(struct Node_200CB0 *self, s32 a1, s32 a2, s32 a3) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = D_0024F418;
        self->field2 = a3;
        self->field3 = a2;
    }
}
