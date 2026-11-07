// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Pair_2779B0 { s32 a; void* b; };
extern u8 D_0064C700[];
Pair_2779B0 D_002779B0 = { 0, D_0064C700 };

void func_001FA0A0(void)
{
    D_002779B0.a = 0;
}

s32 func_001FA0D8(void)
{
    return 1;
}

s32 func_001FA1B0(s32* src, s32* dst)
{
    s32 value = src[4];
    dst[2] = value;
    return value;
}

extern s32 D_006294C0[];

s32 func_001FA1C0(s32 index)
{
    return D_006294C0[index];
}

extern s32 D_006293A4;
extern s32 D_006293AC;

void func_001FA4A0(s32 index, s32 first, s32 second)
{
    s32 scaled = index << 3;
    if (index < 0) {
        index = D_006293A4;
    } else {
        index = D_006293AC;
    }
    scaled += index;
    s32* p = (s32*)scaled;
    p[0] = first;
    p[1] = second;
}

// NEAR: EXACT only with SLY1_COMPILER=2.9-ee-991111 (Sony's release, saves in 8 bytes, as in the libraries); the default 2.9.3 build saves with sq/lq and differs (docs/TOOLCHAIN.md, lib compiler row not supported by tools/compile.py).

struct Buf_1F84D8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
};

s32 func_001F6B20(Buf_1F84D8* self);

s32 D_002771C0 = -1;
extern s32 D_002771C4;

void func_001F84D8(void)
{
    if (D_002771C0 == -1) {
        Buf_1F84D8 b;
        b.f8 = 1;
        b.f14 = 0;
        b.f4 = 1;
        D_002771C0 = func_001F6B20(&b);
        D_002771C4 = func_001F6B20(&b);
    }
}

// NEAR: retail saves s0/ra with sd/ld (8-byte, Sony 2.9-ee-991111 pattern); SN GCC emits sq/lq. Body matches.

struct Desc_001F8968 { s32 f0; s32 f4; s32 f8; s32 fc; s32 f10; s32 f14; };
struct Handle_001F8968;

s32 D_002771BC = -1;

s32 func_001F6B20(Desc_001F8968* self);

void func_001F8968(void)
{
    if (D_002771BC == -1) {
        Desc_001F8968 d;
        d.f8 = 1;
        d.f4 = 1;
        d.f14 = 0;
        D_002771BC = func_001F6B20(&d);
    }
}

extern s32 D_002771BC;
void func_001F8968(void);
s32 func_001F6B60(s32 a);

s32 func_001F89B8(void)
{
    func_001F8968();
    func_001F6B60(D_002771BC);
    return 0;
}

// NEAR: prologue and epilogue save $ra with sd/ld (8 bytes) where ours uses sq/lq (16 bytes); the rest of the body matches. Retail's 8-byte saves match the 2.9-ee-991111 library compiler, which tools/check.py cannot select per file.
struct Arg_1F8BF8;
void func_001F5C0C(Arg_1F8BF8* p, s32 a, s32 b);

extern s32 D_002771B8;
extern u8 D_00628B68[];

s32 func_001F8BF8(void)
{
    D_002771B8 = 0;
    func_001F5C0C((Arg_1F8BF8*)D_00628B68, 0, 4);
    return 0;
}

// NEAR: retail saves s0..s3 and ra with 8-byte sd/ld; the default compiler saves them with 16-byte sq/lq. Otherwise identical

struct Arg_1F9790;

u32 D_0027697C = 0x30333432;
extern u8 D_00628E28[];
extern char D_0024EB80[];
void* D_002771D0 = D_0024EB80;

s32 func_001F59C4(struct Arg_1F9790* a, void* b, s32 c);

s32 func_001F9790(void)
{
    s32 result = 0;
    void* second = &D_0027697C;
    if (func_001F59C4((struct Arg_1F9790*)D_00628E28, second, 4) != 0) {
        if (func_001F59C4((struct Arg_1F9790*)D_00628E28, D_002771D0, 4) != 0) {
            result = func_001F59C4((struct Arg_1F9790*)second, D_002771D0, 4) != 0;
        }
    }
    return result;
}

// NEAR: only the ra save and restore differ (ours sq/lq, retail sd/ld; 0x1F lib region, see docs/TOOLCHAIN.md)

struct Clear_1F9820;
extern s32 D_002771CC;
extern u8 D_00628E28[];
void func_001F5C0C(Clear_1F9820* p, s32 value, s32 size);

s32 func_001F9820(void)
{
    D_002771CC = -1;
    func_001F5C0C((Clear_1F9820*)D_00628E28, 0, 4);
    return 0;
}

// NEAR: retail saves $ra with sd, default compiler with sq; call and frame identical
struct Ctx_001F9A90;
s32 func_001F9868(Ctx_001F9A90* a0, void* a1, void* a2, u32* a3, s32 a4);

