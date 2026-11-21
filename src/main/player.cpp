// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x16F608 to 0x1793C0: the player, class 0x07 (struct Player in
// include/switched_collider.h), its methods, its state changes and its target choice. Its name
// is ours, after the class.
#include "common.h"
#include "asm_functions.h"
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
#include "object_message.h"
#include "scaled_transform.h"
#include "state_notifier.h"
#include "transform_object.h"
#include "state_walker.h"
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
#include "collider_pose.h"
#include "mesh_hit_sample.h"
#include "functions/base_object.h"
#include "functions/blend_animation.h"
#include "functions/camera.h"
#include "functions/camera_controller.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/curve_segment.h"
#include "functions/effect_spawner.h"
#include "functions/entry_queue.h"
#include "functions/game_progress.h"
#include "functions/matrix.h"
#include "functions/on_off_object.h"
#include "functions/oscillator.h"
#include "functions/pad_input.h"
#include "functions/path_follower.h"
#include "functions/player_aim.h"
#include "functions/player_link.h"
#include "functions/player_mode.h"
#include "functions/player_path.h"
#include "functions/player_request.h"
#include "functions/player_state2.h"
#include "functions/player_target.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/screen_element.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/target_lists.h"
#include "functions/trail_ribbon.h"
#include "functions/turning_collider.h"
#include "functions/warp_menu.h"
#include "functions/world5_boss.h"
#include "functions/world_contacts.h"

// The pose source of the child-sum kind (g_childSumPoseSourceMethods): the attachment base and a
// word of its own at 0x1C.
struct ChildSumPoseSource : Attachment {
    u8 pad18[0x1C - 0x18];
    s32 f1C;                // 0x1C: 2 at set-up
};
struct BufferedStream;

// Types other files define, named by the parameters of their functions declared here.
struct BlendAnimation;
struct BlendSlot;
struct CameraSoundOwner;
struct Chooser;
struct PlayerTargetState;
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
f32 g_jumpSpeedBase = 455.0f;
f32 g_jumpKind3SpeedScale = 0.699999988f;
f32 g_jumpKind4SpeedScale = 0.600000024f;
f32 g_soundEffect94Volume = 0.699999988f;
f32 g_soundEffect7EVolume = 0.600000024f;
f32 D_00262E28 = 1000.0f;
f32 D_00262E2C = 850.0f;
f32 D_00262E30 = 50.0f;

// NEAR: frame, saves, the vtable call and the branch tree match; the 0xD path loads its two floats into $f1/$f0 where retail uses $f0/$f1, so the shared store tail differs

// The path the player follows (0x23B8, 0x23BC): its frame, its curve, and whether it is a rail.
struct PathRecord { u8 pad00[0x18]; PlacedObject* frame; u8 pad1C[0x34 - 0x1C]; PathCurve* curve; u8 pad38[0x40 - 0x38]; s32 isRail; };
typedef s32 (*VFn_170410)(Player* self, void* out, s32 end);

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
f32 g_phaseSoundInitial0[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 g_phaseSoundInitial1[4] = { 0.0f, 0.25f, 0.449999988f, 0.449999988f };
f32 g_phaseSoundInitial2[4] = { 0.0f, 0.25f, 0.449999988f, 0.449999988f };
f32 g_phaseSoundInitial3[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 g_phaseSoundInitial4[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 g_ledgeHandOffsetInitial[4] = { 37.0f, 0.0f, 25.0f, 0.0f };
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
s32 g_spinTargetRateDefault = 50;
s32 g_spinTargetRateSubState8 = 100;
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
f32 g_cameraPoseMaxOffset = 75.0f;
f32 g_cameraPoseMinOffset = -325.0f;
f32 g_cameraHeightMaxOffset = -50.0f;
f32 g_cameraHeightMinOffset = -350.0f;
f32 g_cameraHeightStartOffset[2] = { -300.0f, 0.0f };
f32 D_002638D0[4] = { 1.5f, -0.5f, 0.0f, 0.0f };
f32 g_pivotApproachRamp[4] = { 1500.0f, 0.0f, 0.5f, 0.0f };
f32 g_heightApproachRamp[4] = { 4000.0f, 0.0f, 4.0f, 0.0f };
f32 g_forceApproachRamp[4] = { 600.0f, 300.0f, 0.100000001f, 50.0f };
f32 g_playerCallbackWindow[2] = { 0.150000006f, 0.25f };
f32 g_positionApproachRamp[3] = { 1000.0f, 0.0f, 0.25f };
f32 g_uprightThreshold = 0.899999976f;
f32 D_00263928[2] = { 8.0f, 0.0f };

s32 g_stateFallbackChain[16] = { -1, 36, 36, 36, -1, 36, 36, 36, 36, -1, 45, 45, 41, 40, 0, 0 };
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
f32 g_hitRingOffsets[32] = { 40.0f, 0.0f, 0.0f, 0.0f, 28.2999992f, 28.2999992f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, -28.2999992f, 28.2999992f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 0.0f, -28.2999992f, -28.2999992f, 0.0f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 28.2999992f, -28.2999992f, 0.0f, 0.0f };
f32 g_searchBoxMargin[4] = { 200.0f, 200.0f, 200.0f, 0.0f };
f32 D_00263AA0[4] = { 400.0f, -1.0f, 0.0f, 0.0f };
f32 D_00263AB0[4] = { 0.0f, 1000.0f, 0.0f, 0.0f };


// Set-up of a new player object after the turning collider's: marks the state, aim mode, sub-state
// and jump kind as none (-1), copies the five phase-sound tables, sets the bounds radius (15), the
// gravity (0, 0, -1750), the ledge hand offset and the trail, and starts the blend scales at 1.
void InitPlayer(Player* self)
{
    InitTurningCollider(self);
    self->state = -1;
    self->aimMode = -1;
    self->subState = -1;
    self->jumpKind = -1;
    self->phaseSoundStates[0] = *(Vec4U*)g_phaseSoundInitial0;
    self->phaseSoundStates[1] = *(Vec4U*)g_phaseSoundInitial1;
    self->phaseSoundStates[2] = *(Vec4U*)g_phaseSoundInitial2;
    self->phaseSoundStates[3] = *(Vec4U*)g_phaseSoundInitial3;
    self->phaseSoundStates[4] = *(Vec4U*)g_phaseSoundInitial4;
    self->boundsRadius = 15.0f;
    Vu0::Q(self->gravity) = Vu0::FromFloats(0.0f, 0.0f, -1750.0f);
    self->flags = (self->flags & ~(3ULL << 40)) | (1ULL << 40);
    self->ledgeHandOffset = *(Vec4*)g_ledgeHandOffsetInitial;
    self->trailEnabled = 1;
    self->padSelectMode = -1;
    self->innerFadeScale = 1.0f;
    self->outerFadeScale = 1.0f;
    self->animSeekTime = -3.4028235e+38f;
    self->pulseFadeDuration = 2.0f;
}

void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);

// Loads the collider, resolves the player's links, builds its member group, resets two timestamps
// to -1 and makes this the current player.
void LoadPlayer(Player* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 0x97, g_playerCharacterLinks);
    FindOrBuildMemberGroup((void**)self->pad2428, self);
    self->f2284 = -1.0f;
    self->aimHeldTime = -1.0f;
    g_player = self;
}

u8* CreatePoseSource(World* root, PlacedObject* value, const T2195_Vt* table);
void InsertAttachment(PlacedObject* self, Attachment* src);
void AddMatrixAttachment(PlacedObject* self, s32 key, Attachment** out);
AnimRecord* FindAnimRecord(s32 key);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void* AllocateZeroedFrontMemory(s32 n);
extern u8 g_childSumPoseSourceMethods[];
extern u8 g_snapshotPoseSourceMethods[];
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void SetPlayerState(Player* self, s32 state, s32 sub);


// The player's start method, once its links are resolved: builds the animation blends (six-, eight-
// and three-entry), the pose sources and matrix attachments on its rig object and parts, the trail
// and the aim blends, the on/off record and the table objects, then enters state 0, sets the camera
// height (75 below the position) and the gravity scale and mass, and flags its five collider parts.
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
    ChildSumPoseSource* a = (ChildSumPoseSource*)CreatePoseSource(self->world, self->rigObject, (const T2195_Vt*)g_childSumPoseSourceMethods);
    a->mode0 = 9;
    a->mode1 = 9;
    a->key = 3;
    a->f1C = 2;
    InsertAttachment(self->rigObject, a);
    self->f24FC = a;
    AddMatrixAttachment(self->rigObject, 5, (Attachment**)&self->rigAttachment);
    AddMatrixAttachment((PlacedObject*)self->f618, 5, (Attachment**)&self->f2504);
    AddMatrixAttachment((PlacedObject*)self->f61C, 5, (Attachment**)&self->f2508);
    AddMatrixAttachment((PlacedObject*)self->linkPartA, 7, (Attachment**)&self->footPartA);
    AddMatrixAttachment((PlacedObject*)self->linkPartB, 7, (Attachment**)&self->footPartB);
    self->rigPoseSource = CreatePoseSource(self->world, self->rigObject, (const T2195_Vt*)g_snapshotPoseSourceMethods);
    ((OwnerSnapshotAttachment*)self->rigPoseSource)->key = 1;
    InsertAttachment(self->rigObject, (Attachment*)self->rigPoseSource);
    self->trailOwner = self->f23D0;
    self->trailAnimRecord = FindAnimRecord(0x15A);
    self->f1530 = 0.5f;
    self->f1560 = *(Vec4*)D_00263710;
    self->f1570 = *(Vec4*)D_00263720;
    self->f1538 = 2;
    TransformPointBetweenFrames(0, (PlacedObject*)self->f23D0, &((PlacedObject*)self->f23D4)->v140, &self->f1540);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->f1540)));
    Vu0::Q(self->f1540) = Vu0::MulX(Vu0::Q(self->f1540), Vu0::Scalar((len + self->boundsRadius) / len));
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend4, 0, 0, 0, (BlendAnimation**)&self->aimAnim4);
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend5, 0, 0, 0, (BlendAnimation**)&self->aimAnim5);
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend6, 0, 0, 0, (BlendAnimation**)&self->aimAnim6);
    BuildCombinedBlendAnimation(self, 12, 2, self->aimBlend7, 0, 0, 0, (BlendAnimation**)&self->aimAnim7);
    BaseObject* o = (BaseObject*)self->textureObject;
    if (o != 0) {
        o->desc->m02(o);
        BuildTexturePackets((TextureRenderObject*)(self->textureObject), self->rangeRecord);
    }
    self->ownOnOffObject = (OnOffObject*)CreateTypedRecord(0x63, self->world, 0, 0x316, -1);
    ResetPlayerOnOffObject(self);
    CreateEightEntryBlend(self, (BlendSlot*)self->eightWaySlots, &self->eightWayBlend);
    ResolvePlayerTableObjects(self);
    self->desc03()->m34(self, self->stateNodes[0], 1);
    SetPlayerState(self, 0, -1);
    self->cameraHeight = self->v140.z - 75.0f;
    SetTurningColliderGravityScale(self, g_playerGravityScale);
    SetColliderMass(self, g_playerMass);
    Collider* c = (Collider*)self->slotObjects[0];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->slotObjects[2];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->slotObjects[1];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->slotObjects[3];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
    }
    c = (Collider*)self->slotObjects[4];
    if (c != 0) {
        c->flags538 |= (u64)0x8000 << 28;
        if (((PlacedObject*)self->slotObjects[4])->linkRecord == 0) {
            ((PlacedObject*)self->slotObjects[4])->linkRecord = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);
        }
        ((PlacedObject*)self->slotObjects[4])->linkRecord->flags |= 8;
        ((PlacedObject*)self->slotObjects[4])->linkRecord->p60 = 0;
    }
    if (self->stateNodes[8] == 0) {
        self->stateNodes[8] = self->stateNodes[2];
    }
    self->selfPoseSource = CreatePoseSource(self->world, self, (const T2195_Vt*)g_snapshotPoseSourceMethods);
    InsertAttachment(self, (Attachment*)self->selfPoseSource);
    self->snapshotPoseFirst = (Attachment*)CreatePoseSource(self->world, (PlacedObject*)self->f61C, (const T2195_Vt*)g_snapshotPoseSourceMethods);
    self->snapshotPoseFirst->key = 5;
    InsertAttachment((PlacedObject*)self->f61C, self->snapshotPoseFirst);
    self->snapshotPoseSecond = (Attachment*)CreatePoseSource(self->world, (PlacedObject*)(self->f23D0), (const T2195_Vt*)g_snapshotPoseSourceMethods);
    self->snapshotPoseSecond->key = 5;
    InsertAttachment((PlacedObject*)(self->f23D0), self->snapshotPoseSecond);
    self->flags &= ~(u64)0x0C000000;
    self->flags &= ~(u64)0x30000000;
    BuildCombinedBlendAnimation(self, 12, 3, (u8*)&self->pathLeanRight, 0, 0, 0, (BlendAnimation**)&self->pathLeanBlend);
    self->pathLeanCentre = 1.0f;
    if (self->pathLeanBlend != 0) {
        SetBlendItemWeights((BlendAnimationView*)(self->pathLeanBlend), 12, 3, (u8*)&self->pathLeanRight);
    }
    void* q = self->f2490;
    if (q != 0) {
        // the object's class is not known
        *(s32*)((u8*)q + 0x2F0) = 2;
    }
}

