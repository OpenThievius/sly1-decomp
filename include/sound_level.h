// SPDX-License-Identifier: AGPL-3.0-or-later
// A request for a sound level: a 12-byte record of the pool at World::pool1BB8, kept on
// World::list1BC4 (func_001BEEF8 makes one). The highest level among them is the current one
// (func_001BEF88); the IOP is sent the level plus 20. Objects hold the one they pushed and
// give it back with RemoveSoundLevelAndRecompute (func_001BF0D8). Written for this project from
// what retail's code does.
#ifndef SOUND_LEVEL_H
#define SOUND_LEVEL_H

#include "common.h"

struct SoundLevelEntry {
    s32 level;              // 0x00: -20 to 0x6B (PushSoundLevel)
    u8 pad4[8];
};

typedef char check_SoundLevelEntry[sizeof(SoundLevelEntry) == 0xC ? 1 : -1];

#endif
