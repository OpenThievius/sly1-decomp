// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind v249d: a memory reader, a C++ object with one virtual (GCC vtable D_00249D98). Written for
// this project from what retail's code does (config/us/tables.tsv, kinds.tsv).
//
// func_0013CC00 builds one on its stack and hands it to func_0013C9D0, which asks it for bytes
// through entry 1 (func_0013CC80): `fn((u8*)port + delta, count, dst)`. A plain struct with an
// explicit vptr: the entries are GCC 2.95's {s16 delta; s16 index; fn}, entry 0 being
// {offset-to-top, rtti} = {0, 0, 0}. No `virtual`, so GCC emits nothing of its own (the table is
// defined in 0013C000.cpp as a table of functions).
#ifndef V249D_H
#define V249D_H

#include "common.h"

struct V249D;

struct V249D_Vt {
    s16 adj0; s16 idx0; void* fn0;                                              // 0x00
    s16 adj1; s16 idx1; s32 (*read)(V249D* self, s32 count, void* dst);         // 0x08
    s16 adj2; s16 idx2; void* fn2;                                              // 0x10
};

struct V249D {
    const V249D_Vt* vt;     // 0x00
    u8* base;               // 0x04: the bytes
    void* f08;              // 0x08: the owner's pointer (set, never read)
    s32 pos;                // 0x0C: how far it has read
    union {
        void* f10;          // 0x10: the object func_0013CC00 makes it from
        s32 remain;         // 0x10: bytes left (func_0013CC80)
    };
};

#endif
