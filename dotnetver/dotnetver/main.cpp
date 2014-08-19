#include "stdafx.h"
#include "messages.h"


template<typename Key, typename Type>
Type getValueOrDefault(const std::map<Key, Type>& map, const Key& keyToFind, Type defaultValue)
{
	auto pair = map.find(keyToFind);
	return pair != map.end() ? (*pair).second : defaultValue;
}

void printToConsoleById(DWORD messageId);
void printToConsole(wchar_t* message);

int _tmain(int argc, _TCHAR* argv[])
{
	UINT oldConsoleCP = SetConsoleOutputCP(CP_UTF8);

	HKEY hkey;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full\\"), 0, KEY_READ, &hkey))
	{
		DWORD release, size = sizeof(release);
		if (ERROR_SUCCESS == RegQueryValueEx(hkey, TEXT("Release"), NULL, NULL, (LPBYTE) &release, &size))
		{
			std::map<int, DWORD> releaseToMessage;
			releaseToMessage[378389] = MSG_NET45_INSTALLED;
			releaseToMessage[378675] = MSG_NET451_INSTALLED; // .NET 4.5.1 with Windows 8.1
			releaseToMessage[378758] = MSG_NET451_INSTALLED;
			releaseToMessage[379893] = MSG_NET452_INSTALLED;

			DWORD messageId = getValueOrDefault<int, DWORD>(releaseToMessage, release, MSG_NET_UNKNOWN_RELEASE);
			printToConsoleById(messageId);
		}
		RegCloseKey(hkey);
	}

	SetConsoleOutputCP(oldConsoleCP);
	return 0;
}

void printToConsole(wchar_t* message)
{
	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, message, -1, NULL, 0, NULL, NULL);
	char* m = new char[bufferSize];
	WideCharToMultiByte(CP_UTF8, 0, message, -1, m, bufferSize, NULL, NULL);
	wprintf(L"%S", m);
	delete[] m;
}

void printToConsoleById(DWORD dwMessageId)
{
	//va_list args;
	//va_start(args, dwMessageId);

	LPTSTR buf;
	DWORD dwChars = FormatMessage(
		FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		dwMessageId,
		LANG_NEUTRAL, // Language: LANG_NEUTRAL = current thread's language
		//MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA), 
		(LPTSTR) &buf,    // Destination buffer
		0,
		NULL //&args         // Insertion parameters
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
