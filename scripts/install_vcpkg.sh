#!/bin/bash

# check if VCPKG_ROOT is set, if so, display vcpkg already installed
if [ -n "$VCPKG_ROOT" ]; then
    echo "vcpkg already installed"
    
    # return if script is run by source command (return to parent shell) otherwise exit
    if [ "$0" = "$BASH_SOURCE" ]; then
        exit 1
    else
        return 1
    fi
fi

echo "Installing vcpkg..."

git clone https://github.com/microsoft/vcpkg.git

./vcpkg/bootstrap-vcpkg.sh

# echo "export VCPKG_ROOT=$PWD/vcpkg" >> ~/.bashrc
export VCPKG_ROOT=$PWD/vcpkg

# echo "export PATH=$VCPKG_ROOT:$PATH" >> ~/.bashrc
export PATH=$VCPKG_ROOT:$PATH

echo "vcpkg installed"
