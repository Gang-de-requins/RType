@echo off

set VCPKG_DIR=vcpkg
set BIN_DIR=bin
set BUILD_DIR=build

rd /s /q build
rd /s /q bin
rd /s /q %VCPKG_DIR%\

echo Cleanup complete.
