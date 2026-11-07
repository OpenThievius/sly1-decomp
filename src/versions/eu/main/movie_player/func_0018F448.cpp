// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: initialises the loader object, its tasks and callbacks, and the CRC table; adds a per-channel task loop.
struct Obj_eu_18F448 {
    u8 pad0[0xC];
    void* fC;
    u8 pad1[0x48];
    void* f58;
    void* f5C;
    u8 pad2[0xC8];
    void* f128;
    void* f12C;
};
struct Tail_eu_18F448 {
    u8 pad0[0x14C];
    u32 crc;
    u8* cur;
    s32 remain;
};
extern s32 D_eu_002636EC;
extern s32 D_eu_002639FC;
extern u8 D_eu_002F52C0[];
extern u8 D_eu_00478240[];
extern u8 D_eu_00448240[];
extern u8 D_eu_005C04C0[];
extern u8 D_eu_005A4240[];
extern u8 D_eu_005C05E0[];
extern u8 D_eu_0014B588[];
void func_0018F448(Obj_18F448* self_, void* v)
{
    Obj_eu_18F448* self = (Obj_eu_18F448*)self_;
    s32 i;
    s32 n;

    self->fC = v;
    self->f58 = D_eu_002F52C0;
    self->f5C = D_eu_00478240;
    InitRingBuffer((u8*)self + 0x60, 0x30000, (void*)((s32)D_eu_00448240 | 0x20000000));
    StartMovieStream((MovieStream*)((u8*)self + 0x80));
    func_0020ADA0();
    func_0020AE40((u8*)self + 0x10, self->f58, 0x152F68);
    func_0020A538((u8*)self + 0x10, 0, 0, (void*)AcceptMovieDataIntoRing, self);
    for (n = 0; D_eu_002636EC >= n; n++) {
        func_0020A538((u8*)self + 0x10, 2, n, (void*)PassMovieDataToStream, self);
        func_0020A538((u8*)self + 0x10, 3, n, (void*)PassMovieDataToStream, self);
    }
    func_0020B168((u8*)self + 0x10, 1, (void*)FlushMovieToIpu, self);
    func_0020B168((u8*)self + 0x10, 4, (void*)FeedMovieDecoderWithoutWaiting, self);
    func_0020B168((u8*)self + 0x10, 0, (void*)AcceptMovieDecoderEvent, self);
    while (FeedMovieDecoder((Object_18F890*)self, 1) == 0) {
    }
    self->f128 = D_eu_005A4240;
    self->f12C = D_eu_005C04C0;
    D_eu_002639FC = 0;
    ((Tail_eu_18F448*)&g_moviePlayer)->cur = (u8*)0x100010;
    ((Tail_eu_18F448*)&g_moviePlayer)->remain = (s32)D_eu_0014B588;
    ((Tail_eu_18F448*)&g_moviePlayer)->crc = 0xFFFFFFFF;
    u8* tb = D_eu_005C05E0;
    i = 0;
    s32 j;
    do {
        u32 c = i;
        s32 k;
        s32 off = c * 4;
        j = c + 1;
        for (k = 7; k >= 0; k--) {
            if (c & 1) c = (c >> 1) ^ 0xEDB88320; else c = c >> 1;
        }
        *(u32*)(tb + off) = c;
        i = j;
    } while (j < 256);
}
