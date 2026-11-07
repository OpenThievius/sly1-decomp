// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x69 (descriptor D_00221210, 0x350 bytes), a placed object (class 0x02) that makes
// itself the current one (D_0026FCF0) after loading. Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's 0x2D0 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef CURRENT_PLACED_OBJECT_H
#define CURRENT_PLACED_OBJECT_H

#include "placed_object.h"

struct StateTrigger;     // state_trigger.h
struct StateWalker;      // state_walker.h

// A state graph of the choice screen and the walker func_0016AB38 makes on it
// (func_001B6290): the walker moves to a choice's key (D_00262860).
struct ChoiceWalker {
    StateTrigger* graph;    // 0x00
    StateWalker* walker;    // 0x04
};

// An object func_0016AB38 can offer as the pending choice: one whose flag word (through
// 0x304) is clear; func_0016B580 chooses its state (func_001518B8).
struct ChoiceSequence {
    u8 pad[0x304];
    s32* flagp;             // 0x304
};

// 0x69: after loading (slot 16) it sets two bits of the parent's doubleword at 0x2C8, sets
// 0x2D0 to -1 and has its level call func_0016AB38 on it (func_001DBCC8). It is the level
// choice screen: func_0016B300 sets the choice, func_0016B0F8 moves it, func_0016B190
// confirms it, func_0016B580 runs it from the pad.
struct CurrentPlacedObject : PlacedObject {
    s32 choice;             // 0x2D0: the current choice (-1 after loading; func_0016B300)
    s32 keyIndex;           // 0x2D4: which key of the choice the walker goes to (1 once confirmed)
    f32 choiceTime;         // 0x2D8: the clock when the choice was set
    ChoiceWalker walkers[4]; // 0x2DC: walker 0 shows the choice, 3 the confirmed one
    s32 lastChoice;         // 0x2FC: the last choice open (func_0016AB38 counts down from 5)
    s32 walkerChoice;       // 0x300: the choice walkers 2 and 3 stand at
    u8 pad304[0x308 - 0x304];
    ChoiceSequence* pendingSequence; // 0x308: chosen at set-up, run once by func_0016B580
    u8 pad30C[0x310 - 0x30C];
    StateTrigger* levelObjects[5]; // 0x310: slot 2 of each open level's is called (func_0016AB38)
    void* choiceAnimations[6]; // 0x324: by choice, played when it is confirmed (func_0016B190)
    ChoiceSequence* sequences[4]; // 0x33C: the candidates for pendingSequence
    u8 pad34C[0x350 - 0x34C];
};

typedef char check_CurrentPlacedObject[sizeof(CurrentPlacedObject) == 0x350 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0016AED8(CurrentPlacedObject* self);                       // 0x69 slot 16

#endif
