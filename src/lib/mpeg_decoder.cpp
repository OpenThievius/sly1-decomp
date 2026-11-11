// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's decoder front end, from 0x20ADA0 to 0x20C1A0, built whole
// (config/us/files.tsv): the library's initialisation (func_0020ADA0), the decoder's creation,
// reset and deletion and the setters the game calls (func_0020AE40 to func_0020B168), its message
// queue, ring buffer and error reporting, the picture loop (func_0020B2E8 to func_0020B790), the
// sequence header and the extensions it reads (func_0020B9F0 to func_0020C168), and the IPU's DMA
// stop and restart around a picture (func_0020C178, func_0020C188). One file between two edges,
// with no evidence of a boundary inside it; it could be several. Its .rodata is its messages and
// the jump table of func_0020B2E8, its .data the library's identification string and the default
// quantiser matrices. Written for this project from retail's code.
#include "common.h"
#include "asm_func.h"

// The library's identification string, 16 characters without a terminator.
char D_0027AF70[16] = { 'P', 's', 'I', 'I', 'l', 'i', 'b', 'm', 'p', 'e', 'g', ' ', '2', '4', '2', '0' };

// The default quantiser matrices: intra, and non-intra (all 16).
u8 D_0027AF80[64] = { 0x08, 0x10, 0x10, 0x13, 0x10, 0x13, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x1a, 0x18, 0x1a, 0x1b, 0x1b, 0x1b, 0x1a, 0x1a, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b, 0x1d, 0x1d, 0x1d, 0x22, 0x22, 0x22, 0x1d, 0x1d, 0x1d, 0x1b, 0x1b, 0x1d, 0x1d, 0x20, 0x20, 0x22, 0x22, 0x25, 0x26, 0x25, 0x23, 0x23, 0x22, 0x23, 0x26, 0x26, 0x28, 0x28, 0x28, 0x30, 0x30, 0x2e, 0x2e, 0x38, 0x38, 0x3a, 0x45, 0x45, 0x53 };
u8 D_0027AFC0[64] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };

s32 DisableInterrupts(void);
s32 EnableInterrupts(void);
void ResetIpu(void);

void InitMpegLibrary(void) {
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 &= 0xFFFFFEFF;
    *(volatile u32*)0x1000B400 &= 0xFFFFFEFF;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    ResetIpu();
}

struct Outer_20AE40 {
    s32 f0; s32 f4; s32 f8; s32 pad0C;
    s64 f10; s64 f18; s64 f20; s64 f28; s64 f30; s64 f38;
    s32 f40;
};
struct Plane_20AE40 { u8 data[0x68]; };
struct Ring_20AE40 { u8* start; u32 size; u8* head; u8* tail; };
struct Inner_20AE40 {
    s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; s32 f1C;
    s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30; s32 f34; s32 f38; s32 f3C;
    s32 f40; s32 f44; s32 f48; s32 f4C; s32 f50; s32 f54; s32 f58; s32 f5C;
    s32 f60; s32 f64; s32 f68; s32 f6C; s32 f70; s32 pad74; s64 f78; s32 f80; s32 pad84;
    s64 f88; s32 f90; s32 f94; s32 f98; s32 f9C; s32 fA0; s32 fA4; s32 fA8; s32 fAC;
    s32 fB0; s32 fB4; s32 fB8; s32 fBC; s32 fC0; s32 fC4; s32 fC8; s32 fCC;
    s32 fD0; s32 fD4; s32 fD8; s32 fDC; s32 fE0; s32 fE4; s32 fE8; s32 fEC;
    s64 fF0; s32 fF8; s32 fFC; s32 f100; s32 f104;
    Ring_20AE40 ring;
    u8 pad118[0x1B8 - 0x118];
    Plane_20AE40* planes[3][4];
    Plane_20AE40 plane[9];
    u8 pad590[0x81C - 0x590];
    s32 f81C;
    u8 pad820[0x84C - 0x820];
    s32 f84C;
    s32 f850;
    s32 f854;
    Outer_20AE40* f858;
};

