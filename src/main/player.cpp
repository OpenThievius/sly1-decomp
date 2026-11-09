// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x16F608 to 0x1793C0: the player, class 0x07 (struct Player in
// include/switched_collider.h), its methods, its state changes and its target choice. Its name
// is ours, after the class.
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
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
#include "on_off_object.h"

extern f32 g_frameDt[];
extern f32 g_gameTime[];

// The ramp ApproachValueWithRamp turns the player's spin angle (0x2434) back to zero with
// (func_001727B0); the two ids are those of the spin's links (0x16F, 0x170).
struct SpinRampParams { f32 f0; f32 f4; f32 f8; f32 fC; s32 f10; s32 f14; };

// size: pointer, word accesses only
Player* g_player = 0;
f32 D_00262E14 = 455.0f;
f32 D_00262E18 = 0.699999988f;
f32 D_00262E1C = 0.600000024f;
f32 D_00262E20 = 0.699999988f;
f32 D_00262E24 = 0.600000024f;
f32 D_00262E28 = 1000.0f;
f32 D_00262E2C = 850.0f;
f32 D_00262E30 = 50.0f;

// NEAR: frame, saves, the vtable call and the branch tree match; the 0xD path loads its two floats into $f1/$f0 where retail uses $f0/$f1, so the shared store tail differs

struct Sub_170410 { u8 pad0[0x40]; s32 f40; };
typedef s32 (*VFn_170410)(Player* self, void* out);

f32 D_00262E34 = 0.8f;
f32 D_00262E38 = 0.5f;
f32 D_00262E3C = 0.25f;

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
ObjectLink D_00263558[27] = {
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
f32 D_00263700 = 1.29999995f;
f32 D_00263704 = 238689.0f;
f32 D_00263708 = 0.0f;
f32 D_0026370C = 0.0f;
f32 D_00263710[4] = { -1.5f, 0.00100000005f, 0.0f, 0.0f };

// Globals typed by worker dv02, from retail's bytes and their readers.
f32 D_00263720[4] = { 1.0f, -4.0f, 0.0f, 0.0f };
RampProfile D_00263730 = { 10.0f, 0.0f, 0.5f, 50.0f };
RampProfile D_00263740 = { 40.0f, 0.0f, 0.25f, 200.0f };
RampProfile D_00263750 = { 15.0f, 0.0f, 0.25f, 100.0f };
f32 D_00263760[4] = { -0.200000003f, 0.00200000009f, 0.0f, 0.0f };
f32 D_00263770[4] = { 0.200000003f, 0.0f, 0.800000012f, 0.0f };
f32 D_00263780[4] = { 40.0f, 0.0f, 0.100000001f, 0.0f };
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
f32 D_002637D8 = 0.100000001f;
f32 D_002637DC = 1000.0f;
f32 D_002637E0 = 20.0f;
f32 D_002637E4 = -7.5f;
f32 D_002637E8[2] = { 0.5f, 0.0f };
f32 D_002637F0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_00263800[4] = { -20.0f, 5.0f, -25.0f, 0.0f };
f32 D_00263810[4] = { 0.0f, -0.600000024f, 0.5f, 0.0f };
f32 D_00263820[4] = { -20.0f, 5.0f, -25.0f, 0.0f };
f32 D_00263830[4] = { 0.0f, -0.600000024f, 0.5f, 0.0f };
f32 D_00263840[4] = { 0.0f, 0.0f, -100.0f, 0.0f };
f32 D_00263850 = -0.5f;
f32 D_00263854 = 100.0f;
f32 D_00263858[6] = { 4.0f, 0.0f, 0.5f, 10.0f, 0.0f, 0.0f };
f32 D_00263870[4] = { 0.0f, 0.5f, 0.0f, 0.0f };
f32 D_00263880 = 50.0f;
f32 D_00263884 = -50.0f;
f32 D_00263888[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_00263894 = 0.349999994f;
f32 D_00263898 = 0.0f;
SpinRampParams D_002638A0 = { 50.0f, 0.0f, 0.25f, 0.0f, 0x16F, 0x170 };
f32 D_002638B8 = 75.0f;
f32 D_002638BC = -325.0f;
f32 D_002638C0 = -50.0f;
f32 D_002638C4 = -350.0f;
f32 D_002638C8[2] = { -300.0f, 0.0f };
f32 D_002638D0[4] = { 1.5f, -0.5f, 0.0f, 0.0f };
f32 D_002638E0[4] = { 1500.0f, 0.0f, 0.5f, 0.0f };
f32 D_002638F0[4] = { 4000.0f, 0.0f, 4.0f, 0.0f };
f32 D_00263900[4] = { 600.0f, 300.0f, 0.100000001f, 50.0f };
f32 D_00263910[2] = { 0.150000006f, 0.25f };
f32 D_00263918[3] = { 1000.0f, 0.0f, 0.25f };
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
f32 D_002639E8[10] = { 0.699999988f, 0.800000012f, 0.899999976f, 1.0f, 1.20000005f, 1.39999998f, 1.60000002f, 1.79999995f, 2.0f, 0.0f };
f32 D_00263A10[32] = { 40.0f, 0.0f, 0.0f, 0.0f, 28.2999992f, 28.2999992f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, -28.2999992f, 28.2999992f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 0.0f, -28.2999992f, -28.2999992f, 0.0f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 28.2999992f, -28.2999992f, 0.0f, 0.0f };
f32 D_00263A90[4] = { 200.0f, 200.0f, 200.0f, 0.0f };
f32 D_00263AA0[4] = { 400.0f, -1.0f, 0.0f, 0.0f };
f32 D_00263AB0[4] = { 0.0f, 1000.0f, 0.0f, 0.0f };

void InitTurningCollider(void* self);

void InitPlayer(Player* self)
{
    InitTurningCollider(self);
    self->f2220 = -1;
    self->f223C = -1;
    self->f2228 = -1;
    self->f224C = -1;
    self->f2440[0] = *(Vec4U*)D_002636A0;
    self->f2440[1] = *(Vec4U*)D_002636B0;
    self->f2440[2] = *(Vec4U*)D_002636C0;
    self->f2440[3] = *(Vec4U*)D_002636D0;
    self->f2440[4] = *(Vec4U*)D_002636E0;
    self->f2420 = 15.0f;
    Vu0::Q(self->gravity) = Vu0::FromFloats(0.0f, 0.0f, -1750.0f);
    self->flags = (self->flags & ~(3ULL << 40)) | (1ULL << 40);
    self->v24E0 = *(Vec02*)D_002636F0;
    self->f21C0 = 1;
    self->f2718 = -1;
    self->f2728 = 1.0f;
    self->f2724 = 1.0f;
    self->f2758 = -3.4028235e+38f;
    self->f26D0 = 2.0f;
}

void LoadCollider(void* self);
void ResolveObjectLinks(void* self, s32 id, void* table);
void FindOrBuildMemberGroup(void* a, void* b);

void LoadPlayer(Player* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 0x97, g_playerCharacterLinks);
    FindOrBuildMemberGroup((u8*)self + 0x2428, self);
    self->f2284 = -1.0f;
    self->f21C8 = -1.0f;
    g_player = self;
}

void StartTurningCollider(TurningCollider* self);
void CreateSixEntryBlend(void* self, void* a, void* b);
void CreatePlayerTwoEntryBlend(Player* self);
void CreateEightEntryBlend(void* self, void* a, void* b);
void CreateThreeEntryBlend(void* self, void* a, void* b);
u8* CreatePoseSource(World* root, void* value, u8* table);
void InsertAttachment(void* a, void* b);
void AddMatrixAttachment(void* a, s32 b, void* c);
s32 FindAnimRecord(s32 key);
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void BuildTexturePackets(void* a, RangeRecord* b);
void* CreateTypedRecord(s32 a, void* b, s32 c, s32 d, s32 e);
void ResetPlayerOnOffObject(Player* self);
void ResolvePlayerTableObjects(Player* self);
void SetTurningColliderGravityScale(void* self, f32 v);
void SetColliderMass(Collider* self, f32 m);
void* AllocateZeroedFrontMemory(s32 bytes);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
extern u8 D_0021A9A8[];
extern u8 D_00219588[];
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void SetPlayerState(Player* self, s32 a, s32 b);

#define PS(T, o) (*(T*)((u8*)self + (o)))

void func_0016F810(Player* self)
{
    StartTurningCollider(self);
    ResolveObjectLinks(self, 27, D_00263558);
    CreateSixEntryBlend(self, (u8*)self + 0x720, (u8*)self + 0x900);
    CreatePlayerTwoEntryBlend(self);
    CreateEightEntryBlend(self, (u8*)self + 0xA20, (u8*)self + 0xB20);
    CreateEightEntryBlend(self, (u8*)self + 0xB30, (u8*)self + 0xC30);
    CreateSixEntryBlend(self, (u8*)self + 0xC40, (u8*)self + 0xE20);
    CreateThreeEntryBlend(self, (u8*)self + 0x2360, (u8*)self + 0x2384);
    CreateSixEntryBlend(self, (u8*)self + 0xE30, (u8*)self + 0x1010);
    self->f598 = self;
    self->f5F0 = PS(void*, 0x110C);
    u8* a = CreatePoseSource(self->world, self->f24F8, D_0021A9A8);
    *(s8*)(a + 0x10) = 9;
    *(s8*)(a + 0x11) = 9;
    *(s32*)(a + 0x14) = 3;
    *(s32*)(a + 0x1C) = 2;
    InsertAttachment(self->f24F8, a);
    PS(u8*, 0x24FC) = a;
    AddMatrixAttachment(self->f24F8, 5, &self->f2500);
    AddMatrixAttachment(self->f618, 5, &self->f2504);
    AddMatrixAttachment(self->f61C, 5, &self->f2508);
    AddMatrixAttachment(self->f610, 7, &self->f250C);
    AddMatrixAttachment(self->f614, 7, &self->f2510);
    PS(u8*, 0x2518) = CreatePoseSource(self->world, self->f24F8, D_00219588);
    *(s32*)(PS(u8*, 0x2518) + 0x14) = 1;
    InsertAttachment(self->f24F8, PS(u8*, 0x2518));
    PS(void*, 0x1520) = PS(void*, 0x23D0);
    PS(s32, 0x1524) = FindAnimRecord(0x15A);
    PS(f32, 0x1530) = 0.5f;
    PS(Vec02, 0x1560) = *(Vec02*)D_00263710;
    PS(Vec02, 0x1570) = *(Vec02*)D_00263720;
    PS(s32, 0x1538) = 2;
    TransformPointBetweenFrames(0, PS(s32, 0x23D0), (u8*)self->f23D4 + 0x140, (u8*)self + 0x1540);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(PS(Vec02, 0x1540))));
    Vu0::Q(PS(Vec02, 0x1540)) = Vu0::MulX(Vu0::Q(PS(Vec02, 0x1540)), Vu0::Scalar((len + self->f2420) / len));
    BuildCombinedBlendAnimation(self, 12, 2, (u8*)self + 0x2540, 0, 0, 0, (void**)((u8*)self + 0x2558));
    BuildCombinedBlendAnimation(self, 12, 2, (u8*)self + 0x255C, 0, 0, 0, (void**)((u8*)self + 0x2574));
    BuildCombinedBlendAnimation(self, 12, 2, (u8*)self + 0x2578, 0, 0, 0, (void**)((u8*)self + 0x2590));
    BuildCombinedBlendAnimation(self, 12, 2, (u8*)self + 0x2594, 0, 0, 0, (void**)((u8*)self + 0x25AC));
    BaseObject* o = PS(BaseObject*, 0x243C);
    if (o != 0) {
        o->desc->m02(o);
        BuildTexturePackets(PS(void*, 0x243C), self->f284);
    }
    self->f2678 = (OnOffObject*)CreateTypedRecord(0x63, self->world, 0, 0x316, -1);
    ResetPlayerOnOffObject(self);
    CreateEightEntryBlend(self, (u8*)self + 0x910, (u8*)self + 0xA10);
    ResolvePlayerTableObjects(self);
    ((void (*)(Player*, void*, s32))((void**)self->desc)[0xE0 / 4])(self, self->f1390[0], 1);
    SetPlayerState(self, 0, -1);
    self->f650 = self->v140.z - 75.0f;
    SetTurningColliderGravityScale(self, D_00263700);
    SetColliderMass(self, D_00263704);
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
        if (((PlacedObject*)self->f25D8[4])->f224 == 0) {
            ((PlacedObject*)self->f25D8[4])->f224 = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);
        }
        *(s32*)((u8*)((PlacedObject*)self->f25D8[4])->f224 + 0xB0) |= 8;
        *(s32*)((u8*)((PlacedObject*)self->f25D8[4])->f224 + 0x60) = 0;
    }
    if (self->f1390[8] == 0) {
        self->f1390[8] = self->f1390[2];
    }
    self->f2514 = CreatePoseSource(self->world, self, D_00219588);
    InsertAttachment(self, self->f2514);
    PS(u8*, 0x251C) = CreatePoseSource(self->world, self->f61C, D_00219588);
    *(s32*)(PS(u8*, 0x251C) + 0x14) = 5;
    InsertAttachment(self->f61C, PS(u8*, 0x251C));
    PS(u8*, 0x2520) = CreatePoseSource(self->world, PS(void*, 0x23D0), D_00219588);
    *(s32*)(PS(u8*, 0x2520) + 0x14) = 5;
    InsertAttachment(PS(void*, 0x23D0), PS(u8*, 0x2520));
    self->flags &= ~(u64)0x0C000000;
    self->flags &= ~(u64)0x30000000;
    BuildCombinedBlendAnimation(self, 12, 3, (u8*)self + 0x106C, 0, 0, 0, (void**)((u8*)self + 0x1090));
    PS(f32, 0x1078) = 1.0f;
    if (PS(void*, 0x1090) != 0) {
        SetBlendItemWeights(PS(void*, 0x1090), 12, 3, (u8*)self + 0x106C);
    }
    void* q = PS(void*, 0x2490);
    if (q != 0) {
        *(s32*)((u8*)q + 0x2F0) = 2;
    }
}

