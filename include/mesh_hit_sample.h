// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x30-byte hit CollectMeshHits gives (collider_contact.cpp's MeshHitEntry), as the camera's push-out
// and the player's probe read it: only the normal, at 0x10, is named.
#ifndef MESH_HIT_SAMPLE_H
#define MESH_HIT_SAMPLE_H

#include "common.h"
#include "placed_object.h"

struct MeshHitSample {
    u8 pad00[0x10];
    Vec02 normal;           // 0x10
    u8 pad20[0x10];
};

#endif
