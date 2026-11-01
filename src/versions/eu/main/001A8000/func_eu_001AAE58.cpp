// SPDX-License-Identifier: AGPL-3.0-or-later
// Walks the 37 object pointers of D_002486B0: each object whose field 0x560 is set gets its virtual slot 10 called on it.
typedef void (*VFn_eu_001AAE58)(void* self);
struct Obj_eu_001AAE58 { VFn_eu_001AAE58* vtbl; u8 pad[0x560 - 4]; s32 f560; };

void func_eu_001AAE58(void)
{
    void** p = (void**)D_002486B0;
    s32 n = 0x24;
    do {
        Obj_eu_001AAE58* o = (Obj_eu_001AAE58*)*p;
        n--;
        if (o->f560 != 0) {
            VFn_eu_001AAE58 fn = o->vtbl[10];
            if (fn != 0) {
                fn(o);
            }
        }
        p++;
    } while (n >= 0);
}
