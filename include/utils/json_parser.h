#pragma once

#include <json/json.h>

#include <istream>

namespace supercharge::meteringvalues::utils {

struct JsonParser {

    JsonParser() = delete;

    static Json::Value parse(std::istream& json_stream);
};

} // namespace namespace supercharge::meteringvalues::utils
