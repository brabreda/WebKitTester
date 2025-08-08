# WebKit C++ Project

A C++ project that uses WebKit with automatic dependency management through CMake.

## Features

- ✅ **One-script setup**: Everything is handled by CMake and the build script
- ✅ **Automatic dependency cloning**: WebKit, libwpe, and wpebackend-fdo are automatically cloned and built
- ✅ **Version control**: Easy to specify different versions of dependencies
- ✅ **Cross-platform**: Works on Linux, macOS, and other Unix-like systems

## Quick Start

### Prerequisites

Make sure you have the following installed:
- CMake 3.20 or higher
- Git
- C++ compiler (GCC, Clang, etc.)
- Build tools (make, ninja, etc.)

### Build Everything

```bash
# Make the build script executable (if not already)
chmod +x build.sh

# Run the build script
./build.sh
```

This will:
1. Clone WebKit, libwpe, and wpebackend-fdo repositories
2. Build all dependencies
3. Build your application
4. Create the final executable in `build/WebKitApp`

## Manual Build

If you prefer to build manually:

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

## Customizing Dependencies

You can specify different versions of dependencies:

```bash
cmake .. \
    -DWEBKIT_VERSION=webkitgtk-2.40.0 \
    -DLIBWPE_VERSION=v1.14.0 \
    -DWPEBACKEND_VERSION=v1.14.0
```

## Project Structure

```
.
├── CMakeLists.txt          # Main CMake configuration
├── build.sh               # Build script
├── src/
│   ├── main.cpp          # Main application
│   ├── webview.cpp       # WebView implementation
│   └── webview.h         # WebView header
├── lib/                   # External dependencies (auto-cloned)
│   ├── .gitignore        # Excludes dependencies from version control
│   └── README.md         # Dependency documentation
└── README.md             # This file
```

## How It Works

The `CMakeLists.txt` uses CMake's `ExternalProject` module to:

1. **Clone repositories**: Automatically downloads WebKit, libwpe, and wpebackend-fdo into the `lib/` directory
2. **Build dependencies**: Compiles each dependency with the correct configuration
3. **Install locally**: Installs headers and libraries in `lib/*-install/` directories
4. **Link everything**: Links your application against the built libraries
5. **Handle dependencies**: Ensures dependencies are built before your application

## Customizing the Build

### Adding More Dependencies

To add more dependencies, add another `ExternalProject_Add` section:

```cmake
ExternalProject_Add(your-dependency
    GIT_REPOSITORY https://github.com/user/repo.git
    GIT_TAG main
    SOURCE_DIR ${LIB_DIR}/your-dependency
    BINARY_DIR ${EXTERNAL_BUILD_DIR}/your-dependency-build
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${LIB_DIR}/your-dependency-install
        -DCMAKE_BUILD_TYPE=Release
)
```

Then update `lib/.gitignore` to exclude the new dependency directories.

### Modifying Build Options

You can customize build options for each dependency by modifying the `CMAKE_ARGS` in the `ExternalProject_Add` calls.

## Troubleshooting

### Common Issues

1. **Build fails with "git not found"**: Install Git
2. **CMake version too old**: Update to CMake 3.20 or higher
3. **Missing system dependencies**: Install development packages for EGL, OpenGL, etc.

### Debug Build

For debugging, use:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

## Next Steps

This is a basic setup. To make it a full WebKit application, you'll need to:

1. Integrate with WebKit's C API
2. Add proper event handling
3. Implement window management
4. Add JavaScript bridge functionality

The current implementation provides the foundation with WPE integration.
