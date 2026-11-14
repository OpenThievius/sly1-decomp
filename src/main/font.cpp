// SPDX-License-Identifier: AGPL-3.0-or-later
// The fonts and text, 0x15C178 to 0x15E6A8 (its .rodata from 0x24A220, its .data from
// 0x262250): the font registry, measuring, wrapping and drawing strings, the font's GCC vtables
// (g_fontMethods, the font's and its abstract base's), glyph drawing and frames, loading and
// image upload, and the text reader with its colour, font and scale codes. Its .rodata is its two
// vtables, which GCC 2.95 writes after a file's literals and jump tables (docs/AGENT_WORKFLOW.md,
// "Finding and proving a file"): they end the range's .rodata at 0x24A2D0, consistent with this
// file but not proving its start. Its edges are cut by role only, from the object cycler
// (object_cycler.cpp) and to the render frames (render_frame.cpp); the cut before could lie
// from 0x15C0A0 to 0x15C178, the one after from 0x15E5F0 to 0x15E6A8. The name is ours, after
// its role.
#include "common.h"
#include "effect_spawner.h"
#include "vu0.h"
#include "asm_func.h"
#include "system.h"
#include "effect_owner.h"
#include "effect.h"
#include "shapes.h"
#include "active_set_solver.h"
#include "list_iter.h"
#include "transform_object.h"
#include "object_group.h"
#include "cursor_animator.h"
#include "object_cycler.h"
#include "scaling_volume.h"
#include "world.h"
#include "globals.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "base_object.h"
#include "packet_writer.h"
#include "font.h"
#include "render_frame.h"
#include "text_reader.h"
#include "layout_137228.h"
#include "scope_marker.h"
#include "vu0.h"
#include "functions/buffered_stream.h"
#include "functions/pooled_object.h"
#include "functions/texture_upload.h"
struct BumpAllocator;



void* AllocateFrontMemory(s32 size);

void* AllocateFrontMemory(s32 size);

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void CopyMemory(void* dst, void* src, u32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void CopyMemory(void* dst, void* src, u32 size);


// An entry of a GCC 2.95 vtable as this file defines D_0024A220 (the font table).
struct VtableEntry { s32 delta; void (*fn)(); };
extern const VtableEntry g_fontMethods[22];
void* AllocateObjectMemory(u32);
void CopyFont(Font*, Font*);

extern s32 g_fonts[];
extern s32 g_defaultFont;

FontGlyph* FindFontGlyph(Font* a, s32 b);

void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

void* InitGifPacket(void* p);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);

void CopyFontMetrics(Font* self, Font* dst);

FontGlyph* FindFontGlyph(Font* table, s8 key);

void AddDmaRefTag(void* obj, s32 a, s32 b);

void SetFontClipRect(Font* unused, Vec4U* v, PacketWriter* obj);
s32 AddFontImagesToFrame(Font* self, void* obj);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void BeginGifRegListTag(PacketWriter* self, u32 a1, u64 a2);

extern s32 g_defaultFont;

void CopyMemory(void* dst, void* src, u32 size);


void* InitGifPacket(void* p);

void AddDmaRefTag(void* list, u32 count, s32 value);

void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);


void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);


void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

s32 WrapTextLines(TextReader* self, f32 limit);

extern s8 g_fontEscapeKeys[];
extern s32 g_fonts[];

s32 WrapFontString(Font* self, u8* s, f32 w);

// NEAR: the first load of self->p54 goes to $v0 (retail $v1), so two
// pointer loads differ in register choice; everything else matches.

struct FontUploadFrame { PacketWriter a; u8 buf[0x100]; };
PacketWriter* InitGifPacket(PacketWriter* p);

// Matched: for loop over i with D_00262264 + i * 0x88.

extern s32 g_fontCount;
extern u8* g_fontRecords;

void UploadFontImages(Font* self, void* arg);


void AddGifRegListFloat(PacketWriter* self, s32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* self, s32 a1, s32 a2, u32 a3, u32 a4);

FontGlyph* FindFontGlyph(Font* self, s8 key);

s32 WrapTextLines(TextReader* self, f32 limit);
f32 MeasureTextWidth(TextReader* self);

struct FontHeader {
    u16 u0;
    u16 u2;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    f32 scale;
    u16 uC;
    u16 padE;
};



struct BufferedStream;
void* AllocateFrontMemory(s32 n);
extern s32 g_glyphUOffset;
extern s32 g_glyphVOffset;