#undef PS

// x + t (y + t z) of a curve's three coefficients.
static inline f32 EvalCurve3(const f32* c, f32 t) { return c[0] + t * (c[1] + t * c[2]); }

extern f32 g_gameClock[];


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
static inline f32 TiltRotation(Mat3* out, Mat3* turn, const Mat3& m, const Vec4& to, Vec4* axis)
{
    const u128* q = (const u128*)&m;
    f32 angle = ComputeAngleBetweenVectors((Vec4*)((const Vec4*)&q[2]), (Vec4*)&to, axis);
    BuildAxisAngleMatrix((const Vec4*)axis, (Mat3*)turn, angle);
    const u128* p = (const u128*)turn;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Mat3 r;
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
    Vec4 axis;
    Vec4 axis2;
    Vec4 along;
    Vec4 rest;
    Vec4 spin;
    Vec4 torque;
    Mat3 turn;
    Mat3 rot;
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
    Mat3* goal = &self->headingMatrix;
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
        Vec4* pivot;
        if (self->groundContact != 0) {
            pivot = &self->groundContactPoint;
        } else {
            pivot = (Vec4*)self->probeVertex;
        }
        Vec4 arm;
        Vec4 v;
        Vec4 u;
        Vu0::Q(arm) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*pivot));
        Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v180), Vu0::Q(arm));
        AddColliderForce(self, &v);
        Vu0::Q(u) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(arm));
        Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(u));
        AddColliderForce(self, &v);
    }
}

void ApplyPlayerDefaultSteering(Player* self);
void *StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
void* StoreQuadword(u128* out, u128 v);

// Stores v as the direction at dir and steers the player toward the offset along it. Both
// addresses are the inline's parameters, so each call forms its frame address again where
// retail does (addiu in each call's delay slot); written at the call sites, CSE keeps the one
// address in a saved register (docs/TOOLCHAIN.md, "A frame address passed by an inline call
// is not GCSE's").
static inline void SteerAlongDirection(Player* self, Vec4* off, Vec4* dir, s128 v, f32 t)
{
    StoreQuadword((u128*)dir, v);
    SteerColliderTowardRotation(self, 0, 0, off, (f32*)dir, t);
}

// The player's per-step physics: steps the collider, then applies the steering of the current
// state: states 2, 3, 7, 4 and 6 have their own step functions, state 13 steers by its sub-state,
// state 9 holds against gravity for the first quarter second, state 11 does nothing, and the rest
// use ApplyPlayerDefaultSteering.
void StepPlayer(Player* self, f32 t)
{
    Mat3 m;
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
            BuildAxisAngleMatrix((const Vec4*)&g_unitZVector, (Mat3*)&m, self->heading);
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
            SteerColliderTowardPosition(self, 0, 0, (Vec4*)&g_zeroVector, D_002637A0, t);
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


// Fills in the friction and bounce of a contact for the player from its state: state 13 uses two
// fixed rates, state 7 none, a contact the player can stand on (virtual method 90) a fixed
// friction, and state 4 other fixed rates for most sub-states. The friction is divided by the
// gravity scale at the end.
void ComputePlayerSlideRates(Player* self, BodyContact* out, s32 end)
{
    f32 a;
    f32 b;
    if (self->state == 0xD) {
        a = g_slideRateFirst;
        b = g_slideRateSecond;
    } else if (self->state == 7) {
        goto zero_both;
    } else if (((VFn_170410*)self->desc)[90](self, out, end) != 0) {
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


// In state 4 with flag 0x10, lowers the contact limit to the weight (mass times gravity), scaled by
// the frame time with flag 1; in other states uses the collider's clamp.
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
void ComputeObjectSteeringHeading(f32 a, f32 b, PlacedObject* self, f32* p1, f32* p3, f32* out0, f32* out1, f32* out2);

// Carries out what was asked of the player since the last frame, by flags: 8 takes the jump kind, 1
// sets the state and sub-state, 2 the aim mode, 0x10 runs the callback.
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

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
// Frees the player's chain of pooled contacts and, for the states that are pinned to something,
// puts a contact back: state 7 pins to the path, state 6 to the target, and state 8 (holding a
// ledge) adds an object contact at the ledge point, offset by the ledge slack and the hand offset.
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
        Vec4 pos;
        Mat3 m;
        Vec4 k;
        TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec4*)self->ledgeLocalPoint, &pos);
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


// Outside state 0xD uses the collider's test. In state 0xD a contact counts as ground when its
// normal points up enough (z 0.7 or more on the side) and its kind is 4 to 6 on side 0.
s32 IsPlayerGroundContact(Player* self, BodyContact* e, s32 idx)
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


// The player's contact resolution for one end of a contact. In state 4, the lowest-vertex contact
// takes the heading velocity's part along the surface. In other states but 0xD, a ground contact
// goes through the turning collider's resolution, and a contact on the player's own part gets the
// velocity of the player's spin at the point subtracted.
void ResolvePlayerContact(Player* self, BodyContact* c, s32 idx)
{
    ContactEnd03* e = &c->end[idx];
    if (self->state == 4) {
        if (c->kind == 1 && idx == 0 && (Vec4*)c->featureEnd0 == self->lowestVertex) {
            Vec4 t;
            u128 n = Vu0::Rotate(self->headingMatrix, Vu0::Q(self->headingVelocity));
            Vu0::Q(t) = Vu0::Sub(n, Vu0::MulX(Vu0::Q(c->normal), Vu0::Dot(n, Vu0::Q(c->normal))));
            Vu0::Q(c->end[0].v30) = Vu0::Add(Vu0::Q(c->end[0].v30), Vu0::Q(t));
        }
    } else if (self->state != 0xD) {
        if (((s32 (*)(Player*, BodyContact*, s32))self->desc06()->m56)(self, c, idx)) {
            ResolveTurningColliderGroundContact(self, c, idx);
        } else if (e->part == (Collider*)self) {
            Vu0::Q(e->v30) = Vu0::Sub(Vu0::Q(e->v30), Vu0::Cross(Vu0::Q(self->v160), Vu0::Sub(Vu0::Q(e->point), Vu0::Q(self->v140))));
        }
    }
}

// An object the player was queued to (+0x2BE0, +0x26D4): its walker at +0x2D4, a walker handle at
// +0x2D8, and the list of the objects at +0x304 (count at +0x300) whose own walkers it sets.
struct WalkerHost { u8 pad00[0x140]; Vec4 v140; u8 pad150[0x2D0 - 0x150]; s32 levelFlag; void* walker; void* f2D8; u8 pad2DC[0x300 - 0x2DC]; s32 count; WalkerHost* list[1]; };
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
    Vec4 vC0;              // 0xC0
    u8 padD0[0x134 - 0xD0];
    void* p134;             // 0x134
};
PlayerNoticeEffect* CreateEffect(s32 kind, EffectOwner* sys);
void AddEffectListener(void* obj, void* arg);
f32 GetAnimationMarkerTime(Animation* self, s32 key);
f32* FindAnimationMarkerEvent(Animation* anim, s32 key);
void ReleasePlayerToState2(Player* self);
extern f32 D_002637CC;
extern s32 g_spinTargetRateDefault;
extern s32 g_spinTargetRateSubState8;
extern f32 g_gameClock[];

static inline s32 MinOfCounts(s32 a, s32 b)
{
    return a < b ? a : b;
}

// The player's message handler, after the switched collider's: kinds 5 and 7 (an animation player
// ended) queue the follow-up state or aim mode, kind 0x13 is an animation marker (spin rate, focus
// hold, root motion, effects, flags by code), kinds 0xA and 0xB set or clear the hit collider, and
// kind 2 releases the player to state 2 when the object it is bound to goes away.
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
            if (other == 0 || src != (void*)((StateWalker*)other)->player) {
                break;
            }
        }
        switch (msg->code) {
        case 0x138: {
            Vec4 v;
            AnimationTrack* track = src->anim->movedTrack;
            if (track == 0) {
                break;
            }
            PositionCurve* c = track->pos;
            c->vt->eval(c, self, src->time, src->speed, 0, 0, &v);
            Vu0::Q(v) = Vu0::Rotate(self->headingMatrix, Vu0::Q(v));
            self->desc02()->m20(self, &v);
            if (src == (void*)self->stateAnimPlayer) {
                Vec4 w;
                u128 s = Vu0::FromFloat(-1.0f);
                Vu0::Q(self->headingVelocity) = Vu0::MulX(Vu0::Q(v), s);
                Vu0::Q(w) = s;
            }
            break;
        }
        case 0x13C:
            if (self->subState == 8) {
                self->spinTargetRate = (f32)g_spinTargetRateSubState8;
            } else {
                self->spinTargetRate = (f32)g_spinTargetRateDefault;
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
                    fx->vt->m00(fx, (u8*)&((PlacedObject*)self->f59C)->v140, D_002637CC, 0);
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
                    fx->vt->m00(fx, (u8*)&((PlacedObject*)h->f2D8)->v140, 1.0f / D_002637CC, 0);
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
            self->pressArmed = 1;
            break;
        case 0x15F:
            self->pressArmed = 0;
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
            self->containingCollider = (Collider*)msg->source;
            for (u32 k = 0; k < 8; k++) {
                self->hitStamps[k].time = 0;
            }
        }
        break;
    case 0xB:
        if (msg->obj == self && msg->source == self->containingCollider) {
            self->containingCollider = 0;
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
struct PoseHolderDesc { u8 pad00[8]; void (*m2)(PoseHolder47* self, Vec4* out, f32 t, s32 a); };
struct PoseHolder47 { PoseHolderDesc* desc; };
// The object at 0x2208: a frame at +0x18 and a holder of poses at +0x34.
struct PoseTarget { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PoseHolder47* holder; };
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

// Turns the player's heading toward the aim target (an object) or, failing that, the point on the
// aim curve, using the direction from the player in the x/y plane. Gives 0 when it has neither.
s32 AimPlayerAtTarget(Player* self)
{
    Vec4 pos;
    Vec4 d1;
    Vec4 d2;
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
struct PosedPart { u8 pad00[0x10]; s8 state; s8 next; u8 pad12[0x20 - 0x12]; Vec4 offset; u8 pad30[0x40 - 0x30]; Mat3 rotation; };

void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec4* origin, Vec4* vel, Vec4* velSum, Vec4* spin, Vec4* spinSum);
void TransformPointAtTime(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin, f32 t);

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
static inline void SampleCurveDirection(PathCurve* c, PlacedObject* frame, f32 t, Vec4* dir)
{
    if (c->vt->m02 != 0)
        ((void (*)(PathCurve*, f32, s32, Vec4*))c->vt->m02)(c, t, 0, dir);
    TransformDirectionBetweenFrames(frame, 0, dir, dir);
}

// Poses the player's rig parts each frame. On a track in state 6 (sub-state 0x10, aim mode 4 or 5)
// the rig gets one of two fixed poses. Then the motion of what the player stands on or rides
// (ground contact, target node, track) is turned into an offset for the lead part and two others
// through a pull curve; on a rail the path lean and its three blend weights are eased too.
void PosePlayerTargetPart(Player* self)
{
    s32 mode;
    if (self->state == 6 && self->targetMode == 4 && self->subState == 0x10 && (u32)(self->aimMode - 4) < 2) {
        void* angles;
        mode = 2;
        if (((PathRecord*)self->targetTrack)->isRail != 0) {
            Vu0::Q(((PosedPart*)self->rigPoseSource)->offset) = Vu0::Q(*(Vec4*)D_00263820);
            angles = D_00263830;
        } else {
            Vec4 d;
            Mat3 m;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PosedPart*)self->footPartA)->offset), Vu0::Q(((PosedPart*)self->footPartB)->offset));
            f32 angle = D_00263850 * ArctangentOfRatio(d.z, D_00263854);
            BuildAxisAngleMatrix((const Vec4*)&g_unitYVector, (Mat3*)&m, angle);
            Vu0::Q(((PosedPart*)self->rigPoseSource)->offset) = Vu0::Add(Vu0::Q(*(Vec4*)D_00263840), Vu0::Rotate(m, Vu0::Sub(Vu0::Q(*(Vec4*)D_00263800), Vu0::Q(*(Vec4*)D_00263840))));
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
        ((const PlacedObjectDescriptor*)self->rigObject->desc)->m2B(self->rigObject);
    }
    Vec4 rest;
    Vec4 pos;
    Vec4 vel;
    Vec4 along;
    Vec4 side;
    Vec4 k;
    Vec4 push;
    Vu0::Q(rest) = Vu0::Q(g_zeroVector);
    PlacedObject* frame = 0;
    Vec4* at = 0;
    PosedPart* lead = (PosedPart*)self->rigAttachment;
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
                    ((void (*)(PathCurve*, f32, Vec4*, Vec4*))c->vt->m01)(c, self->trackPos, &pos, &vel);
                TransformPointBetweenFrames(frame, 0, &pos, &pos);
                at = &pos;
                if (((PathRecord*)self->targetTrack)->isRail != 0) {
                    Vu0::Q(vel) = Vu0::DivX(Vu0::Q(vel), Vu0::Length(Vu0::Q(vel)));
                    f32 speed = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v150), Vu0::Q(vel)));
                    Vu0::Q(k) = Vu0::FromFloat(speed);
                    Vu0::Q(along) = Vu0::MulX(Vu0::Q(vel), Vu0::Q(k));
                    f32 t = self->trackDistance + speed * g_motionLookaheadTime;
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
        Vu0::Q(push) = Vu0::Q(g_zeroVector);
    }
    Vu0::Q(((PosedPart*)self->rigAttachment)->offset) = Vu0::Q(push);
    f32 e1 = EvalCurve3(D_00263870, ((PosedPart*)self->footPartA)->offset.z);
    f32 e2 = EvalCurve3(D_00263870, ((PosedPart*)self->footPartB)->offset.z);
    f32 z;
    if (push.z < e1)
        z = e2 <? push.z;
    else
        z = e2 <? e1;
    ((PosedPart*)self->rigAttachment)->offset.z = z;
    if (self->aimMode == -1) {
        u128 s = Vu0::MulX(Vu0::Q(push), Vu0::ScalarAt(D_002637E8[0]));
        Vu0::Q(((PosedPart*)self->f2504)->offset) = s;
        Vu0::Q(((PosedPart*)self->f2508)->offset) = s;
    } else {
        ((PosedPart*)self->f2508)->offset = ((PosedPart*)self->f2504)->offset = g_zeroVector;
    }
}

