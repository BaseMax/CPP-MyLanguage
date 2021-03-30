/*
 * @Name: Cpp-MyLanguage
 * @Date: 12 March 2021; 13 March 2021; 28, 29, 30 March 2021
 * @Author: Max Base
 * @Repository: https://github.com/BaseMax/CPP-MyLanguage
 */

#include <iostream>
#include <fstream>
#include <map>
#include <sstream> //std::stringstream

#include "json/json.hpp"

using JSon = nlohmann::json;

using if_streamer = std::ifstream;

struct Globalization {
  inline static JSon GET = JSon::parse(if_streamer("/Users/compez/drogon/build/Tegra/translations/contents2.json"));
};

class LanguageStruct {
public:

  static std::shared_ptr<LanguageStruct> getInstance;
  //static LanguageStruct* getInstance;

  void deleteInstance();

  LanguageStruct(
      bool ltr,
      const std::string& word_key,
      const std::string& module,
      const std::string& default_value ,
      const std::string& custom_value,
      bool status);
public:
  std::string language() const;
  std::string code() const;
  bool ltr() const;
  bool has_error() const;
  std::string word_key() const;
  std::string module() const;
  std::string default_value() const;
  std::string custom_value() const;
  bool status() const;

private:

  static LanguageStruct* m_instance;

  bool m_ltr = false;
  std::string m_language;
  std::string  m_code;

  bool m_has_error;
  std::string m_word_key;
  std::string m_module;
  std::string m_default_value;
  std::string m_custom_value;
  bool m_status;

};

class Language {
public:
  Language();
  ~Language();

public:
  void parse();
  void parseLangs();
  void parseWords();

  void parseFile(const std::string&  filename);
  void displayWord(LanguageStruct w);

  void log();
  void logLangs();
  void logWords();


  bool hasKey(const std::string& sheet, const std::string& lang, const std::string& key);

  LanguageStruct getString(const std::string& sheet, const std::string& lang, const std::string& key);

  std::string readFile(const std::string&  filename);

private:
  std::map<std::string, LanguageStruct> m_languages;
  std::map<std::string, std::map<std::string, std::map<std::string, LanguageStruct>>> m_map;
  //std::shared_ptr<std::map<std::string, std::map<std::string, std::map<std::string, LanguageStruct>>>> m_map;

};

