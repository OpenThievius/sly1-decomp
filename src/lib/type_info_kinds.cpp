// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's type information, second part, the whole object 0x200750-0x2014D0: the
// ordering of two types, the match of a thrown type against a handler's, the routines the compiler
// calls to fill in the type information of pointers, qualified types, functions, members and
// arrays, the dynamic cast, and the type information of the builtin types; the compiler writes
// out the classes of those kinds (defined here, so their constructors stay inline), their
// vtables and type information. C++, built by the Linux cc1plus of 2.9-ee-991111
// (config/cflags.tsv, docs/TOOLCHAIN.md); the classes are named as retail's type-name strings
// spell them (docs/NAMING.md). Written for this project from retail's code.
#include "common.h"
#include "placement.h"
#include "new.h"
#include "typeinfo.h"

extern "C" int func_001F6738(const char* a, const char* b);

// A pointer type: what it points to.
class __pointer_type_info : public type_info {
public:
    const type_info& type;

    __pointer_type_info(const char* name, const type_info& target) : type_info(name), type(target) {}
};

// A qualified type: its qualifiers (1 const, 2 volatile) and the type they qualify.
class __attr_type_info : public type_info {
public:
    enum Qualifiers { NONE = 0, CONST = 1, VOLATILE = 2, CONST_VOLATILE = 3 };

    const type_info& type;
    Qualifiers attr;

    __attr_type_info(const char* name, Qualifiers qualifiers, const type_info& target)
        : type_info(name), type(target), attr(qualifiers) {}
};

// A builtin type.
class __builtin_type_info : public type_info {
public:
    __builtin_type_info(const char* name) : type_info(name) {}
};

// A function type.
class __func_type_info : public type_info {
public:
    __func_type_info(const char* name) : type_info(name) {}
};

// A pointer to member function.
class __ptmf_type_info : public type_info {
public:
    __ptmf_type_info(const char* name) : type_info(name) {}
};

// A pointer to data member.
class __ptmd_type_info : public type_info {
public:
    __ptmd_type_info(const char* name) : type_info(name) {}
};

// An array type.
class __array_type_info : public type_info {
public:
    __array_type_info(const char* name) : type_info(name) {}
};

// The type information of void (defined below with the other builtin types).
extern "C" const type_info& func_00200E08(void);

bool type_info::before(const type_info& other) const
{
    return func_001F6738(name_, other.name_) < 0;
}

