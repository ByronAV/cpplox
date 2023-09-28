#!/usr/bin/env bash
set -eu

DIR="build"
function build() {

    echo "Building output files..."
    # Create build directory
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
}

function clean() {
    if [ -d "$DIR" ]; then
        echo "Removing build directory..."
        rm -rf "$DIR"
    fi
}

while [ $# -ne 0 ]; do
    case $1 in
        --build) #Build the bin output
            build
            ;;
        --clean)
            clean
            ;;
    esac
    shift
done

