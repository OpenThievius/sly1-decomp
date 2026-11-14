// SPDX-License-Identifier: AGPL-3.0-or-later
// The cycler draw params record.
#ifndef CYCLER_DRAW_PARAMS_H
#define CYCLER_DRAW_PARAMS_H

#include "common.h"

struct CyclerDrawParams { u8 pad[0x40]; f32 scale; u8 pad2[0x10 - 4]; };

#endif
