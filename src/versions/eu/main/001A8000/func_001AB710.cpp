// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields moved (+0x310), u16 flag at +8, extra func_eu_001374E0 call, PAL-only name lookup func_eu_0015C778 and a buffer built by func_eu_0015DCB8/func_eu_0015E7E0.
struct Actor_001AB710_eu { u8 pad0[4]; void* p4; u16 f08; u8 pad1[0x518 - 0xA]; s32 f518; f32 f51C; void* f520; u8 pad2[8]; f32 f52C; f32 f530; u8 pad3[0x10]; f32 f544; f32 f548; u8 pad4[0x40]; PackedWord_001AB710 w58C; u8 pad5[4]; s32 f594; };

void func_00137248(void* out, void* p);
void func_eu_001374E0(void* out, s32 v);
void func_eu_0015C778(void* p, void* name, void* out, s32 zero, void* d);
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* d);

void func_001AB710(Actor_001AB710_eu* self)
{
    Local_001AB710 L;
    u8 buf[0xC0];
    if (self->f08 != 0) {
        f32 f544 = self->f544;
        f32 f548 = self->f548;
        s32 s0v = self->f518;
        func_00137228(&L, self->f52C, self->f530);
        func_00137238(&L, f544, f548);
        L.tag = s0v;
        func_00137248(&L, &L.tag);
        func_00137260(&L, 0);
        func_00137268(&L, 0);
        func_eu_001374E0(&L, 0);
        void* obj = self->f520;
        if (obj != 0) {
            SubObj_001AB710* sub = *(SubObj_001AB710**)obj;
            if (sub != 0) {
                VDesc_001AB710* d = sub->desc4C;
                d->fn4C((u8*)sub + d->off48, obj, &L, D_00262280);
            }
        }
        f32 v = self->f51C;
        u8* dp = D_00262280;
        func_0015C8B8(self->p4, v, v);
        ((u8*)&L.tag)[0] = 0x54;
        ((u8*)&L.tag)[1] = 0;
        func_eu_0015C778(self->p4, &L.tag, &L, 0, dp);
        f32 r = func_0015C418(self->p4, &L.tag);
        f32 a = self->f52C + r;
        L.y = self->f530;
        L.x = a;
        if (self->f594 != 0) {
            L.w30 = self->w58C;
            L.w10 = L.w30;
        }
        func_eu_0015DCB8(buf, (u8*)self + 10, self->p4, 0);
        func_eu_0015E7E0(buf, &L, 0, dp);
        func_0015C900(self->p4);
    }
}