void func_001F9A90(Ctx_001F9A90* a0, void* a1, void* a2)
{
	u32 out[4];
	func_001F9868(a0, a1, a2, out, 0);
}

// NEAR: default 2.95.3 saves $ra with sq/lq where retail has sd/ld; EXACT with SLY1_COMPILER=2.9-ee-991111 (docs/TOOLCHAIN.md item 3)

enum Arg_001F9C18 { ARG_001F9C18_NONE = 0 };

s32 func_001F6CF0(Arg_001F9C18 which);
void func_001FA0A0(void);

s32 func_001F9C18(void)
{
    if ((func_001F6CF0((Arg_001F9C18)4) & 0x40000) != 0) {
        func_001FA0A0();
        return 1;
    }
    return 0;
}

// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_1F9E50;

s32 D_002771D8[3] = { 131, 2072072, 0 };

void func_001F9E90(Ctx_1F9E50* a, s32 b);
s32 func_001F9E40(s32 fn);
s32 func_001F9E08(Ctx_1F9E50* a);

s32 func_001F9E50(void)
{
    func_001F9E90((Ctx_1F9E50*)D_002771D8[0], D_002771D8[1]);
    s32 r = func_001F9E40((s32)func_001F9E08);
    return r - 0x20C;
}

// NEAR: retail is a bare tail jump `j` with a nop delay slot; SN 2.95.3 keeps a frame (sq ra) and uses jal. Only Sony 2.9-ee-991111 tail-calls (docs/TOOLCHAIN.md).

struct Node_001FA068 { s32 a; };

s32 func_001FA9C0(Node_001FA068* p);

void func_001FA068(Node_001FA068* p)
{
    func_001FA9C0(p);
}

// NEAR: ra is saved with sq/lq, retail sd/ld (Sony 2.9-ee-991111 lib build, docs/TOOLCHAIN.md); body otherwise EXACT

void func_001FA078(void* arg);

s32 func_001FA0E0(s32 mode, void* arg)
{
    if (mode == 1) {
        func_001FA078(arg);
    }
    return 0;
}

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

enum Req_1FA140 { REQ_1FA140_CLOCK = 0x10 };
void func_001F6D10(Req_1FA140 req, void* arg);

void func_001FA140(s32 value) { s32 local = value; func_001F6D10(REQ_1FA140_CLOCK, &local); }

// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_1FA630;

s32 func_001FA4F8(Ctx_1FA630* a, s32 mode, s32 b, s32 c, s32 d, s32 e, s32 f);

s32 func_001FA630(Ctx_1FA630* a, s32 b, s32 c, s32 d, s32 e, s32 f)
{
    return func_001FA4F8(a, 0, b, c, d, e, f);
}

// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_1FA670;

s32 func_001FA4F8(Ctx_1FA670* a, s32 mode, s32 b, s32 c, s32 d, s32 e, s32 f);

s32 func_001FA670(Ctx_1FA670* a, s32 b, s32 c, s32 d, s32 e, s32 f)
{
    return func_001FA4F8(a, 1, b, c, d, e, f);
}


struct Node_001F8200 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    Node_001F8200* f40;
};

struct Ctx_001F8200 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    Node_001F8200* f34;
};

void func_001F71D0(Node_001F8200* a);

void func_001F8200(Ctx_001F8200* self)
{
    Node_001F8200* n = self->f34;
    Node_001F8200* list = n->f40;
    if (list->f0C == 0) {
        list->f0C = (s32)n;
    } else {
        ((Node_001F8200*)list->f10)->f3C = (s32)n;
    }
    list->f10 = (s32)n;
    s32 a = self->f14;
    s32 b = self->f1C;
    n->f20 = a;
    n->f1C = b;
    n->f24 = self->f20;
    n->f0C = self->f24;
    n->f28 = self->f28;
    n->f2C = self->f2C;
    n->f30 = self->f30;
    n->f34 = self->f10;
    if (list->f00 < 0) {
        return;
    }
    if (list->f04 != 0) {
        return;
    }
    func_001F71D0((Node_001F8200*)list->f00);
}

struct Mgr_1F8538 { s32 v; };

extern u8 D_00628940[];

s32 func_001F6B60(Mgr_1F8538* m);
s32 func_001F6B40(Mgr_1F8538* m);

s32 func_001F8538(s32 a0)
{
    s32 s = a0;
    (void)func_001F84D8();
    (void)func_001F6B60((*(Mgr_1F8538**)&D_002771C0));
    if ((u32)a0 >= 0x20u) {
        (void)func_001F6B40((*(Mgr_1F8538**)&D_002771C0));
        return 0;
    }
    s32 t = s << 4;
    t += (s32)D_00628940;
    (void)func_001F6B40((*(Mgr_1F8538**)&D_002771C0));
    return t;
}

