// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: on first use reads the 14 bytes of the ROM version file "rom0:ROMVER" into D_eu_00284650 (printing a message when it cannot open or read it) and returns the buffer.
extern char D_eu_00284650[];
extern const char D_eu_00251270[];
extern const char D_eu_00251280[];
extern const char D_eu_00251298[];

s32 func_001F8C30(const char* name, s32 mode);
s32 ReadFile(s32 handle, char* buf, s32 size);
s32 CloseFile(s32 handle);
s32 PrintFormatted(const char* msg);

char* func_eu_0020A730(void)
{
    if (D_eu_00284650[0] == 0) {
        s32 h = func_001F8C30(D_eu_00251270, 1);
        if (h == -1) {
            PrintFormatted(D_eu_00251280);
        }
        if (ReadFile(h, D_eu_00284650, 14) == -1) {
            PrintFormatted(D_eu_00251298);
        }
        CloseFile(h);
    }
    return D_eu_00284650;
}
