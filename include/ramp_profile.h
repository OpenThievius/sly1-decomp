// SPDX-License-Identifier: AGPL-3.0-or-later
// How ApproachValueWithRamp (func_001EA4B8) moves a value to a target: at most maxSpeed a
// second, slowing to endSpeed over the last rampTime seconds; func_001EA620 also limits the
// change of speed to maxAccel. The 16-byte records of .data (D_00275C18, D_00276278 ...) are
// read as these. Written for this project from what retail's code does.
#ifndef RAMP_PROFILE_H
#define RAMP_PROFILE_H

#include "common.h"

struct RampProfile {
    f32 maxSpeed;           // 0x00
    f32 endSpeed;           // 0x04: the speed at the target
    f32 rampTime;           // 0x08: the seconds it takes to slow from maxSpeed to endSpeed
    f32 maxAccel;           // 0x0C: 0 for none (func_001EA620)
};

#endif
