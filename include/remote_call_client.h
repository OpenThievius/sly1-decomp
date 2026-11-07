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
typedef void (*RemoteCallEndFn)(s32 arg);

typedef struct RemoteCallClient {
    struct RemoteCallPacket* packet; // 0x00: the request packet in flight, 0 when none
    s32 id;                          // 0x04: that packet's id, to tell a reused packet
    s32 sema;                        // 0x08: the semaphore a waiting request sleeps on, -1 when none
    s32 fC;                          // 0x0C
    s32 f10;                         // 0x10: cleared by BindRemoteService
    s32 f14;                         // 0x14: a word of the bind's reply
    s32 f18;                         // 0x18: a word of the bind's reply
    RemoteCallEndFn callback;        // 0x1C: run when the reply arrives
    s32 callbackArg;                 // 0x20
    s32 server;                      // 0x24: the service's record on the IOP, 0 until bound
} RemoteCallClient;

#endif
