// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x19E040 to 0x1A3AE0 (its .rodata from 0x24C930, its .data from 0x26B530): the
// effect owner (class 0x1E) and the effects it runs (CreateEffect makes one; GetEffectKindTable
// picks its kind's table of functions, the 27 tables at 0x219C20 in
// src/main/class_descriptors.cpp), with their VU0 helpers. It starts at an exact edge
// (group_marker.cpp's end). Its end is NOT proved by retail: the cut at 0x1A3AE0 follows the change
// of role only, from the effects to the walker collider (class 0x15) and the unrelated families
// of pair_controller.cpp, which no function on either side calls across. Retail's data allows it:
// the last of this file's .rodata (FLT_MAX at 0x24C9BC) and .data (D_0026B770) are read before
// 0x1A3598, the next file's first (0x24C9C0, D_0026B778) from 0x1A3B20 on, and no gap of
// padding marks either edge, so the cut could lie at any function start from 0x1A3598 to
// 0x1A3B20, or the two could be one file. Its name is ours, after its role.
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
#include "aim_blend_grid.h"
#include "effect_owner.h"
#include "effect_spawner.h"
#include "world.h"
#include "camera.h"
#include "object_gatherer.h"
#include "switched_collider.h"
#include "packet_writer.h"
#include "effect.h"
#include "globals.h"
#include "group_marker.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "paired_object.h"
#include "hit_target.h"
#include "sound_state_object.h"
#include "object_creator.h"
#include "object_pool.h"
#include "pair_controller.h"
#include "screen_element.h"
#include "shapes.h"
#include "object_link.h"
#include "target_binding.h"
#include "game_progress.h"
#include "object_message.h"
#include "object_event.h"
#include "pad_record.h"
#include "animation.h"
#include "attachment.h"
#include "message_body.h"
#include "asm_func.h"
#include "mul_rotation.h"
#include "ramp_profile.h"
#include "node_query.h"
#include "object_finder.h"
struct BriefEffectSource;


void AddCallbackNode(World* world, Callback01** head, void* fn, void* ctx);
void RemoveCallbackNode(World* mgr, Callback01** link, void* fn, void* ctx);



void InitCollider(Collider* self);

void SetListLinkOffset(List01* self, s32 offset);

void* PopFreeSlot(Pool6C* pool);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

const Vt219C* GetEffectKindTable(u32 n);

void AppendToList(List01* self, void* item);

void CountEffectUse(Effect* self);

void RemoveFromList(List01* list, void* item);

void ReleaseEffect(Effect* self);

void ReleaseCallRecords(World* self, T219CHook* node);

void PushFreeSlot(Pool6C* list, void* item);

extern f32 g_gameClock[];

void InitEffect(Effect* self, void* pos, f32 scale, s32 flags);



extern f32 g_gameTime;

void RemoveEffect(Effect* self);

s32 IsObjectAttached(BaseObject* self);

struct TreeNode03;
s32 FindPlaneTreeNodeForPoint(Vec02* pos, TreeNode03* nodes);

struct Oscillator;
void ComputeOscillatorDisplacement(Oscillator* self, f32 time, Vec02* in, Vec02* deltas, Vec02* outA, Vec02* outDeltas, Vec02* outB);

s32 DrawEffectAt(Effect* self, Camera* cam, Vec02* pos, f32 (*rot)[4]);
void BuildBasisFromXAndZHint(const Vec02* x, const Vec02* hint, Mat02* out);
void BuildBasisFromXAndYHint(Vec02* x, Vec02* hint, Mat02* out);





s32 CollectTreeNodeSpans(TreeNode03* root, Vec02* a, Vec02* b, s32* groups, s32 max, ColliderSpan* spans);

Effect* CreateEffect(s32 kind, EffectOwner* sys);


extern Camera* g_camera;






void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

// A list walk whose frame pushes itself when it is made and pops itself when it goes out of scope.
struct ListWalk : ListFrame {
    ListWalk(List01* l)
    {
        list = l;
        link = (u8*)l;
        offset = l->offset;
        prev = g_activeListFrames;
        g_activeListFrames = this;
    }
    ~ListWalk() { g_activeListFrames = prev; }
    // The list's first element, from the list's head.
    void* First()
    {
        void* n = *(void**)list;
        link = (u8*)n + offset;
        return n;
    }
    void* Next()
    {
        void* n = *(void**)link;
        link = (u8*)n + offset;
        return n;
    }
};

void RemoveEffect(Effect* self);

void UnregisterCollider(Collider* self);

// An entry of the effect kinds' tables of functions (src/main/class_descriptors.cpp).
typedef void (*Fn_Table)();

extern const Fn_Table g_basicEffectMethods[];

extern const Fn_Table g_fallingEffectMethods[];

extern const Fn_Table g_risingEffectMethods[];

extern const Fn_Table g_impactEffectMethods[];

extern const Fn_Table g_growingEffectMethods[];

extern const Fn_Table g_shrinkingFallEffectMethods[];

extern const Fn_Table g_droppingEffectMethods[];

extern const Fn_Table g_streakEffectMethods[];

extern const Fn_Table g_scaledEffectMethods[];

extern const Fn_Table g_trailSegmentEffectMethods[];

extern const Fn_Table g_spawningEffectMethods[];

extern const Fn_Table g_followUpEffectMethods[];

extern const Fn_Table g_wideTrailSegmentEffectMethods[];

extern const Fn_Table g_shortFallingEffectMethods[];

extern u8 g_emitterEffectMethods[];

extern const Fn_Table g_cameraSpaceEffectMethods[];

extern const Fn_Table g_longStreakEffectMethods[];

extern const Fn_Table g_phasedEffectMethods[];

extern const Fn_Table g_projectileEffectMethods[];

extern const Fn_Table g_hitMarkEffectMethods[];

extern const Fn_Table g_tumblingEffectMethods[];

extern const Fn_Table g_aimedEffectMethods[];

extern const Fn_Table g_streakedEffectMethods[];

extern const Fn_Table g_spinningEffectMethods[];

extern const Fn_Table g_facingEffectMethods[];

extern const Fn_Table g_delayedEffectMethods[];

extern const Fn_Table g_messageEffectMethods[];

// The loop walks an intrusive list with an iterator that registers itself on a global stack
// (D_0027B314) for its lifetime and unregisters in its destructor.





void RemoveFromList(List01* list, void* item);

void AppendToList(List01* self, void* item);


void EndEffect();

s32 HandleEffectContact();

void MoveEffect();

void InitRisingEffect(Effect* self, void* pos, f32 scale, s32 flags);

void MoveDriftingEffect();

void EndEffectWithImpactOnExit();

void InitImpactEffect(Effect* self, void* pos, f32 scale, s32 flags);

void UpdateDroppingEffect();

void DrawDroppingEffect();

void EndDroppingEffect();

void InitStreakEffect(Effect* self, void* pos, f32 scale, s32 flags);

void DrawStreakEffect();

void InitScaledEffect(Effect* self, void* pos, f32 scale, s32 flags);

void InitTrailSegment(Effect* self, void* pos, f32 scale, s32 flags);

void DetachTrailSegment();

void MoveTrailSegment();

void DrawTrailSegment();

void InitSpawningEffect(Effect* self, void* pos, f32 scale, s32 flags);

void SpawnFollowUpEffect();

void InitFollowUpEffect(Effect* self, void* pos, f32 scale, s32 flags);

void InitWideTrailSegment(Effect* self, void* pos, f32 scale, s32 flags);

void InitShortFallingEffect(Effect* self, void* pos, f32 scale, s32 flags);

void InitCameraSpaceEffect(Effect* self, void* pos, f32 scale, s32 flags);

void MoveCameraSpaceEffect();

void DrawCameraSpaceEffect();

void RunEffectEndCallback();

void InitLongStreakEffect(Effect* self, void* pos, f32 scale, s32 flags);

void InitPhasedEffect(Effect* self, void* pos, f32 scale, s32 flags);

void KeepPhasedEffectStill();

void AdvanceEffectPhases();

void DrawPhasedEffect();

void CopyEffectSourceIds();

void DrawProjectileEffect();

s32 HandleEffectImpact();

void UpdateEffectUntilDetached(Effect* self, f32 dt);

void DrawHitMarkEffect();

void SetRandomEffectSpin();

void MoveTumblingEffect();

s32 HandleTumblingEffectImpact();

void AimEffectAtNearestObject();

void PlaceEffectAtSource();

void DrawStreakedEffect();

s32 HandleStreakedEffectImpact();

void RandomizeEffectSpin();

s32 HandleEffectContactUnlessKind6();

void DrawSpinningEffect();

void InitFacingEffect(Effect* self, void* pos, f32 scale, s32 flags);

void DrawFacingEffect();

void InitDelayedEffect(Effect* self, void* pos, f32 scale, s32 flags);

void MoveDelayedEffect();

void UpdateDelayedEffect();

void DrawDelayedEffect(Effect* self, void* a1);

void ResolveEffectTarget();

void SendEffectMessagesAtRate();

void CountEffectUse(Effect* node);

void ReleaseEffect(Effect* node);

u32 IsListEmpty(List01* list);

void CollideEffects(EffectOwner* self);

void ClearRootTries(PlacedObject* self);

