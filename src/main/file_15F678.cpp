// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "id_lookup_object.h"
#include "placed_object.h"
#include "animation.h"
#include "sound_record.h"
#include "asm_func.h"
#include "list_iter.h"
#include "v24a0.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "keyed_entry.h"
#include "identity_key.h"
#include "strip_mesh.h"
#include "vertex_batch.h"
#include "shapes.h"

struct Owner_15F678
{
    u8 pad[0x1ED0];
    s32 count;
    void** items;
};

void func_0015FA58(void* self);
void func_0015FD78(void* self);

struct Sub_15F9A0 { u8 pad0[8]; s32 count; void** items; };
struct Obj_15F9A0 { u8 pad0[0x54]; void* f54; u8 pad1[0x6C - 0x58]; s32 count6C; void* items70[1]; };

void func_0015F930(void* list, void* base, void* item);
void func_0015F710(void* self, void* value);

struct Class_0015FB28 { u8 pad0[8]; s32 flags; u8 pad1[0x54]; void (*visit)(void* self, void* arg); };
struct Node_0015FB28 { Class_0015FB28* cls; u8 pad0[0x18]; Node_0015FB28* next; u8 pad1[0x14]; Node_0015FB28* child; };


struct Elem_15F6C0 { u8 pad[0x54]; void* owner; Elem_15F6C0* next; };
struct Owner_15F6C0 { u8 pad[0x60]; Elem_15F6C0* head; };

void func_00152730(void* dst, void* src);

struct Item_15F7D8 { u8 pad[0x54]; void* f54; };
struct Group_15F7D8 { u8 pad[8]; s32 count; Item_15F7D8** items; };

s32 func_00182FC8(void* p);
void func_0015F6C0(void* ctx, void* a, void* b);

struct Item_15F8B0 { u8 pad[0x6C]; s32 count6C; void* items70[4]; };
struct Group_15F8B0 { u8 pad[8]; s32 count; Item_15F8B0** items; };

void func_0015F7D8(void* self, Group_15F8B0* group);

struct Items_15F930
{
    s32 count;
};

void* func_001F5B08(void* dst, void* src, s32 bytes);

struct Obj_15FA58 { u8 pad0[0x54]; void* f54; u8 pad1[0x6C - 0x58]; s32 count6C; void* items70[1]; u8 pad2[0x2C8 - 0x74]; u64 flags2C8; };
struct Self_15FA58 { u8 pad0[0x1ED0]; s32 count; Obj_15FA58** items; };

void func_0015F7D8(void* self, void* item);

struct Obj_15FBB8;
extern u8 D_00248D30[];

void func_001BF788(Obj_15FBB8* self, s32 n);
void func_001BFCD8(void* a0, void* a1, void* a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, s32 a5);

void func_00182C58(BaseObject* self);
void* func_0018D500(s32 size);
s32 func_0015A480(World* world, s32 item, void* c);
void func_0015F8B0(World* world, FoundList* sub);


struct Iter_15F710 {
    List01* list;
    u8* link;
    s32 offset;
    Iter_15F710* prev;
};

struct Node_15F710 {
    u8 pad0[0x54];
    Node_15F710* f54;
    u8 pad58[8];
    List01 list;
};

void func_00152600(List01* list, Node_15F710* node);
void func_0015F678(void* self, Node_15F710* node);

