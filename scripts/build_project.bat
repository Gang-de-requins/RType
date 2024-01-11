@echo off

set PROJECT_CLIENT_DIR=client
set PROJECT_SERVER_DIR=server
set RTYPE_CLIENT=r-type_client
set RTYPE_SERVER=r-type_server

set DEBUG=false

:parse_args
if "%~1" == "--debug" (
    set DEBUG=true
    shift
    goto :parse_args
) else if "%~1" == "--help" (
    echo "Usage: ./scripts/build_project.bat [--debug]"
    exit /b 0
) else if not "%~1" == "" (
    echo "Invalid argument: %~1"
    exit /b 1
)

if "%DEBUG%" == "true" (
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug
) else (
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
)

cmake --build build

copy /y build\%PROJECT_CLIENT_DIR%\Debug\%RTYPE_CLIENT%.exe .
copy /y build\%PROJECT_CLIENT_DIR%\Debug\raylib.dll .

copy /y build\%PROJECT_SERVER_DIR%\Debug\%RTYPE_SERVER%.exe .
copy /y build\%PROJECT_SERVER_DIR%\Debug\raylib.dll .
