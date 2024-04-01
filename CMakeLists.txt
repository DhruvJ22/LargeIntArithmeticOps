# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.00)

# Project name
project(LargeIntAritmeticOps)  

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Collect source files
file(GLOB SOURCES "src/*.cpp")

# Add a library target named 'arithmetic_operations' from the source files
add_library(arithmetic_operations STATIC ${SOURCES})

# Include the 'include' directory for the 'arithmetic_operations' target
target_include_directories(arithmetic_operations PUBLIC include)

# Add an executable target for the main program
add_executable(main main.cpp)
# Link 'arithmetic_operations' to 'main'
target_link_libraries(main PRIVATE arithmetic_operations)

# Add an executable target for the example
add_executable(example1 example/computeAtomsinCalcium.cpp)
# Link 'arithmetic_operations' to 'example'
target_link_libraries(example1 PRIVATE arithmetic_operations)

# Add an executable target for the example
add_executable(example2 example/computeExponentofLargeInt.cpp)
# Link 'arithmetic_operations' to 'example'
target_link_libraries(example2 PRIVATE arithmetic_operations)

########################################################################################3
# For Unit and Integration Testing
add_subdirectory(extern/googletest)

# Include FFTW3 download and build - for testing
include(ExternalProject)
# Define FFTW3 download URL
set(FFTW3_URL "http://www.fftw.org/fftw-3.3.10.tar.gz")
# ExternalProject_Add to download and build FFTW3
ExternalProject_Add(
                    fftw3_external
                    URL ${FFTW3_URL}
                    PREFIX ${CMAKE_BINARY_DIR}/fftw3  # Specify the directory where FFTW3 will be downloaded and built
                    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=${CMAKE_BINARY_DIR}/fftw3-install
                    BUILD_COMMAND make
                    INSTALL_COMMAND make install
                    LOG_DOWNLOAD ON)
# Define variables for FFTW3 include directory and library
set(FFTW3_INCLUDE_DIR ${CMAKE_BINARY_DIR}/fftw3-install/include)
set(FFTW3_LIBRARY ${CMAKE_BINARY_DIR}/fftw3-install/lib/libfftw3.a)
# Add include directory for FFTW3
include_directories(${FFTW3_INCLUDE_DIR})

# Collect test files
file(GLOB TEST_FILES "test/*_test.cpp")

add_executable(tests ${TEST_FILES} ${SOURCES})
target_link_libraries(tests PRIVATE gtest gtest_main)
target_link_libraries(tests PRIVATE ${FFTW3_LIBRARY}) # Link against the FFTW3 library
target_include_directories(tests PRIVATE include)