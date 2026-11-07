// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with func_eu_001F7738, a function only PAL has, where US calls func_00201720
void func_eu_001F7738(u8* dst, const char* src, s32 max);

s32 func_00209E48(s32 a0, s32 a1, const char* name, s32 a3, s32 a4, s32 a5)
{
    s32 status = func_001F6B70((Lock_9E48*)D_0027AECC);
    if (status < 0) {
        return -200;
    }
    Mgr_9E48* mgr = (Mgr_9E48*)D_0062AD40;
    if (*(s32*)(D_0062AD40 + 0x24) == 0) {
        func_001F6B40((Lock_9E48*)D_0027AECC);
        return -100;
    }
    if (name == 0 || *name == 0) {
        func_001F6B40((Lock_9E48*)D_0027AECC);
        return -210;
    }
    Rec_9E48* rec = (Rec_9E48*)D_0062ADF0;
    rec->f0 = a0;
    rec->f4 = a1;
    rec->f8 = a3;
    rec->fC = a4;
    rec->f10 = a5;
    func_eu_001F7738((u8*)rec + 0x14, name, 0x3FF);
    ((u8*)rec)[0x413] = 0;
    if (a4 >= 0) {
        func_001FA7D8(a5, a4 << 6);
    }
    s32 r = func_001F8290(mgr, 0xD, 1, rec, 0x414, D_0062C300, 4, 0, 0);
    if (r == 0) {
        D_0027AEC8 = 0xD;
    } else {
        func_001F6B40((Lock_9E48*)D_0027AECC);
    }
    return r;
}