void* FillMemory(s32 dst, s32 c, u32 n);
s32 ReportMpegError(Inner_20AE40* a, const char* msg);
void InitMpegRing(Ring_20AE40* r, u8* start, u32 size);
s32 AllocateFromMpegRing(Inner_20AE40* a, Ring_20AE40* r, u32 size, u32 align);
void func_0020B810(Inner_20AE40* a);
void ResetMpegDecoder(Outer_20AE40* a);
s32 ReleaseMpegPictures(Outer_20AE40* a);
void func_0020B258(Ring_20AE40* r);
void SaveMpegDmaState(void);
void RestoreMpegDmaState(void);

s32 CreateMpegDecoder(Outer_20AE40* out, s32 mem, u32 size)
{
    FillMemory(mem, 0, size);
    Inner_20AE40* in = (Inner_20AE40*)(((u32)(mem + 3) >> 2) << 2);
    s32 diff = (s32)in - mem;
    u32 rest = size - diff;
    if (rest < 0x10C0) {
        ReportMpegError(in, "The size of work area is too small");
        return 0;
    }
    out->f40 = (s32)in;
    rest -= 0x10C0;
    InitMpegRing(&in->ring, (u8*)in + 0x10C0, rest);
    out->f0 = 0;
    out->f4 = 0;
    out->f8 = 0;
    out->f10 = -1;
    out->f18 = -1;
    out->f20 = 0;
    out->f28 = -1;
    out->f30 = -1;
    out->f38 = 0;
    in->fB4 = 0;
    in->fB8 = 0;
    in->fBC = 0;
    in->fC0 = 0;
    in->fC4 = 0;
    in->fC8 = 0;
    in->fCC = 0;
    in->fD0 = 0;
    in->fD4 = 0;
    in->fD8 = 0;
    in->fDC = 0;
    in->fE0 = 0;
    in->fE4 = 0;
    in->fE8 = 0;
    in->fF8 = 0;
    in->f0C = 0;
    in->f14 = 0;
    in->f2C = 0;
    in->f34 = 0;
    in->f3C = 0;
    in->fF0 = -1;
    in->f1C = (s32)SaveMpegDmaState;
    in->f24 = (s32)RestoreMpegDmaState;
    s32 r278 = AllocateFromMpegRing(in, &in->ring, 0x600, 8);
    in->f48 = 0;
    in->fFC = 0;
    in->f100 = 0;
    in->f104 = 0;
    in->f70 = 0;
    in->f78 = 0;
    in->f80 = -1;
    in->f88 = 0;
    in->f90 = 0;
    in->fAC = 0;
    in->f94 = -1;
    in->f98 = -1;
    in->f9C = -1;
    in->f858 = out;
    in->f44 = r278;
    in->fB0 = 1;
    func_0020B810(in);
    ResetMpegDecoder(out);
    ReleaseMpegPictures(out);
    in->planes[0][0] = &in->plane[0];
    in->planes[0][1] = &in->plane[1];
    in->planes[0][3] = &in->plane[2];
    in->planes[1][0] = &in->plane[3];
    in->planes[1][1] = &in->plane[4];
    in->planes[1][3] = &in->plane[5];
    in->planes[2][0] = &in->plane[6];
    in->planes[2][1] = &in->plane[7];
    in->planes[2][3] = &in->plane[8];
    func_0020B258(&in->ring);
    in->f850 = -1;
    in->f854 = 0;
    in->f84C = 0;
    in->f81C = 0x70003600;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

s32 DeleteMpegDecoder(void) {
	return 1;
}

LINKER_REMNANT(func_0020B050);

struct Obj_20B058 { u8 pad[0x40]; u8* state; };

s32 RunMpegPictureLoop(Obj_20B058* obj);

s32 DecodeMpegPicture(Obj_20B058* obj, u32 a1, s32 a2)
{
    u8* st = obj->state;
    *(s32*)(st + 0xB0) = 1;
    *(u32*)(st + 0xD8) = (a1 & 0xFFFFFFFu) | 0x20000000u;
    *(s32*)(st + 0xE4) = a2;
    *(s32*)(st + 0xE0) = 0;
    *(s32*)(st + 0xDC) = 0;
    return RunMpegPictureLoop(obj);
}

LINKER_REMNANT(func_0020B0A0);

struct Device_20B0B0 {
	u8 padding[0x40];
	void* state;
};

s32 GetMpegDecoderStatus(Device_20B0B0* device) {
	return *(s32*)device->state;
}

void func_0020B780(void* s);
void func_0020B870(void* s);
struct S_20B0C0 { u8 pad0[8]; s32 f8; u8 pad[0x34]; u8* st; };
void ResetMpegDecoder(S_20B0C0* d) {
    u8* s = d->st;
    *(s32*)s = 0;
    *(s32*)(s + 4) = 0;
    *(s32*)(s + 8) = 0;
    d->f8 = 0;
    *(s32*)(s + 0xAC) = 0;
    *(s32*)(s + 0x80) = -1;
    func_0020B870(s);
    *(s32*)(s + 0x118) = 0;
    func_0020B780(s);
}

struct Device_20B110 {
	u8 padding[0x40];
	u8* state;
};

struct DeviceState_20B110 {
	u8 padding[0x1B8];
	void* a;
	void* d;
	u8 padding2[8];
	void* b;
	void* e;
	u8 padding3[8];
	void* c;
	void* f;
};

s32 ReleaseMpegPictures(Device_20B110* device) {
	DeviceState_20B110* state = (DeviceState_20B110*)device->state;
	if (state->a) *(s32*)((char*)state->a + 0x28) = 0;
	if (state->b) *(s32*)((char*)state->b + 0x28) = 0;
	if (state->c) *(s32*)((char*)state->c + 0x28) = 0;
	if (state->d) *(s32*)((char*)state->d + 0x28) = 0;
	if (state->e) *(s32*)((char*)state->e + 0x28) = 0;
	if (state->f) *(s32*)((char*)state->f + 0x28) = 0;
	return 1;
}

struct Obj_20B168 { u8 pad[0x40]; u32* values; };

s32 SetMpegCallback(Obj_20B168* obj, s32 index, s32 value, s32 second)
{
    u32* array = obj->values;
    u32* current = array + 3;
    u32 offset = index * 2;
    current += offset;
    array += offset;
    array[4] = second;
    s32 old = *current;
    *current = value;
    return old;
}

struct Ctx_0020B190;
typedef s32 (*Fn_0020B190)(Ctx_0020B190*, s32*, s32);
struct Ent_0020B190 { Fn_0020B190 fn; s32 arg; };
struct Tab_0020B190 { u8 pad[0xC]; Ent_0020B190 e[1]; };
struct Ctx_0020B190 { u8 pad[0x40]; Tab_0020B190* table; };
s32 RunMpegCallback(Ctx_0020B190* p, s32* idx) {
    s32 r = 0;
    if (p != 0) {
        Tab_0020B190* t = p->table;
        if (t != 0) {
            Fn_0020B190 fn = t->e[*idx].fn;
            if (fn != 0) {
                r = fn(p, idx, t->e[*idx].arg);
            }
        }
    }
    return r;
}

struct Q_0020B1E0;
s32 RunMpegCallback(Q_0020B1E0* q, s32* out);

s32 RunMpegStallCallback(Q_0020B1E0* q)
{
    s32 flag[8];
    flag[0] = 1;
    return RunMpegCallback(q, flag);
}

LINKER_REMNANT(func_0020B208);

struct Item_20B240 { s32 a; s32 b; s32 c; s32 d; };
void InitMpegRing(Item_20B240* item, s32 value, s32 field)
{
    item->a = value;
    item->b = field;
    item->c = value;
    item->d = value;
}

struct Field_20B258 {
	u8 padding[8];
	s32 f8;
	s32 fc;
};

s32 func_0020B258(Field_20B258* field) {
	return field->fc = field->f8;
}

s32 func_0020B268(s32* item)
{
    s32 value = item[3];
    item[2] = value;
    return value;
}

struct Owner_0020B278;

struct Pool_0020B278 {
    u32 f00;
    u32 f04;
    u32 f08;
};


s32 ReportMpegError(Owner_0020B278* owner, const char* p);

s32 AllocateFromMpegRing(Owner_0020B278* owner, Pool_0020B278* pool, u32 offset, u32 align)
{
    u32 base;
    u32 end;

    base = (pool->f08 + align - 1) / align;
    base = base * align;
    end = base + offset;
    if (pool->f00 + pool->f04 >= end) {
        pool->f08 = end;
        return base;
    }
    (void)ReportMpegError(owner, "work area size is too small");
    return 0;
}

struct Ctx_20B2E8 {
    s32 f0;
    u8 pad0[0x94 - 4];
    s32 f94, f98, f9C, fA0, fA4, fA8;
    u8 pad1[0xD4 - 0xAC];
    s32 fD4;
    s32 fD8;
    u8 pad2[0x174 - 0xDC];
    s32 f174;
    u8 pad3[0x820 - 0x178];
    s32 f820;
    u8 pad4[0x848 - 0x824];
    s32 f848;
};
struct Self_20B2E8 { u8 pad[0x40]; Ctx_20B2E8* ctx; };

void ReportMpegErrorFormat(Ctx_20B2E8* c, s32 msg, s32 flags);
s32 ParseMpegHeaders(Ctx_20B2E8* c);
s32 func_0020B570(Self_20B2E8* self, s32 a, s32 b);
s32 func_0020B718(Self_20B2E8* self);

s32 RunMpegPictureLoop(Self_20B2E8* self)
{
    s32 s3 = 1;
    s32 s2 = 0;
    Ctx_20B2E8* c = self->ctx;
    c->f0 = 0;
    if ((c->fD8 & 0x3F) != 0) {
        ReportMpegErrorFormat(c, (s32)"image buffer needs to be aligned to 64byte boundary(0x%08x)", c->fD8);
        return -1;
    }
    c->f820 = 0;
    for (;;) {
        if (s2 != -1) {
            do {
                s3 = ParseMpegHeaders(c);
                if (s3 == 0) break;
                if (c->f174 == c->fD4) break;
            } while (c->f848 != 0);
        }
        switch (s3) {
        case 0:
            (void)func_0020B718(self);
            c->f0 = 1; 
            break;
        case 1:
            c->fA8 = 0;
            c->fA4 = 0;
            c->fA0 = 0;
            s2 = func_0020B570(self, 0, c->f94);
            c->fA0++;
            break;
        case 2:
            s2 = func_0020B570(self, c->fA4, c->f98);
            c->fA4++;
            break;
        case 3:
        case 4:
            s2 = func_0020B570(self, c->fA8, c->f9C);
            c->fA8++;
            break;
        }
        if (c->f820 != 0 || c->f0 != 0) break;
    }
    return 1;
}

struct Ent_20B458 {
    u8 pad0[0x4];
    s32 f4;
    s32 f8;
    u8 pad1[0xAC - 0xC];
    s32 fAC;
    u8 pad2[0x118 - 0xB0];
    s32 f118;
    s32 f11C;
    s32 f120;
    u8 pad3[0x174 - 0x124];
    s32 f174;
};
struct Ctx_20B458 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x40 - 0xC];
    Ent_20B458* f40;
};
struct Ent_arg_20B458 { u32 v; };

