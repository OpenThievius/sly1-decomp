// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_functions.h"
#include "flag_table.h"
#include "asm_func.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "object_message.h"
#include "world.h"
#include "object_event.h"
#include "transform_object.h"
#include "vu0.h"
#include "object_finder.h"
#include "list_walk.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/effect_spawner.h"
#include "functions/flagged_object.h"
#include "functions/iop_commands.h"
#include "functions/matrix.h"
#include "functions/object_gatherer.h"
#include "functions/oscillator.h"
#include "functions/pad_input.h"
#include "functions/path_follower.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/zone_collider.h"
struct BufferedStream;
struct Quad16;


// The file's .data, in retail's order: two boxes (the corners 0 and the size -1e8 or 1e8) and
// the records that point at them, which func_0013E430 reads, then the disc code's sector check
// state (disc_access.cpp uses it; its own .data must start 8-aligned).
f32 g_planeTreeBelowBounds[8] = { 0.0f, 0.0f, 0.0f, 0.0f, -100000000.0f, 0.0f, 0.0f, 0.0f };
f32 g_planeTreeAboveBounds[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 100000000.0f, 0.0f, 0.0f, 0.0f };
f32* g_planeTreeEmptyBelow[4] = { g_planeTreeBelowBounds, 0, 0, 0 };
f32* g_planeTreeEmptyAbove[3] = { g_planeTreeAboveBounds, 0, 0 };
s32 g_discSectorCheckState = 0;

extern u8 g_flagTable[];

// Initialises a masked collider: scale range 0.8 to 1.2, tint of 16 in each channel, a new
// flag-table index and no receiver.
void InitMaskedCollider(MaskedCollider* self)
{
    MaskedCollider* o = self;
    InitCollider(self);
    o->scaleMin = 0.8f;
    o->scaleMax = 1.2f;
    o->hitLimit = 1;
    o->impulseScale = 1.0f;
    o->tintByte4 = 16;
    o->tint[3] = 16;
    o->tint[2] = 16;
    o->tint[1] = 16;
    o->tint[0] = 16;
    o->id688 = TakeFlagTableIndex((FlagTable*)g_flagTable);
    o->receiverKey = -1;
}


// Loads the collider; resolves its receiver from the receiver key (lookup mode 0x101) and
// starts it, or builds the member group when the key is -1.
void LoadMaskedCollider(MaskedCollider* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    if (self->receiverKey == -1) {
        FindOrBuildMemberGroup((void**)&self->receiver, self);
        return;
    }
    BaseObject* v = (BaseObject*)FindFirstObjectById(self->world, 0x101, self->receiverKey, self);
    self->receiver = v;
    if (v != 0) {
        ResolveAndStartObject(v);
    }
}

void* CopyToFrontMemory(s32 size, void* owner);

