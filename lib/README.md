# External Dependencies

This directory contains external dependencies that are automatically cloned and built by CMake.

## Structure

The dependencies are organized as follows:

```
lib/
├── webkit/              # WebKit source code (cloned automatically)
├── webkit-install/      # WebKit installation (headers, libraries)
├── libwpe/              # libwpe source code (cloned automatically)
├── libwpe-install/      # libwpe installation (headers, libraries)
├── wpebackend-fdo/      # wpebackend-fdo source code (cloned automatically)
├── wpebackend-install/  # wpebackend-fdo installation (headers, libraries)
└── .gitignore          # Excludes all dependency files from version control
```

## How It Works

1. **Automatic Cloning**: CMake's ExternalProject automatically clones repositories here
2. **Automatic Building**: Dependencies are built and installed in their respective `-install` directories
3. **Version Control**: The actual dependency files are excluded from git via `.gitignore`
4. **Clean Structure**: Each dependency has its own subdirectory for organization

## Adding New Dependencies

To add a new dependency:

1. Add a new `ExternalProject_Add` section in the main `CMakeLists.txt`
2. Set the `SOURCE_DIR` to `${LIB_DIR}/your-dependency-name`
3. Set the `CMAKE_INSTALL_PREFIX` to `${LIB_DIR}/your-dependency-name-install`
4. Update the `.gitignore` to exclude the new dependency directories

## Benefits

- **Clean Project Structure**: Dependencies are organized in one place
- **Version Control Friendly**: Only your code is tracked, not external dependencies
- **Easy Cleanup**: You can easily remove all dependencies by deleting the `lib/` directory
- **Reproducible Builds**: Dependencies are always cloned fresh, ensuring consistency

