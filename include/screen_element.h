// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind t217d: the static screen elements of the game's on-screen interface (a message line, a
// timer, a gauge, a caption): 37 objects in .data (D_0026C6C8 ... D_00274118, listed by
// D_002486B0), each with a 20-slot table of functions (D_00217E30 ... D_00221380).
// func_001A9C68 installs the tables and calls slot 0 on each; the frame code calls slot 5 (reset),
// slot 9 (draw), and slots 14 and 15 (show, hide) from many files. Written for this project from
// what retail's code does (config/us/tables.tsv, dispatch.tsv).
//
// ScreenElement is the base: the fields the generic slots (func_001AA1F0 ... func_001AAF58) use, up to
// 0x260; the derived elements add their own from 0x260 on (T217D_XXX, XXX the last three hex
// digits of the table). Fields are named for what the code does with them; a later step may
// rename them. The globals' sizes are not known (the labels in .data are 0x23C to 0x298 apart,
// and some labels sit inside an object): no sizeof check is made for the variants.
// Three tables of the later segment end in the same three digits as one of the first
// (D_002212E0 and D_002182E0, D_00221330 and D_00218330, D_00221380 and D_00218380): their
// variants take four digits (T217D_12E0, T217D_1330, T217D_1380).
#ifndef SCREEN_ELEMENT_H
#define SCREEN_ELEMENT_H

#include "common.h"

struct Font;       // the font (include/font.h): a game object with a GCC vtable at +0x4C
struct WarpPage;    // a warp page, class 0x67 (include/warp_page.h)
struct PadRecord;   // the pad's state (include/pad_record.h)

// A four-byte word that may sit at any address: copying one is a pair of unaligned loads.
struct __attribute__((packed)) T217D_Word { s32 v; };
// A float that may sit at any address: storing one is a pair of unaligned stores (swl, swr).
struct __attribute__((packed)) T217D_Float { f32 v; };
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

// D_0026C3E0: the 37 elements' places and a word after them.
struct ElementPlaceTable {
    T217D_Place e[37];
    s32 end;
};

struct ScreenElement;
struct StepSequence;    // include/step_sequence.h

// The 20 slots. Those the base fills are the generic ones; the derived tables replace
// slots 0, 1, 2, 8, 9, 14, 15, 16 and so on with their own.
struct T217D_Vt {
    void (*m00)(ScreenElement* self, s32 index);        // 0x00: init (func_001AA1F0)
    void (*m01)(ScreenElement* self);                   // 0x04: set up (func_001AA268 in the base)
    void (*m02)(ScreenElement* self);                   // 0x08: update the slide (func_001AA298)
    void (*m03)(ScreenElement* self, s32 top);          // 0x0C: told it is (1) or is no longer (0) the top of a stack (func_001E9498)
    void (*m04)(ScreenElement* self, PadRecord* pad);   // 0x10: handle the pad as the top of the stack (func_001E9108)
    void (*m05)(ScreenElement* self);                   // 0x14: reset, m16(self, 0) (func_001AA8C8)
    void (*m06)(ScreenElement* self);                   // 0x18: not used by these files
    void (*m07)(ScreenElement* self);                   // 0x1C: not used by these files
    void (*m08)(ScreenElement* self, const char* text); // 0x20: set the text (func_001AA4F0)
    void (*m09)(ScreenElement* self);                   // 0x24: draw (func_001AA790)
    void (*m10)(ScreenElement* self);                   // 0x28: not used by these files
    f32 (*m11)(ScreenElement* self);                    // 0x2C: seconds to slide in
    f32 (*m12)(ScreenElement* self);                    // 0x30: seconds to stay, 0 for always
    f32 (*m13)(ScreenElement* self);                    // 0x34: seconds to slide out
    void (*m14)(ScreenElement* self);                   // 0x38: show (func_001AA8F0)
    void (*m15)(ScreenElement* self);                   // 0x3C: hide (func_001AA958)
    void (*m16)(ScreenElement* self, s32 mode);         // 0x40: go to a mode (func_001AA998)
    void (*m17)(ScreenElement* self, f32* clock);       // 0x44: use another clock (func_001AAF58)
    s32 (*m18)(ScreenElement* self, ScreenElement* other);      // 0x48: both on screen together (func_001AAAC8)
    void (*m19)(ScreenElement* self);                   // 0x4C: unused, 0 in every table
};

