// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "animation.h"
#include "id_filter_object.h"
#include "world.h"
#include "c8b.h"
#include "attachment.h"
#include "s1dbbd8.h"
#include "target_binding.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "shapes.h"
#include "globals.h"

s32 func_0012C288(void* a, void* b, s32 c, s32 d, s32 e, s32 f);

void* func_0012CCE8(void);
void func_0012D2A8(Animation* a, Track83* b);

s32 func_001833F0(void* a, void* b);

void func_00121648(void* n, void* b);

struct Mid_12F7E0 { u8 pad[0x14]; void* p14; };
struct Obj_12F7E0 { u8 pad[8]; Mid_12F7E0* mid; };

void func_001831E8(void* a, void* b, void* c, s32 d);

s32 func_0012FF10(StreamReader* self);
s32 func_001F8C38(s32 h);
s32 func_002032C8(s32 x);
void func_0012FFE8(StreamReader* self);

void func_001830D8(void);

void func_00182C58(void* self);
void func_0012C208(void* self);
void func_001DBC60(void* host, void* cb, void* ctx, s32 a3, s32 a4);

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
s32 func_0012C7B0(void* self, s32 a1, s32 a2, s32* out, f32 fa, f32 fb);

struct Obj_0012C208 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0x28];
    s32 id;
};

void func_0012C288(void* self, s32 a1, s32 a2, s32 a3, s32 a4, void** out);

struct Node_0012C808 {
    u8 pad0[0xC];
    s32 key;
    u8 pad1[0x2C];
    Node_0012C808* next;
};

struct Owner_0012C808 {
    u8 pad0[0x6C];
    Node_0012C808* head;
};

void* func_0012C808(void* self, s32 key);
s32 func_0012C7B0(void* self, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void func_0012F0A0(void* obj, s32 a1, f32 fa, f32 fb);

void func_0012C840(void* self, s32 key, s32 a2, s32 a3, void** out, f32 fa, f32 fb);

void func_0012F6B0(AnimationPlayer* self, f32 x);
void func_0012F190(AnimationPlayer* self, s32 zero);
void func_0012F1D8(AnimationPlayer* self);
void func_0012E4E0(AnimationPlayer* self, Animation* sub, s32* out);
void func_0012E760(AnimationPlayer* self);
void func_0012D4A8(AnimationPlayer* self);

struct Item_0012F1D8 { u8 pad[0x20]; Item_0012F1D8* next; };

void func_001226D8(Item_0012F1D8* item);

void func_00152600(u8* a, void* b);
void func_001B5F28(u8* a, void* b);

Attachment* func_0012D570(void* a0, void* a1);

struct Node_12F718 {
    u8 pad0[4];
    void* data4;
    u8 pad8[0xC];
    s32 value14;
    u8 pad18[8];
    Node_12F718* next;
};

struct Owner_12F718 {
    u8 pad0[0x44];
    Node_12F718* head;
};

void func_00129A58(void* p);

struct Obj_12F760 {
    void (**vtbl)(void* self);
};

void* func_0012CBE8(void);

void func_001831E8(void* a, void* b, void* c, void* d);

void func_001B7968(Collider* self);
void func_001B9AE0(Collider* self, s32 a, Vec02* b, s32 c, Vec02* d);

void func_001BA130(Collider* self);
void func_00138F28(void* a, void* b);

s32 func_001F92E8(s32 a, s32 b, s32* c);
s32 func_00203D90(void);

void func_0018D778(void* self);

s32 func_0012FDA0(void* self, s32 a, s32 b);

void func_001DDA20(void* a);
void func_001DDA50(void* a);

void func_0012E760(void* obj);
s32 func_0012C7B0(void* self, void* a1, f32 fa, f32 fb, void* a2, void** out);

s32 func_001833F0(void* a, s32 b);

struct Entry_12CCE8 { s32 key; u8 pad[0x18]; };

s32 func_001B8A08(Collider* self, Collider* key);
s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 kind);

void func_0012FE70(StreamReader *self);

s32 func_0012FF20(StreamReader* a0);

struct Head_2197B8 { const void* tinfo; s32 f4; };
extern const Head_2197B8 D_002197B8;
void* func_001B5EE0(Pool6C* pool);
void func_00152438(List01* self, s32 value);

struct Quad_12F9B8 { s32 a, b, c, d; };

void func_001B93F8(Collider* self);
void func_00128018(void* a, s32 b, void* c, void* d);

struct Item_12E760 { s32 w[4]; };
struct Vt_12E760 { void* pad[2]; void (*fn8)(void* self, s32 a); };
struct Elem_12E760 { Vt_12E760* vt; };
struct Frame_12E760 { s32 f00; s32 f04; s32 f08; s32 f0C; };
struct Tmp_12E760 { s32 a; s32 b; };

