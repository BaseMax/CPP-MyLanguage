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

std::string Language::getFile() const {
  return m_filename;
}

void Language::setFile(const std::string& filename) {
  m_filename = filename;
}

void Language::displayWord(const LanguageStruct& w) {
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

void Language::logLangs() {
  std::cout << "---------------- [LOG LANGS] ---------------\n";
  for (auto s = m_map.begin(); s != m_map.end(); ++s) {
    std::cout << s->first << ":\n";
    for (auto itr = s->second.begin(); itr != s->second.end(); ++itr) {
      std::cout << "\t" << itr->first << "\n";
    }
  }

}

void Language::logWords() {
  std::cout << "---------------- [LOG WORDS] ---------------\n";
  for (auto s = m_map.begin(); s != m_map.end(); ++s) {
    std::cout << s->first << ":\n";
    for (auto itr = s->second.begin(); itr != s->second.end(); ++itr) {
      std::cout << "\t" << itr->first << "\n";
      auto childs = itr->second;
      for (auto itr = childs.begin(); itr != childs.end(); ++itr) {
        std::cout << "\t\t" << itr->first << "\n";
        displayWord(itr->second);
      }
    }
  }
}

void Language::log() {
  logLangs();
  logWords();
}

void Language::parseLangs() {
  for (const auto& t : m_parsed_json["languages"]) {
    std::cout << t << "\n";
    std::string language_t = t["language"].get<std::string>();
    std::string code_t = t["code"].get<std::string>();
  }
}

void Language::parseWords() {
  auto items = m_parsed_json.items();
  for (const auto& [key, value] : items) {
    std::map<std::string, std::map<std::string, LanguageStruct>> mysheet;
    if (key == "languages") {
      continue;
    }
    for (auto t : m_parsed_json[ key ].items()) {
      std::map<std::string, LanguageStruct> v;
      for (auto i : t.value()) {
        LanguageStruct v_myword = {
          .ltr = false,
          .language = std::string(),
          .code = std::string(),
          .word_key = i["word_key"].get<std::string>(),
          .module = i["module"].get<std::string>(),
          .default_value = i["default_value"].get<std::string>(),
          .custom_value = i["custom_value"].get<std::string>(),
        };
        v.insert(std::pair<std::string, LanguageStruct>(i["word_key"].get<std::string>(), v_myword));
      }
      mysheet[t.key()] = v;
    }
    m_map[key] = mysheet;
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

bool Language::hasString(const std::string& sheet, const std::string& lang, const std::string& key) {
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
