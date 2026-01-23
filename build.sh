#!/usr/bin/env bash

set -e

rm -rf build
mkdir build

echo "[*] Configuring cmake and creating compile commands.json"
cd build
cmake -S .. -B . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make -j

echo "Done"
