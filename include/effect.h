// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind t219c: the records of class 0x1E's list (EffectOwner::list558) -- the effects a part with
// collision shows: a spark, a flash, a ring that follows a body. Written for this project from
// what retail's code does (config/us/tables.tsv, src/main/class_descriptors.cpp, effect.cpp).
//
// func_0019EA78(kind, owner) takes a record from the world's pool at World+0x1B2C (0x180 records
// of 0x140 bytes), zeroes it, stores the kind's table (func_0019E908: kind 0 is D_00219C20, kind
// 2 on D_00219C40 and the next 26 tables, 0x20 bytes apart; no kind 1) at +0, the kind at +4 and
// the 1E object at +0xC, links it into the list (link at +0x10) and counts a use (+8).
// func_0019EBE8 takes it out again and, when the last use goes, func_0019EC30 runs its end
// hooks and gives it back to the pool.
//
// The kinds, by what their own slots do (config/names.tsv names each table g_<kind>EffectMethods):
// 0 basic (the shared slots only), 2 falling, 3 rising, 4 impact, 5 growing, 6 shrinking fall,
// 7 dropping, 8 streak, 9 scaled, 10 trail segment, 11 spawning, 12 follow-up, 13 wide trail
// segment, 14 short falling, 15 emitter, 16 camera space, 17 long streak, 18 phased, 19
// projectile, 20 hit mark, 21 tumbling, 22 aimed, 23 streaked, 24 spinning, 25 facing, 26 delayed
// and 27 message.
//
// The 27 kinds share one layout: the header and the fields the shared slots read are the same
// for all, and each kind's own fields sit in the span from +0x28 to +0x140 where the others
// leave it free. Where two kinds read one offset differently (a float, an integer, a pointer),
// a union holds them. The tables are defined in src/main/class_descriptors.cpp as arrays of function
// pointers; Vt219C gives their slots types.
#ifndef EFFECT_H
#define EFFECT_H

#include "common.h"
#include "placed_object.h"

struct EffectOwner;     // the owner (include/c1e.h)
struct Collider;     // the body some records follow (include/c03.h)
struct Effect;

// A 16-byte, 16-aligned block moved as one quadword.
struct __attribute__((aligned(16))) Quad219C {
    s32 a, b, c, d;
};

// The 8 slots of a kind's table. Slot 0 is the kind's set-up (the creator calls it right after
// func_0019EA78 with the place); 3, 4, 5, 6 and 7 are mostly the shared func_0019F390,
// func_0019F560, func_0019F858, func_0019ECE0 and func_0019ED58.
struct Vt219C {
    void (*m00)(Effect* self, void* pos, f32 scale, s32 flags);          // 0x00: set-up
    void (*m01)(Effect* self, void* other);                              // 0x04
    void (*m02)(Effect* self);                                           // 0x08
    void (*m03)(Effect* self, f32 dt);                                   // 0x0C: moves it (func_0019E220)
    void (*m04)(Effect* self, f32 dt);                                   // 0x10: every frame
    void (*m05)(Effect* self, void* other);                              // 0x14
    void (*m06)(Effect* self, s32 flag);                                 // 0x18: end (func_0019F560)
    s32 (*m07)(Effect* self, void* other, void* a2, void* a3);           // 0x1C: contact
};

// What a record runs when it ends (+0x118, the list func_0019EC30 walks).
struct T219CHook {
    void (*fn)(void* payload, s32 kind, Effect* owner);      // 0x00
    void* payload;                                          // 0x04
    u8 pad08[0x10 - 0x08];                                  // 0x08
    T219CHook* next;                                        // 0x10
};

// The parameter block a kind-0x10 record points to (+0x130): D_00261AD0, D_00261B60 and
// D_0026A970, 0x70 bytes each, const data of the three owners that create such a record
// (func_00148298, func_00148FF0, func_001999D0). Six rows of floats, then the function the
// record runs with its owner (+0x134) when it ends (func_001A0F88). The block is 16-aligned:
// InitCameraSpaceEffect (func_001A0C98) copies its sixth row (+0x50) with one lq. So D_0026A970
// starts object_gatherer.cpp's .data on 16, 8 bytes after gauge_collider.cpp's ends (the
// linker's padding).
struct __attribute__((aligned(16))) T219C_Params {
    f32 rows[24];                   // 0x00
    void (*fn60)(void* owner);      // 0x60
    u8 pad64[0x70 - 0x64];          // 0x64
};

