// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 734/744 (98.7%), checked 2026-11-07
#include "common.h"
#include "fpu.h"
#include "vu0.h"
#include "path_curve_object.h"
#include "world.h"
#include "packet_writer.h"
#include "list_iter.h"
#include "shapes.h"
#include "globals.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "asm_func.h"
// NEAR (2026-11-08, wave 4): the whole function is retail's (BuildRangeRecordPacket), 8 instructions differ in registers only: retail loads f40 into $f5 and f44 into $f4 (the near and far of the range, $f20 = f40 - k, $f21 = f44 - k) where here they take $f4 and $f5, and it moves $f17 before $f16 for BuildProjectionMatrix's last two arguments. The packet's uniforms are a struct (RangeUniforms) so that the loads of D_002744F0 and the two FLT_MAX literals come before the stores, as retail's. Declaring the four floats as locals in all 24 orders, num/den splits and swapping lo and hi declarations did not move the registers.
// What the range record's first unpack holds: a matrix, the sizes of the record's colour bytes
// halved, and the near and far planes of the range with the clip below the near one.
struct RangeUniforms {
    u8 pad00[0x40];
    s32 sizes[4];
    f32 nearZ;
    f32 farZ;
    u8 pad58[4];
    f32 clipZ;
};
void* InitPacketWriter(PacketWriter* p);
void UsePacketBufferMemory(PacketWriter* b, s32 n, void* q);
void ReserveVifUnpack(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifFlushE(PacketWriter* s);
void DetachPacketBuffer(PacketWriter* s, void* a, s32 b);
void SubmitMeshQueueEntry(void* p);
void BuildBasisFromXAndZHint(void* x, void* z, void* out);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);
void InitIdentityMatrix(Mat4A* m);
void BuildProjectionMatrix(Mat4A* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void BuildViewProjectionMatrix(void* pos, void* basis, Mat4A* proj, void* out);
void CopyMemory(void* dst, void* src, s32 n);
extern u8 D_000003B0[];
extern f32 D_002744F0;

void BuildRangeRecordPacket(RangeRecord* self)
{
    if (self->link != 0) {
        Camera* g = g_camera;
        s32 bits = self->link->maskC;
        s32 need = g->f21C;
        s32 ok = 0;
        if ((bits & 0x10000000) != 0 || (need & bits) == need) {
            ok = 1;
        }
        if (ok != 0) {
            PacketWriter pw;
            u8 spare[16];
            Vec02 pos;
            Mat02 basis;
            Mat4A proj;
            Vec02 axis;
            RangeUniforms* p;
            InitPacketWriter(&pw);
            u8* dst = self->f2D0;
            if (dst == 0) {
                dst = spare;
            }
            UsePacketBufferMemory(&pw, 0x20, (u8*)self + 0xD0);
            ReserveVifUnpack(&pw, 0xC, 6, 0x16, 0, &p);
            AnimRecordEntry* ents = self->link->ents;
            ReserveVifUnpack(&pw, 0xC, ents->type, 0x1C, dst, dst + 8);
            *(s32*)(dst + 4) = ents->addr;
            *(s32*)(dst + 0xC) = 0;
            SubmitMeshQueueEntry(dst);
            WriteVifMscal(&pw, D_000003B0);
            WriteVifFlushE(&pw);
            DetachPacketBuffer(&pw, &self->fC0, 0);
            axis = self->v20;
            BuildBasisFromXAndZHint(&axis, &self->v30, &basis);
            if (AreFloatsNearlyEqual(self->f04, self->f08, 0.0001f) != 0) {
                pos = self->v10;
                InitIdentityMatrix(&proj);
                f32 half = 0.5f;
                f32 q = half / self->f04;
                proj.m[0][0] = q;
                proj.m[1][1] = q;
                proj.m[3][0] = half;
                proj.m[3][1] = half;
                p->nearZ = -3.40282347e+38f;
                p->farZ = 3.40282347e+38f;
                p->clipZ = self->f40 - D_002744F0;
            } else {
                f32 k = (self->f08 * self->f40 - self->f04 * self->f44) / (self->f08 - self->f04);
                f32 lo = self->f40 - k;
                f32 hi = self->f44 - k;
                Vu0::Set(pos, Vu0::MulAddX(Vu0::Q(self->v10), Vu0::Q(axis), Vu0::Scalar(k)));
                BuildProjectionMatrix(&proj, 0.5f / (self->f04 / lo), 0.5f / (self->f04 / lo), 0.5f, 0.5f, lo, hi);
                if (lo < hi) {
                    p->nearZ = lo;
                    p->farZ = hi;
                } else {
                    p->nearZ = hi;
                    p->farZ = lo;
                }
                p->clipZ = p->nearZ - D_002744F0;
            }
            BuildViewProjectionMatrix(&pos, &basis, &proj, (u8*)self + 0x70);
            CopyMemory(p, (u8*)self + 0x70, 0x40);
            for (s32 i = 0; i < 4; i++) {
                p->sizes[i] = ((((u8*)self->link) + i)[4] + 1) >> 1;
            }
        }
    }
}

