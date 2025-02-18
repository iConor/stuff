@echo off


if not exist ..\build mkdir ..\build
pushd ..\build


cl ..\src\sdl_main.cpp /nologo /I "..\..\..\lib\sdl2\include" /link /LIBPATH:"..\..\..\lib\sdl2\lib\x64" SDL2.lib SDL2main.lib opengl32.lib shell32.lib /SUBSYSTEM:console


popd
