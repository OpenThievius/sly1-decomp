// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1533/1700 (90.2%), checked 2026-11-13
// NEAR (2026-11-10, w13-1DEBE8): ControlTintBlendCollider. Size and frame now match (0x200, s5
// saved). The frame came from two things. (1) The second product is a by-value inline
// (RotatedRows, g++'s named return value) passed straight to MultiplyByTransposedMatrix3x3:
// expand_call allocates the call's return temporary (0xE0, later reused by the velocity and
// its Scalar slots) before it expands the argument, whose inline frame (t at 0x110, out at
// 0x140) comes next, as in retail; the declared p/q locals put them the other way round.
// (2) Retail's fifth saved register s5 is &g_unitRange for the speed clamp: CSE carries an
// address computed after the lean clamp's join (the block of the three BuildAxisAngleMatrix
// calls, with the speed test's then-arm falling through) into the speed arm, so `unit` is
// taken there; written in the lean or the w clamp it is wrong (lean and w compute their own
// in retail). The rows of frame->m110 read through a u128 pointer give retail's
// `addiu v0,v0,0x110; move a1,v0; lqc2 0x10(v0)`; the first product stored to self->m660
// first puts the 660 rows before m's.
// Still differs (re-scored 2026-11-10, w15-1DEBE8; the signature is now slot 0x134's,
// Desc05::m49 (self, dt, pad), dt unread, no code change):
// (a) global-alloc order: pad (11 refs over 331 insns, 0.100) ranks below &cur (3 over 29,
// 0.103), so pad takes s3 for retail's s2; then r509 (%hi g_unitRange, 5/290, 0.034) ranks
// below r506 (%hi g_unitZVector, 2/54, 0.037) and the s1/s3 pair swaps. One more pad ref
// gives retail's s2 (diagnostic: the stick heading call written in both arms of the camera
// if/else), but cross-jumping cannot merge those copies (the fall-through arm's call ends its
// block with flow's (use (const_int 0)), so find_cross_jump stops at once): 1720 bytes.
// (b) the third BuildAxisAngleMatrix's lui/a1/a0 issue in idle alu slots before the first
// product's stores; retail has them after the rot stores. A loop note would do it, but
// final.c aligns the first label after any NOTE_INSN_LOOP_BEG and retail's labels after
// 0x1DEEE4 are 4 mod 8: no loop there (docs/toolchain/sched1.md). Also the 660 row stores
// (retail 0x670, 0x680, 0x660) and call 2's a0/a1 order (sched2, likely from (a)'s registers).
// (c) w's slot: RotateTransposed reads frame->m110's rows through a u128 pointer, which waits
// for the MEM_SCALAR_P slot stores; with the rows read as Vec members (a RotateTransposed
// variant like RotateMembers, tried only as a diagnostic, not a helper of the project yet)
// the whole velocity tail is retail's (docs/toolchain/alias-classes.md).
// W23 (2026-11-11, tools/globalalloc.py replays the dumps exactly: 177 of 177 dispositions): (a) is two
// separate ranking flips, both confirmed with --set. Retail's s1/s2/s3 for &tgt (r126), pad (r118),
// &cur (r124), %hi g_unitRange (r510) and %hi g_unitZVector (r507) all come out with
// `--set 124:length=31 --set 126:length=30 --set 118:length=333 --set 510:refs=6` (or
// `--set 507:length=60` in place of 510's refs). So: (1) &cur (3 refs over 29) must rank below pad
// (11 over 331, 997): two more pre-reload insns where both &cur and &tgt live (insns 51-126: the
// f720 == 2 tests and the teleport arm) would do it, e.g. a copy that reload deletes; the then-arm
// (desc slot 84 only) does not count, both are dead there. (2) r510 (5 refs, life 2 x 145 by
// update_equiv_regs) must outrank r507 (2 refs, 2 x 27): one more g_unitRange ref, or r507 living
// 3 insns longer. The pre-reload insn count over r510's span equals the final code's (144 vs 145),
// so retail's difference is in refs or lives, not in deleted copies there. Tried: the two key reads
// as one inline helper called twice (both addresses then formed before the first call; 82 lines).
// W24 (2026-11-11): a --set scan of every allocno (refs +-1/+2, length +-2, x0.9, x1.1, /2, x2) on
// top of 124:length=31 finds no other lever: only 507:length=60, 510:refs=6 or 7, 510:length=145
// or 261. (a) needs exactly &cur >= 31 and &tgt <= 30, and the region's insns (41-126 less the
// then-arm) are retail's final code one for one, so two insns retail had there must go after
// global-alloc (reload's no-op copies, reload_cse, reorg, cross-jumping or flow2's dead stores).
// (b) is sched1's order in bb 21: gcse inserts the copies 1392 (r507) and 1395 (r510) at the end
// of bb 21, and sched1's birthing rule issues each right after its source, 394 (%hi
// g_unitZVector, priority 6) and 452 (%hi g_unitRange, 7). r510 wins when 5 x life(r507) >
// life(r510) in real insns; 1392 two places earlier is a tie (344 each, allocno 507 first).
// `sched1.py --prio 394=8` or `--prio 452=5` gives it; 394 needs two more cycles on the cross
// product's chain (394-395-415-420-430), e.g. Cross's three instructions as three asms, which is
// not a helper. r510's refs are flow's (before combine, never recounted) and the flow dump already
// has its five references in their final form. Tried (78 lines unless noted): the f720 test as
// `cur != 0x352` first (107), `f720 == 2 &&` in both conditions, a switch on f720, a Vec Cross.
// w25 (2026-11-11): the lives global-alloc ranks are sched1's recount of every insn in its output
// (docs/toolchain/sched1.md, "Invisible instructions"). Of the code-less insns that reach sched1
// (flow's nop after a block-ending call, a clamp's join copy, an argument copy in its own
// register, GCSE's copies) none fits (a)'s region without changing code; inline parameter and
// Vec copies are gone after cse1 and combine. Tried: both stick tests as an inline predicate
// `StickPushed(pad)` (keeps a store-flag sequence, 1724 bytes).
// w35 (2026-11-12): func_00130C58's walls were the notes of a loop that runs once (loop-depth
// references, a barrier after LOOP_BEG and LOOP_END; docs/toolchain/loops.md, "The 3's second
// set"), so the same was tried here as a probe: each of the 33 top-level statements in its own
// `do { } while (0)`. 25 of them add the aligned label's nop (1704 bytes: no LOOP_BEG can sit
// there in retail, as (b) already found); the 8 that keep 1700 (the first if, the f720 block,
// the target-key test, reach, the second ComputePolarOffset(&axis), vel, the body's velocity
// store and the last if) are no closer: the same 78 lines or more, and one more pad reference
// at depth 2 (reach, the last if) overshoots, pad takes s1. No single such region is retail's
// here; (a) and (b) stay as above.
// w40-fc (2026-11-12): (b) is a block boundary, not a barrier. Probe (not a match, the store is
// invented): `if (self != 0) k = 0.0f;` between `rot = m;` and the third BuildAxisAngleMatrix,
// k declared at the top and assigned again on both later paths. flow1 deletes the store, the
// branch and label split the block through sched1, the allocators and sched2, and jump2 deletes
// the branch to the next insn (a register-only test leaves nothing): the call's lui, a1, lwc1,
// a0 come out in retail's order, 1700 bytes, 56 lines, registers only
// (build/swarm/w40-fc/a2.cpp; with `pad != 0` pad takes s1, 61 lines). With the split, block
// A's VU0 registers move (tilt rows vf5/vf2 for retail's vf6/vf3): replaying local-alloc
// (build/swarm/w40-fc/lq.py), retail needs the tilt's second row live over at least 9 insns
// (7 in the probe) and the first row with the product's last row over at least 25 (23), i.e.
// two more sched1 insns between the tilt loads and the last row's product that leave no code;
// the unsplit form had them only because the three argument insns were scheduled there. So
// retail's block A holds two invisible insns, r507's life three and &cur's two: the same kind
// of thing in three blocks, still unidentified (docs/toolchain/sched1.md, "Argument moves
// held back").
// w44-fc (2026-11-12): the invisible insns of (a) are two jumps. func_001EC7A8 matched with an
// if/else whose arms flow1 deletes (docs/toolchain/alias-classes.md, "A merged arm keeps its
// place"): the conditional jump and the then-arm's jump over the else stay through sched1, both
// allocators and sched2 and leave no code (a test of a register against zero leaves nothing at
// all). Probe here (invented, not a match): on top of w40-fc's probe for (b), `if (self != 0)
// reach = pad->f48; else reach = pad->f7C;` between the two key reads, reach set again where
// it is computed. W23's numbers come out as predicted, &cur and pad two insns longer and &tgt
// not: pad takes s2 and &cur s3 everywhere, 56 lines to 42 (build/swarm/w44-fc/f2/s1.cpp). It
// is not retail's form: the first key read becomes `addiu a1,sp,368` with `move s3,a1` in the
// call's slot (retail `addiu s3`, `move a1,s3`). The same if/else after the second key read
// overshoots (63 lines); with a real test (`self->f720 == 2`, `cur == 0x352`) its operands stay
// (1708 bytes). Still open: the s1/s3 pair (r507 against r510), block A's two insns and the
// 660 rows' store order, the velocity tail. For the store order (retail 0x670, 0x680, 0x660):
// replaying sched1 with the two row loads through `self + 0x660` (insns 704, 705) depending
// only on their own rows' stores gives retail's order of the three stores, so in retail those
// loads did not wait for row 0's store: the address pseudo had a known value for alias.c
// (a REG_EQUAL or REG_EQUIV note on its set), the wall func_00144540 has too. Also ruled out:
// `rot = m` through an inline with a self-assignment test (folded before cse, no change).
// w46-c (2026-11-13), about 45 compiles, all probes on top of w44-fc's (build/swarm/w46-c/f1/): (1) the
// velocity tail is exact with the rows of frame->m110 read as Vu0::Vec members in a copy of
// RotateTransposed (t1.cpp, 42 lines to 28; here 78 to 64, as RotateTransposedMembers below:
// a twin of Vu0::RotateMembers that would belong in include/vu0.h, the maintainer's call). (2) The 660 rows' store order is not an alias fact: with
// the row loads cut from row 0's store (and from each other's) the replay puts row 0's store
// last, after m's. What gives retail's order of the whole second half of block A (0x670,
// 0x680, 0x660, m's rows, offset, the two row loads, the product, rot's rows around v640's
// store) is rank_for_schedule's register weight: rows 1 and 2's products dying at their
// stores to self (`wif.py t1.d 28 w:631=0 w:673=0`). A priority does it too in the replay,
// but a real one passes down the chain: rows 1 and 2 stored a second time right after the
// product (w_t1_q.cpp) leave no code (1700 bytes) and put row 1's store first, with its
// product ahead of row 0's, which retail does not have. So in retail m's and rot's rows 1
// and 2 are stored from other pseudos than the products, in the same registers: two copies
// that leave no code, which is also block A's two insns. `m = *p` with p a pointer local
// (t3.cpp) gives the deaths and retail's order of the three stores, but its copies are
// lq/sq through a GPR. (3) The tilt's rows loaded in the order 1, 2, 0 (t2.cpp, values
// passed to RotateRows) give retail's vf3/vf2 for tilt row 1 and turn row 2 (23 lines): row
// 1 then lives 9 insns. Left there: row 0's quantity against the product's result (vf6
// against vf5; it needs 5 more insns of life, or the product's result stored at once) and
// the three stores. (4) The product helpers of include/mul_rotation.h in place of
// RotateRowsBy, m and rot declared after them: 44 lines or more, their copies go through
// the out pointer. Not tried: (a), (b) and r507 beyond w44-fc's probes.
// w49-f (2026-11-13), 33 compiles (build/swarm/w49-f/f/), no closer. Established from
// haifa-sched.c: INSN_REG_WEIGHT is the pattern's SETs less its REG_DEAD/REG_UNUSED notes, so a
// store weighs 1, or 0 where a register dies in it (base: all six block-A stores weigh 1; `wif.py
// base.d 25 w:610=0 w:652=0` gives retail's order from 0x670 to rot's last row). And haifa
// reattaches the deaths after scheduling (attach_deaths_insn), so local-alloc sees the new order.
// Ruled out by reasoning, each checked against the dumps: (1) a code-less copy X1 = P1 ahead of
// the 0x670 store in the stream: cse makes one of the two canonical and rewrites the other's
// uses, and the copy would feed m's store (priority 61) so sched1 issues it first; both
// registers then live and the copy is code (s1: Vec by-value parameters, 1704 bytes). (2) m's
// rows reloaded after the 660 stores and deleted by reload_cse in the product's register (the
// t3 shape): a pseudo only loaded and stored is TI_REGS (movti and stores are neutral in
// regclass) and local-alloc gives it a GPR (v1/v0, as in t3); only a "j" use makes it VU0, and
// that use is code. (3) m and rot stored before the 660 stores (a1-a3): the frame stores still
// feed RotateTransposed's loads (priority 61) and rot's go early; rot written after
// RotateTransposed always holds the last use of P1 and P2. Also no change: products and stores
// as Vu0::Vec values (v1-v4, cse folds every copy), RotateTransposedMembers for the first
// product's transpose (e1-e3: Vec-member loads still wait for the mem/s frame stores), m copied
// through a pointer or u128 rows (p1-p6, 1708 bytes or GPR copies), RotatedRows for the first
// product and chained assignments (q1-q4, 1712-1752 bytes). Left: retail's rows 1 and 2 of m
// and rot come from a register that is not the product's, with no code, and no plain C++ form
// that gives that is known; (a), (b) and r507 as above.
// w50-f (2026-11-13), about 30 compiles (build/swarm/w50-f/): the 660 rows' order is not a
// weight. In the dumps the six stores (three to self, three to m) tie on priority (61), weight
// and dependents, so sched1 issues them in LUID order as each becomes ready; retail's order
// (0x670, 0x680, 0x660, m's rows) is the order of the stream when row 0's store to self is
// emitted after rows 1 and 2 (either order of those two) and before `m = self->m660`. Written
// so (below: the first product kept in a local, stored last), block A is retail's insn for
// insn except for the three argument insns of wall (b) that sit among its loads: the same 64
// lines here, but with w40-fc's and w44-fc's probes for (a) and (b) on top, 26 lines, all
// registers (build/swarm/w50-f/f/f2.cpp; 28 without it). No pseudo other than the products is
// needed: the weights of w46-c and w49-f were another way to the same order in the replay.
// What is left, each measured on that probe: (1) (a)'s `addiu a1,sp,368; move s3,a1` (the
// probe's own artefact); (2) s1/s3 (r507 against r510, as W23); (3) block A's VU0 registers:
// tools/globalalloc.py's local-alloc replay gives the tilt's row 1 priority 11428 (4 refs over
// 7 insns) against 10000 for turn's row 2 (2 over 2), and the quantity of tilt's row 0 and the
// last product 10434 (8 refs over 23) against 10000 for the transposed product's result;
// retail has both the other way, so 9 insns for the first and 25 for the second (w40-fc's two
// insns between the tilt loads and the last product), or turn's row 2 loaded directly before
// its product and v640 stored directly after the transposed product in sched1's order.
// (b) holds after reload too: in our sched2 the call's `addiu a1` and `move a0` again take
// the idle alu slots beside the tilt loads, where retail's slots are idle, so the boundary is
// not a CLOBBER (reload deletes those before sched2); a jump that jump2 deletes, or an asm
// without operands, are what is left. Ruled out, compiled: a run-once loop from each of six
// starts (the heading call, reach, the first ComputePolarOffset, lean, the first
// BuildAxisAngleMatrix, HandleStepSequenceSkipButtons) to `rot = m` with the new store order
// (1704 bytes, or 52 lines with VU0 registers vf10/vf11: depth 2 is not retail's); the w
// clamp written in both arms of the speed test for cross-jumping to merge (one more pad and
// g_unitRange reference each, but the copies schedule differently and stay: 1796 bytes);
// the key tests as switches (1704 to 1716 bytes); one u128 reused for the cross product and
// the rows (a vmove, 1704 bytes). From toplev.c: jump runs again before cse2, so an arm
// emptied after cse1 (an inline's unused result) leaves no jump for sched1; only an arm flow1
// or a later pass empties does.
#include "common.h"
#include "vu0.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "world.h"
#include "screen_element.h"
#include "font.h"
#include "globals.h"
#include "game_progress.h"
#include "level_entry.h"
#include "message_body.h"
#include "owner_message.h"
#include "shapes.h"
#include "state_walker.h"
#include "pad_record.h"
#include "camera.h"

