#!/bin/sh

. /etc/profile
module avail
module load gcc/12.1.0

mkdir build
cmake --version
cmake -S . -B project-release -DCMAKE_BUILD_TYPE=Release
cmake --build project-release
