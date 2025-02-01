#!/bin/bash

# platform=$(uname -s)

# TODO:
#       Remove IMGUI_EXAMPLES:
IMGUI_EXAMPLES="-I imgui/examples -DIMGUI_IMPL_OPENGL_LOADER_GLAD"
IMGUI_SRC="-I imgui $IMGUI_EXAMPLES"

GLAD_SRC="-I glad/include -I glad/src"
OPENGL_LIB="-framework OpenGl"

GLM_SRC="-I glm"

SDL_SRC=$(sdl2-config --cflags)
SDL_LIB=$(sdl2-config --libs)

clang++ sdl_main.cpp -o sdl_main $SDL_SRC $IMGUI_SRC $GLAD_SRC $GLM_SRC $SDL_LIB $OPENGL_LIB
