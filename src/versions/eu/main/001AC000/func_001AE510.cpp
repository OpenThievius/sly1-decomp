// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: sets the label of the two known objects from a text id (0x4C, 0x4B) through the object's own method.

struct Key_eu_1AE510 { s16 id; s16 pad; };
struct Obj_eu_1AE510;
typedef void (*Fn_eu_1AE510)(Obj_eu_1AE510* self, Key_eu_1AE510* key);
struct Obj_eu_1AE510 { Fn_eu_1AE510* vt; void* f4; };

void func_eu_001AAFB0(Obj_1AE510* self);

void func_001AE510(Obj_1AE510* base)
{
    Obj_eu_1AE510* self = (Obj_eu_1AE510*)base;
    Key_eu_1AE510 key;
    func_eu_001AAFB0(base);
    self->f4 = func_0015C1C0(2);
    if ((u8*)self == D_00273C50) {
        key.pad = 0;
        key.id = 0x4C;
    } else if ((u8*)self == D_002739F0) {
        key.pad = 0;
        key.id = 0x4B;
    }
    self->vt[8](self, &key);
}
