#!/bin/bash

## This file has a non-standard name not known to R and will not be part
## of any source package *.tar.gz created by R CMD BUILD or a alike.

test -d inst/include/tiledbsoma && \
    rm -rf test -d inst/include/tiledbsoma

test -f src/soma_reader.cc && \
    rm -rf src/pyapi/ src/thread_pool/ src/*.cc src/logger.h src/CMakeLists.txt
