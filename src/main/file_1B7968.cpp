// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
#include "buffered_stream.h"
#include "object_event.h"
#include "key_record.h"
#include "key_id.h"
#include "base_object.h"
#include "asm_func.h"
#include "point_object.h"
#include "id_linked_object.h"
#include "game_progress.h"
#include "shapes.h"
#define VA_ARG_1C2430(ap, T) (*(T*)((ap += 8) - 8))

f32 func_001EAAE0(f32 a, f32 b);
f32 func_00205778(f32 a, f32 b);
extern f32 D_0026185C[];
s32 func_00182F40(Collider* e, void* b);
void func_001BF048(void* p);
void func_001837E0(StateGraph* host, s32 a, s32 b, void** args);
s32 func_00137BE0(void* a);
void* func_0018D5C0(s32 size);
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
void func_001243E0(void* self);
void func_001388A0(void* owner, void* self);
void func_001DC828(void* owner, Contacts03* contacts);
void func_00152600(void* p, void* self);
void func_001DC108(void* owner, Touch03* list);
void func_00138BE0(void* owner, void* self, s32 n);
void func_00152600(void* a, void* b);
void func_001B5F28(void* a, void* b);
void func_001837E0(void* a, s32 b, s32 c, s32 d);
void func_00152438(void* self, s32 value);
void func_00123ED0(void* self);
void func_00160E80(Mesh03* mesh);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_0011A498(void* a, s32 b, s32 c, ScriptValue* d);
struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };
void func_00124A48(void* self);
void* func_0018D500(s32 size);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00124FC0(void* self);
void* func_001B6290(void* bank, s32 r, s32 minus_one, s32 zero);
void func_00152470(List01* list, StateWalker* item);
void func_001837E0(StateGraph* self, s32 a, s32 b, void* c);
void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D658(u32 bytes);
struct Lo_1B4FC0 { s32 v; };
s32 func_001EAA70(Lo_1B4FC0 lo, s32 hi);
void* func_0018D658(s32 size);
void func_00125108(Collider* self);
void func_00138BE0(void* a, void* b, s32 c);
void func_001389C8(void* a);
void func_001B9448(Collider* self);
void func_001B94F0(Collider* self, s32 value);
void func_00138F28(void* a, void* b);
s32 func_001C1AD8(s32 value, void* out);
s32 func_001C1A28(s32 value, void* out);
struct Vec_1B9338 { s32 v[4]; };
void func_001BA500(void* a, void* b, void* c, void* d, s32 e);
void func_001B9AB0(void* a, void* b);
void func_001261C0(Collider* self, void* a, void* m);
void func_001BA430(void* a, void* b, void* c, s32 d);
void func_00129DF8(void* self);
typedef u64 Quad_1B8960 __attribute__((mode(TI)));
void func_00125138(void* self);
void func_001B8820(Mesh03* a, Mesh03* b, Quad_1B8960 q, Mat02* c);
struct __attribute__((aligned(16))) Quad_1B9B50 { s32 a, b, c, d; };
void func_001280C0(void* a, void* b, void* c, void* d);
void func_001245A8(void* self, void* p);
s32 func_00182F40(void* e, void* b);
void func_00183350(void* self, s32 kind, void* arg);
struct Entry_1BB028 { const Vec02* quad; s32 value; };
extern Entry_1BB028 D_002746E0[8];
void* func_0018D658(s32 n);
s32 func_001387F8(void* self, void* other);
// Matched by indexing the end as (u32)e + (i << 6).

void func_001837E0(void* self, s32 a, s32 b, void* c);
void func_001DC108(void* pool, Touch03* m);
Touch03* func_001DC0C8(void* pool);
void func_00127048(Collider* self, Collider* other);
void func_00160EA0(Mesh03* a, s32 b, Mesh03* c);
void func_0013E6C8(Mesh03* a, Tree03* b, Mesh03* c, Tree03* d);
// NEAR: 14 lines: retail preloads f400/f40C into s0 (lw s0 before loop and in the bnel delay slot), we load into v1; f408 loop test reload; last loop pointer s2 vs index


