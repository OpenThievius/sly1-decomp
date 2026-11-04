// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// A count followed by that many values.
struct IntList { s32 count; s32 items[1]; };





// A record that keeps a stack of values at 0x708.
struct StackAt708 { u8 pad[0x708]; s32 count; s32 items[1]; };



struct Vec_1188F0 { f32 x, y, z, w; };
struct Src_1188F0 { s32 pad0; void* p4; };

void* func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_001566C8(void* obj, f32 f);
void func_0011B060(void* self, s32 n);
void func_0011B538(void* self, s32 k);
void func_0011B018(void* dst, void* src);



struct __attribute__((aligned(16))) Quad_119A58 { s32 w[4]; };
struct Node_119A58 { s32 pad[2]; Node_119A58* next; };

void func_0011B008(Quad_119A58* q);
void func_0011B018(void* out, Quad_119A58* q);
void func_0011B060(Quad_119A58* q, s32 mode);
void func_0011B0A8(Quad_119A58* a, Quad_119A58* b);
void func_0011A080(Quad_119A58* t, Node_119A58* n, s32 c);



void* func_0011A4D8(void* a, s32 b, s32 c, void* d);
void func_0011B0A8(void* a, void* b);



void func_0018D778(void);



struct Stack_11A790 { u8 pad[0xF0C]; s32 count; s32 items[1]; };



void func_0011ADF8(void* p, s32 mode);



extern u8 D_0025C2B0[];
void* func_0011C240(void* p);
void* func_001F5C0C(void* p, s32 value, s32 size);

struct Rec_11B570 { s32 tag; s32 value; };
void func_0011B418(void* self);

struct Rec_11B700 { s32 tag; s32 value; };
void func_0011B418(void* self);

struct Obj_11B8A8 { s32 tag; void* ptr; };

void func_0011B418(void* self);

struct Node_11BE90 { s32 key; u8 data[8]; struct Node_11BE90* next; };
struct Head_11BE90 { struct Node_11BE90* first; };

void func_0011B0A8(void* a, void* b);

struct Node_11AF28 {
    s32 kind;
    s32 value;
    Node_11AF28* child;
};
typedef Node_11AF28 Node_11AEB8;

void func_0011B258(void* src, void* dst, void* arg);
Node_11AEB8* func_0011AF28(void);

extern u8 D_0025C250[];

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

void func_0011B418(void* self);
void func_0018D778(void* self);

extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011C2A0(void* p);



extern u8 D_00259F38[];

void* func_0011A678(void* p);
void func_0011A680(void* p, s32 n);



void func_0011ADF8(s32 a, s32 b);



extern u8 D_0025C2D0[];

void* func_0011C240(void* p);
void* func_001F5C0C(void* p, s32 v, s32 n);

s32 func_0011C498(void);
void func_0011C418(void* obj, s32 value, s32 zero);

void* func_0018D5C0(s32 size);
void* func_001F5C0C(void* p, s32 value, s32 size);

extern u8 D_00259F38[];
extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011A6A8(void* p);
void func_0011A670(void);
void func_0011AF78(void* self);
void func_0011C4E8(void);
void func_0011C128(void* obj, s32 count, s32 size);
void func_0011CA90(void);

struct Quad_1180C0 { s32 a, b, c, d; };
struct Frame_1180C0 { Quad_1180C0 q; Quad_1180C0 t; s32 a; s32 b; };
union Raw_1180C0 { s32 i; f32 f; };
struct In_1180C0 { u8 pad0[4]; s32 w4; s32 kind; Raw_1180C0 raw; };

extern void* D_00275710;

void func_0011B008(Quad_1180C0* q);
void func_0018D608(void);
void func_0018D6F0(void);
void func_001DC4D0(void* self, f32 scale, s32 p1, s32 p2, s32 p3, s32 p4, s32* o1, s32* o2);
void func_00117AF0(Quad_1180C0* t, s32 a, s32 b);
void func_0011B0A8(Quad_1180C0* a, Quad_1180C0* b);
void func_0011B060(Quad_1180C0* q, int mode);
void func_0011B018(void* dst, Quad_1180C0* src);



