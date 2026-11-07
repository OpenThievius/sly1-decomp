// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: draws the object with a texture pointer set on the output, and the 50 Hz offsets.
// D_eu_0027939C is US D_0027240C, at an address the tools do not pair.
struct __attribute__((packed)) Pk4_1E0678 { s32 v; };
typedef void (*VFn_1E0678)(void* self, void* handle, void* out, void* tbl);
struct VTab_1E0678 { u8 pad0[0x48]; s16 adj; u8 pad1[0x4C - 0x4A]; VFn_1E0678 fn; };

struct Obj_eu_1E0678 {
    u8 pad0[4];
    s32 f4;
    u16 f8;
    u8 pad_a[0x408 - 0xA];
    u8 f408[0x518 - 0x408];
    Pk4_1E0678 f518;
    f32 f51c;
    void* f520;
    u8 pad524[0x534 - 0x524];
    f32 f534;
    f32 f538;
    u8 pad53c[0x544 - 0x53C];
    f32 f544;
    f32 f548;
    f32 f54c;
};

extern f32 D_eu_0027939C;
void func_00137260(TextLayout* out, void* tex);
void func_eu_001374E0(TextLayout* out, s32 flag);
void func_0015C8B8(s32 handle, f32 a, f32 b);
void func_eu_0015DCB8(void* out, void* p, s32 handle, s32 z);
void func_eu_0015E7E0(void* a, void* b, s32 c, void* d);
void func_0015C900(s32 handle);

struct OutT_eu_1E0678 : TextLayout {
    void Tex(void* t) { func_00137260(this, t); }
    void FlagC(s32 f) { func_eu_001374E0(this, f); }
};

struct Hd_eu_1E0678 {
    static void Draw(void* h, TextLayout* out, void* tbl)
    {
        if (*(void**)h != 0) {
            VTab_1E0678* vt = *(VTab_1E0678**)((u8*)*(void**)h + 0x4C);
            vt->fn((u8*)*(void**)h + vt->adj, h, out, tbl);
        }
    }
};

void func_001E0678(Obj_eu_1E0678* self)
{
    Pk4_1E0678 tmp;
    OutT_eu_1E0678 out;
    Pk4_1E0678 slot;
    u8 loc[0xC0];

    if (self->f8 != 0) {
        u8* tex = self->f408;
        PushFontScale(self->f4, self->f51c, self->f51c);
        tmp = self->f518;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->f54c);
        f32 p = self->f544;
        f32 q = self->f548;
        s32 held = tmp.v;
        out.Pos(self->f534, self->f538 - D_eu_0027939C * 54.305084228515625f);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.Tex(tex);
        out.FlagB(0);
        out.FlagC(0);

        u8* h = (u8*)self->f520;
        if (h != 0) {
            slot = *(Pk4_1E0678*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->f54c);
            Hd_eu_1E0678::Draw(self->f520, &out, &g_gsPacketWriter);
            *(Pk4_1E0678*)((u8*)self->f520 + 0x18) = slot;
        }
        func_eu_0015DCB8(loc, &self->f8, self->f4, 0);
        func_eu_0015E7E0(loc, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->f4);
    }
}
