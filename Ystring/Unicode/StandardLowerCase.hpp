//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "CharMappingTypes.hpp"

namespace Ystring { namespace Unicode
{
    CompactCharMapping CompactLowerCaseMappings[] =
    {
        {0x000040, 0x00000020, 0x07FFFFFE, 0xF8000001},
        {0x0000C0, 0x00000020, 0x7F7FFFFF, 0x80800000},
        {0x000100, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x000120, 0x00000001, 0xAA545555, 0x55AAAAAA},
        {0x000140, 0x00000001, 0x555554AA, 0xAAAAAB55},
        {0x000160, 0x00000001, 0x2A555555, 0xD4AAAAAA},
        {0x000180, 0x00000001, 0x01020894, 0x4E243129},
        {0x0001A0, 0x00000001, 0x11289095, 0xEE512D2A},
        {0x0001C0, 0x00000001, 0x4AAAA920, 0xB555524F},
        {0x0001E0, 0x00000001, 0x55145555, 0xAA29AAAA},
        {0x000200, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x000220, 0x00000001, 0x08055554, 0x93FAAAAA},
        {0x000240, 0x00000001, 0x00005542, 0xFFFFAA85},
        {0x000360, 0x00000001, 0x00450000, 0x7FBAFFFF},
        {0x000380, 0x00000020, 0xFFFE0000, 0x000128BF},
        {0x0003A0, 0x00000020, 0x00000FFB, 0xFFFFF004},
        {0x0003C0, 0x00000001, 0x55000000, 0xAAFF7FFF},
        {0x0003E0, 0x00000001, 0x04805555, 0x196FAAAA},
        {0x000400, 0x00000050, 0x0000FFFF, 0x00000000},
        {0x000420, 0x00000020, 0x0000FFFF, 0xFFFF0000},
        {0x000460, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x000480, 0x00000001, 0x55555401, 0xAAAAABFE},
        {0x0004A0, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x0004C0, 0x00000001, 0x55552AAA, 0xAAAAD554},
        {0x0004E0, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x000500, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x000520, 0x00000030, 0xFFFE0000, 0x0001AAAA},
        {0x000540, 0x00000030, 0x007FFFFF, 0xFF800000},
        {0x0010A0, 0x00001C60, 0xFFFFFFFF, 0x00000000},
        {0x0010C0, 0x00001C60, 0x000020BF, 0xFFFFDF40},
        {0x0013A0, 0x000097D0, 0xFFFFFFFF, 0x00000000},
        {0x0013C0, 0x000097D0, 0xFFFFFFFF, 0x00000000},
        {0x0013E0, 0x000097D0, 0x0000FFFF, 0xFFC00000},
        {0x001E00, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x001E20, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x001E40, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x001E60, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x001E80, 0x00000001, 0x00155555, 0xBFEAAAAA},
        {0x001EA0, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x001EC0, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x001EE0, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x001F00, 0xFFFFFFF8, 0x3F00FF00, 0xC0FF00FF},
        {0x001F20, 0xFFFFFFF8, 0xFF00FF00, 0x00FF00FF},
        {0x001F40, 0xFFFFFFF8, 0xAA003F00, 0x55FFC0FF},
        {0x001F60, 0xFFFFFFF8, 0x0000FF00, 0xFFFF00FF},
        {0x001F80, 0xFFFFFFF8, 0xFF00FF00, 0x00FF00FF},
        {0x001FA0, 0xFFFFFFF8, 0x0300FF00, 0xE0FF00FF},
        {0x001FC0, 0xFFFFFFAA, 0x00000F00, 0xF0FFE0FF},
        {0x002160, 0x00000010, 0x0000FFFF, 0xFFFF0000},
        {0x0024A0, 0x0000001A, 0xFFC00000, 0x003FFFFF},
        {0x0024C0, 0x0000001A, 0x0000FFFF, 0xFFFF0000},
        {0x002C00, 0x00000030, 0xFFFFFFFF, 0x00000000},
        {0x002C20, 0x00000030, 0x00007FFF, 0xFFFF8000},
        {0x002C60, 0x00000001, 0x00240A81, 0x3FDA1562},
        {0x002C80, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x002CA0, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x002CC0, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x002CE0, 0x00000001, 0x00042805, 0xFFFBD7FA},
        {0x00A640, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x00A660, 0x00000001, 0x00001555, 0xFFFFEAAA},
        {0x00A680, 0x00000001, 0x05555555, 0xFAAAAAAA},
        {0x00A720, 0x00000001, 0x55545554, 0xAAABAAAB},
        {0x00A740, 0x00000001, 0x55555555, 0xAAAAAAAA},
        {0x00A760, 0x00000001, 0x4A005555, 0x95FFAAAA},
        {0x00A780, 0x00000001, 0x55450855, 0xAABAD7AA},
        {0x00A7A0, 0x00000001, 0x00500155, 0xFFA0C2AA},
        {0x00FF20, 0x00000020, 0x07FFFFFE, 0xF8000001},
        {0x010400, 0x00000028, 0xFFFFFFFF, 0x00000000},
        {0x010420, 0x00000028, 0x000000FF, 0xFFFFFF00},
        {0x010C80, 0x00000040, 0xFFFFFFFF, 0x00000000},
        {0x010CA0, 0x00000040, 0x0007FFFF, 0xFFF80000},
        {0x0118A0, 0x00000020, 0xFFFFFFFF, 0x00000000},
    };

