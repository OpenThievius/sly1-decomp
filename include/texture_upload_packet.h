// SPDX-License-Identifier: AGPL-3.0-or-later
// The texture upload packet records.
#ifndef TEXTURE_UPLOAD_PACKET_H
#define TEXTURE_UPLOAD_PACKET_H

#include "common.h"

struct PacketWriter;
struct GsTex0 {
    u64 tbp : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
};
struct TextureUploadPacket : PacketWriter { u8 span[0x10]; void* out; };
struct QueuedGifTags {
    s32 f0;
    u8 pad0[0xC];
    s32 f10;
};

#endif