FontGlyph* FindFontGlyph(Font* self, s8 key);
s32 AddFontImagesToFrame(Font* self, void* obj);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void BeginGifRegListTag(PacketWriter* self, u32 a1, u64 a2);
void AddGifRegListFloat(PacketWriter* self, s32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* self, s32 a1, s32 a2, u32 a3, u32 a4);
void func_0015E678(void);

void RewindTextReader(TextReader* self);



typedef struct StringLayout StringLayout;
typedef signed long s64;
typedef unsigned long u64;
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


void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);
void SetTextDefaultColor(TextReader* self, Rgba_137248* p);

// Inline text codes: ~RRGGBB / ~. colour, &<id> / &. font, ^<d><d> / ^. scale.
s32 FindFontByKeyChar(s32 id);
void CopyFont(Font* font, Font* out);
void PopFontScale(Font* font);
void PushFontScale(Font* font, f32 a, f32 b);

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

FontGlyph* FindFontGlyph(Font* self, s8 key);
void PushFontScale(Font* p, f32 a, f32 b);
void PopFontScale(Font* p);
void DrawFontQuad(Font* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, PacketWriter* s);


void ClearDefaultFont(void)
{
    g_defaultFont = 0;
}

s32 IsFontLoaded(s32 a0)
{
    if (a0 == -1) {
        goto none;
    }
    if (((s32*)g_fonts)[a0] != 0) {
        goto some;
    }
none:
    return 0;
some:
    return 1;
}

s32 GetFontById(s32 a)
{
    if (a == -1) {
        return 0;
    }
    s32 v = g_fonts[a];
    if (v != 0) {
        return v;
    }
    return g_defaultFont;
}

s32 FindFontByKeyChar(s32 a0)
{
    s8 key = (s8)a0;
    s32 i = 0;
    while (i < 5 && key != g_fontEscapeKeys[i]) {
        i++;
    }
    if (i < 5) {
        return g_fonts[i];
    }
    return 0;
}

void CopyFontMetrics(Font* src, Font* dst)
{
    dst->f00 = src->f00;
    dst->advance = src->advance;
    dst->height = src->height;
    dst->sx = src->sx;
    dst->sy = src->sy;
    dst->depth = src->depth;
    CopyMemory(dst->stack, src->stack, src->depth << 3);
    dst->useTestWord = src->useTestWord;
    dst->testWord = src->testWord;
    dst->drawZ = src->drawZ;
}

void SetFontClipRect(Font* unused, Vec4U* v, PacketWriter* obj)
{
    if (v != 0) {
        s32 pw = (s32)(v->x + v->z) - 1;
        s32 pz = (s32)((v->y + v->w) * 0.454545468f) - 1;
        s32 py = (s32)(v->y * 0.454545468f);
        s32 px = (s32)v->x;
        BeginGifTag(obj, 0, 1, 0xE);
        u64 key = (u64)px | ((u64)pw << 16) | ((u64)py << 32) | ((u64)pz << 48);
        AddGifRegisterWrite(obj, 0x40, key);
    }
}

void ResetFontClipRect(Font* unused, Vec4U* clip, PacketWriter* obj)
{
    if (clip != 0) {
        BeginGifTag(obj, 0, 1, 0xE);
        AddGifRegisterWrite(obj, 0x40, 0xDF0000027F0000UL);
    }
}

f32 MeasureFontString(Font* self, const char* s)
{
    f32 acc;
    const char* p;
    if (s == 0) {
        return 0.0f;
    }
    p = s;
    acc = 0.0f;
    while (*p != 0) {
        const FontVt* n = self->vt;
        acc = acc + n->width((Font*)((u8*)self + n->adj3), (s8)(u8)*p++);
    }
    return acc;
}

f32 MeasureFontStringHeight(Font* self, u8* s, f32 width)
{
    f32 a = (f32)self->height * self->sy;
    s32 n = WrapFontString(self, s, width);
    return a * (f32)n;
}

s32 WrapFontString(Font* self, u8* s, f32 w)
{
    s32 count = 1;
    s8* cur = (s8*)s;
    f32 acc = 0.0f;
    while (*cur != 0) {
        s32 c = (s8)(s32)*(u8*)cur;
        if (c == 10) {
            acc = 0.0f;
            count++;
        } else {
            const FontVt* t = self->vt;
            acc += t->width((Font*)((u8*)self + t->adj3), c);
        }
        if (w != 0.0f && w < acc) {
            s8* p = cur;
            while (p >= (s8*)s) {
                s8 c2 = *p;
                if (c2 == 10) {
                    break;
                }
                if (c2 == 32 || c2 == 9) {
                    cur = p;
                    acc = 0.0f;
                    *cur = 10;
                    count++;
                    break;
                }
                p--;
            }
            if (acc != 0.0f) {
                *cur = 10;
                count++;
                acc = 0.0f;
            }
        }
        cur++;
    }
    return count;
}

