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
    set(PUBLIC_HEADERS_ROOT
        ${PUBLIC_HEADERS_ROOT}
        src/Ystring/Utf16W.hpp
        )
    set(PUBLIC_HEADERS_UTF16
        ${PUBLIC_HEADERS_UTF16}
        src/Ystring/Utf16/Utf16WString.hpp
        )
    set(PRIVATE_HEADERS
        ${PRIVATE_HEADERS}
        src/Ystring/Utf16/Utf16WChars.hpp
        )
    set(SOURCE_FILES
        ${SOURCE_FILES}
        src/Ystring/Utf16/Utf16WString.cpp
        )
endif(YSTRING_WCHAR_IS_2_BYTES)

set(PUBLIC_HEADERS_ROOT
    src/Ystring/Conversion.hpp
    src/Ystring/Encoding.hpp
    src/Ystring/EncodingInfo.hpp
    src/Ystring/Endianness.hpp
    src/Ystring/EscapeType.hpp
    src/Ystring/FindFlags.hpp
    src/Ystring/PlatformDetails.hpp
    src/Ystring/Predicates.hpp
    src/Ystring/SplitFlags.hpp
    src/Ystring/Utf8.hpp
    src/Ystring/Utf16.hpp
    src/Ystring/Utf32.hpp
    src/Ystring/YstringDefinitions.hpp
    src/Ystring/YstringException.hpp
    ${PUBLIC_HEADERS_ROOT}
    )

set(PUBLIC_HEADERS_CONVERSION
    src/Ystring/Conversion/Convert.hpp
    src/Ystring/Conversion/Converter.hpp
    src/Ystring/Conversion/ErrorHandlingPolicy.hpp
    )

set(PUBLIC_HEADERS_STREAMING
    src/Ystring/Streaming/StreamFill.hpp
    src/Ystring/Streaming/StreamJoin.hpp
    src/Ystring/Streaming/StreamOperators.hpp
    )

set(PUBLIC_HEADERS_UNICODE
    src/Ystring/Unicode/CharClass.hpp
    src/Ystring/Unicode/UnicodeChars.hpp
    src/Ystring/Unicode/UnicodePredicates.hpp
    )

set(PUBLIC_HEADERS_UTF8
    src/Ystring/Utf8/Utf8String.hpp
    )

set(PUBLIC_HEADERS_UTF16
    src/Ystring/Utf16/Utf16String.hpp
    ${PUBLIC_HEADERS_UTF16}
    )

set(PUBLIC_HEADERS_UTF32
    src/Ystring/Utf32/Utf32String.hpp
    ${PUBLIC_HEADERS_UTF32}
    )

set(PUBLIC_HEADERS
    ${PUBLIC_HEADERS_ROOT}
    ${PUBLIC_HEADERS_CONVERSION}
    ${PUBLIC_HEADERS_STREAMING}
    ${PUBLIC_HEADERS_UNICODE}
    ${PUBLIC_HEADERS_UTF8}
    ${PUBLIC_HEADERS_UTF16}
    ${PUBLIC_HEADERS_UTF32}
    )

set(PRIVATE_HEADERS
    src/Ystring/Encodings/DecoderResult.hpp
    src/Ystring/PrivatePlatformDetails.hpp
    src/Ystring/Conversion/AbstractDecoder.hpp
    src/Ystring/Conversion/AbstractEncoder.hpp
    src/Ystring/Conversion/CodePageDecoder.hpp
    src/Ystring/Conversion/CodePageEncoder.hpp
    src/Ystring/Conversion/Utf16Decoder.hpp
    src/Ystring/Conversion/Utf16Encoder.hpp
    src/Ystring/Conversion/Utf32Decoder.hpp
    src/Ystring/Conversion/Utf32Encoder.hpp
    src/Ystring/Conversion/Utf8Decoder.hpp
    src/Ystring/Conversion/Utf8Encoder.hpp
    src/Ystring/Encodings/CodePage.hpp
    src/Ystring/Encodings/CodePageFactory.hpp
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
    src/Ystring/Encodings/EncodeUtf8.hpp
    src/Ystring/Encodings/Ibm437.hpp
    src/Ystring/Encodings/Ibm850.hpp
    src/Ystring/Encodings/Iso8859_1.hpp
    src/Ystring/Encodings/Iso8859_10.hpp
    src/Ystring/Encodings/Iso8859_15.hpp
    src/Ystring/Encodings/Iso8859_9.hpp
    src/Ystring/Encodings/Windows1250.hpp
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
    src/Ystring/Unicode/CaseConverter.hpp
    src/Ystring/Unicode/CaseInsensitive.hpp
    src/Ystring/Unicode/CharMap.hpp
    src/Ystring/Unicode/CharMappingTypes.hpp
    src/Ystring/Unicode/StandardLowerCase.hpp
    src/Ystring/Unicode/StandardTitleCase.hpp
    src/Ystring/Unicode/StandardUpperCase.hpp
    src/Ystring/Utf16/Utf16Chars.hpp
    src/Ystring/Utf16/Utf16Encoding.hpp
    src/Ystring/Utf32/Utf32Chars.hpp
    src/Ystring/Utf32/Utf32Encoding.hpp
    src/Ystring/Utf8/Utf8Chars.hpp
    src/Ystring/Utf8/Utf8Encoding.hpp
    src/Ystring/Utilities/Algorithms.hpp
    src/Ystring/Utilities/ArrayOutputIterator.hpp
    src/Ystring/Utilities/CountingOutputIterator.hpp
    src/Ystring/Utilities/Endian.hpp
    src/Ystring/Utilities/Iterators.hpp
    src/Ystring/Utilities/KeyFunctionAlgorithms.hpp
    src/Ystring/Utilities/Union16.hpp
    src/Ystring/Utilities/Union32.hpp
    src/Ystring/Utilities/Utilities.hpp
    ${PRIVATE_HEADERS}
    )

