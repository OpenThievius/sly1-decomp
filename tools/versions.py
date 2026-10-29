# SPDX-License-Identifier: AGPL-3.0-or-later
"""The game versions this repository knows, from config/versions.json.

Every tool takes its paths from here: a version's boot executable lives at
baserom/<version>/<boot name>, its splat configuration at
config/splat/<version>.yaml, and its generated assembly under asm/<version>/.
"""

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CONFIG = ROOT / "config" / "versions.json"
BASEROM = ROOT / "baserom"


def load():
    with open(CONFIG, encoding="utf-8") as f:
        return json.load(f)


def versions():
    return load()["versions"]


def primary():
    return load()["primary"]


def get(key):
    table = versions()
    if key not in table:
        raise KeyError("unknown version %r (known: %s)" % (key, ", ".join(table)))
    return table[key]


def boot_path(key):
    return BASEROM / key / get(key)["boot"]["name"]


def splat_config(key):
    return ROOT / "config" / "splat" / ("%s.yaml" % key)


def identify_boot(name, sha1):
    """The version whose boot executable has this name and SHA-1, or None."""
    for key, v in versions().items():
        if v["boot"]["name"] == name and v["boot"]["sha1"] == sha1:
            return key
    return None
