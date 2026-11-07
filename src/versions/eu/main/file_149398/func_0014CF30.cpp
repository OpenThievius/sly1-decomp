// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two slots written in D_0026D348 are at 0x574 and 0x578 (not 0x264 and 0x268).
struct Glob_eu_14CF30 {
    u8 pad0[0x574];
    void* f574;
    void* f578;
};

void HandleGaugeManagerNotification(GaugeManager* self, s32 kind, void* key)
{
    HandlePlacedObjectNotification(self, kind, key);
    switch (kind) {
    case 6: {
        s32 i;
        for (i = 0; i < self->slotCount; i++) {
            if (self->slots[i].key == key) {
                break;
            }
        }
        if (i < self->slotCount) {
            self->slots[i].key = 0;
        }
        break;
    }
    case 0x14:
        if (key == self->device) {
            s32 out;
            GetStateWalkerCurrentKey(key, &out);
            if (out == 0x3FD) {
                (*(Glob_eu_14CF30*)&g_gaugeAmountCaption).f574 = &self->amount;
                (*(Glob_eu_14CF30*)&g_gaugeAmountCaption).f578 = &self->maxAmount;
                SetWorldActiveFollower(self->world, self);
                StartTimer(&g_timerElement, self->f2D8);
                SetTimerLimit(&g_timerElement, 0.0f, FinishGaugeOnTimeout);
                StartTimerCounting(&g_timerElement);
            }
            if (self->tag430 == 0x3FD) {
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                g_timerElement.vt->m15(&g_timerElement);
                SetWorldActiveFollower(self->world, 0);
            }
            self->tag430 = out;
        }
        break;
    }
}