extern f32 g_frameDt;
extern f32 D_002757F0[4];
extern Vec02 D_002757E0;
extern f32 D_00275800[4];
extern f32 D_00275810[8];
extern f32 D_00275830[4];
extern f32 D_00275840[4];
extern f32 D_00275850[4];
extern f32 D_00275860;
extern f32 D_00275864;
s32 HasAnimationDrivenAttachment(TintBlendCollider* self);
void GetStateWalkerCurrentKey(void* p, s32* out);
void GetStateWalkerTargetKey(void* p, s32* out);
void TeleportStateWalker(void* p, s32 n);
void SetStateWalkerTarget(void* p, s32 n);
void HandleStepSequenceSkipButtons(void* self, PadRecord* rec);
s32 IsTopCameraController(void* p);
void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);
f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);
void ClearPadPressedBits(PadRecord* self, s32 mask);
void SetTintBlendColliderState(void* self, s32 flag);
extern s32 g_movieChecksumFailed;

struct TintPart_1DEBE8 { u8 pad00[0x18]; PlacedObject* frame; };
struct TintBody_1DEBE8 { u8 pad00[0x20]; Vec02 v20; u8 pad30[0x40 - 0x30]; Mat02 m40; };
typedef void (*TintSelfFn_1DEBE8)(void* self);

