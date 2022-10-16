#pragma once

#include <string>
#include <vector>

namespace supercharge::meteringvalues::utils {

struct StringUtils {

    StringUtils() = delete;

    static std::string replace(const std::string& input, const std::string& substr, const std::string& replacement);
    static std::vector<std::string> tokenize(const std::string& input, const char delimiter);

};

} // namespace supercharge::meteringvalues::utils
