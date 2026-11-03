// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

s32 func_0020B048(void) {
	return 1;
}

struct Device_20B0B0 {
	u8 padding[0x40];
	void* state;
};

s32 func_0020B0B0(Device_20B0B0* device) {
	return *(s32*)device->state;
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

s32 func_0020B110(Device_20B110* device) {
	DeviceState_20B110* state = (DeviceState_20B110*)device->state;
	if (state->a) *(s32*)((char*)state->a + 0x28) = 0;
	if (state->b) *(s32*)((char*)state->b + 0x28) = 0;
	if (state->c) *(s32*)((char*)state->c + 0x28) = 0;
	if (state->d) *(s32*)((char*)state->d + 0x28) = 0;
	if (state->e) *(s32*)((char*)state->e + 0x28) = 0;
	if (state->f) *(s32*)((char*)state->f + 0x28) = 0;
	return 1;
}

struct Field_20B258 {
	u8 padding[8];
	s32 f8;
	s32 fc;
};

s32 func_0020B258(Field_20B258* field) {
	return field->fc = field->f8;
}

extern u32* D_0062AD68;
extern u32* D_0062AD6C;
extern u32* D_0062AD70;
void func_00209C60(u32 base) {
    volatile u32* regs = (volatile u32*)(base | 0x20000000);
    if (D_0062AD68) *D_0062AD68 = regs[0];
    if (D_0062AD6C) *D_0062AD6C = regs[1];
    if (D_0062AD70) *D_0062AD70 = regs[0x24];
}

struct Obj_20B168 { u8 pad[0x40]; u32* values; };

s32 func_0020B168(Obj_20B168* obj, s32 index, s32 value, s32 second)
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

struct Item_20B240 { s32 a; s32 b; s32 c; s32 d; };
void func_0020B240(Item_20B240* item, s32 value, s32 field)
{
    item->a = value;
    item->b = field;
    item->c = value;
    item->d = value;
}

s32 func_0020B268(s32* item)
{
    s32 value = item[3];
    item[2] = value;
    return value;
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

// NEAR: every instruction matches except the save and restore of s0-s6 and ra, which are sq/lq here and sd/ld in retail (the default compiler saves 16 bytes per register; no C form found that changes it).

struct Rec_2095B0 { s32 f00; s32 f04; s32 f08; u8 pad0C[8]; u8 name[0x400]; };
struct Handle_2095B0;
struct Pool_2095B0;
struct Name_2095B0;

extern s32 D_0027AECC;
extern u8 D_0062AD40[];
extern u8 D_0062AE04[];
extern u8 D_0062C300[];
extern s32 D_0027AEC8;

s32 func_001F6B70(Handle_2095B0* h);
void func_001F6B40(Handle_2095B0* h);
s32 func_001F8290(Pool_2095B0* p, s32 a1, s32 a2, Rec_2095B0* r, s32 size, u8* desc, s32 a6, s32 a7, s32 extra);
s32 func_00201720(Name_2095B0* dst, const char* src, s32 max);

s32 func_002095B0(s32 a0, s32 a1, const char* a2, s32 a3)
{
    if (func_001F6B70((Handle_2095B0*)D_0027AECC) < 0) {
        return -200;
    }
    u8* pool = D_0062AD40;
    if (*(s32*)(pool + 0x24) == 0) {
        func_001F6B40((Handle_2095B0*)D_0027AECC);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        func_001F6B40((Handle_2095B0*)D_0027AECC);
        return -210;
    }
    u8* name = D_0062AE04;
    func_00201720((Name_2095B0*)name, a2, 0x3FF);
    ((s32*)name)[-5] = a0;
    Rec_2095B0* r = (Rec_2095B0*)(name - 0x14);
    r->f08 = a3;
    r->f04 = a1;
    r->name[0x3FF] = 0;
    s32 result = func_001F8290((Pool_2095B0*)pool, 2, 1, r, 0x414, D_0062C300, 4, 0, 0);
    if (result == 0) {
        D_0027AEC8 = 2;
    } else {
        func_001F6B40((Handle_2095B0*)D_0027AECC);
    }
    return result;
}

// NEAR: only the ra save and restore differ (ours sq/lq, retail sd/ld; 0x20 lib region, see docs/TOOLCHAIN.md)

struct Ctx_2096E8;
extern s32 D_0027AEC8;
void* func_002095B0(Ctx_2096E8* ctx, s32 a1, void* a2, void* a3);

void* func_002096E8(Ctx_2096E8* ctx, s32 a1, void* a2)
{
    void* p = func_002095B0(ctx, a1, a2, (void*)0x40);
    if (p == 0) {
        D_0027AEC8 = 0xB;
    }
    return p;
}

// NEAR: retail is library code (0x1F59C4 and up, layout.tsv) built by 2.9-ee-991111: saves are sd (8 bytes), ours sq; the epilogue is ld, ours lq. Beyond the saves, s0/s1 order of the table address and the first slot stores still differ (21 lines in check.py).

struct Dev_00209870 { u8 pad[0x4]; };
struct Ctl_00209870 { u8 pad[0x24]; s32 busy; };
struct Slot_00209870 { void* owner; u8 pad0[8]; void* arg2; u8 pad1[8]; void* arg1; void* tab; };

extern u8 D_0062AD40[];
extern u8 D_0062ADC0[];
extern u8 D_0062B240[];
extern u8 D_0062C300[];
extern s32 D_0027AEC8;

s32 func_001F6B70(Dev_00209870* d);
void func_001F6B40(Dev_00209870* d);
void func_001FA7D8(void* a, s32 b);
s32 func_001F8290(Dev_00209870* a, s32 b, s32 c, void* d, s32 e, void* f, s32 g, void* h, void* i);
void func_002097D8(void);

s32 func_00209870(void* a0, void* a1, void* a2)
{
    Ctl_00209870* ctl;
    Slot_00209870* slot;
    void* tab;
    s32 r;
    if (func_001F6B70((*(Dev_00209870**)&D_0027AECC)) < 0) {
        return -200;
    }
    ctl = (Ctl_00209870*)D_0062AD40;
    if (ctl->busy == 0) {
        func_001F6B40((*(Dev_00209870**)&D_0027AECC));
        return -100;
    }
    tab = D_0062B240;
    slot = (Slot_00209870*)D_0062ADC0;
    slot->owner = a0;
    slot->tab = tab;
    slot->arg1 = a1;
    slot->arg2 = a2;
    func_001FA7D8(a1, (s32)a2);
    func_001FA7D8(tab, 0xC0);
    r = func_001F8290((Dev_00209870*)ctl, 5, 1, slot, 0x30, D_0062C300, 4,
                      (void*)((u8*)func_002097D8 + 8), tab);
    if (r == 0) {
        D_0027AEC8 = 5;
    } else {
        func_001F6B40((*(Dev_00209870**)&D_0027AECC));
    }
    return r;
}

// NEAR: body matches; retail saves and restores its eight $s registers with sd/ld, the 2.9-ee library compiler, where SN GCC 2.95.3 emits sq/lq (only those 18 lines differ).

struct Lock_9E48;
struct Mgr_9E48;
struct Rec_9E48 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; u8 name[0x400]; };

s32 func_001F6B70(Lock_9E48* lock);
void func_001F6B40(Lock_9E48* lock);
void func_00201720(u8* dst, const char* src, s32 max);
void func_001FA7D8(s32 a, s32 b);
s32 func_001F8290(Mgr_9E48* a, s32 b, s32 c, Rec_9E48* d, s32 e, u8* f, s32 g, s32 h, s32 i);

extern s32 D_0027AECC;
extern u8 D_0062AD40[];
extern u8 D_0062ADF0[];
extern u8 D_0062C300[];
extern s32 D_0027AEC8;

s32 func_00209E48(s32 a0, s32 a1, const char* name, s32 a3, s32 a4, s32 a5)
{
    s32 status = func_001F6B70((Lock_9E48*)D_0027AECC);
    if (status < 0) {
        return -200;
    }
    Mgr_9E48* mgr = (Mgr_9E48*)D_0062AD40;
    if (*(s32*)(D_0062AD40 + 0x24) == 0) {
        func_001F6B40((Lock_9E48*)D_0027AECC);
        return -100;
    }
    if (name == 0 || *name == 0) {
        func_001F6B40((Lock_9E48*)D_0027AECC);
        return -210;
    }
    Rec_9E48* rec = (Rec_9E48*)D_0062ADF0;
    rec->f0 = a0;
    rec->f4 = a1;
    rec->f8 = a3;
    rec->fC = a4;
    rec->f10 = a5;
    func_00201720((u8*)rec + 0x14, name, 0x3FF);
    ((u8*)rec)[0x413] = 0;
    if (a4 >= 0) {
        func_001FA7D8(a5, a4 << 6);
    }
    s32 r = func_001F8290(mgr, 0xD, 1, rec, 0x414, D_0062C300, 4, 0, 0);
    if (r == 0) {
        D_0027AEC8 = 0xD;
    } else {
        func_001F6B40((Lock_9E48*)D_0027AECC);
    }
    return r;
}

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

struct Ctx_0020A518;
s32 func_0020A220(Ctx_0020A518* ctx, s32 a, s32 b, s32 c, s32 d);

s32 func_0020A518(Ctx_0020A518* ctx, s32 a, s32 b) { return func_0020A220(ctx, a, b, 0, -1); }

// NEAR: body matches; only the saves differ: retail sd/ld, ours sq/lq

struct Obj_0020A780;

void func_002116B0(Obj_0020A780* self, s32 size);
s32 func_002115F8(Obj_0020A780* self, s32 n);

s32 func_0020A780(Obj_0020A780* self)
{
    func_002116B0(self, 0x38);
    func_002116B0(self, 0x28);
    while (func_002115F8(self, 1) == 1) {
        func_002116B0(self, 0x18);
    }
    return 1;
}

// NEAR: the body matches; retail saves s0, s1 and ra with 8-byte sd/ld, the default 2.95.3 build with 16-byte sq/lq (PAL differs too)

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

// NEAR: only the s0 and ra saves and restores differ (ours sq/lq, retail sd/ld)

struct Buf_0020B940;
struct Ctx_0020B940;
s32 func_001E1FD0(Buf_0020B940* dst, const char* fmt, ...);
void func_0020B978(Ctx_0020B940* self, char* buf);

void func_0020B940(Ctx_0020B940* self, const char* fmt)
{
    char buf[0x100];
    func_001E1FD0((Buf_0020B940*)buf, fmt);
    func_0020B978(self, buf);
}

// NEAR: retail saves $ra with sd (8 bytes) and reloads with ld; SN GCC 2.95.3 saves it with sq. Body otherwise matches.

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

s32 func_0020B190(Sub_20B978* sub, Pair_20B978* pair);
s32 func_0020B930(Arg_20B978* arg);

s32 func_0020B978(Self_20B978* self, s32 value)
{
    Pair_20B978 pair;

    if (self->f858 != 0 && self != 0 && self->f0C != 0) {
        pair.a = 0;
        pair.b = value;
        return func_0020B190((Sub_20B978*)self->f858, &pair);
    }
    return func_0020B930((Arg_20B978*)value);
}

// NEAR: retail saves $ra and $s0-$s5 with sd (8 bytes), not the 16-byte sq of this compiler; the body is otherwise identical.
extern u8 D_00250160[];
extern u8 D_00250188[];

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

u32 func_0020DEE8(u32 value);
u32 func_0020F5B8(struct Obj_20BF78 *self, u32 n);
void func_0020B978(struct Obj_20BF78 *self, void *p);

void func_0020BF78(struct Obj_20BF78 *self)
{
    u32 s2;
    u32 s0;
    u32 s3;
    u32 s4;
    u32 s5;

    self->field848 = 1;
    func_0020DEE8(0);
    s2 = func_0020F5B8(self, 0x1C);
    s5 = (s2 >> 1) & 0xFFF;
    self->field140 = (s2 >> 17) & 3;
    s4 = (s2 >> 13) & 3;
    s3 = (s2 >> 15) & 3;
    if (self->field140 != 1) {
        func_0020B978(self, D_00250160);
    }
    self->field13C = (s2 >> 19) & 1;
    s0 = s2 >> 20;
    s2 = func_0020F5B8(self, 0x10) >> 8;
    if (s0 != 0x48 && s0 != 0x58 && s0 != 0x44) {
        func_0020B978(self, D_00250188);
    }
    self->field124 = (s3 << 12) | (self->field124 & 0xFFF);
    self->field128 = (s4 << 12) | (self->field128 & 0xFFF);
    self->field134 += s5 << 18;
    self->field138 += s2 << 10;
}

struct Hdl_209720 { s32 v; };
struct Elt_209720 { u8 pad[0x24]; s32 f24; };
struct Slot_209720 { s32 v; };

extern u8 D_0062AD40[];
extern u8 D_0062C300[];
extern s32 D_0027AEC8;

s32 func_001F6B70(Hdl_209720* h);
s32 func_001F6B40(Hdl_209720* h);
s32 func_001F8290(Elt_209720* a, s32 b, s32 c, Slot_209720* d, s32 e, void* f, s32 g, s32 h, s32 i);

s32 func_00209720(s32 value)
{
    s32 r;
    Elt_209720* elt;
    if (func_001F6B70((*(Hdl_209720**)&D_0027AECC)) < 0) {
        return -200;
    }
    elt = (Elt_209720*)D_0062AD40;
    if (elt->f24 == 0) {
        (void)func_001F6B40((*(Hdl_209720**)&D_0027AECC));
        return -100;
    }
    (*(Slot_209720*)&D_0062ADC0).v = value;
    r = func_001F8290(elt, 3, 1, ((Slot_209720*)&D_0062ADC0), 0x30, D_0062C300, 4, 0, 0);
    if (r == 0) {
        D_0027AEC8 = 3;
    } else {
        (void)func_001F6B40((*(Hdl_209720**)&D_0027AECC));
    }
    return r;
}

struct Pool_209FA8 { u8 pad[0x24]; s32 busy; };
struct Req_209FA8 { s32 f0; s32 a; s32 b; };
struct Handle_209FA8 { s32 h; };

extern u8 D_0062C300[];

extern s32 func_001F6B70(Handle_209FA8* h);
extern void func_001F6B40(Handle_209FA8* h);
extern s32 func_001F8290(Pool_209FA8* p, s32 a1, s32 a2, Req_209FA8* q, s32 a4, u8* a5, s32 a6, s32 a7, s32 a8);

s32 func_00209FA8(s32 a, s32 b)
{
    s32 r = func_001F6B70((Handle_209FA8*)(*(u32*)&D_0027AECC));
    s32 res;
    if (r < 0) {
        return -200;
    }
    if (((Pool_209FA8*)D_0062AD40)->busy == 0) {
        func_001F6B40((Handle_209FA8*)(*(u32*)&D_0027AECC));
        return -100;
    }
    (*(Req_209FA8*)&D_0062ADC0).b = b;
    (*(Req_209FA8*)&D_0062ADC0).a = a;
    res = func_001F8290(((Pool_209FA8*)&D_0062AD40), 0x10, 1, ((Req_209FA8*)&D_0062ADC0), 0x30, D_0062C300, 4, 0, 0);
    if (res == 0) {
        (*(u32*)&D_0027AEC8) = 0x10;
    } else {
        func_001F6B40((Handle_209FA8*)(*(u32*)&D_0027AECC));
    }
    return res;
}

struct Obj_20B058 { u8 pad[0x40]; u8* state; };

s32 func_0020B2E8(Obj_20B058* obj);

s32 func_0020B058(Obj_20B058* obj, u32 a1, s32 a2)
{
    u8* st = obj->state;
    *(s32*)(st + 0xB0) = 1;
    *(u32*)(st + 0xD8) = (a1 & 0xFFFFFFFu) | 0x20000000u;
    *(s32*)(st + 0xE4) = a2;
    *(s32*)(st + 0xE0) = 0;
    *(s32*)(st + 0xDC) = 0;
    return func_0020B2E8(obj);
}

struct Q_0020B1E0;
s32 func_0020B190(Q_0020B1E0* q, s32* out);

s32 func_0020B1E0(Q_0020B1E0* q)
{
    s32 flag[8];
    flag[0] = 1;
    return func_0020B190(q, flag);
}

struct Owner_0020B278;

struct Pool_0020B278 {
    u32 f00;
    u32 f04;
    u32 f08;
};

extern u8 D_00250098[];

s32 func_0020B978(Owner_0020B278* owner, u8* p);

s32 func_0020B278(Owner_0020B278* owner, Pool_0020B278* pool, u32 offset, u32 align)
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
    (void)func_0020B978(owner, D_00250098);
    return 0;
}

