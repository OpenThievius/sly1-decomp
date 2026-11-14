// SPDX-License-Identifier: AGPL-3.0-or-later
// The game's list walk, as every file that walks a list shares it. Written for this project.
// A walk keeps a frame on the stack: the list, the slot holding the next element, the offset of
// the link inside an element, and the frame of the walk it interrupts. D_0027B314 points to the
// innermost frame; a walk pushes its frame there and pops it when done.
#ifndef LIST_ITER_H
#define LIST_ITER_H

#include "common.h"

struct ListFrame {
    void* list;
    u8* link;
    s32 offset;
    ListFrame* prev;
};

extern ListFrame* g_activeListFrames;

// The same frame as some walks keep it: four words, each pointer handled as an int.
struct WordListFrame {
    sptr list;
    sptr link;
    s32 offset;
    sptr prev;
};

#endif
