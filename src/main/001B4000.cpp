// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "c88.h"
#include "c54.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
void func_001B4AD0(CursorAnimator* self);

struct Vec2_1B5160 { f32 x; f32 y; };
struct Inner_1B5160 { u8 pad0[0x34]; s32 i34; };
struct Other_1B5160 {
    void* vt; u8 pad0[0xC]; Vec2_1B5160 vec; u8 pad1[0x60]; Inner_1B5160* p78;
};

struct Entry_2198E8 { const u8* f0; s32 f4; };
extern const Entry_2198E8 D_002198E8;
extern const u8 D_00217410[];

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
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
void func_001B5160(AngleFrameAnimator* p, void* unused, Other_1B5160* q);
void func_001B5200(ScrollAnimator* p, AnimatorParams* s);
void func_001B5278(ScrollAnimator* p, f32 t);
f32 func_001B5308(ScrollAnimator* p);
void func_001B5398(CircleAnimator* p, AnimatorParams* s);
void func_001B5400(CircleAnimator* self);
f32 func_001B5488(CircleAnimator* p);
void func_001B54D0(TriangleAnimator* self, AnimatorParams* src);
void func_001B5568(TriangleAnimator* self, void** out);
extern const Fn_Table D_0021E358[];
extern const Fn_Table D_0021E378[];
extern const Fn_Table D_0021E398[];
extern const Fn_Table D_0021E3B8[];
extern const Fn_Table D_0021E3D8[];
extern const Fn_Table D_0021E3F8[];
extern const Fn_Table D_0021E418[];

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001B55C0();
extern const Fn_Table D_0021E358[8] = { (Fn_Table)func_001B4B68, (Fn_Table)func_001B4BC8, (Fn_Table)func_001B4C30, (Fn_Table)func_001B4D18, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E378[8] = { (Fn_Table)func_001B4D48, (Fn_Table)func_001B4DA8, (Fn_Table)func_001B4E18, (Fn_Table)func_001B4F18, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E398[8] = { (Fn_Table)func_001B4F80, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B4FC0, (Fn_Table)func_001B4B38, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3B8[8] = { (Fn_Table)func_001B5060, (Fn_Table)func_001B5108, 0, (Fn_Table)func_001B4B38, (Fn_Table)func_001B5160, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3D8[8] = { (Fn_Table)func_001B5200, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B5278, (Fn_Table)func_001B5308, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3F8[8] = { (Fn_Table)func_001B5398, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B5400, (Fn_Table)func_001B5488, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E418[8] = { (Fn_Table)func_001B54D0, (Fn_Table)func_001B4AD0, 0, (Fn_Table)func_001B4B38, (Fn_Table)func_001B55C0, (Fn_Table)func_001B4B48, (Fn_Table)func_001B5568, 0 };

extern const Entry_2198E8 D_002198E8 = { D_00217410, 0x93 };
