// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "screen_element.h"
#include "v24a2.h"
#include "game_progress.h"

struct Config_1E0848 { u8 pad000[4]; s8 marker04; u8 pad005[3]; f32 value08; f32 value0C; f32 value10; f32 value14; s32 value18; };
extern Config_1E0848 D_002758E0;
void func_001F5C0C(void* dst, s32 value, s32 size);
void func_001E0848(void* self, u32 mode)
{
	if (mode != 0xFFFF || self == 0) return;
	func_001F5C0C(&D_002758E0, 0, 0x1C);
	D_002758E0.marker04 = 0x2D;
	D_002758E0.value08 = 2.0f;
	D_002758E0.value0C = 1.0f;
	D_002758E0.value10 = 0.3f;
	D_002758E0.value14 = 0.3f;
	D_002758E0.value18 = 0xFF7D4B00;
}

void func_001E02C8(void* self, s32 n);

void func_001E0828(void* self)
{
    func_001E02C8(self, 3);
}

void func_001F5C0C(void* p, s32 zero, s32 size);

struct Glob_1E00B0 { u8 pad[0x230C]; f32 f230C; s32 f2310; void* f2314; };
struct Pool_1E00B0 { u8 pad[0xAA]; u16 fAA; };
extern Glob_1E00B0* D_00275710;
extern Pool_1E00B0 D_00262C70;
extern f32 D_0026185C;
extern s32 D_002701C4;
extern s32 D_002623DC;

void func_0016EC20(Pool_1E00B0* q, s32 n);
void func_001BE5F8(s32 q);
void func_001E02C8(T217D_1380* q, s32 n);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(T217D_510* q, f32 v);
s32 func_001E9970(void);

void func_001E00B0(T217D_1380* self)
{
    func_001AA298(self);
    switch (self->state) {
    case 0:
    case 1:
    {
        if (self->pressed != 0) {
        if (D_00262C70.fAA & 4) {
            func_0016EC20(&D_00262C70, 4);
            func_001BE5F8(D_00275710->f2310);
            if (D_00275710->f2314 != 0) {
                func_001AA8B8(self, 15.0f);
                self->vt->m08(self, (const char*)D_00275710->f2314);
            } else {
                self->vt->m15(self);
            }
            self->pressed = 0;
        } else if (D_0026185C >= 5.0f) {
            self->vt->m15(self);
            self->pressed = 0;
        }
        }
    break;
    }
    case 2:
    {
        T217D_510* o = &D_0026E760;
        s32 r;
        if (o->state == 0) {
            func_001E02C8(self, 3);
            return;
        }
        func_001AB920(o, -func_00205C78(2.0f, (f32)D_002623DC));
        r = func_001E9970();
        if (r) o->vt->m14(o); else o->vt->m15(o);
        if (D_002623C8->flags & 8) {
            s32 b = 0;
            if (r && D_002701C4 == 0 && D_002623C8->f08 < D_0026E760.time) b = 1;
            if (b) D_0026E9F8.vt->m14(&D_0026E9F8); else D_0026E9F8.vt->m15(&D_0026E9F8);
        }
    }
    break;
    }
}

struct Buf_1E02C8 { char c[0x40]; };
struct X_1E02C8 { u8 pad[4]; };

extern s32 D_002623DC;
Buf_1E02C8 D_00275900 = {};
extern X_1E02C8 D_00264A40;

void func_001AB958(T217D_510* o);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00160C48(s32 v);
void func_001DDAD0(Glob_1E00B0* g);
void func_001AB890(T217D_510* o, f32 v);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(T217D_510* o, f32 v);
void func_001AB928(T217D_510* o, f32 v, void* fn);
void func_001AB938(T217D_510* o);
s32 func_001E1FD0(Buf_1E02C8* dst, const char* fmt, ...);
void func_0018C7F8(X_1E02C8* x);
s32 func_001602A0(void);
void func_001604B8(s32 m);
void func_00194D30(T217D_6D0* y, s32 a, s32 b);
void func_00148CE0(Glob_1E00B0* g);

