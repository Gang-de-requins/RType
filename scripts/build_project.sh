#!/bin/bash

PROJECT_CLIENT_DIR=client
PROJECT_CLIENT_NAME=r-type_client

PROJECT_SERVER_DIR=server
PROJECT_SERVER_NAME=r-type_server

if [ ! -d "build" ]; then
  mkdir build
fi

cmake --preset=linux

cmake --build build

cp build/$PROJECT_CLIENT_DIR/$PROJECT_CLIENT_NAME .
cp build/$PROJECT_SERVER_DIR/$PROJECT_SERVER_NAME .
