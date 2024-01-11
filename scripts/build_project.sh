#!/bin/bash

PROJECT_CLIENT_DIR=client
PROJECT_CLIENT_NAME=r-type_client

PROJECT_SERVER_DIR=server
PROJECT_SERVER_NAME=r-type_server

DEBUG=false

while [ $# -gt 0 ]; do
    case "$1" in
        --debug)
            DEBUG=true
            ;;
        --help)
            echo "Usage: $0 [--debug]"
            exit 0
            ;;
        *)
            echo "Unknown argument: $1"
            exit 1
            ;;
    esac
    shift
done
    

if [ "$DEBUG" = true ]; then
    echo "Building in debug mode"
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug
else
    echo "Building in release mode"
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
fi

cmake --build build

cp build/$PROJECT_CLIENT_DIR/$PROJECT_CLIENT_NAME .
cp build/$PROJECT_SERVER_DIR/$PROJECT_SERVER_NAME .
