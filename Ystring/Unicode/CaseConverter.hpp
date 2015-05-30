#pragma once

#include <functional>
#include "CharMap.hpp"

namespace Ystring { namespace Unicode {

uint32_t lower(uint32_t ch);
uint32_t title(uint32_t ch);
uint32_t upper(uint32_t ch);

}}
