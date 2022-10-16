#include "utils/string_utils.h"

#include "catch.hpp"

using namespace supercharge::meteringvalues::utils;

TEST_CASE("StringUtils::replace replaces every occurrence of search string and keeps the input unchanged") {

    std::string input_string = "He who controls the spice controls the universe.";
    std::string result = StringUtils::replace(input_string, " ", "//");
    REQUIRE(input_string == "He who controls the spice controls the universe.");
    REQUIRE(result == "He//who//controls//the//spice//controls//the//universe.");
}

TEST_CASE("StringUtils::tokenize splits string by delimiter character") {

    std::string input_string = "Hope clouds observation";
    const auto tokens = StringUtils::tokenize(input_string, ' ');
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == "Hope");
    REQUIRE(tokens[1] == "clouds");
    REQUIRE(tokens[2] == "observation");
}
