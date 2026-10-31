// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_18C1A8 { u8 pad0[0x14]; s32 f14; };

s32 func_0018D1F8(void* self);

s32 func_0018C1A8(Obj_18C1A8* self)
{
    s32 r = func_0018D1F8(self);
    if (r != 0) {
        self->f14 = 2;
    } else {
        self->f14 = 3;
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

struct Ctx_0018D8E0 { u8 pad[0x6B8]; s32 ready; };

void func_0013B4C0(void* self);

void func_0018D8E0(Ctx_0018D8E0* self)
{
    func_0013B4C0(self);
    self->ready = 1;
}

struct Ctx_0018D910 { u8 pad[0x2C8]; u64 flags; };

extern u8 D_002699B0[];

void func_0013B598(void* self);
void func_00124DF8(void* self, s32 mode, void* data);

void func_0018D910(Ctx_0018D910* self)
{
    u64 mask = (u64)(s64)-0x301;
    u64 set = 0x8000;
    func_0013B598(self);
    func_00124DF8(self, 1, D_002699B0);
    mask <<= 16;
    mask |= 0xFFFF;
    mask <<= 16;
    mask |= 0xFFFF;
    set <<= 25;
    self->flags = (self->flags & mask) | set;
}

struct Obj_18E678 { u8 pad0[4]; s32 f04; s32 f08; };

void func_0018E6A0(void* self);

void func_0018E678(Obj_18E678* self, s32 a1, s32 a2)
{
    self->f04 = a2;
    self->f08 = a1;
    func_0018E6A0(self);
}

struct Ctx_18E7C0 {
    u8 pad0[4];
    s32 f4;
    u8 pad1[4];
    s32 fC;
};

struct Span_18E7C0 {
    s32 a;
    s32 b;
    void* c;
    s32 d;
};

void func_001F6C20(s32 a);
void* func_001F6CA0(Span_18E7C0* span, s32 n);
s32 func_001F6C90(void* obj);

void* func_0018E7C0(Ctx_18E7C0* p, void* a1, s32 a2)
{
    Span_18E7C0 span;
    void* obj;

    span.a = a2;
    span.b = p->f4 + p->fC;
    span.c = a1;
    span.d = 0;
    func_001F6C20(0);
    obj = func_001F6CA0(&span, 1);
    while (func_001F6C90(obj) >= 0) {
    }
    return a1;
}

void* func_0018E8C0(void)
{
    return 0;
}

int func_0018E938(void)
{
    return 1;
}

s32 func_0018F940(s32 a, s32 b);

s32 func_0018F968(void)
{
    return func_0018F940(1, 0xFFFF);
}

struct Actor_0018F988 {
    u8 pad_000[0x538];
    u64 flags_538;
};

void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_0018F988(Actor_0018F988* self)
{
    func_001B7968(self);
    self->flags_538 |= (u64)0x8000 << 28;
    func_001B9AE0(self, 3, 0, 3, 0);
}

struct Actor_0018FEF8 {
    u8 pad_000[0xBD0];
    s32 field_BD0;
    s32 field_BD4;
};

void func_001C6F48(void* self);

void func_0018FEF8(Actor_0018FEF8* self)
{
    func_001C6F48(self);
    self->field_BD4 = 0;
    self->field_BD0 = 0;
}

struct Obj_18FF28 {
    u8 pad0[0x5F0];
    s32 f5F0;
    u8 pad1[0xC38 - 0x5F4];
    s32 fC38;
    s32 fC3C;
    s32 fC40;
    s32 fC44;
};

extern u8 D_00269B60[];

void func_001C72A0(void* self);
void func_00124DF8(void* self, s32 n, void* table);
s32 func_001CA758(void* self, s32 id);

void func_0018FF28(Obj_18FF28* self)
{
    func_001C72A0(self);
    func_00124DF8(self, 2, D_00269B60);
    self->f5F0 = func_001CA758(self, 0xEF);
    self->fC38 = func_001CA758(self, 0x16C);
    self->fC3C = func_001CA758(self, 0x16D);
    self->fC40 = func_001CA758(self, 0x16A);
    self->fC44 = func_001CA758(self, 0x16B);
}

struct Actor_0018FFB0 {
    u8 pad_000[0x4];
    s32 field_004;
    u8 pad_008[0x720 - 0x008];
    void* field_720_ptr;
    s32 field_724;
    u8 pad_728[0xC04 - 0x728];
    s32 field_C04;
    u8 pad_C08[0xC10 - 0xC08];
    s32 field_C10;
    u8 pad_C14[0xC28 - 0xC14];
    s32 field_C28;
    s32 field_C2C;
    s32 field_C30;
    s32 field_C34;
    s32 field_C38;
    s32 field_C3C;
    s32 field_C40;
    s32 field_C44;
};

void func_001CB6F8(void* a, void* b);
void func_001C91C8(void* self, s32 a, s32 b);

void func_0018FFB0(Actor_0018FFB0* self, s32 a1, s32 a2)
{
    s32 a2v = a2;
    switch (self->field_724) {
    case 4:
        self->field_C28 = 0;
        self->field_C10 = 0;
        break;
    case 0x10:
        if (self->field_C30 == 4) {
            a2v = self->field_C44;
        } else {
            a2v = self->field_C3C;
        }
        break;
    case 0xB:
        if (self->field_C30 == 4) {
            a2v = self->field_C40;
        } else {
            a2v = self->field_C38;
        }
        if (self->field_720_ptr != 0) {
            func_001CB6F8(self->field_720_ptr, self);
        }
        break;
    }
    func_001C91C8(self, a1, a2v);
    s32 kind = self->field_724;
    if (kind == 0xB || kind == 0x10) {
        self->field_C04 = 0;
    }
}

void func_001F5C0C(void* p, s32 v, s32 n);

void func_0018D410(void* p)
{
    func_001F5C0C(p, 0, 8);
}

struct Obj_0018DC88 {
    u8 pad0[0x6BC];
    s32 count6BC;
    void* items6C0[4];
    s32 count6D0;
    void* items6D4[4];
    void* f6E4;
};

s32 func_001833F0(void* key, void* item);
s32 func_001300E8(void* key, void* item);
s32 func_001B8A08(void* self, void* key);

s32 func_0018DC88(Obj_0018DC88* self, void* key)
{
    if (key == self->f6E4) {
        return 1;
    }
    for (s32 i = 0; i < self->count6BC; i++) {
        if (func_001833F0(key, self->items6C0[i]) != 0) {
            return 1;
        }
    }
    for (s32 j = 0; j < self->count6D0; j++) {
        if (func_001300E8(key, self->items6D4[j]) != 0) {
            return 1;
        }
    }
    return func_001B8A08(self, key);
}

struct List_0018DD50 { u8 pad0[0x6BC]; u32 count; void* items[4]; };

void func_0018DD50(List_0018DD50* list, void* item)
{
    u32 n = list->count;
    if (n < 4) {
        list->items[n] = item;
        list->count = n + 1;
    }
}

s32 func_0018EDA0(void)
{
    return 1;
}

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

struct Queue_18DD78 { u8 pad0[0x6D0]; s32 count; s32 items[4]; };

void func_0018DD78(Queue_18DD78* self, s32 value)
{
    s32 n = self->count;
    if ((u32)n < 4) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct Obj_18EA48 { s32 flag; u8 pad0[0x2C - 4]; };

void func_0011E460(void);
void func_0013C9B0(void* state);
void func_0018E6A0(void* self);

void func_0018EA48(Obj_18EA48* self)
{
    if (self->flag != 0) {
        func_0011E460();
        self->flag = 1;
        func_0013C9B0((u8*)self + 0x2C);
        func_0013C9B0((u8*)self + 0x4C);
        func_0018E6A0((u8*)self + 0x6C);
    }
}

struct Obj_18F148 { u8 pad0[4]; s32 f04; s32 f08; };

void func_0018F198(void* self, s32 value);

void func_0018F148(Obj_18F148* self)
{
    s32 pending = self->f08;
    s32 first = self->f04;
    self->f04 = 0;
    self->f08 = 0;
    func_0018F198(self, first);
    if (pending != 0) {
        func_0018F198(self, pending);
    }
}

s32 func_0018D748() { return 0; }

void func_0018D750() {}

struct Elem_18C028 { u8 pad0[0xC]; f32 fC; u8 pad1[0x1A4C]; };
struct Self_18C028 { u8 pad0[0xC]; s32 f0C; f32 f10; u8 pad1[0x4F34]; Elem_18C028* f4F48; };
struct Cfg_18C028 { u8 pad0[0x10]; f32 f10; };

extern u8 D_00269990[];
extern Cfg_18C028 D_00261858[];

s32 func_0018BFA8(void* lhs, void* rhs);
void func_001605E8(void* self);
void func_0018B670(void* a, void* fn, void* self);
void func_0018C420(void* self);
void func_0018D0A0(void* self);

void func_0018C028(Self_18C028* self, s32 value)
{
    s32 old = self->f0C;
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
    func_0018B670(D_00269990, (void*)func_0018D0A0, self);
    goto store;
c420:
    func_0018B670(D_00269990, (void*)func_0018C420, self);
    goto store;
loop: {
    Elem_18C028* e;
    Elem_18C028* p = (Elem_18C028*)((u8*)self + 0x1A30);
    e = self->f4F48 = (Elem_18C028*)((u8*)self + 0x30);
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
    self->f0C = value;
    self->f10 = D_00261858->f10;
}

struct Obj_18C178 { u8 pad0[0x18]; s32 f18; f32 f1C; u8 pad1[0x4F24]; s32 f4F44; };
extern f32 D_00261868[];

void func_0018C178(Obj_18C178* self, s32 value)
{
    if (value != self->f18) {
        if (value == 2) self->f4F44 = 0;
        self->f18 = value;
        self->f1C = D_00261868[0];
    }
}

typedef void (*VFn_18C7F8)(void* self);
struct Self_18C7F8 { u8 pad0[0x4F44]; s32 f4F44; };
struct Glob_18C7F8 { u8 pad0[0x19EC]; s32 f19EC; };
struct Gx_18C7F8 { u8 pad0[0x27C]; s32 f27C; };
struct __attribute__((packed)) Pk_18C7F8 { s32 v; };
struct Obj_18C7F8 { VFn_18C7F8* vtbl; };

extern Glob_18C7F8* D_002623C0;
extern u8 D_00269990[];
extern Gx_18C7F8 D_0026FF68[];
extern Obj_18C7F8 D_00273EB0[];

void func_00194D30(void* self, s32 a, s32 b);
void func_0018B670(void* a, void* fn, void* self);
void func_0018C638(void* self);

void func_0018C7F8(Self_18C7F8* self)
{
    if (self->f4F44 != 0) {
        if ((D_002623C0->f19EC & 0x100) == 0) {
            D_0026FF68->f27C = -1;
            func_00194D30(D_0026FF68, 1, 0x14);
        } else {
            func_0018B670(D_00269990, (void*)func_0018C638, self);
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
void func_001E2138(void* dst, void* src);
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

void func_0018D978(void* self)
{
    func_001B7B78(self);
    void* p = *(void**)((u8*)self + 0x6B4);
    if (p != 0) {
        func_0012E760(p);
        *(void**)((u8*)self + 0x6B4) = 0;
    }
}

extern u8* D_00275710;
extern u8 D_002CBB40[];

void func_0011D6A8(u32 a0);
void func_0011D6D8(s32 a0);
void func_0011E010(void);
s32 func_0011CE30(void);
void func_0011E110(s32 a0);
s32 func_0011E1F8(s32 flag);
s32 func_0011D4B8(s32 arg);
void func_0011D480(s32 a0, s32 a1);
s32 func_0011E428(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001C08B0(void* p, s32 a, s32 b);
void func_0013C988(void* state, s32 initialValue, void* secondaryValue);
s32 func_0018E678(void* self, s32 a1, s32 a2);

struct Obj_18E940 {
    s32 f00;
    s32 f04;
    u8 pad08[0x24];
    u8 sub2C[0x20];
    u8 sub4C[0x20];
    u8 sub6C[0x20];
    s32 f8C;
    s32 f90;
};

s32 func_0018E940(struct Obj_18E940* self)
{
    s32 r;
    func_0011D6A8(0xFFFFFFFF);
    func_001C08B0(D_00275710, 0, 0);
    func_0011E010();
    while (func_0011CE30() != 0) {
    }
    func_0011E110(1);
    func_0011E1F8(0);
    self->f8C = func_0011D4B8(2);
    self->f90 = func_0011D4B8(8);
    func_0011D480(2, 0x400);
    func_0011D480(8, 0x200);
    r = func_0011E428(0x6000, 0x400, 0, 2, 2);
    if (r >= 0) {
        self->f00 = 1;
        func_0013C988(self->sub2C, 0x28, &self->f04);
        func_0013C988(self->sub4C, 0xC000, D_002CBB40);
        return func_0018E678(self->sub6C, 0x6000, r);
    }
    self->f00 = 0;
    return 1;
}

extern u8* D_00275710;

void func_0011E498(void);
void func_0011D480(s32 a0, s32 a1);
void func_001C0950(void* p);
void func_0011D6D8(u32 a0);

struct Obj_18EAA0 {
    s32 f00;
    u8 pad04[0x88];
    s32 f8C;
    s32 f90;
};

void func_0018EAA0(struct Obj_18EAA0* self)
{
    self->f00 = 0;
    func_0011E498();
    func_0011D480(2, self->f8C);
    func_0011D480(8, self->f90);
    func_001C0950(D_00275710);
    func_0011D6D8(0xFFFFFFFF);
}

void func_0013CC00(void* a, u32 b, void* c);

s32 func_0018EC40(void* a0, void* a1, void* a2)
{
    if (*(u32*)((u8*)a2 + 0x70) >= *(u32*)((u8*)a1 + 0xC)) {
        func_0013CC00((u8*)a2 + 0x60, *(u32*)((u8*)a1 + 0xC), *(void**)((u8*)a1 + 0x8));
        return 1;
    }
    return 0;
}

void* func_0018D5C0(u32 n);

void* func_0018D758(u32 n)
{
    return func_0018D5C0(n);
}

struct Args_18EC80 { u8 pad0[8]; s32 f8; s32 fC; };

void func_0018EAF8(void* self, s32 a, s32 b);

void func_0018EC80(void* a0, Args_18EC80* a1, void* a2)
{
    func_0018EAF8((u8*)a2 + 0x80, a1->fC, a1->f8);
}

void func_0018F890(void* self, s32 flag);

s32 func_0018ED78(void* a0, s32 a1, void* a2)
{
    func_0018F890(a2, 0);
    return 1;
}

struct Blk_18EB98 { u8 b[0x24]; };

struct Self_18EB98 {
    s32 state;
    u8 pad4[0x4C - 4];
    Blk_18EB98 f4C;
    s32 f70;
    s32 f74;
    u8 pad78[8];
    s32 f80;
};

s32 func_0013CAD8(Blk_18EB98* a, s32 b, void* c);
void func_0011E4C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_0018E838(void* p);

void func_0018EB98(Self_18EB98* self)
{
    switch (self->state) {
    case 2:
        func_0013CAD8(&self->f4C, self->f80, (u8*)&self->f4C + 0x20);
        if (self->f80 != 0) {
            break;
        }
        func_0011E4C0(self->f70, self->f74, self->f70, 0, 0);
        self->state = 3;
        break;
    case 3: {
        void* s0 = (u8*)&self->f4C + 0x20;
        func_0018E838(s0);
        func_0013CAD8(&self->f4C, self->f80, s0);
        break;
    }
    }
}

// was NEAR: the shift arm: retail branches with bnez on (v < 16) to the sllv, with li v0,1 in the delay slot; ours uses beqz and the arms swap

s32 func_0018E410(void* p);

void func_0018F0E8(void* self, void* p)
{
    s32 m;
    s32 v;

    if (*(void**)((u8*)self + 4) != 0) {
        return;
    }
    *(void**)((u8*)self + 4) = p;
    v = func_0018E410(p);
    if ((u32)v >= 16) {
        m = 0;
    } else {
        m = 1 << v;
    }
    *(u32*)((u8*)D_002623C0 + 0x19F4) |= m;
}

struct Stream_18EAF8 {
    s32 mode;
    u8 pad0[0x2C - 4];
    u8 sub2C[0x10];
    s32 v3C;
    u8 pad1[0x4C - 0x40];
    u8 sub4C[0x10];
    s32 v5C;
};

s32 func_0013CC00(void* sub, s32 a, s32 b);

s32 func_0018EAF8(Stream_18EAF8* self, s32 left, s32 right)
{
    s32 n;

    if (self->mode == 0) {
        goto zero;
    }
    left -= 4;
    right += 4;
    if (self->mode == 1) {
        n = func_0013CC00(self->sub2C, left, right);
        left -= n;
        right += n;
        if (self->v3C > 0) {
            goto one;
        }
        self->mode = 2;
    }
    if (self->v5C >= left) {
        goto call;
    }
zero:
    return 0;
call:
    func_0013CC00(self->sub4C, left, right);
one:
    return 1;
}

struct Cursor_18E6A0 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};

void func_0018E6A0(Cursor_18E6A0* c)
{
    c->f14 = c->f8;
    c->f18 = 0;
    c->f10 = 0;
    c->fC = 0;
    c->f1C = 0;
}

struct Local_18EF78 { u8 bytes[0x30]; };

void func_001611B8(Local_18EF78* b);
void func_001529C8(Local_18EF78* b, s32 a1, void* self);
void func_00152B38(Local_18EF78* b);
void func_001613C0(Local_18EF78* b, s32 a1, s32 a2, u64 a3);
void func_00161708(Local_18EF78* b, s32 a1, u64 a2);
void func_001614C8(Local_18EF78* b, s32 a1, s32 a2);
void func_001615F0(Local_18EF78* b, s32 a1, s32 a2, s32 a3, s32 a4);
void func_00161200(Local_18EF78* b);
void func_00152D30(Local_18EF78* b);
void func_001529E0(Local_18EF78* b, s32 a1, s32 a2);

void func_0018EF78(void* self, s32 a1, s32 a2)
{
    Local_18EF78 buf;
    func_001611B8(&buf);
    func_001529C8(&buf, 0x12, self);
    func_00152B38(&buf);
    func_001613C0(&buf, 6, 1, 0xE);
    func_00161708(&buf, 6, 0x0AA8029E00ULL);
    func_00161708(&buf, 0x14, 0x61);
    func_00161708(&buf, 8, 5);
    func_00161708(&buf, 0x42, 0x44);
    func_00161708(&buf, 0x47, 0x31001);
    func_001613C0(&buf, 0x116, 5, 0xE4343);
    func_001614C8(&buf, 8, 8);
    func_001615F0(&buf, 0x6C00, 0x7900, 0, 0);
    func_001614C8(&buf, (a1 << 4) | 8, (a2 << 4) | 8);
    func_001615F0(&buf, 0x9400, 0x8700, 0, 0);
    func_00161708(&buf, 0x61, 0);
    func_00161200(&buf);
    func_00152D30(&buf);
    func_001529E0(&buf, 0, 0);
}

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

struct Frame_18DB20 {
    Quad_18DB20 q00;
    Quad_18DB20 q10;
    Quad_18DB20 q20;
    Tbl3_18DB20 tbl30;
    Quad_18DB20 q60;
    u8 pad70[0xA0 - 0x70];
    Blk4_18DB20 blkA0;
    u8 padE0[0xF0 - 0xE0];
    Blk4_18DB20 blkF0;
};

typedef void (*VFn_18DB20)(void* self, f32 f, void* a, void* b);
struct Obj_18DB20 { VFn_18DB20* vtbl; };

struct Self_18DB20 {
    u8 pad0[0x1EC];
    Obj_18DB20* p1EC;
    Obj_18DB20* p1F0;
    u8 pad1[0x2C8 - 0x1F4];
    u64 flags2C8;
};

extern u8 D_00248D30[];
extern u8 D_002483D0[];

void func_00125B70(void* obj, void* c, void* out);
void func_00188B08(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);
void func_00125C90(void* obj, void* s, void* out);

void func_0018DB20(Self_18DB20* self, void* in1, void* in2)
{
    Frame_18DB20 f;

    if ((self->flags2C8 & 0x100000000ULL) == 0) {
        if (self->p1EC == 0 && self->p1F0 == 0) {
            func_00125C90(self, in1, in2);
        } else {
            if (self->p1EC != 0) {
                self->p1EC->vtbl[4](self->p1EC, 0.0f, &f, &f.q10);
            } else {
                f.q00 = *(Quad_18DB20*)D_00248D30;
            }
            if (self->p1F0 != 0) {
                self->p1F0->vtbl[5](self->p1F0, 0.0f, &f.tbl30, &f.q20);
            } else {
                f.tbl30 = *(Tbl3_18DB20*)D_002483D0;
            }
            func_00125B70(self, in2, &f.blkA0);
            func_00188B08(&f, &f.tbl30, &f.q60);
            func_00188668(&f.blkF0, &f.blkA0, &f.q60);
            f.blkA0 = f.blkF0;
            func_00125C90(self, in1, &f.blkA0);
        }
    }
}

struct Card_18C250 { u8 pad0[4]; void* f4; void* f8; u8 pad1[8]; s32 f14; u8 pad2[0x10]; s32 f28; };

extern u8 D_00248470[];
extern void* func_0020A078(void*, void*, const char*);
extern s32 func_0018BD00(void*, s32, void*);
extern s32 func_0018C1E8(void*);
extern s32 func_0018D228(void*, const char*);
extern s32 func_0018D368(void*, const char*, const char*, s32);
extern s32 func_0018CA10(void*, const char*, const char*);
extern s32 func_0018CBF8(void*, const char*);
extern s32 func_001E1FD0(char*, const char*, ...);
extern s32 func_0018D028(void*, void*, void*, void*);

s32 func_0018C250(Card_18C250* self)
{
    char name[0x50];
    s32 info[4];
    s32 r = func_0018BD00(func_0020A078(self->f4, self->f8, "/"), 0x12, info);
    if (r != 0) return r;
    s32 need = info[0] == 0 ? 2 : 1;
    s32 sz = func_0018C1E8(D_00248470);
    need += 5;
    need += (sz + 1023) / 1024;
    need += 0x15;
    if (self->f28 < need) return 1;
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
                    if (self->f14 < 5) self->f14 = 5;
                }
            }
        }
    }
    return r;
}

extern u8 D_00269A00[];
extern s32 D_00261F1C;

void func_001F6B60(s32 a);
void func_001686E8(s32 a, s32 b);
void func_001684E8(void);
void func_001683E8(void);

struct Task_18E558 {
    u8 pad0[0x114];
    s32 f114;
    s32 f118;
    u8 pad1[0x14];
    s32 f130;
    volatile s32 f134;
};

void func_0018E558(void)
{
    Task_18E558* t = (Task_18E558*)D_00269A00;

    for (;;) {
        t->f134 = 0;
        func_001F6B60(t->f130);
        t->f134 = 1;
        func_001686E8(D_00261F1C, t->f114);
        t->f134 = 2;
        func_001684E8();
        func_001686E8(D_00261F1C, t->f118);
        func_001683E8();
        func_001686E8(D_00261F1C, t->f118);
        func_001683E8();
    }
}

struct Obj_18F610 {
    u8 pad0[0x138];
    u32 crc;
    u8* cur;
    s32 remain;
};

extern u8 D_005A2E60[];
extern u8 D_00269B48[];

void func_0018F610(Obj_18F610* self)
{
    if (self->remain > 0) {
        s32 n = self->remain - 4;
        u32* tab = (u32*)D_005A2E60;
        u8* p = self->cur;
        u8* nxt = p + 4;
        u32 c0 = self->crc;
        u32 c1, c2, c3;

        c1 = tab[(c0 ^ p[0]) & 0xff] ^ (c0 >> 8);
        self->crc = c1;
        c2 = tab[(c1 ^ p[1]) & 0xff] ^ (c1 >> 8);
        self->crc = c2;
        self->remain = n;
        c3 = tab[(c2 ^ p[2]) & 0xff] ^ (c2 >> 8);
        self->crc = c3;
        u32 t = tab[(c3 ^ p[3]) & 0xff];
        self->cur = nxt;
        u32 c = t ^ (c3 >> 8);
        self->crc = c;
        if (n == 0 && c != 0) {
            *(s32*)D_00269B48 = 1;
        }
    }
}

struct Obj_18F7D0 {
    s32 f00;
    u8 pad04[0x08];
    s32 f0C;
    u8 pad10[0x124];
    s32 f134;
};

extern s32 D_002626CC;

void func_0018EA48(Obj_18F7D0* self);
void func_0018EAA0(Obj_18F7D0* self);
void func_0020B0C0(Obj_18F7D0* self);
s32 func_0020B048(Obj_18F7D0* self);
void func_001B3450(void);

void func_0018F7D0(Obj_18F7D0* self)
{
    u8* base = (u8*)self;
    s32 mask;

    self->f0C = 0;
    func_0018EA48((Obj_18F7D0*)(base + 0x80));
    func_0018EAA0((Obj_18F7D0*)(base + 0x80));
    func_0020B0C0((Obj_18F7D0*)(base + 0x10));
    (void)func_0020B048((Obj_18F7D0*)(base + 0x10));
    if (self->f134 != 0) {
        do {
        } while (*(volatile s32*)&self->f134 != 0);
    }
    D_002626CC = 3;
    func_001B3450();
    if ((u32)self->f00 >= 16) {
        mask = 0;
    } else {
        mask = 1 << self->f00;
    }
    *(s32*)((u8*)D_002623C0 + 0x19F8) |= mask;
}

extern u8 D_0024B3A0[];
extern u8 D_0024B3B0[];
extern u8 D_0024B3C8[];

struct Buf_18C770 { u8 bytes[0x50]; };
struct Obj_18C770 { u8 pad0[0x4F4C]; s32 f4F4C; };

s32 func_001E1FD0(Buf_18C770* dst, const char* fmt, ...);
s32 func_0018D028(Obj_18C770* self, Buf_18C770* buf, void* a2, void* a3);

s32 func_0018C770(Obj_18C770* self)
{
    Buf_18C770 buf;
    s32 f = self->f4F4C;
    s32 n;
    s32 g;

    if (f == 0) {
        return 0x2C;
    }
    n = f - 0x30;
    n = n - (s32)self;
    n = n * 0x26FFD927;
    n = (n >> 2) + 1;
    func_001E1FD0(&buf, (const char*)D_0024B3A0, D_0024B3B0, D_0024B3C8, n);
    g = self->f4F4C;
    return func_0018D028(self, &buf, (void*)g, (void*)(g + 0x1A00));
}

struct Obj_18CBF8;

void func_0018CC20(Obj_18CBF8* self, void* b, void* c, void* d);

extern u8 D_00248470[];
extern u8 D_0024B3D8[];

void func_0018CBF8(Obj_18CBF8* self, void* b)
{
    func_0018CC20(self, b, D_00248470, D_0024B3D8);
}

struct __attribute__((aligned(16))) Quad_18DDA0 { s32 a, b, c, d; };
struct Ctx_18DDA0 { u8 pad[0]; };

extern u8 D_00248D30[];
void func_0018D8E0(Ctx_18DDA0* self);

void func_0018DDA0(Ctx_18DDA0* self)
{
    func_0018D8E0(self);
    *(Quad_18DDA0*)((u8*)self + 0x350) = *(Quad_18DDA0*)D_00248D30;
}

struct Ent_18E410 {
    u8 pad0[8];
    s32 k0;
    u8 pad1[0xC];
    s32 k1;
    u8 pad2[4];
};

extern u8 D_002484B0[];

s32 func_0018E410(Ent_18E410* key)
{
    Ent_18E410* p = (Ent_18E410*)D_002484B0;
    s32 i = 0;
    s32 m;

    do {
        if (p == key) {
            m = 1;
        } else if (p == 0 || key == 0) {
            m = 0;
        } else {
            m = ((p->k0 ^ p->k1) ^ (key->k0 ^ key->k1)) == 0;
        }
        if (!m) {
            i++;
            p++;
        } else {
            return i;
        }
    } while (i < 16);
    return -1;
}

extern u8 D_002699C0[];
extern u8 D_0024B580[];
extern u8 D_0024B588[];

u8* func_0018E480(s32 index)
{
    if ((u32)index < 16) {
        return ((u8**)D_002699C0)[index];
    }
    if (index == -1) {
        return D_0024B580;
    }
    return D_0024B588;
}

struct Ctl_18E4C0 { u8 pad[0]; };

extern u8 D_00269A00[];
extern u8 D_002484B0[];
void func_0018F0E8(Ctl_18E4C0* self, void* p);

void func_0018E4C0(s32 idx)
{
    func_0018F0E8((Ctl_18E4C0*)D_00269A00, D_002484B0 + (idx << 5));
}

struct Ctx_18E4F0 { u8 pad0[4]; };
struct Dev_18E4F0 { u8 pad0[0x19F4]; s32 w19F4; };

extern u8 D_002484B0[];
extern u8 D_00269A08[];

void func_0018E4C0(Ctx_18E4F0* self, u32 n);

void func_0018E4F0(Ctx_18E4F0* self, u32 n)
{
    Dev_18E4F0* dev;
    s32 m;

    func_0018E4C0(self, n);
    *(void**)D_00269A08 = (void*)(D_002484B0 + (n << 5));
    if (n >= 16) { m = 0; } else { m = 1 << n; }
    dev = (Dev_18E4F0*)D_002623C0;
    dev->w19F4 |= m;
}

struct Obj_18ECA8 { u8 pad0[0x60]; u8 sub[0x14]; s32 f74; };
struct Sub_18ECA8 { u8 b[0x14]; };
struct Buf_18ECA8 { void* f0; u8 rest[0x3C]; };

extern u8 D_0024B598[];

s32 func_0018F890(Obj_18ECA8* self, s32 flag);
void func_001F5C0C(void* dst, s32 value, s32 size);
void func_0013CC00(Sub_18ECA8* a, u32 b, void* c);
void func_0013CC48(Sub_18ECA8* p, s32 n);
s32 func_0013CAD8(Sub_18ECA8* a, s32 b, void* c);

s32 func_0018ECA8(void* u0, void* u1, Obj_18ECA8* self)
{
    Buf_18ECA8 buf;
    s32 total = 0x40;
    while (self->f74 < 0x1000) {
        if (func_0018F890(self, 1) == 0) {
            func_001F5C0C(&buf, 0, 0x40);
            s32 k = self->f74;
            func_0013CC00((Sub_18ECA8*)&self->sub, total - (k % 32), &buf);
            break;
        }
    }
    buf.f0 = (void*)D_0024B598;
    func_0013CC48((Sub_18ECA8*)&self->sub, 0);
    func_0013CAD8((Sub_18ECA8*)&self->sub, 0, &buf);
    return 1;
}

extern u8 D_0024B5B8[];
extern void* D_00269AEC;

void func_0018F940(void* self, s32 key)
{
    if (key == 0xFFFF) {
        if (self != 0) {
            D_00269AEC = D_0024B5B8;
        }
    }
}

struct Obj_18D0A0 {
    s32 pad0;
    void* p4;
    void* p8;
    u8 padC[0x8];
    s32 f14;
    u8 pad18[0x8];
    f32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
};

s32 func_00209CB8(void* a, void* b, s32* c, s32* d, s32* e);
s32 func_0018BD00(s32 v, s32 code, s32 extra);

s32 func_0018D0A0(Obj_18D0A0* o)
{
    s32 r = func_0018BD00(func_00209CB8(o->p4, o->p8, &o->f24, &o->f28, &o->f2C), 1, 0);
    switch (r) {
    case 9:
    case 11:
        o->f14 = 1;
        r = 11;
        break;
    case 10:
    case 12:
        o->f14 = 2;
        r = 12;
        break;
    case 0:
        if (o->f2C != 0) {
            if (o->f14 < 3)
                o->f14 = 3;
            else
                break;
        } else
            o->f14 = 2;
        break;
    }
    o->f20 = D_00261868[0] + 0.3f;
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
struct Obj_18C638 { u8 pad0[0x4F44]; u8* p4F44; };
struct Ctx_18C638;


extern u8 D_0024B3A0[];
extern u8 D_0024B3B0[];
extern u8 D_0024B3C8[];

void func_001A7E90(Ctx_18C638* ctx);
s32 func_001E1FD0(Buf_18C638* dst, const char* fmt, ...);
s32 func_0018CFC0(Obj_18C638* owner, Buf_18C638* name, u8* state);

s32 func_0018C638(Obj_18C638* self)
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
    func_001E1FD0(&buf, (const char*)D_0024B3A0, D_0024B3B0, D_0024B3C8, n);
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

extern Src_18CA10 D_0024B3D0;
extern u8 D_0024B3E0[];
extern u8 D_0024B3E8[];

s32 func_001F5C0C(Cfg_18CA10* dst, s32 value, s32 size);
void func_001B5C40(Obj_18CA10* p, void* q);
s32 func_001E1FD0(Buf_18CA10* dst, const char* fmt, ...);
s32 func_0018D368(Owner_18CA10* a, Buf_18CA10* b, Cfg_18CA10* c, s32 d);

s32 func_0018CA10(Owner_18CA10* owner, void* a1, Obj_18CA10* a2)
{
    Cfg_18CA10 c;
    Buf_18CA10 buf;
    (void)func_001F5C0C(&c, 0, 0x3C4);
    c.f000 = D_0024B3D0.w0;
    c.f004 = D_0024B3D0.b4;
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
    func_001E1FD0(&buf, (const char*)D_0024B3E0, a1, D_0024B3E8);
    return func_0018D368(owner, &buf, &c, 0x3C4);
}

struct Self_18CC20 { u8 pad[16]; };
struct Obj_18CC20 { u8 b[0x60]; };
struct Key_18CC20 { s32 w0; s32 w4; u8 pad8[0xC]; s32 w14; u8 pad18[4]; s32 w1C; };
struct Pair_18CC20;
void func_0018D410(Pair_18CC20* p);
struct Pair_18CC20 {
    s32 first;
    s32 second;
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

extern u8 D_0024B3E0[];
void func_0018D608(void);
u8* func_0018D658(s32 size);
s32 func_00137290(Obj_18CC20* o, s32 a, u8* b, s32 c);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
s32 func_0018D268(Self_18CC20* s, char* a, s32 b, s32* c);
void func_0018D410(Pair_18CC20* p);
s32 func_001373B0(Obj_18CC20* o, Pair_18CC20* p);
void func_00137A60(Obj_18CC20* o, s32 n, u8* d);
s32 func_0018D328(Self_18CC20* s, s32 a, u8* d, s32 n, s32* out);
void func_001373D0(Obj_18CC20* o);
s32 func_0018D2B0(Self_18CC20* s, s32 a);
void func_0018D6F0(void);
void func_001372E0(Obj_18CC20* o, s32 f);


s32 func_0018CC20(Self_18CC20* self, s32 a1, Key_18CC20* key, s32 a3)
{
    char text[0x50];
    Obj_18CC20 obj;
    Pair_18CC20 pair;
    u8 data[0x1000];
    s32 code;
    s32 got;
    s32 status;

    func_0018D608();
    code = -1;
    (void)func_00137290(&obj, 0x8040, func_0018D658(0x8040), 0);
    func_001E1FD0(text, (const char*)D_0024B3E0, a1, a3);
    status = func_0018D268(self, text, 0x202, &code);
    if (status == 0) {
        if (!pair.Set(key) || !func_001373B0(&obj, &pair)) {
            status = 0x27;
        } else {
            s32 left = *(s32*)(obj.b + 0x10);
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
struct Dev_18F198 {
    u8 pad[0xAA];
    u16 bits;
};
struct Tbl_18F198 {
    u8 pad[0x19F8];
    u32 mask;
};
struct Loc_18F198 {
    u8 body[0x30];
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
struct Self_18F198 {
    u32 mode;
    u8 pad[0xC];
    u8 list[1];
};

extern Key_18F198 D_00248490;
extern u8 D_002C3B00[];
extern Dev_18F198 D_00262C70;
extern u8 D_00275F80[];
extern s32 D_00269B4C;
extern s32 D_002613EC;

void func_00191E70(s32 v);
s32 func_0018E410(Key_18F198* k);
void func_0012FCF0(Loc_18F198* o, u8* d);
void func_0018D410(Pair_18F198* k);
s32 func_0012FD78(Loc_18F198* o, Pair_18F198* k);
void func_0018F448(Self_18F198* s, Loc_18F198* o);
void func_0016EC20(Dev_18F198* d, s32 n);
void func_00143030(u8* t);
void func_0016E238(Dev_18F198* d);
s32 func_001F00F0(u8* a, Dev_18F198* b, s32 c);
void func_001409E0();
void func_0018F6E8(Self_18F198* s);
s32 func_0020B0B0(u8* l);
void func_0018F7D0(Self_18F198* s);
void func_0012FDE8(Loc_18F198* o);
void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00191EB0(s32 v);
void func_0012FD30(Loc_18F198* o, s32 f);



void func_0018F198(Self_18F198* self, Key_18F198* key)
{
    Loc_18F198 loc;
    Pair_18F198 pr;
    func_00191E70(4);
    self->mode = func_0018E410(key);
    func_0012FCF0(&loc, D_002C3B00);
    if (pr.Set(key) && func_0012FD78(&loc, &pr)) {
        func_0018F448(self, &loc);
        while (!func_0020B0B0(self->list)) {
            func_00143030(((u8*)D_00261858));
            func_0016E238(&D_00262C70);
            s32 flag = 0;
            if (key->Same(&D_00248490)) flag = D_00269B4C != 0;
            u32 m;
            if (self->mode >= 16) m = 0;
            else m = 1u << self->mode;
            if ((*(Tbl_18F198**)&D_002623C0)->mask & m) flag = 1;
            if (flag) {
                if (func_001F00F0(D_00275F80, &D_00262C70, 2)) break;
                if (D_00262C70.bits & 0x91F) {
                    func_0016EC20(&D_00262C70, 0x91F);
                    break;
                }
            }
            func_001409E0();
            if (D_002613EC != 3) break;
            func_0018F6E8(self);
        }
        if (key->Same(&D_00248490)) D_00269B4C = 1;
        func_0018F7D0(self);
        func_0012FDE8(&loc);
    } else {
        func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    func_00191EB0(4);
    func_0012FD30(&loc, 2);
}
