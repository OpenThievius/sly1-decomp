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

extern s32 D_00275BEC;
extern f32 g_timeScale;
extern T217D_Vt D_00218330;


void InitItemColumn(T217D_720* self)
{
    u32 n;

    InitScreenElement(self, 0x20);
    T217D_330* e = self->items;
    for (n = 0; n < 4; n++) {
        e->vt = &D_00218330;
        D_00218330.m00(e, 0x12);
        e++;
    }
}

void SetupItemColumn(T217D_720* self)
{
    T217D_330* e;
    u32 i;

    e = (T217D_330*)self;
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

void UpdateItemColumn(T217D_720* self, f32* clock)
{
    SetScreenElementClock(self, clock);
    T217D_330* e = self->items;
    for (u32 i = 0; i < 4; i++) {
        e->vt->m17(e, clock);
        e++;
    }
}

void UpdateItemColumnSlide(T217D_720* self)
{
    UpdateScreenElementSlide(self);
    for (s32 i = 0; i < self->count; i++) {
        T217D_330* s = &self->items[i];
        s->vt->m02(s);
    }
}

void DrawItemColumn(T217D_720* self)
{
    if (D_00275BEC == 1) {
        f32 acc = self->y;
        s32 i;
        for (i = 0; i < self->count; i++) {
            T217D_330* e = &self->items[i];
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

void ResizeItemColumn(T217D_720* self, s32 n, f32 x, f32 y)
{
    self->place->dx = x;
    self->place->dy = y;
    self->count = n;
    Font* q = self->font;
    SetScreenElementSize(self, self->w, (f32)q->height * q->sy * (f32)n);
    self->vt->m16(self, 2);
}

void ClearItemColumn(T217D_720* self)
{
    self->vt->m16(self, 0);
}

void PostItemColumnEntry(T217D_720* self, s32 index, char* text, f32 hold)
{
    T217D_330* item = &self->items[index];
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
