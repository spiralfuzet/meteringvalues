#pragma once

#include "message/meter_values.h"

#include <iostream>

namespace supercharge::meteringvalues::visitor {

struct PowerCalculatorVisitor {

    explicit PowerCalculatorVisitor(std::ostream& output);

    void operator()(const message::MeterValues& meter_values);

    private:
    std::ostream& output;

    using MeasurandCategory = std::pair<message::Measurand, message::Phase>;

    constexpr static MeasurandCategory L1NCurrentImport = std::make_pair(message::Measurand::CurrentImport, message::Phase::L1N);
    constexpr static MeasurandCategory L2NCurrentImport = std::make_pair(message::Measurand::CurrentImport, message::Phase::L2N);
    constexpr static MeasurandCategory L3NCurrentImport = std::make_pair(message::Measurand::CurrentImport, message::Phase::L3N);
    constexpr static MeasurandCategory L1NVoltage = std::make_pair(message::Measurand::Voltage, message::Phase::L1N);
    constexpr static MeasurandCategory L2NVoltage = std::make_pair(message::Measurand::Voltage, message::Phase::L2N);
    constexpr static MeasurandCategory L3NVoltage = std::make_pair(message::Measurand::Voltage, message::Phase::L3N);

};

} // namespace supercharge::meteringvalues::visitor
