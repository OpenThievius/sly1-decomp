// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// The five pools values are taken from (func_0011C240): func_0011BF70 sets them up, func_0011C040
// empties them all. Built at startup: the compiler's initialiser, constructor and destructor for this
// file are func_0011C0A8, func_0011C0E8 and func_0011C108 (config/us/generated.tsv).
struct Pool_25C250 {
    u8 pad0[0x18];
    void* callback;  // set by func_0011BF70
    s32 pad1C;
    Pool_25C250() { callback = 0; }
    ~Pool_25C250() {}
};
Pool_25C250 D_0025C250;
Pool_25C250 D_0025C270;
Pool_25C250 D_0025C290;
Pool_25C250 D_0025C2B0;
Pool_25C250 D_0025C2D0;

void* func_0011B008(void* self);

void func_0011B9A8(void* out, void* src);

void func_0011B060(void* self, s32 n);

void func_0011B538(void* self, s32 k);

void func_0011B018(void* dst, void* src);

struct __attribute__((aligned(16))) Quad_119A58 { s32 w[4]; };

void func_0011B008(Quad_119A58* q);

void func_0011B018(void* out, Quad_119A58* q);

void func_0011B060(Quad_119A58* q, s32 mode);

void func_0011B0A8(Quad_119A58* a, Quad_119A58* b);

void func_0011B0A8(void* a, void* b);

void func_0018D778(void);


void* func_0011C240(void* p);

void* func_001F5C0C(void* p, s32 value, s32 size);

struct Rec_11B570 { s32 tag; s32 value; };

void func_0011B418(void* self);

struct Rec_11B700 { s32 tag; s32 value; };

struct Obj_11B8A8 { s32 tag; void* ptr; };

struct Node_11BE90 { s32 key; u8 data[8]; struct Node_11BE90* next; };

struct Head_11BE90 { struct Node_11BE90* first; };

struct Node_11AF28 {
    s32 kind;
    s32 value;
    Node_11AF28* child;
};

typedef Node_11AF28 Node_11AEB8;

void func_0011B258(void* src, void* dst, void* arg);

Node_11AEB8* func_0011AF28(void);


void* func_0011C240(void* pool);

void* func_001F5C0C(void* dst, s32 value, s32 size);

Node_11AF28* func_0011B008(Node_11AF28* self);

void func_0011B060(void* self, s32 flags);

struct Ext_11AF98 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
};

struct Node_11B008 {
    s32 kind;
    s32 value;
    Node_11B008* child;
};

struct Node_11B018 {
    s32 kind;
    s32 value;
    Node_11B018* child;
};

void func_0011B4A8(Node_11B018* node);

void func_0018D778(void* self);




extern u8 D_00259F38[];

void* func_001F5C0C(void* p, s32 v, s32 n);

s32 func_0011C498(void);

void func_0011C418(void* obj, s32 value, s32 zero);

void* func_0018D5C0(s32 size);

void func_0011A6A8(void* p);

void func_0011A670(void);

void func_0011AF78(void* self);

void func_0011C4E8(void);

void func_0011C128(void* obj, s32 count, s32 size);

void func_0011CA90(void);

struct Quad_1180C0 { s32 a, b, c, d; };

void func_0011B008(Quad_1180C0* q);

void func_0011B0A8(Quad_1180C0* a, Quad_1180C0* b);

void func_0011B060(Quad_1180C0* q, int mode);

void func_0011B018(void* dst, Quad_1180C0* src);

struct Quad_1183B8 { s32 a, b, c, d; };

void func_0011B008(Quad_1183B8* q);

void func_0011B0A8(Quad_1183B8* a, Quad_1183B8* b);

void func_0011B060(Quad_1183B8* q, int mode);

void func_0011B018(void* dst, Quad_1183B8* src);

struct Quad_118458 { s32 a, b, c, d; };

void func_0011B008(Quad_118458* q);

void func_0011B0A8(Quad_118458* a, Quad_118458* b);

void func_0011B060(Quad_118458* q, int mode);

