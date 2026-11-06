// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "c88.h"
#include "c54.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"

void func_001B4AA0(CursorAnimator* self, const AnimatorParams* src);
void func_001B4AD0(CursorAnimator* self);
void func_001B46E0(AnimCursor* cur, s32 idx);
void func_001B4750(AnimCursor* cur, f32 x, f32 y);
AnimRecord* func_001B4688(s32 key);
extern AnimCursor* D_00274544;
extern AnimCursor* D_0027451C;

f32 func_001EAAE0(f32 a, f32 b);

struct Vec2_1B5160 { f32 x; f32 y; };
struct Inner_1B5160 { u8 pad0[0x34]; s32 i34; };
struct Other_1B5160 {
    void* vt; u8 pad0[0xC]; Vec2_1B5160 vec; u8 pad1[0x60]; Inner_1B5160* p78;
};

extern u8 func_00166690[];
f32 func_00205778(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

f32 func_002058A0(f32 a, f32 b);

extern f32 D_0026185C;

struct Vec2_1B55A8 { f32 x; f32 y; };

struct Walk_1B5D80 { s32 a; u32 b; u32 c; };

struct Obj_1B65F8 {
    u8 pad0[0x24];
    void* f24;
    u8 pad1[0x10];
    f32 f38;
};

void func_0012F6B0(void* p);

struct Slot_1B71C8 {
    void* first;
    s32 second;
};

struct Self_1B71C8 {
    u8 pad0[0xCD4];
    s32 count;
    u8 pad1[4];
    Slot_1B71C8 slots[1];
};

s32 func_001300E8(void* a, s32 b);
s32 func_00182F40(Collider* e, void* b);

void func_0015FCD8(C09* self, void* p);
void func_001BF048(void* p);

struct Entry_1B65C8 { s32 value; s32 extra; };
struct Host_1B65C8 { u8 pad[0x38]; Entry_1B65C8* entries; };
struct Node_1B65C8 { u8 pad[0x18]; Host_1B65C8* host; u8 pad2[0x2C - 0x1C]; s32 index; };

struct Node_1B6C68 {
    u8 pad[0x28];
    s32 f28;
    s32 index;
};

void func_001B6E28(Node_1B6C68* self, s32 a, s32 b);

struct Node_1B6CA8 {
    u8 pad[0x24];
    s32 f24;
};

void func_001B6C68(Node_1B6CA8* self);
void func_001B66A0(Node_1B6CA8* self);

typedef void (*VFn_1B6D78)(void* self);
struct Obj_1B6D78 { VFn_1B6D78* vtbl; };
typedef void (*Cb_1B6D78)(void* obj, s32 a, s32 b);
struct Link_1B6D78 {
    Cb_1B6D78 fn;
    void* obj;
    u8 pad[0x8];
    Link_1B6D78* next;
};
struct Node_1B6D78 {
    u8 pad[0x1C];
    Obj_1B6D78* f1C;
    u8 pad2[0x3C - 0x20];
    Link_1B6D78* f3C;
};

struct Entry_1B6E28 { s32 value; s32 extra; };
struct Node_1B6E28 { u8 pad[0x18]; C88* host; };

void func_001837E0(C88* host, s32 a, s32 b, void** args);


void func_001694A0(void* p);

extern s32 D_0027453C;
extern CursorAnimator** D_00274540;

s32 func_001B4B08(CursorAnimator* p);

s32 func_00137BE0(void* a);
s32 func_001B4920(s32 type);
void* func_0018D5C0(s32 size);
void* func_001B4980(s32 type);
void func_00137A60(void* owner, s32 key, void* out);

struct Node_1B5EA0 { Node_1B5EA0* next; };
struct Pool_1B5EA0 { u8 pad[8]; Node_1B5EA0* head; };

struct Node_1B5EC0 { Node_1B5EC0* next; };
struct Pool_1B5EC0 { u8 pad[8]; Node_1B5EC0* head; };

void* func_001B5EA0(Pool_1B5EC0* pool);

struct Node_1B5EE0 { Node_1B5EE0* next; };
struct Pool_1B5EE0 { s32 count; u8 pad[4]; Node_1B5EE0* head; };

void* func_001B5EA0(Pool_1B5EE0* pool);
void func_001F5C0C(void* p, int zero, s32 count);

void func_00138828(void* owner, void* self);
Contacts03* func_001DC7D0(void* owner, void* self);
void func_00138F28(void* owner, void* self);
void func_00152470(void* p, void* self);
void func_001240F8(void* self);
void func_001B7C40(Collider* self, s32 flag);
void func_001BB580(void* p);
void func_001BB4A0(void* self);

void func_001B7A98(Collider* self)
{
    World* owner = self->world;
    owner->count34++;
    if (self->parent == 0) {
        func_00138828(owner, self);
        self->contacts = TakeContactTable(owner, self);
        InitContactPairFlags(owner, self);
        owner->count38++;
        AppendToList(&owner->bodies, self);
    }
    RegisterPlacedObject(self);
    SetColliderPartListed(self, 1);
    self->desc03()->m44(self);
    if (!(self->flags538 & (1ULL << 54))) {
        UpdateAnchorModeFlags(self->root03());
    } else {
        UpdateAnchorModeFlags(self);
    }
    ResolveContactHandler(self);
}

void func_001243E0(void* self);
void func_001388A0(void* owner, void* self);
void func_001DC828(void* owner, Contacts03* contacts);
void func_00152600(void* p, void* self);
void func_001DC108(void* owner, Touch03* list);

void func_001B7B78(Collider* self)
{
    Collider* old50 = self->root03();
    World* owner = self->world;
    SetColliderPartListed(self, 0);
    UnregisterPlacedObject(self);
    owner->count34--;
    if (self->parent == 0) {
        func_001388A0(owner, self);
        ReleaseContactTable(owner, self->contacts);
        owner->count38--;
        RemoveFromList(&owner->bodies, self);
    }
    FreeTouchNodes(owner, self->touching);
    u64 flags = self->flags538;
    self->touching = 0;
    if (!(flags & (1ULL << 54)) && old50 != self) {
        UpdateAnchorModeFlags(old50);
    }
}

void func_00138BE0(void* owner, void* self, s32 n);

void func_001B7C40(Collider* self, s32 flag)
{
    if (flag == ((self->flags538 >> 50) & 1)) {
        return;
    }
    if (flag != 0) {
        AppendToList(&self->root03()->parts, self);
    } else {
        RemoveFromList(&self->root03()->parts, self);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 50)) | ((u64)(flag & 1) << 50);
    ClearRootObjectStateBits(self->world, self, 7);
    Collider* sub = self->root03();
    sub->desc03()->m32(sub);
}