// The record of a probe the player keeps for each of its two parts (+0x1190, +0x1290):
// func_001719E8 fills it (the animation it was measured for, whether the segment hit, the probe
// radius, the part's position, the probe's start and the segment's ends) and func_00171C80 reads
// it back for the block of the part.
struct ProbeRecord { Animation* animation; s32 hit; f32 radius; u8 pad0C[4]; Vec4 v10; Vec4 v20; Vec4 v30; Vec4 v40; };
// The node the player's state selects, the holder of the part's body and the body's two extents.
struct ProbeNode { u8 pad00[8]; Animation* animation; };
struct ProbeNodeBase { u8 pad00[0x100]; Vec4 v100; };
struct ProbeBody { u8 pad00[0x60]; Vec4 v60; Vec4 v70; void* f80; ProbeNodeBase* f84; };
struct ProbeHolder { u8 pad00[0x224]; ProbeBody* body; };
s32 CollectBoundsSpans(Vec4* p, Vec4* a, Vec4* b, f32 radius, s32 count, ColliderSpan* out);

// Measures a foot probe for a part, only when the state's animation has changed since the record
// was filled: samples the animation (at its marker 0x142 time, or 0) for the foot, the part and the
// body, then stores in the record the probe's start, the segment's ends, the radius (the body's two
// extents plus 10) and the first collider span hit by the segment.
void MeasurePlayerFootProbe(void* self, void* a, void* b, void* part, f32 k, void* d)
{
    Player* pl = (Player*)self;
    ProbeHolder* obj = (ProbeHolder*)b;
    ProbeRecord* rec = (ProbeRecord*)d;
    ProbeNode* node;
    if (pl->state == 0) {
        if (pl->aimMode < 10) {
            if (pl->aimMode < 6) {
                node = (ProbeNode*)((StateWalker*)pl->stateWalker)->player;
            } else {
                node = (ProbeNode*)pl->aimAnimPlayer;
            }
        } else {
            node = (ProbeNode*)((StateWalker*)pl->stateWalker)->player;
        }
    } else if (pl->stateWalker != 0) {
        node = (ProbeNode*)((StateWalker*)pl->stateWalker)->player;
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
    Vec4 v0;
    Vec4 v10;
    Vec4 v20;
    Mat3 m30;
    Vec4 v60;
    Vec4 v70;
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
    rec->v30 = *(Vec4*)&span.q[0];
    rec->v40 = *(Vec4*)&span.q[1];
}

struct ProbeResult { u8 pad00[0x20]; Vec4 v20; };
Collider* FindNearestSpanObject(s32 flags, Vec4* a1, Vec4* a2, s32 count, Collider** list, ColliderSpan* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec4* a, Vec4* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);


// Checks one foot's ground with the probe MeasurePlayerFootProbe stored: casts the stored segment
// against the colliders in its box, and on a hit writes the offset from the hit to the probe's
// start into the part's record. Gives 0 only when nothing is hit while the player is on the ground
// and the segment's far end is below -85; every other case gives 1.
s32 ProbePlayerFootGround(Player* self, void* record, void* part)
{
    ProbeRecord* p = (ProbeRecord*)record;
    ProbeResult* result = (ProbeResult*)part;
    if (p->hit == 0) {
        return 1;
    }
    PushBackMemoryMark();
    ColliderSpan span;
    Vec4 from;
    Vec4 to;
    Vec4 world;
    s32 count;
    Collider** list;
    TransformPointBetweenFrames(self, 0, &p->v30, &from);
    TransformPointBetweenFrames(self, 0, &p->v40, &to);
    GatherCollidersInBox(self->world, (Collider*)self->root, &from, &to, 0, 0, &count, &list);
    Collider* found = FindNearestSpanObject(0, &from, &to, count, list, &span);
    PopBackMemoryMark();
    if (found != 0) {
        Vu0::Q(span.q[0]) = Vu0::Sub(Vu0::Q(span.q[0]), Vu0::Q(g_unitZVector));
        TransformPointBetweenFrames(0, (PlacedObject*)self, (Vec4*)&span, &world);
        Vu0::Q(result->v20) = Vu0::Sub(Vu0::Q(world), Vu0::Q(p->v10));
        return 1;
    }
    result->v20 = g_zeroVector;
    if (self->groundContact != 0 && p->v40.z < -85.0f) {
        return 0;
    }
    return 1;
}

s32 AimPlayerAtTarget(void* self);

void MeasurePlayerFootProbe(void* self, void* a, void* b, void* part, f32 k, void* d);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec4* origin, Vec4* vel, Vec4* velSum, Vec4* spin, Vec4* spinSum);


// The per-frame update of state 0: turns the heading toward the aim target or, standing on a moving
// object, with its spin (limited to 10), then measures and tests both foot probes. The first time
// one finds no ground, it moves the state walker to its entry 0x148 and latches that with f118C.
void UpdatePlayerState0(Player* self)
{
    Vec3 loc;
    if (AimPlayerAtTarget(self) == 0) {
        if (self->groundContact != 0) {
            ComputeObjectMotionInFrame((PlacedObject*)self->groundContactPart, 0, &self->groundContactPoint, 0, (Vec4*)&loc, 0, 0);
            loc.z = ClampToMagnitude(loc.z, 10.0f);
            self->heading = self->heading + loc.z * g_frameDt[0];
        }
    }
    if (self->footPartA == 0) return;
    u8* p1 = (u8*)&self->footProbeA;
    f32 k = 5.0f;
    MeasurePlayerFootProbe(self, self->f628, self->f620, self->footPartA, k, p1);
    u8* p2 = (u8*)&self->footProbeB;
    MeasurePlayerFootProbe(self, self->f62C, self->f624, self->footPartB, k, p2);
    if (ProbePlayerFootGround(self, p1, self->footPartA) != 0) {
        if (ProbePlayerFootGround(self, p2, self->footPartB) != 0) return;
    }
    if (self->f118C != 0) return;
    if (self->stateGraph == 0) return;
    if (FindStateEntryIndex((StateGraph*)self->stateGraph, 0x148) >= 0) TeleportStateWalker((StateWalker*)self->stateWalker, 0x148);
    self->f118C = 1;
}


// Launches the player along a ballistic arc to target (starting 75 units below its position, at the
// given angle), unless it is in state 4; then goes to state 2 and scales the jump speed, clearing
// f2498 when scale is 0.
void PlacePlayerOnGround(Player* self, void* target, f32 angle, f32 scale)
{
    Vec4 tmp = self->v140;
    tmp.z = tmp.z - 75.0f;
    Vec4 out;
    ComputeBallisticLaunchVelocity(&tmp, (Vec4*)target, &out, (u8*)self, angle);
    self->desc02()->m20(self, &out);
    if (self->state != 4) {
        SetPlayerState(self, 2, 6);
        self->jumpSpeed = self->jumpSpeed * scale;
        if (scale == 0.0f) {
            self->f2498 = 0;
        }
    }
}

// From state 3 or 7 (jump kind 1), or from state 6 with target mode 4 or 5, goes to state 2.
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


// Builds the rotation of the spin part (f61C) at a point in the frame: the player's rotation turned
// by the spin angle minus the rate times the frame time times t (about the z axis in sub-state 8,
// the x axis otherwise), then combined with the part's own rotation, into *out.
void OrientPlayerSpinPart(Player* self, Mat3* out, f32 t)
{
    Vec4 axis;
    Mat3 m;
    if (self->subState == 8) {
        axis = g_unitZVector;
    } else {
        axis = g_unitXVector;
    }
    BuildAxisAngleMatrix((const Vec4*)&axis, (Mat3*)&m, self->spinAngle - g_frameDt[0] * self->spinRate * t);
    Mat3 a;
    Mat3 c;
    MulRotationThenCopy(&c, self->rot, m);
    MulRotationCopiedVia(out, a, c, ((PlacedObject*)self->f61C)->rot);
}

