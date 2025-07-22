cmake_minimum_required(VERSION 3.31)
project(opengl_cmake_template)

# -----------------------------------------------------------------------------------------------------------------
# CMAKE SETUP
# -----------------------------------------------------------------------------------------------------------------

# Use C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure assets header file
configure_file(${CMAKE_SOURCE_DIR}/src/util/RootDir.h.in ${CMAKE_SOURCE_DIR}/src/util/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

# -----------------------------------------------------------------------------------------------------------------

# Find all C++ source and header files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Define the include directories
include_directories(
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/include"
)

# -----------------------------------------------------------------------------------------------------------------
# LIBRARIES
# -----------------------------------------------------------------------------------------------------------------

# Use CPM.cmake
include(cmake/CPM.cmake)

# Configure libraries
include(cmake/Libraries.cmake)

# -----------------------------------------------------------------------------------------------------------------
