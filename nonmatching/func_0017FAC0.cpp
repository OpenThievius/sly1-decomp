// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the status branches and retail's max.s instruction still differ.
#include "common.h"

struct Obj_17FAC0 { u8 pad[0x358]; f32 radius; };
struct Point_17FAC0 { u8 pad[8]; f32 coordinate; };
s32 func_001EACA0(f32* range, f32 radius, f32 dy, f32 dx);

s32 func_0017FAC0(Obj_17FAC0* self, Point_17FAC0* p1, Point_17FAC0* p2,
                  Point_17FAC0* p3, Point_17FAC0* p4, f32* output)
{
    f32 half = self->radius * 0.5f;
    f32 dy = p2->coordinate - p4->coordinate;
    f32 dx = p1->coordinate - p3->coordinate;
    f32 range[2];
    s32 result = func_001EACA0(range, half, dy, dx);
    if (result == 1) goto check_value;
    if (result < 2) return 0;
    if (result == 2) range[0] = range[0] < range[1] ? range[1] : range[0];
check_value:
    if (range[0] <= 0.0f) return 0;
    *output = range[0];
    return 1;
}
