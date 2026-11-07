// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "world.h"
#include "object_pool.h"
#include "screen_element.h"
#include "v24a2.h"
#include "shapes.h"
#include "game_clock.h"
#include "game_progress.h"
#include "text_reader.h"
#include "globals.h"

// The font object's calls.
V24A2* func_0015C1C0(s32 k);
void func_0015C8B8(V24A2* font, f32 x, f32 y);
f32 func_0015C418(V24A2* font, void* text);
void func_0015C638(V24A2* font, void* text, void* out, s32 zero, void* d);
void func_0015C900(V24A2* font);
void* func_0015DB28(void* out, void* text, V24A2* font);
void func_0015E318(void* buf, void* out, s32 zero, void* d);

void func_00182ED0(void* self);
void func_001A93C8(void* self);


void func_001F3C08(void* a, f32* out);
void func_00128150(int a, int b, void* c, f32* d);
f32 func_00205778(f32 x, f32 y);


void func_001C7CB8(void* self);
void func_0012E760(void* obj);


extern f32 D_0026185C;
extern f32 D_00261860;

void func_001AB980(T217D_510* self, f32 value);

extern s32 D_0026227C;

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);


void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);

void func_001C72A0(C0D* self);
void func_001DDC38(void* sub, C0D* self);


s32 func_001DDA80(void* sub);


typedef void* (*VFn_1A9960)(void* self);
void func_001C8C08(C0D* self);
void func_001C8418(C0D* self, void* p);


void func_001C8E28(C0D* self);
void func_001C8BC0(C0D* self);


extern u8 D_00264A40[];

void func_001C91C8(C0D* self);
void func_001603E8(s32 n);
void func_0018C7F8(u8* p);


extern T217D_2E0 D_0026E248;

s32 func_001E9970(void);



struct Tab_26C3E0 { T217D_Place e[37]; s32 end; };
extern Tab_26C3E0 D_0026C3E0;
extern u8 D_00261868[];


void* func_0018D5C0(u32 n);


void func_00182C58(void* self);
void* func_0015A448(void* obj, s32 id, void* owner);
s32 func_001300E8(void* node, s32 kind);


void func_001F5C0C(void* p, s32 value, s32 size);


void func_001F5C0C(void* p, s32 value, s32 size);


void func_001A93C8(void* self);


struct Entry_1A8718 { s32 key; s32 pad[3]; s32 flags; };

Entry_1A8718* func_001A8718(ObjectPool* table, s32 key);


struct Row_1A8820 { s32 unk0; s32 itemCount; void** items; u8 pad[8]; };


struct Entry_1A87E0 { s32 pad0; s32 f4; s32 pad1; s32 fC; };

Entry_1A87E0* func_001A8718(void* table, s32 key);


struct __attribute__((aligned(16))) Quad_1A94C0 { s32 a, b, c, d; };
struct Inner_1A94C0 {
    u8 pad0[0x110];
    Quad_1A94C0 q110;
    Quad_1A94C0 q120;
    Quad_1A94C0 q130;
    Quad_1A94C0 q140;
};
struct Obj_1A94C0 {
    void* f0;
    void* f4;
    Inner_1A94C0* f8;
    u8 pad0[4];
    Quad_1A94C0 q10;
    Quad_1A94C0 q20;
    Quad_1A94C0 q30;
    Quad_1A94C0 q40;
};

void func_001920B0(void* self, void* arg);
s32 func_001F3BD8(void* self, void* arg);
void func_001F3C08(void* self, void* arg);
void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);


extern u8 D_00261868[];

void func_001830D8(ObjectPool* self, void* o);
void* func_001A8110(void* self);
void func_00152438(void* self, s32 value);
void func_00152470(void* list, void* item);
u8* func_0018D568(s32 size, void* src);


// NEAR: frame and body match; the two local slots are swapped (retail: tmp at sp+0x30, buffer at sp+0x40; ours: buffer at sp+0x30, tmp at sp+0xE0), so the frame is 0x120 not 0x130


void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);


struct Local_001AB710 { f32 x; f32 y; u8 pad0[0x8]; T217D_Word w10; u8 pad1[0xC]; s32 tag; u8 pad2[0xC]; T217D_Word w30; };
struct VDesc_001AB710 { u8 pad0[0x48]; s16 off48; u8 pad1[2]; void (*fn4C)(void* self, void* obj, void* out, void* d); };
struct SubObj_001AB710 { u8 pad0[0x4C]; VDesc_001AB710* desc4C; };

