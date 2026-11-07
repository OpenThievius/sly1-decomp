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
// it through this pointer. 001E4000.cpp defines it (= 0).
extern World* D_00275710;

// The camera, class 0x6D (c6d.h): 22 views in 5 files. camera.cpp defines it (= 0).
extern Camera* D_00261990;

// The player, an object of class 0x07 (c05.h): its views reach 0x2758..0x275C, inside the class's
// 0x2BF0 bytes and past the 0x720 of its parent 0x06; no class derives from 0x07
// (config/us/classes.tsv), and func_001D29C8 and func_001D31D0, which name it, are class 0x07's
// (methods.tsv). 001E4000.cpp defines it (= 0).
extern Player* D_00262E10;

// An object of class 0x65 (c65.h) or none: func_001516C0 and func_00192A70 read its fields.
extern StepSequence* D_0027051C;

// The axes and the identity, in .rodata (001E4000.cpp defines all but D_00248D30): read as
// whole vectors (lq) and as a matrix (three lq).
extern const Mat02 D_002483D0;  // the identity (rows 1 0 0 0, 0 1 0 0, 0 0 1 0)
extern const Vec02 D_00248D00;  // 1 0 0 0
extern const Vec02 D_00248D10;  // 0 1 0 0
extern const Vec02 D_00248D20;  // 0 0 1 0
extern const Vec02 D_00248D30;  // 0 0 0 0

// The two packet streams (PacketWriter, packet_writer.h): 20 views of D_002622A8 in 6 files, 6 of D_00262280 in
// 4. Their labels are 0x24 and 0x28 bytes: the stream's last words are not used here. Both are
// zeros in file_1549C8.cpp's .data, included there from the disassembly.
extern PacketWriter D_002622A8;
extern PacketWriter D_00262280;

// The image records func_001B2BA8 and func_001B2CF8 allocate (func_0018D5C0: count * 0x18 and
// count * 0x20) and func_001690C0, func_00169780, func_001B2B50, func_001B2CA8 read: the 24- and
// 32-byte records of font.h. 001E4000.cpp defines both pointers.
extern ImageRecord* D_00274504;
extern PaletteRecord* D_0027450C;

// List heads (List01, c01.h), defined in file_1549C8.cpp (D_002626E8, D_002626F8 and D_00262708
// in file_167D68.cpp, D_00264088 in file_17D248.cpp): each label is 0xC bytes (D_00262300's and D_00264088's run to the next
// label with a word or a pad after them).
extern List01 D_002622E0;
extern List01 D_002622F0;
extern List01 D_00262300;
extern List01 D_002626E8;
extern List01 D_002626F8;
extern List01 D_00262708;       // its head is the first object of class 0x46 (Node_150298, Iter_16A820)
extern List01 D_00264088;
// A list head (func_00152438(D_00269BA8, 0x38) sets it up, file_18F988.cpp defines it): its
// label runs 0x18 bytes, to D_00269BC0, of which the list functions use the first 0xC.
struct List_269BA8 {
    List01 list;            // 0x00
    u8 pad0C[0x18 - 0xC];
};
extern List_269BA8 D_00269BA8;

#endif
