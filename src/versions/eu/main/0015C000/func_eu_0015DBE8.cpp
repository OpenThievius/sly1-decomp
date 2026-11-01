// SPDX-License-Identifier: AGPL-3.0-or-later
// Binary search of a table of 8-byte entries, sorted by their u16 key; returns the entry or 0.
struct Entry_eu_0015DBE8 {
    u16 key;
    u16 pad02;
    s32 value;
};

struct Lookup_eu_0015DBE8 {
    u8 pad00[0x78];
    s32 count;
    Entry_eu_0015DBE8* table;
};

Entry_eu_0015DBE8* func_eu_0015DBE8(Lookup_eu_0015DBE8* self, u16 key)
{
    s32 k = key;
    s32 hi = self->count - 1;
    s32 lo = 0;
    Entry_eu_0015DBE8* base;

    if (hi >= 0) {
        base = self->table;
        do {
            s32 mid = (hi + lo) / 2;
            Entry_eu_0015DBE8* e = (Entry_eu_0015DBE8*)(mid * 8 + (s32)base);
            s32 diff = k - e->key;
            if (diff == 0) {
                return e;
            }
            if (diff > 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } while (hi >= lo);
    }
    return 0;
}