void func_00182C58(void* self);
void func_001B61F0(void* self);
void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);

struct Pair_1B63C0 {
    s32 key_00;
    s32 value_04;
};

f32 func_001EAAE0(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

s32 func_001B63C0(void* self, s32 key);

struct Reg_001B6438 { u8 pad0[0x1B88]; };
struct Owner_001B6438 { u8 pad0[0x14]; Reg_001B6438* reg_14; };
struct Obj_001B6438 {
    u8 pad0[0x18];
    Owner_001B6438* owner_18;
    u8 pad1[0x24 - 0x1C];
    void* handle_24;
    u8 pad2[0x3C - 0x28];
    void* ptr_3C;
};

void func_0012E760(void* p);
void func_001DBC18(void* a, void* b);
void func_00152600(void* a, void* b);
void func_001B5F28(void* a, void* b);
void func_001837E0(void* a, s32 b, s32 c, s32 d);

struct Vec3_1B5588 { f32 x; f32 y; f32 z; };

void func_00152438(void* self, s32 value);
void func_00123ED0(void* self);
void func_00160E80(Mesh03* mesh);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_0011A498(void* a, s32 b, s32 c, ScriptValue* d);
void func_001BB4A0(void* self);

void func_001B7968(Collider* self)
{
    ScriptValue local;
    s32 s0;
    InitScriptValue(&local);
    func_00152438(&self->parts, 0x2E4);
    InitPlacedObject(self);
    func_00160E80(&self->mesh);
    self->meshCopy = self->mesh;
    if (self->parent != 0) {
        SetColliderAnchors(self, 3, 0, 3, 0);
    }
    self->f4BC = -1;
    self->index = -1;
    if (self->f2C != 0) {
        s0 = LookupScriptVariable(self->f2C, 6, 1, &local);
        s0 |= LookupScriptVariable(self->f2C, 7, 1, &local);
        if (s0 != 0) {
            self->flags538 |= (u64)0x8000 << 48;
        }
    }
    self->gravity = self->world->gravity;
    ResolveContactHandler(self);
    DestroyScriptValue(&local, 2);
}

struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };

