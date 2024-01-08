@echo off

set PROJECT_CLIENT_DIR=client
set PROJECT_SERVER_DIR=server
set RTYPE_CLIENT=r-type_client
set RTYPE_SERVER=r-type_server

cmake -S . -B build -D CMAKE_BUILD_TYPE=Release

cmake --build build

copy /y build\%PROJECT_CLIENT_DIR%\Debug\%RTYPE_CLIENT%.exe .
copy /y build\%PROJECT_CLIENT_DIR%\Debug\raylib.dll .

copy /y build\%PROJECT_SERVER_DIR%\Debug\%RTYPE_SERVER%.exe .
copy /y build\%PROJECT_SERVER_DIR%\Debug\raylib.dll .
