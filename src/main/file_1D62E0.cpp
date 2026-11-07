// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1D62E0 to 0x1DDCE0: classes 0x07 and 0x3F, the output buffer, class 0x19, the world
// (class 0x6C) and its script functions. Its .data runs from 0x275140 to the zeroed globals
// D_00275710 (g_currentWorld) to D_00275728 that close it; its .rodata is the "%s" of
// func_001D72C8, the float of func_001D8470 and the pairs of func_001DCD28. One file between
// two edges with no evidence inside it: it could be several.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"

extern f32 D_00261858[];

typedef void (*VFnA)(void* self);
typedef void (*VFnB)(void* self, void* arg);

struct Node_1D6CB0 {
    void** vtbl;
};

s32 func_00182FC8(void* node);

s32 func_001B8A08(void* self, s32 value);



struct __attribute__((aligned(16))) Quad_1D73A8 { s32 a, b, c, d; };

void func_001921A8(void* self);
void func_0018D800(void* dst, void* src, u32 size);
void func_001DB290(void* self);

void func_0013B708(StandIn* self, s32 kind, ObjectMessage* ref);

void func_001F5C0C(OwnerMessage* p, s32 zero, s32 size);

void func_001D72C8(OutputBuffer* a0, s32 a1);
void func_0018D778(OutputBuffer* a0);

void func_0018D800(void* dst, void* src, s32 bytes);
s32 func_001F7B88(void* a, void* b);
void func_001F9028(s32 a, void* b, s32 n);

void func_0018D800(void* dst, void* src, s32 count);
void func_001D72C8(OutputBuffer* self);
struct Snd_1D7440 { s32 pad; };

struct __attribute__((aligned(16))) Quad_1D7440 { s32 a, b, c, d; };
struct Src_1D7440 { u8 pad[0x100]; Quad_1D7440 q; };
struct Slot_1D7440 {
    Src_1D7440* p;
    u8 pad4[0xC];
    Quad_1D7440 q;
    u8 pad20[0x40];
};
struct Vt_1D7440 { u8 pad[0x6C]; void (*fn6C)(void* o, void* arg); };
struct Ent_1D7440 { Vt_1D7440* vt; };

void func_00124A48(PathFollower* self);
void func_00124DF8(PathFollower* self, s32 n, void* table);
f32 func_00205778(f32 a, f32 b);
StateTrigger* func_001B6290(Snd_1D7440* a, PathFollower* self, s32 b, s32 c);
void func_001B64D8(StateTrigger* a, s32 b);
void func_001BFCD8(s32 id, void* a1, PathFollower* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 func_001EAAE0(f32 a, f32 b);
void* func_0015A418(World* host, s32 a1, s32 a2, PathFollower* ctx);
s32 func_0015A198(World* host, s32 a1, s32 a2, s32 a3, s32 a4, Ent_1D7440** out);
void func_001DB290(PathFollower* self);

void func_001B9F30(void);

void func_001C0C08(void* a, void* b);

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 value, u32 size);

void* func_001C0C68(void* a, void* b);

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 a, s32 b);

void func_001B5F28(void* list, void* item);

void func_001B5F28(void* list, void* item);

void* func_001DBBD8(void* self);

typedef void (*VFn_1D92F0)(void* self);
struct Sub_1D92F0 { VFn_1D92F0* vtbl; };
extern f32 D_0026185C;

void func_001DBC18(void* self, void* node);

typedef void (*VFn_1DACB0)(void* self, void* a, void* b);
struct Target_1DACB0 { VFn_1DACB0* vtbl; };
void func_001CB328(void* self, void* value);
void func_001924C8(void* self, void* a, void* b);

void func_001B89B8(void* self);
void func_001DAD28(void* self);

struct Link_1DAF08 { u8 pad[0x50]; void* owner; };
struct Rec_1DAF08 { u8 pad0[8]; s32 kind; u8 pad1[0x6CC - 0xC]; Link_1DAF08* link; };

void func_00192230(void* self, s32 kind, Rec_1DAF08* rec);

struct Obj_1DBA38 { u8 pad0[0x14]; s32 f14; };
void func_00137B60(void* self, s32 n);
void func_00137A60(void* self, s32 size, s32 obj);

struct Entry_001DB1E8 { s32 active; s32 a; u8 pad[0x10]; f32 x; f32 y; s32 b; s32 c; };


typedef void (*VFn_1DB0C8)(void* self, void* a, s32 b, void* c, s32 d, void* e, s32 f);
struct Inner_1DB0C8 { VFn_1DB0C8* vtbl; };
struct Outer_1DB0C8 { u8 pad0[0x34]; Inner_1DB0C8* inner; };

void func_00152438(void* self, s32 value);

void func_001DBC18(void* self, void* node);

struct Sub_1D8740 { u8 pad0[0xC]; s32 n0C; };

f32 func_001D86F8(f32 x, f32 lim, f32 base);

void func_001B8540(void* self);
void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_001B8420(void* self, void* p, f32 f);

struct __attribute__((aligned(16))) Quad_001DAC20 { s32 a, b, c, d; };
struct Slot_001DAC20 { void* ptr; u8 pad[0x5C]; };

extern u8 D_0026DAAC[];

void func_001922E8(void* a, void* b);
void func_001DDC38(void* sub, void* self);
void func_001DB238(void* self, s32 mode);

struct Obj_1DAFB8 { void** vtbl; };
struct Arg_1DAFB8 { u8 pad_00[0x34]; Obj_1DAFB8* obj; };
struct Entry_1DAFB8 { s32 flag; void* ptr; u8 pad_08[8]; u8 at10[0x18]; };
void func_001DAD28(void* self);
void func_001F3BD8(void* self, void* arg);

typedef void (*VFn7_1DAFB8)(Obj_1DAFB8* self, void* a1, s32 a2, s32 a3, s32 a4, void* a5, void* a6);
typedef f32 (*VFnF_1DAFB8)(Obj_1DAFB8* self);

s32 func_00137480(void* self, s32 n);
s32 func_00137D78(void* self);

struct Res_1DA170 { u8 pad[0x48]; void* f48; };

Res_1DA170* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
s32 func_001E9970(void);

void func_0011A800(void* a);
s32 func_0011A498(void* a, s32 b, s32 c, ScriptValue* d);
void* func_0011A080(ScriptValue* t, R11B008Node* n, void* c);
void* func_0011A400(ScriptValue* self, void* table, s32 key, ScriptValue* item);
extern u8 D_00259F38[];

struct Sub_1D8578 { u8 pad0[0xC]; s32 n0C; };
struct Tri_1D8578 { f32 a; f32 b; f32 c; };

extern f32 D_00261858[];

void* func_001925F0(void);
f32 func_001EA4B8(void* p, s32 zero, f32 a, f32 b, f32 c);
f32 func_001EAAE0(f32 a, f32 b);

struct Entry_1DB110 {
    s32 f0;
    void* f4;
    u8 pad8[4];
    s32 fC;
    void* f10;
    Entry_1DB110* f14;
    u8 pad18[0x10];
};

struct VObj_1DB110;
typedef void (*VFn_1DB110)(VObj_1DB110* self, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, void* a6);
struct VObj_1DB110 {
    VFn_1DB110* vtbl;
};

struct Node_1DB110 {
    u8 pad0[0x34];
    VObj_1DB110* f34;
};

struct __attribute__((aligned(16))) Quad_1DB110 {
    s32 a, b, c, d;
};

void func_001F3BD8(void* item, void* out);

extern f32 D_0026185C;
void* func_001925F0(void);
void func_001929D0(void* self);

void func_00192B58(PathFollower* self, f32 t);
void func_001D8578(PathFollower* self);
void func_001D87C8(PathFollower* self, s32* out);
void func_001D8BD0(PathFollower* self);
void func_001D9678(PathFollower* self, f32 t);
void func_001D8D90(PathFollower* self);
void func_001D8E40(PathFollower* self);
void func_001D9488(PathFollower* self, s32 v);
void func_001D9AC8(PathFollower* self);
void func_00129DF8(PathFollower* self);

extern f32 D_0026185C;

struct Inner_1D9338 { u8 pad0[0xC]; s32 value; };
extern u8 D_00261EF0[];

void func_00151E20(void* msg, f32 value);

s32 func_001EB080(s32 count, ValueRange* spans, f32 x);

struct Sub_1DB4C8 { u8 b; };

extern s32 D_00262C64;

void func_00182C18(World* self);
void func_001C09D8(World* self, s32 a, s32 b);
void* func_0018D5C0(s32 size);
void func_001DC740(World* self);
void func_001B5DD0(Sub_1DB4C8* p, s32 a, s32 b);
void func_001B5E30(Sub_1DB4C8* p, s32 a, s32 b);
void func_00152438(Sub_1DB4C8* p, s32 a);
void func_001DBA90(World* self, f32 x);

#define SUB(off) ((Sub_1DB4C8*)((u8*)self + (off)))

typedef s32 Id_1DBAE0;

s32 func_001C0C50(Id_1DBAE0 index);

extern f32 D_002754F8; extern f32 D_002754F4; extern f32 D_00261860; extern f32 D_002754E8[3];
f32 func_00205778(f32 a, f32 b); f32 func_001EA408(f32 a); f32 func_001EA480(f32 a, f32 b); f32 func_001EA728(void* p, void* out, f32 a, f32 b, f32 c);