LINKER_REMNANT(func_0015C630);

void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s)
{
  const char *p;
  const char *next;
  s32 pending = 1;
  f32 x;
  f32 y;
  self->vt->begin((Font*) (((u8*) self) + self->vt->adj4), clip, s);
  if (par->verticalAlign == 0)
  {
    y = par->y;
  }
  else
  {
    f32 sc = self->sy;
    f32 h = ((f32) self->height) * sc;
    const char *q = str;
    if ((*q) != 0)
    {
      do
      {
        if ((*(q++)) == '\n')
        {
          h += ((f32) self->height) * sc;
        }
      }
      while ((*q) != 0);
    }
    if (par->verticalAlign == 2)
    {
      y = (par->y + par->height) - h;
    }
    else
    {
      y = par->y + ((par->height - h) * 0.5f);
    }
  }
  for (p = str; (*p) != 0; p = next)
  {
    f32 half = 0.5f;
    s32 right = 2;
    char c = *((const u8 *) p);
    next = p + 1;
    if (c == '\n')
    {
      pending = 1;
      y += ((f32) self->height) * self->sy;
    }
    else
    {
      if (pending != 0)
      {
        if (par->horizontalAlign == 0)
        {
          x = par->x;
        }
        else
        {
          const char *q;
          x = 0.0f;
          for (q = p; (*q != 0) && (*q != '\n'); q++)
          {
            x += self->vt->width((Font *) (((u8 *) self) + self->vt->adj3), *q);
          }
          if (par->horizontalAlign == right)
          {
            x = (par->x + par->width) - x;
          }
          else
          {
            x = par->x + ((par->width - x) * half);
          }
        }
        pending = 0;
      }
      x += self->vt->draw(x, y, (Font*) (((u8*) self) + self->vt->adj6), *p, par->color, s);
    }
  }

  self->vt->end((Font*) (((u8*) self) + self->vt->adj7), clip, s);
}

// Points recorded in order, the first of them scaled into u and v.
void PushFontScale(Font* trail, f32 su, f32 sv)
{
    FontScale* point = &trail->stack[trail->depth++];
    point->x = trail->sx;
    point->y = trail->sx;
    trail->sx = trail->stack[0].x * su;
    trail->sy = trail->stack[0].y * sv;
}

void PopFontScale(Font* obj) { obj->depth--; FontScale* item = &obj->stack[obj->depth]; obj->sx = item->x; obj->sy = item->y; }

Font* CloneFont(Font* owner, f32 x, f32 y)
{
	Font* out = (Font*)AllocateObjectMemory(0x88);
	out->vt = (const FontVt*)&g_fontMethods;
	CopyFont(owner, out);
	out->sx *= x;
	out->sy *= y;
	return out;
}

void CopyFont(Font* self, Font* dst)
{
    CopyFontMetrics(self, dst);
    dst->id = self->id;
    dst->imgA = self->imgA;
    dst->imgB = self->imgB;
    dst->texWord = self->texWord;
    dst->imageTagCount = self->imageTagCount;
    dst->imageTagData = self->imageTagData;
    dst->paletteTagCount = self->paletteTagCount;
    dst->paletteTagData = self->paletteTagData;
    dst->glyphCount = self->glyphCount;
    dst->glyphs = self->glyphs;
    dst->mask = self->mask;
}

s32 HasFontGlyph(Font* a, s32 b)
{
    return FindFontGlyph(a, (s8)b) != 0;
}

f32 GetFontCharWidth(Font* self, s8 key)
{
    FontGlyph* e = FindFontGlyph(self, key);
    f32 x;
    f32 y;
    if (e == 0) {
        x = self->sx;
        y = (f32)self->advance;
    } else {
        x = (f32)(e->w + 1);
        y = self->sx;
    }
    return x * y;
}

s32 AddFontImagesToFrame(Font* self, void* obj)
{
    s32 r = (g_buildFrame->flags & self->mask) == 0;
    if (r != 0) {
        CloseDmaTag((PacketWriter*)obj);
        AddDmaRefTag(obj, self->imageTagCount, self->imageTagData);
        AddDmaRefTag(obj, self->imgA->blockCount, self->imgA->data);
        if (self->imgB != 0) {
            AddDmaRefTag(obj, self->paletteTagCount, self->paletteTagData);
            AddDmaRefTag(obj, self->imgB->blockCount, self->imgB->data);
        }
        BeginDmaTag((PacketWriter*)obj);
        g_buildFrame->flags |= self->mask;
    }
    return r;
}

