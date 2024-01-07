@echo off

set BUILD_DIR=build
set RTYPE_CLIENT=r-type_client
set RTYPE_SERVER=r-type_server

echo Cleaning up...
echo Deleting build directory...
rd /s /q build
echo Deleting binaries...
del /q %RTYPE_CLIENT%.*
del /q %RTYPE_SERVER%.*
del /q raylib.dll

echo Cleanup complete.
