#pragma once

#include <functional>

namespace supercharge::meteringvalues::visitor {

template<typename A>
struct VisitorFacade {

    VisitorFacade(const std::vector<std::function<void(const A&)>>& visitors) : visitors(visitors) {}

    void operator()(const A& arg) {
        std::for_each(visitors.begin(), visitors.end(), [&arg](auto& v) { v(arg); });
    }

    private:
    std::vector<std::function<void(const A&)>> visitors;
};

} // namespace supercharge::meteringvalues::visitor