struct Effect {
    const Vt219C* vt;       // 0x00
    s32 kind;               // 0x04
    s32 uses;               // 0x08: func_0019EC20 counts one, func_0019EC30 ends at 0
    EffectOwner* owner;             // 0x0C: the 0x1E object whose list holds it
    Effect* next;            // 0x10: the link in EffectOwner::list558
    Effect* prev;            // 0x14
    f32 start;              // 0x18: the time it began (D_0026185C)
    f32 life;               // 0x1C: how long it lasts (func_0019F560)
    union {
        s32 i20;            // 0x20: a number taken from the world (D_00275710 + 0x1CEC ..)
        void* p20;          // 0x20: the object it follows (kinds 16 and 26)
    };
    Collider* target;            // 0x24: the body it follows (func_0019F560, func_0019F9D0)
    u8 pad28[0x30 - 0x28];  // 0x28
    union {
        Quad219C q30;       // 0x30
        f32 m30[3];         // 0x30
    };
    Quad219C q40;           // 0x40
    Vec02 rotation[3];      // 0x50: the placement (func_0019F858 reads it with the one at +0x80)
    Quad219C pos;           // 0x80: the effect's current point
    Quad219C prevPos;       // 0x90: the point it was at last frame
    union {
        Quad219C qA0;       // 0xA0
        u8 padA0[0xB0 - 0xA0];  // 0xA0
    };
    union {
        f32 fB0;            // 0xB0
        s32 iB0;            // 0xB0
    };
    u8 padB4[0xC0 - 0xB4];  // 0xB4
    union {
        Quad219C qC0;       // 0xC0
        Vec02 vC0;          // 0xC0: kind 26's direction (func_001924C8 gives it the world's gravity)
    };
    u8 padD0[0x100 - 0xD0]; // 0xD0
    Vec02 v100;             // 0x100: a spin the effect turns by (func_0019F390)
    union {
        s32 i110;           // 0x110
        f32 spinDrag;       // 0x110: its drag, per second (func_0019F390)
    };
    void* oscillator;       // 0x114: the frame func_0019F858 places the record by
    T219CHook* hooks;       // 0x118: run at its end (func_0019EC30)
    u8 pad11C[0x120 - 0x11C];   // 0x11C
    union {
        f32 f120;           // 0x120
        s32 i120;           // 0x120
        void* p120;         // 0x120
    };
    union {
        f32 f124;           // 0x124
        s32 i124;           // 0x124
        Effect* p124;        // 0x124
    };
    union {
        f32 f128;           // 0x128
        s32 i128;           // 0x128
        Effect* p128;        // 0x128
    };
    s32 i12C;               // 0x12C: kind 18's point the strip starts at (DrawPhasedEffect)
    union {
        const T219C_Params* params; // 0x130: kind 16's block
        s32 (*points)(void* src, s32 max, void* out); // 0x130: kind 18's points, from +0x134 (DrawPhasedEffect)
        f32 f130;           // 0x130: an angle (TakeDelayedEffectSourcePose)
    };
    union {
        void* p134;         // 0x134: kind 16's owner
        s32 i134;           // 0x134
    };
    u8 pad138[0x140 - 0x138];   // 0x138
};

typedef char check_Quad219C[sizeof(Quad219C) == 0x10 ? 1 : -1];
typedef char check_T219CHook[sizeof(T219CHook) == 0x14 ? 1 : -1];
typedef char check_T219C_Params[sizeof(T219C_Params) == 0x70 && __alignof__(T219C_Params) == 16 ? 1 : -1];
typedef char check_Effect[sizeof(Effect) == 0x140 ? 1 : -1];

#endif
