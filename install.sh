#!/bin/bash

YSTRING_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

if [ ! -d build/release.Ystring ]
then
    mkdir -p build/release.Ystring
fi

cd build/release.Ystring
cmake -DCMAKE_BUILD_TYPE=Release $YSTRING_DIR
make install
cd ..

if [ ! -d build/debug.Ystring ]
then
    mkdir -p build/debug.Ystring
fi

cd build/debug.Ystring
cmake -DCMAKE_BUILD_TYPE=Debug $YSTRING_DIR
make install
cd ..