// The next object of a list walk, and the walk moved past it.
struct NextEffect {
    static Effect* Of(ListFrame* it)
    {
        Effect* obj = *(Effect**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

// A list walk's start: the frame takes the list and is pushed.
struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

struct NextListItem {
    static u8* Of(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct EndListWalk {
    static void Of(ListFrame* it)
    {
        g_activeListFrames = it->prev;
    }
};

void PushBackMemoryMark(void);

void* AllocateBackMemory(s32 size);

void PopBackMemoryMark(void);

struct PlaneTreeNode;
struct PlaneTreeOutput;
s32 QueryPlaneTreePoint(PlaneTreeNode* node, Vec02* p, f32 eps, PlaneTreeOutput* out);

s32 CollectColliderSpansInTree(Collider* self, void* a1, void* a2, void* a3, s32 a4, ColliderSpan* a5);

u32 IsListEmpty(List01* p);


void UpdateEffect(Effect* self, f32 dt);

s32 IsObjectAttached(BaseObject* self);

extern Quad219C D_00275C50;

void SetTrailSegmentAnchor(void* selfv, s32 kind, void* extra);

void InitStreakEffect(Effect* self, void* pos, f32 scale, s32 flags);

void SetEffectPhase(Effect* self, s32 mode);

// A 0x30-byte point func_001A1F40 sorts by its angle about a centre (its position at 0x10, the
// angle at 0x20).
struct AngledPoint { u8 pad00[0x20]; f32 angle; };



extern s32 D_0026B6C0[4];

void AttachHitMarkEffect(Effect* self, s32 target, void* other, Vec02* point, Vec02* normal, Effect** out);

s32 IsObjectOfKind(BaseObject* list, s32 key);

s32 HandleEffectContact(Effect* self, void* b, void* c, void* d);



void TakeDelayedEffectSourcePose(Effect* self);

void DrawEffect(Effect* self, void* a1);

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

void TransformRotationBetweenFrames(PlacedObject* from, PlacedObject* to, Mat02* in, Mat02* out);


s32 IsObjectOfKind(BaseObject* list, s32 key);





extern f32 D_0026B5B0[4];

extern f32 D_0026B5C0[4];


extern f32 D_0026B710[4];

extern f32 D_0026B720[4];

void InitEffect(Effect* self, void* pos, f32 scale, s32 flags);


void UpdateEffect(Effect* self, f32 dt);

// A quadword in a 128-bit register (the VU0 helpers func_00118D20 and func_00118D30).
typedef int Quadword128 __attribute__((mode(TI)));

void InitEffect(Effect* self, void* pos, f32 scale, s32 flags);

void *StoreFloatAsQuadword(u128* out, f32 f);

void* CopyQuadword(u128* out, void* src);

Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);

void* StoreQuadword(u128* out, u128 v);

extern f32 D_0026B570[4];

extern f32 D_0026B580[4];

extern f32 D_0026B5D0[4];

extern f32 D_0026B5E0[4];

void SetTrailSegmentAnchor(void* selfv, s32 kind, void* extra);

extern Vec02 D_0026B560;

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

extern f32 D_0026B6A0[4];

extern f32 D_0026B6B0[4];

void* StoreQuadword(u128* out, u128 v);

extern f32 D_0026B590[4];

extern f32 D_0026B5A0[4];

s32 IsObjectOfKind(BaseObject* list, s32 key);

void RemoveFromList(List01* list, void* item);

void AppendToList(List01* self, void* item);

f32 RandomFloatInRange(f32 a, f32 b);

void InitCollider(Collider* self);

void RemoveFromList(List01* list, void* item);

void AppendToList(List01* self, void* item);

void RemoveFromList(List01* list, void* item);

void AppendToList(List01* self, void* item);

void RemoveFromList(List01* list, void* item);

void SetListLinkOffset(List01* self, s32 offset);


// The coefficients of a quadratic in t (a + bt + ct^2), as the pose holds them.
struct QuadraticCoeffs { f32 a, b, c; };

// A quadratic evaluated at t and clamped to a range (func_001A5760).
struct ClampedQuadratic {
    static f32 Eval(const QuadraticCoeffs* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
    static void Clamp(f32& c, f32 v, const ValueRange* r)
    {
        f32 lo = r->lo;
        f32 hi = r->hi;
        if (v < lo) {
            c = lo;
        } else if (hi < v) {
            c = hi;
        } else {
            c = v;
        }
    }
    static void Get(f32& c, const QuadraticCoeffs* p, f32 t)
    {
        Clamp(c, Eval(p, t), &g_unitRange);
    }
};

// The file's .data (0x26B530 to 0x26C3E0), all initialised, in address order.

f32 D_0026B530[4] = { 1.0f, 1.666667f, -2.666667f, 0.0f };

f32 D_0026B540 = 0.5f;

f32 D_0026B544 = 0.5f;

f32 D_0026B548 = 1.5f;

f32 D_0026B54C = 200.0f;

// The life left to an effect that falls below the floor (HandleEffectContact reads it as a float).
f32 D_0026B550 = 0.25f;

// A size curve, read as one quadword (InitScaledEffect): 16-aligned, which leaves retail's 12
// bytes of zeros after the float before it.
Vec02 D_0026B560 = { 0.5f, 2.0f, -2.0f, 0.0f };

f32 D_0026B570[4] = { 0.5f, -0.5f, 0.0f, 0.0f };

f32 D_0026B580[4] = { 1.0f, -1.0f, 0.0f, 0.0f };

f32 D_0026B590[4] = { 0.0f, 2.0f, -1.0f, 0.0f };

f32 D_0026B5A0[4] = { 4.0f, -4.0f, 0.0f, 0.0f };

f32 D_0026B5B0[4] = { 0.699999988079071f, 0.0f, -0.699999988079071f, 0.0f };

f32 D_0026B5C0[4] = { 0.0f, 0.0f, 50.0f, 0.0f };

f32 D_0026B5D0[4] = { 0.75f, -0.75f, -0.0f, 0.0f };

f32 D_0026B5E0[4] = { 1.0f, 2.0f, -3.0f, 0.0f };

f32 D_0026B5F0[4] = { 0.5f, 0.0f, 0.0f, 0.0f };

f32 D_0026B600[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

f32 D_0026B610[4] = { 1.0f, -0.7f, 0.0f, 0.0f };

f32 D_0026B620[4] = { 135.0f, 0.0f, -85.0f, 0.0f };

f32 D_0026B630[4] = { 50.0f, 170.0f, -85.0f, 0.0f };

f32 D_0026B640[4] = { 1.0f, 0.0005f, 0.0f, 0.0f };

f32 D_0026B650[4] = { 1.0f, 10.0f, 0.0f, 0.0f };

f32 D_0026B660[4] = { 1.65f, -0.0002f, 0.0f, 0.0f };

f32 D_0026B670[4] = { 0.65f, 1.0f, 0.0f, 0.0f };

f32 D_0026B680[4] = { 0.0f, 6.0f, 0.0f, 0.0f };

f32 D_0026B690[4] = { 5.0f, 16.0f, 0.0f, 0.0f };

f32 D_0026B6A0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

f32 D_0026B6B0[4] = { 1.0f, -1.0f, 0.0f, 0.0f };

s32 D_0026B6C0[4] = { 0x40, 5, 0x42, 0x43 };

f32 D_0026B6D0[4] = { 0.0f, -0.01f, 0.0f, 0.0f };

f32 D_0026B6E0[2] = { -10.0f, 10.0f };

f32 D_0026B6E8 = -1.0f;

f32 D_0026B6EC = 200.0f;

f32 D_0026B6F0[4] = { 0.75f, 1.25f, 0.0f, 0.0f };

f32 D_0026B700[4] = { 0.0f, 0.001f, 0.0f, 0.0f };

f32 D_0026B710[4] = { 0.0f, 4.0f, -4.0f, 0.0f };

f32 D_0026B720[4] = { 0.25f, 3.0f, -3.0f, 0.0f };

f32 D_0026B730[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

f32 D_0026B740[4] = { 0.0f, 0.75f, 0.0f, 0.0f };

f32 D_0026B750[4] = { 1.0f, 5.0f, 0.0f, 0.0f };

f32 D_0026B760[4] = { 0.5f, 0.0f, 0.5f, 0.0f };

f32 D_0026B770[2] = { 0.5f, 1.0f };

EffectOwner* AcquireEffectOwner(World* self, s32 flag)
{
    if (flag == 0 && self->sharedEffectOwner != 0) {
        return self->sharedEffectOwner;
    }
    EffectOwner* n = self->freeEffectOwners;
    if (n != 0) {
        self->freeEffectOwners = n->saved564;
        n->exclusive = flag;
        n->desc->m02(n);
        if (flag == 0) {
            self->sharedEffectOwner = n;
        }
    }
    return n;
}

void InitEffectOwner(EffectOwner* self)
{
    InitCollider(self);
    SetListLinkOffset(&self->list558, 0x10);
    u64 flags = self->flags;
    flags &= (u64)(s64)(s32)0xCFFFFFFF;
    flags |= 0x20000000ULL;
    u64 wide = self->flags538;
    wide |= (u64)1 << 42;
    flags &= 0xFFFFFCFFFFFFFFFFULL;
    wide |= (u64)1 << 51;
    f32 k = 1e10f;
    flags |= (u64)1 << 40;
    self->flags538 = wide;
    self->fadeDistanceFar = k;
    self->flags = flags;
}

void CopyEffectOwnerMargin(EffectOwner* a, Rec50* b)
{
    a->boundsMargin = b->f1E8;
}

void ReleaseEffectOwner(EffectOwner* self)
{
    ListWalk cur(&self->list558);
    Effect* node = (Effect*)cur.First();
    while (node != 0) {
        RemoveEffect(node);
        node = (Effect*)cur.Next();
    }
    self->saved564 = self->world->freeEffectOwners;
    self->world->freeEffectOwners = self;
    if (self == self->world->sharedEffectOwner) {
        self->world->sharedEffectOwner = 0;
    }
    UnregisterCollider(self);
}

void MoveEffectsAndBounds(EffectOwner* self, f32 dt)
{
    ListWalk walk(&self->list558);
    self->boundsMin.x = self->boundsMin.y = self->boundsMin.z = 3.4028235e+38f;
    self->boundsMax.x = self->boundsMax.y = self->boundsMax.z = -3.4028235e+38f;
    Effect* e = (Effect*)walk.First();
    while (e != 0) {
        if (e->start <= g_gameClock[1]) {
            e->vt->m03(e, dt);
        }
        Vu0::Q(self->boundsMin) = Vu0::Min(Vu0::Q(self->boundsMin), Vu0::Min(Vu0::Q(e->pos), Vu0::Q(e->prevPos)));
        Vu0::Q(self->boundsMax) = Vu0::Max(Vu0::Q(self->boundsMax), Vu0::Max(Vu0::Q(e->pos), Vu0::Q(e->prevPos)));
        e = (Effect*)walk.Next();
    }
    if (self->boundsMargin != 0.0f) {
        Vec02 m;
        Vu0::Q(m) = Vu0::Splat(self->boundsMargin);
        Vu0::Q(self->boundsMin) = Vu0::Sub(Vu0::Q(self->boundsMin), Vu0::Q(m));
        Vu0::Q(self->boundsMax) = Vu0::Add(Vu0::Q(self->boundsMax), Vu0::Q(m));
    }
    Vec02 center;
    const Desc02* d = self->desc02();
    Vu0::Q(center) = Vu0::MulXSum(Vu0::Q(self->boundsMin), Vu0::Scalar(0.5f), Vu0::Q(self->boundsMax), Vu0::Scalar(0.5f));
    d->m1D(self, &center);
    f32 r = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(center), Vu0::Q(self->boundsMax))));
    self->radius3D0 = r;
    self->radius3CC = r;
    self->boundRadius = r;
    self->f2A4 = r;
}

void KeepEffectOwnerBounds(void) {}

void UpdateEffectOwner(EffectOwner* self, f32 t)
{
    ListFrame it;
    BeginListWalk::Of(&it, &self->list558);
    Effect* node;
    while ((node = NextEffect::Of(&it)) != 0) {
        if (node->start >= g_gameClock[1]) {
            continue;
        }
        CountEffectUse(node);
        node->vt->m04(node, t);
        ReleaseEffect(node);
    }
    s64 m = 0x8000;
    m <<= 23;
    if ((self->flags & m) != 0 || IsListEmpty(&self->list558) != 0) {
        self->desc->m03(self);
    } else {
        CollideEffects(self);
    }
    ClearRootTries(self);
    g_activeListFrames = it.prev;
}

void CollideEffects(EffectOwner* self)
{
    if (self->exclusive != 1) return;
    ContactRow03* l;
    for (l = self->contacts->head; l != 0; l = l->next) {
        ListFrame it0;
        BeginListWalk::Of(&it0, &l->other->parts);
        if (l->other->flags538 & ((u64)0x8000 << 27)) {
            EndListWalk::Of(&it0);
            continue;
        }
        Collider* s2;
        for (s2 = (Collider*)NextListItem::Of(&it0); s2 != 0; s2 = (Collider*)NextListItem::Of(&it0)) {
            ListFrame it1;
            void* buf;
            ColliderSpan hits[4];
            BeginListWalk::Of(&it1, &self->list558);
            if ((s2->flags538 & ((u64)0x8000 << 28)) && (s2->desc->flags & 0x80) == 0) {
                EndListWalk::Of(&it1);
                continue;
            }
            PushBackMemoryMark();
            if (s2->tree.count > 0) {
                buf = AllocateBackMemory(s2->tree.count2 * 12);
                if (QueryPlaneTreePoint((PlaneTreeNode*)s2->tree.nodes, &self->v140, self->radius3D0, (PlaneTreeOutput*)&buf) != 2) goto skip;
                buf = (u8*)buf - 12;
            } else {
                buf = 0;
            }
            {
                Effect* n;
                for (n = (Effect*)NextListItem::Of(&it1); n != 0; n = (Effect*)NextListItem::Of(&it1)) {
                    if (n->start >= g_gameClock[1]) continue;
                    s32 cnt = CollectColliderSpansInTree(s2, buf, &n->prevPos, &n->pos, 4, hits);
                    s32 i;
                    for (i = 0; i < cnt; i++) {
                        ColliderSpan* h = &hits[i];
                        if (h->time[0] == 0.0f) continue;
                        if (n->vt->m07(n, s2, h, &h->q[2]) != 0) break;
                    }
                }
            }
        skip:
            PopBackMemoryMark();
            EndListWalk::Of(&it1);
        }
        EndListWalk::Of(&it0);
    }
    if (IsListEmpty(&self->list558) != 0) {
        self->desc->m03(self);
    }
}

void DrawEffects(EffectOwner* self, void* arg, void* arg2)
{
    ListFrame fr;
    s32 e = (s32)&self->list558;
    fr.link = (u8*)e;
    fr.list = (void*)e;
    s32 old = (s32)g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    g_activeListFrames = &fr;
    fr.prev = (ListFrame*)old;
    s32 h = *(s32*)e;
    fr.offset = link;
    fr.link = (u8*)(h + link);
    s32 n = h;
    while (n != 0) {
        Effect* node = (Effect*)n;
        if (node->start >= g_gameClock[1]) {
        } else {
            node->vt->m05(node, arg);
        }
        s32 nx = *(s32*)fr.link;
        s32 lk = fr.offset;
        fr.link = (u8*)(nx + lk);
        n = nx;
    }
    g_activeListFrames = fr.prev;
}

const Vt219C* GetEffectKindTable(u32 n)
{
    switch (n) {
    case 0: return (const Vt219C*)(g_basicEffectMethods);
    case 2: return (const Vt219C*)(g_fallingEffectMethods);
    case 3: return (const Vt219C*)(g_risingEffectMethods);
    case 4: return (const Vt219C*)(g_impactEffectMethods);
    case 5: return (const Vt219C*)(g_growingEffectMethods);
    case 6: return (const Vt219C*)(g_shrinkingFallEffectMethods);
    case 7: return (const Vt219C*)(g_droppingEffectMethods);
    case 8: return (const Vt219C*)(g_streakEffectMethods);
    case 9: return (const Vt219C*)(g_scaledEffectMethods);
    case 10: return (const Vt219C*)(g_trailSegmentEffectMethods);
    case 11: return (const Vt219C*)(g_spawningEffectMethods);
    case 12: return (const Vt219C*)(g_followUpEffectMethods);
    case 13: return (const Vt219C*)(g_wideTrailSegmentEffectMethods);
    case 14: return (const Vt219C*)(g_shortFallingEffectMethods);
    case 15: return (const Vt219C*)g_emitterEffectMethods;
    case 16: return (const Vt219C*)(g_cameraSpaceEffectMethods);
    case 17: return (const Vt219C*)(g_longStreakEffectMethods);
    case 18: return (const Vt219C*)(g_phasedEffectMethods);
    case 19: return (const Vt219C*)(g_projectileEffectMethods);
    case 20: return (const Vt219C*)(g_hitMarkEffectMethods);
    case 21: return (const Vt219C*)(g_tumblingEffectMethods);
    case 22: return (const Vt219C*)(g_aimedEffectMethods);
    case 23: return (const Vt219C*)(g_streakedEffectMethods);
    case 24: return (const Vt219C*)(g_spinningEffectMethods);
    case 25: return (const Vt219C*)(g_facingEffectMethods);
    case 26: return (const Vt219C*)(g_delayedEffectMethods);
    case 27: return (const Vt219C*)(g_messageEffectMethods);
    default: return 0;
    }
}

Effect* CreateEffect(s32 kind, EffectOwner* sys)
{
    if (sys == 0) {
        sys = AcquireEffectOwner(g_currentWorld, 0);
        if (sys == 0) return 0;
    }
    Effect* o = (Effect*)PopFreeSlot(&sys->world->pool1B2C);
    if (o != 0) {
        FillMemory(o, 0, sys->world->pool1B2C.size);
        const Vt219C* r = GetEffectKindTable(kind);
        o->kind = kind;
        o->owner = sys;
        o->vt = r;
        AppendToList(&sys->list558, o);
        CountEffectUse(o);
    }
    return o;
}

ASM_FUNC(func_0019EB28);

void RemoveEffect(Effect* self)
{
    RemoveFromList(&self->owner->list558, self);
    ReleaseEffect(self);
}

void CountEffectUse(Effect* counter)
{
    counter->uses++;
}

void ReleaseEffect(Effect* self)
{
    s32 n = self->uses - 1;
    self->uses = n;
    if (n != 0) {
        return;
    }
    void (*fn)(Effect*) = self->vt->m02;
    if (fn != 0) {
        fn(self);
    }
    T219CHook* head = self->hooks;
    if (head != 0) {
        self->hooks = 0;
        for (T219CHook* it = head; it != 0; it = it->next) {
            it->fn(it->payload, 0x10, self);
        }
        ReleaseCallRecords(g_currentWorld, head);
    }
    PushFreeSlot(&self->owner->world->pool1B2C, self);
}

void EndEffect(Effect* value, s32 enabled)
{
    if (enabled) RemoveEffect(value);
}

void ShortenEffectLife(Effect* self, f32 x)
{
    f32 span = g_gameClock[1] - self->start;
    f32 t = self->life - span;
    if (x < t) {
        f32 r = t / self->life;
        f32 q = x / r;
        self->life = q;
        self->start = g_gameClock[1] - (1.0f - r) * q;
    }
}

struct AttachedSet;
void GetAttachedSetPointMotion(AttachedSet* self, void* in, Quad16* outA, Quad16* outB);
// The larger of two floats (max.s; through an inline function, b >? a reads a first and gives
// the result b's register).
static inline f32 MaxF(f32 a, f32 b) { return b >? a; }
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist);
void SpawnBriefEffectAt(void* a0, BriefEffectSource* a1, f32 f);

// An effect that hits something (slot 7, the shared contact): against a moving object (class
// flag 0x80) it takes on half the object's motion there; otherwise it bounces as a spinning ball
// of its radius, with a bounce and a friction (kind 24's own, 0.7 and 0.8 for the rest), off the
// object's nearest vertex along the normal when the object is a collider, and is pushed out.
s32 HandleEffectContact(Effect* self, void* b, void* c, void* d)
{
    PlacedObject* other = (PlacedObject*)b;
    Vec02* at = (Vec02*)c;
    Vec02* normal = (Vec02*)d;
    f32 radius;
    f32 bounce;
    f32 friction;
    if (self->kind == 24) {
        radius = self->f120;
        bounce = self->f124;
        friction = self->f128;
    } else {
        bounce = 0.7f;
        radius = ((PlacedObject*)self->p20)->boundRadius;
        friction = 0.8f;
    }
    f32 t = (g_gameTime - self->start) / self->life;
    radius *= ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t);
    if (other->desc->flags & 0x80) {
        Vec02 target;
        GetAttachedSetPointMotion((AttachedSet*)other, at, (Quad16*)&target, 0);
        Vu0::Vec vel = Vu0::MulAddX(Vu0::Vec::Of(self->qA0), Vu0::Sub(Vu0::Vec::Of(target), Vu0::Vec::Of(self->qA0)), Vu0::Vec::ScalarAt(D_0026B544));
        f32 time = D_0026B540;
        Vu0::Q(self->qA0) = vel.q;
        Vu0::Q(self->qC0) = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(target), vel), Vu0::Vec::Scalar(time)).q;
        ShortenEffectLife(self, time);
        SpawnBriefEffectAt(at, (BriefEffectSource*)other, radius * D_0026B548);
        return 1;
    }
    Collider* o = (Collider*)self->p20;
    Vu0::Vec nv = Vu0::Vec::Of(*normal);
    Vu0::Vec p;
    if (o->desc->flags & 2) {
        Vec02 v;
        Vu0::Q(v) = Vu0::RotateTransposed(self->rotation, nv).q;
        Vec02 cur;
        Vec02* end = (Vec02*)o->mesh.verts + o->mesh.vertCount;
        Vec02 best;
        Vu0::Q(best) = Vu0::Q(D_00248D30);
        f32 bestD = 3.4028235e+38f;
        for (Vec02* q = (Vec02*)o->mesh.verts; q < end; q++) {
            Vu0::Q(cur) = Vu0::Q(*q);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(v), Vu0::Vec::Of(cur)));
            if (d < bestD) {
                Vu0::Q(best) = Vu0::Q(cur);
                bestD = d;
            }
        }
        p = Vu0::RotateUntied(self->rotation, Vu0::Vec::Of(best));
    } else {
        p = Vu0::MulX(nv, Vu0::Vec::Scalar(-radius));
    }
    Vu0::Vec d1 = nv;
    Vu0::Vec c1 = Vu0::Cross(p, d1);
    Vec02 vAt;
    ComputeObjectMotionInFrame(other, 0, at, &vAt, 0, 0, 0);
    radius = MaxF(radius, 10.0f);
    Vu0::Vec turn = Vu0::Cross(Vu0::Vec::Of(self->v100), p);
    Vu0::Vec rel = Vu0::Sub(Vu0::Add(Vu0::Vec::Of(self->qA0), turn), Vu0::Vec::Of(vAt));
    Vu0::Vec wv1 = Vu0::MulAddX(d1, Vu0::Cross(c1, p), Vu0::Vec::Scalar(2.5f / (radius * radius)));
    f32 j1 = Vu0::ToFloatMoved(Vu0::Dot(rel, nv)) * (-1.0f - bounce) / Vu0::ToFloatMoved(Vu0::Dot(wv1, nv));
    Vu0::Vec imp1 = Vu0::MulAddX(rel, wv1, Vu0::Vec::Scalar(j1));
    Vu0::Vec tang1 = Vu0::Sub(imp1, Vu0::MulX(nv, Vu0::Dot(imp1, nv)));
    Vu0::Vec mu;
    mu.q = Vu0::Scalar(-friction);
    Vu0::Vec dir = nv;
    dir = Vu0::MulAddX(dir, Vu0::NormalizeOr(tang1, Vu0::Vec::Of(g_unitXVector)), mu);
    Vu0::Vec c2 = Vu0::Cross(p, dir);
    Vu0::Vec wv2 = Vu0::MulAddX(dir, Vu0::Cross(c2, p), Vu0::Vec::Scalar(2.5f / (radius * radius)));
    f32 j2 = Vu0::ToFloatMoved(Vu0::Dot(rel, nv)) * (-1.0f - bounce) / Vu0::ToFloatMoved(Vu0::Dot(wv2, nv));
    Vu0::Vec imp2 = Vu0::MulAddX(rel, wv2, Vu0::Vec::Scalar(j2));
    Vu0::Vec tang2 = Vu0::Sub(imp2, Vu0::MulX(nv, Vu0::Dot(imp2, nv)));
    Vec02 t1;
    Vec02 t2;
    Vu0::Set(t1, tang1.q);
    Vu0::Set(t2, tang2.q);
    f32 along;
    f32 off;
    MeasurePointToSegment((Vec02*)&D_00248D30, &t1, &t2, &along, &off);
    *(Vu0::Vec*)&self->qA0 = Vu0::Add(Vu0::Vec::Of(self->qA0), Vu0::MulXSum(d1, Vu0::Vec::Scalar((1.0f - along) * j1), dir, Vu0::Vec::Scalar(along * j2)));
    *(Vu0::Vec*)&self->v100 = Vu0::MulAddX(Vu0::Vec::Of(self->v100), Vu0::MulXSum(c1, Vu0::Vec::Scalar((1.0f - along) * j1), c2, Vu0::Vec::Scalar(along * j2)), Vu0::Vec::Scalar(2.5f / (radius * radius)));
    if (((Vec02*)&self->qA0)->z < D_0026B54C) {
        ((Vec02*)&self->qA0)->z = D_0026B54C;
        ShortenEffectLife(self, D_0026B550);
    }
    f32 depth = MaxF(0.0f, Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Vec::Of(*at), Vu0::Vec::Of(self->pos)), nv))) + 1.0f;
    Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Vec::Of(self->pos), nv, Vu0::Vec::Scalar(depth)).q;
    return 1;
}

