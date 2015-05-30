cmake_minimum_required(VERSION 3.2)
project(Ystring)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/Modules"
    ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(PUBLIC_HEADERS
    Ystring/Unicode/CaseConverter.hpp
    Ystring/Unicode/CaseInsensitive.hpp
    Ystring/Unicode/CharClass.hpp
    Ystring/Unicode/UnicodeChars.hpp
    Ystring/Unicode/UnicodePredicates.hpp
    Ystring/Utilities/KeyFunctionAlgorithms.hpp
    )

set(PRIVATE_HEADERS
    Ystring/Unicode/CharMap.hpp
    Ystring/Unicode/CharMappingTypes.hpp
    Ystring/Unicode/StandardLowerCase.hpp
    Ystring/Unicode/StandardTitleCase.hpp
    Ystring/Unicode/StandardUpperCase.hpp
    )

set(SOURCE_FILES
    Ystring/Unicode/CaseConverter.cpp
    Ystring/Unicode/CharClass.cpp
    Ystring/Unicode/CharMap.cpp
    Ystring/Unicode/CharMappingTypes.cpp
    )

add_library(
    ${PROJECT_NAME} SHARED
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    )


set(CTEST_OUTPUT_ON_FAILURE 1)
add_subdirectory(UnitTest)
