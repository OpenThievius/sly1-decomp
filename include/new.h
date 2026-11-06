// SPDX-License-Identifier: AGPL-3.0-or-later
// The allocation failure the C++ runtime throws, named as its type information spells it in
// retail (docs/NAMING.md). Its inline members, vtable and type information are written out by
// the one file that says `#pragma implementation "new.h"` (src/lib/new_handler.cpp). Written for
// this project from retail's code.
#ifndef NEW_H
#define NEW_H
#pragma interface

#include "exception.h"

class bad_alloc : public exception {
public:
    virtual const char* what() const { return "bad_alloc"; }
};

#endif
