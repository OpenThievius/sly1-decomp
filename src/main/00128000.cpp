// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "animation.h"
#include "code_checksum.h"
#include "placed_object.h"
#include "switched_collider.h"
#include "world.h"
#include "attachment.h"
#include "shapes.h"
#include "range_record.h"
#include "globals.h"

typedef void (*Fn_2197C0)();
extern const Fn_2197C0 D_002197C0[10];
void* func_00121228(World* root, BaseObject* item, void* table);

void func_0012A4A0(void* self, s32 a1);

void func_00129730(void* self);

struct Sub_12A580 { u8 pad[0x40]; f32 f40; };

struct Sub_12A5B8 { u8 pad[0x40]; f32 f40; };

struct Vec16_12A5D0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A5D0 { u8 pad[0x50]; Vec16_12A5D0 v50; };

extern u8 D_00275C40[];

struct __attribute__((packed)) U64_12A630 { u64 v; };
struct Sub_12A630 { u8 pad[0x60]; U64_12A630 v60; };

extern u8 D_00275C60[];

struct Vec16_12A6A0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6A0 { u8 pad[0x70]; Vec16_12A6A0 v70; };

void* func_001291D0(f32 x);
void func_001B1DA8(void* p, f32 x);

extern u8 D_0027B520[];
void func_001B1AC8(void* p);

struct Sub_129510 { u8 pad[0x44]; f32 f44; };

extern u8 D_00260E80[];
void* func_0018D500(s32 n);

struct __attribute__((aligned(16))) Quad_129F58 { s32 v[4]; };

extern u8 D_00260EC0[];
void func_0012A320(void* self, f32* v);

void func_0012A3E8(void* self, s32 flag);

struct Sub_12A770 { u8 pad[0x44]; void* f44; };

void* func_00185468(void* p);

struct Ctx_12AA28 { u8 pad[0x90]; void* field; };

Ctx_12AA28* func_0012A970(void* self);

struct Inner_12AC88 { s32 value; };

struct Inner_12AD98 { u8 pad[0xC]; f32 value; };

void func_0012ABA8(void* self, f32 f);

struct Inner_12AEB0 { u8 pad[0x1C]; void* ptr; };

void func_001BF7F8(void* p);

struct Entry_12B0B0 { s32 w[16]; } __attribute__((aligned(16)));

extern Entry_12B0B0 D_00260F00[4];

void func_0012B040(void* self);

struct Obj_12B2E8 { u8 pad[0xC]; u32 value; };

struct Part_128DB8 {
    u8 pad0[0x60];
    BaseObject* p60;
    BaseObject* p64;
    u8 pad68[0x18];
    s32 f80;
    BaseObject* p84;
    void* p88;
    u8 pad8c[0xB0 - 0x8C];
    s32 flags;
};

BaseObject* func_0015A448(void* a0, void* a1, void* a2);
void* func_0015A868(void* a0, s32 a1);

struct Timer_129108 { u8 pad0[4]; s32 f4; s32 f8; s32 fC; f32 f10; };

void* func_0018D5C0(s32 size);

void* func_001B5EE0(void* a0);
void func_001B1AC8(void* a0);
void func_00152470(void* a0, void* a1);

struct Sub_12A7F8 { u8 pad0[0x48]; s32 f48; };

struct Sub_12A810 { u8 pad0[0x20]; s32 f20; };

void func_00129730(PlacedObject* self);

struct Sub_12A848 { u8 pad0[0x20]; s32 f20; };

struct Sub_12A8B8 { u8 pad0[0x4C]; s32 f4C; };

struct Sub_12A8C8 { u8 pad0[0x4C]; s32 f4C; };

void* func_0015A418(s32 a0, s32 a1, s32 a2, void* a3);
void* func_0011E580(s32 a0, s32 a1, void* a2, s32 a3, s32 a4);

void* func_001291D0(void* self);
void func_001B1CF8(void* self, s32 value);

void* func_001291D0(void* self, f32 x);
void func_001B1D70(void* self, f32 v);

