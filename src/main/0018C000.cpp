// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "c49.h"
#include "game_clock.h"
#include "memory_card.h"
#include "object_link.h"
#include "buffered_stream.h"
#include "key_id.h"

s32 func_0018D1F8(void* self);

s32 func_0018C1A8(MemoryCard* self)
{
    s32 r = func_0018D1F8(self);
    if (r != 0) {
        self->targetState = 2;
    } else {
        self->targetState = 3;
    }
    return r;
}

struct Key_18C1E8 { s32 w0; s32 w4; s32 w8; s32 wC; };
struct Obj_18C1E8 { s32 f00; s32 f04; u8 pad08[0xC]; s32 f14; u8 pad18[4]; s32 f1C; };

void func_0018D410(void* p);
s32 func_001407A0(void* p);

s32 func_0018C1E8(Obj_18C1E8* self)
{
    Key_18C1E8 key;
    s32 flag;
    func_0018D410(&key);
    if (self == 0) {
        flag = 0;
    } else {
        s32 x = self->f04 ^ self->f1C;
        key.w0 = self->f00 ^ self->f14;
        key.w4 = x;
        flag = x != 0;
    }
    if (flag != 0) {
        return func_001407A0(&key);
    }
    return 0;
}

extern s32 func_0018C888(void*, void*, s32, void*, void*);
extern s32 func_0018BD00(s32, void*, s32);
extern void* func_00209FA8(s32, s32);
extern void* func_002096E8(s32, s32, void*);
extern void* func_002095B0(s32, s32, void*, void*);
extern void* func_00209720(void*);
extern void* func_00209990(void*, void*, void*);

s32 func_0018C9C0(void* a0, void* a1, void* a2)
{
	s32 temp;
	s32 result = func_0018C888(a0, a1, 1, a2, &temp);
	if (result != 0)
		return result;
	return temp == 1 ? 0 : 14;
}

struct Obj_18D168 { u8 pad0[4]; void* p4; void* p8; u8 pad1[0x18]; s32 p24; s32 p28; s32 p2C; };

s32 func_00209CB8(void* a, void* b, s32* c, s32* d, s32* e);
s32 func_0018BD00(s32 v, s32 code, s32 extra);
struct State_18CFC0 { s32 type; s32 size; s32 handle; };
extern s32 func_00160650(void*);
extern s32 func_0018D368(void*, void*, void*, s32);

s32 func_0018CFC0(void* owner, void* name, State_18CFC0* state)
{
    state->type = 18;
    state->size = 0x1A00;
    return func_0018D368(owner, name,
        (state->handle = func_00160650(state), state), 0x1A00);
}

extern void func_001605E8(void*);
extern s32 func_0018CFC0(void*, void*, void*);
extern s32 func_0018C9C0(void*, void*, void*);

s32 func_0018D028(void* a0, void* a1, void* a2, void* a3)
{
    u8 local[0x60];
    func_001605E8(a2);
    if (a3 == 0) a3 = local;
    s32 result = func_0018CFC0(a0, a1, (State_18CFC0*)a2);
    if (result != 0) return result;
    return func_0018C9C0(a0, a1, a3);
}

s32 func_0018D168(Obj_18D168* a0, s32* a1)
{
    s32 v = func_0018BD00(func_00209CB8(a0->p4, a0->p8, &a0->p24, &a0->p28, &a0->p2C), 1, 0);
    switch (v) {
    case 9: v = 0; break;
    case 10: v = 12; break;
    }
    if (v == 0) { *a1 = a0->p28 << 10; } else { *a1 = 0; }
    return v;
}

s32 func_0018D1F8(void* p)
{
	void* result = func_00209FA8(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8));
	return func_0018BD00((s32)result, (void*)0x10, 0);
}

s32 func_0018D228(void* p, void* value)
{
	s32 result = func_0018BD00((s32)func_002096E8(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8), value), (void*)0xB, 0);
	return result == 0x18 ? 0 : result;
}

s32 func_0018D268(void* p, void* a1, void* a2, void* a3)
{
	return func_0018BD00((s32)func_002095B0(*(s32*)((char*)p + 4), *(s32*)((char*)p + 8), a1, a2), (void*)2, (s32)a3);
}

void func_0018D2B0(void* unused, void* value)
{
	func_0018BD00((s32)func_00209720(value), (void*)3, 0);
}

s32 func_00209870(void* a, void* b, void* c);
s32 func_0018BD00(s32 v, s32 code, void* extra);

s32 func_0018D2E8(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    return func_0018BD00(func_00209870(a1, a2, a3), 5, a4);
}

void func_0018D328(void* unused, void* a1, void* a2, void* a3, void* a4)
{
	func_0018BD00((s32)func_00209990(a1, a2, a3), (void*)6, (s32)a4);
}

struct Result_18D368 { s32 first; s32 second; };
extern s32 func_0018D268(void*, void*, void*, void*);
extern void func_0018D328(void*, void*, void*, void*, void*);
extern void func_0018D2B0(void*, void*);

s32 func_0018D368(void* self, void* code, void* data, s32 version)
{
    Result_18D368 result;
    result.first = -1;
    s32 status = func_0018D268(self, code, (void*)514, &result.first);
    if (status != 0) return status;
    status = ((s32 (*)(void*, void*, void*, void*, void*))func_0018D328)(self, (void*)result.first, data, (void*)version, &result.second);
    if (status == 0) status = result.second == version ? 0 : 7;
    func_0018D2B0(self, (void*)result.first);
    return status;
}

void func_0018D4F8(s32 size)
{
    (void)size;
}

extern u8* D_002C2A1C;

void func_0018D4F8(s32 size);

