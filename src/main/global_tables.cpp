// SPDX-License-Identifier: AGPL-3.0-or-later
// A file of data only, after src/main/property_registry.cpp in the link and before
// src/main/object_host_functions.cpp (.rodata 0x244F40 to 0x248D80, .data 0x250580 to 0x2505D8):
// tables code all over the game reads, the sound table, the class descriptors by class id, the
// checksum table of the disc check, keys, the level table, unit vectors. Named after what it
// holds.
#include "common.h"
#include "class_descriptor.h"
#include "asm_func.h"
#include "anim_curve.h"
#include "keyed_entry.h"
#include "key_record.h"
#include "screen_element.h"
#include "level_entry.h"

// The sounds' table: each sound's bank and its index in the bank, by id (func_001BE4A8 reads it;
// func_001C0070 reads it from its second word, D_00245024).
struct SoundEntry { s32 bank; s32 index; };

void UpdateColliderBounds();

extern const ClassHead D_00217410;
extern const ClassDescriptor<28> D_00217418;
extern const ClassDescriptor<48> D_00217498;
extern const ClassDescriptor<86> D_00217568;
extern const ClassDescriptor<28> D_00217740;
extern const ClassDescriptor<28> g_pointObjectClass;
extern const ClassDescriptor<28> D_00217840;
extern const ClassDescriptor<28> D_002178C0;
extern const ClassDescriptor<28> D_00217940;
extern const ClassDescriptor<48> D_002179C0;
extern const ClassDescriptor<48> D_00217A90;
extern const ClassDescriptor<48> D_00217B60;
extern const ClassDescriptor<124> D_00217C30;
extern const ClassDescriptor<28> g_coloredTriangleSetClass;
extern const ClassDescriptor<72> D_00218770;
extern const ClassDescriptor<48> D_002188A0;
extern const ClassDescriptor<74> D_00218970;
extern const ClassDescriptor<72> D_00218AA8;
extern const ClassDescriptor<74> D_00218BD8;
extern const ClassDescriptor<74> D_00218D10;
extern const ClassDescriptor<74> D_00218E48;
extern const ClassDescriptor<72> D_00218F80;
extern const ClassDescriptor<72> D_002190B0;
extern const ClassDescriptor<28> D_002191E0;
extern const ClassDescriptor<48> D_00219260;
extern const ClassDescriptor<72> D_00219330;
extern const ClassDescriptor<28> D_00219460;
extern const ClassDescriptor<28> D_002194E0;
extern const ClassDescriptor<28> D_00219738;
extern const ClassHead g_animationPlayerMethods;
extern const ClassDescriptor<28> D_002197E8;
extern const ClassDescriptor<28> D_00219868;
extern const ClassHead g_stateWalkerMethods;
extern const ClassDescriptor<72> D_002198F0;
extern const ClassDescriptor<48> D_00219A20;
extern const ClassDescriptor<72> D_00219AF0;
extern const ClassDescriptor<48> D_00219F80;
extern const ClassDescriptor<48> D_0021A050;
extern const ClassDescriptor<28> D_0021A120;
extern const ClassDescriptor<28> D_0021A1A0;
extern const ClassDescriptor<28> D_0021A220;
extern const ClassDescriptor<28> D_0021A2A0;
extern const ClassDescriptor<48> D_0021A320;
extern const ClassDescriptor<48> D_0021A490;
extern const ClassDescriptor<28> D_0021A560;
extern const ClassDescriptor<28> D_0021A5E0;
extern const ClassDescriptor<72> D_0021A660;
extern const ClassDescriptor<28> D_0021A7B8;
extern const ClassDescriptor<88> D_0021A838;
extern const ClassDescriptor<74> D_0021A9D0;
extern const ClassDescriptor<72> D_0021AB08;
extern const ClassDescriptor<78> D_0021AC38;
extern const ClassDescriptor<78> D_0021AD80;
extern const ClassDescriptor<78> D_0021AEC8;
extern const ClassDescriptor<78> D_0021B010;
extern const ClassDescriptor<28> D_0021B158;
extern const ClassDescriptor<28> D_0021B1D8;
extern const ClassDescriptor<28> D_0021B258;
extern const ClassDescriptor<72> g_idFilterObjectClass;
extern const ClassDescriptor<48> g_redirectObjectClass;
extern const ClassDescriptor<72> D_0021B4D8;
extern const ClassDescriptor<28> D_0021B608;
extern const ClassDescriptor<88> D_0021B688;
extern const ClassDescriptor<28> D_0021B7F8;
extern const ClassDescriptor<72> D_0021B878;
extern const ClassDescriptor<72> D_0021B9A8;
extern const ClassDescriptor<28> g_itemKeeperClass;
extern const ClassDescriptor<100> D_0021BB58;
extern const ClassDescriptor<100> D_0021BCF8;
extern const ClassDescriptor<100> D_0021BE98;
extern const ClassDescriptor<72> D_0021C038;
extern const ClassDescriptor<72> D_0021C168;
extern const ClassDescriptor<28> D_0021C298;
extern const ClassDescriptor<72> g_flaggedObjectClass;
extern const ClassDescriptor<28> g_pointGraphObjectClass;
extern const ClassDescriptor<48> D_0021C4C8;
extern const ClassDescriptor<72> g_objectCyclerClass;
extern const ClassDescriptor<48> g_stateNotifierClass;
extern const ClassDescriptor<48> D_0021C798;
extern const ClassDescriptor<48> D_0021C868;
extern const ClassDescriptor<48> D_0021C938;
extern const ClassDescriptor<48> D_0021CA08;
extern const ClassDescriptor<48> D_0021CAD8;
extern const ClassDescriptor<48> D_0021CBA8;
extern const ClassDescriptor<76> D_0021CC78;
extern const ClassDescriptor<76> D_0021CDB8;
extern const ClassDescriptor<76> D_0021CEF8;
extern const ClassDescriptor<48> D_0021D038;
extern const ClassDescriptor<48> D_0021D108;
extern const ClassDescriptor<84> D_0021D1D8;
extern const ClassDescriptor<28> D_0021D338;
extern const ClassDescriptor<72> g_objectGathererClass;
extern const ClassDescriptor<48> g_pairControllerClass;
extern const ClassDescriptor<84> D_0021D5B8;
extern const ClassDescriptor<72> g_pairedObjectClass;
extern const ClassDescriptor<72> g_hitTargetClass;
extern const ClassDescriptor<72> g_soundStateObjectClass;
extern const ClassDescriptor<72> g_objectCreatorClass;
extern const ClassDescriptor<72> D_0021DBD8;
extern const ClassDescriptor<74> D_0021DD08;
extern const ClassDescriptor<48> D_0021DE40;
extern const ClassDescriptor<74> D_0021DF10;
extern const ClassDescriptor<74> D_0021E048;
extern const ClassDescriptor<74> D_0021E180;
extern const ClassDescriptor<36> D_0021E2B8;
extern const ClassDescriptor<72> g_scaledOffsetObjectClass;
extern const ClassDescriptor<48> D_0021E588;
extern const ClassDescriptor<48> D_0021E658;
extern const ClassDescriptor<100> D_0021E728;
extern const ClassDescriptor<100> D_0021E8C8;
extern const ClassDescriptor<100> D_0021EA68;
extern const ClassDescriptor<84> D_0021EC08;
extern const ClassDescriptor<100> D_0021ED68;
extern const ClassDescriptor<28> D_0021EF08;
extern const ClassDescriptor<48> g_entryTableObjectClass;
extern const ClassDescriptor<72> D_0021F058;
extern const ClassDescriptor<72> D_0021F188;
extern const ClassDescriptor<28> D_0021F2B8;
extern const ClassDescriptor<28> D_0021F338;
extern const ClassDescriptor<28> D_0021F3B8;
extern const ClassDescriptor<28> D_0021F438;
extern const ClassDescriptor<88> D_0021F4B8;
extern const ClassDescriptor<84> D_0021F628;
extern const ClassDescriptor<100> D_0021F788;
extern const ClassDescriptor<84> D_0021F928;
extern const ClassDescriptor<100> D_0021FA88;
extern const ClassDescriptor<72> D_0021FC28;
extern const ClassDescriptor<72> D_0021FD58;
extern const ClassDescriptor<100> D_0021FE88;
extern const ClassDescriptor<100> D_00220028;
extern const ClassDescriptor<100> D_002201C8;
extern const ClassDescriptor<48> D_00220368;
extern const ClassDescriptor<84> D_00220438;
extern const ClassDescriptor<84> D_00220598;
extern const ClassDescriptor<72> D_002206F8;
extern const ClassDescriptor<72> g_countdownColliderClass;
extern const ClassDescriptor<74> D_00220958;
extern const ClassDescriptor<84> D_00220A90;
extern const ClassDescriptor<28> D_00220C40;
extern const ClassDescriptor<84> D_00220CC0;
extern const ClassDescriptor<72> D_00220E20;
extern const ClassDescriptor<48> g_idLinkedObjectClass;
extern const ClassDescriptor<48> D_00221020;
extern const ClassDescriptor<48> g_partHolderObjectClass;
extern const ClassDescriptor<48> g_currentPlacedObjectClass;
extern const ClassDescriptor<48> g_codeChecksumClass;
extern const ClassDescriptor<28> D_002214A0;
extern const ClassDescriptor<28> D_00221520;
extern const char D_0024A2D0[8];
extern const char D_0024A2D8[16];
extern const char D_0024A2E8[16];
extern const char D_0024A2F8[24];
extern const char D_0024A310[24];
extern const char D_0024A328[24];
extern const char D_0024A340[24];
extern const char D_0024A358[24];
extern const char D_0024A370[24];
extern const char D_0024A388[24];
extern const char D_0024A3A0[24];
extern const char D_0024A3B8[24];
extern const char D_0024A3D0[16];
extern const char D_0024A3E0[16];
extern const char D_0024A3F0[16];
extern const char D_0024A400[24];
extern const char D_0024A418[24];
extern const char D_0024A430[16];
extern const char D_0024A440[24];
extern const char D_0024A458[24];
extern const char D_0024A470[16];
extern const char D_0024A480[24];
extern const char D_0024A498[24];
extern const char D_0024A4B0[24];
extern const char D_0024A4C8[24];
extern const char D_0024A4E0[16];
extern const char D_0024A4F0[24];
extern const char D_0024A508[24];
extern const char D_0024A520[24];
extern const char D_0024A538[16];
extern const char D_0024A548[24];
extern const char D_0024A560[24];
extern const char D_0024A578[24];
extern const char D_0024A590[16];
extern const char D_0024A5A0[24];
extern const char D_0024A5B8[24];
extern const char D_0024A5D0[24];
extern const char D_0024A5E8[24];
extern const char D_0024A600[16];
extern const char D_0024A610[24];
extern const char D_0024A628[16];
extern const char D_0024A638[16];
extern const char D_0024A648[24];
extern const char D_0024A660[24];
extern const char D_0024A678[16];
extern const char D_0024A688[24];
extern const char D_0024DCB0[];
extern const char D_0024DCC8[];
extern const char D_0024DCE8[];
extern const char D_0024DD38[];
extern const char D_0024DD60[];
extern const char D_0024DD80[];
extern const char D_0024DDA0[];
extern const char D_0024DDC8[];
extern const char D_0024DDF0[];
extern const char D_0024DE10[];
extern const char D_0024DE38[];
extern const char D_0024DE50[];
extern const char D_0024DE70[];
extern const char D_0024DE98[];
extern const char D_0024DEC0[];
extern const char D_0024DEF0[];
extern const char D_0024DF10[];
extern const char D_0024DF50[];
extern const char D_0024DF78[];
extern const char D_0024DFA0[];
extern const char D_0024DFB8[];
extern const char D_0024DFD8[];
extern const char D_0024DFF0[];
extern const char D_0024E018[];
extern const char D_0024E038[];
extern const char D_0024E060[];
extern const char D_0024E088[];
extern const char D_0024E0A8[];
extern const char D_0024E0C8[];
extern const char D_0024E0F8[];
extern const char D_0024E118[];

