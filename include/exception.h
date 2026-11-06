// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's exception base class and the exception an unexpected one becomes, named as
// their type information spells them in retail (docs/NAMING.md). The one file that says
// `#pragma implementation "exception.h"` (src/lib/exception.cpp) writes out their inline members,
// vtables and type information; every other file refers to them by name. Written for this
// project from retail's code.
#ifndef EXCEPTION_H
#define EXCEPTION_H
#pragma interface

class exception {
public:
    exception() {}
    virtual ~exception() {}
    virtual const char* what() const;
};

class bad_exception : public exception {
public:
    bad_exception() {}
    virtual ~bad_exception() {}
};

#endif
