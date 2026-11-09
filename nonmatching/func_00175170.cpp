// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 9852/9860, checked 2026-11-08
// NEAR: python3 tools/check.py nonmatching/func_00175170.cpp func_00175170 (2026-11-08, worker large-175170): SetPlayerState, 2,463 instructions against retail's 2,465; the three switches (leave state, enter state, leave and enter sub-state), their eleven jump tables, every case's calls, the frame, the saved registers and the four spilled locals (0x74 flag, 0x78 layers, 0x7C walker id, 0x80 skip) are retail's; 2,424 of 2,465 instructions align equal.
// Still differs (2026-11-08): sub-state 9's `if (self->f2220 == 2) skip = 1;` becomes jump.c's store-flag (xori, sltiu, sw) where retail branches (bne, li, sw: two instructions more; a second statement in the if, such as a dead `else anim = 0`, gives retail's code, so retail's if was not a lone set); sub-state 55 loads v back with lqc2 where retail has lq then qmtc2 (one instruction); the rest is order and registers: the prologue's flag spill before speed's 1.0, state 7's path kind in v1 (retail a1), state 6/5's TriggerScriptEvent argument order, state 6/4's load of D_00263990 after the dot, state 13's stores (retail 0x273C, 0x538, 0x3CC), sub-states 10/11 (the sound's two floats loaded before the zero vector), 37/38 (0x630 before 0x638), 55 (v0/v1 and a0/v1 swapped around the normalisation) and the final reload of skip (v0, retail v1).
// Notes: each case's statements were ordered with build/swarm/large-175170/perm.py (every order compiled and scored); the walker took $fp only once its `walker = 0` came after the other locals' initialisers (global-alloc priority: its live length had been 4 insns longer than the walker id's).
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "base_object.h"
#include "placed_object.h"
#include "collider.h"
#include "screen_element.h"
#include "camera.h"
#include "animation.h"
#include "vu0.h"

extern f32 g_gameTime[];
extern Player* g_player;
extern f32 D_00262E14;
extern f32 D_00262E18;
extern f32 D_00262E1C;
extern f32 D_00262E20;
extern f32 D_00262E24;
extern f32 D_00262E2C;
extern f32 D_00262E30;
extern f32 D_00263970[4];
extern f32 D_00263980[4];
extern f32 D_00263990;
extern f32 D_00263994;
extern f32 D_00263998;
extern f32 D_0026399C;
extern f32 D_002639A0[4];
extern f32 D_002639B0[2];
struct Obj_2639B8 { s32 f0; u8 pad04[4]; };
extern s32 D_002639B8;
extern f32 g_unitRange[];

void func_001C61E0(void* self, s32 arg);
void func_001C4D60(Player* self, void* a1, s32 zero);
void SetPlayerPartLayers(Player* self, s32 flags);
s32 FindStateEntryIndex(void* p, s32 n);
f32 ArctangentOfRatio(f32 a, f32 b);
s32 IsObjectAttached(void* p);
void ResetPlayerOnOffObject(Player* self);
void ReleaseFarPlayerLinks(Player* self);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, void* d);
f32 GetAnimationMarkerTime(Animation* anim, s32 key);
void BuildPerpendicularPair(Vec02* dir, Vec02* out, const Vec02* a, const Vec02* b);

#include "fpu.h"
#include "attachment.h"
#include "on_off_object.h"

void CreateAnimationPlayer(void* anim, void* owner, s32 count, void* args, s32 flag, void* out, f32 start, f32 speed);
void StopAnimationPlayer(void* p);
s32 IsObjectOfKind(void* node, s32 kind);
void InitContactPairFlags(void* world, void* obj);
void PushCameraController(void* camera, s32 kind, void* sounds, void* owner, s32 a4);
void RemoveCameraControllers(void* camera, s32 mask, s32 kind, void* sounds, void* owner, s32 a5);
void RequestCameraSnap(Camera* camera, s32 mode);
void StartCameraSounds(void* sounds);
void SendEmptyMessage(void* x);
s32 MaskWorldBitsBySave(void);
void SetPooledObjectPlayerHold(void* obj, s32 hold);
void SelectPlayerStateAnimation(Player* self);
void ComputePlayerJumpVelocity(Player* self, Vec02* out);
void func_0017FC48(Player* self, Vec02* out);
void func_0017FCC8(Player* self, Vec02* out);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void ActivateSwitchedCollider(void* obj);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void DestroyStateWalker(void* h);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void AddColliderAttachment(Collider* o, Attach03* node);
void RemoveColliderAttachment(Collider* o, Attach03* node);
void SetColliderTreeContactsDropped(void* self, s32 dropped);
void* PushSoundLevel(s32 level);
void ReleaseSoundLevel(void* p);
void StartSoundEffect(s32 sound, void* a1, void* obj, void* pos, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void ResetTrailRing(void* sub);
void SetTurningColliderLinkFlag(void* self, s32 a1);
void TurnColliderTowardHeading(Player* self);
void TurnPlayerToClass75AheadMask8(Player* self);
void TurnPlayerToClass75AheadMask4(Player* self);
void PlacePlayerOnLinkedObject(Player* self);
void SetFlaggedLinkContactMask(Player* self, void* obj, s32 on);
void GetLinkedObjectHeading(Player* self, f32* out);
void ComputePlayerLinkPose(Player* self, Vec02* pos, Mat02* rotA, Mat02* rotB);
s32 HasNoActiveObject89(Player* self);
void TakeCountedColliderTouch(void* obj, Player* a, s32 b);
Attach03* TakeAttachRecord(void* world);
void ReleaseAttachRecords(void* owner, Attach03* list);
void PopActiveSequenceElement(void* x);
void SetOnOffObjectForcedState(void* p, s32 n);
void PushStackElement(void* a, void* b);
void PopStackElement(void* p);
f32 WrapAngle(f32 a);
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
void* FillMemory(void* dst, s32 value, s32 size);

extern s32 D_00270454;
extern f32 D_00274F00;
extern f32 D_00274F04;
extern f32 D_00274F08;
extern f32 D_00274F14;
extern u8 g_elementStack[];

// The shape a track object (+0x2208, +0x23BC) holds at +0x34: slot 1 the position and direction
// at a length, slot 2 the position.
struct TrackShape_175170;
struct TrackShapeDesc_175170 {
    void* m0;
    void (*m1)(TrackShape_175170* self, f32 t, Vec02* pos, Vec02* dir);    // 0x04
    void (*m2)(TrackShape_175170* self, f32 t, Vec02* pos, s32 a);         // 0x08
};
struct TrackShape_175170 {
    TrackShapeDesc_175170* desc;
    u8 pad04[4];
    s32 looped;             // 0x08
    s32 count;              // 0x0C
    f32* start;             // 0x10
    f32* lengths;           // 0x14
};

// An animation argument CreateAnimationPlayer takes: the held object as argument 0x61.
struct AnimArg_175170 {
    s32 id;
    void* value;
};

// The animation player of the player's state, or its state walker, stopped.
static inline void StopPlayerAnimation(Player* self)
{
    if (self->watched2230 != 0) {
        StopAnimationPlayer(self->watched2230);
        self->watched2230 = 0;
    } else if (self->f2234 != 0) {
        DestroyStateWalker(self->f2234);
        self->f2234 = 0;
    }
}

template <class T> static inline Vu0::Vec& AsVec_175170(T& v) { return *(Vu0::Vec*)&v; }

// v made unit length, or fallback when shorter than 0.0001, the fallback in the first arm
// (as player_path.cpp's).
static inline Vu0::Vec NormalizeOrElse_175170(Vu0::Vec v, Vu0::Vec fallback)
{
    u128 len = Vu0::Length(v.q);
    Vu0::Vec r;
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        r = fallback;
    } else {
        r.q = Vu0::DivX(v.q, len);
    }
    return r;
}

