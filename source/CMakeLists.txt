
project(EizoApp)

cmake_minimum_required(VERSION 3.0)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")



# Set the source files to be included in the library
set(SOURCES
    functions.cpp
)

# Add the source directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Create the library target
add_library(my_library STATIC ${SOURCES})

# Specify any include directories for the library


