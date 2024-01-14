#!/bin/bash

BUILD_DIR=build
RTYPE_CLIENT=r-type_client
RTYPE_SERVER=r-type_server

echo "Cleaning up..."
echo "Deleting build directory..."
rm -rf $BUILD_DIR
echo "Deleting executables..."
rm $RTYPE_CLIENT
rm $RTYPE_SERVER

echo "Cleanup complete."
