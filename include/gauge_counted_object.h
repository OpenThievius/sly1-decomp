// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x48 (descriptor D_0021FC28, 0x560 bytes), a gauge-counted object: a collision object
// that, when it starts (StartGaugeCountedObject), resolves the three objects of its link table
// (g_gaugeCountedObjectLinks) and adds one to the limit at +0x684 of the first class 0x18
// object. Written for this project from what retail's code does (config/us/classes.tsv).
#ifndef GAUGE_COUNTED_OBJECT_H
#define GAUGE_COUNTED_OBJECT_H

#include "collider.h"

struct GaugeCountedObject : Collider {
    u8 pad550[4];
    void* f554;             // 0x554: loaded (id 0x3E5)
    void* f558;             // 0x558: loaded (id 0x3E4)
    void* f55C;             // 0x55C: loaded (id 0x3E6)
};

typedef char check_GaugeCountedObject[sizeof(GaugeCountedObject) == 0x560 ? 1 : -1];

#endif
