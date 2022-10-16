#include "utils/string_utils.h"

namespace supercharge::meteringvalues::utils {

std::string StringUtils::replace(const std::string& input, const std::string& substr, const std::string& replacement) {
    std::string result(input);
    size_t pos = 0;
    while((pos = result.find(substr, pos)) != std::string::npos) {
        result.replace(pos, substr.length(), replacement);
        pos += replacement.length();
    }
    return result;
}

std::vector<std::string> StringUtils::tokenize(const std::string& input, const char delimiter) {
    std::vector<std::string> tokens;
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = input.find(delimiter, prev)) != std::string::npos) {
        tokens.push_back(input.substr(prev, pos - prev));
        prev = pos + 1;
    }
    tokens.push_back(input.substr(prev));
 
    return tokens;
}

} // namespace supercharge::meteringvalues::utils
