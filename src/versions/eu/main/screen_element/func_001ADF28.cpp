// SPDX-License-Identifier: AGPL-3.0-or-later
// Calls PAL-only SetupScreenElementText, replaces f4 with the callback at +0xC of the object at f4 + 0x4C (given f4 + f8 and two PAL-only floats), stores func_0015C1C0(2) through the pointer at f520 (= D_00274488) when func_0015C188(2) is not zero, then sets f574 and f570 from PAL-only globals and calls PAL-only func_eu_001AED58.
extern f32 D_eu_0027DBBC;
extern f32 D_eu_0027DBC0;
extern s32 D_eu_00263EEC;
struct Pal_eu_001AEEA0;
// Read as an aggregate's first word (its neighbours at 0x26ABE4 and 0x26ABEC are written through a base), so the
// load waits behind the stores to self, as retail's does.
extern Pal_eu_001AEEA0* D_eu_0026ABE8[];
void SetupScreenElementText(void* self);
void func_eu_001AED58(void* self);

typedef void* (*FnG_eu_001AEC90)(void* p, f32 a, f32 b);
struct Sub_eu_001AEC90 { u8 pad[8]; s16 f8; u8 pad2[2]; FnG_eu_001AEC90 fC; };
struct Inner_eu_001AEC90 { u8 pad[0x4C]; Sub_eu_001AEC90* f4C; };
struct Ptr_eu_001AEC90 { u8 pad[0xC]; f32 fC; };
struct Obj_eu_001AEC90 { u8 pad0[4]; void* f4; u8 pad1[0x520 - 8]; void** f520; u8 pad2[0x570 - 0x524]; s32 f570; s32 f574; };

void InitPromptElement(Obj_eu_001AEC90* self)
{
    SetupScreenElementText(self);
    Inner_eu_001AEC90* a = (Inner_eu_001AEC90*)self->f4;
    Sub_eu_001AEC90* b = a->f4C;
    self->f4 = b->fC((u8*)a + b->f8, D_eu_0027DBBC, D_eu_0027DBC0);
    if (GetFontById(2) != 0) {
        self->f520 = (void**)&D_00274488;
        *self->f520 = GetFontById(2);
    }
    self->f570 = D_eu_00263EEC == 3;
    self->f574 = 0;
    s32 flag = 0;
    if (D_eu_0026ABE8[0] != 0) {
        if (((Ptr_eu_001AEC90*)D_eu_0026ABE8[0])->fC != 0.0f) {
            flag = 1;
        }
    }
    self->f574 = flag;
    func_eu_001AED58(self);
}
