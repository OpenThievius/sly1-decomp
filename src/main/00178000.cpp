// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "c4a.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "globals.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"

void func_001B9690(void* self);
void func_001C29E8(void* sub);

void func_00178008(Player* self)
{
    SetColliderPosition(self);
    ResetTrailRing(self->f1520);
    self->f2768 = 0;
}

void func_001B7968(void* self);


s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);


typedef void (*VFn_17BC20)(void* self);

struct Comp_17BC20 {
    VFn_17BC20* vtbl;
    u8 pad0[0x2D0 - 4];
    s32 f2D0;
};

struct Obj_17BC20 {
    u8 pad0[0x3C];
    s32 f3C;
    u8 pad1[0x58 - 0x40];
    Comp_17BC20* f58;
    s32 f5C;
};

s32 func_00182FC8(void* p);


extern s32 D_00263E2C;


void func_00124A48(void* self);
void func_00124DF8(void* self, int n, void* table);


void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);


void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017B410(C4A* self, s32 a1);
s32 func_0017B510(C4A* self, s32 a1);


struct Msg_17B3A8 {
    u8 pad0[4];
    s32 f4;
    u8 pad1[8];
    u32 f10;
};

void func_001AC060(void* p);
void func_0017B598(C4A* self);
void func_001837E0(void* self, s32 a, s32 b, s32 c);


s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);


struct Item_178258 { u8 pad[0x2D0]; s32 link; };

void func_00178258(Player* a0, Item_178258* a1)
{
    if (a0->f2220 != 9 && a1->link == 0) {
        a0->f2BE4 = a1;
    }
}

struct Item_178280 { u8 pad[0x2D0]; s32 link; };

void func_00178280(Player* a0, Item_178280* a1)
{
    if (a0->f2220 != 9 && a1->link == 0) {
        a0->f2BE8 = a1;
    }
}

void func_001921A8(void* self);


struct Sub_1793F0 { u8 pad0[0xE0]; void* fE0; };
struct Packed_1793F0 { f32 v; } __attribute__((packed));

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_0012B5B8(void* a, s32 b, s32 c);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017ABE8(void* self, s32 a1);
s32 func_001B4688(s32 key);


void func_001C29E8(void* sub);
void func_00192820(void* self);

void func_00178038(Player* self)
{
    ResetTrailRing(self->f1520);
    RegisterSwitchedCollider(self);
}

typedef void (*VFn_179690)(void*);

void func_001BC088(void* self, void* b);


void func_00192C58(void* self);
void func_0017ABE8(void* self, s32 a1);


void func_00192230(void* self, s32 kind, MessageBody* rec);


struct __attribute__((aligned(16))) Quad_178598 {
    s32 a, b, c, d;
};

struct Pair_178598 {
    Quad_178598 q0;
    Quad_178598 q1;
};

struct Sub_178598 {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    Quad_178598 q20;
    Quad_178598 q30;
};

struct Frame_178598 {
    Quad_178598 q0;
    Quad_178598 q1;
    Quad_178598 q2;
    Quad_178598 p0;
    Quad_178598 p1;
    f32 fl;
};

void func_00178D98(void* self, s32 a1, s32 a2, void* a3, void* a4);
void func_001782C0(void* self, void* s2, f32 f, void* a2, void* a3, void* a4);
void func_00175170(void* self, s32 a, s32 b);

extern f32 D_0026185C;

