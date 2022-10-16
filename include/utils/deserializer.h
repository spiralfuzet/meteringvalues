#pragma once

#include "utils/json_parser.h"
#include "utils/string_utils.h"

#include <fmt/format.h>
#include <magic_enum.hpp>

#include <fstream>
#include <filesystem>

namespace supercharge::meteringvalues::utils {

template <typename T>
struct ValueDeserializer {
    T deserialize(const Json::Value& value);
};

template<typename T, typename = void>
struct EnumDeserializer {

    EnumDeserializer() = delete;

    static T deserialize(const Json::Value& value);

    static T deserialize(const Json::Value& value, const std::string& key);
};

template<typename T>
struct EnumDeserializer<T, typename std::enable_if_t<std::is_enum_v<T>>> {

    static T deserialize(const Json::Value& value) {
        const auto as_string = value.asString();
        const auto normalized_str =  StringUtils::replace(
            StringUtils::replace(as_string, ".", ""), "-", "");
        const auto maybe_as_enum = magic_enum::enum_cast<T>(normalized_str);
        if (!maybe_as_enum.has_value()) {
            throw std::runtime_error(fmt::format("Value: '{}' is not recognized as the given enum", as_string));
        }
        return maybe_as_enum.value();
    }

    static T deserialize(const Json::Value& value, const std::string& key) {
        if (!value.isMember(key)) {
            throw std::runtime_error(fmt::format("No enum value under key: '{}'", key));
        }
        return deserialize(value[key]);
    }
};

template<typename T>
struct Deserializer {

    T deserialize(const std::filesystem::path &json_file) const {
        if (!std::filesystem::is_regular_file(json_file)) {
            throw std::runtime_error(fmt::format("Provided file {} is not a regular file.", json_file.string()));
        }
        std::ifstream ifs{json_file.string()};
        const auto parsed = JsonParser::parse(ifs);
        ValueDeserializer<T> deserializer;
        return deserializer.deserialize(parsed);
    }
};

} // namespace supercharge::meteringvalues::utils
