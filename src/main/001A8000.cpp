// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_00182ED0(void* self);
void func_001A93C8(void* self);

void func_001A80E0(void* self)
{
    func_00182ED0(self);
    func_001A93C8(self);
}

void func_001F3C08(void* a, f32* out);
void func_00128150(int a, int b, void* c, f32* d);
f32 func_00205778(f32 x, f32 y);

void func_001A97C8(u8* self, f32* out, int x)
{
    f32 v[12];
    if (*(void**)(self + 0x10) != 0) {
        func_001F3C08(*(void**)(self + 0x10), v);
        func_00128150(0, x, v, v);
        *out = func_00205778(v[1], v[0]);
    } else if (*(u8**)(self + 0x14) != 0) {
        func_00128150(0, x, *(u8**)(self + 0x14) + 0x110, v);
        *out = func_00205778(v[1], v[0]);
    } else {
        *out = *(f32*)(self + 0x8);
    }
}

void func_001C7CB8(void* self);
void func_0012E760(void* obj);

void func_001A9A40(void* self)
{
    u8* s = (u8*)self;
    func_001C7CB8(self);
    void* p = *(void**)(s + 0xC20);
    if (p != 0) {
        if (*(f32*)((u8*)p + 0x18) == 0.0f) {
            func_0012E760(p);
            *(void**)(s + 0xC20) = 0;
        }
    }
}

struct Obj_1AA788 { u8 pad[0x20C]; f32 value; };

void func_001AA788(Obj_1AA788* self, f32 v)
{
    self->value = v;
}

struct Obj_1AA8B8 { u8 pad[0x244]; f32 value; };

void func_001AA8B8(Obj_1AA8B8* self, f32 v)
{
    self->value = v;
}

extern f32 D_0026185C;
extern f32 D_00261860;

typedef void (*VFn_1AB660)(void* self);

void func_001AA298(void* self);
void func_001AB980(void* self, f32 value);

struct Obj_1AB660 {
    VFn_1AB660* vtbl;
    u8 pad[0x250 - 4];
    s32 mode;
    u8 pad2[0x260 - 0x254];
    s32 flag;
    f32 timer;
    u8 pad3[0x290 - 0x268];
    s32 extra;
};

void func_001AB660(Obj_1AB660* self)
{
    func_001AA298(self);
    if (self->mode == 0) {
        return;
    }
    if (self->flag == 0) {
        s32 close = (1.0f <= D_0026185C - self->timer);
        if ((u32)(self->mode - 1) < 2) {
            if (self->extra != 0 || close) {
                self->vtbl[15](self);
            }
        }
    } else {
        func_001AB980(self, D_00261860);
    }
}

extern f32 D_0026185C;

struct Obj_1ABE20 { u8 pad[0x260]; s32 state; f32 timer; };

void func_001ABE20(Obj_1ABE20* self, s32 state)
{
    if (self->state != state) {
        self->state = state;
        self->timer = D_0026185C;
    }
}

struct Obj_1AA268 {
    u8 pad0[4];
    s32 f4;
    u8 f8;
    u8 pad9[0x208 - 9];
    u32 f208;
    f32 f20c;
};

extern s32 D_0026227C;

void func_001AA268(Obj_1AA268* self)
{
    s32 value = D_0026227C;
    u32 flags = 0xFF808080;
    self->f4 = value;
    self->f20c = 1.0f;
    self->f208 = flags;
    self->f8 = 0;
}

struct Obj_1AA790 {
    u8 pad0[4];
    s32 f4;
    s8 f8;
    u8 pad9[0x208 - 9];
    s32 f208;
    f32 f20c;
    void* f210;
    u8 pad214[0x21C - 0x214];
    f32 f21c;
    f32 f220;
    u8 pad224[0x234 - 0x224];
    f32 f234;
    f32 f238;
};

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);

extern u8 D_00262280[];

void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);
void func_0015C8B8(s32 a, f32 x, f32 y);
void func_0015C638(s32 a, void* b, void* c, s32 d, void* e);
void func_0015C900(s32 v);

void func_001AA790(Obj_1AA790* self)
{
    u8 out[32];
    s32 tmp;
    void* handle;
    f32 x;

    if (self->f8 != 0) {
        f32 p = self->f234;
        f32 q = self->f238;
        s32 held = self->f208;
        func_00137228(out, self->f21c, self->f220);
        func_00137238(out, p, q);
        tmp = held;
        func_00137248(out, &tmp);
        func_00137260(out, 0);
        func_00137268(out, 0);

        handle = self->f210;
        if (handle != 0) {
            void* obj = *(void**)handle;
            if (obj != 0) {
                void* vt = *(void**)((u8*)obj + 76);
                VirtualCall_1AA790 fn = *(VirtualCall_1AA790*)((u8*)vt + 76);
                s16 adj = *(s16*)((u8*)vt + 72);
                fn((u8*)obj + adj, handle, out, D_00262280);
            }
        }
        x = self->f20c;
        func_0015C8B8(self->f4, x, x);
        func_0015C638(self->f4, &self->f8, out, 0, D_00262280);
        func_0015C900(self->f4);
    }
}

struct Obj_1AA898 {
    u8 pad[576];
    f32 value;
};

f32 func_001AA898(Obj_1AA898* self)
{
    return self->value;
}

struct Obj_1AA8A0 {
    u8 pad[580];
    f32 value;
};

f32 func_001AA8A0(Obj_1AA8A0* self)
{
    return self->value;
}

struct Obj_1AA8A8 {
    u8 pad[584];
    f32 value;
};

f32 func_001AA8A8(Obj_1AA8A8* self)
{
    return self->value;
}

struct Node_1A98F8 { u8 pad0[0x14]; void* sub; };

void func_001C72A0(Node_1A98F8* self);
void func_001DDC38(void* sub, Node_1A98F8* self);

void func_001A98F8(Node_1A98F8* self)
{
    func_001C72A0(self);
    func_001DDC38(self->sub, self);
}

struct Node_1A9928 { u8 pad0[0x14]; void* sub; u8 pad1[0xC24 - 0x18]; s32 field_C24; };

