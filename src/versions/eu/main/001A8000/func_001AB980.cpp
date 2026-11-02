// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the clock sits 0x310 further on, formats into a 16-byte stack buffer and hands it to func_eu_001AB238 instead of drawing with the font calls.
struct Clock_1AB980_eu;
typedef void (*Cb_1AB980_eu)(Clock_1AB980_eu* self, s32 arg);
struct Clock_1AB980_eu
{
    u8 pad0[0x570];
    s32 mode;
    f32 start;
    f32 time;
    f32 rate;
    s32 lastSec;
    s32 lastTenth;
    f32 warn;
    u8 pad58C[4];
    Cb_1AB980_eu onWarn;
    s32 warned;
    f32 limit;
    Cb_1AB980_eu onEnd;
};
void func_001ABE20(Clock_1AB980_eu* self, s32 state);
void func_eu_001AB238(void* self, const char* s);

void func_001AB980(Clock_1AB980_eu* self, f32 dt)
{
    char buf[16];
    f32 t = __builtin_fabsf(self->time);
    s32 sec = (s32)t;
    s32 hund = (s32)(t * 10.0f);
    s32 tenth = (s32)((t - (f32)sec) * 10.0f);

    if (self->mode == 2)
    {
        f32 rate = self->rate;
        if (rate != 0.0f)
        {
            if (rate < 0.0f && 0.0f <= self->time && self->time < 10.0f)
            {
                if (tenth != self->lastTenth)
                {
                    if (tenth == 9)
                        func_001BFCD8(0x7E, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                    else if (tenth == 4)
                        func_001BFCD8(0x7F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                }
            }
            else if (sec != self->lastSec)
            {
                func_001BFCD8((sec & 1) ? 0x72 : 0x73, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
    }
    self->lastTenth = tenth;
    self->lastSec = sec;

    if ((*(Clock_00261858*)&D_00261858).on != 0 && self->mode == 2 && (*(s32*)D_00262C68 & 2))
    {
        s32 warn = 0;
        s32 end = 0;
        f32 rate = self->rate;
        self->time = self->time + dt * rate;
        if (rate < 0.0f)
        {
            if (self->warn != D_0024CD6C && self->time <= self->warn)
                warn = 1;
            if (self->time <= self->limit)
                end = 1;
        }
        else if (rate > 0.0f)
        {
            if (self->warn != D_0024CD6C && self->warn <= self->time)
                warn = 1;
            if (self->time >= self->limit)
                end = 1;
        }
        if (warn && self->warned == 0)
        {
            self->warned = 1;
            if (self->onWarn != 0)
                self->onWarn(self, 0);
        }
        if (end)
        {
            self->time = self->limit;
            func_001BFCD8(1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            func_001ABE20(self, 0);
            if (self->onEnd != 0)
                self->onEnd(self, 1);
        }
        t = __builtin_fabsf(self->time);
    }

    s32 show = 0;
    s32 tenths = 0;
    s32 hi;
    s32 lo;
    s32 sep;
    s32 h;
    if (t < 10.0f && (h = (s32)(t * 10.0f)) != hund)
    {
        hi = h / 10;
        lo = h % 10;
        sep = '.';
        tenths = 1;
        show = 1;
    }
    else
    {
        s32 s = (s32)t;
        if (s != sec || (self->mode == 1 && (*(Clock_00261858*)&D_00261858).now - self->start <= (*(Clock_00261858*)&D_00261858).wait))
        {
            hi = s / 60;
            lo = s % 60;
            sep = ':';
            show = 1;
        }
    }
    if (show)
    {
        func_001E20B8(buf, 0x10, D_0024CD50, 0x54, hi, sep, (lo < 10 && !tenths) ? D_0024CD60 : D_0024CD68, lo);
        func_eu_001AB238(self, buf);
    }
}
