#pragma once

#include "message/reading_context.h"
#include "message/measurand.h"
#include "message/phase.h"
#include "message/location.h"
#include "message/unit.h"
#include "message/value_format.h"
#include "utils/deserializer.h"

#include <optional>
#include <string>

namespace supercharge::meteringvalues {

namespace message {

struct SampledValue {

    SampledValue(double value) : value(value),
        reading_context(ReadingContext::SamplePeriodic),
        value_format(ValueFormat::Raw),
        measurand(Measurand::EnergyActiveImportRegister),
        phase(std::nullopt),
        location(Location::Outlet),
        unit(UnitOfMeasure::Wh) {}

    double value;
    ReadingContext reading_context;
    ValueFormat value_format;
    Measurand measurand;
    std::optional<Phase> phase;
    Location location;
    UnitOfMeasure unit;
};

} // namespace message

namespace utils {

template<>
struct ValueDeserializer<message::SampledValue> {

    message::SampledValue deserialize(const Json::Value& value) {

        message::SampledValue sampled_value(std::stod(value["value"].asString()));
        if (value.isMember("context")) {
            sampled_value.reading_context = EnumDeserializer<message::ReadingContext>::deserialize(value, "context");
        }
        if (value.isMember("format")) {
            sampled_value.value_format = EnumDeserializer<message::ValueFormat>::deserialize(value, "format");
        }
        if (value.isMember("measurand")) {
            sampled_value.measurand = EnumDeserializer<message::Measurand>::deserialize(value, "measurand");
        }
        if (value.isMember("phase")) {
            sampled_value.phase = EnumDeserializer<message::Phase>::deserialize(value, "phase");
        }
        if (value.isMember("location")) {
            sampled_value.location = EnumDeserializer<message::Location>::deserialize(value, "location");
        }
        if (value.isMember("unit")) {
            sampled_value.unit = EnumDeserializer<message::UnitOfMeasure>::deserialize(value, "unit");
        }
        return sampled_value;
    }
};

} // namespace utils

} // namespace supercharge::meteringvalues
