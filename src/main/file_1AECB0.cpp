// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"

#include "list_iter.h"


struct Queue_1AF078 {
    u8 pad_0[0x5A0];
    u32 count;
    u32 items[4];
};



struct Obj_001AECE0 {
    u8 pad0[0x550];
    s32 f550;
};



struct Node_129CA8 {
    u8 pad0[0x18];
    union {
        s32 w;
        f32 f;
    } f18;
};

struct Obj_001AEF68 {
    u8 pad0[0x5c8];
    Node_129CA8* f5c8;
    f32 f5cc;
};

Node_129CA8* func_00129CA8(Obj_001AEF68* self);



struct Sink_001AEFA0 { u8 pad0[0x18]; f32 value; };
struct Mixer_001AEFA0 { u8 pad0[0x5C8]; Sink_001AEFA0* sink; f32 pending; };
struct Global_001AEFA0 { u8 pad0[0x2220]; s32 state; };

struct Dev_001B0578;
extern Dev_001B0578* D_00262E10;

void func_001B93F8(Mixer_001AEFA0* self);



struct Stack_001AF000 { u8 pad0[0x564]; u32 count; s32 items[4]; };



struct Queue_1AF028 { u8 pad[0x578]; s32 count; void* items[4]; };



struct Queue_1AF050 { u8 pad[0x58C]; s32 count; void* items[4]; };



struct Unit_1AF0A0 { u8 pad[0xB04]; f32 scale; };

void func_001AECB0(void* self);



struct Entry_2744B8 { s32 a; s32 b; s32 c; };
Entry_2744B8 D_002744B8[2] = { { 2, 0x28A, 0xAE4 }, { 2, 0x28B, 0xAE8 } };

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* table);



struct Obj_1AEE50 { u8 pad0[0x578]; s32 count578; s32 items57C[9]; s32 count5A0; s32 items5A4[9]; };

s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 item);



extern u8* D_00275710;
extern f32 D_00261858[];
s32 D_002744D0 = 0;

struct Node_1AF508 {
    u8 pad0[0x558];
    s32 x558;
    u8 pad1[0xAF0 - 0x55C];
    Node_1AF508* next;
    u8 pad2[0xAFC - 0xAF4];
    f32 fAFC;
};



extern s32 D_002744D0;
void func_0015FCD8(void* self, void* p);
void func_00152470(void* list, void* item);
void func_00152600(void* list, void* item);

struct Obj_1AF7A8 {
    u8 pad0[0x14];
    u8* p14;
    u8 pad1[0xAF8 - 0x18];
    s32 flag_AF8;
};



struct Obj_001AED78 {
    u8 pad0[0x564];
    s32 f564;
    s32 f568[9];
    s32 f58c;
    s32 f590[9];
    s32 f5b4;
};

s32 func_001AEE50(Obj_001AED78* self, s32 value);
s32 func_001833F0(s32 value, s32 item);
s32 func_001300E8(s32 value, s32 item);



struct Obj_1AEF00 {
    u8 pad_0[0x564];
    s32 f564;
    s32 f568;
    u8 pad_56C[0x58C - 0x56C];
    s32 f58C;
    u8 pad_590[0x5B4 - 0x590];
    s32 f5B4;
};

s32 func_001833F0(void* a, s32 b);



typedef void (*VFn_1AF3B8)(void* self);

struct Child_1AF3B8 { VFn_1AF3B8* vtbl; };

struct Entry_1AF3B8 { void* obj; s32 value; };

struct Group_1AF3B8 {
    Child_1AF3B8* child;
    u8 pad0[0x24 - 4];
    s32 count;
    Entry_1AF3B8 items[5];
};

struct Obj_1AF3B8 {
    VFn_1AF3B8* vtbl;
    u8 pad0[0x14 - 4];
    void* f14;
    u8 pad1[0x560 - 0x18];
    void* f560;
    u8 pad2[0x5D4 - 0x564];
    s32 groupCount;
    u8 pad3[0x5E0 - 0x5D8];
    Group_1AF3B8 groups[1];
    u8 pad4[0xB00 - 0x630];
    s32 f_B00;
};

void func_00124A48(void* self);
void* func_00183058(void* a, void* b, void* c);



s32 func_001AEE50(void* self, void* key);
s32 func_00160D10();
struct Obj_1AFAF8 {
    u8 pad0[0x50];
    s32 x50;
    u8 pad1[0x2CC - 0x54];
    u32 x2CC;
    u8 pad2[0x538 - 0x2D0];
    u64 f538;
    u8 pad3[0x2220 - 0x540];
    s32 x2220;
    u8 pad4[0x239C - 0x2224];
    s32 x239C;
};


struct Obj_1AECB0 {
    u8 pad_00[0x554];
    s32 f554;
    s32 f558;
};

void func_001B7968(Obj_1AECB0* self);



struct Mixer_001AF5C8;
struct MixVt_001AF5C8 {
    u8 pad0[0x130];
    void (*hook)(Mixer_001AF5C8*, s32*);
    u8 pad1[0x144 - 0x134];
    void (*done)(Mixer_001AF5C8*, s32);
};
struct Mixer_001AF5C8 {
    MixVt_001AF5C8* vt;
    u8 pad4[0x554 - 4];
    s32 f554;
    s32 state;
    f32 f55C;
    u8 pad560[0x5B8 - 0x560];
    f32 f5B8;
    f32 f5BC;
    u8 pad5C0[0xAEC - 0x5C0];
    f32 fAEC;
    u8 padAF0[0xB04 - 0xAF0];
    f32 fB04;
    f32 fB08;
};