#undef PS

INCLUDE_ASM(func_0016FD70);

INCLUDE_RODATA(jtbl_0024A870);
INCLUDE_ASM(func_001701B0);


void ComputePlayerSlideRates(Player* self, Contact03* out)
{
    f32 a;
    f32 b;
    if (self->f2220 == 0xD) {
        a = D_00262E34;
        b = D_00262E38;
    } else if (self->f2220 == 7) {
        goto zero_both;
    } else if (((VFn_170410*)self->desc)[90](self, out) != 0) {
        if (self->f2220 == 6 && self->f239C == 4 && ((Sub_170410*)self->f23BC)->f40 != 0) {
            goto zero_both;
        }
        a = D_002637B8;
        out->f98 = 0.0f;
        out->f94 = a;
        goto divide;
    } else {
        if (self->f2220 != 4) {
            goto zero_both;
        }
        s32 v = self->f2228;
        if (v == 0x28 || v == 0x31) {
            a = D_002637B0;
            out->f98 = 0.0f;
            out->f94 = a;
            goto divide;
        }
        a = D_002637B0;
        b = D_002637B4;
    }
    out->f94 = a;
    out->f98 = b;
    goto divide;
zero_both:
    out->f94 = 0.0f;
    out->f98 = 0.0f;
divide:
    out->f94 = out->f94 / self->f700;
}
extern f32 D_002637C0[3];

void ClampColliderContactLimit(void* self, s32 flags, void* out);

void ClampPlayerContactLimit(Player* self, s32 flags, ContactLimit03* out)
{
    if (self->f2220 == 4) {
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

void SetPlayerState(void* self, s32 mode, s32 count);
void func_001C61E0(void* self, s32 arg);
void func_00128598(void* self, s32 a, s32 b, f32* heading, s32 c, f32* speed, f32 dt, f32 h);
void RunPlayerCallback(void* self);

void ApplyPendingPlayerStateRequest(Player* self)
{
    s32 flags = self->f2254;
    if (flags == 0) {
        return;
    }
    if (flags & 8) {
        self->f2254 = flags & ~8;
        self->f224C = self->f2264;
    }
    if (self->f2254 & 1) {
        SetPlayerState(self, self->f2258, self->f225C);
    }
    if (self->f2254 & 2) {
        func_001C61E0(self, self->f2260);
    }
    if (self->f2254 & 0x10) {
        RunPlayerCallback(self);
    }
}

void FreePooledContactChain(void* a, Contact03* b);
void PinPlayerToPath(void* self);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void PinPlayerToTarget(void* self);
void BuildPerpendicularPair(Vec02* dir, Vec02* out, const Vec02* a, const Vec02* b);
void AddPlayerObjectContacts(void* self, s32 a, void* b, Vec02* c, s32 d, Vec02* e);
void func_00170660(Player* self)
{
    FreePooledContactChain(self->world, self->contacts4B4);
    self->contacts4B4 = 0;
    switch (self->f2220) {
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
        TransformPointBetweenFrames(self->f24A0, 0, self->f24B0, &pos);
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->v24C0), Vu0::Q(k));
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(self->v24D0));
        BuildPerpendicularPair(&m.r[0], &m.r[1], &g_unitZVector, &g_unitZVector);
        Vu0::Q(pos) = Vu0::Sub(Vu0::Q(pos), Vu0::Rotate(m, Vu0::Q(self->v24E0)));
        AddPlayerObjectContacts(self, 7, self->f24A0, &pos, 0, &self->v140);
        break;
    }
    }
}

extern f32 D_00274AD0[];

s32 IsTurningColliderGroundContact(void* self);

