// SPDX-License-Identifier: AGPL-3.0-or-later
// The runtime's exception classes keep their vtables where retail has them (config/us/libcalls.tsv):
// with `#pragma interface` the compiler refers to them by name instead of writing its own.
#pragma interface
#include "common.h"

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

u8* func_001FF048(u8* input, u32* output)
{
	u8 byte = *input;
	u32 shift = 0;
	input++;
	u32 value = byte & 0x7F;
	if (byte & 0x80) {
		do {
			byte = *input;
			shift += 7;
			input++;
			value |= (byte & 0x7F) << shift;
		} while (byte & 0x80);
	}
	*output = value;
	return input;
}

void* func_001FFFE0(void* a0, void* a1) { return a1; }

void* func_001FFFE8(void* a0, void* a1) { return a1; }

u8* func_001FF090(u8* input, s32* output)
{
    u32 shift = 0;
    u32 value = 0;
    u8 byte;

    do {
        byte = *input++;
        value |= (u32)(byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);

    if (shift < 32) {
        s32 signMask = -1;
        if (byte & 0x40) {
            value |= signMask << shift;
        }
    }
    *output = (s32)value;
    return input;
}

extern s32 D_00278640;

s32 func_001FE928(s32 value)
{
    s32 previous = D_00278640;
    D_00278640 = value;
    return previous;
}

struct Node_1FFBE0 { s32 first; s32 second; s32 value; s32 link; s32 flag; Node_1FFBE0* previous; };
extern Node_1FFBE0* D_0062A7B8;

void func_001FFBE0(s32 value, Node_1FFBE0* item)
{
    item->value = value;
    item->second = 0;
    item->first = 0;
    item->flag = 0;
    item->link = value;
    item->previous = D_0062A7B8;
    D_0062A7B8 = item;
}

s32 D_002789D8;

s32 func_001FFFD0(s32 value)
{
    s32 previous = D_002789D8;
    D_002789D8 = value;
    return previous;
}

struct Cur_1FF490 { s32 off; s32 f4; s32 f8; s32 fC; };
struct List_1FF490 { Cur_1FF490** items; s32 count; };

void func_001FF490(Cur_1FF490* cur, List_1FF490* list, s32* lo, s32* hi)
{
    s32 mn = *lo;
    s32 mx = *hi;
    if (cur->off != 0) {
        do {
            if (cur->f4 == 0) goto next;
            if (cur->f8 == 0) goto next;
            {
                list->items[list->count++] = cur;
                {
                    s32 x = cur->f8;
                    s32 e = x + cur->fC;
                    if ((u32)x < (u32)mn) mn = x;
                    if ((u32)mx < (u32)e) mx = e;
                }
            }
        next:
            cur = (Cur_1FF490*)((u8*)cur + cur->off + 4);
        } while (cur->off != 0);
    }
    *lo = mn;
    *hi = mx;
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0024F0C0[];

void* func_001FEF58(void* self)
{
    *(void**)self = ((u8*)D_0024F0C0);
    return self;
}

extern u8 D_0024F0D8[];

void* func_001FEFF0(void* self)
{
    *(void**)self = D_0024F0D8;
    return self;
}

void func_00200000(void);
void func_00200050(void);
void* func_001FFFF0(void);
struct VEnt_24F1E0 { s32 delta; void (*fn)(); };
struct Bad_24F1E0 { char name[24]; VEnt_24F1E0 vt[3]; };
extern const Bad_24F1E0 D_0024F1E0;

void* func_001FFFF0(void)
{
    return (void*)&D_0024F1E0;
}

extern void (*D_00278048)();

u8* func_001FDA10(void);

// NEAR: retail saves $ra with sd, default compiler with sq; body identical
struct Ctx_001FE978;
void* func_001FDA10(Ctx_001FE978* self);

s32 func_001FE978(Ctx_001FE978* self)
{
	return *(s32*)func_001FDA10(self);
}

// NEAR: default 2.95.3 saves $ra with sq/lq where retail has sd/ld; EXACT with SLY1_COMPILER=2.9-ee-991111

struct Obj_001FE998 {
    u8 pad[0x14];
    s32 flag;
    u8 pad2[8];
    s64 count;
};


Obj_001FE998* func_001FE998(void)
{
    Obj_001FE998* obj = *(Obj_001FE998**)func_001FDA10();
    obj->flag = 1;
    obj->count++;
    return obj;
}

// NEAR: retail saves s0..s3 and ra with 8-byte sd/ld (the default compiler: 16-byte sq/lq); and retail stores the function pointer at +0 before the two halfword stores, and computes its address before the `li v1,1`, where ours keeps the halfword stores first. Otherwise identical

struct Size_1FEA88;
struct Fn_1FEA88;

struct Obj_1FEA88 {
    void* f00;
    u16 f04;
    u16 f06;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    u64 f20;
    s32 f28;
};

struct Obj_1FEA88* func_001FE9D0(struct Size_1FEA88* n);
s32 func_001FEA18(struct Fn_1FEA88* self);

void func_001FEA88(s32 a0, s32 a1, s32 a2)
{
    struct Obj_1FEA88* obj = func_001FE9D0((struct Size_1FEA88*)0x30);
    obj->f0C = a1;
    obj->f10 = a2;
    obj->f08 = a0;
    obj->f28 = a0;
    obj->f20 = 0;
    obj->f14 = 0;
    obj->f00 = (void*)func_001FEA18;
    obj->f04 = 4;
    obj->f06 = 1;
    s32* p = (s32*)func_001FDA10();
    obj->f18 = *p;
    *p = (s32)obj;
}

// NEAR: retail is library code (0x1F59C4 onward, Sony's 2.9-ee-991111) and saves $ra with sd, 8 bytes; the default compiler saves it with sq, 16 bytes. The body matches.

struct Obj_1FEEC8 { u8 pad[0x14]; s32 count; };
struct Slot_1FEEC8 { Obj_1FEEC8* obj; };


s32 func_001FEEC8(void)
{
    Obj_1FEEC8* obj = ((Slot_1FEEC8*)func_001FDA10())->obj;
    s32 result = 0;
    if (obj != 0) {
        result = obj->count == 0;
    }
    return result;
}

// NEAR: ra is saved with sq/lq, retail sd/ld (Sony 2.9-ee-991111 lib build); body otherwise EXACT

struct Obj_001FEF00;

struct Vtbl_001FEF00 {
    void* slot0;
    void* (*slot1)(Obj_001FEF00* self);
};

struct Obj_001FEF00 {
    Vtbl_001FEF00* vtbl;
};

s32 func_001FEF00(Obj_001FEF00* self)
{
    return *(s32*)self->vtbl->slot1(self);
}

// NEAR: only the $ra and $s0 saves differ: retail sd/ld, ours sq/lq

extern u8 D_0062C5A8[];
extern const char D_0024F0F0[16];
extern u8 D_0027B318[];

struct Node_1FEF70 {
    void *field0;
};

void func_00200118(struct Node_1FEF70 *self, void *a1, void *a2);

void* func_001FF008(void);
void* func_001FEF70(void) {
    struct Node_1FEF70 *node = (struct Node_1FEF70 *)D_0062C5A8;
    if (node->field0 == 0) {
        func_001FF008();
        func_00200118(node, (void*)D_0024F0F0, D_0027B318);
    }
    return node;
}

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern u8 D_0027B318[];
extern const char D_0024F100[16];

struct Node_1FF008 {
    void *field0;
    void *vtbl;
};

void func_00200138(struct Node_1FF008 *self, void *value);

void *func_001FF008(void) {
    struct Node_1FF008 *node = (struct Node_1FF008 *)D_0027B318;
    if (*(void **)D_0027B318 == 0) {
        func_00200138(node, (void*)D_0024F100);
    }
    return node;
}

s32 func_0018D750(void);

s32 func_001FE9F8(void)
{
    return func_0018D750();
}

struct Obj_001FEF28 { u8* f0; };

s32 func_0018D778(Obj_001FEF28* self);
extern u8 D_0024F0D8[];

u8* func_001FEF28(Obj_001FEF28* self, s32 flag)
{
    u8* value = D_0024F0D8;
    self->f0 = value;
    if (flag & 1) {
        return (u8*)func_0018D778(self);
    }
    return value;
}

extern u8 D_0024F0D8[];

s32 func_0018D778(void* self);

s32 func_001FEFC0(void* self, s32 flags)
{
    void* v = D_0024F0D8;
    *(void**)self = v;
    if (flags & 1) {
        return func_0018D778(self);
    }
    return (s32)v;
}

// NEAR: retail saves with sd/ld (ours sq/lq); jalr's delay slot is a nop in retail, ours moves a0 there

struct Node_001FEA18 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
    u8 pad1[0x18];
    s32 f28;
};

struct Hdr_001FEA18 {
    u8 pad0[4];
    s16 kind;
};

struct Res_001FEA18;

typedef s32 (*Fn_001FEA18)();

s32 func_00200778(Res_001FEA18* a, s32 b, s32 c);

s32 func_001FEA18(Node_001FEA18* self, void* fn, Hdr_001FEA18* a2)
{
    if (a2 != 0 && a2->kind != 4) {
        return 0;
    }
    if (fn == (void*)-1) {
        return self->f8;
    }
    s32 r = ((Fn_001FEA18)fn)();
    r = func_00200778((Res_001FEA18*)r, self->fC, self->f28);
    if (r != 0) {
        self->f8 = r;
    }
    return r;
}

struct Node_1FEBE0 { u8 pad[0x14]; s32 flag; };
struct Head_1FEBE0 { Node_1FEBE0* node; };

extern void func_001FE8F0(void) __attribute__((noreturn));

void func_001FEBE0(void)
{
    Node_1FEBE0* n = ((Head_1FEBE0*)func_001FDA10())->node;
    if (n == 0)
        func_001FE8F0();
    n->flag = 0;
}

struct Chain_1FF448 { s32 next; s32 a; s32 b; };
s32 func_001FF448(Chain_1FF448* p)
{
    s32 n = 0;
    s32 off = p->next;
    s32 nx;
    if (off != 0) {
        goto body;
        for (;;) {
            off = nx;
        body:
            if (p->a != 0 && p->b != 0) n++;
            p = (Chain_1FF448*)((u8*)p + off + 4);
            nx = p->next;
            if (nx == 0) break;
        }
    }
    return n;
}

// EXACT: func_001FF1E0 takes (acc, count) so count lives in s4; f0 stored before f4.

struct Obj_1FF518 { s32 f0; s32 f4; s32 f8; s32* f0C; s32 f10; };
struct Acc_1FF518 { s32* items; s32 count; s32* other; s32 unused; u32 lo; s32 hi; };
struct Cur_1FF518 { s32 pad[1]; };

s32 func_001FF448(Cur_1FF518* cur);
void func_001FF490(Cur_1FF518* cur, Acc_1FF518* list, u32* lo, s32* hi);
s32 func_001FF1E0(Acc_1FF518* acc, s32 n);
void* func_0018D740(s32 size);

void func_001FF518(Obj_1FF518* self)
{
    s32 count;
    s32* p;
    Acc_1FF518 acc;

    if (self->f0C != 0) {
        p = self->f0C;
        count = 0;
        if (*p != 0) {
            do {
                count += func_001FF448((Cur_1FF518*)*p);
                p++;
            } while (*p != 0);
        }
    } else {
        count = func_001FF448((Cur_1FF518*)self->f8);
    }
    self->f10 = count;
    acc.items = (s32*)func_0018D740(count << 2);
    acc.other = (s32*)func_0018D740(count << 2);
    acc.lo = 0xFFFFFFFF;
    acc.count = 0;
    acc.unused = 0;
    acc.hi = 0;
    if (self->f0C != 0) {
        p = self->f0C;
        if (*p != 0) {
            do {
                func_001FF490((Cur_1FF518*)*p, &acc, &acc.lo, &acc.hi);
                p++;
            } while (*p != 0);
        }
    } else {
        func_001FF490((Cur_1FF518*)self->f8, &acc, &acc.lo, &acc.hi);
    }
    self->f0C = (s32*)func_001FF1E0(&acc, count);
    self->f0 = acc.lo;
    self->f4 = acc.hi;
}

struct Cie_1FF740;

struct Fde_1FF740 {
    s32 length;
    s32 cieOffset;
    Cie_1FF740* Cie()
    {
        return (Cie_1FF740*)((char*)&cieOffset - cieOffset);
    }
};

struct Cie_1FF740 {
    s32 length;
    s32 id;
    s8 version;
    char augmentation[1];
};

struct __attribute__((packed)) Unaligned_1FF740 {
    s32 v;
};

struct Info_1FF740 {
    char *augmentation;
    s32 ehPtr;
    s32 codeAlign;
    s32 dataAlign;
    s32 raReg;
};

s32 func_001F6738(const char *a, const char *b);
s32 func_001E2100(const char *s);
u8 *func_001FF048(u8 *p, s32 *out);
u8 *func_001FF090(u8 *p, s32 *out);

u8 *func_001FF740(struct Fde_1FF740 *fde, struct Info_1FF740 *info) {
    struct Cie_1FF740 *cie = fde->Cie();
    u8 *p;
    s32 len;

    info->augmentation = cie->augmentation;
    if (func_001F6738(cie->augmentation, "") != 0 &&
        func_001F6738(info->augmentation, "eh") != 0 &&
        info->augmentation[0] != 'z') {
        return 0;
    }
    p = (u8 *)info->augmentation + GetStringLength(info->augmentation) + 1;
    if (func_001F6738(info->augmentation, "eh") == 0) {
        info->ehPtr = ((struct Unaligned_1FF740 *)p)->v;
        p += 4;
    } else {
        info->ehPtr = 0;
    }
    p = func_001FF048(p, &info->codeAlign);
    p = func_001FF090(p, &info->dataAlign);
    info->raReg = *p++;
    if (info->augmentation[0] == 'z') {
        p = func_001FF048(p, &len);
        p += len;
    }
    return p;
}

struct RuleSet_1FF848 {
    u8 pad0[8];
    s64 cfaOffset;
    s64 cfaReg;
    s64 value[0x50];
    u16 retColumn;
    u8 pad29A[2];
    u8 how[0x54];
    struct RuleSet_1FF848 *saved;
    u8 pad2F4[4];
};

struct Cie_1FF848 {
    u8 pad0[8];
    s32 codeAlign;
    s32 dataAlign;
};

struct __attribute__((packed)) U16_1FF848 {
    u16 v;
};

struct __attribute__((packed)) U32_1FF848 {
    u32 v;
};

u8 *func_001FF048(u8 *p, u32 *out);
void func_002014D0(void);
struct RuleSet_1FF848 *func_0018D740(u32 size);
void func_0018D750(struct RuleSet_1FF848 *p);

u8 *func_001FF848(u8 *p, struct RuleSet_1FF848 *rs, struct Cie_1FF848 *cie, u32 *pc) {
    s32 offset;
    u32 reg;
    u32 reg2;
    u8 op = *p++;

    if (op & 0x40) {
        *pc += (op & 0x3F) * cie->codeAlign;
    } else if (op & 0x80) {
        reg = op & 0x3F;
        p = func_001FF048(p, (u32 *)&offset);
        offset *= cie->dataAlign;
        rs->how[reg] = 1;
        rs->value[reg] = offset;
    } else if (op & 0xC0) {
        reg = op & 0x3F;
        rs->how[reg] = 0;
    } else {
        switch (op) {
        case 0:
            break;
        case 1:
            *pc = ((struct U32_1FF848 *)p)->v;
            p += 4;
            break;
        case 2:
            *pc += *p;
            p += 1;
            break;
        case 3:
            *pc += ((struct U16_1FF848 *)p)->v;
            p += 2;
            break;
        case 4:
            *pc += ((struct U32_1FF848 *)p)->v;
            p += 4;
            break;
        case 5:
            p = func_001FF048(p, &reg);
            p = func_001FF048(p, (u32 *)&offset);
            offset *= cie->dataAlign;
            rs->how[reg] = 1;
            rs->value[reg] = offset;
            break;
        case 6:
            p = func_001FF048(p, &reg);
            rs->how[reg] = 0;
            break;
        case 7:
        case 8:
            break;
        case 9:
            p = func_001FF048(p, &reg);
            p = func_001FF048(p, &reg2);
            rs->how[reg] = 2;
            rs->value[reg] = reg2;
            break;
        case 12:
            p = func_001FF048(p, &reg);
            p = func_001FF048(p, (u32 *)&offset);
            rs->retColumn = reg;
            rs->cfaOffset = offset;
            break;
        case 13:
            p = func_001FF048(p, &reg);
            rs->retColumn = reg;
            break;
        case 14:
            p = func_001FF048(p, (u32 *)&offset);
            rs->cfaOffset = offset;
            break;
        case 10: {
            struct RuleSet_1FF848 *copy = func_0018D740(sizeof(struct RuleSet_1FF848));
            *copy = *rs;
            rs->saved = copy;
            break;
        }
        case 11: {
            struct RuleSet_1FF848 *copy = rs->saved;
            *rs = *copy;
            func_0018D750(copy);
            break;
        }
        case 45:
            for (reg = 16; reg < 32; reg++) {
                rs->how[reg] = 1;
                rs->value[reg] = (reg - 16) * 4;
            }
            break;
        case 46:
            p = func_001FF048(p, (u32 *)&offset);
            rs->cfaReg = offset;
            break;
        default:
            func_002014D0();
            break;
        }
    }
    return p;
}

void func_002014D0(void) __attribute__((noreturn));

struct Info_001FEC10 {
    u8 pad[8];
    void* value;
    void* type;
};

extern void func_001FE938() __attribute__((noreturn));

// The runtime's exceptions: a base class with a description, and the classes thrown below.
class Error_1FEC10 {
public:
    Error_1FEC10() {}
    virtual ~Error_1FEC10() {}
    virtual const char* Describe() const;
};

class Unlisted_1FEC10 : public Error_1FEC10 {
public:
    Unlisted_1FEC10() {}
    virtual ~Unlisted_1FEC10() {}
};

class Fault_1FEDC8 : public Error_1FEC10 {
public:
    Fault_1FEDC8() {}
    virtual ~Fault_1FEDC8() {}
};

class Fault_1FEE48 : public Error_1FEC10 {
public:
    Fault_1FEE48() {}
    virtual ~Fault_1FEE48() {}
};

void func_001FEC10(s32 count, void** allowed)
{
    Info_001FEC10* info = *(Info_001FEC10**)func_001FDA10();
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_00200778((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
            throw;
        }
    }
    try {
        func_001FE938();
    } catch (...) {
        if (info != (Info_001FEC10*)__exception_info) {
            info = (Info_001FEC10*)__exception_info;
            for (i = 0; i < count; i++) {
                if (func_00200778((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
                    throw;
                }
            }
        }
        void* type = func_001FEF70();
        for (i = 0; i < count; i++) {
            if (func_00200778((Res_001FEA18*)allowed[i], (s32)type, (s32)info->value)) {
                throw Unlisted_1FEC10();
            }
        }
        func_001FE8F0();
    }
}

void func_001FEDC8()
{
    throw Fault_1FEDC8();
}

void func_001FEE48()
{
    throw Fault_1FEE48();
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
extern const Fn_Table D_0024F0C0[6] = { 0, (Fn_Table)func_001FEF70, 0, (Fn_Table)func_001FEF28, 0, (Fn_Table)func_001FEF00 };

typedef void (*Handler_001FE8F0)(void) __attribute__((noreturn));

void func_001FE8F0(void) __attribute__((noreturn));

void func_001FE8F0(void)
{
	((Handler_001FE8F0)D_00278048)();
}

void func_001FE908(void) __attribute__((noreturn));

void func_001FE908(void)
{
	func_001FE8F0();
}

Handler_001FE8F0 func_001FE918(Handler_001FE8F0 handler)
{
	Handler_001FE8F0 old = (Handler_001FE8F0)D_00278048;
	D_00278048 = (void (*)())handler;
	return old;
}

typedef void (*Handler_001FE938)(void) __attribute__((noreturn));

void func_001FE938(void) __attribute__((noreturn));

void func_001FE938(void)
{
	((Handler_001FE938)D_00278640)();
}

s32 func_001FE950(void)
{
	return *(s32*)func_001FDA10() + 8;
}

struct Arg_1FE9D0;
s32 func_0018D740(Arg_1FE9D0* size);
extern void func_001FE8F0(void) __attribute__((noreturn));

s32 func_001FE9D0(Arg_1FE9D0* size)
{
    s32 p = func_0018D740(size);
    if (p == 0)
        func_001FE8F0();
    return p;
}

// The exception an allocation failure throws (its typeinfo function is func_00200000).
class Fault_1FD8A8 {
public:
    virtual ~Fault_1FD8A8();
};

struct Arg_001FD8A8;

void* func_0018D758(Arg_001FD8A8* q);

void* func_001FD8A8(Arg_001FD8A8* a) throw(Fault_1FD8A8)
{
    return func_0018D758(a);
}


struct Handle_1FEB18 {
    u8 pad_00[0x8];
    void* object;
    void* data;
    void (*callback)(void*, s32);
    s32 state;
    Handle_1FEB18* next;
    u8 pad_1C[4];
    s64 refs;
    void* buf;
};

extern void func_001FE8F0(void) __attribute__((noreturn));
s32 func_001FE9F8(void*);
s32 func_00200C40(void*);

void func_001FEB18(Handle_1FEB18* self)
{
    Handle_1FEB18** link = (Handle_1FEB18**)func_001FDA10();
    if (--self->refs != 0) {
        return;
    }
    if (self == *link && self->state == 0) {
        return;
    }
    for (; *link != 0; link = &(*link)->next) {
        if (*link == self) {
            break;
        }
    }
    if (*link == 0) {
        func_001FE8F0();
    }
    *link = self->next;
    if (self->callback != 0) {
        self->callback(self->object, 2);
    }
    if (func_00200C40(self->data) == 0) {
        func_001FE9F8(self->buf);
    }
    func_001FE9F8(self);
}

struct Elem_001FF0E0 { s32 a; s32 b; s32 key; };
struct Arr_001FF0E0 { Elem_001FF0E0** data; s32 count; };

void func_001FF0E0(Arr_001FF0E0* self, Arr_001FF0E0* other)
{
    s32 j = other->count;
    if (j != 0) {
        s32 n1 = self->count;
        s32 i = n1;
        do {
            Elem_001FF0E0* x = other->data[--j];
            if (i != 0 && self->data[i - 1]->key - x->key > 0) {
                do {
                    self->data[i + j] = self->data[i - 1];
                    i--;
                } while (i != 0 && self->data[i - 1]->key - x->key > 0);
            }
            self->data[i + j] = x;
        } while (j != 0);
        self->count = n1 + other->count;
    }
}

struct Node_1FFE58 { s32 a; s32 b; s32 key; };
struct List_1FFE58 { Node_1FFE58** data; u32 count; };

void func_001FFE58(List_1FFE58* self, List_1FFE58* out)
{
    u32 n = self->count;
    u32 next[n];
    u32 head = 0xFFFFFFFFu;
    u32 i;
    u32 cur;
    for (i = 0; i < n; i++) {
        for (cur = head; cur != 0xFFFFFFFFu; cur = next[cur]) {
            if (self->data[i]->key - self->data[cur]->key >= 0) break;
            out->data[out->count++] = self->data[cur];
            self->data[cur] = 0;
        }
        head = i;
        next[i] = cur;
    }
    cur = 0;
    for (i = 0; i < n; i++) {
        Node_1FFE58* x = self->data[i];
        if (x != 0) {
            self->data[cur++] = x;
        }
    }
    self->count = cur;
}

// Globals defined from C.
s32 D_00278640 = (s32)func_001FE908;
extern const char D_0024F0F0[16] = "13bad_exception";
extern const char D_0024F100[16] = "9exception";
extern const Bad_24F1E0 D_0024F1E0 = { "bad_alloc", { { 0, func_00200000 }, { 0, func_00200050 }, { 0, (void(*)())func_001FFFF0 } } };