void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, void* p);
void func_00137260(void* out, s32 v);
void func_00137268(void* out, s32 v);

extern void* const D_002486B0[];
extern u8 D_00262C68[];
extern u8 D_00262C70[];
extern u8 D_00262D38[];
extern u8 D_00275F80[];

void func_001EFD10(void* a, void* b);


extern void* const D_002486B0[];


// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
// The screen elements' methods, in src/main/screen_element.cpp.
void func_001AA268(ScreenElement* self);
void func_001AA298(ScreenElement* self);
void func_001AAF88(T217D_E30* self);
void func_001AB198(T217D_E30* self);
f32 func_001AB5D8(void);
void func_001AB600(T217D_510* self);
void func_001AB660(T217D_510* self);
void func_001AB710(T217D_510* self);
f32 func_001ABE40(void);
f32 func_001ABE50(void);
f32 func_001ABE60(void);

extern const Fn_Table D_00217E30[];
extern const Fn_Table D_00217E80[];
extern const Fn_Table D_00217ED0[];
extern const Fn_Table D_00217F20[];
extern const Fn_Table D_00217F70[];
extern const Fn_Table D_00217FC0[];
extern const Fn_Table D_00218010[];
extern const Fn_Table D_00218060[];
extern const Fn_Table D_002180B0[];
extern const Fn_Table D_00218100[];
extern const Fn_Table D_00218150[];
extern const Fn_Table D_002181A0[];
extern const Fn_Table D_002181F0[];
extern const Fn_Table D_00218240[];
extern const Fn_Table D_00218290[];
extern const Fn_Table D_002182E0[];
extern const Fn_Table D_00218330[];
extern const Fn_Table D_00218380[];
extern const Fn_Table D_002183D0[];
extern const Fn_Table D_00218420[];
extern const Fn_Table D_00218470[];
extern const Fn_Table D_002184C0[];
extern const Fn_Table D_00218510[];
extern const Fn_Table D_00218560[];
extern const Fn_Table D_002185B0[];
extern const Fn_Table D_00218600[];
extern const Fn_Table D_002186D0[];
extern const Fn_Table D_00218720[];
extern const Fn_Table D_0021A3F0[];
extern const Fn_Table D_0021A440[];
extern const Fn_Table D_00220BF0[];
extern const Fn_Table D_002210F0[];
extern const Fn_Table D_002212E0[];
extern const Fn_Table D_00221330[];
extern const Fn_Table D_00221380[];
extern u8 D_00275F80[];

void func_001EFCE8(void* p);


extern s8 D_00262250[];
extern u8 D_0024E879[];
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void* func_001E2138(void* dst, void* src);

struct Hdr_1A8208 { u8 pad0[4]; s32 f4; s32 f8; Quad16* fC; };
struct Ent_1A8208 { s32 f0; s32 f4; void** f8; s32 fC; s32 f10; };
struct Self_1A8208 {
    u8 pad0[0x14]; void* f14; u8 pad18[0x1C];
    s32 f34; Ent_1A8208* f38; Hdr_1A8208* f3C;
};

void* func_0018D500(s32 size);
PlacedObject* func_0015A418(void* a, s32 b, s32 c, Self_1A8208* d);
void func_00152438(void* p, s32 a);
s32 func_001527D8(void* p);
PlacedObject* func_00183058(PlacedObject* a, World* b, BaseObject* c);


struct Tab_1A87A8;
struct Ent_1A87A8 { s32 pad[4]; s32 flags; };

Ent_1A87A8* func_001A8718(Tab_1A87A8* table, s32 key);


void func_001A8AF8(ObjectPool* self);


struct Obj_1A93E8;
void func_001F5C0C(Obj_1A93E8* p, s32 zero, s32 size);


extern void* const D_002486B0[];


extern void* const D_002486B0[];


extern void* const D_002486B0[];

extern Tab_26C3E0 D_0026C3E0;



// NEAR: (fixed: indexed loop gave EXACT)
// allocator puts the count in $s1 and the pointer in $s0; retail is the other way round.

extern u8 D_00275F80[];
void func_001EFEE0(u8* a);
void func_001AE820(u8* a);



struct Entry_1A8150 { s32 f0; s32 f4; u8 pad[8]; s32 f10; };