struct Ctx_0020B190;
typedef s32 (*Fn_0020B190)(Ctx_0020B190*, s32*, s32);
struct Ent_0020B190 { Fn_0020B190 fn; s32 arg; };
struct Tab_0020B190 { u8 pad[0xC]; Ent_0020B190 e[1]; };
struct Ctx_0020B190 { u8 pad[0x40]; Tab_0020B190* table; };
s32 func_0020B190(Ctx_0020B190* p, s32* idx) {
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

struct Ent_20A538 { u64 key; u64 data; s32 value; s32 extra; };
struct Ctx_20A538 { u8 pad[0x44]; struct Ent_20A538* ents; s32 count; };
struct Obj_20A538 { u8 pad[0x40]; struct Ctx_20A538* ctx; };
struct Pair_20A538 { u64 a; u64 b; };
extern Pair_20A538 D_0027AED0[];
u64 func_0020A190(s32 idx, u64 key);

s32 func_0020A538(struct Obj_20A538* self, s32 idx, u64 key, s32 a3, s32 a4)
{
    s32 result = 0;
    struct Ctx_20A538* ctx = self->ctx;
    struct Ent_20A538* ents = ctx->ents;
    u64 k = func_0020A190(idx, key);
    s32 count = ctx->count;
    s32 i;
    for (i = 0; i < count; i++) {
        if (k == ents[i].key) {
            result = ents[i].value;
            break;
        }
    }
    if (i < 0x40) {
        struct Ent_20A538* e = &ents[i];
        ctx->count = count + 1;
        e->key = k;
        e->extra = a4;
        e->value = a3;
        e->data = D_0027AED0[idx].b;
    }
    return result;
}

// EXACT: o->w8 and o->w4 computed straight from a (no v temp), the byte loop as a for
struct Reader_0020A630 { u8 pad[0x10]; };
struct Out_0020A630 { s32 w0; s32 w4; s32 w8; s32 wC; };

s32 func_002116B0(Reader_0020A630* r, s32 bits);
void func_00211700(Reader_0020A630* r);
s32 func_002115F8(Reader_0020A630* r, s32 bits);
void func_0020A780(Reader_0020A630* r, Out_0020A630* o);

s32 func_0020A630(Reader_0020A630* r, Out_0020A630* o)
{
    u32 i; u32 n; u32 a; u32 b; u32 c;
    i = 0;
    (void)func_002116B0(r, 0x22);
    a = func_002116B0(r, 3);
    func_00211700(r);
    b = func_002116B0(r, 0xF);
    func_00211700(r);
    c = func_002116B0(r, 0xF);
    func_00211700(r);
    o->w0 = func_002116B0(r, 9);
    (void)func_002116B0(r, 0x1E);
    n = func_002116B0(r, 3);
    o->w8 = (a >> 2) & 1;
    o->w4 = (a << 30) | (b << 15) | c;
    for (i = 0; i < n; i++) {
        (void)func_002116B0(r, 8);
    }
    if (func_002115F8(r, 0x20) == 0x1BB) {
        o->wC = 1;
        func_0020A780(r, o);
    } else {
        o->wC = 0;
    }
    return 1;
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
s32 func_00210090(Sub_20B5B8* sub);
s32 func_0020F7F0(Sub_20B5B8* sub);
s32 func_0020B718(Ctx_20B5B8* ctx);
void func_00210160(Sub_20B5B8* sub, s32 a1, s32 a2);
void func_0020B1E0(Ctx_20B5B8* ctx);

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
            (void)func_00210090(s0);
        }
    }
    s1 = 1;
    s0->f120 = s1;
    if (func_0020F7F0(s0) == 0) {
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
            s4 = (func_00210090(s0) != 0) ? s1 : 0;
        }
    }
    func_00210160(s0, s0->f118, s0->f4);
    s0->f120 = 0;
    self->f8 = s0->f118 - s0->fAC;
    s0->f118 = s0->f118 + 1;
    s0->f4 = s0->f4 + 1;
    if (s3 == 0) {
        func_0020B1E0(self);
    }
    return s4;
}

