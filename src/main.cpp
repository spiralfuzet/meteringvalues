#include "message/response_wrapper.h"
#include "utils/deserializer.h"
#include "visitor/visitor_composite.h"
#include "visitor/visitor_facade.h"
#include "visitor/meter_value_printer.h"
#include "visitor/power_calculator.h"

#include <iostream>

using namespace supercharge::meteringvalues::message;
using namespace supercharge::meteringvalues::utils;
using namespace supercharge::meteringvalues::visitor;

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Please provide metering file path as CLI argument";
    }

    try {
        Deserializer<ResponseWrapper> deserializer;
        const auto metering_values_payload = deserializer.deserialize(argv[1]);

        for (const auto& response : metering_values_payload.responses) {
            std::cout << "Id token: " << response.id_token << std::endl;
            std::visit(
                VisitorComposite {
                    VisitorFacade<MeterValues>{{
                        MeterValuesPrinterVisitor(std::cout),
                        PowerCalculatorVisitor(std::cout)
                    }},
                    [](auto) {} // default visitor
                },
                response.payload
            );
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
