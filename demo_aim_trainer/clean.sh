#!/usr/bin/env bash

set -e

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    echo "Removing $BUILD_DIR directory..."
    rm -rf "$BUILD_DIR"
    echo "Clean complete."
else
    echo "No build directory found."
fi