// The object a handler for `want` receives when `have` is thrown at `object`, or 0.
extern "C" void* func_00200778(const type_info* want, const type_info* have, void* object)
{
    void* found;
    const __user_type_info* user;

    if (*want == *have)
        return object;
    found = 0;
    user = dynamic_cast<const __user_type_info*>(have);
    if (user != 0) {
        found = user->findBase(*want, 1, object, 0, 0);
    } else {
        const __pointer_type_info* from = dynamic_cast<const __pointer_type_info*>(have);
        if (from != 0) {
            const __pointer_type_info* to = dynamic_cast<const __pointer_type_info*>(want);
            if (to != 0) {
                const type_info* subFrom = &from->type;
                const type_info* subTo = &to->type;
                int cvFrom;
                int cvTo;
                const __attr_type_info* at = dynamic_cast<const __attr_type_info*>(subFrom);
                if (at != 0) {
                    cvFrom = at->attr;
                    subFrom = &at->type;
                } else {
                    cvFrom = 0;
                }
                at = dynamic_cast<const __attr_type_info*>(subTo);
                if (at != 0) {
                    cvTo = at->attr;
                    subTo = &at->type;
                } else {
                    cvTo = 0;
                }
                if ((cvFrom & 1) <= (cvTo & 1) && (cvFrom & 2) <= (cvTo & 2)) {
                    if (*subTo == *subFrom) {
                        found = object;
                    } else if (*subTo == func_00200E08()
                               && dynamic_cast<const __func_type_info*>(subFrom) == 0) {
                        found = object;
                    } else if ((user = dynamic_cast<const __user_type_info*>(subFrom)) != 0) {
                        found = user->findBase(*subTo, 1, object, 0, 0);
                    } else {
                        const __pointer_type_info* pointerFrom = dynamic_cast<const __pointer_type_info*>(subFrom);
                        if (pointerFrom != 0) {
                            const __pointer_type_info* pointerTo = dynamic_cast<const __pointer_type_info*>(subTo);
                            if (pointerTo != 0) {
                                int allConst = cvTo & 1;
                                subTo = &pointerTo->type;
                                subFrom = &pointerFrom->type;
                                for (;;) {
                                    at = dynamic_cast<const __attr_type_info*>(subFrom);
                                    if (at != 0) {
                                        cvFrom = at->attr;
                                        subFrom = &at->type;
                                    } else {
                                        cvFrom = 0;
                                    }
                                    at = dynamic_cast<const __attr_type_info*>(subTo);
                                    if (at != 0) {
                                        cvTo = at->attr;
                                        subTo = &at->type;
                                    } else {
                                        cvTo = 0;
                                    }
                                    if ((cvFrom & 1) > (cvTo & 1) || (cvFrom & 2) > (cvTo & 2))
                                        goto done;
                                    if (!allConst && ((cvFrom & 1) < (cvTo & 1) || (cvFrom & 2) < (cvTo & 2)))
                                        goto done;
                                    if (*subTo == *subFrom) {
                                        found = object;
                                        break;
                                    }
                                    pointerTo = dynamic_cast<const __pointer_type_info*>(subTo);
                                    pointerFrom = dynamic_cast<const __pointer_type_info*>(subFrom);
                                    if (pointerTo == 0 || pointerFrom == 0)
                                        goto done;
                                    if (!(cvTo & 1))
                                        allConst = 0;
                                    subTo = &pointerTo->type;
                                    subFrom = &pointerFrom->type;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
done:
    return found;
}

// Whether a type is a pointer type.
extern "C" bool func_00200C40(const type_info* type)
{
    const __pointer_type_info* pointer = dynamic_cast<const __pointer_type_info*>(type);
    return pointer != 0;
}

extern "C" void func_00200C90(void* at, const char* name, const type_info* target)
{
    new (at) __pointer_type_info(name, *target);
}

extern "C" void func_00200CB0(void* at, const char* name, int qualifiers, const type_info* target)
{
    new (at) __attr_type_info(name, (__attr_type_info::Qualifiers)qualifiers, *target);
}

extern "C" void func_00200CD8(void* at, const char* name)
{
    new (at) __func_type_info(name);
}

extern "C" void func_00200CF8(void* at, const char* name)
{
    new (at) __ptmf_type_info(name);
}

extern "C" void func_00200D18(void* at, const char* name)
{
    new (at) __ptmd_type_info(name);
}

extern "C" void func_00200D38(void* at, const char* name)
{
    new (at) __array_type_info(name);
}

// The compiler's dynamic cast: the `to` subobject of the object at `address`, whose type
// `from` gives, or 0.
extern "C" void* __dynamic_cast(const type_info& (*from)(void), const type_info& (*to)(void), int publicOnly,
                                void* address, const type_info& (*sub)(void), void* subObject)
{
    return static_cast<const __user_type_info&>(from()).findBase(to(), publicOnly, address, &sub(), subObject);
}

// The type information of the builtin types, each built in its own storage when first asked for.
void* D_00278E00[2] = { 0, 0 };
void* D_00278E08[2] = { 0, 0 };
void* D_00278E10[2] = { 0, 0 };
void* D_00278E18[2] = { 0, 0 };
void* D_00278E20[2] = { 0, 0 };
void* D_00278E28[2] = { 0, 0 };
void* D_00278E30[2] = { 0, 0 };
void* D_00278E38[2] = { 0, 0 };
void* D_00278E40[2] = { 0, 0 };
void* D_00278E48[2] = { 0, 0 };
void* D_00278E50[2] = { 0, 0 };
void* D_00278E58[2] = { 0, 0 };
void* D_00278E60[2] = { 0, 0 };
void* D_00278E68[2] = { 0, 0 };
void* D_00278E70[2] = { 0, 0 };
void* D_00278E78[2] = { 0, 0 };
void* D_00278E80[2] = { 0, 0 };

extern "C" const type_info& func_00200E08(void)
{
    if (D_00278E00[0] == 0)
        new (D_00278E00) __builtin_type_info("v");
    return *(const type_info*)D_00278E00;
}

extern "C" const type_info& func_00200E40(void)
{
    if (D_00278E08[0] == 0)
        new (D_00278E08) __builtin_type_info("x");
    return *(const type_info*)D_00278E08;
}

extern "C" const type_info& func_00200E78(void)
{
    if (D_00278E10[0] == 0)
        new (D_00278E10) __builtin_type_info("l");
    return *(const type_info*)D_00278E10;
}

extern "C" const type_info& func_00200EB0(void)
{
    if (D_00278E18[0] == 0)
        new (D_00278E18) __builtin_type_info("i");
    return *(const type_info*)D_00278E18;
}

extern "C" const type_info& func_00200EE8(void)
{
    if (D_00278E20[0] == 0)
        new (D_00278E20) __builtin_type_info("s");
    return *(const type_info*)D_00278E20;
}

extern "C" const type_info& func_00200F20(void)
{
    if (D_00278E28[0] == 0)
        new (D_00278E28) __builtin_type_info("b");
    return *(const type_info*)D_00278E28;
}

extern "C" const type_info& func_00200F58(void)
{
    if (D_00278E30[0] == 0)
        new (D_00278E30) __builtin_type_info("c");
    return *(const type_info*)D_00278E30;
}

extern "C" const type_info& func_00200F90(void)
{
    if (D_00278E38[0] == 0)
        new (D_00278E38) __builtin_type_info("w");
    return *(const type_info*)D_00278E38;
}

extern "C" const type_info& func_00200FC8(void)
{
    if (D_00278E40[0] == 0)
        new (D_00278E40) __builtin_type_info("r");
    return *(const type_info*)D_00278E40;
}

extern "C" const type_info& func_00201000(void)
{
    if (D_00278E48[0] == 0)
        new (D_00278E48) __builtin_type_info("d");
    return *(const type_info*)D_00278E48;
}

extern "C" const type_info& func_00201038(void)
{
    if (D_00278E50[0] == 0)
        new (D_00278E50) __builtin_type_info("f");
    return *(const type_info*)D_00278E50;
}

extern "C" const type_info& func_00201070(void)
{
    if (D_00278E58[0] == 0)
        new (D_00278E58) __builtin_type_info("Ui");
    return *(const type_info*)D_00278E58;
}

extern "C" const type_info& func_002010A8(void)
{
    if (D_00278E60[0] == 0)
        new (D_00278E60) __builtin_type_info("Ul");
    return *(const type_info*)D_00278E60;
}

extern "C" const type_info& func_002010E0(void)
{
    if (D_00278E68[0] == 0)
        new (D_00278E68) __builtin_type_info("Ux");
    return *(const type_info*)D_00278E68;
}

extern "C" const type_info& func_00201118(void)
{
    if (D_00278E70[0] == 0)
        new (D_00278E70) __builtin_type_info("Us");
    return *(const type_info*)D_00278E70;
}

extern "C" const type_info& func_00201150(void)
{
    if (D_00278E78[0] == 0)
        new (D_00278E78) __builtin_type_info("Uc");
    return *(const type_info*)D_00278E78;
}

extern "C" const type_info& func_00201188(void)
{
    if (D_00278E80[0] == 0)
        new (D_00278E80) __builtin_type_info("Sc");
    return *(const type_info*)D_00278E80;
}
