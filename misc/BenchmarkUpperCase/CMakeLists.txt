##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-08-31.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.13)
project(Ystring_Benchmark)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif(APPLE)

find_package(Ystring REQUIRED)
include_directories(${YSTRING_INCLUDE_DIR})

add_executable(BenchmarkUpperCase
    BenchmarkUpperCase.cpp
    Timer.hpp
    )

target_link_libraries(BenchmarkUpperCase ${YSTRING_LIBRARY})

add_executable(MakeRandomText
    MakeRandomText.cpp
    Random.cpp
    Random.hpp
    )

target_link_libraries(MakeRandomText
    Ystring::Ystring
    )