void func_0011B018(void* dst, Quad_118458* src);

struct Blob_119FA0 { s32 w[4]; };

void func_0011B008(Blob_119FA0* b);

void func_0011B018(void* dst, Blob_119FA0* src);

void func_0011B060(Blob_119FA0* b, s32 mode);

void func_0011B0A8(Blob_119FA0* a, void* b);

void func_0011B538(Blob_119FA0* b, s32 n);

struct Blob_11A358 { s32 w[4]; };

void func_0011B008(Blob_11A358* b);

void func_0011B018(void* dst, Blob_11A358* src);

void func_0011B060(Blob_11A358* b, s32 mode);

s32 func_0011B0A8(u8* a, void* b);

void func_0011B538(Blob_11A358* b, s32 n);

struct Blob_11A400 { s32 w[4]; };

void func_0011B008(Blob_11A400* b);

void func_0011B018(void* dst, Blob_11A400* src);

void func_0011B060(Blob_11A400* b, s32 mode);

void func_0011B538(Blob_11A400* b, s32 n);

struct Pair_11B0A8 { s32 a; s32 b; };

void func_0011B4A8(void* self);

struct Cell_11B538 { s32 value; };

struct Tagged_11B5B0 { s32 tag; f32 value; };

struct Value_11B008 { s32 tag; s32 payload; };

void func_0011B008(Value_11B008* v);

void func_0011B018(Value_11B008* dst, Value_11B008* src);

void func_0011B060(Value_11B008* v, int mode);

void func_0011B5B0(Value_11B008* v, f32 f);

struct Quad_118608 { s32 a, b, c, d; };

void func_0011B008(Quad_118608* q);

void* func_0011C618(void);

void func_0011B788(Quad_118608* q, void* b);

void func_0011B018(void* dst, Quad_118608* src);

void func_0011B060(Quad_118608* q, int mode);

struct Quad_118720 { s32 a, b, c, d; };

void func_0011B008(Quad_118720* q);

void func_0011B570(Quad_118720* q, s32 n);

void func_0011B018(void* dst, Quad_118720* src);

void func_0011B060(Quad_118720* q, int mode);

void func_0011C418(void* a, void* b, void* c);

struct Flag_11B5F0 { s32 tag; s32 flag; };

struct Obj_11B640 { s32 tag; void* ptr; };

void func_0011B060(void* self, s32 mode);

struct Tag_11B680 { s32 tag; s32 value; };

struct Tagged_11B8E8 { s32 tag; s32 value; };

struct Quad_11B928 { s32 a, b, c, d; };

struct Scaled_11B928 { s32 tag; f32 scale; };

void func_0011B008(Quad_11B928* q);

void func_0011B060(Quad_11B928* q, int mode);

void func_0011B570(Quad_11B928* q, s32 n);

struct Counters_11A6A8 {
    s32 count;
    u8 pad[0x500];
    s32 count2;
};

void func_0011A6A8(Counters_11A6A8* self);

struct Rec_11B6C0 { s32 tag; s32 value; };

struct Rec_11B740 { s32 tag; s32 value; };

s32 func_0011C580(u32 addr);

s32 func_0011C690(u32 value);

s32 func_0011C7C0(u32 value);

s32 func_0011C8D0(u32 value);

s32 func_0011C9E0(u32 value);

void* func_0011B008(void* obj);

void* func_0011C508(void);

void func_0011B740(void* a, void* b);

void func_0011B060(void* obj, s32 n);

struct __attribute__((aligned(16))) Quad_119AF8 { s32 w[4]; };

void func_0011B008(Quad_119AF8* q);

void func_0011B538(Quad_119AF8* q, s32 k);

void func_0011B0A8(Quad_119AF8* a, Quad_119AF8* b);

void func_0011B060(Quad_119AF8* q, s32 mode);

void func_0011B018(void* dst, Quad_119AF8* src);

// EXACT: callee 0011B008 declared s32 and called as statement.

struct __attribute__((aligned(16))) Quad_118DB8 { s32 w[4]; };

