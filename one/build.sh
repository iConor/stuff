#!/bin/bash

if [ ! -d build ]; then mkdir build; fi
pushd build > /dev/null


clang -o main ../src/main.cpp


popd > /dev/null
