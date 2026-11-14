// SPDX-License-Identifier: AGPL-3.0-or-later
// An object of the kernel library from 0x1F9690 to 0x1F9AD8, built whole (config/us/files.tsv):
// a client of an IOP service over the command channel (0x80000006). func_001F9690 binds the
// client D_00628E00 once (D_002771CC, -1 until then) and keeps the service's version word in
// D_00628E28; func_001F9790 tells whether that word, the library's own ("2430", the end of
// D_00276970) and the string "...." D_002771D0 points to differ; func_001F9820 forgets the
// binding. func_001F9868 sends a request: a name of up to 0xFB characters and up to 0xFC bytes
// of data in the buffer D_00628C00, and returns the reply's size and its word; func_001F9A90
// sends one with the command 0.
#include "common.h"
#include "remote_call_client.h"
#include "asm_func.h"

// A name or a block of data of the request: 0xFC bytes.
struct ModuleBlob { u8 b[0xFC]; };
// The buffer of the request and of its reply: the size of the data it carries (the reply's
// result, in the same word), the reply's second word, the name and the data.
struct ModuleLoadBuffer { s32 size; s32 word; ModuleBlob name; ModuleBlob data; };

s32 g_moduleLoaderBound = -1;
const char* D_002771D0 = "....";
// A string no code reads.
extern const char D_0024EB88[] = "all";

static ModuleLoadBuffer g_moduleLoaderBuffer __attribute__((aligned(64)));
static RemoteCallClient g_moduleLoaderClient __attribute__((aligned(64)));
static s32 g_moduleLoaderVersion;

extern char D_00276970[16];

s32 CompareMemory(const void* a, const void* b, s32 n);
extern "C" void* CopyBytes(void* dst, const void* src, s32 n);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void* CopyStringBounded(ModuleBlob* dst, ModuleBlob* src, s32 n);
s32 BindModuleLoader(void);

// A word read at any alignment.
struct __attribute__((packed)) UnalignedWord { u32 v; };


s32 BindModuleLoader(void)
{
    s32 i;
    RemoteCallClient* c;

    if (g_moduleLoaderBound < 0) {
        for (;;) {
            c = &g_moduleLoaderClient;
            if (BindRemoteService(c, 0x80000006, 0) < 0) {
                return -1;
            }
            if (c->server != 0) {
                g_moduleLoaderBound = 0;
                if (CallRemoteService(&g_moduleLoaderClient, 0xFF, 0, 0, 0, &g_moduleLoaderBuffer, 4, 0, 0) < 0) {
                    return 0xFFFEFFFF;
                }
                *(UnalignedWord*)&g_moduleLoaderVersion = *(UnalignedWord*)&g_moduleLoaderBuffer;
                return 0;
            }
            for (i = 0x100000; i != -1; ) i--;
        }
    }
    return 0;
}

s32 IsModuleLoaderMismatched(void)
{
    s32 result = 0;
    void* second = &D_00276970[12];
    if (CompareMemory(&g_moduleLoaderVersion, second, 4) != 0) {
        if (CompareMemory(&g_moduleLoaderVersion, D_002771D0, 4) != 0) {
            result = CompareMemory(second, D_002771D0, 4) != 0;
        }
    }
    return result;
}

s32 ForgetModuleLoader(void)
{
    g_moduleLoaderBound = -1;
    FillMemory(&g_moduleLoaderVersion, 0, 4);
    return 0;
}

LINKER_REMNANT(func_001F9858);

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

s32 LoadIopModuleFile(ModuleBlob* src, s32 size, ModuleBlob* data)
{
    s32 out[4];
    return SendModuleLoadRequest(src, size, data, out, 0);
}

LINKER_REMNANT(func_001F9AB0);
