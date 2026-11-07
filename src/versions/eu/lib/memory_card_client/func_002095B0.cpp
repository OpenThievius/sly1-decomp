// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with func_eu_001F7738, a function only PAL has, where US calls func_00201720
s32 func_eu_001F7738(Name_2095B0* dst, const char* src, s32 max);

s32 OpenCardFile(s32 a0, s32 a1, const char* a2, s32 a3)
{
    if (TrySemaphore((Handle_2095B0*)g_cardSemaphore) < 0) {
        return -200;
    }
    u8* pool = g_cardClient;
    if (*(s32*)(pool + 0x24) == 0) {
        PostSemaphore((Handle_2095B0*)g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore((Handle_2095B0*)g_cardSemaphore);
        return -210;
    }
    u8* name = D_0062ADF0 + 0x14;
    func_eu_001F7738((Name_2095B0*)name, a2, 0x3FF);
    ((s32*)name)[-5] = a0;
    Rec_2095B0* r = (Rec_2095B0*)(name - 0x14);
    r->f08 = a3;
    r->f04 = a1;
    r->name[0x3FF] = 0;
    s32 result = CallRemoteService((Pool_2095B0*)pool, 2, 1, r, 0x414, D_0062C300, 4, 0, 0);
    if (result == 0) {
        g_cardRequestInFlight = 2;
    } else {
        PostSemaphore((Handle_2095B0*)g_cardSemaphore);
    }
    return result;
}
