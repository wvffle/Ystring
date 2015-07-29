##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-05-31
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.2)

set(PARENT_PROJECT Ystring)
project(${PARENT_PROJECT}Test)

find_package(JEBTest)
if(NOT JEBTEST_FOUND)
    message(FATAL_ERRORO "Could not find JEBTest.")
endif(NOT JEBTEST_FOUND)

include_directories(${JEBTEST_INCLUDE_DIRS})

set(SOURCE_FILES
    main.cpp
    Generic/test_Convert.cpp
    Generic/test_GenericString.cpp
    Unicode/test_CaseConverter.cpp
    Unicode/test_CaseInsensitive.cpp
    Unicode/test_CharClass.cpp
    Unicode/test_CharMap.cpp
    Unicode/test_CharMappingTypes.cpp
    Utf8/test_Utf8String.cpp
    Utf8/test_Utf8StringCpp11.cpp
    )

add_executable(${PROJECT_NAME}
               ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
                      ${PARENT_PROJECT}
                      ${JEBTEST_LIBRARIES})

add_test(${PARENT_PROJECT} ${PROJECT_NAME})