s32 func_001DDA80(void* sub);

s32 func_001A9928(Node_1A9928* self)
{
    if (func_001DDA80(self->sub) != 0)
        return 0;
    return self->field_C24;
}

typedef void* (*VFn_1A9960)(void* self);
struct Obj_1A9960 { VFn_1A9960* vtbl; u8 pad0[0x724 - 4]; s32 state724; };

void func_001C8C08(Obj_1A9960* self);
void func_001C8418(Obj_1A9960* self, void* p);

void func_001A9960(Obj_1A9960* self)
{
    func_001C8C08(self);
    if (self->state724 == 0x10) {
        void* r = self->vtbl[102](self);
        if (r != 0)
            func_001C8418(self, (u8*)r + 0x140);
    }
}

struct Obj_1A99B8 { u8 pad0[0x724]; s32 state724; };

void func_001C8E28(Obj_1A99B8* self);
void func_001C8BC0(Obj_1A99B8* self);

void func_001A99B8(Obj_1A99B8* self)
{
    func_001C8E28(self);
    if (self->state724 == 0x10)
        func_001C8BC0(self);
}

struct Flag_1AB958 { u8 pad[0x290]; s32 value; };

void func_001ABE20(void* self, s32 v);

void func_001AB958(Flag_1AB958* self)
{
    self->value = 1;
    func_001ABE20(self, 0);
}

f32 func_001ABE40(void)
{
    return 0.0f;
}

f32 func_001ABE50(void)
{
    return 0.0f;
}

f32 func_001ABE60(void)
{
    return 0.0f;
}

struct Obj_1A99F8 { u8 pad[0x724]; s32 state; };

extern u8 D_00264A40[];

void func_001C91C8(Obj_1A99F8* self);
void func_001603E8(s32 n);
void func_0018C7F8(u8* p);

void func_001A99F8(Obj_1A99F8* self)
{
    func_001C91C8(self);
    if (self->state == 0xB) {
        func_001603E8(4);
        func_0018C7F8(D_00264A40);
    }
}

typedef void (*VFn_1A9A98)(void* self);
struct Obj_1A9A98 { VFn_1A9A98* vtbl; };

extern Obj_1A9A98 D_0026E248;

s32 func_001E9970(void);

void func_001A9A98(void)
{
    if (func_001E9970()) {
        D_0026E248.vtbl[14](&D_0026E248);
    } else {
        D_0026E248.vtbl[15](&D_0026E248);
    }
}

struct Obj_1A9C58 { u8 pad[0xC14]; s32 f14; s32 f18; s32 f1C; };

void func_001A9C58(Obj_1A9C58* self, s32 a, s32 b, s32 c)
{
    self->f14 = a;
    self->f18 = b;
    self->f1C = c;
}

struct Obj_1AA1F0 {
    u8 pad0[0x214];
    s32 index;
    u8* entry218;
    f32 f21C;
    f32 f220;
    u8 pad1[8];
    f32 f22C;
    f32 f230;
    f32 f234;
    f32 f238;
    u8 pad4[4];
    f32 f240;
    u8 pad2[4];
    f32 f248;
    u8 pad3[12];
    u8* table258;
};

extern u8 D_0026C3E0[];
extern u8 D_00261868[];

void func_001AAB20(Obj_1AA1F0* self, f32 x, f32 y);

void func_001AA1F0(Obj_1AA1F0* self, s32 index)
{
    self->entry218 = D_0026C3E0 + index * 20;
    self->f248 = 0.25f;
    self->f240 = 0.25f;
    self->table258 = D_00261868;
    self->index = index;
    func_001AAB20(self, self->f234, self->f238);
    self->f21C = self->f22C;
    self->f220 = self->f230;
}

void* func_0018D5C0(u32 n);

struct Owner_1A8110 {
    u8 pad[0x3C];
    void* sub;
};

void* func_001A8110(Owner_1A8110* self)
{
    if (self->sub == 0) {
        void* p = func_0018D5C0(0x20);
        self->sub = p;
        *(Owner_1A8110**)p = self;
    }
    return self->sub;
}

struct Obj_1AA8B0 { u8 pad[0x240]; f32 value; };

void func_001AA8B0(Obj_1AA8B0* self, f32 v)
{
    self->value = v;
}

struct Obj_1AA8C0 { u8 pad[0x248]; f32 value; };

void func_001AA8C0(Obj_1AA8C0* self, f32 v)
{
    self->value = v;
}

struct Obj_1A8590 { u8 pad0[0x14]; void* f14; u8 pad1[0x34]; s32 f4C; s32 f50; s32 f54; s32 f58; void* f5C; void* f60; void* f64; void* f68; u8 pad2[0x74]; void* fE0; void* fE4; u8 pad3[0x78]; void* f160; void* f164; s32 f168; };

void func_00182C58(void* self);
void* func_0015A448(void* obj, s32 id, void* owner);
s32 func_001300E8(void* node, s32 kind);

void func_001A8590(Obj_1A8590* self)
{
    func_00182C58(self);
    if (self->f168 != 0) {
        return;
    }
    self->f168 = 1;
    if (self->f4C != -1) {
        void* p = func_0015A448(self->f14, self->f4C, self);
        if (p != 0) {
            if (func_001300E8(p, 0x7E) != 0) {
                self->f60 = p;
            } else if (func_001300E8(p, 0x73) != 0) {
                self->f64 = p;
            } else if (func_001300E8(p, 2) != 0) {
                self->f68 = p;
            }
        }
    }
    if (self->f50 != -1) {
        void* p = func_0015A448(self->f14, self->f50, self);
        if (p != 0) {
            if (func_001300E8(p, 2) != 0) {
                self->fE0 = p;
            } else if (func_001300E8(p, 0x75) != 0) {
                self->fE4 = p;
            }
        }
    }
    if (self->f54 != -1) {
        void* p = func_0015A448(self->f14, self->f54, self);
        if (p != 0) {
            if (func_001300E8(p, 0x73) != 0) {
                self->f160 = p;
            } else if (func_001300E8(p, 2) != 0) {
                self->f164 = p;
            }
        }
    }
    if (self->f58 != -1) {
        self->f5C = func_0015A448(self->f14, self->f58, self);
    }
}