s32 func_00137B90(BufferedStream* in);
void func_00137FB0(BufferedStream* in, Mesh03* p);
void func_00138278(BufferedStream* in, Mesh03* a, Tree03* out);
f32 func_00137DF8(BufferedStream* in);
void func_00137EB0(BufferedStream* in, Mat02* p);
void func_00137E70(BufferedStream* in, Vec02* p);
void func_001B9448(Collider* self, f32 x);
s32 func_00137BE0(BufferedStream* in);
s32 func_00137D10(BufferedStream* in);
s32 func_00137C40(BufferedStream* in);
void func_001289C0(Collider* self, BufferedStream* in);
void func_00138F28(void* a, Collider* b);
struct Out_1B9F30 {
    s32 f00;
    u8 pad04[0x0C];
    Vec02 q10;
    Vec02 q20;
    f32 f30;
    f32 f34;
    f32 f38;
    s32 f3C;
};
void func_00189378(Mat02* m, s32 zero, Vec02* out);
void func_001861E8(void* pool, Contact03* head);
extern s32 D_00274744;
void func_001BE998(void);
extern s32 D_00274728;
void func_001BEB10(void* self);
s32 func_0011CE30(void);
void func_001F6C20(s32 a);
s32 func_0011D598(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_00152600(u8* a, void* b);
void func_001B5F28(u8* a, void* b);
extern u8 D_00604790[];
void func_001F5C0C(u8* p, s32 a, s32 b);
void func_0011CBB8(void);
s32 func_001BE268(s32 a);
s32 func_0011DF58(s32 a, s32 b, s32 c, s32 d);
void func_0011D928(s32 a);
void func_001C06D8(void);
void func_0011D520(s32 a, s32 b);
void func_0011D558(s32 a, s32 b, s32 c);
void func_0011E3A0(s32 a, s32 b);
void* func_001B5EA0(void* p);
void func_001F5C0C(void* p, s32 zero, s32 size);
void func_00152470(void* list, void* item);
struct Entry_1BF718 { u8 pad[0xC]; s32 f0C; };
struct Slot_1BF718 { Entry_1BF718* entry; };
struct Obj_1BF728 { u8 pad0[4]; s32 f04; u8 pad1[4]; void* f0C; };
void func_00152600(u8* p, Obj_1BF728* self);
void func_001B5F28(u8* p, Obj_1BF728* self);
struct Obj_1BF788 { u8 pad[0x18]; u8* f18; };
void func_001BF728(Obj_1BF788* self);
void func_0011D600(u8* p);
void func_0011D860(u8* p, s32 a, s32 b, s32 c);
struct Obj_1BF8E8 { u8 pad0[0x14]; f32 f14; u8 pad1[0x38]; f32 f50; };
void func_001BE860(Obj_1BF8E8* self);
struct Rec_1BFFC8 { u8 pad0[4]; s32 f04; u8 pad1[0x40]; s32 f48; };
void func_001BBEB8(Collider* self);
void func_00125440(Collider* self, f32 x, void* b);
void func_001BC0E0(void* a0, f32 x, void* a1, void* a2);
void func_001C06A0(s32 a, s32 b, f32 x);
void func_0011D640(s32 a);
void func_0011D670(s32 a);
void func_00152470(u8* a, void* b);
struct Entry_1BF048 {
    s32 key;
};
extern s32 D_002748EC;
extern s32 D_00274734;
extern s32 D_00274738;
void func_001BEDF8(void* self);
void func_001BEF88(void* self);
typedef signed int s32;
typedef unsigned char u8;
extern s32 D_00274720;
extern s32 D_0027473C;
void func_0011D450(s32 handle);
void func_0011D600(s32 handle);
struct Obj_1BF0D8 { s32 kind; };
void func_001BEDF8(Obj_1BF0D8* self);
void func_001BEF88(Obj_1BF0D8* self);
extern s32 D_0027472C;
typedef void (*Fn_001BF578)(void);
s32 func_001493A0(u8* p);
s32 func_00149638(u8* s);
void func_001BF398(void);
void func_001BF2E0(void);
struct Rec_1BE4D8 {
    s32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    s32 f10;
    f32 f14;
    u8 pad18[4];
    s32 f1C;
    s32 f20;
};
struct Owner_1BE4D8 {
    Rec_1BE4D8* rec;
};
void* func_0018D5C0(s32 bytes);
extern s32 D_00274730;
typedef s32 (*Cmp_1BE0A8)(void* a, void* b);
void func_001BE068(u8* base, s32 stride, s32 rowB, s32 rowA);
s32 func_001BE980(void);
void func_0018D410(void* p);
s32 func_0011E048(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
struct Obj_1BE5F8 { s32 w0; s32 w4; u8 pad8[0xC]; s32 w14; u8 pad18[4]; s32 w1C; };
struct Local_1BE5F8 { s32 a; s32 b; };
void func_001BE5D8(void);
void func_0011E0E0(s32 a0, void (*a1)(void), u64 a2);
struct Local_1BE728 { s32 a; s32 b; };
void func_0011D420(void);
void* func_001925F0(void);
typedef s32 (*VFn_001BF3D0)(void* self);
struct Obj_001BF3D0 {
    VFn_001BF3D0* vtbl;
};
f32 func_001BF5E0(void* self);
void func_001BF200(f32 r, void* self, f32* out, s32* flag, f32 a, f32 b, f32 c);
struct Obj_1BE860 { u8 pad0[0x18]; void* f18; u8 pad1[0x34]; f32 f50; f32 f54; };
void func_0011D798(void* a0, s32 a1, s32 a2);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BE860(void* self);
void func_001BF718(void* slot);
struct Rec_1BEB10 { s32 f0; s32 f4; s32 f8; u8 pad0[8]; s32 f14; s32 f18; s32 f1C; };
void func_001BEA78(void);
void func_001BE1E8(void);
s32 func_0011E1F8(s32 a);
void func_001BEAC8(s32 h);
void func_0011D2A8(s32 a0, s32 a1, void* a2, s32 a3);
void func_0018D800(void* dst, void* src, s32 count);
s32 func_00152720(void* a);
void* func_001BED98(void);
struct Item_1BD558 { u8 pad0[0xD0]; Item_1BD558* next; };
struct Node_1BD558;
struct Group_1BD558 { Item_1BD558* items; Group_1BD558* next; u8 pad[4]; Node_1BD558* child; };
struct GroupHead_1BD558 { Group_1BD558* first; };
struct Node_1BD558 { u8 pad0[0x480]; GroupHead_1BD558* groups; u8 pad1[0x4B4 - 0x484]; Item_1BD558* items; u8 pad2[0x538 - 0x4B8]; u64 flags; };
s32 func_0011D708(s32 handle);
extern f32 D_00261858[];
struct Frame_1BDD00 { s32 list; s32 cursor; s32 link; s32 prev; };
struct Cnt_1BDD00 { s32 pad; s32 n1; s32 n2; };
struct Cls_1BDD00;
struct Node_1BDD00;
typedef void (*VFn_1BDD00)(Node_1BDD00* self, s32 a, f32 f);
struct Cls_1BDD00 {
    u8 pad0[8];
    s32 flags;
    u8 pad0C[0x70];
    VFn_1BDD00 fn7C;
};
struct Node_1BDD00 {
    Cls_1BDD00* cls;
    u8 pad4[0x224];
    s32 f228;
    u8 pad22C[0x30C];
    u64 flags538;
};
struct Item_1BDD00 {
    u8 pad0[0x414];
    Item_1BDD00* next;
};
void func_0018D608();
void func_0018D6F0();
void func_001BD678(Node_1BDD00* n, s32* c1, Node_1BDD00** a1, s32* c2, Node_1BDD00** a2);
void func_001BDA50(World* ctx, s32 n, Node_1BDD00** arr, f32 f, s32 flags);
s32 func_00129D70(Node_1BDD00* n);
void func_00129DF8(Node_1BDD00* n);
void func_0011E0B0(s32 a0);
struct Ent_1BE4A8 { u8 pad[0]; };
struct Ent_1BFAF8 { s32 a; s32 b; };
extern Ent_1BFAF8 D_00245020[];
s32 func_001BE268(Ent_1BE4A8* e);
struct Sel_1BE568;
struct Pair_1BE568 { s32 key; s32 w4; };
extern u8 D_006047B0[];
extern u8 D_006047D0[];
void func_001BE4A8(Sel_1BE568* self);
// NEAR: the lui of D_0026185C is scheduled before the sw of self->idx; retail stores idx first. Otherwise every instruction matches.

struct Idx_1BFAF8;
struct Link_1BFAF8;
struct Node_1BFAF8 {
    s32 idx;            // 0x00
    u8 pad04[0x04];
    s32 link;           // 0x08
    u8 pad0c[0x04];
    f32 f10;            // 0x10
    u8 pad14[0x04];
    s32 f18;            // 0x18
    u8 pad1c[0x24];
    s32 f40;            // 0x40
    u8 pad44[0x0C];
    f32 f50;            // 0x50
    u8 pad54[0x04];
    f32 f58;            // 0x58
    u8 pad5c[0x1C];
    f32 f78;            // 0x78
};
s32 func_001BE4A8(Idx_1BFAF8* idx);
s32 func_0011D598(Link_1BFAF8* a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_001BF428(Node_1BFAF8* self);
void func_001BF7F8(Node_1BFAF8* self, f32 x);
void func_001BE860(Node_1BFAF8* self);
// NEAR: first load of the chain pointer lands in $v1 and the sum in $v0, retail has them in $v0/$v1; one instruction short so the final branch targets 0x1BF028 instead of 0x1BF02C

struct Frame_1BEF88 { s32 f0; s32 f4; s32 f8; s32 fC; };
s32 func_00152720(Frame_1BEF88* p);
// NEAR: 23 diff lines, register allocation only: queue index in t1 (retail) vs v1 (ours), mask built in a0 vs a2, cleanup counter in t1 vs a0

struct Obj_1BD678;
struct Node_1BD678;
struct Holder_1BD678 {
    Node_1BD678* head;
};
struct Node_1BD678 {
    Obj_1BD678* list0;
    Node_1BD678* next4;
    u8 pad[4];
    Obj_1BD678* owner;
};
struct Obj_1BD678 {
    u8 pad0[0x480];
    Holder_1BD678* holder480;
    u8 pad1[0x538 - 0x484];
    u64 flags;
};
struct Ent_1BF7F8 {
    s32 idx;
    s32 f4;
    s32 f8;
    u8 pad0C[0xC];
    s32 f18;
    u8 pad1C[0x14];
    s32 f30;
    u8 pad34[0x24];
    f32 f58;
    f32 f5C;
    s32 f60;
    u8 pad64[8];
    s32 flag6C;
    s32 f70;
    s32 clampv(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) {
            return lo;
        }
        if (hi < v) {
            return hi;
        }
        return v;
    }
};
s32 func_0011D7D8(s32 a, s32 b);
void func_0011D810(s32 x, s32 y);
struct Ent_1BE268 { s32 w0; s32 w4; s32 w8; s32 wC; s32 w10; s32 w14; s32 w18; s32 w1C; };
struct Pair_1BE268 { s32 id; s32 arg; };
extern const Ent_1BE268 D_00244F40[7];
void func_0011D450(void);
void func_0018D410(KeyId* p);
s32 func_00203828(s32 a);
s32 func_0011D140(s32 a, s32 b);
s32 func_0011D760(s32 a, s32 b);
struct Eight_1BFCD8 { u8 b[8]; };
struct __attribute__((aligned(16))) Buf_1BFCD8 {
    u8 p0[0x50]; f32 f50;
    u8 p54[0x64 - 0x54]; Eight_1BFCD8 f64;
    u8 p6C[0x74 - 0x6C]; f32 f74; f32 f78;
    u8 p7C[0x90 - 0x7C];
};
struct Glob_1BFCD8 { u8 p[0x1D70]; s32 f1D70; };
enum Id_1BFCD8 { ID_1BFCD8_NONE = -1 };
s32 func_001BE568(Id_1BFCD8 id);
s32 func_001BE4A8(Id_1BFCD8 id);
void func_001BF920(Buf_1BFCD8* buf, Buf_1BFCD8** out, s32 a2, s32 a3, s32 a4, f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* a5, s32 a6);
void func_0011D798(Id_1BFCD8 a0, s32 a1, s32 a2);
void func_001BFBF8(Buf_1BFCD8* b);
void func_001BFAF8(Buf_1BFCD8* b, s32 id);
s32 func_0011D598(Id_1BFCD8 a, s32 b, s32 c, s32 d, s32 e, s32 f);
struct Arg_1BF5E0;
struct Obj_1BF5E0;
typedef f32 (*Fn_1BF5E0)(Obj_1BF5E0* self, Arg_1BF5E0* arg);
struct Node_1BEE48;
struct List_1BEE48 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_1BEE48 { List_1BEE48* list; u8* link; s32 offset; Iter_1BEE48* saved; };
struct World_1BEE48 { u8 pad[0x1BC4]; List_1BEE48 list; };
void func_001BEDF8(Node_1BEE48* node);
struct Next_1BEE48 {
    static Node_1BEE48* Of(Iter_1BEE48* it)
    {
        Node_1BEE48* node = *(Node_1BEE48**)it->link;
        it->link = (u8*)node + it->offset;
        return node;
    }
};
struct Begin_1BEE48 {
    static void Of(Iter_1BEE48* it, List_1BEE48* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_1BEE48*)g_activeListFrames);
        g_activeListFrames = (ListFrame*)it;
    }
};
Contact03* func_001B5EC0(u8* p);
void func_001861E8(u8* a, Contact03* b);
struct B8_1BF920 { u8 b[8]; };
struct Q16_1BF920 { u64 a; u64 b; } __attribute__((aligned(16)));
struct Obj_1BF920 {
    u8 pad0[4];
    s32 f04;
    u8 pad8[4];
    Obj_1BF920* f0C;
    f32 f10;
    f32 f14;
    u8 pad18[8];
    Q16_1BF920 f20;
    u8* f30;
    f32 f34;
    f32 f38;
    s32 f3C;
    u8 pad40[4];
    s32 f44;
    s32 f48;
    u8 f4C;
    u8 pad4D[3];
    f32 f50;
    s32 f54;
    f32 f58;
    f32 f5C;
    u8 pad60[4];
    B8_1BF920 f64;
    u8 pad6C[0xC];
    union { B8_1BF920 v; f32 f; } f78;
    union { B8_1BF920 v; f32 f; } f80;
};
void* func_001F5C0C(Obj_1BF920* p, s32 v, s32 n);
s32 func_001EAA70(s32 a, s32 b);
void func_001BF620(Q16_1BF920* self, f32* out, s32* flag, f32 a, f32 b, f32 c);
void func_001BF428(Obj_1BF920* self);
struct Frame_1BDA50;
struct Ctx_1BDA50;
struct Buf_1BDA50 { u8 b[0x100]; };
struct List_1BDA50 { u8* first; s32 pad04; s32 offset; };
struct Frame_1BDA50 { List_1BDA50* list; u8** link; s32 offset; Frame_1BDA50* prev; };
struct Item_1BDA50 {
    u8 pad0[0x2D8];
    List_1BDA50 list;
    u8 pad2E4[0x254];
    u64 flags;
};
struct Begin_1BDA50 {
    static void Of(Frame_1BDA50* it, List_1BDA50* list)
    {
        it->list = list;
        it->link = (u8**)list;
        it->offset = list->offset;
        it->prev = ((Frame_1BDA50*)g_activeListFrames);
        g_activeListFrames = (ListFrame*)it;
    }
};
struct Next_1BDA50 {
    static u8* Of(Frame_1BDA50* it)
    {
        u8* obj = *it->link;
        it->link = (u8**)(obj + it->offset);
        return obj;
    }
};
struct End_1BDA50 {
    static void Of(Frame_1BDA50* it) { g_activeListFrames = (ListFrame*)it->prev; }
};
s32 func_001BD558(s32 n, Item_1BDA50** arr, s32 cap, Buf_1BDA50* buf);
void func_001BCD00(Ctx_1BDA50* ctx, s32 n, Item_1BDA50** arr, s32 v, Buf_1BDA50* buf, f32 f, s32 ex);
void func_001BD888(s32 n, Item_1BDA50** arr);
void func_001BD790(u8* node, s32 flag);
struct Ent_1C0070;
struct Frame_1C0070 : ListFrame {
    Ent_1C0070* Next() { Ent_1C0070* n = *(Ent_1C0070**)link; link = (u8*)n + offset; return n; }
};
struct Ent_1C0070 {
    s32 f0; s32 f4; s32 f8; u8 pad0c[0x08]; f32 f14;
    s32 f18; u8 pad1c[0x04];
    u8 f20[0x10];
    BaseObject* f30; f32 f34; f32 f38; s32 f3C; s32 f40; s32 f44; s32 f48; u8 f4C;
    u8 pad4d[3];
    s32 f50; s32 f54; f32 f58; u8 pad5c[0x18];
    f32 f74; f32 f78;
};
struct Pair_1C0070 { s32 a; s32 b; };
extern Pair_1C0070 D_00245024[];
s32 func_001BF1F0(void);
void* func_001BF3D0(void);
typedef f32 (*Fn_1C0070)(void* a, void* b);
s32 func_0011D708(ListFrame* h);
s32 func_00182FC8(BaseObject* o);
void func_0011D600(s32 h);
void func_0011D730(s32 h, void (*fn)(void), s64 arg);
void func_001BFFC8(void);
void func_001BFBF8(Ent_1C0070* e);
void func_001BF200(f32 r, void* pos, s32* o1, s32* o2, f32 a, f32 b, f32 c);
void func_001BF428(Ent_1C0070* e);
void func_001BF7F8(Ent_1C0070* e, f32 x);
void func_001BE860(Ent_1C0070* e);
void func_001BF788(Ent_1C0070* e, s32 n);
void func_00130110(void* p);
void func_001C27B0(s32 a, s32 b);
s32 func_0011D4E0(s32 flag);
struct Pk8_1C0A50 { u64 v; } __attribute__((packed));
struct Ent_1C0A50 { s32 key; Pk8_1C0A50 a; Pk8_1C0A50 b; };
extern Pk8_1C0A50 D_00274820;
extern Pk8_1C0A50 D_00274828;
extern s32 D_006053E0[];
s32 func_0011D8F0(s32 a, s32 b);
void func_00182ED0(void* self);
void func_00152600(void* table, void* self);
void func_001C0C08(s32 index, s32 value);
void func_001B6438(s32 p);
s32 func_001B6290(s32 p, void* ctx, s32 a2, s32 a3);
void func_00182D48(void* self);
void func_00152470(void* table, void* self);
void func_001830D8(void* self);
struct Entry_1C1390 { s32 key; void* value; };
extern u8 D_00259F38[];
void func_0011A6C0(void* a, void* b);
void func_0011D480(s32 a, s32 b);
extern s32 D_00274808[6];
void func_0011E328(s32 a, s32 b);
void func_0011E360(s32 a, s32 b, s32 c);
struct Pt_1C0AB8 { f32 x; f32 y; };
struct Ent_1C0AB8 { s32 key; f32 a0; f32 a1; f32 b0; f32 b1; };
extern f32 D_00274838[11][4];
void func_0011D480(s32 slot, s32 value);
void func_001C0600(s32 column);
struct __attribute__((packed)) Pk8_1C0B38 { u64 v; };
struct Ent_1C0B38 { s32 key; Pk8_1C0B38 a; Pk8_1C0B38 b; };
extern u8 D_002748E8[4];
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, void* a4, void* a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
struct Packed_001C0B08 { u64 value; } __attribute__((packed));
void func_0011E010(void);
void func_0011E110(s32 a0);
s32 func_0011E1F8(s32 flag);
void func_001C0808(s32 a0);
void func_001BEE48(void);
void func_001C0CB0(void);
struct Rec_1C1530 { s32 a; R11B008Node* head; s32 cnt; };
typedef void (*Cb_1C1530)(void* a, void* b);
struct Obj_1C2238 { u8 pad[4]; R11B008List* f4; };
void* func_001C14C0(void* a, s32 b);
void func_001C1F20(ScriptValue* self, void* a, void* b, ScriptValue* c);
struct Obj_1C22B8 { u8 pad[4]; R11B008List* f4; };
struct Ring_1C25B0 {
    s32 f0;
    s32 f4;
    s32 f8[8];
    s32 f28[0x20 / 4];
    s32 f48;
    s32 f4C;
};
struct Dma_1C25B0 {
    s32 f0;
    u8 pad4[0x7C];
    s32 f80;
};
extern Dma_1C25B0* D_00261F20;
s32 func_00202C38(Dma_1C25B0* d, s32 b, s32 c);
void func_00202B68(Dma_1C25B0* d);
extern f32 D_00274758[11][4];
struct Pair_1C08B0 { s32 a; s32 b; };
struct Stack_1C08B0 { u8 pad0[0x2328]; Pair_1C08B0 pairs[4]; s32 count; };
extern s32 D_00274808[];
void func_0011E328(s32 channel, s32 value);
void func_0011E360(s32 channel, s32 value, s32 value2);
struct Pair_1C0950 { s32 a; s32 b; };
struct Stack_1C0950 { u8 pad0[0x2328]; Pair_1C0950 pairs[4]; s32 count; };
struct List_1C1A28 { s32 type; R11B008Node* head; R11B008Node* tail; };
struct Desc_1C15D8;
typedef void (*Get_1C15D8)(void* obj, void* out);
typedef void* (*Base_1C15D8)(void* obj, s32 z);
struct Desc_1C15D8 {
    s32 kind;
    u32 flags;
    s32 pad8;
    s32 off;
    s32 imm;
    s32 imm2;
    s32 pad18;
    Base_1C15D8 base;
};
void func_001F5C0C(void* p, s32 v, s32 n);
void func_001C15D8(ScriptValue* t, s32 value, Desc_1C15D8* d);
s32 func_001C0CF0(void);
struct KeyPair_1C14C0 { s32 key; s32 value; };
struct KeyTable_1C14C0 { s32 count; KeyPair_1C14C0* items; };
struct KeyRef_1C14C0 { s32 pad0; s32 index; };
struct KeyHolder_1C14C0 { KeyRef_1C14C0* ref; };
extern KeyTable_1C14C0 D_00244950[];
struct TabA_24D2A8 { s32 v[42]; };
struct TabB_24D350 { s32 v[25]; };
extern const TabA_24D2A8 D_0024D2A8;
extern const TabB_24D350 D_0024D350;
extern s32 D_00274830;
// (if/else with the small path first moved $s0/$s1)
struct Obj_1C21A0 { u8 pad[4]; R11B008List* f4; };
void func_001C15D8(ScriptValue* self, void* a, s32 r);
struct Owner_1C0C08 { u8 pad0[1]; };
void func_0011D8B0(Owner_1C0C08* a0, s32 a1, s32 a2);
void func_00182C18(BaseObject* self);
struct E_1C1190 { R11B008Node* a; s32 b; };
s32 func_00137C40(void* src);
void* func_0018D500(u32 size);
void func_00138518(void* self);
s32 func_0011A630(void);
void func_0011A6C0(u8* a, s32 b);
void* func_0011A358(ScriptValue* out, s32 a, s32 b, ScriptValue* body);
extern s32 D_00275714;
// NEAR: the entry pointer is loaded into v0 where retail uses v1 (register choice only); five lines differ.

