// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DEBUG_ASSERT_H
#define DEBUG_ASSERT_H

// The assertion macro of a debug build, as the release build compiles it: nothing, in the form a
// statement macro takes. GCC 2.95 still marks an empty loop that runs once with its loop notes,
// which end a CSE path and are a scheduling barrier, so retail's code shows where one stood.
//
// Used only where retail's code is proved to need those notes and the site is one where an
// assertion plausibly stood (AGENTS.md, "Matching rules"); each use says so in a comment and
// names its section of docs/toolchain/. Written for this project; the name is our own.
#define ASSERT(cond) do { } while (0)

#endif
