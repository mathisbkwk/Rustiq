#!/bin/bash
echo "Running development script..."
concurrently \
    "cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build && cmake --build build" \
