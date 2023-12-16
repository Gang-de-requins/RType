@echo off

set PROJECT_CLIENT_DIR=client
set PROJECT_CLIENT_NAME=r-type_client

set PROJECT_SERVER_DIR=server
set PROJECT_SERVER_NAME=r-type_server

if not exist "build" mkdir build

cmake --preset=windows

cmake --build build

copy build\%PROJECT_CLIENT_DIR%\%PROJECT_CLIENT_NAME% .
copy build\%PROJECT_SERVER_DIR%\%PROJECT_SERVER_NAME% .
