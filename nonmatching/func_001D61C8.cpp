// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 206/276 (74.6%), checked 2026-11-06
// NEAR: order: as func_001D5FA8; it passes a 12-byte stack struct as the pointer argument.
#include "common.h"

struct Cfg_1D61C8 {
    u8 pad0[4]; f32 f4; f32 f8; u8 pad1[0x1C]; s32 i28; u8 pad2[8]; f32 f34; u8 pad3[8]; f32 f40; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74;
};
struct Host_1D61C8 { u8 pad[0x60]; u8* inner; };
struct Args_1D61C8 { s32 pad; f32 f4; u8* inner; };
extern s32 D_00275138;
extern Cfg_1D61C8 D_00605650;
extern u8 D_002750A8[];
void func_001F5C0C(void* p, s32 zero, s32 size);
s32 func_001B4688(s32 id);
void func_001D5678(void* a, s32 b, void* c, s32 d, void* e, void* f, void* g);

void func_001D61C8(Host_1D61C8* self)
{
    u8* inner = self->inner;
    if (D_00275138 == 0) {
        func_001F5C0C(&D_00605650, 0, 0x80);
        D_00605650.f44 = -100.0f;
        D_00605650.f4 = 5.0f;
        D_00605650.f40 = 0.5f;
        D_00605650.f8 = 1.0f;
        D_00605650.i28 = 0;
        D_00605650.f34 = 1.0f;
        D_00605650.i48 = 0xFFFFFFFF;
        D_00605650.i68 = 0xFFFFFFFF;
        D_00275138 = 1;
        D_00605650.f50 = 25.0f;
        D_00605650.f60 = 1.0f;
        D_00605650.f54 = 1.0f;
    }
    Args_1D61C8 args;
    D_00605650.i70 = 0;
    D_00605650.i74 = func_001B4688(0x15C);
    args.f4 = 60.0f;
    args.inner = inner;
    func_001D5678(inner + 0x140, 0x11, D_002750A8, 1, &args, &D_00605650, self);
}
