#include <iostream>
#include "my_language.hpp"

int main(int argc, const char * argv[]) {

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

    return 0;
}
