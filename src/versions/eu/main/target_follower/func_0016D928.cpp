// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL picks an id from a word table and resolves it with a PAL-only function instead of indexing 32-byte slots.
extern s32 D_eu_0024AFD8[];
KeyRecord* func_eu_001DE018(s32 id);

void StartRandomStreamVoice(TargetFollower* self)
{
    s32 r;
    s32* tbl;

    if (self->f5C0 == 0) {
        return;
    }
    if (HasStreamVoice() != 0) {
        return;
    }
    r = RandomIntInRange(0, 0x64);
    if (r >= 0x14) {
        return;
    }
    tbl = D_eu_0024AFD8;
    r = RandomIntInRange(0, 6);
    OpenKeyRecord(func_eu_001DE018(tbl[r]));
    self->f5CC = 1;
}
