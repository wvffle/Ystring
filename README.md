Ystring is a library of function that is intended to make it (almost) as easy
to  work with unicode strings in C++ as it is in Python. In particular it
makes it convenient to manipulate UTF-8 encoded strings.

It provides common string functions like case-insensitive *find* and *compare*, *split*, *join*, *upper*, *lower* and many more, all of which have been implemented with efficiency in mind.

Tested and working with the following compilers:
* Visual C++ 2010, 2013 and 2015 (Windows)
* clang-503 (OS X Mavericks) and clang-602 (OS X Yosemite)
* gcc

Installation
------------

### OS X

### Linux and Unix

### Windows

To follow the installation instructions you must have [cmake](www.cmake.org) installed and its folder included in the PATH environment variable.

Features
--------
* Support for the three most common unicode encodings, UTF-8 (string), UTF-16 (wstring on Windows, u16string), UTF-32 (u32string).
* Conversion between common encodings (UTF-8, UTF-16, UTF-32, iso-8859-*, cp1252 etc.).
* No third-party dependencies. The only requirements are partial support for C++11 and its standard library.

Caveats
-------
 * Limited support for decomposed characte: no conversion beteween composed and decomposed characters, and no comparisons.
 
Examples
--------

### Convert UTF-8 string to upper case

```cpp
#include <iostream>
#include <Ystring/Utf8.hpp>

int main()
{
    std::string s = u8"Köztársaság";
    std::cout << s << " -> " << Ystring::Utf8::upper(s) << "\n";
}
```

Compile and run (in a shell that uses UTF-8, e.g. Terminal under Mac OS X): 

```console
$ c++ -std=c++11 Upper.cpp -lYstring -o Upper
$ ./Upper
Köztársaság -> KÖZTÁRSASÁG
```

### Convert string to title case

```cpp
#include <iostream>
#include <Ystring/Utf8.hpp>

int main()
{
    std::cout << Ystring::Utf8::title("still pumped from using the mouse\n");
}
```

Compile and run: 

```console
$ c++ -std=c++11 Title.cpp -lYstring -o Title
$ ./Title
Still Pumped From Using The Mouse
```

### Pretty-print colon-separated paths

```cpp
#include <iostream>
#include <Ystring/Utf8.hpp>

using namespace Ystring::Utf8;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;
    std::cout << join(split(argv[1], ":"), "\n") << "\n";
}
```

Compile and run: 

```console
$ c++ -std=c++11 PrintPath.cpp -lYstring -o PrintPath
$ echo $PATH
/opt/local/bin:/opt/local/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:~/bin
$ ./PrintPath $PATH
/opt/local/bin
/opt/local/sbin
/usr/local/bin
/usr/bin
/bin
/usr/sbin
/sbin
~/bin
```


### Pretty-print semicolon-separated paths

This example demonstrates how to compile and run an example from the Windows command prompt.

```cpp
#include <iostream>
#include <Ystring/Utf8.hpp>

using namespace Ystring::Utf8;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;
    std::cout << join(split(argv[1], ";"}), "\n") << "\n";
}
```

Compile and run: 

Before I compile the example I've opened and built the projects in the Ystring solution, including the INSTALL project that has to be selected and built separately. I have then opened the folders where the include, lib and dll files were installed and copied the Ystring folder (which contains the header files that constitue the interface to Ystring), Ystring.lib and Ystring.dll to the same folder as my example file (PrintPathWin.cpp).

The first command add the Visual Studio 2010 compiler and tools to the current PATH. To use a different version of Visual Studio you just have to replace the version number with the one you want (e.g. "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" for Visual Studio 2015).

About the options to cl.exe:
* /I. Adds the current path to include dirs.
* /EHsc Compile with support for exceptions.
* /nologo Don't print Microsoft copyright message etc.
* /MD Specifies which runtime library to use (multi-threaded dll).

In a Windows command prompt:

```
D:\Temp>"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"
Setting environment for using Microsoft Visual Studio 2010 x86 tools.

D:\Temp>dir /b
PrintPathWin.cpp
Ystring
Ystring.dll
Ystring.lib

D:\Temp>cl.exe PrintPath2.cpp /I. /EHsc /nologo /MD
PrintPath2.cpp

D:\Temp>echo %PATH%
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\BIN\amd64; C:\Program Fil
es (x86)\Microsoft Visual Studio 10.0\VC\VCPackages; C:\Program Files (x86)\Micr
osoft Visual Studio 10.0\Common7\IDE; C:\Program Files (x86)\Microsoft Visual St
udio 10.0\Common7\Tools; C:\Program Files (x86)\Microsoft Visual Studio 10.0\VST
SDB\Deploy; C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\BIN; C:\Windo
ws\system32; C:\Windows; C:\Windows\System32\Wbem; C:\Windows\System32\WindowsPo
werShell\v1.0; C:\Python34; D:\Commands; C:\Program Files\TortoiseGit\bin; C:\Pr
ogram Files (x86)\CMake\bin

D:\Temp>PrintPath2.exe "%PATH%"
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\BIN\amd64
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\VCPackages
C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE
C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VSTSDB\Deploy
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\BIN
C:\Windows\system32
C:\Windows
C:\Windows\System32\Wbem
C:\Windows\System32\WindowsPowerShell\v1.0\
C:\Python34
D:\Commands
C:\Program Files\TortoiseGit\bin
C:\Program Files (x86)\CMake\bin
```
