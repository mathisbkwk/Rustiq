#!/bin/bash
echo "Running development script..."
concurrently \
    "cd ai && cargo run" \
    "cd backend && go run main.go" \
    "cd frontend && bun run dev" \
    