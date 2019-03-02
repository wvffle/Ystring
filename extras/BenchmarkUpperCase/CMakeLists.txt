##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-08-31.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 2.8)
project(Ystring_Benchmark)

set(CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/../cmake/Modules"
    ${CMAKE_MODULE_PATH})

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
elseif(WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS -DYSTRING_EXPORTS)
endif(APPLE)

find_package(Ystring REQUIRED)
include_directories(${YSTRING_INCLUDE_DIR})

add_executable(.
    BenchmarkUpperCase.cpp
    Timer.hpp)
target_link_libraries(. ${YSTRING_LIBRARY})

add_executable(MakeRandomText
    MakeRandomText.cpp
    Random.cpp
    Random.hpp)
target_link_libraries(MakeRandomText ${YSTRING_LIBRARY})
