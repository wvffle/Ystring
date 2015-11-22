//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-22
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractEncoder.hpp"
#include "../CodePage/CodePage.hpp"

namespace Ystring { namespace Conversion {

    class CodePageEncoder : public AbstractEncoder
    {
    public:
        CodePageEncoder(Encoding_t encoding);

        void setReplacementCharacter(char32_t value);

    protected:
        bool doEncode(const char32_t*& srcBeg, const char32_t* srcEnd,
                      std::string& dst);

    private:
        CodePage::CodePage m_CodePage;
    };

}}
