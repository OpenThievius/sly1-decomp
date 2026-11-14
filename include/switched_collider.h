// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x05 (descriptor D_00217C30, 0x610 bytes) and the 24 classes under it: 0x06 (0x07,
// 0x08 with 0x09..0x13, 0x14), 0x15, 0x16, 0x17, 0x18, 0x19 (0x1A), 0x1B, 0x1C, 0x1D. Written
// for this project from what retail's code does (config/us/classes.tsv); one struct per class,
// named by class id until the naming step, each derived from its parent's with its fields at
// their retail offsets. Fields are named by offset where no reader shows more.
#ifndef SWITCHED_COLLIDER_H
#define SWITCHED_COLLIDER_H

#include "collider.h"

struct PointGraphObject;
struct BlendAnimationView;
struct SwitchedCollider;
struct TurningCollider;
// An object the player hit and the clock when (Player::hitStamps).
struct HitStamp {
    Collider* obj;          // 0x00
    f32 time;               // 0x04
};

struct Player;
struct ObjectMessage;    // object_message.h
struct World3BeatPressCollider;
struct Agent;
struct OnOffObject;     // an object of class 0x63 (c63.h)
struct PathCurveObject;   // path_curve_object.h
struct AimBlendGrid;      // aim_blend_grid.h
struct StateTrigger;      // state_trigger.h
struct StateWalker; // a handle func_001B6290 makes (s1b6290.h)
struct AnimationPlayer;  // an animation's player (t2195.h)
struct EntryQueue;       // class 0x8F (entry_queue.h)
struct World3Timeline;         // class 0x90 (world3_timeline.h)
struct PadRecord;        // pad_record.h

// 0x80 bytes at 0x580 of class 0x05, which class 0x17's slot 72 copies as one block: the data
// GetActiveSwitchedColliderData gives, D_00604700 when no collider is active. Its members are
// known only from the file's two brace initialisers (switched_collider.cpp): the vectors at 0x00
// and 0x70 are Quadratic16s (include/shapes.h: retail's initialiser has the CLOBBER of a union
// member before each one's first float); those at 0x20 and 0x50 have a first float too and no
// CLOBBER, so they are plain. The floats at 0x40 are zero in both; SpawnSurfaceContactEffects
// (effect_spawner.cpp) fills 0x44 and 0x48 with two angles, and its initialiser has a CLOBBER
// before them: one of the two is a union's member (either gives retail's code; 0x44 is kept).
struct Blk05 {
    Quadratic16 v00;        // 0x00
    Vec02 v10;              // 0x10
    Vec02 v20;              // 0x20
    Quad16 q30;             // 0x30: a vector copied whole (g_unitZVector in D_00269C10)
    f32 f40;                // 0x40
    union {
        f32 f44;            // 0x44
        u32 f44Bits;
    };
    f32 f48;                // 0x48
    s32 f4C;                // 0x4C
    Vec02 v50;              // 0x50
    Quad16 q60;             // 0x60: a vector copied whole (the zero vector in D_00604700)
    Quadratic16 v70;        // 0x70
};
typedef char check_Blk05[sizeof(Blk05) == 0x80 ? 1 : -1];

// Records of class 0x08: the targets at 0x758 and 0x870 (an id and the object it resolves
// to), the id groups at 0x7E8, the entries at 0xA7C.
struct Slot08 {
    s32 id;                 // 0x00
    void* obj;              // 0x04
};

struct Group08 {
    s32 ids[4];             // 0x00
};

struct Elem08 {
    s32 key;                // 0x00
    void* obj;              // 0x04
    s32 messageKind;        // 0x08: the kind of message sent to the part touching it
};

// An entry of class 0x1C's list at 0x634: a direction (0..3) and the time it is due.
struct Ent1C {
    s32 dir;                // 0x00
    f32 t;                  // 0x04
};

// A 0x100-byte record class 0x07 keeps twice (0x1190, 0x1290), one per object it holds.
struct Part07 {
    u8 pad00[0x50];
    s32 valid;              // 0x50: cleared by func_00172530 when the object is missing; func_001C4790 needs it set
    u8 pad54[0x60 - 0x54];
    Vec02 pointA;           // 0x60: the two points func_001C4790 queries a collider's spans between
    Vec02 pointB;           // 0x70: the second point of the span query
    f32 distance;           // 0x80: the distance func_001C4618 measures between the two points
    u8 pad84[0x90 - 0x84];
    ColliderSpan span;      // 0x90: the nearest span found (func_001C4790)
};

// One of class 0x17's six groups at 0x658: count keys, the n objects they resolve to (slot 16),
// and the one picked at random.
struct Ent17 {
    s32 count;              // 0x00
    s32 keys[4];            // 0x04
    s32 n;                  // 0x14
    void* list[4];          // 0x18
    s32 pick;               // 0x28
};

// A message class 0x07's slot 75 keeps (+0x26B4): its kind, an argument, and a callback with
// its data that slot 75 calls once.
struct Ev07 {
    s32 kind;               // 0x00
    s32 arg;                // 0x04
    s32 data;               // 0x08
    s32 fn;                 // 0x0C
};

// One of class 0x19's four slots at 0x6B0: an object and a position.
struct Slot19 {
    PlacedObject* obj;      // 0x00: linked by id (D_002752A0); its position is copied to v10 at start
    PlacedObject* obj2;     // 0x04: the object a second link gives (func_001DA7E0 places it with this one)
    PlacedObject* obj8;     // 0x08: the object its start is taken from (func_001DA320)
    s32 contactStamp;       // 0x0C: compared with PathFollower::contactStamp (func_001DA7E0)
    Vec02 placedPos;        // 0x10: the position the object is placed at
    Vec02 contactPoint;     // 0x20: the contact point
    Vec02 contactDirection; // 0x30: the direction at the contact
    Vec02 contactVelocity;  // 0x40: the motion at the contact point
    f32 turnRate;           // 0x50: f698 over f610 (slots 0, 1) or f614 (func_001D8D90)
    f32 turnAngle;          // 0x54: an angle f50 advances by the clock's step (func_001DA7E0)
    f32 firstEmitterOwed;   // 0x58: the particles owed to the first emitter, spent whole (func_001D8E40)
    f32 secondEmitterOwed;  // 0x5C: the same for the second
};

// A marker on class 0x19's path (sixteen at 0x874): an object (kind 0, func_001DB110) or a
// point (kind 1, func_001DB1E8). The object markers form a ring through next, numbered in
// order from the first (0xAF4); their place on the path is the arc length the path's curve
// gives (PathCurveVt::m10).
struct PathMarker {
    s32 kind;               // 0x00: 0 an object, 1 a point
    void* item;             // 0x04: the object (the point's id for kind 1)
    u8 pad08[0x0C - 0x08];
    s32 index;              // 0x0C: one more than the marker before it in the ring
    f32 pathLength;         // 0x10: the arc length of its place on the path
    PathMarker* next;       // 0x14
    f32 x;                  // 0x18: a point's two values
    f32 y;                  // 0x1C
    s32 b;                  // 0x20
    s32 c;                  // 0x24
};

// An entry of class 0x08's second queue at 0xAC8 (func_001CA720 adds one, func_001CA7C0
// resolves its id into obj).
struct Pend08 {
    s32 mask;               // 0x00: the message mask the entry answers to
    s32 id;                 // 0x04: -1 once resolved
    void* obj;              // 0x08
};

// Class 0x10's doubleword at 0xC10, which its slot 9 keeps across the copy as an unaligned
// doubleword.
struct __attribute__((packed)) Pack10 {
    u64 value;              // 0x00
};

// Class 0x05's descriptor: 0x03's slots, then twelve more (slot n at 0x10 + 4n).
struct Desc05 : Desc03 {
    void (*m48)(SwitchedCollider* self, s32 mode);               // 0x130: slot 72 (func_001922E8)
    void (*m49)(SwitchedCollider* self, f32 dt, PadRecord* pad);   // 0x134: slot 73: the pad each frame while it is the active one (func_001E9C78)
    s32 (*m4A)(SwitchedCollider* self);                          // 0x138: slot 74 (func_00192410)
    s32 (*m4B)(SwitchedCollider* self, s32 a);                   // 0x13C: slot 75 (func_00192450, class 0x08: func_001C9A48)
    s32 (*m4C)(SwitchedCollider* self, void* arg);               // 0x140: slot 76 (func_00192488, class 0x08: func_001C9990)
    s32 (*m4D)(SwitchedCollider* self);                          // 0x144: slot 77 (func_00192490)
    void (*m4E)(SwitchedCollider* self, s32 mode, PlacedObject* other);   // 0x148: slot 78 (func_001924C8)
    void (*m4F)(SwitchedCollider* self, s32 state);              // 0x14C: slot 79 (func_001925C0)
    void (*m50)(SwitchedCollider* self);                         // 0x150: slot 80 (func_00192C58)
    void* m51;                                      // 0x154: slot 81 (func_00192A28)
    void* m52;                                      // 0x158: slot 82 (func_00192A38)
    SwitchedCollider* (*m53)(SwitchedCollider* self);           // 0x15C: slot 83 (func_001930B0): the collider it stands for, or 0
};

