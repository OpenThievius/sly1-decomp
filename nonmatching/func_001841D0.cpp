// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1424/1428 (99.7%), checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 1 (source line 88); 25 differing lines before, 4 now.
// NEAR (2026-11-08): RefreshConeVolumeShape (func_001841D0): retail's size and frame, regdiff order, 95.2% in src/main/base_object.cpp. What got there: the locals declared where they are first used (the colour's Scalar slot freed at 0x40 and taken by each case's own vector, fit after it), the side planes counted upward (loop.c walks them with a pointer and counts down), the far and near planes' vectors stored through self and their distances through references taken before the loop (retail's v1, a1), 1.0 and 0.0 as named locals (f20, f21), the default ramp written [0][0], [1][0], [0][1], [1][1]. Still differs: the schedule around the far plane (retail loads rangeMax before the axis and the 50.0 before the store), and the two spilled addresses of the last FitUnitRampBetweenPair call take each other's slot (retail 0x144 for &rangeMin, 0x140 for &ramp[1][3]): their pseudos come from GCSE's hoisting in the order the expressions first appear. Needs the ConeVolume fields this branch adds (shape, hsv, planes, basis, packetSize, packet).
// In the context of its file, src/main/base_object.cpp.
#include "common.h"
#include "vu0.h"
#include "packet_writer.h"
#include "cone_volume.h"