void func_001F5C0C(void* p, s32 value, s32 size);

struct Tail_001A9438 { s32 a; f32 b; s32 c; };
struct Body_001A9438 { u8 pad0[0x110]; Tail_001A9438 tail; u8 gap[4]; s32 f120; f32 f124; };

void func_001A9438(Body_001A9438* self)
{
    func_001F5C0C((u8*)self + 0xE0, 0, 0x70);
    Tail_001A9438* t = &self->tail;
    t->a = 0;
    t->b = 1.0f;
    t->c = 0;
    self->f124 = 20000.0f;
    self->f120 = 0;
}

void func_001F5C0C(void* p, s32 value, s32 size);

void func_001A9498(u8* self)
{
    func_001F5C0C(self + 0x150, 0, 0x18);
}

extern s32 D_00261858;

f32 func_001AB5D8(void)
{
    return D_00261858 != 0 ? 2.5f : 0.0f;
}

void func_001A93C8(void* self);

void func_001A86F8(void* self, s32 flag)
{
    if (flag) {
        func_001A93C8(self);
    }
}

struct Entry_1A8718 { s32 key; s32 pad[3]; s32 flags; };
struct Table_1A8718 { u8 pad[0x34]; s32 count; Entry_1A8718* entries; };

Entry_1A8718* func_001A8718(Table_1A8718* table, s32 key);

void func_001A8778(Table_1A8718* table, s32 key)
{
    Entry_1A8718* e = func_001A8718(table, key);
    if (e) {
        e->flags |= 2;
    }
}

typedef void (*VFn_1AA8C8)(void* self, s32 arg);
struct Obj_1AA8C8 { VFn_1AA8C8* vtbl; };

void func_001AA8C8(void* self)
{
    Obj_1AA8C8* o = (Obj_1AA8C8*)self;
    o->vtbl[16](self, 0);
}

struct Actor_001AB920 { u8 pad[0x26C]; f32 field_26C; };

void func_001AB920(Actor_001AB920* self, f32 value)
{
    self->field_26C = value;
}

struct Row_1A8820 { s32 unk0; s32 itemCount; void** items; u8 pad[8]; };
struct S_1A8820 { u8 pad[0x34]; s32 count; Row_1A8820* rows; };
struct T_1A8820 { u8 pad[8]; s32 value; };
s32 func_001A8820(S_1A8820* list, T_1A8820* query) { for(s32 i=0;i<list->count;i++){ Row_1A8820* row=(Row_1A8820*)((u8*)list->rows+i*0x14); if(row->itemCount<=0) continue; void** items=row->items; if(*(s32*)((u8*)items[0]+8) != query->value) continue; for(s32 j=0;j<row->itemCount;j++) if(query==items[j]) return 1; } return 0; }

struct S_1A93C8 { u8 pad0[0x3C]; s32 ptr; u8 pad1[8]; s32 field; };
void func_001A93C8(S_1A93C8* p) { p->field = 0; if (p->ptr != 0 && *(s32*)((u8*)p->ptr + 4) != 0) *(s32*)((u8*)p->ptr + 0x10) = 0; }

struct Entry_1A87E0 { s32 pad0; s32 f4; s32 pad1; s32 fC; };

Entry_1A87E0* func_001A8718(void* table, s32 key);

void func_001A87E0(void* table, s32 key, s32 value)
{
    Entry_1A87E0* e = func_001A8718(table, key);
    if (e != 0) {
        if (value >= e->fC) {
            value = e->fC;
        }
        e->f4 = value;
    }
}

struct __attribute__((aligned(16))) Quad_1A94C0 { s32 a, b, c, d; };
struct Inner_1A94C0 {
    u8 pad0[0x110];
    Quad_1A94C0 q110;
    Quad_1A94C0 q120;
    Quad_1A94C0 q130;
    Quad_1A94C0 q140;
};
struct Obj_1A94C0 {
    void* f0;
    void* f4;
    Inner_1A94C0* f8;
    u8 pad0[4];
    Quad_1A94C0 q10;
    Quad_1A94C0 q20;
    Quad_1A94C0 q30;
    Quad_1A94C0 q40;
};

void func_001920B0(void* self, void* arg);
void func_001F3BD8(void* self, void* arg);
void func_001F3C08(void* self, void* arg);
void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);

void func_001A94C0(Obj_1A94C0* self, Quad_1A94C0* a1, Quad_1A94C0* a2, void* a3)
{
    if (self->f0 != 0) {
        func_001920B0(self->f0, a1);
        a2[0] = self->q20;
        a2[1] = self->q30;
        a2[2] = self->q40;
    } else if (self->f4 != 0) {
        func_001F3BD8(self->f4, a1);
        func_001F3C08(self->f4, a2);
    } else {
        if (self->f8 != 0) {
            a1[0] = self->f8->q140;
            Inner_1A94C0* in = self->f8;
            a2[0] = in->q110;
            a2[1] = in->q120;
            a2[2] = in->q130;
        } else {
            a1[0] = self->q10;
            a2[0] = self->q20;
            a2[1] = self->q30;
            a2[2] = self->q40;
        }
    }
    if (a3 != 0) {
        func_00128018(0, a3, a1, a1);
        func_00128150(0, a3, a2, a2);
    }
}

void func_001ABE20(void* self, s32 state);

void func_001AB938(void* self)
{
    func_001ABE20(self, 2);
}

extern u8 D_00261868[];

struct Obj_1AAF58 {
    u8 pad0[0x254];
    f32 f254;
    void* f258;
};

void func_001AAF58(Obj_1AAF58* self, f32* p)
{
    if (self->f258 != p) {
        if (p == 0) {
            p = (f32*)D_00261868;
        }
        self->f254 = *p;
    }
    self->f258 = p;
}

struct Obj_1AB928 { u8 pad[0x288]; f32 f288; s32 f28c; };

