#!/bin/bash

function delete() {
    find "$1" -name "$2" -print -exec rm -rf {} \; 2> /dev/null
}

# cmake
delete . build
delete dependencies include
delete dependencies "lib*"
delete dependencies bin
delete dependencies share
delete . Debug
delete . Release

# bin
delete . "arcade"
delete . "*.exe"

# data
delete . "save.txt"

# libs
delete lib "*.so"
delete lib "*.dylib"
delete lib "*.dll"

# debug
delete . "*.ilk"
delete . "*.pdb"
delete . "vgcore*"
delete . "peda-session-*.txt"

# tests
delete . "unit_tests"