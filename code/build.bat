@echo off

set INCLUDE_DIR="..\code\external"
set LINKER_DIR="..\code\lib"

mkdir ..\build
pushd ..\build
cl /Zi /FC /I%INCLUDE_DIR% ..\code\game.cpp /link %LINKER_DIR%\raylib.lib
popd
