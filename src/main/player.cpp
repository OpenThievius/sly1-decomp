// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x16F608 to 0x1793C0: the player, class 0x07 (struct Player in
// include/switched_collider.h), its methods, its state changes and its target choice. Its name
// is ours, after the class.
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "world5_boss.h"
#include "world5_countdown.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "font.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "background_job.h"
#include "vu0.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "owner_message.h"
#include "transform_object.h"
#include "list_iter.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "animation.h"
#include "anim_curve.h"
#include "fpu.h"
#include "attachment.h"
#include "aim_blend_grid.h"
#include "on_off_object.h"
#include "mul_rotation.h"
#include "value_range.h"
#include "counted_collider.h"
#include "pooled_object.h"
#include "object_pool.h"
#include "sound_level.h"
#include "state_graph.h"
#include "target_binding.h"
#include "point_object.h"
#include "texture_render_object.h"
#include "object_finder.h"
struct BufferedStream;

// Types other files define, named by the parameters of their functions declared here.
struct BlendAnimation;
struct BlendSlot;
struct CameraSoundOwner;
struct Chooser;
struct Chooser_1CDFB8;
struct FaceRef;
struct FollowProbe;
struct MeshHitEntry;
struct PathObject;
struct PathPad;
struct PlayerBlendItem;
struct PlayingSound;
struct PooledContact;
struct RingSource;
struct ScaledTransform;
struct TargetCand;
struct ThreeBlendRecord;
struct TrailRing;
struct TurnBlendRecords;

extern f32 g_frameDt[];
extern f32 g_gameTime[];

// The ramp ApproachValueWithRamp turns the player's spin angle (0x2434) back to zero with
// (func_001727B0); the two ids are those of the spin's links (0x16F, 0x170).
struct SpinRampParams { f32 maxSpeed; f32 endSpeed; f32 rampTime; f32 maxAccel; s32 f10; s32 f14; };

// size: pointer, word accesses only
Player* g_player = 0;
f32 D_00262E14 = 455.0f;
f32 D_00262E18 = 0.699999988f;
f32 D_00262E1C = 0.600000024f;
f32 g_soundEffect94Volume = 0.699999988f;
f32 g_soundEffect7EVolume = 0.600000024f;
f32 D_00262E28 = 1000.0f;
f32 D_00262E2C = 850.0f;
f32 D_00262E30 = 50.0f;

// NEAR: frame, saves, the vtable call and the branch tree match; the 0xD path loads its two floats into $f1/$f0 where retail uses $f0/$f1, so the shared store tail differs

// The path the player follows (0x23B8, 0x23BC): its frame, its curve, and whether it is a rail.
struct PathRecord { u8 pad00[0x18]; PlacedObject* frame; u8 pad1C[0x34 - 0x1C]; PathCurve* curve; u8 pad38[0x40 - 0x38]; s32 isRail; };
typedef s32 (*VFn_170410)(Player* self, void* out);

f32 g_slideRateFirst = 0.8f;
f32 g_slideRateSecond = 0.5f;
f32 g_state13ExitDelay = 0.25f;

ObjectLink g_playerCharacterLinks[151] = {
    {0x0, 0x145, 0x1188},
    {0x0, 0x82, 0x724},
    {0x0, 0x83, 0x774},
    {0x2, 0x84, 0x7C4},
    {0x2, 0x85, 0x814},
    {0x2, 0x86, 0x864},
    {0x2, 0x87, 0x8B4},
    {0x0, 0x92, 0x914},
    {0x0, 0x93, 0x934},
    {0x0, 0x94, 0x954},
    {0x0, 0x95, 0x974},
    {0x0, 0x96, 0x994},
    {0x0, 0x97, 0x9B4},
    {0x0, 0x98, 0x9D4},
    {0x0, 0x99, 0x9F4},
    {0x0, 0x9F, 0xA24},
    {0x0, 0xA0, 0xA44},
    {0x0, 0xA1, 0xA64},
    {0x0, 0xA2, 0xA84},
    {0x0, 0xA3, 0xAA4},
    {0x0, 0xA4, 0xAC4},
    {0x0, 0xA5, 0xAE4},
    {0x0, 0xA6, 0xB04},
    {0x0, 0xA7, 0xB24},
    {0x0, 0xA9, 0xB28},
    {0x0, 0xA8, 0xB2C},
    {0x0, 0xAA, 0xB34},
    {0x0, 0xAB, 0xB54},
    {0x0, 0xAC, 0xB74},
    {0x0, 0xAD, 0xB94},
    {0x0, 0xAE, 0xBB4},
    {0x0, 0xAF, 0xBD4},
    {0x0, 0xB0, 0xBF4},
    {0x0, 0xB1, 0xC14},
    {0x0, 0xB2, 0xC34},
    {0x0, 0xB4, 0xC38},
    {0x0, 0xB3, 0xC3C},
    {0x0, 0xB5, 0xC44},
    {0x0, 0xB6, 0xC94},
    {0x2, 0xB7, 0xCE4},
    {0x2, 0xB8, 0xD34},
    {0x2, 0xB9, 0xD84},
    {0x2, 0xBA, 0xDD4},
    {0x0, 0xBB, 0xE24},
    {0x0, 0xBC, 0xE28},
    {0x0, 0xBD, 0xE2C},
    {0x2, 0xBE, 0xE34},
    {0x2, 0xBF, 0xE84},
    {0x2, 0xC0, 0xED4},
    {0x2, 0xC1, 0xF24},
    {0x2, 0xC2, 0xF74},
    {0x2, 0xC3, 0xFC4},
    {0x2, 0xC4, 0x1014},
    {0x2, 0xDD, 0x1018},
    {0x2, 0xDE, 0x101C},
    {0x0, 0x8C, 0x1020},
    {0x0, 0x8D, 0x1024},
    {0x0, 0x8E, 0x1028},
    {0x0, 0x90, 0x1030},
    {0x0, 0x91, 0x1034},
    {0x0, 0x157, 0x2364},
    {0x0, 0x158, 0x2370},
    {0x0, 0x159, 0x237C},
    {0x0, 0x8B, 0x1038},
    {0x2, 0x9E, 0x1060},
    {0x0, 0x9A, 0x1064},
    {0x0, 0x9D, 0x1068},
    {0x0, 0x9B, 0x1040},
    {0x0, 0x9C, 0x1050},
    {0x0, 0x7D, 0x21C4},
    {0x0, 0xF3, 0x2544},
    {0x0, 0xF7, 0x2550},
    {0x0, 0xF5, 0x2560},
    {0x0, 0xF9, 0x256C},
    {0x2, 0xFB, 0x257C},
    {0x2, 0xFF, 0x2588},
    {0x2, 0xFD, 0x2598},
    {0x2, 0x101, 0x25A4},
    {0x2, 0x103, 0x25B0},
    {0x2, 0x104, 0x25B4},
    {0x0, 0x105, 0x25B8},
    {0x0, 0x107, 0x25C0},
    {0x0, 0x1B8, 0x25C8},
    {0x2, 0x106, 0x25BC},
    {0x2, 0x108, 0x25C4},
    {0x2, 0x11A, 0x25D4},
    {0x0, 0x64, 0x1390},
    {0x2, 0x65, 0x1394},
    {0x2, 0x66, 0x1398},
    {0x2, 0x67, 0x13AC},
    {0x2, 0x68, 0x13B0},
    {0x2, 0x69, 0x13D4},
    {0x2, 0x6A, 0x13D8},
    {0x2, 0x6B, 0x13DC},
    {0x2, 0x6C, 0x13E0},
    {0x2, 0x6D, 0x13EC},
    {0x2, 0x6E, 0x14A8},
    {0x2, 0x6F, 0x14AC},
    {0x2, 0x70, 0x14B0},
    {0x2, 0x71, 0x14B4},
    {0x2, 0x72, 0x14B8},
    {0x2, 0x73, 0x14BC},
    {0x2, 0x74, 0x14C0},
    {0x2, 0x75, 0x14C4},
    {0x2, 0x76, 0x14CC},
    {0x2, 0x78, 0x14D0},
    {0x2, 0x77, 0x14D4},
    {0x2, 0x79, 0x14D8},
    {0x2, 0x7A, 0x14DC},
    {0x2, 0x7B, 0x146C},
    {0x2, 0x7C, 0x13C4},
    {0x0, 0xE2, 0x112C},
    {0x0, 0xE3, 0x1130},
    {0x0, 0xE4, 0x1134},
    {0x0, 0xE5, 0x1138},
    {0x0, 0xE6, 0x113C},
    {0x0, 0xE7, 0x1140},
    {0x0, 0xE8, 0x1144},
    {0x0, 0xE9, 0x1148},
    {0x0, 0xEA, 0x1150},
    {0x0, 0xEC, 0x1154},
    {0x0, 0xEB, 0x1158},
    {0x0, 0xED, 0x115C},
    {0x0, 0xEE, 0x1160},
    {0x2, 0xEF, 0x110C},
    {0x2, 0xF1, 0x1110},
    {0x2, 0xF2, 0x1114},
    {0x2, 0x109, 0x25CC},
    {0x2, 0x10A, 0x25D0},
    {0x2, 0x172, 0x243C},
    {0x6, 0x51, 0x2490},
    {0x6, 0x5A, 0x2494},
    {0x2, 0x17D, 0x26D8},
    {0x2, 0x17E, 0x26E0},
    {0x2, 0x17F, 0x26E8},
    {0x2, 0x180, 0x26F0},
    {0x2, 0x181, 0x26F8},
    {0x2, 0x182, 0x2700},
    {0x2, 0x183, 0x2708},
    {0x2, 0x184, 0x2710},
    {0x2, 0x185, 0x271C},
    {0x2, 0x186, 0x2720},
    {0x2, 0x18B, 0x272C},
    {0x20, 0x18D, 0x604},
    {0x2, 0x11B, 0x1070},
    {0x2, 0x11C, 0x107C},
    {0x2, 0x11D, 0x1088},
    {0x2, 0x153, 0x274C},
    {0x2, 0x154, 0x2754},
    {0x2, 0x155, 0x2760},
    {0x2, 0x156, 0x2764}
};
ObjectLink g_playerObjectLinks[27] = {
    { 0x4, 0x60, 0x24F8 },
    { 0x2, 0x161, 0x588 },
    { 0x2, 0x162, 0x58C },
    { 0x2, 0x163, 0x590 },
    { 0x4, 0x5B, 0x2390 },
    { 0x2, 0x62, 0x2394 },
    { 0x2, 0x63, 0x2398 },
    { 0x4, 0x16F, 0x23D0 },
    { 0x4, 0x170, 0x23D4 },
    { 0x2, 0x173, 0x23D8 },
    { 0x4, 0x160, 0x584 },
    { 0x20, 0x164, 0x59C },
    { 0x20, 0x165, 0x5A0 },
    { 0x20, 0x166, 0x5A4 },
    { 0x22, 0x169, 0x267C },
    { 0x22, 0x7E, 0x25D8 },
    { 0x2, 0x7F, 0x25DC },
    { 0x2, 0x80, 0x25E0 },
    { 0x2, 0x1B9, 0x25E4 },
    { 0x22, 0x81, 0x25E8 },
    { 0x6, 0x50, 0x1504 },
    { 0x26, 0x18E, 0x1508 },
    { 0x26, 0x18F, 0x150C },
    { 0x26, 0x190, 0x1510 },
    { 0x26, 0x191, 0x1514 },
    { 0x22, 0x192, 0x1518 },
    { 0x26, 0x151, 0x2750 }
};
f32 D_002636A0[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 D_002636B0[4] = { 0.0f, 0.25f, 0.449999988f, 0.449999988f };
f32 D_002636C0[4] = { 0.0f, 0.25f, 0.449999988f, 0.449999988f };
f32 D_002636D0[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 D_002636E0[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 D_002636F0[4] = { 37.0f, 0.0f, 25.0f, 0.0f };
f32 g_playerGravityScale = 1.29999995f;
f32 g_playerMass = 238689.0f;
f32 D_00263708 = 0.0f;
f32 D_0026370C = 0.0f;
f32 D_00263710[4] = { -1.5f, 0.00100000005f, 0.0f, 0.0f };

// Globals typed by worker dv02, from retail's bytes and their readers.
f32 D_00263720[4] = { 1.0f, -4.0f, 0.0f, 0.0f };
RampProfile g_playerTiltRampProfile = { 10.0f, 0.0f, 0.5f, 50.0f };
RampProfile g_steeringRampProfileSlow = { 40.0f, 0.0f, 0.25f, 200.0f };
RampProfile g_steeringRampProfileFast = { 15.0f, 0.0f, 0.25f, 100.0f };
f32 g_steeringBlendBySpeedCurve[4] = { -0.200000003f, 0.00200000009f, 0.0f, 0.0f };
f32 g_steeringBlendByLeanCurve[4] = { 0.200000003f, 0.0f, 0.800000012f, 0.0f };
f32 g_turnTowardRotationRates[4] = { 40.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00263790[4] = { 0.0f, 2.5f, 0.0f, 0.0f };
f32 D_002637A0[4] = { 0.0f, 5.0f, 0.0f, 0.0f };
f32 D_002637B0 = 1.0f;
f32 D_002637B4 = 0.3f;
f32 D_002637B8 = 1.5f;

f32 D_002637BC = 2.0f;

f32 D_002637C0[3] = { 0.1f, 2.0f, 0.0f };
f32 D_002637CC = 0.875999987f;
s32 D_002637D0 = 50;
s32 D_002637D4 = 100;
f32 g_motionLookaheadTime = 0.100000001f;
f32 g_followPullRange = 1000.0f;
f32 D_002637E0 = 20.0f;
f32 D_002637E4 = -7.5f;
f32 D_002637E8[2] = { 0.5f, 0.0f };
f32 g_followPullCurve[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_00263800[4] = { -20.0f, 5.0f, -25.0f, 0.0f };
f32 D_00263810[4] = { 0.0f, -0.600000024f, 0.5f, 0.0f };
f32 D_00263820[4] = { -20.0f, 5.0f, -25.0f, 0.0f };
f32 D_00263830[4] = { 0.0f, -0.600000024f, 0.5f, 0.0f };
f32 D_00263840[4] = { 0.0f, 0.0f, -100.0f, 0.0f };
f32 D_00263850 = -0.5f;
f32 D_00263854 = 100.0f;
f32 g_hookTurnRamp[6] = { 4.0f, 0.0f, 0.5f, 10.0f, 0.0f, 0.0f };
f32 D_00263870[4] = { 0.0f, 0.5f, 0.0f, 0.0f };
f32 D_00263880 = 50.0f;
f32 D_00263884 = -50.0f;
f32 g_scaleApproachRamp[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_00263894 = 0.349999994f;
f32 D_00263898 = 0.0f;
SpinRampParams g_spinRampParams = { 50.0f, 0.0f, 0.25f, 0.0f, 0x16F, 0x170 };
f32 D_002638B8 = 75.0f;
f32 D_002638BC = -325.0f;
f32 D_002638C0 = -50.0f;
f32 D_002638C4 = -350.0f;
f32 D_002638C8[2] = { -300.0f, 0.0f };
f32 D_002638D0[4] = { 1.5f, -0.5f, 0.0f, 0.0f };
f32 g_pivotApproachRamp[4] = { 1500.0f, 0.0f, 0.5f, 0.0f };
f32 g_heightApproachRamp[4] = { 4000.0f, 0.0f, 4.0f, 0.0f };
f32 g_forceApproachRamp[4] = { 600.0f, 300.0f, 0.100000001f, 50.0f };
f32 D_00263910[2] = { 0.150000006f, 0.25f };
f32 g_positionApproachRamp[3] = { 1000.0f, 0.0f, 0.25f };
f32 D_00263924 = 0.899999976f;
f32 D_00263928[2] = { 8.0f, 0.0f };

s32 D_00263930[16] = { -1, 36, 36, 36, -1, 36, 36, 36, 36, -1, 45, 45, 41, 40, 0, 0 };
f32 D_00263970[4] = { 0.0f, 0.0f, -750.0f, 0.0f };
f32 D_00263980[4] = { 0.0f, 0.0f, 500.0f, 0.0f };
f32 D_00263990 = -0.200000003f;
f32 D_00263994 = 1.0f;
f32 D_00263998 = 0.5f;
f32 D_0026399C = 0.25f;
f32 D_002639A0[4] = { -1.0f, 0.00400000019f, 0.0f, 0.0f };
f32 D_002639B0[2] = { 150.0f, -0.75f };
// read as a scalar (func_00175170), so a word, and the word after it
s32 D_002639B8 = 0;
s32 D_002639BC = 0;
f32 D_002639C0[4] = { 0.0f, 0.0f, 75.0f, 0.0f };
f32 D_002639D0[4] = { 0.0f, 0.0f, -225.0f, 0.0f };
f32 D_002639E0[2] = { -75.0f, 0.0f };
f32 g_targetArcDurations[10] = { 0.699999988f, 0.800000012f, 0.899999976f, 1.0f, 1.20000005f, 1.39999998f, 1.60000002f, 1.79999995f, 2.0f, 0.0f };
f32 D_00263A10[32] = { 40.0f, 0.0f, 0.0f, 0.0f, 28.2999992f, 28.2999992f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, -28.2999992f, 28.2999992f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 0.0f, -28.2999992f, -28.2999992f, 0.0f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 28.2999992f, -28.2999992f, 0.0f, 0.0f };
f32 D_00263A90[4] = { 200.0f, 200.0f, 200.0f, 0.0f };
f32 D_00263AA0[4] = { 400.0f, -1.0f, 0.0f, 0.0f };
f32 D_00263AB0[4] = { 0.0f, 1000.0f, 0.0f, 0.0f };

void InitTurningCollider(TurningCollider* self);

void InitPlayer(Player* self)
{
    InitTurningCollider(self);
    self->state = -1;
    self->aimMode = -1;
    self->subState = -1;
    self->jumpKind = -1;
    self->phaseSoundStates[0] = *(Vec4U*)D_002636A0;
    self->phaseSoundStates[1] = *(Vec4U*)D_002636B0;
    self->phaseSoundStates[2] = *(Vec4U*)D_002636C0;
    self->phaseSoundStates[3] = *(Vec4U*)D_002636D0;
    self->phaseSoundStates[4] = *(Vec4U*)D_002636E0;
    self->boundsRadius = 15.0f;
    Vu0::Q(self->gravity) = Vu0::FromFloats(0.0f, 0.0f, -1750.0f);
    self->flags = (self->flags & ~(3ULL << 40)) | (1ULL << 40);
    self->ledgeHandOffset = *(Vec02*)D_002636F0;
    self->trailEnabled = 1;
    self->padSelectMode = -1;
    self->f2728 = 1.0f;
    self->f2724 = 1.0f;
    self->animSeekTime = -3.4028235e+38f;
    self->pulseFadeDuration = 2.0f;
}

void LoadCollider(Collider* self, BufferedStream* in);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void FindOrBuildMemberGroup(void** out, void* self);

void LoadPlayer(Player* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 0x97, g_playerCharacterLinks);
    FindOrBuildMemberGroup((void**)self->pad2428, self);
    self->f2284 = -1.0f;
    self->f21C8 = -1.0f;
    g_player = self;
}

void StartTurningCollider(TurningCollider* self);
void CreateSixEntryBlend(TurningCollider* self, PlayerBlendItem* items, BlendAnimationView** out);
void CreatePlayerTwoEntryBlend(Player* self);
void CreateEightEntryBlend(TurningCollider* self, BlendSlot* slots, BlendAnimationView** gr);
void CreateThreeEntryBlend(void* a0, ThreeBlendRecord* a1, void** a2);
u8* CreatePoseSource(World* root, PlacedObject* value, const T2195_Vt* table);
void InsertAttachment(PlacedObject* self, Attachment* src);
void AddMatrixAttachment(PlacedObject* self, s32 key, Attachment** out);
s32 FindAnimRecord(s32 key);
void BuildCombinedBlendAnimation(Collider* ctx, s32 stride, s32 count, u8* items, s32 nkeys, s32* keyA, s32* keyB, BlendAnimation** out);
void BuildTexturePackets(TextureRenderObject* self, RangeRecord* a);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void ResetPlayerOnOffObject(Player* self);
void ResolvePlayerTableObjects(Player* self);
void SetTurningColliderGravityScale(TurningCollider* self, f32 s);
void SetColliderMass(Collider* self, f32 m);
void* AllocateZeroedFrontMemory(s32 n);
void SetBlendItemWeights(BlendAnimationView* self, s32 a1, s32 a2, void* a3);
extern u8 g_childSumPoseSourceMethods[];
extern u8 g_snapshotPoseSourceMethods[];
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void SetPlayerState(Player* self, s32 state, s32 sub);


void StartPlayer(Player* self)
{
    StartTurningCollider(self);
    ResolveObjectLinks(self, 27, g_playerObjectLinks);
    CreateSixEntryBlend(self, (PlayerBlendItem*)self->sixWayItems, &self->sixWayBlend);
    CreatePlayerTwoEntryBlend(self);
    CreateEightEntryBlend(self, (BlendSlot*)self->eightSlotsB, &self->eightBlendB);
    CreateEightEntryBlend(self, (BlendSlot*)self->eightSlotsC, &self->eightBlendC);
    CreateSixEntryBlend(self, (PlayerBlendItem*)self->sixItemsB, &self->sixBlendB);
    CreateThreeEntryBlend(self, (ThreeBlendRecord*)&self->linkTowardWeight, &self->linkBlend);
    CreateSixEntryBlend(self, (PlayerBlendItem*)self->sixItemsC, &self->sixBlendC);
    self->f598 = self;
    self->f5F0 = self->subStateAnims[28];
    u8* a = CreatePoseSource(self->world, self->rigObject, (const T2195_Vt*)g_childSumPoseSourceMethods);
    *(s8*)(a + 0x10) = 9;
    *(s8*)(a + 0x11) = 9;
    *(s32*)(a + 0x14) = 3;
    *(s32*)(a + 0x1C) = 2;
    InsertAttachment(self->rigObject, (Attachment*)a);
    self->f24FC = a;
    AddMatrixAttachment(self->rigObject, 5, (Attachment**)&self->f2500);
    AddMatrixAttachment((PlacedObject*)self->f618, 5, (Attachment**)&self->f2504);
    AddMatrixAttachment((PlacedObject*)self->f61C, 5, (Attachment**)&self->f2508);
    AddMatrixAttachment((PlacedObject*)self->f610, 7, (Attachment**)&self->footPartA);
    AddMatrixAttachment((PlacedObject*)self->f614, 7, (Attachment**)&self->footPartB);
    self->rigPoseSource = CreatePoseSource(self->world, self->rigObject, (const T2195_Vt*)g_snapshotPoseSourceMethods);
    *(s32*)((u8*)self->rigPoseSource + 0x14) = 1;
    InsertAttachment(self->rigObject, (Attachment*)self->rigPoseSource);
    self->trailOwner = self->f23D0;
    self->trailAnimRecord = FindAnimRecord(0x15A);
    self->f1530 = 0.5f;
    self->f1560 = *(Vec02*)D_00263710;
    self->f1570 = *(Vec02*)D_00263720;
    self->f1538 = 2;
    TransformPointBetweenFrames(0, (PlacedObject*)self->f23D0, (Vec02*)((u8*)self->f23D4 + 0x140), &self->f1540);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->f1540)));
    Vu0::Q(self->f1540) = Vu0::MulX(Vu0::Q(self->f1540), Vu0::Scalar((len + self->boundsRadius) / len));
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend4, 0, 0, 0, (BlendAnimation**)&self->aimAnim4);
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend5, 0, 0, 0, (BlendAnimation**)&self->aimAnim5);
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend6, 0, 0, 0, (BlendAnimation**)&self->aimAnim6);
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend7, 0, 0, 0, (BlendAnimation**)&self->aimAnim7);
    BaseObject* o = (BaseObject*)self->f243C;
    if (o != 0) {
        o->desc->m02(o);
        BuildTexturePackets((TextureRenderObject*)(self->f243C), self->rangeRecord);
    }
    self->ownOnOffObject = (OnOffObject*)CreateTypedRecord(0x63, self->world, 0, 0x316, -1);
    ResetPlayerOnOffObject(self);
    CreateEightEntryBlend(self, (BlendSlot*)self->eightWaySlots, &self->eightWayBlend);
    ResolvePlayerTableObjects(self);
    ((void (*)(Player*, void*, s32))((void**)self->desc)[0xE0 / 4])(self, self->stateNodes[0], 1);
    SetPlayerState(self, 0, -1);
    self->cameraHeight = self->v140.z - 75.0f;
    SetTurningColliderGravityScale(self, g_playerGravityScale);
    SetColliderMass(self, g_playerMass);
    Collider* c = (Collider*)self->f25D8[0];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->f25D8[2];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->f25D8[1];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->f25D8[3];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->f25D8[4];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
        if (((PlacedObject*)self->f25D8[4])->linkRecord == 0) {
            ((PlacedObject*)self->f25D8[4])->linkRecord = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);
        }
        *(s32*)((u8*)((PlacedObject*)self->f25D8[4])->linkRecord + 0xB0) |= 8;
        *(s32*)((u8*)((PlacedObject*)self->f25D8[4])->linkRecord + 0x60) = 0;
    }
    if (self->stateNodes[8] == 0) {
        self->stateNodes[8] = self->stateNodes[2];
    }
    self->selfPoseSource = CreatePoseSource(self->world, self, (const T2195_Vt*)g_snapshotPoseSourceMethods);
    InsertAttachment(self, (Attachment*)self->selfPoseSource);
    self->f251C = CreatePoseSource(self->world, (PlacedObject*)self->f61C, (const T2195_Vt*)g_snapshotPoseSourceMethods);
    *(s32*)(self->f251C + 0x14) = 5;
    InsertAttachment((PlacedObject*)self->f61C, (Attachment*)(self->f251C));
    self->f2520 = CreatePoseSource(self->world, (PlacedObject*)(self->f23D0), (const T2195_Vt*)g_snapshotPoseSourceMethods);
    *(s32*)(self->f2520 + 0x14) = 5;
    InsertAttachment((PlacedObject*)(self->f23D0), (Attachment*)(self->f2520));
    self->flags &= ~(u64)0x0C000000;
    self->flags &= ~(u64)0x30000000;
    BuildCombinedBlendAnimation(self, 12, 3, (u8*)&self->pathLeanRight, 0, 0, 0, (BlendAnimation**)&self->pathLeanBlend);
    self->pathLeanCentre = 1.0f;
    if (self->pathLeanBlend != 0) {
        SetBlendItemWeights((BlendAnimationView*)(self->pathLeanBlend), 12, 3, (u8*)&self->pathLeanRight);
    }
    void* q = self->f2490;
    if (q != 0) {
        *(s32*)((u8*)q + 0x2F0) = 2;
    }
}

