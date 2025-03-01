#!/bin/bash


if [ ! -d build ]; then mkdir build; fi
pushd build > /dev/null


if [[ $(uname) == "Darwin" ]]
then
    clang ../src/sdl2_main.cpp -o sdl2_main -F /Library/Frameworks -framework SDL2 -framework OpenGL
else
    gcc ../src/sdl2_main.cpp -o sdl2_main `sdl2-config --cflags --libs`
fi


popd > /dev/null
