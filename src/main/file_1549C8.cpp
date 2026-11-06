// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x1549C8 to 0x15F678: the methods of classes 0x50, 0x77 to 0x7A, 0x60 and 0x40, the effect
// helpers between them, the font and text drawing (its GCC vtable D_0024A220) and the packet
// writers' frame code, ending with the static initialiser func_0015F618 and _GLOBAL_$I$
// func_0015F658. One file between two edges; it could be several.
#include "common.h"
#include "effect_spawner.h"
#include "asm_func.h"
#include "effect_owner.h"
#include "effect.h"
#include "shapes.h"
#include "active_set_solver.h"
#include "list_iter.h"
#include "transform_object.h"
#include "cursor_animator.h"
#include "object_cycler.h"
#include "c60.h"
#include "world.h"
#include "globals.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "base_object.h"
#include "v24a0.h"
#include "v24a2.h"
#include "render_frame.h"
#include "text_reader.h"
#include "layout_137228.h"


void func_00155F90();
void func_00155FA0(EffectSpawner* self);

void* func_00155778(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

void* func_00158DD8(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

struct __attribute__((aligned(16))) Quad_001566C8 { s32 a, b, c, d; };
struct Msg_001566C8 {
    s32 kind;
    u8 pad0[0x20 - 4];
    Quad_001566C8 q;
    s32 zero;
    f32 f;
    u8 pad1[0x50 - 0x38];
};
struct Game_001566C8 {
    u8 pad0[0x1D0C];
    void* f1D0C;
};
typedef void (*VFn_001566C8)(void* self, void* msg);


struct Obj_1550B8;
typedef void (*VFn_1550B8)(Obj_1550B8* self, void* arg);
struct Sub_1550B8 { u8 pad[0x7C]; void* value; };
struct Obj_1550B8 { VFn_1550B8* vtbl; u8 pad[0x2D0 - 4]; Sub_1550B8* sub; };

extern f32 D_0026185C;

struct Frame_157E00 {
    s32 out[4];
    s32 flag;
    s32 pad[3];
    s32 pair[2];
    u8 tail[0x18];
};

void func_0018D608(void);
void func_0018D6F0(void);
void func_001579B0(void* a, void* b, s32* out);
void func_00157320(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3);
void func_00157B88(void* a, void* b, s32* out, s32* pair);
void func_001575D8(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3, s32 p0, s32 p1);

struct Word_154EE0 {
    s32 value;
};

struct Buffer_154EE0 {
    u8 pad0[0x4C];
    s32 cap;
    U32P* items;
    void* source;
};

void* func_0018D500(s32 size);
void* func_00137B90(void* src);
Word_154EE0 func_00137C40(void* src);

void* func_0018D500(s32 size);
void func_001549C8(void* mem);
void func_001289C0(void* self, s32 count);
s32 func_00137CC0(s32 count);
T2176* func_0014D9A8(s32 kind);
void func_00154C80(void* self, s32 count);
s32 func_00137BE0(s32 count);
void* func_00155778(void* self, s32 flag);
void func_00154EE0(void* self, s32 count, void* unused, s32 src);

void func_00127048(void* self);

struct Rec_001550E8 { u8 pad00[0x18]; void* f18; u8 pad1C[0x18]; s32 f34; };

void func_001249A8(EffectSpawner* self);
Rec50* func_00155778(EffectSpawner* self, s32 mode);
void func_00158288(Rec50* p, EffectSpawner* self);
Rec_001550E8* func_0015A418(void* a0, s32 a1, s32 a2, EffectSpawner* a3);
s32 func_001300E8(Rec_001550E8* p, s32 k);
void* func_001DBCC8(void* a0, void (*cb)(void), EffectSpawner* a2, s32 a3, s32 a4);

void* func_0018D568(s32 size, void* owner);

extern f32 D_0026185C;

struct Obj_156000;

void func_00155F90();
void func_00155FA0(Obj_156000* self);

struct Obj_156030;

s32 func_00155FB0(Obj_156030* self);

void func_00123ED0(void*);
void func_00152438(void*,s32);

void func_00158198(void*,void*,void*,f32,f32,f32,f32,void*);

void func_0013A128(void*,void*);
void func_0019E158(void*,void*);
f32 func_001EAAE0(f32,f32);

void* func_001F5C0C(void*,s32,s32);

struct Item_154880 {
    u8 pad0[0x34];
    f32 f34;
    f32 f38;
    u8 pad1[0x44 - 0x3C];
    void* p44;
    u8 pad2[0x60 - 0x48];
};


void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D658(s32 size);
void func_0018D800(void* dst, void* src, s32 size);
void func_00153528(ActiveSetSolver* loc, s32 count);
void func_00152470(void* tmp, Item_154880* item);
void func_00153EC0(ActiveSetSolver* loc, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

struct __attribute__((aligned(16))) Q_157320 { s32 a, b, c, d; };
struct Hdr_157320 { u8 pad[4]; s32* f4; s32 f8; };
EffectOwner* func_0019E040(u8* ctx, s32 flag);
void func_0019E158(EffectOwner* a, Rec50* b);
Effect* func_0019EA78(s32 a, EffectOwner* b);
void func_001A0338(EffectOwner* self, s32 kind, Effect* extra);
void func_001583E8(Effect* a, Rec50* b);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_00152720(void* p);

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))
typedef void (*VFn)();

struct Span_00156FC8 {
    f32 lo;
    f32 hi;
};

struct Slot_00156FC8 {
    s32 count;
    f32 step;
    f32 rate;
    f32 phase;
    f32 out10;
};

f32 func_001EA408(f32 x);
f32 func_001EAAE0(f32 a, f32 b);


typedef void (*VFn_157FF8)(void* self, void* frame);

struct __attribute__((aligned(16))) Quad_157FF8 { s32 a, b, c, d; };

struct Frame_157FF8 {
    s32 kind;
    u8 pad0[0x1C];
    Quad_157FF8 pos;
    f32 f30;
    s32 f34;
    void* f38;
    u8 pad1[0xC];
};

struct Sub_157FF8 { u8 pad0[0x120]; s32 f120; u8 pad1[0x8C]; s32 f1B0; };

struct Elem_157FF8 { VFn_157FF8* vtbl; u8 pad0[0x8C]; Sub_157FF8* f90; };

struct List_157FF8 { u8 pad0[0x90]; s32 count; Elem_157FF8* items[1]; };

struct Owner_157FF8 { u8 pad0[0x1CE8]; List_157FF8* list; };

struct __attribute__((aligned(16))) Blk_157EF8 { Quad16 q[8]; };
struct __attribute__((aligned(16))) Tail_157EF8 { Quad16 q[4]; };
void* func_001F5C0C(void* p, s32 v, u32 n);
struct Pair_157EF8 { s32 z; s32 b; s32 c; Pair_157EF8() { func_001F5C0C(this, 0, sizeof(*this)); } };
struct __attribute__((aligned(16))) Frame_157EF8 { u8 pad0[0x20]; Quad16 self_copy; u8 pad1[0x30]; Quad16 a1_copy; u8 pad2[0x30]; Blk_157EF8 blk; s32 f120; u8 pad3[0x8C]; Tail_157EF8 tail; u8 pad4[0x10]; };

void func_001549C8(void* mem);
void func_00157E00(void* a, void* b, void* c);


struct Item_158108 { u8 pad0[0xC]; s32 fC; };
struct Owner_158108 { u8 pad0[0x278]; Item_158108* f278; };
typedef void (*VFn_158108)(Effect* self, void* a, s32 z, f32 f);

void* func_0019EA78(s32 a, s32 b);

void func_00182C58(void* a0);

struct Blob_158730 { u8 data[0x50]; };


struct __attribute__((aligned(16))) Quad_158778 { s32 a, b, c, d; };
struct Msg_158778 {
    s32 a;
    s32 b;
    u8 pad0[8];
    Quad_158778 q1;
    Quad_158778 q2;
    f32 x;
    f32 y;
    u8 pad1[0x50 - 0x38];
};

void func_001830D8(void* self);
C77* func_00183058(void* a, void* b, void* c);

void func_001B4AD0(CursorAnimator* self);
AnimRecord* func_001B4688(s32 key);
void func_00159770(CrossfadeAnimator* self, s32 mode);

typedef void (*VFn_159AD0)(void* self);
struct Sub_159AD0 { VFn_159AD0* vtbl; };
struct Obj_159AD0 {
    Sub_159AD0* f0;
    f32 f4;
    f32 f8;
};

s32 func_00182FC8(void* obj);
void func_00159C28(Obj_159AD0* self);
extern PackedFloatPair D_00262180;
extern PackedFloatPair D_00262188;
extern PackedFloatPair D_00262190;
extern PackedFloatPair D_00262198;
extern PackedFloatPair D_002621A0;
extern PackedFloatPair D_002621A8;
extern PackedFloatPair D_002621B0;
extern PackedFloatPair D_002621B8;
extern PackedFloatPair D_002621C0;

void func_001B7968(Collider* self);
void func_00152470(List01* a, ObjectCycler* b);

void* func_001556E8(void* x);

struct Rec_158C60;
Rec_158C60* func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
s32 func_001300E8(void* self, s32 kind);

struct __attribute__((aligned(16))) Quad_158F80 { s32 a, b, c, d; };
struct Body_158F80 { Quad_158F80 q[5]; };
struct Rec_158F80 { void* owner; u8 pad0[0xC]; Body_158F80 body; f32 f60; };

extern f32 D_00261858[];

void* func_001B5EA0(void* p);
void func_00152450(void* p);
void func_00152470(void* list, void* item);
void func_001590A0(void* self, void* body);

void func_001BE4D8(void* p);

typedef void (*VFn_159478)(void* self);
struct Node_159478 { VFn_159478* vtbl; u8 pad0[0x7C]; void* owner; u8 pad1[0xC]; s32 count; void* items[8]; };

void* func_0011E580(s32 a0, void* a1, void* a2, s32 a3, s32 a4);
void func_0018D800(void* dst, void* src, s32 size);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

struct Rec_158C60 {
    u8 pad0[0x18];
    void* f18;
    u8 pad1[0x20 - 0x1c];
    s32 f20;
    u8 pad2[0x34 - 0x24];
    s32 f34;
    u8 pad3[0x7c - 0x38];
    Rec_158C60* f7c;
};

Rec_158C60* func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
void func_00158288(Rec79* rec, C79* self);

extern f32 D_0026185C;
f32 func_001EAAE0(f32 a, f32 b);

extern f32 D_0026185C;
f32 func_001EAAE0(f32 a, f32 b);
void func_001B46E0(AnimCursor* cur, s32 idx);


void* func_0018D5C0(s32 size);
void func_001549C8(void* p);
s32 func_00137CC0(void* other);
T2176* func_0014D9A8(s32 kind);
void* func_00137BE0(void* other);
void func_00154C80(void* p, void* other);
void func_00154EE0(void* a, void* b, void* c, void* d);
extern s32 D_002621E0[6];

void func_00124DF8(void* self, s32 n, void* p);
f32 func_001EAAE0(f32 a, f32 b);
void func_0015B7B8(ObjectCycler* self, s32 x);
void func_00124A48(void* self);

struct Node_159BB0 { PlacedObject* owner; };


void* func_001B5EE0(void* where);
void func_00152470(void* where, Node_159BB0* node);

struct Owner_159C28 { u8 pad[0x294]; s32 flag294; s32 flag298; };
struct Node_159C28 { Owner_159C28* owner; };


void func_00152600(void* where, Node_159C28* node);
void func_001B5F28(void* where, Node_159C28* node);
void func_001B5F28(void* l, void* n);

extern f32 D_00261860;
void func_00124FC0(void* self);
f32 func_001EA4B8(void* p, s32 zero, f32 a, f32 b, f32 c);

struct Frame_15A9A8 { Quad16 q0; u8 pad1[0x30]; Quad16 m40[4]; u8 pad2[0x10]; Quad16 m90[4]; };

void func_0018A008(s32 zero, void* out, f32 v);
void func_00125B70(void* obj, void* c, void* out);
void func_00188668(Quad16* out, void* b, Quad16* in);
void func_001261C0(void* obj, void* b, void* m);


struct Frame_159CA0 { u8 buf[0x2C0]; s32 value; };

void func_00168770(void* buf, s32* value, s32 flag);
void func_00152B38(void* self);
void func_001EE7D0(void* self, s32 n, void* buf, s32 flag);
void func_00152D70(void* self);

extern f32 D_0026185C;

struct Ctx_159ED0 { u8 pad0[0x54]; f32 f54; u8 pad58[4]; s32 f5C; };

void func_00152470(void* list, void* item);

s32 func_0015A198(void*,s32,s32,void*,s32,void*);

void func_001289C0(void*,void*);
s32 func_001E4C48(void*,void*,void*,void*,void*);

AnimCursor* func_001B4B48(CursorAnimator* self, const AnimRecord* key);

void func_00158198(void*,void*,void*,f32,f32,f32,f32,void*);

struct __attribute__((aligned(16))) Quad_15B720 { s32 a, b, c, d; };
struct Rec_15B720 {
    u8 pad0[0x8];
    f32 f8;
    s32 fC;
    u8 pad1[0x20 - 0x10];
    Quad_15B720 f20;
    Quad_15B720 f30;
};
struct __attribute__((aligned(16))) Local_15B720 {
    s32 f0;
    u8 pad0[0x10 - 0x4];
    Quad_15B720 f10;
    Quad_15B720 f20;
    u8 pad1[0x50 - 0x30];
};

void func_0015B7B8(void* self, s32 x);
void func_001BC0E0(void* a0, f32 x, void* a1, void* a2);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void func_001BA130();
s32 func_001526D0(void* sub, ObjectCycler* self);
void func_00152600(void* data, ObjectCycler* self);
void func_001BFCD8(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void func_001BF788(void* self, s32 n);
void func_001BFCD8(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);

struct __attribute__((aligned(4))) Out_159D00 { u8 c[4]; };
struct Req_159D00 { void* fn; f32 f; s32 mode; u8 pad[0x54]; Out_159D00 col; u8 pad2[0x1C]; };
extern s32 D_00275BC4;

extern s32 D_00270458;
extern f32 D_0026185C;
void func_00152600(u8* a, ColorFade* b);
void func_00159CA0(ColorFade* o);
void func_0019D410(Req_159D00* r);

struct Entry_158198 {
    s32 a;
    s32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    u8 pad0[0x10];
};

struct Emitter_158198 {
    s32 kind;
    u8 pad0[0xC];
    s32 count;
    Entry_158198* entries;
};

void* func_0018D5C0(s32 bytes);

typedef void (*Fn1_1587C8)(void* self, void* arg);

struct Link_1587C8 { void* item; u8 pad0[4]; Link_1587C8* next; };
struct Node_1587C8 { void** vtbl; u8 pad0[0x2CC]; Link_1587C8* list; };

s32 func_00137D10(void* src);
s32 func_001300E8(void* node, s32 kind);
void* func_0011E580(s32 a0, void* a1, void* a2, s32 a3, s32 a4);

struct Node_15A4B8 { Node_15A4B8* next; s32 value; };

extern u8 D_00247448[];

s32 func_00182FC8(PlacedObject* o);

typedef int V128_15B128 __attribute__((mode(TI)));

extern f32 D_00261858[];

void func_001B93F8(ObjectCycler* self);
void func_0015B7B8(ObjectCycler* self, s32 mode);
s32 func_0015BEF0(ObjectCycler* self);
s32 func_0015BD48(ObjectCycler* self, V128_15B128* out);
void func_0015BC78(ObjectCycler* self);
s32 func_0015C0A0(ObjectCycler* self);
s32 func_0015BFC0(ObjectCycler* self);
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_00123ED0(void* self);

struct Iter_00159588;
extern f32 D_00261858[];

struct Node_00159588 { void* f0; u8 pad4[0xC]; u8 body[0x50]; f32 f60; };
struct Iter_00159588 { List01* list; u8* link; s32 offset; Iter_00159588* saved; };

void func_001590A0(void* a, void* b);
void func_00152600(List01* list, Node_00159588* node);
void func_001B5F28(Pool6C* set, Node_00159588* node);

struct Next_00159588 {
    static Node_00159588* Of(Iter_00159588* it)
    {
        Node_00159588* obj = *(Node_00159588**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00159588 {
    static void Of(Iter_00159588* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00159588*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};
extern s32 D_002621C8[6];

void func_001BAC30(ObjectCycler* self, void* arg);
void func_00124DF8(ObjectCycler* self, s32 n, void* table);
void func_00159478(void** out, ObjectCycler* self);
s32 func_0015A480(u8* self, s32 kind, ObjectCycler* arg);
void func_00182ED8(s32 a);
s32 func_001526D0(List01* sub, ObjectCycler* self);
void func_00152600(List01* data, ObjectCycler* self);

struct Out_15B4D0 { u8 pad[0x40]; f32 scale; u8 pad2[0x10 - 4]; };
extern f32 D_0026185C;
extern f32 D_00262230[4];
extern f32 D_00262240[4];
extern f32 D_00275C60[];
void func_00125B70(ObjectCycler* self, void* c, void* out);

s32 func_001300E8(PlacedObject* obj, s32 id);
s32 func_00182FC8(PlacedObject* obj);
s32 func_0015A4B8(u32 i, s32 id);
void func_00159F48(PlacedObject* obj, s32 kind, s32 all, s32 zero, PlacedObject* root, s32 max,
                   s32* countOut, PlacedObject** found, s32* minOut);

void func_001B4AA0(CursorAnimator* self, const AnimatorParams* src);


struct VEnt_0024A220 { s32 delta; void (*fn)(); };
struct Vec2_24A210 { f32 x; f32 y; };
extern const VEnt_0024A220 D_0024A220[22];
void* func_0018D758(u32);
void func_0015C9B0(V24A2*, V24A2*);

extern s32 D_00262268[];
extern s32 D_0026227C;

V24A2_Glyph* func_0015DAB8(V24A2* a, s32 b);

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

struct Frame_15EB20 {
    u8 scratch[0x80];
    u8 obj[0x30];
};

extern u8 D_00212160[];
extern u8 D_00215C50[];

void* func_001611B8(void* p);
void func_001529C8(void* p, s32 n, void* q);
void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, s32 b);
void func_00161200(void* p);
void func_001EE450(void* self);
void func_001EE8D0(void* self, void* p);
void func_0015EAE0(void* self, void* a, void* b);
void func_00152D30(void* self);
void func_001529E0(void* self, void* p, s32 n);

void func_0015C260(V24A2* self, V24A2* dst);

V24A2_Glyph* func_0015DAB8(V24A2* table, s8 key);

void func_00152D70(void* obj);
void func_00152B80(void* obj, s32 a, s32 b);
void func_00152B38(void* obj);

void func_0015C2E8(V24A2* a0, s32 a1, void* a2);
s32 func_0015CAB8(V24A2* self, void* obj);
void func_001613C0(void* obj, s32 a, s32 b, s32 c);
void func_00161708(void* obj, s32 tag, s64 value);
void func_00161768(void* obj, s32 tag, s64 value);

extern s32 D_0026227C;

void func_0018D800(void* dst, void* src, s32 size);

struct Pair_15EF88 { u8 pad0[0x4]; s32 f4; u8 pad8[0x4]; s32 fC; };

extern s32 D_00261F18;
extern s32 D_00261F1C;

void func_0015ED50(void* a, s32 b);
void func_001686E8(s32 a, s32 b);


void* func_001611B8(void* p);
void* func_001EE318(void* p);

void func_0015F618(s32 flag, s32 code);

struct Frame_15C0A0 {
    Vec02 q;
    s32 a;
    s32 b;
};

extern f32 D_00261858[];

typedef s32 (*Pred_15C0A0)(void* a, void* b);

s32 func_0015C058(void* a, void* b);
void func_0018D608(void* self);
s32 func_001419E8(s32 zero, void* p, void* q, s32 a, s32 b, s32 c);
void func_0018D6F0(void);
void func_001DC4D0(s32 a0, s32 a1, void* a2, Pred_15C0A0 a3, void* a4, s32* a5, s32* a6, f32 f12);

void func_00152B80(void* list, u32 count, s32 value);
extern s32 D_0026230C;

void func_001613C0(void* obj, s32 a, s32 b, s32 c);
void func_00161708(void* obj, s32 a, s32 b);
void func_00161200(void* obj);
void func_00152D30(void* obj);
void func_001529E0(void* obj, void* a, s32 b);

void func_0015EB20(void* list, void* a, s32 b);
void func_0015EBF0(void* obj, void* a, s32 b);
void func_00152440(void* p);
s32 func_001F6B40(void* a);

extern List01 D_002622E0;
extern List01 D_002622F0;
extern List01 D_00262300;
extern s32 D_002622D0;
extern void* D_002623B0;

struct Obj_0015C3C0;

void func_001613C0(Obj_0015C3C0* obj, s32 a1, s32 a2, s32 a3);
void func_00161708(Obj_0015C3C0* obj, s32 a1, u64 key);

extern s32 D_002622D4;
extern s32 D_00274538;
extern s32 D_00261F1C;

void func_001B3488(s32 value);
void func_00202A80(s32 a, s32 b);

struct Cursor_15DFA0 { u8 pad[4]; u8* flag; };

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

struct Lines_15E068 { s8* start; s8* cur; V24A2* holder; };

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

s32 func_0015E068(void* self);

extern s8 D_00262250[];
extern s32 D_00262268[];

s32 func_0015C4E8(V24A2* self, u8* s);

// NEAR: the first load of self->p54 goes to $v0 (retail $v1), so two
// pointer loads differ in register choice; everything else matches.

struct Frame_15D998 { V24A0 a; u8 buf[0x100]; };
V24A0* func_001611B8(V24A0* p);
s32 func_00168D88(void* self, s32 size);
void func_00168FB0(void* self, s32 v);
void func_001529C8(void* self, s32 count, void* base);
void func_00169088(void* self, s32 dbp, void* ctx);
void func_00152A50(void* self, s32* count, u32* begin, s32* out, s32 flag);
void func_00168E78(void* self, s32 v);
void func_00168F48(void* self, s32 v, void* ctx);

// Matched: for loop over i with D_00262264 + i * 0x88.

extern s32 D_00262260;
extern u8* D_00262264;

void func_00168D68(void* dst, s32 size, s32 align);
void func_0015D998(void* item, void* buf);


void func_001617E8(V24A0* s, u32 tag, f32 value);
void func_00161860(V24A0* s, s32 a, s32 b);
void func_001618C0(V24A0* s, s32 a, s32 b, s32 c, s32 d);

V24A2_Glyph* func_0015DAB8(V24A2* self, s8 key);

s32 func_0015E068(void* self, f32 f);
f32 func_0015E1F0(void* self);

struct Obj_0015C2E8;
struct Vec4_0015C2E8 { f32 x; f32 y; f32 z; f32 w; };

void func_001613C0(Obj_0015C2E8* obj, s32 a1, s32 a2, s32 a3);
void func_00161708(Obj_0015C2E8* obj, s32 a1, u64 key);

extern u32 D_002C3B00[];
extern u8 D_00148D74[];
extern s32 D_00262310;

extern void* D_002623B4;
extern volatile s32 D_002623B8;
extern void* D_0026231C;
extern s32 D_002626CC;

s32 func_001F6B60(void* a);
void func_0015EF88(void* self, s32 flag);
void func_0015F320(void);
void func_001683E8(void);
void func_0015EFE8(void* p);
void func_00191EB0(s32 a);

struct Local_15D8A8 {
    u16 u0;
    u16 u2;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    f32 f8;
    u16 uC;
    u16 padE;
};



void func_00137A60(void* src, s32 n, void* dst);
void* func_0018D500(s32 n);
extern s32 D_00262258;
extern s32 D_0026225C;

V24A2_Glyph* func_0015DAB8(V24A2* self, s8 key);
s32 func_0015CAB8(V24A2* self, V24A0* s);
void func_001613C0(V24A0* s, s32 a, s32 b, s32 c);
void func_00161708(V24A0* s, s32 a, u64 b);
void func_00161768(V24A0* s, s32 a, u64 b);
void func_001617E8(V24A0* s, u32 tag, f32 value);
void func_00161860(V24A0* s, s32 a, s32 b);
void func_001618C0(V24A0* s, s32 a, s32 b, s32 c, s32 d);

// NEAR: CRC table loop: retail keeps inner counter k in v1 and n*4 in a1; ours swaps them (5 insns)

extern u8 D_003C3B00[], D_005C3B00[];
extern void* D_002623B0;
extern void* D_002623B4;
extern void* D_00275958[];
void func_00152438(List01* self, s32 value);
void func_001F6950(s32 a0, void (*fn)(void), s32 a2);
void func_001F6DA8(s32 a0);
void* func_001E2268(s32 a, s32 b);
void func_001F6A20(void* a, s32 b);
void func_0015E678(void);

void func_0015DB80(TextReader* self);

struct A_0015C058 { u8 pad[0x50]; s32 f50; };
struct B_0015C058 { u8 pad0[0x50]; s32 f50; u8 pad1[0x278]; u32 f2CC; u8 pad2[0x268]; u64 f538; };

extern void* D_002623B0;
extern void* D_002623B4;
extern u32 D_00262314;
extern s32 D_00261F18;
extern s32 D_00261F1C;
extern s32 D_002626CC;

void func_0015EDB8(void);
s32 func_001F6B60(void* p);
void func_0015ED50(RenderFrame* f);
void func_001684E8(void);
void func_001686E8(s32 a, s32 b);
void func_0015F320(void);
s32 func_00202C38(s32 a, s32 b, s32 c);
void func_001683E8(void);

struct Iter_15EFE8 {
    List01* list;
    u8* link;
    s32 offset;
    Iter_15EFE8* prev;
};

struct Node_15EFE8 {
    u8 pad0[0x14];
    u8* f14;
    u8 pad18[0x1088 - 0x18];
    void* f1088;
};


s32 func_00152720(List01* l);
void func_00152600(List01* l, Node_15EFE8* n);
void func_00152470(u8* l, Node_15EFE8* n);
void func_00152440(List01* l);

struct Begin_15EFE8 {
    static void Of(Iter_15EFE8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = ((Iter_15EFE8*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_15EFE8 {
    static Node_15EFE8* Of(Iter_15EFE8* it)
    {
        Node_15EFE8* obj = *(Node_15EFE8**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

typedef struct Par_15C638 Par_15C638;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;
typedef float f32;
struct Par_15C638
{
  f32 f0;
  f32 f4;
  f32 f8;
  f32 fC;
  s32 f10;
  s32 f14;
  s32 f18;
};

class Font_15E318 {
public:
    u8 pad[0x4C];
    virtual void V0();
    virtual void V1();
    virtual f32 Width(s32 c);
    virtual void Begin(s32 x, s32 y);
    virtual void Flush(s32 y);
    virtual f32 Draw(f32 left, f32 top, s32 c, s32 d, s32 y);
    virtual void End(s32 x, s32 y);
};

void func_0015DB80(TextReader* self);
s32 func_0015DBE0(TextReader* self);
void func_0015DBB8(TextReader* self, Rgba_137248* p);

// Inline text codes: ~RRGGBB / ~. colour, &<id> / &. font, ^<d><d> / ^. scale.
s32 func_0015C200(s32 id);
void func_0015C9B0(V24A2* font, V24A2* out);
void func_0015C900(V24A2* font);
void func_0015C8B8(V24A2* font, f32 a, f32 b);

struct Item_15D4E0 {
    V24A2* f0;
    s8 key;
    u8 p5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 color;
};
struct Rect_15D4E0 { f32 x, y, w, h; };

V24A2_Glyph* func_0015DAB8(V24A2* self, s8 key);
void func_0015C8B8(V24A2* p, f32 a, f32 b);
void func_0015C900(V24A2* p);
void func_0015D338(V24A2* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, V24A0* s);
extern void* D_0026231C;
extern void* D_002623B0;
extern volatile s32 D_002623B8;

extern void* D_002623B4;
extern s32 D_00262318;
extern s32 D_002622D0;

void func_00191E70(s32 v);
s32 func_001F6B60(void* a);
void func_001529C8(void* self, s32 count, void* base);
void func_00152B38(void* self);

INCLUDE_ASM(func_001549C8);

void func_00154C10(EffectSpawner* self)
{
    InitPlacedObject(self);
    self->f2D8=-1;
    self->f2E0=10.0f;
    self->id2F8[0]=-1;
    self->id2F8[1]=-1;
    self->id304=-1;
    self->id300=-1;
    self->id30C=-1;
    self->f2D4=-1;
    self->f2DC=10.0f;
    self->f340=-1.0f;
    self->f310=-1;
    func_00152438(self->list314,0x320);
}

ASM_FUNC(func_00154C80);

void func_00154EE0(Buffer_154EE0* self, s32 count, void* unused, void* src)
{
    s32 limit = 31;
    s32 cap = (limit < count) ? 32 : count;
    self->cap = cap;
    self->items = (U32P*)AllocateFrontMemory(cap * 4);
    self->source = ReadBufferedU8(src);
    for (s32 i = 0; i < count; i++) {
        Word_154EE0 tmp = ReadBufferedU32(src);
        if (i < self->cap) {
            self->items[i] = *(U32P*)&tmp;
        }
    }
}

void func_00154F98(EffectSpawner* self, s32 count)
{
    void* mem = AllocateFrontMemory(0x200);
    self->rec = (Rec50*)mem;
    func_001549C8(mem);
    LoadPlacedObject(self, count);
    s32 index = ReadBufferedS8(count);
    if (index != -1) {
        T2176* obj = CreatePathCurve(index);
        self->rec->curve20 = obj;
        void (*fn)(T2176* self, void* stream) = obj->vt->m00;
        if (fn != 0) {
            fn(obj, (void*)count);
        }
    }
    if (self->rec->kind == 4) {
        func_00154C80(&self->rec->curve20, count);
    }
    s32 n = ReadBufferedU16(count);
    if (n != 0) {
        void* b = GetOwnSpawnRecord(self, 1);
        ReadCappedWordList((u8*)b + 0x130, n, self, count);
    }
}

void func_00155080(EffectSpawner* self)
{
    CopyPlacedObject(self);
    self->rec->uses++;
}

void func_001550B8(Obj_1550B8* self)
{
    self->vtbl[25](self, self->sub->value);
}

void func_001550E8(EffectSpawner* self)
{
    Rec50* s2;

    PostLoadPlacedObject(self);
    if (self->key2F8 == -1 && self->id304 == -1 && self->id30C == -1 && self->id300 == -1) {
        Rec50* p = self->rec;
        if (p->kind != 3 && (p->f120 != 0 || p->f188 == -1)) goto tail;
    }
    s2 = GetOwnSpawnRecord(self, 1);
    if (self->id2F8[0] != -1) {
        Rec_001550E8* r = FindFirstObjectById(self->world, 0x104, self->id2F8[0], self);
        s2->target = r;
        if (r != 0) AppendQueuedCall(self->world, (void (*)(void))func_001550B8, self, 0, 0);
    }
    if (self->id2F8[1] != -1) {
        s2->found[0] = FindFirstObjectById(self->world, 0x104, self->id2F8[1], self);
    }
    if (self->id304 != -1) {
        s2->found[1] = FindFirstObjectById(self->world, 0x104, self->id304, self);
    }
    if (self->id300 != -1) {
        Rec_001550E8* s1 = FindFirstObjectById(self->world, 0x104, self->id300, self);
        if (IsObjectOfKind(s1, 3) != 0) s2->found[2] = s1;
    }
    if (self->id30C != -1) {
        Rec_001550E8* r = FindFirstObjectById(self->world, 0x104, self->id30C, self);
        s2->value20 = r->f34;
        s2->target = r->f18;
    }
tail:
    func_00158288(self->rec, self);
}

extern const f32 D_0024A120 = 3.4028235e+38f;

ASM_FUNC(func_00155270);

void func_00155678(EffectSpawner* self, s32 mode, BaseObject* p)
{
    if (mode == 2) {
        if (p == self->held344) {
            p->desc->m18(p, self);
            self->held344 = 0;
        } else if (p == self->held348) {
            p->desc->m18(p, self);
            self->held348 = 0;
        }
    }
}

Rec50* func_001556E8(Rec50* self)
{
    Rec50* n;
    if (self->uses < 2) return self;
    n = (Rec50*)CopyToFrontMemory(0x200, self);
    if (self->kind == 3 && self->f24 != 0) {
        n->f24 = CopyToFrontMemory(0x28 * self->value20, self->f24);
    }
    n->uses = 1;
    self->uses -= 1;
    return n;
}

Rec50* func_00155778(EffectSpawner* self, s32 mode)
{
    if (mode == 1) {
        self->f34C = mode;
        self->rec = CloneSharedSpawnRecord(self->rec);
    }
    return self->rec;
}

EffectSpawner* func_001557B8(EffectSpawner* self, s32 value)
{
    if (value == 1) {
        self->f34C = value;
    }
    return self;
}

void func_001557D0(void* self,void* a,void* b,f32 x,f32 y,f32 z,f32 w)
{
    u8* p=(u8*)GetOwnSpawnRecord(self,1);
    AddRangeEntry(p+16,a,b,x,y,z,w,self);
}

ASM_FUNC(func_00155868);

ASM_FUNC(func_00155AB0);

void func_00155F28(EffectSpawner* self)
{
    if ((self->flags & 0x0C000000) == 0x08000000) {
        return;
    }
    PlacedObject* p = (PlacedObject*)self->parent;
    while (p != 0) {
        if ((p->flags & 0x0C000000) == 0x08000000) {
            break;
        }
        p = (PlacedObject*)p->parent;
    }
    if (p != 0) {
        self->f88 = p->f88;
    }
}

void func_00155F78(EffectSpawner* self, f32 f)
{
    self->f340 = g_gameTime + f;
}

void func_00155F90(EffectSpawner* self)
{
    self->f340 = 3.4028234663852886e+38f;
}

void func_00155FA0(EffectSpawner* self)
{
    self->f340 = -1.0f;
}

s32 func_00155FB0(EffectSpawner* self)
{
    if (g_gameTime < self->f340) {
        return 1;
    }
    if (self->f2D4 < 2) {
        if (self->f2D4 >= 0) {
            if (self->f2D8 == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void func_00156000(Obj_156000* self, s32 a1)
{
    if (a1 != 0) {
        func_00155FA0(self);
    } else {
        SetEffectSpawnerActiveForever();
    }
}

void func_00156030(Obj_156030* self, s32* out)
{
    *out = IsEffectSpawnerActive(self) == 0;
}

void func_00156060(void* self,s32* out)
{
    *out=IsEffectSpawnerActive((EffectSpawner*)self);
}

void func_00156088(u8* self)
{
    *(s32*)(self+0x34C)=0;
    if (*(void**)(self+0x348)) func_0013A128(*(void**)(self+0x348),*(void**)(self+0x2D0));
    if (*(void**)(self+0x344)) func_0019E158(*(void**)(self+0x344),*(void**)(self+0x2D0));
    f32 value;
    if (*(s32*)(self+0x2D4)==3) value=RandomFloatInRange(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0))*60.0f;
    else value=RandomFloatInRange(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0));
    *(f32*)(self+0x328)=value;
}

void func_00156108(EffectSpawner* self, s32 a1)
{
    if (self->f2D4 == -1) {
        self->f2D8 = a1;
    } else if (self->f2D4 == 0) {
        if (a1 == 0) {
            SetEffectSpawnerActiveForever();
        } else if (a1 == -1) {
            func_00155FA0(self);
        } else {
            self->f2D8 = a1;
        }
    }
    self->f34C = 1;
}

void func_00156178(EffectSpawner* a0, s32 a1)
{
    a0->f308 = a1;
    a0->f34C = 1;
}

void func_00156188(u8* self,s32 kind)
{
    *(s32*)(self+0x1B0)=kind;
    func_001F5C0C(self+0x1F0,0,12);
    if (kind!=24) {
        if (kind==27) {
            *(s32*)(self+0x1F0)=-1;
            *(f32*)(self+0x1F4)=10.0f;
        }
    } else {
        *(f32*)(self+0x1F0)=25.0f;
        *(f32*)(self+0x1F4)=0.8f;
        *(f32*)(self+0x1F8)=0.8f;
    }
}

void func_00156218(void* a0, s32 a1)
{
    void* r = GetOwnSpawnRecord(a0, 1);
    SetSpawnRecordKind(r, a1);
}

void func_00156250(void* a0, s32 a1)
{
    void* r = GetOwnedSpawnRecord(a0, 1);
    SetSpawnRecordKind(r, a1);
}

ASM_FUNC(func_00156288);

void func_001566C8(Quad_001566C8* a0, f32 f)
{
    void* obj = ((Game_001566C8*)g_currentWorld)->f1D0C;
    if (obj != 0) {
        Msg_001566C8 m;
        m.kind = 12;
        m.q = *a0;
        m.f = f;
        m.zero = 0;
        VFn_001566C8* vt = *(VFn_001566C8**)obj;
        vt[31](obj, &m);
    }
}

INCLUDE_RODATA(jtbl_0024A130);

ASM_FUNC(func_00156718);

ASM_FUNC(func_00156F08);

void func_00156FC8(s32 n, Span_00156FC8* span, s32 k, Slot_00156FC8* out) { if (n > 0) { out->count = n < k ? n : k; } else { out->count = k; } s32 steps = k - 1; steps += out->count; steps = steps / out->count; f32 w = WrapAngle(span->hi - span->lo); f32 rate = 6.2831855f / (f32)out->count; f32 step = w / (f32)steps; out->rate = rate; out->step = step; out->phase = span->lo + step * 0.5f; out->out10 = RandomFloatInRange(0.0f, 6.2831855f); }

ASM_FUNC(func_00157098);

ASM_FUNC(func_00157248);

void func_00157320(Rec50* self, Hdr_157320* h, s32 n, Q_157320* pos, Q_157320* q2, f32* v5, f32* v6)
{
    u8* s7 = AT(u8*, self, 0x7C);
    EffectOwner* node = 0;
    u8* c = (u8*)self + 0x120;
    s32 i;
    if (h) {
        if (h->f4) node = (EffectOwner*)*h->f4;
    }
    if (!node) {
        node = AcquireEffectOwner((u8*)g_currentWorld, AT(s32, c, 0xC4));
        if (!node) return;
        if (h) {
            if (h->f4) *h->f4 = (s32)node;
        }
        func_0019E158(node, self);
        if (h) {
            if (h->f8) {
                typedef void (*F)(EffectOwner*, s32);
                (*(F*)(AT(u8*, node, 0) + 0x6C))(node, h->f8);
            }
        }
    }
    if (node) {
    for (i = 0; i < n; i++) {
        Effect* it = CreateEffect(AT(s32, c, 0x90), node);
        if (!it) break;
        Q_157320* s1 = pos + i;
        u8* cls = AT(u8*, it, 0);
        f32 f = RandomFloatInRange(AT(f32, c, 0xB0), AT(f32, c, 0xB4));
        typedef void (*F0)(Effect*, Q_157320*, s32, f32);
        (*(F0*)cls)(it, s1, AT(s32, c, 0xC0), f);
        f32 f1 = AT(f32, c, 0xA4);
        if (f1 != 0.0f || AT(f32, c, 0xA8) != 0.0f) {
            AT(f32, it, 0x34) = f1;
            AT(f32, it, 0x38) = AT(f32, c, 0xA8);
        }
        AT(Q_157320, it, 0xA0) = q2[i];
        AT(f32, it, 0x18) = v5[i];
        AT(f32, it, 0x1C) = v6[i] - v5[i];
        AT(Q_157320, it, 0x40) = AT(Q_157320, self, 0x110);
        func_001583E8((Effect*)((u8*)it + 0xB0), self);
        if (AT(s32, c, 0xB8)) AT(s32, it, 0x20) = AT(s32, c, 0xB8);
        if (s7) {
            AT(Q_157320, it, 0x50) = AT(Q_157320, s7, 0x110);
            AT(Q_157320, it, 0x60) = AT(Q_157320, s7, 0x120);
            AT(Q_157320, it, 0x70) = AT(Q_157320, s7, 0x130);
        }
        if (AT(s32, c, 0x94) != -1) {
            EffectOwner* o = (EffectOwner*)CreateEffect(AT(s32, c, 0x94), 0);
            if (!o) break;
            typedef void (*F1)(f32, EffectOwner*, void*, s32);
            F1 fn = *(F1*)(*(u8**)o);
            fn(AT(f32, it, 0x30) * 0.5f, o, (u8*)it + 0x80, 0);
            func_001A0338(o, 1, it);
        }
        {
            u8* cl = AT(u8*, it, 0);
            VFn* p = (VFn*)(cl + 4);
            if (*p) ((void (*)(Effect*, Rec50*))*p)(it, self);
        }
    }
    if (IsListEmpty((u8*)node + 0x558)) {
        typedef void (*F2)(EffectOwner*);
        (*(F2*)(AT(u8*, node, 0) + 0x1C))(node);
    }
    }
}

ASM_FUNC(func_001575D8);

ASM_FUNC(func_001579B0);

INCLUDE_RODATA(D_0024A144);

ASM_FUNC(func_00157B88);

void func_00157E00(void* a, Rec50* b, void* c)
{
    Frame_157E00 f;
    if (a == 0) {
        return;
    }
    PushBackMemoryMark();
    f.flag = 1;
    func_001579B0(a, b, f.out);
    if (b->f120 == 1) {
        SpawnRecordEffects(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3]);
    } else {
        if (b->f130 == 2) {
            func_00157B88(a, b, f.out, f.pair);
        } else {
            f.pair[0] = 0;
            f.pair[1] = 0;
        }
        func_001575D8(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3], f.pair[0], f.pair[1]);
    }
    PopBackMemoryMark();
}

void func_00157EF8(Quad16* self, Quad16* a1, void* a2, Tail_157EF8* a3, Blk_157EF8* a4, s32 a5, s32 a6)
{
    Frame_157EF8 f;
    func_001549C8(&f);
    Pair_157EF8 p;
    f.self_copy = *self;
    f.a1_copy = *a1;
    f.blk = *a4;
    p.b = a5;
    p.c = a6;
    f.f120 = 1;
    f.tail = *a3;
    SpawnEffectsFromRecord(a2, &f, &p);
}

LINKER_REMNANT(func_00157FF0);

void func_00157FF8(void* self, void* obj, f32 x)
{
    Frame_157FF8 frame;
    List_157FF8* list = (*(Owner_157FF8**)((u8*)&g_currentWorld))->list;

    if (list == 0) return;
    for (s32 i = 0; i < list->count; i++) {
        Elem_157FF8* e = list->items[i];
        frame.kind = 4;
        frame.pos = *(Quad_157FF8*)self;
        if (e->f90->f120 == 1) {
            switch (e->f90->f1B0) {
            case 4:
                frame.kind = 0x14;
                frame.f30 = x;
                break;
            case 2:
                frame.kind = 0x24;
                frame.f38 = obj;
                break;
            }
        }
        e->vtbl[31](e, &frame);
    }
}

void func_00158108(void* a0, Owner_158108* a1, f32 f)
{
    Effect* o = (Effect*)CreateEffect(4, 0);
    if (o != 0) {
        ((VFn_158108)o->vt->m00)(o, a0, 0, f);
        o->life = 0.75f;
        if (a1->f278 != 0) {
            o->p114 = (void*)a1->f278->fC;
        }
    }
}

void func_00158198(Emitter_158198* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15)
{
    self->kind = 3;
    if (self->entries == 0) {
        self->entries = (Entry_158198*)AllocateZeroedFrontMemory(0x500);
    }
    if (self->count < 0x20) {
        s32 n = self->count;
        Entry_158198* e = self->entries + n;
        self->count = n + 1;
        e->a = a1;
        e->b = a2;
        e->c = f13;
        if (0.0f <= f15) {
            e->d = f15;
        } else {
            e->d = f13;
        }
        e->e = f12;
        if (0.0f <= f14) {
            e->f = f14;
        } else {
            e->f = f12;
        }
    }
}

ASM_FUNC(func_00158288);

ASM_FUNC(func_001583E8);

INCLUDE_ASM(func_00158480);

void func_001585F8(C77* self)
{
    StartObject(self);
    self->desc->m03(self);
}

ASM_FUNC(func_00158630);

void func_00158730(C77* a0)
{
    Blob_158730 b;
    func_001F5C0C(&b, 0, 0x50);
    a0->desc->m1B(a0, &b);
}

void func_00158778(C77* a0, s32 a1, s32 a2, Quad_158778* a3, Quad_158778* a4, f32 x, f32 y)
{
    Msg_158778 m;
    m.a = a1;
    m.b = a2;
    m.q1 = *a3;
    m.q2 = *a4;
    m.x = x;
    m.y = y;
    a0->desc->m1B(a0, &m);
}

void func_001587C0()
{
}

void func_001587C8(C78* self, void* src)
{
    void* arr[8];
    s32 total;
    s32 i;
    ReadTransformObject(self, src);
    total = ReadBufferedS16(src);
    for (i = 0; i < total; i++) {
        s32 r1 = ReadBufferedS16(src);
        s32 r2 = ReadBufferedS16(src);
        s32 r3 = ReadBufferedS16(src);
        Node_1587C8* obj = (Node_1587C8*)CreateTypedRecord(r1, self->world, self->parent, r2, r3);
        s32 n;
        ((Fn1_1587C8)obj->vtbl[14])(obj, src);
        if (((u32*)obj->vtbl)[2] & 0x100) {
            Link_1587C8* p = obj->list;
            n = 0;
            while (p != 0) {
                if ((u32)n < 8) {
                    arr[n] = p->item;
                    n++;
                }
                p = p->next;
            }
        } else {
            arr[0] = obj;
            n = 1;
        }
        if (n > 0) {
            void** dst = (void**)self->members;
            void** s = arr;
            s32 j;
            for (j = n; j != 0; j--, s++) {
                C77* o = (C77*)*s;
                if (IsObjectOfKind(o, 0x78) != 0 || IsObjectOfKind(o, 0x7A) != 0) {
                    o->desc->m03(o);
                    u32 c = self->count;
                    if (c < 8) {
                        *(void**)((u8*)dst + (c << 2)) = o;
                        self->count = c + 1;
                        o->group = self;
                    }
                }
            }
        }
    }
}

void func_00158980(C78* self)
{
    CopyObjectData(self);
    for (s32 i = 0; i < self->count; i++) {
        C77* o = CreateObjectCopy(self->members[i], self->world, self->parent);
        o->desc->m03(o);
        self->members[i] = o;
        o->group = self;
    }
}

void func_00158A10(C78* self)
{
    for (s32 i = 0; i < self->count; i++) {
        C77* it = self->members[i];
        void (*fn)(BaseObject*) = it->desc->m0F;
        if (fn != 0) {
            fn(it);
        }
    }
}

void func_00158A80(C78* self, void* message)
{
    for (s32 i = 0; i < self->count; i++) {
        C77* it = self->members[i];
        it->desc->m1B(it, message);
    }
}

void func_00158B00(C79* self)
{
    InitTransformObject(self);
    self->id94 = -1;
    self->id98 = -1;
}

void func_00158B30(C79* self, void* stream)
{
    Rec79* p = (Rec79*)AllocateZeroedFrontMemory(0x200);
    self->rec = p;
    func_001549C8(p);
    ReadTransformObject(self, stream);
    s32 idx = ReadBufferedS8(stream);
    if (idx != -1) {
        Rec79* n = GetOwnedSpawnRecord(self, 1);
        n->curve20 = CreatePathCurve(idx);
        if (n->curve20->vt->m00 != 0) {
            n->curve20->vt->m00(n->curve20, stream);
        }
    }
    Rec79* q = self->rec;
    if (q->kind == 4) {
        func_00154C80(&q->curve20, stream);
    }
    void* t = ReadBufferedU16(stream);
    if (t != 0) {
        Rec79* m = GetOwnedSpawnRecord(self, 1);
        ReadCappedWordList((u8*)m + 0x130, t, self, stream);
    }
}

void func_00158C28(C79* self)
{
    CopyObjectData(self);
    self->rec->uses += 1;
}

void func_00158C60(C79* self)
{
    Rec79* r;
    Rec79* c;

    if (self->id94 == -1 && self->id98 == -1) {
        c = self->rec;
        if (c->kind != 3) {
            if (c->link120 != 0) goto tail_c;
            if (c->link188 == -1) goto tail;
        }
    }

    {
        s32 none = -1;

        r = GetOwnedSpawnRecord(self, 1);
        if (self->id94 != none) {
            r->target = FindFirstObjectById(self->world, 260, self->id94, self);
        }
        if (self->id98 != none) {
            Rec_158C60* q = FindFirstObjectById(self->world, 260, self->id98, self);
            r->value20 = q->f34;
            r->target = q->f18;
        }
    }

tail:
    c = self->rec;
tail_c:
    func_00158288(c, self);
}

void func_00158D38(void)
{
}

void func_00158D40(C79* self, void* a, void* b, f32 x, f32 y, f32 z, f32 w)
{
    u8* p = (u8*)GetOwnedSpawnRecord(self, 1);
    AddRangeEntry(p+16,a,b,x,y,z,w,self);
}

Rec79* func_00158DD8(C79* self, s32 own)
{
    if (own == 1) {
        self->rec = (Rec79*)CloneSharedSpawnRecord(self->rec);
    }
    return self->rec;
}

void func_00158E10(C7A* self)
{
    InitRecordMember(self);
    self->idAC = -1;
    self->idB0 = -1;
    self->idB4 = -1;
}

void func_00158E48(C7A* self)
{
    Rec79* s;
    void* p;

    ResolveRecordMemberTargets(self);
    if (self->idAC == -1 && *(s64*)&self->idB0 == -1) {
        return;
    }
    s = GetOwnedSpawnRecord(self, 1);
    if (self->idAC != -1) {
        s->found[0] = FindFirstObjectById(self->world, 0x104, self->idAC, self);
    }
    if (self->idB0 != -1) {
        s->found[1] = FindFirstObjectById(self->world, 0x104, self->idB0, self);
    }
    if (self->idB4 != -1) {
        p = FindFirstObjectById(self->world, 0x104, self->idB4, self);
        if (IsObjectOfKind(p, 3) != 0) {
            s->found[2] = p;
        }
    }
}

void func_00158F10(C7A* self, s32 kind, BaseObject* other)
{
    if (kind == 2) {
        if (other == self->heldC0) {
            other->desc->m18(other, self);
            self->heldC0 = 0;
        } else if (other == self->heldC4) {
            other->desc->m18(other, self);
            self->heldC4 = 0;
        }
    }
}

void func_00158F80(C7A* self, void* message)
{
    Rec_158F80* r;
    f32* k;
    s32 done = 0;

    if (0.0f < self->delay) {
        r = (Rec_158F80*)PopFreeSlot(&self->world->pool1BD0);
        if (r != 0) {
            r->owner = self;
            r->body = *(Body_158F80*)message;
            done = 1;
            k = (f32*)g_gameClock;
            r->f60 = k[1] + self->delay;
            func_00152450((u8*)r + 0x64);
            AppendToList(&self->world->list1BDC, r);
        }
    }
    if (done == 0) {
        func_001590A0(self, message);
    }
}

s32 func_00159068(void* self)
{
    C7A* o = (C7A*)self;
    if (o->fA0 == 0) {
        InitSoundParams(&o->fA0);
    }
    return o->fA0;
}

INCLUDE_RODATA(jtbl_0024A150);

ASM_FUNC(func_001590A0);

void func_00159478(void** out, void* self)
{
    BaseObject* o = (BaseObject*)self;
    void* arr[32];
    s32 n;
    s32 cnt;
    s32 i;
    Node_159478* s2;

    n = GatherObjectsById(o->world, 0x202, 0x77, self, 0x20, arr);
    switch (n) {
    case 0:
        *out = 0;
        return;
    case 1:
        *out = arr[0];
        return;
    }
    s2 = (Node_159478*)CreateTypedRecord(0x78, o->world, self, 0x202, -1);
    cnt = 8;
    if (n < 8) {
        cnt = n;
    }
    s2->count = cnt;
    CopyMemory(s2->items, arr, cnt * 4);
    for (i = 0; i < n; i++) {
        Node_159478* p = (Node_159478*)arr[i];
        if (i < s2->count) {
            p->owner = s2;
        }
        p->vtbl[7](p);
    }
    *out = s2;
}

void func_00159588(World* self)
{
    Iter_00159588 it;
    Begin_00159588::Of(&it, &self->list1BDC);
    Node_00159588* node;
    while ((node = Next_00159588::Of(&it)) != 0) {
        if (!(g_gameClock[1] < node->f60)) {
            func_001590A0(node->f0, node->body);
            RemoveFromList(&self->list1BDC, node);
            PushFreeSlot(&self->pool1BD0, node);
        }
    }
    g_activeListFrames = (ListFrame*)it.saved;
}

ASM_FUNC(func_00159668);

void func_00159680(CrossfadeAnimator* self, AnimatorParams* src)
{
    LoadAnimatorBase(self, src);
    self->cursor2.flags = self->cursor.flags;
    self->recordKey2 = src->s14;
    self->scale = src->f4;
    self->lo = src->f8;
    self->hi = src->fC;
    self->limit = src->f10;
}

void func_001596E0(CrossfadeAnimator* self)
{
    BindAnimatorRecord(self);
    AnimRecord* a = FindAnimRecord(self->recordKey2);
    self->cursor2.record = a;
    if (a != 0) {
        if (a->owner == 0) {
            if (self->cursor.record->owner == self) {
                a->owner = self;
            }
        }
    }
    s32 lo = 0;
    if (self->cursor.record != 0) {
        lo = self->cursor.record->count;
    }
    s32 hi = 0;
    if (self->cursor2.record != 0) {
        hi = self->cursor2.record->count;
    }
    self->mode = -1;
    self->count = (hi < lo) ? lo : hi;
    SetCrossfadeMode(self, 0);
}

void func_00159770(CrossfadeAnimator* s, s32 mode)
{
    if (s->mode == mode) return;
    if (mode == 1) goto store;
    if (mode < 2) {
        if (mode == 0) goto zero;
        s->mode = mode;
        goto tail;
    }
    if (mode == 2) goto two;
    s->mode = mode;
    goto tail;

zero:
    {
        s32 n = s->count;
        f32 span = (f32)(n << 1) * (1.0f - s->ratio) / s->scale;
        s->pos = (f32)(n - 1) * s->ratio;
        s->step = span;
        f32 r = RandomFloatInRange(0.0f, 1.0f);
        if (r < s->limit) {
            s->level = 0.0f;
        } else {
            s->level = RandomFloatInRange(s->lo, s->hi);
        }
    }
    goto store;

two:
    {
        s32 last = s->count - 1;
        if ((s32)s->pos == last) {
            s->mode = mode;
            goto tail;
        }
        s->pos = (f32)last;
    }

store:
    s->mode = mode;

tail:
    s->stamp2 = g_gameTime;
}

void func_00159890(CrossfadeAnimator* s, f32 dt)
{
    s32 count = s->count;
    if (count < 2) return;
    s32 mode = s->mode;
    if (mode == 1) goto m1;
    if (mode < 2) {
        if (mode == 0) goto m0;
        goto call;
    }
    if (mode == 2) goto m2;
    if (mode == 3) goto m3;
    goto call;

m0:
    if (s->level <= g_gameTime - s->stamp2) mode = 1;
    goto call;

m1:
    {
        f32 step = s->step * dt;
        f32 sum = s->pos + step;
        s->pos = sum;
        if ((f32)count <= sum) {
            f32 back = sum - step;
            s->pos = back;
            mode = ((s32)back == count - 1) ? 2 : 3;
        }
    }
    goto call;

m2:
    if (s->ratio < 1.0f) mode = 3;
    goto call;

m3:
    {
        f32 v = s->pos - s->step * dt;
        s->pos = v;
        if (v <= (f32)count * s->ratio) mode = 0;
    }

call:
    SetCrossfadeMode(s, mode);
    SetCursorFrame(&s->cursor, (s32)s->pos);
    SetCursorFrame(&s->cursor2, (s32)s->pos);
}

void func_00159A00(CrossfadeAnimator* a0, f32 f12)
{
    a0->ratio = f12;
    if (1.0f <= f12) {
        SetCrossfadeMode(a0, 2);
    } else {
        a0->mode = -1;
        SetCrossfadeMode(a0, 0);
    }
    SetCursorFrame(&a0->cursor, (s32)a0->pos);
    SetCursorFrame(&a0->cursor2, (s32)a0->pos);
}

AnimCursor* func_00159A80(CrossfadeAnimator* self, const AnimRecord* key)
{
    AnimCursor* p = FindAnimatorCursor(self, key);
    if (p == 0) {
        p = &self->cursor2;
        if ((key->key ^ self->recordKey2) != 0) {
            p = 0;
        }
    }
    return p;
}

void func_00159AD0(Obj_159AD0* self, f32 dt)
{
    if (self->f8 != 0.0f) {
        if (IsObjectAttached(self->f0) == 0) {
            RemoveObjectNodeFromWorld(self);
            return;
        }
    }
    f32 old = self->f4;
    self->f4 = old + self->f8 * dt;
    if (self->f4 <= 0.0f && old > 0.0f) {
        Sub_159AD0* s = self->f0;
        s->vtbl[7](s);
        RemoveObjectNodeFromWorld(self);
        return;
    }
    if (self->f4 >= 1.0f && old < 1.0f) {
        RemoveObjectNodeFromWorld(self);
    }
}

Node_159BB0* func_00159BB0(PlacedObject* self)
{
    Node_159BB0* node = (Node_159BB0*)PopZeroedFreeSlot((u8*)g_currentWorld + 0x1C18);
    node->owner = self;
    if (self->f294 != 0) {
        AppendToList((u8*)g_currentWorld + 0x1C30, node);
    } else {
        AppendToList((u8*)g_currentWorld + 0x1C24, node);
    }
    return node;
}

void func_00159C28(Node_159C28* node)
{
    if (node->owner->flag294 != 0) {
        RemoveFromList((u8*)g_currentWorld + 0x1C30, node);
    } else {
        RemoveFromList((u8*)g_currentWorld + 0x1C24, node);
    }
    node->owner->flag298 = 0;
    PushFreeSlot((u8*)g_currentWorld + 0x1C18, node);
}

void func_00159CA0(u8* a0)
{
    Frame_159CA0 f;
    f.value = *(s32*)(a0 + 0x60);
    FillScreenColor(&f, &f.value, 0);
    V24A0* s = &g_vifPacketWriter;
    BeginDmaTag(s);
    func_001EE7D0(s, 0x2C, &f, 0);
    CloseDmaTag(s);
}

void func_00159D00(ColorFade* self)
{
    if (D_00275BC4 != 3) return;
    s32 g = D_00270458;
    if (g == 1) return;
    if (g == 2) return;
    Out_159D00 out; Rgba4 a, b;

    f32 t = g_gameTime - self->startTime;
    f32 d;
    if (t < self->fadeInTime) {
        a = self->startColor; b = self->holdColor;
        d = self->fadeInTime;
    } else {
        t -= self->fadeInTime;
        if (t < self->holdTime) {
            a = self->holdColor; b = self->holdColor;
            d = self->holdTime;
        } else {
            t -= self->holdTime;
            if (!(t < self->fadeOutTime)) {
                u8* p = (u8*)g_currentWorld + 0x1CD8;
                self->running = 0;
                RemoveFromList(p, self);
                return;
            }
            a = self->holdColor; b = self->endColor;
            d = self->fadeOutTime;
        }
    }
    f32 r = t / d;
    for (s32 i = 0; i < 4; i++)
        out.c[i] = (s32)((1.0f - r) * ((u8*)&a)[i] + r * ((u8*)&b)[i]);
    Req_159D00 q;
    q.f = -1.0f;

    q.fn = (void*)(void (*)(ColorFade*))DrawScreenFill;
    q.col = out;
    switch (self->mode) {
    case 0: q.mode = 1; break;
    case 1: q.mode = 0x10; break;
    }
    QueueDeferredRequest(&q);
}

void func_00159ED0(Ctx_159ED0* a0)
{
    if (a0->f5C == 0) {
        a0->f5C = 1;
        a0->f54 = g_gameTime;
        AppendToList((u8*)g_currentWorld + 0x1CD8, a0);
    }
}

u8* func_00159F20(u8* base, s32 n)
{
    return base + (((n * 0x95675) & 0x1FF) * 12 + 0x84);
}

void func_00159F48(PlacedObject* self, s32 mode, s32 a2, s32 a3, PlacedObject* a4, s32 cap,
                   s32* count, PlacedObject** arr, s32* lvlp)
{
    PlacedObject* a0;
    PlacedObject* prev;
    switch (mode) {
    case 2:
        if (self->alias != 0 && a3 == 0) return;
        if (self->parent == a4) goto add;
        return;
    case 1:
        if (self->alias != 0 && a3 == 0) return;
        a0 = (PlacedObject*)self->parent;
        if (a0 == 0) return;
        do {
            u64 lvl = a0->mark;
            if (lvl != 0) {
                if (lvl == 1) goto add;
                return;
            }
            if (a0->alias != 0) return;
            a0 = (PlacedObject*)a0->parent;
        } while (a0 != 0);
        return;
    case 3:
        if (self->desc->flags & 1) {
            if (self->flags & ((u64)0xF000 << 30)) goto add;
        }
        return;
    case 4:
        prev = 0;
        a0 = self;
        if ((self->desc->flags & 1) == 0) a0 = (PlacedObject*)self->parent;
        while (a0 != 0) {
            u64 f = a0->flags;
            if (f & ((u64)0xF000 << 30)) {
                s32 lvl = (s32)(a0->flags >> 42) & 0xF;
                u32 cur = *lvlp;
                if (!(cur < lvl)) {
                    if (!(lvl < cur)) goto add;
                    *lvlp = lvl;
                    *count = 0;
                    *arr = 0;
                    goto add;
                }
            }
            if (a0 == prev) return;
            if (a0->alias != 0 && (a0 != self || a3 == 0)) {
                s32 want = -1;
                if (a4 != 0) {
                    for (PlacedObject* v = a4; v; v = (PlacedObject*)v->parent) {
                        if (v->alias != 0) { want = v->alias->id; break; }
                    }
                }
                if (a0->alias->id != want) return;
                prev = (PlacedObject*)a0->parent;
            }
            a0 = (PlacedObject*)a0->parent;
        }
        if (*lvlp != 0x7FFFFFFF) return;
        goto add;
    case 5:
    add:
        if (a2 == 0 && IsObjectAttached(self) == 0) return;
        if (*count < cap) arr[*count] = self;
        (*count)++;
        return;
    default:
        return;
    }
}

INCLUDE_ASM(func_0015A198);

Rec_158C60* func_0015A418(void* self,s32 flags,s32 kind,void* arg)
{
    s32 out=0;
    func_0015A198(self,flags|0x200,kind,arg,1,&out);
    return (Rec_158C60*)out;
}

s32 func_0015A448(void* self,s32 kind,void* arg)
{
    s32 out=0;
    func_0015A198(self,0x204,kind,arg,1,&out);
    return out;
}

s32 func_0015A480(void* self,s32 kind,void* arg)
{
    s32 out=0;
    func_0015A198(self,0x201,kind,arg,1,&out);
    return out;
}

s32 func_0015A4B8(s32 index, s32 value)
{
    Node_15A4B8* p = ((Node_15A4B8**)D_00247448)[index];
    while (p != 0) {
        if (p->value != value) {
            p = p->next;
        } else {
            return 1;
        }
    }
    return 0;
}

s32 func_0015A4F0(World* world, u32 flags, s32 id, PlacedObject* root, s32 max, PlacedObject** found)
{
    s32 c;
    s32 min;
    s32 kind;
    PlacedObject* obj;
    PlacedObject* mark;
    PlacedObject* p;
    s32 n;
    u32 i;

    if (id == -1) {
        return 0;
    }
    if (root == 0 && (flags & 5) == 0) {
        return 0;
    }
    kind = flags & 0xFF;
    c = 0;
    if (kind == 3) {
        // Retail reads obj here before anything sets it (lw 0($s0) with $s0 unset).
        if (!(obj->desc->flags & 1)) {
            obj = (PlacedObject*)obj->parent;
        }
        for (; obj != 0; obj = (PlacedObject*)obj->parent) {
            if (IsObjectOfKind(obj, id) != 0 && ((flags & 0x100) || IsObjectAttached(obj) != 0)) {
                if (c < max) {
                    found[c] = obj;
                }
                c++;
            }
        }
    } else if (kind == 2 && !(flags & 0x100)) {
        if (!(root->desc->flags & 1)) {
            return 0;
        }
        for (obj = (PlacedObject*)root->children.head; obj != 0; obj = (PlacedObject*)obj->next) {
            if (IsObjectOfKind(obj, id) == 0) {
                continue;
            }
            if (c < max) {
                found[c] = obj;
            }
            c++;
        }
    } else {
        switch (kind) {
        case 1:
        case 3:
        case 4:
            mark = root;
            if (mark != 0 && !(mark->desc->flags & 1)) {
                mark = (PlacedObject*)mark->parent;
            }
            p = mark;
            n = 0;
            while (p != 0) {
                n++;
                p->mark = n;
                p = (PlacedObject*)p->parent;
            }
            min = 0x7FFFFFFF;
            break;
        default:
            mark = 0;
            break;
        }
        for (i = id; i < 0x95 && IsClassOfKind(i, id); i++) {
            for (obj = (PlacedObject*)world->f1884[i]; obj != 0; obj = (PlacedObject*)obj->nextById) {
                CollectObjectByMode(obj, kind, flags & 0x100, 0, root, max, &c, found, &min);
            }
        }
        for (p = mark; p != 0; p = (PlacedObject*)p->parent) {
            p->mark = 0;
        }
    }
    if (!(flags & 0x200) && max < c) {
        c = max;
    }
    return c;
}

s32 func_0015A838(void* self,s32 flags,s32 kind,void* arg)
{
    s32 out=0;
    GatherObjectsById(self,flags|0x200,kind,arg,1,&out);
    return out;
}

BaseObject* func_0015A868(BaseObject* list, BaseObject* other)
{
    for (BaseObject* p = list; p != 0; p = p->parent) {
        for (BaseObject* q = other; q != 0; q = q->parent) {
            if (p == q) {
                return p;
            }
        }
    }
    return 0;
}

LINKER_REMNANT(func_0015A8B0);

void func_0015A8B8(C60* self)
{
    InitPlacedObject(self);
    f32* v = self->v;
    self->f2F0 = 1.0f;
    self->f2EC = 1.0f;
    self->v[0] = 1.0f;
    v[1] = 0.2f;
    v[2] = 0.1f;
}

void func_0015A918(C60* self,void* other)
{
    LoadPlacedObject(self,other);
    ReadMeshTables(other,&self->out2D0,&self->out2D4,&self->out2D8,&self->out2DC);
}

void func_0015A960(C60* self)
{
    UpdatePlacedObject(self);
    self->f2EC = ApproachValueWithRamp(self->v, 0, self->f2EC, self->f2F0, g_frameDt);
}

void func_0015A9A8(C60* self, void* arg1, void* arg2)
{
    Frame_15A9A8 f;
    func_0018A008(0, &f.q0, self->f2EC);
    BuildPlacedObjectTransform(self, arg2, f.m40);
    func_00188668(f.m90, f.m40, &f.q0);
    f.m40[0] = f.m90[0];
    f.m40[1] = f.m90[1];
    f.m40[2] = f.m90[2];
    f.m40[3] = f.m90[3];
    func_001261C0(self, arg1, f.m40);
}

ASM_FUNC(func_0015AA50);

void func_0015AAE0(ObjectCycler* self)
{
    InitCollider(self);
    self->state = -1;
    self->p610.pk = D_00262180;
    self->p618.pk = D_00262188;
    self->p620.pk = D_00262190;
    self->p628.pk = D_00262198;
    self->swapKind = -1;
    self->checkDelay.pk = D_002621A0;
    self->p650.pk = D_002621A8;
    self->p658.pk = D_002621B0;
    self->p660.pk = D_002621B8;
    self->p670.pk = D_002621C0;
    self->indexStep = 1;
    self->f690 = -1;
    AppendToList(&self->world->list1C48, self);
}

void func_0015AC08(ObjectCycler* self, void* arg)
{
    u32 i;
    LoadCollider(self, arg);
    ResolveObjectLinks(self, 2, g_objectCyclerLoadLinks);
    FindOrBuildMemberGroup((void**)&self->group, self);
    for (i = 0; i < 16; i++) {
        s32 kind = i + 0x23C;
        s32 p = func_0015A480((u8*)self->world, kind, self);
        if (!p)
            continue;
        func_00182ED8(p);
        if (self->mode == 1) {
            if (self->swapKind == kind)
                self->swapIndex = self->count;
        }
        self->objs[self->count++] = (PlacedObject*)p;
    }
    if (self->mode == 1) {
        for (i = 0; i < 8; i++) {
            s32 p = func_0015A480((u8*)self->world, i + 0x24D, self);
            if (p) {
                func_00182ED8(p);
                self->altObjects[self->altCount++] = (PlacedObject*)p;
            }
        }
    }
    if (self->mode) {
        if (IsInList(&self->world->list1C48, self))
            RemoveFromList(&self->world->list1C48, self);
    }
}

void func_0015AD80(ObjectCycler* self)
{
    PackedFloatPair tmp;
    tmp = self->f5DC;
    CopyCollider();
    self->f5DC = tmp;
    if (self->mode == 0) {
        StartSoundEffect(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
    } else {
        if (IsInList(&self->world->list1C48, self) != 0) {
            RemoveFromList(&self->world->list1C48, self);
        }
    }
}

void func_0015AE38(ObjectCycler* self, s32 flag)
{
    if (self->mode == 0) {
        if (flag != 0) {
            StopSoundRecord(self->handle, 0);
        } else {
            StartSoundEffect(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
        }
    }
}

void func_0015AEB0(ObjectCycler* self)
{
    ResolveObjectLinks(self, 2, g_objectCyclerStartLinks);
    if (self->mode == 1) {
        f32 t = RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
        self->nextCheckTime = g_gameClock[1] + t;
        t = RandomFloatInRange(self->p670.a, self->p670.b);
        self->f680 = g_gameClock[1] + t;
    }
    func_0015B7B8(self, self->startState);
    StartPlacedObject(self);
    self->f64C = self->radius3CC + self->radius3CC;
}

INCLUDE_RODATA(jtbl_0024A190);

ASM_FUNC(func_0015AF50);

void func_0015B128(ObjectCycler* self)
{
    UpdateCollider(self);
    if (self->stateEnd <= g_gameClock[1]) {
        s32 a1 = self->state;
        switch (a1) {
        case 0:
        case 3:
            func_0015B7B8(self, -1);
            a1 = 0;
            break;
        case 1:
            a1 = 2;
            break;
        case 5:
            a1 = func_0015BEF0(self);
            break;
        case 6:
            a1 = 0;
            break;
        default:
            break;
        }
        func_0015B7B8(self, a1);
    }
    s32 st = self->state;
    switch (st) {
    case 0:
    case 3:
    case 5: {
        s32 sub = self->mode;
        switch (sub) {
        case 0:
            if (self->handle == 0) {
                StartSoundEffect(0x41, &self->handle, (s32)self, 0, 700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            self->index = (self->index + 1) % self->count;
            break;
        case 1:
            if (st == 0) {
                if (self->nextCheckTime <= g_gameClock[1]) {
                    V128_15B128 tmp;
                    if (func_0015BD48(self, &tmp)) {
                        *(V128_15B128*)&self->v5F0 = tmp;
                        func_0015B7B8(self, 5);
                    } else {
                        self->nextCheckTime = g_gameClock[1] + RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
                    }
                }
            }
            if (self->nextStepTime <= g_gameClock[1]) {
                s32 n = self->count;
                if (n >= 2) {
                    s32 v = self->index + self->indexStep;
                    self->index = v;
                    if (v >= n) {
                        self->index = n - 2;
                        self->indexStep = -1;
                    } else if (v < 0) {
                        self->index = 1;
                        self->indexStep = 1;
                    }
                    self->nextStepTime = g_gameClock[1] + self->stepInterval;
                }
            }
            break;
        }
        if (0.15f < g_gameClock[1] - self->stateStart) {
            ContactRow03* n = self->contacts->head;
            if (n != 0) {
                for (; n != 0; n = n->next) {
                    if (n->head != 0) {
                        self->stateEnd = g_gameClock[1];
                        break;
                    }
                }
            }
        }
        break;
    }
    case 6:
        if (func_0015C0A0(self) || func_0015BFC0(self)) {
            func_0015B7B8(self, 0);
        } else if (self->nextAdvanceTime <= g_gameClock[1]) {
            s32 idx = (self->index + 1) % self->altCount;
            self->index = idx;
            self->nextAdvanceTime = g_gameClock[1];
            f32 x, y;
            if (idx == 0) {
                x = self->p660.a;
                y = self->p660.b;
            } else {
                x = self->p658.a;
                y = self->p658.b;
            }
            self->nextAdvanceTime += RandomFloatInRange(x, y);
        }
        break;
    }
    if (self->mode == 1) {
        s32 s = self->state;
        if (s == 0 || s == 5) {
            func_0015BC78(self);
        }
    }
}

void func_0015B4D0(ObjectCycler* self, void* a1, void* a2)
{
    Out_15B4D0 out;
    BuildPlacedObjectTransform(self, a2, &out);
    switch (self->state) {
    case 1: {
        f32 base = self->stateStart;
        f32 num = g_gameTime - base;
        f32 den = self->stateEnd - base;
        f32 t = num / den;
        f32 v = D_00262230[0] + t * (D_00262230[1] + t * D_00262230[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->obj5D0->desc02()->m24(self->obj5D0, a1, &out);
        break;
    }
    case 3: {
        f32 base = self->stateStart;
        f32 num = g_gameTime - base;
        f32 den = self->stateEnd - base;
        f32 t = num / den;
        f32 v = D_00262240[0] + t * (D_00262240[1] + t * D_00262240[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->objs[self->index]->desc02()->m24(self->objs[self->index], a1, &out);
        break;
    }
    case 6: {
        self->altObjects[self->index]->desc02()->m24(self->altObjects[self->index], a1, &out);
        break;
    }
    default: {
        s32 idx = self->index;
        if (self->mode == 1 && self->swapKind != -1) {
            f32 t = (g_gameTime - self->stateStart) / (self->stateEnd - self->stateStart);
            if (1.0f - self->swapTail < t) idx = self->swapIndex;
        }
        self->objs[idx]->desc02()->m24(self->objs[idx], a1, &out);
        break;
    }
    }
}

s32 func_0015B720(ObjectCycler* self, Rec_15B720* r)
{
    if (self->state != 1) {
        func_0015B7B8(self, 1);
        if ((r->fC & 8) != 0) {
            func_001BC0E0(self, r->f8, &r->f20, &r->f30);
        }
        if (self->group != 0) {
            Local_15B720 loc;
            loc.f0 = 6;
            loc.f20 = r->f20;
            loc.f10 = r->f30;
            self->group->desc->m1B(self->group, &loc);
        }
    }
    return 1;
}

INCLUDE_RODATA(jtbl_0024A1D0);

INCLUDE_RODATA(jtbl_0024A1F0);

extern const Vec2_24A210 D_0024A210 = {0.0f, 4.73242188f};
extern const f32 D_0024A218[2] = {3.4028235e+38f, 0.0f};

ASM_FUNC(func_0015B7B8);

ASM_FUNC(func_0015BC78);

ASM_FUNC(func_0015BD48);

ASM_FUNC(func_0015BEF0);

ASM_FUNC(func_0015BFC0);

s32 func_0015C058(A_0015C058* a0, B_0015C058* a1)
{
    if ((a1->f538 & 0x80000000000ULL) || a1->f50 == a0->f50) return 0;
    u64 v = a1->f2CC;
    return ((s32)v ^ 1) & 1;
}

s32 func_0015C0A0(ObjectCycler* self)
{
    f32* tbl = g_gameClock;
    if (tbl[1] - self->f66C < 0.05f) {
        return 0;
    }
    PushBackMemoryMark(self);
    Frame_15C0A0 fr;
    func_001DC4D0((s32)self->world, 0, &self->v140, func_0015C058, self, &fr.a, &fr.b, self->f64C);
    fr.q = self->v140;
    fr.q.z = fr.q.z - self->f64C;
    s32 r = FindNearestSpanObject(0, &self->v140, &fr.q, fr.a, fr.b, 0);
    PopBackMemoryMark();
    self->f66C = tbl[1];
    return r == 0;
}

void func_0015C178(void)
{
    g_defaultFont = 0;
}

s32 func_0015C188(s32 a0)
{
    if (a0 == -1) {
        goto none;
    }
    if (((s32*)g_fonts)[a0] != 0) {
        goto some;
    }
none:
    return 0;
some:
    return 1;
}

s32 func_0015C1C0(s32 a)
{
    if (a == -1) {
        return 0;
    }
    s32 v = g_fonts[a];
    if (v != 0) {
        return v;
    }
    return g_defaultFont;
}

s32 func_0015C200(s32 a0)
{
    s8 key = (s8)a0;
    s32 i = 0;
    while (i < 5 && key != g_fontEscapeKeys[i]) {
        i++;
    }
    if (i < 5) {
        return g_fonts[i];
    }
    return 0;
}

void func_0015C260(V24A2* src, V24A2* dst)
{
    dst->f00 = src->f00;
    dst->advance = src->advance;
    dst->height = src->height;
    dst->sx = src->sx;
    dst->sy = src->sy;
    dst->depth = src->depth;
    CopyMemory(dst->stack, src->stack, src->depth << 3);
    dst->f30 = src->f30;
    dst->f38 = src->f38;
    dst->f40 = src->f40;
}

void func_0015C2E8(V24A2* unused, Vec4_0015C2E8* v, Obj_0015C2E8* obj)
{
    if (v != 0) {
        s32 pw = (s32)(v->x + v->z) - 1;
        s32 pz = (s32)((v->y + v->w) * 0.454545468f) - 1;
        s32 py = (s32)(v->y * 0.454545468f);
        s32 px = (s32)v->x;
        BeginGifTag(obj, 0, 1, 0xE);
        u64 key = (u64)px | ((u64)pw << 16) | ((u64)py << 32) | ((u64)pz << 48);
        AddGifRegisterWrite(obj, 0x40, key);
    }
}

void func_0015C3C0(V24A2* unused, s32 flag, Obj_0015C3C0* obj)
{
    if (flag != 0) {
        BeginGifTag(obj, 0, 1, 0xE);
        AddGifRegisterWrite(obj, 0x40, 0xDF0000027F0000UL);
    }
}

f32 func_0015C418(V24A2* self, s8* s)
{
    f32 acc;
    s8* p;
    if (s == 0) {
        return 0.0f;
    }
    p = s;
    acc = 0.0f;
    while (*p != 0) {
        const V24A2_Vt* n = self->vt;
        acc = acc + n->width((V24A2*)((u8*)self + n->adj3), (s8)(u8)*p++);
    }
    return acc;
}

f32 func_0015C4A8(V24A2* self, u8* s)
{
    f32 a = (f32)self->height * self->sy;
    s32 n = WrapFontString(self, s);
    return a * (f32)n;
}

s32 func_0015C4E8(V24A2* self, u8* s, f32 w)
{
    s32 count = 1;
    s8* cur = (s8*)s;
    f32 acc = 0.0f;
    while (*cur != 0) {
        s32 c = (s8)(s32)*(u8*)cur;
        if (c == 10) {
            acc = 0.0f;
            count++;
        } else {
            const V24A2_Vt* t = self->vt;
            acc += t->width((V24A2*)((u8*)self + t->adj3), c);
        }
        if (w != 0.0f && w < acc) {
            s8* p = cur;
            while (p >= (s8*)s) {
                s8 c2 = *p;
                if (c2 == 10) {
                    break;
                }
                if (c2 == 32 || c2 == 9) {
                    cur = p;
                    acc = 0.0f;
                    *cur = 10;
                    count++;
                    break;
                }
                p--;
            }
            if (acc != 0.0f) {
                *cur = 10;
                count++;
                acc = 0.0f;
            }
        }
        cur++;
    }
    return count;
}

LINKER_REMNANT(func_0015C630);

void func_0015C638(V24A2 *self, char *str, Par_15C638 *par, s32 a3, s32 a4)
{
  char *p;
  char *next;
  s32 pending = 1;
  f32 x;
  f32 y;
  self->vt->begin((V24A2 *) (((u8 *) self) + self->vt->adj4), a3, a4);
  if (par->f18 == 0)
  {
    y = par->f4;
  }
  else
  {
    f32 sc = self->sy;
    f32 h = ((f32) self->height) * sc;
    char *q = str;
    if ((*q) != 0)
    {
      do
      {
        if ((*(q++)) == '\n')
        {
          h += ((f32) self->height) * sc;
        }
      }
      while ((*q) != 0);
    }
    if (par->f18 == 2)
    {
      y = (par->f4 + par->fC) - h;
    }
    else
    {
      y = par->f4 + ((par->fC - h) * 0.5f);
    }
  }
  for (p = str; (*p) != 0; p = next)
  {
    f32 half = 0.5f;
    s32 right = 2;
    char c = *((u8 *) p);
    next = p + 1;
    if (c == '\n')
    {
      pending = 1;
      y += ((f32) self->height) * self->sy;
    }
    else
    {
      if (pending != 0)
      {
        if (par->f14 == 0)
        {
          x = par->f0;
        }
        else
        {
          char *q;
          x = 0.0f;
          for (q = p; (*q != 0) && (*q != '\n'); q++)
          {
            x += self->vt->width((V24A2 *) (((u8 *) self) + self->vt->adj3), *q);
          }
          if (par->f14 == right)
          {
            x = (par->f0 + par->f8) - x;
          }
          else
          {
            x = par->f0 + ((par->f8 - x) * half);
          }
        }
        pending = 0;
      }
      x += self->vt->draw(x, y, (V24A2 *) (((u8 *) self) + self->vt->adj6), *p, par->f10, a4);
    }
  }

  self->vt->end((V24A2 *) (((u8 *) self) + self->vt->adj7), a3, a4);
}

// Points recorded in order, the first of them scaled into u and v.
void func_0015C8B8(V24A2* trail, f32 su, f32 sv)
{
    V24A2_Pt* point = &trail->stack[trail->depth++];
    point->x = trail->sx;
    point->y = trail->sx;
    trail->sx = trail->stack[0].x * su;
    trail->sy = trail->stack[0].y * sv;
}

void func_0015C900(V24A2* obj) { obj->depth--; V24A2_Pt* item = &obj->stack[obj->depth]; obj->sx = item->x; obj->sy = item->y; }

V24A2* func_0015C930(V24A2* owner, f32 x, f32 y)
{
	V24A2* out = (V24A2*)func_0018D758(0x88);
	out->vt = (const V24A2_Vt*)&g_fontMethods;
	CopyFont(owner, out);
	out->sx *= x;
	out->sy *= y;
	return out;
}

void func_0015C9B0(V24A2* self, V24A2* dst)
{
    CopyFontMetrics(self, dst);
    dst->id = self->id;
    dst->imgA = self->imgA;
    dst->imgB = self->imgB;
    dst->f60 = self->f60;
    dst->f68 = self->f68;
    dst->f6C = self->f6C;
    dst->f70 = self->f70;
    dst->f74 = self->f74;
    dst->glyphCount = self->glyphCount;
    dst->glyphs = self->glyphs;
    dst->mask = self->mask;
}

s32 func_0015CA38(V24A2* a, s32 b)
{
    return FindFontGlyph(a, (s8)b) != 0;
}

f32 func_0015CA60(V24A2* self, s8 key)
{
    V24A2_Glyph* e = FindFontGlyph(self, key);
    f32 x;
    f32 y;
    if (e == 0) {
        x = self->sx;
        y = (f32)self->advance;
    } else {
        x = (f32)(e->w + 1);
        y = self->sx;
    }
    return x * y;
}

s32 func_0015CAB8(V24A2* self, void* obj)
{
    s32 r = (g_buildFrame->flags & self->mask) == 0;
    if (r != 0) {
        CloseDmaTag(obj);
        AddDmaRefTag(obj, self->f68, self->f6C);
        AddDmaRefTag(obj, self->imgA->f14, self->imgA->f10);
        if (self->imgB != 0) {
            AddDmaRefTag(obj, self->f70, self->f74);
            AddDmaRefTag(obj, self->imgB->fC, self->imgB->f8);
        }
        BeginDmaTag(obj);
        g_buildFrame->flags |= self->mask;
    }
    return r;
}

void func_0015CB88(V24A2* self, s32 a1, void* obj)
{
    SetFontClipRect(self, a1, obj);
    s32 ok = AddFontImagesToFrame(self, obj);
    BeginGifTag(obj, 6, 1, 0xE);
    if (ok != 0) {
        AddGifRegisterWrite(obj, 0x3F, 0);
    }
    s64 v = 0x31001;
    if (self->f30 != 0) {
        v = self->f38;
    }
    AddGifRegisterWrite(obj, 0x47, v);
    AddGifRegisterWrite(obj, 0x42, 0x44);
    AddGifRegisterWrite(obj, 6, self->f60);
    AddGifRegisterWrite(obj, 0x14, 0x60);
    AddGifRegisterWrite(obj, 8, 5);
    AddGifRegisterWrite(obj, 0, 0x1D6);
    BeginGifRegListTag(obj, 5, 0x43431);
}

void func_0015CC80(V24A2* self, void* obj)
{
    s32 ok = AddFontImagesToFrame(self, obj);
    BeginGifTag(obj, 6, 1, 0xE);
    if (ok != 0) {
        AddGifRegisterWrite(obj, 0x3F, 0);
    }
    AddGifRegisterWrite(obj, 6, self->f60);
    AddGifRegisterWrite(obj, 0, 0x1D6);
    BeginGifRegListTag(obj, 5, 0x43431);
}

f32 func_0015CD18(f32 x, f32 y, V24A2* self, s8 key, u32 color, V24A0* s)
{
    V24A2_Glyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->f60u >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + w;
        f32 py = y + h;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            func_00161860(s, e->u << 4, (s4 - e->v) << 4);
            func_001618C0(s, (s32)((x + 1728.0f) * 16.0f),
                          (s32)((y * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
            func_00161860(s, (e->u + e->w) << 4, (s4 - (e->v + self->height)) << 4);
            func_001618C0(s, (s32)((px + 1728.0f) * 16.0f),
                          (s32)((py * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
        }
        return (f32)(e->w + 1) * self->sx;
    }
    return (f32)self->advance * self->sx;
}

void func_0015CF70(V24A2* self, s8 key, u32 color, V24A0* s, f32 x, f32 y)
{
    V24A2_Glyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->f60u >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + h;
        f32 py = y + w;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            s32 u0 = (e->u << 4) + D_00262258;
            s32 v0 = ((s4 - e->v) << 4) + D_0026225C;
            s32 u1 = ((e->u + e->w) << 4) + D_00262258;
            s32 v1 = ((s4 - (e->v + self->height)) << 4) + D_0026225C;
            s32 ok = AddFontImagesToFrame(self, s);
            BeginGifTag(s, 6, 1, 0xE);
            if (ok != 0) {
                AddGifRegisterWrite(s, 0x3F, (u64)0);
            }
            u64 v = 0x31001;
            if (self->f30 != 0) {
                v = self->f38;
            }
            AddGifRegisterWrite(s, 0x47, (u64)v);
            AddGifRegisterWrite(s, 0x42, (u64)0x44);
            AddGifRegisterWrite(s, 6, (u64)self->f60u);
            AddGifRegisterWrite(s, 0x14, (u64)0x60);
            AddGifRegisterWrite(s, 8, (u64)5);
            AddGifRegisterWrite(s, 0, (u64)0x1D4);
            BeginGifRegListTag(s, 9, 0x434343431ULL);
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            func_00161860(s, u0, v0);
            s32 sx = (s32)((x + 1728.0f) * 16.0f);
            s32 sy = (s32)((py * 0.45454547f + 1936.0f) * 16.0f);
            func_001618C0(s, sx, sy, self->f40, 0);
            func_00161860(s, u1, v0);
            s32 sy2 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
            func_001618C0(s, sx, sy2, self->f40, 0);
            func_00161860(s, u0, v1);
            s32 sx2 = (s32)((px + 1728.0f) * 16.0f);
            func_001618C0(s, sx2, sy, self->f40, 0);
            func_00161860(s, u1, v1);
            func_001618C0(s, sx2, sy2, self->f40, 0);
            self->vt->end((V24A2*)((u8*)self + self->vt->adj7), 0, (s32)&g_gsPacketWriter);
        }
    }
}

void func_0015D338(V24A2* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, V24A0* s)
{
    color = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
    AddGifRegListFloat(s, color, 0.0f);
    func_00161860(s, (s32)(u0 * 16.0f), (s32)(v0 * 16.0f));
    func_001618C0(s, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
    func_00161860(s, (s32)(u1 * 16.0f), (s32)(v1 * 16.0f));
    func_001618C0(s, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
}

void func_0015D4E0(V24A2* self, Item_15D4E0* item, Rect_15D4E0* r, V24A0* s)
{
    V24A2_Glyph* e = FindFontGlyph(self, item->key);
    if (e != 0) {
        PushFontScale(item->f0, item->f10, item->f14);
        f32 top = r->y;
        f32 sx = self->sx;
        f32 left = r->x;
        s32 u2i = e->u + e->w;
        f32 x2 = left + r->w + item->f8 * sx;
        f32 cw = (f32)e->w * sx;
        f32 x1 = left - item->f8 * sx;
        s32 sz = 1 << (s32)((self->f60u >> 30) & 0xF);
        s32 height = self->height;
        f32 sy = self->sy;
        s32 v0i = sz - e->v;
        f32 x0 = x1 - cw;
        s32 v2i = sz - (e->v + height);
        f32 u1 = (f32)((e->u + u2i) / 2);
        f32 v1 = (f32)((v0i + v2i) / 2);
        f32 u0 = (f32)e->u;
        f32 y1 = top - item->fC * sy;
        f32 v0 = (f32)v0i;
        f32 x3 = x2 + cw;
        f32 y2 = top + r->h + item->fC * sy;
        f32 y0 = y1 - (f32)height * sy;
        f32 y3 = y2 + (f32)height * sy;
        self->vt->begin((V24A2*)((u8*)self + self->vt->adj4), 0, (s32)s);
        f32 v2 = (f32)v2i;
        f32 u2 = (f32)u2i;
        DrawFontQuad(self, item->color, x0, y0, x1, y1, u0, v0, u1, v1, s);
        DrawFontQuad(self, item->color, x2, y0, x3, y1, u1, v0, u2, v1, s);
        DrawFontQuad(self, item->color, x0, y2, x1, y3, u0, v1, u1, v2, s);
        DrawFontQuad(self, item->color, x2, y2, x3, y3, u1, v1, u2, v2, s);
        DrawFontQuad(self, item->color, x1, y0, x2, y1, u1, v0, u1, v1, s);
        DrawFontQuad(self, item->color, x1, y2, x2, y3, u1, v1, u1, v2, s);
        DrawFontQuad(self, item->color, x0, y1, x1, y2, u0, v1, u1, v1, s);
        DrawFontQuad(self, item->color, x2, y1, x3, y2, u1, v1, u2, v1, s);
        DrawFontQuad(self, item->color, x1, y1, x2, y2, u1, v1, u1, v1, s);
        PopFontScale(item->f0);
        self->vt->end((V24A2*)((u8*)self + self->vt->adj7), 0, (s32)s);
    }
}

void func_0015C2E8();
void func_0015C3C0();
void func_0015C930();
void func_0015CA38();
void func_0015CA60();
void func_0015CB88();
void func_0015CC80();
void func_0015CD18();
void func_0015CF70();
void func_0015D4E0();
void func_001FBDF8();
extern const VEnt_0024A220 D_0024A220[22] = {{0, 0}, {0, func_0015C930}, {0, func_0015CA38}, {0, func_0015CA60}, {0, func_0015CB88}, {0, func_0015CC80}, {0, func_0015CD18}, {0, func_0015C3C0}, {0, func_0015CF70}, {0, func_0015D4E0}, {0, 0}, {0, 0}, {0, func_001FBDF8}, {0, func_001FBDF8}, {0, func_001FBDF8}, {0, func_0015C2E8}, {0, func_001FBDF8}, {0, func_001FBDF8}, {0, func_0015C3C0}, {0, func_001FBDF8}, {0, func_001FBDF8}, {0, 0}};

void func_0015D8A8(V24A2* obj, void* src)
{
    Local_15D8A8 l;
    ReadBufferedStreamBytes(src, 0x10, &l);
    s32 idx = l.b7;
    obj->id = idx;
    g_fonts[idx] = (s32)obj;
    obj->imgA = (V24A2_ImgA*)((u8*)g_imageRecordsA + l.u0 * 32);
    void* t;
    if (l.u2 != 0xFFFF) {
        t = (u8*)g_imageRecordsB + l.u2 * 24;
    } else {
        t = 0;
    }
    obj->imgB = (V24A2_ImgB*)t;
    s32 n = l.uC;
    s32 A = l.b4, B = l.b5, C = l.b6; f32 F = l.f8;
    obj->f00 = A;
    obj->sx = F;
    obj->glyphCount = n;
    obj->height = C;
    obj->advance = B;
    obj->sy = F;
    obj->glyphs = (V24A2_Glyph*)AllocateFrontMemory(n << 3);
    ReadBufferedStreamBytes(src, obj->glyphCount << 3, obj->glyphs);
}

void func_0015D998(V24A2* self, void* arg)
{
    Frame_15D998 f;
    s32 n;

    (void)InitGifPacket(&f.a);
    V24A2_ImgA* q = self->imgA;
    n = AllocateBump(arg, q->f0A);
    BuildImageTexRegister(self->imgA, n);
    self->f60u = self->imgA->f18;
    UsePacketBufferMemory(&f.a, 16, f.buf);
    StartImageUpload(self->imgA, n, &f.a);
    DetachPacketBufferCopy(&f.a, &self->f68, 0, &self->f6C, 7);
    if (self->imgB != 0) {
        n = AllocateBump(arg, self->imgB->f6);
        BuildPaletteTexRegister(self->imgB, n);
        u64 t = self->f60u;
        t |= self->imgB->f10;
        self->f60u = t;
        UsePacketBufferMemory(&f.a, 16, f.buf);
        StartPaletteUpload(self->imgB, n, &f.a);
        DetachPacketBufferCopy(&f.a, &self->f70, 0, &self->f74, 7);
    }
}

// EXACT: element address written as off + (u32)entries

V24A2_Glyph* func_0015DAB8(V24A2* self, u8 key)
{
    s32 lo = 0;
    s32 hi = self->glyphCount - 1;

    if (hi >= 0) {
        do {
            s32 mid = (hi + lo) / 2;
            s32 off = mid * 8;
            V24A2_Glyph* e = (V24A2_Glyph*)(off + (u32)self->glyphs);
            s32 d = key - e->key;

            if (d == 0) {
                return e;
            }
            if (d > 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } while (!(hi < lo));
    }
    return 0;
}

TextReader* func_0015DB28(TextReader* self, s32 a1, s32 a2)
{
    self->inlineFont.vt = (const V24A2_Vt*)&g_fontMethods;
    self->text = a1;
    self->defaultFont = (V24A2*)a2;
    self->inlineFontColorBits = 0xFF808080;
    self->defaultColorBits = 0xFF808080;
    self->baseColorBits = 0xFF808080;
    self->colorBits = 0xFF808080;
    RewindTextReader(self);
    return self;
}

void func_0015DB80(TextReader* self)
{
    s32 t;
    self->cur = (char*)self->text;
    self->font = self->defaultFont;
    t = ((U32P*)((u8*)self + 0xA4))->v;
    ((U32P*)((u8*)self + 0xA0))->v = t;
    t = ((U32P*)((u8*)self + 0xA0))->v;
    ((U32P*)((u8*)self + 0x9C))->v = t;
    self->fontChanged = 0;
}

void func_0015DBB8(u8* dst, u8* src)
{
    s32 v = ((U32P*)src)->v;
    ((U32P*)(dst + 0xA4))->v = v;
    v = ((U32P*)(dst + 0xA4))->v;
    ((U32P*)(dst + 0x9C))->v = v;
}

s32 func_0015DBE0(TextReader* self)
{
    s32 done = 0;
    s32 changed = 1;
    V24A2* inl = &self->inlineFont;
    do {
        char* p = self->cur;
        switch (*p) {
        case '~':
            if (p[1] == '~') {
                self->cur = p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->baseColor = self->defaultColor;
                self->color = self->baseColor;
                self->cur += 2;
            } else {
                char* q = p + 1;
                u32 acc = 0;
                while (*q != 0 && q - self->cur < 7) {
                    u32 ch = (u8)*q;
                    u32 d;
                    if (ch - '0' < 10)
                        d = (s8)ch - '0';
                    else if (ch - 'A' < 6)
                        d = (s8)ch - 55;
                    else if (ch - 'a' < 6)
                        d = (s8)ch - 87;
                    else
                        break;
                    q++;
                    acc = (acc << 4) + d;
                }
                if (q - self->cur >= 7) {
                    self->baseColor.r = ((acc >> 16) & 0xFF) + 1 >> 1;
                    self->baseColor.g = ((acc & 0xFF00) >> 8) + 1 >> 1;
                    self->baseColor.b = (acc & 0xFF) + 1 >> 1;
                    self->color = self->baseColor;
                    self->cur += 7;
                } else {
                    self->font = self->defaultFont;
                    self->color = self->defaultColor;
                    done = 1;
                }
            }
            break;
        case '&':
            if (p[1] == '&') {
                self->cur = p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->font = self->defaultFont;
                self->color = self->baseColor;
                self->fontChanged = changed;
                self->cur += 2;
            } else {
                V24A2* nf = (V24A2*)FindFontByKeyChar(p[1]);
                if (nf != 0) {
                    CopyFont(nf, inl);
                    self->cur += 2;
                    V24A2* d = self->defaultFont;
                    f32 ratio = ((f32)d->height * d->sy) / ((f32)inl->height * inl->sy);
                    self->font = inl;
                    u8 al = self->color.a;
                    self->inlineFont.sx *= ratio;
                    self->inlineFont.sy *= ratio;
                    Rgba4 t = self->inlineFontColor;
                    t.a = al;
                    self->color = t;
                    self->fontChanged = changed;
                } else {
                    self->font = self->defaultFont;
                    done = 1;
                    self->color = self->defaultColor;
                    self->fontChanged = changed;
                }
            }
            break;
        case '^':
            if (p[1] == '^') {
                self->cur = p + 1;
                done = 1;
            } else if (p[1] == '.') {
                PopFontScale(self->font);
                self->cur += 2;
            } else {
                f32 a = (f32)(p[1] - '0') + (f32)(p[2] - '0') * 0.1f;
                V24A2* f = self->font;
                PushFontScale(f, a * f->sx, a * f->sy);
                self->cur += 3;
            }
            break;
        default:
            done = 1;
            break;
        }
    } while (done == 0);
    char* e = self->cur;
    char r = *e;
    self->cur = e + 1;
    return r;
}

s32 func_0015DF58(void* self)
{
    s32 n = 0;
    RewindTextReader(self);
    while (ReadTextChar(self) != 0) {
        n++;
    }
    return n;
}

void func_0015DFA0(Cursor_15DFA0* self, s32 n)
{
    RewindTextReader(self);
    for (;;) {
        if (ReadTextChar(self) == 0) {
            break;
        }
        if (n == 0) {
            break;
        }
        n--;
    }
    *self->flag = 0;
}

f32 func_0015DFF8(TextReader* self)
{
    f32 acc = 0.0f;
    RewindTextReader(self);
    s32 item;
    while ((item = ReadTextChar(self)) != 0) {
        V24A2* holder = self->font;
        const V24A2_Vt* disp = holder->vt;
        acc += disp->width((V24A2*)((u8*)holder + disp->adj3), item);
    }
    return acc;
}

s32 func_0015E068(Lines_15E068* self, f32 limit)
{
    s32 lines = 1;
    f32 width = 0.0f;
    s32 newline = 10;
    s32 space = 32;
    s32 tab = 9;
    RewindTextReader(self);
    s32 c;
    while ((c = ReadTextChar(self)) != 0) {
        if (c == newline) {
            width = 0.0f;
            lines++;
        } else {
            V24A2* holder = self->holder;
            const V24A2_Vt* glyph = holder->vt;
            width += glyph->width((V24A2*)((u8*)holder + glyph->adj3), c);
        }
        if (limit != 0.0f && limit < width) {
            s8* p = self->cur - 1;
            while (p >= self->start) {
                if (*p == 10) {
                    break;
                }
                if (*p == space || *p == tab) {
                    width = 0.0f;
                    self->cur = p + 1;
                    lines++;
                    *p = 10;
                    break;
                }
                p--;
            }
            if (width != 0.0f) {
                *self->cur = (s8)newline;
                lines++;
                width = 0.0f;
            }
        }
    }
    return lines;
}

f32 func_0015E1B0(TextReader* self)
{
    V24A2* holder = self->defaultFont;
    f32 width = (f32)holder->height * holder->sy;
    s32 lines = WrapTextLines(self);
    return width * (f32)lines;
}

ASM_FUNC(func_0015E1F0);

void func_0015E290(void* self, f32 f, f32* out1, f32* out2)
{
    s32 n = WrapTextLines(self, f);
    f32 g = func_0015E1F0(self);
    TextReader* o = (TextReader*)self;
    f32 k = (f32)o->defaultFont->height * o->defaultFont->sy;
    f32 t = (f32)n * k;
    if (out1 != 0) {
        *out1 = g;
    }
    if (out2 != 0) {
        *out2 = t;
    }
}

void func_0015E318(TextReader* self, Layout_137228* p, s32 x, s32 y)
{
    f32 f[64];
    Rgba_137248 u;
    s32 first = 1;
    s32 n = 0;
    f32 top;
    f32 left;
    s32 c;
    func_001F5C0C(f, 0, 0x100);
    RewindTextReader(self);
    while ((c = ReadTextChar(self)) != 0) {
        if (c == 10) {
            n++;
        } else {
            f[n] += ((Font_15E318*)self->font)->Width(c);
        }
    }
    c = (s32)p->f18;
    if (c == 0) {
        top = p->y;
    } else {
        f32 tot = (f32)(n + 1) * ((f32)self->defaultFont->height * self->defaultFont->sy);
        if (c == 2)
            top = (p->y + p->h) - tot;
        else
            top = p->y + (p->h - tot) * 0.5f;
    }
    u = p->color;
    SetTextDefaultColor(self, &u);
    Font_15E318* started = 0;
    f32 half = 0.5f;
    RewindTextReader(self);
    s32 right = 2;
    f32* fp = f;
    while ((n = ReadTextChar(self)) != 0) {
        if (n == 10) {
            first = 1;
            fp++;
            top += (f32)self->defaultFont->height * self->defaultFont->sy;
            continue;
        }
        if (first) {
            if (p->f14 == 0) {
                left = p->x;
            } else {
                f32 g = *fp;
                if (p->f14 == right)
                    left = (p->x + p->w) - g;
                else
                    left = p->x + (p->w - g) * half;
            }
            first = 0;
        }
        if (started == 0) {
            ((Font_15E318*)self->font)->Begin(x, y);
            started = (Font_15E318*)self->font;
        } else if (self->fontChanged != 0) {
            ((Font_15E318*)self->font)->Flush(y);
            self->fontChanged = 0;
        }
        left += ((Font_15E318*)self->font)->Draw(left, top, n, self->colorBits, y);
    }
    ((Font_15E318*)self->font)->End(x, y);
}

void func_0015E5F0(void)
{
    u8 buf[16];
    InitBumpAllocator(buf, 0x1400, 0x1E00);
    for (s32 i = 0; i < g_fontCount; i++) {
        UploadFontImages(g_fontRecords + i * 0x88, buf);
    }
}

LINKER_REMNANT(func_0015E678);

ASM_FUNC(func_0015E6A8);

void func_0015E810(void)
{
    for (u32 i = 0; i < 2; i++) {
        RenderFrame* r = &g_renderFrames[i];
        r->bufA = (u8*)D_002C3B00 + i * 0x80000;
        r->bufB = D_003C3B00 + i * 0x100000;
        r->f10 = D_005C3B00 + i * 0x10600;
        func_00152438(&r->l20, 0x630);
        func_00152438(&r->l2C, 0x1090);
        func_00152438(&r->l38, 0xB8);
    }
    func_00152438(&D_002622E0, 0x630);
    func_00152438(&D_002622F0, 0x1090);
    func_00152438(&g_deferredReleaseListC, 0xB8);
    func_001F6950(5, (void (*)(void))((u8*)func_0015E678 + 0x30), 0);
    func_001F6DA8(5);
    g_frameReadySemaphore = CreateLockSemaphore(0, 2);
    g_frameDoneSemaphore = CreateLockSemaphore(2, 2);
    u32* tab = (u32*)D_002C3B00;
    s32 n = 0;
    do {
        u32 c = n;
        s32 off = n * 4;
        for (s32 k = 7; k >= 0; k--) {
            if (c & 1) c = (c >> 1) ^ 0xEDB88320;
            else c >>= 1;
        }
        *(u32*)((u8*)tab + off) = c;
        n++;
    } while (n < 256);
    func_001F6A20(g_mainAndRenderThreads[1], 0);
}

void func_0015E9F0(void)
{
    s32 idx;

    func_00191E70(3);
    func_001F6B60(g_frameDoneSemaphore);
    idx = g_nextBuildFrameIndex;
    g_nextBuildFrameIndex = idx + 1;
    g_buildFrame = &g_renderFrames[idx];
    if ((u32)(idx + 1) >= 2) {
        g_nextBuildFrameIndex = 0;
    }
    ReleaseFrameNodes(g_buildFrame);
    {
        RenderFrame* slot = g_buildFrame;
        s32 v = *(s32*)((u8*)g_camera + 0x21C);
        slot->flags = 0;
        slot->f44 = v;
        slot->f1C = 0;
        UsePacketBufferMemory(&g_gsPacketWriter, 0x8000, slot->bufA);
    }
    UsePacketBufferMemory(&g_vifPacketWriter, 0x10000, g_buildFrame->bufB);
    g_buildFrameData = g_buildFrame->i10;
    BeginDmaTag(&g_gsPacketWriter);
    BeginDmaTag(&g_vifPacketWriter);
}

void func_0015EAE0(void* list, s32 value, s32 end)
{
    if (D_0026230C != value) {
        D_0026230C = value;
        AddDmaRefTag(list, ((u32)(end - value) + 15) >> 4, value);
    }
}

void func_0015EB20(void* self, void* p, s32 n)
{
    Frame_15EB20 fr;
    void* buf = fr.obj;
    InitGifPacket(buf);
    UsePacketBufferMemory(buf, 8, fr.scratch);
    BeginGifTag(buf, 0, 1, 0xE);
    AddGifRegisterWrite(buf, 0x61, 0);
    EndGifPacket(buf);
    WriteVifFlush(self);
    WriteVifDirectFromWriter(self, buf);
    AddDmaRefTagIfChanged(self, D_00212160, D_00215C50);
    AddDmaEndTag(self);
    DetachPacketBuffer(self, p, n);
}

void func_0015EBF0(void* obj, void* a, s32 b)
{
    BeginGifTag(obj, 0, 1, 0xE);
    AddGifRegisterWrite(obj, 0x61, 0);
    EndGifPacket(obj);
    AddDmaEndTag(obj);
    DetachPacketBuffer(obj, a, b);
}

void func_0015EC68(void)
{
    WriteGsFinishPacket(&g_vifPacketWriter, (u8*)g_buildFrame + 8, 0);
    CloseDrawBuffer(&g_gsPacketWriter, g_buildFrame, 0);
    g_buildFrame->l20 = D_002622E0;
    ClearList(&D_002622E0);
    g_buildFrame->l2C = D_002622F0;
    ClearList(&D_002622F0);
    g_buildFrame->l38 = g_deferredReleaseListC;
    ClearList(&g_deferredReleaseListC);
    g_buildFrameData = 0;
    g_buildFrame = 0;
    func_001F6B40(g_frameReadySemaphore);
}

void func_0015ED50(RenderFrame* self)
{
    g_drawFrameData = self->i10;
    SwitchActiveImageMask(self->f44);
    if (self->f1C != 0 && D_00274538 != 0) {
        *(volatile s32*)0x10003010 = 4;
        func_00202A80(g_gifChannel, D_00274538);
    }
}

void func_0015EDB8(void)
{
    const u8* table = (const u8*)D_002C3B00;
    s32 n = (s32)D_00148D74;
    u32 crc = 0xFFFFFFFF;
    u32* p = (u32*)0x00100000;
    if (n > 0) {
        do {
            u32 w = *p;
            n -= 4;
            p++;
            crc = *(u32*)(table + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
        } while (n > 0);
    }
    if (crc != 0) {
        g_codeChecksumFailed = 1;
    }
}

void func_0015EE80(void)
{
    VerifyCodeChecksum();
    for (;;) {
        g_renderThreadWaiting = 1;
        func_001F6B60(g_frameReadySemaphore);
        g_renderThreadWaiting = 0;
        g_drawingFrame = &g_renderFrames[D_00262314];
        D_00262314++;
        if (D_00262314 >= 2) {
            D_00262314 = 0;
        }
        func_0015ED50((RenderFrame*)g_drawingFrame);
        func_001684E8();
        func_001686E8(g_vif1Channel, ((RenderFrame*)g_drawingFrame)->bufBAddr);
        *(volatile s32*)0x10003010 = 0;
        func_001686E8(g_gifChannel, ((RenderFrame*)g_drawingFrame)->bufAAddr);
        func_0015F320();
        func_00202C38(g_vif1Channel, 0, 0);
        func_001F6B40(g_frameDoneSemaphore);
        FlipDisplayFrame();
        D_002626CC = 1;
    }
}

void func_0015EF88(Pair_15EF88* self, s32 flag)
{
    func_0015ED50(self, flag);
    func_001686E8(g_vif1Channel, self->fC);
    if (flag != 0) {
        *(volatile s32*)0x10003010 = 0;
        func_001686E8(g_gifChannel, self->f4);
    }
}

void func_0015EFE8(RenderFrame* self)
{
    Iter_15EFE8 it;
    Node_15EFE8* n;
    if (IsListEmpty(&self->l20) == 0) {
        Begin_15EFE8::Of(&it, &self->l20);
        while ((n = Next_15EFE8::Of(&it)) != 0) {
            RemoveFromList(&self->l20, n);
            AppendToList(n->f14 + 0x1CC0, n);
        }
        ClearList(&self->l20);
        g_activeListFrames = (ListFrame*)it.prev;
    }
    if (IsListEmpty(&self->l2C) == 0) {
        Begin_15EFE8::Of(&it, &self->l2C);
        while ((n = Next_15EFE8::Of(&it)) != 0) {
            if (n->f1088 != 0) {
                PushFreeSlot((u8*)g_currentWorld + 0x1B4C, n->f1088);
            }
            RemoveFromList(&self->l2C, n);
            PushFreeSlot((u8*)g_currentWorld + 0x1B40, n);
        }
        ClearList(&self->l2C);
        g_activeListFrames = (ListFrame*)it.prev;
    }
    if (IsListEmpty(&self->l38) == 0) {
        Begin_15EFE8::Of(&it, &self->l38);
        while ((n = Next_15EFE8::Of(&it)) != 0) {
            RemoveFromList(&self->l38, n);
            PushFreeSlot((u8*)g_currentWorld + 0x1BF4, n);
        }
        g_activeListFrames = (ListFrame*)it.prev;
    }
}

void func_0015F210(s32 flag)
{
    for (s32 i = 0; (u32)i < 2; i++) {
        func_001F6B60(g_frameDoneSemaphore);
    }
    for (s32 i = 0; (u32)i < 2; i++) {
        func_001F6B40(g_frameDoneSemaphore);
    }
    while (g_renderThreadWaiting == 0) {
    }
    if (flag != 0 && g_drawingFrame != 0) {
        s32 n = 2;
        do {
            SendRenderFrameToDma(g_drawingFrame, 1);
            func_0015F320();
            FlipDisplayFrame();
        } while (--n >= 0);
        D_002626CC = 3;
    }
    u8* p = (u8*)g_renderFrames;
    u8* end = p + 0x90;
    do {
        ReleaseFrameNodes(p);
        p += 0x48;
    } while (p < end);
    func_00191EB0(3);
    g_drawingFrame = 0;
}

INCLUDE_ASM(func_0015F320);

void func_0015F618(s32 flag, s32 code)
{
    if (code == 0xFFFF && flag != 0) {
        InitGifPacket(&g_gsPacketWriter);
        InitPacketWriter(&g_vifPacketWriter);
    }
}

void func_0015F658(void)
{
    func_0015F618(1, 0xFFFF);
}
