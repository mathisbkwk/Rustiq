#!/bin/bash
echo "Running development script..."
concurrently \
    "cd ai && cd build && cmake .. && cmake --build ." \
    "cd backend && go run main.go" \
    "cd frontend && bun run dev" \
