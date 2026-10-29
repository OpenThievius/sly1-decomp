// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: candidate is 212 bytes versus retail 180; dispatch shape and loop body still differ.
#include "common.h"

struct Object_192230 {
    u8 pad00[0x574];
    void* resource;
    u8 pad578[0x34];
    s32 values[9];
    s32 count;
};
void func_00127378(void*, s32, s32);
void func_001BF788(void*, s32);

void func_00192230(Object_192230* self, s32 kind, s32 value)
{
    func_00127378(self, kind, value);
    if (kind == 11) goto call_resource;
    if (kind == 16) goto search_values;
    return;
call_resource:
        func_001BF788(self->resource, 0);
        return;
search_values:
    {
        s32 count = self->count;
        if (count > 0) {
            if (self->values[0] == value) {
                self->values[0] = 0;
            } else {
                for (s32 i = 1; i < count; i++) {
                    if (self->values[i] == value) {
                        self->values[i] = 0;
                        break;
                    }
                }
            }
        }
    }
}
