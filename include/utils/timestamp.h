#pragma once

#include <chrono>
#include <iostream>

namespace supercharge::meteringvalues::utils {

inline static std::tm localtime(std::time_t& tt);

struct TimeStamp {

    explicit TimeStamp(const std::string& timestamp_string);

    friend std::ostream& operator<<(std::ostream& os, const TimeStamp& ts);

    private:
    std::chrono::time_point<std::chrono::system_clock> time_point;

};

} // namespace supercharge::meteringvalues::utils