void func_00178598(Player* self, Pair_178598* s2, f32 f)
{
    Frame_178598 fr;
    fr.fl = f;
    if (s2 == 0) {
        ChooseBestTargetCandidate(self, 0, 0, &fr.p0, &fr.fl);
        s2 = (Pair_178598*)&fr.p0;
    }
    void* q1 = &fr.q1;
    func_001782C0(self, s2, fr.fl, q1, &fr.q0, &fr.q2);
    ((Sub_178598*)self->f2514)->f18 = g_gameTime + fr.fl;
    ((Sub_178598*)self->f2514)->q20 = fr.q0;
    ((Sub_178598*)self->f2514)->q30 = fr.q2;
    self->desc02()->m20(self, (Vec02*)q1);
    self->q2B70[0] = *(Vec02*)&s2->q0;
    self->q2B70[1] = *(Vec02*)&s2->q1;

    func_00175170(self, 4, 0x2C);
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first

typedef s32 (*VFn_17AA40_A)(void* self, s32 v);
typedef void (*VFn_17AA40_B)(void* self, void* p);
typedef void (*VFn_17AA40_C)(void* self, s32 a, void* b);

struct Msg_17AA40 {
    void* self;
    s32 v;
};

s32 func_00160C58(void);
void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_0017ABE8(void* self, s32 a1);

extern f32 D_0026185C;


// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 D_00263E2C;

void func_001AC060(void* p);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_0012C918(void* a, CountdownCollider* b, s32 c, void* d, f32 e, f32 f);
s32 func_001BC320(void* self, ObjectEvent* msg);


struct Vt_17B9D0
{
    u8 pad0[0x28];
    void (*f28)(void* self, Vec02* a, s32 b, Vec02* c, Vec02* d, s32 e, s32 f);
};

struct Node_17B9D0
{
    u8 pad0[0x18];
    void* f18;
    u8 pad1c[0x18];
    struct { Vt_17B9D0* vt; }* f34;
    u8 pad38[0x108];
    Vec02 f140;
};

struct Self_17B9D0
{
    u8 pad0[0x3C];
    u8* f3C;
};

s32 func_001300E8(Node_17B9D0* n, s32 kind);
void func_00128018(void* a, void* b, void* c, Vec02* d);

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.

struct Ptr_17A9E0;
s32 func_001DDA80(Ptr_17A9E0* p);

struct Pair_1781E0 { s32 a, b; };

void func_001B6598(void* ptr, s32* out);
void func_001B6568(void* ptr, s32* out);

void func_001781E0(u8* self, u8* other)
{
    Pair_1781E0 r;
    if (*(s32*)(self + 0x2220) != 9) {
        func_001B6598(*(void**)(other + 0x2D8), &r.a);
        func_001B6568(*(void**)(other + 0x2D8), &r.b);
        if (r.a == 0x22E && (r.b == r.a || r.b == -1)) {
            *(u8**)(self + 0x2BE0) = other;
        }
    }
}

typedef void (*Fn_17B410)(void* self);

struct Sys_17B410 {
    Fn_17B410* vtbl;
    u8 pad0[0x260 - 4];
    s32 f260;
    s32 f264;
    u8 pad1[0x26C - 0x268];
    s32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
};

extern f32 D_0026185C;

void func_001DDC38(void* a, void* b);
s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);


extern s32 D_00263E2C;
extern s32 D_00263E30;
extern f32 D_0026185C;

void func_001B93F8(void* self);
void func_0012E760(void* p);
void func_0017B8C0(void* self, s32 state);
void func_00160578(s32 n);


extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 func_001E9970(void* self);


extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 func_001E9970(void* self);


extern f32 D_00261858[];
extern f32 D_00275C60[];
extern Rgba4 D_002623E0;

f32 func_00205210(f32 x);
void func_00126A48(C1B* o, u32 value);
void func_00125C90(C1B* o, void* s, void* out);


// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

