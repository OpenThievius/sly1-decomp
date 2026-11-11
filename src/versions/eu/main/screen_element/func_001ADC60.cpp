// SPDX-License-Identifier: AGPL-3.0-or-later
// Runs the sub-object's update with two table floats, stores the result, sets the pointer at 0x520, then stores a timer value and either moves the object or sets its text.
extern f32 D_eu_0027DB98;
extern f32 D_eu_0027DB9C;
extern u8 D_eu_0027DBA0[];

struct SubInfo_eu_1AE9C0 {
    u8 pad[8];
    s16 off;
    u8 pad2[2];
    s32 (*fn)(void* self, f32 a, f32 b);
};
struct Sub_eu_1AE9C0 {
    u8 pad[0x4C];
    SubInfo_eu_1AE9C0* info;
};
struct Obj_eu_1AE9C0 {
    void** vt;
    Sub_eu_1AE9C0* sub;
    u8 pad8[0x518];
    s32* f520;
    u8 pad524[0x4C];
    s32 f570;
};

void SetupScreenElementText(Obj_eu_1AE9C0* self);
void* FindAnimRecord(s32 id);
void SetScreenElementSize(Obj_eu_1AE9C0* self, f32 x, f32 y);
const char* func_eu_001DDAB0(s32 id);

void InitTitleElement(Obj_eu_1AE9C0* self)
{
    SetupScreenElementText(self);
    Sub_eu_1AE9C0* sub = self->sub;
    self->sub = (Sub_eu_1AE9C0*)sub->info->fn((u8*)sub + sub->info->off, D_eu_0027DB98, D_eu_0027DB9C);
    if (GetFontById(2) != 0) {
        self->f520 = (s32*)D_eu_0027DBA0;
        *self->f520 = (s32)GetFontById(2);
    }
    s32 r = (s32)FindAnimRecord(0x493);
    self->f570 = r;
    if (r != 0) {
        SetScreenElementSize(self, 366.75f, 165.75f);
    } else {
        const char* text = func_eu_001DDAB0(0xB);
        ((void (*)(void*, const char*))self->vt[8])(self, text);
    }
}
