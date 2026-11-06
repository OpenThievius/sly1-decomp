// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL prints the RPC collision message only while a PAL-only flag is clear.
extern s32 D_eu_0025D6B8;

s32 func_0011D968(s32 id, s32 size, u8* data)
{
    s32 i;
    s32 r;
    for (i = 0; i < size; i++)
        g_iopCommandArgs[i] = data[i];
    while ((s32)g_iopReplyBuffer) {
        PollIopCommands();
        func_001F6C20(0);
    }
    ArmIopReplyBuffer(&D_0025C3C0, 1);
    while (func_001F8480(D_0027B4C8)) {
        if (D_eu_0025D6B8 == 0)
            PrintFormatted((void*)D_002494E8);
        PollIopCommands();
        func_001F6C20(0);
    }
    if (size)
        func_001F8290(D_0027B4C8, id, 1, g_iopCommandArgs, size, &D_0025C3C0, 0xC, 0, 0);
    else
        func_001F8290(D_0027B4C8, id, 1, 0, 0, &D_0025C3C0, 0xC, 0, 0);
    while (!IsIopReplyReady()) {
    }
    r = ((Req_0025C3C0*)&D_0025C3C0)->result;
    if (*D_0025C360[g_iopBufferIndex] != 0 && D_0025C384 == 0)
        FlushIopCommandBuffer();
    return r;
}
