// SPDX-License-Identifier: AGPL-3.0-or-later
// BROKEN, checked 2026-11-01
// SKIP: retail entry starts with addiu $sp,$sp,+0xC0, then nop, before the
// function creates a 0x20-byte frame. AGENT_WORKFLOW.md section 4 says to stop
// on a stray stack increment; this is not a standalone function entry.