// Copies the collider but keeps its own flag-table index, and gives the copy its own 0x24-byte
// copy of the sound parameters.
void CopyMaskedCollider(MaskedCollider* self, MaskedCollider* other)
{
    s32 saved = self->id688;
    CopyCollider(self, other);
    self->id688 = saved;
    if (other->soundParams)
        self->soundParams = CopyToFrontMemory(0x24, other->soundParams);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "memory_reader.h"
#include "object_message.h"
struct BaseObject;
struct Vec4;

struct BaseObject;

struct BaseObject;
struct Vec4;

struct Mat3;





typedef void (*Hook_CE40)(void* self);

void StartPlacedObject(PlacedObject* self);
void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

// Starts the placed object and queues AttachMaskedColliderChildren for it.
void StartMaskedCollider(MaskedCollider* self)
{
    StartPlacedObject(self);
    AppendQueuedCall(self->world, (void*)AttachMaskedColliderChildren, self, 0, 0);
}

extern u8 g_flagTable[];

// A list walk's frame (ListFrame's words) with one more word after it, the flag
// func_00199C10 reads for each child.
struct ListFrameWithFlag { s32 list; s32 cursor; s32 link; s32 prev; s32 out; };
struct NumberedItem;
s32 IsObjectOfKind(BaseObject* list, s32 key);

// Registers the children of a masked collider in its slot table: skips the kinds that are not its
// business (0x75, 0x7A, 0x53), for a busy collider only the numbered items whose flag is clear,
// enters each child under the first slot with its id (or a new slot of kind 4) and calls the
// child's method 3.
void AttachMaskedColliderChildren(MaskedCollider* self)
{
    ListFrameWithFlag fr;
    MaskedCollider* n;
    s32 i;
    MaskedQueueEntry* e;
    if (TestFlagTableBit((FlagTable*)g_flagTable, self->id688)) self->busy = 1;
    s32 l = (s32)&self->children;
    fr.cursor = l;
    fr.list = l;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = ((ObjectList*)l)->offset;
    *(s32*)&g_activeListFrames = (s32)&fr;
    fr.prev = old;
    s32 h = (s32)self->children.head;
    fr.link = link;
    fr.cursor = h + link;
    n = (MaskedCollider*)h;
    while (n != 0) {
        if (self->busy) {
            if (!IsObjectOfKind(n, 0x2E)) goto next;
            GetNumberedItemFlag((NumberedItem*)n, &fr.out);
            if (fr.out) goto next;
        }
        if (IsObjectOfKind(n, 0x75)) goto next;
        if (IsObjectOfKind(n, 0x7A)) goto next;
        if (IsObjectOfKind(n, 0x53)) goto next;
        if (IsObjectOfKind(n, 0x27)) n->slots[1].kind = (s32)self;
        for (i = 0; i < self->count550; i++) {
            e = &self->slots[i];
            if (MatchesObjectId(n, e->key)) {
                e->node = (s32)n;
                switch (e->kind) {
                case 0:
                case 1:
                case 3:
                    goto next;
                case 2:
                case 4:
                default:
                    break;
                }
                break;
            }
        }
        if (i >= self->count550) {
            e = &self->slots[self->count550];
            self->count550 = self->count550 + 1;
            e->kind = 4;
            e->node = (s32)n;
        }
        n->desc->m03(n);
    next:
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        n = (MaskedCollider*)nx;
    }
    *(s32*)&g_activeListFrames = fr.prev;
}


// Updates the collider; a busy collider is cleared and told through slot 0x48 of its class that
// its contact ended.
void UpdateMaskedCollider(MaskedCollider* self, f32 dt)
{
    UpdateCollider(self, dt);
    if (self->busy != 0) {
        self->busy = 0;
        self->desc20()->m48(self);
    }
}

struct PathFollower;

// The contact event func_0013D0B0 takes: the object that touched, a strength, two flag words and
// two vectors.
struct ContactEvent_0013D0B0 {
    PlacedObject* obj;      // 0x00
    u8 pad04[4];
    f32 strength;           // 0x08
    u32 flags;              // 0x0C
    u32 flags10;            // 0x10
    u8 pad14[0x20 - 0x14];
    Vec4 v20;              // 0x20
    Vec4 v30;              // 0x30
};

extern u8 g_padRecord[];

// The masked collider's reaction to an event on another object: ignored while it holds something or
// if the object is not one of its kinds or accepted (IsObjectAccepted). On an impact (flag 8) it
// applies an impulse, and on a hit (flag 0x10) it shakes the pad when the player did it, raises
// script event 0x14 and calls its method 0x48 once the count reaches its limit.
s32 HandleMaskedColliderEvent(MaskedCollider* self, ContactEvent_0013D0B0* ev)
{
    Vec4 push;
    Vec4 k;
    s32* counter;
    s32 i;

    if (self->hold != 0) {
        return 1;
    }
    if (ev->flags == 0) {
        return 0;
    }
    if (ev->obj == 0) {
        return 0;
    }
    if ((ev->obj->desc->flags & 2) == 0) {
        return 0;
    }
    for (i = 0; i < self->count668; i++) {
        if (IsObjectOfKind((MaskedCollider*)ev->obj, (s32)self->list66C[i]) != 0) {
            break;
        }
    }
    if (i >= self->count668) {
        if (IsObjectAccepted(self, (PathFollower*)ev->obj) == 0) {
            return 0;
        }
    }
    if ((ev->flags & 4) != 0) {
        return 1;
    }
    if ((ev->flags & 8) != 0) {
        Vu0::Q(k) = Vu0::FromFloatAt(self->impulseScale);
        Vu0::Q(push) = Vu0::MulX(Vu0::Q(ev->v30), Vu0::Q(k));
        SetColliderAnchors(self, 0, 0, 0, 0);
        ApplyColliderImpulseEvent(self, ev->strength, &ev->v20, &push);
    }
    if ((ev->flags & 0x10) == 0) {
        return 1;
    }
    if (ev->obj == GetActiveSwitchedCollider()) {
        if ((ev->flags10 & 0x10) == 0) {
            StartPadRecordPattern((PadRecord*)g_padRecord, 9, 0.3f);
        }
    }
    counter = &self->hitCount;
    self->hitCount++;
    TriggerScriptEvent(self, 0x14, 1, &counter);
    if (self->hitCount >= self->hitLimit) {
        self->desc20()->m48(self);
    }
    return 1;
}

// The larger of two floats, b first in max.s (retail's operand order, as pair_controller.cpp's).
static inline f32 MaxF(f32 a, f32 b) { return b >? a; }
s32 IsWorldBodyLimitReached(World* self, BaseObject* obj, u32 value);
struct ScatterController;
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
extern u8 g_scatterController[];
extern u8 g_zeroVector[];

// The sound a released zone plays (the block at 0x6B4, func_0013DAF0).
struct ZoneSound {
    s32 sound;              // 0x00
    f32 farRange;           // 0x04
    f32 nearRange;          // 0x08
    f32 volume;             // 0x0C
};

// Slot 72: the zone lets go, once. Each queued object it found is put back into the world
// (kinds 2 and 3 at rest, the others with a random push and spin, upright for classes 0x2E and
// 0x55) and told so (message 15); unless its flag was already set, the zone tells the object at
// 0x618 or the world's listener of its radius, scatters at its point and plays its sound. It
// leaves its parent's list unless kept, marks itself done in the flag table, tells itself
// (message 14) and its script (event 0x16 if it was done before, 2 if not).
void HandleMaskedColliderActivation(MaskedCollider* self)
{
    s32 wasSet;
    s32 i;

    if (self->hold != 0) {
        return;
    }
    wasSet = TestFlagTableBit((FlagTable*)g_flagTable, self->id688) != 0;
    if (self->quiet == 0) {
        for (i = 0; i < self->count550; i++) {
            MaskedQueueEntry* e = &self->slots[i];
            MaskedCollider* node;
            ObjectMessage msg;
            if (e->kind == 0) {
                continue;
            }
            node = (MaskedCollider*)e->node;
            if (node == 0) {
                continue;
            }
            if (IsWorldBodyLimitReached(self->world, node, MatchesObjectId(node, self->key638)) != 0) {
                continue;
            }
            if ((node->desc->flags & 1) && !((u32)(e->kind - 2) < 2)) {
                Vec4 v;
                Vec4 w;
                f32 x = RandomFloatInRange(-self->spread, self->spread);
                f32 y = RandomFloatInRange(-self->spread, self->spread);
                f32 z = RandomFloatInRange(-self->spread, self->spread);
                u128 push = Vu0::FromFloats(x, y, z);
                Vu0::Set(v, push);
                f32 s = RandomFloatInRange(self->scaleMin, self->scaleMax);
                Vu0::Set(v, Vu0::MulAddX(push, Vu0::Q(node->pos), Vu0::Scalar(s)));
                node->desc02()->m20(node, &v);
                x = RandomFloatInRange(-self->spin, self->spin);
                y = RandomFloatInRange(-self->spin, self->spin);
                z = RandomFloatInRange(-self->spin, self->spin);
                Vu0::Q(w) = Vu0::FromFloats(x, y, z);
                node->desc02()->m21(node, &w);
                if (node->desc->flags & 2) {
                    SetColliderAnchors(node, 0, 0, 0, 0);
                }
            }
            if (e->kind == 4 || e->kind == 2) {
                node->desc->m02(node);
            }
            if (!((u32)(e->kind - 2) < 2) && (node->desc->flags & 2)) {
                node->desc->m15(node, 0);
            } else {
                node->desc->m15(node, self->parent);
            }
            if (node->desc->flags & 1) {
                if ((u32)(e->kind - 2) < 2) {
                    node->desc02()->m20(node, (Vec4*)g_zeroVector);
                    node->desc02()->m21(node, (Vec4*)g_zeroVector);
                } else if (IsObjectOfKind(node, 0x2E) || IsObjectOfKind(node, 0x55)) {
                    Mat3 m;
                    RotateMatrixUpright(&node->rot, 0, &m);
                    node->desc02()->m1E(node, &m);
                    node->desc02()->m21(node, (Vec4*)g_zeroVector);
                    if (IsObjectOfKind(node, 0x2E)) {
                        SetColliderAnchors(node, 0, 0, 3, 0);
                    } else if (IsObjectOfKind(node, 0x59)) {
                        node->desc02()->m2F(node, 1);
                    } else {
                        node->desc02()->m2F(node, 3);
                    }
                }
            }
            msg.p0 = self;
            msg.target = node;
            node->desc->m0E(node, 15, &msg);
        }
        if (!wasSet) {
            Vec4 point;
            SlotMessage release;
            f32 radius;
            BaseObject* other;
            switch (self->radiusKind) {
            case 0:
                radius = MaxF(self->f2A4, self->radius3CC);
                break;
            case 1:
                radius = MaxF(self->boundRadius, self->radius3D0);
                break;
            }
            other = self->receiver;
            if (other != 0) {
                release.kind = 9;
                release.owner = self;
                release.f30 = self->f620;
                release.radius = radius;
                other->desc->m1B(other, &release);
            } else {
                SendPointEventToWorldListener((Quad16*)&self->v140, radius);
            }
            TransformPointBetweenFrames(self, 0, &self->point6A0, &point);
            ScatterObjectsAtPoint((ScatterController*)g_scatterController, &point, self->scatterCount, self->scatter6B0);
            ZoneSound* sound = (ZoneSound*)self->soundParams;
            if (sound != 0) {
                StartSoundEffect(sound->sound, 0, 0, &self->v140, sound->farRange, sound->nearRange, sound->volume, 0.0f, 0.0f, 0, 0);
            } else {
                StartSoundEffect(0x2A, 0, 0, &self->v140, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
        if (self->keep == 0) {
            self->desc->m03(self);
        }
    }
    self->hold = 1;
    SetFlagTableBit((FlagTable*)g_flagTable, self->id688);
    self->desc->m0E(self, 14, self);
    if (wasSet) {
        TriggerScriptEvent(self, 0x16, 0, 0);
    } else {
        TriggerScriptEvent(self, 2, 0, 0);
    }
}

extern u8 g_flagTable[];


// Sets the hold flag and mirrors it in the collider's flag-table bit.
void SetObjectHold(MaskedCollider* self, s32 v)
{
    self->hold = v;
    if (v != 0) {
        SetFlagTableBit((FlagTable*)g_flagTable, self->id688);
    } else {
        ClearFlagTableBit((FlagTable*)g_flagTable, self->id688);
    }
}

// Appends a key of kind 0 to the collider's list of 16 key slots (ignored when full).
void AddMaskedColliderKeyKind0(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 0;
        q->count550++;
    }
}

// Appends a key of kind 1 to the collider's list of 16 key slots (ignored when full).
void AddMaskedColliderKeyKind1(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 1;
        q->count550++;
    }
}



// Appends a key of kind 2 to the collider's list of 16 key slots (ignored when full).
void AddMaskedColliderKeyKind2(MaskedCollider* self, s32 value)
{
    if ((u32)self->count550 < 16) {
        self->slots[self->count550].key = value;
        self->slots[self->count550].kind = 2;
        self->count550++;
    }
}

// Appends a key of kind 3 to the collider's list of 16 key slots (ignored when full).
void AddMaskedColliderKeyKind3(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 3;
        q->count550++;
    }
}

// Turns the player bit (1) of the collider's accept mask on or off; the mask becomes 8 when
// nothing else would be accepted.
void SetAcceptsPlayer(MaskedCollider* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 1) & ~8;
    } else {
        self->mask &= ~1;
        if (self->mask == 0) self->mask = 8;
    }
}

void GetAcceptsPlayer(MaskedCollider* state, s32* result) {
	*result = state->mask & 1;
}

// Turns the flagged-objects bit (4) of the collider's accept mask on or off; the mask becomes 8
// when nothing else would be accepted.
void SetAcceptsFlaggedObjects(MaskedCollider* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 4) & ~8;
    } else {
        self->mask &= ~4;
        if (self->mask == 0) self->mask = 8;
    }
}

void GetAcceptsFlaggedObjects(MaskedCollider* state, s32* result) {
	*result = (state->mask >> 2) & 1;
}

// Adds an object id to the collider's list of 4 accepted ids and turns on the list bit (2) of
// its mask.
void AddAcceptedObjectId(MaskedCollider* obj, s32 value) { if ((u32)obj->count640 < 4) { obj->list644[obj->count640++] = value; obj->mask |= 2; } }

// Adds a kind to the collider's list of 4 accepted kinds and turns on the list bit (2) of its
// mask.
void AddAcceptedKind(MaskedCollider* r, s32 value)
{
    s32 n = r->count654;
    if ((u32)n < 4) {
        r->list658[n] = value;
        r->count654 = n + 1;
        r->mask |= 2;
    }
}

