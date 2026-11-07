// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x19E040 to 0x1A7FE8, built whole (config/us/files.tsv): one file between
// two exact edges, which could be several. It holds the effect owner (class 0x1E) and the effects
// it runs (func_0019EA78 creates one; func_0019E908 picks its kind's table of functions, the 27
// tables at 0x219C20 in src/main/0019C000.cpp), with their VU0 helpers; then class 0x15, the pair
// controller (class 0x5F) and the paired objects (class 0x42), classes 0x43, 0x44 and 0x45 and
// the pad pattern player. Its .rodata (0x24C930 to 0x24CBC4) is the FLT_MAX constants of the VU0
// functions and of func_001A1DF0 and func_001A54F8 (literals in their code), the jump tables, the
// triangle func_001A3C40 copies and the pose table func_001A4718 copies; its .data (0x26B530 to
// 0x26C3E0) is the globals below. Named after its first address until what it was is known.
#include "common.h"
#include "list_iter.h"
#include "c8b.h"
#include "effect_owner.h"
#include "effect_spawner.h"
#include "world.h"
#include "camera.h"
#include "object_gatherer.h"
#include "switched_collider.h"
#include "v24a0.h"
#include "effect.h"
#include "globals.h"
#include "group_marker.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "paired_object.h"
#include "hit_target.h"
#include "sound_state_object.h"
#include "object_creator.h"
#include "object_pool.h"
#include "pair_controller.h"
#include "screen_element.h"
#include "shapes.h"
#include "object_link.h"
#include "target_binding.h"
#include "game_progress.h"
#include "asm_func.h"

struct Obj_0019F8E8 { u8 pad[0x44]; s32 value; };
void func_001831E8(void* world, void* list, void* a, void* b);
void func_00183238(void* world, void* list, void* a, void* b);

struct Buf_19DF48 { u8 raw[0x30]; };

typedef void (*Fn_19DF48)(void);

void func_001B7968(Collider* self);

void func_00152438(void* p, s32 n);

void* func_001B5EA0(void* p);

void func_001F5C0C(void* p, s32 zero, s32 size);

const Vt219C* func_0019E908(u32 n);

void func_00152470(void* list, void* item);

void func_0019EC20(Effect* self);

void func_00152600(void* table, void* self);

void func_0019EC30(Effect* self);

void func_001DBC18(void* a, void* b);

void func_001B5F28(void* a, void* b);

extern f32 D_00261858[];

void func_0019EB28(Effect* self);

struct __attribute__((aligned(16))) Vec_19D2A8 { s32 a, b, c, d; };

struct Frame_19D2A8 { Vec_19D2A8 q0; Vec_19D2A8 q1; s32 w20; s32 w24; };

extern f32 D_0026185C;

void func_0019EBE8(Effect* self);

s32 func_00182FC8(void* p);

s32 func_0013E658(void* a, s32 b);

void func_001F2EF0(f32 f, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5);

s32 func_0019F620(void* self, void* a1, void* a2, void* a3);

struct Frame_19E848 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

struct ColorFade;

typedef void (*VFn_19D6C0)(ColorFade* self, void* arg, s32 z);

struct Frame_19D6C0 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

struct Slot_2622D8 { u8 pad00[0x1C]; s32 r1C; };

struct Scratch_19F9D0 { Quad219C head; u8 rest[0x700 - 16]; };

s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);

Effect* func_0019EA78(s32 kind, EffectOwner* sys);

struct Ctx_19DBB0 { u8 pad0[0x2F4]; s32 idx2F4; };

extern Camera* D_00261990;

struct __attribute__((aligned(16))) Vec_19D338 { s32 a, b, c, d; };

struct Frame_19D338 {
    Vec_19D338 q0;
    Vec_19D338 q1;
    Vec_19D338 q2;
    Vec_19D338 q3;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
};

typedef s32 (*Slot_19D338)(void* self, void* a1, s32 a2, void* a3, s32 a4, s32 a5, f32 f, void* a6);

struct Obj_19D338 { Slot_19D338* vtbl; };

struct Src_19D338 {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x34 - 0x1C];
    Obj_19D338* f34;
};

s32 func_00128018(void* a, s32 b, void* c, void* d);

struct Cursor_19E168;

struct Cursor_19E168 {
    void* link;
    u8* at;
    s32 stride;
    Cursor_19E168* prev;
    Cursor_19E168(void* l) {
        link = l;
        at = (u8*)l;
        stride = ((s32*)l)[2];
        prev = ((Cursor_19E168*)D_0027B314);
        D_0027B314 = (ListFrame*)this;
    }
    Effect* first() {
        Effect* n = *(Effect**)link;
        at = (u8*)n + stride;
        return n;
    }
    Effect* next() {
        Effect* n = *(Effect**)at;
        at = (u8*)n + stride;
        return n;
    }
    ~Cursor_19E168() { D_0027B314 = (ListFrame*)prev; }
};

void func_0019EBE8(Effect* node);

void func_001B7B78(Collider* self);

struct Stream_19C470;

void func_0019CC10(f32 x, f32 y, f32 z, C8B* o, void* p);

// An entry of the effect kinds' tables of functions (src/main/0019C000.cpp).
typedef void (*Fn_Table)();

extern const Fn_Table D_00219C20[];

extern const Fn_Table D_00219C40[];

extern const Fn_Table D_00219C60[];

extern const Fn_Table D_00219C80[];

extern const Fn_Table D_00219CA0[];

extern const Fn_Table D_00219CC0[];

extern const Fn_Table D_00219CE0[];

extern const Fn_Table D_00219D00[];

extern const Fn_Table D_00219D20[];

extern const Fn_Table D_00219D40[];

extern const Fn_Table D_00219D60[];

extern const Fn_Table D_00219D80[];

extern const Fn_Table D_00219DA0[];

extern const Fn_Table D_00219DC0[];

extern u8 D_00219DE0[];

extern const Fn_Table D_00219E00[];

extern const Fn_Table D_00219E20[];

extern const Fn_Table D_00219E40[];

extern const Fn_Table D_00219E60[];

extern const Fn_Table D_00219E80[];

extern const Fn_Table D_00219EA0[];

extern const Fn_Table D_00219EC0[];

extern const Fn_Table D_00219EE0[];

extern const Fn_Table D_00219F00[];

extern const Fn_Table D_00219F20[];

extern const Fn_Table D_00219F40[];

extern const Fn_Table D_00219F60[];

// The loop walks an intrusive list with an iterator that registers itself on a global stack
// (D_0027B314) for its lifetime and unregisters in its destructor.
typedef void (*VFn_19C068)(void *self);

typedef void (*VFn2_19C068)(void *self, void *x);

struct Frame_19C068;