void BeginFontDraw(Font* self, Vec4U* clip, void* obj)
{
    SetFontClipRect(self, clip, (PacketWriter*)obj);
    s32 ok = AddFontImagesToFrame(self, obj);
    BeginGifTag((PacketWriter*)obj, 6, 1, 0xE);
    if (ok != 0) {
        AddGifRegisterWrite((PacketWriter*)obj, 0x3F, 0);
    }
    s64 v = 0x31001;
    if (self->useTestWord != 0) {
        v = self->testWord;
    }
    AddGifRegisterWrite((PacketWriter*)obj, 0x47, v);
    AddGifRegisterWrite((PacketWriter*)obj, 0x42, 0x44);
    AddGifRegisterWrite((PacketWriter*)obj, 6, self->texWord);
    AddGifRegisterWrite((PacketWriter*)obj, 0x14, 0x60);
    AddGifRegisterWrite((PacketWriter*)obj, 8, 5);
    AddGifRegisterWrite((PacketWriter*)obj, 0, 0x1D6);
    BeginGifRegListTag((PacketWriter*)obj, 5, 0x43431);
}

void BeginFontGlyphPacket(Font* self, void* obj)
{
    s32 ok = AddFontImagesToFrame(self, obj);
    BeginGifTag((PacketWriter*)obj, 6, 1, 0xE);
    if (ok != 0) {
        AddGifRegisterWrite((PacketWriter*)obj, 0x3F, 0);
    }
    AddGifRegisterWrite((PacketWriter*)obj, 6, self->texWord);
    AddGifRegisterWrite((PacketWriter*)obj, 0, 0x1D6);
    BeginGifRegListTag((PacketWriter*)obj, 5, 0x43431);
}

f32 DrawFontGlyph(f32 x, f32 y, Font* self, s8 key, u32 color, PacketWriter* s)
{
    FontGlyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->texWordU >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + w;
        f32 py = y + h;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            AddGifUvRegListEntry(s, e->u << 4, (s4 - e->v) << 4);
            AddGifXyzfRegListEntry(s, (s32)((x + 1728.0f) * 16.0f),
                          (s32)((y * 0.45454547f + 1936.0f) * 16.0f), self->drawZ, 0);
            AddGifUvRegListEntry(s, (e->u + e->w) << 4, (s4 - (e->v + self->height)) << 4);
            AddGifXyzfRegListEntry(s, (s32)((px + 1728.0f) * 16.0f),
                          (s32)((py * 0.45454547f + 1936.0f) * 16.0f), self->drawZ, 0);
        }
        return (f32)(e->w + 1) * self->sx;
    }
    return (f32)self->advance * self->sx;
}

void DrawFontGlyphTurned(Font* self, s8 key, u32 color, PacketWriter* s, f32 x, f32 y)
{
    FontGlyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->texWordU >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + h;
        f32 py = y + w;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            s32 u0 = (e->u << 4) + g_glyphUOffset;
            s32 v0 = ((s4 - e->v) << 4) + g_glyphVOffset;
            s32 u1 = ((e->u + e->w) << 4) + g_glyphUOffset;
            s32 v1 = ((s4 - (e->v + self->height)) << 4) + g_glyphVOffset;
            s32 ok = AddFontImagesToFrame(self, s);
            BeginGifTag(s, 6, 1, 0xE);
            if (ok != 0) {
                AddGifRegisterWrite(s, 0x3F, (u64)0);
            }
            u64 v = 0x31001;
            if (self->useTestWord != 0) {
                v = self->testWord;
            }
            AddGifRegisterWrite(s, 0x47, (u64)v);
            AddGifRegisterWrite(s, 0x42, (u64)0x44);
            AddGifRegisterWrite(s, 6, (u64)self->texWordU);
            AddGifRegisterWrite(s, 0x14, (u64)0x60);
            AddGifRegisterWrite(s, 8, (u64)5);
            AddGifRegisterWrite(s, 0, (u64)0x1D4);
            BeginGifRegListTag(s, 9, 0x434343431ULL);
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            AddGifUvRegListEntry(s, u0, v0);
            s32 sx = (s32)((x + 1728.0f) * 16.0f);
            s32 sy = (s32)((py * 0.45454547f + 1936.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx, sy, self->drawZ, 0);
            AddGifUvRegListEntry(s, u1, v0);
            s32 sy2 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx, sy2, self->drawZ, 0);
            AddGifUvRegListEntry(s, u0, v1);
            s32 sx2 = (s32)((px + 1728.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx2, sy, self->drawZ, 0);
            AddGifUvRegListEntry(s, u1, v1);
            AddGifXyzfRegListEntry(s, sx2, sy2, self->drawZ, 0);
            self->vt->end((Font*)((u8*)self + self->vt->adj7), 0, &g_gsPacketWriter);
        }
    }
}

