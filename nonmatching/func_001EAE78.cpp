// SPDX-License-Identifier: AGPL-3.0-or-later
// SKIP: the plain-C++ attempt fails to compile: SN GCC 2.95.3 reports
// “unsupported wide integer operation” for the 64-bit significand mask/shift.
// AGENT_WORKFLOW.md section 4 says to stop when C cannot express the required
// instruction operation; no inline assembly or compiler workaround is allowed.
