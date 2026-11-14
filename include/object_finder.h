// SPDX-License-Identifier: AGPL-3.0-or-later
// Finding a world's objects by id (effect_spawner.cpp defines them): GatherObjectsByMode and
// GatherObjectsById collect up to max objects of an id into found, the caller's array of object
// pointers, the low byte of flags saying where to look (relative to scope, the object asking) and
// 0x200 asking for one; the FindFirst* forms return the first. One declaration for every file,
// where each had its own. Written for this project from what retail's code does.
#ifndef OBJECT_FINDER_H
#define OBJECT_FINDER_H

#include "common.h"

struct World;
struct BaseObject;
struct PlacedObject;

s32 GatherObjectsByMode(World* world, s32 flags, s32 id, void* scope, s32 max, void* found);
BaseObject* FindFirstObjectById(World* world, s32 flags, s32 id, void* scope);
BaseObject* FindFirstObjectByIdMode4(World* world, s32 id, void* scope);
BaseObject* FindFirstObjectByIdMode1(World* world, s32 id, void* scope);
s32 GatherObjectsById(World* world, u32 flags, s32 id, void* scope, s32 max, void* found);
PlacedObject* FindFirstObjectByIdGathered(World* world, s32 flags, s32 id, void* scope);

#endif