s32 IsSpinNegligible(void* a);
s32 IsVelocityNegligible(void* a);
s32 IsAccelerationNegligible(void* a);
struct SpinRecord_158480;
// The definition takes the time step last; the EE passes it in its own register, and retail's
// caller evaluates it before the matrix, as this order does.
void TurnMatrixBySpin(SpinRecord_158480* self, f32 dt, f32* out);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);

// The four rows func_0019F390 builds a turn in and TurnMatrixBySpin fills.
struct EffectFrame {
    Vec02 r[4];
};

// An effect's spin and motion over dt: the spin dragged and, when it is not negligible, turned
// into a rotation the placement (rot50) is multiplied by; then the velocity carried through the
// spin's frame and the position moved along it.
void MoveEffect(Effect* self, f32 dt)
{
    EffectFrame frame;

    if (IsSpinNegligible(&self->v100) == 0) {
        f32 len;
        Mat02 res;
        Vu0::Q(self->v100) = Vu0::MulX(Vu0::Q(self->v100), Vu0::Scalar(self->spinDrag * dt + 1.0f));
        len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v100)));
        if (0.0001f < len) {
            Vu0::Q(frame.r[0]) = Vu0::MulX(Vu0::Q(self->v100), Vu0::Scalar(1.0f / len));
            BuildAxisAngleMatrix(&frame.r[0], (Mat02*)&frame.r[1], len * dt);
            MulRotationRowsIndexed(&res, *(Mat02*)&frame.r[1], *(Mat02*)self->rotation);
            *(Mat02*)self->rotation = res;
        }
    }
    self->prevPos = self->pos;
    if (IsVelocityNegligible(&self->qA0) == 0 || IsAccelerationNegligible(&self->qC0) == 0) {
        TurnMatrixBySpin((SpinRecord_158480*)((u8*)self + 0xB0), dt, (f32*)&frame);
        u128 nv = Vu0::Transform(frame, Vu0::Q(self->qA0), 1.0f);
        Vu0::Q(self->qA0) = nv;
        Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), nv, Vu0::Scalar(dt));
    }
}