u8* func_0018D500(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    func_0018D4F8(size);
    result = D_002C2A1C;
    D_002C2A1C = result + ((size + 15) & ~15);
    return result;
}

extern u8* D_002C2A18;

void func_0018D550(void)
{
    D_002C2A1C = D_002C2A18;
}

u8* func_0018D500(s32 size);
void func_0018D800(u8* dst, void* src, s32 count);

u8* func_0018D568(s32 size, void* src)
{
    u8* result = func_0018D500(size);

    if (result != 0) {
        func_0018D800(result, src, size);
    }
    return result;
}

void* func_0018D500(u32 n);
void func_001F5C0C(void* p, s32 v, s32 n);

void* func_0018D5C0(u32 n)
{
    void* p = func_0018D500(n);
    if (p) {
        func_001F5C0C(p, 0, n);
    }
    return p;
}

extern u8 D_002C2A28[];
extern s32 D_002C2A34;
extern u8* D_002C2A20;
extern u8 D_002C2A38[];

void func_001E22F8(void* obj);

void func_0018D608(void)
{
    func_001E22F8(D_002C2A28);
    D_002C2A34 = D_002C2A34 + 1;
    ((u8**)D_002C2A38)[D_002C2A34] = D_002C2A20;
}

u8* func_0018D658(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    func_0018D4F8(size);
    result = D_002C2A20;
    result = result - ((size + 15) & ~15);
    D_002C2A20 = result;
    return result;
}

int func_0018D740(void)
{
    return 0;
}

void func_0018D778(void* self)
{
}

void func_0013B4C0(void* self);

void func_0013B598(void* self);
void func_00124DF8(void* self, s32 mode, void* data);

void func_0018E6A0(void* self);

void func_001F6C20(s32 a);
s32 func_001F6C90(void* obj);

s32 func_0018F940(s32 a, s32 b);

void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_0018F988(C49* self)
{
    func_001B7968(self);
    self->flags538 |= (u64)0x8000 << 28;
    func_001B9AE0(self, 3, 0, 3, 0);
}

void func_001C6F48(void* self);

void func_0018FEF8(C0E* self)
{
    func_001C6F48(self);
    self->fBD4 = 0;
    self->fBD0 = 0;
}

void func_001C72A0(void* self);
void func_00124DF8(void* self, s32 n, void* table);
s32 func_001CA758(void* self, s32 id);

void func_0018FF28(C0E* self)
{
    func_001C72A0(self);
    func_00124DF8(self, 2, D_00269B60);
    self->f5F0 = (void*)func_001CA758(self, 0xEF);
    self->fC38 = func_001CA758(self, 0x16C);
    self->fC3C = func_001CA758(self, 0x16D);
    self->fC40 = func_001CA758(self, 0x16A);
    self->fC44 = func_001CA758(self, 0x16B);
}

void func_001CB6F8(void* a, void* b);
void func_001C91C8(void* self, s32 a, s32 b);

void func_0018FFB0(C0E* self, s32 a1, s32 a2)
{
    s32 a2v = a2;
    switch (self->f724) {
    case 4:
        self->fC28 = 0;
        self->fC10 = 0;
        break;
    case 0x10:
        if (self->fC30 == 4) {
            a2v = self->fC44;
        } else {
            a2v = self->fC3C;
        }
        break;
    case 0xB:
        if (self->fC30 == 4) {
            a2v = self->fC40;
        } else {
            a2v = self->fC38;
        }
        if (self->f720 != 0) {
            func_001CB6F8(self->f720, self);
        }
        break;
    }
    func_001C91C8(self, a1, a2v);
    s32 kind = self->f724;
    if (kind == 0xB || kind == 0x10) {
        self->fC04 = 0;
    }
}

void func_001F5C0C(void* p, s32 v, s32 n);

void func_0018D410(void* p)
{
    func_001F5C0C(p, 0, 8);
}

s32 func_001833F0(void* key, void* item);
s32 func_001300E8(void* key, void* item);
s32 func_001B8A08(void* self, void* key);

u8* func_0018D658(s32 size);
void func_001F5C0C(void* p, s32 v, s32 n);

void* func_0018D6A8(s32 size)
{
    u8* p = func_0018D658(size);
    if (p) {
        func_001F5C0C(p, 0, size);
    }
    return p;
}

extern u8 D_002C2A28[];
extern s32 D_002C2A34;
extern u8* D_002C2A20;
extern u8 D_002C2A38[];

void func_001E2358(void* obj);

void func_0018D6F0(void)
{
    s32 n = D_002C2A34;
    u8** slot = &((u8**)D_002C2A38)[n];
    n = n - 1;
    D_002C2A34 = n;
    D_002C2A20 = *slot;
    func_001E2358(D_002C2A28);
}

void func_0011E460(void);
void func_0013C9B0(void* state);
void func_0018E6A0(void* self);

void func_0018F198(void* self, s32 value);

s32 func_0018D748() { return 0; }

void func_0018D750() {}

struct Elem_18C028 { u8 pad0[0xC]; f32 fC; u8 pad1[0x1A4C]; };

extern u8 D_00269990[];

s32 func_0018BFA8(void* lhs, void* rhs);
void func_001605E8(void* self);
void func_0018B670(void* a, void* fn, void* self);
s32 func_0018C420(void* self);
s32 func_0018D0A0(void* self);

