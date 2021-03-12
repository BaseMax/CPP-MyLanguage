#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream

#include "json.hpp"

using JSon = nlohmann::json;

using if_streamer    = std::ifstream;

struct Globalization {
  inline static JSon GET = JSon::parse(if_streamer("input.json"));
};

int main(int argc, const char * argv[]) {
    std::ifstream inFile;
    inFile.open("input.json");
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str = strStream.str();
    // std::cout << str << "\n";

    for (auto t : Globalization::GET["exceptions"]) {
        std::cout << "============\n";
        std::cout << t["language"]<<",";
        std::cout << t["code"]<<",";
        std::cout << t["ltr"]<<"\n";
        for (auto i : t["translations"]) {
            std::cout << i["word_key"] << ":" << i["default_value"] << std::endl;
        }
    }

    return 0;
}
