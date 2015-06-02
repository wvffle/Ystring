cmake_minimum_required(VERSION 3.2)
project(Ystring)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/Modules"
    ${CMAKE_MODULE_PATH})

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
elseif(WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif(APPLE)

set(PUBLIC_HEADERS
    Ystring/DecoderResult.hpp
    Ystring/FindFlags.hpp
    Ystring/Unicode/CaseConverter.hpp
    Ystring/Unicode/CaseInsensitive.hpp
    Ystring/Unicode/CharClass.hpp
    Ystring/Unicode/UnicodeChars.hpp
    Ystring/Unicode/UnicodePredicates.hpp
    Ystring/Utf8/DecodeUtf8.hpp
    Ystring/Utf8/DecodeUtf8-impl.hpp
    Ystring/Utf8/EncodeUtf8.hpp
    Ystring/Utf8/EncodeUtf8-impl.hpp
    Ystring/Utf8/Utf8Encoding.hpp
    Ystring/Utf8/Utf8String.hpp
    Ystring/Utilities/Iterators.hpp
    Ystring/Utilities/KeyFunctionAlgorithms.hpp
    Ystring/Utilities/Range.hpp
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
    Ystring/Utf8/EncodeUtf8.cpp
    Ystring/Utf8/Utf8String.cpp
    )

add_library(
    ${PROJECT_NAME} SHARED
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    )

set(CTEST_OUTPUT_ON_FAILURE 1)
add_subdirectory(UnitTest)
