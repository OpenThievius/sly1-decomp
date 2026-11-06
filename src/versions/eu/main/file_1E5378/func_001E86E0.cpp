// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields at 0x578/0x580 and the manager state at 0x570; calls PAL's func_eu_001AB238 where US calls vtable slot 8.
void func_001E7460(void* self);
void func_001E7440(void* self, s32 v);
void func_001E87F0(void* self, void* a1);
void func_001E7518(void* self, s32 mode);
struct Obj_1E86E0_eu {
    u8 pad0[0x578];
    s32 f578;
    u8 pad1[4];
    s32 f580;
};

struct Mgr_1E86E0_eu {
    void** vtbl;
    u8 pad[0x570 - 4];
    s32 f570;
};

void func_eu_001AB238(void* self, s32 v);

void func_001E86E0(Obj_1E86E0_eu* self, s32 value)
{
    if (value == self->f580) return;
    if (self->f580 == 0) {
        func_eu_001AB238(&g_typedTextCaptionBox, 0);
    }
    self->f580 = value;
    if (((Mgr_1E86E0_eu*)&g_typedTextCaptionBox)->f570 == 4) {
        ApplyArcTarget(self);
        if (self->f580 != 0) {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 2);
            SetArcPhase(self, 1);
            SetArcFade(self, 0);
        } else {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 0);
            SetArcPhase(self, 3);
            SetArcFade(self, 0);
            SetArcSpecialObject(self, 0);
        }
    } else {
        s32 st = self->f578;
        if (st >= 2) return;
        if (st < 0) return;
        SetArcPhase(self, 2);
    }
}
