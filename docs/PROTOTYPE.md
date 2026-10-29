# The May 2002 prototype

**PS2 - Sly E3 Build 5-19D For Preview Only**: a preview disc dated
2002-05-19, three months before the NTSC-U release (2002-08-24 on its disc). It
is a raw CD dump (`MODE2/2352` `.img` with `.cue`, `.ccd` and `.sub`); the
disc's SHA-1 and its executable's are in [`config/versions.json`](../config/versions.json)
under `may19`. `tools/setup.py` recognises it, says so, and extracts nothing
from it.

Its executable (12,523,740 bytes, against retail's 1,712,328) was not
stripped: it keeps a symbol table and debug information. That is why it is
tempting, and why the rule below is strict.

## The rule: nothing is taken from it

**Nothing from the prototype is copied into this repository.** Not its code
or data, and not what its symbols and debug information say either:

- no symbol names, mangled signatures or symbol tables;
- no type, class or structure definitions, field names or layouts;
- no source file names, paths or file lists;
- no tool that extracts any of these into a form ready to copy.

Everything the project commits is derived from **retail's own code**: we read
what a function does and name it, type it and place it ourselves. Working on a
hard function, you may look at the prototype to understand what the game is
doing, and then write your own version: different names, your own structure,
reasoned from retail's bytes. Copying something across unchanged, or with
cosmetic edits, is not allowed. If you are unsure whether something counts as
your own, treat it as copied.

The prototype is also **never the evidence for a match**. A match is always
retail's bytes in a build that equals retail.

## Why it is listed at all

`config/versions.json` records its checksums so that tools recognise the disc
and never mistake it for retail, and so that research notes can say which build
they describe. Its role there is `reference`, and no build, check or progress
report uses it.
