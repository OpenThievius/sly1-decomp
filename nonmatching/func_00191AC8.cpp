// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 416/428, checked 2026-11-13
// w44-fa (2026-11-12), 5 compiles, from the dumps: (2) is a real insn, not reload's or caller-save's. vf4's caller-save slot is 320 (pc around CopyBytes) and vf4 holds p before the third call, so nothing saves k there; the exit is a label with two predecessors, so no reload is inherited. Retail's first loop block ends with `K4 = k` (k unallocated, hence `lqc2 vf4,304(sp)`, reorg takes it into the beqz slot) and the exit uses K4 (sqc2 vf4,192; vdiv vf4). k then has 12 refs (its set 2, the rows 6, k2 2, the copy 2) over 3 calls: not worth a caller save (4 * 3 >= 12), as the body needs. (1) is the temporary of a 64-to-128-bit conversion: with the mfc1's output a u64 and `k.q = (u128)kg`, expand makes a no-conflict block (`(set (subreg:DI T 0) kg)`, `(set (subreg:DI T 1) 0)`, `(set T T)` with REG_EQUAL zero_extend), T takes v0 (`move v0,s6`) and `k = T` stores it when k has no register; loop.c does not move it. Compiled: with that alone k gets vf6 with a caller save (its refs rise above 12: the exit's uses count on top), whose restore at the block's end is retail's beqz-slot load in shape (save slot 320 or 336, not 304). Ruled out: PRE (a Vec02 k in memory, written at the loop's top: one load in the body, the exit's load stays at the exit; the conversion written again at the exit is not made redundant, gcse does not take a libcall's REG_EQUAL as an expression: `por v0,zero,s1` at the exit), haifa's interblock motion (every region is one block), a Vec02 in memory read back into k after the first call (k crosses two calls and gets vf6 with a caller save). Open: the source of a copy of k after TestOwnerGraphSpan that gcse's copy propagation does not fold into the exit's uses (a plain `kz = k` is folded: the copy is available at the exit). The rewrite sweep's hint (a narrower `i`, 1.0f as a local in the body: 104 to 88 words) is not followed here: retail's loop has `addiu s1,s1,1; sltiu v0,s1,11` with no extension, so the index is 32 bits wide.
// w32-sizeA (2026-11-11): not retried; the first differing block is the loop's head (retail's per-iteration move v0,s6; sq v0,304 and the extra saved register s8), as in (1) above.
// DECLS (2026-11-11, w28-nmdecls): TransformPointBetweenFrames now void (defined void): neutral, 92/107. TestOwnerGraphSpan stays s32: the C uses its result (it does not compile as void) although file_18F988's definition is void.
// w23-vuE (2026-11-11): the retail form of the scale found: 416 bytes of 428, frame 512 as retail's (86% by regdiff, 92 of 107
// instructions). The scale is a u128 GPR value kg = ScalarInGprReg(scale), made once before the loop (mfc1 in a saved GPR across
// the three calls), and the per-iteration `k.q = kg;` copies it into the Vec k, which global-alloc leaves in memory (spill
// slot 304): the rows load it from 304, the k2 copy is lq 304/sq 240, the vector after the loop is reloaded from the same slot.
// The earlier forms made k itself the mfc1 output, which loop.c moves out of the loop with its set. What still differs:
// (1) retail's per-iteration copy is `move v0,s6; sq v0,304(sp)` (a 64-bit move: a partial set of the TImode pseudo, so one
// insn more in the lives), ours stores `sq s4,304(sp)` directly; that extra insn lengthens the lives of dir (4 refs, 56 insns)
// and i (7 refs, 98): both have priority 1428 (log2(refs)*refs*10000/life, exactly tied) and the tie goes to the lower number
// (dir), retail's order is i first (s1=i, s2=dir); the same shift puts retail's &p (s4) and &hit (s5) before kg (s6), ours kg
// before them (kg s4, &hit s5, &p s6). (2) retail loads k into vf4 in the beqz's delay slot after TestOwnerGraphSpan (the post-loop
// use kept in a register across the exit test), ours after the loop. A u64 asm output with `k.q = (u128)kg` gives the `move
// v0,s6` but makes k a VU0 register with 23 refs (the partial sets), `*(u64*)&k.q = *(u64*)&kg` the same.
// NEAR (2026-11-10, w16-191AC8): 81.3% by regdiff (was 80.4%), 412 bytes against 428: the four missing insns are exactly retail's mfc1 s6, the in-loop move v0,s6 and s8's save and restore (see (1)); everything else in the loop now matches. The scale is a Vu0::Vec value k (not a Vec02 in memory): global-alloc leaves it unallocated (10 refs, 3 calls crossed: 4*3 >= 10, so no caller save) and reload gives it the spill slot at 304, so the rows load it as retail does (vf2 for row 0, vf4 inherited for rows 1 and 2), the copy to k2 goes through a GPR (lq v0,304; sq v0,240) and the pos copy as a Vec value is spilled to 320 across CopyBytes, all as retail. Still differs: (1) loop.c moves k's set out of the loop (the mfc1 output is k itself after CSE; an invariant set once), where retail keeps the mfc1 in a saved GPR (s6, one saved register more: frame 512 against our 496) and per iteration copies it (move v0,s6; sq v0,304): retail's in-loop set is not invariant to loop.c (a partial set, or a second set in the loop); (2) retail loads k into vf4 right after TestOwnerGraphSpan (beqz's delay slot, before the branch: not reorg's, vf4 is live into the exit) and after the loop stores it to 192 (a temporary in rot's slot) and divides by vf4; ours reloads it at the vdiv. No source tried makes a value set after the call that lives to the exit: a separate `kz = k` after the call (loop.c moves it with k), a fresh Vec::ScalarInGpr(scale) for the divide (not CSE'd across the loop: mfc1 again), Vec::ScalarInGpr(scale) per iteration (the slot at 304 stays in the loop but k is hoisted to 320: frame 528), a FloatQuad union {f32; u128} set from scale (in memory, not a register: swc1 then lq), `= { scale }` (the same), a cast to the union (does not compile), Q((s128)k.q) for the divisor (no temporary), u128 k (identical to the Vec).
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "box_collider.h"
#include "object_link.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "point_graph_object.h"
#include "world.h"
#include "step_sequence.h"
#include "screen_element.h"
#include "globals.h"
#include "pad_record.h"
#include "effect.h"
#include "vu0.h"
void InitCollider(void* self);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void InitAgent(void* self);
void StartAgent(void* self);
void ResolveObjectLinks(void* self, s32 n, void* table);
s32 ResolveAgentClip(void* self, s32 id);
void RemoveItemKeeperMember(void* a, void* b);
void EnterAgentState(void* self, s32 a, s32 b);
s32 IsObjectAttached();
s32 FindSwitchedColliderIndex(SwitchedCollider* value);
s32 FindSwitchedColliderIndex(void* value);
void ActivateSwitchedColliderIndex(s32 index);
void* MoveMemory(void* dst, void* src, s32 size);
void RegisterCollider(void* self);
void AddToSwitchedColliderList(void* self);
void UnregisterCollider(void* self);
void RemoveFromSwitchedColliderList(void* self);
void AddToSwitchedColliderList(SwitchedCollider* self);
void RemoveFromSwitchedColliderList(SwitchedCollider* self);
void* GetActiveSwitchedCollider();
struct InteractFlags {
    s32 a;
    s32 b;
};
s32 IsObjectInPool(void* p, s32 v);
s32 AcceptAgentRequest(void* self, s32* arg);
void StartObject(void* self);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void TransformPointBetweenFrames(void* a0, s32 a1, void* a2, void* a3);
typedef void (*ChildFn)(void* self);
struct SeekPartner {
    ChildFn* vtbl;
    u8 pad04[0x618 - 0x04];
    void* p618;
};
void LeaveAgentState(void* self);
extern s32 g_buttonCodeFlags;
s32 IsPadSelectFlagHeld(void* p);
s32 IsAgentRequestBlocked(void* self, s32 a);
void* CreateEffect(s32 kind, s32 zero);
void AddEffectListener(void* node, void* owner);
f32 GetAnimationMarkerTime(void* obj, s32 id);
typedef void (*ActivationHook)(void* self, s32 mode, void* other);
extern u8 g_elementStack[];
void PushStackElement(void* a, void* b);
extern s32 g_padRouting;
extern u8* D_0026F800;
s32 IsTopCameraController(void* p);
void SkipRemainingSteps(StepSequence* ctx, PadRecord* rec);
void SetStepSequenceState(void* p, s32 n);
void ClearPadPressedBits(PadRecord* rec, s32 n);
s32 IsObjectAttached(void* p);
s32 IsObjectOfKind(void* a, s32 b);
void ReparentObject(void* self, s32 value);
void ReadBufferedString(void* other, void* sub);
void InitCollider(void* self);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value);
extern void ChangeAgentState(SeekingAgent* self, s32 mode, s32 value);
struct SourceNotice { s32 f_0; u8 pad4[4]; s32 f_8; };
extern void HandleAgentNotification(SeekingAgent* self, s32 code, SourceNotice* req);
extern void SpendReserveUnit(void);
void CopyCollider(SwitchedCollider* self);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 mode);
void PushCameraController(void* mgr, s32 a1, void* a2, SwitchedCollider* self, s32 a4);
void RemoveCameraControllers(void* mgr, s32 a1, s32 a2, s32 a3, SwitchedCollider* self, s32 a5);
void* GetActiveSwitchedCollider(void);
void ActivateSwitchedCollider(void* value);
struct GraphQuery { u8 data[4]; };
struct GraphQueryOwner { u8 head[0x34]; GraphQuery part; };
s32 FindPointGraphPath(GraphQuery* part);
void SnapPointToPointGraph(GraphQuery* part);
void ReadBufferedVector3(void* a, void* b);
void ReadPropertyRecords(void* a, void* b);
void TransformPointBetweenFrames(void* a, s32 b, void* c, s32 d);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
extern u8 D_0026A210[];
void SetupScreenElementText(void* self);
s32 IsFontLoaded(s32 k);
void* GetFontById(s32 k);
struct Obj_191AA8 {
    u8 pad0[0x54];
    void* p54;
};
s32 CollectSegmentSpansInPlaneTree(void* p);
void SyncDataCache(s32 a);
void CopyObjectData(void* self);
void SetListLinkOffset(void* self, s32 value);
void ClearList(void* p);
void RegisterObject(void* self);
void AppendToList(void* table, void* self);
void UnregisterObject(void* self);
void RemoveFromList(void* table, void* self);
extern s32 g_menuChoiceLabels[];
s32 IsPadSelectFlagHeld(void* p);
void CaptureColliderPose(void);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, Quad16* p, s32 zero);
struct AgentEvent { s32 id; };
struct EventNotice {
    SeekingAgent* self;
    s32 id;
};
s32 HasSpareCount(void* a, void* b);
s32 HandleAgentObjectEvent(void* a, void* b);
extern s32 g_buttonCodeFlags;
extern u8* g_saveData;
struct EffectSpawnParams { s32 f0, f4, f8, fC; f32 f10, f14; s32 f18, f1C; f32 f20, f24; s32 f28, f2C, f30, f34, f38, f3C; };
void RotateMatrixUpright(void* sub, s32 zero, void* out);
s32 CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, s32 d, f32 fa, f32 fb);
void SpawnEffectsAt(void* a, void* b, s32 c, void* d, void* e, s32 f, s32 g);
void LoadObjectProperties(BaseObject* o, Stream8A* in);
s32 ReadBufferedU16(Stream8A* in);
void* AllocateZeroedFrontMemory(s32 n);
void ReadBufferedVector3(Stream8A* in, void* p);
s32 ReadBufferedU8(Stream8A* in);
void* AllocateFrontMemory(s32 n);
f32 ReadBufferedFloat(Stream8A* in);
s32 ReadBufferedS16(Stream8A* in);
void MeasurePointGraphEdges(PointGraph* m);
void* GetActiveSwitchedCollider(void);
void InitObject(BaseObject* self);
void HandlePlacedObjectNotification(SwitchedCollider* self, s32 kind, void* msg);
void StopSoundRecord(void* self, s32 n);
extern f32 D_0026A700;
extern f32 D_0026A704;
extern f32 D_0026A708;
extern f32 D_0026A70C;
void StopStreamVoice(void);
void PushBackMemoryMark(void);
s32* AllocateBackMemory(s32 bytes);
void CopyMemory(void* dst, void* src, s32 bytes);
void PopBackMemoryMark(void);
s32 IsPointPathShortcutBlocked(void* self, s32 a, s32 b);
s32 GetEntryName(s32 v);
void UpdateAgentGoal(SeekingAgent* self);
void SetAgentGoalPoint(SeekingAgent* self, void* p);
s32 IsObjectAttached(void* p);
s32 GetObjectWorldPosition(void* self, s32* arg);
s32 CollectSegmentSpansInPlaneTree(void* a, s32 b, s32 c, s32 d, ColliderSpan* e);
typedef void (*SlotFn)(void* self);
extern u8* g_saveData;
void UpdateCollider(SwitchedCollider* self);
void EmitSwitchedColliderTrailPoints(SwitchedCollider* self);
struct ClampInt {
    static s32 Of(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) return lo;
        if (hi < v) return hi;
        return v;
    }
};
f32 TruncateFloat(f32 x);
void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other);
s32 ConstructSwitchedColliderDefaults(s32 a, s32 b);
f32 D_00269B50[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
ObjectLink D_00269B60[2] = { { 0x20, 0x167, 0x59C }, { 0x20, 0x168, 0x5A0 } };
f32 D_00269B78[11] = { 0.0f, 0.5f, -0.5f, 1.0f, -1.0f, 1.5f, -1.5f, 2.0f, -2.0f, 2.5f, -2.5f };
s32 g_screenOwner = 0;
List_269BA8 g_targetVectors = { 0 };
f32 D_00269BC0[3] = { 1000.0f, 10.0f, 1.0f };
s32 g_activeSwitchedCollider = -1;
EffectSpawnParams D_00269BD0 = { 0x18, -1, 0, 0, 1.0f, 2.0f, 0, 0, 1.0f, 2.0f, 0, 0, 0, 1, 0, 0 };
static Blk05 D_00604700;
Blk05 D_00269C10;
s32 g_switchedColliderCount;
void* g_switchedColliders[16];
struct PlaneNode {
    Vec02 normal;           
    f32 offset;             
    s32 below;              
    s32 above;              
};

s32 TestOwnerGraphSpan(Obj_191AA8* self, Vec02* pos, Vec02* point, s32 count, ColliderSpan* out);
void* CopyBytes(void* dst, void* src, s32 n);
void BuildAxisAngleMatrix(const Vec02* axis, f32 angle, Mat02* out);

// A matrix copied whole: the call's arguments are its parameters, substituted as constants.
static inline void CopyMatrix(Mat02* d, const Mat02* s) { CopyBytes(d, (void*)s, 0x30); }

void FitStepToPointGraph(Obj_191AA8* self, f32 scale, Vec02* pos, Vec02* dir)
{
    Mat02 m;
    Vec02 p;
    Vec02 hit;
    ColliderSpan span;
    Mat02 rot;
    Vec02 k2;
    Mat02 s;
    Vu0::Vec k;
    u128 kg = Vu0::ScalarInGprReg(scale);
    f32 best = -1.0f;
    u32 i = 0;
    do {
        k.q = kg;
        BuildAxisAngleMatrix(&g_unitZVector, D_00269B78[i], &m);
        *(Vu0::Vec*)&s.r[0] = Vu0::MulX(Vu0::Vec::Of(m.r[0]), k);
        *(Vu0::Vec*)&s.r[1] = Vu0::MulX(Vu0::Vec::Of(m.r[1]), k);
        *(Vu0::Vec*)&s.r[2] = Vu0::MulX(Vu0::Vec::Of(m.r[2]), k);
        *(Vu0::Vec*)&k2 = k;
        Vu0::Vec pc = Vu0::Vec::Of(*pos);
        CopyMatrix(&rot, &s);
        *(Vu0::Vec*)&p = Vu0::Add(pc, Vu0::Rotate(rot, Vu0::Vec::Of(*dir)));
        if (TestOwnerGraphSpan(self, pos, &p, 1, &span) != 0 && best < span.time[1]) {
            best = span.time[1];
            Vu0::Q(hit) = Vu0::Q(span.q[1]);
            if (1.0f <= best) break;
        }
        i++;
    } while (i < 11);
    *(Vu0::Vec*)dir = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(hit), Vu0::Vec::Of(*pos)), k);
}
