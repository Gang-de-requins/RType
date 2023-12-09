#!/bin/bash

PROJECT_CLIENT_NAME=r-type_client
PROJECT_SERVER_NAME=r-type_server
VCPKG_DIR=vcpkg
VCPKG_INSTALLED_DIR=vcpkg_installed

rm -rf build
rm $PROJECT_CLIENT_NAME
rm $PROJECT_SERVER_NAME
rm -rf $VCPKG_DIR
rm -rf $VCPKG_INSTALLED_DIR
