// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1C2320 { u8 pad[4]; void* f4; };
void func_00130110(void* p);
void* func_0011BE90(void* a, void* b, void* c);
void func_0011BDD0(void* self, void* a, void* b, void* c);
void func_0011BD28(void* self, void* a, void* b, void* c);

void* func_001C2320(void* self, Obj_1C2320* p, void* a2, void* a3)
{
    func_00130110(p);
    if (func_0011BE90(p->f4, a2, 0)) func_0011BDD0(self, p->f4, a2, a3);
    else func_0011BD28(self, p->f4, a2, a3);
    return self;
}

void func_001C27B0(s32 a, s32 b);

void func_001C29C8()
{
    func_001C27B0(1, 0xFFFF);
}

struct Obj_1C29E8 { u8 pad[8]; s32 f8; s32 fC; };

void func_001C29E8(Obj_1C29E8* o)
{
    o->fC = 0;
    o->f8 = 0;
}

void func_001921A8(void* self);

struct Obj_1C3390 { u8 pad[0x610]; s32 f610; u8 pad2[0x694 - 0x614]; s32 f694; };

void func_001C3390(Obj_1C3390* self)
{
    func_001921A8(self);
    self->f610 = -1;
    self->f694 = 5;
}

bool func_001E9970();

typedef void (*VFn_1C3928)(void*);
struct Obj_1C3928 { VFn_1C3928* vtbl; };
extern Obj_1C3928 D_0026DD48;
extern Obj_1C3928 D_0026DFC8;

// NEAR: the two lui immediates for D_0026DD48 / D_0026DFC8 come out wrong in check.py (see results.tsv note).
void func_001C3928()
{
    if (func_001E9970()) {
        D_0026DD48.vtbl[14]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[14]((void*)&D_0026DFC8);
    } else {
        D_0026DD48.vtbl[15]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[15]((void*)&D_0026DFC8);
    }
}

struct Entry_1C3C00 { s32 first; u8 pad[60]; };
struct Obj_1C3C00 { u8 p0[0x67C]; s32 f67C; s32 f680; s32 f684; s32 f688; u8 p1[0x694 - 0x68C]; s32 f694; };
s32 func_001300E8(s32 a, s32 b);
s32 func_001833F0(s32 a, s32 b);

void func_001C3C00(Obj_1C3C00* self, Entry_1C3C00* table, s32 idx)
{
    Entry_1C3C00* e = (Entry_1C3C00*)((u8*)table + ((1 - idx) << 6));
    if (func_001300E8(e->first, 0x21)) {
        if (self->f694 > 0) {
            self->f680 = 1;
            return;
        }
        if (self->f67C == 0) self->f684 = e->first;
        return;
    }
    if (func_001833F0(e->first, 0x52F)) self->f688 = e->first;
}

void func_00192C58(void* self);
void func_001C3FC8(void* self, s32 flag);

void func_001C3E80(void* self)
{
    func_00192C58(self);
    func_001C3FC8(self, 1);
}

typedef void (*VFn_1C3F68)(void*, void*);
struct Obj_1C3F68 { VFn_1C3F68* vtbl; };
struct Local_1C3F68 { s32 pad[2]; s32 value; VFn_1C3F68 fn; };
void func_001D7098(void* self, s32 a, s32 b);
void func_001C3EB0(void* self, void* data);

void func_001C3F68(Obj_1C3F68* self, s32 value)
{
    Local_1C3F68 local;
    func_001D7098(&local, 0, value);
    local.value = value;
    local.fn = func_001C3EB0;
    self->vtbl[80]((void*)self, (void*)&local);
}

void func_001C06A0(s32 a, s32 b, f32 x);

void func_001C0000(s32 flag, f32 x)
{
    func_001C06A0(6, 0, x);
    func_001C06A0(6, 2, x);
    func_001C06A0(6, 3, x);
    if (flag) {
        func_001C06A0(6, 1, x);
    }
}

s32 func_0011D4E0(s32 flag);

s32 func_001C0790(s32 value)
{
    return func_0011D4E0(value != 0);
}

struct Pk8_1C0A50 { u64 v; } __attribute__((packed));
struct Ent_1C0A50 { s32 key; Pk8_1C0A50 a; Pk8_1C0A50 b; };
struct Obj_1C0A50 { u8 pad[0x1D80]; s32 count; Ent_1C0A50 ents[16]; };

extern Pk8_1C0A50 D_00274820;
extern Pk8_1C0A50 D_00274828;

void func_001C0A50(Obj_1C0A50* self, s32 key)
{
    if (self->count < 16) {
        Ent_1C0A50* e = &self->ents[self->count];
        e->key = key;
        e->a = D_00274820;
        e->b = D_00274828;
        self->count++;
    }
}

extern s32 D_00274728;
extern s32 D_006053E0[];

s32 func_0011D8F0(s32 a, s32 b);

void func_001C0C68(s32 i)
{
    D_006053E0[i] = func_0011D8F0(D_00274728, i);
}

struct Obj_1C1110 { u8 pad[0x14]; s32 f14; };

void func_00182ED0(Obj_1C1110* self);
void func_00152600(s32 p, Obj_1C1110* self);

void func_001C1110(Obj_1C1110* self)
{
    func_00182ED0(self);
    func_00152600(self->f14 + 0x1C84, self);
}

struct Loc_1C1E48 { u8 obj[0x10]; s32 tmp; s32 flag; s32 cnt; };

void func_0011B008(Loc_1C1E48* p);
void func_0011B6C0(Loc_1C1E48* p, s32 v);
void func_0011B538(Loc_1C1E48* p, s32 v);
void func_0011B018(void* self, Loc_1C1E48* p);
void func_0011B060(Loc_1C1E48* p, s32 v);
void func_001C1A28(s32* p, s32 v);

void* func_001C1E48(void* self, s32 n, s32* keys, s32* vals)
{
    Loc_1C1E48 loc;
    func_0011B008(&loc);
    loc.flag = 0;
    loc.cnt = 0;
    for (s32 i = 0; i < n; i++) {
        loc.tmp = keys[i];
        func_001C1A28(&loc.tmp, vals[i]);
    }
    if (loc.flag) {
        func_0011B6C0(&loc, loc.flag);
    } else {
        func_0011B538(&loc, 0);
    }
    func_0011B018(self, &loc);
    func_0011B060(&loc, 2);
    return self;
}
