// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 126/132 (95.5%), checked 2026-11-01
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

f32 MeasureFontString(Self_eu_15C6F0* self, const u8* s)
{
    if (s == 0) {
        return 0.0f;
    }
    const u8* p = s;
    f32 total = 0.0f;
    if (*p != 0) {
        do {
            f32 r = self->f4C->fn1C((u8*)self + self->f4C->off18, *p);
            p++;
            total += r;
        } while (*p != 0);
    }
    return total;
}