void UpdateEffect(Effect* self, f32 dt)
{
    f32 t = g_gameTime - self->start;
    if (self->life < t) {
        RemoveEffect(self);
        return;
    }
    EffectOwner* c = self->owner;
    if (c->exclusive == 1) {
        return;
    }
    Collider* h = self->target;
    if (h == 0) {
        return;
    }
    if (h->tree.nodes == 0) {
        return;
    }
    s32 flag = 0;
    if (IsObjectAttached(h) != 0) {
        if (FindPlaneTreeNodeForPoint((Vec02*)&self->pos, self->target->tree.nodes) != 0) {
            flag = 1;
        }
    }
    self->vt->m06(self, flag);
}

void BuildScaledTransformMatrix(f32* pos, f32 (*rot)[4], f32* scale, f32 (*out)[4]);
void SubmitScaledPlacedObjectTransform(PlacedObject* self, void* a, Quad16* src);
s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);

// What an effect hands its object's draw method (slot 38): the placement, then the alpha and a
// scale.
struct EffectDraw {
    f32 m[4][4];            // 0x00
    f32 alpha;              // 0x40
    f32 scale;              // 0x44: 1.0
};

s32 DrawEffectAt(Effect* self, Camera* cam, Vec02* pos, f32 (*rot)[4])
{
    PlacedObject* o = (PlacedObject*)self->p20;
    if (o == 0) {
        return 1;
    }
    if (self->life <= 0.0f) {
        return 0;
    }
    f32 t = (g_gameTime - self->start) / self->life;
    f32 a;
    ClampedQuadratic::Get(a, (const QuadraticCoeffs*)&self->q40, t);
    f32 b = ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t);
    f32 radius = o->boundRadius * b;
    f32 fade;
    u128 d = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(cam->position));
    u128 ones = Vu0::Ones();
    if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Scalar(radius)) ^ 0xF0) != 0) {
        return 1;
    }
    if (ComputeCameraDistanceFade(cam, d, &fade, radius, o->fadeDistanceFar) == 0) {
        return 0;
    }
    if (a < 0.0001f && b < 0.0001f) {
        return 1;
    }
    EffectDraw draw;
    Vec02 scale;
    Vu0::Q(scale) = Vu0::Splat(b);
    BuildScaledTransformMatrix(&pos->x, rot, &scale.x, draw.m);
    draw.alpha = a * fade;
    draw.scale = 1.0f;
    o->desc02()->m26(o, cam, &draw);
    f32 keep = o->xyScale;
    if (0.0f < keep) {
        o->xyScale = keep * b;
        SubmitScaledPlacedObjectTransform(o, cam, (Quad16*)&draw);
        o->xyScale = keep;
    }
    return 1;
}

void DrawEffect(Effect* self, void* a1)
{
    u8 scratch[0x40];
    void* a2;
    void* a3;
    if (self->oscillator != 0) {
        ComputeOscillatorDisplacement((Oscillator*)self->oscillator, 50.0f, (Vec02*)&self->pos, (Vec02*)self->rotation, (Vec02*)scratch, (Vec02*)(scratch + 0x10), 0);
        a2 = scratch;
        a3 = scratch + 0x10;
    } else {
        a2 = &self->pos;
        a3 = self->rotation;
    }
    s32 r = DrawEffectAt(self, (Camera*)a1, (Vec02*)a2, (f32 (*)[4])a3);
    if (r == 0) {
        RemoveEffect(self);
    }
}

void AddEffectListener(void* obj, void* arg)
{
    const Desc01* desc = ((BaseObject*)arg)->desc;
    AddCallbackNode(g_currentWorld, (Callback01**)((u8*)obj + 0x118), (void*)desc->m0D, arg);
}

void AddEffectCallback(void* obj, void* a1, void* a2)
{
    AddCallbackNode(g_currentWorld, (Callback01**)((u8*)obj + 0x118), a1, a2);
}

void RemoveEffectCallback(void* obj, void* a1, void* a2)
{
    RemoveCallbackNode(g_currentWorld, (Callback01**)((u8*)obj + 0x118), a1, a2);
}

void InitFallingEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    self->life = 5.0f;
    World* g = g_currentWorld;
    self->i20 = (s32)g->slot1CE8[1];
    self->qC0 = *(Quad219C*)&g->gravity;
}

void EndEffectWithImpact(Effect* self, s32 flag)
{
    if (flag != 0) {
        ColliderSpan s[16];
        *(Quad219C*)&s[0].q[0] = self->pos;
        if (self->target->tree.nodes != 0) {
            CollectTreeNodeSpans(self->target->tree.nodes, (Vec02*)&self->prevPos, (Vec02*)&self->pos, 0, 0x10, s);
        }
        Effect* p = CreateEffect(4, 0);
        if (p != 0) {
            p->vt->m00(p, s, 40.0f, 0);
            p->life = 0.75f;
            p->m30[1] = 30.0f;
            if (self->target->f278 != 0) {
                p->oscillator = (void*)((s32*)self->target->f278)[3];
            }
        }
        RemoveEffect(self);
    }
}

void InitRisingEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    Vec02 k;
    InitFallingEffect(self, pos, scale, flags);
    self->m30[0] = 0.33f;
    Vu0::Q(k) = Vu0::FromFloat(-0.2f);
    Vu0::Q(self->vC0) = Vu0::MulX(Vu0::Q(g_currentWorld->gravity), Vu0::Q(k));
    self->fB0 = -8.0f;
}

void MoveEffect(Effect* self, f32 dt);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void ComputeSinCos(f32 angle, f32* sinOut, f32* cosOut);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
void MoveDriftingEffect(Effect* self, f32 dt)
{
    MoveEffect(self, dt);
    f32 r = RandomFloatInRange(0.0f, 1.0f);
    s32 drift = 0;
    s32 still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->qA0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->qA0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->qA0))) < 0.0001f) {
        still = 1;
    }
    if (!still && r < 0.3f) {
        drift = 1;
    }
    if (drift) {
        Vec02 dir;
        Vec02 side[2];
        Vec02 push;
        f32 s;
        f32 c;
        Vu0::Q(dir) = Vu0::Q(self->qA0);
        Vu0::Q(dir) = Vu0::DivX(Vu0::Q(dir), Vu0::Length(Vu0::Q(dir)));
        BuildPerpendicularPair(&dir, side, &g_unitXVector, &g_unitZVector);
        f32 speed = RandomFloatInRange(100.0f, (1.0f - r * 3.3333333f) * 300.0f + 100.0f);
        ComputeSinCos(RandomFloatInRange(0.0f, 6.2831855f), &s, &c);
        Vu0::Q(push) = Vu0::MulXSum(Vu0::Q(side[0]), Vu0::Scalar(s * speed), Vu0::Q(side[1]), Vu0::Scalar(c * speed));
        Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(push), Vu0::Scalar(dt));
    }
}

void EndEffectWithImpactOnExit(Effect* value, u32 enabled)
{
    EndEffectWithImpact(value, enabled < 1);
}

void InitEffect(Effect* self, void* pos, f32 scale, s32 flags);

void InitImpactEffect(Effect* self, void* pos, f32 limit, s32 flags)
{
    InitEffect(self, pos, limit, flags);
    f32 c = 200.0f;
    f32 v = c <? limit;
    self->i20 = (s32)g_currentWorld->slot1CE8[2];
    self->m30[0] = v;
    self->m30[1] = v * 0.6f;
}

void InitGrowingEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    self->life = 3.0f;
    World* g = g_currentWorld;
    s32 v = (s32)g->slot1CE8[3];
    self->m30[1] = 0.6f;
    self->i20 = v;
}

void InitShrinkingFallEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    self->life = 2.0f;
    World* g = g_currentWorld;
    self->qC0 = *(Quad219C*)&g->gravity;
    self->m30[2] = -1.0f;
}

void InitDroppingEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    World* g = g_currentWorld;
    s32 v = (s32)g->slot1CE8[6];
    self->life = 0.5f;
    self->i20 = v;
}

void UpdateDroppingEffect(Effect* self, f32 dt)
{
    Vec02 k;
    while (self->target != 0 && IsObjectAttached(self->target) == 0) {
        self->target = (Collider*)self->target->parent;
    }
    if (g_gameClock[1] - self->start > 0.15f) {
        Vu0::Q(k) = Vu0::FromFloat(0.5f);
        self->fB0 = -8.0f;
        Vu0::Q(self->vC0) = Vu0::MulX(Vu0::Q(g_currentWorld->gravity), Vu0::Q(k));
    }
    UpdateEffect(self, dt);
}

void DrawBeamBetweenPoints(PlacedObject* self, PlacedObject* b, Vec02* p, Vec02* q, f32 sx, f32 sy);

void DrawDroppingEffect(Effect* self, void* a1)
{
    DrawEffect(self, a1);
    u128 d = Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(self->prevPos));
    if (100.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
        f32 t = (g_gameTime - self->start) / self->life;
        f32 x;
        ClampedQuadratic::Get(x, (const QuadraticCoeffs*)&self->q40, t);
        DrawBeamBetweenPoints((PlacedObject*)g_currentWorld->slot1CE8[7], (PlacedObject*)a1, (Vec02*)&self->prevPos, (Vec02*)&self->pos, 0.1f, x);
    }
}

void EndDroppingEffect(Effect* self, void* other)
{
    if (other != 0) {
        RemoveEffect(self);
    }
}

void InitStreakEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    self->life = 0.25f;
    s32 v = (s32)g_currentWorld->slot1CE8[4];
    self->i20 = v;
    self->q40 = D_00275C50;
    self->f120 = 0.05f;
}

void DrawStreakEffect(Effect* self, void* a1)
{
    Vec02 pos;
    f32 t = g_gameTime - self->start;
    f32 m = self->f120;
    if (t < m) {
        m = t;
    }
    Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->qA0), Vu0::Scalar(-m));
    f32 p = t / self->life;
    f32 x;
    ClampedQuadratic::Get(x, (const QuadraticCoeffs*)&self->q40, p);
    f32 y = ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, p);
    if (x <= 0.0f || y <= 0.0f) {
        RemoveEffect(self);
    } else {
        DrawBeamBetweenPoints((PlacedObject*)self->p20, (PlacedObject*)a1, &pos, (Vec02*)&self->pos, y, x);
    }
}

void InitScaledEffect(Effect* self, void* pos, f32 f, s32 flags)
{
    InitEffect(self, pos, f, flags);
    self->life = 0.5f;
    s32 v = (s32)g_currentWorld->slot1CE8[5];
    u8* p = (u8*)&D_0026B560;
    self->i20 = v;
    Quadword128 t;
    StoreFloatAsQuadword((u128*)&t, f);
    Quad219C* sub = &self->q30;
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword((u128*)&u, p);
    StoreQuadword((u128*)sub, ScaleQuadword(tv, u));
}

void InitTrailSegment(Effect* self, void* pos, f32 f, s32 flags)
{
    InitEffect(self, pos, f, flags);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B580;
    s32 v = (s32)g_currentWorld->slot1CE8[7];
    self->fB0 = -15.0f;
    self->i20 = v;
    self->q40 = *(Quad219C*)D_0026B570;
    self->life = 0.35f;
    Quadword128 t;
    StoreFloatAsQuadword((u128*)&t, f);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword((u128*)&u, p);
    StoreQuadword((u128*)sub, ScaleQuadword(tv, u));
}

void DetachTrailSegment(Effect* self)
{
    SetTrailSegmentAnchor(self, 0, 0);
}

void OnTrailAnchorEnded(void* self, s32 kind, void* extra);

void SetTrailSegmentAnchor(void* selfv, s32 kind, void* extra)
{
    Effect* self = (Effect*)selfv;
    if (self->i120 == kind) {
        return;
    }
    switch (self->i120) {
    case 1:
        RemoveEffectCallback(self->p124, (void*)OnTrailAnchorEnded, self);
        if (kind == 0) {
            Vu0::Q(self->prevPos) = Vu0::Q(self->p124->pos);
        }
        self->i120 = kind;
        break;
    case 2: {
        BaseObject* anchor = (BaseObject*)self->p128;
        ((void (*)(BaseObject*, void*, void*))((s32*)anchor->desc)[0x78 / 4])(anchor, (void*)OnTrailAnchorEnded, self);
        if (kind == 0) {
            if (extra != 0) {
                Vu0::Q(self->prevPos) = Vu0::Q(*(Quad219C*)extra);
            } else {
                Vu0::Q(self->prevPos) = Vu0::Q(((PlacedObject*)self->p128)->v140);
            }
        }
        self->i120 = kind;
        break;
    }
    default:
        self->i120 = kind;
        break;
    }
    switch (kind) {
    case 1: {
        Effect* other = (Effect*)extra;
        Vu0::Q(self->pos) = Vu0::Q(other->pos);
        Vu0::Q(self->qA0) = Vu0::Q(other->qA0);
        self->p124 = other;
        AddEffectCallback(other, (void*)OnTrailAnchorEnded, self);
        break;
    }
    case 2: {
        PlacedObject* other = (PlacedObject*)extra;
        Vu0::Q(self->pos) = Vu0::Q(other->v140);
        Vu0::Q(self->qA0) = Vu0::Q(other->v150);
        self->p128 = (Effect*)other;
        ((void (*)(BaseObject*, void*, void*))((s32*)other->desc)[0x74 / 4])(other, (void*)OnTrailAnchorEnded, self);
        break;
    }
    case 0:
        Vu0::Q(self->qA0) = Vu0::Zero();
        break;
    }
}