struct Ent_1C13E8 { R11B008Node* a; s32 b; };
void func_0011A080(ScriptValue* t, R11B008Node* node, s32 b);
struct Cmd_1C1AD8 { u32 kind; R11B008Node* list; };
struct __attribute__((aligned(16))) Blob_1C1BF8 { Quad16 q[3]; };
struct W8_1C1BF8 { s32 a, b; };
struct W12_1C1BF8 { s32 a, b, c; };
struct Rec3_1C15D8 { s32 a, b, c; };
struct D8_1C15D8 { s32 a, b; };
extern void* func_0011C508(void);
extern void* func_0011C618(void);
extern void* func_001884E0(void* d, void* s);
extern void func_001884C0(void* d);
extern void* func_0011C748(void);
extern void* func_0011C858(void);
extern void* func_0011C968(void);
struct List_1C0808 {
    u8* first;
    s32 pad04;
    s32 offset;
};
struct Iter_1C0808 {
    List_1C0808* list;
    u8** link;
    s32 offset;
    Iter_1C0808* prev;
};
void func_001BF788(u8* obj, void* item);
struct Begin_1C0808 {
    static void Of(Iter_1C0808* it, List_1C0808* list)
    {
        it->list = list;
        it->link = (u8**)list;
        it->offset = list->offset;
        it->prev = (Iter_1C0808*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)it;
    }
};
struct Next_1C0808 {
    static u8* Of(Iter_1C0808* it)
    {
        u8* obj = *it->link;
        it->link = (u8**)(obj + it->offset);
        return obj;
    }
};
struct End_1C0808 {
    static void Of(Iter_1C0808* it)
    {
        g_activeListFrames = (ListFrame*)it->prev;
    }
};
struct Tag_1C2430 { u64 lo; u64 hi; };
struct Slot_1C2430 {
    Tag_1C2430* tags;
    u32 base;
    u32 addrs[8];
    s32 sizes[8];
    s32 count;
    s32 state;
};
struct Chan_1C2430 {
    u32 f0;
    u8 pad4[0x7C];
    u32 f80;
};
extern Chan_1C2430* D_00261F24;
typedef char* VaList_1C2430;
s32 func_00202C38(void* p, s32 a, s32 b);
void func_00202A80(Chan_1C2430* c, u32 addr);
void func_001C05D0(f32 x);
void func_001C06A0(s32 row, s32 column, f32 value);
void func_001C0760(s32 flag);
s32 func_001C0790(s32 value);
void func_001C07B0(void);
void func_001C0808(void* item);
void func_001C08B0(Stack_1C08B0* self, s32 a, s32 b);
void func_001C0950(Stack_1C0950* self);
void func_001C09D8(World* self, s32 index, s32 value);
void func_001C0A50(World* self, s32 key);
void func_001C0AB8(World* self, Pt_1C0AB8* p);
void func_001C0B08(World* self, Packed_001C0B08* item);
void func_001C0B38(World* self);
void func_001C0C08(s32 idx, s32 val);
s32 func_001C0C50(s32 index);
void func_001C0C68(s32 i);
s32 func_001C0CF0();
void func_001C0EC0(void);
void func_001C1190(World* self, BufferedStream* arg);
void* func_001C1390(s32 index, World* self);
ScriptValue* func_001C13E8(ScriptValue* self, s32 index, World* ctx);
s32 func_001C14C0(KeyHolder_1C14C0* self, s32 key);
ScriptValue* func_001C1530(ScriptValue* self, void* ctx, s32 v, Cb_1C1530 cb);
ScriptValue* func_001C15D8(ScriptValue* out, void* base, Desc_1C15D8* d);
s32 func_001C1A28(List_1C1A28* self, s32 value);
s32 func_001C1AD8(Cmd_1C1AD8* cmd, s32* val);
ScriptValue* func_001C1BF8(ScriptValue* out, s32 n, ScriptValue* args, const u32* kinds, void** dsts);
ScriptValue* func_001C1E48(ScriptValue* self, s32 n, s32* keys, s32* vals);
ScriptValue* func_001C21A0(ScriptValue* self, Obj_1C21A0* p, s32 n);
ScriptValue* func_001C2238(ScriptValue* self, Obj_1C2238* p, s32 key, ScriptValue* value);
ScriptValue* func_001C22B8(ScriptValue* self, Obj_1C22B8* p, s32 key, ScriptValue* value);
ScriptValue* func_001C2320(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* func_001C23B0(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...);
void func_001C2430(s32 size, ...);
void func_001C25B0(s32 first, ...);
void func_001C29C8();

Collider* func_001BB540(Collider* node, s32 offset);
extern const s32 D_00246838[772];

// The file's .data, in retail's order.
f32 D_002746C0[4] = { 0.0f, 3.0f, 0.0f, 0.0f };
f32 D_002746D0[4] = { 0.0f, 0.75f, 0.0f, 0.0f };
Entry_1BB028 D_002746E0[8] = {
    { &D_00248D30, 0 },
    { &D_00248D30, 3 },
    { &g_unitXVector, 2 },
    { &g_unitYVector, 2 },
    { &g_unitZVector, 2 },
    { &g_unitZVector, 1 },
    { &g_unitYVector, 1 },
    { &g_unitXVector, 1 },
};
s32 D_00274720 = 0;
s32 D_00274724 = 0;
s32 D_00274728 = 0;
s32 D_0027472C = 0;
s32 D_00274730 = 0;
s32 D_00274734 = 0;
s32 D_00274738 = 0;
s32 D_0027473C = 0;
s32 D_00274740 = -1;
s32 D_00274744 = 0;
s32 D_00274748 = 0;
s32 D_0027474C = 0;
f32 D_00274750 = -2.0f;
s32 D_00274754 = 3;
f32 D_00274758[11][4] = { 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
s32 D_00274808[6] = { 0, 2, 3, 4, 9, 1 };
Pk8_1C0A50 D_00274820 = { 0x40C0000040800000ULL };
Pk8_1C0A50 D_00274828 = { 0x45FA0000453B8000ULL };
s32 D_00274830 = 0;
f32 D_00274838[11][4] = { 0 };
u8 D_002748E8[4] = { 0 };
s32 D_002748EC = 0;
Ring_1C25B0 D_002748F0[2] = { { 0 } };
s32 D_00274990 = 0;

void func_001B7968(Collider* self)
{
    ScriptValue local;
    s32 s0;
    InitScriptValue(&local);
    SetListLinkOffset(&self->parts, 0x2E4);
    InitPlacedObject(self);
    ClearRecordBody(&self->mesh);
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

ASM_FUNC(func_001B7D00);

ASM_FUNC(func_001B7F78);

ASM_FUNC(func_001B8148);

ASM_FUNC(func_001B8420);

ASM_FUNC(func_001B8540);

ASM_FUNC(func_001B8820);

void func_001B8960(Collider* self)
{
    ComputePlacedObjectWorldFrame(self);
    TransformMeshToWorld(&self->mesh, &self->meshCopy, *(Quad_1B8960*)&self->v140, &self->m110);
    TransformMeshToWorld(&self->mesh2, &self->mesh2Copy, *(Quad_1B8960*)&self->v140, &self->m110);
}

void func_001B89B8(Collider* self)
{
    RecomputePlacedObjectFrame(self);
    self->root03()->desc03()->m32(self->root03());
    ClearRootObjectStateBits(self->world, self, 7);
    func_001389C8(self->world);
}

s32 func_001B8A08(Collider* a, Collider* b)
{
    u64 m1 = 0x8080;
    s32 r = 0;
    m1 <<= 40;
    if ((a->flags538 & m1) != 0) {
        u64 bf = b->flags538;
        u64 m2 = 0x8000;
        m2 <<= 40;
        if ((bf & m2) != 0) {
            return 1;
        }
    }
    return r;
}

void func_001B8A48(Collider* self)
{
    ContactRow03* node = self->contacts->head;
    while (node != 0) {
        Contact03* it = node->head;
        while (it != 0) {
            if (0.0001f < it->timer) {
                for (s32 i = 0; i < 2; i++) {
                    Collider* obj = FindHandlerForSlot(it->end[i].part, 0x114);
                    if (obj != 0) {
                        void (*fn)(Collider*, Contact03*, s32) = obj->desc03()->m41;
                        if (fn != 0) {
                            fn(obj, it, i);
                        }
                    }
                }
                *(s32*)&it->timer = 0;
            }
            if (node->head == 0) {
                break;
            }
            it = it->next;
        }
        node = node->next;
    }
}

ASM_FUNC(func_001B8B30);

INCLUDE_RODATA(jtbl_0024D280);
ASM_FUNC(func_001B8B90);

ASM_FUNC(func_001B8FE0);

ASM_FUNC(func_001B8FE8);

ASM_FUNC(func_001B9058);

ASM_FUNC(func_001B91A8);

void func_001B9338(Collider* self, f32 t)
{
    Vec_1B9338 local;
    Attach03* node;
    u64 m = 0x8000;
    m <<= 36;
    if (self->parent == 0) {
        if ((self->flags538 & m) == 0) {
            ConstrainColliderVector(self, &self->v440, &self->gravity, &local, 0);
            AddColliderForce(self, &local);
        }
    }
    node = self->attached;
    if (node != 0) {
        do {
            Collider* obj = node->owner;
            obj->desc03()->m33(obj, node, t);
            node = node->next;
        } while (node != 0);
    }
}

void func_001B93D8(Collider* self, void* a, void* m)
{
    func_001261C0(self, a, m);
}

void func_001B93F8(Collider* self)
{
    UpdatePlacedObject(self);
}

void func_001B9418(Collider* self, f32 v)
{
    f32 a = self->mass;
    f32 q = v / a;
    self->mass = a * q;
    ComputeColliderInverseInertia(self);
}

ASM_FUNC(func_001B9448);

void func_001B94F0(Collider* self, s32 mode)
{
    Collider* ctx = self->root03();
    if (ctx == 0) {
        return;
    }
    if (mode != 0) {
        Contact03* freed = 0;
        for (ContactRow03* o = ctx->contacts->head; o != 0; o = o->next) {
            Contact03** pp = &o->head;
            Contact03* it;
            while ((it = *pp) != 0) {
                s32 other = it->end[0].body != ctx;
                ContactEnd03* p = &it->end[other];
                s32 hit;
                switch (mode) {
                case 1:
                    hit = IsObjectDescendantOf(p->part, self);
                    break;
                case 2:
                    hit = p->part == self;
                    break;
                case 3:
                    hit = 0;
                    if (p->part == self && other == 0) {
                        if (it->kind >= 8 && it->kind <= 9) {
                            hit = 1;
                        }
                    }
                    break;
                default:
                    hit = 0;
                    break;
                }
                if (hit != 0) {
                    *pp = it->next;
                    it->next = freed;
                    freed = it;
                } else {
                    pp = &it->next;
                }
            }
            *o->link = o->head;
        }
        FreePooledContactChain(self->world, freed);
    }
    ctx->f4B8 = 0;
}

void func_001B9680(Collider* self)
{
    self->v370 = self->v140;
}

ASM_FUNC(func_001B9690);

void func_001B97E0(Collider* self, Mat02* src)
{
    self->rot.r[0] = src->r[0];
    self->rot.r[1] = src->r[1];
    self->rot.r[2] = src->r[2];
    if (self->root != 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
        DropColliderContacts(self, 1);
    }
    self->desc->m0E(self, 4, self);
}

ASM_FUNC(func_001B9860);

LINKER_REMNANT(func_001B9938);

ASM_FUNC(func_001B9940);

ASM_FUNC(func_001B99F0);

LINKER_REMNANT(func_001B9AA8);

ASM_FUNC(func_001B9AB0);

ASM_FUNC(func_001B9AC8);

void func_001B9AE0(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4)
{
    self->mode450 = a1;
    u64 flag = (self->flags538 >> 54) & 1;
    if (a2 != 0) {
        self->v440 = *a2;
    }
    self->mode470 = a3;
    if (a4 != 0) {
        self->v460 = *a4;
    }
    Collider* sub = self->root03();
    if (sub != 0) {
        s32 f2 = 0;
        if (a1 == 3) {
            f2 = (a3 == 3);
        }
        if (flag != f2) {
            UpdateAnchorModeFlags(sub);
        }
    }
}

void func_001B9B50(Collider* self, BaseObject* p)
{
    Quad_1B9B50 local0;
    Quad_1B9B50 local1;
    if (self->parent == p) {
        return;
    }
    Collider* s5 = self->root03();
    func_001280C0(self->parent, 0, &self->v440, &local0);
    func_001280C0(self->parent, 0, &self->v460, &local1);
    ReparentPlacedObject(self, p);
    func_001280C0(0, p, &local0, &self->v440);
    func_001280C0(0, p, &local1, &self->v460);
    if (self->root != 0) {
        if ((self->flags538 & (1ULL << 54)) != 0 && s5 != 0) {
            UpdateAnchorModeFlags(s5);
        }
        Collider* f = self->root03();
        if ((f->flags538 & (1ULL << 55)) != 0) {
            UpdateAnchorModeFlags(f);
        } else {
            UpdateAnchorModeFlags(self);
        }
    }
    ResolveContactHandler(self);
}

ASM_FUNC(func_001B9C80);

LINKER_REMNANT(func_001B9D08);

ASM_FUNC(func_001B9D10);

LINKER_REMNANT(func_001B9F28);

void func_001B9F30(Collider* self, Out_1B9F30* out)
{
    Vec02 tmp[3];
    out->q10 = self->v140;
    out->q20 = self->v150;
    func_00189378(&self->m110, 0, &tmp[0]);
    out->f30 = ArctangentOfRatio(-tmp[0].y, -tmp[0].x);
    out->f34 = 100.0f;
    out->f00 = 0;
    out->f38 = g_gameTime[0];
    out->f3C = 0;
}

s32 func_001B9FB0(Collider* self, void* other)
{
    s32 key;
    Contact03* n;
    for (n = (Contact03*)GetContactRowHead(self, other), key = (s32)self->root; n != 0; n = n->next) {
        s32 s1 = (key ^ (s32)n->end[0].body) != 0;
        s32 o0 = s1 * 64;
        if (IsObjectDescendantOf(*(void**)((u8*)n + o0 + 4), self) != 0) {
            s32 o1 = (1 - s1) * 64;
            if (IsObjectDescendantOf(*(void**)((u8*)n + o1 + 4), other) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void* func_001BA068(Collider* self)
{
    Collider* s3 = self->root03();
    ContactRow03* s2 = s3->contacts->head;
    for (; s2 != 0; s2 = s2->next) {
        Contact03* s0 = s2->head;
        while (s0 != 0) {
            s32 s1 = ((u32)s3 ^ (u32)s0->end[0].body) != 0;
            if (IsObjectDescendantOf(*(void**)((u8*)(s0) + (s1 << 6) + 4), self) != 0) {
                return *(void**)((u8*)(s0) + ((1 - s1) << 6) + 4);
            }
            s0 = s0->next;
        }
    }
    return 0;
}

void func_001BA130(Collider* self, Collider* other)
{
    u64 bit = (self->flags538 >> 50) & 1;
    Link02 a, c, d;
    List01 b;
    a = self->link2D0;
    b = self->parts;
    c = self->link2E4;
    Contacts03* s480 = self->contacts;
    Collider* s4E4 = self->handler;
    d = self->link414;
    CopyPlacedObject(self, other);
    self->contacts = s480;
    self->link2D0 = a;
    self->parts = b;
    self->link2E4 = c;
    self->link414 = d;
    self->handler = s4E4;
    self->attached = 0;
    self->f4B8 = 0;
    self->flags538 = (self->flags538 & 0xFFFBFFFFFFFFFFFFULL) | (bit << 50);
    SetColliderPartListed(self, 1);
    if (self->meshCopy.vertCount) func_00160EA0(&other->meshCopy, 0, &self->meshCopy);
    if (self->tree.nodes) CloneTreeNodes(&other->meshCopy, &other->tree, &self->meshCopy, &self->tree);
    if (self->mesh2Copy.vertCount) func_00160EA0(&other->mesh2Copy, 0, &self->mesh2Copy);
    if ((s32)self->flags538) CloneTreeNodes(&other->mesh2Copy, &other->tree2, &self->mesh2Copy, &self->tree2);
    self->touching = 0;
    self->flags538 |= 0x20000000000ULL;
}

ASM_FUNC(func_001BA2E8);

ASM_FUNC(func_001BA430);

void func_001BA500(void* self, void* a, void* b, void* c, s32 d)
{
    ConstrainVectorByAnchor(a, b, c, d);
}

void func_001BA528(Collider* self, Attach03* node)
{
    node->next = self->attached;
    self->attached = node;
    ClearRootTries(self);
}

void func_001BA550(Collider* o, Attach03* node)
{
    Attach03** link = &o->attached;
    if (*link == 0) {
        goto tail;
    }
    if (o->attached == node) {
        o->attached = node->next;
    } else {
        Attach03* prev;
        for (;;) {
            prev = *link;
            Attach03* nx = prev->next;
            link = &prev->next;
            if (nx == 0) {
                goto tail;
            }
            if (nx == node) {
                break;
            }
        }
        prev->next = node->next;
    }
    node->next = 0;
tail:
    ClearRootTries(o);
}

ASM_FUNC(func_001BA5B0);

void func_001BAC28(Collider* self, Attach03* node, f32 dt)
{
}

void func_001BAC30(Collider* self, BufferedStream* in)
{
    s32 i;
    s32 j;
    s32 n;
    Pair03* e;
    u8 flag = ReadBufferedU8(in) & 1;
    self->flags = (self->flags & ~(1ULL << 33)) | ((u64)flag << 33);
    func_00137FB0(in, &self->mesh);
    self->radius3D0 = self->mesh.radius;
    self->radius3CC = self->mesh.radius;
    if (self->flags & (1ULL << 33)) {
        self->meshCopy = self->mesh;
    } else {
        func_00160EA0(&self->mesh, 0, &self->meshCopy);
    }
    ReadFaceTree(in, &self->meshCopy, &self->tree);
    i = 0;
    self->mass = ReadBufferedFloat(in);
    ReadBufferedRotation3(in, &self->inertia);
    ReadBufferedVector3(in, &self->offset);
    ComputeColliderInverseInertia(self, 1.0f);
    self->groupCount = ReadBufferedU16(in);
    self->groups = (Pair03*)AllocateFrontMemory(self->groupCount << 3);
    if (self->groupCount > 0) {
        do {
            e = self->groups;
            e += i++;
            e->a = ReadBufferedS16(in);
            e->b = ReadBufferedU16(in);
        } while (i < self->groupCount);
    }
    n = ReadBufferedU32(in);
    j = 0;
    self->nodeGroups = (s32*)AllocateFrontMemory(n << 2);
    if (n > 0) {
        do {
            s32 v = ReadBufferedS16(in);
            self->nodeGroups[j] = v;
            j++;
        } while (j < n);
    }
    self->refCount = ReadBufferedU32(in);
    i = 0;
    self->refs = (Pair03*)AllocateFrontMemory(self->refCount << 3);
    while (i < self->refCount) {
        e = self->refs;
        e += i++;
        e->a = ReadBufferedS16(in);
        e->b = ReadBufferedS16(in);
    }
    if (self->refCount > 0) {
        j = 0;
        self->faceStarts = (s32*)AllocateFrontMemory((self->meshCopy.faceCount + 1) << 2);
        if (self->meshCopy.faceCount >= 0) {
            do {
                s32 v = ReadBufferedS16(in);
                self->faceStarts[j] = v;
                j++;
            } while (self->meshCopy.faceCount >= j);
        }
    }
    func_00137FB0(in, &self->mesh2);
    if (self->flags & (1ULL << 33)) {
        self->mesh2Copy = self->mesh2;
    } else {
        func_00160EA0(&self->mesh2, 0, &self->mesh2Copy);
    }
    ReadFaceTree(in, &self->mesh2Copy, &self->tree2);
    LoadPlacedObject(self, in);
    SetColliderPartListed(self, 1);
    self->desc03()->m44(self);
    if (self->parent == 0) {
        self->desc03()->m32(self);
        InitContactPairFlags(self->world, self);
    }
}

void func_001BAFE0(Collider* self, f32 v)
{
    self->flags538 |= (u64)0x8000 << 25;
    self->radius3CC = v;
}

void func_001BB000(void* self)
{
    SetColliderAnchors(self, 3, 0, 3, 0);
}

void func_001BB028(s32 index, s32* out, Vec02* dst)
{
    *out = D_002746E0[index].value;
    *dst = *D_002746E0[index].quad;
}

ASM_FUNC(func_001BB058);

ASM_FUNC(func_001BB0C8);

void func_001BB138(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 32)) | ((u64)(value & 0xF) << 32); }

void func_001BB168(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(1ULL << 47)) | ((u64)(value & 1) << 47); }

void func_001BB1A0(Collider* self, s32 flag)
{
    self->flags538 = (self->flags538 & 0xFFFEFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 48);
}

void func_001BB1D8(Collider* self, u8 value) { self->b2C8 = value; }

void func_001BB1E0(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 36)) | ((u64)(value & 0xF) << 36); }

void func_001BB210(Collider* self, s32 kind, void* arg)
{
    SendObjectNotification(self, kind, arg);
    Attach03* n = self->attached;
    if (n != 0) {
        do {
            Attach03* next = n->next;
            Collider* obj = n->owner;
            if (obj != self) {
                void (*fn)(BaseObject*, s32, void*) = obj->desc->m0D;
                if (fn != 0) {
                    fn(obj, kind, arg);
                }
            }
            n = next;
        } while (n != 0);
    }
}

// The literal func_001BB290 loads.
extern const f32 D_0024D2A0 = 3.4028235e38f;

INCLUDE_ASM(func_001BB290);

void func_001BB378(Collider* self, s32 flag)
{
    self->flags538 = (self->flags538 & ~(1ULL << 51)) | ((u64)(flag & 1) << 51);
}

void func_001BB3B0(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 42;
    self->flags538 = (self->flags538 & ~(1ULL << 42)) | bit;
    DropColliderContacts(self, value != 0);
}

void func_001BB400(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 43;
    self->flags538 = (self->flags538 & ~(1ULL << 43)) | bit;
    DropColliderContacts(self, value != 0 ? 2 : 0);
}

void func_001BB450(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 44;
    self->flags538 = (self->flags538 & ~(1ULL << 44)) | bit;
    DropColliderContacts(self, value != 0 ? 3 : 0);
}

void func_001BB4A0(Collider* self)
{
    ListFrame frame;
    const Desc03* info = self->desc03();
    if (info->m41 != 0 || info->m3C != 0 || info->m3D != 0) {
        self->handler = self;
    } else if (info->m3E != 0) {
        self->handler = self;
    } else {
        Collider* p = (Collider*)self->parent;
        if (p != 0) {
            self->handler = p->handler;
        } else {
            self->handler = 0;
        }
    }
    Collider* c = (Collider*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) ResolveContactHandler(c);
        c = (Collider*)c->next;
    }
}

Collider* func_001BB540(Collider* node, s32 offset)
{
    Collider* s;
    while (node != 0 && (s = node->handler) != 0) {
        if (*(s32*)((u8*)s->desc + offset) != 0) return s;
        node = (Collider*)s->parent;
    }
    return 0;
}

void func_001BB580(Collider* self)
{
    ListFrame frame;
    s32 flag = 0;
    if (self->mode450 == 3) {
        flag = (self->mode470 == 3);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 54)) | ((u64)flag << 54);
    s32 s2 = flag & 1;
    s32 a0 = 0;
    if (self->flags538 & (1ULL << 54)) {
        if (self->parent == 0 || (((Collider*)self->parent)->flags538 & (1ULL << 56)) != 0) a0 = 1;
    }
    self->flags538 = (self->flags538 & ~(1ULL << 56)) | ((u64)a0 << 56);
    Collider* c = (Collider*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) {
            UpdateAnchorModeFlags(c);
            if ((c->flags538 & (1ULL << 55)) == 0) s2 = 0;
        }
        c = (Collider*)c->next;
    }
    u64 bit = (self->flags538 >> 55) & 1;
    if (bit != (u64)s2) {
        self->flags538 = (self->flags538 & ~(1ULL << 55)) | ((u64)(s2 & 1) << 55);
        if (self->parent == 0 && self->root != 0) {
            InitContactPairFlags(self->world, self);
        }
    }
}

