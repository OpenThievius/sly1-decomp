// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DEBUG_SCOPE_H
#define DEBUG_SCOPE_H

// The scope object of a debug build (a timer or a trace of the function it stands in), as the
// release build compiles it: an empty class whose constructor and destructor do nothing. An
// empty class is one byte, so the object is a QImode local, and the destructor takes its
// address: GCC 2.95 cannot keep a variable narrower than a word in a register once its address
// is taken (put_var_into_stack: no ADDRESSOF where PROMOTE_MODE widens the mode), so it gets
// a one-byte stack slot at once, ahead of every slot made later. The inlined bodies are empty,
// so nothing reads or writes the slot, and retail's frame shows where one stood
// (docs/toolchain/stack-slots.md, "A 4-byte slot nothing touches").
//
// Used only where retail's frame is proved to hold such a slot and nothing else explains it;
// each use says so in a comment. Written for this project; the name is our own.
struct DebugScope {
    DebugScope() {}
    ~DebugScope() {}
};

#endif
