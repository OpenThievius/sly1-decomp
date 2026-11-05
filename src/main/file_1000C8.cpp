// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "r11b008.h"
#include "shapes.h"
#include "c01.h"
#include "c02.h"
#include "c03.h"
#include "c05.h"
#include "c1f.h"
#include "c20.h"
#include "c28.h"
#include "c29.h"
#include "c2c.h"
#include "c30.h"
#include "c36.h"
#include "c3b.h"
#include "c47.h"
#include "c4a.h"
#include "c4c.h"
#include "c4e.h"
#include "c50.h"
#include "c5d.h"
#include "c60.h"
#include "c62.h"
#include "c65.h"
#include "c6d.h"
#include "c73.h"
#include "c7d.h"
#include "c83.h"
#include "c88.h"
#include "c8b.h"
#include "c8c.h"
#include "c8d.h"
#include "c8f.h"
#include "c90.h"

// The kinds a property's arguments are read as (func_001C23B0's fourth argument): one word per
// argument, copied from the file's .rodata into the frame as one block.
struct Kinds2 { s32 k[2]; };
struct Kinds3 { s32 k[3]; };
struct Kinds4 { s32 k[4]; };
struct Kinds5 { s32 k[5]; };
struct Kinds6 { s32 k[6]; };

struct Obj_101D38;

