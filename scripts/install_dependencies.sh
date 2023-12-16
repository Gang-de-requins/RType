#!/bin/bash

if [ -d "vcpkg" ]; then
    echo "vcpkg already installed"
    exit 0
fi

git clone https://github.com/microsoft/vcpkg.git

./vcpkg/bootstrap-vcpkg.sh
