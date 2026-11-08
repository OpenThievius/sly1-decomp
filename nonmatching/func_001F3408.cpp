// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 760/736, checked 2026-11-08
#include "oscillator.h"
#include "game_clock.h"
#include "vu0.h"
#include "common.h"
// NEAR (2026-11-07, night-loop): EvaluateOscillator, written whole. Its loop as retail's (194 real insns at the loop pass with the vectors as Vu0::Vec values, docs/TOOLCHAIN.md "Loops": li 0xD0; mult and 2pi stay in the loop, 1.0 alone is hoisted, into f21), the kinds a switch, sin and cos two locals (put last in the frame, at 0x70/0x74), the weight stores c, s, c, s, c. Still differs, 26 lines of scheduling: after ComputeSinCos retail moves the cosine into vf3 before the sine's mfc1 (v0, after it), where ours does the sine's mfc1 first, into v1; and the last weighted sum loads v30 before v50 (ours v50 first). Neither the order of the weight arguments, nor named weights, nor the sine's bits through a union moved it.
struct NoiseOctave { f32 w; f32 x; f32 y; f32 z; };
struct NoiseBlend { f32 lo; f32 hi; f32 scale; s32 count; NoiseOctave items[1]; };
f32 EvaluateNoiseBlend(NoiseBlend* obj);

// An entry of the oscillator (0xD0 bytes at +0x50): a sine (kind 0) turns the frame rows it owns
// by the sine and cosine of the clock times f68 plus f6C; a noise blend (kind 1) sets its frame
// to an axis-angle matrix of two noise values, less the identity.
struct OscillatorEntry {
    s32 kind;               // 0x00: 0 a sine, 1 a noise blend
    s32 frame;              // 0x04: the frames it writes (Oscillator's framesA and framesB)
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10: kind 1: the axis turned by the first matrix
    Vec02 v20;              // 0x20: kind 1: the first matrix's axis
    Vec02 v30;              // 0x30: kind 1: a NoiseBlend (the second angle)
    Vec02 v40;              // 0x40
    Vec02 v50;              // 0x50
    s32 row;                // 0x60: kind 0: the first of the two rows it writes
    f32 scale;              // 0x64
    f32 f68;                // 0x68
    f32 f6C;                // 0x6C
    u8 pad70[0x80 - 0x70];
    u8 blend80[0xD0 - 0x80]; // 0x80: kind 1: a NoiseBlend (the first angle)
};

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void ComputeSinCos(f32 x, f32* sinOut, f32* cosOut);
void RefreshOscillatorFrames(Oscillator* self);

void EvaluateOscillator(Oscillator* self)
{
    if (g_gameClock.time == self->lastTime) {
        return;
    }
    if (self->framesDirty != 0) {
        RefreshOscillatorFrames(self);
    }
    for (s32 i = 0; i < self->entryCount; i++) {
        OscillatorEntry* e = (OscillatorEntry*)((u8*)self + 0x50) + i;
        OscillatorFrame* fa = &self->framesA[e->frame];
        OscillatorFrame* fb = &self->framesB[e->frame];
        switch (e->kind) {
        case 0: {
            f32 phase = g_gameClock.time * e->f68 + e->f6C;
            f32 sn, cs;
            ComputeSinCos(phase * 6.2831855f, &sn, &cs);
            Vec02 a;
            Vec02 b;
            s32 row = e->row;
            Vu0::Set(a, Vu0::MulXSum(Vu0::Vec::Of(e->v20), Vu0::Vec::ScalarAt(cs), Vu0::Vec::Of(e->v40), Vu0::Vec::Scalar(sn)).q);
            fa->r[row].x = a.x;
            fa->r[row].y = a.y;
            fa->r[row].z = a.z;
            Vu0::Set(a, Vu0::MulXSum(Vu0::Vec::Of(e->v20), Vu0::Vec::FromFloat(-sn), Vu0::Vec::Of(e->v40), Vu0::Vec::ScalarAt(cs)).q);
            fa->r[row + 1].x = a.x;
            fa->r[row + 1].y = a.y;
            fa->r[row + 1].z = a.z;
            Vu0::Set(b, Vu0::MulXSum(Vu0::Vec::Of(e->v30), Vu0::Vec::ScalarAt(cs), Vu0::Vec::Of(e->v50), Vu0::Vec::Scalar(sn)).q);
            fb->r[row].x = b.x;
            fb->r[row].y = b.y;
            Vu0::Set(b, Vu0::MulXSum(Vu0::Vec::Of(e->v30), Vu0::Vec::FromFloat(-sn), Vu0::Vec::Of(e->v50), Vu0::Vec::ScalarAt(cs)).q);
            fb->r[row + 1].x = b.x;
            fb->r[row + 1].y = b.y;
            break;
        }
        case 1: {
            f32 angle = EvaluateNoiseBlend((NoiseBlend*)&e->v30);
            Mat02 m;
            Mat02 turn;
            Vec02 axis;
            f32 tilt = EvaluateNoiseBlend((NoiseBlend*)e->blend80);
            BuildAxisAngleMatrix(&e->v20, &turn, tilt);
            Vu0::Set(axis, Vu0::Rotate(turn, Vu0::Vec::Of(e->v10)).q);
            BuildAxisAngleMatrix(&axis, &m, angle);
            fa->r[0].x = m.r[0].x - 1.0f;
            fa->r[0].y = m.r[0].y;
            fa->r[0].z = m.r[0].z;
            fa->r[1].x = m.r[1].x;
            fa->r[1].y = m.r[1].y - 1.0f;
            fa->r[1].z = m.r[1].z;
            fa->r[2].x = m.r[2].x;
            fa->r[2].y = m.r[2].y;
            fa->r[2].z = m.r[2].z - 1.0f;
            break;
        }
        }
    }
    self->lastTime = g_gameClock.time;
}
