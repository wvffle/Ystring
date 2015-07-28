#!/bin/sh

if [ ! -e "$1" ]
then
    echo "Usage: $0 <unicode database>"
    exit 1
fi

echo Making StandardUpperCase.hpp
python make_case_convert_file.py upper $1 > StandardUpperCase.hpp
echo Making StandardLowerCase.hpp
python make_case_convert_file.py lower $1 > StandardLowerCase.hpp
echo Making StandardTitleCase.hpp
python make_case_convert_file.py title $1 > StandardTitleCase.hpp
echo Making CharClass.cpp
python make_char_class_file.py $1 > CharClass.cpp
