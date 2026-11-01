// SPDX-License-Identifier: AGPL-3.0-or-later
// Calls PAL-only func_eu_001AAFE0 on the object, then its virtual slot 14 when its field 0x570 is set, the global D_00262E10 is not in state 6 and D_00275BC0 holds 3 with its field at 0x2C below 2; otherwise its virtual slot 15.
typedef void (*VFnE_eu_001AE468)(void* self);
struct Obj_eu_001AE468_hdr { VFnE_eu_001AE468* vtbl; u8 pad[0x570 - 4]; s32 f570; };
struct Ctx_eu_001AE468 { u8 pad[0x2220]; s32 f2220; };
struct Mgr_eu_001AE468 { s32 f0; s32 f4; u8 pad[0x2C - 8]; s32 f2C; };

void func_eu_001AAFE0(void* self);

void func_eu_001AE468(void* p)
{
    Obj_eu_001AE468_hdr* self = (Obj_eu_001AE468_hdr*)p;
    func_eu_001AAFE0(p);
    if (self->f570 != 0) {
        Ctx_eu_001AE468* c = (Ctx_eu_001AE468*)D_00262E10;
        if (c == 0 || c->f2220 != 6) {
            Mgr_eu_001AE468* m = (Mgr_eu_001AE468*)D_00275BC0;
            if (m->f4 == 3 && m->f2C < 2) {
                self->vtbl[14](p);
                return;
            }
        }
    }
    self->vtbl[15](p);
}
