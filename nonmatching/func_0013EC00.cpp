// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the search and update loop is instruction-for-instruction close,
// but the compiler orders the loop index and pointer initializers differently
// and emits the insertion address using v1 instead of retail's a0.
#include "common.h"

struct Entry_13EC00 { s32 key0, key1, valueA, valueB; };
s32 func_0013EC00(Entry_13EC00* entries, s32 capacity, s32* count, s32 flag, s32 key0, s32 key1, s32 value)
{
    if (*count <= 0) goto insert_13EC00;
    s32 i = 0;
    Entry_13EC00* entry = entries;
    while (i < *count) {
        if (entry->key0 == key0) {
            if (entry->key1 == -1 || entry->key1 == key1) {
                if (flag != 0) entry->valueA = value;
                else entry->valueB = value;
                return 1;
            }
        }
        i++;
        entry++;
    }
insert_13EC00:
    s32 index = *count;
    s32 next = index + 1;
    if (next >= capacity) return 0;
    *count = next;
    entry = (Entry_13EC00*)((char*)entries + index * 16);
    entry->key0 = key0;
    entry->key1 = key1;
    if (flag) {
        entry->valueA = value;
        entry->valueB = -1;
    } else {
        entry->valueB = value;
        entry->valueA = -1;
    }
    return 1;
}
