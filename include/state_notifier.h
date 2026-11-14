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
struct Camera;
struct ContactObject;
struct StateNotifier;


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
    f32 stateSince;         // 0x2D4: the clock when the state was set
    s32 initialMode;               // 0x2D8
    s32 f2DC;               // 0x2DC
    f32 f2E0;               // 0x2E0: i times D_00261B40 for the i-th scattered (func_00148AC0)
    u8 pad2E4[0x2E8 - 0x2E4];
    void* f2E8;             // 0x2E8: the object whose message ends it (func_00147EF8)
    void* f2EC;             // 0x2EC
    Vec02 v2F0;             // 0x2F0: pushed clear of what it overlaps (func_00146DB0)
    Vec02 v300;             // 0x300: its motion, split along the push (func_00146DB0)
    Vec02 v310;             // 0x310: the push (func_001478F0 sets it, func_00146518 adds it to the motion)
    union {
        f32 f320;           // 0x320
        s32 i320;
    };
    PlacedObject* f324;     // 0x324: where the splash goes when it crosses the camera's plane facing away
    PlacedObject* f328;     // 0x328: and facing it (func_00147428)
    s32 f32C;               // 0x32C: which side of the camera's plane it was last frame
    f32 f330;               // 0x330: the time of the last splash
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
    f32 f35C;               // 0x35C: an angle about v360, eased to 0 in state 4 (func_00146518)
    Vec02 v360;             // 0x360: its axis (func_001478F0)
    s32 f370;               // 0x370: set once state 4 has come to rest (func_00146518)
    union {
        u8 tail374[8];      // 0x374: copied unaligned by func_00146418
        StateNotifier* next374; // 0x374: the link in the world's list1C54 (func_001DCD28)
    };
    s32 f37C;               // 0x37C
    StateListener* listener;         // 0x380
    StateListener* f384;    // 0x384: told the whole units f38C counts in state 7 (func_00147428)
    f32 f388;               // 0x388
    f32 f38C;               // 0x38C: f388 per second, added up in state 7
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
void LoadStateNotifier(StateNotifier* self, void* arg);         // 0x55 slot 10
void CopyStateNotifier(StateNotifier* self, void* arg);          // 0x55 slot 9
void StartStateNotifier(StateNotifier* self);                       // 0x55 slot 16
s32 HandleStateNotifierContact(StateNotifier* self, ContactObject* b);           // 0x55 slot 45
void UpdateStateNotifier(StateNotifier* self, f32 dt);                     // 0x55 slot 17 (original assembly)
void SetStateNotifierState(Camera* self, s32 state);             // 0x55 slot 47
void InitTimeRangeNotifier(TimeRangeNotifier* self);                       // 0x58 slot 0
void HandleTimeRangeNotifierNotification(TimeRangeNotifier* self, s32 kind, void* target);
void UpdateTimeRangeNotifier(TimeRangeNotifier* self, f32 dt);
void SetEffectNotifierState(TimeRangeNotifier* self, s32 mode);
void InitSoundNotifier(SoundNotifier* self);
void SetSoundNotifierState(SoundNotifier* self, s32 mode);
void InitSaveNotifier(SaveNotifier* self);
void SetSaveNotifierState(SaveNotifier* self, s32 mode);
void InitDeadlineNotifier(DeadlineNotifier* self);
void StartDeadlineNotifier(DeadlineNotifier* self);
void HandleDeadlineNotifierNotification(DeadlineNotifier* self, s32 kind, void* msg);
void UpdateNotifierWorldDeadline(DeadlineNotifier* self, f32 dt);
void SetDeadlineNotifierState(DeadlineNotifier* self, s32 mode);
void InitCountdownNotifier(CountdownNotifier* self);
void HandleCountdownNotifierNotification(CountdownNotifier* self, s32 kind, void* msg);
void CountDownNotifierTimer(CountdownNotifier* self, f32 dt);
void SetCountdownNotifierState(CountdownNotifier* self, s32 mode);
void InitArmedStateNotifier(ArmedStateNotifier* self);

#endif
