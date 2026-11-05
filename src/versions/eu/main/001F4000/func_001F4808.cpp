// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the state at offset 0x570 of the global block (US 0x260).
struct Gl_eu_1F4808 { u8 pad[0x570]; s32 f570; };
void func_001F4808(ObjectSubGroup* self)
{
    BaseObject* key;
    s32 i;
    s32 found = 0;
    s32 next;
    Animation* it;

    key = (BaseObject*)func_001925F0();
    if (((Gl_eu_1F4808*)(Gl_1F4808*)&D_0026E9F8)->f570 == 2
        && (self->f2E0 != 0 || self->f2D4 != 0
            || ((*(Glob_1F4808**)&D_002623C0)->f19DC == 0 && (u8)func_001601A0(self->f2FC) == 1))) {
        func_001E0828((Gl_1F4808*)&D_0026E9F8);
        func_001F4760(self, 2);
        goto tail;
    }
    if (((Gl_eu_1F4808*)(Gl_1F4808*)&D_0026E9F8)->f570 >= 2) {
        func_001E02C8((Gl_1F4808*)&D_0026E9F8, 4);
    }
    if (self->f2D8 != 0) {
        func_001F4408(1, self->f318);
        func_001F4760(self, 0);
        return;
    }
    if (key == 0 || func_001300E8(key, 0x16) == 0) {
        func_001451F0((*(u8**)&D_00261990), 2, 0, (*(u8**)&D_00261990) + 0x460, 0, 0);
    }
    func_001F4760(self, 5);
    for (i = 0; i < self->count; i++) {
        it = (Animation*)self->items[i];
        func_0012C7B0(it, 0, 0, 0, 0.0f, 1.0f);
        next = 0;
        if (found != 0 || func_0012C9A8(it) != 0) {
            next = 1;
        }
        found = next;
    }
    if (found == 0) {
        if (self->f324 > 0.0f) {
            self->f31C = ((f32*)&D_0026185C)[0] + self->f324;
        } else if (self->count > 0) {
            self->f31C = ((f32*)&D_0026185C)[0] + ((Animation*)self->items[0])->length;
        } else {
            self->f31C = ((f32*)&D_0026185C)[0];
        }
    }
tail:
    func_001837E0(self, 2, 0, 0);
}
