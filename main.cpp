#include <iostream>
#include "my_language.hpp"

int main(int argc, const char * argv[]) {

    MyLanguage lang;
    // TODO: lang.parseFile("input.json");
    lang.parse();
    lang.log();

    return 0;
}