s32 IsPlayerGroundContact(Player* self, Contact03* e, s32 idx)
{
    if (self->f2220 != 0xD) {
        return IsTurningColliderGroundContact(self);
    }
    f32 scale = D_00274AD0[idx];
    if (e->v80.z * scale < 0.7f) {
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

void func_00170820(Player* self, Contact03* c, s32 idx)
{
    ContactEnd03* e = &c->end[idx];
    if (self->f2220 == 4) {
        if (c->kind == 1 && idx == 0 && (Vec02*)c->fA0 == self->f6D8) {
            Vec02 t;
            u128 n = Vu0::Rotate(self->m660, Vu0::Q(self->v640));
            Vu0::Q(t) = Vu0::Sub(n, Vu0::MulX(Vu0::Q(c->v80), Vu0::Dot(n, Vu0::Q(c->v80))));
            Vu0::Q(c->end[0].v30) = Vu0::Add(Vu0::Q(c->end[0].v30), Vu0::Q(t));
        }
    } else if (self->f2220 != 0xD) {
        if (((s32 (*)(Player*, Contact03*, s32))self->desc06()->m56)(self, c, idx)) {
            ResolveTurningColliderGroundContact(self, c, idx);
        } else if (e->part == (Collider*)self) {
            Vu0::Q(e->v30) = Vu0::Sub(Vu0::Q(e->v30), Vu0::Cross(Vu0::Q(self->v160), Vu0::Sub(Vu0::Q(e->v10), Vu0::Q(self->v140))));
        }
    }
}

// An object the player was queued to (+0x2BE0, +0x26D4): its walker at +0x2D4, a walker handle at
// +0x2D8, and the list of the objects at +0x304 (count at +0x300) whose own walkers it sets.
struct WalkerHost { u8 pad00[0x140]; Vec02 v140; u8 pad150[0x2D0 - 0x150]; s32 f2D0; void* f2D4; void* f2D8; u8 pad2DC[0x300 - 0x2DC]; s32 count; WalkerHost* list[1]; };
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
PlayerNoticeEffect* CreateEffect(s32 a, s32 b);
void AddEffectListener(void* obj, void* arg);
f32 GetAnimationMarkerTime(Animation* anim, s32 key);
f32* FindAnimationMarkerEvent(Animation* anim, s32 key);
void SetStateWalkerTarget(void* p, s32 key);
void ReleasePlayerToState2(Player* self);
void HandleSwitchedColliderNotification(void* self, s32 kind, void* rec);
extern f32 D_002637CC;
extern s32 D_002637D0;
extern s32 D_002637D4;
extern f32 g_gameClock[];

static inline s32 MinOfCounts(s32 a, s32 b)
{
    return a < b ? a : b;
}

#define PS(T, o) (*(T*)((u8*)self + (o)))
void HandlePlayerNotification(Player* self, s32 kind, PlayerNotification* msg)
{
    HandleSwitchedColliderNotification(self, kind, msg);
    switch (kind) {
    case 5:
        if ((void*)msg == PS(void*, 0x2244)) {
            self->f2254 |= 2;
            if (self->f223C == 10) {
                self->f2260 = 2;
            } else {
                self->f2260 = -1;
            }
        } else if ((void*)msg == self->watched2230) {
            switch (self->f2220) {
            case 7:
                if (self->f2228 == 0x1B || self->f2228 == 0x17) {
                    self->f2258 = 7;
                    self->f225C = 0x18;
                    self->f2254 |= 1;
                }
                break;
            case 2:
                if (self->f2228 != 7) {
                    if (self->f2228 != 8) {
                        break;
                    }
                }
                self->f2258 = 2;
                self->f225C = 2;
                self->f2254 |= 1;
                break;
            case 0xC:
                if (self->f2228 == 0x21) {
                    self->f2258 = 0xC;
                    self->f225C = 0x22;
                    self->f2254 |= 1;
                    break;
                }
                if (self->f2228 != 0x23) {
                    break;
                }
            case 9:
            case 0xA:
            case 0xE:
            case 0xF:
            case 0x10:
                self->f225C = -1;
                self->f2258 = 0;
                self->f2254 |= 1;
                break;
            case 4:
                self->f2254 |= 0x10;
                break;
            }
        }
        break;
    case 7:
        if ((void*)msg == self->watched2230) {
            switch (self->f2220) {
            case 5:
            case 6:
                self->fA14 = -1;
                break;
            }
        }
        break;
    case 0x13: {
        PlayerNoticePlayer* src = (PlayerNoticePlayer*)msg->source;
        if (src != (void*)self->watched2230 && src != PS(void*, 0x2244)) {
            void* other = self->f2234;
            if (other == 0 || src != *(void**)((u8*)other + 0x24)) {
                break;
            }
        }
        switch (msg->code) {
        case 0x138: {
            Vec02 v;
            Track83* track = src->anim->f9C;
            if (track == 0) {
                break;
            }
            PositionCurve* c = track->pos;
            c->vt->eval(c, self, 0, src->time, src->speed, 0, &v);
            Vu0::Q(v) = Vu0::Rotate(self->m660, Vu0::Q(v));
            self->desc02()->m20(self, &v);
            if (src == (void*)self->watched2230) {
                Vec02 w;
                u128 s = Vu0::FromFloat(-1.0f);
                Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(v), s);
                Vu0::Q(w) = s;
            }
            break;
        }
        case 0x13C:
            if (self->f2228 == 8) {
                self->f242C = (f32)D_002637D4;
            } else {
                self->f242C = (f32)D_002637D0;
            }
            break;
        case 0x13D:
            self->f242C = 0;
            break;
        case 0x13A:
            self->f554 = 1;
            break;
        case 0x13B:
            Vu0::Q(self->v2530) = Vu0::Sub(Vu0::Q(self->v560), Vu0::Q(self->pos));
            self->f554 = 0;
            self->v2530.z = 0.0f;
            break;
        case 0x13E: {
            f32 left = GetAnimationMarkerTime(((PlayerNoticePlayer*)self->watched2230)->anim, 0x140) - msg->time;
            self->f5D0 = 0;
            s32 most = g_currentLevelRecord->f438;
            s32 count = ((WalkerHost*)self->f26D4)->count;
            s32 n = MinOfCounts(count, most);
            for (s32 i = 0; i < n; i++) {
                WalkerHost* h = ((WalkerHost*)self->f26D4)->list[i];
                PlayerNoticeEffect* fx = CreateEffect(0x1A, 0);
                self->f5AC[self->f5D0++] = fx;
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
            for (i = 0; i < ((WalkerHost*)self->f26D4)->count; i++) {
                WalkerHost* h = ((WalkerHost*)self->f26D4)->list[i];
                s32 most = g_currentLevelRecord->f438;
                if (i < most) {
                    if (!(most < ((WalkerHost*)self->f26D4)->count)) {
                        SetStateWalkerTarget(h->f2D4, 0x22F);
                    } else {
                        SetStateWalkerTarget(h->f2D4, 0x230);
                    }
                } else {
                    SetStateWalkerTarget(h->f2D4, 0x231);
                }
            }
            if (!(g_currentLevelRecord->f438 < ((WalkerHost*)self->f26D4)->count)) {
                SetStateWalkerTarget(((WalkerHost*)self->f26D4)->f2D8, 0x22F);
                g_currentLevelRecord->f448 |= ((WalkerHost*)self->f26D4)->f2D0;
            } else {
                SetStateWalkerTarget(((WalkerHost*)self->f26D4)->f2D8, 0x230);
            }
            f32* e = FindAnimationMarkerEvent(((PlayerNoticePlayer*)self->watched2230)->anim, 0x13F);
            if (e == 0) {
                break;
            }
            f32 left = e[0] - ((PlayerNoticePlayer*)self->watched2230)->time;
            self->f5D0 = 0;
            s32 most = g_currentLevelRecord->f438;
            s32 count = ((WalkerHost*)self->f26D4)->count;
            s32 n = MinOfCounts(count, most);
            for (i = 0; i < n; i++) {
                WalkerHost* h = ((WalkerHost*)self->f26D4)->list[i];
                PlayerNoticeEffect* fx = CreateEffect(0x1A, 0);
                self->f5AC[self->f5D0++] = fx;
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
            PS(s32, 0x2738) = 1;
            break;
        case 0x15F:
            PS(s32, 0x2738) = 0;
            break;
        case 0x144:
            self->f2254 |= 0x10;
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
                self->f26D8[k].time = 0;
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
        switch (self->f2220) {
        case 3:
            held = (void*)self->f2204;
            goto check;
        case 7:
            held = (void*)self->f2208;
            goto check;
        case 6:
            if (self->f239C == 4) {
                goto pushed;
            }
            if (self->f239C != 5) {
                break;
            }
            held = PS(void*, 0x23B8);
        check:
            if (held == (void*)msg) {
                ReleasePlayerToState2(self);
            }
            break;
        pushed:
            if (self->f23BC == (void*)msg) {
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
s32 GetObjectWorldPosition(void* p, Vec02* out);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
f32 ArctangentOfRatio(f32 a, f32 b);

s32 func_00171180(Player* self)
{
    Vec02 pos;
    Vec02 d1;
    Vec02 d2;
    f32 y;
    f32 x;
    if (self->f2200 != 0) {
        GetObjectWorldPosition(self->f2200, &pos);
        Vu0::Q(d1) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        y = d1.y;
        x = d1.x;
    } else if (self->f2208 != 0) {
        PoseHolder47* h = ((PoseTarget*)self->f2208)->holder;
        if (h->desc->m2 != 0) {
            h->desc->m2(h, &pos, *(f32*)((u8*)self + 0x220C), 0);
        }
        TransformPointBetweenFrames(((PoseTarget*)self->f2208)->frame, 0, &pos, &d1);
        Vu0::Q(d2) = Vu0::Sub(Vu0::Q(d1), Vu0::Q(self->v140));
        y = d2.y;
        x = d2.x;
    } else {
        return 0;
    }
    self->f638 = ArctangentOfRatio(y, x);
    return 1;
}

INCLUDE_ASM(func_00171238);

INCLUDE_ASM(func_001719E8);

// The record of a probe the player keeps for each of its two parts (+0x1190, +0x1290) and the
// block of the part it fills (func_00171C80).
struct ProbeRecord { u8 pad00[4]; void* f04; u8 pad08[8]; Vec02 v10; u8 pad20[0x10]; Vec02 v30; Vec02 v40; };
struct ProbeResult { u8 pad00[0x20]; Vec02 v20; };
s32 FindNearestSpanObject(void* a, Vec02* from, Vec02* to, s32 count, Collider** list, void* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(void* world, void* self, Vec02* a, Vec02* b, s32 c, s32 d, s32* count, Collider*** list);


s32 func_00171C80(Player* self, void* record, void* part)
{
    ProbeRecord* p = (ProbeRecord*)record;
    ProbeResult* result = (ProbeResult*)part;
    if (p->f04 == 0) {
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
    GatherCollidersInBox(self->world, self->root, &from, &to, 0, 0, &count, &list);
    s32 found = FindNearestSpanObject(0, &from, &to, count, list, &span);
    PopBackMemoryMark();
    if (found != 0) {
        Vu0::Q(span.q[0]) = Vu0::Sub(Vu0::Q(span.q[0]), Vu0::Q(g_unitZVector));
        TransformPointBetweenFrames(0, (s32)self, &span, &world);
        Vu0::Q(result->v20) = Vu0::Sub(Vu0::Q(world), Vu0::Q(p->v10));
        return 1;
    }
    result->v20 = D_00248D30;
    if (self->f690 != 0 && p->v40.z < -85.0f) {
        return 0;
    }
    return 1;
}

s32 AimPlayerAtTarget(void* self);

void func_001719E8(void* self, s32 a, s32 b, void* part, f32 k, void* d);
void ComputeObjectMotionInFrame(s32 a, s32 b, void* c, s32 d, void* e, s32 f, s32 g);
f32 ClampToMagnitude(f32 a, f32 b);
s32 FindStateEntryIndex(void* p, s32 n);
void TeleportStateWalker(void* p, s32 n);


void UpdatePlayerState0(Player* self)
{
    Vec3 loc;
    if (AimPlayerAtTarget(self) == 0) {
        if (self->f690 != 0) {
            ComputeObjectMotionInFrame((s32)self->f6C0, 0, (u8*)self + 0x6A0, 0, &loc, 0, 0);
            loc.z = ClampToMagnitude(loc.z, 10.0f);
            self->f638 = self->f638 + loc.z * g_frameDt[0];
        }
    }
    if (self->f250C == 0) return;
    u8* p1 = (u8*)self + 0x1190;
    f32 k = 5.0f;
    func_001719E8(self, (s32)self->f628, (s32)self->f620, self->f250C, k, p1);
    u8* p2 = (u8*)self + 0x1290;
    func_001719E8(self, (s32)self->f62C, (s32)self->f624, self->f2510, k, p2);
    if (func_00171C80(self, p1, self->f250C) != 0) {
        if (func_00171C80(self, p2, self->f2510) != 0) return;
    }
    if (self->f118C != 0) return;
    if (self->f1188 == 0) return;
    if (FindStateEntryIndex(self->f1188, 0x148) >= 0) TeleportStateWalker(self->f2234, 0x148);
    self->f118C = 1;
}

s32 ComputeBallisticLaunchVelocity(void* a0, void* a1, void* a2, void* a3);

void PlacePlayerOnGround(Player* self, f32 unusedF12, f32 scale)
{
    Vec02 tmp = self->v140;
    tmp.z = tmp.z - 75.0f;
    Vec02 out;
    void* a1;
    ComputeBallisticLaunchVelocity(&tmp, a1, &out, self);
    self->desc02()->m20(self, &out);
    if (self->f2220 != 4) {
        SetPlayerState(self, 2, 6);
        self->f226C = self->f226C * scale;
        if (scale == 0.0f) {
            self->f2498 = 0;
        }
    }
}

void ReleasePlayerToState2(Player* self)
{
    s32 st = self->f2220;
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
        self->f224C = 1;
        SetPlayerState(self, 2, 2);
    } else {
        s32 w = self->f239C;
        if (w >= 6) {
            return;
        }
        if (w < 4) {
            return;
        }
        SetPlayerState(self, 2, 2);
    }
}

INCLUDE_ASM(func_00172078);

INCLUDE_ASM(func_001721B0);

void RecomputeTurningColliderFrame(Player* self);
void func_001C4618(Player* self, void* a1, void* a2, s32 a3, f32 f12, void* a4);

void RecomputePlayerFrame(Player* self)
{
    RecomputeTurningColliderFrame(self);
    if (self->f2220 == 6 && self->f239C == 7) {
        self->f1290.f50 = 0;
        goto clear;
    }
    {
        void* a1 = self->f610;
        if (a1 == 0) {
            self->f1290.f50 = 0;
            goto clear;
        }
        if (self->f614 == 0) {
            self->f1290.f50 = 0;
            goto clear;
        }
        f32 k = 6.0f;
        func_001C4618(self, a1, a1, (s32)self->f620, k, (u8*)self + 0x1190);
        func_001C4618(self, self->f614, self->f614, (s32)self->f624, k, (u8*)self + 0x1290);
    }
    return;
clear:
    self->f1190.f50 = 0;
}

void func_001C4848(Player* s, void* a, void* b, void* c);
void BuildPlacedObjectTransform(Player* s, void* c, f32* out);
void OrientPlayerSpinPart(Player* s, f32* buf, f32 t);
void BuildMatrixFromRotationAndTranslation(void* a, f32* b, f32* out);
void UpdatePlayerLinkPose(Player* s);
void DrawTurningCollider(Player* s, void* a, void* b);
void QueueTrailRibbonDraw(void* a, void* b);
void QueuePlayerMarkerRingDraw(Player* s, void* a, void* b);

void DrawPlayer(Player* self, void* a, void* b)
{
    f32 buf[12];
    f32 out[20];
    s32 i;

    if (!(self->f2220 == 6 && self->f239C == 7))
    {
        func_001C4848(self, self->f610, self->f610, &self->f1190);
        func_001C4848(self, self->f614, self->f614, &self->f1290);
    }
    if (self->f2434 != 0.0f || self->f2430 != 0.0f)
    {
        ((PlacedObject*)self->f61C)->flags &= ~(1ULL << 32);
        BuildPlacedObjectTransform(self, b, out);
        out[16] *= 0.25f;
        for (i = 0; i < 4; i++)
        {
            OrientPlayerSpinPart(self, buf, (f32)i * 0.25f);
            BuildMatrixFromRotationAndTranslation(&((PlacedObject*)self->f61C)->v140, buf, out);
            ((PlacedObject*)self->f61C)->desc02()->m24((PlacedObject*)self->f61C, a, out);
        }
        ((PlacedObject*)self->f61C)->flags |= 0x100000000UL;
    }
    if (self->f2220 == 3)
    {
        UpdatePlayerLinkPose(self);
    }
    DrawTurningCollider(self, a, b);
    if (self->f21C0)
    {
        QueueTrailRibbonDraw(self->f1520, a);
    }
    QueuePlayerMarkerRingDraw(self, a, b);
}


f32 FloatRemainder(f32 v, f32 m);
f32 ApproachValueWithRamp(void* p, f32 a, f32 b, void* o, f32 c);

void UpdatePlayerSpin(Player* self)
{
    if (self->f242C == 0.0f) {
        if (self->f2434 == 0.0f) {
            return;
        }
    }
    if (self->f242C != 0.0f) {
        *(f32*)((u8*)self + 0x2430) = self->f242C;
        self->f2434 = FloatRemainder(self->f2434 + self->f242C * g_frameDt[0], 6.2831855f);
    } else {
        if (self->f2434 == 0.0f) {
            return;
        }
        f32 r = ApproachValueWithRamp(&D_002638A0, self->f2434, 6.2831855f, &self->f2430, g_frameDt[0]);
        self->f2434 = r;
        if (r == 6.2831855f) {
            self->f2434 = 0.0f;
        }
    }
}

// EXACT: callee func_001300E8 declared with a third parameter and called with k, which puts k in a2

// The object the player hands contacts to (Player::f2750): it keeps them in a chain at 0x554.
struct ContactChainOwner {
    u8 pad0[0x554];
    Contact03* chain;       // 0x554
};

void ExtractContactsByPartMode(Player* a, void* b);
s32 IsObjectOfKind(void* key, s32 kind, s32 extra);
void CollectTurningColliderContacts(Player* a);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void FreePooledContactChain(void* a, Contact03* b);

void PrunePlayerContacts(Player* self)
{
    ContactRow03* row;
    Contact03** slot;
    Contact03* n;
    Contact03* head = 0;
    ExtractContactsByPartMode(self, self->f151C);
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
                    } else if ((void*)n->end[1 - k].body == ((ContactChainOwner*)self->f2750) && ((s32 (*)(Player*, Contact03*))self->desc06()->m56)(self, n)) {
                        *slot = n->next;
                        n->next = ((ContactChainOwner*)self->f2750)->chain;
                        ((ContactChainOwner*)self->f2750)->chain = n;
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
    if (self->f2220 == 8) {
        self->f690 = 1;
        self->f694 = g_gameTime[0];
        TransformPointBetweenFrames(self->f24A0, 0, self->f24B0, &self->v6A0);
        self->v6B0 = g_unitZVector;
        self->f6C0 = self->f24A0;
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
                            if ((void*)n->end[1 - k].body == ((PlacedObject*)self->f24A0)->root) {
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
    FreePooledContactChain(self->world, head);
}

void SaveColliderPreviousPosition(void* self);

void SavePlayerPreviousPosition(Player* self)
{
    SaveColliderPreviousPosition(self);
    self->f21CC = 0;
}

// EXACT: declaring D_00261860 as an array (extern f32 D_00261860[], passed as D_00261860[0]) moved the float load into the jal delay slot.


void MoveCollider(void* self, void* b, f32 x);

void SetPlayerBoundsPoints(Player* self)
{
    self->v21D0[1] = ((PlacedObject*)self->f23D4)->v140;
    self->f21CC = 0;
    MoveCollider(self, 0, g_frameDt[0]);
    if (self->f223C == 0) {
        self->v21D0[0] = self->v140;
        self->v21D0[2] = ((PlacedObject*)self->f23D4)->v140;
        self->f21CC = 3;
        self->desc03()->m32(self);
    } else {
        self->f21CC = 0;
    }
}

void UpdateColliderBounds(void* self);
void ExpandColliderBoundsBySphere(void* self, void* p, f32 f);

void UpdatePlayerBounds(Player* self)
{
    s32 i = 0;
    UpdateColliderBounds(self);
    if (self->f21CC > 0) {
        Vec02* p = self->v21D0;
        do {
            ExpandColliderBoundsBySphere(self, p, self->f2420);
            i++;
            p++;
        } while (i < self->f21CC);
    }
}

s32 IsObjectAttached(void* p);

void* FindFirstAttachedSlotObject(Player* self, s32* out)
{
    void* p = self->f25D8[0];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 0;
        return self->f25D8[0];
    }
    p = self->f25D8[2];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 1;
        return self->f25D8[2];
    }
    p = self->f25D8[1];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 2;
        return self->f25D8[1];
    }
    p = self->f25D8[3];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 2;
        return self->f25D8[3];
    }
    p = self->f25D8[4];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 1;
        return self->f25D8[4];
    }
    return 0;
}

void AddTurningColliderProbeContact(Player* a, Collider* b, void* c, void* d);
void KeepNearestPartSpan(Player* a, Collider* b, void* c, void* d);
void AddMeshContacts(Collider* a, f32 f, void* b, void* c, s32 d, s32 e, s32 g, void* h);
void func_00186BA8(void* a, Collider* b, void* c, void* d, void* e, void* f);

void CollidePlayerWithObject(Player* self, Collider* a1, void* a2, void* a3, void* a4, void* a5)
{
    s32 idx;
    Collider* v;
    Collider* cur;

    switch (self->f2220)
    {
    case 4:
        if (self->f2BD8 == 0)
        {
            switch (self->f2228)
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
        if (self->f2BD8 == 0)
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
                    AddMeshContacts(a1, a1->radius3CC, (u8*)a1 + 0x140, v, v->tree.count, (s32)v->tree.nodes, 0, (u8*)self + 0x2670);
                }
                else if (a3)
                {
                    func_00186BA8(v, a1, a2, a3, a4, (u8*)self + 0x2670);
                }
                return;
            }
        }
    }
}

s32 GetPlayerContactMode(Player* self)
{
    if (self->f2220 == 3 || self->f2220 == 0xD) {
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
extern f32 D_002638E0[4];
extern f32 D_002638F0[4];

void CaptureSwitchedColliderPose(Player* self, u8* out, f32 dt);
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, void* d);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, f32* p, s32 zero);
u128 ApproachPointWithRamp(u128 a, u128 b, f32 dt, f32* ramp, s32 zero);
void func_001733B8(Player* self, u8* out);
void GetObjectWorldPosition(s32 obj, Vec02* out);
#include "value_range.h"
typedef void (*PoseAtFn)(PoseHolder47* self, Vec02* pos, Vec02* dir, f32 t);

// The pose a collider's slot captures each frame (CaptureSwitchedColliderPose fills pos).
struct ColliderPose {
    s32 flags;              // 0x00: bit 0 set in the player's grounded states
    u8 pad04[0x10 - 0x04];
    Vec02 pos;              // 0x10: where the camera looks
    Vec02 dir;              // 0x20: the path's direction times the speed along it
    u8 pad30[0x34 - 0x30];
    f32 f34;                // 0x34: a weight, scaled down by the spin or cleared
    f32 f38;                // 0x38: the time it was last stamped
    s32 f3C;                // 0x3C
};
#define PL(T, o) (*(T*)((u8*)self + (o)))

void func_00172EE0(Player* self, ColliderPose* pose, f32 dt)
{
    u8* out = (u8*)pose;
    Vec02 last = self->v560;
    CaptureSwitchedColliderPose(self, out, dt);
    if (self->f554 == 0) {
        if (self->f2220 == 7) {
            Vec02 pos;
            Vec02 dir;
            PoseHolder47* h = ((PoseTarget*)self->f2208)->holder;
            PoseAtFn fn = (PoseAtFn)h->desc->m2;
            if (fn != 0) {
                fn(h, &pos, &dir, self->f2410);
            }
            TransformPointBetweenFrames(((PoseTarget*)self->f2208)->frame, 0, &pos, &pos);
            Vu0::Q(pose->pos) = Vu0::Q(pos);
            TransformDirectionBetweenFrames(((PoseTarget*)self->f2208)->frame, 0, &dir, &dir);
            u128 d = Vu0::Q(dir);
            d = Vu0::NormalizeOr(d, Vu0::Q(D_00248D30));
            Vu0::Q(pose->dir) = Vu0::MulX(d, Vu0::ScalarAt(self->f2414));
            Vu0::Q(dir) = d;
            self->f650 = pose->pos.z - 125.0f;
        } else {
            if (self->f2220 == 3) {
                Vec02 pos;
                GetObjectWorldPosition(self->f2204, &pos);
                self->f650 = pos.z + D_002638C8[0];
            } else if (self->f690 != 0) {
                self->f650 = self->v6A0.z;
            } else if (g_camera->f224 != 0) {
                self->f650 = self->v140.z - 75.0f;
            }
            f32 h = self->f650;
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
            self->f650 = r;
            f32 z = r + 125.0f;
            if (g_camera->f224 != 0) {
                pose->pos.z = z;
            } else {
                f32 v = ApproachValueWithRamp(last.z, z, g_gameClock[2], D_002638F0, 0);
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
        if (self->f2220 == 6 && self->f239C == 0) {
            func_001733B8(self, out);
        }
        u128 d = ApproachPointWithRamp(Vu0::Q(self->v2530), Vu0::Q(D_00248D30), dt, D_002638E0, 0);
        Vu0::Q(self->v2530) = d;
        Vu0::Q(pose->pos) = Vu0::Add(Vu0::Q(pose->pos), d);
    }
    switch (self->f2220) {
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
        switch (self->f239C) {
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
    switch (self->f2220) {
    case 0:
        stamp = 0;
        break;
    case 6:
        if (self->f2228 == 16) {
            stamp = 0;
        }
        break;
    case 7:
        if (self->f2228 == 24) {
            stamp = 0;
        }
        break;
    }
    if (stamp != 0) {
        self->f2680 = g_gameTime[0];
    }
    pose->f38 = self->f2680;
    switch (self->f2220) {
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
        pose->f34 = pose->f34 * k;
        break;
    }
    case 4:
        switch (self->f2228) {
        case 41:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            pose->f34 = 0.0f;
        }
        break;
    case 7:
    case 13:
        pose->f34 = 0.0f;
        break;
    }
    self->v560 = pose->pos;
}

#undef POSE
#undef PL

INCLUDE_ASM(func_001733B8);


void HandleSwitchedColliderActivation(void* a, void* b);
void ShowModeLabel(s32 id);

void SetPlayerTracked(Player* a, void* b)
{
    HandleSwitchedColliderActivation(a, b);
    s32 id;
    if (b != 0) id = g_saveData->f19FC;
    else id = -1;
    ShowModeLabel(id);
}

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(void* world, void* self, Vec02* a, Vec02* b, s32 c, s32 d, s32* count, Collider*** list);
s32 CollectColliderSpans(Collider* self, void* a1, void* a2, s32 a3, void* a4);

s32 func_00173750(Player* self, Vec02* offset)
{
    s32 count;
    Collider** list;
    Vec02 from;
    Vec02 to;
    ColliderSpan spans[8];
    s32 i = 0;
    PushBackMemoryMark();
    from = *self->f6D8;
    Vu0::Q(to) = Vu0::Add(Vu0::Q(*self->f6D8), Vu0::Q(*offset));
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

s32 HasAnimationDrivenAttachment(void* ctx);
void ReleaseAnimationDrivenAttachments(void* ctx);
void* FillMemory(void* dst, s32 value, s32 size);
s32 IsObjectOfKind(BaseObject* n, s32 kind);
s32 IsTopCameraController(u8* p);
s32 HasSpareCount(void);
s32 MaskWorldBitsBySave(void);
void SetPlayerBlendWeights(f32 angle, f32 t, Player* self, void* records, s32 n);
extern s32 g_currentMode;
extern s32 g_padRouting;
extern s32 g_padSelectFlags;
s32 IsEntryQueueRunning(EntryQueue* q);
void DrivePlayerFromEntryQueue(EntryQueue* q, PadRecord* pad);
void UnbindEntryQueue(EntryQueue* q);
void StartObjectFade(void* key, s32 id, s32 on);
void ClearPadPressedBits(PadRecord* pad, s32 mask);
BaseObject* FindFirstObjectById(World* world, s32 kind, s32 id, s32 ctx);
void func_001C49E8(Player* self, PadRecord* pad);
f32 WrapAngle(f32 a);
void UpdateModeSelection(Player* self, PadRecord* pad);
void SkipRemainingSteps(StepSequence* self);
void SetStepSequenceState(StepSequence* self, s32 state);
s32 ChooseNearbyPlayerTarget(Player* self, s32 a, s32* out);
void StartSoundEffect(s32 sound, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 ChoosePlayerTargetByCost(Player* self, void* target);
s32 ChoosePlayerNextState(Player* self);
void PopStackElement(void* q);
void HandlePlayerAimButton(Player* self, PadRecord* pad);
// player_request.cpp defines it with four parameters; retail's call here also loads the word at
// 0xA10 into $a2 (first, as the argument order below gives).
void SetPlayerVelocityFromHeading(Player* self, void* basis, s32 n, f32 heading, f32 speed);
void ControlPlayerOnLinkedObject(Player* self, PadRecord* pad);
void ControlPlayerOnPath(Player* self, PadRecord* pad);
void func_0017D5D8(Player* self, PadRecord* pad);
void ControlPlayerOnTarget(Player* self, PadRecord* pad);
void func_00177990(Player* self);
extern s32 D_00261D38;
extern s32 D_00275F84;
extern StepSequence* D_0026F800;
extern u8 g_elementStack[];

// Slot 73 of class 0x07: the player's control for a frame. Without control (an activation queued, the
// entry queue running) the pad is a cleared record. It works out a jump (the pad's 0x40 bit near a
// floor), a fall and a step skip, then changes state until the state it chooses is the one it is in,
// and runs the state's own control. A 0x40 press without a jump stamps 0x2284, except in state 4
// (the goto, past the stamp). In the
// default case the offset is stored through a cast, so its address is not a register CSE hands on to
// the call, which retail computes after the time test.
void ControlPlayer(Player* self, PadRecord* pad)
{
    if (HasAnimationDrivenAttachment(self)) {
        if (!(0.0f < pad->f48) && (pad->flags & 0xF0) == 0) {
            return;
        }
        ReleaseAnimationDrivenAttachments(self);
    }
    PadRecord blank;
    if (D_00261D38 > 0 || self->walkerActivation != 0 || self->firstActivation != 0 || self->secondActivation != 0) {
        switch (self->f2220) {
        case 12:
            if (self->f2BD0 == 0) {
                SetPlayerState(g_player, 12, 0x23);
            }
            break;
        case 8:
            if (g_gameTime[0] - self->f2224 > 0.2f) {
                self->f224C = 4;
                SetPlayerState(g_player, 2, 0);
            }
            break;
        case 2:
            switch (self->f2228) {
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
    if (self->f2220 != 4) {
    if (self->entryQueue != 0 && IsEntryQueueRunning(self->entryQueue)) {
        EntryQueue* q = self->entryQueue;
        if ((g_padRecord.flags & 0x800) && D_00275F84 == 0) {
            s32 start = q->f40;
            if (start >= 0) {
                for (s32 i = start; i < q->f34; i++) {
                    QueueEntry* e = &((QueueEntry*)q->buffer)[i];
                    if (e->kind == 1) {
                        BaseObject* o = FindFirstObjectById(q->world, 0x104, e->id, q->f4C);
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
        func_001C49E8(self, pad);
    }
    } else {
        func_001C49E8(self, pad);
    }
    s32 skipStep = 0;
    s32 noFloor = 0;
    s32 moving;
    s32 falling = 0;
    s32 jump = 0;
    WrapAngle(self->f630 - ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x));
    if (pad->flags & 0x40) {
        switch (self->f2220) {
        case 6:
            if (self->f239C == 2 || self->f239C == 5 || self->f239C == 4) {
                jump = 1;
            }
            break;
        case 2:
            switch (self->f2228) {
            case 7:
            case 8:
                break;
            default:
                if (self->f2498 != 0) {
                    Vec02 off;
                    Vu0::Q(off) = Vu0::MulXSum3(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->f6CC),
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
            *(u128*)&off = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->f6CC - 60.0f));
            if (g_gameTime[0] - self->f694 < 0.1f || HasFloorAtPlayerOffset(self, &off)) {
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
    } else if (g_gameTime[0] - self->f2284 < 0.1f && g_gameTime[0] - self->f694 < 0.1f) {
        jump = 1;
    }
held:
    switch (self->f2220) {
    case 0:
    case 1:
    case 5:
    case 6:
    case 14:
    case 15:
    case 16:
        if (g_gameTime[0] - self->f694 > 0.1f) {
            Vec02 off;
            if (self->f2220 == 6 && self->f239C == 3) {
                Vu0::Q(off) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->f6CC - 200.0f));
            } else {
                Vu0::Q(off) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->f6CC - 60.0f));
            }
            noFloor = !HasFloorAtPlayerOffset(self, &off);
        }
        break;
    default:
        noFloor = 0;
        break;
    }
    moving = 0.0f < self->f634;
    s32 aim = pad->keyA8 & 0x20;
    s32 modeKey = 0;
    if (pad->flags & 0x10) {
        modeKey = g_currentMode == 0;
    }
    UpdateModeSelection(self, pad);
    if (!IsTopCameraController((u8*)&g_camera->ctl454)) {
        PadRecord* rec = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
        StepSequence* seq = (StepSequence*)g_typedTextCaptionBox.child;
        if (seq != 0 && seq->state2D4 == 3 && seq->f32C == 0 && (rec->flags & 0xC) && *(s32*)seq->target304 != 0) {
            if (self->f2220 == 12) {
                self->f2BD0 = 0;
                skipStep = 1;
            }
            SkipRemainingSteps((StepSequence*)g_typedTextCaptionBox.child);
            ClearPadPressedBits(rec, 0xC);
        } else if (self->f2BD4 != 0 || (pad->flags & 0xC)) {
            if (self->f2220 == 12) {
                if (g_typedTextCaptionBox.child == 0) {
                    self->f2BD0 = 0;
                    skipStep = 1;
                }
            } else if (g_typedTextCaptionBox.child == 0) {
                if ((pad->flags & 4) && D_0026F800 != 0 && (self->f2BD4 == 0 || D_0026F800->mode2D0 == 1)) {
                    SetStepSequenceState(D_0026F800, 1);
                } else if (self->f2BD4 == 0) {
                    self->f2BD0 = 0;
                    skipStep = 1;
                }
            }
        }
    }
    for (;;) {
        s32 state = self->f2220;
        s32 sub = self->f2228;
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
                state = self->f2220;
                sub = self->f2228;
            }
            break;
        case 0:
            if ((self->f223C == 8 || self->f223C == 9) && self->f2248 == 0) {
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
                target = ChooseNearbyPlayerTarget(self, 0, &self->f239C);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E24, 0.0f, 0.0f, 0, 0);
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
                self->f224C = state;
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
                target = ChooseNearbyPlayerTarget(self, 0, &self->f239C);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E24, 0.0f, 0.0f, 0, 0);
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
                target = ChooseNearbyPlayerTarget(self, 0, &self->f239C);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E24, 0.0f, 0.0f, 0, 0);
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
                && (sub != 5 || g_gameTime[0] - self->f222C > 0.05f);
            if (ready) {
                if (pad->flags & 0x20) {
                    ClearPadPressedBits(pad, 0x20);
                    func_001C61E0(self, -1);
                    sub = ChoosePlayerTargetByCost(self, 0);
                    break;
                }
                if ((sub != 6 || self->f226C != 0.0f) && (pad->flags & 0x80)) {
                    func_001C61E0(self, -1);
                    sub = 7;
                    ClearPadPressedBits(pad, 0x80);
                    break;
                }
            }
            if (ready && modeKey && (MaskWorldBitsBySave() & 0x10)) {
                func_001C61E0(self, -1);
                sub = 8;
                break;
            }
            if (jump) {
                sub = 0;
                if (MaskWorldBitsBySave() & 0x1000) {
                    break;
                }
                if (!(pad->keyA8 & 0x10)) {
                    self->f2744 = 0;
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
                self->f224C = 1;
            }
            break;
        case 6:
            if (self->f239C == 2) {
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
            if (self->f239C == 4 || self->f239C == 5) {
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
            if (pad->keyA8 & 0x20) {
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
                self->f224C = 4;
            }
            break;
        case 12:
            if (skipStep) {
                if (self->f2228 == 0x22) {
                    sub = 0x23;
                    PopStackElement(g_elementStack);
                    break;
                }
            } else if (self->f2228 == 0x22) {
                T217D_440* box = &g_typedTextCaptionBox;
                if (box->state == 0 || (box->state == 2 && box->child != 0 && ((StepSequence*)box->child)->state2D4 == 4)) {
                    sub = 0x23;
                    break;
                }
            }
            if (self->f2228 == 0x21 && self->f25CC == 0 && g_gameTime[0] - self->f222C >= 0.5f) {
                sub = 0x22;
                break;
            }
            if (self->f2228 == 0x23 && self->f25D0 == 0 && g_gameTime[0] - self->f222C >= 0.25f) {
                state = 0;
                sub = -1;
            }
            break;
        case 13:
            if (!(pad->keyA8 & 0x10) && g_gameTime[0] - self->f2224 > D_00262E3C) {
                sub = 0x38;
                break;
            }
            self->f638 = self->f630;
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
        if (state == self->f2220 && sub == self->f2228) {
            break;
        }
        SetPlayerState(self, state, sub);
        skipStep = 0;
        jump = 0;
        falling = 0;
    }
    HandlePlayerAimButton(self, pad);
    switch (self->f2220) {
    case 5:
        SetPlayerVelocityFromHeading(self, (u8*)self + 0x910, self->fA10, self->f630, self->f634);
        break;
    case 1:
        SetPlayerBlendWeights(self->f630, self->f634, self, (u8*)self + 0x720, self->f900);
        break;
    case 4:
    case 10: {
        self->v640 = D_00248D30;
        PlayerNoticePlayer* src = (PlayerNoticePlayer*)self->watched2230;
        if (src != 0) {
            Track83* track = src->anim->f9C;
            if (track != 0) {
                PositionCurve* c = track->pos;
                if (c != 0) {
                    Vec02 v;
                    c->vt->eval(c, self, 0, src->time, src->speed, 0, &v);
                    Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(v), Vu0::Scalar(-1.0f));
                }
            }
        }
        break;
    }
    case 3:
        ControlPlayerOnLinkedObject(self, pad);
        break;
    case 7:
        ControlPlayerOnPath(self, pad);
        break;
    case 2:
        func_0017D5D8(self, pad);
        break;
    case 6:
        ControlPlayerOnTarget(self, pad);
        break;
    case 0:
    case 16:
        break;
    }
    func_00177990(self);
}

void UpdateTurningCollider(Player* self, f32 dt);
s32 HasAnimationDrivenAttachment(void* ctx);
void func_00174E20(Player* self);
void UpdateSixEntryBlendWeights(Player* self, void* blend, s32 n, void* msg);
f32 WrapModulo(f32 x, f32 y);
void PlayPhaseCrossingSound(Player* self, void* p, f32 f);
void UpdateEightEntryBlendWeights(Player* self, void* blend, s32 n);
void func_0017F018(Player* self);
void UpdatePlayerTargetPhase(Player* self);
u128 ApproachPointWithRamp(u128 cur, u128 target, f32 dt, const f32* params, s32 flag);
s32 func_0017E088(Player* self, void* frame, Vec02* pos, s32 a, s32 b, Vec02* out);
void UpdatePlayerRequestSubState(Player* self);
void UpdatePlayerAimTarget(Player* self);
void ReleaseFarPlayerLinks(Player* self);
void func_001D66A8(Player* self);
void ClearRootTries(void* self);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* o1, f32* o2);
void FindClosestPointsOnSegments(Vec02* a0, Vec02* a1, Vec02* b0, Vec02* b1, Vec02* out, f32* d, Vec02* out2);
void InitOwnerMessage(void* out, s32 mode, void* owner);
void func_00171238(Player* self);
void func_001790B8(Player* self);
void RunPlayerQueuedActivations(Player* self);
extern f32 D_00274B64;

struct PhaseObject_174808 { u8 pad00[0x34]; f32 f34; };
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
        func_00174E20(self);
    }
    if (self->f26C4 != 0 && self->f2220 != 4 && self->f26D0 < g_gameTime[0] - self->f26CC) {
        self->f26C4 = 0;
    }
    switch (self->f2220) {
    case 1:
        UpdateSixEntryBlendWeights(self, (u8*)self + 0x720, self->f900, self->watched2230);
        {
            f32 phase = WrapModulo((((PhaseMessage_174808*)self->watched2230)->f14 + D_00274B64 * ((PhaseMessage_174808*)self->watched2230)->f18) / ((PhaseMessage_174808*)self->watched2230)->f8->f34, 1.0f);
            PlayPhaseCrossingSound(self, &self->f2440[0], phase);
        }
        break;
    case 5:
        UpdateEightEntryBlendWeights(self, (u8*)self + 0x910, self->fA10);
        {
            f32 phase = WrapModulo((((PhaseMessage_174808*)self->watched2230)->f14 + D_00274B64 * ((PhaseMessage_174808*)self->watched2230)->f18) / ((PhaseMessage_174808*)self->watched2230)->f8->f34, 1.0f);
            PlayPhaseCrossingSound(self, &self->f2440[1], phase);
        }
        break;
    case 2:
        func_0017F018(self);
        break;
    case 0:
        UpdatePlayerState0(self);
        break;
    case 6:
        UpdatePlayerTargetPhase(self);
        break;
    case 8: {
        Vec02 local;
        Vu0::Q(self->v24D0) = ApproachPointWithRamp(Vu0::Q(self->v24D0), Vu0::Q(D_00248D30), dt, D_00263918, 0);
        TransformPointBetweenFrames(self->f24A0, 0, self->f24B0, &local);
        if (func_0017E088(self, self->f24A0, &local, self->f24F0, self->f24F4, &self->v24C0) == 0) {
            SetPlayerState(self, 2, 2);
            break;
        }
        self->f638 = ArctangentOfRatio(-self->v24C0.y, -self->v24C0.x);
        break;
    }
    case 9: {
        Vec02 local;
        if (self->f26D4 != 0) {
            Vu0::Q(local) = Vu0::Sub(Vu0::Q(((Player*)self->f26D4)->v140), Vu0::Q(g_player->v140));
        } else {
            Vu0::Q(local) = Vu0::Sub(Vu0::Q(g_camera->f40), Vu0::Q(g_player->v140));
        }
        self->f638 = ArctangentOfRatio(local.y, local.x);
        break;
    }
    case 4:
        UpdatePlayerRequestSubState(self);
        break;
    case 12:
        self->f638 = *(f32*)&g_camera->ctl460.value;
        break;
    case 13:
        if (self->f2228 == 0x38) {
            if (D_00263924 < self->rot.r[2].z) {
                s32 slow = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v160), Vu0::Q(self->v160)))) < D_00263928[0];
                if (slow) {
                    SetPlayerState(self, 2, 2);
                }
            }
        } else if (self->f2228 == 0x36) {
            if (self->f690 != 0) {
                SetPlayerState(self, 0xD, 0x37);
            }
        }
        break;
    }
    UpdatePlayerAimTarget(self);
    ((ContactBody_174808*)self)->desc->m160((ContactBody_174808*)self);
    ReleaseFarPlayerLinks(self);
    func_001D66A8(self);
    ClearRootTries(self);
    if (self->f223C == 0) {
        Vec02 local;
        Vec02 pts[3];
        Vec02 dirs[3];
        Vec02 closest;
        f32 t;
        f32 dist;
        f32 gap;
        if (self->f2204 != 0) {
            GetObjectWorldPosition((void*)self->f2204, &local);
            for (s32 i = 1; i < self->f21CC; i++) {
                MeasurePointToSegment(&local, &self->v21D0[i - 1], &self->v21D0[i], &t, &dist);
                if (dist < ((LinkTarget_174808*)self->f2200)->radius + self->f2420) {
                    SetPlayerState(self, 3, 0x33);
                    break;
                }
            }
        } else if (self->f2208 != 0) {
            s32 i;
            for (i = 0; i < self->f21CC; i++) {
                TransformPointBetweenFrames(0, (s32)((PathTarget_174808*)self->f2208)->frame, &self->v21D0[i], &pts[i]);
                PathShape_174808* s = ((PathTarget_174808*)self->f2208)->shape;
                if (s->desc->m30 != 0) {
                    s->desc->m30(s, &pts[i], *(f32*)((u8*)self + 0x220C), 0, &dirs[i], 0, 0, 0);
                }
            }
            for (i = 1; i < self->f21CC; i++) {
                FindClosestPointsOnSegments(&pts[i - 1], &pts[i], &dirs[i - 1], &dirs[i], &local, &gap, &closest);
                if (gap < self->f2420) {
                    SetPlayerState(self, 7, 0x17);
                    break;
                }
            }
        }
    }
    if (*(Contact03**)self->f151C != 0) {
        for (Contact03* c = *(Contact03**)self->f151C; c != 0; c = c->next) {
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
        FreePooledContactChain(self->world, *(Contact03**)self->f151C);
        *(Contact03**)self->f151C = 0;
    }
    UpdatePlayerSpin(self);
    func_00171238(self);
    func_001790B8(self);
    RunPlayerQueuedActivations(self);
}

void func_00174E20(Player* self)
{
    switch (self->f2220) {
    case 3:
        SetPlayerState(self, 2, 2);
        break;
    case 0xD:
        SetPlayerState(self, 0xD, 0x38);
        break;
    }
    s32 state = self->f2220;
    func_001C61E0(self, -1);
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
        Vu0::Q(self->v640) = Vu0::Zero();
        break;
    default: {
        f32 heading;
        f32 speed;
        state = 0;
        func_00128598(self, 0, 0, &heading, 0, &speed, g_frameDt[0], self->f638);
        if (speed > 0.0f) {
            state = 1;
        }
        self->f638 = heading;
        Vu0::Q(self->v640) = Vu0::FromFloats(-speed, 0.0f, 0.0f);
        SetPlayerState(self, state, -1);
    }
    }
}


void func_001C4D60(Player* self, void* a1, s32 zero);

void SelectPlayerStateAnimation(Player* self)
{
    void* node;
    switch (self->f2220) {
    case 6: {
        s32 m = self->f239C;
        if ((m == 0 && self->f2228 == 0x15) || m == 7) {
            node = self->f146C;
        } else {
            node = self->f13D4[m];
        }
        break;
    }
    case 4: {
        s32 i = self->f2228;
        if (i != -1) {
            node = self->f1418[i];
            if (node == 0) {
                do {
                    s32 k = D_00263930[i - 0x24];
                    if (k == -1) {
                        break;
                    }
                    node = self->f1418[k];
                    i = k;
                } while (node == 0);
            }
        }
        break;
    }
    case 2: {
        s32 i = self->f2228;
        if (i < 0xE) {
            if (i >= 0xC) {
                node = self->f146C;
                break;
            }
        }
    }
    default:
        node = self->f1390[self->f2220];
        break;
    case 0xD:
        return;
    }
    if (node == 0) {
        node = self->f1390[0];
    }
    func_001C4D60(self, node, 0);
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
        ((Dev_175078*)self->f250C)->f10 = b ? 9 : -1;
        ((Dev_175078*)self->f2510)->f10 = b ? 9 : -1;
        PlacedObject* o = self->f24F8;
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





void CreateAnimationPlayer(void* anim, void* owner, s32 count, void* args, s32 flag, void* out, f32 start, f32 speed);
void InitContactPairFlags(void* world, void* obj);
void PushCameraController(void* camera, s32 kind, void* sounds, void* owner, s32 a4);
void RemoveCameraControllers(void* camera, s32 mask, s32 kind, void* sounds, void* owner, s32 a5);
void RequestCameraSnap(Camera* camera, s32 mode);
void StartCameraSounds(void* sounds);
void SendEmptyMessage(void* x);
void SetPooledObjectPlayerHold(void* obj, s32 hold);
void ComputePlayerJumpVelocity(Player* self, Vec02* out);
void func_0017FC48(Player* self, Vec02* out);
void func_0017FCC8(Player* self, Vec02* out);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void ActivateSwitchedCollider(void* obj);
void DestroyStateWalker(void* h);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void AddColliderAttachment(Collider* o, Attach03* node);
void RemoveColliderAttachment(Collider* o, Attach03* node);
void SetColliderTreeContactsDropped(void* self, s32 dropped);
void* PushSoundLevel(s32 level);
void ReleaseSoundLevel(void* p);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
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
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);

extern s32 D_00270454;
extern f32 D_00274F00;
extern f32 D_00274F04;
extern f32 D_00274F08;
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
void func_001C61E0(void* self, s32 arg);
void func_001C4D60(Player* self, void* a1, s32 zero);
s32 FindStateEntryIndex(void* p, s32 n);
f32 ArctangentOfRatio(f32 a, f32 b);
s32 IsObjectAttached(void* p);
void ResetPlayerOnOffObject(Player* self);
void ReleaseFarPlayerLinks(Player* self);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, void* d);
f32 GetAnimationMarkerTime(Animation* anim, s32 key);
void BuildPerpendicularPair(Vec02* dir, Vec02* out, const Vec02* a, const Vec02* b);
void StopAnimationPlayer(void* p);
s32 MaskWorldBitsBySave(void);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void ResetTrailRing(void* sub);
void PushStackElement(void* a, void* b);
f32 WrapAngle(f32 a);
void* FillMemory(void* dst, s32 value, s32 size);

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

#define PS(T, o) (*(T*)((u8*)self + (o)))
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

    if (self->f2220 == state && self->f2228 == sub) {
        return;
    }
    self->f2254 &= ~1;
    if (self->f2220 != state) {
        switch (self->f2220) {
        case 2: {
            self->penalizedTargetId = 0;
            if (state != 3 && state != 7) {
                StartSoundEffect(0x49, 0, (s32)self, 0, 1000.0f, 500.0f, 0.7f, 0.0f, 0.0f, 0, 0);
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
                StartSoundEffect(0x4E, 0, (s32)self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
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
            self->hook = self->f273C;
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
            TrackShape_175170* s = AT(TrackShape_175170*, track, 0x34);
            s32 turn = AT(s32, track, 0x58);
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
                StartSoundEffect(0x4D, 0, (s32)self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                loud = 1;
                SetPooledObjectPlayerHold(self->heldObject, 1);
                break;
            case 5:
                TriggerScriptEvent(self->f23B8, 2, 0, 0);
                ((BaseObject*)self->f23B8)->desc->m17((BaseObject*)self->f23B8, self);
                SetFlaggedLinkContactMask(self, self->f23B8, 1);
                layers = 1;
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
            self->f273C = self->hook;
            self->hook = 0;
            self->flags538 |= (u64)1 << 40;
            self->radius3CC = D_00262E30;
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
            StartSoundEffect(0x4F, 0, (s32)self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
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
            // The same if/else as case 4's: here anim is set again below, so the else is dead and
            // flow deletes it, but it keeps jump.c from turning a lone `skip = 1` into a
            // conditional move, as retail's branch shows (docs/TOOLCHAIN.md, "Conditional moves").
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
            AsVec_175170(self->v640) = Vu0::Vec::Zero();
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
            if (self->f2B70 != 0 && IsObjectOfKind((BaseObject*)self->f2B70, 0x70)) {
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

void IgnorePlayerArgument(void)
{
}

void SetPlayerState(void* self, s32 mode, s32 count);

void SwitchPlayerState11(void* self, s32 flag)
{
    SetPlayerState(self, flag ? 11 : 0, -1);
}

void SetPlayerProbeContactsDisabled(Player* self, s32 value)
{
    self->f2BD8 = value;
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
        case 32: q->out = node->f2B4; break;
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
s32 IsObjectAttached(void* p);
// A hit CollectMeshHits gives (0x30 bytes).
struct MeshHit {
    u8 pad00[0x30];
};
s32 CollectMeshHits(f32 radius, Vec02* point, s32 count, void* nodes, void* a3, Mesh03* mesh, s32 max, MeshHit* out);
void HeapSortRecords(void* base, s32 count, s32 size, s32 (*compare)(FloatKeyedItem* a, FloatKeyedItem* b));
void func_001C61E0(Player* self, s32 n);
void* FillMemory(void* dst, s32 value, s32 size);

// The player's grabs of the frame. The state picks the object it reaches with (one of the five
// at 0x25D8) and the kinds of hold it takes (2, 4 or 8). Each class 0x75 object of those kinds
// whose position is on the object's mesh, and each contact of this frame between the object and
// another, makes a query (up to 64), nearest along the object's first axis first; the first whose
// node the player has not taken yet is taken (up to 32): its kind 2 drops the player's state,
// kind 1 ends the grab (the object's slot 3, or state 13 in state 0x37). The frame's contacts
// go back to the world's pool.
void func_00177990(Player* self)
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

    if (self->f2220 == 4) {
        goto done;
    }
    if (self->f2228 == 7) {
        target = (Collider*)self->f25D8[1];
        mask = 4;
    } else if (self->f223C == 4 || self->f223C == 6 || self->f223C == 5 || self->f223C == 7) {
        target = (Collider*)self->f25D8[0];
        mask = 2;
    } else if (self->f2220 == 10) {
        target = (Collider*)self->f25D8[2];
        mask = 8;
    } else if (self->f2228 == 8) {
        target = (Collider*)self->f25D8[3];
        mask = 4;
    } else if (self->f2228 == 0x37 && (MaskWorldBitsBySave() & 0x400)) {
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
            if (CollectMeshHits(o->scale, &pos, target->tree.count2, target->tree.nodes, 0, &target->meshCopy, 1, &hit) <= 0) {
                continue;
            }
            if (n >= sizeof(recs) / sizeof(recs[0])) {
                break;
            }
            rec = &recs[n];
            FillMemory(rec, 0, 0x40);
            n++;
            ComputeObjectMotionInFrame((s32)o->parent, 0, &pos, (s32)&rec->dir, 0, 0, 0);
            ComputeObjectMotionInFrame((s32)o->parent, 0, &pos, (s32)&motion, 0, 0, 0);
            rec->p00 = self;
            rec->hold = o;
            rec->pos = pos;
            rec->kind = mask;
            rec->weight = self->mass * scale;
            Vu0::StoreX(rec->key, Vu0::Dot(Vu0::Q(target->m110.r[0]), Vu0::Q(pos)));
        }
    }
    if (n == 0 && self->f2670 == 0) {
        return;
    }
    for (Contact03* c = self->f2670; c != 0; c = c->next) {
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
        rec->pos = c->end[1 - e].v10;
        rec->kind = mask;
        rec->weight = self->mass * 1000.0f;
        ComputeObjectMotionInFrame((s32)c->end[e].part, 0, &rec->pos, (s32)&rec->dir, 0, 0, 0);
        Vu0::StoreX(rec->key, Vu0::Dot(Vu0::Q(target->m110.r[0]), Vu0::Q(rec->pos)));
    }
    HeapSortRecords(recs, n, 0x40, CompareKeysAscending);
    for (i = 0; i < n; i++) {
        rec = &recs[i];
        PlacedObject* node = FindNodeForQuery(rec, self->f25EC, self->f25F0);
        if (node == 0) {
            continue;
        }
        if (rec->out & 2) {
            if (mask & 2) {
                if (self->f223C == 6 || self->f223C == 4) {
                    SetPlayerState(self, 0, -1);
                    func_001C61E0(self, 8);
                } else {
                    SetPlayerState(self, 0, -1);
                    func_001C61E0(self, 9);
                }
            } else if (mask & 4) {
                SetPlayerState(self, 0, -1);
                func_001C61E0(self, 8);
            }
        }
        if (rec->out & 1) {
            if (self->f2228 == 0x37) {
                SetPlayerState(self, 0xD, 0x38);
            } else {
                target->desc->m03(target);
            }
            goto done;
        }
        if ((u32)self->f25EC < 32) {
            self->f25F0[self->f25EC++] = node;
        }
    }
done:
    FreePooledContactChain(self->world, self->f2670);
    self->f2670 = 0;
}

s32 IsTopCameraController(u8* p);

s32 IsPlayerCameraFree(Player* self)
{
    if (self->f2220 == 12 && self->f2228 == 0x22) return 0;
    return IsTopCameraController((u8*)&g_camera->ctl454) == 0;
}

void StartSwitchedColliderEffect(void* self, s32 mode);
void SetPlayerState(void* self, s32 a, s32 b);

void StartPlayerEffect(Player* self, s32 mode)
{
    StartSwitchedColliderEffect(self, mode);
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
    switch (self->f2220) {
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
        out[1] = (s32)self->f2BD0 == (s32)other;
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

void PushStackElement(void* a, void* b);

void ReceivePlayerNode(Player* self, InteractTarget* node)
{
    if ((u32)(node->mode - 1) < 2) {
        g_typedTextCaptionBox.child = node;
        PushStackElement(g_elementStack, &g_typedTextCaptionBox);
        return;
    }
    if (self->f2220 != 0xC) {
        s32 f = self->f2254;
        self->f225C = 0x21;
        self->f2BD0 = node;
        self->f2258 = 0xC;
        self->f2254 = f | 1;
    }
}

void SetColliderPosition(void* self);
void ResetTrailRing(void* sub);

void SetPlayerPosition(Player* self)
{
    SetColliderPosition(self);
    ResetTrailRing(self->f1520);
    self->f2768 = 0;
}

void InitSwitchedCollider(void* self);



void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void SetFollowObjects(void* a, s32 b, s32 c);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
void SetModeColliderMode(void* self, s32 a1);
s32 FindAnimRecord(s32 key);


void ResetTrailRing(void* sub);
void RegisterSwitchedCollider(void* self);

void RegisterPlayer(Player* self)
{
    ResetTrailRing(self->f1520);
    RegisterSwitchedCollider(self);
}

// An object the player was queued to (+0x2BE0): a walker handle at +0x2D8, and the list of the
// objects at +0x304 (count at +0x300) whose own walkers it sets.
struct WalkerListObject;
void GetStateWalkerCurrentKey(void* p, s32* out);
void GetStateWalkerTargetKey(void* p, s32* out);
void SetStateWalkerTarget(void* p, s32 key);

void func_00178068(Player* self)
{
    s32 state = self->f2220;
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
        GetStateWalkerCurrentKey(host->f2D8, &cur);
        GetStateWalkerTargetKey(host->f2D8, &target);
        if (cur != 0x22E) {
            return;
        }
        if (target != cur && target != -1) {
            return;
        }
        if (g_currentLevelRecord->f438 > 0) {
            g_player->f26D4 = host;
            SetPlayerState(g_player, 9, 0x1E);
            return;
        }
        for (s32 i = 0; i < host->count; i++) {
            SetStateWalkerTarget(host->list[i]->f2D4, 0x231);
        }
        Vec02 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(host->v140), Vu0::Q(g_player->v140));
        g_player->f638 = ArctangentOfRatio(d.y, d.x);
    }
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first



s32 HasSpareCount(void);
void ComputeModeColliderAnchors(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void SetModeColliderMode(void* self, s32 a1);



// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 D_00263E2C;

void DecrementGaugeCount(void* p);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void ReplaceAnimationPlayer(void* a, CountdownCollider* b, s32 c, void* d, f32 e, f32 f);
s32 HandleObjectEvent(void* self, ObjectEvent* msg);


void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.


// A walker's current and target keys (GetStateWalkerCurrentKey, GetStateWalkerTargetKey).
struct WalkerKeys { s32 a, b; };

void GetStateWalkerCurrentKey(void* ptr, s32* out);
void GetStateWalkerTargetKey(void* ptr, s32* out);

void QueuePlayerWalkerActivation(Player* self, u8* other)
{
    WalkerKeys r;
    if (self->f2220 != 9) {
        GetStateWalkerCurrentKey(*(void**)(other + 0x2D8), &r.a);
        GetStateWalkerTargetKey(*(void**)(other + 0x2D8), &r.b);
        if (r.a == 0x22E && (r.b == r.a || r.b == -1)) {
            self->walkerActivation = other;
        }
    }
}

void InitCollider(void* self);


s32 ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);





s32 IsObjectAttached(void* p);


extern s32 D_00263E2C;


void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, int n, void* table);


void ComputeModeColliderAnchors(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);


void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
void SetGaugeModeObjectMode(GaugeModeObject* self, s32 a1);
s32 PlayGaugeModeObjectLoop(GaugeModeObject* self, s32 a1);



void DecrementGaugeCount(void* p);
void PlayGaugeModeObjectTarget(GaugeModeObject* self);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);


s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);


void QueuePlayerFirstActivation(Player* a0, InteractTarget* a1)
{
    if (a0->f2220 != 9 && a1->mode == 0) {
        a0->firstActivation = a1;
    }
}

void QueuePlayerSecondActivation(Player* a0, InteractTarget* a1)
{
    if (a0->f2220 != 9 && a1->mode == 0) {
        a0->secondActivation = a1;
    }
}

ASM_FUNC(func_001782A8);

INCLUDE_ASM(func_001782C0);


void MoveCollider(void* self, void* b);


void FinishSwitchedCollider(void* self);
void SetModeColliderMode(void* self, s32 a1);


void HandleSwitchedColliderNotification(void* self, s32 kind, MessageBody* rec);


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

void ChooseBestTargetCandidate(void* self, s32 a1, s32 a2, void* a3, void* a4);
void ComputeTargetArc(void* self, void* s2, f32 f, void* a2, void* a3, void* a4);
void SetPlayerState(void* self, s32 a, s32 b);


void LaunchPlayerAtTarget(Player* self, TargetHit* s2, f32 f)
{
    TargetArcFrame fr;
    fr.fl = f;
    if (s2 == 0) {
        ChooseBestTargetCandidate(self, 0, 0, &fr.p0, &fr.fl);
        s2 = (TargetHit*)&fr.p0;
    }
    void* q1 = &fr.q1;
    ComputeTargetArc(self, s2, fr.fl, q1, &fr.q0, &fr.q2);
    ((TargetLaunch*)self->f2514)->landTime = g_gameTime[0] + fr.fl;
    ((TargetLaunch*)self->f2514)->q20 = fr.q0;
    ((TargetLaunch*)self->f2514)->q30 = fr.q2;
    self->desc02()->m20(self, (Vec02*)q1);
    self->q2B70[0] = s2->q0;
    self->q2B70[1] = s2->q1;

    SetPlayerState(self, 4, 0x2C);
}

INCLUDE_RODATA(D_0024AFA0);
extern const f32 D_0024AFA0;

void EvaluateHermiteVectorSegment(void* a, void* b, void* c, void* d, f32 f12, f32 f13, f32 f14, void* a4, s32 a5, s32 a6);
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
        ComputeTargetArc(self, target, D_002639E8[i], &a, &b, &c);
        b.z = b.z - 75.0f;
        prev = start;
        f32 total = 1.0f;
        for (f32 u = 0.0f; u < D_002639E8[i]; u += 0.25f) {
            EvaluateHermiteVectorSegment(&start, &a, &b, &c, D_002639E8[i], D_002639E8[i] <? (u + 0.25f), 1.0f, &cur, 0, 0);
            s32 n = CollectSpansFromList(&prev, &cur, count, list, 8, spans);
            for (s32 k = 0; k < n; k++) {
                total += Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(spans[k].q[0]), Vu0::Q(spans[k].q[1]))));
            }
            prev = cur;
        }
        f32 score = total * Vu0::ToFloat(Vu0::Length(Vu0::Q(a)));
        if (score < bestScore) {
            bestScore = score;
            bestTime = D_002639E8[i];
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
    ComputeTargetArc(self, cand, t, 0, &q, 0);
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
            f32 d = -o->f6CC - ((Vec02*)o->mesh.verts)[o->f6D0].z;
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




void SetWorldActiveFollower(void* a, void* b);
s32 ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);


extern s32 D_00263E2C;
extern s32 g_timeoutFired;

void UpdateCollider(void* self);
void StopAnimationPlayer(void* p);
void SetCountdownState(void* self, s32 state);
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

f32 Cosine(f32 x);
void SetObjectTreeRecordValue(ModeCollider* o, u32 value);
void func_00125C90(ModeCollider* o, void* s, void* out);


// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void StepCollider(ModeCollider* self, f32 t);
void ComputeModeColliderAnchors(ModeCollider* self, Vec02* a, Vec02* b);
void SteerColliderTowardPosition(ModeCollider* self, void* buf, f32 f, void* d1, void* d2, void* d3);
void TurnColliderTowardRotation(ModeCollider* self, f32 scale, void* out, void* data);


// A 0x20-byte candidate: an object, its distance along its curve (class 0x6E) and the point
// ComputeTargetArc gives. The player keeps f2768 of them at 0x2770.
struct TargetCandidate {
    BaseObject* node;       // 0x00
    f32 f4;                 // 0x04
    u8 pad08[8];
    u8 f10[16];             // 0x10
};
s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void PushBackMemoryMark(void);
TargetCandidate* AllocateZeroedBackMemory(s32 size);
void PopBackMemoryMark(void);
s32 IsObjectOfKind(BaseObject* n, s32 kind);
void TransformPointBetweenFrames(void* a, void* b, Vec02* c, Vec02* d);
void ComputeTargetArc(Player* self, TargetCandidate* e, f32 f, void* a2, void* a3, void* a4);
s32 CompareDistanceFromPlayer(TargetCandidate* a, TargetCandidate* b);
void SortElements(TargetCandidate* base, s32 n, s32 size, s32 (*cmp)(TargetCandidate*, TargetCandidate*));
f32 ScoreTargetCandidate(Player* self, void* e, s32 v, void* a3, TargetHit* a4, f32* a5);
void* FillMemory(void* dst, s32 value, s32 size);

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

    v = GatherObjectsById(self->world, 5, 8, 0, 0x20, scratch);
    PushBackMemoryMark();
    buf = AllocateZeroedBackMemory(n << 5);
    for (s32 i = 0; i < n; i++) {
        BaseObject* node = items[i];
        if (IsObjectAttached(node) != 0) {
            TargetCandidate* e = buf + cnt;
            cnt = cnt + 1;
            e->node = node;
            if (IsObjectOfKind(node, 0x6E) != 0) {
                TransformPointBetweenFrames(0, node->parent, &self->v140, &tmp);
                PathCurve* s = ((PathCurveObject*)node)->curve;
                if (s->vt->m10 != 0) {
                    s->vt->m10(s, &tmp, 0, 0, 0, 0, &e->f4);
                }
            } else {
                e->f4 = 0;
            }
            ComputeTargetArc(self, e, 0.7f, 0, e->f10, 0);
        }
    }
    SortElements(buf, cnt, 0x20, CompareDistanceFromPlayer);
    best = 3.40282347e+38f;
    for (s32 i = 0; i < cnt; i++) {
        r = ScoreTargetCandidate(self, &buf[i], v, scratch, &hit, &dist);
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
            r = ScoreTargetCandidate(self, q, v, scratch, &hit, &dist);
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
    f32 f4;
    f32 f8;
    u8 padC[4];
    Vec02 pos;
};
extern const Vec02 D_00248D30;
void ConvertPositionToWorld(void* obj, Vec02* out);
void* MoveMemory(void* dst, void* src, s32 size);
#define History(p) ((TargetMemo*)((u8*)(p) + 0x2770))
void func_001790B8(Player* self)
{
    Vec02 pos = D_00248D30;
    TargetMemo tmp;
    u8* key = 0;
    f32 w = 0.0f;
    switch (self->f2220) {
    case 3: {
        u8* o = (u8*)self->f2204;
        if (*(s32*)(o + 0xB8) != 0) {
            return;
        }
        key = o;
        break;
    }
    case 6:
        switch (self->f239C) {
        case 4: {
            u8* o = (u8*)self->f23BC;
            if (*(s32*)(o + 0x50) != 0) {
                return;
            }
            key = o;
            w = *(f32*)((u8*)self + 0x23C4);
            break;
        }
        case 5: {
            u8* o = *(u8**)((u8*)self + 0x23B8);
            if (*(s32*)(o + 0x5C) != 0) {
                return;
            }
            key = o;
            break;
        }
        case 0: {
            u8* o = (u8*)self->f23A0;
            if (o != 0) {
                if (*(s32*)(o + 0x5C) != 0) {
                    return;
                }
                key = o;
                w = self->f23A4;
            } else {
                o = (u8*)self->f23A8;
                if (*(s32*)(o + 0x74) != 0) {
                    return;
                }
                key = o;
                ConvertPositionToWorld(o, (Vec02*)&tmp);
                Vu0::Q(tmp.pos) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)&tmp));
                w = ArctangentOfRatio(tmp.pos.y, tmp.pos.x) * *(f32*)((u8*)self->f23A8 + 0x5C);
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
        if (self->f690 == 0) {
            return;
        }
        if (self->f6C0 == 0) {
            pos = self->v6A0;
        } else {
            if ((((Collider*)self->f6C0)->flags538 & (1ull << 52)) != 0) {
                return;
            }
            pos = self->v6A0;
        }
        break;
    case 7: {
        u8* o = (u8*)self->f2208;
        if (*(s32*)(o + 0x60) != 0) {
            return;
        }
        w = self->f2410;
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
                if (__builtin_fabsf(w - e->f4) < 50.0f) {
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
    History(self)[0].f4 = w;
    History(self)[0].f8 = g_gameClock[1];
}
