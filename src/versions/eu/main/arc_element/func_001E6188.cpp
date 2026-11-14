// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the instrument pointer is at 0x58C (US 0x27C).
void SetupScreenElementText(void* self);
struct Obj_1E6188_eu { u8 pad[0x58C]; ConeSprite* p58C; };

void CreateArcSprite(Obj_1E6188_eu* self)
{
    SetupScreenElementText(self);
    self->p58C = (ConeSprite*)CreateTypedRecord(0x51, g_currentWorld, 0, 0x201, -1);
    SetConeVolumeMode((ConeVolume*)self->p58C, 1);
    SetConeVolumeColor((ConeVolume*)self->p58C, (Quad16*)g_coneVolumeColor);
    SetConeVolumeFirstAngle((ConeVolume*)self->p58C, g_coneVolumeFirstAngle);
    SetConeVolumeSecondLevel((ConeVolume*)self->p58C, g_coneVolumeSecondLevel);
    SetConeVolumeSecondAngle((ConeVolume*)self->p58C, g_coneVolumeSecondAngle);
    SetConeVolumeThirdLevel((ConeVolume*)self->p58C, g_coneVolumeThirdLevel);
    SetConeVolumeThirdAngle((ConeVolume*)self->p58C, g_coneVolumeThirdAngle);
    SetConeVolumeRange((ConeVolume*)self->p58C, (U64P*)g_arcSpriteRange);
    SetConeVolumeValue((ConeVolume*)self->p58C, 1);
    self->p58C->vtbl[7](self->p58C);
}
