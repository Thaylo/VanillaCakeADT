#!/bin/bash
sudo apt update
sudo apt-get -y install cmake
mkdir build
cd build
cmake ..
make