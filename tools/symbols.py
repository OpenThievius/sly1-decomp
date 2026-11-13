# SPDX-License-Identifier: AGPL-3.0-or-later
"""Address names and readable names, one mapping for every tool (docs/NAMING.md).

A symbol is written in source either by its address name (func_XXXXXXXX, D_XXXXXXXX) or by the
readable name config/names/ gives it (include/names.h turns the second into the first before the
compiler sees it). The tools that read source text, rather than objects, go through this module so
that both forms work:

    canonical("RegisterButtonCodes")    -> "func_0016F588"   (an address name stays as it is)
    readable("func_0016F588")           -> "RegisterButtonCodes"
    normalize(text)                     -> the text with every readable name turned into its address
    find_definition(text, "RegisterButtonCodes")  -> (start, end) of the definition, or None

The markers INCLUDE_ASM, ASM_FUNC, LINKER_REMNANT, LINKER_REMNANT_AFTER_INIT, INCLUDE_RODATA and
INCLUDE_DATA always take the address name: the build checks them against
config/us/original_asm.tsv, and they name the disassembly file they include.

The tables are read once per process. This module reads them without tools/names.py (which uses
this module for its converter).
"""

import functools
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
TABLES = ROOT / "config" / "names"
ADDRESS = re.compile(r"^(?:func(?:_[a-z]+)?|D)_[0-9A-F]{8}$")    # func_eu_XXXXXXXX: only PAL has it
IDENT = re.compile(r"\b[A-Za-z_]\w*\b")
MARKERS = ("INCLUDE_ASM", "ASM_FUNC", "LINKER_REMNANT", "LINKER_REMNANT_AFTER_INIT",
           "INCLUDE_RODATA", "INCLUDE_DATA")


def read_pairs(top=None):
    """[(address name, readable name)] of every row of the tables under config/names/."""
    top = Path(top) if top else TABLES
    out = []
    for path in sorted(top.rglob("*.tsv")) if top.exists() else []:
        for line in path.read_text().splitlines()[1:]:
            cells = line.split("\t")
            if len(cells) >= 2 and ADDRESS.match(cells[0]) and cells[1]:
                out.append((cells[0], cells[1]))
    return out


class Symbols:
    """The two directions of the tables."""

    def __init__(self, pairs):
        self.to_name = dict(pairs)                              # func_0016F588 -> RegisterButtonCodes
        self.to_address = {n: a for a, n in self.to_name.items()}
        self._pattern = None

    def canonical(self, name):
        """The address name of a symbol given either way; an unknown name comes back as it is."""
        return self.to_address.get(name, name)

    def readable(self, symbol):
        """The readable name of an address name, or the address name when it has none."""
        return self.to_name.get(symbol, symbol)

    def normalize(self, text):
        """`text` with each readable name replaced by its address name (as the preprocessor would
        make it), for the tools that match address names in source. Newlines are kept, so a line
        number is the same; columns are not."""
        if not self.to_address:
            return text
        table = self.to_address
        return IDENT.sub(lambda m: table.get(m.group(0), m.group(0)), text)


@functools.lru_cache(maxsize=None)
def load():
    return Symbols(read_pairs())


def reload():
    """Forget the cached tables (a test or a long-lived process that has changed them)."""
    load.cache_clear()


def canonical(name):
    return load().canonical(name)


def readable(symbol):
    return load().readable(symbol)


def normalize(text):
    return load().normalize(text)


def find_definition(text, symbol):
    """(start, end) of `symbol`'s definition in a source text, from its first line to its closing
    brace, whether the file writes the address name or the readable one; None when there is none."""
    import version_src
    try:
        return version_src.definition_span(text, canonical(symbol))
    except version_src.VersionSourceError:
        return None
