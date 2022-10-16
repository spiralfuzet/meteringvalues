#include "visitor/power_calculator.h"

#include <map>
#include <optional>

namespace supercharge::meteringvalues::visitor {

PowerCalculatorVisitor::PowerCalculatorVisitor(std::ostream& output) : output(output) {}

void PowerCalculatorVisitor::operator()(const message::MeterValues& meter_values) {
    std::map<MeasurandCategory, double> power_calculation_relevant_values;
    for (const auto& m : meter_values.meter_value) {
        for (const auto& sv : m.values) {
            if (sv.phase.has_value()) {
                power_calculation_relevant_values.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(sv.measurand, sv.phase.value()),
                    std::forward_as_tuple(sv.value)
                );
            }
        }
    }
    const auto l1_n_current_import = power_calculation_relevant_values.find(L1NCurrentImport);
    const auto l1_n_voltage = power_calculation_relevant_values.find(L1NVoltage);
    std::optional<double> l1_n_power_import = std::nullopt;
    if (l1_n_current_import != power_calculation_relevant_values.end() && l1_n_voltage != power_calculation_relevant_values.end()) {
        l1_n_power_import = std::make_optional(l1_n_current_import->second * l1_n_voltage->second);
        output << "\tPowerImport L1-N: " << *l1_n_power_import << " W" << std::endl;
    }
    const auto l2_n_current_import = power_calculation_relevant_values.find(L2NCurrentImport);
    const auto l2_n_voltage = power_calculation_relevant_values.find(L2NVoltage);
    std::optional<double> l2_n_power_import = std::nullopt;
    if (l2_n_current_import != power_calculation_relevant_values.end() && l2_n_voltage != power_calculation_relevant_values.end()) {
        l2_n_power_import = std::make_optional(l2_n_current_import->second * l2_n_voltage->second);
        output << "\tPowerImport L2-N: " << *l2_n_power_import << " W" << std::endl;
    }
    const auto l3_n_current_import = power_calculation_relevant_values.find(L3NCurrentImport);
    const auto l3_n_voltage = power_calculation_relevant_values.find(L3NVoltage);
    std::optional<double> l3_n_power_import = std::nullopt;
    if (l3_n_current_import != power_calculation_relevant_values.end() && l3_n_voltage != power_calculation_relevant_values.end()) {
        l3_n_power_import = std::make_optional(l3_n_current_import->second * l3_n_voltage->second);
        output << "\tPowerImport L3-N: " << *l1_n_power_import << " W" << std::endl;
    }
    if (l1_n_power_import.has_value() && l2_n_power_import.has_value() && l3_n_power_import.has_value()) {
        // Note: This is only true for symmetrical networks.
        // In an asymmetric network, angle values are needed for power value calculation 
        output << "\tPowerImport: " << l1_n_power_import.value() + l2_n_power_import.value() + l3_n_power_import.value() << " W" << std::endl;
    }
}

} // namespace supercharge::meteringvalues::visitor
