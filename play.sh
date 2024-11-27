#!/bin/bash

# Compile the C++ code
g++ -std=c++14 src/*.cpp -Iinclude -o Game

# Run the executable (works on macOS, Linux, and Windows with a Unix-like shell)
./Game
