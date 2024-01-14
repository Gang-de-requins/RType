@echo off

set BUILD_DIR=build
set PONG=pong

echo Cleaning up...
echo Deleting build directory...
rd /s /q build
echo Deleting binaries...
del /q %PONG%.*
del /q raylib.dll

echo Cleanup complete.
