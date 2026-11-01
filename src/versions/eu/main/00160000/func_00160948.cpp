// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's fallback key is entry D_eu_00263710 of a table of 0x20-byte keys, not the first one.
extern s32 D_eu_00263710;

void func_00160948(void)
{
    Key_160948* k = func_00160180((((Ctx_160948*)D_002623C0)->f19D8 << 8) | ((Ctx_160948*)D_002623C0)->f19DC);
    if (k == 0) {
        k = (Key_160948*)((u8*)&D_00247AB0 + D_eu_00263710 * 0x20);
    }
    func_00160CC8(D_002623D8);
    if (D_00275BC0.f30 != 1 || ((Ctx_160948*)D_002623C0)->fC != 0.0f || !k->Same(&D_00275B04)) {
        func_001F0428(k, -1, 1);
    } else if (D_00275BC0.f30 == 1) {
        if (D_00275F84 == 0) {
            func_001C0760(((Ctx_160948*)D_002623C0)->f19EC & 0x80);
            func_001C0790(((Ctx_160948*)D_002623C0)->f19EC & 0x40);
            Rec_160948* r = func_0015A418(D_00275710, 0x105, 0x494, 0);
            if (r != 0) {
                Frame_160948 frame((Lst_160948*)((u8*)r + 0x6C));
                void* head = r->head;
                frame.cursor = (u8*)head + frame.next_off;
                void* node = head;
                if (node != 0) {
                    do {
                        func_0012E760(node);
                        node = frame.Next();
                    } while (node != 0);
                }
            }
            D_00275BC0.f30 = -1;
            func_001E96F8(&D_00275BC0, 3);
        }
    }
}