struct Quad_1183B8 { s32 a, b, c, d; };
struct Frame_1183B8 { Quad_1183B8 q; Quad_1183B8 t; };

void func_0011B008(Quad_1183B8* q);
void func_00118198(Quad_1183B8* dst, s32 code, s32 x, s32 y, s32 z);
void func_0011B0A8(Quad_1183B8* a, Quad_1183B8* b);
void func_0011B060(Quad_1183B8* q, int mode);
void func_0011B018(void* dst, Quad_1183B8* src);



struct Quad_118458 { s32 a, b, c, d; };
struct Frame_118458 { Quad_118458 q; Quad_118458 t; };

void func_0011B008(Quad_118458* q);
void func_00118198(Quad_118458* dst, s32 code, s32 x, s32 y, s32 z);
void func_0011B0A8(Quad_118458* a, Quad_118458* b);
void func_0011B060(Quad_118458* q, int mode);
void func_0011B018(void* dst, Quad_118458* src);



struct Blob_119FA0 { s32 w[4]; };
struct Inner_119FA0 { u8 pad0[4]; s32 id; };
struct Mid_119FA0 { u8 pad0[8]; Inner_119FA0* inner; };
struct Outer_119FA0 { u8 pad0[4]; Mid_119FA0* mid; };


void func_0011B008(Blob_119FA0* b);
void func_0011B018(void* dst, Blob_119FA0* src);
void func_0011B060(Blob_119FA0* b, s32 mode);
void func_0011B0A8(Blob_119FA0* a, void* b);
void func_0011B538(Blob_119FA0* b, s32 n);
void func_001C13E8(void* dst, s32 id, u8* ctx);
void* func_001C1390(s32 id, u8* ctx);
void func_0011A338(void* list, void* value);



struct Slot_11A328 { s32 flag; s32 value; };



struct Blob_11A358 { s32 w[4]; };
struct Node_11A358 { s32 kind; u8 body[8]; Node_11A358* next; };
struct Owner_11A358 { u8 pad0[0x14]; Node_11A358* head; };

void func_0011B008(Blob_11A358* b);
void func_0011B018(void* dst, Blob_11A358* src);
void func_0011B060(Blob_11A358* b, s32 mode);
s32 func_0011B0A8(u8* a, void* b);
void func_0011B538(Blob_11A358* b, s32 n);
s32 func_0011C498(void);



struct Blob_11A400 { s32 w[4]; };

void func_0011B008(Blob_11A400* b);
void func_0011B018(void* dst, Blob_11A400* src);
void func_0011B060(Blob_11A400* b, s32 mode);
void func_0011B0A8(void* a, void* b);
void func_0011B538(Blob_11A400* b, s32 n);
void* func_0011A4D8(void* table, void* key, s32 mode);



struct Stack_11A7D8 { u8 pad[0x1310]; s32 count; s32 items[1]; };



struct Pair_11B0A8 { s32 a; s32 b; };

void func_0011B418(void* self);
void func_0011B4A8(void* self);

struct Cell_11B538 { s32 value; };

void func_0011B418(void* self);

struct Tagged_11B5B0 { s32 tag; f32 value; };

void func_0011B418(void* self);

struct Value_11B008 { s32 tag; s32 payload; };

void func_0011B008(Value_11B008* v);
void func_0011B018(Value_11B008* dst, Value_11B008* src);
void func_0011B060(Value_11B008* v, int mode);
void func_0011B5B0(Value_11B008* v, f32 f);

struct Quad_118608 { s32 a, b, c, d; };
struct Frame_118608 { Quad_118608 q; };
struct In_118608 { u8 pad0[4]; s32 f4; u8 pad8[4]; s32 fC; u8 pad10[4]; s32 f14; };

