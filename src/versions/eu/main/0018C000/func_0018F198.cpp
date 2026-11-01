// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: same flow with a stop flag after the device test
void func_0018F198(Self_18F198* self, Key_18F198* key)
{
    Loc_18F198 loc;
    Pair_18F198 pr;
    func_00191E70(4);
    self->mode = func_0018E410(key);
    func_0012FCF0(&loc, D_002C3B00);
    if (pr.Set(key) && func_0012FD78(&loc, &pr)) {
        func_0018F448(self, &loc);
        while (!func_0020B0B0(self->list)) {
            func_00143030(((u8*)D_00261858));
            func_0016E238(&D_00262C70);
            s32 flag = 0;
            if (key->Same(&D_00248490)) flag = D_00269B4C != 0;
            u32 m;
            if (self->mode >= 16) m = 0;
            else m = 1u << self->mode;
            if ((*(Tbl_18F198**)&D_002623C0)->mask & m) flag = 1;
            if (flag) {
                s32 stop = 0;
                if (func_001F00F0(D_00275F80, &D_00262C70, 2)) {
                    stop = 1;
                } else if (D_00262C70.bits & 0x91F) {
                    func_0016EC20(&D_00262C70, 0x91F);
                    stop = 1;
                }
                if (stop) break;
            }
            func_001409E0();
            if (D_002613EC != 3) break;
            func_0018F6E8(self);
        }
        if (key->Same(&D_00248490)) D_00269B4C = 1;
        func_0018F7D0(self);
        func_0012FDE8(&loc);
    } else {
        func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    func_00191EB0(4);
    func_0012FD30(&loc, 2);
}