struct Begin_15F710 {
    static void Of(Iter_15F710* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (Iter_15F710*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_15F710 {
    static Node_15F710* Of(Iter_15F710* it)
    {
        Node_15F710* obj = *(Node_15F710**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

void* func_00160110();

s32* func_00160810();

struct Refs_160D00
{
    u8 pad[4];
    s32 refs;
};


void func_001612E8(void* self, s32 a1, s32 a2);


struct Entry_001601D8 { u8 pad0[0x28]; s32 f28; };

Entry_001601D8* func_00160110(void* a0);

s32 func_001602A0(void);

extern s32 D_002623CC;
extern u8 D_00261420[];

s32 func_001601A0(s32 a0);
void func_001608E0(void);
void func_00140F48(u8* p);
void func_00140D90(u8* p);
void func_00160880(void);

struct Vec3_162680 { f32 x; f32 y; f32 z; };

void* func_0018D500(s32 size);

struct Item_162810 { u8 pad[0x38]; void* ref; u8 rest[0x70 - 0x3C]; };

struct Owner_162810
{
    u8 pad0[0xC];
    s32 count;
    Item_162810* items;
    u8 pad1[0x50 - 0x14];
    s32 capacity;
    void** refs;
};

void* func_001F5C0C(void* p, s32 value, s32 size);

struct Counter_160CE8
{
    u8 pad[4];
    s32 count;
};

struct Counter_160CF0
{
    u8 pad[4];
    s32 count;
};

struct Ctx_160D10
{
    u8 pad[0x235C];
    s32 bits;
};

extern Ctx_160D10* D_00275710;

void func_0018D778(void);

void func_00162508(void* self);
void func_00188B08(void* a, void* b, void* c);
void func_00188B48(void* a, void* b, void* c);

struct Obj_00161BB0 {
    u8 pad0[0xF8];
    s32 f0F8;
};

void func_00162508(void* self);
void func_001626A8(void* self, u32* value);

KeyedEntry* func_001600A0(void);

struct __attribute__((packed)) Word_269984 { u32 value; };

extern u8 D_00261EF0[];
extern Word_269984 D_00269984;
extern s32 D_00262C64;
extern s32 D_002623CC;

void func_001605E8(void* self);
void func_00160CC8(void* self);
void func_00151A68(void* self);
void func_001608E0(void);

void func_001612E8(void* self, s32 a1, s32 a2);


void func_001612E8(void* self, s32 a1, s32 a2);


void func_001612E8(void* self, s32 a1, s32 a2);

struct Rec_160E80 { u8 pad0[4]; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; };

void func_001613C0(void* self, s32 a, s32 b, s32 c);



void func_00160918();

typedef void* (*Fill_161B80)(void*,s32,s32);

void func_001612E8(void* self, s32 a1, s32 a2);

void func_001612E8(void* self, s32 a1, s32 a2);

struct Ctx_161028 { u8 pad0[4]; s32 count; u8* base; };
struct Entry_161028 { s16 k0; s16 k1; u8 pad[4]; Entry_161028* next; };
struct Holder_161028 { u8 pad0[0x14]; Entry_161028* head; };
struct Elem_161028 { Holder_161028* holder; u8 pad[8]; };

void func_0018D608(void);
u8* func_0018D658(s32 size);
void func_0018D6F0(void);
s32 func_0013E430(u8* a0, u8* a1, s32* a2, f32 scale);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* obj, void* data);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* obj, void* text);

void func_001A7E90(void* self);

// the key keeps the file's comparison (IdentityKey has no method of its own: the forms differ per file)
struct Key_160948 : IdentityKey {
    s32 Same(Key_160948* o)
    {
        if (this == o) {
            return 1;
        }
        if (this == 0) {
            return 0;
        }
        if (o == 0) {
            return 0;
        }
        return ((signedWords[2] ^ signedWords[6]) ^ (o->signedWords[2] ^ o->signedWords[6])) == 0;
    }
};

struct Frame_160948;

struct Lst_160948 {
    void* head;
    s32 pad4;
    s32 next_off;
};

struct Frame_160948 {
    void* list;
    void* cursor;
    s32 next_off;
    Frame_160948* prev;
    Frame_160948(Lst_160948* l)
    {
        list = l;
        cursor = l;
        next_off = l->next_off;
        prev = (Frame_160948*)D_0027B314;
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_160948() { D_0027B314 = (ListFrame*)prev; }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + next_off;
        return n;
    }
};

struct Sys_160948 { u8 pad0[0x30]; s32 f30; };
extern Sys_160948 D_00275BC0;
extern Key_160948 D_00247AB0;
extern s32 D_00275F84;

Key_160948* func_00160180(s32 key);
void func_00160CC8(void* p);
void func_001F0428(void* a, s32 b, s32 c);
void func_001C0760(s32 flag);
void func_001C0790(s32 flag);
Animation* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_0012E760(void* obj);
void func_001E96F8(void* obj, s32 mode);

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* s, s32 n);

struct Sys_1608E0;
void func_00140D90(Sys_1608E0* p);

extern u8 D_00261420[];

struct Call_160DA0;

extern u8 D_00261EF0[];
extern u8 D_00261420[];
extern u8 D_0026FF68[];

void func_001DDAD0(Call_160DA0* x);
void func_001BE708(void);
void func_001EFFA0(Call_160DA0* dst, FadeRequest* args, s32 count);
void func_00140ED0(Call_160DA0* r);
void func_00194D30(Call_160DA0* self, s32 a, s32 b);
void func_00151E20(Call_160DA0* self, f32 amount);


struct Key_1602A0;
u32* func_00160810(Key_1602A0* key);

struct Obj_160578 { s32 f0; };

extern u8 D_00247AD0[];

void func_001F0428(Obj_160578* obj, s32 m, s32 n);
void func_0018E4F0(s32 slot, u32 n);

struct Obj_160918 { u8 pad[0]; };

void func_00160880(void);
void func_001F0428(Obj_160918* obj, s32 value, s32 count);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0024A6F8[];
s32 func_00152888(V24A0* a);

void func_001604B8(s32 mode);

// EXACT: self->block store ahead of self->f20 store.

struct Pkt_1639E8;
struct Hdr_1639E8
{
    u16* p;
    s32 count;
};
struct Vec3_1639E8
{
    f32 x;
    f32 y;
    f32 z;
};
struct Ent_1639E8
{
    u16* idx;
    s32 pad;
};
struct Self_1639E8
{
    u8 pad00[0x40];
    s32 f40;
};
// Built at startup: the compiler's initialiser and constructor for this file are func_00167D20
// and func_00167D48 (config/us/generated.tsv).
struct Rgba_1639E8
{
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
    Rgba_1639E8(u32 v) { rgba = v; }
};

// The file's .data, in retail's order.
char D_002623D0[8] = "<none>";
u8 D_002623D8[4] = { 0 };
s32 D_002623DC = 0;
Rgba_1639E8 D_002623E0(0x80101010);
s32 D_002623E4 = 1;
s32 D_002623E8[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 D_00262400[6] = { -1, 0, 4, 8, 12, 0 };
s32 D_00262418[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 D_00262430[6] = { -1, 0, 4, 8, 12, 0 };
s32 D_00262448[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 D_00262460[5] = { -1, 0, 4, 8, 12 };
s32 D_00262474 = 0x28;
extern u8 D_00001298[];
extern u8 D_00001368[];
extern u8 D_00000ED8[];

void func_001EE5C8(Pkt_1639E8* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_00152980(V24A0* f, s32 size);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_00161278(V24A0* f, s32 n);
void func_001EE668(Pkt_1639E8* s, s32 a, s32 b, void* data, s32 flags);
void func_001528E0(V24A0* f);
void func_001615F0(V24A0* f, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001EE4C0(Pkt_1639E8* s, u32* src);
void func_001EE528(Pkt_1639E8* s, s32 value);
void func_001EE3F0(Pkt_1639E8* s, void* data);
void func_001EE480(Pkt_1639E8* s);
void func_00163990(s32 mode, Pkt_1639E8* obj);

struct Zero_1639E8
{
    static void Clear(u32* q)
    {
        func_001F5C0C(q, 0, 0x10);
    }
};

struct Clamp_160B28 {
    static s32 Of(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) return lo;
        if (v > hi) return hi;
        return v;
    }
};

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.

class Obj_161958 {
public:
    u8 pad0[0xC];
    u64* cursor;
    u8 pad1[0x8];
    virtual void Begin(s32 arg);
    void func_00161958(s32 count);
};

struct Self_162508 { u8 pad0[0xF8]; u8* f0F8; u8 pad1[0x28]; s32 f124; };

extern V24A0 D_002622A8;
extern u8 D_000018C0[];

void func_00166658(void);
s32 func_001EE560(V24A0* s, s32 a, s32 b, s32 c);
void func_00161B80(Self_162508* self);
void func_00161C00(Self_162508* self);
void func_00161F70(Self_162508* self);

struct Copy_162508 {
    static void Words(s32* dst, s32* src, s32 n)
    {
        s32 rem = n & 3;
        s32 bulk = n - rem;
        s32 i;
        for (i = 0; i < rem; i++) {
            *dst++ = *src++;
        }
        for (i = 0; i < bulk; i += 4) {
            s32 a = src[0];
            s32 b = src[1];
            s32 c = src[2];
            s32 d = src[3];
            dst[0] = a;
            dst[1] = b;
            dst[2] = c;
            dst[3] = d;
            src += 4;
            dst += 4;
        }
    }
};

struct __attribute__((packed)) Rec_1626D8 {
    u64 q0;
    u64 q8;
    u64 q10;
    u64 q18;
    s32 f20;
    s32 value;
    Rec_1626D8() {}
};

struct Obj_1626D8 {
    u8 pad0[0xF8];
    u8* pF8;
    Rec_1626D8 cur;
    s32 count;
    Rec_1626D8 recs[1];
};

void func_0018D800(Rec_1626D8* dst, const void* src, s32 size);
void func_00162508(Obj_1626D8* self);
void func_00161BB0(Obj_1626D8* self, u8* value);

struct Pair_161C00 { s32 f0; u8* f4; };
struct Q_161C00 { u8 pad[0x18]; s32 f18; };
struct P_161C00 { u8 pad[4]; u8 f4[4]; u8 pad2[0x10]; s32 f18; Pair_161C00* f1C; u8 pad3[4]; Q_161C00* f24; };
struct V3_161C00 { f32 x; f32 y; f32 z; };
struct V4_161C00 { V3_161C00 v; f32 w; };
struct Elem_161C00 { V3_161C00 v; u8 pad[0xC]; u8 rgba[4]; f32 f1C; f32 f20; s32 f24; };
struct Self_161C00 {
    u8 pad[0x80];
    f32 f80;
    u8 pad2[0xF8 - 0x84];
    P_161C00* fF8;
    u8 pad3[0x124 - 0xFC];
    s32 f124;
    Elem_161C00 e[1];
};
struct Hd_161C00 { u16 f0; u16 f2; u8 pad[4]; u16 f8[4]; u16 f10; u8 pad3[6]; };
struct Packet_161C00 { u32 w[8]; };

void func_001F5C0C(Hd_161C00* p, s32 v, s32 n);
extern u8 D_00001A50[];
extern u8 D_000002F8[];
void func_0018D800(Packet_161C00* dst, u8* src, s32 n);

struct Mem_161F70 { u8 b[1]; };
struct Hd_161F70 { u16 f0; u16 f2; u8 pad4[4]; u16 f8[3]; u16 fE; u16 f10; u8 pad12[6]; };
struct Vec3_161F70 { f32 x, y, z; };
struct Out4_161F70 { Vec3_161F70 v; f32 w; };
struct Out3_161F70 { f32 x, y, z; };
struct Mat_161F70 { f32 m[4][4]; };
struct Vert_161F70
{
    Vec3_161F70 pos;
    f32 nx, ny, nz;
    u8 col[4];
    f32 u, v;
    s32 flag;
};
struct Sub_161F70 { u8 pad[0x18]; s32 n; };
struct Ent_161F70 { s32 n; u8* data; };
struct Mesh_161F70
{
    u8 pad0[4];
    u8 col[4];
    u8 pad8[0x10];
    s32 count;
    Ent_161F70* ents;
    u8 pad20[4];
    Sub_161F70* sub;
};
struct Tex_161F70 { u8 pad[0x418]; s32 n; u8 pad41C[4]; u8 data[1]; };
struct Self_161F70
{
    u8 pad0[0x80];
    f32 base;
    u8 pad84[0x30];
    s32 texCount;
    Tex_161F70* tex[16];
    Mesh_161F70* mesh;
    u8 padFC[0x28];
    s32 n;
    Vert_161F70 verts[1];
};

extern u8 D_00000288[];
extern u8 D_00001210[];
extern u8 D_00001AB0[];
extern u8 D_00000010[];

void func_001EE5C8(V24A0* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
Mem_161F70* func_001F5C0C(Mem_161F70* p, s32 value, s32 size);
void func_001EE3F0(V24A0* s, void* data);
void func_001EE420(V24A0* s, void* data);
void func_001EE480(V24A0* s);
void func_00152D70(V24A0* s);
void func_00152B80(V24A0* s, s32 n, void* data);
void func_00152B38(V24A0* s);
void func_0018D800(Mem_161F70* dst, void* src, s32 count);

struct Pkt_163ED8;
struct Vec3_163ED8 {
    f32 x;
    f32 y;
    f32 z;
};
struct Uv_163ED8 {
    f32 u;
    f32 v;
};
struct Rec_163ED8 {
    u8 pos;
    u8 pad1;
    u8 uv;
    u8 flags;
};
struct Ent_163ED8 {
    u16* idx;
    s32 pad;
};
struct Self_163ED8 {
    u8 pad00[0x40];
    s32 f40;
};
struct Info_163ED8 {
    u8 pad00[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
};
struct Hook_163ED8;
typedef MeshNode* (*HookFn_163ED8)(Hook_163ED8* self, StripMesh* mesh);
struct Hook_163ED8 {
    HookFn_163ED8* vt;
};
struct Obj_163ED8 {
    u8 pad00[0x38];
    Hook_163ED8* f38;
    u8 pad3C[0x40 - 0x3C];
    f32 f40;
    u8 pad44[0x54 - 0x44];
    Info_163ED8* f54;
};
struct Extra_163ED8 {
    s32 f0;
    s32 a4[4];
    s32 a14[4];
    s32 a24[4];
};
struct Unpack_163ED8 {
    u16 off[4];
    u16 strip[4];
    u16 f10;
    u16 f12;
    u16 pad14[2];
};
struct Hdr_163ED8 {
    u8 pad00[0x1C];
    Unpack_163ED8* p;
    Extra_163ED8* extra;
    s32 count;
};

extern u8 D_000002F8[];
extern u8 D_00001A50[];
extern u8 D_000036D0[];
extern u8 D_00001A80[];
extern u8 D_000027C0[];
extern u8 D_00002008[];
extern u8 D_000023B8[];
extern u8 D_00003A80[];
extern u8 D_00003A90[];

void func_00152B38(Pkt_163ED8* pkt);
void func_00152D70(Pkt_163ED8* pkt);
void func_00152CA0(Pkt_163ED8* pkt);
void func_001EE5C8(Pkt_163ED8* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_001EE498(Pkt_163ED8* s, s32 a, s32 b);
void func_001EE4C0(Pkt_163ED8* s, u32* src);
void func_001EE528(Pkt_163ED8* s, s32 value);
void func_001EE3F0(Pkt_163ED8* s, void* data);
void func_001EE420(Pkt_163ED8* s, void* data);
void func_001EE480(Pkt_163ED8* s);
void func_001EE668(Pkt_163ED8* s, s32 a, s32 b, void* data, s32 flags);
void func_001EE718(Pkt_163ED8* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* func_0018D5C0(s32 bytes);
void func_00163938(s32 mode, Pkt_163ED8* pkt);
void func_00169608(s32 a, s32 b, MeshNode* node);
void func_001694F8(StripMesh* mesh, MeshStrip* strip, s32 a, s32 b, s32 n, MeshNode* node);

void func_001EE3B8(void* obj, s32 size, s32 flags);

void func_0016C528(void*);

typedef void (*VFn_165728)(void* self);
struct Obj_165728 { VFn_165728* vtbl; };
struct Entry_165728 { u8 pad0[0x38]; Obj_165728* f38; u8 pad1[0x70 - 0x3C]; };
struct Node_165728 { u8 pad0[4]; void* f4; s32 f8; u8 pad1[0x80 - 0xC]; Node_165728* next80; };
struct Self_165728 { u8 pad0[0xC]; s32 count0C; Entry_165728* f10; u8* f14; u8 pad1[0x4C - 0x18]; Node_165728* f4C; };

void func_001662A8(void* self, void* entry, void* sub, void* ctx);
void func_001F2798(void* owner, void* unused, void* ctx);

struct __attribute__((aligned(16))) Quad_165828 { s32 a, b, c, d; };
struct Mat_165828 { Quad_165828 q[4]; };
struct Node_165828 { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct Elem_165828 { Node_165828* p0; u8 pad0[0xC]; Mat_165828 m; u8 tail[0x90 - 0x50]; };
struct Obj_165828 { s32 count; Elem_165828* elems; s32* keys; };
struct Frame_165828 { Quad_165828 a; u8 pad0[0x30]; Quad_165828 b; u8 pad1[0x30]; Mat_165828 m; };

void* func_0015A448(void* a, s32 b, void* c);
void func_00188B08(void* a, void* b, void* out);
void func_00188B48(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);

struct Elem_165FE0;
typedef void (*VFn_165FE0)(void* self, f32 f);

struct Elem_165FE0 {
    VFn_165FE0* vtbl;
    u8 pad4[0x8];
    void* f0C;
    u8 pad10[0x70];
    Elem_165FE0* next80;
};

struct Owner_165FE0 {
    u8 pad0[0x4C];
    Elem_165FE0* head4C;
};


s32 func_001B4B08(void* p);
void func_001F3408(void* p);

extern u8 D_00000010[];
extern u8 D_000000F0[];

struct Ctx_165588 { u8 pad0[0x28]; s32 f28; };
struct Range_165588 { u16 lo; u16 hi; };
struct Rec_165588 { u8 pad0[0x18]; u8* f18; Range_165588* f1C; };
struct Out_165588 { void* f0; void* f4; void* f8; void* fC; void* f10; void* f14; };

void* func_001EE318(void* p);
void func_00152938(void* buf, u32 count, u32 kind);
void func_001EE498(void* b, u32 x, u32 y);
void func_001EE5C8(void* s, u32 tag, s32 size, s32 a3, void* a4, void* a5);
void func_001EE3F0(void* s, void* n);
void func_001529E0(void* self, void* a, void* b);

struct Node_165920 { s32 tag; Node_165920* p4; u8 pad8[0x48]; void* p50; void* p54; u8 pad58[0x28]; Node_165920* next; u8 pad84[0xC]; };
struct Sub_165920 { u8 pad[0x10]; u32 flags; };
struct Rec_165920 { u8 pad[0x38]; Sub_165920* a; u8 pad3C[0x18]; void* b; };
struct Obj_165920 { s32 n0; void* p4; u8 pad8[4]; s32 count; Rec_165920* recs; void* p14; u8 pad18[0x28]; s32 n40; void* p44; u8 pad48[4]; Node_165920* head; s32 f50; };

void func_0018D800(Obj_165920* dst, void* src, s32 n);
void* func_0018D5C0(s32 n);
void* func_0018D568(s32 size, void* src);
void func_00165AE8(Obj_165920* o, void* a, void* b);
void func_00162810(Obj_165920* o);

// Index written (i << 4) * 9: a plain &items[i] gives a mult that loop.c does not strength-reduce (no s4 offset giv).
struct __attribute__((aligned(16))) Quad_1660E8 { s32 a, b, c, d; };
struct Mat_1660E8 { Quad_1660E8 q[4]; };
struct Obj_1660E8;
typedef void (*VFn_1660E8)(Obj_1660E8* self);
struct VT_1660E8 { u8 pad[0xC0]; VFn_1660E8 f; };
struct Link_1660E8 { u8 pad0[0x60]; Mat_1660E8 m60; u8 pad[4]; s32 a4; u8 pad2[8]; u32 flags; };
struct Obj_1660E8 { VT_1660E8* vt; u8 pad0[0x10C]; u8 sub110[0x30]; u8 sub140[0x40]; u8 pad180[0xA4]; Link_1660E8* link; };
struct Elem_1660E8 { Obj_1660E8* obj; u8 pad[0xC]; Quad_1660E8 q10[4]; Mat_1660E8 m50;  };
struct List_1660E8 { s32 count; Elem_1660E8* items; };
struct Par_1660E8 { u8 pad[0x30]; };

void func_00188B48(void* a, void* b, void* out);
void func_00188B08(void* a, void* b, void* out);
Mat_1660E8 func_00188668(Mat_1660E8 a, void* q);

struct Pkt_164868 {
    u8 pad[0x24];
};
struct Vec3_164868 {
    f32 x;
    f32 y;
    f32 z;
};
struct Uv_164868 {
    f32 u;
    f32 v;
};
struct Rec_164868 {
    u8 pos;
    u8 nrm;
    u8 uv;
    u8 flags;
};
struct Ent_164868 {
    u16* pos;
    u16* nrm;
};
struct Quad_164868 {
    f32 x[4];
    f32 y[4];
    f32 z[4];
    f32 w[4];
};
struct Self_164868 {
    u8 pad00[0x40];
    s32 f40;
};
struct Info_164868 {
    u8 pad00[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
};
struct Hook_164868;
typedef MeshNode* (*HookFn_164868)(Hook_164868* self, StripMesh* mesh);
struct Hook_164868 {
    HookFn_164868* vt;
};
struct Obj_164868 {
    u8 pad00[0x18];
    s32 f18;
    u8 pad1C[0x28 - 0x1C];
    s32 f28;
    u8 pad2C[0x38 - 0x2C];
    Hook_164868* f38;
    u8 pad3C[0x40 - 0x3C];
    f32 f40;
    u8 pad44[0x54 - 0x44];
    Info_164868* f54;
};
struct Extra_164868 {
    s32 f0;
    s32 a4[4];
    s32 a14[4];
    s32 a24[4];
};
struct Unpack_164868 {
    u16 off[4];
    u16 strip[4];
    u16 f10;
    u16 f12;
    u16 pad14[2];
};
struct Hdr_164868 {
    u8 pad00[0x14];
    u32 f14;
    u8 pad18[0x1C - 0x18];
    Unpack_164868* p;
    Extra_164868* extra;
    s32 count;
};

extern u8 D_00000288[];
extern u8 D_00001AB0[];
extern u8 D_00002008[];
extern u8 D_00002088[];
extern u8 D_000023B8[];
extern u8 D_000023D8[];
extern u8 D_000023F0[];
extern u8 D_000027C0[];
extern u8 D_00003A80[];
extern u8 D_00003AA0[];

void func_00152B38(Pkt_164868* pkt);
void func_00152D70(Pkt_164868* pkt);
void func_00152CA0(Pkt_164868* pkt);
void func_001EE5C8(Pkt_164868* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_001EE498(Pkt_164868* s, s32 a, s32 b);
void func_001EE4C0(Pkt_164868* s, u32* src);
void func_001EE528(Pkt_164868* s, s32 value);
void func_001EE3F0(Pkt_164868* s, void* data);
void func_001EE480(Pkt_164868* s);
void func_001EE668(Pkt_164868* s, s32 a, s32 b, void* data, s32 flags);
void func_001EE718(Pkt_164868* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* func_0018D5C0(s32 bytes);
void func_00163938(s32 mode, Pkt_164868* pkt);
void func_00169608(s32 a, s32 b, MeshNode* node);
void func_001694F8(StripMesh* mesh, MeshStrip* strip, s32 a, s32 b, s32 n, MeshNode* node);

void func_0015F678(Owner_15F678* owner, u8* obj);
void func_0015F6C0(void* ctx, Owner_15F6C0* self, Owner_15F6C0* other);
void func_0015F710(void* self, Node_15F710* owner);
void func_0015F7D8(void* self, Group_15F7D8* group);
void func_0015F8B0(void* self, Group_15F8B0* group);
void func_0015F930(Items_15F930* list, s32* arr, s32 value);
void func_0015F9A0(void* self, Sub_15F9A0* s);
void func_0015FA58(Self_15FA58* self);
void func_0015FB28(Node_0015FB28* self, void* arg);
s32 func_0015FBA0(PlacedObject* self, s32* out);
void func_0015FBB8(PlacedObject* self, s32 flag);
void func_0015FF58(void* self);
void func_00160050(IdLookupObject* obj, s32 value);
void func_00160070();
KeyedEntry* func_001600A0(KeyedEntry* key);
void* func_00160110(s32 key);
void* func_00160148();
s32 func_00160180(void);
s32 func_001601A0(void);
s32 func_001601D8(void* a0);
void func_00160208(s32 key, s32* a1, s32* a2, s32* a3);
s32 func_001602A0(void);
void func_00160340(s32 n);
void func_001603E8(s32 n);
void func_001604B8(s32 mode);
void func_00160578(s32 kind);
void func_001605E8(GameProgress* self);
s32 func_00160650(GameProgress* s);
void func_00160690(s32 a0, s32 flags);
void func_001607D0(f32 dx);
void* func_00160810(s32 key);
s32 func_00160850();
void func_00160880(void);
void func_001608E0(void);
void func_00160918(void);
void func_00160948(void);
s32 func_00160B28(u8* p);
void func_00160C48(s32 value);
s32 func_00160C58();
void* func_00160CA0(u8* self,s32 index);
void func_00160CC8(void* p);
void func_00160CE8(Counter_160CE8* c);
s32 func_00160CF0(Counter_160CF0* c);
void func_00160D00(Refs_160D00* self);
s32 func_00160D10();
void func_00160D30(u32* out);
s32 func_00160D98(void);
void func_00160DA0(void);
void func_00160E80(Rec_160E80* self);
s32 func_00161028(Ctx_161028* dst, Ctx_161028* src, s32 key, s32 maxOut, Entry_161028** out);
V24A0* func_001611B8(V24A0* self);
void func_00161200(V24A0* self);
void func_00161278(V24A0* f, s32 n);
s32 func_001612E8(V24A0* obj);
void func_001612F8(V24A0* self, u64 prim, s32 nloop, s32 nreg, u64 data, s32* out);
void func_001613C0(V24A0* self, s32 a1, s32 a2, s32 a3);
void func_00161458(V24A0* self, u32 value);
void func_001614C8(V24A0* self,s32 a,s32 b);
void func_00161520(V24A0* self,f32 a,f32 b,f32 c);
void func_00161588(V24A0* self, s32 a1, s32 a2, u64 a3);
void func_001615F0(V24A0* self, u32 a1, u32 a2, u32 a3, u32 a4);
void func_00161670(V24A0* self, u32 a1, u32 a2, u32 a3, u32 a4);
void func_00161708(V24A0* self, u64 a1, u64 a2);
void func_00161768(V24A0* self, u32 a1, u64 a2);
void func_001617E8(V24A0* self, s32 tag, f32 value);
void func_00161860(V24A0* self, s32 a1, s32 a2);
void func_001618C0(V24A0* self, s32 a1, s32 a2, u32 a3, u32 a4);
void func_00161A88(void* self, s32 flag);
void func_00161AB0(u8* self, void* a1, void* a2);
void func_00161B80(u8* self);
void func_00161BB0(Obj_00161BB0* self, s32 value);
void func_00161C00(Self_161C00* self);
void func_00161F70(Self_161F70* self);
void func_00162508(Self_162508* self);
void func_00162680(VertexBatch* body, Vec3_162680* v);
void func_001626A8(u8* dst, u8* src);
void func_001626C0(VertexBatch* dst, U64P* src);
void func_001626D8(Obj_1626D8* self, s32 value);
void func_00162810(Owner_162810* owner);
void func_00163938(s32 mode, void* obj);
void func_00163990(s32 mode, void* obj);
void func_001639E8(Self_1639E8* self, s32 mode, Hdr_1639E8* hdr, s32 n, Vec3_1639E8* vecs, s32 extra,
                   void* extraData, Ent_1639E8* ents, Vec3_1639E8* verts, void* data, Pkt_1639E8* pkt);
void func_00163ED8(Self_163ED8* self, Obj_163ED8* obj, s32 mode, Hdr_163ED8* hdr, StripMesh* mesh,
                   Vec3_163ED8* vecs, s32 unused6, u8 (*tints)[4], Uv_163ED8* uvs, s32 n, Rec_163ED8* recs,
                   Ent_163ED8* ents, Vec3_163ED8* verts, s32 unused13, f32* weights, Pkt_163ED8* pkt,
                   s32** outs);
void func_00164868(Self_164868* self, Obj_164868* obj, s32 unused2, s32 mode, Hdr_164868* hdr,
                   StripMesh* mesh, Vec3_164868* vecs, Vec3_164868* nrms, u8 (*tints)[4], Uv_164868* uvs,
                   s32 n, Rec_164868* recs, Ent_164868* ents, Vec3_164868* verts, Vec3_164868* vnrms,
                   f32* weights, Pkt_164868* pkt, s32** outs);
void func_00165588(Ctx_165588* a, Rec_165588* b, Out_165588* c);
void func_00165728(Self_165728* self, PlacedObject* ctx);
void func_00165828(Obj_165828* self, PlacedObject* ctx);
void func_00165920(Obj_165920* self, s32 arg, void* src);
void func_00165FE0(Owner_165FE0* self, PlacedObject* sub, f32 f);
void func_001660A0(PlacedObject* self);
void func_001660E8(PlacedObject* self, Par_1660E8* par);
void func_00166658(void);

void func_0015F678(Owner_15F678* owner, u8* obj)
{
    u64 flags = *(u64*)(obj + 0x2C8);
    u64 bit = (u64)0x8000 << 24;
    if (!(flags & bit))
    {
        *(u64*)(obj + 0x2C8) = flags | bit;
        s32 n = owner->count;
        owner->items[n] = obj;
        owner->count = n + 1;
    }
}

void func_0015F6C0(void* ctx, Owner_15F6C0* self, Owner_15F6C0* other)
{
    ListFrame frame;
    if (self != other) {
        Elem_15F6C0* e = other->head;
        if (e != 0) {
            e->owner = self;
            for (e = e->next; e != 0; e = e->next) {
                e->owner = self;
            }
        }
        SpliceListToEnd(&self->head, &other->head);
    }
}

void func_0015F710(void* self, Node_15F710* owner)
{
    Iter_15F710 it;
    Node_15F710* node;
    Begin_15F710::Of(&it, &owner->list);
    while ((node = Next_15F710::Of(&it)) != 0) {
        if (node != owner) {
            RemoveFromList(&owner->list, node);
            node->f54 = node;
            node->list.tail = (u8*)node;
            node->list.head = (u8*)node;
        }
        QueueObjectForRegroup(self, node);
    }
    g_activeListFrames = (ListFrame*)it.prev;
}

void func_0015F7D8(void* self, Group_15F7D8* group)
{
    s32 i = 0;
    while (i < group->count) {
        if (IsObjectAttached(group->items[i]) != 0) {
            break;
        }
        i++;
    }
    s32 first = i;
    for (; i < group->count; i++) {
        if (IsObjectAttached(group->items[i]) != 0) {
            MergeObjectLinkLists(self, group->items[first]->f54, group->items[i]->f54);
        }
    }
}

void func_0015F8B0(void* self, Group_15F8B0* group)
{
    if (group->count >= 2) {
        for (s32 i = 0; i < group->count; i++) {
            Item_15F8B0* item = group->items[i];
            u32 n = item->count6C;
            if (n < 4) {
                item->items70[n] = group;
                item->count6C = n + 1;
            }
        }
        MergeObjectGroupMembers(self, group);
    }
}

void func_0015F930(Items_15F930* list, s32* arr, s32 value)
{
    s32 i = list->count;
    s32* p = (s32*)(((s32)i << 2) + (s32)arr);
    i--;
    for (;;)
    {
        if (i < 0)
        {
            return;
        }
        p--;
        if (*p == value)
        {
            break;
        }
        i--;
    }
    (void)func_001F5B08(arr, arr + 1, (list->count - i) * 4 - 4);
    list->count--;
}

void func_0015F9A0(void* self, Sub_15F9A0* s)
{
    s32 i;
    Obj_15F9A0* obj;
    if (s->count >= 2) {
        for (i = 0; i < s->count; i++) {
            obj = (Obj_15F9A0*)s->items[i];
            RemoveValueFromArray(&obj->count6C, obj->items70, s);
        }
        for (i = 0; i < s->count; i++) {
            obj = (Obj_15F9A0*)s->items[i];
            if (obj->f54 != 0) {
                DissolveObjectLinkList(self, obj->f54);
                break;
            }
        }
    }
}

void func_0015FA58(Self_15FA58* self)
{
    s32 i = self->count;
    i--;
    if (i >= 0) {
        u64 mask = ((u64)~0x80 << 32) | 0xFFFFFFFF;
        do {
            Obj_15FA58* obj = self->items[i];
            obj->flags2C8 &= mask;
            if (obj->f54 == obj) {
                s32 j = obj->count6C;
                j--;
                for (; j >= 0; j--) {
                    MergeObjectGroupMembers(self, obj->items70[j]);
                }
            }
            i--;
        } while (i >= 0);
    }
    self->count = 0;
}

void func_0015FB28(Node_0015FB28* self, void* arg)
{
    ListFrame frame;
    if (self->cls->visit != 0)
        self->cls->visit(self, arg);
    Node_0015FB28* node = self->child;
    if (node != 0)
    {
        do
        {
            if (node->cls->flags & 1)
                VisitObjectTree(node, arg);
            node = node->next;
        } while (node != 0);
    }
}

s32 func_0015FBA0(PlacedObject* self, s32* out)
{
    s32 bit = (s32)(self->flags >> 38) & 1;
    *out = bit;
    return bit;
}

void func_0015FBB8(PlacedObject* self, s32 flag)
{
    if (flag != 0) {
        self->vA0 = self->v150;
        self->vB0 = self->v160;
        self->f29C = 0;
        if (self->f2AC != 0) {
            StopSoundRecord((Obj_15FBB8*)self->f2AC->p1C, 0);
        }
        self->desc02()->m20(self, (Vec02*)D_00248D30);
        self->desc02()->m21(self, (Vec02*)D_00248D30);
        self->flags |= (u64)1 << 38;
    } else {
        self->flags &= ~((u64)1 << 38);
        self->desc02()->m20(self, &self->vA0);
        self->desc02()->m21(self, &self->vB0);
        SoundRecord* c = self->f2AC;
        if (c != 0) {
            StartSoundEffect(c->p00, &c->p1C, (void*)self, 0, c->f04, c->f08, c->f0C, c->f10, c->f20, &c->b14, 0);
        }
    }
}

ASM_FUNC(func_0015FCD8);

ASM_FUNC(func_0015FD78);

void func_0015FF58(void* self)
{
    RegroupQueuedObjects(self);
    func_0015FD78(self);
}

void func_0015FF88(IdLookupObject* self)
{
    StartObject(self);
    World* cur = self->world;
    FoundList* sub = &self->found;
    sub->items = (s32*)AllocateFrontMemory(self->idCount * 4);
    for (s32 i = 0; i < self->idCount; i++) {
        s32 r = func_0015A480(cur, self->ids[i], self->parent);
        if (r != 0) { s32 n = sub->count; sub->items[n] = r; sub->count = n + 1; }
    }
    RegisterObjectGroup(cur, &self->found);
}

void func_00160050(IdLookupObject* obj, s32 value) { obj->ids[obj->idCount++] = value; }

void func_00160070() { func_00160918(); }

LINKER_REMNANT(func_00160090);

KeyedEntry* func_001600A0(KeyedEntry* key)
{
    KeyedEntry* p = (KeyedEntry*)g_keyedEntries;
    KeyedEntry* end = (KeyedEntry*)((u8*)g_keyedEntries + 0x7E8);
    s32 m;

    do {
        if (key == p) {
            m = 1;
        } else if (key == 0 || p == 0) {
            m = 0;
        } else {
            m = ((key->key.signedWords[2] ^ key->key.signedWords[6]) ^ (p->key.signedWords[2] ^ p->key.signedWords[6])) == 0;
        }
        if (!m) {
            p = (KeyedEntry*)((u8*)p + 0x2C);
        } else {
            return p;
        }
    } while (p < end);
    return 0;
}

void* func_00160110(s32 key)
{
    u8* p = (u8*)g_keyedEntries;
    u8* end = (u8*)g_keyedEntries + 0x7E8;
    for (;;) {
        if (key != *(s32*)(p + 0x20)) {
            p += 0x2C;
            if ((u32)p < (u32)end) {
                continue;
            }
            return 0;
        }
        return p;
    }
}

void* func_00160148()
{
    void* p = FindEntryById();
    if (p == 0)
    {
        return D_002623D0;
    }
    return *(void**)((u8*)p + 0x24);
}

LINKER_REMNANT(func_00160178);

s32 func_00160180(void)
{
    return (s32)FindEntryById();
}

s32 func_001601A0(void)
{
    s32 v;
    KeyedEntry* r = FindKeyEntry();
    v = -1;
    if (r != 0) v = r->id;
    return v;
}

LINKER_REMNANT(func_001601D0);

s32 func_001601D8(void* a0)
{
    Entry_001601D8* e = FindEntryById(a0);
    s32 r = 0;
    if (e != 0) {
        r = e->f28;
    }
    return r;
}

void func_00160208(s32 key, s32* a1, s32* a2, s32* a3)
{
    KeyedEntry* p;
    KeyedEntry* end;

    *a3 = 0;
    *a2 = 0;
    p = (KeyedEntry*)g_keyedEntries;
    *a1 = 0;
    end = (KeyedEntry*)((u8*)g_keyedEntries + 0x7E8);
    do {
        if ((p->id >> 8) == key) {
            if (p->i28 & 2) {
                (*a1)++;
            }
            if (p->i28 & 4) {
                (*a2)++;
            }
            if (p->i28 & 8) {
                (*a3)++;
            }
        }
        p++;
    } while (p < end);
}

s32 func_001602A0(void) {
    u32 mask = 0xE;
    u8* p = (u8*)g_keyedEntries;
    u8* end = (u8*)g_keyedEntries + 0x7E8;
    do {
        u32* r = GetLevelEntryByKey((Key_1602A0*)*(void**)(p + 0x20));
        mask &= ~*(u32*)(p + 0x28) | *r;
        p += 0x2C;
    } while (p < end);
    s32 clear = -3;
    s32 n = 4;
    u8* q = (u8*)&g_saveData->levels[1].f448;
    do {
        u32 flag = *(u32*)q & 0x20;
        mask = (flag == 0) ? (mask & (u32)clear) : mask;
        q += 0x44C;
        n--;
    } while (n >= 0);
    return mask;
}

void func_00160340(s32 n)
{
    switch (n) {
    case 1: g_saveData->f19F4 |= 0x10; break;
    case 2: g_saveData->f19F4 |= 0x40; break;
    case 3: g_saveData->f19F4 |= 0x100; break;
    case 4: g_saveData->f19F4 |= 0x400; break;
    case 5: g_saveData->f19F4 |= 0x1000; break;
    }
}

void func_001603E8(s32 n)
{
    g_saveData->levels[n].f448 |= 0x20;
    switch (n) {
    case 1:
        g_saveData->f19F4 |= 0x20;
        break;
    case 2:
        g_saveData->f19F4 |= 0x80;
        break;
    case 3:
        g_saveData->f19F4 |= 0x200;
        g_saveData->f19F0 |= 0x10000;
        break;
    case 4:
        g_saveData->f19F4 |= 0x800;
        break;
    case 5:
        func_001604B8(2);
        break;
    }
}

void func_001604B8(s32 mode)
{
    switch (mode) {
    case 2:
        g_saveData->f19F4 |= 0xA002;
        g_saveData->f19F8 |= 2;
        break;
    case 4:
        if ((func_001602A0() & 4) != 0) {
            g_saveData->f19F4 |= 0xC000;
        }
        break;
    case 8:
        if ((func_001602A0() & 8) != 0) {
            g_saveData->f19F4 |= 0xC;
            g_saveData->f19F8 |= 0xC;
        }
        break;
    }
}

void func_00160578(s32 kind)
{
    s32 s0 = -1;

    if (kind != 4) { if (kind < 5) { if (kind == 2) { s0 = 0xD; } } } else { s0 = 0xE; }
    StartObjectFade((Obj_160578*)D_00247AD0, -1, 1);
    if (s0 != -1) {
        QueueMovieWithSuccessor(s0, 0xF);
    }
}

void func_001605E8(GameProgress* self)
{
    func_001F5C0C(self, 0, 0x1A00);
    self->type = 0x12;
    self->f19D8 = 0;
    self->f19F0 = 0;
    self->size = 0x1A00;
    self->f19DC = 3;
    self->f19E0 = 5;
    self->f19FC = -1;
    ApplyPadPatternSetting(self);
}

s32 func_00160650(GameProgress* s)
{
    u8* p = (u8*)&s->fC;
    s32 sum = 0;
    for (s32 i = 0; i < (u8*)(s + 1) - (u8*)&s->fC; i++) {
        sum += *p++;
    }
    return sum;
}

void func_00160690(s32 a0, s32 flags)
{
    s32 r = GetEntryIdByKey(a0);
    s32 hi = (r != -1) ? (r >> 8) : 0;
    s32 lo = (r != -1) ? (r & 0xFF) : 0;
    G27C230* base = &g_saveData->levels[hi];
    GameProgress* g = g_saveData;
    s32 gate = g->f19E0;
    g_currentLevelRecord = base;
    g_currentEntry = (G27C230*)((u8*)base + lo * 0x78);
    if (gate < 0 || (flags & 2) != 0) {
        func_001608E0();
    } else if ((flags & 1) != 0) {
        RestoreFlagTableSnapshot(g_flagTable);
    } else if ((flags & 4) != 0) {
        func_00160880();
    } else {
        func_00140D90(g_flagTable);
    }
    g = g_saveData;
    g_previousLevelIndex = g->f19D8;
    g->f19D8 = hi;
    g->f19DC = lo;
    g_currentLevelRecord->f448 |= 1;
    g_currentEntry->flags |= 1;
}

void func_001607D0(f32 dx)
{
    g_saveData->fC += dx;
    g_currentLevelRecord->f444 += dx;
    g_currentEntry->f04 += dx;
}

void* func_00160810(s32 key)
{
    return key == -1 ? 0 : (u8*)&g_saveData->levels[key >> 8] + (key & 0xFF) * 0x78;
}

s32 func_00160850()
{
    s32* p = GetLevelEntryByKey();
    s32 value = 0;
    if (p)
    {
        value = *p;
    }
    return value;
}

void func_00160880(void)
{
    ResetGameProgress(g_saveData);
    D_00269984.value = 0;
    func_00160CC8(D_002623D8);
    ClearScatterController(g_scatterController);
    g_buttonCodeFlags = 0;
    g_previousLevelIndex = -1;
    func_001608E0();
}

void func_001608E0(void)
{
    GameProgress* g = g_saveData;
    g->f19E0 = 5;
    g->f19E4 = 0;
    func_00140D90((Sys_1608E0*)g_flagTable);
}

void func_00160918(void)
{
    func_00160880();
    StartObjectFade((Obj_160918*)&D_00247AB0, -1, 0);
}

void func_00160948(void)
{
    Key_160948* k = func_00160180((g_saveData->f19D8 << 8) | g_saveData->f19DC);
    if (k == 0) {
        k = &D_00247AB0;
    }
    func_00160CC8(D_002623D8);
    if (g_elementStack.f30 != 1 || g_saveData->fC != 0.0f || !k->Same((Key_160948*)&D_00275B04)) {
        StartObjectFade(k, -1, 1);
    } else if (g_elementStack.f30 == 1) {
        if (D_00275F84 == 0) {
            func_001C0760(g_saveData->f19EC & 0x80);
            func_001C0790(g_saveData->f19EC & 0x40);
            Animation* r = FindFirstObjectById(g_currentWorld, 0x105, 0x494, 0);
            if (r != 0) {
                Frame_160948 frame((Lst_160948*)r->props6C);
                void* head = *(void**)r->props6C;
                frame.cursor = (u8*)head + frame.next_off;
                void* node = head;
                if (node != 0) {
                    do {
                        StopAnimationPlayer(node);
                        node = frame.Next();
                    } while (node != 0);
                }
            }
            g_elementStack.f30 = -1;
            SetElementStackState(&g_elementStack, 3);
        }
    }
}

s32 func_00160B28(u8* p)
{
    s32 total = 0;
    s32 done = 0;
    u32 i;
    s32 k;
    for (i = 0; i < 0x2E; i++) {
        u8* e = (u8*)g_keyedEntries + i * 0x2C;
        u32 v = *(u32*)(e + 0x20);
        s32 idx = (s32)v >> 8;
        if (idx != 0) {
            u32 flags = *(u32*)(e + 0x28);
            u32* w = (u32*)(p + (idx * 0x44C + 0x10) + (v & 0xFF) * 0x78);
            u32 bit;
            total++;
            done += *w & 1;
            for (bit = 2; bit & 0xE; bit <<= 1) {
                if (flags & bit) {
                    total++;
                    if (*w & bit) done++;
                }
            }
        }
    }
    for (k = 0; k < 5; k++) {
        total++;
        if (*(u32*)(p + 0x8A4 + k * 0x44C) & 0x20) done++;
    }
    if (done == 0) return 0;
    if (done == total) return 100;
    return Clamp_160B28::Of(done * 100 / total, 1, 99);
}

void func_00160C48(s32 value)
{
    g_saveData->f19E4 = value;
}

s32 func_00160C58()
{
    s32 result=0;
    if (g_saveData->f19E4>0 || (g_buttonCodeFlags&2)) result=1;
    return result;
}

LINKER_REMNANT(func_00160C90);

void* func_00160CA0(u8* self,s32 index)
{
    if ((u32)(index-0x33B)>=12) return 0;
    else return self+(index*4-0xCD8);
}

void func_00160CC8(void* p)
{
    func_001F5C0C(p, 0, 8);
}

void func_00160CE8(Counter_160CE8* c)
{
    c->count = 0;
}

s32 func_00160CF0(Counter_160CF0* c)
{
    return ++c->count;
}

void func_00160D00(Refs_160D00* self)
{
    self->refs--;
}

s32 func_00160D10()
{
    return g_saveData->f19F0 & g_currentWorld->bits;
}

void func_00160D30(u32* out)
{
    s32 m;
    switch (g_saveData->f19D8) {
    case 4: m = 0x10000000; break;
    case 1: m = 0x20000000; break;
    case 2: m = 0x40000000; break;
    case 3: m = 0x80000000; break;
    case 0:
    case 5: m = 0; break;
    }
    if (out) *out = m;
}

s32 func_00160D98(void)
{
    return 2;
}

void func_00160DA0(void)
{
    GameProgress* o = g_saveData;
    u8* x = (u8*)g_currentWorld;
    s32 t = o->f19E0 - 1;
    o->f19E0 = t;
    func_001DDAD0((Call_160DA0*)x);
    StopLockedStreamVoice();
    GameProgress* p = g_saveData;
    s32 m = p->f19DC;
    if (m == 1) {
        FadeRequest args;
        args.kind = m;
        args.text = (u8*)&D_00275B04;
        u8* base = args.text - 0x14;
        args.f08 = *(s32*)(base + 0x8);
        args.f0C = *(s32*)(base + 0xC);
        args.flags = 0x10;
        StartScreenFade((Call_160DA0*)&g_screenFade, &args, 1);
    } else if (p->f19E0 >= 0) {
        StartScreenFadeFromFlagTable((Call_160DA0*)g_flagTable);
    } else {
        SetPauseMenuLayerPage((Call_160DA0*)g_pauseMenuElement, 0, 1);
    }
    RaiseScatterLevels((Call_160DA0*)g_scatterController, 1.0f);
}

void func_00160E80(Rec_160E80* self)
{
    self->f4 = 0;
    self->f8 = 0;
    self->fC = 0;
    self->f10 = 0;
    self->f14 = 0;
    self->f18 = 0;
}

ASM_FUNC(func_00160EA0);

s32 func_00161028(Ctx_161028* dst, Ctx_161028* src, s32 key, s32 maxOut, Entry_161028** out)
{
    s32 buf[4];

    PushBackMemoryMark();
    u8* k = AllocateBackMemory(src->count * 12);
    buf[0] = (s32)k;
    if (func_0013E430(src->base, dst->base + key * 16, buf, 1.0f) != 2) {
        PopBackMemoryMark();
        return 0;
    }
    s32 i = 0;
    s32 n = (((s32)buf[0] - (s32)k) * (s32)0xAAAAAAAB) >> 2;
    s32 j = 0;
    if (n > 0) {
        for (; i < n; i++) {
            Elem_161028* e = (Elem_161028*)(k + i * 12);
            Entry_161028* p = e->holder->head;
            if (p == 0) {
                continue;
            }
            Entry_161028** o = (Entry_161028**)(j * 4 + (s32)out);
            while (p != 0) {
                if (key == p->k0 || key == p->k1) {
                    s32 m;
                    for (m = 0; m < j; m++) {
                        if (p == out[m]) {
                            break;
                        }
                    }
                    if (m >= j && j < maxOut) {
                        *o = p;
                        o++;
                        j++;
                    }
                }
                p = p->next;
            }
        }
    }
    PopBackMemoryMark();
    return j;
}

extern const Fn_Table D_0024A6F8[6] = { 0, 0, 0, (Fn_Table)(void (*)(V24A0* f, s32 n))func_00161278, 0, 0 };

V24A0* func_001611B8(V24A0* self)
{
    (void)InitPacketBuffer(self);
    self->f14 = 1;
    self->vt = (const V24A0_Vt*)g_gifPacketMethods;
    self->f1C = 0;
    self->f20 = 0;
    self->f24 = 0;
    return self;
}

void func_00161200(V24A0* self)
{
    if (self->f1C != 0) {
        const V24A0_Vt* s = self->vt;
        s->close((V24A0*)((u8*)self + s->adj1), 1);
    } else {
        BeginGifTag(self, 0, 1, 0xE);
        const V24A0_Vt* s = self->vt;
        s->close((V24A0*)((u8*)self + s->adj1), 1);
    }
}

void func_00161278(V24A0* f, s32 n)
{
    if (f->f1C == 0)
        return;
    u32 q = f->f24 / f->f20;
    u32 a2 = f->curU;
    if (a2 & 0xF) {
        f->curU = a2 + 8;
        *(u64*)a2 = 0;
    }
    u32* p = f->f1C;
    u32 w;
    if (n) {
        w = *p;
        w |= 0x8000;
    } else {
        w = *p;
    }
    w |= q;
    *p = w;
    f->f1C = 0;
}

s32 func_001612E8(V24A0* obj) { return ++obj->f24; }

void func_001612F8(V24A0* self, u64 prim, s32 nloop, s32 nreg, u64 data, s32* out)
{
    V24A0* w = self;
    const V24A0_Vt* sub = w->vt;
    sub->close((V24A0*)((u8*)self + sub->adj1), 0);

    u8* p = w->cur;
    u64 tag = (prim << 47) | (1ULL << 46) | (u64)nloop | ((u64)nreg << 60);
    w->cur = p + 16;
    *(u64*)(p + 8) = data;
    *(u64*)p = tag;
    if (out != 0) {
        *out = (s32)w->cur;
    }
    w->cur = w->cur + nloop * nreg * 16;
}

void func_001613C0(V24A0* self, s32 a1, s32 a2, s32 a3)
{
    const V24A0_Vt* d = self->vt;
    d->close((V24A0*)((u8*)self + d->adj1), 0);
    u8* blk = self->cur;
    s64 lo = ((s64)a2 << 60) | ((s64)1 << 46);
    s64 hdr = ((s64)a1 << 47) | lo;
    self->cur = blk + 0x10;
    *(s64*)blk = hdr;
    *(s64*)(blk + 8) = (s64)a3;
    self->block = blk;
    self->f20 = a2;
    self->f24 = 0;
}

void func_00161458(V24A0* self, u32 value)
{
    CountGifEntry(self, 1, 1);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = value & 0xFF;
    p[1] = (value & 0xFF00) >> 8;
    p[2] = (value >> 16) & 0xFF;
    p[3] = value >> 24;
}

void func_001614C8(V24A0* self,s32 a,s32 b)
{
    CountGifEntry(self,1,3);
    s32* p=(s32*)self->cur;
    self->cur+=16;
    p[0]=a;
    p[1]=b;
}

void func_00161520(V24A0* self,f32 a,f32 b,f32 c)
{
    CountGifEntry(self,1,2);
    f32* p=(f32*)self->cur;
    self->cur+=16;
    p[0]=a;
    p[1]=b;
    p[2]=c;
}

void func_00161588(V24A0* self, s32 a1, s32 a2, u64 a3)
{
    CountGifEntry(self, 1, 5);
    u8* p = self->cur;
    self->cur = p + 0x10;
    *(s32*)(p + 0x0) = a1;
    *(s32*)(p + 0x4) = a2;
    *(u64*)(p + 0x8) = a3;
}

void func_001615F0(V24A0* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 1, 4);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = a1;
    p[1] = a2;
    p[2] = a3;
    p[3] = (a4 & 0xFF) << 4;
}

void func_00161670(V24A0* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 1, 4);
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 4);
    p[0] = a1;
    p[1] = a2;
    p[2] = (a3 & 0xFFFFFF) << 4;
    p[3] = ((a4 & 0xFF) << 4) | 0x8000;
}

void func_00161708(V24A0* self, u64 a1, u64 a2)
{
    CountGifEntry(self, 1, 14);
    u64* p = self->cur64;
    self->cur64 = p + 2;
    p[0] = a2;
    p[1] = a1;
}

LINKER_REMNANT(func_00161760);

void func_00161768(V24A0* self, u32 a1, u64 a2)
{
    const V24A0_Vt* sub = self->vt;
    sub->close((V24A0*)((u8*)self + sub->adj1), 0);
    u64* p = self->cur64;
    self->cur64 = p + 2;
    p[1] = a2;
    p[0] = ((u64)a1 << 60) | ((u64)0x8000 << 43);
    self->f20 = a1;
    self->last = p;
    self->f24 = 0;
}

void func_001617E8(V24A0* self, s32 tag, f32 value)
{
    CountGifEntry(self, 0, 1);
    s32 bits = *(s32*)&value;
    u64 hi = (u64)(s64)bits << 32;
    u64 lo = (u64)(u32)tag;
    u64* p = (u64*)self->cur;
    self->cur = (u8*)(p + 1);
    *p = lo | hi;
}

LINKER_REMNANT(func_00161858);

void func_00161860(V24A0* self, s32 a1, s32 a2)
{
    CountGifEntry(self, 0, 3);
    u64 v = (u64)a1 | (u64)(a2 << 16);
    u64* p = self->cur64;
    self->cur64 = p + 1;
    *p = v;
}

void func_001618C0(V24A0* self, s32 a1, s32 a2, u32 a3, u32 a4)
{
    CountGifEntry(self, 0, 4);
    u64 lo = (u64)a1 | (u64)(a2 << 16);
    u64 mid = a3 & 0xFFFFFF;
    u64* p = self->cur64;
    self->cur64 = p + 1;
    *p = (lo | (mid << 32)) | ((u64)a4 << 56);
}

LINKER_REMNANT(func_00161950);

void Obj_161958::func_00161958(s32 count)
{
    Begin(0);
    u64* p = cursor;
    cursor = p + 2;
    p[0] = (u64)count | ((u64)2 << 58);
    p[1] = 0;
}

struct Bytes16_1619C0 { u8 b[16]; };
extern u8* D_00261990;

u8* func_001619C0(u8* self)
{
    s32 i;
    for (i = 0x93; i != -1; i--) {
    }
    func_001F5C0C(self + 0xFC, 0, 0x28);
    func_001F5C0C(self, 0, 0xB0);
    u8* camera = g_camera;
    *(s32*)(self + 0x98) = 1;
    *(f32*)(self + 0x90) = 1.0f;
    *(Bytes16_1619C0*)(self + 0x80) = *(Bytes16_1619C0*)(camera + 0x208);
    *(s32*)(self + 0xB0) = 0;
    *(s32*)(self + 0xB4) = 0;
    *(s32*)(self + 0x94) = -1;
    *(f32*)(self + 0xAC) = 1.0f;
    ResetVertexBatch(self);
    return self;
}

void func_00161A88(void* self, s32 flag)
{
    (void)self;
    if (flag & 1) {
        func_0018D778();
    }
}

void func_00161AB0(u8* self, void* a1, void* a2)
{
    FlushVertexBatch(self);
    BuildMatrixFromRotationAndTranslation(a1, a2, self);
    func_00188B48(a1, a2, self + 0x40);
}

INCLUDE_ASM(func_00161B10);

void func_00161B80(u8* self)
{
    *(s32*)(self+0xF8)=0;
    *(s32*)(self+0x124)=0;
    ((Fill_161B80)func_001F5C0C)(self+0x128,0,0x1720);
}

void func_00161BB0(Obj_00161BB0* self, s32 value)
{
    u32 local;
    FlushVertexBatch(self);
    self->f0F8 = value;
    local = 0xFFFFFFFF;
    SetVertexColor(self, &local);
}

void func_00161C00(Self_161C00* self)
{
    Hd_161C00* hd;
    f32* out1;
    V4_161C00* out2;
    u8* out3;
    s32 count;
    Packet_161C00* dst;
    s32 base;
    s32 i;
    s32 k;
    Elem_161C00* c;

    base = 0x24;
    func_001EE5C8(&g_vifPacketWriter, 0xD, 3, 0xB, 0, &hd);
    func_001F5C0C(hd, 0, 0x18);
    hd->f10 = 3;
    hd->f0 = base;
    base = self->f124 * 3 + 0x24;
    hd->f2 = base;
    WriteVifStcycl(&g_vifPacketWriter, 1, 3);
    func_001EE5C8(&g_vifPacketWriter, 8, self->f124, hd->f0, 0, &out1);
    func_001EE5C8(&g_vifPacketWriter, 0xC, self->f124, hd->f0 + 2, 0, &out2);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->f124; i++) {
        c = &self->e[i];
        out1[0] = c->f1C;
        out1[1] = c->f20;
        out1[2] = 1.0f;
        out2->v = c->v;
        out2->w = c->f24 != 0 ? self->f80 + 32768.0f : self->f80;
        out1 += 3;
        out2++;
    }
    WriteVifMscal(&g_vifPacketWriter, D_00001A50);
    WriteVifStcycl(&g_vifPacketWriter, 1, 3);
    func_001EE5C8(&g_vifPacketWriter, 0xE, self->f124, hd->f0 + 1, 0, &out3);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->f124; i++) {
        s32 j;
        c = &self->e[i];
        for (j = 0; j < 4; j++) {
            out3[j] = (self->fF8->f4[j] * c->rgba[j] + 0x100) / 0x1FE;
        }
        out3 += 4;
    }
    for (k = 0; k < self->fF8->f18; k++) {
        Pair_161C00* pair = &self->fF8->f1C[k];
        s32 frame;
        func_001EE5C8(&g_vifPacketWriter, 0xC, pair->f0, base, &count, &dst);
        frame = 0;
        if (self->fF8->f24 != 0) {
            frame = self->fF8->f24->f18;
        }
        CopyMemory(dst, pair->f4 + ((frame * pair->f0) << 4), count);
        dst->w[0] |= 0x8000 | self->f124;
        dst->w[4] |= 0x8000;
        hd->f8[k] = base;
        base += pair->f0;
    }
    WriteVifMscalf(&g_vifPacketWriter, D_000002F8);
}

void func_00161F70(Self_161F70* self)
{
    Hd_161F70* hdr;
    Out4_161F70* p4;
    Mat_161F70* p8;
    u8* pC;
    Out3_161F70* p10;
    s32 size;
    u32* dst;
    s32 off = 0x24;
    s32 j;
    s32 i;
    Vert_161F70* v;

    func_001EE5C8(&g_vifPacketWriter, 0xD, 3, 0xB, 0, &hdr);
    func_001F5C0C((Mem_161F70*)hdr, 0, 0x18);
    hdr->f10 = 4;
    hdr->f0 = off;
    off += self->n * 4;
    hdr->f2 = off;
    off += (((self->n + 3) & ~3) - self->n) * 4;
    hdr->fE = off;
    off += self->n;
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    func_001EE5C8(&g_vifPacketWriter, 0xC, self->n, hdr->f0 + 3, 0, &p4);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    for (i = 0; i < self->n; i++)
    {
        v = &self->verts[i];
        p4->v = v->pos;
        if (v->flag != 0)
            p4->w = self->base + 32768.0f;
        else
            p4->w = self->base + 28672.0f;
        p4++;
    }
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    func_001EE5C8(&g_vifPacketWriter, 0xC, (self->n + 3) & ~3, hdr->f0, 0, &p8);
    func_001EE5C8(&g_vifPacketWriter, 0xE, self->n, hdr->f0 + 1, 0, &pC);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    WriteVifMscal(&g_vifPacketWriter, D_00000288);
    for (i = 0; i < self->n; i += 4)
    {
        for (j = 0; j < 4; j++)
        {
            if (i + j < self->n)
            {
                p8->m[0][j] = self->verts[i + j].nx;
                p8->m[1][j] = self->verts[i + j].ny;
                p8->m[2][j] = self->verts[i + j].nz;
            }
            else
            {
                p8->m[0][j] = p8->m[1][j] = p8->m[2][j] = 0.0f;
            }
        }
        func_001F5C0C((Mem_161F70*)p8->m[3], 0, 0x10);
        p8++;
    }
    for (i = 0; i < self->n; i++)
    {
        v = &self->verts[i];
        for (s32 m = 0; m < 4; m++)
            pC[m] = (self->mesh->col[m] * v->col[m] + 0x100) / 0x1FE;
        pC += 4;
    }
    CloseDmaTag(&g_vifPacketWriter);
    for (s32 t = 0; t < self->texCount; t++)
        AddDmaRefTag(&g_vifPacketWriter, self->tex[t]->n, self->tex[t]->data);
    BeginDmaTag(&g_vifPacketWriter);
    WriteVifMscal(&g_vifPacketWriter, D_00001210);
    WriteVifFlushE(&g_vifPacketWriter);
    WriteVifStcycl(&g_vifPacketWriter, 1, 4);
    func_001EE5C8(&g_vifPacketWriter, 8, self->n, hdr->f0, 0, &p10);
    WriteVifStcycl(&g_vifPacketWriter, 1, 1);
    WriteVifMscal(&g_vifPacketWriter, D_00001AB0);
    for (i = 0; i < self->n; i++)
    {
        v = &self->verts[i];
        p10->x = v->u;
        p10->y = v->v;
        p10->z = 1.0f;
        p10++;
    }
    s32 k = 0;
    for (s32 t = 0; t < self->mesh->count; t++)
    {
        Ent_161F70* e = &self->mesh->ents[t];
        func_001EE5C8(&g_vifPacketWriter, 0xC, e->n, off, &size, &dst);
        Sub_161F70* sub = self->mesh->sub;
        s32 m = sub ? sub->n : 0;
        CopyMemory((Mem_161F70*)dst, e->data + m * e->n * 16, size);
        dst[0] |= 0x8000 | self->n;
        dst[4] |= 0x8000;
        hdr->f8[k] = off;
        k++;
        off += e->n;
    }
    WriteVifMscalf(&g_vifPacketWriter, D_00000010);
}

void func_00162508(Self_162508* self)
{
    if (self->f0F8 == 0) {
        return;
    }
    if (self->f124 < 3) {
        ResetVertexBatch(self);
        return;
    }
    {
        FlipVifBaseOffset();
        V24A0* s = &g_vifPacketWriter;
        s32 size = WriteVifUnpackHeader(s, 12, 11, 0);
        Copy_162508::Words((s32*)s->cur, (s32*)self, size >> 2);
        s->cur += size;
        WriteVifMscal(&g_vifPacketWriter, D_000018C0);
        switch (*self->f0F8) {
        case 1:
        case 6:
        case 7:
        case 8:
            BuildUnlitVertexPacket(self);
            break;
        case 0:
            BuildLitVertexPacket(self);
            break;
        }
    }
    ResetVertexBatch(self);
}

void func_00162680(VertexBatch* body, Vec3_162680* v)
{
    body->x = v->x;
    body->y = v->y;
    body->z = v->z;
}

LINKER_REMNANT(func_001626A0);

void func_001626A8(u8* dst, u8* src)
{
    *(U32P*)(dst + 0x114) = *(U32P*)src;
}

void func_001626C0(VertexBatch* dst, U64P* src)
{
    dst->texCoord.v = src->v;
}

void func_001626D8(Obj_1626D8* self, s32 value)
{
    s32 n;
    s64 max;

    self->cur.value = value;
    n = self->count;
    max = (*self->pF8 == 0) ? 0x50 : 0x94;
    self->recs[n] = self->cur;
    n++;
    self->count = n;
    if (n == max) {
        Rec_1626D8 tmp[2];
        u8* p = self->pF8;
        CopyMemory(tmp, &self->recs[self->count - 2], sizeof(tmp));
        FlushVertexBatch(self);
        func_00161BB0(self, p);
        CopyMemory(self->recs, tmp, sizeof(tmp));
        self->count = 2;
    }
}

void func_00162810(Owner_162810* owner)
{
    owner->refs = (void**)AllocateFrontMemory(owner->capacity << 2);
    s32 n = 0;
    for (s32 i = 0; i < owner->count; i++) {
        void* ref = owner->items[i].ref;
        if (ref != 0)
            owner->refs[n++] = ref;
    }
}

INCLUDE_RODATA(D_0024A710);
ASM_FUNC(func_00162890);

void func_00163938(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        WriteVifMscal(obj, D_000018C0);
        break;
    case 1:
        WriteVifMscal(obj, D_000018F8);
        break;
    }
}

void func_00163990(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        WriteVifMscal(obj, D_00000FA0);
        break;
    case 1:
        WriteVifMscal(obj, D_00000FD8);
        break;
    }
}

void func_001639E8(Self_1639E8* self, s32 mode, Hdr_1639E8* hdr, s32 n, Vec3_1639E8* vecs, s32 extra,
                   void* extraData, Ent_1639E8* ents, Vec3_1639E8* verts, void* data, Pkt_1639E8* pkt)
{
    V24A0 f;
    u32 buf[4];
    s32 i;
    Vec3_1639E8* out;
    s32 off = 0x2B;

    func_001EE5C8(pkt, 0xD, 2, 0x16, 0, hdr);
    func_001F5C0C(hdr->p, 0, 0x10);
    InitGifPacket(&f);
    AllocateTempPacketBuffer(&f, 8);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x42, 0x44);
    AddGifRegisterWrite(&f, 1, (u64)D_002623E0.r | ((u64)D_002623E0.g << 8) | ((u64)D_002623E0.b << 16)
                             | ((u64)D_002623E0.a << 24) | (1ULL << 32));
    CloseGifTag(&f, 1);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin, 0x18);
    RewindPacketBuffer(&f);
    BeginGifTag(&f, 0xC1, 3, 0x44E);
    AddGifRegisterWrite(&f, 0x47, 0x70000);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    CloseGifTag(&f, 0);
    BeginGifTag(&f, 1, 3, 0x44E);
    AddGifRegisterWrite(&f, 0x47, 0x72001);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    CloseGifTag(&f, 1);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin, 0x1B);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin + 0x40, 0x1F);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin, 0x23);
    CopyWordsToWriter(pkt, 0xC, 2, f.begin + 0x40, 0x27);

    hdr->p[0] = off;
    off += n;
    hdr->p[1] = off;
    CopyWordsToWriter(pkt, 8, n, vecs, hdr->p[0]);
    if (hdr->count > 0)
    {
        hdr->p[4] = off;
        off += hdr->count * 4;
        hdr->p[5] = off;
        Zero_1639E8::Clear(buf);
        off += n;
        WriteVifStrow(pkt, buf);
        WriteVifStmask(pkt, D_002623E8[hdr->count]);
        CopyWordsToWriter(pkt, D_00262400[hdr->count], n, data, hdr->p[5]);
        WriteVifStmask(pkt, 0);
    }
    s32 end = off + extra;
    if (self->f40 != 0)
    {
        hdr->p[5] = off;
        hdr->p[6] = self->f40 + off;
        for (i = 0; i < self->f40; i++)
        {
            CopyWordsToWriter(pkt, 0, 1, &i, 0x1D);
            func_001EE5C8(pkt, 8, n, hdr->p[6], 0, &out);
            u16* idx = ents[i].idx;
            for (s32 k = 0; k < n; k++)
            {
                Vec3_1639E8* v = &verts[idx[k]];
                out[k].x = v->x - vecs[k].x;
                out[k].y = v->y - vecs[k].y;
                out[k].z = v->z - vecs[k].z;
            }
            WriteVifMscal(pkt, D_00001298);
            WriteVifFlushE(pkt);
        }
    }
    hdr->p[2] = off;
    hdr->p[3] = end;
    CopyWordsToWriter(pkt, 0xE, extra, extraData, hdr->p[2]);
    func_00163990(mode, pkt);
    WriteVifMscal(pkt, D_00001368);
    WriteVifMscal(pkt, D_00000ED8);
}

void func_00163ED8(Self_163ED8* self, Obj_163ED8* obj, s32 mode, Hdr_163ED8* hdr, StripMesh* mesh,
                   Vec3_163ED8* vecs, s32 unused6, u8 (*tints)[4], Uv_163ED8* uvs, s32 n, Rec_163ED8* recs,
                   Ent_163ED8* ents, Vec3_163ED8* verts, s32 unused13, f32* weights, Pkt_163ED8* pkt,
                   s32** outs)
{
    u32 buf[4];
    f32* uvOut;
    f32* posOut;
    s32 a;
    s32 b;
    f32* wOut;
    s32 k;
    Vec3_163ED8* dOut;
    u8* cOut;
    s32 c;
    s32 d;
    s32 off;
    s32 hasUv;
    s32 tinted;
    void* tail;
    void* head;
    MeshNode* node;
    s32 i;
    Rec_163ED8* r;

    if (obj->f54 != 0) {
        BeginDmaTag(pkt);
    }
    func_001EE5C8(pkt, 0xD, 3, 0xB, 0, &hdr->p);
    off = 0x24;
    func_001F5C0C(hdr->p, 0, 0x18);
    hdr->p->f10 = 3;
    hdr->p->off[0] = off;
    off = n * 3 + 0x24;
    hdr->p->off[1] = off;
    switch (mesh->kind) {
    case 1:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        head = D_000002F8;
        tail = D_00001A50;
        tinted = 1;
        hasUv = 1;
        break;
    case 4:
        head = D_000036D0;
        tail = D_00001A80;
        hasUv = mesh->mode & 2;
        tinted = hasUv;
        break;
    case 9:
        head = D_000002F8;
        tail = D_00001A50;
        hasUv = 0;
        tinted = 1;
        break;
    }
    cOut = 0;
    uvOut = 0;
    WriteVifStcycl(pkt, 1, 3);
    if (hasUv) {
        func_001EE5C8(pkt, 8, n, hdr->p->off[0], 0, &uvOut);
    }
    func_001EE5C8(pkt, 0xC, n, hdr->p->off[0] + 2, 0, &posOut);
    WriteVifStcycl(pkt, 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    if (obj->f54 != 0) {
        Extra_163ED8* e = (Extra_163ED8*)AllocateZeroedFrontMemory(0x34);
        hdr->extra = e;
        e->f0 = (s32)posOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        if (hasUv) {
            if (r->uv == 0xFF) {
                uvOut[0] = uvOut[1] = 0.0f;
            } else {
                uvOut[0] = uvs[r->uv].u;
                uvOut[1] = uvs[r->uv].v;
            }
            uvOut[2] = 1.0f;
            uvOut += 3;
        }
        *(Vec3_163ED8*)posOut = vecs[recs[i].pos];
        if (recs[i].flags >> 7) {
            posOut[3] = obj->f40 + 32768.0f;
        } else {
            posOut[3] = obj->f40 + 28672.0f;
        }
        posOut += 4;
    }
    node = 0;
    if (obj->f38 != 0) {
        node = obj->f38->vt[5](obj->f38, mesh);
    }
    if (node == 0 && mesh->hook != 0) {
        node = ((Hook_163ED8*)mesh->hook)->vt[5]((Hook_163ED8*)mesh->hook, mesh);
    }
    func_00163938(mode, pkt);
    if (node != 0 && (node->flags & 2)) {
        func_001EE5C8(pkt, 4, 1, 0x16, &a, &b);
        QueueNodeLink(b, a, node);
        WriteVifMscal(pkt, D_000027C0);
    }
    if (hdr->count > 0) {
        hdr->p->off[2] = off;
        off += hdr->count * 4;
        hdr->p->off[3] = off;
        off += n;
        func_001F5C0C(buf, 0, 0x10);
        WriteVifStrow(pkt, buf);
        WriteVifStmask(pkt, D_00262418[hdr->count]);
        func_001EE5C8(pkt, D_00262430[hdr->count], n, hdr->p->off[3], 0, &wOut);
        WriteVifStmask(pkt, 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        WriteVifMscal(pkt, D_00002008);
    }
    if (self->f40 != 0) {
        hdr->p->off[3] = off;
        off += self->f40;
        hdr->p->strip[3] = off;
        for (k = 0; k < self->f40; k++) {
            if (k > 0) {
                WriteVifFlushE(pkt);
            }
            CopyWordsToWriter(pkt, 0, 1, &k, 0x16);
            func_001EE5C8(pkt, 8, n, hdr->p->strip[3], 0, &dOut);
            u16* idx = ents[k].idx;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3_163ED8* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            WriteVifMscal(pkt, D_000023B8);
        }
    }
    if (hdr->extra != 0) {
        Extra_163ED8* e = hdr->extra;
        for (s32 i = 0; i < obj->f54->f10; i++) {
            func_001EE5C8(pkt, 0xC, n, off, 0, &e->a24[i]);
            if (obj->f54->f18 != 0) {
                WriteVifUnpack(pkt, 0xC, 4, 0, 0x16, &e->a14[i]);
                WriteVifMscal(pkt, D_00003A80);
                WriteVifFlushE(pkt);
            }
            if (obj->f54->f14 != 0) {
                WriteVifUnpack(pkt, 0xC, 4, 0, 0x16, &e->a4[i]);
                WriteVifMscal(pkt, D_00003A90);
                WriteVifFlushE(pkt);
            }
        }
        hdr->p->off[3] = off;
        off += n;
    }
    WriteVifMscal(pkt, tail);
    if (tinted) {
        WriteVifStcycl(pkt, 1, 3);
        func_001EE5C8(pkt, 0xE, n, hdr->p->off[0] + 1, 0, &cOut);
        WriteVifStcycl(pkt, 1, 1);
        for (i = 0; i < n; i++) {
            s32 j;
            r = &recs[i];
            if ((r->flags & 0x7F) == 0x7F) {
                for (j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] + 1) >> 1;
                }
            } else {
                for (j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] * tints[r->flags & 0x7F][j] + 0x100) / 0x1FE;
                }
            }
            cOut += 4;
        }
    }
    for (s32 i = 0; i < mesh->nstrips; i++) {
        MeshStrip* s = &mesh->strips[i];
        func_001EE5C8(pkt, 0xC, s->count, off, &c, &d);
        QueueMeshStrip(mesh, s, d, c, n, node);
        hdr->p->strip[i] = off;
        off += s->count;
    }
    WriteVifMscalf(pkt, head);
    if (obj->f54 != 0) {
        CloseDmaTag(pkt);
        AddDmaReturnTag(pkt);
    }
}

void func_00164868(Self_164868* self, Obj_164868* obj, s32 unused2, s32 mode, Hdr_164868* hdr,
                   StripMesh* mesh, Vec3_164868* vecs, Vec3_164868* nrms, u8 (*tints)[4], Uv_164868* uvs,
                   s32 n, Rec_164868* recs, Ent_164868* ents, Vec3_164868* verts, Vec3_164868* vnrms,
                   f32* weights, Pkt_164868* pkt, s32** outs)
{
    u32 buf[4];
    f32* posOut;
    f32* wOut;
    s32 k;
    Vec3_164868* dOut;
    Quad_164868* quads;
    f32* nOut;
    u8* cOut;
    Vec3_164868* nDelta;
    f32* uvOut;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 off;
    MeshNode* node;
    s32 i;
    Rec_164868* r;

    if (obj->f54 != 0) {
        BeginDmaTag(&pkt[2]);
    }
    obj->f18 = 1;
    func_001EE5C8(&pkt[0], 0xD, 3, 0xB, 0, &hdr->p);
    off = 0x24;
    func_001F5C0C(hdr->p, 0, 0x18);
    hdr->p->f10 = 4;
    hdr->p->f12 = hdr->f14 * 0x7FA6 / 0xFF;
    hdr->p->off[0] = off;
    off = n * 4 + 0x24;
    hdr->p->off[1] = off;
    if (hdr->count != 0 || self->f40 != 0) {
        obj->f28 = 1;
    }
    if (obj->f28 != 0) {
        off += (((n + 3) & ~3) - n) * 4;
    }
    hdr->p->strip[3] = off;
    off += n;
    WriteVifStcycl(&pkt[0], 1, 4);
    func_001EE5C8(&pkt[0], 0xC, n, hdr->p->off[0] + 3, 0, &posOut);
    WriteVifStcycl(&pkt[0], 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (obj->f54 != 0) {
        Extra_164868* e = (Extra_164868*)AllocateZeroedFrontMemory(0x34);
        hdr->extra = e;
        e->f0 = (s32)posOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        *(Vec3_164868*)posOut = vecs[r->pos];
        if (r->flags >> 7) {
            posOut[3] = obj->f40 + 32768.0f;
        } else {
            posOut[3] = obj->f40 + 28672.0f;
        }
        posOut += 4;
    }
    func_00163938(mode, &pkt[0]);
    if (hdr->count > 0) {
        hdr->p->off[2] = off;
        off += hdr->count * 4;
        hdr->p->off[3] = off;
        off += n;
        func_001F5C0C(buf, 0, 0x10);
        WriteVifStrow(&pkt[0], buf);
        WriteVifStmask(&pkt[0], D_00262448[hdr->count]);
        func_001EE5C8(&pkt[0], D_00262460[hdr->count], n, hdr->p->off[3], 0, &wOut);
        WriteVifStmask(&pkt[0], 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        WriteVifMscal(&pkt[0], D_00002008);
    }
    if (self->f40 != 0) {
        hdr->p->off[3] = off;
        off += self->f40;
        for (k = 0; k < self->f40; k++) {
            CopyWordsToWriter(&pkt[0], 0, 1, &k, 0x16);
            func_001EE5C8(&pkt[0], 8, n, hdr->p->strip[3], 0, &dOut);
            u16* idx = ents[k].pos;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3_164868* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            WriteVifMscal(&pkt[0], D_000023B8);
            WriteVifFlushE(&pkt[0]);
        }
    }
    WriteVifStcycl(&pkt[1], 1, 4);
    if (obj->f28 != 0 && hdr->count == 0 && self->f40 == 0) {
        func_001EE5C8(&pkt[1], 0xC, (n + 3) & ~3, hdr->p->off[0], 0, &quads);
        nOut = 0;
    } else {
        func_001EE5C8(&pkt[1], 0xC, n, hdr->p->off[0], 0, &nOut);
        quads = 0;
    }
    func_001EE5C8(&pkt[1], 0xE, n, hdr->p->off[0] + 1, 0, &cOut);
    WriteVifStcycl(&pkt[1], 1, 1);
    if (hdr->count > 0) {
        WriteVifMscal(&pkt[1], D_00002088);
    }
    if (self->f40 > 0) {
        for (s32 m = 0; m < self->f40; m++) {
            if (m > 0) {
                WriteVifFlushE(&pkt[1]);
            }
            func_001EE5C8(&pkt[1], 8, n, hdr->p->strip[3], 0, &nDelta);
            u16* idx = ents[m].nrm;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3_164868* v = &vnrms[idx[i]];
                nDelta[i].x = v->x - nrms[r->nrm].x;
                nDelta[i].y = v->y - nrms[r->nrm].y;
                nDelta[i].z = v->z - nrms[r->nrm].z;
            }
            WriteVifMscal(&pkt[1], D_000023D8);
        }
        WriteVifMscal(&pkt[1], D_000023F0);
    }
    WriteVifMscal(&pkt[1], D_00000288);
    for (i = 0; i < n; i++) {
        s32 j;
        r = &recs[i];
        if ((r->flags & 0x7F) == 0x7F) {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] + 1) >> 1;
            }
        } else {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] * tints[r->flags & 0x7F][j] + 0x100) / 0x1FE;
            }
        }
        if (nOut != 0) {
            if (r->nrm == 0xFF) {
                nOut[0] = nOut[1] = nOut[2] = 0.0f;
            } else {
                *(Vec3_164868*)nOut = nrms[r->nrm];
            }
            nOut[3] = (cOut[0] + cOut[1] + cOut[2]) * 0.33333334f;
            nOut += 4;
        }
        cOut += 4;
    }
    if (quads != 0) {
        for (i = 0; i < n; i += 4) {
            for (s32 j = 0; j < 4; j++) {
                if (i + j < n) {
                    quads->x[j] = nrms[recs[i + j].nrm].x;
                    quads->y[j] = nrms[recs[i + j].nrm].y;
                    quads->z[j] = nrms[recs[i + j].nrm].z;
                } else {
                    quads->x[j] = quads->y[j] = quads->z[j] = 0.0f;
                }
            }
            func_001F5C0C(quads->w, 0, 0x10);
            quads++;
        }
    }
    WriteVifStcycl(&pkt[2], 1, 4);
    func_001EE5C8(&pkt[2], 8, n, hdr->p->off[0], 0, &uvOut);
    WriteVifStcycl(&pkt[2], 1, 1);
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        if (r->uv == 0xFF) {
            uvOut[0] = uvOut[1] = 0.0f;
        } else {
            uvOut[0] = uvs[r->uv].u;
            uvOut[1] = uvs[r->uv].v;
        }
        uvOut[2] = 1.0f;
        uvOut += 3;
    }
    node = 0;
    if (obj->f38 != 0) {
        node = obj->f38->vt[5](obj->f38, mesh);
    }
    if (node == 0 && mesh->hook != 0) {
        node = ((Hook_164868*)mesh->hook)->vt[5]((Hook_164868*)mesh->hook, mesh);
    }
    if (node != 0 && (node->flags & 2)) {
        func_001EE5C8(&pkt[2], 4, 1, 0x16, &a, &b);
        QueueNodeLink(b, a, node);
        WriteVifMscal(&pkt[2], D_000027C0);
    }
    if (hdr->extra != 0) {
        Extra_164868* e = hdr->extra;
        for (s32 i = 0; i < obj->f54->f10; i++) {
            func_001EE5C8(&pkt[2], 0xC, n, off, 0, &e->a24[i]);
            if (obj->f54->f18 != 0) {
                WriteVifUnpack(&pkt[2], 0xC, 4, 0, 0x16, &e->a14[i]);
                WriteVifMscal(&pkt[2], D_00003A80);
                WriteVifFlushE(&pkt[2]);
            }
            if (obj->f54->f14 != 0) {
                WriteVifUnpack(&pkt[2], 0xC, 4, 0, 0x16, &e->a4[i]);
                WriteVifMscal(&pkt[2], D_00003AA0);
                WriteVifFlushE(&pkt[2]);
            }
        }
        hdr->p->off[3] = off;
        off += n;
    }
    WriteVifMscal(&pkt[2], D_00001AB0);
    s32 slot = 0;
    for (s32 i = 0; i < mesh->nstrips; i++) {
        MeshStrip* s = &mesh->strips[i];
        func_001EE5C8(&pkt[2], 0xC, s->count, off, &c, &d);
        QueueMeshStrip(mesh, s, d, c, n, node);
        hdr->p->strip[slot++] = off;
        off += s->count;
    }
    if (obj->f54 != 0) {
        CloseDmaTag(&pkt[2]);
        AddDmaReturnTag(&pkt[2]);
    }
}

