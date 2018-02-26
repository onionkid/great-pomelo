cmake_minimum_required(VERSION 3.10)

#include
include(CTest)
include(CPack)

# CMake instructions to make the static lib
ADD_LIBRARY(foo STATIC libfoo/foo.c )
ADD_LIBRARY(hoot STATIC libhoot/hoot.c )

# Include dir
include_directories(libfoo)

# VAR
SET(APP_EXE greatPomelo)
SET(APP_EXE_TEST greatPomeloTest)

# Configure executable
ADD_EXECUTABLE(${APP_EXE}  main/main.c libfoo/foo.h libhoot/hoot.h)
ADD_EXECUTABLE(${APP_EXE_TEST}  test/mainTest.c libfoo/foo.h libhoot/hoot.h)

# Link the libraries
TARGET_LINK_LIBRARIES(${APP_EXE} foo hoot)
TARGET_LINK_LIBRARIES(${APP_EXE_TEST} foo hoot)

######## TEST