extern s32 D_002744D0;
extern f32 D_0026185C[];
void func_001AEFA0(Mixer_001AF5C8* self, f32 a);
void func_001AF508();



struct Sub_1AECE8;
struct Obj_1AECE8 { u8 pad[0x550]; Sub_1AECE8* f550; u8 pad2[4]; s32 state; f32 f55C; };
void func_00123AB0(Sub_1AECE8* object, s32 mode);
void func_001837E0(Obj_1AECE8* self, s32 a, s32 b, s32 c);
extern f32 D_0026185C[];

struct Obj_1B04A0 {
    u8 pad_0[0x5D8];
    s32 f5D8;
};

void func_001AECB0(Obj_1B04A0* o);



typedef void (*VFn_1B0F70)(void* self, s32 arg);

struct Obj_1B0F70 {
    VFn_1B0F70* vtbl;
    u8 pad_4[0x554 - 4];
    s32 f554;
    s32 f558;
};



void func_00124A48(void* self);

typedef void (*VFn_1B11A0)(void* self, s32 arg);

struct Vtbl_1B11A0 {
    u8 pad0[0x144];
    VFn_1B11A0 fn144;
};

struct Item_1B11A0 {
    u8 pad0[0x8];
    s32 f08;
    u8 pad1[0x14 - 0xC];
    s32 f14;
};

struct Obj_1B11A0 {
    Vtbl_1B11A0* vt;
    u8 pad0[0x278];
    s32 f27C;
    Item_1B11A0** f280;
    u8 pad1[0x560 - 0x284];
    s32 f560;
    u8 pad2[0x610 - 0x564];
    Item_1B11A0* f610;
};



typedef void (*VFn_1B15D0)(void* self, s32 arg);

struct Vtbl_1B15D0 {
    u8 pad0[0x144];
    VFn_1B15D0 fn144;
};

struct Obj_1B15D0 {
    Vtbl_1B15D0* vt;
    u8 pad0[0x554 - 0x4];
    s32 f554;
};



extern f32 D_0026185C[];

typedef void (*VFn_1B1608)(void* self, s32 arg);

struct Vtbl_1B1608 {
    u8 pad0[0x144];
    VFn_1B1608 fn144;
};

struct Rec_1B1608 {
    u8 pad0[0x550];
    s32 f550;
    f32 f554;
};

struct Obj_1B1608 {
    Vtbl_1B1608* vt;
    u8 pad0[0x550 - 0x4];
    Rec_1B1608* f550;
    s32 f554;
    s32 f558;
    u8 pad1[0x5C0 - 0x55C];
    s32 f5C0;
};



typedef void (*VFn_1B00E8)(void* self, s32 arg);

struct Obj_1B00E8 { VFn_1B00E8* vtbl; u8 pad_4[0x554 - 4]; s32 f554; s32 f558; };



struct Obj_1B1158 {
    u8 pad_0[0x5D0];
    s32 f5D0;
    s32 f5D4;
    u8 pad_5D8[0x5E0 - 0x5D8];
    s32 f5E0;
    s32 f5E4;
    u8 pad_5E8[0x5F0 - 0x5E8];
    s32 f5F0;
    s32 f5F4;
    u8 pad_5F8[0x600 - 0x5F8];
    s32 f600;
};

void func_001AECB0(void* self);



typedef void (*VFn_1B0160)(void* self, s32 arg);

struct Obj_1B0160 {
    VFn_1B0160* vtbl;
    u8 pad_4[0x554 - 4];
    s32 f554;
    s32 f558;
};



struct Obj_1B0470 {
    u8 pad_0[0xB08];
    f32 fB08;
};



struct S_1B0488 { u8 pad[0xB08]; f32 value; };




typedef void (*VFn_1B0EA8)(void* self, s32 arg);

struct Obj_1B0EA8 {
    VFn_1B0EA8* vtbl;
    u8 pad_4[0x554 - 4];
    s32 f554;
};



struct Item_2744D8 { u32 flags, id, off8; };
Item_2744D8 D_002744D8[2] = {
    { 2, 0x28C, 0x5D0 },
    { 2, 0x28D, 0x5D4 },
};
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

typedef void (*VFn_1B04D0)(void* self, s32 v);

struct Sub_1B04D0 {
    u8 pad0[0x44];
    s32 x44;
};

struct Obj_1B04D0 {
    VFn_1B04D0* vtbl;
    u8 pad0[0x14 - 4];
    u8* p14;
    u8 pad1[0x200 - 0x18];
    Sub_1B04D0* p200;
    u8 pad2[0x538 - 0x204];
    u64 f538;
    u8 pad3[0x560 - 0x540];
    s32 x560;
    u8 pad4[0x5D0 - 0x564];
    Obj_1B04D0* x5D0;
    s32 x5D4;
};



typedef void (*VFn_1B0EE0)(void* self, s32 arg);

struct Vtbl_1B0EE0 {
    u8 pad0[0x144];
    VFn_1B0EE0 fn144;
};

struct Rec_1B0EE0 {
    u8 pad0[0x550];
    s32 f550;
    f32 f554;
};