void func_0018C028(MemoryCard* self, s32 value)
{
    s32 old = self->state;
    s32 n;
    if (value == old) return;
    if (old == 5) self->f4F48 = 0;
    if (value == 3) goto c420;
    if (value < 4) goto small;
    if (value == 5) goto loop;
    goto store;
small:
    if (value >= 2) goto store;
    if (value < 0) goto store;
    func_0018B670(g_backgroundJob, (void*)func_0018D0A0, self);
    goto store;
c420:
    func_0018B670(g_backgroundJob, (void*)func_0018C420, self);
    goto store;
loop: {
    Elem_18C028* e;
    Elem_18C028* p = (Elem_18C028*)((u8*)self + 0x1A30);
    e = (Elem_18C028*)(self->f4F48 = (u8*)self + 0x30);
    n = 2;
    do {
        if (e->fC != 0.0f) {
            s32 r = func_0018BFA8((u8*)self->f4F48 + 0x1A00, p);
            if (r < 0) self->f4F48 = e;
        } else {
            func_001605E8(e);
        }
        p = (Elem_18C028*)((u8*)p + 0x1A5C);
        e = (Elem_18C028*)((u8*)e + 0x1A5C);
    } while (--n >= 0);
}

store:
    self->state = value;
    self->stateTime = D_00261858.elapsed;
}

extern f32 D_00261868[];

void func_0018C178(MemoryCard* self, s32 value)
{
    if (value != self->displayMode) {
        if (value == 2) self->i4F44 = 0;
        self->displayMode = value;
        self->displayModeTime = D_00261868[0];
    }
}

typedef void (*VFn_18C7F8)(void* self);
struct Gx_18C7F8 { u8 pad0[0x27C]; s32 f27C; };
struct __attribute__((packed)) Pk_18C7F8 { s32 v; };
struct Obj_18C7F8 { VFn_18C7F8* vtbl; };

extern u8 D_00269990[];
extern Gx_18C7F8 D_0026FF68[];
extern Obj_18C7F8 D_00273EB0[];

void func_00194D30(void* self, s32 a, s32 b);
void func_0018B670(void* a, void* fn, void* self);
s32 func_0018C638(void* self);

void func_0018C7F8(MemoryCard* self)
{
    if (self->i4F44 != 0) {
        if ((D_002623C0->f19EC & 0x100) == 0) {
            D_0026FF68->f27C = -1;
            func_00194D30(D_0026FF68, 1, 0x14);
        } else {
            func_0018B670(g_backgroundJob, (void*)func_0018C638, self);
            u8* obj = (u8*)D_00273EB0;
            ((Pk_18C7F8*)(obj + 0x260))->v = 0;
            ((Obj_18C7F8*)obj)->vtbl[14](obj);
        }
    }
}

struct Ctx_18C888 { u8 pad0[4]; void* p4; void* p8; };

extern u8 D_002BE540[];
extern u8 D_002BE9C0[];

s32 func_001E2100(void* p);
void* func_001E2138(void* dst, void* src);
void func_001F5C0C(void* p, s32 zero, s32 size);
s32 func_00209E48(void* a, void* b, void* c, s32 d, s32 e, void* f);
s32 func_0018BD00(s32 v, s32 code, void* extra);
void func_0018B780(void* a, void* b);

s32 func_0018C888(Ctx_18C888* a, u8* b, s32 c, u8* d, s32* e)
{
    s32 flag;
    s32 r;
    u8* t;
    s32 i;
    u8* buf;
    if (c >= 0x13) {
        return 0x25;
    }
    if (b != 0) {
        if ((u32)func_001E2100(b) >= 0x41) {
            return 0xD;
        }
        func_001E2138(D_002BE9C0, b);
        flag = 0;
    } else {
        flag = 1;
        b = D_002BE9C0;
    }
    buf = D_002BE540;
    func_001F5C0C(buf, 0, 0x480);
    r = func_0018BD00(func_00209E48(a->p4, a->p8, b, flag, c, buf), 0xD, e);
    if (r != 0) {
        return r;
    }
    i = 0;
    if (*e > 0) {
        t = d;
        do {
            func_0018B780(buf, t);
            i++;
            t += 0x5C;
            buf += 0x40;
        } while (i < *e);
    }
    return 0;
}

extern u8* D_002C2A14;
extern u8* D_002C2A18;
extern u8* D_002C2A1C;

u8* func_0018D4B0(s32 size)
{
    u8* result;
    u8* next;

    if (size == 0) {
        return 0;
    }
    result = D_002C2A14;
    next = result + ((size + 15) & ~15);
    D_002C2A14 = next;
    D_002C2A18 = D_002C2A1C = next;
    return result;
}

void func_001B7B78(void* self);
void func_0012E760(void* obj);

extern u8* D_00275710;
extern u8 D_002CBB40[];

