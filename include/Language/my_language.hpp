/*
 * @Name: Cpp-MyLanguage
 * @Date: 12 March 2021; 13 March 2021; 28, 29, 30 March 2021
 * @Author: Max Base
 * @Repository: https://github.com/BaseMax/CPP-MyLanguage
 */

#ifndef MY_LANGUAGE_HEADER_FILE
#define MY_LANGUAGE_HEADER_FILE

#include <iostream>
#include <fstream>
#include <map>
#include <sstream> //std::stringstream

#if __has_include ("json.hpp")
  #include "json.hpp"
#endif

namespace Core::Utility {
using JSon = nlohmann::json;
using JSonException = nlohmann::detail::exception;
using if_streamer = std::ifstream;

class Language {
  /**
   * @brief The Language private data structure
   */
  struct LanguageStruct;
  using Languages_t = std::map<std::string, LanguageStruct>;
  using Sheet_t = std::map<std::string, Languages_t>;

 public:
  /**
   * @brief Returns the file name, which is set with the setFile() function.
   * @return Returns @var `m_filename` value.
   * @see getFile()
   */
  std::string getFile() const;

  /**
  * @brief Set the input JSON file.
  * @param path or filename to load JSON file. e.g: input.json
  * @see getFile()
  */
  void setFile(const std::string& filename);

  /**
   * @brief Start parsing the JSON.
   * @see init()
   * @see parseLangs()
   * @see parseWords()
   */
  void parse();

  /**
   * @brief Just for logging.
   */
  void log() const;

  /**
   * @brief Checks for the existence of [shee][lang][key]
   * @param sheet: name of your selected sheet
   * @param lang: code of the language structure. e.g: en_US, or fa_IR
   * @param key: word_key of the `myword` structure. e.g: error, warning
   * @return Returns true in case of success.
   */
  bool hasString(const std::string& sheet, const std::string& lang, const std::string& key) const;

  /**
   * @brief Returns [sheet][lang][key] value of the JSON.
   * @param sheet: name of your selected sheet
   * @param lang: code of the language structure. e.g: en_US, or fa_IR
   * @param key: word_key of the `myword` structure. e.g: error, warning
   * @return Returns a LanguageStruct::has_error == false in case of success.
   */
  LanguageStruct getString(const std::string& sheet, const std::string& lang, const std::string& key);


 private:
  /**
   * @brief Reads all @p filename content and return it.
   * @param filename
   * @return Returns a std::string::empty() == false in case of success.
   */
  static std::string readFile(const std::string&  filename);

  /**
   * @brief Just a logging function.
   * @see log();
   */
  void logWords() const;

  /**
   * @brief Just a logging function
   * @see log();
   */
  void logLangs() const;

  /**
   * @brief Just a logging function.
   * @param w
   * @see logWords();
   */
  void displayWord(LanguageStruct const& w) const;

  /**
   * @brief Parse @var `m_filename` json
   * @return Return true in case of success.
   */
  [[nodiscard]] bool init() noexcept;

  /**
   * @brief Parse the Language section of the JSON
   */
  void parseLangs();

  /**
   * @brief /// FIXME: I don't know.
   */
  void parseWords();

 private:
  struct LanguageStruct final {
    bool ltr = false;
    std::string language;
    std::string  code;

    bool has_error = true;
    std::string word_key;
    std::string module;
    std::string default_value;
    std::string custom_value;
    // bool status;
  };
  struct JsonKeys final {
    static constexpr auto languages = "languages";
    static constexpr auto language = "language";
    static constexpr auto code = "code";
    static constexpr auto word_key = "word_key";
    static constexpr auto module = "module";
    static constexpr auto default_value = "default_value";
    static constexpr auto custom_value = "custom_value";
  };

 private:
  JSon m_parsed_json;
  LanguageStruct m_instance;

  std::string m_filename;
  Languages_t m_languages;
  std::map<std::string, Sheet_t> m_map;
};
} // namespace Core::Utility

#endif
