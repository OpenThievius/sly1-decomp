// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "on_off_object.h"
#include "world.h"
#include "t2173.h"
#include "globals.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "s193210.h"
#include "output_buffer.h"


void* func_001D7120(u8* buf, char* dst, s32 cap);
s32 func_001E1DB8(u8* buf, s32 a, s32 b);
void func_001D7148(u8* buf, s32 n);



void func_001F5C0C(void* p, s32 v, s32 n);
s32 func_001F6B20(void* self);

struct Ctor_1E2268 {
    u8 pad0[4];
    void* b;
    void* a;
    u8 pad1[0x14];
};





s32 func_001E1EB0(void* self, void* ap);



struct Stream_001E1F58 { u8 bytes[0x420]; };

void* func_001D7120(void* stream, char* dst, s32 cap);
s32 func_001E1DB8(void* stream, const char* fmt, void* ap);
void func_001D7148(void* stream, s32 mode);



s32 func_001E1F58(char* dst, const char* fmt, void* ap);



s32 func_001E2018(char* dst, s32 cap, const char* fmt, void* ap);



struct Stream_1E1EB0 { u8 bytes[0x420]; };

void* func_001D7100(void* stream, s32 cap);
s32 func_001E1DB8(void* stream, const char* fmt, void* ap);
void func_001D7148(void* stream, s32 mode);



s32 func_001E2100(void* p);
void func_0018D800(void* dst, void* src, s32 count);



s32 func_001E2100(void* p);
void func_0018D800(void* dst, void* src, s32 count);





s32 func_001E2268(s32 a, s32 b);

struct IntPair_1E22C0 { u8 pad0[4]; s32 a; s32 b; };




void func_001451F0(u32 a0, int a1, int a2, void* a3, int a4, void* a5);
void func_00145088(u32 a0, int a1, void* a2, int a3, void* a4);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
extern f32 D_0026185C;




void func_001E2870(void* self, s32 a, s32 b);



struct Tally_1E2358 { s32 count; s32 last; void* ptr; };
extern void func_001F6B40(void* a);




void func_00124FC0(void* self);
void func_001E2870(void* self, s32 a, s32 b);
void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);



void func_001261C0(void);





extern f32 D_00275980[16];






void func_001243E0(void* self);
void func_001E2778(void* self, s32 state);
void func_001DBD40(void* a, s32 b, s32 c, void* d, s32 e, s32 f);



void func_00124A48(void* self);



void func_0015FBB8(void* self, void* p);
void func_001E2778(void* selfv, s32 state);



void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
s32 func_001E4C48(void* a, void* b, void* c, void* d, void* e);
s32 func_00137CC0(void* a);
void* func_0014D9A8(s32 idx);
void func_0011EC40(void* a, void* b);




struct Sub_1E30A0 { u8 pad[0x438]; f32 f438; f32 f43C; };
struct Glob_1E30A0 { u8 pad[0x1C8]; f32 f1C8; };



void func_001F5C0C(void* p, s32 zero, s32 size);

extern u8 D_00275940[0x18];

u64 func_001FBE00(u64 value, u64 radix);
s64 func_001FC3D0(u64 value, u64 radix);
void func_0018D800(void* dst, void* src, s32 count);



extern f32 D_00275980[];
extern f32 D_00275A10[4];
extern f32 D_00275A20[2];

void func_00123ED0(void* self);




struct Tally_1E22F8 { s32 count; s32 last; void* ptr; };
extern s32 func_001F6A90(void);
extern s32 func_001F6B60(void* a);



struct Field_001E0E18 {
    u8 pad0[0x20];
    s32 kind;
    u8 pad1[0x8];
    u8 mode;
};





struct Sub_1E2870;
struct Mgr_1E2870;
struct Loc_1E2870 {
    s32 v[4];
};
struct Pq_1E2870 {
    u8 pad0[0x2220];
    s32 f2220;
};
struct Glob_1E2870 {
    u8 pad0[0x224];
    s32 f224;
};


void* func_001925F0(void);
void func_00128018(Mgr_1E2870* a0, OnOffObject* a1, void* a2, Loc_1E2870* a3);
s32 func_001E4DC0(Sub_1E2870* self, Loc_1E2870* value);
void func_001E2778(OnOffObject* self, s32 state);




struct Locals_1E1DB8 {
    u8 spec[0x40];      // the conversion spec, at sp + 0
    void* va;           // the argument pointer, at sp + 0x40
    u8 pad44[0xC];
};

struct Str_1E1DB8;

void func_001D72C8(OutputBuffer* ctx);
s32 func_001D7190(OutputBuffer* ctx, const char* p, s32 n);
char* func_001E21D8(Str_1E1DB8* s, s32 c);
s32 func_001E2100(Str_1E1DB8* s);
s32 func_001E0978(const char* at, u8* spec, void* va);
void func_001E1A08(u8* spec, OutputBuffer* ctx, void* va, const char* at, s32 len);



extern u8 D_0024E879[];





struct Fmt_1E1028 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8 pad20[0xC];
    s8 mode;
    u8 pad2D[3];
    s32 f30;
};
struct Val_1E1028 {
    u64 v;
};








s32 func_001E0E18(Fmt_1E1028* self, Val_1E1028* v);
s32 func_001E2100(char* p);
s32 func_001E0EF8(s8 c);
s32 func_001E0F58(char* buf, s32 len, u64 value, u32 radix);
s32 func_001D7190(OutputBuffer* sink, const char* p, s32 n);
void func_001E2218(char* p);



