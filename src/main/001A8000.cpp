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
