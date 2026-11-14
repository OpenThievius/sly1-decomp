// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1E5378 to 0x1E88D0: the player-linked collider, the arc (a screen element of 57 points on
// a half circle, with its outline and ticks) and the grey colour its static initialiser builds.
// Its name is ours, after the arc, which holds most of its code.
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
#include "fpu.h"
#include "list_iter.h"
#include "packet_writer.h"
#include "screen_element.h"
#include "message_body.h"
#include "shapes.h"
#include "camera.h"
#include "state_walker.h"
#include "object_pool.h"
#include "vu0.h"
#include "pad_record.h"
#include "object_finder.h"
#include "functions/agent.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/camera_controller.h"
#include "functions/collider.h"
#include "functions/game_progress.h"
#include "functions/group_marker.h"
#include "functions/matrix.h"
#include "functions/object_pool.h"
#include "functions/pad_input.h"
#include "functions/placed_object.h"
#include "functions/pooled_object.h"
#include "functions/screen_element.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/text_panel.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
struct ObjectLink;
struct PlacedObject;
struct World;
struct Mat3;
struct Vec4;
struct DeferredRequest;
// Types other files define, named by the parameters of their functions declared here.

extern u8* g_player;
extern u8* g_currentWorld;

void* AllocateFrontMemory(s32 size);

// Initialises the collider: the switched collider's defaults, f644 = 1, two 0x40-byte front-heap
// tables (linkedObjects, linkedIds) and the ranges -1.5 to 1.5 and -0.7 to 0.7 at 0x650-0x65C.
void InitPlayerLinkedCollider(PlayerLinkedCollider* self)
{
    InitSwitchedCollider(self);
    self->f644 = 1;
    self->linkedObjects = AllocateFrontMemory(0x40);
    self->linkedIds = AllocateFrontMemory(0x40);
    self->f658 = -1.5f;
    self->f65C = 1.5f;
    self->f650 = -0.7f;
    self->f654 = 0.7f;
}

// Appends value to the collider's linked ids, up to 0x11 of them.
void AddPlayerLinkedColliderId(PlayerLinkedCollider* self, void* value)
{
    s32 n = self->linkedCount;
    if (n < 0x11) {
        ((void**)self->linkedIds)[n] = value;
        self->linkedCount = n + 1;
    }
}

typedef void (*ListenFn)(void* self, void* other);

struct ListenerObject {
    ListenFn* vtbl;
};

struct OwnedAgent {
    u8 pad0[0xC2C];
    PlayerLinkedCollider* owner;
};

extern s32 g_playerLinkedColliderLinks[10];


// Start of a player-linked collider: starts the placed object, resolves its links, creates its
// state walker from its state graph, then finds the agent it belongs to (class 7) and the objects
// with ids 0x160 and 0x161... that it uses.
void StartPlayerLinkedCollider(PlayerLinkedCollider* self)
{
    void* r2;
    s32 i;
    s32 n;
    void* r;

    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, (ObjectLink*)g_playerLinkedColliderLinks);
    self->stateWalker = (StateWalker*)CreateStateWalker((StateGraph*)self->stateGraph, self, -1, 1);
    r = FindFirstObjectByIdMode4((World*)g_currentWorld, 7, self);
    if (r != 0) {
        self->target = r;
        self->agent = r;
        ((OwnedAgent*)r)->owner = self;
        self->f598 = r;
        self->f584 = (void*)FindFirstObjectById(self->world, 1, 0x160, r);
        i = 0;
        do {
            self->f588[i] = (void*)FindFirstObjectById(self->world, 1, i + 0x161, r);
            i++;
        } while (i < 3);
        self->f594 = 300.0f;
        ((ListenerObject*)r)->vtbl[27](r, self);
    } else {
        self->target = (void*)g_player;
    }

    n = 0;
    while (n < self->linkedCount) {
        r2 = FindFirstObjectByIdMode4(self->world, ((s32*)self->linkedIds)[n], self);
        if (r2 != 0) {
            ((void**)self->linkedObjects)[n] = r2;
            n++;
        }
    }
    self->linkedCount = n;
    VectorToAngles((Vec3*)&self->m110, &self->f648, &self->f64C);
}


// Per-frame update: updates the switched collider and, when it has a target, checks the target's
// method 0x4D: if true, every other object of id class 5 (up to 8) that is not in state 0xB is sent
// to state 0xA and f580 is cleared; otherwise f580 is set to 1.
void UpdatePlayerLinkedCollider(PlayerLinkedCollider* self, f32 dt)
{
    void* arr[8];
    s32 n;
    s32 count;
    s32 i;

    UpdateSwitchedCollider(self, dt);
    if (((SwitchedCollider*)self->target) != 0) {
        if (((SwitchedCollider*)self->target)->desc05()->m4D(((SwitchedCollider*)self->target))) {
            n = GatherObjectsById(self->world, 5, 8, 0, 8, arr);
            if (n > 0) {
                count = n;
                i = 0;
                do {
                    void* item = arr[i];
                    if (item != self->target) {
                        if (((Agent*)item)->state != 0xB) {
                            ChangeAgentState((Agent*)item, 0xA, 0);
                        }
                    }
                    count--;
                    i++;
                } while (count != 0);
            }
            self->f580 = 0;
        } else {
            self->f580 = 1;
        }
    }
}

extern u8* g_player;


void ChoosePlayerLinkedColliderTarget(PlayerLinkedCollider* self);
void AdvancePlayerLinkedColliderWalker(PlayerLinkedCollider* self);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

// Control step: chooses the target; when the pad's bits 0xC0 are pressed it clears them and
// advances the state walker; then, if the player has something at 0x2740 and is attached, calls the
// player's method 0x134 with t and a cleared 0xC4-byte buffer.
void ControlPlayerLinkedCollider(PlayerLinkedCollider* self, void* obj, f32 t)
{
    u8 buf[0xC4];
    u8* o;

    ChoosePlayerLinkedColliderTarget(self);
    if (((PadRecord*)obj)->flags & 0xC0) {
        ClearPadPressedBits((PadRecord*)obj, 0xC0);
        AdvancePlayerLinkedColliderWalker(self);
    }
    o = g_player;
    if (o != 0) {
        if (((Player*)o)->entryQueue != 0) {
            if (IsObjectAttached((BaseObject*)o)) {
                FillMemory(buf, 0, 0xC4);
                o = g_player;
                if (((Player*)o)->desc05()->m49 != 0) {
                    ((Player*)o)->desc05()->m49((Player*)o, t, (PadRecord*)buf);
                }
            }
        }
    }
}

extern Camera* g_camera;
extern u8 g_elementStack[];


