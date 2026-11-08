// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: a field of the system configuration word, or for a console whose ROM version is a tool's the byte D_eu_0028464C.
extern u8 D_eu_0028464C;
s32 func_eu_0020A7D0(void);

// What ReadSystemConfig fills: four words, the first holds the fields read here.
struct SystemConfig_eu {
    u32 word;
    u32 rest[3];
};
void ReadSystemConfig(SystemConfig_eu* out);

u32 func_eu_0020A810(void)
{
    SystemConfig_eu cfg;
    u32 r;
    ReadSystemConfig(&cfg);
    if (func_eu_0020A7D0() != 0) {
        r = D_eu_0028464C;
    } else {
        ReadSystemConfig(&cfg);
        u32 v = cfg.word;
        if (((v >> 13) & 7) == 0) {
            r = (v >> 4) & 1;
        } else {
            r = (v >> 16) & 0x1F;
        }
    }
    return r;
}
