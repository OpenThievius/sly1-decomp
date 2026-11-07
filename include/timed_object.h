// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x30 (descriptor D_0021AC38, 0x5D0 bytes), a collidable object with a small state machine
// (a state at +0x558, the time it was entered at +0x55C, a descriptor hook that picks the next
// state), and the three classes under it: 0x31 (D_0021AD80, 0xB10 bytes: a group of child
// objects), 0x32 (D_0021AEC8, 0x5F0 bytes) and 0x33 (D_0021B010, 0x620 bytes: three frame
// ranges and a blink). Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/timed_object.cpp).
//
// Their fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef TIMED_OBJECT_H
#define TIMED_OBJECT_H

#include "collider.h"

struct TimedObject;
struct StateTrigger;

// The track player func_00129CA8 returns (func_001AEF68 takes one): 0x18 holds a value that is given
// back as the record is cleared (a float read, then zeroed as an integer).
struct TrackPlayer {
    u8 pad00[0x18];
    union {
        s32 w;
        f32 f;
    } f18;                  // 0x18
};

// Class 0x30's descriptor: 0x03's slots, then six more (slot n at 0x10 + 4n; slot 72 is empty in
// 0x30).
struct Desc30 : Desc03 {
    void (*m48)(TimedObject* self, s32* state);     // 0x130: pick the next state (0x32: func_001B0C68)
    void (*m49)(TimedObject* self, s32 flag);       // 0x134: func_001B00E8, func_001B0EA8
    void (*m4A)(TimedObject* self);                 // 0x138: func_001B0120, func_001B0EE0
    void (*m4B)(TimedObject* self);                 // 0x13C: func_001B0160, func_001B0F70
    void (*m4C)(TimedObject* self, StateTrigger* trigger); // 0x140: slot 76, keep the trigger (func_001AECE0; func_001236C8)
    void (*m4D)(TimedObject* self, s32 state);      // 0x144: enter a state (func_001AECE8)
};

struct TimedObject : Collider {
    StateTrigger* trigger;  // 0x550: set by slot 76; slot 77 tells it when the state goes from 1 to 2
    s32 f554;               // 0x554: 0 at set-up
    s32 state;              // 0x558: -1 at set-up
    f32 f55C;               // 0x55C: the time the state was entered
    s32 f560;               // 0x560: the state slot 77 is called with when the object is set up
    Ids03 ids564;           // 0x564: object ids (func_001AF000)
    Ids03 ids578;           // 0x578: object ids (func_001AF028)
    Ids03 ids58C;           // 0x58C: class ids (func_001AF050)
    Ids03 ids5A0;           // 0x5A0: class ids (func_001AF078)
    s32 f5B4;               // 0x5B4: when set, every object is accepted (func_001AED78)
    f32 f5B8;               // 0x5B8
    f32 f5BC;               // 0x5BC
    s32 f5C0;               // 0x5C0
    void* f5C4;             // 0x5C4: a sound (func_001BFCD8 starts it, func_001BF788 stops it)
    TrackPlayer* f5C8;           // 0x5C8
    f32 f5CC;               // 0x5CC: the value kept out of f5C8's record

    const Desc30* desc30() const { return (const Desc30*)desc; }
};

// A group of 0x31: a child object and the objects it was cloned from the first group for.
struct TimedGroupEntry {
    BaseObject* obj;               // 0x00
    s32 value;              // 0x04
};

struct TimedGroupChild {
    BaseObject* child;             // 0x00
    f32 riseScale;          // 0x04: the scale of the group's ramp (func_001B0360)
    f32 fallScale;          // 0x08: the same in the falling states 3 and 7
    u8 pad0C[0x24 - 0x0C];
    s32 count;              // 0x24
    TimedGroupEntry items[5];       // 0x28
};

// 0x31: slot 9 (func_001AF3B8) clones the first group's entries into every other group; the
// objects are kept in the world's list at +0x1CA8 (link at 0xAF0).
struct TimedGroup : TimedObject {
    u8 pad5D0[0x5D4 - 0x5D0];
    s32 groupCount;         // 0x5D4
    u8 pad5D8[0x5E0 - 0x5D8];
    TimedGroupChild groups[16];     // 0x5E0
    u8 padAE0[0xAEC - 0xAE0];
    f32 fAEC;               // 0xAEC
    TimedGroup* listNext;          // 0xAF0: the link in the world's list at +0x1CA8
    u8 padAF4[0xAF8 - 0xAF4];
    s32 flagAF8;            // 0xAF8: 1 while it is in the list
    f32 fAFC;               // 0xAFC
    s32 fB00;               // 0xB00
    f32 fB04;               // 0xB04: 1.0 at set-up
    f32 fB08;               // 0xB08
    u8 padB0C[0xB10 - 0xB0C];
};

