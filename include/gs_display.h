// SPDX-License-Identifier: AGPL-3.0-or-later
// The GS display registers and the fade packet.
#ifndef GS_DISPLAY_H
#define GS_DISPLAY_H

#include "common.h"

struct PacketWriter;
struct FadePacket : PacketWriter { s32 value; u8 pad[0x3F0]; };
struct GsPmode { u32 en1 : 1; u32 rest : 31; u32 hi : 32; };
struct GsDispFb { u32 fbp : 9; u32 fbw : 6; u32 psm : 5; u32 pad0 : 12; u32 dbx : 11; u32 dby : 11; u32 pad1 : 10; };
struct GsDisplay { u32 dx : 12; u32 dy : 11; u32 magh : 4; u32 magv : 2; u32 pad0 : 3; u32 dw : 12; u32 dh : 11; u32 pad1 : 9; };
struct GsPrivRegs {
    GsPmode pmode; u8 pad0[0x70 - 8];
    GsDispFb dispfb2; u8 pad1[8];
    GsDisplay display2; u8 pad2[0x1000 - 0x88];
    u32 csr;
};

#endif
