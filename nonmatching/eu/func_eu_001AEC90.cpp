// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 177/196 (90.3%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AEC90.cpp func_eu_001AEC90 --unit src/main/001AC000.cpp
// Still differs: Like func_eu_001AD5E0 then sets f574/f570 and calls func_eu_001AED58; ours schedules the flag=0 move and p load before the f574/f570 stores (6 lines).
// Calls PAL-only func_eu_001AAFB0, replaces f4 with the callback at +0xC of the object at f4 + 0x4C (given f4 + f8 and two PAL-only floats), stores func_0015C1C0(2) through the pointer at f520 (= D_00274488) when func_0015C188(2) is not zero, then sets f574 and f570 from PAL-only globals and calls PAL-only func_eu_001AED58.
extern f32 D_eu_0027DBBC;
extern f32 D_eu_0027DBC0;
extern s32 D_eu_00263EEC;
struct Pal_eu_001AEEA0;
extern Pal_eu_001AEEA0* D_eu_0026ABE8;
extern u8 D_00274488[];
void func_eu_001AAFB0(void* self);
void func_eu_001AED58(void* self);

typedef void* (*FnG_eu_001AEC90)(void* p, f32 a, f32 b);
struct Sub_eu_001AEC90 { u8 pad[8]; s16 f8; u8 pad2[2]; FnG_eu_001AEC90 fC; };
struct Inner_eu_001AEC90 { u8 pad[0x4C]; Sub_eu_001AEC90* f4C; };
struct Ptr_eu_001AEC90 { u8 pad[0xC]; f32 fC; };
struct Obj_eu_001AEC90 { u8 pad0[4]; void* f4; u8 pad1[0x520 - 8]; void** f520; u8 pad2[0x570 - 0x524]; s32 f570; s32 f574; };

void func_eu_001AEC90(Obj_eu_001AEC90* self)
{
    func_eu_001AAFB0(self);
    Inner_eu_001AEC90* a = (Inner_eu_001AEC90*)self->f4;
    Sub_eu_001AEC90* b = a->f4C;
    self->f4 = b->fC((u8*)a + b->f8, D_eu_0027DBBC, D_eu_0027DBC0);
    if (func_0015C1C0(2) != 0) {
        self->f520 = (void**)&D_00274488;
        *self->f520 = func_0015C1C0(2);
    }
    self->f570 = D_eu_00263EEC == 3;
    self->f574 = 0;
    s32 flag = 0;
    if (D_eu_0026ABE8 != 0) {
        if (((Ptr_eu_001AEC90*)D_eu_0026ABE8)->fC != 0.0f) {
            flag = 1;
        }
    }
    self->f574 = flag;
    func_eu_001AED58(self);
}
