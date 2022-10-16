#pragma once

#include "message/response.h"
#include "utils/deserializer.h"

#include <vector>

namespace supercharge::meteringvalues {
    
namespace message {

struct ResponseWrapper {

    std::vector<Response> responses;
};

} // namespace message

namespace utils {

template<>
struct ValueDeserializer<message::ResponseWrapper> {
    
    message::ResponseWrapper deserialize(const Json::Value& value) {
        ValueDeserializer<message::Response> response_deserializer;
        message::ResponseWrapper response_wrapper;
        if (!value.isMember("x")) {
            return response_wrapper;
        }
        const auto& responses = value["x"];
        if (!responses.isArray()) {
            return response_wrapper;
        }
        for (Json::Value::ArrayIndex i = 0; i != responses.size(); ++i) {
            response_wrapper.responses.emplace_back(
                response_deserializer.deserialize(responses[i]));
        }
        return response_wrapper;
    }
};

} // namespace utils

} // namespace supercharge::meteringvalues