extern const KeyRecord g_soundBankKeys[7] = {
    { 0x586CE175, 0xA5D810DD, 0x6CE4D53F, 0xECC6A60C, 0xF9C79CAC, 0x586738D6, 0x6CE4D502, 0xA5D3AA4D },
    { 0x76189614, 0x6EE970CD, 0x717ACA47, 0xF4A7BE8B, 0x0813F34A, 0x7615DDF6, 0x717ACA02, 0x6EE0502D },
    { 0xD57DEF5E, 0xDE51C895, 0x60C9BCCE, 0x68BEB12D, 0x3C9CC701, 0xD57600A0, 0x60C9BC90, 0xDE5AA289 },
    { 0x2E978089, 0x6C3DACD2, 0x404E96BE, 0xEB7C87D1, 0x1A44A8FD, 0x2E9C7A76, 0x404E96F5, 0x6C376D5A },
    { 0xF7910242, 0xB22A7031, 0x7E493E67, 0xC0C5A294, 0x7DAAC2EE, 0xF79D3FE7, 0x7E493E01, 0xB2212725 },
    { 0x62D93F7B, 0xF44F6995, 0xE714AFF6, 0xE9D43879, 0x45BB4335, 0x62D5735D, 0xE714AFAC, 0xF4443211 },
    { 0x903B9250, 0x94FE5B03, 0xAE386CA4, 0x5CA78ADB, 0x9C29A26A, 0x9030552E, 0xAE386C98, 0x94FB9367 },
};
extern const SoundEntry g_soundEntries[771] = {
    { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 },
    { 0, 8 }, { 0, 9 }, { 0, 10 }, { 0, 11 }, { 0, 12 }, { 0, 13 }, { 0, 14 }, { 0, 15 },
    { 0, 16 }, { 0, 17 }, { 0, 18 }, { 0, 19 }, { 0, 20 }, { 0, 21 }, { 0, 22 }, { 0, 23 },
    { 0, 24 }, { 0, 25 }, { 0, 26 }, { 0, 27 }, { 0, 28 }, { 0, 29 }, { 0, 30 }, { 0, 31 },
    { 0, 32 }, { 0, 33 }, { 0, 34 }, { 0, 35 }, { 0, 36 }, { 0, 37 }, { 0, 38 }, { 0, 39 },
    { 0, 40 }, { 0, 41 }, { 0, 42 }, { 0, 43 }, { 0, 44 }, { 0, 45 }, { 0, 46 }, { 0, 47 },
    { 0, 48 }, { 0, 49 }, { 0, 50 }, { 0, 51 }, { 0, 52 }, { 0, 53 }, { 0, 54 }, { 0, 55 },
    { 0, 56 }, { 0, 57 }, { 0, 58 }, { 0, 59 }, { 0, 60 }, { 0, 61 }, { 0, 62 }, { 0, 63 },
    { 0, 64 }, { 0, 65 }, { 0, 66 }, { 0, 67 }, { 0, 68 }, { 0, 69 }, { 0, 70 }, { 0, 71 },
    { 0, 72 }, { 0, 73 }, { 0, 74 }, { 0, 75 }, { 0, 76 }, { 0, 77 }, { 0, 78 }, { 0, 79 },
    { 0, 80 }, { 0, 81 }, { 0, 82 }, { 0, 83 }, { 0, 84 }, { 0, 85 }, { 0, 86 }, { 0, 87 },
    { 0, 88 }, { 0, 89 }, { 0, 90 }, { 0, 91 }, { 0, 92 }, { 0, 93 }, { 0, 94 }, { 0, 95 },
    { 0, 96 }, { 0, 97 }, { 0, 98 }, { 0, 99 }, { 0, 100 }, { 0, 101 }, { 0, 102 }, { 0, 103 },
    { 0, 104 }, { 0, 105 }, { 0, 106 }, { 0, 107 }, { 0, 108 }, { 0, 109 }, { 0, 110 }, { 0, 111 },
    { 0, 112 }, { 0, 113 }, { 0, 114 }, { 0, 115 }, { 0, 116 }, { 0, 117 }, { 0, 118 }, { 0, 119 },
    { 0, 120 }, { 0, 121 }, { 0, 122 }, { 0, 123 }, { 0, 124 }, { 0, 125 }, { 0, 126 }, { 0, 127 },
    { 0, 128 }, { 0, 129 }, { 0, 130 }, { 0, 131 }, { 0, 132 }, { 0, 133 }, { 0, 134 }, { 0, 135 },
    { 0, 136 }, { 0, 137 }, { 0, 138 }, { 0, 139 }, { 0, 140 }, { 0, 141 }, { 0, 142 }, { 0, 143 },
    { 0, 144 }, { 0, 145 }, { 0, 146 }, { 0, 147 }, { 0, 148 }, { 0, 149 }, { 0, 150 }, { 0, 151 },
    { 0, 152 }, { 0, 153 }, { 0, 154 }, { 0, 155 }, { 0, 156 }, { 0, 157 }, { 0, 158 }, { 0, 159 },
    { 0, 160 }, { 0, 161 }, { 0, 162 }, { 0, 163 }, { 0, 164 }, { 0, 165 }, { 0, 166 }, { 0, 167 },
    { 0, 168 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 },
    { 1, 7 }, { 1, 8 }, { 1, 9 }, { 1, 10 }, { 1, 11 }, { 1, 12 }, { 1, 13 }, { 1, 14 },
    { 1, 15 }, { 1, 16 }, { 1, 17 }, { 1, 18 }, { 1, 19 }, { 1, 20 }, { 1, 21 }, { 1, 22 },
    { 1, 23 }, { 1, 24 }, { 1, 25 }, { 1, 26 }, { 1, 27 }, { 1, 28 }, { 1, 29 }, { 1, 30 },
    { 1, 31 }, { 1, 32 }, { 1, 33 }, { 1, 34 }, { 1, 35 }, { 1, 36 }, { 1, 37 }, { 1, 38 },
    { 1, 39 }, { 1, 40 }, { 1, 41 }, { 1, 42 }, { 1, 43 }, { 1, 44 }, { 1, 45 }, { 1, 46 },
    { 1, 47 }, { 1, 48 }, { 1, 49 }, { 1, 50 }, { 1, 51 }, { 1, 52 }, { 1, 53 }, { 1, 54 },
    { 1, 55 }, { 1, 56 }, { 1, 57 }, { 1, 58 }, { 1, 59 }, { 1, 60 }, { 1, 61 }, { 1, 62 },
    { 1, 63 }, { 1, 64 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 },
    { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 }, { 2, 10 }, { 2, 11 }, { 2, 12 }, { 2, 13 },
    { 2, 14 }, { 2, 15 }, { 2, 16 }, { 2, 17 }, { 2, 18 }, { 2, 19 }, { 2, 20 }, { 2, 21 },
    { 2, 22 }, { 2, 23 }, { 2, 24 }, { 2, 25 }, { 2, 26 }, { 2, 27 }, { 2, 28 }, { 2, 29 },
    { 2, 30 }, { 2, 31 }, { 2, 32 }, { 2, 33 }, { 2, 34 }, { 2, 35 }, { 2, 36 }, { 2, 37 },
    { 2, 38 }, { 2, 39 }, { 2, 40 }, { 2, 41 }, { 2, 42 }, { 2, 43 }, { 2, 44 }, { 2, 45 },
    { 2, 46 }, { 2, 47 }, { 2, 48 }, { 2, 49 }, { 2, 50 }, { 2, 51 }, { 2, 52 }, { 2, 53 },
    { 2, 54 }, { 2, 55 }, { 2, 56 }, { 2, 57 }, { 2, 58 }, { 2, 59 }, { 2, 60 }, { 2, 61 },
    { 2, 62 }, { 2, 63 }, { 2, 64 }, { 2, 65 }, { 2, 66 }, { 2, 67 }, { 2, 68 }, { 2, 69 },
    { 2, 70 }, { 2, 71 }, { 2, 72 }, { 2, 73 }, { 2, 74 }, { 2, 75 }, { 2, 76 }, { 2, 77 },
    { 2, 78 }, { 2, 79 }, { 2, 80 }, { 2, 81 }, { 2, 82 }, { 2, 83 }, { 2, 84 }, { 2, 85 },
    { 2, 86 }, { 2, 87 }, { 2, 88 }, { 2, 89 }, { 2, 90 }, { 2, 91 }, { 2, 92 }, { 2, 93 },
    { 2, 94 }, { 2, 95 }, { 2, 96 }, { 2, 97 }, { 2, 98 }, { 2, 99 }, { 2, 100 }, { 2, 101 },
    { 2, 102 }, { 2, 103 }, { 2, 104 }, { 2, 105 }, { 2, 106 }, { 2, 107 }, { 2, 108 }, { 2, 109 },
    { 2, 110 }, { 2, 111 }, { 2, 112 }, { 2, 113 }, { 2, 114 }, { 2, 115 }, { 2, 116 }, { 2, 117 },
    { 2, 118 }, { 2, 119 }, { 2, 120 }, { 2, 121 }, { 2, 122 }, { 2, 123 }, { 2, 124 }, { 2, 125 },
    { 2, 126 }, { 2, 127 }, { 2, 128 }, { 2, 129 }, { 2, 130 }, { 2, 131 }, { 2, 132 }, { 2, 133 },
    { 2, 134 }, { 2, 135 }, { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 },
    { 3, 6 }, { 3, 7 }, { 3, 8 }, { 3, 9 }, { 3, 10 }, { 3, 11 }, { 3, 12 }, { 3, 13 },
    { 3, 14 }, { 3, 15 }, { 3, 16 }, { 3, 17 }, { 3, 18 }, { 3, 19 }, { 3, 20 }, { 3, 21 },
    { 3, 22 }, { 3, 23 }, { 3, 24 }, { 3, 25 }, { 3, 26 }, { 3, 27 }, { 3, 28 }, { 3, 29 },
    { 3, 30 }, { 3, 31 }, { 3, 32 }, { 3, 33 }, { 3, 34 }, { 3, 35 }, { 3, 36 }, { 3, 37 },
    { 3, 38 }, { 3, 39 }, { 3, 40 }, { 3, 41 }, { 3, 42 }, { 3, 43 }, { 3, 44 }, { 3, 45 },
    { 3, 46 }, { 3, 47 }, { 3, 48 }, { 3, 49 }, { 3, 50 }, { 3, 51 }, { 3, 52 }, { 3, 53 },
    { 3, 54 }, { 3, 55 }, { 3, 56 }, { 3, 57 }, { 3, 58 }, { 3, 59 }, { 3, 60 }, { 3, 61 },
    { 3, 62 }, { 3, 63 }, { 3, 64 }, { 3, 65 }, { 3, 66 }, { 3, 67 }, { 3, 68 }, { 3, 69 },
    { 3, 70 }, { 3, 71 }, { 3, 72 }, { 3, 73 }, { 3, 74 }, { 3, 75 }, { 3, 76 }, { 3, 77 },
    { 3, 78 }, { 3, 79 }, { 3, 80 }, { 3, 81 }, { 3, 82 }, { 3, 83 }, { 3, 84 }, { 3, 85 },
    { 3, 86 }, { 3, 87 }, { 3, 88 }, { 3, 89 }, { 3, 90 }, { 3, 91 }, { 3, 92 }, { 3, 93 },
    { 3, 94 }, { 3, 95 }, { 3, 96 }, { 3, 97 }, { 3, 98 }, { 3, 99 }, { 3, 100 }, { 3, 101 },
    { 3, 102 }, { 3, 103 }, { 3, 104 }, { 3, 105 }, { 3, 106 }, { 3, 107 }, { 3, 108 }, { 3, 109 },
    { 3, 110 }, { 3, 111 }, { 3, 112 }, { 3, 113 }, { 3, 114 }, { 3, 115 }, { 3, 116 }, { 3, 117 },
    { 3, 118 }, { 3, 119 }, { 3, 120 }, { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 },
    { 4, 5 }, { 4, 6 }, { 4, 7 }, { 4, 8 }, { 4, 9 }, { 4, 10 }, { 4, 11 }, { 4, 12 },
    { 4, 13 }, { 4, 14 }, { 4, 15 }, { 4, 16 }, { 4, 17 }, { 4, 18 }, { 4, 19 }, { 4, 20 },
    { 4, 21 }, { 4, 22 }, { 4, 23 }, { 4, 24 }, { 4, 25 }, { 4, 26 }, { 4, 27 }, { 4, 28 },
    { 4, 29 }, { 4, 30 }, { 4, 31 }, { 4, 32 }, { 4, 33 }, { 4, 34 }, { 4, 35 }, { 4, 36 },
    { 4, 37 }, { 4, 38 }, { 4, 39 }, { 4, 40 }, { 4, 41 }, { 4, 42 }, { 4, 43 }, { 4, 44 },
    { 4, 45 }, { 4, 46 }, { 4, 47 }, { 4, 48 }, { 4, 49 }, { 4, 50 }, { 4, 51 }, { 4, 52 },
    { 4, 53 }, { 4, 54 }, { 4, 55 }, { 4, 56 }, { 4, 57 }, { 4, 58 }, { 4, 59 }, { 4, 60 },
    { 4, 61 }, { 4, 62 }, { 4, 63 }, { 4, 64 }, { 4, 65 }, { 4, 66 }, { 4, 67 }, { 4, 68 },
    { 4, 69 }, { 4, 70 }, { 4, 71 }, { 4, 72 }, { 4, 73 }, { 4, 74 }, { 4, 75 }, { 4, 76 },
    { 4, 77 }, { 4, 78 }, { 4, 79 }, { 4, 80 }, { 4, 81 }, { 4, 82 }, { 4, 83 }, { 4, 84 },
    { 4, 85 }, { 4, 86 }, { 4, 87 }, { 4, 88 }, { 4, 89 }, { 4, 90 }, { 4, 91 }, { 4, 92 },
    { 4, 93 }, { 4, 94 }, { 4, 95 }, { 4, 96 }, { 4, 97 }, { 4, 98 }, { 4, 99 }, { 4, 100 },
    { 4, 101 }, { 5, 0 }, { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 }, { 5, 6 },
    { 5, 7 }, { 5, 8 }, { 5, 9 }, { 5, 10 }, { 5, 11 }, { 5, 12 }, { 5, 13 }, { 5, 14 },
    { 5, 15 }, { 5, 16 }, { 5, 17 }, { 5, 18 }, { 5, 19 }, { 5, 20 }, { 5, 21 }, { 5, 22 },
    { 5, 23 }, { 5, 24 }, { 5, 25 }, { 5, 26 }, { 5, 27 }, { 5, 28 }, { 5, 29 }, { 5, 30 },
    { 5, 31 }, { 5, 32 }, { 5, 33 }, { 5, 34 }, { 5, 35 }, { 5, 36 }, { 5, 37 }, { 5, 38 },
    { 5, 39 }, { 5, 40 }, { 5, 41 }, { 5, 42 }, { 5, 43 }, { 5, 44 }, { 5, 45 }, { 5, 46 },
    { 5, 47 }, { 5, 48 }, { 5, 49 }, { 5, 50 }, { 5, 51 }, { 5, 52 }, { 5, 53 }, { 5, 54 },
    { 5, 55 }, { 5, 56 }, { 5, 57 }, { 5, 58 }, { 5, 59 }, { 5, 60 }, { 5, 61 }, { 5, 62 },
    { 5, 63 }, { 5, 64 }, { 5, 65 }, { 5, 66 }, { 5, 67 }, { 5, 68 }, { 5, 69 }, { 5, 70 },
    { 5, 71 }, { 5, 72 }, { 5, 73 }, { 5, 74 }, { 5, 75 }, { 5, 76 }, { 5, 77 }, { 5, 78 },
    { 5, 79 }, { 5, 80 }, { 5, 81 }, { 5, 82 }, { 5, 83 }, { 5, 84 }, { 5, 85 }, { 5, 86 },
    { 5, 87 }, { 5, 88 }, { 5, 89 }, { 5, 90 }, { 5, 91 }, { 5, 92 }, { 5, 93 }, { 5, 94 },
    { 5, 95 }, { 5, 96 }, { 5, 97 }, { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 },
    { 6, 5 }, { 6, 6 }, { 6, 7 }, { 6, 8 }, { 6, 9 }, { 6, 10 }, { 6, 11 }, { 6, 12 },
    { 6, 13 }, { 6, 14 }, { 6, 15 }, { 6, 16 }, { 6, 17 }, { 6, 18 }, { 6, 19 }, { 6, 20 },
    { 6, 21 }, { 6, 22 }, { 6, 23 }, { 6, 24 }, { 6, 25 }, { 6, 26 }, { 6, 27 }, { 6, 28 },
    { 6, 29 }, { 6, 30 }, { 6, 31 }, { 6, 32 }, { 6, 33 }, { 6, 34 }, { 6, 35 }, { 6, 36 },
    { 6, 37 }, { 6, 38 }, { 6, 39 }, { 6, 40 }, { 6, 41 }, { 6, 42 }, { 6, 43 }, { 6, 44 },
    { 6, 45 }, { 6, 46 }, { 6, 47 }, { 6, 48 }, { 6, 49 }, { 6, 50 }, { 6, 51 }, { 6, 52 },
    { 6, 53 }, { 6, 54 }, { 6, 55 }, { 6, 56 }, { 6, 57 }, { 6, 58 }, { 6, 59 }, { 6, 60 },
    { 6, 61 }, { 6, 62 }, { 6, 63 }, { 6, 64 }, { 6, 65 }, { 6, 66 }, { 6, 67 }, { 6, 68 },
    { 6, 69 }, { 6, 70 }, { 6, 71 }, { 6, 72 }, { 6, 73 }, { 6, 74 }, { 6, 75 }, { 6, 76 },
    { 6, 77 }, { 6, 78 }, { 6, 79 },
};
extern const s32 g_soundEntryForcedAvailable[772] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
extern ClassHead D_002505B8;  // in .data, below
extern const void* const D_00247448[149] = {
    &D_00217410,
    &D_00217418,
    &D_00217498,
    &D_00217568,
    &D_00220E20,
    &D_00217C30,
    &D_0021A838,
    &D_0021B688,
    &D_0021BB58,
    &D_0021BE98,
    &D_0021BCF8,
    &D_0021E728,
    &D_0021E8C8,
    &D_0021EA68,
    &D_0021F788,
    &D_0021FA88,
    &D_0021FE88,
    &D_00220028,
    &D_002201C8,
    &D_0021ED68,
    &D_0021F4B8,
    &D_0021D5B8,
    &D_0021F628,
    &D_0021D1D8,
    &D_0021F928,
    &D_00220438,
    &D_00220A90,
    &D_00220598,
    &D_0021EC08,
    &D_00220CC0,
    &D_00219AF0,
    &D_00218770,
    &D_00218970,
    &D_00218BD8,
    &D_0021A9D0,
    &D_0021DD08,
    &D_00220958,
    &D_00218D10,
    &D_00218E48,
    &D_00218AA8,
    &D_002190B0,
    &D_00218F80,
    &D_0021F058,
    &D_00219330,
    &D_0021CC78,
    &D_0021CDB8,
    &D_0021CEF8,
    &D_0021AB08,
    &D_0021AC38,
    &D_0021AD80,
    &D_0021AEC8,
    &D_0021B010,
    &g_idFilterObjectClass,
    &D_002198F0,
    &D_0021C038,
    &D_0021C168,
    &g_flaggedObjectClass,
    &g_scaledOffsetObjectClass,
    &D_0021A660,
    &D_0021B4D8,
    &D_0021DF10,
    &D_0021E048,
    &D_0021E180,
    &D_0021B878,
    &g_objectCyclerClass,
    &g_objectGathererClass,
    &g_pairedObjectClass,
    &g_hitTargetClass,
    &g_soundStateObjectClass,
    &g_objectCreatorClass,
    &D_0021DBD8,
    &D_0021F188,
    &D_0021FC28,
    &D_0021FD58,
    &D_002206F8,
    &g_countdownColliderClass,
    &D_0021B9A8,
    &D_00219F80,
    &D_00217A90,
    &D_00219260,
    &D_0021A050,
    &D_00217B60,
    &D_00219A20,
    &D_0021A320,
    &D_0021C4C8,
    &g_stateNotifierClass,
    &D_0021C868,
    &D_0021CAD8,
    &D_0021C798,
    &D_0021C938,
    &D_0021CA08,
    &D_0021CBA8,
    &D_0021D038,
    &D_0021D108,
    &g_redirectObjectClass,
    &g_pairControllerClass,
    &D_0021DE40,
    &D_0021E588,
    &D_0021E658,
    &D_002188A0,
    &g_entryTableObjectClass,
    &D_0021A490,
    &g_idLinkedObjectClass,
    &D_00221020,
    &D_00220368,
    &g_currentPlacedObjectClass,
    &g_partHolderObjectClass,
    &g_codeChecksumClass,
    &D_002214A0,
    &D_00221520,
    &D_00217740,
    &D_0021A560,
    &D_0021B258,
    &D_0021F338,
    &D_0021F3B8,
    &D_002178C0,
    &D_00217940,
    &D_0021B158,
    &D_0021B1D8,
    &D_0021A120,
    &D_0021A1A0,
    &D_0021A220,
    &D_0021A2A0,
    &D_0021C298,
    &D_0021D338,
    &D_002179C0,
    &g_pointObjectClass,
    &D_0021A5E0,
    &D_0021B7F8,
    &D_0021F2B8,
    &D_00217840,
    &D_00219738,
    &D_002197E8,
    &D_002194E0,
    &D_00219460,
    &D_002191E0,
    &D_00219868,
    &g_itemKeeperClass,
    &g_pointGraphObjectClass,
    &D_0021A7B8,
    &D_0021E2B8,
    &D_0021F438,
    &g_coloredTriangleSetClass,
    &D_0021B608,
    &D_0021EF08,
    &D_00220C40,
    &g_animationPlayerMethods,
    &g_stateWalkerMethods,
    &D_002505B8
};
extern const u32 g_crc32Table[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};
extern const u32 D_00247AA0 = 0x17F;
extern const u32 D_00247AA4 = 0x14E0EF;
extern const u32 D_00247AA8[2] = { 0x2E774159, 0 };
extern const u32 D_00247AB0[8] = { 0xFDC02D54, 0x0AB32899, 0x6BD9B0B8, 0x3C8FB5B8, 0x02EF0F96, 0xFDCCA9C0, 0x6BD9B0AD, 0x0AB165D8 };
extern const u32 D_00247AD0[8] = { 0x2F5A2B8C, 0x7C1B2134, 0xF6CA6520, 0x75002C27, 0xB708AA18, 0x2F5705BF, 0xF6CA6529, 0x7C35CE16 };
extern const KeyedEntry g_keyedEntries[46] = {
    { { 0xFDC02D54, 0x0AB32899, 0x6BD9B0B8, 0x3C8FB5B8, 0x02EF0F96, 0xFDCCA9C0, 0x6BD9B0AD, 0x0AB165D8 }, 0x00000002, D_0024A2D0, 0x00000000 },
    { { 0x70692A0C, 0x7C1ADFDF, 0x8DDAB8A2, 0xFEC7AC06, 0xCF2C336D, 0x7065AED2, 0x8DDAB8A8, 0x7C53A53E }, 0x00000003, D_0024A2D8, 0x00000000 },
    { { 0x2F5A2B8C, 0x7C1B2134, 0xF6CA6520, 0x75002C27, 0xB708AA18, 0x2F5705BF, 0xF6CA6529, 0x7C35CE16 }, 0x00000004, D_0024A2E8, 0x00000000 },
    { { 0x21AE2EFD, 0x8032D4F4, 0x57308A08, 0xFCC368AF, 0x5AE57D3A, 0x21A31573, 0x57308A2D, 0x8078262F }, 0x00000100, D_0024A2F8, 0x0000000E },
    { { 0x3A18A984, 0x43DF3FC4, 0x462872FD, 0x368F2E0E, 0xC389BEF7, 0x3A1358E8, 0x462872DB, 0x439A73E7 }, 0x00000101, D_0024A310, 0x00000000 },
    { { 0x8AFD3960, 0xAC2F4521, 0xF66CA215, 0x7550F254, 0x1C0429D2, 0x8AF1EF1F, 0xF66CA234, 0xAC131937 }, 0x00000102, D_0024A328, 0x0000000E },
    { { 0xFA00A4D4, 0x2B9592C6, 0x19333451, 0xF3021496, 0xED95088F, 0xFA0CDD98, 0x19333475, 0x2BC71397 }, 0x00000103, D_0024A340, 0x0000000E },
    { { 0x55782648, 0x7C38E297, 0x6512C668, 0xB5AF751C, 0x49FAB8FB, 0x55741958, 0x6512C648, 0x7C0F6898 }, 0x00000104, D_0024A358, 0x0000000E },
    { { 0x5ED07C40, 0x4ACAA4FF, 0x4CF76E84, 0xDF64A3A2, 0xA0F55FC3, 0x5EDC7797, 0x4CF76E9B, 0x4AF304E9 }, 0x00000105, D_0024A370, 0x0000000E },
    { { 0x59A2D291, 0x6F41BEA4, 0xCEEE7857, 0xBF734963, 0x588DB2A7, 0x59AF9F96, 0xCEEE7870, 0x6F4D10EA }, 0x00000106, D_0024A388, 0x00000002 },
    { { 0x0AF17BCA, 0x357EBDDD, 0x65AEC442, 0x209BF707, 0x2AA7CBEF, 0x0AFDDFA6, 0x65AEC46A, 0x354038F4 }, 0x00000107, D_0024A3A0, 0x0000000E },
    { { 0xBD799A28, 0xBB675614, 0xA2CFD3E5, 0x18D9F2E5, 0x1C494DB2, 0xBD75AA4A, 0xA2CFD3C7, 0xBB4013AF }, 0x00000108, D_0024A3B8, 0x00000000 },
    { { 0x9443A65C, 0x6A8C5C73, 0xF461374C, 0xB7E0CF07, 0x32B103EF, 0x94481DBB, 0xF4613740, 0x6ADA3CC7 }, 0x00000200, D_0024A3D0, 0x0000000E },
    { { 0xB2C1322F, 0x027AF1AE, 0x73D1F95C, 0x7EDA6F1F, 0x65366029, 0xB2CDECDB, 0x73D1F953, 0x022CC41B }, 0x00000201, D_0024A3E0, 0x00000000 },
    { { 0xF6AA3766, 0x6EE44033, 0xC8CEDC91, 0xF54C0C2A, 0x413C17A4, 0xF6A6DD11, 0xC8CEDC9F, 0x6EA20BE1 }, 0x00000202, D_0024A3F0, 0x0000000E },
    { { 0x96B81254, 0x87BFCA5D, 0x16A6D62F, 0x976F1995, 0xFE4CA8EC, 0x96B4DC09, 0x16A6D63D, 0x87866960 }, 0x00000203, D_0024A400, 0x00000002 },
    { { 0xE3D43512, 0x27982FB7, 0x516A4462, 0x7C1565F7, 0x1DEDAD16, 0xE3D8C137, 0x516A4471, 0x27A5D3A9 }, 0x00000204, D_0024A418, 0x00000002 },
    { { 0x3F452A5A, 0xE7DFCB19, 0x3D2FF024, 0x0A466EB9, 0xADD4FA33, 0x3F487850, 0x3D2FF034, 0xE79BCC30 }, 0x00000205, D_0024A430, 0x0000000E },
    { { 0x27EEDC0C, 0x42D1114A, 0x2AFB9928, 0xAACE171D, 0xE50F8A06, 0x27E220C6, 0x2AFB9939, 0x4290349A }, 0x00000206, D_0024A440, 0x0000000E },
    { { 0xB3590529, 0x2936FC1F, 0xE38710D4, 0xC8802051, 0xF19B17C4, 0xB35516D2, 0xE38710C0, 0x290A1469 }, 0x00000207, D_0024A458, 0x0000000E },
    { { 0x21CADA41, 0x635F5DD8, 0x1756DB03, 0x3DE92F94, 0x3CC24DD3, 0x21C12619, 0x1756DB0E, 0x636B749E }, 0x00000208, D_0024A470, 0x00000000 },
    { { 0x4792B776, 0xDB3479C6, 0xD5D60AD4, 0x49270025, 0x0648E89D, 0x479ED350, 0xD5D60AFD, 0xDB7E83B6 }, 0x00000300, D_0024A480, 0x0000000E },
    { { 0x70F7F5BA, 0xF3A4A6F8, 0x2B0CE758, 0x1B2E85EF, 0x941D6918, 0x70FAF97B, 0x2B0CE775, 0xF3F82427 }, 0x00000301, D_0024A498, 0x00000000 },
    { { 0x4288AE87, 0xF946ECEE, 0x2EC30CB4, 0x9FDEF57C, 0xF31E36E5, 0x42840398, 0x2EC30C85, 0xF90AC054 }, 0x00000302, D_0024A4B0, 0x0000000E },
    { { 0x18553E3D, 0x147C896A, 0x2A4B495D, 0x98E7B7BC, 0xAD4148A7, 0x1859FC84, 0x2A4B4971, 0x1429F912 }, 0x00000303, D_0024A4C8, 0x0000000E },
    { { 0x14ADD7B5, 0x26637BFA, 0xF61DDB5C, 0xC6091F6E, 0x0E0C8BE4, 0x14A09263, 0xF61DDB73, 0x264A610B }, 0x00000304, D_0024A4E0, 0x00000002 },
    { { 0xD5FA54DB, 0x352BF531, 0xF504CCE4, 0xA52CA674, 0x56FC4BC8, 0xD5F64852, 0xF504CCD4, 0x35621799 }, 0x00000305, D_0024A4F0, 0x0000000E },
    { { 0xFC736514, 0x7BDCD02C, 0x07BCD396, 0x04D7BB91, 0xABA60A6C, 0xFC7F3E08, 0x07BCD3B8, 0x7B9C0BDE }, 0x00000306, D_0024A508, 0x00000002 },
    { { 0x552F9A6D, 0x851FEF4D, 0x7ED446BB, 0xD56439EA, 0xEE405DE8, 0x5523D7FF, 0x7ED44690, 0x8506AECD }, 0x00000307, D_0024A520, 0x00000002 },
    { { 0x631E0C66, 0x786F0552, 0x5CD8547B, 0x790F7F64, 0xE5763F4F, 0x6315D77D, 0x5CD85451, 0x782D1F0A }, 0x00000308, D_0024A538, 0x00000000 },
    { { 0xDDE3089F, 0xF6445E0B, 0x839A18B5, 0x12B38073, 0x24AD5171, 0xDDEE11AF, 0x839A18A3, 0xF613C5C4 }, 0x00000400, D_0024A548, 0x0000000E },
    { { 0x09FCA124, 0x2FDB235A, 0x4E7C6634, 0x244D8BD6, 0xA817793B, 0x09F0CF50, 0x4E7C662D, 0x2F94FF1B }, 0x00000401, D_0024A560, 0x00000000 },
    { { 0x073DAB55, 0x33416024, 0x8CC5FB13, 0x38B05273, 0x2EBC58F1, 0x07364F1B, 0x8CC5FB08, 0x33176720 }, 0x00000402, D_0024A578, 0x0000000E },
    { { 0x69193071, 0x64C2907F, 0x9D7744B7, 0x0D7B899C, 0xBCDFE0BF, 0x691561D2, 0x9D7744A0, 0x6486EFC7 }, 0x00000403, D_0024A590, 0x0000000E },
    { { 0x31C24155, 0x2A93133E, 0xF733F040, 0x1C2232DE, 0xB2A034DB, 0x31CF6446, 0xF733F05C, 0x2AD267C8 }, 0x00000404, D_0024A5A0, 0x00000002 },
    { { 0x55F238FD, 0xA436D1AD, 0xF5C88A4C, 0x1862E8EB, 0xD61AFAD8, 0x55FE1E59, 0xF5C88A52, 0xA471F3B7 }, 0x00000405, D_0024A5B8, 0x00000002 },
    { { 0x2390CCDD, 0xE7ABA666, 0x0A8E45C4, 0x6643FE22, 0x97D2FB1E, 0x239B04E5, 0x0A8E45DE, 0xE7F898A4 }, 0x00000406, D_0024A5D0, 0x0000000E },
    { { 0x0F84BC15, 0x5C2652BF, 0xBD31382E, 0x11FED1F7, 0xB4E14DA6, 0x0F880B96, 0xBD313833, 0x5C16E898 }, 0x00000407, D_0024A5E8, 0x00000002 },
    { { 0xE4806B75, 0x1DE290C8, 0xDFCAEBC4, 0x4A1C6170, 0x71E1A8DE, 0xE48C2D92, 0xDFCAEBDC, 0x1DC193FE }, 0x00000408, D_0024A600, 0x00000000 },
    { { 0xD5B67B6A, 0x4854289A, 0xE1FCA832, 0x4F3C70E6, 0x2C782027, 0xD5BA4D2A, 0xE1FCA83A, 0x48678D7B }, 0x00000500, D_0024A610, 0x00000000 },
    { { 0xCB5C1CD2, 0x7DA13F74, 0xD29AD321, 0x41CC84D6, 0x212F6EC3, 0xCB50A252, 0xD29AD326, 0x7DBB77CD }, 0x00000502, D_0024A628, 0x00000000 },
    { { 0x36E5CD84, 0x066ED834, 0x3DA04171, 0x7BE81ABD, 0x86A774CA, 0x36EE1EF8, 0x3DA04177, 0x06477F5B }, 0x00000503, D_0024A638, 0x00000000 },
    { { 0x981B0998, 0x35E939CD, 0xE0016E8A, 0x7210407C, 0x923436E4, 0x9816461F, 0xE0016E88, 0x35E27074 }, 0x00000504, D_0024A648, 0x00000000 },
    { { 0x48C10A2C, 0xED11F262, 0xBF175611, 0x9D181905, 0x86D2E9A9, 0x48CC0FF3, 0xBF175614, 0xED3E4BF8 }, 0x00000505, D_0024A660, 0x00000000 },
    { { 0x9EAE1C3C, 0xC2FEDE9B, 0x2AFD4D95, 0x573AF42F, 0xA18F6572, 0x9EA328CC, 0x2AFD4D91, 0xC2D3B7FC }, 0x00000506, D_0024A678, 0x00000000 },
    { { 0xAC0C665D, 0x524AA938, 0x33CB5B57, 0xE1FFC9B9, 0x35BE9ACD, 0xAC006598, 0x33CB5B54, 0x527D9E86 }, 0x00000508, D_0024A688, 0x00000000 },
};
extern const KeyRecord g_streamVoiceKeys[7] = {
    {0x239C1F4B, 0x4F1B6BCE, 0x332880C9, 0xDC1FC810, 0xB3EF7189, 0x239FB500, 0x332882F6, 0x4F1B486E},
    {0x674A1AEF, 0xEAAAB4AD, 0xCE2EF724, 0xB0B61237, 0x30E7A079, 0x67448204, 0xCE2EF564, 0xEAAA8C7D},
    {0x9FFD39A4, 0x92C0B086, 0x1904453E, 0x13763226, 0x52A098D3, 0x9FFD0941, 0x1904477F, 0x92C08E66},
    {0x631F4A84, 0xB9572D78, 0xA364788C, 0xBAF57CFC, 0xB7D7C188, 0x63176250, 0xA3647ACE, 0xB9571298},
    {0x816C657F, 0xB563A94D, 0x90993FD9, 0x2B5164CE, 0xA46DB733, 0x81696BC7, 0x90993D9A, 0xB563EFCD},
    {0xD4312CB4, 0xC376AE2A, 0x8D50D2C3, 0xC7A8D28C, 0x39A7CE66, 0xD422EB19, 0x8D50D087, 0xC3769B7A},
    {0x3909A2A2, 0xDA5D87C2, 0xC3446569, 0x59D126B9, 0x6943323B, 0x390995E6, 0xC344672C, 0xDA5DAE02}
};
extern const char D_002483B8[24] = "@KFWHJGL";
extern const Mat02 g_identityMatrix = { { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f } } };
extern const f32 D_00248400[28] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
extern const KeyRecord g_memoryCardIconKey = { 0x80CFADA9, 0x930F4F53, 0x7F1AF6BE, 0x5EAA1EBC, 0xDDC30E98, 0x80DB63DE, 0x7F1AF5F2, 0x930F1BCB };
extern const IdentityKey D_00248490 = { { { 0xEF312076, 0x53B6BFB5, 0x4846D1FF, 0x0EAD57EE, 0x9E3389D7, 0xEF3E4A62, 0x4846D2BB, 0x531DFFB1 } } };
extern const IdentityKey g_movieKeys[16] = {
    { { { 0xF5248332, 0x853A4F27, 0x46B9CAE3, 0x13D7C04C, 0x74F101E3, 0xF524CCCD, 0x46B9C9A3, 0x80694F23 } } },
    { { { 0xCE3D9360, 0x2F5524C3, 0xAD69A291, 0xE6559C19, 0x9871938B, 0xCE3E40C9, 0xAD69A1D0, 0x2A3164C7 } } },
    { { { 0xFB4E86C1, 0x6C87A1D9, 0x52316802, 0x5104AFFE, 0xBE64E217, 0xFB5EE14F, 0x52316B3E, 0x7992A1DD } } },
    { { { 0xAA6745EF, 0xE20C5CCD, 0x5C96D810, 0xE02E90DD, 0xD1277036, 0xAA663067, 0x5C96DB2F, 0xEF791CC9 } } },
    { { { 0xFA1F9E5E, 0x536F409D, 0xF496C49E, 0x8DCA8A5D, 0xB23276D3, 0xFA19E5AF, 0xF496C7DB, 0x50670099 } } },
    { { { 0xA2774D68, 0x5B77ECC0, 0x919E5521, 0x27816F4B, 0x4E1FE92F, 0xA27AD384, 0x919E5667, 0x59486CC4 } } },
    { { { 0x93B51720, 0xA36BF0A9, 0x0F49C87D, 0x392C04FD, 0xECDF8673, 0x93B28EFF, 0x0F49CB40, 0xA719B0AD } } },
    { { { 0x052890A7, 0x6DF00199, 0xF4B16A32, 0x80E128F7, 0x7029184B, 0x052D5A2B, 0xF4B1690C, 0x6FBB819D } } },
    { { { 0xEBD27ABC, 0x8EDE98E5, 0x385602E3, 0x6EDAD7CC, 0x3E572A20, 0xEBDD75D0, 0x385601A4, 0x8C1658E1 } } },
    { { { 0xE621B6AA, 0xE129CC90, 0x3B5A84E3, 0x80C4FB2F, 0x26950B04, 0xE622929B, 0x3B5A87AB, 0xE0A90C94 } } },
    { { { 0x078CF2E7, 0xCFBE2AE9, 0x50D22ECE, 0xF5E53F61, 0x0EF768D9, 0x07826A14, 0x50D22D8C, 0xCC0DEAED } } },
    { { { 0x6E916B53, 0xD7899E64, 0xB27D8190, 0xACE3EE23, 0x2E5415B6, 0x6E8167C1, 0xB27D82D3, 0xD50C9E60 } } },
    { { { 0x8E98A2D8, 0x464C9D9A, 0x15CB2951, 0xF0C350EB, 0xB464DC83, 0x8E95F9A5, 0x15CB2A67, 0x478B5D9E } } },
    { { { 0xB804419D, 0x66FAEFB7, 0x07841B81, 0xF7BE8C47, 0x3AF12C8A, 0xB81795B4, 0x078418BB, 0x63B7EFB3 } } },
    { { { 0x92E9986B, 0xD7FD98C1, 0x9A3D4AC0, 0x93483E1B, 0x6D268427, 0x92EF8F9B, 0x9A3D49FB, 0xD59D18C5 } } },
    { { { 0x1B7736BC, 0x08EA9779, 0x9ABAE153, 0x01F1543B, 0x48D846BE, 0x1B72254A, 0x9ABAE26B, 0x0D7F577D } } },
};
extern void* const g_screenElements[38] = {
    (void*)&D_002721D0,
    (void*)&g_typedTextCaptionBox,
    (void*)&D_00270650,
    (void*)&D_0026C6C8,
    (void*)&D_0026C948,
    (void*)&D_0026CBC8,
    (void*)&D_0026CE48,
    (void*)&D_0026D0C8,
    (void*)&g_gaugeAmountCaption,
    (void*)&D_0026D5C8,
    (void*)&D_0026D848,
    (void*)&D_0026DAC8,
    (void*)&D_0026DD48,
    (void*)&D_0026DFC8,
    (void*)&g_gaugeBarElement,
    (void*)&D_0026E4E0,
    (void*)&g_timerElement,
    (void*)&g_timerCaption,
    (void*)&g_buttonHintElement,
    (void*)&D_0026EED0,
    (void*)&D_0026F138,
    (void*)&D_0026F5A0,
    (void*)&g_mapScreenList,
    (void*)&D_0026FA90,
    (void*)&D_0026FD00,
    (void*)&g_pauseMenuElement,
    (void*)&D_002708E0,
    (void*)&D_00271558,
    (void*)&D_00272430,
    (void*)&D_002726B0,
    (void*)&D_00272930,
    (void*)&D_00272B98,
    (void*)&g_stackedCaptionGroup,
    (void*)&D_002739F0,
    (void*)&D_00273C50,
    (void*)&D_00273EB0,
    (void*)&D_00274118,
    0,
};
extern const LevelEntry g_levelEntries[33] = {
    { 0x00000100, 77.0f, { 0xB4D572D8, 0xF825BBFB, 0xD81D7156, 0x397F5178, 0x728793AF, 0xB4DDCF33, 0xD81D73EC, 0xF8032CCB }, D_0024DCB0 },
    { 0x00000102, 60.0f, { 0x2D97B868, 0x3B2491E4, 0x149B5E84, 0xED6063AB, 0xEC614227, 0x2D9472EA, 0x149B5C3C, 0x3B063804 }, D_0024DCC8 },
    { 0x00000103, 139.0f, { 0x7EA0F65C, 0xD2337F06, 0xBE2AFC49, 0x12C36311, 0x7C279683, 0x7EA42098, 0xBE2AFEF0, 0xD22162E6 }, D_0024DCE8 },
    { 0x00000104, 90.0f, { 0x43450000, 0x1BA9F623, 0xD50CE115, 0x2C1200AF, 0xCEA641C8, 0x4356A7CF, 0xD50CE3A2, 0x1B896FC3 }, D_0024DD38 },
    { 0x00000105, 92.0f, { 0x99CE9B7C, 0x71906A24, 0xF0C28B06, 0xEB485F8B, 0x53B61FF1, 0x99DD5CC8, 0xF0C289B0, 0x71B1D014 }, D_0024DD60 },
    { 0x00000106, 0.0f, { 0x2699F11C, 0x49A028DA, 0x4F211F07, 0x48124182, 0x178D0C5F, 0x269A54DB, 0x4F211DBC, 0x4984311A }, D_0024DD80 },
    { 0x00000107, 70.0f, { 0x58F37394, 0x1350631B, 0x01CBDC91, 0x44F71ECF, 0xDF5726B9, 0x58F33959, 0x01CBDE2D, 0x1372669B }, D_0024DDA0 },
    { 0x00000200, 90.0f, { 0xD0F1FFA7, 0xC60FB906, 0xF6CBF1E8, 0xDBDFC7A2, 0x60C39D81, 0xD0F25069, 0xF6CBF340, 0xC62CF876 }, D_0024DDC8 },
    { 0x00000202, 135.0f, { 0x8D75C2BA, 0x1C60DBC3, 0x87B409B3, 0xE1C1EC55, 0x1628B119, 0x8D73AF2A, 0x87B40B1A, 0x1C4054D3 }, D_0024DDF0 },
    { 0x00000203, 80.0f, { 0xEFF2D448, 0xCD3CF9B6, 0x643C8676, 0xEE4BB37E, 0x5221084A, 0xEFFBDEE7, 0x643C84DA, 0xCD29D486 }, D_0024DD80 },
    { 0x00000204, 0.0f, { 0x085CFED8, 0x500DEAB1, 0x2D8244CE, 0x20D7E0BD, 0x7B9BF59A, 0x084F301B, 0x2D824663, 0x50119521 }, D_0024DE10 },
    { 0x00000205, 118.0f, { 0x34B8FDC0, 0xBA921EE9, 0xBC440B92, 0xF084CB5F, 0x9B5D7162, 0x34B8BB9E, 0xBC440938, 0xBAB16B39 }, D_0024DE38 },
    { 0x00000206, 77.0f, { 0x1C7E6EEE, 0x3905F736, 0x84C0AC66, 0xF3ECEA0D, 0xF49EA1A6, 0x1C7E59A4, 0x84C0AECD, 0x39225AD6 }, D_0024DCC8 },
    { 0x00000207, 83.0f, { 0x22F88C24, 0x981BED54, 0xBE8B1621, 0xC6B35547, 0x244B7E13, 0x22FEE53D, 0xBE8B148F, 0x98385A04 }, D_0024DE50 },
    { 0x00000300, 95.0f, { 0x255C8D9D, 0xC67DD187, 0xB30FF9E1, 0xC0220E2F, 0x42968B68, 0x25585E92, 0xB30FFB5C, 0xC6607257 }, D_0024DE70 },
    { 0x00000302, 122.0f, { 0x95E88262, 0x256551E6, 0x4ADF2CC3, 0x3DB989E3, 0xB6A6B35A, 0x95EB4CBA, 0x4ADF2E00, 0x2543D296 }, D_0024DE98 },
    { 0x00000303, 138.0f, { 0x11AF8222, 0x4154CCCF, 0x0079AF5D, 0xE4F21BF0, 0x4D1A9134, 0x11BB038E, 0x0079ADE2, 0x414910EF }, D_0024DEC0 },
    { 0x00000304, 0.0f, { 0x4E5C5D94, 0x9A873808, 0x96FFEFBF, 0x8BD43856, 0x4D5F0EF3, 0x4E53B0C4, 0x96FFED7E, 0x9A95DB18 }, D_0024DEF0 },
    { 0x00000305, 128.0f, { 0xF98CB02D, 0xA283FC15, 0x25BB5DC0, 0xE157D974, 0x79983E9E, 0xF989BEEC, 0x25BB5F02, 0xA29D9135 }, D_0024DF10 },
    { 0x00000306, 0.0f, { 0xCD08BB18, 0xE7BF9B3F, 0xC95EE322, 0xE910E326, 0x9644F239, 0xCD09B122, 0xC95EE1E2, 0xE799CE4F }, D_0024DF50 },
    { 0x00000307, 0.0f, { 0x675AB398, 0xCDC3F75B, 0x04221B83, 0x8816DEE1, 0xC808ED2E, 0x675C5565, 0x0422193D, 0xCDD7A0DB }, D_0024DF78 },
    { 0x00000400, 129.0f, { 0x690D68D5, 0x91BE10E9, 0x53BEE0CB, 0x2DD4C53B, 0x34B03761, 0x691EC614, 0x53BEE264, 0x91A1B799 }, D_0024DFA0 },
    { 0x00000402, 135.0f, { 0xCDE8339C, 0xA52C25B6, 0x7A1C3B47, 0x60EAC381, 0x5CCA62D2, 0xCDE6A0FA, 0x7A1C39F5, 0xA50AE286 }, D_0024DFB8 },
    { 0x00000403, 145.0f, { 0x2E641117, 0x48B11069, 0x55A7DCBF, 0xBEE1993E, 0x68804E34, 0x2E651ED2, 0x55A7DE0F, 0x4894DAA9 }, D_0024DFD8 },
    { 0x00000404, 165.0f, { 0x67AF3B57, 0xF492F4FB, 0x4582A324, 0x58A7E5D7, 0x19037D39, 0x67BCF0BB, 0x4582A197, 0xF48440DB }, D_0024DFF0 },
    { 0x00000405, 0.0f, { 0x39FDBB59, 0x61874FF5, 0x431AA733, 0x1BF9BD2A, 0xD8FC45CE, 0x39E904E7, 0x431AA586, 0x619A0B55 }, D_0024E018 },
    { 0x00000406, 162.0f, { 0x130F1A4B, 0xF165A43C, 0x1085A760, 0x7EF09D87, 0xEEDC6182, 0x130BC343, 0x1085A5D1, 0xF17A745C }, D_0024E038 },
    { 0x00000407, 0.0f, { 0xAEE1B3B0, 0x23F21A5C, 0x2C5069FC, 0x69DA4B36, 0x2EFC59A8, 0xAEE1800D, 0x2C506B48, 0x23E4C85C }, D_0024E060 },
    { 0x00000502, 0.0f, { 0xE03513A1, 0xDF69E228, 0xBCC1BC75, 0x66B59F20, 0x5603C88D, 0xE0251B60, 0xBCC1BED2, 0xDF776558 }, D_0024E088 },
    { 0x00000503, 0.0f, { 0x10003460, 0x2357C8AB, 0x82DF6820, 0x9EA4EEF0, 0x67FFDE84, 0x101449AA, 0x82DF6A86, 0x2348C7EB }, D_0024E0A8 },
    { 0x00000504, 0.0f, { 0xC0351F76, 0xAEA9D7A0, 0xA96A1A69, 0x5A238437, 0x525CDAB3, 0xC03D3461, 0xA96A18CA, 0xAE889780 }, D_0024E0C8 },
    { 0x00000505, 0.0f, { 0x166B5E9F, 0xD83C11E9, 0x64ED4809, 0x9F137E03, 0x544B9C1C, 0x167F901D, 0x64ED4AAC, 0xD82147F9 }, D_0024E0F8 },
    { 0x00000506, 0.0f, { 0x9CD62C23, 0x9AB39D3E, 0xEA6D2E63, 0xFEC5BF26, 0xC170A675, 0x9CD0481B, 0xEA6D2CC7, 0x9A96D39E }, D_0024E118 },
};
extern const Vec02 g_unitXVector = { 1.0f, 0.0f, 0.0f, 0.0f };
extern const Vec02 g_unitYVector = { 0.0f, 1.0f, 0.0f, 0.0f };
extern const Vec02 g_unitZVector = { 0.0f, 0.0f, 1.0f, 0.0f };
extern const Vec02 D_00248D30 = { 0.0f, 0.0f, 0.0f, 0.0f };
extern const f32 D_00248D40[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
extern const f32 D_00248D50[4] = { 3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f, 0.0f };
// Read only by func_001B8540, which is original assembly (16 bytes, then 16 no code reads).
extern const u32 D_00248D60[8] = { 0xFF7FFFFF, 0xFF7FFFFF, 0xFF7FFFFF, 0, 0x53DE6B03, 0xF1409707, 0x45DE6074, 0xD41837D9 };
// The file's .data.
u8 D_00250580[56] = { 0 };
// The descriptor of class 0x94, the last of D_00247448: two zero words.
ClassHead D_002505B8 = { 0, 0 };
// The method table file_1E88D0.cpp's objects take (c62.h), zero in the image.
void* D_002505C0[6] = { 0 };
