#!/bin/bash

# Compile the C++ code
g++ src/*.cpp -Iinclude -o Game

# Run the executable (works on macOS, Linux, and Windows with a Unix-like shell)
./Game
