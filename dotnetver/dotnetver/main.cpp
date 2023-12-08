#include "stdafx.h"
#include "messages.h"
#include "ConsoleCodePage.h"

TCHAR* VAL_VERSION = TEXT("Version");
TCHAR* VAL_INSTALL = TEXT("Install");
TCHAR* VAL_SP      = TEXT("SP");

// How to determine which versions and service pack levels of the Microsoft .NET Framework are installed
// http://support.microsoft.com/kb/318785

//class LocalMachineRegistryKey
//{
//private:
//	HKEY hkey_;
//
//public:
//	LocalMachineRegistryKey(LPCWSTR lpSubKey)
//	{
//		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hkey_))
//
//	}
//};

DWORD releaseToMessageId(int release)
{
	switch (release)
	{
	// .NET 4.5
	case 378389: return MSG_NET45_INSTALLED;
	case 378675: return MSG_NET451_INSTALLED; // On Windows 8.1 and Windows Server 2012 R2
	case 378758: return MSG_NET451_INSTALLED; // On all other Windows operating systems
	case 379893: return MSG_NET452_INSTALLED;
	// .NET 4.6
	case 393295: return MSG_NET46_INSTALLED; // .NET 4.6 with Windows 10
	case 393297: return MSG_NET46_INSTALLED;
	case 394254: return MSG_NET461_INSTALLED; // .NET 4.6.1 on Windows 10
	case 394271: return MSG_NET461_INSTALLED;
	case 394747: return MSG_NET462_PREVIEW_INSTALLED; // .NET 4.6.2 on Windows 10 RS1 Preview
	case 394748: return MSG_NET462_PREVIEW_INSTALLED;
	// .NET 4.7
	case 460798: return MSG_NET47_INSTALLED; // On Windows 10 Creators Update
	case 460805: return MSG_NET47_INSTALLED; // On all other Windows operating systems (including other Windows 10 operating systems)
	case 461308: return MSG_NET471_INSTALLED; // On Windows 10 Fall Creators Update and Windows Server, version 1709
	case 461310: return MSG_NET471_INSTALLED; // On all other Windows operating systems (including other Windows 10 operating systems)
	case 461808: return MSG_NET472_INSTALLED; // On Windows 10 April 2018 Update and Windows Server, version 1803
	case 461814: return MSG_NET472_INSTALLED; // On all Windows operating systems other than Windows 10 April 2018 Update and Windows Server, version 1803
	// .NET 4.8
	case 528040: return MSG_NET48_INSTALLED; // On Windows 10 May 2019 Update and Windows 10 November 2019 Update: 
	case 528049: return MSG_NET48_INSTALLED; // On all other Windows operating systems (including other Windows 10 operating systems)
	case 528372: return MSG_NET48_INSTALLED; // On Windows 10 May 2020 Update, October 2020 Update, May 2021 Update, November 2021 Update, and 2022 Update
	case 528449: return MSG_NET48_INSTALLED; // On Windows 11 and Windows Server 2022
	// .NET 4.8.1
	case 533320: return MSG_NET481_INSTALLED; // On Windows 11 2022 Update and Windows 11 2023 Update
	case 533325: return MSG_NET481_INSTALLED; // All other Windows operating systems
	}

	return MSG_NET_UNKNOWN_RELEASE;
}

void printToConsole(wchar_t* message)
{
	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, message, -1, nullptr, 0, nullptr, nullptr);
	char* m = new char[bufferSize];
	WideCharToMultiByte(CP_UTF8, 0, message, -1, m, bufferSize, nullptr, nullptr);
	wprintf(L"%S", m); // C runtime version
	delete[] m;

	//DWORD len = lstrlen(message), written = 0;
	//WriteConsoleInput(
	//	GetStdHandle(STD_OUTPUT_HANDLE),
	//	message,
	//	lstrlen(message),
	//	&written
	//	);
}

