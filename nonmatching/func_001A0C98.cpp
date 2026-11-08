// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 184/196 (93.9%), checked 2026-11-08
#include "common.h"
#include "effect.h"
#include "vu0.h"
// NEAR (2026-11-08, worker night-mmi): all but the call of ProjectPointToCamera: retail loads
// self->params (lw s0) in its delay slot, after the argument moves, so params and pos share s0;
// here the load follows the call and move a1, s0 takes the slot. Reading params before the call
// (a statement, or a comma in an argument) puts the load first and pos in s2.

struct Camera;
extern Camera* g_camera;
extern f32 D_0026B5F0[4];
extern Quad219C D_00275C50;
f32 RandomFloatInRange(f32 a, f32 b);
void InitEffect(Effect* self, void* pos);
void ProjectPointToCamera(Camera* cam, void* pos, void* out);

void InitCameraSpaceEffect(Effect* self, void* pos)
{
    InitEffect(self, pos);
    ProjectPointToCamera(g_camera, pos, &self->f120);
    const T219C_Params* p = self->params;
    f32 x = RandomFloatInRange(p->rows[8], p->rows[12]);
    f32 y = RandomFloatInRange(p->rows[9], p->rows[13]);
    f32 z = RandomFloatInRange(p->rows[10], p->rows[14]);
    self->life = D_0026B5F0[0];
    Vu0::Q(self->qA0) = Vu0::FromFloats(x, y, z);
    self->q40 = D_00275C50;
    self->q30 = *(const Quad219C*)&p->rows[20];
}