// Class 0x06's descriptor (also 0x07's and 0x14's): four more slots.
struct Desc06 : Desc05 {
    void (*m54)(TurningCollider* self);             // 0x160: slot 84, the matrix from the heading (class 0x06: func_001C53B0)
    s32 (*m55)(TurningCollider* self);                          // 0x164: slot 85 (class 0x06: func_001C4F00)
    void* m56;                                      // 0x168: slot 86 (class 0x06: func_001C5248)
    s32 (*m57)(Agent* self);                          // 0x16C: slot 87 (class 0x08: func_001CB3C8)
};

// Class 0x08's descriptor (and its subclasses'): twelve more slots.
struct Desc08 : Desc06 {
    s32 (*m58)(Agent* self);                          // 0x170: slot 88 (class 0x08: func_001CA460)
    s32 (*m59)(Agent* self);                          // 0x174: slot 89 (class 0x08: func_001C8010)
    void* m5A;                                      // 0x178: slot 90 (class 0x08: func_001C8E28)
    void (*m5B)(Agent* self, s32 state, void* context);   // 0x17C: slot 91 (class 0x08: func_001C9008)
    void (*m5C)(Agent* self, s32 old, void* context);     // 0x180: slot 92 (class 0x08: func_001C91C8)
    s32 (*m5D)(Agent* self);                          // 0x184: slot 93 (class 0x08: func_001CA468)
    void (*m5E)(Agent* self, s32 on);                 // 0x188: slot 94 (class 0x08: func_001C8C08)
    void* m5F;                                      // 0x18C: slot 95 (class 0x08: func_001C8590)
    void* m60;                                      // 0x190: slot 96 (class 0x08: func_001C9CF8)
    void* m61;                                      // 0x194: slot 97 (class 0x08: func_001C9AF8)
    void* (*m62)(Agent* self);                        // 0x198: slot 98 (class 0x08: func_001CAA08)
    void* m63;                                      // 0x19C: slot 99
};

struct SwitchedCollider : Collider {
    s32 enabled;            // 0x550: on (func_00192990 calls func_001926D0, off func_00192780); set by slots 0 and 9
    s32 holdFocus;          // 0x554: slot 69 keeps v560 while it is set
    u8 pad558[0x560 - 0x558];
    Vec02 focusPoint;       // 0x560: v140 kept by slot 72; slot 69 reads its z
    u8 pad570[0x574 - 0x570];
    void* playingSound;     // 0x574: given to func_001BF788 by slot 13 (kind 0xB)
    union {
        Blk05 blk580;       // 0x580: copied whole by class 0x17 (func_0019A520)
        struct {
            s32 f580;       // 0x580: 1 at set-up
            void* f584;     // 0x584: an object (class 0x16: func_0015A418 0x160)
            void* f588[3];  // 0x588: objects (class 0x16: 0x161..0x163); slot 17 starts one
            f32 f594;       // 0x594: 300.0 in class 0x16
            void* f598;     // 0x598: itself at set-up
            s32 f59C;       // 0x59C: given to the node slot 78 makes
            u8 pad5A0[0x5AC - 0x5A0];
            void* effects[9]; // 0x5AC: f5D0 of them (slot 78 makes the first; slot 13 forgets one)
            s32 effectCount; // 0x5D0: how many entries effects holds
            u8 pad5D4[0x5F0 - 0x5D4];
            void* f5F0;     // 0x5F0: an object slot 78 reads (func_0012CCC0)
            u8 pad5F4[0x600 - 0x5F4];
        };
    };
    s32 f600;               // 0x600: slot 17 calls func_00192DD0 in 1 and 3
    PlacedObject* f604;              // 0x604: an object slot 80 moves into place
    u8 pad608[0x610 - 0x608];

    const Desc05* desc05() const { return (const Desc05*)desc; }
};

struct TurningCollider : SwitchedCollider {
    void* f610;             // 0x610
    void* f614;             // 0x614
    void* f618;             // 0x618
    void* f61C;             // 0x61C
    void* f620;             // 0x620
    void* f624;             // 0x624
    EntryQueue* f628;       // 0x628: the entry queue it binds to the player (func_001EB748)
    void* f62C;             // 0x62C
    f32 stickHeading;       // 0x630: the heading the stick asks for
    f32 stickLevel;         // 0x634: the stick's push level
    f32 heading;            // 0x638: the facing angle about z
    f32 headingWeight;      // 0x63C: how much the heading steers its contacts, 0 to 1
    union {
        void* f640;         // 0x640
        Vec02 headingVelocity; // 0x640: class 0x14 sets it from D_00248D30 (func_001DFBE0)
    };
    f32 cameraHeight;       // 0x650: the camera's height for the player (func_00172EE0)
    u8 pad654[0x660 - 0x654];
    Mat02 headingMatrix;    // 0x660: the identity at set-up (slot 16); slot 84 hands it on

    s32 groundContact;      // 0x690: set while a ground contact is held
    f32 groundContactTime;  // 0x694: the clock when the ground contact was found
    f32 f698;               // 0x698
    u8 pad69C[0x6A0 - 0x69C];
    Vec02 groundContactPoint; // 0x6A0
    Vec02 groundContactNormal; // 0x6B0
    void* groundContactPart; // 0x6C0
    f32 stepPhase;          // 0x6C4
    f32 f6C8;               // 0x6C8
    f32 probeDepth;         // 0x6CC: how far below the lowest vertex the probe vertex is put
    s32 probeIndex;         // 0x6D0: the index of the mesh's last vertex (func_001C4FF8)
    s32 probeVertex;        // 0x6D4: the probe vertex in the mesh copy
    Vec02* lowestVertex;    // 0x6D8: the lowest vertex of the mesh copy (func_001C4FF8); compared with Contact03::featureEnd0 by the player (func_00170820)
    void* followedMesh;     // 0x6DC: the mesh it follows
    f32 turnGain;           // 0x6E0: the first of three turn gains
    f32 f6E4;               // 0x6E4
    f32 f6E8;               // 0x6E8
    u8 pad6EC[0x6F0 - 0x6EC];
    Vec02 headingWeightCurve; // 0x6F0
    f32 gravityScale;       // 0x700
    s32 sinkRamp[3];        // 0x704
    s32 restRamp[3];        // 0x710
    u8 pad71C[0x720 - 0x71C];

    const Desc06* desc06() const { return (const Desc06*)desc; }
};

// An entry of the player's two-entry path blend (+0x103C): its weight, its animation and the
// speed it plays at (CreatePlayerTwoEntryBlend, ControlPlayerOnPath).
struct PlayerBlendEntry {
    f32 weight;             // 0x00
    void* anim;             // 0x04
    u8 pad08[4];
    f32 speed;              // 0x0C
};

