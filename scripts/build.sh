#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"


BUILD_TYPE=Debug
BUILD_DIR="$PROJECT_ROOT/build"

C_COMPILER=clang
CPP_COMPILER=clang++

CXX_FLAGS=""
LINK_FLAGS=""

if [[ "$CPP_COMPILER" == "clang++" ]]; then
    CXX_FLAGS="-stdlib=libc++"
    LINK_FLAGS="-stdlib=libc++"
fi

if [[ "$1" == "--release" ]]; then

    BUILD_DIR=build-release
    BUILD_TYPE=Release
fi

cmake -S . -B $BUILD_DIR \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_C_COMPILER=$C_COMPILER \
    -DCMAKE_CXX_COMPILER=$CPP_COMPILER \
    -DCMAKE_CXX_FLAGS=$CXX_FLAGS

cmake --build $BUILD_DIR -j

echo "Done ($BUILD_TYPE)"

