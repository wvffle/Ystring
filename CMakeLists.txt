##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-05-31.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 2.8)
project(Ystring)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
elseif(WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS -DYSTRING_EXPORTS)
endif(APPLE)

if(MSVC)
    set(YSTRING_WCHAR_IS_2_BYTES TRUE)
    if(MSVC_VERSION LESS 1900)
        set(YSTRING_NO_NEW_CHAR_TYPE TRUE)
    endif(MSVC_VERSION LESS 1900)
endif(MSVC)

if (YSTRING_WCHAR_IS_2_BYTES)
    set(PUBLIC_HEADERS_ROOT
        ${PUBLIC_HEADERS_ROOT}
        Ystring/Utf16W.hpp
        )
    set(PUBLIC_HEADERS_UTF16
        ${PUBLIC_HEADERS_UTF16}
        Ystring/Utf16/Utf16WString.hpp
        )
    set(PRIVATE_HEADERS
        ${PRIVATE_HEADERS}
        Ystring/Utf16/Utf16WChars.hpp
        )
    set(SOURCE_FILES
        ${SOURCE_FILES}
        Ystring/Utf16/Utf16WString.cpp
        )
endif(YSTRING_WCHAR_IS_2_BYTES)

set(PUBLIC_HEADERS_ROOT
    Ystring/Encoding.hpp
    Ystring/EncodingInfo.hpp
    Ystring/EscapeType.hpp
    Ystring/FindFlags.hpp
    Ystring/PlatformDetails.hpp
    Ystring/Predicates.hpp
    Ystring/SplitFlags.hpp
    Ystring/Utf8.hpp
    Ystring/Utf16.hpp
    Ystring/Utf32.hpp
    Ystring/YstringDefinitions.hpp
    Ystring/YstringException.hpp
    ${PUBLIC_HEADERS_ROOT}
    )

set(PUBLIC_HEADERS_STREAMING
    Ystring/Streaming/StreamFill.hpp
    Ystring/Streaming/StreamJoin.hpp
    Ystring/Streaming/StreamOperators.hpp
    )

set(PUBLIC_HEADERS_UNICODE
    Ystring/Unicode/CharClass.hpp
    Ystring/Unicode/UnicodeChars.hpp
    Ystring/Unicode/UnicodePredicates.hpp
    )

set(PUBLIC_HEADERS_UTF8
    Ystring/Utf8/Utf8String.hpp
    )

set(PUBLIC_HEADERS_UTF16
    ${PUBLIC_HEADERS_UTF16}
    Ystring/Utf16/Utf16String.hpp
    )

set(PUBLIC_HEADERS_UTF32
    ${PUBLIC_HEADERS_UTF32}
    Ystring/Utf32/Utf32String.hpp
    )

set(PUBLIC_HEADERS
    ${PUBLIC_HEADERS_ROOT}
    ${PUBLIC_HEADERS_STREAMING}
    ${PUBLIC_HEADERS_UTF8}
    ${PUBLIC_HEADERS_UTF16}
    ${PUBLIC_HEADERS_UTF32}
    )