s32 func_0011B008(Quad_118DB8* q);

void func_0011B018(void* out, Quad_118DB8* q);

void func_0011B060(Quad_118DB8* q, s32 mode);

void func_0011B0A8(Quad_118DB8* a, Quad_118DB8* b);

void func_0011B538(Quad_118DB8* q, s32 n);

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_118E80 { s32 w[4]; };

s32 func_0011B008(Quad_118E80* q);

void func_0011B018(void* out, Quad_118E80* q);

void func_0011B060(Quad_118E80* q, s32 mode);

void func_0011B0A8(Quad_118E80* a, Quad_118E80* b);

void func_0011B538(Quad_118E80* q, s32 n);

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119878 { s32 w[4]; };

s32 func_0011B008(Quad_119878* q);

void func_0011B0A8(Quad_119878* a, Quad_119878* b);

void func_0011B060(Quad_119878* q, s32 mode);

void func_0011B538(Quad_119878* q, s32 k);

void func_0011B018(void* dst, Quad_119878* src);

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119970 { s32 w[4]; };

struct Item_119970 { s32 tag; Item_119970* child; Item_119970* next; };

struct Rec_119970 { s32 c; Item_119970* head; s32 count; s32 found; Item_119970* after; };

s32 func_0011B008(Quad_119970* q);

void* func_0011AFC8(void);

void func_0011B700(Quad_119970* r, Rec_119970* value);

void func_0011B018(void* dst, Quad_119970* src);

void func_0011B060(Quad_119970* q, s32 mode);

struct Node_11BD28 { s32 key; Value_11B008 value; Node_11BD28* next; };

struct List_11BD28 { Node_11BD28* head; };

Value_11B008* func_0011B0A8(Value_11B008* dst, Value_11B008* src);

void func_0011B538(Value_11B008* v, s32 tag);

void* func_0011B008(void* p);

void func_0011B5F0(void* p, s32 flag);

void func_0011B060(void* p, s32 flags);

struct Tmp_119218;

void func_0011B018(void* out, void* p);

struct Tmp_119218 {
    s32 tag; s32 value; s32 pad[2];
    ~Tmp_119218() { func_0011B060(this, 2); }
};

void func_0011B0A8(void* a, const Tmp_119218& b);

struct Link_1194A8 { s32 f0; Link_1194A8* f4; Link_1194A8* f8; };

struct __attribute__((aligned(16))) Quad_1194A8 { s32 type; Link_1194A8* head; s32 w2; s32 w3; };

void* func_0011B008(void* q);

void func_0011B018(void* self, void* q);

void func_0011B538(void* q, s32 n);

void func_0011B060(void* q, s32 mode);

// Fixed by merging the two flag tests into one "kind != 0x1B || p != 0".

struct __attribute__((aligned(16))) Quad_119310 { s32 kind; void* p; s32 w[2]; };

s32 func_0011B008(Quad_119310* q);

void func_0011B018(void* out, Quad_119310* q);

void func_0011B060(Quad_119310* q, s32 mode);

void func_0011B0A8(Quad_119310* a, Quad_119310* b);

void func_0011B538(Quad_119310* q, s32 n);

struct Quad_118F48 { s32 a, b, c, d; };

void func_0011B008(Quad_118F48* q);

void func_0011B018(void* dst, Quad_118F48* src);

void func_0011B060(Quad_118F48* q, int mode);

void func_0011B0A8(Quad_118F48* a, Quad_118F48* b);

void func_0011B538(Quad_118F48* q, int n);

struct __attribute__((aligned(16))) Quad_1196C8 { s32 w[4]; };

s32 func_0011B008(Quad_1196C8* q);

void func_0011B018(void* out, Quad_1196C8* q);

void func_0011B060(Quad_1196C8* q, s32 mode);

void func_0011B0A8(Quad_1196C8* a, Quad_1196C8* b);

struct Val_11B0F8 {
    s32 type;
    union {
        s32 i;
        f32 f;
        f32* v;
        void* p;
    } u;
};

