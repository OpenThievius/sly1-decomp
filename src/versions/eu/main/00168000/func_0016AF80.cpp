// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the names come from a text table (func_eu_001DDAB0 ids 0x16, 0x18, 0x17), and the empty label and the flagged case go through PAL-only func_eu_001AB238 (with PAL's own empty string D_eu_0024CC20) and func_eu_001ADF10. The object field is at +0x974.
const char* func_eu_001DDAB0(s32 id);
void func_eu_001AB238(void* self, const char* s);
void func_eu_001ADF10(void* self);
extern char D_eu_0024CC20[];
struct Obj_16AF80_eu {
    void** vtbl;
    u8 pad4[0x970];
    s32 f974;
};

void func_0016AF80(Ctx_16AF80* self)
{
    s32 s1 = 0;
    s32 stride = 0x44C;
    Pair_16AF80* p = self->f2E0;

    if (p->f28 != p->f30) {
        func_eu_001AB238(D_0026F138, D_eu_0024CC20);
    } else if (self->f2D0 == 0) {
        void** vt = *(void***)D_0026F138;
        ((VFnS_16AF80)vt[8])(D_0026F138, func_eu_001DDAB0(0x16));
    } else {
        s32 flags = *(s32*)(D_002623C0 + self->f2D0 * stride + 0x458);
        if (flags & 1) {
            func_eu_001ADF10(D_0026F138);
        } else if (self->f2D0 == self->f300) {
            void** vt = *(void***)D_0026F138;
            ((VFnS_16AF80)vt[8])(D_0026F138, func_eu_001DDAB0(0x18));
        } else {
            s1 = 1;
            func_eu_001AB238(D_0026F138, D_eu_0024CC20);
        }
    }

    func_001AA8B8(D_0026F138, 0.0f);
    ((Obj_16AF80_eu*)D_0026F138)->f974 = 0;
    {
        void** vt = *(void***)D_0026F138;
        ((VFnV_16AF80)vt[14])(D_0026F138);
    }

    if (s1 != 0) {
        ((VFnS_16AF80)(*(void***)D_0026FA90)[8])(D_0026FA90, func_eu_001DDAB0(0x17));
        ((VFnV_16AF80)(*(void***)D_0026FA90)[14])(D_0026FA90);
    } else {
        void** vt = *(void***)D_0026FA90;
        ((VFnV_16AF80)vt[15])(D_0026FA90);
    }
}
