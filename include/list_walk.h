// SPDX-License-Identifier: AGPL-3.0-or-later
// The helpers that begin, step and scope a list walk (list_iter.h's frame), as the game's files
// write them: a walk's first step, its next element, and the walk as an object whose
// constructor pushes the frame and whose destructor pops it.
#ifndef LIST_WALK_H
#define LIST_WALK_H

#include "common.h"
#include "base_object.h"
#include "list_iter.h"

// Pushes a walk's frame (the statements in this order).
struct BeginListWalk {
    static void Of(ListFrame* it, ObjectList* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

struct ListWalkBegin {
    static void Of(ListFrame* it, ObjectList* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

// The next element as bytes.
struct ListWalkNext {
    static u8* Of(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

// The next element as an object.
struct ListWalkNextBase {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

// A walk as an object: the frame, pushed by the constructor and popped by the destructor.
struct ListWalk : ListFrame {
    ListWalk(ObjectList* l)
    {
        list = l;
        link = (u8*)l;
        offset = l->offset;
        prev = g_activeListFrames;
        g_activeListFrames = this;
    }
    ~ListWalk() { g_activeListFrames = prev; }
    // The list's first element, from the list's head.
    void* First()
    {
        void* n = *(void**)list;
        link = (u8*)n + offset;
        return n;
    }
    void* Next()
    {
        void* n = *(void**)link;
        link = (u8*)n + offset;
        return n;
    }
};

// A walk as a set of steps on a frame: begin, next element, end.
struct ListWalkSteps {
    static void Begin(ListFrame* it, ObjectList* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
    static u8* Next(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
    static void End(ListFrame* it) { g_activeListFrames = it->prev; }
};

// The same walk as a frame of its own: the list, the cursor, the link's offset and the walk it
// interrupts.
struct ScopedListFrame {
    void* list;
    void* cursor;
    s32 next_off;
    ScopedListFrame* prev;
    ScopedListFrame(ObjectList* l)
    {
        list = l;
        cursor = l;
        next_off = l->offset;
        prev = (ScopedListFrame*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ScopedListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

#endif
