// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 489/632 (77.4%), checked 2026-11-07
#include "common.h"
#include "effect_spawner.h"
#include "asm_func.h"
#include "vu0.h"
#include "effect_owner.h"
#include "effect.h"
#include "shapes.h"
#include "active_set_solver.h"
#include "list_iter.h"
#include "transform_object.h"
#include "object_group.h"
#include "cursor_animator.h"
#include "object_cycler.h"
#include "c60.h"
#include "world.h"
#include "globals.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "base_object.h"
#include "packet_writer.h"
#include "font.h"
#include "render_frame.h"
#include "text_reader.h"
#include "layout_137228.h"
// NEAR (2026-11-07, worker vu0-c): every instruction but the loop's constants. Retail keeps
// -1.0 in s8 for the qmtc2 (lui s8, 0xBF80 before the loop) and 3 in s6, comparing with 2 from
// v1; here the -1.0 is built in the loop (lui v0) and 2 is kept in s6, 3 in s7, so the saved
// registers shift. FromFloat substitutes the constant into its asm, which reload loads after
// loop optimization; a FromFloat that copies its float (or its bits, a union) first gives the
// constant a pseudo but costs elsewhere (docs/TOOLCHAIN.md, "The VU0 helpers"). The spin is read
// into a u128 before the select of the arm: retail loads it before the branch, and so ties the
// cross product's result to the arm. The literal 3.40282347e+38 is retail's D_0024A144.

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))
extern f32 g_gameClock[];
void* FillMemory(void* p, s32 v, u32 n);
void* AllocateBackMemory(s32 size);
struct SpawnSetup {
    s32 out[4];
    s32 flag;
    s32 pad[3];
    s32 pair[2];
    u8 tail[0x18];
};
struct SpawnFrame {
    Vec02 pos;              // 0x00
    Mat02 rot;              // 0x10
    Vec02 vel;              // 0x40
    Vec02 spin;             // 0x50
    SpawnFrame() { FillMemory(this, 0, sizeof(*this)); }
};
void func_001579B0(s32 n, Rec50* rec, SpawnSetup* out);

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);
void ComputeChainedWorldFrame(Rec50* self, Vec02* pos, Mat02* rot);
void ComputeObjectFrameAtTime(void* self, void* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);

void func_00157B88(s32 n, void* owner, SpawnSetup* first, SpawnSetup* second)
{
    SpawnFrame frame;
    Vec02 P;
    Vec02 V;
    Vec02 W;
    Mat02 M;
    Vec02 tmp;
    Rec50* r = AT(Rec50*, owner, 0x18C);
    Rec50* sub = AT(Rec50*, r, 0x90);
    void* saved = sub->target;
    if (AT(s32, r, 0x94) == -1) {
        sub->target = AT(void*, r, 0x18);
    }
    if (AT(Rec50*, r, 0x90)->target == AT(void*, r, 0x18)) {
        ComputeChainedWorldFrame(r, &frame.pos, &frame.rot);
        AT(SpawnFrame*, AT(Rec50*, r, 0x90), 0x78) = &frame;
    }
    second->flag = 0;
    func_001579B0(n, AT(Rec50*, r, 0x90), second);
    AT(SpawnFrame*, AT(Rec50*, r, 0x90), 0x78) = 0;
    f32 last = 3.40282347e+38f;
    for (s32 i = 0; i < n; i++) {
        if (AT(Rec50*, r, 0x90)->target != 0) {
            f32 t = ((f32*)first->out[3])[i] - g_gameClock[1];
            if (!AreFloatsNearlyEqual(t, last, 0.0001f)) {
                last = t;
                ComputeObjectFrameAtTime(AT(Rec50*, r, 0x90)->target, 0, last, &P, &M, &V, &W);
            }
            Vec02* p = (Vec02*)(i * 16 + second->out[0]);
            Vu0::Set(tmp, Vu0::Rotate(M, Vu0::Q(*p)));
            Vu0::Q(*p) = Vu0::Add(Vu0::Q(P), *(u128*)&tmp);
            s32 kind = AT(s32, AT(Rec50*, r, 0x90), 0x80);
            if (kind != 3) {
                Vec02* v = (Vec02*)(i * 16 + second->out[1]);
                Vu0::Q(*v) = Vu0::Rotate(M, Vu0::Q(*v));
                if (kind != 2) {
                    u128 moved = Vu0::Add(Vu0::Q(*(Vec02*)(i * 16 + second->out[1])), Vu0::Q(V));
                    u128 spin = Vu0::Q(W);
                    Vu0::Q(*(Vec02*)(i * 16 + second->out[1])) = Vu0::Add(moved,
                        Vu0::Cross(spin, Vu0::Q(kind == 1 ? *(Vec02*)(second->out[0] + i * 16) : tmp)));
                }
            }
        }
        Vu0::Q(tmp) = Vu0::FromFloat(-1.0f);
        Vu0::Q(*(Vec02*)(i * 16 + second->out[1])) = Vu0::MulX(Vu0::Q(*(Vec02*)(i * 16 + second->out[1])), Vu0::Q(tmp));
    }
    AT(Rec50*, r, 0x90)->target = saved;
}