struct Blob_1F9868 { u8 b[0xFC]; };
struct Buf_1F9868 { s32 f0; s32 f4; Blob_1F9868 name; Blob_1F9868 data; };
extern Buf_1F9868 D_00628C00;
extern u8 D_00628E00[];

s32 func_001F9690(void);
s32 func_001F9790(void);
void func_00201720(Blob_1F9868* dst, Blob_1F9868* src, s32 n);
void func_001F5A58(Blob_1F9868* dst, Blob_1F9868* src, s32 n);
s32 func_001F8290(u8* a, s32 b, s32 c, Buf_1F9868* d, s32 e, Buf_1F9868* f, s32 g, s32 h, s32 i);

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

struct Frame_001F9DC0 { s32 w[16]; };

s32 func_001F6B20(Frame_001F9DC0* q);
s32 D_002771E4;
s32 D_002771E8;

void func_001F9DC0(void)
{
    Frame_001F9DC0 f;
    f.w[1] = 1;
    f.w[2] = 1;
    f.w[9] = 1;
    f.w[10] = 1;
    D_002771E4 = func_001F6B20(&f);
    D_002771E8 = func_001F6B20((Frame_001F9DC0*)&f.w[8]);
}

extern s32 D_00629394;
s32 D_002779B8[2] = { 0, 0 };

s32 func_001F6E10(s32 a0);
s32 func_001F6990(s32 a0, s32 a1);

void func_001FA468(void)
{
    (void)func_001F6E10(5);
    (void)func_001F6990(5, D_00629394);
    D_002779B8[0] = 0;
}

extern s32 D_006293A4;
extern s32 D_006293AC;

void func_001FA4D0(s32 index)
{
    s32 off = index << 3;
    if (index < 0) {
        index = D_006293A4;
    } else {
        index = D_006293AC;
    }
    off += index;
    *(s32*)off = 0;
}

struct Obj_1F8480 {
    u8 pad0[0x10];
    s32 flags;
    u8 pad1[4];
    s32 id;
};
struct Ref_1F8480 {
    Obj_1F8480* obj;
    s32 key;
};

s32 func_001F8480(Ref_1F8480* self)
{
    Obj_1F8480* o = self->obj;
    if (o != 0 && self->key == o->id) {
        u32 f = o->flags & 1;
        if (f != 0) goto yes;
    }
    return 0;
yes:
    return 1;
}

struct Node_1F80C0;
struct Ctx_1F80C0 { Node_1F80C0* f0; s32 f4; s32 f8; s32 pad_c; s32 f10; u8 pad14[0x10]; s32 f24; };
struct Node_1F80C0 { u8 pad0[0x14]; Node_1F80C0* f14; s32 f18; Ctx_1F80C0* f1C; s32 f20; };
struct Ring_1F80C0;
struct Args_1F80C0 { s32 a; s32 b; s32 c; };
typedef s32 Kind_1F80C0;
typedef s32 Code_1F80C0;

extern u8 D_00627800[];

Node_1F80C0* func_001F7DB0(Ring_1F80C0* r);
s32 func_001F6B20(Args_1F80C0* a);
void func_001F7E58(Node_1F80C0* n);
s32 func_001FA630(Kind_1F80C0 k, Node_1F80C0* n, s32 sz, s32 a3, s32 a4, s32 a5);
s32 func_001F6B60(Code_1F80C0 c);
void func_001F6B30(Code_1F80C0 c);

s32 func_001F80C0(Ctx_1F80C0* self, s32 a1, s32 a2)
{
    Args_1F80C0 args;
    Node_1F80C0* node;
    s32 r;
    s32 scratch[4];
    (void)scratch;

    self->f10 = 0;
    self->f24 = 0;
    node = func_001F7DB0((Ring_1F80C0*)D_00627800);
    if (node == 0) return -1;
    self->f0 = node;
    self->f4 = node->f18;
    node->f20 = a1;
    node->f14 = node;
    node->f1C = self;
    if ((a2 & 1) == 0) {
        args.c = 0;
        args.b = 1;
        r = func_001F6B20(&args);
        self->f8 = r;
        if (r < 0) {
            func_001F7E58(node);
            return -3;
        }
        if (func_001FA630(0x80000009, node, 0x40, 0, 0, 0) == 0) {
            func_001F7E58(node);
            func_001F6B30(self->f8);
            return -2;
        }
        func_001F6B60(self->f8);
        func_001F6B30(self->f8);
        return 0;
    }
    self->f8 = -1;
    if (func_001FA630(0x80000009, node, 0x40, 0, 0, 0) != 0) {
        return 0;
    }
    func_001F7E58(node);
    return -2;
}

