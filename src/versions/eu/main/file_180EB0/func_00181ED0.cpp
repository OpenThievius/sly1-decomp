// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the aim's fields at 0x570 to 0x590 (US 0x260 to 0x280; PAL's ScreenElement is 0x310
// bytes longer).

// D_00270650 as PAL lays it out, for the aim's fields.
struct T217D_BF0Eu {
    u8 pad000[0x570];
    f32 rateX;                  // 0x570
    f32 rateY;                  // 0x574
    u8 pad578[0x580 - 0x578];
    f32 aim[4];                 // 0x580
    void* target;               // 0x590
};

void func_00181ED0(T217D_BF0* element, PadStick* pad)
{
    T217D_BF0Eu* self = (T217D_BF0Eu*)element;
    Vec02 p;
    Vec02 best;
    f32 bestScore = 3.40282347e+38f;
    Vu0::Q(best) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    Class75Object* chosen = 0;
    for (Class75Object* o = *(Class75Object**)g_class75List; o != 0; o = *(Class75Object**)&o->link) {
        GetObjectWorldPosition(o, &p);
        ProjectPointToCamera(g_camera, &p, &p);
        if (p.z < 100.0f) {
            continue;
        }
        f32 r = o->scale / (p.z * *(f32*)((u8*)g_camera + 0x1F0));
        u128 d = Vu0::Sub(Vu0::Q(p), Vu0::Q(self->aim));
        f32 eps = 0.0001f;
        f32 score = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d))) - r;
        score = eps >? score;
        if (o == self->target) {
            score *= 0.5f;
        }
        if (score < bestScore || (score == bestScore && p.z < best.z)) {
            Vu0::Q(best) = Vu0::Q(p);
            bestScore = score;
            chosen = o;
        }
    }
    self->rateX = ApproachValueWithRamp(self->rateX, pad->x, g_gameClock[2], D_00264198, 0);
    f32 y = pad->y;
    if (g_saveData->f19EC & 0x400) {
        y = -y;
    }
    self->rateY = ApproachValueWithRamp(self->rateY, y, g_gameClock[2], D_00264198, 0);
    self->aim[0] = ClampHelper::Of(self->aim[0] + g_gameClock[2] * self->rateX * D_002641A4, -1.0f, 1.0f);
    self->aim[1] = ClampHelper::Of(self->aim[1] - g_gameClock[2] * self->rateY * D_002641A4, -1.0f, 1.0f);
    f32 far = 1000.0f;
    self->aim[2] = ApproachValueWithRamp(self->aim[2], far >? best.z, g_gameClock[2], D_002641A8, 0);
    self->target = chosen;
}
