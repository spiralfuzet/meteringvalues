#include "utils/timestamp.h"

#include <fmt/format.h>

#include <iomanip>
#include <sstream>

namespace supercharge::meteringvalues::utils {

std::tm localtime(std::time_t& tt) {
    std::tm tm{}; 
#if defined(__unix__)
    localtime_r(&tt, &tm);
#elif defined(_MSC_VER)
    localtime_s(&tm, &tt);
#else
    throw std::runtime_error("Not supported system");
#endif
    return tm;
}

TimeStamp::TimeStamp(const std::string& timestamp_string) {
    std::tm tm = {};
    std::stringstream ss(timestamp_string);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    if (ss.fail()) {
        throw std::runtime_error(fmt::format("Timestamp parsing failed for string: '{}'", timestamp_string));
    }
    time_point = std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::ostream& operator<<(std::ostream& os, const TimeStamp& ts) {
    std::time_t tt = std::chrono::system_clock::to_time_t(ts.time_point);
    std::tm tm = localtime(tt);
    os << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    return os;
}

} // namespace supercharge::meteringvalues::utils