static inline f32 Quadratic(const f32* poly, f32 z)
{
    return poly[0] + z * (poly[1] + z * poly[2]);
}

// The rows of m, each turned by r, returned by value (g++'s named return value).
static inline Mat02 RotatedRows(const Mat02& r, const Mat02& m) return out
{
    const u128* q = (const u128*)&m;
    Mat02 t;
    Vu0::Q(t.r[0]) = Vu0::RotateUntied(r, q[0]);
    out.r[0] = t.r[0];
    Vu0::Q(t.r[1]) = Vu0::RotateUntied(r, q[1]);
    out.r[1] = t.r[1];
    Vu0::Q(t.r[2]) = Vu0::RotateUntied(r, q[2]);
    out.r[2] = t.r[2];
}

// Vu0::RotateTransposed with the rows read as Vu0::Vec members (mem/s at a varying address), as
// Vu0::RotateMembers reads Rotate's: the loads then do not wait for the weights' slot stores
// (alias.c, fixed_scalar_and_varying_struct_p). Kept here until the function matches.
template <class M> static inline u128 RotateTransposedMembers(const M& m, u128 v)
{
    const Vu0::Vec* r = (const Vu0::Vec*)&m;
    u128 out, p0, p1, p2, one;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, vf0, vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
            "vadday.x ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\t"
            "vaddax.z ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=&j"(out), "=&j"(one), "=&j"(p0), "=&j"(p1), "=&j"(p2)
            : "j"(r[0].q), "j"(r[1].q), "j"(r[2].q), "j"(v));
    return out;
}

