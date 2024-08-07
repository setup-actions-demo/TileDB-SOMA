#!/usr/bin/env python
import hashlib
import sys


sha256 = hashlib.sha256()

for path in sys.argv[1:]:
    file_sha256 = hashlib.sha256()
    with open(path, "rb") as f:
        for byte_block in iter(lambda: f.read(4096), b""):
            file_sha256.update(byte_block)
    digest = file_sha256.digest()
    print(f"{path}: {digest.hex()}", file=sys.stderr)
    sha256.update(digest)

result = sha256.hexdigest()
print(result)
