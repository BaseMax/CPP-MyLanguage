/*
 * @Name: Cpp-MyLanguage
 * @Date: 12 March 2021; 13 March 2021; 28, 29, 30 March 2021
 * @Author: Max Base
 * @Repository: https://github.com/BaseMax/CPP-MyLanguage
 */

#include "my_language.hpp"

//LanguageStruct *LanguageStruct::getInstance()
//{
//  return this;
//}

std::shared_ptr<LanguageStruct> LanguageStruct::getInstance;

LanguageStruct::LanguageStruct(bool ltr,
                               const std::string& word_key,
                               const std::string& module,
                               const std::string& default_value ,
                               const std::string& custom_value,
                               bool status) :
                                              m_ltr(ltr),
                                              m_word_key(word_key),
                                              m_module(module),
                                              m_default_value(default_value),
                                              m_custom_value(custom_value),
                                              m_status(status)

{

}

Language::Language() {

}


Language::~Language() {

}

bool LanguageStruct::ltr() const {
  return m_ltr;
}

std::string LanguageStruct::language() const {
  return m_language;
}

std::string LanguageStruct::code() const {
  return m_code;
}

bool LanguageStruct::has_error() const {
  return m_has_error;
}

std::string LanguageStruct::word_key() const {
  return m_word_key;
}

std::string LanguageStruct::module() const {
  return m_module;
}

std::string LanguageStruct::default_value() const {
  return m_default_value;
}

std::string LanguageStruct::custom_value() const {
  return m_custom_value;
}

bool LanguageStruct::status() const {
  return m_status;
}

void Language::displayWord(LanguageStruct w) {
  std::cout << "\t\t\t"<<"word_key: " << w.word_key() <<"\n";
  std::cout << "\t\t\t"<<"module: " << w.module() <<"\n";
  std::cout << "\t\t\t"<<"default_value: " << w.default_value() <<"\n";
  std::cout << "\t\t\t"<<"custom_value: " << w.custom_value() <<"\n";
  std::cout << "\t\t\t"<<"status: " << w.status() <<"\n";
}

std::string Language::readFile(const std::string& filename) {
  std::ifstream inFile;
  inFile.open("input.json");
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
      std::cout << "\t"<<itr->first << "\n";
      auto childs = itr->second;
      for (auto itr = childs.begin(); itr != childs.end(); ++itr) {
        std::cout << "\t\t" << itr->first << "\n";
        displayWord(itr->second);
      }
    }
  }
}

void Language::log() {
  std::cout << "log\n";
  logLangs();
  logWords();
}

void Language::parseLangs() {
  std::cout << "parseLangs\n";
  for (const auto& t : Globalization::GET["languages"]) {
    std::cout << t << "\n";
    //     {"code":"en_US","language":"english","ltr":true}
    //     {"code":"fa_IR","language":"persian","ltr":false}

    std::string language_t = t["language"].get<std::string>();
    std::string code_t = t["code"].get<std::string>();
    bool ltr_t = t["ltr"].get<bool>();

    //            m_languages[code] = {
    //                false,"","","","",false
    //            };
  }
}

    void Language::parseWords() {
  // std::cout << "parseWords\n";
  auto items = Globalization::GET.items();
  for (const auto& [key, value] : items) {
    // key values are: exceptions, global, languages, ...
    // std::cout << "\n\n----------------------\n";
    // std::cout << key << " : " << value << "\n";
    std::map<std::string, std::map<std::string, LanguageStruct>> mysheet;
    if(key == "languages") {
      // solved bug: terminate called after throwing an instance of 'nlohmann::detail::type_error' what():  [json.exception.type_error.305] cannot use operator[] with a string argument with string
      continue;
      }
    for (auto t : Globalization::GET[ key ].items()) {
      // std::cout << t << "\n";
      std::map<std::string, LanguageStruct> v;
      for (auto i : t.value()) {
        // std::cout << "\nin loop\n";
        // std::cout << i << "\n";
        // std::cout << i["word_key"].get<std::string>() << ":" << i["default_value"].get<std::string>() << std::endl;
        LanguageStruct v_myword = {
            false,
            i["word_key"].get<std::string>(),
            i["module"].get<std::string>(),
            i["default_value"].get<std::string>(),
            i["custom_value"].get<std::string>(),
            i["status"],
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
void Language::parseFile(const std::string&  filename) {
  // TODO
  // struct Globalization {
  //  inline static JSon GET = JSon::parse(if_streamer("input.json"));
  // };

  parse();
}

/*
 * hasKey(lang, key)
 * Arguments:
 * std::string sheet: name of your selected sheet
 * std::string lang: code of the language structure. e.g: en_US, or fa_IR
 * std::string key: word_key of the `myword` structure. e.g: error, warning
 */
bool Language::hasKey(const std::string& sheet, const std::string& lang, const std::string& key) {
  for (auto s = m_map.begin(); s != m_map.end(); ++s) {
    if(s->first != sheet) {
      continue;
    }
    for (auto itr = s->second.begin(); itr != s->second.end(); ++itr) {
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
  }

  return false;
}

/*
 * getKey(lang, key)
 * Arguments:
 * std::string sheet: name of your selected sheet
 * std::string lang: code of the language structure. e.g: en_US, or fa_IR
 * std::string key: word_key of the `myword` structure. e.g: error, warning
 */
LanguageStruct Language::getString(const std::string& sheet, const std::string& lang, const std::string& key) {
  for (auto s = m_map.begin(); s != m_map.end(); ++s) {
    if(s->first != sheet) {
      continue;
    }
    for (auto itr = s->second.begin(); itr != s->second.end(); ++itr) {
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
  }

  return *LanguageStruct::getInstance;
  //return {false,"","","","",false};
}