void func_00165588(Ctx_165588* a, Rec_165588* b, Out_165588* c)
{
    u8 buf[0x30];
    s32 s0;

    if (*b->f18 != 0) return;
    if (a->f28 != 0) return;
    InitPacketWriter(buf);
    s0 = (b->f1C->hi - b->f1C->lo) / 4;
    AllocateQuadwordBuffer(buf, (u32)((s0 + 7) / 4), 0x1A);
    WriteVifStcycl(buf, 1, 4);
    func_001EE5C8(buf, 0xE, s0, b->f1C->lo + 1, 0, &c->f8);
    WriteVifStcycl(buf, 1, 1);
    WriteVifMscal(buf, D_00000010);
    DetachPacketBuffer(buf, &c->f0, &c->f4);
    AllocateQuadwordBuffer(buf, (u32)((s0 + 4) / 2), 0x1A);
    WriteVifStcycl(buf, 1, 4);
    func_001EE5C8(buf, 0xE, s0, b->f1C->lo + 2, 0, &c->f14);
    WriteVifStcycl(buf, 1, 1);
    func_001EE5C8(buf, 0xE, s0, b->f1C->hi, 0, 0);
    WriteVifMscal(buf, D_000000F0);
    DetachPacketBuffer(buf, &c->fC, &c->f10);
}

