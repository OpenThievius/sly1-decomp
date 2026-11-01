// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0015DF18.cpp func_eu_0015DF18 --unit src/main/0015C000.cpp
// Still differs: Adds n or 2n to the word at +8 by kind (0 or 1), else returns 1 (switch form); only the return-1 path differs: ours branches to a shared epilogue, retail has its own jr ra.
// Adds n (kind 0) or 2n (kind 1) to the position at +8 and returns it; any other kind returns 1.
struct Step_eu_0015DF18 {
    s32 kind;
    s32 pad04;
    s32 pos;
};

s32 func_eu_0015DF18(Step_eu_0015DF18* self, s32 n)
{
    switch (self->kind) {
    case 0:
        self->pos += n;
        return self->pos;
    case 1:
        self->pos += n * 2;
        return self->pos;
    default:
        return 1;
    }
}