struct Obj_1B0EE0 {
    Vtbl_1B0EE0* vt;
    u8 pad0[0x550 - 0x4];
    Rec_1B0EE0* f550;
    s32 f554;
    s32 f558;
    u8 pad1[0x5C0 - 0x55C];
    s32 f5C0;
};

extern f32 D_0026185C[];



typedef void (*VFn_1B0120)(void* self, s32 arg);

struct Obj_1B0120 { VFn_1B0120* vtbl; u8 pad_4[0x554 - 4]; s32 f554; s32 f558; };



struct Obj_1B0BE0 {
    u8 pad_0[0x50];
    s32 f50;
    u8 pad_54[0x2CC - 0x54];
    u32 f2CC;
    u8 pad_2D0[0x538 - 0x2D0];
    u64 f538;
};

s32 func_001925F0(void);
s32 func_001AEE50(void* self, void* other);



// Matched by a switch on f558 (cases 1 and 5).

typedef void (*VFn_1B1698)(void* self, s32 arg);

struct Vtbl_1B1698 {
    u8 pad0[0x144];
    VFn_1B1698 fn144;
};

struct Obj_1B1698 {
    Vtbl_1B1698* vt;
    u8 pad0[0x554 - 0x4];
    s32 f554;
    s32 f558;
    u8 pad1[0x608 - 0x55C];
    f32 f608;
    u8 pad2[0x618 - 0x60C];
    s32 f618;
};



struct Ent_1B01B0 {
    u8 pad0[0x24];
    s32 count;
    s32 e[1][2];
};
struct Obj_1B01B0;
struct VT_1B01B0 {
    void* pad[7];
    void (*slot1C)(Obj_1B01B0*);
};
struct Obj_1B01B0 {
    VT_1B01B0* vt;
    u8 pad4[0x550];
    s32 f554;
    s32 state;
};

