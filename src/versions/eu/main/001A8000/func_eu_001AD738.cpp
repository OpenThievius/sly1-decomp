// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 68/76 (89.5%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AD738.cpp func_eu_001AD738 --unit src/main/001A8000.cpp
// Still differs: Returns 1 if func_001AAAC8 or the field at 0x570 is non-zero; retail does move s0,a0 before the call and move s1,zero in its delay slot, ours puts s1=0 first.
// Returns 1 when func_001AAAC8 gives non-zero or the field at 0x570 is set, 0 otherwise.
struct Obj_eu_001AD738;
s32 func_001AAAC8(Obj_eu_001AD738* self);
struct Obj_eu_001AD738 {
    u8 pad00[0x570];
    s32 flag;
};
s32 func_eu_001AD738(Obj_eu_001AD738* self)
{
    s32 r = 0;
    if (func_001AAAC8(self) != 0 || self->flag != 0) {
        r = 1;
    }
    return r;
}
