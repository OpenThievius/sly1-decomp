// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL adds a check after the switch: for 0 or 12, a state other than 2 forces 11 and f14 = 1.
s32 func_0018D0A0(Obj_18D0A0* o)
{
    s32 r = func_0018BD00(func_00209CB8(o->p4, o->p8, &o->f24, &o->f28, &o->f2C), 1, 0);
    switch (r) {
    case 9:
    case 11:
        o->f14 = 1;
        r = 11;
        break;
    case 10:
    case 12:
        o->f14 = 2;
        r = 12;
        break;
    case 0:
        if (o->f2C != 0) {
            if (o->f14 < 3)
                o->f14 = 3;
            else
                break;
        } else
            o->f14 = 2;
        break;
    }
    if ((r == 0 || r == 12) && o->f24 != 2) {
        o->f14 = 1;
        r = 11;
    }
    o->f20 = D_00261868[0] + 0.3f;
    return r;
}
