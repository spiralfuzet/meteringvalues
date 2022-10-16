#pragma once

namespace supercharge::meteringvalues::message {

enum class Measurand {

    CurrentExport, // Current.Export
    CurrentImport, // Current.Import
    CurrentOffered, // Current.Offered
    EnergyActiveExportRegister, //Energy.Active.Export.Register
    EnergyActiveImportRegister, // Energy.Active.Import.Register
    EnergyReactiveExportRegister, // Energy.Reactive.Export.Register
    EnergyReactiveImportRegister, // Energy.Reactive.Import.Register
    EnergyActiveExportInterval, // Energy.Active.Export.Interval
    EnergyActiveImportInterval, // Energy.Active.Import.Interval
    EnergyReactiveExportInterval, // Energy.Reactive.Export.Interval
    EnergyReactiveImportInterval, // Energy.Reactive.Import.Interval
    Frequency,
    PowerActiveExport, // Power.Active.Export
    PowerActiveImport, // Power.Active.Import
    PowerFactor, // Power.Factor
    PowerOffered, // Power.Offered
    PowerReactiveExport, // Power.Reactive.Export
    PowerReactiveImport, // Power.Reactive.Import
    RPM,
    SoC,
    Temperature,
    Voltage
};

} // namespace supercharge::meteringvalues::message