// Called when the collider is switched on (p non-zero) or off: on, pushes the caption box and a
// camera controller (anchored on its object, using its own orientation if set) and sets the state
// walker's target 0x359; off, pops the box and removes the controller.
void HandlePlayerLinkedColliderActivation(PlayerLinkedCollider* self, u8* p)
{
    HandleSwitchedColliderActivation(self, p);
    if (p != 0) {
        g_camera->ctl460.zoomDivisor = 100.0f;
        PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
        SetTextPanelState(&g_typedTextCaptionBox, 5);
        g_camera->ctl460.anchorObject = (void*)self->f61C;
        if (self->f630 != 0) {
            *(Quad16*)g_camera->rotation = *(Quad16*)&self->m110.r[0];
            *(Quad16*)g_camera->rotationRow1 = *(Quad16*)&self->m110.r[1];
            *(Quad16*)g_camera->rotationRow2 = *(Quad16*)&self->m110.r[2];
        }
        PushCameraController(g_camera, 6, &g_camera->ctl460, self, 0);
        PushStackValue(&g_camera->ctl460, self->f644);
        SetStateWalkerTarget(self->stateWalker, 0x359);
    } else {
        g_camera->ctl460.zoomDivisor = 10.0f;
        PopStackElement((ElementStack*)g_elementStack);
        RemoveCameraControllers(g_camera, 0xF, 6, &g_camera->ctl460, self, 0);
        PopStackValue(&g_camera->ctl460);
        SetStateWalkerTarget(self->stateWalker, 0x358);
    }
}


// Collider filter: rejects a collider with flag bit 43, one whose root is the collider itself, one
// already in the pool, and one that either it or the pool's chosen item refuses (method 0x38);
// accepts the rest.
s32 IsPlayerLinkedColliderCandidate(PlayerLinkedCollider* self, Collider* node)
{
    Collider* a;
    Collider* b;

    if (node->flags538 & (1ULL << 43)) {
        return 0;
    }
    if ((void*)node->root == (void*)self) {
        return 0;
    }
    if (IsObjectInPool(self->pool, node) != 0) {
        return 0;
    }
    a = node->root03();
    b = (Collider*)self->pool->chosenItem;
    if (a->desc03()->m38(a, b) != 0 || b->desc03()->m38(b, a) != 0) {
        return 0;
    }
    return 1;
}

struct SpanHit {
    Vec4 point;
    u8 pad10[0x60];
};

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
u8* FindNearestSpanObject(s32 flags, Vec4* a1, Vec4* a2, s32 count, Collider** list, ColliderSpan* out);
void PopBackMemoryMark(void);
struct PlacementRecord;
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

// Chooses which collider the player-linked object points at: when its pool has a choice, takes the
// caption box's centre, unprojects it through the camera to a segment (distances 10 to 80000),
// gathers the colliders along it and keeps the best one for the object.
void ChoosePlayerLinkedColliderTarget(PlayerLinkedCollider* self)
{
    if (HasObjectPoolChoice(self->pool) != 0) {
        ObjectPool* pool = self->pool;
        u8* place = (u8*)&pool->f60;
        u8* e0 = (u8*)&pool->fE0;
        u8* ang = (u8*)&pool->f150;
        f32 cx;
        f32 cy;
        Vec4 a;
        Vec4 b;
        Vec4 lo;
        Vec4 hi;
        Collider** list;
        s32 n;

        GetTextPanelCenter(&g_typedTextCaptionBox, &cx, &cy);
        Vu0::Set(a, Vu0::FromFloats(cx * 0.003125f - 1.0f, 1.0f - cy * 0.0040584416f, 10.0f));
        Vu0::Set(b, Vu0::FromFloats(cx * 0.003125f - 1.0f, 1.0f - cy * 0.0040584416f, 80000.0f));
        UnprojectCameraPoint(g_camera, (f32*)&a, &lo);
        UnprojectCameraPoint(g_camera, (f32*)&b, &hi);
        Vec4 pos;
        SpanHit hit;
        PushBackMemoryMark();
        GatherCollidersInBox(self->world, 0, &lo, &hi, IsPlayerLinkedColliderCandidate, self, &n, &list);
        Collider* found = (Collider*)FindNearestSpanObject(0, &lo, &hi, n, list, (ColliderSpan*)&hit);
        if (found != 0 && found->id != 1) {
            *(u8**)e0 = (u8*)found;
            TransformPointBetweenFrames(0, (PlacedObject*)found, (Vec4*)&hit, (Vec4*)&pool->fF0);
            pos = hit.point;
            if (IsObjectOfKind(found->root, 0xE) != 0 || IsObjectOfKind(found->root, 7) != 0) {
                g_typedTextCaptionBox.palette = 2;
            } else if (IsObjectOfKind(found->root, 8) != 0) {
                g_typedTextCaptionBox.palette = 1;
            } else {
                u8* c = (u8*)found;
                while (c != 0) {
                    s32 i;
                    for (i = 0; i < self->linkedCount; i++) {
                        if (((u8**)self->linkedObjects)[i] == c) {
                            break;
                        }
                    }
                    if (i < self->linkedCount) {
                        break;
                    }
                    c = (u8*)((BaseObject*)c)->parent;
                }
                if (c != 0) {
                    g_typedTextCaptionBox.palette = 1;
                } else {
                    g_typedTextCaptionBox.palette = 0;
                }
            }
        } else {
            *(u8**)e0 = 0;
            // a field access here changes retail's code (the record pointer e0 is kept in a register)
            *(Vec4*)(e0 + 0x10) = hi;
            g_typedTextCaptionBox.palette = 0;
            pos = hi;
        }
        PopBackMemoryMark();
        Vec4 c0;
        Mat3 rot;
        Vec4 d;
        GetPlacementRecordTransform((PlacementRecord*)place, &c0, rot.r, 0);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(c0));
        // a field access here changes retail's code (the record pointer is kept in a register)
        *(f32*)(ang + 8) = ArctangentOfRatio(d.y, d.x);
        *(f32*)(ang + 4) = ArctangentOfRatio(d.z, Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d)))));
    }
}


// When the state walker's current and target keys are both 0x359 and the pool has a chosen object,
// sets the walker's target to 0x35A.
void AdvancePlayerLinkedColliderWalker(PlayerLinkedCollider* self)
{
    s32 a;
    s32 b;
    GetStateWalkerCurrentKey(self->stateWalker, &a);
    GetStateWalkerTargetKey(self->stateWalker, &b);
    if (a == 0x359 && b == a) {
        if (HasObjectPoolChoice(self->pool) != 0) {
            SetStateWalkerTarget(self->stateWalker, 0x35A);
        }
    }
}



