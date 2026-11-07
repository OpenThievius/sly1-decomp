// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with func_eu_001F7738, a function only PAL has, where US calls func_00201720
void func_eu_001F7738(Blob_1F9868* dst, Blob_1F9868* src, s32 n);

s32 func_001F9868(Blob_1F9868* src, s32 size, Blob_1F9868* data, s32* out, s32 cmd)
{
    if (func_001F9690() < 0) {
        return -0x10000;
    }
    if (func_001F9790() != 0) {
        return -0x10004;
    }
    Blob_1F9868* p = &D_00628C00.name;
    func_eu_001F7738(p, src, 0xFC);
    Buf_1F9868* q = (Buf_1F9868*)((u8*)p - 8);
    q->name.b[0xFB] = 0;
    if (data != 0) {
        if (size >= 0xFD) {
            q->data = *data;
            D_00628C00.f0 = 0xFC;
        } else {
            func_001F5A58(&q->data, data, size);
            q->f0 = size;
        }
    } else {
        q->data.b[0] = 0;
        q->f0 = 0;
    }
    Buf_1F9868* buf = &D_00628C00;
    if (func_001F8290(D_00628E00, cmd, 0, buf, 0x200, buf, 8, 0, 0) < 0) {
        return -0x10001;
    }
    s32 v = buf->f4;
    s32 ret = D_00628C00.f0;
    *out = v;
    return ret;
}