s32 func_001F59C4(void* a, void* b, s32 n);

struct Arg_11B418;

struct Op_11B418 { s32 kind; Arg_11B418* arg; };

void func_0011C5B0(Arg_11B418* a);

void func_0011C6C0(Arg_11B418* a);

void func_0011C7F0(Arg_11B418* a);

void func_0011C900(Arg_11B418* a);

void func_0011CA20(Arg_11B418* a);

struct Cmd_11B4A8 {
    s32 op;
    u32 arg;
};

struct Tmp_11A080 { s32 w[4]; };

struct Ret_11A080;

void func_0011B008(Tmp_11A080* t);

void func_0011B018(Ret_11A080* dst, Tmp_11A080* src);

void func_0011B060(Tmp_11A080* t, s32 mode);

void func_0011B0A8(Tmp_11A080* dst, void* src);

struct Val_11B258 { s32 tag; void* val; };

struct __attribute__((aligned(16))) Q16_11B258 { s32 w[4]; };

struct __attribute__((aligned(16))) Q64_11B258 { Q16_11B258 q[4]; };

struct __attribute__((packed)) D8_11B258 { s32 a, b; };

struct D12_11B258 { D8_11B258 a; s32 c; };

struct Node_11B258 { s32 pad; };

void func_0011AEB8(Val_11B258* src, Node_11B258* dst, void* arg);

void* func_0011C748(void);

void* func_0011C858(void);

void* func_0011C968(void);

s32 func_0011C580(Q16_11B258* p);

s32 func_0011C690(Q64_11B258* p);

s32 func_0011C7C0(Q16_11B258* p);

s32 func_0011C8D0(D8_11B258* p);

s32 func_0011C9E0(D12_11B258* p);

void func_0011AF98(Val_11B258* src, Node_11B258* dst, void* arg);

struct Rd_11BA28;

struct Node_11BA28 {
    s32 kind;
    s32 w4;
    Node_11BA28* child;
};

extern s32 D_00275714;

s32 func_00137B90(Rd_11BA28* r);

void func_00137BE0(Rd_11BA28* r);

s32 func_00137D78(Rd_11BA28* r);

f32 func_00137DF8(Rd_11BA28* r);

s32 func_00137C40(Rd_11BA28* r);

void func_0011B570(Node_11BA28* n, s32 v);

void func_0011B5B0(Node_11BA28* n, f32 v);

void func_0011B5F0(Node_11BA28* n, s32 v);

void func_0011B8A8(Node_11BA28* n, s32 v);

void func_0011B640(Node_11BA28* n, s32 v);

void func_0011B680(Node_11BA28* n, s32 v);

void func_0011B740(Node_11BA28* n, f32* p);

void func_0011B788(Node_11BA28* n, f32* p);

void func_0011B7D0(Node_11BA28* n, f32* p);

void func_0011B818(Node_11BA28* n, f32* p);

void func_0011B860(Node_11BA28* n, f32* p);

void func_0011B6C0(Node_11BA28* n, Node_11BA28* c);

struct V_119BB0 { s32 type; void* p; };

V_119BB0* func_0011B008(V_119BB0* q);

void func_0011B060(V_119BB0* q, s32 mode);

void func_0011B0A8(V_119BB0* a, V_119BB0* b);

void func_0011B018(V_119BB0* dst, V_119BB0* src);

void func_0011B6C0(V_119BB0* q, V_119BB0* head);

void func_0011B538(V_119BB0* q, s32 n);