// Passes the notification to the switched collider and, for kind 0x13, reacts to the message code:
// 0x35B from the state walker's player launches an object of the pool; from the agent's player code
// 0x15E sets f628 and 0x15F clears it.
void HandlePlayerLinkedColliderNotification(PlayerLinkedCollider* self, s32 kind, MessageBody* rec)
{
    HandleSwitchedColliderNotification(self, kind, rec);
    if (kind == 0x13) {
        StateWalker* dev = self->stateWalker;
        s32 id = rec->sourceId;
        if (id == (s32)dev->player) {
            if (rec->code == 0x35B) {
                LaunchChosenPoolObject(self->pool, 1);
            }
        } else if (((Agent*)self->agent) != 0 && id == (s32)((Agent*)self->agent)->statePlayer) {
            s32 k = rec->code;
            if (k != 0x15E) {
                if (k == 0x15F) {
                    self->f628 = 0;
                }
            } else {
                self->f628 = 1;
            }
        }
    }
}


// A collider may contact arg when the ordinary collider test allows it or arg is in the collider's
// pool.
s32 TestPlayerLinkedColliderMayContact(PlayerLinkedCollider* self, void* arg)
{
    if (TestCollidersMayContact(self, (Collider*)arg)) {
        return 1;
    }
    if (self->pool != 0) {
        s32 r = IsObjectInPool(self->pool, (BaseObject*)arg);
        if (r != 0) {
            return 1;
        }
    }
    return 0;
}



// Starts an effect: through the linked agent's method 0x148 when there is an agent, else as a
// switched collider's.
void StartPlayerLinkedColliderEffect(PlayerLinkedCollider* self, s32 mode, PlacedObject* other)
{
    if (self->agent != 0) {
        ((SwitchedCollider*)self->agent)->desc05()->m4E((SwitchedCollider*)self->agent, mode, other);
    } else {
        StartSwitchedColliderEffect(self, mode, other);
    }
}

struct ZeroPair { s32 lo; s32 hi; };

// Gives back zero interact flags: this collider never interacts.
void GetPlayerLinkedColliderInteractFlags(PlayerLinkedCollider* a0, void* a1, ZeroPair* out)
{
    out->lo = 0;
    out->hi = 0;
}

// The collider's target, or the collider itself when it has none.
void* GetPlayerLinkedColliderTarget(PlayerLinkedCollider* self) { return self->target ? self->target : self; }

// A view of the vertices that starts one vertex before the first (0x254): through it, the fields
// of the vertex i are at 0x2C more (x at 0x2C, y at 0x34, the colours at 0x3C and 0x40, the
// brightness at 0x44 and 0x48, the rates from 0x4C), and the previous vertex's next place is at
// 0x04 and 0x0C.
struct ArcPointStep {
    u8 pad0[4];
    f32 previousNextX;
    u8 pad1[4];
    f32 previousNextY;
    u8 pad2[0x2C - 0x10];
    f32 x;
    u8 pad3[4];
    f32 y;
    u8 pad4[4];
    u32 colorA;
    u32 colorB;
    f32 level;
    f32 target;
    f32 rateA;
    f32 rateB;
    f32 rateC;
};


// Initialises the arc element (its kinds 0x1A and the other one mirror each other): size 160 by
// 125.4, the edge positions and the 57 points, each with an angular step of 1/57 and its start
// state.
void InitArcPoints(HeldItemSparkle* self, s32 kind)
{
    self->w = 160.0f;
    self->h = 125.4f;
    self->lineLen = self->lineLen2 = 3.3000002f;
    InitScreenElement(self, kind);
    f32 sign;
    if (kind == 0x1A) {
        self->edgeTo = 0.0f;
        self->edgeFrom = self->w - 62.7f;
        sign = 1.0f;
    } else {
        self->edgeTo = self->w;
        self->edgeFrom = 62.7f;
        sign = -1.0f;
    }
    f32 step = 1.0f / 57.0f;
    s32 i = 0;
    u32 dim = 0x30000000;
    s32 special = 0x1A;
    ArcPointStep* p;
    for (p = (ArcPointStep*)(self->pts - 1); i < 0x39; i++) {
        f32 t = (f32)i * step;
        f32 y = t + t - 1.0f;
        p->y = y;
        p->x = sign * Fpu::Sqrt(1.0f - y * y);
        p->colorA = p->colorB = (i & 1) ? dim : 0x30808080;
        p->level = p->target = 0.0f;
        if (self->index == special) {
            p->rateA = RandomFloatInRange(0.6f, 0.8f);
            p->rateB = RandomFloatInRange(0.4f, 0.6f);
            p->rateC = RandomFloatInRange(0.05f, 0.2f);
        } else {
            p->rateA = RandomFloatInRange(0.3f, 0.4f);
            p->rateB = RandomFloatInRange(0.2f, 0.3f);
            p->rateC = RandomFloatInRange(0.1f, 0.4f);
        }
        if (i != 0) {
            p->previousNextY = p->y;
            p->previousNextX = p->x;
        }
        // address arithmetic: steps to the next 0x2C-byte record (p++ changes retail's code)
        p = (ArcPointStep*)((u8*)p + 0x2C);
    }
    self->pts[56].nextY = 1.0f;
    self->pts[56].nextX = 0.0f;
    if (self->index == 0x1A) {
        self->pulseA = RandomFloatInRange(1.0f, 1.4f);
        self->pulseB = RandomFloatInRange(0.6f, 0.8f);
        self->pulseC = RandomFloatInRange(0.1f, 0.2f);
    } else {
        self->pulseA = RandomFloatInRange(0.5f, 0.7f);
        self->pulseB = RandomFloatInRange(0.2f, 0.3f);
        self->pulseC = RandomFloatInRange(0.3f, 0.5f);
    }
}

extern u8* g_currentWorld;
extern u8 g_coneVolumeColor[];
extern f32 g_arcSpriteRange[2];
extern f32 g_coneVolumeFirstAngle;
extern f32 g_coneVolumeSecondLevel;
extern f32 g_coneVolumeSecondAngle;
extern f32 g_coneVolumeThirdLevel;
extern f32 g_coneVolumeThirdAngle;

typedef void (*ConeSpriteFn)(void* self);
struct ConeSprite { ConeSpriteFn* vtbl; };

struct ConeVolume;
struct U64P;
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);

