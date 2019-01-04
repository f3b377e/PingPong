cmake_minimum_required(VERSION 3.12)
project(CppToUnity)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

find_package (OpenCV REQUIRED)

set(CppToUnity_SRC
        CppToUnity.cpp
        CppToUnity.hpp)

add_library(CppToUnity SHARED ${CppToUnity_SRC})
set_property(TARGET CppToUnity PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries (CppToUnity ${OpenCV_LIBS})
target_link_libraries (CppToUnity rt)
