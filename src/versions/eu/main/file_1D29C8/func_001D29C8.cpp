// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: restores the mode, resets the camera sub-object and sets the mode's music/state.
const char* func_eu_001DDAB0(s32 id);

void func_001D29C8(u32 mode)
{
    switch (D_00274F74) {
    case 1:
        if ((*(Ctx_1D29C8**)&D_00262E10) == 0)
            goto tail;
        if ((*(Ctx_1D29C8**)&D_00262E10)->f2220 == 0xD)
            func_00175170((*(Ctx_1D29C8**)&D_00262E10), 0, -1);
        break;
    case 3:
        if ((*(Ctx_1D29C8**)&D_00262E10) == 0)
            goto tail;
        if ((*(Ctx_1D29C8**)&D_00262E10)->f1518 != 0) {
            if (func_00182FC8((*(Ctx_1D29C8**)&D_00262E10)->f1518) != 0)
                func_00126D60((*(Ctx_1D29C8**)&D_00262E10)->f1518, 0.5f);
        }
        break;
    }
    if ((*(Ctx_1D29C8**)&D_00262E10) != 0) {
        D_00261854 = 1.0f;
        if ((*(Ctx_1D29C8**)&D_00262E10)->f2750 != 0) {
            if (func_00182FC8((*(Ctx_1D29C8**)&D_00262E10)->f2750) != 0)
                func_001D32D8((*(Ctx_1D29C8**)&D_00262E10)->f2750, (*(Ctx_1D29C8**)&D_00262E10), 1);
        }
        func_001D31D0((*(Ctx_1D29C8**)&D_00262E10), 0);
        if ((*(Ctx_1D29C8**)&D_00262E10) != 0) {
            if ((void*)(*(Ctx_1D29C8**)&D_00262E10) == func_001925F0())
                D_00274F74 = mode;
        }
    }
tail:
    if (mode != D_002623C0->f19FC && mode < 7) {
        func_001AA8B8(&D_0026EC70, ((*(Ctx_1D29C8**)&D_00262E10) != 0 && (void*)(*(Ctx_1D29C8**)&D_00262E10) == func_001925F0()) ? 3.0f : 8.0f);
        func_001AA788(&D_0026EC70, 0.6f);
        D_0026EC70.vt->fn20(&D_0026EC70, (s32)func_eu_001DDAB0((s32)D_00274F58[mode]));
        D_0026EC70.vt->fn38(&D_0026EC70);
        D_002623C0->f19FC = mode;
    }
}