// Creates the arc's sprite: a cone volume object (class 0x51) in mode 1 with the global cone volume
// colour, angles and levels and the arc's own range.
void CreateArcSprite(HeldItemSparkle* self)
{
    SetupScreenElementText(self);
    self->sprite = CreateTypedRecord(0x51, g_currentWorld, 0, 0x201, -1);
    SetConeVolumeMode((ConeVolume*)self->sprite, 1);
    SetConeVolumeColor((ConeVolume*)self->sprite, (Quad16*)g_coneVolumeColor);
    SetConeVolumeFirstAngle((ConeVolume*)self->sprite, g_coneVolumeFirstAngle);
    SetConeVolumeSecondLevel((ConeVolume*)self->sprite, g_coneVolumeSecondLevel);
    SetConeVolumeSecondAngle((ConeVolume*)self->sprite, g_coneVolumeSecondAngle);
    SetConeVolumeThirdLevel((ConeVolume*)self->sprite, g_coneVolumeThirdLevel);
    SetConeVolumeThirdAngle((ConeVolume*)self->sprite, g_coneVolumeThirdAngle);
    SetConeVolumeRange((ConeVolume*)self->sprite, (U64P*)g_arcSpriteRange);
    SetConeVolumeValue((ConeVolume*)self->sprite, 1);
    ((ConeSprite*)self->sprite)->vtbl[7](self->sprite);
}

// Gives back the first and one-past-last of the arc's 57 points that are visible: size (0 to 1) of
// the 57 points, centred.
void GetArcVisibleRange(HeldItemSparkle* self, s32* first, s32* second) { s32 n = (s32)(self->size * 57.0f); s32 half = (57 - n) / 2; *first = half; *second = half + n; }

extern s32 g_displayMode;

// Writes the GIF vertices of the arc's outline: in display mode 4 a plain rectangle at the
// element's shown position and size (with the y scale for the screen), otherwise the visible part
// of the arc, between the arc's two edges, as a strip.
void WriteArcOutlineVertices(HeldItemSparkle* self, PacketWriter* c, s32 k)
{
    if (g_displayMode == 4) {
        f32 y = self->shownY;
        f32 x = self->shownX;
        s32 x0 = (s32)((x + 1728.0f) * 16.0f);
        s32 y0 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
        AddGifXyzfNoDrawEntry(c, x0, y0, k, 0);
        AddGifXyzfNoDrawEntry(c, x0, (s32)(((y + self->h) * 0.45454547f + 1936.0f) * 16.0f), k, 0);
        AddGifXyzfEntry(c, (s32)(((x + self->w) + 1728.0f) * 16.0f), y0, k, 0);
        y = y + self->h;
        x = x + self->w;
        AddGifXyzfEntry(c, (s32)((x + 1728.0f) * 16.0f), (s32)((y * 0.45454547f + 1936.0f) * 16.0f), k, 0);
    } else {
        s32 r[2];
        GetArcVisibleRange(self, &r[0], &r[1]);
        if (r[0] != r[1]) {
            f32 a = self->y + 62.7f;
            f32 b = self->x + self->edgeTo;
            f32 bx = self->x + self->edgeFrom;
            s32 x0, y0, i;
            f32 t;
            y0 = (s32)(((a + self->pts[r[0]].y * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
            x0 = (s32)((b + 1728.0f) * 16.0f);
            t = bx + self->pts[r[0]].x * 62.7f;
            AddGifXyzfNoDrawEntry(c, x0, y0, k, 0);
            AddGifXyzfNoDrawEntry(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            for (i = r[0]; i < r[1]; i++) {
                T217D_3F0_Pt* p = &self->pts[i];
                t = bx + p->nextX * 62.7f;
                s32 x = (s32)((b + 1728.0f) * 16.0f);
                y0 = (s32)(((a + p->nextY * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
                AddGifXyzfEntry(c, x, y0, k, 0);
                AddGifXyzfEntry(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            }
        }
    }
}

extern u8 g_arcGreyColor[8];

struct ColorLerp {
    static u8 Of(s32 a, s32 b, f32 t)
    {
    if (a == b) return b;
    if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
    return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
};

#define GIF_SCREEN_X(x) ((s32)(((x) + 1728.0f) * 16.0f))
#define GIF_SCREEN_Y(y) ((s32)(((y) * 0.45454547f + 1936.0f) * 16.0f))

// The arc's points: a quad from the edge to each point, coloured from its own colour toward
// grey by its level, then sparkles scattered at random over each point's span, more the
// brighter it is.
void WriteArcPointVertices(HeldItemSparkle* self, PacketWriter* buf)
{
    s32 first, last;
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    f32 x0 = self->x + self->edgeFrom;
    f32 y0 = self->y + 62.7f;
    f32 xe = self->x + self->edgeTo;
    BeginGifTag(buf, 0x44, 5, 0x44441);
    for (s32 i = first; i < last; i++) {
        T217D_3F0_Pt* p = &self->pts[i];
        f32 xa = x0 + p->x * 62.7f;
        f32 xb = x0 + p->nextX * 62.7f;
        f32 ya = y0 + p->y * 62.7f;
        f32 yb = y0 + p->nextY * 62.7f;
        Rgba4 c;
        {
            Rgba4 a = *(Rgba4*)&p->colorB;
            Rgba4 b = *(Rgba4*)g_arcGreyColor;
            f32 t = p->level;
            Rgba4 m;
            m.r = ColorLerp::Of(a.r, b.r, t);
            m.g = ColorLerp::Of(a.g, b.g, t);
            m.b = ColorLerp::Of(a.b, b.b, t);
            m.a = ColorLerp::Of(a.a, b.a, t);
            c = m;
        }
        AddGifRgbaEntry(buf, *(u32*)&c);
        s32 sx = GIF_SCREEN_X(xe);
        s32 sya = GIF_SCREEN_Y(ya);
        AddGifXyzfEntry(buf, sx, sya, 0, 0);
        AddGifXyzfEntry(buf, GIF_SCREEN_X(xa), sya, 0, 0);
        s32 syb = GIF_SCREEN_Y(yb);
        AddGifXyzfEntry(buf, sx, syb, 0, 0);
        AddGifXyzfEntry(buf, GIF_SCREEN_X(xb), syb, 0, 0);
    }
    BeginGifTag(buf, 0, 1, 1);
    AddGifRgbaEntry(buf, 0x80000000);
    BeginGifTag(buf, 0, 1, 4);
    for (s32 i = first; i < last; i++) {
        T217D_3F0_Pt* p = &self->pts[i];
        s32 n = (s32)(p->level * 3.999f) + 2;
        if (n != 0) {
            f32 xa = x0 + p->x * 62.7f;
            f32 xb = x0 + p->nextX * 62.7f;
            f32 lo = xb <? (xe < xa ? xe : xa);
            f32 hi = xb >? (xa < xe ? xe : xa);
            f32 ya = y0 + p->y * 62.7f;
            f32 yb = y0 + p->nextY * 62.7f;
            for (s32 j = 0; j < n; j++) {
                f32 x = RandomFloatInRange(lo, hi);
                f32 y = RandomFloatInRange(ya, yb);
                AddGifXyzfEntry(buf, GIF_SCREEN_X(x), GIF_SCREEN_Y(y), 0, 0);
            }
        }
    }
}


extern f32 g_elapsedTime;
extern Rgba4 g_arcTickColorFrom;
extern Rgba4 g_arcTickColorTo;



struct FadeClamp {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) return lo;
        if (hi < x) return hi;
        return x;
    }
};

// Writes the GIF vertex data for the arc's tick marks: the colour is blended from
// g_arcTickColorFrom to g_arcTickColorTo by a fade value that moves over 0.2 s (fade 0 up, fade 1
// down) since fadeSince, then each visible tick's vertices are added.
void WriteArcTickVertices(HeldItemSparkle* self, PacketWriter* buf)
{
    Rgba4 c;
    f32 t;
    switch (self->fade) {
    case 0:
        t = FadeClamp::Of((g_elapsedTime - self->fadeSince) * 5.0f, 0.0f, 1.0f);
        break;
    case 1:
        t = FadeClamp::Of(1.0f - (g_elapsedTime - self->fadeSince) * 5.0f, 0.0f, 1.0f);
        break;
    }
    BeginGifTag(buf, 0, 1, 1);
    {
        Rgba4 a = g_arcTickColorFrom;
        Rgba4 b = g_arcTickColorTo;
        Rgba4 r;
        r.r = ColorLerp::Of(a.r, b.r, t);
        r.g = ColorLerp::Of(a.g, b.g, t);
        r.b = ColorLerp::Of(a.b, b.b, t);
        r.a = ColorLerp::Of(a.a, b.a, t);
        c = r;
    }
    AddGifRgbaEntry(buf, *(u32*)&c);
    BeginGifTag(buf, 0x44, 1, 4);
    f32 x0 = self->x + self->edgeFrom;
    f32 y0 = self->y + 62.7f;
    f32 xe = self->x + self->edgeTo;
    s32 first, last;
    GetArcVisibleRange(self, &first, &last);
    T217D_3F0_Pt* e = &self->pts[first];
    f32 len = self->lineLen;
    f32 xa = x0 + e->x * 62.7f;
    f32 xb = x0 + (len + 62.7f) * e->x;
    f32 ya = y0 + e->y * 62.7f;
    f32 yb = ya - len;
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xe), GIF_SCREEN_Y(ya), 0, 0);
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xe), GIF_SCREEN_Y(yb), 0, 0);
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xa), GIF_SCREEN_Y(ya), 0, 0);
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xb), GIF_SCREEN_Y(yb), 0, 0);
    for (s32 i = first; i < last; i++) {
        e = &self->pts[i];
        xa = x0 + e->x * 62.7f;
        ya = y0 + e->y * 62.7f;
        xb = x0 + (self->lineLen + 62.7f) * e->x;
        yb = y0 + (self->lineLen + 62.7f) * e->y;
        AddGifXyzfEntry(buf, GIF_SCREEN_X(xa), GIF_SCREEN_Y(ya), 0, 0);
        AddGifXyzfEntry(buf, GIF_SCREEN_X(xb), GIF_SCREEN_Y(yb), 0, 0);
    }
    xa = x0 + e->nextX * 62.7f;
    ya = y0 + e->nextY * 62.7f;
    yb = ya + self->lineLen;
    xb = x0 + (self->lineLen + 62.7f) * e->nextX;
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xa), GIF_SCREEN_Y(ya), 0, 0);
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xb), GIF_SCREEN_Y(yb), 0, 0);
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xe), GIF_SCREEN_Y(ya), 0, 0);
    AddGifXyzfEntry(buf, GIF_SCREEN_X(xe), GIF_SCREEN_Y(yb), 0, 0);
}

