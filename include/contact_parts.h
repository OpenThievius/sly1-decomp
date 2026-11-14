// SPDX-License-Identifier: AGPL-3.0-or-later
// The contact-node records of the world's listed objects.
#ifndef CONTACT_PARTS_H
#define CONTACT_PARTS_H

#include "common.h"

struct ContactBody;
struct ContactPart;
struct ContactPartVt
{
    u8 pad0[0x10C];
    void (*f10C)(ContactPart* c);
    void (*f110)(ContactPart* c);
};
struct ContactPart
{
    ContactPartVt* vt;
    u8 pad[0x2E4 - 4];
    ContactPart* next;
};
struct ContactSlot
{
    Contact03* f0;
};
struct ContactNode
{
    Contact03* f0;
    ContactNode* f4;
    ContactSlot* f8;
    ContactBody* fC;
};
struct ContactNodeList
{
    ContactNode* head;
};
struct ContactBody
{
    u8 pad0[0x2C8];
    u64 bits2C8;
    u8 pad1[0x2D8 - 0x2D0];
    ContactPart* children;
    u8 pad2[0x414 - 0x2DC];
    ContactBody* next;
    u8 pad3[0x480 - 0x418];
    ContactNodeList* list;
    u8 pad4[0x4B8 - 0x484];
    s32 kind;
    u8 pad5[0x538 - 0x4BC];
    u64 bits538;
};

#endif
