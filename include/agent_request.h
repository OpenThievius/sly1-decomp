// SPDX-License-Identifier: AGPL-3.0-or-later
// A request an agent is asked to take (the agents' request slot: AcceptAgentRequest and its
// overrides): a kind and the object it concerns. Written for this project from what retail's
// code does.
#ifndef AGENT_REQUEST_H
#define AGENT_REQUEST_H

#include "common.h"

struct BaseObject;

struct AgentRequest { s32 kind00; BaseObject* ref04; };

#endif