struct Player : TurningCollider {
    u8 pad720[0x900 - 0x720];
    BlendAnimationView* sixWayBlend; // 0x900: the blend of state 1, six entries
    u8 pad904[0xA10 - 0x904];
    BlendAnimationView* eightWayBlend; // 0xA10: the blend of state 5, eight entries
    s32 eightWayHalf;       // 0xA14: -1, 0 or 1: which three of the blend slots take the weights (func_001D4348)
    u8 padA18[0x1018 - 0xA18];
    void* aimAnim10;        // 0x1018: the animation of aim state 10 (func_001C61E0)
    void* aimAnim11;        // 0x101C: that of aim state 11
    u8 pad1020[0x103C - 0x1020];
    union {
        u8 f103C[0x20];     // 0x103C
        PlayerBlendEntry blend103C[2];  // 0x103C: the two entries of the path blend (ControlPlayerOnPath)
    };
    void* f105C;            // 0x105C: the blend item BuildCombinedBlendAnimation makes of blend103C
    u8 pad1060[0x1064 - 0x1060];
    void* f1064;            // 0x1064
    u8 pad1068[0x106C - 0x1068];
    f32 pathLeanRight;      // 0x106C: the three weights func_00171238 gives SetBlendItemWeights, 0xC apart
    u8 pad1070[0x1078 - 0x1070];
    f32 pathLeanCentre;     // 0x1078: the weight of no lean
    u8 pad107C[0x1084 - 0x107C];
    f32 pathLeanLeft;       // 0x1084: the weight of the negative lean
    u8 pad1088[0x1090 - 0x1088];
    void* pathLeanBlend;    // 0x1090: the blend those weights go to
    f32 pathLean;           // 0x1094: eased toward the side the path turns to (func_00171238)
    f32 pathLeanRate;       // 0x1098: its rate
    void* subStateAnims[59]; // 0x109C: the animation of each sub-state (+0x2228), by its number (SetPlayerState)
    void* stateGraph;       // 0x1188: the state graph the player's walker runs
    s32 f118C;              // 0x118C
    Part07 f1190;           // 0x1190: given to func_001C4848/func_001C4618 with f610 (slot 37)
    Part07 f1290;           // 0x1290: the same with f614
    void* stateNodes[0x11]; // 0x1390: the animation node of each state (func_00174F50)
    void* targetModeNodes[0x11]; // 0x13D4: those of state 6, by +0x239C
    void* subStateNodes[0x15]; // 0x1418: those of state 4, by sub-state
    void* specialNode;      // 0x146C: the node of state 6's special cases
    u8 pad1470[0x1504 - 0x1470];
    void* f1504;            // 0x1504
    void* f1508[4];         // 0x1508
    void* f1518;            // 0x1518
    u8 contactChainHead[4]; // 0x151C: given to func_001BC4D8
    u8 trail[0x21C0 - 0x1520];  // 0x1520: a record func_001C29E8 and func_001C3028 work on
    s32 trailEnabled;       // 0x21C0: set, the trail ribbon is drawn
    AimBlendGrid* aimGrid;  // 0x21C4: the aim grid TrackAimTargetObject and TrackAimTargetPoint blend
    f32 f21C8;              // 0x21C8
    s32 boundsPointCount;   // 0x21CC: how many points boundsPoints holds
    Vec02 boundsPoints[3];  // 0x21D0: the points the player's bounds are expanded over
    void* aimTarget;        // 0x2200: the object aimed at
    BaseObject* boundObject; // 0x2204: the object aimed at (player_target.cpp)
    s32 aimCurve;           // 0x2208: the curve object aimed at or ridden
    f32 aimCurvePos;        // 0x220C: the time along the aim path (TrackAimTargetPoint)
    BaseObject* previousBoundObject; // 0x2210: the last f2204; cleared by aim state 0 (func_001C61E0)
    s32 previousAimCurve;   // 0x2214: the same
    u8 pad2218[0x221C - 0x2218];
    s32 pathFlipped;        // 0x221C: set, the path's frame is turned about (func_001D1630)
    s32 state;              // 0x2220: the player's state, 0..16
    f32 stateStartTime;     // 0x2224: the time the state was entered
    s32 subState;           // 0x2228: the sub-state within the state
    f32 subStateStartTime;  // 0x222C: the time the sub-state was entered
    ObjectMessage* stateAnimPlayer; // 0x2230: the message whose object set it lets go of (func_00198EF8)
    void* stateWalker;      // 0x2234: the player's state walker
    u8 pad2238[0x223C - 0x2238];
    s32 aimMode;            // 0x223C: the aim mode, -1 or 0..11
    f32 aimStartTime;       // 0x2240: a time, compared with the clock while f223C is 4..7 (func_001CAF38)
    void* aimAnimPlayer;    // 0x2244: the aim's animation player (func_001C61E0 replaces it)
    s32 f2248;              // 0x2248
    s32 jumpKind;           // 0x224C: which jump the player makes (-1 none, 0..4)
    s32 f2250;              // 0x2250
    s32 pendingFlags;       // 0x2254: which deferred changes ApplyPendingPlayerStateRequest carries out
    s32 pendingState;       // 0x2258: the state of a pending change
    s32 pendingSubState;    // 0x225C: the sub-state of a pending change
    s32 pendingAimMode;     // 0x2260: the aim mode of a pending change
    s32 pendingJumpKind;    // 0x2264: the jump kind a pending change sets
    s32 steerKeepsDirection; // 0x2268: set, the steer keeps its direction (func_0017D5D8)
    f32 jumpSpeed;          // 0x226C: the horizontal speed of the jump
    s32 jumpStickPhase;     // 0x2270: where the jump's stick hold is: 0 waiting, 1 held full, 2 released, 3 none
    f32 jumpStartTime;      // 0x2274: the time the jump started
    f32 stickFullTime;      // 0x2278: the time the stick reached full during the jump
    f32 stickReleaseTime;   // 0x227C: the time the stick came off full during the jump
    u8 pad2280[0x2284 - 0x2280];
    f32 f2284;              // 0x2284
    u8 pad2288[0x2290 - 0x2288];
    Vec02 v2290;            // 0x2290: the steer direction func_0017D5D8 keeps
    f32 linkPushTime;       // 0x22A0: the time the stick last pushed along or against the link (func_001CD0C8)
    s32 linkReturnState;    // 0x22A4: the link state to go back to, -1 for none (func_001CD0C8)
    s32 linkReversed;       // 0x22A8: set when the link's heading is turned round (func_001CD0C8)
    void* linkSystem;       // 0x22AC: the link system the player is hanging on
    Vec02 linkAcceleration; // 0x22B0: the link's acceleration (func_001CC818, or SolvePlayerLinkSystem)
    u8 pad22C0[0x2360 - 0x22C0];
    f32 linkTowardWeight;   // 0x2360: the three weights func_001CD0C8 gives SetBlendItemWeights, 0xC apart
    u8 pad2364[0x236C - 0x2364];
    f32 linkAwayWeight;     // 0x236C: the blend weight of the away animation
    u8 pad2370[0x2378 - 0x2370];
    f32 linkIdleWeight;     // 0x2378: the blend weight of the idle animation
    u8 pad237C[0x2384 - 0x237C];
    void* linkBlend;        // 0x2384: the blend those weights go to
    f32 linkTowardRamp;     // 0x2388: ramped to 0 or 1 by the link state (func_001CD0C8)
    f32 linkMoveRamp;       // 0x238C: the same
    u8 pad2390[0x239C - 0x2390];
    s32 targetMode;         // 0x239C: what the player is bound to: 0 curve, 1 point, 2 part, 6 object or vector, 7 switch
    void* targetCurve;      // 0x23A0: the object the player is pushed along (func_001733B8); its +0x54 set keeps an agent from facing the player (func_001CB3D0)
    f32 targetCurvePos;     // 0x23A4: the player's place along targetCurve
    void* targetPoint;      // 0x23A8: its +0x6C set does the same (func_001CB3D0)
    f32 targetPointPlace;   // 0x23AC: the place on the point at 0x23A8 (func_0017F018)
    void* heldObject;       // 0x23B0: the object the player holds (PrunePlayerContacts, TestListedCollisionPartMayContact)
    void* leapTarget;       // 0x23B4: the point object the player leaps to (func_0017D5D8)
    void* targetNode;       // 0x23B8: the node object it is bound to
    void* targetTrack;      // 0x23BC: the track record it is bound to
    f32 trackPos;           // 0x23C0: the place along the record at 0x23BC (DrivePlayerFromEntryQueue)
    f32 f23C4;              // 0x23C4: added to f23C0 with the speed along the record (func_00171238)
    s32 trackReversed;      // 0x23C8: set, the turn is the other way (func_00171238)
    void* targetSwitch;     // 0x23CC: the class 0x17 object that set state 7 (func_0019AB78)
    void* f23D0;            // 0x23D0: an object whose slots 6, 7 and 35 the aim states 2 and 11 swap with f23D8 (func_001C61E0)
    void* f23D4;            // 0x23D4
    void* f23D8;            // 0x23D8: the other of the pair
    u8 pad23DC[0x23E0 - 0x23DC];
    f32 f23E0;              // 0x23E0
    f32 f23E4;              // 0x23E4
    u8 pad23E8[0x23F0 - 0x23E8];
    f32 f23F0;              // 0x23F0
    f32 f23F4;              // 0x23F4
    u8 pad23F8[0x2400 - 0x23F8];
    Vec02 pathPoseOffset;   // 0x2400: eased toward zero each frame on the path (ControlPlayerOnPath)
    f32 pathPos;            // 0x2410: the length along the path (func_001D1A80)
    f32 pathSpeed;          // 0x2414: the speed along it (func_00172EE0 scales the path's direction by it)
    f32 pathSpeedEased;     // 0x2418: the eased speed the path's turn checks read (ControlPlayerOnPath)
    s32 pathStickSide;      // 0x241C: -1, 0 or 1: which way the stick holds the player on the path
    f32 boundsRadius;       // 0x2420: the radius the bounds are expanded by around each point
    f32 aimEndTime;         // 0x2424: the clock time the aim mode ends
    u8 pad2428[0x242C - 0x2428];
    f32 spinTargetRate;     // 0x242C: the angular rate the spin approaches
    f32 spinRate;           // 0x2430: the angular rate
    f32 spinAngle;          // 0x2434: the spin angle
    Collider* f2438;        // 0x2438: the object it is aimed at (func_001D66A8)
    u8 pad243C[0x2440 - 0x243C];
    Vec4U phaseSoundStates[5]; // 0x2440: D_002636A0 to D_002636E0 at set-up, copied whole (InitPlayer)
    u8 pad2490[0x2498 - 0x2490];
    s32 f2498;              // 0x2498
    u8 pad249C[0x24A0 - 0x249C];
    void* ledgeCollider;    // 0x24A0: the collider whose ledge the player holds
    u8 pad24A4[0x24B0 - 0x24A4];
    u8 ledgeLocalPoint[0x10]; // 0x24B0: filled by func_00128018 (func_00172898)
    Vec02 ledgeOffset;      // 0x24C0: the offset ComputeLedgeOffsetForContact gives
    Vec02 ledgeSlack;       // 0x24D0: the difference that is eased back to zero
    Vec02 ledgeHandOffset;  // 0x24E0: the offset subtracted after rotating by the pose matrix
    s32 ledgeKind;          // 0x24F0: handed to func_0017E088 with f24F4 (UpdatePlayer)
    s32 ledgeKey;           // 0x24F4: the key of the ledge contact
    PlacedObject* rigObject; // 0x24F8: the object of link id 0x60 (D_00262E40); func_00175078 calls its slot 43
    u8 pad24FC[0x2500 - 0x24FC];
    void* f2500;            // 0x2500: five parts whose byte at +0x10 func_00175078 sets to 9 or -1
    void* f2504;            // 0x2504
    void* f2508;            // 0x2508
    void* footPartA;        // 0x250C: also given to func_001719E8 and func_00171C80 with f1190
    void* footPartB;        // 0x2510: the same with f1290
    void* selfPoseSource;   // 0x2514: the player's own pose source
    void* rigPoseSource;    // 0x2518: the pose source on rigObject
    u8 pad251C[0x2530 - 0x251C];
    Vec02 poseOffset;       // 0x2530: an offset of the pose eased to zero (func_00172EE0)
    u8 aimBlend4[0x18];     // 0x2540: the blend set up for aim state 4 (func_001C6D00), with its animation
    void* aimAnim4;         // 0x2558: the animation of aim mode 4
    u8 aimBlend5[0x18];     // 0x255C: state 5's
    void* aimAnim5;         // 0x2574: the animation of aim mode 5
    u8 aimBlend6[0x18];     // 0x2578: state 6's
    s32 aimAnim6;           // 0x2590: the animation of aim mode 6
    u8 aimBlend7[0x18];     // 0x2594: state 7's
    s32 aimAnim7;           // 0x25AC: the animation of aim mode 7
    void* aimAnim8;         // 0x25B0: the animation of aim state 8 (func_001C61E0)
    void* aimAnim9;         // 0x25B4: that of aim state 9
    u8 pad25B8[0x25C8 - 0x25B8];
    void* markerAnim;       // 0x25C8: the animation whose markers state 8 reads (func_0017D248) and whose marker 0x1BB func_0017F018 reads
    s32 f25CC;              // 0x25CC: ControlPlayer (func_00173888) holds state 12's step 0x21 while it is set
    s32 f25D0;              // 0x25D0: the same for step 0x23
    u8 pad25D4[0x25D8 - 0x25D4];
    void* f25D8[5];         // 0x25D8
    s32 foundNodeCount;     // 0x25EC: the number of f25F0 entries (func_00177990 adds up to 32); cleared by aim states 3 to 7 (func_001C61E0)
    PlacedObject* foundNodes[32]; // 0x25F0: the nodes func_00177990 found, which FindNodeForQuery skips
    Contact03* queryContacts; // 0x2670: contacts func_00177990 reads, then gives back to the world's pool
    s32 forcedOnOffObject;  // 0x2674: func_001D1200 compares it with f2678
    OnOffObject* ownOnOffObject;    // 0x2678: the record func_001D1260 fills
    u8 pad267C[0x2680 - 0x267C];
    f32 f2680;              // 0x2680: the last time the pose was stamped (func_00172EE0)
    s32 onOffPhase;         // 0x2684: the on/off phase
    f32 onOffPhaseTime;     // 0x2688: the time the phase was set
    s32 f268C;              // 0x268C
    Vec02 v2690;            // 0x2690
    s32 f26A0;              // 0x26A0
    u8 pad26A4[0x26A8 - 0x26A4];
    s32 ringCount;          // 0x26A8: the number of ring entries
    void* ringAnchors;      // 0x26AC: the ring's anchor table
    union {
        s32 f26B0;          // 0x26B0: set by func_001D4C90 (a function's address, or 0)
        void (*cb26B0)(Player* self);  // 0x26B0: called once by func_001D4C98
    };
    Ev07 lastMessage;       // 0x26B4: the last message slot 75 took (func_001D4D08)
    s32 pulseActive;        // 0x26C4: set while the marker pulses
    f32 pulseStartTime;     // 0x26C8: the time the pulse began
    f32 pulseFadeStart;     // 0x26CC: the time the pulse's fade began
    f32 pulseFadeDuration;  // 0x26D0: how long the fade lasts
    void* walkerHost;       // 0x26D4: the object that sent the player to state 9 (func_00178068)
    HitStamp hitStamps[8];  // 0x26D8: the objects func_001D66A8 hit and when