void func_001B4330(Quad_001B4580* p);

struct Slot_1B70B0 { s32 value; s32 pad4; };
struct Self_1B70B0 { u8 pad0[0xC38]; Slot_1B70B0 slots[1]; };

s32 func_001CA600(s32 index);

void func_00124A48(void* self);

struct Walk_1B5DD0 { s32 a; void* b; s32 c; };

void* func_0018D500(s32 size);
void func_001B5D80(void* s, s32 v, s32 n);

struct Walk_1B5E30 { s32 a; void* b; s32 c; };

void* func_0018D500(s32 size);
void func_001B5D80(void* s, s32 v, s32 n);

struct Node_1B6388 {
    u8 pad0[0x8];
    Node_1B6388* next;
    u8 pad1[0x10];
    s32 key;
};

struct Owner_1B6388 {
    u8 pad0[0x48];
    Node_1B6388* head;
};

struct Holder_1B6DF8 {
    u8 pad0[0x14];
    void* ptr;
};

struct Self_1B6DF8 {
    u8 pad0[0x18];
    Holder_1B6DF8* holder;
};

void func_001831E8(void* a, void* b, s32 c, void* d);

struct Pair_1B7128 {
    s32 key;
    s32 value;
};

void func_001C72A0(void* self);
void func_001B6F50(void* self);
s32 func_0015A448(void* host, s32 id, void* ctx);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_001C7CB8(void* self);
void func_001B7638(void* self);

typedef void (*VFn_1B7790)(void* self);
struct Sub_1B7790 { VFn_1B7790* vtbl; };
void func_001C91C8(void* self);
void func_001BF048(void* p);

typedef s32 (*VFn_1B7818)(void* self);

s32 func_001CA468(void* self);

void func_001C9DE0(void* self, s32 code, void* req);

f32 func_001EAAE0(f32 a, f32 b);

f32 func_001EAAE0(f32 a, f32 b);

extern f32 D_0026185C;
f32 func_001EA408(f32 a);
void func_001EAD88(f32 angle, f32* a, f32* b);

extern f32 D_0026185C;
f32 func_001EAFE0(f32 x, f32 y);

void func_00124FC0(void* self);

void func_001C6F48(void* self);

struct Ent_1B6EC8 { s32 v; s32 pad; };

extern f32 D_0026185C;

extern s32 D_002744F8;
extern AnimRecord* D_002744FC;

struct Item_1B61F0 {
    u8 pad_00[0x40];
    s32 value_40;
};

struct Slot_1B61F0 {
    Item_1B61F0* item_00;
    s32 pad_04[4];
};

struct Bank_1B61F0 {
    u8 pad_00[0x14];
    void* owner_14;
    u8 pad_18[0x24];
    s32 count_3C;
    Slot_1B61F0* slots_40;
};

s32 func_0015A448(void* owner, s32 value, void* bank);
void* func_001B6290(void* bank, s32 r, s32 minus_one, s32 zero);

u16 func_001B5B58(u8 ch);
s32 func_001E2100(void* p);

struct Inner_1B6CF0 { u8 pad[0x34]; f32 f34; };
struct Item_1B6CF0 {
    u8 pad[0x8];
    Inner_1B6CF0* inner;
    u8 pad2[0x14 - 0x0C];
    f32 f14;
};
struct Node_1B6CF0 { u8 pad[0x24]; s32 f24; };

