// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws a framed rectangle around the owner's bounds using the GS-style draw helpers (positions in 12.4 fixed point).
struct Inner_eu_1AEA90 { u16 x; u16 y; };
struct Link_eu_1AEA90 { u8 pad0[0xC]; Inner_eu_1AEA90** rect; };
struct Peer_eu_1AEA90 { u8 pad0[0x14]; Link_eu_1AEA90* link; };
struct Obj_eu_1AEA90 {
    u8 pad0[0x52C]; f32 f52C; f32 f530; u8 pad1[0x544 - 0x534]; f32 f544; f32 f548;
    u8 pad2[0x570 - 0x54C]; Peer_eu_1AEA90* peer;
};
extern u8 D_eu_00263590[];
void func_eu_001AB558(void* self);
s32 func_001B2988(void* p, s32 a, s32 b);
void func_eu_00161A20(void* ctx, s32 a, s32 b, u64 c);
void func_eu_00161D68(void* ctx, s32 a, s64 b);
void func_eu_00161AB8(void* ctx, s32 color);
void func_eu_00161B28(void* ctx, s32 a, s32 b);
void func_eu_00161C50(void* ctx, s32 a, s32 b, s32 c, s32 d);

void func_eu_001AEA90(Obj_eu_1AEA90* self)
{
    s32 tmp[4];
    if (self->peer != 0) {
        Inner_eu_1AEA90* r = *self->peer->link->rect;
        s32 id = func_001B2988(self->peer->link, 0, 0);
        u8* ctx = D_eu_00263590;
        func_eu_00161A20(ctx, 0x156, 10, 0x43431EEEEEULL);
        func_eu_00161D68(ctx, 0x47, 0x33001);
        func_eu_00161D68(ctx, 0x42, 0x44);
        func_eu_00161D68(ctx, 6, id);
        func_eu_00161D68(ctx, 0x14, 0x60);
        func_eu_00161D68(ctx, 8, 5);
        tmp[0] = (s32)0x80808080;
        func_eu_00161AB8(ctx, tmp[0]);
        func_eu_00161B28(ctx, 0, r->y << 4);
        func_eu_00161C50(ctx, (s32)((self->f52C + 1728.0f) * 16.0f),
                         (s32)((self->f530 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
        func_eu_00161B28(ctx, r->x << 4, 0);
        func_eu_00161C50(ctx, (s32)(((self->f52C + self->f544) + 1728.0f) * 16.0f),
                         (s32)(((self->f530 + self->f548) * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
    } else {
        func_eu_001AB558(self);
    }
}