void func_00165728(Self_165728* self, PlacedObject* ctx)
{
    for (s32 i = 0; i < self->count0C; i++)
    {
        Entry_165728* e = self->f10 + i;
        Obj_165728* o = e->f38;
        if (o != 0)
        {
            o->vtbl[1](o);
        }
        func_001662A8(self, e, self->f14 + i * 0x28, ctx);
    }
    Node_165728* n = self->f4C;
    if (n != 0)
    {
        do
        {
            void* v = FindFirstObjectById(ctx->world, 0x104, n->f8, ctx);
            if (v != 0)
            {
                AttachNodeToOwner(v, ctx, n->f4);
            }
            n = n->next80;
        } while (n != 0);
    }
}

void func_00165828(Obj_165828* self, PlacedObject* ctx)
{
    Frame_165828 f;
    s32 i;

    for (i = 0; i < self->count; i++) {
        Elem_165828* e = &self->elems[i];
        Node_165828* r = (Node_165828*)func_0015A448(ctx->world, self->keys[i], ctx);
        e->p0 = r;
        if (r != 0) {
            BuildMatrixFromRotationAndTranslation(&ctx->v140, &ctx->m110, &f.a);
            func_00188B48(&e->p0->sub140, &e->p0->sub110, &f.b);
            func_00188668(&f.m, &f.b, &f.a);
            e->m = f.m;
        }
    }
}