// Adds an entry to the collider's list of 3 and turns on the list bit (2) of its mask.
void AddMaskedColliderListEntry(MaskedCollider* obj, s32 value) { if ((u32)obj->count668 < 3) { obj->list66C[obj->count668++] = (void*)value; obj->mask |= 2; } }

// The collider's sound parameters, created on first use.
void* GetMaskedColliderSoundParams(MaskedCollider* self)
{
    if (!self->soundParams) InitSoundParams((SoundRecord**)&self->soundParams);
    return self->soundParams;
}

s32 IsObjectOfKind(BaseObject* list, s32 key);

// Whether a masked collider accepts an object by its mask: no mask accepts everything; bit 0
// accepts the active switched collider, bit 4 any object of flag 0x20, and bit 2 an object whose id
// or kind is in the collider's id list or kind list.
s32 IsObjectAccepted(MaskedCollider* self, BaseObject* msg)
{


    if (self->mask == 0) {
        return 1;
    }
    if (self->mask & 1) {
        if (msg == GetActiveSwitchedCollider()) {
            return 1;
        }
    }
    if (self->mask & 4) {
        if (msg->desc->flags & 0x20) {
            return 1;
        }
    }
    if ((self->mask & 2) == 0) {
        return 0;
    }
    for (s32 i = 0; i < self->count640; i++) {
        if (MatchesObjectId(msg, self->list644[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->count654; i++) {
        if (IsObjectOfKind(msg, self->list658[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

extern f32 g_gameTime;

// Updates the collider; state 1 moves to state 2 once the object has been tried twice or its
// time limit has passed since the stamp.
void UpdateTimedState(TimedStateObject* self, f32 dt)
{
    s32 next;

    UpdateCollider(self, dt);
    next = self->state;
    if (next != 0) {
        if (next == 1) {
            if (self->tries >= 2 || self->limit < g_gameTime - self->stamp) {
                next = 2;
            }
        }
    }
    SetTimedState(self, next);
}

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);

// After the base handling, notification 0xF about this object starts the timed state 1.
void HandleTimedStateNotification(TimedStateObject* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0xF) {
        if ((TimedStateObject*)msg->target == self) {
            SetTimedState(self, 1);
        }
    }
}

s32 IsObjectOfKind(BaseObject* list, s32 key);
// Whether the contact counts: no for an object with flag bit 55, yes when it accepts all, and
// otherwise no for an object of kind 0x27 unless its child allows it.
s32 TestTimedStateContact(TimedStateObject* node, Collider* src)
{
    s32 r;
    if (src->flags538 & (1ULL << 55)) return 0;
    if (node->acceptAll != 0) return 1;
    TimedStateFilterObject* c = node->child;
    if (c == 0 || c->f694 == 0) {
        r = IsObjectOfKind(src, 0x27);
        if (r != 0) return 0;
    }
    return 1;
}

extern f32 g_gameTime;
void FadeOutPlacedObject(Collider* self, f32 time);

// Changes the timed state and stamps the time; entering state 2 fades the object out.
void SetTimedState(TimedStateObject* self, s32 state)
{
    if (state != self->state) {
        // a field access here changes retail's code
        *(s32*)((u8*)self + 0x550) = state;
        f32 t = g_gameTime;
        self->stamp = t;
        if (state == 2) {
            (void)FadeOutPlacedObject(self, self->param);
        }
    }
}


// Initialises the masked collider to accept the player and flagged objects (mask 5).
void InitPlayerFlaggedCollider(PlayerFlaggedCollider* self)
{
    InitMaskedCollider(self);
    self->mask = 5;
    self->scatterCount = -1;
}

// Initialises the masked collider with mask 1, scale 1.0 and no anchor presets.
void InitMassScalingCollider(MassScalingCollider* self)
{
    InitMaskedCollider(self);
    self->mask = 1;
    self->scale = 1.0f;
    self->sel6C4 = -1;
    self->sel6C8 = -1;
}

// When the collider is not held or busy, takes the other object of a contact pair (by index) if
// accepted: applies its anchor presets, marks the collider busy, remembers the object and
// scales the mass by the scale.
void LatchContactObject(MassScalingCollider* self, u8* table, s32 index)
{
    BaseObject* value;
    s32 one;

    if (self->hold != 0) return;
    one = 1;
    value = *(BaseObject**)(table + ((one - index) << 6));
    if (self->busy != 0) return;
    if (IsObjectAccepted(self, value) == 0) return;
    if (self->sel6C4 != -1) SetColliderTurnAnchorPreset(self, self->sel6C4);
    if (self->sel6C8 != -1) SetColliderMoveAnchorPreset(self, self->sel6C8);
    self->busy = one;
    self->cur = value;
    self->mass = self->mass * self->scale;
}

s32 IsObjectOfKind(BaseObject* list, s32 key);

// After LatchContactObject, remembers the other object of the contact pair as the collider's
// switched collider when it is of kind 5 and accepted.
void LatchAcceptedSwitchedCollider(LatchedSwitchCollider* self, u8* table, s32 index)
{
    BaseObject* value;

    LatchContactObject(self, table, index);
    if (self->hold != 0) return;
    value = *(BaseObject**)(table + ((1 - index) << 6));
    if (IsObjectOfKind(value, 5) != 0) {
        if (IsObjectAccepted(self, value) != 0) {
            self->sel6D4 = (SwitchedCollider*)value;
        }
    }
}

struct OwnerMessage;

// Updates the masked collider and, if a switched collider was latched, sends it the owner
// message when it is still the active one, then forgets it.
void UpdateLatchedSwitchCollider(LatchedSwitchCollider* self, f32 dt)
{
    s32 local[4];
    UpdateMaskedCollider(self, dt);
    if (self->sel6D4 != 0) {
        if (self->sel6D4 != GetActiveSwitchedCollider()) {
            self->sel6D4 = 0;
            return;
        }
        InitOwnerMessage((OwnerMessage*)local, self->ownerMessageMode, self);
        SwitchedCollider* p = self->sel6D4;
        p->desc05()->m4C(p, local);
        self->sel6D4 = 0;
    }
}

// A face of a mesh's tree as the walk reads it: its plane.
struct TreeFace {
    Vec4 normal;           // 0x00
    f32 d;                  // 0x10
};

// An entry of the tree walk's stack: the part of the segment from t on, in a subtree.
struct TreeWalkEntry {
    TreeNode03* node;       // 0x00: the subtree still to walk (0: the segment is in a leaf)
    f32 t;                  // 0x04: where the part starts
    TreeNode03* solid;      // 0x08: the node behind whose face the part lies (0: in front)
    TreeFace* face;         // 0x0C: the face crossed at t
};

extern "C" void* FillMemory(void* p, s32 value, s32 size);

// The spans of the segment a-b behind the faces of the tree at root, at most max of them, into
// spans: each run of the segment behind one solid node (of the group groups gives it, when given),
// from the point it enters to the point it leaves and the faces crossed there.
s32 CollectTreeNodeSpans(TreeNode03* root, Vec4* a, Vec4* b, s32* groups, s32 max, ColliderSpan* spans)
{
    TreeWalkEntry cur;
    TreeWalkEntry stack[32];
    TreeWalkEntry* top = stack;
    ColliderSpan* span = 0;
    ColliderSpan* next = spans;
    cur.node = root;
    cur.t = 0.0f;
    cur.solid = 0;
    cur.face = 0;
    top->node = 0;
    top->t = 1.0f;
    top->solid = 0;
    top->face = 0;
    for (;;) {
        f32 one = 1.0f;
        while (cur.node == 0) {
            if (cur.solid != 0) {
                if (span != 0 && cur.face == span->face54 &&
                    (groups == 0 || span->group == groups[cur.solid - root])) {
                    {
                    f32 t = top->t;
                    Vu0::Q(span->q[1]) = Vu0::MulXSum(Vu0::Vec::Of(*a), Vu0::Vec::Scalar(1.0f - t), Vu0::Vec::Of(*b), Vu0::Vec::Scalar(t)).q;
                    }
                    span->face54 = top->face;
                    Quad16* src = (Quad16*)top->face;
                    if (src == 0) {
                        src = (Quad16*)g_zeroVector;
                    }
                    span->q[3] = *src;
                    span->time[1] = top->t;
                } else {
                    if (next - spans >= max) {
                        return max;
                    }
                    span = next++;
                    FillMemory(span, 0, 0x70);
                    Vu0::Q(span->q[0]) = Vu0::MulXSum(Vu0::Vec::Of(*a), Vu0::Vec::Scalar(1.0f - cur.t), Vu0::Vec::Of(*b), Vu0::Vec::Scalar(cur.t)).q;
                    {
                    f32 t = top->t;
                    Vu0::Q(span->q[1]) = Vu0::MulXSum(Vu0::Vec::Of(*a), Vu0::Vec::Scalar(1.0f - t), Vu0::Vec::Of(*b), Vu0::Vec::Scalar(t)).q;
                    }
                    span->face50 = cur.face;
                    span->face54 = top->face;
                    if (cur.face != 0) {
                        span->q[2] = *(Quad16*)cur.face;
                    }
                    if (top->face != 0) {
                        span->q[3] = *(Quad16*)top->face;
                    }
                    span->time[0] = cur.t;
                    span->time[1] = top->t;
                    if (groups != 0) {
                        span->group = groups[cur.solid - root];
                    }
                }
            }
            if (top <= stack) {
                return next - spans;
            }
            cur = *top;
            top--;
        }
        TreeNode03* n = cur.node;
        TreeFace* f = (TreeFace*)n->face;
        f32 da = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(*a), Vu0::Vec::Of(f->normal))) - f->d;
        f32 db = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(*b), Vu0::Vec::Of(f->normal))) - f->d;
        if (da <= 0.0f && db <= 0.0f) {
            cur.solid = n;
            cur.node = n->back;
            continue;
        }
        if (0.0f < da && 0.0f < db) {
            cur.solid = 0;
            cur.node = cur.node->front;
            continue;
        }
        f32 t = da / (da - db);
        f32 dIn = db * cur.t + (one - cur.t) * da;
        f32 dOut = db * top->t + (one - top->t) * da;
        if (cur.t < t && t < top->t) {
            top++;
            top->t = t;
            top->face = (TreeFace*)cur.node->face;
            if (dIn <= 0.0f) {
                top->solid = 0;
                top->node = cur.node->front;
            } else {
                top->solid = cur.node;
                top->node = cur.node->back;
            }
        }
        if (dIn < 0.0f || (dIn == 0.0f && dOut <= 0.0f)) {
            cur.solid = cur.node;
            cur.node = cur.node->back;
        } else {
            cur.solid = 0;
            cur.node = cur.node->front;
        }
    }
}

// A node of a plane tree: its plane and the two sides (the boxes D_002613D0 and D_002613E0 are
// such nodes, with a box for a plane); func_0013E430 appends the nodes of the pieces it cuts.
struct PlaneTreePlane {
    Vec4 normal;           // 0x00
    f32 offset;             // 0x10
};

struct PlaneTreeNode {
    PlaneTreePlane* plane;  // 0x00
    PlaneTreeNode* below;   // 0x04
    PlaneTreeNode* above;   // 0x08
};

struct PlaneTreeOutput {
    PlaneTreeNode* cur;     // 0x00: the next node to write
};

// Classifies a point against a tree of planes within eps: gives 0 (outside), 1 (inside) or 2 (near
// a plane, in which case the part of the tree that the point's neighbourhood reaches is copied into
// out). It follows one side while the point is more than eps from the plane, and both sides when it
// is within eps.
s32 QueryPlaneTreePoint(PlaneTreeNode* node, Vec4* p, f32 eps, PlaneTreeOutput* out)
{
    f32 d;
    s32 result;
    while (node != 0) {
        PlaneTreePlane* pl = node->plane;
        f32 dot = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(*p), Vu0::Q(pl->normal)));
        d = dot - pl->offset;
        if (eps < d) {
            node = node->above;
            continue;
        }
        if (d < -eps) {
            node = node->below;
            continue;
        }
        s32 lo;
        s32 hi;
        PlaneTreeNode* loNode;
        PlaneTreeNode* hiNode;
        if (node->below != 0) {
            lo = QueryPlaneTreePoint(node->below, p, eps, out);
            loNode = out->cur - 1;
        } else {
            lo = 0;
        }
        if (node->above != 0) {
            hi = QueryPlaneTreePoint(node->above, p, eps, out);
            hiNode = out->cur - 1;
        } else {
            hi = 1;
        }
        if (lo == hi && hi != 2) {
            result = hi;
            goto done;
        }
        out->cur->plane = node->plane;
        switch (lo) {
        case 0:
            out->cur->below = 0;
            break;
        case 1:
            out->cur->below = (PlaneTreeNode*)g_planeTreeEmptyBelow;
            break;
        case 2:
            out->cur->below = loNode;
            break;
        }
        switch (hi) {
        case 0:
            out->cur->above = (PlaneTreeNode*)g_planeTreeEmptyAbove;
            break;
        case 1:
            out->cur->above = 0;
            break;
        case 2:
            out->cur->above = hiNode;
            break;
        }
        result = 2;
        out->cur++;
        goto done;
    }
    result = eps < d;
done:
    return result;
}

