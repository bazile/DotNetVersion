//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_RUNTIME                 0x2
#define FACILITY_STUBS                   0x3
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: MSG_NET11_INSTALLED
//
// MessageText:
//
// .NET Framework v1.1 is installed
//
#define MSG_NET11_INSTALLED              ((DWORD)0x40021100L)

//
// MessageId: MSG_NET11SP1_INSTALLED
//
// MessageText:
//
// .NET Framework v1.1 SP1 is installed
//
#define MSG_NET11SP1_INSTALLED           ((DWORD)0x40021110L)

//
// MessageId: MSG_NET45_INSTALLED
//
// MessageText:
//
// .NET Framework v4.5 is installed
//
#define MSG_NET45_INSTALLED              ((DWORD)0x40024500L)

//
// MessageId: MSG_NET451_INSTALLED
//
// MessageText:
//
// .NET Framework v4.5.1 is installed
//
#define MSG_NET451_INSTALLED             ((DWORD)0x40024510L)

//
// MessageId: MSG_NET452_INSTALLED
//
// MessageText:
//
// .NET Framework v4.5.2 is installed
//
#define MSG_NET452_INSTALLED             ((DWORD)0x40024520L)

//
// MessageId: MSG_NET46_INSTALLED
//
// MessageText:
//
// .NET Framework v4.6 is installed
//
#define MSG_NET46_INSTALLED              ((DWORD)0x40024600L)

//
// MessageId: MSG_NET461_INSTALLED
//
// MessageText:
//
// .NET Framework v4.6.1 is installed
//
#define MSG_NET461_INSTALLED             ((DWORD)0x40024610L)

//
// MessageId: MSG_NET462_PREVIEW_INSTALLED
//
// MessageText:
//
// .NET Framework v4.6.2 Preview is installed
//
#define MSG_NET462_PREVIEW_INSTALLED     ((DWORD)0x40024621L)

//
// MessageId: MSG_NET47_INSTALLED
//
// MessageText:
//
// .NET Framework v4.7 is installed
//
#define MSG_NET47_INSTALLED              ((DWORD)0x40024700L)

//
// MessageId: MSG_NET471_INSTALLED
//
// MessageText:
//
// .NET Framework v4.7.1 is installed
//
#define MSG_NET471_INSTALLED             ((DWORD)0x40024710L)

//
// MessageId: MSG_NET472_INSTALLED
//
// MessageText:
//
// .NET Framework v4.7.2 is installed
//
#define MSG_NET472_INSTALLED             ((DWORD)0x40024720L)

//
// MessageId: MSG_NET48_INSTALLED
//
// MessageText:
//
// .NET Framework v4.8 is installed
//
#define MSG_NET48_INSTALLED              ((DWORD)0x40024800L)

//
// MessageId: MSG_NET481_INSTALLED
//
// MessageText:
//
// .NET Framework v4.8.1 is installed
//
#define MSG_NET481_INSTALLED             ((DWORD)0x40024810L)

//
// MessageId: MSG_NET_UNKNOWN_RELEASE
//
// MessageText:
//
// Unknown release of .NET was found
//
#define MSG_NET_UNKNOWN_RELEASE          ((DWORD)0x40020900L)