struct Obj_1FA4F8 { s32 w0; s32 w4; s32 w8; };
struct Rec_1FA4F8 { s32 w0; s32 w4; s32 w8; s32 wC; };
struct Ctx_1FA4F8 { s32 pad; };

extern s32 D_006293A0[];

void func_001FA7D8(Ctx_1FA4F8* ctx, s32 a1);
void func_001FA7D8(Obj_1FA4F8* o, s32 a1);
s32 func_001F6CB0(Rec_1FA4F8* recs, s32 n);
s32 func_001F6CA0(Rec_1FA4F8* recs, s32 n);

s32 func_001FA4F8(s32 p1, s32 flags, Obj_1FA4F8* obj, s32 p4, Ctx_1FA4F8* p5, s32 p6, s32 count, s32 p8)
{
    Rec_1FA4F8 recs[2];
    s32 n;
    s32 result;

    if ((u32)(p4 - 0x10) >= 0x61u) {
        return 0;
    }
    n = 0;
    if (count > 0) {
        u8 lo = ((u8*)obj)[0];
        n = 1;
        recs[0].w0 = (s32)p5;
        recs[0].w4 = p6;
        obj->w4 = p6;
        obj->w0 = lo | (count << 8);
        recs[0].w8 = count;
        recs[0].wC = 0;
        if (flags & 4) {
            func_001FA7D8(p5, count);
        }
    } else {
        obj->w4 = 0;
        obj->w0 = ((u8*)obj)[0];
    }
    recs[n].w0 = (s32)obj;
    recs[n].w4 = D_006293A0[0];
    recs[n].w8 = p4;
    obj->w8 = p1;
    ((u8*)obj)[0] = (u8)p4;
    recs[n].wC = 0x44;
    func_001FA7D8(obj, p4);
    n++;
    if (flags & 1) {
        result = func_001F6CB0(recs, n);
    } else {
        result = func_001F6CA0(recs, n);
    }
    return result;
}

struct Span_1F9AD8 {
    void* a;
    s32 b;
    s32 c;
    s32 d;
};

struct Cmd_1F9AD8 {
    union {
        u64 hdr;
        s32 w[2];
    };
    s32 w8;
    s32 padC;
    s32 len;
    void* q;
    u8 text[1];
};
extern Cmd_1F9AD8 D_00628E40;

void func_001F6C40(s8* text, void* q);
s32 func_001F6CF0(u32 a0);
void func_001FA7D8(Cmd_1F9AD8* a0, s32 a1);
u32 func_001F6CE0(u32 reg, u32 value);
s32 func_001F6CA0(Span_1F9AD8* span, s32 n);

s32 func_001F9AD8(s8* text, void* q)
{
    Span_1F9AD8 span;
    s32 len;
    s32 w;

    func_001F6C40(text, q);
    w = func_001F6CF0(0x80000000);
    D_00628E40.q = q;
    len = 0;
    if (text[0] != 0) {
        do {
            D_00628E40.text[len] = (u8)text[len];
            len++;
        } while (text[len] != 0);
    }
    D_00628E40.w[1] = 0;
    D_00628E40.len = len;
    D_00628E40.w8 = (s32)0x80000003;
    D_00628E40.hdr = D_00628E40.hdr & 0xFFFFFFFF000000FFULL;
    *(u8*)&D_00628E40 = 0x68;
    span.a = &D_00628E40;
    span.b = w;
    span.c = 0x68;
    span.d = 0x44;
    func_001FA7D8(&D_00628E40, 0x68);
    func_001F6CE0(4, 0x40000);
    if (func_001F6CA0(&span, 1) != 0) {
        func_001F6CE0(4, 0x10000);
        func_001F6CE0(4, 0x20000);
        func_001F6CE0(0x80000002, 0);
        func_001F6CE0(0x80000000, 0);
        return 1;
    }
    return 0;
}

s32 func_001F7B88(const char *fmt, ...);
s32 func_001F7BE8(s32 a);
void func_001F7D88(void);
s32 func_001F9AD8(char *text, void *q);

extern const char D_0024EB90[16];
struct Msgs_24EBA0 {
    char tooLong[32];
    char packet[40];
    char recvErr[24];
    char sendErr[24];
    char wlen[24];
};
extern const Msgs_24EBA0 D_0024EBA0;

s32 func_001F9C50(char *arg) {
    char buf[80];
    char *e = arg;
    const char *pre = D_0024EB90;
    char *d;
    char *base;

    while (*e != 0) {
        e++;
    }
    base = arg - 11;
    if ((u32)(e - base) > 80) {
        func_001F7B88(D_0024EBA0.tooLong, arg);
        return 0;
    }
    func_001F7BE8(0);
    func_001F7D88();
    d = buf;
    while (*pre != 0) {
        *d++ = *pre++;
    }
    while (*arg != 0) {
        *d++ = *arg++;
    }
    *d = 0;
    return func_001F9AD8(buf, 0);
}