extern void* g_currentWarpPage;
extern f32 D_00263894;
extern f32 D_00263898;
extern f32 g_scaleApproachRamp[3];
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
void OrientPlayerSpinPart(Player* self, Mat3* out, f32 t);
void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf);
// The player's draw-time pose: eases the two scale factors (f2724, f2728) toward 1, or toward fixed
// values in state 6 mode 3 when no object is active, and scales the transform while they are under
// 1. It then sets the bounds radius to 500, adds a trail point (from the spin part while spinning)
// and, except in state 12 sub-state 0x22, applies the transform to the object.
void BlendPlayerPose(Player* self, void* a, void* b)
{
    ScaledTransform out;
    Vec4 pos;
    Mat3 turned;
    Mat3 m90;
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
        f32 ramp = self->outerFadeScale;
        target = D_00263898;
        self->outerFadeScale = k * D_00263894 + (1.0f - k) * ramp;
    } else {
        f32 one = 1.0f;
        self->outerFadeScale = ApproachValueWithRamp(self->outerFadeScale, one, g_gameClock[2], (RampProfile*)g_scaleApproachRamp, 0);
        target = one;
    }
    f32 spin = ApproachValueWithRamp(self->innerFadeScale, target, g_gameClock[2], (RampProfile*)g_scaleApproachRamp, 0);
    self->innerFadeScale = spin;
    if (self->outerFadeScale < 1.0f || spin < 1.0f) {
        BuildPlacedObjectTransform(self, (Quad16*)b, &out);
        b = &out;
        out.innerFade = self->innerFadeScale;
        out.outerFade = out.outerFade * self->outerFadeScale;
    }
    self->boundRadius = 500.0f;
    if (self->spinAngle != 0.0f || self->spinRate != 0.0f) {
        OrientPlayerSpinPart(self, &m90, 0.0f);
        PlacedObject* obj = (PlacedObject*)self->f23D0;
        Mat3* b3 = &obj->rot;
        u128 r0 = Vu0::Q(m90.r[0]);
        u128 r1 = Vu0::Q(m90.r[1]);
        u128 r2 = Vu0::Q(m90.r[2]);
        Vu0::Q(pos) = Vu0::RotateRows(r0, r1, r2, Vu0::Q(obj->pos));
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
    // the object's class is not known
    if (g_currentWarpPage != 0 && (u32)(*(s32*)((u8*)g_currentWarpPage + 0x2D0) - 2) < 2) {
        return;
    }
    ApplyPlacedObjectTransform(self, (Camera*)a, (ScaledTransform*)b);
    ((Collider*)self->f61C)->flags &= ~(0x8000ULL << 17);
}


// Recomputes the collider frame, then the two follow probes toward the linked parts (f610 and
// f614), or marks them invalid when there are none or the player is in state 6 with target mode 7.
void RecomputePlayerFrame(Player* self)
{
    RecomputeTurningColliderFrame(self);
    if (self->state == 6 && self->targetMode == 7) {
        self->footProbeB.valid = 0;
        goto clear;
    }
    {
        void* a1 = self->linkPartA;
        if (a1 == 0) {
            self->footProbeB.valid = 0;
            goto clear;
        }
        if (self->linkPartB == 0) {
            self->footProbeB.valid = 0;
            goto clear;
        }
        f32 k = 6.0f;
        // retail's caller evaluates the radius before the probe, as the fifth argument
        ((void (*)(void*, PlacedObject*, void*, PlacedObject*, f32, FollowProbe*))BuildPartProbeTowardLink)(self, (PlacedObject*)a1, a1, (PlacedObject*)self->f620, k, (FollowProbe*)((u8*)&self->footProbeA));
        ((void (*)(void*, PlacedObject*, void*, PlacedObject*, f32, FollowProbe*))BuildPartProbeTowardLink)(self, (PlacedObject*)self->linkPartB, self->linkPartB, (PlacedObject*)self->f624, k, (FollowProbe*)((u8*)&self->footProbeB));
    }
    return;
clear:
    self->footProbeA.valid = 0;
}

void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
void OrientPlayerSpinPart(Player* self, Mat3* out, f32 t);