void func_0011B008(Quad_118608* q);
void* func_0011C618(void);
void func_00128150(s32 a, s32 b, s32 c, void* d);
void func_001884C0(void* p);
void func_0011B788(Quad_118608* q, void* b);
void func_0011B018(void* dst, Quad_118608* src);
void func_0011B060(Quad_118608* q, int mode);



struct Quad_118720 { s32 a, b, c, d; };
struct Frame_118720 { Quad_118720 q; s32 n; s32 pad[3]; };
struct In_118720 { u8 pad0[4]; s32 f4; u8 pad8[4]; s32 fC; };

void func_0011B008(Quad_118720* q);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_0011B570(Quad_118720* q, s32 n);
void func_001BF718(void* slot);
void func_0011B018(void* dst, Quad_118720* src);
void func_0011B060(Quad_118720* q, int mode);



// A node of a keyed list: the key, a value whose address is returned, and the next node at 0xC.
struct Node_11A4D8 { s32 key; s32 value; s32 pad8; struct Node_11A4D8* next; };

// A tree node: count and child pointers at 0x0 and 0x4, a list head at 0x14, a busy flag at 0x18.
struct Tree_11A4D8 {
    s32 count;
    struct Tree_11A4D8* items[4];
    struct Node_11A4D8* head;
    s32 flag;
};



// The same tree node as func_0011A4D8: count and child pointers, a list head at 0x14, a flag at 0x18.
struct Node_11A5B0;
struct Tree_11A5B0 {
    s32 count;
    struct Tree_11A5B0* items[4];
    struct Node_11A5B0* head;
    s32 flag;
};

void func_0018D800(void* dst, void* src, s32 bytes);
s32 func_0011C498(void);
void func_0011C418(void* a, void* b, void* c);



struct Flag_11B5F0 { s32 tag; s32 flag; };
void func_0011B418(void* self);

struct Obj_11B640 { s32 tag; void* ptr; };
void func_0011B418(void* self);

struct Vec_118850 { f32 x, y, z, w; };
struct Src_118850 { s32 pad0; s32 n; };

void* func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_0016EC38(void* p, s32 n, f32 f);
void func_0011B060(void* self, s32 mode);
void func_0011B018(void* dst, void* src);

extern u8 D_00262C70[];



extern u8 D_0025C270[];
void* func_0011C240(void* p);





struct Stack_11A7B8 { u8 pad[0x1310]; s32 count; s32 items[1]; };



struct Tag_11B680 { s32 tag; s32 value; };
void func_0011B418(void* self);

struct Tagged_11B8E8 { s32 tag; s32 value; };

void func_0011B418(void* self);

struct Quad_11B928 { s32 a, b, c, d; };
struct Scaled_11B928 { s32 tag; f32 scale; };

void func_0011B008(Quad_11B928* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(Quad_11B928* q, int mode);
void func_0011B570(Quad_11B928* q, s32 n);

// A 128-bit value, copied as one quadword.
typedef u64 Quad_118D10 __attribute__((mode(TI)));

// Copies the quadword at src into out and returns out.


// A 128-bit value, stored as one quadword.
typedef u64 Quad_118D20 __attribute__((mode(TI)));

// Stores the quadword v into out and returns out.




struct Counters_11A6A8 {
    s32 count;
    u8 pad[0x500];
    s32 count2;
};



struct Rec_11B6C0 { s32 tag; s32 value; };
void func_0011B418(void* self);

struct Rec_11B740 { s32 tag; s32 value; };
void func_0011B418(void* self);
s32 func_0011C580(u32 addr);

struct Obj_0011A708 { u8 pad[0x504]; s32 count; s32 values[1]; };


struct Obj_0011A728 { u8 pad[0x708]; s32 count; s32 values[1]; };


struct Obj_0011A770 { u8 pad[0xF0C]; s32 count; s32 values[1]; };




s32 func_0011C690(u32 value);

s32 func_0011C7C0(u32 value);

s32 func_0011C8D0(u32 value);

s32 func_0011C9E0(u32 value);

struct Tmp_1184F8 { u8 bytes[0x10]; };
struct Src_1184F8 { s32 pad0; void* a; s32 pad2; s32 b; s32 pad4; void* c; };

void* func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_0011B740(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);



struct Tmp_118580 { u8 bytes[0x10]; };
struct Src_118580 { s32 pad0; void* a; s32 pad2; s32 b; s32 pad4; void* c; };

void* func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_001280C0(void* a, s32 b, void* c, void* d);
void func_0011B740(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);



struct Tmp_1187E8 { s32 w0; s32 w1; s32 w2; s32 w3; };
struct Src_1187E8 { s32 pad0; void* a; };

void* func_0011B008(void* obj);
void func_001BF788(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);



struct Tmp_118D48 { u8 bytes[0x10]; };
struct Src_118D48 { s32 pad0; s32 a; };

void* func_0011B008(void* obj);
s32 func_0011A498(void* a, s32 b, s32 c, void* d);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);



