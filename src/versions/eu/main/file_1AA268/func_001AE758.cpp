// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's flag pair and the field at 8 are 16-bit.
typedef void (*VFn_1AE758)(void* self, void* arg);
void func_001AA268(void* self);
void func_001AA8B0(void* self, f32 v);
void func_001AA8C0(void* self, f32 v);
void func_001AA8B8(void* self, f32 v);
void func_001AA788(void* self, f32 v);
struct Flags_1AE758_eu { u16 a; u16 b; };
struct Obj_1AE758_eu { VFn_1AE758* vtbl; void* f4; u16 f8; };

void func_001AE758(Obj_1AE758_eu* self)
{
    f32 k = 0.25f;
    Flags_1AE758_eu fl;
    s32 v;

    SetupScreenElementText(self);
    SetScreenElementSlideInTime(self, k);
    SetScreenElementSlideOutTime(self, k);
    SetScreenElementHoldTime(self, 0.0f);
    void* r = GetFontById(1);
    f32 g = *(f32*)&D_002744AC;
    self->f4 = r;
    SetScreenElementScale(self, g);
    v = GetCyclingGlyph();
    fl.b = 0;
    fl.a = v;
    self->vtbl[8](self, &fl);
    self->f8 = 0;
}
