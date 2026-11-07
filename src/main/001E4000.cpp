// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "game_progress.h"

extern const f32 D_00249E4C = 3.4028235e+38f;
extern const char D_0024A2D0[8] = "Splash";
extern const char D_0024A2D8[16] = "Paris, France";
extern const char D_0024A2E8[16] = "The Hideout";
extern const char D_0024A2F8[24] = "A Stealthy Approach";
extern const char D_0024A310[24] = "Prowling the Grounds";
extern const char D_0024A328[24] = "High Class Heist";
extern const char D_0024A340[24] = "Into the Machine";
extern const char D_0024A358[24] = "A Cunning Disguise";
extern const char D_0024A370[24] = "The Fire Down Below";
extern const char D_0024A388[24] = "Treasure in the Depths";
extern const char D_0024A3A0[24] = "The Gunboat Graveyard";
extern const char D_0024A3B8[24] = "The Eye of the Storm";
extern const char D_0024A3D0[16] = "A Rocky Start";
extern const char D_0024A3E0[16] = "Muggshot's Turf";
extern const char D_0024A3F0[16] = "Boneyard Casino";
extern const char D_0024A400[24] = "Murray's Big Gamble";
extern const char D_0024A418[24] = "At the Dog Track";
extern const char D_0024A430[16] = "Two to Tango";
extern const char D_0024A440[24] = "Straight to the Top";
extern const char D_0024A458[24] = "Back Alley Heist";
extern const char D_0024A470[16] = "Last Call";
extern const char D_0024A480[24] = "The Dread Swamp Path";
extern const char D_0024A498[24] = "The Swamp's Dark Center";
extern const char D_0024A4B0[24] = "The Lair of the Beast";
extern const char D_0024A4C8[24] = "A Grave Undertaking";
extern const char D_0024A4E0[16] = "Piranha Lake";
extern const char D_0024A4F0[24] = "Descent into Danger";
extern const char D_0024A508[24] = "A Ghastly Voyage";
extern const char D_0024A520[24] = "Down Home Cooking";
extern const char D_0024A538[16] = "A Deadly Dance";
extern const char D_0024A548[24] = "A Perilous Ascent";
extern const char D_0024A560[24] = "Inside the Stronghold";
extern const char D_0024A578[24] = "Flaming Temple of Flame";
extern const char D_0024A590[16] = "The Unseen Foe";
extern const char D_0024A5A0[24] = "The King of the Hill";
extern const char D_0024A5B8[24] = "Rapid Fire Assault";
extern const char D_0024A5D0[24] = "Duel by the Dragon";
extern const char D_0024A5E8[24] = "A Desperate Race";
extern const char D_0024A600[16] = "Flame Fu!";
extern const char D_0024A610[24] = "A Hazardous Path";
extern const char D_0024A628[16] = "Burning Rubber";
extern const char D_0024A638[16] = "A Daring Rescue";
extern const char D_0024A648[24] = "Bentley Comes Through";
extern const char D_0024A660[24] = "A Temporary Truce";
extern const char D_0024A678[16] = "Sinking Peril";
extern const char D_0024A688[24] = "A Strange Reunion";

extern const double D_0024E9C8 = 0.1;
extern const double D_0024E9D0 = 0.1;
extern const double D_0024E9D8 = 1000000.0;
extern const char D_002504F8[48] = "Too small buffer size for %dx%d picture\n";

f32 D_00261CD4 = 500.0f;
f32 D_00261CD8 = 800.0f;
ThresholdRange D_00261D40[4] = {
    { 0.8f, 2, 5 }, { 0.4f, 6, 10 }, { 0.2f, 15, 25 }, { 0.0f, 50, 100 }
};
f32 D_00262178[2] = { 0.5f, 2.0f };
f32 D_002621F8[6] = { 7.0f, 1.0f, 0.25f, 0.0f, 0.0f, 0.0f };
f32 D_00262210[4] = { 0.0f, 0.25f, 0.000250000012f, 0.0f };
f32 D_00262220[4] = { 0.0f, 0.25f, 0.0250000004f, 0.0f };
char D_00262250[8] = "02134";
s32 D_002622CC = 1;
GameProgress* D_002623C0 = &D_0027C220;
G27C230* D_002623C4 = D_0027C230;
G27C230* D_002623C8 = D_0027C230;
s32 D_002623CC = -1;

// Globals typed by worker dz02, from retail's bytes and their readers.
// size: s32 counter (lw/sw), 4 bytes before an 8-aligned next label
s32 D_00261D38 = 0;
// size: func_00151A68 clears 0x24 bytes of it
ScatterController D_00261EF0 = {};
// size: semaphore id from func_002027A0 (lw/sw), 4-byte label
s32 D_00261F14 = 0;
s32 D_00261F18 = 0;
s32 D_00261F1C = 0;
s32 D_00261F20 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_00261F70 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_00262260 = 0;
// size: pointer to array allocated by new Ent[D_00262260] (lw/sw), 4-byte label
u8* D_00262264 = 0;
// size: loop bound 5, stride 4 in func_0015C200
s32 D_00262268[5] = {0};
// size: s32 (lw/sw), 4-byte label
s32 D_0026227C = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_002622D0 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_002622D4 = 0;
// size: pointer (lw/sw), 4 bytes before an 8-aligned next label
RenderFrame* D_002622D8 = 0;
// size: 12-byte record copied into Slot r20 by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622E0 = {};
// size: 12-byte record copied into Slot r2C by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622F0 = {};
// size: 12-byte record copied into Slot r38 by func_0015EC68
List01 D_00262300 = {};
// size: s32 (sw), 4-byte label
s32 D_00262310 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_00262318 = 0;
// size: func_0015E810 loops 2 records of stride 0x48 (end = base + 0x90)
RenderFrame D_00262320[2] = {};
// size: pointer (lw/sw), 4-byte label
void* D_002623B4 = 0;
