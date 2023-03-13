#!/bin/bash
cd build
rm -rf ./*
cmake ..
cmake --build . --target all -- -j $(nproc)
ctest -C DEBUG -V