#define UNCACHED_1F85A8(p) ((void *)((u32)(p) | 0x20000000))

struct __attribute__((packed)) Word_1F85A8 {
    u32 v;
    static void Read(void* dst, void* src) { *(Word_1F85A8*)dst = *(Word_1F85A8*)UNCACHED_1F85A8(src); }
};

struct Bytes_1F85A8 {
    s32 count0;
    s32 count1;
    u8 *dst0;
    u8 *dst1;
    u8 buf0[0x40];
    u8 buf1[0x40];
};

struct Block144_1F85A8 {
    u8 b[0x144];
};

struct Block40_1F85A8 {
    u8 b[0x40];
};

extern u8 D_00628500[];
extern volatile s32 D_00277138[];

void *func_001F5A58(void *dst, const void *src, s32 n);
void func_001F6B50(s32 sema);

void func_001F85A8(void) {
    s32 sema;
    s32 type;
    void *dst;
    s32 size;
    void *pdst;
    u32 psize;
    s32 i;

    Word_1F85A8::Read(&sema, D_00628500);
    Word_1F85A8::Read(&type, D_00628500 + 4);
    Word_1F85A8::Read(&dst, D_00628500 + 8);
    Word_1F85A8::Read(&size, D_00628500 + 12);
    if (sema >= 0) {
        func_001F5A58(dst, UNCACHED_1F85A8(D_00628500 + 16), size);
    }
    switch (type) {
    case 2: {
        struct Bytes_1F85A8 *b = (struct Bytes_1F85A8 *)UNCACHED_1F85A8(D_00628500 + 20);
        if (b->count0 > 0) {
            u8 *d = b->dst0;
            for (i = 0; i < b->count0; i++) {
                d[i] = b->buf0[i];
            }
        }
        if (b->count1 > 0) {
            u8 *d = b->dst1;
            for (i = 0; i < b->count1; i++) {
                d[i] = b->buf1[i];
            }
        }
        break;
    }
    case 11:
        Word_1F85A8::Read(&pdst, D_00628500 + 20);
        *(struct Block144_1F85A8 *)pdst = *(struct Block144_1F85A8 *)UNCACHED_1F85A8(D_00628500 + 24);
        break;
    case 12:
        Word_1F85A8::Read(&pdst, D_00628500 + 20);
        *(struct Block40_1F85A8 *)pdst = *(struct Block40_1F85A8 *)UNCACHED_1F85A8(D_00628500 + 24);
        break;
    case 23:
    case 25:
    case 26:
        Word_1F85A8::Read(&pdst, D_00628500 + 20);
        Word_1F85A8::Read(&psize, D_00628500 + 24);
        if (psize > 0x400) {
            psize = 0x400;
        }
        func_001F5A58(pdst, UNCACHED_1F85A8(D_00628500 + 28), psize);
        break;
    }
    if (sema < 0) {
        sema = -sema;
        i = 0;
        for (;;) {
            if (g_semaphoreSlots[i] == sema) {
                g_semaphoreSlots[i] = -1;
                break;
            }
            if (++i >= 32) return;
        }
    } else {
        func_001F6B50(sema);
    }
}

extern s32 D_002771BC;
s32 func_001F6B40(s32 a);
void func_001F89E8() { func_001F6B40(D_002771BC); }

void func_001F9DC0(); void func_001F6F48(); void func_001F70F8(); void func_001F9FB8(); void func_001FA8F8();
void func_001F9EA8()
{
    func_001F9DC0();
    func_001F9E50();
    func_001F6F48();
    func_001F70F8();
    func_001F9FB8();
    func_001FA8F8();
}

void func_001FA068();
void func_001F6920(s32 a);
void func_001FA078(s32 a)
{
    func_001FA068();
    func_001F6920(a);
}

struct A_1FA190 { u8 p[0x10]; s32 i; s32 v; };
struct B_1FA190 { u8 p[0x1C]; s32* t; };
void func_001FA190(A_1FA190* a, B_1FA190* b) { b->t[a->i] = a->v; }

struct Ring_1F8010;
struct Node_1F8010 { u8 p0[8]; s32 f8; u8 pC[8]; s32 f14; };
struct Msg_1F8010 { u8 p0[0x14]; s32 f14; u8 p18[4]; s32 f1C; u32 f20; s32 f24; s32 f28; s32 f2C; };
struct Src_1F8010 { u8 p0[0x14]; s32 f14; u8 p18[4]; s32 f1C; s32 f20; };
struct Ctx_1FA670;