struct Rec_209CB8 { s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; s32 f1C; };
struct Handle_209CB8;
struct Pool_209CB8 { u8 pad[0x24]; s32 f24; };
struct Blk_209CB8;
typedef void (*Cb_209CB8)(u32 base);

extern s32 D_0027AECC;
extern u8 D_0062B240[];
extern u8 D_0062C300[];
extern s32 D_0027AEC8;

s32 func_001F6B70(Handle_209CB8* h);
void func_001F6B40(Handle_209CB8* h);
s32 func_001FA7D8(Blk_209CB8* p, s32 size);
s32 func_001F8290(Pool_209CB8* p, s32 a1, s32 a2, Rec_209CB8* r, s32 size, u8* desc, s32 a6, Cb_209CB8 cb, u8* extra);
void func_00209C60(u32 base);

s32 func_00209CB8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (func_001F6B70((Handle_209CB8*)D_0027AECC) < 0) {
        return -200;
    }
    if ((*(Pool_209CB8*)&D_0062AD40).f24 == 0) {
        func_001F6B40((Handle_209CB8*)D_0027AECC);
        return -100;
    }
    (*(Rec_209CB8*)&D_0062ADC0).f04 = a0;
    (*(Rec_209CB8*)&D_0062ADC0).f08 = a1;
    (*(Rec_209CB8*)&D_0062ADC0).f1C = (s32)D_0062B240;
    if (a2) {
        (*(Rec_209CB8*)&D_0062ADC0).f14 = 1;
    } else {
        (*(Rec_209CB8*)&D_0062ADC0).f14 = 0;
    }
    if (a3) {
        (*(Rec_209CB8*)&D_0062ADC0).f10 = 1;
    } else {
        (*(Rec_209CB8*)&D_0062ADC0).f10 = 0;
    }
    if (a4) {
        (*(Rec_209CB8*)&D_0062ADC0).f0C = 1;
    } else {
        (*(Rec_209CB8*)&D_0062ADC0).f0C = 0;
    }
    (*(s32*)&D_0062AD68) = a2;
    (*(s32*)&D_0062AD6C) = a3;
    (*(s32*)&D_0062AD70) = a4;
    (void)func_001FA7D8((Blk_209CB8*)D_0062B240, 0xC0);
    s32 result = func_001F8290(((Pool_209CB8*)&D_0062AD40), 1, 1, ((Rec_209CB8*)&D_0062ADC0), 0x30, D_0062C300, 4, func_00209C60, D_0062B240);
    if (result == 0) {
        D_0027AEC8 = 1;
    } else {
        func_001F6B40((Handle_209CB8*)D_0027AECC);
    }
    return result;
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

