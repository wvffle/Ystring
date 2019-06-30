//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "Ystring/EscapeType.hpp"
#include "AppendEscaped.hpp"
#include "AppendUnescaped.hpp"
#include "BackslashUnescaper.hpp"
#include "FixedLengthBackslashEscaper.hpp"
#include "UrlEscaper.hpp"
#include "VariableLengthBackslashEscaper.hpp"
#include "XmlEscaper.hpp"

namespace Ystring { namespace Generic {
    namespace Detail {
        EncodedString::FixedLengthBackslashEscaper makeFixedLengthBackslashEscaper(
                size_t charSize);
    }

    template<typename Str, typename It, typename Enc>
    void appendEscaped(StringReference<Str>& dst,
                       Range<It> src,
                       EscapeType_t type,
                       Enc encoding)
    {
        typedef typename StringReference<Str>::ValueType Char;
        switch (type)
        {
        case EscapeType::BACKSLASH:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    src,
                    EncodedString::isMandatoryEscape,
                    Detail::makeFixedLengthBackslashEscaper(sizeof(Char)));
            break;
        case EscapeType::BACKSLASH_ASCII:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    src,
                    EncodedString::isNonAsciiEscape,
                    Detail::makeFixedLengthBackslashEscaper(sizeof(Char)));
            break;
        case EscapeType::BACKSLASH_ASCII_SMART:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    EncodedString::makeForwardDecoder(src, encoding),
                    EncodedString::isNonAsciiEscape,
                    EncodedString::VariableLengthBackslashEscaper());
            break;
        case EscapeType::JSON:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    EncodedString::makeForwardDecoder(src, encoding),
                    EncodedString::isMandatoryEscape,
                    EncodedString::FixedLengthBackslashEscaper('u', 4));
            break;
        case EscapeType::JSON_ASCII:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    EncodedString::makeForwardDecoder(src, encoding),
                    EncodedString::isNonAsciiEscape,
                    EncodedString::FixedLengthBackslashEscaper('u', 4));
            break;
        case EscapeType::URL_QUERY:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    src,
                    EncodedString::isUrlQueryEscape,
                    EncodedString::UrlEscaper());
            break;
        case EscapeType::XML_ATTRIBUTE:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    EncodedString::makeForwardDecoder(src, encoding),
                    EncodedString::isXmlAttributeEscape,
                    EncodedString::XmlEscaper());
            break;
        case EscapeType::XML_TEXT:
            EncodedString::appendEscaped(
                    dst.getAppender(),
                    EncodedString::makeForwardDecoder(src, encoding),
                    EncodedString::isXmlTextEscape,
                    EncodedString::XmlEscaper());
            break;
        default:
            YSTRING_THROW("Unsupported escape type " +
                          std::to_string(uint64_t(type)));
        }
    }

    template<typename Str, typename It, typename Enc>
    void appendUnescaped(StringReference<Str>& dst,
                         Range<It> src,
                         EscapeType_t type,
                         Enc encoding)
    {
        switch (type)
        {
        case EscapeType::BACKSLASH:
        case EscapeType::BACKSLASH_ASCII:
        case EscapeType::BACKSLASH_ASCII_SMART:
            EncodedString::appendUnescaped(
                    dst,
                    src,
                    encoding,
                    EncodedString::isBackslash,
                    EncodedString::BackslashUnescaper(true));
            break;
        case EscapeType::JSON:
        case EscapeType::JSON_ASCII:
            EncodedString::appendUnescaped(
                    dst,
                    src,
                    encoding,
                    EncodedString::isBackslash,
                    EncodedString::BackslashUnescaper(false));
            break;
        case EscapeType::XML_ATTRIBUTE:
        case EscapeType::XML_TEXT:
        default:
            YSTRING_THROW("Unsupported escape type " +
                          std::to_string(uint64_t(type)));
        }
    }

    template <typename It>
    bool hasEscapedCharacters(Range <It> str,
                              EscapeType_t type)
    {
        switch (type)
        {
        case EscapeType::BACKSLASH:
        case EscapeType::BACKSLASH_ASCII:
        case EscapeType::BACKSLASH_ASCII_SMART:
        case EscapeType::JSON:
        case EscapeType::JSON_ASCII:
            return find(str, '\\') != end(str);
        case EscapeType::URL_QUERY:
            return find(str, '%') != end(str);
        case EscapeType::XML_ATTRIBUTE:
        case EscapeType::XML_TEXT:
            return find(str, '&') != end(str);
        default:
            YSTRING_THROW("Unsupported escape type " +
                          std::to_string(uint64_t(type)));
        }
    }

    template <typename It, typename Enc>
    bool hasUnescapedCharacters(Range <It> str,
                                EscapeType_t type,
                                Enc encoding)
    {
        switch (type)
        {
        case EscapeType::BACKSLASH:
            return EncodedString::hasUnescapedCharacters(
                    str, EncodedString::isMandatoryEscape);
        case EscapeType::BACKSLASH_ASCII:
            return EncodedString::hasUnescapedCharacters(
                    str, EncodedString::isNonAsciiEscape);
        case EscapeType::BACKSLASH_ASCII_SMART:
            return EncodedString::hasUnescapedCharacters(
                    EncodedString::makeForwardDecoder(str, encoding),
                    EncodedString::isNonAsciiEscape);
        case EscapeType::JSON:
            return EncodedString::hasUnescapedCharacters(
                    EncodedString::makeForwardDecoder(str, encoding),
                    EncodedString::isMandatoryEscape);
        case EscapeType::JSON_ASCII:
            return EncodedString::hasUnescapedCharacters(
                    EncodedString::makeForwardDecoder(str, encoding),
                    EncodedString::isNonAsciiEscape);
        case EscapeType::URL_QUERY:
            return EncodedString::hasUnescapedCharacters(
                    str, EncodedString::isUrlQueryEscape);
        case EscapeType::XML_ATTRIBUTE:
            return EncodedString::hasUnescapedCharacters(
                    EncodedString::makeForwardDecoder(str, encoding),
                    EncodedString::isXmlAttributeEscape);
        case EscapeType::XML_TEXT:
            return EncodedString::hasUnescapedCharacters(
                    EncodedString::makeForwardDecoder(str, encoding),
                    EncodedString::isXmlTextEscape);
        default:
            YSTRING_THROW("Unsupported escape type " +
                          std::to_string(uint64_t(type)));
        }
    }

    template<typename Str, typename It, typename Enc>
    Str escape(Range<It> src, EscapeType_t type, Enc encoding)
    {
        auto str = Str();
        auto ref = makeStringReference(str);
        appendEscaped(ref, src, type, encoding);
        return str;
    }

    template<typename Str, typename It, typename Enc>
    Str unescape(Range<It> src, EscapeType_t type, Enc encoding)
    {
        auto str = Str();
        auto ref = makeStringReference(str);
        appendUnescaped(ref, src, type, encoding);
        return str;
    }

    namespace Detail {
        inline
        EncodedString::FixedLengthBackslashEscaper makeFixedLengthBackslashEscaper(
                size_t charSize)
        {
            if (charSize == 1)
                return EncodedString::FixedLengthBackslashEscaper('x', 2);
            if (charSize == 2)
                return EncodedString::FixedLengthBackslashEscaper('u', 4);
            return EncodedString::FixedLengthBackslashEscaper('U', 8);
        }
    }
}}