    s32 padSelectMode;      // 0x2718: -1, or a mode that holds the pad-select flag (func_001D27C0)
    u8 pad271C[0x2724 - 0x271C];
    f32 f2724;              // 0x2724: 1.0 at set-up (InitPlayer)
    f32 f2728;              // 0x2728: 1.0 at set-up
    u8 pad272C[0x2730 - 0x272C];
    s32 f2730;              // 0x2730
    f32 f2734;              // 0x2734: the time state 4 last took the pad's 0x40 press (ControlPlayer)
    s32 f2738;              // 0x2738: set, ControlPlayer runs the player's callback within D_00263910 of it
    void* f273C;            // 0x273C: the hook (+0x3C8) put aside on entering state 13, given back on leaving it (func_00175170)
    EntryQueue* entryQueue; // 0x2740: the entry queue that drives it (func_0017CE20, func_0017CE80)
    s32 slowDownHeld;       // 0x2744: mode 2's slow-down held (func_001D2BB8)
    f32 speedUpAmount;      // 0x2748: mode 4's speed-up, 1 while held, eased back to 0 (func_001D2BB8)
    u8 pad274C[0x2750 - 0x274C];
    void* contactOwner;     // 0x2750: the object the player hands its contacts to
    u8 pad2754[0x2758 - 0x2754];
    f32 animSeekTime;       // 0x2758: the time of that seek
    s32 animSeekValue;      // 0x275C: 0 or 1: where the object animations were last sought
    u8 pad2760[0x2768 - 0x2760];
    s32 f2768;              // 0x2768
    u8 pad276C[0x2770 - 0x276C];
    u8 f2770[0x20];         // 0x2770
    u8 pad2790[0x2B70 - 0x2790];
    union {
        Vec02 contactQuads[2]; // 0x2B70: the two quads func_00178598 copies from what func_001782C0 takes
        struct {
            void* touchedObject; // 0x2B70: the object it touches (func_001D4A98, func_001D51A0)
            s32 f2B74;      // 0x2B74
            s32 f2B78;      // 0x2B78
            s32 f2B7C;      // 0x2B7C
            s32 f2B80;      // 0x2B80
            s32 f2B84;      // 0x2B84
            s32 f2B88;      // 0x2B88
            s32 f2B8C;      // 0x2B8C
        };
    };
    u8 pad2B90[0x2BB0 - 0x2B90];
    Vec02 savedVelocity;    // 0x2BB0: the velocity put aside by a request
    Vec02 savedSpin;        // 0x2BC0: the spin put aside by a request
    void* pendingCaption;   // 0x2BD0: the caption element waiting to be shown
    s32 f2BD4;              // 0x2BD4: ControlPlayer's step-sequence skip reads it with the pad's 0xC bits
    s32 probeContactsDisabled; // 0x2BD8: set, the player adds no probe contacts
    void* penalizedTarget;  // 0x2BDC: AddRepeatTargetPenalty adds a cost to this candidate
    void* walkerActivation; // 0x2BE0: QueuePlayerWalkerActivation, taken by RunPlayerQueuedActivations
    void* firstActivation;  // 0x2BE4: QueuePlayerFirstActivation
    void* secondActivation; // 0x2BE8: QueuePlayerSecondActivation
    u8 pad2BEC[0x2BF0 - 0x2BEC];
};