void func_0012D5D0(AnimationPlayer* self, Item_12E760* item, Tmp_12E760* out);
void func_0012F760(AnimationPlayer* self, s32 a, AnimationPlayer* b);
void func_001DBC18(u8* self, void* node);
void func_0015F9A0(u8* a, u8* s);
void func_0012D448(AnimationPlayer* self, s32 v);
void func_001DBD40(u8* a, s32 b, s32 c, AnimationPlayer* d, s32 e, s32 f);
void func_00152600(u8* a, AnimationPlayer* b);
void func_00152470(u8* a, AnimationPlayer* b);
void func_001BF718(s32* slot);
void func_001837E0(Animation* self, s32 a, s32 b, s32* c);

f32 func_002058A0(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

void func_001F5B08(Track83* dst, Track83* src, s32 bytes);

struct Item_12E4E0 { f32 t; s32 type; s32 w2; s32 w3; };
void func_0012D5D0(AnimationPlayer* self, Item_12E4E0* item, s32* out);

// was NEAR: call result is stored directly (retail copies v0 to v1 first, then s1=v1 for the out pointer); 5 lines differ

struct Entry_12D1B0 { s32 f0; s32 type; s32 f8; s32 fC; };
struct Obj_12D1B0 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0x5C - 0x18];
    s32 count;
    Entry_12D1B0* items;
};

void* func_0018D658(s32 size);

struct World_12D5D0;
struct VObj_12D5D0 {
    void** vt;
};
struct Msg_12D5D0 {
    union {
        f32 f;
        s32 i;
    } a0;
    s32 kind;
    union {
        s32 i;
        f32 f;
        void* p;
        struct {
            s16 lo;
            s16 hi;
        } h;
    } a8;
    union {
        s32 i;
        f32 f;
        struct {
            s16 lo;
            s16 hi;
        } h;
    } aC;
};
struct Seq_12D5D0 {
    s16 count;
    s16 ids[6];
    s16 cur;
    s16 target;
    u8 pad12[2];
    s32 f14;
    s32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
};
struct Ent_12D5D0 {
    u8 pad0[4];
    VObj_12D5D0* f4;
    VObj_12D5D0* f8;
    s32 fC;
    u8 pad10[0x18 - 0x10];
    s32 f18;
};
struct Owner_12D5D0 {
    u8 pad0[0x14];
    World_12D5D0* world;
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    f32 f34;
    u8 pad38[0x3C - 0x38];
    Ent_12D5D0* ents;
    u8 pad40[0x5C - 0x40];
    s32 nmsgs;
    Msg_12D5D0* msgs;
};
struct Info_12D5D0 {
    s32 f0;
    s32 f4;
    s32 f8;
    f32 fC;
};
struct Req_12D5D0 {
    s32 flags;
    void* f4;
    u8 pad8[0x20 - 0x8];
    Vec4U buf;
    f32 f30;
    u8 pad34[4];
    void* f38;
    u8 pad3C[0x50 - 0x3C];
};
union Scratch_12D5D0 {
    Req_12D5D0 req;
    Vec4U v[3];
    void* p[3];
    s32 w[3];
};
struct __attribute__((packed)) Word_12D5D0 { s32 v; };

typedef void (*VFn_12D5D0)(void* self);
typedef void (*VFnI_12D5D0)(void* self, s32 a);
typedef void (*VFnP_12D5D0)(void* self, void* a);
typedef void (*VFnIP_12D5D0)(void* self, s32 a, void* b);
typedef void (*VFnAim_12D5D0)(void* self, void* obj, s32 a, Vec4U* b, Vec4U* c, f32 x, f32 y);

extern u8 D_00275F80[];
extern u8 D_0026E760[];
extern u8 D_00262C70[];
extern u8 D_00269A00[];
extern VObj_12D5D0 D_00272E08;
extern u8 D_00275BC0[];

