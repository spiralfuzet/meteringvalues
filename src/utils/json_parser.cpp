#include "utils/json_parser.h"

#include <fmt/format.h>

namespace supercharge::meteringvalues::utils {

Json::Value JsonParser::parse(std::istream& json_stream) {
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, json_stream, &root, &errs))  {
        throw std::runtime_error(fmt::format("Read file error: {}", errs));
    }
    return root;
}

} // namespace namespace supercharge::meteringvalues::utils