void ControlTintBlendCollider(TintBlendCollider* self, f32 dt, PadRecord* pad)
{
    Vec02 offset;
    Vec02 axis;
    Mat02 tilt;
    Mat02 turn;
    Mat02 m;
    Mat02 rot;
    s32 cur;
    s32 tgt;
    f32 stick;
    if (HasAnimationDrivenAttachment(self) != 0) {
        return;
    }
    GetStateWalkerCurrentKey(self->f75C, &cur);
    GetStateWalkerTargetKey(self->f75C, &tgt);
    if (self->f720 == 2) {
        if (cur == 0x352) {
            ((TintSelfFn_1DEBE8*)self->desc)[84](self);
        } else if (self->f738 != 0 && 0.7f < pad->f7C) {
            ((TintSelfFn_1DEBE8*)self->desc)[84](self);
            TeleportStateWalker(self->f75C, 0x352);
            GetStateWalkerCurrentKey(self->f75C, &cur);
            GetStateWalkerTargetKey(self->f75C, &tgt);
        }
    }
    if ((u32)(cur - 0x352) >= 2) {
        return;
    }
    if (tgt != -1 && tgt != 0x352 && tgt != 0x353) {
        return;
    }
    HandleStepSequenceSkipButtons(self, pad);
    if (IsTopCameraController(&g_camera->ctl454) == 0 && 0.7f < pad->f7C) {
        ComputeCameraRelativeStickHeading(g_camera, pad, 1, &self->f638);
        if (__builtin_fabsf(WrapAngle(self->f638 - ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x))) < 0.5f && g_movieChecksumFailed == 0) {
            SetStateWalkerTarget(self->f75C, 0x353);
        }
    } else {
        SetStateWalkerTarget(self->f75C, 0x352);
    }
    ComputeCameraRelativeStickHeading(g_camera, pad, 0, &stick);
    f32 reach = ((ValueRange*)D_002757F0)->Clamp(Quadratic(&D_002757E0.x, pad->f48));
    ComputePolarOffset(&offset, stick + 3.14159274f, reach, 0.0f);
    ComputePolarOffset(&axis, stick, 1.0f, 0.0f);
    Vu0::Q(axis) = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(axis));
    f32 lean = g_unitRange.Limit(Quadratic(D_00275800, pad->f48));
    ValueRange* unit = &g_unitRange;
    BuildAxisAngleMatrix(&axis, &tilt, D_00275810[0] * lean);
    BuildAxisAngleMatrix(&g_unitZVector, &turn, self->f638);
    u128 p0 = Vu0::RotateUntied(tilt, Vu0::Q(turn.r[0]));
    Vu0::Q(self->m660.r[1]) = Vu0::RotateUntied(tilt, Vu0::Q(turn.r[1]));
    Vu0::Q(self->m660.r[2]) = Vu0::RotateUntied(tilt, Vu0::Q(turn.r[2]));
    Vu0::Q(self->m660.r[0]) = p0;
    m = self->m660;
    Vu0::Q(self->v640) = Vu0::RotateTransposed(self->m660, Vu0::Q(offset));
    rot = m;
    BuildAxisAngleMatrix(&axis, &m, D_00275830[0] * lean);
    PlacedObject* frame = ((TintPart_1DEBE8*)self->f748)->frame;
    rot = MultiplyByTransposedMatrix3x3(frame->m110, RotatedRows(m, frame->m110));
    ((TintBody_1DEBE8*)self->f74C)->m40 = rot;
    ((TintBody_1DEBE8*)self->f754)->m40 = rot;
    f32 speed = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150)));
    f32 k;
    if (0.0f < speed) {
        k = D_00275860 * unit->Clamp(Quadratic(D_00275840, speed)) / speed;
    } else {
        k = 0.0f;
    }
    f32 w = D_00275864 * g_unitRange.Clamp(Quadratic(D_00275850, pad->f48));
    ComputePolarOffset(&axis, stick, 1.0f, 0.0f);
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulXSum(Vu0::Q(self->v150), Vu0::Scalar(k), Vu0::Q(axis), Vu0::Scalar(w));
    Vu0::Q(((TintBody_1DEBE8*)self->f74C)->v20) = RotateTransposedMembers(((TintPart_1DEBE8*)self->f748)->frame->m110, Vu0::Q(vel));
    if (self->f73C != 0 && g_player != 0 && (pad->flags & 0x40)) {
        ClearPadPressedBits(pad, 0x40);
        SetTintBlendColliderState(self, 0);
    }
}
