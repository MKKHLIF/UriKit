#!/bin/bash

# Check if the script is running on a Unix-like system (Linux or macOS)
if [[ "$OSTYPE" == "darwin"* ]] || [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Running on a Unix-like system (Linux or macOS)."
else
    echo "This script is only meant to run on Linux or macOS."
    exit 1
fi

# Function to test if a command exists
function test_command {
    command -v "$1" &> /dev/null
    return $?
}

# Check if git is installed
if ! test_command "git"; then
    echo "Git is not installed. Please install Git and try again."
    exit 1
fi

# Check if cmake is installed
if ! test_command "cmake"; then
    echo "CMake is not installed. Please install CMake and try again."
    exit 1
fi

# Check if vcpkg is already cloned, else clone it
VCPKG_DIR="$HOME/vcpkg"
if [ ! -d "$VCPKG_DIR" ]; then
    echo "Cloning vcpkg repository..."
    git clone https://github.com/microsoft/vcpkg.git "$VCPKG_DIR"
else
    echo "vcpkg directory already exists."
fi

# Run the bootstrap script for vcpkg
echo "Running bootstrap-vcpkg.sh..."
cd "$VCPKG_DIR" || exit
./bootstrap-vcpkg.sh

# Integrate vcpkg with the system
echo "Integrating vcpkg..."
./vcpkg integrate install

# Install dependencies using vcpkg
echo "Installing dependencies with vcpkg..."
./vcpkg install

# Set up build directory
BUILD_DIR="$GITHUB_WORKSPACE/build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

# Configure CMake with vcpkg toolchain
echo "Configuring CMake..."
cmake -B"$BUILD_DIR" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_TOOLCHAIN_FILE="$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake" \
      -S"$GITHUB_WORKSPACE"

# Build the project
echo "Building the project..."
cmake --build "$BUILD_DIR" --config Release

# Run tests with ctest
echo "Running tests with ctest..."
ctest --build-config Release --output-on-failure

