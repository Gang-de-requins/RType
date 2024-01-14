@echo off

set PROJECT_PONG_DIR=pong
set PONG=pong

cmake -B build
cmake --build build/

copy /y build\%PROJECT_PONG_DIR%\Debug\%PONG%.exe .
copy /y build\%PROJECT_PONG_DIR%\Debug\raylib.dll .
