// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the instrument pointer is at 0x58C (US 0x27C).
void SetupScreenElementText(void* self);
struct Obj_1E6188_eu { u8 pad[0x58C]; ConeSprite* p58C; };

void CreateArcSprite(Obj_1E6188_eu* self)
{
    SetupScreenElementText(self);
    self->p58C = (ConeSprite*)CreateTypedRecord(0x51, g_currentWorld, 0, 0x201, -1);
    SetConeVolumeMode((ConeVolume*)self->p58C, 1);
    SetConeVolumeColor((ConeVolume*)self->p58C, (Quad16*)D_00275640);
    SetConeVolumeFirstAngle((ConeVolume*)self->p58C, D_00275650);
    SetConeVolumeSecondLevel((ConeVolume*)self->p58C, D_00275654);
    SetConeVolumeSecondAngle((ConeVolume*)self->p58C, D_00275658);
    SetConeVolumeThirdLevel((ConeVolume*)self->p58C, D_0027565C);
    SetConeVolumeThirdAngle((ConeVolume*)self->p58C, D_00275660);
    SetConeVolumeRange((ConeVolume*)self->p58C, (U64P*)D_00275B58);
    SetConeVolumeValue((ConeVolume*)self->p58C, 1);
    self->p58C->vtbl[7](self->p58C);
}