extern s32 D_00269C90;
extern s32 D_00262C6C;
extern u8 D_00275BC0[];
extern s32 D_002640A4;
extern f32 D_00261854;
extern s32 D_00261D38;

void func_00192880(s32 index);
void func_0016E148(void);
void func_00143AF0(void* obj);
void func_001DFD70(void);
void func_0017FD70(void);
void func_00191EE8(void);
void func_00169CA0(void);
void func_001C07B0(void);
void func_001B40C8(void);
void func_0011C040(void);
void func_001E9688(void* a);
void func_0018D550(void);

struct __attribute__((packed)) Word_1DB838 { s32 v; };

typedef int V128_1DB290 __attribute__((mode(TI)));

struct Poly_1DB290 {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

struct Obj_1DB290 {
    u8 pad0[0x620];
    f32 f620;
    f32 f624;
    f32 f628;
    u8 pad62C[4];
    u8 v630[0x10];
    f32 f640;
    f32 f644;
    u8 pad648[8];
    u8 v650[0x10];
    f32 f660;
    f32 f664;
    u8 pad668[8];
    u8 v670[0x10];
    f32 f680;
    f32 f684;
    u8 pad688[0x854 - 0x688];
    f32 f854;
    s32 f858;
    f32 f85C;
    f32 f860;
    f32 f864;
    u8 pad868[4];
    f32 f86C;
    u8 pad870[0xAF4 - 0x870];
    s32 fAF4;
    s32 fAF8;
    u8 padAFC[4];
    s32 fB00;
    u8 padB04[0xB10 - 0xB04];
    f32 fB10;
};

void func_00118CF0(void* out, f32 f);
void* func_00118D10(void* out, void* in);
void* func_00118D20(void* dst, V128_1DB290 v);
V128_1DB290 func_001DB460(V128_1DB290 a, V128_1DB290 b, V128_1DB290 c, V128_1DB290 d);

struct Bounds_1DB290 {
    f32 lo;
    f32 hi;
    void Blend(f32 y, const Bounds_1DB290& a, f32 x, const Bounds_1DB290& b)
    {
        lo = y * a.lo + x * b.lo;
        hi = y * a.hi + x * b.hi;
    }
};
struct Clamp2_1DB290 {
    f32 lo;
    f32 hi;
    f32 Clamp(f32 v)
    {
        if (v < lo)
            return lo;
        if (hi < v)
            return hi;
        return v;
    }
};

s32 func_00160850(void* obj);

s32 func_00160850(void* obj);

s32 func_00160850(void* obj);

s32 func_00160850(void* obj);

// The four key/value slots after offset 0x44 of a level entry (SetEntrySlotValue, GetEntrySlotValue).
struct EntrySlot { s32 key; s32 value; };
struct EntrySlotTable { u8 pad[0x44]; EntrySlot slots[4]; };

void* func_00160810(void* obj);

s32 func_00160B28(void* p);

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 value, u32 size);

extern void* D_002622CC;
extern void* D_00264260;

f32 func_001EB0F8(void* p);

void* func_001BEEF8(void* p);

void func_001922E8(void* self, void* p);

void* func_001EAA70(void* a, void* b);
s32 func_00148AC0(void* heap, int size, void* c, void* d, int e);

extern u8 D_00261EF0[];

void func_00152410(void* p);

void* func_001BF0D8(void* p);

typedef void (*VFn_001DDC40)(void* self);
struct Child_001DDC40 { VFn_001DDC40* vtbl; };

void func_001B5F28(void* list, void* item);

void func_001DC710(Contacts03* node, Contacts03** head);
void func_001DC7B0(Contacts03* node, Contacts03** head);

extern u8 D_00275BC0[];

void func_001E9570(void* g);

struct __attribute__((packed)) Unaligned_1DDB20 { s32 v; };

void func_00194D30(T217D_6D0* self, s32 mode, s32 value);

s32 func_00137C40(void* src);
void func_00138518(void* self);

struct Stack_001DC208 { s32 count; s32* values; };

struct __attribute__((packed)) Pair_1DC150 { s32 n; void* buf; };

void* func_0018D500(s32 size);
void* func_00183058(void* a, void* b, void* c);


void* func_00160810(void* obj);

s32 func_001BE980(void);
void func_001DFBE0(void* self, s32 flag);

void func_001B6598(void* dev, s32* out);
void func_001B6568(void* dev, s32* out);
void func_00192230(void* self, s32 kind, MessageBody* rec);

struct __attribute__((aligned(16))) Quad_1DD548 { s32 v[4]; };
struct __attribute__((packed)) Pack4_1DD548 { s32 v; };
struct Locals_1DD548 { Quad_1DD548 pts[10]; Pack4_1DD548 c; };

void func_00130B48(void* a0, void* a1, void* a2, void* a3, s32 n, void* out, f32 w0, f32 w1, f32 w2);
void func_001DD3E0(void* a, void* b, void* c, s32 d, s32 e);

extern u8 D_00274738[];

void func_001C06A0(s32 a, s32 b, f32 x);
void func_0011D928(s32 a);


void* func_0018D5C0(u32 n);

s32 func_001DDA80(void* p);

struct Obj_1DC9A0;
struct Alloc_1DC9A0;

ConeVolume* func_0011E580(Alloc_1DC9A0* a0, Obj_1DC9A0* a1, void* a2, s32 a3, s32 a4);
void func_00184768(ConeVolume* p, s32 v);
void func_001847F0(ConeVolume* p, void* q);
void func_00184858(ConeVolume* p, f32 v);
void func_00184818(ConeVolume* p, f32 v);
void func_00184878(ConeVolume* p, f32 v);
void func_00184838(ConeVolume* p, f32 v);
void func_00184898(ConeVolume* p, f32 v);
void func_001848B8(ConeVolume* p, void* q);
void func_00184990(ConeVolume* p, void* q);

extern f32 D_0026185C;

void func_001DC710(Contacts03* node, Contacts03** head);
void func_001DC7B0(Contacts03* node, Contacts03** head);
ContactRow03* func_00138788(void* owner, Contacts03* h, Contacts03* handle);
void func_001861E8(void* a, Contact03* b);
void func_00129DF8(void* self);
void func_001B5F28(void* list, void* item);

typedef u64 Q_1DD3E0 __attribute__((mode(TI)));
struct __attribute__((aligned(16))) Quad_001DD3E0 { f32 x, y, z, w; };
struct __attribute__((packed)) Word_001DD3E0 { s32 v; };
struct Vec3_001DD3E0 { f32 x, y, z; };
struct Locals_001DD3E0 { Quad_001DD3E0 buf[4]; Word_001DD3E0 tmp; };

extern Vec3_001DD3E0 D_0026ABF0;
extern Vec3_001DD3E0 D_0026AC00;

Q_1DD3E0 func_00188740(u8* self, Q_1DD3E0 q);
s32 func_001DD218(Quad_001DD3E0* out);
void func_001AE3B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, void* tmp, s32 k);

struct Obj_1DD758 { s32 f0; };

u32 func_001601D8(Obj_1DD758* a0);

struct Obj_1DD7A0 { s32 f0; };

u32 func_001601D8(Obj_1DD7A0* a0);

s32 func_0016E0F0(s32 bits);

void func_0016E118(s32 n);
f32 func_00205778(f32 a, f32 b);
void func_00188850(const Vec02* t, void* out, f32 x);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001DFBE0(void* self, s32 flag);

struct Pa_1DE910;
extern f32 D_00261858[];
void func_001D7098(OwnerMessage* l, s32 zero, Collider* c);
void func_001861E8(Pa_1DE910* a0, Contact03* a1);
struct Pair_001DCD28 { s32 key; s32 count; };

struct Desc_001DCD28 { s32 pad0; s32 key; };

struct Obj_001DCD28;
typedef void (*VFn_001DCD28)(Obj_001DCD28* self);
struct Obj_001DCD28 { VFn_001DCD28* vtbl; u8 pad[0x2D8 - 4]; s32 f2D8; };

struct Node_001DCD28 {
    Desc_001DCD28* desc;
    u8 pad0[0x334 - 4];
    s32 flag334;
    u8 pad1[0x374 - 0x338];
    Node_001DCD28* next;
};

Obj_001DCD28* func_00183058(Node_001DCD28* node, World* self, void* z);

extern f32 D_00261858[];

void func_001B64D8(StateTrigger* h, s32 b);
void func_00188850(const Vec02* tab, void* out, f32 v);

struct Arg_001DD710 { s32 pad; };
u32 func_001601D8(Arg_001DD710* a);

extern f32 D_00261858[];

struct Plane_1DD218 { f32 x, y, z, w; };