LINKER_REMNANT(func_0013E650);

ASM_FUNC(func_0013E658);

void* AllocateFrontMemory(s32 size);

// Copies a collision tree for a copy of its mesh: the counts, and a new node array (from front
// memory) in which every face and node pointer is moved by the offset between the old mesh and the
// new one.
void CloneTreeNodes(CollisionMesh* self, MeshTree* src, CollisionMesh* base, MeshTree* dst)
{
    dst->count = src->count;
    dst->count2 = src->count2;
    dst->nodes = (TreeNode03*)AllocateFrontMemory(src->count * 12);
    for (s32 i = 0; i < dst->count; i++) {
        TreeNode03* s = &src->nodes[i];
        TreeNode03* d = &dst->nodes[i];
        d->face = (void*)((s32)base->faces + ((s32)s->face - (s32)self->faces));
        d->back = s->back != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->back - (s32)src->nodes)) : 0;
        d->front = s->front != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->front - (s32)src->nodes)) : 0;

    }
}


// Looks up each id of the pair's list under its owner and, for each object found, adds it to
// the queued objects and starts it.
void ResolveZoneObjects(void* self, ZoneSideRecord* list, void* context)
{
    s32 n = list->seen.count;
    s32* items = list->seen.values;
    for (s32 i = 0; i < n; i++) {
        void* object = FindFirstObjectById((World*)self, 0x104, items[i], context);
        if (object) {
            AppendToQueuedObjects(list, (BaseObject*)object);
            ResolveAndStartObject((BaseObject*)object);
        }
    }
}


// Whether the object matches any id of the list.
s32 IsObjectInIdList(IdQueue* set, void* key)
{
    s32 i = set->count - 1;
    s32* base = set->values;
    if (i >= 0) {
        s32* p = (s32*)(i * 4 + (s32)base);
        do {
            if (MatchesObjectId((BaseObject*)key, *p) != 0) {
                return 1;
            }
            i--;
            p--;
        } while (i >= 0);
    }
    return 0;
}

// Adds an object to the pair's list of queued objects; false once the list has 16.
bool AppendToQueuedObjects(ZoneSideRecord* pair, BaseObject* value) {
	pair->queued.values[pair->queued.count++] = value;
	return pair->queued.count < 16;
}

// Adds a value to a queue of at most 16; false once it is full.
bool AppendToObjectQueue(IdQueue* queue, s32 value) {
	queue->values[queue->count++] = value;
	return queue->count < 16;
}

extern u8 g_flagTable[];

// Gives the zone record a flag-table index and no sequence.
void InitZoneRecord(TriggerZoneRecord* s)
{
    s->id120 = TakeFlagTableIndex((FlagTable*)g_flagTable);
    s->sequenceId = -1;
}







