@echo off


if NOT EXIST build (
mkdir build
)
pushd build


REM TODO: /Od /Oi /Gm- /GR- /EHa- /FC /MTd /W4 /Wx /wd4100 /wd4189
set compiler_flags= /FC /Z7 /Fmwin32_main.map /nologo

REM TODO: /SUBSYSTEM:windows /incremental:no /opt:ref kernel32.lib
set linker_flags= user32.lib gdi32.lib opengl32.lib


cl ..\src\win32_main.cpp %compiler_flags% /link %linker_flags%


popd
