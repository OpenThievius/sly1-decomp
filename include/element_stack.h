// SPDX-License-Identifier: AGPL-3.0-or-later
// The element stack, one object at D_00275BC0 to D_00275BF4 (g_elementStack): the menus push and pop
// screen elements on it, and the world load reads its resume state. Split out of screen_element.h so
// that the files that only set or test its state need not take the whole element header.
#ifndef ELEMENT_STACK_H
#define ELEMENT_STACK_H

#include "common.h"

struct ScreenElement;

// The stack of screen elements the menus push and pop (g_elementStack, D_00275BC0): its state
// (SetElementStackState), and the elements, whose top gets the pad each frame
// (UpdateElementStack, warp_menu.cpp).
struct ElementStack {
    u8 pad00[4];
    s32 state;              // 0x04: 0 .. 8 (SetElementStackState)
    f32 stateTime;          // 0x08: the clock when the state was set
    ScreenElement* items[8]; // 0x0C: items[count - 1] is the top
    s32 count;              // 0x2C: 1 for the base element alone
    s32 resumeState;        // 0x30: the state that state 3 stands for, -1 for 3 itself
};

// The one stack, D_00275BC0 to D_00275BF4, defined whole in warp_menu.cpp.
extern ElementStack g_elementStack;

#endif
