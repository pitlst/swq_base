#!/bin/bash
cd build
cmake ..
cmake --build . --target all -- -j $(nproc)
ctest -C DEBUG -V