s32 func_001BB710(Collider* self, s32 value)
{
    Collider* ctx = self->root03();
    ContactRow03* n = ctx->contacts->head;
    while (n != 0) {
        Contact03* e = n->head;
        while (e != 0) {
            s32 idx = ((u32)e->end[0].body ^ (u32)ctx) != 0;
            ContactEnd03* s = &e->end[idx];
            if (s->part == self) {
                void* tmp = e->end[1 - idx].part;
                if (ScriptListContainsValue(value, &tmp) == 0) {
                    if (AppendPropertyToScriptList(value, &tmp) == 0) return 0;
                }
            }
            e = e->next;
        }
        n = n->next;
    }
    return 1;
}

s32 func_001BB800(Collider* obj, s32* outCount, void*** outArr)
{
    Collider* own = obj->root03();
    ContactRow03* nd;
    Contact03* it;
    s32 n = 0;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (it = nd->head; it; it = it->next) {
            s32 g = it->end[0].body != own;
            if (IsObjectDescendantOf(*(void**)((u8*)it + (g << 6) + 4), obj))
                n++;
        }
    }
    void** arr = (void**)AllocateBackMemory(n << 2);
    void** end = arr;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (Contact03* it2 = nd->head; it2; it2 = it2->next) {
            s32 f = it2->end[0].body != own;
            if (IsObjectDescendantOf(*(void**)((u8*)it2 + (f << 6) + 4), obj)) {
                void* v = *(void**)((u8*)it2 + ((1 - f) << 6) + 4);
                void** p;
                for (p = arr; p < end; p++)
                    if (*p == v) break;
                if (!(p < end)) {
                    *end = v;
                    end++;
                }
            }
        }
    }
    *outArr = arr;
    s32 cnt = end - arr;
    *outCount = cnt;
    return cnt;
}

s32 func_001BB9A0(Touch03* node, Collider* value)
{
    while (node != 0) {
        if (node->obj == value) return 1;
        node = node->next;
    }
    return 0;
}

void func_001BB9D0(Collider* self)
{
    Collider* core = self->root03();
    ContactRow03* o;
    Contact03* e;
    Touch03* m;
    Touch03* prev;
    Collider* other;
    void* args;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                if (!IsInTouchingList(self->touching, other)) {
                    args = &other;
                    TriggerScriptEvent(self, 6, 1, &args);
                }
            }
        }
    }
    for (m = self->touching; m != 0; m = m->next) {
        s32 found = 0;
        for (o = core->contacts->head; o != 0 && !found; o = o->next) {
            for (e = o->head; e != 0 && !found; e = e->next) {
                s32 i = e->end[0].body != core;
                if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                    other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                    if (other == m->obj) found = 1;
                }
            }
        }
        if (!found) {
            args = m;
            TriggerScriptEvent(self, 7, 1, &args);
        }
    }
    FreeTouchNodes(self->world, self->touching);
    self->touching = 0;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                Touch03* n = AllocateTouchNode(self->world);
                n->obj = other;
                if (self->touching != 0) prev->next = n; else self->touching = n;
                prev = n;
            }
        }
    }
}

s32 func_001BBC30(Collider* self)
{
    return 0;
}

ASM_FUNC(func_001BBC38);

ASM_FUNC(func_001BBEB8);

void func_001BC088(Collider* self, void* b, f32 x)
{
    if (self->hook != 0) {
        func_001BBEB8(self);
    }
    func_00125440(self, x, b);
}

ASM_FUNC(func_001BC0E0);

ASM_FUNC(func_001BC260);

s32 func_001BC320(Collider* self, ObjectEvent* shape)
{
    if (shape->eventFlags & 0x8) {
        func_001BC0E0(self, shape->radius, (u8*)shape + 0x20, (u8*)shape + 0x30);
    }
    return shape->eventFlags != 0;
}

ASM_FUNC(func_001BC368);

void func_001BC4D8(Collider* self, Contact03** out)
{
    Contact03* freed = 0;
    if (self->root == self) {
        ContactRow03* h = self->contacts->head;
        if (h) {
            do {
                Contact03** pp = (Contact03**)h;
                Contact03* n;
                while ((n = *pp) != 0) {
                    int k = (n->end[0].body != self);
                    Collider* e = n->end[1 - k].part;
                    while (e && !e->f4E0) e = (Collider*)e->parent;
                    if (e) {
                        switch (e->f4E0) {
                        case 1: {
                            Contact03* c = TakePoolSlot((u8*)self->world + 0x1AFC);
                            *c = *n;
                            c->next = *out;
                            *out = c;
                            break;
                        }
                        case 3:
                            *pp = n->next;
                            n->next = freed;
                            freed = n;
                            continue;
                        case 4:
                            *pp = n->next;
                            n->next = *out;
                            *out = n;
                            continue;
                        }
                    }
                    pp = &n->next;
                }
                *h->link = h->head;
                h = h->next;
            } while (h);
        }
        FreePooledContactChain((u8*)self->world, freed);
    }
}

ASM_FUNC(func_001BC670);

void func_001BC710(Collider* self, u32 flag)
{
    self->flags538 = (self->flags538 & 0xFFEFFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 52);
}

void func_001BC748(Collider* self, u32* out)
{
    u32 bit = (u32)(self->flags538 >> 52) & 1;
    *out = bit;
}

void func_001BC760(Collider* self, s32* index, Collider** list)
{
    ListFrame frame;
    self->index = *index;
    list[*index] = self;
    (*index)++;
    for (Collider* item = (Collider*)self->children.head; item; item = (Collider*)item->next)
        if (item->desc->flags & 2)
            item->desc03()->m35(item, index, list);
}

ASM_FUNC(func_001BC7F8);

ASM_FUNC(func_001BC828);

ASM_FUNC(func_001BC978);

ASM_FUNC(func_001BCD00);

s32 func_001BD558(s32 count, Node_1BD558** roots, s32 cap, Item_1BD558** out)
{
    s32 n = 0;
    s32 i;
    Node_1BD558* root;
    for (i = 0; i < count; i++) {
        root = roots[i];
        root->flags |= ((u64)1 << 58);
        for (Item_1BD558* item = root->items; item; item = item->next) {
            if (n >= cap) goto done;
            out[n++] = item;
        }
        GroupHead_1BD558* gh = root->groups;
        for (Group_1BD558* g = gh->first; g; g = g->next) {
            if (g->child->flags & ((u64)1 << 58)) continue;
            for (Item_1BD558* item = g->items; item; item = item->next) {
                if (n >= cap) goto done;
                out[n++] = item;
            }
        }
    }
done:
    {
        Node_1BD558** r = roots;
        if (count > 0) {
            i = count;
            do {
                root = *r;
                i--;
                r++;
                root->flags &= ~((u64)1 << 58);
            } while (i != 0);
        }
    }
    return n;
}

void func_001BD678(Obj_1BD678* self, s32* outQueued, Obj_1BD678** queue, s32* outFlagged, Obj_1BD678** list)
{
    s32 nq = 1;
    s32 nl = 0;
    queue[0] = self;
    self->flags |= (u64)1 << 57;
    s32 qi;
    for (qi = 0; qi < nq; qi++) {
        Obj_1BD678* x = queue[qi];
        Node_1BD678* node = x->holder480->head;
        while (node != 0) {
            Obj_1BD678* y = node->owner;
            if ((y->flags & ((u64)1 << 57)) == 0 && node->list0 != 0) {
                if (y->flags & ((u64)1 << 55)) {
                    list[nl] = y;
                    nl++;
                } else {
                    queue[nq] = y;
                    nq++;
                }
                y->flags |= (u64)1 << 57;
            }
            node = node->next4;
        }
    }
    if (nl > 0) {
        qi = nl;
        Obj_1BD678** p = list;
        do {
            Obj_1BD678* z = *p;
            p++;
            z->flags &= ~((u64)1 << 57);
        } while (--qi != 0);
    }
    *outQueued = nq;
    *outFlagged = nl;
}

