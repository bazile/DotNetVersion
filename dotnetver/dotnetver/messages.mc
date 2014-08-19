; // ***** Sample.mc *****
; // This is the header section.

MessageIdTypedef=DWORD

SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
Warning=0x2:STATUS_SEVERITY_WARNING
Error=0x3:STATUS_SEVERITY_ERROR
)

FacilityNames=(System=0x0:FACILITY_SYSTEM
Runtime=0x2:FACILITY_RUNTIME
Stubs=0x3:FACILITY_STUBS
Io=0x4:FACILITY_IO_ERROR_CODE
)

LanguageNames=(English=0x409:messages_en)
LanguageNames=(Russian=0x419:messages_ru)

MessageId    = 0x4500
Severity     = Informational
Facility     = Runtime
SymbolicName = MSG_NET45_INSTALLED
Language     = English
.NET v4.5 is installed
.

Language = Russian
.NET v4.5 установлен
.


MessageId    = 0x4510
Severity     = Informational
Facility     = Runtime
SymbolicName = MSG_NET451_INSTALLED
Language     = English
.NET v4.5.1 is installed
.

Language = Russian
.NET v4.5.1 установлен
.


MessageId    = 0x4520
Severity     = Informational
Facility     = Runtime
SymbolicName = MSG_NET452_INSTALLED
Language     = English
.NET v4.5.2 is installed
.

Language = Russian
.NET v4.5.2 установлен
.


MessageId    = 0x900
Severity     = Informational
Facility     = Runtime
SymbolicName = MSG_NET_UNKNOWN_RELEASE
Language     = English
Unknown release of .NET was found
.

Language = Russian
Неизвестный release .NET
.
