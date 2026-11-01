// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct RandomState_1F6708 { u8 pad[0x58]; u32 state; };
extern RandomState_1F6708* D_0027696C;

u32 func_001F6708(void)
{
    u32 state = D_0027696C->state * 0x41C64E6Du + 0x3039u;
    D_0027696C->state = state;
    return state & 0x7FFFFFFFu;
}

// NEAR: loop tail keeps addiu a0 before bnez with a nop in its slot; ours fills the slot, so the beqz target is one word short

s32 func_001F6F00(s32* dst, const s32* src, u32 bytes)
{
    u32 n = bytes >> 2;
    u32 i = 0;
    if (n != 0) {
        do {
            s32 v = *src;
            i++;
            src++;
            *dst++ = v;
        } while (i < n);
    }
    return 0;
}

// NEAR: retail saves ra with sd and has no float spills (ours spills $f12-$f18 for the variadic wrapper, 72 vs 56 bytes); ap offset matches

struct Out_1F7B50;
s32 func_001F7588(Out_1F7B50* out, void* ap);

s32 func_001F7B50(Out_1F7B50* out, ...)
{
    void* ap = (char*)__builtin_next_arg(out) - 56;
    return func_001F7588(out, ap);
}

// NEAR: frame layout and a1..a7 spill match; ours adds swc1 spills of f12..f18 (varargs floats) and saves s0/s1/ra with sq instead of sd

extern s32 D_00277130;
void func_001F72A8(void);
s32 func_001F7588(void* self, void* ap);

s32 func_001F7B88(void* self, ...)
{
    void* ap = (char*)__builtin_next_arg(self) - 56;
    s32 saved = D_00277130;
    D_00277130 = (s32)func_001F72A8;
    s32 r = func_001F7588(self, ap);
    D_00277130 = saved;
    return r;
}

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

void func_001FA468();
extern u32 D_00277134;

void func_001F7D88() { func_001FA468(); D_00277134 = 0; }

// NEAR: body EXACT; only the save/restore ops differ: retail sd/ld, default flags give sq/lq

typedef void (*Fn_1F7EA8)(s32 arg);
struct Node_1F7EA8 {
    s32 f0;
    u8 pad4[4];
    s32 f8;
    u8 pad12[8];
    s32 f14;
    s32 f18;
    Fn_1F7EA8 f1C;
    s32 f20;
    s32 f24;
};
struct Obj_1F7EA8 { u8 pad[0x1C]; Node_1F7EA8* node; s32 tag; s32 v24; s32 v28; s32 v2C; };
struct Ref_1F7EA8;
void func_001F6B50(Ref_1F7EA8* a);
void func_001F7E58(Ref_1F7EA8* a);

void func_001F7EA8(Obj_1F7EA8* obj) {
    Node_1F7EA8* s0;
    u32 tag = obj->tag;
    if (tag == 0x8000000A) goto call_path;
    if (tag > 0x8000000A) {
        s0 = obj->node;
        goto after;
    }
    if (tag == 0x80000009) goto set_fields;
    s0 = obj->node;
    goto after;
call_path:
    s0 = obj->node;
    if (s0->f1C != 0) {
        s0->f1C(s0->f20);
        s0 = obj->node;
    }
    goto after;
set_fields:
    s0 = obj->node;
    s0->f24 = obj->v24;
    s0->f14 = obj->v28;
    s0->f18 = obj->v2C;
after:
    s32 a0 = s0->f8;
    if (a0 >= 0) func_001F6B50((Ref_1F7EA8*)a0);
    func_001F7E58((Ref_1F7EA8*)s0->f0);
    s0->f0 = 0;
}
