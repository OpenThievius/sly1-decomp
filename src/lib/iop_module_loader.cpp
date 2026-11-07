// SPDX-License-Identifier: AGPL-3.0-or-later
// An object of the kernel library from 0x1F9690 to 0x1F9AD8, built whole (config/us/files.tsv):
// a client of an IOP service over the command channel (0x80000006). func_001F9690 binds the
// client D_00628E00 once (D_002771CC, -1 until then) and keeps the service's version word in
// D_00628E28; func_001F9790 tells whether that word, the library's own ("2430", the end of
// D_00276970) and the string "...." D_002771D0 points to differ; func_001F9820 forgets the
// binding. func_001F9868 sends a request: a name of up to 0xFB characters and up to 0xFC bytes
// of data in the buffer D_00628C00, and returns the reply's size and its word; func_001F9A90
// sends one with the command 0.
#include "common.h"
#include "asm_func.h"

struct Blob_1F9868 { u8 b[0xFC]; };
struct Buf_1F9868 { s32 f0; s32 f4; Blob_1F9868 name; Blob_1F9868 data; };

s32 D_002771CC = -1;
const char* D_002771D0 = "....";
// A string no code reads.
extern const char D_0024EB88[] = "all";

static Buf_1F9868 D_00628C00 __attribute__((aligned(64)));
static u8 D_00628E00[0x28] __attribute__((aligned(64)));
static s32 D_00628E28;

extern char D_00276970[16];

s32 func_001F59C4(const void* a, const void* b, s32 n);
void* func_001F5A58(void* dst, const void* src, s32 n);
void func_001F5C0C(void* p, s32 value, s32 size);
s32 func_001F8290(u8* a, s32 b, s32 c, Buf_1F9868* d, s32 e, Buf_1F9868* f, s32 g, s32 h, s32 i);
void func_00201720(Blob_1F9868* dst, Blob_1F9868* src, s32 n);
s32 func_001F9690(void);

struct __attribute__((packed)) Word_1F9690 { u32 v; };

// A client of the command channel (src/lib/remote_call.cpp): 0x24 is set once it is bound.
struct Client_1F9690 {
    s32 pad[9];
    s32 bound;
};

s32 func_001F80C0(Client_1F9690* client, u32 cmd, s32 mode);

s32 func_001F9690(void)
{
    s32 i;
    Client_1F9690* c;

    if (D_002771CC < 0) {
        for (;;) {
            c = (Client_1F9690*)D_00628E00;
            if (func_001F80C0(c, 0x80000006, 0) < 0) {
                return -1;
            }
            if (c->bound != 0) {
                D_002771CC = 0;
                if (func_001F8290(D_00628E00, 0xFF, 0, 0, 0, &D_00628C00, 4, 0, 0) < 0) {
                    return 0xFFFEFFFF;
                }
                *(Word_1F9690*)&D_00628E28 = *(Word_1F9690*)&D_00628C00;
                return 0;
            }
            for (i = 0x100000; i != -1; ) i--;
        }
    }
    return 0;
}

s32 func_001F9790(void)
{
    s32 result = 0;
    void* second = &D_00276970[12];
    if (func_001F59C4(&D_00628E28, second, 4) != 0) {
        if (func_001F59C4(&D_00628E28, D_002771D0, 4) != 0) {
            result = func_001F59C4(second, D_002771D0, 4) != 0;
        }
    }
    return result;
}

s32 func_001F9820(void)
{
    D_002771CC = -1;
    func_001F5C0C(&D_00628E28, 0, 4);
    return 0;
}

LINKER_REMNANT(func_001F9858);

s32 func_001F9868(Blob_1F9868* src, s32 size, Blob_1F9868* data, s32* out, s32 cmd)
{
    if (func_001F9690() < 0) {
        return -0x10000;
    }
    if (func_001F9790() != 0) {
        return -0x10004;
    }
    Blob_1F9868* p = &D_00628C00.name;
    func_00201720(p, src, 0xFC);
    Buf_1F9868* q = (Buf_1F9868*)((u8*)p - 8);
    q->name.b[0xFB] = 0;
    if (data != 0) {
        if (size >= 0xFD) {
            q->data = *data;
            D_00628C00.f0 = 0xFC;
        } else {
            func_001F5A58(&q->data, data, size);
            q->f0 = size;
        }
    } else {
        q->data.b[0] = 0;
        q->f0 = 0;
    }
    Buf_1F9868* buf = &D_00628C00;
    if (func_001F8290(D_00628E00, cmd, 0, buf, 0x200, buf, 8, 0, 0) < 0) {
        return -0x10001;
    }
    s32 v = buf->f4;
    s32 ret = D_00628C00.f0;
    *out = v;
    return ret;
}

void func_001F9A90(Blob_1F9868* src, s32 size, Blob_1F9868* data)
{
    s32 out[4];
    func_001F9868(src, size, data, out, 0);
}

LINKER_REMNANT(func_001F9AB0);
