// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "anim_curve.h"

// The dispatch tables func_00121160 gives each kind of curve: three functions, or one and a
// shared one, each table followed by a zero word.
void func_0011F0C8();
void func_0011EFC8();
void func_0011F180();
void func_0011F320();
void func_0011F210();
void func_0011F3E8();
void func_0011F478();
void func_0011F568();
void func_0011F620();
void func_0011EFB0();
void func_00120AA8();
void func_00120D58();
void func_00120110();
void func_00120130();
void func_001201D0();
void func_001201F0();
void func_001202C0();
void func_001202F0();
void func_00120360();
void func_00120388();
void func_001203A8();
void func_00120418();
void func_00120440();
extern const WeightCurveVt D_00219668 = { (WeightCurveEval)func_0011F0C8, (WeightCurveRead)func_0011EFC8, (WeightCurveTimes)func_0011F180, 0 };
extern const WeightCurveVt D_00219678 = { (WeightCurveEval)func_0011F320, (WeightCurveRead)func_0011F210, (WeightCurveTimes)func_0011F3E8, 0 };
extern const WeightCurveVt D_00219688 = { (WeightCurveEval)func_0011F478, (WeightCurveRead)func_0011F568, (WeightCurveTimes)func_0011F620, 0 };
extern const WeightCurveVt D_00219698 = { (WeightCurveEval)func_00120AA8, 0, (WeightCurveTimes)func_0011EFB0, 0 };
extern const WeightCurveVt D_002196A8 = { (WeightCurveEval)func_00120D58, 0, (WeightCurveTimes)func_0011EFB0, 0 };

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_0011FC20();
void func_0011FC90();
void func_0011FDB8();
void func_0011FDD8();
void func_0011FE40();
void func_0011FED8();
void func_0011EF48();
void func_00120470();
void func_0011FF08();
void* func_0011FFA8();
void func_0011FFD8();
void func_0011EF68();
void func_0011EF70();
void func_00120700();
extern const PositionCurveVt D_002196B8 = { (PositionCurveEval)func_0011FC20, (PositionCurveRead)func_0011FC90, (PositionCurveTimes)func_0011FDB8, 0 };
extern const PositionCurveVt D_002196C8 = { (PositionCurveEval)func_0011FDD8, (PositionCurveRead)func_0011FE40, (PositionCurveTimes)func_0011FED8, 0 };
extern const PositionCurveVt D_002196D8 = { (PositionCurveEval)func_00120470, 0, (PositionCurveTimes)func_0011EF48, 0 };
extern const RotationCurveVt D_002196E8 = { (RotationCurveEval)func_0011FF08, (RotationCurveGet)func_0011FFA8, (RotationCurveRead)func_0011FFD8, (RotationCurveTimes)func_00120110 };
extern const RotationCurveVt D_002196F8 = { (RotationCurveEval)func_00120130, (RotationCurveGet)func_001201D0, (RotationCurveRead)func_001201F0, (RotationCurveTimes)func_001202C0 };
extern const RotationCurveVt D_00219708 = { (RotationCurveEval)func_00120700, (RotationCurveGet)func_0011EF68, 0, (RotationCurveTimes)func_0011EF70 };
extern const ScaleCurveVt D_00219718 = { (ScaleCurveEval)func_001202F0, (ScaleCurveRead)func_00120360, (ScaleCurveTimes)func_00120388, 0 };
extern const ScaleCurveVt D_00219728 = { (ScaleCurveEval)func_001203A8, (ScaleCurveRead)func_00120418, (ScaleCurveTimes)func_00120440, 0 };
