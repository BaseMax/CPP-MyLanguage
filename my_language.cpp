/*
 * @Name: Cpp-MyLanguage
 * @Date: 12 March 2021; 13 March 2021; 28, 29, 30 March 2021
 * @Author: Max Base
 * @Repository: https://github.com/BaseMax/CPP-MyLanguage
 */

#include "my_language.hpp"

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
  // std::cout << "\t\t\t"<<"status: " << w.status() <<"\n";
}

std::string Language::readFile(const std::string& filename) {
  std::ifstream inFile;
  inFile.open(filename);
  std::stringstream strStream;
  strStream << inFile.rdbuf();
  std::string str = strStream.str();
  // LOG: std::cout << str << "\n";
  return str;
}

void Language::logLangs() {
  // std::cout << "logLangs\n";
  std::cout << "---------------- [LOG LANGS] ---------------\n";
  for (auto s = m_map.begin(); s != m_map.end(); ++s) {
    std::cout << s->first << ":\n";
    for (auto itr = s->second.begin(); itr != s->second.end(); ++itr) {
      std::cout << "\t" << itr->first << "\n";
    }
  }

}

void Language::logWords() {
  // std::cout << "logWords\n";
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
    //     {"code":"en_US","language":"english","ltr":true}
    //     {"code":"fa_IR","language":"persian","ltr":false}

    std::string language_t = t["language"].get<std::string>();
    std::string code_t = t["code"].get<std::string>();
    //    bool ltr_t = t["ltr"].get<bool>();

    //            m_languages[code] = {
    //                false,"","","","",false
    //            };
  }
}

void Language::parseWords() {
  // std::cout << "parseWords\n";
  auto items = m_parsed_json.items();
  for (const auto& [key, value] : items) {
    // key values are: exceptions, global, languages, ...
    // std::cout << "\n\n----------------------\n";
    // std::cout << key << " : " << value << "\n";
    std::map<std::string, std::map<std::string, LanguageStruct>> mysheet;
    if (key == "languages") {
      // solved bug: terminate called after throwing an instance of 'nlohmann::detail::type_error' what():  [json.exception.type_error.305] cannot use operator[] with a string argument with string
      continue;
    }
    for (auto t : m_parsed_json[ key ].items()) {
      // std::cout << t << "\n";
      std::map<std::string, LanguageStruct> v;
      for (auto i : t.value()) {
        // std::cout << "\nin loop\n";
        // std::cout << i << "\n";
        // std::cout << i["word_key"].get<std::string>() << ":" << i["default_value"].get<std::string>() << std::endl;
        LanguageStruct v_myword = {
          .ltr = false,
          .language = std::string(),
          .code = std::string(),
          .word_key = i["word_key"].get<std::string>(),
          .module = i["module"].get<std::string>(),
          .default_value = i["default_value"].get<std::string>(),
          .custom_value = i["custom_value"].get<std::string>(),
          // i["status"],
        };
        v.insert(std::pair<std::string, LanguageStruct>(i["word_key"].get<std::string>(), v_myword));
      }
      mysheet[t.key()] = v;
    }
    m_map[key] = mysheet;
  }
}

/*
 * parse()
 * Arguments: void
 * std::string filename: path or filename to load JSON file. e.g: input.json
 */
void Language::parse() {

  if (init()) {
    // call parseLangs
    parseLangs();

    // call parseWords
    parseWords();
  } else {
    std::clog << "Error on parsing!\n";
  }
}

/*
 * hasString(sheet, lang, key)
 * Arguments:
 * std::string sheet: name of your selected sheet
 * std::string lang: code of the language structure. e.g: en_US, or fa_IR
 * std::string key: word_key of the `myword` structure. e.g: error, warning
 */
bool Language::hasString(const std::string& sheet, const std::string& lang, const std::string& key) {
  try {
    auto const __lang = m_map.at(sheet).at(lang);
    return __lang.find(key) != std::cend(__lang);
  } catch (...) {
    return false;
  }
}

/*
 * getString(sheet, lang, key)
 * Arguments:
 * std::string sheet: name of your selected sheet
 * std::string lang: code of the language structure. e.g: en_US, or fa_IR
 * std::string key: word_key of the `myword` structure. e.g: error, warning
 */
Language::LanguageStruct Language::getString(const std::string& sheet, const std::string& lang, const std::string& key) {
  try {
    return m_map.at(sheet).at(lang).at(key);
  } catch (...) {
    return m_instance;
  }

  // return std::shared_ptr<LanguageStruct>();
  // return std::shared_ptr<LanguageStruct>(m_instance);
  // return std::make_shared<LanguageStruct>(nullptr);
  // return m_instance;
  // return std::make_shared<LanguageStruct>(LanguageStruct::getInstance);

  // return NULL;

  // return LanguageStruct::getInstance;
  // return *LanguageStruct::getInstance;

  // return {false,"","","","",false};
  // return {};
}