Msg_1F8010* func_001F7E78(Ring_1F8010* r);
Node_1F8010* func_001F7FC0(s32 key, Ring_1F8010* r);
s32 func_001FA670(Ctx_1FA670* a, Msg_1F8010* b, s32 c, s32 d, s32 e, s32 f);

void func_001F8010(Src_1F8010* src, Ring_1F8010* ring)
{
    Msg_1F8010* m = func_001F7E78(ring);
    s32 a = src->f14;
    s32 b = src->f1C;
    m->f14 = a;
    m->f1C = b;
    m->f20 = 0x80000009;
    Node_1F8010* n = func_001F7FC0(src->f20, ring);
    if (n == 0) {
        m->f24 = 0;
        m->f28 = 0;
        m->f2C = 0;
    } else {
        m->f24 = (s32)n;
        m->f28 = n->f8;
        m->f2C = n->f14;
    }
    func_001FA670((Ctx_1FA670*)0x80000008, m, 0x40, 0, 0, 0);
}

struct Msg_1FA1E8;

struct Slot_1FA1E8 {
    void (*f0)(Msg_1FA1E8*, void*);
    void* f4;
};

struct Ctl_1FA1E8 {
    u32 f0;
    u32 f4;
    s32 f8;
    Slot_1FA1E8* fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32* f1C;
};

struct Req_1FA1E8 {
    s32 pad[3];
    s32 fC;
    void* f10;
};

extern s32 D_002779B8[];
extern Ctl_1FA1E8 D_00629398;
extern Slot_1FA1E8 D_006293C0[];
extern s32 D_006294C0[];
extern u8 D_006292C0[];
extern u8 D_00629340[];
extern Req_1FA1E8 D_00629380;
extern s32 D_00629394;

void func_001FA190(Msg_1FA1E8* msg, void* arg);
void func_001FA1B0(Msg_1FA1E8* msg, void* arg);
void func_001FA6B0(void);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);
void func_001F6C20(s32 a);
void func_001F6CC0(void);
s32 func_001F6970(s32 a, void* b, s32 c);
void func_001F6E78(s32 a);
s32 func_001F6CF0(u32 a);
u32 func_001F6CE0(u32 reg, u32 value);
s32 func_001FA630(u32 index, void* b, s32 c, s32 d, s32 e, s32 f);

void func_001FA1E8(void)
{
    s32 i;
    func_001F9D60();
    if (D_002779B8[0] != 0) {
        func_001F9DA8();
        return;
    }
    D_002779B8[0] = 1;
    D_00629398.f0 = (u32)D_006292C0 | 0x20000000;
    D_00629398.f4 = (u32)D_00629340 | 0x20000000;
    D_00629398.f10 = 0x20;
    D_00629398.f8 = 0;
    D_00629398.fC = D_006293C0;
    D_00629398.f14 = 0;
    D_00629398.f18 = 0;
    D_00629398.f1C = D_006294C0;
    for (i = 0; i < 32; i++) {
        D_006293C0[i].f0 = 0;
        D_006293C0[i].f4 = 0;
    }
    for (i = 0; i < 32; i++) {
        D_006294C0[i] = 0;
    }
    D_006293C0[0].f0 = func_001FA1B0;
    D_006293C0[1].f0 = func_001FA190;
    D_006293C0[0].f4 = &D_00629398;
    D_006293C0[1].f4 = &D_00629398;
    func_001F9DA8();
    func_001F6C20(0);
    if ((*(volatile u32*)0x1000E010 & 0x20) != 0) {
        *(volatile u32*)0x1000E010 = 0x20;
    }
    if ((*(volatile u32*)0x1000C000 & 0x100) == 0) {
        func_001F6CC0();
    }
    D_00629394 = func_001F6970(5, (void*)func_001FA6B0, 0);
    func_001F6E78(5);
    D_00629398.f8 = func_001F6CF0(0x80000000);
    if (D_00629398.f8 != 0) {
        D_00629380.f10 = D_006292C0;
        func_001FA630(0x80000000, &D_00629380, 0x14, 0, 0, 0);
        return;
    }
    while ((func_001F6CF0(4) & 0x20000) == 0) {
    }
    D_00629398.f8 = func_001F6CF0(2);
    func_001F6CE0(0x80000000, D_00629398.f8);
    func_001F6CE0(0x80000001, (u32)&D_00629398);
    D_00629380.f10 = D_006292C0;
    D_00629380.fC = 0;
    func_001FA630(0x80000002, &D_00629380, 0x14, 0, 0, 0);
}

s32* func_001F9E08(s32 value)
{
    s32* p = (s32*)0x80000000;
    while (*p != value)
        p++;
    return p;
}


struct Node_001F8C38 { s32 f0; s32 f4; };
struct Ctor_001F8C38 { s32 a0; s32 a1; s32 a2; s32 a3; s32 a4; s32 a5; };
struct Glob_001F8C38 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; };
struct Q_001F8C38 { u8 pad[4]; };