void SplitTrailSegment(Effect* self)
{
    Effect* d = CreateEffect(10, 0);
    if (d != 0) {
        d->vt->m00(d, &self->pos, 0.0f, 0);
        d->i20 = self->i20;
        d->fB0 = self->fB0;
        d->q40 = self->q40;
        d->life = self->life;
        Effect* p;
        if (self->i120 == 1) {
            p = self->p124;
            f32* m = p->m30;
            f32 q = (self->start - p->start) / p->life;
            f32 den = p->m30[0] + q * (m[1] + q * m[2]);
            f32 res = self->m30[0] / den;
            q = (g_gameTime - p->start) / p->life;
            res = res * (p->m30[0] + q * (m[1] + q * m[2]));
            d->m30[0] = res;
            d->m30[1] = -res;
        } else {
            d->q30 = self->q30;
            p = self->p128;
        }
        SetTrailSegmentAnchor(d, self->i120, p);
        SetTrailSegmentAnchor(self, 3, d);
    } else {
        SetTrailSegmentAnchor(self, 0, 0);
    }
}

// One step of a trail segment: its velocity damped by fB0 and pulled by vC0 over dt, its two
// ends moved by it. Then the anchor's (kind 1: another segment's, kind 2: a placed object's)
// speed and distance decide whether it lets go or splits.
void MoveTrailSegment(Effect* self, f32 dt)
{
    Vu0::Q(self->qA0) = Vu0::MulXSum(Vu0::Q(self->qA0), Vu0::Scalar(self->fB0 * dt + 1.0f), Vu0::Q(self->qC0), Vu0::Scalar(dt));
    Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->qA0), Vu0::Scalar(dt));
    Vec02* vel;
    Vec02* pos;
    switch (self->i120) {
    case 0:
        Vu0::Q(self->prevPos) = Vu0::MulAddX(Vu0::Q(self->prevPos), Vu0::Q(self->qA0), Vu0::Scalar(dt));
        return;
    case 1:
        pos = (Vec02*)&self->p124->pos;
        vel = (Vec02*)&self->p124->qA0;
        break;
    case 2: {
        PlacedObject* o = (PlacedObject*)self->p128;
        if (o->flags & ((u64)0x8000 << 20)) {
            SetTrailSegmentAnchor(self, 0, 0);
            return;
        }
        pos = &o->v140;
        vel = &o->v150;
        break;
    }
    default:
        return;
    }
    if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(*vel), Vu0::Q(*vel))) < 40000.0f) {
        SetTrailSegmentAnchor(self, 0, 0);
        return;
    }
    u128 d = Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(*pos));
    if (625.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
        SplitTrailSegment(self);
    }
}

s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);

void DrawTrailSegment(Effect* self, Camera* cam)
{
    Vec02 r;
    f32 fade;
    PlacedObject* o = (PlacedObject*)self->p20;
    if (o == 0) {
        RemoveEffect(self);
        return;
    }
    f32 radius = o->boundRadius;
    s32 in = 0;
    u128 d = Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(cam->position));
    u128 ones = Vu0::Ones();
    Vu0::Q(r) = Vu0::FromFloat(radius);
    if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Q(r)) ^ 0xF0) == 0) {
        in = ComputeCameraDistanceFade(cam, d, &fade, radius, o->fadeDistanceFar) != 0;
    }
    if (in == 0) {
        return;
    }
    f32 t = (g_gameTime - self->start) / self->life;
    f32 a;
    ClampedQuadratic::Get(a, (const QuadraticCoeffs*)&self->q40, t);
    f32 b = ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t);
    if (0.0001f < a && 0.0001f < b) {
        void* to;
        switch (self->i120) {
        case 1:
        case 3:
            to = (u8*)self->p124 + 0x80;
            break;
        case 2:
            to = (u8*)self->p128 + 0x140;
            break;
        case 0:
            to = &self->prevPos;
            break;
        }
        DrawBeamBetweenPoints((PlacedObject*)self->p20, (PlacedObject*)cam, (Vec02*)&self->pos, (Vec02*)to, b * 100.0f, a * fade);
        return;
    }
    RemoveEffect(self);
}

void OnTrailAnchorEnded(void* self, s32 kind, void* extra)
{
    if (kind == 3) {
        goto three;
    }
    if (kind < 4) {
        if (kind == 2) {
            goto zero;
        }
        return;
    }
    if (kind == 10) {
        goto zero;
    }
    if (kind != 16) {
        return;
    }
zero:
    SetTrailSegmentAnchor(self, 0, 0);
    return;
three:
    SetTrailSegmentAnchor(self, 0, (u8*)extra + 16);
}

void InitSpawningEffect(Effect* self, void* pos, f32 f, s32 flags)
{
    InitEffect(self, pos, f, flags);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B590;
    s32 v = (s32)g_currentWorld->slot1CE8[8];
    self->life = 0.25f;
    self->i20 = v;
    Quadword128 t;
    StoreFloatAsQuadword((u128*)&t, f);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword((u128*)&u, p);
    (void)StoreQuadword((u128*)sub, ScaleQuadword(tv, u));
    u8* q = (u8*)D_0026B5A0;
    self->q40 = *(Quad219C*)q;
}

void SpawnFollowUpEffect(Effect* self, f32 arg)
{
    UpdateEffect(self, arg);
    f32 d = g_gameTime - self->start;
    d = d - 0.15f;
    if (0.0f <= d && d < arg) {
        arg = -self->m30[2];
        Effect* n = CreateEffect(12, 0);
        if (n != 0) {
            n->vt->m00(n, &self->pos, arg, 0);
        }
    }
}

void InitFollowUpEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    World* sys = g_currentWorld;
    self->i20 = (s32)sys->slot1CE8[9];
    self->life = 3.0f;
    self->q40 = *(Quad219C*)D_0026B5B0;
    self->m30[1] = self->m30[0] * 0.25f;
    self->qC0 = *(Quad219C*)D_0026B5C0;
    self->fB0 = -1.0f;
}

void InitWideTrailSegment(Effect* self, void* pos, f32 f, s32 flags)
{
    InitTrailSegment(self, pos, f, flags);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B5E0;
    s32 v = (s32)g_currentWorld->slot1CE8[10];
    self->fB0 = -15.0f;
    self->i20 = v;
    self->q40 = *(Quad219C*)D_0026B5D0;
    Quadword128 t;
    StoreFloatAsQuadword((u128*)&t, f);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword((u128*)&u, p);
    StoreQuadword((u128*)sub, ScaleQuadword(tv, u));
}

void InitShortFallingEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    World* g = g_currentWorld;
    s32 v = (s32)g->slot1CE8[1];
    self->life = 0.5f;
    self->i20 = v;
    self->qC0 = *(Quad219C*)&g->gravity;
}

void InitEffect(Effect* self, void* pos, f32 scale, s32 flags);
void ProjectPointToCamera(Camera* camera, Vec02* in, f32* out);

void InitCameraSpaceEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    const T219C_Params* p = self->params;
    ProjectPointToCamera(g_camera, (Vec02*)pos, &self->f120);
    f32 x = RandomFloatInRange(p->rows[8], p->rows[12]);
    f32 y = RandomFloatInRange(p->rows[9], p->rows[13]);
    f32 z = RandomFloatInRange(p->rows[10], p->rows[14]);
    self->life = D_0026B5F0[0];
    Vu0::Q(self->qA0) = Vu0::FromFloats(x, y, z);
    self->q40 = D_00275C50;
    self->q30 = *(const Quad219C*)&p->rows[20];
}

void EvaluateHermiteVectorSegment(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 t, f32 k, Vec02* pos, Vec02* vel, Vec02* acc);
void UnprojectCameraPoint(Camera* camera, f32* a, Vec02* out);

void MoveCameraSpaceEffect(Effect* self, f32 f)
{
    Quad219C a;
    Quad219C b;
    f32 t = self->start + self->life - g_gameTime;
    t = t >? f;
    EvaluateHermiteVectorSegment(t, (const Vec02*)&self->f120, (const Vec02*)&self->qA0, (const Vec02*)self->params, (const Vec02*)(self->params->rows + 4), f, 1.0f, (Vec02*)&a, (Vec02*)&b, 0);
    *(Quad219C*)&self->f120 = a;
    self->qA0 = b;
    UnprojectCameraPoint(g_camera, (f32*)&a, (Vec02*)&self->pos);
}


void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);

// Draws the effect at its point seen from the camera, turned by the part of the camera's turn the
// effect's age gives (twice its age times pi about the axis of its parameters, +0x40).
void DrawCameraSpaceEffect(Effect* self, Camera* cam)
{
    Vec02 point;
    Mat02 view;
    Mat02 a;
    Mat02 b;
    Mat02 out;
    Vec02 axis;
    f32 angle;
    f32 t;
    Mat02 r2;
    Mat02 r1;
    Mat02* c = (Mat02*)self->rotation;

    UnprojectCameraPoint(cam, &self->f120, &point);
    MultiplyMatrices3x3(c, (Mat02*)&cam->g80, &view);
    MatrixToAxisAngle(&view, &angle, &axis);
    t = (g_gameTime - self->start) / self->life;
    BuildAxisAngleMatrix(&axis, &a, angle * t);
    BuildAxisAngleMatrix((Vec02*)((u8*)self->params + 0x40), &b, (t + t) * 3.14159274f);
    MulRotationRowsInto(&r1, a, b);
    MulRotationRowsIntoIndexed(&r2, r1, *c);
    out = r2;
    DrawEffectAt(self, cam, &point, (f32 (*)[4])&out);
}

void RunEffectEndCallback(Effect* self)
{
    if (self->life < g_gameTime - self->start) {
        RemoveEffect(self);
        self->params->fn60(self->p134);
    }
}

void InitEmitterEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    self->q40 = D_00275C50;
    self->life = 2.0f;
}

LINKER_REMNANT(func_001A1028);

static inline f32 ClampRange(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

// The emitter's two targets are quadratics of its age (include/shapes.h's Quadratic16, each a
// brace initialiser: the compiler clears the local and stores the non-zero coefficients, and
// the CLOBBER of the first one's union orders the frame stores as retail has them).
void MoveEmitterEffect(Effect* self, f32 dt)
{
    Vec02 d1, d2, vel, pa, pb;
    Quadratic16 a = { 125.0f, -25.0f, 0.0f };
    Quadratic16 b = { 20.0f, 20.0f, 0.0f };
    f32 t = (g_gameTime - self->start) / self->life;
    f32 u = ClampRange(t, 0.0f, 1.0f);
    Vu0::Q(pa) = Vu0::FromFloats(a.x + u * (a.y + u * a.z), 0.0f, 0.0f);
    Vu0::Q(pb) = Vu0::FromFloats(0.0f, b.x + u * (b.y + u * b.z), 0.0f);
    Vu0::Q(d1) = Vu0::Sub(Vu0::Q(pa), Vu0::Q(self->pos));
    Vu0::Q(d2) = Vu0::Sub(Vu0::Q(pb), Vu0::Q(self->qA0));
    Vu0::Q(d2) = Vu0::MulXSum(Vu0::Q(d1), Vu0::Scalar(25.0f), Vu0::Q(d2), Vu0::Scalar(10.0f));
    Vu0::Q(self->qA0) = Vu0::MulAddX(Vu0::Q(self->qA0), Vu0::Q(d2), Vu0::Scalar(dt));
    Vu0::Q(vel) = Vu0::Q(self->qA0);
    vel.y = 0.0f;
    Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(vel), Vu0::Scalar(dt));
}

void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);