void* func_0011AE78(void);
void func_0011AEB8(Node_11AEB8* src, Node_11AEB8* dst, void* arg);
Node_11AF28* func_0011AF28(void);
void func_0011AF78(void* self);
void func_0011AF98(Ext_11AF98* src, Ext_11AF98* dst, s32 first);
void* func_0011AFC8(void);
Node_11B008* func_0011B008(Node_11B008* self);
Node_11B018* func_0011B018(Node_11B018* dst, Node_11B018* src);
void func_0011B060(void* self, s32 flags);
Pair_11B0A8* func_0011B0A8(Pair_11B0A8* dst, Pair_11B0A8* src);
s32 func_0011B0F8(Val_11B0F8* a, Val_11B0F8* b);
void func_0011B258(Val_11B258* in, Val_11B258* out, void* arg);
void func_0011B418(Op_11B418* op);
void func_0011B4A8(Cmd_11B4A8* c);
void func_0011B538(Cell_11B538* self, s32 v);
void func_0011B570(Rec_11B570* r, s32 value);
void func_0011B5B0(Tagged_11B5B0* self, f32 v);
void func_0011B5F0(Flag_11B5F0* r, void* arg);
void func_0011B640(Obj_11B640* self, void* arg);
void func_0011B680(Tag_11B680* r, s32 value);
void func_0011B6C0(Rec_11B6C0* r, s32 value);
void func_0011B700(Rec_11B700* r, s32 value);
void func_0011B740(Rec_11B740* r, s32 value);
void func_0011B788(Rec_11B570* self, u32 value);
void func_0011B7D0(Rec_11B570* self, u32 value);
void func_0011B818(Rec_11B570* self, u32 value);
void func_0011B860(Rec_11B570* self, u32 value);
void func_0011B8A8(Obj_11B8A8* self, void* arg);
void func_0011B8E8(Tagged_11B8E8* self, s32 value);
void* func_0011B928(void* out, Scaled_11B928* in);
Value_11B008* func_0011B9A8(Value_11B008* out, Value_11B008* in);
Node_11BA28* func_0011BA28(Rd_11BA28* rd);
Value_11B008* func_0011BD28(Value_11B008* self, List_11BD28* list, s32 key, Value_11B008* value);
Value_11B008* func_0011BDD0(Value_11B008* out, List_11BD28* list, s32 key, Value_11B008* value);
s32 func_0011BE90(Head_11BE90* head, s32 key, void* arg);
void func_0011BEE0(void** self, s32* out);
void* func_0011BF30(void);
void func_0011BF70(void);

void* func_0011AE78(void)
{
    void* p = func_0011C240(&D_0025C2D0);
    func_001F5C0C(p, 0, 12);
    return p;
}

void func_0011AEB8(Node_11AEB8* src, Node_11AEB8* dst, void* arg)
{
    func_0011B258(src, dst, arg);
    if (src->child != 0) {
        Node_11AEB8* copy = func_0011AF28();
        func_0011AEB8(src->child, copy, arg);
        dst->child = copy;
    }
}

Node_11AF28* func_0011AF28(void)
{
    Node_11AF28* node = (Node_11AF28*)func_0011C240(&D_0025C250);
    func_001F5C0C(node, 0, 12);
    func_0011B008(node);
    node->kind = -1;
    return node;
}

void func_0011AF78(void* self)
{
    func_0011B060(self, 2);
}

void func_0011AF98(Ext_11AF98* src, Ext_11AF98* dst, s32 first)
{
    if (first == 0) {
        first = src->w0;
    }
    dst->w0 = first;
    dst->w1 = src->w1;
    dst->w2 = src->w2;
    dst->w3 = src->w3;
    dst->w4 = src->w4;
}

void* func_0011AFC8(void)
{
    void* p = func_0011C240(&D_0025C2B0);
    func_001F5C0C(p, 0, 0x14);
    return p;
}

Node_11B008* func_0011B008(Node_11B008* self)
{
    self->kind = -1;
    return self;
}

Node_11B018* func_0011B018(Node_11B018* dst, Node_11B018* src)
{
    func_0011B4A8(src);
    dst->kind = src->kind;
    dst->value = src->value;
    return dst;
}

void func_0011B060(void* self, s32 flags)
{
    func_0011B418(self);
    if (flags & 1) {
        func_0018D778(self);
    }
}

Pair_11B0A8* func_0011B0A8(Pair_11B0A8* dst, Pair_11B0A8* src)
{
    func_0011B4A8(src);
    func_0011B418(dst);
    dst->a = src->a;
    dst->b = src->b;
    return dst;
}

