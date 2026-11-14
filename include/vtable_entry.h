// SPDX-License-Identifier: AGPL-3.0-or-later
// The vtable entry record.
#ifndef VTABLE_ENTRY_H
#define VTABLE_ENTRY_H

#include "common.h"

struct VtableEntry { s32 delta; void (*fn)(); };

#endif
