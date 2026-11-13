// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: T217D_2E0 fields f260 to f27C are at 0x570 to 0x58C (US 0x260 to 0x27C).
struct Bar_17B8C0_eu { u8 pad0[0x570]; s32 f570; s32 f574; s32 f578; s32 f57C; s32 f580; f32 f584; f32 f588; f32 f58C; };

void SetCountdownState(CountdownCollider* self, s32 state)
{
    if (state == self->mode) {
        return;
    }
    D_00263E2C = -1;
    switch (state) {
    case 1:
        {
            Bar_17B8C0_eu* bar = (Bar_17B8C0_eu*)&g_gaugeBarElement;
            bar->f57C = bar->f570 = 4;
            bar->f580 = bar->f574 = 4;
            bar->f578 = 0x10;
            bar->f588 = 1.0f;
            bar->f584 = 0.0f;
            bar->f58C = -1.0f;
        }
        SetWorldActiveFollower(self->world, self);
        break;
    case 2:
        MarkLevelDone(5);
        StartMemoryCardSave(&g_memoryCard);
        break;
    }
    self->mode = state;
    self->startTime = g_gameClock[1];
}