#undef PS

// x + t (y + t z) of a curve's three coefficients.
static inline f32 EvalCurve3(const f32* c, f32 t) { return c[0] + t * (c[1] + t * c[2]); }

extern f32 g_gameClock[];

f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
f32 ApproachValueClampingVelocity(f32 x, f32 v, f32 target, f32 dt, void* params, f32* outv);
void AddColliderTorque(void* self, Vec02* torque);
void AddColliderForce(void* self, void* force);

// a blended toward b by t.
static inline f32 BlendRamp(f32 t, f32 a, f32 b)
{
    return (1.0f - t) * a + t * b;
}

// m turned so that its z axis lies along to: the angle between them, the axis in axis, the
// turn about it in turn, and m's rows each rotated by the turn into out (the rows kept in
// vector locals and a matrix local, MulRotationRowsIndexed's form with each row stored by
// Vu0::Set). m's rows are read through one pointer to them, a variable of the inline set
// before the first call: an inline's own pointer variable has no pointer flag, so its rows 1
// and 2 have no alias base and wait for the stores of the row before, as retail's do; a pointer
// of the caller, or the address of m written at each read, is flagged (or folds into the
// object's offset) and its loads move to the top (docs/TOOLCHAIN.md, "A rotation product's
// rows read after the stores"). Q's reference return would leave an address pseudo for each
// row local that GCSE reuses for a later local at the same frame offset (a saved register).
static inline f32 TiltRotation(Mat02* out, Mat02* turn, const Mat02& m, const Vec02& to, Vec02* axis)
{
    const u128* q = (const u128*)&m;
    f32 angle = ComputeAngleBetweenVectors((Vec02*)((const Vec02*)&q[2]), (Vec02*)&to, axis);
    BuildAxisAngleMatrix((const Vec02*)axis, (Mat02*)turn, angle);
    const u128* p = (const u128*)turn;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Set(x, Vu0::RotateRows(a0, a1, a2, q[0]));
    r.r[0] = x;
    Vu0::Set(y, Vu0::RotateRows(a0, a1, a2, q[1]));
    r.r[1] = y;
    u128 w = Vu0::RotateRows(a0, a1, a2, q[2]);
    Vu0::Set(r.r[2], w);
    Vu0::Set(z, w);
    *out = r;
    return angle;
}

// The player's upright torque: the ramp profile blended by the ground speed and scaled by 0x634
// (D_00263740 alone off the ground), the tilt and the heading to the goal matrix 0x660, the
// two speeds ApproachValueClampingVelocity gives, the torque that reaches them in one step,
// and the pull to the pivot. The two speeds are scalars whose addresses are passed, so they
// live in the frame's last slots (put there after every local); an array of two would be a
// local below the product's locals.
void ApplyPlayerDefaultSteering(Player* self)
{
    Vec02 axis;
    Vec02 axis2;
    Vec02 along;
    Vec02 rest;
    Vec02 spin;
    Vec02 torque;
    Mat02 turn;
    Mat02 rot;
    RampProfile ramp;
    f32 tiltSpeed;
    f32 headingSpeed;

    if (self->state == 1) {
        f32 v = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v150), Vu0::Q(self->v150))));
        f32 t = g_unitRange.Limit(EvalCurve3(g_steeringBlendBySpeedCurve, v));
        ramp.maxSpeed = BlendRamp(t, g_steeringRampProfileSlow.maxSpeed, g_steeringRampProfileFast.maxSpeed);
        ramp.endSpeed = BlendRamp(t, g_steeringRampProfileSlow.endSpeed, g_steeringRampProfileFast.endSpeed);
        ramp.rampTime = BlendRamp(t, g_steeringRampProfileSlow.rampTime, g_steeringRampProfileFast.rampTime);
        ramp.maxAccel = BlendRamp(t, g_steeringRampProfileSlow.maxAccel, g_steeringRampProfileFast.maxAccel);
        f32 k = self->stickLevel;
        t = g_unitRange.Limit(EvalCurve3(g_steeringBlendByLeanCurve, k));
        ramp.maxSpeed *= t;
        ramp.endSpeed *= t;
    } else {
        ramp = g_steeringRampProfileSlow;
    }
    Mat02* goal = &self->headingMatrix;
    f32 tilt = TiltRotation(&rot, &turn, self->rot, goal->r[2], &axis);
    f32 heading = ComputeAngleBetweenVectors(&rot.r[0], &goal->r[0], &axis2);
    u128 up = Vu0::Q(goal->r[2]);
    if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(axis2), up)) < 0.0f) {
        heading = -heading;
    }
    Vu0::Q(axis2) = up;
    f32 w = SplitVectorAlongAxis(&self->v160, &axis, &along, &rest);
    f32 w2 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(rest), Vu0::Q(axis2)));
    ApproachValueClampingVelocity(0.0f, w, tilt, g_gameClock[2], &g_playerTiltRampProfile, &tiltSpeed);
    ApproachValueClampingVelocity(0.0f, w2, heading, g_gameClock[2], &ramp, &headingSpeed);
    f32 dt = g_gameClock[2];
    Vu0::Q(spin) = Vu0::MulXSum(Vu0::Q(axis), Vu0::ScalarAt(tiltSpeed), Vu0::Q(axis2), Vu0::ScalarAt(headingSpeed));
    Vu0::Q(torque) = Vu0::MulXSum(Vu0::Q(spin), Vu0::Scalar(1.0f / dt), Vu0::Q(self->v160), Vu0::Scalar(-1.0f / dt));
    AddColliderTorque(self, &torque);
    {
        Vec02* pivot;
        if (self->groundContact != 0) {
            pivot = &self->groundContactPoint;
        } else {
            pivot = (Vec02*)self->probeVertex;
        }
        Vec02 arm;
        Vec02 v;
        Vec02 u;
        Vu0::Q(arm) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*pivot));
        Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v180), Vu0::Q(arm));
        AddColliderForce(self, &v);
        Vu0::Q(u) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(arm));
        Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(u));
        AddColliderForce(self, &v);
    }
}

void StepCollider(Collider* self, f32 t);
void ApplyPlayerDefaultSteering(Player* self);
void StepPlayerState2(Player* self);
void TurnPlayerTowardLinkedObject(Player* self);
void StepPlayerOnPath(Player* self);
void StepPlayerRequestState(Player* self);
void StepPlayerAlongTarget(Player* self);
void ComputePolarOffset(Vec3* out, f32 unused, f32 scale, f32 z);
void *StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
s128 ScaleQuadword(s128 a, s128 b);
void* StoreQuadword(u128* out, u128 v);
void SteerColliderTowardRotation(Collider* self, Mat02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
void SteerColliderTowardPosition(Collider* self, Vec02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain);

// Stores v as the direction at dir and steers the player toward the offset along it. Both
// addresses are the inline's parameters, so each call forms its frame address again where
// retail does (addiu in each call's delay slot); written at the call sites, CSE keeps the one
// address in a saved register (docs/TOOLCHAIN.md, "A frame address passed by an inline call
// is not GCSE's").
static inline void SteerAlongDirection(Player* self, Vec02* off, Vec02* dir, s128 v, f32 t)
{
    StoreQuadword((u128*)dir, v);
    SteerColliderTowardRotation(self, 0, 0, off, (f32*)dir, t);
}

void StepPlayer(Player* self, f32 t)
{
    Mat02 m;
    s128 qa;
    s128 a;
    s128 b;
    StepCollider(self, t);
    switch (self->state) {
    case 2:
        StepPlayerState2(self);
        break;
    case 3:
        TurnPlayerTowardLinkedObject(self);
        break;
    case 7:
        StepPlayerOnPath(self);
        break;
    case 4:
        StepPlayerRequestState(self);
        break;
    case 6:
        StepPlayerAlongTarget(self);
        break;
    case 13:
        switch (self->subState) {
        case 0x38:
            BuildAxisAngleMatrix((const Vec02*)&g_unitZVector, (Mat02*)&m, self->heading);
            TurnColliderTowardRotation(self, g_frameDt[0], &m, g_turnTowardRotationRates);
            break;
        case 0x36:
        case 0x37: {
            ComputePolarOffset((Vec3*)&m.r[0], self->heading + 1.5707964f, self->stickLevel * D_00262E28 / self->radius3CC, 0.0f);
            u8* table = (u8*)D_00263790;
            StoreFloatAsQuadword((u128*)&a, self->stickLevel);
            qa = a;
            CopyQuadword((u128*)&b, table);
            s128 prod = ScaleQuadword(qa, b);
            SteerAlongDirection(self, &m.r[0], &m.r[1], prod, t);
            break;
        }
        }
        break;
    case 9:
        if (g_gameClock[1] - self->stateStartTime > 0.25f) {
            Vu0::Q(m.r[1]) = Vu0::FromFloat(-1.0f);
            Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Q(m.r[1]));
            AddColliderForce(self, &m.r[0]);
            SteerColliderTowardPosition(self, 0, 0, (Vec02*)&D_00248D30, D_002637A0, t);
            TurnColliderTowardRotation(self, g_gameClock[2], &self->headingMatrix, &self->turnGain);
        } else {
            ApplyPlayerDefaultSteering(self);
        }
        break;
    default:
        ApplyPlayerDefaultSteering(self);
        break;
    case 11:
        break;
    }
}


void ComputePlayerSlideRates(Player* self, Contact03* out)
{
    f32 a;
    f32 b;
    if (self->state == 0xD) {
        a = g_slideRateFirst;
        b = g_slideRateSecond;
    } else if (self->state == 7) {
        goto zero_both;
    } else if (((VFn_170410*)self->desc)[90](self, out) != 0) {
        if (self->state == 6 && self->targetMode == 4 && ((PathRecord*)self->targetTrack)->isRail != 0) {
            goto zero_both;
        }
        a = D_002637B8;
        out->bounce = 0.0f;
        out->friction = a;
        goto divide;
    } else {
        if (self->state != 4) {
            goto zero_both;
        }
        s32 v = self->subState;
        if (v == 0x28 || v == 0x31) {
            a = D_002637B0;
            out->bounce = 0.0f;
            out->friction = a;
            goto divide;
        }
        a = D_002637B0;
        b = D_002637B4;
    }
    out->friction = a;
    out->bounce = b;
    goto divide;
zero_both:
    out->friction = 0.0f;
    out->bounce = 0.0f;
divide:
    out->friction = out->friction / self->gravityScale;
}
extern f32 D_002637C0[3];

void ClampColliderContactLimit(Collider* self, s32 flags, ContactLimit03* limit);

void ClampPlayerContactLimit(Player* self, s32 flags, ContactLimit03* out)
{
    if (self->state == 4) {
        if (flags & 0x10) {
            f32 v;
            if (flags & 1) {
                v = -self->mass * self->gravity.z * g_frameDt[0] * D_002637BC;
            } else {
                v = -self->mass * self->gravity.z * D_002637C0[0];
            }
            if (v < out->limit) {
                out->limit = v;
            }
        }
    } else {
        ClampColliderContactLimit(self, flags, out);
    }
}

void SetPlayerState(Player* self, s32 state, s32 sub);
void SetPlayerAimMode(Player* self, s32 state);
void ComputeObjectSteeringHeading(f32 a, f32 b, PlacedObject* self, f32* p1, f32* p3, f32* out0, f32* out1, f32* out2);
void RunPlayerCallback(Player* self);

void ApplyPendingPlayerStateRequest(Player* self)
{
    s32 flags = self->pendingFlags;
    if (flags == 0) {
        return;
    }
    if (flags & 8) {
        self->pendingFlags = flags & ~8;
        self->jumpKind = self->pendingJumpKind;
    }
    if (self->pendingFlags & 1) {
        SetPlayerState(self, self->pendingState, self->pendingSubState);
    }
    if (self->pendingFlags & 2) {
        SetPlayerAimMode(self, self->pendingAimMode);
    }
    if (self->pendingFlags & 0x10) {
        RunPlayerCallback(self);
    }
}

void FreePooledContactChain(World* world, Contact03* head);
void PinPlayerToPath(Player* self);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void PinPlayerToTarget(Player* self);
void BuildPerpendicularPair(Vec02* dir, Vec02* out, const Vec02* a, const Vec02* b);
void AddPlayerObjectContacts(Player* self, s32 flags, BaseObject* node, Vec02* origin, Vec02* axis, Vec02* offset);
void ReleasePlayerContacts(Player* self)
{
    FreePooledContactChain((World*)self->world, self->contacts4B4);
    self->contacts4B4 = 0;
    switch (self->state) {
    case 7:
        PinPlayerToPath(self);
        break;
    case 6:
        PinPlayerToTarget(self);
        break;
    case 8: {
        Vec02 pos;
        Mat02 m;
        Vec02 k;
        TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec02*)self->ledgeLocalPoint, &pos);
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->ledgeOffset), Vu0::Q(k));
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(self->ledgeSlack));
        BuildPerpendicularPair(&m.r[0], &m.r[1], &g_unitZVector, &g_unitZVector);
        Vu0::Q(pos) = Vu0::Sub(Vu0::Q(pos), Vu0::Rotate(m, Vu0::Q(self->ledgeHandOffset)));
        AddPlayerObjectContacts(self, 7, (BaseObject*)self->ledgeCollider, &pos, 0, &self->v140);
        break;
    }
    }
}

extern f32 g_contactSideSigns[];

s32 IsTurningColliderGroundContact(TurningCollider* self, Contact03* a, s32 idx);

s32 IsPlayerGroundContact(Player* self, Contact03* e, s32 idx)
{
    if (self->state != 0xD) {
        return IsTurningColliderGroundContact(self, e, idx);
    }
    f32 scale = g_contactSideSigns[idx];
    if (e->normal.z * scale < 0.7f) {
        return 0;
    }
    s32 k = e->kind;
    if (k < 7) {
        if (k >= 4) {
            return idx == 0;
        }
    }
    return 0;
}

void ResolveTurningColliderGroundContact(TurningCollider* self, Contact03* c, s32 idx);

void ResolvePlayerContact(Player* self, Contact03* c, s32 idx)
{
    ContactEnd03* e = &c->end[idx];
    if (self->state == 4) {
        if (c->kind == 1 && idx == 0 && (Vec02*)c->featureEnd0 == self->lowestVertex) {
            Vec02 t;
            u128 n = Vu0::Rotate(self->headingMatrix, Vu0::Q(self->headingVelocity));
            Vu0::Q(t) = Vu0::Sub(n, Vu0::MulX(Vu0::Q(c->normal), Vu0::Dot(n, Vu0::Q(c->normal))));
            Vu0::Q(c->end[0].v30) = Vu0::Add(Vu0::Q(c->end[0].v30), Vu0::Q(t));
        }
    } else if (self->state != 0xD) {
        if (((s32 (*)(Player*, Contact03*, s32))self->desc06()->m56)(self, c, idx)) {
            ResolveTurningColliderGroundContact(self, c, idx);
        } else if (e->part == (Collider*)self) {
            Vu0::Q(e->v30) = Vu0::Sub(Vu0::Q(e->v30), Vu0::Cross(Vu0::Q(self->v160), Vu0::Sub(Vu0::Q(e->point), Vu0::Q(self->v140))));
        }
    }
}

// An object the player was queued to (+0x2BE0, +0x26D4): its walker at +0x2D4, a walker handle at
// +0x2D8, and the list of the objects at +0x304 (count at +0x300) whose own walkers it sets.
struct WalkerHost { u8 pad00[0x140]; Vec02 v140; u8 pad150[0x2D0 - 0x150]; s32 levelFlag; void* walker; void* f2D8; u8 pad2DC[0x300 - 0x2DC]; s32 count; WalkerHost* list[1]; };
// What HandlePlayerNotification is handed: the sender first; then an object or a time; then an
// event code.
struct PlayerNotification {
    void* source;           // 0x00
    union {
        void* obj;          // 0x04
        f32 time;           // 0x04
    };
    s32 code;               // 0x08
};
// The animation player the notifications of kind 0x13 come from.
struct PlayerNoticePlayer {
    u8 pad00[0x08];
    Animation* anim;        // 0x08
    u8 pad0C[0x14 - 0x0C];
    f32 time;               // 0x14
    f32 speed;              // 0x18
};
// An effect CreateEffect hands back: its set-up slot, then the times and objects it follows.
struct PlayerNoticeEffect;
struct PlayerNoticeEffectVt {
    void (*m00)(PlayerNoticeEffect* self, void* pos, f32 scale, s32 flags);
};
struct PlayerNoticeEffect {
    const PlayerNoticeEffectVt* vt; // 0x00
    u8 pad04[0x18 - 0x04];
    f32 start;              // 0x18
    f32 life;               // 0x1C
    void* p20;              // 0x20
    u8 pad24[0xC0 - 0x24];
    Vec02 vC0;              // 0xC0
    u8 padD0[0x134 - 0xD0];
    void* p134;             // 0x134
};
PlayerNoticeEffect* CreateEffect(s32 kind, EffectOwner* sys);
void AddEffectListener(void* obj, void* arg);
f32 GetAnimationMarkerTime(Animation* self, s32 key);
f32* FindAnimationMarkerEvent(Animation* anim, s32 key);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void ReleasePlayerToState2(Player* self);
void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg);
extern f32 D_002637CC;
extern s32 D_002637D0;
extern s32 D_002637D4;
extern f32 g_gameClock[];

static inline s32 MinOfCounts(s32 a, s32 b)
{
    return a < b ? a : b;
}

void HandlePlayerNotification(Player* self, s32 kind, PlayerNotification* msg)
{
    HandleSwitchedColliderNotification(self, kind, msg);
    switch (kind) {
    case 5:
        if ((void*)msg == self->aimAnimPlayer) {
            self->pendingFlags |= 2;
            if (self->aimMode == 10) {
                self->pendingAimMode = 2;
            } else {
                self->pendingAimMode = -1;
            }
        } else if ((void*)msg == self->stateAnimPlayer) {
            switch (self->state) {
            case 7:
                if (self->subState == 0x1B || self->subState == 0x17) {
                    self->pendingState = 7;
                    self->pendingSubState = 0x18;
                    self->pendingFlags |= 1;
                }
                break;
            case 2:
                if (self->subState != 7) {
                    if (self->subState != 8) {
                        break;
                    }
                }
                self->pendingState = 2;
                self->pendingSubState = 2;
                self->pendingFlags |= 1;
                break;
            case 0xC:
                if (self->subState == 0x21) {
                    self->pendingState = 0xC;
                    self->pendingSubState = 0x22;
                    self->pendingFlags |= 1;
                    break;
                }
                if (self->subState != 0x23) {
                    break;
                }
            case 9:
            case 0xA:
            case 0xE:
            case 0xF:
            case 0x10:
                self->pendingSubState = -1;
                self->pendingState = 0;
                self->pendingFlags |= 1;
                break;
            case 4:
                self->pendingFlags |= 0x10;
                break;
            }
        }
        break;
    case 7:
        if ((void*)msg == self->stateAnimPlayer) {
            switch (self->state) {
            case 5:
            case 6:
                self->eightWayHalf = -1;
                break;
            }
        }
        break;
    case 0x13: {
        PlayerNoticePlayer* src = (PlayerNoticePlayer*)msg->source;
        if (src != (void*)self->stateAnimPlayer && src != self->aimAnimPlayer) {
            void* other = self->stateWalker;
            if (other == 0 || src != *(void**)((u8*)other + 0x24)) {
                break;
            }
        }
        switch (msg->code) {
        case 0x138: {
            Vec02 v;
            Track83* track = src->anim->movedTrack;
            if (track == 0) {
                break;
            }
            PositionCurve* c = track->pos;
            c->vt->eval(c, self, src->time, src->speed, 0, 0, &v);
            Vu0::Q(v) = Vu0::Rotate(self->headingMatrix, Vu0::Q(v));
            self->desc02()->m20(self, &v);
            if (src == (void*)self->stateAnimPlayer) {
                Vec02 w;
                u128 s = Vu0::FromFloat(-1.0f);
                Vu0::Q(self->headingVelocity) = Vu0::MulX(Vu0::Q(v), s);
                Vu0::Q(w) = s;
            }
            break;
        }
        case 0x13C:
            if (self->subState == 8) {
                self->spinTargetRate = (f32)D_002637D4;
            } else {
                self->spinTargetRate = (f32)D_002637D0;
            }
            break;
        case 0x13D:
            self->spinTargetRate = 0;
            break;
        case 0x13A:
            self->holdFocus = 1;
            break;
        case 0x13B:
            Vu0::Q(self->poseOffset) = Vu0::Sub(Vu0::Q(self->focusPoint), Vu0::Q(self->pos));
            self->holdFocus = 0;
            self->poseOffset.z = 0.0f;
            break;
        case 0x13E: {
            f32 left = GetAnimationMarkerTime(((PlayerNoticePlayer*)self->stateAnimPlayer)->anim, 0x140) - msg->time;
            self->effectCount = 0;
            s32 most = g_currentLevelRecord->f438;
            s32 count = ((WalkerHost*)self->walkerHost)->count;
            s32 n = MinOfCounts(count, most);
            for (s32 i = 0; i < n; i++) {
                WalkerHost* h = ((WalkerHost*)self->walkerHost)->list[i];
                PlayerNoticeEffect* fx = CreateEffect(0x1A, 0);
                self->effects[self->effectCount++] = fx;
                if (fx != 0) {
                    f32 nearest = 300.0f;
                    fx->vt->m00(fx, (u8*)self->f59C + 0x140, D_002637CC, 0);
                    AddEffectListener(fx, self);
                    PlacedObject* to = (PlacedObject*)h->f2D8;
                    f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(to->v140), Vu0::Q(((PlacedObject*)self->f59C)->v140))));
                    fx->p20 = to;
                    d = nearest >? d;
                    fx->life = left <? (d * 0.00055555557f);
                    fx->vC0 = g_currentWorld->gravity;
                    fx->p134 = (void*)self->f59C;
                }
            }
            break;
        }
        case 0x140: {
            s32 i;
            for (i = 0; i < ((WalkerHost*)self->walkerHost)->count; i++) {
                WalkerHost* h = ((WalkerHost*)self->walkerHost)->list[i];
                s32 most = g_currentLevelRecord->f438;
                if (i < most) {
                    if (!(most < ((WalkerHost*)self->walkerHost)->count)) {
                        SetStateWalkerTarget((StateWalker*)h->walker, 0x22F);
                    } else {
                        SetStateWalkerTarget((StateWalker*)h->walker, 0x230);
                    }
                } else {
                    SetStateWalkerTarget((StateWalker*)h->walker, 0x231);
                }
            }
            if (!(g_currentLevelRecord->f438 < ((WalkerHost*)self->walkerHost)->count)) {
                SetStateWalkerTarget((StateWalker*)(((WalkerHost*)self->walkerHost)->f2D8), 0x22F);
                g_currentLevelRecord->f448 |= ((WalkerHost*)self->walkerHost)->levelFlag;
            } else {
                SetStateWalkerTarget((StateWalker*)(((WalkerHost*)self->walkerHost)->f2D8), 0x230);
            }
            f32* e = FindAnimationMarkerEvent(((PlayerNoticePlayer*)self->stateAnimPlayer)->anim, 0x13F);
            if (e == 0) {
                break;
            }
            f32 left = e[0] - ((PlayerNoticePlayer*)self->stateAnimPlayer)->time;
            self->effectCount = 0;
            s32 most = g_currentLevelRecord->f438;
            s32 count = ((WalkerHost*)self->walkerHost)->count;
            s32 n = MinOfCounts(count, most);
            for (i = 0; i < n; i++) {
                WalkerHost* h = ((WalkerHost*)self->walkerHost)->list[i];
                PlayerNoticeEffect* fx = CreateEffect(0x1A, 0);
                self->effects[self->effectCount++] = fx;
                if (fx != 0) {
                    f32 nearest = 300.0f;
                    fx->vt->m00(fx, (u8*)h->f2D8 + 0x140, 1.0f / D_002637CC, 0);
                    AddEffectListener(fx, self);
                    f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(((PlacedObject*)h->f2D8)->v140), Vu0::Q(((PlacedObject*)self->f59C)->v140))));
                    fx->p20 = (void*)self->f59C;
                    d = nearest >? d;
                    f32 life = left <? (d * 0.0016666667f);
                    fx->life = life;
                    fx->vC0 = g_currentWorld->gravity;
                    fx->p134 = h->f2D8;
                    fx->start = g_gameClock[1] + (left - life);
                }
            }
            break;
        }
        case 0x15E:
            self->f2738 = 1;
            break;
        case 0x15F:
            self->f2738 = 0;
            break;
        case 0x144:
            self->pendingFlags |= 0x10;
            break;
        case 0x143:
            self->f2248 = 1;
            break;
        }
        break;
    }
    case 0xA:
        if (msg->obj == self) {
            self->f2438 = (Collider*)msg->source;
            for (u32 k = 0; k < 8; k++) {
                self->hitStamps[k].time = 0;
            }
        }
        break;
    case 0xB:
        if (msg->obj == self && msg->source == self->f2438) {
            self->f2438 = 0;
        }
        break;
    case 2: {
        void* held;
        switch (self->state) {
        case 3:
            held = (void*)self->boundObject;
            goto check;
        case 7:
            held = (void*)self->aimCurve;
            goto check;
        case 6:
            if (self->targetMode == 4) {
                goto pushed;
            }
            if (self->targetMode != 5) {
                break;
            }
            held = self->targetNode;
        check:
            if (held == (void*)msg) {
                ReleasePlayerToState2(self);
            }
            break;
        pushed:
            if (self->targetTrack == (void*)msg) {
                ReleasePlayerToState2(self);
            }
            break;
        }
        break;
    }
    }
}
#undef PS