struct LinePoints { f32 x; f32 y; };
void NoteConeVolumeLightingChange(ConeVolume* self);
void FitReciprocalThroughPoints(f32* out, s32* flag, f32 x, f32 y, f32 z, f32 w);
void FitUnitRampBetweenPair(LinePoints* self, f32* out0, f32* out1);
void FitLineThroughAngleSamples(f32 a, f32 b, f32 c, f32 d, f32* out0, void* out1);
void InitPacketWriter(PacketWriter* p);
void UsePacketBufferMemory(PacketWriter* p, s32 n, void* q);
void CopyWordsToWriter(PacketWriter* p, s32 size, s32 count, void* data, s32 addr);
void WriteVifMscal(PacketWriter* p, void* code);
void WriteVifFlushE(PacketWriter* p);
void DetachPacketBuffer(PacketWriter* p, u32* outCount, u8** outBegin);
void ConvertHsv255ToRgb255(Vec02* hsv, Vec02* rgb);
void TransformDirectionBetweenFrames(void* frame, s32 zero, void* in, Vec02* out);
void BuildBasisFromXAndZHint(void* x, void* z, void* out);
void func_001443C8(Mat02* m, Vec02* out, f32 x, f32 y);
void BuildProjectionMatrix(f32 (*out)[4], f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void BuildViewProjectionMatrix(void* pos, void* basis, f32 (*proj)[4], f32 (*out)[4]);
extern u8 D_00000BF0[];
extern u8 D_00000D30[];
extern u8 D_00000EF0[];

void RefreshConeVolumeShape(ConeVolume* self)
{
    PacketWriter w;
    InitPacketWriter(&w);
    NoteConeVolumeLightingChange(self);
    if (0.0001f < self->firstAngle && 0.0001f < self->hsv.z) {
        self->shape = 2;
    } else if (0.0001f < self->secondAngle && 0.0001f < self->secondLevel) {
        self->shape = 1;
    } else {
        self->shape = 0;
    }
    UsePacketBufferMemory(&w, 0x20, self->packet);
    Vec02 c;
    if (0.0001f < self->hsv.z) {
        ConvertHsv255ToRgb255(&self->hsv, &c);
        Vu0::Q(c) = Vu0::MulX(Vu0::Q(c), Vu0::Scalar(1.0f / self->hsv.z));
    } else {
        Vu0::Q(c) = Vu0::Zero();
    }
    CopyWordsToWriter(&w, 0xC, 1, &c, 0x16);
    f32 fit[2][4];
    FitLineThroughAngleSamples(self->firstAngle, 0.0f, 0.0f, self->hsv.z, &fit[1][2], &fit[0][2]);
    FitLineThroughAngleSamples(self->secondAngle, 0.0f, 0.0f, self->secondLevel, &fit[1][1], &fit[0][1]);
    FitLineThroughAngleSamples(360.0f - self->thirdAngle, 0.0f, 360.0f, self->thirdLevel, &fit[1][0], &fit[0][0]);
    CopyWordsToWriter(&w, 0xC, 2, fit, 0x17);
    switch (self->mode) {
    case 0: {
        Vec02 d;
        TransformDirectionBetweenFrames(self, 0, &self->q320, &d);
        CopyWordsToWriter(&w, 8, 1, &d, 0x19);
        WriteVifMscal(&w, D_00000BF0);
        break;
    }
    case 1: {
        f32 r[4];
        FitReciprocalThroughPoints(&r[0], (s32*)&r[1], self->rangeMin, 1.0f, self->rangeMax, 0.0f);
        CopyWordsToWriter(&w, 4, 1, r, 0x19);
        CopyWordsToWriter(&w, 8, 1, &self->v140, 0x1A);
        WriteVifMscal(&w, D_00000D30);
        break;
    }
    case 2:
    case 3: {
        Vec02 d;
        Vec02 up;
        TransformDirectionBetweenFrames(self, 0, &self->q320, &d);
        Vu0::Q(d) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(-1.0f));
        TransformDirectionBetweenFrames(self, 0, &self->q340, &up);
        BuildBasisFromXAndZHint(&d, &up, &self->basis);
        func_001443C8(&self->basis, self->planes, self->f350, self->f354);
        Vec02& far = self->planes[4];
        Vec02& near = self->planes[5];
        for (s32 i = 0; i < 4; i++) {
            self->planes[i].w = -Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(self->planes[i])));
        }
        Vu0::Q(self->planes[4]) = Vu0::Q(self->basis.r[0]);
        far.w = -self->rangeMax - Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(self->planes[4])));
        f32 proj[4][4];
        f32 view[4][4];
        f32 ramp[2][4];
        f32 one = 1.0f;
        f32 zero = 0.0f;
        u128 neg = Vu0::ScalarInGpr(-1.0f);
        Vu0::Q(self->planes[5]) = Vu0::MulX(Vu0::Q(self->basis.r[0]), neg);
        near.w = 50.0f - Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(self->planes[5])));
        BuildProjectionMatrix(proj, one / self->f350, one / self->f354, zero, zero, 50.0f, self->rangeMax);
        BuildViewProjectionMatrix(&self->v140, &self->basis, proj, view);
        Vu0::Q(d) = Vu0::MulX(Vu0::Q(d), Vu0::ScalarInGpr(-1.0f));
        if (self->mode == 2) {
            FitUnitRampBetweenPair((LinePoints*)&self->f360, &ramp[0][0], &ramp[1][0]);
            FitUnitRampBetweenPair((LinePoints*)&self->f368, &ramp[0][1], &ramp[1][1]);
            ramp[0][2] = one;
            ramp[1][2] = zero;
        } else {
            ramp[0][0] = one;
            ramp[1][0] = zero;
            ramp[0][1] = one;
            ramp[1][1] = zero;
            FitUnitRampBetweenPair((LinePoints*)&self->f358, &ramp[0][2], &ramp[1][2]);
        }
        FitUnitRampBetweenPair((LinePoints*)&self->rangeMin, &ramp[0][3], &ramp[1][3]);
        CopyWordsToWriter(&w, 0xC, 2, ramp, 0x19);
        CopyWordsToWriter(&w, 8, 1, &d, 0x1B);
        CopyWordsToWriter(&w, 0xC, 4, view, 0x1C);
        WriteVifMscal(&w, D_00000EF0);
        break;
    }
    }
    WriteVifFlushE(&w);
    DetachPacketBuffer(&w, &self->packetSize, 0);
}
