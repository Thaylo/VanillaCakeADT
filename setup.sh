#!/bin/bash

# Function to check if a command is available
command_exists() {
  command -v "$1" >/dev/null 2>&1
}

# Check the operating system and install required tools
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  sudo apt update
  sudo apt -y install cmake
  elif [[ "$OSTYPE" == "darwin"* ]]; then
    # Check if Homebrew is installed
    if command_exists brew; then
      brew install cmake
    else
      echo "Error: Homebrew is required but not installed. Please install Homebrew."
      exit 1
    fi
  elif [[ "$OSTYPE" == "msys"* || "$OSTYPE" == "cygwin" ]]; then
    # Assuming Git Bash on Windows
    if command_exists cmake; then
      echo "cmake has been detected."
    else
      echo "It seems like you are using Windows OS. Make sure you have cmake installed."
      exit 1
    fi
else
  echo "Error: Unsupported operating system."
  exit 1
fi


if [[ "$OSTYPE" == "msys"* || "$OSTYPE" == "cygwin" ]]; then
  cd third_party
  git clone https://github.com/google/googletest.git
  cd googletest
  mkdir build
  cd build
  cmake -DCMAKE_CXX_STANDARD=14 ..
  "/c/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe" "googletest-distribution.sln" -property:Configuration=Release
  cd ../../..
  mkdir build
  cd build
  cmake -DCMAKE_CXX_STANDARD=14 ..
  "/c/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe" "VanillaCake.sln" -property:Configuration=Release
  ./tests/Release/unit_tests.exe
else
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
  cd ..
  ./build/tests/unit_tests
  echo "Starting project demonstrator..."
  ./build/VanillaCake
fi