void func_001AB928(Obj_1AB928* self, s32 v, f32 f)
{
    self->f288 = f;
    self->f28c = v;
}

struct Sub_1A84C8 { u8 pad0[4]; s32 f4; s32 f8; u8 pad1[8]; void* f14; };
struct Obj_1A84C8 { u8 pad0[0x34]; s32 count; void* items; Sub_1A84C8* sub; };

void func_001830D8(Obj_1A84C8* self, void* o);
void* func_001A8110(void* self);
void func_00152438(void* self, s32 value);
void func_00152470(void* list, void* item);
u8* func_0018D568(s32 size, void* src);

void func_001A84C8(Obj_1A84C8* self, Obj_1A84C8* other)
{
    func_001830D8(self, other);
    if (self->sub != 0 && self->sub->f4 != 0) {
        if (other->sub->f8 != 0) {
            self->sub = 0;
        } else {
            other->sub->f8 = 1;
            func_00152438((u8*)other->sub + 0x14, 0x18);
            self->sub = 0;
        }
        func_001A8110(self);
        self->sub->f4 = 1;
        self->sub->f8 = 2;
        self->sub->f14 = other;
        func_00152470((u8*)other->sub + 0x14, self->sub);
    } else {
        self->items = func_0018D568(other->count * 0x14, other->items);
    }
}

// NEAR: frame and body match; the two local slots are swapped (retail: tmp at sp+0x30, buffer at sp+0x40; ours: buffer at sp+0x30, tmp at sp+0xE0), so the frame is 0x120 not 0x130

extern u8 D_0026FF68[];
extern u8 D_00262280[];

struct __attribute__((packed)) Word_1AB198 {
    s32 v;
};

struct Obj_1AB198 {
    u8 pad0[4];
    s32 f4;
    s8 f8;
    u8 pad1[0x208 - 9];
    Word_1AB198 f208;
    u8 pad2[0x20C - 0x20C];
    f32 f20c;
    u8 pad3[0x21C - 0x210];
    f32 f21c;
    f32 f220;
    u8 pad4[0x234 - 0x224];
    f32 f234;
    f32 f238;
};

struct Glob_1AB198 {
    u8 pad0[0x250];
    s32 f250;
    u8 pad1[0x284 - 0x254];
    f32 f284;
};

void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);
void func_0015C8B8(s32 handle, f32 a, f32 b);
void func_0015DB28(void* out, void* p, s32 handle);
void func_0015E318(void* buf, void* out, s32 zero, void* data);
void func_0015C900(s32 handle);

void func_001AB198(Obj_1AB198* self)
{
    u8 out[0x20];
    Word_1AB198 packed;
    s32 held;
    s32 tmp[4];
    u8 buf[0xB0];
    f32 scale;
    f32 px;
    f32 py;
    Glob_1AB198* g;

    if (self->f8 == 0) {
        return;
    }
    g = (Glob_1AB198*)D_0026FF68;
    scale = 1.0f;
    if (g->f250 != 0) {
        scale = g->f284;
    }
    packed = self->f208;
    ((u8*)&packed)[3] = (u8)(s32)(scale * 255.0f);
    held = packed.v;
    px = self->f234;
    py = self->f238;
    func_00137228(out, self->f21c, self->f220);
    func_00137238(out, px, py);
    tmp[0] = held;
    func_00137248(out, &tmp[0]);
    func_00137260(out, 0);
    func_00137268(out, 0);
    func_0015C8B8(self->f4, self->f20c, self->f20c);
    func_0015DB28(buf, &self->f8, self->f4);
    func_0015E318(buf, out, 0, D_00262280);
    func_0015C900(self->f4);
}

typedef void (*VFn_1AA8F0)(void* self, s32 flag);

struct Obj_1AA8F0 {
    VFn_1AA8F0* vtbl;
    u8 pad0[0x250 - 4];
    s32 state;
    f32 f254;
    f32* p258;
};

void func_001AA8F0(Obj_1AA8F0* self)
{
    s32 s = self->state;
    if (s == 2) {
        goto store;
    }
    if (s < 3) {
        if (s == 0) {
            goto call;
        }
        return;
    }
    if (s != 3) {
        return;
    }
call:
    self->vtbl[16](self, 1);
    return;
store:
    self->f254 = *self->p258;
}

extern u8 D_00262280[];

struct __attribute__((packed)) PackedWord_001AB710 { s32 v; };
struct Local_001AB710 { f32 x; f32 y; u8 pad0[0x8]; PackedWord_001AB710 w10; u8 pad1[0xC]; s32 tag; u8 pad2[0xC]; PackedWord_001AB710 w30; };
struct VDesc_001AB710 { u8 pad0[0x48]; s16 off48; u8 pad1[2]; void (*fn4C)(void* self, void* obj, void* out, void* d); };
struct SubObj_001AB710 { u8 pad0[0x4C]; VDesc_001AB710* desc4C; };
struct Actor_001AB710 { u8 pad0[4]; void* p4; s8 f08; u8 pad1[0x1FF]; s32 f208; f32 f20C; void* f210; u8 pad2[8]; f32 f21C; f32 f220; u8 pad3[0x10]; f32 f234; f32 f238; u8 pad4[0x40]; PackedWord_001AB710 w27C; u8 pad5[4]; s32 f284; };

void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, void* p);
void func_00137260(void* out, s32 v);
void func_00137268(void* out, s32 v);
void func_0015C8B8(void* p, f32 x, f32 y);
f32 func_0015C418(void* p, void* name);
void func_0015C638(void* p, void* name, void* out, s32 zero, void* d);
void func_0015C900(void* p);

