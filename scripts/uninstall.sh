#!/bin/bash

PROJECT_CLIENT_NAME=r-type_client
PROJECT_SERVER_NAME=r-type_server
VCPKG_DIR=vcpkg
VCPKG_INSTALLED_DIR=vcpkg_installed


# remove vcpkg if it is installed
if [ -d $VCPKG_DIR ]; then
    echo "uninstalling vcpkg..."
    rm -rf $VCPKG_DIR
    rm -rf $VCPKG_INSTALLED_DIR

    # remove vcpkg from PATH
    # sed -i '/export VCPKG_ROOT=$PWD\/vcpkg/d' ~/.bashrc
    # sed -i '/export PATH=$VCPKG_ROOT:$PATH/d' ~/.bashrc

    echo "vcpkg uninstalled"
fi

rm -rf build
rm $PROJECT_CLIENT_NAME
rm $PROJECT_SERVER_NAME