void func_001BD790(Collider* obj, s32 mode)
{
    if (mode) {
        u64 f = obj->flags538;
        u64 sv = obj->savedC0;
        sv &= ~(u64)1;
        sv |= (f >> 54) & 1;
        sv &= ~(u64)2;
        u64 b55 = (f >> 55) & 1;
        f |= (u64)1 << 54;
        s32 a = obj->mode450;
        s32 b = obj->mode470;
        f |= (u64)1 << 55;
        sv |= b55 << 1;
        obj->save90 = a;
        obj->save94 = b;
        obj->savedC0 = sv;
        obj->mode450 = 3;
        obj->mode470 = 3;
        obj->flags538 = f;
    } else {
        u64 bit0 = (s32)obj->savedC0 & 1;
        u64 bit1 = (u64)((s32)(obj->savedC0 >> 1) & 1);
        s32 a = obj->save90;
        s32 b = obj->save94;
        obj->mode450 = a;
        obj->mode470 = b;
        obj->flags538 = ((obj->flags538 & ~((u64)1 << 54)) | (bit0 << 54)) & ~((u64)1 << 55) | (bit1 << 55);
    }
}

void func_001BD888(s32 n, Collider** objs)
{
    s32 local[5];
    Collider** sorted;
    s32* counts;
    s32 i;

    if (n < 2) {
        return;
    }
    PushBackMemoryMark();
    sorted = (Collider**)AllocateBackMemory(n * 4);
    counts = (s32*)AllocateBackMemory(n * 4);
    FillMemory(counts, 0, n * 4);
    FillMemory(local, 0, 20);
    for (i = 0; i < n; i++) {
        Collider* o = objs[i];
        u32 cnt = 0;
        ContactRow03* p = o->contacts->head;
        while (p != 0) {
            if (p->head != 0 && (o->flags538 & 0x0080000000000000ULL) != 0) {
                cnt++;
                if (cnt >= 4) {
                    break;
                }
            }
            p = p->next;
        }
        counts[i] = cnt;
        if (cnt < 4) {
            local[cnt + 1]++;
        }
    }
    i = 1;
    do {
        local[i] += local[i - 1];
        i++;
    } while ((u32)i < 5);
    for (i = 0; i < n; i++) {
        s32 cnt = counts[i];
        s32 idx = local[cnt];
        sorted[idx] = objs[i];
        local[cnt] = idx + 1;
    }
    CopyMemory(objs, sorted, n * 4);
    PopBackMemoryMark();
}

void func_001BDA50(Ctx_1BDA50* ctx, s32 n, Item_1BDA50** arr, f32 f, s32 ex)
{
    Buf_1BDA50 buf;
    Frame_1BDA50 it;
    s32 v = CollectGroupItems(n, arr, 0x40, &buf);
    if (v < 0x40 || n < 2) {
        func_001BCD00(ctx, n, arr, v, &buf, f, ex);
        return;
    }
    SortCollidersByContactCount(n, arr);
    s32 half = n / 2;
    s32 i;
    u8* p;
    for (i = 0; i < half; i++) {
        arr[i]->flags |= 1ULL << 58;
    }
    ProcessColliderGroup(ctx, n - half, arr + half, f, ex);
    for (i = 0; i < half; i++) {
        arr[i]->flags &= ~(1ULL << 58);
    }
    for (i = half; i < n; i++) {
        Begin_1BDA50::Of(&it, &arr[i]->list);
        for (p = Next_1BDA50::Of(&it); p; p = Next_1BDA50::Of(&it)) {
            SetColliderForcedState(p, 1);
        }
        End_1BDA50::Of(&it);
    }
    ProcessColliderGroup(ctx, half, arr, f, ex);
    for (i = half; i < n; i++) {
        Begin_1BDA50::Of(&it, &arr[i]->list);
        for (p = Next_1BDA50::Of(&it); p; p = Next_1BDA50::Of(&it)) {
            SetColliderForcedState(p, 0);
        }
        End_1BDA50::Of(&it);
    }
}

void func_001BDD00(World* self, s32 flags, f32 f)
{
    Frame_1BDD00 fr;
    Cnt_1BDD00 c;
    Node_1BDD00** arr1;
    Node_1BDD00** arr2;
    s32 j;
    s32 i;
    Node_1BDD00* s;
    PushBackMemoryMark();
    arr1 = (Node_1BDD00**)AllocateBackMemory(self->count38 * 4);
    c.n1 = 0;
    arr2 = (Node_1BDD00**)AllocateBackMemory(self->count38 * 4);
    c.n2 = 0;
    SyncDataCache(0);
    if (flags & 1) {
        s32 e = (s32)&self->list60;
        fr.cursor = e;
        fr.list = e;
        s32 old = (s32)g_activeListFrames;
        s32 link = *(s32*)(e + 8);
        g_activeListFrames = (ListFrame*)&fr;
        fr.prev = old;
        s32 h = *(s32*)e;
        fr.link = link;
        fr.cursor = h + link;
        s32 p = h;
        while (p != 0) {
            Node_1BDD00* node = (Node_1BDD00*)p;
            if (!(node->cls->flags & 2) || (node->flags538 & (1ULL << 55))) {
                if (node->f228 < 2) {
                    node->cls->fn7C(node, 0, g_gameClock[2]);
                }
            }
            s32 nx = *(s32*)fr.cursor;
            fr.cursor = nx + fr.link;
            p = nx;
        }
        g_activeListFrames = (ListFrame*)fr.prev;
    }
    for (s = (Node_1BDD00*)self->list6C.head; s != 0; s = (Node_1BDD00*)((Item_1BDD00*)s)->next) {
        if (s->flags538 & (1ULL << 57)) continue;
        if (s->flags538 & (1ULL << 55)) continue;
        CollectConnectedColliders(s, &c.n1, arr1, &c.n2, arr2);
        if (flags & 1) {
            for (i = 0; i < c.n1; i++) {
                if (arr1[i]->f228 < 2) break;
            }
            if (i >= c.n1) {
                for (j = 0; j < c.n2; j++) {
                    if (arr2[j]->f228 < 2) break;
                }
                if (j >= c.n2) continue;
            }
            for (i = 0; i < c.n1; i++) {
                arr1[i]->cls->fn7C(arr1[i], 0, g_gameClock[2]);
            }
        }
        ProcessColliderGroup(self, c.n1, arr1, f, flags);
        for (i = 0; i < c.n1; i++) {
            if (!func_00129D70(arr1[i])) {
                ClearRootTries(arr1[i]);
            }
        }
    }
    for (s = (Node_1BDD00*)self->bodies.head; s != 0; s = *(Node_1BDD00**)((u8*)s + 0x2D0)) {
        s->flags538 &= ~(1ULL << 57);
    }
    PopBackMemoryMark();
}

void func_001BE068(u8* base, s32 stride, s32 rowB, s32 rowA)
{
    s32* b = (s32*)(base + rowB * stride);
    s32* a = (s32*)(base + rowA * stride);
    for (s32 n = stride; n > 0; n -= 4) {
        s32 y = *a;
        s32 x = *b;
        *b = y;
        *a = x;
        a++;
        b++;
    }
}

void func_001BE0A8(u8* base, s32 n, s32 size, Cmp_1BE0A8 cmp)
{
    if (n < 2) return;
    s32 end = n - 1;
    s32 start = n / 2;
    for (;;) {
        if (start > 0) {
            start--;
        } else {
            SwapSortRecords(base, size, end, 0);
            s32 t = end;
            end = t - 1;
            if (t < 2) return;
        }
        s32 i = start;
        s32 c = 2 * i + 1;
        if (end < c) continue;
        for (;;) {
            if (c < end) {
                s32 s0 = c + 1;
                if (cmp(base + c * size, base + s0 * size) < 0) c = s0;
            }
            if (cmp(base + i * size, base + c * size) < 0) {
                SwapSortRecords(base, size, i, c);
                i = c;
                c = c + (c + 1);
                if (end < c) break;
                continue;
            }
            break;
        }
    }
}

void func_001BE1E8(void)
{
    if (g_stagedBankHandle != 0) {
        if (g_stagedBankVoice != 0) {
            StopSoundVoice(g_stagedBankVoice);
        }
        UnloadSoundBank(g_stagedBankHandle);
        while (PollIopCommands() != 0) {
        }
        g_stagedBankHandle = 0;
    }
    g_stagedBankState = 0;
    g_stagedBankVoice = 0;
}

s32 func_001BE268(s32 n)
{
    KeyId l;
    s32 h;
    if (n == g_loadedSoundBank) {
        return ((s32*)&g_soundBankHandles)[n];
    }
    if (n == 0) {
        h = ((s32*)&g_soundBankHandles)[0];
        if (h != 0) {
            return h;
        }
    } else {
        UnloadStagedBank();
        if (g_loadedSoundBank >= 0 && (h = ((s32*)&g_soundBankHandles)[g_loadedSoundBank]) != 0) {
            UnloadSoundBank();
            while (PollIopCommands() != 0) {
            }
            ((s32*)&g_soundBankHandles)[g_loadedSoundBank] = 0;
            func_0011D420();
        }
        g_loadedSoundBank = n;
    }
    ClearKeyId(&l);
    const Ent_1BE268* e = &g_soundBankKeys[n];
    s32 ok;
    if (e == 0) {
        ok = 0;
    } else {
        l.second = e->w4 ^ e->w1C;
        l.first = e->w0 ^ e->w14;
        ok = l.second != 0;
    }
    if (ok) {
        while (WaitDiscReady(0) != 2) {
        }
        SyncDiscRead(0);
        s32 r = LoadSoundBankAtLocation(l.first, 0);
        ((s32*)&g_soundBankHandles)[n] = r;
        if (r != 0) {
            func_0011D420();
            if (((s32*)&g_soundBankLoaded)[n] == 0) {
                ((s32*)&g_soundBankLoaded)[n] = 1;
                for (s32 i = 0; i < 0x303; i++) {
                    if (((Pair_1BE268*)&g_soundEntries)[i].id == n) {
                        ((s32*)&g_soundEntryAvailable)[i] = func_0011D760(((s32*)&g_soundBankHandles)[n], ((Pair_1BE268*)&g_soundEntries)[i].arg) != 0 || g_soundEntryForcedAvailable[i] != 0;
                    }
                }
            }
        }
    }
    return ((s32*)&g_soundBankHandles)[n];
}

void func_001BE4A8(s32 idx)
{
    EnsureSoundBankLoaded(*(Ent_1BE4A8**)((u8*)g_soundEntries + idx * 8));
}

void func_001BE4D8(Owner_1BE4D8* self)
{
    self->rec = (Rec_1BE4D8*)AllocateZeroedFrontMemory(0x24);
    self->rec->f00 = -1;
    self->rec->f04 = 3000.0f;
    self->rec->f08 = 300.0f;
    self->rec->f0C = 1.0f;
    self->rec->f10 = 0;
    self->rec->f1C = 0;
    self->rec->f14 = -1.0f;
    self->rec->f20 = 0;
}

s32 func_001BE568(s32 idx)
{
    Pair_1BE568* p = (Pair_1BE568*)g_soundEntries + idx;

    if (((s32*)g_soundBankLoaded)[p->key] == 0) {
        EnsureSoundEntryBankLoaded((Sel_1BE568*)idx);
    }
    return ((s32*)g_soundEntryAvailable)[idx];
}

void func_001BE5D8(void)
{
    g_streamVoicePending = 0;
}

s32 func_001BE5E8(void) { return g_streamVoiceLocked; }

void func_001BE5F8(Obj_1BE5F8* self)
{
    if (g_streamVoiceLocked != 0) {
        return;
    }
    if (self == 0) {
        return;
    }
    Local_1BE5F8 l;
    Local_1BE5F8* p;
    if (HasStreamVoice() != 0) {
        StopStreamVoice();
    }
    p = &l;
    ClearKeyId(p);
    s32 b = self->w4 ^ self->w1C;
    p->b = b;
    p->a = self->w0 ^ self->w14;
    if (b == 0) {
        return;
    }
    s32 h = StartStreamedVoice(p->a, 0, 0, 0, 0x400, 0, 2, 0, 0);
    if (h == 0) {
        return;
    }
    g_streamVoice = h;
    g_streamVoiceLocked = 1;
    g_streamVoicePending = 0;
    SetVolumeChannelFactor(8, 1, 0.5f);
    SetVolumeChannelFactor(8, 0, 0.5f);
    SetVolumeChannelFactor(8, 3, 0.5f);
}

void func_001BE708(void)
{
    g_streamVoiceLocked = 0;
    StopStreamVoice();
}

void func_001BE728(KeyRecord* self)
{
    if (g_streamVoiceLocked != 0) {
        return;
    }
    Local_1BE728 l;
    Local_1BE728* p;
    if (HasStreamVoice() != 0) {
        StopStreamVoice();
    }
    p = &l;
    ClearKeyId(p);
    s32 r = 0;
    if (self != 0) {
        s32 b = self->wordB ^ self->maskB;
        p->b = b;
        l.a = self->wordA ^ self->maskA;
        r = b != 0;
    }
    if (r == 0) {
        return;
    }
    s32 h = StartStreamedVoice(l.a, 0, 0, 0, 0x400, 0, 2, 0, 1);
    if (h == 0) {
        return;
    }
    g_streamVoice = h;
    g_streamVoicePending = 1;
    RequestStreamCallback(h, ClearStreamVoicePending, (u32)h);
}

s32 func_001BE810(void)
{
    if (g_streamVoiceLocked != 0)
        return 0;
    if (g_streamVoice != 0) {
        if (g_streamVoicePending != 0)
            return 1;
        func_0011E0B0(g_streamVoice);
    }
    return 0;
}

void func_001BE860(Obj_1BE860* self)
{
    s32 a1 = (s32)(self->f50 * 1024.0f);
    s32 a2;
    if (0.0f < self->f54) {
        a2 = (s32)((self->f54 + 2.0f) * 179.5f) - 359;
    } else {
        a2 = (s32)((self->f54 + 2.0f) * 179.5f);
    }
    SetVoiceVolumePan(self->f18, a1, a2);
}

void func_001BE8F8(s32 a0, void** a1, f32 f12, f32 f13)
{
    s32 flag = 0;
    void* local;
    void** p = a1;
    if (p == 0) {
        flag = 1;
        p = (void**)&local;
    }
    StartSoundEffect(-2, p, a0, 0, f12, f13, 1.0f, 0.0f, 0.0f, 0, 0);
    if (*p != 0) {
        ApplySoundRecordVolumePan(*p);
        if (flag != 0) {
            ClearSoundRecordHandle(p);
        }
    }
}

s32 func_001BE980(void)
{
    return g_streamVoice != 0;
}