void func_001AB710(Actor_001AB710* self)
{
    Local_001AB710 L;
    if (self->f08 != 0) {
        f32 f234 = self->f234;
        f32 f238 = self->f238;
        s32 s0v = self->f208;
        func_00137228(&L, self->f21C, self->f220);
        func_00137238(&L, f234, f238);
        L.tag = s0v;
        func_00137248(&L, &L.tag);
        func_00137260(&L, 0);
        func_00137268(&L, 0);
        void* obj = self->f210;
        if (obj != 0) {
            SubObj_001AB710* sub = *(SubObj_001AB710**)obj;
            if (sub != 0) {
                VDesc_001AB710* d = sub->desc4C;
                d->fn4C((u8*)sub + d->off48, obj, &L, D_00262280);
            }
        }
        f32 v = self->f20C;
        u8* dp = D_00262280;
        func_0015C8B8(self->p4, v, v);
        ((u8*)&L.tag)[0] = 0x54;
        ((u8*)&L.tag)[1] = 0;
        func_0015C638(self->p4, &L.tag, &L, 0, dp);
        f32 r = func_0015C418(self->p4, &L.tag);
        f32 a = self->f21C + r;
        L.y = self->f220;
        L.x = a;
        if (self->f284 != 0) {
            L.w30 = self->w27C;
            L.w10 = L.w30;
        }
        func_0015C638(self->p4, (u8*)self + 9, &L, 0, dp);
        func_0015C900(self->p4);
    }
}

typedef void (*VFn_1A9FD0)(void* self);
struct Dyn_1A9FD0 { VFn_1A9FD0* vtbl; };

extern u8 D_002486B0[];
extern u8 D_00262C68[];
extern u8 D_00262C70[];
extern u8 D_00262D38[];
extern u8 D_00275F80[];

void func_001EFD10(void* a, void* b);

void func_001A9FD0(void)
{
    Dyn_1A9FD0** slots = (Dyn_1A9FD0**)D_002486B0;
    for (s32 i = 36; i >= 0; i--) {
        Dyn_1A9FD0* o = slots[i];
        o->vtbl[2](o);
    }
    u8* g = D_00275F80;
    void* b;
    if (*(s32*)D_00262C68 & 4) {
        b = D_00262C70;
    } else {
        b = D_00262D38;
    }
    func_001EFD10(g, b);
}

typedef void (*VFn_1AA0C0)(void* self);
struct Obj_1AA0C0 {
    VFn_1AA0C0* vtbl;
};

extern u8 D_002486B0[];

void func_001AA0C0(void)
{
    Obj_1AA0C0** p = (Obj_1AA0C0**)D_002486B0;
    s32 n = 0x24;
    do {
        n--;
        Obj_1AA0C0* o = *p;
        o->vtbl[5](o);
        p++;
    } while (n >= 0);
}

struct VTable_1A9C68 { void (*fn)(void* self, s32 i); };
struct Obj_1A9C68 { VTable_1A9C68* vt; };

extern u8* D_0026C6C8;
extern u8* D_0026CBC8;
extern u8* D_0026CE48;
extern u8* D_0026D0C8;
extern u8* D_0026D348;
extern u8* D_0026D5C8;
extern u8* D_0026C948;
extern u8* D_0026D848;
extern u8* D_0026DAC8;
extern u8* D_0026DD48;
extern u8* D_0026DFC8;
extern u8* D_0026E4E0;
extern u8* D_0026E760;
extern u8* D_0026E9F8;
extern u8* D_0026EC70;
extern u8* D_0026EED0;
extern u8* D_0026F138;
extern u8* D_0026F5A0;
extern u8* D_0026F808;
extern u8* D_0026FA90;
extern u8* D_0026FD00;
extern u8* D_002701F8;
extern u8* D_00270650;
extern u8* D_00271558;
extern u8* D_00272430;
extern u8* D_002726B0;
extern u8* D_00272930;
extern u8* D_00272B98;
extern u8* D_002721D0;
extern u8* D_00272E08;
extern u8* D_002708E0;
extern u8* D_002739F0;
extern u8* D_00273C50;
extern u8* D_00273EB0;
extern u8* D_00274118;
extern u8 D_00217E30[];
extern u8 D_00217E80[];
extern u8 D_00217ED0[];
extern u8 D_00217F20[];
extern u8 D_00217F70[];
extern u8 D_00217FC0[];
extern u8 D_00218010[];
extern u8 D_00218060[];
extern u8 D_002180B0[];
extern u8 D_00218100[];
extern u8 D_00218150[];
extern u8 D_002181A0[];
extern u8 D_002181F0[];
extern u8 D_00218240[];
extern u8 D_00218290[];
extern u8 D_002182E0[];
extern u8 D_00218330[];
extern u8 D_00218380[];
extern u8 D_002183D0[];
extern u8 D_00218420[];
extern u8 D_00218470[];
extern u8 D_002184C0[];
extern u8 D_00218510[];
extern u8 D_00218560[];
extern u8 D_002185B0[];
extern u8 D_00218600[];
extern u8 D_002186D0[];
extern u8 D_00218720[];
extern u8 D_0021A3F0[];
extern u8 D_0021A440[];
extern u8 D_00220BF0[];
extern u8 D_002210F0[];
extern u8 D_002212E0[];
extern u8 D_00221330[];
extern u8 D_00221380[];
extern u8 D_00275F80[];

void func_001EFCE8(void* p);

void func_001A9C68()
{
    D_0026C6C8 = D_00217E30;
    D_0026C948 = D_00217E80;
    D_0026CBC8 = D_00217ED0;
    D_0026CE48 = D_00217F20;
    D_0026D0C8 = D_00217F70;
    D_0026D348 = D_00217FC0;
    D_0026D5C8 = D_002180B0;
    D_0026D848 = D_00218010;
    D_0026DAC8 = D_00218060;
    D_0026DD48 = D_00218100;
    D_0026DFC8 = D_00218150;
    *(u8**)&D_0026E248 = D_002182E0;
    D_0026E4E0 = D_002181A0;
    D_0026E760 = D_00218510;
    D_0026E9F8 = D_00221380;
    D_0026EC70 = D_00218330;
    D_0026EED0 = D_00218380;
    D_0026F138 = D_002183D0;
    D_0026F5A0 = D_00218420;
    D_0026F808 = D_002210F0;
    D_0026FA90 = D_002212E0;
    D_0026FD00 = D_00221330;
    *(u8**)&D_0026FF68 = D_002186D0;
    D_002701F8 = D_0021A440;
    D_00270650 = D_00220BF0;
    D_002708E0 = D_0021A3F0;
    D_00271558 = D_0021A3F0;
    D_00272430 = D_00218240;
    D_002726B0 = D_00218290;
    D_00272930 = D_00218470;
    D_00272B98 = D_002184C0;
    D_002721D0 = D_00218560;
    D_00272E08 = D_00218720;
    D_002739F0 = D_002185B0;
    D_00273C50 = D_002185B0;
    D_00273EB0 = D_00218600;
    D_00274118 = D_002181F0;
    for (s32 i = 0x24; i >= 0; i--) {
        ((Obj_1A9C68**)D_002486B0)[i]->vt->fn(((Obj_1A9C68**)D_002486B0)[i], i);
    }
    func_001EFCE8(D_00275F80);
}

