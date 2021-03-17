# C++ MyLanguage

My Language Cpp TINY Library

> A c++ library to handle and manage all of words/strings and languages of a software in a JSON structure.

If your software is a bit international and you want to handle and manage all of strings and languages from server.

**JSON** is a good format and you can easily seperate words and strings into diffrent parts. But main problem is how to parse a complex **JSON** structure in c+ and use this.

We need to parse JSON and access to each element and value of JSON at the runtime.
In this library I did implenment some useful function to easily parse and use JSON structure and store in a `std::map`, So you can easily access to strings anywhere.

## Using

```cpp
#include "my_language.hpp"
```

## Sample program

```cpp
MyLanguage lang;
// TODO: lang.parseFile("input.json");
lang.parse();

lang.log();

std::cout << "------------------------------ [ TEST getKey ] -----------------------------\n";

std::cout << lang.getKey("exceptions", "fa_IR", "error").default_value << "\n";

std::cout << lang.getKey("exceptions", "en_US", "error").default_value << "\n";

std::cout << "------------------------------ [ TEST getKey has_error ] -----------------------------\n";

auto i = lang.getKey("exceptions", "en_US", "_bad_keyword_bad_");
if(i.has_error) {
    std::cout << "A error...\n";
}
else {
    std::cout << i.has_error << "\n";
}

std::cout << "------------------------------ [ TEST hasKey ] -----------------------------\n";

bool j = lang.hasKey("exceptions", "en_US", "_bad_keyword_bad_");
if(j == true) {
    std::cout << "No error!\n" << "\n";
}
else {
    std::cout << "A error...\n";
}

j = lang.hasKey("exceptions", "en_US", "error");
if(j == true) {
    std::cout << "No error!\n" << "\n";
}
else {
    std::cout << "A error...\n";
}

std::cout << "------------------------------ [ TEST getKey in another sheet ] -----------------------------\n";

auto k = lang.getKey("global", "fa_IR", "name");
if(k.has_error) {
    std::cout << "A error...\n";
}
else {
    std::cout << k.default_value << std::endl;
}
```

## Acknowledgment

First of all, I have to thank Mr. Asadzadeh because this library was written at his request.

I'm not good in c++ so maybe some parts are not well, In any case you can contribute or improve this one and I would accept and will merge this with love )

© Copyright Max Base