// Takes the children of a collider that are of flag 0x40 into the zone record's first queue (and
// records the collider as its owner), skipping the ones already seen in either of its queues.
void CollectZoneChildren(TriggerZoneRecord* self, Collider* a1)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &a1->children);
    self->owner = a1;
    BaseObject* node;
    while ((node = ListWalkNextBase::Of(&it)) != 0) {
        if (node->desc->flags & 0x40) {
            if (IsObjectInIdList(&self->pairs[1].seen, node) == 0) {
                if (IsObjectInIdList(&self->pairs[0].seen, node) == 0) {
                    AppendToQueuedObjects(&self->pairs[0], node);
                }
            }
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
}

extern u8 g_flagTable[];

void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

// Starts a zone record: mode -1, resolves the objects of both pairs, and, for a persistent
// record whose flag-table bit is set, queues DeferZoneRecordActivation.
void StartZoneRecord(TriggerZoneRecord* self)
{
    s32 n;
    ZoneSideRecord* p;
    void* target;

    self->mode = -1;
    target = self->owner->world;
    p = self->pairs;
    n = 1;
    do {
        ResolveZoneObjects(target, p, self->owner);
        p++;
    } while (--n >= 0);
    if (self->persistent != 0) {
        if (TestFlagTableBit((FlagTable*)g_flagTable, self->id120)) {
            AppendQueuedCall((World*)target, (void*)DeferZoneRecordActivation, self, 0, 0);
        }
    }
}

void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

// Queued call: the first run (mode 0) queues itself once more with mode 0xC, and the run after
// that activates the zone record, so the activation is deferred by a queue pass.
void DeferZoneRecordActivation(void* selfp, s32 mode)
{
    TriggerZoneRecord* self = (TriggerZoneRecord*)selfp;
    if (mode == 0) {
        AppendQueuedCall(self->owner->world, (void*)DeferZoneRecordActivation, self, 0xC, 0);
    } else {
        ActivateZoneRecord(self, 1, 1);
    }
}

struct ZoneTargetEntry;
// Sets a zone target entry (a flag, then id, key and state) in the zone's table of 8.
void SetZoneEntry(TriggerZoneRecord* self, s32 a, s32 b, s32 c, s32 d)
{
    UpsertKeyedEntry((ZoneTargetEntry*)self->table14C, 8, &self->count148, a, b, c, d);
}

extern f32 g_gameTime;
void ClearRootTries(PlacedObject* self);

// Changes the zone record's mode and stamps the time; going from 0 to 1 activates the record,
// going to 0 from any mode but -1 deactivates it.
void SetZoneMode(TriggerZoneRecord* self, s32 b)
{
    s32 old = self->mode;
    if (b == old) {
        return;
    }
    s32 s1 = 0;
    if (old == 0) {
        s1 = (b == 1);
    }
    s32 s2 = 0;
    if (old != -1) {
        if (b == 0) {
            s2 = 1;
        }
    }
    // a field access here changes retail's code
    *(s32*)((u8*)self + 0x12C) = b;
    self->stamp = g_gameTime;
    ClearRootTries(self->owner);
    if (s1 != 0) {
        ActivateZoneRecord(self, 0, 0);
    }
    if (s2 != 0) {
        DeactivateZoneRecord(self, 0);
    }
}

// An entry of TriggerZoneRecord::table14C (func_0013EC00 adds or updates one, func_0013ECB0 applies a
// list of them): an object's id, a key it answers to (-1 any), and the states to set it to.
struct ZoneTargetEntry {
    s32 id;                 // 0x00
    s32 key;                // 0x04: -1 matches any
    s32 onState;            // 0x08: when the flag is set
    s32 offState;           // 0x0C: otherwise
};

// Sets the on-state (flag set) or off-state of the entry with id k1 and key k2 (or any key),
// adding the entry if there is room (capacity cap); 0 when the table is full.
s32 UpsertKeyedEntry(ZoneTargetEntry* tab, s32 cap, s32* count, s32 flag, s32 k1, s32 k2, s32 val)
{
    for (s32 i = 0; i < *count; i++) {
        ZoneTargetEntry* p = &tab[i];
        if (p->id == k1 && (p->key == -1 || p->key == k2)) {
            if (flag != 0) {
                p->onState = val;
            } else {
                p->offState = val;
            }
            return 1;
        }
    }
    s32 n = *count;
    if (n + 1 >= cap) {
        return 0;
    }
    *count = n + 1;
    ZoneTargetEntry* e = (ZoneTargetEntry*)((n << 4) + (s32)tab);
    e->id = k1;
    e->key = k2;
    if (flag != 0) {
        e->onState = val;
        e->offState = -1;
    } else {
        e->offState = val;
        e->onState = -1;
    }
    return 1;
}

void* FindObjectHandle(PlacedObject* self, s32 key);

// For each of n entries, gathers the object with the entry's id, finds the walker handle with the
// entry's key on it and sets that walker's target to the entry's on-state (flag set) or off-state
// (flag clear), unless it is -1. Stops at the first entry whose object cannot be found.
void SetGatheredWalkerTargets(void* self, s32 n, ZoneTargetEntry* ent, void* arg, s32 flag)
{
    s32 count = 0;
    void* out;
    if (n > 0) {
        ZoneTargetEntry* p = ent;
        do {
            if (GatherObjectsByMode((World*)self, 0x304, p->id, arg, 1, &out) != 1) {
                return;
            }
            void* v = FindObjectHandle((PlacedObject*)out, p->key);
            if (v == 0) {
                count++;
            } else {
                s32 k;
                if (flag != 0) {
                    k = p->onState;
                } else {
                    k = p->offState;
                }
                if (k != -1) {
                    SetStateWalkerTarget((StateWalker*)v, k);
                }
                count++;
            }
            p++;
        } while (count < n);
    }
}

struct StepSequence;
void* FindOrCreateSeekedAnimationPlayer(void* self, BaseObject* key, s32 a2, s32 a3, f32 fa, f32 fb);

// An object queued in a zone (func_0013ED90): the id of the object it goes to and a flag.
struct ZoneQueuedObject { u8 pad[0x40]; s32 key40; s32 flag44; };

// Runs a zone record's queued objects for a mode: seeks the animation players of each (forward or
// backward by the sign of the seek time and the reversed flag), sets the gathered walker targets
// and, when the record has a step sequence, resets it (mode 1) or has it choose its state (mode 0).
void RunZoneRecordEntries(TriggerZoneRecord* self, s32 mode, s32 p, s32 q)
{
    s32 n = self->pairs[mode].queued.count;
    {
        BaseObject** list = self->pairs[mode].queued.values;
        s32 i;
        for (i = 0; i < n; i++) {
            ZoneQueuedObject* obj = (ZoneQueuedObject*)list[i];
            void* other;
            s32 dir;
            if (MatchesObjectId(self->owner, obj->key40)) {
                other = self->owner;
            } else if (obj->key40 != -1) {
                other = FindFirstObjectByIdMode4(self->owner->world, obj->key40, self->owner);
            } else {
                other = 0;
            }
            if (p != 0 && obj->flag44 == 0) {
                f32 t = self->seekTime;
                dir = 0;
                if (t >= 0.0f) {
                    dir = 2;
                }
                FindOrCreateSeekedAnimationPlayer(obj, (BaseObject*)other, dir, 0, 0.0f, t);
            } else if (self->reversed != 0) {
                f32 t = self->seekTime;
                dir = 0;
                if (t < 0.0f) {
                    dir = 2;
                }
                FindOrCreateSeekedAnimationPlayer(obj, (BaseObject*)other, dir, 0, 0.0f, t);
            } else {
                FindOrCreateSeekedAnimationPlayer(obj, (BaseObject*)other, 1, 0, 0.0f, self->seekTime);
            }
        }
    }
    SetGatheredWalkerTargets(self->owner->world, self->count148, (ZoneTargetEntry*)self->table14C, self->owner, mode == 0);
    if (self->sequenceId != -1 && q == 0) {
        void* t = FindFirstObjectByIdMode4(self->owner->world, self->sequenceId, self->owner);
        if (mode != 0) {
            if (mode == 1) {
                ResetStepSequence((StepSequence*)t);
            }
            return;
        }
        ChooseStepSequenceState((StepSequence*)t);
    }
}

enum Kind_13EF50 { kind_13EF50_2 = 2 };

extern u8 g_flagTable[];

void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// Activates a zone record: raises script event 2 (0x16 when q is set) on its owner, plays its sound
// unless silent, runs its queued entries, leaves the active mode unless it stays active, sets its
// saved flag if persistent and sends its owner notification 0xC.
void ActivateZoneRecord(TriggerZoneRecord* self, s32 p, s32 q)
{
    if (q != 0) {
        TriggerScriptEvent(self->owner, 0x16, 0, 0);
    } else {
        TriggerScriptEvent(self->owner, 2, 0, 0);
    }
    if (self->silent == 0) {
        if (q == 0) {
            StartSoundEffect(kind_13EF50_2, 0, self->owner, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    RunZoneRecordEntries(self, 0, p, q);
    if (self->staysActive == 0) {
        SetZoneMode(self, 2);
    }
    if (self->persistent != 0) {
        SetFlagTableBit((FlagTable*)g_flagTable, self->id120);
    }
    self->owner->desc->m0E(self->owner, 0xC, self);
}


// Triggers script event 3, runs the record's off entries and tells the owner (message 13).
void DeactivateZoneRecord(TriggerZoneRecord* self, s32 p)
{
    TriggerScriptEvent(self->owner, 3, 0, 0);
    RunZoneRecordEntries(self, 1, p, 0);
    Collider* o = self->owner;
    o->desc->m0E(o, 13, self);
}


// Initialises the collider and its zone record.
void InitTriggerZone(TriggerZone* self)
{
    InitCollider(self);
    InitZoneRecord(&self->zone);
}


// Loads the collider and collects the zone's children.
void LoadTriggerZone(TriggerZone* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    CollectZoneChildren(&self->zone, self);
}


// Adds a quad to the trigger zone; an object matching id 0x200 puts its quad first (shifting
// the others up), any other goes last.
void AddTriggerZoneQuad(TriggerZone* self, void* a1, TriggerZoneQuad* q)
{
    s32 n = self->quadCount;
    s32 idx;
    if (MatchesObjectId((BaseObject*)a1, 0x200)) {
        idx = 0;
        if (n > 0) {
            u8* p = (u8*)self + n * 16;
            s32 o = n * 16;
            // address arithmetic over a variable index
            MoveMemory((u8*)(o + (s32)self) + 0x7C0, &self->quads[0], o);
        }
    } else {
        idx = n;
    }
    self->quads[idx] = *q;
    self->quadCount++;
}

// The 0x30-byte entry copied as three quadwords.
struct __attribute__((aligned(16))) ZoneEntryBlock { u8 b[0x30]; };

// n rotations moved by one place: the size is the inline's own product, which retail multiplies
// again apart from the destination's.
static inline void MoveRotations(void* dst, void* src, s32 n) { MoveMemory(dst, src, n * 0x30); }

// Adds a rotation entry to the trigger zone; an object matching id 0x200 puts its entry first
// (shifting the others up), any other goes last.
void AddTriggerZoneRotation(TriggerZone* self, BaseObject* a1, Mat3* e)
{
    s32 n = self->count7E0;
    s32 idx;
    if (MatchesObjectId(a1, 0x200)) {
        idx = 0;
        if (n > 0) {
            MoveRotations(&self->entries[n], &self->entries[0], n);
        }
    } else {
        idx = n;
    }
    *(ZoneEntryBlock*)&self->entries[idx] = *(ZoneEntryBlock*)e;
    self->count7E0++;
}


struct ZoneListFrame {
    void* list;
    void* cursor;
    s32 next_off;
    ZoneListFrame* prev;
    ZoneListFrame(ObjectList* l)
    {
        list = l;
        cursor = l;
        ZoneListFrame* p = (ZoneListFrame*)g_activeListFrames;
        next_off = l->offset;
        g_activeListFrames = (ListFrame*)this;
        prev = p;
    }
    ~ZoneListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

void StartPlacedObject(PlacedObject* self);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void TransformRotationBetweenFrames(PlacedObject* from, PlacedObject* to, Mat3* in, Mat3* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void CopyMemory(void* dst, void* src, u32 size);
extern const Vec4 g_unitXVector;
extern const Vec4 g_unitYVector;
extern const Vec4 g_unitZVector;

static inline Vec4* RowOf(Mat3* m, s32 i)
{
    return &m->r[i];
}

// The trigger zone's start method: starts the placed object and its zone record, sets mode 0 and
// takes its child markers: in state 0 each quad marker (kind 0x7E) becomes a stored point, in state
// 1 each rotation marker (0x73) a stored rotation, and the kind 0x76 child is kept as the marker
// node. It then constrains the points (state 0) or works out the plane vectors (state 1).
void StartTriggerZone(TriggerZone* self)
{
    ZoneListFrame frame(&self->children);
    Vec4 v;
    StartPlacedObject(self);
    StartZoneRecord(&self->zone);
    SetTriggerZoneMode(self, 0);
    s32 state = self->state;
    void* head = *(void**)frame.cursor;
    frame.cursor = (void*)((s32)head + frame.next_off);
    PlacedObject* node = (PlacedObject*)head;
    if (node != 0) {
        do {
            if (state == 0 && IsObjectOfKind(node, 0x7E)) {
                TransformPointBetweenFrames(self, (PlacedObject*)self->parent, (Vec4*)&((TransformObject*)node)->pos, &v);
                AddTriggerZoneQuad(self, node, (TriggerZoneQuad*)&v);
            } else if (state == 1 && IsObjectOfKind(node, 0x73) && !IsObjectOfKind(node, 0x75)) {
                Mat3 m;
                TransformRotationBetweenFrames(self, (PlacedObject*)self->parent, (Mat3*)&((TransformObject*)node)->rot, &m);
                AddTriggerZoneRotation(self, node, &m);
                node->desc->m03(node);
            }
            if (IsObjectOfKind(node, 0x76)) {
                self->markerNode = (s32)node;
            }
            void* next = *(void**)frame.cursor;
            frame.cursor = (void*)((s32)next + frame.next_off);
            node = (PlacedObject*)next;
        } while (node != 0);
    }
    switch (state) {
    case 0: {
        s32 i;
        for (i = 0; i < self->quadCount; i++) {
            Vu0::Q(v) = Vu0::Sub(Vu0::Q(self->quads[i]), Vu0::Q(self->pos));
            ConstrainColliderVector(self, &self->v440, &v, &v, 0);
            Vu0::Q(self->quads[i]) = Vu0::Add(Vu0::Q(self->pos), Vu0::Q(v));
        }
        u128 d = Vu0::Sub(Vu0::Q(self->quads[self->quadCount - 1]), Vu0::Q(self->quads[0]));
        Vu0::Q(self->v860) = d;
        Vu0::Q(self->v860) = Vu0::DivX(d, Vu0::Length(d));
        Vu0::Q(self->v870) = Vu0::MulX(Vu0::Q(self->v860), Vu0::Scalar(-1.0f));
        break;
    }
    case 1: {
        Mat3 rows;
        Vec4 a;
        Vec4 b;
        Vec4 dir;
        s32 k = self->count7E0 - 1;
        TransformDirectionBetweenFrames((PlacedObject*)self->parent, self, &self->v460, &dir);
        Vec4* side;
        Vec4* last;
        const Vec4* up;
        if (0.9f < dir.x) {
            rows.r[0] = ((Mat3*)self->entries)->r[2];
            side = &((Mat3*)self->entries)->r[1];
            up = &g_unitYVector;
            last = RowOf((Mat3*)&self->entries[k], 1);
            rows.r[1] = ((Mat3*)&self->entries[k])->r[2];
        } else if (0.9f < dir.y) {
            rows.r[0] = ((Mat3*)self->entries)->r[0];
            side = &((Mat3*)self->entries)->r[2];
            up = &g_unitZVector;
            last = RowOf((Mat3*)&self->entries[k], 2);
            rows.r[1] = ((Mat3*)&self->entries[k])->r[0];
        } else {
            rows.r[0] = ((Mat3*)self->entries)->r[1];
            side = &((Mat3*)self->entries)->r[0];
            up = &g_unitXVector;
            last = RowOf((Mat3*)&self->entries[k], 0);
            rows.r[1] = ((Mat3*)&self->entries[k])->r[1];
        }
        if (self->parent != 0) {
            rows.r[2] = self->pos;
        } else {
            rows.r[2] = self->v140;
        }
        CopyMemory(&self->v860, &rows, 0x20);
        Vu0::Q(self->v850) = Vu0::MulX(Vu0::Q(*up), Vu0::Scalar(100.0f));
        Vu0::Q(a) = Vu0::MulAddX(Vu0::Q(rows.r[2]), Vu0::Q(*side), Vu0::Scalar(100.0f));
        Vu0::Q(b) = Vu0::MulAddX(Vu0::Q(rows.r[2]), Vu0::Q(*last), Vu0::Scalar(100.0f));

        Vu0::Q(v) = Vu0::Sub(Vu0::Q(b), Vu0::Q(a));
        if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v870), Vu0::Q(v)))) {
            Vu0::Q(self->v870) = Vu0::MulX(Vu0::Q(self->v870), Vu0::Scalar(-1.0f));
        } else {
            Vu0::Q(self->v860) = Vu0::MulX(Vu0::Q(self->v860), Vu0::Scalar(-1.0f));
        }
        break;
    }
    case 2:
        break;
    }
}


// Copies the collider but keeps the zone's own flag-table index and points the zone's owner at
// itself.
void CopyTriggerZone(TriggerZone* self, TriggerZone* src)
{
    s32 keep = self->zone.id120;
    CopyCollider(self, src);
    self->zone.id120 = keep;
    self->zone.owner = self;
}


void SetTriggerZoneMode(TriggerZone* state, s32 mode) {
	SetZoneMode(&state->zone, mode);
}

s32 IsObjectOfKind(BaseObject* list, s32 key);

// Whether an object may set a trigger zone off: if the zone lists ids to accept, the object must
// match one, otherwise it must match none of the ids to refuse; the same then for the lists of
// kinds. With no lists every object passes.
s32 PassesTriggerFilters(TriggerZone* self, void* arg)
{
    if (self->countIdsIn > 0) {
        s32 i;
        for (i = 0; i < self->countIdsIn; i++) {
            if (MatchesObjectId((BaseObject*)arg, self->idsIn[i]) != 0) {
                break;
            }
        }
        if (i >= self->countIdsIn) {
            return 0;
        }
    } else if (self->countIdsOut > 0) {
        s32 i;
        for (i = 0; i < self->countIdsOut; i++) {
            if (MatchesObjectId((BaseObject*)arg, self->idsOut[i]) != 0) {
                break;
            }
        }
        if (i < self->countIdsOut) {
            return 0;
        }
    }
    if (self->countKindsIn > 0) {
        s32 i;
        for (i = 0; i < self->countKindsIn; i++) {
            if (IsObjectOfKind((BaseObject*)arg, self->kindsIn[i]) != 0) {
                break;
            }
        }
        if (i >= self->countKindsIn) {
            return 0;
        }
    } else if (self->countKindsOut > 0) {
        s32 i;
        for (i = 0; i < self->countKindsOut; i++) {
            if (IsObjectOfKind((BaseObject*)arg, self->kindsOut[i]) != 0) {
                break;
            }
        }
        if (i < self->countKindsOut) {
            return 0;
        }
    }
    return 1;
}

// The vector func_0013F8A0 loads.
extern const Vec4 D_00249DD0 = { 3.4028235e+38f, 0.0f, 0.0f, 0.0f };

ASM_FUNC(func_0013F8A0);

extern "C" f32 Arccosine(f32 x);

// Gives the index of the zone's rotation entry closest to the zone's own rotation (the largest
// rotation cosine of the product), and through out that angle with Arccosine; 0 when there are
// none.
s32 FindLargestEntryIndex(TriggerZone* s, f32* out)
{
    Mat3U loc;
    f32 best = 0.0f;
    s32 idx;
    s32 i;

    if (s->count7E0 == 0) {
        return 0;
    }
    for (i = s->count7E0 - 1; i >= 0; i--) {
        ZoneRotationEntry* e = &s->entries[i];
        MultiplyMatrices3x3(&s->rot, (Mat3*)e, (Mat3*)&loc);
        f32 t = GetMatrixRotationCosine((f32*)&loc);
        if (best < t) {
            best = t;
            idx = i;
        }
    }
    if (out != 0) {
        *out = Arccosine(best);
    }
    return idx;
}

extern u8 g_zeroVector[];


// The trigger zone's per-step motion: the collider's, then, in state 0 or 1, steers the zone toward
// the stored point (state 0) or rotation (state 1) of its chosen index, or the first one while in
// mode 4.
void StepTriggerZone(TriggerZone* self, f32 t)
{
    StepCollider(self, t);
    switch (self->state) {
    case 0:
        if (self->quadCount != 0) {
            u8* p = (u8*)self->quads;
            if (self->zone.mode != 4) {
                p += self->chosenIndex << 4;
            }
            SteerColliderTowardPosition(self, (Vec4*)p, (f32*)self->p20C, (Vec4*)g_zeroVector, (f32*)self->p210, t);
        }
        break;
    case 1:
        if (self->count7E0 != 0) {
            u8* p = (u8*)self->entries;
            if (self->zone.mode != 4) {
                p += self->chosenIndex * 0x30;
            }
            SteerColliderTowardRotation(self, (Mat3*)p, (f32*)self->p214, (Vec4*)g_zeroVector, (f32*)self->p218, t);
        }
        break;
    }
}

struct PooledContact;

// Frees the trigger zone's pooled contacts and makes new ones for the zone's walls: two planes,
// from the stored points (state 0) or the rotation planes, each tested against the zone's own
// position; a wall the position is past (by more than 0.0001) gets one contact of kind 10 with no
// bounce.
void ReleaseTriggerZoneContacts(TriggerZone* self)
{
    Vec4 v[2];
    Vec4 w[2];
    Vec4 p;
    Vec4* where;
    f32 fa;
    f32 fb;
    f32 ga;
    f32 gb;
    s32 i;

    if (self->quadCount == 0 && self->count7E0 == 0) {
        return;
    }
    if (self->contacts4B4 != 0) {
        FreePooledContactChain(self->world, self->contacts4B4);
        self->contacts4B4 = 0;
    }
    for (i = 0; i < 2; i++) {
        if (i < self->quadCount) {
            TransformPointBetweenFrames((PlacedObject*)self->parent, 0, (Vec4*)&self->quads[i], &v[i]);
        }
        TransformDirectionBetweenFrames((PlacedObject*)self->parent, 0, &(&self->v860)[i], &w[i]);
    }
    if (self->state == 0) {
        where = &self->v140;
        fa = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(w[0])));
        ga = Vu0::ToFloat(Vu0::Dot(Vu0::Q(v[0]), Vu0::Q(w[0])));
        gb = Vu0::ToFloat(Vu0::Dot(Vu0::Q(v[1]), Vu0::Q(w[1])));
        fb = -fa;
    } else {
        TransformPointBetweenFrames(self, 0, &self->v850, &p);
        where = &p;
        ga = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(w[0])));
        gb = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(w[1])));
        fa = Vu0::ToFloat(Vu0::Dot(Vu0::Q(p), Vu0::Q(w[0])));
        fb = Vu0::ToFloat(Vu0::Dot(Vu0::Q(p), Vu0::Q(w[1])));
    }
    f32 x = fa - ga;
    if (x < -1e-4f) {
        BodyContact* c = (BodyContact*)CreatePooledContact(x, self, 0, where, &w[0], 10, 0, 0, &self->contacts4B4);
        c->bounce = 0.0f;
    } else {
        x = fb - gb;
        if (x < -1e-4f) {
            BodyContact* c = (BodyContact*)CreatePooledContact(x, self, 0, where, &w[1], 10, 0, 0, &self->contacts4B4);
            c->bounce = 0.0f;
        }
    }
}