struct PoseHolder47;
struct PoseHolderDesc { u8 pad00[8]; void (*m2)(PoseHolder47* self, Vec02* out, f32 t, s32 a); };
struct PoseHolder47 { PoseHolderDesc* desc; };
// The object at 0x2208: a frame at +0x18 and a holder of poses at +0x34.
struct PoseTarget { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PoseHolder47* holder; };
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

s32 AimPlayerAtTarget(Player* self)
{
    Vec02 pos;
    Vec02 d1;
    Vec02 d2;
    f32 y;
    f32 x;
    if (self->aimTarget != 0) {
        GetObjectWorldPosition((BaseObject*)self->aimTarget, &pos);
        Vu0::Q(d1) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        y = d1.y;
        x = d1.x;
    } else if (self->aimCurve != 0) {
        PoseHolder47* h = ((PoseTarget*)self->aimCurve)->holder;
        if (h->desc->m2 != 0) {
            h->desc->m2(h, &pos, self->aimCurvePos, 0);
        }
        TransformPointBetweenFrames((PlacedObject*)(((PoseTarget*)self->aimCurve)->frame), 0, &pos, &d1);
        Vu0::Q(d2) = Vu0::Sub(Vu0::Q(d1), Vu0::Q(self->v140));
        y = d2.y;
        x = d2.x;
    } else {
        return 0;
    }
    self->heading = ArctangentOfRatio(y, x);
    return 1;
}

// A part of the player's model as func_00171238 poses it: its state (0x10) and the state asked
// for (0x11), its offset and its rotation (BuildEulerRotationMatrix).
struct PosedPart { u8 pad00[0x10]; s8 state; s8 next; u8 pad12[0x20 - 0x12]; Vec02 offset; u8 pad30[0x40 - 0x30]; Mat02 rotation; };

void BuildEulerRotationMatrix(f32* in, f32* out);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
f32 WrapModulo(f32 x, f32 m);
f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
f32 ApproachValueClampingVelocity(f32 x, f32 v, f32 target, f32 dt, void* params, f32* outv);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
void TransformPointAtTime(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);

// The smaller of two floats (min.s; through an inline function the result takes b's register).
static inline f32 MinF(f32 a, f32 b) { return a <? b; }

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

// The direction of a path curve at t (its slot 2, when it has one) turned from the curve's frame
// into the world. The address of the result is the inline's argument, formed at each call.
static inline void SampleCurveDirection(PathCurve* c, PlacedObject* frame, f32 t, Vec02* dir)
{
    if (c->vt->m02 != 0)
        ((void (*)(PathCurve*, f32, s32, Vec02*))c->vt->m02)(c, t, 0, dir);
    TransformDirectionBetweenFrames(frame, 0, dir, dir);
}

void PosePlayerTargetPart(Player* self)
{
    s32 mode;
    if (self->state == 6 && self->targetMode == 4 && self->subState == 0x10 && (u32)(self->aimMode - 4) < 2) {
        void* angles;
        mode = 2;
        if (((PathRecord*)self->targetTrack)->isRail != 0) {
            Vu0::Q(((PosedPart*)self->rigPoseSource)->offset) = Vu0::Q(*(Vec02*)D_00263820);
            angles = D_00263830;
        } else {
            Vec02 d;
            Mat02 m;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PosedPart*)self->footPartA)->offset), Vu0::Q(((PosedPart*)self->footPartB)->offset));
            f32 angle = D_00263850 * ArctangentOfRatio(d.z, D_00263854);
            BuildAxisAngleMatrix((const Vec02*)&g_unitYVector, (Mat02*)&m, angle);
            Vu0::Q(((PosedPart*)self->rigPoseSource)->offset) = Vu0::Add(Vu0::Q(*(Vec02*)D_00263840), Vu0::Rotate(m, Vu0::Sub(Vu0::Q(*(Vec02*)D_00263800), Vu0::Q(*(Vec02*)D_00263840))));
            angles = D_00263810;
        }
        BuildEulerRotationMatrix((f32*)angles, (f32*)(&((PosedPart*)self->rigPoseSource)->rotation));
    } else {
        mode = -1;
    }
    PosedPart* part = (PosedPart*)self->rigPoseSource;
    if (part->state != mode) {
        part->next = mode;
        s32 n = ((PosedPart*)self->rigPoseSource)->next;
        part->state = n;
        ((const Desc02*)self->rigObject->desc)->m2B(self->rigObject);
    }
    Vec02 rest;
    Vec02 pos;
    Vec02 vel;
    Vec02 along;
    Vec02 side;
    Vec02 k;
    Vec02 push;
    Vu0::Q(rest) = Vu0::Q(D_00248D30);
    PlacedObject* frame = 0;
    Vec02* at = 0;
    PosedPart* lead = (PosedPart*)self->f2500;
    if (lead == 0 || lead->state == -1)
        return;
    switch (self->state) {
    case 0:
        if (self->groundContact != 0) {
            frame = (PlacedObject*)self->groundContactPart;
            at = &self->groundContactPoint;
        }
        break;
    case 6:
        if (self->subState == 0x10) {
            switch (self->targetMode) {
            case 5: {
                PathRecord* rec = (PathRecord*)self->targetNode;
                frame = rec->frame;
                ConvertPositionToWorld((BaseObject*)rec, &pos);
                at = &pos;
                break;
            }
            case 4: {
                PathRecord* rec = (PathRecord*)self->targetTrack;
                PathCurve* c = rec->curve;
                frame = rec->frame;
                if (c->vt->m01 != 0)
                    ((void (*)(PathCurve*, f32, Vec02*, Vec02*))c->vt->m01)(c, self->trackPos, &pos, &vel);
                TransformPointBetweenFrames(frame, 0, &pos, &pos);
                at = &pos;
                if (((PathRecord*)self->targetTrack)->isRail != 0) {
                    Vu0::Q(vel) = Vu0::DivX(Vu0::Q(vel), Vu0::Length(Vu0::Q(vel)));
                    f32 speed = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v150), Vu0::Q(vel)));
                    Vu0::Q(k) = Vu0::FromFloat(speed);
                    Vu0::Q(along) = Vu0::MulX(Vu0::Q(vel), Vu0::Q(k));
                    f32 t = self->f23C4 + speed * g_motionLookaheadTime;
                    f32 len = c->vt->m08(c);
                    if (c->wrap != 0) {
                        t = WrapModulo(t, len);
                    } else {
                        f32 lo = *c->lengths;
                        if (t < lo)
                            t = lo;
                        else if (len < t)
                            t = len;
                    }
                    SampleCurveDirection(c, frame, t, &vel);
                    *(u128*)&k = Vu0::FromFloat(speed);
                    Vu0::Q(side) = Vu0::MulX(Vu0::DivX(Vu0::Q(vel), Vu0::Length(Vu0::Q(vel))), *(const u128*)&k);
                    Vu0::Q(rest) = Vu0::Sub(Vu0::Q(side), Vu0::Q(along));
                    if (self->pathLeanBlend != 0) {
                        u128 n = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(vel));
                        Vu0::Q(k) = Vu0::DivX(n, Vu0::Length(n));
                        f32 turn = ClampBetween(SplitVectorAlongAxis(&rest, &k, 0, &rest) / g_followPullRange, -1.0f, 1.0f);
                        if (self->trackReversed != 0)
                            turn = -turn;
                        f32 r = ApproachValueClampingVelocity(self->pathLean, self->pathLeanRate, turn * (2.0f - __builtin_fabsf(turn)), g_frameDt[0], g_hookTurnRamp, &self->pathLeanRate);
                        self->pathLean = r;
                        f32 a = r >? 0.0f;
                        f32 b = -r >? 0.0f;
                        self->pathLeanRight = a;
                        self->pathLeanLeft = b;
                        self->pathLeanCentre = 1.0f - a - b;
                        SetBlendItemWeights((BlendAnimationView*)self->pathLeanBlend, 0xC, 3, &self->pathLeanRight);
                    }
                    goto motion;
                }
                break;
            }
            }
        }
        break;
    }
    if (frame == 0)
        return;
motion:
    ComputeObjectMotionInFrame(frame, 0, at, &vel, 0, 0, 0);
    TransformPointBetweenFrames(0, (PlacedObject*)frame, at, &along);
    Vu0::Q(side) = Vu0::Zero();
    TransformPointAtTime(frame, 0, &along, 0, &side, 0, g_motionLookaheadTime);
    Vu0::Q(k) = Vu0::DivX(Vu0::Sub(Vu0::Add(Vu0::Q(rest), Vu0::Q(side)), Vu0::Q(vel)), Vu0::ScalarAt(g_motionLookaheadTime));
    f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(k), Vu0::Q(k))));
    if (0.0001f < dist) {
        f32 g = EvalCurve3(g_followPullCurve, MinF(1.0f, dist / g_followPullRange));
        f32 lo = g_unitRange.lo;
        f32 hi = g_unitRange.hi;
        if (g < lo)
            g = lo;
        else if (hi < g)
            g = hi;
        Vu0::Q(k) = Vu0::RotateTransposed(self->headingMatrix, Vu0::Q(k));
        Vu0::Q(push) = Vu0::FromFloats(k.x * D_002637E0 * g / dist, k.y * D_002637E0 * g / dist, D_002637E4 * g);
    } else {
        Vu0::Q(push) = Vu0::Q(D_00248D30);
    }
    Vu0::Q(((PosedPart*)self->f2500)->offset) = Vu0::Q(push);
    f32 e1 = EvalCurve3(D_00263870, ((PosedPart*)self->footPartA)->offset.z);
    f32 e2 = EvalCurve3(D_00263870, ((PosedPart*)self->footPartB)->offset.z);
    f32 z;
    if (push.z < e1)
        z = e2 <? push.z;
    else
        z = e2 <? e1;
    ((PosedPart*)self->f2500)->offset.z = z;
    if (self->aimMode == -1) {
        u128 s = Vu0::MulX(Vu0::Q(push), Vu0::ScalarAt(D_002637E8[0]));
        Vu0::Q(((PosedPart*)self->f2504)->offset) = s;
        Vu0::Q(((PosedPart*)self->f2508)->offset) = s;
    } else {
        ((PosedPart*)self->f2508)->offset = ((PosedPart*)self->f2504)->offset = D_00248D30;
    }
}

// The record of a probe the player keeps for each of its two parts (+0x1190, +0x1290):
// func_001719E8 fills it (the animation it was measured for, whether the segment hit, the probe
// radius, the part's position, the probe's start and the segment's ends) and func_00171C80 reads
// it back for the block of the part.
struct ProbeRecord { Animation* animation; s32 hit; f32 radius; u8 pad0C[4]; Vec02 v10; Vec02 v20; Vec02 v30; Vec02 v40; };
// The node the player's state selects, the holder of the part's body and the body's two extents.
struct ProbeNode { u8 pad00[8]; Animation* animation; };
struct ProbeNodeBase { u8 pad00[0x100]; Vec02 v100; };
struct ProbeBody { u8 pad00[0x60]; Vec02 v60; Vec02 v70; void* f80; ProbeNodeBase* f84; };
struct ProbeHolder { u8 pad00[0x224]; ProbeBody* body; };
s32 CollectBoundsSpans(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out);

void MeasurePlayerFootProbe(void* self, s32 a, s32 b, void* part, f32 k, void* d)
{
    Player* pl = (Player*)self;
    ProbeHolder* obj = (ProbeHolder*)b;
    ProbeRecord* rec = (ProbeRecord*)d;
    ProbeNode* node;
    if (pl->state == 0) {
        if (pl->aimMode < 10) {
            if (pl->aimMode < 6) {
                node = *(ProbeNode**)((u8*)pl->stateWalker + 0x24);
            } else {
                node = *(ProbeNode**)((u8*)pl + 0x2244);
            }
        } else {
            node = *(ProbeNode**)((u8*)pl->stateWalker + 0x24);
        }
    } else if (pl->stateWalker != 0) {
        node = *(ProbeNode**)((u8*)pl->stateWalker + 0x24);
    } else {
        node = (ProbeNode*)pl->stateAnimPlayer;
    }
    if (node->animation == rec->animation) {
        return;
    }
    rec->animation = node->animation;
    f32 x = 0.0f;
    f32* found = FindAnimationMarkerEvent(node->animation, 0x142);
    if (found != 0) {
        x = *found;
    }
    f32 y = 0.0f;
    Vec02 v0;
    Vec02 v10;
    Vec02 v20;
    Mat02 m30;
    Vec02 v60;
    Vec02 v70;
    ColliderSpan span;
    SampleAnimationFrameChain((BlendAnimationView*)node->animation, x, y, (PlacedObject*)a, (PlacedObject*)pl, 1, &v0, 0, 0, 0);
    ProbeBody* b1 = obj->body;
    v0.z = v0.z - k;
    SampleAnimationFrameChain((BlendAnimationView*)node->animation, x, y, (PlacedObject*)b1->f80, (PlacedObject*)pl, 1, &v10, 0, 0, 0);
    SampleAnimationFrameChain((BlendAnimationView*)node->animation, x, y, (PlacedObject*)obj, (PlacedObject*)pl, 1, &v20, &m30, 0, 0);
    *(Vu0::Vec*)&v20 = Vu0::Add(Vu0::Vec::Of(v20), Vu0::Rotate(m30, Vu0::Vec::Of(obj->body->v60)));
    *(Vu0::Vec*)&rec->v20 = Vu0::Add(Vu0::Vec::Of(v10), Vu0::Sub(Vu0::Vec::Of(v0), Vu0::Vec::Of(v20)));
    ProbeBody* body = obj->body;
    rec->radius = Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(body->f84->v100))) + Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(body->v70))) + 10.0f;
    Vu0::Vec up = Vu0::Vec::Of(g_unitZVector);
    *(Vu0::Vec*)&v60 = Vu0::MulAddX(Vu0::Vec::Of(v0), up, Vu0::Vec::ScalarAtValue(D_00263880));
    *(Vu0::Vec*)&v70 = Vu0::MulAddX(Vu0::Vec::Of(v0), up, Vu0::Vec::ScalarAtValue(D_00263884));
    rec->hit = 0 < CollectBoundsSpans(&rec->v20, &v60, &v70, rec->radius, 1, &span);
    rec->v10 = v0;
    rec->v30 = *(Vec02*)&span.q[0];
    rec->v40 = *(Vec02*)&span.q[1];
}

struct ProbeResult { u8 pad00[0x20]; Vec02 v20; };
s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);


s32 ProbePlayerFootGround(Player* self, void* record, void* part)
{
    ProbeRecord* p = (ProbeRecord*)record;
    ProbeResult* result = (ProbeResult*)part;
    if (p->hit == 0) {
        return 1;
    }
    PushBackMemoryMark();
    ColliderSpan span;
    Vec02 from;
    Vec02 to;
    Vec02 world;
    s32 count;
    Collider** list;
    TransformPointBetweenFrames(self, 0, &p->v30, &from);
    TransformPointBetweenFrames(self, 0, &p->v40, &to);
    GatherCollidersInBox(self->world, (Collider*)self->root, &from, &to, 0, 0, &count, &list);
    s32 found = FindNearestSpanObject(0, &from, &to, count, list, &span);
    PopBackMemoryMark();
    if (found != 0) {
        Vu0::Q(span.q[0]) = Vu0::Sub(Vu0::Q(span.q[0]), Vu0::Q(g_unitZVector));
        TransformPointBetweenFrames(0, (PlacedObject*)self, (Vec02*)&span, &world);
        Vu0::Q(result->v20) = Vu0::Sub(Vu0::Q(world), Vu0::Q(p->v10));
        return 1;
    }
    result->v20 = D_00248D30;
    if (self->groundContact != 0 && p->v40.z < -85.0f) {
        return 0;
    }
    return 1;
}

s32 AimPlayerAtTarget(void* self);

void MeasurePlayerFootProbe(void* self, s32 a, s32 b, void* part, f32 k, void* d);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
f32 ClampToMagnitude(f32 a, f32 b);
s32 FindStateEntryIndex(StateGraph* self, s32 key);
void TeleportStateWalker(StateWalker* self, s32 key);


void UpdatePlayerState0(Player* self)
{
    Vec3 loc;
    if (AimPlayerAtTarget(self) == 0) {
        if (self->groundContact != 0) {
            ComputeObjectMotionInFrame((PlacedObject*)self->groundContactPart, 0, &self->groundContactPoint, 0, (Vec02*)&loc, 0, 0);
            loc.z = ClampToMagnitude(loc.z, 10.0f);
            self->heading = self->heading + loc.z * g_frameDt[0];
        }
    }
    if (self->footPartA == 0) return;
    u8* p1 = (u8*)&self->f1190;
    f32 k = 5.0f;
    MeasurePlayerFootProbe(self, (s32)self->f628, (s32)self->f620, self->footPartA, k, p1);
    u8* p2 = (u8*)&self->f1290;
    MeasurePlayerFootProbe(self, (s32)self->f62C, (s32)self->f624, self->footPartB, k, p2);
    if (ProbePlayerFootGround(self, p1, self->footPartA) != 0) {
        if (ProbePlayerFootGround(self, p2, self->footPartB) != 0) return;
    }
    if (self->f118C != 0) return;
    if (self->stateGraph == 0) return;
    if (FindStateEntryIndex((StateGraph*)self->stateGraph, 0x148) >= 0) TeleportStateWalker((StateWalker*)self->stateWalker, 0x148);
    self->f118C = 1;
}

s32 ComputeBallisticLaunchVelocity(Vec02* from, Vec02* to, Vec02* out, u8* rec, f32 angle);

void PlacePlayerOnGround(Player* self, void* target, f32 angle, f32 scale)
{
    Vec02 tmp = self->v140;
    tmp.z = tmp.z - 75.0f;
    Vec02 out;
    ComputeBallisticLaunchVelocity(&tmp, (Vec02*)target, &out, (u8*)self, angle);
    self->desc02()->m20(self, &out);
    if (self->state != 4) {
        SetPlayerState(self, 2, 6);
        self->jumpSpeed = self->jumpSpeed * scale;
        if (scale == 0.0f) {
            self->f2498 = 0;
        }
    }
}

void ReleasePlayerToState2(Player* self)
{
    s32 st = self->state;
    if (st != 6) {
        if (st < 7) {
            if (st == 3) {
                goto act;
            }
        } else if (st == 7) {
            goto act;
        }
        return;
    act:
        self->jumpKind = 1;
        SetPlayerState(self, 2, 2);
    } else {
        s32 w = self->targetMode;
        if (w >= 6) {
            return;
        }
        if (w < 4) {
            return;
        }
        SetPlayerState(self, 2, 2);
    }
}

void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);

void OrientPlayerSpinPart(Player* self, Mat02* out, f32 t)
{
    Vec02 axis;
    Mat02 m;
    if (self->subState == 8) {
        axis = g_unitZVector;
    } else {
        axis = g_unitXVector;
    }
    BuildAxisAngleMatrix((const Vec02*)&axis, (Mat02*)&m, self->spinAngle - g_frameDt[0] * self->spinRate * t);
    Mat02 a;
    Mat02 c;
    MulRotationThenCopy(&c, self->rot, m);
    MulRotationCopiedVia(out, a, c, ((PlacedObject*)self->f61C)->rot);
}

extern void* D_0026FA68;
extern f32 D_00263894;
extern f32 D_00263898;
extern f32 g_scaleApproachRamp[3];
s32 HasNoActiveObject89(Player* self);
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
void OrientPlayerSpinPart(Player* self, Mat02* out, f32 t);
void AddTrailPoint(TrailRing* self, Vec02* pos, Mat02* mat, s32 flag, f32 scale, f32 dt);
void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf);
void BlendPlayerPose(Player* self, void* a, void* b)
{
    u8 out[0x50] __attribute__((aligned(16)));
    Vec02 pos;
    Mat02 turned;
    Mat02 m90;
    if (self->flags & (0x8000ULL << 17)) {
        return;
    }
    f32 target;
    if (self->state == 6 && self->targetMode == 3 && HasNoActiveObject89(self) != 0) {
        f32 since = g_gameClock[1] - self->stateStartTime;
        f32 k;
        if (0.5f <= since) {
            k = 1.0f;
        } else {
            k = g_gameClock[2] / (0.5f - since);
        }
        f32 ramp = self->f2724;
        target = D_00263898;
        self->f2724 = k * D_00263894 + (1.0f - k) * ramp;
    } else {
        f32 one = 1.0f;
        self->f2724 = ApproachValueWithRamp((RampProfile*)g_scaleApproachRamp, 0, self->f2724, one, g_gameClock[2]);
        target = one;
    }
    f32 spin = ApproachValueWithRamp((RampProfile*)g_scaleApproachRamp, 0, self->f2728, target, g_gameClock[2]);
    self->f2728 = spin;
    if (self->f2724 < 1.0f || spin < 1.0f) {
        BuildPlacedObjectTransform(self, (Quad16*)b, (ScaledTransform*)out);
        b = out;
        *(f32*)(out + 0x44) = self->f2728;
        *(f32*)(out + 0x40) = *(f32*)(out + 0x40) * self->f2724;
    }
    self->boundRadius = 500.0f;
    if (self->spinAngle != 0.0f || self->spinRate != 0.0f) {
        OrientPlayerSpinPart(self, &m90, 0.0f);
        u8* obj = (u8*)self->f23D0;
        Mat02* b3 = (Mat02*)(obj + 0xD0);
        u128 r0 = Vu0::Q(m90.r[0]);
        u128 r1 = Vu0::Q(m90.r[1]);
        u128 r2 = Vu0::Q(m90.r[2]);
        Vu0::Q(pos) = Vu0::RotateRows(r0, r1, r2, Vu0::Q(*(Vec02*)(obj + 0x100)));
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(((Collider*)self->f61C)->v140), Vu0::Q(pos));
        MulRotationCopied(&turned, m90, *b3);
        AddTrailPoint((TrailRing*)self->trail, &pos, &turned, 0, self->spinRate, g_gameClock[2]);
        ((Collider*)self->f61C)->flags |= (0x8000ULL << 17);
    } else {
        s32 flag;
        switch (self->state) {
        case 3:
        case 4:
        case 7:
            flag = 1;
            break;
        default:
            flag = 0;
            break;
        }
        AddTrailPoint((TrailRing*)self->trail, 0, 0, flag, 0.0f, g_gameClock[2]);
    }
    if (self->state == 12 && self->subState == 0x22) {
        return;
    }
    if (D_0026FA68 != 0 && (u32)(*(s32*)((u8*)D_0026FA68 + 0x2D0) - 2) < 2) {
        return;
    }
    ApplyPlacedObjectTransform(self, (Camera*)a, (ScaledTransform*)b);
    ((Collider*)self->f61C)->flags &= ~(0x8000ULL << 17);
}