// Draws the player: places the two foot parts at their probe spans, and while the spin is on draws
// the spin part four times at quarter steps of the spin (OrientPlayerSpinPart with t = 0, 0.25,
// 0.5, 0.75). Then, in state 3, updates the link pose, draws the turning collider, queues the trail
// ribbon if it is enabled and queues the marker ring.
void DrawPlayer(Player* self, void* a, void* b)
{
    f32 buf[12];
    f32 out[20];
    s32 i;

    if (!(self->state == 6 && self->targetMode == 7))
    {
        PlacePartAtProbeSpan(self, (PlacedObject*)self->linkPartA, (PlacedObject*)self->linkPartA, &self->footProbeA);
        PlacePartAtProbeSpan(self, (PlacedObject*)self->linkPartB, (PlacedObject*)self->linkPartB, &self->footProbeB);
    }
    if (self->spinAngle != 0.0f || self->spinRate != 0.0f)
    {
        ((PlacedObject*)self->f61C)->flags &= ~(1ULL << 32);
        BuildPlacedObjectTransform(self, (Quad16*)b, (ScaledTransform*)out);
        out[16] *= 0.25f;
        for (i = 0; i < 4; i++)
        {
            OrientPlayerSpinPart(self, (Mat3*)buf, (f32)i * 0.25f);
            BuildMatrixFromRotationAndTranslation((const Vec4*)&((PlacedObject*)self->f61C)->v140, (const Mat3*)buf, (Mat4A*)out);
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

// Advances the player's spin angle (radians): at the target rate while one is set, wrapped at 2 pi;
// with no target it ramps the angle back to a full turn (spinRate follows the ramp) and zeroes it
// on arrival.
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
        f32 r = ApproachValueWithRamp(self->spinAngle, 6.2831855f, g_frameDt[0], (RampProfile*)&g_spinRampParams, &self->spinRate);
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
    BodyContact* chain;       // 0x554
};

s32 IsObjectOfKind(BaseObject* list, s32 key);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);

// Filters the player's contact list after collision: contacts with the held object go back to the
// pool unless the other side is of kind 0x46, and contacts with the contact owner that method 56
// accepts are moved onto the owner's chain. In state 8 it also makes the ledge point the ground
// contact and drops the contacts with the ledge's root, except kind 0xB.
void PrunePlayerContacts(Player* self)
{
    ContactRow03* row;
    BodyContact** slot;
    BodyContact* n;
    BodyContact* head = 0;
    ExtractContactsByPartMode(self, (BodyContact**)self->contactChainHead);
    row = self->contacts->head;
    if (row) {
        do {
            slot = &row->head;
            n = row->head;
            if (n) {
                do {
                    s32 k = (n->end[0].body != self);
                    if (n->end[k].part == self->heldObject) {
                        void* other = n->end[1 - k].body;
                        // PrunePlayerContacts matches only with k passed in $a2, which no other
                        // call of IsObjectOfKind sets
                        if (other == 0 || ((s32 (*)(void*, s32, s32))IsObjectOfKind)(other, 0x46, k) == 0) {
                            *slot = n->next;
                            n->next = head;
                            head = n;
                        } else {
                            slot = &n->next;
                        }
                    } else if ((void*)n->end[1 - k].body == ((ContactChainOwner*)self->contactOwner) && ((s32 (*)(Player*, BodyContact*))self->desc06()->m56)(self, n)) {
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
        TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec4*)self->ledgeLocalPoint, &self->groundContactPoint);
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


// Saves the collider's previous position and clears the bound point count.
void SavePlayerPreviousPosition(Player* self)
{
    SaveColliderPreviousPosition(self);
    self->boundsPointCount = 0;
}

// EXACT: declaring D_00261860 as an array (extern f32 D_00261860[], passed as D_00261860[0]) moved the float load into the jal delay slot.



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

// Updates the collider's bounds, then grows them by a sphere around each of the player's extra
// bound points.
void UpdatePlayerBounds(Player* self)
{
    s32 i = 0;
    UpdateColliderBounds(self);
    if (self->boundsPointCount > 0) {
        Vec4* p = self->boundsPoints;
        do {
            ExpandColliderBoundsBySphere(self, p, self->boundsRadius);
            i++;
            p++;
        } while (i < self->boundsPointCount);
    }
}


// Looks through the five slot objects at f25D8 in the order 0, 2, 1, 3, 4 and gives back the first
// that is attached, with *out set to its group (0, 1, 2, 2, 1 for those slots); null when none is.
void* FindFirstAttachedSlotObject(Player* self, s32* out)
{
    void* p = self->slotObjects[0];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 0;
        return self->slotObjects[0];
    }
    p = self->slotObjects[2];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 1;
        return self->slotObjects[2];
    }
    p = self->slotObjects[1];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 2;
        return self->slotObjects[1];
    }
    p = self->slotObjects[3];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 2;
        return self->slotObjects[3];
    }
    p = self->slotObjects[4];
    if (p != 0 && IsObjectAttached((BaseObject*)p) != 0) {
        *out = 1;
        return self->slotObjects[4];
    }
    return 0;
}


// The player's collision callback for another collider: adds probe contacts (never in states 3, 7
// and 0xD; in state 4 only for sub-states 0x24, 0x2A and 0x2B; not when probeContactsDisabled is
// set), updates both foot probes' nearest span and, if an attached slot object is on the other
// collider's parent chain, adds the mesh contacts between them.
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
    KeepNearestPartSpan(self, a1, a4, &self->footProbeA);
    KeepNearestPartSpan(self, a1, a4, &self->footProbeB);
    v = (Collider*)FindFirstAttachedSlotObject(self, &idx);
    if (v)
    {
        for (cur = a1; cur; cur = (Collider*)cur->parent)
        {
            // address arithmetic over a variable index
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

// 0 in state 3 or 0xD, 3 otherwise.
s32 GetPlayerContactMode(Player* self)
{
    if (self->state == 3 || self->state == 0xD) {
        return 0;
    }
    return 3;
}

extern f32 g_cameraPoseMaxOffset;
extern f32 g_cameraPoseMinOffset;
extern f32 g_cameraHeightMaxOffset;
extern f32 g_cameraHeightMinOffset;
extern f32 g_cameraHeightStartOffset[2];
extern f32 D_002638D0[4];
extern f32 g_pivotApproachRamp[4];
extern f32 g_heightApproachRamp[4];

void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
struct PushRecord;
void FillPlayerPushRecord(Player* self, PushRecord* out);
#include "value_range.h"
typedef void (*PoseAtFn)(PoseHolder47* self, Vec4* pos, Vec4* dir, f32 t);

// The pose a collider's slot captures each frame (CaptureSwitchedColliderPose fills pos).

// Fills the pose the camera reads each frame, after the switched collider's. Unless the focus is
// held, the focus is the point along the path in state 7, or the player's position with a clamped,
// ramped camera height. The pose offset is eased to zero, and the flags, weight and stamp time are
// set by state and sub-state.
void CapturePlayerPose(Player* self, ColliderPose* pose, f32 dt)
{
    u8* out = (u8*)pose;
    Vec4 last = self->focusPoint;
    CaptureSwitchedColliderPose(self, out, dt);
    if (self->holdFocus == 0) {
        if (self->state == 7) {
            Vec4 pos;
            Vec4 dir;
            PoseHolder47* h = ((PoseTarget*)self->aimCurve)->holder;
            PoseAtFn fn = (PoseAtFn)h->desc->m2;
            if (fn != 0) {
                fn(h, &pos, &dir, self->pathPos);
            }
            TransformPointBetweenFrames((PlacedObject*)(((PoseTarget*)self->aimCurve)->frame), 0, &pos, &pos);
            Vu0::Q(pose->position) = Vu0::Q(pos);
            TransformDirectionBetweenFrames((PlacedObject*)(((PoseTarget*)self->aimCurve)->frame), 0, &dir, &dir);
            u128 d = Vu0::Q(dir);
            d = Vu0::NormalizeOr(d, Vu0::Q(g_zeroVector));
            Vu0::Q(pose->dir) = Vu0::MulX(d, Vu0::ScalarAt(self->pathSpeed));
            Vu0::Q(dir) = d;
            self->cameraHeight = pose->position.z - 125.0f;
        } else {
            if (self->state == 3) {
                Vec4 pos;
                GetObjectWorldPosition(self->boundObject, &pos);
                self->cameraHeight = pos.z + g_cameraHeightStartOffset[0];
            } else if (self->groundContact != 0) {
                self->cameraHeight = self->groundContactPoint.z;
            } else if (g_camera->snapping != 0) {
                self->cameraHeight = self->v140.z - 75.0f;
            }
            f32 h = self->cameraHeight;
            f32 lo = self->pos.z + g_cameraHeightMinOffset;
            f32 hi = self->pos.z + g_cameraHeightMaxOffset;
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
                pose->position.z = z;
            } else {
                f32 v = ApproachValueWithRamp(last.z, z, g_gameClock[2], (RampProfile*)g_heightApproachRamp, 0);
                pose->position.z = v;
                f32 zlo = self->pos.z + g_cameraPoseMinOffset;
                f32 zhi = self->pos.z + g_cameraPoseMaxOffset;
                f32 w;
                if (v < zlo) {
                    w = zlo;
                } else if (zhi < v) {
                    w = zhi;
                } else {
                    w = v;
                }
                pose->position.z = w;
            }
        }
        if (self->state == 6 && self->targetMode == 0) {
            FillPlayerPushRecord(self, (PushRecord*)out);
        }
        u128 d = ApproachPointWithRamp(Vu0::Q(self->poseOffset), Vu0::Q(g_zeroVector), dt, (RampProfile*)g_pivotApproachRamp, 0);
        Vu0::Q(self->poseOffset) = d;
        Vu0::Q(pose->position) = Vu0::Add(Vu0::Q(pose->position), d);
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
        self->poseStampTime = g_gameTime[0];
    }
    pose->stampTime = self->poseStampTime;
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
    self->focusPoint = pose->position;
}

#undef POSE
#undef PL

// The object the player is pushed along (+0x23A0): a frame at +0x18, flags at +0x50 and a holder
// at +0x34 that has an array of floats, or answers a length through its descriptor.
struct PushHolderDesc;
struct PushHolder { PushHolderDesc* desc; u8 pad04[4]; s32 f08; s32 count; u8 pad10[4]; f32* values; };
struct PushHolderDesc {
    u8 pad00[8];
    void (*m2)(PushHolder* self, Vec4* out, f32 t, s32 a);
    u8 pad0C[0x20 - 0x0C];
    f32 (*length)(PushHolder* self);
};
struct PushObject { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PushHolder* holder; u8 pad38[0x50 - 0x38]; u32 flags; };
struct PushRecord { u8 pad00[0x30]; f32 heading; s32 f34; };

// Fills the record the pose takes while the player is pushed along an object (state 6, mode 0): the
// heading from the heading matrix's x axis and, by the on/off phase, the point v2690 the player is
// pushed toward. It also eases the force (+0x300) of the player's on/off object, pushing back near
// each end of the curve.
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
            Vec4 point;
            PushHolder* holder = ((PushObject*)self->targetCurve)->holder;
            if (holder->desc->m2 != 0) {
                holder->desc->m2(holder, &point, limit, 0);
            }
            TransformPointBetweenFrames((PlacedObject*)(((PushObject*)self->targetCurve)->frame), 0, &point, &self->v2690);
            self->v2690.z = self->v2690.z + 125.0f;
        } else {
            Vec4 k;
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
    f32* slot = &target->block2F0.f10[0];
    self->ownOnOffObject->block2F0.f10[0] = ApproachValueWithRamp(*slot, force, g_frameDt[0], (RampProfile*)g_forceApproachRamp, 0);
}



// Does the switched collider's activation and shows the mode label of the saved hint mode (or -1
// when b is null).
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
void GatherCollidersInBox(World* world, Collider* skip, Vec4* a, Vec4* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
s32 CollectColliderSpans(Collider* self, Vec4* a1, Vec4* a2, s32 a3, ColliderSpan* a4);

// Whether there is ground within offset of the player's lowest vertex: gathers the colliders in the
// box from that vertex to vertex + offset and gives 1 if any span they give along that segment has
// a surface normal with z above 0.7 (a walkable slope), 0 otherwise.
s32 HasFloorAtPlayerOffset(Player* self, Vec4* offset)
{
    s32 count;
    Collider** list;
    Vec4 from;
    Vec4 to;
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
            if (p->time[0] != 0.0f && ((Vec4*)&p->q[2])->z > 0.7f) {
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
extern s32 g_currentMode;
extern s32 g_padRouting;
extern s32 g_padSelectFlags;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void UpdatePlayerGrabs(Player* self);
extern s32 g_controlBlockingElementCount;
extern s32 g_resumeSoundSetupDone;
extern StepSequence* g_playerStepSequence;

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
    if (g_controlBlockingElementCount > 0 || self->walkerActivation != 0 || self->firstActivation != 0 || self->secondActivation != 0) {
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
                    Vec4 off;
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
            Vec4 off;
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
            Vec4 off;
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
        if (seq != 0 && seq->state2D4 == 3 && seq->buttonSkipBlocked == 0 && (rec->flags & 0xC) && *(s32*)seq->target304 != 0) {
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
                    self->buttonPressTime = g_gameTime[0];
                }
            }
            if (self->pressArmed != 0 && g_gameTime[0] - self->buttonPressTime < g_playerCallbackWindow[0]) {
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
                target = ChooseNearbyPlayerTarget((PlayerTargetState*)self, 0, &self->targetMode);
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
                target = ChooseNearbyPlayerTarget((PlayerTargetState*)self, 0, &self->targetMode);
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
                target = ChooseNearbyPlayerTarget((PlayerTargetState*)self, 0, &self->targetMode);
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
                    PopStackElement(&g_elementStack);
                    break;
                }
            } else if (self->subState == 0x22) {
                CaptionBox* box = &g_typedTextCaptionBox;
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
        SetPlayerVelocityFromHeading(self, (const Vec4*)self->eightWaySlots, self->eightWayBlend, self->stickHeading, self->stickLevel);
        break;
    case 1:
        SetPlayerBlendWeights(self->stickHeading, self->stickLevel, self, (TurnBlendRecords*)self->sixWayItems, self->sixWayBlend);
        break;
    case 4:
    case 10: {
        self->headingVelocity = g_zeroVector;
        PlayerNoticePlayer* src = (PlayerNoticePlayer*)self->stateAnimPlayer;
        if (src != 0) {
            AnimationTrack* track = src->anim->movedTrack;
            if (track != 0) {
                PositionCurve* c = track->pos;
                if (c != 0) {
                    Vec4 v;
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

s32 HasAnimationDrivenAttachment(SwitchedCollider *self);
void UpdatePlayerWhileAnimationDriven(Player* self);
void ClearRootTries(PlacedObject* self);
void PosePlayerTargetPart(Player* self);
void RecordPlayerTargetMemo(Player* self);
void RunPlayerQueuedActivations(Player* self);
extern f32 g_phaseTimeOffset;

struct PhasePeriodObject { u8 pad00[0x34]; f32 period; };
struct PhaseTimeMessage { u8 pad00[8]; PhasePeriodObject* f8; u8 pad0C[0x14 - 0xC]; f32 f14; f32 f18; };
struct PhasePathShape;
struct PathShapeDescriptor { u8 pad00[0x30]; void (*m30)(PhasePathShape* self, Vec4* at, f32 t, s32 a, Vec4* out, s32 b, s32 c, s32 d); };
struct PhasePathShape { PathShapeDescriptor* desc; };
struct PhasePathTarget { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PhasePathShape* shape; };
struct AimedTarget { u8 pad00[0x8C]; f32 radius; };
struct ContactedObject;
struct ContactedObjectDescriptor {
    u8 pad00[0x12C];
    s32 (*m12C)(ContactedObject* self, BodyContact* c, OwnerMessage* msg);
    u8 pad130[0x140 - 0x130];
    void (*m140)(ContactedObject* self, OwnerMessage* msg);
    u8 pad144[0x160 - 0x144];
    void (*m160)(ContactedObject* self);
};
struct ContactedObject {
    ContactedObjectDescriptor* desc;
    u8 pad04[0x18 - 0x04];
    ContactedObject* parent;     // 0x18
    u8 pad1C[0x4E0 - 0x1C];
    s32 f4E0;                       // 0x4E0
};

// Which end of the contact the object is: 0 when it is end 0's body, else 1.
static inline s32 ContactEndOf(BodyContact* c, void* obj)
{
    return c->end[0].body != obj;
}

// The player's per-frame update: the turning collider's, pending state requests, the
// animation-driven case and the per-state update (blend weights and phase sounds, the ledge hold,
// facing the host or camera). In aim mode 0 it tests the bounds points against the bound object or
// curve; it also hands queued contacts to their owners and runs the spin and target upkeep.
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
            f32 phase = WrapModulo((((PhaseTimeMessage*)self->stateAnimPlayer)->f14 + g_phaseTimeOffset * ((PhaseTimeMessage*)self->stateAnimPlayer)->f18) / ((PhaseTimeMessage*)self->stateAnimPlayer)->f8->period, 1.0f);
            PlayPhaseCrossingSound(self, (f32*)&self->phaseSoundStates[0], phase);
        }
        break;
    case 5:
        UpdateEightEntryBlendWeights(self, (BlendSlot*)self->eightWaySlots, self->eightWayBlend);
        {
            f32 phase = WrapModulo((((PhaseTimeMessage*)self->stateAnimPlayer)->f14 + g_phaseTimeOffset * ((PhaseTimeMessage*)self->stateAnimPlayer)->f18) / ((PhaseTimeMessage*)self->stateAnimPlayer)->f8->period, 1.0f);
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
        Vec4 local;
        Vu0::Q(self->ledgeSlack) = ApproachPointWithRamp(Vu0::Q(self->ledgeSlack), Vu0::Q(g_zeroVector), dt, (RampProfile*)g_positionApproachRamp, 0);
        TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec4*)self->ledgeLocalPoint, &local);
        if (ComputeLedgeOffsetForContact(self, (Collider*)self->ledgeCollider, &local, self->ledgeKind, (void*)self->ledgeKey, &self->ledgeOffset) == 0) {
            SetPlayerState(self, 2, 2);
            break;
        }
        self->heading = ArctangentOfRatio(-self->ledgeOffset.y, -self->ledgeOffset.x);
        break;
    }
    case 9: {
        Vec4 local;
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
            if (g_uprightThreshold < self->rot.r[2].z) {
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
    ((ContactedObject*)self)->desc->m160((ContactedObject*)self);
    ReleaseFarPlayerLinks(self);
    NotifyPlayerGroundObject(self);
    ClearRootTries(self);
    if (self->aimMode == 0) {
        Vec4 local;
        Vec4 pts[3];
        Vec4 dirs[3];
        Vec4 closest;
        f32 t;
        f32 dist;
        f32 gap;
        if (self->boundObject != 0) {
            GetObjectWorldPosition((BaseObject*)self->boundObject, &local);
            for (s32 i = 1; i < self->boundsPointCount; i++) {
                MeasurePointToSegment(&local, &self->boundsPoints[i - 1], &self->boundsPoints[i], &t, &dist);
                if (dist < ((AimedTarget*)self->aimTarget)->radius + self->boundsRadius) {
                    SetPlayerState(self, 3, 0x33);
                    break;
                }
            }
        } else if (self->aimCurve != 0) {
            s32 i;
            for (i = 0; i < self->boundsPointCount; i++) {
                TransformPointBetweenFrames(0, (PlacedObject*)((PhasePathTarget*)self->aimCurve)->frame, &self->boundsPoints[i], &pts[i]);
                PhasePathShape* s = ((PhasePathTarget*)self->aimCurve)->shape;
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
    if (*(BodyContact**)self->contactChainHead != 0) {
        for (BodyContact* c = *(BodyContact**)self->contactChainHead; c != 0; c = c->next) {
            ContactedObject* o = (ContactedObject*)c->end[1 - ContactEndOf(c, self)].part;
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
                ((ContactedObject*)self)->desc->m140((ContactedObject*)self, &msg);
            }
        }
        FreePooledContactChain((World*)self->world, *(BodyContact**)self->contactChainHead);
        *(BodyContact**)self->contactChainHead = 0;
    }
    UpdatePlayerSpin(self);
    PosePlayerTargetPart(self);
    RecordPlayerTargetMemo(self);
    RunPlayerQueuedActivations(self);
}

// The update used while an attached object drives the player's animation: leaves state 3 for state
// 2 and puts state 0xD in its sub-state 0x38, clears the aim mode and, in the other states except
// 2, 3 and 13 to 16, takes heading and speed from ComputeObjectSteeringHeading and switches to
// state 0 or 1 by whether the speed is positive (states 4 and 12 only zero the heading velocity).
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



// Picks the animation node for the player's state and makes the turning collider follow its mesh:
// state 6 by target mode, state 4 by sub-state (falling back along the D_00263930 chain when a node
// is missing), state 2 sub-states 0xC and 0xD the special node, other states their own node, and
// node 0 when the choice is empty. State 0xD changes nothing.
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
                    s32 k = g_stateFallbackChain[i - 0x24];
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

struct LayeredPart {
    u8 pad_00[0x10];
    s8 f10;
};

// Sets which of the player's parts are drawn: bit 0 of flags selects the three rig parts and bit 1
// the two foot parts (each part's layer byte becomes 9 when on, -1 when off), then tells the five
// objects to refresh through method 0x2B.
void SetPlayerPartLayers(Player* self, s32 flags)
{
    if (self->rigAttachment != 0) {
        s32 a = flags & 1;
        ((LayeredPart*)self->rigAttachment)->f10 = a ? 9 : -1;
        ((LayeredPart*)self->f2504)->f10 = a ? 9 : -1;
        ((LayeredPart*)self->f2508)->f10 = a ? 9 : -1;
        s32 b = flags & 2;
        ((LayeredPart*)self->footPartA)->f10 = b ? 9 : -1;
        ((LayeredPart*)self->footPartB)->f10 = b ? 9 : -1;
        PlacedObject* o = self->rigObject;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->f618;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->f61C;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->linkPartA;
        o->desc02()->m2B(o);
        o = (PlacedObject*)self->linkPartB;
        o->desc02()->m2B(o);
    }
}





void CreateAnimationPlayer(Animation* self, BaseObject* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
ColliderAttachment* TakeAttachRecord(World* self);
void ReleaseAttachRecords(World* self, ColliderAttachment* node);
void PopActiveSequenceElement(World* world);

extern s32 D_00270454;
extern f32 g_pathFinishMargin;
extern f32 g_pathStartMargin;
extern f32 g_steepSlopeThreshold;
extern f32 g_pathProbeDistance;

// The shape a track object (+0x2208, +0x23BC) holds at +0x34: slot 1 the position and direction
// at a length, slot 2 the position.
struct PlayerTrackShape;
struct PlayerTrackShapeClass {
    void* m0;
    void (*m1)(PlayerTrackShape* self, f32 t, Vec4* pos, Vec4* dir);    // 0x04
    void (*m2)(PlayerTrackShape* self, f32 t, Vec4* pos, s32 a);         // 0x08
};
struct PlayerTrackShape {
    PlayerTrackShapeClass* desc;
    u8 pad04[4];
    s32 looped;             // 0x08
    s32 count;              // 0x0C
    f32* start;             // 0x10
    f32* lengths;           // 0x14
};

// An animation argument CreateAnimationPlayer takes: the held object as argument 0x61.
struct AnimationArgument {
    s32 id;
    void* value;
};

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
f32 GetAnimationMarkerTime(Animation* self, s32 key);
void StopAnimationPlayer(AnimationPlayer* self);
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
static inline Vu0::Vec NormalizeInPlace_175170(Vec4& v, const Vec4& fallback)
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

// A word of another object by its offset. Its uses below are left raw: the objects they reach
// (f2490, f2494, boundObject, aimCurve, leapTarget, the tracks) are of classes the code does not
// show, so no type has these fields.
// The base is a pointer (every use passes one): a word holding an address is not a base.
#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))

// Changes the player's state and sub-state (nothing happens if both are unchanged): runs the
// cleanup for leaving the old ones, then the set-up for the new ones, which picks the animation or
// state graph, sound, part layers and aim mode. It stores them with the time, selects the state's
// animation node and replaces the playing animation.
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
            if (self->containingCollider == 0) {
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
            ((Attachment*)self->snapshotPoseFirst)->mode0 = -1;
            ((Attachment*)self->snapshotPoseFirst)->mode1 = -1;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            ((Attachment*)self->snapshotPoseSecond)->mode1 = -1;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            SetTurningColliderLinkFlag(self, 1);
            if (self->linkSystem != 0) {
                RemoveColliderAttachment(((ColliderAttachment*)self->linkSystem)->target, (ColliderAttachment*)self->linkSystem);
                ReleaseAttachRecords((World*)self->world, (ColliderAttachment*)self->linkSystem);
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
                // the object's class is not known
                AT(Vec4, self->f2490, 0x300) = g_zeroVector;
            }
            if (self->f2494 != 0) {
                // the object's class is not known
                AT(Vec4, self->f2494, 0x300) = g_zeroVector;
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
            self->cameraSpringMode = 0;
            if (self->soundLevelEntry != 0) {
                ReleaseSoundLevel((SoundLevelEntry*)(self->soundLevelEntry));
                self->soundLevelEntry = 0;
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
            BaseObject* o = (BaseObject*)self->slotObjects[2];
            self->aimTarget = 0;
            self->boundObject = 0;
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 12:
            RemoveCameraControllers(g_camera, 0xF, 6, (CameraController*)&g_camera->ctl460, self, 0);
            if (D_00270454 != 0) {
                PopStackElement(&g_elementStack);
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
            self->hook = self->savedHook;
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
            ((Attachment*)self->snapshotPoseFirst)->mode0 = 2;
            ((Attachment*)self->snapshotPoseFirst)->mode1 = 2;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            ((Attachment*)self->snapshotPoseSecond)->mode1 = 2;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            Vec4 pos;
            Mat3 rotA;
            Mat3 rotB;
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
                // the object's class is not known
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
            // the object's class is not known
            sound = AT(s32, self->boundObject, 0xA8);
            SetPlayerAimMode(self, 1);
            for (Collider* c = (Collider*)((BaseObject*)self->boundObject)->parent; c != 0; c = (Collider*)c->parent) {
                if (c->desc->flags & 2) {
                    if ((c->mode450 != 3 && c->positionAttachment != 0 && c->positionAttachment->mode0 == 1) ||
                        (c->mode470 != 3 && c->orientationAttachment != 0 && c->orientationAttachment->mode1 == 1)) {
                        ColliderAttachment* a = TakeAttachRecord((World*)self->world);
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
            PlayerTrackShape* s = (PlayerTrackShape*)((PathCurveObject*)track)->curve;
            // the object's class is not known
            s32 turn = AT(s32, track, 0x58);
            Vec4 a;
            Vec4 b;
            switch (turn) {
            case 0:
                self->pathFlipped = 0;
                break;
            case 1:
                self->pathFlipped = 1;
                break;
            default: {
                if (s->desc->m2 != 0) {
                    s->desc->m2(s, self->pathPos + g_pathProbeDistance, &a, 0);
                    if (s->desc->m2 != 0) {
                        s->desc->m2(s, self->pathPos - g_pathProbeDistance, &b, 0);
                    }
                }
                TransformPointBetweenFrames((PlacedObject*)((BaseObject*)self->aimCurve)->parent, 0, &a, &a);
                TransformPointBetweenFrames((PlacedObject*)((BaseObject*)self->aimCurve)->parent, 0, &b, &b);
                Vec4 d;
                *(u128*)&d = NormalizeOrElse_175170(Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b)), Vu0::Vec::Of(g_unitZVector)).q;
                self->pathFlipped = d.z < -g_steepSlopeThreshold;
                break;
            }
            }
            f32 len = self->aimCurvePos;
            self->pathPos = len;
            if (s->looped == 0) {
                if (self->pathFlipped != 0) {
                    self->pathPos = Clamp_175170(len, s->lengths[0] + g_pathFinishMargin, s->lengths[s->count - 1] - g_pathStartMargin);
                } else {
                    self->pathPos = Clamp_175170(len, s->lengths[0] + g_pathStartMargin, s->lengths[s->count - 1] - g_pathFinishMargin);
                }
            }
            if (s->desc->m2 != 0) {
                s->desc->m2(s, self->pathPos, &a, 0);
            }
            TransformPointBetweenFrames((PlacedObject*)((BaseObject*)self->aimCurve)->parent, 0, &a, &a);
            TransformPointBetweenFrames(self, 0, &self->v23E0, &b);
            Vu0::Q(self->pathPoseOffset) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
            // the object's class is not known
            sound = AT(s32, self->aimCurve, 0x50);
            Vu0::Q(self->poseOffset) = Vu0::Sub(Vu0::Q(self->focusPoint), Vu0::Q(a));
            break;
        }
        case 8: {
            SetPlayerAimMode(self, -1);
            sound = 0x59;
            SetFlaggedLinkContactMask(self, (BaseObject*)self->ledgeCollider, 1);
            Vec4 pos;
            Mat3 m;
            Vec4 k;
            TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec4*)self->ledgeLocalPoint, &pos);
            Vu0::Q(k) = Vu0::FromFloat(-1.0f);
            Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->ledgeOffset), Vu0::Q(k));
            BuildPerpendicularPair(&m.r[0], &m.r[1], &g_unitZVector, &g_unitZVector);
            Vu0::Q(pos) = Vu0::Sub(Vu0::Q(pos), Vu0::Rotate(m, Vu0::Q(self->ledgeHandOffset)));
            anim = self->f1038;
            Vu0::Q(self->ledgeSlack) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(pos));
            self->pathPoseOffset = g_zeroVector;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        }
        case 4:
            if (self->f2490 != 0) {
                // the object's class is not known
                AT(Vec4, self->f2490, 0x300) = *(Vec4*)D_00263970;
            }
            if (self->f2494 != 0) {
                // the object's class is not known
                AT(Vec4, self->f2494, 0x300) = *(Vec4*)D_00263970;
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
                Vec4 dir;
                Vec4 tan;
                PlayerTrackShape* s = (PlayerTrackShape*)((PathCurveObject*)track)->curve;
                if (s->desc->m1 != 0) {
                    s->desc->m1(s, self->trackPos, 0, &tan);
                }
                TransformDirectionBetweenFrames((PlacedObject*)((BaseObject*)track)->parent, 0, &tan, &dir);
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
                self->desc02()->m20(self, (Vec4*)&g_zeroVector);
                loud = 1;
                self->desc02()->m21(self, (Vec4*)&g_zeroVector);
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
                self->soundLevelEntry = PushSoundLevel(-20);
            }
            break;
        }
        case 9: {
            Vec4 d;
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
            self->savedHook = self->hook;
            self->hook = 0;
            self->flags538 |= (u64)1 << 40;
            self->radius3CC = D_00262E30;
            if (self->stateNodes[13] != 0) {
                SetTurningColliderFollowedMesh(self, 0, 0);
            }
            self->headingVelocity = g_zeroVector;
            SetPlayerAimMode(self, -1);
            break;
        case 16:
            self->headingVelocity = g_zeroVector;
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
            self->headingVelocity = g_zeroVector;
            break;
        }
        case 15:
            anim = self->f2754;
            self->headingVelocity = g_zeroVector;
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
            self->headingVelocity = g_zeroVector;
            break;
        case 9:
            if (self->leapTarget != 0) {
                // the object's class is not known
                Collider* c = AT(Collider*, self->leapTarget, 0x60);
                if (c != 0) {
                    c->partMode = 0;
                }
                self->leapTarget = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            self->headingVelocity = g_zeroVector;
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
            if (state != 6 || self->targetMode != ((TargetVector*)self->targetPoint)->f58) {
                self->targetPoint = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 12:
            if (state != 6 || self->targetMode != ((TargetCurve*)self->targetCurve)->mode40) {
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
            BaseObject* o = (BaseObject*)self->slotObjects[1];
            if (o != 0) {
                o->desc->m03(o);
            }
            o = (BaseObject*)self->slotObjects[3];
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
            // the object's class is not known
            AT(Vec4, self->f2490, 0x300) = g_zeroVector;
            break;
        case 28:
            if (self->forcedOnOffObject != 0) {
                SetOnOffObjectForcedState((void*)self->forcedOnOffObject, 0);
                self->forcedOnOffObject = 0;
            }
            break;
        case 55: {
            BaseObject* o = (BaseObject*)self->slotObjects[4];
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
            Vec4 v;
            self->steerKeepsDirection = 0;
            self->f2498 = 1;
            self->jumpStickPhase = 0;
            f32 now = g_gameTime[0];
            self->stickReleaseTime = now;
            self->stickFullTime = now;
            self->jumpStartTime = now;
            self->jumpSpeed = g_jumpSpeedBase * Fpu::Sqrt(self->gravityScale);
            self->groundContact = 0;
            StartSoundEffect(0x4F, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            ComputePlayerJumpVelocity(self, &v);
            switch (self->jumpKind) {
            case 1:
                anim = self->jumpAnimKinds134;
                break;
            case 4:
                self->jumpSpeed *= g_jumpKind4SpeedScale;
                anim = self->jumpAnimKinds134;
                break;
            case 3:
                self->jumpSpeed *= g_jumpKind3SpeedScale;
                anim = self->jumpAnimKinds134;
                break;
            case 0:
            case 2:
                if (self->jumpKind == 2) {
                    anim = self->jumpAnimKind2;
                } else {
                    anim = self->jumpAnimDefault;
                }
                break;
            }
            if (anim == 0) {
                anim = self->jumpAnimDefault;
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
                    anim = self->jumpAnimKinds134;
                    break;
                case 0:
                    anim = self->jumpAnimDefault;
                    break;
                case 2:
                    anim = self->jumpAnimKind2;
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
                anim = self->jumpAnimDefault;
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
                anim = self->jumpAnimDefault;
            }
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            // the object's class is not known
            Collider* c = AT(Collider*, self->leapTarget, 0x60);
            anim = self->f1030;
            if (c != 0) {
                c->partMode = 3;
            }
            break;
        }
        case 10:
        case 11: {
            Vec4 v;
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
            Vec4 v;
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
            self->jumpSpeed = g_jumpSpeedBase * Fpu::Sqrt(self->gravityScale);
            self->v2290 = self->v150;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->groundContact = 0;
            anim = self->jumpAnimDefault;
            self->v2290.z = 0.0f;
            break;
        case 44:
            self->f2498 = 1;
            self->groundContact = 0;
            if (self->requestAccepted != 0) {
                anim = self->subStateAnims[43];
            } else {
                anim = self->jumpAnimDefault;
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
            Vec4 v;
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
                // the object's class is not known
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
                        TargetCurve* o = (TargetCurve*)self->targetCurve;
                        if (o->f4C == 0) {
                            self->forcedOnOffObject = 0;
                        } else if (o->target != 0) {
                            self->forcedOnOffObject = (s32)o->target;
                        } else {
                            self->forcedOnOffObject = (s32)self->ownOnOffObject;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                            p->desc->m15(p, ((BaseObject*)self->targetCurve)->parent);
                            ((OnOffObject*)self->forcedOnOffObject)->obj = (OnOffCurve*)((PathCurveObject*)self->targetCurve)->curve;
                        }
                    } else if (self->targetPoint != 0) {
                        TargetVector* o = (TargetVector*)self->targetPoint;
                        if ((s32)o->target == 0) {
                            self->forcedOnOffObject = 0;
                        } else if (o->targetId != 0) {
                            self->forcedOnOffObject = o->targetId;
                        } else {
                            self->forcedOnOffObject = (s32)self->ownOnOffObject;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                            p->desc->m15(p, ((BaseObject*)self->targetPoint)->parent);
                            ((OnOffObject*)self->forcedOnOffObject)->orbitsPoint = 1;
                            ((OnOffObject*)self->forcedOnOffObject)->v400 = *(Vec4*)&((TargetVector*)self->targetPoint)->q40;
                            ((OnOffObject*)self->forcedOnOffObject)->orbitRadius = ((TargetVector*)self->targetPoint)->f5C;
                        }
                    }
                    if ((OnOffObject*)self->forcedOnOffObject == self->ownOnOffObject) {
                        const Vec4* z = &g_zeroVector;
                        OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m1D(p, (Vec4*)z);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m1E(p, (Mat3*)&g_identityMatrix);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m20(p, (Vec4*)z);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m21(p, (Vec4*)z);
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
            anim = self->pathBlendItem;
            break;
        case 26:
            anim = self->pathBlendItem;
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
            PushCameraController(g_camera, 6, (CameraController*)&g_camera->ctl460, self, 0);
            break;
        case 34: {
            f32 dim = 0.6f;
            SetVolumeChannelFactor(5, 0, dim);
            SetVolumeChannelFactor(5, 1, dim);
            StartCameraSounds((CameraSoundOwner*)&g_camera->ctl460);
            RequestCameraSnap(g_camera, 0);
            g_typedTextCaptionBox.child = self->pendingCaption;
            self->pendingCaption = 0;
            PushStackElement(&g_elementStack, &g_typedTextCaptionBox);
            break;
        }
        case 35:
            if ((void*)self->f25D0 != 0) {
                anim = (void*)self->f25D0;
            }
            RemoveCameraControllers(g_camera, 0xF, 6, (CameraController*)&g_camera->ctl460, self, 0);
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
                    // the object's class is not known
                    AT(Vec4, self->f2490, 0x300) = *(Vec4*)D_00263980;
                }
            }
            if (sub == 47) {
                Vec4 d;
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(self->v140));
                self->heading = ArctangentOfRatio(d.y, d.x);
            }
            break;
        case 41:
        case 48: {
            Vec4 d;
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
            self->desc02()->m21(self, (Vec4*)&g_zeroVector);
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
            if (self->stateAnimPlayer != 0 && (void*)self->stateAnimPlayer->key == self->linkBlend) {
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
            Vec4 v;
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
            Vu0::Vec len = NormalizeInPlace_175170(v, g_zeroVector);
            f32 k = Vu0::ToFloatMoved(len) / self->radius3CC;
            Vec4 spin;
            Vu0::Q(spin) = Vu0::FromFloats(-k * v.y, k * v.x, 0.0f);
            self->desc02()->m21(self, &spin);
            anim = self->f25D4;
            if (self->slotObjects[4] != 0) {
                if (MaskWorldBitsBySave() & 0x400) {
                    BaseObject* o = (BaseObject*)self->slotObjects[4];
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
            AnimationArgument args[2];
            AnimationArgument* arg = args;
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

// Sets state 11 when flag is non-zero and state 0 otherwise.
void SwitchPlayerState11(void* self, s32 flag)
{
    SetPlayerState((Player*)self, flag ? 11 : 0, -1);
}

// Sets the flag that disables the probe contacts and clears f4B8.
void SetPlayerProbeContactsDisabled(Player* self, s32 value)
{
    self->probeContactsDisabled = value;
    self->stateBits = 0;
}

// Finds the node a node query applies to: starts at the query's holder (or its parent) and walks up
// the parent chain, giving 0 if a node of the excluded list of n is met. Each node gets the query's
// out value from its tint slot chosen by the query kind and is asked (method 0x2D) to accept it;
// the first that does is returned, null when the chain ends.
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

// Comparison for a sort into ascending key order: 1 when the first key is larger, else -1.
s32 CompareKeysAscending(FloatKeyedItem* a, FloatKeyedItem* b)
{
    s32 r = -1;
    if (a->key > b->key) r = 1;
    return r;
}

extern ObjectList g_class75List;
typedef s32 (*SortCompareFn)(void* a, void* b);
void HeapSortRecords(void* records, s32 n, s32 size, SortCompareFn cmp);
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
    Vec4 pos;
    Vec4 motion;
    MeshHitSample hit;
    NodeQuery* rec;
    Collider* target;
    s32 mask;
    s32 n;
    s32 i;

    if (self->state == 4) {
        goto done;
    }
    if (self->subState == 7) {
        target = (Collider*)self->slotObjects[1];
        mask = 4;
    } else if (self->aimMode == 4 || self->aimMode == 6 || self->aimMode == 5 || self->aimMode == 7) {
        target = (Collider*)self->slotObjects[0];
        mask = 2;
    } else if (self->state == 10) {
        target = (Collider*)self->slotObjects[2];
        mask = 8;
    } else if (self->subState == 8) {
        target = (Collider*)self->slotObjects[3];
        mask = 4;
    } else if (self->subState == 0x37 && (MaskWorldBitsBySave() & 0x400)) {
        target = (Collider*)self->slotObjects[4];
        mask = 8;
    } else {
        goto done;
    }
    n = 0;
    if (IsObjectAttached(target)) {
        f32 scale = 1000.0f;
        Class75Object* o;
        for (o = (Class75Object*)g_class75List.head; o != 0; o = *(Class75Object**)&o->link) {
            if (o->enabled == 0) {
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
            ComputeObjectMotionInFrame((PlacedObject*)o->parent, 0, &pos, (Vec4*)&rec->dir, 0, 0, 0);
            ComputeObjectMotionInFrame((PlacedObject*)o->parent, 0, &pos, (Vec4*)&motion, 0, 0, 0);
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
    for (BodyContact* c = self->queryContacts; c != 0; c = c->next) {
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
        ComputeObjectMotionInFrame((PlacedObject*)c->end[e].part, 0, &rec->pos, (Vec4*)&rec->dir, 0, 0, 0);
        Vu0::StoreX(rec->key, Vu0::Dot(Vu0::Q(target->m110.r[0]), Vu0::Q(rec->pos)));
    }
    HeapSortRecords(recs, n, 0x40, (s32 (*)(void*, void*))CompareKeysAscending);
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


// False in state 12 with sub-state 0x22; otherwise true when the player's camera controller is not
// the top one.
s32 IsPlayerCameraFree(Player* self)
{
    if (self->state == 12 && self->subState == 0x22) return 0;
    return IsTopCameraController((CameraController*)&g_camera->ctl454) == 0;
}

void SetPlayerState(Player* self, s32 state, s32 sub);

// Starts the collider effect, and for effect modes 0 and 1 puts the player in state 9 with sub-
// state 0x1C and 0x1D.
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

// Says what the player can do with an interact target, by state: out[0] (can start it) and out[1]
// (can take it), mostly depending on the target's mode being 1. out[0] is cleared unless g_elementStack.state
// is 3.
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
    if (g_elementStack.state != 3)
        out[0] = 0;
}



// For an interact target of mode 1 or 2 shows it in the typed-text caption box. Otherwise, unless
// in state 0xC, requests state 0xC (sub-state 0x21) with the target as its caption.
void ReceivePlayerNode(Player* self, InteractTarget* node)
{
    if ((u32)(node->mode - 1) < 2) {
        g_typedTextCaptionBox.child = node;
        PushStackElement(&g_elementStack, &g_typedTextCaptionBox);
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


// Moves the collider, clears the trail ring and f2768.
void SetPlayerPosition(Player* self, Vec4* pos)
{
    SetColliderPosition(self, pos);
    ResetTrailRing((TrailRing*)self->trail);
    self->targetMemoCount = 0;
}




void StartPlacedObject(void* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void SetFollowObjects(void* a, s32 b, s32 c);
AnimRecord* FindAnimRecord(s32 key);



// Clears the trail ring and registers the switched collider.
void RegisterPlayer(Player* self)
{
    ResetTrailRing((TrailRing*)self->trail);
    RegisterSwitchedCollider(self);
}

// An object the player was queued to (+0x2BE0): a walker handle at +0x2D8, and the list of the
// objects at +0x304 (count at +0x300) whose own walkers it sets.
struct WalkerListObject;

// In states 0, 1 and 5, activates the queued first or second activation object (method 0x2F) if it
// is not running yet. Otherwise it handles a queued walker host whose walker waits at key 0x22E:
// with a positive level-record count the player goes to state 9 (sub-state 0x1E), else the group's
// walkers are set to target 0x231 and the player turns toward the host.
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
    if (((StateNotifier*)a)->state == 0) {
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
        Vec4 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(host->v140), Vu0::Q(g_player->v140));
        g_player->heading = ArctangentOfRatio(d.y, d.x);
    }
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first



void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin);



// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 g_world5CountdownRequest;

void ReplaceAnimationPlayer(Animation* anim, BaseObject* owner, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);


void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.


// A walker's current and target keys (GetStateWalkerCurrentKey, GetStateWalkerTargetKey).
struct WalkerKeys { s32 a, b; };


// Remembers the object as the pending walker activation when the player is not in state 9 and the
// object's state walker is at (or heading to) state 0x22E.
void QueuePlayerWalkerActivation(Player* self, u8* other)
{
    WalkerKeys r;
    if (self->state != 9) {
        // the object's class is not known
        GetStateWalkerCurrentKey((StateWalker*)(*(void**)(other + 0x2D8)), &r.a);
        GetStateWalkerTargetKey((StateWalker*)(*(void**)(other + 0x2D8)), &r.b);
        if (r.a == 0x22E && (r.b == r.a || r.b == -1)) {
            self->walkerActivation = other;
        }
    }
}



void ReplaceAnimationPlayer(Animation* anim, BaseObject* owner, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);







extern s32 g_world5CountdownRequest;


void StartPlacedObject(void* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);


void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin);


void StartPlacedObject(void* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);






// Remembers an interact target of mode 0 as the first pending activation (not in state 9).
void QueuePlayerFirstActivation(Player* a0, InteractTarget* a1)
{
    if (a0->state != 9 && a1->mode == 0) {
        a0->firstActivation = a1;
    }
}

// Remembers an interact target of mode 0 as the second pending activation (not in state 9).
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
    Vec4 v10;
};
typedef void (*ShapeAtFn)(void* self, f32 t, Vec4* out, s32 x);
struct ShapeOwner {
    ShapeAtFn* vtbl;
};
struct TargetShaped {
    u8 pad00[0x34];
    ShapeOwner* shape;
};
s32 IsObjectOfKind(BaseObject* list, s32 key);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
// EXACT: gravity read in each expression that weights it, as a value of its own: the -0.5 dt
// weight then comes before the load in the insn order, and sched1 keeps it there
// (docs/TOOLCHAIN.md, "sched1").
void ComputeTargetArc(Player* self, TargetArcSource* src, f32 dt, Vec4* vel, Vec4* pos, Vec4* acc)
{
    Vec4 p;
    Vec4 v1;
    Vec4 a;
    Vec4 off = *(Vec4*)D_002639C0;
    BaseObject* parent;
    if (src->target != 0) {
        parent = src->target->parent;
        if (IsObjectOfKind(src->target, 0x76)) {
            p = *(Vec4*)&((TransformObject*)src->target)->pos;
            off = *(Vec4*)D_002639D0;
        } else if (IsObjectOfKind(src->target, 0x70)) {
            BaseObject* obj = src->target;
            ShapeOwner* shape = ((TargetShaped*)obj)->shape;
            if (shape->vtbl[2] != 0) {
                shape->vtbl[2](shape, src->t, &p, 0);
            }
            Mat3 frame;
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
            p = *(Vec4*)&((TransformObject*)src->target)->pos;
        } else {
            p = g_zeroVector;
        }
    } else {
        parent = 0;
        p = src->v10;
    }
    a = g_zeroVector;
    // retail's caller evaluates the time before the pointers, as the third argument
    ((void (*)(PlacedObject*, PlacedObject*, f32, Vec4*, Mat3*, Vec4*, Vec4*))TransformPointAtTime)((PlacedObject*)parent, 0, dt, &p, 0, &a, 0);
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








// A target the player may aim at: two quads (ScoreTargetCandidate's hit, ChooseBestTargetCandidate's
// result, the pair the player keeps at 0x2B70).
struct TargetHit {
    union {
        Vec4 q0;           // 0x00
        void* obj;          // 0x00: the object aimed at, none for a point on the ground (func_001788F0)
    };
    Vec4 q1;               // 0x10
};
// The record the player keeps at 0x2514 for a jump at a target: when it lands and the two ends
// of its arc (func_00178598).
struct TargetLaunch {
    u8 pad0[0x18];
    f32 landTime;           // 0x18: the game time it lands
    u8 pad1[0x20 - 0x1C];
    Vec4 q20;              // 0x20
    Vec4 q30;              // 0x30
};

// func_00178598's locals: the arc's three points, the chosen target and its time.
struct TargetArcFrame {
    Vec4 q0;
    Vec4 q1;
    Vec4 q2;
    Vec4 p0;
    Vec4 p1;
    f32 fl;
};

void ChooseBestTargetCandidate(Player* self, s32 n, BaseObject** items, TargetHit* out, f32* outf);
void ComputeTargetArc(Player* self, TargetArcSource* src, f32 dt, Vec4* vel, Vec4* pos, Vec4* acc);
void SetPlayerState(Player* self, s32 state, s32 sub);


// Starts the player's leap at a target over f seconds: when s2 is null the best candidate is chosen
// first (ChooseBestTargetCandidate). Computes the arc, records the landing time and the arc's ends
// in the pose record, gives the player the launch velocity, keeps the target's quads and enters
// state 4, sub-state 0x2C.
void LaunchPlayerAtTarget(Player* self, TargetHit* s2, f32 f)
{
    TargetArcFrame fr;
    fr.fl = f;
    if (s2 == 0) {
        ChooseBestTargetCandidate(self, 0, 0, (TargetHit*)&fr.p0, &fr.fl);
        s2 = (TargetHit*)&fr.p0;
    }
    void* q1 = &fr.q1;
    ComputeTargetArc(self, (TargetArcSource*)s2, fr.fl, (Vec4*)q1, &fr.q0, &fr.q2);
    ((TargetLaunch*)self->selfPoseSource)->landTime = g_gameTime[0] + fr.fl;
    ((TargetLaunch*)self->selfPoseSource)->q20 = fr.q0;
    ((TargetLaunch*)self->selfPoseSource)->q30 = fr.q2;
    self->desc02()->m20(self, (Vec4*)q1);
    self->contactQuads[0] = s2->q0;
    self->contactQuads[1] = s2->q1;

    SetPlayerState(self, 4, 0x2C);
}

INCLUDE_RODATA(D_0024AFA0);
extern const f32 D_0024AFA0;

s32 CollectSpansFromList(void* a0, void* a1, s32 count, Collider** list, s32 a4, ColliderSpan* a5);

// Picks the flight time of a leap to the target: for each of nine durations in g_targetArcDurations
// it samples the arc in quarter-second steps, adds up the length of collider spans the arc passes
// through, and scores that total times the arc's launch strength. The duration with the lowest
// score is written to *out.
void ChooseTargetArcTime(PlacedObject* self, void* target, s32 count, Collider** list, f32* out)
{
    Vec4 start;
    Vec4 b;
    Vec4 a;
    Vec4 c;
    Vec4 cur;
    Vec4 prev;
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

extern f32 g_hitRingOffsets[32];
extern f32 g_searchBoxMargin[4];
extern f32 D_00263AA0[4];
extern f32 D_00263AB0[4];

// Scores a leap target candidate, 0 being a clean one: adds penalties when the landing point has no
// floor (2000), has an obstacle above it (2000) or lacks floor around it (1500), and a cost from
// the distance of each listed object to the landing point. Gives back the score, with the hit (its
// landing point) in *out and the arc time from ChooseTargetArcTime in *outTime.
f32 ScoreTargetCandidate(Player* self, TargetHit* cand, s32 n, TurningCollider** objs, TargetHit* out, f32* outTime)
{
    typedef Vu0::Vec Vec;
    f32 t = 0.7f;
    PushBackMemoryMark();
    Vec4 lo;
    Vec4 hi;
    Vec4 q;
    ComputeTargetArc(self, (TargetArcSource*)cand, t, 0, &q, 0);
    f32 score = 0.0f;
    Vu0::Q(hi) = Vu0::Max(Vec::Of(self->v140), Vec::Of(q)).q;
    Vu0::Q(lo) = Vu0::Min(Vec::Of(self->v140), Vec::Of(q)).q;
    hi.z = hi.z + 200.0f;
    Vu0::Q(lo) = Vu0::Sub(Vec::Of(lo), Vec::Of(g_searchBoxMargin)).q;
    Vu0::Q(hi) = Vu0::Add(Vec::Of(hi), Vec::Of(g_searchBoxMargin)).q;
    s32 count;
    Collider** list;
    GatherCollidersInBox(self->world, self, &lo, &hi, 0, 0, &count, &list);
    TargetHit hit = *cand;
    if (cand->obj == 0) {
        Vec4 p;
        Vec4 r;
        ColliderSpan span;
        p = r = q;
        p.z = p.z + 125.0f;
        r.z = r.z - 175.0f;
        if (FindNearestSpanObject(0, &p, &r, count, list, &span) == 0 || span.time[0] == score ||
            ((Vec4*)&span.q[2])->z < t) {
            f32 penalty = 2000.0f;
            score = penalty >? score;
            hit.q1 = q;
        } else {
            hit.q1 = *(Vec4*)&span.q[0];
        }
        p = r = hit.q1;
        p.z = p.z + 180.0f;
        r.z = r.z + 5.0f;
        if (FindNearestSpanObject(0, &p, &r, count, list, &span)) {
            f32 penalty = 2000.0f;
            score = penalty >? score;
        }
        for (u32 i = 0; i < 8; i++) {
            Vu0::Q(p) = Vu0::Q(r) = Vu0::Add(Vec::Of(hit.q1), Vec::Of(((Vec4*)g_hitRingOffsets)[i])).q;
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
        Vec4 at;
        if (o->mesh.verts != 0) {
            f32 d = -o->probeDepth - ((Vec4*)o->mesh.verts)[o->probeIndex].z;
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

void StopAnimationPlayer(AnimationPlayer* self);


extern s32 g_displayMode;
extern s32 D_00270B54;
extern s32 D_002717CC;


extern s32 g_displayMode;
extern s32 D_00270B54;
extern s32 D_002717CC;


extern f32 g_gameClock[];
extern Rgba4 g_defaultModelColor;

extern "C" f32 Cosine(f32 x);
void SetObjectTreeRecordValue(World5ModeCollider* o, u32 value);
void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf);


// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];



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
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void ComputeTargetArc(Player* self, TargetArcSource* src, f32 dt, Vec4* vel, Vec4* pos, Vec4* acc);
s32 CompareDistanceFromPlayer(TargetCandidate* a, TargetCandidate* b);
void SortElements(void* base, u32 n, u32 size, s32 (*compare)(const void* x, const void* y));
f32 ScoreTargetCandidate(Player* self, TargetHit* cand, s32 n, TurningCollider** objs, TargetHit* out, f32* outTime);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

// Chooses the player's leap target among the n objects in items: builds a candidate for each
// attached one, sorts them by distance from the player and scores them with ScoreTargetCandidate,
// stopping at a score of 0. If the best is over 1000 it also tries the remembered places of the
// memo. With no candidate at all it gives a point 75 below the player and time 0.75.
void ChooseBestTargetCandidate(Player* self, s32 n, BaseObject** items, TargetHit* out, f32* outf)
{
    u8 scratch[0x80];
    TargetHit hit;
    Vec4 tmp;
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
            ComputeTargetArc(self, (TargetArcSource*)e, 0.7f, 0, (Vec4*)e->point, 0);
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
    for (s32 i = 0; i < self->targetMemoCount; i++) {
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

extern const Vec4 g_zeroVector;
// Keeps the player's memo of places it has stood (up to 32 entries of key object, position or
// distance along it, and time). Each frame it makes the entry for the current place (the object the
// state is bound to, the path position or the ground contact; some states record nothing), moves an
// existing entry within 50 units to the front, or inserts a new one.
void RecordPlayerTargetMemo(Player* self)
{
    Vec4 pos = g_zeroVector;
    TargetMemo tmp;
    u8* key = 0;
    f32 w = 0.0f;
    switch (self->state) {
    case 3: {
        // the object's class is not known
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
            // the object's class is not known
            u8* o = (u8*)self->targetTrack;
            if (*(s32*)(o + 0x50) != 0) {
                return;
            }
            key = o;
            w = self->trackDistance;
            break;
        }
        case 5: {
            // the object's class is not known
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
                if (((TargetCurve*)o)->f5C != 0) {
                    return;
                }
                key = o;
                w = self->targetCurvePos;
            } else {
                // the object's class is not known
                o = (u8*)self->targetPoint;
                if (*(s32*)(o + 0x74) != 0) {
                    return;
                }
                key = o;
                ConvertPositionToWorld((BaseObject*)o, (Vec4*)&tmp);
                Vu0::Q(tmp.pos) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec4*)&tmp));
                w = ArctangentOfRatio(tmp.pos.y, tmp.pos.x) * ((TargetVector*)self->targetPoint)->f5C;
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
        // the object's class is not known
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
    for (i = 1; i < self->targetMemoCount; i++) {
        TargetMemo* e = &self->targetMemo[i];
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
                MoveMemory(&self->targetMemo[2], &self->targetMemo[1], (i - 1) * 0x20);
                self->targetMemo[1] = tmp;
            }
            break;
        }
    }
    if (i >= self->targetMemoCount) {
        if ((u32)self->targetMemoCount < 0x20) {
            self->targetMemoCount++;
        }
        MoveMemory(&self->targetMemo[1], &self->targetMemo[0], self->targetMemoCount * 0x20 - 0x20);
        FillMemory(&self->targetMemo[0], 0, 0x20);
    }
    self->targetMemo[0].key = key;
    self->targetMemo[0].pos = pos;
    self->targetMemo[0].along = w;
    self->targetMemo[0].time = g_gameClock[1];
}
