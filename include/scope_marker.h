// SPDX-License-Identifier: AGPL-3.0-or-later
// An object of a class whose destructor emits no code. Written for this project.
// Some of retail's frames hold one unread slot of 1 to 4 bytes right after the function's
// aggregate locals and before its address-taken scalars and spills. An object of a class with a
// non-trivial destructor is addressable, so expand_decl gives it a stack slot even when it is
// empty and never read; nothing else of that size and kind fits (docs/TOOLCHAIN.md, "An object
// with a destructor keeps a slot"). The original's class is unknown, plausibly a scope object
// whose body is compiled out in release builds. Used only where a retail frame shows exactly
// this slot: func_0014B6A8, func_001DC238, func_001DC4D0 and func_0015A198.
#ifndef SCOPE_MARKER_H
#define SCOPE_MARKER_H

struct ScopeMarker {
    ~ScopeMarker() {}
};

#endif
