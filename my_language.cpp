/*
 * @Name: Cpp-MyLanguage
 * @Date: 2021 March 2021
 * @Author: Max Base
 * @Repository: https://github.com/BaseMax/CPP-MyLanguage
 */

#include "my_language.hpp"

void MyLanguage::display_word(myword w) {
    std::cout << "\t\t"<<"word_key: " << w.word_key<<"\n";
    std::cout << "\t\t"<<"module: " << w.module<<"\n";
    std::cout << "\t\t"<<"default_value: " << w.default_value<<"\n";
    std::cout << "\t\t"<<"custom_value: " << w.custom_value<<"\n";
    std::cout << "\t\t"<<"status: " << w.status<<"\n";
}

std::string MyLanguage::readFile(std::string filename) {
    std::ifstream inFile;
    inFile.open("input.json");
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str = strStream.str();
    // LOG: std::cout << str << "\n";
    return str;
}

void MyLanguage::logLangs(void) {
    std::cout << "---------------- [LOG LANGS] ---------------\n";
    for (auto itr = mymap.begin(); itr != mymap.end(); ++itr) {
        std::cout << itr->first << "\n";
    }

}

void MyLanguage::logWords(void) {
    std::cout << "---------------- [LOG WORDS] ---------------\n";
    for (auto itr = mymap.begin(); itr != mymap.end(); ++itr) {
        std::cout << itr->first << "\n";
        auto childs = itr->second;
        for (auto itr = childs.begin(); itr != childs.end(); ++itr) {
            std::cout << "\t" << itr->first << "\n";
            display_word(itr->second);
        }
    }
}

void MyLanguage::log(void) {
    logLangs();
    logWords();
}

void MyLanguage::parseLangs(void) {
    for (auto t : Globalization::GET["languages"]) {
        std::string language = t["language"].get<std::string>();
        std::string code = t["code"].get<std::string>();
        bool ltr = t["ltr"];

        mylanguages[code] = {
            language,
            code,
            ltr
        };
    }
}

void MyLanguage::parseWords(void) {
    for (auto t : Globalization::GET["exceptions"].items()) {
        std::map<std::string, myword> v;
        for (auto i : t.value()) {
            // std::cout << i["word_key"].get<std::string>() << ":" << i["default_value"].get<std::string>() << std::endl;
            myword v_myword = {
                false,
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
}

/*
 * parse()
 * Arguments: void
 * std::string filename: path or filename to load JSON file. e.g: input.json
 */
void MyLanguage::parse(void) {
    // call parseLangs
    parseLangs();

    // call parseWords
    parseWords();
}

/*
 * parseFile(filename)
 * Arguments:
 * std::string filename: path or filename to load JSON file. e.g: input.json
 */
void MyLanguage::parseFile(std::string filename) {
    // TODO
    // struct Globalization {
    //  inline static JSon GET = JSon::parse(if_streamer("input.json"));
    // };

    parse();
}

/*
 * hasKey(lang, key)
 * Arguments:
 * std::string lang: code of the language structure. e.g: en_US, or fa_IR
 * std::string key: word_key of the `myword` structure. e.g: error, warning
 */
bool MyLanguage::hasKey(std::string lang, std::string key) {
    for (auto itr = mymap.begin(); itr != mymap.end(); ++itr) {
        if(itr->first != lang) {
            continue;
        }
        auto childs = itr->second;
        for (auto itr2 = childs.begin(); itr2 != childs.end(); ++itr2) {
            if(itr2->first == key) {
                return true;
            }
        }
    }

    return false;
}

/*
 * getKey(lang, key)
 * Arguments:
 * std::string lang: code of the language structure. e.g: en_US, or fa_IR
 * std::string key: word_key of the `myword` structure. e.g: error, warning
 */
MyLanguage::myword MyLanguage::getKey(std::string lang, std::string key) {
    for (auto itr = mymap.begin(); itr != mymap.end(); ++itr) {
        if(itr->first != lang) {
            continue;
        }
        auto childs = itr->second;
        for (auto itr2 = childs.begin(); itr2 != childs.end(); ++itr2) {
            if(itr2->first == key) {
                return itr2->second;
            }
        }
    }

    // TODO: use pointer and: return NULL;
    return {true};
}
