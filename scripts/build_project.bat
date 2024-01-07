@echo off

set PROJECT_CLIENT_DIR=client
set PROJECT_SERVER_DIR=server

cmake -S . -B build -D CMAKE_BUILD_TYPE=Release

cmake --build build

xcopy /s /y build\%PROJECT_CLIENT_DIR%\Debug\* .\bin\client\
xcopy /s /y build\%PROJECT_SERVER_DIR%\Debug\* .\bin\server\
