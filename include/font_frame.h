// SPDX-License-Identifier: AGPL-3.0-or-later
// The font upload frame, glyph and string layout records.
#ifndef FONT_FRAME_H
#define FONT_FRAME_H

#include "common.h"

struct FontUploadFrame { PacketWriter a; u8 buf[0x100]; };
struct StringLayout
{
  f32 x;
  f32 y;
  f32 width;
  f32 height;
  s32 color;
  s32 horizontalAlign;
  s32 verticalAlign;
};
struct FrameGlyph {
    Font* font;
    s8 key;
    u8 p5[3];
    f32 paddingX;
    f32 paddingY;
    f32 scaleX;
    f32 scaleY;
    u32 color;
};
struct FrameRect { f32 x, y, w, h; };

#endif
