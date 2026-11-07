// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL has the table at its own address, read at 0x570 and stores 8 at offset 0x30 of D_00275BC0 (unaligned) before func_001E96F8.
struct Sys_1F0220_eu { u8 pad0[0x30]; s32 f30; } __attribute__((packed));
struct Tbl_1F0220_eu { u8 pad0[0x570]; void* f570; void* f574[1]; };
extern Tbl_1F0220_eu D_eu_00274868;

void SetScreenFadeMode(ScreenFade* self, s32 mode)
{
    if (self->mode == mode) goto L0410;
    if (self->mode == 2) {
        if (D_0026FA68 != 0) {
            SetWarpPageMode(D_0026FA68, 0);
        }
    }
    if (mode == 1) goto L02E0;
    if (mode < 2) {
        if (mode == 0) {
            self->opacityWord = 0;
            goto L0400;
        }
        self->mode = mode;
        goto L0404;
    }
    if (mode == 2) goto L02A0;
    if (mode == 3) goto L0374;
    self->mode = mode;
    goto L0404;

L02A0:
    if (self->active.kind != 0) {
        FadeRequest* q = &self->active;
        QueueWorldLoad((u8*)&g_worldLoadRequest, (s32)q->key, q->f08, q->f0C, q->flags);
    }
    self->active.kind = 0;
    self->opacity = 1.0f;
    self->queued.kind = 0;
    goto L0400;

L02E0:
    {
        s32 v = self->style;
        if (v == 2) goto L0300;
        if (v == 3) goto L0354;
        goto L0364;
    }

L0300:
    {
        s32 v = GetEntryIdByKey((s32)self->active.key);
        s32 a3 = v >> 8;
        s32 a2 = v & 0xFF;
        if (D_0026FA68 == 0) goto L034C;
        if (v == -1) goto L034C;
        s32 a1 = 10;
        if (a3 != 0) a1 = a2;
        SetWarpCursor(D_0026FA68, a1, 3);
        ShowCountedScreenElement(g_currentWorld);
        goto L0364;
    }

L034C:
    self->style = 0;
    goto L0364;

L0354:
    mode = 2;
    goto L02A0;

L0364:
    ((Sys_1F0220_eu*)g_elementStack)->f30 = 8;
    SetElementStackState(g_elementStack, 8);
    self->mode = mode;
    goto L0404;

L0374:
    {
        s32 a = self->style;
        if (a == 2) goto L038C;
        if (a == mode) goto L03EC;
        self->mode = mode;
        goto L0404;
    }

L038C:
    {
        if (self->style == D_00275BF0[0]) {
            s32 idx = g_previousLevelIndex;
            if (idx != -1) {
                D_eu_00274868.f570 = D_eu_00274868.f574[idx];
            }
        }
        if (D_eu_00274868.f570 != 0) {
            ((WarpPage*)D_eu_00274868.f570)->f2E0 = 3;
            SetWarpPageMode(D_eu_00274868.f570, 4);
            self->mode = mode;
            goto L0404;
        }
        self->style = 3;
        goto L0400;
    }

L03EC:
    FadeScreenToBlack(0.25f);
    self->style = 0;
    goto L0400;

L0400:
    self->mode = mode;
L0404:
    self->modeStartTime = g_elapsedTime[0];
L0410:
    return;
}
