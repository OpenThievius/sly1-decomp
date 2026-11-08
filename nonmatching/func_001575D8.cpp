// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 960/980, checked 2026-11-07
// NEAR: the frame (0xD0), the calls, the loop shape (a `while` whose test acquires the next chunk)
//       and the VU0 dot are retail's. The induction variables are not: retail walks the record
//       array with $s0 and the previous-frame arrays with their own $s2, counts with $s3 and keeps
//       the element index and the source pointers on the stack; ours folds the three previous-frame
//       arrays into $s0's offsets. About 20 compiles (the chunk as a struct of arrays, a walking
//       pointer for the previous frame, the unsigned count test).
#include "common.h"
#include "effect_owner.h"
#include "effect.h"
#include "globals.h"
#include "vu0.h"

struct Rec50;
struct EffectOwnerSlot { u8 pad[4]; s32* f4; s32 f8; };
void func_0013A128(void*, void*);
f32 RandomFloatInRange(f32 a, f32 b);
#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))

EffectOwner* ResetFirstListedObject(void);
EffectOwner* AcquireOwnedRecord(EffectOwner* set);
s32 RandomIntInRange(s32 lo, s32 hi);
void* FillMemory(void* p, s32 v, u32 n);

struct ParticleChunk {
    Quad16 pos[0x2C];       // 0x000
    Quad16 vel[0x2C];       // 0x2C0
    Quad16 rec[0x2C];       // 0x580
    Quad16 posPrev[0x2C];   // 0x840
    Quad16 velPrev[0x2C];   // 0xB00
    Quad16 recPrev[0x2C];   // 0xDC0
    s32 f1080;
    u32 count;              // 0x1084
    Quad16* extra;          // 0x1088: 32-byte entries
    s32 f108C;
    ParticleChunk* next;    // 0x1090
};

void func_001575D8(Rec50* self, EffectOwnerSlot* h, s32 n, Quad16* pos, Quad16* vel, f32* size, f32* spin, Quad16* e, Quad16* g)
{
    EffectOwner* set = 0;
    s32 i;
    ParticleChunk* chunk;
    if (h) {
        if (h->f4) set = (EffectOwner*)*h->f4;
    }
    if (!set) {
        u8* world = (u8*)g_currentWorld;
        if (AT(s32, world, 0x1B48) == 0) return;
        if (AT(s32, self, 0x130) == 2) {
            if (AT(s32, world, 0x1B54) == 0) return;
        }
        set = ResetFirstListedObject();
        if (!set) return;
        if (h) {
            if (h->f4) *h->f4 = (s32)set;
        }
        func_0013A128(set, self);
        if (h) {
            if (h->f8) {
                typedef void (*F)(EffectOwner*, s32);
                (*(F*)(AT(u8*, set, 0) + 0x6C))(set, h->f8);
            }
        }
        if (!set) return;
    }
    chunk = AT(ParticleChunk*, set, 0x624);
    i = 0;
    while (i < n && (chunk != 0 || (chunk = (ParticleChunk*)AcquireOwnedRecord(set)) != 0)) {
        u32 k = chunk->count;
        if (k < 0x2C && i < n) {
            do {
                Quad16* rec = &chunk->rec[k];
                chunk->pos[k] = pos[i];
                AT(f32, &chunk->pos[k], 0xC) = size[i];
                chunk->vel[k] = vel[i];
                AT(f32, &chunk->vel[k], 0xC) = spin[i];
                FillMemory(rec, 0, 0x10);
                s32 r = RandomIntInRange(0, AT(s32, set, 0x590) - 1);
                AT(s32, rec, 0) = r;
                if (AT(s32, set, 0x614) != 0) AT(s32, rec, 0) = r & ~1;
                if (AT(s32, self, 0x178) != 0) AT(s32, rec, 4) = RandomIntInRange(0, AT(s32, set, 0x384) - 1);
                if (AT(s32, set, 0x618) == 2) {
                    f32 f = RandomFloatInRange(AT(f32, self, 0x19C), AT(f32, self, 0x1A0));
                    AT(f32, rec, 8) = f;
                    if (AT(s32, self, 0x198) == 0) {
                        if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(AT(Quad16, g_camera, 0x90)), Vu0::Q(chunk->vel[k])))) AT(f32, rec, 8) = -f;
                    }
                    if (AT(s32, self, 0x1A4) != 0) AT(f32, rec, 0xC) = RandomFloatInRange(-3.14159274f, 3.14159274f);
                }
                if (AT(s32, set, 0x320) == 2) {
                    Quad16* arr = chunk->extra;
                    AT(Quad16, arr, k * 32) = e[i];
                    AT(Quad16, arr, k * 32 + 0x10) = g[i];
                }
                chunk->posPrev[k] = chunk->pos[k];
                chunk->velPrev[k] = chunk->vel[k];
                chunk->recPrev[k] = *rec;
                chunk->count = chunk->count + 1;
                AT(s32, set, 0x620) = AT(s32, set, 0x620) + 1;
                k++;
                i++;
            } while (k < 0x2C && i < n);
        }
        chunk = chunk->next;
    }
}
