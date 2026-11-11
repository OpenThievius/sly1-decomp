// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: SetFontClipRect's twin with PAL's vertical scale (0.546296 for NTSC's 0.454545):
// packs the clip rectangle into a scissor register write.
void func_eu_0015C5C0(Font* unused, Vec4U* v, PacketWriter* obj)
{
    if (v != 0) {
        s32 pw = (s32)(v->x + v->z) - 1;
        s32 pz = (s32)((v->y + v->w) * 0.5462962985038757f) - 1;
        s32 py = (s32)(v->y * 0.5462962985038757f);
        s32 px = (s32)v->x;
        BeginGifTag(obj, 0, 1, 0xE);
        u64 key = (u64)px | ((u64)pw << 16) | ((u64)py << 32) | ((u64)pz << 48);
        AddGifRegisterWrite(obj, 0x40, key);
    }
}
