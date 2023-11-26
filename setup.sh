#!/bin/bash

# Function to check if a command is available
command_exists() {
  command -v "$1" >/dev/null 2>&1
}

# Check the operating system and install required tools
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  sudo apt update
  sudo apt-get -y install cmake
elif [[ "$OSTYPE" == "darwin"* ]]; then
  # Check if Homebrew is installed
  if command_exists brew; then
    brew install cmake
  else
    echo "Error: Homebrew is required but not installed. Please install Homebrew."
    exit 1
  fi
else
  echo "Error: Unsupported operating system."
  exit 1
fi

cd third_party
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake -DCMAKE_CXX_STANDARD=14 ..
make
cd ../../..
mkdir build
cd build
cmake -DCMAKE_CXX_STANDARD=14 ..
make
./tests/unit_tests