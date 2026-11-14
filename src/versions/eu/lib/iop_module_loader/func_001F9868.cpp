// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with its own copy of CopyStringBounded (func_001F7738, the same bytes), placed elsewhere
void* CopyStringBounded(ModuleBlob* dst, ModuleBlob* src, s32 n);

s32 SendModuleLoadRequest(ModuleBlob* src, s32 size, ModuleBlob* data, s32* out, s32 cmd)
{
    if (BindModuleLoader() < 0) {
        return -0x10000;
    }
    if (IsModuleLoaderMismatched() != 0) {
        return -0x10004;
    }
    ModuleBlob* p = &g_moduleLoaderBuffer.name;
    CopyStringBounded(p, src, 0xFC);
    ModuleLoadBuffer* q = (ModuleLoadBuffer*)((u8*)p - 8);
    q->name.b[0xFB] = 0;
    if (data != 0) {
        if (size >= 0xFD) {
            q->data = *data;
            g_moduleLoaderBuffer.size = 0xFC;
        } else {
            CopyBytes(&q->data, data, size);
            q->size = size;
        }
    } else {
        q->data.b[0] = 0;
        q->size = 0;
    }
    ModuleLoadBuffer* buf = &g_moduleLoaderBuffer;
    if (CallRemoteService(&g_moduleLoaderClient, cmd, 0, buf, 0x200, buf, 8, 0, 0) < 0) {
        return -0x10001;
    }
    s32 v = buf->word;
    s32 ret = g_moduleLoaderBuffer.size;
    *out = v;
    return ret;
}