void func_00123AB0(void* object, s32 mode);
s32 func_00123D08(C2F* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001250C8(void* p);
s32 func_00126CB8(void* self, f32 value);
s32 func_00126D60(void* self, f32 value);
void* func_00129B98(void* self, s32 key);
void* func_00129C20(void* self, s32 key);
void* func_00129CA8(void* self);
void func_0012A8B8(void* p);
void func_0012A8C8(void* p);
void func_0012A8D8(C02* self, s32 a, f32 x, f32 y);
void func_0012AA50(void* self, f32 a, f32 b);
s32 func_0012AAE8(void* self, f32 value);
void func_0012AF38(C02* self, s32 value, Quad16* src, f32 x, f32 y, f32 z);
void func_0012B010(void* p);
s32 func_0012B5B8(C02* x, s32 a, s32 b);
void* func_0012C7D8(C83* self, s32 a1, f32 f1, f32 f2, s32 a2);
void* func_0012C8F8(C83* item, s32 a, f32 x, f32 y, s32 b, s32 c);
f32 func_0012CCC0(void* obj, s32 id);
void func_0012E760(void* obj);
s32 func_0012E928(void* obj, s32 a, s32 b);
void func_0012F0A0(Obj_101D38* self, s32 a, f32 x, f32 y);
void func_0012F190(void* obj, s32 v);
s32 func_001300E8(void* list, s32 value);
s32 func_0013BE00(void* p, f32 x);
void func_0013BF68(void*);
s32 func_00140750(C28* self, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_00140770(C29* self, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_00141170(void*,void*);
void func_001455F0(void* p);
s32 func_00145FB8(void*,s32);
s32 func_00145FD8(void*);
s32 func_00145FF8(void* x);
void func_00146018(C6D* obj, s32 value, f32 first, f32 second);
void func_00146028(void* x);
s32 func_00146038(void* obj, void* p, f32 x, f32 y);
void func_00150408(void*);
void func_00150418(void*,s32);
void func_00150750(void* x);
void func_00150760(void* x);
void func_001518B8(void* x);
void func_001519A8(void* x);
void func_001519E0(C65* p, s32 a, s32 b);
void func_001557D0(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
s32 func_00155F78(void* p, f32 x);
void func_00155F90(void* x);
void func_00155FA0(void* x);
void func_00158730(void* x);
void func_00158778(C77* self, s32 a, s32 b, Quad4* u, Quad4* v, f32 x, f32 y);
void func_00158D40(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
void func_00159ED0(void* x);
s32 func_0015AA50(void*,void*);
void func_0016DCF0(void*);
void func_0016DD00(void*);
void func_00171F28(void* self, void* v, f32 x, f32 y);
void func_00171FE0(void*);
void func_001777F8(void*,s32);
void func_00177800(void*,s32);
s32 func_001781E0(void* obj, s32 v);
s32 func_00178258(void* obj, s32 v);
void func_00178280(void*,s32);
void func_0017AD50(void* x);
s32 func_0017B550(void* self, s32 index);
void func_0017B598(void* x);
void func_0017CDE0(void*);
void func_0017CE20(void* x, s32 v);
void func_0017CE80(void*);
void func_0017CFC8(void* x, s32 v);
void func_0017CFF0(void* x, s32 v);
void func_0017D018(void* x, s32 v);
s32 func_0017D040(void* self, s32 value);
void* func_0017D078(void* self, s32 value);
void func_0017D0A0(void* self, s32 a, f32 value);
void func_0017D0D8(C8F* p, s32 a, s32 b);
void func_0017D100(C8F* self, s32 b, s32 c, s32 d, s32 e);
void func_0017D148(C8F* self, s32 a, s32 b, f32 value);
void func_0017D180(C8F* self, s32 a, s32 b, f32 value);
void func_0017D1B8(void* self, s32 b, s32 c, s32 d);
void func_0017D1E8(void* x, f32 f);
void func_0017D220(void* x);
void func_00182948(void* a0, s32 a1, f32 x);
void func_00182DD8(void* p);
s32 func_00182F40(void* e, s32 v);
void* func_00183058(C01* x, s32 a, s32 b);
s32 func_001833F0(void* key, s32 item);
s32 func_00183910(C01* x, s32 a, s32 b);
s32 func_00183990(C01* x, s32 a, s32 b);
void func_00183A10(void* a0, s32 a1, f32 x);
void func_00183A90(void* a0, s32 a1, Quad16* a2);
void func_00183B20(void* a0, s32 a1, Quad16* a2);
s32 func_00183BB8(C01* x, s32 a, s32 b);
void func_00183C38(void* a0, s32 a1, Quad16* a2);
void func_0018AC58(C0C* st);
void func_0018DD50(void*,s32);
void func_0018DD78(void*,s32);
s32 func_00190660(void* x, s32 v);
void func_00192418(void* o);
void func_001993C0(void* x);
void func_00199AF0(void* p);
void func_0019AD30(C17* p, s32 a, s32 b);
void func_0019CE28(C8B* value, f32 x, f32 y, f32 z);
void func_0019CE38(C8B* self, f32 x, f32 y, f32 z);
s32 func_001A8150(C8C* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001A8778(void*,s32);
void func_001A87A8(void*,s32);
void func_001A87E0(C8C* p, s32 a, s32 b);
void func_001A8AF8(void*);
s32 func_001A8C90(void* obj, s32 v);
void func_001A93E8(void* x);
void func_001A9438(void* x);
void func_001A9498(void*);
void func_001A9C58(C0D* self, s32 a, s32 b, s32 c);
s32 func_001B0470(void* p, f32 x);
s32 func_001B0488(void* p, f32 x);
void* func_001B6290(C88* a, s32 b, s32 c, s32 d);
void func_001B6438(void* x);
void func_001B70B0(C09* p, s32 a, s32 b);
void func_001BB1E0(void* self, u32 value);
s32 func_001BC670(void* x, void* out);
s32 func_001C08B0(C6C* x, s32 a, s32 b);
void func_001C0950(void* p);
s32 func_001C09D8(C6C* x, s32 a, s32 b);
void func_001C3F68(void* self, s32 value);
void func_001C4180(void* self, s32 value);
void func_001C41A0(void* self, s32 value);
void func_001C8FD0(C08* p, s32 a, s32 b);
void func_001CA608(C08* self, s32 a, s32 b);
void func_001CA658(C08* self, s32 a, s32 b);
void* func_001CA6D0(void* obj, s32 v);
void func_001CA720(C08* self, s32 a, s32 b);
void func_001CA898(C08* p, s32 a, s32 b);
void func_001CA960(C08* self, s32 a, s32 b);
s32 func_001CAD60(C08* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001CB328(void*, s32);
void func_001D2830(void*,s32);
void func_001D31D0(void*,s32);
void func_001D32D8(C4C* self, s32 a, s32 b);
void func_001D6CB0(void* obj);
void func_001DB110(void*,s32);
void func_001DB1E8(C19* item, s32 a, f32 x, f32 y, s32 b, s32 c);
void func_001DB290(C19* st);
void func_001DBAC0(C6C* self, s32 a, s32 b);
s32 func_001DBAE0(void*,s32);
void func_001DBB00(C6C* self, s32 a, s32 b);
s32 func_001DD690(void* self, s32 obj);
s32 func_001DD6B0(void* self, s32 obj);
s32 func_001DD6D0(void* self, s32 obj);
s32 func_001DD6F0(void* self, s32 obj);
s32 func_001DD710(void* x, s32 v);
s32 func_001DD758(void* x, s32 v);
s32 func_001DD7A0(void* x, s32 v);
void func_001DD7E8(C6C* self, void* obj, s32 key, s32 value);
s32 func_001DD888(C6C* self, s32 a, s32 b);
s32 func_001DD8E8(void* x, s32 v);
s32 func_001DD908(void* self, s32 index);
s32 func_001DD928(void* self);
void func_001DD950(C6C* unused, s32 a, s32 b, void* c);
void func_001DDA20(void* a);
void func_001DDA50(void*);
void func_001DDAD0(void* x);
void func_001DDB20(C6C* self, s32 a, s32 b);
void func_001DDB58(void* x);
void func_001DDBB8(void* x);
s32 func_001DDBF8(void*,s32);
s32 func_001DDC18(void* unused, s32 p);
s32 func_001DDC78(void*,s32);
s32 func_001DDC90(void*,s32);
void func_001EC528(void* x);
s32 func_001ED018(void* self, s32 value);
void func_001ED020(void* x);
void func_001ED090(C13* p, s32 a, s32 b);
s32 func_001ED0D8(void* self, s32 value);
void func_001ED558(C90* self, s32 p, f32 f, s32 q);
void func_001ED588(C90* self, s32 p, f32 f, s32 q);
void func_001ED5B8(C90* self, s32 p, f32 v);
void func_001ED5D8(C90* self, s32 p, f32 v);
void func_001ED5F8(C90* self, s32 p, f32 v);
void func_001ED618(C90* self, s32 p, f32 v);
void func_001EF830(void* o);
s32 func_001EF8C0(C62* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001F36E8(void*);
void func_001F3768(void* x);
void func_001F3928(void* self, f32 a, f32 b, f32 c, f32 d);
void func_001F3990(void* self, f32 a, f32 b, f32 c, f32 d);
void func_001F4008(void* x);
s32 func_001F42D0(C73* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001F4808(void* x);
void func_001F4ED0(void*);
void func_001F4F20(void* p);
void func_001F5210(void* p);

// Reads a property call's arguments: count values of args, each as its kind in kinds, through
// the pointers that follow (func_001C1BF8, src/main/file_1C05D0.cpp); gives back a value.
R11B008* func_001C23B0(R11B008* ret, s32 count, R11B008* args, const void* kinds, ...);

// The file's .rodata: the argument signatures its functions copy, in retail's order.
extern const s32 D_00248D80[2] = { 0x2000, 0x2000 };
extern const s32 D_00248D88[2] = { 0x14, 0 };
extern const s32 D_00248D90[2] = { 0x14, 5 };
extern const s32 D_00248D98[2] = { 0x14, 1 };
extern const s32 D_00248DA0[2] = { 0x14, 9 };
extern const s32 D_00248DA8[2] = { 0x14, 10 };
extern const s32 D_00248DB0[2] = { 0x14, 6 };
extern const s32 D_00248DB8[2] = { 0x14, 2 };
extern const s32 D_00248DC0[4] = { 1, 1, 0x1000, 0 };
extern const s32 D_00248DD0[2] = { 1, 1 };
extern const s32 D_00248DD8[6] = { 14, 1, 1, 1, 10, 0 };
extern const s32 D_00248DF0[4] = { 0, 6, 6, 6 };
extern const s32 D_00248E00[4] = { 0x2000, 1, 1, 0x1000 };
extern const s32 D_00248E10[6] = { 0x2000, 0x1000, 1, 1, 0x1000, 0 };
extern const s32 D_00248E28[4] = { 0x1000, 1, 1, 0 };
extern const Kinds2 D_00248E38 = { { 6, 0x1000 } };
extern const s32 D_00248E40[6] = { 6, 6, 1, 1, 1, 1 };
extern const s32 D_00248E58[6] = { 0x1000, 0x2000, 2, 2, 1, 1 };
extern const s32 D_00248E70[4] = { 0x2000, 6, 0x1000, 0 };
extern const s32 D_00248E80[4] = { 5, 5, 2, 0 };
extern const s32 D_00248E90[2] = { 0x1000, 5 };
extern const s32 D_00248E98[4] = { 15, 6, 5, 0 };
extern const Kinds2 D_00248EA8 = { { 0xF, 6 } };
extern const Kinds2 D_00248EB0 = { { 0x1000, 0x2000 } };
extern const s32 D_00248EB8[2] = { 5, 5 };
extern const s32 D_00248EC0[2] = { 5, 0 };
extern const s32 D_00248EC8[4] = { 0x2000, 1, 1, 0 };
extern const s32 D_00248ED8[4] = { 2, 1, 1, 0 };
extern const s32 D_00248EE8[2] = { 0x1000, 6 };
extern const s32 D_00248EF0[4] = { 6, 6, 6, 6 };
extern const s32 D_00248F00[4] = { 1, 1, 1, 0 };
extern const s32 D_00248F10[4] = { 6, 5, 0, 0 };
extern const s32 D_00248F20[2] = { 6, 5 };
extern const s32 D_00248F28[4] = { 1, 1, 1, 1 };
extern const s32 D_00248F38[6] = { 0x2000, 1, 1, 0x2000, 0x2000, 0 };
extern const s32 D_00248F50[2] = { 0x2000, 1 };
extern const s32 D_00248F58[2] = { 6, 1 };
extern const s32 D_00248F60[4] = { 6, 0x1000, 0x1000, 0 };
extern const s32 D_00248F70[4] = { 6, 1, 0, 0 };
extern const s32 D_00248F80[4] = { 6, 0x1000, 0, 0 };
extern const s32 D_00248F90[2] = { 6, 0 };
extern const s32 D_00248F98[2] = { 0x2000, 5 };
extern const s32 D_00248FA0[4] = { 5, 1, 0x1000, 0 };
extern const s32 D_00248FB0[4] = { 5, 1, 6, 0 };
extern const s32 D_00248FC0[2] = { 5, 1 };
extern const s32 D_00248FC8[4] = { 0x2000, 0x2000, 0x2000, 0 };
extern const s32 D_00248FD8[2] = { 0x2000, 0 };

// The file's .data: the property descriptors, filled at startup by func_00109488.
struct Prop_2505D8 { s32 f0; s32 flags; u8 body[24]; };
Prop_2505D8 D_002505D8[1179];

R11B008* func_001000C8(R11B008* ret, void* obj, s32 unused, R11B008* args);
R11B008* func_00100178(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100218(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_001002C0(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100368(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100438(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_001004F0(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_001005A0(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100650(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100720(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_001007F0(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_001008B8(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100998(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100A78(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100B48(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00100C28(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00100CC8(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00100D68(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00100E08(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00100EE0(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00100FA8(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00101058(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00101168(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00101208(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_001012B8(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00101368(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00101418(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_001014C8(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00101568(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_00101620(R11B008* ret, C02* obj, s32 unused, R11B008* args);
R11B008* func_001016F0(R11B008* ret, C03* obj, s32 unused, R11B008* args);
R11B008* func_001017A0(R11B008* ret, C03* obj, s32 unused, R11B008* args);
R11B008* func_00101860(R11B008* ret, C73* obj, s32 unused, R11B008* args);
R11B008* func_00101950(R11B008* ret, C73* obj, s32 unused, R11B008* args);
R11B008* func_001019F0(R11B008* ret, C7D* obj, s32 unused, R11B008* args);
R11B008* func_00101A90(R11B008* ret, C83* obj, s32 unused, R11B008* args);
R11B008* func_00101B80(R11B008* ret, C83* obj, s32 unused, R11B008* args);
R11B008* func_00101C88(R11B008* ret, C83* obj, s32 unused, R11B008* args);
R11B008* func_00101D38(R11B008* ret, Obj_101D38* obj, s32 unused, R11B008* args);
R11B008* func_00101E10(R11B008* ret, void* obj, s32 unused, R11B008* args);
R11B008* func_00101EB0(R11B008* ret, void* obj, s32 unused, R11B008* args);
R11B008* func_00101F60(R11B008* ret, void* obj, s32 unused, R11B008* args);
R11B008* func_00102030(R11B008* ret, C1F* obj, s32 unused, R11B008* args);
R11B008* func_001020D0(R11B008* ret, C20* obj, s32 unused, R11B008* args);
R11B008* func_00102178(R11B008* ret, C28* obj, s32 unused, R11B008* args);
R11B008* func_00102268(R11B008* ret, C29* obj, s32 unused, R11B008* args);
R11B008* func_00102358(R11B008* ret, C05* obj, s32 unused, R11B008* args);
R11B008* func_001023F8(R11B008* ret, C05* obj, s32 unused, R11B008* args);
R11B008* func_001024B0(R11B008* ret, C2F* obj, s32 unused, R11B008* args);
R11B008* func_00102560(R11B008* ret, C2F* obj, s32 unused, R11B008* args);
R11B008* func_00102650(R11B008* ret, C30* obj, s32 unused, R11B008* args);
R11B008* func_00102710(R11B008* ret, C30* obj, s32 unused, R11B008* args);
R11B008* func_001027C0(R11B008* ret, C31* obj, s32 unused, R11B008* args);
R11B008* func_00102870(R11B008* ret, C31* obj, s32 unused, R11B008* args);
R11B008* func_00102920(R11B008* ret, C50* obj, s32 unused, R11B008* args);
R11B008* func_001029D0(R11B008* ret, C50* obj, s32 unused, R11B008* args);
R11B008* func_00102A70(R11B008* ret, C50* obj, s32 unused, R11B008* args);
R11B008* func_00102B10(R11B008* ret, C50* obj, s32 unused, R11B008* args);
R11B008* func_00102C28(R11B008* ret, C79* obj, s32 unused, R11B008* args);
R11B008* func_00102D40(R11B008* ret, C7A* obj, s32 unused, R11B008* args);
R11B008* func_00102DE0(R11B008* ret, C7A* obj, s32 unused, R11B008* args);
R11B008* func_00102F10(R11B008* ret, C78* obj, s32 unused, R11B008* args);
R11B008* func_00102FB0(R11B008* ret, C78* obj, s32 unused, R11B008* args);
R11B008* func_001030E0(R11B008* ret, C88* obj, s32 unused, R11B008* args);
R11B008* func_001031C0(R11B008* ret, void* obj, s32 unused, R11B008* args);
R11B008* func_00103260(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103350(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103420(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001034F0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103590(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103640(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001036F0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001037A0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103850(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103900(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001039B0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103A60(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103B40(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103C10(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103CC0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103D70(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103E10(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103EB0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00103F80(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00104020(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001040C0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00104170(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00104220(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001042F0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001043A0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00104470(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00104510(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_001045B0(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00104660(R11B008* ret, C6C* obj, s32 unused, R11B008* args);
R11B008* func_00104710(R11B008* ret, C6D* obj, s32 unused, R11B008* args);
R11B008* func_001047C0(R11B008* ret, C6D* obj, s32 unused, R11B008* args);
R11B008* func_00104860(R11B008* ret, C6D* obj, s32 unused, R11B008* args);
R11B008* func_00104900(R11B008* ret, C6D* obj, s32 unused, R11B008* args);
R11B008* func_001049D8(R11B008* ret, C6D* obj, s32 unused, R11B008* args);
R11B008* func_00104A78(R11B008* ret, C6D* obj, s32 unused, R11B008* args);
R11B008* func_00104B18(R11B008* ret, C6D* obj, s32 unused, R11B008* args);
R11B008* func_00104C00(R11B008* ret, C4E* obj, s32 unused, R11B008* args);
R11B008* func_00104CA0(R11B008* ret, C4E* obj, s32 unused, R11B008* args);
R11B008* func_00104D40(R11B008* ret, C36* obj, s32 unused, R11B008* args);
R11B008* func_00104DE0(R11B008* ret, C2E* obj, s32 unused, R11B008* args);
R11B008* func_00104E80(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_00104F50(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_00105020(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_001050D0(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_001051C0(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_00105290(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_00105360(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_00105430(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_00105500(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_001055A8(R11B008* ret, C08* obj, s32 unused, R11B008* args);
R11B008* func_00105658(R11B008* ret, C09* obj, s32 unused, R11B008* args);
R11B008* func_00105728(R11B008* ret, C3B* obj, s32 unused, R11B008* args);
R11B008* func_001057D8(R11B008* ret, C3B* obj, s32 unused, R11B008* args);
R11B008* func_00105878(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105960(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105A00(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105AB0(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105B60(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105C10(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105CC0(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105D60(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105E10(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105EC0(R11B008* ret, C07* obj, s32 unused, R11B008* args);
R11B008* func_00105F70(R11B008* ret, C8B* obj, s32 unused, R11B008* args);
R11B008* func_00106048(R11B008* ret, C8B* obj, s32 unused, R11B008* args);
R11B008* func_00106120(R11B008* ret, C23* obj, s32 unused, R11B008* args);
R11B008* func_001061C0(R11B008* ret, C23* obj, s32 unused, R11B008* args);
R11B008* func_00106270(R11B008* ret, C3C* obj, s32 unused, R11B008* args);
R11B008* func_00106320(R11B008* ret, C3C* obj, s32 unused, R11B008* args);
R11B008* func_001063D0(R11B008* ret, C62* obj, s32 unused, R11B008* args);
R11B008* func_001064C0(R11B008* ret, C47* obj, s32 unused, R11B008* args);
R11B008* func_00106560(R11B008* ret, C47* obj, s32 unused, R11B008* args);
R11B008* func_00106600(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_001066F0(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_001067A0(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_00106850(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_00106920(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_001069C0(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_00106A70(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_00106B10(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_00106BB0(R11B008* ret, C8C* obj, s32 unused, R11B008* args);
R11B008* func_00106C50(R11B008* ret, C65* obj, s32 unused, R11B008* args);
R11B008* func_00106CF0(R11B008* ret, C65* obj, s32 unused, R11B008* args);
R11B008* func_00106D90(R11B008* ret, C65* obj, s32 unused, R11B008* args);
R11B008* func_00106E60(R11B008* ret, C65* obj, s32 unused, R11B008* args);
R11B008* func_00106F00(R11B008* ret, C65* obj, s32 unused, R11B008* args);
R11B008* func_00106FA0(R11B008* ret, C5D* obj, s32 unused, R11B008* args);
R11B008* func_00107040(R11B008* ret, C8D* obj, s32 unused, R11B008* args);
R11B008* func_001070E0(R11B008* ret, C8D* obj, s32 unused, R11B008* args);
R11B008* func_00107180(R11B008* ret, C8D* obj, s32 unused, R11B008* args);
R11B008* func_00107268(R11B008* ret, C8D* obj, s32 unused, R11B008* args);
R11B008* func_00107350(R11B008* ret, C0C* obj, s32 unused, R11B008* args);
R11B008* func_001073F0(R11B008* ret, C17* obj, s32 unused, R11B008* args);
R11B008* func_001074C0(R11B008* ret, C19* obj, s32 unused, R11B008* args);
R11B008* func_00107570(R11B008* ret, C19* obj, s32 unused, R11B008* args);
R11B008* func_00107678(R11B008* ret, C19* obj, s32 unused, R11B008* args);
R11B008* func_00107718(R11B008* ret, C73* obj, s32 unused, R11B008* args);
R11B008* func_001077D8(R11B008* ret, C60* obj, s32 unused, R11B008* args);
R11B008* func_00107898(R11B008* ret, C0E* obj, s32 unused, R11B008* args);
R11B008* func_00107948(R11B008* ret, C24* obj, s32 unused, R11B008* args);
R11B008* func_00107A10(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107AB0(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107B60(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107C00(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107CB0(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107D60(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107E10(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107EC0(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00107F70(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00108038(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00108128(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00108208(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_001082E8(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_001083C8(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00108498(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_00108548(R11B008* ret, C8F* obj, s32 unused, R11B008* args);
R11B008* func_001085E8(R11B008* ret, C01* obj, s32 unused, R11B008* args);
R11B008* func_00108688(R11B008* ret, C4A* obj, s32 unused, R11B008* args);
R11B008* func_00108728(R11B008* ret, C4A* obj, s32 unused, R11B008* args);
R11B008* func_001087D8(R11B008* ret, C1B* obj, s32 unused, R11B008* args);
R11B008* func_00108878(R11B008* ret, C13* obj, s32 unused, R11B008* args);
R11B008* func_00108928(R11B008* ret, C13* obj, s32 unused, R11B008* args);
R11B008* func_001089C8(R11B008* ret, C13* obj, s32 unused, R11B008* args);
R11B008* func_00108A98(R11B008* ret, C13* obj, s32 unused, R11B008* args);
R11B008* func_00108B48(R11B008* ret, C13* obj, s32 unused, R11B008* args);
R11B008* func_00108BE8(R11B008* ret, C90* obj, s32 unused, R11B008* args);
R11B008* func_00108CC8(R11B008* ret, C90* obj, s32 unused, R11B008* args);
R11B008* func_00108DA8(R11B008* ret, C90* obj, s32 unused, R11B008* args);
R11B008* func_00108E70(R11B008* ret, C90* obj, s32 unused, R11B008* args);
R11B008* func_00108F38(R11B008* ret, C90* obj, s32 unused, R11B008* args);
R11B008* func_00109000(R11B008* ret, C90* obj, s32 unused, R11B008* args);
R11B008* func_001090C8(R11B008* ret, C0D* obj, s32 unused, R11B008* args);
R11B008* func_001091A8(R11B008* ret, C1D* obj, s32 unused, R11B008* args);
R11B008* func_00109258(R11B008* ret, C1D* obj, s32 unused, R11B008* args);
R11B008* func_00109308(R11B008* ret, C1D* obj, s32 unused, R11B008* args);
R11B008* func_001093B8(R11B008* ret, C4C* obj, s32 unused, R11B008* args);

R11B008* func_001000C8(R11B008* ret, void* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 7;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001300E8(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100178(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00182DD8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100218(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    obj->desc->m03(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001002C0(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    obj->desc->m02(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100368(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248D80;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B8A8(&q, func_00183058(obj, o1, o2));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100438(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    C01* out;
    func_0011B008(&q);
    kinds = 0x2000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    obj->desc->m15(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001004F0(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 flag = func_00182F40(obj, out);
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001005A0(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 flag = func_001833F0(obj, out);
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100650(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248D88;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00183910(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100720(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248D90;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00183990(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001007F0(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 a;
    f32 b;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248D98;
    (void)func_001C23B0(&t, 2, args, &kinds, &a, &b);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00183A10(obj, a, b);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001008B8(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    Quad16 vec;
    R11B008 t;
    s32 out;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248DA0;
    (void)func_001C23B0(&t, 2, args, &kinds, &out, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00183A90(obj, out, &vec);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100998(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    Quad16 vec;
    R11B008 t;
    s32 out;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248DA8;
    (void)func_001C23B0(&t, 2, args, &kinds, &out, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00183B20(obj, out, &vec);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100A78(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248DB0;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00183BB8(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100B48(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    Quad16 vec;
    R11B008 t;
    s32 out;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248DB8;
    (void)func_001C23B0(&t, 2, args, &kinds, &out, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00183C38(obj, out, &vec);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100C28(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001250C8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100CC8(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012A8B8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100D68(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012A8C8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100E08(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    f32 o0;
    f32 o1;
    s32 o2;
    Kinds3* np;
    f32* o0p;
    f32* o1p;
    s32* o2p;
    func_0011B008(&q);
    np = &kinds;
    o0p = &o0;
    o1p = &o1;
    o2p = &o2;
    kinds = *(Kinds3*)&D_00248DC0;
    (void)func_001C23B0(&t, 3, args, np, o0p, o1p, o2p);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012A8D8(obj, o2, o0, o1);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100EE0(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    f32 x;
    f32 y;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248DD0;
    (void)func_001C23B0(&t, 2, args, &kinds, &x, &y);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012AA50(obj, x, y);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00100FA8(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 f0;
    func_0011B008(&q);
    kinds = 1;
    func_001C23B0(&t, 1, args, &kinds, &f0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0012AAE8(obj, f0);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101058(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds5 kinds;
    Quad16 vec;
    R11B008 t;
    s32 i0;
    f32 f0, f1, f2;
    func_0011B008(&q);
    kinds = *(Kinds5*)&D_00248DD8;
    func_001C23B0(&t, 5, args, &kinds, &i0, &f0, &f1, &f2, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012AF38(obj, i0, &vec, f0, f1, f2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101168(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012B010(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101208(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 f0;
    func_0011B008(&q);
    kinds = 1;
    func_001C23B0(&t, 1, args, &kinds, &f0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00126CB8(obj, f0);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001012B8(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 f0;
    func_0011B008(&q);
    kinds = 1;
    func_001C23B0(&t, 1, args, &kinds, &f0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00126D60(obj, f0);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101368(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B8A8(&q, func_00129C20(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101418(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 y;
    func_0011B008(&q);
    s32* px = &kinds;
    s32* py = &y;
    *px = 6;
    func_001C23B0(&t, 1, args, px, py);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B8A8(&q, func_00129B98(obj, y));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001014C8(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B8A8(&q, func_00129CA8(obj));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101568(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    C02* y;
    func_0011B008(&q);
    s32* px = &kinds;
    C02** py = &y;
    *px = 0x2000;
    (void)func_001C23B0(&t, 1, args, px, py);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    obj->desc02()->m1F(obj, y);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101620(R11B008* ret, C02* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248D80;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0012B5B8(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001016F0(R11B008* ret, C03* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 y;
    func_0011B008(&q);
    s32* px = &kinds;
    s32* py = &y;
    *px = 0x1000;
    (void)func_001C23B0(&t, 1, args, px, py);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001BB1E0(obj, y);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001017A0(R11B008* ret, C03* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Quad4 vec;
    R11B008 t;
    s32 kinds;
    func_0011B008(&q);
    kinds = 2;
    func_001C23B0(&t, 1, args, &kinds, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_001BC670(obj, &vec);
    func_0011B5F0(&q, r);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101860(R11B008* ret, C73* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248DF0;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_001F42D0(obj, o0, o1, o2, o3);
    (void)r;
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101950(R11B008* ret, C73* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F4008(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001019F0(R11B008* ret, C7D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F4808(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101A90(R11B008* ret, C83* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    f32 o1;
    f32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)&D_00248E00;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    void* r = func_0012C7D8(obj, o0, o1, o2, o3);
    func_0011B8A8(&q, r);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101B80(R11B008* ret, C83* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds5 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    f32 o3;
    f32 o4;
    s32 o5;
    func_0011B008(&q);
    kinds = *(Kinds5*)&D_00248E10;
    (void)func_001C23B0(&t, 5, args, &kinds, &o1, &o2, &o3, &o4, &o5);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B8A8(&q, func_0012C8F8(obj, o1, o3, o4, o2, o5));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101C88(R11B008* ret, C83* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 v;
    func_0011B008(&q);
    kinds = 6;
    (void)func_001C23B0(&t, 1, args, &kinds, &v);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    f32 r = func_0012CCC0(obj, v);
    func_0011B5B0(&q, r);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101D38(R11B008* ret, Obj_101D38* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o0;
    f32 o1;
    f32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)&D_00248E28;
    (void)func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012F0A0(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101E10(R11B008* ret, void* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012E760(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101EB0(R11B008* ret, void* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 5;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012F190(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00101F60(R11B008* ret, void* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = D_00248E38;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0012E928(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102030(R11B008* ret, C1F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001EF830(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001020D0(R11B008* ret, C20* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    obj->desc20()->m48(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102178(R11B008* ret, C28* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248DF0;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_00140750(obj, o0, o1, o2, o3);
    (void)r;
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102268(R11B008* ret, C29* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248DF0;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_00140770(obj, o0, o1, o2, o3);
    (void)r;
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102358(R11B008* ret, C05* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00192418(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001023F8(R11B008* ret, C05* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 flag = obj->desc05()->m4B(obj, out);
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001024B0(R11B008* ret, C2F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00123AB0(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102560(R11B008* ret, C2F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248DF0;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_00123D08(obj, o0, o1, o2, o3);
    (void)r;
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102650(R11B008* ret, C30* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    void (*fn)(C30*, s32) = obj->desc30()->m49;
    if (fn != 0) {
        fn(obj, out);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102710(R11B008* ret, C30* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    void (*fn)(C30*) = obj->desc30()->m4A;
    if (fn != 0) {
        fn(obj);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001027C0(R11B008* ret, C31* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 out;
    func_0011B008(&q);
    kinds = 1;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001B0488(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102870(R11B008* ret, C31* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 out;
    func_0011B008(&q);
    kinds = 1;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001B0470(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102920(R11B008* ret, C50* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 out;
    func_0011B008(&q);
    kinds = 1;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00155F78(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001029D0(R11B008* ret, C50* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00155F90(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102A70(R11B008* ret, C50* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00155FA0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102B10(R11B008* ret, C50* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds6 kinds;
    R11B008 t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    func_0011B008(&q);
    kinds = *(Kinds6*)&D_00248E40;
    (void)func_001C23B0(&t, 6, args, &kinds, &i0, &i1, &f0, &f1, &f2, &f3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001557D0(obj, i0, i1, f0, f1, f2, f3);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102C28(R11B008* ret, C79* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds6 kinds;
    R11B008 t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    func_0011B008(&q);
    kinds = *(Kinds6*)&D_00248E40;
    (void)func_001C23B0(&t, 6, args, &kinds, &i0, &i1, &f0, &f1, &f2, &f3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00158D40(obj, i0, i1, f0, f1, f2, f3);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102D40(R11B008* ret, C7A* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00158730(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102DE0(R11B008* ret, C7A* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds6 kinds;
    Quad4 vec0;
    Quad4 vec1;
    R11B008 t;
    s32 i0;
    s32 i1;
    f32 f0;
    f32 f1;

    func_0011B008(&q);
    s32* pi0 = &i0;
    s32* pi1 = &i1;
    kinds = *(Kinds6*)&D_00248E58;
    (void)func_001C23B0(&t, 6, args, &kinds, pi0, pi1, &vec0, &vec1, &f0, &f1);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00158778(obj, i0, i1, &vec0, &vec1, f0, f1);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102F10(R11B008* ret, C78* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00158730(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00102FB0(R11B008* ret, C78* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds6 kinds;
    Quad4 vec0;
    Quad4 vec1;
    R11B008 t;
    s32 i0;
    s32 i1;
    f32 f0;
    f32 f1;

    func_0011B008(&q);
    kinds = *(Kinds6*)&D_00248E58;
    (void)func_001C23B0(&t, 6, args, &kinds, &i0, &i1, &vec0, &vec1, &f0, &f1);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00158778(obj, i0, i1, &vec0, &vec1, f0, f1);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001030E0(R11B008* ret, C88* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds3*)&D_00248E70;
    (void)func_001C23B0(&t, 3, args, &kinds, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    void* v = func_001B6290(obj, o1, o2, o3);
    func_0011B8A8(&q, v);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001031C0(R11B008* ret, void* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001B6438(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103260(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    Quad4 vec;
    R11B008 t;
    s32 a;
    s32 b;
    func_0011B008(&q);
    kinds = *(Kinds3*)&D_00248E80;
    (void)func_001C23B0(&t, 3, args, &kinds, &a, &b, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DD950(obj, a, b, &vec);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103350(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248E90;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001C09D8(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103420(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248E90;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001C08B0(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001034F0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001C0950(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103590(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0xF;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD690(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103640(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0xF;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD6B0(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001036F0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0xF;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD6D0(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001037A0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0xF;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD6F0(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103850(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0xF;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD710(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103900(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0xF;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD758(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001039B0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0xF;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD7A0(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103A60(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    void* o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds3*)&D_00248E98;
    (void)func_001C23B0(&t, 3, args, &kinds, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DD7E8(obj, o1, o2, o3);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103B40(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248EA8;
    func_001C23B0(&t, 2, args, &kinds, &out1, &out2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_001DD888(obj, out1, out2);
    func_0011B570(&q, r);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103C10(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD8E8(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103CC0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_001DD908(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103D70(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B570(&q, func_001DD928(obj));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103E10(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDAD0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103EB0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248EB0;
    (void)func_001C23B0(&t, 2, args, &kinds, &out1, &out2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDB20(obj, out1, out2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00103F80(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDB58(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104020(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDBB8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001040C0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 5;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 v = func_001DDBF8(obj, out);
    func_0011B570(&q, v);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104170(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x5;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001DDC18(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104220(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248EB8;
    (void)func_001C23B0(&t, 2, args, &kinds, &out1, &out2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DBAC0(obj, out1, out2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001042F0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 5;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 v = func_001DBAE0(obj, out);
    func_0011B570(&q, v);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001043A0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    Kinds2* pp;
    s32* o1;
    s32* o2;
    func_0011B008(&q);
    pp = &kinds;
    o1 = &out1;
    o2 = &out2;
    kinds = *(Kinds2*)D_00248EC0;
    (void)func_001C23B0(&t, 2, args, pp, o1, o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DBB00(obj, out1, out2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104470(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDA20(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104510(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDA50(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001045B0(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDC90(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104660(R11B008* ret, C6C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDC78(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104710(R11B008* ret, C6D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00145FB8(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001047C0(R11B008* ret, C6D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B570(&q, func_00145FD8(obj));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104860(R11B008* ret, C6D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 v = func_00145FF8(obj);
    func_0011B570(&q, v);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104900(R11B008* ret, C6D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o0;
    f32 o1;
    f32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248EC8;
    func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00146018(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001049D8(R11B008* ret, C6D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00146028(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104A78(R11B008* ret, C6D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001455F0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104B18(R11B008* ret, C6D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    Quad4 vec;
    R11B008 t;
    f32 fx;
    f32 fy;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248ED8;
    func_001C23B0(&t, 3, args, &kinds, &vec, &fx, &fy);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_00146038(obj, &vec, fx, fy));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104C00(R11B008* ret, C4E* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F4ED0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104CA0(R11B008* ret, C4E* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F4F20(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104D40(R11B008* ret, C36* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F5210(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104DE0(R11B008* ret, C2E* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00199AF0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104E80(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)func_001C23B0(&t, 2, args, &kinds, &out1, &out2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001CA608(obj, out1, out2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00104F50(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248EE8;
    func_001C23B0(&t, 2, args, &kinds, &out1, &out2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001CA658(obj, out1, out2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105020(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x1000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B8A8(&q, func_001CA6D0(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001050D0(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248EF0;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_001CAD60(obj, o0, o1, o2, o3);
    (void)r;
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001051C0(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    func_0011B008(&q);
    kinds = *(Kinds2*)&D_00248E38;
    (void)func_001C23B0(&t, 2, args, &kinds, &out1, &out2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001CA960(obj, out1, out2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105290(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 out1;
    s32 out2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)func_001C23B0(&t, 2, args, &kinds, &out1, &out2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001CA720(obj, out1, out2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105360(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = D_00248EB0;
    (void)func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001C8FD0(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105430(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    Kinds2* kp;
    s32* o1p;
    s32* o2p;
    func_0011B008(&q);
    kp = &kinds;
    o1p = &o1;
    o2p = &o2;
    kinds = *(Kinds2*)D_00248EE8;
    (void)func_001C23B0(&t, 2, args, kp, o1p, o2p);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001CA898(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105500(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    ((void (*)(void*))obj->desc08()->m61)(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001055A8(R11B008* ret, C08* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001CB328(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105658(R11B008* ret, C09* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001B70B0(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105728(R11B008* ret, C3B* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 out;
    func_0011B008(&q);
    kinds = 1;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0013BE00(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001057D8(R11B008* ret, C3B* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0013BF68(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105878(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    Quad4 vec;
    R11B008 t;
    f32 fx;
    f32 fy;
    Kinds3* kp;
    Quad4* vecp;
    f32* fxp;
    f32* fyp;
    func_0011B008(&q);
    kp = &kinds;
    vecp = &vec;
    fxp = &fx;
    fyp = &fy;
    kinds = *(Kinds3*)D_00248ED8;
    (void)func_001C23B0(&t, 3, args, kp, vecp, fxp, fyp);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00171F28(obj, &vec, fx, fy);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105960(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00171FE0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105A00(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001777F8(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105AB0(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001D2830(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105B60(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00177800(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105C10(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001D31D0(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105CC0(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001D6CB0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105D60(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001781E0(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105E10(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00178258(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105EC0(R11B008* ret, C07* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00178280(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00105F70(R11B008* ret, C8B* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    f32 o0;
    f32 o1;
    f32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248F00;
    (void)func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0019CE28(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106048(R11B008* ret, C8B* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    f32 o0;
    f32 o1;
    f32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248F00;
    (void)func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0019CE38(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106120(R11B008* ret, C23* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00150408(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001061C0(R11B008* ret, C23* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00150418(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106270(R11B008* ret, C3C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0018DD50(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106320(R11B008* ret, C3C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 7;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0018DD78(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001063D0(R11B008* ret, C62* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248DF0;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_001EF8C0(obj, o0, o1, o2, o3);
    (void)r;
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001064C0(R11B008* ret, C47* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0016DCF0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106560(R11B008* ret, C47* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0016DD00(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106600(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248F10;
    func_001C23B0(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 r = func_001A8150(obj, o0, o1, o2, o3);
    (void)r;
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001066F0(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A8778(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001067A0(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A87A8(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106850(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248F20;
    func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A87E0(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106920(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A8AF8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001069C0(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    s32 flag = func_001A8C90(obj, out);
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106A70(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A93E8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106B10(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A9438(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106BB0(R11B008* ret, C8C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A9498(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106C50(R11B008* ret, C65* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00150750(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106CF0(R11B008* ret, C65* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00150760(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106D90(R11B008* ret, C65* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = D_00248EA8;
    (void)func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001519E0(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106E60(R11B008* ret, C65* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001518B8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106F00(R11B008* ret, C65* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001519A8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00106FA0(R11B008* ret, C5D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001993C0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107040(R11B008* ret, C8D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F36E8(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001070E0(R11B008* ret, C8D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F3768(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107180(R11B008* ret, C8D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248F28;
    (void)func_001C23B0(&t, 4, args, &kinds, &x, &y, &z, &w);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F3928(obj, x, y, z, w);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107268(R11B008* ret, C8D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248F28;
    func_001C23B0(&t, 4, args, &kinds, &x, &y, &z, &w);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F3990(obj, x, y, z, w);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107350(R11B008* ret, C0C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0018AC58(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001073F0(R11B008* ret, C17* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0019AD30(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001074C0(R11B008* ret, C19* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DB110(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107570(R11B008* ret, C19* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds5 kinds;
    R11B008 t;
    s32 o1;
    f32 o2;
    f32 o3;
    s32 o4;
    s32 o5;
    func_0011B008(&q);
    kinds = *(Kinds5*)D_00248F38;
    (void)func_001C23B0(&t, 5, args, &kinds, &o1, &o2, &o3, &o4, &o5);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DB1E8(obj, o1, o2, o3, o4, o5);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107678(R11B008* ret, C19* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DB290(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107718(R11B008* ret, C73* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Quad4 vec;
    R11B008 t;
    s32 kinds;
    func_0011B008(&q);
    kinds = 2;
    func_001C23B0(&t, 1, args, &kinds, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_00141170(obj, &vec));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001077D8(R11B008* ret, C60* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Quad4 vec;
    R11B008 t;
    s32 kinds;
    func_0011B008(&q);
    kinds = 2;
    func_001C23B0(&t, 1, args, &kinds, &vec);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_0015AA50(obj, &vec));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107898(R11B008* ret, C0E* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B5F0(&q, func_00190660(obj, out));
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107948(R11B008* ret, C24* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 a;
    f32 b;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248F50;
    (void)func_001C23B0(&t, 2, args, &kinds, &a, &b);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00182948(obj, a, b);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107A10(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q, t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017CDE0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107AB0(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017CE20(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107B60(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q, t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017CE80(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107C00(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x6;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017CFC8(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107CB0(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x6;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017CFF0(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107D60(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x6;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D018(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107E10(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0017D040(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107EC0(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0017D078(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00107F70(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 a;
    f32 b;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248F58;
    (void)func_001C23B0(&t, 2, args, &kinds, &a, &b);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D0A0(obj, a, b);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108038(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds4 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    s32 o3;
    s32 o4;
    func_0011B008(&q);
    kinds = *(Kinds4*)D_00248F60;
    (void)func_001C23B0(&t, 4, args, &kinds, &o1, &o2, &o3, &o4);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D100(obj, o1, o2, o3, o4);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108128(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o1;
    f32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248F70;
    (void)func_001C23B0(&t, 3, args, &kinds, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D148(obj, o1, o3, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108208(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o1;
    f32 o2;
    s32 o3;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248F70;
    (void)func_001C23B0(&t, 3, args, &kinds, &o1, &o2, &o3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D180(obj, o1, o3, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001082E8(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248F80;
    func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D1B8(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001083C8(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248F90;
    (void)func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D0D8(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108498(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    f32 out;
    func_0011B008(&q);
    kinds = 1;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D1E8(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108548(R11B008* ret, C8F* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D220(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001085E8(R11B008* ret, C01* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00159ED0(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108688(R11B008* ret, C4A* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017B598(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108728(R11B008* ret, C4A* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 6;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0017B550(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001087D8(R11B008* ret, C1B* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017AD50(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108878(R11B008* ret, C13* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001ED018(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108928(R11B008* ret, C13* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED020(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001089C8(R11B008* ret, C13* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248F98;
    (void)func_001C23B0(&t, 2, args, &kinds, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED090(obj, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108A98(R11B008* ret, C13* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001ED0D8(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108B48(R11B008* ret, C13* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, args, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001EC528(obj);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108BE8(R11B008* ret, C90* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o0;
    f32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248FA0;
    (void)func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED558(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108CC8(R11B008* ret, C90* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o0;
    f32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248FB0;
    (void)func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED588(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108DA8(R11B008* ret, C90* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 n;
    f32 out;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)func_001C23B0(&t, 2, args, &kinds, &n, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED5B8(obj, n, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108E70(R11B008* ret, C90* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 n;
    f32 out;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)func_001C23B0(&t, 2, args, &kinds, &n, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED5D8(obj, n, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00108F38(R11B008* ret, C90* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 n;
    f32 out;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)func_001C23B0(&t, 2, args, &kinds, &n, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED5F8(obj, n, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00109000(R11B008* ret, C90* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 n;
    f32 out;
    func_0011B008(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)func_001C23B0(&t, 2, args, &kinds, &n, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001ED618(obj, n, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001090C8(R11B008* ret, C0D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds3 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    kinds = *(Kinds3*)D_00248FC8;
    (void)func_001C23B0(&t, 3, args, &kinds, &o0, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001A9C58(obj, o0, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001091A8(R11B008* ret, C1D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001C3F68(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00109258(R11B008* ret, C1D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001C4180(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00109308(R11B008* ret, C1D* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    R11B008 t;
    s32 kinds;
    s32 out;
    func_0011B008(&q);
    kinds = 0x2000;
    (void)func_001C23B0(&t, 1, args, &kinds, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001C41A0(obj, out);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001093B8(R11B008* ret, C4C* obj, s32 unused, R11B008* args)
{
    R11B008 q;
    Kinds2 kinds;
    R11B008 t;
    s32 o0;
    s32 o1;
    func_0011B008(&q);
    (void)func_001C23B0(&t, 2, args, (kinds = *(Kinds2*)D_00248FD8, &kinds), &o0, &o1);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001D32D8(obj, o0, o1);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

INCLUDE_ASM(func_00109488);
