// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// NEAR: retail saves registers in 8 bytes (sd); retail puts the sb before the loop bnez and the state return tail differs.

struct Obj_204AA8;
struct Lock_204AA8;
struct Ctx_204AA8 { s32 kind; void* a; void* b; u8 bytes[6]; u8 pad1A[2]; s32 state; };

extern Ctx_204AA8 D_0062ACC0;
struct Sema_2040E8 {
    u8 pad00[0x24];
    s32 f24;
};
extern Sema_2040E8 D_0062AA80[];

s32 func_001F8290(Lock_204AA8* l, s32 a, s32 b, Ctx_204AA8* c, s32 d, Ctx_204AA8* e, s32 f, s32 g, s32 h);
void func_00204610(Obj_204AA8* o, void* q, s32 n);

s32 func_00204AA8(Obj_204AA8* p, void* q, u8* src)
{
    Ctx_204AA8* c = &D_0062ACC0;
    s32 i;

    c->kind = 8;
    c->a = p;
    c->b = q;
    i = 0;
    do {
        c->bytes[i] = src[i];
        i++;
    } while (i < 6);
    if (func_001F8290((Lock_204AA8*)D_0062AA80, 1, 0, c, 0x80, c, 0x80, 0, 0) < 0) return 0;
    if (c->state == 1) func_00204610(p, q, 2);
    return c->state;
}

struct Obj_204930 { u32 mode; u32 a; u32 b; u32 c; u32 d; u32 result; };


s32 func_001F8290(u8* p0, s32 a1, s32 a2, Obj_204930* a3, s32 a4, Obj_204930* a5, s32 a6, s32 a7, s32 a8);
s32 func_00204610(Obj_204930* obj, s32 a1, s32 a2);