struct VT_1AA5A0 {
    u8 pad0[0x10];
    s16 adj;
    u8 pad1[2];
    s32 (*fn)(void* self, s32 c);
};

struct In_1AA5A0 {
    u8 pad[0x4C];
    VT_1AA5A0* vt;
    s32 call(s32 c) { return vt->fn((u8*)this + vt->adj, c); }
};

struct Obj_1AA5A0 {
    u8 pad0[4];
    In_1AA5A0* in;
    s8 text[0x200];
};

extern s8 D_00262250[];
extern u8 D_0024E879[];
In_1AA5A0* func_0015C1C0(s32 k);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void func_001E2138(void* dst, void* src);

void func_001AA5A0(Obj_1AA5A0* self)
{
    char buf[0x200];
    s8* s = self->text;
    char* d = buf;
    if (*s != 0) {
        do {
            if (self->in->call(*s) == 0) {
                if (func_0015C1C0(3)->call(*s) != 0) {
                    d += func_001E1FD0(d, "&%c%c&.", D_00262250[3], *s);
                    goto next;
                }
                if (func_0015C1C0(4)->call(*s) != 0) {
                    d += func_001E1FD0(d, "&%c%c&.", D_00262250[4], *s);
                    goto next;
                }
            }
            if (*s == 0x2F) {
                if (D_0024E879[s[1]] & 4) {
                    d += func_001E1FD0(d, "^05~b2a83d/");
                    s++;
                    while (*s != 0 && (D_0024E879[*s] & 4)) {
                        *d = *s;
                        s++;
                        d++;
                    }
                    d += func_001E1FD0(d, "~.^.");
                    s--;
                } else {
                    *d = *(u8*)s;
                    d++;
                }
            } else {
                *d = *(u8*)s;
                d++;
            }
        next:
            s++;
        } while (*s != 0);
    }
    *d = 0;
    func_001E2138(self->text, buf);
}

struct Quad_1A8208 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Hdr_1A8208 { u8 pad0[4]; s32 f4; s32 f8; Quad_1A8208* fC; };
struct Ent_1A8208 { s32 f0; s32 f4; void** f8; s32 fC; s32 f10; };
struct Obj_1A8208;
typedef void (*VFn_1A8208)(Obj_1A8208* self);
typedef void (*VFn2_1A8208)(Obj_1A8208* self, s32 a);
struct Obj_1A8208 {
    VFn_1A8208* vtbl;
    u8 pad4[0x10]; s32 f14; s32 f18;
    u8 pad1C[0x174]; Quad_1A8208 q190; u8 pad1A0[0x30]; Quad_1A8208 q1D0;
};
struct Self_1A8208 {
    u8 pad0[0x14]; void* f14; u8 pad18[0x1C];
    s32 f34; Ent_1A8208* f38; Hdr_1A8208* f3C;
};

void* func_0018D500(s32 size);
Obj_1A8208* func_0015A418(void* a, s32 b, s32 c, Self_1A8208* d);
void func_00152438(void* p, s32 a);
s32 func_001527D8(void* p);
Obj_1A8208* func_00183058(Obj_1A8208* a, s32 b, s32 c);

void func_001A8208(Self_1A8208* self)
{
    s32 i;
    if (self->f3C != 0) {
        if (self->f3C->f4 != 0) {
            self->f3C->fC = (Quad_1A8208*)func_0018D500(self->f34 << 5);
        }
    }
    for (i = 0; i < self->f34; i++) {
        Ent_1A8208* e = &self->f38[i];
        Obj_1A8208* obj = func_0015A418(self->f14, 4, e->f0, self);
        s32 n;
        s32 cnt;
        if (obj == 0) {
            e->f4 = 0;
            continue;
        }
        if (self->f3C != 0 && self->f3C->f4 != 0) {
            s32 x = self->f3C->f8;
            if (x == 1) goto c1;
            if (x < 2) {
                if (x == 0) goto c0;
            } else if (x == 2) {
                n = 0;
                cnt = 0;
            }
            goto done;
        c0:
            self->f3C->f8 = 1;
            func_00152438((u8*)self->f3C + 0x14, 0x18);
        c1: {
                s32 r = func_001527D8((u8*)self->f3C + 0x14);
                s32 lim = r + 1;
                s32 m = e->f4;
                s32 q = lim;
                if (q < m) q = m;
                n = q;
                cnt = n - r - 1;
            }
        } else {
            n = e->f4;
            cnt = n - 1;
        }
    done:
        if (n != 0) e->f8 = (void**)func_0018D500(n << 2);
        e->f8[e->fC++] = obj;
        if (cnt > 0) {
            s32 k = cnt;
            do {
                Obj_1A8208* o2 = func_00183058(obj, obj->f14, obj->f18);
                e->f8[e->fC++] = o2;
                if (o2->vtbl[19] != 0) o2->vtbl[19](o2);
                o2->vtbl[20](o2);
                ((VFn2_1A8208)(o2->vtbl[25]))(o2, 0);
                o2->vtbl[7](o2);
            } while (--k);
        }
        if (obj->vtbl[19] != 0) obj->vtbl[19](obj);
        obj->vtbl[20](obj);
        ((VFn2_1A8208)(obj->vtbl[25]))(obj, 0);
        obj->vtbl[7](obj);
        if (self->f3C != 0 && self->f3C->f4 != 0) {
            Quad_1A8208* d = self->f3C->fC + (i << 1);
            d[0] = obj->q190;
            d[1] = obj->q1D0;
        }
    }
}