struct Frame_19C068 {
    List01 *list;
    s32 *cur;
    s32 step;
    Frame_19C068 *prev;
    Frame_19C068(List01 *l)
    {
        list = l;
        cur = (s32 *)&l->head;
        step = l->offset;
        prev = ((Frame_19C068*)D_0027B314);
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_19C068() { D_0027B314 = (ListFrame*)prev; }
    s32 Next()
    {
        s32 n = *cur;
        cur = (s32 *)(n + step);
        return n;
    }
};

struct Ob_19C068 {
    VFn_19C068 *vtbl;
};

void func_00152600(List01 *a, ObjectGatherer *b);

void func_00152470(List01 *a, ObjectGatherer *b);

struct Buf_19C068 { s32 w[4]; };

void func_00128018(void *a, s32 b, void *c, struct Buf_19C068 *d);

void func_0019ECE0();

void func_0019ED58();

void func_0019F390();

void func_0019FA98();

void func_0019FB08();

void func_0019FCE8();

void func_0019FD08();

void func_0019FE50();

void func_0019FF20();

void func_001A0020();

void func_001A0040();

void func_001A00A0();

void func_001A01B8();

void func_001A0258();

void func_001A0318();

void func_001A05D8();

void func_001A0758();

void func_001A09C0();

void func_001A0A78();

void func_001A0B20();

void func_001A0BA0();

void func_001A0C50();

void func_001A0C98();

void func_001A0D60();

void func_001A0DF0();

void func_001A0F88();

void func_001A1410();

void func_001A1458();

void func_001A1498();

void func_001A14A0();

void func_001A15D8();

void func_001A22C8();

void func_001A22E0();

s32 func_001A25F0();

void func_001A26B0();

void func_001A26F8();

void func_001A2770();

void func_001A2830();

s32 func_001A2A68();

void func_001A2B48();

void func_001A2D30();

void func_001A2D88();

void func_001A2E68();

void func_001A3008();

s32 func_001A3128();

void func_001A31A0();

void func_001A31F0();

void func_001A3250();

void func_001A3598();

void func_001A3730();

void func_001A38F0();

void func_001A3990();

void func_001A39C8();

void func_001A3A18();

void func_0019EC20(Effect* node);

void func_0019EC30(Effect* node);

u32 func_00152720(List01* list);

void func_0019E558(EffectOwner* self);

void func_00129DF8(PlacedObject* self);

struct Iter_19E420 { List01* list; u8* link; s32 offset; Iter_19E420* saved; };

struct Next_19E420 {
    static Effect* Of(Iter_19E420* it)
    {
        Effect* obj = *(Effect**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_19E420 {
    static void Of(Iter_19E420* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_19E420*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_0019CC10(C8B* self, f32* out, f32 a, f32 b, f32 c);

struct Iter_19E558 { List01* list; u8* link; s32 offset; Iter_19E558* prev; };

struct Begin_19E558 {
    static void Of(Iter_19E558* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (Iter_19E558*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_19E558 {
    static u8* Of(Iter_19E558* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct End_19E558 {
    static void Of(Iter_19E558* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};

struct Hit_19E558 { u8 pad0[0x40]; f32 weight; u8 pad44[0x2C]; };

void func_0018D608(void);

void* func_0018D658(s32 size);

void func_0018D6F0(void);

s32 func_0013E430(u8* a0, u8* a1, void** a2, f32 scale);

s32 func_00141C90(Collider* self, void* a1, void* a2, void* a3, s32 a4, Hit_19E558* a5);

u32 func_00152720(List01* p);

struct Pkt_19DDA0;

void func_0019F560(Effect* self);

s32 func_00182FC8(s32 handle);

void func_001BAC30(void* self);

void func_00124DF8(void* self, s32 n, void* data);

extern Quad219C D_00275C50;

void func_001A0338(void* self, s32 kind, s32 extra);

void func_001A0040(Effect* self);

void func_001A1DF0(Effect* self, s32 n);

struct Item_1A1F18 { u8 pad0[0x20]; f32 key20; };

struct Src_1A22C8 { u8 pad0[0x1DC]; s32 f1DC; u8 pad1[0x10]; s32 f1F0; };

struct Obj_1A25F0 { u8 pad0[0x50]; void* f50; };

extern s32 D_0026B6C0[4];

void func_001A2380(Effect* self, s32 v, void* other, void* a2, void* a3, s32 zero);

s32 func_001300E8(void* self, s32 kind);

s32 func_0019ED58(Effect* a, void* b, void* c, void* d);

struct Obj_1A3128 { u8 pad0[0x50]; void* p50; };

typedef void (*VFn_1A38F0)(void* self);

struct Obj_1A38F0 { VFn_1A38F0* vtbl; };

void func_001A35F0(Effect* self);

void func_0019F858(Effect* self);

void func_00128018(void* a0, void* a1, void* a2, void* a3);

void func_00128150(void* a0, void* a1, void* a2, void* a3);

struct Other_1A2A68 { u8 pad0[0x50]; void* f50; };

s32 func_001300E8(void* node, s32 kind);

void func_001A2380(Effect* self, s32 v, void* other, void* a2, void* a3, void* out);

struct Self_1A2B18 { u8 pad0[0x7C]; void* f7C; };

struct Other_1A2B18 { u8 pad0[0x538]; u64 f538; };

struct Src_1A2D30 { u8 pad0[0x7C]; void* link; u8 pad1[0x1F0 - 0x80]; s32 f1F0; s32 f1F4; };

extern f32 D_0026B5B0[4];

extern f32 D_0026B5C0[4];

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

struct Other_1A39C8 {
    u8 pad000[0x7C];
    void* p7C;
    u8 pad080[0x1F0 - 0x80];
    s32 i1F0;
    f32 f1F4;
};

typedef void (*VFn_1A3B58)(void* self);

void func_00124A48(void* self);

void func_00124DF8(void* self, s32 a1, void* a2);

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void* func_001B6290(void* a, void* b, s32 c, s32 d);

s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

void func_001A4070(void* self, s32 n);

void func_001A42C8(void* self, s32 v);

struct Src_1A3F40 { u8 pad_000[0x48]; f32 f48; u8 pad_04C[0x7C - 0x4C]; f32 f7C; };

void func_00144FF8(void* a, void* b, s32 c, void* d);

extern f32 D_0026B710[4];

extern f32 D_0026B720[4];

void func_0019EB28(Effect* self, f32 x);

struct Quad_1A3A18 { s32 a, b, c, d; } __attribute__((aligned(16)));

struct Buf_1A3A18 { s32 n; u8 pad[0x1C]; Quad_1A3A18 q; u8 tail[0x20]; };

typedef void (*Fn_1A3A18)(void* self, void* arg);

void func_0019F560(Effect* self, f32 s);

typedef int V128_1A0258 __attribute__((mode(TI)));

void func_0019EB28(Effect* self, f32 f);

void func_00118CF0(void* out, f32 f);

void* func_00118D10(void* out, void* in);

V128_1A0258 func_00118D30(V128_1A0258 a, V128_1A0258 b);

void* func_00118D20(void* dst, V128_1A0258 v);

extern f32 D_0026B570[4];

extern f32 D_0026B580[4];

extern f32 D_0026B5D0[4];

extern f32 D_0026B5E0[4];

void func_001A0338(void* self, s32 kind, void* extra);

typedef int V128_1A01B8 __attribute__((mode(TI)));

V128_1A01B8 func_00118D30(V128_1A01B8 a, V128_1A01B8 b);

void* func_00118D20(void* dst, V128_1A01B8 v);

extern f32 D_0026B560[4];

struct Inner_1A3C40;

struct Src_1A3C40;

struct Ptr_1A3C40;

struct Out_1A3C40;

typedef void (*VFn_1A3C40)(Inner_1A3C40* self, void* a);

struct Tri_1A3C40 { s64 a __attribute__((packed)); s32 b; };

struct Inner_1A3C40 {
    VFn_1A3C40* vtbl;   // 0x00
    u8 pad04[0x10C];
    f32 f110;           // 0x110
    f32 f114;           // 0x114
};

struct Frame_1A3C40 {
    f32 buf[4];         // 0x00
    u8 pad10[0x20];
    Tri_1A3C40 tri;     // 0x30
    u8 pad3c[0x04];
};

extern const f32 D_0024C9C0[4];

extern f32 D_00261860;

void func_0012E760(Ptr_1A3C40* obj);

void func_001A3F40(C15* self, Src_1A3C40* src);

void func_001ED650(Out_1A3C40* out, f32 unused, f32 scale, f32 z);

f32 func_00205778(f32 a, f32 b);

f32 func_001EA728(u8* p, s32 a, f32 b, f32 c, f32 d);

void func_001892A0(f32* out, f32 unused, f32 value);

extern f32 D_0026B6A0[4];

extern f32 D_0026B6B0[4];

void func_001921A8(void* self);

typedef int V128_1A09C0 __attribute__((mode(TI)));

V128_1A09C0 func_00118D30(V128_1A09C0 a, V128_1A09C0 b);

void* func_00118D20(Quad219C* dst, V128_1A09C0 v);

extern f32 D_0026B590[4];

extern f32 D_0026B5A0[4];

void func_001A76A0(void* child, int flag);

void func_00124DF8(void* self, int idx, void* table);

void func_00159478(void* sub, void* self);

struct Blob8_1A6540 { u8 b[8]; };

void func_001BA130(void* self);

typedef void (*Fn_1A6588)(void* self);

void func_001A6BE0(PairedObject* self, int flag);

struct Node_1A6F28 { void* flags; struct Node_1A6F28* next; s32 pad8; void* data; };

s32 func_001300E8(void* self, int kind);

struct Blob8_1A7050 { u8 b[8]; };

struct Blob8_1A7098 { u8 b[8]; };

typedef void (*Fn_1A7098)(void* self);

void func_001A7480(void* self, int flag);

extern f32 D_0026B850[4];

void func_001B9338(void* self);

void func_00189378(void* sub, int zero, void* out);

void func_001B9D10(void* self, void* out, void* data, f32 scale);

struct Obj_1A7290 { u8 pad[0x98]; f32 a98; };

typedef void (*VFn_1A7798)(void* self);

void* func_0015A838(void* a, int b, int c, void* d);

void func_001A7998(ObjectCreator* self, int flag);

struct Vec_1A7D18 { s32 count; s32 pad; f32 x; };

int func_001A7EE8(void* a);

void func_001A7D98(void* self, int mode);

struct Self_1A5F78 {
    u8 pad0[0x35C];
    u8 a35C[0xC];
    u8 a368[0xC];
    u8 a374[0xC];
    s32 a380;
    u8 a384[0xC];
    u8 a390[0xC];
    s32 a39C;
    u8 a3A0[0xC];
    u8 a3AC[0x14];
    u8 pad1[0x628 - 0x3C0];
    s32 a628;
    u8 pad2[0x638 - 0x62C];
    f32 a638;
    f32 a63C;
    f32 a640;
};

void func_00152600(void* a, void* b);

void func_00152470(void* a, void* b);

void func_001A76A0(void* child, s32 flag);

void func_001A5D50(void* self, void* obj);

s32 func_001A6238(void* self, void* child);

f32 func_001EAAE0(f32 a, f32 b);

void func_001A6BE0(void* self, s32 mode);

s32 func_001A6090(void* self, void* child);

void func_001B7968(void* self);

extern f32 D_0026B7D8[4];

void func_001B9338(C15* self);

void func_001B9D10(C15* self, f32* buf, u8* table, f32 scale);

void func_001A7D18(void* self, void* entry);

struct Entry_26B8B0 { s32 w[65]; };

extern Entry_26B8B0 D_0026B8B0[11];

s32 func_002049E8(void* owner, s32 channel, u8* bytes);

struct Pair_001A7E40 { u8 pad0[4]; void* owner; s32 channel; };

struct Obj_1A45B8 { u8 pad0[0x88]; f32 ratio; u8 pad1[8]; f32 value; };

s32 func_00128230(void* ctx);

extern s32 D_0026C3DC;

extern f32 D_00275C60[];

s32 func_001A4898(void);

void func_001A5760(void* self, f32 t);

void func_001A4EF0(void* self, void* p);

void* func_001E9970(void* zero);

void func_00152600(void* table, void* node);

void func_00152470(void* table, void* node);

void func_001A76A0(void* node, s32 flag);

void func_001B93F8(void* self);

s32 func_001A7698(SoundStateObject* self);

void func_001A76A0(SoundStateObject* node, s32 flag);

void func_001B9AE0(Collider* self, s32 a, s32 b, s32 c, s32 d);

void func_00152600(u8* a, void* b);

void func_00152470(u8* a, void* b);

struct Self_1A5B28 {
    u8 pad0[0x35C];
    u8 a35C[0x368 - 0x35C];
    u8 a368[0x374 - 0x368];
    u8 a374[0x380 - 0x374];
    s32 i380;
    u8 pad1[0x3B8 - 0x384];
    s32 i3B8;
    u8 pad2[0x3C4 - 0x3BC];
    s32 i3C4;
    u8 pad3[0x624 - 0x3C8];
    s32 i624;
    u8 pad4[0x62C - 0x628];
    f32 f62C;
    f32 f630;
    f32 f634;
};

void func_001ED650(void* self, f32 x, f32 y, f32 z);

struct Self_1A63F8 { u8 pad[0x348]; f32 f348; f32 f34C; };

s32 func_001A7420(HitTarget* self);

void func_001A7480(HitTarget* self, int flag);

void func_00155FA0(void* x);

void func_00155F90(void* x);

struct Q_1A7AA0 { u8 pad[0x34]; f32 f34; };

struct P_1A7AA0 { u8 pad0[0x8]; Q_1A7AA0* q; u8 pad1[0x8]; f32 f14; };

void func_00192230(void* self, s32 code, void* rec);

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_00155FA0(void* self);

struct Rec_1A43C8 { u8 pad[8]; s32 kind; };

struct Self_1A5DF8 {
    u8 pad0[0x35C];
    u8 a35C[0x374 - 0x35C];
    u8 a374[0x380 - 0x374];
    s32 i380;
    u8 pad1[0x384 - 0x384];
    u8 a384[0x390 - 0x384];
    u8 a390[0x39C - 0x390];
    s32 i39C;
    u8 a3A0[0x3AC - 0x3A0];
    u8 a3AC[0x3C0 - 0x3AC];
    s32 i3C0;
    u8 pad2[0x624 - 0x3C4];
    s32 i624;
    s32 i628;
    f32 f62C;
    f32 f630;
    f32 f634;
    f32 f638;
    f32 f63C;
    f32 f640;
};

struct __attribute__((aligned(16))) Quad_1A72B0 { s32 a; s32 b; f32 f; s32 d; };

struct Msg_1A72B0 {
    s32 kind;
    u8 pad[0xC];
    Quad_1A72B0 q10;
    Quad_1A72B0 q20;
    u8 pad2[0x20];
};

typedef void (*Fn_1A72B0)(void* self, void* msg);

void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, void* a5);

void func_001B6628(void* a, s32 b);

void func_001B64D8(void* a, s32 b);

struct Quad_1A7998 { s32 a, b, c, d; } __attribute__((aligned(16)));

struct Buf_1A7998 { s32 n; u8 pad[0x1C]; Quad_1A7998 q; u8 tail[0x20]; };

typedef void (*FnP_1A7998)(void* self, void* arg);

typedef void (*FnI_1A7998)(void* self, s32 arg);

void func_0012E760(void* p);

s32 func_0012C7B0(void* a, void* b, s32 c, void* d, f32 x, f32 y);

void func_001B6628(void* p, s32 a);

void func_001B64D8(void* p, s32 a);

void func_001BF788(void* p, s32 flag);

void func_001BFCD8(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001A7D98(void* self, s32 mode);

struct Track_001A7B20 { u8 pad0[4]; s32 value4; s32 value8; s32 state; };

extern void* D_0026B860[10];

void func_001A5B28(void* a, void* b);

void func_001B6628(void* self, void* item);

void func_001B64D8(void* self, void* item);

void func_001BC828(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

struct Frame_1A54F8;

struct Frame_1A54F8 {
    List01* iter;
    void* cursor;
    s32 link;
    Frame_1A54F8* prev;
    Frame_1A54F8(List01* i)
    {
        iter = i;
        cursor = i;
        link = i->offset;
        prev = (Frame_1A54F8*)D_0027B314;
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_1A54F8() { D_0027B314 = (ListFrame*)prev; }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
};

struct Node_1A54F8 {
    void** vtbl;
};

s32 func_001527D8(List01* list);

void func_00152600(void* list, void* item);

s32 func_001EAA70(s32 a, s32 b);

enum Kind_1A5C90 { };

void func_001BFCD8(Kind_1A5C90 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

struct Ctx_1A5D50 { u8 bytes[4]; };

void func_001B9AE0(Collider* self, s32 a, void* b, s32 c, s32 d);

void func_001B9AE0(Collider* self, s32 a, void* b, s32 c, void* d);

// Matched: float stores in retail's order with constants loaded as locals; int stores 0x2D0..0x2DC, 0x64C, 0x650 in that order.
struct __attribute__((aligned(16))) Table_1A4718 {
    AlignedQuad q[12];
};

extern const Table_1A4718 D_0024C9D0;

void func_00123ED0(PairController* self);

void func_00152438(void* self, s32 value);

void func_0018D800(void* dst, void* src, s32 count);

enum Kind_1A4070 { K_1A4070_0 };

void func_001F4408(C15* a, s32 n);

void func_00155F90(void* p);

void func_00155FA0(void* p);

void func_001B6628(void* p, s32 n);

void func_001B64D8(void* p, s32 n);

s32 func_0012C7B0(void* a, C15* self, s32 c, s32* out, f32 fa, f32 fb);

void func_001BF788(s32* p, s32 n);

struct LinkedObject { u8 pad0[0x2D4]; s32 f2D4; };

void func_00124FC0(PairController* self);

s32 func_001A4DC0(PairController* self);

void func_001A4EF0(PairController* self, s32 mode);

void func_001A5120(PairController* self);

void func_001A54F8(PairController* self);

void func_001A7998(ObjectCreator* t, s32 flag);

struct Par_1A4DC0 { u8 pad[0x610]; u32 f610; };

struct __attribute__((aligned(16))) Vec_1A6DE0 { f32 x, y, z, w; };

struct Msg_1A6DE0 {
    s32 kind;
    u8 pad4[0xC];
    Vec_1A6DE0 a;
    Vec_1A6DE0 b;
    Vec_1A6DE0 c;
    Vec_1A6DE0 d;
};

struct Ev_1A6DE0 {
    u8 pad0[0xC];
    u32 flags;
    u8 pad10[0x10];
    Vec_1A6DE0 b;
    Vec_1A6DE0 a;
};

enum Id_1A6DE0 { id_1A6DE0_37 = 0x37 };

extern void func_001A6BE0(PairedObject* o, s32 n);

extern void func_001BFCD8(Id_1A6DE0 id, s32 a1, s32 a2, Vec_1A6DE0* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

struct Src_1A7D98 { u8 pad[4]; u8 b4; u8 b5; };

struct Obj_1A7D98 {
    u8 pad0[4];
    void* owner;
    s32 channel;
    s32 state;
    Src_1A7D98* src;
    u8 pad1[8];
    f32 f1C;
};

void func_001A7E40(Obj_1A7D98* self);

extern f32 D_0026186C;

struct Link_1A4EF0 { u8 pad[0x18]; PairController* f18; };

extern u8 D_00275BC0[];

extern u8 D_00261EF0[];

void func_001E9498(u8* a, u8* b);

void func_001DDC38(void* host, PairController* self);

void func_001A6BE0(PairController* o, s32 n);

void func_001A4070(void* a, s32 n);

void func_00151E20(u8* a, f32 b);

void func_00151FC8(u8* a);

void func_00194D30(u8* a, s32 b, s32 c);

void func_0012E760(PairedObject* o);

void func_001B6438(PairedObject* o);

void func_001A5C38(void* p, PairedObject* o);

void func_001A5DD8(void* p, PairedObject* o);

void func_001A5DF8(void* p, PairedObject* o);

void func_001A5F78(void* p, PairedObject* o);

void func_001A5C90(void* p, PairedObject* o);

void func_0012C288(f32 a, f32 b, void* h, PairedObject* o, s32 n, TargetBinding* buf, s32 e, void** out);

struct Entry_1A7B88 { s32 f0; u8 b[2]; u8 pad[2]; f32 delay; };

struct Table_1A7B88 { s32 count; Entry_1A7B88 entries[1]; };

struct Obj_1A7B88 { u8 pad0[0x4]; void* owner; s32 channel; s32 state; Table_1A7B88* table; s32 index; f32 f18; f32 f1C; };

void func_001A7E40(Obj_1A7B88* self);

struct Poly_1A5760 { f32 a, b, c; };

struct Range_1A5760 { f32 lo, hi; };

struct Curve_1A5760 {
    static f32 Eval(const Poly_1A5760* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
    static void Clamp(f32& c, f32 v, const Range_1A5760* r)
    {
        f32 lo = r->lo;
        f32 hi = r->hi;
        if (v < lo) {
            c = lo;
        } else if (hi < v) {
            c = hi;
        } else {
            c = v;
        }
    }
    static void Get(f32& c, const Poly_1A5760* p, f32 t)
    {
        Clamp(c, Eval(p, t), ((Range_1A5760*)&D_00275C60));
    }
};

// The file's .data (0x26B530 to 0x26C3E0), all initialised, in address order.

f32 D_0026B530[4] = { 1.0f, 1.666667f, -2.666667f, 0.0f };

f32 D_0026B540 = 0.5f;

f32 D_0026B544 = 0.5f;

f32 D_0026B548 = 1.5f;

f32 D_0026B54C = 200.0f;

f32 D_0026B550[4] = { 0.25f, 0.0f, 0.0f, 0.0f };

f32 D_0026B560[4] = { 0.5f, 2.0f, -2.0f, 0.0f };

f32 D_0026B570[4] = { 0.5f, -0.5f, 0.0f, 0.0f };

f32 D_0026B580[4] = { 1.0f, -1.0f, 0.0f, 0.0f };

f32 D_0026B590[4] = { 0.0f, 2.0f, -1.0f, 0.0f };

f32 D_0026B5A0[4] = { 4.0f, -4.0f, 0.0f, 0.0f };

f32 D_0026B5B0[4] = { 0.699999988079071f, 0.0f, -0.699999988079071f, 0.0f };

f32 D_0026B5C0[4] = { 0.0f, 0.0f, 50.0f, 0.0f };

f32 D_0026B5D0[4] = { 0.75f, -0.75f, -0.0f, 0.0f };

f32 D_0026B5E0[4] = { 1.0f, 2.0f, -3.0f, 0.0f };

f32 D_0026B5F0[4] = { 0.5f, 0.0f, 0.0f, 0.0f };

f32 D_0026B600[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

f32 D_0026B610[4] = { 1.0f, -0.7f, 0.0f, 0.0f };

f32 D_0026B620[4] = { 135.0f, 0.0f, -85.0f, 0.0f };

f32 D_0026B630[4] = { 50.0f, 170.0f, -85.0f, 0.0f };

f32 D_0026B640[4] = { 1.0f, 0.0005f, 0.0f, 0.0f };

f32 D_0026B650[4] = { 1.0f, 10.0f, 0.0f, 0.0f };

f32 D_0026B660[4] = { 1.65f, -0.0002f, 0.0f, 0.0f };

f32 D_0026B670[4] = { 0.65f, 1.0f, 0.0f, 0.0f };

f32 D_0026B680[4] = { 0.0f, 6.0f, 0.0f, 0.0f };

f32 D_0026B690[4] = { 5.0f, 16.0f, 0.0f, 0.0f };

f32 D_0026B6A0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

f32 D_0026B6B0[4] = { 1.0f, -1.0f, 0.0f, 0.0f };

s32 D_0026B6C0[4] = { 0x40, 5, 0x42, 0x43 };

f32 D_0026B6D0[4] = { 0.0f, -0.01f, 0.0f, 0.0f };

f32 D_0026B6E0[2] = { -10.0f, 10.0f };

f32 D_0026B6E8 = -1.0f;

f32 D_0026B6EC = 200.0f;

f32 D_0026B6F0[4] = { 0.75f, 1.25f, 0.0f, 0.0f };

f32 D_0026B700[4] = { 0.0f, 0.001f, 0.0f, 0.0f };

f32 D_0026B710[4] = { 0.0f, 4.0f, -4.0f, 0.0f };

f32 D_0026B720[4] = { 0.25f, 3.0f, -3.0f, 0.0f };

f32 D_0026B730[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

f32 D_0026B740[4] = { 0.0f, 0.75f, 0.0f, 0.0f };

f32 D_0026B750[4] = { 1.0f, 5.0f, 0.0f, 0.0f };

f32 D_0026B760[4] = { 0.5f, 0.0f, 0.5f, 0.0f };

f32 D_0026B770[2] = { 0.5f, 1.0f };

ObjectLink D_0026B778[2] = { { 0x2, 0x28E, 0x640 }, { 0x2, 0x292, 0x650 } };

ObjectLink D_0026B790[6] = {
    { 0x4, 0x291, 0x64C },
    { 0x4, 0x299, 0x664 },
    { 0x4, 0x297, 0x65C },
    { 0x4, 0x298, 0x660 },
    { 0x2, 0x29A, 0x680 },
    { 0x2, 0x29B, 0x67C },
};

f32 D_0026B7D8[4] = { 20.0f, 0.0f, 0.30000001192092896f, 0.0f };

ObjectLink D_0026B7E8[6] = {
    { 0x2, 0x29C, 0x58C },
    { 0x2, 0x29D, 0x590 },
    { 0x2, 0x29E, 0x594 },
    { 0x2, 0x29F, 0x598 },
    { 0x2, 0x2A1, 0x5A0 },
    { 0x2, 0x2A2, 0x5A4 }
};

ObjectLink D_0026B830[1] = { { 0x2, 0x2A3, 0x560 } };

ObjectLink D_0026B840[1] = { { 0x6, 0x2AE, 0x578 } };

f32 D_0026B850[4] = { 2.0f, 0.0f, 0.699999988079071f, 0.0f };

void* D_0026B860[10] = { (void*)0x2A4, (void*)0x2A5, (void*)0x2A6, (void*)0x2A7, (void*)0x2A8, (void*)0x2A9, (void*)0x2AA, (void*)0x2AB, (void*)0x2AC, (void*)0x2AD };

ObjectLink D_0026B888[1] = { { 0x2, 0x2AF, 0x55C } };

s32 D_0026B898[2] = { 688, 689 };

ObjectLink D_0026B8A0[1] = { { 0x2, 0x2B3, 0x560 } };

Entry_26B8B0 D_0026B8B0[11] = {
    { { 0x1, 0x1, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0x9600, 0x3D4CCCCD, 0x0, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xD200, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xFF00, 0x3DCCCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x7, 0xD200, 0x3DCCCCCD, 0xBE00, 0x3C23D70A, 0xAA00, 0x3C23D70A, 0x9600, 0x3C23D70A, 0x8200, 0x3C23D70A, 0x6E00, 0x3C23D70A, 0x0, 0x3E800000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xFF01, 0x3DCCCCCD, 0x1, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xAA00, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xAA00, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xAA00, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x3, 0xA000, 0x3E19999A, 0x0, 0x3DCCCCCD, 0x5A00, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x5, 0xFF00, 0x3E4CCCCD, 0x0, 0x3DA3D70A, 0xC800, 0x3E051EB8, 0x0, 0x3D75C28F, 0x9600, 0x3DE147AE, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } }
};

s32 D_0026C3DC = 0;

EffectOwner* func_0019E040(World* self, s32 flag)
{
    if (flag == 0 && self->f1B3C != 0) {
        return self->f1B3C;
    }
    EffectOwner* n = self->f1B38;
    if (n != 0) {
        self->f1B38 = n->saved564;
        n->f550 = flag;
        n->desc->m02(n);
        if (flag == 0) {
            self->f1B3C = n;
        }
    }
    return n;
}

void func_0019E0B8(EffectOwner* self)
{
    InitCollider(self);
    func_00152438(&self->list558, 0x10);
    u64 flags = self->flags;
    flags &= (u64)(s64)(s32)0xCFFFFFFF;
    flags |= 0x20000000ULL;
    u64 wide = self->flags538;
    wide |= (u64)1 << 42;
    flags &= 0xFFFFFCFFFFFFFFFFULL;
    wide |= (u64)1 << 51;
    f32 k = 1e10f;
    flags |= (u64)1 << 40;
    self->flags538 = wide;
    self->f80 = k;
    self->flags = flags;
}

void func_0019E158(EffectOwner* a, Rec50* b)
{
    a->f554 = b->f1E8;
}

void func_0019E168(EffectOwner* self)
{
    Cursor_19E168 cur(&self->list558);
    Effect* node = cur.first();
    while (node != 0) {
        RemoveEffect(node);
        node = cur.next();
    }
    self->saved564 = self->world->f1B38;
    self->world->f1B38 = self;
    if (self == self->world->f1B3C) {
        self->world->f1B3C = 0;
    }
    UnregisterCollider(self);
}

INCLUDE_RODATA(D_0024C930);

INCLUDE_RODATA(D_0024C934);

ASM_FUNC(func_0019E220);

void func_0019E418(void) {}

void func_0019E420(EffectOwner* self, f32 t)
{
    Iter_19E420 it;
    Begin_19E420::Of(&it, &self->list558);
    Effect* node;
    while ((node = Next_19E420::Of(&it)) != 0) {
        if (node->start >= g_gameClock[1]) {
            continue;
        }
        func_0019EC20(node);
        node->vt->m04(node, t);
        ReleaseEffect(node);
    }
    s64 m = 0x8000;
    m <<= 23;
    if ((self->flags & m) != 0 || IsListEmpty(&self->list558) != 0) {
        self->desc->m03(self);
    } else {
        CollideEffects(self);
    }
    func_00129DF8(self);
    g_activeListFrames = (ListFrame*)it.saved;
}

void func_0019E558(EffectOwner* self)
{
    if (self->f550 != 1) return;
    ContactRow03* l;
    for (l = self->contacts->head; l != 0; l = l->next) {
        Iter_19E558 it0;
        Begin_19E558::Of(&it0, &l->other->parts);
        if (l->other->flags538 & ((u64)0x8000 << 27)) {
            End_19E558::Of(&it0);
            continue;
        }
        Collider* s2;
        for (s2 = (Collider*)Next_19E558::Of(&it0); s2 != 0; s2 = (Collider*)Next_19E558::Of(&it0)) {
            Iter_19E558 it1;
            void* buf;
            Hit_19E558 hits[4];
            Begin_19E558::Of(&it1, &self->list558);
            if ((s2->flags538 & ((u64)0x8000 << 28)) && (s2->desc->flags & 0x80) == 0) {
                End_19E558::Of(&it1);
                continue;
            }
            PushBackMemoryMark();
            if (s2->tree.count > 0) {
                buf = AllocateBackMemory(s2->tree.count2 * 12);
                if (func_0013E430((u8*)s2->tree.nodes, (u8*)&self->v140, &buf, self->radius3D0) != 2) goto skip;
                buf = (u8*)buf - 12;
            } else {
                buf = 0;
            }
            {
                Effect* n;
                for (n = (Effect*)Next_19E558::Of(&it1); n != 0; n = (Effect*)Next_19E558::Of(&it1)) {
                    if (n->start >= g_gameClock[1]) continue;
                    s32 cnt = CollectColliderSpansInTree(s2, buf, &n->q90, &n->q80, 4, hits);
                    s32 i;
                    for (i = 0; i < cnt; i++) {
                        Hit_19E558* h = &hits[i];
                        if (h->weight == 0.0f) continue;
                        if (n->vt->m07(n, s2, h, (u8*)h + 0x20) != 0) break;
                    }
                }
            }
        skip:
            PopBackMemoryMark();
            End_19E558::Of(&it1);
        }
        End_19E558::Of(&it0);
    }
    if (IsListEmpty(&self->list558) != 0) {
        self->desc->m03(self);
    }
}

void func_0019E848(EffectOwner* self, void* arg)
{
    Frame_19E848 fr;
    s32 e = (s32)&self->list558;
    fr.cursor = e;
    fr.list = e;
    s32 old = (s32)g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    g_activeListFrames = (ListFrame*)&fr;
    fr.prev = old;
    s32 h = *(s32*)e;
    fr.link = link;
    fr.cursor = h + link;
    s32 n = h;
    while (n != 0) {
        Effect* node = (Effect*)n;
        if (node->start >= g_gameClock[1]) {
        } else {
            node->vt->m05(node, arg);
        }
        s32 nx = *(s32*)fr.cursor;
        s32 lk = fr.link;
        fr.cursor = nx + lk;
        n = nx;
    }
    g_activeListFrames = (ListFrame*)fr.prev;
}

const Vt219C* func_0019E908(u32 n)
{
    switch (n) {
    case 0: return (const Vt219C*)(D_00219C20);
    case 2: return (const Vt219C*)(D_00219C40);
    case 3: return (const Vt219C*)(D_00219C60);
    case 4: return (const Vt219C*)(D_00219C80);
    case 5: return (const Vt219C*)(D_00219CA0);
    case 6: return (const Vt219C*)(D_00219CC0);
    case 7: return (const Vt219C*)(D_00219CE0);
    case 8: return (const Vt219C*)(D_00219D00);
    case 9: return (const Vt219C*)(D_00219D20);
    case 10: return (const Vt219C*)(D_00219D40);
    case 11: return (const Vt219C*)(D_00219D60);
    case 12: return (const Vt219C*)(D_00219D80);
    case 13: return (const Vt219C*)(D_00219DA0);
    case 14: return (const Vt219C*)(D_00219DC0);
    case 15: return (const Vt219C*)D_00219DE0;
    case 16: return (const Vt219C*)(D_00219E00);
    case 17: return (const Vt219C*)(D_00219E20);
    case 18: return (const Vt219C*)(D_00219E40);
    case 19: return (const Vt219C*)(D_00219E60);
    case 20: return (const Vt219C*)(D_00219E80);
    case 21: return (const Vt219C*)(D_00219EA0);
    case 22: return (const Vt219C*)(D_00219EC0);
    case 23: return (const Vt219C*)(D_00219EE0);
    case 24: return (const Vt219C*)(D_00219F00);
    case 25: return (const Vt219C*)(D_00219F20);
    case 26: return (const Vt219C*)(D_00219F40);
    case 27: return (const Vt219C*)(D_00219F60);
    default: return 0;
    }
}

Effect* func_0019EA78(s32 kind, EffectOwner* sys)
{
    if (sys == 0) {
        sys = AcquireEffectOwner(g_currentWorld, 0);
        if (sys == 0) return 0;
    }
    Effect* o = (Effect*)PopFreeSlot(&sys->world->pool1B2C);
    if (o != 0) {
        func_001F5C0C(o, 0, sys->world->pool1B2C.size);
        const Vt219C* r = GetEffectKindTable(kind);
        o->kind = kind;
        o->owner = sys;
        o->vt = r;
        AppendToList(&sys->list558, o);
        func_0019EC20(o);
    }
    return o;
}

ASM_FUNC(func_0019EB28);

void func_0019EBE8(Effect* self)
{
    RemoveFromList(&self->owner->list558, self);
    ReleaseEffect(self);
}

void func_0019EC20(Effect* counter)
{
    counter->uses++;
}

void func_0019EC30(Effect* self)
{
    s32 n = self->uses - 1;
    self->uses = n;
    if (n != 0) {
        return;
    }
    void (*fn)(Effect*) = self->vt->m02;
    if (fn != 0) {
        fn(self);
    }
    T219CHook* head = self->hooks;
    if (head != 0) {
        self->hooks = 0;
        for (T219CHook* it = head; it != 0; it = it->next) {
            it->fn(it->payload, 0x10, self);
        }
        ReleaseCallRecords(g_currentWorld, head);
    }
    PushFreeSlot(&self->owner->world->pool1B2C, self);
}

void func_0019ECE0(Effect* value, s32 enabled)
{
    if (enabled) RemoveEffect(value);
}

void func_0019ED00(Effect* self, f32 x)
{
    f32 span = g_gameClock[1] - self->start;
    f32 t = self->life - span;
    if (x < t) {
        f32 r = t / self->life;
        f32 q = x / r;
        self->life = q;
        self->start = g_gameClock[1] - (1.0f - r) * q;
    }
}

INCLUDE_RODATA(D_0024C9B0);

ASM_FUNC(func_0019ED58);

ASM_FUNC(func_0019F390);

void func_0019F560(Effect* self)
{
    f32 t = g_gameTime - self->start;
    if (self->life < t) {
        RemoveEffect(self);
        return;
    }
    EffectOwner* c = self->owner;
    if (c->f550 == 1) {
        return;
    }
    Collider* h = self->target;
    if (h == 0) {
        return;
    }
    if (h->tree.nodes == 0) {
        return;
    }
    s32 flag = 0;
    if (IsObjectAttached(h) != 0) {
        if (func_0013E658(&self->q80, (s32)self->target->tree.nodes) != 0) {
            flag = 1;
        }
    }
    self->vt->m06(self, flag);
}

ASM_FUNC(func_0019F620);

void func_0019F858(Effect* self, void* a1)
{
    u8 scratch[0x40];
    void* a2;
    void* a3;
    if (self->p114 != 0) {
        func_001F2EF0(50.0f, self->p114, &self->q80, self->rot50,
                      scratch, scratch + 0x10, 0);
        a2 = scratch;
        a3 = scratch + 0x10;
    } else {
        a2 = &self->q80;
        a3 = self->rot50;
    }
    s32 r = func_0019F620(self, a1, a2, a3);
    if (r == 0) {
        RemoveEffect(self);
    }
}

void func_0019F8E8(void* obj, void* arg)
{
    Obj_0019F8E8* value = *(Obj_0019F8E8**)arg;
    AddCallbackNode((void*)g_currentWorld, (u8*)obj + 0x118, (void*)value->value, arg);
}

void func_0019F918(void* obj, void* a1, void* a2)
{
    AddCallbackNode((void*)g_currentWorld, (u8*)obj + 0x118, a1, a2);
}

void func_0019F950(void* obj, void* a1, void* a2)
{
    RemoveCallbackNode((void*)g_currentWorld, (u8*)obj + 0x118, a1, a2);
}

void func_0019F988(Effect* self)
{
    func_0019EB28(self);
    self->life = 5.0f;
    World* g = g_currentWorld;
    self->i20 = (s32)g->slot1CE8[1];
    self->qC0 = *(Quad219C*)&g->gravity;
}

void func_0019F9D0(Effect* self, s32 flag)
{
    if (flag != 0) {
        Scratch_19F9D0 s;
        s.head = self->q80;
        if (self->target->tree.nodes != 0) {
            func_0013DFD8(self->target->tree.nodes, &self->q90, &self->q80, 0, 0x10, &s);
        }
        Effect* p = CreateEffect(4, 0);
        if (p != 0) {
            p->vt->m00(p, &s, 40.0f, 0);
            p->life = 0.75f;
            p->m30[1] = 30.0f;
            if (self->target->f278 != 0) {
                p->p114 = (void*)((s32*)self->target->f278)[3];
            }
        }
        RemoveEffect(self);
    }
}

ASM_FUNC(func_0019FA98);

ASM_FUNC(func_0019FB08);

void func_0019FCE8(Effect* value, u32 enabled)
{
    func_0019F9D0(value, enabled < 1);
}

ASM_FUNC(func_0019FD08);

void func_0019FD70(Effect* self)
{
    func_0019EB28(self);
    self->life = 3.0f;
    World* g = g_currentWorld;
    s32 v = (s32)g->slot1CE8[3];
    self->m30[1] = 0.6f;
    self->i20 = v;
}

void func_0019FDC0(Effect* self)
{
    func_0019EB28(self);
    self->life = 2.0f;
    World* g = g_currentWorld;
    self->qC0 = *(Quad219C*)&g->gravity;
    self->m30[2] = -1.0f;
}

void func_0019FE10(Effect* self)
{
    func_0019EB28(self);
    World* g = g_currentWorld;
    s32 v = (s32)g->slot1CE8[6];
    self->life = 0.5f;
    self->i20 = v;
}

ASM_FUNC(func_0019FE50);

ASM_FUNC(func_0019FF20);

void func_001A0020(Effect* self, void* other)
{
    if (other != 0) {
        RemoveEffect(self);
    }
}

void func_001A0040(Effect* self)
{
    func_0019EB28(self);
    self->life = 0.25f;
    s32 v = (s32)g_currentWorld->slot1CE8[4];
    self->i20 = v;
    self->q40 = D_00275C50;
    self->f120 = 0.05f;
}

ASM_FUNC(func_001A00A0);

void func_001A01B8(Effect* self, f32 f)
{
    func_0019EB28(self, f);
    self->life = 0.5f;
    s32 v = (s32)g_currentWorld->slot1CE8[5];
    u8* p = (u8*)D_0026B560;
    self->i20 = v;
    V128_1A01B8 t;
    func_00118CF0(&t, f);
    Quad219C* sub = &self->q30;
    V128_1A01B8 tv = t;
    V128_1A01B8 u;
    CopyQuadword(&u, p);
    StoreQuadword(sub, func_00118D30(tv, u));
}

void func_001A0258(Effect* self, f32 f)
{
    func_0019EB28(self, f);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B580;
    s32 v = (s32)g_currentWorld->slot1CE8[7];
    self->fB0 = -15.0f;
    self->i20 = v;
    self->q40 = *(Quad219C*)D_0026B570;
    self->life = 0.35f;
    V128_1A0258 t;
    func_00118CF0(&t, f);
    V128_1A0258 tv = t;
    V128_1A0258 u;
    CopyQuadword(&u, p);
    StoreQuadword(sub, func_00118D30(tv, u));
}

void func_001A0318(Effect* self)
{
    func_001A0338(self, 0, 0);
}

ASM_FUNC(func_001A0338);

void func_001A04A0(Effect* self)
{
    Effect* d = CreateEffect(10, 0);
    if (d != 0) {
        d->vt->m00(d, &self->q80, 0.0f, 0);
        d->i20 = self->i20;
        d->fB0 = self->fB0;
        d->q40 = self->q40;
        d->life = self->life;
        Effect* p;
        if (self->i120 == 1) {
            p = self->p124;
            f32* m = p->m30;
            f32 q = (self->start - p->start) / p->life;
            f32 den = p->m30[0] + q * (m[1] + q * m[2]);
            f32 res = self->m30[0] / den;
            q = (g_gameTime - p->start) / p->life;
            res = res * (p->m30[0] + q * (m[1] + q * m[2]));
            d->m30[0] = res;
            d->m30[1] = -res;
        } else {
            d->q30 = self->q30;
            p = self->p128;
        }
        func_001A0338(d, self->i120, p);
        func_001A0338(self, 3, d);
    } else {
        func_001A0338(self, 0, 0);
    }
}

ASM_FUNC(func_001A05D8);

ASM_FUNC(func_001A0758);

void func_001A0950(void* self, s32 kind, s32 extra)
{
    if (kind == 3) {
        goto three;
    }
    if (kind < 4) {
        if (kind == 2) {
            goto zero;
        }
        return;
    }
    if (kind == 10) {
        goto zero;
    }
    if (kind != 16) {
        return;
    }
zero:
    func_001A0338(self, 0, 0);
    return;
three:
    func_001A0338(self, 0, extra + 16);
}

void func_001A09C0(Effect* self, f32 f)
{
    func_0019EB28(self, f);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B590;
    s32 v = (s32)g_currentWorld->slot1CE8[8];
    self->life = 0.25f;
    self->i20 = v;
    V128_1A09C0 t;
    func_00118CF0(&t, f);
    V128_1A09C0 tv = t;
    V128_1A09C0 u;
    CopyQuadword(&u, p);
    (void)StoreQuadword(sub, func_00118D30(tv, u));
    u8* q = (u8*)D_0026B5A0;
    self->q40 = *(Quad219C*)q;
}

void func_001A0A78(Effect* self, f32 arg)
{
    func_0019F560(self);
    f32 d = g_gameTime - self->start;
    d = d - 0.15f;
    if (0.0f <= d && d < arg) {
        arg = -self->m30[2];
        Effect* n = CreateEffect(12, 0);
        if (n != 0) {
            n->vt->m00(n, &self->q80, arg, 0);
        }
    }
}

void func_001A0B20(Effect* self)
{
    func_0019EB28(self);
    World* sys = g_currentWorld;
    self->i20 = (s32)sys->slot1CE8[9];
    self->life = 3.0f;
    self->q40 = *(Quad219C*)D_0026B5B0;
    self->m30[1] = self->m30[0] * 0.25f;
    self->qC0 = *(Quad219C*)D_0026B5C0;
    self->fB0 = -1.0f;
}

void func_001A0BA0(Effect* self, f32 f)
{
    func_001A0258(self, f);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B5E0;
    s32 v = (s32)g_currentWorld->slot1CE8[10];
    self->fB0 = -15.0f;
    self->i20 = v;
    self->q40 = *(Quad219C*)D_0026B5D0;
    V128_1A0258 t;
    func_00118CF0(&t, f);
    V128_1A0258 tv = t;
    V128_1A0258 u;
    CopyQuadword(&u, p);
    StoreQuadword(sub, func_00118D30(tv, u));
}

void func_001A0C50(Effect* self)
{
    func_0019EB28(self);
    World* g = g_currentWorld;
    s32 v = (s32)g->slot1CE8[1];
    self->life = 0.5f;
    self->i20 = v;
    self->qC0 = *(Quad219C*)&g->gravity;
}

ASM_FUNC(func_001A0C98);

ASM_FUNC(func_001A0D60);

ASM_FUNC(func_001A0DF0);

void func_001A0F88(Effect* self)
{
    if (self->life < g_gameTime - self->start) {
        RemoveEffect(self);
        self->params->fn60(self->p134);
    }
}

void func_001A0FE8(Effect* self)
{
    func_0019EB28(self);
    self->q40 = D_00275C50;
    self->life = 2.0f;
}

LINKER_REMNANT(func_001A1028);

ASM_FUNC(func_001A1030);

ASM_FUNC(func_001A11C0);

ASM_FUNC(func_001A1398);

void func_001A1410(Effect* self)
{
    func_001A0040(self);
    World* ctx = g_currentWorld;
    s32 v = ctx->f1D28;
    self->f120 = 0.15f;
    self->i20 = v;
}

void func_001A1458(Effect* self)
{
    func_0019EB28(self);
    s32 v = g_currentWorld->f1D28;
    self->i120 = -1;
    self->i20 = v;
    self->i128 = -1;
}

void func_001A1498(Effect* self)
{
}

void func_001A14A0(Effect* c, f32 dt)
{
    f32 t = (g_gameTime - c->start) / c->life;
    f32 k;
    switch (c->i120) {
    case 0: k = D_0026B600[0] + t * (D_0026B600[1] + t * D_0026B600[2]); break;
    case 1: k = D_0026B610[0]; break;
    case 2: k = D_0026B610[0] + t * (D_0026B610[1] + t * D_0026B610[2]); break;
    }
    f32 p = c->f124 + k * dt;
    c->f124 = p;
    if (1.0f <= p) c->f124 = p - 1.0f;
    if (1.0f < t) {
        switch (c->i120) {
        case 0: SetEffectPhase(c, 1); break;
        case 1: SetEffectPhase(c, 2); break;
        case 2: RemoveEffect(c); break;
        }
    }
}

INCLUDE_RODATA(D_0024C9B4);

ASM_FUNC(func_001A15D8);

void func_001A1DF0(Effect* self, s32 mode)
{
    f32 t;
    f32 x;

    if (mode == self->i120) {
        return;
    }
    f32 one = 1.0f;
    x = (g_gameClock[1] - self->start) / self->life;
    if (x < 0.0f) {
        t = 0.0f;
    } else if (one < x) {
        t = one;
    } else {
        t = x;
    }
    switch (mode) {
    case 0:
        self->q40 = *(Quad219C*)D_0026B6A0;
        self->life = 0.25f;
        break;
    case 1:
        self->q40 = *(Quad219C*)((u8*)&D_00275C50);
        self->life = 3.4028235e+38f;
        break;
    case 2:
        self->q40 = *(Quad219C*)D_0026B6B0;
        self->life = 0.5f;
        break;
    }
    if ((mode == 0 || mode == 2) && (self->i120 == 0 || self->i120 == 2)) {
        t = 1.0f - t;
    } else {
        t = 0.0f;
    }
    self->start = g_gameClock[1] - t * self->life;
    self->i120 = mode;
}

s32 func_001A1F18(Item_1A1F18* a, Item_1A1F18* b)
{
    if (a->key20 < b->key20) return -1;
    return 1;
}

ASM_FUNC(func_001A1F40);

INCLUDE_RODATA(D_0024C9BC);

ASM_FUNC(func_001A2070);

void func_001A22C8(Effect* self, Src_1A22C8* src)
{
    self->i120 = src->f1DC;
    self->i124 = src->f1F0;
}

ASM_FUNC(func_001A22E0);

ASM_FUNC(func_001A2380);

s32 func_001A25F0(Effect* self, Obj_1A25F0* other, void* a2, void* a3)
{
    u32 i;
    for (i = 0; i < 4; i++) {
        if (IsObjectOfKind(other->f50, D_0026B6C0[i]) != 0) {
            return 0;
        }
    }
    if (IsObjectOfKind(other, 0x1F) == 0) {
        func_001A2380(self, self->i120, other, a2, a3, 0);
    }
    RemoveEffect(self);
    return 1;
}

void func_001A26B0(Effect* self)
{
    func_0019F560(self);
    s32 h = self->i120;
    if (h != 0) {
        if (IsObjectAttached(h) == 0) {
            RemoveEffect(self);
        }
    }
}

void func_001A26F8(Effect* self, void* a1)
{
    u8 scratch[0x40];

    func_00128018(self->p120, 0, &self->q80, scratch);
    func_00128150(self->p120, 0, self->rot50, scratch + 0x10);
    func_0019F620(self, a1, scratch, scratch + 0x10);
}

ASM_FUNC(func_001A2770);

ASM_FUNC(func_001A2830);

s32 func_001A2A68(Effect* self, void* a1, void* a2, void* a3)
{
    Other_1A2A68* other = (Other_1A2A68*)a1;
    u8 out[0x10];
    void* p;

    if (IsObjectOfKind(other->f50, 0x40) != 0) {
        return 0;
    }
    if (IsObjectOfKind(other->f50, 6) != 0) {
        return 0;
    }
    func_001A2380(self, self->i20, other, a2, a3, out);
    p = *(void**)out;
    if (p != 0) {
        func_00128150(0, other, (u8*)p + 0x50, (u8*)p + 0x50);
    }
    RemoveEffect(self);
    return 1;
}

s32 func_001A2B18(Self_1A2B18* self, Other_1A2B18* other)
{
    u64 flag = 0x8000;

    flag <<= 28;
    if ((other->f538 & flag) != 0) {
        return 0;
    }
    return other != self->f7C;
}

ASM_FUNC(func_001A2B48);

void func_001A2D30(Effect* dst, void* a1)
{
    Src_1A2D30* src = (Src_1A2D30*)a1;
    func_00128018(src->link, 0, (u8*)src + 0x20, &dst->q80);
    dst->iB0 = 0;
    dst->i110 = 0;
    dst->i120 = src->f1F4;
    dst->i124 = src->f1F0;
}

ASM_FUNC(func_001A2D88);

ASM_FUNC(func_001A2E68);

ASM_FUNC(func_001A3008);

s32 func_001A3128(Effect* a0, Obj_1A3128* a1, void* a2, void* a3)
{
    if (IsObjectOfKind(a1->p50, 6) != 0) {
        return 0;
    }
    return func_0019ED58(a0, a1, a2, a3);
}

ASM_FUNC(func_001A31A0);

void func_001A31F0(Effect* self)
{
    func_0019EB28(self);
    f32 half = 0.5f;
    u8* sys = (u8*)g_currentWorld;
    self->life = half;
    self->i20 = *(s32*)(sys + 0x1D30);
    self->q40 = *(Quad219C*)D_0026B710;
    self->q30 = *(Quad219C*)D_0026B720;
}

ASM_FUNC(func_001A3250);

void func_001A3598(Effect* self, f32 x)
{
    func_0019EB28(self, x);
    self->q40 = *(Quad219C*)&D_00275C50;
    self->m30[0] = x;
    self->m30[1] = 1.0f - x;
    *(s32*)&self->m30[2] = 0;
}

ASM_FUNC(func_001A35F0);

ASM_FUNC(func_001A3730);

void func_001A38F0(Effect* self)
{
    if (self->start <= g_gameClock[1]) {
        if (self->i134 != 0) {
            func_001A35F0(self);
        }
    }
    f32 span = g_gameClock[1] - self->start;
    if (self->life < span) {
        Obj_1A38F0* o = (Obj_1A38F0*)self->p20;
        o->vtbl[6](o);
        RemoveEffect(self);
    }
}

void func_001A3990(Effect* self)
{
    if (g_gameTime < self->start) {
        return;
    }
    func_0019F858(self);
}

void func_001A39C8(Effect* self, void* otherv)
{
    Other_1A39C8* other = (Other_1A39C8*)otherv;
    self->i120 = FindFirstObjectById(g_currentWorld, 0x104, other->i1F0, other->p7C);
    self->f124 = other->f1F4;
}

void func_001A3A18(Effect* self, f32 scale)
{
    func_0019F560(self, scale);
    if (self->p120 == 0) return;
    f32 t = scale * self->f124;
    f32 v = self->f128 + t;
    self->f128 = v;
    if (!(1.0f <= v)) return;
    f32 nv;
    do {
        Buf_1A3A18 buf;
        buf.n = 4;
        buf.q = *(Quad_1A3A18*)&self->q80;
        void* obj = self->p120;
        Fn_1A3A18* vt = *(Fn_1A3A18**)obj;
        vt[31](obj, &buf);
        nv = self->f128 - 1.0f;
        self->f128 = nv;
    } while (1.0f <= nv);
}

ASM_FUNC(func_001A3AC8);

void func_001A3AE0(C15* self)
{
    C15* o = self;
    InitSwitchedCollider(self);
    o->f610 = -1;
    o->f628 = 2000.0f;
    o->f614 = -1;
}

void func_001A3B20(C15* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 2, (void*)D_0026B778);
}

void func_001A3B58(C15* self)
{
    StartPlacedObject(self);
    if (self->f678 != 0) {
        ResolveObjectLinks(self, 6, (void*)D_0026B790);
        SetColliderAnchors(self, 0, 0, 3, 0);
        if (self->f640 != 0) {
            self->f644 = CreateStateWalker(self->f640, self, -1, 0);
        }
        if (self->f650 != 0) {
            self->f654 = CreateStateWalker(self->f650, self, -1, 1);
        }
        self->f668 = GatherObjectsById(g_currentWorld, 1, 0x50, self->f664, 3, self->f66C);
        func_001A4070(self, 2);
        func_001A42C8(self, 0);
    } else {
        ((VFn_1A3B58*)self->desc)[7](self);
    }
}

extern const f32 D_0024C9C0[4] = { 30.0f, 0.0f, 0.2f, 0.0f };

void func_001A3C40(C15* self, Src_1A3C40* src)
{
    Frame_1A3C40 f;
    if (self->f688 != 0) {
        StopAnimationPlayer(((Ptr_1A3C40*)self->f684));
        self->f684 = 0;
        self->f688 = 0;
    }
    func_001A3F40(self, src);
    ComputePolarOffset((Out_1A3C40*)((u8*)self + 0x630), self->f618, self->f61C * self->f628, 0.0f);
    f.tri = *(Tri_1A3C40*)D_0024C9C0;
    f32 r = func_00205778(((Inner_1A3C40*)self->f64C)->f114, ((Inner_1A3C40*)self->f64C)->f110);
    r = ApproachAngleWithRamp((u8*)&f.tri, 0, r, self->f620, g_frameDt);
    func_001892A0(f.buf, r, 0.0f);
    func_00128150(0, self, f.buf, f.buf);
    ((Inner_1A3C40*)self->f64C)->vtbl[34](((Inner_1A3C40*)self->f64C), f.buf);
}

ASM_FUNC(func_001A3D40);

void func_001A3F40(C15* out, Src_1A3F40* src)
{
    if (0.3f < src->f48) {
        func_00144FF8(g_camera, src, 0, &out->f618);
    }
    out->f61C = src->f48;
    if (0.8f < src->f7C) {
        func_00144FF8(g_camera, src, 1, &out->f620);
    }
    out->f624 = src->f7C;
}

s32 func_001A3FE0(C15* self)
{
    s32 r = self->f610;
    switch (r) {
    case 0:
        if (0.0f < self->f61C) {
            r = 1;
        }
        break;
    case 1:
        if (self->f61C == 0.0f) {
            r = 0;
        }
        break;
    case 2:
        if (self->f684 == 0) {
            r = 1;
        }
        break;
    }
    return r;
}

void func_001A4070(C15* self, s32 n)
{
    s32 old = self->f610;
    if (old == n) return;
    void* h = 0;
    self->f610 = n;
    s32 snd = -1;
    s32 flag = 0;
    s32 kind = 0x14D;
    switch (n) {
    case 0:
        snd = 0x28F;
        flag = 1;
        kind = -1;
        break;
    case 1:
        snd = 0x290;
        break;
    case 2:
        snd = 0x290;
        h = self->f680;
        break;
    case 3:
        snd = 0x290;
        h = self->f67C;
        func_001F4408(0, 1);
        break;
    }
    for (s32 i = 0; i < self->f668; i++) {
        if (flag) SetEffectSpawnerActiveForever(((void**)self->f66C)[i]);
        else func_00155FA0(((void**)self->f66C)[i]);
    }
    if (self->f644) {
        if (old == -1) TeleportStateWalker(self->f644, snd);
        else SetStateWalkerTarget(self->f644, snd);
    }
    if (h) {
        CreateAnimationPlayerWithoutPresetTargets(h, self, 1, (s32*)&self->f684, 0.0f, 1.0f);
    }
    if (self->f648) {
        if (kind == *self->f648) return;
        StopSoundRecord(self->f648, 0);
        self->f648 = 0;
    }
    if (kind != -1) {
        StartSoundEffect((s32)(Kind_1A4070)kind, (void*)&self->f648, (void*)self, 0, 10000.0f, 6000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    }
}

s32 func_001A4258(C15* self)
{
    s32 r = self->f614;
    switch (r) {
    case 0:
        if (0.8f <= self->f624) {
            r = 1;
        }
        break;
    case 1:
        if (self->f624 < 0.8f) {
            r = 0;
        }
        break;
    }
    return r;
}

void func_001A42C8(C15* self, s32 state)
{
    s32 old = self->f614;
    if (old == state) {
        return;
    }
    self->f614 = state;
    s32 a2;
    s32 s1;
    switch (state) {
    case 0:
        a2 = 0x293;
        s1 = -1;
        break;
    case 1:
        a2 = 0x294;
        s1 = 0x150;
        break;
    }
    if (self->f654 != 0) {
        if (old == -1) {
            TeleportStateWalker(self->f654, a2);
        } else {
            SetStateWalkerTarget(self->f654, a2);
        }
    }
    s32 cur = -1;
    if (self->f658 != 0) {
        cur = *(s32*)self->f658;
        if (s1 == cur) {
            return;
        }
        StopSoundRecord(self->f658, 0);
        self->f658 = 0;
        cur = -1;
    }
    if (s1 == cur) {
        return;
    }
    f32 zero = 0.0f;
    StartSoundEffect(s1, &self->f658, self, 0, 10000.0f, 6000.0f, 1.0f, zero, zero, 0, 0);
}

void func_001A43C8(C15* self, s32 code, Rec_1A43C8* rec)
{
    HandleSwitchedColliderNotification(self, code, rec);
    if (code == 5) {
        goto code5;
    }
    if (code != 0x13) {
        return;
    }
    if (rec->kind == 0x295) {
        goto kind295;
    }
    if (rec->kind == 0x296) {
        goto kind296;
    }
    return;
kind295:
    StartSoundEffect(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    func_00155FA0(self->f65C);
    return;
kind296:
    StartSoundEffect(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    func_00155FA0(self->f660);
    return;
code5:
    if (rec == self->f684) {
        self->f688 = 1;
    }
}

void func_001A44E8(C15* self)
{
    f32 buf[12];
    StepCollider(self);
    func_001892A0(buf, self->f618, 0.0f);
    func_001B9D10(self, buf, D_0026B7D8, g_frameDt);
}

ASM_FUNC(func_001A4538);

void func_001A45B8(C15* ctx, Obj_1A45B8* obj)
{
    if (func_00128230(ctx) != 0) {
        return;
    }
    if (0.7f < obj->ratio) {
        obj->value = 20.0f;
    }
}

void func_001A4610(C15* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    Vec02 s0;
    Vec02 s1;
    s32 n = *(s32*)(a2 + ((1 - a3) << 6));
    s0 = self->v440;
    s1 = self->q450;
    if (n != 0) {
        if (IsObjectOfKind((void*)n, 0x43) || IsObjectOfKind((void*)n, 0x42)) {
            self->mode450 = 1;
            self->v440 = g_unitZVector;
        }
    }
    func_001BC828(self, a1, a2, a3, a4, a5);
    self->v440 = s0;
    self->q450 = s1;
}

s32 func_001A4710(void)
{
    return 0;
}

extern const Table_1A4718 D_0024C9D0 = { {
    { 2.0f, 5.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 8.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 1.0f, 2.5f, 0.10000000149011612f, 0.30000001192092896f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 1.5f, 3.0f, 0.15000000596046448f, 0.4000000059604645f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 400.0f, 1500.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 3.0f, 6.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f }
} };

void func_001A4718(PairController* self)
{
    Table_1A4718 tmp;

    InitPlacedObject(self);
    func_00152438(self->list35C, 0x5A0);
    func_00152438(self->list368, 0x5A0);
    func_00152438(self->list374, 0x5A0);
    func_00152438(self->list384, 0x5B0);
    func_00152438(self->list390, 0x5B0);
    func_00152438(self->list3A0, 0x568);
    func_00152438(self->list3AC, 0x568);
    self->id2D0 = -1;
    self->id2D4 = -1;
    self->id2D8 = -1;
    self->id2DC = -1;
    self->id64C = -1;
    self->state = -1;
    self->limit3B8 = 0x28;
    tmp = g_pairControllerPoseTable;
    CopyMemory(self->poseA, &tmp, 0xC0);
    CopyMemory(self->poseB, &tmp, 0xC0);
    self->q3D0 = *(AlignedQuad*)&D_00275C50;
    f32 k2300 = 2300.0f;
    f32 k1500 = 1500.0f;
    f32 k146 = 1.46f;
    f32 k3000 = 3000.0f;
    self->tune350 = k3000;
    self->tune348 = k2300;
    self->tune344 = k1500;
    self->tune34C = k146;
    self->mode340 = 0;
}

void func_001A4858(PairController* obj, s32 value)
{
    obj->id2D0 = value;
}

void func_001A4860(PairController* obj, s32 value)
{
    obj->id2D4 = value;
}

void func_001A4868(u8* self, s32 value)
{
    *(s32*)(self + 0x2D8) = value;
}

void func_001A4870(PairController* obj, s32 value)
{
    obj->id2DC = value;
}

void func_001A4878(PairController* list, s32 value)
{
    s32 n = list->idCount;
    list->ids[n] = value;
    list->idCount = n + 1;
}

s32 func_001A4898(void)
{
    s32 flags = g_currentEntry->flags;
    if ((flags & 4) == 0) {
        s32 bit = flags & 2;
        return bit != 0;
    }
    return 2;
}

ASM_FUNC(func_001A48C0);

void func_001A4B30(PairController* self)
{
    StartPlacedObject(self);
    if (self->id64C != func_001A4898()) {
        self->desc->m03(self);
    } else {
        BlendMotion* k = &self->kin;
        f32 dt = g_currentEntry->dt;
        f32 v = k->pos + dt * (k->vel + dt * k->acc);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        f32 t;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = hi;
        } else {
            t = v;
        }
        f32 u = 1.0f - t;
        f32* pa = self->poseA;
        f32* pb = self->poseB;
        f32* po = self->poseOut;
        for (u32 i = 0; i < 48; i++) {
            *po++ = u * *pa++ + t * *pb++;
        }
        UpdatePairControllerTuning(self, 0.0f);
        SetPairControllerState(self, 0);
    }
}

void func_001A4C48(PairController* self)
{
    ObjectCreator* t;
    s32 st;
    UpdatePlacedObject(self);
    while ((st = ChoosePairControllerState(self)) != self->state) {
        SetPairControllerState(self, st);
    }
    switch (st) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 6:
        break;
    case 2:
        if (self->count3BC < self->limit3B8) {
            if (self->f634 < g_gameClock[1]) {
                func_001A5120(self);
            }
        }
        if (self->f640 < g_gameClock[1]) {
            StartPairedObjects(self);
        }
        break;
    case 5: {
        t = self->target;
        if (t) {
            if (t->state == 0) {
                LinkedObject* s = self->link;
                if (s == 0 || s->f2D4 != 3) {
                    SetObjectCreatorState(t, 1);
                }
            }
        }
        break;
    }
    }
}

void func_001A4D60(PairController* self)
{
    void* p = 0;
    if (self->state == 2) {
        p = AreMenusAndFadeClear(p);
    }
    if (p != 0) {
        D_0026D0C8.vt->m14(&D_0026D0C8);
    } else {
        D_0026D0C8.vt->m15(&D_0026D0C8);
    }
}

s32 func_001A4DC0(PairController* self)
{
    u32 s = self->state;
    switch (s) {
    case 0:
        { u32 one = 1;
        if (((Par_1A4DC0*)self->f354)->f610 <= one) s = one; }
        break;
    case 1:
        if (!self->link || self->link->f2D4 != 3) s = 2;
        break;
    case 2:
        if (self->f3C0) { s = 3; break; }
        if (self->f3C4 == self->limit3B8) s = 5;
        break;
    case 3:
        if (self->link->f2D4 != 3) s = 4;
        break;
    case 5:
        if (self->target) {
            if (self->target->state == 3 && self->target->stateTime + 3.0f < g_gameClock[1]) s = 6;
        } else if (self->f654 + 5.0f < g_gameClock[1]) {
            if (!self->link || self->link->f2D4 != 3) s = 6;
        }
        break;
    case 4:
    case 6:
        break;
    }
    return s;
}

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))
#define O(o, off) (*(PairController**)((u8*)(o) + (off)))
void func_001A4EF0(PairController* self, s32 state)
{
    PairController* o;
    s32 v;
    ListFrame frame;
    if (W(self, 0x650) == state) return;
    W(self, 0x650) = state;
    F(self, 0x654) = g_gameClock[1];
    W(self, 0x658) = 0;
    switch (state) {
    case 0:
        break;
    case 1: {
        if (W(self, 0x64C) < 3) {
            if (W(self, 0x64C) >= 0) {
                if (g_currentEntry->f14) {
                    W(self, 0x658) = 0;
                } else {
                    W(self, 0x658) = FindFirstObjectById(self->world, 0x105, 0x33B, 0);
                }
            }
        }
        s32 w = W(self, 0x658);
        if (w) {
            T217D_440* box = &g_typedTextCaptionBox;
            ((U32P*)&box->child)->v = w;
            PushStackElement(g_elementStack, (u8*)box);
        }
        break;
    }
    case 2: {
        D_0026D0C8.target = &self->f3C4;
        D_0026D0C8.limit = &self->limit3B8;
        func_001DDC38(self->world, self);
        break;
    }
    case 5:
        v = FindFirstObjectById(self->world, 0x105, 0x33D, 0);
        W(self, 0x658) = v;
        if (v) {
            g_typedTextCaptionBox.child = (void*)v;
            PushStackElement(g_elementStack, (u8*)&g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) SetPairedState(o, 8);
        func_00151FC8(D_00261EF0);
        break;
    case 3:
        v = FindFirstObjectById(self->world, 0x105, 0x33E, 0);
        W(self, 0x658) = v;
        if (v) {
            g_typedTextCaptionBox.child = (void*)v;
            PushStackElement(g_elementStack, (u8*)&g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) {
            Link_1A4EF0* l = (Link_1A4EF0*)P(o, 0x55C);
            if (l == 0 || l->f18 != o) SetPairedState(o, 7);
        }
        func_00151E20(D_00261EF0, 1.0f);
        break;
    case 4:
        SetPauseMenuLayerPage((u8*)&g_pauseMenuElement, 0, 0x1A);
        break;
    case 6:
        func_001A4070(P(self, 0x354), 3);
        D_0026EC70.vt->m15(&D_0026EC70);
        break;
    }
}
#undef F
#undef W
#undef P
#undef O

INCLUDE_RODATA(D_0024CAEC);

ASM_FUNC(func_001A5120);

void func_001A54F8(PairController* self)
{
    if (*(s32*)(self->list390 + 0xC) >= self->f628) {
        self->f640 = 3.4028234663852886e+38f;
    } else {
        Node_1A54F8* owner = *(Node_1A54F8**)(self->list390);
        s32 count = CountListItems((List01*)self->list3A0);
        if (count != 0) {
            Frame_1A54F8 w((List01*)self->list3A0);
            u8* node;
            s32 r = RandomIntInRange(0, count - 1);
            s32 j = r;
            j--;
            if (r >= 0) {
                do {
                    node = (u8*)w.Next();
                } while (j-- >= 0);
            }
            RemoveFromList(self->list3A0, node);
            AppendToList(self->list3AC, node);
            RemoveFromList(self->list390, owner);
            AppendToList(self->list384, owner);
            *(void**)((u8*)owner + 0x560) = node;
            (*(s32*)(self->list390 + 0xC))++;
            ((void (*)(void*))owner->vtbl[0x18 / 4])(owner);
            ((void (*)(void*, void*))owner->vtbl[0x84 / 4])(owner, node + 0x140);
            ((void (*)(void*, void*))owner->vtbl[0x88 / 4])(owner, node + 0x110);
            SetPairedState(owner, 1);
            SetSoundStateObjectState(*(void**)((u8*)owner + 0x560), 1);
            *(f32*)((u8*)owner + 0x564) = self->f644;
            *(f32*)((u8*)owner + 0x568) = self->f648;
            f32* fp = &self->f638;
            self->f640 = g_gameClock[1] + RandomFloatInRange(self->f638, fp[1]);
            StartSoundEffect(-1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            StartSoundEffect(0x14E, 0, (s32)node, 0, 12000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
}

#define F(o) (*(f32*)((u8*)self + (o)))
#define I(o) (*(s32*)((u8*)self + (o)))
#define P(o) ((const Poly_1A5760*)((u8*)self + (o)))
void func_001A5760(PairController* self, f32 dt)
{
    f32 t0;
    Curve_1A5760::Get(t0, P(0x5B0), dt);
    F(0x62C) = (1.0f - t0) * F(0x5A0) + t0 * F(0x5A8);
    F(0x630) = (1.0f - t0) * F(0x5A4) + t0 * F(0x5AC);

    f32 t1;
    Curve_1A5760::Get(t1, P(0x5D0), dt);
    F(0x638) = (1.0f - t1) * F(0x5C0) + t1 * F(0x5C8);
    F(0x63C) = (1.0f - t1) * F(0x5C4) + t1 * F(0x5CC);

    f32 t2;
    Curve_1A5760::Get(t2, P(0x5F0), dt);
    F(0x644) = (1.0f - t2) * F(0x5E0) + t2 * F(0x5E4);

    f32 t3;
    Curve_1A5760::Get(t3, P(0x610), dt);
    F(0x648) = (1.0f - t3) * F(0x600) + t3 * F(0x604);

    f32 t4;
    Curve_1A5760::Get(t4, P(0x570), dt);
    s32 n = (s32)((1.0f - t4) * F(0x560) + t4 * F(0x564));
    if (I(0x624) < n && I(0x380) == I(0x624)) {
        F(0x634) = g_gameClock[1] + RandomFloatInRange(F(0x62C), F(0x630));
    }
    I(0x624) = n;

    f32 t5;
    Curve_1A5760::Get(t5, P(0x590), dt);
    n = (s32)((1.0f - t5) * F(0x580) + t5 * F(0x584));
    if (I(0x628) < n && I(0x39C) == I(0x628)) {
        F(0x640) = g_gameClock[1] + RandomFloatInRange(F(0x638), F(0x63C));
    }
    I(0x628) = n;
}
#undef F
#undef I
#undef P

void func_001A5B28(Self_1A5B28* self, HitTarget* obj)
{
    s32 n = self->i3C4 + 1;
    f32 x = (f32)self->i3B8;
    self->i3C4 = n;
    UpdatePairControllerTuning(self, (f32)n / x);
    if (obj->partner != 0) {
        RemoveFromList(self->a35C, obj);
    } else {
        RemoveFromList(self->a368, obj);
    }
    AppendToList(self->a374, obj);
    if (obj->partner != 0) {
        if (func_001A6090(self, obj->partner) != 0) {
            SetPairedState(obj->partner, 3);
        } else {
            ((HitTarget*)obj->partner)->partner = 0;
            SetPairedState(obj->partner, 2);
        }
    }
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->i380 == self->i624) {
        f32 t = RandomFloatInRange(self->f62C, self->f630);
        self->f634 = g_gameClock[1] + t;
    }
    self->i380 = self->i380 - 1;
}

void func_001A5C38(u8* self, PairedObject* obj)
{
    RemoveFromList(self + 0x3AC, obj->attachment);
    AppendToList(self + 0x3A0, obj->attachment);
    SetSoundStateObjectState(obj->attachment, 0);
    obj->attachment = 0;
}

void func_001A5C90(void* a0, void* a1)
{
    PairedObject* s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc->m15((Collider*)s->partner, (BaseObject*)a1);
    s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc02()->m20((Collider*)s->partner, (Vec02*)&D_00248D30);
    s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc02()->m21((Collider*)s->partner, (Vec02*)&D_00248D30);
    SetColliderAnchors((Collider*)((PairedObject*)a1)->partner, 3, 0, 3, 0);
    StartSoundEffect((Kind_1A5C90)0x151, (void*)0, 0, (void*)0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

void func_001A5D50(Ctx_1A5D50* unused, PairedObject* h)
{
    Collider* o = (Collider*)h->partner;

    (void)unused;
    o->desc->m15(o, 0);
    o->desc02()->m20(o, (Vec02*)&D_00248D30);
    o->desc02()->m21(o, (Vec02*)&D_00248D30);
    SetColliderAnchors(o, 2, (void*)&g_unitZVector, 3, 0);
}

void func_001A5DD8(void* unused, PairedObject* obj)
{
    SetSoundStateObjectState(obj->attachment, 1);
}

void func_001A5DF8(Self_1A5DF8* self, PairedObject* obj)
{
    self->i3C0 = self->i3C0 + 1;
    RemoveFromList(self->a35C, obj->partner);
    AppendToList(self->a374, obj->partner);
    RemoveFromList(self->a384, obj);
    AppendToList(self->a390, obj);
    RemoveFromList(self->a3AC, obj->attachment);
    AppendToList(self->a3A0, obj->attachment);
    {
        PairedObject* p = (PairedObject*)obj->partner;
        p->desc->m15(p, 0);
    }
    {
        PairedObject* q = (PairedObject*)obj->partner;
        q->desc->m03(q);
    }
    obj->desc->m03(obj);
    SetSoundStateObjectState(obj->attachment, 0);
    obj->attachment = 0;
    ((PairedObject*)obj->partner)->partner = 0;
    obj->partner = 0;
    if (self->i380 == self->i624) {
        f32 t = RandomFloatInRange(self->f62C, self->f630);
        self->f634 = g_gameClock[1] + t;
    }
    self->i380 = self->i380 - 1;
    if (self->i39C == self->i628) {
        f32 t2 = RandomFloatInRange(self->f638, self->f63C);
        self->f640 = g_gameClock[1] + t2;
    }
    self->i39C = self->i39C - 1;
    StartSoundEffect(0x51, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

void func_001A5F78(Self_1A5F78* self, PairedObject* obj)
{
    RemoveFromList(self->a384, obj);
    AppendToList(self->a390, obj);
    if (obj->attachment != 0) {
        RemoveFromList(self->a3AC, obj->attachment);
        AppendToList(self->a3A0, obj->attachment);
        SetSoundStateObjectState(obj->attachment, 0);
    }
    PairedObject* child = (PairedObject*)obj->partner;
    if (child != 0) {
        if (child->parent == obj) {
            func_001A5D50(self, obj);
        }
        RemoveFromList(self->a35C, child);
        AppendToList(self->a368, child);
        if (func_001A6238(self, child) == 0) {
            child->partner = 0;
        }
    }
    obj->attachment = 0;
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->a39C == self->a628) {
        f32 r = RandomFloatInRange(self->a638, self->a63C);
        self->a640 = g_gameClock[1] + r;
    }
    self->a39C = self->a39C - 1;
}

INCLUDE_RODATA(D_0024CAF4);

ASM_FUNC(func_001A6090);

void func_001A6168(u8* self, PairedObject* obj, PairedObject* node)
{
    PairedObject* cur = (PairedObject*)obj->partner;
    if (cur != 0 && cur == node) {
        return;
    }
    PairedObject* s2 = (PairedObject*)node->partner;
    obj->partner = node;
    node->partner = obj;
    if (s2 == 0) {
        RemoveFromList(self + 0x368, node);
        AppendToList(self + 0x35C, node);
    }
    if (cur != 0) {
        RemoveFromList(self + 0x35C, cur);
        AppendToList(self + 0x368, cur);
        cur->partner = 0;
        func_001A6238(self, cur);
    }
    if (s2 != 0) {
        s2->partner = 0;
        SetPairedState(s2, 2);
        if (func_001A6090(self, s2) != 0) {
            SetPairedState(s2, 3);
        }
    }
}

INCLUDE_RODATA(D_0024CAF8);

ASM_FUNC(func_001A6238);

INCLUDE_RODATA(D_0024CAFC);

ASM_FUNC(func_001A6328);

void func_001A63F8(Self_1A63F8* self, PairedObject* b)
{
    f32 r0 = RandomFloatInRange(0.0f, 6.2831855f);
    f32 r1 = RandomFloatInRange(0.0f, self->f348);
    ComputePolarOffset((u8*)b + 0x570, r0, r1, 0.0f);
    b->f574 = b->f574 * self->f34C;
}

void* func_001A6480(void* self)
{
    PairController* obj = (PairController*)self;
    return (u8*)self + (obj->poseIndex * 0xC0 + 0x3E0);
}

void func_001A6498(PairedObject* self)
{
    InitCollider(self);
    self->state = -1;
    self->f584 = 1.0f;
    self->f588 = 2.5f;
    SetColliderAnchors(self, 1, (void*)&g_unitZVector, 2, (void*)&g_unitZVector);
}

void func_001A64F8(PairedObject* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 6, g_pairedObjectLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

void func_001A6540(PairedObject* self)
{
    Blob8_1A6540 tmp = *(Blob8_1A6540*)&self->blob5B0;
    CopyCollider(self);
    *(Blob8_1A6540*)&self->blob5B0 = tmp;
}

void func_001A6588(PairedObject* self)
{
    StartPlacedObject(self);
    SetPairedState(self, 0);
    Fn_1A6588* vt = *(Fn_1A6588**)self;
    vt[7](self);
}

INCLUDE_RODATA(jtbl_0024CB00);

ASM_FUNC(func_001A65C8);

ASM_FUNC(func_001A6788);

INCLUDE_RODATA(jtbl_0024CB30);

ASM_FUNC(func_001A69F8);

void func_001A6BE0(PairedObject* self, s32 mode)
{
    TargetBinding buf[2];
    TargetBinding* w;
    void* h;
    void* s3;

    if (self->state == mode) return;
    if (self->activeHandle) {
        StopAnimationPlayer((PairedObject*)self->activeHandle);
        self->activeHandle = 0;
    }
    if (self->soundHandle) {
        DestroyStateWalker((PairedObject*)self->soundHandle);
        self->soundHandle = 0;
    }
    switch (self->state) {
    case 1:
        ReleasePairedAttachment(self->controller, self);
        break;
    case 5:
        if (mode == 6) ActivatePairedAttachment(self->controller, self);
        break;
    case 6:
        if (mode == 0) FinishPairedObjectTransition(self->controller, self);
        break;
    case 9:
        RemovePairedObject(self->controller, self);
        break;
    default:
        break;
    }
    self->state = mode;
    h = 0;
    s3 = 0;
    self->stateTime = g_gameClock[1];
    w = buf;
    switch (mode) {
    case 0: case 10:
        break;
    case 1: case 2: case 3:
        h = self->f58C;
        break;
    case 4:
        func_001A5C90(self->controller, self);
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->f594;
        break;
    case 5: case 6:
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->f590;
        break;
    case 7:
        s3 = self->f5A0;
        break;
    case 8:
        s3 = self->f5A4;
        break;
    case 9:
        h = self->f598;
        break;
    }
    if (h) CreateAnimationPlayer(0.0f, 1.0f, h, self, w - buf, buf, 1, &self->activeHandle);
    if (s3) self->soundHandle = CreateStateWalker(s3, self, -1, 1);
}

s32 func_001A6DE0(PairedObject* o, Ev_1A6DE0* ev) {
    if (ev->flags & 0x20) {
        switch (o->state) {
        case 1: case 2: case 3: case 4: case 5: case 7: case 8:
            SetPairedState(o, 9);
            break;
        case 6: {
            HitTarget* c = (HitTarget*)o->partner;
            SetPairedState(o, 9);
            if (c) SetHitTargetState(c, 9);
            break;
        }
        }
        if (o->state == 9) {
            HitTarget* t = (HitTarget*)o->notifyRecord;
            if (t) {
                Msg_1A6DE0 m;
                m.kind = 6;
                m.a = ev->a;
                m.b = ev->b;
                m.a.z += 3000.0f;
                t->desc->m1B(t, &m);
            }
            StartSoundEffect(id_1A6DE0_37, 0, 0, &ev->b, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    return ev->flags != 0;
}

void* func_001A6F28(u8* self)
{
    Node_1A6F28* cur = *(Node_1A6F28**)(*(u8**)(self + 0x480));
    while (cur) {
        if (cur->flags != 0 && IsObjectOfKind(cur->data, 0x43) != 0)
            return cur->data;
        cur = cur->next;
    }
    return 0;
}

void func_001A6F88(HitTarget* self)
{
    s32* z;
    InitCollider(self);
    SetColliderAnchors(self, 2, (void*)&g_unitZVector, 3, 0);
    f32 one = 1.0f;
    f32 pt2 = 0.2f;
    z = (s32*)&self->scalePoly;
self->recoverDelay = one;
self->scalePoly.x = one;
self->hitLimit = 8;
self->state = -1;
self->hitInterval = pt2;
z[1]=0;z[2]=0;
}

void func_001A7008(HitTarget* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_hitTargetLoadLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

void func_001A7050(HitTarget* self)
{
    Blob8_1A7050 tmp = *(Blob8_1A7050*)&self->blob5A0;
    CopyCollider(self);
    *(Blob8_1A7050*)&self->blob5A0 = tmp;
}

void func_001A7098(HitTarget* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, g_hitTargetStartLinks);
    if (self->scaledObject != 0) {
        *(Blob8_1A7098*)&self->f57C = *(Blob8_1A7098*)((u8*)self->scaledObject + 0x2DC);
    }
    if (self->soundId != 0) {
        self->soundHandle = (void*)CreateStateWalker(self->soundId, self, -1, 0);
    }
    SetHitTargetState(self, 0);
    Fn_1A7098* vt = *(Fn_1A7098**)self;
    vt[7](self);
}

void func_001A7128(HitTarget* self)
{
    UpdateCollider(self);
    s32 n;
    while ((n = ChooseHitTargetState(self)) != self->state) {
        SetHitTargetState(self, n);
    }
    void* sub = self->scaledObject;
    if (sub != 0) {
        f32 t = -self->v150.z;
        if (9.99999975e-05f < t) {
            func_00155FA0(sub);
            TimePolynomial* v = &self->scalePoly;
            f32 p = v->x + t * (v->y + t * v->z);
            f32 lo = g_unitRange[0];
            f32 hi = g_unitRange[1];
            f32 x;
            if (p < lo) {
                x = lo;
            } else if (hi < p) {
                x = hi;
            } else {
                x = p;
            }
            f32 a = self->f57C * x;
            f32 b = self->f580 * x;
            u8* o = (u8*)self->scaledObject;
            *(f32*)(o + 0x2DC) = a;
            *(f32*)(o + 0x2E0) = b;
        } else {
            SetEffectSpawnerActiveForever(sub);
        }
    }
}

void func_001A7230(HitTarget* self)
{
    StepCollider(self);
    if (self->parent == 0) {
        u8 buf[0x30];
        func_00189378(&self->m110, 0, buf);
        func_001B9D10(self, buf, D_0026B850, g_frameDt);
    }
}

void func_001A7290(HitTarget* self, Obj_1A7290* obj)
{
    obj->a98 = obj->a98 * 0.6f;
}

s32 func_001A72B0(HitTarget* self, u8* p)
{
    s32 st;

    if ((*(s32*)(p + 0xC) & 0x10) == 0) {
        goto done;
    }
    if (self->parent != 0) {
        goto done;
    }
    st = self->state;
    if (st == 9) {
        goto done;
    }
    if (g_gameClock[1] < self->stateTime + self->hitInterval) {
        goto done;
    }
    st += 1;
    if (st >= self->hitLimit) {
        SetHitTargetState(self, 9);
        void* obj = self->notifyRecord;
        if (obj != 0) {
            Msg_1A72B0 msg;
            msg.q10 = *(Quad_1A72B0*)(p + 0x30);
            f32 f = msg.q10.f + 1000.0f;
            msg.kind = 6;
            msg.q20 = *(Quad_1A72B0*)(p + 0x20);
            msg.q10.f = f;
            Fn_1A72B0* vt = *(Fn_1A72B0**)obj;
            vt[31](obj, &msg);
        }
        StartSoundEffect(0x23, 0, 0, p + 0x20, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        SetHitTargetState(self, st);
        StartSoundEffect(0x14F, 0, 0, p + 0x20, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
done:
    return *(s32*)(p + 0xC) != 0;
}

s32 func_001A7420(HitTarget* self)
{
    s32 v = self->state;
    if (v > 0) {
        if (v >= 9) {
            if (v == 9) {
                goto zero;
            }
            goto end;
        }
        f32 t = g_gameClock[1] - self->stateTime;
        if (self->recoverDelay < t) {
            v -= 1;
        }
        goto end;
    }
    goto end;
zero:
    v = 0;
end:
    return v;
}

void func_001A7480(HitTarget* self, s32 value)
{
    s32 old = self->state;
    if (value == old) {
        return;
    }
    if (old == 9) {
        RemoveFinishedHitTarget(self->controller, self);
    }
    self->state = value;
    self->stateTime = g_gameClock[1];
    void* a2 = self->soundHandle;
    if (a2 != 0) {
        void* item = g_hitTargetStateIds[value];
        if (old == -1) {
            TeleportStateWalker(a2, item);
        } else {
            SetStateWalkerTarget(a2, item);
        }
    }
}

void func_001A7520(SoundStateObject* self)
{
    InitCollider(self);
    self->state = -1;
}

void func_001A7550(SoundStateObject* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_soundStateObjectLinks);
}

void func_001A7588(SoundStateObject* self)
{
    PackedWord8 tmp;
    tmp = self->keptBytes;
    CopyCollider(self);
    self->keptBytes = tmp;
}

void func_001A75D0(SoundStateObject* self)
{
    ListFrame frame;
    StartPlacedObject(self);
    if (self->soundId != 0) {
        self->soundHandle = (void*)CreateStateWalker(self->soundId, self, -1, 1);
    }
    BaseObject* n = (BaseObject*)self->children.head;
    while (n != 0) {
        if (IsObjectOfKind(n, 0x7E) != 0) {
            self->child7E = n;
            break;
        }
        n = n->next;
    }
    SetSoundStateObjectState(self, 0);
}

void func_001A7648(SoundStateObject* self)
{
    UpdateCollider(self);
    s32 v;
    while ((v = GetSoundStateObjectState(self)) != self->state) {
        SetSoundStateObjectState(self, v);
    }
}

s32 func_001A7698(SoundStateObject* p) { return p->state; }

void func_001A76A0(SoundStateObject* self, s32 idx)
{
    s32 old = self->state;
    if (old == idx) return;
    self->state = idx;
    void* child = self->soundHandle;
    f32 d = g_gameClock[1];
    self->stateTime = d;
    if (child == 0) return;
    s32 v = g_soundStateSoundIds[idx];
    if (old == -1) TeleportStateWalker(child, v);
    else SetStateWalkerTarget(child, v);
}

void func_001A7708(ObjectCreator* self)
{
    InitCollider(self);
    self->state = -1;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

void func_001A7750(ObjectCreator* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_objectCreatorLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

void func_001A7798(ObjectCreator* self)
{
    StartPlacedObject(self);
    if (self->createsObject == 0) {
        VFn_1A7798* vt = *(VFn_1A7798**)self;
        vt[7](self);
        return;
    }
    self->created = FindFirstObjectByIdGathered(self->world, 0x101, 0x59, self->children.head);
    SetObjectCreatorState(self, 0);
}

ASM_FUNC(func_001A7800);

void func_001A7998(ObjectCreator* self, s32 idx)
{
    if (self->state != idx) {
        if (self->activeHandle != 0) {
            StopAnimationPlayer(self->activeHandle);
            self->activeHandle = 0;
        }
        self->state = idx;
        void* s2 = 0;
        self->stateTime = g_gameClock[1];
        switch (idx) {
        case 1: {
            void* a2 = self->notifyRecord;
            s2 = self->f560;
            if (a2 != 0) {
                Buf_1A7998 buf;
                buf.n = 4;
                buf.q = *(Quad_1A7998*)&self->v140;
                FnP_1A7998* vt = *(FnP_1A7998**)a2;
                vt[31](a2, &buf);
            }
            break;
        }
        case 2: {
            void* a = self->created;
            ((FnI_1A7998*)*(void**)a)[25](a, 0);
            a = self->created;
            ((FnI_1A7998*)*(void**)a)[51](a, 1);
            break;
        }
        }
        if (s2 != 0) CreateAnimationPlayerWithoutPresetTargets(s2, self, 0, &self->activeHandle, 0.0f, 1.0f);
    }
}

s32 func_001A7AA0(ObjectCreator* self)
{
    s32 mode = self->state;
    s32 r = mode;
    P_1A7AA0* p;
    s32* g;
    s32 bits;
    if (mode == 1) {
        goto acc;
    }
    if (mode < 2) {
        goto out;
    }
    if (mode == 2) {
        goto flags;
    }
    goto out;
acc:
    p = (P_1A7AA0*)self->activeHandle;
    if (p == 0) {
        goto two;
    }
    if (!(p->q->f34 <= p->f14)) {
        goto flags;
    }
two:
    r = 2;
flags:
    g = *(s32**)&g_currentEntry;
    bits = *g;
    r = (bits & 2) ? 3 : r;
out:
    return r;
}

void func_001A7B20(Track_001A7B20* self, s32 a1, s32 a2)
{
    if (self->state == 0) {
        SetPadPatternState(self, 1);
    } else {
        SetPadPatternState(self, 3);
    }
    self->value4 = a1;
    self->value8 = a2;
}

void func_001A7B88(Obj_1A7B88* s)
{
    f32 dt = g_gameClock[5];
    switch (s->state) {
    case 2:
        if (*(s32*)g_gameClock != 0 && s->f18 > 0.0f) {
            s->f1C -= dt;
            if (s->f1C <= 0.0f) {
                s->index++;
                if (s->index >= s->table->count) {
                    s->index = 0;
                }
                u8 bytes[2];
                Entry_1A7B88* e = (Entry_1A7B88*)((u8*)s->table + (s->index << 3));
                bytes[0] = e->b[0];
                bytes[1] = e->b[1];
                func_002049E8(s->owner, s->channel, bytes);
                s->f1C = ((Entry_1A7B88*)((u8*)s->table + (s->index << 3)))->delay;
            }
            s->f18 -= dt;
        } else {
            SetPadPatternState(s, 3);
        }
        break;
    case 3:
    case 4:
        if (s->f1C > 0.0f) {
            StopPadPatternOutput(s);
            s->f1C -= dt;
        } else {
            SetPadPatternState(s, s->state == 3);
        }
        break;
    }
}

void func_001A7CE8(void* self, s32 index)
{
    StartPadPattern(self, (u8*)g_padPatterns + index * 0x104);
}

void func_001A7D18(void* self, Vec_1A7D18* p, f32 f)
{
    u8* s = (u8*)self;
    if (*(s32*)(s + 0xC) != 0 && p->count > 0) {
        if (IsPadPatternEnabled((void*)g_saveData) != 0) {
            *(f32*)(s + 0x18) = f;
            *(Vec_1A7D18**)(s + 0x10) = p;
            *(s32*)(s + 0x14) = 0;
            f32 x = p->x;
            *(s32*)(s + 0xC) = -1;
            *(f32*)(s + 0x1C) = x;
            SetPadPatternState(self, 2);
        }
    }
}

void func_001A7D98(Obj_1A7D98* self, s32 state)
{
    u8 bytes[2];
    if (state == self->state) return;
    switch (state) {
    case 2:
        bytes[0] = self->src->b4;
        bytes[1] = self->src->b5;
        func_002049E8(self->owner, self->channel, bytes);
        self->state = state;
        return;
    case 3:
    case 4:
        StopPadPatternOutput(self);
        self->f1C = g_frameStep * 4.0f;
        break;
    case 0:
    case 1:
        break;
    }
    self->state = state;
}

void func_001A7E40(Pair_001A7E40* self)
{
    u8 bytes[2];
    bytes[0] = 0;
    bytes[1] = 0;
    func_002049E8(self->owner, self->channel, bytes);
}

void func_001A7E70(void)
{
    if (g_padPatternSetting == 0) {
        g_padPatternSetting = 1;
    }
}

void func_001A7E90(GameProgress* ctx)
{
    s32 v = g_padPatternSetting;
    if (v == 2) {
        goto clear;
    }
    if (v < 3) {
        return;
    }
    if (v == 3) {
        goto set;
    }
    return;
clear:
    ctx->f19EC &= 0xFFFFFFDF;
    return;
set:
    ctx->f19EC |= 0x20;
}

s32 func_001A7EE8(GameProgress* ctx)
{
    s32 v = g_padPatternSetting;
    if (v == 1) {
        goto tail;
    }
    if (v < 2) {
        if (v == 0) {
            goto zero;
        }
        goto tail;
    }
    if (v == 2) {
        goto one;
    }
    if (v == 3) {
        goto zero;
    }
    goto tail;
one:
    return 1;
zero:
    return 0;
tail:
    return ((ctx->f19EC >> 5) ^ 1) & 1;
}

void func_001A7F50(GameProgress* self)
{
    s32 g = g_padPatternSetting;
    switch (g) {
    case 1: self->f19EC = self->f19EC ^ 0x20; break;
    case 2: self->f19EC = self->f19EC | 0x20; break;
    case 3: self->f19EC = self->f19EC & 0xFFFFFFDF; break;
    }
    if (self->f19EC & 0x20) {
        g_padPatternSetting = 3;
        return;
    }
    g_padPatternSetting = 2;
}
