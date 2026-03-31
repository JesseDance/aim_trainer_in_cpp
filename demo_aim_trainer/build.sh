#!/usr/bin/env bash

set -e

BUILD_DIR="build"
BUILD_TYPE="Release"

# Default target
TARGET="linux"

# Parse argument
if [ "$1" == "windows" ]; then
    TARGET="windows"
fi

echo "Building for: $TARGET"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

if [ "$TARGET" == "linux" ]; then
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
else
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
          -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-mingw64.cmake ..
fi

make -j$(nproc)

echo "Build finished!"