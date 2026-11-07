// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's type information, the whole object, 0x200080-0x200750: type_info's destructor
// and comparison, the three routines the compiler calls to fill in a class's type information,
// and the three casts that find a base inside an object; the compiler writes out here
// (`#pragma implementation`) the inline members of include/typeinfo.h, the classes' vtables and
// their type information. C++, built by the Linux cc1plus of 2.9-ee-991111 (config/cflags.tsv,
// docs/TOOLCHAIN.md); the functions keep retail's names (config/us/generated.tsv). Written for
// this project from retail's code.
#include "common.h"
#include "placement.h"
#include "new.h"
#pragma implementation "typeinfo.h"
#include "typeinfo.h"

extern "C" int func_001F6738(const char* a, const char* b);

type_info::~type_info()
{
}

bool type_info::operator==(const type_info& other) const
{
    return &other == this || CompareStrings(name_, other.name_) == 0;
}

extern "C" void __rtti_class(void* at, const char* name, const __class_type_info::Base* bases, size_t count)
{
    new (at) __class_type_info(name, bases, count);
}

extern "C" void __rtti_si(void* at, const char* name, const type_info* base)
{
    new (at) __si_type_info(name, static_cast<const __user_type_info&>(*base));
}

extern "C" void __rtti_user(void* at, const char* name)
{
    new (at) __user_type_info(name);
}

void* __user_type_info::findBase(const type_info& target, int, void* object, const type_info*, void*) const
{
    return *this == target ? object : 0;
}

void* __si_type_info::findBase(const type_info& target, int publicOnly, void* object, const type_info* sub,
                            void* subObject) const
{
    if (*this == target)
        return object;
    return base_.findBase(target, publicOnly, object, sub, subObject);
}

void* __class_type_info::findBase(const type_info& target, int publicOnly, void* object, const type_info* sub,
                               void* subObject) const
{
    void* found;
    size_t i;

    if (*this == target)
        return object;
    found = 0;
    for (i = 0; i < count_; i++) {
        void* p;
        if (publicOnly && bases_[i].access != PUBLIC)
            continue;
        p = (char*)object + bases_[i].offset;
        if (bases_[i].isVirtual)
            p = *(void**)p;
        p = bases_[i].type->findBase(target, publicOnly, p, sub, subObject);
        if (p != 0) {
            if (found == 0) {
                found = p;
            } else if (found != p) {
                if (sub != 0) {
                    const __user_type_info& t = static_cast<const __user_type_info&>(target);
                    void* a = t.findBase(*sub, 1, found);
                    void* b = t.findBase(*sub, 1, p);
                    if (a == b) {
                    } else if (a == subObject) {
                        continue;
                    } else if (b == subObject) {
                        found = p;
                        continue;
                    }
                }
                return 0;
            }
        }
    }
    return found;
}