void UpdateEmitterEffect(Effect* self, f32 dt)
{
    Mat02 axisRot;
    Mat02 m;
    BuildAxisAngleMatrix(&g_unitZVector, &axisRot, *(f32*)((u8*)self + 0xA4) * dt);
    MulRotationRowsIndexed(&m, axisRot, *(Mat02*)self->rotation);
    s32 fire = 0;
    Vec02* cam = (Vec02*)&g_camera->g80;
    if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->rotation[0]), Vu0::Q(*cam))) &&
        Vu0::ToFloat(Vu0::Dot(Vu0::Q(m.r[0]), Vu0::Q(*cam))) <= 0.0f && 0.5f < g_gameTime - self->start) {
        fire = 1;
    }
    if (fire) {
        Vec02 pos;
        u128 r = Vu0::Rotate(m, Vu0::Q(self->pos));
        Vu0::Set(pos, r);
        Vu0::Set(pos, Vu0::Add(r, Vu0::Q(((PlacedObject*)self->p120)->v140)));
        Effect* e = CreateEffect(0x10, 0);
        if (e != 0) {
            e->vt->m00(e, &pos, 1.0f, 0);
            e->life = 0.25f;
        }
        if (--self->i124 <= 0) {
            RemoveEffect(self);
            return;
        }
    }
    self->rotation[0] = m.r[0];
    self->rotation[1] = m.r[1];
    self->rotation[2] = m.r[2];
}


void DrawEmitterEffect(Effect* self, void* a1)
{
    Vec02 pos;
    Mat02 rot;
    Vu0::Q(pos) = Vu0::Rotate(self->rotation, Vu0::Q(self->pos));
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(((PlacedObject*)self->p120)->v140));
    rot = g_identityMatrix;
    DrawEffectAt(self, (Camera*)a1, &pos, (f32 (*)[4])&rot);
}

void InitLongStreakEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitStreakEffect(self, pos, scale, flags);
    World* ctx = g_currentWorld;
    s32 v = ctx->f1D28;
    self->f120 = 0.15f;
    self->i20 = v;
}

void InitPhasedEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    s32 v = g_currentWorld->f1D28;
    self->i120 = -1;
    self->i20 = v;
    self->i128 = -1;
}

void KeepPhasedEffectStill(Effect* self)
{
}

void AdvanceEffectPhases(Effect* c, f32 dt)
{
    f32 t = (g_gameTime - c->start) / c->life;
    f32 k;
    switch (c->i120) {
    case 0: k = D_0026B600[0] + t * (D_0026B600[1] + t * D_0026B600[2]); break;
    case 1: k = D_0026B610[0]; break;
    case 2: k = D_0026B610[0] + t * (D_0026B610[1] + t * D_0026B610[2]); break;
    }
    f32 p = c->f124 + k * dt;
    c->f124 = p;
    if (1.0f <= p) c->f124 = p - 1.0f;
    if (1.0f < t) {
        switch (c->i120) {
        case 0: SetEffectPhase(c, 1); break;
        case 1: SetEffectPhase(c, 2); break;
        case 2: RemoveEffect(c); break;
        }
    }
}

// A point of a phased effect's strip, as the effect's source writes them (+0x130): where the
// piece starts, the point whose x and y head to the next one and whose z is its width, then
// what DrawPhasedEffect works out for it.
struct PhasedEffectPoint {
    Vec02 base;             // 0x00
    Vec02 at;               // 0x10
    f32 heading;            // 0x20: the angle to the next point, 0 to 2 pi
    f32 length;             // 0x24: the distance to the next point in x and y
    f32 turn;               // 0x28: the turn to the next point's heading, over its width
    s32 id;                 // 0x2C
};

// Slot 5 of the kind-18 table: works out each point's heading, length and turn, then draws the
// strip piece by piece along it, from the point the effect has reached (+0x124). Each piece's
// operands are formed in the order retail loads and stores them: the first loop's weights and
// ends as locals, each weight before its end, and both loops' scale after the position
// (docs/TOOLCHAIN.md, "A weighted sum's operands in insn order").
void DrawPhasedEffect(Effect* self, Camera* cam)
{
    PhasedEffectPoint pts[64];
    EffectDraw draw;
    Vec02 v;
    Mat02 m;
    Mat02 rot;
    Vec02 scale;
    f32 one = 1.0f;
    f32 x = (g_gameTime - self->start) / self->life;
    f32 t;
    if (x < 0.0f) {
        t = 0.0f;
    } else if (one < x) {
        t = one;
    } else {
        t = x;
    }
    f32 size;
    switch (self->i120) {
    case 0:
        size = D_0026B620[0] + t * (D_0026B620[1] + t * D_0026B620[2]);
        break;
    case 1:
        size = D_0026B630[0];
        break;
    case 2:
        size = D_0026B630[0] + t * (D_0026B630[1] + t * D_0026B630[2]);
        break;
    }
    f32 total = 0.0f;
    s32 i;
    s32 cur;
    PhasedEffectPoint* p;
    s32 n = self->points(self->p134, 0x3F, pts);
    pts[n] = pts[0];
    f32 scaleMin = 3.402823466e+38f;
    draw.scale = 1.0f;
    draw.alpha = 0.0f;
    for (i = 0; i < n; i++) {
        p = &pts[i];
        Vu0::Q(v) = Vu0::Sub(Vu0::Q(pts[i + 1].at), Vu0::Q(p->at));
        f32 h = ArctangentOfRatio(v.y, v.x) + 3.14159274f;
        p->heading = h;
        f32 w = cam->nearDistance >? p->at.z;
        f32 a;
        f32 b;
        f32 c;
        ClampedQuadratic::Get(a, (const QuadraticCoeffs*)&self->q40, t);
        ClampedQuadratic::Clamp(b, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B660, w), (const ValueRange*)D_0026B670);
        draw.alpha = a * b >? draw.alpha;
        f32 s = ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t);
        ClampedQuadratic::Clamp(c, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B640, w), (const ValueRange*)D_0026B650);
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(v), Vu0::Q(v))));
        scaleMin = s * c <? scaleMin;
        p->length = len;
        total += len;
    }
    pts[n] = pts[0];
    for (i = 0; i < n; i++) {
        p = &pts[i];
        f32 dh = p[1].heading - p->heading;
        if (dh <= 0.0f) {
            dh += 6.28318548f;
        }
        f32 turn = dh * D_0026B630[0] / p[1].at.z;
        p->turn = turn;
        total += turn;
    }
    pts[n] = pts[0];
    if (self->i128 < 0) {
        f32 c;
        ClampedQuadratic::Clamp(c, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B680, total), (const ValueRange*)D_0026B690);
        self->i128 = (s32)c;
        cur = n;
    } else {
        for (cur = 0; cur < n; cur++) {
            if (pts[cur].id == self->i12C) {
                break;
            }
        }
    }
    if (!(cur < n)) {
        self->i12C = pts[0].id;
        cur = 0;
    }
    f32 pos = self->f124 * total / (f32)self->i128;
    i = 0;
    while (i < n) {
        s32 nextI = i + 1;
        s32 next = cur + 1;
        p = &pts[cur];
        f32 step = 0.0f;
        f32 rest = pos - p->length;
        if (rest < step) {
            do {
                t = (pos + step) / (pos - rest);
                BuildAxisAngleMatrix(&g_unitXVector, &m, p->heading);
                f32 k = size * scaleMin;
                MulRotationRowsX(&rot, cam->rot3A0, m);
                Vu0::Vec w0 = Vu0::Vec::Scalar(1.0f - t);
                u128 a = Vu0::Q(p->base);
                Vu0::Vec w1 = Vu0::Vec::Scalar(t);
                u128 b = Vu0::Q(p[1].base);
                Vu0::Q(v) = Vu0::MulXSum3(a, w0.q, b, w1.q, Vu0::Q(rot.r[2]), Vu0::Scalar(k));
                Vu0::Q(scale) = Vu0::Splat(scaleMin);
                BuildScaledTransformMatrix(&v.x, (f32 (*)[4])&rot, &scale.x, draw.m);
                PlacedObject* o = (PlacedObject*)self->p20;
                o->desc02()->m26(o, cam, &draw);
                step += total / (f32)self->i128;
            } while (rest + step < 0.0f);
        }
        pos = rest + step;
        step = 0.0f;
        rest = pos - p->turn;
        if (rest < step) {
            do {
                t = (pos + step) / (pos - rest);
                f32 dh = p[1].heading - p->heading;
                if (dh <= 0.0f) {
                    dh += 6.28318548f;
                }
                BuildAxisAngleMatrix(&g_unitXVector, &m, p->heading + t * dh);
                f32 k = size * scaleMin;
                MulRotationRowsX(&rot, cam->rot3A0, m);
                Vu0::Q(v) = Vu0::MulAddX(Vu0::Vec::Of(p[1].base), Vu0::Vec::Of(rot.r[2]), Vu0::Vec::Scalar(k)).q;
                Vu0::Q(scale) = Vu0::Splat(scaleMin);
                BuildScaledTransformMatrix(&v.x, (f32 (*)[4])&rot, &scale.x, draw.m);
                PlacedObject* o = (PlacedObject*)self->p20;
                o->desc02()->m26(o, cam, &draw);
                step += total / (f32)self->i128;
            } while (rest + step < 0.0f);
        }
        cur = next % n;
        i = nextI;
        pos = rest + step;
    }
}

void SetEffectPhase(Effect* self, s32 mode)
{
    f32 t;
    f32 x;

    if (mode == self->i120) {
        return;
    }
    f32 one = 1.0f;
    x = (g_gameClock[1] - self->start) / self->life;
    if (x < 0.0f) {
        t = 0.0f;
    } else if (one < x) {
        t = one;
    } else {
        t = x;
    }
    switch (mode) {
    case 0:
        self->q40 = *(Quad219C*)D_0026B6A0;
        self->life = 0.25f;
        break;
    case 1:
        self->q40 = *(Quad219C*)((u8*)&D_00275C50);
        self->life = 3.4028235e+38f;
        break;
    case 2:
        self->q40 = *(Quad219C*)D_0026B6B0;
        self->life = 0.5f;
        break;
    }
    if ((mode == 0 || mode == 2) && (self->i120 == 0 || self->i120 == 2)) {
        t = 1.0f - t;
    } else {
        t = 0.0f;
    }
    self->start = g_gameClock[1] - t * self->life;
    self->i120 = mode;
}

s32 CompareByFloatKeyAscending(AngledPoint* a, AngledPoint* b)
{
    if (a->angle < b->angle) return -1;
    return 1;
}

// A point of ComputeProjectedHull: where it is, where it projects (x and y over z), and its
// angle about the lowest one (0x30 bytes).
struct HullPoint {
    Vec02 world;            // 0x00
    Vec02 screen;           // 0x10
    f32 angle;              // 0x20
    u8 pad24[0x30 - 0x24];
};

void InitIdentityMatrix(Mat4* self);
Mat4A MultiplyMatrices(void* m, void* in);
void BuildBasisFromX(Vec02* x, Mat02* out);
s32 ComputeProjectedHull(void* m, s32 n, HullPoint* pts);

// The frame looking from the camera toward pos: the camera's position moved to the origin, then
// the basis built from the direction (its rows as the columns), and the product passed to
// ComputeProjectedHull, returned by value as a temporary.
s32 ComputeHullSeenFromCamera(Vec02* pos, s32 n, HullPoint* pts)
{
    Mat4 m0;
    Mat4 m1;
    Vec02 v;
    Mat02 rot;
    Mat4A t;
    InitIdentityMatrix(&m0);
    InitIdentityMatrix(&m1);
    m0.m[3][0] = -((f32*)g_camera)[16];
    m0.m[3][1] = -((f32*)g_camera)[17];
    m0.m[3][2] = -((f32*)g_camera)[18];
    Vu0::Q(v) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(g_camera->position));
    BuildBasisFromX(&v, &rot);
    m1.m[0][0] = -rot.r[1].x;
    m1.m[1][0] = -rot.r[1].y;
    m1.m[2][0] = -rot.r[1].z;
    m1.m[0][1] = rot.r[2].x;
    m1.m[1][1] = rot.r[2].y;
    m1.m[2][1] = rot.r[2].z;
    m1.m[0][2] = rot.r[0].x;
    m1.m[1][2] = rot.r[0].y;
    m1.m[2][2] = rot.r[0].z;
    t = MultiplyMatrices(&m1, &m0);
    return ComputeProjectedHull(&t, n, pts);
}

void TransformByMatrixWithW(const Quad16* m, const Vec02* v, f32 w, Vec02* out);
void SortElements(void* base, u32 n, u32 size, s32 (*compare)(const void* x, const void* y));

