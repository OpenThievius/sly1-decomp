// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the fields of self are at 0x56C, 0x570, 0x58C and 0x590 (US 0x25C, 0x260, 0x27C, 0x280).
struct Obj_1F1C90_eu {
    VFn_1F1C90* vtbl;
    u8 pad0[0x56C - 4];
    s32 f56C;
    Sub_1F1C90* f570;
    u8 pad1[0x58C - 0x574];
    f32 f58C;
    f32 f590;
};

void func_001AA060(void* self);
s32 func_001F0468(void);
s32 func_001F0490(void* o, s32 n, s32* a, s32* b);
void func_001F1590(void* self, s32 a1, s32 a2);
void func_001F1610(void* self);
void func_001AA8B0(void* self, f32 v);
void func_001AA8C0(void* self, f32 v);
void func_001BED48(void);
void func_001BED70(void);
void func_0016E0F0(s32 bits);
void func_0016E118(s32 n);
void func_0016EC88(void* p);
void func_001E96F8(void* obj, s32 mode);

void func_001F1C90(Obj_1F1C90_eu* self, s32 a1)
{
    if ((a1 != 0) != (self->f56C == 0)) return;
    if (a1 != 0) {
        func_001AA060(self);
        s32 r = func_001F0468();
        if (r == 10) {
            r = (func_001F0490(self->f570, 1, 0, 0) != 0);
        }
        func_001F1590(self->f570, r, 2);
        self->f590 = 1.0f;
        self->f58C = 1.0f;
        Anim_1F1C90* an = self->f570->f2E4;
        if (an != 0) {
            func_001AA8B0(self, an->f34);
        }
        Glob_1F1C90* g = (Glob_1F1C90*)D_002623C0;
        if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
            func_001BED48();
        }
        self->vtbl[14](self);
        func_0016E0F0(1);
        func_0016EC88(D_00262C70);
        func_001E96F8(D_00275BC0, 7);
    } else {
        self->vtbl[15](self);
        if (self->f570->f560 == 0) {
            func_001F1610(self->f570);
            Anim_1F1C90* an = self->f570->f2E8;
            if (an != 0) {
                func_001AA8C0(self, an->f34);
            }
            func_0016E118(1);
            func_001E96F8(D_00275BC0, 3);
            Glob_1F1C90* g = (Glob_1F1C90*)D_002623C0;
            if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
                func_001BED70();
            }
        }
    }
    self->f56C = a1;
}