void DrawFontQuad(Font* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, PacketWriter* s)
{
    color = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
    AddGifRegListFloat(s, color, 0.0f);
    AddGifUvRegListEntry(s, (s32)(u0 * 16.0f), (s32)(v0 * 16.0f));
    AddGifXyzfRegListEntry(s, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.45454547f + 1936.0f) * 16.0f), self->drawZ, 0);
    AddGifUvRegListEntry(s, (s32)(u1 * 16.0f), (s32)(v1 * 16.0f));
    AddGifXyzfRegListEntry(s, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.45454547f + 1936.0f) * 16.0f), self->drawZ, 0);
}

void DrawFontFrame(Font* self, FrameGlyph* item, FrameRect* r, PacketWriter* s)
{
    FontGlyph* e = FindFontGlyph(self, item->key);
    if (e != 0) {
        PushFontScale(item->font, item->scaleX, item->scaleY);
        f32 top = r->y;
        f32 sx = self->sx;
        f32 left = r->x;
        s32 u2i = e->u + e->w;
        f32 x2 = left + r->w + item->paddingX * sx;
        f32 cw = (f32)e->w * sx;
        f32 x1 = left - item->paddingX * sx;
        s32 sz = 1 << (s32)((self->texWordU >> 30) & 0xF);
        s32 height = self->height;
        f32 sy = self->sy;
        s32 v0i = sz - e->v;
        f32 x0 = x1 - cw;
        s32 v2i = sz - (e->v + height);
        f32 u1 = (f32)((e->u + u2i) / 2);
        f32 v1 = (f32)((v0i + v2i) / 2);
        f32 u0 = (f32)e->u;
        f32 y1 = top - item->paddingY * sy;
        f32 v0 = (f32)v0i;
        f32 x3 = x2 + cw;
        f32 y2 = top + r->h + item->paddingY * sy;
        f32 y0 = y1 - (f32)height * sy;
        f32 y3 = y2 + (f32)height * sy;
        self->vt->begin((Font*)((u8*)self + self->vt->adj4), 0, s);
        f32 v2 = (f32)v2i;
        f32 u2 = (f32)u2i;
        DrawFontQuad(self, item->color, x0, y0, x1, y1, u0, v0, u1, v1, s);
        DrawFontQuad(self, item->color, x2, y0, x3, y1, u1, v0, u2, v1, s);
        DrawFontQuad(self, item->color, x0, y2, x1, y3, u0, v1, u1, v2, s);
        DrawFontQuad(self, item->color, x2, y2, x3, y3, u1, v1, u2, v2, s);
        DrawFontQuad(self, item->color, x1, y0, x2, y1, u1, v0, u1, v1, s);
        DrawFontQuad(self, item->color, x1, y2, x2, y3, u1, v1, u1, v2, s);
        DrawFontQuad(self, item->color, x0, y1, x1, y2, u0, v1, u1, v1, s);
        DrawFontQuad(self, item->color, x2, y1, x3, y2, u1, v1, u2, v1, s);
        DrawFontQuad(self, item->color, x1, y1, x2, y2, u1, v1, u1, v1, s);
        PopFontScale(item->font);
        self->vt->end((Font*)((u8*)self + self->vt->adj7), 0, s);
    }
}

void SetFontClipRect(Font* unused, Vec4U* v, PacketWriter* obj);
void ResetFontClipRect(Font* unused, Vec4U* clip, PacketWriter* obj);
void BeginFontDraw(Font* self, Vec4U* clip, void* obj);
void BeginFontGlyphPacket(Font* self, void* obj);
void DrawFontGlyphTurned(Font* self, s8 key, u32 color, PacketWriter* s, f32 x, f32 y);
void DrawFontFrame(Font* self, FrameGlyph* item, FrameRect* r, PacketWriter* s);
extern "C" void HandleAbstractCall();
extern const VtableEntry g_fontMethods[22] = {{0, 0}, {0, (void (*)())CloneFont}, {0, (void (*)())HasFontGlyph}, {0, (void (*)())GetFontCharWidth}, {0, (void (*)())BeginFontDraw}, {0, (void (*)())BeginFontGlyphPacket}, {0, (void (*)())DrawFontGlyph}, {0, (void (*)())ResetFontClipRect}, {0, (void (*)())(void (*)(Font*, s8, u32, PacketWriter*, f32, f32))DrawFontGlyphTurned}, {0, (void (*)())DrawFontFrame}, {0, 0}, {0, 0}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, (void (*)())SetFontClipRect}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, (void (*)())ResetFontClipRect}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, 0}};

