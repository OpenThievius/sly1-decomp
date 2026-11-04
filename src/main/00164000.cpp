// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"


void func_001CA5E0(void);

void func_00167EF0(void)
{
    func_001CA5E0();
}

struct Ctx_167E08 { u8 pad0[0x14]; void* p14; u8 pad1[0x750 - 0x18]; void* p750; u8 pad2[0xC18 - 0x754]; s32 c18; s32 c1c; u8 pad3[0xC30 - 0xC20]; s32 c30; s32 c34; };
struct Ent_167E08 { u8 pad0[0x328]; s32 f328; };
struct Out_167E08 { s32 count; Ent_167E08** items; };

void func_001C72A0(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0018D608(void);
void func_0018D6F0(void);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_00167E08(Ctx_167E08* self)
{
    Out_167E08 out;
    s32 i;

    func_001C72A0(self);
    if (self->c18 != -1) {
        self->c1c = (s32)func_0015A448(self->p14, self->c18, self);
    }
    if (self->c30 != -1) {
        self->c34 = (s32)func_0015A448(self->p14, self->c30, self);
    }
    if (self->p750 != 0) {
        func_0018D608();
        func_0012D1B0(self->p750, self, &out.count, (void**)&out.items);
        for (i = 0; i < out.count; i++) {
            Ent_167E08* e = out.items[i];
            if (e->f328 == 0) {
                void* t = func_001EFA30();
                e->f328 = (s32)t;
                func_001EFA60(t, e);
            }
        }
        func_0018D6F0();
    }
}

struct Cfg_167D68 {
    u8 pad_000[0x738];
    s32 f738;
    f32 f73C;
    u8 pad_740[0x0C];
    f32 f74C;
    u8 pad_750[0x4C0];
    f32 fC10;
    f32 fC14;
    s32 fC18;
    u8 padC1C[0x4];
    f32 fC20;
    f32 fC24;
    f32 fC28;
    f32 fC2C;
    s32 fC30;
};

void func_001C6F48(void* self);
void func_00167D68(Cfg_167D68* self);

void func_00167D68(Cfg_167D68* self)
{
    func_001C6F48(self);
    self->fC20 = 1000.0f;
    self->fC24 = 1500.0f;
    self->fC28 = 0.78539816f;
    self->fC2C = 3.14159265f;
    self->fC10 = 2000.0f;
    self->fC30 = -1;
    self->fC14 = 300.0f;
    self->fC18 = -1;
    self->f73C = 300.0f;
    self->f738 = 0;
    self->f74C = 1.04719755f;
}

// Data of src/main/file_15F678.cpp, defined here until the file's own data is proved.
