// SPDX-License-Identifier: AGPL-3.0-or-later
// The element stack's state word, the one SetElementStackState writes and the world load reads
// back to resume (g_elementStack, D_00275BC0, seen from the files that set and test it).
#ifndef ELEMENT_STACK_STATE_H
#define ELEMENT_STACK_STATE_H

#include "common.h"

struct ElementStackState { u8 pad0[0x30]; s32 resumeState; };

#endif