set(SOURCE_FILES
    src/Ystring/EncodingInfo.cpp
    src/Ystring/Predicates.cpp
    src/Ystring/YstringException.cpp
    src/Ystring/Conversion/AbstractDecoder.cpp
    src/Ystring/Conversion/AbstractEncoder.cpp
    src/Ystring/Conversion/CodePageDecoder.cpp
    src/Ystring/Conversion/CodePageEncoder.cpp
    src/Ystring/Conversion/Converter.cpp
    src/Ystring/Conversion/Utf8Decoder.cpp
    src/Ystring/Conversion/Utf8Encoder.cpp
    src/Ystring/Encodings/CodePage.cpp
    src/Ystring/Encodings/CodePageFactory.cpp
    src/Ystring/Encodings/EncodeUtf8.cpp
    src/Ystring/Encodings/Ibm437.cpp
    src/Ystring/Encodings/Ibm850.cpp
    src/Ystring/Encodings/Iso8859_1.cpp
    src/Ystring/Encodings/Iso8859_10.cpp
    src/Ystring/Encodings/Iso8859_15.cpp
    src/Ystring/Encodings/Iso8859_9.cpp
    src/Ystring/Encodings/Windows1250.cpp
    src/Ystring/Encodings/Windows1252.cpp
    src/Ystring/Streaming/StreamOperators.cpp
    src/Ystring/Unicode/CaseConverter.cpp
    src/Ystring/Unicode/CharClass.cpp
    src/Ystring/Unicode/CharMap.cpp
    src/Ystring/Unicode/CharMappingTypes.cpp
    src/Ystring/Utf16/Utf16String.cpp
    src/Ystring/Utf32/Utf32String.cpp
    src/Ystring/Utf8/Utf8String.cpp
    ${SOURCE_FILES}
    )

add_library(Ystring STATIC
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    )

target_compile_definitions(Ystring
    PRIVATE
        $<$<BOOL:${MSVC}>:_SCL_SECURE_NO_WARNINGS>
        $<$<BOOL:${MSVC}>:YSTRING_EXPORTS>
)

set_target_properties(Ystring PROPERTIES
    MACOSX_RPATH ON
    DEBUG_OUTPUT_NAME "Ystring.debug")

set(CTEST_OUTPUT_ON_FAILURE 1)
add_subdirectory(YstringTest)

install(TARGETS Ystring DESTINATION lib)
install(FILES ${PUBLIC_HEADERS_ROOT}
    DESTINATION include/Ystring)
install(FILES ${PUBLIC_HEADERS_CONVERSION}
    DESTINATION include/Ystring/Conversion)
install(FILES ${PUBLIC_HEADERS_STREAMING}
    DESTINATION include/Ystring/Streaming)
install(FILES ${PUBLIC_HEADERS_UNICODE}
    DESTINATION include/Ystring/Unicode)
install(FILES ${PUBLIC_HEADERS_UTF8}
    DESTINATION include/Ystring/Utf8)
install(FILES ${PUBLIC_HEADERS_UTF16}
    DESTINATION include/Ystring/Utf16)
install(FILES ${PUBLIC_HEADERS_UTF32}
    DESTINATION include/Ystring/Utf32)
