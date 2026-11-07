// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 240/236, checked 2026-11-07
// NEAR: everything but the end: retail stores the dot product with qmfc2.ni v0 and sw v0,0x840(s0) (the word straight to memory); ToFloat gives mfc2, mtc1 and swc1 there. Needs ToBits (u128 -> u32).
// In the context of its file, src/main/file_1D62E0.cpp.
// From 0x1D62E0 to 0x1DDCE0: classes 0x07 and 0x3F, the output buffer, class 0x19, the world
// (class 0x6C) and its script functions. Its .data runs from 0x275140 to the zeroed globals
// D_00275710 (g_currentWorld) to D_00275728 that close it; its .rodata is the "%s" of
// func_001D72C8, the float of func_001D8470 and the pairs of func_001DCD28. One file between
// two edges with no evidence inside it: it could be several.
#include "common.h"
#include "vu0.h"
#include "globals.h"
#include "path_curve_object.h"

void FindPathFollowerPathPosition(PathFollower* self)
{
    if (self->f830 != 0) {
        Vec02 p;
        Vec02 tangent;
        Vec02 side;
        PathCurve* o = self->f830->curve;
        if (o->vt->m11) {
            o->vt->m11(o, *(f32*)((u8*)self + 0x838), (u8*)self + 0x100, 0, (f32*)&p, (f32*)&tangent, (f32*)((u8*)self + 0x838), 0);
        }
        u128 c = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
        Vu0::Q(side) = Vu0::DivX(c, Vu0::Length(c));
        self->f83C = self->f830->curve->vt->m05(self->f830->curve, *(f32*)((u8*)self + 0x838));
        self->f840 = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)self + 0x100)), Vu0::Q(p)), Vu0::Q(side)));
    }
}
