# SPDX-License-Identifier: AGPL-3.0-or-later
"""Read files out of a PlayStation 2 disc image, with the standard library only.

Handles plain ISO 9660 images (2048-byte sectors) and raw CD images
(2352-byte sectors, Mode 1 or Mode 2 Form 1, as a .bin/.img beside a .cue),
which is how the May 2002 prototype is dumped.

    python3 tools/disc.py info IMAGE           # layout, SYSTEM.CNF, root files
    python3 tools/disc.py extract IMAGE NAME OUT

This file is shared with OpenThievius (tools/disc.py there); keep the two
copies identical (OpenThievius's shared/files.json lists them).
"""

import argparse
import hashlib
import os
import struct
import sys
import zlib

SECTOR = 2048
RAW_SECTOR = 2352
SYNC = b"\x00" + b"\xff" * 10 + b"\x00"


class DiscError(Exception):
    pass


class Disc:
    """An open disc image: its sector layout and its ISO 9660 root."""

    def __init__(self, path):
        self.path = path
        self.size = os.path.getsize(path)
        self._f = open(path, "rb")
        self.raw = self._detect_raw()
        pvd = self.read_sectors(16, 1)
        if pvd[0:1] != b"\x01" or pvd[1:6] != b"CD001":
            self.close()
            raise DiscError("%s: no ISO 9660 volume descriptor at sector 16" % path)
        self.volume_id = pvd[40:72].decode("ascii", "replace").strip()
        self.root = _parse_record(pvd[156:190])

    def close(self):
        self._f.close()

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        self.close()

    def _detect_raw(self):
        if self.size % RAW_SECTOR:
            return False
        self._f.seek(16 * RAW_SECTOR)
        return self._f.read(12) == SYNC

    def read_sectors(self, lba, count):
        if not self.raw:
            self._f.seek(lba * SECTOR)
            return self._f.read(count * SECTOR)
        out = []
        self._f.seek(lba * RAW_SECTOR)
        for _ in range(count):
            raw = self._f.read(RAW_SECTOR)
            if len(raw) < RAW_SECTOR:
                break
            # Byte 15 is the mode; Mode 2 Form 1 has an 8-byte subheader first.
            start = 24 if raw[15] == 2 else 16
            out.append(raw[start:start + SECTOR])
        return b"".join(out)

    def read_extent(self, lba, size):
        return self.read_sectors(lba, (size + SECTOR - 1) // SECTOR)[:size]

    def listdir(self, record=None):
        record = record or self.root
        data = self.read_extent(record["lba"], record["size"])
        entries, pos = [], 0
        while pos < len(data):
            length = data[pos]
            if length == 0:  # records never cross a sector: skip to the next one
                pos = (pos // SECTOR + 1) * SECTOR
                continue
            entry = _parse_record(data[pos:pos + length])
            if entry["name"] not in ("\x00", "\x01"):
                entries.append(entry)
            pos += length
        return entries

    def find(self, path):
        record = self.root
        for part in path.replace("\\", "/").strip("/").split("/"):
            want = part.upper()
            for entry in self.listdir(record):
                if entry["name"].upper() == want:
                    record = entry
                    break
            else:
                raise DiscError("%s: %s not on the disc" % (self.path, path))
        return record

    def read_file(self, path):
        record = self.find(path)
        return self.read_extent(record["lba"], record["size"])

    def system_cnf(self):
        text = self.read_file("SYSTEM.CNF").decode("ascii", "replace")
        fields = {}
        for line in text.splitlines():
            if "=" in line:
                key, value = line.split("=", 1)
                fields[key.strip()] = value.strip()
        return fields

    def boot_name(self):
        """The executable SYSTEM.CNF boots, e.g. SCUS_971.98."""
        boot = self.system_cnf().get("BOOT2", "")
        name = boot.split(":", 1)[-1].lstrip("\\/").split(";", 1)[0]
        if not name:
            raise DiscError("%s: SYSTEM.CNF names no BOOT2 executable" % self.path)
        return name


def _parse_record(rec):
    lba = struct.unpack_from("<I", rec, 2)[0]
    size = struct.unpack_from("<I", rec, 10)[0]
    flags = rec[25]
    name_len = rec[32]
    name = rec[33:33 + name_len].decode("ascii", "replace")
    if not flags & 2:
        name = name.split(";", 1)[0]
    return {"name": name, "lba": lba, "size": size, "dir": bool(flags & 2)}


def checksums(path_or_bytes):
    """CRC32, MD5, SHA-1 and SHA-256 of a file or a bytes object."""
    hashes = {n: hashlib.new(n) for n in ("md5", "sha1", "sha256")}
    crc = 0

    def feed(block):
        nonlocal crc
        crc = zlib.crc32(block, crc)
        for h in hashes.values():
            h.update(block)

    if isinstance(path_or_bytes, (bytes, bytearray)):
        feed(path_or_bytes)
        size = len(path_or_bytes)
    else:
        size = os.path.getsize(path_or_bytes)
        with open(path_or_bytes, "rb") as f:
            for block in iter(lambda: f.read(1 << 22), b""):
                feed(block)
    result = {n: h.hexdigest() for n, h in hashes.items()}
    result["crc32"] = "%08x" % crc
    result["size"] = size
    return result


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = parser.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("info", help="print the image's layout, SYSTEM.CNF and root files")
    p.add_argument("image")
    p = sub.add_parser("extract", help="copy one file out of the image")
    p.add_argument("image")
    p.add_argument("name")
    p.add_argument("out")
    args = parser.parse_args(argv)

    try:
        with Disc(args.image) as disc:
            if args.cmd == "info":
                print("image:   %s (%s sectors)" % (args.image, "raw 2352-byte" if disc.raw else "2048-byte"))
                print("volume:  %s" % disc.volume_id)
                print("boots:   %s" % disc.boot_name())
                for entry in disc.listdir():
                    print("  %-16s %12d%s" % (entry["name"], entry["size"], "  <dir>" if entry["dir"] else ""))
            else:
                data = disc.read_file(args.name)
                with open(args.out, "wb") as f:
                    f.write(data)
                print("%s: %d bytes, sha1 %s" % (args.out, len(data), hashlib.sha1(data).hexdigest()))
    except DiscError as e:
        print("error: %s" % e, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