extern u8 D_00627880[];
extern u8 D_00628940[];
extern u8 D_006284C0[];
extern u8 D_00628B40[];

s32 func_001F89B8(s32 a);
void func_001F89E8(void);
s32 func_001F6B20(Ctor_001F8C38* c);
void func_001F6B30(s32 h);
s32 func_001F6B60(s32 h);
s32 func_001F8290(Q_001F8C38* a, s32 b, s32 c, Q_001F8C38* d, s32 e, u8* f, s32 g, s32 h, s32 i);

struct Lock_1F8C38 { static s32 Ready(s32 n) { func_001F89B8(n); return ((s32*)&D_002771B8)[0]; } };
struct Min_1F8C38 { static s32 Of(s32 a, s32 b) { return a < b ? a : b; } };

s32 func_001F8C38(s32 a0)
{
    Glob_001F8C38* g = (Glob_001F8C38*)D_00627880;
    Node_001F8C38* p;
    s32 h;
    s32 out;
    s32 v;
    Ctor_001F8C38 ctor;
    u8* q;

    p = (struct Node_001F8C38 *)func_001F8538(a0);
    if (Lock_1F8C38::Ready(1) == 0) {
        func_001F89E8();
        return -1;
    }
    if (p == 0 || p->f4 == 0) {
        func_001F89E8();
        return -9;
    }
    g->fC = p->f0;
    g->f10 = ((s32)p - (s32)D_00628940) >> 4;
    ctor.a1 = 1;
    ctor.a2 = 0;
    ctor.a5 = 0;
    h = func_001F6B20(&ctor);
    g->f0 = h;
    g->f4 = (s32)&out;
    g->f8 = 4;
    q = D_006284C0;
    v = func_001F8290((Q_001F8C38*)D_00628B40, 1, 0, (Q_001F8C38*)g, 0x14, q, 4, 0, 0);
    if (v >= 0) {
        p->f4 = 0;
    } else {
        func_001F6B30(h);
        func_001F89E8();
        return -0xB;
    }
    v = *(s32*)((s32)q | 0x20000000);
    func_001F89E8();
    if (v == 0) {
        func_001F6B30(h);
        return -0xB;
    }
    func_001F6B60(h);
    func_001F6B30(h);
    return Min_1F8C38::Of(out, 0);
}

struct A_1F8A28 { s32 pad[9]; s32 f24; };
struct U_1F8A28 { u8 b[4]; } __attribute__((packed));
struct G_1F8A28 { void (*a)(s32); s32 b; };
extern G_1F8A28 D_00628BC0;
extern u8 D_00628B80[];
extern u8 D_00628B40[];
extern u8 D_00628940[];
extern u8 D_00628500[];
extern u8 D_006284C0[];
extern u8 D_00628B68[];
extern u8 D_00627840[];
extern s32 D_002771C0;
extern s32 D_002771B8;
void func_001F89F8();

s32 func_001F9D60(void);
void func_001FA4A0(u32 a, void* b, void* c);
s32 func_001F80C0(A_1F8A28* a, u32 b, s32 c);
void func_001F84D8(void);
s32 func_001F8290(A_1F8A28* a, s32 b, s32 c, void* d, s32 e, void* f, s32 g, s32 h, s32 i);

s32 func_001F8A28(void)
{
    s32 i;
    A_1F8A28* q;
    G_1F8A28* g = &D_00628BC0;
    (s32)func_001F7BE8(0);
    D_00628BC0.a = 0;
    g->b = 0;
    func_001F9D60();
    func_001FA4A0(0x80000011, (void*)&func_001F85A8, D_00628B80);
    func_001FA4A0(0x80000013, (void*)&func_001F89F8, (void*)g);
    (s32)func_001F9DA8();
    for (;;) {
        q = (A_1F8A28*)D_00628B40;
        if (func_001F80C0(q, 0x80000001, 0) < 0) return -1;
        if (q->f24 != 0) break;
        for (i = 0x100000; i != -1; ) i--;
    }
    func_001F84D8();
    func_001F6B60(D_002771C0);
    for (u8* p = D_00628940; p < D_00628940 + 0x200; p += 0x10) *(s32*)(p + 4) = 0;
    func_001F6B40(D_002771C0);
    *(u8**)D_00627840 = D_00628500;
    if (func_001F8290((A_1F8A28*)D_00628B40, 0xFF, 0, D_00627840, 4, D_006284C0, 4, 0, 0) < 0) return 0xFFFEFFFF;
    *(U_1F8A28*)D_00628B68 = *(U_1F8A28*)((u32)D_006284C0 | 0x20000000);
    D_002771B8 = 1;
    return 0;
}

