#pragma once

#include "message/sampled_value.h"
#include "utils/deserializer.h"
#include "utils/timestamp.h"

#include <vector>

namespace supercharge::meteringvalues {

namespace message {

struct MeterValue {

    explicit MeterValue(const utils::TimeStamp& timestamp): timestamp(timestamp) {}

    utils::TimeStamp timestamp;
    std::vector<SampledValue> values;  
};


} // namespace message

namespace utils {

template<>
struct ValueDeserializer<message::MeterValue> {

    message::MeterValue deserialize(const Json::Value& value) {

        ValueDeserializer<message::SampledValue> sampled_value_deserializer;
        message::MeterValue meter_value(TimeStamp(value["timestamp"].asString()));
        if (!value.isMember("sampledValue")) {
            return meter_value;
        }
        const auto& sampled_values = value["sampledValue"];
        if (!sampled_values.isArray()) {
            return meter_value;
        }
        for (Json::Value::ArrayIndex i = 0; i != sampled_values.size(); ++i) {
            meter_value.values.emplace_back(sampled_value_deserializer.deserialize(sampled_values[i]));
        }
        return meter_value;
    }
};

} // namespace utils

} // namespace supercharge::meteringvalues
