##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-05-31
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.2)

project(YstringTest)

find_package(Ytest QUIET)

if (NOT TARGET Ytest::Ytest)
    message("Ytest not found. Unit tests will not be built or run.")
    return()
endif ()

if(MSVC)
    set(SOURCE_FILES_PLATFORM_SPECIFIC
        Utf/test_Utf16WString.cpp)
else()
    set(SOURCE_FILES_PLATFORM_SPECIFIC
        Utf/test_Utf16String.cpp
        )
endif()

add_executable(YstringTest
    main.cpp
    test_EncodingInfo.cpp
    Conversion/test_Converter.cpp
    Generic/test_Convert.cpp
    Generic/test_GenericString.cpp
    Streaming/test_StreamFill.cpp
    Streaming/test_StreamJoin.cpp
    Unicode/test_CaseConverter.cpp
    Unicode/test_CaseInsensitive.cpp
    Unicode/test_CharClass.cpp
    Unicode/test_CharMap.cpp
    Unicode/test_CharMappingTypes.cpp
    Utf/test_DecodeUtf8.cpp
    Utf/test_EncodeUtf8.cpp
    Utf/test_Utf8String.cpp
    Utf/test_Utf8StringCpp11.cpp
    Utf/test_Utf32String.cpp
    Utf/test_DecodeUtf16.cpp
    Utf/test_EncodeUtf16.cpp
    ${SOURCE_FILES_PLATFORM_SPECIFIC}
    )

target_include_directories(YstringTest
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
    )

target_link_libraries(YstringTest
    PRIVATE
        Ystring::Ystring
        Ytest::Ytest
    )

add_test(NAME YstringTest
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/YstringTest
    )
