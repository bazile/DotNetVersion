#pragma once
class ConsoleCodePage
{
public:
	ConsoleCodePage(UINT wCodePageID);
	~ConsoleCodePage();
private:
	UINT oldConsoleCP_;
};
