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

Examples
--------

### Convert UTF-8 string to upper case

    #include <iostream>
    #include <Ystring/Utf8.hpp>
    
    int main()
    {
        std::string s = u8"Köztársaság";
        std::cout << s << " -> " << Ystring::Utf8::upper(s) << "\n";
    }

Compile and run (in a shell that uses UTF-8, e.g. Terminal under Mac OS X): 

    $ c++ -std=c++11 Upper.cpp -lYstring -o Upper
    $ ./Upper
    Köztársaság -> KÖZTÁRSASÁG

### Convert string to title case

    #include <iostream>
    #include <Ystring/Utf8.hpp>
    
    int main()
    {
        std::cout << Ystring::Utf8::title("still pumped from using the mouse\n");
    }

Compile and run: 

    $ c++ -std=c++11 Title.cpp -lYstring -o Title
    $ ./Title
    Still Pumped From Using The Mouse

### Pretty-print colon-separated paths

    #include <iostream>
    #include <Ystring/Utf8.hpp>
    
    using namespace Ystring::Utf8;
    
    int main(int argc, char* argv[])
    {
        if (argc != 2)
            return 1;
        std::cout << join(split(argv[1], ":"), "\n") << "\n";
    }

Compile and run: 

    $ c++ -std=c++11 PrintPath.cpp -lYstring -o PrintPath
    $ echo $PATH
    $ ./PrintPath $PATH