struct Spec_1E0978 {
    s32 left;       // 0x00
    s32 plus;       // 0x04
    s32 space;      // 0x08
    s32 alt;        // 0x0C
    s32 zero;       // 0x10
    s32 noprec;     // 0x14
    s32 width;      // 0x18
    s32 prec;       // 0x1C
    s32 length;     // 0x20
    s32 f24;        // 0x24
    s32 f28;        // 0x28
    s8 conv;        // 0x2C
    s8 pad2D[3];
    s32 upper;      // 0x30
};

void func_001F5C0C(Spec_1E0978* dst, s32 value, s32 size);
s32 func_001E08F8(s8* s, s32* out);
extern u8 D_0024E879[];



struct Spec_001E1A08 {
    s32 f00; s32 f04; s32 f08; u8 pad0C[4]; s32 f10; s32 f14; s32 f18;
    s32 i1C; s32 i20; s32 i24; s32 i28; u8 ch; u8 pad2D[3]; s32 f30;
};



s32 func_001E2100(const char* s);
s32 func_001D7190(OutputBuffer* c, const char* s, s32 n);
void func_001E0CD0(Spec_001E1A08* sp, OutputBuffer* c, const char* s);
void func_001E1028(Spec_001E1A08* sp, OutputBuffer* c, u64 v);
void func_001E17A8(Spec_001E1A08* sp, OutputBuffer* c, s64 s);
void func_001E17A8(Spec_001E1A08* sp, OutputBuffer* c, double value);
s32 func_001E1498(char* buf, s32 n, Spec_001E1A08* sp, double value);
void func_001E2218(char* p);
double func_001FD868(f32 f);



struct Ctx_1E0CD0 : OutputBuffer {
    void Pad(u8 ch, s32 count)
    {
        u8 buf = ch;
        while (count-- > 0) {
            if (AppendToOutputBuffer(this, (const char*)&buf, 1) != 1) {
                break;
            }
        }
    }
};
struct Str_1E0CD0;

struct Obj_1E0CD0 {
    s32 f00;
    u8 p04[0x10 - 0x04];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};



s32 func_001E2100(Str_1E0CD0* p);






struct Obj_1E13D0 { u8 pad; };


f32 func_00205C78(f32 a, f32 b);
Obj_1E13D0* func_001FCDE0(Obj_1E13D0* self, u64 v);
Obj_1E13D0* func_001FCDE0(Obj_1E13D0* self, double v); // soft-float double in a1
Obj_1E13D0* func_001EAE78(Obj_1E13D0* self);
Obj_1E13D0* func_001FCD78(Obj_1E13D0* self, Obj_1E13D0* v);
s32 func_001FD410(Obj_1E13D0* self);



struct Spec_1E1498 {
    u8 pad0[0x14];
    s32 noPoint;
    u8 pad1[4];
    s32 prec;
    u8 pad2[0xC];
    u8 conv;
};

extern u8 D_00275940[];



void* func_001E2138(char* dst, char* src);
s32 func_001E2100(char* p);
s32 func_001E1330(double v);
u8 func_001E13D0(double v, s32 e, s32 i);
f32 func_00205C78(f32 a, f32 b);
double func_001FD868(f32 f);
double func_001FCDE0(double a, double b);
double func_001FCD20(double a, double b);

union Bits_001E1498 {
    double d;
    u64 u;
};



struct Init_1E2398 { s32 f00; void (*f04)(void); s32 f08; s32 f0C; s32 f10; s32 f14; u8 pad[0x18]; };

extern u8 D_006056D0[];
extern u8 D_002832F0[];
struct Pair_1E2398 { s32 f0; s32 f4; };
extern Pair_1E2398 D_00275958;

void func_0015EE80(void);
s32 func_001F6A90(void);
void func_001F6A50(s32 a, s32 b);
s32 func_001F5C0C(Init_1E2398* p, s32 zero, s32 size);
s32 func_001F6A10(Init_1E2398* p);



s32 func_001FD308(double a, double b);
f32 func_001FD578(double a);
f32 func_00205B28(f32 x);
double func_001FD868(f32 x);
s32 func_001FD410(double a);
double func_001FD358(s32 a);

extern f32 D_00261858[];


struct Ret_1E4880 { u8 pad[0x20]; f32 value; };



void func_001F5C0C(void* p, s32 v, s32 n);

// Built at startup: its constructor is func_001E4E38; the compiler's initialiser and constructor
// for this file are func_001E5328 and func_001E5358 (config/us/generated.tsv).
struct Ctor_1E4E38 {
    s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; u8 body[0x20];
    Ctor_1E4E38();
};



struct Blk_1E4E80 { s32 state; s32 a; s32 b; s32 c; s32 d; };










struct Blk_1E5278 { u8 pad[0x14]; };
struct Ring_1E5278 { s32 w; };

extern u8 D_00261420[];

void func_001C05D0(f32 x);
void func_00140ED0(Ring_1E5278* r);
void func_001E4E80(Blk_1E5278* self, u8* p, s32 a, s32 b, s32 c);



struct Blob_1E4EA8 { u32 w[8]; };
struct Eq_1E4EA8 {
    static s32 Of(Blob_1E4EA8* a, Blob_1E4EA8* b)
    {
        if (a == b) return 1;
        if (b == 0) return 0;
        return ((a->w[2] ^ a->w[6]) ^ (b->w[2] ^ b->w[6])) == 0;
    }
};
struct VT1_1E4EA8 { u8 pad[0x38]; void (*m38)(void*); };
struct Self_1E4EA8 { s32 f0; Blob_1E4EA8* f4; s32 f8; s32 fC; s32 f10; Blob_1E4EA8 f14; };
struct Sub_1E4EA8 : BufferedStream {
    void SetOwner(void* o) { owner = o; }
};
struct Cur_1E4EA8 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; u32 f19E0; };
struct Cur2_1E4EA8 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; u32 pad19E0[3]; u32 f19EC; };
struct Pl_1E4EA8 { u8 pad[0x4F44]; Cur_1E4EA8* f4F44; };
struct Vo_1E4EA8 { void* vt; };