void RecomputeTurningColliderFrame(TurningCollider* self);
void BuildPartProbeTowardLink(void* unused0, PlacedObject* self, void* unused2, PlacedObject* obj, f32 radius, FollowProbe* out); // the float where retail's caller passes it; the definition has it last

void RecomputePlayerFrame(Player* self)
{
    RecomputeTurningColliderFrame(self);
    if (self->state == 6 && self->targetMode == 7) {
        self->f1290.valid = 0;
        goto clear;
    }
    {
        void* a1 = self->f610;
        if (a1 == 0) {
            self->f1290.valid = 0;
            goto clear;
        }
        if (self->f614 == 0) {
            self->f1290.valid = 0;
            goto clear;
        }
        f32 k = 6.0f;
        BuildPartProbeTowardLink(self, (PlacedObject*)a1, a1, (PlacedObject*)self->f620, k, (FollowProbe*)((u8*)&self->f1190));
        BuildPartProbeTowardLink(self, (PlacedObject*)self->f614, self->f614, (PlacedObject*)self->f624, k, (FollowProbe*)((u8*)&self->f1290));
    }
    return;
clear:
    self->f1190.valid = 0;
}

void PlacePartAtProbeSpan(void* unused0, PlacedObject* other, PlacedObject* self, Part07* rec);
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
void OrientPlayerSpinPart(Player* self, Mat02* out, f32 t);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void UpdatePlayerLinkPose(Player* s);
void DrawTurningCollider(TurningCollider* self, void* unused1, void* unused2);
void QueueTrailRibbonDraw(TrailRing* self, u8* cam);
void QueuePlayerMarkerRingDraw(Player* self, RingSource* a, void* b);

void DrawPlayer(Player* self, void* a, void* b)
{
    f32 buf[12];
    f32 out[20];
    s32 i;

    if (!(self->state == 6 && self->targetMode == 7))
    {
        PlacePartAtProbeSpan(self, (PlacedObject*)self->f610, (PlacedObject*)self->f610, &self->f1190);
        PlacePartAtProbeSpan(self, (PlacedObject*)self->f614, (PlacedObject*)self->f614, &self->f1290);
    }
    if (self->spinAngle != 0.0f || self->spinRate != 0.0f)
    {
        ((PlacedObject*)self->f61C)->flags &= ~(1ULL << 32);
        BuildPlacedObjectTransform(self, (Quad16*)b, (ScaledTransform*)out);
        out[16] *= 0.25f;
        for (i = 0; i < 4; i++)
        {
            OrientPlayerSpinPart(self, (Mat02*)buf, (f32)i * 0.25f);
            BuildMatrixFromRotationAndTranslation((const Vec02*)&((PlacedObject*)self->f61C)->v140, (const Mat02*)buf, (Mat4A*)out);
            ((PlacedObject*)self->f61C)->desc02()->m24((PlacedObject*)self->f61C, a, out);
        }
        ((PlacedObject*)self->f61C)->flags |= 0x100000000UL;
    }
    if (self->state == 3)
    {
        UpdatePlayerLinkPose(self);
    }
    DrawTurningCollider(self, a, b);
    if (self->trailEnabled)
    {
        QueueTrailRibbonDraw((TrailRing*)self->trail, (u8*)a);
    }
    QueuePlayerMarkerRingDraw(self, (RingSource*)a, b);
}


extern "C" f32 FloatRemainder(f32 x, f32 y);
// The floats where retail's caller passes them; the definition has them last.
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueWithRamp(RampProfile* k, f32 x, f32 y, f32* out, f32 z);

void UpdatePlayerSpin(Player* self)
{
    if (self->spinTargetRate == 0.0f) {
        if (self->spinAngle == 0.0f) {
            return;
        }
    }
    if (self->spinTargetRate != 0.0f) {
        self->spinRate = self->spinTargetRate;
        self->spinAngle = FloatRemainder(self->spinAngle + self->spinTargetRate * g_frameDt[0], 6.2831855f);
    } else {
        if (self->spinAngle == 0.0f) {
            return;
        }
        f32 r = ApproachValueWithRamp((RampProfile*)&g_spinRampParams, self->spinAngle, 6.2831855f, &self->spinRate, g_frameDt[0]);
        self->spinAngle = r;
        if (r == 6.2831855f) {
            self->spinAngle = 0.0f;
        }
    }
}

// EXACT: callee func_001300E8 declared with a third parameter and called with k, which puts k in a2

// The object the player hands contacts to (Player::contactOwner): it keeps them in a chain at 0x554.
struct ContactChainOwner {
    u8 pad0[0x554];
    Contact03* chain;       // 0x554
};

void ExtractContactsByPartMode(Collider* self, Contact03** out);
// Left with a third argument: PrunePlayerContacts matches only with k passed in $a2, which no
// other call of IsObjectOfKind sets.
s32 IsObjectOfKind(void* key, s32 kind, s32 extra);
void CollectTurningColliderContacts(TurningCollider* self);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void FreePooledContactChain(World* world, Contact03* head);

void PrunePlayerContacts(Player* self)
{
    ContactRow03* row;
    Contact03** slot;
    Contact03* n;
    Contact03* head = 0;
    ExtractContactsByPartMode(self, (Contact03**)self->contactChainHead);
    row = self->contacts->head;
    if (row) {
        do {
            slot = &row->head;
            n = row->head;
            if (n) {
                do {
                    s32 k = (n->end[0].body != self);
                    if (*(void**)((u8*)n + (k << 6) + 4) == self->heldObject) {
                        void* other = n->end[1 - k].body;
                        if (other == 0 || IsObjectOfKind(other, 0x46, k) == 0) {
                            *slot = n->next;
                            n->next = head;
                            head = n;
                        } else {
                            slot = &n->next;
                        }
                    } else if ((void*)n->end[1 - k].body == ((ContactChainOwner*)self->contactOwner) && ((s32 (*)(Player*, Contact03*))self->desc06()->m56)(self, n)) {
                        *slot = n->next;
                        n->next = ((ContactChainOwner*)self->contactOwner)->chain;
                        ((ContactChainOwner*)self->contactOwner)->chain = n;
                    } else {
                        slot = &n->next;
                    }
                    n = *slot;
                } while (n);
            }
            *row->link = row->head;
            row = row->next;
        } while (row);
    }
    CollectTurningColliderContacts(self);
    if (self->state == 8) {
        self->groundContact = 1;
        self->groundContactTime = g_gameTime[0];
        TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec02*)self->ledgeLocalPoint, &self->groundContactPoint);
        self->groundContactNormal = g_unitZVector;
        self->groundContactPart = self->ledgeCollider;
        row = self->contacts->head;
        if (row) {
            do {
                slot = &row->head;
                n = row->head;
                if (n) {
                    do {
                        s32 k = (self != n->end[0].body);
                        if (n->kind == 0xB) {
                            slot = &n->next;
                        } else {
                            if ((void*)n->end[1 - k].body == ((PlacedObject*)self->ledgeCollider)->root) {
                                *slot = n->next;
                                n->next = head;
                                head = n;
                            } else {
                                slot = &n->next;
                            }
                        }
                        n = *slot;
                    } while (n);
                }
                *row->link = row->head;
                row = row->next;
            } while (row);
        }
    }
    FreePooledContactChain((World*)self->world, head);
}

void SaveColliderPreviousPosition(Collider* self);

void SavePlayerPreviousPosition(Player* self)
{
    SaveColliderPreviousPosition(self);
    self->boundsPointCount = 0;
}

// EXACT: declaring D_00261860 as an array (extern f32 D_00261860[], passed as D_00261860[0]) moved the float load into the jal delay slot.


void MoveCollider(Collider* self, f32 x, void* b);

void SetPlayerBoundsPoints(Player* self)
{
    self->boundsPoints[1] = ((PlacedObject*)self->f23D4)->v140;
    self->boundsPointCount = 0;
    MoveCollider(self, g_frameDt[0], 0);
    if (self->aimMode == 0) {
        self->boundsPoints[0] = self->v140;
        self->boundsPoints[2] = ((PlacedObject*)self->f23D4)->v140;
        self->boundsPointCount = 3;
        self->desc03()->m32(self);
    } else {
        self->boundsPointCount = 0;
    }
}

void UpdateColliderBounds(Collider* self);
void ExpandColliderBoundsBySphere(void* self, void* p, f32 f);

void UpdatePlayerBounds(Player* self)
{
    s32 i = 0;
    UpdateColliderBounds(self);
    if (self->boundsPointCount > 0) {
        Vec02* p = self->boundsPoints;
        do {
            ExpandColliderBoundsBySphere(self, p, self->boundsRadius);
            i++;
            p++;
        } while (i < self->boundsPointCount);
    }
}

s32 IsObjectAttached(BaseObject* self);

void* FindFirstAttachedSlotObject(Player* self, s32* out)
{
    void* p = self->f25D8[0];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 0;
        return self->f25D8[0];
    }
    p = self->f25D8[2];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 1;
        return self->f25D8[2];
    }
    p = self->f25D8[1];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 2;
        return self->f25D8[1];
    }
    p = self->f25D8[3];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 2;
        return self->f25D8[3];
    }
    p = self->f25D8[4];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 1;
        return self->f25D8[4];
    }
    return 0;
}

void AddTurningColliderProbeContact(TurningCollider* self, Collider* obj, void* filter, void* out);
void KeepNearestPartSpan(void* unused, void* a1, void* a2, Part07* self);
void AddMeshContacts(Collider* a0, f32 radius, Vec02* a1, Collider* a2, s32 a3, FaceRef* a4, FaceRef* a5, PooledContact** a6);
void CreateMeshPairContacts(Collider* self, Collider* other, s32 a2, FaceRef* a3, u8* ctx, PooledContact** list);

void CollidePlayerWithObject(Player* self, Collider* a1, s32 a2, void* a3, void* a4, void* a5)
{
    s32 idx;
    Collider* v;
    Collider* cur;

    switch (self->state)
    {
    case 4:
        if (self->probeContactsDisabled == 0)
        {
            switch (self->subState)
            {
            case 0x24:
            case 0x2A:
            case 0x2B:
                AddTurningColliderProbeContact(self, a1, a4, a5);
                break;
            }
        }
        break;
    case 3:
    case 7:
    case 0xD:
        break;
    default:
        if (self->probeContactsDisabled == 0)
        {
            AddTurningColliderProbeContact(self, a1, a4, a5);
        }
        break;
    }
    KeepNearestPartSpan(self, a1, a4, &self->f1190);
    KeepNearestPartSpan(self, a1, a4, &self->f1290);
    v = (Collider*)FindFirstAttachedSlotObject(self, &idx);
    if (v)
    {
        for (cur = a1; cur; cur = (Collider*)cur->parent)
        {
            if (*((u8*)cur + idx + 0x2B0))
            {
                if (a1->flags538 & (1ULL << 40))
                {
                    AddMeshContacts(a1, a1->radius3CC, &a1->v140, v, v->tree.count, (FaceRef*)v->tree.nodes, 0, (PooledContact**)&self->queryContacts);
                }
                else if (a3)
                {
                    CreateMeshPairContacts(v, a1, a2, (FaceRef*)a3, (u8*)a4, (PooledContact**)&self->queryContacts);
                }
                return;
            }
        }
    }
}

s32 GetPlayerContactMode(Player* self)
{
    if (self->state == 3 || self->state == 0xD) {
        return 0;
    }
    return 3;
}

extern f32 D_002638B8;
extern f32 D_002638BC;
extern f32 D_002638C0;
extern f32 D_002638C4;
extern f32 D_002638C8[2];
extern f32 D_002638D0[4];
extern f32 g_pivotApproachRamp[4];
extern f32 g_heightApproachRamp[4];

void CaptureSwitchedColliderPose(SwitchedCollider* self, u8* out, f32 a);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
u128 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec02* vel);
struct PushRecord;
void FillPlayerPushRecord(Player* self, PushRecord* out);
#include "value_range.h"
typedef void (*PoseAtFn)(PoseHolder47* self, Vec02* pos, Vec02* dir, f32 t);

// The pose a collider's slot captures each frame (CaptureSwitchedColliderPose fills pos).
struct ColliderPose {
    s32 flags;              // 0x00: bit 0 set in the player's grounded states
    u8 pad04[0x10 - 0x04];
    Vec02 pos;              // 0x10: where the camera looks
    Vec02 dir;              // 0x20: the path's direction times the speed along it
    u8 pad30[0x34 - 0x30];
    f32 weight;             // 0x34: a weight, scaled down by the spin or cleared
    f32 stampTime;          // 0x38: the time it was last stamped
    s32 f3C;                // 0x3C
};
#define PL(T, o) (*(T*)((u8*)self + (o)))

void CapturePlayerPose(Player* self, ColliderPose* pose, f32 dt)
{
    u8* out = (u8*)pose;
    Vec02 last = self->focusPoint;
    CaptureSwitchedColliderPose(self, out, dt);
    if (self->holdFocus == 0) {
        if (self->state == 7) {
            Vec02 pos;
            Vec02 dir;
            PoseHolder47* h = ((PoseTarget*)self->aimCurve)->holder;
            PoseAtFn fn = (PoseAtFn)h->desc->m2;
            if (fn != 0) {
                fn(h, &pos, &dir, self->pathPos);
            }
            TransformPointBetweenFrames((PlacedObject*)(((PoseTarget*)self->aimCurve)->frame), 0, &pos, &pos);
            Vu0::Q(pose->pos) = Vu0::Q(pos);
            TransformDirectionBetweenFrames((PlacedObject*)(((PoseTarget*)self->aimCurve)->frame), 0, &dir, &dir);
            u128 d = Vu0::Q(dir);
            d = Vu0::NormalizeOr(d, Vu0::Q(D_00248D30));
            Vu0::Q(pose->dir) = Vu0::MulX(d, Vu0::ScalarAt(self->pathSpeed));
            Vu0::Q(dir) = d;
            self->cameraHeight = pose->pos.z - 125.0f;
        } else {
            if (self->state == 3) {
                Vec02 pos;
                GetObjectWorldPosition(self->boundObject, &pos);
                self->cameraHeight = pos.z + D_002638C8[0];
            } else if (self->groundContact != 0) {
                self->cameraHeight = self->groundContactPoint.z;
            } else if (g_camera->snapping != 0) {
                self->cameraHeight = self->v140.z - 75.0f;
            }
            f32 h = self->cameraHeight;
            f32 lo = self->pos.z + D_002638C4;
            f32 hi = self->pos.z + D_002638C0;
            f32 r;
            if (h < lo) {
                r = lo;
            } else if (hi < h) {
                r = hi;
            } else {
                r = h;
            }
            self->cameraHeight = r;
            f32 z = r + 125.0f;
            if (g_camera->snapping != 0) {
                pose->pos.z = z;
            } else {
                f32 v = ApproachValueWithRamp((RampProfile*)g_heightApproachRamp, 0, last.z, z, g_gameClock[2]);
                pose->pos.z = v;
                f32 zlo = self->pos.z + D_002638BC;
                f32 zhi = self->pos.z + D_002638B8;
                f32 w;
                if (v < zlo) {
                    w = zlo;
                } else if (zhi < v) {
                    w = zhi;
                } else {
                    w = v;
                }
                pose->pos.z = w;
            }
        }
        if (self->state == 6 && self->targetMode == 0) {
            FillPlayerPushRecord(self, (PushRecord*)out);
        }
        u128 d = ApproachPointWithRamp(Vu0::Q(self->poseOffset), Vu0::Q(D_00248D30), dt, (RampProfile*)g_pivotApproachRamp, 0);
        Vu0::Q(self->poseOffset) = d;
        Vu0::Q(pose->pos) = Vu0::Add(Vu0::Q(pose->pos), d);
    }
    switch (self->state) {
    case 2:
        if (self->f2498 != 0) {
            pose->flags |= 1;
        }
        break;
    case 3:
    case 4:
    case 5:
        pose->flags |= 1;
        break;
    case 6:
        switch (self->targetMode) {
        case 0:
        case 1:
            pose->f3C = 1;
            break;
        case 2:
        case 4:
        case 5:
            break;
        default:
            pose->flags |= 1;
            break;
        }
        break;
    }
    s32 stamp = 1;
    switch (self->state) {
    case 0:
        stamp = 0;
        break;
    case 6:
        if (self->subState == 16) {
            stamp = 0;
        }
        break;
    case 7:
        if (self->subState == 24) {
            stamp = 0;
        }
        break;
    }
    if (stamp != 0) {
        self->f2680 = g_gameTime[0];
    }
    pose->stampTime = self->f2680;
    switch (self->state) {
    case 0: {
        f32 a = __builtin_fabsf(self->v160.z);
        f32 k = D_002638D0[0] + a * (D_002638D0[1] + a * D_002638D0[2]);
        f32* range = (f32*)&g_unitRange;
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
        k = r;
        pose->weight = pose->weight * k;
        break;
    }
    case 4:
        switch (self->subState) {
        case 41:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            pose->weight = 0.0f;
        }
        break;
    case 7:
    case 13:
        pose->weight = 0.0f;
        break;
    }
    self->focusPoint = pose->pos;
}

#undef POSE
#undef PL

// The object the player is pushed along (+0x23A0): a frame at +0x18, flags at +0x50 and a holder
// at +0x34 that has an array of floats, or answers a length through its descriptor.
struct PushHolderDesc;
struct PushHolder { PushHolderDesc* desc; u8 pad04[4]; s32 f08; s32 count; u8 pad10[4]; f32* values; };
struct PushHolderDesc {
    u8 pad00[8];
    void (*m2)(PushHolder* self, Vec02* out, f32 t, s32 a);
    u8 pad0C[0x20 - 0x0C];
    f32 (*length)(PushHolder* self);
};
struct PushObject { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PushHolder* holder; u8 pad38[0x50 - 0x38]; u32 flags; };
struct PushRecord { u8 pad00[0x30]; f32 heading; s32 f34; };
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);

void FillPlayerPushRecord(Player* self, PushRecord* out)
{
    out->heading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
    if (self->forcedOnOffObject != (s32)self->ownOnOffObject) {
        return;
    }
    out->f34 = 0;
    switch (self->onOffPhase) {
    case 1 ... 2: {
        PushObject* o = (PushObject*)self->targetCurve;
        if (o != 0) {
            f32 limit;
            if (self->onOffPhase == 1) {
                PushHolder* h = o->holder;
                limit = self->targetCurvePos + *(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f);
                if (h->f08 == 0) {
                    f32 top = h->values[h->count - 1];
                    if (o->flags & 2) {
                        top = top + 100.0f;
                    }
                    limit = top <? limit;
                }
            } else {
                PushHolder* h = o->holder;
                limit = self->targetCurvePos - *(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f);
                if (h->f08 == 0) {
                    f32 bottom = h->values[0];
                    if (o->flags & 1) {
                        bottom = bottom - 100.0f;
                    }
                    limit = bottom >? limit;
                }
            }
            Vec02 point;
            PushHolder* holder = ((PushObject*)self->targetCurve)->holder;
            if (holder->desc->m2 != 0) {
                holder->desc->m2(holder, &point, limit, 0);
            }
            TransformPointBetweenFrames((PlacedObject*)(((PushObject*)self->targetCurve)->frame), 0, &point, &self->v2690);
            self->v2690.z = self->v2690.z + 125.0f;
        } else {
            Vec02 k;
            if (self->onOffPhase == 1) {
                Vu0::Q(k) = Vu0::FromFloat(*(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f));
                Vu0::Q(self->v2690) = Vu0::Add(Vu0::Q(self->v140), Vu0::MulX(Vu0::Q(self->m110.r[1]), Vu0::Q(k)));
            } else {
                Vu0::Q(k) = Vu0::FromFloat(*(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f));
                Vu0::Q(self->v2690) = Vu0::Sub(Vu0::Q(self->v140), Vu0::MulX(Vu0::Q(self->m110.r[1]), Vu0::Q(k)));
            }
            self->v2690.z = self->v2690.z + 50.0f;
        }
        break;
    }
    case 0:
        self->v2690 = self->v140;
        self->v2690.z = self->v2690.z + 50.0f;
        break;
    case 3:
        break;
    }
    if (self->targetCurve == 0) {
        return;
    }
    PushHolder* h = ((PushObject*)self->targetCurve)->holder;
    if (h->f08 != 0) {
        return;
    }
    f32 base = 30.0f;
    f32 len = h->desc->length(h) - base;
    f32 span = (len - base) * 0.5f;
    f32 reach = MinF(span, 300.0f);
    f32 lowEdge = reach + base;
    f32 highEdge = len - reach;
    f32 at = self->targetCurvePos;
    f32 w;
    f32 force;
    if (at < lowEdge) {
        f32 t = (lowEdge - at) / reach;
        w = ClampBetween(t, 0.0f, 1.0f);
        force = -w * w * 150.0f;
    } else if (highEdge < at) {
        f32 t = (at - highEdge) / reach;
        w = ClampBetween(t, 0.0f, 1.0f);
        force = w * w * 150.0f;
    } else {
        force = 0.0f;
    }
    OnOffObject* target = self->ownOnOffObject;
    f32* slot = (f32*)((u8*)target + 0x300);
    *(f32*)((u8*)self->ownOnOffObject + 0x300) = ApproachValueWithRamp((RampProfile*)g_forceApproachRamp, 0, *slot, force, g_frameDt[0]);
}


void HandleSwitchedColliderActivation(SwitchedCollider* self, void* activator);
void ShowModeLabel(s32 mode);

void SetPlayerTracked(Player* a, void* b)
{
    HandleSwitchedColliderActivation(a, b);
    s32 id;
    if (b != 0) id = g_saveData->lastHintMode;
    else id = -1;
    ShowModeLabel(id);
}

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
s32 CollectColliderSpans(Collider* self, Vec02* a1, Vec02* a2, s32 a3, ColliderSpan* a4);

s32 HasFloorAtPlayerOffset(Player* self, Vec02* offset)
{
    s32 count;
    Collider** list;
    Vec02 from;
    Vec02 to;
    ColliderSpan spans[8];
    s32 i = 0;
    PushBackMemoryMark();
    from = *self->lowestVertex;
    Vu0::Q(to) = Vu0::Add(Vu0::Q(*self->lowestVertex), Vu0::Q(*offset));
    GatherCollidersInBox(self->world, self, &from, &to, 0, 0, &count, &list);
    for (; i < count; i++) {
        s32 n = CollectColliderSpans(list[i], &from, &to, 8, spans);
        for (s32 j = 0; j < n; j++) {
            ColliderSpan* p = &spans[j];
            if (p->time[0] != 0.0f && ((Vec02*)&p->q[2])->z > 0.7f) {
                PopBackMemoryMark();
                return 1;
            }
        }
    }
    PopBackMemoryMark();
    return 0;
}

#include "pad_record.h"
#include "step_sequence.h"
#include "identity_key.h"

s32 HasAnimationDrivenAttachment(SwitchedCollider *self);
void ReleaseAnimationDrivenAttachments(Player* self);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 IsObjectOfKind(BaseObject* list, s32 key);
s32 IsTopCameraController(CameraController* self);
s32 HasSpareCount(void);
s32 MaskWorldBitsBySave(void);
void SetPlayerBlendWeights(f32 f12, f32 f13, TurningCollider* a0, TurnBlendRecords* a1, BlendAnimationView* a2); // the floats first, as the definition takes them
extern s32 g_currentMode;
extern s32 g_padRouting;
extern s32 g_padSelectFlags;
s32 IsEntryQueueRunning(EntryQueue* q);
void DrivePlayerFromEntryQueue(EntryQueue* q, PadRecord* pad);
void UnbindEntryQueue(EntryQueue* q);
void StartObjectFade(IdentityKey* obj, s32 value, s32 count);
void ClearPadPressedBits(PadRecord* self, u32 mask);
void ReadTurningColliderStickHeading(TurningCollider* self, PadRecord* pad);
f32 WrapAngle(f32 a);
void UpdateModeSelection(Player* self, PadRecord* pad);
void SkipRemainingSteps(StepSequence* self);
void SetStepSequenceState(StepSequence* self, s32 state);
s32 ChooseNearbyPlayerTarget(Chooser_1CDFB8* self, void* target, s32* out);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
s32 ChoosePlayerTargetByCost(Chooser* self, TargetCand* keep);
s32 ChoosePlayerNextState(Player* self);
void PopStackElement(ElementStack* g);
void HandlePlayerAimButton(Player* self, PadRecord* pad);
// player_request.cpp defines it with four parameters; retail's call here also loads the word at
// 0xA10 into $a2 (first, as the argument order below gives).
void SetPlayerVelocityFromHeading(Player* self, const Vec02* basis, BlendAnimationView* blend, f32 heading, f32 speed);
void ControlPlayerOnLinkedObject(Player* self, void* pad);
void ControlPlayerOnPath(Player* self, PathPad* pad);
void ControlPlayerState2(Player* self, PadRecord* pad);
void ControlPlayerOnTarget(Player* self, PadRecord* pad);
void UpdatePlayerGrabs(Player* self);
extern s32 D_00261D38;
extern s32 g_resumeSoundSetupDone;
extern StepSequence* g_playerStepSequence;
extern u8 g_elementStack[];