s32 func_00204930(s32 a0, s32 a1, s32 a2, s32 a3)
{
    Obj_204930* obj = (Obj_204930*)((u8*)&D_0062ACC0);
    s32 status;
    s32 r;

    obj->c = a2;
    obj->d = a3;
    obj->mode = 6;
    obj->a = a0;
    obj->b = a1;
    r = func_001F8290((u8*)D_0062AA80, 1, 0, obj, 0x80, obj, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    status = obj->result;
    if (status == 1) {
        (void)func_00204610((Obj_204930*)a0, a1, 2);
        status = obj->result;
    }
    return status;
}

struct Ctx_00204DB8 { s32 f00; u8 pad[8]; s32 f0C; };
struct Q_00204DB8;
s32 func_001F8290(Q_00204DB8* q, s32 a, s32 b, Ctx_00204DB8* c, s32 d, Ctx_00204DB8* e, s32 f, s32 g, s32 h);

s32 func_00204DB8(void)
{
    Ctx_00204DB8* ctx = (Ctx_00204DB8*)((u8*)&D_0062ACC0);
    ctx->f00 = 0x12;
    s32 r = func_001F8290((Q_00204DB8*)D_0062AA80, 1, 0, ctx, 0x80, ctx, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    return ctx->f0C;
}


s32 D_0027AE80;
extern s32 D_0027AE84;
extern const char D_0024F780[];
extern const char D_0024F7A8[];

s32 func_001F80C0(Sema_2040E8* s, u32 flags, s32 arg);
s32 func_00204DB8(void);
s32 func_00204228(void* arg);
s32 func_001E1F10(const char* fmt, ...);

s32 func_002040E8(void* arg)
{
    D_0027AE80 = 1;
    while (func_001F80C0(&D_0062AA80[0], 0x80000100, 0), D_0062AA80[0].f24 == 0) {
        for (s32 i = 0x10000; i != -1; i--) {
        }
    }
    for (;;) {
        func_001F80C0(&D_0062AA80[1], 0x80000101, 0);
        if (D_0062AA80[1].f24 != 0) {
            break;
        }
        for (s32 i = 0x10000; i != -1; i--) {
        }
    }
    s32 r = func_00204DB8();
    s32 hi = r >> 8;
    if (hi != 4) {
        if (D_0027AE84 != 0) {
            PrintFormatted(D_0024F780);
            PrintFormatted(D_0024F7A8, 4, 0, hi, r & 0xFF);
        }
        return 0;
    }
    return func_00204228(arg);
}

// The pad library's state of each port's 4 slots: the slot's buffer, whether it is open, and two
// more words the setup clears.
struct Slot_2044B0 { u8* buffer; u8 pad[0x0C]; s32 open; s32 f14; s32 f18; };
struct Ctx_204228 { s32 kind; u8 pad[8]; s32 result; s32 f10; };
struct Lock_204228;

extern Slot_2044B0 D_0062AAD0[][4];

s32 func_001F8290(Lock_204228* l, s32 a, s32 b, Ctx_204228* c, s32 d, Ctx_204228* e, s32 f, s32 g, s32 h);

s32 func_00204228(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        D_0062AAD0[0][i].open = 0;
        D_0062AAD0[0][i].f18 = 0;
        D_0062AAD0[0][i].f14 = 0;
        D_0062AAD0[1][i].open = 0;
        D_0062AAD0[1][i].f18 = 0;
        D_0062AAD0[1][i].f14 = 0;
    }
    (*(Ctx_204228*)&D_0062ACC0).kind = 0x10;
    (*(Ctx_204228*)&D_0062ACC0).f10 = 0;
    if (func_001F8290((Lock_204228*)((u8*)&D_0062AA80), 1, 0, ((Ctx_204228*)&D_0062ACC0), 0x80, ((Ctx_204228*)&D_0062ACC0), 0x80, 0, 0) < 0) {
        return 0;
    }
    return (*(Ctx_204228*)&D_0062ACC0).result;
}


struct Request_204C38 { s32 count; s32 owner; s32 channel; s32 data; s32 state; };
struct Lock_204C38;
struct Owner_204C38;
s32 func_001F8290(Lock_204C38* l, s32 a, s32 b, Request_204C38* c, s32 d, Request_204C38* e, s32 f, s32 g, s32 h);
s32 func_00204610(Owner_204C38* owner, s32 channel, s32 n);

s32 func_00204C38(Owner_204C38* owner, s32 channel, s32 data)
{
    Request_204C38* request = (Request_204C38*)&D_0062ACC0;
    request->data = data;
    request->count = 10;
    request->owner = (s32)owner;
    request->channel = channel;
    s32 status = func_001F8290((Lock_204C38*)D_0062AA80, 1, 0, request, 0x80, request, 0x80, 0, 0);
    if (status < 0)
        return 0;
    s32 state = request->state;
    if (state == 1) {
        func_00204610(owner, channel, 2);
        state = request->state;
    }
    return state;
}

extern const char D_0024F780[40] = "libpad: Module version mismatch ";
extern const char D_0024F7A8[40] = "[libpad.a = %d.%d, padman.irx = %d.%d]\n";

// The two frames of a pad slot's buffer, the newer of which the readers below take. The second
// multiply of each slot's index is mult1, which the compiler issues to the EE's second pipeline.
struct Frame_2044B0 { u8 head[0x58]; s32 count; u8 pad5C[4]; s32 size; u8 pad64[0x0C]; u8 state; u8 mode; u8 pad72[0x0E]; };
void func_00204EC8(Frame_2044B0* a, Frame_2044B0* b);
void* func_001F5A58(void* dst, const void* src, s32 n);

Frame_2044B0* func_002044B0(s32 port, s32 slot)
{
    Frame_2044B0* frames = (Frame_2044B0*)D_0062AAD0[port][slot].buffer;
    s32 newer;
    func_00204EC8(frames, frames + 2);
    newer = frames[0].count < frames[1].count;
    return &frames[newer];
}

s32 func_00204510(s32 port, s32 slot, u8* data)
{
    Frame_2044B0* frame;
    if (D_0062AAD0[port][slot].open == 0)
        return 0;
    frame = func_002044B0(port, slot);
    func_001F5A58(data, frame, frame->size);
    return frame->size;
}

s32 func_00204590(s32 port, s32 slot)
{
    Frame_2044B0* frame;
    if (D_0062AAD0[port][slot].open == 0)
        return 0x63;
    frame = func_002044B0(port, slot);
    if (frame->state == 6) {
        if (frame->mode == 2)
            return 5;
    }
    return frame->state;
}

s32 func_00204610(s32 port, s32 slot, s32 value)
{
    if (D_0062AAD0[port][slot].open == 0)
        return 0;
    func_002044B0(port, slot)->mode = value;
    return 1;
}

u32 func_00204678(s32 port, s32 slot)
{
    if (D_0062AAD0[port][slot].open == 0)
        return 0;
    return func_002044B0(port, slot)->mode;
}

s32 func_00204B80(s32 port, s32 slot);

s32 func_00204CE8(s32 port, s32 slot)
{
    if (D_0062AAD0[port][slot].open == 0)
        return 0;
    return func_00204B80(port, slot) == 0x3FFFF;
}

s32 func_00204D48(s32 port, s32 slot)
{
    if (D_0062AAD0[port][slot].open == 0)
        return 0;
    return func_00204C38((Owner_204C38*)port, slot, 0xFFF);
}
