// SPDX-License-Identifier: AGPL-3.0-or-later
// A client of a service on the IOP, reached through the remote calls of src/lib/remote_call.cpp:
// BindRemoteService binds it to a service id and CallRemoteService sends its requests. Each
// library keeps one for every service it uses (the disc, pad, memory card, file and module
// loader clients). Written for this project from retail's code.
#ifndef REMOTE_CALL_CLIENT_H
#define REMOTE_CALL_CLIENT_H

#include "common.h"

struct RemoteCallPacket;

// What CallRemoteService runs when a request without a wait ends, with its argument.
typedef void (*RemoteCallEndFn)(void* arg);

// The client's packet word: the request packet in flight, 0 when none. It is a member of a
// union because CallRemoteService's code needs its store to conflict with every other store,
// which only a union member's does (docs/toolchain/alias-classes.md, "A store that conflicts
// with two classes"). The pointer is the member the code uses; the plain word is our choice of
// a second member.
typedef union RemoteCallPacketRef {
    struct RemoteCallPacket* ptr;
    u32 word;
} RemoteCallPacketRef;

typedef struct RemoteCallClient {
    RemoteCallPacketRef packet;      // 0x00: the request packet in flight, 0 when none
    s32 id;                          // 0x04: that packet's id, to tell a reused packet
    s32 sema;                        // 0x08: the semaphore a waiting request sleeps on, -1 when none
    s32 fC;                          // 0x0C
    s32 f10;                         // 0x10: cleared by BindRemoteService
    s32 f14;                         // 0x14: a word of the bind's reply
    s32 f18;                         // 0x18: a word of the bind's reply
    u32 callback;                    // 0x1C: a RemoteCallEndFn as a plain word, run when the reply arrives
    s32 callbackArg;                 // 0x20
    s32 server;                      // 0x24: the service's record on the IOP, 0 until bound
} RemoteCallClient;

// src/lib/remote_call.cpp defines them, with C linkage; every client library declares them here.
#ifdef __cplusplus
extern "C" {
#endif
s32 BindRemoteService(RemoteCallClient* self, u32 cmd, s32 mode);
s32 CallRemoteService(RemoteCallClient* self, s32 cmd, s32 mode, void* send, s32 sendSize, void* recv, s32 recvSize,
                      RemoteCallEndFn callback, void* callbackArg);
s32 IsRemoteCallPending(RemoteCallClient* self);
#ifdef __cplusplus
}
#endif

#endif
