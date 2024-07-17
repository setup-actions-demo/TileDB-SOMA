#!/usr/bin/env bash

set -e

ref="$(git log -1 --format=%h $(cat .git/BISECT_HEAD))"

# Invert exit code; `git bisect` assumes newer = broken, older = working, but in this case it's the opposite: build
# works on recent commits, we're looking for most recent broken commit.
! ./docker-test.sh "$ref"