extern u8 D_002C3B00[];
extern u8 D_00261EF0[];
extern u8 D_002623D8[];
extern u8 D_0026FA90[];
extern f32 D_0026186C;
extern Vo_1E4EA8 D_0026C6C8;
extern Cur2_1E4EA8* D_002623C0;
extern Pl_1E4EA8 D_00264A40;

void func_00191E70(s32 a);
void func_0018D410(KeyId* q);
S193210* func_00193210(S193210* q, U32P* a, U32P* b, U32P* c, U32P* d);
void* func_00137290(BufferedStream* q, s32 a, u8* b, s32 c);
void func_00193270(void* q);
s32 func_001373B0(BufferedStream* q, KeyId* k);
void func_001372E0(BufferedStream* q, s32 n);
void func_001DB838(World* q);
void func_001DB928(s32 a, BufferedStream* q);
void func_001430B8(u8* q, f32 v);
s32 func_0016E0F0(s32 n);
void func_00160690(Blob_1E4EA8* q, s32 n);
World* func_0011E580(s32 a, s32 b, s32 c, s32 d, s32 e);
void func_001C06A0(s32 a, s32 b, f32 x);
void func_001373D0(BufferedStream* q);
void func_00193300(void* q);
void func_0018C7F8(Pl_1E4EA8* q);
void func_00143A60(s32 q, s32 f);
void func_001C0070(void);
s32 func_001F4318(World* q, s32 a, s32 b);
void func_00151E18(u8* q);
void func_00160CE8(u8* q);
void func_0016B520(u8* q);
void func_00138C00(World* q, s32 n);
void func_00143E40(s32 q, s32 n, f32 v);
void func_00142ED0(f32 x);
void func_001C06D8(void);
void func_00191EB0(s32 a);

// The file's .data, in retail's order; the labels only its assembly reads are included.
u8 D_00275940[0x18] = "0123456789abcdef";
Pair_1E2398 D_00275958 = { 0, 0 };
u8 D_00275960[4] = { 0 };
s32 D_00275964 = 0;
INCLUDE_DATA(D_00275970);
INCLUDE_DATA(D_00275974);
INCLUDE_DATA(D_00275978);
f32 D_00275980[16] = { -450.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 1.0f, 0, 0, 125.0f, 1.0f, 0, 0 };
INCLUDE_DATA(D_002759C0);
f32 D_00275A10[4] = { 0, 0.5f, 0, 0 };
f32 D_00275A20[2] = { 0, 3.4028235e38f };
INCLUDE_DATA(D_00275A28);
INCLUDE_DATA(D_00275A2C);
INCLUDE_DATA(D_00275A30);
INCLUDE_DATA(D_00275A40);
INCLUDE_DATA(D_00275A50);
INCLUDE_DATA(D_00275A58);
INCLUDE_DATA(D_00275A70);
INCLUDE_DATA(D_00275A80);
INCLUDE_DATA(D_00275A90);
INCLUDE_DATA(D_00275AA0);

s32 func_001E08F8(s8* s, s32* out)
{
    s8* p = s;
    s32 sign = 1;
    s32 value = 0;
    s32 count = 0;
    u8 c;

    if (*p == 0x2D) {
        sign = -1;
    }
    if (sign == -1) {
        p++;
        count = 1;
    }
    c = *p;
    if ((u32)(c - 0x30) < 10) {
        do {
            value = value * 10 + ((s8)c - 0x30);
            p++;
            c = *p;
            count++;
        } while ((u32)(c - 0x30) < 10);
    }
    *out = value * sign;
    return count;
}

s32 func_001E0978(s8* at, Spec_1E0978* spec, s32** va)
{
    s32 state = 0;
    s8* p = at;
    s32 next;

    func_001F5C0C(spec, 0, 0x34);
    if (*at != 0) {
        for (;;) {
            s32 adv = 0;
            next = state;
            switch (state) {
            case 0: {
                s8 c = *p;
                if (c != 0x25) {
                    next = 6;
                } else {
                    s8 d = p[1];
                    next = 1;
                    if (d == c) {
                        spec->conv = d;
                        next = 6;
                        adv = 2;
                    } else {
                        adv = 1;
                    }
                }
                break;
            }
            case 1:
                switch ((s8)((u8)*p - 0x20)) {
                case 13:
                    spec->left = 1;
                    adv = 1;
                    break;
                case 11:
                    spec->plus = 1;
                    adv = 1;
                    break;
                case 0:
                    spec->space = 1;
                    adv = 1;
                    break;
                case 3:
                    spec->alt = 1;
                    adv = 1;
                    break;
                case 16:
                    spec->zero = 1;
                    adv = 1;
                    break;
                default:
                    next = 2;
                    break;
                }
                break;
            case 2:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    spec->width = w;
                    if (w < 0) {
                        w = (w < 0) ? -w : w;
                        spec->left = 1;
                        spec->width = w;
                    }
                    adv = 1;
                } else {
                    adv = ParseSignedDecimal(p, &spec->width);
                }
                if (p[adv] == 0x2E) {
                    next = 3;
                    adv++;
                } else {
                    next = 4;
                }
                break;
            case 3:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    adv = 1;
                    w = (w < 0) ? -w : w;
                    spec->prec = w;
                } else {
                    adv = ParseSignedDecimal(p, &spec->prec);
                }
                spec->noprec = spec->prec == 0;
                next = 4;
                break;
            case 4: {
                switch ((s8)((u8)*p - 0x4C)) {
                case 28:
                    spec->length = 1;
                    adv = 1;
                    break;
                case 32:
                    adv = 1;
                    if (p[1] != 0x6C) {
                        spec->length = 2;
                        break;
                    }
                    // fall through
                case 0:
                case 37:
                    spec->length = 2;
                    adv++;
                    break;
                case 1:
                case 10:
                case 33:
                case 42: {
                    s32 a = 3;
                    s32 r = 1;
                    s32 d;
                    s32 l;
                    if (g_charClassFlags[(s8)(u8)*p] & 1) {
                        a = 4;
                    }
                    spec->f24 = a;
                    d = *p;
                    l = (g_charClassFlags[d] & 1) ? d + 0x20 : d;
                    if (l ^ 0x76) {
                        r = a;
                    }
                    spec->f28 = r;
                    adv = 1;
                    break;
                }
                default:
                    break;
                }
                next = 5;
                break;
            }
            case 5:
                if (*p != 0x25) {
                    s32 e = *p;
                    s32 f;
                    s32 l;
                    spec->upper = g_charClassFlags[e] & 1;
                    f = *p;
                    l = (g_charClassFlags[f] & 1) ? f + 0x20 : f;
                    spec->conv = l;
                }
                adv = 1;
                next = 6;
                break;
            default:
                return p - at;
            }
            p += adv;
            state = next;
            if (*p == 0 || next == 6) {
                break;
            }
        }
    }
    return p - at;
}


