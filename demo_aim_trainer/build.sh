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

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

cmake --build . --parallel


echo "Build finished!"