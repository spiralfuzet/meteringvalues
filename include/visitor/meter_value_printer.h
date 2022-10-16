#pragma once

#include "message/meter_values.h"

#include <iostream>

namespace supercharge::meteringvalues::visitor {

struct MeterValuesPrinterVisitor {

    explicit MeterValuesPrinterVisitor(std::ostream& output);

    void operator()(const message::MeterValues& meter_values);

    private:
    std::ostream& output;
};

} // namespace supercharge::meteringvalues::visitor
