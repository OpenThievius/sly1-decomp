// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

struct VT_1E00B0 { u8 pad[0x20]; void (*m20)(void*, void*); u8 pad24[0x14]; void (*m38)(void*); void (*m3C)(void*); };
struct Obj_1E00B0 { VT_1E00B0* vt; u8 pad04[0x25C]; s32 f260; u8 pad264[4]; f32 f268; s32 f26C; };
struct Glob_1E00B0 { u8 pad[0x230C]; f32 f230C; s32 f2310; void* f2314; };
struct Cam_1E00B0 { s32 flags; u8 pad[4]; f32 f08; };
struct Pool_1E00B0 { u8 pad[0xAA]; u16 fAA; };
extern Obj_1E00B0 D_0026E760;
extern Obj_1E00B0 D_0026E9F8;
extern Glob_1E00B0* D_00275710;
extern Cam_1E00B0* D_002623C8;
extern Pool_1E00B0 D_00262C70;
extern f32 D_0026185C;
extern s32 D_002701C4;
extern s32 D_002623DC;
void func_001AA298(Obj_1E00B0* q);
void func_0016EC20(Pool_1E00B0* q, s32 n);
void func_001BE5F8(s32 q);
void func_001AA8B8(Obj_1E00B0* q, f32 v);
void func_001E02C8(Obj_1E00B0* q, s32 n);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(Obj_1E00B0* q, f32 v);
s32 func_001E9970(void);

void func_001E00B0(Obj_1E00B0* self)
{
    func_001AA298(self);
    switch (self->f260) {
    case 0:
    case 1:
    {
        if (self->f26C != 0) {
        if (D_00262C70.fAA & 4) {
            func_0016EC20(&D_00262C70, 4);
            func_001BE5F8(D_00275710->f2310);
            if (D_00275710->f2314 != 0) {
                func_001AA8B8(self, 15.0f);
                self->vt->m20(self, D_00275710->f2314);
            } else {
                self->vt->m3C(self);
            }
            self->f26C = 0;
        } else if (D_0026185C >= 5.0f) {
            self->vt->m3C(self);
            self->f26C = 0;
        }
        }
    break;
    }
    case 2:
    {
        Obj_1E00B0* o = &D_0026E760;
        s32 r;
        if (o->f260 == 0) {
            func_001E02C8(self, 3);
            return;
        }
        func_001AB920(o, -func_00205C78(2.0f, (f32)D_002623DC));
        r = func_001E9970();
        if (r) o->vt->m38(o); else o->vt->m3C(o);
        if (D_002623C8->flags & 8) {
            s32 b = 0;
            if (r && D_002701C4 == 0 && D_002623C8->f08 < D_0026E760.f268) b = 1;
            if (b) D_0026E9F8.vt->m38(&D_0026E9F8); else D_0026E9F8.vt->m3C(&D_0026E9F8);
        }
    }
    break;
    }
}

struct VT_1E02C8 { u8 pad[0x20]; void (*m20)(void*, void*); u8 pad24[0x14]; void (*m38)(void*); void (*m3C)(void*); };
struct Obj_1E02C8 { VT_1E02C8* vt; u8 pad04[0x254]; f32* f258; s32 f25C_pad; s32 f260; f32 f264; s32 f268; s32 f26C; };
struct Cnt_1E02C8 { u8 pad[0x440]; s32 f440; };
struct Buf_1E02C8 { char c[0x40]; };
struct X_1E02C8 { u8 pad[4]; };
struct Y_1E02C8 { u8 pad[4]; };

extern Cnt_1E02C8* D_002623C4;
extern s32 D_002623DC;
Buf_1E02C8 D_00275900 = {};
extern X_1E02C8 D_00264A40;
extern Y_1E02C8 D_0026FF68;

void func_001AB958(Obj_1E00B0* o);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00160C48(s32 v);
void func_001DDAD0(Glob_1E00B0* g);
void func_001AB890(Obj_1E00B0* o, f32 v);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(Obj_1E00B0* o, f32 v);
void func_001AB928(Obj_1E00B0* o, f32 v, void* fn);
void func_001AB938(Obj_1E00B0* o);
s32 func_001E1FD0(Buf_1E02C8* dst, const char* fmt, ...);
void func_001AA8B8(Obj_1E02C8* o, f32 v);
void func_0018C7F8(X_1E02C8* x);
s32 func_001602A0(void);
void func_001604B8(s32 m);
void func_00194D30(Y_1E02C8* y, s32 a, s32 b);
void func_00148CE0(Glob_1E00B0* g);

