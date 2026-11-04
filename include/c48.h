// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x48 (descriptor D_0021FC28, 0x560 bytes): a collision object with three objects the
// level loader resolves into it (D_0026A8E0). Written for this project from what retail's code
// does (config/us/classes.tsv).
#ifndef C48_H
#define C48_H

#include "c03.h"

struct C48 : C03 {
    u8 pad550[4];
    void* f554;             // 0x554: loaded (id 0x3E5)
    void* f558;             // 0x558: loaded (id 0x3E4)
    void* f55C;             // 0x55C: loaded (id 0x3E6)
};

typedef char check_C48[sizeof(C48) == 0x560 ? 1 : -1];

#endif