f32 func_001B6C68(Node_1B6CF0* self);
void func_001B66A0(Node_1B6CF0* self);
void func_0012F0A0(void* a, f32 b, f32 c, s32 d);

f32 func_001EAAE0(f32 a, f32 b);

struct Entry_001B6568 {
    s32 value;
    s32 extra;
};
struct Sub_001B6568 {
    u8 pad0[0x38];
    Entry_001B6568* table;
};

struct Entry_001B6598 {
    s32 value;
    s32 extra;
};
struct Sub_001B6598 {
    u8 pad0[0x38];
    Entry_001B6598* table;
};
struct Ctx_001B6598 {
    u8 pad0[0x18];
    Sub_001B6598* sub;
    u8 pad1[0x28 - 0x1C];
    s32 index;
};

s32 func_001B63F8(void* self, s32 key);
void func_001B6E28(StateWalker* self, s32 a, s32 b);
void func_001B66A0(StateWalker* self);

struct Flags_1B64D8 { u8 pad0[0xC]; s32 flags; };
struct Node_1B64D8 {
    u8 pad0[0x18];
    void* f18;
    u8 pad1[0x24 - 0x1C];
    void* f24;
    u8 pad2[0x30 - 0x28];
    s32 f30;
    Flags_1B64D8* f34;
};

s32 func_001B63F8(C88* self, s32 key);
void func_001B6C68(Node_1B64D8* self);
void func_0012E760(AnimationPlayer* obj);
void func_001B66A0(Node_1B64D8* self);

struct Entry_2198E8 { const u8* f0; s32 f4; };
extern const Entry_2198E8 D_002198E8;
extern const u8 D_00217410[];

void* func_001B5EE0(Pool6C* pool);
void func_00152470(List01* list, StateWalker* item);
s32 func_001B63F8(C88* self, s32 key);
void func_001B6E28(StateWalker* self, s32 a, s32 b);
void func_001B66A0(StateWalker* self);
void func_001837E0(C88* self, s32 a, s32 b, void* c);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
f32 func_001B4B38(void);
AnimCursor* func_001B4B48(CursorAnimator* self, const AnimRecord* key);
void func_001B4B68(FrameRunAnimator* p, AnimatorParams* s);
void func_001B4BC8(FrameRunAnimator* p);
void func_001B4C30(FrameRunAnimator* p, f32 dt);
f32 func_001B4D18(FrameRunAnimator* p);
void func_001B4D48(FramePingPongAnimator* p, AnimatorParams* s);
void func_001B4DA8(FramePingPongAnimator* p);
void func_001B4E18(FramePingPongAnimator* p, f32 dt);
f32 func_001B4F18(FramePingPongAnimator* p);
void func_001B4F80(RandomJumpAnimator* p, AnimatorParams* s);
void func_001B4FC0(RandomJumpAnimator* self, f32 x);
void func_001B5060(AngleFrameAnimator* self, AnimatorParams* key);
void func_001B5108(AngleFrameAnimator* p);
void func_001B5160(AngleFrameAnimator* p, void* unused, Other_1B5160* q);
void func_001B5200(ScrollAnimator* p, AnimatorParams* s);
void func_001B5278(ScrollAnimator* p, f32 t);
f32 func_001B5308(ScrollAnimator* p);
void func_001B5398(CircleAnimator* p, AnimatorParams* s);
void func_001B5400(CircleAnimator* self);
f32 func_001B5488(CircleAnimator* p);
void func_001B54D0(TriangleAnimator* self, AnimatorParams* src);
void func_001B5568(TriangleAnimator* self, void** out);
extern const Fn_Table D_0021E358[];
extern const Fn_Table D_0021E378[];
extern const Fn_Table D_0021E398[];
extern const Fn_Table D_0021E3B8[];
extern u8 D_0021E438[];
extern const Fn_Table D_0021E3D8[];
extern const Fn_Table D_0021E3F8[];
extern const Fn_Table D_0021E418[];

