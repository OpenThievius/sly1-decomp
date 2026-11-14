// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the names come from a text table (func_eu_001DDAB0 ids 0x16, 0x18, 0x17), and the empty label and the flagged case go through PAL-only func_eu_001AB238 (with PAL's own empty string D_eu_0024CC20) and func_eu_001ADF10. The object field is at +0x974.
typedef void (*VFnV_16AF80)(void* self);
typedef void (*VFnS_16AF80)(void* self, const char* s);
const char* GetTextTableEntry(s32 id);
void SetScreenElementByteText(void* self, const char* s);
void SetElementWideTextFromIndexedCounts(void* self);
extern char D_eu_0024CC20[];
struct Obj_16AF80_eu {
    void** vtbl;
    u8 pad4[0x970];
    s32 f974;
};

void ShowCurrentObjectCaptions(CurrentPlacedObject* self)
{
    s32 s1 = 0;
    StateWalker* p = self->walkers[0].walker;

    if (p->currentEntry != p->index) {
        SetScreenElementByteText((&D_0026F138), D_eu_0024CC20);
    } else if (self->choice == 0) {
        void** vt = *(void***)(&D_0026F138);
        ((VFnS_16AF80)vt[8])((&D_0026F138), GetTextTableEntry(0x16));
    } else {
        s32 flags = g_saveData->levels[self->choice].f448;
        if (flags & 1) {
            SetElementWideTextFromIndexedCounts((&D_0026F138));
        } else if (self->choice == self->walkerChoice) {
            void** vt = *(void***)(&D_0026F138);
            ((VFnS_16AF80)vt[8])((&D_0026F138), GetTextTableEntry(0x18));
        } else {
            s1 = 1;
            SetScreenElementByteText((&D_0026F138), D_eu_0024CC20);
        }
    }

    SetScreenElementHoldTime((&D_0026F138), 0.0f);
    ((Obj_16AF80_eu*)(&D_0026F138))->f974 = 0;
    {
        void** vt = *(void***)(&D_0026F138);
        ((VFnV_16AF80)vt[14])((&D_0026F138));
    }

    if (s1 != 0) {
        ((VFnS_16AF80)(*(void***)(&D_0026FA90))[8])((&D_0026FA90), GetTextTableEntry(0x17));
        ((VFnV_16AF80)(*(void***)(&D_0026FA90))[14])((&D_0026FA90));
    } else {
        void** vt = *(void***)(&D_0026FA90);
        ((VFnV_16AF80)vt[15])((&D_0026FA90));
    }
}