s32 func_0011B0F8(Val_11B0F8* a, Val_11B0F8* b)
{
    if (a->type != b->type)
        return 0;
    switch (a->type) {
    case 0x15:
        return a->u.f == b->u.f;
    case 0x1B: {
        s32 r = 0;
        if (a->u.p == 0) {
            if (b->u.p == 0)
                goto yes;
            goto out;
        }
        if (b->u.p != 0) {
        yes:
            r = 1;
        }
    out:
        return r;
    }
    case 0x17:
        return func_001F59C4(a->u.p, b->u.p, 0x40) == 0;
    case 0x19: {
        f32* pa = a->u.v;
        f32* pb = b->u.v;
        s32 r = 0;
        if (pa[0] == pb[0] && pa[1] == pb[1])
            r = 1;
        return r;
    }
    case 0x16:
    case 0x18:
    case 0x1A: {
        f32* pa = a->u.v;
        f32* pb = b->u.v;
        s32 r = 0;
        if (pa[0] == pb[0] && pa[1] == pb[1] && pa[2] == pb[2])
            r = 1;
        return r;
    }
    case 0x14:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
        return a->u.i == b->u.i;
    }
    return 1;
}

void func_0011B258(Val_11B258* in, Val_11B258* out, void* arg)
{
    out->tag = in->tag;
    switch (in->tag) {
    case 0x1E: {
        Node_11B258* n = (Node_11B258*)func_0011AF28();
        func_0011AEB8((Val_11B258*)in->val, n, arg);
        out->val = n;
        break;
    }
    case 0x16: {
        Q16_11B258* p = (Q16_11B258*)func_0011C508();
        *p = *(Q16_11B258*)in->val;
        (void)func_0011C580(p);
        out->val = p;
        break;
    }
    case 0x17: {
        Q64_11B258* p = (Q64_11B258*)func_0011C618();
        *p = *(Q64_11B258*)in->val;
        (void)func_0011C690(p);
        out->val = p;
        break;
    }
    case 0x18: {
        Q16_11B258* p = (Q16_11B258*)func_0011C748();
        *p = *(Q16_11B258*)in->val;
        (void)func_0011C7C0(p);
        out->val = p;
        break;
    }
    case 0x19: {
        D8_11B258* p = (D8_11B258*)func_0011C858();
        *p = *(D8_11B258*)in->val;
        (void)func_0011C8D0(p);
        out->val = p;
        break;
    }
    case 0x1A: {
        D12_11B258* p = (D12_11B258*)func_0011C968();
        *p = *(D12_11B258*)in->val;
        (void)func_0011C9E0(p);
        out->val = p;
        break;
    }
    case 0x1F: {
        Node_11B258* n = (Node_11B258*)func_0011AFC8();
        func_0011AF98((Val_11B258*)in->val, n, arg);
        out->val = n;
        break;
    }
    default:
        out->val = in->val;
        break;
    }
}

void func_0011B418(Op_11B418* op)
{
    switch (op->kind) {
    case 0x16: func_0011C5B0(op->arg); break;
    case 0x17: func_0011C6C0(op->arg); break;
    case 0x18: func_0011C7F0(op->arg); break;
    case 0x19: func_0011C900(op->arg); break;
    case 0x1A: func_0011CA20(op->arg); break;
    }
}

void func_0011B4A8(Cmd_11B4A8* c)
{
    switch (c->op) {
    case 0x16: func_0011C580(c->arg); break;
    case 0x17: func_0011C690(c->arg); break;
    case 0x18: func_0011C7C0(c->arg); break;
    case 0x19: func_0011C8D0(c->arg); break;
    case 0x1A: func_0011C9E0(c->arg); break;
    }
}

void func_0011B538(Cell_11B538* self, s32 v)
{
    func_0011B418(self);
    self->value = v;
}

void func_0011B570(Rec_11B570* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x14;
}

void func_0011B5B0(Tagged_11B5B0* self, f32 v)
{
    func_0011B418(self);
    self->value = v;
    self->tag = 0x15;
}

