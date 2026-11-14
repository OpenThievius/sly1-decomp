// SPDX-License-Identifier: AGPL-3.0-or-later
// An entry of the link tables ResolveObjectLinks (func_00124DF8)(self, count, table) walks when an object is set up:
// for each entry it finds the object id `id` names (func_0015A418, kind 1, or 5 with flag 1,
// | 0x100 with flag 0x20) and, unless flag 8, stores it at self + offset; unless flag 4 it calls
// func_00182ED8 on it, and with flag 0x10 func_001832F0(found, self). Written for this project
// from what retail's code does. The tables are data: no function fills them, so the type is
// named by the one that reads them: each entry links the object to another object found by id.
//
// 55 tables are passed to func_00124DF8 (every `func_00124DF8(..., D_X)` in src/, and
// D_00263558, which func_0016F810's assembly passes with 27). They are declared here without a
// length: their definitions (in C, in the proved files and global_tables.cpp) keep
// theirs. A few labels end with one more word after the entries (D_00262718: nine entries and a
// word; D_00262E40: 151 and a word; D_00275750: nine and a word): the next table's alignment on
// 8, so player.cpp defines D_00262E40 with its 151 entries. D_0026AA50 ends with two zero words
// that are not alignment (its 26 entries end on 8); object_gatherer.cpp defines it over its whole
// label, as a struct, so it is not declared here.
#ifndef OBJECT_LINK_H
#define OBJECT_LINK_H

#include "common.h"

struct ObjectLink {
    u32 flags;              // 0x00: 1, 4, 8, 0x10, 0x20 (above)
    u32 id;                 // 0x04: the id of the object to find
    u32 offset;             // 0x08: where in the object the found one goes
};

typedef char check_ObjectLink[sizeof(ObjectLink) == 0xC ? 1 : -1];

extern ObjectLink g_flaggedObjectLinks[];
extern ObjectLink g_stateNotifierLinks[];
extern ObjectLink g_gaugeManagerLinks[];
extern ObjectLink g_pooledObjectLinks[];
extern ObjectLink g_takerLinks[];
extern ObjectLink g_objectCyclerLoadLinks[];
extern ObjectLink g_objectCyclerStartLinks[];
extern ObjectLink g_partHolderLinks[];
extern ObjectLink g_currentPlacedObjectLinks[];
extern ObjectLink g_targetFollowerLoadLinks[];
extern ObjectLink g_targetFollowerResolveLinks[];
extern ObjectLink g_playerCharacterLinks[];
extern ObjectLink g_playerObjectLinks[];
extern ObjectLink g_modeColliderLinks[];
extern ObjectLink g_gaugeHolderLinks[];
extern ObjectLink g_countdownTable[];
extern ObjectLink g_modeWalkerLinks[];
extern ObjectLink g_pathSpeedColliderLinks[];
extern ObjectLink g_world2BossLoadLinks[];
extern ObjectLink g_world2BossStartLinks[];
extern ObjectLink g_contactListObjectLinks[];
extern ObjectLink D_00269B60[];
extern ObjectLink g_gaugeColliderLoadLinks[];
extern ObjectLink g_gaugeColliderStartLinks[];
extern ObjectLink g_gaugeCountedObjectLinks[];
extern ObjectLink g_stateWalkerObjectLoadLinks[];
extern ObjectLink g_stateWalkerObjectStartLinks[];
extern ObjectLink g_stateWalkerGroupLoadLinks[];
extern ObjectLink g_numberedItemLinks[];
extern ObjectLink g_objectGathererLoadLinks[];
extern ObjectLink g_objectGathererStartLinks[];
extern ObjectLink g_walkerColliderLoadLinks[];
extern ObjectLink g_walkerColliderStartLinks[];
extern ObjectLink g_pairedObjectLinks[];
extern ObjectLink g_hitTargetLoadLinks[];
extern ObjectLink g_hitTargetStartLinks[];
extern ObjectLink g_soundStateObjectLinks[];
extern ObjectLink g_objectCreatorLinks[];
extern ObjectLink g_timedGroupLinks[];
extern ObjectLink g_sequencedObjectLinks[];
extern ObjectLink g_hitCountColliderLinks[];
extern ObjectLink g_turningColliderLinks[];
extern ObjectLink g_agentLoadLinks[];
extern ObjectLink g_agentStartLinks[];
extern ObjectLink g_countedColliderLinkIds[];
extern ObjectLink g_pathFollowerLinks[];
extern ObjectLink g_tintBlendColliderLinks[];
extern ObjectLink g_playerLinkedColliderLinks[];
extern ObjectLink g_world1BossLinks[];
extern ObjectLink g_world3BeatPressLoadLinks[];
extern ObjectLink g_world3BeatPressStartLinks[];
extern ObjectLink g_world3BossStartLinks[];
extern ObjectLink g_warpPageLinks[];

#endif