extern u8 g_gsPacketWriter[];

void WriteArcPointVertices(HeldItemSparkle* self, PacketWriter* buf);
void WriteArcTickVertices(HeldItemSparkle* self, PacketWriter* buf);

// When drawing the arc is allowed, writes a GIF tag with two register writes (0x47, 0x42) and then
// the arc's point and tick vertices to the GS packet.
void DrawArc(HeldItemSparkle* self)
{
    u8* s = g_gsPacketWriter;
    if (IsArcDrawAllowed()) {
        BeginGifTag((PacketWriter*)s, 0, 1, 0xE);
        AddGifRegisterWrite((PacketWriter*)s, 0x47, 0x31001);
        AddGifRegisterWrite((PacketWriter*)s, 0x42, 0x44);
        WriteArcPointVertices(self, (PacketWriter*)s);
        WriteArcTickVertices(self, (PacketWriter*)s);
    }
}

extern f32 g_elapsedTime;

// Sets the arc's fade state and notes the elapsed time it changed at.
void SetArcFade(HeldItemSparkle* a0, s32 a1)
{
    if (a1 != a0->fade) {
        a0->fade = a1;
        a0->fadeSince = g_elapsedTime;
    }
}

extern s32 g_displayMode;

// Makes the arc's target its current object: the old one gets its method 3 (unless it is the
// special object in display mode 4), the new one its method 2, the tree-records value (not in mode
// 4) and flag bit 32 of its flags.
void ApplyArcTarget(HeldItemSparkle* self)
{
    PlacedObject* cur = (PlacedObject*)self->current;
    if ((PlacedObject*)self->target == cur) {
        return;
    }
    if (cur != 0) {
        if (!(g_displayMode == 4 && cur == (PlacedObject*)self->special)) {
            cur->desc->m03(cur);
        }
    }
    self->current = self->target;
    if (self->current != 0) {
        ((PlacedObject*)self->current)->desc->m02((PlacedObject*)self->current);
        if (g_displayMode != 4) {
            SetObjectTreeRecordsValue((PlacedObject*)self->current, self);
        }
        ((PlacedObject*)self->current)->flags |= 0x100000000UL;
    }
}