void* func_0018D5C0(u32 n);


s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...);
extern s32 D_002751D4;

// EXACT: dst built as i*4 + (u32)items

struct Rec_1A8AF8 { s32 f0; s32 count; s32* items; s32 f0C; s32 flags; };
void func_001A89E8(ObjectPool* self);
s32 func_001A88A0(ObjectPool* self, s32 item);
void func_001F5B08(s32* dst, s32* src, s32 size);


struct Rec_001A89E8 {
    s32 f00;
    s32 f04;
    s32* f08;
    s32 f0C;
    s32 f10;
};

s32 func_001A88A0(ObjectPool* self, s32 item);




void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...);

f32 func_001EAF28(f32 x);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001AA1F0();
void func_001AA790();
void func_001AA898();
void func_001AA8A0();
void func_001AA8A8();
void func_001AA8C8();
void func_001AA8F0();
void func_001AA958();
void func_001AAF58();
void func_001AAAC8();
void func_001AA4F0();
void func_001AA998();
void func_001AB058();
void func_001ABE70();
void func_001AC0E8();
void func_001AC888();
void func_001AC910();
void func_001AC990();
s32 func_001AC9E0();
void func_001ACA30();
void func_001ACA68();
void func_001ACAA8();
void func_001ACDA0();
void func_001ACE38();
void func_001AD320();
void func_001AD378();
void func_001AD3B0();
void func_001AD3F0();
void func_001AD6A8();
void func_001AD718();
void func_001AD7B0();
void func_001ADC60();
void func_001ADD28();
void func_001ADF28();
void func_001AE130();
void func_001AE178();
void func_001AE220();
void func_001AD940();
void func_001AD970();
void func_001ADB00();
void func_001AE510();
void func_001AE5E0();
void func_001AE758();
void func_001AE7F8();
void func_00193E58();
void func_001940E8();
void func_001943E8();
void func_00194E60();
void func_00194F00();
void func_00194F38();
void func_00194F80();
void func_0014ABD0();
void func_0014AC48();
void func_0014AD00();
void func_0014AD70();
void func_0014ADE0();
void func_001E5E70();
void func_001E6188();
void func_001E73B8();
void func_001E76E0();
void func_001E77C0();
void func_001E7C60();
void func_001E8840();
void func_001310F0();
void func_00131198();
void func_00135550();
void func_00136040();
void func_00136238();
void func_001363D0();
void func_00136408();
f32 func_001365F0();
f32 func_00136648();
void func_001366A0();
void func_00136EF8();
s32 func_00136FA8();
void func_001821B0();
void func_001F1960();
void func_001F1A08();
void func_001F1C90();
void func_001F20A8();
void func_0016B4A0();
void func_0016B560();
void func_0016B580();
void func_0016B7A8();
void func_0016B860();
void func_0016BA40();
void func_0016BBA8();
void func_0016BDD0();
void func_0016BEA0();
void func_001DFEB8();
void func_001E00B0();
void func_001E0678();
extern const Fn_Table D_00217E30[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217E80[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217ED0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217F20[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217F70[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001ABE40, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00217FC0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001ABE50, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218010[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218060[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002180B0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218100[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218150[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002181A0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001ABE60, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002181F0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218240[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218290[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002182E0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ABE70, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AC0E8, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218380[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AC888, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AC910, (Fn_Table)func_001ACAA8, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001ACA30, (Fn_Table)func_001ACA68, (Fn_Table)func_001AC990, (Fn_Table)func_001AAF58, (Fn_Table)func_001AC9E0, 0 };
extern const Fn_Table D_002183D0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ACDA0, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001ACE38, (Fn_Table)func_001AD3F0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AD378, (Fn_Table)func_001AD3B0, (Fn_Table)func_001AD320, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218420[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AD6A8, (Fn_Table)func_001AD718, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AD7B0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218470[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ADC60, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001ADD28, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002184C0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001ADF28, (Fn_Table)func_001AE178, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AE220, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AE130, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218510[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AB600, (Fn_Table)func_001AB660, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB710, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218560[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AD940, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001ADB00, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AD970, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002185B0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AE510, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AE5E0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218600[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001AE758, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001AA790, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AE7F8, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002186D0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_00193E58, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_001940E8, (Fn_Table)func_001943E8, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_00194F80, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_00194F00, (Fn_Table)func_00194F38, (Fn_Table)func_00194E60, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00218720[20] = { (Fn_Table)func_0014ABD0, (Fn_Table)func_0014AC48, (Fn_Table)func_0014AD70, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_0014ADE0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_0014AD00, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_0021A3F0[20] = { (Fn_Table)func_001E5E70, (Fn_Table)func_001E6188, (Fn_Table)func_001E77C0, 0, 0, (Fn_Table)func_001E8840, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001E73B8, (Fn_Table)func_001E7C60, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001E76E0, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_0021A440[20] = { (Fn_Table)func_001310F0, (Fn_Table)func_00131198, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_00136238, (Fn_Table)func_00136040, (Fn_Table)func_001363D0, (Fn_Table)func_00136EF8, (Fn_Table)func_00136FA8, (Fn_Table)func_00136408, (Fn_Table)func_001366A0, 0, (Fn_Table)func_001365F0, (Fn_Table)func_001AA8A0, (Fn_Table)func_00136648, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_00135550, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00220BF0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)(void (*)(ScreenElement* self))func_001AA268, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001821B0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002210F0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001F1960, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_001F1C90, (Fn_Table)func_001F1A08, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001F20A8, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_002212E0[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_0016B4A0, (Fn_Table)func_0016B560, (Fn_Table)func_0016B7A8, (Fn_Table)func_0016B580, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_0016B860, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00221330[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_0016BA40, (Fn_Table)(void (*)(ScreenElement* self))func_001AA298, (Fn_Table)func_0016BDD0, (Fn_Table)func_0016BBA8, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_0016BEA0, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };
extern const Fn_Table D_00221380[20] = { (Fn_Table)func_001AA1F0, (Fn_Table)func_001DFEB8, (Fn_Table)func_001E00B0, 0, 0, (Fn_Table)func_001AA8C8, 0, 0, (Fn_Table)func_001AA4F0, (Fn_Table)func_001E0678, 0, (Fn_Table)func_001AA898, (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958, (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0 };


s32 func_001E2100(const char*);
void* func_001E2138(char*, const char*);
void func_0015E290(TextReader*, f32, f32*, f32*);

extern f32 D_00261860;

void func_001AB2B8(T217D_E30* self);
f32 func_0015DFF8(TextReader* loc);


struct Key_1A88A0 { u8 pad0[0x678]; s32 f678; u8 pad1[4]; s32 f680; };
struct List_1A88A0 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_1A88A0 { List_1A88A0* list; u8* link; s32 offset; Iter_1A88A0* prev; };

s32 func_00182FC8(Key_1A88A0* p);
s32 func_001300E8(Key_1A88A0* p, s32 kind);

struct Begin_1A88A0 {
    static void Of(Iter_1A88A0* it, List_1A88A0* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (Iter_1A88A0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_1A88A0 {
    static u8* Of(Iter_1A88A0* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct End_1A88A0 {
    static void Of(Iter_1A88A0* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};


// Data defined by this file.
extern void* const D_002486B0[38] = {
    (void*)&D_002721D0,
    (void*)&D_002701F8,
    (void*)&D_00270650,
    (void*)&D_0026C6C8,
    (void*)&D_0026C948,
    (void*)&D_0026CBC8,
    (void*)&D_0026CE48,
    (void*)&D_0026D0C8,
    (void*)&D_0026D348,
    (void*)&D_0026D5C8,
    (void*)&D_0026D848,
    (void*)&D_0026DAC8,
    (void*)&D_0026DD48,
    (void*)&D_0026DFC8,
    (void*)&D_0026E248,
    (void*)&D_0026E4E0,
    (void*)&D_0026E760,
    (void*)&D_0026E9F8,
    (void*)&D_0026EC70,
    (void*)&D_0026EED0,
    (void*)&D_0026F138,
    (void*)&D_0026F5A0,
    (void*)&D_0026F808,
    (void*)&D_0026FA90,
    (void*)&D_0026FD00,
    (void*)&D_0026FF68,
    (void*)&D_002708E0,
    (void*)&D_00271558,
    (void*)&D_00272430,
    (void*)&D_002726B0,
    (void*)&D_00272930,
    (void*)&D_00272B98,
    (void*)&D_00272E08,
    (void*)&D_002739F0,
    (void*)&D_00273C50,
    (void*)&D_00273EB0,
    (void*)&D_00274118,
    0,
};
extern Tab_26C3E0 D_0026C3E0;

