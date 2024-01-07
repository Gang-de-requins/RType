#!/bin/bash

PROJECT_CLIENT_DIR=client
PROJECT_CLIENT_NAME=r-type_client

PROJECT_SERVER_DIR=server
PROJECT_SERVER_NAME=r-type_server

cmake -S . -B build -D CMAKE_BUILD_TYPE=Release

cmake --build build

cp build/$PROJECT_CLIENT_DIR/$PROJECT_CLIENT_NAME .
cp build/$PROJECT_SERVER_DIR/$PROJECT_SERVER_NAME .