s32 ComputeProjectedHull(void* m, s32 n, HullPoint* pts)
{
    HullPoint tmp;
    f32 lowest = 3.40282347e+38f;
    s32 low = -1;
    s32 i;
    HullPoint* p;
    for (i = 0; i < n; i++) {
        p = &pts[i];
        TransformByMatrixWithW((const Quad16*)m, &p->world, 1.0f, &p->screen);
        f32 z = p->screen.z;
        p->screen.y /= z;
        p->screen.x /= z;
        if (p->screen.y < lowest) {
            lowest = p->screen.y;
            low = i;
        }
    }
    tmp = pts[0];
    pts[0] = pts[low];
    pts[low] = tmp;
    for (i = 1; i < n; i++) {
        p = &pts[i];
        Vu0::Q(tmp.world) = Vu0::Sub(Vu0::Q(p->screen), Vu0::Q(pts[0].screen));
        p->angle = ArctangentOfRatio(tmp.world.y, tmp.world.x);
    }
    SortElements(&pts[1], n - 1, 0x30, (s32 (*)(const void*, const void*))CompareByFloatKeyAscending);
    HullPoint* out = pts;
    for (i = 0; i < n; i++) {
        p = &pts[i];
        while (out >= &pts[2]) {
            u128 side = Vu0::Cross(Vu0::Sub(Vu0::Q(out[-1].screen), Vu0::Q(out[-2].screen)), Vu0::Q(g_unitZVector));
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(p->screen), Vu0::Q(out[-2].screen)), side)) < 0.0f) {
                break;
            }
            out--;
        }
        *out = *p;
        out++;
    }
    return out - pts;
}

void CopyEffectSourceIds(Effect* self, Rec50* src)
{
    self->p120 = src->found[1];
    self->i124 = src->f1F0;
}

void DrawProjectileEffect(Effect* self, void* a1)
{
    Vec02 dir;
    Mat02 rot;
    Vec02 k;
    u128 d;
    Vec02* p = &dir;
    if (self->i124 != 0) {
        u128 g = Vu0::Q(g_camera->g80);
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        d = Vu0::MulX(g, Vu0::Q(k));
    } else {
        d = Vu0::Q(g_unitZVector);
    }
    Vu0::Q(*p) = d;
    BuildBasisFromXAndZHint((const Vec02*)&self->qA0, &dir, &rot);
    DrawEffectAt(self, (Camera*)a1, (Vec02*)&self->pos, (f32 (*)[4])&rot);
}

void BuildEulerRotationMatrix(f32* in, f32* out);
void BuildShortestArcRotation(const Vec02* from, const Vec02* to, Mat02* out);

void AttachHitMarkEffect(Effect* self, s32 target, void* other, Vec02* point, Vec02* normal, Effect** out)
{
    Effect* e = 0;
    if (target != 0) {
        e = CreateEffect(0x14, 0);
        if (e != 0) {
            Vec02 local;
            Mat02 basis;
            Vec02 angles;
            Mat02 turn;
            TransformPointBetweenFrames(0, (PlacedObject*)other, point, &local);
            f32 zero = 0.0f;
            f32 t = (g_gameTime - self->start) / self->life;
            f32* m = self->m30;
            f32 size = self->m30[0] + t * (m[1] + t * m[2]);
            size *= RandomFloatInRange(0.8f, 1.4f);
            e->vt->m00(e, &local, size, 0);
            e->i20 = target;
            e->life = 5.0f;
            e->m30[2] = -size;
            e->p120 = other;
            basis.r[2] = *normal;
            BuildPerpendicularPair(normal, basis.r, &g_unitXVector, &g_unitZVector);
            angles.y = zero;
            angles.x = zero;
            angles.z = RandomFloatInRange(zero, 6.2831855f);
            BuildEulerRotationMatrix((f32*)&angles, (f32*)&turn);
            {
                Mat02 r;
                Vec02 x;
                Vec02 y;
                Vec02 z;
                Vu0::Q(x) = Vu0::RotateUntied(basis, Vu0::Q(turn.r[0]));
                r.r[0] = x;
                Vu0::Q(y) = Vu0::RotateUntied(basis, Vu0::Q(turn.r[1]));
                r.r[1] = y;
                Vu0::Q(z) = Vu0::RotateUntied(basis, Vu0::Q(turn.r[2]));
                r.r[2] = z;
                e->rotation[0] = r.r[0];
                e->rotation[1] = r.r[1];
                e->rotation[2] = r.r[2];
            }
            if (__builtin_fabsf(normal->z) < 0.7f) {
                Vec02 up = *normal;
                Mat02 arc;
                up.z = zero;
                BuildShortestArcRotation(&up, normal, &arc);
                Vu0::Q(e->qA0) = Vu0::Rotate(arc, Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-50.0f)));
            }
        }
    }
    if (out != 0) {
        *out = e;
    }
}

s32 HandleEffectImpact(Effect* self, PlacedObject* other, void* a2, void* a3)
{
    u32 i;
    for (i = 0; i < 4; i++) {
        if (IsObjectOfKind(other->root, D_0026B6C0[i]) != 0) {
            return 0;
        }
    }
    if (IsObjectOfKind(other, 0x1F) == 0) {
        AttachHitMarkEffect(self, self->i120, other, (Vec02*)a2, (Vec02*)a3, 0);
    }
    RemoveEffect(self);
    return 1;
}

void UpdateEffectUntilDetached(Effect* self, f32 dt)
{
    UpdateEffect(self, dt);
    BaseObject* h = (BaseObject*)self->p120;
    if (h != 0) {
        if (IsObjectAttached(h) == 0) {
            RemoveEffect(self);
        }
    }
}

void DrawHitMarkEffect(Effect* self, void* a1)
{
    u8 scratch[0x40];

    TransformPointBetweenFrames((PlacedObject*)self->p120, 0, (Vec02*)&self->pos, (Vec02*)scratch);
    TransformRotationBetweenFrames((PlacedObject*)self->p120, 0, (Mat02*)self->rotation, (Mat02*)(scratch + 0x10));
    DrawEffectAt(self, (Camera*)a1, (Vec02*)scratch, (f32 (*)[4])(scratch + 0x10));
}

void BuildBasisFromX(Vec02* x, Mat02* out);

void SetRandomEffectSpin(Effect* self)
{
    Quad16 axis;
    f32 x = RandomFloatInRange(-1.0f, 1.0f);
    f32 y = RandomFloatInRange(-1.0f, 1.0f);
    f32 z = RandomFloatInRange(0.1f, 0.9f) + 0.1f;
    Vu0::Q(axis) = Vu0::FromFloats(x, y, z);
    BuildBasisFromX((Vec02*)&axis, (Mat02*)self->rotation);
}

f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);

// A quadratic in z (poly[0] + poly[1] z + poly[2] z^2), clamped to range[0]..range[1]; the same
// inline as player_state2.cpp's.
static inline f32 EvalClampedQuadratic(const f32* poly, const f32* range, f32 z)
{
    f32 v = poly[0] + z * (poly[1] + z * poly[2]);
    f32 lo = range[0];
    f32 hi = range[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    return v;
}

// Turns an effect by angle about the second row of rot (its placement): the turn built into the
// caller's matrix, then the velocity and the placement's rows rotated by it, rot's rows read by
// index through the parameter and the result stored through the effect. The parameter is a
// pseudo of the inline's own, without the pointer flag a declared pointer gets, set before the
// call; its row loads may alias the frame's stores, so each waits for the row before
// (docs/TOOLCHAIN.md, "An inline's pointer parameter and frame stores").
static inline void TurnEffectAboutRow(Effect* o, const Mat02& rot, Mat02* turn, f32 angle)
{
    BuildAxisAngleMatrix(&rot.r[1], turn, angle);
    const u128* p = (const u128*)turn;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vu0::Q(o->qA0) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(o->qA0));
    const u128* q = (const u128*)&rot;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
    *(Mat02*)o->rotation = r;
}

// v made unit length in place, or set to fallback when shorter than 0.0001; returns the length.
static inline f32 NormalizeInPlace(Vec02* v, const Vec02& fallback)
{
    Vu0::Vec t = Vu0::Vec::Of(*v);
    Vu0::Vec l = Vu0::Length(t);
    if (Vu0::ToFloat(l) < 0.0001f) {
        *v = fallback;
    } else {
        Vu0::Q(*v) = Vu0::DivX(t, l).q;
    }
    return Vu0::ToFloatMoved(l);
}

// A tumbling effect's motion over dt: the placement turned about its own second row at a rate
// from the velocity along its first (D_0026B6D0, clamped to D_0026B6E0), the velocity's part
// along the motion scaled by D_0026B6E8 towards the speed D_0026B6EC and the rest by the drag at
// +0xB0, which is cleared for MoveEffect and put back after. One float scratch holds the spin
// and then the speed: one pseudo with two deaths, which global-alloc places above the block's
// locals in both places ($f4).
void MoveTumblingEffect(Effect* self, f32 dt)
{
    f32 t = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->qA0), Vu0::Q(self->rotation[0])));
    f32 w = EvalClampedQuadratic(D_0026B6D0, D_0026B6E0, t);
    Mat02 turn;
    TurnEffectAboutRow(self, *(Mat02*)self->rotation, &turn, w * dt);
    f32 drag = self->fB0;
    self->iB0 = 0;
    Vec02 along;
    Vec02 across;
    SplitVectorAlongAxis((Vec02*)&self->qA0, self->rotation, &along, &across);
    t = NormalizeInPlace(&along, g_unitXVector);
    Vu0::Q(self->qA0) =
        Vu0::MulXSum(Vu0::Vec::Of(along), Vu0::Vec::Scalar(D_0026B6EC + (D_0026B6E8 * dt + 1.0f) * (t - D_0026B6EC)),
                     Vu0::Vec::Of(across), Vu0::Vec::Scalar(drag * dt + 1.0f)).q;
    MoveEffect(self, dt);
    self->fB0 = drag;
}


s32 HandleTumblingEffectImpact(Effect* self, void* a1, void* a2, void* a3)
{
    PlacedObject* other = (PlacedObject*)a1;
    u8 out[0x10];
    void* p;

    if (IsObjectOfKind(other->root, 0x40) != 0) {
        return 0;
    }
    if (IsObjectOfKind(other->root, 6) != 0) {
        return 0;
    }
    AttachHitMarkEffect(self, self->i20, other, (Vec02*)a2, (Vec02*)a3, (Effect**)out);
    p = *(void**)out;
    if (p != 0) {
        TransformRotationBetweenFrames(0, other, (Mat02*)((u8*)p + 0x50), (Mat02*)((u8*)p + 0x50));
    }
    RemoveEffect(self);
    return 1;
}

s32 IsEffectAimCandidate(Rec50* self, Collider* other)
{
    u64 flag = 0x8000;

    flag <<= 28;
    if ((other->flags538 & flag) != 0) {
        return 0;
    }
    return other != self->target;
}

typedef int Quadword128 __attribute__((mode(TI)));
void *StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(u128* out, u128 v);
s32 IsEffectAimCandidate(Rec50* self, Collider* other);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
Collider* FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);
void BuildBasisFromX(Vec02* x, Mat02* out);
extern const Vec02 g_unitZVector;

void AimEffectAtNearestObject(Effect* self, Rec50* src)
{
    f32* poly = (f32*)((u8*)src + 0x1C0);
    f32 speed = self->m30[0];
    f32 peak = poly[0];
    f32 a = peak;
    f32 b = poly[1];
    f32 c = poly[2];
    peak = (a + b + c) >? peak;
    if (0.0001f < __builtin_fabsf(c)) {
        f32 t = -b / (c + c);
        peak = (a + t * (b + t * c)) >? peak;
    }
    Vec02 end;
    ColliderSpan span;
    s32 n;
    Collider** list;
    Quadword128 tq;
    Quadword128 uq;
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->qA0)));
    f32 reach = speed * peak;
    Vec02* from = (Vec02*)&self->pos;
    Vu0::Q(self->qA0) = Vu0::NormalizeOr(Vu0::Q(self->qA0), Vu0::Q(g_unitZVector));
    Vu0::Q(end) = Vu0::MulAddX(Vu0::Q(*from), Vu0::Q(self->qA0), Vu0::Scalar(reach * 100.0f));
    PushBackMemoryMark();
    GatherCollidersInBox(g_currentWorld, 0, from, &end, (s32 (*)(void*, Collider*))IsEffectAimCandidate, src, &n, &list);
    if (FindNearestSpanObject(1, from, &end, n, list, &span) != 0) {
        speed = speed * span.time[0];
    }
    PopBackMemoryMark();
    StoreFloatAsQuadword((u128*)&tq, speed);
    Quadword128 tv = tq;
    CopyQuadword((u128*)&uq, poly);
    StoreQuadword((u128*)&self->q30, ScaleQuadword(tv, uq));
    BuildBasisFromX((Vec02*)&self->qA0, (Mat02*)self->rotation);
    Vu0::Q(self->qA0) = Vu0::Zero();
}

