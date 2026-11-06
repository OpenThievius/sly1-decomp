// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"


void func_001CA5E0(void);

void func_00167EF0(void)
{
    DrawAgent();
}

struct Ent_167E08 { u8 pad0[0x328]; s32 f328; };
struct Out_167E08 { s32 count; Ent_167E08** items; };

void func_001C72A0(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0018D608(void);
void func_0018D6F0(void);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_00167E08(C0A* self)
{
    Out_167E08 out;
    s32 i;

    StartAgent(self);
    if (self->fC18 != -1) {
        self->fC1C = (s32)func_0015A448(self->world, self->fC18, self);
    }
    if (self->fC30 != -1) {
        self->fC34 = (s32)func_0015A448(self->world, self->fC30, self);
    }
    if (self->f750 != 0) {
        PushBackMemoryMark();
        GatherAnimationEventObjects(self->f750, self, &out.count, (void**)&out.items);
        for (i = 0; i < out.count; i++) {
            Ent_167E08* e = out.items[i];
            if (e->f328 == 0) {
                void* t = func_001EFA30();
                e->f328 = (s32)t;
                AppendToSmallList(t, e);
            }
        }
        PopBackMemoryMark();
    }
}

void func_001C6F48(void* self);
void func_00167D68(C0A* self);

void func_00167D68(C0A* self)
{
    InitAgent(self);
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
