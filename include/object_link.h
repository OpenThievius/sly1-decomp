// SPDX-License-Identifier: AGPL-3.0-or-later
// An entry of the link tables ResolveObjectLinks (func_00124DF8)(self, count, table) walks when an object is set up:
// for each entry it finds the object id `id` names (func_0015A418, kind 1, or 5 with flag 1,
// | 0x100 with flag 0x20) and, unless flag 8, stores it at self + offset; unless flag 4 it calls
// func_00182ED8 on it, and with flag 0x10 func_001832F0(found, self). Written for this project
// from what retail's code does. The tables are data: no function fills them, so the type is
// named by the one that reads them: each entry links the object to another object found by id.
//
// 54 tables are passed to func_00124DF8 (every `func_00124DF8(..., D_X)` in src/). They are
// declared here without a length: their definitions (53 of them are in C, 001E4000.cpp
// and the window files) keep theirs. A few labels end with one more word after the entries
// (D_00262718: nine entries and a word; D_00262E40: 151 and a word; D_00275750: nine and a word).
#ifndef OBJECT_LINK_H
#define OBJECT_LINK_H

#include "common.h"

struct ObjectLink {
    u32 flags;              // 0x00: 1, 4, 8, 0x10, 0x20 (above)
    u32 id;                 // 0x04: the id of the object to find
    u32 offset;             // 0x08: where in the object the found one goes
};

typedef char check_ObjectLink[sizeof(ObjectLink) == 0xC ? 1 : -1];

extern ObjectLink D_00261410[];
extern ObjectLink D_002619A0[];
extern ObjectLink D_00261CA0[];
extern ObjectLink D_00261CC8[];
extern ObjectLink D_00261CE0[];
extern ObjectLink D_002621C8[];
extern ObjectLink D_002621E0[];
extern ObjectLink D_00262718[];
extern ObjectLink D_00262788[];
extern ObjectLink D_002629D0[];
extern ObjectLink D_00262A10[];
extern ObjectLink D_00262E40[];
extern ObjectLink D_00263AC8[];
extern ObjectLink D_00263D58[];
extern ObjectLink D_00263E08[];
extern ObjectLink D_002640B0[];
extern ObjectLink D_00264230[];
extern ObjectLink D_00264910[];
extern ObjectLink D_00264928[];
extern ObjectLink D_002699B0[];
extern ObjectLink D_00269B60[];
extern ObjectLink D_0026A728[];
extern ObjectLink D_0026A738[];
extern ObjectLink D_0026A8E0[];
extern ObjectLink D_0026A918[];
extern ObjectLink D_0026A928[];
extern ObjectLink D_0026A938[];
extern ObjectLink D_0026A948[];
extern ObjectLink D_0026AA50[];
extern ObjectLink D_0026AB90[];
extern ObjectLink D_0026ABA0[];
extern ObjectLink D_0026B778[];
extern ObjectLink D_0026B790[];
extern ObjectLink D_0026B7E8[];
extern ObjectLink D_0026B830[];
extern ObjectLink D_0026B840[];
extern ObjectLink D_0026B888[];
extern ObjectLink D_0026B8A0[];
extern ObjectLink D_002744B8[];
extern ObjectLink D_002744D8[];
extern ObjectLink D_002749B0[];
extern ObjectLink D_00274AD8[];
extern ObjectLink D_00274C20[];
extern ObjectLink D_00274C30[];
extern ObjectLink D_00274F90[];
extern ObjectLink D_002752A0[];
extern ObjectLink D_00275750[];
extern ObjectLink D_00275B28[];
extern ObjectLink D_00275B60[];
extern ObjectLink D_00275C90[];
extern ObjectLink D_00275CA0[];
extern ObjectLink D_00275D08[];
extern ObjectLink D_00275FE0[];

#endif