struct __attribute__((aligned(16))) Quad_12A028 { s32 w[4]; };

extern u8 D_00260E90[];

struct __attribute__((aligned(16))) Quad_12A0F8 { s32 w[4]; };

extern u8 D_00260EA0[];

struct Sub_12ACD8 { u8 pad0[4]; f32 value; };

struct Sub_12ACF8 { u8 pad0[8]; f32 value; };

void func_0012ABA8(PlacedObject* self);

struct __attribute__((packed)) Rec_12AD30 { s32 a; s32 b; };
struct Sub_12AD30 { u8 pad0[0x14]; Rec_12AD30 rec; };

struct Sub_12AD78 { u8 pad0[8]; f32 value; };

s32 func_00182FC8(PlacedObject* self);
void func_00143AF8(Camera* a, PlacedObject* self);
void func_00143B20(Camera* a, PlacedObject* self);

void func_001B1FB0(void* self, f32 x);

void func_001B1FE0(void* self, f32 x);

void func_001B2010(void* self, f32 x);

void func_001B2068(void* self, void* src);

typedef u64 Quad_129EE0 __attribute__((mode(TI)));
struct Frame_129EE0 { Quad_129EE0 r; Quad_129EE0 a; Quad_129EE0 b; };

void func_00118CF0(Quad_129EE0* out, void* src);
void* func_00118D10(Quad_129EE0* out, void* src);
Quad_129EE0 func_00118D30(Quad_129EE0 a, Quad_129EE0 b);
Quad_129EE0 func_00118D20(Quad_129EE0* out, Quad_129EE0 v);
void func_00129F58(void* self, Quad_129EE0* src);

struct __attribute__((packed)) Vec4_12A150 { f32 x, y, z, w; };
struct Vec4F_12A150 { f32 x, y, z, w; };
extern Vec4F_12A150 D_00260EB0;

void func_0012A200(PlacedObject* self, Vec4_12A150* src);

void* func_0018D500(s32 size);

struct Part_0012AC08 { void* link; f32 f4; f32 f8; f32 fc; f32 f10; u8 sub14[8]; u8 sub1C[4]; f32 f20; };

s32 func_00182FC8(void* self);

struct __attribute__((packed)) Pack4_12A2C0 { f32 a, b, c, d; };

extern void func_0012A320(PlacedObject* self, Pack4_12A2C0* in);

struct __attribute__((packed)) Pack4_12A320 { f32 a, b, c, d; };

void* func_0018D500(u32 size);

struct Part_12AE20 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };

void func_001BF8E8(void* p);

struct Part_12AE58 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };

struct Node_129450 {
    u8 pad[2];
    s16 value_2;
};

struct Sub_129480 {
    u8 pad[4];
    f32 value_4;
};

void* func_00129400(void* self);

struct Node_129C20 {
    u8 pad0[0x10];
    Node_129C20* f10;
    u8 pad1[4];
    void* f18;
    void* f1C;
};

s32 func_001833F0(void* key, s32 item);

s32 func_00123DC0(void* a);
s32 func_00123E00(void* a);

struct __attribute__((packed)) U64_12A700 { u64 v; };
struct Sub_12A700 { u8 pad[0x80]; U64_12A700 v80; };

struct Part_12AE78 { u8 pad[0x10]; f32 value; };

struct Part_12AEE8 { u8 pad[0x10]; f32 value; };

struct Inner_0012B238 { u8 pad[0x30]; f32 value; };

struct Sub_1294B0 { u8 pad[8]; f32 f8; };

struct Sub_1294E0 { u8 pad[0x40]; f32 f40; };

typedef u64 Quad_129E10 __attribute__((mode(TI)));
struct Frame_129E10 { Quad_129E10 r; Quad_129E10 a; Quad_129E10 b; };

extern u8 D_00260E70[];

void func_00118CF0(Quad_129E10* out, void* src);
void* func_00118D10(Quad_129E10* out, void* src);
Quad_129E10 func_00118D30(Quad_129E10 a, Quad_129E10 b);
Quad_129E10 func_00118D20(Quad_129E10* out, Quad_129E10 v);
void func_00129E88(void* self, Quad_129E10* v);