extern s32 func_002101F0(Ent_20B458* e, u32 a1);
extern s32 DecodePictureData(Ent_20B458* e);
extern void func_00210160(Ent_20B458* e, s32 a1, s32 a2);
extern s32 RunMpegStallCallback(Ctx_20B458* c);

struct Ent_ops_20B458 {
    static s8 Ready(Ent_20B458* e)
    {
        s32 t = func_002101F0(e, 0);
        s8 r = 0;
        if (t != 0) {
            r = DecodePictureData(e) != 0;
        }
        return r;
    }
};

s32 func_0020B458(Ctx_20B458* s1, s32 a1, s32 a2)
{
    s32 s2;
    Ent_20B458* s0 = s1->f40;
    s32 s3 = 0;

    if (a2 == -1 || a1 < a2) {
        if (s0->f8 == 0) {
            s1->f8 = 0;
            s0->f8 = 1;
        }
        s2 = Ent_ops_20B458::Ready(s0);
    } else {
        s2 = func_002101F0(s0, 0);
        s3 = 1;
        (void)RunMpegStallCallback(s1);
    }
    func_00210160(s0, s0->f118, s0->f4);
    if (s0->f174 == 3) {
        ;
    } else if (s3 == 0) {
        s0->f120 = (s0->f120 == 0);
    }
    s1->f8 = s0->f118 - s0->fAC;
    if (s0->f120 == 0) {
        s0->f118 = s0->f118 + 1;
        s0->f4 = s0->f4 + 1;
    }
    return s2;
}

