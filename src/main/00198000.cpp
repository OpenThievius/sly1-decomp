// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "object_set.h"
#include "object_gatherer.h"
#include "c6e.h"
#include "c5c.h"
#include "c5d.h"
#include "effect_owner.h"
#include "effect_spawner.h"
#include "c8b.h"
#include "world.h"
#include "effect.h"
#include "list_iter.h"
#include "globals.h"
#include "game_progress.h"
#include "object_message.h"
#include "object_event.h"

void func_001B7968(void* self);


void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);


typedef s32 (*VFn_198B28)(void* self);
void func_00124A48(void* self);
s32 func_0012C9A8(void* node);
void func_00182ED8(void* node);


typedef void (*VFn_198DA8)(void* self);

void* func_0012C8F8(void* item, s32 a, f32 x, s32 b, f32 y, s32 c);
void func_001837E0(void* self, s32 a, s32 b, s32 c);


typedef void (*VFn_198E58)(void* self, void* msg);

struct Msg_198E58 {
    s32 kind;
    void* owner;
    u8 pad_08[0x50 - 8];
};

struct Target_198E58 {
    VFn_198E58* vtbl;
};


s32 func_00182FC8(void* self);


void func_001BA130(void*);
void func_00198980(ObjectSet*);
void func_001B7F78(void);
void func_00182D48(void*);
void func_00152470(void*, void*);
void func_00182ED0(void*);
void func_00152600(void*, void*);
void func_00182C58(void*);
void* func_0015A418(void*, s32, s32, void*);
void func_001B7A98(void*);
void func_001B7B78(void*);
void func_00182C18(void*);
void func_00144848(void*);
void func_0015EAE0(void*, void*, void*);
void func_0019D860(void);
void func_0019D968(void);
void func_0019D930(void);
void func_0019EBE8(Effect*);
void func_001831E8(void*, void*, s32, void*);
void func_001831E8(void*, void*, void*, void*);
void func_00183238(void*, void*, void*, void*);
void func_0019F9D0(Effect*, s32);


typedef void (*VFn_198EF8)(void* self, void* other);

struct Ctx_198EF8 {
    VFn_198EF8* vtbl;
    u8 pad_04[0x2230 - 4];
    ObjectMessage* watched_2230;
};


void func_00127378(ObjectSet* self, s32 msg, ObjectMessage* m);


s32 func_001300E8(void* obj, s32 kind);


void* func_001929F8();
s32 func_00182F40(void* e, void* b);

struct Rec_199000 {
    u8 pad0[0x18];
    void* f18;
};

struct Elem_199000 {
    u8 pad0[0x4];
    void* f4;
    u8 pad1[0x40 - 0x8];
};











struct Rec_19A088 { s32 flags; u8 rest[0x74]; };


struct Obj_19A0F0 { u8 pad0[0x30]; s32 f30; };
extern Obj_19A0F0 D_00275BC0;
void func_0019A088(s32 index);
void func_001E5278(s32 mode);


void func_001921A8(C17* self);


struct Obj_19A178 { s32 f0; s32 f4; s32 f8; };
s32 func_0015A418(s32 a, s32 b, s32 c, s32 d);
void func_00182ED8(s32 a);
s32 func_001B6290(s32 a, s32 b, s32 c, s32 d);


void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0016EC88(void* p);
s32 func_001602A0(void);
void func_00160578(s32 value);
void* func_0015A448(void* a, s32 code, void* c);

extern u8 D_00262C70[];






void func_001830D8(void* self);




struct Obj_0019C3D0 { u8 pad[0x14]; u8* owner; };


struct Obj_0019C408 { u8 pad[0x14]; u8* owner; };




struct Val_0019D468 { u8 pad[4]; f32 value; };

extern u32 D_00604788;


extern u8 D_00212160[];
extern u8 D_00215C50[];


extern u8 D_00212160[];
extern u8 D_00215C50[];
extern u32 D_00604788;


extern u8 D_00212160[];
extern u8 D_00215C50[];


