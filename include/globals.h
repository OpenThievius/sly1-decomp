// SPDX-License-Identifier: AGPL-3.0-or-later
// The globals many files read whose type is a class or a type of the existing headers: the
// world, the camera, the player, the constant vectors, the packet streams, the list heads.
// Written for this project from what retail's code does (build/swarm/st3/globals.tsv).
//
// One declaration each; a global defined in C stays defined where it is (the file named), and
// takes this type there. The records that have a type of their own are declared with it, in
// its header (g27c220.h, g262c70.h, g264a40.h, g275f80.h, ...). D_0027B314 is list_iter.h's and
// the ScreenElement objects (D_0026E248, D_002701F8, ...) are t217d.h's.
#ifndef GLOBALS_H
#define GLOBALS_H

#include "base_object.h"
#include "placed_object.h"
#include "switched_collider.h"
#include "step_sequence.h"
#include "world.h"
#include "camera.h"
#include "packet_writer.h"
#include "font.h"

// The world: 28 views in 15 files agree with class 0x6C (c6c.h), and every one of them reaches
// it through this pointer. world.cpp defines it (= 0).
extern World* g_currentWorld;

// The camera, class 0x6D (c6d.h): 22 views in 5 files. camera.cpp defines it (= 0).
extern Camera* g_camera;

// The player, an object of class 0x07 (c05.h): its views reach 0x2758..0x275C, inside the class's
// 0x2BF0 bytes and past the 0x720 of its parent 0x06; no class derives from 0x07
// (config/us/classes.tsv), and func_001D29C8 and func_001D31D0, which name it, are class 0x07's
// (methods.tsv). player.cpp defines it (= 0).
extern Player* g_player;

// An object of class 0x65 (c65.h) or none: func_001516C0 and func_00192A70 read its fields.
extern StepSequence* D_0027051C;

// The axes and the identity, in .rodata (global_tables.cpp defines them): read as
// whole vectors (lq) and as a matrix (three lq).
extern const Mat02 g_identityMatrix;  // the identity (rows 1 0 0 0, 0 1 0 0, 0 0 1 0)
extern const Vec02 g_unitXVector;  // 1 0 0 0
extern const Vec02 g_unitYVector;  // 0 1 0 0
extern const Vec02 g_unitZVector;  // 0 0 1 0
extern const Vec02 D_00248D30;  // 0 0 0 0

// The two packet streams (PacketWriter, packet_writer.h): 20 views of D_002622A8 in 6 files, 6 of D_00262280 in
// 4. Their objects are 0x24 and 0x28 bytes (the VIF writer ends with the count at 0x20, the GS
// writer, a GIF writer, with the entry count at 0x24): render_frame.cpp, which does not include
// this header, defines both at those sizes.
extern PacketWriter g_vifPacketWriter;
extern PacketWriter g_gsPacketWriter;

// The image records func_001B2BA8 and func_001B2CF8 allocate (func_0018D5C0: count * 0x18 and
// count * 0x20) and func_001690C0, func_00169780, func_001B2B50, func_001B2CA8 read: the 24- and
// 32-byte records of font.h. anim_record.cpp defines both pointers.
extern ImageRecord* g_imageRecordsA;
extern PaletteRecord* g_imageRecordsB;

// List heads (List01, c01.h), defined in render_frame.cpp (D_002626E8, D_002626F8 and D_00262708
// in target_lists.cpp, D_00264088 in player_state2.cpp): each label is 0xC bytes (D_00262300's and D_00264088's run to the next
// label with a word or a pad after them).
extern List01 D_002622E0;
extern List01 D_002622F0;
extern List01 g_deferredReleaseListC;
extern List01 g_targetCurveList;
extern List01 g_targetPointList;
extern List01 g_partList;       // its head is the first object of class 0x46 (Node_150298, Iter_16A820)
extern List01 g_pointObjects;
// A list head (func_00152438(D_00269BA8, 0x38) sets it up, point_graph.cpp defines it): 0xC
// bytes like every other; its label runs to D_00269BC0 because switched_collider.cpp's .data
// starts there, after the linker's padding.
struct List_269BA8 {
    List01 list;            // 0x00
};
extern List_269BA8 g_targetVectors;

#endif