struct Sub_179590;
extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void func_001B9338(C1B* self, f32 t);
void func_001794E0(C1B* self, Vec02* a, Vec02* b);
void func_00127E60(Sub_179590* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_001B9058(C1B* self, void* buf, f32 f, void* d1, void* d2, void* d3);
void func_001B9D10(C1B* self, f32 scale, void* out, void* data);


struct Q_178D98 {
    u8 b[16];
} __attribute__((aligned(16)));
struct Hit_178D98 {
    Q_178D98 q0;
    Q_178D98 q1;
};
struct Node_178D98;
struct Vt_178D98;
struct Sub_178D98 {
    Vt_178D98* vt;
};
struct Vt_178D98 {
    u8 pad00[0x28];
    void (*f28)(Sub_178D98* self, Q_178D98* a, s32 b, s32 c, s32 d, s32 e, f32* out);
};
struct Node_178D98 {
    u8 pad00[0x18];
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    Sub_178D98* f34;
};
struct Entry_178D98 {
    Node_178D98* node;
    f32 f4;
    u8 pad08[8];
    u8 f10[16];
};
struct Slot_178D98 {
    Node_178D98* node;
    u8 pad04[0x1C];
};
extern f32 D_0024AFA4;
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_0018D608(void);
Entry_178D98* func_0018D6A8(s32 size);
void func_0018D6F0(void);
s32 func_00182FC8(Node_178D98* p);
s32 func_001300E8(Node_178D98* n, s32 kind);
void func_00128018(void* a, void* b, Q_178D98* c, Q_178D98* d);
void func_001782C0(Player* self, Entry_178D98* e, f32 f, void* a2, void* a3, void* a4);
s32 func_00178D18(Entry_178D98* a, Entry_178D98* b);
void func_001F5CD0(Entry_178D98* base, s32 n, s32 size, s32 (*cmp)(Entry_178D98*, Entry_178D98*));
f32 func_001788F0(Player* self, void* e, s32 v, void* a3, Hit_178D98* a4, f32* a5);
void func_001F5C0C(void* dst, s32 value, s32 size);

void func_00178D98(Player* self, s32 n, Node_178D98** items, Hit_178D98* out, f32* outf)
{
    u8 scratch[0x80];
    Hit_178D98 hit;
    Q_178D98 tmp;
    f32 dist;
    f32 r;
    s32 v;
    Entry_178D98* buf;
    f32 best;
    s32 cnt = 0;

    v = GatherObjectsById(self->world, 5, 8, 0, 0x20, scratch);
    PushBackMemoryMark();
    buf = AllocateZeroedBackMemory(n << 5);
    for (s32 i = 0; i < n; i++) {
        Node_178D98* node = items[i];
        if (IsObjectAttached(node) != 0) {
            Entry_178D98* e = buf + cnt;
            cnt = cnt + 1;
            e->node = node;
            if (IsObjectOfKind(node, 0x6E) != 0) {
                func_00128018(0, node->f18, (Q_178D98*)&self->v140, &tmp);
                Sub_178D98* s = node->f34;
                if (s->vt->f28 != 0) {
                    s->vt->f28(s, &tmp, 0, 0, 0, 0, &e->f4);
                }
            } else {
                e->f4 = 0;
            }
            func_001782C0(self, e, 0.7f, 0, e->f10, 0);
        }
    }
    func_001F5CD0(buf, cnt, 0x20, func_00178D18);
    best = D_0024AFA4;
    for (s32 i = 0; i < cnt; i++) {
        r = func_001788F0(self, &buf[i], v, scratch, &hit, &dist);
        if (r < best) {
            best = r;
            *out = hit;
            *outf = dist;
            if (best == 0.0f)
                goto done;
        }
    }
    if (best <= 1000.0f)
        goto done;
    for (s32 i = 0; i < self->f2768; i++) {
        Slot_178D98* q = &((Slot_178D98*)self->f2770)[i];
        if (q->node == 0 || IsObjectAttached(q->node) != 0) {
            r = func_001788F0(self, q, v, scratch, &hit, &dist);
            if (r < best) {
                best = r;
                *out = hit;
                *outf = dist;
                if (best == 0.0f)
                    goto done;
            }
        }
    }
    if (best == D_0024AFA4) {
        func_001F5C0C(out, 0, 0x20);
        *(s32*)out = 0;
        out->q1 = *(Q_178D98*)&self->v140;
        ((f32*)out)[6] -= 75.0f;
        *outf = 0.75f;
    }
done:
    PopBackMemoryMark();
}