// 0x32: two object ids it resolves at load (D_002744D8: +0x5D0 and +0x5D4), a state of its own
// at +0x5D8 (func_001B1070) and three times.
struct SequencedObject : TimedObject {
    Collider* f5D0;              // 0x5D0
    s32 f5D4;               // 0x5D4
    s32 state5D8;           // 0x5D8: -1 at set-up
    f32 f5DC;               // 0x5DC: the time it was entered
    f32 f5E0;               // 0x5E0
    f32 f5E4;               // 0x5E4
    f32 f5E8;               // 0x5E8
    u8 pad5EC[0x5F0 - 0x5EC];
};

// A range of frames (func_001B1898): the first and the last, the time it takes, and how it
// loops (0 around, 1 back and forth).
struct FrameRange {
    s32 first;              // 0x00: -1 at set-up
    s32 last;               // 0x04: -1 at set-up
    f32 duration;           // 0x08
    s32 mode;               // 0x0C
};

struct BlinkObject : TimedObject {
    FrameRange animB;           // 0x5D0
    FrameRange animC;           // 0x5E0
    FrameRange animA;           // 0x5F0
    s32 blinkFrame;         // 0x600: -1 at set-up
    f32 blinkRate;          // 0x604
    f32 f608;               // 0x608
    f32 f60C;               // 0x60C
    Elem02* f610;           // 0x610: an entry of PlacedObject's list at 0x280 (a frame target for func_001B1898)
    f32 f614;               // 0x614
    s32 f618;               // 0x618
    u8 pad61C[0x620 - 0x61C];
};

typedef char check_Desc30[sizeof(Desc30) == 0x148 ? 1 : -1];
typedef char check_TimedObject[sizeof(TimedObject) == 0x5D0 ? 1 : -1];
typedef char check_TimedGroupChild[sizeof(TimedGroupChild) == 0x50 ? 1 : -1];
typedef char check_TimedGroup[sizeof(TimedGroup) == 0xB10 ? 1 : -1];
typedef char check_SequencedObject[sizeof(SequencedObject) == 0x5F0 ? 1 : -1];
typedef char check_FrameRange[sizeof(FrameRange) == 0x10 ? 1 : -1];
typedef char check_BlinkObject[sizeof(BlinkObject) == 0x620 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitTimedObject(TimedObject* self);                      // 0x30 slot 0
void UpdateTimedObject(TimedObject* self);                      // 0x30 slot 17
void SetTimedObjectTarget(TimedObject* self, s32 value);           // 0x30 slot 76
void EnterTimedObjectState(TimedObject* self, s32 state);           // 0x30 slot 77
void InitTimedGroup(TimedGroup* self);                      // 0x31 slot 0
void LoadTimedGroup(TimedGroup* self);                      // 0x31 slot 10
void CloneTimedGroupEntries(TimedGroup* self);                      // 0x31 slot 16
void UpdateTimedGroup(TimedGroup* self, f32 dt);              // 0x31 slot 17
void SetStaggeredColliderFrozen(TimedGroup* self, void* p);             // 0x31 slot 20
void SetTimedGroupMode(TimedGroup* self, s32 flag);            // 0x31 slot 73
void RequestTimedGroupEnd(TimedGroup* self);                      // 0x31 slot 74
void FinishTimedGroup(TimedGroup* self);                      // 0x31 slot 75
void EnterTimedGroupState(TimedGroup* self, s32 state);           // 0x31 slot 77
void InitSequencedObject(SequencedObject* self);                      // 0x32 slot 0
void SetupSequencedObject(SequencedObject* self);                      // 0x32 slot 16
void UpdateSequencedObject(SequencedObject* self);                      // 0x32 slot 17
s32 TestSequencedObjectMayContact();                                // 0x32 slot 56
void SetSequencedObjectMode(SequencedObject* self, s32 flag);            // 0x32 slot 73
void RequestSequencedObjectEnd(SequencedObject* self);                      // 0x32 slot 74
void FinishSequencedObject(SequencedObject* self);                      // 0x32 slot 75
void EnterSequencedObjectState(SequencedObject* self, s32 state);           // 0x32 slot 77
void InitBlinkObject(BlinkObject* self);                      // 0x33 slot 0
void SetupBlinkObject(BlinkObject* self);                      // 0x33 slot 16
void UpdateBlinkObject(BlinkObject* self);                      // 0x33 slot 17
void SetBlinkObjectMode(BlinkObject* self, s32 flag);            // 0x33 slot 73
void RequestBlinkObjectEnd(BlinkObject* self);                      // 0x33 slot 74
void FinishBlinkObject(BlinkObject* self);                      // 0x33 slot 75
void EnterBlinkObjectState(BlinkObject* self, s32 state);           // 0x33 slot 77

#endif