struct Sub_12A7A8 { u8 pad[0x44]; s32 v44; };

struct __attribute__((packed)) U64_12AF00 { u64 v; };
struct Sub_12AF00 { u8 pad[0x14]; U64_12AF00 p14; };

// Newly matched US functions from the small-function wave.
extern void func_0012A430(void*, s32);
extern void func_001BE4D8(void*);
struct Quad_129598 { s32 words[4]; } __attribute__((aligned(16)));
struct Result_129598 { u8 pad[0x30]; Quad_129598 value; };
struct Node_129B98 { u8 pad0[8]; void* item; void* owner; u8 pad2[0x34 - 0x10]; Node_129B98* next; };
extern s32 func_001833F0(void*, s32);
struct State_12A430 { u8 pad[0x10]; u8 value; };
extern void func_001296E0(void*);
struct State_12A4A0 { u8 pad[0x11]; u8 value; };
struct State_12A4E8 { u8 pad[0x14]; s32 value; };
extern void func_00129A58(void*);
struct State_12A7C0 { u8 pad[0x48]; s32 value; };
extern void func_00129730(void*);
extern void func_0012ABA8(void*);
struct Inner_12ABD0 { s32 value; };
extern void func_001BF788(void*, s32);
struct Inner_12B010 { u8 pad[0x1C]; void* resource; };
extern void func_0012B040(void*);
struct Vec_12B140 { s32 v[4]; } __attribute__((aligned(16)));
struct Vec_12B1A0 { s32 v[4]; } __attribute__((aligned(16)));

struct Sub_00129540 { u8 pad[4]; f32 value; u8 gap[0x38]; f32 scale; };
f32 func_00205778(f32 a, f32 b);

struct Sub_0012AA00 { u8 pad[0x8C]; f32 value; };

void func_001B5388(void* part, f32 a, f32 b);

void func_00159A00(void* part, f32 value);

extern Entry_12B0B0 D_00261000[2];

void func_001BF788(void* ptr, s32 value);

struct Node_1299E0 { u8 pad0[8]; Node_1299E0* next; u8 pad1[8]; s32 key; };

void func_00152540(void* list, Node_1299E0* before, Node_1299E0* value);

void func_00152600(void* a, void* b);
void func_00152470(void* list, void* item);

void func_00188FD8(void* a, f32* out);

struct Local_129648 { f32 tmp[4]; f32 out[4]; u8 pad[0x20]; };

void func_00188A20(void* a, void* b);

void func_00182C18(void* self);
void func_00152438(void* self, s32 value);

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)
struct Part_0012AC08R { void* link; f32 f4; f32 f8; f32 fc; f32 f10; u8 sub14[8]; void* sub1C; f32 f20; };

void func_001BF788(void* self, s32 n);
void func_001BFCD8(void* a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, void* a2, s32 a3, void* a4, s32 a5);

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)
struct __attribute__((packed)) Rec_0012AF38 { s32 a; s32 b; };
struct Part_0012AF38 { void* link; f32 f4; f32 f8; f32 fc; f32 f10; Rec_0012AF38 rec14; void* sub1C; f32 f20; };

// NEAR: same bytes except the prologue order: retail loads the crc word and the table base before the n > 0 test (lw v0, addiu t1, then blez); ours tests first

void func_001837E0(void* self, s32 a, s32 b, s32 c);

s32 func_00137D10(Stream83* p);
s32 func_00137BE0(Stream83* p);
s32 func_00137CC0(Stream83* p);
s32 func_00137B90(Stream83* p);
void func_0012D2A8(Animation* a, Track83* b);
void func_0012BC38(Animation* a, Stream83* b, s32 c, s32* d, s32* e);
void func_0011EC40(Animation* a, Stream83* b);
T2196_Pos* func_00120FB0(s32 cc);
T2196_Rot* func_00121050(s32 cc);
T2196_Scale* func_001210F0(s32 cc);
T2196_Weight* func_00121160(s32 cc);

