// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "object_link.h"
#include "path_curve.h"

// The types of PathCurveVt's slots, for the tables at the end of this file.
typedef void (*PathLoad)(PathCurve* self, void* stream);
typedef void (*PathM01)(PathCurve* self, s32 a1, s32 a2);
typedef void (*PathM02)(PathCurve* self, s32 a1, s32 a2);
typedef void (*PathM03)(PathCurve* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5);
typedef void (*PathTransform)(PathCurve* self, void* a, void* b);
typedef f32 (*PathArcAt)(PathCurve* self, f32 t);
typedef f32 (*PathTimeAt)(PathCurve* self, f32 t);
typedef f32 (*PathLast)(PathCurve* self);
typedef f32 (*PathFill)(PathCurve* self);
typedef void (*PathM10)(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);
typedef void (*PathM11)(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
// Defined in src/main/path_curve.cpp.
f32 func_0014DB40();
f32 func_0014DB58();
void func_0014DD28();
void func_0014DE08();
void func_0014DE40();
void func_0014DE78();
void func_0014DF68();
f32 func_0014DF98();
f32 func_0014E000();
f32 func_0014E068();
void func_0014E090();
void func_0014E170();
void func_0014E2A0();
void func_0014E3D0();
void func_0014E5B8();
void func_0014E6A8();
void func_0014E710();
void func_0014E828();
f32 func_0014E910();
f32 func_0014E990();
void func_0014EA48();
void func_0014EB10();
void func_0014EC70();
void func_0014ED98();
extern const PathCurveVt D_002176D0 = { (PathLoad)func_0014DD28, (PathM01)func_0014DE08, (PathM02)func_0014DE40, (PathM03)func_0014DE78, (PathTransform)func_0014DF68, (PathArcAt)func_0014DF98, (PathTimeAt)func_0014E000, (PathLast)func_0014DB40, (PathLast)func_0014DB58, (PathFill)func_0014E068, (PathM10)func_0014E090, (PathM11)func_0014E170, (PathM11)func_0014E2A0, 0 };
extern const PathCurveVt D_00217708 = { (PathLoad)func_0014E3D0, (PathM01)func_0014E5B8, (PathM02)func_0014E6A8, (PathM03)func_0014E710, (PathTransform)func_0014E828, (PathArcAt)func_0014E910, (PathTimeAt)func_0014E990, (PathLast)func_0014DB40, (PathLast)func_0014DB58, (PathFill)func_0014EA48, (PathM10)func_0014EB10, (PathM11)func_0014EC70, (PathM11)func_0014ED98, 0 };
