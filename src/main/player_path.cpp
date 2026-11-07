// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"

// The file's .data, in retail's order; the label only its assembly reads is included.
float D_00274F00 = 35.0f;
float D_00274F04 = 100.0f;
float D_00274F08 = 0.5f;
INCLUDE_DATA(D_00274F0C);
float D_00274F14 = 50.0f;
float D_00274F18 = 1.0f;
float D_00274F1C = 0.400000006f;
float D_00274F20[2] = {10.0f, 0.0f};
float D_00274F28[4] = {1500.0f, 0.0f, 0.5f, 0.0f};

struct TwoEntryBlendEntry {
    u8 pad0[4];
    void* p4;
    u8 pad8[4];
    f32 fC;
};

void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);
void func_0012CD78(f32 f12, f32 f13, void* a0, void* a1, void* a2, s32 a3, void* a4, s32 a5, void* a6, s32 a7);

void func_001D14F0(Player* self)
{
    f32 out[4];
    TwoEntryBlendEntry* e = (TwoEntryBlendEntry*)self->f103C;
    s32 i = 1;
    do {
        func_0012CD78(0.0f, 1.0f, e->p4, self->f614, self, 1, 0, 0, out, 0);
        e->fC = out[2];
        e++;
        i--;
    } while (i >= 0);
    func_00139038(self, 0x10, 2, self->f103C, 0, 0, 0, &self->f105C);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f618, self, 1, &self->f23E0, 0, 0, 0);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f614, self, 1, &self->f23F0, 0, 0, 0);
    f32 avg = (self->f23E0 + self->f23F0) * 0.5f;
    self->f23F4 = 0.0f;
    self->f23E4 = 0.0f;
    self->f23F0 = avg;
    self->f23E0 = avg;
}

ASM_FUNC(func_001D1630);

ASM_FUNC(func_001D1A80);

ASM_FUNC(func_001D1BB0);

ASM_FUNC(func_001D2518);

void func_001DDA20(void* a);
void func_001DDB58(void* a);
void func_001DDA50(void* a);
void func_001DDBB8(void* a);

void func_001D27C0(Player* a0, s32 a1)
{
    if (a0->f2718 != a1) {
        if (a0->f2718 == -1) {
            AcquirePadSelectFlag(a0->world);
            ShowCountedScreenElement(a0->world);
        }
        a0->f2718 = a1;
        if (a1 == -1) {
            ReleasePadSelectFlag(a0->world);
            HideCountedScreenElement(a0->world);
        }
    }
}

ASM_FUNC(func_001D2830);
