// SPDX-License-Identifier: AGPL-3.0-or-later
// Placement allocation: the memory is given. Written for this project.
#ifndef PLACEMENT_H
#define PLACEMENT_H

typedef unsigned int size_t;

inline void* operator new(size_t, void* place) throw() { return place; }

#endif