struct __attribute__((aligned(16))) Quad_119AF8 { s32 w[4]; };
struct Node_119AF8 { s32 pad[2]; Node_119AF8* next; };
struct Wrap_119AF8 { s32 pad[2]; Node_119AF8* first; };
struct Owner_119AF8 { s32 pad; Wrap_119AF8* wrap; };

void func_0011B008(Quad_119AF8* q);
void func_0011B538(Quad_119AF8* q, s32 k);
void func_0011A080(Quad_119AF8* t, Node_119AF8* n, s32 c);
void func_0011B0A8(Quad_119AF8* a, Quad_119AF8* b);
void func_0011B060(Quad_119AF8* q, s32 mode);
void func_0011B018(void* dst, Quad_119AF8* src);



// EXACT: callee 0011B008 declared s32 and called as statement.

struct __attribute__((aligned(16))) Quad_118DB8 { s32 w[4]; };
struct Node_118DB8 { s32 pad0; Node_118DB8* f4; Node_118DB8* f8; };

s32 func_0011B008(Quad_118DB8* q);
void func_0011B018(void* out, Quad_118DB8* q);
void func_0011B060(Quad_118DB8* q, s32 mode);
void func_0011B0A8(Quad_118DB8* a, Quad_118DB8* b);
void func_0011B538(Quad_118DB8* q, s32 n);
void func_0011A080(Quad_118DB8* t, Node_118DB8* n, s32 c);
void* func_0011A400(void* self, s32 table, void* key, void* item);



// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_118E80 { s32 w[4]; };
struct Node_118E80 { s32 pad0; Node_118E80* f4; Node_118E80* f8; };

s32 func_0011B008(Quad_118E80* q);
void func_0011B018(void* out, Quad_118E80* q);
void func_0011B060(Quad_118E80* q, s32 mode);
void func_0011B0A8(Quad_118E80* a, Quad_118E80* b);
void func_0011B538(Quad_118E80* q, s32 n);
void func_0011A080(Quad_118E80* t, Node_118E80* n, s32 c);
void* func_0011A358(void* self, s32 owner, void* kind, void* body);



// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119878 { s32 w[4]; };
struct Node_119878 { s32 pad[2]; Node_119878* next; };
struct Wrap_119878 { s32 pad[2]; Node_119878* first; };
struct Owner_119878 { s32 pad; Wrap_119878* wrap; };

s32 func_0011B008(Quad_119878* q);
void func_0011A080(Quad_119878* t, Node_119878* n, s32 c);
void func_0011B0A8(Quad_119878* a, Quad_119878* b);
void func_0011B060(Quad_119878* q, s32 mode);
void func_0011B538(Quad_119878* q, s32 k);
void func_0011B018(void* dst, Quad_119878* src);



// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119970 { s32 w[4]; };
struct Item_119970 { s32 tag; Item_119970* child; Item_119970* next; };
struct Wrap_119970 { s32 pad[2]; Item_119970* first; };
struct Owner_119970 { s32 pad; Wrap_119970* wrap; };
struct Rec_119970 { s32 c; Item_119970* head; s32 count; s32 found; Item_119970* after; };

