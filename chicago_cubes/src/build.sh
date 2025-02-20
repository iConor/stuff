#!/bin/bash


if [ ! -d ../build ]; then mkdir ../build; fi
pushd ../build > /dev/null


clang ../src/sdl_main.cpp -o sdl_main -DGL_SILENCE_DEPRECATION -framework OpenGL -framework SDL2 -F /Library/Frameworks/


popd > /dev/null
