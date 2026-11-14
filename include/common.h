// SPDX-License-Identifier: AGPL-3.0-or-later
// Types every source file uses. Written for this project from what the code does;
// nothing here comes from an SDK.
#ifndef COMMON_H
#define COMMON_H

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
// 64 bits by machine mode, not by `long`: the PS2 compiler's `long` is 64 bits and its
// `long long` 128, while most other targets have a 32-bit `long`; DImode is 64 bits on every
// GCC or Clang target, and the same type as `long` here, so the code is unchanged.
typedef signed int s64 __attribute__((mode(DI)));
typedef unsigned int u64 __attribute__((mode(DI)));
typedef float f32;

// An integer that holds an address: a field or value that carries a pointer in some uses and a
// number in others, or an address the code does arithmetic on. The PS2's pointers are 32 bits,
// so these are retail's 32-bit integers; a port to 64-bit pointers changes only these two lines
// (docs/PORTING.md).
typedef s32 sptr;
typedef u32 uptr;

// Readable names for address-named symbols (docs/NAMING.md).
#include "names.h"

#endif
