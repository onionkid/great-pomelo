cmake_minimum_required(VERSION 3.10)

#include
include(CTest)
include(CPack)

# CMake instructions to make the static lib
ADD_LIBRARY(foo STATIC libfoo/foo.c )
ADD_LIBRARY(hoot STATIC libhoot/hoot.c )
ADD_LIBRARY(cunit-test STATIC test/pomeloUT.c )

# Include dir
include_directories(libfoo)

# VAR
SET(APP_EXE greatPomelo)

# Configure executable
ADD_EXECUTABLE(${APP_EXE}  main/main.c libfoo/foo.h libhoot/hoot.h)

# Link the libraries
TARGET_LINK_LIBRARIES(${APP_EXE} foo hoot)

################################################################
# UNIT TEST
################################################################
#CUNIT
SET(CUNIT_HOME_INCLUDE /usr/local/include/CUnit)
SET(CUNIT_HOME_LIB /usr/local/lib)


# Include dir
include_directories(libfoo)
include_directories(${CUNIT_HOME_INCLUDE})

#Link dir
link_directories(${CUNIT_HOME_LIB})

# VAR
SET(APP_EXE_TEST greatPomeloTest)

# Configure executable
ADD_EXECUTABLE(${APP_EXE_TEST} test/mainTest.c libfoo/foo.h libhoot/hoot.h test/pomeloUT.h ${CUNIT_HOME_INCLUDE}/Automated.h )

# Link the libraries
TARGET_LINK_LIBRARIES(${APP_EXE_TEST} hoot cunit cunit-test foo )
