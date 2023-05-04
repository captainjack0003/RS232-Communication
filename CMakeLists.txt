project(EizoApp)

cmake_minimum_required(VERSION 3.0)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


# Add the include directory to your project
include_directories(${CMAKE_SOURCE_DIR}/includes)


# Add the source directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/source)

add_subdirectory(source)
add_executable(Eizo_App main.cpp)
target_link_libraries(Eizo_App my_library)