float D_00275140[4] = {1.0f, 0.0f, -0.75f, 0.0f};
float D_00275150[4] = {0.699999988f, 0.300000012f, 0.0f, 0.0f};
float D_00275160 = 650.0f;
float D_00275164 = 100.0f;
float D_00275168 = -100.0f;
float D_0027516C = 50.0f;
float D_00275170[2] = {-10.0f, 0.0f};
float D_00275178[4] = {250.0f, 0.0f, 1.0f, 4500.0f};
float D_00275188 = 10.0f;
float D_0027518C = 50.0f;
float D_00275190[4] = {0.0f, 45.0f, 0.0f, 0.0f};
float D_002751A0[4] = {0.0f, 2.5f, 0.0f, 0.0f};
float D_002751B0[4] = {0.0f, 7.5f, 0.0f, 0.0f};
float D_002751C0[4] = {0.0f, 4.0f, 0.0f, 0.0f};
float D_002751D0 = 850.0f;
s32 D_002751D4 = 60;
float D_002751D8 = 1.25f;
float D_002751DC = 0.75f;
float D_002751E0[4] = {1.35000002f, 0.0f, -0.349999994f, 0.0f};
float D_002751F0[4] = {1.0f, 1.35000002f, 0.0f, 0.0f};
float D_00275200[4] = {1.5f, 0.0f, -0.5f, 0.0f};
float D_00275210[4] = {1.0f, 1.5f, 0.0f, 0.0f};
float D_00275220[4] = {9000.0f, 0.0f, -9000.0f, 0.0f};
float D_00275230[4] = {0.0f, 9000.0f, 0.0f, 0.0f};
float D_00275240[4] = {1.0f, -1.0f, 0.0f, 0.0f};
f32 D_00275250[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
};
f32 D_00275290[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
ObjectLink D_002752A0[20] = {
    { 4, 0x416, 0x6B0 }, { 4, 0x417, 0x710 }, { 4, 0x418, 0x770 }, { 4, 0x419, 0x7D0 },
    { 0, 0x41A, 0x6B8 }, { 0, 0x41B, 0x718 }, { 0, 0x41C, 0x778 }, { 0, 0x41D, 0x7D8 },
    { 6, 0x41E, 0x6B4 }, { 6, 0x41F, 0x714 }, { 6, 0x420, 0x774 }, { 6, 0x421, 0x7D4 },
    { 0, 0x422, 0x690 }, { 2, 0x428, 0xB28 }, { 2, 0x429, 0xB2C }, { 2, 0x42A, 0xB44 },
    { 2, 0x42B, 0xB4C }, { 0x22, 0x423, 0xB14 }, { 0x20, 0x424, 0xB18 }, { 0x20, 0x425, 0xB1C }
};
float D_00275390 = 1.0f;
f32 D_00275394 = 2.0f;
Vec02 D_002753A0 = { 0.0f, 30.0f, 3.0f, 0.0f };
float D_002753B0[4] = {0.0f, 0.00999999978f, 0.0f, 0.0f};
float D_002753C0[2] = {0.0f, 45.0f};
float D_002753C8 = 15.0f;
float D_002753CC = 90.0f;
float D_002753D0[4] = {0.0f, 0.25f, 0.75f, 0.0f};
float D_002753E0[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float D_002753F0[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float D_00275400[4] = {0.0f, 2.5f, 0.25f, 0.0f};
float D_00275410 = 6000.0f;
float D_00275414 = 11250.0f;
float D_00275418 = 7.0f;
float D_0027541C = 2500.0f;
f32 D_00275420[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 D_00275430[4] = { 0.5f, 1.0f, 0.0f, 0.0f };
f32 D_00275440[2] = { 0.5f, 1.0f };
f32 D_00275448[4] = { 4000.0f, 0.0f, 2.0f, 0.0f };
f32 D_00275458[6] = { 2000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
f32 D_00275470[4] = { 0.0f, 0.0333333313f, 0.0f, 0.0f };
f32 D_00275480[2] = { 0.0f, 50.0f };
f32 D_00275488 = -10.0f;
f32 D_00275490[4] = { 0.05f, 0.0f, 0.25f, 0.0f };
f32 D_002754A0[4] = { 1.5f, 2.5f, 0.0f, 0.0f };
f32 D_002754B0[4] = { 1000.0f, -0.5f, 0.0f, 0.0f };
f32 D_002754C0[2] = { 0.0f, 625.0f };
ValueRange D_002754C8 = { -1300.0f, 1300.0f };
f32 D_002754D0[3] = { 1125.0f, 0.0f, 0.100000001f };
f32 D_002754DC = 750.0f;
f32 D_002754E0[2] = { 1.0f, 0.0f };
f32 D_002754E8[3] = { 8.0f, 0.0f, 0.25f };
f32 D_002754F4 = 0.7f;
f32 D_002754F8 = 0.5f;
f32 D_00275500[2] = { 0.400000006f, 0.800000012f };
f32 D_00275508[2] = { 0.0500000007f, 0.300000012f };
f32 D_00275510[2] = { 0.100000001f, 0.400000006f };
f32 D_00275518[3] = { 10.0f, 0.0f, 0.100000001f };
f32 D_00275524 = 4000.0f;
Vec02 D_00275530 = { -0.5f, 0.699999988f, 0.0f, 0.0f };
f32 D_00275540[4] = { 1.0f, -0.5f, 0.0f, 0.0f };
f32 D_00275550[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_00275560[4] = { -0.5f, 2.0f, 0.0f, 0.0f };
f32 D_00275570[4] = { 0.5f, 4.0f, 0.0f, 0.0f };
f32 D_00275580[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_00275590[4] = { 1.0f, -0.600000024f, 0.0f, 0.0f };
f32 D_002755A0[2] = { 0.25f, 1.0f };
f32 D_002755A8 = 1.10000002f;
f32 D_002755AC = 1000.0f;
f32 D_002755B0[4] = { 0.5f, 0.25f, 0.0f, 0.0f };
f32 D_002755C0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_002755D0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002755E0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002755F0[2] = { 0.0f, 1.0f };
f32 D_002755F8 = 0.75f;
f32 D_00275600[4] = { 2000.0f, 0.0f, 2000.0f, 0.0f };
f32 D_00275610 = 0.5f;
f32 D_00275614 = 0.00200000009f;
f32 D_00275618 = 800.0f;
f32 D_00275620[4] = { 2000.0f, 0.0f, 0.150000006f, 0.0f };
s32 D_00275630[4] = { 1, 0, 0, 0 };
f32 D_00275640[4] = { 0.0f, 255.0f, 255.0f, 0.0f };
f32 D_00275650 = 0;
f32 D_00275654 = 255.0f;
f32 D_00275658 = 240.0f;
f32 D_0027565C = 0;
f32 D_00275660 = 180.0f;
Vec02 D_00275670 = { -0.2f, 0.3f, -1.0f, 0.0f };
f32 D_00275680[4] = { 100.0f, -150.0f, 500.0f, 0.0f };
f32 D_00275690[2] = { 500.0f, 2500.0f };
f32 D_00275698[2] = { 500.0f, 2500.0f };
f32 D_002756A0[4] = { 500.0f, 2500.0f, 0.0f, 0.0f };
Plane_1DD218 D_002756B0[6] = {
    { 1.0f, 0.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f },
    { 0.0f, -1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 1.0f }
};
World* D_00275710 = 0;
s32 D_00275714 = 0;
s32 D_00275718 = 0;
s32 D_0027571C = 0;
s32 D_00275720 = 0;
s32 D_00275724 = 0;
s32 D_00275728 = 0;

ASM_FUNC(func_001D62E0);

s32 func_001D65D8(Player* self)
{
    if (self->f2220 != 4) {
        return self->f26C4 != 0;
    }
    if (self->f2228 < 45) {
        return 1;
    }
    return 2;
}

ASM_FUNC(func_001D6608);

ASM_FUNC(func_001D66A8);

ASM_FUNC(func_001D6A18);

ASM_FUNC(func_001D6B18);

void func_001D6CB0(Player* self)
{
    StandIn* obj = (StandIn*)self->f1518;
    if (obj != 0) {
        Node_1D6CB0* s0 = 0;
        u32 i = 0;
        while (i < 4) {
            s0 = (Node_1D6CB0*)self->f1508[i];
            if (s0 != 0 && IsObjectAttached(s0) != 0) {
                break;
            }
            i++;
        }
        if (i >= 4) {
            s0 = (Node_1D6CB0*)self->f1504;
        }
        obj->desc->m02(obj);
        ((VFnB)((void**)obj->desc)[25])(obj, 0);
        ((VFnB)((void**)obj->desc)[35])(obj, s0);
        obj->f690 = g_gameClock[1];
        obj->f694 = 1;
        if (s0 != self->f1504) {
            ((VFnA)s0->vtbl[7])(s0);
        }
    }
}

s32 func_001D6DA0(StandIn* self, s32 value)
{
    if (value == (s32)g_player) {
        return 1;
    }
    return TestCollidersMayContact(self, value);
}

ASM_FUNC(func_001D6DD8);

void func_001D7018(StandIn* self)
{
    func_0013BA70(self);
    self->f694 = 0;
}

void func_001D7040(StandIn* self, s32 kind, ObjectMessage* ref)
{
    HandleChildGroupNotification(self, kind, ref);
    if (kind == 10 && ref->target == self) {
        ((StandIn*)ref->target)->f694 = 0;
    }
}

void func_001D7098(OwnerMessage* self, s32 mode, s32 owner) { func_001F5C0C(self, 0, 0x10); self->owner = owner; self->mode = mode; self->c = owner; }

ASM_FUNC(func_001D70E8);

OutputBuffer* func_001D7100(OutputBuffer* self, s32 handle)
{
    self->handle = handle;
    self->targetWord = 0;
    self->capacity = 0;
    self->used = 0;
    self->count = 0;
    self->pending = 0;
    return self;
}

OutputBuffer* func_001D7120(OutputBuffer* self, u8* target, s32 capacity) { self->target = target; self->capacity = capacity; self->used = 0; self->handle = -1; self->count = 0; self->pending = 0; return self; }

void func_001D7148(OutputBuffer* a0, s32 a1)
{
    FlushOutputBuffer(a0, a1);
    if (a1 & 1) FreeObjectMemory(a0);
}

s32 func_001D7190(OutputBuffer* self, void* src, s32 size)
{
    s32 n = size;
    s32 done = 0;

    if (self->target != 0 && self->capacity != 0 && n != 0) {
        s32 avail = self->capacity - self->used;
        if (avail < n) {
            n -= avail;
        }
    }
    if (n == 0) {
        return 0;
    }
    if (self->target != 0) {
        CopyMemory(self->target + self->used, src, n);
        self->used += n;
        done = n;
    } else if (n > 0) {
        do {
            s32 room = 0x400 - self->pending;
            s32 rem = n - done;
            s32 take = (room < rem) ? room : rem;
            if (take != 0) {
                CopyMemory((u8*)self + (self->pending + 0x18), (u8*)src + done, take);
                done += take;
                self->pending += take;
            }
            if (self->pending == 0x400) {
                FlushOutputBuffer(self);
            }
        } while (done < n);
    }
    self->count += done;
    return n;
}

void func_001D72C8(OutputBuffer* self)
{
    u8 buf[0x90];
    s32 done;
    u8* p;
    s32 chunk;
    s32 rem;

    if (self->pending == 0) {
        return;
    }
    if (self->targetWord != 0) {
        return;
    }
    if (self->handle < 0) {
        p = self->buf;
        for (done = 0; done < self->pending; done += chunk) {
            rem = self->pending - done;
            chunk = 0x80;
            if (!(rem > 0x7F)) {
                chunk = rem;
            }
            CopyMemory(buf, p, chunk);
            p += chunk;
            buf[chunk] = 0;
            PrintBuffered((void*)"%s", buf);
        }
    } else {
        WriteFile(self->handle, self->buf, self->pending);
    }
    self->pending = 0;
}

void func_001D73A8(PathFollower* self)
{
    InitSwitchedCollider(self);
    self->f614 = 50.0f;
    self->f610 = 50.0f;
    self->f618 = 3000.0f;
    self->f61C = 1300.0f;
    self->f868 = 2.0f;
    self->fB04 = 3;
    (*(Quad_1D73A8*)&self->v620) = *(Quad_1D73A8*)D_00275290;
    CopyMemory(self->f630, D_00275250, 0x40);
    ResetPathFollower(self);
}

void func_001D7440(PathFollower* self)
{
    Ent_1D7440* buf[16];
    s32 id0;
    s32 id1;
    s32 id2;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x14, D_002752A0);
    self->f694 = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    if (((Snd_1D7440*)self->fB44) != 0) {
        StateTrigger* v = CreateStateWalker(((Snd_1D7440*)self->fB44), self, -1, 0);
        self->fB48 = v;
        SetStateWalkerTarget(v, self->fB30 == 1 ? 0x484 : 0x384);
    }
    switch (g_currentWorld->f1D70) {
    case 3:
        id0 = self->f550 ? 0x1D2 : 0x1AD;
        id1 = 0x1BB;
        id2 = 0x1AF;
        goto spawn;
    case 5:
        id0 = self->f550 ? 0x2A6 : 0x280;
        id1 = 0x27F;
        id2 = 0x27D;
        goto spawn;
    case 6:
        id0 = self->f550 ? 0x2DE : 0x2DC;
        id1 = 0x2DB;
        id2 = 0x2DD;
    spawn:
        StartSoundEffect(id0, self->fB80, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id1, self->fB84, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id2, self->fB7C, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        {
            f32 r = RandomFloatInRange(-0.1f, 0.1f);
            self->fB8C = self->fB90 = self->fB94 = self->fB98 = r;
        }
        break;
    default:
        break;
    }
    {
        void* c = FindFirstObjectById(g_currentWorld, 0x104, 7, self);
        if (c != 0) {
            self->f594 = 200.0f;
            self->fB78 = c;
            self->f598 = c;
        }
    }
    if (self->fB30 == 1) {
        s32 n = GatherObjectsByMode(self->world, 0x105, 0x426, 0, 0x10, buf);
        for (s32 i = 0; i < n; i++) {
            buf[i]->vt->fn6C(buf[i], self);
        }
        T217D_E30* boxA = &D_00272430;
        T217D_E30* boxB = &D_002726B0;
        ((U32P*)&boxA->own)->v = 0;
        ((U32P*)&boxB->own)->v = 0;
        boxA->target = &boxA->own;
        boxB->target = &boxB->own;
    }
    for (s32 k = 0; k < 4; k++) {
        Slot_1D7440* s = (Slot_1D7440*)&self->f6B0[k];
        s->q = s->p->q;
    }
    ResetPathFollower(self);
}

ASM_FUNC(func_001D7778);

f32 func_001D8470(s32 count, ValueRange* spans, f32 x)
{
    if (IsInsideAnyRange(count, spans, x) == 0) {
        return x;
    }
    f32 bestDist = 3.4028234663852886e+38f;
    f32 best = bestDist;
    if (count > 0) {
        ValueRange* s = spans;
        s32 n = count;
        do {
            f32 d = __builtin_fabsf(x - s->lo);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->lo) == 0) {
                    best = s->lo;
                    bestDist = d;
                }
            }
            d = __builtin_fabsf(x - s->hi);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->hi) == 0) {
                    best = s->hi;
                    bestDist = d;
                }
            }
            s++;
            n--;
        } while (n != 0);
    }
    return best;
}

void func_001D8578(PathFollower* self)
{
    if (self != GetActiveSwitchedCollider()) {
        self->f85C = ApproachValueWithRamp((u8*)D_00275490, 0, self->f85C, self->f860, g_gameClock[2]);
        if (!(g_gameClock[1] < self->f864)) {
            f32 one = 1.0f;  // hoisted: retail holds 1.0f in $f3 before the multiply
            s32 idx = 3 * (self->fB00 - 1) + ((Sub_1D8578*)self->fAF8)->n0C;
            f32 t = (f32)idx * 0.1f;
            f32 w;
            if (t < 0.0f) {
                w = 0.0f;
            } else if (one < t) {
                w = one;
            } else {
                w = t;
            }
            Tri_1D8578* q = (Tri_1D8578*)((u8*)self + 0x670);
            f32 val = q->a + w * (q->b + w * q->c);
            f32 lo = self->f680;
            f32 hi = self->f684;
            if (val < lo) {
                val = lo;
            } else if (hi < val) {
                val = hi;
            }
            self->f860 = val;
            f32 r = RandomFloatInRange(-0.05f, 0.05f);
            self->f860 = self->f860 + r;
            f32 r2 = RandomFloatInRange(D_002754A0[0], D_002754A0[1]);
            self->f864 = g_gameClock[1] + r2;
        }
    }
}

f32 func_001D86F8(f32 x, f32 lim, f32 base)
{
    f32 d = lim - base;
    if (x * 0.5f < d)
        d = d - x;
    else if (d < x * -0.5f)
        d = d + x;
    return d;
}

s32 func_001D8740(PathFollower* self, PathFollower* other)
{
    s32 d = self->fB00 - other->fB00;
    if (d > 0) return 1;
    if (d < 0) return 0;
    d = ((Sub_1D8740*)self->fAF8)->n0C - ((Sub_1D8740*)other->fAF8)->n0C;
    if (d > 0) return 1;
    if (d < 0) return 0;
    f32 r = GetWrappedDifference(self->f834, self->f83C, other->f83C);
    return 0.0f < r;
}

ASM_FUNC(func_001D87C8);

ASM_FUNC(func_001D8BD0);

void func_001D8D90(PathFollower* self)
{
    f32 a = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 b = WrapAngle(self->f694 - a);
    f32 c = ClampToMagnitude(D_002754F8 * b, D_002754F4);
    self->f69C = ApproachAngleWithRamp((u8*)D_002754E8, 0, self->f69C, c, g_frameDt);
    for (u32 i = 0; i < 4; i++) {
        Slot19* s = &self->f6B0[i];
        if ((s32)i < 2) {
            s->f50 = self->f698 / self->f610;
        } else {
            s->f50 = self->f698 / self->f614;
        }

    }
}

ASM_FUNC(func_001D8E40);

void func_001D92F0(PathFollower* self)
{
    self->f854 = g_gameTime;
    self->f858 = self->f858 - 1;
    Sub_1D92F0* s = (Sub_1D92F0*)self->fB14;
    if (s != 0) {
        s->vtbl[6](s);
    }
}

void func_001D9338(PathFollower* self)
{
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    s32 idx = self->fB00 - 1;
    f32 f = (f32)(idx * 3 + ((Inner_1D9338*)self->fAF8)->value) * 0.1f;
    if (f < lo) {
        f = lo;
    } else if (hi < f) {
        f = hi;
    }
    s32 s0 = self->fB0C - self->fB08;
    s32 t = 0;
    if (s0 >= 3) {
        s32 mk = 1 << (s0 & 7);
        t = g_currentEntry->bits74[s0 / 8] & mk;
    }
    if (s0 < 3 || t) {
        RaiseScatterLevels(g_scatterController, f);
    }
    if (s0 >= 0) {
        do {
            G27C230* g = g_currentEntry;
            u8* bb = g->bits74;
            u8* byte = bb + s0 / 8;
            s32 mask = 1 << (s0 & 7);
            if ((*byte & mask) == 0) {
                *byte = (u8)(*byte | mask);
                g->count70++;
            }
            s0--;
        } while (s0 >= 0);
    }
}

INCLUDE_ASM(func_001D9488);

ASM_FUNC(func_001D9678);

ASM_FUNC(func_001D9AC8);

void func_001D9C98(PathFollower* self, f32 t)
{
    s32 local = 0;
    UpdateSwitchedCollider(self, t);
    if (self->fB34 != 1) {
        if (self->fB34 < 2) {
            if (self->fB34 == 0) {
                self->f698 = 0;
            }
        }
    } else {
        UpdatePathFollowerPace(self);
        AdvancePathFollowerAlongPath(self, &local);
        ComputePathFollowerHeadingTarget(self);
    }
    UpdatePathFollowerSound(self, t);
    SteerPathFollower(self);
    func_001D8E40(self);
    AdvancePathFollowerEntry(self, local);
    ProcessPathFollowerContacts(self);
    if (self->rot.r[2].z > 0.5f) {
        self->f850 = g_gameTime;
    }
    if (self->fB34 != 0) {
        ClearRootTries(self);
    }
}

ASM_FUNC(func_001D9D78);

void func_001DA170(PathFollower* self)
{
    s32 a = 0;
    s32 b = 0;
    switch (self->fB30) {
    case 0: {
        Res_1DA170* r = (Res_1DA170*)FindFirstObjectById(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->f48;
            s32 code;
            GetStateWalkerTargetKey(dev, &code);
            if (code == -1) {
                GetStateWalkerCurrentKey(dev, &code);
            }
            if (code < 0x431) {
                if (code >= 0x42F) {
                    a = AreMenusAndFadeClear();
                }
            }
        }
        break;
    }
    case 1:
        b = AreMenusAndFadeClear();
        break;
    }
    if (a != 0) {
        D_0026D848.vt->m14(&D_0026D848);
        D_0026D5C8.vt->m14(&D_0026D5C8);
        D_0026DAC8.vt->m14(&D_0026DAC8);
    } else {
        D_0026D848.vt->m15(&D_0026D848);
        D_0026D5C8.vt->m15(&D_0026D5C8);
        D_0026DAC8.vt->m15(&D_0026DAC8);
    }
    if (b != 0) {
        D_00272430.vt->m14(&D_00272430);
        D_002726B0.vt->m14(&D_002726B0);
    } else {
        D_00272430.vt->m15(&D_00272430);
        D_002726B0.vt->m15(&D_002726B0);
    }
}

void func_001DA310(PathFollower* self) { self->f6A0++; }

ASM_FUNC(func_001DA320);

ASM_FUNC(func_001DA6E0);

ASM_FUNC(func_001DA7E0);

ASM_FUNC(func_001DAA18);

void func_001DAC20(PathFollower* self)
{
    u32 i;
    Quad_001DAC20 q;
    UpdateColliderBounds(self);
    for (i = 0; i < 4; i++) {
        Slot_001DAC20* slot = (Slot_001DAC20*)&self->f6B0[i];
        if (slot->ptr != 0) {
            f32 f;
            q = *(Quad_001DAC20*)((u8*)slot->ptr + 0x190);
            func_00128018(self, 0, &q, &q);
            f = ((s32)i < 2) ? self->f610 : self->f614;
            func_001B8420(self, &q, f);
        }
    }
}

void func_001DACB0(PathFollower* self, void* a, void* b)
{
    if (((Target_1DACB0*)self->fB78) != 0) {
        SetAgentMainClip(((Target_1DACB0*)self->fB78), 0);
        Target_1DACB0* t = ((Target_1DACB0*)self->fB78);
        t->vtbl[82](t, a, b);
    } else {
        StartSwitchedColliderEffect(self, a, b);
    }
}

ASM_FUNC(func_001DAD28);

void func_001DAE18(PathFollower* self)
{
    RecomputeColliderFrame(self);
    FindPathFollowerPathPosition(self);
}

void func_001DAE48(void)
{
    CaptureColliderPose();
}

void func_001DAE68(PathFollower* self, void* v)
{
    HandleSwitchedColliderActivation(self, v);
    if (v != 0) {
        T217D_E30* a = &D_0026D5C8;
        *(void**)(D_0026DAAC) = (u8*)self + 0x858;
        T217D_E30* b = &D_0026DAC8;
        a->target = (s32*)((u8*)self + 0xB00);
        a->limit = (s32*)((u8*)self + 0xB04);
        b->target = (s32*)((u8*)self + 0xB08);
        b->limit = (s32*)((u8*)self + 0xB0C);
        SetWorldActiveFollower(*(void**)((u8*)self + 0x14), self);
    } else {
        if (self->fB34 == 2) {
            SetPathFollowerMode(self, 0);
        }
    }
}

void func_001DAF08(PathFollower* self, s32 code, Rec_1DAF08* rec)
{
    HandleSwitchedColliderNotification(self, code, rec);
    if (code == 0xE && rec->kind == 0x426) {
        T217D_E30* a = &D_00272430;
        s32 lim = D_002751D4;
        if (a->own < lim) {
            T217D_E30* b = &D_002726B0;
            if (b->own < lim) {
                if (rec->link->owner == self) {
                    a->own = a->own + 1;
                } else {
                    b->own = b->own + 1;
                }
            }
        }
    }
}

void func_001DAFB8(PathFollower* self, Arg_1DAFB8* arg)
{
    self->f830 = arg;
    Obj_1DAFB8* o = arg->obj;
    if (o->vtbl[10]) ((VFn7_1DAFB8)o->vtbl[10])(o, (u8*)self + 0x100, 0, 0, 0, (u8*)self + 0x838, 0);
    FindPathFollowerPathPosition(self);
    self->f844 = self->f840;
    self->f834 = ((VFnF_1DAFB8)((Arg_1DAFB8*)self->f830)->obj->vtbl[8])(((Arg_1DAFB8*)self->f830)->obj);
    for (s32 i = 0; i < self->f870; i++) {
        Entry_1DAFB8* e = &((Entry_1DAFB8*)self->f874)[i];
        if (e->flag == 0) {
            s32 loc[4];
            GetObjectWorldPosition(e->ptr, loc);
            Obj_1DAFB8* o2 = ((Arg_1DAFB8*)self->f830)->obj;
            if (o2->vtbl[10]) ((VFn7_1DAFB8)o2->vtbl[10])(o2, loc, 0, 0, 0, 0, e->at10);
        }
    }
}

void func_001DB0C8(u8* self, Outer_1DB0C8* obj)
{
    s32 loc[4];
    Inner_1DB0C8* inner;

    *(Outer_1DB0C8**)(self + 0x848) = obj;
    inner = obj->inner;
    if (inner->vtbl[10] != 0) {
        inner->vtbl[10](inner, self + 0x100, 0, loc, 0, self + 0x84C, 0);
    }
}

void func_001DB110(PathFollower* self, void* item)
{
    if (item == 0) {
        return;
    }
    s32 n = self->f870;
    if ((u32)n >= 16) {
        return;
    }
    self->f870 = n + 1;
    Entry_1DB110* e = &((Entry_1DB110*)self->f874)[n];
    e->f4 = item;
    e->f0 = 0;
    if (self->fAF4 == 0) {
        self->fAF8 = e;
        self->fAF4 = e;
        e->f14 = e;
    } else {
        e->f14 = ((Entry_1DB110*)self->fAF4)->f14;
        ((Entry_1DB110*)self->fAF4)->f14 = e;
        e->fC = e->f14->fC + 1;
    }
    if (self->f830 != 0) {
        Quad_1DB110 tmp;
        GetObjectWorldPosition(item, &tmp);
        VObj_1DB110* o = ((Node_1DB110*)self->f830)->f34;
        VFn_1DB110 fn = o->vtbl[10];
        if (fn != 0) {
            fn(o, &tmp, 0, 0, 0, 0, &e->f10);
        }
    }
}

void func_001DB1E8(PathFollower* self, s32 a, s32 b, s32 c, f32 x, f32 y) { if (a && (u32)self->f870 < 16) { Entry_001DB1E8* e = &((Entry_001DB1E8*)self->f874)[self->f870]; self->f870++; e->a = a; e->active = 1; e->x = x; e->y = y; e->b = b; e->c = c; } }

void func_001DB238(PathFollower* self, s32 mode)
{
    if (mode != self->fB34) {
        *(s32*)((u8*)self + 0xB34) = mode;
        *(f32*)((u8*)self + 0xB38) = g_gameTime;
        if (mode == 2 && self != GetActiveSwitchedCollider()) {
            ActivateSwitchedCollider(self);
        }
    }
}

void func_001DB290(Obj_1DB290* self)
{
    self->fB00 = 1;
    self->fAF8 = self->fAF4;
    self->f858 = 0;
    self->f854 = -10.0f;
    self->f864 = -10.0f;
    self->f86C = -10.0f;
    self->fB10 = -10.0f;
    G27C230* rec = g_currentEntry;
    f32 t = ((Poly_1DB290*)&self->f620)->Eval(rec->dt);
    f32 l = g_unitRange.lo;
    f32 h = g_unitRange.hi;
    f32 x;
    if (t < l)
        x = l;
    else if (h < t)
        x = h;
    else
        x = t;
    f32 y = 1.0f - x;
    u8* p630 = self->v630;
    u8* p650 = self->v650;
    u8* p670 = self->v670;
    V128_1DB290 a, b, c, d;
    V128_1DB290 a2, b2, c2, d2;
    func_00118CF0(&a, y);
    a2 = a;
    CopyQuadword(&b, p630);
    b2 = b;
    func_00118CF0(&c, x);
    c2 = c;
    CopyQuadword(&d, p650);
    d2 = d;
    StoreQuadword(p670, AddWeightedVectors(a2, b2, c2, d2));
    ((Bounds_1DB290*)&self->f680)->Blend(y, *(Bounds_1DB290*)&self->f640, x, *(Bounds_1DB290*)&self->f660);
    f32 r = ((Clamp2_1DB290*)&self->f680)->Clamp(*(f32*)p670);
    self->f860 = r;
    self->f85C = r;
}

ASM_FUNC(func_001DB448);

ASM_FUNC(func_001DB460);

void func_001DB480(u8* self)
{
    u32 i;
    for (i = 0; i < 0x200; i++) {
        SetListLinkOffset(self + 0x84 + i * 0xC, 0xC);
    }
}

void func_001DB4C8(World* self)
{
    f32 x;
    InitObject(self);
    SetIopChannel2Setting(self, 0, 0);
    self->buf1AD8 = (void*)AllocateFrontMemory(0x4800);
    self->buf1ADC = AllocateZeroedFrontMemory(0x10000);
    InitContactTables(self);
    InitSlotPool(SUB(0x1AF0), 0x10, 0x400);
    InitSlotPool(SUB(0x1AFC), 0xE0, 0x100);
    InitSlotPool(SUB(0x1B08), 0x10, 0x80);
    InitSlotPool(SUB(0x1B14), 0x14, 0x400);
    InitSlotPool(SUB(0x1B2C), 0x140, 0x180);
    InitAlignedSlotPool(SUB(0x1B40), 0x10C0, 0x80);
    InitSlotPool(SUB(0x1B4C), 0x580, 0x20);
    InitSlotPool(SUB(0x1B58), 0xEC, 0x100);
    InitSlotPool(SUB(0x1B20), 0xD0, 0x400);
    InitSlotPool(SUB(0x1BA0), 0x90, 0x80);
    InitSlotPool(SUB(0x1BB8), 0xC, 0x20);
    InitSlotPool(SUB(0x1B88), 0x40, 0x100);
    InitSlotPool(SUB(0x1BF4), 0x2E0, 0x20);
    InitSlotPool(SUB(0x1BD0), 0x70, 0x20);
    InitSlotPool(SUB(0x1C0C), 0x8, 0x80);
    InitSlotPool(SUB(0x1C18), 0x14, 0x100);
    self->buf1ED4 = (void*)AllocateFrontMemory(0x1000);
    SetListLinkOffset(SUB(0x48), 0x1C);
    SetListLinkOffset(SUB(0x54), 0x48);
    SetListLinkOffset(SUB(0x78), 0x48);
    SetListLinkOffset(SUB(0x60), 0x40);
    SetListLinkOffset(SUB(0x6C), 0x414);
    SetListLinkOffset(SUB(0x3C), 0x2D0);
    SetListLinkOffset(SUB(0x1B64), 0x34);
    SetListLinkOffset(SUB(0x1B70), 0x34);
    SetListLinkOffset(SUB(0x1B7C), 0x34);
    SetListLinkOffset(SUB(0x1B94), 0x10);
    SetListLinkOffset(SUB(0x1BAC), 0x64);
    SetListLinkOffset(SUB(0x1BC4), 0x4);
    SetListLinkOffset(SUB(0x1BE8), 0x410);
    SetListLinkOffset(SUB(0x1C00), 0xB8);
    SetListLinkOffset(SUB(0x1BDC), 0x64);
    SetListLinkOffset(SUB(0x1C3C), 0x2DC);
    SetListLinkOffset(SUB(0x1C48), 0x5DC);
    SetListLinkOffset(SUB(0x1C54), 0x374);
    SetListLinkOffset(SUB(0x1C60), 0x600);
    SetListLinkOffset(SUB(0x1C6C), 0x90);
    SetListLinkOffset(SUB(0x1C78), 0x56C);
    SetListLinkOffset(SUB(0x1C84), 0x50);
    SetListLinkOffset(SUB(0x1C90), 0x38);
    SetListLinkOffset(SUB(0x1C9C), 0x38);
    SetListLinkOffset(SUB(0x1CA8), 0xAF0);
    SetListLinkOffset(SUB(0x1CB4), 0x630);
    SetListLinkOffset(SUB(0x1CC0), 0x630);
    SetListLinkOffset(SUB(0x1C24), 0xC);
    SetListLinkOffset(SUB(0x1C30), 0xC);
    SetListLinkOffset(SUB(0x1CCC), 0xC10);
    SetListLinkOffset(SUB(0x1CD8), 0x34);
    x = -1500.0f;
    if (g_buttonCodeFlags & 4) {
        x = -900.0f;
    }
    SetWorldGravityZ(self, x);
    self->f1D64 = 0x10;
    self->f1D65 = 0x10;
    self->f1D66 = 0x40;
    self->f1D68 = 50.0f;
    self->f1D70 = -1;
    self->f1D74 = 0;
    self->f2308 = 15.0f;
    self->f230C = 180.0f;
    self->f234C = 1.0f;
    self->f2350 = 1.0f;
    self->f2354 = 1;
    self->f235C = 0xF03FFFFF;
}

void func_001DB838(s32 a0)
{
    if (a0 != 0) {
        ActivateSwitchedColliderIndex(-1);
        g_switchedColliderCount = 0;
        g_player = 0;
        g_padSelectFlags = 0;
        UpdatePadRouting();
        ClearCameraObjectList(g_camera);
        ClearClass75List();
        ClearPointObjectList();
        ClearTargetVectorList();
        ClearObjectLists();
        StopAllSoundsAndWait();
        ResetScreenResources();
        ShutDownScriptValuePools();
        ResetElementStack(g_elementStack);
        ResetFrontMemory();
        u8* c = (u8*)&D_0026CE48;
        u8* e = (u8*)&g_timerElement;
        g_camera = 0;
        g_coloredTriangleSet = 0;
        g_stepScale = 1.0f;
        ((Word_1DB838*)(c + 0x274))->v = 0;
        ((Word_1DB838*)(e + 0x280))->v = 0;
        D_00261D38 = 0;
        *(s32*)(c + 0x278) = 0;
        *(s32*)(e + 0x28C) = 0;
    }
}

void func_001DB928(s32 a0, BufferedStream* self)
{
    s32 s2 = a0;
    s32 s3;
    s32 s0;
    if (self->mode == 1) {
        if (s2 == 0) {
            func_00137480(self, D_00275728);
            self->f14 -= D_00275728;
        }
        s3 = ReadBufferedS32(self);
        s0 = ReadBufferedS32(self);
    } else {
        s3 = ReadBufferedS32(self);
        s0 = ReadBufferedS32(self);
        if (s0 != D_00275724) s2 = 1;
        if (s2 == 0) {
            s32 v = self->f14 - D_00275728;
            self->f14 = (s2 < v) ? v : 0;
        }
    }
    s32 r = (s32)AllocateFrontMemory(s3);
    D_00275724 = s0;
    D_00275720 = s3;
    D_00275718 = r;
    D_0027571C = s2;
}

void func_001DBA38(Obj_1DBA38* self)
{
    if (D_0027571C != 0) {
        D_00275728 = self->f14;
        AlignBufferedStreamPosition(self, 0x10);
        ReadBufferedStreamBytes(self, D_00275720, D_00275718);
    }
}

ASM_FUNC(func_001DBA90);

void func_001DBAC0(void* self, void* a, void* b)
{
    SetCachedVoiceParam(a, b);
}

s32 func_001DBAE0(s32 unused, Id_1DBAE0 index)
{
    return GetCachedVoiceParam(index);
}

void* func_001DBB00(void* unused, void* a1, void* a2)
{
    return RefreshCachedVoiceParam(a1, a2);
}

s32 func_001DBB20(World* self, BaseObject* obj, u32 value) { return (obj->desc->flags & 2) && self->count38 >= 0xF7 && value == 0; }

void* func_001DBB50(u8* self)
{
    void* p = func_001B5EC0(self + 0x1B08);
    FillMemory(p, 0, 16);
    return p;
}

void func_001DBB90(u8* self, Attach03* node)
{
    if (node) {
        do {
            Attach03* next = node->nextOwn;
            PushFreeSlot(self + 0x1B08, node);
            node = next;
        } while (node);
    }
}

void* func_001DBBD8(u8* self)
{
    void* p = func_001B5EC0(self + 0x1B14);
    FillMemory(p, 0, 0x14);
    return p;
}

void func_001DBC18(u8* self, T219CHook* node)
{
    while (node != 0) {
        T219CHook* next = node->next;
        PushFreeSlot(self + 0x1B14, node);
        node = next;
    }
}

QueuedCall* func_001DBCC8(World* self, s32 a, s32 b, s32 c, s32 d);

void func_001DBC60(World* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    QueuedCall* n = self->f1EC8;
    if (n != 0) {
        do {
            if (n->k0 == a1 && n->k1 == a2 && n->k2 == a3 && n->k3 == a4) {
                return;
            }
            n = n->next;
        } while (n != 0);
    }
    AppendQueuedCall(self, a1, a2, a3, a4);
}

QueuedCall* func_001DBCC8(World* self, s32 a, s32 b, s32 c, s32 d)
{
    QueuedCall* e = (QueuedCall*)TakeCallRecord(self);
    e->k0 = a;
    e->k1 = b;
    e->k2 = c;
    e->k3 = d;
    if (self->f1ECC != 0) self->f1ECC->next = e;
    else self->f1EC8 = e;
    self->f1ECC = e;
    return e;
}

void func_001DBD40(World* self, u32 mask, s32 k0, s32 k1, s32 k2, s32 k3)
{
    QueuedCall* prev = 0;
    QueuedCall* removed = 0;
    QueuedCall* cur = self->f1EC8;
    QueuedCall* next;
    s32 bit;

    if (cur != 0) {
        do {
            next = cur->next;
            bit = 1;
            while (bit < 16) {
                if (mask & bit) {
                    switch (bit) {
                    case 1:
                        if (cur->k0 != k0) goto miss;
                        break;
                    case 2:
                        if (cur->k1 != k1) goto miss;
                        break;
                    case 4:
                        if (cur->k2 != k2) goto miss;
                        break;
                    case 8:
                        if (cur->k3 != k3) goto miss;
                        break;
                    }
                }
                bit <<= 1;
            }
            if (prev != 0) {
                prev->next = next;
            } else {
                self->f1EC8 = next;
            }
            if (next == 0) {
                self->f1ECC = prev;
            }
            cur->next = removed;
            removed = cur;
            goto advance;
        miss:
            prev = cur;
        advance:
            cur = next;
        } while (cur != 0);
    }
    ReleaseCallRecords(self, removed);
}

void func_001DBE48(World* self)
{
    while (self->f1EC8 != 0) {
        QueuedCall* node = self->f1EC8;
        if (node == self->f1ECC) self->f1ECC = 0;
        self->f1EC8 = node->next;
        node->next = 0;
        node->fn(node->k1, node->k2, node->k3);
        ReleaseCallRecords(self, node);
    }
}

void func_001DBEC8(World* self, f32 limit)
{
    ScriptValue a;
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&a);
    InitScriptValue(&q);
    MarkPoolLiveEnds(g_markStacks);
    LookupScriptVariable(self->f2C, self->f1EF8, 0, &a);
    R11B008Node* n;
    s32 found;
    if (a.tag != 0x1E) {
        goto fin;
    }
    {
        n = a.node;
        found = 0;
        while (n) {
            R11B008Node* e = n->node;
            f32 d = e->f - limit;
            if (d <= 0.0f) {
                found = 1;
                EvalScriptExpression(&t, e->next, self->f2C);
                AssignScriptValue(&q, &t);
                DestroyScriptValue(&t, 2);
                SetScriptValueTag(n, 0);
            } else {
                SetScriptValueFloat(e, d);
            }
            n = n->next;
        }
        if (!found) {
        fin:
            DestroyScriptValue(&q, 2);
            DestroyScriptValue(&a, 2);
            return;
        }
    }
    LookupScriptVariable(self->f2C, self->f1EF8, 0, &a);
    {
        R11B008Node* head = a.node;
        R11B008Node* prev = 0;
        for (n = a.node; n; n = n->next) {
            if (n->tag == 0x1E) {
                prev = n;
            } else if (prev) {
                prev->next = n->next;
            } else {
                head = n->next;
            }
        }
        if (head != a.node) {
            if (head) {
                SetScriptValueChain(&a, head);
            } else {
                SetScriptValueTag(&a, 0);
            }
            AssignScriptVariable(&t, self->f2C, self->f1EF8, &a);
            DestroyScriptValue(&t, 2);
        }
    }
    DestroyScriptValue(&q, 2);
    DestroyScriptValue(&a, 2);
}

