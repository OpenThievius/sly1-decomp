// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "screen_element.h"

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
extern const T217D_Vt D_00217E30 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00217E80 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00217ED0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00217F20 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00217F70 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001ABE40, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00217FC0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001ABE50, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218010 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218060 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002180B0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218100 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218150 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002181A0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001ABE60, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002181F0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218240 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218290 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AAF88, (ElementFn)func_001AB058, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB198, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AB5D8, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002182E0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001ABE70, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AC0E8, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218380 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AC888, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AC910, (ElementFn)func_001ACAA8, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001ACA30, (ElementFn)func_001ACA68, (ElementIntFn)func_001AC990, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AC9E0, 0 };
extern const T217D_Vt D_002183D0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001ACDA0, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001ACE38, (ElementFn)func_001AD3F0, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AD378, (ElementFn)func_001AD3B0, (ElementIntFn)func_001AD320, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218420 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AD6A8, (ElementFn)func_001AD718, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AD7B0, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218470 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001ADC60, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001ADD28, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002184C0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001ADF28, (ElementFn)func_001AE178, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AE220, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AE130, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218510 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AB600, (ElementFn)func_001AB660, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AB710, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218560 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AD940, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001ADB00, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AD970, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002185B0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AE510, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AE5E0, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218600 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AE758, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001AA790, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AE7F8, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002186D0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_00193E58, (ElementFn)func_001AA298, (ElementIntFn)func_001940E8, (ElementPadFn)func_001943E8, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_00194F80, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_00194F00, (ElementFn)func_00194F38, (ElementIntFn)func_00194E60, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00218720 = { (ElementIntFn)func_0014ABD0, (ElementFn)func_0014AC48, (ElementFn)func_0014AD70, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_0014ADE0, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_0014AD00, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_0021A3F0 = { (ElementIntFn)func_001E5E70, (ElementFn)func_001E6188, (ElementFn)func_001E77C0, 0, 0, (ElementFn)func_001E8840, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001E73B8, (ElementFn)func_001E7C60, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001E76E0, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_0021A440 = { (ElementIntFn)func_001310F0, (ElementFn)func_00131198, (ElementFn)func_001AA298, (ElementIntFn)func_00136238, (ElementPadFn)func_00136040, (ElementFn)func_001363D0, (ElementFn)func_00136EF8, (ElementFn)func_00136FA8, (ElementTextFn)func_00136408, (ElementFn)func_001366A0, 0, (ElementTimeFn)func_001365F0, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_00136648, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_00135550, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00220BF0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001AA268, (ElementFn)func_001AA298, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001821B0, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002210F0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001F1960, (ElementFn)func_001AA298, (ElementIntFn)func_001F1C90, (ElementPadFn)func_001F1A08, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001F20A8, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_002212E0 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_0016B4A0, (ElementFn)func_0016B560, (ElementIntFn)func_0016B7A8, (ElementPadFn)func_0016B580, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_0016B860, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00221330 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_0016BA40, (ElementFn)func_001AA298, (ElementIntFn)func_0016BDD0, (ElementPadFn)func_0016BBA8, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_0016BEA0, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };
extern const T217D_Vt D_00221380 = { (ElementIntFn)func_001AA1F0, (ElementFn)func_001DFEB8, (ElementFn)func_001E00B0, 0, 0, (ElementFn)func_001AA8C8, 0, 0, (ElementTextFn)func_001AA4F0, (ElementFn)func_001E0678, 0, (ElementTimeFn)func_001AA898, (ElementTimeFn)func_001AA8A0, (ElementTimeFn)func_001AA8A8, (ElementFn)func_001AA8F0, (ElementFn)func_001AA958, (ElementIntFn)func_001AA998, (ElementClockFn)func_001AAF58, (ElementPairFn)func_001AAAC8, 0 };

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
