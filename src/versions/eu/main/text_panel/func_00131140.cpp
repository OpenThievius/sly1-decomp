// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the object's fields are 0x28C later (f300..f314 at 0x58C..0x5A0).
typedef void (*VFn_131140)(void* self, s32 arg);

struct Obj_131140_eu {
    VFn_131140* vtbl;
    u8 pad0[0x58C - 4];
    s32 f300;
    s32 f304;
    s32 f308;
    u8 pad1[8];
    f32 f314;
};

void SetTextPanelSubject(Obj_131140_eu* self, BaseObject* value);

void ClearTextPanel(Obj_131140_eu* self)
{
    self->vtbl[8](self, 0);
    SetTextPanelSubject(self, 0);
    self->f300 = 0;
    self->f304 = 0;
    self->f308 = 0;
    self->f314 = 0.4f;
}