void* func_001DC0C8(u8* self)
{
    void* p = func_001B5EC0(self + 0x1C0C);
    FillMemory(p, 0, 0x8);
    return p;
}

void func_001DC108(u8* owner, Touch03* node)
{
    while (node != 0) {
        Touch03* next = node->next;
        PushFreeSlot(owner + 0x1C0C, node);
        node = next;
    }
}

void func_001DC150(World* self, void* src, s32 n)
{
    struct Pair_1DC150 tmp;
    s32 i;
    s32 idx;

    tmp.n = n - 1;
    if (tmp.n > 0) {
        tmp.buf = AllocateFrontMemory(tmp.n * 4);
        for (i = 0; i < tmp.n; i++) {
            ((void**)tmp.buf)[i] = CreateObjectCopy(src, self, 0);
        }
    }
    idx = self->f1EFC;
    ((Pair_1DC150*)self->f1F00)[idx] = tmp;
    self->f1EFC = idx + 1;
}

s32 func_001DC208(World* self, s32 index) { Stack_001DC208* s = &((Stack_001DC208*)self->f1F00)[index]; s->count--; return s->values[s->count]; }

ASM_FUNC(func_001DC238);

ASM_FUNC(func_001DC4D0);

void func_001DC710(Contacts03* a0, Contacts03** a1) {
    Contacts03* next;
    if (a0->next == 0) {
        next = a0->prev;
    } else {
        a0->next->prev = a0->prev;
        next = a0->prev;
    }
    if (next != 0) {
        next->next = a0->next;
    } else {
        *a1 = a0->next;
    }
}