s32 func_001BE810(void);
void func_001BE728(void* p);
void func_001BE998(void);
s32 func_001EAA70(s32 lo, s32 hi);
s32 func_001BE568(s32 id);
Collider* func_0015A418(World_12D5D0* w, s32 kind, s32 id, void* scope);
Collider* func_0015A448(World_12D5D0* w, s32 id, void* scope);
void func_001BFCD8(s32 id, VObj_12D5D0** handle, Collider* target, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BF788(VObj_12D5D0* h, s32 n);
void func_001BED20(void);
void func_001BECF8(void);
void func_001518B8(Collider* t);
s32 func_00126CB8(Collider* t, f32 v);
s32 func_00126D60(Collider* t, f32 v);
void func_001B9AE0(Collider* t, s32 a, s32 b, s32 c, s32 d);
void func_001F4ED0(Collider* t);
void func_001F4F20(Collider* t);
void func_00177800(Player* g, s32 flag);
void func_0012F190(AnimationPlayer* self, s32 v);
// the node keeps the inline setter of its second mode byte that retail's code calls (see NOTES.md)
struct Node_12D5D0 : T2195_7C0 {
    void SetMode(s32 mode) { mode1 = mode; }
};
Node_12D5D0* func_0012D570(AnimationPlayer* self, s32 key);
void func_001215C0(Node_12D5D0* n);
void func_001EFFA0(u8* dst, s32 a, s32 b);
void func_001F00C0(u8* dst, s32 a, s32 b);
void func_001F4408(s32 a, s32 b);
void func_001AB890(u8* p, f32 x);
void func_001AB938(u8* p);
void func_001AB958(u8* p);
s32 func_0012C7B0(Collider* a, Collider* b, s32 c, s32 d, f32 x, f32 y);
void func_0016EC38(u8* p, s32 n, f32 f);
void func_001837E0(void* self, s32 a, s32 b, void* c);
void func_0012F760(AnimationPlayer* self, s32 a, void* b);
void func_0012B2F8(Collider* t, s32 key);
void* func_001B6388(Collider* a, Collider* b);
void* func_001B6290(Collider* a, Collider* b, s32 c, s32 d);
void func_001B64D8(void* a, s32 b);
void func_001B6438(void* o);
s32 func_001300E8(Collider* n, s32 kind);
void func_001920B0(Collider* n, Vec4U* out);
s32 func_001F3BD8(Collider* n, Vec4U* out);
s32 func_00182FC8(void* p);
void func_001DDB58(World_12D5D0* w);
void func_001DDBB8(World_12D5D0* w);
void func_0018F0E8(u8* a, s32 b);
void func_0014AEA0(VObj_12D5D0* self, s32 n, f32 x, f32 y);
void func_0014AF10(VObj_12D5D0* self);
void func_0014AF38(VObj_12D5D0* self, s32 a, s32 b, f32 x);
void func_001E96F8(u8* obj, s32 mode);
void func_001DDAB8(World_12D5D0* w, f32 v);
void func_001DDAC8(World_12D5D0* w, f32 v);
void func_0017CE20(Collider* t, Player* g);

struct Clamp_12D5D0 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

struct Range_12E968 { u32 field0; f32 minimum; f32 maximum; };
struct Obj_12E968 { u8 pad0[8]; Range_12E968* range; };

s32 func_001F8DB8(void* p, s32 a, s32 b);
void func_00140CC8(void* p, s32 n, s32 base);

struct Key_12D4A8 {
    f32 time;
    u8 pad[12];
};

struct Rec_12CBE8 {
    u32 f0;
    s32 f4;
    s32 f8;
    u32 fC;
};

struct Obj_12CBE8 {
    u8 pad0[0x54];
    s32 f54;
    Rec_12CBE8* f58;
    s32 f5C;
    Rec_12CBE8* f60;
    s32 f64;
    Rec_12CBE8* f68;
};

struct Iter_12F8C8 { List01* list; u8* link; s32 offset; Iter_12F8C8* saved; };

struct Next_12F8C8 {
    static PlacedObject* Of(Iter_12F8C8* it)
    {
        PlacedObject* obj = *(PlacedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_12F8C8 {
    static void Of(Iter_12F8C8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_12F8C8*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00124A48(PlacedObject* self);
s32 func_0015A448(void* world, s32 b, PlacedObject* c);
s32 func_001300E8(void* n, s32 kind);

struct Entry_12E5D0 {
    f32 key;
    s32 a4;
    s32 a8;
    s32 aC;
};

void func_0012D5D0(AnimationPlayer* self, Entry_12E5D0* entry, s32* out);

// kept: the bitfields make `n->f10 = n->f11 = 3` store from two registers, as retail does
struct Node_12C288 {
    u8 pad0[0x10]; s32 f10 : 8; s32 f11 : 8; s32 f12 : 8; s32 f13 : 8; s32 f14;
    u8 pad1[0x1C - 0x18]; AnimationPlayer* f1C;
    u8 pad2[0x28 - 0x20]; s32 f28;
};
struct Item_12C288 { u8 pad[0x10]; };

void func_00152470(u8* list, AnimationPlayer* o);
void func_00152470(u8* list, Node_12C288* n);
void func_0018D608(void);
PlacedObject* func_0015A418(World* w, s32 kind, s32 key, void* ctx);
Node_12C288* func_00128998(PlacedObject* h);
void func_001B5F28(u8* list, Node_12C288* n);
void func_001215C0(Node_12C288* n);
void func_001299E0(PlacedObject* h, Node_12C288* n);
void func_0018D6F0(void);
void func_0015F8B0(World* w, u8* p);
void func_0012D5D0(AnimationPlayer* o, Item_12C288* item, s32* out);
void func_0012F190(AnimationPlayer* o, s32 flag);
void func_001837E0(Animation* self, s32 a, s32 b, AnimationPlayer*** c);

extern const u8 D_00217410[];
extern const Head_2197B8 D_002197B8 = { D_00217410, 0x92 };
