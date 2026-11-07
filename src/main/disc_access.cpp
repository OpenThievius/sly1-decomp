// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "key_id.h"

// The sector check's state, the word before this file's .data: GCC aligns the read errors
// (24 bytes) to 8, so a .data that started at 0x2613EC would put them at 0x261400.
extern s32 g_discSectorCheckState;

// The file's .data, in retail's order: the drive's state, the last result of a read request
// and the read errors.
s32 g_discStatus = -1;
s32 g_lastDiscReadResult = 0;
s32 g_discReadErrors[6] = { 0, 0, 0, 0, 0, 0 };

// In another stretch of .rodata (global_tables.cpp defines them): the read mode, the checked sector
// and its CRC-32.
extern const u32 D_00247AA0;
extern const u32 D_00247AA4;
extern const u32 D_00247AA8[2];
extern u8 D_002701B8[];
extern u8 g_discCheckSectorBuffer[];
extern u32 g_crc32Table[];
extern u8 g_pauseMenuElement[];

s32 StartDiscRead(s32 a0, s32 a1, void* a2, void* a3);
s32 SyncDiscRead(s32 mode);
s32 GetDiscReadError(void);
void UppercaseString(s8* p);
s32 GetStringLength(const s8* s);
void* AppendString(s8* dst, const char* src);
s32 FormatToString(void* dst, const char* fmt, ...);
s32 CheckDiscChanged(s32 a0, s32* out);
u32 func_00203A20(s32 arg);
s32 ReadDiscSectors(void*, void*, void*, void*);
s32 SyncDiscNCommand(s32);
s32 GetDiscError(void);
s32 RefreshDiscStatus(void);
s32 TestDiscReadDone(s32 value);
void SetPauseMenuLayerPage(void* self, s32 a, s32 b);

void ResetDiscSectorCheck(void)
{
    g_discSectorCheckState = 3;
}

// The second word of a key (GetKeyedDataSize, func_0018C1E8, hands it one).
s32 GetKeyIdSecond(KeyId* key)
{
    return key->second;
}

s32 NormalizeDiscPath(s8* path)
{
    UppercaseString(path);
    s32 len = GetStringLength(path);
    if (len != 0) {
        s8 last = path[len - 1];
        if (last != '\\' && last != '/') {
            AppendString(path, ";1");
            len = GetStringLength(path);
        }
    }
    s8* end = path + len;
    s8* out = path;
    s8* in = path;
    s32 count = 0;
    s32 n = 0;
    s32 max = 8;
    while (in < end) {
        switch (*in) {
        case '/':
        case '\\':
            if (n != 0) {
                *out++ = 0;
                n = 0;
                max = 8;
                count++;
            }
            break;
        case '.':
            if (n != 0 && max == 8) {
                *out++ = *in;
                n = 0;
                max = 3;
            }
            break;
        case ';':
            if (n != 0 && in == end - 2 && in[1] == '1') {
                *out++ = *in++;
                *out++ = *in;
                n += 2;
                break;
            }
        default:
            if (n < max) {
                if ((u8)(*in - 'A') < 26 || (u8)(*in - '0') < 10) {
                    *out++ = *in;
                } else {
                    *out++ = '_';
                }
                n++;
            }
            break;
        }
        in++;
    }
    if (n != 0) {
        *out = 0;
        count++;
    }
    return count;
}

INCLUDE_ASM(func_00140968);

void SendDiscCommand22WhenReady(void)
{
    if (g_discStatus == 0x14) {
        func_00203A20(2);
    }
}

void InitDiscAccessModule(void) {}

void StepDiscSectorCheck(void)
{
    s32 tmp[1];
    s32 s1;
    switch (g_discSectorCheckState) {
    case 3:
        if (CheckDiscChanged(2, tmp) != 0) {
            if (tmp[0] != 0) {
                if (RefreshDiscStatus() == 0) {
                    SetPauseMenuLayerPage(g_pauseMenuElement, 2, 0x16);
                    g_discSectorCheckState = 1;
                }
            }
        }
        break;
    case 1:
        s1 = *(s32*)D_002701B8;
        if (s1 == 2) {
            if (RefreshDiscStatus() != 0) {
                if (StartDiscRead((s32)D_00247AA4, 1, g_discCheckSectorBuffer, (void*)&D_00247AA0) == 1) {
                    g_discSectorCheckState = s1;
                }
            }
        }
        break;
    case 2:
        if (TestDiscReadDone(0) != 0) {
            u8* p = g_discCheckSectorBuffer;
            u32* tbl = g_crc32Table;
            u32 crc = 0xFFFFFFFF;
            s32 n = 0x7FF;
            do {
                crc = *(u32*)((u8*)tbl + (((crc ^ *p) & 0xFF) << 2)) ^ (crc >> 8);
                p++;
                n--;
            } while (n != -1);
            if ((s32)crc != (s32)D_00247AA8[0]) {
                g_discSectorCheckState = 1;
            } else {
                SetPauseMenuLayerPage(g_pauseMenuElement, 2, -1);
                g_discSectorCheckState = 3;
            }
        }
        break;
    }
}

// The path pieces func_00140B60 formats with, after func_001407A8's ";1" in .rodata.
extern const u16 D_00249E20[4] = { 0x5C, 0, 0, 0 };
extern const char D_00249E28[8] = "%s\\%s";
extern const char D_00249E30[8] = "cdrom0:";
extern const char D_00249E38[4] = "";

void FormatDiscPath(void* self, s8* a1, s32 flag)
{
    char buf[256];
    *(u16*)buf = D_00249E20[0];
    AppendString((s8*)buf, (const char*)a1);
    s32 n = NormalizeDiscPath((s8*)buf);
    char* p = buf;
    for (s32 i = 1; i < n; i++) {
        p[GetStringLength((s8*)p)] = 0x5C;
    }
    FormatToString(self, D_00249E28,
                  flag ? (void*)D_00249E30 : (void*)D_00249E38, buf);
}

void StartDiscReadUntilAccepted(void* a, void* b, void* c)
{
    s32 result;
    do {
        result = StartDiscRead((s32)a, (s32)b, c, (void*)&D_00247AA0);
        g_lastDiscReadResult = result;
        if (result != 1) { SyncDiscRead(0); g_discReadErrors[0] = GetDiscReadError(); }
    } while (result != 1);
}

void StartLowLevelDiscReadUntilAccepted(void* a, void* b, void* c)
{
    s32 result;
    do {
        result = ReadDiscSectors(a, b, c, (void*)&D_00247AA0);
        g_lastDiscReadResult = result;
        if (result != 1) { SyncDiscNCommand(0); g_discReadErrors[0] = GetDiscError(); }
    } while (result != 1);
}

s32 TestDiscReadDone(s32 value) { s32 result = SyncDiscRead((u32)value < 1u); return result == 0; }

LINKER_REMNANT(func_00140D88);
