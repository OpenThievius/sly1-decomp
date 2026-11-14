// SPDX-License-Identifier: AGPL-3.0-or-later
// The gathered event object record.
#ifndef GATHERED_EVENT_OBJECT_H
#define GATHERED_EVENT_OBJECT_H

#include "common.h"

struct GatheredEventObject { u8 pad0[0x328]; s32 f328; };
struct GatheredObjects { s32 count; GatheredEventObject** items; };

#endif
