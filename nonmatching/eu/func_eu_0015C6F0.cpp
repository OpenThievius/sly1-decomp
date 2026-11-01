// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0015C6F0.cpp func_eu_0015C6F0 --unit src/main/0015C000.cpp
// Still differs: Sums a float callback result over the bytes of a string; only the loop registers differ (sub-object v0 vs retail v1, callback v1 vs v0, byte test v0 vs v1; 6 lines).
// Only in PAL: sums a float over the bytes of a string, each byte handed to a callback of the object's sub-object at 0x4C.
typedef f32 (*Glyph_eu_15C6F0_Fn)(void* self, u8 c);

struct Sub_eu_15C6F0 {
    u8 pad0[0x18];
    s16 off18;
    u8 pad1A[2];
    Glyph_eu_15C6F0_Fn fn1C;
};

struct Self_eu_15C6F0 {
    u8 pad0[0x4C];
    Sub_eu_15C6F0* f4C;
};

f32 func_eu_0015C6F0(Self_eu_15C6F0* self, const u8* s)
{
    if (s == 0) {
        return 0.0f;
    }
    const u8* p = s;
    f32 total = 0.0f;
    if (*p != 0) {
        do {
            u32 c = *p;
            p++;
            total += self->f4C->fn1C((u8*)self + self->f4C->off18, c);
        } while (*p != 0);
    }
    return total;
}