void func_0011D6A8(u32 a0);
void func_0011D6D8(s32 a0);
void func_0011E010(void);
s32 func_0011CE30(void);
void func_0011E110(s32 a0);
s32 func_0011E1F8(s32 flag);
void func_0011D4B8(s32 arg);
void func_0011D480(s32 a0, s32 a1);
void func_0011E428(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001C08B0(void* p, s32 a, s32 b);
void func_0013C988(void* state, s32 initialValue, void* secondaryValue);
void func_0018E678(void* self, s32 a1, s32 a2);

extern u8* D_00275710;

void func_0011E498(void);
void func_0011D480(s32 a0, s32 a1);
void func_001C0950(void* p);
void func_0011D6D8(u32 a0);

s32 func_0013CC00(void* a, u32 b, void* c);

void* func_0018D5C0(u32 n);

void* func_0018D758(u32 n)
{
    return func_0018D5C0(n);
}

s32 func_0018EAF8(void* self, s32 a, s32 b);

s32 func_0018F890(void* self, s32 flag);

struct Blk_18EB98 { u8 b[0x24]; };

s32 func_0013CAD8(Blk_18EB98* a, s32 b, void* c);
void func_0011E4C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_0018E838(void* p);

// was NEAR: the shift arm: retail branches with bnez on (v < 16) to the sllv, with li v0,1 in the delay slot; ours uses beqz and the arms swap

s32 func_0018E410(void* p);

s32 func_0013CC00(void* sub, s32 a, s32 b);

typedef u64 Q18D780 __attribute__((mode(TI)));

void func_0018D780(Q18D780* dst, Q18D780* src, s32 n)
{
    Q18D780* d = dst;
    Q18D780* s = src;
    s32 rem = n & 3;
    s32 total = n - rem;
    s32 k;
    if (rem != 0) {
        k = rem;
        do {
            *d++ = *s++;
        } while (--k != 0);
    }
    if (total > 0) {
        k = 0;
        do {
            Q18D780 q0 = s[0];
            Q18D780 q1 = s[1];
            Q18D780 q2 = s[2];
            Q18D780 q3 = s[3];
            s += 4;
            k += 4;
            d[0] = q0;
            d[1] = q1;
            d[2] = q2;
            d[3] = q3;
            d += 4;
        } while (k < total);
    }
}

struct __attribute__((aligned(16))) Quad_18DB20 { s32 a, b, c, d; };
struct __attribute__((aligned(16))) Tbl3_18DB20 { Quad_18DB20 q[3]; };
struct __attribute__((aligned(16))) Blk4_18DB20 { Quad_18DB20 q[4]; };

typedef void (*VFn_18DB20)(void* self, f32 f, void* a, void* b);
struct Obj_18DB20 { VFn_18DB20* vtbl; };

extern u8 D_00248D30[];
extern u8 D_002483D0[];

void func_00125B70(void* obj, void* c, void* out);
void func_00188B08(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);
void func_00125C90(void* obj, void* s, void* out);

extern const u32 D_00248470[8];
extern void* func_0020A078(void*, void*, const char*);
extern s32 func_0018BD00(void*, s32, void*);
extern s32 func_0018C1E8(void*);
extern s32 func_0018D228(void*, const char*);
extern s32 func_0018D368(void*, const char*, const char*, s32);
extern s32 func_0018CA10(void*, const char*, const char*);
extern s32 func_0018CBF8(void*, const char*);
extern s32 func_001E1FD0(char*, const char*, ...);
extern s32 func_0018D028(void*, void*, void*, void*);

s32 func_0018C250(MemoryCard* self)
{
    char name[0x50];
    s32 info[4];
    s32 r = func_0018BD00(func_0020A078(self->port, self->slot, "/"), 0x12, info);
    if (r != 0) return r;
    s32 need = info[0] == 0 ? 2 : 1;
    s32 sz = func_0018C1E8((void*)D_00248470);
    need += 5;
    need += (sz + 1023) / 1024;
    need += 0x15;
    if (self->freeBlocks < need) return 1;
    const char* dir = "/BASCUS-97198YAOTWTD!";
    r = func_0018D228(self, dir);
    if (r == 0) {
        const char* title = "Sly Cooper";
        r = func_0018D368(self, "/BASCUS-97198YAOTWTD!/BASCUS-97198YAOTWTD!", title, 10);
        if (r == 0) {
            r = func_0018CA10(self, dir, title);
            if (r == 0) {
                r = func_0018CBF8(self, dir);
                if (r == 0) {
                    for (s32 i = 0; i < 3; i++) {
                        func_001E1FD0(name, "/%s/%s%d", "BASCUS-97198YAOTWTD!", "save", i + 1);
                        r = func_0018D028(self, name, (u8*)self + 0x30 + i * 0x1A5C, (u8*)self + 0x1A30 + i * 0x1A5C);
                        if (r != 0) return r;
                    }
                    if (self->targetState < 5) self->targetState = 5;
                }
            }
        }
    }
    return r;
}

extern u32 D_00269A00[];
extern s32 D_00261F1C;

s32 func_001F6B60(s32 a);
void func_001686E8(s32 a, s32 b);
void func_001684E8(void);
void func_001683E8(void);

extern u8 D_005A2E60[];
extern u8 D_00269B48[];

extern s32 D_002626CC;

void func_001B3450(void);

extern const char D_0024B3A0[16];
extern const char D_0024B3B0[24];
extern const char D_0024B3C8[8];

struct Buf_18C770 { u8 bytes[0x50]; };

s32 func_001E1FD0(Buf_18C770* dst, const char* fmt, ...);
s32 func_0018D028(MemoryCard* self, Buf_18C770* buf, void* a2, void* a3);

s32 func_0018C770(MemoryCard* self)
{
    Buf_18C770 buf;
    s32 f = self->i4F4C;
    s32 n;
    s32 g;

    if (f == 0) {
        return 0x2C;
    }
    n = f - 0x30;
    n = n - (s32)self;
    n = n * 0x26FFD927;
    n = (n >> 2) + 1;
    func_001E1FD0(&buf, D_0024B3A0, D_0024B3B0, D_0024B3C8, n);
    g = self->i4F4C;
    return func_0018D028(self, &buf, (void*)g, (void*)(g + 0x1A00));
}

struct Obj_18CBF8;

s32 func_0018CC20(Obj_18CBF8* self, void* b, void* c, void* d);

extern const u32 D_00248470[8];
extern const char D_0024B3D8[8];

void func_0018CBF8(Obj_18CBF8* self, void* b)
{
    func_0018CC20(self, b, (void*)D_00248470, (void*)D_0024B3D8);
}

extern u8 D_00248D30[];

extern const u32 D_002484B0[128];

extern u8* D_002699C0[16];
extern const char D_0024B580[8];
extern const char D_0024B588[16];

extern u32 D_00269A00[];
extern const u32 D_002484B0[128];

extern const u32 D_002484B0[128];
extern u32 D_00269A08[57];

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0024B598[];

void func_001F5C0C(void* dst, s32 value, s32 size);

extern const Fn_Table D_0024B5B8[];
extern void* D_00269AEC;

s32 func_00209CB8(void* a, void* b, s32* c, s32* d, s32* e);
s32 func_0018BD00(s32 v, s32 code, s32 extra);

s32 func_0018D0A0(MemoryCard* o)
{
    s32 r = func_0018BD00(func_00209CB8(o->port, o->slot, &o->f24, &o->freeBlocks, &o->f2C), 1, 0);
    switch (r) {
    case 9:
    case 11:
        o->targetState = 1;
        r = 11;
        break;
    case 10:
    case 12:
        o->targetState = 2;
        r = 12;
        break;
    case 0:
        if (o->f2C != 0) {
            if (o->targetState < 3)
                o->targetState = 3;
            else
                break;
        } else
            o->targetState = 2;
        break;
    }
    o->nextPollTime = D_00261868[0] + 0.3f;
    return r;
}

// EXACT: i declared before blocks, assigned inside the if(size != 0)

void func_0018D780(void* dst, void* src, u32 count);

void func_0018D800(u8* dst, u8* src, u32 size)
{
    u32 any = (u32)dst | (u32)src | size;
    if (any & 3) {
        u32 i = 0;
        if (size != 0) {
            do {
                *dst++ = *src++;
                i++;
            } while (i < size);
        }
    } else if (any & 0xF) {
        s32 words = size >> 2;
        u32* wd = (u32*)dst;
        size = words & 3;
        u32* ws = (u32*)src;
        s32 i;
        s32 blocks = words - size;
        if (size != 0) {
            i = size;
            do {
                *wd++ = *ws++;
                i--;
            } while (i != 0);
        }
        if (blocks > 0) {
            i = 0;
            do {
                u32 a = ws[0];
                i += 4;
                u32 b = ws[1];
                u32 c = ws[2];
                u32 d = ws[3];
                wd[0] = a;
                ws += 4;
                wd[1] = b;
                wd[2] = c;
                wd[3] = d;
                wd += 4;
            } while (i < blocks);
        }
    } else {
        func_0018D780(dst, src, size >> 4);
    }
}

struct Blob_18C638 { s32 w[0x1A00 / 4]; };
struct Buf_18C638 { u8 bytes[0x50]; };
struct Ctx_18C638;

extern const char D_0024B3A0[16];
extern const char D_0024B3B0[24];
extern const char D_0024B3C8[8];

void func_001A7E90(Ctx_18C638* ctx);
s32 func_001E1FD0(Buf_18C638* dst, const char* fmt, ...);
s32 func_0018CFC0(MemoryCard* owner, Buf_18C638* name, u8* state);

s32 func_0018C638(MemoryCard* self)
{
    Buf_18C638 buf;
    s32 n;

    if (self->p4F44 == 0) {
        return 0x2C;
    }
    func_001A7E90((Ctx_18C638*)(*(u8**)&D_002623C0));
    *(Blob_18C638*)self->p4F44 = *(Blob_18C638*)(*(u8**)&D_002623C0);
    n = (s32)self->p4F44 - 0x30;
    n = n - (s32)self;
    n = n * 0x26FFD927;
    n = (n >> 2) + 1;
    func_001E1FD0(&buf, D_0024B3A0, D_0024B3B0, D_0024B3C8, n);
    return func_0018CFC0(self, &buf, self->p4F44);
}

struct Src_18CA10 {
    s32 w0;
    u8 b4;
};
struct Name_18CA10 {
    u8 b[8];
};
struct Cfg_18CA10 {
    s32 f000;
    u8 f004;
    s16 f006;
    u8 pad08[4];
    s32 f00C;
    s32 f010;
    s32 f014;
    s32 f018;
    u8 pad1C[4];
    s32 f020;
    s32 f024;
    s32 f028;
    u8 pad2C[4];
    s32 f030;
    s32 f034;
    s32 f038;
    u8 pad3C[4];
    s32 f040;
    s32 f044;
    s32 f048;
    u8 pad4C[4];
    s32 f050;
    f32 f054;
    f32 f058;
    u8 pad5C[4];
    f32 f060;
    f32 f064;
    f32 f068;
    u8 pad6C[4];
    f32 f070;
    f32 f074;
    f32 f078;
    u8 pad7C[4];
    f32 f080;
    f32 f084;
    f32 f088;
    u8 pad8C[4];
    f32 f090;
    s32 f094;
    f32 f098;
    u8 pad9C[4];
    f32 f0A0;
    f32 f0A4;
    f32 f0A8;
    u8 padAC[4];
    f32 f0B0;
    f32 f0B4;
    f32 f0B8;
    u8 padBC[4];
    u8 pad0C0[0x104 - 0xC0];
    Name_18CA10 f104;
    u8 pad10C[0x144 - 0x10C];
    Name_18CA10 f144;
    u8 pad14C[0x184 - 0x14C];
    Name_18CA10 f184;
    u8 pad18C[0x3C4 - 0x18C];
};

struct Obj_18CA10 { u8 pad[1]; };
struct Owner_18CA10 { u8 pad[1]; };
struct Buf_18CA10 { char s[0x50]; };

extern const Src_18CA10 D_0024B3D0;
extern const char D_0024B3E0[8];
extern const char D_0024B3E8[24];

s32 func_001F5C0C(Cfg_18CA10* dst, s32 value, s32 size);
void func_001B5C40(Obj_18CA10* p, void* q);
s32 func_001E1FD0(Buf_18CA10* dst, const char* fmt, ...);
s32 func_0018D368(Owner_18CA10* a, Buf_18CA10* b, Cfg_18CA10* c, s32 d);

s32 func_0018CA10(Owner_18CA10* owner, void* a1, Obj_18CA10* a2)
{
    Cfg_18CA10 c;
    Buf_18CA10 buf;
    (void)func_001F5C0C(&c, 0, 0x3C4);
    c.f000 = ((Src_18CA10*)&D_0024B3D0)->w0;
    c.f004 = ((Src_18CA10*)&D_0024B3D0)->b4;
    c.f006 = 0x20;
    c.f00C = 0x60;
    c.f010 = 0;
    c.f014 = 0x87;
    c.f018 = 0xFF;
    c.f020 = 0;
    c.f024 = 0x29;
    c.f028 = 0x6F;
    c.f030 = 0;
    c.f034 = 0x29;
    c.f038 = 0x6F;
    c.f040 = 0;
    c.f044 = 0x87;
    c.f048 = 0xFF;
    c.f050 = 0;
    c.f054 = 0.5f;
    c.f058 = -0.5f;
    c.f060 = 0.5f;
    c.f064 = -0.4f;
    c.f068 = 0.1f;
    c.f070 = -0.5f;
    c.f074 = 0.5f;
    c.f078 = 0.5f;
    c.f080 = 0.14f;
    c.f084 = 0.03f;
    c.f088 = 0.48f;
    c.f090 = 0.33f;
    c.f094 = 0;
    c.f098 = 0.33f;
    c.f0A0 = 0.14f;
    c.f0A4 = 0.14f;
    c.f0A8 = 0.38f;
    c.f0B0 = 0.5f;
    c.f0B4 = 0.5f;
    c.f0B8 = 0.5f;
    func_001B5C40(a2, (u8*)&c + 0xC0);
    c.f104 = (*(Name_18CA10*)&D_0024B3D8);
    c.f144 = (*(Name_18CA10*)&D_0024B3D8);
    c.f184 = (*(Name_18CA10*)&D_0024B3D8);
    func_001E1FD0(&buf, D_0024B3E0, a1, D_0024B3E8);
    return func_0018D368(owner, &buf, &c, 0x3C4);
}

struct Self_18CC20 { u8 pad[16]; };
struct Key_18CC20 { s32 w0; s32 w4; u8 pad8[0xC]; s32 w14; u8 pad18[4]; s32 w1C; };
void func_0018D410(KeyId* p);
struct Pair_18CC20 : KeyId {
    s32 Set(Key_18CC20* key)
    {
        s32 has;
        func_0018D410(this);
        if (!key) {
            has = 0;
        } else {
            s32 t = key->w4 ^ key->w1C;
            second = t;
            first = key->w0 ^ key->w14;
            has = t != 0;
        }
        return has;
    }
};

extern const char D_0024B3E0[8];
void func_0018D608(void);
u8* func_0018D658(s32 size);
s32 func_00137290(BufferedStream* o, s32 a, u8* b, s32 c);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
s32 func_0018D268(Self_18CC20* s, char* a, s32 b, s32* c);
void func_0018D410(KeyId* p);
s32 func_001373B0(BufferedStream* o, KeyId* p);
void func_00137A60(BufferedStream* o, s32 n, u8* d);
s32 func_0018D328(Self_18CC20* s, s32 a, u8* d, s32 n, s32* out);
void func_001373D0(BufferedStream* o);
s32 func_0018D2B0(Self_18CC20* s, s32 a);
void func_0018D6F0(void);
void func_001372E0(BufferedStream* o, s32 f);

s32 func_0018CC20(Self_18CC20* self, s32 a1, Key_18CC20* key, s32 a3)
{
    char text[0x50];
    BufferedStream obj;
    Pair_18CC20 pair;
    u8 data[0x1000];
    s32 code;
    s32 got;
    s32 status;

    func_0018D608();
    code = -1;
    (void)func_00137290(&obj, 0x8040, func_0018D658(0x8040), 0);
    func_001E1FD0(text, D_0024B3E0, a1, a3);
    status = func_0018D268(self, text, 0x202, &code);
    if (status == 0) {
        if (!pair.Set(key) || !func_001373B0(&obj, &pair)) {
            status = 0x27;
        } else {
            s32 left = obj.f10;
            while (left > 0) {
                s32 n = 0x1000;
                if (left <= 0xFFF) n = left;
                func_00137A60(&obj, n, data);
                status = func_0018D328(self, code, data, n, &got);
                if (status) goto done;
                left -= got;
                if (got != n) { status = 7; goto done; }
            }
            status = 0;
        }
    done:
        func_001373D0(&obj);
        s32 r = func_0018D2B0(self, code);
        if (status == 0) status = r;
        func_0018D6F0();
    }
    func_001372E0(&obj, 2);
    return status;
}

struct Key_18F198 {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
    u32 w4;
    u32 w5;
    u32 w6;
    u32 w7;
    s32 Same(Key_18F198* b)
    {
        Key_18F198* a = this;
        if (a == b) return 1;
        if (!a) return 0;
        if (!b) return 0;
        return ((a->w2 ^ a->w6) ^ (b->w2 ^ b->w6)) == 0;
    }
};
struct Key_18F198;
struct Pair_18F198;
void func_0018D410(Pair_18F198* p);
struct Pair_18F198 {
    u32 k[2];
    s32 Set(Key_18F198* key)
    {
        func_0018D410(this);
        s32 ok;
        if (!key) {
            ok = 0;
        } else {
            u32 t = key->w1 ^ key->w7;
            k[1] = t;
            k[0] = key->w0 ^ key->w5;
            ok = t != 0;
        }
        return ok;
    }
};

extern u8 D_002C3B00[];
extern u8 D_00275F80[];
extern s32 D_002613EC;

extern const Key_18F198 D_00248490;
void func_00191E70(s32 v);
s32 func_0018E410(Key_18F198* k);
void func_0018D410(Pair_18F198* k);
void func_00143030(u8* t);
void func_001409E0();
s32 func_0020B0B0(u8* l);
void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00191EB0(s32 v);

struct Ent_18C420 {
    u8 a[0x1A00];
    u8 b[0x5C];
};

struct Self_18C420 {
    u8 p00[4];
    void* f4;
    void* f8;
    u8 p0C[0x14 - 0x0C];
    s32 f14;
    u8 p18[0x30 - 0x18];
    Ent_18C420 ent[3];
};

struct Buf_18C420 {
    u8 raw[0x50];
};

extern const char D_0024B348[24];
extern const char D_0024B3A0[16];
extern const char D_0024B3B0[24];
extern const char D_0024B3C8[8];

s32 func_00209E48(void* a, void* b, void* c, s32 d, s32 e, void* f);
s32 func_0018BD00(s32 v, s32 code, s32* out);
s32 func_0018D168(Self_18C420* a0, s32* a1);
s32 func_001E1FD0(Buf_18C420* dst, const char* fmt, ...);
s32 func_0018CDD8(Self_18C420* self, Buf_18C420* buf, u8* a, u8* b);

s32 func_0018C420(Self_18C420* self) {
    Buf_18C420 buf;
    s32 r;
    s32 n;
    Ent_18C420* e;
    s32 local50;
    s32 local54;

    r = func_0018BD00(func_00209E48(self->f4, self->f8, (void*)D_0024B348, 0, -1, 0), 0xD, &local50);
    if (local50 <= 0) {
        func_0018D168(self, &local54);
        if (local54 <= 0xC3FF) {
            self->f14 = 4;
        }
        return 0xE;
    }
    n = 0;
    if (r == 0) {
        for (; r == 0 && n < 3; n++) {
            func_001E1FD0(&buf, D_0024B3A0, D_0024B3B0, D_0024B3C8, n + 1);
            (void)func_0018CDD8(self, &buf, self->ent[n].a, self->ent[n].b);
        }
        if (r == 0 && self->f14 < 5) {
            self->f14 = 5;
        }
    }
    return r;
}

// EXACT: f04,f08,f10,f0C,f14 store order; func_001F5C0C declared s32, called as (void)

extern u32 D_00269A00[];
extern u8 D_002C2B00[];
extern u8 D_002832F0[];
extern s32 D_00275964;

void func_0018E558(void);

extern u8 D_0064C70F[];
s32 D_002699A4 = 0;
extern s32 D_002699A8;
extern s32 D_002C2A10;
extern s32 D_002C2A24;
extern u8 D_002C2A28[];
extern s32 D_002C2A34;
void func_001E22C0(void* self);

void func_0018D430(void)
{
    D_002699A4 = (s32)D_0064C70F & -16;
    D_002699A8 = 0x2000000;
    // The heap's pointers (u8* elsewhere in this file), written as words.
    D_002C2A10 = *(s32*)&D_002C2A14 = *(s32*)&D_002C2A18 = *(s32*)&D_002C2A1C = D_002699A4;
    *(s32*)&D_002C2A20 = D_002C2A24 = D_002699A8;
    D_002C2A34 = -1;
    func_001E22C0(D_002C2A28);
}

void func_00189350(u8* a, u8* b);

struct Buffer_18F890 { u8 pad00[0x18]; s32 head; s32 base; s32 tail; };
struct Empty_18F890 {
    static bool Of(Buffer_18F890* b) { return b->head == b->tail; }
};
void func_00130070(Buffer_18F890*);
void func_001F6C20(s32);
s32 func_0020A518(void*, s32, s32);
void func_001300D8(Buffer_18F890*, s32);


void func_001A7E90(GameProgress* ctx);

s32 func_0018C568(MemoryCard* self)
{
    if (self->image == 0) {
        return 0x2C;
    }
    *D_002623C0 = *self->image;
    func_001A7E90(D_002623C0);
    return 0;
}

s32 func_0020B058(void* a, s32 b, s32 c);
void func_0018EDA8(s32 a, s32 b, s32 c, s32 d);
void func_0018EF78(s32 a, s32 b, s32 c);
void func_001F6C20(s32 a);
void func_001F6B40(s32 a);
void func_0018EB98(void* a);

struct Info_18CDD8 { u8 pad0[0x44]; s32 f44; s32 f48; u8 pad4C[0x60 - 0x4C]; };

void func_001F5C0C(void* p, s32 v, s32 n);
void func_001605E8(GameProgress* img);
s32 func_00160650(GameProgress* img);
s32 func_0018C9C0(void* a, void* b, Info_18CDD8* info);
s32 func_0018D268(void* a, void* b, s32 c, s32* h);
s32 func_0018D2E8(void* a, s32 h, GameProgress* buf, s32 size, s32* got);
void func_0018D2B0(void* a, s32 h);

s32 func_0018CDD8(void* a0, void* a1, GameProgress* out, Info_18CDD8* info)
{
    Info_18CDD8 local;
    GameProgress buf;
    s32 handle = -1;
    s32 got;
    s32 r;
    s32 size;
    if (info == 0) info = &local;
    func_001F5C0C(info, 0, 0x5C);
    func_001605E8(out);
    r = func_0018C9C0(a0, a1, info);
    if (r != 0) return r;
    if ((info->f48 & 0xD4) != 4) return 20;
    size = info->f44;
    if (size != 0x1A00) return 28;
    r = func_0018D268(a0, a1, 1, &handle);
    if (r != 0) return r;
    r = func_0018D2E8(a0, handle, &buf, 0x1A00, &got);
    if (r == 0) {
        r = 8;
        if (got == size) {
            if (buf.type != 18 || buf.size != got) r = 28;
            else if (buf.sum != func_00160650(&buf)) r = 27;
            else {
                *out = buf;
                r = 0;
            }
        }
    }
    func_0018D2B0(a0, handle);
    return r;
}

extern u8 D_002D7B40[];
extern u8 D_0045AAC0[];
extern u8 D_0042AAC0[];
extern u8 D_00586AC0[];
extern u8 D_005A2D40[];
extern s32 D_002626CC;
extern u8 D_00148D68[];

void func_0020ADA0(void);

// Data defined from retail's bytes.
extern const char D_0024B340[8] = "/";
extern const char D_0024B360[48] = "/BASCUS-97198YAOTWTD!/BASCUS-97198YAOTWTD!";
extern const char D_0024B390[16] = "Sly Cooper";
extern const u32 D_00248470[8] = { 0x80CFADA9, 0x930F4F53, 0x7F1AF6BE, 0x5EAA1EBC, 0xDDC30E98, 0x80DB63DE, 0x7F1AF5F2, 0x930F1BCB };
extern const Key_18F198 D_00248490 = { 0xEF312076, 0x53B6BFB5, 0x4846D1FF, 0x0EAD57EE, 0x9E3389D7, 0xEF3E4A62, 0x4846D2BB, 0x531DFFB1 };
extern const u32 D_002484B0[128] = {
     0xF5248332, 0x853A4F27, 0x46B9CAE3, 0x13D7C04C, 0x74F101E3, 0xF524CCCD, 0x46B9C9A3, 0x80694F23 ,
     0xCE3D9360, 0x2F5524C3, 0xAD69A291, 0xE6559C19, 0x9871938B, 0xCE3E40C9, 0xAD69A1D0, 0x2A3164C7 ,
     0xFB4E86C1, 0x6C87A1D9, 0x52316802, 0x5104AFFE, 0xBE64E217, 0xFB5EE14F, 0x52316B3E, 0x7992A1DD ,
     0xAA6745EF, 0xE20C5CCD, 0x5C96D810, 0xE02E90DD, 0xD1277036, 0xAA663067, 0x5C96DB2F, 0xEF791CC9 ,
     0xFA1F9E5E, 0x536F409D, 0xF496C49E, 0x8DCA8A5D, 0xB23276D3, 0xFA19E5AF, 0xF496C7DB, 0x50670099 ,
     0xA2774D68, 0x5B77ECC0, 0x919E5521, 0x27816F4B, 0x4E1FE92F, 0xA27AD384, 0x919E5667, 0x59486CC4 ,
     0x93B51720, 0xA36BF0A9, 0x0F49C87D, 0x392C04FD, 0xECDF8673, 0x93B28EFF, 0x0F49CB40, 0xA719B0AD ,
     0x052890A7, 0x6DF00199, 0xF4B16A32, 0x80E128F7, 0x7029184B, 0x052D5A2B, 0xF4B1690C, 0x6FBB819D ,
     0xEBD27ABC, 0x8EDE98E5, 0x385602E3, 0x6EDAD7CC, 0x3E572A20, 0xEBDD75D0, 0x385601A4, 0x8C1658E1 ,
     0xE621B6AA, 0xE129CC90, 0x3B5A84E3, 0x80C4FB2F, 0x26950B04, 0xE622929B, 0x3B5A87AB, 0xE0A90C94 ,
     0x078CF2E7, 0xCFBE2AE9, 0x50D22ECE, 0xF5E53F61, 0x0EF768D9, 0x07826A14, 0x50D22D8C, 0xCC0DEAED ,
     0x6E916B53, 0xD7899E64, 0xB27D8190, 0xACE3EE23, 0x2E5415B6, 0x6E8167C1, 0xB27D82D3, 0xD50C9E60 ,
     0x8E98A2D8, 0x464C9D9A, 0x15CB2951, 0xF0C350EB, 0xB464DC83, 0x8E95F9A5, 0x15CB2A67, 0x478B5D9E ,
     0xB804419D, 0x66FAEFB7, 0x07841B81, 0xF7BE8C47, 0x3AF12C8A, 0xB81795B4, 0x078418BB, 0x63B7EFB3 ,
     0x92E9986B, 0xD7FD98C1, 0x9A3D4AC0, 0x93483E1B, 0x6D268427, 0x92EF8F9B, 0x9A3D49FB, 0xD59D18C5 ,
     0x1B7736BC, 0x08EA9779, 0x9ABAE153, 0x01F1543B, 0x48D846BE, 0x1B72254A, 0x9ABAE26B, 0x0D7F577D 
};
extern const char D_0024B348[24] = "/BASCUS-97198YAOTWTD!";
extern const char D_0024B3A0[16] = "/%s/%s%d";
extern const char D_0024B3B0[24] = "BASCUS-97198YAOTWTD!";
extern const char D_0024B3C8[8] = "save";
extern const Src_18CA10 D_0024B3D0 = { 0x44325350, 0 };
extern const char D_0024B3D8[8] = "sly.ico";
extern const char D_0024B3E0[8] = "%s/%s";
extern const char D_0024B3E8[24] = "icon.sys";

s32 D_002699A8;
ObjectLink D_00269B60[2] = { { 0x20, 0x167, 0x59C }, { 0x20, 0x168, 0x5A0 } };
