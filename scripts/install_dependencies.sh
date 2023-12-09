#!/bin/bash

# curl -fsSL -o vcpkg.zip https://github.com/microsoft/vcpkg/archive/refs/tags/2023.11.20.zip
# unzip vcpkg.zip

# ./vcpkg-2023.11.20/bootstrap-vcpkg.sh

# ./vcpkg-2023.11.20/vcpkg install

git clone https://github.com/microsoft/vcpkg.git

./vcpkg/bootstrap-vcpkg.sh

./vcpkg/vcpkg install