// Slot 73 of class 0x07: the player's control for a frame. Without control (an activation queued, the
// entry queue running) the pad is a cleared record. It works out a jump (the pad's 0x40 bit near a
// floor), a fall and a step skip, then changes state until the state it chooses is the one it is in,
// and runs the state's own control. A 0x40 press without a jump stamps 0x2284, except in state 4
// (the goto, past the stamp). In the
// default case the offset is stored through a cast, so its address is not a register CSE hands on to
// the call, which retail computes after the time test.
void ControlPlayer(Player* self, PadRecord* pad, f32 dt)
{
    if (HasAnimationDrivenAttachment(self)) {
        if (!(0.0f < pad->stickMagnitude) && (pad->flags & 0xF0) == 0) {
            return;
        }
        ReleaseAnimationDrivenAttachments(self);
    }
    PadRecord blank;
    if (D_00261D38 > 0 || self->walkerActivation != 0 || self->firstActivation != 0 || self->secondActivation != 0) {
        switch (self->state) {
        case 12:
            if (self->pendingCaption == 0) {
                SetPlayerState(g_player, 12, 0x23);
            }
            break;
        case 8:
            if (g_gameTime[0] - self->stateStartTime > 0.2f) {
                self->jumpKind = 4;
                SetPlayerState(g_player, 2, 0);
            }
            break;
        case 2:
            switch (self->subState) {
            case 4:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                SetPlayerState(self, 2, 2);
                break;
            }
            break;
        }
        FillMemory(&blank, 0, sizeof(blank));
        pad = &blank;
    }
    if (self->state != 4) {
    if (self->entryQueue != 0 && IsEntryQueueRunning(self->entryQueue)) {
        EntryQueue* q = self->entryQueue;
        if ((g_padRecord.flags & 0x800) && g_resumeSoundSetupDone == 0) {
            s32 start = q->entryIndex;
            if (start >= 0) {
                for (s32 i = start; i < q->entryCount; i++) {
                    QueueEntry* e = &((QueueEntry*)q->buffer)[i];
                    if (e->kind == 1) {
                        BaseObject* o = FindFirstObjectById(q->world, 0x104, e->id, (void*)q->lastFoundObject);
                        if (o != 0 && IsObjectOfKind(o, 0x74)) {
                            StartObjectFade(&D_00275B04, o->id, 1);
                            ClearPadPressedBits(&g_padRecord, 0x800);
                            break;
                        }
                    }
                }
            }
        }
        FillMemory(&blank, 0, sizeof(blank));
        pad = &blank;
        DrivePlayerFromEntryQueue(self->entryQueue, &blank);
    } else {
        if (self->entryQueue != 0) {
            UnbindEntryQueue(self->entryQueue);
        }
        ReadTurningColliderStickHeading(self, pad);
    }
    } else {
        ReadTurningColliderStickHeading(self, pad);
    }
    s32 skipStep = 0;
    s32 noFloor = 0;
    s32 moving;
    s32 falling = 0;
    s32 jump = 0;
    WrapAngle(self->stickHeading - ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x));
    if (pad->flags & 0x40) {
        switch (self->state) {
        case 6:
            if (self->targetMode == 2 || self->targetMode == 5 || self->targetMode == 4) {
                jump = 1;
            }
            break;
        case 2:
            switch (self->subState) {
            case 7:
            case 8:
                break;
            default:
                if (self->f2498 != 0) {
                    Vec02 off;
                    Vu0::Q(off) = Vu0::MulXSum3(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth),
                                                Vu0::Q(self->v150), Vu0::Scalar(0.1f),
                                                Vu0::Q(self->gravity), Vu0::Scalar(0.5f * 0.1f * 0.1f));
                    falling = HasFloorAtPlayerOffset(self, &off) == 0;
                }
                break;
            }
            break;
        case 4:
            goto held;
        case 5:
        default: {
            Vec02 off;
            *(u128*)&off = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth - 60.0f));
            if (g_gameTime[0] - self->groundContactTime < 0.1f || HasFloorAtPlayerOffset(self, &off)) {
                jump = 1;
            }
            break;
        }
        case 3:
        case 7:
        case 8:
            jump = 1;
            break;
        }
        if (!jump) {
            self->f2284 = g_gameTime[0];
        }
    } else if (g_gameTime[0] - self->f2284 < 0.1f && g_gameTime[0] - self->groundContactTime < 0.1f) {
        jump = 1;
    }
held:
    switch (self->state) {
    case 0:
    case 1:
    case 5:
    case 6:
    case 14:
    case 15:
    case 16:
        if (g_gameTime[0] - self->groundContactTime > 0.1f) {
            Vec02 off;
            if (self->state == 6 && self->targetMode == 3) {
                Vu0::Q(off) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth - 200.0f));
            } else {
                Vu0::Q(off) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth - 60.0f));
            }
            noFloor = !HasFloorAtPlayerOffset(self, &off);
        }
        break;
    default:
        noFloor = 0;
        break;
    }
    moving = 0.0f < self->stickLevel;
    s32 aim = pad->buttons & 0x20;
    s32 modeKey = 0;
    if (pad->flags & 0x10) {
        modeKey = g_currentMode == 0;
    }
    UpdateModeSelection(self, pad);
    if (!IsTopCameraController((CameraController*)((u8*)&g_camera->ctl454))) {
        PadRecord* rec = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
        StepSequence* seq = (StepSequence*)g_typedTextCaptionBox.child;
        if (seq != 0 && seq->state2D4 == 3 && seq->f32C == 0 && (rec->flags & 0xC) && *(s32*)seq->target304 != 0) {
            if (self->state == 12) {
                self->pendingCaption = 0;
                skipStep = 1;
            }
            SkipRemainingSteps((StepSequence*)g_typedTextCaptionBox.child);
            ClearPadPressedBits(rec, 0xC);
        } else if (self->f2BD4 != 0 || (pad->flags & 0xC)) {
            if (self->state == 12) {
                if (g_typedTextCaptionBox.child == 0) {
                    self->pendingCaption = 0;
                    skipStep = 1;
                }
            } else if (g_typedTextCaptionBox.child == 0) {
                if ((pad->flags & 4) && g_playerStepSequence != 0 && (self->f2BD4 == 0 || g_playerStepSequence->mode2D0 == 1)) {
                    SetStepSequenceState(g_playerStepSequence, 1);
                } else if (self->f2BD4 == 0) {
                    self->pendingCaption = 0;
                    skipStep = 1;
                }
            }
        }
    }
    for (;;) {
        s32 state = self->state;
        s32 sub = self->subState;
        s32 target;
        switch (state) {
        case 4:
            if (HasSpareCount()) {
                if (pad->flags & 0x40) {
                    ClearPadPressedBits(pad, 0x40);
                    self->f2734 = g_gameTime[0];
                }
            }
            if (self->f2738 != 0 && g_gameTime[0] - self->f2734 < D_00263910[0]) {
                RunPlayerCallback(self);
                state = self->state;
                sub = self->subState;
            }
            break;
        case 0:
            if ((self->aimMode == 8 || self->aimMode == 9) && self->f2248 == 0) {
                break;
            }
            if (jump) {
                state = 2;
                sub = 0;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (modeKey && (MaskWorldBitsBySave() & 2)) {
                state = 10;
                sub = 0x1F;
                break;
            }
            if (aim) {
                target = ChooseNearbyPlayerTarget((Chooser_1CDFB8*)self, 0, &self->targetMode);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
            }
            if (skipStep) {
                state = 12;
                sub = 0x21;
                break;
            }
            if (moving) {
                state = 1;
                sub = -1;
            }
            break;
        case 1:
            if (jump) {
                state = 2;
                sub = 0;
                self->jumpKind = state;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (modeKey && (MaskWorldBitsBySave() & 2)) {
                state = 10;
                sub = 0x1F;
                break;
            }
            if (aim) {
                target = ChooseNearbyPlayerTarget((Chooser_1CDFB8*)self, 0, &self->targetMode);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
            }
            if (skipStep) {
                state = 12;
                sub = 0x21;
                break;
            }
            if (!moving) {
                state = 0;
                sub = -1;
            }
            break;
        case 5:
            if (jump) {
                state = 2;
                sub = 0;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (aim) {
                target = ChooseNearbyPlayerTarget((Chooser_1CDFB8*)self, 0, &self->targetMode);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
            }
            if (skipStep) {
                state = 12;
                sub = 0x21;
                break;
            }
            state = 0;
            sub = -1;
            break;
        case 2: {
            s32 ready = !(sub == 10 || sub == 11 || sub == 13 || sub == 12 || sub == 14 || sub == 15 || sub == 8)
                && (sub != 5 || g_gameTime[0] - self->subStateStartTime > 0.05f);
            if (ready) {
                if (pad->flags & 0x20) {
                    ClearPadPressedBits(pad, 0x20);
                    SetPlayerAimMode(self, -1);
                    sub = ChoosePlayerTargetByCost((Chooser*)self, 0);
                    break;
                }
                if ((sub != 6 || self->jumpSpeed != 0.0f) && (pad->flags & 0x80)) {
                    SetPlayerAimMode(self, -1);
                    sub = 7;
                    ClearPadPressedBits(pad, 0x80);
                    break;
                }
            }
            if (ready && modeKey && (MaskWorldBitsBySave() & 0x10)) {
                SetPlayerAimMode(self, -1);
                sub = 8;
                break;
            }
            if (jump) {
                sub = 0;
                if (MaskWorldBitsBySave() & 0x1000) {
                    break;
                }
                if (!(pad->buttons & 0x10)) {
                    self->slowDownHeld = 0;
                }
                break;
            }
            if (falling) {
                sub = 3;
            }
            break;
        }
        case 3:
        case 7:
            if (jump) {
                state = 2;
                sub = 0;
                self->jumpKind = 1;
            }
            break;
        case 6:
            if (self->targetMode == 2) {
                if (jump) {
                    state = 2;
                    sub = 5;
                }
                break;
            }
            if (jump) {
                state = 2;
                sub = 0;
                break;
            }
            if (self->targetMode == 4 || self->targetMode == 5) {
                break;
            }
            if (modeKey && (MaskWorldBitsBySave() & 2)) {
                state = 10;
                sub = 0x1F;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (pad->buttons & 0x20) {
                break;
            }
            if (g_padSelectFlags & 1) {
                break;
            }
            state = ChoosePlayerNextState(self);
            sub = -1;
            break;
        case 8:
            if (jump) {
                state = 2;
                sub = 0;
                self->jumpKind = 4;
            }
            break;
        case 12:
            if (skipStep) {
                if (self->subState == 0x22) {
                    sub = 0x23;
                    PopStackElement((ElementStack*)g_elementStack);
                    break;
                }
            } else if (self->subState == 0x22) {
                T217D_440* box = &g_typedTextCaptionBox;
                if (box->state == 0 || (box->state == 2 && box->child != 0 && ((StepSequence*)box->child)->state2D4 == 4)) {
                    sub = 0x23;
                    break;
                }
            }
            if (self->subState == 0x21 && self->f25CC == 0 && g_gameTime[0] - self->subStateStartTime >= 0.5f) {
                sub = 0x22;
                break;
            }
            if (self->subState == 0x23 && self->f25D0 == 0 && g_gameTime[0] - self->subStateStartTime >= 0.25f) {
                state = 0;
                sub = -1;
            }
            break;
        case 13:
            if (!(pad->buttons & 0x10) && g_gameTime[0] - self->stateStartTime > g_state13ExitDelay) {
                sub = 0x38;
                break;
            }
            self->heading = self->stickHeading;
            break;
        case 14:
        case 15:
        case 16:
            if (noFloor) {
                state = 2;
                sub = 2;
            }
            break;
        }
        if (state == self->state && sub == self->subState) {
            break;
        }
        SetPlayerState(self, state, sub);
        skipStep = 0;
        jump = 0;
        falling = 0;
    }
    HandlePlayerAimButton(self, pad);
    switch (self->state) {
    case 5:
        SetPlayerVelocityFromHeading(self, (const Vec02*)self->eightWaySlots, self->eightWayBlend, self->stickHeading, self->stickLevel);
        break;
    case 1:
        SetPlayerBlendWeights(self->stickHeading, self->stickLevel, self, (TurnBlendRecords*)self->sixWayItems, self->sixWayBlend);
        break;
    case 4:
    case 10: {
        self->headingVelocity = D_00248D30;
        PlayerNoticePlayer* src = (PlayerNoticePlayer*)self->stateAnimPlayer;
        if (src != 0) {
            Track83* track = src->anim->movedTrack;
            if (track != 0) {
                PositionCurve* c = track->pos;
                if (c != 0) {
                    Vec02 v;
                    c->vt->eval(c, self, src->time, src->speed, 0, 0, &v);
                    Vu0::Q(self->headingVelocity) = Vu0::MulX(Vu0::Q(v), Vu0::Scalar(-1.0f));
                }
            }
        }
        break;
    }
    case 3:
        ControlPlayerOnLinkedObject(self, pad);
        break;
    case 7:
        ControlPlayerOnPath(self, (PathPad*)pad);
        break;
    case 2:
        ControlPlayerState2(self, pad);
        break;
    case 6:
        ControlPlayerOnTarget(self, pad);
        break;
    case 0:
    case 16:
        break;
    }
    UpdatePlayerGrabs(self);
}

void UpdateTurningCollider(TurningCollider* self, f32 dt);
s32 HasAnimationDrivenAttachment(SwitchedCollider *self);
void UpdatePlayerWhileAnimationDriven(Player* self);
void UpdateSixEntryBlendWeights(TurningCollider* p, void* e, BlendAnimationView* g, void* a3);
f32 WrapModulo(f32 x, f32 y);
void PlayPhaseCrossingSound(Player* self, f32* p, f32 f);
void UpdateEightEntryBlendWeights(Player* self, BlendSlot* slots, BlendAnimationView* gr);
void UpdatePlayerState2(Player* self);
void UpdatePlayerTargetPhase(Player* self);
u128 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec02* vel);
s32 ComputeLedgeOffsetForContact(Collider* self, Collider* part, Vec02* point, s32 kind, void* arg, Vec02* out);
void UpdatePlayerRequestSubState(Player* self);
void UpdatePlayerAimTarget(Player* self);
void ReleaseFarPlayerLinks(Player* self);
void NotifyPlayerGroundObject(Player* self);
void ClearRootTries(PlacedObject* self);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* o1, f32* o2);
void FindClosestPointsOnSegments(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir);
void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);
void PosePlayerTargetPart(Player* self);
void RecordPlayerTargetMemo(Player* self);
void RunPlayerQueuedActivations(Player* self);
extern f32 D_00274B64;

struct PhaseObject_174808 { u8 pad00[0x34]; f32 period; };
struct PhaseMessage_174808 { u8 pad00[8]; PhaseObject_174808* f8; u8 pad0C[0x14 - 0xC]; f32 f14; f32 f18; };
struct PathShape_174808;
struct PathShapeDesc_174808 { u8 pad00[0x30]; void (*m30)(PathShape_174808* self, Vec02* at, f32 t, s32 a, Vec02* out, s32 b, s32 c, s32 d); };
struct PathShape_174808 { PathShapeDesc_174808* desc; };
struct PathTarget_174808 { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PathShape_174808* shape; };
struct LinkTarget_174808 { u8 pad00[0x8C]; f32 radius; };
struct ContactBody_174808;
struct ContactBodyDesc_174808 {
    u8 pad00[0x12C];
    s32 (*m12C)(ContactBody_174808* self, Contact03* c, OwnerMessage* msg);
    u8 pad130[0x140 - 0x130];
    void (*m140)(ContactBody_174808* self, OwnerMessage* msg);
    u8 pad144[0x160 - 0x144];
    void (*m160)(ContactBody_174808* self);
};
struct ContactBody_174808 {
    ContactBodyDesc_174808* desc;
    u8 pad04[0x18 - 0x04];
    ContactBody_174808* parent;     // 0x18
    u8 pad1C[0x4E0 - 0x1C];
    s32 f4E0;                       // 0x4E0
};

// Which end of the contact the object is: 0 when it is end 0's body, else 1.
static inline s32 ContactEndOf(Contact03* c, void* obj)
{
    return c->end[0].body != obj;
}

void UpdatePlayer(Player* self, f32 dt)
{
    UpdateTurningCollider(self, dt);
    ApplyPendingPlayerStateRequest(self);
    if (HasAnimationDrivenAttachment(self) != 0) {
        UpdatePlayerWhileAnimationDriven(self);
    }
    if (self->pulseActive != 0 && self->state != 4 && self->pulseFadeDuration < g_gameTime[0] - self->pulseFadeStart) {
        self->pulseActive = 0;
    }
    switch (self->state) {
    case 1:
        UpdateSixEntryBlendWeights(self, self->sixWayItems, self->sixWayBlend, self->stateAnimPlayer);
        {
            f32 phase = WrapModulo((((PhaseMessage_174808*)self->stateAnimPlayer)->f14 + D_00274B64 * ((PhaseMessage_174808*)self->stateAnimPlayer)->f18) / ((PhaseMessage_174808*)self->stateAnimPlayer)->f8->period, 1.0f);
            PlayPhaseCrossingSound(self, (f32*)&self->phaseSoundStates[0], phase);
        }
        break;
    case 5:
        UpdateEightEntryBlendWeights(self, (BlendSlot*)self->eightWaySlots, self->eightWayBlend);
        {
            f32 phase = WrapModulo((((PhaseMessage_174808*)self->stateAnimPlayer)->f14 + D_00274B64 * ((PhaseMessage_174808*)self->stateAnimPlayer)->f18) / ((PhaseMessage_174808*)self->stateAnimPlayer)->f8->period, 1.0f);
            PlayPhaseCrossingSound(self, (f32*)&self->phaseSoundStates[1], phase);
        }
        break;
    case 2:
        UpdatePlayerState2(self);
        break;
    case 0:
        UpdatePlayerState0(self);
        break;
    case 6:
        UpdatePlayerTargetPhase(self);
        break;
    case 8: {
        Vec02 local;
        Vu0::Q(self->ledgeSlack) = ApproachPointWithRamp(Vu0::Q(self->ledgeSlack), Vu0::Q(D_00248D30), dt, (RampProfile*)g_positionApproachRamp, 0);
        TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec02*)self->ledgeLocalPoint, &local);
        if (ComputeLedgeOffsetForContact(self, (Collider*)self->ledgeCollider, &local, self->ledgeKind, (void*)self->ledgeKey, &self->ledgeOffset) == 0) {
            SetPlayerState(self, 2, 2);
            break;
        }
        self->heading = ArctangentOfRatio(-self->ledgeOffset.y, -self->ledgeOffset.x);
        break;
    }
    case 9: {
        Vec02 local;
        if (self->walkerHost != 0) {
            Vu0::Q(local) = Vu0::Sub(Vu0::Q(((Player*)self->walkerHost)->v140), Vu0::Q(g_player->v140));
        } else {
            Vu0::Q(local) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(g_player->v140));
        }
        self->heading = ArctangentOfRatio(local.y, local.x);
        break;
    }
    case 4:
        UpdatePlayerRequestSubState(self);
        break;
    case 12:
        self->heading = *(f32*)&g_camera->ctl460.value;
        break;
    case 13:
        if (self->subState == 0x38) {
            if (D_00263924 < self->rot.r[2].z) {
                s32 slow = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v160), Vu0::Q(self->v160)))) < D_00263928[0];
                if (slow) {
                    SetPlayerState(self, 2, 2);
                }
            }
        } else if (self->subState == 0x36) {
            if (self->groundContact != 0) {
                SetPlayerState(self, 0xD, 0x37);
            }
        }
        break;
    }
    UpdatePlayerAimTarget(self);
    ((ContactBody_174808*)self)->desc->m160((ContactBody_174808*)self);
    ReleaseFarPlayerLinks(self);
    NotifyPlayerGroundObject(self);
    ClearRootTries(self);
    if (self->aimMode == 0) {
        Vec02 local;
        Vec02 pts[3];
        Vec02 dirs[3];
        Vec02 closest;
        f32 t;
        f32 dist;
        f32 gap;
        if (self->boundObject != 0) {
            GetObjectWorldPosition((BaseObject*)self->boundObject, &local);
            for (s32 i = 1; i < self->boundsPointCount; i++) {
                MeasurePointToSegment(&local, &self->boundsPoints[i - 1], &self->boundsPoints[i], &t, &dist);
                if (dist < ((LinkTarget_174808*)self->aimTarget)->radius + self->boundsRadius) {
                    SetPlayerState(self, 3, 0x33);
                    break;
                }
            }
        } else if (self->aimCurve != 0) {
            s32 i;
            for (i = 0; i < self->boundsPointCount; i++) {
                TransformPointBetweenFrames(0, (PlacedObject*)((PathTarget_174808*)self->aimCurve)->frame, &self->boundsPoints[i], &pts[i]);
                PathShape_174808* s = ((PathTarget_174808*)self->aimCurve)->shape;
                if (s->desc->m30 != 0) {
                    s->desc->m30(s, &pts[i], self->aimCurvePos, 0, &dirs[i], 0, 0, 0);
                }
            }
            for (i = 1; i < self->boundsPointCount; i++) {
                FindClosestPointsOnSegments(&pts[i - 1], &pts[i], &dirs[i - 1], &dirs[i], (f32*)&local, &gap, &closest);
                if (gap < self->boundsRadius) {
                    SetPlayerState(self, 7, 0x17);
                    break;
                }
            }
        }
    }
    if (*(Contact03**)self->contactChainHead != 0) {
        for (Contact03* c = *(Contact03**)self->contactChainHead; c != 0; c = c->next) {
            ContactBody_174808* o = (ContactBody_174808*)c->end[1 - ContactEndOf(c, self)].part;
            while (o != 0 && o->f4E0 == 0) {
                o = o->parent;
            }
            if (o != 0 && (o->f4E0 == 1 || o->f4E0 == 4)) {
                OwnerMessage msg;
                InitOwnerMessage(&msg, 0, o);
                for (; o != 0; o = o->parent) {
                    if (o->desc->m12C(o, c, &msg) != 0) {
                        break;
                    }
                }
                ((ContactBody_174808*)self)->desc->m140((ContactBody_174808*)self, &msg);
            }
        }
        FreePooledContactChain((World*)self->world, *(Contact03**)self->contactChainHead);
        *(Contact03**)self->contactChainHead = 0;
    }
    UpdatePlayerSpin(self);
    PosePlayerTargetPart(self);
    RecordPlayerTargetMemo(self);
    RunPlayerQueuedActivations(self);
}

void UpdatePlayerWhileAnimationDriven(Player* self)
{
    switch (self->state) {
    case 3:
        SetPlayerState(self, 2, 2);
        break;
    case 0xD:
        SetPlayerState(self, 0xD, 0x38);
        break;
    }
    s32 state = self->state;
    SetPlayerAimMode(self, -1);
    switch (state) {
    case 2:
    case 3:
    case 13:
    case 14:
    case 15:
    case 16:
        break;
    case 4:
    case 12:
        Vu0::Q(self->headingVelocity) = Vu0::Zero();
        break;
    default: {
        f32 heading;
        f32 speed;
        state = 0;
        ComputeObjectSteeringHeading(g_frameDt[0], self->heading, self, 0, 0, &heading, 0, &speed);
        if (speed > 0.0f) {
            state = 1;
        }
        self->heading = heading;
        Vu0::Q(self->headingVelocity) = Vu0::FromFloats(-speed, 0.0f, 0.0f);
        SetPlayerState(self, state, -1);
    }
    }
}


void SetTurningColliderFollowedMesh(TurningCollider* self, Collider* other, s32 all);

void SelectPlayerStateAnimation(Player* self)
{
    void* node;
    switch (self->state) {
    case 6: {
        s32 m = self->targetMode;
        if ((m == 0 && self->subState == 0x15) || m == 7) {
            node = self->specialNode;
        } else {
            node = self->targetModeNodes[m];
        }
        break;
    }
    case 4: {
        s32 i = self->subState;
        if (i != -1) {
            node = self->subStateNodes[i];
            if (node == 0) {
                do {
                    s32 k = D_00263930[i - 0x24];
                    if (k == -1) {
                        break;
                    }
                    node = self->subStateNodes[k];
                    i = k;
                } while (node == 0);
            }
        }
        break;
    }
    case 2: {
        s32 i = self->subState;
        if (i < 0xE) {
            if (i >= 0xC) {
                node = self->specialNode;
                break;
            }
        }
    }
    default:
        node = self->stateNodes[self->state];
        break;
    case 0xD:
        return;
    }
    if (node == 0) {
        node = self->stateNodes[0];
    }
    SetTurningColliderFollowedMesh(self, (Collider*)node, 0);
}

