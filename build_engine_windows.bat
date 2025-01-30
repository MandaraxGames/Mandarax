@echo off

rem SDL2 paths
set SDL_DIR=C:\Program Files\SDL2\SDL2-2.30.7\include
set SDL_IMAGE_DIR=C:\Program Files\SDL2_image-2.8.2\include
set SDL_LIB_DIR=C:\Program Files\SDL2\SDL2-2.30.7\VisualC\x64\Release
set SDL_IMAGE_LIB_DIR=C:\Program Files\SDL2_image-2.8.2\lib\x64

rem Create lib directory if it doesn't exist
if exist lib del /q lib
if not exist lib mkdir lib

rem Compile engine source files
echo Building Mandarax engine...
cl /c /GS- /I"%SDL_DIR%" /I"%SDL_IMAGE_DIR%" /I"src" /I"include" src/mx_*.c /Folib/

rem Create static library
lib /OUT:lib/mandarax.lib lib/*.obj

echo Engine build complete.