// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: resets the two engines after a pending change and restores the slot's pose.
struct Eng_1F0908;
typedef void (*SetFn_1F0908)(Eng_1F0908* e, s32 mode);
struct EngVt_1F0908 { u8 pad[0x40]; SetFn_1F0908 set; };
struct Eng_1F0908 { EngVt_1F0908* vt; };
void SetScreenElementHoldTime(Eng_1F0908* e, f32 x);
void SetElementTextFromEntry(Eng_1F0908* e, s32 a, s32 b);
struct Eng_eu_1F0908 {
    EngVt_1F0908* vt;
    u8 pad4[0x56C];
    s32 i570;
    u8 pad574[0x400];
    s32 i974;
};

void AnnouncePendingWarpEntry(WarpPage* self)
{
    if (D_00276250 == -1) return;
    SetScreenElementHoldTime(&D_002721D0, ((g_saveData->f19D8 << 8) | g_saveData->f19DC) == 4 ? 0.5f : 2.0f);
    D_002721D0.vt->m16(&D_002721D0, 2);
    Eng_eu_1F0908* e = ((Eng_eu_1F0908*)&D_0026F138);
    e->i570 = 0;
    e->vt->set((Eng_1F0908*)e, 0);
    SetElementTextFromEntry((Eng_1F0908*)e, g_saveData->f19D8, g_saveData->f19DC);
    e->i974 = 1;
    SetScreenElementHoldTime((Eng_1F0908*)e, 0.0f);
    e->vt->set((Eng_1F0908*)e, 2);
    Animation* sl = self->entries[D_00276250].f00;
    if (sl != 0) {
        f32 f = 0.0f;
        if (D_00276654 == 0) f = sl->length;
        ReplaceAnimationPlayer(sl, self, 0, &self->f2F0, f, 0.0f);
    }
    if (self->f2E8 != 0) {
        for (s32 i = 0; i < self->f2E8->startCount; i++) {
            AnimEvent* en = &self->f2E8->startList[i];
            if (en->kind == 10) {
                BaseObject* n = FindFirstObjectById(self->world, 0x104, en->a8.i, self);
                if (n != 0) n->desc->m02(n);
            }
        }
    }
    D_00276250 = -1;
}