extern Player* g_player;
extern f32 g_gameTime;

s32 FindNearestStoredPoint(TriggerZone* self, f32* out);
void ClearRootTries(PlacedObject* self);

// The trigger zone's per-frame update: after the collider's, sets the zone mode by its state. Mode
// 2 times out to mode 4, and mode 4 settles to mode 0 or 1. In modes 0 and 1, states 2 to 4 test
// the player's marker or a contact that passes the filters, and the others test how near the
// nearest stored point or largest entry is (under 2 units or 0.1), and set the chosen index.
void UpdateTriggerZone(TriggerZone* self, f32 dt)
{
    UpdateCollider(self, dt);
    switch (self->zone.mode) {
    case 2: {
        Player* g = g_player;
        f32 t;
        if (g) {
            if (g->state == 3 && (s32)g->boundObject == self->markerNode) self->zone.stamp = g_gameTime;
        }
        t = self->zone.duration;
        if (0.0f <= t) {
            if (t < g_gameTime - self->zone.stamp) SetTriggerZoneMode(self, 4);
        }
        break;
    }
    case 3:
        break;
    case 4: {
        s32 r = -1;
        switch (self->state) {
        case 0: if (!FindNearestStoredPoint(self, 0)) r = 1; break;
        case 1: if (!FindLargestEntryIndex(self, 0)) r = 1; break;
        case 2:
        case 4: r = 1; break;
        case 3: r = 0; break;
        }
        if (r != -1) SetTriggerZoneMode(self, r);
        break;
    }
    case 0:
    case 1: {
        s32 r = self->zone.mode;
        s32 st = self->state;
        switch (st) {
        case 3:
            break;
        case 4: {
            Player* g = g_player;
            r = 0;
            if (g) {
                if (g->state == 3) r = (s32)g->boundObject == self->markerNode;
            }
            break;
        }
        case 2: {
            Collider* s4 = self->root03();
            ContactRow03* l = s4->contacts->head;
            r = 0;
            for (; l; l = l->next) {
                BodyContact* n = l->head;
                for (; n; n = n->next) {
                    s32 k = n->end[0].body != s4;
                    if (((ContactEnd03*)((u8*)n + (k << 6)))->part == self) {
                        if (PassesTriggerFilters(self, n->end[1 - k].body)) { r = 1; goto done; }
                    }
                }
            }
            break;
        }
        default: {
            f32 v[2];
            s32 s0;
            s32 lt;
            s32 mode = self->zone.mode;
            r = mode;
            if (st == 0) {
                s0 = FindNearestStoredPoint(self, &v[0]);
                lt = v[0] < 2.0f;
            } else {
                s0 = FindLargestEntryIndex(self, &v[1]);
                lt = v[1] < 0.1f;
            }
            if (lt) {
                if (s0 == 0 && mode == 1) r = 0;
                else if (s0 == 1 && !mode) r = 1;
            }
            if (self->chosenIndex != s0) {
                ClearRootTries(self);
                self->chosenIndex = s0;
            }
            break;
        }
        }
    done:
        SetTriggerZoneMode(self, r);
        break;
    }
    }
}