void func_001E02C8(Obj_1E02C8* self, s32 n)
{
    if (self->f260 == n) {
        return;
    }
    switch (self->f260) {
    case 1:
        if (self->f26C != 0) {
            self->vt->m3C(self);
            self->f26C = 0;
        }
        break;
    case 2:
        func_001AB958(&D_0026E760);
        D_0026E760.vt->m3C(&D_0026E760);
        self->vt->m3C(self);
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
        Cam_1E00B0* cam = D_002623C8;
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
            self->vt->m20(self, &D_00275900);
        } else {
            func_001AA8B8(self, 5.0f);
            self->vt->m20(self, (void*)"Beginning Master Thief Sprint!");
        }
        self->vt->m38(self);
        break;
    }
    case 3: {
        Obj_1E00B0* o = &D_0026E760;
        s32 id;
        f32 t = o->f268;
        if (0.0f < t) {
            Cam_1E00B0* cam = D_002623C8;
            if (cam->flags & 8) {
                if (cam->f08 < t) {
                    cam->f08 = t;
                    id = 0x1D;
                    func_0018C7F8(&D_00264A40);
                } else {
                    id = 0x1E;
                }
            } else {
                id = 0x1B;
                cam->flags |= 8;
                cam->f08 = o->f268;
                D_002623C4->f440 = D_002623C4->f440 + 1;
                if (func_001602A0() & 8) {
                    func_001604B8(8);
                    func_0018C7F8(&D_00264A40);
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
    self->f260 = n;
    self->f264 = *self->f258;
    if (n == 2) {
        func_00148CE0(D_00275710);
    }
    self->f268 = (self->f260 != 0);
}

struct __attribute__((packed)) Pk4_1E0678 { s32 v; };
typedef void (*VFn_1E0678)(void* self, void* handle, void* out, void* tbl);
struct VTab_1E0678 { u8 pad0[0x48]; s16 adj; u8 pad1[0x4C - 0x4A]; VFn_1E0678 fn; };
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
    static void Draw(void* h, Out_1E0678* out, void* tbl)
    {
        if (*(void**)h != 0) {
            VTab_1E0678* vt = *(VTab_1E0678**)((u8*)*(void**)h + 0x4C);
            vt->fn((u8*)*(void**)h + vt->adj, h, out, tbl);
        }
    }
};
struct Obj_1E0678 {
    u8 pad0[4];
    s32 f4;
    s8 f8;
    u8 pad9[0x208 - 9];
    Pk4_1E0678 f208;
    f32 f20c;
    void* f210;
    u8 pad214[0x224 - 0x214];
    f32 f224;
    f32 f228;
    u8 pad22c[0x234 - 0x22C];
    f32 f234;
    f32 f238;
    f32 f23c;
};

extern u8 D_00262280[];
extern f32 D_0027240C;
void func_0015C8B8(s32 handle, f32 a, f32 b);
void func_0015DB28(void* out, void* p, s32 handle);
void func_0015E318(void* a, void* b, s32 c, void* d);
void func_0015C900(s32 handle);

void func_001E0678(Obj_1E0678* self)
{
    Pk4_1E0678 tmp;
    Out_1E0678 out;
    Pk4_1E0678 slot;
    u8 loc[0xB0];

    if (self->f8 != 0) {
        func_0015C8B8(self->f4, self->f20c, self->f20c);
        tmp = self->f208;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->f23c);
        f32 p = self->f234;
        f32 q = self->f238;
        s32 held = tmp.v;
        out.Pos(self->f224, self->f228 - D_0027240C * 66.40000915527344f);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(0);
        out.FlagB(0);

        u8* h = (u8*)self->f210;
        if (h != 0) {
            slot = *(Pk4_1E0678*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->f23c);
            Hd_1E0678::Draw(self->f210, &out, D_00262280);
            *(Pk4_1E0678*)((u8*)self->f210 + 0x18) = slot;
        }
        func_0015DB28(loc, &self->f8, self->f4);
        func_0015E318(loc, &out, 0, D_00262280);
        func_0015C900(self->f4);
    }
}