set(PRIVATE_HEADERS
    Ystring/DecoderResult.hpp
    Ystring/PrivatePlatformDetails.hpp
    Ystring/CodePage/CodePage.hpp
    Ystring/CodePage/CodePageEncoding.hpp
    Ystring/CodePage/Cp437.hpp
    Ystring/CodePage/Iso8859_1.hpp
    Ystring/CodePage/Windows1252.hpp
    Ystring/Encoded/Appender.hpp
    Ystring/Encoded/AppendEscaped.hpp
    Ystring/Encoded/AppendUnescaped.hpp
    Ystring/Encoded/BackslashUnescaper.hpp
    Ystring/Encoded/DecoderAlgorithms.hpp
    Ystring/Encoded/DecoderStringFunctions.hpp
    Ystring/Encoded/DecoderStringFunctions-impl.hpp
    Ystring/Encoded/Encoder.hpp
    Ystring/Encoded/FixedLengthBackslashEscaper.hpp
    Ystring/Encoded/ForwardDecoder.hpp
    Ystring/Encoded/ReverseDecoder.hpp
    Ystring/Encoded/VariableLengthBackslashEscaper.hpp
    Ystring/Encoded/XmlEscaper.hpp
    Ystring/Generic/StringReference.hpp
    Ystring/Generic/GenericString.hpp
    Ystring/Generic/GenericString-impl.hpp
    Ystring/Generic/Range.hpp
    Ystring/Generic/RangeAlgorithms.hpp
    Ystring/Generic/StringTypeTraits.hpp
    Ystring/Unicode/CaseConverter.hpp
    Ystring/Unicode/CaseInsensitive.hpp
    Ystring/Unicode/CharMap.hpp
    Ystring/Unicode/CharMappingTypes.hpp
    Ystring/Unicode/StandardLowerCase.hpp
    Ystring/Unicode/StandardTitleCase.hpp
    Ystring/Unicode/StandardUpperCase.hpp
    Ystring/Utf8/DecodeUtf8.hpp
    Ystring/Utf8/DecodeUtf8-impl.hpp
    Ystring/Utf8/EncodeUtf8.hpp
    Ystring/Utf8/EncodeUtf8-impl.hpp
    Ystring/Utf8/Utf8Chars.hpp
    Ystring/Utf8/Utf8Encoding.hpp
    Ystring/Utf16/DecodeUtf16.hpp
    Ystring/Utf16/DecodeUtf16-impl.hpp
    Ystring/Utf16/EncodeUtf16.hpp
    Ystring/Utf16/EncodeUtf16-impl.hpp
    Ystring/Utf16/Utf16Chars.hpp
    Ystring/Utf16/Utf16Encoding.hpp
    Ystring/Utf32/DecodeUtf32.hpp
    Ystring/Utf32/DecodeUtf32-impl.hpp
    Ystring/Utf32/EncodeUtf32.hpp
    Ystring/Utf32/EncodeUtf32-impl.hpp
    Ystring/Utf32/Utf32Chars.hpp
    Ystring/Utf32/Utf32Encoding.hpp
    Ystring/Utilities/Algorithms.hpp
    Ystring/Utilities/ArrayOutputIterator.hpp
    Ystring/Utilities/CountingOutputIterator.hpp
    Ystring/Utilities/Endian.hpp
    Ystring/Utilities/Iterators.hpp
    Ystring/Utilities/KeyFunctionAlgorithms.hpp
    Ystring/Utilities/Union16.hpp
    Ystring/Utilities/Union32.hpp
    Ystring/Utilities/Utilities.hpp
    Ystring/Encoded/UrlEscaper.hpp
    ${PRIVATE_HEADERS}
    )

set(SOURCE_FILES
    Ystring/EncodingInfo.cpp
    Ystring/Predicates.cpp
    Ystring/YstringException.cpp
    Ystring/CodePage/CodePage.cpp
    Ystring/CodePage/Cp437.cpp
    Ystring/CodePage/Iso8859_1.cpp
    Ystring/CodePage/Windows1252.cpp
    Ystring/Streaming/StreamOperators.cpp
    Ystring/Unicode/CaseConverter.cpp
    Ystring/Unicode/CharClass.cpp
    Ystring/Unicode/CharMap.cpp
    Ystring/Unicode/CharMappingTypes.cpp
    Ystring/Utf8/EncodeUtf8.cpp
    Ystring/Utf8/Utf8String.cpp
    Ystring/Utf16/Utf16String.cpp
    Ystring/Utf32/Utf32String.cpp
    ${SOURCE_FILES}
    )

add_library(
    ${PROJECT_NAME} SHARED
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    )

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        MACOSX_RPATH ON
        DEBUG_OUTPUT_NAME "${PROJECT_NAME}.debug")

set(CTEST_OUTPUT_ON_FAILURE 1)
add_subdirectory(UnitTest)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${PUBLIC_HEADERS_ROOT}
    DESTINATION include/${PROJECT_NAME})
install(FILES ${PUBLIC_HEADERS_STREAMING}
    DESTINATION include/${PROJECT_NAME}/Streaming)
install(FILES ${PUBLIC_HEADERS_UNICODE}
    DESTINATION include/${PROJECT_NAME}/Unicode)
install(FILES ${PUBLIC_HEADERS_UTF8}
    DESTINATION include/${PROJECT_NAME}/Utf8)
install(FILES ${PUBLIC_HEADERS_UTF16}
    DESTINATION include/${PROJECT_NAME}/Utf16)
install(FILES ${PUBLIC_HEADERS_UTF32}
    DESTINATION include/${PROJECT_NAME}/Utf32)
