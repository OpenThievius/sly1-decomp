// SPDX-License-Identifier: AGPL-3.0-or-later
// The delayed message body record.
#ifndef DELAYED_MESSAGE_BODY_H
#define DELAYED_MESSAGE_BODY_H

#include "common.h"

struct DelayedMessageBody { Quad16 q[5]; };
struct DelayedMessage { void* owner; u8 pad0[0xC]; DelayedMessageBody body; f32 due; };

#endif
