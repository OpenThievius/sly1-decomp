// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "attachment.h"
#include "anim_curve.h"

// D_00219600: an attachment's table, then the base tables of the four families of animation
// curves (anim_curve.h), in the order of their factories; nothing refers to those four.
struct AttachmentAndCurveBases {
    T2195_Vt attachment;        // 0x00
    PositionCurveVt position;   // 0x28
    RotationCurveVt rotation;   // 0x38
    ScaleCurveVt scale;         // 0x48
    WeightCurveVt weight;       // 0x58
};

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001212D8();
void func_00121358();
void func_00122890();
void func_00122920();
void func_00122968();
void func_001229C0();
void func_001229E0();
f32 func_00122A00();
void func_00122A18();
void func_00122A80();
void func_00122B30();
void func_00122C48();
void func_00122CB0();
f32 func_00122D90();
void func_0011EF40();
void func_0011EF48();
void func_0011EF60();
void func_0011EF68();
void func_0011EF70();
void func_0011EF88();
void func_0011EF90();
void func_0011EFA8();
void func_0011EFB0();
void func_001214B8();
void func_00121568();
void func_00121580();
f32 func_001215A8();
void func_00122DA0();
void func_00122DE0();
extern const T2195_Vt D_002195B0 = { (AttachInit)func_00122890, (AttachCopy)func_001212D8, (AttachRelease)func_00121358, 0, (AttachGetPos)func_00122920, (AttachGetRot)func_00122968, (AttachGetValue)func_001229C0, (AttachGetMatrix)func_001229E0, (AttachGetIndexed)func_00122A00, 0 };
extern const T2195_Vt D_002195D8 = { (AttachInit)func_00122A18, (AttachCopy)func_001212D8, (AttachRelease)func_00121358, 0, (AttachGetPos)func_00122A80, (AttachGetRot)func_00122B30, (AttachGetValue)func_00122C48, (AttachGetMatrix)func_00122CB0, (AttachGetIndexed)func_00122D90, 0 };
extern const AttachmentAndCurveBases D_00219600 = {
    { (AttachInit)func_00122DA0, (AttachCopy)func_001212D8, (AttachRelease)func_00121358, 0, (AttachGetPos)func_001214B8, (AttachGetRot)func_00122DE0, (AttachGetValue)func_00121568, (AttachGetMatrix)func_00121580, (AttachGetIndexed)func_001215A8, 0 },
    { (PositionCurveEval)func_0011EF40, 0, (PositionCurveTimes)func_0011EF48, 0 },
    { (RotationCurveEval)func_0011EF60, (RotationCurveGet)func_0011EF68, 0, (RotationCurveTimes)func_0011EF70 },
    { (ScaleCurveEval)func_0011EF88, 0, (ScaleCurveTimes)func_0011EF90, 0 },
    { (WeightCurveEval)func_0011EFA8, 0, (WeightCurveTimes)func_0011EFB0, 0 },
};

void func_00121338();
void func_00122F88();
void func_00122F28();
void func_00122FE0();
void func_00123120();
void func_00123270();
void func_001232E8();
void func_00123358();
extern const T2195_Vt D_002197C0 = { (AttachInit)func_00121338, (AttachCopy)func_00122F88, (AttachRelease)func_00122F28, 0, (AttachGetPos)func_00122FE0, (AttachGetRot)func_00123120, (AttachGetValue)func_00123270, (AttachGetMatrix)func_001232E8, (AttachGetIndexed)func_00123358, 0 };
