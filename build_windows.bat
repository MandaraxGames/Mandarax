@echo off

rem Set SDL2 and library directory paths
set SDL_DIR=C:\Program Files\SDL2\SDL2-2.30.7\include
set SDL_TTF_DIR=C:\Program Files\SDL2_ttf-2.22.0\include
set SDL_IMAGE_DIR=C:\Program Files\SDL2_image-2.8.2\include
set SDL_LIB_DIR=C:\Program Files\SDL2\SDL2-2.30.7\VisualC\x64\Release
set SDL_TTF_LIB_DIR=C:\Program Files\SDL2_ttf-2.22.0\lib\x64
set SDL_IMAGE_LIB_DIR=C:\Program Files\SDL2_image-2.8.2\lib\x64

rem Define common compiler flags
set CommonCompilerFlags=/GS- /I"%SDL_DIR%" /I"%SDL_TTF_DIR%" /I"%SDL_IMAGE_DIR%"

rem Define mode-specific compiler flags
set DebugCompilerFlags=/Od /Zi /MTd
set ReleaseCompilerFlags=/O2 /MT /WX

rem Define common linker flags (excluding SDL2main.lib)
set CommonLinkerFlags=/LIBPATH:"%SDL_LIB_DIR%" /LIBPATH:"%SDL_TTF_LIB_DIR%" /LIBPATH:"%SDL_IMAGE_LIB_DIR%" SDL2.lib SDL2_ttf.lib SDL2_image.lib kernel32.lib /NODEFAULTLIB /ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS

rem Set output directory and file name
if not exist bin mkdir bin
set OutputDir=bin
for %%I in ("%~dp0.") do set DIR_NAME=%%~nI
set OutputFile=%OutputDir%\%DIR_NAME%.exe

rem Create assets directory in bin if it doesn't exist
if not exist "%OutputDir%\assets" mkdir "%OutputDir%\assets"
if not exist "%OutputDir%\assets\fonts" mkdir "%OutputDir%\assets\fonts"

rem Copy all assets
echo Copying assets...
xcopy /y /i /e "assets\*.*" "%OutputDir%\assets\"
xcopy /y /i "src\fonts\*.*" "%OutputDir%\assets\fonts\"

rem Determine build mode (release or debug)
if "%1"=="" (
    echo No build mode specified. Defaulting to debug mode.
    set CompilerMode=debug
    set CompilerFlags=%CommonCompilerFlags% %DebugCompilerFlags%
) else if "%1"=="release" (
    echo Release mode selected.
    set CompilerMode=release
    set CompilerFlags=%CommonCompilerFlags% %ReleaseCompilerFlags%
) else (
    echo Invalid build mode. Use "release" or "debug".
    exit /b 1
)

rem Clean the output directory executables and objects but preserve assets
echo Cleaning binaries from the bin folder...
del /q "%OutputDir%\*.exe" "%OutputDir%\*.obj"

rem Compile all .c files in the src directory and output the executable in the bin directory
echo Compiling project in %CompilerMode% mode...
cl %CompilerFlags% "src\*.c" /Fe"%OutputFile%" /Fo"%OutputDir%\\" /link %CommonLinkerFlags%

rem Move the .pdb file to the bin directory if it exists
if exist vc*.pdb (
    move vc*.pdb "%OutputDir%"
)

rem Copy SDL2.dll, SDL2_ttf.dll, and SDL2_image.dll and its dependencies
echo Copying SDL2.dll, SDL2_ttf.dll, and SDL2_image.dll...
copy "%SDL_LIB_DIR%\SDL2.dll" "%OutputDir%\"
copy "%SDL_TTF_LIB_DIR%\SDL2_ttf.dll" "%OutputDir%\"
copy "%SDL_IMAGE_LIB_DIR%\SDL2_image.dll" "%OutputDir%\"

rem Check if compilation succeeded
if %errorlevel%==0 (
    echo Compilation succeeded. Running the program...
    rem Use pushd/popd to properly handle directory changes
    pushd "%OutputDir%"
    call "%DIR_NAME%.exe"
    popd
) else (
    echo Compilation failed.
)