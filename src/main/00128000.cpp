// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Owned { u8 pad[0x14]; void* owner; };

extern u8 D_002197C0[];
void func_00121228(void* owner, void* item, void* table);

void func_00128998(Owned* item)
{
    func_00121228(item->owner, item, D_002197C0);
}

void func_0012A4A0(void* self, s32 a1);

void func_0012A478(void* self, s32 a1)
{
    func_0012A4A0(self, a1 != 0 ? 1 : -1);
}

void func_00129730(void* self);

struct Sub_12A580 { u8 pad[0x40]; f32 f40; };
struct Obj_12A580 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A580* p200; };

void func_0012A580(Obj_12A580* self, f32 f)
{
    func_00129730(self);
    self->p200->f40 = f;
}

struct Sub_12A5B8 { u8 pad[0x40]; f32 f40; };
struct Obj_12A5B8 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A5B8* p200; };

void func_0012A5B8(Obj_12A5B8* self, f32* out)
{
    f32 r = 0.0f;
    if (self->p200 != 0) r = self->p200->f40;
    *out = r;
}

void func_00129730(void* self);

struct Vec16_12A5D0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A5D0 { u8 pad[0x50]; Vec16_12A5D0 v50; };
struct Obj_12A5D0 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A5D0* p200; };

void func_0012A5D0(Obj_12A5D0* self, Vec16_12A5D0* src)
{
    func_00129730(self);
    self->p200->v50 = *src;
}

extern u8 D_00275C40[];

struct Vec16_12A610 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A610 { u8 pad[0x50]; Vec16_12A610 v50; };
struct Obj_12A610 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A610* p200; };

void func_0012A610(Obj_12A610* self, Vec16_12A610* out)
{
    Vec16_12A610* src = self->p200 != 0 ? (Vec16_12A610*)((u8*)self->p200 + 0x50) : (Vec16_12A610*)D_00275C40;
    *out = *src;
}

void func_00129730(void* self);

struct __attribute__((packed)) U64_12A630 { u64 v; };
struct Sub_12A630 { u8 pad[0x60]; U64_12A630 v60; };
struct Obj_12A630 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A630* p200; };

void func_0012A630(Obj_12A630* self, U64_12A630* src)
{
    func_00129730(self);
    self->p200->v60 = *src;
}

extern u8 D_00275C60[];

struct __attribute__((packed)) U64_12A678 { u64 v; };
struct Sub_12A678 { u8 pad[0x60]; U64_12A678 v60; };
struct Obj_12A678 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A678* p200; };

void func_0012A678(Obj_12A678* self, U64_12A678* out)
{
    U64_12A678* src = self->p200 != 0 ? (U64_12A678*)((u8*)self->p200 + 0x60) : (U64_12A678*)D_00275C60;
    *out = *src;
}

void func_00129730(void* self);

struct Vec16_12A6A0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6A0 { u8 pad[0x70]; Vec16_12A6A0 v70; };
struct Obj_12A6A0 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A6A0* p200; };

void func_0012A6A0(Obj_12A6A0* self, Vec16_12A6A0* src)
{
    func_00129730(self);
    self->p200->v70 = *src;
}

extern u8 D_00275C40[];

struct Vec16_12A6E0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6E0 { u8 pad[0x70]; Vec16_12A6E0 v70; };
struct Obj_12A6E0 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A6E0* p200; };

void func_0012A6E0(Obj_12A6E0* self, Vec16_12A6E0* out)
{
    Vec16_12A6E0* src = self->p200 != 0 ? (Vec16_12A6E0*)((u8*)self->p200 + 0x70) : (Vec16_12A6E0*)D_00275C40;
    *out = *src;
}
