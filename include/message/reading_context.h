#pragma once

namespace supercharge::meteringvalues::message {
    
enum class ReadingContext {
    
    InterruptionBegin, // Interruption.Begin
    InterruptionEnd, // Interruption.End
    Other,
    SampleClock, // Sample.Clock
    SamplePeriodic, // Sample.Periodic
    TransactionBegin, // Transaction.Begin
    TransactionEnd,  // Transaction.End
    Trigger
};

}  // namespace supercharge::meteringvalues::message