LINKER_REMNANT(func_001BE990);

void func_001BE998(void)
{
    s32 r;
    if (g_streamVoiceLocked != 0) return;
    if (g_streamVoice == 0) return;
    StopSoundVoice(g_streamVoice);
    while ((r = IsVoiceBusy(g_streamVoice)) != 0) {
        r = 0x4E20;
        while (--r >= 0) {
        }
    }
    g_streamVoice = 0;
    g_streamVoicePending = 0;
}

void func_001BEA28(void)
{
    if (g_streamVoice != 0) {
        func_0011D640(g_streamVoice);
    }
}

void func_001BEA50(void)
{
    if (g_streamVoice != 0) {
        func_0011D670(g_streamVoice);
    }
}

void func_001BEA78(void)
{
    if (g_stagedBankState == 3) {
        StopSoundVoice(g_stagedBankVoice);
        g_stagedBankVoice = 0;
        g_stagedBankState = 2;
    }
}

void func_001BEAC8(s32 h)
{
    g_stagedBankHandle = h;
    if (h != 0) {
        func_0011D420();
        g_stagedBankState = 2;
    } else {
        g_stagedBankRecord = 0;
        g_stagedBankState = 0;
    }
}

void func_001BEB10(Rec_1BEB10* self)
{
    s32 local[2];
    s32 same;
    s32 flag;

    if (self == 0) {
        StopStagedBankVoice();
        return;
    }
    Rec_1BEB10* old = (Rec_1BEB10*)g_stagedBankRecord;
    if (self == old) {
        same = 1;
    } else if (self == 0) {
        same = 0;
    } else if (old == 0) {
        same = 0;
    } else {
        same = ((self->f8 ^ self->f18) ^ (old->f8 ^ old->f18)) == 0;
    }
    if (same != 0 && g_stagedBankState != 0) {
        return;
    }
    while (PollIopCommands() != 0 && g_stagedBankState == 1) {
        SyncDataCache(0);
    }
    UnloadStagedBank();
    g_stagedBankRecord = (s32)self;
    ClearKeyId(local);
    if (self == 0) {
        flag = 0;
    } else {
        s32 x = self->f4 ^ self->f1C;
        local[0] = self->f0 ^ self->f14;
        local[1] = x;
        flag = x != 0;
    }
    if (flag != 0) {
        g_stagedBankState = 1;
        SyncDiscRead(0);
        StartSoundBankLoad(local[0], 0, (void*)StoreStagedBankHandle, 0);
    }
}

void func_001BEC58(void* self)
{
    RequestStagedBank(self);
    if (self == 0) return;
    while (PollIopCommands() != 0 && g_stagedBankState == 1) {
        SyncDataCache(0);
    }
    if (g_stagedBankState == 2) {
        s32 h = StartSoundVoice(g_stagedBankHandle, 0, 0x400, -1, 0, 0);
        g_stagedBankVoice = h;
        if (h == 0) return;
        g_stagedBankState = 3;
    }
}

void func_001BECF8(void)
{
    SetVolumeChannelFactor(2, 1, 0.0f);
}

void func_001BED20(void)
{
    SetVolumeChannelFactor(2, 1, 1.0f);
}

void func_001BED48(void)
{
    func_0011D640(g_stagedBankVoice);
}

void func_001BED70(void)
{
    func_0011D670(g_stagedBankVoice);
}

void* func_001BED98(void)
{
    void* p = PopFreeSlot((u8*)g_currentWorld + 0x1BB8);
    if (p != 0) {
        FillMemory((u8*)p, 0, 12);
        AppendToList((u8*)g_currentWorld + 0x1BC4, p);
    }
    return p;
}

void func_001BEDF8(void* self)
{
    RemoveFromList((u8*)g_currentWorld + 0x1BC4, self);
    PushFreeSlot((u8*)g_currentWorld + 0x1BB8, self);
}

void func_001BEE48(void)
{
    Iter_1BEE48 it;
    Begin_1BEE48::Of(&it, &(*(World_1BEE48**)&g_currentWorld)->list);
    Node_1BEE48* node;
    for (node = Next_1BEE48::Of(&it); node != 0; node = Next_1BEE48::Of(&it)) {
        RemoveSoundLevelEntry(node);
    }
    SendIopSoundLevel(0x14);
    D_002748EC = 0;
    g_activeListFrames = (ListFrame*)it.saved;
    g_previousSoundLevel = 0;
    g_currentSoundLevel = 0;

}

void* func_001BEEF8(s32 x)
{
    s32 flag = IsListEmpty((u8*)g_currentWorld + 0x1BC4);
    void* p = AllocateSoundLevelEntry();
    s32 hi = 0x6B;
    s32 v = -20;
    if (x >= -20) {
        if (hi < x) v = hi; else v = x;
    }
    if (p != 0) {
        *(s32*)p = v;
        s32 cur = g_currentSoundLevel;
        if (cur < v || flag != 0) {
            g_currentSoundLevel = v;
            g_previousSoundLevel = cur;
        }
    }
    return p;
}

void func_001BEF88(void)
{
    Frame_1BEF88 f;
    s32 P = (s32)g_currentWorld + 0x1BC4;
    s32 x;
    f.f0 = P;
    f.f4 = P;
    f.f8 = *(s32*)(P + 8);
    f.fC = (s32)g_activeListFrames;
    g_activeListFrames = (ListFrame*)&f;
    if (IsListEmpty((Frame_1BEF88*)P) != 0) {
        g_currentSoundLevel = 0;
    } else {
        g_currentSoundLevel = -20;
        s32 x0 = *(s32*)f.f4;
        f.f4 = x0 + f.f8;
        x = x0;
        if (x != 0) {
            do {
                s32 v = *(s32*)x;
                if (g_currentSoundLevel < v) {
                    g_currentSoundLevel = v;
                }
                s32 y = *(s32*)f.f4;
                f.f4 = y + f.f8;
                x = y;
            } while (x != 0);
        }
    }
    g_activeListFrames = (ListFrame*)f.fC;
}

void func_001BF048(Entry_1BF048* self)
{
    if (self != 0) {
        s32 key = self->key;
        RemoveSoundLevelEntry(self);
        if (key == g_currentSoundLevel) {
            RecomputeSoundLevel(self);
            s32 cur = g_currentSoundLevel;
            if (cur >= 0) {
                D_002748EC = 0;
            }
            g_previousSoundLevel = cur;
            SendIopSoundLevel(cur + 0x14);
            SetVolumeChannelFactor(7, 1, 1.0f);
            g_previousSoundLevel = -0x64;
        }
    }
}

void func_001BF0D8(Obj_1BF0D8* self)
{
    if (self == 0) {
        return;
    }
    s32 k = self->kind;
    RemoveSoundLevelEntry(self);
    if (k == g_currentSoundLevel) {
        g_previousSoundLevel = k;
        RecomputeSoundLevel(self);
    }
}

void func_001BF130(void)
{
    FillMemory(g_soundBankHandles, 0, 0x1C);
    InitIopCommandChannels();
    EnsureSoundBankLoaded(0);
    EnableIopDiscAccess(1, 0x2000, 1, 1);
    SendIopSoundLevel(0x14);
    ResetVolumeChannelFactors();
    func_0011D520(0, 1);
    func_0011D558(0, 0, 0x2F);
    func_0011D558(1, 0x18, 0x2F);
    func_0011D558(3, 0x18, 0x2F);
    func_0011D558(2, 0x18, 0x2F);
    func_0011E3A0(2, 4);
}

LINKER_REMNANT(func_001BF1E8);

s32 func_001BF1F0(void) { return D_00274748; }

ASM_FUNC(func_001BF200);

ASM_FUNC(func_001BF2E0);

ASM_FUNC(func_001BF398);

void* func_001BF3D0(void)
{
    Obj_001BF3D0* p = (Obj_001BF3D0*)GetActiveSwitchedCollider();
    u8* r;
    if (p != 0 && p->vtbl[78](p) != 0) {
        r = (u8*)p + 0x140;
    } else {
        r = (u8*)g_camera + 0x40;
    }
    return r;
}

ASM_FUNC(func_001BF428);

Fn_001BF578 func_001BF578(void)
{
    s32 n;
    if (IsTopCameraController((u8*)g_camera + 0x460) == 0) return MeasureListenerDistance;
    n = PeekStackValue((u8*)g_camera + 0x460);
    if (n >= 3) return MeasureListenerDistance;
    if (n <= 0) return MeasureListenerDistance;
    return MeasureCameraWeightedDistance;
}

f32 func_001BF5E0(Arg_1BF5E0* arg)
{
    Obj_1BF5E0* obj = (Obj_1BF5E0*)GetSoundListenerPosition();
    return ((Fn_1BF5E0)ChooseSoundListenerFunction())(obj, arg);
}

void func_001BF620(void* self, f32* out, s32* flag, f32 a, f32 b, f32 c)
{
    if (self != 0) {
        f32 r = ComputeSoundListenerFactor(self);
        ComputeSoundVolumeAndPan(r, self, out, flag, a, b, c);
    } else {
        *out = a;
        *flag = 0;
    }
}

void* func_001BF6B8(void)
{
    void* s = PopFreeSlot((u8*)g_currentWorld + 0x1BA0);
    if (s) {
        FillMemory(s, 0, 0x90);
        AppendToList((u8*)g_currentWorld + 0x1BAC, s);
    }
    return s;
}

void func_001BF718(Slot_1BF718* slot)
{
    Entry_1BF718* e = slot->entry;
    e->f0C = 0;
    slot->entry = 0;
}

void func_001BF728(Obj_1BF728* self)
{
    if (self->f0C != 0) {
        *(s32*)self->f0C = 0;
    }
    self->f04 = -1;
    RemoveFromList((u8*)g_currentWorld + 0x1BAC, self);
    PushFreeSlot((u8*)g_currentWorld + 0x1BA0, self);
}

void func_001BF788(Obj_1BF788* self, s32 n)
{
    if (self != 0) {
        if (n == 0) {
            StopSoundVoice(self->f18);
        } else {
            f32 t = (f32)n * 0.24000001f;
            s32 q = (s32)t;
            func_0011D860(self->f18, -4, q, 2);
        }
        FreeSoundRecord(self);
    }
}

void func_001BF7F8(Ent_1BF7F8* p, f32 a)
{
    if (p == 0) {
        return;
    }
    if (a == p->f58) {
        if (p->f30 == 0) {
            return;
        }
        if (!(0.0001f < p->f5C)) {
            return;
        }
    }
    s32 v0 = p->flag6C;
    p->f58 = a;
    if (v0 == 0) {
        p->f70 = GetSoundPitchBase(p->f8, g_soundEntries[p->idx].b);
        p->flag6C = 1;
    }
    s32 v = p->f70 + (s32)(p->f58 * 1524.0f) + p->f60;
    SetVoicePitch(p->f18, p->clampv(v, -0x8000, 0x7FFF));
}

void func_001BF8E8(Obj_1BF8E8* self, f32 a)
{
    if (self != 0) {
        f32 scale = a / self->f14;
        f32 base = self->f50;
        self->f14 = a;
        self->f50 = base * scale;
        ApplySoundRecordVolumePan(self);
    }
}

void func_001BF920(Obj_1BF920* self, Obj_1BF920* parent, s32 a2, u8* a3, Q16_1BF920* q, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, B8_1BF920* p78, B8_1BF920* p80)
{
    B8_1BF920 keep = self->f64;
    FillMemory(self, 0, 0x90);
    self->f64 = keep;
    if (a3) q = (Q16_1BF920*)(a3 + 0x140);
    self->f0C = parent;
    if (parent) *(Obj_1BF920**)parent = self;
    self->f58 = f15;
    self->f5C = f16;
    s32 id = g_nextSoundRecordId;
    self->f04 = id++;
    self->f3C = a2;
    self->f30 = a3;
    self->f34 = f12;
    self->f38 = f13;
    self->f14 = f14;
    self->f48 = 0;
    g_nextSoundRecordId = id;
    self->f4C = RandomIntInRange(0, 3);
    if (p78) self->f78.v = *p78; else self->f78.f = -1.0f;
    if (p80) self->f80.v = *p80; else self->f80.f = -1.0f;
    if (q) self->f20 = *q;
    s32 fl = 0;
    if (q || self->f78.f >= 0.0f) fl = 1;
    self->f44 = fl;
    ComputeSoundAttenuation(q, &self->f50, &self->f54, f14, f12, f13);
    ComputeSoundRecordDoppler(self);
}

void func_001BFAF8(Node_1BFAF8* self, s32 idx)
{
    s32 link;
    s32 v3;
    if (idx != -2) {
        link = EnsureSoundEntryBankLoaded((Idx_1BFAF8*)idx);
        v3 = g_soundEntries[idx].b;
        self->link = link;
    }
    self->idx = idx;
    self->f10 = g_gameTime[0];
    if (idx == -2) {
        v3 = g_streamVoice;
        self->f40 = 0;
        self->f18 = v3;
        return;
    }
    if (self->f50 != 0.0f && self->f78 < 0.0f) {
        s32 r = StartSoundVoice((Link_1BFAF8*)link, v3, 0, 0, 0, 0);
        self->f40 = 0;
        self->f18 = r;
        ComputeSoundRecordDoppler(self);
        SetSoundRecordPitch(self, self->f58);
        ApplySoundRecordVolumePan(self);
    } else {
        self->f18 = 0;
        self->f40 = 1;
    }
}

ASM_FUNC(func_001BFBF8);

void func_001BFCD8(s32 id, Buf_1BFCD8** out, s32 p2, s32 p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, s32 p5) {
    Buf_1BFCD8* s1;
    s32 s0;
    if (id == -1) return;
    if (id != -2) {
        s32 a1 = g_soundEntries[id].a;
        if (a1 > 0 && a1 != (*(Glob_1BFCD8**)&g_currentWorld)->f1D70) return;
        s0 = IsSoundEntryAvailable((Id_1BFCD8)id);
    } else {
        s0 = 0;
    }
    s1 = 0;
    if (p3 || p2 || out) {
        if (s0 == 0 && (p4 == 0 || *p4 < 0.0f)) {
            Buf_1BFCD8 tmp;
            InitSoundRecord(&tmp, out, 0, p2, p3, fa, fb, fc, fd, fe, 0, 0);
            if (tmp.f50 != 0.0f) {
                s1 = (Buf_1BFCD8*)AllocateSoundRecord();
                if (s1) {
                    tmp.f64 = s1->f64;
                    *s1 = tmp;
                }
            } else if (id == -2) {
                SetVoiceVolumePan((Id_1BFCD8)g_streamVoice, 0, 0);
            }
            if (out) *out = s1;
        } else {
            s1 = (Buf_1BFCD8*)AllocateSoundRecord();
            if (!s1) return;
            InitSoundRecord(s1, out, s0, p2, p3, fa, fb, fc, fd, fe, p4, p5);
        }
        if (s1) {
            if (0.0f <= s1->f78) {
                ScheduleAmbientSoundRecord(s1);
                s1->f74 = (*(f32*)&g_gameTime) + RandomFloatInRange(0.0f, s1->f78);
            }
            StartSoundRecordVoice(s1, id);
        }
    } else {
        s32 v = EnsureSoundEntryBankLoaded((Id_1BFCD8)id);
        StartSoundVoice((Id_1BFCD8)v, g_soundEntries[id].b, (s32)(fc * 1024.0f), 0, (s32)(fd * 1524.0f), 0);
    }
}

