// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with func_eu_001F7738, a function only PAL has, where US calls func_00201720
void CopyStringBoundedForIopClients(Blob_1F9868* dst, Blob_1F9868* src, s32 n);

s32 SendModuleLoadRequest(Blob_1F9868* src, s32 size, Blob_1F9868* data, s32* out, s32 cmd)
{
    if (BindModuleLoader() < 0) {
        return -0x10000;
    }
    if (IsModuleLoaderMismatched() != 0) {
        return -0x10004;
    }
    Blob_1F9868* p = &g_moduleLoaderBuffer.name;
    CopyStringBoundedForIopClients(p, src, 0xFC);
    Buf_1F9868* q = (Buf_1F9868*)((u8*)p - 8);
    q->name.b[0xFB] = 0;
    if (data != 0) {
        if (size >= 0xFD) {
            q->data = *data;
            g_moduleLoaderBuffer.f0 = 0xFC;
        } else {
            CopyBytes(&q->data, data, size);
            q->f0 = size;
        }
    } else {
        q->data.b[0] = 0;
        q->f0 = 0;
    }
    Buf_1F9868* buf = &g_moduleLoaderBuffer;
    if (CallRemoteService(g_moduleLoaderClient, cmd, 0, buf, 0x200, buf, 8, 0, 0) < 0) {
        return -0x10001;
    }
    s32 v = buf->f4;
    s32 ret = g_moduleLoaderBuffer.f0;
    *out = v;
    return ret;
}