s32 func_0011B008(Quad_119970* q);
void* func_0011AFC8(void);
void func_0011B700(Quad_119970* r, Rec_119970* value);
void func_0011B018(void* dst, Quad_119970* src);
void func_0011B060(Quad_119970* q, s32 mode);



struct Node_11BD28 { s32 key; Value_11B008 value; Node_11BD28* next; };
struct List_11BD28 { Node_11BD28* head; };

void func_0011B008(Value_11B008* v);
void func_0011B018(Value_11B008* dst, Value_11B008* src);
void func_0011B060(Value_11B008* v, int mode);
Value_11B008* func_0011B0A8(Value_11B008* dst, Value_11B008* src);
void func_0011B538(Value_11B008* v, s32 tag);

struct Node_119218 { s32 f0; s32 f4; Node_119218* next; };
struct Holder_119218 { s32 f0; s32 f4; Node_119218* head; };
struct Args_119218 { s32 f0; Holder_119218* holder; };

void* func_0011B008(void* p);
void func_0011B5F0(void* p, s32 flag);
void func_0011B060(void* p, s32 flags);
struct Tmp_119218;
void func_0011B018(void* out, void* p);

struct Tmp_119218 {
    s32 tag; s32 value; s32 pad[2];
    ~Tmp_119218() { func_0011B060(this, 2); }
};
struct Cursor_119218 {
    s32 tag; s32 value; s32 pad[2];
    Cursor_119218(const Cursor_119218& o) { func_0011B018(this, (void*)&o); }
    Cursor_119218() { func_0011B008(this); }
    ~Cursor_119218() { func_0011B060(this, 2); }
};

Tmp_119218 func_0011A080(void* node, void* extra);
void func_0011B0A8(void* a, const Tmp_119218& b);



struct Cursor_119128 { s32 tag; s32 value; s32 pad[2]; };
struct Node_119128 { s32 f0; s32 f4; Node_119128* next; };
struct Holder_119128 { s32 f0; s32 f4; Node_119128* head; };
struct Args_119128 { s32 f0; Holder_119128* holder; };

void func_0011B5F0(void* p, s32 flag);
void func_0011A080(void* out, void* node, void* extra);
void func_0011B0A8(void* a, void* b);
void func_0011B060(void* p, s32 flags);
void func_0011B018(void* out, void* p);



struct Link_1194A8 { s32 f0; Link_1194A8* f4; Link_1194A8* f8; };
struct __attribute__((aligned(16))) Quad_1194A8 { s32 type; Link_1194A8* head; s32 w2; s32 w3; };
struct Ent_1194A8 { s32 f0; Link_1194A8* f4; Link_1194A8* f8; };
struct Owner_1194A8 { s32 f0; Ent_1194A8* f4; };

void* func_0011B008(void* q);
void func_0011B018(void* self, void* q);
void func_0011B538(void* q, s32 n);
void func_0011A080(void* t, void* n, void* c);
void func_0011B0A8(void* a, void* b);
void func_0011B060(void* q, s32 mode);
void func_00113AA8(void* a, s32 b, void* c, void* d);



// Fixed by merging the two flag tests into one "kind != 0x1B || p != 0".

struct __attribute__((aligned(16))) Quad_119310 { s32 kind; void* p; s32 w[2]; };
struct Node_119310 { s32 kind; Node_119310* f4; Node_119310* f8; };

s32 func_0011B008(Quad_119310* q);
void func_0011B018(void* out, Quad_119310* q);
void func_0011B060(Quad_119310* q, s32 mode);
void func_0011B0A8(Quad_119310* a, Quad_119310* b);
void func_0011B538(Quad_119310* q, s32 n);
void func_0011A080(Quad_119310* t, Node_119310* n, s32 c);