extern s32 D_002744D0;
s32 func_001BFCD8(Obj_1B01B0* a0, s32 a1, Obj_1B01B0* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BF788(s32 a, s32 n);
void func_001AECE8(Obj_1B01B0* self, s32 s);
void func_00155F90(s32 p);



struct Self_1B0FC0 {
    u8 pad0[0x558];
    s32 state;
    u8 pad55C[0x5C0 - 0x55C];
    s32 f5C0;
};
void func_001B1070(Self_1B0FC0* self, s32 v);
void func_001AECE8(Self_1B0FC0* self, s32 s);



struct Obj_1B1710 {
    u8 pad0[0x558];
    s32 state;
    f32 f55C;
    u8 pad1[0x5C0 - 0x560];
    s32 f5C0;
    void* f5C4;
    u8 pad2[0x614 - 0x5C8];
    f32 f614;
    s32 f618;
};

struct Tgt_1B1710;
void func_001BF788(Tgt_1B1710* t, s32 n);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001AECE8(Obj_1B1710* self, s32 n);



struct Obj_001B0578;
struct VT_001B0578 {
    u8 pad0[0x130];
    void (*f130)(Obj_001B0578* self, s32* st);
    u8 pad1[0x10];
    void (*f144)(Obj_001B0578* self, s32 st);
};
struct Obj_001B0578 {
    VT_001B0578* vt;
    u8 pad0[0x550];
    s32 i554; s32 i558; f32 f55C; u8 pad1[0x58];
    f32 f5B8, f5BC; s32 i5C0; u8 pad2[0x10];
    s32 i5D4, i5D8; f32 f5DC, f5E0, f5E4, f5E8;
};
struct Dev_001B0578;
struct DevVT_001B0578 {
    u8 pad[0x13C];
    s32 (*f13C)(Dev_001B0578* d, s32 n);
    s32 (*f140)(Dev_001B0578* d, void* b);
};
struct Dev_001B0578 { DevVT_001B0578* vt; };
extern f32 D_0026185C[];

void func_001AEFA0(Obj_001B0578* self);
void func_001AEF68(Obj_001B0578* self);
void func_001B1070(Obj_001B0578* self, s32 n);
void func_001D7098(void* buf, s32 n, Obj_001B0578* self);



struct Obj_1B1238;
struct VT_1B1238 {
    u8 pad0[0x130];
    void (*f130)(Obj_1B1238* self, s32* state);
    u8 pad1[0x144 - 0x134];
    void (*f144)(Obj_1B1238* self, s32 state);
};
struct Obj_1B1238 {
    VT_1B1238* vt;
    u8 pad0[0x554 - 4];
    s32 f554;
    s32 f558;
    f32 f55c;
    u8 pad1[0x5B8 - 0x560];
    f32 f5b8;
    f32 f5bc;
    s32 f5c0;
    u8 pad2[0x608 - 0x5C4];
    f32 f608;
    f32 f60c;
};

extern f32 D_0026185C[];
void func_001AEFA0(Obj_1B1238* self);
void func_001B1898(Obj_1B1238* self);



// NEAR: float regs: case 0 wants t=$f4 zero=$f2 m=$f3; ours t=$f3 zero=$f4 m=$f2 (8 lines differ); delay-slot load of m fixed via local m

struct Cfg_1B0360 {
    f32 pad0;
    f32 f4;
    f32 f8;
};

struct Obj_1B0360 {
    u8 pad0[0x554];
    s32 i554;
    s32 mode;
    f32 f55C;
    u8 pad560[0x5B8 - 0x560];
    f32 f5B8;
    f32 f5BC;
    u8 pad5C0[0xAEC - 0x5C0];
    f32 fAEC;
    u8 padAF0[0xB04 - 0xAF0];
    f32 fB04;
};

extern f32 D_0026185C[];



struct Anim_001B1898 {
    s32 first;
    s32 last;
    f32 duration;
    s32 mode;
};

struct Obj_001B1898 {
    u8 pad0[0x558];
    s32 state;
    f32 startTime;
    u8 pad560[0x5D0 - 0x560];
    Anim_001B1898 animB;
    Anim_001B1898 animC;
    Anim_001B1898 animA;
    s32 blinkFrame;
    f32 blinkRate;
    u8 pad608[0x610 - 0x608];
    s32 target;
    f32 blinkStart;
};

extern f32 D_0026185C[];
void func_001B46E0(s32 a, s32 frame);



struct Node_1B1070 {
    u8 pad0[0x44];
    s32 f44;
};

struct Snd_1B1070;
enum Kind_1B1070 { KIND_1B1070_1B = 0x1B };

struct Obj_1B1070 {
    u8 pad0[0x200];
    Node_1B1070* f200;
    u8 pad1[0x5C4 - 0x204];
    Snd_1B1070* f5C4;
    u8 pad2[0x5D8 - 0x5C8];
    s32 f5D8;
    f32 f5DC;
};

struct Clk_1B1070 { f32 t; };

void func_001BF788(Snd_1B1070* p, s32 n);
void func_001BFCD8(Kind_1B1070 a0, Snd_1B1070** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001AECB0(Obj_1AECB0* a0);
void func_001AECE0(Obj_001AECE0* self, s32 value);
void func_001AECE8(Obj_1AECE8* self, s32 state);
s32 func_001AED78(Obj_001AED78* self, s32 value);
s32 func_001AEE50(Obj_1AEE50* self, void* key);
s32 func_001AEF00(Obj_1AEF00* o, void* p);
void func_001AEF68(Obj_001AEF68* self);
void func_001AEFA0(Mixer_001AEFA0* self);
void func_001AF000(Stack_001AF000* self, s32 value);
void func_001AF028(Queue_1AF028* self, void* item);
void func_001AF050(Queue_1AF050* self, void* item);
void func_001AF078(Queue_1AF078* q, u32 value);
void func_001AF0A0(Unit_1AF0A0* self);
void func_001AF0D0(void* self);
void func_001AF3B8(Obj_1AF3B8* self);
void func_001AF508();
void func_001AF5C8(Mixer_001AF5C8* self, f32 amount);
void func_001AF7A8(Obj_1AF7A8* self, void* p);
s32 func_001AFAF8(Obj_1AFAF8* a0, Obj_1AFAF8* a1);
void func_001B00E8(Obj_1B00E8* self, s32 flag);
void func_001B0120(Obj_1B0120* self);
void func_001B0160(Obj_1B0160* self);
void func_001B01B0(Obj_1B01B0* self, s32 s);
f32 func_001B0360(Obj_1B0360* o, Cfg_1B0360* c);
void func_001B0470(Obj_1B0470* self, f32 x);
void func_001B0488(S_1B0488* p, f32 x);
void func_001B04A0(Obj_1B04A0* o);
void func_001B04D0(Obj_1B04D0* self);
void func_001B0578(Obj_001B0578* self);
s32 func_001B0BD8();
s32 func_001B0BE0(Obj_1B0BE0* self, Obj_1B0BE0* other);
void func_001B0EA8(Obj_1B0EA8* self, s32 value);
void func_001B0EE0(Obj_1B0EE0* self);
void func_001B0F70(Obj_1B0F70* o);
void func_001B0FC0(Self_1B0FC0* self, s32 s);
void func_001B1070(Obj_1B1070* self, s32 arg);
void func_001B1158(Obj_1B1158* self);
void func_001B11A0(Obj_1B11A0* self);
void func_001B1238(Obj_1B1238* self);
void func_001B15D0(Obj_1B15D0* self, s32 mode);
void func_001B1608(Obj_1B1608* self);
void func_001B1698(Obj_1B1698* self);
void func_001B1710(Obj_1B1710* self, s32 n);
void func_001B1898(Obj_001B1898* self);

void func_001AECB0(Obj_1AECB0* a0) {
    func_001B7968(a0);
    a0->f554 = 0;
    a0->f558 = -1;
}

void func_001AECE0(Obj_001AECE0* self, s32 value)
{
    self->f550 = value;
}

void func_001AECE8(Obj_1AECE8* self, s32 state)
{
    if (self->state == state) return;
    if (self->state == 1 && state == 2) {
        if (self->f550 != 0) {
            func_00123AB0(self->f550, 0);
            if (self->state != 1) state = self->state;
        }
        func_001837E0(self, 2, 0, 0);
    }
    self->state = state;
    self->f55C = D_0026185C[0];
}

s32 func_001AED78(Obj_001AED78* self, s32 value)
{

    if (self->f5b4 != 0) {
        return 1;
    }
    if (func_001AEE50(self, value) != 0) {
        return 0;
    }
    for (s32 i = 0; i < self->f564; i++) {
        if (func_001833F0(value, self->f568[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->f58c; i++) {
        if (func_001300E8(value, self->f590[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_001AEE50(Obj_1AEE50* self, void* key)
{
    for (s32 i = 0; i < self->count578; i++) {
        if (func_001833F0(key, self->items57C[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->count5A0; i++) {
        if (func_001300E8(key, self->items5A4[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_001AEF00(Obj_1AEF00* o, void* p)
{
    if (p == 0) return 0;
    if (o->f5B4 == 0 && o->f564 == 1 && o->f58C == 0 && func_001833F0(p, o->f568) != 0) return 1;
    return 0;
}

void func_001AEF68(Obj_001AEF68* self)
{
    Node_129CA8* node = func_00129CA8(self);

    if (node != 0) {
        self->f5cc = node->f18.f;
        node->f18.w = 0;
        self->f5c8 = node;
    }
}

void func_001AEFA0(Mixer_001AEFA0* self)
{
    func_001B93F8(self);
    Sink_001AEFA0* sink = self->sink;
    if (sink != 0) {
        Global_001AEFA0* g = (Global_001AEFA0*)D_00262E10;
        if (g != 0) {
            if (g->state != 4) {
                sink->value = self->pending;
                self->sink = 0;
                *(s32*)&self->pending = 0;
            }
        }
    }
}

void func_001AF000(Stack_001AF000* self, s32 value)
{
    u32 n = self->count;
    if (n < 4) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

void func_001AF028(Queue_1AF028* self, void* item)
{
    s32 n = self->count;
    if ((u32)n < 4) {
        self->items[n] = item;
        self->count = n + 1;
    }
}

void func_001AF050(Queue_1AF050* self, void* item)
{
    s32 n = self->count;
    if ((u32)n < 4) {
        self->items[n] = item;
        self->count = n + 1;
    }
}

void func_001AF078(Queue_1AF078* q, u32 value)
{
    u32 n = q->count;
    if (n < 4) {
        q->items[n] = value;
        q->count = n + 1;
    }
}

void func_001AF0A0(Unit_1AF0A0* self)
{
    func_001AECB0(self);
    self->scale = 1.0f;
}

void func_001AF0D0(void* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 2, D_002744B8);
}

INCLUDE_ASM(func_001AF108);

void func_001AF3B8(Obj_1AF3B8* self)
{
    Group_1AF3B8* src = &self->groups[0];
    func_00124A48(self);
    for (s32 i = 0; i < self->groupCount; i++) {
        Group_1AF3B8* g = &self->groups[i];
        Child_1AF3B8* c = g->child;
        c->vtbl[7](c);
        if (i != 0) {
            {
                s32 j;
                for (j = 0; j < src->count; j++) {
                    Entry_1AF3B8* s = src->items + j;
                    Entry_1AF3B8* d = g->items + j;
                    Child_1AF3B8* o = (Child_1AF3B8*)func_00183058(s->obj, self->f14, self);
                    d->obj = o;
                    if (o->vtbl[19] != 0) {
                        o->vtbl[19](o);
                    }
                    o = (Child_1AF3B8*)d->obj;
                    o->vtbl[20](o);
                    d->value = s->value;
                }
            }
            g->count = src->count;
        }
    }
    self->f_B00 = func_001AEF00((Obj_1AEF00*)self, (void*)D_00262E10);
    ((void (*)(void*, void*))self->vtbl[81])(self, self->f560);
}

void func_001AF508()
{
    ListFrame frame;
    s32 count = 0;
    Node_1AF508* n = *(Node_1AF508**)(D_00275710 + 0x1CA8);
    while (n != 0) {
        s32 t = count + 1;
        count = (n->x558 != 8) ? t : count;
        n = n->next;
    }
    if (count != 0) {
        s32 idx = 0;
        n = *(Node_1AF508**)(D_00275710 + 0x1CA8);
        while (n != 0) {
            if (n->x558 != 8) {
                n->fAFC = D_00261858[1] + (0.03333333507180214f / (f32)count) * (f32)idx;
                idx++;
            }
            n = n->next;
        }
    }
    D_002744D0 = 0;
}

void func_001AF5C8(Mixer_001AF5C8* self, f32 amount)
{
    s32 cmd;
    f32 v;
    f32 hi;
    f32 lo;

    func_001AEFA0(self, amount);
    v = self->fB04 + amount * self->fB08;
    hi = 1.0f;
    lo = 0.0f;
    if (v < lo)
        v = lo;
    else if (hi < v)
        v = hi;
    self->fB04 = v;
    if (D_002744D0)
        func_001AF508();
    cmd = self->state;
    switch (cmd) {
    case 0:
        if (self->f5B8 < D_0026185C[0] - self->f55C)
            cmd = 1;
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 2:
        cmd = 3;
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 3:
        if (self->f5BC < D_0026185C[0] - self->f55C) {
            if (self->f554 == 0) {
                cmd = 8;
                break;
            }
            if (self->f554 != 1)
                break;
            cmd = 4;
            if (self->vt->hook)
                self->vt->hook(self, &cmd);
            break;
        }
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 4:
        if (self->f5B8 < D_0026185C[0] - self->f55C)
            cmd = 5;
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 1:
    case 5:
    case 6:
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 7:
        if (self->fAEC < D_0026185C[0] - self->f55C)
            cmd = 8;
        else if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 8:
        break;
    }
    self->vt->done(self, cmd);
}

void func_001AF7A8(Obj_1AF7A8* self, void* p)
{
    func_0015FCD8(self, p);
    if (p != 0) {
        if (self->flag_AF8 != 0) {
            func_00152600(self->p14 + 0x1CA8, self);
            self->flag_AF8 = 0;
        }
    } else {
        func_00152470(self->p14 + 0x1CA8, self);
        self->flag_AF8 = 1;
    }
    D_002744D0 = 1;
}

INCLUDE_ASM(func_001AF820);

s32 func_001AFAF8(Obj_1AFAF8* a0, Obj_1AFAF8* a1)
{
    u64 m = 0x8000;
    m <<= 28;
    if ((a1->f538 & m) != 0 || a1->x50 == a0->x50 || func_001AEE50(a0, a1) != 0) {
        return 0;
    }
    if ((void*)a1 == (void*)D_00262E10 && a1->x2220 == 6 && a1->x239C == 3) {
        if ((func_00160D10() & 0x12000) != 0) {
            return 0;
        }
    }
    s64 t = (s64)a1->x2CC;
    return ((s32)t ^ 1) & 1;

}

INCLUDE_RODATA(jtbl_0024CFF0);
INCLUDE_ASM(func_001AFBB0);

void func_001B00E8(Obj_1B00E8* self, s32 flag)
{
    s32 m = 5;
    self->f554 = flag;
    if (!flag) {
        m = 1;
    }
    self->vtbl[0x144 / 4](self, m);
}

void func_001B0120(Obj_1B0120* self)
{
    if (self->f558 == 8) {
        return;
    }
    s32 m = 7;
    if (!self->f554) {
        m = 3;
    }
    self->vtbl[0x144 / 4](self, m);
}

void func_001B0160(Obj_1B0160* self)
{
    if (self->f558 < 3) {
        if (self->f558 >= 0) {
            self->vtbl[0x144 / 4](self, 3);
        }
    }
    self->f554 = 1;
}

void func_001B01B0(Obj_1B01B0* self, s32 s)
{
    u8* b = (u8*)self;
    s32 st = self->state;
    if (st == s) return;
    if (st == -1 || st == 8) {
        f32 z = 0.0f;
        f32 a = 1000.0f, c = 100.0f, d = 0.4f;
        (void)func_001BFCD8((Obj_1B01B0*)0x1A, (s32)(b + 0x5C4), self, 0, a, c, d, z, z, 0, 0);
    }
    switch (s) {
    case 3:
    case 7:
        for (s32 i = 0; i < *(s32*)(b + 0x5D4); i++) {
            Ent_1B01B0* e = (Ent_1B01B0*)(b + (i * 0x50 + 0x5E0));
            for (s32 j = 0; j < e->count; j++) func_00155F90(e->e[j][0]);
        }
        break;
    case 8: {
        f32 v;
        if (self->f554 == 0) v = *(f32*)(b + 0x5BC); else v = *(f32*)(b + 0xAEC);
        func_001BF788(*(s32*)(b + 0x5C4), (s32)v * 1000);
        self->vt->slot1C(self);
        D_002744D0 = 1;
        break;
    }
    default:
        break;
    }
    func_001AECE8(self, s);
}

f32 func_001B0360(Obj_1B0360* o, Cfg_1B0360* c)
{
    f32 s = c->f4;
    f32 r;
    f32 m;
    f32 t;
    switch (o->mode) {
    case 0:
    case 4: {
        f32 t0 = o->f5B8;
        if (t0 == 0.0f) {
            r = o->fB04;
        } else {
            f32 q = (D_0026185C[0] - o->f55C) / t0;
            m = o->fB04;
            if (q < 0.0f)
                r = 0.0f;
            else if (m < q)
                r = m;
            else
                r = q;
        }
        break;
    }
    case 1:
    case 2:
    case 5:
    case 6:
        r = o->fB04;
        break;
    case 3:
    case 7:
        t = o->i554 == 0 ? o->f5BC : o->fAEC;
        if (t == 0.0f) {
            r = 0.0f;
        } else {
            f32 m = o->fB04;
            r = 1.0f - (D_0026185C[0] - o->f55C) / t;
            if (r < 0.0f)
                r = 0.0f;
            else if (m < r)
                r = m;
        }
        s = c->f8;
        break;
    case 8:
        r = 0.0f;
        break;
    }
    return s * r;
}

void func_001B0470(Obj_1B0470* self, f32 x)
{
    self->fB08 = -1.0f / x;
}

void func_001B0488(S_1B0488* p, f32 x) { p->value = 1.0f / x; }

void func_001B04A0(Obj_1B04A0* o)
{
    func_001AECB0(o);
    o->f5D8 = -1;
}

void func_001B04D0(Obj_1B04D0* self)
{
    func_00124A48(self);
    func_00124DF8(self, 2, D_002744D8);
    if (self->x5D0 == 0) {
        self->x5D0 = self;
    }
    if (self->x5D4 == 0) {
        self->x5D4 = *(s32*)(self->p14 + 0x1D14);
    }
    if (self->p200 != 0) {
        self->p200->x44 = 0;
    }
    u64 m = 0x8000;
    m <<= 28;
    self->f538 |= m;
    func_001B9AE0(self, 3, 0, 3, 0);
    self->vtbl[81](self, self->x560);
}

void func_001B0578(Obj_001B0578* self) {
    s32 st;
    s32 s1;
    func_001AEFA0(self);
    st = self->i558;
    switch (self->i558) {
    case 0:
        if (self->f5B8 < D_0026185C[0] - self->f55C) st = 1;
        break;
    case 2:
        st = 3;
        break;
    case 3:
        if (self->f5BC < D_0026185C[0] - self->f55C) st = 8;
        break;
    case 4:
        if (self->f5B8 < D_0026185C[0] - self->f55C) st = 5;
        break;
    case 1:
    case 5:
        if (self->vt->f130) {
            self->vt->f130(self, &st);
        }
        goto tail;
    case 6:
        s1 = self->i5D8;
        switch (s1) {
        case 0:
            if (D_00262E10 && D_00262E10->vt->f13C(D_00262E10, 2)) {
                s1 = 2;
            } else if (self->f5E0 < D_0026185C[0] - self->f5DC) {
                if (D_00262E10) {
                    u8 buf[16];
                    func_001D7098(buf, 2, self);
                    if (D_00262E10->vt->f140(D_00262E10, buf)) {
                        s1 = 1;
                        func_001AEF68(self);
                    }
                } else {
                    s1 = 1;
                }
            }
            break;
        case 1:
            if (self->f5E4 < D_0026185C[0] - self->f5DC) s1 = 2;
            break;
        case 2:
            if (self->f5E8 < D_0026185C[0] - self->f5DC) {
                s1 = -1;
                st = 5;
            }
            break;
        }
        func_001B1070(self, s1);
        goto tail;
    case 7:
        if (self->f5BC < D_0026185C[0] - self->f55C) st = 8;
        break;
    case 8:
        if (self->i5C0 == 0) {
            switch (self->i554) {
            case 0: st = 0; break;
            case 1: st = 4; break;
            }
        }
        goto tail;
    }
tail:
    self->vt->f144(self, st);
}

INCLUDE_RODATA(jtbl_0024D070);
INCLUDE_ASM(func_001B0838);

s32 func_001B0BD8() { return 1; }

s32 func_001B0BE0(Obj_1B0BE0* self, Obj_1B0BE0* other)
{
    if ((other->f538 & (1UL << 43)) != 0 || other->f50 == func_001925F0() || other->f50 == self->f50 || func_001AEE50(self, other) != 0) {
        return 0;
    }
    s64 t = (s64)other->f2CC;
    return ((s32)t ^ 1) & 1;
}

INCLUDE_ASM(func_001B0C68);

void func_001B0EA8(Obj_1B0EA8* self, s32 value)
{
    s32 m = 5;
    self->f554 = value;
    if (!value) {
        m = 1;
    }
    self->vtbl[0x144 / 4](self, m);
}

void func_001B0EE0(Obj_1B0EE0* self)
{
    if (self->f558 != 8) {
        self->vt->fn144(self, self->f554 == 0 ? 3 : 7);
    }
    Rec_1B0EE0* r = self->f550;
    if (r != 0) {
        if (r->f550 == 1) {
            if (__builtin_fabsf(D_0026185C[0] - r->f554) < 0.2f) {
                self->f5C0 = r->f550;
            }
        }
    }
}

void func_001B0F70(Obj_1B0F70* o)
{
    if (o->f554 == 0) {
        o->f554 = 1;
        if (o->f558 != 8) {
            o->vtbl[0x144 / 4](o, 3);
        }
    }
}

void func_001B0FC0(Self_1B0FC0* self, s32 s)
{
    if (self->state != s) {
        switch (self->state) {
        case -1: case 0: case 1: case 2: case 3: case 4: case 5: case 7:
            break;
        case 6:
            func_001B1070(self, -1);
            break;
        case 8:
            self->f5C0 = 0;
            break;
        }
        switch (s) {
        case 6:
            func_001B1070(self, 0);
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 7: case 8:
            break;
        }
        func_001AECE8(self, s);
    }
}

void func_001B1070(Obj_1B1070* self, s32 arg)
{
    if (self->f5D8 == arg) return;
    switch (self->f5D8) {
    case -1:
        break;
    case 0:
        break;
    case 1:
        func_001BF788(self->f5C4, 0);
        break;
    case 2:
        break;
    }
    switch (arg) {
    case -1:
        break;
    case 0:
        if (self->f200 != 0) {
            self->f200->f44 = 4;
        }
        break;
    case 1:
        func_001BFCD8(KIND_1B1070_1B, &self->f5C4, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 2:
        if (self->f200 != 0) {
            self->f200->f44 = 0;
        }
        break;
    }
    self->f5D8 = arg;
    self->f5DC = (*(Clk_1B1070*)D_0026185C).t;
}

void func_001B1158(Obj_1B1158* self)
{
    func_001AECB0(self);
    self->f5D0 = -1;
    self->f5D4 = -1;
    self->f5E0 = -1;
    self->f5E4 = -1;
    self->f5F0 = -1;
    self->f5F4 = -1;
    self->f600 = -1;
}

void func_001B11A0(Obj_1B11A0* self)
{
    func_00124A48(self);
    for (s32 i = 0; i < self->f27C; i++) {
        Item_1B11A0* it = self->f280[i];
        if (it->f08 == 1 && it->f14 != 0) {
            self->f610 = it;
            break;
        }
    }
    self->vt->fn144(self, self->f560);
}

void func_001B1238(Obj_1B1238* self)
{
    s32 state;

    func_001AEFA0(self);
    state = self->f558;
    switch (state) {
    case 0:
        if (self->f5b8 < D_0026185C[0] - self->f55c) {
            state = 1;
        }
        break;
    case 1:
        if (0.0f <= self->f608) {
            if (self->f608 < D_0026185C[0] - self->f55c) {
                state = 3;
                break;
            }
        }
        if (self->vt->f130 != 0) {
            self->vt->f130(self, &state);
        }
        break;
    case 3:
        if (self->f5bc < D_0026185C[0] - self->f55c) {
            state = 8;
        }
        break;
    case 4:
        if (self->f5b8 < D_0026185C[0] - self->f55c) {
            state = 5;
        }
        break;
    case 5:
        if (0.0f <= self->f608) {
            if (self->f608 < D_0026185C[0] - self->f55c) {
                state = 7;
                break;
            }
        }
        if (self->vt->f130 != 0) {
            self->vt->f130(self, &state);
        }
        break;
    case 7:
        if (self->f5bc < D_0026185C[0] - self->f55c) {
            state = 8;
        }
        break;
    case 8:
        if (self->f5c0 == 0) {
            if (self->f60c < D_0026185C[0] - self->f55c) {
                switch (self->f554) {
                case 0:
                    state = 0;
                    break;
                case 1:
                    state = 4;
                    break;
                }
            }
        }
        break;
    }
    self->vt->f144(self, state);
    func_001B1898(self);
}

INCLUDE_ASM(func_001B1438);

void func_001B15D0(Obj_1B15D0* self, s32 mode)
{
    self->f554 = mode;
    self->vt->fn144(self, mode == 0 ? 1 : 5);
}

void func_001B1608(Obj_1B1608* self)
{
    if (self->f558 != 8) {
        self->vt->fn144(self, self->f554 == 0 ? 3 : 7);
    }
    Rec_1B1608* r = self->f550;
    if (r != 0) {
        if (r->f550 == 1) {
            if (__builtin_fabsf(D_0026185C[0] - r->f554) < 0.2f) {
                self->f5C0 = r->f550;
            }
        }
    }
}

void func_001B1698(Obj_1B1698* self)
{
    self->f554 = 1;
    if (self->f608 < 0.0f) {
        self->f618 = 0;
        switch (self->f558) {
        case 1:
            self->vt->fn144(self, 3);
            break;
        case 5:
            self->vt->fn144(self, 7);
            break;
        }
    }
}

void func_001B1710(Obj_1B1710* self, s32 n)
{
    if (self->state == n) return;
    switch (self->state) {
    case 1:
    case 5:
        func_001BF788((Tgt_1B1710*)self->f5C4, 0);
        self->f614 = self->f55C;
        break;
    case 8:
        self->f5C0 = 0;
        self->f618 = 0;
        break;
    }
    switch (n) {
    case 1:
        func_001BFCD8(15, &self->f5C4, (s32)self, 0, 2000.0f, 500.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 2:
    case 6:
        self->f618 = 1;
        break;
    case 3:
    case 4:
    case 7:
        break;
    case 5:
        func_001BFCD8(27, &self->f5C4, (s32)self, 0, 2000.0f, 500.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    }
    func_001AECE8(self, n);
    if (self->f618 != 0 && (n == 2 || n == 6)) {
        self->state = (n == 2) ? 1 : 5;
        self->f55C = self->f614;
    }
}

void func_001B1898(Obj_001B1898* self)
{
    s32 first, last, mode, frame;
    f32 duration, start;

    switch (self->state) {
    case 0:
    case 4:
    case 8:
        first = self->animA.first;
        last = self->animA.last;
        duration = self->animA.duration;
        mode = self->animA.mode;
        start = self->startTime;
        break;
    case 1:
        first = self->animB.first;
        last = self->animB.last;
        duration = self->animB.duration;
        mode = self->animB.mode;
        start = self->startTime;
        break;
    case 3:
        frame = (s32)((D_0026185C[0] - self->startTime) / (1.0f / self->blinkRate)) % 2;
        if (frame != 0) {
            first = self->animB.first;
            last = self->animB.last;
            duration = self->animB.duration;
            mode = self->animB.mode;
            start = self->blinkStart;
        } else {
            first = self->blinkFrame;
            last = first;
        }
        break;
    case 7:
        frame = (s32)((D_0026185C[0] - self->startTime) / (1.0f / self->blinkRate)) % 2;
        if (frame != 0) {
            first = self->animC.first;
            last = self->animC.last;
            duration = self->animC.duration;
            mode = self->animC.mode;
            start = self->blinkStart;
        } else {
            first = self->blinkFrame;
            last = first;
        }
        break;
    case 5:
        first = self->animC.first;
        last = self->animC.last;
        duration = self->animC.duration;
        mode = self->animC.mode;
        start = self->startTime;
        break;
    }

    s32 count = last - first + 1;
    if (count == 1 || duration <= 0.0f) {
        frame = first;
    } else {
        switch (mode) {
        case 0:
            frame = (s32)((D_0026185C[0] - start) / (duration / (f32)count)) % count;
            break;
        case 1: {
            s32 period = count * 2 - 2;
            frame = (s32)((D_0026185C[0] - start) / (duration / (f32)period)) % period;
            if (frame >= count)
                frame -= (frame - count + 1) * 2;
            break;
        }
        }
        frame += first;
    }
    func_001B46E0(self->target + 0x10, frame);
}
