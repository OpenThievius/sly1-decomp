// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: draws a ring of vertices around a centre, in PAL's screen scale.
void func_001F1E38(f32 cx, f32 cy, f32 radius, f32 angle, s32 n, s32* c1, s32* c2, s32 flags)
{
    Locals_1F1E38 loc;
    s32 i;
    f32 step = 6.2831855f / (f32)n;
    func_001613C0((Frame_1F1E38*)D_00262280, 0, 1, 0xE);
    func_00161708((Frame_1F1E38*)D_00262280, 0x47, 0x31001);
    func_00161708((Frame_1F1E38*)D_00262280, 0x42, (flags & 1) ? 0x48 : 0x44);
    func_001613C0((Frame_1F1E38*)D_00262280, 0x4D, 2, 0x41);
    func_00161458((Stream_1F1E38*)D_00262280, *c1);
    func_001615F0((Stream_1F1E38*)D_00262280, (u32)(s32)((cx + 1728.0f) * 16.0f),
                  (u32)(s32)((cy * 0.546296298f + 1920.0f) * 16.0f), 0, 0);
    loc.k = 0;
    for (i = 0; i < n + 1; i++) {
        func_001EAD88(func_001EA408(angle), &loc.x, &loc.y);
        loc.x = loc.x * radius + cx;
        loc.y = loc.y * radius + cy;
        if ((i & 1) && (flags & 2)) {
            func_00161458((Stream_1F1E38*)D_00262280, loc.k);
        } else {
            func_00161458((Stream_1F1E38*)D_00262280, *c2);
        }
        angle += step;
        func_001615F0((Stream_1F1E38*)D_00262280, (u32)(s32)((loc.x + 1728.0f) * 16.0f),
                      (u32)(s32)((loc.y * 0.546296298f + 1920.0f) * 16.0f), 0, 0);
    }
}