struct Dev_175078 {
    u8 pad_00[0x10];
    s8 f10;
};

void SetPlayerPartLayers(Player* self, s32 flags)
{
    if (self->f2500 != 0) {
        s32 a = flags & 1;
        ((Dev_175078*)self->f2500)->f10 = a ? 9 : -1;
        ((Dev_175078*)self->f2504)->f10 = a ? 9 : -1;
        ((Dev_175078*)self->f2508)->f10 = a ? 9 : -1;
        s32 b = flags & 2;
        ((Dev_175078*)self->footPartA)->f10 = b ? 9 : -1;
        ((Dev_175078*)self->footPartB)->f10 = b ? 9 : -1;
        PlacedObject* o = self->rigObject;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->f618;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->f61C;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->f610;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->f614;
        o->desc02()->m2B(o);
    }
}





void CreateAnimationPlayer(Animation* self, BaseObject* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void InitContactPairFlags(World* self, Collider* obj);
void PushCameraController(Camera* self, s32 key, CameraController* ctl, void* target, void* arg);
void RemoveCameraControllers(Camera* self, s32 flags, s32 k0, CameraController* k1, void* k2, void* k3);
void RequestCameraSnap(Camera* self, f32* src);
void StartCameraSounds(CameraSoundOwner* self);
void SendEmptyMessage(MemberObject* a0);
void SetPooledObjectPlayerHold(PooledObject* self, s32 v);
void ComputePlayerJumpVelocity(Player* self, Vec02* out);
void ComputeUpwardBoostVelocity(PlacedObject* self, Vec02* out);
void ComputeUpwardBoostVelocityUnitSlope(PlacedObject* self, Vec02* out);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void ActivateSwitchedCollider(void* obj);
void DestroyStateWalker(StateWalker* self);
void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);
void AddColliderAttachment(Collider* o, Attach03* node);
void RemoveColliderAttachment(Collider* o, Attach03* node);
void SetColliderTreeContactsDropped(Collider* self, s32 value);
SoundLevelEntry* PushSoundLevel(s32 level);
void ReleaseSoundLevel(SoundLevelEntry* self);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void SetTurningColliderLinkFlag(TurningCollider* self, s32 a1);
void TurnColliderTowardHeading(TurningCollider* self);
void TurnPlayerToClass75AheadMask8(Player* self);
void TurnPlayerToClass75AheadMask4(Player* self);
void PlacePlayerOnLinkedObject(Player* self);
void SetFlaggedLinkContactMask(Collider* self, BaseObject* node, s32 flag);
void GetLinkedObjectHeading(Player* self, f32* heading);
void ComputePlayerLinkPose(Player* self, Vec02* pos, Mat02* rotA, Mat02* rotB);
s32 HasNoActiveObject89(Player* self);
void TakeCountedColliderTouch(CountedCollider* self, void* v, s32 flag);
Attach03* TakeAttachRecord(World* self);
void ReleaseAttachRecords(World* self, Attach03* node);
void PopActiveSequenceElement(World* world);
void SetOnOffObjectForcedState(void* p, s32 n);
void ComputePolarOffset(Vec3* out, f32 unused, f32 scale, f32 z);

extern s32 D_00270454;
extern f32 D_00274F00;
extern f32 D_00274F04;
extern f32 g_steepSlopeThreshold;
extern f32 D_00274F14;

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
void SetPlayerAimMode(Player* self, s32 state);
void SetTurningColliderFollowedMesh(TurningCollider* self, Collider* other, s32 all);
s32 FindStateEntryIndex(StateGraph* self, s32 key);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
s32 IsObjectAttached(BaseObject* self);
void ResetPlayerOnOffObject(Player* self);
void ReleaseFarPlayerLinks(Player* self);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
f32 GetAnimationMarkerTime(Animation* self, s32 key);
void BuildPerpendicularPair(Vec02* dir, Vec02* out, const Vec02* a, const Vec02* b);
void StopAnimationPlayer(AnimationPlayer* self);
s32 MaskWorldBitsBySave(void);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
void ResetTrailRing(TrailRing* o);
void PushStackElement(ElementStack* self, ScreenElement* node);
f32 WrapAngle(f32 a);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

static inline void StopPlayerAnimation(Player* self)
{
    if (self->stateAnimPlayer != 0) {
        StopAnimationPlayer((AnimationPlayer*)self->stateAnimPlayer);
        self->stateAnimPlayer = 0;
    } else if (self->stateWalker != 0) {
        DestroyStateWalker((StateWalker*)self->stateWalker);
        self->stateWalker = 0;
    }
}

// A 16-byte vector in memory as a Vu0::Vec to store to: a structure's store, which the scheduler
// keeps apart from a global scalar's load (docs/TOOLCHAIN.md, "Alias classes in the schedule").
template <class T>
static inline Vu0::Vec& AsVec_175170(T& v)
{
    return *(Vu0::Vec*)&v;
}

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

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))

