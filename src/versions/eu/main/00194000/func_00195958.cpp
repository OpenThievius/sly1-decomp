// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: menu fields 0x310 further on, menu 15 joins the closing group, a per-language title string, and two new menus (33, 34); the entry table sits at 0x255538, which the tools cannot pair with US's D_002542D8.
struct Menu_195958_eu {
    u8 pad0[0x570];
    s32 f260;
    s32 f264;
    s32 f268;
    u8 pad1[0x27C - 0x26C];
    s32 f27C;
    s32 f280;
};
struct Sub_195958_eu {
    u8 pad0[0x570];
    s32 f260;
};

extern u8 D_eu_00249050[][32];
extern s32 D_eu_00263710;
extern s32 D_eu_00263624;
extern Ent_195958 D_eu_00255538[];

void func_001961C0(Menu_195958_eu* self);
void func_00194D30(Menu_195958_eu* self, s32 a, s32 b);
void func_00194278(Menu_195958_eu* self, s32 a, s32 b);
void func_001936A0(Menu_195958_eu* self);
void func_001E9498(u8* a, Sub_195958_eu* b);
void func_eu_00160620(s32 a);
u8* func_eu_00160788(s32 a);

void func_00195958(Menu_195958_eu* self)
{
    s32 sel = D_00269D50[self->f260].items ? D_00269D50[self->f260].items[self->f264] : -1;
    if (sel == 0x11) {
        func_001961C0(self);
        return;
    }
    switch (self->f260) {
    case 0:
        switch (sel) {
        case 3:
            func_00194D30(self, 0, -1);
            return;
        case 4: {
            Sub_195958_eu* s = (Sub_195958_eu*)&D_0026F808;
            if (s->f260 != 0) {
                func_00194D30(self, 0, -1);
                func_001E9498(D_00275BC0, s);
                return;
            }
            func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            return;
        }
        case 18: {
            s32 v;
            void* s2 = func_00193660();
            void* s0 = func_001925F0();
            if (s2 != 0 && s0 != 0 && func_001300E8(s0, 0x19) != 0) {
                func_001B6598(s2, &v);
                if (v < 0x431) {
                    if (v >= 0x42F) {
                        func_001D9338(s0);
                        func_001B6628(s2, 0x42E);
                    }
                }
            }
            func_00194D30(self, 0, -1);
            return;
        }
        case 19:
        case 20:
            func_00194278(self, 1, 1);
            return;
        case 21:
            func_00194D30(self, 0, -1);
            func_001F4408(1, 2);
            return;
        case 22:
            func_00194D30(self, 0, -1);
            func_001F0428(D_eu_00249050[D_eu_00263710], -1, 2);
            return;
        case 9:
            func_00194D30(self, 0, 2);
            return;
        case 5:
            func_00194D30(self, 0, 0x17);
            return;
        case 23:
            func_00194D30(self, 0, 0x1F);
            return;
        }
        return;
    case 23:
        switch (sel) {
        case 6:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0x10);
            return;
        case 7:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0x11);
            return;
        case 8:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0xB);
            return;
        case 13:
            func_001A7F50(((Glob_195958*)D_002623C0));
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        case 15: {
            Glob_195958* g = ((Glob_195958*)D_002623C0);
            g->f19EC ^= 0x80;
            func_001C0760(g->f19EC & 0x80);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 16: {
            Glob_195958* g = ((Glob_195958*)D_002623C0);
            g->f19EC ^= 0x40;
            func_001C0790(g->f19EC & 0x40);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 14:
            func_00194D30(self, 0, 0x18);
            return;
        case 23:
            func_00194D30(self, 0, 0x1F);
            return;
        }
        return;
    case 27:
        if ((func_001602A0() & 8) != 0) {
            func_00160578(8);
            return;
        }
        func_00194278(self, 0, 2);
        return;
    case 1:
    case 26:
    case 28:
    case 29:
    case 30:
        func_00194278(self, (u32)sel < 1, 1);
        return;
    case 25: {
        s32 a = self->f280;
        self->f280 = 0;
        func_001B64D8(a, sel == 0 ? 0x434 : 0x435);
        func_00194D30(self, 0, -1);
        return;
    }
    case 2:
        if (sel == 0) {
            Boot_195958* b = &D_00264A40;
            if (b->f4F44 != 0) {
                self->f27C = 2;
                if ((((Glob_195958*)D_002623C0)->f19EC & 0x100) == 0) {
                    func_00194D30(self, 1, 0x14);
                } else {
                    func_00194D30(self, 1, 0xC);
                    func_0018B670(&D_00269990, (void*)func_0018C638, b);
                }
            } else {
                func_00194398();
            }
            func_00194D30(self, 0, -1);
            return;
        }
        func_00194D30(self, 0, -1);
        return;
    case 31:
        switch (sel) {
        case 0x18: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x200;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x19: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x400;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x1A: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x800;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        }
        return;
    case 33:
        func_00194D30(self, 0, -1);
        if (sel >= 0x22) {
            break;
        }
        if (sel < 0x1B) {
            return;
        }
        func_eu_00160620(sel - 0x1B);
        func_001F0428(func_eu_00160788(3), 0x1BE, 1);
        return;
    case 34:
        func_00194D30(self, 0, -1);
        D_eu_00263624 = 1;
        return;
    case 14:
        if (sel == 0) {
            goto c6030;
        }
        func_00194D30(self, 1, -1);
        return;
    case 4:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C1A8, &D_00264A40);
            func_00194D30(self, 1, 5);
            return;
        }
        goto c5EC0;
    case 7:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C250, &D_00264A40);
            func_00194D30(self, 1, 8);
            return;
        }
        goto c5EC0;
    case 3:
    case 6:
    case 9:
    case 10:
    case 15:
    case 21:
    case 32:
    c5EC0: {
        s32 v;
        func_00194D30(self, 1, -1);
        func_0018C178(&D_00264A40, 2);
        v = self->f268;
        if (v == 0xB) {
            goto c5F08;
        }
        if (v < 0xB) {
            return;
        }
        if (v >= 0x12) {
            return;
        }
        if (v < 0x10) {
            return;
        }
    }
    case 24:
    c5F08:
        func_00194D30(self, 0, 0x17);
        return;
    case 16: {
        Ent_195958* e = &D_eu_00255538[sel];
        if (e->fC == 0.0f) {
            func_00194D30(self, 0, -1);
            D_00264A40.f4F44 = e;
            func_0018C568(&D_00264A40);
            func_00160948();
            return;
        }
        func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    case 17:
        func_00194D30(self, 0, -1);
        D_00264A40.f4F44 = &D_eu_00255538[sel];
        func_0018C568(&D_00264A40);
        func_00160948();
        return;
    case 11: {
        Ent_195958* e;
        u32 p;
        p = sel * sizeof(Ent_195958);
        p += (u32)D_eu_00255538;
        e = (Ent_195958*)p;
        D_00264A40.f4F4C = e;
        if (e->fC == 0.0f) {
        c6030:
            Boot_195958* b;
            b = &D_00264A40;
            b->f4F44 = b->f4F4C;
            self->f27C = 0xB;
            if ((((Glob_195958*)D_002623C0)->f19EC & 0x100) == 0) {
                func_00194D30(self, 1, 0x14);
            } else {
                func_00194D30(self, 1, 0xC);
                func_0018B670(&D_00269990, (void*)func_0018C638, b);
            }
            func_00194D30(self, 0, -1);
            return;
        }
        func_00194D30(self, 1, 0xE);
        return;
    }
    case 18:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C770, &D_00264A40);
            func_00194D30(self, 1, 0x13);
            return;
        }
        func_00194D30(self, 1, -1);
        return;
    case 13:
        func_00194D30(self, 1, -1);
        return;
    case 20: {
        ((Glob_195958*)D_002623C0)->f19EC |= 0x100;
        s32 v = self->f27C;
        switch (v) {
        case 2:
        case 0xB:
            func_00194D30(self, 1, 0xC);
            break;
        case -1:
            func_00194D30(self, 1, -1);
            D_00273EB0.vt->f38(&D_00273EB0);
            break;
        }
        func_0018B670(&D_00269990, (void*)func_0018C638, &D_00264A40);
        return;
    }
    }
}