// After the base event handling, a handled event whose flags lack bit 4 sets mode 1 on a zone
// that is in state 3 and in mode 0.
s32 HandleTriggerZoneEvent(TriggerZone* a0, void* a1)
{
    s32 r = HandleObjectEvent(a0, (ObjectEvent*)a1);
    if (r != 0 && (((ObjectEvent*)a1)->eventFlags & 4) == 0 && a0->state == 3 && a0->zone.mode == 0) {
        SetTriggerZoneMode(a0, 1);
    }
    return r;
}


// Initialises the collider and its zone record, sets flag bit 43 and sets both anchors to 3.
void InitZoneCollider(ZoneCollider* self)
{
    u64 m = 0x8000;
    InitCollider(self);
    InitZoneRecord(&self->zone);
    m <<= 28;
    self->flags538 = self->flags538 | m;
    SetColliderAnchors(self, 3, 0, 3, 0);
}


// Loads the collider and collects its zone's children; a collider that reports what is inside
// keeps its zone active.
void LoadZoneCollider(ZoneCollider* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    CollectZoneChildren(&self->zone, self);
    if (self->reportInside != 0) {
        self->zone.staysActive = 1;
    }
}

void StartPlacedObject(PlacedObject* self);


// Starts the placed object and its zone record, sets mode 0, resolves each listed id to its
// first object (mode 4 lookup) into the object list, and, when no ids were listed, makes it
// test the active collider.
void StartZoneCollider(ZoneCollider* self)
{
    StartPlacedObject(self);
    StartZoneRecord(&self->zone);
    SetZoneColliderMode(self, 0);
    for (s32 i = 0; i < self->countIds; i++) {
        void* p = FindFirstObjectByIdMode4(self->world, self->ids[i], self);
        if (p != 0) {
            s32 n = self->countObjs;
            self->objs[n] = (s32)p;
            self->countObjs = n + 1;
        }
    }
    if (self->countIds == 0) {
        self->testsActiveCollider = 1;
    }
}



