//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../EscapeType.hpp"
#include "../Encoded/AppendEscaped.hpp"
#include "../Encoded/AppendUnescaped.hpp"
#include "../Encoded/BackslashUnescaper.hpp"
#include "../Encoded/FixedLengthBackslashEscaper.hpp"
#include "../Encoded/UrlEscaper.hpp"
#include "../Encoded/VariableLengthBackslashEscaper.hpp"
#include "../Encoded/XmlEscaper.hpp"

namespace Ystring { namespace Generic {
    namespace Detail {
        Encoded::FixedLengthBackslashEscaper makeFixedLengthBackslashEscaper(
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
            Encoded::appendEscaped(
                    dst.getAppender(),
                    src,
                    Encoded::isMandatoryEscape,
                    Detail::makeFixedLengthBackslashEscaper(sizeof(Char)));
            break;
        case EscapeType::BACKSLASH_ASCII:
            Encoded::appendEscaped(
                    dst.getAppender(),
                    src,
                    Encoded::isNonAsciiEscape,
                    Detail::makeFixedLengthBackslashEscaper(sizeof(Char)));
            break;
        case EscapeType::BACKSLASH_ASCII_SMART:
            Encoded::appendEscaped(
                    dst.getAppender(),
                    Encoded::makeForwardDecoder(src, encoding),
                    Encoded::isNonAsciiEscape,
                    Encoded::VariableLengthBackslashEscaper());
            break;
        case EscapeType::JSON:
            Encoded::appendEscaped(
                    dst.getAppender(),
                    Encoded::makeForwardDecoder(src, encoding),
                    Encoded::isMandatoryEscape,
                    Encoded::FixedLengthBackslashEscaper('u', 4));
            break;
        case EscapeType::JSON_ASCII:
            Encoded::appendEscaped(
                    dst.getAppender(),
                    Encoded::makeForwardDecoder(src, encoding),
                    Encoded::isNonAsciiEscape,
                    Encoded::FixedLengthBackslashEscaper('u', 4));
            break;
        case EscapeType::URL_QUERY:
            Encoded::appendEscaped(
                    dst.getAppender(),
                    src,
                    Encoded::isUrlQueryEscape,
                    Encoded::UrlEscaper());
            break;
        case EscapeType::XML_ATTRIBUTE:
            Encoded::appendEscaped(
                    dst.getAppender(),
                    Encoded::makeForwardDecoder(src, encoding),
                    Encoded::isXmlAttributeEscape,
                    Encoded::XmlEscaper());
            break;
        case EscapeType::XML_TEXT:
            Encoded::appendEscaped(
                    dst.getAppender(),
                    Encoded::makeForwardDecoder(src, encoding),
                    Encoded::isXmlTextEscape,
                    Encoded::XmlEscaper());
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
            Encoded::appendUnescaped(
                    dst,
                    src,
                    encoding,
                    Encoded::isBackslash,
                    Encoded::BackslashUnescaper(true));
            break;
        case EscapeType::JSON:
        case EscapeType::JSON_ASCII:
            Encoded::appendUnescaped(
                    dst,
                    src,
                    encoding,
                    Encoded::isBackslash,
                    Encoded::BackslashUnescaper(false));
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
            return Encoded::hasUnescapedCharacters(
                    str, Encoded::isMandatoryEscape);
        case EscapeType::BACKSLASH_ASCII:
            return Encoded::hasUnescapedCharacters(
                    str, Encoded::isNonAsciiEscape);
        case EscapeType::BACKSLASH_ASCII_SMART:
            return Encoded::hasUnescapedCharacters(
                    Encoded::makeForwardDecoder(str, encoding),
                    Encoded::isNonAsciiEscape);
        case EscapeType::JSON:
            return Encoded::hasUnescapedCharacters(
                    Encoded::makeForwardDecoder(str, encoding),
                    Encoded::isMandatoryEscape);
        case EscapeType::JSON_ASCII:
            return Encoded::hasUnescapedCharacters(
                    Encoded::makeForwardDecoder(str, encoding),
                    Encoded::isNonAsciiEscape);
        case EscapeType::URL_QUERY:
            return Encoded::hasUnescapedCharacters(
                    str, Encoded::isUrlQueryEscape);
        case EscapeType::XML_ATTRIBUTE:
            return Encoded::hasUnescapedCharacters(
                    Encoded::makeForwardDecoder(str, encoding),
                    Encoded::isXmlAttributeEscape);
        case EscapeType::XML_TEXT:
            return Encoded::hasUnescapedCharacters(
                    Encoded::makeForwardDecoder(str, encoding),
                    Encoded::isXmlTextEscape);
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
        Encoded::FixedLengthBackslashEscaper makeFixedLengthBackslashEscaper(
                size_t charSize)
        {
            if (charSize == 1)
                return Encoded::FixedLengthBackslashEscaper('x', 2);
            if (charSize == 2)
                return Encoded::FixedLengthBackslashEscaper('u', 4);
            return Encoded::FixedLengthBackslashEscaper('U', 8);
        }
    }
}}
