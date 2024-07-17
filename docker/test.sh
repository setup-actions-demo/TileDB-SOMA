#!/usr/bin/env bash

set -e

if [ $# -ne 1 ]; then
    echo "Usage: $0 <ref>" >&2
    exit 1
fi

ref="$1"
echo "Building ref $ref"
img=tiledb-soma-$ref
# Invert exit code; `git bisect` assumes newer = broken, older = working, but in this case it's the opposite: build
# works on recent commits, we're looking for most recent broken commit.
docker build -t $img --build-arg ref=$ref .