void SetPlayerState(Player* self, s32 state, s32 sub)
{
    void* walker;
    s32 sound = -1;
    f32 start = 0.0f;
    void* anim = 0;
    f32 speed = 1.0f;
    s32 flag = 1;
    s32 layers = 0;
    s32 walkerId = -1;
    s32 skip = 0;
    walker = 0;

    if (self->state == state && self->subState == sub) {
        return;
    }
    self->pendingFlags &= ~1;
    if (self->state != state) {
        switch (self->state) {
        case 2: {
            self->penalizedTarget = 0;
            if (state != 3 && state != 7) {
                StartSoundEffect(0x49, 0, self, 0, 1000.0f, 500.0f, 0.7f, 0.0f, 0.0f, 0, 0);
            }
            self->jumpKind = -1;
            if (self->aimMode == 0 && state != 7 && state != 3) {
                SetPlayerAimMode(self, -1);
            }
            if (self->f2438 == 0) {
                void* m = 0;
                switch (state) {
                case 6:
                    switch (self->targetMode) {
                    case 4:
                    case 5:
                        m = self->f2720;
                        break;
                    case 0:
                    case 1:
                    case 3:
                    case 6:
                    case 7:
                        m = self->f271C;
                        break;
                    }
                    break;
                case 0:
                case 1:
                case 5:
                case 9:
                case 10:
                case 12:
                    m = self->f271C;
                    break;
                }
                if (m != 0) {
                    SendEmptyMessage((MemberObject*)m);
                }
            }
            if (!(MaskWorldBitsBySave() & 0x1000)) {
                self->slowDownHeld = 0;
            }
            break;
        }
        case 5:
            self->eightWayHalf = -1;
            break;
        case 3: {
            if (state == 2) {
                self->penalizedTarget = (void*)self->boundObject;
            }
            TriggerScriptEvent((BaseObject*)self->boundObject, 3, 0, 0);
            BaseObject* o = (BaseObject*)self->boundObject;
            o->desc->m18(o, self);
            self->previousBoundObject = self->boundObject;
            SetPlayerAimMode(self, -1);
            ((Attachment*)self->f251C)->mode0 = -1;
            ((Attachment*)self->f251C)->mode1 = -1;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            ((Attachment*)self->f2520)->mode1 = -1;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            SetTurningColliderLinkFlag(self, 1);
            if (self->linkSystem != 0) {
                RemoveColliderAttachment(((Attach03*)self->linkSystem)->target, (Attach03*)self->linkSystem);
                ReleaseAttachRecords((World*)self->world, (Attach03*)self->linkSystem);
                self->linkSystem = 0;
            }
            ResetTrailRing((TrailRing*)self->trail);
            break;
        }
        case 7: {
            if (state == 2) {
                self->penalizedTarget = (void*)self->aimCurve;
            }
            TriggerScriptEvent((BaseObject*)self->aimCurve, 3, 0, 0);
            BaseObject* o = (BaseObject*)self->aimCurve;
            o->desc->m18(o, self);
            SetFlaggedLinkContactMask(self, (BaseObject*)self->aimCurve, 0);
            self->previousAimCurve = self->aimCurve;
            self->f2218 = self->aimCurvePos;
            s32 aim = -1;
            if (state == 2 && self->aimAnim11 != 0) {
                aim = 11;
            }
            SetPlayerAimMode(self, aim);
            Vu0::Q(self->poseOffset) = Vu0::Sub(Vu0::Q(self->focusPoint), Vu0::Q(self->pos));
            self->poseOffset.z = 0.0f;
            ResetTrailRing((TrailRing*)self->trail);
            break;
        }
        case 8:
            SetFlaggedLinkContactMask(self, (BaseObject*)self->ledgeCollider, 0);
            self->ledgeCollider = 0;
            break;
        case 4:
            self->f23DC = -1;
            if (self->f2490 != 0) {
                AT(Vec02, self->f2490, 0x300) = D_00248D30;
            }
            if (self->f2494 != 0) {
                AT(Vec02, self->f2494, 0x300) = D_00248D30;
            }
            self->f580 = 1;
            ResetTrailRing((TrailRing*)self->trail);
            self->pulseFadeStart = g_gameTime[0];
            break;
        case 6: {
            switch (self->targetMode) {
            case 2:
                StopPlayerAnimation(self);
                StartSoundEffect(0x4E, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                SetPooledObjectPlayerHold((PooledObject*)self->heldObject, 0);
                break;
            case 5:
                TriggerScriptEvent((BaseObject*)self->targetNode, 3, 0, 0);
                ((BaseObject*)self->targetNode)->desc->m18((BaseObject*)self->targetNode, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)self->targetNode, 0);
                self->heldObject = 0;
                break;
            case 4:
                TriggerScriptEvent((BaseObject*)self->targetTrack, 3, 0, 0);
                ((BaseObject*)self->targetTrack)->desc->m18((BaseObject*)self->targetTrack, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)self->targetTrack, 0);
                self->heldObject = 0;
                break;
            case 6:
                if (self->aimMode == 0 && state != 7 && state != 3) {
                    SetPlayerAimMode(self, -1);
                }
                break;
            case 7: {
                PlacedObject* o = (PlacedObject*)self->targetSwitch;
                self->heading = WrapAngle(ArctangentOfRatio(o->m110.r[0].y, o->m110.r[0].x) + 1.0f);
                self->targetSwitch = 0;
                break;
            }
            case 3:
            default:
                self->heldObject = 0;
                break;
            }
            if (state == 2) {
                if (self->targetCurve != 0) {
                    self->penalizedTarget = self->targetCurve;
                } else if (self->targetPoint != 0) {
                    self->penalizedTarget = self->targetPoint;
                } else if (self->targetNode != 0) {
                    self->penalizedTarget = self->targetNode;
                } else if (self->targetTrack != 0) {
                    self->penalizedTarget = self->targetTrack;
                } else {
                    self->penalizedTarget = 0;
                }
            }
            self->eightWayHalf = -1;
            self->targetMode = -1;
            self->targetCurve = 0;
            self->targetPoint = 0;
            self->targetNode = 0;
            self->targetTrack = 0;
            if (self->forcedOnOffObject != 0) {
                SetOnOffObjectForcedState((void*)self->forcedOnOffObject, 0);
                self->forcedOnOffObject = 0;
            }
            self->f268C = 0;
            if (self->f26A4 != 0) {
                ReleaseSoundLevel((SoundLevelEntry*)(self->f26A4));
                self->f26A4 = 0;
            }
            BaseObject* o = self->f272C;
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
            self->aimTarget = 0;
            self->boundObject = 0;
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 12:
            RemoveCameraControllers(g_camera, 0xF, 6, (CameraController*)((u8*)g_camera + 0x460), self, 0);
            if (D_00270454 != 0) {
                PopStackElement((ElementStack*)g_elementStack);
            }
            break;
        case 9:
            self->walkerHost = 0;
            self->desc05()->m4F(self, 0);
            break;
        case 0:
            switch (self->aimMode) {
            case 6:
                SetPlayerAimMode(self, 4);
                break;
            case 7:
                SetPlayerAimMode(self, 5);
                break;
            case 8:
            case 9:
                SetPlayerAimMode(self, -1);
                break;
            }
            break;
        case 1:
            break;
        case 13:
            self->flags538 &= ~((u64)1 << 40);
            self->hook = self->f273C;
            if (self->stateNodes[13] != 0) {
                SetTurningColliderFollowedMesh(self, (Collider*)self->stateNodes[13], 1);
            }
            break;
        }

        switch (state) {
        case 0:
            walkerId = 0x146;
            self->f118C = 0;
            walker = self->stateGraph;
            if (self->state == 2) {
                s32 late = self->f2250;
                if (late == -1) {
                    f32 limit = 0.95f;
                    if (self->subState == 3) {
                        limit = 1.25f;
                    }
                    late = limit < g_gameTime[0] - self->stateStartTime;
                }
                if (late == 1 && FindStateEntryIndex((StateGraph*)walker, 0x14A)) {
                    walkerId = 0x14A;
                } else if (FindStateEntryIndex((StateGraph*)walker, 0x149)) {
                    walkerId = 0x149;
                }
            }
            layers = 3;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        case 1:
            anim = (void*)self->sixWayBlend;
            break;
        case 5:
            anim = (void*)self->eightWayBlend;
            break;
        case 2:
            if (self->jumpKind == -1) {
                self->jumpKind = 0;
            }
            self->f2250 = -1;
            self->f2498 = 0;
            self->f249C = 3.40282347e+38f;
            break;
        case 3: {
            self->linkReturnState = -1;
            self->linkTowardRamp = self->linkMoveRamp = 1.0f;
            anim = self->linkBlend;
            self->linkPushTime = g_gameTime[0];
            start = 0.5f;
            SetTurningColliderLinkFlag(self, 0);
            speed = 0.0f;
            ((Attachment*)self->f251C)->mode0 = 2;
            ((Attachment*)self->f251C)->mode1 = 2;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            ((Attachment*)self->f2520)->mode1 = 2;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            Vec02 pos;
            Mat02 rotA;
            Mat02 rotB;
            f32 heading;
            ComputePlayerLinkPose(self, &pos, &rotA, &rotB);
            Vu0::Q(self->f22F0) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->f61C)->pos), Vu0::Q(pos));
            MultiplyMatrices3x3(&rotA, &((PlacedObject*)self->f61C)->rot, &self->f2300);
            MultiplyMatrices3x3(&rotB, &((PlacedObject*)self->f23D0)->rot, &self->f2330);
            TriggerScriptEvent((BaseObject*)self->boundObject, 2, 0, 0);
            BaseObject* o = (BaseObject*)self->boundObject;
            o->desc->m17(o, self);
            GetLinkedObjectHeading(self, &heading);
            f32 back = WrapAngle(heading + 3.14159274f);
            s32 kind = 1;
            if (self->boundObject != 0) {
                kind = AT(s32, self->boundObject, 0xA0);
            }
            switch (kind) {
            case 2:
                self->heading = back;
                self->linkReversed = 1;
                break;
            case 1:
                self->heading = heading;
                self->linkReversed = 0;
                break;
            case 0:
                if (__builtin_fabsf(WrapAngle(heading - self->stickHeading)) < 1.57079637f) {
                    self->heading = heading;
                    self->linkReversed = 0;
                } else {
                    self->heading = back;
                    self->linkReversed = 1;
                }
                break;
            }
            u128 zero = Vu0::Zero();
            sound = AT(s32, self->boundObject, 0xA8);
            SetPlayerAimMode(self, 1);
            for (Collider* c = (Collider*)AT(BaseObject*, self->boundObject, 0x18); c != 0; c = (Collider*)c->parent) {
                if (c->desc->flags & 2) {
                    if ((c->mode450 != 3 && c->positionAttachment != 0 && c->positionAttachment->mode0 == 1) ||
                        (c->mode470 != 3 && c->orientationAttachment != 0 && c->orientationAttachment->mode1 == 1)) {
                        Attach03* a = TakeAttachRecord((World*)self->world);
                        a->owner = self;
                        a->target = c;
                        AddColliderAttachment(c, a);
                        self->linkSystem = a;
                        break;
                    }
                }
            }
            Vu0::Q(self->headingVelocity) = zero;
            PlacePlayerOnLinkedObject(self);
            break;
        }
        case 7: {
            TriggerScriptEvent((BaseObject*)self->aimCurve, 2, 0, 0);
            BaseObject* o = (BaseObject*)self->aimCurve;
            o->desc->m17(o, self);
            SetFlaggedLinkContactMask(self, (BaseObject*)self->aimCurve, 1);
            self->pathStickSide = -1;
            void* track = (void*)self->aimCurve;
            TrackShape_175170* s = AT(TrackShape_175170*, track, 0x34);
            s32 turn = AT(s32, track, 0x58);
            Vec02 a;
            Vec02 b;
            switch (turn) {
            case 0:
                self->pathFlipped = 0;
                break;
            case 1:
                self->pathFlipped = 1;
                break;
            default: {
                if (s->desc->m2 != 0) {
                    s->desc->m2(s, self->pathPos + D_00274F14, &a, 0);
                    if (s->desc->m2 != 0) {
                        s->desc->m2(s, self->pathPos - D_00274F14, &b, 0);
                    }
                }
                TransformPointBetweenFrames((PlacedObject*)(AT(void*, self->aimCurve, 0x18)), 0, &a, &a);
                TransformPointBetweenFrames((PlacedObject*)(AT(void*, self->aimCurve, 0x18)), 0, &b, &b);
                Vec02 d;
                *(u128*)&d = NormalizeOrElse_175170(Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b)), Vu0::Vec::Of(g_unitZVector)).q;
                self->pathFlipped = d.z < -g_steepSlopeThreshold;
                break;
            }
            }
            f32 len = self->aimCurvePos;
            self->pathPos = len;
            if (s->looped == 0) {
                if (self->pathFlipped != 0) {
                    self->pathPos = Clamp_175170(len, s->lengths[0] + D_00274F00, s->lengths[s->count - 1] - D_00274F04);
                } else {
                    self->pathPos = Clamp_175170(len, s->lengths[0] + D_00274F04, s->lengths[s->count - 1] - D_00274F00);
                }
            }
            if (s->desc->m2 != 0) {
                s->desc->m2(s, self->pathPos, &a, 0);
            }
            TransformPointBetweenFrames((PlacedObject*)(AT(void*, self->aimCurve, 0x18)), 0, &a, &a);
            TransformPointBetweenFrames(self, 0, (Vec02*)&self->f23E0, &b);
            Vu0::Q(self->pathPoseOffset) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
            sound = AT(s32, self->aimCurve, 0x50);
            Vu0::Q(self->poseOffset) = Vu0::Sub(Vu0::Q(self->focusPoint), Vu0::Q(a));
            break;
        }
        case 8: {
            SetPlayerAimMode(self, -1);
            sound = 0x59;
            SetFlaggedLinkContactMask(self, (BaseObject*)self->ledgeCollider, 1);
            Vec02 pos;
            Mat02 m;
            Vec02 k;
            TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec02*)self->ledgeLocalPoint, &pos);
            Vu0::Q(k) = Vu0::FromFloat(-1.0f);
            Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->ledgeOffset), Vu0::Q(k));
            BuildPerpendicularPair(&m.r[0], &m.r[1], &g_unitZVector, &g_unitZVector);
            Vu0::Q(pos) = Vu0::Sub(Vu0::Q(pos), Vu0::Rotate(m, Vu0::Q(self->ledgeHandOffset)));
            anim = self->f1038;
            Vu0::Q(self->ledgeSlack) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(pos));
            self->pathPoseOffset = D_00248D30;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        }
        case 4:
            if (self->f2490 != 0) {
                AT(Vec02, self->f2490, 0x300) = *(Vec02*)D_00263970;
            }
            if (self->f2494 != 0) {
                AT(Vec02, self->f2494, 0x300) = *(Vec02*)D_00263970;
            }
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            SetPlayerAimMode(self, -1);
            self->f580 = 0;
            self->pulseFadeStart = 3.40282347e+38f;
            break;
        case 6: {
            s32 loud = 0;
            switch (self->targetMode) {
            case 2:
                StopPlayerAnimation(self);
                StartSoundEffect(0x4D, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                loud = 1;
                SetPooledObjectPlayerHold((PooledObject*)self->heldObject, 1);
                break;
            case 5:
                TriggerScriptEvent((BaseObject*)self->targetNode, 2, 0, 0);
                ((BaseObject*)self->targetNode)->desc->m17((BaseObject*)self->targetNode, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)self->targetNode, 1);
                layers = 1;
                break;
            case 4: {
                void* track = self->targetTrack;
                layers = 1;
                TriggerScriptEvent((BaseObject*)track, 2, 0, 0);
                ((BaseObject*)track)->desc->m17((BaseObject*)track, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)track, 1);
                self->pathStickSide = -1;
                Vec02 dir;
                Vec02 tan;
                TrackShape_175170* s = AT(TrackShape_175170*, track, 0x34);
                if (s->desc->m1 != 0) {
                    s->desc->m1(s, self->trackPos, 0, &tan);
                }
                TransformDirectionBetweenFrames((PlacedObject*)(AT(void*, track, 0x18)), 0, &tan, &dir);
                dir.z = 0.0f;
                AsVec_175170(dir) = NormalizeOrElse_175170(Vu0::Vec::Of(dir), Vu0::Vec::Of(g_unitXVector));
                s32 back = 1;
                if (!(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->m110.r[0]))) < D_00263990)) {
                    back = 0;
                }
                self->trackReversed = back;
                break;
            }
            case 7:
                self->desc02()->m20(self, (Vec02*)&D_00248D30);
                loud = 1;
                self->desc02()->m21(self, (Vec02*)&D_00248D30);
                Vu0::Q(self->headingVelocity) = Vu0::Zero();
                ActivateSwitchedCollider(self->targetSwitch);
                break;
            case 3: {
                BaseObject* o = self->f272C;
                if (o != 0) {
                    o->desc->m02(o);
                    loud = 1;
                }
                if (HasNoActiveObject89(self)) {
                    StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect94Volume, 0.0f, 0.0f, 0, 0);
                } else {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
                break;
            }
            case 0:
            case 1:
                loud = 1;
                if (self->state != 2 || (self->subState != 12 && self->subState != 13)) {
                    StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect94Volume, 0.0f, 0.0f, 0, 0);
                }
                break;
            }
            self->onOffPhase = -1;
            if (loud) {
                self->f26A4 = PushSoundLevel(-20);
            }
            break;
        }
        case 9: {
            Vec02 d;
            if (self->walkerHost != 0) {
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->walkerHost)->v140), Vu0::Q(g_player->v140));
            } else {
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(g_player->v140));
            }
            self->heading = ArctangentOfRatio(d.y, d.x);
            TurnColliderTowardHeading(self);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            SetPlayerAimMode(self, -1);
            break;
        }
        case 11:
            SetPlayerAimMode(self, -1);
            SetColliderAnchors(self, 3, 0, 3, 0);
            SetColliderTreeContactsDropped(self, 1);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->groundContact = 0;
            break;
        case 10:
            SetPlayerAimMode(self, -1);
            self->foundNodeCount = 0;
            TurnPlayerToClass75AheadMask8(self);
            break;
        case 12:
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        case 13:
            self->f273C = self->hook;
            self->hook = 0;
            self->flags538 |= (u64)1 << 40;
            self->radius3CC = D_00262E30;
            if (self->stateNodes[13] != 0) {
                SetTurningColliderFollowedMesh(self, 0, 0);
            }
            self->headingVelocity = D_00248D30;
            SetPlayerAimMode(self, -1);
            break;
        case 16:
            self->headingVelocity = D_00248D30;
            break;
        case 14: {
            BaseObject* o = (BaseObject*)self->contactOwner;
            if (IsObjectAttached(o)) {
                TakeCountedColliderTouch((CountedCollider*)self->contactOwner, self, 1);
            }
            o = (BaseObject*)self->contactOwner;
            o->desc->m02(o);
            o = (BaseObject*)self->contactOwner;
            o->desc->m15(o, self);
            o = (BaseObject*)self->contactOwner;
            o->desc->m03(o);
            anim = self->f274C;
            self->headingVelocity = D_00248D30;
            break;
        }
        case 15:
            anim = self->f2754;
            self->headingVelocity = D_00248D30;
            break;
        }
        ReleaseFarPlayerLinks(self);
    }

    if (self->subState != sub) {
        switch (self->subState) {
        case 17:
            self->eightWayHalf = -1;
            break;
        case 5: {
            Collider* held = (Collider*)self->heldObject;
            self->heldObject = 0;
            InitContactPairFlags(held->world, held);
            break;
        }
        case 4:
            if (state != 6 || self->targetMode != 2) {
                Collider* held = (Collider*)self->heldObject;
                self->heldObject = 0;
                InitContactPairFlags(held->world, held);
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            self->headingVelocity = D_00248D30;
            break;
        case 9:
            if (self->leapTarget != 0) {
                Collider* c = AT(Collider*, self->leapTarget, 0x60);
                if (c != 0) {
                    c->partMode = 0;
                }
                self->leapTarget = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            self->headingVelocity = D_00248D30;
            break;
        case 10:
            if (state != 6 || self->targetMode != 5) {
                self->targetNode = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 11:
            if (state != 6 || self->targetMode != 4) {
                self->targetTrack = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 13:
            if (state != 6 || self->targetMode != AT(s32, self->targetPoint, 0x58)) {
                self->targetPoint = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 12:
            if (state != 6 || self->targetMode != AT(s32, self->targetCurve, 0x40)) {
                self->targetCurve = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 7:
        case 8: {
            if (self->aimMode == -1) {
                self->aimTarget = 0;
                self->boundObject = 0;
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
            FillMemory(&self->touchedObject, 0, 0x20);
        case 14:
        case 15:
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 23:
            if (state == 7) {
                SetPlayerAimMode(self, self->aimAnim10 != 0 ? 10 : 2);
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
            AT(Vec02, self->f2490, 0x300) = D_00248D30;
            break;
        case 28:
            if (self->forcedOnOffObject != 0) {
                SetOnOffObjectForcedState((void*)self->forcedOnOffObject, 0);
                self->forcedOnOffObject = 0;
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
            self->steerKeepsDirection = 0;
            self->f2498 = 1;
            self->jumpStickPhase = 0;
            f32 now = g_gameTime[0];
            self->stickReleaseTime = now;
            self->stickFullTime = now;
            self->jumpStartTime = now;
            self->jumpSpeed = D_00262E14 * Fpu::Sqrt(self->gravityScale);
            self->groundContact = 0;
            StartSoundEffect(0x4F, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            ComputePlayerJumpVelocity(self, &v);
            switch (self->jumpKind) {
            case 1:
                anim = self->f1028;
                break;
            case 4:
                self->jumpSpeed *= D_00262E1C;
                anim = self->f1028;
                break;
            case 3:
                self->jumpSpeed *= D_00262E18;
                anim = self->f1028;
                break;
            case 0:
            case 2:
                if (self->jumpKind == 2) {
                    anim = self->f1024;
                } else {
                    anim = self->f1020;
                }
                break;
            }
            if (anim == 0) {
                anim = self->f1020;
            }
            if (self->jumpKind == 4 && self->stickLevel == 0.0f) {
                ComputePolarOffset((Vec3*)&v, self->heading, 100.0f, v.z);
                self->jumpStickPhase = 3;
            } else {
                ComputePolarOffset((Vec3*)&v, self->stickHeading, self->jumpSpeed * self->stickLevel, v.z);
            }
            self->desc02()->m20(self, &v);
            break;
        }
        case 1:
            skip = 1;
            break;
        case 2:
            if (self->subState != 1 && self->subState != 5) {
                switch (self->jumpKind) {
                case 1:
                case 3:
                case 4:
                    anim = self->f1028;
                    break;
                case 0:
                    anim = self->f1020;
                    break;
                case 2:
                    anim = self->f1024;
                    break;
                }
                start = GetAnimationMarkerTime((Animation*)anim, 0x134);
            } else {
                skip = 1;
            }
            break;
        case 4:
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            if (self->state == 2) {
                skip = 1;
            } else {
                anim = self->f1020;
            }
            InitContactPairFlags(((Collider*)self->heldObject)->world, (Collider*)self->heldObject);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        case 9: {
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            // The same if/else as case 4's: here anim is set again below, so the else is dead and
            // flow deletes it, but it keeps jump.c from turning a lone `skip = 1` into a
            // conditional move, as retail's branch shows (docs/TOOLCHAIN.md, "Conditional moves").
            if (self->state == 2) {
                skip = 1;
            } else {
                anim = self->f1020;
            }
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            Collider* c = AT(Collider*, self->leapTarget, 0x60);
            anim = self->f1030;
            if (c != 0) {
                c->partMode = 3;
            }
            break;
        }
        case 10:
        case 11: {
            Vec02 v;
            ComputeUpwardBoostVelocity(self, &v);
            self->desc02()->m20(self, &v);
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            anim = self->f1030;
            self->f2498 = 0;
            AsVec_175170(self->headingVelocity) = Vu0::Vec::Zero();
            StartSoundEffect(0x50, 0, 0, 0, 3000.0f, 300.0f, D_00263994, D_00263998, 0.0f, 0, 0);
            break;
        }
        case 12:
        case 13:
        case 14:
        case 15:
            skip = 1;
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->f2498 = 0;
            if (sub == 12 || sub == 13) {
                StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect94Volume, 0.0f, 0.0f, 0, 0);
            }
            break;
        case 5: {
            Vec02 v;
            anim = self->fE2C;
            Vu0::Q(v) = Vu0::Add(Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::Scalar(Fpu::Sqrt(self->gravityScale) * 800.0f)), Vu0::Q(self->v150));
            self->desc02()->m20(self, &v);
            self->f2498 = 1;
            break;
        }
        case 6:
            self->f2498 = 1;
            self->steerKeepsDirection = 1;
            self->jumpStickPhase = 2;
            self->jumpSpeed = D_00262E14 * Fpu::Sqrt(self->gravityScale);
            self->v2290 = self->v150;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->groundContact = 0;
            anim = self->f1020;
            self->v2290.z = 0.0f;
            break;
        case 44:
            self->f2498 = 1;
            self->groundContact = 0;
            if (self->f2730 != 0) {
                anim = self->subStateAnims[43];
            } else {
                anim = self->f1020;
            }
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            if (self->touchedObject != 0 && IsObjectOfKind((BaseObject*)self->touchedObject, 0x70)) {
                self->heading = ArctangentOfRatio(self->v150.y, self->v150.x);
                TurnColliderTowardHeading(self);
            }
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            SetColliderTreeContactsDropped(self, 1);
            self->groundContact = 0;
            break;
        case 7:
            self->foundNodeCount = 0;
            self->steerKeepsDirection = 1;
            sound = 10;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            anim = self->f25C0;
            TurnPlayerToClass75AheadMask4(self);
            self->aimEndTime = g_gameTime[0] + D_0026399C;
            break;
        case 8:
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->steerKeepsDirection = 1;
            self->foundNodeCount = 0;
            anim = self->markerAnim;
            break;
        case 3: {
            Vec02 v;
            self->f2498 = 0;
            anim = self->f1034;
            ComputeUpwardBoostVelocityUnitSlope(self, &v);
            self->desc02()->m20(self, &v);
            break;
        }
        case 16:
        case 21:
            switch (self->targetMode) {
            case 0:
                anim = self->fB24;
                break;
            case 2:
                anim = self->fE24;
                break;
            case 1:
            case 3:
                anim = self->fC34;
                break;
            case 5:
                walker = self->stateGraph;
                walkerId = 0x14C;
                break;
            case 4:
                if (AT(s32, self->targetTrack, 0x40) != 0 && self->pathLeanBlend != 0) {
                    anim = self->pathLeanBlend;
                    self->pathLean = self->pathLeanRate = 0.0f;
                } else {
                    walker = self->stateGraph;
                    walkerId = 0x14D;
                }
                layers = 3;
                break;
            case 6:
                anim = self->f1014;
                break;
            case 7:
                anim = 0;
                break;
            }
            break;
        case 17:
            switch (self->targetMode) {
            case 0:
                speed = 2.0f;
                anim = self->eightBlendB;
                if (self->forcedOnOffObject == 0) {
                    if (self->targetCurve != 0) {
                        void* o = self->targetCurve;
                        if (AT(s32, o, 0x4C) == 0) {
                            self->forcedOnOffObject = 0;
                        } else if (AT(s32, o, 0x48) != 0) {
                            self->forcedOnOffObject = AT(s32, o, 0x48);
                        } else {
                            self->forcedOnOffObject = (s32)self->ownOnOffObject;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                            p->desc->m15(p, AT(BaseObject*, self->targetCurve, 0x18));
                            ((OnOffObject*)self->forcedOnOffObject)->obj = AT(Arr63*, self->targetCurve, 0x34);
                        }
                    } else if (self->targetPoint != 0) {
                        void* o = self->targetPoint;
                        if (AT(s32, o, 0x68) == 0) {
                            self->forcedOnOffObject = 0;
                        } else if (AT(s32, o, 0x64) != 0) {
                            self->forcedOnOffObject = AT(s32, o, 0x64);
                        } else {
                            self->forcedOnOffObject = (s32)self->ownOnOffObject;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                            p->desc->m15(p, AT(BaseObject*, self->targetPoint, 0x18));
                            ((OnOffObject*)self->forcedOnOffObject)->f38C = 1;
                            ((OnOffObject*)self->forcedOnOffObject)->v400 = AT(Vec02, self->targetPoint, 0x40);
                            ((OnOffObject*)self->forcedOnOffObject)->orbitRadius = AT(f32, self->targetPoint, 0x5C);
                        }
                    }
                    if ((OnOffObject*)self->forcedOnOffObject == self->ownOnOffObject) {
                        const Vec02* z = &D_00248D30;
                        OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m1D(p, (Vec02*)z);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m1E(p, (Mat02*)&g_identityMatrix);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m20(p, (Vec02*)z);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m21(p, (Vec02*)z);
                    }
                    if (self->forcedOnOffObject != 0) {
                        ((OnOffObject*)self->forcedOnOffObject)->switchedCollider = self;
                        SetOnOffObjectForcedState((void*)self->forcedOnOffObject, 1);
                    }
                }
                break;
            case 1:
                speed = 1.75f;
                anim = self->eightBlendC;
                break;
            case 3:
                anim = (void*)self->eightWayBlend;
                break;
            }
            break;
        case 20:
            switch (self->targetMode) {
            case 2:
                anim = self->sixBlendB;
                break;
            case 3:
                anim = (void*)self->sixWayBlend;
                break;
            case 4:
                anim = self->sixBlendC;
                break;
            }
            break;
        case 19:
            switch (self->targetMode) {
            case 0:
                anim = self->fB2C;
                break;
            case 1:
                anim = self->fC3C;
                break;
            }
            break;
        case 18:
            switch (self->targetMode) {
            case 0:
                anim = self->fB28;
                break;
            case 1:
                anim = self->fC38;
                break;
            }
            break;
        case 23:
            anim = self->f1060;
            if (anim == 0) {
                anim = self->f1068;
                start = ((Animation*)anim)->length * 0.5f;
                speed = 0.5f;
            }
            self->pathSpeedEased = 0.0f;
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
            anim = self->f1068;
            self->pathFlipped = !self->pathFlipped;
            break;
        case 28:
        case 29:
        case 30:
            anim = self->subStateAnims[sub];
            if (sub == 28 && self->f267C != 0) {
                self->forcedOnOffObject = (s32)self->f267C;
                SetOnOffObjectForcedState(self->f267C, 1);
            }
            if (sub == 30) {
                self->desc05()->m4F(self, 3);
            }
            PopActiveSequenceElement(self->world);
            break;
        case 31:
            anim = self->f25B8;
            sound = 14;
            break;
        case 32:
            anim = self->f25BC;
            break;
        case 33:
            if ((void*)self->f25CC != 0) {
                anim = (void*)self->f25CC;
            }
            PushCameraController(g_camera, 6, (CameraController*)((u8*)g_camera + 0x460), self, 0);
            break;
        case 34: {
            f32 dim = 0.6f;
            SetVolumeChannelFactor(5, 0, dim);
            SetVolumeChannelFactor(5, 1, dim);
            StartCameraSounds((CameraSoundOwner*)((u8*)g_camera + 0x460));
            RequestCameraSnap(g_camera, 0);
            g_typedTextCaptionBox.child = self->pendingCaption;
            self->pendingCaption = 0;
            PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
            break;
        }
        case 35:
            if ((void*)self->f25D0 != 0) {
                anim = (void*)self->f25D0;
            }
            RemoveCameraControllers(g_camera, 0xF, 6, (CameraController*)((u8*)g_camera + 0x460), self, 0);
            RequestCameraSnap(g_camera, 0);
            break;
        case 39:
        case 45:
        case 46:
        case 47:
            if (sub == 45) {
                u128 vel = Vu0::Q(self->v150);
                if (-250.0f < Vu0::ToFloatMoved(Vu0::Dot(vel, Vu0::Q(self->headingMatrix.r[0])))) {
                    sub = 46;
                } else {
                    f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(vel, vel)));
                    f32 k = D_002639A0[0] + len * (D_002639A0[1] + len * D_002639A0[2]);
                    f32* range = (f32*)&g_unitRange;
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
                    self->heading = WrapAngle(self->heading + WrapAngle(ArctangentOfRatio(self->v150.y, self->v150.x) + 3.14159274f - self->heading) * r);
                    TurnColliderTowardHeading(self);
                }
            }
            anim = self->subStateAnims[sub];
            if (sub == 47 || sub == 39) {
                if (self->f2490 != 0) {
                    AT(Vec02, self->f2490, 0x300) = *(Vec02*)D_00263980;
                }
            }
            if (sub == 47) {
                Vec02 d;
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(self->v140));
                self->heading = ArctangentOfRatio(d.y, d.x);
            }
            break;
        case 41:
        case 48: {
            Vec02 d;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(self->v140));
            self->heading = ArctangentOfRatio(d.y, d.x);
            anim = self->subStateAnims[sub];
            break;
        }
        case 36:
        case 42:
        case 43:
            anim = self->subStateAnims[sub];
            break;
        case 40:
        case 49:
            self->desc02()->m21(self, (Vec02*)&D_00248D30);
            self->heading = self->stickHeading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
            anim = self->subStateAnims[sub];
            break;
        case 37:
        case 38:
            flag = 0;
            self->heading = self->stickHeading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
            anim = self->subStateAnims[sub];
            if (D_002639B8 != 0) {
                speed = 0.0f;
            }
            break;
        case 50:
        case 51:
        case 52:
            if (self->stateAnimPlayer != 0 && AT(void*, self->stateAnimPlayer, 8) == self->linkBlend) {
                skip = 1;
                break;
            }
            anim = self->linkBlend;
            speed = 0.0f;
            start = ((Animation*)anim)->length * 0.5f;
            break;
        case 53:
            walker = self->stateGraph;
            walkerId = 0x14B;
            break;
        case 55: {
            Vec02 v;
            u128 vel = Vu0::Q(self->v150);
            f32 most = D_00262E2C;
            Vu0::Q(v) = vel;
            s32 slow = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(vel, vel))) < D_002639B0[0];
            if (slow) {
                ComputePolarOffset((Vec3*)&v, self->heading, most, 0.0f);
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
            anim = self->f25D4;
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
            anim = self->f25D4;
            break;
        case 57:
            anim = self->f2760;
            break;
        case 58:
            anim = self->f2764;
            break;
        }
    }

    if (state != self->state) {
        self->state = state;
        self->stateStartTime = g_gameTime[0];
    }
    if (sub != self->subState) {
        self->subState = sub;
        self->subStateStartTime = g_gameTime[0];
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
            CreateAnimationPlayer((Animation*)anim, self, arg - args, (TargetBinding*)args, flag, (AnimationPlayer**)&self->stateAnimPlayer, start, speed);
        } else if (walker != 0) {
            self->stateWalker = CreateStateWalker((StateGraph*)walker, self, walkerId, flag);
        }
    }
}

#undef AT
#undef PS

void IgnorePlayerArgument(Player* self, s32 arg)
{
}

void SetPlayerState(Player* self, s32 state, s32 sub);

void SwitchPlayerState11(void* self, s32 flag)
{
    SetPlayerState((Player*)self, flag ? 11 : 0, -1);
}

void SetPlayerProbeContactsDisabled(Player* self, s32 value)
{
    self->probeContactsDisabled = value;
    self->f4B8 = 0;
}

PlacedObject* FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list) {
    PlacedObject* node;
    if (((PlacedObject*)q->hold)->desc->flags & 1) {
        node = (PlacedObject*)q->hold;
    } else {
        node = (PlacedObject*)((PlacedObject*)q->hold)->parent;
    }
    for (; node != 0; node = (PlacedObject*)node->parent) {
        s32 i;
        for (i = 0; i < n; i++) {
            if (node == list[i]) return 0;
        }
        switch (q->kind) {
        case 2: q->out = node->tint[0]; break;
        case 8: q->out = node->tint[1]; break;
        case 4: q->out = node->tint[2]; break;
        case 16: q->out = node->tint[3]; break;
        case 32: q->out = node->tintByte4; break;
        default: q->out = 0; break;
        }
        if (node->desc02()->m2D(node, q)) return node;
    }
    return node;
}

// An element CompareKeysAscending orders: a float key at 0x14.
struct FloatKeyedItem {
    u8 pad0[0x14];
    f32 key;                // 0x14
};

s32 CompareKeysAscending(FloatKeyedItem* a, FloatKeyedItem* b)
{
    s32 r = -1;
    if (a->key > b->key) r = 1;
    return r;
}

extern List01 g_class75List;
s32 MaskWorldBitsBySave(void);
s32 IsObjectAttached(BaseObject* self);
// A hit CollectMeshHits gives (0x30 bytes).
struct MeshHit {
    u8 pad00[0x30];
};
// The float where retail's caller passes it; the definition has it last.
s32 CollectMeshHits(Vec02* center, f32 radius, s32 count, FaceRef* list, FaceRef* cursor, Mesh03* mesh, s32 cap, MeshHitEntry* out);
typedef s32 (*SortCompareFn)(void* a, void* b);
void HeapSortRecords(void* records, s32 n, s32 size, SortCompareFn cmp);
void SetPlayerAimMode(Player* self, s32 state);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

// The player's grabs of the frame. The state picks the object it reaches with (one of the five
// at 0x25D8) and the kinds of hold it takes (2, 4 or 8). Each class 0x75 object of those kinds
// whose position is on the object's mesh, and each contact of this frame between the object and
// another, makes a query (up to 64), nearest along the object's first axis first; the first whose
// node the player has not taken yet is taken (up to 32): its kind 2 drops the player's state,
// kind 1 ends the grab (the object's slot 3, or state 13 in state 0x37). The frame's contacts
// go back to the world's pool.
void UpdatePlayerGrabs(Player* self)
{
    NodeQuery recs[64];
    ListFrame frame;
    Vec02 pos;
    Vec02 motion;
    MeshHit hit;
    NodeQuery* rec;
    Collider* target;
    s32 mask;
    s32 n;
    s32 i;

    if (self->state == 4) {
        goto done;
    }
    if (self->subState == 7) {
        target = (Collider*)self->f25D8[1];
        mask = 4;
    } else if (self->aimMode == 4 || self->aimMode == 6 || self->aimMode == 5 || self->aimMode == 7) {
        target = (Collider*)self->f25D8[0];
        mask = 2;
    } else if (self->state == 10) {
        target = (Collider*)self->f25D8[2];
        mask = 8;
    } else if (self->subState == 8) {
        target = (Collider*)self->f25D8[3];
        mask = 4;
    } else if (self->subState == 0x37 && (MaskWorldBitsBySave() & 0x400)) {
        target = (Collider*)self->f25D8[4];
        mask = 8;
    } else {
        goto done;
    }
    n = 0;
    if (IsObjectAttached(target)) {
        f32 scale = 1000.0f;
        Class75Object* o;
        for (o = (Class75Object*)g_class75List.head; o != 0; o = *(Class75Object**)&o->link) {
            if (o->f90 == 0) {
                continue;
            }
            if (!(o->count & mask)) {
                continue;
            }
            GetObjectWorldPosition(o, &pos);
            if (CollectMeshHits(&pos, o->scale, target->tree.count2, (FaceRef*)target->tree.nodes, 0, &target->meshCopy, 1, (MeshHitEntry*)&hit) <= 0) {
                continue;
            }
            if (n >= sizeof(recs) / sizeof(recs[0])) {
                break;
            }
            rec = &recs[n];
            FillMemory(rec, 0, 0x40);
            n++;
            ComputeObjectMotionInFrame((PlacedObject*)o->parent, 0, &pos, (Vec02*)&rec->dir, 0, 0, 0);
            ComputeObjectMotionInFrame((PlacedObject*)o->parent, 0, &pos, (Vec02*)&motion, 0, 0, 0);
            rec->p00 = self;
            rec->hold = o;
            rec->pos = pos;
            rec->kind = mask;
            rec->weight = self->mass * scale;
            Vu0::StoreX(rec->key, Vu0::Dot(Vu0::Q(target->m110.r[0]), Vu0::Q(pos)));
        }
    }
    if (n == 0 && self->queryContacts == 0) {
        return;
    }
    for (Contact03* c = self->queryContacts; c != 0; c = c->next) {
        s32 e = (Collider*)self != c->end[0].body;
        if (c->end[e].part != target) {
            continue;
        }
        if (n >= sizeof(recs) / sizeof(recs[0])) {
            break;
        }
        rec = &recs[n];
        FillMemory(rec, 0, 0x40);
        n++;
        rec->p00 = self;
        rec->hold = c->end[1 - e].part;
        rec->pos = c->end[1 - e].point;
        rec->kind = mask;
        rec->weight = self->mass * 1000.0f;
        ComputeObjectMotionInFrame((PlacedObject*)c->end[e].part, 0, &rec->pos, (Vec02*)&rec->dir, 0, 0, 0);
        Vu0::StoreX(rec->key, Vu0::Dot(Vu0::Q(target->m110.r[0]), Vu0::Q(rec->pos)));
    }
    HeapSortRecords(recs, n, 0x40, CompareKeysAscending);
    for (i = 0; i < n; i++) {
        rec = &recs[i];
        PlacedObject* node = FindNodeForQuery(rec, self->foundNodeCount, self->foundNodes);
        if (node == 0) {
            continue;
        }
        if (rec->out & 2) {
            if (mask & 2) {
                if (self->aimMode == 6 || self->aimMode == 4) {
                    SetPlayerState(self, 0, -1);
                    SetPlayerAimMode(self, 8);
                } else {
                    SetPlayerState(self, 0, -1);
                    SetPlayerAimMode(self, 9);
                }
            } else if (mask & 4) {
                SetPlayerState(self, 0, -1);
                SetPlayerAimMode(self, 8);
            }
        }
        if (rec->out & 1) {
            if (self->subState == 0x37) {
                SetPlayerState(self, 0xD, 0x38);
            } else {
                target->desc->m03(target);
            }
            goto done;
        }
        if ((u32)self->foundNodeCount < 32) {
            self->foundNodes[self->foundNodeCount++] = node;
        }
    }
done:
    FreePooledContactChain((World*)self->world, self->queryContacts);
    self->queryContacts = 0;
}

s32 IsTopCameraController(CameraController* self);

s32 IsPlayerCameraFree(Player* self)
{
    if (self->state == 12 && self->subState == 0x22) return 0;
    return IsTopCameraController((CameraController*)&g_camera->ctl454) == 0;
}

void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other);
void SetPlayerState(Player* self, s32 state, s32 sub);

void StartPlayerEffect(Player* self, s32 mode, PlacedObject* other)
{
    StartSwitchedColliderEffect(self, mode, other);
    switch (mode) {
    case 0:
        (void)SetPlayerState(self, 9, 0x1C);
        break;
    case 1:
        (void)SetPlayerState(self, 9, 0x1D);
        break;
    }
}

// The objects the player is told about (GetPlayerInteractFlags, ReceivePlayerNode and the two
// activation queues): each reads only the word at 0x2D0, a mode (1 and 2 are captions).
struct InteractTarget {
    u8 pad0[0x2D0];
    s32 mode;               // 0x2D0
};
extern s32 D_00275BC4;

void GetPlayerInteractFlags(Player* self, InteractTarget* other, s32* out)
{
    s32 v;
    switch (self->state) {
    case 0:
    case 1:
    case 5:
        v = 1;
        goto both;
    case 2:
    case 8:
    case 10:
    case 13:
    case 14:
    case 15:
    case 16:
        out[0] = 1;
        out[1] = other->mode == 1;
        break;
    case 3:
    case 6:
    case 7:
        v = other->mode == 1;
    both:
        out[0] = v;
        out[1] = v;
        break;
    case 12:
        out[0] = 0;
        out[1] = (s32)self->pendingCaption == (s32)other;
        break;
    case 4:
    case 9:
        out[0] = 0;
        out[1] = other->mode == 1;
        break;
    case 11:
        out[0] = 0;
        out[1] = 1;
        break;
    }
    if (D_00275BC4 != 3)
        out[0] = 0;
}

extern u8 g_elementStack[];

void PushStackElement(ElementStack* self, ScreenElement* node);

void ReceivePlayerNode(Player* self, InteractTarget* node)
{
    if ((u32)(node->mode - 1) < 2) {
        g_typedTextCaptionBox.child = node;
        PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
        return;
    }
    if (self->state != 0xC) {
        s32 f = self->pendingFlags;
        self->pendingSubState = 0x21;
        self->pendingCaption = node;
        self->pendingState = 0xC;
        self->pendingFlags = f | 1;
    }
}

void SetColliderPosition(Collider* self, Vec02* pos);
void ResetTrailRing(TrailRing* o);

void SetPlayerPosition(Player* self, Vec02* pos)
{
    SetColliderPosition(self, pos);
    ResetTrailRing((TrailRing*)self->trail);
    self->f2768 = 0;
}