struct Child_0020B570 { u8 pad[0x174]; s32 kind; };
struct Owner_0020B570 {
    u8 pad[0x40];
    Child_0020B570* child;
};

s32 func_0020B458(Owner_0020B570* self, s32 a, s32 b);
s32 func_0020B5B8(Owner_0020B570* self, s32 a, s32 b);

s32 func_0020B570(Owner_0020B570* self, s32 a, s32 b)
{
    if (self->child->kind != 3) {
        return func_0020B5B8(self, a, b);
    }
    return func_0020B458(self, a, b);
}

struct Sub_20B5B8 {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 pad0C[0xA0];
    s32 fAC;
    u8 pad1[0x24];
    s32 fD4;
    u8 pad2[0x40];
    s32 f118;
    s32 f11C;
    s32 f120;
    u8 pad3[0x50];
    s32 f174;
};

struct Ctx_20B5B8 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x34];
    Sub_20B5B8* sub;
};

s32 func_002101F0(Sub_20B5B8* sub, s32 flag);
s32 DecodePictureData(Sub_20B5B8* sub);
s32 ParseMpegHeaders(Sub_20B5B8* sub);
s32 func_0020B718(Ctx_20B5B8* ctx);
void func_00210160(Sub_20B5B8* sub, s32 a1, s32 a2);
s32 RunMpegStallCallback(Ctx_20B5B8* ctx);

