// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

f32 func_00205318(f32 x)
{
    s32 i0 = *(s32*)&x;
    s32 j0 = ((i0 >> 23) & 0xff) - 0x7f;
    s32 i;

    if (j0 < 0x17) {
        if (j0 < 0) {
            if (1.0e30f + x > 0.0f) {
                if (i0 >= 0) {
                    i0 = 0;
                } else if ((i0 & 0x7fffffff) != 0) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = 0x7fffff >> j0;
            if ((i0 & i) == 0) {
                return x;
            }
            if (1.0e30f + x > 0.0f) {
                if (i0 < 0) {
                    i0 += 0x800000 >> j0;
                }
                i0 &= ~i;
            }
        }
    } else {
        if (j0 == 0x80) {
            return x + x;
        }
        return x;
    }
    *(s32*)&x = i0;
    return x;
}

// NEAR: retail saves registers in 8 bytes (sd); retail puts the sb before the loop bnez and the state return tail differs.

struct Obj_204AA8;
struct Lock_204AA8;
struct Ctx_204AA8 { s32 kind; void* a; void* b; u8 bytes[6]; u8 pad1A[2]; s32 state; };

extern Ctx_204AA8 D_0062ACC0;
extern u8 D_0062AA80[];

s32 func_001F8290(Lock_204AA8* l, s32 a, s32 b, Ctx_204AA8* c, s32 d, Ctx_204AA8* e, s32 f, s32 g, s32 h);
void func_00204610(Obj_204AA8* o, void* q, s32 n);

s32 func_00204AA8(Obj_204AA8* p, void* q, u8* src)
{
    Ctx_204AA8* c = &D_0062ACC0;
    s32 i;

    c->kind = 8;
    c->a = p;
    c->b = q;
    i = 0;
    do {
        c->bytes[i] = src[i];
        i++;
    } while (i < 6);
    if (func_001F8290((Lock_204AA8*)D_0062AA80, 1, 0, c, 0x80, c, 0x80, 0, 0) < 0) return 0;
    if (c->state == 1) func_00204610(p, q, 2);
    return c->state;
}

struct Obj_204930 { u32 mode; u32 a; u32 b; u32 c; u32 d; u32 result; };

extern u8 D_0062AA80[];

s32 func_001F8290(u8* p0, s32 a1, s32 a2, Obj_204930* a3, s32 a4, Obj_204930* a5, s32 a6, s32 a7, s32 a8);
s32 func_00204610(Obj_204930* obj, s32 a1, s32 a2);

s32 func_00204930(s32 a0, s32 a1, s32 a2, s32 a3)
{
    Obj_204930* obj = (Obj_204930*)((u8*)&D_0062ACC0);
    s32 status;
    s32 r;

    obj->c = a2;
    obj->d = a3;
    obj->mode = 6;
    obj->a = a0;
    obj->b = a1;
    r = func_001F8290(D_0062AA80, 1, 0, obj, 0x80, obj, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    status = obj->result;
    if (status == 1) {
        (void)func_00204610((Obj_204930*)a0, a1, 2);
        status = obj->result;
    }
    return status;
}

struct Ctx_00204DB8 { s32 f00; u8 pad[8]; s32 f0C; };
struct Q_00204DB8;
extern u8 D_0062AA80[];
s32 func_001F8290(Q_00204DB8* q, s32 a, s32 b, Ctx_00204DB8* c, s32 d, Ctx_00204DB8* e, s32 f, s32 g, s32 h);

s32 func_00204DB8(void)
{
    Ctx_00204DB8* ctx = (Ctx_00204DB8*)((u8*)&D_0062ACC0);
    ctx->f00 = 0x12;
    s32 r = func_001F8290((Q_00204DB8*)D_0062AA80, 1, 0, ctx, 0x80, ctx, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    return ctx->f0C;
}
