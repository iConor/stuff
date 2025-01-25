#!/bin/bash






if [ ! -d build ]; then mkdir build; fi
pushd build > /dev/null


clang -o sdl2_main ../src/sdl2_main.cpp  -framework OpenGL `sdl2-config --cflags --libs`


popd > /dev/null