s32 func_0020B5B8(Ctx_20B5B8* self, s32 a1, s32 a2)
{
    s32 s3 = 0;
    Sub_20B5B8* s0;
    s32 s1;
    s32 s4;
    s32 t;
    s32 r;

    s0 = self->sub;
    s0->f120 = 0;
    if (a2 == -1 || a1 < a2) {
        s3 = 1;
    }
    if (s0->f8 == 0) {
        self->f8 = 0;
        s0->f8 = 1;
    }
    if (func_002101F0(s0, 0) != 0) {
        if (s3 != 0) {
            (void)DecodePictureData(s0);
        }
    }
    s1 = 1;
    s0->f120 = s1;
    if (ParseMpegHeaders(s0) == 0) {
        (void)func_0020B718(self);
        s0->f0 = s1;
        return 0;
    }
    t = (s0->fD4 ^ 1) != 0 ? s1 : 2;
    if (s0->f174 != t) {
        return -1;
    }
    r = func_002101F0(s0, 1);
    s32 u = 0;
    if (r != 0) {
        u = s1;
    }
    s4 = 0;
    if (u != 0) {
        if (s3 != 0) {
            s4 = (DecodePictureData(s0) != 0) ? s1 : 0;
        }
    }
    func_00210160(s0, s0->f118, s0->f4);
    s0->f120 = 0;
    self->f8 = s0->f118 - s0->fAC;
    s0->f118 = s0->f118 + 1;
    s0->f4 = s0->f4 + 1;
    if (s3 == 0) {
        RunMpegStallCallback(self);
    }
    return s4;
}

struct Inner_20B718 {
    u8 pad0[4];
    s32 a;
    s32 b;
    u8 pad1[0xA0];
    s32 c;
    u8 pad2[0x68];
    s32 d;
};

struct Obj_20B718 {
    u8 pad0[8];
    s32 out;
    u8 pad1[0x34];
    Inner_20B718* inner;
};

extern void func_0020B790(Inner_20B718* self);

s32 func_0020B718(Obj_20B718* self)
{
    s32 r = 0;
    Inner_20B718* in = self->inner;

    if (in->a != 0) {
        if (in->b != 0) {
            func_0020B790(in);
            self->out = in->d - in->c;
            in->a = 0;
            r = 1;
        }
    }
    return r;
}

void SetIpuMpeg1Mode(s32 a);
struct S_20B780 { u8 pad[0x848]; s32 f; };
void func_0020B780(S_20B780* s) {
    s->f = 0;
    SetIpuMpeg1Mode(1);
}

