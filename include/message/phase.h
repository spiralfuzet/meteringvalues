#pragma once

namespace supercharge::meteringvalues::message {

enum class Phase {
    
    L1,
    L2,
    L3,
    N,
    L1N, // L1-N
    L2N, // L2-N
    L3N, // L3-N
    L1L2, // L1-l2
    L2L3, // L1-l2
    L3L1, // L3-l1
};

} // namespace supercharge::meteringvalues::message