void func_001BFFC8(void* guard, s64 key)
{
    if (guard == 0) {
        s32 tag = (s32)(key >> 32);
        Rec_1BFFC8* r = (Rec_1BFFC8*)(s32)(key & 0xFFFFFFFFu);
        if (r->f04 == tag) {
            r->f48 = 1;
        }
    }
}

void func_001C0000(s32 flag, f32 x)
{
    SetVolumeChannelFactor(6, 0, x);
    SetVolumeChannelFactor(6, 2, x);
    SetVolumeChannelFactor(6, 3, x);
    if (flag) {
        SetVolumeChannelFactor(6, 1, x);
    }
}

void func_001C0070(void)
{
    Frame_1C0070 f;
    if (func_001BF1F0() != 0) return;
    void* v4 = GetSoundListenerPosition();
    Fn_1C0070 v5 = (Fn_1C0070)ChooseSoundListenerFunction();
    u8* P = (u8*)g_currentWorld + 0x1BAC;
    ListFrame* saved = g_activeListFrames;
    f.list = P;
    f.link = P;
    f.offset = *(s32*)(P + 8);
    f.prev = saved;
    g_activeListFrames = &f;
    if (g_streamVoice != 0 && IsVoiceBusy(g_streamVoice) == 0) {
        if (g_streamVoiceLocked != 0) {
            SetVolumeChannelFactor(8, 1, 1.0f);
            SetVolumeChannelFactor(8, 0, 1.0f);
            SetVolumeChannelFactor(8, 3, 1.0f);
        }
        g_streamVoice = 0;
        g_streamVoiceLocked = 0;
        g_streamVoicePending = 0;
    }
    if (g_previousSoundLevel != -100) {
        s32 up = g_previousSoundLevel < g_currentSoundLevel;
        if (g_currentSoundLevel > 0 && up) {
            SendIopSoundLevel(g_currentSoundLevel + 0x14);
            g_previousSoundLevel = g_currentSoundLevel;
            SetVolumeChannelFactor(7, 1, 1.0f);
            D_002748EC = 0;
        } else {
            D_00274754 = D_00274754 - 1;
            if (D_00274754 < 0) {
                s32 a = g_previousSoundLevel;
                s32 v = (g_currentSoundLevel < a) ? a - 1 : a + 1;
                D_002748EC = (u32)v >> 31;
                g_previousSoundLevel = v;
                SendIopSoundLevel(v + 0x14);
                if (g_previousSoundLevel < 0) {
                    f32 cnv = (f32)g_previousSoundLevel;
                    f32 k = -0.05f;
                    f32 zero = 0.0f;
                    f32 one = 1.0f;
                    f32 x = cnv * k;
                    f32 y;
                    if (x < zero) y = zero;
                    else if (one < x) y = one;
                    else y = x;
                    f32 m = y * 0.6666667f;
                    SetVolumeChannelFactor(7, 1, (1.0f - y) + m);
                }
                D_00274754 = D_00274754 + 3;
            }
        }
        if (up ? !(g_previousSoundLevel < g_currentSoundLevel) : !(g_previousSoundLevel > g_currentSoundLevel)) {
            D_002748EC = (u32)g_previousSoundLevel >> 31;
            SendIopSoundLevel(g_currentSoundLevel + 0x14);
            g_previousSoundLevel = -100;
        }
    }
    Ent_1C0070* e;
    {
        while ((e = f.Next()) != 0) {
            u8* s1;
            f32 r;
            if (e->f30 != 0 && IsObjectAttached(e->f30) == 0) {
                StopSoundRecord(e, 0);
                goto next;
            }
            if (e->f40 == 0) {
                if (e->f48 != 0) {
                    if (0.0f <= e->f78) {
                        e->f18 = 0;
                    } else {
                        if (e->f30 != 0) e->f30->desc->m0E(e->f30, 9, e);
                        if (e->f3C == 0) goto kill;
                        StopSoundVoice(e->f18);
                        e->f18 = 0;
                    }
                    e->f48 = 0;
                    e->f40 = 1;
                    goto next;
                }
                e->f4C = (e->f4C + 1) % 4;
                if (e->f4C == 0) {
                    RequestVoiceCallback(e->f18, MarkSoundRecordIfIdMatches, ((s64)e->f4 << 32) | (s64)(s32)e);
                }
            }
            if (0.0f <= e->f78) {
                f32* s1 = g_gameClock;
                if (s1[1] < e->f74) {
                    if (e->f40 != 0) goto next;
                } else {
                    ScheduleAmbientSoundRecord(e);
                    if (e->f40 != 0) {
                        if (s1[1] - D_00274750 < 1.0f) goto next;
                        D_00274750 = s1[1];
                    }
                }
            }
            if (e->f44 == 0) goto next;
            {
                s1 = (u8*)e + 0x20;
                if (e->f30 != 0) s1 = (u8*)e->f30 + 0x140;
                r = v5(v4, s1);
                if (e->f34 < r) {
                    if (0.0f <= e->f78) goto next;
                    if (e->f40 != 0) goto next;
                    if (e->f3C != 0 || 0.0f < e->f74) {
                        StopSoundVoice(e->f18);
                        e->f18 = 0;
                        e->f40 = 1;
                        goto next;
                    }
                kill:
                    StopSoundRecord(e, 0);
                    goto next;
                }
                ComputeSoundVolumeAndPan(r, s1, &e->f50, &e->f54, e->f14, e->f34, e->f38);
            }
            if (e->f40 != 0 && e->f0 != -2) {
                e->f18 = StartSoundVoice(e->f8, D_00245024[e->f0].a, 0, 0, 0, 0);
                e->f40 = 0;
            }
            ComputeSoundRecordDoppler(e);
            SetSoundRecordPitch(e, e->f58);
            ApplySoundRecordVolumePan(e);
        next:;
        }
    }
    PollIopCommands();
    g_activeListFrames = f.prev;
}

void func_001C05D0(f32 x)
{
    SetIopVolumeChannel(8, (s32)(x * 1024.0f));
}

void func_001C0600(s32 column)
{
    f32* p = &g_volumeChannelFactors[0][column];
    f32 prod = 1.0f;
    s32 n = 10;

    do {
        prod = prod * *p;
        p += 4;
        n--;
    } while (n >= 0);

    f32 one = 1.0f;

    if (prod < 0.0f) {
        prod = 0.0f;
    } else if (one < prod) {
        prod = one;
    }

    SetIopVolumeChannel(column, (s32)(prod * 1024.0f));
}

void func_001C06A0(s32 row, s32 column, f32 value)
{
    g_volumeChannelFactors[row][column] = value;
    ApplyVolumeChannelFactors(column);
}

void func_001C06D8(void)
{
    CopyMemory(g_volumeChannelFactors, g_defaultVolumeChannelFactors, 0xB0);
    SetIopVolumeChannel8(1.0f);
    for (s32 i = 0; i < 4; i++) {
        ApplyVolumeChannelFactors(i);
    }
    SilenceVolumeChannel3(g_saveData->f19EC & 0x80);
    func_001C0790(g_saveData->f19EC & 0x40);
}

void func_001C0760(s32 flag)
{
    SetVolumeChannelFactor(3, 1, flag ? 0.0f : 1.0f);
}

s32 func_001C0790(s32 value)
{
    return func_0011D4E0(value != 0);
}

void func_001C07B0(void)
{
    StopAllIopSounds();
    StopWorldSoundRecords(0);
    ClearSoundLevels();
    ClearCachedVoiceParams();
    while (PollIopCommands() != 0) {
    }
    func_0011E110(1);
    SyncDiscRead(0);
}

void func_001C0808(void* item)
{
    if (g_currentWorld) {
        Iter_1C0808 it;
        u8* obj;
        Begin_1C0808::Of(&it, (List_1C0808*)&g_currentWorld->f1BAC);
        for (obj = Next_1C0808::Of(&it); obj; obj = Next_1C0808::Of(&it)) {
            StopSoundRecord(obj, item);
        }
        End_1C0808::Of(&it);
    }
    PollIopCommands();
}

void func_001C08B0(Stack_1C08B0* self, s32 a, s32 b)
{
    if ((u32)self->count < 4) {
        SetIopChannelValue(2, D_00274808[a]);
        SetIopChannelValuePair(2, b, b);
        self->pairs[self->count].a = a;
        self->pairs[self->count].b = b;
        self->count++;
    }
}

void func_001C0950(Stack_1C0950* self)
{
    s32 n = self->count;
    if (n >= 2) {
        self->count = n - 1;
        SetIopChannelValue(2, D_00274808[self->pairs[n - 2].a]);
        SetIopChannelValuePair(2, self->pairs[self->count - 1].b, self->pairs[self->count - 1].b);
    }
}

void func_001C09D8(World* self, s32 index, s32 value)
{
    SetIopChannelValue(2, D_00274808[index]);
    SetIopChannelValuePair(2, value, value);
    *(s32*)self->f2328 = index;
    *(s32*)(self->f2328 + 4) = value;
    self->f2348 = 1;
}

void func_001C0A50(World* self, s32 key)
{
    if (self->f1D80 < 16) {
        Ent_1C0A50* e = &((Ent_1C0A50*)self->f1D84)[self->f1D80];
        e->key = key;
        e->a = D_00274820;
        e->b = D_00274828;
        self->f1D80++;
    }
}

void func_001C0AB8(World* self, Pt_1C0AB8* p)
{
    s32 n = self->f1D80;
    if (n != 0) {
        Ent_1C0AB8* e = (Ent_1C0AB8*)((u8*)self + 0x1D70 + n * 20);
        e->b0 = 8000.0f - p->y * 50.0f;
        e->b1 = 8000.0f - p->x * 50.0f;
    }
}

void func_001C0B08(World* self, Packed_001C0B08* item) { if (!self->f1D80) return; u8* dst = (u8*)self + 0x1D70 + self->f1D80 * 20; *(Packed_001C0B08*)(dst + 4) = *item; }

void func_001C0B38(World* self)
{
    for (s32 i = 0; i < self->f1D80; i++) {
        Ent_1C0B38* e = &((Ent_1C0B38*)self->f1D84)[i];
        StartSoundEffect(e->key, D_002748E8, 0, 0, &e->a, &e->b, 8000.0f, 3000.0f, 1.0f, 0.0f, 0.0f);
    }
}

void func_001C0C08(s32 idx, s32 val)
{
    if (val != D_006053E0[idx]) {
        D_006053E0[idx] = val;
        SetVoiceParam((Owner_1C0C08*)g_stagedBankVoice, idx, val);
    }
}

s32 func_001C0C50(s32 index)
{
    return D_006053E0[index];
}

void func_001C0C68(s32 i)
{
    D_006053E0[i] = GetVoiceParam(g_stagedBankVoice, i);
}

void func_001C0CB0(void)
{
    for (s32 i = 0; i < 8; i++) {
        SetCachedVoiceParam(i, 0);
    }
}

