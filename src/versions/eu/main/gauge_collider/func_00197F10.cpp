// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two slots written in D_0026D348 on code 0x3F3 are at 0x574 and 0x578 (not 0x264 and 0x268).
void HandleGaugeColliderNotification(GaugeCollider* self, s32 kind, void* rec)
{
    s32 code;
    HandleSwitchedColliderNotification(self, kind, rec);
    switch (kind) {
    case 0xB:
        self->noticeValue = 0;
        return;
    case 0xA:
        self->noticeValue = *(s32*)rec;
        return;
    case 0x14:
        if (rec != self->phaseWalker) {
            return;
        }
        GetStateWalkerCurrentKey((StateWalker*)rec, &code);
        if (code == 0x3F3) {
            u8* tbl;
            *(void**)D_0026E744 = (u8*)self + 0x67C;
            tbl = (u8*)&g_gaugeAmountCaption;
            *(void**)(tbl + 0x574) = (u8*)self + 0x680;
            *(void**)(tbl + 0x578) = (u8*)self + 0x684;
            SetWorldActiveFollower(self->world, self);
            StartTimer(&g_timerElement, self->timeLimit);
            SetTimerLimit(&g_timerElement, 0.0f, (T217D_510_Fn)EndGaugeColliderTimer);
            StartTimerCounting(&g_timerElement);
        } else {
            if (code < 0x3F3) {
                return;
            }
            if (code < 0x3F6) {
                StopTimer(&g_timerElement);
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                D_0026E4E0.vt->m15(&D_0026E4E0);
                g_timerElement.vt->m15(&g_timerElement);
                SetWorldActiveFollower(self->world, 0);
            }
        }
        return;
    }
}
