/*
 * @Name: Cpp-MyLanguage
 * @Date: 2021 March 2021
 * @Author: Max Base
 * @Repository: https://github.com/BaseMax/CPP-MyLanguage
 */

#include <iostream>
#include <fstream>
#include <map>
#include <sstream> //std::stringstream

#include "json.hpp"

using JSon = nlohmann::json;

using if_streamer = std::ifstream;

struct Globalization {
  inline static JSon GET = JSon::parse(if_streamer("input.json"));
};

class MyLanguage {

    typedef struct {
        std::string language;
        std::string code;
        bool ltr;
    } mylanguage;

    typedef struct {
        bool has_error;
        std::string word_key;
        std::string module;
        std::string default_value;
        std::string custom_value;
        bool status;
    } myword;

    public:
        void parse(void);
        void parseLangs(void);
        void parseWords(void);

        void parseFile(std::string filename);
        void display_word(myword w);

        void log(void);
        void logLangs(void);
        void logWords(void);


        bool hasKey(std::string lang, std::string key);
        myword getKey(std::string lang, std::string key);

        std::string readFile(std::string filename);

    private:
        std::map<std::string, mylanguage> mylanguages;
        std::map<std::string, std::map<std::string, myword>> mymap;
};

