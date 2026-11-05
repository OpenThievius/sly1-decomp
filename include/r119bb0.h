// SPDX-License-Identifier: AGPL-3.0-or-later
// The script machine's built-in functions (src/main/file_112698.cpp): their shared signature, the
// record of their table, the host function a tag 0x21 value points to, and the scope every
// evaluation runs in. Written for this project from what retail's code does
// (build/swarm/v2/NOTES.md); the value itself is ScriptValue (r11b008.h).
#ifndef R119BB0_H
#define R119BB0_H

#include "common.h"
#include "script_value.h"

struct R11A630;

// A built-in: func_00119BB0 calls one as `fn(&result, count, args, scope)` (`jalr` through the
// record's first word, the four arguments in a0..a3) and every built-in returns its first
// argument, as GCC 2.95 returns the address of a class it gives back. `args` holds `count`
// values, 8 bytes apart; `scope` is the scope the call is evaluated in.
typedef ScriptValue* (*R119BB0Fn)(ScriptValue* ret, s32 count, ScriptValue* args, R11A630* scope);

// A record of the built-ins' table: 125 records from D_00259958 (func_00112698's) to 0x259F34;
// retail's second label, D_00259DE8, falls on the count of record 97 (func_00117668's, which
// reads it). A tag 0x1D value holds a record's index; func_00119BB0 reads `count` and `rest`,
// evaluates `count` arguments, and when `rest` is set gathers the remaining ones into one tag
// 0x1E chain (tag 0 when there are none) after them.
struct R119BB0 {
    R119BB0Fn fn;           // 0x00: func_00119BB0 calls it
    s32 count;              // 0x04: func_00119BB0; the arguments evaluated one by one
    s32 rest;               // 0x08: func_00119BB0; nonzero: the rest as a chain in args[count]
};

typedef char check_R119BB0[sizeof(R119BB0) == 0xC ? 1 : -1];

// What a tag 0x21 value points to: a function of the host with its object. func_00119BB0 calls
// `fn(&result, self, count, args)` with `count` arguments; func_00113B60 compares two by `self`
// and `fn`. Its producer is outside this file; only these three words are read here, so the
// size is not known.
struct R119BB0Host {
    void* self;             // 0x00: func_00119BB0, func_00113B60
    ScriptValue* (*fn)(ScriptValue* ret, void* self, s32 count, ScriptValue* args);   // 0x04: func_00119BB0, func_00113B60
    s32 count;              // 0x08: func_00119BB0
};

// A scope: up to four enclosing scopes searched after its own names, and its names as a list of
// R11B008Key (key: the name, value: what it holds). 0x1C bytes from the pool D_0025C270, cleared
// (func_0011A630); func_0011A328 gives it one enclosing scope, func_0011A358 adds a name,
// func_0011A4D8 looks one up (`busy` stops the search coming back through a cycle),
// func_0011A5B0 copies one.
struct R11A630 {
    s32 count;              // 0x00: func_0011A328, func_0011A4D8, func_0011A5B0
    R11A630* parents[4];    // 0x04: func_0011A328, func_0011A4D8, func_0011A5B0 (count * 4 bytes)
    R11B008Key* head;       // 0x14: func_0011A358, func_0011A4D8, func_0011A5B0
    s32 busy;               // 0x18: func_0011A4D8
};

typedef char check_R11A630[sizeof(R11A630) == 0x1C ? 1 : -1];

#endif
