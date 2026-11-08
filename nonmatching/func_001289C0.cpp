// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 581/592 (98.1%), checked 2026-11-07
// NEAR: every instruction and register matches except the last min: retail loads self->f80 into $f1 before the lui/mtc1 of 2000.0 into $f0; ours schedules the constant first (or, with the operands the other way round, swaps the two registers). Tried: operand order, a local for either operand, `cap = 2000.0f; cap = cap <? ...`.
#include "common.h"
#include "placed_object.h"
#include "world.h"

s32 ReadBufferedU8(void* a);
s32 ReadBufferedS16(void* a);
s32 ReadBufferedU32(void* a);
f32 ReadBufferedFloat(void* a);
void ReadBufferedRotation3(void* a, void* b);
void ReadBufferedVector3(void* a, void* b);
void* AllocateFrontMemory(s32 n);
extern const f32 D_00249A1C;
void LoadFollowRecord(PlacedObject* self, void* a1);
void ReadPropertyRecords(PlacedObject* self, void* stream);
void ReadPlacedObjectModel(void* record, void* stream, PlacedObject* owner);
void ReadSlotObjects(World* world, PlacedObject* self, void* stream);

struct BakedRow {
    s32 id;
    f32* values;
};

void func_001289C0(PlacedObject* self, void* r)
{
    ReadBufferedRotation3(r, &self->rot);
    ReadBufferedVector3(r, &self->pos);
    self->bits24 = ReadBufferedU8(r);
    self->bits26 = ReadBufferedU8(r);
    self->bits28 = ReadBufferedU8(r);
    self->f88 = ReadBufferedU32(r);
    self->f80 = ReadBufferedFloat(r);
    self->f84 = ReadBufferedFloat(r);
    self->f2A4 = ReadBufferedFloat(r);
    self->f2A8 = ReadBufferedFloat(r);
    if (self->f80 == D_00249A1C) {
        self->f80 = 10000000000.0f;
    }
    if (self->f84 == D_00249A1C) {
        f32 cap = 2000.0f;
        cap = cap <? self->f80;
        self->f84 = cap;
    }
    ReadPropertyRecords(self, r);
    ReadPlacedObjectModel(self->sub22C, r, self);
    LoadFollowRecord(self, r);
    if (self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    self->f2B8 = ReadBufferedU8(r);
    BakedRow* rows = (BakedRow*)AllocateFrontMemory(self->f2B8 << 3);
    self->f2BC = rows;
    for (s32 i = 0; i < self->f2B8; i++) {
        BakedRow* row = &((BakedRow*)self->f2BC)[i];
        row->id = ReadBufferedS16(r);
        row->values = (f32*)AllocateFrontMemory(self->f26C << 2);
        for (s32 j = 0; j < self->f26C; j++) {
            row->values[j] = ReadBufferedFloat(r);
        }
    }
    ReadSlotObjects(self->world, self, r);
}