struct Agent : TurningCollider {
    void* roster;           // 0x720: the item keeper record it belongs to
    s32 state;              // 0x724: the agent's state
    f32 stateTime;          // 0x728: the clock when the state last changed
    s32 requestBits;        // 0x72C: bit 0 asks to change state to requestedState, bit 1 to end the second player
    s32 requestedState;     // 0x730: the state func_001C9A58 hands to func_001C8F20 (0 from func_001CB328)
    u8 pad734[0x738 - 0x734];
    s32 targetRangeMin;     // 0x738: the nearest distance a target may be at
    f32 targetRangeMax;     // 0x73C: the furthest distance a target may be at
    f32 retargetDelayMin;   // 0x740: the shortest wait before it may target again
    f32 retargetDelayMax;   // 0x744: the longest wait before it may target again
    f32 targetReadyTime;    // 0x748: the clock before which it takes no target
    f32 targetAngleLimit;   // 0x74C: the widest bearing to a target, in radians
    void* mainClip;         // 0x750: the clip the main player plays
    AnimationPlayer* mainPlayer; // 0x754: an animation's player (func_0012C288 makes it, func_0012E760 ends it)
    Slot08 stateClips[17];  // 0x758: ids -1 at set-up (slot 0)
    AnimationPlayer* statePlayer; // 0x7E0: another (func_0012F0A0, func_0012F6B0)
    s32 clipGroupCount;     // 0x7E4
    Group08 clipGroups[8];  // 0x7E8
    void* lastClip;         // 0x868: the clip the state player last played
    f32 lastClipPhase;      // 0x86C: how far through lastClip it was
    Slot08 secondaryClips[17]; // 0x870: ids -1 at set-up (slot 0)
    void* defaultSecondaryClip; // 0x8F8
    u8 pad8FC[0x900 - 0x8FC];
    Vec02 placePosition;    // 0x900: a place an item keeper gives its member (func_001CC120)
    f32 placeHeading;       // 0x910: its heading there
    f32 resumeTime;         // 0x914: the animation time the next player starts at
    f32 savedClipTime;      // 0x918: the animation time saved when a clip stops
    f32 savedClipSpeed;     // 0x91C: the speed saved when a clip stops
    s32 f920;               // 0x920
    s32 pathGraphId;        // 0x924: the id of the point graph
    PointGraphObject* pathGraph; // 0x928: the point graph of f924 (FindFirstObjectByIdMode4)
    s32 pathCount;          // 0x92C: func_001C84C0 compares it with f930
    s32 pathIndex;          // 0x930: the point of the path it heads for
    u8 pad934[0xA40 - 0x934];
    Vec02 goalPoint;        // 0xA40: the last point func_001C8418 was given
    Vec02 snappedGoal;      // 0xA50: that point (after SnapPointToOwnerGraph) while fA60 is clear
    s32 pathValid;          // 0xA60: cleared by func_001C8418 once the point is 40 (D_00274C90) from vA50 on the ground
    u8 padA64[0xA68 - 0xA64];
    s32 hitsLeft;           // 0xA68: the hits it takes before it is removed
    s32 fA6C;               // 0xA6C
    f32 fadeDelay;          // 0xA70
    void* stateObject;      // 0xA74: the object whose animation state 3 plays
    s32 meshKeyCount;       // 0xA78: the number of fA7C entries (func_001CA960)
    Elem08 meshKeys[4];     // 0xA7C
    Contact03* hitContacts; // 0xAAC: the contacts CollideAgentWithObject gathers; func_001CAF38 handles
                            // and frees them
    Vec02 launchVelocity;   // 0xAB0: the velocity func_001CAF38 launches an object with
                            // (LaunchObjectWithAgentVelocity hands it on)
    s32 sparePlayerContacts; // 0xAC0: func_001CAF38 lets the player's contacts be while it is set
    s32 extraClipCount;     // 0xAC4: the number of fAC8 entries (func_001CA720)
    Pend08 extraClips[4];   // 0xAC8
    s32 hasMemberGroupId;   // 0xAF8
    s32 memberGroupId;      // 0xAFC
    BaseObject* memberGroup; // 0xB00: the object of id fAFC, or the member group (PostLoadAgent)
    s32 hasTargetSetId;     // 0xB04: a flag (1 from func_001CA888, tested by func_001C72A0)
    s32 targetSetId;        // 0xB08
    void* targetSet;        // 0xB0C: the pool of objects it may target
    s32 flagIndex;          // 0xB10: its bit in the flag table
    s32 fB14;               // 0xB14
    f32 startPhase;         // 0xB18: the fraction of the clip a state-2 clip starts at
    s32 usesPitch;          // 0xB1C: set when it faces with a pitch as well as a yaw
    u8 fB20[4];             // 0xB20
    f32 pitch;              // 0xB24: the facing pitch
    u8 padB28[0xB40 - 0xB28];
    s32 hasSecondaryTarget; // 0xB40: set to 1 with fB48 (func_001CAB00)
    u8 padB44[0xB48 - 0xB44];
    void* secondaryTarget;  // 0xB48
    s32 secondaryTargetKey; // 0xB4C: the id of the objects PickAgentSecondaryTarget picks from
    void* primaryTarget;    // 0xB50
    void* target;           // 0xB54
    s32 fB58;               // 0xB58
    s32 fB5C;               // 0xB5C
    u8 scatterPoint[0x10];  // 0xB60
    s32 fB70;               // 0xB70
    void* copySource;       // 0xB74: the object CopyAgent copied it from, where its clips are looked up
    s32 followsClipMotion;  // 0xB78: set while the clip's own motion moves it
    s32 facingLocked;       // 0xB7C
    s32 fB80;               // 0xB80
    s32 stateLocked;        // 0xB84
    s32 stateForced;        // 0xB88
    s32 loopBackArmed;      // 0xB8C
    u8 padB90[0xBA4 - 0xB90];
    s32 arrivalTime;        // 0xBA4
    u8 padBA8[0xBD0 - 0xBA8];
    s32 fBD0;               // 0xBD0
    s32 fadesOut;           // 0xBD4: set when state 11 fades the object out
    u32 requestsBlocked;    // 0xBD8: set to refuse requests and object events
    u8 padBDC[0xBE8 - 0xBDC];
    f32 contactValue;       // 0xBE8
    s32 bindingKey;         // 0xBEC: the id its state player's extra target binding uses (-1 none)
    s32 bindingObject;      // 0xBF0: the object that binding gives the state player
    f32 state6Deadline;     // 0xBF4: the clock when state 6 may end
    f32 fBF8;               // 0xBF8
    f32 clip10Deadline;     // 0xBFC: the clock when the clip of state 10 plays
    f32 state8Deadline;     // 0xC00: the clock when state 8 is chosen
    s32 contactsDisabled;   // 0xC04: set in states 11 and 16
    u8 padC08[0xC10 - 0xC08];

    const Desc08* desc08() const { return (const Desc08*)desc; }
};

struct ObjectGatherer;
struct CompanionAgent : Agent {
    s32 companionId;        // 0xC10: the id of its companion object
    void* companion;        // 0xC14
    f32 reachRadius;        // 0xC18: the horizontal reach from the companion
    f32 reachHeight;        // 0xC1C: the height reach from the companion
    f32 closeRadius;        // 0xC20: the distance that counts as close
    f32 closeHeight;        // 0xC24: the height difference that counts as close
    s32 closeZoneId;        // 0xC28: the id of the zone that counts as close
    ObjectGatherer* closeZone; // 0xC2C: the object of id fC28, whose shape func_001B7280 tests
    s32 lookTarget;         // 0xC30: the object the companion looks at
    void* poseSource;       // 0xC34
    Slot08 lookEntries[17]; // 0xC38: ids -1 at set-up (func_001B6EC8), resolved by func_001B6F50
    void* soundLevel;       // 0xCC0
    s32 clipEndCount;       // 0xCC4
    u8 padCC8[0xCD4 - 0xCC8];
    s32 excludedCount;      // 0xCD4
    Slot08 excludedObjects[5]; // 0xCD8: fCD4 of them, resolved by slot 16 (func_001B7128)
};

struct ConeAgent : Agent {
    f32 leashDistance;      // 0xC10: the furthest the target may be from its home
    f32 leashHeight;        // 0xC14: the greatest height difference to a target
    s32 zoneId;             // 0xC18: the id of the zone the target must be in
    ObjectGatherer* zone;   // 0xC1C: the object of id fC18, whose shape func_00167F10 tests
    f32 nearRange;          // 0xC20: the distance inside which the full angle holds
    f32 farRange;           // 0xC24: the distance beyond which a target is refused
    f32 farAngle;           // 0xC28: the widest bearing at farRange
    f32 nearAngle;          // 0xC2C: the widest bearing at nearRange
    s32 sightZoneId;        // 0xC30: the id of the zone that skips the angle test
    ObjectGatherer* sightZone; // 0xC34: the object of id fC30, whose shape func_00167F10 tests
    union {
        s32 engaged;        // 0xC38: set when the target was found free (func_00167F10)
        s64 engagedQuad;    // 0xC38: the same, tested as a doubleword
    };
    s32 disabled;           // 0xC40
    u8 padC44[0xC50 - 0xC44];
};

// 0x0B, the keyed cone agent: a cone agent that counts down (+0xC5C) as it moves between its six
// key objects (FindNearestAgentKey).
struct World1Boss : ConeAgent {
    void* stateGraph;       // 0xC50: the graph of the walker
    void* stateWalker;      // 0xC54: the state walker
    s32 stageKey;           // 0xC58: its mode, 0x2D8 to 0x2DB
    s32 visitsLeft;         // 0xC5C: the count it lowers (ChooseWorld1BossState stops at 0)
    void* fC60;             // 0xC60
    PlacedObject* keyRoots[6]; // 0xC64: the roots whose colliders slot 56 refuses (func_001E9038)
    PlacedObject* nearestKeyRoot; // 0xC7C: the nearest of fC64 (FindNearestAgentKey)
    s32 stageFlagIndices[4]; // 0xC80: the flag table bits it takes (TakeFlagTableIndex)
    s32 stagesLeft;         // 0xC90: the stages still to go
    u8 padC94[0xCA0 - 0xC94];
};

struct World2Boss : Agent {
    s32 fC10;               // 0xC10
    u8 padC14[0xE00 - 0xC14];
    BlendAnimationView* blendView; // 0xE00
    s32 firstInRange;       // 0xE04: its first clip was in range last frame (func_0018AE38)
    s32 secondInRange;      // 0xE08: the second's
    void* walkerGraph;      // 0xE0C
    void* walker;           // 0xE10
    void* fE14;             // 0xE14
    void* firstPool;        // 0xE18
    void* secondPool;       // 0xE1C
    s32 keyedCount;         // 0xE20
    void* keyedObjects;     // 0xE24
    s32 phase;              // 0xE28: the number of phases passed
    s32 drawsRing;          // 0xE2C: set while the marker ring is drawn
    s32 phaseClips[3];      // 0xE30
    s32 pendingWalkerTarget; // 0xE3C: the walker key to go to when state 16 ends
    Vec02 launchPoint;      // 0xE40
};

struct World4Boss : Agent {
    s32 fC10;               // 0xC10
    Animation* fC14;        // 0xC14: the animations the script gives (SetWorld4BossValues)
    Animation* fC18;        // 0xC18
    Animation* fC1C;        // 0xC1C
    u8 padC20[0xC24 - 0xC20];
    s32 fC24;               // 0xC24
    u8 padC28[0xC30 - 0xC28];
};

struct SeekingAgent : Agent {
    s32 objectCount;        // 0xC10: the number of fC14
    void* objects[4];       // 0xC14: objects
    void* walkTarget;       // 0xC24: an object whose position slot 89 takes (func_001F3BD8)
    void* stateTarget;      // 0xC28: the same in states 12 and 13; slot 71 clears it
    void* partner;          // 0xC2C: an object (slot 91 calls its slot 80)
    s32 requestKind;        // 0xC30
    s32 requestInPool;      // 0xC34: set when the requester is in the partner's pool
    s32 removeClip;         // 0xC38
    s32 hurtClip;           // 0xC3C
    s32 removeClipAlt;      // 0xC40
    s32 hurtClipAlt;        // 0xC44
    u8 padC48[0xC50 - 0xC48];
};