void func_001E0CD0(Obj_1E0CD0* self, Ctx_1E0CD0* ctx, const char* str) {
    s32 n;
    s32 right;
    s32 left;
    u8 pad;

    if (str == 0) {
        str = "(null)";
    }
    right = 0;
    n = GetStringLength((Str_1E0CD0*)str);
    left = 0;
    if (self->f1C != 0 && self->f1C < n) {
        n = self->f1C;
    } else if (self->f14 != 0) {
        n = 0;
    }
    if (n < self->f18) {
        pad = (self->f10 != 0) ? 0x30 : 0x20;
        s32 d = self->f18 - n;
        if (self->f00 != 0) {
            right = d;
        } else {
            left = d;
        }
    }
    ctx->Pad(pad, left);
    AppendToOutputBuffer(ctx, str, n);
    ctx->Pad(0x20, right);
}


s32 func_001E0E18(Field_001E0E18* self, void* dst)
{
    s32 ret = 0;
    if (self->kind != 1) {
        if (self->kind < 2) {
            if (self->kind == 0) {
                *(u32*)((u8*)dst + 4) = 0;
            }
        }
    } else {
        *(u64*)dst = *(u16*)dst;
    }
    if (self->mode == 'd' || self->mode == 'i') {
        switch (self->kind) {
        case 0:
            if (*(s32*)dst < 0) {
                *(s32*)dst = -*(s32*)dst;
                ret = 1;
            }
            break;
        case 1:
            if (*(s16*)dst < 0) {
                *(s16*)dst = -*(u16*)dst;
                ret = 1;
            }
            break;
        case 2:
            if (*(s64*)dst < 0) {
                *(s64*)dst = -*(s64*)dst;
                ret = 1;
            }
            break;
        }
    }
    return ret;
}

s32 func_001E0EF8(s8 c)
{
    switch (c) {
    case 0x64:
    case 0x69:
    case 0x75:
        return 10;
    case 0x42:
    case 0x62:
        return 2;
    case 0x6F:
        return 8;
    case 0x78:
        return 16;
    }
    return 10;
}

s32 func_001E0F58(u8* buf, s32 len, u64 value, u32 radixArg)
{
    u64 radix = radixArg;
    u8* end = buf + len;
    u8* stop = end;
    u64 v = value;
    do {
        s64 digit = func_001FC3D0(v, radix);
        end--;
        *end = D_00275940[(s32)digit];
        v = func_001FBE00(v, radix);
    } while (v != 0 && end >= buf);
    s32 count = stop - end;
    if (count != 0 && buf < end) {
        CopyMemory(buf, end, count);
    }
    return count;
}


void func_001E1028(Fmt_1E1028* self, OutputBuffer* sink, u64 value)
{
    char buf[0x50];
    char pfx[0x10];
    char padc[0x10];
    Val_1E1028 val;
    s32 total;
    s32 lead;
    s32 trail;
    s32 zeros;
    s32 plen;
    s32 ndig;
    s32 n;

    val.v = value;
    if (self->f14 != 0 || self->f1C != 0) {
        self->f10 = 0;
    }
    if (self->f14 != 0 && val.v == 0) {
        plen = 0;
        zeros = 0;
        ndig = 0;
    } else {
        s32 neg = ExtractIntegerSign(self, &val);
        zeros = self->f1C;
        pfx[0] = 0;
        switch ((u8)self->mode) {
        case 'd':
        case 'i':
            if (neg) {
                __builtin_strcpy(pfx, "-");
            } else if (self->f4) {
                __builtin_strcpy(pfx, "+");
            } else if (self->f8) {
                __builtin_strcpy(pfx, " ");
            }
            zeros -= GetStringLength(pfx);
            break;
        case 'b':
            if (self->fC) {
                __builtin_strcpy(pfx, "0b");
            }
            break;
        case 'o':
            if (self->fC) {
                __builtin_strcpy(pfx, "0");
            }
            break;
        case 'x':
            if (self->fC) {
                __builtin_strcpy(pfx, "0x");
            }
            break;
        }
        plen = GetStringLength(pfx);
        ndig = WriteIntegerDigits(buf, 0x40, val.v, GetConversionRadix(self->mode));
        zeros -= ndig;
        zeros = zeros >= 0 ? zeros : 0;
    }
    buf[ndig] = 0;
    if (self->f30) {
        UppercaseString(pfx);
        UppercaseString(buf);
    }
    total = plen + zeros + ndig;
    lead = 0;
    trail = 0;
    if (total < self->f18) {
        s32 rem = self->f18 - total;
        if (self->f0) {
            trail = rem;
        } else if (self->f10 == 0) {
            lead = rem;
        } else if (ndig != 0) {
            zeros += rem;
        } else {
            lead = rem;
        }
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
    AppendToOutputBuffer(sink, pfx, plen);
    padc[0] = '0';
    n = zeros;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
    AppendToOutputBuffer(sink, buf, ndig);
    padc[0] = ' ';
    n = trail;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
}


s32 func_001E1330(double v)
{
    s32 i;
    if (func_001FD308(v, 0.0) > 0) {
        double l = func_001FD868(func_00205B28(func_001FD578(v)));
        i = func_001FD410(l);
        if (func_001FD308(l, 0.0) < 0 && func_001FD308(l, func_001FD358(i)) != 0)
            i--;
    } else {
        i = 0;
    }
    return i;
}

s8 func_001E13D0(Obj_1E13D0* self0, s32 a, s32 b)
{
    Obj_1E13D0* self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = func_00205C78(10.0f, (f32)(-b));
        Obj_1E13D0* p = func_001FCDE0(self, func_001FD868(t));
        self = TruncateDouble(p);
        p = TruncateDouble(func_001FCDE0(self, 0.1));
        p = func_001FCDE0(p, (u64)0x4024000000000000ULL);
        idx = func_001FD410(func_001FCD78(self, p));
    }
    return ((s8*)&D_00275940)[idx];
}


