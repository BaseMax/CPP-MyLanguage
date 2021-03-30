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
  LanguageStruct();
  LanguageStruct(
      bool ltr,
      const std::string& word_key,
      const std::string& module,
      const std::string& default_value,
      const std::string& custom_value
      // ,
      // bool status
  );

  inline static std::unique_ptr<LanguageStruct> getInstance;
  void deleteInstance();

  std::string language() const;
  std::string code() const;
  bool ltr() const;
  bool has_error() const;
  std::string word_key() const;
  std::string module() const;
  std::string default_value() const;
  std::string custom_value() const;
  // bool status() const;

 private:
  bool m_ltr;
  std::string m_language;
  std::string  m_code;

  bool m_has_error;
  std::string m_word_key;
  std::string m_module;
  std::string m_default_value;
  std::string m_custom_value;
  // bool m_status;

};

class Language {
 public:
  JSon GET;

  [[nodiscard]] bool init() noexcept;

  std::string getFile() const;

  /**
  * @brief Set the input JSON file.
  * @param path or filename to load JSON file. e.g: input.json
  */
  void setFile(const std::string& filename);

  void parse();
  void parseLangs();
  void parseWords();
  void displayWord(LanguageStruct const& w);
  void log();
  void logLangs();
  void logWords();
  bool hasString(const std::string& sheet, const std::string& lang, const std::string& key);

  LanguageStruct getString(const std::string& sheet, const std::string& lang, const std::string& key);
  // LanguageStruct getString(const std::string& sheet, const std::string& lang, const std::string& key);

  std::string readFile(const std::string&  filename);

 private:
  // static LanguageStruct* m_instance;
  LanguageStruct m_instance;

  std::string m_filename;
  std::map<std::string, LanguageStruct> m_languages;
  std::map<std::string, std::map<std::string, std::map<std::string, LanguageStruct>>> m_map;
};