struct Obj_0020B790 {
    u8 pad000[0x118];
    s32 f118;
    s32 f11C;
    s32 f120;
    u8 pad124[0x174 - 0x124];
    s32 f174;
    u8 pad178[0x1BC - 0x178];
    s32 f1BC;
    u8 pad1C0[0x1CC - 0x1C0];
    s32 f1CC;
    u8 pad1D0[0x1DC - 0x1D0];
    s32 f1DC;
};

s32 ReportMpegError(struct Obj_0020B790 *self, const char *msg);
void func_00210970(struct Obj_0020B790 *self, s32 a1, s32 a2);
void func_00210A80(struct Obj_0020B790 *self, s32 a1, s32 a2, s32 a3);

void func_0020B790(struct Obj_0020B790 *self)
{
    s32 n = self->f118;
    if (self->f120 != 0)
        ReportMpegError(self, "the second field is missing");
    else if (self->f174 == 3)
        func_00210970(self, self->f1BC, n - 1);
    else
        func_00210A80(self, self->f1CC, self->f1DC, n - 1);
    self->f120 = 0;
}

struct Dev_20B810 {
    u8 pad0[0x590];
    u8* f590;
    u8* f594;
    u8 pad1[0x6D0 - 0x598];
    u8* f6D0;
    u8* f6D4;
    u8 pad2[0x810 - 0x6D8];
    u32 f810;
};

void SetIpuMpeg1Mode(s32 a);

void func_0020B810(Dev_20B810* self)
{
    u8* spr = (u8*)0x70000000;
    SetIpuMpeg1Mode(1);
    self->f590 = spr;
    self->f594 = spr + 0x1800;
    self->f6D0 = spr + 0x1B00;
    self->f6D4 = spr + 0x3300;
    self->f810 = 0;
}

s32 DisableInterrupts(void);
s32 EnableInterrupts(void);
u32 SyncIpu(s32 a, s32 b);

struct Chan_20B870 {
    u8 pad0[0x1B0];
    s32 f1B0;
    u8 pad1[0x818 - 0x1B4];
    s32 f818;
};

void func_0020B870(Chan_20B870* c) {
    c->f818 = 1;
    c->f1B0 = 0;
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = 0;
    *(volatile u32*)0x1000B400 = 0;
    *(volatile u32*)0x1000D400 = 0;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    *(volatile u32*)0x1000D420 = 0;
    *(volatile u32*)0x10002010 = 0x40000000;
    SyncIpu(0, 0);
}

s32 PrintFormatted(const char* fmt, s32 msg);

void PrintMpegError(s32 msg) {
    PrintFormatted("[MPEG ERROR]%s\n", msg);
}

struct Buf_0020B940;
struct Ctx_0020B940;
s32 FormatToString(Buf_0020B940* dst, const char* fmt, ...);
s32 ReportMpegError(Ctx_0020B940* self, char* buf);

void ReportMpegErrorFormat(Ctx_0020B940* self, const char* fmt)
{
    char buf[0x100];
    FormatToString((Buf_0020B940*)buf, fmt);
    ReportMpegError(self, buf);
}

struct Self_20B978 {
    u8 pad0[0xC];
    s32 f0C;
    u8 pad1[0x848];
    void* f858;
};

struct Pair_20B978 {
    s32 a;
    s32 b;
};

struct Sub_20B978;
struct Arg_20B978;

s32 RunMpegCallback(Sub_20B978* sub, Pair_20B978* pair);
s32 PrintMpegError(Arg_20B978* arg);

s32 ReportMpegError(Self_20B978* self, s32 value)
{
    Pair_20B978 pair;

    if (self->f858 != 0 && self != 0 && self->f0C != 0) {
        pair.a = 0;
        pair.b = value;
        return RunMpegCallback((Sub_20B978*)self->f858, &pair);
    }
    return PrintMpegError((Arg_20B978*)value);
}

struct Item_20B9D0 { u8 pad[4]; s32 x; s32 y; s32 left; s32 top; };
s32 func_0020B9D0(Item_20B9D0* item, s32 x, s32 y)
{
    item->x = x;
    item->y = y;
    item->left = x >> 4;
    item->top = y >> 4;
    return 1;
}

