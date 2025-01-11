@echo off

if not exist build (mkdir build)
pushd build


cl /Zi /nologo ..\src\main.cpp /link userenv.lib advapi32.lib


popd
