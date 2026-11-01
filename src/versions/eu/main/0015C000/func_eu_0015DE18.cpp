// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the span from start to end for kind 0, half of it for kind 1, and 0 for other kinds.
struct Span_eu_15DE18 { s32 kind; s32 start; s32 end; };
s32 func_eu_0015DE18(Span_eu_15DE18* a0)
{
    switch (a0->kind) {
    case 0:
        return a0->end - a0->start;
    case 1:
        return (a0->end - a0->start) >> 1;
    }
    return 0;
}
