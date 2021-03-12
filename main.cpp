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

// std::map<std::pair<std::string, std::string>, std::map<std::string, std::string>> mymap;
// std::map<std::string, std::string> v;
// for(const auto& l : languages) {
//   for (auto t : Globalization::GET["exceptions"]) {
//     for (auto i : t["translations"]) {
//       //std::cout << i["word_key"] << ":" << i["default_value"] << std::endl;
//       std::cout << "l.second: " << l.second << std::endl;
//       v.insert(std::pair(i["word_key"], i["default_value"]));
//       mymap[std::pair(l.second ,"exceptions")] = v;
//     }
// }
// }
// for(const auto& c : mymap[std::pair("persian" ,"exceptions")]["error"]) {
// std::cout << c;
// }
// }
// std::map<std::pair<std::string, std::string>, std::map<std::string, std::string>> mymap;


typedef struct {
    std::string language;
    std::string code;
    bool ltr;
} mylanguage;
std::map<std::string, mylanguage> mylanguages;

typedef struct {
    std::string word_key;
    std::string module;
    std::string default_value;
    std::string custom_value;
    bool status;
} myword;

std::map<std::string, std::map<std::string, myword>> mymap;


void display_word(myword w) {
    std::cout << "\t\t"<<"word_key: " << w.word_key<<"\n";
    std::cout << "\t\t"<<"module: " << w.module<<"\n";
    std::cout << "\t\t"<<"default_value: " << w.default_value<<"\n";
    std::cout << "\t\t"<<"custom_value: " << w.custom_value<<"\n";
    std::cout << "\t\t"<<"status: " << w.status<<"\n";
}

void log() {
    std::cout << "---------------- [LOG] ---------------\n";
    for (auto itr = mymap.begin(); itr != mymap.end(); ++itr) {
        std::cout << itr->first << "\n";
        auto childs = itr->second;
        for (auto itr = childs.begin(); itr != childs.end(); ++itr) {
            std::cout << "\t" << itr->first << "\n";
            display_word(itr->second);
        }
    }
}

int main(int argc, const char * argv[]) {

    for (auto t : Globalization::GET["languages"]) {
        std::string language = t["language"].get<std::string>();
        std::string code = t["code"].get<std::string>();
        bool ltr = t["ltr"];

        std::cout << "============\n";
        std::cout << language << "," << code << "," << ltr <<"\n";

        mylanguages[code] = {
            language,
            code,
            ltr
        };
    }

    for (auto t : Globalization::GET["exceptions"].items()) {
        std::map<std::string, myword> v;
        std::cout << t.key() << "\n";
        for (auto i : t.value()) {
            // std::cout << i["word_key"].get<std::string>() << ":" << i["default_value"].get<std::string>() << std::endl;
            myword v_myword = {
                i["word_key"].get<std::string>(),
                i["module"].get<std::string>(),
                i["default_value"].get<std::string>(),
                i["custom_value"].get<std::string>(),
                i["status"],
            };
            v.insert(
                std::pair<std::string, myword>(
                    i["word_key"].get<std::string>(),
                    v_myword
                )
            );
        }
        mymap[t.key()] = v;
    }


    log();

    return 0;
}