void func_001E02C8(T217D_1380* self, s32 n)
{
    if (self->state == n) {
        return;
    }
    switch (self->state) {
    case 1:
        if (self->pressed != 0) {
            self->vt->m15(self);
            self->pressed = 0;
        }
        break;
    case 2:
        func_001AB958(&D_0026E760);
        D_0026E760.vt->m15(&D_0026E760);
        self->vt->m15(self);
        break;
    }
    switch (n) {
    case 2: {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        func_001BFCD8(0x6D, 0, 0, 0, 3000.0f, 300.0f, one, zero, zero, 0, 0);
        func_00160C48(0);
        func_001DDAD0(D_00275710);
        func_001AB890(&D_0026E760, D_00275710->f230C + 0.99f);
        func_001AB920(&D_0026E760, -func_00205C78(2.0f, (f32)D_002623DC));
        func_001AB928(&D_0026E760, zero, 0);
        func_001AB938(&D_0026E760);
        G27C230* cam = D_002623C8;
        if (cam->flags & 8) {
            f32 t = cam->f08;
            if (t < one) {
                func_001E1FD0(&D_00275900, "Best time: &10.%d", (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 minutes = s / 60;
                s32 seconds = s % 60;
                func_001E1FD0(&D_00275900, "Best time: &1%d:%02d", minutes, seconds);
            }
            func_001AA8B8(self, zero);
            self->vt->m08(self, D_00275900.c);
        } else {
            func_001AA8B8(self, 5.0f);
            self->vt->m08(self, "Beginning Master Thief Sprint!");
        }
        self->vt->m14(self);
        break;
    }
    case 3: {
        T217D_510* o = &D_0026E760;
        s32 id;
        f32 t = o->time;
        if (0.0f < t) {
            G27C230* cam = D_002623C8;
            if (cam->flags & 8) {
                if (cam->f08 < t) {
                    cam->f08 = t;
                    id = 0x1D;
                    func_0018C7F8(&g_memoryCard);
                } else {
                    id = 0x1E;
                }
            } else {
                id = 0x1B;
                cam->flags |= 8;
                cam->f08 = o->time;
                D_002623C4->f440 = D_002623C4->f440 + 1;
                if (func_001602A0() & 8) {
                    func_001604B8(8);
                    func_0018C7F8(&g_memoryCard);
                }
            }
        } else {
            id = 0x1C;
            if (D_002623C8->flags & 8) {
                id = 0x1E;
            }
        }
        func_00194D30(&D_0026FF68, 0, id);
        break;
    }
    }
    self->state = n;
    self->stateSince = *self->clock;
    if (n == 2) {
        func_00148CE0(D_00275710);
    }
    self->active = (self->state != 0);
}

struct Out_1E0678;
void func_00137228(Out_1E0678* out, f32 x, f32 y);
void func_00137238(Out_1E0678* out, f32 x, f32 y);
void func_00137248(Out_1E0678* out, s32* value);
void func_00137260(Out_1E0678* out, s32 flag);
void func_00137268(Out_1E0678* out, s32 flag);
struct Out_1E0678 {
    u8 b[32];
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};
struct Hd_1E0678 {
    static void Draw(V24A2** h, Out_1E0678* out, void* tbl)
    {
        if (*h != 0) {
            const V24A2_Vt* vt = (*h)->vt;
            vt->drawBox((V24A2*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};

extern u8 D_00262280[];
extern f32 D_0027240C;
void func_0015C8B8(V24A2* font, f32 a, f32 b);
void func_0015DB28(void* out, void* p, V24A2* font);
void func_0015E318(void* a, void* b, s32 c, void* d);
void func_0015C900(V24A2* font);

void func_001E0678(T217D_1380* self)
{
    T217D_Word tmp;
    Out_1E0678 out;
    T217D_Word slot;
    u8 loc[0xB0];

    if (self->text[0] != 0) {
        func_0015C8B8(self->font, self->scale, self->scale);
        tmp = self->colorWord;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
        f32 p = self->w;
        f32 q = self->h;
        s32 held = tmp.v;
        out.Pos(self->shownX, self->shownY - D_0027240C * 66.40000915527344f);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(0);
        out.FlagB(0);

        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            Hd_1E0678::Draw(self->frame, &out, D_00262280);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        func_0015DB28(loc, &self->text[0], self->font);
        func_0015E318(loc, &out, 0, D_00262280);
        func_0015C900(self->font);
    }
}

// _GLOBAL_$I$ of the file, after the 16 bytes the linker left of two layout setters.
void func_001E08D8(void)
{
    func_001E0848((void*)1, 0xFFFF);
}
