// SPDX-License-Identifier: AGPL-3.0-or-later
// Dispatches on the mode field: 0 and 1 call one of two functions with the object, otherwise 0.
struct Mode_eu_15DE58 { s32 mode; void* obj; };
s32 GetStringLength(void* obj);
s32 GetWideStringLength(void* obj);

s32 GetTextReaderLength(Mode_eu_15DE58* self)
{
    switch (self->mode) {
    case 0:
        return GetStringLength(self->obj);
    case 1:
        return GetWideStringLength(self->obj);
    }
    return 0;
}