extern const TabA_24D2A8 D_0024D2A8 = { { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 1, -5, -5, -5, -5, 1, 1, -5, -5, -5, 1, 1, 1, -5, -5, 1, 1, 1, 1, -5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
extern const TabB_24D350 D_0024D350 = { { 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 } };

s32 func_001C0CF0() {
    TabA_24D2A8 a = D_0024D2A8;
    TabB_24D350 b = D_0024D350;
    s32 r = RandomIntInRange(0, 5);
    D_00274830 += *(s32*)((u8*)&a + (b.v[D_00274830 + 12] * 24 + r * 4));
    return D_00274830;
}

void func_001C0EC0(void)
{
    if (D_002748EC != 0) {
        f32 scale = (f32)StepBiasedRandomWalk();
        StartSoundEffect(0x77, 0, 0, 0, 0.0f, 0.0f, 0.5f, scale * 0.083333336f, 0.0f, 0, 0);
    }
}

ASM_FUNC(func_001C0F30);

void func_001C0FF0(IdLinkedObject* self)
{
    StartPlacedObject(self);
    SetObjectLinkId(self, self->linkId);
    self->desc->m03(self);
}

void func_001C1030(IdLinkedObject* self, s32 v)
{
    if (self->link != 0) {
        DestroyStateWalker(self->link);
        self->link = 0;
    }
    s32 r = FindFirstObjectById(self->world, 0x101, v, self);
    self->linkTarget = r;
    if (r != 0) {
        self->link = CreateStateWalker(r, self, -1, 1);
    }
    self->linkId = v;
}

void func_001C10A8(ListedPointObject* self)
{
    InitObject(self);
    self->f58 = 3.4028235e38f;
}

void func_001C10D8(ListedPointObject* self)
{
    RegisterObject(self);
    AppendToList(&self->world->list1C84, self);
}

void func_001C1110(ListedPointObject* self)
{
    UnregisterObject(self);
    RemoveFromList(&self->world->list1C84, self);
}

void func_001C1148(ListedPointObject* self)
{
    KeptBits saved;
    saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

void func_001C1190(World* self, BufferedStream* arg) {
    ScriptValue q0;
    ScriptValue q1;
    ScriptValue q2;
    s32 i = 0;
    InitScriptValue(&q0);
    self->f1EF0 = ReadBufferedU32(arg);
    self->f1EF4 = AllocateFrontMemory(self->f1EF0 << 3);
    s32 n1 = ReadBufferedU32(arg);
    s32 n2 = ReadBufferedU32(arg);
    for (i = 0; i < self->f1EF0; i++) {
        {
            E_1C1190* e = (E_1C1190*)self->f1EF4 + i;
            e->a = ReadScriptValueChain(arg);
            e->b = 0;
            if (D_00275714) {
                SkipBufferedBlock(arg);
                SkipBufferedBlock(arg);
                SkipBufferedBlock(arg);
            }
        }
    }
    if (D_00275714) {
        if (n1 > 0) { s32 k = n1; do SkipBufferedBlock(arg); while (--k); }
        if (n2 > 0) { s32 k = n2; do SkipBufferedBlock(arg); while (--k); }
    }
    s32 r = NewScriptScope();
    i = 0;
    self->f2C = (void*)r;
    AddUniqueMarkRoot(g_markStacks, r);
    self->f1EF8 = n1;
    SetScriptValueTag(&q0, 0);
    DefineScriptVariable(&q1, (s32)self->f2C, self->f1EF8, &q0);
    DestroyScriptValue(&q1, 2);
    if (self->f1EF0 > 0) {
        do {
            InitScriptValue(&q1);
            EvalScriptEntry(&q2, i, self);
            i++;
            AssignScriptValue(&q1, &q2);
            DestroyScriptValue(&q2, 2);
            DestroyScriptValue(&q1, 2);
        } while (i < self->f1EF0);
    }
    DestroyScriptValue(&q0, 2);
}

void* func_001C1390(s32 index, World* self)
{
    if (index == -1) {
        return 0;
    } else {
        Entry_1C1390* e = (Entry_1C1390*)((index << 3) + (u32)self->f1EF4);
        void* p = e->value;
        if (p != 0) AddUniqueMarkRoot(g_markStacks, p);
        return p;
    }
}

ScriptValue* func_001C13E8(ScriptValue* self, s32 index, World* ctx)
{
    s32 off = index << 3;
    ScriptValue q;
    Ent_1C13E8* e;
    InitScriptValue(&q);
    e = (Ent_1C13E8*)(off + (s32)ctx->f1EF4);
    if (e->a != 0 && e->b == 0) {
        ScriptValue t;
        ((Ent_1C13E8*)(off + (s32)ctx->f1EF4))->b = NewScriptScope();
        EvalScriptExpression(&t, ((Ent_1C13E8*)(off + (s32)ctx->f1EF4))->a, ((Ent_1C13E8*)(off + (s32)ctx->f1EF4))->b);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

s32 func_001C14C0(KeyHolder_1C14C0* self, s32 key)
{
    KeyTable_1C14C0* entry = &g_classPropertyLists[self->ref->index];
    s32 lo = 0;
    s32 hi = entry->count - 1;
    KeyPair_1C14C0* items = entry->items;

    while (lo <= hi) {
        s32 mid = (lo + hi) >> 1;
        s32 k = items[mid].key;
        if (k == key) {
            return items[mid].value;
        }
        if (key < k) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

ScriptValue* func_001C1530(ScriptValue* self, void* ctx, s32 v, Cb_1C1530 cb)
{
    ScriptValue q;
    Rec_1C1530 r;
    InitScriptValue(&q);
    r.a = v;
    r.head = 0;
    r.cnt = 0;
    cb(ctx, &r);
    if (r.head != 0) {
        SetScriptValueChain(&q, r.head);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

ScriptValue* func_001C15D8(ScriptValue* out, void* base, Desc_1C15D8* d)
{
    ScriptValue q;
    ScriptValue q2;
    s32 t20, t28, t2c, t30;
    f32 t24;
    char* p;
    Get_1C15D8 fn;
    InitScriptValue(&q);
    if (d->flags & 1) {
        s32* r = (s32*)TakeZeroedPoolEntry();
        r[0] = (s32)base;
        r[1] = d->imm;
        r[2] = d->imm2;
        SetScriptValueIntC(&q, (s32)r);
    } else if (d->flags & 2) {
        if (d->flags & 0x1000) {
            p = (char*)d->base(base, 0) + d->off;
        } else {
            p = (char*)base + d->off;
        }
        switch (d->kind) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            SetScriptValueInt(&q, *(s32*)p);
            break;
        case 1:
            SetScriptValueFloat(&q, *(f32*)p);
            break;
        case 0:
            SetScriptValueBool(&q, *(s32*)p);
            break;
        case 2: {
            Quad16* r = (Quad16*)AcquireVectorAPayload();
            *r = *(Quad16*)p;
            SetScriptValueVectorA(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = AcquireMatrixPayload();
            CopyRotationMatrix(r, p);
            SetScriptValueMatrix(&q, (f32*)r);
            break;
        }
        case 9: {
            Quad16* r = (Quad16*)AcquireVectorBPayload();
            *r = *(Quad16*)p;
            SetScriptValueVectorB(&q, (f32*)r);
            break;
        }
        case 10: {
            D8_1C15D8* r = (D8_1C15D8*)AcquirePairPayload();
            *r = *(D8_1C15D8*)p;
            SetScriptValuePair(&q, (f32*)r);
            break;
        }
        case 11: {
            Rec3_1C15D8* r = (Rec3_1C15D8*)AcquireTriplePayload();
            *r = *(Rec3_1C15D8*)p;
            SetScriptValueTriple(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->kind & 0x1000) {
                SetScriptValueInt(&q, *(s32*)p);
            } else if (d->kind & 0x2000) {
                SetScriptValuePointerB(&q, (void*)*(s32*)p);
            }
            break;
        }
    } else {
        if (d->flags & 0x1000) {
            p = (char*)d->base(base, 0);
        } else {
            p = (char*)base;
        }
        if (d->flags & 4) {
            fn = (Get_1C15D8)d->off;
        } else {
            fn = *(Get_1C15D8*)(*(char**)base + d->off);
        }
        switch (d->kind) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            fn(p, &t20);
            SetScriptValueInt(&q, t20);
            break;
        case 1:
            fn(p, &t24);
            SetScriptValueFloat(&q, t24);
            break;
        case 0:
            fn(p, &t28);
            SetScriptValueBool(&q, t28);
            break;
        case 2: {
            void* r = AcquireVectorAPayload();
            fn(p, r);
            SetScriptValueVectorA(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = AcquireMatrixPayload();
            fn(p, r);
            ResetMatrixHomogeneous(r);
            SetScriptValueMatrix(&q, (f32*)r);
            break;
        }
        case 9: {
            void* r = AcquireVectorBPayload();
            fn(p, r);
            SetScriptValueVectorB(&q, (f32*)r);
            break;
        }
        case 10: {
            void* r = AcquirePairPayload();
            fn(p, r);
            SetScriptValuePair(&q, (f32*)r);
            break;
        }
        case 11: {
            void* r = AcquireTriplePayload();
            fn(p, r);
            SetScriptValueTriple(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->kind < 0) {
                BuildScriptListFromCallback(&q2, base, d->kind & 0x7fffffff, fn);
                AssignScriptValue(&q, &q2);
                DestroyScriptValue(&q2, 2);
            } else if (d->kind & 0x1000) {
                fn(p, &t2c);
                SetScriptValueInt(&q, t2c);
            } else if (d->kind & 0x2000) {
                fn(p, &t30);
                SetScriptValuePointerB(&q, (void*)t30);
            }
            break;
        }
    }
    CopyConstructScriptValue(out, &q);
    DestroyScriptValue(&q, 2);
    return out;
}

s32 func_001C1A28(List_1C1A28* self, s32 value)
{
    Desc_1C15D8 d;
    ScriptValue t;
    FillMemory(&d, 0, 0x20);
    d.flags = 2;
    d.kind = self->type;
    d.off = 0;
    R11B008Node* n = NewScriptValueNode();
    ReadPropertyValue(&t, value, &d);
    AssignScriptValue(n, &t);
    DestroyScriptValue(&t, 2);
    if (self->head != 0) {
        self->tail->next = n;
    } else {
        self->head = n;
    }
    self->tail = n;
    return 1;
}

s32 func_001C1AD8(Cmd_1C1AD8* cmd, s32* val) {
    ScriptValue q;
    R11B008Node* l;
    InitScriptValue(&q);
    l = cmd->list;
    if (l) {
        switch (cmd->kind) {
        case 1:
            SetScriptValueFloat(&q, *(f32*)val);
            break;
        case 0:
            SetScriptValueBool(&q, *val);
            break;
        case 2: case 4: case 9: case 10: case 11: case 13:
            break;
        default:
            if (cmd->kind & 0x1000) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
                SetScriptValueInt(&q, *val);
            } else if (cmd->kind & 0x2000) {
                SetScriptValuePointerB(&q, (void*)*val);
            }
            break;
        }
        while (l) {
            if (AreScriptValuesEqual(l, &q)) {
                DestroyScriptValue(&q, 2);
                return 1;
            }
            l = l->next;
        }
    }
    DestroyScriptValue(&q, 2);
    return 0;
}

ScriptValue* func_001C1BF8(ScriptValue* out, s32 n, ScriptValue* args, const u32* kinds, void** dsts)
{
    ScriptValue q;
    ScriptValue a;
    ScriptValue b;
    ScriptValue c;
    s32 i;
    InitScriptValue(&q);
    for (i = 0; i < n; i++) {
        AssignScriptValue(&q, args + i);
        u32 t = kinds[i];
        void* d = dsts[i];
        switch (t) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
        case 20:
            if (q.tag == 0x14) {
                goto store;
            }
            InitScriptValue(&a);
            ConvertScriptValueToInt(&b, &q);
            AssignScriptValue(&a, &b);
            DestroyScriptValue(&b, 2);
            *(s32*)d = a.i;
            DestroyScriptValue(&a, 2);
            break;
        case 1:
            if (q.tag == 0x15) {
                *(f32*)d = q.f;
            } else {
                InitScriptValue(&a);
                ConvertScriptValueToFloat(&c, &q);
                AssignScriptValue(&a, &c);
                DestroyScriptValue(&c, 2);
                *(f32*)d = a.f;
                DestroyScriptValue(&a, 2);
            }
            break;
        case 4:
            *(Blob_1C1BF8*)d = *(Blob_1C1BF8*)q.p;
            break;
        case 2:
        case 9:
            *(Quad16*)d = *(Quad16*)q.p;
            break;
        case 10:
            *(W8_1C1BF8*)d = *(W8_1C1BF8*)q.p;
            break;
        case 11:
            *(W12_1C1BF8*)d = *(W12_1C1BF8*)q.p;
            break;
        default:
            if (t & 0x1000) {
                goto store;
            }
            if (t & 0x2000) {
                goto store;
            }
            break;
        case 0:
        store:
            *(s32*)d = q.i;
            break;
        case 13:
            break;
        }
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(out, &q);
    DestroyScriptValue(&q, 2);
    return out;
}

ScriptValue* func_001C1E48(ScriptValue* self, s32 n, s32* keys, s32* vals)
{
    ScriptValue q;
    List_1C1A28 list;
    InitScriptValue(&q);
    list.head = 0;
    list.tail = 0;
    for (s32 i = 0; i < n; i++) {
        list.type = keys[i];
        AppendPropertyToScriptList(&list, vals[i]);
    }
    if (list.head) {
        SetScriptValueChain(&q, list.head);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

INCLUDE_RODATA(jtbl_0024D510);
INCLUDE_ASM(func_001C1F20);

ScriptValue* func_001C21A0(ScriptValue* self, Obj_1C21A0* p, s32 n)
{
    if (n < 0x495) {
        s32 r = (s32)FindPropertyDescriptor(p, n);
        ReadPropertyValue(self, p, r);
    } else {
        ScriptValue q;
        InitScriptValue(&q);
        FindKeyedValue(p->f4, n, &q);
        CopyConstructScriptValue(self, &q);
        DestroyScriptValue(&q, 2);
    }
    return self;
}

ScriptValue* func_001C2238(ScriptValue* self, Obj_1C2238* p, s32 key, ScriptValue* value)
{
    if (key < 0x495) {
        void* v = FindPropertyDescriptor(p, key);
        WritePropertyValue(self, p, v, value);
    } else {
        UpdateKeyedValue(self, p->f4, key, value);
    }
    return self;
}

ScriptValue* func_001C22B8(ScriptValue* self, Obj_1C22B8* p, s32 key, ScriptValue* value)
{
    EnsureKeyedList(p);
    AddKeyedValue(self, p->f4, key, value);
    return self;
}

ScriptValue* func_001C2320(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value)
{
    EnsureKeyedList(p);
    if (FindKeyedValue((R11B008List*)p->f04, key, 0)) UpdateKeyedValue(self, (R11B008List*)p->f04, key, value);
    else AddKeyedValue(self, (R11B008List*)p->f04, key, value);
    return self;
}

ScriptValue* func_001C23B0(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...)
{
    void* arr[32];
    void* ap = (char*)__builtin_next_arg(kinds) - 32;
    if (count > 0) {
        void** d = arr;
        s32 i = count;
        do {
            ap = (char*)ap + 8;
            *d = *(void**)((char*)ap - 8);
            d++;
            i--;
        } while (i != 0);
    }
    StoreScriptArguments(ret, count, args, (const u32*)kinds, arr);
    return ret;
}

void func_001C2430(s32 size, ...)
{
    VaList_1C2430 ap;
    Slot_1C2430* e = &((Slot_1C2430*)D_002748F0)[1 - D_00274990];
    s32 n = 0;
    ap = (VaList_1C2430)__builtin_next_arg(size) - (8 - __builtin_args_info(0)) * 8;
    u32 addr = e->base;
    if (e->state == 3) {
        WaitDmaChannel((*(void**)&g_fromSprChannel), 0, 0);
    }
    e->state = 1;
    s32 data = VA_ARG_1C2430(ap, s32);
    if (size != 0) {
        do {
            s32 nsize = VA_ARG_1C2430(ap, s32);
            size = (size + 15) & ~15;
            addr += 16;
            e->sizes[n] = size;
            e->addrs[n] = addr;
            addr += size;
            s32 ndata = VA_ARG_1C2430(ap, s32);
            if (data != 0) {
                e->tags[n].lo = (u64)(size >> 4) | ((u64)(ndata != 0 ? 3 : 0) << 28) | ((u64)data << 32);
            }
            data = ndata;
            size = nsize;
            n++;
        } while (size != 0);
    }
    e->count = n;
    Chan_1C2430* c = g_toSprChannel;
    c->f0 |= 0x40;
    c->f80 = (e->base & 0x0FFFFFFF) | 0x80000000;
    StartDmaChain(c, (u32)e->tags & 0x0FFFFFFF);
}

void func_001C25B0(s32 first, ...) {
    s32 buf[8];
    Ring_1C25B0* r = &D_002748F0[D_00274990];
    s32 n = 0;
    s32 x = first;
    r->f4C = 3;
    WaitDmaChannel(g_fromSprChannel, 0, 0);
    void* ap = (char*)__builtin_next_arg(first) - 56;
    while (x) {
        buf[n] = x;
        ap = (char*)ap + 8;
        x = *(s32*)((char*)ap - 8);
        n++;
    }
    s32 i = 0;
    n = r->f48 - n;
    while (n < r->f48 - 1) {
        *(u64*)(r->f8[n] - 0x10) = ((r->f28[n] >> 4) | 0x10000000) | ((u64)buf[i] << 32);
        n++;
        i++;
    }
    Dma_1C25B0* d = g_fromSprChannel;
    *(u64*)(r->f8[n] - 0x10) = ((r->f28[n] >> 4) | 0x70000000) | ((u64)buf[i] << 32);
    d->f0 &= ~0x40;
    d->f80 = (r->f4 & 0xFFFFFFF) + 0x80000000;
    StartDmaChainToMemory(d);
    r = &D_002748F0[1 - D_00274990];
    if (r->f4C == 3) r->f4C = 0;
}

LINKER_REMNANT(func_001C27A8);

INCLUDE_ASM(func_001C27B0);

void func_001C29C8()
{
    func_001C27B0(1, 0xFFFF);
}
