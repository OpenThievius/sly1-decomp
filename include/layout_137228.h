// SPDX-License-Identifier: AGPL-3.0-or-later
// The text layout other files fill before drawing (position, size, colour, two words), with
// setters they call and never inline. With `#pragma interface`, the one file that names this
// header in `#pragma implementation` (src/main/text_panel.cpp) writes them out, after its static
// initialiser; every other file refers to them by name.
#pragma interface

struct __attribute__((packed)) Rgba_137248 { u32 value; };

struct Layout_137228 {
    f32 x, y;
    f32 w, h;
    Rgba_137248 color;
    s32 f14;
    void* f18;

    void Pos(f32 x_, f32 y_);
    void Size(f32 w_, f32 h_);
    void Color(s32* value);
    void SetF14(s32 value);
    void SetF18(void* value);
};