struct GaugeColliderAgent : Agent {
    s32 noticeValue;        // 0xC10
    void* node;             // 0xC14: the node it holds from the gauge collider
    s32 nearCollider;       // 0xC18: set within 1100 of the active collider on the ground, cleared past 2000 (func_00198860)
    u8 padC1C[0xC20 - 0xC1C];
};

struct WorldListedAgent : Agent {
    Pack10 listLink;        // 0xC10: its link in the world's list of agents
    u8 padC18[0xC20 - 0xC18];
};

struct NumberedAgent : WorldListedAgent {
    s32 targetNear;         // 0xC20: latched when the target is near and ahead of it
    s32 fC24;               // 0xC24
    void* slot;             // 0xC28: the gauge slot it holds
    s32 number;             // 0xC2C: its place in the order the agents started
};

struct ContactAgent : WorldListedAgent {
    void* slot;             // 0xC20: the gauge slot it holds
    f32 clipSpeed;          // 0xC24: the speed its state clip plays at
    u8 padC28[0xC30 - 0xC28];
};

// An entry of the tempo agent's table at 0xC6C (func_001ED090 adds one): an animation player
// and the number of beats its animation spans, whose speed SyncWorld3BossEntries sets.
struct TempoPlayerEntry {
    AnimationPlayer* player; // 0x00
    s32 beats;              // 0x04
};

// 0x13, the tempo agent: counts beats at a tempo (UpdateWorld3Boss) for the class 0x1C
// beat-press colliders to judge presses against (JudgeWorld3BeatPressInput).
struct World3Boss : Agent {
    s32 clips[4];           // 0xC10: the clips of D_00275CF8 it resolves at load (ResolveAgentClip, func_001EBF40)
    s32 pendingClip;        // 0xC20: the clip of the scheduled press
    void* lines[4];         // 0xC24: the timelines of the links 0x4E7.. (func_001EC828 takes the one at fC40)
    World3Timeline* pendingTimeline; // 0xC34: the timeline to start when the beat clock restarts
    World3Timeline* heldTimeline; // 0xC38: the timeline it runs (EndHeldWorld3Timeline)
    World3BeatPressCollider* beatPressCollider; // 0xC3C: the active beat-press collider (HandleWorld3BeatPressColliderActivation sets it)
    s32 direction;          // 0xC40: which of fC24 is in use
    f32 pressScheduledTime; // 0xC44: the clock when the last press was scheduled
    void* faceObject;       // 0xC48: an object it goes to and faces in states 12 to 14
    s32 fC4C;               // 0xC4C: set and cleared by timeline entries of kinds 4 and 5 (func_001ED318)
    void* walkerGraph;      // 0xC50
    void* walker;           // 0xC54
    u8 padC58[0xC5C - 0xC58];
    s32 tempo;              // 0xC5C: the tempo in beats a minute (SetWorld3BossTempo)
    s32 spanBeats;          // 0xC60: a span in beats (SetWorld3BossSpanBeats)
    f32 spanSeconds;        // 0xC64: that span in seconds
    s32 playerCount;        // 0xC68: the number of fC6C entries (func_001ED090)
    TempoPlayerEntry* players; // 0xC6C: a 0x400-byte table (slot 0)
    s32 bar;                // 0xC70: the bars counted (four beats each)
    s32 beat;               // 0xC74: the beats counted
    s32 beatInBar;          // 0xC78: the beat in the bar, 0 to 3
    f32 barPosition;        // 0xC7C: the position in the bar, in beats
    f32 lastBeatTime;       // 0xC80: the time of the last beat
    f32 nextBeatTime;       // 0xC84: the time of the next beat
    f32 beatLength;         // 0xC88: the beat length in use, in seconds
    f32 newBeatLength;      // 0xC8C: the beat length set, 60 over the tempo (taken at the bar)
    u8 padC90[0xC94 - 0xC90];
    s32 beatGate;           // 0xC94: 0 closed, 1 waiting for a beat, 2 open
    s32 keyedCount;         // 0xC98
    void* keyedObjects;     // 0xC9C
};

struct TintBlendCollider : TurningCollider {
    s32 state;              // 0x720: the mode func_001DFBE0 sets
    f32 stateTime;          // 0x724: the clock when it last changed (func_001DFBE0)
    s32 tinted;             // 0x728: set while its colour is blended
    f32 tintStartTime;      // 0x72C
    f32 tintFadeTime;       // 0x730
    u8 pad734[0x738 - 0x734];
    s32 f738;               // 0x738
    s32 f73C;               // 0x73C
    void* heldContacts;     // 0x740
    void* f744;             // 0x744
    void* f748;             // 0x748
    void* f74C;             // 0x74C
    void* f750;             // 0x750
    void* f754;             // 0x754
    void* walkerGraph;      // 0x758
    StateWalker* walker;        // 0x75C: a handle (func_001B64D8, func_001B6628 take it)
};

struct WalkerCollider : SwitchedCollider {
    s32 state;              // 0x610: the walker's state, -1 at set-up
    s32 subState;           // 0x614: the walker's sub-state, -1 at set-up
    f32 heading;            // 0x618: the heading of the left stick
    f32 stickLength;        // 0x61C: how far the left stick is pushed
    f32 aimHeading;         // 0x620: the heading of the second stick
    f32 aimLength;          // 0x624: how far the second stick is pushed
    f32 speedScale;         // 0x628: the scale of the stick length in the move offset
    u8 pad62C[0x630 - 0x62C];
    Vec02 moveOffset;       // 0x630: the offset func_001A3C40 computes from the heading (ComputePolarOffset)
    void* stateGraph;       // 0x640: the graph of the state walker
    void* stateWalker;      // 0x644: the walker that follows the state
    s32* stateSound;        // 0x648: the sound of the state
    void* f64C;             // 0x64C
    void* subStateGraph;    // 0x650: the graph of the sub-state walker
    void* subStateWalker;   // 0x654: the walker that follows the sub-state
    void* subStateSound;    // 0x658: the sound of the sub-state
    void* f65C;             // 0x65C
    void* f660;             // 0x660
    void* f664;             // 0x664
    s32 spawnerCount;       // 0x668: how many effect spawners spawners holds
    u8 spawners[0xC];       // 0x66C: the effect spawners gathered at start
    s32 f678;               // 0x678
    void* f67C;             // 0x67C
    void* f680;             // 0x680
    void* stateAnimPlayer;  // 0x684: the animation player of the state
    s32 stateAnimDone;      // 0x688: set when the state's animation finished
    u8 pad68C[0x690 - 0x68C];
};

struct ObjectPool;      // object_pool.h

struct PlayerLinkedCollider : SwitchedCollider {
    void* stateGraph;       // 0x610: the graph of the walker
    StateWalker* stateWalker; // 0x614: the walker on f610 (func_001E5428)
    ObjectPool* pool;       // 0x618: the pool it chooses from (func_001E5888, func_001E5C78)
    s32 f61C;               // 0x61C
    void* target;           // 0x620: the object this collider stands for
    void* agent;            // 0x624: the agent found for it
    s32 f628;               // 0x628
    u8 pad62C[0x630 - 0x62C];
    s32 f630;               // 0x630
    u8 pad634[0x638 - 0x634];
    s32 linkedCount;        // 0x638: how many linked objects there are
    void* linkedObjects;    // 0x63C: the objects the ids resolve to
    void* linkedIds;        // 0x640: the ids of the linked objects
    s32 f644;               // 0x644
    u8 pad648[0x650 - 0x648];
    f32 f650;               // 0x650
    f32 f654;               // 0x654
    f32 f658;               // 0x658
    f32 f65C;               // 0x65C
};

struct C17 : SwitchedCollider {
    s32 stateGraph;         // 0x610: the graph of the walker
    StateWalker* stateWalker;   // 0x614: a handle (func_001B6290)
    u8 pad618[0x61C - 0x618];
    u8 markers[0x28];       // 0x61C: three 12-byte records func_0019A178 sets up (slot 16)
    s32 extraId;            // 0x644: the link id of the extra object
    void* extraObject;      // 0x648: the extra object
    s32 triggerId;          // 0x64C: the link id of the trigger object
    void* triggerObject;    // 0x650: the object that announces the player's step
    s32 f654;               // 0x654
    Ent17 sequenceGroups[6]; // 0x658: the six groups of step sequences the progress picks from
    s32 levelBit;           // 0x760: the world-bit mask the collider stands for
    s32 levelBitIndex;      // 0x764: the index of levelBit in the table of the 28 bits
    void* levelBitObjects[28]; // 0x768: the object of each table entry
    s32 queueCount;         // 0x7D8: how many objects are queued
    void* queue[1];         // 0x7DC: the queued objects, run one at a time
    u8 pad7E0[0x800 - 0x7E0];
};

