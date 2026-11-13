// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: 50 Hz (a hold of 1/50 s, not 1/60), the entries are 0x570 apart from 0x574, and the text goes through a PAL-only lookup
// (func_eu_001DDAB0) in place of US's underscore-to-space loop.

struct Item_eu_14AF38 {
    const T217D_Vt* vt;
    Font* font;
    u8 pad08[0x544 - 8];
    f32 w;                      // 0x544
    u8 pad548[0x570 - 0x548];
};

struct Column_eu_14AF38 {
    const T217D_Vt* vt;
    Font* font;
    u8 pad08[0x570 - 8];
    s32 count;                  // 0x570
    Item_eu_14AF38 items[4];    // 0x574
};

char* GetTextTableEntry(char* text);

void PostItemColumnEntry(Column_eu_14AF38* self, s32 index, char* text, f32 hold)
{
    Item_eu_14AF38* item = &self->items[index];
    item->vt->m08((ScreenElement*)item, GetTextTableEntry(text));
    f32 width = 0.0f;
    for (s32 i = 0; i < self->count; i++) {
        width = self->items[i].w >? width;
    }
    Font* q = self->items[0].font;
    SetScreenElementSize((ScreenElement*)self, width, (f32)q->height * q->sy * (f32)self->count);
    if (hold != 0.0f) {
        item = &self->items[index];
        f32 span = item->vt->m11((ScreenElement*)item);
        span += item->vt->m13((ScreenElement*)item);
        hold -= span;
        if (hold <= 0.0f) {
            hold = 0.02f;
        }
        SetScreenElementHoldTime((ScreenElement*)item, hold);
        item->vt->m14((ScreenElement*)item);
    }
}