void PlaceEffectAtSource(Effect* dst, void* a1)
{
    Rec50* src = (Rec50*)a1;
    TransformPointBetweenFrames((PlacedObject*)src->target, 0, (Vec02*)((u8*)src + 0x20), (Vec02*)&dst->pos);
    dst->iB0 = 0;
    dst->i110 = 0;
    dst->i120 = src->i1F4;
    dst->i124 = src->f1F0;
}

// The streak from the place along the velocity's direction, 100 long, drawn with the world's
// template slot 11, or DrawEffectAt in the velocity's frame. The template is read first, before
// the stores of dir and tail: a load through the world pointer would wait for them (docs/TOOLCHAIN.md,
// "A pointer read before the frame stores").
void DrawStreakedEffect(Effect* self, void* a1)
{
    if (self->i20 == 0) {
        BaseObject* tmpl = g_currentWorld->slot1CE8[11];
        Vec02 dir;
        Vec02 tail;
        u128 v = Vu0::Q(self->qA0);
        Vu0::Q(dir) = v;
        Vu0::Q(dir) = Vu0::DivX(v, Vu0::Length(v));
        Vu0::Q(tail) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(dir), Vu0::Scalar(100.0f));
        DrawBeamBetweenPoints((PlacedObject*)tmpl, (PlacedObject*)a1, &tail, (Vec02*)&self->pos, 10.0f, 1.0f);
    } else {
        Mat02 rot;
        BuildBasisFromXAndYHint((Vec02*)&self->qA0, (Vec02*)((u8*)a1 + 0x80), &rot);
        DrawEffectAt(self, (Camera*)a1, (Vec02*)&self->pos, (f32 (*)[4])&rot);
    }
}

s32 FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);

s32 HandleStreakedEffectImpact(Effect* self, void* hold, Vec02* where, Vec02* dir)
{
    if (self->i124 != 0) {
        NodeQuery q;
        FillMemory(&q, 0, 0x40);
        q.pos = *where;
        q.dir = *(Vec02*)&self->qA0;
        q.hold = hold;
        q.p00 = self->owner;
        q.kind = 0x10;
        if (FindNodeForQuery(&q, 0, 0) != 0) {
            goto remove;
        }
    }
    if (self->i120 != 0) {
        Mat02 basis;
        Vec02 v;
        *(Vec02*)&self->pos = *where;
        BuildBasisFromX(dir, &basis);
        Vu0::Q(v) = Vu0::RotateTransposed(basis, Vu0::Q(self->qA0));
        v.x *= RandomFloatInRange(-0.95f, -0.85f);
        v.y += RandomFloatInRange(-400.0f, 400.0f);
        v.z += RandomFloatInRange(-400.0f, 400.0f);
        Vu0::Q(self->qA0) = Vu0::Rotate(basis, Vu0::Q(v));
        return 1;
    }
remove:
    RemoveEffect(self);
    return 1;
}

void RandomizeEffectSpin(Effect* self, Rec50* src)
{
    self->life *= RandomFloatInRange(D_0026B6F0[0], D_0026B6F0[1]);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->qA0)));
    f32 t;
    self->f120 = *(f32*)((u8*)src + 0x1F0);
    self->f124 = *(f32*)((u8*)src + 0x1F4);
    self->f128 = *(f32*)((u8*)src + 0x1F8);
    ClampedQuadratic::Get(t, (const QuadraticCoeffs*)D_0026B700, len);
    f32 s = t * 10.0f;
    f32* p = (f32*)((u8*)self + 0x100);
    for (s32 i = 2; i >= 0; i--) {
        *p++ = RandomFloatInRange(-s, s);
    }
}

s32 HandleEffectContactUnlessKind6(Effect* a0, PlacedObject* a1, void* a2, void* a3)
{
    if (IsObjectOfKind(a1->root, 6) != 0) {
        return 0;
    }
    return HandleEffectContact(a0, a1, a2, a3);
}

// A spinning effect drawn at its centre moved along D_00248D20 by its weight f120.
void DrawSpinningEffect(Effect* self, void* a1)
{
    Vec02 pos;
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloatAt(self->f120);
    Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(g_unitZVector), Vu0::Q(k));
    DrawEffectAt(self, (Camera*)a1, &pos, (f32 (*)[4])self->rotation);
}

void InitFacingEffect(Effect* self, void* pos, f32 scale, s32 flags)
{
    InitEffect(self, pos, scale, flags);
    f32 half = 0.5f;
    u8* sys = (u8*)g_currentWorld;
    self->life = half;
    self->i20 = *(s32*)(sys + 0x1D30);
    self->q40 = *(Quad219C*)D_0026B710;
    self->q30 = *(Quad219C*)D_0026B720;
}

// Draws a facing effect: an object turned to the camera, scaled and faded by the distance and
// by the effect's age.
void DrawFacingEffect(Effect* self, Camera* cam)
{
    Vec02 pos;
    Vec02 dir;
    Vec02 scale;
    Mat02 axis;
    Mat02 basis;
    Mat02 rot;
    EffectDraw draw;
    PlacedObject* o = (PlacedObject*)self->p20;
    if (o != 0) {
        TransformPointBetweenFrames((PlacedObject*)self->p120, 0, (Vec02*)&self->pos, &pos);
        u128 r = Vu0::ScalarAt(o->boundRadius);
        u128 ones = Vu0::Ones();
        u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(cam->position));
        if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, r) ^ 0xF0) != 0) {
            RemoveEffect(self);
            return;
        }
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(pos));
        BuildBasisFromXAndZHint(&dir, (const Vec02*)&g_unitZVector, &basis);
        f32 t = (g_gameTime - self->start) / self->life;
        f32 k = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(dir))) * 0.001f;
        f32 s = ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t);
        f32 near;
        ClampedQuadratic::Clamp(near, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B740, k), (const ValueRange*)D_0026B750);
        Vu0::Q(scale) = Vu0::Splat(s * near);
        f32 a;
        ClampedQuadratic::Get(a, (const QuadraticCoeffs*)&self->q40, t);
        f32 fade;
        ClampedQuadratic::Clamp(fade, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B760, k), (const ValueRange*)D_0026B770);
        draw.alpha = a * fade;
        draw.scale = 1.0f;
        BuildAxisAngleMatrix(&g_unitXVector, &axis, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B730, t));
        MulRotationRowsX(&rot, basis, axis);
        BuildScaledTransformMatrix(&pos.x, (f32(*)[4])&rot, &scale.x, draw.m);
        ((PlacedObject*)self->p20)->desc02()->m26((PlacedObject*)self->p20, cam, &draw);
    }
}

void InitDelayedEffect(Effect* self, void* pos, f32 x, s32 flags)
{
    InitEffect(self, pos, x, flags);
    self->q40 = *(Quad219C*)&D_00275C50;
    self->m30[0] = x;
    self->m30[1] = 1.0f - x;
    *(s32*)&self->m30[2] = 0;
}

void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);

// Takes the source object's pose (+0x134) and lets it go: the effect starts there and moves
// over its life to where its target object (+0x20) will be then, turning by the rotation
// between the two frames.
void TakeDelayedEffectSourcePose(Effect* self)
{
    Vec02 pos;
    Mat02 rot;
    Mat02 turn;
    PlacedObject* src = (PlacedObject*)self->p134;
    *(Vec02*)&self->pos = src->v140;
    self->rotation[0] = src->m110.r[0];
    self->rotation[1] = src->m110.r[1];
    self->rotation[2] = src->m110.r[2];
    ComputeObjectFrameAtTime((PlacedObject*)self->p20, 0, &pos, &rot, 0, 0, self->life);
    Vu0::Q(self->qA0) = Vu0::MulXSum(Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos)), Vu0::Scalar(1.0f / self->life),
                                     Vu0::Q(self->qC0), Vu0::Scalar(self->life * -0.5f));
    MultiplyMatrices3x3(&rot, (Mat02*)self->rotation, &turn);
    MatrixToAxisAngle(&turn, &self->f130, (Vec02*)&self->f120);
    if (0.0f < self->f130) {
        self->f130 = self->f130 + 6.28318548f;
    } else {
        self->f130 = self->f130 - 6.28318548f;
    }
    ((BaseObject*)self->p134)->desc->m03((BaseObject*)self->p134);
    self->p134 = 0;
}

// The product a b with MulRotationRowsX's locals, its rows stored to out as quadwords.
static inline void MulRows(Vec02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    Vu0::Q(out[0]) = Vu0::Q(r.r[0]);
    Vu0::Q(out[1]) = Vu0::Q(r.r[1]);
    Vu0::Q(out[2]) = Vu0::Q(r.r[2]);
}

// An effect homing on its object's frame at the end of its life (once started): its position
// and velocity steered there through func_00130540 over the time left, and its placement the
// object's rotation then, turned about f120 by f130 times the share of its life left.
void MoveDelayedEffect(Effect* self, f32 f)
{
    Vec02 pos;
    Vec02 v10;
    Vec02 v20;
    Vec02 v30;
    Mat02 rot;
    Mat02 turn;
    f32 t;

    if (!(g_gameClock[1] < self->start)) {
        self->prevPos = self->pos;
        t = self->start + self->life - g_gameClock[1];
        t = f >? t;
        ComputeObjectFrameAtTime((PlacedObject*)self->p20, 0, &pos, &rot, 0, 0, t);
        u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos));
        u128 w1 = Vu0::Scalar(1.5f / t);
        u128 w2 = Vu0::Scalar(-0.5f);
        u128 w3 = Vu0::Scalar(0.25f);
        u128 c = Vu0::MulX(Vu0::Q(self->qC0), Vu0::Scalar(t));
        Vu0::Q(v10) = Vu0::MulXSum3(d, w1, Vu0::Q(self->qA0), w2, c, w3);
        EvaluateHermiteVectorSegment(t, (const Vec02*)&self->pos, (const Vec02*)&self->qA0, &pos, &v10, f, 1.0f, &v20, &v30, 0);
        BuildAxisAngleMatrix((Vec02*)&self->f120, &turn, self->f130 * t / self->life);
        self->pos = *(Quad219C*)&v20;
        self->qA0 = *(Quad219C*)&v30;
        MulRows(self->rotation, turn, rot);
    }
}

void UpdateDelayedEffect(Effect* self)
{
    if (self->start <= g_gameClock[1]) {
        if (self->i134 != 0) {
            TakeDelayedEffectSourcePose(self);
        }
    }
    f32 span = g_gameClock[1] - self->start;
    if (self->life < span) {
        BaseObject* o = (BaseObject*)self->p20;
        o->desc->m02(o);
        RemoveEffect(self);
    }
}

void DrawDelayedEffect(Effect* self, void* a1)
{
    if (g_gameTime < self->start) {
        return;
    }
    DrawEffect(self, a1);
}

void ResolveEffectTarget(Effect* self, void* otherv)
{
    Rec50* other = (Rec50*)otherv;
    self->p120 = FindFirstObjectById(g_currentWorld, 0x104, other->f1F0, other->target);
    self->f124 = other->f1F4;
}

void SendEffectMessagesAtRate(Effect* self, f32 scale)
{
    UpdateEffect(self, scale);
    if (self->p120 == 0) return;
    f32 t = scale * self->f124;
    f32 v = self->f128 + t;
    self->f128 = v;
    if (!(1.0f <= v)) return;
    f32 nv;
    do {
        SlotMessage buf;
        buf.kind = 4;
        buf.qb = *(Quad16*)&self->pos;
        BaseObject* obj = (BaseObject*)self->p120;
        obj->desc->m1B(obj, &buf);
        nv = self->f128 - 1.0f;
        self->f128 = nv;
    } while (1.0f <= nv);
}

LINKER_REMNANT(func_001A3AC8);

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))
#define O(o, off) (*(PairController**)((u8*)(o) + (off)))

#undef F
#undef W
#undef P
#undef O

void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
extern const Vec02 g_unitZVector;

#define F(o) (*(f32*)((u8*)self + (o)))
#define I(o) (*(s32*)((u8*)self + (o)))
#define P(o) ((const QuadraticCoeffs*)((u8*)self + (o)))

#undef F
#undef I
#undef P
