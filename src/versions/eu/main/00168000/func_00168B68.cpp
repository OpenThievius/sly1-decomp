// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL runs at 50 Hz (50.0f) and uses a 468.61017f screen height.
void func_00168B68(f32 t)
{
    Frame_168B68 f;
    s32 i = 0;
    s32 n;

    func_001611B8(&f);
    n = (s32)(t * 50.0f);
    func_001683B8();
    D_002626CC = 0;
    if (n > 0) {
        do {
            f32 x = ((f32)i + 1.0f) / (f32)n;
            f32 y = x * 255.0f;
            s32 v = (s32)(x * y);
            i++;
            func_001529C8(&f, 0x40, &f.value);
            func_00152B38(&f);
            func_0019DDA0(0.0f, 0.0f, 640.0f, 468.61017f, 0, 0, 0, v, &f);
            func_001613C0(&f, 0, 1, 0xE);
            func_00161708(&f, 0x61, 0);
            func_00161200(&f);
            func_00152D30(&f);
            func_001529E0(&f, 0, 0);
            func_001686E8(D_00261F1C, &f.value);
            func_001683E8();
        } while (i < n);
    }
}
