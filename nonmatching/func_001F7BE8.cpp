// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 355/412 (86.2%), checked 2026-11-07
#include "common.h"
// NEAR: body and calls right, tail call right; only the scheduling/register choice of the 10 stores to D_00627800 (s2/s0 setup order) differs

struct Ctl_1F7BE8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
};

extern u8 D_00626000[];
extern u8 D_00626800[];
extern u8 D_00627000[];
extern Ctl_1F7BE8 g_remoteCallState;
extern s32 g_remoteCallsReady;

s32 DisableInterrupts(void);
void EnableInterrupts(void);
void InitCommandChannel(void);
s32 GetChannelWord(s32 index);
void SetCommandHandler(u32 index, void (*fn)(void), void* arg);
s32 SendCommand(u32 a, void* b, s32 c, s32 d, s32 e, s32 f);
s32 ReadIopRegister(u32 reg);
void WriteIopRegister(u32 reg, u32 value);
void HandleRemoteCallReply(void);
void AnswerServiceLookup(void);
void QueueServerRequest(void);
void AnswerIopCall(void);

void InitRemoteCalls(void)
{
    DisableInterrupts();
    if (g_remoteCallsReady != 0) {
        EnableInterrupts();
        return;
    }
    s32 one = 1;
    g_remoteCallsReady = one;
    EnableInterrupts();
    InitCommandChannel();
    DisableInterrupts();
    u8* buf = D_00626000;
    Ctl_1F7BE8* c = &g_remoteCallState;
    c->f4 = (s32)buf | 0x20000000;
    c->f0 = one;
    c->f8 = 0x20;
    c->fC = 0;
    c->f10 = 0;
    c->f14 = (s32)D_00626800 | 0x20000000;
    c->f18 = 0x20;
    c->f1C = (s32)D_00627000 | 0x20000000;
    c->f20 = 0x20;
    c->f24 = 0;
    SetCommandHandler(0x80000008, HandleRemoteCallReply, c);
    SetCommandHandler(0x80000009, AnswerServiceLookup, c);
    SetCommandHandler(0x8000000A, QueueServerRequest, c);
    SetCommandHandler(0x8000000C, AnswerIopCall, c);
    EnableInterrupts();
    if (ReadIopRegister(0x80000002) != 0) {
        return;
    }
    s32* p = (s32*)(buf + 0x40);
    p[3] = one;
    SendCommand(0x80000002, p, 0x10, 0, 0, 0);
    while (GetChannelWord(0) == 0) {
    }
    WriteIopRegister(0x80000002, 1);
}
