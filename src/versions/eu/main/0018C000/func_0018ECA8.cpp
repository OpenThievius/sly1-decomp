// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the read loop also handles status 1 (func_0018EB98 on the object at +0x80) and stops on status 2.

extern u8 D_eu_0024D878[];

s32 func_0018ECA8(void* u0, void* u1, Obj_18ECA8* self)
{
    Buf_18ECA8 buf;
    while (self->f74 < 0x1000) {
        s32 r = func_0018F890(self, 1);
        if (r == 2) {
            func_001F5C0C(&buf, 0, 0x40);
            s32 k = self->f74;
            func_0013CC00((Sub_18ECA8*)&self->sub, 0x40 - (k % 32), &buf);
            break;
        }
        if (r == 1) {
            func_0018EB98((Self_18EB98*)((u8*)self + 0x80));
        }
    }
    buf.f0 = (void*)D_eu_0024D878;
    func_0013CC48((Sub_18ECA8*)&self->sub, 0);
    func_0013CAD8((Sub_18ECA8*)&self->sub, 0, &buf);
    return 1;
}