// The types of the table's slots, to define a table with.
typedef void (*ElementFn)(ScreenElement* self);
typedef void (*ElementIntFn)(ScreenElement* self, s32 value);
typedef void (*ElementPadFn)(ScreenElement* self, PadRecord* pad);
typedef void (*ElementTextFn)(ScreenElement* self, const char* text);
typedef f32 (*ElementTimeFn)(ScreenElement* self);
typedef void (*ElementClockFn)(ScreenElement* self, f32* clock);
typedef s32 (*ElementPairFn)(ScreenElement* self, ScreenElement* other);

// The base element, 0x260 bytes (the four sub-elements of D_00218720's object are this big).
struct ScreenElement {
    const T217D_Vt* vt;         // 0x00
    Font* font;                // 0x04: the font object (func_0015C1C0) the text is drawn with
    char text[0x200];           // 0x08: the text; its first byte is the element's visible flag
    union {
        u32 color;              // 0x208: 0xFF808080 is "no tint"; the alpha is the top byte
        T217D_Word colorWord;   // 0x208
        T217D_Rgba rgba;        // 0x208
    };
    f32 scale;                  // 0x20C: text size
    Font** frame;              // 0x210: a cell holding the object drawn behind the text, or 0
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
    s32 open;                   // 0x25C: 1 while the menu screen is open (the menus' show and hide set it; the other elements leave it 0)
};

// The sixteen plain captions (D_00217E30 ... D_00218290, one table shape): a text that follows
// a counter in the game's state, f214 telling which one (func_001AB2B8), and counts to it.
struct T217D_E30 : ScreenElement {
    s32 shown;                  // 0x260: the value on the display, -1 before the first update
    s32* target;                // 0x264: the counter it follows
    s32* limit;                 // 0x268: a second counter (the "of" in "3/5")
    f32 rate;                   // 0x26C: counts per second (6000.0 at the start)
    f32 fraction;               // 0x270: the part of a count not yet taken
    void (*onDone)(void* arg);  // 0x274: called once when it reaches the counter
    void* doneArg;              // 0x278
    s32 own;                    // 0x27C: D_00274118 only: a count of its own that `target` points at (func_001943E8)
};

struct T217D_510;
typedef void (*T217D_510_Fn)(T217D_510* self, s32 arg);

