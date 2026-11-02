// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 929/944 (98.4%), checked 2026-11-02
#include "common.h"
// NEAR: only register choice differs: final n==2 test uses li v1,2/lw v0 (retail li v0,2/lw v1), and the s/60 string lui sits before li v1,60 (retail after). Literal string flagged by check.py.

struct VT_1E02C8 { u8 pad[0x20]; void (*m20)(void*, void*); u8 pad24[0x14]; void (*m38)(void*); void (*m3C)(void*); };
struct Obj_1E02C8 { VT_1E02C8* vt; u8 pad04[0x254]; f32* f258; s32 f25C_pad; s32 f260; f32 f264; s32 f268; s32 f26C; };
struct Obj2_1E02C8 { VT_1E02C8* vt; u8 pad04[0x264]; f32 f268; };
struct Glob_1E02C8 { u8 pad[0x230C]; f32 f230C; };
struct Cam_1E02C8 { u32 flags; u8 pad[4]; f32 f08; };
struct Cnt_1E02C8 { u8 pad[0x440]; s32 f440; };
struct Buf_1E02C8 { char c[1]; };
struct X_1E02C8 { u8 pad[4]; };
struct Y_1E02C8 { u8 pad[4]; };

extern Obj2_1E02C8 D_0026E760;
extern Glob_1E02C8* D_00275710;
extern Cam_1E02C8* D_002623C8;
extern Cnt_1E02C8* D_002623C4;
extern s32 D_002623DC;
extern Buf_1E02C8 D_00275900;
extern X_1E02C8 D_00264A40;
extern Y_1E02C8 D_0026FF68;

void func_001AB958(Obj2_1E02C8* o);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00160C48(s32 v);
void func_001DDAD0(Glob_1E02C8* g);
void func_001AB890(Obj2_1E02C8* o, f32 v);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(Obj2_1E02C8* o, f32 v);
void func_001AB928(Obj2_1E02C8* o, f32 v, void* fn);
void func_001AB938(Obj2_1E02C8* o);
s32 func_001E1FD0(Buf_1E02C8* dst, const char* fmt, ...);
void func_001AA8B8(Obj_1E02C8* o, f32 v);
void func_0018C7F8(X_1E02C8* x);
s32 func_001602A0(void);
void func_001604B8(s32 m);
void func_00194D30(Y_1E02C8* y, s32 a, s32 b);
void func_00148CE0(Glob_1E02C8* g);

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
        Cam_1E02C8* cam = D_002623C8;
        if (cam->flags & 8) {
            f32 t = cam->f08;
            if (t < one) {
                func_001E1FD0(&D_00275900, "Best time: &10.%d", (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                func_001E1FD0(&D_00275900, "Best time: &1%d:%02d", s / 60, s % 60);
            }
            func_001AA8B8(self, zero);
            self->vt->m20(self, &D_00275900);
        } else {
            func_001AA8B8(self, 5.0f);
            self->vt->m20(self, (void*)"Beginning Master Thief Sprint!");
        }
        self->vt->m38(self);
        self->f260 = n;
        break;
    }
    case 3: {
        Obj2_1E02C8* o = &D_0026E760;
        s32 id;
        f32 t = o->f268;
        if (0.0f < t) {
            Cam_1E02C8* cam = D_002623C8;
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
        self->f260 = n;
        break;
    }
    default:
        self->f260 = n;
        break;
    }
    self->f264 = *self->f258;
    if (n == 2) {
        func_00148CE0(D_00275710);
    }
    self->f268 = (self->f260 != 0);
}
