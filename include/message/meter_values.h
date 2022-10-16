#pragma once

#include "message/meter_value.h"
#include "utils/deserializer.h"

#include <vector>

namespace supercharge::meteringvalues {

namespace message {

struct MeterValues {

    MeterValues(int connector_id, int transaction_id)
        : connector_id(connector_id), transaction_id(transaction_id) {}

    int connector_id;
    int transaction_id;

    std::vector<MeterValue> meter_value;
};

} // namespace message

namespace utils {

template<>
struct ValueDeserializer<message::MeterValues> {

    message::MeterValues deserialize(const Json::Value& value) {
        ValueDeserializer<message::MeterValue> meter_value_deserializer;
        if (!value.isMember("connectorId") || !value.isMember("transactionId")) {
            throw std::runtime_error("Illegal MeterValues payload. ConnectorId or TransactionId is missing.");
        }
        message::MeterValues meter_values(value["connectorId"].asInt(), value["transactionId"].asInt());
        if (!value.isMember("meterValue")) {
            return meter_values;
        }
        const auto& meter_values_array = value["meterValue"];
        if (!meter_values_array.isArray()) {
            return meter_values;
        }
        for (Json::Value::ArrayIndex i = 0; i != meter_values_array.size(); ++i) {
            meter_values.meter_value.emplace_back(
                meter_value_deserializer.deserialize(meter_values_array[i]));
        }
        return meter_values;
    }
};

} // namespace utils

} // namespace supercharge::meteringvalues
