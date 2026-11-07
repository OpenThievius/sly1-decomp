// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "base_object.h"
#include "cursor_animator.h"
void func_001B4AD0(CursorAnimator* self);

// Defined in src/main/anim_record.cpp.
struct DrawnPart;

extern const u8 D_00217410[];

f32 func_001B4B38(void);
AnimCursor* func_001B4B48(CursorAnimator* self, const AnimRecord* key);
void func_001B4B68(FrameRunAnimator* p, AnimatorParams* s);
void func_001B4BC8(FrameRunAnimator* p);
void func_001B4C30(FrameRunAnimator* p, f32 dt);
f32 func_001B4D18(FrameRunAnimator* p);
void func_001B4D48(FramePingPongAnimator* p, AnimatorParams* s);
void func_001B4DA8(FramePingPongAnimator* p);
void func_001B4E18(FramePingPongAnimator* p, f32 dt);
f32 func_001B4F18(FramePingPongAnimator* p);
void func_001B4F80(RandomJumpAnimator* p, AnimatorParams* s);
void func_001B4FC0(RandomJumpAnimator* self, f32 x);
void func_001B5060(AngleFrameAnimator* self, AnimatorParams* key);
void func_001B5108(AngleFrameAnimator* p);
void func_001B5160(AngleFrameAnimator* p, void* unused, DrawnPart* q);
void func_001B5200(ScrollAnimator* p, AnimatorParams* s);
void func_001B5278(ScrollAnimator* p, f32 t);
f32 func_001B5308(ScrollAnimator* p);
void func_001B5398(CircleAnimator* p, AnimatorParams* s);
void func_001B5400(CircleAnimator* self);
f32 func_001B5488(CircleAnimator* p);
void func_001B54D0(TriangleAnimator* self, AnimatorParams* src);
void func_001B5568(TriangleAnimator* self, void** out);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001B55C0();
extern const CursorAnimatorMethods D_0021E358 = { (AnimLoad)func_001B4B68, (AnimBind)func_001B4BC8, (AnimStep)func_001B4C30, (AnimProgress)func_001B4D18, 0, (AnimFind)func_001B4B48, 0, 0 };
extern const CursorAnimatorMethods D_0021E378 = { (AnimLoad)func_001B4D48, (AnimBind)func_001B4DA8, (AnimStep)func_001B4E18, (AnimProgress)func_001B4F18, 0, (AnimFind)func_001B4B48, 0, 0 };
extern const CursorAnimatorMethods D_0021E398 = { (AnimLoad)func_001B4F80, (AnimBind)func_001B4AD0, (AnimStep)func_001B4FC0, (AnimProgress)func_001B4B38, 0, (AnimFind)func_001B4B48, 0, 0 };
extern const CursorAnimatorMethods D_0021E3B8 = { (AnimLoad)func_001B5060, (AnimBind)func_001B5108, 0, (AnimProgress)func_001B4B38, (AnimFollow)func_001B5160, (AnimFind)func_001B4B48, 0, 0 };
extern const CursorAnimatorMethods D_0021E3D8 = { (AnimLoad)func_001B5200, (AnimBind)func_001B4AD0, (AnimStep)func_001B5278, (AnimProgress)func_001B5308, 0, (AnimFind)func_001B4B48, 0, 0 };
extern const CursorAnimatorMethods D_0021E3F8 = { (AnimLoad)func_001B5398, (AnimBind)func_001B4AD0, (AnimStep)func_001B5400, (AnimProgress)func_001B5488, 0, (AnimFind)func_001B4B48, 0, 0 };
extern const CursorAnimatorMethods D_0021E418 = { (AnimLoad)func_001B54D0, (AnimBind)func_001B4AD0, 0, (AnimProgress)func_001B4B38, (AnimFollow)func_001B55C0, (AnimFind)func_001B4B48, (AnimOutputs)func_001B5568, 0 };

extern const ClassHead D_002198E8 = { D_00217410, 0x93 };
