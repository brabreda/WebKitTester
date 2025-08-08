cmake_minimum_required(VERSION 3.20)
project(WebKitApp VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include ExternalProject for dependency management
include(ExternalProject)
include(FetchContent)

# Set up dependency versions
set(WEBKIT_VERSION "main" CACHE STRING "WebKit version to use")
set(LIBWPE_VERSION "main" CACHE STRING "libwpe version to use")
set(WPEBACKEND_VERSION "main" CACHE STRING "wpebackend-fdo version to use")

# Set up lib directory for external dependencies
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXTERNAL_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/external)

# Configure ExternalProject for WebKit
ExternalProject_Add(webkit
    GIT_REPOSITORY https://github.com/WebKit/WebKit.git
    GIT_TAG ${WEBKIT_VERSION}
    SOURCE_DIR ${LIB_DIR}/webkit
    BINARY_DIR ${EXTERNAL_BUILD_DIR}/webkit-build
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${LIB_DIR}/webkit-install
        -DCMAKE_BUILD_TYPE=Release
        -DENABLE_WEBKIT=ON
        -DENABLE_WEBKIT2=ON
        -DENABLE_WPE=ON
        -DENABLE_TOOLS=OFF
        -DENABLE_API_TESTS=OFF
    BUILD_BYPRODUCTS ${LIB_DIR}/webkit-install/lib/libWebKit.so
)

# Configure ExternalProject for libwpe
ExternalProject_Add(libwpe
    GIT_REPOSITORY https://github.com/WebPlatformForEmbedded/libwpe.git
    GIT_TAG ${LIBWPE_VERSION}
    SOURCE_DIR ${LIB_DIR}/libwpe
    BINARY_DIR ${EXTERNAL_BUILD_DIR}/libwpe-build
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${LIB_DIR}/libwpe-install
        -DCMAKE_BUILD_TYPE=Release
    BUILD_BYPRODUCTS ${LIB_DIR}/libwpe-install/lib/libwpe.so
)

# Configure ExternalProject for wpebackend-fdo
ExternalProject_Add(wpebackend-fdo
    GIT_REPOSITORY https://github.com/Igalia/wpebackend-fdo.git
    GIT_TAG ${WPEBACKEND_VERSION}
    SOURCE_DIR ${LIB_DIR}/wpebackend-fdo
    BINARY_DIR ${EXTERNAL_BUILD_DIR}/wpebackend-build
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${LIB_DIR}/wpebackend-install
        -DCMAKE_BUILD_TYPE=Release
    BUILD_BYPRODUCTS ${LIB_DIR}/wpebackend-install/lib/libWPEBackend-fdo.so
)

# Add your source files
set(SOURCES
    src/main.cpp
    src/webview.cpp
)

set(HEADERS
    src/webview.h
)

# Create your executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set up include directories for dependencies
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${LIB_DIR}/webkit-install/include
    ${LIB_DIR}/libwpe-install/include
    ${LIB_DIR}/wpebackend-install/include
)

# Link against the built dependencies
target_link_libraries(${PROJECT_NAME} 
    ${LIB_DIR}/webkit-install/lib/libWebKit.so
    ${LIB_DIR}/libwpe-install/lib/libwpe.so
    ${LIB_DIR}/wpebackend-install/lib/libWPEBackend-fdo.so
)

# Add dependencies to ensure they're built first
add_dependencies(${PROJECT_NAME} webkit libwpe wpebackend-fdo)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)

# Installation
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
