// SPDX-License-Identifier: AGPL-3.0-or-later
// An object that holds a walker at 0x48, which the object found by id 0x42C gives the path
// followers and the world.
#ifndef WALKER_HOLDER_H
#define WALKER_HOLDER_H

#include "common.h"

struct WalkerHolder { u8 pad[0x48]; void* walker; };

#endif
