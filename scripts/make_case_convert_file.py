# -*- coding: utf-8 -*-
##****************************************************************************
## Copyright © 2012 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2012-06-28.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
import datetime
import os
import sys
import codegen

AlternativeIndexes = {
    "Upper": -1,
    "Lower": -2,
    "Title": -3
}

def getMostPrevalentDiff(values):
    diffs = {}
    for v, w in values:
        if not diffs.get(w - v):
            diffs[w - v] = 1
        else:
            diffs[w - v] += 1
    bestDiff, maxCount = 0, 0
    for diff in diffs:
        if diffs[diff] > maxCount:
            bestDiff, maxCount = diff, diffs[diff]
    return bestDiff, maxCount

def makeDiffSet(major, diff, values):
    bitSet = 0
    nbitSet = 0xFFFFFFFF
    remainder = []
    for v, w in values:
        if w - v == diff:
            bitSet |= 1 << (v - major)
        else:
            remainder.append((v, w))
        nbitSet ^= 1 << (v - major)
    return (major, diff, bitSet, nbitSet), remainder

template = """\
//****************************************************************************
// Copyright © [[[year]]] Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on [[[date]]].
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "CharMappingTypes.hpp"

namespace Ystring { namespace Unicode {

CompactCharMapping Compact[[[name]]]CaseMappings[] =
{
    [[[compact_mappings]]]
};

CharMapping [[[name]]]CaseMappings[] =
{
    [[[mappings]]]
};

}}
"""

def writeCpp(diffSets, mappings, name):
    compactMappings = []
    for diffSet in diffSets:
        if diffSet[1] < 0:
            s = "{0x%06X, 0x%08X, 0x%08X, 0x%08X}," % (
                diffSet[0], 2**32 + diffSet[1], diffSet[2], diffSet[3])
        else:
            s = "{0x%06X, 0x%08X, 0x%08X, 0x%08X}," % diffSet
        compactMappings.append(s)
    expandedMappings = []
    for ch, altCh in mappings:
        expandedMappings.append("{0x%06X, 0x%06X}," % (ch, altCh))
    date = datetime.date.today()
    codegenParams = dict(
        year=date.year,
        date="%d-%02d-%02d" % (date.year, date.month, date.day),
        name=name,
        compact_mappings=compactMappings,
        mappings=expandedMappings)
    print(codegen.makeText(template, codegen.DictExpander(codegenParams)))

def main(args):
    if len(args) != 2:
        print("usage: %s <name> <unicode data file>"
              % os.path.basename(sys.argv[0]))
        print("<name> must be 'upper', 'lower' or 'title'")
        return 1
    name = args[0].title()
    alternativeIndex = AlternativeIndexes[name]
    chars = {}
    for line in open(args[1]):
        parts = line.split(";")
        parts[-1] = parts[-1].strip()
        if parts[alternativeIndex]:
            ch = int(parts[0], 16)
            altCh = int(parts[alternativeIndex], 16)
            major = (ch // 32) * 32
            charList = chars.get(major)
            if not charList:
                chars[major] = [(ch, altCh)]
            else:
                charList.append((ch, altCh))
    diffSets = []
    mappings = []
    for major in sorted(chars):
        diff, count = getMostPrevalentDiff(chars[major])
        if count > 2:
            diffSet, remainder = makeDiffSet(major, diff, chars[major])
            diffSets.append(diffSet)
            mappings.extend(remainder)
        else:
            mappings.extend(chars[major])
    writeCpp(diffSets, mappings, name)
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