struct Dec_20B9F0 {
    u8 pad0[0xD4];
    s32 fD4;
    u8 pad1[0x124 - 0xD8];
    u32 f124;
    s32 f128;
    u8 pad2[0x134 - 0x12C];
    u32 f134;
    u32 f138;
    u8 pad3[0x840 - 0x13C];
    u32 f840;
    u32 f844;
    u8 pad4[0x858 - 0x848];
    void* f858;
};


u32 ReadIpuBits(Dec_20B9F0* d, s32 bits);
s32 ReportMpegError(Dec_20B9F0* d, const char* msg);
s32 WaitIpuCommandDone(Dec_20B9F0* d);
void SendIpuCommand(Dec_20B9F0* d, u32 value);
void func_0020BEA0(Dec_20B9F0* d, u32 value, u8* table);
void ReadExtensionsAndUserData(Dec_20B9F0* d);
s32 func_0020BB18(void* p);

void ReadSequenceHeader(Dec_20B9F0* d) {
    d->fD4 = 0;
    u32 v = ReadIpuBits(d, 0x20);
    d->f124 = v >> 20;
    d->f128 = (v >> 8) & 0xFFF;
    if (d->f128 > 0xAF0) {
        ReportMpegError(d, "vertical size > 2800");
    }
    v = ReadIpuBits(d, 0x1E);
    d->f134 = v >> 12;
    d->f138 = (v >> 1) & 0x3FF;
    d->f840 = ReadIpuBits(d, 1);
    if (d->f840) {
        WaitIpuCommandDone(d);
        SendIpuCommand(d, 0x50000000);
        WaitIpuCommandDone(d);
    } else {
        func_0020BEA0(d, 0x50000000, D_0027AF80);
    }
    d->f844 = ReadIpuBits(d, 1);
    if (d->f844) {
        WaitIpuCommandDone(d);
        SendIpuCommand(d, 0x58000000);
        WaitIpuCommandDone(d);
    } else {
        func_0020BEA0(d, 0x58000000, D_0027AFC0);
    }
    ReadExtensionsAndUserData(d);
    func_0020BB18(d->f858);
}

INCLUDE_ASM(func_0020BB18);

void func_0020BDC0(u32* a0, u32* a1, u32* a2, u32* a3, u32* a4, u32* a5, u32* a6, u32* a7, u32* p9, u32 p10, u32 p11, u32 p12, s32 p13, s32 p14)
{
    u32 mask = 0x0FFFFFFF;
    u32 bits = 0x20000000;
    s32 n = (p13 * p14) / 512;
    *a0 = (p10 & mask) | bits;
    *a1 = (p11 & mask) | bits;
    *a2 = (p12 & mask) | bits;
    *a3 = (p10 & mask) | bits;
    *a4 = (p11 & mask) | bits;
    *a5 = (p12 & mask) | bits;
    u32 y2 = n * 0x180;
    y2 = ((y2 + p10) & mask) | bits;
    u32 u2 = n * 0x180;
    u2 = ((u2 + p11) & mask) | bits;
    u32 v2 = n * 0x180;
    v2 = ((v2 + p12) & mask) | bits;
    *a6 = y2;
    *a7 = u2;
    *p9 = v2;
}

struct Obj_20BEA0 { u8 pad000[0x858]; u32 field858; };
struct Handle_20BEA0;
struct Req_20BEA0 { s32 mode; s32 pad[7]; };
s32 RunMpegCallback(Handle_20BEA0* h, Req_20BEA0* out);
void WaitIpuCommandDone(Obj_20BEA0* self);
void SendIpuCommand(Obj_20BEA0* self, u32 value);
s32 DisableInterrupts(void);
s32 EnableInterrupts(void);

void func_0020BEA0(Obj_20BEA0* obj, u32 value, u32 mask)
{
    Req_20BEA0 req;
    req.mode = 2;

    RunMpegCallback((Handle_20BEA0*)obj->field858, &req);
    WaitIpuCommandDone(obj);
    *(volatile u32*)0x10002000 = 0;
    WaitIpuCommandDone(obj);
    (void)DisableInterrupts();
    *(volatile u32*)0x1000B410 = mask & 0x0FFFFFFF;
    *(volatile u32*)0x1000B420 = 4;
    *(volatile u32*)0x1000B400 = 0x101;
    (void)EnableInterrupts();
    SendIpuCommand(obj, value);
    WaitIpuCommandDone(obj);
    req.mode = 3;
    RunMpegCallback((Handle_20BEA0*)obj->field858, &req);
}

