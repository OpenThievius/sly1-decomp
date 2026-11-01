// SPDX-License-Identifier: AGPL-3.0-or-later
// Clears D_eu_00263710, passes the result of func_eu_0020A810 to func_eu_00160568 and then calls func_00160918.
extern s32 D_eu_00263710;
void* func_eu_0020A810(void);
void func_eu_00160568(void* p);

void func_eu_00160538(void)
{
    D_eu_00263710 = 0;
    func_eu_00160568(func_eu_0020A810());
    func_00160918();
}
