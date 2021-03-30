/*
 * @Name: Cpp-MyLanguage
 * @Date: 12 March 2021; 13 March 2021; 28, 29, 30 March 2021
 * @Author: Max Base
 * @Repository: https://github.com/BaseMax/CPP-MyLanguage
 */

#include "my_language.hpp"

namespace Core::Utility {
bool Language::init() noexcept {
  bool res = true;
  try {
    m_parsed_json = JSon::parse(if_streamer(getFile()));
  } catch (JSonException& e) {
    std::clog << "Error Message : " << e.what() << "\n";
    res = false;
  }
  return res;
}

std::string Language::getFile() const { return m_filename; }

void Language::setFile(const std::string& filename) { m_filename = filename; }

void Language::displayWord(const LanguageStruct& w) const {
  std::cout << "\t\t\t" << "word_key: " << w.word_key << "\n";
  std::cout << "\t\t\t" << "module: " << w.module << "\n";
  std::cout << "\t\t\t" << "default_value: " << w.default_value << "\n";
  std::cout << "\t\t\t" << "custom_value: " << w.custom_value << "\n";
}

std::string Language::readFile(const std::string& filename) {
  std::ifstream inFile;
  inFile.open(filename);
  std::stringstream strStream;
  strStream << inFile.rdbuf();
  std::string str = strStream.str();
  return str;
}

void Language::logLangs() const {
  std::cout << "---------------- [LOG LANGS] ---------------\n";
  for (auto const& sheet : m_map) {
    std::cout << sheet.first << ":\n";

    for (auto const& itr : sheet.second) {
      std::cout << "\t" << itr.first << "\n";
    }
  }
}

void Language::logWords() const {
  std::cout << "---------------- [LOG WORDS] ---------------\n";
  for (auto const& sheet : m_map) {
    std::cout << sheet.first << ":\n";

    for (auto const& itr : sheet.second) {
      std::cout << "\t" << itr.first << "\n";

      for (auto const& child : itr.second) {
        std::cout << "\t\t" << itr.first << "\n";
        displayWord(child.second);
      }
    }
  }
}

void Language::log() const {
  logLangs();
  logWords();
}

void Language::parseLangs() {
  for (const auto& t : m_parsed_json["languages"]) {
    std::cout << t << "\n";
    std::string language_t = t["language"].get<std::string>();
    std::string code_t = t["code"].get<std::string>();

    /// FIXME: What is usage of language_t and code_t?
  }
}

void Language::parseWords() {
  try {
    Sheet_t mysheet;

    auto items = m_parsed_json.at("languages").at("languages").items();
    for (auto const& item : items) {
      Languages_t newItem;

      for (auto const& i : item.value()) {
        LanguageStruct v_myword = {
          .ltr = false,
          .language = std::string(),
          .code = std::string(),
          .word_key = i["word_key"].get<std::string>(),
          .module = i["module"].get<std::string>(),
          .default_value = i["default_value"].get<std::string>(),
          .custom_value = i["custom_value"].get<std::string>(),
        };
        newItem.insert(std::pair<std::string, LanguageStruct>(i["word_key"].get<std::string>(), v_myword));
      }
      mysheet[item.key()] = std::move(newItem);
    }
    m_map["languages"] = std::move(mysheet);

  } catch (...) {
    /// FIXME: Handle error if needed.
  }
}

void Language::parse() {
  if (init()) {
    parseLangs();
    parseWords();
  } else {
    std::clog << "Error on parsing!\n";
  }
}

bool Language::hasString(const std::string& sheet, const std::string& lang, const std::string& key) const {
  try {
    auto const __lang = m_map.at(sheet).at(lang);
    return __lang.find(key) != std::cend(__lang);
  } catch (...) {
    return false;
  }
}

Language::LanguageStruct Language::getString(const std::string& sheet, const std::string& lang, const std::string& key) {
  try {
    return m_map.at(sheet).at(lang).at(key);
  } catch (...) {
    return m_instance;
  }
}
} // namespace Core::Utility
