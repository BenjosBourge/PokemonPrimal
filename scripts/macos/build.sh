#!/bin/bash

function usage() {
    echo "Usage: $0 [args]"
    printf "\t--pkg\t\tPackage the project into a .zip file.\n"
    printf "\t--build\t\tBuild the whole project using cmake & ninja.\n"
    printf "\t--doc\t\tLaunch documentation generation.\n"
}

function build() {
    echo "[INFO]: Building project."

    rm -rf build/

    mkdir build && cd build

    cmake -G Ninja ..

    ninja

    cp bin/r-type_client .
    cp bin/r-type_server .
}

function pkg() {
    if [ ! -d "build" ]; then
        build
    fi
    echo "[INFO]: Packaging project."

    cd build

    cpack -G TGZ
}

function doc() {
    echo "[INFO]: Documenting project."

    doxygen Doxyfile
}

if [ "$1" = "--build" ]; then
    build
elif [ "$1" = "--pkg" ]; then
    pkg
elif [ "$1" = "--doc" ]; then
    doc
else
    usage
fi
