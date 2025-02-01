#!/bin/bash

clang -o build/sdl_main sdl_main.cpp -framework OpenGL -framework SDL2 -F ~/Library/Frameworks/ -I ~/Library/Frameworks/SDL2.framework/Headers