struct Hdr_1B6F50;
struct Elem_1B6F50;
struct Sub_1B6F50 { u8 p0[0x11]; u8 f11; u8 p1[0x0A]; s32 f1C; u8 p2[0x60]; s32 f80; s32 f84; };
typedef void (*VFn_1B6F50)(void* self);
struct Elem_1B6F50 { VFn_1B6F50* vtbl; };
struct Ent_1B6F50 { s32 key; void* val; };
extern u8 D_0021A790[];
void* func_0015A448(Hdr_1B6F50* obj, s32 id, C09* flags);
s32 func_0015A4F0(Hdr_1B6F50* a0, s32 a1, s32 a2, C09* a3, s32 a4, void* a5);
s32 func_001833F0(Elem_1B6F50* a, s32 b);
void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D658(u32 bytes);
void* func_00121228(Hdr_1B6F50* root, s32 value, void* table);
void func_001299E0(Hdr_1B6F50* self, void* src);


struct Quad_1B7638 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} __attribute__((aligned(16)));

struct Sub_1B7638 {
    u8 pad0[0x2F0];
    f32 f2F0;
};

struct Target_1B7638 {
    u8 pad0[0x24];
    void *field24;
    u8 pad1[0x30 - 0x28];
    struct Quad_1B7638 quad30;
};


s32 func_001C96B8(C09 *self);
s32 func_001CB578(C09 *self);

struct Lo_1B4FC0 { s32 v; };
s32 func_001EAA70(Lo_1B4FC0 lo, s32 hi);
f32 func_001EAAE0(f32 a, f32 b);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001B55C0();
extern const Fn_Table D_0021E358[8] = { (Fn_Table)func_001B4B68, (Fn_Table)func_001B4BC8, (Fn_Table)func_001B4C30, (Fn_Table)func_001B4D18, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E378[8] = { (Fn_Table)func_001B4D48, (Fn_Table)func_001B4DA8, (Fn_Table)func_001B4E18, (Fn_Table)func_001B4F18, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E398[8] = { (Fn_Table)func_001B4F80, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B4FC0, (Fn_Table)func_001B4B38, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3B8[8] = { (Fn_Table)func_001B5060, (Fn_Table)func_001B5108, 0, (Fn_Table)func_001B4B38, (Fn_Table)func_001B5160, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3D8[8] = { (Fn_Table)func_001B5200, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B5278, (Fn_Table)func_001B5308, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3F8[8] = { (Fn_Table)func_001B5398, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B5400, (Fn_Table)func_001B5488, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E418[8] = { (Fn_Table)func_001B54D0, (Fn_Table)func_001B4AD0, 0, (Fn_Table)func_001B4B38, (Fn_Table)func_001B55C0, (Fn_Table)func_001B4B48, (Fn_Table)func_001B5568, 0 };

struct Track_1B66A0
{
    u8 pad00[0x34];
    f32 f34;
};
struct Edge_1B66A0
{
    Track_1B66A0* track;
    s32 a;
    s32 b;
    u32 flags;
    f32 weight;
};
struct Link_1B66A0
{
    s32 f0;
    s32 next;
};
struct Graph_1B66A0
{
    u8 pad00[0x34];
    s32 nodeCount;
    Link_1B66A0* links;
    s32 edgeCount;
    Edge_1B66A0* edges;
};
struct Mover_1B66A0
{
    u8 pad00[0x18];
    Graph_1B66A0* graph;
    s32 f1C;
    s32 f20;
    void* f24;
    s32 cur;
    s32 f2C;
    s32 target;
    Edge_1B66A0* edge;
    f32 f38;
};

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D6F0(void);
f32 func_001EAAE0(f32 a, f32 b);
void func_001B6E28(Mover_1B66A0* self, s32 a, s32 b);
s32 func_0012C7B0(Track_1B66A0* track, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void func_0012F7E0(void* obj, void (*fn)(Mover_1B66A0*, s32, s32), Mover_1B66A0* self);
void func_001B6CA8(Mover_1B66A0* self, s32 a, s32 b);
void func_0012F190(void* obj, s32 zero);
void func_0012E760(void* obj);
void func_001B6D78(Mover_1B66A0* self, s32 a, Mover_1B66A0* b);

extern const Entry_2198E8 D_002198E8 = { D_00217410, 0x93 };
