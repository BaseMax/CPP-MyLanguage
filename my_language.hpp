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
using JSonException = nlohmann::detail::exception;

using if_streamer = std::ifstream;

//class Globalization {
//public:
//  Globalization() {

//  }
//  ~Globalization() {

//  }
//  static JSon parse() {
//    JSon j;
//    try {
//      j = JSon::parse(if_streamer(getFile()));
//    } catch (JSon::exception& e) {
//      std::clog << e.what() << "\n";
//    }
//    return j;
//  }

//  inline static JSon GET = parse();

//  inline static std::string getFile() noexcept {
//    return m_filename;
//  }

//  void setFile(const std::string& filename) {
//    if(m_filename != filename || m_filename.empty()) {
//      m_filename = filename;
//    }
//  }

//private:
//  inline static std::string m_filename;


//};

class LanguageStruct {
public:

  static std::unique_ptr<LanguageStruct> getInstance;

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

  JSon GET;

  [[nodiscard]] bool init() noexcept {
    bool res = {false};
    try {
      GET = JSon::parse(if_streamer(getFile()));
      res = true;
    } catch (JSonException& e) {
      std::clog << "Error Message : " << e.what() << "\n";
      res = false;
    }
    return res;
  }

  std::string getFile() {
    return m_filename;
  }

  void setFile(const std::string& filename) {
    if(m_filename != filename || m_filename.empty()) {
      m_filename = filename;
    }
  }

public:
  void parse();
  void parseLangs();
  void parseWords();

  void parseFile(const std::string& filename);
  void displayWord(LanguageStruct w);

  void log();
  void logLangs();
  void logWords();

  bool hasString(const std::string& sheet, const std::string& lang, const std::string& key);

  LanguageStruct getString(const std::string& sheet, const std::string& lang, const std::string& key);

  std::string readFile(const std::string&  filename);

private:
  std::string m_filename;
  std::map<std::string, LanguageStruct> m_languages;
  std::map<std::string, std::map<std::string, std::map<std::string, LanguageStruct>>> m_map;
};

