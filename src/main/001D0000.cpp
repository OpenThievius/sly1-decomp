// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "on_off_object.h"
#include "game_clock.h"

void func_001861E8(void* a, s32 b);


void func_001D1200(Player* self, s32 n)
{
    if (n == self->f2684) {
        return;
    }
    self->f2684 = n;
    self->f2688 = g_gameClock.time;
    self->f26A0 = 0;
    if (n <= 0) {
        return;
    }
    if (n >= 3) {
        if (n == 3) {
            self->f268C = 1;
        }
        return;
    }
    {
        s32 v = self->f2674;
        if (v == (s32)self->f2678) {
            self->f268C = 2;
        } else {
            self->f268C = 0;
        }
    }
}

struct __attribute__((aligned(16))) Blob_274E60_1D1260 { f32 f[36]; };


extern Blob_274E60_1D1260 D_00274E60;

void func_001E2840(OnOffObject* o, s32 v);

void func_001D1260(Player* self)

{
    OnOffObject* o = self->f2678;
    o->i414 = 5;
    o->f2D4 = 0;
    o->f2DC = 0;
    o->obj = 0;
    o->block2F0 = *(Block63*)&D_00274E60;
    o->f418 = 1;
    o->f388 = 3;
    o->f380 = 0;
    o->f384 = 0;
    o->f41C = 0;
    o->f390 = 0;
    o->f3A0 = 0;
    SetOnOffObjectForcedState(o, 0);
}

struct Obj_1D1478 { u8 pad[0x50]; s32 f50; };
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
s32 func_001D1478(Player* self)
{
    void* arr[64];
    s32 n = GatherObjectsById(self->world, 5, 0x89, 0, 0x40, arr);
    for (s32 i = 0; i < n; i++) {
        Obj_1D1478* o = (Obj_1D1478*)arr[i];
        s32 v = o->f50;
        if (v < 3) {
            if (v > 0) {
                return 0;
            }
        }
    }
    return 1;
}

f32 func_001FD578(u64 v);

s32 func_001D3C68(s32 stride, s32 n, s32 m, char* out, ...) {
    f32 rows[16];
    f32 cols[16];
    u64* ap = (u64*)((char*)__builtin_next_arg(out) - 32);
    f32 sum = 0.0f;
    s32 i;
    s32 j;
    s32 changed;
    for (i = 1; i < n; i++) {
        ap++;
        rows[i] = func_001FD578(ap[-1]);
        sum += rows[i];
    }
    rows[0] = 1.0f - sum;
    sum = 0.0f;
    for (j = 1; j < m; j++) {
        ap++;
        cols[j] = func_001FD578(ap[-1]);
        sum += cols[j];
    }
    cols[0] = 1.0f - sum;
    char* p = out;
    changed = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            sum = rows[i] * cols[j];
            if (sum != *(f32*)p) {
                *(f32*)p = sum;
                changed = 1;
            }
            p += stride;
        }
    }
    return changed;
}

Blob_274E60_1D1260 D_00274E60 = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -225.0f, 1.0f, 0.0f, 0.0f, 20.0f, 1.0f, 0.0f, 0.0f,
      -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f,
      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }
};
