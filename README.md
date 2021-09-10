# Cetris

## About

This project aims to become a tetris clone made in C++ using GLFW.
This software is currently only tested on Arch Linux.

## Requirements

You need the GLFW library and GNU C/C++ Compiler (GCC) and their respective dependancies installed on your system.

### Arch based ditributions

Install the following packages for Arch based distributions :
```
glfw-x11
gcc
```

### Ubuntu based distributions

Install the following packages for Ubuntu based distributions :
```
gcc-10
libglfw3-dev
```

## Build & Run

!! Warning : the scripts have only been tested on Arch based ditributions! If it fails to build, you will have to figure out how to call for some libraries on your distribution.

Launch the script `build.sh` to build the application binary.

Launch the script `run.sh` to build and run the application. The binary will be deleted on exit with this script.

The script `clean.sh` is meant to clean (delete) the compilation files. All that should remain after running this script is the code and vscode settings.