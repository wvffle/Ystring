##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-05-31.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.13)
project(Ystring)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
    set(YSTRING_WCHAR_IS_2_BYTES TRUE)
endif(MSVC)

if (YSTRING_WCHAR_IS_2_BYTES)
    set(ADDITIONAL_SOURCE_FILES
        include/Ystring/Utf16W.hpp
        include/Ystring/Utf/Utf16WString.hpp
        src/Ystring/Utf/Utf16WChars.hpp
        src/Ystring/Utf/Utf16WString.cpp
        )
endif()

add_library(Ystring STATIC
    include/Ystring/Conversion.hpp
    include/Ystring/Conversion/Convert.hpp
    include/Ystring/Conversion/Converter.hpp
    include/Ystring/Conversion/ErrorHandlingPolicy.hpp
    include/Ystring/Encoding.hpp
    include/Ystring/EncodingInfo.hpp
    include/Ystring/Endianness.hpp
    include/Ystring/EscapeType.hpp
    include/Ystring/FindFlags.hpp
    include/Ystring/PlatformDetails.hpp
    include/Ystring/Predicates.hpp
    include/Ystring/SplitFlags.hpp
    include/Ystring/Streaming/StreamFill.hpp
    include/Ystring/Streaming/StreamJoin.hpp
    include/Ystring/Streaming/StreamOperators.hpp
    include/Ystring/Unicode/CharClass.hpp
    include/Ystring/Unicode/UnicodeChars.hpp
    include/Ystring/Unicode/UnicodePredicates.hpp
    include/Ystring/Utf/Utf16String.hpp
    include/Ystring/Utf/Utf32String.hpp
    include/Ystring/Utf/Utf8String.hpp
    include/Ystring/Utf16.hpp
    include/Ystring/Utf32.hpp
    include/Ystring/Utf8.hpp
    include/Ystring/YstringDefinitions.hpp
    include/Ystring/YstringException.hpp
    src/Ystring/Conversion/AbstractDecoder.cpp
    src/Ystring/Conversion/AbstractDecoder.hpp
    src/Ystring/Conversion/AbstractEncoder.cpp
    src/Ystring/Conversion/AbstractEncoder.hpp
    src/Ystring/Conversion/CodePageDecoder.cpp
    src/Ystring/Conversion/CodePageDecoder.hpp
    src/Ystring/Conversion/CodePageEncoder.cpp
    src/Ystring/Conversion/CodePageEncoder.hpp
    src/Ystring/Conversion/Converter.cpp
    src/Ystring/Conversion/Utf16Decoder.hpp
    src/Ystring/Conversion/Utf16Encoder.hpp
    src/Ystring/Conversion/Utf32Decoder.hpp
    src/Ystring/Conversion/Utf32Encoder.hpp
    src/Ystring/Conversion/Utf8Decoder.cpp
    src/Ystring/Conversion/Utf8Decoder.hpp
    src/Ystring/Conversion/Utf8Encoder.cpp
    src/Ystring/Conversion/Utf8Encoder.hpp
    src/Ystring/EncodingInfo.cpp
    src/Ystring/Encodings/CodePage.cpp
    src/Ystring/Encodings/CodePage.hpp
    src/Ystring/Encodings/CodePageFactory.cpp
    src/Ystring/Encodings/CodePageFactory.hpp
    src/Ystring/Encodings/DecoderResult.hpp
    src/Ystring/Encodings/DecodeUtf16-impl.hpp
    src/Ystring/Encodings/DecodeUtf16.hpp
    src/Ystring/Encodings/DecodeUtf32-impl.hpp
    src/Ystring/Encodings/DecodeUtf32.hpp
    src/Ystring/Encodings/DecodeUtf8-impl.hpp
    src/Ystring/Encodings/DecodeUtf8.hpp
    src/Ystring/Encodings/EncodeUtf16-impl.hpp
    src/Ystring/Encodings/EncodeUtf16.hpp
    src/Ystring/Encodings/EncodeUtf32-impl.hpp
    src/Ystring/Encodings/EncodeUtf32.hpp
    src/Ystring/Encodings/EncodeUtf8-impl.hpp
    src/Ystring/Encodings/EncodeUtf8.cpp
    src/Ystring/Encodings/EncodeUtf8.hpp
    src/Ystring/Encodings/Ibm437.cpp
    src/Ystring/Encodings/Ibm437.hpp
    src/Ystring/Encodings/Ibm850.cpp
    src/Ystring/Encodings/Ibm850.hpp
    src/Ystring/Encodings/Iso8859_1.cpp
    src/Ystring/Encodings/Iso8859_1.hpp
    src/Ystring/Encodings/Iso8859_10.cpp
    src/Ystring/Encodings/Iso8859_10.hpp
    src/Ystring/Encodings/Iso8859_15.cpp
    src/Ystring/Encodings/Iso8859_15.hpp
    src/Ystring/Encodings/Iso8859_9.cpp
    src/Ystring/Encodings/Iso8859_9.hpp
    src/Ystring/Encodings/Windows1250.cpp
    src/Ystring/Encodings/Windows1250.hpp
    src/Ystring/Encodings/Windows1252.cpp
    src/Ystring/Encodings/Windows1252.hpp
    src/Ystring/Generic/Appender.hpp
    src/Ystring/Generic/AppendEscaped.hpp
    src/Ystring/Generic/AppendUnescaped.hpp
    src/Ystring/Generic/BackslashUnescaper.hpp
    src/Ystring/Generic/DecoderAlgorithms.hpp
    src/Ystring/Generic/DecoderStringFunctions-impl.hpp
    src/Ystring/Generic/DecoderStringFunctions.hpp
    src/Ystring/Generic/Encoder.hpp
    src/Ystring/Generic/FixedLengthBackslashEscaper.hpp
    src/Ystring/Generic/ForwardDecoder.hpp
    src/Ystring/Generic/GenericConvert.hpp
    src/Ystring/Generic/GenericEscape.hpp
    src/Ystring/Generic/GenericJoin.hpp
    src/Ystring/Generic/GenericSplit.hpp
    src/Ystring/Generic/GenericString-impl.hpp
    src/Ystring/Generic/GenericString.hpp
    src/Ystring/Generic/Range.hpp
    src/Ystring/Generic/RangeAlgorithms.hpp
    src/Ystring/Generic/ReverseDecoder.hpp
    src/Ystring/Generic/StringReference.hpp
    src/Ystring/Generic/StringTypeTraits.hpp
    src/Ystring/Generic/UrlEscaper.hpp
    src/Ystring/Generic/VariableLengthBackslashEscaper.hpp
    src/Ystring/Generic/XmlEscaper.hpp
    src/Ystring/Predicates.cpp
    src/Ystring/PrivatePlatformDetails.hpp
    src/Ystring/Streaming/StreamOperators.cpp
    src/Ystring/Unicode/CaseConverter.cpp
    src/Ystring/Unicode/CaseConverter.hpp
    src/Ystring/Unicode/CaseInsensitive.hpp
    src/Ystring/Unicode/CharClass.cpp
    src/Ystring/Unicode/CharMap.cpp
    src/Ystring/Unicode/CharMap.hpp
    src/Ystring/Unicode/CharMappingTypes.cpp
    src/Ystring/Unicode/CharMappingTypes.hpp
    src/Ystring/Unicode/StandardLowerCase.hpp
    src/Ystring/Unicode/StandardTitleCase.hpp
    src/Ystring/Unicode/StandardUpperCase.hpp
    src/Ystring/Utf/Utf16Chars.hpp
    src/Ystring/Utf/Utf16Encoding.hpp
    src/Ystring/Utf/Utf16String.cpp
    src/Ystring/Utf/Utf32Chars.hpp
    src/Ystring/Utf/Utf32Encoding.hpp
    src/Ystring/Utf/Utf32String.cpp
    src/Ystring/Utf/Utf8Chars.hpp
    src/Ystring/Utf/Utf8Encoding.hpp
    src/Ystring/Utf/Utf8String.cpp
    src/Ystring/Utilities/Algorithms.hpp
    src/Ystring/Utilities/ArrayOutputIterator.hpp
    src/Ystring/Utilities/CountingOutputIterator.hpp
    src/Ystring/Utilities/Endian.hpp
    src/Ystring/Utilities/Iterators.hpp
    src/Ystring/Utilities/KeyFunctionAlgorithms.hpp
    src/Ystring/Utilities/Union16.hpp
    src/Ystring/Utilities/Union32.hpp
    src/Ystring/Utilities/Utilities.hpp
    src/Ystring/YstringException.cpp
    ${ADDITIONAL_SOURCE_FILES}
    )

target_compile_definitions(Ystring
    PRIVATE
        $<$<BOOL:${MSVC}>:_SCL_SECURE_NO_WARNINGS>
    )

target_include_directories(Ystring BEFORE
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

set_target_properties(Ystring PROPERTIES
    MACOSX_RPATH ON
    DEBUG_OUTPUT_NAME "Ystring.debug")

add_library(Ystring::Ystring ALIAS Ystring)

if (EXISTS "${CMAKE_SOURCE_DIR}/external/Ytest/CMakeLists.txt")
    add_subdirectory(external/Ytest EXCLUDE_FROM_ALL)
endif ()

enable_testing()

add_subdirectory(tests/YstringTest)

export(TARGETS Ystring
    NAMESPACE
        Ystring::
    FILE
        YstringConfig.cmake
    )

include(GNUInstallDirs)

install(TARGETS Ystring
    EXPORT
        YstringConfig
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(EXPORT YstringConfig
    FILE
        YstringConfig.cmake
    NAMESPACE
        Yson::
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/Ystring
    )

install(
    DIRECTORY
        include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
    )
