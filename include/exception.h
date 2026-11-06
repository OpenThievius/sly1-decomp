// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's exception base class, named as its type information spells it in retail
// (docs/NAMING.md). Its out-of-line members and vtable belong to the runtime's exception file;
// with `#pragma interface` every other file refers to them by name. Written for this project
// from retail's code.
#ifndef EXCEPTION_H
#define EXCEPTION_H
#pragma interface

class exception {
public:
    exception() {}
    virtual ~exception() {}
    virtual const char* what() const;
};

#endif
