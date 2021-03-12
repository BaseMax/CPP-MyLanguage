#include <iostream>
#include <fstream>
#include <map>
#include <sstream> //std::stringstream

#include "json.hpp"

using JSon = nlohmann::json;

using if_streamer    = std::ifstream;

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
	    std::string word_key;
	    std::string module;
	    std::string default_value;
	    std::string custom_value;
	    bool status;
	} myword;

	public:
		void parse();
		void parseFile(std::string filename);
		void display_word(myword w);

		void log();
		void MyLanguage::logLangs();
		void MyLanguage::logWords();

		std::string MyLanguage::getKey(std::string lang, std::string key);

		std::string readFile(std::string filename);

	private:
		std::map<std::string, mylanguage> mylanguages;
		std::map<std::string, std::map<std::string, myword>> mymap;
};

