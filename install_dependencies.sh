#!/bin/bash

echo "Installing development dependencies for DFD-HEAT..."

# Update package list
sudo apt update

# Install CMake and build tools
echo "Installing CMake and build essentials..."
sudo apt install -y cmake build-essential git

# Install Qt6 development packages
echo "Installing Qt6 with Qt3D..."
sudo apt install -y \
    qt6-base-dev \
    qt6-3d-dev \
    qt6-base-private-dev \
    libqt6sql6-sqlite \
    libqt6network6 \
    libqt6opengl6-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev

# Install Eigen for linear algebra
echo "Installing Eigen3..."
sudo apt install -y libeigen3-dev

# Install SQLite for material database
echo "Installing SQLite..."
sudo apt install -y sqlite3 libsqlite3-dev

# Check if GMSH is available (optional for now)
echo "Checking for GMSH..."
if ! command -v gmsh &> /dev/null; then
    echo "GMSH not found. You can install it later with: sudo apt install gmsh"
else
    echo "GMSH found!"
fi

echo ""
echo "Installation complete!"
echo ""
echo "Installed versions:"
cmake --version 2>/dev/null | head -1 || echo "CMake not found"
qmake6 --version 2>/dev/null | grep "Qt version" || echo "Qt6 not found"
g++ --version | head -1

echo ""
echo "Now you can build the project with:"
echo "  ./build.sh"