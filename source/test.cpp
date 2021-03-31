#include <filesystem>

#include "Language/my_language.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Input and Output Test", "[JSON Reading]") {
  Core::Utility::Language lang;
  lang.setFile(std::filesystem::current_path() / "../test/input.json");
  lang.parse();

  //  REQUIRE(lang.getString("exceptions", "fa_IR", "error").default_value ==
  //          "{\"code\":\"en_US\",\"language\":\"english\",\"ltr\":true,\"status\":true}");
  //  REQUIRE(lang.getString("exceptions", "en_US", "error").default_value ==
  //          "{\"code\":\"fa_IR\",\"language\": \"persian\",\"ltr\":false,\"status\":true}");

  //  REQUIRE(lang.getString("exceptions", "en_US", "_bad_keyword_bad_").has_error);
  //  REQUIRE(lang.getString("global", "fa_IR", "name").has_error);
  //  REQUIRE_FALSE(lang.hasString("exceptions", "en_US", "_bad_keyword_bad_"));
  //  REQUIRE_FALSE(lang.hasString("exceptions", "en_US", "error"));
}
