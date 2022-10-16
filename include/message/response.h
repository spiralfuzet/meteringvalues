#pragma once

#include "message/message_trigger_enum_type.h"
#include "message/meter_values.h"
#include "utils/deserializer.h"

#include <fmt/format.h>
#include <magic_enum.hpp>

#include <string>
#include <variant>

namespace supercharge::meteringvalues {

namespace message {

// todo: add types for other message trigger types
using PayloadType = std::variant<MeterValues>;

struct Response {

    template <typename FWD>
    Response(int connector_id, const std::string& id_token, MessageTriggerEnumType message_trigger, FWD&& payload_content)
        : connector_id(connector_id),
        id_token(id_token),
        message_trigger(message_trigger),
        payload(std::forward<FWD>(payload_content)) {}

    int connector_id;
    std::string id_token;
    MessageTriggerEnumType message_trigger;
    PayloadType payload;

    const auto& get() const {
        switch (message_trigger) {
            case MessageTriggerEnumType::MeterValues:
            return std::get<MeterValues>(payload);
            default:
            throw std::runtime_error(fmt::format(
                "Message type: '{}' is not supported", magic_enum::enum_name(message_trigger)));
        }
    }
};

} // namespace message

namespace utils {

struct PayloadDeserializerSelector {

    PayloadDeserializerSelector() = delete;

    static auto payload_deserializer(const message::MessageTriggerEnumType& message_trigger) {
        switch (message_trigger) {
            case message::MessageTriggerEnumType::MeterValues:
                return ValueDeserializer<message::MeterValues>();
            default:
                throw std::runtime_error(fmt::format(
                    "No parser implemented for payload type: '{}'",
                    magic_enum::enum_name(message_trigger)));
        }
    }
};

template<>
struct ValueDeserializer<message::Response> {

    message::Response deserialize(const Json::Value& value) {
        if (value.size() != 4) {
            std::runtime_error("Response should contain exactly 4 elements");
        }
        const auto message_trigger = EnumDeserializer<message::MessageTriggerEnumType>::deserialize(value[2]);
        message::Response response(value[0].asInt(), value[1].asString(), message_trigger,
            PayloadDeserializerSelector::payload_deserializer(message_trigger).deserialize(value[3]));
        return response;
    }
};

} // namespace utils

} // namespace supercharge::meteringvalues
