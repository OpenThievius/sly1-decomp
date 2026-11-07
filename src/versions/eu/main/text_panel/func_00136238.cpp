// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields shifted (0x56C/0x5AC/0x5B0/0x5B4/0x5B8); toggles the menu state and its callbacks.
struct Obj_136238_eu;
struct VT_136238_eu { u8 pad0[0x40]; void (*f40)(Obj_136238_eu*, s32); };
struct Obj_136238_eu {
    VT_136238_eu* vt;
    u8 pad4[0x56C - 4];
    s32 f56C;
    u8 pad260[0x5AC - 0x570];
    s32 f5AC;
    struct Sub_136238_eu* f5B0;
    s32 f5B4;
    s32 f5B8;
};
struct Sub_136238_eu { u8 pad0[0x2D4]; s32 f2D4; };

void func_001BEA50(void);
void func_001BEA28(void);
s32 func_00160D10(void);
void func_00135E78(Obj_136238_eu* self, s32 state, s32 flag);
s32 func_0015A4F0(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void func_00192190(void* p);

struct Min_136238_eu { static s32 Of(s32 a, s32 b) { if (b - 1 < a) return b; return a; } };

void func_00136238(Obj_136238_eu* self, s32 on)
{
    LevelBit in;
    void* arr[0x100];
    s32 n;
    if ((on != 0) != (self->f56C == 0)) return;
    if (self->f5B0 != 0 && self->f5B0->f2D4 == 3) {
        if (on != 0) func_001BEA50();
        else func_001BEA28();
    }
    self->f56C = on;
    self->f5AC = 0;
    if (on != 0) {
        self->vt->f40(self, 2);
        GetCurrentLevelBit(&in);
        if (MaskWorldBitsBySave() & in.v) {
            if (MaskWorldBitsBySave() & D_00261120[self->f5B8]) ReleasePanelEntries(self, self->f5B8, 1);
        }
        if (MaskWorldBitsBySave() & 0x800) {
            n = GatherObjectsById(*(s32*)g_currentWorld, 0x205, 0x82, 0, 0x100, arr);
            n = Min_136238_eu::Of(n, 0x100);
            if (n > 0) {
                void** p = arr;
                s32 i = n;
                do { i--; func_00192190(*p); p++; } while (i != 0);
            }
        }
    } else {
        self->vt->f40(self, 0);
        self->f5B8 = self->f5B4;
        ReleasePanelEntries(self, 0, 1);
    }
}