void InitSwitchedCollider(SwitchedCollider* self);



void StartPlacedObject(void* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void SetFollowObjects(void* a, s32 b, s32 c);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
void BuildCombinedBlendAnimation(Collider* ctx, s32 stride, s32 count, u8* items, s32 nkeys, s32* keyA, s32* keyB, BlendAnimation** out);
void SetBlendItemWeights(BlendAnimationView* self, s32 a1, s32 a2, void* a3);
void SetWorld5ModeColliderMode(void* self, s32 a1);
s32 FindAnimRecord(s32 key);


void ResetTrailRing(TrailRing* o);
void RegisterSwitchedCollider(SwitchedCollider* self);

void RegisterPlayer(Player* self)
{
    ResetTrailRing((TrailRing*)self->trail);
    RegisterSwitchedCollider(self);
}

// An object the player was queued to (+0x2BE0): a walker handle at +0x2D8, and the list of the
// objects at +0x304 (count at +0x300) whose own walkers it sets.
struct WalkerListObject;
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);

void RunPlayerQueuedActivations(Player* self)
{
    s32 state = self->state;
    if (state < 0) {
        return;
    }
    if (state >= 2 && state != 5) {
        return;
    }
    PlacedObject* a = (PlacedObject*)self->firstActivation;
    if (a != 0) {
        self->firstActivation = 0;
    } else {
        a = (PlacedObject*)self->secondActivation;
        if (a == 0) {
            goto walker;
        }
        self->secondActivation = 0;
    }
    if (*(s32*)((u8*)a + 0x2D0) == 0) {
        a->desc02()->m2F(a, 1);
    }
    return;
walker:
    {
        WalkerHost* host = (WalkerHost*)self->walkerActivation;
        if (host == 0) {
            return;
        }
        self->walkerActivation = 0;
        s32 cur;
        s32 target;
        GetStateWalkerCurrentKey((StateWalker*)host->f2D8, &cur);
        GetStateWalkerTargetKey((StateWalker*)host->f2D8, &target);
        if (cur != 0x22E) {
            return;
        }
        if (target != cur && target != -1) {
            return;
        }
        if (g_currentLevelRecord->f438 > 0) {
            g_player->walkerHost = host;
            SetPlayerState(g_player, 9, 0x1E);
            return;
        }
        for (s32 i = 0; i < host->count; i++) {
            SetStateWalkerTarget((StateWalker*)host->list[i]->walker, 0x231);
        }
        Vec02 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(host->v140), Vu0::Q(g_player->v140));
        g_player->heading = ArctangentOfRatio(d.y, d.x);
    }
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first



s32 HasSpareCount(void);
void ComputeWorld5ModeColliderAnchors(void* self, void* a, void* b);
void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
void SetWorld5ModeColliderMode(void* self, s32 a1);



// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 g_world5CountdownRequest;

void DecrementGaugeCount(void* p);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
void ReplaceAnimationPlayer(Animation* anim, BaseObject* owner, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
s32 HandleObjectEvent(Collider* self, ObjectEvent* shape);


void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.


// A walker's current and target keys (GetStateWalkerCurrentKey, GetStateWalkerTargetKey).
struct WalkerKeys { s32 a, b; };

void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);

void QueuePlayerWalkerActivation(Player* self, u8* other)
{
    WalkerKeys r;
    if (self->state != 9) {
        GetStateWalkerCurrentKey((StateWalker*)(*(void**)(other + 0x2D8)), &r.a);
        GetStateWalkerTargetKey((StateWalker*)(*(void**)(other + 0x2D8)), &r.b);
        if (r.a == 0x22E && (r.b == r.a || r.b == -1)) {
            self->walkerActivation = other;
        }
    }
}

void InitCollider(Collider* self);


void ReplaceAnimationPlayer(Animation* anim, BaseObject* owner, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);





s32 IsObjectAttached(BaseObject* self);


extern s32 g_world5CountdownRequest;


void StartPlacedObject(void* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);


void ComputeWorld5ModeColliderAnchors(void* self, void* a, void* b);
void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);


void StartPlacedObject(void* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void BuildCombinedBlendAnimation(Collider* ctx, s32 stride, s32 count, u8* items, s32 nkeys, s32* keyA, s32* keyB, BlendAnimation** out);
void SetBlendItemWeights(BlendAnimationView* self, s32 a1, s32 a2, void* a3);
void SetWorld5BossMode(World5Boss* self, s32 a1);
s32 PlayWorld5BossLoop(World5Boss* self, s32 a1);



void DecrementGaugeCount(void* p);
void PlayWorld5BossTarget(World5Boss* self);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);



void QueuePlayerFirstActivation(Player* a0, InteractTarget* a1)
{
    if (a0->state != 9 && a1->mode == 0) {
        a0->firstActivation = a1;
    }
}

void QueuePlayerSecondActivation(Player* a0, InteractTarget* a1)
{
    if (a0->state != 9 && a1->mode == 0) {
        a0->secondActivation = a1;
    }
}

LINKER_REMNANT(func_001782A8);

struct TargetArcSource {
    BaseObject* target;
    f32 t;
    u8 pad08[8];
    Vec02 v10;
};
typedef void (*ShapeAtFn)(void* self, f32 t, Vec02* out, s32 x);
struct ShapeOwner {
    ShapeAtFn* vtbl;
};
struct TargetShaped {
    u8 pad00[0x34];
    ShapeOwner* shape;
};
s32 IsObjectOfKind(BaseObject* list, s32 key);
void PlaceOnPathAt(Player* self, PathObject* path, Mat02* out, f32 length);
void PlaceOnTargetCurve(TargetCurve* self, Vec02* out, f32* angleOut, f32 t);
void PlaceOnTargetPoint(TargetPoint* self, Vec02* out, f32* angleOut, f32 t);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void TransformPointAtTime(PlacedObject* self, PlacedObject* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin); // the float where retail's caller passes it; the definition has it last
// EXACT: gravity read in each expression that weights it, as a value of its own: the -0.5 dt
// weight then comes before the load in the insn order, and sched1 keeps it there
// (docs/TOOLCHAIN.md, "sched1").
void ComputeTargetArc(Player* self, TargetArcSource* src, f32 dt, Vec02* vel, Vec02* pos, Vec02* acc)
{
    Vec02 p;
    Vec02 v1;
    Vec02 a;
    Vec02 off = *(Vec02*)D_002639C0;
    BaseObject* parent;
    if (src->target != 0) {
        parent = src->target->parent;
        if (IsObjectOfKind(src->target, 0x76)) {
            p = *(Vec02*)((u8*)src->target + 0x40);
            off = *(Vec02*)D_002639D0;
        } else if (IsObjectOfKind(src->target, 0x70)) {
            BaseObject* obj = src->target;
            ShapeOwner* shape = ((TargetShaped*)obj)->shape;
            if (shape->vtbl[2] != 0) {
                shape->vtbl[2](shape, src->t, &p, 0);
            }
            Mat02 frame;
            PlaceOnPathAt(self, (PathObject*)obj, &frame, src->t);
            Vu0::Q(off) = Vu0::MulX(Vu0::Q(frame.r[0]), Vu0::ScalarAt(D_002639E0[0]));
        } else if (IsObjectOfKind(src->target, 0x6F)) {
            PlaceOnTargetCurve((TargetCurve*)src->target, &p, 0, src->t);
            TransformPointBetweenFrames(0, (PlacedObject*)parent, &p, &p);
        } else if (IsObjectOfKind(src->target, 0x7F)) {
            PlaceOnTargetPoint((TargetPoint*)src->target, &p, 0, src->t);
            TransformPointBetweenFrames(0, (PlacedObject*)parent, &p, &p);
        } else if (IsObjectOfKind(src->target, 0x6E)) {
            ShapeOwner* shape = ((TargetShaped*)src->target)->shape;
            if (shape->vtbl[2] != 0) {
                shape->vtbl[2](shape, src->t, &p, 0);
            }
        } else if (IsObjectOfKind(src->target, 0x7E)) {
            p = *(Vec02*)((u8*)src->target + 0x40);
        } else {
            p = D_00248D30;
        }
    } else {
        parent = 0;
        p = src->v10;
    }
    a = D_00248D30;
    TransformPointAtTime((PlacedObject*)parent, 0, dt, &p, 0, &a, 0);
    u128 end = Vu0::Add(Vu0::Q(p), Vu0::Q(off));
    u128 v = Vu0::DivX(Vu0::Sub(end, Vu0::Q(self->v140)), Vu0::Scalar(dt));
    v = Vu0::MulAddX(v, Vu0::Q(self->gravity), Vu0::Scalar(dt * -0.5f));
    Vu0::Q(p) = end;
    Vu0::Q(v1) = v;
    Vu0::Q(a) = Vu0::MulAddX(v, Vu0::Q(self->gravity), Vu0::Scalar(dt));
    if (vel != 0) {
        Vu0::Q(*vel) = v;
    }
    if (pos != 0) {
        *pos = p;
    }
    if (acc != 0) {
        *acc = a;
    }
}


void MoveCollider(void* self, void* b);


void FinishSwitchedCollider(SwitchedCollider* self);
void SetWorld5ModeColliderMode(void* self, s32 a1);


void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg);


// A target the player may aim at: two quads (ScoreTargetCandidate's hit, ChooseBestTargetCandidate's
// result, the pair the player keeps at 0x2B70).
struct TargetHit {
    union {
        Vec02 q0;           // 0x00
        void* obj;          // 0x00: the object aimed at, none for a point on the ground (func_001788F0)
    };
    Vec02 q1;               // 0x10
};
// The record the player keeps at 0x2514 for a jump at a target: when it lands and the two ends
// of its arc (func_00178598).
struct TargetLaunch {
    u8 pad0[0x18];
    f32 landTime;           // 0x18: the game time it lands
    u8 pad1[0x20 - 0x1C];
    Vec02 q20;              // 0x20
    Vec02 q30;              // 0x30
};

// func_00178598's locals: the arc's three points, the chosen target and its time.
struct TargetArcFrame {
    Vec02 q0;
    Vec02 q1;
    Vec02 q2;
    Vec02 p0;
    Vec02 p1;
    f32 fl;
};

void ChooseBestTargetCandidate(Player* self, s32 n, BaseObject** items, TargetHit* out, f32* outf);
void ComputeTargetArc(Player* self, TargetArcSource* src, f32 dt, Vec02* vel, Vec02* pos, Vec02* acc);
void SetPlayerState(Player* self, s32 state, s32 sub);


void LaunchPlayerAtTarget(Player* self, TargetHit* s2, f32 f)
{
    TargetArcFrame fr;
    fr.fl = f;
    if (s2 == 0) {
        ChooseBestTargetCandidate(self, 0, 0, (TargetHit*)&fr.p0, &fr.fl);
        s2 = (TargetHit*)&fr.p0;
    }
    void* q1 = &fr.q1;
    ComputeTargetArc(self, (TargetArcSource*)s2, fr.fl, (Vec02*)q1, &fr.q0, &fr.q2);
    ((TargetLaunch*)self->selfPoseSource)->landTime = g_gameTime[0] + fr.fl;
    ((TargetLaunch*)self->selfPoseSource)->q20 = fr.q0;
    ((TargetLaunch*)self->selfPoseSource)->q30 = fr.q2;
    self->desc02()->m20(self, (Vec02*)q1);
    self->contactQuads[0] = s2->q0;
    self->contactQuads[1] = s2->q1;

    SetPlayerState(self, 4, 0x2C);
}

INCLUDE_RODATA(D_0024AFA0);
extern const f32 D_0024AFA0;

void EvaluateHermiteVectorSegment(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 t, f32 k, Vec02* pos, Vec02* vel, Vec02* acc);
s32 CollectSpansFromList(void* a0, void* a1, s32 count, Collider** list, s32 a4, ColliderSpan* a5);

void ChooseTargetArcTime(PlacedObject* self, void* target, s32 count, Collider** list, f32* out)
{
    Vec02 start;
    Vec02 b;
    Vec02 a;
    Vec02 c;
    Vec02 cur;
    Vec02 prev;
    ColliderSpan spans[8];
    f32 bestTime = D_0024AFA0;
    f32 bestScore = bestTime;
    start = self->v140;
    start.z = start.z - 75.0f;
    for (u32 i = 0; i < 9; i++) {
        ComputeTargetArc((Player*)self, (TargetArcSource*)target, g_targetArcDurations[i], &a, &b, &c);
        b.z = b.z - 75.0f;
        prev = start;
        f32 total = 1.0f;
        for (f32 u = 0.0f; u < g_targetArcDurations[i]; u += 0.25f) {
            EvaluateHermiteVectorSegment(g_targetArcDurations[i], &start, &a, &b, &c, g_targetArcDurations[i] <? (u + 0.25f), 1.0f, &cur, 0, 0);
            s32 n = CollectSpansFromList(&prev, &cur, count, list, 8, spans);
            for (s32 k = 0; k < n; k++) {
                total += Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(spans[k].q[0]), Vu0::Q(spans[k].q[1]))));
            }
            prev = cur;
        }
        f32 score = total * Vu0::ToFloat(Vu0::Length(Vu0::Q(a)));
        if (score < bestScore) {
            bestScore = score;
            bestTime = g_targetArcDurations[i];
        }
    }
    *out = bestTime;
}

extern f32 D_00263A10[32];
extern f32 D_00263A90[4];
extern f32 D_00263AA0[4];
extern f32 D_00263AB0[4];

f32 ScoreTargetCandidate(Player* self, TargetHit* cand, s32 n, TurningCollider** objs, TargetHit* out, f32* outTime)
{
    typedef Vu0::Vec Vec;
    f32 t = 0.7f;
    PushBackMemoryMark();
    Vec02 lo;
    Vec02 hi;
    Vec02 q;
    ComputeTargetArc(self, (TargetArcSource*)cand, t, 0, &q, 0);
    f32 score = 0.0f;
    Vu0::Q(hi) = Vu0::Max(Vec::Of(self->v140), Vec::Of(q)).q;
    Vu0::Q(lo) = Vu0::Min(Vec::Of(self->v140), Vec::Of(q)).q;
    hi.z = hi.z + 200.0f;
    Vu0::Q(lo) = Vu0::Sub(Vec::Of(lo), Vec::Of(D_00263A90)).q;
    Vu0::Q(hi) = Vu0::Add(Vec::Of(hi), Vec::Of(D_00263A90)).q;
    s32 count;
    Collider** list;
    GatherCollidersInBox(self->world, self, &lo, &hi, 0, 0, &count, &list);
    TargetHit hit = *cand;
    if (cand->obj == 0) {
        Vec02 p;
        Vec02 r;
        ColliderSpan span;
        p = r = q;
        p.z = p.z + 125.0f;
        r.z = r.z - 175.0f;
        if (FindNearestSpanObject(0, &p, &r, count, list, &span) == 0 || span.time[0] == score ||
            ((Vec02*)&span.q[2])->z < t) {
            f32 penalty = 2000.0f;
            score = penalty >? score;
            hit.q1 = q;
        } else {
            hit.q1 = *(Vec02*)&span.q[0];
        }
        p = r = hit.q1;
        p.z = p.z + 180.0f;
        r.z = r.z + 5.0f;
        if (FindNearestSpanObject(0, &p, &r, count, list, &span)) {
            f32 penalty = 2000.0f;
            score = penalty >? score;
        }
        for (u32 i = 0; i < 8; i++) {
            Vu0::Q(p) = Vu0::Q(r) = Vu0::Add(Vec::Of(hit.q1), Vec::Of(((Vec02*)D_00263A10)[i])).q;
            p.z = p.z + 50.0f;
            r.z = r.z - 30.0f;
            if (FindNearestSpanObject(0, &p, &r, count, list, &span) == 0) {
                f32 penalty = 1500.0f;
                score = penalty >? score;
                break;
            }
        }
    }
    for (s32 j = 0; j < n; j++) {
        TurningCollider* o = objs[j];
        Vec02 at;
        if (o->mesh.verts != 0) {
            f32 d = -o->probeDepth - ((Vec02*)o->mesh.verts)[o->probeIndex].z;
            Vu0::Q(at) = Vu0::MulAddX(Vec::Of(hit.q1), Vec::Of(g_unitZVector), Vec::Scalar(d)).q;
        } else {
            at = hit.q1;
        }
        f32 dist = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vec::Of(o->v140), Vec::Of(at))).q) - o->radius3D0;
        f32 x = D_00263AA0[0] + dist * (D_00263AA0[1] + dist * D_00263AA0[2]);
        f32 l = D_00263AB0[0];
        f32 h = D_00263AB0[1];
        if (x < l) {
            x = l;
        } else if (h < x) {
            x = h;
        }
        score = x >? score;
    }
    f32 time;
    ChooseTargetArcTime(self, &hit, count, list, &time);
    PopBackMemoryMark();
    *out = hit;
    *outTime = time;
    return score;
}

ASM_FUNC(func_00178D18);




void SetWorldActiveFollower(World* self, void* v);
void ReplaceAnimationPlayer(Animation* anim, BaseObject* owner, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);


extern s32 g_world5CountdownRequest;
extern s32 g_timeoutFired;

void UpdateCollider(Collider* self, f32 dt);
void StopAnimationPlayer(AnimationPlayer* self);
void SetWorld5CountdownState(void* self, s32 state);
void FadeOutAndQueueMovie(s32 n);


extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 AreMenusAndFadeClear(void* self);


extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 AreMenusAndFadeClear(void* self);


extern f32 g_gameClock[];
extern Rgba4 D_002623E0;

extern "C" f32 Cosine(f32 x);
void SetObjectTreeRecordValue(World5ModeCollider* o, u32 value);
void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf);


// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void StepCollider(Collider* self, f32 t);
void ComputeWorld5ModeColliderAnchors(World5ModeCollider* self, Vec02* a, Vec02* b);
void SteerColliderTowardPosition(Collider* self, Vec02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain);


// A 0x20-byte candidate: an object, its distance along its curve (class 0x6E) and the point
// ComputeTargetArc gives. The player keeps f2768 of them at 0x2770.
struct TargetCandidate {
    BaseObject* node;       // 0x00
    f32 curveDistance;      // 0x04: the distance along the object's curve
    u8 pad08[8];
    u8 point[16];           // 0x10: the point ComputeTargetArc gives
};
void PushBackMemoryMark(void);
TargetCandidate* AllocateZeroedBackMemory(s32 size);
void PopBackMemoryMark(void);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void ComputeTargetArc(Player* self, TargetArcSource* src, f32 dt, Vec02* vel, Vec02* pos, Vec02* acc);
s32 CompareDistanceFromPlayer(TargetCandidate* a, TargetCandidate* b);
void SortElements(void* base, u32 n, u32 size, s32 (*compare)(const void* x, const void* y));
f32 ScoreTargetCandidate(Player* self, TargetHit* cand, s32 n, TurningCollider** objs, TargetHit* out, f32* outTime);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

void ChooseBestTargetCandidate(Player* self, s32 n, BaseObject** items, TargetHit* out, f32* outf)
{
    u8 scratch[0x80];
    TargetHit hit;
    Vec02 tmp;
    f32 dist;
    f32 r;
    s32 v;
    TargetCandidate* buf;
    f32 best;
    s32 cnt = 0;

    v = GatherObjectsById(self->world, 5, 8, 0, 0x20, (PlacedObject**)scratch);
    PushBackMemoryMark();
    buf = AllocateZeroedBackMemory(n << 5);
    for (s32 i = 0; i < n; i++) {
        BaseObject* node = items[i];
        if (IsObjectAttached(node) != 0) {
            TargetCandidate* e = buf + cnt;
            cnt = cnt + 1;
            e->node = node;
            if (IsObjectOfKind(node, 0x6E) != 0) {
                TransformPointBetweenFrames(0, (PlacedObject*)node->parent, &self->v140, &tmp);
                PathCurve* s = ((PathCurveObject*)node)->curve;
                if (s->vt->m10 != 0) {
                    s->vt->m10(s, &tmp, 0, 0, 0, 0, &e->curveDistance);
                }
            } else {
                e->curveDistance = 0;
            }
            ComputeTargetArc(self, (TargetArcSource*)e, 0.7f, 0, (Vec02*)e->point, 0);
        }
    }
    SortElements(buf, cnt, 0x20, (s32 (*)(const void*, const void*))CompareDistanceFromPlayer);
    best = 3.40282347e+38f;
    for (s32 i = 0; i < cnt; i++) {
        r = ScoreTargetCandidate(self, (TargetHit*)&buf[i], v, (TurningCollider**)scratch, &hit, &dist);
        if (r < best) {
            best = r;
            *out = hit;
            *outf = dist;
            if (best == 0.0f)
                goto done;
        }
    }
    if (best <= 1000.0f)
        goto done;
    for (s32 i = 0; i < self->f2768; i++) {
        TargetCandidate* q = &((TargetCandidate*)self->f2770)[i];
        if (q->node == 0 || IsObjectAttached(q->node) != 0) {
            r = ScoreTargetCandidate(self, (TargetHit*)q, v, (TurningCollider**)scratch, &hit, &dist);
            if (r < best) {
                best = r;
                *out = hit;
                *outf = dist;
                if (best == 0.0f)
                    goto done;
            }
        }
    }
    if (best == 3.40282347e+38f) {
        FillMemory(out, 0, 0x20);
        *(s32*)out = 0;
        out->q1 = self->v140;
        ((f32*)out)[6] -= 75.0f;
        *outf = 0.75f;
    }
done:
    PopBackMemoryMark();
}

struct TargetMemo {
    void* key;
    f32 along;
    f32 f8;
    u8 padC[4];
    Vec02 pos;
};
extern const Vec02 D_00248D30;
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void* MoveMemory(void* dst, void* src, s32 size);
#define History(p) ((TargetMemo*)((u8*)(p) + 0x2770))
void RecordPlayerTargetMemo(Player* self)
{
    Vec02 pos = D_00248D30;
    TargetMemo tmp;
    u8* key = 0;
    f32 w = 0.0f;
    switch (self->state) {
    case 3: {
        u8* o = (u8*)self->boundObject;
        if (*(s32*)(o + 0xB8) != 0) {
            return;
        }
        key = o;
        break;
    }
    case 6:
        switch (self->targetMode) {
        case 4: {
            u8* o = (u8*)self->targetTrack;
            if (*(s32*)(o + 0x50) != 0) {
                return;
            }
            key = o;
            w = self->f23C4;
            break;
        }
        case 5: {
            u8* o = (u8*)self->targetNode;
            if (*(s32*)(o + 0x5C) != 0) {
                return;
            }
            key = o;
            break;
        }
        case 0: {
            u8* o = (u8*)self->targetCurve;
            if (o != 0) {
                if (*(s32*)(o + 0x5C) != 0) {
                    return;
                }
                key = o;
                w = self->targetCurvePos;
            } else {
                o = (u8*)self->targetPoint;
                if (*(s32*)(o + 0x74) != 0) {
                    return;
                }
                key = o;
                ConvertPositionToWorld((BaseObject*)o, (Vec02*)&tmp);
                Vu0::Q(tmp.pos) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)&tmp));
                w = ArctangentOfRatio(tmp.pos.y, tmp.pos.x) * *(f32*)((u8*)self->targetPoint + 0x5C);
            }
            break;
        }
        case 7:
            return;
        default:
            goto probe;
        }
        break;
    case 2:
    case 4:
    case 8:
    case 11:
        return;
    case 0:
    case 1:
    case 5:
    case 9:
    case 10:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    probe:
        if (self->groundContact == 0) {
            return;
        }
        if (self->groundContactPart == 0) {
            pos = self->groundContactPoint;
        } else {
            if ((((Collider*)self->groundContactPart)->flags538 & (1ull << 52)) != 0) {
                return;
            }
            pos = self->groundContactPoint;
        }
        break;
    case 7: {
        u8* o = (u8*)self->aimCurve;
        if (*(s32*)(o + 0x60) != 0) {
            return;
        }
        w = self->pathPos;
        key = o;
        break;
    }
    default:
        break;
    }
        s32 i;
    for (i = 1; i < self->f2768; i++) {
        TargetMemo* e = &History(self)[i];
        s32 match = 0;
        if (key == e->key) {
            if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(pos), Vu0::Q(e->pos)))) < 50.0f) {
                if (__builtin_fabsf(w - e->along) < 50.0f) {
                    match = 1;
                }
            }
        }
        if (match) {
            if (i != 1) {
                tmp = *e;
                MoveMemory(&History(self)[2], &History(self)[1], (i - 1) * 0x20);
                History(self)[1] = tmp;
            }
            break;
        }
    }
    if (i >= self->f2768) {
        if ((u32)self->f2768 < 0x20) {
            self->f2768++;
        }
        MoveMemory(&History(self)[1], &History(self)[0], self->f2768 * 0x20 - 0x20);
        FillMemory(&History(self)[0], 0, 0x20);
    }
    History(self)[0].key = key;
    History(self)[0].pos = pos;
    History(self)[0].along = w;
    History(self)[0].f8 = g_gameClock[1];
}
