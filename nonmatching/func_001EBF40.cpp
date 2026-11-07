// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 98/108 (90.7%), checked 2026-11-06
// NEAR: order: 25 of 27 instructions line up; s2 and s3 (self and the loop counter) are swapped.
//       Eight source variants did not move them.
// In the context of its file, src/main/file_1E88D0.cpp.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "fpu.h"
#include "world.h"
#include "warp_page.h"
#include "screen_element.h"
#include "globals.h"
#include "shapes.h"
#include "object_link.h"
#include "owner_message.h"
#include "game_clock.h"
#include "pad_record.h"
#include "memory_card.h"
#include "timeline.h"
#include "value_list_object.h"
#include "c62.h"
#include "attached_set.h"
#include "packet_writer.h"
#include "screen_fade.h"
#include "transform_object.h"
#include "oscillator.h"
#include "camera.h"
#include "game_progress.h"
#include "item_keeper.h"
#include "asm_func.h"

void func_001C9AF8(void);
void func_001E90A8(void* p);
void func_001AA110(void);
struct __attribute__((packed)) Entry8_1EBCD8 { u8 b[8]; };
struct List_1EBCD8 { u8 pad[0x630]; s32 count; Entry8_1EBCD8 items[1]; };
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a, void* p);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
void func_001DBCC8(void* a, void* cb, void* ctx, s32 b, s32 c);
void func_001EB550(BeatPressCollider* self);
struct Inner_1EB608 { u8 pad[0xC3C]; void* c3C; };
void func_001922E8(void* self);
s32 func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_001B64D8(void* a, s32 b);
extern s32 D_00262C64;
s32 func_001DDA80(void* p);
struct Probe_001E9038 {
    u8 pad0[0x50];
    s32 key;
};
s32 func_001C7468(void* self, void* probe);
void func_001E96F8(void* self, s32 mode);
s32 func_001BE5E8(void);
void func_001BEA28(void);
f32 func_002058A0(f32 v);
s32 func_001EB050(ValueRange* span, f32 x);
void func_001BEA50(void);
void func_001AA178(void);
extern float D_0026185C[];
void func_001C06A0(int a, int b, float t);
void func_00142ED0(float x);
void func_001BAC30(void* self);
f32 func_001EAFE0(f32 x, f32 y);
struct Vec3_1EAD30 { f32 x; f32 y; f32 z; };
s32 func_001BB290(void* a, s32 b, s32 c);
s32 func_001E89F0(void* a, void* b);
void* func_00129C20(s32 a, s32 b);
void func_001C9CF8(void* a);
typedef void* (*VFn_1E8EF8)(void* self);
struct Buf_1E8EF8 { s32 v[4]; };
void func_001C8418(KeyedConeAgent* self, void* p);
void func_001C8C08(KeyedConeAgent* self);
s32 func_001F3BD8(void* self, void* arg);
void func_001C8BC0(KeyedConeAgent* self);
void func_001C8E28(KeyedConeAgent* self);
extern u8 D_00261420[];
void func_001DDC38(void* sub, void* self);
void* func_00140FF8(void* p);
void func_00167E08(void* self);
s32 func_001E9970(void);
extern s32 D_00270458;
extern s32 D_00275DBC;
void func_001C6F48(void* self);
void* func_0018D500(s32 size);
void func_001BEA78(void);
void func_001E9570(void* g);
void func_001A7D98(void* self, s32 mode);
void func_001AA0C0(void);
struct Obj_1EA620 { u8 pad[0xC]; f32 f0C; };
f32 func_001EA4B8(f32 a, f32 b, f32 c, void* p, f32* out);
f32 func_001EA408(f32 a);
f32 func_001EA620(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1);
s32 func_001F6708(void);
struct Coeffs_1EA4B8 { f32 p0; f32 p1; f32 p2; };
s32 func_001EACA0(f32* roots, f32 a, f32 b, f32 c);
void func_00167D68(void* self);
struct Entry_1EBFB0 { s32 a; s32 b; s32 c; };
void func_001C72A0(void* self);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6DF8(void* a, void* self);
void* func_0018D568(s32 size, void* name);
s32 func_0015A418(void* a, s32 b, s32 c, void* self);
struct Entry_275D48 { s32 id; f32 v; s32 z; };
f32 func_001EA4B8(void* p, void* out, f32 a, f32 b, f32 c);
s32 func_001C8010(KeyedConeAgent* self);
extern s32 D_00274738;
extern f32 D_00261868[];
void func_001E98E8(ElementStack* a, f32 f);
void func_0018C178(MemoryCard* a, s32 v);
void func_001F0220(u8* a, s32 v);
void func_001DDA50(void* a);
void func_001DDA20(void* a);
void func_001A7E70();
extern u32 D_00262C68;
extern u32 D_00262C6C;
extern s32 D_002701B8;
extern void func_0016E118(s32 n);
extern void* func_001F4378(void);
extern void func_001F4808(void* x);
extern void func_0016EC20(PadRecord* p, s32 n);
extern s32 func_0018C568(MemoryCard* g);
extern void func_001605E8(void* p);
extern void func_00160948(void);
extern void func_00194D30(void* self, s32 a, s32 b);
extern void func_001E9498(ElementStack* o, ScreenElement* g);
extern void func_001E98E8(ElementStack* o, f32 v);
extern void func_001E96F8(ElementStack* o, s32 mode);
extern void func_001409E0(void);
extern void func_001A9FD0(void);
struct Item_1EB748 { s32 type; s32 a; f32 b; s32 c; };
struct List_1EB748 { u8 pad[0x34]; s32 n; Item_1EB748* items; s32 cur; };
struct Grid_1EB748 {
    u8 pad0[0xC38];
    List_1EB748* list;
    u8 pad1[0xC70 - 0xC3C];
    s32 row;
    u8 pad2[0xC7C - 0xC74];
    f32 base;
    u8 pad3[0xC88 - 0xC80];
    f32 scale;
};
typedef s32 (*Fn_1EB748)(BeatPressCollider* self, void* arg);
typedef void (*GFn_1EB748)(Player* g, void* arg);
struct In_1EB748 { u8 pad[0xAA]; u16 fAA; };
s32 func_001F3BD8(void* a, Vec4U* out);
s32 func_001F3C08(void* a, Mat3U* out);
void func_001BFCD8(s32 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 func_00160C58(void);
void func_001929D0(Player* g);
void func_001D7098(OwnerMessage* out, s32 mode, BeatPressCollider* self);
void func_001EB698(void);
void func_001ED020(TempoAgent* o);
void func_001C0C08(s32 a, s32 b);
void func_0017CE20(void* a, Player* g);
extern s32 D_00275C34;
extern u32* D_006256D0;
extern s32 D_006256D4;
extern u32 D_006256D8;
extern u8 D_00148D7C[];
extern u32 D_002476A0[];
struct Crc_1E9B30 {
    static u32 Step(u32 h, u8 b) { return D_002476A0[(h ^ b) & 0xFF] ^ (h >> 8); }
};
void func_001921A8(BeatPressCollider* self);
f32 func_001EAAE0(f32 lo, f32 hi);
f32 func_002059E0(f32 x);
s32 func_001DDA80(World* p);
union Bits_1EAE78 {
    double d;
    u64 u;
};
double func_001FCD20(double a, double b);
struct Node_1E9EE8;
struct Vtbl_1E9EE8 {
    u8 pad0[0x7C];
    void (*update)(Node_1E9EE8*, s32, f32);
};
struct Node_1E9EE8 { Vtbl_1E9EE8* vtbl; };
struct Iter_1E9EE8 { List01* list; u8* link; s32 offset; Iter_1E9EE8* prev; };
struct Begin_1E9EE8 {
    static void Of(Iter_1E9EE8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        Iter_1E9EE8* prev = (Iter_1E9EE8*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
        it->prev = prev;
    }
};
struct Next_1E9EE8 {
    static Node_1E9EE8* Of(Iter_1E9EE8* it)
    {
        Node_1E9EE8* obj = *(Node_1E9EE8**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct End_1E9EE8 {
    static void Of(Iter_1E9EE8* it) { D_0027B314 = (ListFrame*)it->prev; }
};
void func_00124EE8(Node_1E9EE8* n, f32 dt);
void func_0012EBD8(Node_1E9EE8* n, f32 dt);
void func_00159AD0(Node_1E9EE8* n, f32 dt);
void func_001DBE48(World* self);
struct Iter_1E9C78 {
    List01* list;
    u8** link;
    s32 offset;
    Iter_1E9C78* prev;
};
struct Begin_1E9C78 {
    static void Of(Iter_1E9C78* it, List01* list)
    {
        it->list = list;
        it->link = (u8**)list;
        it->offset = list->offset;
        it->prev = (Iter_1E9C78*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};
struct Next_1E9C78 {
    static u8* Of(Iter_1E9C78* it)
    {
        u8* obj = *it->link;
        it->link = (u8**)(obj + it->offset);
        return obj;
    }
};
struct End_1E9C78 {
    static void Of(Iter_1E9C78* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};
struct Holder_1E9C78;
struct Vt_1E9C78 {
    u8 pad0[0x134];
    void (*fn134)(Holder_1E9C78* self, f32 dt, u8* arg);
};
struct Holder_1E9C78 {
    Vt_1E9C78* vt;
};
void func_001E9B30(void);
Holder_1E9C78* func_001925F0(void);
void func_0015FF58(World* self);
void func_00124EE8(u8* n, f32 dt);
void func_0012EBD8(u8* n, f32 dt);
void func_00159AD0(u8* n, f32 dt);
void func_00159588(World* self);
void func_001C0070(void);
struct Iter_1EA118 { ActorList6C* list; u8* link; s32 offset; Iter_1EA118* saved; };
struct Next_1EA118 {
    static Actor6C* Of(Iter_1EA118* it)
    {
        Actor6C* obj = *(Actor6C**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct Begin_1EA118 {
    static void Of(Iter_1EA118* it, ActorList6C* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_1EA118*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};
void func_001E9EE8(World* self, f32 t);
void func_001E9C78(World* self, f32 t);
void func_001E9E30(World* self);
void func_00138C00(World* self, s32 a);
void func_001BDD00(World* self, s32 a, f32 t);
s32 func_00129D70(Actor6C* n);
void func_00129DF8(Actor6C* n);
void func_001BB9D0(Actor6C* n);
void func_001DBEC8(World* self, f32 t);
void func_001B4878(f32 t);
void func_001DDC40(World* self);
void func_0012E710(Actor6C* n);
void func_00143E40(Camera* a, s32 b, f32 t);
void func_001EA0A8(World* self, f32 t);
void func_00182C58(void);
struct Inner_1ED1D8 { u8 pad[0xC70]; s32 c70; };
struct Obj_1ED1D8 { u8 pad0[0x3C]; s32 f3C; Inner_1ED1D8* f40; s32 f44; };
void func_001837E0(void* self, s32 a, s32 b, s32 c);
struct Inner_1ED210 { u8 pad[0xC3C]; s32 c3C; };
void func_001ED318(Timeline* self, s32* p);
struct Item_1ED558 { s32 kind; s32 p; f32 f8; s32 fC; };
Item_1ED558* func_001ED4C8(void* self, s32 kind, s32 p);
struct Out_1ED650 { f32 x; f32 y; f32 z; };
struct Pair_1ED650 { f32 a; f32 b; };
void func_001EAD88(f32* a, f32* b);
void func_00192820(void);
void func_001B6598(void* sub, s32* out);
struct Entry_1ED090 { void* a; s32 b; };
void func_0012F810(void* a, TempoAgent* self);
s32 func_001EDEF0(void* self);
s32 func_001EE560(PacketWriter* s);
void func_00182C18(BaseObject* self);
void func_001BA550(Collider* o, Attach03* node);
void func_001BA528(Collider* o, Attach03* node);
void func_001DBB90(void* owner, Attach03* list);
void func_001F0220(void* o, s32 mode);
void func_0015F9A0(void* a, AttachedGroup* s);
void func_0015F8B0(void* a, AttachedGroup* s);
void func_001F57E0(void* p);
void func_00123ED0(void* self);
void func_001EF900(void* self, s32 b);
s32 func_0013EC00(void* a, s32 b, void* c, s32 d, s32 e, s32 f, s32 g, s32 h);
struct Cursor_1EE368 { u8 pad[0xC]; u32* cursor; };
void* func_001DBCC8(s32 a, void* b, void* c, s32 d, s32 e);
void func_00192850(void);
struct Packer_1EE528 {
    u8 pad0[0xC]; u32* cursor; u8 pad1[0xC]; s32 last;
    void push(u32 word)
    {
        u32* p = cursor;
        cursor = p + 1;
        *p = word;
    }
};
void func_001ED210(void* p);
struct Angles_1EDE38 { f32 unused; f32 first; f32 second; };
struct Vec3_1EDE38 { f32 x; f32 y; f32 z; };
void func_001EAD88(f32 angle, f32* a, f32* b);
typedef u64 Quad_1EEB60 __attribute__((mode(TI)));
s32 func_001EEA40(void* self, void* node, Quad_1EEB60 q, s32* out);
typedef void (*VFn_1EF3A8)(void* self, void* arg);
void func_00125B70(void* obj, void* c, void* out);
void func_00125C90(void* obj, void* s, void* out);
void func_001C8418(void* self, void* p);
void func_001C8C08(void* self);
void func_00182C18(void* self);
struct Out_1ED6B0 { f32 x; f32 y; f32 z; };
void func_001EE368(void* s, s32 target);
s32 func_001EE560(void* self, s32 a, s32 b, s32 c);
void func_00152B80(void* obj, s32 a, s32 b);
void func_00138398(void* src, s32* count, void** out);
s32 func_00137BE0(void* src);
s32 func_00137C40(void* src);
void func_0011EC40(void* a, void* b);
struct Msg_1EF3D8 { AttachedSet* self; Collider* obj; };
void func_001EF520(AttachedSet* self);
void func_00127378(void* self, s32 kind, void* msg);
void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
void func_001F5590(void* a, void* b);
extern s32 D_00275AF0;
s32 func_001F00F0(ScreenFade* self, s32 a1, s32 a2);
void func_001F0220(ScreenFade* self, s32 state);
void func_001C0000(s32 flag, f32 x);
struct Dev_1ECBC8;
typedef void (*Cb_1ECBC8)(void);
typedef s32 Id_1ECBC8;
void func_001C7CB8(TempoAgent* self);
void func_001ED1D8(Timeline* sub);
void func_001ED278(Timeline* sub);
void func_001B6598(Dev_1ECBC8* dev, s32* out);
void func_001C0C68(Id_1ECBC8 a, Dev_1ECBC8* b);
s32 func_001C0C50(Id_1ECBC8 a);
void* func_001DBCC8(Dev_1ECBC8* dev, Cb_1ECBC8 cb, TempoAgent* self, s32 a3, s32 a4);
void func_001ECB18(void);
void func_001C9008(void* self, void* arg);
void func_00152CE0(void* self, s32 index, s32 count);
extern void* D_002505C0[6];
void* func_0018D5C0(u32 n);
void func_001EE5C8(void* s, void* a1, s32 size, void* a3, s32* outSize, u8** outCursor);
struct Mask_1EE9D0 { u8 pad[0x3C]; s32 count; s32* table; };
extern s32 D_002640A4;
void func_00180398(s32 a, f32 v);
void func_0019DDA0(s32 a, s32 b, s32 c, s32 d, void* e, f32 f, f32 g, f32 h, f32 i);
void func_001AC060(void* p);
void func_001EE7D0(PacketWriter* self, s32 n, void* buf, s32 flag);
extern u8 D_0024A0E0[];
s32 func_00152888(PacketWriter* self);
struct Link_1EECE0;
struct Link_1EECE0 {
    s32* a; s32* b; s32 c; Link_1EECE0* prev;
    Link_1EECE0(s32* p) : a(p), b(p), c(p[2]), prev((Link_1EECE0*)D_0027B314) {}
    ~Link_1EECE0() { D_0027B314 = (ListFrame*)prev; }
};
void func_00124A48(AttachedSet* self);
void func_001F55A8(void* self);
struct Mgr_1EF900;
struct Evt_1EF900 {
    void* self;
    s32 old;
    s32 cur;
};
s32 func_0013ECB0(Mgr_1EF900* mgr, s32 a, void* b, C62* self, s32 c);
void func_001B6598(s32 sub, s32* out);
struct Chain_1ED318 {
    u8 pad[0x680];
    s32 f680;
    s32 pad2;
    s32 f688;
};
struct Inner_1ED318 {
    u8 pad[0xC3C];
    Chain_1ED318* fC3C;
    u8 pad2[0xC4C - 0xC40];
    s32 fC4C;
};
struct Msg_1ED318 {
    s32 kind;
    s32 pad[2];
    s32 f0C;
};
void func_001EC7A8(Inner_1ED318* p);
void func_001837E0(void* self, s32 a, s32 b, s32* c);
void func_0016EC88(void* p);
void func_001BFCD8(s32 a0, Timeline* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
struct Entry_1ED4C8 { s32 f00; s32 f04; f32 f08; s32 pad0C; };
extern u8 D_00625760[];
s32 func_001F5C0C(Entry_1ED4C8* dst, s32 value, s32 size);
// The dead "li v0,2" after the func_001ED090 call is the compare constant of an
// "if (n == 2)" whose two arms compile identically: jump2 cross-jumps the arms after
// reload, deletes the branch and leaves the constant load.
struct Inner_1EC570 { u8 pad[0x34]; f32 f34; };
struct Sub_1EC570 { u8 pad0[0x8]; Inner_1EC570* inner; u8 pad1[8]; f32 f14; f32 f18; };
void func_001C91C8(TempoAgent* self, s32 a, s32 b);
void func_001603E8(s32 n);
void func_0018C7F8(void* p);
struct Vec3_1EDDB0 { f32 x; f32 y; f32 z; };
f32 func_00205778(f32 a, f32 b);
struct Entry_1ED0D8 { s32 key; s32 val; };
void func_0018D800(Entry_1ED0D8* dst, Entry_1ED0D8* src, s32 bytes);
struct Inner_1ED278 { u8 pad[0xC70]; s32 fC70; u8 pad2[0xC7C - 0xC74]; f32 fC7C; };
void func_001ED318(Timeline* self, Entry90* e);
void* func_001F5B08(void* dst, void* src, s32 size);
// An array-move helper: its parameter copies give retail its (i * 4 + self) base shared by both pointers.
// Moves n bytes of the item list down over a removed item.
struct Shift_1EFA88 {
    static void Of(C62** dst, C62** src, s32 n)
    {
        func_001F5B08(dst, src, n);
    }
};
struct Sub_1ECB18 { u8 pad0[0x34]; f32 f34; };
struct Obj_1ECB18 {
    u8 pad0[8];
    Sub_1ECB18* f8;
    u8 pad0C[8];
    f32 f14;
    f32 f18;
};
struct Ent_1ECB18 { Obj_1ECB18* f0; s32 f4; };
struct Self_1ECB18 {
    u8 pad0[0xC68];
    s32 fC68;
    Ent_1ECB18* fC6C;
    u8 pad1[4];
    s32 fC74;
    u8 pad2[0xC];
    f32 fC84;
};
void func_001DDAD0(World* x);
struct Match_1EFFA0 {
    static s32 Of(IdentityKey* t)
    {
        IdentityKey* p;
        p = &D_00275B04;
        if (t == p) {
            return 1;
        }
        if (p == 0) {
            return 0;
        }
        return ((p->signedWords[2] ^ p->signedWords[6]) ^ (t->signedWords[2] ^ t->signedWords[6])) == 0;
    }
};
void func_00143940(void* p, f32 v);
void func_00188B08(void* a, void* b, void* out);
struct Src_1F00C0 {
    QuadP pair;
    s32 mid;
};
void func_00128018(void* a0, void* a1, void* a2, void* a3);
s32 func_00128018(void* a, s32 b, void* c, s32 d);
void func_001AD0D0(T217D_3D0* self, s32 a, s32 b);
void func_001F18B0(void* self, s32 value);
extern s32 D_00276654;
struct Msg_1F0428 { s32 kind; void* obj; void* value; u8 pad; s32 last; };
void func_001EFFA0(void* dst, void* args, s32 count);
void func_001F1050(void* self, u32 mode);
void* func_0018D500(int size);
void func_00182C58(void* self);
void func_00182ED8(void* a);
// The pad (include/c73.h's neighbours): its buttons at +0xAA, its direction timers at +0x30 .. 0x3C.
struct Pool_1F1A08;
struct Q3_1F1A08;
struct Val_1F1A08;
typedef s32 Key_1F1A08;
typedef s32 Id_1F1A08;
s32 func_001F0490(WarpPage* o, s32 n, s32* a, s32* b);
s32 func_0016EC98(PadRecord* t);
s32 func_0016EED0(PadRecord* t);
void func_001F1648(WarpPage* o, s32 n);
void func_0016EC20(Pool_1F1A08* p, s32 n);
s32 func_001F0468(void);
void func_001E9570(ElementStack* q);
Val_1F1A08* func_00160180(Key_1F1A08 k);
void func_001F0428(Val_1F1A08* v, s32 m, s32 n);
void func_001BFCD8(Id_1F1A08 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 func_001EA4B8(Q3_1F1A08* p, s32 a1, f32 f12, f32 f13, f32 f14);
struct Anim_1F1C90 { u8 pad[0x34]; f32 f34; };
void func_001AA060(void* self);
s32 func_001F0490(void* o, s32 n, s32* a, s32* b);
void func_001F1590(void* self, s32 a1, s32 a2);
void func_001F1610(void* self);
void func_001AA8B0(void* self, f32 v);
void func_001AA8C0(void* self, f32 v);
void func_001BED48(void);
void func_001BED70(void);
s32 func_0016E0F0(s32 bits);
struct Obj_1F0580 { u8 pad[0x2F4]; s32 mode; };
struct Same_1F00F0 {
    static s32 Of(IdentityKey* t, IdentityKey* o)
    {
        if (t == o) {
            return 1;
        }
        if (o == 0) {
            return 0;
        }
        return ((o->signedWords[2] ^ o->signedWords[6]) ^ (t->signedWords[2] ^ t->signedWords[6])) == 0;
    }
};
struct Blk20_1F00F0 {
    QuadP p;
    s32 w;
};
extern void* D_0026FA68;
extern s32 D_002623CC;
void func_001E4E80(void* a, s32 b, s32 c, s32 d, s32 e);
s32 func_001601A0(s32 a);
void func_001DDB58(void* a);
void func_00168B68(f32 t);
struct Cfg_1F2688;
s32 func_001F5C0C(Cfg_1F2688* p, s32 zero, s32 size);
// The text style the warp menu draws with: the static initialiser (func_001F2688) zeroes it, then
// sets its kind, two sizes given as integers, 0.3 twice and its colour.
struct Cfg_1F2688 {
    u8 pad0[4];
    u8 kind;
    u8 pad5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    s32 f18;
    Cfg_1F2688(s32 a, s32 b)
    {
        func_001F5C0C(this, 0, 0x1C);
        kind = 0x3D;
        f8 = a;
        fC = b;
        f14 = f10 = 0.3f;
        f18 = (s32)0xFF7D4B00;
    }
};
extern f32 D_00276650;
struct Mgr_1F18B0;
struct Loc_1F18B0;
struct Obj_1F18B0;
struct Rec_1F18B0 {
    u8 pad00[0x18];
    Mgr_1F18B0* f18;
    u8 pad1C[0x24];
};
void func_00128018(Mgr_1F18B0* a0, Obj_1F18B0* a1, void* a2, Loc_1F18B0* a3);
struct Clr_1F1960 { s32 a, b, c, d, e, f; };
s32 func_0015C188(s32 n);
Font* func_0015C1C0(s32 n);
void func_001F5C0C(Clr_1F1960* p, s32 v, s32 size);
struct __attribute__((packed)) Ptr_1F0660 { WarpPage* p; };
extern void func_00124A48(WarpPage* o);
struct Rec_1F1050 { s32 f0; f32 f4; s32 f8; };
struct Sub_1F1050 {
    void (**vtbl)(Sub_1F1050*);
    u8 pad04[0x30];
    f32 f34;
    u8 pad38[0x298 - 0x38];
    Rec_1F1050* f298;
};
s32 func_001F0580(WarpPage* o, s32 n);
void func_001F0878(WarpPage* o, s32 n);
void func_001F0908(WarpPage* o);
void func_001F18B0(WarpPage* o, s32 n);
void func_001BF788(void* p, s32 n);
void func_00159C28(Rec_1F1050* r);
void func_00126C58(Sub_1F1050* o);
void func_0012C918(Sub_1F1050* a, WarpPage* b, s32 c, void* d, f32 e, f32 f);
void func_001BFCD8(s32 a0, void** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
struct Node_1F0758;
struct Iter_1F0758 { List01* list; u8* link; s32 offset; Iter_1F0758* saved; };
void func_001249A8(WarpPage* self);
void func_00124DF8(WarpPage* self, s32 n, void* table);
void func_00182ED8(Node_1F0758* node);
struct Next_1F0758 {
    static Node_1F0758* Of(Iter_1F0758* it)
    {
        Node_1F0758* obj = *(Node_1F0758**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct Begin_1F0758 {
    static void Of(Iter_1F0758* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_1F0758*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};
HoldingMember* func_0015A418(World* host, s32 kind, s32 id, HoldingMember* ctx);
struct Ent_1F1648 { s32 f0; u8 rest[0x30]; };
struct Obj_1F1648 { u8 pad0[0x2DC]; s32 f2DC; u8 pad1[0x2F4 - 0x2E0]; s32 f2F4; u8 pad2[0x314 - 0x2F8]; Ent_1F1648 ents[1]; };
extern s32 (*D_00276608[6])[4];
void func_001F1590(Obj_1F1648* self, s32 e, s32 n);
enum Sound_1F1648 { SOUND_1F1648_OK = 0x79, SOUND_1F1648_FAIL = 0x7B };
void func_001BFCD8(Sound_1F1648 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
struct Ent_1F0908 { s32 a; s32 type; s32 id; s32 d; };
struct Tbl_1F0908 { u8 pad0[0x54]; s32 count; Ent_1F0908* ents; };
struct Slot_1F0908 { u8 pad0[0x34]; f32 f34; };
struct SlotRef_1F0908 { Slot_1F0908* s; u8 pad[0x30]; };
struct Obj_1F0908 {
    u8 pad0[0x14];
    void* f14;
    u8 pad18[0x2E8 - 0x18];
    Tbl_1F0908* tbl;
    u8 pad2EC[4];
    u8 f2F0[8];
    SlotRef_1F0908 slots[1];
};
void func_0012C918(Slot_1F0908* s, Obj_1F0908* o, s32 c, void* d, f32 a, f32 b);
BaseObject* func_0015A418(void* o, s32 a, s32 b, Obj_1F0908* c);
struct Locals_1F1E38 { s32 k; s32 pad[3]; f32 x; f32 y; };
void func_001613C0(PacketWriter* f, s32 a, s32 b, s32 c);
void func_00161708(PacketWriter* f, u64 a, u64 b);
void func_00161458(PacketWriter* self, u32 value);
void func_001615F0(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void func_001E90A8(ElementStack* self);
void func_001E9498(ElementStack* self, ScreenElement* node);
void func_001E96F8(ElementStack* self, s32 state);
void func_001E98E8(float x);
f32 func_001EA4B8(Coeffs_1EA4B8* k, f32* out, f32 x, f32 y, f32 z);
void func_001ED090(TempoAgent* self, void* a, s32 b);
void func_001ED1D8(Obj_1ED1D8* self);
void func_001ED210(Timeline* self);
void func_001ED278(Timeline* self);
void func_001ED318(Timeline* self, Msg_1ED318* msg);
void func_001EF900(C62* self, s32 state);
s32 func_001F00F0(ScreenFade* self, PadRecord* o, void* param2);
void func_001F1050(WarpPage* self, u32 next);
void func_001F1590(WarpPage* self, s32 a1, s32 a2);
void func_001F18B0(Obj_1F18B0* self, s32 idx);

ObjectLink D_00275B60[8] = {
    { 3, 0x2D5, 0xC50 }, { 3, 0x2E7, 0xC60 }, { 7, 0x2E1, 0xC64 }, { 7, 0x2E2, 0xC68 },
    { 7, 0x2E3, 0xC6C }, { 7, 0x2E4, 0xC70 }, { 7, 0x2E5, 0xC74 }, { 7, 0x2E6, 0xC78 }
};
// word read whole / address only, 4 bytes to next label
// readers pass only its address; byte buffer, size to next label
u8 D_00275BC0[4] = {0};
INCLUDE_DATA(D_00275BC4);
// size: s32 read as one word (func_00150000.cpp and 001AC000.cpp test bit 8)
// size: s32 compared with 1/2 in 00148000 and 00194000
s32 D_00275BEC = 0;
s32 D_00275BF0[10] = { 0, 0, 3, 10, 6, 63, 3, 11, 5, 31 };
f32 D_00275C18[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
f32 D_00275C28[3] = { 1.0f, 0.0f, 0.1f };
INCLUDE_DATA(D_00275C34);
// size: func_0012A610/func_0012A6E0 copy it as a 16-byte vector
Quad16 D_00275C40 = {0};
f32 D_00275C50[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
ValueRange D_00275C60 = { 0.0f, 1.0f };
ValueRange D_00275C68 = { -1.0f, 1.0f };
f32 D_00275C70[4] = { 0.5f, 0.8f, 0.0f, 0.0f };
f32 D_00275C80[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
ObjectLink D_00275C90[1] = { { 0, 0x4C9, 0x610 } };
ObjectLink D_00275CA0[4] = {
    { 4, 0x4D0, 0x618 }, { 4, 0x4D1, 0x61C }, { 4, 0x4D2, 0x620 }, { 4, 0x4D3, 0x624 }
};
f32 D_00275CD0 = 700.0f;
f32 D_00275CD4 = 650.0f;
s32 D_00275CD8[4] = { 1228, 1230, 1229, 1231 };
s32 D_00275CE8[4] = { 574, 576, 575, 577 };
s32 D_00275CF8[4] = { 1247, 1248, 1249, 1250 };
ObjectLink D_00275D08[5] = {
    { 1, 0x4EB, 0xC50 }, { 0, 0x4E7, 0xC24 }, { 0, 0x4E8, 0xC28 }, { 0, 0x4E9, 0xC2C },
    { 0, 0x4EA, 0xC30 }
};
Entry_275D48 D_00275D48[9] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 }, { 0x3B, 80.0f, 0 },
    { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }, { 0x52, 80.0f, 0 }, { 0x53, 80.0f, 0 },
    { 0x54, 80.0f, 0 }
};
// word read whole / address only, 4 bytes to next label
s32 D_00275DB4 = 0;
// size: s32 state compared/assigned in 001EC000
s32 D_00275DB8 = 0;
INCLUDE_DATA(D_00275DBC);
s32 D_00275DD0[16] = { 4, 2, 1, -1, 8, 4, 2, -1, 12, 6, 3, -1, 16, 8, 4, 2 };
s32 D_00275E10[92] = { 2, 0x2EB, 0x2DC };
// word read whole / address only, 4 bytes to next label
ScreenFade D_00275F80 = { 0 };
f32 D_00275FC0 = 0.5f;
// Globals defined from C.
s32 D_00275FC8[6] = { 0, 2, 4, 4, 4, 0 };
ObjectLink D_00275FE0[52] = {
    { 0x2, 0x1CB, 0x2E4 },
    { 0x2, 0x1CC, 0x2E8 },
    { 0x2, 0x1CD, 0x2F8 },
    { 0x2, 0x1CE, 0x32C },
    { 0x2, 0x1CF, 0x360 },
    { 0x2, 0x1D0, 0x394 },
    { 0x2, 0x1D1, 0x3C8 },
    { 0x2, 0x1D2, 0x3FC },
    { 0x2, 0x1D3, 0x430 },
    { 0x2, 0x1D4, 0x464 },
    { 0x2, 0x1D5, 0x498 },
    { 0x2, 0x1D6, 0x500 },
    { 0x2, 0x1E2, 0x304 },
    { 0x2, 0x1E3, 0x338 },
    { 0x2, 0x1E4, 0x36C },
    { 0x2, 0x1E5, 0x3A0 },
    { 0x2, 0x1E6, 0x3D4 },
    { 0x2, 0x1E7, 0x408 },
    { 0x2, 0x1E8, 0x43C },
    { 0x2, 0x1E9, 0x470 },
    { 0x2, 0x1EA, 0x4A4 },
    { 0x2, 0x1EC, 0x50C },
    { 0x2, 0x1EB, 0x4D8 },
    { 0x2, 0x1D7, 0x2FC },
    { 0x2, 0x1D8, 0x330 },
    { 0x2, 0x1D9, 0x364 },
    { 0x2, 0x1DA, 0x398 },
    { 0x2, 0x1DB, 0x3CC },
    { 0x2, 0x1DC, 0x400 },
    { 0x2, 0x1DD, 0x434 },
    { 0x2, 0x1DE, 0x468 },
    { 0x2, 0x1DF, 0x49C },
    { 0x2, 0x1E1, 0x504 },
    { 0x2, 0x1E0, 0x4D0 },
    { 0x2, 0x1F8, 0x310 },
    { 0x2, 0x1F9, 0x378 },
    { 0x2, 0x1FA, 0x3AC },
    { 0x2, 0x1FB, 0x3E0 },
    { 0x2, 0x1FC, 0x414 },
    { 0x2, 0x1FD, 0x448 },
    { 0x2, 0x1FE, 0x47C },
    { 0x2, 0x1FF, 0x4B0 },
    { 0x2, 0x1ED, 0x30C },
    { 0x2, 0x1EE, 0x340 },
    { 0x2, 0x1EF, 0x374 },
    { 0x2, 0x1F0, 0x3A8 },
    { 0x2, 0x1F1, 0x3DC },
    { 0x2, 0x1F2, 0x410 },
    { 0x2, 0x1F3, 0x444 },
    { 0x2, 0x1F4, 0x478 },
    { 0x2, 0x1F5, 0x4AC },
    { 0x2, 0x1F7, 0x514 },
};
s32 D_00276250 = -1;
f32 D_00276258[4] = { 600.0f, 0.0f, 0.25f, 0.0f };
f32 D_00276268[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00276278[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00276288[4] = { 1.0f, 0.0f, 0.200000003f, 0.0f };
s32 D_00276298[11][4] = {
    { 1, 10, 10, 5 },
    { 2, 0, 3, 5 },
    { -1, 1, 3, 5 },
    { 2, 10, -1, 1 },
    { 8, -1, 5, 7 },
    { 2, 0, 1, 4 },
    { -1, 7, 7, 8 },
    { 6, 8, 4, 6 },
    { 6, -1, 7, -1 },
    { -1, -1, -1, -1 },
    { 0, -1, -1, 0 }
};
s32 D_00276348[11][4] = {
    { 4, 10, 4, 10 },
    { 8, 0, 4, 3 },
    { 5, 3, 1, -1 },
    { 2, 10, 1, -1 },
    { 7, 0, -1, 1 },
    { 8, 2, 8, -1 },
    { 8, 7, -1, 8 },
    { 6, 4, -1, 1 },
    { -1, 1, 6, 5 },
    { -1, -1, -1, -1 },
    { 3, -1, 0, -1 }
};
s32 D_002763F8[11][4] = {
    { 1, 10, 10, 1 },
    { 3, 0, 7, 2 },
    { 4, 0, 1, -1 },
    { 8, 1, 1, 4 },
    { 3, 2, 1, 2 },
    { 6, 10, -1, 8 },
    { -1, 5, -1, 8 },
    { -1, 0, 8, 1 },
    { -1, 7, 5, 7 },
    { -1, -1, -1, -1 },
    { 5, -1, -1, 0 }
};
s32 D_002764A8[11][4] = {
    { 1, 10, 10, 2 },
    { 7, 0, 4, 2 },
    { 5, 0, 1, 5 },
    { 8, 4, -1, 4 },
    { 3, 10, 3, 1 },
    { 6, 2, 1, -1 },
    { -1, 5, 7, -1 },
    { 8, 1, 8, 6 },
    { -1, 4, 3, 1 },
    { -1, -1, -1, -1 },
    { 4, -1, -1, 0 }
};
s32 D_00276558[11][4] = {
    { 2, 10, 2, 4 },
    { -1, -1, -1, -1 },
    { 3, 0, -1, 3 },
    { 8, 0, 2, 4 },
    { 5, 0, 3, 5 },
    { 6, 4, 4, -1 },
    { 8, 5, 8, -1 },
    { -1, -1, -1, -1 },
    { -1, 3, -1, 6 },
    { -1, -1, -1, -1 },
    { 0, -1, -1, 0 }
};
s32 (*D_00276608[6])[4] = { 0, (s32(*)[4])D_00276298, (s32(*)[4])D_00276348, (s32(*)[4])D_002763F8, (s32(*)[4])D_002764A8, (s32(*)[4])D_00276558 };
#ifndef VERSION_EU
// PAL has no style here (its func_001F1960 draws without one): its static initialiser only
// sets D_00276650.
Cfg_1F2688 D_00276620(2, 1);
#endif
INCLUDE_DATA(D_0027663C);
#ifdef VERSION_EU
// PAL's own addresses for these two, which the tools do not pair with US's (VERSION_NAME).
f32 D_eu_0027FDAC = 24.0f;
f32 D_eu_0027FDB0 = D_eu_0027FDAC * 0.75f;
#else
f32 D_00276648 = 24.0f;
f32 D_00276650 = D_00276648 * 0.75f;
#endif
s32 D_00276654;


void func_001E88D0(KeyedConeAgent* self)
{
    func_00167D68(self);
    self->fC58 = 0x2D8;
    self->fC14 = 30000.0f;
    self->fC10 = 30000000.0f;
    self->fC20 = 3000000.0f;
    self->fC24 = 3000000.0f;
    self->fC28 = 0;
    self->fC2C = 6.2831855f;
}

// The file's first read-only data, for func_001E89F0.
extern const f32 D_0024E600[4] = {3.40282347e+38f, 0.0f, 0.0f, 0.0f};

void func_001E8948(KeyedConeAgent* self)
{
    ResolveObjectLinks(self, 8, D_00275B60);
    func_001DDC38(self->world, self);
    if (self->fC50 != 0) {
        self->fC54 = CreateStateWalker(self->fC50, 0, 0x2D7, 0);
    }
    self->fC90 = 4;
    for (u32 i = 0; i < 4; i++) {
        self->fC80[i] = TakeFlagTableIndex(g_flagTable);
    }
    func_00167E08(self);
}

ASM_FUNC(func_001E89F0);

INCLUDE_RODATA(jtbl_0024E610);
INCLUDE_RODATA(jtbl_0024E650);
ASM_FUNC(func_001E8A50);

s32 func_001E8D58(KeyedConeAgent* self)
{
    s32 a1;
    if (self->fC5C <= 0) {
        self->fBFC = 3.4028235e+38f;
    }
    a1 = self->f724;
    if (a1 == 10) {
        a1 = (self->f7E0 == 0) ? 8 : 10;
    } else {
        a1 = ChooseAgentState(self);
    }
    return a1;
}

s32 func_001E8DB0(KeyedConeAgent* a0)
{
    if (a0->fC40 != 0) return 0;
    return a0->fC5C != 0;
}

s32 func_001E8DD0(KeyedConeAgent* a0)
{
    if (a0->fC58 != 0x2DB) return 0;
    {
        s32 v = a0->fC5C;
        if (v == 5 || v == 0) return 0;
        return 1;
    }
}

void func_001E8E08(KeyedConeAgent* a0)
{
    if (a0->fC58 != 0x2DA) {
        s32 v = a0->fC5C - 1;
        if (!(0 < v)) v = 0;
        a0->fC5C = v;
    }
    SteerAgentAlongPath();
}

void func_001E8E48(KeyedConeAgent* self)
{
    if (self->fC58 == 0x2DA && self->f724 == 0xC && func_001BB290(self, 0, 0) != 0) {
        s32 s = func_001E89F0(self, (u8*)self + 0x140);
        if (s != self->fC7C) {
            s32 n = self->fC5C - 1;
            if (!(0 < n)) n = 0;
            self->fC5C = n;
            if (n > 0) {
                void* p = FindObjectHandle(s, -1);
                if (p != 0) SetStateWalkerTarget(p, 0x2E0);
                self->fC7C = s;
            }
        }
    }
    RestartAgentClip(self);
}

void func_001E8EF8(KeyedConeAgent* self)
{
    Buf_1E8EF8 loc;
    switch (self->f724) {
    case 4:
        if (self->fC40 != 0) {
            func_001C8418(self, (u8*)self + 0x190);
        } else {
            GetObjectWorldPosition(self->fC60, &loc);
            func_001C8418(self, &loc);
        }
        break;
    case 8: {
        void* r = ((VFn_1E8EF8*)self->desc)[102](self);
        if (r != 0) func_001C8418(self, (u8*)r + 0x140);
        break;
    }
    default:
        UpdateAgentGoal(self);
        break;
    }
}

void func_001E8FA8(KeyedConeAgent* self)
{
    if (self->f724 == 8) {
        func_001C8BC0(self);
    } else {
        UpdateAgentState(self);
    }
}

void func_001E8FE8(void)
{
    if (AreMenusAndFadeClear()) {
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    } else {
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
    }
}

s32 func_001E9038(KeyedConeAgent* self, Probe_001E9038* probe)
{
    s32 key = probe->key;
    u32 i = 0;
    s32 result;
    do {
        if (key == self->fC64[i]) {
            result = 0;
            goto done;
        }
        i++;
    } while (i < 6);
    result = TestAgentMayContact(self, probe);
done:
    return result;
}

void func_001E9088(void)
{
    InitElementStack(g_elementStack);
}

void func_001E90A8(ElementStack* self)
{
    self->resumeState = -1;
    self->state = -1;
    SetElementStackState(self, 3);
    self->items[0] = 0;
    self->count = 1;
}

void func_001E90E8(void* self)
{
    SetElementStackState(self, 3);
}

void func_001E9108(ElementStack* obj)
{
    f32 d = g_gameClock.elapsed - obj->stateTime;
    s32 s1 = obj->state;
    PadRecord* s2;
    s32 s5;
    if (D_00262C68 & 4) {
        s2 = &g_padRecord;
    } else {
        s2 = &g_blankPadRecord;
    }
    s5 = 0;
    if (D_00262C6C & 0x80) {
        if (0.1f < g_gameClock.time) {
            ClearPadSelectFlags(0x80);
        }
    }
    switch (obj->state) {
    case 0: {
        s32 a2 = 0;
        if (D_002701B8 == 0) {
            s32 m = g_memoryCard.displayMode;
            if (m == 2 || (m == 1 && g_memoryCard.state == 5)) {
                a2 = 1;
            }
        }
        if (a2) {
            func_001F4808(FindActiveObjectSubGroup());
        }
        break;
    }
    case 1: {
        u32 v = s2->flags;
        if (v & 0x800) {
            s32 t;
            ClearPadPressedBits(s2, 0x800);
            t = g_memoryCard.i4F48;
            g_memoryCard.i4F44 = t;
            if (t) {
                ApplyMemoryCardImage(&g_memoryCard);
            } else {
                ResetGameProgress(g_saveData);
            }
            func_00160948();
            s1 = obj->state;
        } else if (v & 0x100) {
            ClearPadPressedBits(s2, 0x100);
            SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0x17);
            s1 = obj->state;
        }
        break;
    }
    case 3: {
        if (D_00262C6C & 2) break;
        if (g_screenFade.mode) break;
        {
            u32 v = s2->flags;
            if ((v & 0x800) || (s2->f14 == 1 && 5.0f <= g_gameClock.time)) {
                SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0);
                s1 = obj->state;
                ClearPadPressedBits(s2, 0x800);
            } else if ((v = s2->flags) & 0x100) {
                T217D_0F0* g2 = &g_mapScreenList;
                WarpPage* x = g2->current;
                if (x == 0) break;
                if (x->mode) break;
                PushStackElement(obj, g2);
                s1 = obj->state;
                ClearPadPressedBits(s2, 0x100);
            }
        }
        break;
    }
    case 4:
        if (d <= 0.2f) {
            ApplyStackTimeScale(obj, (0.2f - d) * 5.0f);
        } else {
            s1 = 5;
        }
        break;
    case 6:
        if (d <= 0.5f) {
            ApplyStackTimeScale(obj, d + d);
        } else {
            s1 = 3;
        }
        break;
    case 2:
    case 5:
    case 7:
        s5 = 1;
        break;
    case 8:
    default:
        break;
    }
    SetElementStackState(obj, s1);
    {
        ScreenElement* e = obj->items[obj->count - 1];
        if (e) {
            if (e->vt->m04) {
                e->vt->m04(e, s2);
            }
        } else if (s5) {
            SetElementStackState(obj, 3);
        }
    }
    StepDiscSectorCheck();
    UpdateScreenElements();
}

void func_001E9498(ElementStack* self, ScreenElement* node)
{
    if (IsStreamVoiceLocked() && self->count == 1) {
        func_001BEA28();
    }
    if (self->count >= 2) {
        ScreenElement* last = self->items[self->count - 1];
        if (last->vt->m03) {
            last->vt->m03(last, 0);
        }
    }
    if (node->vt->m03) {
        node->vt->m03(node, 1);
    }
    s32 index = self->count;
    self->items[index] = node;
    self->count = index + 1;
    if (node->vt->m06) {
        node->vt->m06(node);
    }
}

void func_001E9570(ElementStack* g)
{
    ScreenElement* item = g->items[--g->count];
    if (item->vt->m03) item->vt->m03(item, 0);
    if (item->vt->m07) item->vt->m07(item);
    if (g->count >= 2) {
        ScreenElement* other = g->items[g->count - 1];
        if (other->vt->m03) other->vt->m03(other, 1);
    }
    if (IsStreamVoiceLocked()) {
        if (g->count == 1) func_001BEA50();
    }
}

void func_001E9648(void)
{
    DrawScreenElements();
}

void func_001E9668(void)
{
    func_001AA110();
}

void func_001E9688(ElementStack* self)
{
    while (self->count >= 2) {
        PopStackElement(self);
    }
    s32 one = 1;
    self->resumeState = -1;
    u8* base = (u8*)&g_padRecord;
    self->count = one;
    self->items[0] = 0;
    SetPadPatternState(*(void**)(base + 0xBC), 3);
    ResetScreenElements();
}

void func_001E96F8(ElementStack* self, s32 state)
{
    if (state == 3) {
        s32 t = self->resumeState;
        if (t != -1) state = t;
    }
    if (self->state != state) {
        if (self->state != 0) {
            if (self->state == 1) {
                D_00272930.vt->m15(&D_00272930);
                D_00272B98.vt->m15(&D_00272B98);
                ReleasePadSelectFlag(g_currentWorld);
            }
        }
        self->state = state;
    self->stateTime = g_elapsedTime[0];
    switch (state) {
    case 0:
        if (g_memoryCard.displayMode == 0) SetMemoryCardDisplayMode(&g_memoryCard, 1);
        SetScreenFadeMode(&g_screenFade, 0);
        ApplyStackTimeScale(self, 1.0f);
        break;
    case 1:
        ApplyStackTimeScale(self, 1.0f);
        D_00272930.vt->m14(&D_00272930);
        D_00272B98.vt->m14(&D_00272B98);
        AcquirePadSelectFlag(g_currentWorld);
        func_001A7E70();
        break;
    case 2:
        ApplyStackTimeScale(self, 1.0f);
        break;
    case 3:
        ApplyStackTimeScale(self, 1.0f);
        g_previousSoundLevel = -100;
        break;
    case 5:
    case 7:
        ApplyStackTimeScale(self, 0.0f);
        break;
    case 8:
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
        break;
    }
    }
}

void func_001E98E8(float x)
{
    if (0.0f < g_gameTime[0]) {
        float t = (1.0f - x) * 0.6f + x;
        SetVolumeChannelFactor(4, 1, t);
        SetVolumeChannelFactor(4, 0, t);
    }
    SetGameClockScale(x);
}

s32 func_001E9970(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (func_001DDA80((World*)g_currentWorld) != 0) goto fail;
    if (g_pauseMenuElement.open != 0 && g_pauseMenuElement.page != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode != 0) goto fail;
    if (D_00270458 == 2) goto fail;
    if (D_00270458 == 1) goto fail;
    if (D_00270458 != 4) goto ok;
fail:
    return 0;
ok:
    return 1;
}

s32 func_001E9A10(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (g_pauseMenuElement.open != 0) goto fail;
    if (g_pauseMenuElement.mode != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

s32 func_001E9A68(void)
{
    s32 m;
    if (g_screenFade.mode != 0) goto fail;
    if (g_pauseMenuElement.open != 0) goto fail;
    if (g_pauseMenuElement.mode != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode != 0) goto fail;
    m = D_00270458;
    if (m == 4) goto fail;
    if (m != 1) goto ok;
fail:
    return 0;
ok:
    return 1;
}

s32 func_001E9AD8(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (g_pauseMenuElement.open != 0) goto fail;
    if (g_pauseMenuElement.mode != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

void func_001E9B30(void) {
    if (D_00275C34 == 0) {
        if (g_memoryChecksumRemaining == 0) {
            g_memoryChecksumCursor = (u32*)0x100004;
            g_memoryChecksumRemaining = (s32)D_00148D7C;
            g_memoryChecksumValue = 0xFFFFFFFF;
        }
    }
    if (g_memoryChecksumRemaining == 0) {
        return;
    }
    u32* p = g_memoryChecksumCursor;
    s32 cnt = g_memoryChecksumRemaining;
    u32 h = g_memoryChecksumValue;
    for (s32 i = 0; i < 32 && cnt > 0; i++) {
        u32 w = *p;
        cnt -= 4;
        p++;
        h = Crc_1E9B30::Step(h, w);
        h = Crc_1E9B30::Step(h, w >> 8);
        h = Crc_1E9B30::Step(h, w >> 16);
        h = Crc_1E9B30::Step(h, w >> 24);
    }
    g_memoryChecksumCursor = p;
    g_memoryChecksumValue = h;
    g_memoryChecksumRemaining = cnt;
    if (cnt == 0 && h != 0) {
        D_00275C34 = 1;
    }
}

void func_001E9C78(World* self, f32 dt)
{
    StepMemoryChecksum();
    Holder_1E9C78* h = GetActiveSwitchedCollider();
    if (h != 0) {
        Vt_1E9C78* vt = h->vt;
        if (vt->fn134 != 0) {
            u8* a;
            if ((*(s32*)&D_00262C68) & 2)
                a = (u8*)&g_padRecord;
            else
                a = ((u8*)&g_blankPadRecord);
            vt->fn134(h, dt, a);
        }
    }
    func_0015FF58(self);
    {
        Iter_1E9C78 it;
        Begin_1E9C78::Of(&it, (List01*)&self->list60);
        for (u8* n = Next_1E9C78::Of(&it); n != 0; n = Next_1E9C78::Of(&it)) {
            func_00124EE8(n, dt);
        }
        End_1E9C78::Of(&it);
    }
    {
        Iter_1E9C78 it;
        Begin_1E9C78::Of(&it, (List01*)&self->f1B64);
        for (u8* n = Next_1E9C78::Of(&it); n != 0; n = Next_1E9C78::Of(&it)) {
            func_0012EBD8(n, dt);
        }
        End_1E9C78::Of(&it);
    }
    {
        Iter_1E9C78 it;
        Begin_1E9C78::Of(&it, (List01*)&self->f1C24);
        for (u8* n = Next_1E9C78::Of(&it); n != 0; n = Next_1E9C78::Of(&it)) {
            StepObjectLevelRamp(n, dt);
        }
        End_1E9C78::Of(&it);
    }
    DispatchDelayedMessages(self);
    UpdateSoundEmitters();
    RunQueuedCalls(self);
}

void func_001E9E30(World* self)
{
    ListFrame frame;
    Collider* s1 = (Collider*)self->list6C.head;
    if (s1 != 0) {
        do {
            Collider* s0 = (Collider*)s1->parts.head;
            if (s0 != 0) {
                do {
                    u64 bit = (u64)1 << 53;
                    if ((s0->flags538 & bit) == 0) {
                        ((Desc03*)s0->desc)->m44(s0);
                    }
                    s0->flags538 &= ~bit;
                    s0 = (Collider*)s0->link2E4.next;
                } while (s0 != 0);
            }
            s1 = (Collider*)s1->link414.next;
        } while (s1 != 0);
    }
}

void func_001E9EE8(World* self, f32 dt)
{
    if (dt == 0.0f) return;
    Iter_1E9EE8 it;
    Begin_1E9EE8::Of(&it, &self->list78);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) func_00124EE8(obj, dt);
    End_1E9EE8::Of(&it);
    Begin_1E9EE8::Of(&it, (List01*)&self->f1B70);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) func_0012EBD8(obj, dt);
    End_1E9EE8::Of(&it);
    Begin_1E9EE8::Of(&it, (List01*)&self->f1C30);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) StepObjectLevelRamp(obj, dt);
    End_1E9EE8::Of(&it);
    Begin_1E9EE8::Of(&it, &self->list78);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) obj->vtbl->update(obj, 0, dt);
    End_1E9EE8::Of(&it);
    RunQueuedCalls(self);
}

void func_001EA0A8(World* self, f32 x)
{
    World* o = self;
    f32 a = o->f234C;
    f32 b = o->f2350;
    if (b < a) {
        o->f234C = ApproachValueWithRamp(D_00275C18, 0, a, b, x);
    } else if (a < b) {
        o->f234C = ApproachValueWithRamp(D_00275C28, 0, a, b, x);
    }
}

void func_001EA118(World* self)
{
    Iter_1EA118 it;
    GameClock* clock = &g_gameClock;
    UpdateWorldStepLists(self, clock->step);
    if (clock->dt != 0.0f) {
        UpdateWorldDeltaLists(self, clock->dt);
        UpdateUnflaggedParts(self);
        func_00138C00(self, 0);
        ProcessColliderGroups(self, 1, clock->dt);
        Begin_1EA118::Of(&it, &self->list6C);
        for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
            if (obj->vtable->update != 0) {
                obj->vtable->update(obj, clock->dt);
            }
        }
        g_activeListFrames = (ListFrame*)it.saved;
        func_00138C00(self, 1);
        ProcessColliderGroups(self, 6, g_gameClock.dt);
        Begin_1EA118::Of(&it, &self->list60);
        for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
            if (obj->tries < 2) {
                if (func_00129D70(obj) != 0) {
                    obj->tries++;
                } else {
                    func_00129DF8(obj);
                }
            }
        }
        g_activeListFrames = (ListFrame*)it.saved;
        Begin_1EA118::Of(&it, &self->list6C);
        for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
            obj->vtable->post(obj);
            if (obj->flags & 0x8000000000000000ULL) {
                UpdateTouchingParts(obj);
            }
        }
        g_activeListFrames = (ListFrame*)it.saved;
        func_001DBEC8(self, g_gameClock.dt);
        RunQueuedCalls(self);
        StepAnimators(g_gameClock.dt);
    }
    func_001DDC40(self);
    Begin_1EA118::Of(&it, &self->list1B7C);
    for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
        ReleaseWorldListEntry(obj);
    }
    g_activeListFrames = (ListFrame*)it.saved;
    UpdateCamera(g_camera, 1, g_gameClock.dt);
    StepWorldValueTowardTarget(self, g_gameClock.step);
}

f32 func_001EA408(f32 a)
{
    f32 r = a;
    if (a < -3.1415927f || a > 3.1415927f) {
        r = WrapModulo(a + 3.1415927f, 6.2831855f) - 3.1415927f;
    }
    return r;
}

f32 func_001EA480(f32 a, f32 b)
{
    f32 r = a;
    if (b < r) {
        r = b;
    } else {
        b = -b;
        if (r < b) {
            r = b;
        }
    }
    return r;
}

f32 func_001EA4B8(Coeffs_1EA4B8* k, f32* out, f32 x, f32 y, f32 z)
{
    f32 roots[4];
    s32 flip = 0;
    f32 d = x - y;
    f32 c = z;
    f32 half;
    f32 t;
    f32 res;
    f32 r;
    if (d < 0.0f) {
        flip = 1;
        d = -d;
    }
    half = (k->p1 + k->p0) * k->p2 * 0.5f;
    if (half <= d) {
        f32 u = (d - half) / k->p0;
        if (c <= u) {
            res = d - k->p0 * c;
            t = -k->p0;
            goto tail;
        }
        c = c - u;
        d = half;
    }
    SolveQuadratic(roots, (k->p0 - k->p1) / (k->p2 + k->p2), k->p1, -d);
    r = roots[0] - c;
    if (0.0f < r) {
        res = (k->p0 - k->p1) * r * r / (k->p2 + k->p2) + k->p1 * r;
        t = -(k->p1 + (k->p0 - k->p1) * r / k->p2);
    } else {
        t = -k->p1;
        res = 0.0f;
    }
tail:
    if (flip) {
        res = y - res;
        if (out) {
            *out = -t;
        }
    } else {
        res = res + y;
        if (out) {
            *out = t;
        }
    }
    return res;
}

f32 func_001EA620(f32 a, f32 b, f32 c, f32 d, void* self, f32* out)
{
    Obj_1EA620* o = (Obj_1EA620*)self;
    f32 tmp;
    f32 res = ApproachValueWithRamp(a, c, d, self, &tmp);
    f32 k = o->f0C;
    if (0.0f < k) {
        f32 hi = b + k * d;
        f32 lo = b - k * d;
        if (hi < tmp) {
            tmp = hi;
            res = a + b * d + (k * (d * 0.5f)) * d;
        } else if (tmp < lo) {
            tmp = lo;
            res = a + b * d - (k * (d * 0.5f)) * d;
        }
    }
    if (out != 0) *out = tmp;
    return res;
}

LINKER_REMNANT(func_001EA720);

f32 func_001EA728(f32 a, f32 b, f32 c, void* self, f32* out)
{
    f32 t = WrapAngle(b - a);
    f32 r = ApproachValueWithRamp(0.0f, t, c, self, out);
    return WrapAngle(a + r);
}

f32 func_001EA798(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1)
{
    f32 t = WrapAngle(f14 - f12);
    f32 r = ApproachValueClampingVelocity(0.0f, f13, t, f15, self, a1);
    return WrapAngle(f12 + r);
}

ASM_FUNC(func_001EA818);

ASM_FUNC(func_001EA918);

s32 func_001EAA70(s32 a, s32 b)
{
    if (a == b) {
        return a;
    }
    s32 r = (s32)(u32)func_001F6708();
    s32 span = b - a + 1;
    r = r % 0x95675;
    r = r % span;
    return a + r;
}

f32 func_001EAAE0(f32 a, f32 b)
{
    f32 r;
    if (a != b) {
        s32 n = func_001F6708();
        r = a + (b - a) * (f32)n * 0.0000000004656613f;
    } else {
        r = a;
    }
    return r;
}

f32 func_001EAB48(f32 mean, f32 deviation, f32 limit)
{
    f32 x;
    f32 y;
    f32 r;
    do {
        x = RandomFloatInRange(-1.0f, 1.0f);
        y = RandomFloatInRange(-1.0f, 1.0f);
        r = x * x + y * y;
    } while (r > 1.0f || r == 0.0f);
    f32 v = mean + deviation * y * Fpu::Sqrt(func_002059E0(r) * -2.0f / r);
    if (limit != 0.0f) {
        f32 lo = mean - limit;
        f32 hi = mean + limit;
        if (v < lo) {
            v = lo;
        } else if (hi < v) {
            v = hi;
        }
    }
    return v;
}

ASM_FUNC(func_001EAC68);

s32 func_001EACA0(f32* roots, f32 a, f32 b, f32 c)
{
    f32 disc = b * b - a * (4.0f * c);
    if (disc < 0.0f) {
        return 0;
    }
    a = a + a;
    disc = Fpu::Sqrt(disc) / a;
    b = b / a;
    if (__builtin_fabsf(disc) < 0.0001f) {
        roots[0] = -b;
        return 1;
    }
    roots[0] = -b + disc;
    roots[1] = -b - disc;
    return 2;
}

void func_001EAD30(Vec3_1EAD30* in, Vec3_1EAD30* out, f32 s, f32 t)
{
    out->z = in->z * s * s;
    out->y = (in->z + in->z) * s * t + in->y * s;
    out->x = (in->z * t * t + in->y * t) + in->x;
}

void func_001EAD88(f32* sinOut, f32* cosOut, f32 angle)
{
    f32 t = (angle + 1.5707964f) * 0.31830987f;
    s32 n = (s32)t;
    if (t < 0.0f) {
        n--;
    }
    angle -= (f32)n * 3.1415927f;
    if (n & 1) {
        angle = -angle;
    }
    f32 x2 = angle * angle;
    f32 s = angle;
    angle *= x2;
    s += angle * -0.166666567f;
    angle *= x2;
    s += angle * 0.00833302550f;
    angle *= x2;
    s += angle * -0.000198074136f;
    angle *= x2;
    s += angle * 2.60188699e-06f;
    f32 c = Fpu::Sqrt(1.0f - s * s);
    if (n & 1) {
        *cosOut = -c;
    } else {
        *cosOut = c;
    }
    *sinOut = s;
}

double func_001EAE78(double x)
{
    Bits_1EAE78 v;
    v.d = x;
    s32 e = ((u16)(v.u >> 52) & 0x7FF) - 0x3FF;
    if (e < 0) {
        return 0.0;
    }
    if (e < 0x34) {
        u64 frac = ((u64)1 << (0x34 - e)) - 1;
        u64 mant = v.u & ((u64)-1 >> 12);
        if ((mant & frac) == frac) {
            v.u = (v.u & ((u64)0xFFF0 << 48)) | (mant & ~frac & ((u64)-1 >> 12));
            x = v.d;
            x = func_001FCD20(x, 1.0);
        } else {
            v.u = (v.u & ((u64)0xFFF0 << 48)) | (mant & ~frac & ((u64)-1 >> 12));
            x = v.d;
        }
    }
    return x;
}

f32 func_001EAF28(f32 x)
{
    f32 buf[2];
    u64* qp = (u64*)buf;
    buf[0] = x;
    u64 bits = *qp;
    u32 ex = (u32)((s64)(bits << 9) >> 32) & 0xFF;
    s32 e = (s32)ex - 0x7F;
    if (e < 0)
        return 0.0f;
    if (e < 0x17) {
        s32 mask = (s32)(((u64)1 << (0x17 - e)) - 1);
        s32 frac = *(s32*)buf & 0x7FFFFF;
        if ((frac & mask) == mask) {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
            buf[0] = buf[0] + 1.0f;
        } else {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
        }
    }
    return buf[0];
}

f32 func_001EAFE0(f32 x, f32 y)
{
    f32 r = func_002058A0(x);
    if (r < 0.0f) {
        r += y;
    }
    return r;
}

void func_001EB018(f32* a0, f32 x, f32 y, f32 z, f32 w)
{
    f32 p = w - x;
    f32 q = y - x;
    a0[0] = x;
    f32 r = p / z - q;
    r = r / (z - 1.0f);
    a0[2] = r;
    a0[1] = q - r;
}

s32 func_001EB050(ValueRange* span, f32 x)
{
    s32 inside = 0;
    if (span->lo < x) {
        if (x < span->hi) {
            inside = 1;
        }
    }
    return inside;
}

s32 func_001EB080(s32 count, ValueRange* spans, f32 x)
{
    for (s32 i = 0; i < count; i++) {
        if (IsInsideRange(&spans[i], x)) {
            return 1;
        }
    }
    return 0;
}

f32 func_001EB0F8(ValueRange* span, f32 x)
{
    if (x < span->lo) {
        return span->lo;
    }
    if (span->hi < x) {
        return span->hi;
    }
    return x;
}

s32 func_001EB128(f32* a, f32* b)
{
    f32 x = *a;
    f32 y = *b;
    if (y < x) return 1;
    if (x < y) return -1;
    return 0;
}

void func_001EB160(void)
{
}

ASM_FUNC(func_001EB168);

LINKER_REMNANT(func_001EB458);

void func_001EB460(BeatPressCollider* self)
{
    InitSwitchedCollider(self);
    f32 t = g_currentEntry->dt;
    f32 x = D_00275C80[0] + t * (D_00275C80[1] + t * D_00275C80[2]);
    f32 lo = g_unitRange.lo;
    f32 hi = g_unitRange.hi;
    f32 c;
    if (x < lo) {
        c = lo;
    } else if (hi < x) {
        c = hi;
    } else {
        c = x;
    }
    self->f684 = (1.0f - c) * D_00275C70[0] + c * D_00275C70[1];
}

void func_001EB518(BeatPressCollider* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, D_00275C90);
}

void func_001EB550(BeatPressCollider* a0)
{
    a0->blk580 = g_player->blk580;
    a0->f604 = g_player->f604;
}

void func_001EB598(BeatPressCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 4, D_00275CA0);
    self->f614 = CreateStateWalker(self->f610, self, 0x4CA, 1);
    AppendQueuedCall(self->world, (void*)func_001EB550, self, 0, 0);
}

void func_001EB608(BeatPressCollider* self, void* p)
{
    HandleSwitchedColliderActivation(self);
    Inner_1EB608* r = (Inner_1EB608*)FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
    if (p != 0) {
        SetStateWalkerTarget(self->f614, 0x4CB);
        r->c3C = self;
        self->f68C = r;
    } else {
        SetStateWalkerTarget(self->f614, 0x4CA);
        *(f32*)((u8*)g_player + 0x26D0) = 2.0f;
    }
}

ASM_FUNC(func_001EB698);

void func_001EB748(BeatPressCollider* self, In_1EB748* in)
{
    if (self->f67C != 0 && g_player != 0) {
        Vec4U pos;
        Mat3U mat;
        GetObjectWorldPosition(self->f67C, &pos);
        GetObjectWorldRotation(self->f67C, &mat);
        ((GFn_1EB748*)g_player->desc)[0x84 / 4](g_player, &pos);
        ((GFn_1EB748*)g_player->desc)[0x88 / 4](g_player, &mat);
        ((Fn_1EB748*)self->desc)[0x84 / 4](self, &pos);
        ((Fn_1EB748*)self->desc)[0x88 / 4](self, &mat);
    }
    if (self->f680 != 0) {
        u32 f = in->fAA;
        if (f & 0xF0) {
            s32 dir;
            s32 ok;
            f32 at;
            if (f & 0x80) {
                dir = 0;
            } else if (f & 0x10) {
                dir = 1;
            } else if (f & 0x20) {
                dir = 2;
            } else if (f & 0x40) {
                dir = 3;
            }
            ok = 0;
            if (self->f62C < self->f630) {
                Ent1C* e = &self->f634[self->f62C];
                if (e->dir == dir) {
                    Grid_1EB748* g = ((Grid_1EB748*)self->f68C);
                    at = (f32)g->row * 4.0f + g->base;
                    if (__builtin_fabsf(e->t - at) < self->f684 * 0.5f) {
                        ok = 1;
                    }
                }
            }
            if (ok) {
                self->f678 = dir;
                self->f674 = at;
            } else {
                StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
    }
    if (self->f62C < self->f630) {
        Ent1C* e = &self->f634[self->f62C];
        Grid_1EB748* g = ((Grid_1EB748*)self->f68C);
        f32 at = (f32)g->row * 4.0f + g->base;
        f32 win = self->f684;
        if (self->f678 == e->dir && __builtin_fabsf(e->t - self->f674) < win * 0.5f) {
            SetStateWalkerTarget(self->f614, D_00275CD8[self->f678]);
            StartSoundEffect(D_00275CE8[self->f678], 0, 0, 0, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0, 0);
        } else {
            if (!(at - e->t > win * 0.5f)) {
                return;
            }
            StartSoundEffect(0x51, 0, 0, 0, 30000.0f, 20000.0f, 1.5f, 0.3f, 0.0f, 0, 0);
            if (func_00160C58() == 0 && ((Fn_1EB748*)self->desc)[0x13C / 4](self, 0) == 0) {
                OwnerMessage msg;
                TempoAgent* o;
                ActivateSwitchedCollider(g_player);
                InitOwnerMessage(&msg, 0, self);
                msg.fn = func_001EB698;
                ((s32 (*)(Player*, OwnerMessage*))((GFn_1EB748*)g_player->desc)[0x140 / 4])(g_player, &msg);
                o = (TempoAgent*)FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
                func_001ED020(o);
                o->fBFC = g_gameTime[0];
                SetCachedVoiceParam(2, 1);
                goto next;
            }
            if (((Fn_1EB748*)self->desc)[0x13C / 4](self, 0) == 0) {
                List_1EB748* l;
                ((void (*)(BeatPressCollider*))((Fn_1EB748*)self->desc)[0x150 / 4])(self);
                Player* gl = g_player;
                self->f688 = 1;
                gl->f26C4 = 1;
                f32 v = g_gameTime[0];
                *(f32*)((u8*)gl + 0x26CC) = v;
                gl->f26C8 = v;
                l = ((Grid_1EB748*)self->f68C)->list;
                *(f32*)((u8*)gl + 0x26D0) = 2.0f;
                if (l != 0) {
                    s32 j = l->cur;
                    while (j < l->n) {
                        Item_1EB748* p = &l->items[j];
                        if (p->type == 3) break;
                        j++;
                    }
                    if (j < l->n) {
                        Item_1EB748* it = &l->items[j];
                        Grid_1EB748* gg = ((Grid_1EB748*)self->f68C);
                        *(f32*)((u8*)g_player + 0x26D0) = ((f32)it->a * 4.0f + it->b - ((f32)gg->row * 4.0f + gg->base)) * gg->scale;
                    }
                }
            }
        }
        if (e->dir == 3) {
            ActivateSwitchedCollider(g_player);
            BindEntryQueueToObject(self->f628, g_player);
            self->f628 = 0;
        }
    next:
        self->f62C++;
        if (self->f62C == self->f630) {
            self->f62C = 0;
            self->f630 = 0;
        }
    }
}

s32 func_001EBC88(BeatPressCollider* self)
{
    if (g_buttonCodeFlags & 1) return 1;
    if (func_001DDA80(self->world) == 0) return self->f688 != 0;
    return 1;
}

void func_001EBCD8(List_1EBCD8* list, const Entry8_1EBCD8* src)
{
    s32 n = list->count;
    list->count = n + 1;
    Entry8_1EBCD8* dst = (Entry8_1EBCD8*)((u8*)list + (n * 8 + 0x634));
    *dst = *src;
}

s32 func_001EBD08(void)
{
    return 0;
}

ASM_FUNC(func_001EBD10);

ASM_FUNC(func_001EBDD0);

void func_001EBEB0(TempoAgent* self)
{
    InitAgent(self);
    *(s32*)((u8*)self + 0xC5C) = 0x3C;
    self->fC8C = 1.0f;
    self->fC64 = 8.0f;
    self->fC70 = 0;
    self->fC78 = -1;
    self->fC74 = -1;
    self->fC60 = 8;
    *(s32*)((u8*)self + 0xC6C) = (s32)AllocateFrontMemory(0x400);
    self->world->f2358 = 1;
    StopStagedBankVoice();
    D_00275DB8 = 2;
    D_00275DBC = 0;
}

s32 func_001CA758(void* self, s32 id);
void func_001C7140(void* self);

struct Obj_1EBF40 { u8 pad[0xC10]; s32 fC10[4]; };

void func_001EBF40(Obj_1EBF40* self)
{
    func_001C7140(self);
    for (s32 i = 0; i < 4; i++) {
        self->fC10[i] = func_001CA758(self, D_00275CF8[i]);
    }
}

void func_001EBFB0(TempoAgent* self)
{
    StartAgent(self);
    func_001DDC38(self->world, self);
    ResolveObjectLinks(self, 5, D_00275D08);
    void* r = CreateStateWalker(self->fC50, 0, -1, 0);
    self->fC54 = r;
    func_001B6DF8(r, self);
    self->fC98 = 9;
    self->fC9C = CopyToFrontMemory(0x6C, D_00275D48);
    s32 i = 0;
    if (self->fC98 > 0) {
        s32 off = 0;
        do {
            Entry_1EBFB0* e = (Entry_1EBFB0*)((u8*)self->fC9C + off);
            e->c = FindFirstObjectById(self->world, 1, e->a, self);
            i++;
            off += 12;
        } while (i < self->fC98);
    }
}


void func_001EC098(void)
{
    UnregisterSwitchedCollider();
}

void func_001EC0B8(void)
{
    RegisterSwitchedCollider();
}

s32 func_001EC0D8(TempoAgent* self)
{
    s32 r[4];
    func_001B6598(self->fC54, r);
    switch (r[0]) {
    case 0x4ED:
    case 0x4F0:
    case 0x4F3:
    case 0x4F6:
        if (self->fC20 == 0) goto zero;
    yes:
        return 1;
    case 0x4EE:
    case 0x4F1:
    case 0x4F4:
    case 0x4F7:
        if (self->fC94 == 1) goto zero;
        if (self->fC94 < 2) {
            if (self->fC94 == 0) goto set;
            return 0;
        }
        if (self->fC94 == 2) goto yes;
        return 0;
    set:
        self->fC94 = 1;
    }
zero:
    return 0;
}

s32 func_001EC188(void)
{
    return 1;
}

INCLUDE_ASM(func_001EC190);

void func_001EC380(TempoAgent* self, void* s, void* c)
{
    u8 tmp[0x50];
    void* out = c;
    if (self->f724 == 16) {
        BuildPlacedObjectTransform(self, c, tmp);
        *(s32*)(tmp + 0x44) = 0;
        out = tmp;
    }
    func_00125C90(self, s, out);
}

ASM_FUNC(func_001EC3D8);

void func_001EC478(TempoAgent* self, void* arg)
{
    s32 out;
    s32 sel;
    LeaveAgentState(self, arg);
    s32 st = self->f724;
    if (st != 0xE) {
        if (st != 0x10) {
            return;
        }
        self->fC94 = 0;
        func_001B6598(*(void**)((u8*)self + 0xC54), &out);
        switch (out) {
        case 0x4EE:
            sel = 0x4EF;
            break;
        case 0x4F1:
            sel = 0x4F2;
            break;
        case 0x4F4:
            sel = 0x4F5;
            break;
        }
        SetStateWalkerTarget(*(void**)((u8*)self + 0xC54), sel);
    } else {
        self->fC94 = 0;
    }
}

void func_001EC528(TempoAgent* self)
{
    T217D_2E0* g = &g_gaugeBarElement;
    DecrementGaugeCount((u8*)&g_gaugeBarElement);
    self->fA68 = 2;
    g->fill = g->fillTarget;
}

void func_001EC570(TempoAgent* self, s32 a, s32 b)
{
    s32 r[3];
    switch (self->f724) {
    case 0xE:
        func_001B6598(self->fC54, &r[0]);
        switch (r[0]) {
        case 0x4ED:
        case 0x4F0:
        case 0x4F3:
        case 0x4F6:
            b = self->fC20;
            self->fC20 = 0;
            break;
        }
        break;
    case 0x10:
        DecrementGaugeCount(&g_gaugeBarElement);
        break;
    case 0xB:
        DecrementGaugeCount(&g_gaugeBarElement);
        MarkLevelDone(3);
        StartMemoryCardSave(&g_memoryCard);
        break;
    }
    EnterAgentState(self, a, b);
    switch (self->f724) {
    case 14: {
        func_001B6598(self->fC54, &r[1]);
        f32 q;
        switch (r[1]) {
        case 0x4EE:
            q = 0.083333336f;
            ((Sub_1EC570*)self->f7E0)->f18 = ((Sub_1EC570*)self->f7E0)->inner->f34 / (self->fC88 + self->fC88);
            break;
        case 0x4F1:
        case 0x4F4:
        case 0x4F7:
            q = 0.083333336f;
            ((Sub_1EC570*)self->f7E0)->f18 = ((Sub_1EC570*)self->f7E0)->inner->f34 / (self->fC88 * 4.0f);
            break;
        default:
            return;
        }
        ((Sub_1EC570*)self->f7E0)->f14 = q;
        break;
    }
    case 2:
    case 13: {
        s32 n = 4;
        func_001B6598(self->fC54, &r[2]);
        if (r[2] < 0x4EF) {
            if (r[2] >= 0x4EC) n = 2;
        }
        func_001ED090(self, ((Sub_1EC570*)self->f7E0), n);
        if (n == 2) ((Sub_1EC570*)self->f7E0)->f14 = ((Sub_1EC570*)self->f7E0)->inner->f34 * (self->fC7C / (f32)n);
        else ((Sub_1EC570*)self->f7E0)->f14 = ((Sub_1EC570*)self->f7E0)->inner->f34 * (self->fC7C / (f32)n);
        break;
    }
    case 11:
    case 16:
        self->fC04 = 0;
        break;
    }
}

INCLUDE_ASM(func_001EC7A8);

INCLUDE_RODATA(jtbl_0024E740);
ASM_FUNC(func_001EC828);

void func_001ECB18(Self_1ECB18* self)
{
    f32 den = self->fC84 - (*(f32*)&g_gameTime);
    for (s32 k = 0; k < self->fC68; k++) {
        Ent_1ECB18* e = &self->fC6C[k];
        Obj_1ECB18* o = e->f0;
        f32 len = o->f8->f34;
        f32 start = o->f14;
        f32 t = len / (f32)e->f4 * (f32)((self->fC74 + 1) % e->f4);
        if (t <= start)
            t += len;
        o->f18 = (t - start) / den;
    }

}

void func_001ECBC8(TempoAgent* self)
{
    Timeline* sub;
    s32 code;

    UpdateAgent(self);
    if (D_00275DB8 == 2) {
        if (self->fC88 != self->fC8C) {
            self->fC88 = self->fC8C;
            self->fC64 = self->fC8C * (f32)self->fC60;
        }
        sub = self->fC34;
        self->fC84 = g_gameClock.time + self->fC88;
        self->fC80 = g_gameClock.time;
        self->fC70 = 0;
        self->fC78 = 0;
        self->fC74 = 0;
        if (sub != 0) {
            self->fC34 = 0;
            self->fC38 = sub;
            func_001ED1D8(sub);
        }
        D_00275DB8 = 0;
    }
    if (self->fC84 <= g_gameClock.time) {
        s32 a = self->fC74 + 1;
        s32 b = self->fC78 + 1;
        self->fC80 = self->fC84;
        self->fC74 = a;
        self->fC78 = b;
        if (b >= 4) {
            self->fC78 = 0;
            self->fC70 = self->fC70 + 1;
            if (self->fC88 != self->fC8C) {
                self->fC88 = self->fC8C;
                self->fC64 = self->fC8C * (f32)self->fC60;
            }
        }
        if (self->fC94 == 1) {
            func_001B6598(((Dev_1ECBC8*)self->fC54), &code);
            if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) self->fC94 = 2;
        }
        self->fC84 = self->fC84 + self->fC88;
    }
    self->fC7C = (f32)self->fC78 + (g_gameClock.time - self->fC80) / self->fC88;
    if (self->fC38 != 0) RunTimelineEntries(self->fC38);
    if (D_00275DB8 == 1) {
        RefreshCachedVoiceParam(1, 0);
        if (GetCachedVoiceParam(1) == D_00275DBC) D_00275DB8 = 2;
    }
    AppendQueuedCall(((Dev_1ECBC8*)self->world), func_001ECB18, self, 0, 0);
}

void func_001ECDF8(TempoAgent* self)
{
    s32 code;
    func_001B6598(self->fC54, &code);
    s32 obj = 0;
    if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) {
        obj = AreMenusAndFadeClear();
    }
    if (obj) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

void func_001ECE98(TempoAgent* self)
{
    s32 loc[4];
    s32 v = self->f724;
    if (v >= 14) goto tail;
    if (v < 12) goto tail;
    {
        void* q = self->fC48;
        if (q != 0) {
            GetObjectWorldPosition(q, loc);
            func_001C8418(self, loc);
        } else {
            func_001C8418(self, (u8*)self + 0x140);
        }
    }
    return;
tail:
    UpdateAgentGoal(self);
}

INCLUDE_RODATA(jtbl_0024E780);
ASM_FUNC(func_001ECF10);

void func_001ED018(TempoAgent* self, s32 value)
{
    self->fC34 = (Timeline*)value;
}

void func_001ED020(TempoAgent* self)
{
    func_001ED210(self->fC38);
    self->fC38 = 0;
}

void func_001ED050(TempoAgent* self, s32 v)
{
    self->fC5C = v;
    self->fC8C = 60.0f / (f32)v;
}

void func_001ED070(TempoAgent* self, s32 v)
{
    self->fC60 = v;
    self->fC64 = self->fC88 * (f32)v;
}

void func_001ED090(TempoAgent* self, void* a, s32 b)
{
    Entry_1ED090* e = &((Entry_1ED090*)self->fC6C)[self->fC68++];
    e->b = b;
    e->a = a;
    func_0012F810(a, self);
}

void func_001ED0D8(TempoAgent* self, s32 key)
{
    s32 i = 0;
    if (self->fC68 > 0) {
        Entry_1ED0D8* p = (Entry_1ED0D8*)self->fC6C;
        while (p->key != key) {
            i++;
            if (i >= self->fC68)
                return;
            p++;
        }
        if (i < self->fC68) {
            Entry_1ED0D8* e = (Entry_1ED0D8*)self->fC6C + i;
            CopyMemory(e, e + 1, (self->fC68 - i - 1) * 8);
            self->fC68 = self->fC68 - 1;
        }
    }
}

void func_001ED168(Timeline* self)
{
    InitObject(self);
    self->buffer = AllocateFrontMemory(0xC00);
}

void func_001ED198(Timeline* self)
{
    StartObject();
    self->found = FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
}

void func_001ED1D8(Obj_1ED1D8* self)
{
    self->f3C = 0;
    self->f44 = self->f40->c70;
    TriggerScriptEvent(self, 0x1A, 0, 0);
}

void func_001ED210(Timeline* self)
{
    s32 n;
    TriggerScriptEvent(self, 0x1C, 0, 0);
    n = 5;
    RunTimelineEntry(self, &n);
    if (((Inner_1ED210*)self->found)->c3C) {
        n = 3;
        RunTimelineEntry(self, &n);
    }
}

void func_001ED278(Timeline* self)
{
    Entry90* e;
    s32 v;
    while (self->index < self->f34 && (e = self->Cur(), v = e->f4 + self->f44, !(((Inner_1ED278*)self->found)->fC70 < v))) {
        if (v == ((Inner_1ED278*)self->found)->fC70 && ((Inner_1ED278*)self->found)->fC7C < e->f8) return;
        RunTimelineEntry(self, e);
        self->index++;
    }
}

void func_001ED318(Timeline* self, Msg_1ED318* msg)
{
    switch (msg->kind) {
    case 0:
        func_001EC7A8((Inner_1ED318*)self->found);
        break;
    case 1: {
        s32* loc = &msg->f0C;
        TriggerScriptEvent(self, 0x1B, 1, (s32*)&loc);
        break;
    }
    case 2:
        ((Inner_1ED318*)self->found)->fC3C->f680 = 1;
        D_00273C50.vt->m16(&D_00273C50, 2);
        ResetPadStepRepeat(&g_padRecord);
        StartSoundEffect(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, 0.5f, 0.0f, 0, 0);
        break;
    case 3:
        ((Inner_1ED318*)self->found)->fC3C->f680 = 0;
        ((Inner_1ED318*)self->found)->fC3C->f688 = 0;
        D_00273C50.vt->m16(&D_00273C50, 0);
        break;
    case 4:
        ((Inner_1ED318*)self->found)->fC4C = 1;
        D_002739F0.vt->m16(&D_002739F0, 2);
        StartSoundEffect(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, -0.25f, 0.0f, 0, 0);
        break;
    case 5:
        ((Inner_1ED318*)self->found)->fC4C = 0;
        D_002739F0.vt->m16(&D_002739F0, 0);
        break;
    }
}

void* func_001ED4C8(Timeline* self, s32 a, s32 b, f32 c)
{
    if (self->f34 >= 0xC0) return D_00625760;
    Entry_1ED4C8* e = (Entry_1ED4C8*)((u8*)self->buffer + self->f34 * 16);
    self->f34 = self->f34 + 1;
    (void)func_001F5C0C(e, 0, 16);
    e->f00 = a;
    e->f04 = b;
    e->f08 = c;
    return e;
}

void func_001ED558(void* self, s32 p, s32 val)
{
    AppendTimelineEntry(self, 0, p)->fC = val;
}

void func_001ED588(void* self, s32 p, s32 val)
{
    AppendTimelineEntry(self, 1, p)->fC = val;
}

void func_001ED5B8(void* self, s32 p)
{
    AppendTimelineEntry(self, 2, p);
}

void func_001ED5D8(void* self, s32 p)
{
    AppendTimelineEntry(self, 3, p);
}

void func_001ED5F8(void* self, s32 p)
{
    AppendTimelineEntry(self, 4, p);
}

void func_001ED618(void* self, s32 p)
{
    AppendTimelineEntry(self, 5, p);
}

ASM_FUNC(func_001ED638);

void func_001ED650(Out_1ED650* out, f32 unused, f32 scale, f32 z)
{
    Pair_1ED650 p;
    ComputeSinCos(&p.a, &p.b);
    out->x = p.b * scale;
    out->y = p.a * scale;
    out->z = z;
}

void func_001ED6B0(Out_1ED6B0* out, f32 first, f32 second, f32 scale)
{
    f32 t[4];
    ComputeSinCos(first, &t[0], &t[1]);
    ComputeSinCos(second, &t[2], &t[3]);
    out->x = t[3] * t[1] * scale;
    out->y = t[3] * t[0] * scale;
    out->z = t[2] * scale;
}

ASM_FUNC(func_001ED738);

ASM_FUNC(func_001ED780);

ASM_FUNC(func_001ED840);

LINKER_REMNANT(func_001ED900);

ASM_FUNC(func_001ED908);

ASM_FUNC(func_001EDA80);

ASM_FUNC(func_001EDC08);

void func_001EDDB0(Vec3_1EDDB0* v, f32* a1, f32* a2)
{
    if (a1)
        *a1 = WrapAngle(func_00205778(v->y, v->x));
    if (a2) {
        f32 r = Fpu::Sqrt(v->x * v->x + v->y * v->y);
        *a2 = WrapAngle(func_00205778(v->z, r));
    }
}

void func_001EDE38(Angles_1EDE38* in, Vec3_1EDE38* b, Vec3_1EDE38* out)
{
    f32 t[4];
    ComputeSinCos(in->first, &t[0], &t[1]);
    ComputeSinCos(in->second, &t[2], &t[3]);
    out->x = t[1] * t[3] * b->x - t[2] * b->y;
    out->y = t[1] * t[2] * b->x + t[3] * b->y;
    out->z = -t[0] * b->x + b->z;
}

ASM_FUNC(func_001EDEF0);

ASM_FUNC(func_001EE090);

void func_001EE290(void* self)
{
    func_001EDEF0(self);
}

ASM_FUNC(func_001EE2B0);

PacketWriter* func_001EE318(PacketWriter* self)
{
    (void)InitPacketBuffer(self);
    self->f10 = 1;
    self->vt = (const PacketWriterVt*)D_0024A0E0;
    self->f1C = 0;
    self->f20 = 0;
    return self;
}

LINKER_REMNANT(func_001EE360);

void func_001EE368(Cursor_1EE368* s, s32 target)
{
    u32 raw = (u32)s->cursor;
    s32 idx = (s32)((raw & 0xC) >> 2);
    u32* p = (u32*)raw;
    if (idx == target) goto done;
    do {
        *p = 0;
        idx = (idx + 1) % 4;
        p++;
    } while (idx != target);
done:
    s->cursor = p;
}

void func_001EE3B8(PacketWriter* s, u32 a, u32 b)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = a | 0x3000000;
    u32* q = (u32*)s->cur;
    s->cur = (u8*)(q + 1);
    *q = b | 0x2000000;
}

void func_001EE3F0(PacketWriter* s, s32 n)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = (u32)((n / 8) | 0x14000000);
}

void func_001EE420(PacketWriter* s, s32 n)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = (u32)((n / 8) | 0x15000000);
}

void func_001EE450(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x11000000;
}

void func_001EE468(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x13000000;
}

void func_001EE480(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x10000000;
}

void func_001EE498(PacketWriter* b, u32 x, u32 y)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = y | (x << 8) | 0x01000000;
}

void func_001EE4C0(PacketWriter* b, u32* src){
 u32 *p1,*p2,*p3,*p4,*p5;
 p1=(u32*)b->cur; b->cur = (u8*)(p1 + 1); *p1=0x30000000;
 p2=(u32*)b->cur; b->cur = (u8*)(p2 + 1); *p2=src[0];
 p3=(u32*)b->cur; b->cur = (u8*)(p3 + 1); *p3=src[1];
 p4=(u32*)b->cur; b->cur = (u8*)(p4 + 1); *p4=src[2];
 p5=(u32*)b->cur; b->cur = (u8*)(p5 + 1); *p5=src[3];
}

void func_001EE528(Packer_1EE528* self, s32 value)
{
    if (value != 0) {
        self->push(0x20000000);
        self->push((u32)value);
    }
    self->last = value;
}

s32 func_001EE560(PacketWriter* self, s32 a, s32 b, s32 c)
{
    u32 lo = ((u32)b << 16) | 0x6000C000u;
    u32 head = ((u32)a << 24) | lo;
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 1);
    u32 tag = head | (u32)c;
    *p = tag;
    if (self->f1C != 0) {
        *p = tag | 0x10000000;
    }
    return D_00275DD0[a] * b;
}

void func_001EE5C8(PacketWriter* s, void* unused1, s32 size, void* unused3, s32* outSize, u8** outCursor)
{
    if (size == 0) {
        if (outCursor) *outCursor = 0;
        if (outSize) *outSize = 0;
    } else {
        size = WriteVifUnpackHeader(s);
        if (outCursor) *outCursor = s->cur;
        s->cur += ((size + 3) / 4) * 4;
        if (outSize) *outSize = size;
    }
}

void func_001EE668(void* s, void* a1, s32 size, u32* src, void* a4)
{
    s32 outSize;
    u8* outCursor;
    s32 n;
    s32 rem;
    s32 full;
    s32 i;
    u32* dst;

    func_001EE5C8(s, a1, size, a4, &outSize, &outCursor);
    dst = (u32*)outCursor;
    n = (outSize + 3) >> 2;
    rem = n & 3;
    full = n - rem;
    if (rem != 0) {
        i = rem;
        do {
            *dst++ = *src++;
        } while (--i != 0);
    }
    i = 0;
    if (full > 0) {
        do {
            u32 w0 = src[0];
            u32 w1 = src[1];
            u32 w2 = src[2];
            u32 w3 = src[3];
            i += 4;
            dst[0] = w0;
            dst[1] = w1;
            dst[2] = w2;
            dst[3] = w3;
            src += 4;
            dst += 4;
        } while (i < full);
    }
}

void func_001EE718(PacketWriter* self, s32 a, s32 b, s32 c, s32 d, s32* out)
{
    if (b != 0) {
        PadPacketToQuadSlot(self, 3);
        s32 r = WriteVifUnpackHeader(self, a, b, d);
        s32 t = r + 0xF;
        s32 u = r + 0x1E;
        s32 n = (t >= 0) ? t : u;
        AddDmaRefTag(self, n >> 4, c);
        if (out != 0) {
            *out = (s32)self->f08 - 0xC;
        }
    }
}

void func_001EE7D0(PacketWriter* self, s32 n, void* buf, s32 flag)
{
    PadPacketToQuadSlot(self, 3);
    u32* p = (u32*)self->cur;
    u32 w = (u32)flag << 31;
    self->cur = (u8*)(p + 1);
    w = w | 0x50000000u;
    *p = (u32)n | w;
    func_00152CE0(self, n, (s32)buf);
}

void func_001EE850(PacketWriter* self, s32 a, s32 b, s32 c)
{
    PadPacketToQuadSlot(self, 3);
    u32* p = (u32*)self->cur;
    u32 w = (u32)c << 31;
    self->cur = (u8*)(p + 1);
    w = w | 0x50000000u;
    *p = (u32)a | w;
    AddDmaRefTag(self, a, b);
}

void func_001EE8D0(PacketWriter* a0, PacketWriter* a1) {
    u32 span = a1->curU - (u32)a1->begin;
    func_001EE7D0(a0, span >> 4, (void*)a1->begin, 0);
}

void func_001EE900(ValueListObject* self)
{
    InitObject(self);
    self->world->f1EC4 = self;
}

void func_001EE930(ValueListObject* self, void* src)
{
    s32 i;
    s32 n;

    ReadLinkedItemArray(src, &self->count34, &self->data38);
    n = ReadBufferedU16(src);
    self->valueCount = n;
    self->values = (s32*)AllocateFrontMemory(n * 4);
    for (i = 0; i < self->valueCount; i++) {
        self->values[i] = ReadBufferedU32(src);
    }
    ReadPropertyRecords(self, src);
}

s32 func_001EE9D0(Mask_1EE9D0* self, s32 bits)
{
    s32 acc;
    bits &= 0x7FFFFFFF;
    if (bits == 0) return 0;
    acc = -1;
    for (s32 i = 0; i < self->count; i++) {
        if ((bits >> i) & 1) acc &= self->table[i];
    }
    return acc | bits;
}

ASM_FUNC(func_001EEA40);

s32 func_001EEB60(ValueListObject* self, Quad_1EEB60* vec, s32* out)
{
    s32 r;
    if (self != 0 && self->data38 != 0) {
        Quad_1EEB60 q = *vec;
        *out = 0;
        r = func_001EEA40(self, self->data38, q, out);

    } else {
        r = 0x0FFFFFFF;
        *out = r;
    }
    return r;
}

ASM_FUNC(func_001EEBB0);

void func_001EEC60(AttachedSet* self)
{
    u64 bits;
    s32 one;

    InitCollider(self);
    bits = self->flags538;
    one = 0x8000;
    bits |= (u64)one << 28;
    self->flags538 = bits;
    self->f584 = 1;
    self->f588 = 1;
    self->f364 = 1.0f;
    self->f360 = 1.0f;
    SetColliderAnchors(self, 3, 0, 3, 0);
    InitTrackedNodes(&self->trackedNodes, self);
    self->trackedNodes.f04 = 3;
}

void func_001EECE0(AttachedSet* self)
{
    Link_1EECE0 fr((s32*)&self->children);
    g_activeListFrames = (ListFrame*)&fr;
    StartPlacedObject(self);
    FillTrackedNodes(&self->trackedNodes);
    self->group.items = (void**)AllocateFrontMemory(0x80);
    if (self->f278 != 0) {
        self->desc03()->m32(self);
    }
}

ASM_FUNC(func_001EED68);

void func_001EEE50(void* owner, Attach03** head)
{
    Attach03** link = head;
    Attach03* node = *head;
    Attach03* removed = 0;
    while (node != 0) {
        Collider* o = node->target;
        Attach03* next = node->nextOwn;
        if (((o->flags538 >> 59) & 1) != ((o->flags538 >> 60) & 1)) {
            if (o->flags538 & (1ULL << 59)) {
                RemoveColliderAttachment(o, node);
            } else {
                AddColliderAttachment(o, node);
            }
        }
        Collider* p = node->target;
        if (p->flags538 & (1ULL << 60)) {
            link = &node->nextOwn;
        } else {
            *link = next;
            node->nextOwn = removed;
            removed = node;
        }
        Collider* q = node->target;
        q->flags538 = q->flags538 & ~(1ULL << 60);
        q->flags538 = q->flags538 & ~(1ULL << 59);
        node = next;
    }
    ReleaseAttachRecords(owner, removed);
}

ASM_FUNC(func_001EEF90);

void func_001EF3A8(AttachedSet* self, Attach03* link)
{
    Collider* target = link->target;
    ((VFn_1EF3A8)target->desc03()->m46)(target, self);
}

void func_001EF3D8(AttachedSet* self, s32 kind, void* msg)
{
    s32 flag = 0;
    if (kind == 2) {
        if (msg == (void*)self) {
            Attach03* n = self->links;
            if (n != 0) {
                do {
                    RemoveColliderAttachment(n->target, n);
                    n = n->nextOwn;
                } while (n != 0);
            }
            flag = 1;
            ReleaseAttachRecords(self->world, self->links);
            self->links = 0;
        } else {
            Attach03** link = &self->links;
            Attach03* n = *link;
            if (n != 0) {
                if (n->target == (Collider*)msg) {
                    *link = n->nextOwn;
                } else {
                    for (;;) {
                        link = &(*link)->nextOwn;
                        n = *link;
                        if (n == 0) {
                            break;
                        }
                        if (n->target == (Collider*)msg) {
                            *link = n->nextOwn;
                            break;
                        }
                    }
                }
            }
            Msg_1EF3D8 m;
            m.self = self;
            m.obj = n->target;
            if (n != 0) {
                n->nextOwn = 0;
                flag = 1;
                RemoveColliderAttachment(n->target, n);
                ReleaseAttachRecords(self->world, n);
            }
            m.obj->desc->m0E(m.obj, 11, &m);
        }
    }
    if (flag != 0) {
        RebuildAttachedSet(self);
    }
    HandlePlacedObjectNotification(self, kind, msg);
}

void func_001EF520(AttachedSet* self)
{
    if (self->root == self) {
        AttachedGroup* s = &self->group;
        UnregisterObjectGroup(self->world, s);
        s->items[0] = self;
        s->count = 1;
        Attach03* node = self->links;
        if (node) {
            do {
                s->items[s->count++] = node->target;
                node = node->nextOwn;
            } while (node);
        }
        RegisterObjectGroup(self->world, s);
    }
}

ASM_FUNC(func_001EF5B8);

ASM_FUNC(func_001EF768);

s32 func_001EF808(AttachedSet* self)
{
    func_001F57E0(&self->trackedNodes);
    return 1;
}

void* func_001EF828(AttachedSet* self)
{
    return &self->trackedNodes;
}

void func_001EF830(AttachedSet* o)
{
    *(s32*)((u8*)&o->trackedNodes + 0x94) = 0;
}

void func_001EF838(C62* self)
{
    InitPlacedObject(self);
    self->id2D0 = -1;
    self->id2E0 = -1;
}

void func_001EF868(C62* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, D_00275E10);
    func_001EF900(self, 0);
    self->desc->m03(self);
}

void func_001EF8C0(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    UpsertKeyedEntry((u8*)self + 0x2E8, 4, (u8*)self + 0x2E4, a1, a2, a3, a4, a7);
}

void func_001EF8F8(void) {}

void func_001EF900(C62* self, s32 state)
{
    if (self->id2D0 != state) {
        if (state != 0) {
            if (state == 2)
                func_0013ECB0((Mgr_1EF900*)g_currentWorld, self->f2E4, self->f2E8, self, 1);
        } else {
            if (self->id2D0 == 2)
                func_0013ECB0((Mgr_1EF900*)g_currentWorld, self->f2E4, self->f2E8, self, 0);
        }
        Evt_1EF900 evt;
        evt.old = self->id2D0;
        evt.self = self;
        evt.cur = state;
        self->id2D0 = state;
        self->f2D4 = g_gameTime[0];
        self->desc->m0E(self, 0x16, &evt);
    }
}

void func_001EF9C8(C62* self, s32 kind, Msg62* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 5) {
        if (msg->id == self->id2DC) {
            func_001EF900(self, 0);
        }
    }
}

void* func_001EFA30(void)
{
    C62Group* p = (C62Group*)AllocateZeroedFrontMemory(48);
    p->vtbl = D_002505C0;
    return p;
}

void func_001EFA60(C62Group* self, C62* value) { u32 i = self->count; if (i < 8) { self->items[i] = value; self->count = i + 1; } }

void func_001EFA88(C62Group* self, C62* value)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (self->items[i] == value) break;
    }
    if (i < self->count) {
        Shift_1EFA88::Of(&self->items[i], &self->items[i + 1], (self->count - i) * 4 - 4);
        self->count--;
    }
}

void func_001EFB20(C62Group* s)
{
    s->scheduled = 0;
    if (s->owner != 0 && s->owner->f180 != -1 && s->items[0]->id2E0 == s->owner->f180) {
        s32 i;
        for (i = 0; i < s->count; i++) {
            if (s->items[i]->id2D0 != 1) break;
        }
        if (i >= s->count) {
            for (i = 0; i < s->count; i++) {
                func_001EF900(s->items[i], 2);
            }
            s->owner->f180 = -1;
        }
        return;
    }
    for (s32 i = 0; i < s->count; i++) {
        C62* it = s->items[i];
        if (it->id2D0 != 2) continue;
        if (it->id2DC != 0) continue;
        f32 d = g_gameClock.time - it->f2D4;
        if (it->f2D8 < d) {
            func_001EF900(it, 0);
        }
    }
}

void func_001EFC98(C62Group* self)
{
    if (self->scheduled == 0) {
        self->scheduled = 1;
        AppendQueuedCall((s32)g_currentWorld, (void*)UpdateItemTimeouts, self, -1, 0);
    }
}

LINKER_REMNANT(func_001EFCE0);

void func_001EFCE8(ScreenFade* o)
{
    o->mode = -1;
    SetScreenFadeMode(o, 0);
}

void func_001EFD10(ScreenFade* self, s32 a1)
{
    s32 s = self->mode;
    f32 t = g_gameClock.elapsed - self->modeStartTime;
    f32 thr;
    f32 r;
    switch (s) {
    case 0:
        if (RestoreFadeRequest(self, a1, 1) != 0) return;
        break;
    case 1:
        if (self->style != 2) {
            thr = 0.5f;
            if (self->style == s) thr = 1.5f;
            if (thr < t) {
                s = 2;
                func_001C0000(((self->active.flags >> 3) ^ 1) & 1, 0.0f);
            } else {
                r = t / thr;
                f32 hi = 1.0f;
                f32 lo = 0.0f;
                if (r < lo) r = lo;
                else if (hi < r) r = hi;
                self->opacity = r;
                func_001C0000(((self->active.flags >> 3) ^ 1) & 1, 1.0f - r);
            }
        }
        break;
    case 3: {
        s32 v = self->style;
        if (v != 2) {
            thr = 0.25f;
            if (v == 1) thr = 1.0f;
            if (thr < t) {
                if (v == s) {
                    self->style = 0;
                    self->modeStartTime = g_gameClock.elapsed;
                    self->opacity = 1.0f;
                } else {
                    s = 0;
                }
            } else {
                self->opacity = 1.0f - t / thr;
            }
        }
        break;
    }
    case 2:
        if (self->active.kind == 0 && g_worldLoadRequest != 0) {
        } else {
            s = 3;
        }
        break;
    }
    SetScreenFadeMode(self, s);
}

void func_001EFEE0(ScreenFade* self)
{
    if (g_currentWorld != 0 && g_screenFade.mode != 0) {
        s32 mode = self->style;
        if (mode != 1) {
            if (mode < 2) {
                if (mode == 0) goto draw;
            }
            return;
        }
        if (g_coloredTriangleSet != 0) {
        DrawColoredTriangles(g_coloredTriangleSet, self->opacity);
            return;
        }
        draw:
    f32 v = self->opacity * 255.0f;
    WriteColoredSpritePacket(0, 0, 0, (s32)v, &g_gsPacketWriter, 0.0f, 0.0f, 640.0f, 492.80002f);
    }
}

void func_001EFFA0(ScreenFade* dst, FadeRequest* args, s32 count)
{
    IdentityKey* p;
    s32 mode;

    if (dst->mode == 0) {
        if (D_0027051C != 0) {
            if (*(s32*)((u8*)D_0027051C + 0x2D0) != 2) {
                func_001DDAD0(g_currentWorld);
            }
        }
        if (args->key == 0 || Match_1EFFA0::Of(args->key)) {
            args->flags |= 8;
        } else {
            args->flags &= ~8;
        }
        dst->active = *args;
        dst->style = count;
        mode = 2;
        if (g_currentWorld != 0) {
            mode = 1;
        }
        SetScreenFadeMode(dst, mode);
    }
}


void func_001F00C0(ScreenFade* dst, Src_1F00C0* src, s32 last)
{
    s32 mid = src->mid;
    u64 lo = src->pair.lo;
    u64 hi = src->pair.hi;
    ((QuadP*)&dst->queued)->lo = lo;
    ((QuadP*)&dst->queued)->hi = hi;
    dst->queuedStyle = last;
    dst->queued.flags = mid;
}

s32 func_001F00F0(ScreenFade* self, PadRecord* o, void* param2)
{
    if (func_001DDA80(g_currentWorld) != 0 && self->queued.kind != 0 && (o->flags & 0x800) != 0) {
        ClearPadPressedBits(o, 0x800);
        *(Blk20_1F00F0*)&self->active = *(Blk20_1F00F0*)&self->queued;
        self->style = self->queuedStyle;
        FadeRequest* rr = &self->active;
        IdentityKey* kk = rr->key;
        if (kk == 0 || Same_1F00F0::Of(kk, &D_00275B04)) {
            rr->flags |= 8;
        } else {
            rr->flags &= ~8;
        }
        SetScreenFadeMode(self, (s32)param2);
        return 1;
    }
    return 0;
}

LINKER_REMNANT(func_001F0218);

void func_001F0220(ScreenFade* self, s32 mode)
{
    if (self->mode == mode) goto L0410;
    if (self->mode == 2) {
        if (D_0026FA68 != 0) {
            SetWarpPageMode(D_0026FA68, 0);
        }
    }
    if (mode == 1) goto L02E0;
    if (mode < 2) {
        if (mode == 0) {
            self->opacityWord = 0;
            goto L0400;
        }
        self->mode = mode;
        goto L0404;
    }
    if (mode == 2) goto L02A0;
    if (mode == 3) goto L0374;
    self->mode = mode;
    goto L0404;

L02A0:
    if (self->active.kind != 0) {
        FadeRequest* q = &self->active;
        QueueWorldLoad((u8*)&g_worldLoadRequest, (s32)q->key, q->f08, q->f0C, q->flags);
    }
    self->active.kind = 0;
    self->opacity = 1.0f;
    self->queued.kind = 0;
    goto L0400;

L02E0:
    {
        s32 v = self->style;
        if (v == 2) goto L0300;
        if (v == 3) goto L0354;
        goto L0364;
    }

L0300:
    {
        s32 v = GetEntryIdByKey((s32)self->active.key);
        s32 a3 = v >> 8;
        s32 a2 = v & 0xFF;
        if (D_0026FA68 == 0) goto L034C;
        if (v == -1) goto L034C;
        s32 a1 = 10;
        if (a3 != 0) a1 = a2;
        SetWarpCursor(D_0026FA68, a1, 3);
        ShowCountedScreenElement(g_currentWorld);
        goto L0364;
    }

L034C:
    self->style = 0;
    goto L0364;

L0354:
    mode = 2;
    goto L02A0;

L0364:
    SetElementStackState(g_elementStack, 8);
    self->mode = mode;
    goto L0404;

L0374:
    {
        s32 a = self->style;
        if (a == 2) goto L038C;
        if (a == mode) goto L03EC;
        self->mode = mode;
        goto L0404;
    }

L038C:
    {
        if (self->style == D_00275BF0[0]) {
            s32 idx = g_previousLevelIndex;
            if (idx != -1) {
                g_mapScreenList.current = g_mapScreenList.nodes[idx];
            }
        }
        if (g_mapScreenList.current != 0) {
            g_mapScreenList.current->f2E0 = 3;
            SetWarpPageMode(g_mapScreenList.current, 4);
            self->mode = mode;
            goto L0404;
        }
        self->style = 3;
        goto L0400;
    }

L03EC:
    FadeScreenToBlack(0.25f);
    self->style = 0;
    goto L0400;

L0400:
    self->mode = mode;
L0404:
    self->modeStartTime = g_elapsedTime[0];
L0410:
    return;
}

void func_001F0428(void* obj, void* value, s32 count)
{
    Msg_1F0428 m;
    m.kind = 1;
    m.obj = obj;
    m.value = value;
    m.last = 0;
    StartScreenFade(&g_screenFade, &m, count);
}

s32 func_001F0468(void)
{
    if (D_00275BF0[0] != 2) {
        return g_saveData->f19DC;
    }
    return 10;
}

s32 func_001F0490(WarpPage* self, s32 kind, s32* outA, s32* outB)
{
    s32 flag = 0;
    s32 sel;
    s32 idx;
    if (kind == 10) {
        sel = 0;
        idx = 4;
        flag = 1;
    } else {
        s32 mode = self->slot;
        s32 allowed = 1;
        if (mode == 5 && (kind == 1 || kind == 7)) {
            allowed = 0;
        }
        if (kind == 9) {
            if (allowed != 0) {
                s32 m = mode * 0x44C;
                if (*(s32*)((u8*)g_saveData + m + 0x88) & 1) {
                    s32 q = g_saveData->levels[mode].f448;
                    flag = (q & D_00275FC8[mode]) != 0;
                }
            }
        } else {
            s32 c = kind < 9;
            idx = -1;
            if (c) {
                idx = kind;
            }
            sel = mode;
            flag = 0;
            if (allowed != 0) {
                flag = *(s32*)((u8*)g_saveData + (sel * 0x44C + idx * 0x78) + 0x10) & 1;
            }
        }
    }
    if (outA != 0) {
        *outA = sel;
    }
    if (outB != 0) {
        *outB = idx;
    }
    return flag;
}

s32 func_001F0580(void* self, s32 code)
{
    s32 r;
    if (code == 9) {
        return 0;
    }
    r = IsWarpEntryAvailable(self, code, 0, 0);
    if (r == 0) {
        switch (((Obj_1F0580*)self)->mode) {
        case 1:
            if (code >= 2) {
                if (code < 6) {
                    r = IsWarpEntryAvailable(self, 1, 0, 0);
                } else if (code < 8) {
                    r = IsWarpEntryAvailable(self, 9, 0, 0);
                }
            }
            break;
        case 2:
        case 3:
        case 4:
            if (code >= 2) {
                if (code < 5) {
                    r = IsWarpEntryAvailable(self, 1, 0, 0);
                } else if (code < 8) {
                    r = IsWarpEntryAvailable(self, 9, 0, 0);
                }
            }
            break;
        }
    }
    return r;
}

void func_001F0660(WarpPage* o) {
    StartPlacedObject(o);
    o->flags = (o->flags & ~(3UL << 40)) | (1UL << 40);
    if (g_saveData->f19D8) {
        u8* t = (u8*)&g_mapScreenList;
        ((Ptr_1F0660*)(t + 0x260))->p = o;
    }
    switch (o->id) {
    case 0x1C7: o->slot = 1; break;
    case 0x1C8: o->slot = 2; break;
    case 0x1C9: o->slot = 3; break;
    case 0x1C6: o->slot = 4; break;
    case 0x1CA: o->slot = 5; break;
    default: o->slot = g_saveData->f19D8; break;
    }
    g_mapScreenList.nodes[o->slot] = o;
}

void func_001F0758(WarpPage* self)
{
    Iter_1F0758 it;
    Node_1F0758* node;
    WarpEntry* el;
    s32 i;

    PostLoadPlacedObject(self);
    ResolveObjectLinks(self, 0x34, D_00275FE0);
    Begin_1F0758::Of(&it, &self->children);
    while ((node = Next_1F0758::Of(&it)) != 0) {
        func_00182ED8(node);
    }
    el = self->entries;
    for (i = 0; i < 11; i++) {
        f32 zero = 0.0f;
        el->f28 = zero;
        el->f24 = zero;
        el->phase = RandomFloatInRange(zero, 6.2831855f);
        el->speed = RandomFloatInRange(0.5f, 0.7f);
        el++;
    }
    self->selected = -1;
    g_activeListFrames = (ListFrame*)it.saved;
}

void func_001F0878(WarpPage* self, s32 value)
{
    if (value == 10) {
        SetElementTextFromEntry(&D_0026F138, 0, 4);
    } else {
        T217D_3D0* base = &D_0026F138;
        s32 t = value < 9;
        s32 idx = t ? value : -1;
        SetElementTextFromEntry(base, self->slot, idx);
    }
    SetWarpPageSelectedEntry(self, value);
}

void func_001F08F0(s32 unused, s32 a, s32 b)
{
    D_00276250 = a;
    D_00276654 = b;
}

void func_001F0908(Obj_1F0908* self)
{
    if (D_00276250 == -1) return;
    SetScreenElementHoldTime(&D_002721D0, ((g_saveData->f19D8 << 8) | g_saveData->f19DC) == 4 ? 0.5f : 2.0f);
    D_002721D0.vt->m16(&D_002721D0, 2);
    T217D_3D0* e = &D_0026F138;
    e->pending = 0;
    e->vt->m16(e, 0);
    SetElementTextFromEntry(e, g_saveData->f19D8, g_saveData->f19DC);
    e->announce = 1;
    SetScreenElementHoldTime(e, 0.0f);
    e->vt->m16(e, 2);
    Slot_1F0908* sl = self->slots[D_00276250].s;
    if (sl != 0) {
        f32 f = 0.0f;
        if (D_00276654 == 0) f = sl->f34;
        ReplaceAnimationPlayer(sl, self, 0, self->f2F0, f, 0.0f);
    }
    if (self->tbl != 0) {
        for (s32 i = 0; i < self->tbl->count; i++) {
            Ent_1F0908* en = &self->tbl->ents[i];
            if (en->type == 10) {
                BaseObject* n = FindFirstObjectById(self->f14, 0x104, en->id, self);
                if (n != 0) n->desc->m02(n);
            }
        }
    }
    D_00276250 = -1;
}

INCLUDE_ASM(func_001F0AE0);

void func_001F0EB8(WarpPage* obj, u8* s, void* c)
{
    u8 tmp[0x50];
    Camera* p = g_camera;
    f32 keep1 = p->f1C4;
    f32 keep2 = p->f1C8;
    SnapCameraZoom(p, 1.0f);
    BuildPlacedObjectTransform(obj, c, tmp);
    BuildMatrixFromRotationAndTranslation(s + 0x40, s + 0x80, tmp);
    func_00125C90(obj, s, tmp);
    SnapCameraZoom(g_camera, keep1);
    g_camera->f1C8 = keep2;
}

void func_001F0F70(WarpPage* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind != 5) return;
    s32 v = self->mode;
    if (v == 3) goto L_three;
    if (v >= 4) goto L_ge4;
    if (v == 1) goto L_one;
    return;
L_ge4:
    if (v == 4) goto L_four;
    return;
L_one:
    SetWarpPageMode(self, self->f2E0);
    return;
L_three:
    SetScreenFadeMode(&g_screenFade, 2);
    return;
L_four:
    if ((s32)msg != self->f2EC) return;
    ScreenFade* g = &g_screenFade;
    if (g->mode == 3) {
        SetScreenFadeMode(g, 0);
    }
    SetWarpPageMode(self, 0);
}

void func_001F1050(WarpPage* self, u32 next)
{
    s32 i;
    Sub_1F1050* t;
    s32 cur = self->mode;
    if (cur == (s32)next) {
        return;
    }
    switch (cur) {
    case 1:
    case 4:
        StopSoundRecord(self->sound, 0);
        break;
    case 2:
        if (self->f560 == 0) {
            D_0026F138.vt->m15(&D_0026F138);
        }
        for (s32 k = 0; k < 11; k++) {
            self->entries[k].f28 = 0;
        }
        break;
    case 0: {
        f32 one = 1.0f;
        self->desc->m02(self);
        for (s32 n = 0; n < 11; n++) {
            WarpEntry* s = &self->entries[n];
            if (IsWarpEntryAvailable(self, n, (s32*)0, (s32*)0)) {
                s->f08 = one;
                s32 want;
                if (self->f2E0 == 3) {
                    want = GetCurrentWarpEntry();
                } else {
                    want = self->cursor;
                }
                if (n == want) {
                    s->f10 = one;
                } else {
                    s->f10 = 0;
                }
            } else {
                s->f10 = 0;
                s->f08 = 0;
            }
        }
        *(f32*)((u8*)self + 0x4DC) = *(f32*)((u8*)self + 0x33C);
        for (s32 j = 0; j <= 10; j++) {
            WarpEntry* s = &self->entries[j];
            Sub_1F1050* a = (Sub_1F1050*)s->f04;
            Sub_1F1050* b = (Sub_1F1050*)s->f0C;
            if (a) {
                a->vtbl[6](a);
                EnsureObjectWorldNode(a);
                a->f298->f8 = 0;
                a->f298->f4 = s->f08;
            }
            if (b) {
                b->vtbl[6](b);
                EnsureObjectWorldNode(b);
                b->f298->f8 = 0;
                b->f298->f4 = s->f10;
            }
        }
        break;
    }
    }
    switch (next) {
    case 1: {
        if (self->f2E0 == 3) {
            s32 ne = self->cursor != 1;
            Sub_1F1050* a;
            s32 off;
            if (ne) {
                off = self->cursor * 52;
            } else {
                off = GetCurrentWarpEntry() * 52;
            }
            a = *(Sub_1F1050**)((u8*)self + off + 0x2F8);
            if (a) {
                f32 fa = 0;
                if (ne) {
                    fa = a->f34;
                }
                ReplaceAnimationPlayer(a, self, 0, &self->f2F0, fa, 0.0f);
            }
        } else {
            Sub_1F1050* a = (Sub_1F1050*)self->entries[1].f00;
            if (a) {
                ReplaceAnimationPlayer(a, self, 0, &self->f2F0, 0.0f, 0.0f);
            }
            f32 z = 0.0f;
            SetWarpPageSelectedEntry(self, self->cursor);
            self->q540 = self->q550;
            SelectWarpPageEntry(self, self->cursor);
            SetScreenElementHoldTime(&D_0026F138, z);
            D_0026F138.vt->m14(&D_0026F138);
            StartSoundEffect(0x8A, &self->sound, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
            for (i = 0; i < 11; i++) {
                WarpEntry* s = &self->entries[i];
                s32 r = IsWarpEntryReachable(self, i);
                s->reachable = r;
                s32 v = 0;
                if (r != 0 && ((u32)(i - 2) < 6 || i == 0)) {
                    v = 1;
                }
                s->f20 = v;
                s->f24 = s->f28 = 0.0f;
            }
        }
        self->f2D8 = self->cursor;
        t = (Sub_1F1050*)self->f2E4;
        if (t != 0) {
            goto L146C;
        }
        goto Lz;
    }
    case 4: {
        if (self->f560 == 0) {
            D_0026F138.vt->m15(&D_0026F138);
            if (self->f2E0 == 2) {
                StartSoundEffect(0x8B, &self->sound, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
        func_001F0908(self);
        t = (Sub_1F1050*)self->f2E8;
        if (t == 0) {
            goto Lz;
        }
    L146C:
        ReplaceAnimationPlayer(t, self, 0, &self->f2EC, 0.0f, 1.0f);
        self->mode = next;
        goto L1550;
    }
    case 2:
        for (s32 m = 0; m < 11; m++) {
            if (m != self->selected) {
                self->entries[m].f28 = 1.0f;
            }
        }
        self->mode = next;
        goto L1550;
    case 3:
        self->f2D8 = -1;
        break;
    case 0:
        for (i = 0; i < 11; i++) {
            Sub_1F1050* a = (Sub_1F1050*)self->entries[i].f04;
            Sub_1F1050* b = (Sub_1F1050*)self->entries[i].f0C;
            if (a) {
                if (a->f298) {
                    RemoveObjectNodeFromWorld(a->f298);
                }
                a->vtbl[7](a);
            }
            if (b) {
                if (b->f298) {
                    RemoveObjectNodeFromWorld(b->f298);
                }
                b->vtbl[7](b);
            }
        }
        break;
    default:
        break;
    }
L154C:
    self->mode = next;
L1550:
    self->modeTime = g_gameClock.elapsed;
    return;
Lz:
    next = 0;
    goto L154C;
}

void func_001F1590(WarpPage* self, s32 a1, s32 a2)
{
    s32 v = self->mode;
    if (v == 2) goto L_two;
    if (v < 3) {
        if (v == 0) goto L_store;
    } else {
        if (v == 4) goto L_store;
    }
    return;
L_store:
    self->cursor = a1;
    self->f2E0 = a2;
    SetWarpPageMode(self, 1);
    return;
L_two:
    self->cursor = a1;
    if (a2 == 3) {
        SetWarpPageMode(self, 3);
    }
}

void func_001F1610(WarpPage* self)
{
    s32 v = self->mode;
    if (v < 3) {
        if (v > 0) {
            SetWarpPageMode(self, 4);
        }
    }
}

void func_001F1648(Obj_1F1648* self, s32 idx)
{
    s32 (*table)[4] = D_00276608[self->f2F4];
    if (table == 0) {
        StartSoundEffect(SOUND_1F1648_FAIL, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s32 e = table[self->f2DC][idx];
    while (e != -1 && self->ents[e].f0 == 0) {
        e = table[e][idx];
    }
    if (e != -1 && self->ents[e].f0 != 0) {
        SetWarpCursor(self, e, 2);
        StartSoundEffect(SOUND_1F1648_OK, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        StartSoundEffect(SOUND_1F1648_FAIL, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
}

ASM_FUNC(func_001F17A0);

void func_001F18B0(Obj_1F18B0* self, s32 idx) {
    u8* base = (u8*)self;
    if (*(s32*)(base + 0x534) == idx) {
        return;
    }
    Rec_1F18B0* r = *(Rec_1F18B0**)(base + idx * 0x34 + 0x30C);
    if (r != 0) {
        func_00128018(r->f18, self, (u8*)r + 0x40, (Loc_1F18B0*)(base + 0x550));
    } else {
        *(Quad16*)(base + 0x550) = *(Quad16*)&D_00248D30;
    }
    u8* arr = base + 0x320;
    u8* slot = arr + idx * 0x34;
    *(s32*)slot = 0;
    s32 old = *(s32*)(base + 0x534);
    if (old != -1) {
        *(f32*)(arr + old * 0x34) = 1.0f;
    }
    *(s32*)(base + 0x534) = idx;
}

extern const char D_0024E808[40] = "&2T&. : Back\n&2(&. : Move\n&2X&. : Warp";
void func_001F1960(T217D_0F0* self) {
    SetupScreenElementText(self);
    if (IsFontLoaded(2) != 0) {
        self->frame = (Font**)&D_00276620;
        *self->frame = GetFontById(2);
    }
    SetScreenElementHoldTime(self, 0.0f);
    SetScreenElementScale(self, 0.6f);
    self->color = 0xDF7F7F7F;
    self->vt->m08(self, D_0024E808);
    self->current = 0;
    func_001F5C0C((Clr_1F1960*)self->nodes, 0, 0x18);
}

void func_001F1A08(T217D_0F0* self, PadRecord* t)
{
    s32 loc[2];
    s32 s3;
    s32 s2;
    s32 v1;

    if (self->current == 0) return;
    if (self->current->mode != 2) return;
    if (self->current->f560 != 0) return;
    if ((t->flags & 0x910) != 0 || t->f14 == 1) {
        PopStackElement((ElementStack*)g_elementStack);
        ClearPadPressedBits((Pool_1F1A08*)&g_padRecord, 0x910);
        return;
    }
    if (self->mode != self->current->mode) return;

    s3 = IsWarpEntryAvailable(self->current, self->current->cursor, &loc[0], &loc[1]);
    s2 = GetPadHorizontalStep(t);
    v1 = GetPadVerticalStep(t);
    t->f30 = g_gameClock.elapsed + t->f34;
    t->f38 = g_gameClock.elapsed + t->f3C;

    if (v1 < 0) {
        MoveWarpCursor(self->current, 0);
    } else if (v1 > 0) {
        MoveWarpCursor(self->current, 1);
    } else if (s2 < 0) {
        MoveWarpCursor(self->current, 2);
    } else if (s2 > 0) {
        MoveWarpCursor(self->current, 3);
    } else if ((t->flags & 0x40) != 0) {
        ClearPadPressedBits((Pool_1F1A08*)&g_padRecord, 0x40);
        if (self->current->cursor != GetCurrentWarpEntry()) {
            if (s3 != 0) {
                Val_1F1A08* v = func_00160180((loc[0] << 8) | loc[1]);
                self->current->f560 = 1;
                PopStackElement((ElementStack*)g_elementStack);
                StartObjectFade(v, -1, 2);
            } else {
                StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        } else {
            PopStackElement((ElementStack*)g_elementStack);
        }
    }

    if (s3 != 0) {
        self->scaleTarget = 1.0f;
    } else {
        self->scaleTarget = D_00275FC0;
    }
    self->scale = ApproachValueWithRamp((Q3_1F1A08*)D_00276278, 0, self->scale, self->scaleTarget, g_gameClock.step);
}

void func_001F1C90(T217D_0F0* self, s32 a1)
{
    if ((a1 != 0) != (self->open == 0)) return;
    if (a1 != 0) {
        HideScreenElements(self);
        s32 r = GetCurrentWarpEntry();
        if (r == 10) {
            r = (IsWarpEntryAvailable(self->current, 1, 0, 0) != 0);
        }
        SetWarpCursor(self->current, r, 2);
        self->scaleTarget = 1.0f;
        self->scale = 1.0f;
        Anim_1F1C90* an = (Anim_1F1C90*)self->current->f2E4;
        if (an != 0) {
            SetScreenElementSlideInTime(self, an->f34);
        }
        GameProgress* g = g_saveData;
        if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
            func_001BED48();
        }
        self->vt->m14(self);
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
        SetElementStackState(g_elementStack, 7);
    } else {
        self->vt->m15(self);
        if (self->current->f560 == 0) {
            BeginWarpPageClose(self->current);
            Anim_1F1C90* an = (Anim_1F1C90*)self->current->f2E8;
            if (an != 0) {
                SetScreenElementSlideOutTime(self, an->f34);
            }
            ClearPadSelectFlags(1);
            SetElementStackState(g_elementStack, 3);
            GameProgress* g = g_saveData;
            if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
                func_001BED70();
            }
        }
    }
    self->open = a1;
}

void func_001F1E38(f32 cx, f32 cy, f32 radius, f32 angle, s32 n, s32* c1, s32* c2, s32 flags)
{
    Locals_1F1E38 loc;
    s32 i;
    f32 step = 6.2831855f / (f32)n;
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x42, (flags & 1) ? 0x48 : 0x44);
    BeginGifTag(&g_gsPacketWriter, 0x4D, 2, 0x41);
    AddGifRgbaEntry(&g_gsPacketWriter, *c1);
    AddGifXyzfEntry(&g_gsPacketWriter, (u32)(s32)((cx + 1728.0f) * 16.0f),
                  (u32)(s32)((cy * 0.454545468f + 1936.0f) * 16.0f), 0, 0);
    loc.k = 0;
    for (i = 0; i < n + 1; i++) {
        ComputeSinCos(WrapAngle(angle), &loc.x, &loc.y);
        loc.x = loc.x * radius + cx;
        loc.y = loc.y * radius + cy;
        if ((i & 1) && (flags & 2)) {
            AddGifRgbaEntry(&g_gsPacketWriter, loc.k);
        } else {
            AddGifRgbaEntry(&g_gsPacketWriter, *c2);
        }
        angle += step;
        AddGifXyzfEntry(&g_gsPacketWriter, (u32)(s32)((loc.x + 1728.0f) * 16.0f),
                      (u32)(s32)((loc.y * 0.454545468f + 1936.0f) * 16.0f), 0, 0);
    }
}

INCLUDE_RODATA(D_0024E830);
INCLUDE_RODATA(D_0024E838);
ASM_FUNC(func_001F20A8);

// The style above (D_00276620) and D_00276650 are built by the static initialiser GCC writes
// here (func_001F2688), and its _GLOBAL_$I$ (func_001F2738) follows the 12 bytes the linker left
// of a function this file wrote out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001F2728);
