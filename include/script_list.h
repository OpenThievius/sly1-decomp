// SPDX-License-Identifier: AGPL-3.0-or-later
// The script list builder and value filter.
#ifndef SCRIPT_LIST_H
#define SCRIPT_LIST_H

#include "common.h"

struct R11B008Node;
struct ScriptListBuilder { s32 type; R11B008Node* head; R11B008Node* tail; };
struct ScriptValueFilter { u32 type; R11B008Node* list; };

#endif
