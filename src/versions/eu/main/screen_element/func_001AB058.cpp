// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's per-frame step of a sliding UI object: moves the position toward its target, fires the callback on arrival, refreshes the text and its placement.
extern f32 D_eu_00262B60;

typedef void (*Callback_eu_1AB058)(void* arg);

struct Handle_eu_1AB058 { u8 pad0[8]; s32 count; u8 padC[0x3C]; f32 scale; };
struct Loc_eu_1AB058 { u8 pad0[0xC0]; };

struct Obj_eu_1AB058 {
    s32 f0;
    Handle_eu_1AB058* handle;
    u16 flag;
    u8 pad1[0x51C - 10];
    f32 f51c;
    u8 pad2[0x570 - 0x520];
    s32 f570;
    s32* f574;
    f32 f578;
    f32 f57c;
    f32 f580;
    Callback_eu_1AB058 f584;
    void* f588;
};

void func_eu_001AAFE0(Obj_eu_1AB058* self);
void FormatCounterCaption(Obj_eu_1AB058* self);
void PushFontScale(Handle_eu_1AB058* handle, f32 a, f32 b);
void func_eu_0015DCB8(Loc_eu_1AB058* out, u16* flag, Handle_eu_1AB058* handle, s32 zero);
f32 func_eu_0015E438(Loc_eu_1AB058* loc);
void SetScreenElementSize(Obj_eu_1AB058* self, f32 x, f32 y);
void PopFontScale(Handle_eu_1AB058* handle);

void UpdateCounterCaption(Obj_eu_1AB058* self)
{
    Loc_eu_1AB058 loc;
    f32 frac;
    s32 n;
    s32 first;
    s32* p;

    func_eu_001AAFE0(self);
    p = self->f574;
    if (self->f570 == *p) {
        return;
    }
    if (self->f570 >= 0) {
        frac = D_eu_00262B60 * self->f57c + self->f580;
        n = (s32)frac;
        self->f580 = frac - (f32)n;
        first = *self->f574;
        if (first < self->f570) {
            s32 lo = self->f570 - n;
            self->f570 = first < lo ? lo : first;
        } else {
            s32 hi = self->f570 + n;
            self->f570 = hi < first ? hi : first;
        }
    } else {
        self->f570 = *p;
    }
    if (self->f570 == *self->f574 && self->f584 != 0) {
        self->f584(self->f588);
        self->f584 = 0;
        self->f588 = 0;
    }
    FormatCounterCaption(self);
    if (self->flag != 0) {
        PushFontScale(self->handle, self->f51c, self->f51c);
        func_eu_0015DCB8(&loc, &self->flag, self->handle, 0);
        f32 x = func_eu_0015E438(&loc);
        f32 y = (f32)self->handle->count * self->handle->scale;
        SetScreenElementSize(self, x, y);
        PopFontScale(self->handle);
    } else {
        SetScreenElementSize(self, 0.0f, 0.0f);
    }
}
