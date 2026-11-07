// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields 0x310 further on, the text goes to a local buffer handed to func_eu_001AB370
struct Self_1AB2B8_eu {
    u8 pad0[0x524];
    s32 f524;
    u8 pad528[0x570 - 0x528];
    s32 f570;
    u8 pad574[4];
    s32* f578;
};
void func_eu_001AB370(Self_1AB2B8_eu* self, char* buf);

void func_001AB2B8(Self_1AB2B8_eu* self)
{
    char buf[0x200];
    switch (self->f524) {
    case 3:
        FormatToStringBounded(buf, 0x200, "%c%d", 0x4C, self->f570);
        break;
    case 4:
        if (*self->f578 != 0) {
            FormatToStringBounded(buf, 0x200, "%d/%d%c", self->f570, *self->f578,
                          self->f570 < *self->f578 ? 0x3F : 0x21);
        } else {
            buf[0] = 0;
        }
        break;
    case 5:
        if ((u32)(g_saveData->f19D8 - 1) < 4) {
            FormatToStringBounded(buf, 0x200, "%d%c", self->f570, 0x4B);
        } else {
            buf[0] = 0;
        }
        break;
    case 6:
        if (g_currentWorld->f2354 != 0) {
            FormatToStringBounded(buf, 0x200, "%c%d", 0x43, self->f570);
        } else {
            buf[0] = 0;
        }
        break;
    case 7:
        FormatToStringBounded(buf, 0x200, "%d/%d%c", self->f570, *self->f578, 0x56);
        break;
    case 8:
        FormatToStringBounded(buf, 0x200, "%d/%d%c", self->f570, *self->f578, 0x4E);
        break;
    case 9:
        FormatToStringBounded(buf, 0x200, "%c%d/%d", 0x46, self->f570, *self->f578);
        break;
    case 10:
        FormatToStringBounded(buf, 0x200, "%c%d", 0x4E, self->f570);
        break;
    case 11:
        FormatToStringBounded(buf, 0x200, "%d/%d%c", self->f570, *self->f578, 0x56);
        break;
    case 28:
        FormatToStringBounded(buf, 0x200, "%d/%d%c", self->f570, D_002751D4, 0x56);
        break;
    case 29:
        FormatToStringBounded(buf, 0x200, "%c%d/%d", 0x4E, self->f570, D_002751D4);
        break;
    case 12:
        FormatToStringBounded(buf, 0x200, "%d/%d%c", self->f570, *self->f578, 0x64);
        break;
    case 13:
        FormatToStringBounded(buf, 0x200, "%c%c%c%c%c%c", 's',
                      self->f570 >= 1 ? 'b' : 'm', self->f570 >= 2 ? 'b' : 'm',
                      self->f570 >= 3 ? 'b' : 'm', self->f570 >= 4 ? 'b' : 'm',
                      self->f570 >= 5 ? 'b' : 'm');
        break;
    case 14:
        FormatToStringBounded(buf, 0x200, "rstuv");
        break;
    case 15:
        FormatToStringBounded(buf, 0x200, "%c%d/5", 0x46, self->f570);
        break;
    case 36:
        FormatToStringBounded(buf, 0x200, "%d%%", self->f570);
        break;
    }
    func_eu_001AB370(self, buf);
}
