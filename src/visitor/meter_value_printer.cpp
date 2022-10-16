#include "visitor/meter_value_printer.h"

namespace supercharge::meteringvalues::visitor {

MeterValuesPrinterVisitor::MeterValuesPrinterVisitor(std::ostream& output) : output(output) {}

void MeterValuesPrinterVisitor::operator()(const message::MeterValues& meter_values) {
    for (const auto& m : meter_values.meter_value) {
        output << "\t" << m.timestamp << std::endl << "\t--------------------" << std::endl;
        for (const auto& sv : m.values) {
            output << "\t" << magic_enum::enum_name(sv.measurand)
                << (sv.phase.has_value() ? fmt::format(" {}", magic_enum::enum_name(sv.phase.value())) : "")
                << " " << sv.value
                << " " << magic_enum::enum_name(sv.unit) << std::endl;
        }
    }
}

} // namespace supercharge::meteringvalues::visitor
