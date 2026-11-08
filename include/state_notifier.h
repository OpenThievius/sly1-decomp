// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x55 (descriptor D_0021C6C8, 0x390 bytes), an object that holds a state (+0x2D0) and
// changes it through its class's slot 47 (func_00147AB0), and the classes under it: 0x56, 0x59,
// 0x5A (0x390, no fields of their own) and 0x57, 0x58 (0x3A0, a timer and its two limits).
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Each class's fields follow its parent's and end at the size its descriptor gives; the pads keep
// every field at its retail offset. Class 0x55 sits under 0x02 (include/c02.h), whose fields and
// descriptor (Desc02: slot 47, 0xCC, sets the state) its methods use. Names may change at the
// naming step.
#ifndef STATE_NOTIFIER_H
#define STATE_NOTIFIER_H

#include "placed_object.h"

// A thing that takes a message in its class's slot 31 (0x10 + 4 * 31 = 0x8C).
struct StateListener {
    void (**vtbl)(StateListener* self, void* message);
};

struct StateNotifier;

// An object a message names whose flags (+0xC) func_001473E0 tests.
struct ContactObject {
    u8 pad0[0xC];
    s32 fC;
};

// 0x55: a state, a few movement numbers set by each subclass's constructor.
struct StateNotifier : PlacedObject {
    s32 state;              // 0x2D0
    u8 pad2D4[0x2D8 - 0x2D4];
    s32 initialMode;               // 0x2D8
    s32 f2DC;               // 0x2DC
    f32 f2E0;               // 0x2E0: i times D_00261B40 for the i-th scattered (func_00148AC0)
    u8 pad2E4[0x2E8 - 0x2E4];
    void* f2E8;             // 0x2E8: the object whose message ends it (func_00147EF8)
    void* f2EC;             // 0x2EC
    Vec02 v2F0;             // 0x2F0: pushed clear of what it overlaps (func_00146DB0)
    Vec02 v300;             // 0x300: its motion, split along the push (func_00146DB0)
    u8 pad310[0x320 - 0x310];
    union {
        f32 f320;           // 0x320
        s32 i320;
    };
    u8 pad324[0x334 - 0x324];
    s32 f334;               // 0x334: func_001DCD28 copies only one whose word is 0
    void* f338;             // 0x338
    s32 f33C;               // 0x33C: set once it has landed on a slope (func_00146DB0)
    s32 armed;               // 0x340
    f32 f344;               // 0x344
    union {
        f32 f348;           // 0x348
        s32 i348;
    };
    f32 f34C;               // 0x34C
    f32 f350;               // 0x350
    f32 f354;               // 0x354
    f32 f358;               // 0x358
    u8 pad35C[0x374 - 0x35C];
    union {
        u8 tail374[8];      // 0x374: copied unaligned by func_00146418
        StateNotifier* next374; // 0x374: the link in the world's list1C54 (func_001DCD28)
    };
    s32 f37C;               // 0x37C
    StateListener* listener;         // 0x380
    u8 pad384[0x388 - 0x384];
    f32 f388;               // 0x388
    u8 pad38C[0x390 - 0x38C];
};

struct SoundNotifier : StateNotifier {};
struct SaveNotifier : StateNotifier {};
struct DeadlineNotifier : StateNotifier {};
struct ArmedStateNotifier : StateNotifier {};

// 0x57 and 0x58: a timer (timeLeft) that counts down from a value chosen between two limits.
struct CountdownNotifier : StateNotifier {
    f32 timeMin;               // 0x390
    f32 timeMax;               // 0x394
    f32 timeLeft;               // 0x398
    u8 pad39C[0x3A0 - 0x39C];
};
struct TimeRangeNotifier : StateNotifier {
    f32 timeMin;               // 0x390
    f32 timeMax;               // 0x394
    f32 timeLeft;               // 0x398
    u8 pad39C[0x3A0 - 0x39C];
};

typedef char check_StateNotifier[sizeof(StateNotifier) == 0x390 ? 1 : -1];
typedef char check_SoundNotifier[sizeof(SoundNotifier) == 0x390 ? 1 : -1];
typedef char check_CountdownNotifier[sizeof(CountdownNotifier) == 0x3A0 ? 1 : -1];
typedef char check_TimeRangeNotifier[sizeof(TimeRangeNotifier) == 0x3A0 ? 1 : -1];
typedef char check_SaveNotifier[sizeof(SaveNotifier) == 0x390 ? 1 : -1];
typedef char check_DeadlineNotifier[sizeof(DeadlineNotifier) == 0x390 ? 1 : -1];
typedef char check_ArmedStateNotifier[sizeof(ArmedStateNotifier) == 0x390 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitStateNotifier(StateNotifier* self);                       // 0x55 slot 0
void LoadStateNotifier(StateNotifier* self, void* stream);         // 0x55 slot 10
void CopyStateNotifier(StateNotifier* self, void* other);          // 0x55 slot 9
void StartStateNotifier(StateNotifier* self);                       // 0x55 slot 16
s32 HandleStateNotifierContact(StateNotifier* self, ContactObject* other);           // 0x55 slot 45
void UpdateStateNotifier(StateNotifier* self);                       // 0x55 slot 17 (original assembly)
void SetStateNotifierState(StateNotifier* self, s32 mode);             // 0x55 slot 47
void InitTimeRangeNotifier(TimeRangeNotifier* self);                       // 0x58 slot 0
void HandleTimeRangeNotifierNotification(TimeRangeNotifier* self, s32 kind, void* target);
void UpdateTimeRangeNotifier(TimeRangeNotifier* self);
void SetEffectNotifierState(TimeRangeNotifier* self, s32 mode);
void InitSoundNotifier(SoundNotifier* self);
void SetSoundNotifierState(SoundNotifier* self, s32 mode);
void InitSaveNotifier(SaveNotifier* self);
void SetSaveNotifierState(SaveNotifier* self, s32 mode);
void InitDeadlineNotifier(DeadlineNotifier* self);
void StartDeadlineNotifier(DeadlineNotifier* self);
void HandleDeadlineNotifierNotification(DeadlineNotifier* self, s32 kind, void* msg);
void UpdateNotifierWorldDeadline(DeadlineNotifier* self);
void SetDeadlineNotifierState(DeadlineNotifier* self, s32 mode);
void InitCountdownNotifier(CountdownNotifier* self);
void HandleCountdownNotifierNotification(CountdownNotifier* self, s32 kind, void* msg);
void CountDownNotifierTimer(CountdownNotifier* self);
void SetCountdownNotifierState(CountdownNotifier* self, s32 mode);
void InitArmedStateNotifier(ArmedStateNotifier* self);

#endif
