// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "memory_reader.h"

// An entry of the file's two GCC vtables, written out as tables of functions.
typedef void (*Fn_Table)();
s32 func_0013CC80(MemoryReader* self, s32 want, void* dst);
int func_0013CCE8();

// The file's .rodata, in retail's order: the vtable of the reader's base (its one virtual,
// func_0013CCE8, returns 0; nothing builds that class) and the memory reader's (D_00249D98).
extern const Fn_Table D_00249D80[6] = { 0, 0, 0, (Fn_Table)func_0013CCE8, 0, 0 };
extern const Fn_Table D_00249D98[6] = { 0, 0, 0, (Fn_Table)func_0013CC80, 0, 0 };

struct InitialState {
	s32 field_00;
	s32 field_04;
	s32 field_08;
	s32 field_0C;
	s32 field_10;
	s32 field_14;
	s32 field_18;
	s32 field_1C;
};

extern void func_0013C9B0(InitialState* state);

void func_0013C988(InitialState* state, s32 initialValue, s32 secondaryValue) {
	state->field_04 = initialValue;
	state->field_00 = secondaryValue;
	ResetRingBuffer(state);
}

void func_0013C9B0(InitialState* state)
{
    state->field_1C = 0;
    state->field_18 = 0;
    state->field_14 = 0;
    state->field_0C = 0;
    state->field_08 = 0;
    state->field_10 = state->field_04;
}

struct Ring_0013C9D0 {
    u8* buf;
    s32 size;
    s32 pos;
    u8 pad_0c[0x04];
    s32 avail;
    s32 f14;
    u8 pad_18[0x04];
    s32 f1c;
};
s32 func_0013C9D0(Ring_0013C9D0* self, s32 n, MemoryReader* port)
{
    s32 total = 0;
    s32 rem = n;
    if (n <= 0 || self->avail < n) {
        rem = self->avail;
    }
    while (rem != 0) {
        s32 avail = self->size - self->pos;
        s32 cnt = rem < avail ? rem : avail;
        s32 r = port->methods->read((MemoryReader*)((u8*)port + port->methods->adj1), cnt, self->buf + self->pos);
        if (r == 0) {
            break;
        }
        total += r;
        rem -= r;
        self->pos += r;
        self->pos %= self->size;
        self->f14 += r;
        self->avail -= r;
        self->f1c += r;
        if (n <= 0) {
            break;
        }
    }
    return total;
}

struct Self_13CAD8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
};
typedef s32 (*FnA_13CAD8)(void* self, s32 a1, s32 a2);
typedef s32 (*FnB_13CAD8)(void* self);
struct Vt_13CAD8 {
    u8 pad0[8];
    s16 adj8;
    u8 pad1[2];
    FnA_13CAD8 fn0C;
    s16 adj10;
    u8 pad2[2];
    FnB_13CAD8 fn14;
};
struct Obj_13CAD8 {
    Vt_13CAD8* vt;
};

s32 func_0013CAD8(Self_13CAD8* self, s32 n, Obj_13CAD8* o)
{
    s32 total = 0;
    s32 rem = n;
    if (rem <= 0 || self->f14 < rem)
        rem = self->f14;
    for (;;) {
        if (rem == 0)
            break;
        s32 chunk = self->f4 - self->fC;
        if (rem < chunk)
            chunk = rem;
        s32 s0 = o->vt->fn0C((u8*)o + o->vt->adj8, chunk, self->f0 + self->fC);
        if (s0 == 0)
            break;
        self->fC = (self->fC += s0) % self->f4;
        self->f14 -= s0;
        if (o->vt->fn14((u8*)o + o->vt->adj10) != 0)
            self->f18 += s0;
        else
            self->f10 += s0;
        rem -= s0;
        total += s0;
        if (n <= 0)
            break;
    }
    return total;
}

struct Self_13CC00 { u8 pad[4]; };

s32 func_0013CC00(Self_13CC00* self, void* a1, void* a2)
{
    if (a1 != 0) {
        MemoryReader arg;
        arg.methods = (const MemoryReaderMethods*)g_memoryReaderMethods;
        arg.base = (u8*)a2;
        arg.f10 = a1;
        arg.f08 = a1;
        arg.pos = 0;
        return FillRingBuffer((Ring_0013C9D0*)self, (s32)a1, &arg);
    }
    return 0;
}

struct Span_CC48 {
    u8 pad0[0x10];
    s32 a;
    u8 pad1[0x4];
    s32 b;
};

void func_0013CC48(Span_CC48* p, s32 n)
{
    if (n == 0) {
        n = p->b;
        if (n == 0) {
            return;
        }
    }
    p->a += n;
    p->b -= n;
}

void func_001F5A58(void* dst, void* src, s32 n);

s32 func_0013CC80(MemoryReader* self, s32 want, void* dst)
{
    s32 n = self->remain;
    u8* base = self->base;
    s32 pos = self->pos;
    if (want < n) {
        n = want;
    }
    func_001F5A58(dst, base + pos, n);
    self->pos += n;
    self->remain -= n;
    return n;
}

int func_0013CCE8() {
	return 0;
}

LINKER_REMNANT(func_0013CCF0);