extern f32 g_gameClock[];
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// Changes the arc's phase: 0 plays sound 0x8C and resets the 57 points to full level with random
// targets and fixed rates, 2 plays sound 0x8D, and the other phases set their own point levels.
void SetArcPhase(HeldItemSparkle* self, s32 mode)
{
    if (mode == self->phase) {
        return;
    }
    switch (mode) {
    case 0: {
        StartSoundEffect(0x8C, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        for (s32 i = 0; i < 57; i++) {
            T217D_3F0_Pt* e = &self->pts[i];
            e->level = 1.0f;
            e->target = RandomFloatInRange(0.0f, 0.05f);
            e->rateA = 1.0f;
            e->rateB = 0.6f;
            e->rateC = 0.2f;
        }
        break;
    }
    case 2:
        StartSoundEffect(0x8D, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 1:
        self->size = 1.0f;
        break;
    case 3:
        self->size = 0.0f;
        ApplyArcTarget(self);
        break;
    }
    self->phase = mode;
    self->phaseSince = g_gameClock[4];
}

extern s32 g_displayMode;

// Sets the arc's screen element mode; on leaving mode 0 it sets the element's offset and size by
// the display mode (640 by 360 in mode 4, 160 by 125.4 otherwise), and with mode 2 it restarts the
// phase 3.
void SetArcMode(HeldItemSparkle* self, s32 value)
{
    s32 old = self->mode;
    SetScreenElementMode(self, value);
    if (old == value) return;
    if (old != 0) goto done;
    if (g_displayMode == 4) {
        self->place->dy = 0.0f;
        SetScreenElementSize(self, 640.0f, 360.0f);
    } else {
        self->place->dy = -20.0f;
        SetScreenElementSize(self, 160.0f, 125.4f);
    }
done:
    if (value != 2) return;
    if (g_displayMode == 4) return;
    self->phase = -1;
    SetArcPhase(self, 3);
}

extern f32 g_gameClock[];
extern s32 D_00270448;
extern s32 g_displayMode;

struct RampProfile;

// Per-frame update of the arc screen element (a ring of 57 points): works out the mode and phase
// from whether it has a current and a target object and the display mode, calls SetArcMode and
// SetArcPhase, and steps each point's level and target by their rates.
void UpdateArc(HeldItemSparkle* self)
{
    UpdateScreenElementSlide(self);
    s32 state = self->mode;
    s32 sub = self->phase;
    switch (state)
    {
    case 0:
        if (self->current != 0)
        {
            state = 2;
        }
        else if (self->target != 0)
        {
            state = D_00270448 != 0;
        }
        break;
    case 3:
        sub = 3;
        break;
    case 2:
        switch (sub)
        {
        case 0:
        {
            f32 f = self->size + g_gameClock[5] * 5.0f;
            self->size = f;
            if (1.0f <= f)
            {
                self->size = 1.0f;
                sub = 1;
            }
            break;
        }
        case 2:
        {
            f32 f = self->size - g_gameClock[5] * 5.0f;
            self->size = f;
            if (f <= 0.0f)
            {
                self->size = 0.0f;
                sub = 3;
            }
            break;
        }
        case 3:
            if (self->target != 0)
            {
                sub = 0;
            }
            else
            {
                state = 3;
            }
            break;
        }
        if (g_displayMode != 4)
        {
            self->pulse = ApproachValueWithRamp((RampProfile*)&self->pulseA, 0, self->pulse, self->pulseTarget, g_gameClock[5]);
            if (AreFloatsNearlyEqual(self->pulse, self->pulseTarget, 1e-4f) != 0)
            {
                self->pulse = 1.0f;
                if (self->index == 0x1A)
                {
                    self->pulseA = RandomFloatInRange(1.0f, 1.4f);
                    self->pulseB = RandomFloatInRange(0.6f, 0.8f);
                    self->pulseC = RandomFloatInRange(0.1f, 0.2f);
                }
                else
                {
                    self->pulseA = RandomFloatInRange(0.5f, 0.7f);
                    self->pulseB = RandomFloatInRange(0.2f, 0.3f);
                    self->pulseC = RandomFloatInRange(0.3f, 0.5f);
                }
            }
            s32 idx = (s32)(self->pulse * 56.999f);
            f32 d = RandomFloatInRange(0.1f, 0.2f);
            if (self->index == 0x1A)
            {
                d = d + d;
            }
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 v = self->pts[idx].level + d;
            if (v < lo)
            {
                v = lo;
            }
            else if (hi < v)
            {
                v = hi;
            }
            self->pts[idx].level = v;
            s32 big = 0x1A;
            f32* q;
            T217D_3F0_Pt* e;
            s32 i;
            for (q = &self->pts[0].rateA, e = self->pts, i = 0; i < 57; q += 11, i++, e++)
            {
                if (AreFloatsNearlyEqual(e->level, e->target, 1e-4f) != 0)
                {
                    if (self->index == big)
                    {
                        e->rateA = RandomFloatInRange(0.6f, 0.8f);
                        e->rateB = RandomFloatInRange(0.4f, 0.6f);
                        e->rateC = RandomFloatInRange(0.05f, 0.2f);
                    }
                    else
                    {
                        e->rateA = RandomFloatInRange(0.3f, 0.4f);
                        e->rateB = RandomFloatInRange(0.2f, 0.3f);
                        e->rateC = RandomFloatInRange(0.1f, 0.4f);
                    }
                    e->target = RandomFloatInRange(0.0f, 0.05f);
                }
                else
                {
                    e->level = ApproachValueWithRamp((RampProfile*)q, 0, e->level, e->target, g_gameClock[5]);
                }
            }
        }
        break;
    }
    self->vt->m16(self, state);
    SetArcPhase(self, sub);
}

extern PadRecord g_padRecord;
struct ArcDrawRequest;
void DrawArcOutlinePacket(ArcDrawRequest* request);
void DrawArcTickPacket(ArcDrawRequest* request);

// What an arc holds (HeldItemSparkle::current): the camera zoom it is seen at, where on the screen it
// stands (a depth and the fractions of the arc's box), its offset from the point found, and its
// point in the special object's frame.
struct ArcHeld : PlacedObject {
    u8 pad2D0[0x2D4 - 0x2D0];
    f32 zoom;               // 0x2D4
    f32 depth;              // 0x2D8
    f32 u;                  // 0x2DC
    f32 v;                  // 0x2E0
    u8 pad2E4[0x2F0 - 0x2E4];
    Vec4 offset;           // 0x2F0: in the camera's frame
    Vec4 point;            // 0x300: in the special object's frame
};

// A placement handed to slot 36: a matrix with its translation and a scale.
struct ArcPlacement {
    Vec4 rows[4];
    f32 scaleX;
    f32 scaleY;
};

// The request queued for each of the arc's draws: the function, its count and the arc.
struct ArcQueueRequest {
    void (*fn)(ArcDrawRequest* request); // 0x00
    s32 f04;                // 0x04
    s32 count;              // 0x08
    u8 pad0C[0x60 - 0x0C];
    HeldItemSparkle* arc;         // 0x60
    u8 pad64[0x80 - 0x64];
};

// A request cleared. Through the inline the request's address is a constant at each use, formed
// again at each call (addiu a0,sp,N), as retail does; FillMemory(&request, ..) directly leaves it
// in a saved register across the calls (docs/TOOLCHAIN.md,
// "Frame addresses and a constant's copy in the arc's frame").
static inline void ClearArcQueueRequest(ArcQueueRequest* request)
{
    FillMemory(request, 0, sizeof(*request));
}

// The arc's frame: while the caption box is open (state 4) only a fully grown arc that is fading
// out; otherwise once the menus are closed. Its held object goes where the arc's box shows it,
// unprojected at its depth, then (state 2 and 3) 20 above and 150 out from the camera, moved by
// the stick in state 2, or (state 4) at the special object's point; it is placed there and the
// outline and the ticks are queued, the camera's zoom put back.
void QueueArcDraw(HeldItemSparkle* self)
{
    Vec4 screen;
    Vec4 world;
    Vec4 aim;
    Vec4 dir;
    Mat3 basis;
    ArcPlacement place;
    s32 first;
    s32 last;
    f32 zoom;
    f32 zoomY;

    if (g_typedTextCaptionBox.state == 4) {
        if (self->fade != 1) {
            return;
        }
        if (self->phase != 1) {
            return;
        }
    } else if (!AreArcMenusClosed()) {
        return;
    }
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    if (g_typedTextCaptionBox.state != 4) {
        zoom = g_camera->zoom;
        zoomY = g_camera->zoomGoal;
        SnapCameraZoom(g_camera, ((ArcHeld*)self->current)->zoom);
    }
    {
        ArcHeld* held = (ArcHeld*)self->current;
        f32 sx = ((1.0f - held->u) * self->x + held->u * (self->x + self->w)) * 0.003125f - 1.0f;
        f32 sy = 1.0f - ((1.0f - held->v) * self->y + held->v * (self->y + self->h)) * 0.00405844161f;
        Vu0::Q(screen) = Vu0::FromFloats(sx, sy, held->depth);
        UnprojectCameraPoint(g_camera, (f32*)&screen, &world);
    }
    {
        f32 dist = 150.0f;
        f32 height = 20.0f;
        switch (g_typedTextCaptionBox.state) {
        case 2:
            if (self->index == 0x1A) {
                dist = __builtin_fabsf(g_padRecord.stickX) * g_padRecord.stickX * 150.0f + dist;
                height = __builtin_fabsf(g_padRecord.stickY) * g_padRecord.stickY * 150.0f + height;
            } else {
                dist = __builtin_fabsf(g_padRecord.secondStickX) * g_padRecord.secondStickX * -150.0f + dist;
                height = __builtin_fabsf(g_padRecord.secondStickY) * g_padRecord.secondStickY * 150.0f + height;
            }
        case 3: {
            Camera* cam;
            if (self->index == 0x1A) {
                dist = -dist;
            }
            cam = g_camera;
            Vu0::Q(aim) = Vu0::Add(Vu0::Vec::Of(cam->position).q, Vu0::MulX(Vu0::Q(cam->rotationRow2), Vu0::Scalar(height)));
            Vu0::Q(aim) = Vu0::Add(Vu0::Q(aim), Vu0::MulX(Vu0::Q(cam->rotationRow1), Vu0::Scalar(dist)));
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(aim), Vu0::Q(world));
            BuildBasisFromXAndZHint(&dir, (const Vec4*)&cam->rotationRow2, &basis);
            BuildMatrixFromRotationAndTranslation(&world, &basis, (Mat4A*)&place);
            Vec4 pos;
            Vu0::Q(pos) = Vu0::Add(Vu0::Q(aim), Vu0::Rotate(*(Mat3*)&g_camera->rotation, Vu0::Q(((ArcHeld*)self->current)->offset)));
            ((PlacedObject*)self->sprite)->desc02()->m1D((PlacedObject*)self->sprite, &pos);
            break;
        }
        case 4: {
            PlacedObject* special = (PlacedObject*)self->special;
            Vec4 pos;
            if (special == 0) {
                goto done;
            }
            BuildMatrixFromRotationAndTranslation(&special->v140, &special->m110, (Mat4A*)&place);
            TransformPointBetweenFrames((PlacedObject*)self->special, 0, &((ArcHeld*)self->current)->point, &pos);
            ((PlacedObject*)self->sprite)->desc02()->m1D((PlacedObject*)self->sprite, &pos);
            break;
        }
        }
    }
    if (g_typedTextCaptionBox.state != 4) {
        ArcQueueRequest request;
        ClearArcQueueRequest(&request);
        request.count = 2;
        request.fn = DrawArcOutlinePacket;
        request.arc = self;
        QueueDeferredRequest((DeferredRequest*)&request);
    }
    ((ArcHeld*)self->current)->flags &= ~((u64)1 << 32);
    place.scaleX = place.scaleY = 1.0f;
    ((ArcHeld*)self->current)->desc02()->m24((ArcHeld*)self->current, g_camera, &place);
    ((ArcHeld*)self->current)->flags |= (u64)0x8000 << 17;
    if (g_typedTextCaptionBox.state != 4) {
        ArcQueueRequest request;
        ClearArcQueueRequest(&request);
        request.count = 2;
        request.fn = DrawArcTickPacket;
        request.arc = self;
        QueueDeferredRequest((DeferredRequest*)&request);
    }
done:
    if (g_typedTextCaptionBox.state != 4) {
        SnapCameraZoom(g_camera, zoom);
        g_camera->zoomGoal = zoomY;
    }
}

// The deferred request QueueArcDraw queues: the arc at 0x60.
struct ArcDrawRequest {
    u8 pad00[0x60];
    HeldItemSparkle* arc;         // 0x60
};

extern PacketWriter g_vifPacketWriter;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

void WriteArcOutlineVertices(HeldItemSparkle* self, PacketWriter* buf, s32 a);

// Draw callback of the arc's outline: skips an empty visible range, resets the camera's zoom to the
// current object's for the draw when the two differ (and restores it after), then builds the packet
// from the outline vertices and sends it.
void DrawArcOutlinePacket(ArcDrawRequest* request)
{
    PacketWriter buf;
    s32 first, last;
    HeldItemSparkle* self = request->arc;
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    if (g_displayMode != 4) {
        if (AreFloatsNearlyEqual(g_camera->zoom, ((ArcHeld*)self->current)->zoom, 1e-4f) == 0) {
            f32 zoom = g_camera->zoom;
            f32 f1C8 = g_camera->zoomGoal;
            SnapCameraZoom(g_camera, ((ArcHeld*)self->current)->zoom);
            WriteCameraMatricesPacket(g_camera);
            SnapCameraZoom(g_camera, zoom);
            g_camera->zoomGoal = f1C8;
        }
    }
    PushBackMemoryMark();
    InitGifPacket(&buf);
    AllocateTempPacketBuffer(&buf, 0x100);
    f32 zero = 0.0f;
    f32 right = 640.0f;
    f32 bottom = 492.80002f;
    f32 x0 = zero >? self->x;
    f32 y0 = zero >? self->y;
    f32 x1 = right <? self->x + self->w;
    f32 y1 = bottom <? self->y + self->h;
    BeginGifTag(&buf, 0, 1, 0xE);
    s32 px = (s32)x0;
    s32 pw = (s32)x1 - 1;
    y0 *= 0.45454547f;
    y1 *= 0.45454547f;
    s32 py = (s32)y0;
    s32 pz = (s32)y1 - 1;
    AddGifRegisterWrite(&buf, 0x40, (u64)px | ((u64)pw << 16) | ((u64)py << 32) | ((u64)pz << 48));
    BeginGifTag(&buf, 6, 5, 0x441EE);
    AddGifRegisterWrite(&buf, 0x47, 0x30000);
    AddGifRegisterWrite(&buf, 0x42, 0x5A);
    AddGifRgbaEntry(&buf, 0);
    AddGifXyzfEntry(&buf, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 + 1936.0f) * 16.0f), 0xFFFFFF0, 0);
    AddGifXyzfEntry(&buf, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 + 1936.0f) * 16.0f), 0xFFFFFF0, 0);
    BeginGifTag(&buf, 0, 1, 0xE);
    AddGifRegisterWrite(&buf, 0x47, 0x32001);
    BeginGifTag(&buf, 4, 1, 4);
    WriteArcOutlineVertices(self, &buf, 0);
    EndGifPacket(&buf);
    BeginDmaTag(&g_vifPacketWriter);
    WriteVifFlushE(&g_vifPacketWriter);
    WriteVifDirectFromWriter(&g_vifPacketWriter, &buf);
    CloseDmaTag(&g_vifPacketWriter);
    PopBackMemoryMark();
}

