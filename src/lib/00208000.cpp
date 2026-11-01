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

struct Obj_00208FE8 { u8 pad[8]; s64 f8; };
typedef s64 Key_00208FE8;
s32 func_001FD308(Key_00208FE8 a, Key_00208FE8 b);

s32 func_00208FE8(Obj_00208FE8* obj)
{
    Key_00208FE8 v = obj->f8;
    (void)func_001FD308(v, v);
    return 0;
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
