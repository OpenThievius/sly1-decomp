// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two slots written in D_0026D348 are at 0x574 and 0x578 (not 0x264 and 0x268).
struct Glob_eu_14CF30 {
    VFn_14CF30* vtbl;
    u8 pad0[0x574 - 4];
    void* f574;
    void* f578;
};

void func_0014CF30(C68* self, s32 kind, void* key)
{
    func_00127378(self, kind, key);
    switch (kind) {
    case 6: {
        s32 i;
        for (i = 0; i < self->n2DC; i++) {
            if (self->slots[i].key == key) {
                break;
            }
        }
        if (i < self->n2DC) {
            self->slots[i].key = 0;
        }
        break;
    }
    case 0x14:
        if (key == self->f42C) {
            s32 out;
            func_001B6598(key, &out);
            if (out == 0x3FD) {
                (*(Glob_eu_14CF30*)&D_0026D348).f574 = &self->f2D0;
                (*(Glob_eu_14CF30*)&D_0026D348).f578 = &self->f2D4;
                func_001DDC38(self->world, self);
                func_001AB890(((Glob_14CF30*)&D_0026E760), self->f2D8);
                func_001AB928(((Glob_14CF30*)&D_0026E760), 0.0f, func_0014C668);
                func_001AB938(((Glob_14CF30*)&D_0026E760));
            }
            if (self->tag430 == 0x3FD) {
                (*(Glob_14CF30*)&D_0026D348).vtbl[15](((Glob_14CF30*)&D_0026D348));
                (*(Glob_14CF30*)&D_0026E760).vtbl[15](((Glob_14CF30*)&D_0026E760));
                func_001DDC38(self->world, 0);
            }
            self->tag430 = out;
        }
        break;
    }
}