void func_0011B5F0(Flag_11B5F0* r, void* arg)
{
    func_0011B418(r);
    if (arg != 0)
        r->flag = 1;
    else
        r->flag = 0;
    r->tag = 0x1B;
}

void func_0011B640(Obj_11B640* self, void* arg)
{
    func_0011B418(self);
    self->ptr = arg;
    self->tag = 0x1C;
}

void func_0011B680(Tag_11B680* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x1D;
}

void func_0011B6C0(Rec_11B6C0* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x1E;
}

void func_0011B700(Rec_11B700* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x1F;
}

void func_0011B740(Rec_11B740* r, s32 value)
{
    func_0011C580(value);
    func_0011B418(r);
    r->value = value;
    r->tag = 0x16;
}

void func_0011B788(Rec_11B570* self, u32 value)
{
    (void)func_0011C690(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 23;
}

void func_0011B7D0(Rec_11B570* self, u32 value)
{
    (void)func_0011C7C0(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 24;
}

void func_0011B818(Rec_11B570* self, u32 value)
{
    (void)func_0011C8D0(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 25;
}

void func_0011B860(Rec_11B570* self, u32 value)
{
    (void)func_0011C9E0(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 26;
}

void func_0011B8A8(Obj_11B8A8* self, void* arg)
{
    func_0011B418(self);
    self->ptr = arg;
    self->tag = 0x20;
}

void func_0011B8E8(Tagged_11B8E8* self, s32 value)
{
    func_0011B418(self);
    self->tag = 0x21;
    self->value = value;
}

void* func_0011B928(void* out, Scaled_11B928* in)
{
    if (in->tag == 0x14) {
        func_0011B018(out, in);
    } else {
        Quad_11B928 q;
        func_0011B008(&q);
        func_0011B570(&q, (s32)in->scale);
        func_0011B018(out, &q);
        func_0011B060(&q, 2);
    }
    return out;
}

Value_11B008* func_0011B9A8(Value_11B008* out, Value_11B008* in)
{
    if (in->tag == 0x15) {
        func_0011B018(out, in);
    } else {
        Value_11B008 tmp;
        func_0011B008(&tmp);
        func_0011B5B0(&tmp, (f32)in->payload);
        func_0011B018(out, &tmp);
        func_0011B060(&tmp, 2);
    }
    return out;
}

Node_11BA28* func_0011BA28(Rd_11BA28* rd)
{
    s32 tag = func_00137B90(rd);
    if (tag == 0xFF) {
        return 0;
    }
    s32 flag = tag & 0x80;
    Node_11BA28* n = (Node_11BA28*)func_0011AF28();
    n->kind = tag & 0x7F;
    if (D_00275714) {
        func_00137BE0(rd);
        func_00137BE0(rd);
        func_00137BE0(rd);
        func_00137BE0(rd);
        func_00137BE0(rd);
    }
    switch (n->kind) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20:
        func_0011B570(n, func_00137D78(rd));
        break;
    case 21:
        func_0011B5B0(n, func_00137DF8(rd));
        break;
    case 27:
        func_0011B5F0(n, func_00137C40(rd));
        break;
    case 32:
        func_0011B8A8(n, func_00137C40(rd));
        break;
    case 28:
        func_0011B640(n, func_00137C40(rd));
        break;
    case 29:
        func_0011B680(n, func_00137C40(rd));
        break;
    case 22:
    {
        s32 i = 2;
        f32* buf = (f32*)func_0011C508();
        f32* p = buf;
        do {
            *p++ = func_00137DF8(rd);
        } while (--i >= 0);
        n->kind = -1;
        func_0011B740(n, buf);
    }
        break;
    case 23:
    {
        s32 i = 15;
        f32* buf = (f32*)func_0011C618();
        f32* p = buf;
        do {
            *p++ = func_00137DF8(rd);
        } while (--i >= 0);
        n->kind = -1;
        func_0011B788(n, buf);
    }
        break;
    case 24:
    {
        s32 i = 2;
        f32* buf = (f32*)func_0011C748();
        f32* p = buf;
        do {
            *p++ = func_00137DF8(rd);
        } while (--i >= 0);
        n->kind = -1;
        func_0011B7D0(n, buf);
    }
        break;
    case 25:
    {
        f32* p = (f32*)func_0011C858();
        p[0] = func_00137DF8(rd);
        p[1] = func_00137DF8(rd);
        n->kind = -1;
        func_0011B818(n, p);
    }
        break;
    case 26:
    {
        f32* p = (f32*)func_0011C968();
        p[0] = func_00137DF8(rd);
        p[1] = func_00137DF8(rd);
        p[2] = func_00137DF8(rd);
        n->kind = -1;
        func_0011B860(n, p);
    }
        break;
    case 30:
        func_0011B6C0(n, func_0011BA28(rd));
        break;
    }
    if (flag) {
        n->child = func_0011BA28(rd);
    } else {
        n->child = 0;
    }
    return n;
}

Value_11B008* func_0011BD28(Value_11B008* self, List_11BD28* list, s32 key, Value_11B008* value)
{
    Value_11B008 tmp;
    func_0011B008(&tmp);
    Node_11BD28* node = (Node_11BD28*)func_0011C498();
    node->key = key;
    (void)func_0011B0A8(&node->value, value);
    node->next = list->head;
    list->head = node;
    func_0011B538(&tmp, 0x22);
    func_0011B018(self, &tmp);
    func_0011B060(&tmp, 2);
    return self;
}

Value_11B008* func_0011BDD0(Value_11B008* out, List_11BD28* list, s32 key, Value_11B008* value)
{
    Value_11B008 tmp;
    Node_11BD28* node = list->head;
    while (node != 0) {
        if (node->key == key) {
            func_0011B008(&tmp);
            (void)func_0011B0A8(&node->value, value);
            func_0011B538(&tmp, 0x22);
            func_0011B018(out, &tmp);
            func_0011B060(&tmp, 2);
            goto done;
        }
        node = node->next;
    }
    func_0011B008(&tmp);
    func_0011B538(&tmp, 0x22);
    func_0011B018(out, &tmp);
    func_0011B060(&tmp, 2);
done:
    return out;
}

s32 func_0011BE90(Head_11BE90* head, s32 key, void* arg)
{
    Node_11BE90* n = head->first;
    while (n != 0) {
        if (n->key == key) {
            if (arg != 0) {
                func_0011B0A8(arg, n->data);
            }
            return 1;
        }
        n = n->next;
    }
    return 0;
}

void func_0011BEE0(void** self, s32* out)
{
    s32 v = func_0011C498();
    func_0011C418(*self, v, 0);
    *out = v;
}

void* func_0011BF30(void)
{
    void* p = func_0018D5C0(4);
    func_001F5C0C(p, 0, 4);
    return p;
}

void func_0011BF70(void)
{
    func_0011A6A8(D_00259F38);
    func_0011C128(&D_0025C250, 0xC, 0x2000);
    D_0025C250.callback = (void*)func_0011AF78;
    func_0011C128(&D_0025C270, 0x1C, 0x190);
    D_0025C270.callback = (void*)func_0011A670;
    func_0011C128(&D_0025C290, 0x10, 0x800);
    D_0025C290.callback = (void*)func_0011C4E8;
    func_0011C128(&D_0025C2B0, 0x14, 0x800);
    func_0011CA90();
    func_0011C128(&D_0025C2D0, 0xC, 0x80);
}

void func_0011A6B8(void* p);
void func_0011C1D0(void* p);
void func_0011CBB0(void);

void func_0011C040(void)
{
    func_0011C1D0(&D_0025C250);
    func_0011C1D0(&D_0025C270);
    func_0011C1D0(&D_0025C290);
    func_0011C1D0(&D_0025C2B0);
    func_0011CBB0();
    func_0011C1D0(&D_0025C2D0);
    func_0011A6B8(D_00259F38);
}