void func_001DC740(World* self)
{
    void* mem = AllocateZeroedFrontMemory(0x1000);
    self->tables = (Contacts03*)mem;
    self->freeTables = (Contacts03*)mem;
    for (s32 i = 0; i < 0x100; i++) {
        Contacts03* n = (Contacts03*)((u8*)self->tables + (i << 4));
        n->prev = (i < 1) ? 0 : n - 1;
        n->next = (i > 0xFE) ? 0 : n + 1;
    }
}

void func_001DC7B0(Contacts03* node, Contacts03** head)
{
    node->next = *head;
    node->prev = 0;
    if (*head != 0) {
        (*head)->prev = node;
    }
    *head = node;
}

Contacts03* func_001DC7D0(World* owner, Collider* self)
{
    Contacts03* n = owner->freeTables;
    UnlinkContactTable(n, &owner->freeTables);
    PushContactTable(n, &owner->usedTables);
    n->owner = self;
    return n;
}

void func_001DC828(World* owner, Contacts03* handle)
{
    ContactRow03* e = handle->head;
    if (e != 0) {
        void* freeList = &owner->pool1AF0;
        do {
            ContactRow03* next = e->next;
            ContactRow03* s1 = UnlinkContactRow(owner, e->other->contacts, handle);
            if (e->head != 0) {
                FreePooledContactChain(owner, e->head);
                if (!(e->other->flags538 & (1ULL << 55))) {
                    ClearRootTries(e->other);
                }
                if (!(s1->other->flags538 & (1ULL << 55))) {
                    ClearRootTries(s1->other);
                }
            }
            s1->head = 0;
            e->head = 0;
            PushFreeSlot(freeList, e);
            PushFreeSlot(freeList, s1);
            e = next;
        } while (e != 0);
    }
    handle->head = 0;
    Contacts03** hb = &owner->usedTables;
    s32 a3 = handle - owner->tables;
    Contacts03* p = *hb;
    if (p != 0) {
        do {
            s32 b = p - owner->tables;
            u8* tab = (u8*)owner->buf1ADC;
            u8* r1 = tab + (a3 << 8);
            u8* r2 = tab + (b << 8);
            r2[a3] = 0;
            r1[b] = 0;
            p = p->next;
        } while (p != 0);
    }
    handle->owner = 0;
    UnlinkContactTable(handle, hb);
    PushContactTable(handle, &owner->freeTables);
}

