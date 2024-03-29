# C++ MyLanguage

My Language Cpp TINY Library

> A c++ library to handle and manage all of words/strings and languages of a software in a JSON structure.

If your software is a bit international and you want to handle and manage all of strings and languages from server.

**JSON** is a good format and you can easily seperate words and strings into diffrent parts. But main problem is how to parse a complex **JSON** structure in c++ and use this.

We need to parse JSON and access to each element and value of JSON at the runtime.
In this library I did implenment some useful function to easily parse and use JSON structure and store in a `std::map`, So you can easily access to strings anywhere.

You can check the [input.json](input.json) file to better understand how the library works.

## Purpose of library 

Did you translate words to different languages? Do your software support multi language and you want to handle languages without suffering.

So you can try or improve this library for your use.

## How To Build

Thanks to CMake, it's simple:

```
$ mkdir build;
$ cd build;
$ cmake ..; make -j`nproc`
```

After a successful build, you have:
1. The static build: `output/lib`
2. The shared build: `output/lib`
3. The binary build: `output/bin`
4. The header files: `output/lib/include`  

Let me know if it's not enough for you.

## Example

```cpp
#include "my_language.hpp"

Language lang;
lang.setFile("input.json");
lang.parse();

lang.log();

std::cout << "------------------------------ [ TEST getString ] -----------------------------\n";

std::cout << lang.getString("exceptions", "fa_IR", "error")->default_value() << "\n";

std::cout << lang.getString("exceptions", "en_US", "error")->default_value() << "\n";



std::cout << "------------------------------ [ TEST getString has_error ] -----------------------------\n";

auto i = lang.getString("exceptions", "en_US", "_bad_keyword_bad_");
std::cout << "...\n";
if(i->has_error()) {
    std::cout << "A error...\n";
}
else {
    std::cout << i->has_error() << "\n";
}


std::cout << "------------------------------ [ TEST hasString ] -----------------------------\n";

bool j = lang.hasString("exceptions", "en_US", "_bad_keyword_bad_");
if(j == true) {
    std::cout << "No error!\n";
}
else {
    std::cout << "A error...\n";
}

j = lang.hasString("exceptions", "en_US", "error");
if(j == true) {
    std::cout << "No error!\n";
}
else {
    std::cout << "A error...\n";
}


std::cout << "------------------------------ [ TEST getString in another sheet ] -----------------------------\n";

auto k = lang.getString("global", "fa_IR", "name");
if(k->has_error()) {
    std::cout << "A error...\n";
}
else {
    std::cout << k->default_value() << std::endl;
}
```

## Acknowledgment

Thank a lots from Mr. Ghasem Ramezani Manesh for his review and improving this library.

I'm not good in c++ so maybe some parts are not well, In any case you can contribute or improve this one and I would accept and will merge this with love )

© Copyright Max Base
