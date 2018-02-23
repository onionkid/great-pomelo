cmake_minimum_required(VERSION 3.10)

# CMake instructions to make the static lib
ADD_LIBRARY(foo STATIC libfoo/foo.c )

# Include dir
include_directories(libfoo)

SET(APP_EXE greatPomelo)

# Configure executable
ADD_EXECUTABLE(${APP_EXE}  main/main.c libfoo/foo.h)

# Link the libraries
TARGET_LINK_LIBRARIES(${APP_EXE} foo)