void func_00165920(Obj_165920* self, s32 arg, void* src)
{
    s32 i = 0;
    Node_165920** link;
    CopyMemory(self, src, 0x58);
    self->f50 = 0;
    self->p4 = AllocateZeroedFrontMemory(self->n0 * 0x90);
    self->p44 = CopyToFrontMemory(self->n40 << 2, self->p44);
    self->p14 = CopyToFrontMemory(self->count * 0x28, self->p14);
    Rec_165920* old = self->recs;
    for (; i < self->count; i++) {
        Rec_165920* r = (Rec_165920*)((u8*)self->recs + i * 0x70);
        if ((r->a && (r->a->flags & 4)) || r->b) {
            self->recs = (Rec_165920*)CopyToFrontMemory(self->count * 0x70, self->recs);
            break;
        }
    }
    link = &self->head;
    Node_165920* s = self->head;
    if (s) {
        do {
            Node_165920* n = (Node_165920*)CopyToFrontMemory(0x90, s);
            n->tag = arg;
            Node_165920** pf = &n->p4;
            u32 sz = self->count * 0x70;
            u32 nb = (u32)self->recs;
            if (pf) {
                u32 v = (u32)n->p4;
                if (!(v < (u32)old) && v < (u32)old + sz)
                    n->p4 = (Node_165920*)(v + (nb - (u32)old));
            }
            ((Rec_165920*)n->p4)->b = n;
            *link = n;
            link = &n->next;
            s = n->next;
        } while (s);
    }
    *link = 0;
    i = 0;
    if (self->count > 0) {
        s32 b = 0, a = 0;
        do {
            i++;
            func_00165AE8(self, (u8*)self->recs + a, (u8*)self->p14 + b);
            a += 0x70;
            b += 0x28;
        } while (i < self->count);
    }
    CollectNonNullRefs(self);
}

