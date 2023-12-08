# VanillaCakeADT

A portable library to speed up C software projects. It is and will always be compatible with in Windows, GNU/Linux and macOS environments.

VanillaCakeADT stands for Vanilla C and CMake with C Abstract Data Types.

## Setup

### General Setup Procedures
- Install Git using instructions https://git-scm.com/book/en/v2/Getting-Started-Installing-Git

### Specific Setup Procedures by Operating System

#### Linux
- Make sure you have APT since it has been tested and works for Ubuntu
- Run:
```
sudo apt -y install cmake
```
- Open a shell and run:
```
chmod +x setup.sh
./setup.sh
```

#### Windows
- Download and install CMake at https://cmake.org/download
- Install MS Visual Studio 2022 so you can have MSBuild. Follow instructions from https://learn.microsoft.com/en-us/cpp/build/msbuild-visual-cpp?view=msvc-170
    - If your MS Visual Studio version is not 2022, the paths within setup.sh MUST be changed to point to your MSBuild executable.
- Open a shell and run:
```
bash setup.sh
```


#### MacOS
- Install Homebrew from https://brew.sh
    - Brew is a requirement for our setup.sh script to be able to automatically install cmake.
- Open a shell and run:
```
sh setup.sh
```

### Validating Installation

If your terminal shows something like a Google Test execution, your setup is complete.