void printToConsoleById(DWORD dwMessageId)
{
	//va_list args;
	//va_start(args, dwMessageId);

	LPTSTR buf;
	DWORD dwChars = FormatMessage(
		FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		dwMessageId,
		LANG_NEUTRAL, // Language: LANG_NEUTRAL = current thread's language
		//MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA),
		(LPTSTR)&buf,    // Destination buffer
		0,
		nullptr //&args         // Insertion parameters
		);

	//TODO: Check if we need to manually fallback to english?
	/*if (dwChars == 0)
	{

	}*/

	if (dwChars > 0)
	{
		printToConsole(buf);
		LocalFree(buf);
	}
}

TCHAR* regQueryStringValue(LPCWSTR lpSubKey, LPCWSTR lpValueName)
{
	TCHAR* pValue = nullptr;

	HKEY hkey;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hkey))
	{
		DWORD valueSize = 0;
		if (ERROR_SUCCESS == RegQueryValueEx(hkey, lpValueName, nullptr, nullptr, nullptr, &valueSize))
		{
			pValue = new TCHAR[valueSize];
			if (ERROR_SUCCESS != RegQueryValueEx(hkey, VAL_VERSION, nullptr, nullptr, (LPBYTE)pValue, &valueSize))
			{
				delete[] pValue;
				pValue = nullptr;
			}
		}
		RegCloseKey(hkey);
	}

	return pValue;
}

void regQueryInstallAndSP(LPCWSTR lpSubKey, LPDWORD lpInstall, LPDWORD lpSP)
{
	*lpInstall = -1;
	*lpSP = -1;

	HKEY hkey;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hkey))
	{
		DWORD valueSize = sizeof(DWORD);
		if (ERROR_SUCCESS != RegQueryValueEx(hkey, VAL_INSTALL, nullptr, nullptr, (LPBYTE)lpInstall, &valueSize))
		{
			*lpInstall = -1;
		}

		valueSize = sizeof(DWORD);
		if (ERROR_SUCCESS != RegQueryValueEx(hkey, VAL_SP, nullptr, nullptr, (LPBYTE)lpSP, &valueSize))
		{
			*lpSP = -1;
		}

		RegCloseKey(hkey);
	}
}

void checkDotNet10()
{
	// 1.0.3705.0 - .NET 1.0
	// 1.0.3705.1 - .NET 1.0 SP1
	// 1.0.3705.2 - .NET 1.0 SP2
	// 1.0.3705.3 - .NET 1.0 SP3
	TCHAR* pVersion = regQueryStringValue(TEXT("Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}"), VAL_VERSION);
	if (pVersion != nullptr)
	{
		delete[] pVersion;
	}

	pVersion = regQueryStringValue(TEXT("Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}"), VAL_VERSION);
	if (pVersion != nullptr)
	{
		delete[] pVersion;
	}
}

void checkDotNet11()
{
	DWORD install, sp;

	regQueryInstallAndSP(TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322"), &install, &sp);
	if (install != 1) return;

	if (sp == 0)
	{
		printToConsoleById(MSG_NET11_INSTALLED);
	}
	else if (sp == -1 || sp == 1)
	{
		printToConsoleById(MSG_NET11SP1_INSTALLED);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	ConsoleCodePage consoleCP(CP_UTF8);

	checkDotNet10();

	//HKEY hkey;
	//if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP"), 0, KEY_READ, &hkey))
	//{
	//	//RegQueryInfoKey
	//	TCHAR subkeyName[255 + 1];
	//	for (DWORD keyIdx = 0; ; ++keyIdx)
	//	{
	//		DWORD cName = 255 + 1;
	//		if (ERROR_SUCCESS != RegEnumKeyEx(hkey, keyIdx, subkeyName, &cName, nullptr, nullptr, nullptr, nullptr)) break;

	//		printToConsole(subkeyName);
	//		printToConsole(L"\n");
	//	}
	//	RegCloseKey(hkey);
	//}

	HKEY hkey;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full\\"), 0, KEY_READ, &hkey))
	{
		DWORD release, size = sizeof(release);
		if (ERROR_SUCCESS == RegQueryValueEx(hkey, TEXT("Release"), nullptr, nullptr, (LPBYTE) &release, &size))
		{
			printf("Release=%d\n", release);

			DWORD messageId = releaseToMessageId(release);
			//wprintf(TEXT("%d\n"), release);
			printToConsoleById(messageId);
		}
		RegCloseKey(hkey);
	}

	return 0;
}