struct Obj_1AAAC8 { u8 pad[0x250]; s32 mode; };

s32 func_001AAAC8(Obj_1AAAC8* a, Obj_1AAAC8* b)
{
    s32 r = 0;
    s32 am = a->mode;
    if ((u32)(am - 1) < 2) { if ((u32)(b->mode - 1) < 2) goto yes; }
    if (am == 3) { if (b->mode == 3) goto yes; }
    if (b->mode == 3) { if (am == 2) goto yes; }
    goto done;
yes:
    r = 1;
done:
    return r;
}

struct Tab_1A87A8;
struct Ent_1A87A8 { s32 pad[4]; s32 flags; };

Ent_1A87A8* func_001A8718(Tab_1A87A8* table, s32 key);

void func_001A87A8(Tab_1A87A8* table, s32 key)
{
    Ent_1A87A8* e = func_001A8718(table, key);
    if (e != 0) {
        e->flags &= ~2;
    }
}

struct Obj_001A8C50 {
    u8 pad[0x48];
    s32 count;
};

void func_001A8AF8(Obj_001A8C50* self);

s32 func_001A8C50(Obj_001A8C50* self)
{
    if (self->count != 0) {
        return 1;
    }
    func_001A8AF8(self);
    return self->count != 0;
}

struct Obj_1AA958 {
    void** vtbl;
    u8 pad0[0x250 - 4];
    s32 mode;
};

void func_001AA958(Obj_1AA958* self)
{
    s32 m = self->mode;
    if (m < 3) {
        if (m > 0) {
            ((void (*)(Obj_1AA958*, s32))self->vtbl[16])(self, 3);
        }
    }
}

struct Obj_001AAB20 {
    u8 pad[0x234];
    f32 f234;
    f32 f238;
};

void func_001AAB60(Obj_001AAB20 *self);

void func_001AAB20(Obj_001AAB20 *self, f32 x, f32 y) {
    if (0.0f <= x) {
        self->f234 = x;
    }
    if (0.0f <= y) {
        self->f238 = y;
    }
    func_001AAB60(self);
}

extern u8 D_002483D0[];

struct Obj_1A93E8;
void func_001F5C0C(Obj_1A93E8* p, s32 zero, s32 size);

struct __attribute__((aligned(16))) Tri_1A93E8 {
    s32 w[12];
};

void func_001A93E8(u8* self)
{
    u8* p = self + 0x60;
    func_001F5C0C((Obj_1A93E8*)p, 0, 0x80);
    *(Tri_1A93E8*)(p + 0x20) = *(Tri_1A93E8*)D_002483D0;
}

extern u8 D_002486B0[];

struct Vt_001A9F78 { void* slot0; void (*slot1)(void*); };
struct Obj_001A9F78 { Vt_001A9F78* vt; };

void func_001A9F78(void)
{
    Obj_001A9F78** base = (Obj_001A9F78**)D_002486B0;
    Obj_001A9F78** p = base + 36;
    s32 i = 0x24;
    do {
        i--;
        (*p)->vt->slot1(*p);
        p--;
    } while (i >= 0);
}

extern u8 D_002486B0[];

struct Vt_001AA060 { u8 pad[0x40]; void (*fn)(void*, s32); };
struct Obj_001AA060 { Vt_001AA060* vt; };

void func_001AA060(void)
{
    Obj_001AA060** base = (Obj_001AA060**)D_002486B0;
    Obj_001AA060** p = base + 36;
    s32 i = 0x24;
    do {
        Obj_001AA060* o = *p;
        p--;
        o->vt->fn(o, 0);
        i--;
    } while (i >= 0);
}

struct Obj_1AA110;
typedef void (*Fn_1AA110)(Obj_1AA110* self);
struct VT_1AA110 { u8 pad0[0x28]; Fn_1AA110 fn28; };
struct Obj_1AA110 { VT_1AA110* vt; u8 pad0[0x250 - 4]; s32 f250; };
extern u8 D_002486B0[];
void func_001AA110(void)
{
    s32 n = 0x24;
    Obj_1AA110** p = (Obj_1AA110**)D_002486B0;
    do {
        Obj_1AA110* o = *p;
        p++;
        n--;
        if (o->f250 != 0) {
            Fn_1AA110 fn = o->vt->fn28;
            if (fn != 0) {
                fn(o);
            }
        }
    } while (n >= 0);
}

extern u8 D_0026C3E0[];

struct Entry_001AAEC0 {
    u8 pad0[0xC];
    s32 f0C;
    u8 pad1[4];
};

struct Obj_001AAEC0;

void func_001AAB60(Obj_001AAEC0* self);

void func_001AAEC0(s32 key)
{
    Entry_001AAEC0* e = (Entry_001AAEC0*)D_0026C3E0;
    s32 i;

    for (i = 0; i < 0x25; i++, e++) {
        s32 v = e->f0C;
        if (v != -1) {
            if (((s32*)D_002486B0)[v] == key) {
                func_001AAB60((Obj_001AAEC0*)((s32*)D_002486B0)[i]);
            }
        }
    }
}

struct Self_001AB600 { u8 p0[4]; void* p4; u8 p8[0x270 - 8]; s32 f270; s32 f274; f32 f278; u8 p27C[0x290 - 0x27C]; s32 f290; };

extern f32 D_0024CD48;
void func_001AA268(Self_001AB600* self);
void func_001ABE20(Self_001AB600* self, s32 state);

void func_001AB600(Self_001AB600* self)
{
    func_001AA268(self);
    self->p4 = (void*)func_0015C1C0(2);
    self->f274 = self->f270 = -1;
    self->f278 = D_0024CD48;
    self->f290 = 1;
    func_001ABE20(self, 0);
}

