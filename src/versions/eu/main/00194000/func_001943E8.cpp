// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: self/hud fields 0x310 further on, camera clamps 438..874 and 15..129 at PAL-only floats, per-language text ids (157..161) through func_eu_001DDAB0, and a text-scan in menu 20
struct Self_1943E8_eu {
    u8 pad0[0x560];
    s32 f560;
    f32 f564;
    u8 pad568[0x570 - 0x568];
    s32 f570;
    s32 f574;
    u8 pad578[0x584 - 0x578];
    s32 f584;
    u8 pad588[0x58C - 0x588];
    s32 f58C;
    u8 pad590[0x598 - 0x590];
    s32 f598;
};
struct Hud_1943E8_eu {
    void** vt;
    u8 pad4[0x574 - 0x4];
    s32* f574;
    u8 pad578[0x58C - 0x578];
    s32 f58C;
};
void func_00194D30(Self_1943E8_eu* self, s32 a, s32 b);
void func_00195958(Self_1943E8_eu* self);
void func_001961C0(Self_1943E8_eu* self);
extern f32 D_eu_0026BB30;
extern f32 D_eu_0026BB34;
extern u8 D_eu_00263550[];
extern u16 D_eu_00263558[];
const char* func_eu_001DDAB0(s32 id);
#define HUD_EU ((Hud_1943E8_eu*)&D_00274118)
void func_001943E8(Self_1943E8_eu* self)
{
    Glob_1943E8* g = (*(Glob_1943E8**)&D_002623C0);
    Row_1943E8* row = &((Row_1943E8*)&D_00269D50)[self->f570];
    s32 on;
    s32 n;
    Pad_1943E8* pad;

    on = 0;
    switch ((g->f19D8 << 8) | g->f19DC) {
    case 0x106:
    case 0x204:
    case 0x304:
    case 0x307:
    case 0x407:
    case 0x502:
    case 0x504:
        break;
    default:
        on = self->f570 == 0;
        break;
    }
    if (on) {
        ((VFn_1943E8)D_0026C6C8.vt[14])(&D_0026C6C8);
        ((VFn_1943E8)D_0026C948.vt[14])(&D_0026C948);
        ((VFn_1943E8)D_0026CBC8.vt[14])(&D_0026CBC8);
        ((VFn_1943E8)D_0026CE48.vt[14])(&D_0026CE48);
    } else {
        ((VFn_1943E8)D_0026C6C8.vt[15])(&D_0026C6C8);
        ((VFn_1943E8)D_0026C948.vt[15])(&D_0026C948);
        ((VFn_1943E8)D_0026CBC8.vt[15])(&D_0026CBC8);
        ((VFn_1943E8)D_0026CE48.vt[15])(&D_0026CE48);
    }
    switch (self->f570) {
    case 0:
    case 11:
    case 17:
        HUD_EU->f58C = func_00160B28((*(Glob_1943E8**)&D_002623C0));
        HUD_EU->f574 = &HUD_EU->f58C;
        ((VFn_1943E8)HUD_EU->vt[14])(HUD_EU);
        break;
    default:
        ((VFn_1943E8)HUD_EU->vt[15])(HUD_EU);
        break;
    }
    if (self->f598 != 0) {
        if (func_001BE810() != 0) {
            func_0011CE30();
        }
        self->f598 = func_001BE980();
    }
    s32 ready = 1;
    if (self->f584 != 0 || self->f560 != 2 || !(0.1f < D_00261868 - self->f564)) {
        ready = 0;
    }
    pad = &D_00262C70;
    if (row->f10 == 0) {
        n = 0;
    } else if (row->fC != 0) {
        n = func_0016EED0(pad);
    } else {
        n = func_0016EC98(pad);
    }
    if (n > 0) {
        self->f574 = (self->f574 + 1) % row->f10;
        func_001BFCD8(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (n < 0) {
        self->f574 = (self->f574 + row->f10 - 1) % row->f10;
        func_001BFCD8(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (!ready) {
        return;
    }
    if (pad->fAA & 0x810) {
        func_0016EC20(&D_00262C70, 0x810);
        func_001961C0(self);
        return;
    }
    if (pad->fAA & 0x80) {
        func_0016EC20(&D_00262C70, 0x80);
        if (self->f570 == 11 || self->f570 == 16) {
            Ent_1943E8* e = &((Ent_1943E8*)&D_eu_00255538)[row->items[self->f574]];
            if (e->fC != 0.0f) {
                D_0026998C = e;
                func_00194D30(self, 1, 0x12);
            }
        }
        return;
    }
    if (pad->fAA & 0x40) {
        func_0016EC20(&D_00262C70, 0x40);
        func_00195958(self);
        return;
    }
    switch (self->f570) {
    case 24: {
        f32 a = func_0016F108(pad, 0);
        f32 dx = a - func_0016F108(pad, 1);
        f32 b = func_0016F108(pad, 3);
        f32 dy = b - func_0016F108(pad, 2);
        f32 v;
        if (dx == 0.0f && dy == 0.0f) {
            return;
        }
        D_eu_0026BB30 = Clamp_1943E8::Of(D_eu_0026BB30 + dx * D_0026A22C, 438.0f, 874.0f);
        v = Clamp_1943E8::Of(D_eu_0026BB34 + dy * D_0026A230, 15.0f, 129.0f);
        D_eu_0026BB34 = v;
        {
            Gs_1943E8* gs = ((Gs_1943E8*)&D_00262490);
            s32 h = func_001FD7A0(D_eu_0026BB30);
            Reg_1943E8 ra = gs->f40;
            RegA_1943E8 rb = gs->f18;
            ra.lo = h;
            rb.lo = h;
            gs->f40 = ra;
            gs->f18 = rb;
            s32 w = func_001FD7A0(v);
            ra.mid = w & ~1;
            rb.mid = w & 0x7FE;
            gs->f40 = ra;
            gs->f18 = rb;
        }
        break;
    }
    case 11:
    case 16:
    case 17:
        if (D_00264A58 != 1) {
            func_001961C0(self);
            return;
        } else {
            s32 id = row->items[self->f574];
            if ((u32)(id - 10) < 3) {
                Ent_1943E8* e = &((Ent_1943E8*)&D_eu_00255538)[id];
                if (self->f570 == 16) {
                    if (e->fC != 0.0f) { ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, func_eu_001DDAB0(157)); } else { ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, func_eu_001DDAB0(158)); }
                } else if (self->f570 == 17) {
                    if (e->fC != 0.0f) { ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, func_eu_001DDAB0(159)); } else { ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, func_eu_001DDAB0(158)); }
                } else {
                    if (e->fC != 0.0f) { ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, func_eu_001DDAB0(160)); } else { ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, func_eu_001DDAB0(161)); }
                }
                ((VFn_1943E8)D_0026EC70.vt[14])(&D_0026EC70);
            } else {
                ((VFn_1943E8)D_0026EC70.vt[15])(&D_0026EC70);
            }
        }
        break;
    case 18:
        if (D_00264A58 != 1) {
            func_001961C0(self);
        }
        break;
    case 20: {
        u16* p;
        s32 found;
        if (D_00264A58 != 1) {
            func_001961C0(self);
        }
        found = 0;
        p = (u16*)func_eu_001DDAB0((s32)row->f0);
        for (;;) {
            u16 c = p[0];
            u16 d;
            if (c == 0) {
                break;
            }
            d = p[1];
            if (d == 0) {
                break;
            }
            if (c == 38 && (d == D_eu_00263558[1] || d == D_eu_00263550[1])) {
                found = 1;
                break;
            }
            p++;
        }
        if (found) {
            p[2] = func_001AEA08();
        }
        break;
    }
    case 3:
    case 4:
    case 7:
    case 10:
    case 32:
        if (D_00264A4C == 5) {
            func_00194D30((Self_1943E8_eu*)D_0026FF68, 1, -1);
        }
        break;
    case 5: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_0018B670(p, (void*)(void (*)(Boot_195958*))func_0018C250, ((u8*)&D_00264A40));
                func_00194D30(self, 1, 8);
            } else {
                func_00194D30(self, 1, 6);
            }
        }
        break;
    }
    case 8: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
            } else {
                func_00194D30(self, 1, 9);
            }
        }
        break;
    }
    case 12: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
                if (self->f58C == 2) {
                    func_00194398();
                }
            } else {
                func_00194D30(self, 0, 0x17);
                func_00194D30(self, 1, 0xF);
            }
        }
        break;
    }
    case 19: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            D_0026998C = 0;
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
            } else {
                func_00194D30(self, 0, 0x17);
                func_00194D30(self, 1, 0xF);
            }
        }
        break;
    }
    }
}