// The timer (D_00218510): counts up or down and shows minutes and seconds.
struct T217D_510 : ScreenElement {
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

void SetTimerState(T217D_510* self, s32 state);

// The gauge (D_002182E0): a filled bar that follows a value and flashes a letter.
struct T217D_2E0 : ScreenElement {
    s32 f260;               // 0x260: copied into f26C when a gauge mode starts (func_0017B410)
    s32 f264;               // 0x264: copied into f270 then
    s32 f268;               // 0x268
    union {
        u8 letter;          // 0x26C: the glyph to show, from 'r'
        s32 f26C;           // 0x26C: counted down by func_001AC060
    };
    s32 f270;               // 0x270
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
struct T217D_330 : ScreenElement {
};

// A caption that can be told a new text while it is on screen (D_00218380): the new one waits
// in f264 until the element has slid out.
struct T217D_380 : ScreenElement {
    s32 pending;                // 0x260: a new text waits
    const char* pendingText;    // 0x264
};

// The same with the text copied (D_002183D0).
struct T217D_3D0 : ScreenElement {
    s32 pending;                // 0x260
    char pendingText[0x200];    // 0x264
    s32 announce;               // 0x464: 1 while the announcement is shown in the middle
};

// D_00218420.
struct T217D_420 : ScreenElement {
    union {
        s32 flag;               // 0x260: nonzero, the element shows (func_001AD718)
        StepSequence* owner;    // 0x260: the step sequence in state 5 that shows it (func_00150790)
    };
};

// D_00218470: an element with an icon table.
struct T217D_470 : ScreenElement {
    void* icon;                 // 0x260: the icon's record (func_001B4688), or 0
};

// D_002184C0.
struct T217D_4C0 : ScreenElement {
    s32 flagA;                  // 0x260
    s32 flagB;                  // 0x264
    s32 pending;                // 0x268
};

// D_00218560 and D_002185B0 have no field of their own.
struct T217D_560 : ScreenElement {
};

struct T217D_5B0 : ScreenElement {
};

// D_00218600.
struct T217D_600 : ScreenElement {
    s32 flag;                   // 0x260
};

// One of the 57 points on the outline of D_0021A3F0's sparkle (a circle of 57 vertices, 1 / 57 apart
// in y): its place, the next vertex's place, two colours and the brightness animation.
struct T217D_3F0_Pt {
    f32 x;                      // 0x00: the vertex (func_001E5E70: sign * sqrt(1 - y * y))
    f32 nextX;                  // 0x04: the next vertex's x (the last one's is 0)
    f32 y;                      // 0x08: i / 57 * 2 - 1
    f32 nextY;                  // 0x0C: the next vertex's y (the last one's is 1)
    u32 colorA;                 // 0x10: 0x30808080 or 0x30000000, by the parity of i
    u32 colorB;                 // 0x14
    f32 level;                  // 0x18: brightness, eased toward `target` (func_001E77C0)
    f32 target;                 // 0x1C
    f32 rateA;                  // 0x20: three random speeds
    f32 rateB;                  // 0x24
    f32 rateC;                  // 0x28
};

typedef char check_T217D_3F0_Pt[sizeof(T217D_3F0_Pt) == 0x2C ? 1 : -1];   // func_001E5E70 steps 0x2C bytes

// The sparkle round a held item (D_0021A3F0, two objects: D_002708E0 and D_00271558).
struct T217D_3F0 : ScreenElement {
    s32 fade;                   // 0x260: 0 fading in, 1 fading out (func_001E6C20, func_001E7440)
    f32 fadeSince;              // 0x264: the clock when `fade` was set
    s32 phase;                  // 0x268: 0 growing, 1 full, 2 shrinking, 3 gone (func_001E7518, func_001E77C0)
    f32 phaseSince;             // 0x26C
    void* target;               // 0x270: the object it follows (func_001E86E0 sets it; 0 for none)
    void* current;              // 0x274: the one it has taken hold of (func_001E7460)
    void* special;              // 0x278: the one whose flag 0x100000000 it set (func_001E87F0)
    void* sprite;               // 0x27C: the effect func_001E6188 creates (func_0011E580)
    T217D_3F0_Pt pts[57];       // 0x280
    f32 edgeFrom;               // 0xC4C
    f32 edgeTo;                 // 0xC50
    f32 lineLen;                // 0xC54
    f32 lineLen2;               // 0xC58
    f32 pulse;                  // 0xC5C: eased toward `pulseTarget` (func_001E77C0)
    f32 pulseTarget;            // 0xC60
    f32 pulseA;                 // 0xC64: the three speeds of the easing
    f32 pulseB;                 // 0xC68
    f32 pulseC;                 // 0xC6C
    f32 size;                   // 0xC70: 0 to 1, how much of the outline is drawn (func_001E6268)
};

// A slot of the glyph bank D_0021A440 keeps at its end: a handle and one more word.
struct T217D_440_Slot {
    void* handle;               // 0x00: what func_0019EBE8 / func_001A1DF0 take
    s32 extra;                  // 0x04
};

// The caption box of the dialogue and tutorial screens (D_0021A440, D_002701F8): it types its text
// out, keeps a state of its own (0 off ... 5), and follows a game object (`child`).
struct T217D_440 : ScreenElement {
    s32 state;                  // 0x260: 0 off, 1 .. 4 the kinds of box, 5 (func_001356C0 sets it, func_00136408 tests 4)
    f32 stateSince;             // 0x264: the clock when `state` was set
    f32 textSince;              // 0x268: the clock when the text was set (func_00136408; the typing starts here)
    s32 lineCount;              // 0x26C: line breaks found in the text
    s32 lineBreaks[16];         // 0x270: the character index of each
    u8 pad2B0[0x2F0 - 0x2B0];
    f32 charsPerSecond;         // 0x2F0: 15.0 (func_001310F0), the typing speed (func_00136530)
    u32 highlight;              // 0x2F4: 0x80FFFFFF (func_001310F0)
    u8 f2F8;                // 0x2F8
    u8 pad2F9[0x2FC - 0x2F9];
    s32 f2FC;                   // 0x2FC: set by func_001365A0
    f32 value;                  // 0x300: 0 to 1 (func_001365A8: a percent / 100)
    f32 stickX;                 // 0x304: the smoothed pad direction (func_00136040)
    f32 stickY;                 // 0x308
    f32 spin;                   // 0x30C: moves by the pad's stick (func_00132500)
    Font* smallFont;            // 0x310: a copy of the font at 0.7 by 0.8 (SetupTextPanel)
    f32 f314;                   // 0x314
    void* bands;                // 0x318: the GS packet of the bands behind the panel (SetupTextPanel)
    s32 bandsSize;              // 0x31C
    s32 palette;                // 0x320: 0 .. 2, the colour pair func_00132500 picks
    void* child;                // 0x324: the game object the box follows (its kind at +0x2D0, its state at +0x2D4)
    s32 bankState;              // 0x328: which glyph bank is loaded (func_00135E78), 1 lists the two counters (func_00135F48)
    s32 savedBank;              // 0x32C: the bank to come back to (func_00136238)
    s32 blockA[4];              // 0x330: func_00135E78 clears 0x10 bytes here and at 0x340
    f32 blockB[4];              // 0x340
    s32 countA;                 // 0x350
    s32 count;                  // 0x354: the entries below
    u8 pad358[0x35C - 0x358];
    T217D_440_Slot entries[31]; // 0x35C: `count` of them; 31 fill the object to D_00270650 (0x458 bytes)
};

// The pause menu (D_002186D0, D_0026FF68): three layers each ask for a screen, the lowest answer
// shown (func_00194D30); it slides in and out like the other elements.
struct T217D_6D0 : ScreenElement {
    s32 page;                   // 0x260: the screen on view, -1 for none (func_00193E58 starts it at -1)
    s32 cursor;                 // 0x264: the highlighted row of that screen
    s32 want[3];                // 0x268: the screen each of the three layers asks for, -1 for none
    s32 queued;                 // 0x274: 1 while a screen waits for the slide out to finish
    s32 queuedPage;             // 0x278: that screen
    s32 stage;                  // 0x27C: -1 at the start; 2 and 0xB are set by the buttons (func_00195958)
    s32 f280;                   // 0x280: set by func_001DDB20, cleared by func_00195958
    f32 fade;                   // 0x284: the alpha of the captions drawn over it, 1.0 at the start
    s32 sound;                  // 0x288: the sound handle func_001BE980 gave, 0 for none
};

// The map screen's list (D_002210F0, D_0026F808): it holds the objects of kind 0x67 by slot.
struct T217D_0F0 : ScreenElement {
    WarpPage* current;          // 0x260: the object it shows
    WarpPage* nodes[6];         // 0x264: the warp pages, by their slot (StartWarpPage enters them)
    f32 scale;                  // 0x27C: eased toward `scaleTarget` (func_001F1A08)
    f32 scaleTarget;            // 0x280
};

// D_002212E0 (D_0026FA90): a caption that opens an object's screen.
struct T217D_12E0 : ScreenElement {
    void* node;                 // 0x260: the object it shows (its mode at +0x2D0)
    s32 sound;                  // 0x264: the sound handle func_001BE980 gave, 0 for none
    f32 lastAt;                 // 0x268: the clock of the last time it spoke; -D_00262970 at the start, so the first test passes
};

// D_00221330 (D_0026FD00).
struct T217D_1330 : ScreenElement {
    s32 cursor;                 // 0x260: the chosen one of 16 (4 by 4, func_0016BBA8); func_0016BDD0 starts it at the highest bit set in the game state's word at +0x19F4
};

// D_00221380 (D_0026E9F8): the caption of the timed sprint.
struct T217D_1380 : ScreenElement {
    s32 state;                  // 0x260: 0 off, 1, 2 the sprint on, 3 (func_001E02C8)
    f32 stateSince;             // 0x264: the clock when `state` was set
    s32 active;                 // 0x268: state != 0
    s32 pressed;                // 0x26C: 1 while "Press L for Bonus Commentary" is up (func_001DFEB8)
    s32 f270;                   // 0x270: cleared by func_001DFEB8
};

// D_00220BF0 (D_00270650).
struct T217D_BF0 : ScreenElement {
    f32 rateX;                  // 0x260: the aim's speeds, eased to the stick (func_00181ED0)
    f32 rateY;                  // 0x264
    u8 pad268[0x270 - 0x268];
    f32 aim[4];                 // 0x270: the aim, x and y in -1..1, and the zoom (func_00181ED0); the sprite's place as a fraction of the screen (func_001821B0)
    void* target;               // 0x280: the class 0x75 object the aim chose last (func_00181ED0)
    s32 icon;                   // 0x284: func_001B4688(0x36A) (func_00180F98)
    f32 f288;                   // 0x288: 0.0 at the start, stored through T217D_Float (func_001793F0, func_00180F98)
};

// D_00218720 (D_00272E08): four sub-elements of the same kind (D_00218330) stacked, drawn together.
struct T217D_720 : ScreenElement {
    s32 count;                  // 0x260: how many of `items` are in use (func_0014ADE0)
    T217D_330 items[4];         // 0x264: 0x260 bytes each (func_0014ABD0)
};

// The base's functions (src/main/file_1A7FE8.cpp and screen_element.cpp).
void InitScreenElement(ScreenElement* self, s32 index);
void SetupScreenElementText(ScreenElement* self);
void UpdateScreenElementSlide(ScreenElement* self);
void SetScreenElementText(ScreenElement* self, const char* text);
void SetScreenElementScale(ScreenElement* self, f32 scale);
void DrawScreenElementText(ScreenElement* self);
f32 GetScreenElementSlideInTime(ScreenElement* self);
f32 GetScreenElementHoldTime(ScreenElement* self);
f32 GetScreenElementSlideOutTime(ScreenElement* self);
void SetScreenElementSlideInTime(ScreenElement* self, f32 seconds);
void SetScreenElementHoldTime(ScreenElement* self, f32 seconds);
void SetScreenElementSlideOutTime(ScreenElement* self, f32 seconds);
void ResetScreenElement(ScreenElement* self);
void ShowScreenElement(ScreenElement* self);
void HideScreenElement(ScreenElement* self);
void SetScreenElementMode(ScreenElement* self, s32 mode);
s32 AreScreenElementsTogether(ScreenElement* self, ScreenElement* other);
void SetScreenElementSize(ScreenElement* self, f32 w, f32 h);
void PlaceScreenElement(ScreenElement* self);
void PlaceAnchoredScreenElements(ScreenElement* changed);
void SetScreenElementClock(ScreenElement* self, f32* clock);

// The 37 objects, in .data in address order (GCC writes uninitialised globals in the order
// they are first declared; D_002486B0 lists them in its own order). Each is of the variant of
// its table (D_0026EC70 and the four sub-elements of D_00272E08 have the base's table D_00218330).
extern T217D_E30 D_0026C6C8;    // D_00217E30
extern T217D_E30 D_0026C948;    // D_00217E80
extern T217D_E30 D_0026CBC8;    // D_00217ED0
extern T217D_E30 D_0026CE48;    // D_00217F20
extern T217D_E30 D_0026D0C8;    // D_00217F70
extern T217D_E30 g_gaugeAmountCaption;    // D_00217FC0
extern T217D_E30 D_0026D5C8;    // D_002180B0
extern T217D_E30 D_0026D848;    // D_00218010
extern T217D_E30 D_0026DAC8;    // D_00218060
extern T217D_E30 D_0026DD48;    // D_00218100
extern T217D_E30 D_0026DFC8;    // D_00218150
extern T217D_2E0 g_gaugeBarElement;    // D_002182E0
extern T217D_E30 D_0026E4E0;    // D_002181A0
extern T217D_510 g_timerElement;    // D_00218510
extern T217D_1380 g_timerCaption;   // D_00221380
extern T217D_330 g_buttonHintElement;    // D_00218330
extern T217D_380 D_0026EED0;    // D_00218380
extern T217D_3D0 D_0026F138;    // D_002183D0
extern T217D_420 D_0026F5A0;    // D_00218420
extern T217D_0F0 g_mapScreenList;    // D_002210F0
extern T217D_12E0 D_0026FA90;   // D_002212E0
extern T217D_1330 D_0026FD00;   // D_00221330
extern T217D_6D0 g_pauseMenuElement;    // D_002186D0
extern T217D_440 g_typedTextCaptionBox;    // D_0021A440
extern T217D_BF0 D_00270650;    // D_00220BF0
extern T217D_3F0 D_002708E0;    // D_0021A3F0
extern T217D_3F0 D_00271558;    // D_0021A3F0
extern T217D_560 D_002721D0;    // D_00218560
extern T217D_E30 D_00272430;    // D_00218240
extern T217D_E30 D_002726B0;    // D_00218290
extern T217D_470 D_00272930;    // D_00218470
extern T217D_4C0 D_00272B98;    // D_002184C0
extern T217D_720 g_stackedCaptionGroup;    // D_00218720
extern T217D_5B0 D_002739F0;    // D_002185B0
extern T217D_5B0 D_00273C50;    // D_002185B0
extern T217D_600 D_00273EB0;    // D_00218600
extern T217D_E30 D_00274118;    // D_002181F0

// The base is the stride of D_00218720's four sub-elements (func_0014ABD0 steps 0x260 bytes).
typedef char check_ScreenElement[sizeof(ScreenElement) == 0x260 ? 1 : -1];
typedef char check_T217D_330[sizeof(T217D_330) == 0x260 ? 1 : -1];

// The stack of screen elements the menus push and pop (g_elementStack, D_00275BC0): its state
// (SetElementStackState), and the elements, whose top gets the pad each frame
// (UpdateElementStack, file_1E88D0.cpp).
struct ElementStack {
    u8 pad00[4];
    s32 state;              // 0x04: 0 .. 8 (SetElementStackState)
    f32 stateTime;          // 0x08: the clock when the state was set
    ScreenElement* items[8]; // 0x0C: items[count - 1] is the top
    s32 count;              // 0x2C: 1 for the base element alone
    s32 resumeState;        // 0x30: the state that state 3 stands for, -1 for 3 itself
};

#endif