    CharMapping LowerCaseMappings[] =
    {
        {0x000130, 0x000069},
        {0x000178, 0x0000FF},
        {0x000181, 0x000253},
        {0x000186, 0x000254},
        {0x000189, 0x000256},
        {0x00018A, 0x000257},
        {0x00018E, 0x0001DD},
        {0x00018F, 0x000259},
        {0x000190, 0x00025B},
        {0x000193, 0x000260},
        {0x000194, 0x000263},
        {0x000196, 0x000269},
        {0x000197, 0x000268},
        {0x00019C, 0x00026F},
        {0x00019D, 0x000272},
        {0x00019F, 0x000275},
        {0x0001A6, 0x000280},
        {0x0001A9, 0x000283},
        {0x0001AE, 0x000288},
        {0x0001B1, 0x00028A},
        {0x0001B2, 0x00028B},
        {0x0001B7, 0x000292},
        {0x0001C4, 0x0001C6},
        {0x0001C7, 0x0001C9},
        {0x0001CA, 0x0001CC},
        {0x0001F1, 0x0001F3},
        {0x0001F6, 0x000195},
        {0x0001F7, 0x0001BF},
        {0x000220, 0x00019E},
        {0x00023A, 0x002C65},
        {0x00023D, 0x00019A},
        {0x00023E, 0x002C66},
        {0x000243, 0x000180},
        {0x000244, 0x000289},
        {0x000245, 0x00028C},
        {0x00037F, 0x0003F3},
        {0x000386, 0x0003AC},
        {0x000388, 0x0003AD},
        {0x000389, 0x0003AE},
        {0x00038A, 0x0003AF},
        {0x00038C, 0x0003CC},
        {0x00038E, 0x0003CD},
        {0x00038F, 0x0003CE},
        {0x0003CF, 0x0003D7},
        {0x0003F4, 0x0003B8},
        {0x0003F9, 0x0003F2},
        {0x0003FD, 0x00037B},
        {0x0003FE, 0x00037C},
        {0x0003FF, 0x00037D},
        {0x000410, 0x000430},
        {0x000411, 0x000431},
        {0x000412, 0x000432},
        {0x000413, 0x000433},
        {0x000414, 0x000434},
        {0x000415, 0x000435},
        {0x000416, 0x000436},
        {0x000417, 0x000437},
        {0x000418, 0x000438},
        {0x000419, 0x000439},
        {0x00041A, 0x00043A},
        {0x00041B, 0x00043B},
        {0x00041C, 0x00043C},
        {0x00041D, 0x00043D},
        {0x00041E, 0x00043E},
        {0x00041F, 0x00043F},
        {0x0004C0, 0x0004CF},
        {0x000520, 0x000521},
        {0x000522, 0x000523},
        {0x000524, 0x000525},
        {0x000526, 0x000527},
        {0x000528, 0x000529},
        {0x00052A, 0x00052B},
        {0x00052C, 0x00052D},
        {0x00052E, 0x00052F},
        {0x0013F0, 0x0013F8},
        {0x0013F1, 0x0013F9},
        {0x0013F2, 0x0013FA},
        {0x0013F3, 0x0013FB},
        {0x0013F4, 0x0013FC},
        {0x0013F5, 0x0013FD},
        {0x001E9E, 0x0000DF},
        {0x001FBA, 0x001F70},
        {0x001FBB, 0x001F71},
        {0x001FBC, 0x001FB3},
        {0x001FCC, 0x001FC3},
        {0x001FD8, 0x001FD0},
        {0x001FD9, 0x001FD1},
        {0x001FDA, 0x001F76},
        {0x001FDB, 0x001F77},
        {0x001FE8, 0x001FE0},
        {0x001FE9, 0x001FE1},
        {0x001FEA, 0x001F7A},
        {0x001FEB, 0x001F7B},
        {0x001FEC, 0x001FE5},
        {0x001FF8, 0x001F78},
        {0x001FF9, 0x001F79},
        {0x001FFA, 0x001F7C},
        {0x001FFB, 0x001F7D},
        {0x001FFC, 0x001FF3},
        {0x002126, 0x0003C9},
        {0x00212A, 0x00006B},
        {0x00212B, 0x0000E5},
        {0x002132, 0x00214E},
        {0x002183, 0x002184},
        {0x002C62, 0x00026B},
        {0x002C63, 0x001D7D},
        {0x002C64, 0x00027D},
        {0x002C6D, 0x000251},
        {0x002C6E, 0x000271},
        {0x002C6F, 0x000250},
        {0x002C70, 0x000252},
        {0x002C7E, 0x00023F},
        {0x002C7F, 0x000240},
        {0x00A77D, 0x001D79},
        {0x00A78D, 0x000265},
        {0x00A7AA, 0x000266},
        {0x00A7AB, 0x00025C},
        {0x00A7AC, 0x000261},
        {0x00A7AD, 0x00026C},
        {0x00A7B0, 0x00029E},
        {0x00A7B1, 0x000287},
        {0x00A7B2, 0x00029D},
        {0x00A7B3, 0x00AB53},
    };
}}