struct Sub_12B5B8 {
    u8 pad0[0x60];
    void* f60;
    u8 pad1[0xB0 - 0x64];
    s32 fB0;
};

void* func_0018D5C0(s32 bytes);
void func_00128018(void* a, void* b, void* c, void* d);
void func_00128150(void* a, void* b, void* c, void* d);

s32 func_00137C40(void* a);
void* func_0018D5C0(u32 n);
void func_00137EB0(void* a, void* b);
s32 func_00137D10(void* a);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00137E70(void* a, void* b);
f32 func_00137DF8(void* a);
f32 func_001EA408(f32 a);
s32 func_00137B90(void* a);

typedef u64 Quad_129FB0 __attribute__((mode(TI)));
struct Frame_129FB0 { Quad_129FB0 r; Quad_129FB0 a; Quad_129FB0 b; };

void func_00118CF0(Quad_129FB0* out, void* src);
void* func_00118D10(Quad_129FB0* out, void* src);
Quad_129FB0 func_00118D30(Quad_129FB0 a, Quad_129FB0 b);
Quad_129FB0 func_00118D20(Quad_129FB0* out, Quad_129FB0 v);
void func_0012A028(PlacedObject* self, Quad_129FB0* src);

typedef u64 Quad_12A080 __attribute__((mode(TI)));
struct Frame_12A080 { Quad_12A080 r; Quad_12A080 a; Quad_12A080 b; };

void func_00118CF0(Quad_12A080* out, void* src);
void* func_00118D10(Quad_12A080* out, void* src);
Quad_12A080 func_00118D30(Quad_12A080 a, Quad_12A080 b);
Quad_12A080 func_00118D20(Quad_12A080* out, Quad_12A080 v);
void func_0012A0F8(PlacedObject* self, Quad_12A080* src);

extern u8 D_00219560[];

void func_001299E0(PlacedObject* self, void* src);

extern u8 D_0021A790[];

struct Node_129D00 { u8 pad0[0x14]; void* w14; };

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_002195D8[];
void func_001299E0(PlacedObject* self, Node_129D00* n);

void func_001853F0(void* a, void* b, void* c);

extern const Fn_Table D_00219600[];

struct Inner_0012A8D8 {
    u8 pad0[0x11];
    u8 f11;
    u8 pad1[0x1C - 0x12];
    f32 f1C;
    f32 f20;
};

void func_001299E0(PlacedObject* self, Inner_0012A8D8* src);

struct __attribute__((aligned(16))) Quad_12B180 { s32 a, b, c, d; };

struct __attribute__((aligned(16))) Quad_12B1E0 { s32 a, b, c, d; };

void func_001F5C0C(void** p, s32 v, s32 n);
void func_00129DF8(PlacedObject* self);
void func_001226D8(Attachment* n);

struct Rd_12BC38;
struct Rec_12BC38 { f32 t; s32 kind; s32 w8; s32 wC; };
struct Sub_12BC38 { s32 w0; s32 w4; s32 w8; s32 wC; s32 w10; };
struct Ev_12BC38 {
    s16 h0, h2;
    u8 pad4[0xA];
    s16 hE, h10;
    u8 pad12[2];
    s32 w14, w18;
    f32 f1C, f20, f24;
};
struct Grp_12BC38 { s16 n; s16 h[1]; };

s32 func_00137CC0(Rd_12BC38* r);
void* func_0018D5C0(s32 n);
void func_00138550(Rd_12BC38* r, void* out);
s32 func_00137D10(Rd_12BC38* r);
s32 func_00137D78(Rd_12BC38* r);
f32 func_00137DF8(Rd_12BC38* r);
s32 func_00137B90(Rd_12BC38* r);
s32 func_00137BE0(Rd_12BC38* r);
void func_00137A60(Rd_12BC38* r, s32 n, void* dst);
void func_001384A0(Rd_12BC38* r, void* out);

