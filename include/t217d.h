// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind t217d: the static screen elements of the game's on-screen interface (a message line, a
// timer, a gauge, a caption): 37 objects in .data (D_0026C6C8 ... D_00274118, listed by
// D_002486B0), each with a 20-slot table of functions (D_00217E30 ... D_00221380).
// func_001A9C68 installs the tables and calls slot 0 on each; the frame code calls slot 5 (reset),
// slot 9 (draw), and slots 14 and 15 (show, hide) from many files. Written for this project from
// what retail's code does (config/us/tables.tsv, dispatch.tsv).
//
// T217D is the base: the fields the generic slots (func_001AA1F0 ... func_001AAF58) use, up to
// 0x260; the derived elements add their own from 0x260 on (T217D_XXX, XXX the last three hex
// digits of the table). Fields are named for what the code does with them; a later step may
// rename them. The globals' sizes are not known (the labels in .data are 0x23C to 0x298 apart,
// and some labels sit inside an object): no sizeof check is made for the variants.
#ifndef T217D_H
#define T217D_H

#include "common.h"

struct V24A2;   // the font (include/v24a2.h): a game object with a GCC vtable at +0x4C

// A four-byte word that may sit at any address: copying one is a pair of unaligned loads.
struct __attribute__((packed)) T217D_Word { s32 v; };
// A colour as four bytes (red, green, blue, alpha), copied as a whole.
struct T217D_Rgba { u8 c[4]; };

// Where an element goes: one 20-byte record of D_0026C3E0 per element, in the order of
// D_002486B0 (func_001AAB60 reads them, func_001AA1F0 picks the element's).
struct T217D_Place {
    f32 dx;         // 0x00: distance from the edge (0 centred, > 0 from the left or top, < 0 from the right or bottom)
    f32 dy;         // 0x04
    s32 from;       // 0x08: the side the element slides in from (0 left, 1 right, 2 top, 3 bottom)
    s32 anchor;     // 0x0C: the index of the element it is placed against, -1 for the screen
    s32 relation;   // 0x10: which side of that element (0 .. 3), -1 for none
};

typedef char check_T217D_Place[sizeof(T217D_Place) == 20 ? 1 : -1];   // func_001AA1F0 steps 20 bytes

struct T217D;

// The 20 slots. Those the base fills are the generic ones; the derived tables replace
// slots 0, 1, 2, 8, 9, 14, 15, 16 and so on with their own.
struct T217D_Vt {
    void (*m00)(T217D* self, s32 index);        // 0x00: init (func_001AA1F0)
    void (*m01)(T217D* self);                   // 0x04: set up (func_001AA268 in the base)
    void (*m02)(T217D* self);                   // 0x08: update the slide (func_001AA298)
    void (*m03)(T217D* self);                   // 0x0C: not used by these files
    void (*m04)(T217D* self);                   // 0x10: not used by these files
    void (*m05)(T217D* self);                   // 0x14: reset, m16(self, 0) (func_001AA8C8)
    void (*m06)(T217D* self);                   // 0x18: not used by these files
    void (*m07)(T217D* self);                   // 0x1C: not used by these files
    void (*m08)(T217D* self, const char* text); // 0x20: set the text (func_001AA4F0)
    void (*m09)(T217D* self);                   // 0x24: draw (func_001AA790)
    void (*m10)(T217D* self);                   // 0x28: not used by these files
    f32 (*m11)(T217D* self);                    // 0x2C: seconds to slide in
    f32 (*m12)(T217D* self);                    // 0x30: seconds to stay, 0 for always
    f32 (*m13)(T217D* self);                    // 0x34: seconds to slide out
    void (*m14)(T217D* self);                   // 0x38: show (func_001AA8F0)
    void (*m15)(T217D* self);                   // 0x3C: hide (func_001AA958)
    void (*m16)(T217D* self, s32 mode);         // 0x40: go to a mode (func_001AA998)
    void (*m17)(T217D* self, f32* clock);       // 0x44: use another clock (func_001AAF58)
    s32 (*m18)(T217D* self, T217D* other);      // 0x48: both on screen together (func_001AAAC8)
    void (*m19)(T217D* self);                   // 0x4C: unused, 0 in every table
};

