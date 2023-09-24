#!/usr/bin/env bash
set -eu

# Create build directory
DIR="build"
if [ -d "$DIR" ]; then
    cd build
else
    mkdir build; cd build
fi

# Check that CMake exists in user's machine
if which cmake >/dev/null 2>&1; then
    cmake ..
else
    echo "This build needs CMake >v3.6"
    exit 1
fi

# Run the makefile
make