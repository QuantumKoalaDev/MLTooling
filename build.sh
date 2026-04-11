#!/usr/bin/env bash
set -e

BUILD_TYPE=Debug

cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build -j

echo "Done ($BUILD_TYPE)"