// The base element, 0x260 bytes (the four sub-elements of D_00218720's object are this big).
struct T217D {
    const T217D_Vt* vt;         // 0x00
    V24A2* font;                // 0x04: the font object (func_0015C1C0) the text is drawn with
    char text[0x200];           // 0x08: the text; its first byte is the element's visible flag
    union {
        u32 color;              // 0x208: 0xFF808080 is "no tint"; the alpha is the top byte
        T217D_Word colorWord;   // 0x208
        T217D_Rgba rgba;        // 0x208
    };
    f32 scale;                  // 0x20C: text size
    V24A2** frame;              // 0x210: a cell holding the object drawn behind the text, or 0
    s32 index;                  // 0x214: position in D_002486B0
    T217D_Place* place;         // 0x218: its record of D_0026C3E0
    f32 x;                      // 0x21C: where it is now
    f32 y;                      // 0x220
    f32 shownX;                 // 0x224: where it rests when shown
    f32 shownY;                 // 0x228
    f32 hiddenX;                // 0x22C: where it is when hidden (off the screen)
    f32 hiddenY;                // 0x230
    f32 w;                      // 0x234: size
    f32 h;                      // 0x238
    f32 blend;                  // 0x23C: 0 hidden to 1 shown
    f32 inTime;                 // 0x240: seconds to slide in (slot 11)
    f32 holdTime;               // 0x244: seconds to stay (slot 12), 0 for always
    f32 outTime;                // 0x248: seconds to slide out (slot 13)
    f32 offset;                 // 0x24C: how far into the slide it was when the mode began
    s32 mode;                   // 0x250: 0 hidden, 1 sliding in, 2 shown, 3 sliding out
    f32 since;                  // 0x254: the clock when the mode began
    f32* clock;                 // 0x258: the clock it reads (D_00261868 by default)
    u8 pad25C[0x260 - 0x25C];
};

// The sixteen plain captions (D_00217E30 ... D_00218290, one table shape): a text that follows
// a counter in the game's state, f214 telling which one (func_001AB2B8), and counts to it.
struct T217D_E30 : T217D {
    s32 shown;                  // 0x260: the value on the display, -1 before the first update
    s32* target;                // 0x264: the counter it follows
    s32* limit;                 // 0x268: a second counter (the "of" in "3/5")
    f32 rate;                   // 0x26C: counts per second (6000.0 at the start)
    f32 fraction;               // 0x270: the part of a count not yet taken
    void (*onDone)(void* arg);  // 0x274: called once when it reaches the counter
    void* doneArg;              // 0x278
};

struct T217D_510;
typedef void (*T217D_510_Fn)(T217D_510* self, s32 arg);

// The timer (D_00218510): counts up or down and shows minutes and seconds.
struct T217D_510 : T217D {
    s32 state;                  // 0x260: 0 off, 1 waiting, 2 counting (func_001ABE20)
    f32 stateSince;             // 0x264: the clock when the state began
    f32 time;                   // 0x268: seconds on the timer
    f32 rate;                   // 0x26C: seconds per second, negative to count down
    s32 lastSecond;             // 0x270
    s32 lastTenth;              // 0x274
    f32 warnAt;                 // 0x278: the time to warn at, FLT_MAX for none
    T217D_Word warnColor;       // 0x27C: the colour shown once warned
    T217D_510_Fn onWarn;        // 0x280
    s32 warned;                 // 0x284
    f32 limit;                  // 0x288: the time it stops at
    T217D_510_Fn onEnd;         // 0x28C
    s32 f290;                   // 0x290: set by func_001AB600 and func_001AB958, 0 by func_001AB890
};

void func_001ABE20(T217D_510* self, s32 state);

// The gauge (D_002182E0): a filled bar that follows a value and flashes a letter.
struct T217D_2E0 : T217D {
    u8 pad260[0x26C - 0x260];
    u8 letter;                  // 0x26C: the glyph to show, from 'r'
    u8 pad26D[0x274 - 0x26D];
    f32 fill;                   // 0x274: the filled part of the bar
    f32 fillTarget;             // 0x278
    f32 changedAt;              // 0x27C: the clock when the value last changed, 0 for never
    f32 barX;                   // 0x280: the bar's place inside the element
    f32 barY;                   // 0x284
    f32 barW;                   // 0x288
    f32 barH;                   // 0x28C
    f32 letterX;                // 0x290
    f32 letterY;                // 0x294
};

// D_00218330: the base without any field of its own.
struct T217D_330 : T217D {
};

// A caption that can be told a new text while it is on screen (D_00218380): the new one waits
// in f264 until the element has slid out.
struct T217D_380 : T217D {
    s32 pending;                // 0x260: a new text waits
    const char* pendingText;    // 0x264
};

// The same with the text copied (D_002183D0).
struct T217D_3D0 : T217D {
    s32 pending;                // 0x260
    char pendingText[0x200];    // 0x264
    s32 announce;               // 0x464: 1 while the announcement is shown in the middle
};

