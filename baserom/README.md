# baserom: your own discs

Put an image of each disc you own here (any file name: an `.iso`, or the
`.img`/`.bin` of a raw CD dump). Everything in this directory except this file
is ignored by git and is never committed or shared ([LEGAL.md](../LEGAL.md)).

```sh
python3 tools/setup.py                  # every image in baserom/
python3 tools/setup.py ~/path/to/discs  # or wherever they are
```

`setup.py` recognises each image by the executable its `SYSTEM.CNF` boots and
that executable's SHA-1, and writes it to `baserom/<version>/`:

| Version | Written to | SHA-1 |
|---|---|---|
| `us` | `baserom/us/SCUS_971.98` | `57dc305db57932ad3f1122966cdb695d2e62a47a` |
| `eu` | `baserom/eu/SCES_509.17` | `f23240fc4a3efd463a5b3617b9250da4d5fe842c` |

The disc images' own checksums are in [config/versions.json](../config/versions.json).
The May 2002 prototype is recognised and skipped: nothing is taken from it
([docs/PROTOTYPE.md](../docs/PROTOTYPE.md)). Other releases (Greatest Hits,
other regions) are reported as unknown.