#define F32(x) (*(f32*)&(x))
#define H0(x) (*(s16*)&(x))
#define H2(x) (*((s16*)&(x) + 1))

struct Entry_12B2F8 { s32 key; s32 val; };
struct St_12B2F8 {
    u8 pad0[0x13]; s8 f13; u8 pad14[0x24]; void* f38; s32 f3C;
    s32 Set(s32 v) { s32 o = f13; f13 = v; return o != v; }
};
extern const Fn_Table D_002195B0[];

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001212D8();
void func_00121358();
void func_00122890();
void func_00122920();
void func_00122968();
void func_001229C0();
void func_001229E0();
f32 func_00122A00();
void func_00122A18();
void func_00122A80();
void func_00122B30();
void func_00122C48();
void func_00122CB0();
f32 func_00122D90();
void func_0011EF40();
void func_0011EF48();
void func_0011EF60();
void func_0011EF68();
void func_0011EF70();
void func_0011EF88();
void func_0011EF90();
void func_0011EFA8();
void func_0011EFB0();
void func_001214B8();
void func_00121568();
void func_00121580();
f32 func_001215A8();
void func_00122DA0();
void func_00122DE0();
extern const Fn_Table D_002195B0[10] = { (Fn_Table)func_00122890, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0, (Fn_Table)func_00122920, (Fn_Table)func_00122968, (Fn_Table)func_001229C0, (Fn_Table)func_001229E0, (Fn_Table)func_00122A00, 0 };
extern const Fn_Table D_002195D8[10] = { (Fn_Table)func_00122A18, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0, (Fn_Table)func_00122A80, (Fn_Table)func_00122B30, (Fn_Table)func_00122C48, (Fn_Table)func_00122CB0, (Fn_Table)func_00122D90, 0 };
extern const Fn_Table D_00219600[26] = { (Fn_Table)func_00122DA0, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0, (Fn_Table)func_001214B8, (Fn_Table)func_00122DE0, (Fn_Table)func_00121568, (Fn_Table)func_00121580, (Fn_Table)func_001215A8, 0, (Fn_Table)func_0011EF40, 0, (Fn_Table)func_0011EF48, 0, (Fn_Table)func_0011EF60, (Fn_Table)func_0011EF68, 0, (Fn_Table)func_0011EF70, (Fn_Table)func_0011EF88, 0, (Fn_Table)func_0011EF90, 0, (Fn_Table)func_0011EFA8, 0, (Fn_Table)func_0011EFB0, 0 };

struct Context_001288F0;
struct List_001288F0 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_001288F0 { List_001288F0* list; u8* link; s32 offset; Iter_001288F0* saved; };
s32 func_001C1A28(Context_001288F0* context, PlacedObject** obj);

struct Next_001288F0 {
    static PlacedObject* Of(Iter_001288F0* it)
    {
        PlacedObject* obj = *(PlacedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_001288F0 {
    static void Of(Iter_001288F0* it, List_001288F0* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_001288F0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Node_129A58 { u8 pad0[8]; Node_129A58* next; u8 padC[8]; s32 key; };

void func_00152600(List01* list, Node_129A58* node);
void func_00152540(List01* list, Node_129A58* at, Node_129A58* node);

struct Begin_129A58 {
    static void Of(Iter_001288F0* it, List01* list)
    {
        it->list = (List_001288F0*)list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_001288F0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_129A58 {
    static Node_129A58* Of(Iter_001288F0* it)
    {
        Node_129A58* node = *(Node_129A58**)it->link;
        it->link = (u8*)node + it->offset;
        return node;
    }
};

void func_00121338();
void func_00122F88();
void func_00122F28();
void func_00122FE0();
void func_00123120();
void func_00123270();
void func_001232E8();
void func_00123358();
extern const Fn_2197C0 D_002197C0[10] = {
    func_00121338, func_00122F88, func_00122F28, 0, func_00122FE0,
    func_00123120, func_00123270, func_001232E8, func_00123358, 0
};

extern u8 D_00148D64[];
void func_00123ED0(void* self);