struct Quad_118F48 { s32 a, b, c, d; };
struct Obj_118F48 { u8 pad[4]; Quad_118F48* f4; };
struct Frame_118F48 { Quad_118F48 q; Quad_118F48 t; };

void func_0011B008(Quad_118F48* q);
void func_0011B018(void* dst, Quad_118F48* src);
void func_0011B060(Quad_118F48* q, int mode);
void func_0011B0A8(Quad_118F48* a, Quad_118F48* b);
void func_0011B538(Quad_118F48* q, int n);
void func_0011A080(Quad_118F48* t, void* n, s32 c);
void func_001E1F10(const char* x);
s32 func_00113730(Quad_118F48* t, s32 mode, void* a, s32 c);
extern const char D_00249200[];



struct Ent_11AB58;
struct Sub_11AB58 { s32 type; Ent_11AB58* ent; };
struct Node_11AB58 { Ent_11AB58* f0; Sub_11AB58 sub; Node_11AB58* fC; };
struct List_11AB58 { Node_11AB58* head; };
struct World_11AB58 {
    s32 count;
    Ent_11AB58* ents[0x140];
    s32 n504;
    List_11AB58* lists[1];
};
struct Item_11AB58 { void* fn; u8 p[8]; Ent_11AB58* fC; Item_11AB58* f10; };
struct Glob_11AB58 { u8 p[0x1EC8]; Item_11AB58* f1EC8; };

extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011C2B0(u8* p);
void func_0011C2E8(u8* p);
s32 func_0011C3C8(Ent_11AB58* e);
void func_0011C3F0(Ent_11AB58* e);
void func_0011A728(World_11AB58* w, Ent_11AB58* e);
void func_0011A770(World_11AB58* w, Ent_11AB58* e);
void func_0011A7B8(World_11AB58* w, Ent_11AB58* e);
void func_0011A850(World_11AB58* w);
void func_001834A0(void* a);



struct __attribute__((aligned(16))) Quad_1196C8 { s32 w[4]; };
struct Node_1196C8 { s32 kind; Node_1196C8* f4; Node_1196C8* f8; };

s32 func_0011B008(Quad_1196C8* q);
void func_0011B018(void* out, Quad_1196C8* q);
void func_0011B060(Quad_1196C8* q, s32 mode);
void func_0011B0A8(Quad_1196C8* a, Quad_1196C8* b);
void func_0011A080(Quad_1196C8* t, Node_1196C8* n, void* c);
void* func_0011A630(void);
void func_0011A358(Quad_1196C8* t, void* owner, Node_1196C8* kind, Quad_1196C8* body);
void func_0011A328(void* slot, void* c);



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
struct Inner_11A080 { s32 type; s32 f4; s32 f8; };
struct In_11A080 { s32 kind; Inner_11A080* inner; };
struct Ret_11A080;

