// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the text lookup grew a switch: each row of D_eu_0026B308 holds a mode and two text ids, and mode 2 picks one by the index (a flag, a pad state bit) before the id is turned into text.
struct Row_193598_eu {
    s32 mode;
    s32 ids[2];
};
struct Pad_193598_eu {
    u8 pad[0x19EC];
    u32 flags;
};
struct Slot_193598_eu {
    u8 pad[0xC];
    f32 f0C;
    u8 rest[0x1A5C - 0x10];
};
extern Row_193598_eu D_eu_0026B308[];
extern s32 D_eu_0026ABE4;
extern Pad_193598_eu* D_eu_002636F0;
extern Slot_193598_eu D_eu_00265CD0[];
extern u8 D_eu_0026B530[][0x200];
s32 func_001A7EE8(Pad_193598_eu* p);
void func_001935B0(Slot_193598_eu* a, void* b);
const char* func_eu_001DDAB0(s32 i);

void* func_00193598(s32 x, s32 index)
{
    s32 id = -1;
    Row_193598_eu* row;
    void* out = 0;
    row = &D_eu_0026B308[index];

    switch (row->mode) {
    case 1:
        id = row->ids[0];
        break;
    case 2:
        switch (index) {
        case 9:
            id = D_eu_0026ABE4 != 0 ? row->ids[1] : row->ids[0];
            break;
        case 13:
            id = row->ids[IsPadPatternEnabled(D_eu_002636F0) == 0];
            break;
        case 15:
            id = row->ids[(D_eu_002636F0->flags & 0x80) != 0];
            break;
        case 16:
            id = row->ids[(D_eu_002636F0->flags & 0x40) != 0];
            break;
        case 24:
            id = row->ids[(D_eu_002636F0->flags & 0x200) != 0];
            break;
        case 25:
            id = row->ids[(D_eu_002636F0->flags & 0x400) != 0];
            break;
        case 26:
            id = row->ids[(D_eu_002636F0->flags & 0x800) != 0];
            break;
        }
        break;
    case 0: {
        s32 n = index - 10;
        Slot_193598_eu* slot = &D_eu_00265CD0[n];
        if (slot->f0C != 0.0f) {
            out = D_eu_0026B530[n];
            FormatGameSummary(slot, out);
        } else {
            id = 0x87;
            if (x < 0x12) {
                if (x >= 0x10) {
                    id = 0x86;
                }
            }
        }
        break;
    }
    }
    if (id != -1) {
        out = (void*)func_eu_001DDAB0(id);
    }
    return out;
}