void LoadFont(Font* obj, BufferedStream* src)
{
    FontHeader l;
    ReadBufferedStreamBytes(src, 0x10, &l);
    s32 idx = l.b7;
    obj->id = idx;
    g_fonts[idx] = (s32)obj;
    obj->imgA = (ImageRecord*)((u8*)g_imageRecordsA + l.u0 * 32);
    void* t;
    if (l.u2 != 0xFFFF) {
        t = (u8*)g_imageRecordsB + l.u2 * 24;
    } else {
        t = 0;
    }
    obj->imgB = (PaletteRecord*)t;
    s32 n = l.uC;
    s32 A = l.b4, B = l.b5, C = l.b6; f32 F = l.scale;
    obj->f00 = A;
    obj->sx = F;
    obj->glyphCount = n;
    obj->height = C;
    obj->advance = B;
    obj->sy = F;
    obj->glyphs = (FontGlyph*)AllocateFrontMemory(n << 3);
    ReadBufferedStreamBytes((BufferedStream*)src, obj->glyphCount << 3, obj->glyphs);
}

void UploadFontImages(Font* self, void* arg)
{
    FontUploadFrame f;
    s32 n;

    (void)InitGifPacket(&f.a);
    ImageRecord* q = self->imgA;
    n = AllocateBump((s32*)arg, q->bumpSize);
    BuildImageTexRegister(self->imgA, n);
    self->texWordU = self->imgA->texWord;
    UsePacketBufferMemory(&f.a, 16, f.buf);
    StartImageUpload(self->imgA, n, &f.a);
    DetachPacketBufferCopy(&f.a, &self->imageTagCount, 0, &self->imageTagData, 7);
    if (self->imgB != 0) {
        n = AllocateBump((s32*)arg, self->imgB->bumpSize);
        BuildPaletteTexRegister(self->imgB, n);
        u64 t = self->texWordU;
        t |= self->imgB->texWordBits;
        self->texWordU = t;
        UsePacketBufferMemory(&f.a, 16, f.buf);
        StartPaletteUpload(self->imgB, n, &f.a);
        DetachPacketBufferCopy(&f.a, &self->paletteTagCount, 0, &self->paletteTagData, 7);
    }
}

// EXACT: element address written as off + (u32)entries