INCLUDE_ASM(func_00165AE8);

void func_00165FE0(Owner_165FE0* self, PlacedObject* sub, f32 f)
{
    Elem_165FE0* e;
    s32 i;

    for (i = 0; i < sub->elemCount; i++) {
        e = ((Elem_165FE0**)sub->elems)[i];
        if (ClaimAnimatorStep(e) != 0) {
            VFn_165FE0 fn = e->vtbl[2];
            if (fn != 0) {
                fn(e, f);
            }
        }
    }
    for (e = self->head4C; e != 0; e = e->next80) {
        func_001F3408(e->f0C);
    }
}

void func_001660A0(PlacedObject* self)
{
    u8* p=(u8*)self->f224;
    if (p && (*(s32*)(p+0xB0)&16) && *(s32*)(p+0x64)) func_0016C528(*(void**)(p+0x60));
}

void func_001660E8(PlacedObject* self, Par_1660E8* par)
{
    Mat_1660E8 a;
    Mat_1660E8 b;
    Mat_1660E8 c;
    Mat_1660E8 e;
    s32 i;
    List_1660E8* l = (List_1660E8*)self->sub22C;

    if (l->count > 0) {
        func_00188B48(&self->v140, &self->m110, &a);
        if (par != 0) {
            func_00188B48((u8*)par + 0x30, par, &b);
        } else {
            b = a;
        }
        for (i = 0; i < l->count; i++) {
            Elem_1660E8* el = (Elem_1660E8*)((u8*)l->items + (i << 4) * 9);
            if (el->obj != 0) {
                el->obj->vt->f(el->obj);
                Link_1660E8* t = el->obj->link;
                if (t != 0 && (t->flags & 0x80) && t->a4 != 0) {
                    c = t->m60;
                    e = func_00188668(b, &c);
                } else {
                    BuildMatrixFromRotationAndTranslation(el->obj->sub140, el->obj->sub110, &c);
                    e = func_00188668(a, &c);
                }
                el->m50 = func_00188668(e, &el->q10);
            }
        }
    }
}

INCLUDE_ASM(func_001662A8);

void func_00166658(void)
{
    s32 v = 0x23C - D_00262474;
    D_00262474 = v;
    WriteVifBaseOffset(&g_vifPacketWriter, v, 0);
}

INCLUDE_RODATA(jtbl_0024A750);
INCLUDE_RODATA(jtbl_0024A780);
INCLUDE_ASM(func_00166690);

