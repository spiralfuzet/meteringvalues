#include "visitor/power_calculator.h"

#include "catch.hpp"

#include <sstream>

using namespace supercharge::meteringvalues::visitor;
using namespace supercharge::meteringvalues::message;
using namespace supercharge::meteringvalues::utils;

struct MeteredValuesBuilder {

    MeteredValuesBuilder(int connector_id, int transaction_id) : meter_values(connector_id, transaction_id) {}

    MeteredValuesBuilder& metered_value(const TimeStamp& timestamp) {
        meter_values.meter_value.emplace_back(timestamp);
        return *this;
    }

    MeteredValuesBuilder& voltage(double value, Phase phase) {
        SampledValue voltage(value);
        voltage.measurand = Measurand::Voltage;
        voltage.unit = UnitOfMeasure::V;
        voltage.phase = std::make_optional(phase);
        meter_values.meter_value[meter_values.meter_value.size() - 1].values.emplace_back(std::move(voltage));
        return *this;
    }

    MeteredValuesBuilder& imported_current(double value, Phase phase) {
        SampledValue current(value);
        current.measurand = Measurand::CurrentImport;
        current.unit = UnitOfMeasure::A;
        current.phase = std::make_optional(phase);
        meter_values.meter_value[meter_values.meter_value.size() - 1].values.emplace_back(std::move(current));
        return *this;
    }

    const MeterValues& build() const {
        return meter_values;
    }

    private:
    MeterValues meter_values;
};

TEST_CASE("PowerCalculatorVisitor::operator() prints nothing if there is no voltage and current sampled value in the same phase") {
    // Given voltage and current measurements but in different phases
    std::string measurement_time_str = "2022-10-15T20:20:15Z";
    TimeStamp measurement_time(measurement_time_str);
    const auto meter_values = MeteredValuesBuilder(1, 1)
        .metered_value(measurement_time)
        .voltage(230.1, Phase::L1N)
        .imported_current(12.8, Phase::L2N)
        .build();
    // When calling power calculation
    std::stringstream output_stream;
    PowerCalculatorVisitor power_calculator_visitor(output_stream);
    power_calculator_visitor(meter_values);
    // Then no power was calculated
    REQUIRE(output_stream.str().empty());
}

TEST_CASE("PowerCalculatorVisitor::operator() prints power by phase if voltage and current are both given") {
    // Given voltage and current measurements in the same phase
    std::string measurement_time_str = "2022-10-15T20:20:15Z";
    TimeStamp measurement_time(measurement_time_str);
    const auto phase = Phase::L1N;
    const auto voltage = 230.1;
    const auto current = 12.8;
    const auto meter_values = MeteredValuesBuilder(1, 1)
        .metered_value(measurement_time)
        .voltage(voltage, phase)
        .imported_current(current, phase)
        .build();
    // When calling power calculation
    std::stringstream output_stream;
    PowerCalculatorVisitor power_calculator_visitor(output_stream);
    power_calculator_visitor(meter_values);
    // Then power was calculated
    const auto printed_lines = StringUtils::tokenize(output_stream.str(), '\n');
    REQUIRE(printed_lines.size() == 2);
    const auto power_import_tokens = StringUtils::tokenize(printed_lines[0], ' ');
    REQUIRE(power_import_tokens.size() == 4);
    REQUIRE(StringUtils::replace(power_import_tokens[0], "\t", "") == "PowerImport");
    REQUIRE(power_import_tokens[1] == "L1-N:");
    REQUIRE(std::fabs(std::stod(power_import_tokens[2]) - voltage * current) < 10e-8);
    REQUIRE(power_import_tokens[3] == magic_enum::enum_name(UnitOfMeasure::W));
}

TEST_CASE("PowerCalculatorVisitor::operator() prints all three phase power and line power if all three phase voltages and currents are given") {
    // Given voltage and current measurements in the same phase
    std::string measurement_time_str = "2022-10-15T20:20:15Z";
    TimeStamp measurement_time(measurement_time_str);
    const auto voltage = 230.1;
    const auto current = 12.8;
    const auto meter_values = MeteredValuesBuilder(1, 1)
        .metered_value(measurement_time)
        .voltage(voltage, Phase::L1N)
        .imported_current(current, Phase::L1N)
        .voltage(voltage, Phase::L2N)
        .imported_current(current, Phase::L2N)
        .voltage(voltage, Phase::L3N)
        .imported_current(current, Phase::L3N)
        .build();
    // When calling power calculation
    std::stringstream output_stream;
    PowerCalculatorVisitor power_calculator_visitor(output_stream);
    power_calculator_visitor(meter_values);
    // Then power was calculated
    const auto printed_lines = StringUtils::tokenize(output_stream.str(), '\n');
    REQUIRE(printed_lines.size() == 5);
    
    const auto power_import_tokens = StringUtils::tokenize(printed_lines[3], ' ');
    REQUIRE(power_import_tokens.size() == 3);
    REQUIRE(StringUtils::replace(power_import_tokens[0], "\t", "") == "PowerImport:");
    REQUIRE(std::fabs(std::stod(power_import_tokens[1]) - 3 * voltage * current) < 10e-8);
    REQUIRE(power_import_tokens[2] == magic_enum::enum_name(UnitOfMeasure::W));
}