// Copies the collider but keeps the zone's own flag-table index and points the zone's owner at
// itself.
void CopyZoneCollider(ZoneCollider* self, ZoneCollider* src)
{
    s32 saved = self->zone.id120;
    CopyCollider(self, src);
    self->zone.id120 = saved;
    self->zone.owner = self;
}



void SetZoneColliderMode(ZoneCollider* self, s32 flag)
{
    SetZoneMode(&self->zone, flag);
}

// An object the zone watches (ZoneCollider's objs): its class, and the two places its position is.
struct ZoneTarget {
    const BaseObjectDescriptor* desc;     // 0x00
    u8 pad04[0x40 - 0x04];
    Vec4 v40;              // 0x40
    u8 pad50[0x140 - 0x50];
    Vec4 v140;             // 0x140
};

void CopyMemory(void* dst, void* src, u32 size);

// The zone collider's per-frame update: after the collider's, a timed mode (2) ends when its
// duration is over. Otherwise it tests whether any of its objects (or the active switched collider)
// is inside its radius or plane tree, sets mode 1 if so and 0 if not, and, with reportInside, keeps
// the list of those inside and sends script event 0xC when it changes.
void UpdateZoneCollider(ZoneCollider* self, f32 dt)
{
    ZoneTarget* found[8];
    Vec4 pos;
    ZoneTarget* obj;
    UpdateCollider(self, dt);
    switch (self->zone.mode) {
    case 2:
        if (0.0f <= self->zone.duration && self->zone.duration < g_gameTime - self->zone.stamp) {
            if (self->timedModeNext != 0) {
                SetZoneColliderMode(self, 1);
            } else {
                SetZoneColliderMode(self, 0);
            }
        }
        return;
    case 0:
    case 1:
        break;
    case 3:
    default:
        return;
    }
    s32 n = 0;
    s32 hit = 0;
    if (self->testsActiveCollider != 0) {
        obj = (ZoneTarget*)GetActiveSwitchedCollider();
        if (obj != 0) {
            self->objs[0] = (s32)obj;
            self->countObjs = 1;
        } else {
            self->countObjs = 0;
        }
    }
    for (s32 i = 0; i < self->countObjs; i++) {
        obj = (ZoneTarget*)self->objs[i];
        if (obj->desc->flags & 1) {
            pos = obj->v140;
        } else if (IsObjectOfKind((Collider*)obj, 0x6D)) {
            pos = obj->v40;
        } else if (IsObjectOfKind((Collider*)obj, 0x7E)) {
            ConvertPositionToWorld((BaseObject*)obj, &pos);
        } else if (IsObjectOfKind((Collider*)obj, 0x73)) {
            GetObjectWorldPosition((BaseObject*)obj, &pos);
        }
        s32 inside = 0;
        if (((self->flags538 & 0x10000000000ULL) && Vu0::Distance(pos, self->v140) < self->radius3CC)
            || (self->tree.nodes != 0 && FindPlaneTreeNodeForPoint(&pos, self->tree.nodes) != 0)) {
            inside = 1;
        }
        if (inside) {
            hit = 1;
            if (self->reportInside == 0) {
                break;
            }
            if (IsObjectAttached((BaseObject*)obj) != 0) {
                found[n++] = obj;
            }
        }
    }
    if (self->reportInside != 0) {
        s32 changed = 0;
        if (self->countInside != n) {
            changed = 1;
        } else {
            for (s32 i = 0; i < n; i++) {
                if (found[i] != self->inside[i]) {
                    changed = 1;
                    break;
                }
            }
        }
        if (changed) {
            self->countInside = n;
            CopyMemory(self->inside, found, n * 4);
            TriggerScriptEvent(self, 0xC, 0, 0);
        }
    }
    SetZoneColliderMode(self, hit);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "flagged_object.h"
#include "object_gatherer.h"
#include "world.h"
#include "game_clock.h"
#include "object_event.h"
struct ScriptListBuilder;



s32 AppendPropertyToScriptList(ScriptListBuilder* self, void* value);

// Appends each of the collider's listed inside entries to the script list; 0 as soon as one is
// refused, else 1.
s32 TestListedEntriesAccepted(ZoneCollider* self, void* arg)
{
    for (s32 i = 0; i < self->countInside; i++) {
        if (AppendPropertyToScriptList((ScriptListBuilder*)arg, &self->inside[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



void AppendZoneFirstQueue(void* a, void* b, s32 c)
{
    AppendToObjectQueue(&((TriggerZoneRecord*)a)->pairs[0].seen, c);
}



void AppendTriggerZoneFirstQueue(TriggerZone* self, s32 value)
{
    AppendZoneFirstQueue(&self->zone, self, value);
}


void AppendZoneColliderFirstQueue(void* self, int value)
{
    AppendZoneFirstQueue(&((ZoneCollider*)self)->zone, self, value);
}


void AppendZoneSecondQueue(void* self, void* unused, int value)
{
    AppendToObjectQueue(&((TriggerZoneRecord*)self)->pairs[1].seen, value);
}


void AppendTriggerZoneSecondQueue(TriggerZone* self, int value)
{
    AppendZoneSecondQueue(&self->zone, self, value);
}


void AppendZoneColliderSecondQueue(ZoneCollider* self, s32 b)
{
    AppendZoneSecondQueue(&self->zone, self, b);
}

// Adds an object id to the zone's list of ids that count.
void AddIncludedId(TriggerZone* list, s32 value)
{
    list->idsIn[list->countIdsIn++] = value;
}

// Adds an object id to the zone's list of ids that do not count.
void AddExcludedId(TriggerZone* self, s32 value)
{
    s32 n = self->countIdsOut;
    self->idsOut[n] = value;
    self->countIdsOut = n + 1;
}

// Adds a kind to the zone's list of kinds that count.
void AddIncludedKind(TriggerZone* self, s32 value)
{
    s32 n = self->countKindsIn;
    self->kindsIn[n] = value;
    self->countKindsIn = n + 1;
}

struct Camera;
extern void* g_camera;

// Adds a kind to the zone's list of kinds that do not count.
void AddExcludedKind(TriggerZone* self, s32 value)
{
    s32 i = self->countKindsOut;
    self->kindsOut[i] = value;
    self->countKindsOut = i + 1;
}

// Adds an object id to the collider's list of ids to look for when it starts.
void AddZoneColliderId(ZoneCollider* self, s32 value)
{
    s32 i = self->countIds;
    self->ids[i] = value;
    self->countIds = i + 1;
}

void SetTriggerZoneEntry(TriggerZone* self, s32 a, s32 b, s32 c, s32 d)
{
    SetZoneEntry(&self->zone, a, b, c, d);
}

void SetZoneColliderEntry(ZoneCollider* self, s32 a, s32 b, s32 c, s32 d) { SetZoneEntry(&self->zone, a, b, c, d); }
