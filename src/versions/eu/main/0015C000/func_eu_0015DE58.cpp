// SPDX-License-Identifier: AGPL-3.0-or-later
// Dispatches on the mode field: 0 and 1 call one of two functions with the object, otherwise 0.
struct Mode_eu_15DE58 { s32 mode; void* obj; };
s32 func_001E2100(void* obj);
s32 func_eu_001E3018(void* obj);

s32 func_eu_0015DE58(Mode_eu_15DE58* self)
{
    switch (self->mode) {
    case 0:
        return func_001E2100(self->obj);
    case 1:
        return func_eu_001E3018(self->obj);
    }
    return 0;
}
