// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the text id 0xA4 of the object func_eu_00160718 gives (passing its key through), or PAL's empty string D_eu_0027F0B0 when there is none.
extern char D_eu_0027F0B0[];
struct Obj_eu_00160750 { u8 pad[0xA4]; s32 fA4; };
void* func_eu_00160718(s32 key);
const char* func_eu_001DDAB0(s32 id);

const char* func_eu_00160750(s32 key)
{
    Obj_eu_00160750* o = (Obj_eu_00160750*)func_eu_00160718(key);
    if (o != 0) {
        return func_eu_001DDAB0(o->fA4);
    }
    return D_eu_0027F0B0;
}