extern u8 D_00215C60[];
extern u8 D_00217348[];


void func_0019E158(EffectOwner* a, Rec50* b)
{
    a->f554 = b->f1E8;
}

void func_0019E418(void) {}

void func_0019EC20(Effect* counter)
{
    counter->uses++;
}

void func_0019ECE0(Effect* value, s32 enabled)
{
    if (enabled) RemoveEffect(value);
}

struct Obj_0019F8E8 { u8 pad[0x44]; s32 value; };

void func_0019F8E8(void* obj, void* arg)
{
    Obj_0019F8E8* value = *(Obj_0019F8E8**)arg;
    AddCallbackNode((void*)g_currentWorld, (u8*)obj + 0x118, value->value, arg);
}

void func_0019F918(void* obj, void* a1, void* a2)
{
    AddCallbackNode((void*)g_currentWorld, (u8*)obj + 0x118, a1, a2);
}

void func_0019F950(void* obj, void* a1, void* a2)
{
    RemoveCallbackNode((void*)g_currentWorld, (u8*)obj + 0x118, a1, a2);
}

void func_0019FCE8(Effect* value, u32 enabled)
{
    func_0019F9D0(value, enabled < 1);
}

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_0015A838(void* a, s32 b, s32 c, void* d);

extern u8 D_00261420[];

void func_00198980(ObjectSet* self);
void* func_00140FF8(void* p);


void func_001989B0(ObjectSet* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void* func_0018D500(s32 size);
void func_00182ED8(s32 a);
extern s32 D_0026A948[4];


struct Vec4_19BE08 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Src_19BE08 { u8 pad[0x20]; Vec4_19BE08 q20; Vec4_19BE08 q30; };
struct Local_19BE08 { s32 mode; u8 pad[0xC]; Vec4_19BE08 qa; Vec4_19BE08 qb; u8 pad2[0x20]; };
typedef void (*VFn_19BE08)(void* self, void* arg);
struct Obj_19BE08 { VFn_19BE08* vtbl; };

void func_0019C1C0(void* self, s32 mode);


extern u8 D_00261420[];
s32 func_00198E98(ObjectSet* self);
s32 func_00141008(void* table, s32 index);


extern u8 D_00261420[];
void func_00141040(void* table, s32 index);
void func_00198DA8(ObjectSet* self);


typedef void (*VFn_199AF0)(void* self);


void func_001C72A0(void* self);

struct __attribute__((aligned(16))) Quad_1984B8 { s32 a, b, c, d; };
typedef void (*VFn_1984B8)(void* self, void* ctx);

void* func_001925F0(void);
void func_00197A08(void* h, void* self);
void func_001C9008(void* self, void* arg);

void func_001C91C8(void* self);
void func_001C8920(void* self);

void func_001C9DE0(void* self, s32 code, void* req);

typedef void (*VFnA_199C78)(void* self, s32 a);
typedef void (*VFnB_199C78)(void* self);

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_001BC320(void* self, ObjectEvent* ev);


void func_001BA130(void* self);


extern s32 D_0026A918[4];

void func_001289C0(void* self);
void func_00124DF8(void* self, s32 n, void* table);


extern s32 D_0026A928[4];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);


extern s32 D_0026A938[4];

void func_001289C0(void* self);
void func_00124DF8(void* self, s32 n, void* table);


typedef void (*VFn_199F38)(void* self);

struct Obj_199F38 {
    VFn_199F38* vtbl;
};

struct Holder_199F38 {
    u8 pad0[0x18];
    Obj_199F38* sub;
};

extern u8 D_0026C948[];

s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_00199B18(void* obj);
s32 func_001300E8(void* node, s32 kind);


s32 func_001602A0(void);


extern f32 D_0026185C[];
void func_001B7968(void* self);
f32 func_001EAB48(f32 a, f32 b, f32 c);


extern s32 D_0026AB90[4];

void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void* func_0015A480(void* self, s32 kind, void* arg);
void func_00182ED8(void* node);