struct GaugeCollider : SwitchedCollider {
    void* carryGraph;       // 0x610
    StateWalker* carryWalker;   // 0x614: a handle (func_001B6290)
    f32 heading;            // 0x618: the heading it is driven along
    f32 lastGroundTime;     // 0x61C: the clock when it last had a floor contact
    f32 push;               // 0x620: the stick's push times f624 (func_001974F8)
    f32 pushStrength;       // 0x624
    f32 topSpeed;           // 0x628
    u8 pad62C[0x630 - 0x62C];
    Vec02 groundNormal;     // 0x630
    void* dropZone;         // 0x640: an object func_00198760 tests and hands on
    s32 noticeValue;        // 0x644
    u8 pad648[0x64C - 0x648];
    void* groundProbes[4];  // 0x64C: the four objects whose floor func_00196EB0 samples
    void* poseObject;       // 0x65C
    void* restTarget;       // 0x660: the pose source's target when nothing is carried
    void* poseSource;       // 0x664
    void* carrier;          // 0x668: its record at +0x2D0 takes the held object's value (func_001974F8)
    u8 pad66C[0x670 - 0x66C];
    void* carryNode;        // 0x670: the node func_001971B8 measures from (its world position and +0x40)
    void* held;             // 0x674: the object being carried (func_001974F8)
    void* f678;             // 0x678
    s32 waitingCount;       // 0x67C: counted up by func_00198760, at most D_0026A720
    s32 deliveredCount;     // 0x680: the count g_gaugeAmountCaption shows (func_00197F10)
    s32 deliveryLimit;      // 0x684: its limit, one per class 0x48 object (func_00198920)
    f32 timeLimit;          // 0x688
    f32 pickTime;           // 0x68C: the clock when the carried object was picked (func_001974F8)
    s32 agentCount;         // 0x690
    void* agents;           // 0x694: f690 entries
    f32 nextPlaceTime;      // 0x698: the time of the next transfer (func_00197848, func_00198760)
    List01 freeNodes;       // 0x69C: link offset 0x568 (slot 0); filled by slot 16
    List01 usedNodes;       // 0x6A8: link offset 0x568 (slot 0)
    void* phaseGraph;       // 0x6B4
    void* phaseWalker;      // 0x6B8
    u8 pad6BC[0x6C0 - 0x6BC];
};

// What a path follower's wheels hand their particles to (func_001D8E40): an object whose slot
// at 0x7C takes a spawn record, and a word that, clear, asks for the velocity at the point.
struct PathEmitter {
    void** vt;              // 0x00
    u8 pad04[0x18 - 0x04];
    s32 f18;                // 0x18
};
struct PathEmitters {
    u8 pad00[0x18];
    f32 grip;               // 0x18: the grip a path follower using them has in place of its f868 (func_001D7778)
    f32 maxSpeed;           // 0x1C: the most pace a path follower using them may have (func_001D9D78)
    PathEmitter* firstEmitter; // 0x20
    PathEmitter* secondEmitter; // 0x24
};

struct PathFollower : SwitchedCollider {
    f32 frontWheelRadius;   // 0x610: the radius of the front wheels
    f32 rearWheelRadius;    // 0x614: the radius of the rear wheels
    f32 maxSpeed;           // 0x618: the top speed
    f32 sideLimit;          // 0x61C: the furthest it keeps from the path's centre line
    Vec02 paceBlendCurve;   // 0x620: x, y, z the blend's curve over the entry's clock (func_001DB290)
    union {
        u8 blendEnds[0x40]; // 0x630: 0x40 bytes slot 0 copies from D_00275250
        struct {
            u8 firstEnd[0x10]; // 0x630: the blend's first end (func_001DB290)
            f32 firstRangeLo; // 0x640: its range
            f32 firstRangeHi; // 0x644
            u8 pad648[0x650 - 0x648];
            u8 secondEnd[0x10]; // 0x650: the second end
            f32 secondRangeLo; // 0x660: its range
            f32 secondRangeHi; // 0x664
            u8 pad668[0x670 - 0x668];
        };
    };
    union {
        struct {
            f32 paceCurveA; // 0x670
            f32 paceCurveB; // 0x674
            f32 paceCurveC; // 0x678
            u8 pad67C[0x680 - 0x67C];
        };
        u8 blendedEnd[0x10]; // 0x670: the blend of the two ends
    };
    f32 paceMin;            // 0x680: the blend of the two ranges
    f32 paceMax;            // 0x684
    u8 pad688[0x690 - 0x688];
    PlacedObject* bodyObject; // 0x690: drawn with this one's scale (func_001DAA18)
    f32 targetHeading;      // 0x694: the heading it steers to
    f32 targetSpeed;        // 0x698: divided by f610 or f614 into the slots (func_001D8D90); 0 in func_001D9C98
    f32 steerAngle;         // 0x69C: eased by func_001D8D90
    s32 contactStamp;       // 0x6A0: the contact generation; a wheel stamped with it touched this step
    u8 pad6A4[0x6B0 - 0x6A4];
    Slot19 wheels[4];       // 0x6B0: the four wheels
    PathCurveObject* path;  // 0x830: the path it follows (func_001DAFB8)
    f32 pathLength;         // 0x834: the path's length
    f32 pathTime;           // 0x838: the time it samples the path at (func_00181658)
    f32 pathDistance;       // 0x83C: the distance along the path
    f32 sideOffset;         // 0x840: the signed distance from the path's centre line
    f32 sideTarget;         // 0x844: the side offset it aims at
    PathCurveObject* sidePath; // 0x848: the curve it keeps its side offset on (func_001D87C8)
    f32 sidePathTime;       // 0x84C: the time on f848 found nearest (func_001D87C8)
    f32 uprightTime;        // 0x850: the clock when it last stood upright
    f32 lapTime;            // 0x854: the clock of the last lap count
    s32 lapsLeft;           // 0x858
    f32 pace;               // 0x85C: the share of the top speed it keeps
    f32 paceTarget;         // 0x860
    f32 paceChangeTime;     // 0x864: the clock when the pace target is chosen again
    f32 grip;               // 0x868
    f32 pushedTime;         // 0x86C: -10.0 at reset (func_001DB290)
    s32 markerCount;        // 0x870: the number of markers in use
    PathMarker markers[16]; // 0x874: f870 of them
    PathMarker* firstMarker; // 0xAF4: the first object marker
    PathMarker* currentMarker; // 0xAF8: the current one
    PathEmitters* activeZone; // 0xAFC: the emitters it uses in place of fB18 and fB1C, none for those (func_001D8E40)
    s32 lap;                // 0xB00
    s32 lapCount;           // 0xB04: the number of laps
    s32 place;              // 0xB08: its place among the followers
    s32 placeCount;         // 0xB0C: the number of followers when place was counted
    f32 placeChangeTime;    // 0xB10: -10.0 at reset (func_001DB290)
    BaseObject* lapObject;  // 0xB14
    PathEmitter* firstEmitter; // 0xB18: the wheels' first emitter (func_001D8E40)
    PathEmitter* secondEmitter; // 0xB1C: the second
    u8 padB20[0xB28 - 0xB20];
    void* frontBeam;        // 0xB28: func_001DAA18 draws a quad for each of these two
    void* rearBeam;         // 0xB2C
    s32 kind;               // 0xB30: 0, 1 or 2
    s32 mode;               // 0xB34: 0 idle, 1 follows the path itself, 2 the player's pad
    f32 modeTime;           // 0xB38: the clock when the mode was set
    u8 padB3C[0xB44 - 0xB3C];
    StateTrigger* walkerGraph; // 0xB44: the graph its walker (fB48) is made on
    void* walker;           // 0xB48
    void* contactMesh;      // 0xB4C: the mesh object func_001DA320 tests the other against
    s32 pushedCount;        // 0xB50: the objects in pushed (func_001D9AC8)
    Collider* pushed[8];    // 0xB54: the objects its contacts pushed, each once (func_001D9AC8)
    Contact03* contacts;    // 0xB74: the contacts to process, given back to the world's pool (func_001D9AC8)
    void* partner;          // 0xB78: the class 0x104 object it hands effects to
    u8 slideSound[0x4];     // 0xB7C
    u8 engineSoundB[0x4];   // 0xB80
    u8 engineSoundA[0x4];   // 0xB84
    u8 padB88[0xB8C - 0xB88];
    f32 slidePitchOffset;   // 0xB8C
    f32 engineBPitchOffset; // 0xB90
    f32 engineAPitchOffset; // 0xB94
    f32 fB98;               // 0xB98
    f32 drive;              // 0xB9C: the input UpdatePathFollowerSound's curves weigh (func_001D9678)
    f32 soundSpeed;         // 0xBA0: the speed it ramps towards the forward speed's share (func_001D9678)
    u8 padBA4[0xBB0 - 0xBA4];
};

struct ModeWalker : PathFollower {
    s32 walkerMode;         // 0xBB0: the walker's mode
    f32 walkerModeTime;     // 0xBB4: the clock when the mode was set
    void* stateGraph;       // 0xBB8: the graph of the walker
    StateWalker* stateWalker;   // 0xBBC: a handle (func_001B6290)
    void* fBC0;             // 0xBC0
    void* fBC4;             // 0xBC4: turned to the camera's side (func_00181078)
    void* fBC8;             // 0xBC8
    void* fBCC;             // 0xBCC
    void* fBD0;             // 0xBD0
    u8 padBD4[0xBE0 - 0xBD4];
    Vec02 vBE0;             // 0xBE0
    s32 pulseActive;        // 0xBF0: set while the marker pulses
    f32 pulseStartTime;     // 0xBF4: the time the pulse began
    f32 pulseFadeStart;     // 0xBF8: the time the pulse's fade began
    f32 buttonPressTime;    // 0xBFC: the clock when the button was pressed (func_00181078)
    s32 fC00;               // 0xC00
    void* contactChainHead; // 0xC04: the head of its contact chain
    PlacedObject* fC08;     // 0xC08: the object func_00181658 turns to follow the path's frame
    u8 padC0C[0xC10 - 0xC0C];
};

