// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 196/212 (92.5%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0015C5C0.cpp func_eu_0015C5C0 --unit src/main/0015C000.cpp
// Still differs: Packs four scaled truncated box values into a 64-bit key; with s0,s1,s3,s2 statement order only 5 lines differ (trunc of s3 vs s2 order).
// Packs four scaled, truncated box values from a float quad into one 64-bit key and passes it on.
struct Quad_eu_15C5C0 { f32 a; f32 b; f32 c; f32 d; };

void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, u64 key);

void func_eu_0015C5C0(void* unused, Quad_eu_15C5C0* q, void* ctx)
{
    if (q != 0) {
        f32 k = 0.5462962985038757f;
        s32 s0 = (s32)(q->a + q->c) - 1;
        s32 s1 = (s32)((q->b + q->d) * k) - 1;
        s32 s3 = (s32)q->a;
        s32 s2 = (s32)(q->b * k);
        func_001613C0(ctx, 0, 1, 0xE);
        u64 key = (u64)s3 | ((u64)s0 << 16) | ((u64)s2 << 32) | ((u64)s1 << 48);
        func_00161708(ctx, 0x40, key);
    }
}
