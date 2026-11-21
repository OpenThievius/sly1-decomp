// SPDX-License-Identifier: AGPL-3.0-or-later
// The item column, 0x14ABD0 to 0x14B0C0 (no .rodata, .data or .bss of its own): a screen
// element (its method table D_00218720) that stacks four items, their set-up, update, slide,
// draw, resize and clear, and PostItemColumnEntry. Its edges are not proved by retail, only by
// the change of role: the camera's controllers before it (camera_controller.cpp) and the
// symmetric solve after it (symmetric_solve.cpp). The functions from 0x14A7B8 to 0x14B6A8 read
// no .rodata or .data of either neighbour (gauge_manager.cpp's head), so the cut before could lie
// from 0x14A7B8 to 0x14ABD0 and the one after from 0x14AF38 to 0x14B0C0. The name is ours,
// after its role.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "object_pool.h"
#include "owner_message.h"
#include "vu0.h"
#include "scope_marker.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "ramp_profile.h"

extern f32 g_timeScale;
extern T217D_Vt g_buttonHintElementMethods;


// Initialiser of the item column: a screen element that owns four items of the item's method
// table (D_00218330), each initialised.
void InitItemColumn(StackedCaptionGroup* self)
{
    u32 n;

    InitScreenElement(self, 0x20);
    ButtonHintElement* e = self->items;
    for (n = 0; n < 4; n++) {
        e->vt = &g_buttonHintElementMethods;
        g_buttonHintElementMethods.m00(e, 0x12);
        e++;
    }
}

// Sets the column up: its text, then each of its four items (font scale 0.8, one second to slide
// in and out, no hold time).
void SetupItemColumn(StackedCaptionGroup* self)
{
    ButtonHintElement* e;
    u32 i;

    e = (ButtonHintElement*)self;
    SetupScreenElementText(e);
    e = self->items;
    for (i = 0; i < 4; i++) {
        e->vt->m01(e);
        e->frame = 0;
        e->font->sx = 0.8f;
        e->font->sy = 0.8f;
        SetScreenElementSlideInTime(e, 1.0f);
        SetScreenElementSlideOutTime(e, 1.0f);
        SetScreenElementHoldTime(e, 0.0f);
        e++;
    }
}

// Gives the column and each of its four items the new clock.
void UpdateItemColumn(StackedCaptionGroup* self, f32* clock)
{
    SetScreenElementClock(self, clock);
    ButtonHintElement* e = self->items;
    for (u32 i = 0; i < 4; i++) {
        e->vt->m17(e, clock);
        e++;
    }
}

// Updates the column's slide and then that of each item shown.
void UpdateItemColumnSlide(StackedCaptionGroup* self)
{
    UpdateScreenElementSlide(self);
    for (s32 i = 0; i < self->count; i++) {
        ButtonHintElement* s = &self->items[i];
        s->vt->m02(s);
    }
}

// Draws the column's items stacked downward from its position, each scaled in blend by
// g_timeScale for the draw, while g_elementStack.count is 1.
void DrawItemColumn(StackedCaptionGroup* self)
{
    if (g_elementStack.count == 1) {
        f32 acc = self->y;
        s32 i;
        for (i = 0; i < self->count; i++) {
            ButtonHintElement* e = &self->items[i];
            f32 saved = e->blend;
            f32 base = self->x;
            f32 scaled = saved * g_timeScale;
            e->y = acc;
            e->x = base;
            e->blend = scaled;
            e->vt->m09(e);
            e->blend = saved;
            acc += e->h;
        }
    }
}

// Sets the column to show n items, with the place offset (x, y), and resizes it to n lines of the
// font's height.
void ResizeItemColumn(StackedCaptionGroup* self, s32 n, f32 x, f32 y)
{
    self->place->dx = x;
    self->place->dy = y;
    self->count = n;
    Font* q = self->font;
    SetScreenElementSize(self, self->w, (f32)q->height * q->sy * (f32)n);
    self->vt->m16(self, 2);
}

// Calls slot 16 of the column with 0, which clears it.
void ClearItemColumn(StackedCaptionGroup* self)
{
    self->vt->m16(self, 0);
}

// Sets the text of item index in a column of screen items (underscores become spaces), resizes the
// column to the widest item and a line's height times the number of items and, with a hold time,
// shows the item for that time less its own slide-in and slide-out time (at least one frame, 1/60
// s).
void PostItemColumnEntry(StackedCaptionGroup* self, s32 index, char* text, f32 hold)
{
    ButtonHintElement* item = &self->items[index];
    for (char* p = text; *p != 0; p++) {
        if (*p == '_') {
            *p = ' ';
        }
    }
    item->vt->m08(item, text);
    f32 width = 0.0f;
    for (s32 i = 0; i < self->count; i++) {
        width = self->items[i].w >? width;
    }
    Font* q = self->font;
    SetScreenElementSize(self, width, (f32)q->height * q->sy * (f32)self->count);
    if (hold != 0.0f) {
        item = &self->items[index];
        f32 span = item->vt->m11(item);
        span += item->vt->m13(item);
        hold -= span;
        if (hold <= 0.0f) {
            hold = 0.016666668f;
        }
        SetScreenElementHoldTime(item, hold);
        item->vt->m14(item);
    }
}
