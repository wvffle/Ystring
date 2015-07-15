Ystring is a library of function that is intended to make it (almost) as easy
to  work with unicode strings in C++ as it is in Python. In particular it
makes it convenient to use UTF-8 encoded strings throughout a program.

Tested and working with the following compilers:
* Visual C++ 2010, 2013 and 2015 (Windows)
* clang-503 (OS X Yosemite)
* gcc

Features
--------
* Support for the three most common unicode encodings, UTF-8, UTF-16, UTF-32.
* Conversion between common encodings (UTF-8, UTF-16, UTF-32, iso-8859-*, cp1252 etc.).
* No third-party dependencies. The only requirements are partial support for C++11 and its standard library.
* Fast algorithms, for instance avoid decoding/encoding steps unless they are necessary.
