// SPDX-License-Identifier: AGPL-3.0-or-later
// The script machine's value (src/main/value.cpp): a tag and one word. Written for this project
// from what retail's code does (build/swarm/st3/PLAN.md, section 5; build/swarm/v1/NOTES.md).
//
// Eight bytes. func_0011B018 (the copy) and func_0011B0A8 (the assignment) copy words 0x0 and 0x4
// and nothing else; func_00113888 walks its two arguments 8 bytes apart; the records that hold
// one put the next field right after it (R11B008Node: 0xC-byte entries of D_0025C250, next at
// +8; R11B008Key: 0x10-byte entries of D_0025C290, the value at +4, next at +0xC). A caller's
// local takes a 16-byte stack slot because GCC 2.95 gives a BLKmode local (two words, 4-byte
// aligned: no integer mode on a strict-alignment target) the EE's biggest alignment, 16; the
// slot is the compiler's, not the value's. The lq/sq copies around the callers' values move
// the 16- and 64-byte payloads that a tag 0x16..0x18 value points to (func_0011C508,
// func_0011C618, func_0011C748; func_0011B258), never a value.
//
// Retail's functions are a C++ class's, as GCC 2.95 emits one: func_0011B008 the constructor
// (tag -1, returns this), func_0011B018 the copy constructor, func_0011B060 the destructor (its
// second argument is GCC's in-charge flag: 2 for a local, and the `flags & 1` call of
// func_0018D778, the global operator delete, is the code GCC adds to every destructor),
// func_0011B0A8 the assignment (returns this). They stay free functions under their retail
// names here, and callers call them explicitly: an inline constructor or destructor wrapping
// them changes the callers' code (build/swarm/v1/NOTES.md, "Class or free functions").
#ifndef SCRIPT_VALUE_H
#define SCRIPT_VALUE_H

#include "common.h"

struct R11B008Node;
struct R11AFC8;
struct BufferedStream;

// Tags: the setters, func_0011B0F8 (the comparison), func_0011B258 (the deep copy),
// func_0011B418 / func_0011B4A8 (the payload's release and reference), func_0011BA28 (the reader).
//   below 0x14: an operator node of func_0011BA28, no payload
//   0x14 int (func_0011B570)              0x15 float (func_0011B5B0)
//   0x16 vector, 16 bytes (func_0011B740) 0x17 0x40 bytes (func_0011B788)
//   0x18 vector, 16 bytes (func_0011B7D0) 0x19 two floats (func_0011B818)
//   0x1A three floats (func_0011B860)     0x1B bool (func_0011B5F0)
//   0x1C pointer (func_0011B640)          0x1D int (func_0011B680)
//   0x1E a chain of nodes (func_0011B6C0) 0x1F an R11AFC8 (func_0011B700)
//   0x20 pointer (func_0011B8A8)          0x21 int (func_0011B8E8)
//   0x22 nothing: func_0011B538 sets the tag alone (the built-ins' empty result)
//   -1 unset (func_0011B008)

struct ScriptValue {
    s32 tag;                    // 0x00: func_0011B008 (-1), the setters, func_0011B418, func_0011B4A8
    union {
        s32 i;                  // 0x04: 0x14 0x1B 0x1D 0x21 (func_0011B570, func_0011B5F0, func_0011B680, func_0011B8E8)
        f32 f;                  // 0x04: 0x15 (func_0011B5B0, func_0011B9A8, func_0011B0F8)
        f32* v;                 // 0x04: 0x16..0x1A, the pooled floats (func_0011B740..func_0011B860, func_0011B0F8)
        void* p;                // 0x04: 0x1C 0x20 (func_0011B640, func_0011B8A8); a payload (func_0011B258, func_0011B418)
        R11B008Node* node;      // 0x04: 0x1E (func_0011B6C0, func_0011B258)
        R11AFC8* rec;           // 0x04: 0x1F (func_0011B700, func_0011B258)
    };
};

typedef char check_ScriptValue[sizeof(ScriptValue) == 8 ? 1 : -1];

// A value in a chain: the 0xC-byte entries of D_0025C250, made by func_0011AF28 (cleared and
// constructed), destroyed by func_0011AF78 (the pool's callback), copied with its chain by
// func_0011AEB8, read from a stream by func_0011BA28. A tag 0x1E value points to the first; the
// setters take a node as the value it starts with.
struct R11B008Node : ScriptValue {
    R11B008Node* next;          // 0x08: func_0011AEB8, func_0011BA28
};

typedef char check_R11B008Node[sizeof(R11B008Node) == 0xC ? 1 : -1];

