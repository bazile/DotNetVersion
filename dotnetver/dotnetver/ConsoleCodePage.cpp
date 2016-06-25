#include "stdafx.h"
#include "ConsoleCodePage.h"


ConsoleCodePage::ConsoleCodePage(UINT wCodePageID)
{
	oldConsoleCP_ = SetConsoleOutputCP(wCodePageID);
}


ConsoleCodePage::~ConsoleCodePage()
{
	SetConsoleOutputCP(oldConsoleCP_);
}
