// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x29 (descriptor D_00218F80, 0x7A0 bytes) and its child 0x2A (D_0021F058, 0x7C0 bytes): a
// collision trigger like class 0x28 that watches a short list of objects it looks up by id. It
// embeds the same 0x1CC-byte zone record as class 0x28 (Zone28, include/c28.h), at +0x5C0 instead
// of +0x554. Written for this project from what retail's code does (config/us/classes.tsv).
#ifndef ZONE_COLLIDER_H
#define ZONE_COLLIDER_H

#include "collider.h"
#include "trigger_zone.h"
struct BufferedStream;

struct ZoneCollider : Collider {
    s32 countIds;           // 0x550: how many ids it was loaded with (slot 16 looks each up)
    s32 ids[8];             // 0x554
    s32 countObjs;          // 0x574: the objects slot 16 found
    s32 objs[8];            // 0x578: (the objects as the loop stores them)
    s32 countInside;        // 0x598: the objects inside at the last update (func_00140258 keeps them)
    void* inside[8];        // 0x59C: func_00140550 hands each to a script list
    s32 f5BC;               // 0x5BC: set to 1 when there are no ids
    Zone28 zone;            // 0x5C0: its helpers take the record's address (func_0013E918, 0013E950, 0013EA38, 0013EB68)
    s32 f78C;               // 0x78C: func_00140258's next mode when a timed mode 2 runs out (1 if set, else 0)
    s32 f790;               // 0x790: tested by slot 10 (then zone.f13C = 1)
    u8 pad794[0x7A0 - 0x794];
};

// The child (0x7C0): two objects it finds in the level, by id (slot 15), and its link in the
// list the class 0x47 keeps at +0x55C (func_00152438 gives that list the offset 0x7B0).
struct FollowableObject : ZoneCollider {
    s32 id7A0;              // 0x7A0: -1 at set-up
    void* f7A4;             // 0x7A4: the object of that id, or the first of kind 0x7E (slot 15)
    s32 id7A8;              // 0x7A8: -1 at set-up
    void* f7AC;             // 0x7AC: the object of id7A8 (class 0x47 reads a field of it at +0x318)
    Link02 link7B0;         // 0x7B0: the link in class 0x47's list
    u8 pad7B8[0x7C0 - 0x7B8];
};

typedef char check_ZoneCollider[sizeof(ZoneCollider) == 0x7A0 ? 1 : -1];
typedef char check_FollowableObject[sizeof(FollowableObject) == 0x7C0 ? 1 : -1];

void InitZoneCollider(ZoneCollider* self);                          // slot 0
void CopyZoneCollider(ZoneCollider* self, ZoneCollider* src);                          // slot 9
void LoadZoneCollider(ZoneCollider* self, BufferedStream* stream);                          // slot 10
void StartZoneCollider(ZoneCollider* self);                          // slot 16
void InitFollowableObject(FollowableObject* self);                          // slot 0
void HandleFollowableObjectNotification(FollowableObject* self, s32 kind, void* arg);                // slot 13
void ResolveFollowableObjectLinks(FollowableObject* self);                          // slot 15

#endif