struct Blk_1F92E8 {
    u8 b[0x400];
};

struct G_1F92E8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    Blk_1F92E8 blk;
    s32 f414;
    s32 f418;
    s32 f41C;
};

struct Ent_1F92E8 {
    s32 f0;
    s32 f4;
};

struct Req_1F92E8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
};

extern u8 D_00627880[];
extern u32* D_00627844;
extern s32 D_002771B8;
extern s32 D_002771C4;
extern volatile s32 D_00277138[];
extern u32 D_00628510[];
extern u8 D_00628B40[];
extern u8 D_006284C0[];

s32 func_001F8538(s32 a0);
s32 func_001F89B8(s32 a0);
s32 func_001F8A28(void);
void func_001F89E8(void);
s32 func_001F6B60(s32 h);
s32 func_001F6B40(s32 h);
void func_001F6B30(s32 h);
s32 func_001F6B20(Req_1F92E8* r);
void func_001FA7D8(G_1F92E8* g, s32 n);
s32 func_001F8290(u8* a, s32 b, s32 c, G_1F92E8* d, s32 e, u8* f, s32 g, s32 h, s32 i);

s32 func_001F92E8(s32 a0, s32 mode, u32* out)
{
    G_1F92E8* g = (G_1F92E8*)D_00627880;
    s32 ret = 1;
    Ent_1F92E8* ent = (Ent_1F92E8*)func_001F8538(a0);
    (void)func_001F89B8(5);
    D_00627844 = out;
    if (D_002771B8 == 0) {
        (void)func_001F8A28();
    }
    if (ent == 0 || ent->f4 == 0) {
        func_001F89E8();
        return -9;
    }
    g->f414 = 0;
    g->f418 = 0;
    switch (mode) {
    case 1: {
        (void)func_001F6B60(D_002771C4);
        s32 i = 0;
        while (i < 32 && g_semaphoreSlots[i] == -1) {
            i++;
        }
        if (i == 32) {
            *D_00627844 = 0;
        } else {
            *D_00627844 = 1;
        }
        (void)func_001F6B40(D_002771C4);
        func_001F89E8();
        return 0;
    }
    case 2:
        *out = *(u32*)((u32)D_00628510 | 0x20000000);
        func_001F89E8();
        return 0;
    case 3:
        *(u64*)out = *(u64*)((u32)D_00628510 | 0x20000000);
        func_001F89E8();
        return 0;
    default:
        break;
    }
    g->fC = ent->f0;
    g->f10 = mode;
    Req_1F92E8 r;
    s32 sp30;
    if (out == 0) {
        g->f41C = 0;
    } else {
        g->f41C = 0x400;
        g->blk = *(Blk_1F92E8*)out;
    }
    r.f4 = 1;
    r.f8 = 0;
    r.f14 = 0;
    s32 h = func_001F6B20(&r);
    g->f0 = h;
    g->f4 = (s32)&sp30;
    g->f8 = 4;
    func_001FA7D8((G_1F92E8*)D_00627880, 0x420);
    if (func_001F8290(D_00628B40, 5, 0, (G_1F92E8*)D_00627880, 0x420, D_006284C0, 4, 0, 0) < 0) {
        func_001F6B30(h);
        func_001F89E8();
        return -0xB;
    }
    u32 res = *(u32*)((u32)D_006284C0 | 0x20000000);
    func_001F89E8();
    if (res == 0) {
        func_001F6B30(h);
        return -0xB;
    }
    (void)func_001F6B60(h);
    func_001F6B30(h);
    ret = sp30;
    return ret;
}

void func_0011AE38();
void func_0011C0E8();
void func_00137270();
void func_001460E0();
void func_0015F658();
void func_00167D48();
void func_0016C450();
void func_001963B8();
void func_001AEC90();
void func_001E08D8();
void func_001F2738();
void func_00180E90();
void func_0018F968();
s32 func_001931F0();
void func_001C29C8();
void func_001E5358();
void func_001E88B0();
void func_00211DE0();
void* D_0027B130[21] = {
    (void*)0x12, func_0011AE38, func_0011C0E8, func_00137270,
    func_001460E0, func_0015F658, func_00167D48, func_0016C450,
    func_00180E90, func_0018F968, func_001931F0, func_001963B8,
    func_001AEC90, func_001C29C8, func_001E08D8, func_001E5358,
    func_001E88B0, func_001F2738, func_00211DE0, 0,
    (void*)3
};

extern const char D_0024EB90[16] = "rom0:UDNL ";
extern const Msgs_24EBA0 D_0024EBA0 = {
    "too long parameter '%s'\n",
    "TTY: packet size larger than expect\n",
    "TTY: receive error",
    "TTY: send err %d\n",
    "TTY: err ti->wlen=%08x\n",
};