void func_0020B940(Ctx_20B2E8* c, s32 msg, s32 flags);
s32 func_0020F7F0(Ctx_20B2E8* c);
s32 func_0020B570(Self_20B2E8* self, s32 a, s32 b);
s32 func_0020B718(Self_20B2E8* self);
extern s32 D_002500B8;

s32 func_0020B2E8(Self_20B2E8* self)
{
    s32 s3 = 1;
    s32 s2 = 0;
    Ctx_20B2E8* c = self->ctx;
    c->f0 = 0;
    if ((c->fD8 & 0x3F) != 0) {
        func_0020B940(c, (s32)&D_002500B8, c->fD8);
        return -1;
    }
    c->f820 = 0;
    for (;;) {
        if (s2 != -1) {
            do {
                s3 = func_0020F7F0(c);
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

struct Ctx_20A7F0;

struct Bits_20A7F0
{
    u8 pad00[0x18];
    s64 pos;
};

struct Hdr_20A7F0
{
    u64 id;
    s32 len;
    s32 scramble;
    s64 pts;
    s64 dts;
    s32 start;
    s32 size;
    s32 at;
};

struct Table_20A7F0
{
    u8 bits[16];
};

extern Table_20A7F0 D_00250028;
extern char D_00250038[];

u32 func_002116B0(Bits_20A7F0* bs, s32 n);
void func_00211700(Bits_20A7F0* bs);
void func_00211748(Bits_20A7F0* bs, s32 n);
void func_0020B978(Ctx_20A7F0* ctx, char* msg);

s32 func_0020A7F0(Ctx_20A7F0* ctx, Bits_20A7F0* bs, Hdr_20A7F0* hdr)
{
    Table_20A7F0 tbl;
    s32 flags;
    s32 escr;
    s32 opt;
    s32 ext;
    s32 hdrlen;
    s32 start;
    s32 n;
    s32 skip;
    s32 rest;

    hdr->at = bs->pos;
    tbl = D_00250028;
    func_002116B0(bs, 0x18);
    hdr->id = (u64)func_002116B0(bs, 8) << 32;
    hdr->len = func_002116B0(bs, 16);
    hdr->dts = -1;
    hdr->pts = -1;
    if (hdr->id != (u64)0xBC << 32 && hdr->id != (u64)0xBE << 32 && hdr->id != (u64)0xBF << 32
        && hdr->id != (u64)0xF0 << 32 && hdr->id != (u64)0xF1 << 32 && hdr->id != (u64)0xFF << 32
        && hdr->id != (u64)0xF2 << 32 && hdr->id != (u64)0xF8 << 32)
    {
        func_002116B0(bs, 2);
        hdr->scramble = func_002116B0(bs, 2);
        func_002116B0(bs, 4);
        flags = func_002116B0(bs, 2);
        escr = func_002116B0(bs, 1);
        opt = func_002116B0(bs, 4);
        ext = func_002116B0(bs, 1);
        hdrlen = func_002116B0(bs, 8);
        start = bs->pos;
        if (flags & 2)
        {
            u32 a, b, c;
            func_002116B0(bs, 4);
            a = func_002116B0(bs, 3);
            func_00211700(bs);
            b = func_002116B0(bs, 15);
            func_00211700(bs);
            c = func_002116B0(bs, 15);
            func_00211700(bs);
            hdr->pts = ((u64)((a >> 2) & 1) << 32) | (u32)((a << 30) | (b << 15) | c);
        }
        if (flags == 3)
        {
            u32 a, b, c;
            func_002116B0(bs, 4);
            a = func_002116B0(bs, 3);
            func_00211700(bs);
            b = func_002116B0(bs, 15);
            func_00211700(bs);
            c = func_002116B0(bs, 15);
            func_00211700(bs);
            hdr->dts = ((u64)((a >> 2) & 1) << 32) | (u32)((a << 30) | (b << 15) | c);
        }
        if (escr == 1)
        {
            func_002116B0(bs, 0x30);
        }
        if (opt != 0)
        {
            func_002116B0(bs, tbl.bits[opt]);
        }
        if (ext == 1)
        {
            s32 priv = func_002116B0(bs, 1);
            s32 pack = func_002116B0(bs, 1);
            s32 seq = func_002116B0(bs, 1);
            s32 pstd = func_002116B0(bs, 1);
            s32 ext2;
            func_002116B0(bs, 3);
            ext2 = func_002116B0(bs, 1);
            if (priv == 1)
            {
                func_002116B0(bs, 0x30);
                func_002116B0(bs, 0x30);
                func_002116B0(bs, 0x20);
            }
            if (pack == 1)
            {
                func_0020B978(ctx, D_00250038);
                return 0;
            }
            if (seq == 1)
            {
                func_002116B0(bs, 0x10);
            }
            if (pstd == 1)
            {
                func_002116B0(bs, 0x10);
            }
            if (ext2 == 1)
            {
                u32 i;
                u32 count;
                func_00211700(bs);
                count = func_002116B0(bs, 7);
                for (i = 0; i < count; i++)
                {
                    func_002116B0(bs, 8);
                }
            }
        }
        skip = hdrlen - (s32)((bs->pos - start) >> 3);
        if (skip != 0)
        {
            func_00211748(bs, skip);
        }
        rest = hdr->len - hdrlen;
        n = rest - 3;
        hdr->size = n;
        hdr->start = bs->pos;
        if (hdr->id == (u64)0xBD << 32)
        {
            hdr->id |= func_002116B0(bs, 32);
            n = rest - 7;
        }
        if (n != 0)
        {
            func_00211748(bs, n);
        }
    } else {
    if (hdr->id == (u64)0xBC << 32 || hdr->id == (u64)0xBF << 32 || hdr->id == (u64)0xF0 << 32
        || hdr->id == (u64)0xF1 << 32 || hdr->id == (u64)0xFF << 32 || hdr->id == (u64)0xF2 << 32
        || hdr->id == (u64)0xF8 << 32)
    {
        s32 m = hdr->len;
        if (hdr->id == (u64)0xBF << 32)
        {
            hdr->id |= func_002116B0(bs, 32);
            m -= 4;
        }
        if (m != 0)
        {
            func_00211748(bs, m);
        }
    }
    else if (hdr->id == (u64)0xBE << 32)
    {
        if (hdr->len != 0)
        {
            func_00211748(bs, hdr->len);
        }
    }
    }
    return 1;
}

struct Req_2093F0 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};
struct Sema_2093F0 {
    u8 pad00[0x24];
    s32 f24;
};
struct Info_2093F0 {
    s32 f0;
    s32 f4;
    s32 f8;
};

extern s32 D_0027AECC;
extern u8 D_0062ADC0[];
extern u8 D_0024FFA0[];
extern u8 D_0024FFB8[];
extern u8 D_0024FFE0[];

s32 func_001F6B20(Req_2093F0* r);
void func_00209B80(s32 a, s32 b, s32 c);
void func_001F6B60(s32 sema);
void func_001F7BE8(s32 a);
s32 func_001F80C0(Sema_2093F0* p, u32 flags, s32 z);
void func_001E1F10(u8* msg);
s32 func_001F8290(Sema_2093F0* p, s32 a1, s32 a2, u8* a3, s32 a4, Info_2093F0* a5, s32 a6, s32 a7, s32 a8);
void func_001F6B40(s32 sema);

s32 func_002093F0(void)
{
    if (D_0027AECC < 0) {
        Req_2093F0 req;
        req.f14 = 0;
        req.f08 = 1;
        req.f04 = 1;
        D_0027AECC = func_001F6B20(&req);
    }
    func_00209B80(0, 0, 0);
    func_001F6B60(D_0027AECC);
    func_001F7BE8(0);
    for (;;) {
        if (func_001F80C0((Sema_2093F0*)D_0062AD40, 0x80000400, 0) < 0) {
            func_001E1F10(D_0024FFA0);
            for (;;) {
            }
        }
        if (((Sema_2093F0*)D_0062AD40)->f24 != 0) {
            break;
        }
        for (s32 i = 0x100000; i != 0; i--) {
        }
    }
    s32 r = func_001F8290((Sema_2093F0*)D_0062AD40, 0xFE, 0, D_0062ADC0, 0x30, (Info_2093F0*)D_0062C300, 0xC, 0, 0);
    func_001F6B40(D_0027AECC);
    if (r < 0) {
        ((Sema_2093F0*)D_0062AD40)->f24 = 0;
        return r - 100;
    }
    if (((Info_2093F0*)D_0062C300)->f4 < 0x20A) {
        func_001E1F10(D_0024FFB8);
        ((Sema_2093F0*)D_0062AD40)->f24 = 0;
        return -0x78;
    }
    if (((Info_2093F0*)D_0062C300)->f8 < 0x20E) {
        func_001E1F10(D_0024FFE0);
        ((Sema_2093F0*)D_0062AD40)->f24 = 0;
        return -0x79;
    }
    return ((Info_2093F0*)D_0062C300)->f0;
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

void* func_001F5C0C(s32 dst, s32 c, u32 n);
void func_0020B978(Inner_20AE40* a, const char* msg);
void func_0020B240(Ring_20AE40* r, u8* start, u32 size);
s32 func_0020B278(Inner_20AE40* a, Ring_20AE40* r, u32 size, u32 align);
void func_0020B810(Inner_20AE40* a);
void func_0020B0C0(Outer_20AE40* a);
s32 func_0020B110(Outer_20AE40* a);
void func_0020B258(Ring_20AE40* r);
void func_0020C178(void);
void func_0020C188(void);

s32 func_0020AE40(Outer_20AE40* out, s32 mem, u32 size)
{
    func_001F5C0C(mem, 0, size);
    Inner_20AE40* in = (Inner_20AE40*)(((u32)(mem + 3) >> 2) << 2);
    s32 diff = (s32)in - mem;
    u32 rest = size - diff;
    if (rest < 0x10C0) {
        func_0020B978(in, "The size of work area is too small");
        return 0;
    }
    out->f40 = (s32)in;
    rest -= 0x10C0;
    func_0020B240(&in->ring, (u8*)in + 0x10C0, rest);
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
    in->f1C = (s32)func_0020C178;
    in->f24 = (s32)func_0020C188;
    s32 r278 = func_0020B278(in, &in->ring, 0x600, 8);
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
    func_0020B0C0(out);
    func_0020B110(out);
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

void func_0020B978(struct Obj_0020B790 *self, const char *msg);
void func_00210970(struct Obj_0020B790 *self, s32 a1, s32 a2);
void func_00210A80(struct Obj_0020B790 *self, s32 a1, s32 a2, s32 a3);

void func_0020B790(struct Obj_0020B790 *self)
{
    s32 n = self->f118;
    if (self->f120 != 0)
        func_0020B978(self, "the second field is missing");
    else if (self->f174 == 3)
        func_00210970(self, self->f1BC, n - 1);
    else
        func_00210A80(self, self->f1CC, self->f1DC, n - 1);
    self->f120 = 0;
}

struct Pkt_2097E0 {
    s32 n0;
    s32 n1;
    u8* dst0;
    u8* dst1;
    u8 src0[0x40];
    u8 src1[0x40];
};

void func_002097E0(Pkt_2097E0* p) {
    Pkt_2097E0* q = (Pkt_2097E0*)((u32)p | 0x20000000);
    if (q->n0) {
        u8* d = q->dst0;
        for (s32 i = 0; i < q->n0; i++) {
            *d++ = q->src0[i];
        }
    }
    if (q->n1) {
        u8* d = q->dst1;
        for (s32 i = 0; i < q->n1; i++) {
            *d++ = q->src1[i];
        }
    }
}

void func_00209B10(void);
s32 func_001F6A90(void);
void func_001F69E0(s32 id, void (*cb)(void), s32 ctx);
void func_001F6AB0(void);

void func_00209B38(u16 id) {
    func_001F69E0(id, func_00209B10, func_001F6A90());
    func_001F6AB0();
}

void func_0020B780(void* s);
void func_0020B870(void* s);
struct S_20B0C0 { u8 pad0[8]; s32 f8; u8 pad[0x34]; u8* st; };
void func_0020B0C0(S_20B0C0* d) {
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

void func_0020DEE8(s32 a);
struct S_20B780 { u8 pad[0x848]; s32 f; };
void func_0020B780(S_20B780* s) {
    s->f = 0;
    func_0020DEE8(1);
}

void func_001E1F10(const char* fmt, s32 msg);

void func_0020B930(s32 msg) {
    func_001E1F10("[MPEG ERROR]%s\n", msg);
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

extern u8 D_0027AF80[];
extern u8 D_0027AFC0[];

u32 func_0020F5B8(Dec_20B9F0* d, s32 bits);
void func_0020B978(Dec_20B9F0* d, const char* msg);
void func_0020F0F0(Dec_20B9F0* d);
void func_0020F0C0(Dec_20B9F0* d, u32 value);
void func_0020BEA0(Dec_20B9F0* d, u32 value, u8* table);
void func_0020F9C8(Dec_20B9F0* d);
void func_0020BB18(void* p);

void func_0020B9F0(Dec_20B9F0* d) {
    d->fD4 = 0;
    u32 v = func_0020F5B8(d, 0x20);
    d->f124 = v >> 20;
    d->f128 = (v >> 8) & 0xFFF;
    if (d->f128 > 0xAF0) {
        func_0020B978(d, "vertical size > 2800");
    }
    v = func_0020F5B8(d, 0x1E);
    d->f134 = v >> 12;
    d->f138 = (v >> 1) & 0x3FF;
    d->f840 = func_0020F5B8(d, 1);
    if (d->f840) {
        func_0020F0F0(d);
        func_0020F0C0(d, 0x50000000);
        func_0020F0F0(d);
    } else {
        func_0020BEA0(d, 0x50000000, D_0027AF80);
    }
    d->f844 = func_0020F5B8(d, 1);
    if (d->f844) {
        func_0020F0F0(d);
        func_0020F0C0(d, 0x58000000);
        func_0020F0F0(d);
    } else {
        func_0020BEA0(d, 0x58000000, D_0027AFC0);
    }
    func_0020F9C8(d);
    func_0020BB18(d->f858);
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);
void func_00211BA8(void);

void func_0020ADA0(void) {
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 &= 0xFFFFFEFF;
    *(volatile u32*)0x1000B400 &= 0xFFFFFEFF;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    func_00211BA8();
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);
void func_00211AD8(s32 a, s32 b);

struct Chan_20B870 {
    u8 pad0[0x1B0];
    s32 f1B0;
    u8 pad1[0x818 - 0x1B4];
    s32 f818;
};

void func_0020B870(Chan_20B870* c) {
    c->f818 = 1;
    c->f1B0 = 0;
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = 0;
    *(volatile u32*)0x1000B400 = 0;
    *(volatile u32*)0x1000D400 = 0;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    *(volatile u32*)0x1000D420 = 0;
    *(volatile u32*)0x10002010 = 0x40000000;
    func_00211AD8(0, 0);
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

void func_0020DEE8(s32 a);

void func_0020B810(Dev_20B810* self)
{
    u8* spr = (u8*)0x70000000;
    func_0020DEE8(1);
    self->f590 = spr;
    self->f594 = spr + 0x1800;
    self->f6D0 = spr + 0x1B00;
    self->f6D4 = spr + 0x3300;
    self->f810 = 0;
}

struct Obj_209B80;
struct Q_209B80;
struct Dev_209B80;
extern s32 D_0027AEC8;
extern s32 D_0027AECC;
extern u8 D_0062AD40[];
s32 func_001F8480(Q_209B80* q);
s32 func_00209B38(Obj_209B80* o);
s32 func_001F6B40(Dev_209B80* d);

s32 func_00209B80(Obj_209B80* a0, s32* a1, s32* a2)
{
    s32 ok;
    if (D_0027AEC8 == 0) {
        return -1;
    }
    ok = func_001F8480((Q_209B80*)D_0062AD40);
    if (a0 == 0 && ok != 0) {
        while (func_001F8480((Q_209B80*)D_0062AD40) != 0) {
            (void)func_00209B38((Obj_209B80*)60);
        }
        ok = 0;
    }
    ok = (ok == 0);
    if (a1 != 0) {
        *a1 = D_0027AEC8;
    }
    if (ok != 0) {
        D_0027AEC8 = 0;
        if (a2 != 0) {
            *a2 = (*(s32*)&D_0062C300);
        }
        (void)func_001F6B40((Dev_209B80*)D_0027AECC);
    }
    return ok;
}

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
