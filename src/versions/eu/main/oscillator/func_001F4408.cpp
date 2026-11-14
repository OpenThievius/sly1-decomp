// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL picks the element D_eu_00263710 (32 bytes each) of the table at D_00247AD0 + 0x80 for the first call.
extern s32 D_eu_00263710;
void BeginLevelExit(s32 flag, s32 n)
{
    GameProgress* ctx = g_saveData;
    LevelRecordWord78* o;
    ObjectSubGroup* v;
    LevelFadeEntry* k;
    FadeRequest args;
    if (ctx->levelIndex == 5) {
        goto lm1;
    }
    if (ctx->entryIndex != 0) {
        goto l4490;
    }
    o = (LevelRecordWord78*)g_currentLevelRecord;
    if ((o->flags & 1) != 0) {
        goto l4470;
    }
lm1:
    StartObjectFade((IdentityKey*)(D_00247AD0 + 0x80 + D_eu_00263710 * 32), -1, n);
    return;
l4470:
    k = LookupEntryById((ctx->levelIndex << 8) | 1);
    StartObjectFade((IdentityKey*)k, 0x1BD, n);
    return;
l4490:
    v = (ObjectSubGroup*)FindActiveObjectSubGroup();
    if (v == 0) {
        goto larg;
    }
    if (flag != 0) {
        v->count = 0;
    }
    StartObjectSubGroupFinish(v);
    return;
larg:
    args.kind = 1;
    args.key = &D_00275B04;
    args.f08 = -1;
    args.f0C = -1;
    args.flags = 0;
    StartScreenFade(&g_screenFade, &args, n);
}
