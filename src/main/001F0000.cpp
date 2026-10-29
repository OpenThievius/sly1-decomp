// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1F0468 { u8 pad[0x19DC]; s32 value; };

extern s32 D_00275BF0;
extern void* D_002623C0;

s32 func_001F0468(void)
{
    if (D_00275BF0 != 2) {
        return ((Obj_1F0468*)D_002623C0)->value;
    }
    return 10;
}

struct Cam_1F0EB8 { u8 pad[0x1C4]; f32 a; f32 b; };

extern Cam_1F0EB8* D_00261990;

void func_00143940(void* p, f32 v);
void func_00125B70(void* obj, void* c, void* out);
void func_00188B08(void* a, void* b, void* out);
void func_00125C90(void* obj, void* s, void* out);

void func_001F0EB8(void* obj, u8* s, void* c)
{
    u8 tmp[0x50];
    Cam_1F0EB8* p = D_00261990;
    f32 keep1 = p->a;
    f32 keep2 = p->b;
    func_00143940(p, 1.0f);
    func_00125B70(obj, c, tmp);
    func_00188B08(s + 0x40, s + 0x80, tmp);
    func_00125C90(obj, s, tmp);
    func_00143940(D_00261990, keep1);
    D_00261990->b = keep2;
}

struct Entry_1F3358 { f32 w; f32 x; f32 y; f32 z; };
struct Blob_1F3358 { f32 lo; f32 hi; f32 scale; s32 count; Entry_1F3358 items[1]; };

f32 func_001F3250(f32 a, f32 b, f32 c);
f32 func_001F3328(f32 a, f32 b);

f32 func_001F3358(Blob_1F3358* obj)
{
    f32 num = 0.0f;
    f32 den = 0.0f;
    for (s32 i = 0; i < obj->count; i++) {
        Entry_1F3358* e = &obj->items[i];
        f32 r = func_001F3250(e->x, e->y, e->z);
        num += e->w * r;
        den += e->w;
    }
    f32 t = func_001F3328(num / den, obj->scale);
    return obj->lo + t * (obj->hi - obj->lo);
}

struct Vec4_1F38F0 { f32 a; f32 b; f32 c; f32 d; };
struct Buf_1F38F0 { u8 pad[0xC]; u32 count; Vec4_1F38F0 items[4]; };

void func_001F38F0(Buf_1F38F0* buf, f32 x, f32 y, f32 z, f32 w)
{
    u32 n = buf->count;
    if (n < 4) {
        Vec4_1F38F0* e = &buf->items[n];
        buf->count = n + 1;
        e->a = x;
        e->b = y;
        e->c = z;
        e->d = w;
    }
}

void* func_001F37D8(void* self, s32 mode, s32 flag);

void* func_001F3830(void* self, s32 mode)
{
    return func_001F37D8(self, mode, 1);
}

struct Scaler_001F3850 { u8 pad[0x64]; f32 scale; };

void* func_001F3810(void* self, s32 mode);

void func_001F3850(void* self, f32 x)
{
    Scaler_001F3850* s = (Scaler_001F3850*)func_001F3810(self, 1);
    if (x == 0.0f) s->scale = 0.0f;
    else s->scale = 1.0f / x;
}

struct Scaler_001F38A0 { u8 pad[0x64]; f32 scale; };

void* func_001F3810(void* self, s32 mode);

void func_001F38A0(void* self, f32* out)
{
    Scaler_001F38A0* s = (Scaler_001F38A0*)func_001F3810(self, 1);
    f32 v = s->scale;
    if (v == 0.0f) *out = 0.0f;
    else *out = 1.0f / v;
}

void* func_001F3830(void* self, s32 mode);
void func_001F38F0(void* buf, f32 a, f32 b, f32 c, f32 d);

void func_001F3928(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)func_001F3830(self, 1);
    func_001F38F0(p + 0x30, a, b, c, d);
}