// Draw callback of the arc's ticks: clips the element's rectangle to the screen (640 by 492.8),
// builds a GIF packet of the tick vertices in a temporary buffer and sends it. Nothing is drawn
// when the visible range is empty.
void DrawArcTickPacket(ArcDrawRequest* request)
{
    PacketWriter buf;
    s32 first, last;
    HeldItemSparkle* self = request->arc;
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    PushBackMemoryMark();
    InitGifPacket(&buf);
    AllocateTempPacketBuffer(&buf, 0x200);
    f32 zero = 0.0f;
    f32 right = 640.0f;
    f32 bottom = 492.80002f;
    f32 x0 = zero >? self->x;
    f32 y0 = zero >? self->y;
    f32 x1 = right <? self->x + self->w;
    f32 y1 = bottom <? self->y + self->h;
    BeginGifTag(&buf, 6, 3, 0x44E);
    AddGifRegisterWrite(&buf, 0x47, 0x32001);
    s32 ax = GIF_SCREEN_X(x0);
    s32 ay = GIF_SCREEN_Y(y0);
    AddGifXyzfEntry(&buf, ax, ay, 0, 0);
    s32 bx = GIF_SCREEN_X(x1);
    s32 by = GIF_SCREEN_Y(y1);
    AddGifXyzfEntry(&buf, bx, by, 0, 0);
    BeginGifTag(&buf, 6, 3, 0x44E);
    AddGifRegisterWrite(&buf, 0x47, 0x3E001);
    AddGifXyzfEntry(&buf, ax, ay, 0xFFFFFF0, 0);
    AddGifXyzfEntry(&buf, bx, by, 0xFFFFFF0, 0);
    BeginGifTag(&buf, 0x46, 5, 0x441EE);
    AddGifRegisterWrite(&buf, 0x47, 0x31001);
    AddGifRegisterWrite(&buf, 0x42, 0x5A);
    AddGifRgbaEntry(&buf, 0x80000000);
    AddGifXyzfEntry(&buf, ax, ay, 0, 0);
    AddGifXyzfEntry(&buf, bx, by, 0, 0);
    BeginGifTag(&buf, 0, 1, 0xE);
    AddGifRegisterWrite(&buf, 0x40, 0xDF0000027F0000ULL);
    EndGifPacket(&buf);
    BeginDmaTag(&g_vifPacketWriter);
    WriteVifFlushE(&g_vifPacketWriter);
    WriteVifDirectFromWriter(&g_vifPacketWriter, &buf);
    CloseDmaTag(&g_vifPacketWriter);
    PopBackMemoryMark();
}