struct Obj_20BF78 {
    u8 pad0[0x124];
    u32 field124;
    u32 field128;
    u8 pad12C[0x8];
    u32 field134;
    u32 field138;
    u32 field13C;
    u32 field140;
    u8 pad144[0x704];
    u32 field848;
};

u32 SetIpuMpeg1Mode(u32 value);
u32 ReadIpuBits(struct Obj_20BF78 *self, u32 n);
s32 ReportMpegError(struct Obj_20BF78 *self, const void *p);

void func_0020BF78(struct Obj_20BF78 *self)
{
    u32 s2;
    u32 s0;
    u32 s3;
    u32 s4;
    u32 s5;

    self->field848 = 1;
    SetIpuMpeg1Mode(0);
    s2 = ReadIpuBits(self, 0x1C);
    s5 = (s2 >> 1) & 0xFFF;
    self->field140 = (s2 >> 17) & 3;
    s4 = (s2 >> 13) & 3;
    s3 = (s2 >> 15) & 3;
    if (self->field140 != 1) {
        ReportMpegError(self, "_chroma_format needs to be 1: 420");
    }
    self->field13C = (s2 >> 19) & 1;
    s0 = s2 >> 20;
    s2 = ReadIpuBits(self, 0x10) >> 8;
    if (s0 != 0x48 && s0 != 0x58 && s0 != 0x44) {
        ReportMpegError(self, "Unsupported profile/level");
    }
    self->field124 = (s3 << 12) | (self->field124 & 0xFFF);
    self->field128 = (s4 << 12) | (self->field128 & 0xFFF);
    self->field134 += s5 << 18;
    self->field138 += s2 << 10;
}

struct Node_20C0A8;

s32 ReadIpuBits(struct Node_20C0A8* a, s32 b);

struct Node_20C0A8 {
    u8 pad00[0x144];
    s32 f144;
    s32 f148;
    s32 f14C;
};

void func_0020C0A8(struct Node_20C0A8* self)
{
    ReadIpuBits(self, 3);
    if (ReadIpuBits(self, 1) != 0) {
        ReadIpuBits(self, 8);
        ReadIpuBits(self, 8);
        self->f144 = ReadIpuBits(self, 8);
    }
    self->f148 = ReadIpuBits(self, 0xE);
    ReadIpuBits(self, 1);
    self->f14C = ReadIpuBits(self, 0xE);
}

struct Obj_0020C138;
s32 ReportMpegError(Obj_0020C138* self, const void* table);

void RejectSequenceScalableExtension(Obj_0020C138* self)
{
    ReportMpegError(self, "_sequenceScalableExtension() is not implemented");
}

struct Obj_0020C148;
s32 ReportMpegError(Obj_0020C148* self, const void* table);

void RejectUnknownExtension(Obj_0020C148* self)
{
    ReportMpegError(self, "Unknown Extension");
}

struct Obj_0020C158;
s32 ReportMpegError(Obj_0020C158* self, const void* table);

void RejectSpatialScalableExtension(Obj_0020C158* self)
{
    ReportMpegError(self, "_pictureSpatialScalableExtension is not supported");
}

struct Obj_0020C168;
s32 ReportMpegError(Obj_0020C168* self, const void* table);

void RejectTemporalScalableExtension(Obj_0020C168* self)
{
    ReportMpegError(self, "_pictureTemporalScalableExtension is not supported");
}

struct Out_002118A0;
struct Obj_0020C178 { u8 pad00[0x40]; Out_002118A0* f40; };
void SaveIpuDmaChannels(Out_002118A0* out);

void SaveMpegDmaState(Obj_0020C178* self)
{
    SaveIpuDmaChannels((Out_002118A0*)((u8*)self->f40 + 0x4C));
}

struct Ctx_211988;
struct Obj_0020C188 { u8 pad00[0x40]; u8* f40; };
void RestoreIpuDmaChannels(Ctx_211988* s0);

void RestoreMpegDmaState(Obj_0020C188* self)
{
    RestoreIpuDmaChannels((Ctx_211988*)(self->f40 + 0x4C));
}
