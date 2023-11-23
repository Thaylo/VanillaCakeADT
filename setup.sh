#!/bin/bash
sudo apt update
sudo apt-get -y install cmake
cd third_party
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
cd ..
cd ..
cd ..
mkdir build
cd build
cmake ..
make
./tests/unit_tests