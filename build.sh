#!/usr/bin/env bash
set -e

BUILD_TYPE=Debug
BUILD_DIR=build

C_COMPILER=clang
CPP_COMPILER=clang++

if [[ "$1" == "--release" ]]; then

    BUILD_DIR=build-release
    BUILD_TYPE=Release
fi

cmake -S . -B $BUILD_DIR \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_C_COMPILER=$C_COMPILER \
    -DCMAKE_CXX_COMPILER=$CPP_COMPILER

cmake --build $BUILD_DIR -j

echo "Done ($BUILD_TYPE)"

