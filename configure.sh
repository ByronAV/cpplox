#!/usr/bin/env bash
set -eu

DIR="build"
CMAKEFLAGS=""

function append_cmake_flags() {
    CMAKEFLAGS="$CMAKEFLAGS -D $1:$2=$3"
}

function clean() {
    if [ -d "$DIR" ]; then
        echo "Removing build directory..."
        rm -rf "$DIR"
    else
        echo "No build directory present."
    fi
}

function help_message() {
    echo "Usage ./configure --build=<mode>: Build either in 'Debug' or 'Release' mode"
    echo "                  --clean: Remove the build directory"
    echo "                  --enable-tests, -t: Builds tests"
}

if [[ $# -eq 0 ]] ; then
    help_message
    exit 1
fi

while [ $# -ne 0 ]; do
    case "$1" in
        -*=*) optarg=`echo "$1" | sed 's/[-_a-zA-Z0-9]*=//'` ;;
        *) optarg= ;;
    esac

    case "$1" in
        --build=*) #Build the bin output
            append_cmake_flags CMAKE_BUILD_TYPE STRING $optarg
            ;;
        --clean)
            clean
            exit 0
            ;;
        --enable-tests|-t)
            append_cmake_flags ENABLE_TESTING BOOL true
            ;;
        --help|-h)
            help_message
            exit 0
            ;;
        *)
            echo "Flag not supported: Use --help for information"
            exit 1
            ;;
    esac
    shift
done

# Check that CMake exists in user's machine
if which cmake >/dev/null 2>&1; then

    if [[ $CMAKEFLAGS != *"Debug"* ]] && [[ $CMAKEFLAGS != *"Release"* ]]; then
        echo "Error configuring build."
        help_message
        exit 1
    fi
    
    echo "Building output files..."
    # Create build directory
    if [ -d "$DIR" ]; then
        cd build
    else
        mkdir build; cd build
    fi

    if [[ $CMAKEFLAGS == *"Debug"* ]]; then
        cmake $CMAKEFLAGS ..
    else
        cmake -DCMAKE_BUILD_TYPE=Release ..
    fi
else
    echo "ERROR: This build needs CMake >v3.6"
    exit 1
fi

# Run the makefile
make -j $(nproc)