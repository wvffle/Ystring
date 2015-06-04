//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <string>
#include "../FindFlags.hpp"

namespace Ystring { namespace Utf8 {

/** @brief Returns true if @a str ends with @a cmp.
  */
bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags = FindFlags::DEFAULTS);

std::pair<std::string::iterator, std::string::iterator> find(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

std::pair<std::string::const_iterator, std::string::const_iterator> find(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

std::pair<std::string::iterator, std::string::iterator> find(
      std::pair<std::string::iterator, std::string::iterator> str,
      const std::string& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

std::pair<std::string::const_iterator, std::string::const_iterator> find(
      std::pair<std::string::const_iterator, std::string::const_iterator> str,
      const std::string& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags_t flags = FindFlags::DEFAULTS);

}}
