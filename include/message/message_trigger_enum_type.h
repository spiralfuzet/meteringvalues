#pragma once

namespace supercharge::meteringvalues::message {

enum class MessageTriggerEnumType {
    
    BootNotification,
    LogStatusNotification,
    FirmwareStatusNotification,
    Heartbeat,
    MeterValues,
    SignChargePointCertificate,
    StatusNotification
};

} // namespace supercharge::meteringvalues::message