extern s32 D_0026ABA0[4];

void func_0019C1C0(void* self, s32 mode);
void func_00124DF8(void* self, s32 n, void* table);
void func_00124A48(void* self);


extern s32 D_00270454;
extern u8 D_00264A40[];

void func_001B64D8(void* a, s32 b);
void func_001E9570(void* q);
s32 func_001602A0(void);
void func_001604B8(s32 mode);
void func_0018C7F8(void* p);
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);


typedef void (*VFn_199500)(void* self);
extern s32 D_00275C34;

void func_00198B28(ObjectSet* self);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_001EAA70(s32 a, s32 b);


extern u8 D_0026C948[];
extern u8 D_0026A970[];

typedef void (*VFn_1999D0)(void* self);

struct Obj_1999D0 { VFn_1999D0* vtbl; };
struct __attribute__((aligned(16))) Quad_1999D0 { s32 a, b, c, d; };

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00128018(void* a0, s32 a1, void* a2, void* a3);
Effect* func_0019EA78(s32 kind, EffectOwner* sys);
void func_00199850(C2E* self);
void func_00198DA8(ObjectSet* self);



void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001518B8(s32 x);


struct VObj_19A1E0 { s32 (**vtbl)(VObj_19A1E0*, C17*); };
struct Pad_19A1E0 { u32 flags; u8 pad[0x74]; };


void func_00124A48(C17* o);
void func_00124DF8(C17* o, s32 n, u8* t);
void func_0019A178(void* p, s32 x);
s32 func_001B6290(s32 a, C17* b, s32 c, s32 d);
void func_001B64D8(s32 a, s32 b);
VObj_19A1E0* func_0015A448(World* a, s32 b, C17* c);
s32 func_001EAA70(s32 a, s32 b);
void func_00160D30(s32* p);


s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);

struct Elem_199218 {
    u8 pad0[0x2D0];
    void* f2D0;
    void* f2D4;
};

void func_00124A48(void* self);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001B64D8(void* p, s32 n);


// NEAR: global kept in $a1 not $t0 and the mask shift scheduled early; call and loop sequence match

typedef void (*VFn_199B18)(void* self);

struct Actor_199B18 {
    VFn_199B18* vtbl;
    u8 pad0[0x570 - 4];
    s32 n570;
    void* arr574[1];
    u8 pad1[0x5A0 - 0x578];
    s32 n5A0;
};

void* func_0012C8F8(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb);
void func_001837E0(void* self, s32 a, s32 b, s32 c);


struct Arg_001993C0;
void func_001781E0(Arg_001993C0* a, s32 v);


extern f32 D_0024C8C4;


struct List_1989B0 { s32 head; s32 x; s32 link; };
struct Frame_1989B0 {
    s32 list; s32 cursor; s32 link; s32 prev;
    Frame_1989B0(List_1989B0* l) {
        cursor = (s32)l;
        list = (s32)l;
        link = l->link;
        prev = *(s32*)&D_0027B314;
        *(s32*)&D_0027B314 = (s32)this;
    }
};
void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);
void func_00182ED8(BaseObject* n);


s32 func_001300E8(void* key, s32 kind);
s32 func_00182FC8(void* p);
s32 func_00141170(void* self, void* value);

struct Slot_19AB78 { u8 pad[0x304]; s32* f304; };

struct Slot_19AB78;
struct Ent_19AB78 { u8 pad[0x14]; s32 f14; Slot_19AB78* f18[4]; s32 f28; };
struct Obj_19AB78 { void** vt; };
typedef void (*VFn_19AB78)(Obj_19AB78*);
struct Vi_19AB78 { u8 pad[0x239C]; s32 f239C; u8 p2[0x2C]; void* f23CC; };

void func_00192230(void* self, s32 code, s32* rec);
void func_00175170(void* self, s32 a, s32 b);
s32 func_0019A000(s32 bits);
void func_001518B8(Slot_19AB78* s);




