// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's reset of the game state when the flag is set.
void func_001DB838(s32 a0)
{
    if (a0 != 0) {
        func_00192880(-1);
        D_00269C90 = 0;
        D_00262E10 = 0;
        D_00262C6C = 0;
        func_0016E148();
        func_00143AF0(D_00261990);
        func_001DFD70();
        func_0017FD70();
        func_00191EE8();
        func_00169CA0();
        func_001C07B0();
        func_001B40C8();
        func_0011C040();
        func_001E9688(D_00275BC0);
        func_0018D550();
        u8* c = D_0026CE48;
        u8* e = D_0026E760;
        D_00261990 = 0;
        D_002640A4 = 0;
        D_00261854 = 1.0f;
        ((Word_1DB838*)(c + 0x584))->v = 0;
        ((Word_1DB838*)(e + 0x590))->v = 0;
        D_00261D38 = 0;
        *(s32*)(c + 0x588) = 0;
        *(s32*)(e + 0x59C) = 0;
    }
}