FontGlyph* FindFontGlyph(Font* self, u8 key)
{
    s32 lo = 0;
    s32 hi = self->glyphCount - 1;

    if (hi >= 0) {
        do {
            s32 mid = (hi + lo) / 2;
            s32 off = mid * 8;
            FontGlyph* e = (FontGlyph*)(off + (u32)self->glyphs);
            s32 d = key - e->key;

            if (d == 0) {
                return e;
            }
            if (d > 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } while (!(hi < lo));
    }
    return 0;
}

TextReader* InitTextReader(TextReader* self, char* text, Font* font)
{
    self->inlineFont.vt = (const FontVt*)&g_fontMethods;
    self->start = text;
    self->defaultFont = font;
    self->inlineFontColorBits = 0xFF808080;
    self->defaultColorBits = 0xFF808080;
    self->baseColorBits = 0xFF808080;
    self->colorBits = 0xFF808080;
    RewindTextReader(self);
    return self;
}

void RewindTextReader(TextReader* self)
{
    s32 t;
    self->cur = (char*)self->text;
    self->font = self->defaultFont;
    t = ((U32P*)((u8*)self + 0xA4))->v;
    ((U32P*)((u8*)self + 0xA0))->v = t;
    t = ((U32P*)((u8*)self + 0xA0))->v;
    ((U32P*)((u8*)self + 0x9C))->v = t;
    self->fontChanged = 0;
}

void SetTextDefaultColor(TextReader* self, Rgba_137248* color)
{
    u8* dst = (u8*)self;
    s32 v = ((U32P*)color)->v;
    ((U32P*)(dst + 0xA4))->v = v;
    v = ((U32P*)(dst + 0xA4))->v;
    ((U32P*)(dst + 0x9C))->v = v;
}

s32 ReadTextChar(TextReader* self)
{
    s32 done = 0;
    s32 changed = 1;
    Font* inl = &self->inlineFont;
    do {
        char* p = self->cur;
        switch (*p) {
        case '~':
            if (p[1] == '~') {
                self->cur = (char*)p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->baseColor = self->defaultColor;
                self->color = self->baseColor;
                self->cur += 2;
            } else {
                char* q = p + 1;
                u32 acc = 0;
                while (*q != 0 && q - self->cur < 7) {
                    u32 ch = (u8)*q;
                    u32 d;
                    if (ch - '0' < 10)
                        d = (s8)ch - '0';
                    else if (ch - 'A' < 6)
                        d = (s8)ch - 55;
                    else if (ch - 'a' < 6)
                        d = (s8)ch - 87;
                    else
                        break;
                    q++;
                    acc = (acc << 4) + d;
                }
                if (q - self->cur >= 7) {
                    self->baseColor.r = ((acc >> 16) & 0xFF) + 1 >> 1;
                    self->baseColor.g = ((acc & 0xFF00) >> 8) + 1 >> 1;
                    self->baseColor.b = (acc & 0xFF) + 1 >> 1;
                    self->color = self->baseColor;
                    self->cur += 7;
                } else {
                    self->font = self->defaultFont;
                    self->color = self->defaultColor;
                    done = 1;
                }
            }
            break;
        case '&':
            if (p[1] == '&') {
                self->cur = (char*)p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->font = self->defaultFont;
                self->color = self->baseColor;
                self->fontChanged = changed;
                self->cur += 2;
            } else {
                Font* nf = (Font*)FindFontByKeyChar(p[1]);
                if (nf != 0) {
                    CopyFont(nf, inl);
                    self->cur += 2;
                    Font* d = self->defaultFont;
                    f32 ratio = ((f32)d->height * d->sy) / ((f32)inl->height * inl->sy);
                    self->font = inl;
                    u8 al = self->color.a;
                    self->inlineFont.sx *= ratio;
                    self->inlineFont.sy *= ratio;
                    Rgba4 t = self->inlineFontColor;
                    t.a = al;
                    self->color = t;
                    self->fontChanged = changed;
                } else {
                    self->font = self->defaultFont;
                    done = 1;
                    self->color = self->defaultColor;
                    self->fontChanged = changed;
                }
            }
            break;
        case '^':
            if (p[1] == '^') {
                self->cur = (char*)p + 1;
                done = 1;
            } else if (p[1] == '.') {
                PopFontScale(self->font);
                self->cur += 2;
            } else {
                f32 a = (f32)(p[1] - '0') + (f32)(p[2] - '0') * 0.1f;
                Font* f = self->font;
                PushFontScale(f, a * f->sx, a * f->sy);
                self->cur += 3;
            }
            break;
        default:
            done = 1;
            break;
        }
    } while (done == 0);
    char* e = self->cur;
    char r = *e;
    self->cur = e + 1;
    return r;
}

s32 CountTextChars(void* self)
{
    s32 n = 0;
    RewindTextReader((TextReader*)self);
    while (ReadTextChar((TextReader*)self) != 0) {
        n++;
    }
    return n;
}

void SeekTextReader(TextReader* self, s32 n)
{
    RewindTextReader(self);
    for (;;) {
        if (ReadTextChar(self) == 0) {
            break;
        }
        if (n == 0) {
            break;
        }
        n--;
    }
    *self->cur = 0;
}

f32 SumTextWidth(TextReader* self)
{
    f32 acc = 0.0f;
    RewindTextReader(self);
    s32 item;
    while ((item = ReadTextChar(self)) != 0) {
        Font* holder = self->font;
        const FontVt* disp = holder->vt;
        acc += disp->width((Font*)((u8*)holder + disp->adj3), item);
    }
    return acc;
}

s32 WrapTextLines(TextReader* self, f32 limit)
{
    s32 lines = 1;
    f32 width = 0.0f;
    s32 newline = 10;
    s32 space = 32;
    s32 tab = 9;
    RewindTextReader(self);
    s32 c;
    while ((c = ReadTextChar(self)) != 0) {
        if (c == newline) {
            width = 0.0f;
            lines++;
        } else {
            Font* holder = self->font;
            const FontVt* glyph = holder->vt;
            width += glyph->width((Font*)((u8*)holder + glyph->adj3), c);
        }
        if (limit != 0.0f && limit < width) {
            s8* p = (s8*)self->cur - 1;
            while (p >= (s8*)self->start) {
                if (*p == 10) {
                    break;
                }
                if (*p == space || *p == tab) {
                    width = 0.0f;
                    self->cur = (char*)p + 1;
                    lines++;
                    *p = 10;
                    break;
                }
                p--;
            }
            if (width != 0.0f) {
                *self->cur = (s8)newline;
                lines++;
                width = 0.0f;
            }
        }
    }
    return lines;
}

f32 MeasureTextHeight(TextReader* self, f32 limit)
{
    Font* holder = self->defaultFont;
    f32 width = (f32)holder->height * holder->sy;
    s32 lines = WrapTextLines(self, limit);
    return width * (f32)lines;
}

f32 MeasureTextWidth(TextReader* self)
{
    f32 best = 0.0f;
    s32 newline = 10;
    RewindTextReader(self);
    f32 width = best;
    s32 c;
    while ((c = ReadTextChar(self)) != 0) {
        if (c == newline) {
            best = (width >? best);
            width = 0.0f;
        } else {
            Font* holder = self->font;
            const FontVt* glyph = holder->vt;
            width += glyph->width((Font*)((u8*)holder + glyph->adj3), c);
        }
    }
    best = (width >? best);
    return best;
}

void MeasureText(TextReader* self, f32 f, f32* out1, f32* out2)
{
    s32 n = WrapTextLines(self, f);
    f32 g = MeasureTextWidth(self);
    f32 k = (f32)self->defaultFont->height * self->defaultFont->sy;
    f32 t = (f32)n * k;
    if (out1 != 0) {
        *out1 = g;
    }
    if (out2 != 0) {
        *out2 = t;
    }
}

void DrawAlignedText(TextReader* self, Layout_137228* p, Vec4U* clip, PacketWriter* s)
{
    f32 f[64];
    Rgba_137248 u;
    s32 first = 1;
    s32 n = 0;
    f32 top;
    f32 left;
    s32 c;
    FillMemory(f, 0, 0x100);
    RewindTextReader(self);
    while ((c = ReadTextChar(self)) != 0) {
        if (c == 10) {
            n++;
        } else {
            f[n] += self->font->Width(c);
        }
    }
    c = (s32)p->f18;
    if (c == 0) {
        top = p->y;
    } else {
        f32 tot = (f32)(n + 1) * ((f32)self->defaultFont->height * self->defaultFont->sy);
        if (c == 2)
            top = (p->y + p->h) - tot;
        else
            top = p->y + (p->h - tot) * 0.5f;
    }
    u = p->color;
    SetTextDefaultColor(self, &u);
    Font* started = 0;
    f32 half = 0.5f;
    RewindTextReader(self);
    f32* fp = f;
    while ((n = ReadTextChar(self)) != 0) {
        if (n == 10) {
            first = 1;
            fp++;
            top += (f32)self->defaultFont->height * self->defaultFont->sy;
            continue;
        }
        if (first) {
            if (p->f14 == 0) {
                left = p->x;
            } else {
                f32 g = *fp;
                if (p->f14 == 2)
                    left = (p->x + p->w) - g;
                else
                    left = p->x + (p->w - g) * half;
            }
            first = 0;
        }
        if (started == 0) {
            self->font->Begin(clip, s);
            started = self->font;
        } else if (self->fontChanged != 0) {
            self->font->Flush(s);
            self->fontChanged = 0;
        }
        left += self->font->Draw(left, top, n, self->colorBits, s);
    }
    self->font->End(clip, s);
}

void UploadAllFontImages(void)
{
    u8 buf[16];
    InitBumpAllocator((BumpAllocator*)buf, 0x1400, 0x1E00);
    for (s32 i = 0; i < g_fontCount; i++) {
        UploadFontImages((Font*)(g_fontRecords + i * 0x88), buf);
    }
}

LINKER_REMNANT(func_0015E678);

// The file's .data, 0x262250 to 0x262280, in retail's order.
s8 g_fontEscapeKeys[8] = "02134";
s32 g_glyphUOffset = -8;
s32 g_glyphVOffset = -8;
// size: s32 (lw/sw), 4-byte label
s32 g_fontCount = 0;
// size: pointer to array allocated by new Ent[D_00262260] (lw/sw), 4-byte label
u8* g_fontRecords = 0;
// size: loop bound 5, stride 4 in func_0015C200
s32 g_fonts[5] = {0};
// size: s32 (lw/sw), 4-byte label
s32 g_defaultFont = 0;
