// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: buffer copies and helper calls are modeled, but packed field handling, call scheduling, and code size differ.
#include "common.h"

struct __attribute__((packed)) Buffer_152730 {
    union {
        u64 pair;
        struct { s32 count; s32 size; } fields;
    };
    s32 tail;
};
void func_00152440(Buffer_152730*);
Buffer_152730* func_00152460(Buffer_152730*);
void func_00152730(Buffer_152730* destination, Buffer_152730* source)
{
    if (source->fields.count == 0) return;
    if (destination->fields.count == 0) {
        destination->pair = source->pair;
        destination->tail = source->tail;
        func_00152440(source);
        return;
    }
    Buffer_152730* left = func_00152460(destination);
    Buffer_152730* right = func_00152460(source);
    left->fields.count = source->fields.count;
    right->fields.size = destination->fields.size;
    destination->fields.size = source->fields.size;
    func_00152440(source);
}