// v held between lo and hi.
static inline f32 Clamp_175170(f32 v, f32 lo, f32 hi)
{
    f32 r;
    if (v < lo) {
        r = lo;
    } else if (hi < v) {
        r = hi;
    } else {
        r = v;
    }
    return r;
}

// v made unit length in place, or set to fallback when shorter than 0.0001; its length.
static inline Vu0::Vec NormalizeInPlace_175170(Vec02& v, const Vec02& fallback)
{
    Vu0::Vec q = Vu0::Vec::Of(v);
    Vu0::Vec len = Vu0::Length(q);
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Set(v, Vu0::DivX(q, len).q);
    }
    return len;
}

#define PS(T, o) (*(T*)((u8*)self + (o)))
#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))

void SetPlayerState(Player* self, s32 state, s32 sub)
{
    void* walker;
    s32 sound = -1;
    void* anim = 0;
    f32 start = 0.0f;
    s32 flag = 1;
    f32 speed = 1.0f;
    s32 layers = 0;
    s32 walkerId = -1;
    s32 skip = 0;
    walker = 0;

    if (self->f2220 == state && self->f2228 == sub) {
        return;
    }
    self->f2254 &= ~1;
    if (self->f2220 != state) {
        switch (self->f2220) {
        case 2: {
            self->penalizedTargetId = 0;
            if (state != 3 && state != 7) {
                StartSoundEffect(0x49, 0, self, 0, 1000.0f, 500.0f, 0.7f, 0.0f, 0.0f, 0, 0);
            }
            self->f224C = -1;
            if (self->f223C == 0 && state != 7 && state != 3) {
                func_001C61E0(self, -1);
            }
            if (self->f2438 == 0) {
                void* m = 0;
                switch (state) {
                case 6:
                    switch (self->f239C) {
                    case 4:
                    case 5:
                        m = PS(void*, 0x2720);
                        break;
                    case 0:
                    case 1:
                    case 3:
                    case 6:
                    case 7:
                        m = PS(void*, 0x271C);
                        break;
                    }
                    break;
                case 0:
                case 1:
                case 5:
                case 9:
                case 10:
                case 12:
                    m = PS(void*, 0x271C);
                    break;
                }
                if (m != 0) {
                    SendEmptyMessage(m);
                }
            }
            if (!(MaskWorldBitsBySave() & 0x1000)) {
                self->f2744 = 0;
            }
            break;
        }
        case 5:
            self->fA14 = -1;
            break;
        case 3: {
            if (state == 2) {
                self->penalizedTargetId = self->f2204;
            }
            TriggerScriptEvent((void*)self->f2204, 3, 0, 0);
            BaseObject* o = (BaseObject*)self->f2204;
            o->desc->m18(o, self);
            self->f2210 = self->f2204;
            func_001C61E0(self, -1);
            PS(Attachment*, 0x251C)->mode0 = -1;
            PS(Attachment*, 0x251C)->mode1 = -1;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            PS(Attachment*, 0x2520)->mode1 = -1;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            SetTurningColliderLinkFlag(self, 1);
            if (self->f22AC != 0) {
                RemoveColliderAttachment(((Attach03*)self->f22AC)->target, (Attach03*)self->f22AC);
                ReleaseAttachRecords(self->world, (Attach03*)self->f22AC);
                self->f22AC = 0;
            }
            ResetTrailRing(self->f1520);
            break;
        }
        case 7: {
            if (state == 2) {
                self->penalizedTargetId = self->f2208;
            }
            TriggerScriptEvent((void*)self->f2208, 3, 0, 0);
            BaseObject* o = (BaseObject*)self->f2208;
            o->desc->m18(o, self);
            SetFlaggedLinkContactMask(self, (void*)self->f2208, 0);
            self->f2214 = self->f2208;
            PS(f32, 0x2218) = PS(f32, 0x220C);
            s32 aim = -1;
            if (state == 2 && self->f101C != 0) {
                aim = 11;
            }
            func_001C61E0(self, aim);
            Vu0::Q(self->v2530) = Vu0::Sub(Vu0::Q(self->v560), Vu0::Q(self->pos));
            self->v2530.z = 0.0f;
            ResetTrailRing(self->f1520);
            break;
        }
        case 8:
            SetFlaggedLinkContactMask(self, self->f24A0, 0);
            self->f24A0 = 0;
            break;
        case 4:
            PS(s32, 0x23DC) = -1;
            if (PS(void*, 0x2490) != 0) {
                AT(Vec02, PS(void*, 0x2490), 0x300) = D_00248D30;
            }
            if (PS(void*, 0x2494) != 0) {
                AT(Vec02, PS(void*, 0x2494), 0x300) = D_00248D30;
            }
            self->f580 = 1;
            ResetTrailRing(self->f1520);
            self->f26CC = g_gameTime[0];
            break;
        case 6: {
            switch (self->f239C) {
            case 2:
                StopPlayerAnimation(self);
                StartSoundEffect(0x4E, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                SetPooledObjectPlayerHold(self->heldObject, 0);
                break;
            case 5:
                TriggerScriptEvent(self->f23B8, 3, 0, 0);
                ((BaseObject*)self->f23B8)->desc->m18((BaseObject*)self->f23B8, self);
                SetFlaggedLinkContactMask(self, self->f23B8, 0);
                self->heldObject = 0;
                break;
            case 4:
                TriggerScriptEvent(self->f23BC, 3, 0, 0);
                ((BaseObject*)self->f23BC)->desc->m18((BaseObject*)self->f23BC, self);
                SetFlaggedLinkContactMask(self, self->f23BC, 0);
                self->heldObject = 0;
                break;
            case 6:
                if (self->f223C == 0 && state != 7 && state != 3) {
                    func_001C61E0(self, -1);
                }
                break;
            case 7: {
                PlacedObject* o = (PlacedObject*)self->f23CC;
                self->f638 = WrapAngle(ArctangentOfRatio(o->m110.r[0].y, o->m110.r[0].x) + 1.0f);
                self->f23CC = 0;
                break;
            }
            case 3:
            default:
                self->heldObject = 0;
                break;
            }
            if (state == 2) {
                if (self->f23A0 != 0) {
                    self->penalizedTargetId = (s32)self->f23A0;
                } else if (self->f23A8 != 0) {
                    self->penalizedTargetId = (s32)self->f23A8;
                } else if (self->f23B8 != 0) {
                    self->penalizedTargetId = (s32)self->f23B8;
                } else if (self->f23BC != 0) {
                    self->penalizedTargetId = (s32)self->f23BC;
                } else {
                    self->penalizedTargetId = 0;
                }
            }
            self->fA14 = -1;
            self->f239C = -1;
            self->f23A0 = 0;
            self->f23A8 = 0;
            self->f23B8 = 0;
            self->f23BC = 0;
            if (self->f2674 != 0) {
                SetOnOffObjectForcedState((void*)self->f2674, 0);
                self->f2674 = 0;
            }
            self->f268C = 0;
            if (PS(void*, 0x26A4) != 0) {
                ReleaseSoundLevel(PS(void*, 0x26A4));
                PS(void*, 0x26A4) = 0;
            }
            BaseObject* o = PS(BaseObject*, 0x272C);
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 11:
            SetColliderAnchors(self, 0, 0, 3, 0);
            SetColliderTreeContactsDropped(self, 0);
            break;
        case 10: {
            BaseObject* o = (BaseObject*)self->f25D8[2];
            self->f2200 = 0;
            self->f2204 = 0;
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 12:
            RemoveCameraControllers(g_camera, 0xF, 6, (u8*)g_camera + 0x460, self, 0);
            if (D_00270454 != 0) {
                PopStackElement(g_elementStack);
            }
            break;
        case 9:
            self->f26D4 = 0;
            self->desc05()->m4F(self, 0);
            break;
        case 0:
            switch (self->f223C) {
            case 6:
                func_001C61E0(self, 4);
                break;
            case 7:
                func_001C61E0(self, 5);
                break;
            case 8:
            case 9:
                func_001C61E0(self, -1);
                break;
            }
            break;
        case 1:
            break;
        case 13:
            self->flags538 &= ~((u64)1 << 40);
            self->hook = PS(void*, 0x273C);
            if (self->f1390[13] != 0) {
                func_001C4D60(self, self->f1390[13], 1);
            }
            break;
        }

        switch (state) {
        case 0:
            walkerId = 0x146;
            self->f118C = 0;
            walker = self->f1188;
            if (self->f2220 == 2) {
                s32 late = self->f2250;
                if (late == -1) {
                    f32 limit = 0.95f;
                    if (self->f2228 == 3) {
                        limit = 1.25f;
                    }
                    late = limit < g_gameTime[0] - self->f2224;
                }
                if (late == 1 && FindStateEntryIndex(walker, 0x14A)) {
                    walkerId = 0x14A;
                } else if (FindStateEntryIndex(walker, 0x149)) {
                    walkerId = 0x149;
                }
            }
            layers = 3;
            Vu0::Q(self->v640) = Vu0::Zero();
            break;
        case 1:
            anim = (void*)self->f900;
            break;
        case 5:
            anim = (void*)self->fA10;
            break;
        case 2:
            if (self->f224C == -1) {
                self->f224C = 0;
            }
            self->f2250 = -1;
            self->f2498 = 0;
            PS(f32, 0x249C) = 3.40282347e+38f;
            break;
        case 3: {
            self->f22A4 = -1;
            self->f2388 = self->f238C = 1.0f;
            anim = self->f2384;
            self->f22A0 = g_gameTime[0];
            start = 0.5f;
            SetTurningColliderLinkFlag(self, 0);
            speed = 0.0f;
            PS(Attachment*, 0x251C)->mode0 = 2;
            PS(Attachment*, 0x251C)->mode1 = 2;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            PS(Attachment*, 0x2520)->mode1 = 2;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            Vec02 pos;
            Mat02 rotA;
            Mat02 rotB;
            f32 heading;
            ComputePlayerLinkPose(self, &pos, &rotA, &rotB);
            Vu0::Q(PS(Vec02, 0x22F0)) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->f61C)->pos), Vu0::Q(pos));
            MultiplyMatrices3x3(&rotA, &((PlacedObject*)self->f61C)->rot, &PS(Mat02, 0x2300));
            MultiplyMatrices3x3(&rotB, &((PlacedObject*)self->f23D0)->rot, &PS(Mat02, 0x2330));
            TriggerScriptEvent((void*)self->f2204, 2, 0, 0);
            BaseObject* o = (BaseObject*)self->f2204;
            o->desc->m17(o, self);
            GetLinkedObjectHeading(self, &heading);
            f32 back = WrapAngle(heading + 3.14159274f);
            s32 kind = 1;
            if (self->f2204 != 0) {
                kind = AT(s32, self->f2204, 0xA0);
            }
            switch (kind) {
            case 2:
                self->f638 = back;
                self->f22A8 = 1;
                break;
            case 1:
                self->f638 = heading;
                self->f22A8 = 0;
                break;
            case 0:
                if (__builtin_fabsf(WrapAngle(heading - self->f630)) < 1.57079637f) {
                    self->f638 = heading;
                    self->f22A8 = 0;
                } else {
                    self->f638 = back;
                    self->f22A8 = 1;
                }
                break;
            }
            u128 zero = Vu0::Zero();
            sound = AT(s32, self->f2204, 0xA8);
            func_001C61E0(self, 1);
            for (Collider* c = (Collider*)AT(BaseObject*, self->f2204, 0x18); c != 0; c = (Collider*)c->parent) {
                if (c->desc->flags & 2) {
                    if ((c->mode450 != 3 && c->f1EC != 0 && c->f1EC->mode0 == 1) ||
                        (c->mode470 != 3 && c->f1F0 != 0 && c->f1F0->mode1 == 1)) {
                        Attach03* a = TakeAttachRecord(self->world);
                        a->owner = self;
                        a->target = c;
                        AddColliderAttachment(c, a);
                        self->f22AC = a;
                        break;
                    }
                }
            }
            Vu0::Q(self->v640) = zero;
            PlacePlayerOnLinkedObject(self);
            break;
        }
        case 7: {
            TriggerScriptEvent((void*)self->f2208, 2, 0, 0);
            BaseObject* o = (BaseObject*)self->f2208;
            o->desc->m17(o, self);
            SetFlaggedLinkContactMask(self, (void*)self->f2208, 1);
            self->f241C = -1;
            void* track = (void*)self->f2208;
            s32 turn = AT(s32, track, 0x58);
            TrackShape_175170* s = AT(TrackShape_175170*, track, 0x34);
            Vec02 a;
            Vec02 b;
            switch (turn) {
            case 0:
                self->f221C = 0;
                break;
            case 1:
                self->f221C = 1;
                break;
            default: {
                if (s->desc->m2 != 0) {
                    s->desc->m2(s, self->f2410 + D_00274F14, &a, 0);
                    if (s->desc->m2 != 0) {
                        s->desc->m2(s, self->f2410 - D_00274F14, &b, 0);
                    }
                }
                TransformPointBetweenFrames(AT(void*, self->f2208, 0x18), 0, &a, &a);
                TransformPointBetweenFrames(AT(void*, self->f2208, 0x18), 0, &b, &b);
                Vec02 d;
                *(u128*)&d = NormalizeOrElse_175170(Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b)), Vu0::Vec::Of(g_unitZVector)).q;
                self->f221C = d.z < -D_00274F08;
                break;
            }
            }
            f32 len = PS(f32, 0x220C);
            self->f2410 = len;
            if (s->looped == 0) {
                if (self->f221C != 0) {
                    self->f2410 = Clamp_175170(len, s->lengths[0] + D_00274F00, s->lengths[s->count - 1] - D_00274F04);
                } else {
                    self->f2410 = Clamp_175170(len, s->lengths[0] + D_00274F04, s->lengths[s->count - 1] - D_00274F00);
                }
            }
            if (s->desc->m2 != 0) {
                s->desc->m2(s, self->f2410, &a, 0);
            }
            TransformPointBetweenFrames(AT(void*, self->f2208, 0x18), 0, &a, &a);
            TransformPointBetweenFrames(self, 0, &self->f23E0, &b);
            Vu0::Q(self->v2400) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
            sound = AT(s32, self->f2208, 0x50);
            Vu0::Q(self->v2530) = Vu0::Sub(Vu0::Q(self->v560), Vu0::Q(a));
            break;
        }
        case 8: {
            func_001C61E0(self, -1);
            sound = 0x59;
            SetFlaggedLinkContactMask(self, self->f24A0, 1);
            Vec02 pos;
            Mat02 m;
            Vec02 k;
            TransformPointBetweenFrames(self->f24A0, 0, self->f24B0, &pos);
            Vu0::Q(k) = Vu0::FromFloat(-1.0f);
            Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->v24C0), Vu0::Q(k));
            BuildPerpendicularPair(&m.r[0], &m.r[1], &g_unitZVector, &g_unitZVector);
            Vu0::Q(pos) = Vu0::Sub(Vu0::Q(pos), Vu0::Rotate(m, Vu0::Q(self->v24E0)));
            anim = PS(void*, 0x1038);
            Vu0::Q(self->v24D0) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(pos));
            self->v2400 = D_00248D30;
            Vu0::Q(self->v640) = Vu0::Zero();
            break;
        }
        case 4:
            if (PS(void*, 0x2490) != 0) {
                AT(Vec02, PS(void*, 0x2490), 0x300) = *(Vec02*)D_00263970;
            }
            if (PS(void*, 0x2494) != 0) {
                AT(Vec02, PS(void*, 0x2494), 0x300) = *(Vec02*)D_00263970;
            }
            Vu0::Q(self->v640) = Vu0::Zero();
            func_001C61E0(self, -1);
            self->f580 = 0;
            self->f26CC = 3.40282347e+38f;
            break;
        case 6: {
            s32 loud = 0;
            switch (self->f239C) {
            case 2:
                StopPlayerAnimation(self);
                StartSoundEffect(0x4D, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                loud = 1;
                SetPooledObjectPlayerHold(self->heldObject, 1);
                break;
            case 5:
                TriggerScriptEvent(self->f23B8, 2, 0, 0);
                ((BaseObject*)self->f23B8)->desc->m17((BaseObject*)self->f23B8, self);
                layers = 1;
                SetFlaggedLinkContactMask(self, self->f23B8, 1);
                break;
            case 4: {
                void* track = self->f23BC;
                layers = 1;
                TriggerScriptEvent(track, 2, 0, 0);
                ((BaseObject*)track)->desc->m17((BaseObject*)track, self);
                SetFlaggedLinkContactMask(self, track, 1);
                self->f241C = -1;
                Vec02 dir;
                Vec02 tan;
                TrackShape_175170* s = AT(TrackShape_175170*, track, 0x34);
                if (s->desc->m1 != 0) {
                    s->desc->m1(s, self->f23C0, 0, &tan);
                }
                TransformDirectionBetweenFrames(AT(void*, track, 0x18), 0, &tan, &dir);
                dir.z = 0.0f;
                AsVec_175170(dir) = NormalizeOrElse_175170(Vu0::Vec::Of(dir), Vu0::Vec::Of(g_unitXVector));
                s32 back = 1;
                if (!(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->m110.r[0]))) < D_00263990)) {
                    back = 0;
                }
                self->f23C8 = back;
                break;
            }
            case 7:
                self->desc02()->m20(self, (Vec02*)&D_00248D30);
                loud = 1;
                self->desc02()->m21(self, (Vec02*)&D_00248D30);
                Vu0::Q(self->v640) = Vu0::Zero();
                ActivateSwitchedCollider(self->f23CC);
                break;
            case 3: {
                BaseObject* o = PS(BaseObject*, 0x272C);
                if (o != 0) {
                    o->desc->m02(o);
                    loud = 1;
                }
                if (HasNoActiveObject89(self)) {
                    StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E20, 0.0f, 0.0f, 0, 0);
                } else {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E24, 0.0f, 0.0f, 0, 0);
                }
                break;
            }
            case 0:
            case 1:
                loud = 1;
                if (self->f2220 != 2 || (self->f2228 != 12 && self->f2228 != 13)) {
                    StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E20, 0.0f, 0.0f, 0, 0);
                }
                break;
            }
            self->f2684 = -1;
            if (loud) {
                PS(void*, 0x26A4) = PushSoundLevel(-20);
            }
            break;
        }
        case 9: {
            Vec02 d;
            if (self->f26D4 != 0) {
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->f26D4)->v140), Vu0::Q(g_player->v140));
            } else {
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->f40), Vu0::Q(g_player->v140));
            }
            self->f638 = ArctangentOfRatio(d.y, d.x);
            TurnColliderTowardHeading(self);
            Vu0::Q(self->v640) = Vu0::Zero();
            func_001C61E0(self, -1);
            break;
        }
        case 11:
            func_001C61E0(self, -1);
            SetColliderAnchors(self, 3, 0, 3, 0);
            SetColliderTreeContactsDropped(self, 1);
            Vu0::Q(self->v640) = Vu0::Zero();
            self->f690 = 0;
            break;
        case 10:
            func_001C61E0(self, -1);
            self->f25EC = 0;
            TurnPlayerToClass75AheadMask8(self);
            break;
        case 12:
            Vu0::Q(self->v640) = Vu0::Zero();
            break;
        case 13:
            self->flags538 |= (u64)1 << 40;
            self->radius3CC = D_00262E30;
            PS(void*, 0x273C) = self->hook;
            self->hook = 0;
            if (self->f1390[13] != 0) {
                func_001C4D60(self, 0, 0);
            }
            self->v640 = D_00248D30;
            func_001C61E0(self, -1);
            break;
        case 16:
            self->v640 = D_00248D30;
            break;
        case 14: {
            BaseObject* o = (BaseObject*)self->f2750;
            if (IsObjectAttached(o)) {
                TakeCountedColliderTouch(self->f2750, self, 1);
            }
            o = (BaseObject*)self->f2750;
            o->desc->m02(o);
            o = (BaseObject*)self->f2750;
            o->desc->m15(o, self);
            o = (BaseObject*)self->f2750;
            o->desc->m03(o);
            anim = PS(void*, 0x274C);
            self->v640 = D_00248D30;
            break;
        }
        case 15:
            anim = PS(void*, 0x2754);
            self->v640 = D_00248D30;
            break;
        }
        ReleaseFarPlayerLinks(self);
    }

    if (self->f2228 != sub) {
        switch (self->f2228) {
        case 17:
            self->fA14 = -1;
            break;
        case 5: {
            Collider* held = (Collider*)self->heldObject;
            self->heldObject = 0;
            InitContactPairFlags(held->world, held);
            break;
        }
        case 4:
            if (state != 6 || self->f239C != 2) {
                Collider* held = (Collider*)self->heldObject;
                self->heldObject = 0;
                InitContactPairFlags(held->world, held);
            }
            ((Attachment*)self->f2514)->mode0 = -1;
            self->desc02()->m2B(self);
            self->v640 = D_00248D30;
            break;
        case 9:
            if (self->f23B4 != 0) {
                Collider* c = AT(Collider*, self->f23B4, 0x60);
                if (c != 0) {
                    c->f4E0 = 0;
                }
                self->f23B4 = 0;
            }
            ((Attachment*)self->f2514)->mode0 = -1;
            self->desc02()->m2B(self);
            self->v640 = D_00248D30;
            break;
        case 10:
            if (state != 6 || self->f239C != 5) {
                self->f23B8 = 0;
            }
            ((Attachment*)self->f2514)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 11:
            if (state != 6 || self->f239C != 4) {
                self->f23BC = 0;
            }
            ((Attachment*)self->f2514)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 13:
            if (state != 6 || self->f239C != AT(s32, self->f23A8, 0x58)) {
                self->f23A8 = 0;
            }
            ((Attachment*)self->f2514)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 12:
            if (state != 6 || self->f239C != AT(s32, self->f23A0, 0x40)) {
                self->f23A0 = 0;
            }
            ((Attachment*)self->f2514)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 7:
        case 8: {
            if (self->f223C == -1) {
                self->f2200 = 0;
                self->f2204 = 0;
            }
            BaseObject* o = (BaseObject*)self->f25D8[1];
            if (o != 0) {
                o->desc->m03(o);
            }
            o = (BaseObject*)self->f25D8[3];
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 44:
            SetColliderTreeContactsDropped(self, 0);
            FillMemory(&self->f2B70, 0, 0x20);
        case 14:
        case 15:
            ((Attachment*)self->f2514)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 23:
            if (state == 7) {
                func_001C61E0(self, self->f1018 != 0 ? 10 : 2);
            }
            break;
        case 34: {
            f32 full = 1.0f;
            SetVolumeChannelFactor(5, 0, full);
            SetVolumeChannelFactor(5, 1, full);
            break;
        }
        case 39:
        case 47:
            AT(Vec02, PS(void*, 0x2490), 0x300) = D_00248D30;
            break;
        case 28:
            if (self->f2674 != 0) {
                SetOnOffObjectForcedState((void*)self->f2674, 0);
                self->f2674 = 0;
            }
            break;
        case 55: {
            BaseObject* o = (BaseObject*)self->f25D8[4];
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        }

        switch (sub) {
        case -1:
            break;
        case 0: {
            Vec02 v;
            self->f2268 = 0;
            self->f2498 = 1;
            self->f2270 = 0;
            f32 now = g_gameTime[0];
            self->f227C = now;
            self->f2278 = now;
            self->f2274 = now;
            self->f226C = D_00262E14 * Fpu::Sqrt(self->f700);
            self->f690 = 0;
            StartSoundEffect(0x4F, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            ComputePlayerJumpVelocity(self, &v);
            switch (self->f224C) {
            case 1:
                anim = PS(void*, 0x1028);
                break;
            case 4:
                self->f226C *= D_00262E1C;
                anim = PS(void*, 0x1028);
                break;
            case 3:
                self->f226C *= D_00262E18;
                anim = PS(void*, 0x1028);
                break;
            case 0:
            case 2:
                if (self->f224C == 2) {
                    anim = PS(void*, 0x1024);
                } else {
                    anim = PS(void*, 0x1020);
                }
                break;
            }
            if (anim == 0) {
                anim = PS(void*, 0x1020);
            }
            if (self->f224C == 4 && self->f634 == 0.0f) {
                ComputePolarOffset(&v, self->f638, 100.0f, v.z);
                self->f2270 = 3;
            } else {
                ComputePolarOffset(&v, self->f630, self->f226C * self->f634, v.z);
            }
            self->desc02()->m20(self, &v);
            break;
        }
        case 1:
            skip = 1;
            break;
        case 2:
            if (self->f2228 != 1 && self->f2228 != 5) {
                switch (self->f224C) {
                case 1:
                case 3:
                case 4:
                    anim = PS(void*, 0x1028);
                    break;
                case 0:
                    anim = PS(void*, 0x1020);
                    break;
                case 2:
                    anim = PS(void*, 0x1024);
                    break;
                }
                start = GetAnimationMarkerTime((Animation*)anim, 0x134);
            } else {
                skip = 1;
            }
            break;
        case 4:
            ((Attachment*)self->f2514)->mode0 = 4;
            self->desc02()->m2B(self);
            if (self->f2220 == 2) {
                skip = 1;
            } else {
                anim = PS(void*, 0x1020);
            }
            InitContactPairFlags(((Collider*)self->heldObject)->world, self->heldObject);
            Vu0::Q(self->v640) = Vu0::Zero();
            break;
        case 9: {
            ((Attachment*)self->f2514)->mode0 = 4;
            self->desc02()->m2B(self);
            if (self->f2220 == 2) {
                skip = 1;
            } else {
                anim = PS(void*, 0x1020);
            }
            Vu0::Q(self->v640) = Vu0::Zero();
            Collider* c = AT(Collider*, self->f23B4, 0x60);
            anim = PS(void*, 0x1030);
            if (c != 0) {
                c->f4E0 = 3;
            }
            break;
        }
        case 10:
        case 11: {
            Vec02 v;
            func_0017FC48(self, &v);
            self->desc02()->m20(self, &v);
            ((Attachment*)self->f2514)->mode0 = 4;
            self->desc02()->m2B(self);
            anim = PS(void*, 0x1030);
            self->f2498 = 0;
            *(Vu0::Vec*)&self->v640 = Vu0::Vec::Zero();
            StartSoundEffect(0x50, 0, 0, 0, 3000.0f, 300.0f, D_00263994, D_00263998, 0.0f, 0, 0);
            break;
        }
        case 12:
        case 13:
        case 14:
        case 15:
            skip = 1;
            ((Attachment*)self->f2514)->mode0 = 4;
            self->desc02()->m2B(self);
            Vu0::Q(self->v640) = Vu0::Zero();
            self->f2498 = 0;
            if (sub == 12 || sub == 13) {
                StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E20, 0.0f, 0.0f, 0, 0);
            }
            break;
        case 5: {
            Vec02 v;
            anim = PS(void*, 0xE2C);
            Vu0::Q(v) = Vu0::Add(Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::Scalar(Fpu::Sqrt(self->f700) * 800.0f)), Vu0::Q(self->v150));
            self->desc02()->m20(self, &v);
            self->f2498 = 1;
            break;
        }
        case 6:
            self->f2498 = 1;
            self->f2268 = 1;
            self->f2270 = 2;
            self->f226C = D_00262E14 * Fpu::Sqrt(self->f700);
            self->v2290 = self->v150;
            Vu0::Q(self->v640) = Vu0::Zero();
            self->f690 = 0;
            anim = PS(void*, 0x1020);
            self->v2290.z = 0.0f;
            break;
        case 44:
            self->f2498 = 1;
            self->f690 = 0;
            if (self->f2730 != 0) {
                anim = self->f109C[43];
            } else {
                anim = PS(void*, 0x1020);
            }
            Vu0::Q(self->v640) = Vu0::Zero();
            if (self->f2B70 != 0 && IsObjectOfKind(self->f2B70, 0x70)) {
                self->f638 = ArctangentOfRatio(self->v150.y, self->v150.x);
                TurnColliderTowardHeading(self);
            }
            ((Attachment*)self->f2514)->mode0 = 4;
            self->desc02()->m2B(self);
            SetColliderTreeContactsDropped(self, 1);
            self->f690 = 0;
            break;
        case 7:
            self->f25EC = 0;
            self->f2268 = 1;
            sound = 10;
            Vu0::Q(self->v640) = Vu0::Zero();
            anim = PS(void*, 0x25C0);
            TurnPlayerToClass75AheadMask4(self);
            self->f2424 = g_gameTime[0] + D_0026399C;
            break;
        case 8:
            Vu0::Q(self->v640) = Vu0::Zero();
            self->f2268 = 1;
            self->f25EC = 0;
            anim = self->f25C8;
            break;
        case 3: {
            Vec02 v;
            self->f2498 = 0;
            anim = PS(void*, 0x1034);
            func_0017FCC8(self, &v);
            self->desc02()->m20(self, &v);
            break;
        }
        case 16:
        case 21:
            switch (self->f239C) {
            case 0:
                anim = PS(void*, 0xB24);
                break;
            case 2:
                anim = PS(void*, 0xE24);
                break;
            case 1:
            case 3:
                anim = PS(void*, 0xC34);
                break;
            case 5:
                walker = self->f1188;
                walkerId = 0x14C;
                break;
            case 4:
                if (AT(s32, self->f23BC, 0x40) != 0 && self->f1090 != 0) {
                    anim = self->f1090;
                    self->f1094 = self->f1098 = 0.0f;
                } else {
                    walker = self->f1188;
                    walkerId = 0x14D;
                }
                layers = 3;
                break;
            case 6:
                anim = PS(void*, 0x1014);
                break;
            case 7:
                anim = 0;
                break;
            }
            break;
        case 17:
            switch (self->f239C) {
            case 0:
                speed = 2.0f;
                anim = PS(void*, 0xB20);
                if (self->f2674 == 0) {
                    if (self->f23A0 != 0) {
                        void* o = self->f23A0;
                        if (AT(s32, o, 0x4C) == 0) {
                            self->f2674 = 0;
                        } else if (AT(s32, o, 0x48) != 0) {
                            self->f2674 = AT(s32, o, 0x48);
                        } else {
                            self->f2674 = (s32)self->f2678;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->f2674;
                            p->desc->m15(p, AT(BaseObject*, self->f23A0, 0x18));
                            ((OnOffObject*)self->f2674)->obj = AT(Arr63*, self->f23A0, 0x34);
                        }
                    } else if (self->f23A8 != 0) {
                        void* o = self->f23A8;
                        if (AT(s32, o, 0x68) == 0) {
                            self->f2674 = 0;
                        } else if (AT(s32, o, 0x64) != 0) {
                            self->f2674 = AT(s32, o, 0x64);
                        } else {
                            self->f2674 = (s32)self->f2678;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->f2674;
                            p->desc->m15(p, AT(BaseObject*, self->f23A8, 0x18));
                            ((OnOffObject*)self->f2674)->f38C = 1;
                            ((OnOffObject*)self->f2674)->v400 = AT(Vec02, self->f23A8, 0x40);
                            ((OnOffObject*)self->f2674)->f410 = AT(f32, self->f23A8, 0x5C);
                        }
                    }
                    if ((OnOffObject*)self->f2674 == self->f2678) {
                        const Vec02* z = &D_00248D30;
                        OnOffObject* p = (OnOffObject*)self->f2674;
                        p->desc02()->m1D(p, (Vec02*)z);
                        p = (OnOffObject*)self->f2674;
                        p->desc02()->m1E(p, (Mat02*)&g_identityMatrix);
                        p = (OnOffObject*)self->f2674;
                        p->desc02()->m20(p, (Vec02*)z);
                        p = (OnOffObject*)self->f2674;
                        p->desc02()->m21(p, (Vec02*)z);
                    }
                    if (self->f2674 != 0) {
                        ((OnOffObject*)self->f2674)->f2D0 = self;
                        SetOnOffObjectForcedState((void*)self->f2674, 1);
                    }
                }
                break;
            case 1:
                speed = 1.75f;
                anim = PS(void*, 0xC30);
                break;
            case 3:
                anim = (void*)self->fA10;
                break;
            }
            break;
        case 20:
            switch (self->f239C) {
            case 2:
                anim = PS(void*, 0xE20);
                break;
            case 3:
                anim = (void*)self->f900;
                break;
            case 4:
                anim = PS(void*, 0x1010);
                break;
            }
            break;
        case 19:
            switch (self->f239C) {
            case 0:
                anim = PS(void*, 0xB2C);
                break;
            case 1:
                anim = PS(void*, 0xC3C);
                break;
            }
            break;
        case 18:
            switch (self->f239C) {
            case 0:
                anim = PS(void*, 0xB28);
                break;
            case 1:
                anim = PS(void*, 0xC38);
                break;
            }
            break;
        case 23:
            anim = PS(void*, 0x1060);
            if (anim == 0) {
                anim = PS(void*, 0x1068);
                start = ((Animation*)anim)->length * 0.5f;
                speed = 0.5f;
            }
            self->f2418 = 0.0f;
            break;
        case 24:
            anim = self->f1064;
            break;
        case 25:
            anim = self->f105C;
            break;
        case 26:
            anim = self->f105C;
            speed = -1.0f;
            break;
        case 27:
            anim = PS(void*, 0x1068);
            self->f221C = !self->f221C;
            break;
        case 28:
        case 29:
        case 30:
            anim = self->f109C[sub];
            if (sub == 28 && PS(void*, 0x267C) != 0) {
                self->f2674 = PS(s32, 0x267C);
                SetOnOffObjectForcedState(PS(void*, 0x267C), 1);
            }
            if (sub == 30) {
                self->desc05()->m4F(self, 3);
            }
            PopActiveSequenceElement(self->world);
            break;
        case 31:
            anim = PS(void*, 0x25B8);
            sound = 14;
            break;
        case 32:
            anim = PS(void*, 0x25BC);
            break;
        case 33:
            if (PS(void*, 0x25CC) != 0) {
                anim = PS(void*, 0x25CC);
            }
            PushCameraController(g_camera, 6, (u8*)g_camera + 0x460, self, 0);
            break;
        case 34: {
            f32 dim = 0.6f;
            SetVolumeChannelFactor(5, 0, dim);
            SetVolumeChannelFactor(5, 1, dim);
            StartCameraSounds((u8*)g_camera + 0x460);
            RequestCameraSnap(g_camera, 0);
            g_typedTextCaptionBox.child = self->f2BD0;
            self->f2BD0 = 0;
            PushStackElement(g_elementStack, &g_typedTextCaptionBox);
            break;
        }
        case 35:
            if (PS(void*, 0x25D0) != 0) {
                anim = PS(void*, 0x25D0);
            }
            RemoveCameraControllers(g_camera, 0xF, 6, (u8*)g_camera + 0x460, self, 0);
            RequestCameraSnap(g_camera, 0);
            break;
        case 39:
        case 45:
        case 46:
        case 47:
            if (sub == 45) {
                u128 vel = Vu0::Q(self->v150);
                if (-250.0f < Vu0::ToFloatMoved(Vu0::Dot(vel, Vu0::Q(self->m660.r[0])))) {
                    sub = 46;
                } else {
                    f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(vel, vel)));
                    f32 k = D_002639A0[0] + len * (D_002639A0[1] + len * D_002639A0[2]);
                    f32* range = g_unitRange;
                    f32 lo = range[0];
                    f32 hi = range[1];
                    f32 r;
                    if (k < lo) {
                        r = lo;
                    } else if (hi < k) {
                        r = hi;
                    } else {
                        r = k;
                    }
                    self->f638 = WrapAngle(self->f638 + WrapAngle(ArctangentOfRatio(self->v150.y, self->v150.x) + 3.14159274f - self->f638) * r);
                    TurnColliderTowardHeading(self);
                }
            }
            anim = self->f109C[sub];
            if (sub == 47 || sub == 39) {
                if (PS(void*, 0x2490) != 0) {
                    AT(Vec02, PS(void*, 0x2490), 0x300) = *(Vec02*)D_00263980;
                }
            }
            if (sub == 47) {
                Vec02 d;
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->f40), Vu0::Q(self->v140));
                self->f638 = ArctangentOfRatio(d.y, d.x);
            }
            break;
        case 41:
        case 48: {
            Vec02 d;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->f40), Vu0::Q(self->v140));
            self->f638 = ArctangentOfRatio(d.y, d.x);
            anim = self->f109C[sub];
            break;
        }
        case 36:
        case 42:
        case 43:
            anim = self->f109C[sub];
            break;
        case 40:
        case 49:
            self->desc02()->m21(self, (Vec02*)&D_00248D30);
            self->f638 = self->f630 = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
            anim = self->f109C[sub];
            break;
        case 37:
        case 38:
            flag = 0;
            self->f638 = self->f630 = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
            anim = self->f109C[sub];
            if (D_002639B8 != 0) {
                speed = 0.0f;
            }
            break;
        case 50:
        case 51:
        case 52:
            if (self->watched2230 != 0 && AT(void*, self->watched2230, 8) == self->f2384) {
                skip = 1;
                break;
            }
            anim = self->f2384;
            speed = 0.0f;
            start = ((Animation*)anim)->length * 0.5f;
            break;
        case 53:
            walker = self->f1188;
            walkerId = 0x14B;
            break;
        case 55: {
            Vec02 v;
            u128 vel = Vu0::Q(self->v150);
            f32 most = D_00262E2C;
            Vu0::Q(v) = vel;
            s32 slow = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(vel, vel))) < D_002639B0[0];
            if (slow) {
                ComputePolarOffset(&v, self->f638, most, 0.0f);
            } else {
                f32 len = Vu0::ToFloatMoved(Vu0::Length(vel));
                if (len < most) {
                    Vu0::Q(v) = Vu0::MulX(vel, Vu0::Scalar(most / len));
                }
            }
            self->desc02()->m20(self, &v);
            v.z = 0.0f;
            Vu0::Vec len = NormalizeInPlace_175170(v, D_00248D30);
            f32 k = Vu0::ToFloatMoved(len) / self->radius3CC;
            Vec02 spin;
            Vu0::Q(spin) = Vu0::FromFloats(-k * v.y, k * v.x, 0.0f);
            self->desc02()->m21(self, &spin);
            anim = PS(void*, 0x25D4);
            if (self->f25D8[4] != 0) {
                if (MaskWorldBitsBySave() & 0x400) {
                    BaseObject* o = (BaseObject*)self->f25D8[4];
                    o->desc->m02(o);
                }
            }
            break;
        }
        case 54:
        case 56:
            anim = PS(void*, 0x25D4);
            break;
        case 57:
            anim = PS(void*, 0x2760);
            break;
        case 58:
            anim = PS(void*, 0x2764);
            break;
        }
    }

    if (state != self->f2220) {
        self->f2220 = state;
        self->f2224 = g_gameTime[0];
    }
    if (sub != self->f2228) {
        self->f2228 = sub;
        self->f222C = g_gameTime[0];
    }
    SelectPlayerStateAnimation(self);
    SetPlayerPartLayers(self, layers);
    if (sound != -1) {
        StartSoundEffect(sound, 0, 0, &self->v140, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    if (!skip) {
        StopPlayerAnimation(self);
        if (anim != 0) {
            AnimArg_175170 args[2];
            AnimArg_175170* arg = args;
            if (self->heldObject != 0) {
                arg->id = 0x61;
                arg->value = self->heldObject;
                arg++;
            }
            CreateAnimationPlayer(anim, self, arg - args, args, flag, &self->watched2230, start, speed);
        } else if (walker != 0) {
            self->f2234 = CreateStateWalker(walker, self, walkerId, flag);
        }
    }
}

#undef AT
#undef PS