void SetArcSpecialObject(HeldItemSparkle* self, void* a1);

// Sets the object the arc points at. When the caption box is in state 4 the arc is retargeted at
// once: with a target it goes to phase 1 and fades up, without one it goes to phase 3 and clears
// its special object.
void SetArcTarget(HeldItemSparkle* self, void* value)
{
    if (value == self->target) return;
    if (self->target == 0) {
        g_typedTextCaptionBox.vt->m08(&g_typedTextCaptionBox, 0);
    }
    self->target = value;
    if (g_typedTextCaptionBox.state == 4) {
        ApplyArcTarget(self);
        if (self->target != 0) {
            self->vt->m16(self, 2);
            SetArcPhase(self, 1);
            SetArcFade(self, 0);
        } else {
            self->vt->m16(self, 0);
            SetArcPhase(self, 3);
            SetArcFade(self, 0);
            SetArcSpecialObject(self, 0);
        }
    } else {
        s32 st = self->phase;
        if (st >= 2) return;
        if (st < 0) return;
        SetArcPhase(self, 2);
    }
}

// Replaces the arc's special object, clearing flag bit 32 on the old one and setting it on the new
// one.
void SetArcSpecialObject(HeldItemSparkle* self, void* a1)
{
    PlacedObject* old = (PlacedObject*)self->special;
    if (old != 0) {
        old->flags &= ~(1ULL << 32);
    }
    self->special = a1;
    if (a1 != 0) {
        ((PlacedObject*)a1)->flags |= (1ULL << 32);
    }
}

// Resets the arc element: size, current and target object cleared and phase 3.
void ResetArc(HeldItemSparkle* self)
{
    ResetScreenElement(self);
    self->size = 0;
    self->current = 0;
    self->target = 0;
    self->phase = 3;
}

extern u8 g_arcGreyColor[8];
// Sets the arc's 8-byte grey colour to 0x80 in its first four bytes when called with enabled set
// and value 0xFFFF (the form a compiler-made static constructor calls).
void ConstructGreyColor(s32 enabled, u32 value) { if (value == 0xFFFF && enabled) { g_arcGreyColor[0] = 0x80; g_arcGreyColor[1] = 0x80; g_arcGreyColor[2] = 0x80; g_arcGreyColor[3] = 0x80; } }

void ConstructGreyColor(s32 enabled, u32 value);

// Startup constructor: sets the arc's grey colour.
void ConstructGreyColorAtStartup(void)
{
    ConstructGreyColor(1, 0xFFFF);
}

s32 g_playerLinkedColliderLinks[10] = { 0x00000000, 0x00000356, 0x00000618, 0x00000000, 0x00000357, 0x00000610, 0x00000002, 0x0000035C, 0x0000061C, 0x00000000 };
u8 g_arcGreyColor[8] = { 0 };
f32 g_arcSpriteRange[2] = { 500.0f, 2500.0f };