// D_00218420.
struct T217D_420 : T217D {
    s32 flag;                   // 0x260
};

// D_00218470: an element with an icon table.
struct T217D_470 : T217D {
    void* icon;                 // 0x260: the icon's record (func_001B4688), or 0
};

// D_002184C0.
struct T217D_4C0 : T217D {
    s32 flagA;                  // 0x260
    s32 flagB;                  // 0x264
    s32 pending;                // 0x268
};

// D_00218560 and D_002185B0 have no field of their own.
struct T217D_560 : T217D {
};

struct T217D_5B0 : T217D {
};

// D_00218600.
struct T217D_600 : T217D {
    s32 flag;                   // 0x260
};

// The base's functions (src/main/001A8000.cpp).
void func_001AA1F0(T217D* self, s32 index);
void func_001AA268(T217D* self);
void func_001AA298(T217D* self);
void func_001AA4F0(T217D* self, const char* text);
void func_001AA788(T217D* self, f32 scale);
void func_001AA790(T217D* self);
f32 func_001AA898(T217D* self);
f32 func_001AA8A0(T217D* self);
f32 func_001AA8A8(T217D* self);
void func_001AA8B0(T217D* self, f32 seconds);
void func_001AA8B8(T217D* self, f32 seconds);
void func_001AA8C0(T217D* self, f32 seconds);
void func_001AA8C8(T217D* self);
void func_001AA8F0(T217D* self);
void func_001AA958(T217D* self);
void func_001AA998(T217D* self, s32 mode);
s32 func_001AAAC8(T217D* self, T217D* other);
void func_001AAB20(T217D* self, f32 w, f32 h);
void func_001AAB60(T217D* self);
void func_001AAEC0(T217D* changed);
void func_001AAF58(T217D* self, f32* clock);

// The 37 objects, in .data (D_002486B0 lists them in this order). Each is of the variant of
// its table; those whose variant is not written yet (wave 2) are declared as the base.
extern T217D_E30 D_0026C6C8;    // D_00217E30
extern T217D_E30 D_0026C948;    // D_00217E80
extern T217D_E30 D_0026CBC8;    // D_00217ED0
extern T217D_E30 D_0026CE48;    // D_00217F20
extern T217D_E30 D_0026D0C8;    // D_00217F70
extern T217D_E30 D_0026D348;    // D_00217FC0
extern T217D_E30 D_0026D5C8;    // D_002180B0
extern T217D_E30 D_0026D848;    // D_00218010
extern T217D_E30 D_0026DAC8;    // D_00218060
extern T217D_E30 D_0026DD48;    // D_00218100
extern T217D_E30 D_0026DFC8;    // D_00218150
extern T217D_2E0 D_0026E248;    // D_002182E0
extern T217D_E30 D_0026E4E0;    // D_002181A0
extern T217D_510 D_0026E760;    // D_00218510
extern T217D D_0026E9F8;        // D_00221380
extern T217D_330 D_0026EC70;    // D_00218330
extern T217D_380 D_0026EED0;    // D_00218380
extern T217D_3D0 D_0026F138;    // D_002183D0
extern T217D_420 D_0026F5A0;    // D_00218420
extern T217D D_0026F808;        // D_002210F0
extern T217D D_0026FA90;        // D_002212E0
extern T217D D_0026FD00;        // D_00221330
extern T217D D_0026FF68;        // D_002186D0
extern T217D D_002701F8;        // D_0021A440
extern T217D D_00270650;        // D_00220BF0
extern T217D D_002708E0;        // D_0021A3F0
extern T217D D_00271558;        // D_0021A3F0
extern T217D_E30 D_00272430;    // D_00218240
extern T217D_E30 D_002726B0;    // D_00218290
extern T217D_470 D_00272930;    // D_00218470
extern T217D_4C0 D_00272B98;    // D_002184C0
extern T217D_560 D_002721D0;    // D_00218560
extern T217D D_00272E08;        // D_00218720
extern T217D_5B0 D_002739F0;    // D_002185B0
extern T217D_5B0 D_00273C50;    // D_002185B0
extern T217D_600 D_00273EB0;    // D_00218600
extern T217D_E30 D_00274118;    // D_002181F0

// The base is the stride of D_00218720's four sub-elements (func_0014ABD0 steps 0x260 bytes).
typedef char check_T217D[sizeof(T217D) == 0x260 ? 1 : -1];
typedef char check_T217D_330[sizeof(T217D_330) == 0x260 ? 1 : -1];

#endif