struct World5ModeCollider : SwitchedCollider {
    s32 mode;               // 0x610: the mode (SetWorld5ModeColliderMode)
    f32 modeStartTime;      // 0x614: the clock when the mode was set
    s32 modeAnimPlayer;     // 0x618: the player of the mode's animation
    f32 heading;            // 0x61C: the angle about z of the matrix at 0x620 outside modes 2 to 4 (func_00179A68)
    Mat02 m620;             // 0x620: the collider's matrix (func_00179A68)
    void* f650;             // 0x650
    void* stateGraph;       // 0x654: the graph of the walker
    void* stateWalker;      // 0x658: the state walker
    u8 pad65C[0x660 - 0x65C];
    void* f660;             // 0x660
    PlacedObject* f664;     // 0x664: the object whose position func_00179A68 takes into 0x660's frame
    void* f668;             // 0x668
    u8 pad66C[0x674 - 0x66C];
    PlacedObject* f674[2];  // 0x674: the two objects func_00179A68 turns toward the aimed point
    PlacedObject* f67C;     // 0x67C: a third, turned by its own attachment's frame (func_00179A68)
    BaseObject* f680;       // 0x680: an object g_modeColliderLinks links (func_00124DF8)
    f32 restWeight;         // 0x684: the weight of the neutral animation
    u8 pad688[0x690 - 0x688];
    f32 negXWeight;         // 0x690: the weight of the animation for a negative x aim
    u8 pad694[0x69C - 0x694];
    f32 posXWeight;         // 0x69C: the weight of the animation for a positive x aim
    u8 pad6A0[0x6A8 - 0x6A0];
    f32 negYWeight;         // 0x6A8: the weight of the animation for a negative y aim
    u8 pad6AC[0x6B4 - 0x6AC];
    f32 posYWeight;         // 0x6B4: the weight of the animation for a positive y aim
    u8 pad6B8[0x6C0 - 0x6B8];
    void* weightBlend;      // 0x6C0: the animations of modes 2, 1, 3 and 4 (SetWorld5ModeColliderMode)
    void* mode1Anim;        // 0x6C4: the animation of mode 1
    void* mode3Anim;        // 0x6C8: the animation of mode 3
    void* mode4Anim;        // 0x6CC: the animation of mode 4
    s32 pulseActive;        // 0x6D0: set while the marker pulses
    f32 pulseStartTime;     // 0x6D4: the time the pulse began
    f32 pulseFadeStart;     // 0x6D8: the time the pulse's fade began
    f32 buttonPressTime;    // 0x6DC: the clock when the 0x40 button was last pressed (func_00179A68)
    s32 f6E0;               // 0x6E0
    void* f6E4;             // 0x6E4
    void* f6E8;             // 0x6E8
    f32 aimX;               // 0x6EC: the aim's two values, eased by their speeds (func_00179A68)
    f32 aimY;               // 0x6F0: the aim's y value, eased by its rate
    f32 aimRateX;           // 0x6F4: their speeds
    f32 aimRateY;           // 0x6F8: the rate of aimY
    f32 poseX;              // 0x6FC: the pose's two values, eased by f704 and f708 (func_00179A68)
    f32 poseY;              // 0x700: the pose's y value, eased by its rate
    f32 poseRateX;          // 0x704: the rate of poseX
    f32 poseRateY;          // 0x708: the rate of poseY
    s32 releasePending;     // 0x70C: set, the player is handed back to its own control
};

struct World3BeatPressCollider : SwitchedCollider {
    void* walkerGraph;      // 0x610
    void* walker;           // 0x614
    void* lineAnchors[4];   // 0x618: the objects func_001EC828 places the tempo agent's timelines by
    EntryQueue* entryQueue; // 0x628: the entry queue it binds to the player (func_001EB748)
    s32 nextEntry;          // 0x62C: the index of the entry being judged
    s32 entryCount;         // 0x630: the number of entries held
    Ent1C entries[8];       // 0x634: f630 of them, f62C the next (slot 77)
    f32 pressBeat;          // 0x674: the beat position of the press
    s32 pressDirection;     // 0x678: the direction pressed
    void* frameAnchor;      // 0x67C
    s32 judging;            // 0x680: set while presses are judged
    f32 timingWindow;       // 0x684: the width of the window around a beat
    s32 runEnded;           // 0x688: set when a missed beat ends the run
    void* tempoAgent;       // 0x68C
};

struct HitCountCollider : SwitchedCollider {
    s32 state;              // 0x610
    f32 stateTime;          // 0x614
    u8 pad618[0x62C - 0x618];
    void* f62C;             // 0x62C
    f32 f630;               // 0x630
    f32 f634;               // 0x634
    s32 acceptedMark;       // 0x638: set after an accepted request
    f32 acceptedTime;       // 0x63C
    f32 f640;               // 0x640
    f32 heading;            // 0x644: the heading the stick asks for
    f32 aimHeading;         // 0x648: the heading of the second stick
    u8 pad64C[0x660 - 0x64C];
    PlacedObject* aimObject; // 0x660: an object it turns with itself (func_001C34C8 sets its matrix)
    void* walkerGraph;      // 0x664
    void* walker;           // 0x668
    u8 pad66C[0x670 - 0x66C];
    f32 f670;               // 0x670
    u8 pad674[0x678 - 0x674];
    void* hitClip;          // 0x678
    AnimationPlayer* hitPlayer; // 0x67C: the player func_001C34C8 starts from f678 and stops at speed 0
    s32 hitPending;         // 0x680: set when a hit is to be played
    BaseObject* touchedObject; // 0x684: an object of kind 0x21 that touched it; slot 3 sends it a request
    BaseObject* collectedObject; // 0x688: an object id 0x52F that hit it (func_001C3C00); slot 3 takes it out
    f32 baseRadius;         // 0x68C
    s32 collectedCount;     // 0x690
    s32 hitsLeft;           // 0x694
    s32 placePointCount;    // 0x698: the objects in f69C
    BaseObject* placePoints[1]; // 0x69C: objects the script adds (AddHitCountColliderId)
    u8 pad6A0[0x71C - 0x6A0];
    s32 itemCount;          // 0x71C
    void* items[16];        // 0x720
};

typedef char check_Part07[sizeof(Part07) == 0x100 ? 1 : -1];
typedef char check_Ent17[sizeof(Ent17) == 0x2C ? 1 : -1];
typedef char check_PathMarker[sizeof(PathMarker) == 0x28 ? 1 : -1];
typedef char check_Slot19[sizeof(Slot19) == 0x60 ? 1 : -1];
typedef char check_SwitchedCollider[sizeof(SwitchedCollider) == 0x610 ? 1 : -1];
typedef char check_TurningCollider[sizeof(TurningCollider) == 0x720 ? 1 : -1];
typedef char check_Player[sizeof(Player) == 0x2BF0 ? 1 : -1];
typedef char check_Agent[sizeof(Agent) == 0xC10 ? 1 : -1];
typedef char check_C09[sizeof(CompanionAgent) == 0xD00 ? 1 : -1];
typedef char check_ConeAgent[sizeof(ConeAgent) == 0xC50 ? 1 : -1];
typedef char check_World1Boss[sizeof(World1Boss) == 0xCA0 ? 1 : -1];
typedef char check_World2Boss[sizeof(World2Boss) == 0xE50 ? 1 : -1];
typedef char check_World4Boss[sizeof(World4Boss) == 0xC30 ? 1 : -1];
typedef char check_SeekingAgent[sizeof(SeekingAgent) == 0xC50 ? 1 : -1];
typedef char check_GaugeColliderAgent[sizeof(GaugeColliderAgent) == 0xC20 ? 1 : -1];
typedef char check_WorldListedAgent[sizeof(WorldListedAgent) == 0xC20 ? 1 : -1];
typedef char check_NumberedAgent[sizeof(NumberedAgent) == 0xC30 ? 1 : -1];
typedef char check_ContactAgent[sizeof(ContactAgent) == 0xC30 ? 1 : -1];
typedef char check_World3Boss[sizeof(World3Boss) == 0xCA0 ? 1 : -1];
typedef char check_TintBlendCollider[sizeof(TintBlendCollider) == 0x760 ? 1 : -1];
typedef char check_WalkerCollider[sizeof(WalkerCollider) == 0x690 ? 1 : -1];
typedef char check_PlayerLinkedCollider[sizeof(PlayerLinkedCollider) == 0x660 ? 1 : -1];
typedef char check_C17[sizeof(C17) == 0x800 ? 1 : -1];
typedef char check_GaugeCollider[sizeof(GaugeCollider) == 0x6C0 ? 1 : -1];
typedef char check_PathFollower[sizeof(PathFollower) == 0xBB0 ? 1 : -1];
typedef char check_ModeWalker[sizeof(ModeWalker) == 0xC10 ? 1 : -1];
typedef char check_World5ModeCollider[sizeof(World5ModeCollider) == 0x710 ? 1 : -1];
typedef char check_World3BeatPressCollider[sizeof(World3BeatPressCollider) == 0x690 ? 1 : -1];
typedef char check_C1D[sizeof(HitCountCollider) == 0x760 ? 1 : -1];
typedef char check_Desc05[sizeof(Desc05) == 0x160 ? 1 : -1];
typedef char check_Desc06[sizeof(Desc06) == 0x170 ? 1 : -1];
typedef char check_Desc08[sizeof(Desc08) == 0x1A0 ? 1 : -1];

#endif
