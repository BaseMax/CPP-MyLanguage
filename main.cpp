#include <iostream>
#include "my_language.hpp"

int main() {
  Language lang;
  lang.setFile("input.json");
  lang.parse();
  lang.log();

  std::cout << "------------------------------ [ TEST getString ] -----------------------------\n";

  std::cout << lang.getString("exceptions", "fa_IR", "error").default_value() << "\n";
  std::cout << lang.getString("exceptions", "en_US", "error").default_value() << "\n";

  std::cout << "------------------------------ [ TEST getString has_error ] -----------------------------\n";

  auto const i = lang.getString("exceptions", "en_US", "_bad_keyword_bad_");
  std::cout << "...\n";
  if (i.has_error()) {
    std::cout << "A error...\n";
  } else {
    std::cout << i.has_error() << "\n";
  }


  std::cout << "------------------------------ [ TEST hasString ] -----------------------------\n";

  bool j = lang.hasString("exceptions", "en_US", "_bad_keyword_bad_");
  if (j == true) {
    std::cout << "No error!\n";
  } else {
    std::cout << "A error...\n";
  }

  j = lang.hasString("exceptions", "en_US", "error");
  if (j == true) {
    std::cout << "No error!\n";
  } else {
    std::cout << "A error...\n";
  }


  std::cout << "------------------------------ [ TEST getString in another sheet ] -----------------------------\n";
  auto const k = lang.getString("global", "fa_IR", "name");
  if (k.has_error()) {
    std::cout << "A error...\n";
  } else {
    std::cout << k.default_value() << std::endl;
  }

  return 0;
}