void func_001DC9A0(Obj_1DC9A0* self)
{
    ConeVolume* p;

    if (g_coneVolumeMask[0] & 1) {
        p = CreateTypedRecord((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeDirection(p, &D_00275670);
    }
    if (g_coneVolumeMask[0] & 2) {
        p = CreateTypedRecord((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 1);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeRange(p, D_00275690);
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
    if (g_coneVolumeMask[0] & 4) {
        p = CreateTypedRecord((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 2);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeDirection(p, &D_00275670);
        SetConeVolumeRange(p, D_00275698);
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
    if (g_coneVolumeMask[0] & 8) {
        p = CreateTypedRecord((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 3);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeDirection(p, &D_00275670);
        SetConeVolumeRange(p, D_002756A0);
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
}

void func_001DCCC0(void* self)
{
    s32 n = ReadBufferedU32(self);
    if (D_00275714) {
        s32 i = 1;
        if (i < n) {
            i = n - 1;
            do {
                SkipBufferedBlock(self);
                i--;
            } while (i != 0);
        }
    }
}

void func_001DCD28(World* self)
{
    Pair_001DCD28 pairs[2] = { { 0x58, 0x23 }, { 0x56, 0x5 } };
    u32 i;
    for (i = 0; i < 2; i++) {
        Node_001DCD28* n;
        for (n = (Node_001DCD28*)self->list1C54.head; n != 0; n = n->next) {
            if (n->flag334 == 0 && n->desc->key == pairs[i].key) {
                break;
            }
        }
        if (n == 0) {
            continue;
        }
        for (s32 k = 0; k < pairs[i].count; k++) {
            Obj_001DCD28* o = CreateObjectCopy(n, self, 0);
            o->f2D8 = 2;
            if (o->vtbl[19] != 0) {
                o->vtbl[19](o);
            }
            o->vtbl[20](o);
        }
    }
}

INCLUDE_ASM(func_001DCEA0);

s32 func_001DD218(Quad_001DD3E0* pts)
{
    u32 i;
    for (i = 0; i < 6; i++) {
        const Plane_1DD218* pl = &D_002756B0[i];
        f32 d[2];
        s32 k;
        for (k = 0; k < 2; k++) {
            d[k] = pts[k].x * pl->x + pts[k].y * pl->y + pts[k].z * pl->z + pts[k].w * pl->w;
        }
        if (d[0] >= 0.0f && d[1] >= 0.0f) {
            continue;
        }
        if (d[0] < 0.0f && d[1] < 0.0f) {
            return 0;
        }
        f32 t = d[1] / (d[1] - d[0]);
        if (d[0] >= 0.0f) {
            f32 u = 1.0f - t;
            pts[1].x = t * pts[0].x + u * pts[1].x;
            pts[1].y = t * pts[0].y + u * pts[1].y;
            pts[1].z = t * pts[0].z + u * pts[1].z;
            pts[1].w = t * pts[0].w + u * pts[1].w;
        } else {
            f32 u = 1.0f - t;
            pts[0].x = t * pts[0].x + u * pts[1].x;
            pts[0].y = t * pts[0].y + u * pts[1].y;
            pts[0].z = t * pts[0].z + u * pts[1].z;
            pts[0].w = t * pts[0].w + u * pts[1].w;
        }
    }
    return 1;
}

void func_001DD3E0(Quad_001DD3E0* a, Quad_001DD3E0* b, Word_001DD3E0* c, u8* obj, s32 k)
{
    Locals_001DD3E0 L;
    Quad_001DD3E0* base;
    Quad_001DD3E0* p;
    s32 n;

    base = &L.buf[2];

    L.buf[0] = *a;
    L.buf[0].w = 1.0f;
    L.buf[1] = *b;
    L.buf[1].w = 1.0f;

    p = base;
    n = 1;
    do {
        *(Q_1DD3E0*)p = TransformVector4(obj + 0x100, *(Q_1DD3E0*)(p - 2));
        n--;
        p++;
    } while (n >= 0);

    if (ClipSegmentToPlanes(base) != 0) {
        void* tp = &L.tmp;
        Quad_001DD3E0* q = base;
        n = 1;
        do {
            f32 r = 1.0f / q->w;
            q->x = q->x * r * g_projectionScale.x + g_projectionOffset.x;
            q->y = q->y * r * g_projectionScale.y + g_projectionOffset.y;
            q->z = q->z * r * g_projectionScale.z + g_projectionOffset.z;
            n--;
            q++;
        } while (n >= 0);
        L.tmp = *c;
        DrawLineSegment(*(s32*)&L.buf[2].x, *(s32*)&L.buf[2].y, *(s32*)&L.buf[2].z,
                      *(s32*)&L.buf[3].x, *(s32*)&L.buf[3].y, *(s32*)&L.buf[3].z,
                      tp, k);
    }
}

void func_001DD548(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, f32 x)
{
    Locals_1DD548 L;
    Quad_1DD548* p;
    Quad_1DD548* q;
    u32 i;

    SampleCurvePoints(a0, a1, a2, a3, 10, L.pts, x, 0.0f, x);
    i = 1;
    q = &L.pts[1];
    p = &L.pts[0];
    do {
        L.c = *(Pack4_1DD548*)a4;
        DrawProjectedLine(p, q, &L.c, a5, 1);
        i++;
        q++;
        p++;
    } while (i < 10);
}

void func_001DD5F8(World* self, f32 v)
{
    self->f1D6C = v;
    g_lightingChangeFrame = g_frameCount;
}

void func_001DD610(World* self, f32 v)
{
    self->f1D68 = v;
    g_lightingChangeFrame = g_frameCount;
}

void func_001DD628(void* self, f32 x)
{
    World* s = (World*)self;

    s->f2318 = x;
    *(s32*)g_previousSoundLevel = -100;
    SetVolumeChannelFactor(7, 1, 1.0f);
    SendIopSoundLevel((s32)(s->f2318 + 0.5f));
}

s32 func_001DD690(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x1;
}

s32 func_001DD6B0(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x2;
}

s32 func_001DD6D0(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x4;
}

s32 func_001DD6F0(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x8;
}

s32 func_001DD710(World* a0, Arg_001DD710* a1)
{
    s32 one = 1;
    u32 m = GetEntryFlags(a1);
    s32 r = 0;
    if (m & 2) r = (g_currentEntry->flags & 1) ? one : 0;
    return r;
}

s32 func_001DD758(void* self, void* obj)
{
    u32 flags = GetEntryFlags((Obj_1DD758*)obj);
    u32 bits = flags & 3;
    s32 r = 0;
    if (flags & 4) {
        G27C230* g = g_currentEntry;
        u32 m = (u32)g->flags;
        r = ((bits & m) ^ bits) < 1;
    }
    return r;
}

s32 func_001DD7A0(void* self, void* obj)
{
    u32 flags = GetEntryFlags((Obj_1DD7A0*)obj);
    u32 bits = flags & 7;
    s32 r = 0;
    if (flags & 8) {
        G27C230* g = g_currentEntry;
        u32 m = (u32)g->flags;
        r = ((bits & m) ^ bits) < 1;
    }
    return r;
}

void func_001DD7E8(void* self, void* obj, s32 key, s32 value)
{
    EntrySlotTable* t = (EntrySlotTable*)GetLevelEntryByKey(obj);
    if (t) {
        EntrySlot* found = 0;
        for (u32 i = 0; i < 4; i++) {
            EntrySlot* p = &t->slots[i];
            if (found == 0 && p->key == 0) {
                found = p;
                continue;
            }
            if (p->key == key) {
                found = p;
                break;
            }
        }
        if (found) {
            found->key = key;
            found->value = value;
        }
    }
}

s32 func_001DD888(void* self, void* obj, s32 key)
{
    EntrySlotTable* t = (EntrySlotTable*)GetLevelEntryByKey(obj);
    if (t != 0) {
        EntrySlot* p = t->slots;
        for (u32 i = 0; i < 4; i++) {
            if (p->key == key) {
                return p->value;
            }
            p++;
        }
    }
    return 0;
}

s32 func_001DD8E8(void* self, s32 index)
{
    return g_saveData->levels[index].f448 & 1;
}

s32 func_001DD908(void* self, s32 index)
{
    return g_saveData->levels[index].f448 & 0x20;
}

void func_001DD928(void* self)
{
    ComputeCompletionPercent(g_saveData);
}

void func_001DD950(void* unused, void* a, void* b, void* c)
{
    void* r = RandomIntInRange(a, b);
    if (r != 0) {
        ScatterObjectsAroundCircle(g_currentWorld, 0x58, c, r, 0);
    }
}

void func_001DD9A0(void)
{
    SetScatterLevel(g_scatterController);
}

void func_001DD9C0(void* unused, f32* out)
{
    *out = g_currentEntry->dt;
}

void func_001DD9D8()
{
    f32 r = ClampToRange(&g_unitRange);
    g_currentEntry->f10 = r;
}

void func_001DDA08(void* unused, f32* out)
{
    *out = g_currentEntry->f10;
}

void func_001DDA20(World* a0) {
    s32 n = a0->f231C + 1;
    a0->f231C = n;
    if (n == 1) {
        SetPadSelectFlags(2);
    }
}

void func_001DDA50(World* self)
{
    s32 v = self->f231C - 1;
    self->f231C = v;
    if (v == 0) {
        ClearPadSelectFlags(2);
    }
}

s32 func_001DDA80(World* self) { return self->f231C > 0; }

void func_001DDA90(void* self, s32* out)
{
    *out = HasStreamVoice();
}

void func_001DDAB8(World* self, f32 v)
{
    self->f2350 = v;
    self->f234C = v;
}

void func_001DDAC8(World* self, f32 value) { self->f2350 = value; }

void func_001DDAD0(void)
{
    StepSequence* ctx = D_0027051C;
    if (ctx != 0 && ctx->state2D4 != 4) {
        u32 t = (u32)(ctx->mode2D0 - 1);
        if (t < 2) PopStackElement(g_elementStack);
    }
}

void func_001DDB20(void* unused, s32 a1, s32 a2)
{
    s32 saved = a1;
    u8* p = (u8*)&g_pauseMenuElement;
    ((Unaligned_1DDB20*)(p + 0x280))->v = a2;
    SetPauseMenuLayerPage(&g_pauseMenuElement, 0, saved);
}

void func_001DDB58(World* self)
{
    if (++self->f2320 == 1) {
        SetScreenElementHoldTime(&D_002721D0, 0.0f);
        D_002721D0.vt->m14(&D_002721D0);
    }
}

void func_001DDBB8(World* self)
{
    if (--self->f2320 == 0) {
        D_002721D0.vt->m15(&D_002721D0);
    }
}

LINKER_REMNANT(func_001DDBF0);

void func_001DDBF8(void* self, void* p)
{
    PushSoundLevel(p);
}

void* func_001DDC18(void* unused, void* p)
{
    return RemoveSoundLevelAndRecompute(p);
}

void func_001DDC38(World* self, void* v)
{
    self->f2324 = v;
}

void func_001DDC40(World* self)
{
    Child_001DDC40* p = (Child_001DDC40*)self->f2324;
    if (p != 0) {
        VFn_001DDC40 fn = p->vtbl[50];
        if (fn != 0) {
            fn(p);
        }
    }
}

void func_001DDC78(World* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->f235C |= m;
}

void func_001DDC90(World* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->f235C &= ~m;
}

void func_001DDCB0(void* self, s32* out)
{
    *out = g_saveData->f19E4;
}

void func_001DDCC8(void* unused, s32* out)
{
    *out = g_saveData->f19E0;
}
