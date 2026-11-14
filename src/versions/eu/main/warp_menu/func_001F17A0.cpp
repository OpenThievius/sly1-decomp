// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the y scale and offset are 234.30508 where US has 246.4.
void ProjectWarpEntryToScreen(WarpPage* self, s32 idx, s32 flag, f32* out)
{
    Vec02 v;
    BaseObject* o;
    if (flag != 0) {
        o = (BaseObject*)self->entries[idx].f18;
    } else {
        o = (BaseObject*)self->entries[idx].f14;
    }
    if (o != 0) {
        TransformPointBetweenFrames((PlacedObject*)o->parent, self, (Vec02*)((u8*)o + 0x40), &v);
        Camera* g = g_camera;
        Vu0::Q(v) = Vu0::Rotate(g->f80, Vu0::Q(v));
        Vu0::Q(v) = Vu0::Add(Vu0::Q(g->position), Vu0::Q(v));
        ProjectPointToCamera(g, &v, out);
        out[0] = out[0] * 320.0f + 320.0f;
        out[1] = out[1] * -234.30508f + 234.30508f;
    } else {
        out[0] = 320.0f;
        out[1] = 234.30508f;
    }
}
