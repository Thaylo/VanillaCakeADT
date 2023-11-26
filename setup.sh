#!/bin/bash
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
sudo apt update
sudo apt-get -y install cmake
elif [[ "$OSTYPE" == "darwin"* ]]; then
brew install cmake
fi
cd third_party
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake -DCMAKE_CXX_STANDARD=14 ..
make
cd ..
cd ..
cd ..
mkdir build
cd build
cmake -DCMAKE_CXX_STANDARD=14 ..
make
./tests/unit_tests