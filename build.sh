#!/bin/bash

# WebKit C++ Project Build Script
# This script sets up and builds the entire project with all dependencies

set -e  # Exit on any error

echo "🚀 Setting up WebKit C++ Project..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "📦 Configuring project with CMake..."
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DWEBKIT_VERSION=main \
    -DLIBWPE_VERSION=main \
    -DWPEBACKEND_VERSION=main

# Build the project (this will also build all dependencies)
echo "🔨 Building project and dependencies..."
make -j$(nproc)

echo "✅ Build completed successfully!"
echo "📁 Executable location: build/WebKitApp"
