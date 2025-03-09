#!/bin/bash


SDL_SRC="-I /Library/Frameworks/SDL2.framework/Headers"
SDL_LIB="-F /Library/Frameworks -framework SDL2"

OPENGL_LIB="-framework OpenGL"

GLAD_SRC="-I ../thirdparty/glad/include ../thirdparty/glad/src/glad.c"

GLM_SRC="-I glm"


# Generate debug info for Xcode debugging
# -g

# Emacs' compilation mode links work better as absolute paths
# -fdiagnostics-absolute-paths


if [ ! -d "build" ]; then mkdir build; fi

pushd build > /dev/null || exit

clang++ ../src/sdl_main.cpp -o sdl_main "$SDL_SRC" "$GLAD_SRC" "$SDL_LIB" "$OPENGL_LIB" -g -fdiagnostics-absolute-paths

popd > /dev/null || exit
