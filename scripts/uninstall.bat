@echo off

set PROJECT_CLIENT_NAME=r-type_client
set PROJECT_SERVER_NAME=r-type_server
set VCPKG_DIR=vcpkg
set VCPKG_INSTALLED_DIR=vcpkg_installed 

rd /s /q build
del %PROJECT_CLIENT_NAME%
del %PROJECT_SERVER_NAME%
del %VCPKG_DIR%
del %VCPKG_INSTALLED_DIR%

echo Cleanup complete.