s32 func_001E1498(char* buf, s32 unused, Spec_1E1498* sp, double v)
{
    Bits_001E1498 bits;
    bits.d = v;
    if ((bits.u & 0x7FF0000000000000UL) == 0x7FF0000000000000UL) {
        const char* s = (bits.u & 0x000FFFFFFFFFFFFFUL) ? "(nan)" : "(inf)";
        CopyString(buf, (char*)s);
        return GetStringLength(buf);
    }
    char* out = buf;
    s32 e = GetDecimalExponent(v);
    s32 isE = sp->conv == 'e';
    if (sp->conv == 'g') {
        if (e < -4 || e >= sp->prec) {
            isE = 1;
            sp->prec = sp->prec - 1;
        }
    }
    s32 base = 0;
    if (isE) base = e;
    s32 prec = sp->prec;
    f32 p = func_00205C78(10.0f, (f32)(base - prec));
    double r = func_001FCD20(v, func_001FCDE0(func_001FD868(p), 0.5));
    s32 e2 = GetDecimalExponent(r);
    if (e < GetDecimalExponent(r)) e = e2;
    s32 n, i;
    if (isE) {
        n = 1;
        i = e;
    } else if (e >= 0) {
        i = e;
        n = e + 1;
    } else {
        n = 1;
        i = 0;
    }
    while (n-- > 0) {
        *out++ = GetDecimalDigit(r, e, i--);
    }
    if (sp->noPoint == 0) {
        *out++ = '.';
        n = sp->prec;
        while (n-- > 0) {
            *out++ = GetDecimalDigit(r, e, i--);
        }
        if (sp->conv == 'g' && buf < out) {
            while (buf < out && out[-1] == '0') out--;
            if (buf < out && out[-1] == '.') out--;
        }
    }
    if (isE) {
        *out++ = 'e';
        if (e < 0) {
            *out++ = '-';
            e = -e;
        } else {
            *out++ = '+';
        }
        s32 d = (s32)func_00205C78(10.0f, 2.0f);
        for (s32 k = 2; k >= 0; k--) {
            *out++ = D_00275940[e / d];
            e = (e % d) * 10;
        }
    }
    return out - buf;
}


