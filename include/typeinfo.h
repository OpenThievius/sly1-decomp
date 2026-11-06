// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's type information, its classes named as retail's type-name strings spell them
// (docs/NAMING.md). The one file that says `#pragma implementation "typeinfo.h"`
// (src/lib/type_info.cpp) writes out their inline members, vtables and type information.
// Written for this project from retail's code.
#ifndef TYPEINFO_H
#define TYPEINFO_H
#pragma interface

#include "exception.h"

class type_info {
    const char* name_;

protected:
    type_info(const char* name) : name_(name) {}

public:
    virtual ~type_info();
    const char* name() const { return name_; }
    bool operator==(const type_info& other) const;
    bool operator!=(const type_info& other) const { return !operator==(other); }
};

// What a failed cast to a reference throws.
class bad_cast : public exception {
public:
    bad_cast() {}
    virtual ~bad_cast() {}
};

// What typeid of a null pointer throws.
class bad_typeid : public exception {
public:
    bad_typeid() {}
    virtual ~bad_typeid() {}
};

// A class's type information, which can find a base inside an object of the class.
class __user_type_info : public type_info {
public:
    __user_type_info(const char* name) : type_info(name) {}
    // The address of the `target` subobject of the object at `object`, or 0.
    virtual void* dcast(const type_info& target, int publicOnly, void* object,
                        const type_info* sub = 0, void* subObject = 0) const;
};

// A class with one public, non-virtual base at offset 0.
class __si_type_info : public __user_type_info {
    const __user_type_info& base_;

public:
    __si_type_info(const char* name, const __user_type_info& base)
        : __user_type_info(name), base_(base) {}
    virtual void* dcast(const type_info& target, int publicOnly, void* object,
                        const type_info* sub = 0, void* subObject = 0) const;
};

// Any other class: its list of bases.
class __class_type_info : public __user_type_info {
public:
    enum Access { PUBLIC = 1, PROTECTED = 2, PRIVATE = 3 };
    struct Base {
        const __user_type_info* type;
        unsigned int offset : 29;
        bool isVirtual : 1;
        Access access : 2;
    };

private:
    const Base* bases_;
    size_t count_;

public:
    __class_type_info(const char* name, const Base* bases, size_t count)
        : __user_type_info(name), bases_(bases), count_(count) {}
    virtual void* dcast(const type_info& target, int publicOnly, void* object,
                        const type_info* sub = 0, void* subObject = 0) const;
};

#endif
