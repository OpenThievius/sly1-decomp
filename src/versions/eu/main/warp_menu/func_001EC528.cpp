// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two floats of the global are at 0x584 and 0x588 (US 0x274, 0x278).
struct Glob_1EC528_eu { u8 pad0[0x584]; f32 f584; f32 f588; };

void DecrementWorld3BossGauge(World3Boss* self)
{
    Glob_1EC528_eu* g = (Glob_1EC528_eu*)&g_gaugeBarElement;
    DecrementGaugeCount((u8*)&g_gaugeBarElement);
    self->fA68 = 2;
    g->f584 = g->f588;
}
