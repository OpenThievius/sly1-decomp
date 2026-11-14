// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the object is laid out 0x310 further on: f250 at 0x560, f25C at 0x56C, f260 at 0x570, arr268 at 0x578, f274 and f278 at 0x584 and 0x588.
struct Self_194D30_eu {
    u8 pad0[0x560];
    s32 f560;
    u8 pad1[0x56C - 0x564];
    s32 f56C;
    s32 f570;
    u8 pad2[0x578 - 0x574];
    s32 arr578[3];
    s32 f584;
    s32 f588;
};

void SetPauseMenuLayerPage(Self_194D30_eu* self, s32 idx, s32 value)
{
    s32 s1;
    s32 s2;
    u32 i;
    s32* p;

    s2 = value;
    self->arr578[idx] = s2;
    p = self->arr578;
    for (i = 0; i < 3; i++) {
        if (*p != -1) {
            s2 = *p;
        }
        p++;
    }
    if (self->f584 != 0) {
        s1 = self->f588;
    } else {
        s1 = self->f570;
    }
    ChangePauseMenuPage(self, s1, s2);
    if (s1 != s2) {
        if (self->f560 == 0) {
            SetPauseMenuPage(self, s2);
        } else if (self->f560 >= 0) {
          if (self->f560 < 4) {
            if (s2 == -1) {
                self->f584 = 0;
                self->f588 = s2;
            } else {
                self->f588 = s2;
                self->f584 = 1;
                ((ScreenElement*)self)->vt->m16((ScreenElement*)self, 3);
            }
          }
        }
    }
    if (s2 == -1) {
        if (self->f56C != 0) {
            PopStackElement((ElementStack*)g_elementStack);
        }
    } else {
        if (self->f56C == 0) {
            PushStackElement((ElementStack*)g_elementStack, (ScreenElement*)self);
        }
    }
}
