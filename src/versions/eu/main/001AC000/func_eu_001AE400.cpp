// SPDX-License-Identifier: AGPL-3.0-or-later
// Takes the sub-object from the helper, runs its update with 1.0 twice, stores the result, sets the text and clears the flag at 0x570.
extern char D_eu_0024E348[];

struct SubInfo_eu_1AE400 {
    u8 pad[8];
    s16 off;
    u8 pad2[2];
    s32 (*fn)(void* self, f32 a, f32 b);
};
struct Sub_eu_1AE400 {
    u8 pad[0x4C];
    SubInfo_eu_1AE400* info;
};
struct Obj_eu_1AE400 {
    u8 pad0[4];
    Sub_eu_1AE400* sub;
    u8 pad8[0x568];
    s32 f570;
};

void func_eu_001AAFB0(Obj_eu_1AE400* self);
void* func_0015C1C0(s32 a);
void func_eu_001AB238(void* self, const char* s);

void func_eu_001AE400(Obj_eu_1AE400* self)
{
    func_eu_001AAFB0(self);
    Sub_eu_1AE400* sub = (Sub_eu_1AE400*)func_0015C1C0(2);
    self->sub = (Sub_eu_1AE400*)sub->info->fn((u8*)sub + sub->info->off, 1.0f, 1.0f);
    func_eu_001AB238(self, D_eu_0024E348);
    self->f570 = 0;
}
