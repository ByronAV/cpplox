#!/usr/bin/env bash
set -eu

DIR="build"
function build() {
    # Check that CMake exists in user's machine
    if which cmake >/dev/null 2>&1; then

        if [ "$1" != "debug" ] && [ "$1" != "release" ]; then
            echo "Error configuring build."
            echo "Usage ./configure --build=<mode>: Build either in 'debug' or 'release' mode"
            exit 1
        fi
        
        echo "Building output files..."
        # Create build directory
        if [ -d "$DIR" ]; then
            cd build
        else
            mkdir build; cd build
        fi

        if [ "$1" == "debug" ]; then
            cmake -DCMAKE_BUILD_TYPE=Debug ..
        else
            cmake -DCMAKE_BUILD_TYPE=Release ..
        fi
    else
        echo "ERROR: This build needs CMake >v3.6"
        exit 1
    fi

    # Run the makefile
    make -j $(nproc)
}

function clean() {
    if [ -d "$DIR" ]; then
        echo "Removing build directory..."
        rm -rf "$DIR"
    else
        echo "No build directory present."
    fi
}

if [[ $# -eq 0 ]] ; then
    echo "Usage ./configure --build=<mode>: Build either in 'debug' or 'release' mode"
    echo "      ./configure --clean: Remove the build directory"
    exit 0
fi

while [ $# -ne 0 ]; do
    case "$1" in
        -*=*) optarg=`echo "$1" | sed 's/[-_a-zA-Z0-9]*=//'` ;;
        *) optarg= ;;
    esac

    case "$1" in
        --build=*) #Build the bin output
            build $optarg
            ;;
        --clean)
            clean
            ;;
    esac
    shift
done

