// SPDX-License-Identifier: AGPL-3.0-or-later
// The pose record a collider's slot captures each frame (CaptureColliderPose, the path
// follower's and the player's captures), which the camera reads.
#ifndef COLLIDER_POSE_H
#define COLLIDER_POSE_H

#include "common.h"
#include "placed_object.h"

struct ColliderPose {
    s32 flags;              // 0x00: bit 0 set in the player's grounded states
    u8 pad04[0x10 - 0x04];
    Vec02 position;         // 0x10: where the camera looks
    Vec02 dir;              // 0x20: the path's direction times the speed along it
    f32 heading;            // 0x30: from the first row of the matrix
    f32 weight;             // 0x34: 100.0, or a weight scaled down by the spin or cleared
    f32 stampTime;          // 0x38: the time it was last stamped
    s32 f3C;                // 0x3C
};

#endif
