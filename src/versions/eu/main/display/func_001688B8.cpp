// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: func_00201A18 is called with 3 (US 2) and func_00201D60 with 0x100 (US 0xE0).

void InitDisplay(void)
{
    Rgba4 k;
    Rgba4 t;

    ResetGs(0, 1, 3, 1);
    u8* s0 = D_00262490;
    SetUpDoubleBuffer((GsDBuff*)s0, 0, 0x280, 0x100, 3, 0x30, 0);
    u8* p = s0;
    s32 end = (s32)s0 + 0x50;
    do {
        *(s32*)p &= -2;
        p[1] = 0x80;
        *(s32*)p |= 0x20;
        p += 0x28;
    } while ((s32)p < end);
    k.r = 0;
    k.g = 0;
    k.b = 0;
    k.a = 0x80;
    t = k;
    FillScreenColor(D_002BDC20, &t, 0);
    t = k;
    FillScreenColor(D_002BE1A0, &t, 0);
    t = k;
    FillScreenColor(D_002BDEE0, &t, 1);
    D_002BE460 = CreateLockSemaphore(0, 1);
    D_002BE464 = CreateLockSemaphore(0, 1);
    AddInterruptHandler(2, (void (*)(void))HandleVblankStart, 0);
    EnableInterruptCause(2);
    AddInterruptHandler(0, (void (*)(void))HandleGsFinish, 0);
    EnableInterruptCause(0);
    InitMeshQueue();
    ResetDisplayBuffers();
}