extern f32 D_0024CD4C;

struct Obj_001AB890;
typedef void (*VFn_001AB890)(Obj_001AB890* self);

struct Obj_001AB890 {
    VFn_001AB890* vtbl;
    u8 pad0[0x208 - 4];
    u32 f208;
    u8 pad1[0x268 - 0x20C];
    f32 f268;
    f32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
    u8 pad2[0x280 - 0x27C];
    s32 f280;
    s32 f284;
    s32 f288;
    s32 f28C;
    s32 f290;
};

void func_001ABE20(Obj_001AB890* self, s32 state);
void func_001AB980(Obj_001AB890* self, f32 value);

void func_001AB890(Obj_001AB890* self, f32 x)
{
    self->f280 = 0;
    self->f284 = 0;
    self->f288 = 0;
    self->f28C = 0;
    self->f290 = 0;
    self->f208 = 0xFF808080;
    self->f26C = -1.0f;
    self->f270 = -1;
    self->f274 = -1;
    self->f278 = D_0024CD4C;
    self->f268 = x;
    func_001ABE20(self, 1);
    func_001AB980(self, 0.0f);
    self->vtbl[14](self);
}

// NEAR: (fixed: indexed loop gave EXACT)
// allocator puts the count in $s1 and the pointer in $s0; retail is the other way round.

typedef void (*VFn_001AA178)(void* self);
struct Obj_001AA178 {
    VFn_001AA178* vtbl;
    u8 pad0[0x250 - 4];
    void* f250;
};

extern u8 D_00275F80[];
void func_001EFEE0(u8* a);
void func_001AE820(u8* a);

void func_001AA178(void)
{
    s32 i;
    for (i = 0; i < 0x25; i++) {
        Obj_001AA178* p = ((Obj_001AA178**)D_002486B0)[i];
        if (p->f250 != 0) {
            p->vtbl[9](p);
        }
    }
    func_001EFEE0(D_00275F80);
    func_001AE820((u8*)&D_00273EB0);
}

struct Obj_1AA298;
struct VT_1AA298 {
    u8 p0[0x2C];
    f32 (*f2C)(Obj_1AA298*);
    f32 (*f30)(Obj_1AA298*);
    f32 (*f34)(Obj_1AA298*);
    u8 p38[8];
    void (*f40)(Obj_1AA298*, s32);
};
struct Obj_1AA298 {
    VT_1AA298* vt;
    u8 p4[0x21C - 4];
    f32 f21C, f220, f224, f228, f22C, f230;
    u8 p234[0x23C - 0x234];
    f32 f23C;
    u8 p240[0x24C - 0x240];
    f32 f24C;
    s32 f250;
    f32 f254;
    f32* f258;
};

void func_001AAEC0(Obj_1AA298* self);
extern f32 D_002743A0[];

void func_001AA298(Obj_1AA298* self) {
    f32 t = *self->f258;
    s32 s = self->f250;
    switch (s) {
    case 2: {
        f32 d = self->vt->f30(self);
        if (d != 0.0f) {
            if (d <= t - self->f254) s = 3;
        }
        break; }
    case 1: {
        f32 d = self->vt->f2C(self);
        f32 zero = 0.0f;
        f32 x;
        if (d != zero) {
            f32 one = 1.0f;
            x = (t - self->f254 + self->f24C) / d;
            if (x < zero) x = zero;
            else if (one < x) x = one;
            self->f23C = x;
        }
        if (self->f23C >= 1.0f) s = 2;
        break; }
    case 3: {
        f32 d = self->vt->f34(self);
        f32 zero = 0.0f;
        f32 x;
        if (d != zero) {
            f32 one = 1.0f;
            x = (t - self->f254 + self->f24C) / d;
            f32 y = x < zero ? zero : (one < x ? one : x);
            self->f23C = 1.0f - y;
        }
        if (self->f23C <= 0.0f) s = 0;
        break; }
    }
    if (s == self->f250) {
        f32 p = self->f23C;
        f32 k = D_002743A0[0] + p * (D_002743A0[1] + p * D_002743A0[2]);
        self->f21C = self->f22C + k * (self->f224 - self->f22C);
        self->f220 = self->f230 + k * (self->f228 - self->f230);
        func_001AAEC0(self);
    }
    self->vt->f40(self, s);
}

struct Entry_1A8150 { s32 f0; s32 f4; u8 pad[8]; s32 f10; };
struct Table_1A8150 { u8 pad[0x34]; s32 count; Entry_1A8150* items; };

void* func_0018D5C0(u32 n);

void func_001A8150(Table_1A8150* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->items == 0) {
        self->items = (Entry_1A8150*)func_0018D5C0(0x50);
    }
    Entry_1A8150* e = &self->items[self->count++];
    e->f0 = a1;
    e->f4 = a2;
    e->f10 = ((((e->f10 & -2) | (a3 & 1)) & -3) | ((a4 & 1) << 1));
}

struct Obj_1AAF88 {
    u8 pad000[4];
    u32 f004;
    u8 pad008[0x20C];
    s32 f214;
    u8 pad218[0x48];
    s32 f260;
    void* f264;
    void* f268;
    f32 f26C;
};

extern u8* D_002623C0;
extern u8* D_002623C4;
extern u8* D_002623C8;
extern u8* D_00275710;

void func_001AA268(Obj_1AAF88* self);

void func_001AAF88(Obj_1AAF88* self)
{
    func_001AA268(self);
    self->f004 = (u32)func_0015C1C0(2);
    self->f260 = -1;
    self->f26C = 6000.0f;
    switch (self->f214) {
    case 3:
        self->f264 = D_002623C0 + 0x19E0;
        break;
    case 4:
        self->f264 = D_002623C8 + 0x64;
        self->f268 = D_00275710 + 0x2300;
        break;
    case 5:
        self->f264 = D_002623C4 + 0x438;
        break;
    case 6:
        self->f264 = D_002623C0 + 0x19E8;
        break;
    case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 28: case 29:
    case 36:
        self->f264 = &self->f260;
        break;
    }
}