// A keyed value: the 0x10-byte entries of D_0025C290, made by func_0011C498 (cleared, the value
// constructed) and destroyed by func_0011C4E8 (the pool's callback); func_0011C418 copies a list
// of them, func_0011BD28 pushes one, func_0011BDD0 and func_0011BE90 find one by key.
struct R11B008Key {
    s32 key;                    // 0x00: func_0011BD28, func_0011BDD0, func_0011BE90
    ScriptValue value;              // 0x04: func_0011BD28, func_0011BDD0 (func_0011B0A8), func_0011BE90
    R11B008Key* next;           // 0x0C: func_0011BD28, func_0011BDD0, func_0011BE90
};

typedef char check_R11B008Key[sizeof(R11B008Key) == 0x10 ? 1 : -1];

// A list of R11B008Key: four bytes, made by func_0011BF30 (func_0018D5C0(4), cleared), copied
// by func_0011BEE0; func_0011BD28 pushes at the head.
struct R11B008List {
    R11B008Key* head;           // 0x00: func_0011BD28, func_0011BDD0, func_0011BE90, func_0011BEE0
};

typedef char check_R11B008List[sizeof(R11B008List) == 4 ? 1 : -1];

// The tag 0x1F payload: the 0x14-byte entries of D_0025C2B0, made by func_0011AFC8 (cleared),
// copied by func_0011AF98 (its first word given, or kept when 0).
struct R11AFC8 {
    s32 w0;                     // 0x00: func_0011AF98
    s32 w4;                     // 0x04: func_0011AF98
    s32 w8;                     // 0x08: func_0011AF98
    s32 wC;                     // 0x0C: func_0011AF98
    s32 w10;                    // 0x10: func_0011AF98
};

typedef char check_R11AFC8[sizeof(R11AFC8) == 0x14 ? 1 : -1];

// value.cpp. A function that gives a value back takes the place to build it first (the
// address GCC passes for a class returned by value) and returns it.
void* func_0011AE78(void);
void func_0011AEB8(R11B008Node* src, R11B008Node* dst, s32 first);
R11B008Node* func_0011AF28(void);
void func_0011AF78(R11B008Node* self);
void func_0011AF98(R11AFC8* src, R11AFC8* dst, s32 first);
R11AFC8* func_0011AFC8(void);
ScriptValue* func_0011B008(ScriptValue* self);
ScriptValue* func_0011B018(ScriptValue* self, const ScriptValue* src);
void func_0011B060(ScriptValue* self, s32 flags);
ScriptValue* func_0011B0A8(ScriptValue* self, const ScriptValue* src);
s32 func_0011B0F8(const ScriptValue* a, const ScriptValue* b);
void func_0011B258(const ScriptValue* src, ScriptValue* dst, s32 first);
void func_0011B418(ScriptValue* self);
void func_0011B4A8(const ScriptValue* self);
void func_0011B538(ScriptValue* self, s32 tag);
void func_0011B570(ScriptValue* self, s32 value);
void func_0011B5B0(ScriptValue* self, f32 value);
void func_0011B5F0(ScriptValue* self, s32 flag);
void func_0011B640(ScriptValue* self, void* p);
void func_0011B680(ScriptValue* self, s32 value);
void func_0011B6C0(ScriptValue* self, R11B008Node* node);
void func_0011B700(ScriptValue* self, R11AFC8* rec);
void func_0011B740(ScriptValue* self, f32* v);
void func_0011B788(ScriptValue* self, f32* v);
void func_0011B7D0(ScriptValue* self, f32* v);
void func_0011B818(ScriptValue* self, f32* v);
void func_0011B860(ScriptValue* self, f32* v);
void func_0011B8A8(ScriptValue* self, void* p);
void func_0011B8E8(ScriptValue* self, s32 value);
ScriptValue* func_0011B928(ScriptValue* out, const ScriptValue* in);
ScriptValue* func_0011B9A8(ScriptValue* out, const ScriptValue* in);
R11B008Node* func_0011BA28(BufferedStream* rd);
ScriptValue* func_0011BD28(ScriptValue* out, R11B008List* list, s32 key, const ScriptValue* value);
ScriptValue* func_0011BDD0(ScriptValue* out, R11B008List* list, s32 key, const ScriptValue* value);
s32 func_0011BE90(R11B008List* list, s32 key, ScriptValue* out);
void func_0011BEE0(R11B008List* self, R11B008List* out);
R11B008List* func_0011BF30(void);
void func_0011BF70(void);
void func_0011C040(void);

#endif
