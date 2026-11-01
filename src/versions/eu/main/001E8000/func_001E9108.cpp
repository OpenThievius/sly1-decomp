// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: calls func_0018C178(g, 1) before func_0018C568 and handles a third button (0x10) when D_eu_002636EC >= 2
extern s32 D_eu_002636EC;
struct G2_1E9108_eu { u8 pad[0x570]; Sub_1E9108* f570; };
extern void func_001E9498(Obj_1E9108* o, G2_1E9108_eu* g);
extern void func_0018C178(Glob_1E9108* g, s32 a);

void func_001E9108(Obj_1E9108* obj)
{
    f32 d = D_00261858[4] - obj->f8;
    s32 s1 = obj->state;
    In_1E9108* s2;
    s32 s5;
    if (D_00262C68 & 4) {
        s2 = (In_1E9108*)D_00262C70;
    } else {
        s2 = &D_00262D38;
    }
    s5 = 0;
    if (D_00262C6C & 0x80) {
        if (0.1f < D_00261858[1]) {
            func_0016E118(0x80);
        }
    }
    switch (obj->state) {
    case 0: {
        s32 a2 = 0;
        if (D_002701B8 == 0) {
            s32 m = ((Glob_1E9108*)(Glob_1E9108*)&D_00264A40)->f18;
            if (m == 2 || (m == 1 && ((Glob_1E9108*)(Glob_1E9108*)&D_00264A40)->fC == 5)) {
                a2 = 1;
            }
        }
        if (a2) {
            func_001F4808(func_001F4378());
        }
        break;
    }
    case 1: {
        u32 v = s2->bits;
        if (v & 0x800) {
            s32 t;
            func_0016EC20(s2, 0x800);
            t = ((Glob_1E9108*)(Glob_1E9108*)&D_00264A40)->f4F48;
            ((Glob_1E9108*)(Glob_1E9108*)&D_00264A40)->f4F44 = t;
            if (t) {
                func_0018C178((Glob_1E9108*)&D_00264A40, 1);
                func_0018C568((Glob_1E9108*)&D_00264A40);
            } else {
                func_001605E8(D_002623C0);
            }
            func_00160948();
            s1 = obj->state;
        } else if (v & 0x100) {
            func_0016EC20(s2, 0x100);
            func_00194D30(D_0026FF68, 0, 0x17);
            s1 = obj->state;
        } else if (D_eu_002636EC >= 2 && (v & 0x10)) {
            func_0016EC20(s2, 0x10);
            func_00194D30(D_0026FF68, 0, 0x21);
            s1 = obj->state;
        }
        break;
    }
    case 3: {
        if (D_00262C6C & 2) break;
        if (D_00275F84) break;
        {
            u32 v = s2->bits;
            if ((v & 0x800) || (s2->f14 == 1 && 5.0f <= D_00261858[1])) {
                func_00194D30(D_0026FF68, 0, 0);
                s1 = obj->state;
                func_0016EC20(s2, 0x800);
            } else if ((v = s2->bits) & 0x100) {
                G2_1E9108_eu* g2 = (G2_1E9108_eu*)D_0026F808;
                Sub_1E9108* x = g2->f570;
                if (x == 0) break;
                if (x->f2D0) break;
                func_001E9498(obj, g2);
                s1 = obj->state;
                func_0016EC20(s2, 0x100);
            }
        }
        break;
    }
    case 4:
        if (d <= 0.2f) {
            func_001E98E8(obj, (0.2f - d) * 5.0f);
        } else {
            s1 = 5;
        }
        break;
    case 6:
        if (d <= 0.5f) {
            func_001E98E8(obj, d + d);
        } else {
            s1 = 3;
        }
        break;
    case 2:
    case 5:
    case 7:
        s5 = 1;
        break;
    case 8:
    default:
        break;
    }
    func_001E96F8(obj, s1);
    {
        Elem_1E9108* e = obj->stack[obj->count - 1];
        if (e) {
            if (e->vt->fn) {
                e->vt->fn(e, s2);
            }
        } else if (s5) {
            func_001E96F8(obj, 3);
        }
    }
    func_001409E0();
    func_001A9FD0();
}