void func_001E17A8(Spec_001E1A08* spec, OutputBuffer* ctx, double value)
{
    char buf[0x1C0];
    char sign[16];
    char padc[16];
    s32 zeros = 0;
    s32 left;
    s32 lead;
    s32 n;
    s32 len;
    s32 slen;
    s32 width;
    s32 total;
    s32 neg;
    if (spec->i1C == 0 && spec->f14 == 0) {
        spec->i1C = 6;
    } else if (spec->f14 != 0 && spec->ch == 0x67) {
        spec->i1C = 1;
    }
    neg = value < 0.0;
    if (neg) value = 0.0 - value;
    sign[0] = 0;
    if (neg) __builtin_strcpy(sign, "-");
    else if (spec->f04) __builtin_strcpy(sign, "+");
    else if (spec->f08) __builtin_strcpy(sign, " ");
    slen = GetStringLength(sign);
    len = FormatFloatDigits(buf, 0x1B5, spec, value);
    buf[len] = 0;
    if (spec->f30) UppercaseString(buf);
    width = spec->f18;
    total = slen + len;
    lead = 0;
    left = 0;
    if (total < width) {
        s32 pad = width - total;
        if (spec->f00) left = pad;
        else if (spec->f10 && len != 0) zeros = pad;
        else lead = pad;
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
    n = zeros;
    AppendToOutputBuffer(ctx, sign, slen);
    padc[0] = '0';
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
    AppendToOutputBuffer(ctx, buf, len);
    n = left;
    padc[0] = ' ';
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
}


void func_001E1A08(Spec_001E1A08* sp, OutputBuffer* c, u8** va, const char* fmt, s32 len) {
    u64 v;
    switch (sp->ch) {
    case '%':
        AppendToOutputBuffer(c, (const char*)sp + 0x2C, 1);
        return;
    case 'c': {
        signed char buf[16];
        u8* p = *va;
        *va = p + 8;
        s32 ch = *(s8*)p;
        buf[0] = ch;
        AppendToOutputBuffer(c, (const char*)buf, 1);
        return;
    }
    case 's': {
        u8* p = *va;
        *va = p + 8;
        FormatStringArg(sp, c, *(const char**)p);
        return;
    }
    case 'p':
        sp->i1C = 8;
        sp->ch = 'x';
        sp->i20 = 0;
    case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
        switch (sp->i20) {
        case 0: case 1: { u8* p = *va; *va = p + 8; v = *(u32*)p; break; }
        case 2: { u8* p = *va; *va = p + 8; v = *(u64*)p; break; }
        }
        FormatIntegerArg(sp, c, v);
        return;
    case 'e': case 'f': case 'g':
        if (sp->i24 != 0) {
            const char* s4 = "
";
            u8* a = *va;
            const char* s8 = ",
";
            const char* s7 = "{ ";
            *va = a + 8;
            const char* s5 = ", ";
            const char* s6 = " }";
            f32* fp = *(f32**)a;
            if (sp->i28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
            for (s32 i = 0; i < sp->i28; ) {
                s32 next;
                if (i != 0) {
                    AppendToOutputBuffer(c, s8, GetStringLength(s8));
                }
                next = i + 1;
                AppendToOutputBuffer(c, s7, GetStringLength(s7));
                for (s32 j = 0; j < sp->i24; j++) {
                    if (j != 0) {
                        AppendToOutputBuffer(c, s5, GetStringLength(s5));
                    }
                    FormatFloatArg(sp, c, func_001FD868(*fp++));
                }
                AppendToOutputBuffer(c, s6, GetStringLength(s6));
                i = next;
            }
            if (sp->i28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
        } else {
            u8* p = *va;
            *va = p + 8;
            FormatFloatArg(sp, c, *(s64*)p);
        }
        return;
    case 'n':
        switch (sp->i20) {
        case 0: { u8* p = *va; *va = p + 8; **(s32**)p = c->count; break; }
        case 1: { u8* p = *va; *va = p + 8; s16* q = *(s16**)p; s32 n = c->count; *q = n; break; }
        case 2: { u8* p = *va; *va = p + 8; **(s64**)p = c->count; break; }
        }
        return;
    default:
        AppendToOutputBuffer(c, fmt, len);
        return;
    }
}


s32 func_001E1DB8(OutputBuffer* ctx, const char* fmt, void* a2)
{
    Locals_1E1DB8 loc;
    const char* s1 = fmt;

    loc.va = a2;
    if (*s1 != 0) {
        do {
            char* s2 = FindCharInString((Str_1E1DB8*)s1, '%');
            s32 n = (s32)s2 - (s32)s1;
            if (s2 == 0) {
                n = GetStringLength((Str_1E1DB8*)s1);
                s2 = (char*)((s32)s1 + n);
            }
            if (n != 0) {
                if (AppendToOutputBuffer(ctx, s1, n) < n) {
                    break;
                }
                s1 = s2;
            }
            if (*s1 == '%') {
                s32 n2 = ParseFormatSpec(s1, loc.spec, (void*)&loc.va);
                FormatConversionArg(loc.spec, ctx, (void*)&loc.va, s1, n2);
                s1 = s1 + n2;
            }
        } while (*s1 != 0);
    }
    FlushOutputBuffer(ctx);
    return ctx->count;
}

s32 func_001E1EB0(const char* fmt, void* ap)
{
    Stream_1E1EB0 buf;
    func_001D7100(&buf, -1);
    s32 n = FormatToOutputBuffer(&buf, fmt, ap);
    DestroyOutputBuffer(&buf, 2);
    return n;
}

s32 func_001E1F10(void* self, ...)
{
    void* ap = (char*)__builtin_next_arg(self) - 56;
    return PrintFormattedVa(self, ap);
}

s32 func_001E1F58(char* dst, const char* fmt, void* ap)
{
    Stream_001E1F58 buf;
    func_001D7120(&buf, dst, 0);
    s32 n = FormatToOutputBuffer(&buf, fmt, ap);
    dst += n;
    *dst = 0;
    DestroyOutputBuffer(&buf, 2);
    return n;
}

s32 func_001E1FD0(char* dst, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 48;
    return FormatToStringVa(dst, fmt, ap);
}

s32 func_001E2018(char* dst, s32 cap, s32 a, s32 b)
{
    u8 buf[0x420];
    s32 n;

    func_001D7120(buf, dst, cap);
    n = FormatToOutputBuffer(buf, a, b);
    if (n >= cap) {
        n = -1;
        dst[cap - 1] = 0;
    } else {
        dst[n] = 0;
    }
    DestroyOutputBuffer(buf, 2);
    return n;
}

LINKER_REMNANT(func_001E20B0);

s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 40;
    return FormatToStringBoundedVa(dst, cap, fmt, ap);
}

LINKER_REMNANT(func_001E20F8);

s32 func_001E2100(const char* s) { s32 length = 0; while (*s) { s++; length++; } return length; }

void* func_001E2138(void* dst, void* src)
{
    s32 n = GetStringLength(src);
    CopyMemory(dst, src, n + 1);
    return dst;
}

void* func_001E2180(void* dst, void* src)
{
    s32 len = GetStringLength(dst);
    s32 n = GetStringLength(src);
    CopyMemory((u8*)dst + len, src, n + 1);
    return dst;
}

char* func_001E21D8(char* s, s32 c)
{
    while (*s != 0) {
        if ((s8)*s == c) {
            return s;
        }
        s++;
    }
    return 0;
}

LINKER_REMNANT(func_001E2210);

void func_001E2218(s8* p)
{
    while (*p != 0) {
        s32 c = *p;
        s32 r = c;
        if (g_charClassFlags[c] & 2) {
            r = c - 0x20;
        }
        *p = r;
        p++;
    }
}

void func_001E2268(void* a, void* b)
{
    Ctor_1E2268 tmp;

    func_001F5C0C(&tmp, 0, 0x18);
    tmp.a = a;
    tmp.b = b;
    func_001F6B20(&tmp);
}

LINKER_REMNANT(func_001E22B8);

void func_001E22C0(IntPair_1E22C0* self)
{
    self->a = -1;
    self->b = CreateLockSemaphore(1, 1);
}

void func_001E22F8(Tally_1E22F8* self)
{
    s32 key = func_001F6A90();
    if (key != self->last) {
        (void)func_001F6B60(self->ptr);
        self->last = key;
        self->count = 1;
    } else {
        self->count++;
    }
}

void func_001E2358(Tally_1E2358* self)
{
    if (--self->count == 0) {
        self->last = -1;
        func_001F6B40(self->ptr);
    }
}

LINKER_REMNANT(func_001E2390);

void func_001E2398(void)
{
    Init_1E2398 l;

    g_mainAndRenderThreads.f0 = func_001F6A90();
    func_001F6A50(g_mainAndRenderThreads.f0, 4);
    (void)func_001F5C0C(&l, 0, sizeof(l));
    l.f0C = 0x20000;
    l.f08 = (s32)g_renderThreadStack;
    l.f14 = 2;
    l.f10 = (s32)D_002832F0;
    l.f04 = RunRenderThread;
    g_mainAndRenderThreads.f4 = func_001F6A10(&l);
}

void* func_001E2420(void* self) { return self ? (u8*)self + 0x2F0 : (void*)D_00275980; }

ASM_FUNC(func_001E2438);

void func_001E2520(OnOffObject* self)
{
    InitPlacedObject(self);
    self->block2F0 = *(Block63*)D_00275980;
    self->f428 = 2.0f;
    self->f42C = 1.0f;
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
    self->f420 = 2.0f;
    self->f424 = 1.0f;
    self->f430 = -1;
    self->quad450 = *(Quad63*)D_00275A10;
    {
        u8* src = (u8*)D_00275A20;
        self->pack460 = *(Pack63*)src;
    }
    self->f398 = -1;
}

void func_001E25F8(OnOffObject* self)
{
    UnregisterPlacedObject(self);
    SetOnOffObjectState(self, 0);
    RemoveQueuedCalls(self->world, 2, 0, self, -1, 0);
}

void func_001E2648(OnOffObject* self, void* a1)
{
    ReadBufferedRotation3(a1, &self->rot);
    ReadBufferedVector3(a1, &self->pos);
    const Desc01* vt = self->desc;
    if (vt->m12 != 0) {
        vt->m12(self);
    }
    ReadMeshTables(a1, (u8*)self + 0x2D4, (u8*)self + 0x2D8, (u8*)self + 0x2DC, (u8*)self + 0x2E0);
    s32 idx = ReadBufferedS8(a1);
    if (idx != -1) {
        Arr63* o = (Arr63*)CreatePathCurve(idx);
        self->obj = o;
        void** curveTable = *(void***)o;
        if (curveTable[0] != 0) {
            ((void (*)(void*, void*))curveTable[0])(o, a1);
        }
        Arr63* p = self->obj;
        self->f3F0 = p->data[p->count - 1];
    } else {
        ReadBufferedRotation3(a1, (u8*)self + 0x3B0);
        ReadBufferedVector3(a1, (u8*)self + 0x3E0);
        *(s32*)&self->f3F0 = 0;
    }
    self->i414 = (self->obj != 0) ? 7 : 5;
    ReadPropertyRecords(self, a1);
}

void func_001E2758(OnOffObject* self)
{
    StartPlacedObject(self);
}

void func_001E2778(void* selfv, s32 state)
{
    OnOffObject* self = (OnOffObject*)selfv;
    if (self->f394 == state) return;
    if (state != 0) {
        if (state != 1) {
            self->f394 = state;
            goto tail;
        }
        u32 base = (u32)g_camera;
        PushCameraController(base, self->f388 + 2, (void*)(base + 0x520), (s32)self->f2D0, self);
        TriggerScriptEvent(self, 2, 0, 0);
    } else {
        u32 base = (u32)g_camera;
        RemoveCameraControllers(base, 8, -1, 0, 0, self);
        TriggerScriptEvent(self, 3, 0, 0);
    }
    self->f394 = state;
tail:
    self->f39C = g_gameTime;
}

void func_001E2840(void* selfv, s32 value)
{
    OnOffObject* self = (OnOffObject*)selfv;
    if (value == self->f398) return;
    self->f398 = value;
    UpdateOnOffObjectState(self, 0, 0);
}

void func_001E2870(OnOffObject* self) {
    Loc_1E2870 loc;
    void* p = GetActiveSwitchedCollider();
    if (p == 0) {
        return;
    }
    if (p != self->f2D0) {
        SetOnOffObjectState(self, 0);
        self->f2D0 = p;
    }
    s32 st;
    if (self->f398 == -1) {
        func_00128018(0, self, (u8*)p + 0x140, &loc);
        s32 r = func_001E4DC0((Sub_1E2870*)self->f2E0, &loc);
        st = (0u < (u32)r);
    } else {
        st = self->f398;
    }
    if (self->f384 == 0 && p == (u8*)g_player && ((Pq_1E2870*)p)->f2220 == 2 &&
        ((Glob_1E2870*)g_camera)->f224 == 0) {
        if (self->f398 == -1) {
            return;
        }
    }
    SetOnOffObjectState(self, st);
}

void func_001E2940(OnOffObject* self)
{
    UpdatePlacedObject(self);
    if (self->f398 != 0) {
        AppendQueuedCall(self->world, (void*)(void (*)(OnOffObject*))UpdateOnOffObjectState, self, 0, 0);
    }
}

void func_001E2988(void)
{
    func_001261C0();
}

void func_001E29A8(OnOffObject* self, void* p)
{
    SetPlacedObjectFrozen(self, p);
    if (p != 0) {
        SetOnOffObjectState(self, 0);
    }
}

void func_001E29E8(OnOffObject* self, f32 value) { *(f32*)(self->block2F0.d + 0x74) = value; *(f32*)(self->block2F0.d + 0x78) = 1.0f; *(f32*)(self->block2F0.d + 0x70) = value; }

ASM_FUNC(func_001E2A00);

ASM_FUNC(func_001E2BF0);

ASM_FUNC(func_001E2E68);

void func_001E30A0(T2173_3F8* self)
{
    Sub_1E30A0* s = (Sub_1E30A0*)self->ptr;
    if (s != 0) {
        if (s->f438 != 0.0f) {
            Glob_1E30A0* g = (Glob_1E30A0*)g_camera;
            g->f1C8 = s->f43C;
        }
    }
    self->ptr = 0;
}

void func_001E30D8(T2173_3F8* self, s32 arg)
{
}

void func_001E30E0(T2173_3F8* self, s32 arg) {}

ASM_FUNC(func_001E30E8);

ASM_FUNC(func_001E31F0);

ASM_FUNC(func_001E4578);

f32 func_001E4880(void* a0, void* a1, void* a2, Ret_1E4880* a3)
{
    return a3->value;
}

INCLUDE_RODATA(D_0024E5F0);
ASM_FUNC(func_001E4888);

INCLUDE_ASM(func_001E4C48);

ASM_FUNC(func_001E4DC0);

Ctor_1E4E38::Ctor_1E4E38()
{
    f4 = 0;
    f10 = 0;
    fC = f8 = -1;
    func_001F5C0C(body, 0, 0x20);
}

Ctor_1E4E38 D_00275AF0;

void func_001E4E80(Blk_1E4E80* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->state == 0) {
        self->state = 1;
        self->a = a1;
        self->b = a2;
        self->c = a3;
        self->d = a4;
    }
}

void func_001E4EA8(Self_1E4EA8* self)
{
    KeyId key;
    Blob_1E4EA8 blob;
    S193210 o30;
    U32P w60, w70, w80, w90;
    Sub_1E4EA8 sub;
    func_00191E70(2);
    if (self->f4 != 0) {
        ClearKeyId(&key);
        blob = *self->f4;
        self->f4 = 0;
        key.second = blob.w[1] ^ blob.w[7];
        key.first = blob.w[0] ^ blob.w[5];
        if (key.second == 0) goto end;
        {
            Blob_1E4EA8* s2 = &self->f14;
            s32 ne = !Eq_1E4EA8::Of(&blob, s2);
            w60.v = 0x3F00;
            w70.v = 0x3F3F3F;
            w80.v = 0x3F3F;
            w90.v = 0x3F;
            InitLoadProgress(&o30, &w60, &w70, &w80, &w90);
            InitBufferedStream(&sub, 0x340C00, D_002C3B00, 6);
            sub.SetOwner(&o30);
            if (sub.owner != 0) func_00193270(sub.owner);
            if (OpenBufferedSectorStreamRange(&sub, &key) == 0) {
                DestroyBufferedStream(&sub, 2);
                goto end;
            }
            ResetWorldSubsystems(g_currentWorld);
            g_currentWorld = 0;
            ReadBufferedBlockHeader(ne, &sub);
            SetGameClockTime(((u8*)&g_gameClock), 0.0f);
            SetPadSelectFlags(0x80);
            self->f14 = blob;
            SetCurrentLevelEntry(s2, self->f10);
            g_currentWorld = CreateTypedRecord(0x6C, 0, 0, 3, -1);
            SetVolumeChannelFactor(0xA, 0, 0.0f);
            g_currentWorld->desc->m0A(g_currentWorld, &sub);
            CloseBufferedStream(&sub);
            if (sub.owner != 0) func_00193300(sub.owner);
            if (g_saveData->f19EC & 0x100) {
                Cur_1E4EA8* c = g_memoryCard.f4F44;
                if (c != 0 && (c->f19D8 != g_saveData->f19D8 || c->f19DC != g_saveData->f19DC))
                    StartMemoryCardSave(&g_memoryCard);
            }
            DestroyBufferedStream(&sub, 2);
        }
    }
    ResetCamera((*(s32*)&g_camera), 1);
    UpdateSoundEmitters();
    SetVolumeChannelFactor(0xA, 0, 1.0f);
    FindOrActivateSwitchedCollider(g_currentWorld, self->f8, self->fC);
    NotifyScatterControllerLoaded(g_scatterController);
    ResetCounter(D_002623D8);
    RestoreSelectionCaptionCamera(D_0026FA90);
    func_00138C00(g_currentWorld, 0);
    UpdateCamera((*(s32*)&g_camera), 0, g_frameStep);
    if (self->f10 & 0x10) ((VT1_1E4EA8*)D_0026C6C8.vt)->m38(&D_0026C6C8);
    SetGameClockScale(1.0f);
end:
    ResetVolumeChannelFactors();
    SetVolumeChannelFactor(1, 1, g_currentWorld->f1D7C);
    func_00191EB0(2);
    self->f0 = 0;
}

void func_001E5278(s32 mode)
{
    s32 n;
    func_001C05D0(0.0f);
    switch (mode) {
    case 0:
        n = 0;
        break;
    case 1:
        StartScreenFadeFromFlagTable((Ring_1E5278*)g_flagTable);
        return;
    case 2:
        n = 2;
        break;
    case 3:
        n = 4;
        break;
    }
    QueueWorldLoad((Blk_1E5278*)&g_worldLoadRequest, g_worldLoadRequest.body, -1, -1, n);
}


