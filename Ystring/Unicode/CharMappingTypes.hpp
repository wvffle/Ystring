#pragma once

#include <cstdint>
#include <utility>

namespace Ystring { namespace Unicode {

struct CompactCharMapping
{
    uint32_t segment;
    uint32_t offset;
    uint32_t affected;
    uint32_t ignorable;

    bool get(uint32_t chr, uint32_t& mappedChr) const;
};

struct CharMapping
{
    uint32_t chr;
    uint32_t mappedChr;
};

}}
