##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 25.07.15
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.2)

set(PARENT_PROJECT Ystring)
project(${PARENT_PROJECT}Examples)

add_executable(PrintPath PrintPath.cpp)
target_link_libraries(PrintPath ${PARENT_PROJECT})

add_executable(Title Title.cpp)
target_link_libraries(Title ${PARENT_PROJECT})

add_executable(Upper Upper.cpp)
target_link_libraries(Upper ${PARENT_PROJECT})