void func_0011B008(Tmp_11A080* t);
void func_0011B018(Ret_11A080* dst, Tmp_11A080* src);
void func_0011B060(Tmp_11A080* t, s32 mode);
void func_0011B0A8(Tmp_11A080* dst, void* src);
void func_00118D48(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00118DB8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00118E80(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00118F48(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119030(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119128(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119218(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119310(Tmp_11A080* o, In_11A080* a, s32 b);
void func_001194A8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_001196C8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119878(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119970(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119AF8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119BB0(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119FA0(Tmp_11A080* o, In_11A080* a, s32 b);



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
struct Node_119BB0 { s32 f0; void* f4; Node_119BB0* f8; };
typedef void (*Fn1D_119BB0)(V_119BB0* ret, s32 n, V_119BB0* args, void* ctx);
struct Ent_119BB0 { Fn1D_119BB0 f0; s32 f4; s32 f8; };
typedef void (*Fn21_119BB0)(V_119BB0* ret, void* a, s32 n, V_119BB0* args);
struct O21_119BB0 { void* f0; Fn21_119BB0 f4; s32 f8; };
struct Def_119BB0 { s32 f0; Node_119BB0* f4; s32 f8; s32 fC; s32 f10; };

V_119BB0* func_0011B008(V_119BB0* q);
void func_0011B060(V_119BB0* q, s32 mode);
void func_0011B0A8(V_119BB0* a, V_119BB0* b);
void func_0011B018(V_119BB0* dst, V_119BB0* src);
void func_0011A080(V_119BB0* ret, Node_119BB0* n, void* ctx);
void func_0011B6C0(V_119BB0* q, V_119BB0* head);
void func_0011B538(V_119BB0* q, s32 n);
void* func_0011A630(void);
void func_0011A328(void* s, s32 v);
void func_0011A358(V_119BB0* ret, void* s, void* x, V_119BB0* arg);
void func_00119A58(V_119BB0* ret, s32 v, void* s);
extern Ent_119BB0 D_00259958[];



struct __attribute__((aligned(16))) Quad_119030 { s32 w[4]; };
struct Node_119030 { s32 pad0; Node_119030* f4; Node_119030* f8; };

void func_0011B008(Quad_119030* q);
void func_0011B018(void* out, Quad_119030* q);
void func_0011B060(Quad_119030* q, s32 mode);
void func_0011B0A8(Quad_119030* a, Quad_119030* b);
void func_0011B538(Quad_119030* q, s32 n);
void func_0011A080(Quad_119030* t, Node_119030* n, s32 c);



struct __attribute__((aligned(16))) Quad_118198 { s32 type; struct Node_118198* head; s32 w2; s32 w3; };
struct Ent_118198;
struct Node_118198 { s32 f0; Ent_118198* f4; Node_118198* f8; };
struct Pair_118198 { s32 a; s32 b; };
struct Src_118198 {
    s32 type;
    Node_118198* head;
    Pair_118198 p0;
    Pair_118198 p1;
};
struct Hit_118198 { Quad_118198 q[7]; };

struct Val_118198;
Val_118198* func_0011B008(Val_118198* q);
void func_0011B018(Val_118198* dst, const Val_118198* src);
void func_0011B060(Val_118198* q, s32 mode);
struct __attribute__((aligned(16))) Val_118198 {
    s32 type;
    Node_118198* head;
    s32 w2;
    s32 w3;
    Val_118198() { func_0011B008(this); }
    Val_118198(const Val_118198& o) { func_0011B018(this, &o); }
    ~Val_118198() { func_0011B060(this, 2); }
};
void func_0011B0A8(Val_118198* a, Src_118198* b);
s32 func_001419E8(Quad_118198* z, s32 a, s32 b, s32 c, Ent_118198** d, Hit_118198* e);
void func_0011B8A8(Node_118198* n, Ent_118198* e);
void func_0011B740(Node_118198* n, Quad_118198* q);
void func_0011B6C0(void* q, Node_118198* n);



struct Stk_11A850;

// One generic record: a queued event is { type, object, next }; the lists
// and the object table use the same words.
struct Obj_11A850 {
    s32 f0;
    Obj_11A850* f4;
    Obj_11A850* f8;
    Obj_11A850* fC;
    Obj_11A850* f10;
    Obj_11A850* f14;
};

// What func_0011A7D8 returns: a queue of records and two objects.
struct Batch_11A850 {
    Obj_11A850* f0;
    Obj_11A850* f4;
    s32 f8;
    s32 fC;
    Obj_11A850* f10;
};

Obj_11A850* func_0011A748(Stk_11A850* s);
void func_0011A770(Stk_11A850* s, Obj_11A850* o);
void func_0011A7B8(Stk_11A850* s, Obj_11A850* o);
void func_0011A728(Stk_11A850* s, Obj_11A850* o);
Batch_11A850* func_0011A7D8(Stk_11A850* s);
Obj_11A850* func_0011A790(Stk_11A850* s);
void func_0011C3F0(Obj_11A850* o);
s32 func_0011C3C8(Obj_11A850* o);



extern const char D_00249200[16] = "Splice assert: ";
